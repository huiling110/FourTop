#include <TString.h>

std::map<TString, Double_t> lumiMap = {
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/TWikiLUM
    {"2016preVFP", 19500}, //"UL2016_preVFP", 19500.0 from Fabio
    {"2016postVFP", 16810},
    {"2016", 36310},
    {"UL2017", 41480.0},
    {"UL2018", 59830.0},
};

std::map<TString, Double_t> crossSectionMap = {
    {"tttt", 0.01197},
    {"ttbar_2l", 88.29},
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
};
