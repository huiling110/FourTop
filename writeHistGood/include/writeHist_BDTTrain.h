#ifndef WRITEHIST_BDTTRAIN_H
#define WRITEHIST_BDTTRAIN_H

#include <iterator>

#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>

#include "myEventClass.h"
#include "histsForRegionsMap_class.h"

class WH_BDTTrain
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

    std::vector<std::shared_ptr<histForRegionsBase>> histsForRegion_vec;



public:
    WH_BDTTrain(const TString inputDir, const TString process, TString outVersion = "v0", Bool_t isTest = kTRUE);
    ~WH_BDTTrain();
    void Init();
    void LoopTree(UInt_t entry = 1000);
    void Terminate();
};

#endif