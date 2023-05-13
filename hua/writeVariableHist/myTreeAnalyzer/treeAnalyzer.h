#ifndef TREEANALYZER_H
#define TREEANALYZER_H

#include <iostream>
#include <vector>
#include <variant>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TMVA/Reader.h"

#include "histsForRegionsMap_class.h"
#include "functions.h"

#include "myEventClass.C"

class treeAnalyzer
{
public:
    treeAnalyzer(const TString inputFile, TString treeName, TString outputFolder = "./", TString outVersion = "v0", Bool_t isTest = kTRUE) : m_input{inputFile}, m_outputFolder{outputFolder}, m_isTest{isTest}
    {
        m_file = new TFile(inputFile, "READ"); //???what is this initialization
        if (!m_file || m_file->IsZombie())
        {
            std::cout << "Error: could not open file!" << m_file->GetName() << std::endl;
        }
        else
        {
            std::cout << "input file: " << m_file->GetName() << "\n";
            m_tree = (TTree *)m_file->Get(treeName);
        }

        m_era = getEra(inputFile);
        m_isData = getIsData(inputFile);
        std::cout << "m_era=" << m_era << " m_isData=" << m_isData << "\n";

        m_processName = inputFile(inputFile.Last('/') + 1, inputFile.Sizeof());
        m_processName = m_processName(0, m_processName.First('.'));
        std::cout << "m_processName: " << m_processName << "\n";
        m_outFile = new TFile(m_outputFolder + "variableHists" + "_" + outVersion + "/" + m_processName + ".root", "RECREATE");

        e = new event(m_tree);
    };
    ~treeAnalyzer();

    void Init();
    void LoopTree();
    void readBranch();
    // Bool_t eventCut(event);
    void Terminate();

private:
    TString m_input;
    TTree *m_tree;
    TFile *m_file;
    TString m_processName;
    TString m_era = "2016";
    Bool_t m_isTest = kTRUE;
    Bool_t m_isData = kFALSE;
    TString m_outputFolder;
    TFile *m_outFile;
    event *e;

    // for TMVA reader
    TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");
    std::vector<TString> variablesName{};
    std::vector<Float_t> variablesForReader;
    std::vector<std::variant<Int_t, Double_t>> variablesOriginAll;

    // hists regions
    histsForRegionsMap SR1tau1lSys; // calls for default constructor

    // branch values;
    // maybe define a class myTreeReader for reading branches
    // myTreeReader(TTree*)
    // Int_t tausT_number, leptonsMVAT_number, jets_number, bjetsM_num, leptonsMVAT_2OS, elesTopMVAT_number, muonsTopMVAT_number;
    // Double_t jets_HT, jets_6pt;
    // Double_t EVENT_genWeight, EVENT_prefireWeight, EVENT_prefireWeight_up, EVENT_prefireWeight_down, PUweight_, PUweight_up_, PUweight_down_, HLT_weight, tauT_IDSF_weight_new, elesTopMVAT_weight, musTopMVAT_weight, btagShape_weight, btagShapeR;
    // Double_t tauT_IDSF_weight_new_vsjet_up;
    // Double_t tauT_IDSF_weight_new_vsjet_down;
    // Double_t elesTopMVAT_weight_up;
    // Double_t elesTopMVAT_weight_down;
    // Double_t musTopMVAT_weight_up;
    // Double_t musTopMVAT_weight_down;
};

#endif