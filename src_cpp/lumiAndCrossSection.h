#ifndef LUMIANDCROSSCESTION_H
#define LUMIANDCROSSCESTION_H

#include <TString.h>
#include <map>
//how to deal with global variables? inline with c++17

namespace TTTT{

inline const std::map<TString, Double_t> lumiMap = {
   // fb-1*1000 = pb-1
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/TWikiLUM
    //https://twiki.cern.ch/twiki/bin/view/CMS/PdmVRun3Analysis#Year_2022
    {"2016preVFP", 19500}, //"UL2016_preVFP", 19500.0 from Fabio
    {"2016postVFP", 16810},
    {"2016", 36310},
    {"2017", 41480.0},
    {"2018", 59830.0},
    {"2022", 	9600}, //!!! only for 2022CD 
    {"2022preEE", 	9600}, //!!! only for 2022CD 
    {"2022postEE", 	27700}, //!!! only for 2022CD 
};

inline const std::map<TString, Double_t> crossSectionMap = {
    {"tttt", 0.01197},
    {"ttbar_2l", 88.29},//TT intotal 833.9pb
    {"ttbar_0l", 377.96},
    {"ttbar_1l", 365.34},
    {"ttG", 4.62},        // 3.773
    {"ttZ", 0.783},       // 0.6559
    {"ttW", 0.611},       // 0.2014 changed to 611
    {"ttH_bb", 0.2897},   // 0.2897
    {"ttH_nonbb", 0.209}, // 0.20

    {"wz", 2.343},
    {"ww", 6.430},
    {"zz", 1.016}, // ZZ
    {"st_tZq", 0.07358},
    {"st_tW_antitop", 35.85}, // 38.06
    {"st_tW_top", 35.85},     // 38.09

    {"qcd_50to100", 2.466e+08},    // 50-100  //2.466e+08 +- 2.190e+05 pb
    {"qcd_100to200", 2.801e+07},   // 100to200  //2.801e+07 +- 2.608e+04 pb
    {"qcd_200to300", 1.721e+6},    // 1.710e+06 +- 1.626e+03 pb
    {"qcd_300to500", 3.479e+05},   // 3.473e+05 +- 3.327e+02 pb
    {"qcd_500to700", 3.206e+04},   // 3.220e+04 +- 3.100e+01 pb
    {"qcd_700to1000", 6.827e+03},  // 6.839e+03 +- 6.602e+00 pb
    {"qcd_1000to1500", 1.207e+03}, // 1.207e+03 +- 1.167e+00 pb
    {"qcd_1500to2000", 1.20e+02},  // 1.201e+02 +- 1.160e-01 pb
    {"qcd_2000toInf", 2.525e+01},  // 2.524e+01 +- 2.436e-02 pb

    {"WJetsToLNu_HT-200To400", 532.4},
    {"WJetsToLNu_HT-400To600", 61.6},
    {"WJetsToLNu_HT-600To800", 12.4},
    {"WJetsToLNu_HT-800To1200", 5.77},
    {"WJetsToLNu_HT-1200To2500", 1.023},
    {"WJetsToLNu_HT-2500ToInf", 0.0248},

    //2022 923.6pb; 1pb=1000fb
    //https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
    // {"TTto2L2Nu", 762.1},
    // {"TTtoLNu2Q", 762.1},
    // {"TTto4Q", 741.8	},
    {"TTto2L2Nu", 97.8}, //!!!to be updated, calculated with the same BR as 13TeV
    {"TTtoLNu2Q", 404.6},
    {"TTto4Q", 377.96	},
};

inline const std::map<TString, double> DeepJetM = {
    // std::map of medium WPs for DeepJet

    {"2016postVFP", 0.2489},
    {"2016preVFP", 0.2598},
    {"2017", 0.3040},
    {"2018", 0.2783},
    {"2022preEE", 0.2783},
    {"2022postEE", 0.2783},

};


};
#endif