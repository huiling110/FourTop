#include <iostream>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TBenchmark.h>
#include <TEfficiency.h>
#include "trigEff_vs_HT.h"
#include <TChain.h>
#include <TLorentzVector.h>
#include <TROOT.h> //for gROOT
#include <TSystem.h> // for gSystem

//using namespace std;

void trigEff_vs_HT() {

gBenchmark->Start("running time");

gROOT->ProcessLine(".L Loader.C+");

 //histograms: MC wrt reference
TH1F * h_HT_nocat = new TH1F("h_HT_nocat", "h_HT_nocat; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau0L = new TH1F("h_HT_1tau0L", "h_HT_1tau0L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau1L = new TH1F("h_HT_1tau1L", "h_HT_1tau1L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau2L = new TH1F("h_HT_1tau2L", "h_HT_1tau2L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau3L = new TH1F("h_HT_1tau3L", "h_HT_1tau3L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_2tau0L = new TH1F("h_HT_2tau0L", "h_HT_2tau0L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_2tau1L = new TH1F("h_HT_2tau1L", "h_HT_2tau1L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_2tau2L = new TH1F("h_HT_2tau2L", "h_HT_2tau2L; H_{T} [GeV];", 15, 0, 1500);

TH1F * h_HT_nocat_aft = new TH1F("h_HT_nocat_aft", "h_HT_nocat; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau0L_aft = new TH1F("h_HT_1tau0L_aft", "h_HT_1tau0L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau1L_aft = new TH1F("h_HT_1tau1L_aft", "h_HT_1tau1L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau2L_aft = new TH1F("h_HT_1tau2L_aft", "h_HT_1tau2L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau3L_aft = new TH1F("h_HT_1tau3L_aft", "h_HT_1tau3L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_2tau0L_aft = new TH1F("h_HT_2tau0L_aft", "h_HT_2tau0L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_2tau1L_aft = new TH1F("h_HT_2tau1L_aft", "h_HT_2tau1L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_2tau2L_aft = new TH1F("h_HT_2tau2L_aft", "h_HT_2tau2L; H_{T} [GeV];", 15, 0, 1500);
//histograms: MC truth
TH1F * h_HT_nocat_truth = new TH1F("h_HT_nocat_truth", "h_HT_nocat; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau0L_truth = new TH1F("h_HT_1tau0L_truth", "h_HT_1tau0L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau1L_truth = new TH1F("h_HT_1tau1L_truth", "h_HT_1tau1L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau2L_truth = new TH1F("h_HT_1tau2L_truth", "h_HT_1tau2L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau3L_truth = new TH1F("h_HT_1tau3L_truth", "h_HT_1tau3L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_2tau0L_truth = new TH1F("h_HT_2tau0L_truth", "h_HT_2tau0L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_2tau1L_truth = new TH1F("h_HT_2tau1L_truth", "h_HT_2tau1L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_2tau2L_truth = new TH1F("h_HT_2tau2L_truth", "h_HT_2tau2L; H_{T} [GeV];", 15, 0, 1500);

TH1F * h_HT_nocat_truth_aft = new TH1F("h_HT_nocat_truth_aft", "h_HT_nocat; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau0L_truth_aft = new TH1F("h_HT_1tau0L_truth_aft", "h_HT_1tau0L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau1L_truth_aft = new TH1F("h_HT_1tau1L_truth_aft", "h_HT_1tau1L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau2L_truth_aft = new TH1F("h_HT_1tau2L_truth_aft", "h_HT_1tau2L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_1tau3L_truth_aft = new TH1F("h_HT_1tau3L_truth_aft", "h_HT_1tau3L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_2tau0L_truth_aft = new TH1F("h_HT_2tau0L_truth_aft", "h_HT_2tau0L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_2tau1L_truth_aft = new TH1F("h_HT_2tau1L_truth_aft", "h_HT_2tau1L; H_{T} [GeV];", 15, 0, 1500);
TH1F * h_HT_2tau2L_truth_aft = new TH1F("h_HT_2tau2L_truth_aft", "h_HT_2tau2L; H_{T} [GeV];", 15, 0, 1500);

map<string, string>::iterator file_it = file.begin();

while (file_it != file.end()) { //////////////////////// LOOP OVER FILES ///////////////////////

cout << "Reading process " << file_it->second << "..." << endl;
TString input_base_dir = file_it->second + "/";
gSystem->RedirectOutput("/dev/null"); // do not show errors when not finding the following files: will print a custom error a few lines below
TFile * checkinput = new TFile(input_base_dir + "v3_1-1.root");
TFile * checkinput2 = new TFile(input_base_dir + "v3_1.root");
gSystem->RedirectOutput(0,0); // restore the printing to normal behavior
if (checkinput->IsZombie() && checkinput2->IsZombie()){
cout << "+++ INPUT FILES NOT FOUND! SKIPPING +++" << endl;
 file_it++;
continue;
} 

TChain mychain("tree");
mychain.Add(input_base_dir + "v3*.root");
TChain mychain2("allevents");
mychain2.Add(input_base_dir + "v3*.root");

cout << "Computing the sum of gen event weights..." << endl;
TH1::StatOverflows(kTRUE);
TH1D * genEvtWeights = new TH1D("genEvtWeights", "genEvtWeights", 10, -10, 10 );
mychain2.Project(genEvtWeights->GetName(), "genWeight_allEvents");
cout << "genEvtWeights->GetMean(): " << genEvtWeights->GetMean() << endl;
cout << "genEvtWeights->GetEntries(): " << genEvtWeights->GetEntries() << endl; 
double gen_sum_of_weights = genEvtWeights->GetMean()*genEvtWeights->GetEntries();
cout << gen_sum_of_weights << endl;
TH1::StatOverflows(kFALSE);

double mygenEvtWeight = 0;
mychain.SetBranchAddress( "EVENT_genWeight_", &mygenEvtWeight );

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

Long64_t nevents = mychain.GetEntries();

for ( Long64_t ievent = 0; ievent < nevents; ++ievent ) {
  //if (ievent > 100) break;
  if ( !(ievent % 100000 ) ) cout << "ievent  =  " << ievent << endl;
   //get i-th entry in tree
   mychain.GetEntry( ievent );

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

 bool isSignalTrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1);
 bool isReferenceTrig = (myHLT_IsoMu24 == 1 || myHLT_IsoMu27 == 1);
 
 //compute HT
 float HT = 0.0;
 for (unsigned int i = 0; i < myjetsL->size(); i ++)  {
   
   HT += myjetsL->at(i).Pt();

 }

 //compute HT(jet+lepton)
 float HT_jl = HT;

 for (unsigned int i = 0; i < myleptonsMVAT->size(); i++) {

   HT_jl += myleptonsMVAT->at(i).Pt();
   
 }
   
//   if (HT_jl > 400) {


 if (isReferenceTrig) {

   h_HT_nocat->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);

   if(isSignalTrig) {

     h_HT_nocat_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
     
   }

 }


   if (is1tau0L) {

     if (isReferenceTrig) {

       h_HT_1tau0L->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_1tau0L_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);

     }
     
     
   }// end 1tau0L
 

   if ((is1tau1e) || (is1tau1mu)) {

     if (isReferenceTrig) {

       h_HT_1tau1L->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_1tau1L_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);

     }

 }// end 1tau1L

 if (is1tau2L) {
 
   if (isReferenceTrig) {

       h_HT_1tau2L->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_1tau2L_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);

     }

 }// end 1tau2L

 if (is1tau3L) {

   if (isReferenceTrig) {

       h_HT_1tau3L->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_1tau3L_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);

     }

 }// end 1tau3L

 if (is2tau0L) {

  if (isReferenceTrig) {

       h_HT_2tau0L->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_2tau0L_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);

     }

 }// end 2tau0L

 if ((is2tau1e) || (is2tau1mu)) {

   if (isReferenceTrig) {

       h_HT_2tau1L->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_2tau1L_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);

     }

 }// end 2tau1L

 if (is2tau2L) {

   if (isReferenceTrig) {

       h_HT_2tau2L->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_2tau2L_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);

     }

 }// end 2tau2L

 /////////////////////////
 ///////// MC TRUTH /////
 ///////////////////////
  

   h_HT_nocat_truth->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);

   if(isSignalTrig) {

     h_HT_nocat_truth_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
     
   }


   if (is1tau0L) {

       h_HT_1tau0L_truth->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_1tau0L_truth_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
    
     
   }// end 1tau0L
 

   if ((is1tau1e) || (is1tau1mu)) {

       h_HT_1tau1L_truth->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_1tau1L_truth_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);

 }// end 1tau1L

 if (is1tau2L) {   

       h_HT_1tau2L_truth->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_1tau2L_truth_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);

 }// end 1tau2L

 if (is1tau3L) {

       h_HT_1tau3L_truth->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_1tau3L_truth_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);


 }// end 1tau3L

 if (is2tau0L) {

       h_HT_2tau0L_truth->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_2tau0L_truth_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);


 }// end 2tau0L

 if ((is2tau1e) || (is2tau1mu)) {
  
       h_HT_2tau1L_truth->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_2tau1L_truth_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);

 }// end 2tau1L

 if (is2tau2L) {   

       h_HT_2tau2L_truth->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);
       
       if (isSignalTrig)  h_HT_2tau2L_truth_aft->Fill(HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/gen_sum_of_weights);


 }// end 2tau2L


 //}//end if HT cut

 }//end loop over events

 delete genEvtWeights;

 mychain.Reset();
 mychain2.Reset();

 file_it++;

 }//end loop over files

//TFile *outputfile = new TFile( "trigEff_vs_HT_output.root", "RECREATE" ); 
 TFile *outputfile = new TFile( "asdasd.root", "RECREATE" );
 writeTEfficiency(h_HT_nocat, h_HT_nocat_aft, "e_HT_nocat");
 writeTEfficiency(h_HT_nocat_truth, h_HT_nocat_truth_aft, "e_HT_nocat_truth");

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
 
 TH1F * h_HT_1tauML = (TH1F*)h_HT_1tau2L->Clone();
 TH1F * h_HT_1tauML_aft = (TH1F*)h_HT_1tau2L_aft->Clone();
 TH1F * h_HT_1tauML_truth = (TH1F*)h_HT_1tau2L_truth->Clone();
 TH1F * h_HT_1tauML_truth_aft = (TH1F*)h_HT_1tau2L_truth_aft->Clone();

 h_HT_1tauML->Add(h_HT_1tau3L);
 h_HT_1tauML_aft->Add(h_HT_1tau3L_aft);
 h_HT_1tauML_truth->Add(h_HT_1tau3L_truth);
 h_HT_1tauML_truth_aft->Add(h_HT_1tau3L_truth_aft);
 
 TH1F * h_HT_2tauML = (TH1F*)h_HT_2tau1L->Clone();
 TH1F * h_HT_2tauML_aft = (TH1F*)h_HT_2tau1L_aft->Clone();
 TH1F * h_HT_2tauML_truth = (TH1F*)h_HT_2tau1L_truth->Clone();
 TH1F * h_HT_2tauML_truth_aft = (TH1F*)h_HT_2tau1L_truth_aft->Clone();
 
 h_HT_2tauML->Add(h_HT_2tau2L);
 h_HT_2tauML_aft->Add(h_HT_2tau2L_aft);
 h_HT_2tauML_truth->Add(h_HT_2tau2L_truth);
 h_HT_2tauML_truth_aft->Add(h_HT_2tau2L_truth_aft);

 writeTEfficiency(h_HT_1tauML, h_HT_1tauML_aft, "e_HT_1tauML");
 writeTEfficiency(h_HT_1tauML_truth, h_HT_1tauML_truth_aft, "e_HT_1tauML_truth");

 writeTEfficiency(h_HT_2tauML, h_HT_2tauML_aft, "e_HT_2tauML");
 writeTEfficiency(h_HT_2tauML_truth, h_HT_2tauML_truth_aft, "e_HT_2tauML_truth");

 outputfile->Close();
 delete outputfile;

 gBenchmark->Show("running time");

}//end



void writeTEfficiency(TH1F* hBef, TH1F* hAft, TString name) {

  hBef->Write();
  hAft->Write();
  TH1F *hRatio = (TH1F*)hAft->Clone("");
  hRatio->Divide(hBef);
  hRatio->Write(name);
  /*
  TEfficiency *TEff = 0;
  if(TEfficiency::CheckConsistency(*hAft, *hBef)){
            
    TEff = new TEfficiency(*hAft, *hBef);
    TEff->Write(name);
    delete TEff;
    }
  */
}
