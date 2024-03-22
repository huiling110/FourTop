#ifndef OBJECTSELECTIONNANO_H
#define OBJECTSELECTIONNANO_H
// #include <iostream>
#include <any>

#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include <TTreeReaderValue.h>
#include <TH1D.h>

// #include "eventReader_nano.C"
#include "eventReader_nano.h" //use ttreeReader to construct event
#include "HLTSelector.h"
#include "usefulFunc.h"
#include "goodLumiAndPVSel.h"
#include "METfilter.h"
#include "eleTopMVASel.h"
#include "muTopMVASel.h"
#include "tauSel.h"
#include "jetSel.h"
#include "copyBranch.h"
#include "PUWeightCal.h"
#include "muMVASel.h"
#include "eleMVASel.h"
#include "systWeightCal.h"
#include "../../myLibrary/commenFunction.h"

class objectSelection
{
public:
    objectSelection(TString inputDir, TString singleFileName, TString outputDir, const Bool_t isData, const TString era, const TString processName, Bool_t isRun3, Bool_t m_isTest, const UChar_t eleScale = 0, const UChar_t eleSmear=0, const UChar_t JESSys =0) : m_isData{isData}, m_era{era}, m_processName{processName}, m_isRun3{isRun3}, m_eleScale{eleScale}, m_eleSmear{eleSmear}, m_JESSys{JESSys}
    {
        std::cout << "Initialize objectSelection class..................................\n";
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
            std::cout << "m_isData: " << m_isData << ";    m_era: " << m_era << "; m_isRun3="<<m_isRun3<<"  m_processName="<<m_processName<< "\n";
            std::cout<<"m_eleScale="<<m_eleScale<<" m_eleSmear="<<m_eleSmear<<"\n";
            std::cout<<"m_JESSys="<<m_JESSys<<"\n";

            m_cutflow->SetDirectory(m_output);
            CF_initial->SetDirectory(m_output);
            CF_met->SetDirectory(m_output);
            CF_HLT->SetDirectory(m_output);
            CF_pre->SetDirectory(m_output);
        }
        else
        {
            std::cout << "BAD!!! file not correctly open\n";
        }
        std::cout << "Done initializing objectSelection class................................\n";
        std::cout << "\n";
    };
    ~objectSelection();
    // osBase muonSelection(e, m_outTree);

    void Init();

    void EventLoop(const Bool_t preSelection = kTRUE, const Bool_t ifHLT= kTRUE, ULong_t numEntries = 0);

    void Terminate();
    void getLepEtaPhi(std::vector<Double_t> &lepEtaVec, std::vector<Double_t> &lepPhiVec);

private:
    TFile *m_input;
    TTree *m_tree;
    TTreeReader m_reader;
    eventForNano *e;
    TFile *m_output;
    TTree *m_outTree = new TTree("tree", "tree after object selection");
    Bool_t m_isData;
    TString m_era;
    Bool_t m_isRun3 = kFALSE;
    TString m_processName = "default";
    const UChar_t m_eleScale = 0;
    const UChar_t m_eleSmear = 0;
    const UChar_t m_JESSys = 0;
    const UChar_t m_TES = 3;

    LumiAndPVSel lumiAndPVSelection{m_isData, m_era, m_isRun3}; 
    METFilter metFilter{m_era, m_isRun3};                       //!!! for run3
    // osBase muonSelection{m_outTree};
    HLTSelector HLTselection{m_outTree, m_era};
    EleTopMVASel eleTopMVATSel{m_outTree, m_era, m_isRun3};
    MuSel muSel{m_outTree, m_era, m_isRun3, 2};//muons Tight for both run 2 and run 3
    // MuSel muSelT{m_outTree, m_era, m_isRun3, 3};
    EleMVASel eleMVASel{m_outTree, m_era,m_isData, m_isRun3, 2, m_eleScale, m_eleSmear };//!!!
    // EleMVASel eleMVASelT{m_outTree, m_era,m_isData, m_isRun3, 3, m_eleScale, m_eleSmear };//!!! for run3
    MuTopMVASel muTopMVATSel{m_outTree, m_era, m_isRun3};
    TauSel tauSel{m_outTree, m_era, m_isData, m_isRun3, 3, m_TES};
    TauSel tauSelF{m_outTree, m_era, m_isData, m_isRun3, 2, m_TES};
    TauSel tauSelL{m_outTree, m_era, m_isData, m_isRun3, 1, m_TES};
    JetSel jetSel{m_outTree, m_era, m_processName,  m_isRun3, m_isData, 0, m_JESSys};
    JetSel jetTSel{m_outTree, m_era, m_processName, m_isRun3, m_isData, 1, m_JESSys};
    JetSel bjetLSel{m_outTree, m_era,m_processName,  m_isRun3, m_isData, 11, m_JESSys};
    JetSel bjetMSel{m_outTree, m_era,m_processName,  m_isRun3, m_isData, 12, m_JESSys};
    JetSel bjetTSel{m_outTree, m_era, m_processName, m_isRun3, m_isData, 13, m_JESSys};
    JetSel bjetPNMSel{m_outTree, m_era, m_processName, m_isRun3, m_isData, 15, m_JESSys};
    JetSel bjetPTMSel{m_outTree, m_era, m_processName, m_isRun3, m_isData, 17, m_JESSys};
    CopyBranch copyBranch{m_outTree, m_isRun3};
    PUWeightCal puWeightCal{m_outTree, m_isData, m_era, m_isRun3};
    SystWeightCal systWeightCal{m_outTree, m_isData};

    ULong_t m_elesTotal = 0;
    ULong_t m_musTotal = 0;
    ULong_t m_tausTotal = 0;
    ULong_t m_tausFTotal = 0;
    ULong_t m_tausLTotal = 0;
    ULong_t m_jetsTotal = 0;
    ULong_t m_bjetsM = 0;

    TH1D *m_cutflow = new TH1D("OScutflow", "initial: Met: HLT: preSelection", 4, 0, 4);
    TH1D *CF_initial = new TH1D("OS_initial", "OS_initial", 2, -1, 1);
    TH1D *CF_met = new TH1D("OS_MetFilter", "OS_MetFilter", 2, -1, 1);
    TH1D *CF_HLT = new TH1D("OS_HLT", "OS_HLT", 2, -1, 1);
    TH1D *CF_pre = new TH1D("OS_preSlection", "OS_preSelection", 2, -1, 1);
};

#endif