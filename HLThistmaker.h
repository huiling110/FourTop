#include "TBranch.h"
#include "TTree.h"
#include "TFile.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TMath.h"
#include <iostream>

void branch();
void branchGetEntry(Long64_t tentry=0);
void HistoFill(int Nfiles=-1);
void writeFile();
void initialize();
float DeltaR(float eta1, float eta2, float phi1, float phi2);

TTree *Tree;

vector <double> * Gen_pt_; TBranch *b_Gen_pt;
vector <double> * Gen_eta_; TBranch *b_Gen_eta;
vector <double> * Gen_phi_; TBranch *b_Gen_phi;
vector <double> * Gen_pdg_id_; TBranch *b_Gen_pdg_id;
vector <double> * Gen_motherpdg_id_; TBranch *b_Gen_motherpdg_id;

Int_t HLT_PFHT500_PFMET100_PFMHT100_IDTight_;        TBranch * b_HLT_PFHT500_PFMET100_PFMHT100_IDTight;  
Int_t HLT_PFHT700_PFMET85_PFMHT85_IDTight_;          TBranch * b_HLT_PFHT700_PFMET85_PFMHT85_IDTight;
Int_t HLT_PFHT800_PFMET75_PFMHT75_IDTight_;          TBranch * b_HLT_PFHT800_PFMET75_PFMHT75_IDTight;
Int_t HLT_PFMET120_PFMHT120_IDTight_;                TBranch * b_HLT_PFMET120_PFMHT120_IDTight;
Int_t HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_;        TBranch * b_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight;
Int_t HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight_;     TBranch * b_HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight;
Int_t HLT_CaloJet500_NoJetID_;                       TBranch * b_HLT_CaloJet500_NoJetID;
Int_t HLT_AK8PFJet500_;                              TBranch * b_HLT_AK8PFJet500;
Int_t HLT_PFJet500_;                                 TBranch * b_HLT_PFJet500;
Int_t HLT_PFHT1050_;                                 TBranch * b_HLT_PFHT1050;

Double_t Met_type1PF_pt_;                            TBranch * b_Met_type1PF_pt;

Int_t HLT_PFHT450_SixJet40_BTagCSV_p056_;            TBranch * b_HLT_PFHT450_SixJet40_BTagCSV_p056;
Int_t HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_;      TBranch * b_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056;

Int_t HLT_PFHT500_PFMET100_PFMHT100_IDTight = -9999;
Int_t HLT_PFHT700_PFMET85_PFMHT85_IDTight = -9999;
Int_t HLT_PFHT800_PFMET75_PFMHT75_IDTight = -9999;        
Int_t HLT_PFMET120_PFMHT120_IDTight = -9999;               
Int_t HLT_PFMETNoMu120_PFMHTNoMu120_IDTight = -9999;    
Int_t HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight = -9999;
Int_t HLT_CaloJet500_NoJetID = -9999;
Int_t HLT_AK8PFJet500 = -9999;
Int_t HLT_PFJet500 = -9999;
Int_t HLT_PFHT1050 = -9999;

Int_t HLT_PFHT450_SixJet40_BTagCSV_p056 = -999;

Int_t Trigger  = -9999;

float Gen_quarkfromt_Highpt = -99.;
float Gen_quarkfromt_Highpt_eta = -99.;
float Gen_quarkfromt_Highpt_phi = -99.;

float Gen_Highpt = -99.;
float Gen_Highpt_DEN = -99.;
float Gen_Highpt_eta = -99.;
float Gen_Highpt_phi = -99.;
float Gen_Highpt_NUM_PassTrigger = -99.;

TH1F* h_Gen_Highpt_DEN_0700 = new TH1F("h_Gen_Highpt_DEN_0700","h_Gen_Highpt_DEN_0700",100,0,1000);
TH1F* h_Gen_Highpt_DEN_1000 = new TH1F("h_Gen_Highpt_DEN_1000","h_Gen_Highpt_DEN_1000",100,0,1000);
TH1F* h_Gen_Highpt_DEN_1200 = new TH1F("h_Gen_Highpt_DEN_1200","h_Gen_Highpt_DEN_1200",100,0,1000);

TH1F* h_Gen_Highpt_NUM_PassTrigger_0700 = new TH1F("h_Gen_Highpt_NUM_PassTrigger_0700","h_Gen_Highpt_NUM_PassTrigger_0700",100,0,1000);
TH1F* h_Gen_Highpt_NUM_PassTrigger_1000 = new TH1F("h_Gen_Highpt_NUM_PassTrigger_1000","h_Gen_Highpt_NUM_PassTrigger_1000",100,0,1000);
TH1F* h_Gen_Highpt_NUM_PassTrigger_1200 = new TH1F("h_Gen_Highpt_NUM_PassTrigger_1200","h_Gen_Highpt_NUM_PassTrigger_1200",100,0,1000);

float Gen_Lowpt  = 9999999.;
float Gen_Lowpt_DEN  = 9999999.;
float Gen_Lowpt_eta  = 9999999.;
float Gen_Lowpt_phi  = 9999999.;
float Gen_Lowpt_NUM_PassTrigger = 9999999.;

float Gen_quarkfromt_Lowpt  = 9999999.;
float Gen_quarkfromt_Lowpt_eta  = 9999999.;
float Gen_quarkfromt_Lowpt_phi  = 9999999.;

TH1F* h_Gen_Lowpt_DEN_0700 = new TH1F("h_Gen_Lowpt_DEN_0700","h_Gen_Lowpt_DEN_0700",100,0,1000);
TH1F* h_Gen_Lowpt_DEN_1000 = new TH1F("h_Gen_Lowpt_DEN_1000","h_Gen_Lowpt_DEN_1000",100,0,1000);
TH1F* h_Gen_Lowpt_DEN_1200 = new TH1F("h_Gen_Lowpt_DEN_1200","h_Gen_Lowpt_DEN_1200",100,0,1000);

TH1F* h_Gen_Lowpt_NUM_PassTrigger_0700 = new TH1F("h_Gen_Lowpt_NUM_PassTrigger_0700","h_Gen_Lowpt_NUM_PassTrigger_0700",100,0,1000);
TH1F* h_Gen_Lowpt_NUM_PassTrigger_1000 = new TH1F("h_Gen_Lowpt_NUM_PassTrigger_1000","h_Gen_Lowpt_NUM_PassTrigger_1000",100,0,1000);
TH1F* h_Gen_Lowpt_NUM_PassTrigger_1200 = new TH1F("h_Gen_Lowpt_NUM_PassTrigger_1200","h_Gen_Lowpt_NUM_PassTrigger_1200",100,0,1000);

float Gen_DeltaR_DEN = -99.;
float Gen_DeltaR_NUM_PassTrigger = -99.;

TH1F* h_Gen_DeltaR_DEN_0700 = new TH1F("h_Gen_DeltaR_DEN_0700","h_Gen_DeltaR_DEN_0700",100,0,5);
TH1F* h_Gen_DeltaR_DEN_1000 = new TH1F("h_Gen_DeltaR_DEN_1000","h_Gen_DeltaR_DEN_1000",100,0,5);
TH1F* h_Gen_DeltaR_DEN_1200 = new TH1F("h_Gen_DeltaR_DEN_1200","h_Gen_DeltaR_DEN_1200",100,0,5);

TH1F* h_Gen_DeltaR_NUM_PassTrigger_0700 = new TH1F("h_Gen_DeltaR_NUM_PassTrigger_0700","h_Gen_DeltaR_NUM_PassTrigger_0700",100,0,5);
TH1F* h_Gen_DeltaR_NUM_PassTrigger_1000 = new TH1F("h_Gen_DeltaR_NUM_PassTrigger_1000","h_Gen_DeltaR_NUM_PassTrigger_1000",100,0,5);
TH1F* h_Gen_DeltaR_NUM_PassTrigger_1200 = new TH1F("h_Gen_DeltaR_NUM_PassTrigger_1200","h_Gen_DeltaR_NUM_PassTrigger_1200",100,0,5);

float MET_pt_DEN = -99;
float MET_pt_NUM_PassTrigger = -99;

TH1F* h_MET_pt_DEN_0700 = new TH1F("h_MET_pt_DEN_0700","h_MET_pt_DEN_0700",100,0,1000);
TH1F* h_MET_pt_DEN_1000 = new TH1F("h_MET_pt_DEN_1000","h_MET_pt_DEN_1000",100,0,1000);
TH1F* h_MET_pt_DEN_1200 = new TH1F("h_MET_pt_DEN_1200","h_MET_pt_DEN_1200",100,0,1000);

TH1F* h_MET_pt_NUM_PassTrigger_0700 = new TH1F("h_MET_pt_NUM_PassTrigger_0700","h_MET_pt_NUM_PassTrigger_0700",100,0,1000);
TH1F* h_MET_pt_NUM_PassTrigger_1000 = new TH1F("h_MET_pt_NUM_PassTrigger_1000","h_MET_pt_NUM_PassTrigger_1000",100,0,1000);
TH1F* h_MET_pt_NUM_PassTrigger_1200 = new TH1F("h_MET_pt_NUM_PassTrigger_1200","h_MET_pt_NUM_PassTrigger_1200",100,0,1000);
