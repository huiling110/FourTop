#ifndef INPUTMAP_H
#define INPUTMAP_H

#include "TString.h"
#include <map>
#include <string>

extern std::map<TString, std::array<TString, 3>> corr_SF_map;
// = {
//     //  Summer19UL17_JRV2_MC.db ,, Summer19UL18_JRV2_MC.db
//     // array[0]: JERSF, array[1]: JECuncertainty_MC, array[2]:JECuncertainty_data
//     {"2016preVFP", {"Summer20UL16APV_JRV3_MC_ScaleFactor_AK4PFchs", "Summer19UL16APV_V7_MC_Total_AK4PFchs", "Summer20UL16APV_JRV3_MC_PtResolution_AK4PFchs"}},
//     {"2016postVFP", {"Summer20UL16_JRV3_MC_ScaleFactor_AK4PFchs", "Summer19UL16_V7_MC_Total_AK4PFchs", "Summer20UL16_JRV3_MC_PtResolution_AK4PFchs"}},
//     {"2017", {"Summer19UL17_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL17_V5_MC_Total_AK4PFchs", "Summer19UL17_JRV2_MC_PtResolution_AK4PFchs"}},
//     {"2018", {"Summer19UL18_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL18_V5_MC_Total_AK4PFchs", "Summer19UL18_JRV2_MC_PtResolution_AK4PFchs"}},
// };

extern std::map<TString, std::array<TString, 3>> json_map;

extern std::map<TString, std::array<TString, 4>> jesTagMC;
extern std::map<TString, std::array<TString, 5>> jesTagData;
extern std::map<TString, TString> jesTagDataRuns;

extern std::map<TString, TString> eleScaleSmear;

extern std::map<TString, TString> GoldenJSONs;

extern std::map<TString, std::array<TString, 2>> oldFileMap;

extern std::map<TString, std::array<TString, 4>> pileUpFileMap;

extern std::map<TString, std::array<TString, 2>> TopMVALeptonMap;

extern std::map<TString, double> DeepJetL;

extern std::map<TString, double> DeepJetM;

extern std::map<TString, double> DeepJetT;

extern std::map<TString, double> DeepCSVL;

extern std::map<TString, double> DeepCSVM;

extern std::map<TString, double> DeepCSVT;

extern std::map<TString, std::array<Double_t, 2>> particleNetBMT;

#endif