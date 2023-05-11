#include <iostream>

#include "treeAnalyzer.h"
#include "../SFfileMap.h"

void readVariableList(TString variableListCsv, std::vector<TString> &variablesName, std::vector<Float_t> &variablesForReader, std::vector<std::variant<Int_t, Double_t>> &variablesOriginAll)
{
    std::cout << "reading varibleList: " << variableListCsv << "\n";
    std::ifstream fin(variableListCsv);
    std::string line;
    TString ivariable;
    variablesName.clear();
    variablesOriginAll.clear();
    variablesForReader.clear();
    while (getline(fin, line))
    {
        ivariable = line;
        if (line.size() > 0)
        {
            std::cout << "reading ivariable =" << ivariable << "\n";
            variablesName.push_back(ivariable);
            variablesForReader.push_back(0.0); // tree reader can only read float

            if (ivariable.Contains("number") || ivariable.Contains("num") || ivariable.Contains("charge"))
            {
                std::cout << "reading int ivariable =" << ivariable << "\n";
                variablesOriginAll.push_back(0);
            }
            else
            {
                variablesOriginAll.push_back(0.0);
            }
        }
    }
    fin.close();
}

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
    // std::vector<TString> sysRegions = {"1tau1lSR", "1tau1lPileupUp", "1tau1lPileupDown"};
    // histsForRegionsMap SR1tau1lSys{"BDT", "BDT score", processName, 20, -0.28, 0.4, sysRegions};

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

    // bdt hists
    std::vector<TString> sysRegions = {"1tau1lSR", "1tau1lPileupUp", "1tau1lPileupDown"};
    SR1tau1lSys = histsForRegionsMap{"BDT", "BDT score", m_processName, 20, -0.28, 0.4, sysRegions};
}

void treeAnalyzer::LoopTree()
{
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
        // printf("");
        if (!(jets_number >= 6 && jets_6pt > 40.0 && jets_HT > 500.0 && bjetsM_num >= 1))
        {
            continue;
        }

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
        std::cout << "BDT=" << bdtScore << "\n";

        // filling hists
    }
}

void treeAnalyzer::Terminate()
{
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