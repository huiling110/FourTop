#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"


//sequence matter very much here
TString baseDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forMVA/v1/";

//TFile *file01 =   TFile::Open("data.root");
TFile *file02 =   TFile::Open(baseDir+"TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn.root");
TTree *Tree02 =   (TTree*)file02->Get("newtree");
TTree *Tree02all =   (TTree*)file02->Get("allevents");
//5
TFile *file03 =   TFile::Open(baseDir+"TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
TTree *Tree03 =   (TTree*)file03->Get("newtree");
TTree *Tree03all =   (TTree*)file03->Get("allevents");
TFile *file03_1 =   TFile::Open(baseDir+"TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
TTree *Tree03_1 =   (TTree*)file03->Get("newtree");
TTree *Tree03_1all =   (TTree*)file03->Get("allevents");
TFile *file03_2 =   TFile::Open(baseDir+"TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
TTree *Tree03_2 =   (TTree*)file03->Get("newtree");
TTree *Tree03_2all =   (TTree*)file03->Get("allevents");
vector<TTree*> allTree = {
    Tree02,Tree03, Tree03_1, Tree03_2
};
vector<TTree*> allTree_gen = {
    Tree02all, Tree03all, Tree03_1all, Tree03_2all
};



float separationPower(TH1D* h1, TH1D* h2);

int SigSF = 1;
//float LUMI  = 41500.0; //float LUMI = 36733; //36.773 /fb
float LUMI = 35900; //fb
//?where to get the more precise LUMI?
//SIGNAL

//double wTTTT = (SigSF*LUMI*0.009103);///TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root:  Positive:1709406  Negtive:704054
double wTTTT_sigma = (SigSF*LUMI*0.01197);//TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root 
//tt
double wTTJets_sigma = (LUMI*746.7);//746.7 //TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root 
double wTT_sigma     = (LUMI*746.7)  ; //TT_TuneCUETP8M2T4_13TeV-powheg-pythia8.root 

double wTTGJets_sigma = (LUMI*3.773);  ; //TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root
double wttZJets_sigma = (LUMI*0.6559) ;      //Special care is taken when scaling the ttZ background to the cross-section= (LUMI*)/(-) //ttZJets_13TeV_madgraphMLM-pythia8.root 
double wttWJets_sigma = (LUMI*0.2014);  ; //  ttWJets_13TeV_madgraphMLM.root 
double wttH_sigma= (LUMI*0.3372);  ; //ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root 

//diboson and triboson an w_sigma/z+jets
double wWZ_sigma= (LUMI*2.343);  ;//WZ_TuneCUETP8M1_13TeV-pythia8.root 
//double wWW_sigma= (LUMI*6.430);//?something wrong with ntuple
double wWWTo2L2Nu_sigma = (LUMI*0.1697);   ;//r WWTo2L2Nu_DoubleScattering_13TeV-pythia8.root 
double wWpWpJJ_sigma= (LUMI*0.05390);  ;//WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root 
double wZZ_sigma  = (LUMI*1.016);  ;//ZZ_TuneCUETP8M1_13TeV-pythia8.root 
double wWGJets_sigma = (LUMI*1.269);  ;//WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root 
double wZGJetsToLLG_sigma = (LUMI*0.1319);  ;// ZGJetsToLLG_EW_LO_13TeV-sherpa.root 
//
double wWWW_sigma= (LUMI*0.2086);  ;// WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
double wWWZ_sigma= (LUMI*0.1651);  ;//WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
double wWWG_sigma = (LUMI*0.2147);  ; //WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
double wZZZ_sigma= (LUMI*0.01398);  ;//ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
double wWZZ_sigma= (LUMI*0.05565);  ; //WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
double wWZG_sigma= (LUMI*0.04123);  ;// WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
//double wWGGJets_sigma = (LUMI*1.711);//
double wWGG_sigma =(LUMI*1.819);   ;// WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
double wZGGJets_sigma= (LUMI*0.3717);  ;//ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8.root 


double wWJetsToLNu_sigma= (LUMI*50300) ;  ;//WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root 
//?missing ZJets?= (LUMI*)
//Drell-Yan
double wDYJetsToTauTau_sigma= (LUMI*1983);  ;//DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1.root 
//
//single top
double wtZq_ll_sigma= (LUMI*0.07358);  ;//tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8.root 
//double wtZq_nunu_sigma= (LUMI*);// tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1.root Positive:630623  Negtive:368977  ;//
//?
double wST_tW_antitop_sigma= (LUMI*38.06);  ;//ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root 
double wST_tW_top_sigma= (LUMI*38.09);  ;//ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root 
double wTGJets_sigma= (LUMI*2.967);  ;//TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root 
double wTHW_sigma= (LUMI*0.1467);  ;//THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8.root 
double wTHQ_sigma= (LUMI*0.8816);  ;//THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1.root 
//H 
double wVHToNonbb_sigma= (LUMI*2.137);  ;//VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8.root 
double wZHToTauTau_sigma= (LUMI*0.7524);  ;// ZHToTauTau_M125_13TeV_powheg_pythia8.root 
double wZH_HToBB_ZToLL_sigma= (LUMI*0.07523);  ;//ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8.root 
double wGluGluHToZZTo4L_sigma= (LUMI*2.999);  ;//GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8.root 
double wGluGluHToBB_sigma= (LUMI*32.10);  ;//GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.root 
double wGluGluHToGG_sigma= (LUMI*31.98);  ;//GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root 
double wGluGluHToMuMu_sigma= (LUMI*29.99);  ;//GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root 

double wGluGluHToTauTau_sigma= (LUMI*30.52);  ;//GluGluHToTauTau_M125_13TeV_powheg_pythia8.root 
double wGluGluHToWWTo2L2Nu_sigma= (LUMI*30.52);  ;//GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8.root 
double wGluGluHToWWToLNuQQ_sigma= (LUMI*29.99);  ;//GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8.root 
//double wVBFHToWWToLNuQQ_sigma= (LUMI*3.769)//
double wVBFHToWWTo2L2Nu_sigma= (LUMI*3.769);  ;//VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8.root 
//??very different from ttH
//double wVBFHToWWTo2L2Nu_sigma= (LUMI*);
//double wVBFHToTauTau_sigma= (LUMI*0.237);// VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root Positive:996835  Negtive:765  ;
double wVBFHToMuMu_sigma= (LUMI*0.000823);  ;//VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root 
double wVBFHToGG_sigma= (LUMI*3.992);  ;//VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2.root 
// double wVBFHToBB= (LUMI*)/(-)//
//double wVBF_HToZZTo4L= (LUMI*3.769)/(-)
//HH count as minor
//minor
vector<double> allSigmas {
    wTTTT_sigma, //0
    wTT_sigma, //changed wTTJets to wTT
    wTTGJets_sigma, wttZJets_sigma, wttWJets_sigma, wttH_sigma, //5
    wWZ_sigma, wWWTo2L2Nu_sigma, wWpWpJJ_sigma, wZZ_sigma, wWGJets_sigma, wZGJetsToLLG_sigma, 
    wWWW_sigma, wWWZ_sigma, wWWG_sigma, wZZZ_sigma, wWZZ_sigma, wWZG_sigma, wWGG_sigma, wZGGJets_sigma, 
    wWJetsToLNu_sigma, wDYJetsToTauTau_sigma, 
    wtZq_ll_sigma, wST_tW_antitop_sigma, wST_tW_top_sigma, wTGJets_sigma, wTHW_sigma, wTHQ_sigma, 
    wVHToNonbb_sigma, wZHToTauTau_sigma, wZH_HToBB_ZToLL_sigma, wGluGluHToZZTo4L_sigma, wGluGluHToBB_sigma, wGluGluHToGG_sigma, wGluGluHToMuMu_sigma, wGluGluHToTauTau_sigma, wGluGluHToWWTo2L2Nu_sigma, wGluGluHToWWToLNuQQ_sigma, wVBFHToWWTo2L2Nu_sigma, /*wVBFHToTauTau_sigma, */wVBFHToMuMu_sigma, wVBFHToGG_sigma
};



/*
TFile *file04 =   TFile::Open(baseDir+"TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");//TTGJets
TFile *file05 =   TFile::Open(baseDir+"ttZJets_13TeV_madgraphMLM-pythia8.root");
TFile *file06 =   TFile::Open(baseDir+"ttWJets_13TeV_madgraphMLM.root");
TFile *file07 =   TFile::Open(baseDir+"ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root");//ttH
//6
TFile *file09 =   TFile::Open(baseDir+"WZ_TuneCUETP8M1_13TeV-pythia8.root");
//TFile *file10 =   TFile::Open(baseDir+"WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_1 =   TFile::Open(baseDir+"WWTo2L2Nu_DoubleScattering_13TeV-pythia8.root");
TFile *file11 =   TFile::Open(baseDir+"WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");//?missing this in other places
TFile *file12 =   TFile::Open(baseDir+"ZZ_TuneCUETP8M1_13TeV-pythia8.root");//ZZ
TFile *file13 =   TFile::Open(baseDir+"WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");//

TFile *file14 =   TFile::Open(baseDir+"ZGJetsToLLG_EW_LO_13TeV-sherpa.root");//
//8
TFile *file15 =   TFile::Open(baseDir+"WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file16 =   TFile::Open(baseDir+"WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file17 =   TFile::Open(baseDir+"WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file18 =   TFile::Open(baseDir+"ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file19 =   TFile::Open(baseDir+"WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file20 =   TFile::Open(baseDir+"WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file21 =   TFile::Open(baseDir+"WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");
TFile *file22 =   TFile::Open(baseDir+"ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8.root");
//
TFile *file23 =   TFile::Open(baseDir+"WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");//WJets
TFile *file24 =   TFile::Open(baseDir+"DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1.root");
//7-1
TFile *file25 =   TFile::Open(baseDir+"tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8.root");
//TFile *file26 =   TFile::Open(baseDir+"tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1.root");
TFile *file27 =   TFile::Open(baseDir+"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root");
TFile *file28 =   TFile::Open(baseDir+"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root");
TFile *file29 =   TFile::Open(baseDir+"TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root");
TFile *file30 =   TFile::Open(baseDir+"THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8.root");
TFile *file31 =   TFile::Open(baseDir+"THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1.root");
//12
TFile *file32 =   TFile::Open(baseDir+"VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8.root");
TFile *file33 =   TFile::Open(baseDir+"ZHToTauTau_M125_13TeV_powheg_pythia8.root");
TFile *file34 =   TFile::Open(baseDir+"ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8.root");
TFile *file35 =   TFile::Open(baseDir+"GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8.root");
TFile *file36 =   TFile::Open(baseDir+"GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.root");
TFile *file37 =   TFile::Open(baseDir+"GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root");
TFile *file38 =   TFile::Open(baseDir+"GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root");
TFile *file39 =   TFile::Open(baseDir+"GluGluHToTauTau_M125_13TeV_powheg_pythia8.root");
TFile *file40 =   TFile::Open(baseDir+"GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8.root");
TFile *file41 =   TFile::Open(baseDir+"GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8.root");
TFile *file42 =   TFile::Open(baseDir+"VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8.root");
//TFile *file43 =   TFile::Open(baseDir+"VBFHToTauTau_M125_13TeV_powheg_pythia8.root");//bad input file
TFile *file44 =   TFile::Open(baseDir+"VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root");
TFile *file45 =   TFile::Open(baseDir+"VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2.root");
*/


//TTree *Tree01 =   (TTree*)file01->Get("tree");
/*
TTree *Tree04 =   (TTree*)file04->Get("tree");
TTree *Tree05 =   (TTree*)file05->Get("tree");
TTree *Tree06 =   (TTree*)file06->Get("tree");
TTree *Tree07 =   (TTree*)file07->Get("tree");
// TTree *Tree08 =   (TTree*)file08->Get("tree");
TTree *Tree09 =   (TTree*)file09->Get("tree");
//TTree *Tree10 =   (TTree*)file10->Get("tree");
TTree *Tree10_1 =   (TTree*)file10_1->Get("tree");
TTree *Tree11 =   (TTree*)file11->Get("tree");
TTree *Tree12 =   (TTree*)file12->Get("tree");
TTree *Tree13 =   (TTree*)file13->Get("tree");
TTree *Tree14 =   (TTree*)file14->Get("tree");
TTree *Tree15 =   (TTree*)file15->Get("tree");
TTree *Tree16 =   (TTree*)file16->Get("tree");
TTree *Tree17 =   (TTree*)file17->Get("tree");
TTree *Tree18 =   (TTree*)file18->Get("tree");
TTree *Tree19 =   (TTree*)file19->Get("tree");
TTree *Tree20 =   (TTree*)file20->Get("tree");
TTree *Tree21 =   (TTree*)file21->Get("tree");
TTree *Tree22 =   (TTree*)file22->Get("tree");
TTree *Tree23 =   (TTree*)file23->Get("tree");
TTree *Tree24 =   (TTree*)file24->Get("tree");
TTree *Tree25 =   (TTree*)file25->Get("tree");
//TTree *Tree26 =   (TTree*)file26->Get("tree");
TTree *Tree27 =   (TTree*)file27->Get("tree");
TTree *Tree28 =   (TTree*)file28->Get("tree");
TTree *Tree29 =   (TTree*)file29->Get("tree");
TTree *Tree30 =   (TTree*)file30->Get("tree");
TTree *Tree31 =   (TTree*)file31->Get("tree");
TTree *Tree32 =   (TTree*)file32->Get("tree");
TTree *Tree33 =   (TTree*)file33->Get("tree");
TTree *Tree34 =   (TTree*)file34->Get("tree");
TTree *Tree35 =   (TTree*)file35->Get("tree");
TTree *Tree36 =   (TTree*)file36->Get("tree");
TTree *Tree37 =   (TTree*)file37->Get("tree");
TTree *Tree38 =   (TTree*)file38->Get("tree");
TTree *Tree39 =   (TTree*)file39->Get("tree");
TTree *Tree40 =   (TTree*)file40->Get("tree");
TTree *Tree41 =   (TTree*)file41->Get("tree");
TTree *Tree42 =   (TTree*)file42->Get("tree");
//TTree *Tree43 =   (TTree*)file43->Get("tree");
TTree *Tree44 =   (TTree*)file44->Get("tree");
TTree *Tree45 =   (TTree*)file45->Get("tree");
*/


                                                   

