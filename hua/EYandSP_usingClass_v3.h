/**
 * File              : EYandSP_usingClass_v3.h
 * Author            : Huiling Hua <huahl@ihep.ac.cn>
 * Date              : 03.10.2021
 * Last Modified Date: 03.10.2021
 * Last Modified By  : Huiling Hua <huahl@ihep.ac.cn>
 */
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TROOT.h"
#include "TMath.h"
#include "TString.h"
#include "TCut.h"
#include "TPRegexp.h"




#include "Process_Class.C"
// #include "Process_Class.h"

// if (!TClass::GetDict("Process_Class")) {
    //   gROOT->ProcessLine(".L Process_Class.C++");
// }

// const TString baseDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_postVFP/v1_fromV8/";
const TString baseDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/v1_fromV8/";
const TString baseDir_2016post = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_postVFP/v1_fromV8/";

//Double_t LUMI  = 41500.0; //Double_t LUMI = 36733; //36.773 /fb-1
const Double_t LUMI = 35900; //pb-1
const Double_t gLUMI_2016preVFP = 19520;//19.52 fb
const Double_t gLUMI_2016postVFP = 16810;
//?where to get the more precise LUMI?
std::map<TString, Double_t> lumiMap = {
    {"2016preVFP", 19520},
    {"2016postVFP", 16810},
};



const TCut MetFilters = "Flag_goodVertices==1 && Flag_globalSuperTightHalo2016Filter==1 && Flag_HBHENoiseFilter==1 && Flag_HBHENoiseIsoFilter==1 && Flag_EcalDeadCellTriggerPrimitiveFilter==1 && Flag_BadPFMuonFilter==1";
// const TCut trigger = "HLT_PFHT450_SixJet40_BTagCSV_p056==1 || HLT_PFHT400_SixJet30_DoubleBTagCSV_p056==1";

//???we can do a mapping of channel number with cut here
const TCut ES1tau0l = "tausT_number==1 && leptonsMVAT_number==0 &&  jets_number>=8 && bjetsM_num>=2 && jets_HT>400" ;
const TCut ES1tau1e = "tausT_number==1 && elesMVAT_number==1 && leptonsMVAT_number==1 &&  jets_number>=6 && bjetsM_num>=2 && jets_HT>400" ;
const TCut ES1tau1m = "tausT_number==1 && muonsT_number==1 && leptonsMVAT_number==1&& jets_number>=6 && bjetsM_num>=2 && jets_HT>400" ;
const TCut ES1tau2os = "tausT_number==1 && leptonsMVAT_number==2 && leptonsMVAT_2OS==1  &&  jets_number>=4 && bjetsM_num>=2 && jets_HT>400" ;
const TCut ES1tau2ss = "tausT_number==1 && leptonsMVAT_number==2 && leptonsMVAT_2SS==1 &&  jets_number>=4 && bjetsM_num>=2 && jets_HT>400" ;
const TCut ES1tau3l = "tausT_number==1 && leptonsMVAT_number==3 &&  jets_number>=2 && bjetsM_num>=2 && jets_HT>400" ;
const TCut ES2tau0l = "tausT_number==2 && leptonsMVAT_number==0 &&  jets_number>=6 && bjetsM_num>=2 && jets_HT>400" ;
const TCut ES2tau1e = "tausT_number==2 && elesMVAT_number==1 && leptonsMVAT_number==1 && jets_number>=4 && bjetsM_num>=2 && jets_HT>400" ;
const TCut ES2tau1m = "tausT_number==2 && muonsT_number==1 && leptonsMVAT_number==1 &&  jets_number>=4 && bjetsM_num>=2 && jets_HT>400" ;
const TCut ES2tau2os = "tausT_number==2 && leptonsMVAT_number==2 && leptonsMVAT_2OS==1  && jets_number>=2 && bjetsM_num>=2 && jets_HT>400" ;
const TCut ES2tau2ss = "tausT_number==2 && leptonsMVAT_number==2 && leptonsMVAT_2SS==1 &&  jets_number>=2 && bjetsM_num>=2 && jets_HT>400" ;

const TCut ES1tau1l = ES1tau1e||ES1tau1m;
const TCut ES1tau2l = "tausT_number==1 && leptonsMVAT_number==2 &&  jets_number>=4 && bjetsM_num>=2 && jets_HT>400" ;
const TCut ES2tau1l = "tausT_number==2 && leptonsMVAT_number==1 && jets_number>=4 && bjetsM_num>=2 && jets_HT>400" ;
const TCut ES2tau2l = "tausT_number==2 && leptonsMVAT_number==2 &&  jets_number>=2 && bjetsM_num>=2 && jets_HT>400" ;
const TCut ES2tauXl = ES2tau0l||ES2tau1l||ES2tau2l;
const TCut weight = "EVENT_genWeight*EVENT_prefireWeight*PUWeight*btagEfficiency_weight*HLTefficiency_weight";
const TCut basicWeight = "EVENT_genWeight*EVENT_prefireWeight*PUWeight";

std::map<TString, TCut> channelCutMap = {
    {"1tau0l", ES1tau0l},
    {"1tau1e", ES1tau1e},
    {"1tau1m", ES1tau1m},
    {"1tau1l", ES1tau1l},
    {"1tau2os", ES1tau2os},
    {"1tau2ss", ES1tau2ss},
    {"1tau2l", ES1tau2l},
    {"2tau0l", ES2tau0l},
    {"2tau1e", ES2tau1e},
    {"2tau1m", ES2tau1m},
    {"2tau1l", ES2tau1l},
    {"2tau2l", ES2tau2l},
    {"2tauXl", ES2tauXl}, 
};


std::map<TString, Double_t> crossSectionMap = {
    {"tttt", 0.01197},
    {"ttbar_2l", 88.29},
    {"ttbar_0l", 377.96},
    {"ttbar_1l", 365.34},
} ;



Process TTTT{ baseDir+"tttt.root", crossSectionMap["tttt"]};
Process TTTo2L2Nu{ baseDir+"ttbar_2l.root", crossSectionMap["ttbar_2l"]};
Process TTToHadronic{ baseDir+"ttbar_0l.root", crossSectionMap["ttbar_0l"]};
Process TTToSemiLeptonic{ baseDir+"ttbar_1l.root", crossSectionMap["ttbar_1l"]};
Process TTGJets{baseDir+"ttG.root", 4.62 };//3.773
Process ttZJets{baseDir+"ttZ.root",  0.783};//0.6559
Process ttWJets{baseDir+"ttW.root", 0.611 };//0.2014 changed to 611
Process ttH_bb{baseDir + "ttH_bb.root", 0.2897}; // 0.2897
Process ttH_nonbb{baseDir + "ttH_nonbb.root", 0.209}; // 0.209
// VV
Process WZ{baseDir+"wz.root", 2.343 };
Process WW{baseDir+"ww.root", 6.430 };
Process ZZ{baseDir+"zz.root", 1.016 };//ZZ
// Process WGJets{baseDir+".root", 1.269 };//???
// Process ZGJetsToLLG{baseDir+".root", 0.1319 };//???
//VVV
// Process WWW{baseDir+".root", 0.2086 };//???
// Process WWZ{baseDir+".root", 0.1651 };//???
// Process WWG{baseDir+".root", 0.0435  };//???
// Process ZZZ{baseDir+".root", 0.01398 };//???
// Process WZZ{baseDir+".root", 0.05565 };//???
// Process WZG{baseDir+".root", 0.04123 };//???
// Process WGG{baseDir+".root", 1.819 };//???
// Process ZGGJets{baseDir+".root", 0.3717 };//???
//
// Process WJetsToLNu{baseDir+".root", 50300 };//???
// Process DYJetsToTauTau{baseDir+".root", 1983 };//???
//Single Top
Process tZq_ll{baseDir+"st_tZq.root", 0.07358 };
// Process tZq_nunu{baseDir+".root", 0.1379 };//???
Process ST_tW_antitop{baseDir+"st_tW_antitop.root", 35.85 };//38.06
Process ST_tW_top{baseDir+"st_tW_top.root", 35.85 };//38.09
//TX
// Process TGJets{baseDir+".root", 2.967 };//???
// // Process THW{baseDir+".root", 0.1467 };//???
// Process THQ{baseDir+".root", 0.8816 };//???

//QCD
Process QCD_HT50to100{baseDir + "qcd_50to100.root", 2.466e+08}; // 50-100  //2.466e+08 +- 2.190e+05 pb
Process QCD_HT100to200{baseDir + "qcd_100to200.root", 2.801e+07}; // 100to200  //2.801e+07 +- 2.608e+04 pb
Process QCD_HT200to300{baseDir+"qcd_200to300.root", 1.721e+6 }; // 1.710e+06 +- 1.626e+03 pb
Process QCD_HT300to500{baseDir+"qcd_300to500.root",  3.479e+05}; // 3.473e+05 +- 3.327e+02 pb
Process QCD_HT500to700{baseDir+"qcd_500to700.root",  3.206e+04}; // 3.220e+04 +- 3.100e+01 pb
Process QCD_HT700to1000{baseDir+"qcd_700to1000.root",  6.827e+03};  // 6.839e+03 +- 6.602e+00 pb
Process QCD_HT1000to1500{baseDir+"qcd_1000to1500.root",  1.207e+03}; // 1.207e+03 +- 1.167e+00 pb
Process QCD_HT1500to2000{baseDir+"qcd_1500to2000.root",  1.20e+02}; // 1.201e+02 +- 1.160e-01 pb
Process QCD_HT2000toInf{baseDir+"qcd_2000toInf.root",  2.525e+01 }; // 2.524e+01 +- 2.436e-02 pb




std::vector<Process> allProcesses = {
    TTTT, //0
    TTTo2L2Nu, TTToHadronic, TTToSemiLeptonic, //3
    TTGJets, ttZJets,ttWJets, ttH_bb, ttH_nonbb, //8
    WZ, WW, ZZ,  //11
    tZq_ll,  ST_tW_antitop, ST_tW_top,//14
    QCD_HT50to100, QCD_HT100to200, QCD_HT200to300, QCD_HT300to500, QCD_HT500to700, QCD_HT700to1000, QCD_HT1000to1500, QCD_HT1500to2000, QCD_HT2000toInf,//23
};


Process TTTT_2016post{ baseDir_2016post+"tttt.root", crossSectionMap["tttt"]};
Process TTTo2L2Nu_2016post{ baseDir_2016post+"ttbar_2l.root", crossSectionMap["ttbar_2l"]};
Process TTToHadronic_2016post{ baseDir_2016post+"ttbar_0l.root", crossSectionMap["ttbar_0l"]};
Process TTToSemiLeptonic_2016post{ baseDir_2016post+"ttbar_1l.root", crossSectionMap["ttbar_1l"]};
Process TTGJets_2016post{ baseDir_2016post+"ttG.root", 4.62 };//3.773
Process ttZJets_2016post{ baseDir_2016post+"ttZ.root",  0.783};//0.6559
Process ttWJets_2016post{ baseDir_2016post+"ttW.root", 0.611 };//0.2014 changed to 611
Process ttH_bb_2016post{ baseDir_2016post + "ttH_bb.root", 0.2897}; // 0.2897
Process ttH_nonbb_2016post{ baseDir_2016post + "ttH_nonbb.root", 0.209}; // 0.209
// VV
Process WZ_2016post{ baseDir_2016post+"wz.root", 2.343 };
Process WW_2016post{ baseDir_2016post+"ww.root", 6.430 };
Process ZZ_2016post{ baseDir_2016post+"zz.root", 1.016 };//ZZ
//Single Top
Process tZq_ll_2016post{ baseDir_2016post+"st_tZq.root", 0.07358 };
// Process tZq_nunu_2016post{ baseDir_2016post+".root", 0.1379 };//???
Process ST_tW_antitop_2016post{ baseDir_2016post+"st_tW_antitop.root", 35.85 };//38.06
Process ST_tW_top_2016post{ baseDir_2016post+"st_tW_top.root", 35.85 };//38.09

//QCD
Process QCD_HT50to100_2016post{ baseDir_2016post + "qcd_50to100.root", 2.466e+08}; // 50-100  //2.466e+08 +- 2.190e+05 pb
Process QCD_HT100to200_2016post{ baseDir_2016post + "qcd_100to200.root", 2.801e+07}; // 100to200  //2.801e+07 +- 2.608e+04 pb
Process QCD_HT200to300_2016post{ baseDir_2016post+"qcd_200to300.root", 1.721e+6 }; // 1.710e+06 +- 1.626e+03 pb
Process QCD_HT300to500_2016post{ baseDir_2016post+"qcd_300to500.root",  3.479e+05}; // 3.473e+05 +- 3.327e+02 pb
Process QCD_HT500to700_2016post{ baseDir_2016post+"qcd_500to700.root",  3.206e+04}; // 3.220e+04 +- 3.100e+01 pb
Process QCD_HT700to1000_2016post{ baseDir_2016post+"qcd_700to1000.root",  6.827e+03};  // 6.839e+03 +- 6.602e+00 pb
Process QCD_HT1000to1500_2016post{ baseDir_2016post+"qcd_1000to1500.root",  1.207e+03}; // 1.207e+03 +- 1.167e+00 pb
Process QCD_HT1500to2000_2016post{ baseDir_2016post+"qcd_1500to2000.root",  1.20e+02}; // 1.201e+02 +- 1.160e-01 pb
Process QCD_HT2000toInf_2016post{ baseDir_2016post+"qcd_2000toInf.root",  2.525e+01 }; // 2.524e+01 +- 2.436e-02 pb

std::vector<Process> allProcesses_2016post = {
    TTTT_2016post, //0
    TTTo2L2Nu_2016post, TTToHadronic_2016post, TTToSemiLeptonic_2016post, //3
    TTGJets_2016post, ttZJets_2016post,ttWJets_2016post, ttH_bb_2016post, ttH_nonbb_2016post, //8
    WZ_2016post, WW_2016post, ZZ_2016post,  //11
    tZq_ll_2016post,  ST_tW_antitop_2016post, ST_tW_top_2016post,//14
    QCD_HT50to100_2016post, QCD_HT100to200_2016post, QCD_HT200to300_2016post, QCD_HT300to500_2016post, QCD_HT500to700_2016post, QCD_HT700to1000_2016post, QCD_HT1000to1500_2016post, QCD_HT1500to2000_2016post, QCD_HT2000toInf_2016post,//23
};





/*
Process TTTT{ baseDir+"TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn.root", 0.01197};
Process TTTo2L2Nu{ baseDir+ "TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8.root", 88.29 };//90.6->
Process TTToHadronic(baseDir+"TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8.root", 377.96 );//367.
Process TTToSemiLeptonic(baseDir+"TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root", 365.34);//367.

Process TTGJets(baseDir+"TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root", 4.62 );//3.773
Process ttZJets(baseDir+"ttZJets_13TeV_madgraphMLM-pythia8.root",  0.783);//0.6559
Process ttWJets(baseDir+"ttWJets_13TeV_madgraphMLM.root", 0.611 );//0.2014 changed to 611
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
Process ST_tW_antitop(baseDir+"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root", 35.85 );//38.06
Process ST_tW_top(baseDir+"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root", 35.85 );//38.09
//TX
Process TGJets(baseDir+"TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root", 2.967 );
Process THW(baseDir+"THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8.root", 0.1467 );
Process THQ(baseDir+"THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1.root", 0.8816 );

//QCD
//50-100  //2.466e+08 +- 2.190e+05 pb
//100to200  //2.801e+07 +- 2.608e+04 pb
Process QCD_HT200to300(baseDir+"QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root", 1.721e+6 ); // 1.710e+06 +- 1.626e+03 pb
Process QCD_HT300to500(baseDir+"QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",  3.479e+05); // 3.473e+05 +- 3.327e+02 pb
Process QCD_HT500to700(baseDir+"QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",  3.206e+04); // 3.220e+04 +- 3.100e+01 pb
Process QCD_HT700to1000(baseDir+"QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",  6.827e+03);  // 6.839e+03 +- 6.602e+00 pb
Process QCD_HT1000to1500(baseDir+"QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",  1.207e+03); // 1.207e+03 +- 1.167e+00 pb
Process QCD_HT1500to2000(baseDir+"QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",  1.20e+02); // 1.201e+02 +- 1.160e-01 pb
Process QCD_HT2000toInf(baseDir+"QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",  2.525e+01 ); // 2.524e+01 +- 2.436e-02 pb
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

std::vector<Process> allProcesses = {
    TTTT, //0
    TTTo2L2Nu, TTToHadronic, TTToSemiLeptonic, //3
    TTGJets, ttZJets,ttWJets, ttH, //7
    WZ, WW, ZZ, WGJets, ZGJetsToLLG, //12
    WWW, WWZ, WWG, ZZZ, WZZ, WZG, WGG, ZGGJets,//20
    WJetsToLNu, DYJetsToTauTau,//22
    tZq_ll, tZq_nunu, ST_tW_antitop, ST_tW_top,//26
    TGJets, THW, THQ, //29
    QCD_HT200to300, QCD_HT300to500, QCD_HT500to700, QCD_HT700to1000, QCD_HT1000to1500, QCD_HT1500to2000, QCD_HT2000toInf,//36
};

*/

TH1D* getBackHist(  std::vector<Process>& allProcesses,  const TCut cut, const TCut weight ){
    TH1D* bg = new TH1D( "bg", "bg", 40, 0, 40);
    for(UInt_t j = 1; j < allProcesses.size(); j++){
        if(j > 0) bg->Add( allProcesses[j].getChannelHist( cut, weight) , LUMI*allProcesses[j].getScale() );
    }
    return bg;
}

TH1D* addHistChannel( const TCut cut, const TCut weight, TString branchName, const Int_t binNum, const Double_t binMin, const Double_t binMax, Int_t fromProcess, Int_t toProcess, TString histName  ){
    TH1D* addedHist = new TH1D( histName, branchName, binNum, binMin, binMax );
    // addedHist->ResetStats();
    TH1D::SetDefaultSumw2();
    for(UInt_t j = fromProcess; j < toProcess; j++){
        // addedHist->Add( allProcesses[j].getChannelHist(cut,weight, branchName, binNum, binMin, binMax),  allProcesses[j].getScale() );
        //???
        TH1D* temp = allProcesses[j].getChannelHist(cut,weight, branchName, binNum, binMin, binMax);
        temp->Scale( allProcesses[j].getScale() );
        addedHist->Add( temp,1   );
        delete temp;

    }
    // addedHist->Print();
    return addedHist;

}

void getBgsAndSignalHist( std::vector<TH1D*> &groupedBGsAndSignal , const TCut channelCut, const TCut weight, const TString branch, const Int_t binNum, const Double_t binMin, const Double_t binMax ){

    TH1D*  TTTT = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 0, 1, "TTTT_"+branch );
    TH1D* TT = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 1, 4, "TT_"+branch);
    TH1D* TTX = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 4, 8, "TTX_"+branch );
    TH1D* VV = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 8, 13, "VV_"+branch );
    TH1D* VVV = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 13, 21, "VVV_"+branch );
    TH1D* WJets = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 21, 22, "WJets_"+branch );
    TH1D* DYJets = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 22, 23, "DYJets_"+branch );
    TH1D*  SingleTop = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 23, 27, "SingleTop_"+branch );
    TH1D*  TX= addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 27, 30, "TX_"+branch );
    TH1D*  QCD = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 30, 36, "QCD_"+branch);

    TH1D*  allBg = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 1, 36, "allBg_"+branch);

    groupedBGsAndSignal.push_back( TTTT );
    groupedBGsAndSignal.push_back( TT );
    groupedBGsAndSignal.push_back( TTX );
    groupedBGsAndSignal.push_back( VV );
    groupedBGsAndSignal.push_back( VVV );
    groupedBGsAndSignal.push_back( WJets );
    groupedBGsAndSignal.push_back( DYJets );
    groupedBGsAndSignal.push_back( SingleTop );
    groupedBGsAndSignal.push_back(  TX );
    groupedBGsAndSignal.push_back( QCD );
    groupedBGsAndSignal.push_back( allBg );

    // delete TTTT, TT;
}
void getBgsAndSignalHist_Nano( std::vector<TH1D*> &groupedBGsAndSignal , const TCut channelCut, const TString channelName, const TCut weight, const TString branch, const Int_t binNum, const Double_t binMin, const Double_t binMax ){

    TH1D*  TTTT = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 0, 1, channelName +"_TTTT_"+branch );
    TH1D* TT = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 1, 4, channelName +"_TT_"+branch);
    TH1D* TTX = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 4, 9, channelName +"_TTX_"+branch );
    TH1D* VV = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 9, 12, channelName + "_VV_"+branch );
    TH1D*  SingleTop = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 12, 15, channelName + "_SingleTop_"+branch );
    TH1D*  QCD = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 15, 24, channelName +"_QCD_"+branch);

    TH1D*  allBg = addHistChannel( channelCut, weight, branch, binNum, binMin, binMax, 1, 24, channelName +"_allBg_"+branch);

    groupedBGsAndSignal.push_back( TTTT );
    groupedBGsAndSignal.push_back( TT );
    groupedBGsAndSignal.push_back( TTX );
    groupedBGsAndSignal.push_back( VV );
    groupedBGsAndSignal.push_back( SingleTop );
    groupedBGsAndSignal.push_back( QCD );
    groupedBGsAndSignal.push_back( allBg );

}



Double_t getAllBgEntries( const TCut cut, const TCut weight ){
    Double_t bgEntries = 0.0;
    for(UInt_t j = 1; j < allProcesses.size(); j++){
        bgEntries += allProcesses[j].getChannelHist( cut, weight)->GetEntries();
    }
    return bgEntries;
}

                                                   

