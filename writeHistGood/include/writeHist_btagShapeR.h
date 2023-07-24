#ifndef WriteHist_btagShapeR_H
#define WriteHist_btagShapeR_H

#include <iterator>

#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>

#include "myEventClass.h"

class WriteHist_btagShapeR
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

    // Double_t bins[9] = {25., 50., 70., 100., 140., 200., 300., 600., 1000};
    // Double_t binsEta[3] = {0, 1.5, 2.4};
    TH1D *jets_num_de = new TH1D("jets_num_de", "n^{jet}", 5, 5.5, 12.5);
    TH1D *jets_num_nu = new TH1D("jets_num_nu", "n^{jet}", 5, 5.5, 12.5);

public:
    WriteHist_btagShapeR(const TString inputDir, const TString process, TString outVersion = "v0", Bool_t isTest = kTRUE);
    ~WriteHist_btagShapeR();
    void Init();
    void LoopTree();
    void Terminate();
};

#endif