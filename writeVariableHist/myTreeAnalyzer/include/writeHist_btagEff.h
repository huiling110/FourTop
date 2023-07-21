#ifndef WRITEHIST_BTAGEFF_H
#define WRITEHIST_BTAGEFF_H

#include <TString.h>
#include <TFile.h>
#include <TTree.h>

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
public:
    
WriteHist_btagEff(const TString inputDir, const TString process, TString outVersion = "v0", Bool_t isTest = kTRUE); 
    ~WriteHist_btagEff();
};




#endif