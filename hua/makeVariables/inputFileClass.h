#ifndef INPUTFILECLASS
#define INPUTFILECLASS

#include "TString.h"
#include <map>

// struct yearFileMap{
//     TString muonSFFiles;
//     TString eGammaSFFiles;
// o

std::map<TString, TString> map_era = {
    {"2016preVFP", "UL2016_preVFP"},
    {"2016postVFP", "UL2016_postVFP"},
    {"2017", "UL2017"},
    {"2018", "UL2018"},
};

const TString MUOSF_dir = "../../fabio/UltraLegacy/scale_factors/muons/";
const TString muonSF_base = "../../data_rootFiles/muon/muonefficiencies/Run2/UL/";
std::map<TString, TString> MUOSF_files = {
    // std::map OF INPUT MUO SCALE FACTOR FILES
    {"2016preVFP", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2016_UL_preVFP_ID.root"},
    {"2016postVFP", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2016_UL_postVFP_ID.root"},
    {"2017", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root"},
    {"2018", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root"},
};
std::map<TString, TString> muonSF_tracker = {
    {"2016preVFP", muonSF_base + "2016_preVFP/Efficiency_muon_generalTracks_Run2016preVFP_UL_trackerMuon.root"},
    {"2016postVFP", muonSF_base + "2016_postVFP/Efficiency_muon_generalTracks_Run2016postVFP_UL_trackerMuon.root"},
    {"2017", muonSF_base + "2017/Efficiency_muon_generalTracks_Run2017_UL_trackerMuon.root"},
    {"2018", muonSF_base + "2018/Efficiency_muon_generalTracks_Run2018_UL_trackerMuon.root"},
};
std::map<TString, TString> muonSF_iso = {
    {"2016preVFP", muonSF_base + "2016_preVFP/2016_preVFP_Z/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ISO.root"},
    {"2016postVFP", muonSF_base + "2016_postVFP/2016_postVFP_Z/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ISO.root"},
    {"2017", muonSF_base + "2017/2017_Z/Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root"},
    {"2018", muonSF_base + "2018/2018_Z/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root"},
};

const TString EGammaSF_dir = "../../fabio/UltraLegacy/scale_factors/electrons/";
std::map<TString, TString> EGammaSF_files = {
    // std::map OF INPUT EGamma SCALE FACTOR FILES
    {"2016preVFP", EGammaSF_dir + "egammaEffi.txt_Ele_wp90noiso_preVFP_EGM2D.root"},
    {"2016postVFP", EGammaSF_dir + "egammaEffi.txt_Ele_wp90noiso_postVFP_EGM2D.root"},
    {"2017", EGammaSF_dir + "egammaEffi.txt_EGM2D_MVA90noIso_UL17.root"},
    {"2018", EGammaSF_dir + "egammaEffi.txt_Ele_wp90noiso_EGM2D.root"},
};

// top lepton mva
std::map<TString, std::array<TString, 2>> topLeptonSF_files = {
    {"2016preVFP", {"./topMVASF/ele/2016APV/egammaEffi.txt_EGM2D.root", "./topMVASF/mu/2016HIPM/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
    {"2016postVFP", {"./topMVASF/ele/2016/egammaEffi.txt_EGM2D.root", "./topMVASF/mu/2016/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
    {"2017", {"./topMVASF/ele/2017/egammaEffi.txt_EGM2D.root", "./topMVASF/mu/2017/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
    {"2018", {"./topMVASF/ele/2018/egammaEffi.txt_EGM2D.root", "./topMVASF/mu/2018/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
};

// TString BTVSF_dir = "/publicfs/cms/user/fabioiemmi/CMSSW_10_6_27/src/FourTop/fabio/UltraLegacy/scale_factors/btagging/";
// std::map<TString, TString> BTVSF_files_reshaping = { //std::map OF INPUT BTV SCALE FACTOR FILES

//     {"2016preVFP", BTVSF_dir + "reshaping_deepJet_106XUL16preVFP_v2_dropLines.csv"},
//     {"2016postVFP", BTVSF_dir + "reshaping_deepJet_106XUL16postVFP_v3_dropLines.csv"},
//     {"2017", BTVSF_dir + "reshaping_deepJet_106XUL17_v3_dropLines.csv"},
//     {"2018", BTVSF_dir + "reshaping_deepJet_106XUL18_v2_dropLines.csv"},

// };

// std::map<TString, TString> BTVSF_files_fixedWP = { //std::map OF INPUT BTV SCALE FACTOR FILES

//     {"2016preVFP", BTVSF_dir + "wp_deepJet_106XUL16preVFP_v2.csv"},
//     {"2016postVFP", BTVSF_dir + "wp_deepJet_106XUL16postVFP_v3.csv"},
//     {"2017", BTVSF_dir + "wp_deepJet_106XUL17_v3.csv"},
//     {"2018", BTVSF_dir + "wp_deepJet_106XUL18_v2.csv"},

// };

// std::map<TString, TString> btagEff_files = { //std::map OF INPUT B TAG EFFICIENCY FILES

//     {"2016preVFP", BTVSF_dir + "efficiencies/btagEfficiencies_2016preVFP.root"},
//     {"2016postVFP", BTVSF_dir + "efficiencies/btagEfficiencies_2016postVFP.root"},
//     {"2017", BTVSF_dir + "efficiencies/btagEfficiencies_2017.root"},
//     {"2018", BTVSF_dir + "efficiencies/btagEfficiencies_2018.root"},

// };

// TString TRGSF_dir = "../../fabio/UltraLegacy/scale_factors/trigger/";
// std::map<TString, TString> TRGSF_files = {
//     // std::map OF INPUT TRG SCALE FACTOR FILES
//     // {"2016preVFP", TRGSF_dir + "TriggerSF_2D_2016preVFP.root"},
//     // {"2016postVFP", TRGSF_dir + "TriggerSF_2D_2016postVFP.root"},
//     {"2016preVFP", TRGSF_dir + "TriggerSF_2D_UL2016_preVFP.root"},
//     {"2016postVFP", TRGSF_dir + "TriggerSF_2D_UL2016_postVFP.root"},
//     {"2017", TRGSF_dir + "proxy.root"},
//     {"2018", TRGSF_dir + "proxy.rootv"},
// };

std::map<TString, TString> triggerSF_map = {
    // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v8add2DHist/results/baseline1Muon1b_triggerSF.root"},
    // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v8add2DHist/results/baseline1Muon1b_triggerSF.root"},
    // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v8add2DHist/results/baseline1Muon1b_triggerSF.root"}, // to be updated!!!
    // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baslineNoHLT_v54noHLTButPre/mc/variableHists_v0triggerEff/results/baseline1Muon1b_triggerSF.root"},
    {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v55ojectRemovalwithTightNoHLT/mc/variableHists_v1triigerEff_btagShapeWeight/results/baseline1Muon1b_triggerSF.root"},
    {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v55ojectRemovalwithTightNoHLT/mc/variableHists_v1triigerEff_btagShapeWeight/results/baseline1Muon1b_triggerSF.root"},
    {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v55ojectRemovalwithTightNoHLT/mc/variableHists_v1triigerEff_btagShapeWeight/results/baseline1Muon1b_triggerSF.root"},
    {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v55ojectRemovalwithTightNoHLT/mc/variableHists_v1triigerEff_btagShapeWeight/results/baseline1Muon1b_triggerSF.root"},
};

std::map<TString, std::array<TString, 3>> json_map = {
    {"2016preVFP", {"JME/2016preVFP_UL/jet_jerc.json", "TAU/2016preVFP_UL/tau.json", "BTV/2016preVFP_UL/btagging.json"}},
    {"2016postVFP", {"JME/2016postVFP_UL/jet_jerc.json", "TAU/2016postVFP_UL/tau.json", "BTV/2016postVFP_UL/btagging.json"}},
    {"2017", {"JME/2017_UL/jet_jerc.json", "TAU/2017_UL/tau.json", "BTV/2017_UL/btagging.json"}},
    {"2018", {"JME/2018_UL/jet_jerc.json", "TAU/2018_UL/tau.json", "BTV/2018_UL/btagging.json"}},
};

#endif