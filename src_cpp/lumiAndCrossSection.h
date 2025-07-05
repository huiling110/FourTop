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
    {"2022", 	37300},
    {"2022preEE", 	7875}, 
    {"2022postEE", 	26337}, 
};

inline const std::map<TString, Double_t> crossSectionMap = {
    // {"tttt", 0.01197}, //!!!0.01337 from https://www.arxiv.org/abs/2212.03259
    {"tttt", 0.01337 }, //!!!0.01337 from https://www.arxiv.org/abs/2212.03259

    {"ttbar_0l", 377.96},
    {"ttbar_1l", 365.34},
    {"ttbar_2l", 88.29},//TT intotal 833.9pb

    {"ttG", 15.89},        // 
    {"ttZ", 0.783},       // 0.6559
    {"ttW", 0.611},       // 0.2014 changed to 611
    {"TTZToLLNuNu", 0.281}, //ttZ 0.856
    {"TTZToQQ", 0.578}, //0.859-0.281=0.578 //ttZ to 859 ± 80 fb
    {"TTWJetsToQQ", 0.357}, //592fb //!!!722 ± 74 fb from SS/ML analysis
    {"TTWJetsToLNu", 0.235 },
    {"ttH_bb", 0.2897},   // 0.2897//!!!504 ± 39 fb
    {"ttH_nonbb", 0.209}, // 0.20
    {"ttWW", 0.00698},
    {"TTT", 0.0007},
    {"TTTW", 0.0013},

    //VV cross section updated
    {"wz", 50.6}, //https://arxiv.org/abs/2110.11231
    {"WZTo3LNu", 4.9173 },
    {"ww", 118.},
    {"zz", 16.5}, // ZZ
    {"WWW", 0.2086},
    {"WWZ", 0.1651},
    {"WZZ", 0.05565},
    {"ZZZ", 0.01476},

    {"st_tZq", 0.07358},
    {"st_tW_antitop", 35.85}, // 38.06
    {"st_tW_top", 35.85},     // 38.09
    {"st_schan_had", 7.67936 },
    {"st_schan_lep", 3.74},
    {"st_tchan", 136.02 },
    {"st_antitchan", 80.95},


    // GX: ttGamma, ZGamma
        {"TGJets", 1.02},
        {"ZGToLLG", 55.48},
        {"WGToLNuG", 192.0},

        // H->ZZ, WW
        {"ggH_bb", 28.3},
        {"ggH_tautau", 3.05},
        {"ggH_WW_2l", 1.10},
        {"ggH_ZZ_2l", 28.87},
        {"ggH_ZZ_4l", 0.01212},
        {"ggH_gg", 0.01},

        {"vbfH_bb", 2.20},
        // {"vbfH_nonbb", }, // This entry is commented out in Python, so it's omitted here
        {"vbfH_tautau", 0.237},
        {"vbfH_WW_2l", 0.0859},
        {"VH_nonbb", 0.942},

        {"DYJetsToLL_M-10to50", 15810.0},
        {"DYJetsToLL_M-50", 6077.22},



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
    {"TTToSemiLeptonic", 365.34},
    {"TTToHadronic", 377.96},
    {"TTTo2L2Nu", 88.29},

//from Charis: https://gitlab.cern.ch/ckoraka/vll-analysis/-/blob/master/vll/utils/crossSections.py //!not accurate
//https://docs.google.com/document/d/1yeQKEOXKdy_lsZMbwp2EbNz1h2-1TSjeGvCdiSQiQww/edit 
    { "VLL_EE_M500" , 0.004918},
    { "VLL_EN_M500" , 0.008811*1.98},
    { "VLL_NN_M500" , 0.001194*3.96},
    { "VLL_EE_M550" , 0.003158},
    { "VLL_EN_M550" , 0.005739*1.98},
    { "VLL_NN_M550" , 0.0007615*3.96},
    { "VLL_EE_M600" , 0.002079},//!
    { "VLL_EN_M600" , 0.003743*1.98},//!1.98 for EN production
    { "VLL_NN_M600" , 0.0004964*3.96},//! 3.96 for NN production
    { "VLL_EE_M650" , 0.001397 },
    { "VLL_EN_M650" , 0.002551*1.98},
    { "VLL_NN_M650" , 0.0003352*3.96},
    { "VLL_EE_M700" , 0.0009504},
    { "VLL_EN_M700" , 0.001747*1.98},
    { "VLL_NN_M700" , 0.0002255*3.96}, 
    { "VLL_EE_M750" , 0.0006623},
    { "VLL_EN_M750" , 0.001215*1.98},
    { "VLL_NN_M750" , 0.0001578*3.96},
    { "VLL_EE_M800" , 0.0004645},
    { "VLL_EN_M800" , 0.0008622*1.98},
    { "VLL_NN_M800" , 0.0001095*3.96},               
    { "VLL_EE_M850" , 0.0003267 },
    { "VLL_EN_M850" , 0.000606*1.98},
    { "VLL_NN_M850" , 7.764e-5*3.96},
    { "VLL_EE_M900" , 0.0002385},
    { "VLL_EN_M900" , 0.0004428*1.98},
    { "VLL_NN_M900" , 5.562e-5*3.96},
    { "VLL_EE_M950" , 0.0001715},
    { "VLL_EN_M950" , 0.0003206*1.98},
    { "VLL_NN_M950" , 4e-5*3.96},
    { "VLL_EE_M1000" , 0.0001241},
    { "VLL_EN_M1000" , 0.0002329*1.98},
    { "VLL_NN_M1000" , 2.909e-5*3.96},

    //2022 923.6pb; 1pb=1000fb
    //https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
    // {"TTto2L2Nu", 97.8}, //!!!to be updated, calculated with the same BR as 13TeV
    // {"TTtoLNu2Q", 404.6},
    // {"TTto4Q", 377.96	},
    //https://github.com/LPC-HH/HH4b/blob/2cf6b406d71b0a4637b483c4879613f8c8eda6ef/src/HH4b/xsecs.py#L15
    // QCD
    // also see https://indico.cern.ch/event/1324651/contributions/5576411/attachments/2713143/4711677/2023_09_14_PPD_DijetsAndPairedDijets_JECAndMCNeeds.pdf page 22
    {"QCD_PT-30to50", 112800000.0},
    {"QCD_PT-50to80", 16660000.0},
    {"QCD_PT-80to120", 2507000.0},
    {"QCD_PT-120to170", 441100.0},
    {"QCD_PT-170to300", 113400.0},
    {"QCD_PT-300to470", 7589.0},
    {"QCD_PT-470to600", 626.4},
    {"QCD_PT-600to800", 178.6},
    {"QCD_PT-800to1000", 30.57},
    {"QCD_PT-1000to1400", 8.92},
    {"QCD_PT-1400to1800", 0.8103},
    {"QCD_PT-1800to2400", 0.1148},
    {"QCD_PT-2400to3200", 0.007542},
    {"QCD_PT-3200", 0.0002331},
    // Top},
    // https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO},
    // cross check these?},
    // https://cms.cern.ch/iCMS/analysisadmin/cadilines?line=TOP-22-012},
    // {"TTto4Q", 410.89 },//923.6 * 0.667 * 0.667  // = 410.89  (762.1)},
    // {"TTto2L2Nu", 102.41},//923.6 * 0.333 * 0.333  // = 102.41 (96.9)},
    // {"TTtoLNu2Q", 410.28},//923.6 * 2 * (0.667 * 0.333)  // = 410.28 (404.0)},
    {"TTto4Q", 419.69},//923.6 * 0.6741 * 0.6741 },//branching ratio of W boson from pdg: https://pdglive.lbl.gov/Particle.action?node=S043&init=0
    {"TTto2L2Nu", 98.09},//923.6 * 0.3259 * 0.3259  ,
    {"TTtoLNu2Q", 405.80},//923.6 * 2 * (0.6741 * 0.3259) ,
    //TTTT run 3
    {"TTTT", 0.0158},
};

inline const std::map<TString, double> DeepJetM = {
    // std::map of medium WPs for DeepJet
    //https://btv-wiki.docs.cern.ch/ScaleFactors/UL2018/
    {"2016postVFP", 0.2489},
    {"2016preVFP", 0.2598},
    {"2017", 0.3040},
    {"2018", 0.2783},
    {"2022", 0.2783},
    {"2022preEE", 0.3086},
    {"2022postEE", 0.3196},
};



inline const std::map<TString, double> DeepJetT = {
    // std::map of tight WPs for DeepJet
    {"2016postVFP", 0.6377},
    {"2016preVFP", 0.6502},
    {"2017", 0.7476},
    {"2018", 0.7100},
    {"2022", 0.7100},
    {"2022preEE", 0.7183},
    {"2022postEE", 0.73},
};

inline const std::map<TString, double> DeepJetL = {
    // std::map of loose WPs for DeepJet
    {"2016postVFP", 0.0480},
    {"2016preVFP", 0.0508},
    {"2017", 0.0532},
    {"2018", 0.0490},
    {"2022", 0.0490},
    {"2022preEE", 0.0490},
    {"2022postEE", 0.0490},
};

inline const std::map<TString, double> DeepCSVL = {
    // std::map of loose WPs for DeepCSV
    {"2016postVFP", 0.1918},
    {"2016preVFP", 0.2027},
    {"2017", 0.1355},
    {"2018", 0.1208},

};

inline const std::map<TString, std::array<Double_t, 2>> particleNetBMT = {
    // https://btv-wiki.docs.cern.ch/ScaleFactors/Run3Summer22/
    {"2022preEE", {0.245, 0.6734}},
    {"2022postEE", {0.2605, 0.6915}},
};


inline const std::map<TString, std::array<TString, 5>> json_map = {
    {"2016preVFP", {"JME/2016preVFP_UL/jet_jerc.json", "TAU/2016preVFP_UL/tau.json", "BTV/2016preVFP_UL/btagging.json", "LUM/2016preVFP_UL/puWeights.json", "JME/2016preVFP_UL/jetvetomaps.json"}},
    {"2016postVFP", {"JME/2016postVFP_UL/jet_jerc.json", "TAU/2016postVFP_UL/tau.json", "BTV/2016postVFP_UL/btagging.json", "LUM/2016postVFP_UL/puWeights.json", "JME/2016postVFP_UL/jetvetomaps.json"}},
    {"2017", {"JME/2017_UL/jet_jerc.json", "TAU/2017_UL/tau.json", "BTV/2017_UL/btagging.json", "LUM/2017_UL/puWeights.json", "JME/2017_UL/jetvetomaps.json"}},
    {"2018", {"JME/2018_UL/jet_jerc.json", "TAU/2018_UL/tau.json", "BTV/2018_UL/btagging.json", "LUM/2018_UL/puWeights.json", "JME/2018_UL/jetvetomaps.json"}},
    {"2022preEE", {"JME/2022_Summer22/jet_jerc.json", "../newRun3/TAU/2022_preEE/tau_DeepTau2018v2p5_2022_preEE.json", "BTV/2018_UL/btagging.json", "LUM/2022_Summer22/puWeights.json", "JME/2022_Summer22/jetvetomaps.json"}},//!!! to be updated!!!
    {"2022postEE", {"/JME/2022_Summer22EE/jet_jerc.json", "../newRun3/TAU/2022_postEE/tau_DeepTau2018v2p5_2022_postEE.json", "BTV/2018_UL/btagging.json", "LUM/2022_Summer22EE/puWeights.json", "JME/2022_Summer22EE/jetvetomaps.json"}},//!!! to be updated!!!
};

};
#endif