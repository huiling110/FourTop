#include <map>

using namespace std;

string MUOSF_dir = "/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/fabio/UltraLegacy/scale_factors/muons/";
map<string, string> MUOSF_files = { //MAP OF INPUT MUO SCALE FACTOR FILES                                                                                                                                                            

    {"UL2016_preVFP", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2016_UL_preVFP_ID.root"},
    {"UL2016_postVFP", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2016_UL_postVFP_ID.root"},
    {"UL2017", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root"},
    {"UL2018", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root"},

};

string BTVSF_dir = "/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/fabio/UltraLegacy/scale_factors/btagging/";
map<string, string> BTVSF_files = { //MAP OF INPUT BTV SCALE FACTOR FILES                                                                                                                                                            

    {"UL2016_preVFP", BTVSF_dir + "reshaping_deepJet_106XUL16preVFP_v2.csv"},
    {"UL2016_postVFP", BTVSF_dir + "reshaping_deepJet_106XUL16postVFP_v3.csv"},
    {"UL2017", BTVSF_dir + "reshaping_deepJet_106XUL17_v3.csv"},
    {"UL2018", BTVSF_dir + "reshaping_deepJet_106XUL18_v2.csv"},

};

map<string, string> file = { //MAP OF INPUT FILES

//signal

//{"tttt", "tttt"},

//ttbar background    
//{"ttbar-FH", "ttbar_0l"},
{"ttbar-SL", "ttbar_1l"},
//{"ttbar-DL", "TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8"},
//{"ttbar-incl", "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8"},

/*
//QCD background
//{"QCD_HT200to300", "QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT300to500", "QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT500to700", "QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT700to1000", "QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT1000to1500", "QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT1500to2000", "QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT2000toInf", "QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},


//tt+X background
//{"ttG-SL", "TTGamma_SingleLept_TuneEE5C_13TeV-madgraph-herwigpp"},
//{"ttG-DL", "TTGamma_Dilept_TuneEE5C_13TeV-madgraph-herwigpp"},
{"ttW+jets", "ttWJets_13TeV_madgraphMLM"},
{"ttZ+jets", "ttZJets_13TeV_madgraphMLM-pythia8"},
{"ttG+jets", "TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"},
{"ttH", "ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8"},
*/
/*
//diboson background
{"WZ", "WZ_TuneCUETP8M1_13TeV-pythia8"},
{"WW", "WW_TuneCUETP8M1_13TeV-pythia8"},
{"ZZ", "ZZ_TuneCUETP8M1_13TeV-pythia8"},
{"WG+jets", "WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph"},
{"ZG+jets", "ZGJetsToLLG_EW_LO_13TeV-sherpa"},

//triboson background
{"WWW", "WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"WWZ", "WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
//{"WWG", "WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"ZZZ", "ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"WZZ", "WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"WZG", "WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"WGG", dir +"WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8"},
{"ZGG+jets", "ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8"},

//W+jets background
//{"W+jets", "WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},

//DY background
{"DY", "DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1"},

//single-top background
{"tZq", "tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"},
{"tW_antitop", "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"},
{"tW_top", "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"},
//{"tG+jets", "TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8"},
{"tHW", "THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8"},
{"THq", "THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1"},

//Higgs background
{"VHToNonbb", "VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8"},
{"ZHToTauTau", "ZHToTauTau_M125_13TeV_powheg_pythia8"},
{"ZHTobb", "ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8"},
{"GluGluHTo4L", "GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8"},
{"GluGluHTobb", "GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8"},
{"GluGluHToGG", "GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8"},
{"GluGluHToMuMu", "GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8"},
{"GluGluHToTauTau", "GluGluHToTauTau_M125_13TeV_powheg_pythia8"},
{"GluGluHTo2L2Nu", "GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8"},
{"GluGluHToLNuqq", "GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8"},
{"VBFHTo2L2Nu", "VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8"},
{"VBFHToMuMu", "VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8"},
{"VBFHToGG", "VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2"},
*/
/*
{"data_singleMuon_eraB_0", "SingleMuonB_0"},
{"data_singleMuon_eraB_1", "SingleMuonB_1"},
{"data_singleMuon_eraC_0", "SingleMuonC_0"},
{"data_singleMuon_eraD_0", "SingleMuonD_0"},
{"data_singleMuon_eraE_0", "SingleMuonE_0"},
{"data_singleMuon_eraF_0", "SingleMuonF_0"},
{"data_singleMuon_eraG_0", "SingleMuonG_0"},
{"data_singleMuon_eraG_1", "SingleMuonG_1"},
{"data_singleMuon_eraH_0", "SingleMuonH_0"},
{"data_singleMuon_eraH_1", "SingleMuonH_1"},
*/

};

void writeTEfficiency(TH1F* hBef, TH1F* hAFt, map<string, string>::iterator file_it, TString name);
void writeTEfficiency2D(TH2F* hBef, TH2F* hAFt, map<string, string>::iterator file_it, TString name);
