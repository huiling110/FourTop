

#include "../include/inputMap.h"

std::map<TString, std::array<TString, 3>> corr_SF_map{
    //  Summer19UL17_JRV2_MC.db ,, Summer19UL18_JRV2_MC.db
    // array[0]: JERSF, array[1]: JECuncertainty_MC, array[2]:JERpt resolution
    {"2016preVFP", {"Summer20UL16APV_JRV3_MC_ScaleFactor_AK4PFchs", "Summer19UL16APV_V7_MC_Total_AK4PFchs", "Summer20UL16APV_JRV3_MC_PtResolution_AK4PFchs"}},
    {"2016postVFP", {"Summer20UL16_JRV3_MC_ScaleFactor_AK4PFchs", "Summer19UL16_V7_MC_Total_AK4PFchs", "Summer20UL16_JRV3_MC_PtResolution_AK4PFchs"}},
    {"2017", {"Summer19UL17_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL17_V5_MC_Total_AK4PFchs", "Summer19UL17_JRV2_MC_PtResolution_AK4PFchs"}},
    {"2018", {"Summer19UL18_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL18_V5_MC_Total_AK4PFchs", "Summer19UL18_JRV2_MC_PtResolution_AK4PFchs"}},
    {"2022", {"Summer19UL18_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL18_V5_MC_Total_AK4PFchs", "Summer19UL18_JRV2_MC_PtResolution_AK4PFchs"}},//!!!
    {"2022preEE", {"Summer19UL18_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL18_V5_MC_Total_AK4PFchs", "Summer19UL18_JRV2_MC_PtResolution_AK4PFchs"}},//!!!
    {"2022postEE", {"Summer19UL18_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL18_V5_MC_Total_AK4PFchs", "Summer19UL18_JRV2_MC_PtResolution_AK4PFchs"}}, //!!!1
};
std::map<TString, std::array<TString, 3>> json_map = {
    {"2016preVFP", {"JME/2016preVFP_UL/jet_jerc.json", "TAU/2016preVFP_UL/tau.json", "BTV/2016preVFP_UL/btagging.json"}},
    {"2016postVFP", {"JME/2016postVFP_UL/jet_jerc.json", "TAU/2016postVFP_UL/tau.json", "BTV/2016postVFP_UL/btagging.json"}},
    {"2017", {"JME/2017_UL/jet_jerc.json", "TAU/2017_UL/tau.json", "BTV/2017_UL/btagging.json"}},
    {"2018", {"JME/2018_UL/jet_jerc.json", "TAU/2018_UL/tau.json", "BTV/2018_UL/btagging.json"}},
    {"2022", {"JME/2018_UL/jet_jerc.json", "TAU/2018_UL/tau.json", "BTV/2018_UL/btagging.json"}},//!!! to be updated!!!
    {"2022preEE", {"JME/2018_UL/jet_jerc.json", "TAU/2018_UL/tau.json", "BTV/2018_UL/btagging.json"}},//!!! to be updated!!!
    {"2022postEE", {"../newRun3/JME/2022_Summer22EE/jet_jerc.json", "TAU/2018_UL/tau.json", "BTV/2018_UL/btagging.json"}},//!!! to be updated!!!
};
std::map<TString, TString> GoldenJSONs = {
    {"2016postVFP", "./input/golden_JSONs/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt"},
    {"2016preVFP", "./input/golden_JSONs/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt"},
    {"2017", "./input/golden_JSONs/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt"},
    {"2018", "./input/golden_JSONs/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt"},
    {"2022", "./input/golden_JSONs/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt"},//!!!
    {"2022preEE", "./input/golden_JSONs/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt"},//!!!
    {"2022postEE", "./input/golden_JSONs/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt"},//!!!
    // {"2022", "./input/Cert_Collisions2022_355100_362760_Golden.json"},//!!!
    // {"2022preEE", "./input/Cert_Collisions2022_355100_362760_Golden.json"},//!!!
    // {"2022postEE", "./input/Cert_Collisions2022_355100_362760_Golden.json"},//!!!

};
std::map<TString, std::array<TString, 2>> oldFileMap = {
    {"2016preVFP", {"../data_rootFiles/smearing/UL2016_preVFP/Summer20UL16APV_JRV3_MC_PtResolution_AK4PFchs.txt", "../data_rootFiles/smearing/UL2016_postVFP/Summer19UL16APV_JRV3_MC_SF_AK4PFchs.txt"}},
    {"2016postVFP", {"../data_rootFiles/smearing/UL2016_postVFP/Summer20UL16_JRV3_MC_PtResolution_AK4PFchs.txt", "../data_rootFiles/smearing/UL2016_postVFP/Summer19UL16_JRV3_MC_SF_AK4PFchs.txt"}},
    {"2017", {"../data_rootFiles/smearing/UL2017/Summer20UL17_JRV3_MC_PtResolution_AK4PFchs.txt", "../data_rootFiles/smearing/UL2017/Summer19UL17_JRV3_MC_SF_AK4PFchs.txt"}},
    {"2018", {"../data_rootFiles/smearing/UL2018/Summer20UL18_JRV3_MC_PtResolution_AK4PFchs.txt", "../data_rootFiles/smearing/UL2017/Summer19UL18_JRV3_MC_SF_AK4PFchs.txt"}},
};

std::map<TString, std::array<TString, 4>> pileUpFileMap = {
    {"2016preVFP", {"input/pileup/PileupHistogram-goldenJSON-13tev-2016-preVFP-69200ub-99bins.root", "input/pileup/PileupHistogram-goldenJSON-13tev-2016-preVFP-72400ub-99bins.root", "input/pileup/PileupHistogram-goldenJSON-13tev-2016-preVFP-66000ub-99bins.root", "input/pileup/PUHistogram_mc2016_preVFP.root"}},
    {"2016postVFP", {"input/pileup/PileupHistogram-goldenJSON-13tev-2016-postVFP-69200ub-99bins.root", "input/pileup/PileupHistogram-goldenJSON-13tev-2016-postVFP-72400ub-99bins.root", "input/pileup/PileupHistogram-goldenJSON-13tev-2016-postVFP-66000ub-99bins.root", "input/pileup/PUHistogram_mc2016_postVFP.root"}},
    {"2017", {"input/pileup/PileupHistogram-goldenJSON-13tev-2017-69200ub-99bins.root", "input/pileup/PileupHistogram-goldenJSON-13tev-2017-72400ub-99bins.root", "input/pileup/PileupHistogram-goldenJSON-13tev-2017-66000ub-99bins.root", "input/pileup/PUHistogram_mc2017.root"}},
    {"2018", {"input/pileup/PileupHistogram-goldenJSON-13tev-2018-69200ub-99bins.root", "input/pileup/PileupHistogram-goldenJSON-13tev-2018-72400ub-99bins.root", "input/pileup/PileupHistogram-goldenJSON-13tev-2018-66000ub-99bins.root", "input/pileup/PUHistogram_mc2018.root"}},
    {"2022preEE", {"input/pileup/2022/pileupHistogram-Cert_Collisions2022_355100_362760_GoldenJson-13p6tev-2022-69200ub.root", "input/pileup/2022/pileupHistogram-Cert_Collisions2022_355100_362760_GoldenJson-13p6tev-2022-72400ub.root", "input/pileup/2022/pileupHistogram-Cert_Collisions2022_355100_362760_GoldenJson-13p6tev-2022-66000ub.root", "input/pileup/2022/pileupHistogram-mc-13p6tev-2022.root"}},//!!!MC samples I could not find
    {"2022postEE", {"input/pileup/2022/pileupHistogram-Cert_Collisions2022_355100_362760_GoldenJson-13p6tev-2022-69200ub.root", "input/pileup/2022/pileupHistogram-Cert_Collisions2022_355100_362760_GoldenJson-13p6tev-2022-72400ub.root", "input/pileup/2022/pileupHistogram-Cert_Collisions2022_355100_362760_GoldenJson-13p6tev-2022-66000ub.root", "input/pileup/2022/pileupHistogram-mc-13p6tev-2022.root"}},
    {"2022", {"input/pileup/2022/pileupHistogram-Cert_Collisions2022_355100_362760_GoldenJson-13p6tev-2022-69200ub.root", "input/pileup/2022/pileupHistogram-Cert_Collisions2022_355100_362760_GoldenJson-13p6tev-2022-72400ub.root", "input/pileup/2022/pileupHistogram-Cert_Collisions2022_355100_362760_GoldenJson-13p6tev-2022-66000ub.root", "input/pileup/2022/pileupHistogram-mc-13p6tev-2022.root"}},
};

std::map<TString, std::array<TString, 2>> TopMVALeptonMap = {
    {"2016postVFP", {"input/TopLeptonMVA/mvaWeights_new/el_TOPUL16_XGB.weights.bin", "input/TopLeptonMVA/mvaWeights_new/mu_TOPUL16_XGB.weights.bin"}},
    {"2016preVFP", {"input/TopLeptonMVA/mvaWeights_new/el_TOPUL16APV_XGB.weights.bin", "input/TopLeptonMVA/mvaWeights_new/mu_TOPUL16APV_XGB.weights.bin"}},
    {"2017", {"input/TopLeptonMVA/mvaWeights_new/el_TOPUL17_XGB.weights.bin", "input/TopLeptonMVA/mvaWeights_new/mu_TOPUL17_XGB.weights.bin"}},
    {"2018", {"input/TopLeptonMVA/mvaWeights_new/el_TOPUL18_XGB.weights.bin", "input/TopLeptonMVA/mvaWeights_new/mu_TOPUL18_XGB.weights.bin"}},
    {"2022", {"input/TopLeptonMVA/mvaWeights_new/el_TOPUL18_XGB.weights.bin", "input/TopLeptonMVA/mvaWeights_new/mu_TOPUL18_XGB.weights.bin"}},
    {"2022preEE", {"input/TopLeptonMVA/mvaWeights_new/el_TOPUL18_XGB.weights.bin", "input/TopLeptonMVA/mvaWeights_new/mu_TOPUL18_XGB.weights.bin"}},
    {"2022postEE", {"input/TopLeptonMVA/mvaWeights_new/el_TOPUL18_XGB.weights.bin", "input/TopLeptonMVA/mvaWeights_new/mu_TOPUL18_XGB.weights.bin"}},
};

std::map<TString, double> DeepJetL = {
    // std::map of loose WPs for DeepJet
    {"2016postVFP", 0.0480},
    {"2016preVFP", 0.0508},
    {"2017", 0.0532},
    {"2018", 0.0490},
    {"2022", 0.0490},
    {"2022preEE", 0.0490},
    {"2022postEE", 0.0490},
};

std::map<TString, double> DeepJetM = {
    // std::map of medium WPs for DeepJet
    {"2016postVFP", 0.2489},
    {"2016preVFP", 0.2598},
    {"2017", 0.3040},
    {"2018", 0.2783},
    {"2022", 0.2783},
    {"2022preEE", 0.3086},
    {"2022postEE", 0.3196},
};

std::map<TString, double> DeepJetT = {
    // std::map of tight WPs for DeepJet
    {"2016postVFP", 0.6377},
    {"2016preVFP", 0.6502},
    {"2017", 0.7476},
    {"2018", 0.7100},
    {"2022", 0.7100},
    {"2022preEE", 0.7183},
    {"2022postEE", 0.73},
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

    //https://btv-wiki.docs.cern.ch/ScaleFactors/Run3Summer22/
std::map<TString, std::array<Double_t, 2>> particleNetBMT = {
    // https://btv-wiki.docs.cern.ch/ScaleFactors/Run3Summer22/
    {"2022preEE", {0.245, 0.6734}},
    {"2022postEE", {0.2605, 0.6915}},

};