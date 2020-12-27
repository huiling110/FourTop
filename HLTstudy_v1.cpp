#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"

#include <iostream>

void HLTstudy_v1(){

    TFile *file_TTTT  = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forHLT_v1/NoJEC/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
    TTree *tree_TTTT = (TTree*)file_TTTT->Get("tree");
    
    const TCut channel_1tau0l =  "tausT_number==1 && leptonsMVAT_number==0 &&  jetsL_number>=8 && bjetsM_num>=2";

    TH1F  *h_HLT = new TH1F("HLT", "HLT", 2, 0, 2);
    tree_TTTT->Project( "HLT", "HLT_PFHT450_SixJet40_BTagCSV_p056", channel_1tau0l); 
    h_HLT->Print();

    double eventsFail = h_HLT->GetBinContent(1);
    double eventsPass = h_HLT->GetBinContent(2);

    std::cout<<"denominator = "<<eventsPass+eventsFail<<endl;
    std::cout<<"nemeritor   = "<<eventsPass<<endl;
    std::cout<<"global efficiency = "<<eventsPass/(eventsPass+eventsFail)<<endl;




    delete h_HLT;




}
