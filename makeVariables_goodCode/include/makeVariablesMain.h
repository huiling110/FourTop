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
#include "bjetVarMaker.h"
#include "copyBranches.h"
#include "weightVarMaker.h"
#include "createHists.h"
#include "../../myLibrary/commenFunction.h"

class MakeVariablesMain
{
public:
    // MakeVariablesMain(TString inputDir, TChain *chain, TString outDir, TString processName) : m_inputDir{inputDir}, m_reader(chain), m_processName{processName}
    MakeVariablesMain(TString inputDir, TString outDir, TString processName, Bool_t isData, TString era, Bool_t isRun3) : m_inputDir{inputDir}, m_processName{processName}, m_isData{isData}, m_era{era}, m_isRun3{isRun3}
    {
        std::cout << "Initialize MakeVariablesMain class..................................\n";
        std::cout << "m_isData=" << m_isData << "  m_era=" << m_era << "  m_isRun3=" << m_isRun3 << "\n";

        std::cout<<"inputDir="<<inputDir<<"\n";
        TChain *chain1 = new TChain("tree");
        if(m_isRun3){
            chain1->Add(inputDir + "tree*.root");
        }else{
            chain1->Add(inputDir + "outTree*.root");
        }
        std::cout << "all entries in chain: " << chain1->GetEntries() << "\n";
        std::cout << "all trees in chain: " << chain1->GetNtrees() << "\n";
        m_reader.SetTree(chain1);

        e = new EventForMV(m_reader);

        // set up output
        m_output = new TFile(outDir + m_processName + ".root", "RECREATE");
        m_outTree->SetDirectory(m_output);
        m_cutflow->SetDirectory(m_output);

        //
        createHist = CreateHist(m_output);

        std::cout << "Done initializing MakeVariablesMain class................................\n";
        std::cout << "\n";
    };
    ~MakeVariablesMain();

    void Init();

    void EventLoop(Bool_t preSelection = kTRUE, Bool_t tau1e1Sel=kFALSE, ULong_t numEntries = 1000);
    void Terminate();
    void getLepEtaPhi(std::vector<Double_t> &lepEtaVec, std::vector<Double_t> &lepPhiVec);

private:
    TString m_inputDir;
    TString m_processName;
    // m_isData, m_era and m_isRun3 should be properly initialized from beginning, because other classes depend on it
    const Bool_t m_isData;
    const TString m_era;
    const Bool_t m_isRun3;
    TTreeReader m_reader;
    EventForMV *e;
    TFile *m_output;
    TTree *m_outTree = new TTree("newtree", "tree for BDT");
    TH1D *m_cutflow = new TH1D("cutflowforMV", "initial; baseline", 2, 0, 2);

    //
    // MuonVarMaker muVarMaker{m_outTree};
    ObjVarMaker muVarMaker{m_outTree, "muonsT", 0};
    ObjVarMaker muTopTVarMaker{m_outTree, "muonsTopMVAT", 1};
    EleVarMaker eleVarMaker{m_outTree, "elesMVAT", 0};
    EleVarMaker eleTopVarMaker{m_outTree, "elesTopMVAT", 1};
    TauVarMaker tauVarMaker{m_outTree, "tausT"};
    TauVarMaker tauFVarMaker{m_outTree, "tausF", 1};
    TauVarMaker tauLVarMaker{m_outTree, "tausL", 2};
    TauVarMaker tauTTVarMaker{m_outTree, "tausTT", 3};
    TauVarMaker tauTTTVarMaker{m_outTree, "tausTTT", 4};
    TauVarMaker tauMVarMaker{m_outTree, "tausM", 5};

    JetVarMaker jetVarMaker{m_outTree, "jets", 0};
    // JetVarMaker jetTVarMaker{m_outTree, "jetsT", 1};
    // JetVarMaker bjetMVarMaker{m_outTree, "bjetsM", 2};
    // JetVarMaker bjetLVarMaker{m_outTree, "bjetsL", 3};
    // JetVarMaker bjetTVarMaker{m_outTree, "bjetsT", 4};
    // JetVarMaker bjetPNMVarMaker{m_outTree, "bjetsPNM", 5};
    BjetVarMaker bjetMVarMaker{m_outTree, "bjetsM", 0};
    BjetVarMaker bjetLVarMaker{m_outTree, "bjetsL", 1};
    BjetVarMaker bjetTVarMaker{m_outTree, "bjetsT", 2};
    BjetVarMaker bjetPNMVarMaker{m_outTree, "bjetsPNM", 3};
    BjetVarMaker bjetPTMVarMaker{m_outTree, "bjetsPTM", 4};
    BjetVarMaker bjetPTTVarMaker{m_outTree, "bjetsPTT", 5};

    CopyBranches copyBranches{m_outTree};
    // CreateHist createHists{m_output};
    CreateHist createHist; //cannot initialize here because m_output not properly initialzided yet
    WeightVarMaker weightVarMaker{m_outTree, m_era, m_isData, m_isRun3};
};

#endif