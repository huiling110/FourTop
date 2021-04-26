#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TBenchmark.h>
#include <TEfficiency.h>
#include "trigEff_vs_HT_perprocess.h"
#include <TChain.h>
#include <TLorentzVector.h>
#include <TROOT.h> //for gROOT
#include <TSystem.h> // for gSystem
#define NBINSX 15
#define NBINSY 9
//using namespace std;

void trigEff_vs_HT_perprocess() {

gBenchmark->Start("running time");

gROOT->ProcessLine(".L Loader.C+");
 Float_t binsX[NBINSX+1] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1800, 2100, 3000};
 Float_t binsY[NBINSY+1] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

TFile *outputfile = new TFile( "trigEff_vs_HTj_perprocess_output_withDATA_addHLT_PFJet450_expandHTRange.root", "RECREATE" ); 
//TFile *outputfile = new TFile( "asdasd.root", "RECREATE" );

map<string, string>::iterator file_it = file.begin();

while (file_it != file.end()) { //////////////////////// LOOP OVER FILES ///////////////////////

cout << "Reading process " << file_it->second << "..." << endl;
TString input_base_dir = file_it->second + "/";
/*
gSystem->RedirectOutput("/dev/null"); // do not show errors when not finding the following files: will print a custom error a few lines below
TFile * checkinput = new TFile(input_base_dir + "v3_1-1.root");
TFile * checkinput2 = new TFile(input_base_dir + "v3_1.root");
gSystem->RedirectOutput(0,0); // restore the printing to normal behavior
if (checkinput->IsZombie() && checkinput2->IsZombie()){
cout << "+++ INPUT FILES NOT FOUND! SKIPPING +++" << endl;
 file_it++;
continue;
} 
*/

 TH1::AddDirectory(kFALSE); 
 // HT distribution for signal
 TH1F * h_HT_signal = new TH1F("h_HT_signal", "h_HT_signal; H_{T} [GeV]", 60, 0, 3000);
 //Njets distribution for signal
 TH1F * h_njets_signal = new TH1F("h_njets_signal", "h_njets_signal; Jet multiplicity", 15, 0, 15);
//histograms: wrt reference
//before signal trigger
//vs HT
TH1F * h_HT_nocat = new TH1F("h_HT_nocat", "h_HT_nocat; H_{T} [GeV];", NBINSX, binsX);
//same as line before, but asking for njets requirement
TH1F * h_HT_nocat_njets = new TH1F("h_HT_nocat_njets", "h_HT_nocat_njets; H_{T} [GeV];", NBINSX, binsX);
//same line as before, but asking for mu pt requirement
TH1F * h_HT_nocat_njets_mupt25 = new TH1F("h_HT_nocat_njets_mupt25", "h_HT_nocat_njets_mupt25; H_{T} [GeV];", NBINSX, binsX);
//same line as before, but asking for jet pt requirement
TH1F * h_HT_nocat_njets_mupt25_jetpt35 = new TH1F("h_HT_nocat_njets_mupt25_jetpt35", "h_HT_nocat_njets_mupt25_jetpt35; H_{T} [GeV];", NBINSX, binsX);
//vs Njets
TH1F * h_njets_nocat = new TH1F("h_njets_nocat", "h_njets_nocat; Jet multiplicity;", 15, 0, 15);
//same as line before, but asking for HT requirement
TH1F * h_njets_nocat_HT = new TH1F("h_njets_nocat_HT", "h_njets_nocat_HT; Jet multiplicity;", 15, 0, 15);
//same as line before, but asking for mu pt requirement
TH1F * h_njets_nocat_HT_mupt25 = new TH1F("h_njets_nocat_HT_mupt25", "h_njets_nocat_HT_mupt25; Jet multiplicity;", 15, 0, 15);
//same as line before, but asking for jet pt requirement
TH1F * h_njets_nocat_HT_mupt25_jetpt35 = new TH1F("h_njets_nocat_HT_mupt25_jetpt35", "h_njets_nocat_HT_mupt25_jetpt35; Jet multiplicity;", 15, 0, 15);
//2D distribution njets vs HT
TH2F * h_njetsvsHT_nocat = new TH2F ("h_njetsvsHT_nocat", "h_njetsvsHT_nocat; H_{T} [GeV]; Jet multiplicity", NBINSX, binsX, NBINSY, binsY );
//after signal trigger
//vs HT
TH1F * h_HT_nocat_aft = new TH1F("h_HT_nocat_aft", "h_HT_nocat; H_{T} [GeV];", NBINSX, binsX);
//same as line before, but asking for njets requirement
TH1F * h_HT_nocat_njets_aft = new TH1F("h_HT_nocat_njets_aft", "h_HT_nocat_njets_aft; H_{T} [GeV];", NBINSX, binsX);
//same line as before, but asking for mu pt requirement
TH1F * h_HT_nocat_njets_mupt25_aft = new TH1F("h_HT_nocat_njets_mupt25_aft", "h_HT_nocat_njets_mupt25_aft; H_{T} [GeV];", NBINSX, binsX);
//same line as before, but asking for jet pt requirement
TH1F * h_HT_nocat_njets_mupt25_jetpt35_aft = new TH1F("h_HT_nocat_njets_mupt25_jetpt35_aft", "h_HT_nocat_njets_mupt25_jetpt35_aft; H_{T} [GeV];", NBINSX, binsX);
//vs Njets
TH1F * h_njets_nocat_aft = new TH1F("h_njets_nocat_aft", "h_njets_nocat_aft; Jet multiplicity;", 15, 0, 15);
//same as line before, but asking for HT requirement
TH1F * h_njets_nocat_HT_aft = new TH1F("h_njets_nocat_HT_aft", "h_njets_nocat_HT_aft; Jet multiplicity;", 15, 0, 15);
//same as line before, but asking for mu pt requirement
TH1F * h_njets_nocat_HT_mupt25_aft = new TH1F("h_njets_nocat_HT_mupt25_aft", "h_njets_nocat_HT_mupt25_aft; Jet multiplicity;", 15, 0, 15);
//same as line before, but asking for jet pt requirement
TH1F * h_njets_nocat_HT_mupt25_jetpt35_aft = new TH1F("h_njets_nocat_HT_mupt25_jetpt35_aft", "h_njets_nocat_HT_mupt25_jetpt35_aft; Jet multiplicity;", 15, 0, 15);
//2D distribution njets vs HT
TH2F * h_njetsvsHT_nocat_aft = new TH2F ("h_njetsvsHT_nocat_aft", "h_njetsvsHT_nocat_aft; H_{T} [GeV]; Jet multiplicity", NBINSX, binsX, NBINSY, binsY );

//histograms: truth
//before signal trigger
//vs HT
TH1F * h_HT_nocat_truth = new TH1F("h_HT_nocat_truth", "h_HT_nocat; H_{T} [GeV];", NBINSX, binsX);
//same as line before, but asking for njets requirement
TH1F * h_HT_nocat_njets_truth = new TH1F("h_HT_nocat_njets_truth", "h_HT_nocat_njets_truth; H_{T} [GeV];", NBINSX, binsX);
//same as line before, but asking for mu pt requirement
TH1F * h_HT_nocat_njets_mupt25_truth = new TH1F("h_HT_nocat_njets_mupt25_truth", "h_HT_nocat_njets_mupt25_truth; H_{T} [GeV];", NBINSX, binsX);
//same as line before, but asking for jet pt requirement
TH1F * h_HT_nocat_njets_mupt25_jetpt35_truth = new TH1F("h_HT_nocat_njets_mupt25_jetpt35_truth", "h_HT_nocat_njets_mupt25_jetpt35_truth; H_{T} [GeV];", NBINSX, binsX);
//vs Njets
TH1F * h_njets_nocat_truth = new TH1F("h_njets_nocat_truth", "h_njets_nocat; Jet multiplicity;", 15, 0, 15);
//same as line before, but asking for HT requirement
TH1F * h_njets_nocat_HT_truth = new TH1F("h_njets_nocat_HT_truth", "h_njets_nocat_HT_truth; Jet multiplicity;", 15, 0, 15);
//same as line before, but asking for mu pt requirement
TH1F * h_njets_nocat_HT_mupt25_truth = new TH1F("h_njets_nocat_HT_mupt25_truth", "h_njets_nocat_HT_mupt25_truth; Jet multiplicity;", 15, 0, 15);
//same as line before, but asking for jet pt requirement
TH1F * h_njets_nocat_HT_mupt25_jetpt35_truth = new TH1F("h_njets_nocat_HT_mupt25_jetpt35_truth", "h_njets_nocat_HT_mupt25_jetpt35_truth; Jet multiplicity;", 15, 0, 15);
//2D distribution njets vs HT
TH2F * h_njetsvsHT_nocat_truth = new TH2F ("h_njetsvsHT_nocat_truth", "h_njetsvsHT_nocat_truth; H_{T} [GeV]; Jet multiplicity", NBINSX, binsX, NBINSY, binsY );
//after signal trigger
//vs HT
TH1F * h_HT_nocat_truth_aft = new TH1F("h_HT_nocat_truth_aft", "h_HT_nocat; H_{T} [GeV];", NBINSX, binsX);
//same as line before, but asking for njets requirement
TH1F * h_HT_nocat_njets_truth_aft = new TH1F("h_HT_nocat_njets_truth_aft", "h_HT_nocat_njets_truth_aft; H_{T} [GeV];", NBINSX, binsX);
//same as line before, but asking for mu pt requirement
TH1F * h_HT_nocat_njets_mupt25_truth_aft = new TH1F("h_HT_nocat_njets_mupt25_truth_aft", "h_HT_nocat_njets_mupt25_truth_aft; H_{T} [GeV];", NBINSX, binsX);
//same as line before, but asking for jet pt requirement
TH1F * h_HT_nocat_njets_mupt25_jetpt35_truth_aft = new TH1F("h_HT_nocat_njets_mupt25_jetpt35_truth_aft", "h_HT_nocat_njets_mupt25_jetpt35_truth_aft; H_{T} [GeV];", NBINSX, binsX);
//vs Njets
TH1F * h_njets_nocat_truth_aft = new TH1F("h_njets_nocat_truth_aft", "h_njets_nocat_aft; Jet multiplicity;", 15, 0, 15);
//same as line before, but asking for HT requirement
TH1F * h_njets_nocat_HT_truth_aft = new TH1F("h_njets_nocat_HT_truth_aft", "h_njets_nocat_HT_truth_aft; Jet multiplicity;", 15, 0, 15);
//same as line before, but asking for mu pt requirement
TH1F * h_njets_nocat_HT_mupt25_truth_aft = new TH1F("h_njets_nocat_HT_mupt25_truth_aft", "h_njets_nocat_HT_mupt25_truth_aft; Jet multiplicity;", 15, 0, 15);
//same as line before, but asking for jet pt requirement
TH1F * h_njets_nocat_HT_mupt25_jetpt35_truth_aft = new TH1F("h_njets_nocat_HT_mupt25_jetpt35_truth_aft", "h_njets_nocat_HT_mupt25_jetpt35_truth_aft; Jet multiplicity;", 15, 0, 15);
//2D distribution njets vs HT
TH2F * h_njetsvsHT_nocat_truth_aft = new TH2F ("h_njetsvsHT_nocat_truth_aft", "h_njetsvsHT_nocat_truth_aft; H_{T} [GeV]; Jet multiplicity", NBINSX, binsX, NBINSY, binsY );
 TH1::AddDirectory(kTRUE); 

string data = "data";
TChain mychain("tree");
if (!(file_it->first.find(data) !=std::string::npos)) mychain.Add(input_base_dir + "v3*.root"); 
else mychain.Add(input_base_dir + "TauOfTTTT*.root");
TChain mychain2("allevents");
if (!(file_it->first.find(data) !=std::string::npos)) mychain2.Add(input_base_dir + "v3*.root");

cout << "Computing the sum of gen event weights..." << endl;
TH1::StatOverflows(kTRUE);
TH1D * genEvtWeights = new TH1D("genEvtWeights", "genEvtWeights", 10, -10, 10 );
double gen_sum_of_weights = 0.0;
if (!(file_it->first.find(data) !=std::string::npos)) {
mychain2.Project(genEvtWeights->GetName(), "genWeight_allEvents");
cout << "genEvtWeights->GetMean(): " << genEvtWeights->GetMean() << endl;
cout << "genEvtWeights->GetEntries(): " << genEvtWeights->GetEntries() << endl; 
gen_sum_of_weights = genEvtWeights->GetMean()*genEvtWeights->GetEntries();
cout << gen_sum_of_weights << endl;
}
TH1::StatOverflows(kFALSE);

double mygenEvtWeight = 1;
//if running on data, do not set the gen event weight address
if (!(file_it->first.find(data) !=std::string::npos)) mychain.SetBranchAddress( "EVENT_genWeight_", &mygenEvtWeight );

vector<TLorentzVector> *myjetsL = {}; 
mychain.SetBranchAddress("jets", &myjetsL);

vector<TLorentzVector> *mybjetsM = {}; 
mychain.SetBranchAddress("bjetsM", &mybjetsM);

vector<TLorentzVector> *myelesMVAT = {}; 
mychain.SetBranchAddress("eleMVAT", &myelesMVAT);

vector<TLorentzVector> *mymuonsT = {}; 
mychain.SetBranchAddress("muonsT", &mymuonsT);

vector<TLorentzVector> *mytausT = {}; 
mychain.SetBranchAddress("tausT", &mytausT);

vector<TLorentzVector> *myleptonsMVAT = {}; 
mychain.SetBranchAddress("leptonsMVAT", &myleptonsMVAT);

 // multijet triggers
 int myHLT_PFHT450_SixJet40_BTagCSV_p056 = 0;
 mychain.SetBranchAddress("HLT_PFHT450_SixJet40_BTagCSV_p056_", &myHLT_PFHT450_SixJet40_BTagCSV_p056);

 int myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = 0;
 mychain.SetBranchAddress("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_", &myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056);

 //reference triggers
 int myHLT_IsoMu24 = 0;
 mychain.SetBranchAddress("HLT_IsoMu24_", &myHLT_IsoMu24);

 int myHLT_IsoMu27 = 0;
 mychain.SetBranchAddress("HLT_IsoMu27_", &myHLT_IsoMu27);

 //HLT_PFJet450 to recover eff in data
 int myHLT_PFJet450 = 0;
 mychain.SetBranchAddress("HLT_PFJet450_", &myHLT_PFJet450);

Long64_t nevents = mychain.GetEntries();

for ( Long64_t ievent = 0; ievent < nevents; ++ievent ) {
  //if (ievent > 100) break;
  if ( !(ievent % 100000 ) ) cout << "ievent  =  " << ievent << endl;
   //get i-th entry in tree
   mychain.GetEntry( ievent );
   if (!(mygenEvtWeight > 0)) continue;
   /////////////////////////////////////////////////////////////////////
   ///////////////////// DEFINE CATEGORY CUTS //////////////////////////
   /////////////////////////////////////////////////////////////////////

 bool is1tau0L = (mytausT->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2);
 bool is1tau1e = (mytausT->size()==1 && myleptonsMVAT->size() == 1 && myelesMVAT->size()==1 && myjetsL->size()>=6 && mybjetsM->size()>=2);
 bool is1tau1mu = (mytausT->size()==1 && myleptonsMVAT->size() == 1 && mymuonsT->size()==1 &&  myjetsL->size()>=6 && mybjetsM->size()>=2);
 bool is1tau2L = (mytausT->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2);
 bool is1tau3L = (mytausT->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2);
 bool is2tau0L = (mytausT->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2);
 bool is2tau1e = (mytausT->size()==2 && myleptonsMVAT->size() == 1 && myelesMVAT->size()==1 &&  myjetsL->size()>=4 && mybjetsM->size()>=2);
 bool is2tau1mu = (mytausT->size()==2 && myleptonsMVAT->size() == 1 && mymuonsT->size()==1 &&  myjetsL->size()>=4 && mybjetsM->size()>=2);
 bool is2tau2L = (mytausT->size()==2 && (myelesMVAT->size()+mymuonsT->size())==2 && myjetsL->size()>=2 && mybjetsM->size()>=2);

 /////////////////////////////////////////////////////////////////////
 ///////////////////// DEFINE TRIGGER CUTS ///////////////////////////
 /////////////////////////////////////////////////////////////////////

 bool isSignalTrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1 || myHLT_PFJet450 == 1);
 bool isReferenceTrig = (myHLT_IsoMu24 == 1 || myHLT_IsoMu27 == 1);
 
 //compute HT
 float HT = 0.0;
 bool jetptcut = false;
 int countjetpt = 0;
 for (unsigned int i = 0; i < myjetsL->size(); i ++)  {
   
   if (myjetsL->at(i).Pt() > 35) countjetpt++;
   HT += myjetsL->at(i).Pt();

 }

 if (countjetpt == myjetsL->size()) jetptcut = true;

 //compute HT(jet+lepton)
 float HT_jl = HT;

 for (unsigned int i = 0; i < myleptonsMVAT->size(); i++) {

   HT_jl += myleptonsMVAT->at(i).Pt();
   
 }
   
//   if (HT_jl > 400) {

//compute trigger efficiency in preselection asking for exactly 1 muon (a la ttH(bb))


if (myleptonsMVAT->size() == 1 && mymuonsT->size()==1) {
    
    std:string tttt = "tttt";
	if (file_it->first.find(tttt) !=std::string::npos) {
	  if (isSignalTrig) h_HT_signal->Fill(HT, mygenEvtWeight);
	  if (isSignalTrig) h_njets_signal->Fill(myjetsL->size(), mygenEvtWeight);
	 
}


 if (isReferenceTrig) {

   h_HT_nocat->Fill(HT, mygenEvtWeight);
   h_njets_nocat->Fill(myjetsL->size(), mygenEvtWeight);
   h_njetsvsHT_nocat->Fill(HT, myjetsL->size(), mygenEvtWeight);

   if (myjetsL->size() >= 6) {
   
     h_HT_nocat_njets->Fill(HT, mygenEvtWeight);
     
     if(mymuonsT->at(0).Pt() > 25) {

       h_HT_nocat_njets_mupt25->Fill(HT, mygenEvtWeight);
       if (jetptcut) h_HT_nocat_njets_mupt25_jetpt35->Fill(HT, mygenEvtWeight);

     }

   }
   if (HT > 500) {

     h_njets_nocat_HT->Fill(myjetsL->size(), mygenEvtWeight);
     if(mymuonsT->at(0).Pt() > 25) {

	   h_njets_nocat_HT_mupt25->Fill(myjetsL->size(), mygenEvtWeight);
	   if (jetptcut) h_njets_nocat_HT_mupt25_jetpt35->Fill(myjetsL->size(), mygenEvtWeight);
	   
	 }

   }

   if(isSignalTrig) {

     h_HT_nocat_aft->Fill(HT, mygenEvtWeight);
     h_njets_nocat_aft->Fill(myjetsL->size(), mygenEvtWeight);
     h_njetsvsHT_nocat_aft->Fill(HT, myjetsL->size(), mygenEvtWeight);

     if (myjetsL->size() >= 6) {

       h_HT_nocat_njets_aft->Fill(HT, mygenEvtWeight);
       if (mymuonsT->at(0).Pt() > 25) {

	 h_HT_nocat_njets_mupt25_aft->Fill(HT, mygenEvtWeight);
	 if (jetptcut) h_HT_nocat_njets_mupt25_jetpt35_aft->Fill(HT, mygenEvtWeight);

       }

     }
     
     if (HT > 500) {

       h_njets_nocat_HT_aft->Fill(myjetsL->size(), mygenEvtWeight);
       if (mymuonsT->at(0).Pt() > 25) {

		 h_njets_nocat_HT_mupt25_aft->Fill(myjetsL->size(), mygenEvtWeight);
		 if (jetptcut) h_njets_nocat_HT_mupt25_jetpt35_aft->Fill(myjetsL->size(), mygenEvtWeight); 

	   }

       }

   }

 }

 }

 /* if (is1tau0L) {

     if (isReferenceTrig) {

       h_HT_1tau0L->Fill(HT, mygenEvtWeight);
       h_njets_1tau0L->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_1tau0L_aft->Fill(HT, mygenEvtWeight);
	 h_njets_1tau0L_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }

     }
     
     
   }// end 1tau0L
 
 
   if ((is1tau1e) || (is1tau1mu)) {

     if (isReferenceTrig) {

       h_HT_1tau1L->Fill(HT, mygenEvtWeight);
       h_njets_1tau1L->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_1tau1L_aft->Fill(HT, mygenEvtWeight);
	 h_njets_1tau1L_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }

     }

 }// end 1tau1L

 if (is1tau2L) {
 
   if (isReferenceTrig) {

       h_HT_1tau2L->Fill(HT, mygenEvtWeight);
       h_njets_1tau2L->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_1tau2L_aft->Fill(HT, mygenEvtWeight);
	 h_njets_1tau2L_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }

     }

 }// end 1tau2L

 if (is1tau3L) {

   if (isReferenceTrig) {

       h_HT_1tau3L->Fill(HT, mygenEvtWeight);
       h_njets_1tau3L->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_1tau3L_aft->Fill(HT, mygenEvtWeight);
	 h_njets_1tau3L_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }

     }

 }// end 1tau3L

 if (is2tau0L) {

   if (isReferenceTrig) {

       h_HT_2tau0L->Fill(HT, mygenEvtWeight);
       h_njets_2tau0L->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_2tau0L_aft->Fill(HT, mygenEvtWeight);
	 h_njets_2tau0L_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }

     }

 }// end 2tau0L

 if ((is2tau1e) || (is2tau1mu)) {

   if (isReferenceTrig) {

       h_HT_2tau1L->Fill(HT, mygenEvtWeight);
       h_njets_2tau1L->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_2tau1L_aft->Fill(HT, mygenEvtWeight);
	 h_njets_2tau1L_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }

     }
   
 }// end 2tau1L

 if (is2tau2L) {

   if (isReferenceTrig) {

       h_HT_2tau2L->Fill(HT, mygenEvtWeight);
       h_njets_2tau2L->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_2tau2L_aft->Fill(HT, mygenEvtWeight);
	 h_njets_2tau2L_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }

     }

 }// end 2tau2L
 */
 /////////////////////////
 ///////// MC TRUTH /////
 ///////////////////////
  if (myleptonsMVAT->size() == 1 && mymuonsT->size()==1) {

   h_HT_nocat_truth->Fill(HT, mygenEvtWeight);
   h_njets_nocat_truth->Fill(myjetsL->size(), mygenEvtWeight);
   h_njetsvsHT_nocat_truth->Fill(HT, myjetsL->size(), mygenEvtWeight);
   
   if (myjetsL->size() >= 6) {

     h_HT_nocat_njets_truth->Fill(HT, mygenEvtWeight);
     if (mymuonsT->at(0).Pt() > 25) {

       h_HT_nocat_njets_mupt25_truth->Fill(HT, mygenEvtWeight);
       if(jetptcut) h_HT_nocat_njets_mupt25_jetpt35_truth->Fill(HT, mygenEvtWeight);

     }
   
   }

   if (HT > 500) {

     h_njets_nocat_HT_truth->Fill(myjetsL->size(), mygenEvtWeight);
     if (mymuonsT->at(0).Pt() > 25) {

	   h_njets_nocat_HT_mupt25_truth->Fill(myjetsL->size(), mygenEvtWeight);
	   if (jetptcut) h_njets_nocat_HT_mupt25_jetpt35_truth->Fill(myjetsL->size(), mygenEvtWeight);

	 }

     }

  

   if(isSignalTrig) {

     h_HT_nocat_truth_aft->Fill(HT, mygenEvtWeight);
     h_njets_nocat_truth_aft->Fill(myjetsL->size(), mygenEvtWeight);
     h_njetsvsHT_nocat_truth_aft->Fill(HT, myjetsL->size(), mygenEvtWeight);

     if (myjetsL->size() >= 6){

       h_HT_nocat_njets_truth_aft->Fill(HT, mygenEvtWeight);
       if (mymuonsT->at(0).Pt() > 25) {

	 h_HT_nocat_njets_mupt25_truth_aft->Fill(HT, mygenEvtWeight);
	 if (jetptcut) h_HT_nocat_njets_mupt25_jetpt35_truth_aft->Fill(HT, mygenEvtWeight);

       }

     }
     
     if (HT > 500) {

       h_njets_nocat_HT_truth_aft->Fill(myjetsL->size(), mygenEvtWeight);
       if (mymuonsT->at(0).Pt() > 25) {

		 h_njets_nocat_HT_mupt25_truth_aft->Fill(myjetsL->size(), mygenEvtWeight);
		 if (jetptcut) h_njets_nocat_HT_mupt25_jetpt35_truth_aft->Fill(myjetsL->size(), mygenEvtWeight);

	   }

	 }

   }
  
  }

  /*if (is1tau0L) {

       h_HT_1tau0L_truth->Fill(HT, mygenEvtWeight);
       h_njets_1tau0L_truth->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_1tau0L_truth_aft->Fill(HT, mygenEvtWeight);
	 h_njets_1tau0L_truth_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }
     
   }// end 1tau0L
 

   if ((is1tau1e) || (is1tau1mu)) {

       h_HT_1tau1L_truth->Fill(HT, mygenEvtWeight);
       h_njets_1tau1L_truth->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_1tau1L_truth_aft->Fill(HT, mygenEvtWeight);
	 h_njets_1tau1L_truth_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }


 }// end 1tau1L

 if (is1tau2L) {   

       h_HT_1tau2L_truth->Fill(HT, mygenEvtWeight);
       h_njets_1tau2L_truth->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_1tau2L_truth_aft->Fill(HT, mygenEvtWeight);
	 h_njets_1tau2L_truth_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }


 }// end 1tau2L

 if (is1tau3L) {

       h_HT_1tau3L_truth->Fill(HT, mygenEvtWeight);
       h_njets_1tau3L_truth->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_1tau3L_truth_aft->Fill(HT, mygenEvtWeight);
	 h_njets_1tau3L_truth_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }


 }// end 1tau3L

 if (is2tau0L) {

       h_HT_2tau0L_truth->Fill(HT, mygenEvtWeight);
       h_njets_2tau0L_truth->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_2tau0L_truth_aft->Fill(HT, mygenEvtWeight);
	 h_njets_2tau0L_truth_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }


 }// end 2tau0L

 if ((is2tau1e) || (is2tau1mu)) {
  
          h_HT_2tau1L_truth->Fill(HT, mygenEvtWeight);
       h_njets_2tau1L_truth->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_2tau1L_truth_aft->Fill(HT, mygenEvtWeight);
	 h_njets_2tau1L_truth_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }


 }// end 2tau1L

 if (is2tau2L) {   

          h_HT_2tau2L_truth->Fill(HT, mygenEvtWeight);
       h_njets_2tau2L_truth->Fill(myjetsL->size(), mygenEvtWeight);
       
       if (isSignalTrig)  {
	 
	 h_HT_2tau2L_truth_aft->Fill(HT, mygenEvtWeight);
	 h_njets_2tau2L_truth_aft->Fill(myjetsL->size(), mygenEvtWeight);
 
       }


 }// end 2tau2L
  */

 //}//end if HT cut

 }//end loop over events

 TH1D * totalWeight = new TH1D("totalWeight", "totalWeight", 1, -0.5, 0.5);
 TH1::AddDirectory(kFALSE);
 if (!(file_it->first.find(data) !=std::string::npos)) {  
 totalWeight->Fill(0.0, gen_sum_of_weights);
 }
 TH1::AddDirectory(kTRUE);
 
 outputfile->cd();

 writeTEfficiency(h_HT_nocat, h_HT_nocat_aft, file_it, "e_HT_nocat_");
 if (!(file_it->first.find(data) !=std::string::npos)) writeTEfficiency(h_HT_nocat_truth, h_HT_nocat_truth_aft, file_it, "e_HT_nocat_truth_");

 writeTEfficiency(h_njets_nocat, h_njets_nocat_aft, file_it, "e_njets_nocat_");
 if (!(file_it->first.find(data) !=std::string::npos)) writeTEfficiency(h_njets_nocat_truth, h_njets_nocat_truth_aft, file_it, "e_njets_nocat_truth_");

 writeTEfficiency(h_HT_nocat_njets, h_HT_nocat_njets_aft, file_it, "e_HT_nocat_njets_");
 if (!(file_it->first.find(data) !=std::string::npos)) writeTEfficiency(h_HT_nocat_njets_truth, h_HT_nocat_njets_truth_aft, file_it, "e_HT_nocat_njets_truth_");

 writeTEfficiency(h_njets_nocat_HT, h_njets_nocat_HT_aft, file_it, "e_njets_nocat_HT_");
 if (!(file_it->first.find(data) !=std::string::npos)) writeTEfficiency(h_njets_nocat_HT_truth, h_njets_nocat_HT_truth_aft, file_it, "e_njets_nocat_HT_truth_");

 writeTEfficiency(h_HT_nocat_njets_mupt25, h_HT_nocat_njets_mupt25_aft, file_it, "e_HT_nocat_njets_mupt25_");
 if (!(file_it->first.find(data) !=std::string::npos)) writeTEfficiency(h_HT_nocat_njets_mupt25_truth, h_HT_nocat_njets_mupt25_truth_aft, file_it, "e_HT_nocat_njets_mupt25_truth_");

 writeTEfficiency(h_njets_nocat_HT_mupt25, h_njets_nocat_HT_mupt25_aft, file_it, "e_njets_nocat_HT_mupt25_");
 if (!(file_it->first.find(data) !=std::string::npos)) writeTEfficiency(h_njets_nocat_HT_mupt25_truth, h_njets_nocat_HT_mupt25_truth_aft, file_it, "e_njets_nocat_HT_mupt25_truth_");

 writeTEfficiency(h_HT_nocat_njets_mupt25_jetpt35, h_HT_nocat_njets_mupt25_jetpt35_aft, file_it, "e_HT_nocat_njets_mupt25_jetpt35_");
 if (!(file_it->first.find(data) !=std::string::npos)) writeTEfficiency(h_HT_nocat_njets_mupt25_jetpt35_truth, h_HT_nocat_njets_mupt25_jetpt35_truth_aft, file_it, "e_HT_nocat_njets_mupt25_jetpt35_truth_");

 writeTEfficiency(h_njets_nocat_HT_mupt25_jetpt35, h_njets_nocat_HT_mupt25_jetpt35_aft, file_it, "e_njets_nocat_HT_mupt25_jetpt35_");
 if (!(file_it->first.find(data) !=std::string::npos)) writeTEfficiency(h_njets_nocat_HT_mupt25_jetpt35_truth, h_njets_nocat_HT_mupt25_jetpt35_truth_aft, file_it, "e_njets_nocat_HT_mupt25_jetpt35_truth_");

 writeTEfficiency2D(h_njetsvsHT_nocat, h_njetsvsHT_nocat_aft, file_it, "e_njetsvsHT_nocat_");
 if (!(file_it->first.find(data) !=std::string::npos)) writeTEfficiency2D(h_njetsvsHT_nocat_truth, h_njetsvsHT_nocat_truth_aft, file_it, "e_njetsvsHT_nocat_truth_");

 if (!(file_it->first.find(data) !=std::string::npos)) {
 std::string hTotalWeightName(totalWeight->GetName());
 hTotalWeightName.append("_");
 hTotalWeightName.append(file_it->first);
 totalWeight->Write(hTotalWeightName.c_str());
 }

 h_HT_signal->Write();
 h_njets_signal->Write();
 
 delete h_HT_nocat;
 delete h_njets_nocat;
 delete h_HT_nocat_njets;
 delete h_njets_nocat_HT;
 delete h_HT_nocat_njets_mupt25;
 delete h_njets_nocat_HT_mupt25;
 delete h_HT_nocat_njets_mupt25_jetpt35;
 delete h_njets_nocat_HT_mupt25_jetpt35;
 delete h_njetsvsHT_nocat;
 delete h_HT_nocat_aft;
 delete h_njets_nocat_aft;
 delete h_HT_nocat_njets_aft;
 delete h_njets_nocat_HT_aft;
 delete h_HT_nocat_njets_mupt25_aft;
 delete h_njets_nocat_HT_mupt25_aft;
 delete h_HT_nocat_njets_mupt25_jetpt35_aft;
 delete h_njets_nocat_HT_mupt25_jetpt35_aft;
 delete h_njetsvsHT_nocat_aft;
 delete h_HT_nocat_truth;
 delete h_njets_nocat_truth;
 delete h_HT_nocat_njets_truth;
 delete h_njets_nocat_HT_truth;
 delete h_HT_nocat_njets_mupt25_truth;
 delete h_njets_nocat_HT_mupt25_truth;
 delete h_HT_nocat_njets_mupt25_jetpt35_truth;
 delete h_njets_nocat_HT_mupt25_jetpt35_truth;
 delete h_njetsvsHT_nocat_truth;
 delete h_HT_nocat_truth_aft;
 delete h_njets_nocat_truth_aft;
 delete h_HT_nocat_njets_truth_aft;
 delete h_njets_nocat_HT_truth_aft;
 delete h_HT_nocat_njets_mupt25_truth_aft;
 delete h_njets_nocat_HT_mupt25_truth_aft;
 delete h_HT_nocat_njets_mupt25_jetpt35_truth_aft;
 delete h_njets_nocat_HT_mupt25_jetpt35_truth_aft;
 delete h_njetsvsHT_nocat_truth_aft;
 delete genEvtWeights;
 delete totalWeight;
 delete h_HT_signal;
 delete h_njets_signal;

 mychain.Reset();
 mychain2.Reset();

 file_it++;

 }//end loop over files

 
 /*
 writeTEfficiency(h_HT_1tau0L, h_HT_1tau0L_aft, "e_HT_1tau0L");
 writeTEfficiency(h_HT_1tau0L_truth, h_HT_1tau0L_truth_aft, "e_HT_1tau0L_truth");

 writeTEfficiency(h_HT_1tau1L, h_HT_1tau1L_aft, "e_HT_1tau1L");
 writeTEfficiency(h_HT_1tau1L_truth, h_HT_1tau1L_truth_aft, "e_HT_1tau1L_truth");

 writeTEfficiency(h_HT_1tau2L, h_HT_1tau2L_aft, "e_HT_1tau2L");
 writeTEfficiency(h_HT_1tau2L_truth, h_HT_1tau2L_truth_aft, "e_HT_1tau2L_truth");

 writeTEfficiency(h_HT_1tau3L, h_HT_1tau3L_aft, "e_HT_1tau3L");
 writeTEfficiency(h_HT_1tau3L_truth, h_HT_1tau3L_truth_aft, "e_HT_1tau3L_truth");

 writeTEfficiency(h_HT_2tau0L, h_HT_2tau0L_aft, "e_HT_2tau0L");
 writeTEfficiency(h_HT_2tau0L_truth, h_HT_2tau0L_truth_aft, "e_HT_2tau0L_truth");

 writeTEfficiency(h_HT_2tau1L, h_HT_2tau1L_aft, "e_HT_2tau1L");
 writeTEfficiency(h_HT_2tau1L_truth, h_HT_2tau1L_truth_aft, "e_HT_2tau1L_truth");

 writeTEfficiency(h_HT_2tau2L, h_HT_2tau2L_aft, "e_HT_2tau2L");
 writeTEfficiency(h_HT_2tau2L_truth, h_HT_2tau2L_truth_aft, "e_HT_2tau2L_truth");
 
 TH1F * h_HT_1tauML = (TH1F*)h_HT_1tau2L->Clone("h_HT_1tauML");
 TH1F * h_HT_1tauML_aft = (TH1F*)h_HT_1tau2L_aft->Clone("h_HT_1tauML_aft");
 TH1F * h_HT_1tauML_truth = (TH1F*)h_HT_1tau2L_truth->Clone("h_HT_1tauML_truth");
 TH1F * h_HT_1tauML_truth_aft = (TH1F*)h_HT_1tau2L_truth_aft->Clone("h_HT_1tauML_truth_aft");

 h_HT_1tauML->Add(h_HT_1tau3L);
 h_HT_1tauML_aft->Add(h_HT_1tau3L_aft);
 h_HT_1tauML_truth->Add(h_HT_1tau3L_truth);
 h_HT_1tauML_truth_aft->Add(h_HT_1tau3L_truth_aft);
 
 TH1F * h_HT_2tauML = (TH1F*)h_HT_2tau1L->Clone("h_HT_2tauML");
 TH1F * h_HT_2tauML_aft = (TH1F*)h_HT_2tau1L_aft->Clone("h_HT_2tauML_aft");
 TH1F * h_HT_2tauML_truth = (TH1F*)h_HT_2tau1L_truth->Clone("h_HT_2tauML_truth");
 TH1F * h_HT_2tauML_truth_aft = (TH1F*)h_HT_2tau1L_truth_aft->Clone("h_HT_2tauML_truth_aft");
 
 h_HT_2tauML->Add(h_HT_2tau2L);
 h_HT_2tauML_aft->Add(h_HT_2tau2L_aft);
 h_HT_2tauML_truth->Add(h_HT_2tau2L_truth);
 h_HT_2tauML_truth_aft->Add(h_HT_2tau2L_truth_aft);

 writeTEfficiency(h_HT_1tauML, h_HT_1tauML_aft, "e_HT_1tauML");
 writeTEfficiency(h_HT_1tauML_truth, h_HT_1tauML_truth_aft, "e_HT_1tauML_truth");

 writeTEfficiency(h_HT_2tauML, h_HT_2tauML_aft, "e_HT_2tauML");
 writeTEfficiency(h_HT_2tauML_truth, h_HT_2tauML_truth_aft, "e_HT_2tauML_truth");




 writeTEfficiency(h_njets_nocat, h_njets_nocat_aft, "e_njets_nocat");
 writeTEfficiency(h_njets_nocat_truth, h_njets_nocat_truth_aft, "e_njets_nocat_truth");

 writeTEfficiency(h_njets_nocat_HT, h_njets_nocat_HT_aft, "e_njets_nocat_HT");
 writeTEfficiency(h_njets_nocat_HT_truth, h_njets_nocat_HT_truth_aft, "e_njets_nocat_HT_truth");

 writeTEfficiency(h_njets_nocat_HT_mupt25, h_njets_nocat_HT_mupt25_aft, "e_njets_nocat_HT_mupt25");
 writeTEfficiency(h_njets_nocat_HT_mupt25_truth, h_njets_nocat_HT_mupt25_truth_aft, "e_njets_nocat_HT_mupt25_truth");

 writeTEfficiency(h_njets_1tau0L, h_njets_1tau0L_aft, "e_njets_1tau0L");
 writeTEfficiency(h_njets_1tau0L_truth, h_njets_1tau0L_truth_aft, "e_njets_1tau0L_truth");

 writeTEfficiency(h_njets_1tau1L, h_njets_1tau1L_aft, "e_njets_1tau1L");
 writeTEfficiency(h_njets_1tau1L_truth, h_njets_1tau1L_truth_aft, "e_njets_1tau1L_truth");

 writeTEfficiency(h_njets_1tau2L, h_njets_1tau2L_aft, "e_njets_1tau2L");
 writeTEfficiency(h_njets_1tau2L_truth, h_njets_1tau2L_truth_aft, "e_njets_1tau2L_truth");

 writeTEfficiency(h_njets_1tau3L, h_njets_1tau3L_aft, "e_njets_1tau3L");
 writeTEfficiency(h_njets_1tau3L_truth, h_njets_1tau3L_truth_aft, "e_njets_1tau3L_truth");

 writeTEfficiency(h_njets_2tau0L, h_njets_2tau0L_aft, "e_njets_2tau0L");
 writeTEfficiency(h_njets_2tau0L_truth, h_njets_2tau0L_truth_aft, "e_njets_2tau0L_truth");

 writeTEfficiency(h_njets_2tau1L, h_njets_2tau1L_aft, "e_njets_2tau1L");
 writeTEfficiency(h_njets_2tau1L_truth, h_njets_2tau1L_truth_aft, "e_njets_2tau1L_truth");

 writeTEfficiency(h_njets_2tau2L, h_njets_2tau2L_aft, "e_njets_2tau2L");
 writeTEfficiency(h_njets_2tau2L_truth, h_njets_2tau2L_truth_aft, "e_njets_2tau2L_truth");
 
 TH1F * h_njets_1tauML = (TH1F*)h_njets_1tau2L->Clone("h_njets_1tauML");
 TH1F * h_njets_1tauML_aft = (TH1F*)h_njets_1tau2L_aft->Clone("h_njets_1tauML_aft");
 TH1F * h_njets_1tauML_truth = (TH1F*)h_njets_1tau2L_truth->Clone("h_njets_1tauML_truth");
 TH1F * h_njets_1tauML_truth_aft = (TH1F*)h_njets_1tau2L_truth_aft->Clone("h_njets_1tauML_truth_aft");

 h_njets_1tauML->Add(h_njets_1tau3L);
 h_njets_1tauML_aft->Add(h_njets_1tau3L_aft);
 h_njets_1tauML_truth->Add(h_njets_1tau3L_truth);
 h_njets_1tauML_truth_aft->Add(h_njets_1tau3L_truth_aft);
 
 TH1F * h_njets_2tauML = (TH1F*)h_njets_2tau1L->Clone("h_njets_2tauML");
 TH1F * h_njets_2tauML_aft = (TH1F*)h_njets_2tau1L_aft->Clone("h_njets_2tauML_aft");
 TH1F * h_njets_2tauML_truth = (TH1F*)h_njets_2tau1L_truth->Clone("h_njets_2tauML_truth");
 TH1F * h_njets_2tauML_truth_aft = (TH1F*)h_njets_2tau1L_truth_aft->Clone("h_njets_2tauML_truth_aft");
 
 h_njets_2tauML->Add(h_njets_2tau2L);
 h_njets_2tauML_aft->Add(h_njets_2tau2L_aft);
 h_njets_2tauML_truth->Add(h_njets_2tau2L_truth);
 h_njets_2tauML_truth_aft->Add(h_njets_2tau2L_truth_aft);

 writeTEfficiency(h_njets_1tauML, h_njets_1tauML_aft, "e_njets_1tauML");
 writeTEfficiency(h_njets_1tauML_truth, h_njets_1tauML_truth_aft, "e_njets_1tauML_truth");

 writeTEfficiency(h_njets_2tauML, h_njets_2tauML_aft, "e_njets_2tauML");
 writeTEfficiency(h_njets_2tauML_truth, h_njets_2tauML_truth_aft, "e_njets_2tauML_truth");
 */
 outputfile->Close();
 delete outputfile;

 gBenchmark->Show("running time");

}//end



void writeTEfficiency(TH1F* hBef, TH1F* hAft, map<string, string>::iterator file_it, TString name) {

  std::string hBefName(hBef->GetName());
  hBefName.append("_");
  hBefName.append(file_it->first);
  std::string hAftName(hAft->GetName());
  hAftName.append("_");
  hAftName.append(file_it->first);
  hBef->Write(hBefName.c_str());
  hAft->Write(hAftName.c_str());
  //TH1F *hRatio = (TH1F*)hAft->Clone("");
  //hRatio->Divide(hBef);
  //hRatio->Write(name);
  
  TEfficiency *TEff = 0;
  if(TEfficiency::CheckConsistency(*hAft, *hBef)){
            
    TEff = new TEfficiency(*hAft, *hBef);
    TEff->Write(name+file_it->first);
    delete TEff;
    }
}
void writeTEfficiency2D(TH2F* hBef, TH2F* hAft, map<string, string>::iterator file_it, TString name) {

  std::string hBefName(hBef->GetName());
  hBefName.append("_");
  hBefName.append(file_it->first);
  std::string hAftName(hAft->GetName());
  hAftName.append("_");
  hAftName.append(file_it->first);
  hBef->Write(hBefName.c_str());
  hAft->Write(hAftName.c_str());
  //TH1F *hRatio = (TH1F*)hAft->Clone("");
  //hRatio->Divide(hBef);
  //hRatio->Write(name);
  
  TEfficiency *TEff = 0;
  if(TEfficiency::CheckConsistency(*hAft, *hBef)){
            
    TEff = new TEfficiency(*hAft, *hBef);
    TEff->Write(name+file_it->first);
    delete TEff;
    }
  
}
