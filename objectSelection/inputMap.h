#include "TString.h"
#include <map>
#include <string>

std::map<TString, std::array<TString,2>> corr_SF_map = {
    //  Summer19UL17_JRV2_MC.db ,, Summer19UL18_JRV2_MC.db
    //array[0]: JERSF, array[1]: JECuncertainty_MC, array[2]:JECuncertainty_data
    {"2016preVFP", {"Summer20UL16APV_JRV3_MC_ScaleFactor_AK4PFchs", "Summer19UL16APV_V7_MC_Total_AK4PFchs"}  },
    {"2016postVFP", {"Summer20UL16_JRV3_MC_ScaleFactor_AK4PFchs", "Summer19UL16_V7_MC_Total_AK4PFchs"}  },
    {"2017", {"Summer19UL17_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL17_V5_MC_Total_AK4PFchs"} },
    {"2018", {"Summer19UL18_JRV2_MC_ScaleFactor_AK4PFchs", "Summer19UL18_V5_MC_Total_AK4PFchs"} },
};


std::map<TString, std::array<TString, 2>> json_map = {
    {"2016preVFP", { "JME/2016preVFP_UL/jet_jerc.json", "TAU/2016preVFP_UL/tau.json" } },
    {"2016postVFP", {"JME/2016postVFP_UL/jet_jerc.json", "TAU/2016postVFP_UL/tau.json"} },
    {"2017", {"JME/2017_UL/jet_jerc.json", "TAU/2017_UL/tau.json"} },
    {"2018", {"JME/2018_UL/jet_jerc.json", "TAU/2018_UL/tau.json"} },
};