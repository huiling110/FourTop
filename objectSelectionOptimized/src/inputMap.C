#include "../include/inputMap.h"

std::map<TString, std::array<TString, 4>> corr_SF_map{
    //  Summer19UL17_JRV2_MC.db ,, Summer19UL18_JRV2_MC.db
    // array[0]: JERSF, array[1]: JECuncertainty_MC, array[2]:JERpt resolution; array[3]:vetoMap
    {"2016preVFP", {"Summer20UL16APV_JRV3_MC_ScaleFactor_AK4PFchs", "Summer19UL16APV_V7_MC_Total_AK4PFchs", "Summer20UL16APV_JRV3_MC_PtResolution_AK4PFchs", "Summer22_23Sep2023_RunCD_V1"}},
    {"2016postVFP", {"Summer20UL16_JRV3_MC_ScaleFactor_AK4PFchs", "Summer19UL16_V7_MC_Total_AK4PFchs", "Summer20UL16_JRV3_MC_PtResolution_AK4PFchs", "Summer22_23Sep2023_RunCD_V1"}},
    {"2017", {"Summer19UL17_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL17_V5_MC_Total_AK4PFchs", "Summer19UL17_JRV2_MC_PtResolution_AK4PFchs", "Summer22_23Sep2023_RunCD_V1"}},
    {"2018", {"Summer19UL18_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL18_V5_MC_Total_AK4PFchs", "Summer19UL18_JRV2_MC_PtResolution_AK4PFchs", "Summer22_23Sep2023_RunCD_V1"}},
    {"2022", {"Summer19UL18_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL18_V5_MC_Total_AK4PFchs", "Summer19UL18_JRV2_MC_PtResolution_AK4PFchs", "Summer22_23Sep2023_RunCD_V1"}},//!!!
    {"2022preEE", {"Summer22_22Sep2023_JRV1_MC_ScaleFactor_AK4PFPuppi", "Summer19UL18_V5_MC_Total_AK4PFchs", "Summer22_22Sep2023_JRV1_MC_PtResolution_AK4PFPuppi", "Summer22_23Sep2023_RunCD_V1" }},//!!!
    {"2022postEE", {"Summer22EE_22Sep2023_JRV1_MC_ScaleFactor_AK4PFPuppi", "Summer19UL18_V5_MC_Total_AK4PFchs", "Summer22EE_22Sep2023_JRV1_MC_PtResolution_AK4PFPuppi", "Summer22EE_23Sep2023_RunEFG_V1"}}, //!!!1
};

std::map<TString, std::array<TString, 27>> corr_Uncer_JES_map{
    //  Summer19UL17_JRV2_MC.db ,, Summer19UL18_JRV2_MC.db
    // array[0]: JERSF, array[1]: JECuncertainty_MC, array[2]:JECuncertainty_data
    {"2016preVFP", {"Summer19UL16APV_V7_MC_AbsoluteMPFBias_AK4PFchs", "Summer19UL16APV_V7_MC_AbsoluteScale_AK4PFchs", "Summer19UL16APV_V7_MC_AbsoluteStat_AK4PFchs", "Summer19UL16APV_V7_MC_FlavorQCD_AK4PFchs", "Summer19UL16APV_V7_MC_Fragmentation_AK4PFchs", "Summer19UL16APV_V7_MC_PileUpDataMC_AK4PFchs", "Summer19UL16APV_V7_MC_PileUpPtBB_AK4PFchs", "Summer19UL16APV_V7_MC_PileUpPtEC1_AK4PFchs", "Summer19UL16APV_V7_MC_PileUpPtEC2_AK4PFchs", "Summer19UL16APV_V7_MC_PileUpPtHF_AK4PFchs", "Summer19UL16APV_V7_MC_PileUpPtRef_AK4PFchs", "Summer19UL16APV_V7_MC_RelativeFSR_AK4PFchs", "Summer19UL16APV_V7_MC_RelativeJEREC1_AK4PFchs", "Summer19UL16APV_V7_MC_RelativeJEREC2_AK4PFchs", "Summer19UL16APV_V7_MC_RelativeJERHF_AK4PFchs", "Summer19UL16APV_V7_MC_RelativePtBB_AK4PFchs", "Summer19UL16APV_V7_MC_RelativePtEC1_AK4PFchs", "Summer19UL16APV_V7_MC_RelativePtEC2_AK4PFchs", "Summer19UL16APV_V7_MC_RelativePtHF_AK4PFchs", "Summer19UL16APV_V7_MC_RelativeBal_AK4PFchs", "Summer19UL16APV_V7_MC_RelativeSample_AK4PFchs", "Summer19UL16APV_V7_MC_RelativeStatEC_AK4PFchs", "Summer19UL16APV_V7_MC_RelativeStatFSR_AK4PFchs", "Summer19UL16APV_V7_MC_RelativeStatHF_AK4PFchs", "Summer19UL16APV_V7_MC_SinglePionECAL_AK4PFchs", "Summer19UL16APV_V7_MC_SinglePionHCAL_AK4PFchs", "Summer19UL16APV_V7_MC_TimePtEta_AK4PFchs"}},
    {"2016postVFP", {"Summer19UL16_V7_MC_AbsoluteMPFBias_AK4PFchs", "Summer19UL16_V7_MC_AbsoluteScale_AK4PFchs", "Summer19UL16_V7_MC_AbsoluteStat_AK4PFchs", "Summer19UL16_V7_MC_FlavorQCD_AK4PFchs", "Summer19UL16_V7_MC_Fragmentation_AK4PFchs", "Summer19UL16_V7_MC_PileUpDataMC_AK4PFchs", "Summer19UL16_V7_MC_PileUpPtBB_AK4PFchs", "Summer19UL16_V7_MC_PileUpPtEC1_AK4PFchs", "Summer19UL16_V7_MC_PileUpPtEC2_AK4PFchs", "Summer19UL16_V7_MC_PileUpPtHF_AK4PFchs", "Summer19UL16_V7_MC_PileUpPtRef_AK4PFchs", "Summer19UL16_V7_MC_RelativeFSR_AK4PFchs", "Summer19UL16_V7_MC_RelativeJEREC1_AK4PFchs", "Summer19UL16_V7_MC_RelativeJEREC2_AK4PFchs", "Summer19UL16_V7_MC_RelativeJERHF_AK4PFchs", "Summer19UL16_V7_MC_RelativePtBB_AK4PFchs", "Summer19UL16_V7_MC_RelativePtEC1_AK4PFchs", "Summer19UL16_V7_MC_RelativePtEC2_AK4PFchs", "Summer19UL16_V7_MC_RelativePtHF_AK4PFchs", "Summer19UL16_V7_MC_RelativeBal_AK4PFchs", "Summer19UL16_V7_MC_RelativeSample_AK4PFchs", "Summer19UL16_V7_MC_RelativeStatEC_AK4PFchs", "Summer19UL16_V7_MC_RelativeStatFSR_AK4PFchs", "Summer19UL16_V7_MC_RelativeStatHF_AK4PFchs", "Summer19UL16_V7_MC_SinglePionECAL_AK4PFchs", "Summer19UL16_V7_MC_SinglePionHCAL_AK4PFchs", "Summer19UL16_V7_MC_TimePtEta_AK4PFchs"}},
    {"2017", {"Summer19UL17_V5_MC_AbsoluteMPFBias_AK4PFchs", "Summer19UL17_V5_MC_AbsoluteScale_AK4PFchs", "Summer19UL17_V5_MC_AbsoluteStat_AK4PFchs", "Summer19UL17_V5_MC_FlavorQCD_AK4PFchs", "Summer19UL17_V5_MC_Fragmentation_AK4PFchs", "Summer19UL17_V5_MC_PileUpDataMC_AK4PFchs", "Summer19UL17_V5_MC_PileUpPtBB_AK4PFchs", "Summer19UL17_V5_MC_PileUpPtEC1_AK4PFchs", "Summer19UL17_V5_MC_PileUpPtEC2_AK4PFchs", "Summer19UL17_V5_MC_PileUpPtHF_AK4PFchs", "Summer19UL17_V5_MC_PileUpPtRef_AK4PFchs", "Summer19UL17_V5_MC_RelativeFSR_AK4PFchs", "Summer19UL17_V5_MC_RelativeJEREC1_AK4PFchs", "Summer19UL17_V5_MC_RelativeJEREC2_AK4PFchs", "Summer19UL17_V5_MC_RelativeJERHF_AK4PFchs", "Summer19UL17_V5_MC_RelativePtBB_AK4PFchs", "Summer19UL17_V5_MC_RelativePtEC1_AK4PFchs", "Summer19UL17_V5_MC_RelativePtEC2_AK4PFchs", "Summer19UL17_V5_MC_RelativePtHF_AK4PFchs", "Summer19UL17_V5_MC_RelativeBal_AK4PFchs", "Summer19UL17_V5_MC_RelativeSample_AK4PFchs", "Summer19UL17_V5_MC_RelativeStatEC_AK4PFchs", "Summer19UL17_V5_MC_RelativeStatFSR_AK4PFchs", "Summer19UL17_V5_MC_RelativeStatHF_AK4PFchs", "Summer19UL17_V5_MC_SinglePionECAL_AK4PFchs", "Summer19UL17_V5_MC_SinglePionHCAL_AK4PFchs", "Summer19UL17_V5_MC_TimePtEta_AK4PFchs"}},
    {"2018", {"Summer19UL18_V5_MC_AbsoluteMPFBias_AK4PFchs", "Summer19UL18_V5_MC_AbsoluteScale_AK4PFchs", "Summer19UL18_V5_MC_AbsoluteStat_AK4PFchs", "Summer19UL18_V5_MC_FlavorQCD_AK4PFchs", "Summer19UL18_V5_MC_Fragmentation_AK4PFchs", "Summer19UL18_V5_MC_PileUpDataMC_AK4PFchs", "Summer19UL18_V5_MC_PileUpPtBB_AK4PFchs", "Summer19UL18_V5_MC_PileUpPtEC1_AK4PFchs", "Summer19UL18_V5_MC_PileUpPtEC2_AK4PFchs", "Summer19UL18_V5_MC_PileUpPtHF_AK4PFchs", "Summer19UL18_V5_MC_PileUpPtRef_AK4PFchs", "Summer19UL18_V5_MC_RelativeFSR_AK4PFchs", "Summer19UL18_V5_MC_RelativeJEREC1_AK4PFchs", "Summer19UL18_V5_MC_RelativeJEREC2_AK4PFchs", "Summer19UL18_V5_MC_RelativeJERHF_AK4PFchs", "Summer19UL18_V5_MC_RelativePtBB_AK4PFchs", "Summer19UL18_V5_MC_RelativePtEC1_AK4PFchs", "Summer19UL18_V5_MC_RelativePtEC2_AK4PFchs", "Summer19UL18_V5_MC_RelativePtHF_AK4PFchs", "Summer19UL18_V5_MC_RelativeBal_AK4PFchs", "Summer19UL18_V5_MC_RelativeSample_AK4PFchs", "Summer19UL18_V5_MC_RelativeStatEC_AK4PFchs", "Summer19UL18_V5_MC_RelativeStatFSR_AK4PFchs", "Summer19UL18_V5_MC_RelativeStatHF_AK4PFchs", "Summer19UL18_V5_MC_SinglePionECAL_AK4PFchs", "Summer19UL18_V5_MC_SinglePionHCAL_AK4PFchs", "Summer19UL18_V5_MC_TimePtEta_AK4PFchs"}},
};


//!moved to lumicrosssection.h
// std::map<TString, std::array<TString, 5>> json_map = {
//     {"2016preVFP", {"JME/2016preVFP_UL/jet_jerc.json", "TAU/2016preVFP_UL/tau.json", "BTV/2016preVFP_UL/btagging.json", "LUM/2016preVFP_UL/puWeights.json", "JME/2016preVFP_UL/jetvetomaps.json"}},
//     {"2016postVFP", {"JME/2016postVFP_UL/jet_jerc.json", "TAU/2016postVFP_UL/tau.json", "BTV/2016postVFP_UL/btagging.json", "LUM/2016postVFP_UL/puWeights.json", "JME/2016postVFP_UL/jetvetomaps.json"}},
//     {"2017", {"JME/2017_UL/jet_jerc.json", "TAU/2017_UL/tau.json", "BTV/2017_UL/btagging.json", "LUM/2017_UL/puWeights.json", "JME/2017_UL/jetvetomaps.json"}},
//     {"2018", {"JME/2018_UL/jet_jerc.json", "TAU/2018_UL/tau.json", "BTV/2018_UL/btagging.json", "LUM/2018_UL/puWeights.json", "JME/2018_UL/jetvetomaps.json"}},
//     {"2022preEE", {"JME/2022_Summer22/jet_jerc.json", "../newRun3/TAU/2022_preEE/tau_DeepTau2018v2p5_2022_preEE.json", "BTV/2018_UL/btagging.json", "LUM/2022_Summer22/puWeights.json", "JME/2022_Summer22/jetvetomaps.json"}},//!!! to be updated!!!
//     {"2022postEE", {"/JME/2022_Summer22EE/jet_jerc.json", "../newRun3/TAU/2022_postEE/tau_DeepTau2018v2p5_2022_postEE.json", "BTV/2018_UL/btagging.json", "LUM/2022_Summer22EE/puWeights.json", "JME/2022_Summer22EE/jetvetomaps.json"}},//!!! to be updated!!!
// };

std::map<TString, std::array<TString, 5>> jesTagMC = {
    // MC JES: L1, L2L3; compound, and total uncertainty
    {"2022postEE", {"Summer22EE_22Sep2023_V2_MC_L1FastJet_AK4PFPuppi", "Summer22EE_22Sep2023_V2_MC_L2Relative_AK4PFPuppi", "Summer22EE_22Sep2023_V2_MC_L3Absolute_AK4PFPuppi", "Summer22EE_22Sep2023_V2_MC_L1L2L3Res_AK4PFPuppi", "Summer22EE_22Sep2023_V2_MC_Total_AK4PFPuppi"}},
    {"2022preEE", {"Summer22_22Sep2023_V2_MC_L1FastJet_AK4PFPuppi", "Summer22_22Sep2023_V2_MC_L2Relative_AK4PFPuppi", "Summer22_22Sep2023_V2_MC_L3Absolute_AK4PFPuppi", "Summer22_22Sep2023_V2_MC_L1L2L3Res_AK4PFPuppi", "Summer22_22Sep2023_V2_MC_Total_AK4PFPuppi"}},
};

std::map<TString, std::array<TString, 6>> jesTagData = {
    // Summer22EE_22Sep2023_RunE_V2_DATA_L1FastJet_AK4PFPuppi
    {"2022postEE", {"Summer22EE_22Sep2023_", "_V2_DATA_L1L2L3Res_AK4PFPuppi", "_V2_DATA_L1FastJet_AK4PFPuppi", "_V2_DATA_L2Relative_AK4PFPuppi", "_V2_DATA_L3Absolute_AK4PFPuppi", "_V2_DATA_L2L3Residual_AK4PFPuppi"}},
    {"2022preEE", {"Summer22_22Sep2023_", "_V2_DATA_L1L2L3Res_AK4PFPuppi", "_V2_DATA_L1FastJet_AK4PFPuppi", "_V2_DATA_L2Relative_AK4PFPuppi", "_V2_DATA_L3Absolute_AK4PFPuppi", "_V2_DATA_L2L3Residual_AK4PFPuppi"}},
};



std::map<TString, TString> jesTagDataRuns ={
    {"JetHT2022C", "RunCD"},
    {"JetMET2022C", "RunCD"},
    {"JetMET2022D", "RunCD"},
    {"JetMET2022E", "RunE"},
    {"JetMET2022F", "RunF"},
    {"JetMET2022G", "RunG"},
    {"SingleMuon2022C", "RunCD"},
    {"Muon2022C", "RunCD"},
    {"Muon2022D", "RunCD"},
    {"Muon2022E", "RunE"},
    {"Muon2022F", "RunF"},
    {"Muon2022G", "RunG"},
};

std::map<TString, std::array<TString, 3>> eleScaleSmear = {
    //0: eleJsonFile; 1: scale tag; 2: smearing tag
    {"2022preEE", {"../newRun3/eleScale/2022Re-recoBCD/electronSS.json", "2022Re-recoBCD_ScaleJSON", "2022Re-recoBCD_SmearingJSON"}},
    {"2022postEE", {"../newRun3/eleScale/2022Re-recoE+PromptFG/electronSS.json", "2022Re-recoE+PromptFG_ScaleJSON", "2022Re-recoE+PromptFG_SmearingJSON"}},
    {"2016preVFP", {"../newRun3/eleScale/2022Re-recoE+PromptFG/electronSS.json", "2022Re-recoE+PromptFG_ScaleJSON", "2022Re-recoE+PromptFG_SmearingJSON"}},
    {"2016postVFP", {"../newRun3/eleScale/2022Re-recoE+PromptFG/electronSS.json", "2022Re-recoE+PromptFG_ScaleJSON", "2022Re-recoE+PromptFG_SmearingJSON"}},
    {"2017", {"../newRun3/eleScale/2022Re-recoE+PromptFG/electronSS.json", "2022Re-recoE+PromptFG_ScaleJSON", "2022Re-recoE+PromptFG_SmearingJSON"}},
    {"2018", {"../newRun3/eleScale/2022Re-recoE+PromptFG/electronSS.json", "2022Re-recoE+PromptFG_ScaleJSON", "2022Re-recoE+PromptFG_SmearingJSON"}},
};

std::map<TString, TString> GoldenJSONs = {
        {"2016postVFP", "./input/golden_JSONs/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt"},
         {"2016preVFP", "./input/golden_JSONs/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt"},
          {"2017", "./input/golden_JSONs/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt"},
           {"2018", "./input/golden_JSONs/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt"}, 
        {"2022preEE", "./input/golden_JSONs/Cert_Collisions2022_355100_362760_Golden.json"},//!!!
        {"2022postEE", "./input/golden_JSONs/Cert_Collisions2022_355100_362760_Golden.json"},//!!!
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

std::map<TString, TString> muonES = {
    {"2018", "./../../roccor/RoccoR2018UL.txt"},
    {"2017", "./../../roccor/RoccoR2017UL.txt"},
    {"2016postVFP", "./../../roccor/RoccoR2016bUL.txt"},
    {"2016preVFP", "./../../roccor/RoccoR2016aUL.txt"},
    
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
    {"2022preEE", {0.245, 0.6734}},
    {"2022postEE", {0.2605, 0.6915}},
};

std::map<TString, std::array<Double_t, 2>> robustParticleTransformerMT = {
    {"2022preEE", {0.4319, 0.8482}},
    {"2022postEE", {0.451, 0.8604}}, //80.6%, 67.2%(QCD)
};