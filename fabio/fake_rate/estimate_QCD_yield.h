#include <map>

using namespace std;

double LUMI2016 = 35900.0;

string dir = "/publicfs/cms/user/fabioiemmi/TauOfTTTT/v45_yieldsCrosscheck_presel2jets_PFJet450required/";

map<string, string> file = { //MAP OF INPUT FILES
   
//QCD background

{"QCD_HT200to300", dir + "QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT300to500", dir + "QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT500to700", dir + "QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT700to1000", dir + "QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT1000to1500", dir + "QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT1500to2000", dir + "QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
{"QCD_HT2000toInf", dir + "QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"},
 
/*		
//ttbar background    
{"ttbar-FH", dir + "TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8"},
{"ttbar-SL", dir + "TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8"},
{"ttbar-DL", dir + "TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8"},
	
//tt+X background
{"ttW+jets", dir + "ttWJets_13TeV_madgraphMLM"},
{"ttZ+jets", dir + "ttZJets_13TeV_madgraphMLM-pythia8"},
{"ttG+jets", dir + "TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"},
{"ttH", dir + "ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8"},
*/
/*
//data
{"JetHT_B0", dir + "JetHTB_0"},
{"JetHT_B1", dir + "JetHTB_1"},
{"JetHT_C", dir + "JetHTC_0"},
{"JetHT_D", dir + "JetHTD_0"},
{"JetHT_E", dir + "JetHTE_0"},
{"JetHT_F", dir + "JetHTF_0"},
{"JetHT_G0", dir + "JetHTG_0"},
{"JetHT_G1", dir + "JetHTG_1"},
{"JetHT_H0", dir + "JetHTH_0"},
{"JetHT_H1", dir + "JetHTH_1"},
*/
};

map<string, float> xsec = { //MAP OF CROSS SECTIONS
	
//QCD background
{"QCD_HT200to300", 1721000.0},
{"QCD_HT300to500", 347700.0},
{"QCD_HT500to700", 32100.0},
{"QCD_HT700to1000", 6831.0},
{"QCD_HT1000to1500", 1207.0},
{"QCD_HT1500to2000", 119.9},
{"QCD_HT2000toInf", 25.24},
/*	
//ttbar background    
{"ttbar-FH", 373.0},
{"ttbar-SL", 367.0},
{"ttbar-DL", 90.6},

//tt+X background
{"ttW+jets", 0.2014},
{"ttZ+jets", 0.6559},
{"ttG+jets", 3.697},
{"ttH", 0.3372},
*/
/*
//data
{"JetHT_B0", dir + "JetHTB_0"},
{"JetHT_B1", dir + "JetHTB_1"},
{"JetHT_C", dir + "JetHTC_0"},
{"JetHT_D", dir + "JetHTD_0"},
{"JetHT_E", dir + "JetHTE_0"},
{"JetHT_F", dir + "JetHTF_0"},
{"JetHT_G0", dir + "JetHTG_0"},
{"JetHT_G1", dir + "JetHTG_1"},
{"JetHT_H0", dir + "JetHTH_0"},
{"JetHT_H1", dir + "JetHTH_1"},
*/
};

void writeHisto(TH1F* histo, map<string, string>::iterator file_it);
void writeTEfficiency(TH1F* hBef, TH1F* hAft, map<string, string>::iterator file_it,  TString name);
