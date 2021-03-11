#include <map>

using namespace std;

double LUMI2016 = 35900.0;

//string dir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v31_fixedLeptonBug/";
string dir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v32_addedalleventsTree/";

map<string, string> file = { //MAP OF INPUT FILES
    
//signal
{"tttt", dir + "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn"},

//ttbar background    
{"tt", dir + "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8"},
/*    
//tt+X background
{"ttG+jets", dir + "TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"},
{"ttW+jets", dir + "ttWJets_13TeV_madgraphMLM"},
{"ttZ+jets", dir + "ttZJets_13TeV_madgraphMLM-pythia8"},
{"ttH", dir + "ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8"},

//diboson background
{"WZ", dir + "WZ_TuneCUETP8M1_13TeV-pythia8"},
{"WWTo2L2Nu", dir + "WWTo2L2Nu_DoubleScattering_13TeV-pythia8"},
{"WpWpJJ", dir + "WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8"}, //WHAT'S THIS PROCESS?
{"ZZ", dir + "ZZ_TuneCUETP8M1_13TeV-pythia8"},
{"WG+jets", dir + "WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph"},
{"ZG+jets", dir + "ZGJetsToLLG_EW_LO_13TeV-sherpa"},

//triboson background
{"WWW", dir + "WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"WWZ", dir + "WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"WWG", dir + "WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"ZZZ", dir + "ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"WZZ", dir + "WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"WZG", dir + "WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"WGG", dir +"WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"ZGG+jets", dir + "ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8"},

//W+jets background
{"W+jets", dir + "WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},

//DY background
{"DY", dir + "DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1"},

//single-top background
{"tZq", dir + "tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"},
{"tW_antitop", dir + "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"},
{"tW_top", dir + "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"},
{"tG+jets", dir + "TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8"},
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
*/
};


map<string, TH1F> y_1tau0L; // store histos here
map<string, TH1F> y_1tau1e;
map<string, TH1F> y_1tau1mu;
map<string, TH1F> y_1tau2L;
map<string, TH1F> y_1tau3L;
map<string, TH1F> y_2tau0L;
map<string, TH1F> y_2tau1e;
map<string, TH1F> y_2tau1mu;
map<string, TH1F> y_2tau2L;

map<string, TH1F> total_weight;
