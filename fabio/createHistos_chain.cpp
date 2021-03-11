#include <iostream>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TBenchmark.h>
#include "createHistos_chain.h"

//using namespace std;

void createHistos_chain() {

gBenchmark->Start("running time");

gROOT->ProcessLine(".L Loader.C+");
// gROOT->SetBatch(kTRUE);

map<string, string>::iterator file_it = file.begin();

while (file_it != file.end()) { //////////////////////// LOOP OVER FILES ///////////////////////

cout << "Reading process " << file_it->second << "..." << endl;

TString input_base_dir = file_it->second + "/";

TChain mychain("tree");
mychain.Add(input_base_dir + "v3*.root");
TChain mychain2("allevents");
mychain2.Add(input_base_dir + "v3*.root");

cout << "Computing the sum of gen event weights..." << endl;

TH1F * genEvtWeights = new TH1F("genEvtWeights", "genEvtWeights", 1000000, -10, 10 );
mychain2.Project(genEvtWeights->GetName(), "genWeight_allEvents");
Double_t gen_sum_of_weights = genEvtWeights->GetMean()*genEvtWeights->GetEntries();
 cout << gen_sum_of_weights << endl;

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

//initializing yield containers
TH1F * h_1tau0L = new TH1F("1tau0L", "", 30, 0, 30);
TH1F * h_1tau1e = new TH1F("1tau1e", "", 30, 0, 30);
TH1F * h_1tau1mu = new TH1F("1tau1mu", "", 30, 0, 30);
TH1F * h_1tau2L = new TH1F("1tau2OSL", "", 30, 0, 30);
TH1F * h_1tau3L = new TH1F("1tau3L", "", 30, 0, 30);
TH1F * h_2tau0L = new TH1F("2tau0L", "", 30, 0, 30);
TH1F * h_2tau1e = new TH1F("2tau1e", "", 30, 0, 30);
TH1F * h_2tau1mu = new TH1F("2tau1mu", "", 30, 0, 30);
TH1F * h_2tau2L = new TH1F("2tau2OSL", "", 30, 0, 30);

// initializing sum of weights 
//TH1F * GenEventWeight;
//GenEventWeight = (TH1F*)inputfile->Get("h_genweight");
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// LOOP OVER EVENTS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Long64_t nevents = mychain.GetEntries();

for ( Long64_t ievent = 0; ievent < nevents; ++ievent ){
  if (ievent > 100) break;
  if ( !(ievent % 100000 ) ) cout << "ievent  =  " << ievent << endl;
   //get i-th entry in tree
   mychain.GetEntry( ievent );

   /////////////////////////////////////////////////////////////////////
   ///////////////////// DEFINE CATEGORY CUTS //////////////////////////
   /////////////////////////////////////////////////////////////////////

 bool is1tau0L = (mytausT->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2);
 bool is1tau1e = (mytausT->size()==1 && myleptonsMVAT->size() == 1 && myelesMVAT->size()==1 && myjetsL->size()>=6 && mybjetsM->size()>=2);
 bool is1tau1mu = (mytausT->size()==1 && myleptonsMVAT->size() == 1 && mymuonsT->size()==1 &&  myjetsL->size()>=4 && mybjetsM->size()>=2);
 bool is1tau2L = (mytausT->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2);
 bool is1tau3L = (mytausT->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2);
 bool is2tau0L = (mytausT->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2);
 bool is2tau1e = (mytausT->size()==2 && myleptonsMVAT->size() == 1 && myelesMVAT->size()==1 &&  myjetsL->size()>=4 && mybjetsM->size()>=2);
 bool is2tau1mu = (mytausT->size()==2 && myleptonsMVAT->size() == 1 && mymuonsT->size()==1 &&  myjetsL->size()>=4 && mybjetsM->size()>=2);
 bool is2tau2L = (mytausT->size()==2 && (myelesMVAT->size()+mymuonsT->size())==2 && myjetsL->size()>=2 && mybjetsM->size()>=2);

 if (is1tau0L) h_1tau0L->Fill(myjetsL->size(), mygenEvtWeight);
 if (is1tau1e) h_1tau1e->Fill(myjetsL->size(), mygenEvtWeight);
 if (is1tau1mu) h_1tau1mu->Fill(myjetsL->size(), mygenEvtWeight);
 if (is1tau2L) h_1tau2L->Fill(myjetsL->size(), mygenEvtWeight);
 if (is1tau3L) h_1tau3L->Fill(myjetsL->size(), mygenEvtWeight);
 if (is2tau0L) h_2tau0L->Fill(myjetsL->size(), mygenEvtWeight);
 if (is2tau1e) h_2tau1e->Fill(myjetsL->size(), mygenEvtWeight);
 if (is2tau1mu) h_2tau1mu->Fill(myjetsL->size(), mygenEvtWeight);
 if (is2tau2L) h_2tau2L->Fill(myjetsL->size(), mygenEvtWeight);
 
 } // end loop over events

 y_1tau0L.insert( {file_it->first, *h_1tau0L} );
 y_1tau1e.insert( {file_it->first, *h_1tau1e} );
 y_1tau1mu.insert( {file_it->first, *h_1tau1mu} );
 y_1tau2L.insert( {file_it->first, *h_1tau2L} );
 y_1tau3L.insert( {file_it->first, *h_1tau3L} );
 y_2tau0L.insert( {file_it->first, *h_2tau0L} );
 y_2tau1e.insert( {file_it->first, *h_2tau1e} );
 y_2tau1mu.insert( {file_it->first, *h_2tau1mu} );
 y_2tau2L.insert( {file_it->first, *h_2tau2L} );
  
 //total_weight.insert({file_it->first, *GenEventWeight});
 
//cout << "y_1tau0L.size(): " << y_1tau0L.size() << endl; 
 
 
 delete h_1tau0L;
 delete h_1tau1e;
 delete h_1tau1mu;
 delete h_1tau2L;
 delete h_1tau3L;
 delete h_2tau0L;
 delete h_2tau1e;
 delete h_2tau1mu;
 delete h_2tau2L;
 //delete GenEventWeight;


 //inputfile->Close();
 //delete inputfile;
 file_it++;
 } // end loop over files
 
 TFile *outputfile = new TFile( "Histograms_v31.root", "RECREATE" );
 
 // loop through each category map and save the corresponding histograms
map<string, TH1F>::iterator y_1tau0L_it = y_1tau0L.begin();
 while (y_1tau0L_it != y_1tau0L.end()) {
   y_1tau0L_it->second.Write( (y_1tau0L_it->first + "_1tau0L").c_str() );
   y_1tau0L_it++;
}

map<string, TH1F>::iterator y_1tau1e_it = y_1tau1e.begin();
 while (y_1tau1e_it != y_1tau1e.end()) {
   y_1tau1e_it->second.Write( (y_1tau1e_it->first + "_1tau1e").c_str() );
   y_1tau1e_it++;
}

 map<string, TH1F>::iterator y_1tau1mu_it = y_1tau1mu.begin();
 while (y_1tau1mu_it != y_1tau1mu.end()) {
   y_1tau1mu_it->second.Write( (y_1tau1mu_it->first + "_1tau1mu").c_str() );
   y_1tau1mu_it++;
 }
 
 map<string, TH1F>::iterator y_1tau2L_it = y_1tau2L.begin();
 while (y_1tau2L_it != y_1tau2L.end()) {
   y_1tau2L_it->second.Write( (y_1tau2L_it->first + "_1tau2L").c_str() );
   y_1tau2L_it++;
 }

 map<string, TH1F>::iterator y_1tau3L_it = y_1tau3L.begin();
 while (y_1tau3L_it != y_1tau3L.end()) {
   y_1tau3L_it->second.Write( (y_1tau3L_it->first + "_1tau3L").c_str() );
   y_1tau3L_it++;
 }

 map<string, TH1F>::iterator y_2tau0L_it = y_2tau0L.begin();
 while (y_2tau0L_it != y_2tau0L.end()) {
   y_2tau0L_it->second.Write( (y_2tau0L_it->first + "_2tau0L").c_str() );
   y_2tau0L_it++;
 }

 map<string, TH1F>::iterator y_2tau1e_it = y_2tau1e.begin();
 while (y_2tau1e_it != y_2tau1e.end()) {
   y_2tau1e_it->second.Write( (y_2tau1e_it->first + "_2tau1e").c_str() );
   y_2tau1e_it++;
 }

 map<string, TH1F>::iterator y_2tau1mu_it = y_2tau1mu.begin();
 while (y_2tau1mu_it != y_2tau1mu.end()) {
   y_2tau1mu_it->second.Write( (y_2tau1mu_it->first + "_2tau1mu").c_str() );
   y_2tau1mu_it++;
 }

 map<string, TH1F>::iterator y_2tau2L_it = y_2tau2L.begin();
 while (y_2tau2L_it != y_2tau2L.end()) {
   y_2tau2L_it->second.Write( (y_2tau2L_it->first + "_2tau2L").c_str() );
   y_2tau2L_it++;
 }

 map<string, TH1F>::iterator total_weight_it = total_weight.begin();
 while (total_weight_it != total_weight.end()) {
   total_weight_it->second.Write( (total_weight_it->first + "_GenEventWeight").c_str() );
   total_weight_it++;
 }

 outputfile->Close();
 delete outputfile;

 gBenchmark->Show("running time");
 
}
