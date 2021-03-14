#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"


int SigSF = 1;
//float LUMI  = 41500.0; //float LUMI = 36733; //36.773 /fb
float LUMI = 35900; //fb
//?where to get the more precise LUMI?
float separationPower(TH1D* h1, TH1D* h2);
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
        Double_t getSigma(){
            return m_sigma;
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



                                                   

