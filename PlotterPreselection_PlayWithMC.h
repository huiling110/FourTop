#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

//void MakeHistos(char CUT[1000],const char *plot,int BIN,float MIN,float MAX,int JETSyst,
//		/*TH1D* &data_func,*/ TH1D* &background_func,TH1D* &TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_func,TH1D* &TTGJets_func,TH1D* &ttZJets_13TeV_madgraphMLM-pythia8.root_func,TH1D* &ttWJets_13TeV_madgraphMLM_func,TH1D* &ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root_func,TH1D* &ttbb_4FS_ckm_amcatnlo_madspin_pythia8_func,TH1D* &WZ_TuneCUETP8M1_13TeV-pythia8_func,
//		TH1D* &WW_TuneCUETP8M1_13TeV-pythia8_func,TH1D* &TTWJets_func,TH1D* &TTZ_func, TH1D* &WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_func,
//		TH1D* &TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8func);

void GetHisto(char CUT[1000], TTree *Tree, TH1D* & histo, const char *plot, int BIN, float MIN, float MAX);
void GetHisto_noBoundry(char CUT[1000], TTree *Tree, TH1D* & histo, const char *plot, int BIN, float MIN, float MAX);
float separationPower(TH1D* h1, TH1D* h2);

void MakeHistoErrors(int m, TH1D* &histo_SR, TH1D* histo_P1, TH1D* histo_P2, TH1D* histo_F1, TH1D* histo_F2, TH1D* histo_B1, TH1D* histo_B2, TH1D* histo_Z1, TH1D* histo_Z2, TH1D* histo_W1, TH1D* histo_W2, TH1D* histo_T1, TH1D* histo_T2, TH1D* histo_J1, TH1D* histo_J2, TH1D* histo_J3, TH1D* histo_J4, TH1D* histo_qcd1, TH1D* histo_qcd2, TH1D* histo_pdf1, TH1D* histo_pdf2, TH1D* histo_TR1, TH1D* histo_TR2);

void CloneHistos();


void MakeHistos(char CUT[1000],const char *plot,int BIN,float MIN,float MAX,int JETSyst,
                       /* TH1D* &data_func,*/TH1D* &background_func,TH1D* &TTJets_func,TH1D* &TTGJets_func,TH1D* &ttZJets_func,  TH1D*  &ttWJets_func,TH1D*       &ttH_func,TH1D* &ttbb_func,TH1D* &WZ_func,
                                       /* TH1D* &WW_func,*/TH1D* &WWTo2L2Nu_func, TH1D* &WpWpJJ_func,TH1D* &ZZ_func,TH1D* &WGJets_func, TH1D* &ZGJetsToLLG_func, TH1D* &WWW_func,TH1D* &WWZ_func,TH1D* &WWG_func,TH1D* &ZZZ_func,TH1D* &WZZ_func,TH1D* &WZG_func, TH1D* &WGG_func,TH1D* &ZGGJets_func,TH1D* &WJetsToLNu_func,              TH1D* &DYJetsToTauTau_func, TH1D* &tZq_ll_func,TH1D* &ST_tW_antitop_func, TH1D* &ST_tW_top_func, TH1D* &TGJets_func,TH1D* &THW_func, TH1D* &THQ_func,     TH1D* &VHToNonbb_func, TH1D* &ZHToTauTau_func, TH1D* &ZH_HToBB_ZToLL_func, TH1D* &GluGluHToZZTo4L_func, TH1D* &GluGluHToBB_func, TH1D* &GluGluHToGG_func, TH1D* &GluGluHToMuMu_func, TH1D* &GluGluHToTauTau_func, TH1D* &GluGluHToWWTo2L2Nu_func, TH1D* &GluGluHToWWToLNuQQ_func,TH1D* &VBFHToWWTo2L2Nu_func,TH1D*  &VBFHToGG_func,  TH1D* &TTTT_func);


int SigSF = 1;
//float LUMI  = 41500.0; //float LUMI = 36733; //36.773 /fb
float LUMI = 35900; //fb
//?where to get the more precise LUMI?
//SIGNAL
//double wTTTT = (SigSF*LUMI*0.009103);///TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root:  Positive:1709406  Negtive:704054
double wTTTT_v2 = (SigSF*LUMI*0.01197)/(21942.3);//TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root : 21942.3
//tt
double wTTJets_v2 = (LUMI*746.7)/(9.68684e+10);//746.7 //TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root : 9.68684e+10
double wTT_v2     = (LUMI*746.7)/(7.69155e+07)  ; //TT_TuneCUETP8M2T4_13TeV-powheg-pythia8.root : 7.69155e+07
//1.67772e+07

double wTTGJets_v2 = (LUMI*3.773)/(3.33781e+07);  ; //TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root: 3.33781e+07
double wttZJets_v2 = (LUMI*0.6559)/(9.88336e+06) ;      //Special care is taken when scaling the ttZ background to the cross-section= (LUMI*)/(-) //ttZJets_13TeV_madgraphMLM-pythia8.root : 9.88336e+06
double wttWJets_v2 = (LUMI*0.2014)/(6.70044e+06);  ; //  ttWJets_13TeV_madgraphMLM.root : 6.70044e+06
double wttH_v2= (LUMI*0.3372)/(9.5664e+06);  ; //ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root : 9.5664e+06

// double wttbb_v2= (LUMI*1.393)/(2556073-1427835);// ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root:  Positive:2556073  Negtive:1427835  ;
//diboson and triboson an w_v2/z+jets
double wWZ_v2= (LUMI*2.343)/(2.99757e+06);  ;//WZ_TuneCUETP8M1_13TeV-pythia8.root : 2.99757e+06
//double wWW_v2= (LUMI*6.430)/(-);//?something wrong with ntuple
double wWWTo2L2Nu_v2 = (LUMI*0.1697)/(999367);   ;//r WWTo2L2Nu_DoubleScattering_13TeV-pythia8.root : 999367
double wWpWpJJ_v2= (LUMI*0.05390)/(149681);  ;//WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root : 149681
double wZZ_v2  = (LUMI*1.016)/(998034);  ;//ZZ_TuneCUETP8M1_13TeV-pythia8.root : 998034
double wWGJets_v2 = (LUMI*1.269)/(5.07768e+06);  ;//WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root : 5.07768e+06
double wZGJetsToLLG_v2 = (LUMI*0.1319)/(1.91648e+08);  ;// ZGJetsToLLG_EW_LO_13TeV-sherpa.root : 1.91648e+08
//
double wWWW_v2= (LUMI*0.2086)/(50012.9);  ;// WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root : 50012.9
double wWWZ_v2= (LUMI*0.1651)/(41171.8);  ;//WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root : 41171.8
double wWWG_v2 = (LUMI*0.2147)/(214524);  ; //WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root : 214524
double wZZZ_v2= (LUMI*0.01398)/(3499.45);  ;//ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root : 3499.45
double wWZZ_v2= (LUMI*0.05565)/(13736.4);  ; //WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root : 13736.4
double wWZG_v2= (LUMI*0.04123)/(41207.1);  ;// WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root : 41207.1
//double wWGGJets_v2 = (LUMI*1.711)/(-);//
double wWGG_v2 =(LUMI*1.819)/(1.82543e+06);   ;// WGG_5f_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root : 1.82543e+06
double wZGGJets_v2= (LUMI*0.3717)/(291922);  ;//ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8.root : 291922


double wWJetsToLNu_v2= (LUMI*50300)/(2.9514e+07) ;  ;//WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root : 2.9514e+07
//?missing ZJets?= (LUMI*)/(-)
//Drell-Yan
double wDYJetsToTauTau_v2= (LUMI*1983)/(1.48305e+11);  ;//DYJetsToTauTau_ForcedMuEleDecay_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1.root : 1.48305e+11
//
//single top
double wtZq_ll_v2= (LUMI*0.07358)/(1.03784e+06);  ;//tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8.root : 1.03784e+06
//double wtZq_nunu_v2= (LUMI*)/(630623-368977);// tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1.root:  Positive:630623  Negtive:368977  ;//

//?
double wST_tW_antitop_v2= (LUMI*38.06)/(418378);  ;//ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root : 418378
double wST_tW_top_v2= (LUMI*38.09)/(992024);  ;//ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4.root : 992024
double wTGJets_v2= (LUMI*2.967)/(4.66341e+06);  ;//TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root : 4.66341e+06
double wTHW_v2= (LUMI*0.1467)/(4.98913e+06);  ;//THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8.root : 4.98913e+06
double wTHQ_v2= (LUMI*0.8816)/(9.82991e+06);  ;//THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1.root : 9.82991e+06
//H 
double wVHToNonbb_v2= (LUMI*2.137)/(5.76495e+06);  ;//VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8.root : 5.76495e+06
double wZHToTauTau_v2= (LUMI*0.7524)/(451665);  ;// ZHToTauTau_M125_13TeV_powheg_pythia8.root : 451665
double wZH_HToBB_ZToLL_v2= (LUMI*0.07523)/(149117);  ;//ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8.root : 149117
double wGluGluHToZZTo4L_v2= (LUMI*2.999)/(999800);  ;//GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8.root : 999800
double wGluGluHToBB_v2= (LUMI*32.10)/(4.17422e+08);  ;//GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.root : 4.17422e+08
double wGluGluHToGG_v2= (LUMI*31.98)/(4.76338e+07);  ;//GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root : 4.76338e+07
double wGluGluHToMuMu_v2= (LUMI*29.99)/(1.99089e+06);  ;//GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root : 1.99089e+06

double wGluGluHToTauTau_v2= (LUMI*30.52)/(1.4978e+06);  ;//GluGluHToTauTau_M125_13TeV_powheg_pythia8.root : 1.4978e+06
double wGluGluHToWWTo2L2Nu_v2= (LUMI*30.52)/(492200);  ;//GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8.root : 492200
double wGluGluHToWWToLNuQQ_v2= (LUMI*29.99)/(198000);  ;//GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8.root : 198000
//double wVBFHToWWToLNuQQ_v2= (LUMI*3.769)/(-)//
double wVBFHToWWTo2L2Nu_v2= (LUMI*3.769)/(376906);  ;//VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8.root : 376906
//??very different from ttH
//double wVBFHToWWTo2L2Nu_v2= (LUMI*)/(99931-69);
//double wVBFHToTauTau_v2= (LUMI*0.237)/(996835-765);// VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root:  Positive:996835  Negtive:765  ;
double wVBFHToMuMu_v2= (LUMI*0.000823)/(3.72902e+06);  ;//VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8.root : 3.72902e+06
double wVBFHToGG_v2= (LUMI*3.992)/(3.90874e+06);  ;//VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2.root : 3.90874e+06
// double wVBFHToBB= (LUMI*)/(-)//
//double wVBF_HToZZTo4L= (LUMI*3.769)/(-)
//HH count as minor
//minor
vector<double> allScales_v2 {
    wTTTT_v2, //0
    wTT_v2, //changed wTTJets to wTT
    wTTGJets_v2, wttZJets_v2, wttWJets_v2, wttH_v2, //5
    wWZ_v2, wWWTo2L2Nu_v2, wWpWpJJ_v2, wZZ_v2, wWGJets_v2, wZGJetsToLLG_v2, 
    wWWW_v2, wWWZ_v2, wWWG_v2, wZZZ_v2, wWZZ_v2, wWZG_v2, wWGG_v2, wZGGJets_v2, 
    wWJetsToLNu_v2, wDYJetsToTauTau_v2, 
    wtZq_ll_v2, wST_tW_antitop_v2, wST_tW_top_v2, wTGJets_v2, wTHW_v2, wTHQ_v2, 
    wVHToNonbb_v2, wZHToTauTau_v2, wZH_HToBB_ZToLL_v2, wGluGluHToZZTo4L_v2, wGluGluHToBB_v2, wGluGluHToGG_v2, wGluGluHToMuMu_v2, wGluGluHToTauTau_v2, wGluGluHToWWTo2L2Nu_v2, wGluGluHToWWToLNuQQ_v2, wVBFHToWWTo2L2Nu_v2, /*wVBFHToTauTau_v2, */wVBFHToMuMu_v2, wVBFHToGG_v2
};

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

//sequence matter very much here
// TString baseDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v17_removeMuonISO/NoJEC/";
// TString baseDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/NoJEC/";
// TString baseDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v18_withISO_filetersAndPreselection/NoJEC/";
// TString baseDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v19_addGenHisto/NoJEC/";
TString baseDir = "/publicfs/cms/user/fabioiemmi/v20_checkforv19/NoJEC/";
// vector<TString> files = {
    // "TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root",
// }
// for ( UInt_t f=0; f<files.size(); f++){
    // TString filename = baseDir+file[f];
    // sprintf(ifile, "file%d", f);
    // sprintf(itree, "tree%d", f);
    // TFile *ifile =
// }

//TFile *file01 =   TFile::Open("data.root");
TFile *file02 =   TFile::Open(baseDir+"TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
//5
// TFile *file03 =   TFile::Open(baseDir+"TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file03 =   TFile::Open(baseDir+"TT_TuneCUETP8M2T4_13TeV-powheg-pythia8.root");
/*{{{*/
TFile *file04 =   TFile::Open(baseDir+"TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");//TTGJets
TFile *file05 =   TFile::Open(baseDir+"ttZJets_13TeV_madgraphMLM-pythia8.root");
TFile *file06 =   TFile::Open(baseDir+"ttWJets_13TeV_madgraphMLM.root");
TFile *file07 =   TFile::Open(baseDir+"ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root");//ttH
//?something wrong with ttH ntuple
// TFile *file08 =   TFile::Open(baseDir+"ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
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
TFile *file45 =   TFile::Open(baseDir+"VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2.root");/*}}}*/
//TTree *Tree01 =   (TTree*)file01->Get("tree");
TTree *Tree02 =   (TTree*)file02->Get("tree");
TTree *Tree03 =   (TTree*)file03->Get("tree");
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

TH1D *h_genWeight02 =   (TH1D*)file02->Get("h_genweight");
TH1D *h_genWeight03 =   (TH1D*)file03->Get("h_genweight");
TH1D *h_genWeight04 =   (TH1D*)file04->Get("h_genweight");
TH1D *h_genWeight05 =   (TH1D*)file05->Get("h_genweight");
TH1D *h_genWeight06 =   (TH1D*)file06->Get("h_genweight");
TH1D *h_genWeight07 =   (TH1D*)file07->Get("h_genweight");
// TH1D *h_genWeight08 =   (TH1D*)file08->Get("h_genweight");
TH1D *h_genWeight09 =   (TH1D*)file09->Get("h_genweight");
//TH1D *h_genWeight10 =   (TH1D*)file10->Get("h_genweight");
TH1D *h_genWeight10_1 =   (TH1D*)file10_1->Get("h_genweight");
TH1D *h_genWeight11 =   (TH1D*)file11->Get("h_genweight");
TH1D *h_genWeight12 =   (TH1D*)file12->Get("h_genweight");
TH1D *h_genWeight13 =   (TH1D*)file13->Get("h_genweight");
TH1D *h_genWeight14 =   (TH1D*)file14->Get("h_genweight");
TH1D *h_genWeight15 =   (TH1D*)file15->Get("h_genweight");
TH1D *h_genWeight16 =   (TH1D*)file16->Get("h_genweight");
TH1D *h_genWeight17 =   (TH1D*)file17->Get("h_genweight");
TH1D *h_genWeight18 =   (TH1D*)file18->Get("h_genweight");
TH1D *h_genWeight19 =   (TH1D*)file19->Get("h_genweight");
TH1D *h_genWeight20 =   (TH1D*)file20->Get("h_genweight");
TH1D *h_genWeight21 =   (TH1D*)file21->Get("h_genweight");
TH1D *h_genWeight22 =   (TH1D*)file22->Get("h_genweight");
TH1D *h_genWeight23 =   (TH1D*)file23->Get("h_genweight");
TH1D *h_genWeight24 =   (TH1D*)file24->Get("h_genweight");
TH1D *h_genWeight25 =   (TH1D*)file25->Get("h_genweight");
//TH1D *h_genWeight26 =   (TH1D*)file26->Get("h_genweight");
TH1D *h_genWeight27 =   (TH1D*)file27->Get("h_genweight");
TH1D *h_genWeight28 =   (TH1D*)file28->Get("h_genweight");
TH1D *h_genWeight29 =   (TH1D*)file29->Get("h_genweight");
TH1D *h_genWeight30 =   (TH1D*)file30->Get("h_genweight");
TH1D *h_genWeight31 =   (TH1D*)file31->Get("h_genweight");
TH1D *h_genWeight32 =   (TH1D*)file32->Get("h_genweight");
TH1D *h_genWeight33 =   (TH1D*)file33->Get("h_genweight");
TH1D *h_genWeight34 =   (TH1D*)file34->Get("h_genweight");
TH1D *h_genWeight35 =   (TH1D*)file35->Get("h_genweight");
TH1D *h_genWeight36 =   (TH1D*)file36->Get("h_genweight");
TH1D *h_genWeight37 =   (TH1D*)file37->Get("h_genweight");
TH1D *h_genWeight38 =   (TH1D*)file38->Get("h_genweight");
TH1D *h_genWeight39 =   (TH1D*)file39->Get("h_genweight");
TH1D *h_genWeight40 =   (TH1D*)file40->Get("h_genweight");
TH1D *h_genWeight41 =   (TH1D*)file41->Get("h_genweight");
TH1D *h_genWeight42 =   (TH1D*)file42->Get("h_genweight");
//TH1D *h_genWeight43 =   (TH1D*)file43->Get("h_genweight");
TH1D *h_genWeight44 =   (TH1D*)file44->Get("h_genweight");
TH1D *h_genWeight45 =   (TH1D*)file45->Get("h_genweight");

vector<TTree*> allTree = {
    Tree02,Tree03,Tree04,Tree05,Tree06,Tree07,/*Tree08,*/Tree09,Tree10_1,Tree11,Tree12,Tree13,Tree14,Tree15,Tree16,Tree17,Tree18,Tree19,Tree20,Tree21,Tree22,Tree23,Tree24,Tree25,/*Tree26,*/Tree27,Tree28,Tree29,Tree30,Tree31,Tree32,Tree33,Tree34,Tree35,Tree36,Tree37,Tree38,Tree39,Tree40,Tree41,Tree42,/*Tree43,*/Tree44,Tree45
};
vector<TH1D*> allgenWeights = {
    h_genWeight02,h_genWeight03,h_genWeight04,h_genWeight05,h_genWeight06,h_genWeight07,/*h_genWeight08,*/h_genWeight09,h_genWeight10_1,h_genWeight11,h_genWeight12,h_genWeight13,h_genWeight14,h_genWeight15,h_genWeight16,h_genWeight17,h_genWeight18,h_genWeight19,h_genWeight20,h_genWeight21,h_genWeight22,h_genWeight23,h_genWeight24,h_genWeight25,/*h_genWeight26,*/h_genWeight27,h_genWeight28,h_genWeight29,h_genWeight30,h_genWeight31,h_genWeight32,h_genWeight33,h_genWeight34,h_genWeight35,h_genWeight36,h_genWeight37,h_genWeight38,h_genWeight39,h_genWeight40,h_genWeight41,h_genWeight42,/*h_genWeight43,*/h_genWeight44,h_genWeight45
};

/*
//TFile *file01_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESup/data.root");{{{
TFile *file02_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESup/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESup/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESup/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
TFile *file05_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESup/ttZJets_13TeV_madgraphMLM-pythia8.root.root");
TFile *file06_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESup/ttWJets_13TeV_madgraphMLM.root");
TFile *file07_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESup/ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root.root");
TFile *file08_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESup/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESup/WZ_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESup/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file11_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESup/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");
TFile *file12_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESup/ZZ_TuneCUETP8M1_13TeV-pythia8.root.root");
TFile *file13_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESup/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");
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


//TFile *file01_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESdown/data.root");
TFile *file02_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESdown/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESdown/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESdown/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
TFile *file05_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESdown/ttZJets_13TeV_madgraphMLM-pythia8.root.root");

TFile *file06_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESdown/ttWJets_13TeV_madgraphMLM.root");
TFile *file07_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESdown/ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root.root");
TFile *file08_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESdown/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESdown/WZ_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESdown/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file11_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESdown/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");
TFile *file12_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESdown/ZZ_TuneCUETP8M1_13TeV-pythia8.root.root");
TFile *file13_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JESdown/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");
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




//TFile *file01_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERup/data.root");
TFile *file02_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERup/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERup/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERup/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
TFile *file05_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERup/ttZJets_13TeV_madgraphMLM-pythia8.root.root");
TFile *file06_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERup/ttWJets_13TeV_madgraphMLM.root");
TFile *file07_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERup/ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root.root");
TFile *file08_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERup/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERup/WZ_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERup/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file11_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERup/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");
TFile *file12_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERup/ZZ_TuneCUETP8M1_13TeV-pythia8.root.root");
TFile *file13_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERup/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");
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

//TFile *file01_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERdown/data.root");
TFile *file02_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERdown/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERdown/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERdown/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
TFile *file05_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERdown/ttZJets_13TeV_madgraphMLM-pythia8.root.root");
TFile *file06_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERdown/ttWJets_13TeV_madgraphMLM.root");
TFile *file07_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERdown/ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8.root.root");//ttH
TFile *file08_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERdown/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERdown/WZ_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERdown/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file11_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERdown/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");
TFile *file12_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERdown/ZZ_TuneCUETP8M1_13TeV-pythia8.root.root");
TFile *file13_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v13_correctChargeSum_add2SSand2OS/JERdown/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");
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

                                                   

//TH1D *data_SR; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_SR; TH1D *TTGJets_SR; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_SR; TH1D *ttWJets_13TeV_madgraphMLM_SR;
//TH1D* background_SR;
TH1D* TTJets_SR;
TH1D* TTGJets_SR;
TH1D* ttZJets_SR;
TH1D* ttWJets_SR;
TH1D* ttH_SR;
TH1D* ttbb_SR;
TH1D* WZ_SR;
TH1D* WWTo2L2Nu_SR;
TH1D* WpWpJJ_SR;
TH1D* ZZ_SR;
TH1D* WGJets_SR;
TH1D* ZGJetsToLLG_SR;
TH1D* WWW_SR;
TH1D* WWZ_SR;
TH1D* WWG_SR;
TH1D* ZZZ_SR;
TH1D* WZZ_SR;
TH1D* WZG_SR;
TH1D* WGG_SR;
TH1D* ZGGJets_SR;
TH1D* WJetsToLNu_SR;
TH1D* DYJetsToTauTau_SR;
TH1D* tZq_ll_SR;
TH1D* ST_tW_antitop_SR;
TH1D* ST_tW_top_SR;
TH1D* TGJets_SR;
TH1D* THW_SR;
TH1D* THQ_SR;
TH1D* VHToNonbb_SR;
TH1D* ZHToTauTau_SR;
TH1D* ZH_HToBB_ZToLL_SR;
TH1D* GluGluHToZZTo4L_SR;
TH1D* GluGluHToBB_SR;
TH1D* GluGluHToGG_SR;
TH1D* GluGluHToMuMu_SR;
TH1D* GluGluHToTauTau_SR;
TH1D* GluGluHToWWTo2L2Nu_SR;
TH1D* GluGluHToWWToLNuQQ_SR;
TH1D* VBFHToWWTo2L2Nu_SR;
TH1D* VBFHToGG_SR;
TH1D* TTTT_SR;

TH1D *QCD_HT1000to1500_SR; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_SR; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_SR; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_SR; TH1D *TTWJets_SR; TH1D *TTZ_SR; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8SR; 
TH1D *background_SR;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_SR;

TH1D *data_P1; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_P1; TH1D *TTGJets_P1; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_P1; TH1D *ttWJets_13TeV_madgraphMLM_P1; 
TH1D *QCD_HT1000to1500_P1; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_P1; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_P1; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_P1; TH1D *TTWJets_P1; TH1D *TTZ_P1; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8P1; 
TH1D *background_P1;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_P1;

TH1D *data_P2; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_P2; TH1D *TTGJets_P2; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_P2; TH1D *ttWJets_13TeV_madgraphMLM_P2; 
TH1D *QCD_HT1000to1500_P2; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_P2; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_P2; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_P2; TH1D *TTWJets_P2; TH1D *TTZ_P2; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8P2; 
TH1D *background_P2;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_P2;

TH1D *data_F1; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_F1; TH1D *TTGJets_F1; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_F1; TH1D *ttWJets_13TeV_madgraphMLM_F1; 
TH1D *QCD_HT1000to1500_F1; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_F1; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_F1; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_F1; TH1D *TTWJets_F1; TH1D *TTZ_F1; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8F1; 
TH1D *background_F1;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_F1;

TH1D *data_F2; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_F2; TH1D *TTGJets_F2; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_F2; TH1D *ttWJets_13TeV_madgraphMLM_F2; 
TH1D *QCD_HT1000to1500_F2; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_F2; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_F2; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_F2; TH1D *TTWJets_F2; TH1D *TTZ_F2; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8F2; 
TH1D *background_F2;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_F2;

TH1D *data_B1; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_B1; TH1D *TTGJets_B1; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_B1; TH1D *ttWJets_13TeV_madgraphMLM_B1; 
TH1D *QCD_HT1000to1500_B1; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_B1; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_B1; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_B1; TH1D *TTWJets_B1; TH1D *TTZ_B1; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8B1; 
TH1D *background_B1;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_B1;

TH1D *data_B2; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_B2; TH1D *TTGJets_B2; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_B2; TH1D *ttWJets_13TeV_madgraphMLM_B2; 
TH1D *QCD_HT1000to1500_B2; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_B2; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_B2; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_B2; TH1D *TTWJets_B2; TH1D *TTZ_B2; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8B2; 
TH1D *background_B2;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_B2;

TH1D *data_Z1; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_Z1; TH1D *TTGJets_Z1; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_Z1; TH1D *ttWJets_13TeV_madgraphMLM_Z1; 
TH1D *QCD_HT1000to1500_Z1; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_Z1; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_Z1; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_Z1; TH1D *TTWJets_Z1; TH1D *TTZ_Z1; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8Z1; 
TH1D *background_Z1;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_Z1;

TH1D *data_Z2; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_Z2; TH1D *TTGJets_Z2; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_Z2; TH1D *ttWJets_13TeV_madgraphMLM_Z2; 
TH1D *QCD_HT1000to1500_Z2; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_Z2; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_Z2; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_Z2; TH1D *TTWJets_Z2; TH1D *TTZ_Z2; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8Z2; 
TH1D *background_Z2;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_Z2;

TH1D *data_W1; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_W1; TH1D *TTGJets_W1; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_W1; TH1D *ttWJets_13TeV_madgraphMLM_W1; 
TH1D *QCD_HT1000to1500_W1; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_W1; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_W1; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_W1; TH1D *TTWJets_W1; TH1D *TTZ_W1; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8W1; 
TH1D *background_W1;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_W1;

TH1D *data_W2; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_W2; TH1D *TTGJets_W2; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_W2; TH1D *ttWJets_13TeV_madgraphMLM_W2; 
TH1D *QCD_HT1000to1500_W2; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_W2; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_W2; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_W2; TH1D *TTWJets_W2; TH1D *TTZ_W2; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8W2; 
TH1D *background_W2;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_W2;

TH1D *data_T1; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_T1; TH1D *TTGJets_T1; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_T1; TH1D *ttWJets_13TeV_madgraphMLM_T1; 
TH1D *QCD_HT1000to1500_T1; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_T1; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_T1; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_T1; TH1D *TTWJets_T1; TH1D *TTZ_T1; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8T1; 
TH1D *background_T1;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_T1;

TH1D *data_T2; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_T2; TH1D *TTGJets_T2; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_T2; TH1D *ttWJets_13TeV_madgraphMLM_T2; 
TH1D *QCD_HT1000to1500_T2; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_T2; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_T2; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_T2; TH1D *TTWJets_T2; TH1D *TTZ_T2; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8T2; 
TH1D *background_T2;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_T2;

TH1D *data_J1; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_J1; TH1D *TTGJets_J1; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_J1; TH1D *ttWJets_13TeV_madgraphMLM_J1; 
TH1D *QCD_HT1000to1500_J1; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_J1; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_J1; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_J1; TH1D *TTWJets_J1; TH1D *TTZ_J1; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8J1; 
TH1D *background_J1;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_J1;

TH1D *data_J2; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_J2; TH1D *TTGJets_J2; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_J2; TH1D *ttWJets_13TeV_madgraphMLM_J2; 
TH1D *QCD_HT1000to1500_J2; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_J2; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_J2; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_J2; TH1D *TTWJets_J2; TH1D *TTZ_J2; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8J2; 
TH1D *background_J2;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_J2;

TH1D *data_J3; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_J3; TH1D *TTGJets_J3; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_J3; TH1D *ttWJets_13TeV_madgraphMLM_J3; 
TH1D *QCD_HT1000to1500_J3; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_J3; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_J3; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_J3; TH1D *TTWJets_J3; TH1D *TTZ_J3; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8J3; 
TH1D *background_J3;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_J3;

TH1D *data_J4; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_J4; TH1D *TTGJets_J4; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_J4; TH1D *ttWJets_13TeV_madgraphMLM_J4; 
TH1D *QCD_HT1000to1500_J4; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_J4; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_J4; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_J4; TH1D *TTWJets_J4; TH1D *TTZ_J4; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8J4; 
TH1D *background_J4;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_J4;

TH1D *data_qcd1; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_qcd1; TH1D *TTGJets_qcd1; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_qcd1; TH1D *ttWJets_13TeV_madgraphMLM_qcd1;
TH1D *QCD_HT1000to1500_qcd1; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_qcd1; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_qcd1; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_qcd1; TH1D *TTWJets_qcd1; TH1D *TTZ_qcd1; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8qcd1;
TH1D *background_qcd1;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_qcd1;

TH1D *data_qcd2; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_qcd2; TH1D *TTGJets_qcd2; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_qcd2; TH1D *ttWJets_13TeV_madgraphMLM_qcd2;
TH1D *QCD_HT1000to1500_qcd2; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_qcd2; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_qcd2; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_qcd2; TH1D *TTWJets_qcd2; TH1D *TTZ_qcd2; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8qcd2;
TH1D *background_qcd2;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_qcd2;

TH1D *data_pdf1; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_pdf1; TH1D *TTGJets_pdf1; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_pdf1; TH1D *ttWJets_13TeV_madgraphMLM_pdf1;
TH1D *QCD_HT1000to1500_pdf1; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_pdf1; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_pdf1; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_pdf1; TH1D *TTWJets_pdf1; TH1D *TTZ_pdf1; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8pdf1;
TH1D *background_pdf1;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_pdf1;

TH1D *data_pdf2; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_pdf2; TH1D *TTGJets_pdf2; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_pdf2; TH1D *ttWJets_13TeV_madgraphMLM_pdf2;
TH1D *QCD_HT1000to1500_pdf2; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_pdf2; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_pdf2; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_pdf2; TH1D *TTWJets_pdf2; TH1D *TTZ_pdf2; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8pdf2;
TH1D *background_pdf2;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_pdf2;


TH1D *data_TR1; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_TR1; TH1D *TTGJets_TR1; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_TR1; TH1D *ttWJets_13TeV_madgraphMLM_TR1;
TH1D *QCD_HT1000to1500_TR1; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_TR1; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_TR1; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_TR1; TH1D *TTWJets_TR1; TH1D *TTZ_TR1; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8TR1;
TH1D *background_TR1;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_TR1;


TH1D *data_TR2; TH1D *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_TR2; TH1D *TTGJets_TR2; TH1D *ttZJets_13TeV_madgraphMLM-pythia8.root_TR2; TH1D *ttWJets_13TeV_madgraphMLM_TR2;
TH1D *QCD_HT1000to1500_TR2; TH1D *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_TR2; TH1D *WZ_TuneCUETP8M1_13TeV-pythia8_TR2; TH1D *WW_TuneCUETP8M1_13TeV-pythia8_TR2; TH1D *TTWJets_TR2; TH1D *TTZ_TR2; TH1D *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8TR2;
TH1D *background_TR2;
TH1D *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_TR2;
*/
#include "TH1.h"
