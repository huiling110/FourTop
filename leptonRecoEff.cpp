B0;115;0c#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TBenchmark.h>
#include <TEfficiency.h>
#include "leptonRecoEff.h"

void leptonRecoEff() {

gBenchmark->Start("running time");

map<string, string>::iterator file_it = file.begin();

while (file_it != file.end()) { //////////////////////// LOOP OVER FILES ///////////////////////

 cout << "Opening file " << file_it->second << "..." << endl;
 TFile *inputfile  = new TFile( file_it->second.c_str(), "READ" );

 TH1F * eleMVAT_pt_bef = new TH1F("eleMVAT_pt_bef", "eleMVAT_pt_bef", 60, 0, 60);
 TH1F * eleMVAT_pt_aft = new TH1F("eleMVAT_pt_aft", "eleMVAT_pt_aft", 60, 0, 60);
 TH1F * eleMVAT_pt_s0_bef = new TH1F("eleMVAT_pt_s0_bef", "eleMVAT_pt_s0_bef", 60, 0, 60);
 TH1F * eleMVAT_pt_s0_aft = new TH1F("eleMVAT_pt_s0_aft", "eleMVAT_pt_s0_aft", 60, 0, 60);
 TH1F * eleMVAT_pt_s1_bef = new TH1F("eleMVAT_pt_s1_bef", "eleMVAT_pt_s1_bef", 60, 0, 60);
 TH1F * eleMVAT_pt_s1_aft = new TH1F("eleMVAT_pt_s1_aft", "eleMVAT_pt_s1_aft", 60, 0, 60);
 TH1F * eleMVAT_pt_s2_bef = new TH1F("eleMVAT_pt_s2_bef", "eleMVAT_pt_s2_bef", 60, 0, 60);
 TH1F * eleMVAT_pt_s2_aft = new TH1F("eleMVAT_pt_s2_aft", "eleMVAT_pt_s2_aft", 60, 0, 60);
 TH1F * eleMVAT_pt_s3_bef = new TH1F("eleMVAT_pt_s3_bef", "eleMVAT_pt_s3_bef", 60, 0, 60);
 TH1F * eleMVAT_pt_s3_aft = new TH1F("eleMVAT_pt_s3_aft", "eleMVAT_pt_s3_aft", 60, 0, 60);

 TH1F * eleMVAL_pt_bef = new TH1F("eleMVAL_pt_bef", "eleMVAL_pt_bef", 60, 0, 60);
 TH1F * eleMVAL_pt_aft = new TH1F("eleMVAL_pt_aft", "eleMVAL_pt_aft", 60, 0, 60);
 TH1F * eleMVAL_pt_s0_bef = new TH1F("eleMVAL_pt_s0_bef", "eleMVAL_pt_s0_bef", 60, 0, 60);
 TH1F * eleMVAL_pt_s0_aft = new TH1F("eleMVAL_pt_s0_aft", "eleMVAL_pt_s0_aft", 60, 0, 60);
 TH1F * eleMVAL_pt_s1_bef = new TH1F("eleMVAL_pt_s1_bef", "eleMVAL_pt_s1_bef", 60, 0, 60);
 TH1F * eleMVAL_pt_s1_aft = new TH1F("eleMVAL_pt_s1_aft", "eleMVAL_pt_s1_aft", 60, 0, 60);
 TH1F * eleMVAL_pt_s2_bef = new TH1F("eleMVAL_pt_s2_bef", "eleMVAL_pt_s2_bef", 60, 0, 60);
 TH1F * eleMVAL_pt_s2_aft = new TH1F("eleMVAL_pt_s2_aft", "eleMVAL_pt_s2_aft", 60, 0, 60);
 TH1F * eleMVAL_pt_s3_bef = new TH1F("eleMVAL_pt_s3_bef", "eleMVAL_pt_s3_bef", 60, 0, 60);
 TH1F * eleMVAL_pt_s3_aft = new TH1F("eleMVAL_pt_s3_aft", "eleMVAL_pt_s3_aft", 60, 0, 60);


 TH1F * muonT_pt_bef = new TH1F("muonT_pt_bef", "muonT_pt_bef", 60, 0, 60);
 TH1F * muonT_pt_aft = new TH1F("muonT_pt_aft", "muonT_pt_aft", 60, 0, 60);
 TH1F * muonT_pt_s0_bef = new TH1F("muonT_pt_s0_bef", "muonT_pt_s0_bef", 60, 0, 60);
 TH1F * muonT_pt_s0_aft = new TH1F("muonT_pt_s0_aft", "muonT_pt_s0_aft", 60, 0, 60);
 TH1F * muonT_pt_s1_bef = new TH1F("muonT_pt_s1_bef", "muonT_pt_s1_bef", 60, 0, 60);
 TH1F * muonT_pt_s1_aft = new TH1F("muonT_pt_s1_aft", "muonT_pt_s1_aft", 60, 0, 60);
 TH1F * muonT_pt_s2_bef = new TH1F("muonT_pt_s2_bef", "muonT_pt_s2_bef", 60, 0, 60);
 TH1F * muonT_pt_s2_aft = new TH1F("muonT_pt_s2_aft", "muonT_pt_s2_aft", 60, 0, 60);
 TH1F * muonT_pt_s3_bef = new TH1F("muonT_pt_s3_bef", "muonT_pt_s3_bef", 60, 0, 60);
 TH1F * muonT_pt_s3_aft = new TH1F("muonT_pt_s3_aft", "muonT_pt_s3_aft", 60, 0, 60);

//addressing branches
 TTree *evt = (TTree*)inputfile->Get( "tree" );

 int mygenEles_number = 0;
 evt->SetBranchAddress( "genEles_number", &mygenEles_number );
 
 vector<double> * mygenEle_eta = 0;
 evt->SetBranchAddress( "genEle_eta", &mygenEle_eta );

 vector<double> * mygenEle_phi = 0;
 evt->SetBranchAddress( "genEle_phi", &mygenEle_phi );

 int mygenMuons_number = 0;
 evt->SetBranchAddress( "genMuons_number", &mygenMuons_number );
 
 vector<double> * mygenMuon_eta = 0;
 evt->SetBranchAddress( "genMuon_eta", &mygenMuon_eta );

 vector<double> * mygenMuon_phi = 0;
 evt->SetBranchAddress( "genMuon_phi", &mygenMuon_phi );

 // our usual electrons (i.e., stage 4)
 int myelesMVAT_number = 0;
 evt->SetBranchAddress( "elesMVAT_number", &myelesMVAT_number );
 
 vector<double> * myeleMVAT_pt = 0;
 evt->SetBranchAddress( "eleMVAT_pt", &myeleMVAT_pt );

 vector<double> * myeleMVAT_eta = 0;
 evt->SetBranchAddress( "eleMVAT_eta", &myeleMVAT_eta );

 vector<double> * myeleMVAT_phi = 0;
 evt->SetBranchAddress( "eleMVAT_phi", &myeleMVAT_phi );
 //stage 0 electrons
 int myelesMVAT_number_s0 = 0;
 evt->SetBranchAddress( "elesMVAT_number_s0", &myelesMVAT_number_s0 );
 
 vector<double> * myeleMVAT_pt_s0 = 0;
 evt->SetBranchAddress( "eleMVAT_pt_s0", &myeleMVAT_pt_s0 );

 vector<double> * myeleMVAT_eta_s0 = 0;
 evt->SetBranchAddress( "eleMVAT_eta_s0", &myeleMVAT_eta_s0 );

 vector<double> * myeleMVAT_phi_s0 = 0;
 evt->SetBranchAddress( "eleMVAT_phi_s0", &myeleMVAT_phi_s0 );
 // stage 1 electrons
 int myelesMVAT_number_s1 = 0;
 evt->SetBranchAddress( "elesMVAT_number_s1", &myelesMVAT_number_s1 );

 vector<double> * myeleMVAT_pt_s1 = 0;
 evt->SetBranchAddress( "eleMVAT_pt_s1", &myeleMVAT_pt_s1 );

 vector<double> * myeleMVAT_eta_s1 = 0;
 evt->SetBranchAddress( "eleMVAT_eta_s1", &myeleMVAT_eta_s1 );

 vector<double> * myeleMVAT_phi_s1 = 0;
 evt->SetBranchAddress( "eleMVAT_phi_s1", &myeleMVAT_phi_s1 );
 // stage 2 electrons
 int myelesMVAT_number_s2 = 0;
 evt->SetBranchAddress( "elesMVAT_number_s2", &myelesMVAT_number_s2 );

 vector<double> * myeleMVAT_pt_s2 = 0;
 evt->SetBranchAddress( "eleMVAT_pt_s2", &myeleMVAT_pt_s2 );

 vector<double> * myeleMVAT_eta_s2 = 0;
 evt->SetBranchAddress( "eleMVAT_eta_s2", &myeleMVAT_eta_s2 );

 vector<double> * myeleMVAT_phi_s2 = 0;
 evt->SetBranchAddress( "eleMVAT_phi_s2", &myeleMVAT_phi_s2 );
 //stage 3 electrons
 int myelesMVAT_number_s3 = 0;
 evt->SetBranchAddress( "elesMVAT_number_s3", &myelesMVAT_number_s3 );

 vector<double> * myeleMVAT_pt_s3 = 0;
 evt->SetBranchAddress( "eleMVAT_pt_s3", &myeleMVAT_pt_s3 );

 vector<double> * myeleMVAT_eta_s3 = 0;
 evt->SetBranchAddress( "eleMVAT_eta_s3", &myeleMVAT_eta_s3 );

 vector<double> * myeleMVAT_phi_s3 = 0;
 evt->SetBranchAddress( "eleMVAT_phi_s3", &myeleMVAT_phi_s3 );

 
// our usual electrons (i.e., stage 4)
 int myelesMVAL_number = 0;
 evt->SetBranchAddress( "elesMVAL_number", &myelesMVAL_number );
 
 vector<double> * myeleMVAL_pt = 0;
 evt->SetBranchAddress( "eleMVAL_pt", &myeleMVAL_pt );

 vector<double> * myeleMVAL_eta = 0;
 evt->SetBranchAddress( "eleMVAL_eta", &myeleMVAL_eta );

 vector<double> * myeleMVAL_phi = 0;
 evt->SetBranchAddress( "eleMVAL_phi", &myeleMVAL_phi );
 //stage 0 electrons
 int myelesMVAL_number_s0 = 0;
 evt->SetBranchAddress( "elesMVAL_number_s0", &myelesMVAL_number_s0 );
 
 vector<double> * myeleMVAL_pt_s0 = 0;
 evt->SetBranchAddress( "eleMVAL_pt_s0", &myeleMVAL_pt_s0 );

 vector<double> * myeleMVAL_eta_s0 = 0;
 evt->SetBranchAddress( "eleMVAL_eta_s0", &myeleMVAL_eta_s0 );

 vector<double> * myeleMVAL_phi_s0 = 0;
 evt->SetBranchAddress( "eleMVAL_phi_s0", &myeleMVAL_phi_s0 );
 // stage 1 electrons
 int myelesMVAL_number_s1 = 0;
 evt->SetBranchAddress( "elesMVAL_number_s1", &myelesMVAL_number_s1 );

 vector<double> * myeleMVAL_pt_s1 = 0;
 evt->SetBranchAddress( "eleMVAL_pt_s1", &myeleMVAL_pt_s1 );

 vector<double> * myeleMVAL_eta_s1 = 0;
 evt->SetBranchAddress( "eleMVAL_eta_s1", &myeleMVAL_eta_s1 );

 vector<double> * myeleMVAL_phi_s1 = 0;
 evt->SetBranchAddress( "eleMVAL_phi_s1", &myeleMVAL_phi_s1 );
 // stage 2 electrons
 int myelesMVAL_number_s2 = 0;
 evt->SetBranchAddress( "elesMVAL_number_s2", &myelesMVAL_number_s2 );

 vector<double> * myeleMVAL_pt_s2 = 0;
 evt->SetBranchAddress( "eleMVAL_pt_s2", &myeleMVAL_pt_s2 );

 vector<double> * myeleMVAL_eta_s2 = 0;
 evt->SetBranchAddress( "eleMVAL_eta_s2", &myeleMVAL_eta_s2 );

 vector<double> * myeleMVAL_phi_s2 = 0;
 evt->SetBranchAddress( "eleMVAL_phi_s2", &myeleMVAL_phi_s2 );
 //stage 3 electrons
 int myelesMVAL_number_s3 = 0;
 evt->SetBranchAddress( "elesMVAL_number_s3", &myelesMVAL_number_s3 );

 vector<double> * myeleMVAL_pt_s3 = 0;
 evt->SetBranchAddress( "eleMVAL_pt_s3", &myeleMVAL_pt_s3 );

 vector<double> * myeleMVAL_eta_s3 = 0;
 evt->SetBranchAddress( "eleMVAL_eta_s3", &myeleMVAL_eta_s3 );

 vector<double> * myeleMVAL_phi_s3 = 0;
 evt->SetBranchAddress( "eleMVAL_phi_s3", &myeleMVAL_phi_s3 );

// our usual muons (i.e., stage 4)
 int mymuonsT_number = 0;
 evt->SetBranchAddress( "muonsT_number", &mymuonsT_number );
 
 vector<double> * mymuonT_pt = 0;
 evt->SetBranchAddress( "muonT_pt", &mymuonT_pt );

 vector<double> * mymuonT_eta = 0;
 evt->SetBranchAddress( "muonT_eta", &mymuonT_eta );

 vector<double> * mymuonT_phi = 0;
 evt->SetBranchAddress( "muonT_phi", &mymuonT_phi );
 //stage 0 muons
 int mymuonsT_number_s0 = 0;
 evt->SetBranchAddress( "muonsT_number_s0", &mymuonsT_number_s0 );
 
 vector<double> * mymuonT_pt_s0 = 0;
 evt->SetBranchAddress( "muonT_pt_s0", &mymuonT_pt_s0 );

 vector<double> * mymuonT_eta_s0 = 0;
 evt->SetBranchAddress( "muonT_eta_s0", &mymuonT_eta_s0 );

 vector<double> * mymuonT_phi_s0 = 0;
 evt->SetBranchAddress( "muonT_phi_s0", &mymuonT_phi_s0 );
 // stage 1 muons
 int mymuonsT_number_s1 = 0;
 evt->SetBranchAddress( "muonsT_number_s1", &mymuonsT_number_s1 );

 vector<double> * mymuonT_pt_s1 = 0;
 evt->SetBranchAddress( "muonT_pt_s1", &mymuonT_pt_s1 );

 vector<double> * mymuonT_eta_s1 = 0;
 evt->SetBranchAddress( "muonT_eta_s1", &mymuonT_eta_s1 );

 vector<double> * mymuonT_phi_s1 = 0;
 evt->SetBranchAddress( "muonT_phi_s1", &mymuonT_phi_s1 );
 // stage 2 muons
 int mymuonsT_number_s2 = 0;
 evt->SetBranchAddress( "muonsT_number_s2", &mymuonsT_number_s2 );

 vector<double> * mymuonT_pt_s2 = 0;
 evt->SetBranchAddress( "muonT_pt_s2", &mymuonT_pt_s2 );

 vector<double> * mymuonT_eta_s2 = 0;
 evt->SetBranchAddress( "muonT_eta_s2", &mymuonT_eta_s2 );

 vector<double> * mymuonT_phi_s2 = 0;
 evt->SetBranchAddress( "muonT_phi_s2", &mymuonT_phi_s2 );
 //stage 3 muons
 int mymuonsT_number_s3 = 0;
 evt->SetBranchAddress( "muonsT_number_s3", &mymuonsT_number_s3 );

 vector<double> * mymuonT_pt_s3 = 0;
 evt->SetBranchAddress( "muonT_pt_s3", &mymuonT_pt_s3 );

 vector<double> * mymuonT_eta_s3 = 0;
 evt->SetBranchAddress( "muonT_eta_s3", &mymuonT_eta_s3 );

 vector<double> * mymuonT_phi_s3 = 0;
 evt->SetBranchAddress( "muonT_phi_s3", &mymuonT_phi_s3 );



 Long64_t nevents = evt->GetEntries();

for ( Long64_t ievent = 0; ievent < nevents; ++ievent ){
  if (ievent > 300000) break;
  if ( !(ievent % 100000 ) ) cout << "ievent  =  " << ievent << endl;
  //get i-th entry in tree
  evt->GetEntry( ievent );

  recoEff(0.4, mygenEles_number, myelesMVAT_number, mygenEle_eta, mygenEle_phi, myeleMVAT_eta,myeleMVAT_phi, eleMVAT_pt_bef, eleMVAT_pt_aft, myeleMVAT_pt);
  recoEff(0.4, mygenEles_number, myelesMVAT_number_s0, mygenEle_eta, mygenEle_phi, myeleMVAT_eta_s0, myeleMVAT_phi_s0, eleMVAT_pt_s0_bef, eleMVAT_pt_s0_aft, myeleMVAT_pt_s0);
  recoEff(0.4, mygenEles_number, myelesMVAT_number_s1, mygenEle_eta, mygenEle_phi, myeleMVAT_eta_s1, myeleMVAT_phi_s1, eleMVAT_pt_s1_bef, eleMVAT_pt_s1_aft, myeleMVAT_pt_s1);
  recoEff(0.4, mygenEles_number, myelesMVAT_number_s2, mygenEle_eta, mygenEle_phi, myeleMVAT_eta_s2, myeleMVAT_phi_s2, eleMVAT_pt_s2_bef, eleMVAT_pt_s2_aft, myeleMVAT_pt_s2);
  recoEff(0.4, mygenEles_number, myelesMVAT_number_s3, mygenEle_eta, mygenEle_phi, myeleMVAT_eta_s3, myeleMVAT_phi_s3, eleMVAT_pt_s3_bef, eleMVAT_pt_s3_aft, myeleMVAT_pt_s3);

  recoEff(0.4, mygenEles_number, myelesMVAL_number, mygenEle_eta, mygenEle_phi, myeleMVAL_eta,myeleMVAL_phi, eleMVAL_pt_bef, eleMVAL_pt_aft, myeleMVAL_pt);
  recoEff(0.4, mygenEles_number, myelesMVAL_number_s0, mygenEle_eta, mygenEle_phi, myeleMVAL_eta_s0, myeleMVAL_phi_s0, eleMVAL_pt_s0_bef, eleMVAL_pt_s0_aft, myeleMVAL_pt_s0);
  recoEff(0.4, mygenEles_number, myelesMVAL_number_s1, mygenEle_eta, mygenEle_phi, myeleMVAL_eta_s1, myeleMVAL_phi_s1, eleMVAL_pt_s1_bef, eleMVAL_pt_s1_aft, myeleMVAL_pt_s1);
  recoEff(0.4, mygenEles_number, myelesMVAL_number_s2, mygenEle_eta, mygenEle_phi, myeleMVAL_eta_s2, myeleMVAL_phi_s2, eleMVAL_pt_s2_bef, eleMVAL_pt_s2_aft, myeleMVAL_pt_s2);
  recoEff(0.4, mygenEles_number, myelesMVAL_number_s3, mygenEle_eta, mygenEle_phi, myeleMVAL_eta_s3, myeleMVAL_phi_s3, eleMVAL_pt_s3_bef, eleMVAL_pt_s3_aft, myeleMVAL_pt_s3);

  recoEff(0.4, mygenMuons_number, mymuonsT_number, mygenMuon_eta, mygenMuon_phi, mymuonT_eta,mymuonT_phi, muonT_pt_bef, muonT_pt_aft, mymuonT_pt);
  recoEff(0.4, mygenMuons_number, mymuonsT_number_s0, mygenMuon_eta, mygenMuon_phi, mymuonT_eta_s0, mymuonT_phi_s0, muonT_pt_s0_bef, muonT_pt_s0_aft, mymuonT_pt_s0);
  recoEff(0.4, mygenMuons_number, mymuonsT_number_s1, mygenMuon_eta, mygenMuon_phi, mymuonT_eta_s1, mymuonT_phi_s1, muonT_pt_s1_bef, muonT_pt_s1_aft, mymuonT_pt_s1);
  recoEff(0.4, mygenMuons_number, mymuonsT_number_s2, mygenMuon_eta, mygenMuon_phi, mymuonT_eta_s2, mymuonT_phi_s2, muonT_pt_s2_bef, muonT_pt_s2_aft, mymuonT_pt_s2);
  recoEff(0.4, mygenMuons_number, mymuonsT_number_s3, mygenMuon_eta, mygenMuon_phi, mymuonT_eta_s3, mymuonT_phi_s3, muonT_pt_s3_bef, muonT_pt_s3_aft, mymuonT_pt_s3);

 }// end loop over events

 TFile *outputfile = new TFile( ("leptonRecoEff_output_" + file_it->first + ".root").c_str(), "RECREATE" );

 writeTEfficiency(eleMVAT_pt_bef, eleMVAT_pt_aft, "eleMVAT_recoEff");
 writeTEfficiency(eleMVAT_pt_s0_bef, eleMVAT_pt_s0_aft, "eleMVAT_s0_recoEff");
 writeTEfficiency(eleMVAT_pt_s1_bef, eleMVAT_pt_s1_aft, "eleMVAT_s1_recoEff");
 writeTEfficiency(eleMVAT_pt_s2_bef, eleMVAT_pt_s2_aft, "eleMVAT_s2_recoEff");
 writeTEfficiency(eleMVAT_pt_s3_bef, eleMVAT_pt_s3_aft, "eleMVAT_s3_recoEff");

 writeTEfficiency(eleMVAL_pt_bef, eleMVAL_pt_aft, "eleMVAL_recoEff");
 writeTEfficiency(eleMVAL_pt_s0_bef, eleMVAL_pt_s0_aft, "eleMVAL_s0_recoEff");
 writeTEfficiency(eleMVAL_pt_s1_bef, eleMVAL_pt_s1_aft, "eleMVAL_s1_recoEff");
 writeTEfficiency(eleMVAL_pt_s2_bef, eleMVAL_pt_s2_aft, "eleMVAL_s2_recoEff");
 writeTEfficiency(eleMVAL_pt_s3_bef, eleMVAL_pt_s3_aft, "eleMVAL_s3_recoEff");

 writeTEfficiency(muonT_pt_bef, muonT_pt_aft, "muonT_recoEff");
 writeTEfficiency(muonT_pt_s0_bef, muonT_pt_s0_aft, "muonT_s0_recoEff");
 writeTEfficiency(muonT_pt_s1_bef, muonT_pt_s1_aft, "muonT_s1_recoEff");
 writeTEfficiency(muonT_pt_s2_bef, muonT_pt_s2_aft, "muonT_s2_recoEff");
 writeTEfficiency(muonT_pt_s3_bef, muonT_pt_s3_aft, "muonT_s3_recoEff");

 outputfile->Close();
 delete outputfile;

 inputfile->Close();
 delete inputfile;
 file_it++;

}


}







void recoEff(double dRmatch, int nGen, int nReco, vector<double> * genEta, vector<double> *genPhi, vector<double> *recoEta, vector<double> *recoPhi, TH1F *hBef, TH1F *hAft, vector<double>* recoVar) {

  double dRmin = 10.0;
  int whichlepton = -1;

  for (int i = 0; i < nGen; i++) {

    for (int j = 0; j < nReco; j++) {
      
      hBef->Fill(recoVar->at(j));
      Float_t dEta = fabs( genEta->at(i) - recoEta->at(j) );
      Float_t dPhi = fabs( genPhi->at(i) -recoPhi->at(j) );
      if(dPhi > 3.14159265358979323846) dPhi  = 2*3.14159265358979323846 - dPhi;
      Float_t dR = sqrt( pow(dEta, 2) + pow(dPhi, 2) );
                        
      if ( dR < dRmin ) {
                            
	dRmin = dR;
	whichlepton = j;
      }

    }
   
    if (dRmin < dRmatch) hAft->Fill(recoVar->at(whichlepton));
 
  }

}

void writeTEfficiency(TH1F* hBef, TH1F* hAft, TString name) {

  TEfficiency *TEff = 0;
  if(TEfficiency::CheckConsistency(*hAft, *hBef)){
            
    TEff = new TEfficiency(*hAft, *hBef);
    hBef->Write();
    hAft->Write();
    TEff->Write(name);
    delete TEff;
  }

}
