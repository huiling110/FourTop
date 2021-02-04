#include <iostream>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TBenchmark.h>
#include "trigEff.h"

//using namespace std;

void trigEff(TString setup) {

gBenchmark->Start("running time");

map<string, string>::iterator file_it = file.begin();

while (file_it != file.end()) { //////////////////////// LOOP OVER FILES ///////////////////////

cout << "Opening file " << file_it->second << "..." << endl;
TFile *inputfile  = new TFile( file_it->second.c_str(), "READ" );

//addressing branches
TTree *evt = (TTree*)inputfile->Get( "tree" );

int  mytausT_number = 0;
evt->SetBranchAddress( "tausT_number", &mytausT_number );

int  myleptonsMVAT_number = 0;
evt->SetBranchAddress( "leptonsMVAT_number", &myleptonsMVAT_number );

int  myjetsL_number = 0;
evt->SetBranchAddress( "jetsL_number", &myjetsL_number );

int  mybjetsM_number = 0;
evt->SetBranchAddress( "bjetsM_num", &mybjetsM_number );

int  myelesMVAT_number = 0;
evt->SetBranchAddress( "elesMVAT_number", &myelesMVAT_number );

int  mymuonsT_number = 0;
evt->SetBranchAddress( "muonsT_number", &mymuonsT_number );

int  myleptonsMVAT_2OS = 0;
evt->SetBranchAddress( "leptonsMVAT_2OS", &myleptonsMVAT_2OS );

int  myleptonsMVAT_2SS = 0;
evt->SetBranchAddress( "leptonsMVAT_2SS", &myleptonsMVAT_2SS );

double mygenEvtWeight = 0;
evt->SetBranchAddress( "EVENT_genWeight", &mygenEvtWeight );

vector<double> * myeleMVAT_pt = 0;
evt->SetBranchAddress( "eleMVAT_pt", &myeleMVAT_pt );

vector<double> * mymuonT_pt = 0;
evt->SetBranchAddress( "muonT_pt", &mymuonT_pt );

double myjetsL_1pt = 0;
evt->SetBranchAddress("jetsL_1pt", &myjetsL_1pt);

double myjetsL_2pt = 0;
evt->SetBranchAddress("jetsL_2pt", &myjetsL_2pt);

double myjetsL_3pt = 0;
evt->SetBranchAddress("jetsL_3pt", &myjetsL_3pt);

double myjetsL_4pt = 0;
evt->SetBranchAddress("jetsL_4pt", &myjetsL_4pt);

double myjetsL_5pt = 0;
evt->SetBranchAddress("jetsL_5pt", &myjetsL_5pt);

double myjetsL_6pt = 0;
evt->SetBranchAddress("jetsL_6pt", &myjetsL_6pt);

double myjetsL_7pt = 0;
evt->SetBranchAddress("jetsL_7pt", &myjetsL_7pt);

double myjetsL_8pt = 0;
evt->SetBranchAddress("jetsL_8pt", &myjetsL_8pt);

double myjetsL_9pt = 0;
evt->SetBranchAddress("jetsL_9pt", &myjetsL_9pt);

double myjetsL_10pt = 0;
evt->SetBranchAddress("jetsL_10pt", &myjetsL_10pt);

double myjetsL_11pt = 0;
evt->SetBranchAddress("jetsL_11pt", &myjetsL_11pt);

double myjetsL_HT = 0;
evt->SetBranchAddress("jetsL_HT", &myjetsL_HT);

 // multijet triggers

 int myHLT_PFHT450_SixJet40_BTagCSV_p056 = 0;
evt->SetBranchAddress("HLT_PFHT450_SixJet40_BTagCSV_p056", &myHLT_PFHT450_SixJet40_BTagCSV_p056);

 int myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = 0;
evt->SetBranchAddress("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056", &myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056);

 // single electron triggers

 int myHLT_Ele25_eta2p1_WPTight_Gsf = 0;
 evt->SetBranchAddress("HLT_Ele25_eta2p1_WPTight_Gsf", &myHLT_Ele25_eta2p1_WPTight_Gsf);

 int myHLT_Ele27_WPTight_Gsf = 0;
 evt->SetBranchAddress("HLT_Ele27_WPTight_Gsf", &myHLT_Ele27_WPTight_Gsf);

 int myHLT_Ele27_eta2p1_WPLoose_Gsf = 0;
 evt->SetBranchAddress("HLT_Ele27_eta2p1_WPLoose_Gsf", &myHLT_Ele27_eta2p1_WPLoose_Gsf);

 // electron + tau cross triggers

 int myHLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20 = 0;
 evt->SetBranchAddress("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20", &myHLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20);

 int myHLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1 = 0;
 evt->SetBranchAddress("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1", &myHLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1);

 int myHLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30 = 0;
 evt->SetBranchAddress("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30", &myHLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30);

 // single muon triggers

 int myHLT_IsoMu22 = 0;
 evt->SetBranchAddress("HLT_IsoMu22", &myHLT_IsoMu22);

 int myHLT_IsoTkMu22 = 0;
 evt->SetBranchAddress("HLT_IsoTkMu22", &myHLT_IsoTkMu22);

 int myHLT_IsoMu22_eta2p1 = 0;
 evt->SetBranchAddress("HLT_IsoMu22_eta2p1", &myHLT_IsoMu22_eta2p1);

 int myHLT_IsoTkMu22_eta2p1 = 0;
 evt->SetBranchAddress("HLT_IsoTkMu22_eta2p1", &myHLT_IsoTkMu22_eta2p1);

 int myHLT_IsoMu24 = 0;
 evt->SetBranchAddress("HLT_IsoMu24", &myHLT_IsoMu24);

 int myHLT_IsoTkMu24 = 0;
 evt->SetBranchAddress("HLT_IsoTkMu24", &myHLT_IsoTkMu24);

 // muon + tau cross triggers

 int myHLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1 = 0;
 evt->SetBranchAddress("HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1", &myHLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1);

 // double electron triggers
 
 int myHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = 0;
 evt->SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &myHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);

 // double muon triggers

 int myHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL = 0;
 evt->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL", &myHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL);

 int myHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = 0;
 evt->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ", &myHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);

 int myHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL = 0;
 evt->SetBranchAddress("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL", &myHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL);

 int myHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = 0;
 evt->SetBranchAddress("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ", &myHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ);

 // electron plus muon triggers

 int myHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL = 0;
 evt->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &myHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);

 int myHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = 0;
 evt->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &myHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);

 int myHLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL = 0;
 evt->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL", &myHLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL);
 
 int myHLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ = 0;
 evt->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ", &myHLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ);

 int myHLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = 0;
 evt->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &myHLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);

 int myHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = 0;
 evt->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &myHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);

 // triple lepton triggers

 int myHLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL = 0;
 evt->SetBranchAddress("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL", &myHLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL);

 int myHLT_TripleMu_12_10_5 = 0;
 evt->SetBranchAddress("HLT_TripleMu_12_10_5", &myHLT_TripleMu_12_10_5);

 int myHLT_Mu8_DiEle12_CaloIdL_TrackIdL = 0;
 evt->SetBranchAddress("HLT_Mu8_DiEle12_CaloIdL_TrackIdL", &myHLT_Mu8_DiEle12_CaloIdL_TrackIdL);

 int myHLT_DiMu9_Ele9_CaloIdL_TrackIdL = 0;
 evt->SetBranchAddress("HLT_DiMu9_Ele9_CaloIdL_TrackIdL", &myHLT_DiMu9_Ele9_CaloIdL_TrackIdL);

 // double tau triggers

 int myHLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg = 0;
 evt->SetBranchAddress("HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg", &myHLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg);

 int myHLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg = 0;
 evt->SetBranchAddress("HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg", &myHLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg);

 //histograms
TH1F * h_HT_1tau0L = new TH1F("h_HT_1tau0L", "h_HT_1tau0L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau1L = new TH1F("h_HT_1tau1L", "h_HT_1tau1L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau2L = new TH1F("h_HT_1tau2L", "h_HT_1tau2L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau3L = new TH1F("h_HT_1tau3L", "h_HT_1tau3L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau0L = new TH1F("h_HT_2tau0L", "h_HT_2tau0L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau1L = new TH1F("h_HT_2tau1L", "h_HT_2tau1L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau2L = new TH1F("h_HT_2tau2L", "h_HT_2tau2L; H_{T} [GeV];", 25, 0, 1500);

TH1F *h_njets_ptg40_1tau0L  = new TH1F("h_njets_ptg40_1tau0L", "h_njets_ptg40_1tau0L; Jet multiplicity (p_{T} > 40 GeV);", 15, 0, 15);
TH1F *h_njets_ptg40_1tau1L  = new TH1F("h_njets_ptg40_1tau1L", "h_njets_ptg40_1tau1L; Jet multiplicity (p_{T} > 40 GeV);", 15, 0, 15);
TH1F *h_njets_ptg40_1tau2L  = new TH1F("h_njets_ptg40_1tau2L", "h_njets_ptg40_1tau2L; Jet multiplicity (p_{T} > 40 GeV);", 15, 0, 15);
TH1F *h_njets_ptg40_1tau3L  = new TH1F("h_njets_ptg40_1tau3L", "h_njets_ptg40_1tau3L; Jet multiplicity (p_{T} > 40 GeV);", 15, 0, 15);
TH1F *h_njets_ptg40_2tau0L  = new TH1F("h_njets_ptg40_2tau0L", "h_njets_ptg40_2tau0L; Jet multiplicity (p_{T} > 40 GeV);", 15, 0, 15);
TH1F *h_njets_ptg40_2tau1L  = new TH1F("h_njets_ptg40_2tau1L", "h_njets_ptg40_2tau1L; Jet multiplicity (p_{T} > 40 GeV);", 15, 0, 15);
TH1F *h_njets_ptg40_2tau2L  = new TH1F("h_njets_ptg40_2tau2L", "h_njets_ptg40_2tau2L; Jet multiplicity (p_{T} > 40 GeV);", 15, 0, 15);

TH1F * h_njets_ptg30_1tau0L = new TH1F("h_njets_ptg30_1tau0L", "h_njets_ptg30_1tau0L; Jet multiplicity (p_{T} > 30 GeV);", 15, 0, 15);
TH1F * h_njets_ptg30_1tau1L = new TH1F("h_njets_ptg30_1tau1L", "h_njets_ptg30_1tau1L; Jet multiplicity (p_{T} > 30 GeV);", 15, 0, 15);
TH1F * h_njets_ptg30_1tau2L = new TH1F("h_njets_ptg30_1tau2L", "h_njets_ptg30_1tau2L; Jet multiplicity (p_{T} > 30 GeV);", 15, 0, 15);
TH1F * h_njets_ptg30_1tau3L = new TH1F("h_njets_ptg30_1tau3L", "h_njets_ptg30_1tau3L; Jet multiplicity (p_{T} > 30 GeV);", 15, 0, 15);
TH1F * h_njets_ptg30_2tau0L = new TH1F("h_njets_ptg30_2tau0L", "h_njets_ptg30_2tau0L; Jet multiplicity (p_{T} > 30 GeV);", 15, 0, 15);
TH1F * h_njets_ptg30_2tau1L = new TH1F("h_njets_ptg30_2tau1L", "h_njets_ptg30_2tau1L; Jet multiplicity (p_{T} > 30 GeV);", 15, 0, 15);
TH1F * h_njets_ptg30_2tau2L = new TH1F("h_njets_ptg30_2tau2L", "h_njets_ptg30_2tau2L; Jet multiplicity (p_{T} > 30 GeV);", 15, 0, 15);

TH1F * h_nbjetsM_1tau0L = new TH1F("h_nbjetsM_1tau0L", "h_nbjetsM_1tau0L; b jet multiplicity;", 15, 0, 15);
TH1F * h_nbjetsM_1tau1L = new TH1F("h_nbjetsM_1tau1L", "h_nbjetsM_1tau1L; b jet multiplicity;", 15, 0, 15);
TH1F * h_nbjetsM_1tau2L = new TH1F("h_nbjetsM_1tau2L", "h_nbjetsM_1tau2L; b jet multiplicity;", 15, 0, 15);
TH1F * h_nbjetsM_1tau3L = new TH1F("h_nbjetsM_1tau3L", "h_nbjetsM_1tau3L; b jet multiplicity;", 15, 0, 15);
TH1F * h_nbjetsM_2tau0L = new TH1F("h_nbjetsM_2tau0L", "h_nbjetsM_2tau0L; b jet multiplicity;", 15, 0, 15);
TH1F * h_nbjetsM_2tau1L = new TH1F("h_nbjetsM_2tau1L", "h_nbjetsM_2tau1L; b jet multiplicity;", 15, 0, 15);
TH1F * h_nbjetsM_2tau2L = new TH1F("h_nbjetsM_2tau2L", "h_nbjetsM_2tau2L; b jet multiplicity;", 15, 0, 15);

 double num_1tau0L = 0;
 double den_1tau0L = 0;
 double num_1tau1L = 0;
 double den_1tau1L = 0;
 double num_1tau2L = 0;
 double den_1tau2L = 0;
 double num_1tau3L = 0;
 double den_1tau3L = 0;
 double num_2tau0L = 0;
 double den_2tau0L = 0;
 double num_2tau1L = 0;
 double den_2tau1L = 0;
 double num_2tau2L = 0;
 double den_2tau2L = 0;

Long64_t nevents = evt->GetEntries();

for ( Long64_t ievent = 0; ievent < nevents; ++ievent ) {
  //if (ievent > 100) break;
  if ( !(ievent % 100000 ) ) cout << "ievent  =  " << ievent << endl;
   //get i-th entry in tree
   evt->GetEntry( ievent );

   int njets_ptg40_1tau0L = 0; 
   int njets_ptg40_1tau1L = 0; 
   int njets_ptg40_1tau2L = 0; 
   int njets_ptg40_1tau3L = 0; 
   int njets_ptg40_2tau0L = 0; 
   int njets_ptg40_2tau1L = 0; 
   int njets_ptg40_2tau2L = 0; 
                   
   int njets_ptg30_1tau0L = 0; 
   int njets_ptg30_1tau1L = 0; 
   int njets_ptg30_1tau2L = 0; 
   int njets_ptg30_1tau3L = 0; 
   int njets_ptg30_2tau0L = 0; 
   int njets_ptg30_2tau1L = 0; 
   int njets_ptg30_2tau2L = 0; 


   /////////////////////////////////////////////////////////////////////
   ///////////////////// DEFINE CATEGORY CUTS //////////////////////////
   /////////////////////////////////////////////////////////////////////

 bool is1tau0L = (mytausT_number==1 && myleptonsMVAT_number==0 &&  myjetsL_number>=8 && mybjetsM_number>=2);
 bool is1tau1e = (mytausT_number==1 && myleptonsMVAT_number == 1 && myelesMVAT_number==1 && myjetsL_number>=6 && mybjetsM_number>=2 && myeleMVAT_pt->at(0)>10);
 bool is1tau1mu = (mytausT_number==1 && myleptonsMVAT_number == 1 && mymuonsT_number==1 && myjetsL_number>=6 && mybjetsM_number>=2 && mymuonT_pt->at(0)>10);
 bool is1tau2OSL = (mytausT_number==1 && myleptonsMVAT_number==2 && myleptonsMVAT_2OS==1  &&  myjetsL_number>=4 && mybjetsM_number>=2);
 bool is1tau2SSL = (mytausT_number==1 && myleptonsMVAT_number==2 && myleptonsMVAT_2SS==1 && myjetsL_number>=4 && mybjetsM_number>=2);
 bool is1tau3L = (mytausT_number==1 && myleptonsMVAT_number==3 &&  myjetsL_number>=2 && mybjetsM_number>=2);
 bool is2tau0L = (mytausT_number==2 && myleptonsMVAT_number==0 &&  myjetsL_number>=6 && mybjetsM_number>=2);
 bool is2tau1e = (mytausT_number==2 && myleptonsMVAT_number == 1 && myelesMVAT_number==1 &&  myjetsL_number>=4 && mybjetsM_number>=2);
 bool is2tau1mu = (mytausT_number==2 && myleptonsMVAT_number == 1 && mymuonsT_number==1 &&  myjetsL_number>=4 && mybjetsM_number>=2);
 bool is2tau2OSL = (mytausT_number==2 && myleptonsMVAT_number==2 && myleptonsMVAT_2OS==1  && myjetsL_number>=2 && mybjetsM_number>=2);
 bool is2tau2SSL = (mytausT_number==2 && myleptonsMVAT_number==2 && myleptonsMVAT_2SS==1 && myjetsL_number>=2 && mybjetsM_number>=2);

 // use trigger setup of ttH multilepton
 /////////////////////////////////////////////////////////////////////
 ///////////////////// DEFINE TRIGGER CUTS ///////////////////////////
 /////////////////////////////////////////////////////////////////////

 bool singleEle = (myHLT_Ele25_eta2p1_WPTight_Gsf == 1 || myHLT_Ele27_WPTight_Gsf == 1 || myHLT_Ele27_eta2p1_WPLoose_Gsf == 1);
 bool singleMu = (myHLT_IsoMu22 == 1 || myHLT_IsoTkMu22 == 1 || myHLT_IsoMu22_eta2p1 == 1 || myHLT_IsoTkMu22_eta2p1 == 1 || myHLT_IsoMu24 == 1 ||  myHLT_IsoTkMu24 == 1);
 bool elePlusTau = (myHLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20 == 1 || myHLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1 == 1 || myHLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30 == 1);
 bool muPlusTau = (myHLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1 == 1);
 bool doubleEle = (myHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ == 1);
 bool doubleMu = (myHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL == 1 || myHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ == 1 || myHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL == 1 || myHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ == 1);
 bool elePlusMu (myHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL == 1 || myHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ == 1 || myHLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL == 1 || myHLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ == 1 || myHLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ == 1 || myHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL == 1);
 bool triLepton = (myHLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL == 1 || myHLT_TripleMu_12_10_5 == 1 || myHLT_Mu8_DiEle12_CaloIdL_TrackIdL == 1 || myHLT_DiMu9_Ele9_CaloIdL_TrackIdL == 1);
 bool doubleTau = (myHLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg == 1 || myHLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg == 1);

 bool is1tau0Ltrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1);
 bool is1tau1etrig = (singleEle || elePlusTau);
 bool is1tau1mutrig = (singleMu || muPlusTau);
 bool is1tau2Ltrig = ( singleEle || singleMu || doubleEle || doubleMu || elePlusMu  );
 bool is1tau3Ltrig = ( is1tau2Ltrig || triLepton );
 bool is2tau0Ltrig = doubleTau;
 bool is2tau1etrig = (singleEle || elePlusTau);
 bool is2tau1mutrig = (singleMu || muPlusTau);
 bool is2tau2Ltrig = is1tau2Ltrig;

 if (setup == "ZhangYu") {
   
 is1tau0Ltrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1);
 is1tau1etrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1);
 is1tau1mutrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1);
 is1tau2Ltrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1);
 is1tau3Ltrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1);
 is2tau0Ltrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1);
 is2tau1etrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1);
 is2tau1mutrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1);
 is2tau2Ltrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1);

}

 if (setup == "ttH_ML"){

   if (is1tau0L) {

   den_1tau0L += mygenEvtWeight;
   
   if (is1tau0Ltrig) num_1tau0L += mygenEvtWeight;

 }// end 1tau0L

 if ((is1tau1e && myeleMVAT_pt->at(0) > 30) || (is1tau1mu && mymuonT_pt->at(0) > 30)) {

   den_1tau1L += mygenEvtWeight;

   if (is1tau1etrig || is1tau1mutrig) num_1tau1L += mygenEvtWeight;

 }// end 1tau1L

 if (is1tau2OSL || is1tau2SSL) {

   if (myeleMVAT_pt->size() > 0 && mymuonT_pt->size() == 0) {
     
     if (myeleMVAT_pt->at(0) > 30) {

       den_1tau2L += mygenEvtWeight;
       
       if (is1tau2Ltrig) num_1tau2L += mygenEvtWeight;

     }

   }

   if (myeleMVAT_pt->size() == 0 && mymuonT_pt->size() > 0) {
     
     if (mymuonT_pt->at(0) > 30) {

       den_1tau2L += mygenEvtWeight;
       
       if (is1tau2Ltrig) num_1tau2L += mygenEvtWeight;

     }

   }

   if (myeleMVAT_pt->size() > 0 && mymuonT_pt->size() > 0) {
     
     if (myeleMVAT_pt->at(0) > 30 && mymuonT_pt->at(0) > 30) {

       den_1tau2L += mygenEvtWeight;
       
       if (is1tau2Ltrig) num_1tau2L += mygenEvtWeight;

     }

   }

 }// end 1tau2L

 if (is1tau3L) {

   if (myeleMVAT_pt->size() > 0 && mymuonT_pt->size() == 0) {
     
     if (myeleMVAT_pt->at(0) > 30) {

       den_1tau3L += mygenEvtWeight;
       
       if (is1tau3Ltrig) num_1tau3L += mygenEvtWeight;

     }

   }

   if (myeleMVAT_pt->size() == 0 && mymuonT_pt->size() > 0) {
     
     if (mymuonT_pt->at(0) > 30) {

       den_1tau3L += mygenEvtWeight;
       
       if (is1tau3Ltrig) num_1tau3L += mygenEvtWeight;

     }

   }

   if (myeleMVAT_pt->size() > 0 && mymuonT_pt->size() > 0) {
     
     if (myeleMVAT_pt->at(0) > 30 && mymuonT_pt->at(0) > 30) {

       den_1tau3L += mygenEvtWeight;
       
       if (is1tau3Ltrig) num_1tau3L += mygenEvtWeight;

     }

   }

 }// end 1tau3L

 if (is2tau0L) {

   den_2tau0L += mygenEvtWeight;
   
   if (is2tau0Ltrig) num_2tau0L += mygenEvtWeight;

 }// end 2tau0L

 if ((is2tau1e && myeleMVAT_pt->at(0) > 30) || (is2tau1mu && mymuonT_pt->at(0) > 30)) {

   den_2tau1L += mygenEvtWeight;

   if (is2tau1etrig || is2tau1mutrig) num_2tau1L += mygenEvtWeight;

 }// end 2tau1L

 if (is2tau2OSL || is2tau2SSL) {

   if (myeleMVAT_pt->size() > 0 && mymuonT_pt->size() == 0) {
     
     if (myeleMVAT_pt->at(0) > 30) {

       den_2tau2L += mygenEvtWeight;
       
       if (is2tau2Ltrig) num_2tau2L += mygenEvtWeight;

     }

   }

   if (myeleMVAT_pt->size() == 0 && mymuonT_pt->size() > 0) {
     
     if (mymuonT_pt->at(0) > 30) {

       den_2tau2L += mygenEvtWeight;
       
       if (is2tau2Ltrig) num_2tau2L += mygenEvtWeight;

     }

   }

   if (myeleMVAT_pt->size() > 0 && mymuonT_pt->size() > 0) {
     
     if (myeleMVAT_pt->at(0) > 30 && mymuonT_pt->at(0) > 30) {

       den_2tau2L += mygenEvtWeight;
       
       if (is2tau2Ltrig) num_2tau2L += mygenEvtWeight;

     }

   }

 }// end 2tau2L

 }// end setup ttH_ML

 if (setup == "ZhangYu"){

   if (is1tau0L /*&& myjetsL_1pt > 40*/) {

   den_1tau0L += mygenEvtWeight;
   h_HT_1tau0L->Fill(myjetsL_HT, mygenEvtWeight);
   h_nbjetsM_1tau0L->Fill(mybjetsM_number, mygenEvtWeight);
   countJets(njets_ptg40_1tau0L, 40.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
   countJets(njets_ptg30_1tau0L, 30.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
   h_njets_ptg40_1tau0L->Fill(njets_ptg40_1tau0L, mygenEvtWeight);
   h_njets_ptg30_1tau0L->Fill(njets_ptg30_1tau0L, mygenEvtWeight);
   if (is1tau0Ltrig) num_1tau0L += mygenEvtWeight;
   }// end 1tau0L
 

   if ((is1tau1e /*&& myjetsL_1pt > 40*/) || (is1tau1mu /*&& myjetsL_1pt > 40*/)) {

   den_1tau1L += mygenEvtWeight;
   h_HT_1tau1L->Fill(myjetsL_HT, mygenEvtWeight);
   h_nbjetsM_1tau1L->Fill(mybjetsM_number, mygenEvtWeight);
   countJets(njets_ptg40_1tau1L, 40.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
   countJets(njets_ptg30_1tau1L, 30.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
   h_njets_ptg40_1tau1L->Fill(njets_ptg40_1tau1L, mygenEvtWeight);
   h_njets_ptg30_1tau1L->Fill(njets_ptg30_1tau1L, mygenEvtWeight);

   if (is1tau1etrig || is1tau1mutrig) num_1tau1L += mygenEvtWeight;

 }// end 1tau1L

 if (is1tau2OSL || is1tau2SSL) {
 
   if (true /*myjetsL_1pt > 40*/) {

     den_1tau2L += mygenEvtWeight;
     h_HT_1tau2L->Fill(myjetsL_HT, mygenEvtWeight);
     h_nbjetsM_1tau2L->Fill(mybjetsM_number, mygenEvtWeight);
     countJets(njets_ptg40_1tau2L, 40.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
     countJets(njets_ptg30_1tau2L, 30.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
     h_njets_ptg40_1tau2L->Fill(njets_ptg40_1tau2L, mygenEvtWeight);
     h_njets_ptg30_1tau2L->Fill(njets_ptg30_1tau2L, mygenEvtWeight);
       if (is1tau2Ltrig) num_1tau2L += mygenEvtWeight;

   }

 }// end 1tau2L

 if (is1tau3L) {

   if (true /*myjetsL_1pt > 40*/) {

     den_1tau3L += mygenEvtWeight;
     h_HT_1tau3L->Fill(myjetsL_HT, mygenEvtWeight);
     h_nbjetsM_1tau3L->Fill(mybjetsM_number, mygenEvtWeight);
     countJets(njets_ptg40_1tau3L, 40.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
     countJets(njets_ptg30_1tau3L, 30.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
     h_njets_ptg40_1tau3L->Fill(njets_ptg40_1tau3L, mygenEvtWeight);
     h_njets_ptg30_1tau3L->Fill(njets_ptg30_1tau3L, mygenEvtWeight);
       if (is1tau3Ltrig) num_1tau3L += mygenEvtWeight;

   }

 }// end 1tau3L

 if (is2tau0L) {

   if (true /*myjetsL_1pt > 40*/) {

     den_2tau0L += mygenEvtWeight;
     h_HT_2tau0L->Fill(myjetsL_HT, mygenEvtWeight);
   h_nbjetsM_2tau0L->Fill(mybjetsM_number, mygenEvtWeight);
   countJets(njets_ptg40_2tau0L, 40.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
   countJets(njets_ptg30_2tau0L, 30.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
   h_njets_ptg40_2tau0L->Fill(njets_ptg40_2tau0L, mygenEvtWeight);
   h_njets_ptg30_2tau0L->Fill(njets_ptg30_2tau0L, mygenEvtWeight);
   if (is2tau0Ltrig) num_2tau0L += mygenEvtWeight;

   }

 }// end 2tau0L

 if ((is2tau1e /*&& myjetsL_1pt > 40*/) || (is2tau1mu /*&& myjetsL_1pt > 40*/)) {

   den_2tau1L += mygenEvtWeight;
   h_HT_2tau1L->Fill(myjetsL_HT, mygenEvtWeight);
   h_nbjetsM_2tau1L->Fill(mybjetsM_number, mygenEvtWeight);
   countJets(njets_ptg40_2tau1L, 40.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
   countJets(njets_ptg30_2tau1L, 30.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
   h_njets_ptg40_2tau1L->Fill(njets_ptg40_2tau1L, mygenEvtWeight);
   h_njets_ptg30_2tau1L->Fill(njets_ptg30_2tau1L, mygenEvtWeight);
   if (is2tau1etrig || is2tau1mutrig) num_2tau1L += mygenEvtWeight;

 }// end 2tau1L

 if (is2tau2OSL || is2tau2SSL) {

   if (true /*myjetsL_1pt > 40*/) {
     
       den_2tau2L += mygenEvtWeight;
       h_HT_2tau2L->Fill(myjetsL_HT, mygenEvtWeight);
   h_nbjetsM_2tau2L->Fill(mybjetsM_number, mygenEvtWeight);
   countJets(njets_ptg40_2tau2L, 40.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
   countJets(njets_ptg30_2tau2L, 30.0, myjetsL_1pt, myjetsL_2pt, myjetsL_3pt, myjetsL_4pt, myjetsL_5pt, myjetsL_6pt, myjetsL_7pt, myjetsL_8pt, myjetsL_9pt, myjetsL_10pt, myjetsL_11pt);
   h_njets_ptg40_2tau2L->Fill(njets_ptg40_2tau2L, mygenEvtWeight);
   h_njets_ptg30_2tau2L->Fill(njets_ptg30_2tau2L, mygenEvtWeight);
       if (is2tau2Ltrig) num_2tau2L += mygenEvtWeight;

   }

 }// end 2tau2L

 }// end setup ZhangYu

 }//end loop over events

 cout << setw(10) << left << "" << setw(10) << left << "1tau0L" << setw(10) << left << "1tau1L" << setw(10) << left << "1tau2L" << setw(10) << left << "1tau3L" << setw(10) << left << "2tau0L" << setw(10) << left << "2tau1L" << setw(10) << left << "2tau2L" << endl;
 cout << setw(10) << left << "num" << setw(10) << left << num_1tau0L << setw(10) << left << num_1tau1L << setw(10) << left << num_1tau2L << setw(10) << left << num_1tau3L<< setw(10) << left << num_2tau0L << setw(10) << left << num_2tau1L << setw(10) << left << num_2tau2L << endl;
 cout << setw(10) << left << "den" << setw(10) << left << den_1tau0L << setw(10) << left << den_1tau1L << setw(10) << left << den_1tau2L << setw(10) << left << den_1tau3L<< setw(10) << left << den_2tau0L << setw(10) << left << den_2tau1L << setw(10) << left << den_2tau2L << endl;
 cout << setw(10) << left << "trigEff" << setw(10) << left << num_1tau0L/den_1tau0L << setw(10) << left << num_1tau1L/den_1tau1L << setw(10) << left << num_1tau2L/den_1tau2L << setw(10) << left << num_1tau3L/den_1tau3L << setw(10) << left << num_2tau0L/den_2tau0L << setw(10) << left << num_2tau1L/den_2tau1L << setw(10) << left << num_2tau2L/den_2tau2L << endl;

 TFile *outputfile = new TFile( ("trigEff_output_" + file_it->first + ".root").c_str(), "RECREATE" );

 h_HT_1tau0L->Write();
 h_HT_1tau1L->Write();
 h_HT_1tau2L->Write();
 h_HT_1tau3L->Write();
 h_HT_2tau0L->Write();
 h_HT_2tau1L->Write();
 h_HT_2tau2L->Write();

 h_njets_ptg40_1tau0L->Write(); 
 h_njets_ptg40_1tau1L->Write(); 
 h_njets_ptg40_1tau2L->Write(); 
 h_njets_ptg40_1tau3L->Write(); 
 h_njets_ptg40_2tau0L->Write(); 
 h_njets_ptg40_2tau1L->Write(); 
 h_njets_ptg40_2tau2L->Write(); 
                    
 h_njets_ptg30_1tau0L->Write(); 
 h_njets_ptg30_1tau1L->Write(); 
 h_njets_ptg30_1tau2L->Write(); 
 h_njets_ptg30_1tau3L->Write(); 
 h_njets_ptg30_2tau0L->Write(); 
 h_njets_ptg30_2tau1L->Write(); 
 h_njets_ptg30_2tau2L->Write(); 
             
 h_nbjetsM_1tau0L->Write();
 h_nbjetsM_1tau1L->Write();
 h_nbjetsM_1tau2L->Write();
 h_nbjetsM_1tau3L->Write();
 h_nbjetsM_2tau0L->Write();
 h_nbjetsM_2tau1L->Write();
 h_nbjetsM_2tau2L->Write();

 outputfile->Close();
 delete outputfile;

 inputfile->Close();
 delete inputfile;
 
 file_it++;

 }//end loop over files

 

 gBenchmark->Show("running time");

}//end



void countJets (int & counter, double pt_threshold, double jet_1pt, double jet_2pt, double jet_3pt, double jet_4pt, double jet_5pt, double jet_6pt, double jet_7pt, double jet_8pt, double jet_9pt, double jet_10pt, double jet_11pt) {

if (jet_1pt > pt_threshold) {
  counter++;
  if (jet_2pt > pt_threshold) {
    counter++;
    if (jet_2pt > pt_threshold) {
      counter++;
      if (jet_3pt > pt_threshold) {
	counter++;
	if (jet_4pt > pt_threshold) {
	  counter++;
	  if (jet_5pt > pt_threshold) {
	    counter++;
	    if (jet_6pt > pt_threshold) {
	      counter++;
	      if (jet_7pt > pt_threshold) {
		counter++;
		if (jet_8pt > pt_threshold) {
		  counter++;
		  if (jet_9pt > pt_threshold) {
		    counter++;
		    if (jet_10pt > pt_threshold) {
		      counter++;
		      if (jet_11pt > pt_threshold) {
			counter++;
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
}

}
