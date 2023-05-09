#include <iostream>

#include "treeAnalyzer.h"

void treeAnalyzer::Init()
{
    std::cout << "start to initilation\n";
    // m_outFile = new TFile(m_outputFolder + "variableHists" + "_" + m_version + "/" + m_processName + ".root", "RECREATE");
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