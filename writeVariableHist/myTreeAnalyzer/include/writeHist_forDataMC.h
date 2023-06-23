#ifndef WH_FORDATAMC_H
#define WH_FORDATAMC_H

#include <iostream>
#include <vector>
#include <variant>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH1D.h"

#include "histsForRegionsMap_class.h"
#include "functions.h"
#include "../../myLibrary/commenFunction.h"

#include "myEventClass.h"

class WH_forDataMC
{
public:
    WH_forDataMC(const TString inputDir, const TString process, TString outVersion = "v0", Int_t channel=0, Bool_t isTest = kTRUE) : m_inputDir{inputDir}, m_processName{process}, m_channel{channel}, m_isTest{isTest}
    {
        m_file = new TFile(m_inputDir + m_processName + ".root", "READ"); //???what is this initialization
        if (!m_file || m_file->IsZombie())
        {
            std::cout << "Error: could not open file!" << m_file->GetName() << std::endl;
        }
        else
        {
            std::cout << "input file: " << m_file->GetName() << "\n";
            m_tree = (TTree *)m_file->Get("newtree");
        }

        m_era = getEra(m_inputDir);
        m_isData = getIsData(m_inputDir);
        std::cout << "m_era=" << m_era << " m_isData=" << m_isData << "  m_isTest=" << m_isTest << "\n";

        std::cout << "m_processName: " << m_processName <<"  m_channel: "<<m_channel<< "\n";
        m_outFile = new TFile(m_inputDir + "variableHists" + "_" + outVersion + "/" + m_processName + ".root", "RECREATE");

        e = new event(m_tree);
    };
    ~WH_forDataMC();

    void Init();
    void LoopTree();
    void Terminate();

private:
    TString m_inputDir;
    TString m_processName;
    Int_t m_channel;
    Bool_t m_isTest = kTRUE;
    TTree *m_tree;
    TFile *m_file;
    TString m_era = "2016";
    Bool_t m_isData = kFALSE;
    TString m_outputFolder;
    TFile *m_outFile;
    // TH1D *cutFlowHist = new TH1D("cutFlow", "cutFlow", 3, 0, 3);
    event *e;

    // hists regions
    histsForRegionsMap SR1tau1lSys; // calls for default constructor
};

#endif