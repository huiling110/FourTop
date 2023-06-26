#ifndef MAKEVARIABLESMAIN_H
#define MAKEVARIABLESMAIN_H
// #include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include <TTreeReaderValue.h>
#include <TH1D.h>
#include <TChain.h>

#include "eventReader_forMV.h" //use ttreeReader to construct event
// #include "muonVarMaker.h"
#include "objVarMaker.h"
#include "eleVarMaker.h"
#include "tauVarMaker.h"
#include "jetVarMaker.h"
#include "copyBranches.h"
#include "weightVarMaker.h"
#include "../../myLibrary/commenFunction.h"

class MakeVariablesMain
{
public:
    // MakeVariablesMain(TString inputDir, TString singleFileName, TString outputDir, const Bool_t isData, const TString era, Bool_t m_isTest) : m_isData{isData}, m_era{era}
    MakeVariablesMain(TString inputDir, TChain *chain, TString outDir, TString processName) : m_inputDir{inputDir}, m_reader(chain), m_processName{processName}
    {
        std::cout << "Initialize MakeVariablesMain class..................................\n";
        // m_input = new TFile(inputDir + singleFileName, "READ");
        // if (!m_input->IsZombie())
        // {
        // set up input and event object
        // TChain chain("tree");
        // chain.Add(inputDir + "outTree*.root");
        // std::cout<<"all entries in chain: "<<chain.GetEntries()<<"\n";
        // m_reader.SetChain(chain);
        e = new EventForMV(m_reader);

        // set up output
        m_output = new TFile(outDir + m_processName + ".root", "RECREATE");
        m_outTree->SetDirectory(m_output);
        m_cutflow->SetDirectory(m_output);
        m_isData = TTTT::getIsData(m_inputDir);
        m_era = TTTT::getEra(m_inputDir);
        std::cout << "m_isData=" << m_isData << "  m_era=" << m_era << "\n";

        std::cout << "Done initializing MakeVariablesMain class................................\n";
        std::cout << "\n";
    };
    ~MakeVariablesMain();

    void Init();

    void EventLoop(Bool_t preSelection = kTRUE, ULong_t numEntries = 1000);
    void Terminate();
    void getLepEtaPhi(std::vector<Double_t> &lepEtaVec, std::vector<Double_t> &lepPhiVec);

private:
    TString m_inputDir;
    TTreeReader m_reader;
    EventForMV *e;
    TString m_processName;
    TFile *m_output;
    TTree *m_outTree = new TTree("newtree", "tree for BDT");
    Bool_t m_isData = kFALSE;
    TString m_era;
    TH1D *m_cutflow = new TH1D("cutflowforMV", "initial; baseline", 2, 0, 2);

    //
    // MuonVarMaker muVarMaker{m_outTree};
    ObjVarMaker muVarMaker{m_outTree, "muonsT"};
    EleVarMaker eleVarMaker{m_outTree, "eleMVAT", 0};
    EleVarMaker eleTopVarMaker{m_outTree, "eleTopMVAT", 1};
    TauVarMaker tauVarMaker{m_outTree, "tausT"};
    TauVarMaker tauFVarMaker{m_outTree, "tausF", 1};
    TauVarMaker tauLVarMaker{m_outTree, "tausL", 2};
    JetVarMaker jetVarMaker{m_outTree, "jets", 0};
    JetVarMaker jetTVarMaker{m_outTree, "jetsT", 1};
    JetVarMaker bjetMVarMaker{m_outTree, "bjetsM", 2};
    JetVarMaker bjetLVarMaker{m_outTree, "bjetsL", 3};
    JetVarMaker bjetTVarMaker{m_outTree, "bjetsT", 4};

    CopyBranches copyBranches{m_outTree};
    WeightVarMaker weightVarMaker{m_outTree};
};

#endif