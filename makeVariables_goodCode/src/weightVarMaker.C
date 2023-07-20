
#include "../include/weightVarMaker.h"

WeightVarMaker::WeightVarMaker(TTree *outTree)
{
    std::cout << "Initializing WeightVarMaker.....\n";

    outTree->Branch("EVENT_prefireWeight", &EVENT_prefireWeight);
    outTree->Branch("EVENT_prefireWeight_up", &EVENT_prefireWeight_up);
    outTree->Branch("EVENT_prefireWeight_down", &EVENT_prefireWeight_down);
    outTree->Branch("EVENT_genWeight", &EVENT_genWeight);
    outTree->Branch("PUweight_", &PUweight_);
    outTree->Branch("PUweight_up_", &PUweight_up_);
    outTree->Branch("PUweight_down_", &PUweight_down_);
    outTree->Branch("btagEfficiency_weight", &btagEfficiency_weight);
    outTree->Branch("muonIDSF_weight", &muonIDSF_weight);
    outTree->Branch("muonIDSF_weight_up", &muonIDSF_weight_up);
    outTree->Branch("muonIDSF_weight_down", &muonIDSF_weight_down);
    outTree->Branch("mounTrackerSF_weight", &mounTrackerSF_weight);
    outTree->Branch("eleMVAT_IDSF_weight", &eleMVAT_IDSF_weight);
    outTree->Branch("eleMVAT_IDSF_weight_up", &eleMVAT_IDSF_weight_up);
    outTree->Branch("eleMVAT_IDSF_weight_down", &eleMVAT_IDSF_weight_down);
    outTree->Branch("eleMVAT_IDSF_weight_backup", &eleMVAT_IDSF_weight_backup);
    outTree->Branch("elesTopMVAT_weight", &elesTopMVAT_weight);
    outTree->Branch("elesTopMVAT_weight_up", &elesTopMVAT_weight_up);
    outTree->Branch("elesTopMVAT_weight_down", &elesTopMVAT_weight_down);
    outTree->Branch("musTopMVAT_weight", &musTopMVAT_weight);
    outTree->Branch("musTopMVAT_weight_up", &musTopMVAT_weight_up);
    outTree->Branch("musTopMVAT_weight_down", &musTopMVAT_weight_down);
    outTree->Branch("tauT_IDSF_weight", &tauT_IDSF_weight);
    outTree->Branch("tauT_IDSF_weight_new", &tauT_IDSF_weight_new);
    outTree->Branch("tauT_IDSF_weight_new_vsjet_up", &tauT_IDSF_weight_new_vsjet_up);
    outTree->Branch("tauT_IDSF_weight_new_vsjet_down", &tauT_IDSF_weight_new_vsjet_down);
    outTree->Branch("tauT_IDSF_weight_new_vsmu_up", &tauT_IDSF_weight_new_vsmu_up);
    outTree->Branch("tauT_IDSF_weight_new_vsmu_down", &tauT_IDSF_weight_new_vsmu_down);
    outTree->Branch("tauT_IDSF_weight_new_vsele_up", &tauT_IDSF_weight_new_vsele_up);
    outTree->Branch("tauT_IDSF_weight_new_vsele_down", &tauT_IDSF_weight_new_vsele_down);
    outTree->Branch("btagShape_weight", &btagShape_weight);

    outTree->Branch("btagShape_weight_jes_up", &btagShape_weight_jes_up);
    outTree->Branch("btagShape_weight_jes_down", &btagShape_weight_jes_down);
    outTree->Branch("btagShape_weight_hf_up", &btagShape_weight_hf_up);
    outTree->Branch("btagShape_weight_hf_down", &btagShape_weight_hf_down);
    outTree->Branch("btagShape_weight_lf_up", &btagShape_weight_lf_up);
    outTree->Branch("btagShape_weight_lf_down", &btagShape_weight_lf_down);
    outTree->Branch("btagShape_weight_hfstats1_up", &btagShape_weight_hfstats1_up);
    outTree->Branch("btagShape_weight_hfstats1_down", &btagShape_weight_hfstats1_down);
    outTree->Branch("btagShape_weight_hfstats2_up", &btagShape_weight_hfstats2_up);
    outTree->Branch("btagShape_weight_hfstats2_down", &btagShape_weight_hfstats2_down);
    outTree->Branch("btagShape_weight_lfstats1_up", &btagShape_weight_lfstats1_up);
    outTree->Branch("btagShape_weight_lfstats1_down", &btagShape_weight_lfstats1_down);
    outTree->Branch("btagShape_weight_lfstats2_up", &btagShape_weight_lfstats2_up);
    outTree->Branch("btagShape_weight_lfstats2_down", &btagShape_weight_lfstats2_down);
    outTree->Branch("btagShape_weight_cferr1_up", &btagShape_weight_cferr1_up);
    outTree->Branch("btagShape_weight_cferr1_down", &btagShape_weight_cferr1_down);
    outTree->Branch("btagShape_weight_cferr2_up", &btagShape_weight_cferr2_up);
    outTree->Branch("btagShape_weight_cferr2_down", &btagShape_weight_cferr2_down);

    outTree->Branch("btagShapeR", &btagShapeR);
    outTree->Branch("HLT_weight", &HLT_weight);
    outTree->Branch("HLT_weight_stats_up", &HLT_weight_stats_up);
    outTree->Branch("HLT_weight_stats_down", &HLT_weight_stats_down);

    std::cout << "Done initializing ............\n";
    std::cout << "\n";
};

void WeightVarMaker::makeVariables(EventForMV *e)
{
    // clearBranch();
    //!!! to be done
    EVENT_prefireWeight = *e->EVENT_prefireWeight_;
    EVENT_prefireWeight_up = *e->EVENT_prefireWeight_up_;
    EVENT_prefireWeight_down = *e->EVENT_prefireWeight_down_;
    EVENT_genWeight = *e->EVENT_genWeight_;
    PUweight_ = *e->PUWeight;
    PUweight_up_ = *e->PUWeight_up;
    PUweight_down_ = *e->PUWeight_down;

};

void WeightVarMaker::clearBranch()
{ //??? derived class should also have a clearBranch()
};


WeightVarMaker::~WeightVarMaker(){};