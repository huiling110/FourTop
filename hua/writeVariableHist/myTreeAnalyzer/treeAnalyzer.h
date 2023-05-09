#ifndef TREEANALYZER_H
#define TREEANALYZER_H

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

class treeAnalyzer
{
public:
    treeAnalyzer(TString inputFile, TString treeName, Bool_t isTest = kTRUE) : m_isTest{isTest}
    {
        m_file = new TFile(inputFile, "READ");
        m_tree = (TTree *)m_file->Get(treeName);
    };
    ~treeAnalyzer();

    void Init();
    void LoopTree();
    Bool_t eventCut();
    void Terminate();

private:
    TTree *m_tree;
    TFile *m_file;
    TString m_processName;
    TString m_era;
    Bool_t m_isTest = kTRUE;
};

#endif