#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCut.h"


#include <iostream>

void HLTstudy_v1(){

    // bool isGen = false;
    bool isGen = true;

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

    // const TCut channel_1tau0l_gen = "genTaus_number==1 && genEles_number==0 && genMuons_number==0";
    // const TCut channel_1tau0l_gen = "genTaus_number==1 && genEles_number==0  ";
    const TCut channel_1tau0l_gen = "genTaus_number==1 && genMuons_number==0";
    const TCut channel_1tau1l_gen = "genTaus_number==1 && (genEles_number==1 || genMuons_number==1)";
    const TCut channel_1tau2l_gen = "genTaus_number==1 && (genEles_number+genMuons_number)==2";
    const TCut channel_1tau3l_gen = "genTaus_number==1 && (genEles_number+genMuons_number)==3";
    const TCut channel_2tau0l_gen = "genTaus_number==2 && (genEles_number+genMuons_number)==0";
    const TCut channel_2tau1l_gen = "genTaus_number==2 && (genEles_number+genMuons_number)==1";
    const TCut channel_2tau2l_gen = "genTaus_number==2 && (genEles_number+genMuons_number)==2";

    const vector<TCut> channels = { channel_1tau0l, channel_1tau1l, channel_1tau2l, channel_1tau3l, channel_2tau0l, channel_2tau1l, channel_2tau2l};
    const vector<TCut> channels_gen = { channel_1tau0l_gen, channel_1tau1l_gen, channel_1tau2l_gen, channel_1tau3l_gen, channel_2tau0l_gen, channel_2tau1l_gen, channel_2tau2l_gen};
    const vector<TString> channelNames = { "1tau0l", "1tau1l",      "1tau2l",       "1tau3l",       "2tau0l",       "2tau1l",       "2tau2l"};

    
    const TCut singleEleHLT  =  "HLT_Ele25_eta2p1_WPTight_Gsf==1 || HLT_Ele27_WPTight_Gsf==1 || HLT_Ele27_eta2p1_WPTight_Gsf==1";
    const TCut singleMuHLT   = " HLT_IsoMu22==1 || HLT_IsoTkMu22==1 || HLT_IsoMu22_eta2p1==1 || HLT_IsoTkMu22_eta2p1==1 || HLT_IsoMu24==1 || HLT_IsoTkMu24==1 || HLT_IsoMu27==1";
    const TCut eleTauHLT     = "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20==1 || HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1==1 || HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30==1";
    const TCut muTauHLT      = "HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1==1 || HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1==1";
    const TCut doubleEleHLT  = "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ==1";
    const TCut doubleMuHLT   = "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL==1 || HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ==1 || HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8==1";
    const TCut eleMuHLT      = "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ==1 || HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ==1 ||          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL==1";
    const TCut tripleleptons = "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL==1 || HLT_TripleMu_12_10_5==1  || HLT_Mu8_DiEle12_CaloIdL_TrackIdL==1 || HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ==1 || HLT_DiMu9_Ele9_CaloIdL_TrackIdL==1";
    const TCut HLTset_1tau0l = "HLT_PFHT450_SixJet40_BTagCSV_p056==1 || HLT_PFHT400_SixJet30_DoubleBTagCSV_p056==1";
    const TCut HLTset_1tau1l = singleEleHLT || singleMuHLT || eleTauHLT || muTauHLT; 
    const TCut HLTset_1tau2l = singleEleHLT || singleMuHLT || doubleEleHLT || doubleMuHLT || eleMuHLT;
    const TCut HLTset_1tau3l = singleEleHLT || singleMuHLT || doubleEleHLT || doubleMuHLT || eleMuHLT || tripleleptons;
    const TCut HLTset_2tau0l = HLTset_1tau0l;
    const TCut HLTset_2tau1l = HLTset_1tau1l;
    const TCut HLTset_2tau2l = HLTset_1tau2l;
    const vector<TCut> HLTsets = { HLTset_1tau0l, HLTset_1tau1l, HLTset_1tau2l, HLTset_1tau3l, HLTset_2tau0l, HLTset_2tau1l, HLTset_2tau2l };

    // const TString HLTname = "HLT_PFHT450_SixJet40_BTagCSV_p056";
    const vector<TString> HLTnames = { "HLT_PFHT450_SixJet40_BTagCSV_p056", "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056"};

    for (UInt_t i=0; i<channels.size(); i++){
    // for (UInt_t i=1; i<channels.size(); i++){
        if( !(channels.size()==channelNames.size() && channels.size()==HLTsets.size())) {
            std::cout<<"size not matching"<<endl;
            return;
        }

        TH1F *denominator = new TH1F("1tau0l_de", "1tau0l_de", 2, 0, 2);
        TH1F *numerator   = new TH1F("1tau0l_nu", "1tau0l_nu", 2, 0, 2);
        if ( !isGen ){
            std::cout<<"global efficiency of "<<channelNames[i]<<"in preselection region :"<<endl;
            tree_TTTT->Project( "1tau0l_de", "HLT_PFHT450_SixJet40_BTagCSV_p056", channels[i]);
            tree_TTTT->Project( "1tau0l_nu", "HLT_PFHT450_SixJet40_BTagCSV_p056", channels[i]&&HLTsets[i]);
            // tree_TTTT->Project( "1tau0l_nu", "HLT_PFHT450_SixJet40_BTagCSV_p056", channels[i]&&leptonTauHLT);
        }else{
            std::cout<<"global efficiency of "<<channelNames[i]<<"in truth region :"<<endl;
            tree_TTTT->Project( "1tau0l_de", "HLT_PFHT450_SixJet40_BTagCSV_p056", channels_gen[i]);
            tree_TTTT->Project( "1tau0l_nu", "HLT_PFHT450_SixJet40_BTagCSV_p056", channels_gen[i]&&HLTsets[i]);
        }
        denominator->Print();
        std::cout<<"denominator = "<<denominator->Integral()<<endl;
        std::cout<<"numerator   = "<<numerator->Integral()<<endl;
        std::cout<<"efficiency  = "<<numerator->Integral()/denominator->Integral()<<endl;
        std::cout<<endl;

        delete denominator;
        delete numerator;
    }

    // for (UInt_t i=0; i<HLTnames.size(); i++ ){
        // TH1F  *h_HLT_1tau0l = new TH1F("HLT_1tau0l", "HLT_1tau0l", 2, 0, 2);
        // tree_TTTT->Project( "HLT_1tau0l", HLTnames[i], channel_1tau0l);
        // double eventsFail_1tau0l = h_HLT_1tau0l->GetBinContent(1);
        // double eventsPass_1tau0l = h_HLT_1tau0l->GetBinContent(2);
        // std::cout<<"denominator = "<<eventsPass_1tau0l+eventsFail_1tau0l<<endl;
        // std::cout<<"numerator   = "<<eventsPass_1tau0l<<endl;
        // std::cout<<"1tau0l efficiency = "<<eventsPass_1tau0l/(eventsPass_1tau0l+eventsFail_1tau0l)<<endl;
        // std::cout<<endl;
//
        // TH1F  *h_HLT_1tau1l = new TH1F("HLT_1tau1l", "HLT_1tau1l", 2, 0, 2);
        // tree_TTTT->Project( "HLT_1tau1l", HLTnames[i], channel_1tau1l);
        // double eventsFail_1tau1l = h_HLT_1tau1l->GetBinContent(1);
        // double eventsPass_1tau1l = h_HLT_1tau1l->GetBinContent(2);
        // std::cout<<"denominator = "<<eventsPass_1tau1l+eventsFail_1tau1l<<endl;
        // std::cout<<"numerator   = "<<eventsPass_1tau1l<<endl;
        // std::cout<<"1tau1l efficiency = "<<eventsPass_1tau1l/(eventsPass_1tau1l+eventsFail_1tau1l)<<endl;
        // std::cout<<endl;
//
//
        // TH1F  *h_HLT_1tau2l = new TH1F("HLT_1tau2l", "HLT_1tau2l", 2, 0, 2);
        // tree_TTTT->Project( "HLT_1tau2l", HLTnames[i], channel_1tau2l);
        // double eventsFail_1tau2l = h_HLT_1tau2l->GetBinContent(1);
        // double eventsPass_1tau2l = h_HLT_1tau2l->GetBinContent(2);
        // std::cout<<"denominator = "<<eventsPass_1tau2l+eventsFail_1tau2l<<endl;
        // std::cout<<"numerator   = "<<eventsPass_1tau2l<<endl;
        // std::cout<<"1tau2l efficiency = "<<eventsPass_1tau2l/(eventsPass_1tau2l+eventsFail_1tau2l)<<endl;
        // std::cout<<endl;
//
        // TH1F  *h_HLT_1tau3l = new TH1F("HLT_1tau3l", "HLT_1tau3l", 2, 0, 2);
        // tree_TTTT->Project( "HLT_1tau3l", HLTnames[i], channel_1tau3l);
        // double eventsFail_1tau3l = h_HLT_1tau3l->GetBinContent(1);
        // double eventsPass_1tau3l = h_HLT_1tau3l->GetBinContent(2);
        // std::cout<<"denominator = "<<eventsPass_1tau3l+eventsFail_1tau3l<<endl;
        // std::cout<<"numerator   = "<<eventsPass_1tau3l<<endl;
        // std::cout<<"1tau3l efficiency = "<<eventsPass_1tau3l/(eventsPass_1tau3l+eventsFail_1tau3l)<<endl;
        // std::cout<<endl;
//
        // TH1F  *h_HLT_2tau0l = new TH1F("HLT_2tau0l", "HLT_2tau0l", 2, 0, 2);
        // tree_TTTT->Project( "HLT_2tau0l", HLTnames[i], channel_2tau0l);
        // double eventsFail_2tau0l = h_HLT_2tau0l->GetBinContent(1);
        // double eventsPass_2tau0l = h_HLT_2tau0l->GetBinContent(2);
        // std::cout<<"denominator = "<<eventsPass_2tau0l+eventsFail_2tau0l<<endl;
        // std::cout<<"numerator   = "<<eventsPass_2tau0l<<endl;
        // std::cout<<"2tau0l efficiency = "<<eventsPass_2tau0l/(eventsPass_2tau0l+eventsFail_2tau0l)<<endl;
        // std::cout<<endl;
//
        // TH1F  *h_HLT_2tau1l = new TH1F("HLT_2tau1l", "HLT_2tau1l", 2, 0, 2);
        // tree_TTTT->Project( "HLT_2tau1l", HLTnames[i], channel_2tau1l);
        // double eventsFail_2tau1l = h_HLT_2tau1l->GetBinContent(1);
        // double eventsPass_2tau1l = h_HLT_2tau1l->GetBinContent(2);
        // std::cout<<"denominator = "<<eventsPass_2tau1l+eventsFail_2tau1l<<endl;
        // std::cout<<"numerator   = "<<eventsPass_2tau1l<<endl;
        // std::cout<<"2tau1l efficiency = "<<eventsPass_2tau1l/(eventsPass_2tau1l+eventsFail_2tau1l)<<endl;
        // std::cout<<endl;
//
        // TH1F  *h_HLT_2tau2l = new TH1F("HLT_2tau2l", "HLT_2tau2l", 2, 0, 2);
        // tree_TTTT->Project( "HLT_2tau2l", HLTnames[i], channel_2tau2l);
        // double eventsFail_2tau2l = h_HLT_2tau2l->GetBinContent(1);
        // double eventsPass_2tau2l = h_HLT_2tau2l->GetBinContent(2);
        // std::cout<<"denominator = "<<eventsPass_2tau2l+eventsFail_2tau2l<<endl;
        // std::cout<<"numerator   = "<<eventsPass_2tau2l<<endl;
        // std::cout<<"2tau2l efficiency = "<<eventsPass_2tau2l/(eventsPass_2tau2l+eventsFail_2tau2l)<<endl;
        // std::cout<<endl;
//
        // delete h_HLT_1tau0l; //The delete operator does not actually delete anything. It simply returns the memory being pointed to back to the operating system.
        // delete h_HLT_1tau1l;
        // delete h_HLT_1tau2l;
        // delete h_HLT_1tau3l;
        // delete h_HLT_2tau0l;
        // delete h_HLT_2tau2l;
        // delete h_HLT_2tau2l;
    // }







}
