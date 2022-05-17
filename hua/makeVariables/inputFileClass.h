#include "TString.h"
#include <map>

// struct yearFileMap{
//     TString muonSFFiles;
//     TString eGammaSFFiles;
// o


// TString MUOSF_dir = "/publicfs/cms/user/fabioiemmi/CMSSW_10_6_27/src/FourTop/fabio/UltraLegacy/scale_factors/muons/";
const TString MUOSF_dir = "../../fabio/UltraLegacy/scale_factors/muons/";
std::map<TString, TString> MUOSF_files = { //std::map OF INPUT MUO SCALE FACTOR FILES                                                                                                                                                          
    {"UL2016_preVFP", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2016_UL_preVFP_ID.root"},
    {"UL2016_postVFP", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2016_UL_postVFP_ID.root"},
    {"UL2017", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root"},
    {"UL2018", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root"},

};

const TString EGammaSF_dir = "../../fabio/UltraLegacy/scale_factors/electrons/";
std::map<TString, TString> EGammaSF_files = { //std::map OF INPUT EGamma SCALE FACTOR FILES                                                                                                                                                          
    {"UL2016_preVFP", EGammaSF_dir + "egammaEffi.txt_Ele_wp90noiso_preVFP_EGM2D.root"},
    {"UL2016_postVFP", EGammaSF_dir + "egammaEffi.txt_Ele_wp90noiso_postVFP_EGM2D.root"},
    {"UL2017", EGammaSF_dir + "egammaEffi.txt_EGM2D_MVA90noIso_UL17.root"},
    {"UL2018", EGammaSF_dir + "egammaEffi.txt_Ele_wp90noiso_EGM2D.root"},
};

// TString BTVSF_dir = "/publicfs/cms/user/fabioiemmi/CMSSW_10_6_27/src/FourTop/fabio/UltraLegacy/scale_factors/btagging/";
// std::map<TString, TString> BTVSF_files_reshaping = { //std::map OF INPUT BTV SCALE FACTOR FILES

//     {"UL2016_preVFP", BTVSF_dir + "reshaping_deepJet_106XUL16preVFP_v2_dropLines.csv"},
//     {"UL2016_postVFP", BTVSF_dir + "reshaping_deepJet_106XUL16postVFP_v3_dropLines.csv"},
//     {"UL2017", BTVSF_dir + "reshaping_deepJet_106XUL17_v3_dropLines.csv"},
//     {"UL2018", BTVSF_dir + "reshaping_deepJet_106XUL18_v2_dropLines.csv"},

// };

// std::map<TString, TString> BTVSF_files_fixedWP = { //std::map OF INPUT BTV SCALE FACTOR FILES

//     {"UL2016_preVFP", BTVSF_dir + "wp_deepJet_106XUL16preVFP_v2.csv"},
//     {"UL2016_postVFP", BTVSF_dir + "wp_deepJet_106XUL16postVFP_v3.csv"},
//     {"UL2017", BTVSF_dir + "wp_deepJet_106XUL17_v3.csv"},
//     {"UL2018", BTVSF_dir + "wp_deepJet_106XUL18_v2.csv"},

// };

// std::map<TString, TString> btagEff_files = { //std::map OF INPUT B TAG EFFICIENCY FILES

//     {"UL2016_preVFP", BTVSF_dir + "efficiencies/btagEfficiencies_UL2016_preVFP.root"},
//     {"UL2016_postVFP", BTVSF_dir + "efficiencies/btagEfficiencies_UL2016_postVFP.root"},
//     {"UL2017", BTVSF_dir + "efficiencies/btagEfficiencies_UL2017.root"},
//     {"UL2018", BTVSF_dir + "efficiencies/btagEfficiencies_UL2018.root"},

// };

TString TRGSF_dir = "../../fabio/UltraLegacy/scale_factors/trigger/";
std::map<TString, TString> TRGSF_files = { //std::map OF INPUT TRG SCALE FACTOR FILES
    {"UL2016_preVFP", TRGSF_dir + "TriggerSF_2D_UL2016_preVFP.root"},
    {"UL2016_postVFP", TRGSF_dir + "TriggerSF_2D_UL2016_postVFP.root"},
    {"UL2017", TRGSF_dir + "proxy.root"},
    {"UL2018", TRGSF_dir + "proxy.rootv"},
};