#include <map>

using namespace std;

double LUMI2016 = 35900.0;

string dir = "/publicfs/cms/user/fabioiemmi/TauOfTTTT/v46_noBJetsInPresel_forPSEFs/";
//string dir = "/publicfs/cms/user/fabioiemmi/TauOfTTTT/v45_yieldsCrosscheck_presel2jets_PFJet450required/";

map<string, string> file = { //MAP OF INPUT FILES

//signal
{"tttt", dir + "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn"},

//ttbar background    
{"ttbar-FH", dir + "TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8"},
{"ttbar-SL", dir + "TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8"},
{"ttbar-DL", dir + "TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8"},

//QCD background
{"QCD_HT200to300", dir + "QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT300to500", dir + "QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT500to700", dir + "QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT700to1000", dir + "QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT1000to1500", dir + "QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT1500to2000", dir + "QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT2000toInf", dir + "QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},

//tt+X background
{"ttW+jets", dir + "ttWJets_13TeV_madgraphMLM"},
{"ttZ+jets", dir + "ttZJets_13TeV_madgraphMLM-pythia8"},
{"ttG+jets", dir + "TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"},
{"ttH", dir + "ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8"},

//single-top background
{"ST_antitopW", dir + "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"},
{"ST_topW", dir + "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"},
{"tZq_ll", dir + "tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"},
{"tZq_nunu", dir + "tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1"},

//Single Higgs background
{"ggHTobb", dir + "GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8"},
{"ggHToWWToLNuQQ", dir + "GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8"},
{"ggHToWWTo2L2Nu", dir + "GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8"},
{"ggHToTauTau", dir + "GluGluHToTauTau_M125_13TeV_powheg_pythia8"},
{"ggHToGammaGamma", dir + "GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8"},
{"ggHToMuMu", dir + "GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8"},
{"VBFHTobb", dir + "VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix"},
{"VBFHToWWTo2L2Nu", dir + "VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8"},
{"VBFHToZZTo4L", dir + "VBF_HToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8"},
{"VBFHToTauTau", dir + "VBFHToTauTau_M125_13TeV_powheg_pythia8"},
{"VBFHToGammaGamma", dir + "VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2"},
{"VBFHToMuMu", dir + "VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8"},

};

map<string, float> xsec = {
    
//signal
{"tttt", 0.01197},

//ttbar background    
{"ttbar-FH", 373.0},
{"ttbar-SL", 367.0},
{"ttbar-DL", 90.6},

{"QCD_HT200to300", 1721000.0},
{"QCD_HT300to500", 347700.0},
{"QCD_HT500to700", 32100.0},
{"QCD_HT700to1000", 6831.0},
{"QCD_HT1000to1500", 1207.0},
{"QCD_HT1500to2000", 119.9},
{"QCD_HT2000toInf", 25.24},
    
//tt+X background
{"ttW+jets", 0.2014},
{"ttZ+jets", 0.6559},
{"ttG+jets", 3.697},
{"ttH", 0.3372},

//single top background
{"ST_antitopW", 38.09},
{"ST_topW", 38.09},
{"tZq_ll", 0.0736},
{"tZq_nunu", 0.1379}, //how is it possible that this cross section is bigger than tZq_ll?!?

//Single Higgs background
{"ggHTobb", 28.19}, //did not find a cross section for this in McM; took the nominal cross section for ggH from PDG and multiplied by the H(bb) branching fraction
{"ggHToWWToLNuQQ", 4.10},
{"ggHToWWTo2L2Nu", 0.92},
{"ggHToTauTau", 3.1}, 
{"ggHToGammaGamma", 0.11},
{"ggHToMuMu", 0.011},
{"VBFHTobb", 2.19},
{"VBFHToWWTo2L2Nu", 0.071},
{"VBFHToZZTo4L", 0.000796},
{"VBFHToTauTau", 0.24},
{"VBFHToGammaGamma", 0.00858},
{"VBFHToMuMu", 0.000824},

};

void writeHisto(TH1F* histo, map<string, string>::iterator file_it);
