#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"


TString baseDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forMVA/v1/";
class Process
{
    private:
        TString m_fileName;
        Double_t m_sigma;
        TFile* m_file;
        // TTree *eventTree;
        // TTree *alleventTree;
    public:
        Process( TString fileName, Double_t sigma)
            :m_fileName{ fileName}, m_sigma{ sigma}
        {
            m_file = TFile::Open( m_fileName);
        }

        TTree* getEventTree(){
            return (TTree*)m_file->Get( "newtree");
        }
        TTree* getAllEventTree(){
            return (TTree*)m_file->Get("allevents");
        }

};

Process TTTT{ baseDir+"TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn.root", 0.01197};
Process TTTo2L2Nu{ baseDir+ "TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8.root", 373. };
Process TTToHadronic(baseDir+"TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8.root", 367. );
Process TTToSemiLeptonic(baseDir+"TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root", 90.6);
// Process TTGJets(baseDir+"TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root", 3.773 );//TTGJets
Process ttZJets(baseDir+"ttZJets_13TeV_madgraphMLM-pythia8.root", 0.6559);//???something with the files
Process ttWJets(baseDir+"ttWJets_13TeV_madgraphMLM.root", 0.2014 );
Process ttH(baseDir+"ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root", 0.3372 );//ttH
//6
Process WZ(baseDir+"WZ_TuneCUETP8M1_13TeV-pythia8.root", 2.343 );
Process WW(baseDir+"WW_TuneCUETP8M1_13TeV-pythia8.root", 6.430 );
//ProcessWWTo2L2Nu+"WWTo2L2Nu_DoubleScattering_13TeV-pythia8.root", 0.1697 );
// Process (baseDir+"WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root", 0.05390 );//?missing this in other places
Process ZZ(baseDir+"ZZ_TuneCUETP8M1_13TeV-pythia8.root", 1.016 );//ZZ
Process WGJets(baseDir+"WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root", 1.269 );//
Process ZGJetsToLLG(baseDir+"ZGJetsToLLG_EW_LO_13TeV-sherpa.root", 0.1319 );//
//8
Process WWW(baseDir+"WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root", 0.2086 );//
Process WWZ(baseDir+"WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root", 0.1651 );//
// Process WWG(baseDir+"WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
Process ZZZ(baseDir+"ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root", 0.01398 );//
Process WZZ(baseDir+"WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root", 0.05565 );//
Process WZG(baseDir+"WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root", 0.04123 );//
Process WGG(baseDir+"WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root", 1.819 );
Process ZGGJets(baseDir+"ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8.root", 0.3717 );
//
// Process WJetsToLNu(baseDir+"WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root", 50300 );//WJets
Process DYJetsToTauTau(baseDir+"DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1.root", 1983 );
//7-1
Process tZq_ll(baseDir+"tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8.root", 0.07358 );
// Process tZq_nunu(baseDir+"tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1.root", );//???
Process ST_tW_antitop(baseDir+"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root", 38.06 );
Process ST_tW_top(baseDir+"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root", 38.09 );
Process TGJets(baseDir+"TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root", 2.967 );
Process THW(baseDir+"THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8.root", 0.1467 );
Process THQ(baseDir+"THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1.root", 0.8816 );
//12
Process VHToNonbb(baseDir+"VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8.root", 2.137 );
// Process ZHToTauTau(baseDir+"ZHToTauTau_M125_13TeV_powheg_pythia8.root", 0.7524 );
Process ZH_HToBB_ZToLL(baseDir+"ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8.root", 0.07523 );
// Process GluGluHToZZTo4L(baseDir+"GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8.root", 2.999 );
Process GluGluHToBB(baseDir+"GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.root", 32.10 );
Process GluGluHToGG(baseDir+"GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root", 31.98 );
Process GluGluHToMuMu(baseDir+"GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root", 29.99 );
Process GluGluHToTauTau(baseDir+"GluGluHToTauTau_M125_13TeV_powheg_pythia8.root", 30.52 );
Process GluGluHToWWTo2L2Nu(baseDir+"GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8.root", 30.52 );
Process GluGluHToWWToLNuQQ(baseDir+"GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8.root", 29.99 );
Process VBFHToWWTo2L2Nu(baseDir+"VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8.root", 3.769  );//??very different from ttH
Process VBFHToTauTau(baseDir+"VBFHToTauTau_M125_13TeV_powheg_pythia8.root", 0.237 );
Process VBFHToMuMu(baseDir+"VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root", 0.000823 );
Process VBFHToGG(baseDir+"VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2.root", 3.992 );

vector<Process> allProcesses = {
    TTTT, //0
    TTTo2L2Nu, TTToHadronic, TTToSemiLeptonic, //3
   /* ttZJets,*/ ttWJets, ttH, //6
    WZ, WW, ZZ, WGJets, ZGJetsToLLG, 
    WWW, WWZ, ZZZ, WZZ, WZG, WGG, ZGGJets,
    /*WJetsToLNu,*/ DYJetsToTauTau,
    tZq_ll,/* tZq_nunu,*/ ST_tW_antitop, ST_tW_top,
    TGJets, THW, THQ,
    VHToNonbb, /*ZHToTauTau,*/ ZH_HToBB_ZToLL,/* GluGluHToZZTo4L,*/ /*GluGluHToBB.*/ GluGluHToGG, GluGluHToMuMu, GluGluHToTauTau, GluGluHToWWTo2L2Nu, GluGluHToWWToLNuQQ, VBFHToWWTo2L2Nu, VBFHToTauTau, VBFHToMuMu, VBFHToGG,
};
//sequence matter very much here

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

// TFile *file04 =   TFile::Open(baseDir+"TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");//TTGJets
TFile *file05 =   TFile::Open(baseDir+"ttZJets_13TeV_madgraphMLM-pythia8.root");
TFile *file06 =   TFile::Open(baseDir+"ttWJets_13TeV_madgraphMLM.root");
TFile *file07 =   TFile::Open(baseDir+"ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root");//ttH
//6
TFile *file09 =   TFile::Open(baseDir+"WZ_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10 =   TFile::Open(baseDir+"WW_TuneCUETP8M1_13TeV-pythia8.root");
// TFile *file10_1 =   TFile::Open(baseDir+"WWTo2L2Nu_DoubleScattering_13TeV-pythia8.root");
// TFile *file11 =   TFile::Open(baseDir+"WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");//?missing this in other places
TFile *file12 =   TFile::Open(baseDir+"ZZ_TuneCUETP8M1_13TeV-pythia8.root");//ZZ
TFile *file13 =   TFile::Open(baseDir+"WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");//
TFile *file14 =   TFile::Open(baseDir+"ZGJetsToLLG_EW_LO_13TeV-sherpa.root");//
//8
TFile *file15 =   TFile::Open(baseDir+"WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file16 =   TFile::Open(baseDir+"WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
// TFile *file17 =   TFile::Open(baseDir+"WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file18 =   TFile::Open(baseDir+"ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file19 =   TFile::Open(baseDir+"WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file20 =   TFile::Open(baseDir+"WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file21 =   TFile::Open(baseDir+"WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");
TFile *file22 =   TFile::Open(baseDir+"ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8.root");
//
// TFile *file23 =   TFile::Open(baseDir+"WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");//WJets
TFile *file24 =   TFile::Open(baseDir+"DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1.root");
//7-1
TFile *file25 =   TFile::Open(baseDir+"tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8.root");
TFile *file26 =   TFile::Open(baseDir+"tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1.root");
TFile *file27 =   TFile::Open(baseDir+"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root");
TFile *file28 =   TFile::Open(baseDir+"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root");
TFile *file29 =   TFile::Open(baseDir+"TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root");
TFile *file30 =   TFile::Open(baseDir+"THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8.root");
TFile *file31 =   TFile::Open(baseDir+"THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1.root");
//12
TFile *file32 =   TFile::Open(baseDir+"VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8.root");
// TFile *file33 =   TFile::Open(baseDir+"ZHToTauTau_M125_13TeV_powheg_pythia8.root");
TFile *file34 =   TFile::Open(baseDir+"ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8.root");
// TFile *file35 =   TFile::Open(baseDir+"GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8.root");
TFile *file36 =   TFile::Open(baseDir+"GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.root");
TFile *file37 =   TFile::Open(baseDir+"GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root");
TFile *file38 =   TFile::Open(baseDir+"GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root");
TFile *file39 =   TFile::Open(baseDir+"GluGluHToTauTau_M125_13TeV_powheg_pythia8.root");
TFile *file40 =   TFile::Open(baseDir+"GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8.root");
TFile *file41 =   TFile::Open(baseDir+"GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8.root");
TFile *file42 =   TFile::Open(baseDir+"VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8.root");
TFile *file43 =   TFile::Open(baseDir+"VBFHToTauTau_M125_13TeV_powheg_pythia8.root");//bad input file
TFile *file44 =   TFile::Open(baseDir+"VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root");
TFile *file45 =   TFile::Open(baseDir+"VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2.root");


// TTree *Tree04 =   (TTree*)file04->Get("tree");
TTree *Tree05 =   (TTree*)file05->Get("tree");
TTree *Tree06 =   (TTree*)file06->Get("tree");
TTree *Tree07 =   (TTree*)file07->Get("tree");
TTree *Tree09 =   (TTree*)file09->Get("tree");
TTree *Tree10 =   (TTree*)file10->Get("tree");
// TTree *Tree10_1 =   (TTree*)file10_1->Get("tree");
// TTree *Tree11 =   (TTree*)file11->Get("tree");
TTree *Tree12 =   (TTree*)file12->Get("tree");
TTree *Tree13 =   (TTree*)file13->Get("tree");
TTree *Tree14 =   (TTree*)file14->Get("tree");
TTree *Tree15 =   (TTree*)file15->Get("tree");
TTree *Tree16 =   (TTree*)file16->Get("tree");
// TTree *Tree17 =   (TTree*)file17->Get("tree");
TTree *Tree18 =   (TTree*)file18->Get("tree");
TTree *Tree19 =   (TTree*)file19->Get("tree");
TTree *Tree20 =   (TTree*)file20->Get("tree");
TTree *Tree21 =   (TTree*)file21->Get("tree");
TTree *Tree22 =   (TTree*)file22->Get("tree");
// TTree *Tree23 =   (TTree*)file23->Get("tree");
TTree *Tree24 =   (TTree*)file24->Get("tree");
TTree *Tree25 =   (TTree*)file25->Get("tree");
TTree *Tree26 =   (TTree*)file26->Get("tree");
TTree *Tree27 =   (TTree*)file27->Get("tree");
TTree *Tree28 =   (TTree*)file28->Get("tree");
TTree *Tree29 =   (TTree*)file29->Get("tree");
TTree *Tree30 =   (TTree*)file30->Get("tree");
TTree *Tree31 =   (TTree*)file31->Get("tree");
TTree *Tree32 =   (TTree*)file32->Get("tree");
// TTree *Tree33 =   (TTree*)file33->Get("tree");
TTree *Tree34 =   (TTree*)file34->Get("tree");
// TTree *Tree35 =   (TTree*)file35->Get("tree");
TTree *Tree36 =   (TTree*)file36->Get("tree");
TTree *Tree37 =   (TTree*)file37->Get("tree");
TTree *Tree38 =   (TTree*)file38->Get("tree");
TTree *Tree39 =   (TTree*)file39->Get("tree");
TTree *Tree40 =   (TTree*)file40->Get("tree");
TTree *Tree41 =   (TTree*)file41->Get("tree");
TTree *Tree42 =   (TTree*)file42->Get("tree");
TTree *Tree43 =   (TTree*)file43->Get("tree");
TTree *Tree44 =   (TTree*)file44->Get("tree");
TTree *Tree45 =   (TTree*)file45->Get("tree");


// TTree *Tree04all =   (TTree*)file04->Get("allvents");
TTree *Tree05all =   (TTree*)file05->Get("allvents");
TTree *Tree06all =   (TTree*)file06->Get("allvents");
TTree *Tree07all =   (TTree*)file07->Get("allvents");
TTree *Tree09all =   (TTree*)file09->Get("allvents");
TTree *Tree10all =   (TTree*)file10->Get("allvents");
// TTree *Tree10_1all =   (TTree*)file10_1->Get("allvents");
// TTree *Tree11all =   (TTree*)file11->Get("allvents");
TTree *Tree12all =   (TTree*)file12->Get("allvents");
TTree *Tree13all =   (TTree*)file13->Get("allvents");
TTree *Tree14all =   (TTree*)file14->Get("allvents");
TTree *Tree15all =   (TTree*)file15->Get("allvents");
TTree *Tree16all =   (TTree*)file16->Get("allvents");
// TTree *Tree17all =   (TTree*)file17->Get("allvents");
TTree *Tree18all =   (TTree*)file18->Get("allvents");
TTree *Tree19all =   (TTree*)file19->Get("allvents");
TTree *Tree20all =   (TTree*)file20->Get("allvents");
TTree *Tree21all =   (TTree*)file21->Get("allvents");
TTree *Tree22all =   (TTree*)file22->Get("allvents");
// TTree *Tree23all =   (TTree*)file23->Get("allvents");
TTree *Tree24all =   (TTree*)file24->Get("allvents");
TTree *Tree25all =   (TTree*)file25->Get("allvents");
TTree *Tree26all =   (TTree*)file26->Get("allvents");
TTree *Tree27all =   (TTree*)file27->Get("allvents");
TTree *Tree28all =   (TTree*)file28->Get("allvents");
TTree *Tree29all =   (TTree*)file29->Get("allvents");
TTree *Tree30all =   (TTree*)file30->Get("allvents");
TTree *Tree31all =   (TTree*)file31->Get("allvents");
TTree *Tree32all =   (TTree*)file32->Get("allvents");
// TTree *Tree33all =   (TTree*)file33->Get("allvents");
TTree *Tree34all =   (TTree*)file34->Get("allvents");
// TTree *Tree35all =   (TTree*)file35->Get("allvents");
TTree *Tree36all =   (TTree*)file36->Get("allvents");
TTree *Tree37all =   (TTree*)file37->Get("allvents");
TTree *Tree38all =   (TTree*)file38->Get("allvents");
TTree *Tree39all =   (TTree*)file39->Get("allvents");
TTree *Tree40all =   (TTree*)file40->Get("allvents");
TTree *Tree41all =   (TTree*)file41->Get("allvents");
TTree *Tree42all =   (TTree*)file42->Get("allvents");
TTree *Tree43all =   (TTree*)file43->Get("allvents");
TTree *Tree44all =   (TTree*)file44->Get("allvents");
TTree *Tree45all =   (TTree*)file45->Get("allvents");

vector<TTree*> allTree = {
    Tree02,Tree03, Tree03_1, Tree03_2,/* Tree04,*/ Tree05, Tree06, Tree07, Tree09, /*Tree10_1, Tree11,*/ Tree12, Tree13, Tree14, Tree15, Tree16,/* Tree17,*/ Tree18, Tree19, Tree20, Tree21, Tree22,/* Tree23,*/ Tree24, Tree25, Tree26, Tree27, Tree28, Tree29, Tree30, Tree31, Tree32,/* Tree33,*/ Tree34, /*Tree35, */Tree36, Tree37, Tree38, Tree39, Tree40, Tree41, Tree42,  Tree43, Tree44, Tree45
};
vector<TTree*> allTreeall = {
    Tree02all,Tree03all, Tree03_1all, Tree03_2all, /*Tree04al,*/ Tree05all, Tree06all, Tree07all,  Tree09all,/* Tree10_1all, Tree11all, */Tree12all, Tree13all, Tree14all, Tree15all, Tree16all, /*Tree17all,*/ Tree18all, Tree19all, Tree20all, Tree21all, Tree22all,/* Tree23all, */Tree24all, Tree25all, Tree26all, Tree27all, Tree28all, Tree29all, Tree30all, Tree31all, Tree32all,/* Tree33all, */Tree34all, /*Tree35all,*/ Tree36all, Tree37all, Tree38all, Tree39all, Tree40all, Tree41all, Tree42all,  Tree43all, Tree44all, Tree45all
};



float separationPower(TH1D* h1, TH1D* h2);

int SigSF = 1;
//float LUMI  = 41500.0; //float LUMI = 36733; //36.773 /fb
float LUMI = 35900; //fb
//?where to get the more precise LUMI?
//SIGNAL

//double wTTTT = (SigSF**0.009103);///TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root:  Positive:1709406  Negtive:704054
double wTTTT_sigma = SigSF*0.01197;//TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root 
//tt
// double wTTJets_sigma = 746.7;//746.7 //TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root
double wTT_sigma     = 746.7  ; //TT_TuneCUETP8M2T4_13TeV-powheg-pythia8.root 
double wTTTo2L2Nu    = 373.;
double wTTToHadronic = 367.;
double wTTToSemiLeptonic      = 90.6;

double wTTGJets_sigma = 3.773;  ; //TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root
double wttZJets_sigma = 0.6559 ;      //Special care is taken when scaling the ttZ background to the cross-section= /(-) //ttZJets_13TeV_madgraphMLM-pythia8.root 
double wttWJets_sigma = 0.2014;  ; //  ttWJets_13TeV_madgraphMLM.root 
double wttH_sigma= 0.3372;  ; //ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root 

//diboson and triboson an w_sigma/z+jets
double wWZ_sigma= 2.343;  ;//WZ_TuneCUETP8M1_13TeV-pythia8.root 
double wWW_sigma= 6.430;//?something wrong with ntuple
double wWWTo2L2Nu_sigma = 0.1697;   ;//r WWTo2L2Nu_DoubleScattering_13TeV-pythia8.root 
double wWpWpJJ_sigma= 0.05390;  ;//WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root 
double wZZ_sigma  = 1.016;  ;//ZZ_TuneCUETP8M1_13TeV-pythia8.root 
double wWGJets_sigma = 1.269;  ;//WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root 
double wZGJetsToLLG_sigma = 0.1319;  ;// ZGJetsToLLG_EW_LO_13TeV-sherpa.root 
//
double wWWW_sigma= 0.2086;  ;// WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
double wWWZ_sigma= 0.1651;  ;//WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
double wWWG_sigma = 0.2147;  ; //WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
double wZZZ_sigma= 0.01398;  ;//ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
double wWZZ_sigma= 0.05565;  ; //WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
double wWZG_sigma= 0.04123;  ;// WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
//double wWGGJets_sigma = 1.711;//
double wWGG_sigma =1.819;   ;// WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root 
double wZGGJets_sigma= 0.3717;  ;//ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8.root 


double wWJetsToLNu_sigma= 50300 ;  ;//WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root
//?missing ZJets?= 
//Drell-Yan
double wDYJetsToTauTau_sigma= 1983;  ;//DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1.root 
//
//single top
double wtZq_ll_sigma= 0.07358;  ;//tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8.root 
//double wtZq_nunu_sigma= ;// tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1.root Positive:630623  Negtive:368977  ;//
//?
double wST_tW_antitop_sigma= 38.06;  ;//ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root 
double wST_tW_top_sigma= 38.09;  ;//ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root 
double wTGJets_sigma= 2.967;  ;//TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root 
double wTHW_sigma= 0.1467;  ;//THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8.root 
double wTHQ_sigma= 0.8816;  ;//THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1.root 
//H 
double wVHToNonbb_sigma= 2.137;  ;//VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8.root 
double wZHToTauTau_sigma= 0.7524;  ;// ZHToTauTau_M125_13TeV_powheg_pythia8.root 
double wZH_HToBB_ZToLL_sigma= 0.07523;  ;//ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8.root 
double wGluGluHToZZTo4L_sigma= 2.999;  ;//GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8.root 
double wGluGluHToBB_sigma= 32.10;  ;//GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.root 
double wGluGluHToGG_sigma= 31.98;  ;//GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root 
double wGluGluHToMuMu_sigma= 29.99;  ;//GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root 

double wGluGluHToTauTau_sigma= 30.52;  ;//GluGluHToTauTau_M125_13TeV_powheg_pythia8.root 
double wGluGluHToWWTo2L2Nu_sigma= 30.52;  ;//GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8.root 
double wGluGluHToWWToLNuQQ_sigma= 29.99;  ;//GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8.root 
//double wVBFHToWWToLNuQQ_sigma= 3.769//
double wVBFHToWWTo2L2Nu_sigma= 3.769;  ;//VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8.root 
//??very different from ttH
//double wVBFHToWWTo2L2Nu_sigma= ;
//double wVBFHToTauTau_sigma= 0.237;// VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root Positive:996835  Negtive:765  ;
double wVBFHToMuMu_sigma= 0.000823;  ;//VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root 
double wVBFHToGG_sigma= 3.992;  ;//VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2.root 
// double wVBFHToBB= (LUMI*)/(-)//
//double wVBF_HToZZTo4L= (LUMI*3.769)/(-)
//HH count as minor
//minor
vector<double> allSigmas {
    wTTTT_sigma, //0
    // wTT_sigma,
    wTTTo2L2Nu, wTTToHadronic, wTTToSemiLeptonic,
    wTTGJets_sigma, wttZJets_sigma, wttWJets_sigma, wttH_sigma, //5
    wWZ_sigma, wWW_sigma, /*wWWTo2L2Nu_sigma, wWpWpJJ_sigma,*/ wZZ_sigma, wWGJets_sigma, wZGJetsToLLG_sigma, 
    wWWW_sigma, wWWZ_sigma, wWWG_sigma, wZZZ_sigma, wWZZ_sigma, wWZG_sigma, wWGG_sigma, wZGGJets_sigma, 
    wWJetsToLNu_sigma, wDYJetsToTauTau_sigma, 
    wtZq_ll_sigma, wST_tW_antitop_sigma, wST_tW_top_sigma, wTGJets_sigma, wTHW_sigma, wTHQ_sigma, 
    wVHToNonbb_sigma, wZHToTauTau_sigma, wZH_HToBB_ZToLL_sigma, wGluGluHToZZTo4L_sigma, wGluGluHToBB_sigma, wGluGluHToGG_sigma, wGluGluHToMuMu_sigma, wGluGluHToTauTau_sigma, wGluGluHToWWTo2L2Nu_sigma, wGluGluHToWWToLNuQQ_sigma, wVBFHToWWTo2L2Nu_sigma, /*wVBFHToTauTau_sigma, */wVBFHToMuMu_sigma, wVBFHToGG_sigma
};





                                                   

