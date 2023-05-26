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
    Bool_t Select(const eventForNano *e, const TString era = "2017")
    {
        clearBranch();
        Bool_t ifPass = kTRUE;
        // the HLT branch pointer null pointer is not exist in a file
        if (era.CompareTo("2016preVFP") == 0 || era.CompareTo("2016postVFP") == 0)
        {
            ifPass = **e->HLT_PFHT450_SixJet40_BTagCSV_p056 || **e->HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 || **e->HLT_PFJet450;
            // ifPass = **(e->HLT_PFJet450);
        }

        // m_outTree->Fill(); //??? should we fill in every Selector or no need?
        // inconsistent fill could cause strange things

        return ifPass;
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
