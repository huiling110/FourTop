#include <iostream>

#include "treeAnalyzer.h"
#include "../SFfileMap.h"
#include "functions.h"
#include "../../src_cpp/lumiAndCrossSection.h"

void treeAnalyzer::Init()
{
    std::cout << "start to initilation\n";

    // book MVA reader
    TString variableList = BDTTrainingMap[m_era].at(0);
    readVariableList(variableList, variablesName, variablesForReader, variablesOriginAll);
    // std::cout << " " << variablesForReader.size() << " " << variablesOriginAll.size() << "\n";
    for (UInt_t i = 0; i < variablesName.size(); i++)
    {
        reader->AddVariable(variablesName[i], &variablesForReader[i]);
        // must add all variables as floats even for int
    }

    TString methodName = "BDT" + TString(" method");
    TString weightfile = BDTTrainingMap[m_era].at(1) + "TMVAClassification" + TString("_") + "BDT" + TString(".weights.xml");
    reader->BookMVA(methodName, weightfile);

    // regions for hists
    std::vector<TString> sysRegions = {
        "SR",
        "CMS_pileup_" + m_era + "Up",
        "CMS_pileup_" + m_era + "Down",
        "CMS_prefiring_" + m_era + "Up",
        "CMS_prefiring_" + m_era + "Down",
        "CMS_eff_t_" + m_era + "Up",
        "CMS_eff_t_" + m_era + "Down",
        "CMS_tttt_eff_e_" + m_era + "Up",   // our TOP MVA Lepton SF uncertainty
        "CMS_tttt_eff_e_" + m_era + "Down", // our TOP MVA Lepton SF uncertainty
        "CMS_tttt_eff_m_" + m_era + "Up",   // our TOP MVA Lepton SF uncertainty
        "CMS_tttt_eff_m_" + m_era + "Down", // our TOP MVA Lepton SF uncertainty
        "CMS_btag_shape_" + m_era + "Up",
        "CMS_btag_shape_" + m_era + "Down",
    };
    SR1tau1lSys = histsForRegionsMap("BDT", "BDT score", m_processName, 20, -0.28, 0.4, sysRegions);
    SR1tau1lSys.print();
    SR1tau1lSys.setDir(m_outFile);

    readBranch();
    std::cout << "done initializing\n";
    std::cout << "\n";
}

void treeAnalyzer::readBranch()
{
    m_tree->SetBranchAddress("tausT_number", &tausT_number);
    m_tree->SetBranchAddress("elesTopMVAT_number", &elesTopMVAT_number);
    m_tree->SetBranchAddress("muonsTopMVAT_number", &muonsTopMVAT_number);
    m_tree->SetBranchAddress("jets_number", &jets_number);
    m_tree->SetBranchAddress("bjetsM_num", &bjetsM_num);
    m_tree->SetBranchAddress("leptonsMVAT_2OS", &leptonsMVAT_2OS);
    m_tree->SetBranchAddress("jets_HT", &jets_HT);
    m_tree->SetBranchAddress("jets_6pt", &jets_6pt);
    m_tree->SetBranchAddress("EVENT_genWeight", &EVENT_genWeight);
    m_tree->SetBranchAddress("EVENT_prefireWeight", &EVENT_prefireWeight);
    m_tree->SetBranchAddress("EVENT_prefireWeight_up", &EVENT_prefireWeight_up);
    m_tree->SetBranchAddress("EVENT_prefireWeight_down", &EVENT_prefireWeight_down);
    m_tree->SetBranchAddress("PUweight_", &PUweight_);
    m_tree->SetBranchAddress("PUweight_up_", &PUweight_up_);
    m_tree->SetBranchAddress("PUweight_down_", &PUweight_down_);
    m_tree->SetBranchAddress("HLT_weight", &HLT_weight);
    m_tree->SetBranchAddress("tauT_IDSF_weight_new", &tauT_IDSF_weight_new);
    m_tree->SetBranchAddress("elesTopMVAT_weight", &elesTopMVAT_weight);
    m_tree->SetBranchAddress("musTopMVAT_weight", &musTopMVAT_weight);
    m_tree->SetBranchAddress("btagShape_weight", &btagShape_weight);
    m_tree->SetBranchAddress("btagShapeR", &btagShapeR);

    // for (const auto &elem : variablesOriginAll)
    for (UInt_t i = 0; i < variablesOriginAll.size(); i++)
    {
        if (std::holds_alternative<Int_t>(variablesOriginAll[i]))
        {
            m_tree->SetBranchAddress(variablesName[i], std::addressof(std::get<Int_t>(variablesOriginAll[i])));
        }
        else if (std::holds_alternative<Double_t>(variablesOriginAll[i]))
        {
            m_tree->SetBranchAddress(variablesName[i], std::addressof(std::get<Double_t>(variablesOriginAll[i])));
        }
    }
}

void treeAnalyzer::LoopTree()
{
    std::cout << "start to loop tree\n";
    Long64_t allEvent = m_tree->GetEntries();
    if (m_isTest)
    {
        allEvent = 1000;
    }
    std::cout << "looping over trees of " << allEvent << "\n";

    for (UInt_t e = 0; e < allEvent; e++)
    {
        m_tree->GetEntry(e);
        // baseline selection
        //!!!could write a event class, so that all this commen cut and weight can be in one file
        // if (!(jets_number >= 6 && jets_6pt > 40.0 && jets_HT > 500.0 && bjetsM_num >= 1))
        // {
        //     continue;
        // }

        // need to convert the branch Int_t and Double_t for reader
        for (UInt_t j = 0; j < variablesForReader.size(); j++)
        {
            if (std::holds_alternative<Int_t>(variablesOriginAll[j]))
            {
                variablesForReader.at(j) = std::get<Int_t>(variablesOriginAll[j]);
            }
            else
            {
                variablesForReader.at(j) = std::get<Double_t>(variablesOriginAll[j]);
            }
        }
        Double_t bdtScore = reader->EvaluateMVA("BDT method");

        Int_t leptonsMVAT_number = elesTopMVAT_number + muonsTopMVAT_number;
        Bool_t SR1tau1l = tausT_number == 1 && leptonsMVAT_number == 1 && jets_number >= 7 && bjetsM_num >= 2;

        // Return the MVA outputs and fill into histograms
        Double_t basicWeight = EVENT_prefireWeight * EVENT_genWeight * PUweight_ * HLT_weight * tauT_IDSF_weight_new * elesTopMVAT_weight * musTopMVAT_weight * btagShape_weight * btagShapeR;

        // filling hists
        SR1tau1lSys.fillHistVec("SR", bdtScore, basicWeight, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_pileup_" + m_era + "Up", bdtScore, (basicWeight / PUweight_) * PUweight_up_, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_pileup_" + m_era + "Down", bdtScore, (basicWeight / PUweight_) * PUweight_down_, SR1tau1l, m_isData);
    }
    std::cout << "end of event loop\n";
    std::cout << "\n";
}

void treeAnalyzer::Terminate()
{
    std::cout << "Termintate: \n";
    Double_t genWeightSum = getGenSum(m_input);
    Double_t processScale = ((lumiMap[m_era] * crossSectionMap[m_processName]) / genWeightSum);
    if (!m_isData)
    {
        SR1tau1lSys.scale(processScale);
    };

    m_outFile->Write();
    std::cout << "outputFile here: " << m_outFile->GetName() << "\n";
}

treeAnalyzer::~treeAnalyzer()
{
    // code to free any dynamically allocated resources
    m_file->Close();
    m_outFile->Close();
    // delete m_tree;
    // delete m_file;
    // delete m_outFile;
}