#ifndef COPYBRANCHES_H
#define COPYBRANCHES_H

#include "eventReader_forMV.h"

class CopyBranches
{
public:
    CopyBranches(TTree *outTree);
    ~CopyBranches();
    void makeVariables(EventForMV *e);
    void clearBranch();
    void reportEntry(TString className);

private:
    ULong_t m_entry = 0;
    // output branches
    Int_t PV_npvsGood;
    //HLT
    Bool_t HLT_PFHT450_SixJet40_BTagCSV_p056 = kFALSE;
    Bool_t HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = kFALSE;
    Bool_t HLT_PFJet450 = kFALSE;
    Bool_t HLT_IsoMu24 = kFALSE;
    Bool_t HLT_IsoMu27 = kFALSE;
    Bool_t HLT_PFJet500 = kFALSE;
    Bool_t HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = kFALSE;
    Bool_t HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = kFALSE;
    Bool_t HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = kFALSE;
    Bool_t HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 = kFALSE;
    Bool_t HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 = kFALSE;
    Bool_t HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 = kFALSE;
    // 2017
    Bool_t HLT_PFHT430_SixJet40_BTagCSV_p080 = kFALSE;
    Bool_t HLT_PFHT380_SixJet32_DoubleBTagCSV_p075 = kFALSE;
    Bool_t HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 = kFALSE;
    Bool_t HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0 = kFALSE;
    //2022
    Bool_t HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59 = kFALSE;
    Bool_t HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94 = kFALSE;
    Bool_t HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5 = kFALSE;
    Bool_t HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5 = kFALSE;
    Bool_t HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5 =kFALSE;


    //
    Double_t MET_pt = -99;
    Double_t MET_phi = -99;

    std::vector<Double_t> jets_pt_;
    std::vector<Double_t> jets_eta_;
    std::vector<Double_t> jets_btags_;
    std::vector<Double_t> jets_btagsPN_;
    std::vector<Double_t> jets_btagsPT_;
    std::vector<Int_t> jets_flavour_;
};

#endif