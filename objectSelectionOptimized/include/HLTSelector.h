#ifndef HLTSELECTOR_H
#define HLTSELECTOR_H

#include "eventReader_nano.h"

class HLTSelector
{
public:
    HLTSelector(TTree *outTree, const TString era, const TString processName, const Bool_t isData = kFALSE, const  Bool_t isRun3= kFALSE);
    ~HLTSelector(){};

    Bool_t SelectTauTri(const eventForNano *e, const Bool_t ifHLTSel=kFALSE);
    Bool_t SelectLepTri( eventForNano* e);
    Bool_t Select(eventForNano *e, const Bool_t isHLTSel = kTRUE);
    void clearBranch();

private:
    const TString m_era;
    const TString m_processName;
    const Bool_t m_isData;
    const Bool_t m_isRun3;
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
    Bool_t HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_ = kFALSE;
    Bool_t HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0_ = kFALSE;
    //dilepton triggers
    Bool_t HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ = kFALSE;
    Bool_t HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_ = kFALSE;
    Bool_t HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ = kFALSE;
    Bool_t HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ = kFALSE;


    // 2017
    Bool_t HLT_PFHT430_SixJet40_BTagCSV_p080_ = kFALSE;
    Bool_t HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_ = kFALSE;    // run<299329
    Bool_t HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_ = kFALSE; // run<=306460 2017 end
    Bool_t HLT_PFHT1050_ = kFALSE;
    Bool_t HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07_ = kFALSE;
    //2022
    Bool_t HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_ = kFALSE;
    Bool_t HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_ = kFALSE;
    Bool_t HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5_ = kFALSE;
    Bool_t HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5_ = kFALSE;
    Bool_t HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5_ = kFALSE;
    //
    Bool_t HLT_IsoMu24_ = kFALSE;//2018 and 2016
    Bool_t HLT_IsoMu27_ = kFALSE;//2017
    Bool_t HLT_Ele32_WPTight_Gsf_ = kFALSE;
    Bool_t HLT_Ele35_WPTight_Gsf = kFALSE; //only 2017
    Bool_t HLT_if2l = kFALSE;
    //2018

    //hadronic triggers
    // Bool_t HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_ = kFALSE;
    // Bool_t HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_ = kFALSE;
    // Bool_t HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_v_ = kFALSE;
};

#endif
