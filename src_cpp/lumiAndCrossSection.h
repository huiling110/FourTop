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
    {"TTZToQQ", 0.578}, //0.859-0.281=0.578
    {"TTWJetsToQQ", 0.357}, //592fb
    {"TTWJetsToLNu", 0.235 },
    {"ttH_bb", 0.2897},   // 0.2897
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
inline const std::map<TString, std::map<TString, double>> genSumDic = {
//obsolete
        {"2018",{
            {"ttW", 27686900.0},
            {"qcd_2000toInf", 5374710.0},
            {"qcd_200to300", 57336600.0},
            {"st_tW_top", 258137000.0},
            {"WJetsToLNu_HT-200To400", 58225600.0},
            {"WJetsToLNu_HT-400To600", 7444030.0},
            {"WJetsToLNu_HT-1200To2500", 6481520.0},
            {"qcd_1000to1500", 14394800.0},
            {"WJetsToLNu_HT-2500ToInf", 2097650.0},
            {"qcd_300to500", 61609700.0},
            {"qcd_50to100", 38599400.0},
            {"tttt", 106025.0},
            {"qcd_1500to2000", 10411800.0},
            {"ttbar_0l", 104910000000.0},
            {"ttbar_2l", 10457600000.0},
            {"ttH_nonbb", 9281200.0},
            {"WJetsToLNu_HT-600To800", 7718760.0},
            {"st_tW_antitop", 251902000.0},
            {"st_tZq", 924059.0},
            {"ttH_bb", 9451720.0},
            {"ww", 15679100.0},
            {"zz", 3526000.0},
            {"ttG", 27849500.0},
            {"qcd_700to1000", 48506800.0},
            {"wz", 7940000.0},
            {"qcd_500to700", 49184800.0},
            {"ttbar_1l", 143354000000.0},
            {"WJetsToLNu_HT-800To1200", 7306190.0},
            {"ttZ", 32793800.0},
            {"TTToSemiLeptonic", 1.35336e+12},// only for BDT training in 1tau1l and 1tau2l
            {"TTToHadronic", 7.16154e+11},
            {"TTTo2L2Nu", 9.77873e+10},
            {"VLL_EE_M900", 28.573285710000004},
            {"VLL_NN_M750", 18.732711000000002},
            {"VLL_NN_M950", 4.80302336},
            {"VLL_NN_M900", 6.61964497},
            {"VLL_EN_M800", 102.43406055000003},
            {"VLL_EE_M500", 591.1833100000001},
            {"VLL_NN_M550", 91.49154300000001},
            {"VLL_EE_M650", 166.88674399999996},
            {"VLL_EN_M750", 145.86020320000003},
            {"VLL_EN_M700", 209.162717},
            {"VLL_NN_M600", 59.591204000000005},
            {"VLL_NN_M850", 9.260824567},
            {"VLL_NN_M500", 143.230307},
            {"VLL_EN_M1000", 28.1200414},
            {"VLL_EN_M850", 72.9743729},
            {"VLL_EN_M600", 451.93825000000015},
            {"VLL_EE_M950", 20.55407540000001},
            {"VLL_EE_M800", 55.58882853},
            {"VLL_NN_M800", 13.16760272},
            {"VLL_EE_M750", 79.043692},
            {"VLL_EN_M650", 305.767699},
            {"VLL_EN_M500", 1063.7767100000003},
            {"VLL_EN_M900", 53.19825936},
            {"VLL_EE_M550", 378.49510999999995},
            {"VLL_NN_M700", 27.080457},
            {"VLL_EN_M550", 589.06433},
            {"VLL_EE_M850", 39.047127379999985},
            {"VLL_EN_M950", 38.63094899999999},
            {"VLL_EE_M1000", 14.825747},
            {"VLL_NN_M650", 40.048385},
            {"VLL_EE_M600", 248.85666000000006},
            {"VLL_EE_M700", 113.842985},
            {"VLL_NN_M1000", 3.4763252000000002},
            }
        },
        {"2017",{
            {"ttW", 27662100.0},
            {"qcd_2000toInf", 4112570.0},
            {"qcd_200to300", 42714400.0},
            {"st_tW_top", 183285000.0},
            {"WJetsToLNu_HT-200To400", 42282000.0},
            {"WJetsToLNu_HT-400To600", 5468470.0},
            {"WJetsToLNu_HT-1200To2500", 4752120.0},
            {"qcd_1000to1500", 10186700.0},
            {"WJetsToLNu_HT-2500ToInf", 1185700.0},
            {"qcd_300to500", 43430000.0},
            {"qcd_50to100", 26243000.0},
            {"tttt", 84047.0},
            {"qcd_1500to2000", 7701880.0},
            {"ttbar_0l", 73140800000.0},
            {"ttbar_2l", 7695840000.0},
            {"ttH_nonbb", 2540300.0},
            {"WJetsToLNu_HT-600To800", 5545300.0},
            {"st_tW_antitop", 184446000.0},
            {"st_tZq", 737624.0},
            {"ttH_bb", 9041280.0},
            {"ww", 15634100.0},
            {"zz", 2706000.0},
            {"ttG", 22157600.0},
            {"qcd_700to1000", 32934800.0},
            {"wz", 7889000.0},
            {"qcd_500to700", 36194900.0},
            {"ttbar_1l", 104130000000.0},
            {"WJetsToLNu_HT-800To1200", 5088480.0},
            {"ttZ", 31791100.0},
            //!!!VLL gen sum to be added
            {"VLL_EE_M900", 28.531111350000007},
            {"VLL_NN_M750", 18.735795400000004},
            {"VLL_NN_M950", 4.8058968},
            {"VLL_NN_M900", 6.6221903200000005},
            {"VLL_EN_M800", 103.08791407000004},
            {"VLL_EE_M500", 590.91246},
            {"VLL_NN_M550", 91.59974000000004},
            {"VLL_EE_M650", 167.013711},
            {"VLL_EN_M750", 145.74635829999997},
            {"VLL_EN_M700", 209.078184},
            {"VLL_NN_M600", 59.602622},
            {"VLL_NN_M850", 9.262065475},
            {"VLL_NN_M500", 143.329161},
            {"VLL_EN_M1000", 28.115439600000002},
            {"VLL_EN_M850", 71.15131263},
            {"VLL_EN_M600", 452.23478900000003},
            {"VLL_EE_M950", 20.563359700000007},
            {"VLL_EE_M800", 55.582718570000004},
            {"VLL_NN_M800", 13.182733380000002},
            {"VLL_EE_M750", 79.01594231},
            {"VLL_EN_M650", 306.006186},
            {"VLL_EN_M500", 1066.2598600000001},
            {"VLL_EN_M900", 53.17661183},
            {"VLL_EE_M550", 377.9963},
            {"VLL_NN_M700", 27.094814},
            {"VLL_EN_M550", 687.32731},
            {"VLL_EE_M850", 39.0504977},
            {"VLL_EN_M950", 38.62177010000002},
            {"VLL_EE_M1000", 14.839104000000003},
            {"VLL_NN_M650", 40.066835},
            {"VLL_EE_M600", 248.6551},
            {"VLL_EE_M700", 114.04829200000003},
            {"VLL_NN_M1000", 3.4867113999999995},
            }
        },
        {"2016postVFP",{//! to be updated
            {"ttW", 27662100.0},
            {"qcd_2000toInf", 4112570.0},
            {"qcd_200to300", 42714400.0},
            {"st_tW_top", 183285000.0},
            {"WJetsToLNu_HT-200To400", 42282000.0},
            {"WJetsToLNu_HT-400To600", 5468470.0},
            {"WJetsToLNu_HT-1200To2500", 4752120.0},
            {"qcd_1000to1500", 10186700.0},
            {"WJetsToLNu_HT-2500ToInf", 1185700.0},
            {"qcd_300to500", 43430000.0},
            {"qcd_50to100", 26243000.0},
            {"tttt", 84047.0},
            {"qcd_1500to2000", 7701880.0},
            {"ttbar_0l", 73140800000.0},
            {"ttbar_2l", 7695840000.0},
            {"ttH_nonbb", 2540300.0},
            {"WJetsToLNu_HT-600To800", 5545300.0},
            {"st_tW_antitop", 184446000.0},
            {"st_tZq", 737624.0},
            {"ttH_bb", 9041280.0},
            {"ww", 15634100.0},
            {"zz", 2706000.0},
            {"ttG", 22157600.0},
            {"qcd_700to1000", 32934800.0},
            {"wz", 7889000.0},
            {"qcd_500to700", 36194900.0},
            {"ttbar_1l", 104130000000.0},
            {"WJetsToLNu_HT-800To1200", 5088480.0},
            {"ttZ", 31791100.0},
            //!!!VLL gen sum to be added
            {"VLL_EE_M900", 13.116411556060003},
            {"VLL_NN_M750", 8.622703928999996},
            {"VLL_NN_M950", 2.2103802568600006},
            {"VLL_NN_M900", 3.04826023218},
            {"VLL_EN_M800", 47.4851478831},
            {"VLL_EE_M500", 271.84425888000004},
            {"VLL_NN_M550", 42.040172326000004},
            {"VLL_EE_M650", 76.79798925000001},
            {"VLL_EN_M750", 67.024067793},
            {"VLL_EN_M700", 96.02996642700002},
            {"VLL_NN_M600", 27.41190867200001},
            {"VLL_NN_M850", 4.25489071197},
            {"VLL_NN_M500", 65.85715078700002},
            {"VLL_EN_M1000", 12.722034969100001},
            {"VLL_EN_M850", 33.56998965300001},
            {"VLL_EN_M600", 207.942277127},
            {"VLL_EE_M950", 9.449668038000002},
            {"VLL_EE_M800", 25.570716290100002},
            {"VLL_NN_M800", 6.053268028500001},
            {"VLL_EE_M750", 36.31690842},
            {"VLL_EN_M650", 140.48246943600003},
            {"VLL_EN_M500", 490.4631494899999},
            {"VLL_EN_M900", 24.43846516779},
            {"VLL_EE_M550", 174.18510775},
            {"VLL_NN_M700", 12.482674859999998},
            {"VLL_EN_M550", 316.43777271000016},
            {"VLL_EE_M850", 17.960245108600002},
            {"VLL_EN_M950", 17.765286906},
            {"VLL_EE_M1000", 6.818253648},
            {"VLL_NN_M650", 18.449171970000002},
            {"VLL_EE_M600", 114.39435253000005},
            {"VLL_EE_M700", 52.35445601699999},
            {"VLL_NN_M1000", 1.5998133724},
            }
        },
        {"2016preVFP",{//! to be updated
            {"ttW", 27662100.0},
            {"qcd_2000toInf", 4112570.0},
            {"qcd_200to300", 42714400.0},
            {"st_tW_top", 183285000.0},
            {"WJetsToLNu_HT-200To400", 42282000.0},
            {"WJetsToLNu_HT-400To600", 5468470.0},
            {"WJetsToLNu_HT-1200To2500", 4752120.0},
            {"qcd_1000to1500", 10186700.0},
            {"WJetsToLNu_HT-2500ToInf", 1185700.0},
            {"qcd_300to500", 43430000.0},
            {"qcd_50to100", 26243000.0},
            {"tttt", 84047.0},
            {"qcd_1500to2000", 7701880.0},
            {"ttbar_0l", 73140800000.0},
            {"ttbar_2l", 7695840000.0},
            {"ttH_nonbb", 2540300.0},
            {"WJetsToLNu_HT-600To800", 5545300.0},
            {"st_tW_antitop", 184446000.0},
            {"st_tZq", 737624.0},
            {"ttH_bb", 9041280.0},
            {"ww", 15634100.0},
            {"zz", 2706000.0},
            {"ttG", 22157600.0},
            {"qcd_700to1000", 32934800.0},
            {"wz", 7889000.0},
            {"qcd_500to700", 36194900.0},
            {"ttbar_1l", 104130000000.0},
            {"WJetsToLNu_HT-800To1200", 5088480.0},
            {"ttZ", 31791100.0},
            //!!!VLL gen sum to be added
            {"VLL_EE_M900", 15.43261461896},
            {"VLL_NN_M750", 8.42797953003},
            {"VLL_NN_M950", 2.5915737809},
            {"VLL_NN_M900", 3.5778239246100005},
            {"VLL_EN_M800", 55.69181120490001},
            {"VLL_EE_M500", 314.74949720000006},
            {"VLL_NN_M550", 49.368219},
            {"VLL_EE_M650", 90.00829099999999},
            {"VLL_EN_M750", 78.7096950794},
            {"VLL_EN_M700", 112.88255453100001},
            {"VLL_NN_M600", 30.370673760000003},
            {"VLL_NN_M850", 4.997422227080001},
            {"VLL_NN_M500", 77.39741635600001},
            {"VLL_EN_M1000", 15.1919066411},
            {"VLL_EN_M850", 39.461730310590006},
            {"VLL_EN_M600", 244.74249992},
            {"VLL_EE_M950", 11.102484278},
            {"VLL_EE_M800", 30.008244078040004},
            {"VLL_NN_M800", 6.994936238940001},
            {"VLL_EE_M750", 42.599120896},
            {"VLL_EN_M650", 165.02878423999996},
            {"VLL_EN_M500", 576.0895128000002},
            {"VLL_EN_M900", 28.718469362280008},
            {"VLL_EE_M550", 204.2833324},
            {"VLL_NN_M700", 14.616048658000002},
            {"VLL_EN_M550", 371.32015539},
            {"VLL_EE_M850", 21.14188547982},
            {"VLL_EN_M950", 20.8493515734},
            {"VLL_EE_M1000", 8.017708587},
            {"VLL_NN_M650", 21.635039940000002},
            {"VLL_EE_M600", 134.57756321999997},
            {"VLL_EE_M700", 61.531126019999995},
            {"VLL_NN_M1000", 1.8790077074000004},
            }
        },
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