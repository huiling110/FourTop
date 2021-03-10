#include <iostream>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TBenchmark.h>
#include <TEfficiency.h>
#include "trigEff_vs_HT.h"

//using namespace std;

void trigEff_vs_HT() {

gBenchmark->Start("running time");


 //histograms: MC wrt reference
TH1F * h_HT_nocat = new TH1F("h_HT_nocat", "h_HT_nocat; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau0L = new TH1F("h_HT_1tau0L", "h_HT_1tau0L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau1L = new TH1F("h_HT_1tau1L", "h_HT_1tau1L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau2L = new TH1F("h_HT_1tau2L", "h_HT_1tau2L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau3L = new TH1F("h_HT_1tau3L", "h_HT_1tau3L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau0L = new TH1F("h_HT_2tau0L", "h_HT_2tau0L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau1L = new TH1F("h_HT_2tau1L", "h_HT_2tau1L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau2L = new TH1F("h_HT_2tau2L", "h_HT_2tau2L; H_{T} [GeV];", 25, 0, 1500);

TH1F * h_HT_nocat_aft = new TH1F("h_HT_nocat_aft", "h_HT_nocat; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau0L_aft = new TH1F("h_HT_1tau0L_aft", "h_HT_1tau0L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau1L_aft = new TH1F("h_HT_1tau1L_aft", "h_HT_1tau1L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau2L_aft = new TH1F("h_HT_1tau2L_aft", "h_HT_1tau2L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau3L_aft = new TH1F("h_HT_1tau3L_aft", "h_HT_1tau3L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau0L_aft = new TH1F("h_HT_2tau0L_aft", "h_HT_2tau0L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau1L_aft = new TH1F("h_HT_2tau1L_aft", "h_HT_2tau1L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau2L_aft = new TH1F("h_HT_2tau2L_aft", "h_HT_2tau2L; H_{T} [GeV];", 25, 0, 1500);
//histograms: MC truth
TH1F * h_HT_nocat_truth = new TH1F("h_HT_nocat_truth", "h_HT_nocat; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau0L_truth = new TH1F("h_HT_1tau0L_truth", "h_HT_1tau0L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau1L_truth = new TH1F("h_HT_1tau1L_truth", "h_HT_1tau1L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau2L_truth = new TH1F("h_HT_1tau2L_truth", "h_HT_1tau2L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau3L_truth = new TH1F("h_HT_1tau3L_truth", "h_HT_1tau3L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau0L_truth = new TH1F("h_HT_2tau0L_truth", "h_HT_2tau0L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau1L_truth = new TH1F("h_HT_2tau1L_truth", "h_HT_2tau1L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau2L_truth = new TH1F("h_HT_2tau2L_truth", "h_HT_2tau2L; H_{T} [GeV];", 25, 0, 1500);

TH1F * h_HT_nocat_truth_aft = new TH1F("h_HT_nocat_truth_aft", "h_HT_nocat; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau0L_truth_aft = new TH1F("h_HT_1tau0L_truth_aft", "h_HT_1tau0L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau1L_truth_aft = new TH1F("h_HT_1tau1L_truth_aft", "h_HT_1tau1L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau2L_truth_aft = new TH1F("h_HT_1tau2L_truth_aft", "h_HT_1tau2L; H_{T} [GeV];", 50, 0, 1500);
TH1F * h_HT_1tau3L_truth_aft = new TH1F("h_HT_1tau3L_truth_aft", "h_HT_1tau3L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau0L_truth_aft = new TH1F("h_HT_2tau0L_truth_aft", "h_HT_2tau0L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau1L_truth_aft = new TH1F("h_HT_2tau1L_truth_aft", "h_HT_2tau1L; H_{T} [GeV];", 25, 0, 1500);
TH1F * h_HT_2tau2L_truth_aft = new TH1F("h_HT_2tau2L_truth_aft", "h_HT_2tau2L; H_{T} [GeV];", 25, 0, 1500);

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

double myjetsL_HT = 0;
evt->SetBranchAddress("jetsL_HT", &myjetsL_HT);

 // multijet triggers
 int myHLT_PFHT450_SixJet40_BTagCSV_p056 = 0;
 evt->SetBranchAddress("HLT_PFHT450_SixJet40_BTagCSV_p056", &myHLT_PFHT450_SixJet40_BTagCSV_p056);

 int myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = 0;
 evt->SetBranchAddress("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056", &myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056);

 //reference triggers
 int myHLT_AK8PFJet360_TrimMass30 = 0;
 evt->SetBranchAddress("HLT_AK8PFJet360_TrimMass30", &myHLT_AK8PFJet360_TrimMass30);

 int myHLT_PFJet450 = 0;
 evt->SetBranchAddress("HLT_PFJet450", &myHLT_PFJet450);

 int myHLT_IsoMu24 = 0;
 evt->SetBranchAddress("HLT_IsoMu24", &myHLT_IsoMu24);

 int myHLT_IsoMu27 = 0;
 evt->SetBranchAddress("HLT_IsoMu27", &myHLT_IsoMu27);

 // initializing sum of weights                                                                                                                                                                
 TH1F * GenEventWeight;
 GenEventWeight = (TH1F*)inputfile->Get("h_genweight");

Long64_t nevents = evt->GetEntries();

for ( Long64_t ievent = 0; ievent < nevents; ++ievent ) {
  //if (ievent > 100000) break;
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


 //compute HT(jet+lepton)

 float HT_jl = myjetsL_HT;

 for (unsigned int i = 0; i < myeleMVAT_pt->size(); i++) {

   HT_jl += myeleMVAT_pt->at(i);
   
 }

 for (unsigned int i = 0; i < mymuonT_pt->size(); i++) {

   HT_jl += mymuonT_pt->at(i);
   
}
 
bool isSignalTrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1);
  
//   if (HT_jl > 400) {


 if (myHLT_IsoMu24 == 1 || myHLT_IsoMu27 == 1) {

   h_HT_nocat->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());

   if(isSignalTrig) {

     h_HT_nocat_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
     
   }

 }


   if (is1tau0L) {

     if (myHLT_IsoMu24 == 1 || myHLT_IsoMu27 == 1) {

       h_HT_1tau0L->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_1tau0L_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());

     }
     
     
   }// end 1tau0L
 

   if ((is1tau1e) || (is1tau1mu)) {

     if (myHLT_IsoMu24 == 1 || myHLT_IsoMu27 == 1) {

       h_HT_1tau1L->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_1tau1L_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());

     }

 }// end 1tau1L

 if (is1tau2OSL || is1tau2SSL) {
 
   if (myHLT_IsoMu24 == 1 || myHLT_IsoMu27 == 1) {

       h_HT_1tau2L->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_1tau2L_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());

     }

 }// end 1tau2L

 if (is1tau3L) {

   if (myHLT_IsoMu24 == 1 || myHLT_IsoMu27 == 1) {

       h_HT_1tau3L->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_1tau3L_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());

     }

 }// end 1tau3L

 if (is2tau0L) {

  if (myHLT_IsoMu24 == 1 || myHLT_IsoMu27 == 1) {

       h_HT_2tau0L->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_2tau0L_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());

     }

 }// end 2tau0L

 if ((is2tau1e) || (is2tau1mu)) {

   if (myHLT_IsoMu24 == 1 || myHLT_IsoMu27 == 1) {

       h_HT_2tau1L->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_2tau1L_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());

     }

 }// end 2tau1L

 if (is2tau2OSL || is2tau2SSL) {

   if (myHLT_IsoMu24 == 1 || myHLT_IsoMu27 == 1) {

       h_HT_2tau2L->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_2tau2L_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());

     }

 }// end 2tau2L

 /////////////////////////
 ///////// MC TRUTH /////
 ///////////////////////
  

   h_HT_nocat_truth->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());

   if(isSignalTrig) {

     h_HT_nocat_truth_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
     
   }


   if (is1tau0L) {

       h_HT_1tau0L_truth->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_1tau0L_truth_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
    
     
   }// end 1tau0L
 

   if ((is1tau1e) || (is1tau1mu)) {

       h_HT_1tau1L_truth->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_1tau1L_truth_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());

 }// end 1tau1L

 if (is1tau2OSL || is1tau2SSL) {   

       h_HT_1tau2L_truth->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_1tau2L_truth_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());

 }// end 1tau2L

 if (is1tau3L) {

       h_HT_1tau3L_truth->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_1tau3L_truth_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());


 }// end 1tau3L

 if (is2tau0L) {

       h_HT_2tau0L_truth->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_2tau0L_truth_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());


 }// end 2tau0L

 if ((is2tau1e) || (is2tau1mu)) {
  
       h_HT_2tau1L_truth->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_2tau1L_truth_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());

 }// end 2tau1L

 if (is2tau2OSL || is2tau2SSL) {   

       h_HT_2tau2L_truth->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());
       
       if (isSignalTrig)  h_HT_2tau2L_truth_aft->Fill(myjetsL_HT, mygenEvtWeight*LUMI2016*xsec.at(file_it->first)/GenEventWeight->Integral());


 }// end 2tau2L


 //}//end if HT cut

 }//end loop over events

 inputfile->Close();
 delete inputfile;
 
 file_it++;

 }//end loop over files

 TFile *outputfile = new TFile( "trigEff_vs_HT_output.root", "RECREATE" );
 
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
 
 outputfile->Close();
 delete outputfile;

 gBenchmark->Show("running time");

}//end



void writeTEfficiency(TH1F* hBef, TH1F* hAft, TString name) {

  hBef->Write();
  hAft->Write();
  TEfficiency *TEff = 0;
  if(TEfficiency::CheckConsistency(*hAft, *hBef)){
            
    TEff = new TEfficiency(*hAft, *hBef);
    TEff->Write(name);
    delete TEff;
    }
  
}
