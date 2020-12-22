#include "plottingTrigger_dineutrino.h" 

void plottingTrigger_dineutrino(){
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetOptStat("rme");
  gStyle->SetPalette(1,0);
  gStyle->SetTitleX(0.50);
  gStyle->SetTitleY(0.96);
  gStyle->SetPaintTextFormat(".2f");

  using namespace std;
  char openTree[500];  char openTree1[500]; sprintf(openTree, "BOOM");   sprintf(openTree1, "TNT/BOOM");                                                                     //1.定义要打开的tree文件 
  TFile *file1 = TFile::Open("/eos/user/t/tayu/trigger_2017/Tprime_0700.root");    //2.定义要打开的.root文件
  TFile *file2 = TFile::Open("/eos/user/t/tayu/trigger_2017/Tprime_1000.root");    //2.定义要打开的.root文件
  TFile *file3 = TFile::Open("/eos/user/t/tayu/trigger_2017/Tprime_1200.root");    //2.定义要打开的.root文件
  //TFile *file2 = TFile::Open("root://eosuser.cern.ch:1094//eos/user/a/aspiezia/TPrime/2017/TRIGGER/Tprime_1000.root");
  //TFile *file3 = TFile::Open("root://eosuser.cern.ch:1094//eos/user/a/aspiezia/TPrime/2017/TRIGGER/Tprime_1200.root");

  int dineutrino=1;
  int tJet=1;

  for(int Nfiles=0; Nfiles<3; Nfiles++){
    if(Nfiles==0) Tree = (TTree*)file1->Get(openTree1);                                                                             //3.打开.root文件中的tree 
    if(Nfiles==1) Tree = (TTree*)file2->Get(openTree1); 
    if(Nfiles==2) Tree = (TTree*)file3->Get(openTree1);  
    cout<<"this step is ok"<<endl;                                                                                                                     //4.为tree中的branch(变量)设置地址
    branch(); 
    Int_t nentries = (Int_t)Tree->GetEntries();                                                                                    //5.得到tree中总的目录(事例)个数
    //if (Nfiles==0) nentries = 367040;
    for (Int_t i=0; i<nentries; i++) {
    //for (Int_t i=0; i<367040; i++) {
      Long64_t tentry = Tree->LoadTree(i);                                                                                         //6.进入第t个目录
      initialize();                                      //把变量值初始化
      branchGetEntry(tentry);                                                                                                      //7.得到当前(第t个)目录entry下的branch
      bool found_dineutrino = false;
      bool found_tJet = false;
      for (UInt_t j = 0; j < Gen_pt_->size(); ++j) { 
    if(dineutrino==1) {    
	  if((abs(Gen_motherpdg_id_->at(j))==23)&&(abs(Gen_pdg_id_->at(j))==12||abs(Gen_pdg_id_->at(j))==14||abs(Gen_pdg_id_->at(j))==16)){ 
	    if(Gen_pt_->at(j)>Gen_Highpt){
	      Gen_Highpt     = Gen_pt_->at(j); 
	      Gen_Highpt_eta = Gen_eta_->at(j); 
	      Gen_Highpt_phi = Gen_phi_->at(j); 
	    }
	    if(Gen_pt_->at(j)<Gen_Lowpt){
	      Gen_Lowpt     = Gen_pt_->at(j); 
	      Gen_Lowpt_eta = Gen_eta_->at(j); 
	      Gen_Lowpt_phi = Gen_phi_->at(j); 
	    }
	  }
	  if(Gen_Highpt>0 && Gen_Lowpt<999999) found_dineutrino = true;
	}

	if(tJet==1) { 
	  if(abs(Gen_motherpdg_id_->at(j))==24 &&(abs(Gen_pdg_id_->at(j))==1||abs(Gen_pdg_id_->at(j))==2||abs(Gen_pdg_id_->at(j))==3||abs(Gen_pdg_id_->at(j))==4||abs(Gen_pdg_id_->at(j))==5||abs(Gen_pdg_id_->at(j))==6)){ 
	  if(Gen_pt_->at(j)>Gen_quarkfromt_Highpt){
            Gen_quarkfromt_Highpt = Gen_pt_->at(j);
	    Gen_quarkfromt_Highpt_eta = Gen_eta_->at(j);
	    Gen_quarkfromt_Highpt_phi = Gen_phi_->at(j);
        }
          if(Gen_pt_->at(j)<Gen_quarkfromt_Lowpt){
            Gen_quarkfromt_Lowpt = Gen_pt_->at(j);
	    Gen_quarkfromt_Lowpt_eta = Gen_eta_->at(j);
	    Gen_quarkfromt_Lowpt_phi = Gen_phi_->at(j);
        }
	  }
	  if(Gen_quarkfromt_Highpt>0 && Gen_quarkfromt_Lowpt<999999) found_tJet=true;
	}
	  }

    if(found_tJet && found_dineutrino){
      MET_pt_DEN = Met_type1PF_pt_;
      //Gen_Highpt_DEN = Gen_Highpt;
      //Gen_Lowpt_DEN  = Gen_Lowpt;
      //Gen_DeltaR_DEN = DeltaR(Gen_Highpt_eta,Gen_Lowpt_eta,Gen_Highpt_phi,Gen_Lowpt_phi);

      HLT_PFHT500_PFMET100_PFMHT100_IDTight = HLT_PFHT500_PFMET100_PFMHT100_IDTight_;
      HLT_PFHT700_PFMET85_PFMHT85_IDTight   = HLT_PFHT700_PFMET85_PFMHT85_IDTight_;
      HLT_PFHT800_PFMET75_PFMHT75_IDTight   = HLT_PFHT800_PFMET75_PFMHT75_IDTight_;        
      HLT_PFMET120_PFMHT120_IDTight         = HLT_PFMET120_PFMHT120_IDTight_;               
      HLT_PFMETNoMu120_PFMHTNoMu120_IDTight = HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_;    
      HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight = HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight_ ;
      HLT_CaloJet500_NoJetID                = HLT_CaloJet500_NoJetID_;
      HLT_AK8PFJet500                       = HLT_AK8PFJet500_;
      HLT_PFJet500                          = HLT_PFJet500_;
      HLT_PFHT1050                          = HLT_PFHT1050_;

      //if(HLT_PFHT500_PFMET100_PFMHT100_IDTight==1)    Trigger = 1; else Trigger = 0;
      //if(HLT_PFHT700_PFMET85_PFMHT85_IDTight==1)      Trigger = 1; else Trigger = 0;
      //if(HLT_PFHT800_PFMET75_PFMHT75_IDTight==1)      Trigger = 1; else Trigger = 0;    
      //if(HLT_PFMET120_PFMHT120_IDTight==1)            Trigger = 1; else Trigger = 0;
      //if(HLT_PFMETNoMu120_PFMHTNoMu120_IDTight==1)    Trigger = 1; else Trigger = 0;    
      //if(HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight==1)            Trigger = 1; else Trigger = 0;
      if(HLT_PFMET120_PFMHT120_IDTight==1||HLT_PFMETNoMu120_PFMHTNoMu120_IDTight==1)            Trigger = 1; else Trigger = 0;
      //if(HLT_CaloJet500_NoJetID==1)                   Trigger = 1; else Trigger = 0;      
      //if(HLT_AK8PFJet500==1)                          Trigger = 1; else Trigger = 0;
      //if(HLT_PFJet500==1)                             Trigger = 1; else Trigger = 0;    
      //if(HLT_PFHT1050==1)                             Trigger = 1; else Trigger = 0;

      if(Trigger){
	//Gen_Highpt_NUM_PassTrigger  = Gen_Highpt_DEN;
	//Gen_Lowpt_NUM_PassTrigger   = Gen_Lowpt_DEN;
	//Gen_DeltaR_NUM_PassTrigger  = Gen_DeltaR_DEN;
        MET_pt_NUM_PassTrigger = MET_pt_DEN;
	 }

	HistoFill(Nfiles);

	}
	}
   }

   writeFile();
}

void branch(){
  Tree->SetBranchAddress("Gen_pt",                  &Gen_pt_,                  &b_Gen_pt);
  Tree->SetBranchAddress("Gen_eta",                 &Gen_eta_,                 &b_Gen_eta);
  Tree->SetBranchAddress("Gen_phi",                 &Gen_phi_,                 &b_Gen_phi);
  Tree->SetBranchAddress("Gen_pdg_id",              &Gen_pdg_id_,              &b_Gen_pdg_id);
  Tree->SetBranchAddress("Gen_motherpdg_id",        &Gen_motherpdg_id_,        &b_Gen_motherpdg_id);
  Tree->SetBranchAddress("Met_type1PF_pt",          &Met_type1PF_pt_,          &b_Met_type1PF_pt);
  
  Tree->SetBranchAddress("HLT_PFHT500_PFMET100_PFMHT100_IDTight", &HLT_PFHT500_PFMET100_PFMHT100_IDTight_, &b_HLT_PFHT500_PFMET100_PFMHT100_IDTight);
  Tree->SetBranchAddress("HLT_PFHT700_PFMET85_PFMHT85_IDTight", &HLT_PFHT700_PFMET85_PFMHT85_IDTight_, &b_HLT_PFHT700_PFMET85_PFMHT85_IDTight);
  Tree->SetBranchAddress("HLT_PFHT800_PFMET75_PFMHT75_IDTight", &HLT_PFHT800_PFMET75_PFMHT75_IDTight_, &b_HLT_PFHT800_PFMET75_PFMHT75_IDTight);
  Tree->SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight", &HLT_PFMET120_PFMHT120_IDTight_, &b_HLT_PFMET120_PFMHT120_IDTight);
  Tree->SetBranchAddress("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight", &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_, &b_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight);
  Tree->SetBranchAddress("HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight", &HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight_,  &b_HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight);
  Tree->SetBranchAddress("HLT_CaloJet500_NoJetID", &HLT_CaloJet500_NoJetID_, &b_HLT_CaloJet500_NoJetID);
  Tree->SetBranchAddress("HLT_AK8PFJet500", &HLT_AK8PFJet500_,   &b_HLT_AK8PFJet500);
  Tree->SetBranchAddress("HLT_PFJet500", &HLT_PFJet500_,         &b_HLT_PFJet500);
  Tree->SetBranchAddress("HLT_PFHT1050", &HLT_PFHT1050_,         &b_HLT_PFHT1050);
}

void initialize(){
  HLT_PFHT500_PFMET100_PFMHT100_IDTight = -9999;
  HLT_PFHT700_PFMET85_PFMHT85_IDTight = -9999;
  HLT_PFHT800_PFMET75_PFMHT75_IDTight = -9999;        
  HLT_PFMET120_PFMHT120_IDTight = -9999;               
  HLT_PFMETNoMu120_PFMHTNoMu120_IDTight = -9999;    
  HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight = -9999;
  HLT_CaloJet500_NoJetID = -9999;
  HLT_AK8PFJet500 = -9999;
  HLT_PFJet500 = -9999;
  HLT_PFHT1050 = -9999;

  Trigger  = -9999;

  Gen_Highpt = -99.;
  Gen_Highpt_DEN = -99.;
  Gen_Highpt_eta = -99.;
  Gen_Highpt_phi = -99.;
  Gen_Highpt_NUM_PassTrigger = -99.;

  Gen_quarkfromt_Highpt = -99.;
  Gen_quarkfromt_Highpt_eta = -99.;
  Gen_quarkfromt_Highpt_phi = -99.;

  Gen_Lowpt  = 9999999.;
  Gen_Lowpt_DEN  = 9999999.;
  Gen_Lowpt_eta  = 9999999.;
  Gen_Lowpt_phi  = 9999999.;
  Gen_Lowpt_NUM_PassTrigger = 9999999.;

  Gen_quarkfromt_Lowpt  = 9999999.;
  Gen_quarkfromt_Lowpt_eta  = 9999999.; 
  Gen_quarkfromt_Lowpt_phi  = 9999999.;

  Gen_DeltaR_DEN = -99.;
  Gen_DeltaR_NUM_PassTrigger = -99.;

  MET_pt_DEN = -99;
  MET_pt_NUM_PassTrigger = -99;

}

void branchGetEntry(Long64_t tentry=0){
  b_Gen_pt->GetEntry(tentry);
  b_Gen_eta->GetEntry(tentry);
  b_Gen_phi->GetEntry(tentry);
  b_Gen_pdg_id->GetEntry(tentry);
  b_Gen_motherpdg_id->GetEntry(tentry);
  b_Met_type1PF_pt->GetEntry(tentry);

  b_HLT_PFHT500_PFMET100_PFMHT100_IDTight->GetEntry(tentry);
  b_HLT_PFHT700_PFMET85_PFMHT85_IDTight->GetEntry(tentry);
  b_HLT_PFHT800_PFMET75_PFMHT75_IDTight->GetEntry(tentry);
  b_HLT_PFMET120_PFMHT120_IDTight->GetEntry(tentry);
  b_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight->GetEntry(tentry);
  b_HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight->GetEntry(tentry);
  b_HLT_CaloJet500_NoJetID->GetEntry(tentry);
  b_HLT_AK8PFJet500->GetEntry(tentry);
  b_HLT_PFJet500->GetEntry(tentry);
  b_HLT_PFHT1050->GetEntry(tentry);
}

void HistoFill(int Nfiles){
  if(Nfiles==0){
     /*h_Gen_Highpt_DEN_0700->Fill(Gen_Highpt_DEN);
     h_Gen_Highpt_NUM_PassTrigger_0700->Fill(Gen_Highpt_NUM_PassTrigger);

     h_Gen_Lowpt_DEN_0700->Fill(Gen_Lowpt_DEN);
     h_Gen_Lowpt_NUM_PassTrigger_0700->Fill(Gen_Lowpt_NUM_PassTrigger);

     h_Gen_DeltaR_DEN_0700->Fill(Gen_DeltaR_DEN);
     h_Gen_DeltaR_NUM_PassTrigger_0700->Fill(Gen_DeltaR_NUM_PassTrigger);*/

     h_MET_pt_DEN_0700->Fill(MET_pt_DEN);
     h_MET_pt_NUM_PassTrigger_0700->Fill(MET_pt_NUM_PassTrigger);
    
  } 
  if(Nfiles==1){
     /*h_Gen_Highpt_DEN_1000->Fill(Gen_Highpt_DEN);
     h_Gen_Highpt_NUM_PassTrigger_1000->Fill(Gen_Highpt_NUM_PassTrigger);

     h_Gen_Lowpt_DEN_1000->Fill(Gen_Lowpt_DEN);
     h_Gen_Lowpt_NUM_PassTrigger_1000->Fill(Gen_Lowpt_NUM_PassTrigger);

     h_Gen_DeltaR_DEN_1000->Fill(Gen_DeltaR_DEN);
     h_Gen_DeltaR_NUM_PassTrigger_1000->Fill(Gen_DeltaR_NUM_PassTrigger);*/

     h_MET_pt_DEN_1000->Fill(MET_pt_DEN);
     h_MET_pt_NUM_PassTrigger_1000->Fill(MET_pt_NUM_PassTrigger);
	
  } 
  if(Nfiles==2){
     /*h_Gen_Highpt_DEN_1200->Fill(Gen_Highpt_DEN);
     h_Gen_Highpt_NUM_PassTrigger_1200->Fill(Gen_Highpt_NUM_PassTrigger);

     h_Gen_Lowpt_DEN_1200->Fill(Gen_Lowpt_DEN);
     h_Gen_Lowpt_NUM_PassTrigger_1200->Fill(Gen_Lowpt_NUM_PassTrigger);

     h_Gen_DeltaR_DEN_1200->Fill(Gen_DeltaR_DEN);
     h_Gen_DeltaR_NUM_PassTrigger_1200->Fill(Gen_DeltaR_NUM_PassTrigger);*/

     h_MET_pt_DEN_1200->Fill(MET_pt_DEN);
     h_MET_pt_NUM_PassTrigger_1200->Fill(MET_pt_NUM_PassTrigger);
  } 
}

void writeFile(){
  TFile *f;
  f = new TFile("Trigger_dineutrino.root","new"); 

  /*h_Gen_Highpt_DEN_0700->Write();
  h_Gen_Highpt_NUM_PassTrigger_0700->Write();
  h_Gen_Lowpt_DEN_0700->Write();
  h_Gen_Lowpt_NUM_PassTrigger_0700->Write();
  h_Gen_DeltaR_DEN_0700->Write();
  h_Gen_DeltaR_NUM_PassTrigger_0700->Write();

  h_Gen_Highpt_DEN_1000->Write();
  h_Gen_Highpt_NUM_PassTrigger_1000->Write();
  h_Gen_Lowpt_DEN_1000->Write();
  h_Gen_Lowpt_NUM_PassTrigger_1000->Write();
  h_Gen_DeltaR_DEN_1000->Write();
  h_Gen_DeltaR_NUM_PassTrigger_1000->Write();


  h_Gen_Highpt_DEN_1200->Write();
  h_Gen_Highpt_NUM_PassTrigger_1200->Write();
  h_Gen_Lowpt_DEN_1200->Write();
  h_Gen_Lowpt_NUM_PassTrigger_1200->Write();
  h_Gen_DeltaR_DEN_1200->Write();
  h_Gen_DeltaR_NUM_PassTrigger_1200->Write();*/

  h_MET_pt_DEN_0700->Write();
  h_MET_pt_NUM_PassTrigger_0700->Write();
  h_MET_pt_DEN_1000->Write();
  h_MET_pt_NUM_PassTrigger_1000->Write();
  h_MET_pt_DEN_1200->Write();
  h_MET_pt_NUM_PassTrigger_1200->Write();

  f->Close();
}

float DeltaR(float eta1, float eta2, float phi1, float phi2){
  float deltaPhi = TMath::Abs(phi1-phi2);
  float deltaEta = eta1-eta2;
  if(deltaPhi > TMath::Pi()) deltaPhi = TMath::TwoPi() - deltaPhi;
  return TMath::Sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
}
