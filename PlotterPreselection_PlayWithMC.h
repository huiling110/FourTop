#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"

//void MakeHistos(char CUT[1000],const char *plot,int BIN,float MIN,float MAX,int JETSyst,
//		/*TH1F* &data_func,*/ TH1F* &background_func,TH1F* &TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_func,TH1F* &TTGJets_func,TH1F* &ttZJets_13TeV_madgraphMLM-pythia8.root_func,TH1F* &ttWJets_13TeV_madgraphMLM_func,TH1F* &ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root_func,TH1F* &ttbb_4FS_ckm_amcatnlo_madspin_pythia8_func,TH1F* &WZ_TuneCUETP8M1_13TeV-pythia8_func,
//		TH1F* &WW_TuneCUETP8M1_13TeV-pythia8_func,TH1F* &TTWJets_func,TH1F* &TTZ_func, TH1F* &WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_func,
//		TH1F* &TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8func);

void GetHisto(char CUT[1000], TTree *Tree, TH1F* & histo, const char *plot, int BIN, float MIN, float MAX);
void GetHisto_noBoundry(char CUT[1000], TTree *Tree, TH1F* & histo, const char *plot, int BIN, float MIN, float MAX);
float separationPower(TH1F* h1, TH1F* h2);

void MakeHistoErrors(int m, TH1F* &histo_SR, TH1F* histo_P1, TH1F* histo_P2, TH1F* histo_F1, TH1F* histo_F2, TH1F* histo_B1, TH1F* histo_B2, TH1F* histo_Z1, TH1F* histo_Z2, TH1F* histo_W1, TH1F* histo_W2, TH1F* histo_T1, TH1F* histo_T2, TH1F* histo_J1, TH1F* histo_J2, TH1F* histo_J3, TH1F* histo_J4, TH1F* histo_qcd1, TH1F* histo_qcd2, TH1F* histo_pdf1, TH1F* histo_pdf2, TH1F* histo_TR1, TH1F* histo_TR2);

void CloneHistos();


void MakeHistos(char CUT[1000],const char *plot,int BIN,float MIN,float MAX,int JETSyst,
                       /* TH1F* &data_func,*/TH1F* &background_func,TH1F* &TTJets_func,TH1F* &TTGJets_func,TH1F* &ttZJets_func,  TH1F*  &ttWJets_func,TH1F*       &ttH_func,TH1F* &ttbb_func,TH1F* &WZ_func,
                                       /* TH1F* &WW_func,*/TH1F* &WWTo2L2Nu_func, TH1F* &WpWpJJ_func,TH1F* &ZZ_func,TH1F* &WGJets_func, TH1F* &ZGJetsToLLG_func, TH1F* &WWW_func,TH1F* &WWZ_func,TH1F* &WWG_func,TH1F* &ZZZ_func,TH1F* &WZZ_func,TH1F* &WZG_func, TH1F* &WGG_func,TH1F* &ZGGJets_func,TH1F* &WJetsToLNu_func,              TH1F* &DYJetsToTauTau_func, TH1F* &tZq_ll_func,TH1F* &ST_tW_antitop_func, TH1F* &ST_tW_top_func, TH1F* &TGJets_func,TH1F* &THW_func, TH1F* &THQ_func,     TH1F* &VHToNonbb_func, TH1F* &ZHToTauTau_func, TH1F* &ZH_HToBB_ZToLL_func, TH1F* &GluGluHToZZTo4L_func, TH1F* &GluGluHToBB_func, TH1F* &GluGluHToGG_func, TH1F* &GluGluHToMuMu_func, TH1F* &GluGluHToTauTau_func, TH1F* &GluGluHToWWTo2L2Nu_func, TH1F* &GluGluHToWWToLNuQQ_func,TH1F* &VBFHToWWTo2L2Nu_func,TH1F*  &VBFHToGG_func,  TH1F* &TTTT_func);


int SigSF = 1;
//float LUMI  = 41500.0; //float LUMI = 36733; //36.773 /fb
float LUMI = 35900; //fb
//?where to get the more precise LUMI?
//where to get this LUMI//what's these number?where to get these number?
//SIGNAL
//double wTTTT = (SigSF*LUMI*0.009103);///TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root:  Positive:1709406  Negtive:704054
double wTTTT = (SigSF*LUMI*0.01197)/(1709406-704054);//
//tt
double wTTJets = (LUMI*746.7)/(29509487-14335648);//746.7 // TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root:  Positive:29509487  Negtive:14335648
double wTTGJets = (LUMI*3.773)/(3224372-1646539);//TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root:  Positive:3224372  Negtive:1646539  ;
double wttZJets = (LUMI*0.6559)/(9883364-0) ;// ttZJets_13TeV_madgraphMLM-pythia8.root:  Positive:9883364  Negtive:0      //Special care is taken when scaling the ttZ background to the cross-section= (LUMI*)/(-)
double wttWJets = (LUMI*0.2014)/(6700440-0);//ttWJets_13TeV_madgraphMLM.root:  Positive:6700440  Negtive:0  ;
double wttH= (LUMI*0.3372)/(9566400-0);//ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root:  Positive:9566400  Negtive:0  ;
double wttbb= (LUMI*1.393)/(2556073-1427835);//ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root:  Positive:2556073  Negtive:1427835  ;
//diboson and triboson an w/z+jets
double wWZ= (LUMI*2.343)/(2997571-0);//WZ_TuneCUETP8M1_13TeV-pythia8.root:  Positive:2997571  Negtive:0  ;
//double wWW= (LUMI*6.430)/(-);//?something wrong with ntuple
double wWWTo2L2Nu = (LUMI*0.1697)/(999367-0); //WWTo2L2Nu_DoubleScattering_13TeV-pythia8.root:  Positive:999367  Negtive:0  ;
double wWpWpJJ= (LUMI*0.05390)/(149681-0);//WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root:  Positive:149681  Negtive:0  ;
double wZZ  = (LUMI*1.016)/(998034-0);//ZZ_TuneCUETP8M1_13TeV-pythia8.root:  Positive:998034  Negtive:0  ;
double wWGJets = (LUMI*1.269)/(5077680-0);//WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root:  Positive:5077680  Negtive:0  ;
double wZGJetsToLLG = (LUMI*0.1319)/(498406-0);//ZGJetsToLLG_EW_LO_13TeV-sherpa.root:  Positive:498406  Negtive:394  ;
//
double wWWW= (LUMI*0.2086)/(225269-14731);//WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root:  Positive:225269  Negtive:14731  ;
double wWWZ= (LUMI*0.1651)/(235734-14266);//WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root:  Positive:235734  Negtive:14266  ;
double wWWG = (LUMI*0.2147)/(913515-85885);//WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root:  Positive:913515  Negtive:85885  ;
double wZZZ= (LUMI*0.01398)/(231217-18020);//ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root:  Positive:231217  Negtive:18020  ;
double wWZZ= (LUMI*0.05565)/(231583-15217);//WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root:  Positive:231583  Negtive:15217  ;
double wWZG= (LUMI*0.04123)/(921527-76673);//WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root:  Positive:921527  Negtive:76673  ;
//double wWGGJets = (LUMI*1.711)/(-);//
double wWGG =(LUMI*1.819)/(889832-110168); //WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root:  Positive:889832  Negtive:110168  ;
double wZGGJets= (LUMI*0.3717)/(291922-0);//ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8.root:  Positive:291922  Negtive:0  ;

double wWJetsToLNu= (LUMI*50300)/(29514020-0) ;//WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root:  Positive:29514020  Negtive:0  ;
//?missing ZJets?= (LUMI*)/(-)
//Drell-Yan
double wDYJetsToTauTau= (LUMI*1983)/(21891344-4380454);//DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1.rootDYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1.root:  Positive:21891344  Negtive:4380454  ;
//
//single top
double wtZq_ll= (LUMI*0.07358)/(8784890-5147710);//tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8.root:  Positive:8784890  Negtive:5147710  ;
//double wtZq_nunu= (LUMI*)/(630623-368977);//tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1.root:  Positive:630623  Negtive:368977  ;
//?
double wST_tW_antitop= (LUMI*38.06)/(418378-0);//ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root:  Positive:418378  Negtive:0  ;
double wST_tW_top= (LUMI*38.09)/(992024-0);//  ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root:  Positive:992024  Negtive:0  ;
double wTGJets= (LUMI*2.967)/(933719-623277);//TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root:  Positive:933719  Negtive:623277  ;
double wTHW= (LUMI*0.1467)/(4995329-2967);//THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8.root:  Positive:4995329  Negtive:2967  ;
double wTHQ= (LUMI*0.8816)/(9829911-0);//THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1.root:  Positive:9829911  Negtive:0  ;

//H 
double wVHToNonbb= (LUMI*2.137)/(799942-297663);//VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8.root:  Positive:799942  Negtive:297663  ;
double wZHToTauTau= (LUMI*0.7524)/(581490-18313);//ZHToTauTau_M125_13TeV_powheg_pythia8.root:  Positive:581490  Negtive:18313  ;
double wZH_HToBB_ZToLL= (LUMI*0.07523)/(1920440-59420);//ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8.root:  Positive:1920440  Negtive:59420  ;
double wGluGluHToZZTo4L= (LUMI*2.999)/(999800-0);//GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8.root:  Positive:999800  Negtive:0  ;
double wGluGluHToBB= (LUMI*32.10)/(2946318-853055);//GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.root:  Positive:2946318  Negtive:853055  ;
double wGluGluHToGG= (LUMI*31.98)/(335240-96369);//GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root:  Positive:335240  Negtive:96369  ;
double wGluGluHToMuMu= (LUMI*29.99)/(1991200-0);//GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root:  Positive:1991200  Negtive:0  ;
double wGluGluHToTauTau= (LUMI*30.52)/(1497800-0);//GluGluHToTauTau_M125_13TeV_powheg_pythia8.root:  Positive:1497800  Negtive:0  ;
double wGluGluHToWWTo2L2Nu= (LUMI*30.52)/(492200-0);//GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8.root:  Positive:492200  Negtive:0  ;
double wGluGluHToWWToLNuQQ= (LUMI*29.99)/(198000-0);//GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8.root:  Positive:198000  Negtive:0  ;
//double wVBFHToWWToLNuQQ= (LUMI*3.769)/(-)//
double wVBFHToWWTo2L2Nu= (LUMI*3.769)/(99931-69);//VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8.root:  Positive:99931  Negtive:69  ;
//??very different from ttH
//double wVBFHToWWTo2L2Nu= (LUMI*)/(99931-69);
//double wVBFHToTauTau= (LUMI*0.237)/(996835-765);//VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root:  Positive:996835  Negtive:765  ;
double wVBFHToMuMu= (LUMI*0.000823)/(996835-765);//VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root:  Positive:996835  Negtive:765  ;
double wVBFHToGG= (LUMI*3.992)/(639138-338962);//VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2.root:  Positive:639138  Negtive:338962  ;
//double wVBFHToBB= (LUMI*)/(-)//
//double wVBF_HToZZTo4L= (LUMI*3.769)/(-)
//HH count as minor
//minor
//
vector<double> bg_scale {
    wTTTT,//0
    wTTJets,wTTGJets,wttZJets,wttWJets,wttH, wttbb,//6
    wWZ,wWWTo2L2Nu,wWpWpJJ,wZZ,wWGJets,wZGJetsToLLG,
    wWWW,wWWZ,wWWG,wZZZ,wWZZ,wWZG,wWGG,wZGGJets,
    wWJetsToLNu,wDYJetsToTauTau,
    wtZq_ll,wST_tW_antitop,wST_tW_top,wTGJets,wTHW,wTHQ,
    wVHToNonbb,wZHToTauTau,wZH_HToBB_ZToLL,wGluGluHToZZTo4L,wGluGluHToBB,wGluGluHToGG,wGluGluHToMuMu,wGluGluHToTauTau,wGluGluHToWWTo2L2Nu,wGluGluHToWWToLNuQQ,wVBFHToWWTo2L2Nu,/*wVBFHToTauTau,*/wVBFHToMuMu,wVBFHToGG

};


//?should use a better way to add all samples at once
//sequence matter very much here
//TFile *file01 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/data.root");/*{{{*/
TFile *file02 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
//6
TFile *file03 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");//TTGJets
TFile *file05 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/ttZJets_13TeV_madgraphMLM-pythia8.root");
TFile *file06 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/ttWJets_13TeV_madgraphMLM.root");
TFile *file07 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root");//ttH
//?something wrong with ttH ntuple
TFile *file08 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
//6
TFile *file09 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/WZ_TuneCUETP8M1_13TeV-pythia8.root");
//TFile *file10 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/WWTo2L2Nu_DoubleScattering_13TeV-pythia8.root");
TFile *file11 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");//?missing this in other places
TFile *file12 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/ZZ_TuneCUETP8M1_13TeV-pythia8.root");//ZZ
TFile *file13 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");//

TFile *file14 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/ZGJetsToLLG_EW_LO_13TeV-sherpa.root");//
//8
TFile *file15 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file16 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file17 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file18 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file19 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file20 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file21 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");
TFile *file22 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8.root");
//
TFile *file23 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");//WJets
TFile *file24 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1.root");
//7-1
TFile *file25 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8.root");
//TFile *file26 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1.root");
TFile *file27 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root");
TFile *file28 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root");
TFile *file29 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root");
TFile *file30 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8.root");
TFile *file31 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1.root");
//12
TFile *file32 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8.root");
TFile *file33 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/ZHToTauTau_M125_13TeV_powheg_pythia8.root");
TFile *file34 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8.root");
TFile *file35 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8.root");
TFile *file36 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.root");
TFile *file37 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root");
TFile *file38 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root");
TFile *file39 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/GluGluHToTauTau_M125_13TeV_powheg_pythia8.root");
TFile *file40 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8.root");
TFile *file41 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8.root");
TFile *file42 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8.root");
//TFile *file43 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/VBFHToTauTau_M125_13TeV_powheg_pythia8.root");//bad input file
TFile *file44 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root");
TFile *file45 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2.root");
/*
string input_dir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/"; 
// char input_dir[100] = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/NoJEC/"; 
TFile *file02 = TFile::Open(input_dir+"/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03 = TFile::Open(input_dir+"/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04 = TFile::Open(input_dir+"/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");//TTGJets
TFile *file05 = TFile::Open(input_dir+"/ttZJets_13TeV_madgraphMLM-pythia8.root");
TFile *file06 = TFile::Open(input_dir+"/ttWJets_13TeV_madgraphMLM.root");
TFile *file07 = TFile::Open(input_dir+"/ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root");//ttH
//?something wrong with ttH ntuple
TFile *file08 = TFile::Open(input_dir+"/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09 = TFile::Open(input_dir+"/WZ_TuneCUETP8M1_13TeV-pythia8.root");
//TFile *file10 = TFile::Open(input_dir+"/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_1 = TFile::Open(input_dir+"/WWTo2L2Nu_DoubleScattering_13TeV-pythia8.root");
TFile *file11 = TFile::Open(input_dir+"/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");//?missing this in other places
TFile *file12 = TFile::Open(input_dir+"/ZZ_TuneCUETP8M1_13TeV-pythia8.root");//ZZ
TFile *file13 = TFile::Open(input_dir+"/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");//

TFile *file14 = TFile::Open(input_dir+"/ZGJetsToLLG_EW_LO_13TeV-sherpa.root");//
TFile *file15 = TFile::Open(input_dir+"/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file16 = TFile::Open(input_dir+"/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file17 = TFile::Open(input_dir+"/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file18 = TFile::Open(input_dir+"/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file19 = TFile::Open(input_dir+"/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file20 = TFile::Open(input_dir+"/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");//
TFile *file21 = TFile::Open(input_dir+"/WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");
TFile *file22 = TFile::Open(input_dir+"/ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8.root");
TFile *file23 = TFile::Open(input_dir+"/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");//WJets
TFile *file24 = TFile::Open(input_dir+"/DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1.root");
TFile *file25 = TFile::Open(input_dir+"/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8.root");
TFile *file26 = TFile::Open(input_dir+"/tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1.root");
TFile *file27 = TFile::Open(input_dir+"/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root");
TFile *file28 = TFile::Open(input_dir+"/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root");
TFile *file29 = TFile::Open(input_dir+"/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root");
TFile *file30 = TFile::Open(input_dir+"/THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8.root");
TFile *file31 = TFile::Open(input_dir+"/THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1.root");
TFile *file32 = TFile::Open(input_dir+"/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8.root");
TFile *file33 = TFile::Open(input_dir+"/ZHToTauTau_M125_13TeV_powheg_pythia8.root");
TFile *file34 = TFile::Open(input_dir+"/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8.root");
TFile *file35 = TFile::Open(input_dir+"/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8.root");
TFile *file36 = TFile::Open(input_dir+"/GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.root");
TFile *file37 = TFile::Open(input_dir+"/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root");
TFile *file38 = TFile::Open(input_dir+"/GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root");
TFile *file39 = TFile::Open(input_dir+"/GluGluHToTauTau_M125_13TeV_powheg_pythia8.root");
TFile *file40 = TFile::Open(input_dir+"/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8.root");
TFile *file41 = TFile::Open(input_dir+"/GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8.root");
TFile *file42 = TFile::Open(input_dir+"/VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8.root");
TFile *file43 = TFile::Open(input_dir+"/VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2.root");
*/
//TTree *Tree01 = (TTree*)file01->Get("tree");
TTree *Tree02 = (TTree*)file02->Get("tree");
TTree *Tree03 = (TTree*)file03->Get("tree");
TTree *Tree04 = (TTree*)file04->Get("tree");
TTree *Tree05 = (TTree*)file05->Get("tree");
TTree *Tree06 = (TTree*)file06->Get("tree");
TTree *Tree07 = (TTree*)file07->Get("tree");
TTree *Tree08 = (TTree*)file08->Get("tree");
TTree *Tree09 = (TTree*)file09->Get("tree");
//TTree *Tree10 = (TTree*)file10->Get("tree");
TTree *Tree10_1 = (TTree*)file10_1->Get("tree");
TTree *Tree11 = (TTree*)file11->Get("tree");
TTree *Tree12 = (TTree*)file12->Get("tree");
TTree *Tree13 = (TTree*)file13->Get("tree");
TTree *Tree14 = (TTree*)file14->Get("tree");
TTree *Tree15 = (TTree*)file15->Get("tree");
TTree *Tree16 = (TTree*)file16->Get("tree");
TTree *Tree17 = (TTree*)file17->Get("tree");
TTree *Tree18 = (TTree*)file18->Get("tree");
TTree *Tree19 = (TTree*)file19->Get("tree");
TTree *Tree20 = (TTree*)file20->Get("tree");
TTree *Tree21 = (TTree*)file21->Get("tree");
TTree *Tree22 = (TTree*)file22->Get("tree");
TTree *Tree23 = (TTree*)file23->Get("tree");
TTree *Tree24 = (TTree*)file24->Get("tree");
TTree *Tree25 = (TTree*)file25->Get("tree");
//TTree *Tree26 = (TTree*)file26->Get("tree");
TTree *Tree27 = (TTree*)file27->Get("tree");
TTree *Tree28 = (TTree*)file28->Get("tree");
TTree *Tree29 = (TTree*)file29->Get("tree");
TTree *Tree30 = (TTree*)file30->Get("tree");
TTree *Tree31 = (TTree*)file31->Get("tree");
TTree *Tree32 = (TTree*)file32->Get("tree");
TTree *Tree33 = (TTree*)file33->Get("tree");
TTree *Tree34 = (TTree*)file34->Get("tree");
TTree *Tree35 = (TTree*)file35->Get("tree");
TTree *Tree36 = (TTree*)file36->Get("tree");
TTree *Tree37 = (TTree*)file37->Get("tree");
TTree *Tree38 = (TTree*)file38->Get("tree");
TTree *Tree39 = (TTree*)file39->Get("tree");
TTree *Tree40 = (TTree*)file40->Get("tree");
TTree *Tree41 = (TTree*)file41->Get("tree");
TTree *Tree42 = (TTree*)file42->Get("tree");
//TTree *Tree43 = (TTree*)file43->Get("tree");
TTree *Tree44 = (TTree*)file44->Get("tree");
TTree *Tree45 = (TTree*)file45->Get("tree");
/*}}}*/
vector<TTree*> bgTree = {
    Tree02,Tree03,Tree04,Tree05,Tree06,Tree07,Tree08,Tree09,Tree10_1,Tree11,Tree12,Tree13,Tree14,Tree15,Tree16,Tree17,Tree18,Tree19,Tree20,Tree21,Tree22,Tree23,Tree24,Tree25,/*Tree26,*/Tree27,Tree28,Tree29,Tree30,Tree31,Tree32,Tree33,Tree34,Tree35,Tree36,Tree37,Tree38,Tree39,Tree40,Tree41,Tree42,/*Tree43,*/Tree44,Tree45
};
/*
//TFile *file01_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESup/data.root");{{{
TFile *file02_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESup/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESup/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESup/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
TFile *file05_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESup/ttZJets_13TeV_madgraphMLM-pythia8.root.root");
TFile *file06_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESup/ttWJets_13TeV_madgraphMLM.root");
TFile *file07_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESup/ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root.root");
TFile *file08_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESup/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESup/WZ_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESup/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file11_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESup/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");
TFile *file12_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESup/ZZ_TuneCUETP8M1_13TeV-pythia8.root.root");
TFile *file13_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESup/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");
//TTree *Tree01_J1 = (TTree*)file01_J1->Get("tree");
TTree *Tree02_J1 = (TTree*)file02_J1->Get("tree");
TTree *Tree03_J1 = (TTree*)file03_J1->Get("tree");
TTree *Tree04_J1 = (TTree*)file04_J1->Get("tree");
TTree *Tree05_J1 = (TTree*)file05_J1->Get("tree");
TTree *Tree06_J1 = (TTree*)file06_J1->Get("tree");
TTree *Tree07_J1 = (TTree*)file07_J1->Get("tree");
TTree *Tree08_J1 = (TTree*)file08_J1->Get("tree");
TTree *Tree09_J1 = (TTree*)file09_J1->Get("tree");
TTree *Tree10_J1 = (TTree*)file10_J1->Get("tree");
TTree *Tree11_J1 = (TTree*)file11_J1->Get("tree");
TTree *Tree12_J1 = (TTree*)file12_J1->Get("tree");
TTree *Tree13_J1 = (TTree*)file13_J1->Get("tree");


//TFile *file01_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESdown/data.root");
TFile *file02_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESdown/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESdown/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESdown/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
TFile *file05_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESdown/ttZJets_13TeV_madgraphMLM-pythia8.root.root");

TFile *file06_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESdown/ttWJets_13TeV_madgraphMLM.root");
TFile *file07_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESdown/ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root.root");
TFile *file08_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESdown/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESdown/WZ_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESdown/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file11_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESdown/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");
TFile *file12_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESdown/ZZ_TuneCUETP8M1_13TeV-pythia8.root.root");
TFile *file13_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JESdown/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");
//TTree *Tree01_J2 = (TTree*)file01_J2->Get("tree");
TTree *Tree02_J2 = (TTree*)file02_J2->Get("tree");
TTree *Tree03_J2 = (TTree*)file03_J2->Get("tree");
TTree *Tree04_J2 = (TTree*)file04_J2->Get("tree");
TTree *Tree05_J2 = (TTree*)file05_J2->Get("tree");
TTree *Tree06_J2 = (TTree*)file06_J2->Get("tree");
TTree *Tree07_J2 = (TTree*)file07_J2->Get("tree");
TTree *Tree08_J2 = (TTree*)file08_J2->Get("tree");
TTree *Tree09_J2 = (TTree*)file09_J2->Get("tree");
TTree *Tree10_J2 = (TTree*)file10_J2->Get("tree");
TTree *Tree11_J2 = (TTree*)file11_J2->Get("tree");
TTree *Tree12_J2 = (TTree*)file12_J2->Get("tree");
TTree *Tree13_J2 = (TTree*)file13_J2->Get("tree");




//TFile *file01_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERup/data.root");
TFile *file02_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERup/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERup/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERup/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
TFile *file05_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERup/ttZJets_13TeV_madgraphMLM-pythia8.root.root");
TFile *file06_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERup/ttWJets_13TeV_madgraphMLM.root");
TFile *file07_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERup/ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root.root");
TFile *file08_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERup/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERup/WZ_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERup/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file11_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERup/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");
TFile *file12_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERup/ZZ_TuneCUETP8M1_13TeV-pythia8.root.root");
TFile *file13_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERup/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");
//TTree *Tree01_J3 = (TTree*)file01_J3->Get("tree");
TTree *Tree02_J3 = (TTree*)file02_J3->Get("tree");
TTree *Tree03_J3 = (TTree*)file03_J3->Get("tree");
TTree *Tree04_J3 = (TTree*)file04_J3->Get("tree");
TTree *Tree05_J3 = (TTree*)file05_J3->Get("tree");
TTree *Tree06_J3 = (TTree*)file06_J3->Get("tree");
TTree *Tree07_J3 = (TTree*)file07_J3->Get("tree");
TTree *Tree08_J3 = (TTree*)file08_J3->Get("tree");
TTree *Tree09_J3 = (TTree*)file09_J3->Get("tree");
TTree *Tree10_J3 = (TTree*)file10_J3->Get("tree");
TTree *Tree11_J3 = (TTree*)file11_J3->Get("tree");
TTree *Tree12_J3 = (TTree*)file12_J3->Get("tree");
TTree *Tree13_J3 = (TTree*)file13_J3->Get("tree");

//TFile *file01_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERdown/data.root");
TFile *file02_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERdown/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERdown/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERdown/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
TFile *file05_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERdown/ttZJets_13TeV_madgraphMLM-pythia8.root.root");
TFile *file06_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERdown/ttWJets_13TeV_madgraphMLM.root");
TFile *file07_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERdown/ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root.root");//ttH
TFile *file08_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERdown/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERdown/WZ_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERdown/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file11_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERdown/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");
TFile *file12_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERdown/ZZ_TuneCUETP8M1_13TeV-pythia8.root.root");
TFile *file13_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v8_NewNtuple/JERdown/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");
//TTree *Tree01_J4 = (TTree*)file01_J4->Get("tree");
TTree *Tree02_J4 = (TTree*)file02_J4->Get("tree");
TTree *Tree03_J4 = (TTree*)file03_J4->Get("tree");
TTree *Tree04_J4 = (TTree*)file04_J4->Get("tree");
TTree *Tree05_J4 = (TTree*)file05_J4->Get("tree");
TTree *Tree06_J4 = (TTree*)file06_J4->Get("tree");
TTree *Tree07_J4 = (TTree*)file07_J4->Get("tree");
TTree *Tree08_J4 = (TTree*)file08_J4->Get("tree");
TTree *Tree09_J4 = (TTree*)file09_J4->Get("tree");
TTree *Tree10_J4 = (TTree*)file10_J4->Get("tree");
TTree *Tree11_J4 = (TTree*)file11_J4->Get("tree");
TTree *Tree12_J4 = (TTree*)file12_J4->Get("tree");
TTree *Tree13_J4 = (TTree*)file13_J4->Get("tree");

                                                   

//TH1F *data_SR; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_SR; TH1F *TTGJets_SR; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_SR; TH1F *ttWJets_13TeV_madgraphMLM_SR;
//TH1F* background_SR;
TH1F* TTJets_SR;
TH1F* TTGJets_SR;
TH1F* ttZJets_SR;
TH1F* ttWJets_SR;
TH1F* ttH_SR;
TH1F* ttbb_SR;
TH1F* WZ_SR;
TH1F* WWTo2L2Nu_SR;
TH1F* WpWpJJ_SR;
TH1F* ZZ_SR;
TH1F* WGJets_SR;
TH1F* ZGJetsToLLG_SR;
TH1F* WWW_SR;
TH1F* WWZ_SR;
TH1F* WWG_SR;
TH1F* ZZZ_SR;
TH1F* WZZ_SR;
TH1F* WZG_SR;
TH1F* WGG_SR;
TH1F* ZGGJets_SR;
TH1F* WJetsToLNu_SR;
TH1F* DYJetsToTauTau_SR;
TH1F* tZq_ll_SR;
TH1F* ST_tW_antitop_SR;
TH1F* ST_tW_top_SR;
TH1F* TGJets_SR;
TH1F* THW_SR;
TH1F* THQ_SR;
TH1F* VHToNonbb_SR;
TH1F* ZHToTauTau_SR;
TH1F* ZH_HToBB_ZToLL_SR;
TH1F* GluGluHToZZTo4L_SR;
TH1F* GluGluHToBB_SR;
TH1F* GluGluHToGG_SR;
TH1F* GluGluHToMuMu_SR;
TH1F* GluGluHToTauTau_SR;
TH1F* GluGluHToWWTo2L2Nu_SR;
TH1F* GluGluHToWWToLNuQQ_SR;
TH1F* VBFHToWWTo2L2Nu_SR;
TH1F* VBFHToGG_SR;
TH1F* TTTT_SR;

TH1F *QCD_HT1000to1500_SR; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_SR; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_SR; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_SR; TH1F *TTWJets_SR; TH1F *TTZ_SR; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8SR; 
TH1F *background_SR;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_SR;

TH1F *data_P1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_P1; TH1F *TTGJets_P1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_P1; TH1F *ttWJets_13TeV_madgraphMLM_P1; 
TH1F *QCD_HT1000to1500_P1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_P1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_P1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_P1; TH1F *TTWJets_P1; TH1F *TTZ_P1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8P1; 
TH1F *background_P1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_P1;

TH1F *data_P2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_P2; TH1F *TTGJets_P2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_P2; TH1F *ttWJets_13TeV_madgraphMLM_P2; 
TH1F *QCD_HT1000to1500_P2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_P2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_P2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_P2; TH1F *TTWJets_P2; TH1F *TTZ_P2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8P2; 
TH1F *background_P2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_P2;

TH1F *data_F1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_F1; TH1F *TTGJets_F1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_F1; TH1F *ttWJets_13TeV_madgraphMLM_F1; 
TH1F *QCD_HT1000to1500_F1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_F1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_F1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_F1; TH1F *TTWJets_F1; TH1F *TTZ_F1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8F1; 
TH1F *background_F1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_F1;

TH1F *data_F2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_F2; TH1F *TTGJets_F2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_F2; TH1F *ttWJets_13TeV_madgraphMLM_F2; 
TH1F *QCD_HT1000to1500_F2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_F2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_F2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_F2; TH1F *TTWJets_F2; TH1F *TTZ_F2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8F2; 
TH1F *background_F2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_F2;

TH1F *data_B1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_B1; TH1F *TTGJets_B1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_B1; TH1F *ttWJets_13TeV_madgraphMLM_B1; 
TH1F *QCD_HT1000to1500_B1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_B1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_B1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_B1; TH1F *TTWJets_B1; TH1F *TTZ_B1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8B1; 
TH1F *background_B1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_B1;

TH1F *data_B2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_B2; TH1F *TTGJets_B2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_B2; TH1F *ttWJets_13TeV_madgraphMLM_B2; 
TH1F *QCD_HT1000to1500_B2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_B2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_B2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_B2; TH1F *TTWJets_B2; TH1F *TTZ_B2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8B2; 
TH1F *background_B2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_B2;

TH1F *data_Z1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_Z1; TH1F *TTGJets_Z1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_Z1; TH1F *ttWJets_13TeV_madgraphMLM_Z1; 
TH1F *QCD_HT1000to1500_Z1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_Z1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_Z1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_Z1; TH1F *TTWJets_Z1; TH1F *TTZ_Z1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8Z1; 
TH1F *background_Z1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_Z1;

TH1F *data_Z2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_Z2; TH1F *TTGJets_Z2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_Z2; TH1F *ttWJets_13TeV_madgraphMLM_Z2; 
TH1F *QCD_HT1000to1500_Z2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_Z2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_Z2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_Z2; TH1F *TTWJets_Z2; TH1F *TTZ_Z2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8Z2; 
TH1F *background_Z2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_Z2;

TH1F *data_W1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_W1; TH1F *TTGJets_W1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_W1; TH1F *ttWJets_13TeV_madgraphMLM_W1; 
TH1F *QCD_HT1000to1500_W1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_W1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_W1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_W1; TH1F *TTWJets_W1; TH1F *TTZ_W1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8W1; 
TH1F *background_W1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_W1;

TH1F *data_W2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_W2; TH1F *TTGJets_W2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_W2; TH1F *ttWJets_13TeV_madgraphMLM_W2; 
TH1F *QCD_HT1000to1500_W2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_W2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_W2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_W2; TH1F *TTWJets_W2; TH1F *TTZ_W2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8W2; 
TH1F *background_W2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_W2;

TH1F *data_T1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_T1; TH1F *TTGJets_T1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_T1; TH1F *ttWJets_13TeV_madgraphMLM_T1; 
TH1F *QCD_HT1000to1500_T1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_T1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_T1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_T1; TH1F *TTWJets_T1; TH1F *TTZ_T1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8T1; 
TH1F *background_T1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_T1;

TH1F *data_T2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_T2; TH1F *TTGJets_T2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_T2; TH1F *ttWJets_13TeV_madgraphMLM_T2; 
TH1F *QCD_HT1000to1500_T2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_T2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_T2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_T2; TH1F *TTWJets_T2; TH1F *TTZ_T2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8T2; 
TH1F *background_T2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_T2;

TH1F *data_J1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_J1; TH1F *TTGJets_J1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_J1; TH1F *ttWJets_13TeV_madgraphMLM_J1; 
TH1F *QCD_HT1000to1500_J1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_J1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_J1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_J1; TH1F *TTWJets_J1; TH1F *TTZ_J1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8J1; 
TH1F *background_J1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_J1;

TH1F *data_J2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_J2; TH1F *TTGJets_J2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_J2; TH1F *ttWJets_13TeV_madgraphMLM_J2; 
TH1F *QCD_HT1000to1500_J2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_J2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_J2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_J2; TH1F *TTWJets_J2; TH1F *TTZ_J2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8J2; 
TH1F *background_J2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_J2;

TH1F *data_J3; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_J3; TH1F *TTGJets_J3; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_J3; TH1F *ttWJets_13TeV_madgraphMLM_J3; 
TH1F *QCD_HT1000to1500_J3; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_J3; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_J3; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_J3; TH1F *TTWJets_J3; TH1F *TTZ_J3; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8J3; 
TH1F *background_J3;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_J3;

TH1F *data_J4; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_J4; TH1F *TTGJets_J4; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_J4; TH1F *ttWJets_13TeV_madgraphMLM_J4; 
TH1F *QCD_HT1000to1500_J4; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_J4; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_J4; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_J4; TH1F *TTWJets_J4; TH1F *TTZ_J4; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8J4; 
TH1F *background_J4;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_J4;

TH1F *data_qcd1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_qcd1; TH1F *TTGJets_qcd1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_qcd1; TH1F *ttWJets_13TeV_madgraphMLM_qcd1;
TH1F *QCD_HT1000to1500_qcd1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_qcd1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_qcd1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_qcd1; TH1F *TTWJets_qcd1; TH1F *TTZ_qcd1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8qcd1;
TH1F *background_qcd1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_qcd1;

TH1F *data_qcd2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_qcd2; TH1F *TTGJets_qcd2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_qcd2; TH1F *ttWJets_13TeV_madgraphMLM_qcd2;
TH1F *QCD_HT1000to1500_qcd2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_qcd2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_qcd2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_qcd2; TH1F *TTWJets_qcd2; TH1F *TTZ_qcd2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8qcd2;
TH1F *background_qcd2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_qcd2;

TH1F *data_pdf1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_pdf1; TH1F *TTGJets_pdf1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_pdf1; TH1F *ttWJets_13TeV_madgraphMLM_pdf1;
TH1F *QCD_HT1000to1500_pdf1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_pdf1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_pdf1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_pdf1; TH1F *TTWJets_pdf1; TH1F *TTZ_pdf1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8pdf1;
TH1F *background_pdf1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_pdf1;

TH1F *data_pdf2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_pdf2; TH1F *TTGJets_pdf2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_pdf2; TH1F *ttWJets_13TeV_madgraphMLM_pdf2;
TH1F *QCD_HT1000to1500_pdf2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_pdf2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_pdf2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_pdf2; TH1F *TTWJets_pdf2; TH1F *TTZ_pdf2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8pdf2;
TH1F *background_pdf2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_pdf2;


TH1F *data_TR1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_TR1; TH1F *TTGJets_TR1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_TR1; TH1F *ttWJets_13TeV_madgraphMLM_TR1;
TH1F *QCD_HT1000to1500_TR1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_TR1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_TR1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_TR1; TH1F *TTWJets_TR1; TH1F *TTZ_TR1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8TR1;
TH1F *background_TR1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_TR1;


TH1F *data_TR2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_TR2; TH1F *TTGJets_TR2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_TR2; TH1F *ttWJets_13TeV_madgraphMLM_TR2;
TH1F *QCD_HT1000to1500_TR2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_TR2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_TR2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_TR2; TH1F *TTWJets_TR2; TH1F *TTZ_TR2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8TR2;
TH1F *background_TR2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_TR2;
*/
