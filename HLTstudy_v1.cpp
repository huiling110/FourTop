#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCut.h"


#include <iostream>

void HLTstudy_v1(){

    TFile *file_TTTT  = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forHLT_v1/NoJEC/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
    TTree *tree_TTTT = (TTree*)file_TTTT->Get("tree");
    
    const TCut channel_1tau0l =  "tausT_number==1 && leptonsMVAT_number==0 &&  jetsL_number>=8 && bjetsM_num>=2";
    // const TCut channel_1tau1e =  "tausT_number==1 && elesMVAT_number==1  && jetsL_number>=6 && bjetsM_num>=2";
    // const TCut channel_1tau1mu =
    const TCut channel_1tau1l = "tausT_number==1 && leptonsMVAT_number==1 &&  jetsL_number>=6 && bjetsM_num>=2";
    // const TCut channel_1tau2os = "tausT_number==1 && leptonsMVAT_number==2 && &&  jetsL_number>=8 && bjetsM_num>=2";//no branch available in ntuple
    // const TCut channel_1tau2ss =
    const TCut channel_1tau2l = "tausT_number==1 && leptonsMVAT_number==2 &&  jetsL_number>=4 && bjetsM_num>=2";
    const TCut channel_1tau3l = "tausT_number==1 && leptonsMVAT_number==3 &&  jetsL_number>=2 && bjetsM_num>=2";
    const TCut channel_2tau0l = "tausT_number==2 && leptonsMVAT_number==0 &&  jetsL_number>=6 && bjetsM_num>=2";
    const TCut channel_2tau1l = "tausT_number==2 && leptonsMVAT_number==1 &&  jetsL_number>=4 && bjetsM_num>=2";
    const TCut channel_2tau2l = "tausT_number==2 && leptonsMVAT_number==2 &&  jetsL_number>=2 && bjetsM_num>=2";

    const TString HLTname = "HLT_PFHT450_SixJet40_BTagCSV_p056";

    TH1F  *h_HLT_1tau0l = new TH1F("HLT_1tau0l", "HLT_1tau0l", 2, 0, 2);
    tree_TTTT->Project( "HLT_1tau0l", HLTname, channel_1tau0l); 
    // h_HLT_1tau0l->Print();
    double eventsFail_1tau0l = h_HLT_1tau0l->GetBinContent(1);
    double eventsPass_1tau0l = h_HLT_1tau0l->GetBinContent(2);
    std::cout<<"denominator = "<<eventsPass_1tau0l+eventsFail_1tau0l<<endl;
    std::cout<<"numerator   = "<<eventsPass_1tau0l<<endl;
    std::cout<<"1tau0l efficiency = "<<eventsPass_1tau0l/(eventsPass_1tau0l+eventsFail_1tau0l)<<endl;
    std::cout<<endl;
    // TH1F  *h_HLT_1tau0l = new TH1F("HLT_1tau0l", "HLT_1tau0l", 2, 0, 2);
    // tree_TTTT->Project( "HLT_1tau0l", "HLT_PFHT450_SixJet40_BTagCSV_p056", channel_1tau0l);
    // double eventsFail_1tau0l = h_HLT_1tau0l->GetBinContent(1);
    // double eventsPass_1tau0l = h_HLT_1tau0l->GetBinContent(2);
    // std::cout<<"denominator = "<<eventsPass_1tau0l+eventsFail_1tau0l<<endl;
    // std::cout<<"numerator   = "<<eventsPass_1tau0l<<endl;
    // std::cout<<"1tau0l efficiency = "<<eventsPass_1tau0l/(eventsPass_1tau0l+eventsFail_1tau0l)<<endl;
    // std::cout<<endl;

    TH1F  *h_HLT_1tau1l = new TH1F("HLT_1tau1l", "HLT_1tau1l", 2, 0, 2);
    tree_TTTT->Project( "HLT_1tau1l", HLTname, channel_1tau1l); 
    double eventsFail_1tau1l = h_HLT_1tau1l->GetBinContent(1);
    double eventsPass_1tau1l = h_HLT_1tau1l->GetBinContent(2);
    std::cout<<"denominator = "<<eventsPass_1tau1l+eventsFail_1tau1l<<endl;
    std::cout<<"numerator   = "<<eventsPass_1tau1l<<endl;
    std::cout<<"1tau1l efficiency = "<<eventsPass_1tau1l/(eventsPass_1tau1l+eventsFail_1tau1l)<<endl;
    std::cout<<endl;


    TH1F  *h_HLT_1tau2l = new TH1F("HLT_1tau2l", "HLT_1tau2l", 2, 0, 2);
    tree_TTTT->Project( "HLT_1tau2l", HLTname, channel_1tau2l); 
    double eventsFail_1tau2l = h_HLT_1tau2l->GetBinContent(1);
    double eventsPass_1tau2l = h_HLT_1tau2l->GetBinContent(2);
    std::cout<<"denominator = "<<eventsPass_1tau2l+eventsFail_1tau2l<<endl;
    std::cout<<"numerator   = "<<eventsPass_1tau2l<<endl;
    std::cout<<"1tau2l efficiency = "<<eventsPass_1tau2l/(eventsPass_1tau2l+eventsFail_1tau2l)<<endl;
    std::cout<<endl;

    TH1F  *h_HLT_1tau3l = new TH1F("HLT_1tau3l", "HLT_1tau3l", 2, 0, 2);
    tree_TTTT->Project( "HLT_1tau3l", HLTname, channel_1tau3l); 
    double eventsFail_1tau3l = h_HLT_1tau3l->GetBinContent(1);
    double eventsPass_1tau3l = h_HLT_1tau3l->GetBinContent(2);
    std::cout<<"denominator = "<<eventsPass_1tau3l+eventsFail_1tau3l<<endl;
    std::cout<<"numerator   = "<<eventsPass_1tau3l<<endl;
    std::cout<<"1tau3l efficiency = "<<eventsPass_1tau3l/(eventsPass_1tau3l+eventsFail_1tau3l)<<endl;
    std::cout<<endl;

    TH1F  *h_HLT_2tau0l = new TH1F("HLT_2tau0l", "HLT_2tau0l", 2, 0, 2);
    tree_TTTT->Project( "HLT_2tau0l", HLTname, channel_2tau0l); 
    double eventsFail_2tau0l = h_HLT_2tau0l->GetBinContent(1);
    double eventsPass_2tau0l = h_HLT_2tau0l->GetBinContent(2);
    std::cout<<"denominator = "<<eventsPass_2tau0l+eventsFail_2tau0l<<endl;
    std::cout<<"numerator   = "<<eventsPass_2tau0l<<endl;
    std::cout<<"2tau0l efficiency = "<<eventsPass_2tau0l/(eventsPass_2tau0l+eventsFail_2tau0l)<<endl;
    std::cout<<endl;

    TH1F  *h_HLT_2tau1l = new TH1F("HLT_2tau1l", "HLT_2tau1l", 2, 0, 2);
    tree_TTTT->Project( "HLT_2tau1l", HLTname, channel_2tau1l); 
    double eventsFail_2tau1l = h_HLT_2tau1l->GetBinContent(1);
    double eventsPass_2tau1l = h_HLT_2tau1l->GetBinContent(2);
    std::cout<<"denominator = "<<eventsPass_2tau1l+eventsFail_2tau1l<<endl;
    std::cout<<"numerator   = "<<eventsPass_2tau1l<<endl;
    std::cout<<"2tau1l efficiency = "<<eventsPass_2tau1l/(eventsPass_2tau1l+eventsFail_2tau1l)<<endl;
    std::cout<<endl;

    TH1F  *h_HLT_2tau2l = new TH1F("HLT_2tau2l", "HLT_2tau2l", 2, 0, 2);
    tree_TTTT->Project( "HLT_2tau2l", HLTname, channel_2tau2l); 
    double eventsFail_2tau2l = h_HLT_2tau2l->GetBinContent(1);
    double eventsPass_2tau2l = h_HLT_2tau2l->GetBinContent(2);
    std::cout<<"denominator = "<<eventsPass_2tau2l+eventsFail_2tau2l<<endl;
    std::cout<<"numerator   = "<<eventsPass_2tau2l<<endl;
    std::cout<<"2tau2l efficiency = "<<eventsPass_2tau2l/(eventsPass_2tau2l+eventsFail_2tau2l)<<endl;
    std::cout<<endl;




    delete h_HLT_1tau0l;
    delete h_HLT_1tau1l;
    delete h_HLT_1tau2l;




}
