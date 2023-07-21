#ifndef WRITEHIST_BTAGEFF_H
#define WRITEHIST_BTAGEFF_H

#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>

#include "myEventClass.h"

class WriteHist_btagEff
{
private:
    TString m_inputDir;
    TString m_processName;
    Bool_t m_isTest = kTRUE;
    TTree *m_tree;
    TFile *m_file;
    TString m_era = "2016";
    Bool_t m_isRun3 = kFALSE;
    Bool_t m_isData = kFALSE;
    TString m_outputFolder;
    TFile *m_outFile;
    event *e;

    TH2D* m_h2D_jets_ptEta_b = new TH2D("jets_ptEta_genB", "jets_ptEta_genB", 10, 40., 700., 10, 0, 2.4);//maybe should have the same binnig as that of SF provided by BTV
    TH2D* m_h2D_jets_ptEta_c = new TH2D("jets_ptEta_genC", "jets_ptEta_genC", 10, 40., 700., 10, 0, 2.4);//maybe should have the same binnig as that of SF provided by BTV
    TH2D* m_h2D_jets_ptEta_l = new TH2D("jets_ptEta_genL", "jets_ptEta_genL", 10, 40., 700., 10, 0, 2.4);//maybe should have the same binnig as that of SF provided by BTV
    TH2D* m_h2D_jets_ptEta_b_nu = new TH2D("jets_ptEta_genB_nu", "jets_ptEta_genB_nu", 10, 40., 700., 10, 0, 2.4);
    TH2D* m_h2D_jets_ptEta_c_nu = new TH2D("jets_ptEta_genC_nu", "jets_ptEta_genC_nu", 10, 40., 700., 10, 0, 2.4);
    TH2D* m_h2D_jets_ptEta_l_nu = new TH2D("jets_ptEta_genL_nu", "jets_ptEta_genL_nu", 10, 40., 700., 10, 0, 2.4);


public:
    
WriteHist_btagEff(const TString inputDir, const TString process, TString outVersion = "v0", Bool_t isTest = kTRUE); 
    ~WriteHist_btagEff();
void Init();
void LoopTree();
void Terminate();
};




#endif