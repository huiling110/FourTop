#ifndef HLTSELECTOR_H
#define HLTSELECTOR_H

#include "eventReader_nano.h"

class HLTSelector
{
public:
    HLTSelector(TTree *outTree) : m_outTree{outTree}
    {
        m_outTree->Branch("HLT_PFHT450_SixJet40_BTagCSV_p056_", &HLT_PFHT450_SixJet40_BTagCSV_p056_);
    };
    ~HLTSelector(){

    };
    // init(){

    // };
    void Select(const eventForNano *e, const TString era = "2017")
    {
        clearBranch();

        // if (!(e->HLT_PFHT450_SixJet40_BTagCSV_p056->IsValid()))
        // {
        // }

        m_outTree->Fill();
    };
    void clearBranch()
    {
        // HLT_PFHT450_SixJet40_BTagCSV_p056_.clear();
    }
    // void

private:
    TTree *m_outTree;
    // output branches
    Bool_t HLT_PFHT450_SixJet40_BTagCSV_p056_;
};

#endif
