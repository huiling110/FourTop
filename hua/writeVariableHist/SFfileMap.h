
#include "TString.h"
#include <map>

std::map<TString, TString> triggerSF_map = {
    {"2016", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v8add2DHist/results/baseline1Muon1b_triggerSF.root"},
    {"2017", ""},
    {"2018", ""},
};

std::map<TString, TString> btagR_map = {
    // {"2016", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v2aadTopLepWeight_v49FixedPileUpJERAndTES/mc/variableHists_v6_btagRMeasure/results/btagR.root"}, //!!!to be updated!
    {"2016", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v0btagRCal/results/btagR.root"},
    {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v2aadTopLepWeight_v49FixedPileUpJERAndTES/mc/variableHists_v6_btagRMeasure/results/btagR.root"}, //!!!to be updated!
    {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v2aadTopLepWeight_v49FixedPileUpJERAndTES/mc/variableHists_v6_btagRMeasure/results/btagR.root"}, // //!!!to be updated!
};
