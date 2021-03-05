#include <iostream>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TBenchmark.h>
#include "createHistos.h"

//using namespace std;

void createHistos() {

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

//initializing yield containers
TH1F * h_1tau0L = new TH1F("1tau0L", "", 30, 0, 30);
TH1F * h_1tau1e = new TH1F("1tau1e", "", 30, 0, 30);
TH1F * h_1tau1mu = new TH1F("1tau1mu", "", 30, 0, 30);
TH1F * h_1tau2OSL = new TH1F("1tau2OSL", "", 30, 0, 30);
TH1F * h_1tau2SSL = new TH1F("1tau2SSL", "", 30, 0, 30);
TH1F * h_1tau3L = new TH1F("1tau3L", "", 30, 0, 30);
TH1F * h_2tau0L = new TH1F("2tau0L", "", 30, 0, 30);
TH1F * h_2tau1e = new TH1F("2tau1e", "", 30, 0, 30);
TH1F * h_2tau1mu = new TH1F("2tau1mu", "", 30, 0, 30);
TH1F * h_2tau2OSL = new TH1F("2tau2OSL", "", 30, 0, 30);
TH1F * h_2tau2SSL = new TH1F("2tau2SSL", "", 30, 0, 30);

// initializing sum of weights 
TH1F * GenEventWeight;
GenEventWeight = (TH1F*)inputfile->Get("h_genweight");
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// LOOP OVER EVENTS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Long64_t nevents = evt->GetEntries();

for ( Long64_t ievent = 0; ievent < nevents; ++ievent ){
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

 if (is1tau0L) h_1tau0L->Fill(myjetsL_number, mygenEvtWeight);
 if (is1tau1e) h_1tau1e->Fill(myjetsL_number, mygenEvtWeight);
 if (is1tau1mu) h_1tau1mu->Fill(myjetsL_number, mygenEvtWeight);
 if (is1tau2OSL) h_1tau2OSL->Fill(myjetsL_number, mygenEvtWeight);
 if (is1tau2SSL) h_1tau2SSL->Fill(myjetsL_number, mygenEvtWeight);
 if (is1tau3L) h_1tau3L->Fill(myjetsL_number, mygenEvtWeight);
 if (is2tau0L) h_2tau0L->Fill(myjetsL_number, mygenEvtWeight);
 if (is2tau1e) h_2tau1e->Fill(myjetsL_number, mygenEvtWeight);
 if (is2tau1mu) h_2tau1mu->Fill(myjetsL_number, mygenEvtWeight);
 if (is2tau2OSL) h_2tau2OSL->Fill(myjetsL_number, mygenEvtWeight);
 if (is2tau2SSL) h_2tau2SSL->Fill(myjetsL_number, mygenEvtWeight);

 } // end loop over events

 y_1tau0L.insert( {file_it->first, *h_1tau0L} );
 y_1tau1e.insert( {file_it->first, *h_1tau1e} );
 y_1tau1mu.insert( {file_it->first, *h_1tau1mu} );
 y_1tau2OSL.insert( {file_it->first, *h_1tau2OSL} );
 y_1tau2SSL.insert( {file_it->first, *h_1tau2SSL} );
 y_1tau3L.insert( {file_it->first, *h_1tau3L} );
 y_2tau0L.insert( {file_it->first, *h_2tau0L} );
 y_2tau1e.insert( {file_it->first, *h_2tau1e} );
 y_2tau1mu.insert( {file_it->first, *h_2tau1mu} );
 y_2tau2OSL.insert( {file_it->first, *h_2tau2OSL} );
 y_2tau2SSL.insert( {file_it->first, *h_2tau2SSL} );
 
 total_weight.insert({file_it->first, *GenEventWeight});
 
//cout << "y_1tau0L.size(): " << y_1tau0L.size() << endl; 
 
 
 delete h_1tau0L;
 delete h_1tau1e;
 delete h_1tau1mu;
 delete h_1tau2OSL;
 delete h_1tau2SSL;
 delete h_1tau3L;
 delete h_2tau0L;
 delete h_2tau1e;
 delete h_2tau1mu;
 delete h_2tau2OSL;
 delete h_2tau2SSL;
 delete GenEventWeight;


 inputfile->Close();
 delete inputfile;
 file_it++;

 } // end loop over files
 
 TFile *outputfile = new TFile( "Histograms_eleIDbugfix_pt10.root", "RECREATE" );
 
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
 
 map<string, TH1F>::iterator y_1tau2OSL_it = y_1tau2OSL.begin();
 while (y_1tau2OSL_it != y_1tau2OSL.end()) {
   y_1tau2OSL_it->second.Write( (y_1tau2OSL_it->first + "_1tau2OSL").c_str() );
   y_1tau2OSL_it++;
 }

 map<string, TH1F>::iterator y_1tau2SSL_it = y_1tau2SSL.begin();
 while (y_1tau2SSL_it != y_1tau2SSL.end()) {
   y_1tau2SSL_it->second.Write( (y_1tau2SSL_it->first + "_1tau2SSL").c_str() );
   y_1tau2SSL_it++;
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

 map<string, TH1F>::iterator y_2tau2OSL_it = y_2tau2OSL.begin();
 while (y_2tau2OSL_it != y_2tau2OSL.end()) {
   y_2tau2OSL_it->second.Write( (y_2tau2OSL_it->first + "_2tau2OSL").c_str() );
   y_2tau2OSL_it++;
 }

 map<string, TH1F>::iterator y_2tau2SSL_it = y_2tau2SSL.begin();
 while (y_2tau2SSL_it != y_2tau2SSL.end()) {
   y_2tau2SSL_it->second.Write( (y_2tau2SSL_it->first + "_2tau2SSL").c_str() );
   y_2tau2SSL_it++;
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
