#ifndef TREEANALYZER_H
#define TREEANALYZER_H

#include <iostream>
#include <vector>
#include <variant>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH1D.h"
#include "TMVA/Reader.h"

#include "histsForRegionsMap_class.h"
#include "functions.h"

#include "myEventClass.h"

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
    TH1D *cutFlowHist = new TH1D("cutFlow", "cutFlow", 3, 0, 3);
    event *e;

    // for TMVA reader
    TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");
    std::vector<TString> variablesName{};
    std::vector<Float_t> variablesForReader;
    std::vector<std::variant<Int_t, Double_t>> variablesOriginAll;

    // hists regions
    histsForRegionsMap SR1tau1lSys; // calls for default constructor
};

#endif