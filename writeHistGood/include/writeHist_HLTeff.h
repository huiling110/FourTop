#ifndef WRITEHIST_HLTEFF_H
#define WRITEHIST_HLTEFF_H

#include <iterator>

#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>

#include "myEventClass.h"

class WH_HLTeff
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


public:
    WH_HLTeff(const TString inputDir, const TString process, TString outVersion = "v0", Bool_t isTest = kTRUE);
    ~WH_HLTeff();
    void Init();
    void LoopTree(UInt_t entry = 1000);
    void Terminate();
};

#endif