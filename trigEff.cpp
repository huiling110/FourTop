#include <iostream>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TBenchmark.h>
#include "trigEff.h"

//using namespace std;

void trigEff() {

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

 double num_1tau0L = 0;
 double den_1tau0L = 0;
 double num_1tau1L = 0;
 double den_1tau1L = 0;
 double num_1tau2L = 0;
 double den_1tau2L = 0;
 double num_1tau3L = 0;
 double den_1tau3L = 0;

Long64_t nevents = evt->GetEntries();

for ( Long64_t ievent = 0; ievent < nevents; ++ievent ) {
  //if (ievent > 100) break;
  if ( !(ievent % 100000 ) ) cout << "ievent  =  " << ievent << endl;
   //get i-th entry in tree
   evt->GetEntry( ievent );

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

 bool is1tau0Ltrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1);
 bool is1tau1etrig = (singleEle || elePlusTau);
 bool is1tau1mutrig = (singleMu || muPlusTau);
 bool is1tau2Ltrig = ( singleEle || singleMu || doubleEle || doubleMu || elePlusMu  );
 bool is1tau3Ltrig = ( is1tau2Ltrig || triLepton );
 
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

 }//end loop over events
 
 cout << "trigger efficiency for 1tau0L cat = " << num_1tau0L/den_1tau0L << endl;
 cout << "trigger efficiency for 1tau1L cat = " << num_1tau1L/den_1tau1L << endl;
 cout << "trigger efficiency for 1tau2L cat = " << num_1tau2L/den_1tau2L << endl;
 cout << "trigger efficiency for 1tau3L cat = " << num_1tau3L/den_1tau3L << endl;
 
 inputfile->Close();
 delete inputfile;
 file_it++;

 }//end loop over files

 gBenchmark->Show("running time");

}//end
