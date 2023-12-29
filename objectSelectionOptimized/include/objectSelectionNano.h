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
    objectSelection(TString inputDir, TString singleFileName, TString outputDir, const Bool_t isData, const TString era, Bool_t isRun3, Bool_t m_isTest) : m_isData{isData}, m_era{era}, m_isRun3{isRun3}
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
            TString temp = inputDir(0, inputDir.Last('/'));
            m_processName = temp(temp.Last('/')+1, temp.Length()-temp.Last('/'));

            // set up output
            TString outName = outputDir + singleFileName;
            m_output = new TFile(outName, "RECREATE");
            m_outTree->SetDirectory(m_output);

            // set up
            std::cout << "m_isData: " << m_isData << ";    m_era: " << m_era << "; m_isRun3="<<m_isRun3<<"  m_processName="<<m_processName<< "\n";

            //
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

    void EventLoop(const Bool_t preSelection = kTRUE, const Bool_t ifHLT= kTRUE, ULong_t numEntries = 0, const Int_t tauTES = 0, const Int_t ifJER = 0, const Int_t sysJEC = 0);

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

    LumiAndPVSel lumiAndPVSelection{m_isData, m_era, m_isRun3}; //!!!
    METFilter metFilter{m_era, m_isRun3};                       //!!! for run3
    // osBase muonSelection{m_outTree};
    // HLTSelector HLTselection{m_outTree};
    EleTopMVASel eleTopMVATSel{m_outTree, m_era, m_isRun3};
    MuSel muSel{m_outTree, m_era, m_isRun3, 2};
    EleMVASel eleMVASel{m_outTree, m_era, m_isRun3};
    MuTopMVASel muTopMVATSel{m_outTree, m_era, m_isRun3};
    TauSel tauSel{m_outTree, m_era, m_isRun3, 3};
    TauSel tauSelF{m_outTree, m_era, m_isRun3, 2};
    TauSel tauSelL{m_outTree, m_era, m_isRun3, 1};
    JetSel jetSel{m_outTree, m_era, m_isRun3, 0};
    // JetSel jetTSel{m_outTree, m_era, 1};
    // JetSel bjetLSel{m_outTree, m_era, 11};
    // JetSel bjetMSel{m_outTree, m_era, 12};
    // JetSel bjetTSel{m_outTree, m_era, 13};
    CopyBranch copyBranch{m_outTree, m_isRun3};
    // PUWeightCal puWeightCal{m_outTree, m_isData, m_era, m_isRun3};
    // SystWeightCal systWeightCal{m_outTree, m_isData};

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