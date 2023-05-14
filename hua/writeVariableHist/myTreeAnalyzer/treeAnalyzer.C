#include <iostream>

#include "treeAnalyzer.h"
#include "../SFfileMap.h"
#include "functions.h"
#include "../../src_cpp/lumiAndCrossSection.h"
#include "commenSelectionAndWeight.C"

void treeAnalyzer::Init()
{
    std::cout << "start to initilation\n";
    cutFlowHist->SetDirectory(m_outFile);

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
        "CMS_eff_t_vsJet" + m_era + "Up",
        "CMS_eff_t_vsJet" + m_era + "Down",
        "CMS_tttt_eff_e_" + m_era + "Up",   // our TOP MVA Lepton SF uncertainty
        "CMS_tttt_eff_e_" + m_era + "Down", // our TOP MVA Lepton SF uncertainty
        "CMS_tttt_eff_m_" + m_era + "Up",   // our TOP MVA Lepton SF uncertainty
        "CMS_tttt_eff_m_" + m_era + "Down", // our TOP MVA Lepton SF uncertainty
        "CMS_btag_shape_" + m_era + "Up",
        "CMS_btag_shape_" + m_era + "Down",
    };
    SR1tau1lSys = histsForRegionsMap("BDT", "BDT score", m_processName, 20, -0.28, 0.4, sysRegions);
    // SR1tau1lSys.print();
    SR1tau1lSys.setDir(m_outFile);

    readBranch();
    std::cout << "done initializing\n";
    std::cout << "\n";
}

void treeAnalyzer::readBranch()
{
    // for (const auto &elem : variablesOriginAll)
    //???SetBranchAddress here could overwrite previous variables
    //!!!bug!!!
    // not efficient to set up a event class with map to access each branch by string
    // Only use map for BDT , for other variables use normal event class
    /*
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
    */
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

    for (UInt_t i = 0; i < allEvent; i++)
    {
        m_tree->GetEntry(i);
        cutFlowHist->Fill(0);

        if (!(baselineSelection(e)))
        {
            continue;
        }
        cutFlowHist->Fill(1);

        if (!(SR1tau1lSel(e)))
        {
            continue;
        }
        cutFlowHist->Fill(2);

        std::cout << e->tausT_number.v() << e->jets_number.v() << "\n";

        /*
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

                Int_t leptons_number = elesTopMVAT_number + muonsTopMVAT_number;
                Bool_t SR1tau1l = tausT_number == 1 && leptons_number == 1 && jets_number >= 7 && bjetsM_num >= 2;

                // Return the MVA outputs and fill into histograms
                Double_t basicWeight = EVENT_prefireWeight * EVENT_genWeight * PUweight_ * HLT_weight * tauT_IDSF_weight_new * elesTopMVAT_weight * musTopMVAT_weight * btagShape_weight * btagShapeR;

                // filling hists
                SR1tau1lSys.fillHistVec("SR", bdtScore, basicWeight, SR1tau1l, m_isData);
                SR1tau1lSys.fillHistVec("CMS_pileup_" + m_era + "Up", bdtScore, (basicWeight / PUweight_) * PUweight_up_, SR1tau1l, m_isData);
                SR1tau1lSys.fillHistVec("CMS_pileup_" + m_era + "Down", bdtScore, (basicWeight / PUweight_) * PUweight_down_, SR1tau1l, m_isData);
                SR1tau1lSys.fillHistVec("CMS_prefiring_" + m_era + "Up", bdtScore, (basicWeight / EVENT_prefireWeight) * EVENT_prefireWeight_up, SR1tau1l, m_isData);
                SR1tau1lSys.fillHistVec("CMS_prefiring_" + m_era + "Down", bdtScore, (basicWeight / EVENT_prefireWeight) * EVENT_prefireWeight_down, SR1tau1l, m_isData);
                SR1tau1lSys.fillHistVec("CMS_eff_t_vsJet" + m_era + "Up", bdtScore, (basicWeight / tauT_IDSF_weight_new) * tauT_IDSF_weight_new_vsjet_up, SR1tau1l, m_isData);
                SR1tau1lSys.fillHistVec("CMS_eff_t_vsJet" + m_era + "Down", bdtScore, (basicWeight / tauT_IDSF_weight_new) * tauT_IDSF_weight_new_vsjet_down, SR1tau1l, m_isData);
                SR1tau1lSys.fillHistVec("CMS_tttt_eff_e_" + m_era + "Up", bdtScore, (basicWeight / elesTopMVAT_weight) * elesTopMVAT_weight_up, SR1tau1l, m_isData);
                SR1tau1lSys.fillHistVec("CMS_tttt_eff_e_" + m_era + "Down", bdtScore, (basicWeight / elesTopMVAT_weight) * elesTopMVAT_weight_down, SR1tau1l, m_isData);
                SR1tau1lSys.fillHistVec("CMS_tttt_eff_m_" + m_era + "Up", bdtScore, (basicWeight / musTopMVAT_weight) * musTopMVAT_weight_up, SR1tau1l, m_isData);
                SR1tau1lSys.fillHistVec("CMS_tttt_eff_m_" + m_era + "Down", bdtScore, (basicWeight / musTopMVAT_weight) * musTopMVAT_weight_down, SR1tau1l, m_isData);
            }
            */
    }
    std::cout << "end of event loop\n";
    std::cout << "\n";
};

void treeAnalyzer::Terminate()
{
    std::cout << "Termintate: \n";
    Double_t genWeightSum = getGenSum(m_input);
    Double_t processScale = ((lumiMap[m_era] * crossSectionMap[m_processName]) / genWeightSum);
    if (!m_isData)
    {
        SR1tau1lSys.scale(processScale);
    };
    SR1tau1lSys.print();

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