#include <map>
#include <TEfficiency.h>

using namespace std;

string dir = "/publicfs/cms/user/fabioiemmi/v20_checkforv19/NoJEC/";

map<string, string> file = { //MAP OF INPUT FILES
    
//signal
{"tttt", dir + "TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root"},

//ttbar background    
{"tt", dir + "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8.root"},
    
//tt+X background
{"ttG+jets", dir + "TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root"},
{"ttW+jets", dir + "ttWJets_13TeV_madgraphMLM.root"},
{"ttZ+jets", dir + "ttZJets_13TeV_madgraphMLM-pythia8.root"},
{"ttH", dir + "ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root"},

//diboson background
{"WZ", dir + "WZ_TuneCUETP8M1_13TeV-pythia8.root"},
{"WWTo2L2Nu", dir + "WWTo2L2Nu_DoubleScattering_13TeV-pythia8.root"},
{"WpWpJJ", dir + "WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root"}, //WHAT'S THIS PROCESS?
{"ZZ", dir + "ZZ_TuneCUETP8M1_13TeV-pythia8.root"},
{"WG+jets", dir + "WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root"},
{"ZG+jets", dir + "ZGJetsToLLG_EW_LO_13TeV-sherpa.root"},

//triboson background
{"WWW", dir + "WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root"},
{"WWZ", dir + "WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root"},
{"WWG", dir + "WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root"},
{"ZZZ", dir + "ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root"},
{"WZZ", dir + "WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root"},
{"WZG", dir + "WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root"},
{"WGG", dir +"WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root"},
{"ZGG+jets", dir + "ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8.root"},

//W+jets background
{"W+jets", dir + "WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"},

//DY background
{"DY", dir + "DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1.root"},

//single-top background
{"tZq", dir + "tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8.root"},
{"tW_antitop", dir + "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root"},
{"tW_top", dir + "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root"},
{"tG+jets", dir + "TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root"},
{"tHW", dir + "THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8.root"},
{"THq", dir + "THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1.root"},

//Higgs background
{"VHToNonbb", dir + "VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8.root"},
{"ZHToTauTau", dir + "ZHToTauTau_M125_13TeV_powheg_pythia8.root"},
{"ZHTobb", dir + "ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8.root"},
{"GluGluHTo4L", dir + "GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8.root"},
{"GluGluHTobb", dir + "GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.root"},
{"GluGluHToGG", dir + "GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root"},
{"GluGluHToMuMu", dir + "GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root"},
{"GluGluHToTauTau", dir + "GluGluHToTauTau_M125_13TeV_powheg_pythia8.root"},
{"GluGluHTo2L2Nu", dir + "GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8.root"},
{"GluGluHToLNuqq", dir + "GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8.root"},
{"VBFHTo2L2Nu", dir + "VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8.root"},
{"VBFHToMuMu", dir + "VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root"},
{"VBFHToGG", dir + "VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2.root"},

};

double recoEff_1tau1e;
double recoEff_1tau1mu;

map<string, TEfficiency> eff_pt_1tau1e;
map<string, TEfficiency> eff_pt_1tau1mu;
