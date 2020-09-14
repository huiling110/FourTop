#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"

//void MakeHistos(char CUT[1000],const char *plot,int BIN,float MIN,float MAX,int JETSyst,
//		/*TH1F* &data_func,*/ TH1F* &background_func,TH1F* &TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_func,TH1F* &QCD_HT300to500_func,TH1F* &ttZJets_13TeV_madgraphMLM-pythia8.root_func,TH1F* &ttWJets_13TeV_madgraphMLM_func,TH1F* &QCD_HT1000to1500_func,TH1F* &ttbb_4FS_ckm_amcatnlo_madspin_pythia8_func,TH1F* &WZ_TuneCUETP8M1_13TeV-pythia8_func,
//		TH1F* &WW_TuneCUETP8M1_13TeV-pythia8_func,TH1F* &TTWJets_func,TH1F* &TTZ_func, TH1F* &WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_func,
//		TH1F* &TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8func);
void MakeHistoErrors(int m, TH1F* &histo_SR, TH1F* histo_P1, TH1F* histo_P2, TH1F* histo_F1, TH1F* histo_F2, TH1F* histo_B1, TH1F* histo_B2, TH1F* histo_Z1, TH1F* histo_Z2, TH1F* histo_W1, TH1F* histo_W2, TH1F* histo_T1, TH1F* histo_T2, TH1F* histo_J1, TH1F* histo_J2, TH1F* histo_J3, TH1F* histo_J4, TH1F* histo_qcd1, TH1F* histo_qcd2, TH1F* histo_pdf1, TH1F* histo_pdf2, TH1F* histo_TR1, TH1F* histo_TR2);

void CloneHistos();

void MakeHistos(char CUT[1000],const char *plot,int BIN,float MIN,float MAX,int JETSyst,
               /* TH1F* &data_func,*/TH1F* &background_func,TH1F* &TTJets_func,/*TH1F* &QCD_HT300to500_func,*/TH1F* &ttZJets_func,  TH1F*  &ttWJets_func, /*TH1F* &QCD_HT1000to1500_func,*/TH1F* &ttbb_func,TH1F* &WZ_func,
                 /*TH1F* &WW_func,*/TH1F* &WpWpJJ_func,/*TH1F* &TTZToQQ_func,*//*TH1F* &TT_func,*/ TH1F* &TTTT_func);


int SigSF = 1;
//float LUMI  = 41500.0; //float LUMI = 36733; //36.773 /fb
float LUMI = 35900; //fb
//?where to get the more precise LUMI?
//where to get this LUMI//what's these number?where to get these number?
//SIGNAL
double wTTTT = (SigSF*LUMI*0.009103);///TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root:  Positive:1709406  Negtive:704054
//tt
double wTTJets = (LUMI*746.7)/(29509487-14335648);//746.7 // TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root:  Positive:29509487  Negtive:14335648
//double wTTGJets = (LUMI*3.773)/(-)//
double wttZJets = (LUMI*0.6559)/(9883364-0) ;// ttZJets_13TeV_madgraphMLM-pythia8.root:  Positive:9883364  Negtive:0      //Special care is taken when scaling the ttZ background to the cross-section= (LUMI*)/(-)
double wttWJets = (LUMI*0.2014)/(6700440-0);//ttWJets_13TeV_madgraphMLM.root:  Positive:6700440  Negtive:0  ;
//double wttH= (LUMI*0.3372)/(-)//
double wttbb= (LUMI*1.393)/(2556073-1427835);//ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root:  Positive:2556073  Negtive:1427835  ;
//diboson and triboson an w/z+jets
double wWZ= (LUMI*2.343)/(2997571-0);//WZ_TuneCUETP8M1_13TeV-pythia8.root:  Positive:2997571  Negtive:0  ;
//double wWW= (LUMI*6.430)/(-);//?something wrong with ntuple
double wWpWpJJ= (LUMI*0.05390)/(149681-0);//WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root:  Positive:149681  Negtive:0  ;
//double wZZ  = (LUMI*1.016)/(-);//


/*
double wWGJets = (LUMI*1.269)/(5077680-0);//WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root:  Positive:5077680  Negtive:0  ;
double wZGJetsToLLG = (LUMI*0.1319)/(498406-0);//ZGJetsToLLG_EW_LO_13TeV-sherpa.root:  Positive:498406  Negtive:394  ;
double wWWW= (LUMI*0.2086)/(-);//WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root:  Positive:225269  Negtive:14731  ;
double wWWZ= (LUMI*0.1651)/(-);//
double wWWG = (LUMI*0.2147)/(-);//WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root:  Positive:913515  Negtive:85885  ;
double wZZZ= (LUMI*0.01398)/(-);//ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root:  Positive:231217  Negtive:18020  ;
double wWZZ= (LUMI*0.05565)/(-);//WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root:  Positive:231583  Negtive:15217  ;
double wWZG= (LUMI*0.04123)/(-);//WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root:  Positive:921527  Negtive:76673  ;
double wWGGJets = (LUMI*1.711)/(-);//
double wZGGJets= (LUMI*0.3717)/(-);//ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8.root:  Positive:291922  Negtive:0  ;
double wWJetsToLNu= (LUMI*50300)/(-) //data driven
//?missing ZJets?= (LUMI*)/(-)
//Drell-Yan
double wDYJetsToTauTau= (LUMI*1983)/(-)//
//single top= (LUMI*)/(-)
double wtZq_ll= (LUMI*0.07358)/(-)
double wtZq_nunu= (LUMI*)/(-)
double wST_tW_antitop= (LUMI*38.06)/(-)
double wST_tW_top= (LUMI*38.09)/(-)
double wTGJets= (LUMI*2.967)/(-)
double wTHW= (LUMI*0.1467)/(-)
double wTHQ= (LUMI*0.8816)/(-)
//H = (LUMI*)/(-)
double wVHToNonbb= (LUMI*2.137)/(-)
double wZHToTauTau= (LUMI*0.7524)/(-)
double wZH_HToBB_ZToLL= (LUMI*0.07523)/(-)
double wGluGluHToZZTo4L= (LUMI*2.999)/(-)
double wGluGluHToBB= (LUMI*32.10)/(-)
double wGluGluHToGG= (LUMI*31.98)/(-)
double wGluGluHToMuMu= (LUMI*29.99)/(-)
double wGluGluHToTauTau= (LUMI*30.52)/(-)
double wGluGluHToWWTo2L2Nu= (LUMI*30.52)/(-)
double wGluGluHToWWToLNuQQ= (LUMI*29.99)/(-)
double wVBFHToWWToLNuQQ= (LUMI*3.769)/(-)
double wVBFHToWWTo2L2Nu= (LUMI*3.769)/(-)
double wVBFHToTauTau= (LUMI*)/(-)
double wVBFHToMuMu= (LUMI*)/(-)
double wVBFHToGG= (LUMI*3.992)/(-)
double wVBFHToBB= (LUMI*)/(-)
double wVBF_HToZZTo4L= (LUMI*3.769)/(-)
*/
//HH count as minor
//minor
/*
float wTTTT = (SigSF*LUMI*0.009103)/(1739606-716434);//0.009103//9.103e-03 +- 1.401e-05 pb
float wQCD200to300 = (LUMI*1710000)/(18722416-0); //1.710e+06 +- 1.626e+03 pb
float wQCD300to500 = (LUMI*347300)/(17035891-0); //351300 //3.473e+05 +- 3.327e+02 pb
float wQCD500to700 = (LUMI*32200)/(18560541-0);//39750 //3.220e+04 +- 3.100e+01 pb
float wQCD700to1000 = (LUMI*6839)/(15629253-0);// 6.839e+03 +- 6.602e+00 pb
float wQCD1000to1500 = (LUMI*1207)/(4607953-0);//1.207e+03 +- 1.167e+00 pb
float wQCD1500to2000 = (LUMI*120.1)/(3970819-0);//1.201e+02 +- 1.160e-01 pb 
float wQCD2000toIn = (LUMI*25.24)/(1991645-0);//2.524e+01 +- 2.436e-02 pb 
float wTTJets = (LUMI*746.7)/(29509487-14335648);//7.467e+02 +- 2.820e+00 pb
float wTT = (LUMI*730.6)/(69986374-0);   //750 //7.306e+02 +- 5.572e-01 pb
float wTTWJets = (LUMI*0.4062)/(631804-201494);// 4.062e-01 +- 8.103e-04 pb
float wTTZ = (LUMI*0.5297)/(550282-199118);//5.297e-01 +- 7.941e-04 pb
*/
//
//float w0700 = SigSF*(0.5*0.5*5.820 *0.25*LUMI/(386981-1075)); //SIG1/*{{{*/
//float w40 = (3.05*LUMI/(4297198-1269149)); //WZTo1L3Nu/*}}}*/

//TFile *file01 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/NoJEC/data.root");/*{{{*/
TFile *file02 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/NoJEC/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/NoJEC/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
//TFile *file04 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/NoJEC/QCD_HT300to500.root");//TTGJets
TFile *file05 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/NoJEC/ttZJets_13TeV_madgraphMLM-pythia8.root");
TFile *file06 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/NoJEC/ttWJets_13TeV_madgraphMLM.root");
//TFile *file07 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/NoJEC/QCD_HT1000to1500.root");//ttH
TFile *file08 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/NoJEC/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/NoJEC/WZ_TuneCUETP8M1_13TeV-pythia8.root");
//TFile *file10 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/NoJEC/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file11 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/NoJEC/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");//?missing this in other places
//TFile *file12 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/NoJEC/TTZToQQ.root");//ZZ
//TFile *file13 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/NoJEC/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");//
//TTree *Tree01 = (TTree*)file01->Get("tree");
TTree *Tree02 = (TTree*)file02->Get("tree");
TTree *Tree03 = (TTree*)file03->Get("tree");
//TTree *Tree04 = (TTree*)file04->Get("tree");
TTree *Tree05 = (TTree*)file05->Get("tree");
TTree *Tree06 = (TTree*)file06->Get("tree");
//TTree *Tree07 = (TTree*)file07->Get("tree");
TTree *Tree08 = (TTree*)file08->Get("tree");
TTree *Tree09 = (TTree*)file09->Get("tree");
//TTree *Tree10 = (TTree*)file10->Get("tree");
TTree *Tree11 = (TTree*)file11->Get("tree");
//TTree *Tree12 = (TTree*)file12->Get("tree");
//TTree *Tree13 = (TTree*)file13->Get("tree");
/*}}}*/


/*
//TFile *file01_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESup/data.root");
TFile *file02_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESup/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESup/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESup/QCD_HT300to500.root");
TFile *file05_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESup/ttZJets_13TeV_madgraphMLM-pythia8.root.root");
TFile *file06_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESup/ttWJets_13TeV_madgraphMLM.root");
TFile *file07_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESup/QCD_HT1000to1500.root");
TFile *file08_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESup/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESup/WZ_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESup/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file11_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESup/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");
TFile *file12_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESup/TTZToQQ.root");
TFile *file13_J1 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESup/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");
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


//TFile *file01_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESdown/data.root");
TFile *file02_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESdown/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESdown/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESdown/QCD_HT300to500.root");
TFile *file05_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESdown/ttZJets_13TeV_madgraphMLM-pythia8.root.root");

TFile *file06_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESdown/ttWJets_13TeV_madgraphMLM.root");
TFile *file07_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESdown/QCD_HT1000to1500.root");
TFile *file08_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESdown/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESdown/WZ_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESdown/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file11_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESdown/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");
TFile *file12_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESdown/TTZToQQ.root");
TFile *file13_J2 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JESdown/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");
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




//TFile *file01_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERup/data.root");
TFile *file02_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERup/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERup/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERup/QCD_HT300to500.root");
TFile *file05_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERup/ttZJets_13TeV_madgraphMLM-pythia8.root.root");
TFile *file06_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERup/ttWJets_13TeV_madgraphMLM.root");
TFile *file07_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERup/QCD_HT1000to1500.root");
TFile *file08_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERup/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERup/WZ_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERup/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file11_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERup/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");
TFile *file12_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERup/TTZToQQ.root");
TFile *file13_J3 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERup/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");
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

//TFile *file01_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERdown/data.root");
TFile *file02_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERdown/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");
TFile *file03_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERdown/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
TFile *file04_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERdown/QCD_HT300to500.root");
TFile *file05_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERdown/ttZJets_13TeV_madgraphMLM-pythia8.root.root");
TFile *file06_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERdown/ttWJets_13TeV_madgraphMLM.root");
TFile *file07_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERdown/QCD_HT1000to1500.root");//ttH
TFile *file08_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERdown/ttbb_4FS_ckm_amcatnlo_madspin_pythia8.root");
TFile *file09_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERdown/WZ_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file10_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERdown/WW_TuneCUETP8M1_13TeV-pythia8.root");
TFile *file11_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERdown/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8.root");
TFile *file12_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERdown/TTZToQQ.root");
TFile *file13_J4 = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/JERdown/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph.root");
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
*/

                                                   

//TH1F *data_SR; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_SR; TH1F *QCD_HT300to500_SR; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_SR; TH1F *ttWJets_13TeV_madgraphMLM_SR;
TH1F* background_SR;
TH1F* TTJets_SR;
TH1F* ttZJets_SR;
TH1F* ttWJets_SR;
TH1F* ttbb_SR;
TH1F* WZ_SR;
TH1F* WpWpJJ_SR;
TH1F* TTTT_SR;

/* 
TH1F *QCD_HT1000to1500_SR; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_SR; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_SR; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_SR; TH1F *TTWJets_SR; TH1F *TTZ_SR; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8SR; 
TH1F *background_SR;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_SR;

TH1F *data_P1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_P1; TH1F *QCD_HT300to500_P1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_P1; TH1F *ttWJets_13TeV_madgraphMLM_P1; 
TH1F *QCD_HT1000to1500_P1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_P1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_P1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_P1; TH1F *TTWJets_P1; TH1F *TTZ_P1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8P1; 
TH1F *background_P1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_P1;

TH1F *data_P2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_P2; TH1F *QCD_HT300to500_P2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_P2; TH1F *ttWJets_13TeV_madgraphMLM_P2; 
TH1F *QCD_HT1000to1500_P2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_P2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_P2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_P2; TH1F *TTWJets_P2; TH1F *TTZ_P2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8P2; 
TH1F *background_P2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_P2;

TH1F *data_F1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_F1; TH1F *QCD_HT300to500_F1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_F1; TH1F *ttWJets_13TeV_madgraphMLM_F1; 
TH1F *QCD_HT1000to1500_F1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_F1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_F1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_F1; TH1F *TTWJets_F1; TH1F *TTZ_F1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8F1; 
TH1F *background_F1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_F1;

TH1F *data_F2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_F2; TH1F *QCD_HT300to500_F2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_F2; TH1F *ttWJets_13TeV_madgraphMLM_F2; 
TH1F *QCD_HT1000to1500_F2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_F2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_F2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_F2; TH1F *TTWJets_F2; TH1F *TTZ_F2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8F2; 
TH1F *background_F2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_F2;

TH1F *data_B1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_B1; TH1F *QCD_HT300to500_B1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_B1; TH1F *ttWJets_13TeV_madgraphMLM_B1; 
TH1F *QCD_HT1000to1500_B1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_B1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_B1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_B1; TH1F *TTWJets_B1; TH1F *TTZ_B1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8B1; 
TH1F *background_B1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_B1;

TH1F *data_B2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_B2; TH1F *QCD_HT300to500_B2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_B2; TH1F *ttWJets_13TeV_madgraphMLM_B2; 
TH1F *QCD_HT1000to1500_B2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_B2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_B2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_B2; TH1F *TTWJets_B2; TH1F *TTZ_B2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8B2; 
TH1F *background_B2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_B2;

TH1F *data_Z1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_Z1; TH1F *QCD_HT300to500_Z1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_Z1; TH1F *ttWJets_13TeV_madgraphMLM_Z1; 
TH1F *QCD_HT1000to1500_Z1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_Z1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_Z1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_Z1; TH1F *TTWJets_Z1; TH1F *TTZ_Z1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8Z1; 
TH1F *background_Z1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_Z1;

TH1F *data_Z2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_Z2; TH1F *QCD_HT300to500_Z2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_Z2; TH1F *ttWJets_13TeV_madgraphMLM_Z2; 
TH1F *QCD_HT1000to1500_Z2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_Z2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_Z2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_Z2; TH1F *TTWJets_Z2; TH1F *TTZ_Z2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8Z2; 
TH1F *background_Z2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_Z2;

TH1F *data_W1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_W1; TH1F *QCD_HT300to500_W1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_W1; TH1F *ttWJets_13TeV_madgraphMLM_W1; 
TH1F *QCD_HT1000to1500_W1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_W1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_W1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_W1; TH1F *TTWJets_W1; TH1F *TTZ_W1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8W1; 
TH1F *background_W1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_W1;

TH1F *data_W2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_W2; TH1F *QCD_HT300to500_W2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_W2; TH1F *ttWJets_13TeV_madgraphMLM_W2; 
TH1F *QCD_HT1000to1500_W2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_W2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_W2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_W2; TH1F *TTWJets_W2; TH1F *TTZ_W2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8W2; 
TH1F *background_W2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_W2;

TH1F *data_T1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_T1; TH1F *QCD_HT300to500_T1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_T1; TH1F *ttWJets_13TeV_madgraphMLM_T1; 
TH1F *QCD_HT1000to1500_T1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_T1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_T1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_T1; TH1F *TTWJets_T1; TH1F *TTZ_T1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8T1; 
TH1F *background_T1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_T1;

TH1F *data_T2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_T2; TH1F *QCD_HT300to500_T2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_T2; TH1F *ttWJets_13TeV_madgraphMLM_T2; 
TH1F *QCD_HT1000to1500_T2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_T2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_T2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_T2; TH1F *TTWJets_T2; TH1F *TTZ_T2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8T2; 
TH1F *background_T2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_T2;

TH1F *data_J1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_J1; TH1F *QCD_HT300to500_J1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_J1; TH1F *ttWJets_13TeV_madgraphMLM_J1; 
TH1F *QCD_HT1000to1500_J1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_J1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_J1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_J1; TH1F *TTWJets_J1; TH1F *TTZ_J1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8J1; 
TH1F *background_J1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_J1;

TH1F *data_J2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_J2; TH1F *QCD_HT300to500_J2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_J2; TH1F *ttWJets_13TeV_madgraphMLM_J2; 
TH1F *QCD_HT1000to1500_J2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_J2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_J2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_J2; TH1F *TTWJets_J2; TH1F *TTZ_J2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8J2; 
TH1F *background_J2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_J2;

TH1F *data_J3; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_J3; TH1F *QCD_HT300to500_J3; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_J3; TH1F *ttWJets_13TeV_madgraphMLM_J3; 
TH1F *QCD_HT1000to1500_J3; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_J3; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_J3; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_J3; TH1F *TTWJets_J3; TH1F *TTZ_J3; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8J3; 
TH1F *background_J3;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_J3;

TH1F *data_J4; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_J4; TH1F *QCD_HT300to500_J4; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_J4; TH1F *ttWJets_13TeV_madgraphMLM_J4; 
TH1F *QCD_HT1000to1500_J4; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_J4; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_J4; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_J4; TH1F *TTWJets_J4; TH1F *TTZ_J4; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8J4; 
TH1F *background_J4;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_J4;

TH1F *data_qcd1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_qcd1; TH1F *QCD_HT300to500_qcd1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_qcd1; TH1F *ttWJets_13TeV_madgraphMLM_qcd1;
TH1F *QCD_HT1000to1500_qcd1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_qcd1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_qcd1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_qcd1; TH1F *TTWJets_qcd1; TH1F *TTZ_qcd1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8qcd1;
TH1F *background_qcd1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_qcd1;

TH1F *data_qcd2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_qcd2; TH1F *QCD_HT300to500_qcd2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_qcd2; TH1F *ttWJets_13TeV_madgraphMLM_qcd2;
TH1F *QCD_HT1000to1500_qcd2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_qcd2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_qcd2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_qcd2; TH1F *TTWJets_qcd2; TH1F *TTZ_qcd2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8qcd2;
TH1F *background_qcd2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_qcd2;

TH1F *data_pdf1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_pdf1; TH1F *QCD_HT300to500_pdf1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_pdf1; TH1F *ttWJets_13TeV_madgraphMLM_pdf1;
TH1F *QCD_HT1000to1500_pdf1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_pdf1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_pdf1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_pdf1; TH1F *TTWJets_pdf1; TH1F *TTZ_pdf1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8pdf1;
TH1F *background_pdf1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_pdf1;

TH1F *data_pdf2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_pdf2; TH1F *QCD_HT300to500_pdf2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_pdf2; TH1F *ttWJets_13TeV_madgraphMLM_pdf2;
TH1F *QCD_HT1000to1500_pdf2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_pdf2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_pdf2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_pdf2; TH1F *TTWJets_pdf2; TH1F *TTZ_pdf2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8pdf2;
TH1F *background_pdf2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_pdf2;


TH1F *data_TR1; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_TR1; TH1F *QCD_HT300to500_TR1; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_TR1; TH1F *ttWJets_13TeV_madgraphMLM_TR1;
TH1F *QCD_HT1000to1500_TR1; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_TR1; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_TR1; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_TR1; TH1F *TTWJets_TR1; TH1F *TTZ_TR1; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8TR1;
TH1F *background_TR1;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_TR1;


TH1F *data_TR2; TH1F *TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_TR2; TH1F *QCD_HT300to500_TR2; TH1F *ttZJets_13TeV_madgraphMLM-pythia8.root_TR2; TH1F *ttWJets_13TeV_madgraphMLM_TR2;
TH1F *QCD_HT1000to1500_TR2; TH1F *ttbb_4FS_ckm_amcatnlo_madspin_pythia8_TR2; TH1F *WZ_TuneCUETP8M1_13TeV-pythia8_TR2; TH1F *WW_TuneCUETP8M1_13TeV-pythia8_TR2; TH1F *TTWJets_TR2; TH1F *TTZ_TR2; TH1F *TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8TR2;
TH1F *background_TR2;
TH1F *WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_TR2;
*/
