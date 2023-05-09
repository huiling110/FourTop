#include <iostream>

#include "treeAnalyzer.h"
#include "../SFfileMap.h"

void readVariableList(TString variableListCsv, std::vector<TString> &variablesName, std::vector<Float_t> &variablesForReader, std::vector<Double_t> &variablesOrigin, std::vector<TString> &variablesName_int, std::vector<Int_t> &variablesOrigin_int)
{
    std::cout << "reading varibleList: " << variableListCsv << "\n";
    std::ifstream fin(variableListCsv);
    std::string line;
    TString ivariable;
    while (getline(fin, line))
    {
        ivariable = line;
        if (line.size() > 0)
        {
            std::cout << "reading ivariable =" << ivariable << "\n";
            variablesName.push_back(ivariable);
            if (ivariable.Contains("number") || ivariable.Contains("num") || ivariable.Contains("charge"))
            {
                std::cout << "reading int ivariable =" << ivariable << "\n";
                variablesName_int.push_back(ivariable);
                variablesOrigin_int.push_back(0);
            }
            else
            {
                variablesForReader.push_back(0.0);
                variablesOrigin.push_back(0.0);
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
    readVariableList(variableList, variablesName, variablesForReader, variablesOrigin, variablesName_int, variablesOrigin_int);
    UInt_t variableNum = variablesName.size();
    for (UInt_t v = 0; v < variableNum; v++)
    {
        reader->AddVariable(variablesName[v], &variablesForReader[v]);
        //???it seems even for int type we have to add as float
    }
    TString methodName = "BDT" + TString(" method");
    TString weightfile = BDTTrainingMap[m_era].at(1) + "TMVAClassification" + TString("_") + "BDT" + TString(".weights.xml");
    reader->BookMVA(methodName, weightfile);

    // regions for hists
    std::vector<TString> regionsForVariables = {"1tau1lSR", "1tau1lPileupUp", "1tau1lPileupDown", "1tau1lPrefiringUp", "1tau1lPrefiringDown"};

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

    for (UInt_t i = 0; i < variablesOrigin.size(); i++)
    {
        m_tree->SetBranchAddress(variablesName[i], &variablesOrigin[i]);
    }
    for (UInt_t v = 0; v < variablesName_int.size(); v++)
    {
        m_tree->SetBranchAddress(variablesName_int[v], &variablesOrigin_int[v]);
    }
}

void treeAnalyzer::LoopTree()
{
    Long64_t allEvent = m_tree->GetEntries();
    if (m_isTest)
    {
        allEvent = 100;
    }
    std::cout << "looping over trees of " << allEvent << "\n";

    for (UInt_t e = 0; e < allEvent; e++)
    {
        m_tree->GetEntry(e);
        std::cout << tausT_number << "\n";
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