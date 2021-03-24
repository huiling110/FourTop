#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"


TString baseDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forMVA/v4addToptagger_fromv35/";
// TString baseDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forMVA/check_fromv34/";
// TString baseDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forMVA/test/";
// Int_t SigSF = 1;
//Double_t LUMI  = 41500.0; //Double_t LUMI = 36733; //36.773 /fb
Double_t LUMI = 35900; //fb
//?where to get the more precise LUMI?
Double_t separationPower(TH1D* h1, TH1D* h2);


class Process
{
    private:
        TString m_fileName;
        Double_t m_sigma;
        TFile* m_file;
        TTree *eventTree;
        TTree *alleventTree;
    public:
        Process( TString fileName, Double_t sigma)
            :m_fileName{ fileName}, m_sigma{ sigma}
        {
            m_file = TFile::Open( m_fileName);
            eventTree = (TTree*)m_file->Get( "newtree");
            alleventTree = (TTree*)m_file->Get("allevents");
        }

        TTree* getEventTree(){
            // return (TTree*)m_file->Get( "newtree");
            return eventTree;
        }
        // TTree* getAllEventTree(){
            // return alleventTree;
        // }
        Double_t getSigma(){
            return m_sigma;
        }
        Double_t getGenWeightSum(){
           TH1D* h_genWeight = new TH1D( "genWeight", "genWeight", 100, -100., 100.);
           alleventTree->Project( "genWeight", "genWeight_allEvents");
           h_genWeight->StatOverflows(kTRUE);
           return h_genWeight->GetMean() * h_genWeight->GetEntries();
        }
};

Process TTTT{ baseDir+"TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn.root", 0.01197};
Process TTTo2L2Nu{ baseDir+ "TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8.root", 90.6 };
Process TTToHadronic(baseDir+"TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8.root", 367. );
Process TTToSemiLeptonic(baseDir+"TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root", 367.);

Process TTGJets(baseDir+"TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root", 3.773 );//TTGJets
Process ttZJets(baseDir+"ttZJets_13TeV_madgraphMLM-pythia8.root", 0.6559);//???something with the files
Process ttWJets(baseDir+"ttWJets_13TeV_madgraphMLM.root", 0.2014 );
Process ttH(baseDir+"ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root", 0.3372 );//ttH
//VV
Process WZ(baseDir+"WZ_TuneCUETP8M1_13TeV-pythia8.root", 2.343 );
Process WW(baseDir+"WW_TuneCUETP8M1_13TeV-pythia8.root", 6.430 );
Process ZZ(baseDir+"ZZ_TuneCUETP8M1_13TeV-pythia8.root", 1.016 );//ZZ
Process WGJets(baseDir+"WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root", 1.269 );//
Process ZGJetsToLLG(baseDir+"ZGJetsToLLG_EW_LO_13TeV-sherpa.root", 0.1319 );//
//VVV
Process WWW(baseDir+"WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root", 0.2086 );//
Process WWZ(baseDir+"WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root", 0.1651 );//
Process WWG(baseDir+"WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root", 0.0435  );//from TTH
Process ZZZ(baseDir+"ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root", 0.01398 );//
Process WZZ(baseDir+"WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root", 0.05565 );//
Process WZG(baseDir+"WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root", 0.04123 );//
Process WGG(baseDir+"WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root", 1.819 );
Process ZGGJets(baseDir+"ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8.root", 0.3717 );
//
Process WJetsToLNu(baseDir+"WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root", 50300 );//WJets
Process DYJetsToTauTau(baseDir+"DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1.root", 1983 );
//Single Top
Process tZq_ll(baseDir+"tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8.root", 0.07358 );
Process tZq_nunu(baseDir+"tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1.root", 0.1379 );//pb
Process ST_tW_antitop(baseDir+"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root", 38.06 );
Process ST_tW_top(baseDir+"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root", 38.09 );
//TX
Process TGJets(baseDir+"TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root", 2.967 );
Process THW(baseDir+"THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8.root", 0.1467 );
Process THQ(baseDir+"THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1.root", 0.8816 );

//QCD
//50-100  //2.466e+08 +- 2.190e+05 pb
//100to200  //2.801e+07 +- 2.608e+04 pb
Process QCD_HT200to300(baseDir+"QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root", 1.710e+3 ); // 1.710e+06 +- 1.626e+03 pb
Process QCD_HT300to500(baseDir+"QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",  3.473e+02); // 3.473e+05 +- 3.327e+02 pb
Process QCD_HT500to700(baseDir+"QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",  3.220e+01); // 3.220e+04 +- 3.100e+01 pb
Process QCD_HT700to1000(baseDir+"QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",  6.839e+0);  // 6.839e+03 +- 6.602e+00 pb
Process QCD_HT1000to1500(baseDir+"QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",  1.207e+0); // 1.207e+03 +- 1.167e+00 pb
Process QCD_HT1500to2000(baseDir+"QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",  0.1201); // 1.201e+02 +- 1.160e-01 pb
Process QCD_HT2000toInf(baseDir+"QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",  0.02524); // 2.524e+01 +- 2.436e-02 pb
//H
// Process VHToNonbb(baseDir+"VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8.root", 2.137 );
// Process ZHToTauTau(baseDir+"ZHToTauTau_M125_13TeV_powheg_pythia8.root", 0.7524 );
// Process ZH_HToBB_ZToLL(baseDir+"ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8.root", 0.07523 );
// Process GluGluHToZZTo4L(baseDir+"GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8.root", 2.999 );
// Process GluGluHToBB(baseDir+"GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.root", 32.10 );
// Process GluGluHToGG(baseDir+"GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root", 31.98 );
// Process GluGluHToMuMu(baseDir+"GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root", 29.99 );
// Process GluGluHToTauTau(baseDir+"GluGluHToTauTau_M125_13TeV_powheg_pythia8.root", 30.52 );
// Process GluGluHToWWTo2L2Nu(baseDir+"GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8.root", 30.52 );
// Process GluGluHToWWToLNuQQ(baseDir+"GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8.root", 29.99 );
// Process VBFHToWWTo2L2Nu(baseDir+"VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8.root", 3.769  );//??very different from ttH//no newtree
// Process VBFHToTauTau(baseDir+"VBFHToTauTau_M125_13TeV_powheg_pythia8.root", 0.237 );
// Process VBFHToMuMu(baseDir+"VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root", 0.000823 );
// Process VBFHToGG(baseDir+"VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2.root", 3.992 );
vector<Process> allProcesses = {
    TTTT, //0
    TTTo2L2Nu, TTToHadronic, TTToSemiLeptonic, //3
    TTGJets, ttZJets,ttWJets, ttH, //7
    WZ, WW, ZZ, WGJets, ZGJetsToLLG, //12
    WWW, WWZ, WWG, ZZZ, WZZ, WZG, WGG, ZGGJets,//20
    WJetsToLNu, DYJetsToTauTau,//22
    tZq_ll, tZq_nunu, ST_tW_antitop, ST_tW_top,//26
    TGJets, THW, THQ, //29
    QCD_HT200to300, QCD_HT300to500, QCD_HT500to700, QCD_HT700to1000, QCD_HT1000to1500, QCD_HT1500to2000, QCD_HT2000toInf,
    // VHToNonbb, [>ZHToTauTau,*/ ZH_HToBB_ZToLL,[> GluGluHToZZTo4L,*/ /*GluGluHToBB.<] GluGluHToGG, GluGluHToMuMu, GluGluHToTauTau, GluGluHToWWTo2L2Nu, GluGluHToWWToLNuQQ,/* VBFHToWWTo2L2Nu, VBFHToTauTau, <]VBFHToMuMu, VBFHToGG,
};



                                                   

