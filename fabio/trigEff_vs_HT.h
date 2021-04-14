#include <map>

using namespace std;

double LUMI2016 = 35900.0;

string dir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v36_noHLTselection/";

map<string, string> file = { //MAP OF INPUT FILES

//signal
{"tttt", dir + "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn"},

//ttbar background    
{"ttbar-FH", dir + "TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8"},
{"ttbar-SL", dir + "TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8"},
{"ttbar-DL", dir + "TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8"},
//{"ttbar-incl", dir + "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8"},

//QCD background
//{"QCD_HT200to300", dir + "QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT300to500", dir + "QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT500to700", dir + "QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT700to1000", dir + "QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT1000to1500", dir + "QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT1500to2000", dir + "QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT2000toInf", dir + "QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},


//tt+X background
{"ttG-SL", dir + "TTGamma_SingleLept_TuneEE5C_13TeV-madgraph-herwigpp"},
{"ttG-DL", dir + "TTGamma_Dilept_TuneEE5C_13TeV-madgraph-herwigpp"},
{"ttW+jets", dir + "ttWJets_13TeV_madgraphMLM"},
{"ttZ+jets", dir + "ttZJets_13TeV_madgraphMLM-pythia8"},
{"ttH", dir + "ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8"},

//diboson background
{"WZ", dir + "WZ_TuneCUETP8M1_13TeV-pythia8"},
{"WW", dir + "WW_TuneCUETP8M1_13TeV-pythia8"},
{"ZZ", dir + "ZZ_TuneCUETP8M1_13TeV-pythia8"},
{"WG+jets", dir + "WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph"},
{"ZG+jets", dir + "ZGJetsToLLG_EW_LO_13TeV-sherpa"},

//triboson background
{"WWW", dir + "WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"WWZ", dir + "WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
//{"WWG", dir + "WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"ZZZ", dir + "ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"WZZ", dir + "WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"WZG", dir + "WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"WGG", dir +"WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"ZGG+jets", dir + "ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8"},

//W+jets background
//{"W+jets", dir + "WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},

//DY background
{"DY", dir + "DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1"},

//single-top background
{"tZq", dir + "tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"},
{"tW_antitop", dir + "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"},
{"tW_top", dir + "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"},
//{"tG+jets", dir + "TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8"},
{"tHW", dir + "THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8"},
{"THq", dir + "THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1"},

//Higgs background
{"VHToNonbb", dir + "VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8"},
{"ZHToTauTau", dir + "ZHToTauTau_M125_13TeV_powheg_pythia8"},
{"ZHTobb", dir + "ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8"},
{"GluGluHTo4L", dir + "GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8"},
{"GluGluHTobb", dir + "GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8"},
{"GluGluHToGG", dir + "GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8"},
{"GluGluHToMuMu", dir + "GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8"},
{"GluGluHToTauTau", dir + "GluGluHToTauTau_M125_13TeV_powheg_pythia8"},
{"GluGluHTo2L2Nu", dir + "GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8"},
{"GluGluHToLNuqq", dir + "GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8"},
{"VBFHTo2L2Nu", dir + "VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8"},
{"VBFHToMuMu", dir + "VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8"},
{"VBFHToGG", dir + "VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2"},

};

map<string, float> xsec = {
    
//signal
{"tttt", 0.01197},

//ttbar background    
{"ttbar-FH", 373.0},
{"ttbar-SL", 367.0},
{"ttbar-DL", 90.6},
//{"ttbar-incl", 830.7},

{"QCD_HT300to500", 347700.0},
{"QCD_HT500to700", 32100.0},
{"QCD_HT700to1000", 6831.0},
{"QCD_HT1000to1500", 1207.0},
{"QCD_HT1500to2000", 119.9},
{"QCD_HT2000toInf", 25.24},
    
//tt+X background
{"ttG-SL", 5.058},
{"ttG-DL", 1.506},
{"ttW+jets", 0.2014},
{"ttZ+jets", 0.6559},
{"ttH", 0.3372},

//diboson background
{"WZ", 2.343},
{"WW", 63.21},
{"ZZ", 1.016},
{"WG+jets", 1.269},
{"ZG+jets", 0.1319},

//triboson background
{"WWW", 0.2086},
{"WWZ", 0.1651},
//{"WWG", 0.2147},
{"ZZZ", 0.01398},
{"WZZ", 0.05565},
{"WZG", 0.04123},
{"WGG", 1.819},
{"ZGG+jets", 0.3717},

//W+jets background
//{"W+jets", 50300.0},

//DY background
{"DY", 1983.0},

//single-top backgroun
{"tZq", 0.07358},
{"tW_antitop", 38.06},
{"tW_top", 38.09},
//{"tG+jets", 2.967},
{"tHW", 0.1467},
{"THq", 0.8816},

//Higgs background
{"VHToNonbb", 2.137},
//{"ZHToTauTau", 0.7524},
{"ZHTobb", 0.07523},
//{"GluGluHTo4L", 2.999},
{"GluGluHTobb", 32.10},
{"GluGluHToGG", 31.98}, // cross section for ggH(bb) and ggH(gammgamma) comparable, how is this possible?
{"GluGluHToMuMu", 29.99}, // same holds for ggH(mumu)
{"GluGluHToTauTau", 30.52}, // same holds for ggH(tautau)
{"GluGluHTo2L2Nu", 30.52}, // same
{"GluGluHToLNuqq", 29.99},
{"VBFHTo2L2Nu", 3.769},
{"VBFHToMuMu", 0.000823}, //there's no such a big difference in xsec between ggH(mumu) and VBF(mumu) production mechanisms 
{"VBFHToGG", 3.992},

};

void writeTEfficiency(TH1F* hBef, TH1F* hAFt, TString name);
void writeTEfficiency2D(TH2F* hBef, TH2F* hAFt, TString name);
