#ifndef WEIGHTVARMAKER_H
#define WEIGHTVARMAKER_H

#include <TH2D.h>
#include <TH1D.h>
#include "correction.h"

#include "eventReader_forMV.h"


class WeightVarMaker
{
public:
    WeightVarMaker(TTree *outTree, TString era, Bool_t isData);
    ~WeightVarMaker();
    void makeVariables(EventForMV *e);
    void clearBranch();

private:
    // output branches
    Double_t EVENT_prefireWeight;
    Double_t EVENT_prefireWeight_up;
    Double_t EVENT_prefireWeight_down;
    Double_t EVENT_genWeight;
    Double_t PUweight_;
    Double_t PUweight_up_;
    Double_t PUweight_down_;
    Double_t btagEfficiency_weight;
    Double_t muonIDSF_weight;
    Double_t muonIDSF_weight_up;
    Double_t muonIDSF_weight_down;
    Double_t mounTrackerSF_weight;
    Double_t eleMVAT_IDSF_weight;
    Double_t eleMVAT_IDSF_weight_up;
    Double_t eleMVAT_IDSF_weight_down;
    Double_t eleMVAT_IDSF_weight_backup;
    Double_t elesTopMVAT_weight;
    Double_t elesTopMVAT_weight_up;
    Double_t elesTopMVAT_weight_down;
    Double_t musTopMVAT_weight;
    Double_t musTopMVAT_weight_up;
    Double_t musTopMVAT_weight_down;
    Double_t tauT_IDSF_weight;
    Double_t tauT_IDSF_weight_new;
    Double_t tauT_IDSF_weight_new_vsjet_up;
    Double_t tauT_IDSF_weight_new_vsjet_down;
    Double_t tauT_IDSF_weight_new_vsmu_up;
    Double_t tauT_IDSF_weight_new_vsmu_down;
    Double_t tauT_IDSF_weight_new_vsele_up;
    Double_t tauT_IDSF_weight_new_vsele_down;
    Double_t btagShape_weight = 1.0;

    Double_t btagShape_weight_jes_up = 1.0;
    Double_t btagShape_weight_jes_down = 1.0;
    Double_t btagShape_weight_hf_up = 1.0;
    Double_t btagShape_weight_hf_down = 1.0;
    Double_t btagShape_weight_lf_up = 1.0;
    Double_t btagShape_weight_lf_down = 1.0;
    Double_t btagShape_weight_hfstats1_up = 1.0;
    Double_t btagShape_weight_hfstats1_down = 1.0;
    Double_t btagShape_weight_hfstats2_up = 1.0;
    Double_t btagShape_weight_hfstats2_down = 1.0;
    Double_t btagShape_weight_lfstats1_up = 1.0;
    Double_t btagShape_weight_lfstats1_down = 1.0;
    Double_t btagShape_weight_lfstats2_up = 1.0;
    Double_t btagShape_weight_lfstats2_down = 1.0;
    Double_t btagShape_weight_cferr1_up = 1.0;
    Double_t btagShape_weight_cferr1_down = 1.0;
    Double_t btagShape_weight_cferr2_up = 1.0;
    Double_t btagShape_weight_cferr2_down = 1.0;

    Double_t btagShapeR = 1.0;
    Double_t HLT_weight = 1.0;
    Double_t HLT_weight_stats_up = 1.0;
    Double_t HLT_weight_stats_down = 1.0;

    TString m_era;
    const Bool_t m_isData;
    TH2D *eleIDSF_topMVA;
    TH2D *muIDSF_topMVA;

    std::unique_ptr<correction::CorrectionSet> cset;
    std::unique_ptr<correction::CorrectionSet> cset_btag;
    TH1D *btagRHist;


};

#endif