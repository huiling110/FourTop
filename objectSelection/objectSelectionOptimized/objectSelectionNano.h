#ifndef OBJECTSELECTIONNANO_H
#define OBJECTSELECTIONNANO_H
// #include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include <TTreeReaderValue.h>
#include <TH1D.h>

// #include "eventReader_nano.C"
#include "eventReader_nano.h" //use ttreeReader to construct event
// #include "muonSelector.h"
#include "HLTSelector.h"
#include "usefulFunc.h"
#include "goodLumiAndPVSel.h"
#include "METfilter.h"
#include "eleTopMVASel.h"
#include "muTopMVASel.h"
#include "tauSel.h"

class objectSelection
{
public:
    // objectSelection(TString inputFile, TString outputDir)
    // objectSelection(TString inputDir, TString singleFileName, TString outputDir, Bool_t m_isTest)
    objectSelection(TString inputDir, TString singleFileName, TString outputDir, const Bool_t isData, const TString era, Bool_t m_isTest) : m_isData{isData}, m_era{era}
    {
        std::cout << "initialize objectSelection class..................................\n";
        // m_input = new TFile(inputFile, "READ");
        m_input = new TFile(inputDir + singleFileName, "READ");
        if (!m_input->IsZombie())
        {
            std::cout << "input file: " << m_input->GetName() << "\n";
            m_tree = (TTree *)m_input->Get("Events");
            // e = new eventForNano{m_tree};
            // m_reader = TTreeReader(m_tree);
            m_reader.SetTree(m_tree);
            e = new eventForNano(m_reader);

            // set up output
            TString outName = outputDir + singleFileName;
            m_output = new TFile(outName, "RECREATE");
            m_outTree->SetDirectory(m_output);

            // set up
            // m_isData = getIsData(inputDir);
            // m_era = getEra(inputDir);
            std::cout << "m_isData: " << m_isData << ";    m_era: " << m_era << "\n";
        }
        else
        {
            std::cout << "BAD!!! file not correctly open\n";
        }
        std::cout << "done initializing objectSelection class................................\n";
    };
    ~objectSelection();
    // osBase muonSelection(e, m_outTree);

    void Init();

    void EventLoop();
    void Terminate();
    void getLepEtaPhi(std::vector<Double_t> &lepEtaVec, std::vector<Double_t> &lepPhiVec);

private:
    TFile *m_input;
    TTree *m_tree;
    TTreeReader m_reader;
    eventForNano *e;
    TFile *m_output;
    TTree *m_outTree = new TTree("tree", "tree after object selection");
    TH1D *h_forEY_initial = new TH1D("h_initial", "h_initial", 2, -1, 1);
    TH1D *h_forEY_HLT = new TH1D("h_afterHLT", "h_afterHLT", 2, -1, 1);
    TH1D *h_forEY_preSelection = new TH1D("h_afterpreSelection", "h_afterpreSelection", 2, -1, 1);
    Bool_t m_isData;
    TString m_era;

    LumiAndPVSel lumiAndPVSelection{m_isData, m_era};
    METFilter metFilter{};
    // osBase muonSelection{m_outTree};
    HLTSelector HLTselection{m_outTree};
    EleTopMVASel eleTopMVATSel{m_outTree, m_era};
    MuTopMVASel muTopMVATSel{m_outTree, m_era};
    TauSel tauSel{m_outTree, m_era};
    TauSel tauSelF{m_outTree, m_era, 2};
    TauSel tauSelL{m_outTree, m_era, 1};

    TH1D *m_cutflow = new TH1D("cutflowOS", "initial: Met: HLT: preSelection", 4, 0, 4);
};

#endif