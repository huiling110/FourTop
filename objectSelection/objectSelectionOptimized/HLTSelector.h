#ifndef HLTSELECTOR_H
#define HLTSELECTOR_H

#include "eventReader_nano.h"

class HLTSelector
{
public:
    // HLTSelector(TTree *outTree) : m_outTree{outTree}
    HLTSelector(TTree *outTree);
    ~HLTSelector(){};

    Bool_t Select(eventForNano *e, const TString era = "2017", const Bool_t isData = kFALSE, Bool_t isHLTSel = kTRUE);
    void clearBranch();

private:
    // TTree *m_outTree;
    // output branches
    Bool_t HLT_PFHT450_SixJet40_BTagCSV_p056_ = kFALSE;
    Bool_t HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ = kFALSE;
    Bool_t HLT_PFJet450_ = kFALSE;
    Bool_t HLT_PFJet500_ = kFALSE;
    Bool_t HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ = kFALSE;
    Bool_t HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = kFALSE;
    // TRIGGERS FOR 2018 data A
    Bool_t HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = kFALSE;
    Bool_t HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_ = kFALSE;
    Bool_t HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ = kFALSE;
    // 2017
    Bool_t HLT_PFHT430_SixJet40_BTagCSV_p080_ = kFALSE;
    Bool_t HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_ = kFALSE;    // run<299329
    Bool_t HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_ = kFALSE; // run<=306460 2017 end
};

#endif
