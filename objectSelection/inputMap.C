
#include "inputMap.h"

std::map<TString, std::array<TString, 3>> corr_SF_map{
    //  Summer19UL17_JRV2_MC.db ,, Summer19UL18_JRV2_MC.db
    // array[0]: JERSF, array[1]: JECuncertainty_MC, array[2]:JECuncertainty_data
    {"2016preVFP", {"Summer20UL16APV_JRV3_MC_ScaleFactor_AK4PFchs", "Summer19UL16APV_V7_MC_Total_AK4PFchs", "Summer20UL16APV_JRV3_MC_PtResolution_AK4PFchs"}},
    {"2016postVFP", {"Summer20UL16_JRV3_MC_ScaleFactor_AK4PFchs", "Summer19UL16_V7_MC_Total_AK4PFchs", "Summer20UL16_JRV3_MC_PtResolution_AK4PFchs"}},
    {"2017", {"Summer19UL17_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL17_V5_MC_Total_AK4PFchs", "Summer19UL17_JRV2_MC_PtResolution_AK4PFchs"}},
    {"2018", {"Summer19UL18_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL18_V5_MC_Total_AK4PFchs", "Summer19UL18_JRV2_MC_PtResolution_AK4PFchs"}},
};
std::map<TString, std::array<TString, 3>> json_map = {
    {"2016preVFP", {"JME/2016preVFP_UL/jet_jerc.json", "TAU/2016preVFP_UL/tau.json", "BTV/2016preVFP_UL/btagging.json"}},
    {"2016postVFP", {"JME/2016postVFP_UL/jet_jerc.json", "TAU/2016postVFP_UL/tau.json", "BTV/2016postVFP_UL/btagging.json"}},
    {"2017", {"JME/2017_UL/jet_jerc.json", "TAU/2017_UL/tau.json", "BTV/2017_UL/btagging.json"}},
    {"2018", {"JME/2018_UL/jet_jerc.json", "TAU/2018_UL/tau.json", "BTV/2018_UL/btagging.json"}},
};
std::map<TString, TString> GoldenJSONs = {
    {"2016postVFP", "../golden_JSONs/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt"},
    {"2016preVFP", "../golden_JSONs/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt"},
    {"2017", "../golden_JSONs/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt"},
    {"2018", "../golden_JSONs/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt"},

};
std::map<TString, std::array<TString, 2>> oldFileMap = {
    {"2016preVFP", {"../data_rootFiles/smearing/UL2016_preVFP/Summer20UL16APV_JRV3_MC_PtResolution_AK4PFchs.txt", "../data_rootFiles/smearing/UL2016_postVFP/Summer19UL16APV_JRV3_MC_SF_AK4PFchs.txt"}},
    {"2016postVFP", {"../data_rootFiles/smearing/UL2016_postVFP/Summer20UL16_JRV3_MC_PtResolution_AK4PFchs.txt", "../data_rootFiles/smearing/UL2016_postVFP/Summer19UL16_JRV3_MC_SF_AK4PFchs.txt"}},
    {"2017", {"../data_rootFiles/smearing/UL2017/Summer20UL17_JRV3_MC_PtResolution_AK4PFchs.txt", "../data_rootFiles/smearing/UL2017/Summer19UL17_JRV3_MC_SF_AK4PFchs.txt"}},
    {"2018", {"../data_rootFiles/smearing/UL2018/Summer20UL18_JRV3_MC_PtResolution_AK4PFchs.txt", "../data_rootFiles/smearing/UL2017/Summer19UL18_JRV3_MC_SF_AK4PFchs.txt"}},
};

std::map<TString, std::array<TString, 4>> pileUpFileMap = {
    {"2016preVFP", {"../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-preVFP-69200ub-99bins.root", "../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-preVFP-72400ub-99bins.root", "../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-preVFP-66000ub-99bins.root", "../data_rootFiles/PUHistogram_mc2016_preVFP.root"}},
    {"2016postVFP", {"../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-postVFP-69200ub-99bins.root", "../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-postVFP-72400ub-99bins.root", "../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-postVFP-66000ub-99bins.root", "../data_rootFiles/PUHistogram_mc2016_postVFP.root"}},
    {"2017", {"../data_rootFiles/PileupHistogram-goldenJSON-13tev-2017-69200ub-99bins.root", "../data_rootFiles/PileupHistogram-goldenJSON-13tev-2017-72400ub-99bins.root", "../data_rootFiles/PileupHistogram-goldenJSON-13tev-2017-66000ub-99bins.root", "../data_rootFiles/PUHistogram_mc2017.root"}},
    {"2018", {"../data_rootFiles/PileupHistogram-goldenJSON-13tev-2018-69200ub-99bins.root", "../data_rootFiles/PileupHistogram-goldenJSON-13tev-2018-72400ub-99bins.root", "../data_rootFiles/PileupHistogram-goldenJSON-13tev-2018-66000ub-99bins.root", "../data_rootFiles/PUHistogram_mc2018.root"}},
};

std::map<TString, std::array<TString, 2>> TopMVALeptonMap = {
    {"2016postVFP", {"./TopLeptonMVA/mvaWeights_new/el_TOPUL16_XGB.weights.bin", "./TopLeptonMVA/mvaWeights_new/mu_TOPUL16_XGB.weights.bin"}},
    {"2016preVFP", {"./TopLeptonMVA/mvaWeights_new/el_TOPUL16APV_XGB.weights.bin", "./TopLeptonMVA/mvaWeights_new/mu_TOPUL16APV_XGB.weights.bin"}},
    {"2017", {"./TopLeptonMVA/mvaWeights_new/el_TOPUL17_XGB.weights.bin", "./TopLeptonMVA/mvaWeights_new/mu_TOPUL17_XGB.weights.bin"}},
    {"2018", {"./TopLeptonMVA/mvaWeights_new/el_TOPUL18_XGB.weights.bin", "./TopLeptonMVA/mvaWeights_new/mu_TOPUL18_XGB.weights.bin"}},
};

std::map<TString, double> DeepJetL = {
    // std::map of loose WPs for DeepJet
    {"2016postVFP", 0.0480},
    {"2016preVFP", 0.0508},
    {"2017", 0.0532},
    {"2018", 0.0490},
};

std::map<TString, double> DeepJetM = {
    // std::map of medium WPs for DeepJet

    {"2016postVFP", 0.2489},
    {"2016preVFP", 0.2598},
    {"2017", 0.3040},
    {"2018", 0.2783},

};

std::map<TString, double> DeepJetT = {
    // std::map of tight WPs for DeepJet

    {"2016postVFP", 0.6377},
    {"2016preVFP", 0.6502},
    {"2017", 0.7476},
    {"2018", 0.7100},

};

std::map<TString, double> DeepCSVL = {
    // std::map of loose WPs for DeepCSV

    {"2016postVFP", 0.1918},
    {"2016preVFP", 0.2027},
    {"2017", 0.1355},
    {"2018", 0.1208},

};

std::map<TString, double> DeepCSVM = {
    // std::map of medium WPs for DeepCSV

    {"2016postVFP", 0.5847},
    {"2016preVFP", 0.6001},
    {"2017", 0.4506},
    {"2018", 0.4168},

};

std::map<TString, double> DeepCSVT = {
    // std::map of tight WPs for DeepCSV

    {"2016postVFP", 0.8767},
    {"2016preVFP", 0.8819},
    {"2017", 0.7738},
    {"2018", 0.7665},

};