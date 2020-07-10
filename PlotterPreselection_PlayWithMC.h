#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"





void MakeHistos(char CUT[1000],const char *plot,int BIN,float MIN,float MAX,int JETSyst,
		/*TH1F* &data_func,*/ TH1F* &background_func,TH1F* &QCD_HT200to300_func,TH1F* &QCD_HT300to500_func,TH1F* &QCD_HT500to700_func,TH1F* &QCD_HT700to1000_func,TH1F* &QCD_HT1000to1500_func,TH1F* &QCD_HT1500to2000_func,TH1F* &QCD_HT2000toIn_func,
		TH1F* &TTJets_func,TH1F* &TTWJets_func,TH1F* &TTZ_func, TH1F* &TT_func,
		TH1F* &TTTT_func);
void MakeHistoErrors(int m, TH1F* &histo_SR, TH1F* histo_P1, TH1F* histo_P2, TH1F* histo_F1, TH1F* histo_F2, TH1F* histo_B1, TH1F* histo_B2, TH1F* histo_Z1, TH1F* histo_Z2, TH1F* histo_W1, TH1F* histo_W2, TH1F* histo_T1, TH1F* histo_T2, TH1F* histo_J1, TH1F* histo_J2, TH1F* histo_J3, TH1F* histo_J4, TH1F* histo_qcd1, TH1F* histo_qcd2, TH1F* histo_pdf1, TH1F* histo_pdf2, TH1F* histo_TR1, TH1F* histo_TR2);
void CloneHistos();

int SigSF = 1;
//float LUMI  = 41500.0; 
float LUMI = 36733; //36.773 /fb
//where to get this LUMI
//what's these number?where to get these number?
//
//                pb
float wTTTT = (SigSF*LUMI*0.009103)/(1739606-716434);//0.009103//9.103e-03 +- 1.401e-05 pb
float wQCD200to300 = (LUMI*1710000)/(18722416-0); //1.710e+06 +- 1.626e+03 pb
float wQCD300to500 = (LUMI*347300)/(17035891-0); //351300 //3.473e+05 +- 3.327e+02 pb
float wQCD500to700 = (LUMI*32200)/(18560541-0);//39750 //3.220e+04 +- 3.100e+01 pb
float wQCD700to1000 = (LUMI*6839)/(15629253-0);// 6.839e+03 +- 6.602e+00 pb
float wQCD1000to1500 = (LUMI*1207)/(4607953-0);//1.207e+03 +- 1.167e+00 pb
float wQCD1500to2000 = (LUMI*1201)/(3970819-0);//1.201e+02 +- 1.160e-01 pb 
float wQCD2000toIn = (LUMI*25.24)/(1991645-0);//2.524e+01 +- 2.436e-02 pb 
float wTTJets = (LUMI*746.7)/(29509487-14335648);//7.467e+02 +- 2.820e+00 pb
float wTT = (LUMI*730.6)/(69986374-0);   //750 //7.306e+02 +- 5.572e-01 pb
float wTTWJets = (LUMI*0.4062)/(631804-201494);// 4.062e-01 +- 8.103e-04 pb
float wTTZ = (LUMI*0.5297)/(550282-199118);//5.297e-01 +- 7.941e-04 pb

//QCD_HT200to300.root:  Positive:18722416  Negtive:0  ;/*{{{*/
//QCD_HT300to500.root:  Positive:17035891  Negtive:0  ;
//QCD_HT500to700.root:  Positive:18560541  Negtive:0  ;
//QCD_HT700to1000.root:  Positive:15629253  Negtive:0  ;
//QCD_HT1000to1500.root:  Positive:4607953  Negtive:0  ;
//QCD_HT1500to2000.root:  Positive:3970819  Negtive:0  ;
//QCD_HT2000toIn.root:  Positive:1991645  Negtive:0  ;
//TTJets.root:  Positive:29509487  Negtive:14335648  ;
//TTWJetsToQQ.root:  Positive:631804  Negtive:201494  ;
//TTZToQQ.root:  Positive:550282  Negtive:199118  ;
//TTTT.root:  Positive:1739606  Negtive:716434  ;/*}}}*/
//TT.root:  Positive:69986374  Negtive:0  ;
//
//float w0700 = SigSF*(0.5*0.5*5.820 *0.25*LUMI/(386981-1075)); //SIG1/*{{{*/
//float w40 = (3.05*LUMI/(4297198-1269149)); //WZTo1L3Nu/*}}}*/

//TFile *file01 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/data.root");/*{{{*/
TFile *file02 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/TTTT.root");
TFile *file03 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/QCD_HT200to300.root");
TFile *file04 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/QCD_HT300to500.root");
TFile *file05 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/QCD_HT500to700.root");
TFile *file06 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/QCD_HT700to1000.root");
TFile *file07 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/QCD_HT1000to1500.root");
TFile *file08 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/QCD_HT1500to2000.root");
TFile *file09 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/QCD_HT2000toIn.root");
TFile *file10 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/TTJets.root");
TFile *file11 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/TTWJetsToQQ.root");
TFile *file12 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/TTZToQQ.root");
TFile *file13 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/TT.root");
//TTree *Tree01 = (TTree*)file01->Get("tree");
TTree *Tree02 = (TTree*)file02->Get("tree");
TTree *Tree03 = (TTree*)file03->Get("tree");
TTree *Tree04 = (TTree*)file04->Get("tree");
TTree *Tree05 = (TTree*)file05->Get("tree");
TTree *Tree06 = (TTree*)file06->Get("tree");
TTree *Tree07 = (TTree*)file07->Get("tree");
TTree *Tree08 = (TTree*)file08->Get("tree");
TTree *Tree09 = (TTree*)file09->Get("tree");
TTree *Tree10 = (TTree*)file10->Get("tree");
TTree *Tree11 = (TTree*)file11->Get("tree");
TTree *Tree12 = (TTree*)file12->Get("tree");
TTree *Tree13 = (TTree*)file13->Get("tree");
/*}}}*/



//TFile *file01_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESup/data.root");
TFile *file02_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESup/TTTT.root");
TFile *file03_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESup/QCD_HT200to300.root");
TFile *file04_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESup/QCD_HT300to500.root");
TFile *file05_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESup/QCD_HT500to700.root");
TFile *file06_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESup/QCD_HT700to1000.root");
TFile *file07_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESup/QCD_HT1000to1500.root");
TFile *file08_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESup/QCD_HT1500to2000.root");
TFile *file09_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESup/QCD_HT2000toIn.root");
TFile *file10_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESup/TTJets.root");
TFile *file11_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESup/TTWJetsToQQ.root");
TFile *file12_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESup/TTZToQQ.root");
TFile *file13_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESup/TT.root");
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


//TFile *file01_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESdo/data.root");
TFile *file02_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESdo/TTTT.root");
TFile *file03_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESdo/QCD_HT200to300.root");
TFile *file04_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESdo/QCD_HT300to500.root");
TFile *file05_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESdo/QCD_HT500to700.root");
TFile *file06_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESdo/QCD_HT700to1000.root");
TFile *file07_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESdo/QCD_HT1000to1500.root");
TFile *file08_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESdo/QCD_HT1500to2000.root");
TFile *file09_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESdo/QCD_HT2000toIn.root");
TFile *file10_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESdo/TTJets.root");
TFile *file11_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESdo/TTWJetsToQQ.root");
TFile *file12_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESdo/TTZToQQ.root");
TFile *file13_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JESdo/TT.root");
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




//TFile *file01_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERup/data.root");
TFile *file02_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERup/TTTT.root");
TFile *file03_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERup/QCD_HT200to300.root");
TFile *file04_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERup/QCD_HT300to500.root");
TFile *file05_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERup/QCD_HT500to700.root");
TFile *file06_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERup/QCD_HT700to1000.root");
TFile *file07_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERup/QCD_HT1000to1500.root");
TFile *file08_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERup/QCD_HT1500to2000.root");
TFile *file09_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERup/QCD_HT2000toIn.root");
TFile *file10_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERup/TTJets.root");
TFile *file11_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERup/TTWJetsToQQ.root");
TFile *file12_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERup/TTZToQQ.root");
TFile *file13_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERup/TT.root");
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

//TFile *file01_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERdo/data.root");
TFile *file02_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERdo/TTTT.root");
TFile *file03_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERdo/QCD_HT200to300.root");
TFile *file04_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERdo/QCD_HT300to500.root");
TFile *file05_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERdo/QCD_HT500to700.root");
TFile *file06_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERdo/QCD_HT700to1000.root");
TFile *file07_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERdo/QCD_HT1000to1500.root");
TFile *file08_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERdo/QCD_HT1500to2000.root");
TFile *file09_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERdo/QCD_HT2000toIn.root");
TFile *file10_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERdo/TTJets.root");
TFile *file11_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERdo/TTWJetsToQQ.root");
TFile *file12_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERdo/TTZToQQ.root");
TFile *file13_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v2/JERdo/TT.root");
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


                                                   

TH1F *data_SR; TH1F *QCD_HT200to300_SR; TH1F *QCD_HT300to500_SR; TH1F *QCD_HT500to700_SR; TH1F *QCD_HT700to1000_SR; /*{{{*/
TH1F *QCD_HT1000to1500_SR; TH1F *QCD_HT1500to2000_SR; TH1F *QCD_HT2000toIn_SR; TH1F *TTJets_SR; TH1F *TTWJets_SR; TH1F *TTZ_SR; TH1F *TTTT_SR; 
TH1F *background_SR;
TH1F *TT_SR;

TH1F *data_P1; TH1F *QCD_HT200to300_P1; TH1F *QCD_HT300to500_P1; TH1F *QCD_HT500to700_P1; TH1F *QCD_HT700to1000_P1; 
TH1F *QCD_HT1000to1500_P1; TH1F *QCD_HT1500to2000_P1; TH1F *QCD_HT2000toIn_P1; TH1F *TTJets_P1; TH1F *TTWJets_P1; TH1F *TTZ_P1; TH1F *TTTT_P1; 
TH1F *background_P1;
TH1F *TT_P1;

TH1F *data_P2; TH1F *QCD_HT200to300_P2; TH1F *QCD_HT300to500_P2; TH1F *QCD_HT500to700_P2; TH1F *QCD_HT700to1000_P2; 
TH1F *QCD_HT1000to1500_P2; TH1F *QCD_HT1500to2000_P2; TH1F *QCD_HT2000toIn_P2; TH1F *TTJets_P2; TH1F *TTWJets_P2; TH1F *TTZ_P2; TH1F *TTTT_P2; 
TH1F *background_P2;
TH1F *TT_P2;

TH1F *data_F1; TH1F *QCD_HT200to300_F1; TH1F *QCD_HT300to500_F1; TH1F *QCD_HT500to700_F1; TH1F *QCD_HT700to1000_F1; 
TH1F *QCD_HT1000to1500_F1; TH1F *QCD_HT1500to2000_F1; TH1F *QCD_HT2000toIn_F1; TH1F *TTJets_F1; TH1F *TTWJets_F1; TH1F *TTZ_F1; TH1F *TTTT_F1; 
TH1F *background_F1;
TH1F *TT_F1;

TH1F *data_F2; TH1F *QCD_HT200to300_F2; TH1F *QCD_HT300to500_F2; TH1F *QCD_HT500to700_F2; TH1F *QCD_HT700to1000_F2; 
TH1F *QCD_HT1000to1500_F2; TH1F *QCD_HT1500to2000_F2; TH1F *QCD_HT2000toIn_F2; TH1F *TTJets_F2; TH1F *TTWJets_F2; TH1F *TTZ_F2; TH1F *TTTT_F2; 
TH1F *background_F2;
TH1F *TT_F2;

TH1F *data_B1; TH1F *QCD_HT200to300_B1; TH1F *QCD_HT300to500_B1; TH1F *QCD_HT500to700_B1; TH1F *QCD_HT700to1000_B1; 
TH1F *QCD_HT1000to1500_B1; TH1F *QCD_HT1500to2000_B1; TH1F *QCD_HT2000toIn_B1; TH1F *TTJets_B1; TH1F *TTWJets_B1; TH1F *TTZ_B1; TH1F *TTTT_B1; 
TH1F *background_B1;
TH1F *TT_B1;

TH1F *data_B2; TH1F *QCD_HT200to300_B2; TH1F *QCD_HT300to500_B2; TH1F *QCD_HT500to700_B2; TH1F *QCD_HT700to1000_B2; 
TH1F *QCD_HT1000to1500_B2; TH1F *QCD_HT1500to2000_B2; TH1F *QCD_HT2000toIn_B2; TH1F *TTJets_B2; TH1F *TTWJets_B2; TH1F *TTZ_B2; TH1F *TTTT_B2; 
TH1F *background_B2;
TH1F *TT_B2;

TH1F *data_Z1; TH1F *QCD_HT200to300_Z1; TH1F *QCD_HT300to500_Z1; TH1F *QCD_HT500to700_Z1; TH1F *QCD_HT700to1000_Z1; 
TH1F *QCD_HT1000to1500_Z1; TH1F *QCD_HT1500to2000_Z1; TH1F *QCD_HT2000toIn_Z1; TH1F *TTJets_Z1; TH1F *TTWJets_Z1; TH1F *TTZ_Z1; TH1F *TTTT_Z1; 
TH1F *background_Z1;
TH1F *TT_Z1;

TH1F *data_Z2; TH1F *QCD_HT200to300_Z2; TH1F *QCD_HT300to500_Z2; TH1F *QCD_HT500to700_Z2; TH1F *QCD_HT700to1000_Z2; 
TH1F *QCD_HT1000to1500_Z2; TH1F *QCD_HT1500to2000_Z2; TH1F *QCD_HT2000toIn_Z2; TH1F *TTJets_Z2; TH1F *TTWJets_Z2; TH1F *TTZ_Z2; TH1F *TTTT_Z2; 
TH1F *background_Z2;
TH1F *TT_Z2;

TH1F *data_W1; TH1F *QCD_HT200to300_W1; TH1F *QCD_HT300to500_W1; TH1F *QCD_HT500to700_W1; TH1F *QCD_HT700to1000_W1; 
TH1F *QCD_HT1000to1500_W1; TH1F *QCD_HT1500to2000_W1; TH1F *QCD_HT2000toIn_W1; TH1F *TTJets_W1; TH1F *TTWJets_W1; TH1F *TTZ_W1; TH1F *TTTT_W1; 
TH1F *background_W1;
TH1F *TT_W1;

TH1F *data_W2; TH1F *QCD_HT200to300_W2; TH1F *QCD_HT300to500_W2; TH1F *QCD_HT500to700_W2; TH1F *QCD_HT700to1000_W2; 
TH1F *QCD_HT1000to1500_W2; TH1F *QCD_HT1500to2000_W2; TH1F *QCD_HT2000toIn_W2; TH1F *TTJets_W2; TH1F *TTWJets_W2; TH1F *TTZ_W2; TH1F *TTTT_W2; 
TH1F *background_W2;
TH1F *TT_W2;

TH1F *data_T1; TH1F *QCD_HT200to300_T1; TH1F *QCD_HT300to500_T1; TH1F *QCD_HT500to700_T1; TH1F *QCD_HT700to1000_T1; 
TH1F *QCD_HT1000to1500_T1; TH1F *QCD_HT1500to2000_T1; TH1F *QCD_HT2000toIn_T1; TH1F *TTJets_T1; TH1F *TTWJets_T1; TH1F *TTZ_T1; TH1F *TTTT_T1; 
TH1F *background_T1;
TH1F *TT_T1;

TH1F *data_T2; TH1F *QCD_HT200to300_T2; TH1F *QCD_HT300to500_T2; TH1F *QCD_HT500to700_T2; TH1F *QCD_HT700to1000_T2; 
TH1F *QCD_HT1000to1500_T2; TH1F *QCD_HT1500to2000_T2; TH1F *QCD_HT2000toIn_T2; TH1F *TTJets_T2; TH1F *TTWJets_T2; TH1F *TTZ_T2; TH1F *TTTT_T2; 
TH1F *background_T2;
TH1F *TT_T2;

TH1F *data_J1; TH1F *QCD_HT200to300_J1; TH1F *QCD_HT300to500_J1; TH1F *QCD_HT500to700_J1; TH1F *QCD_HT700to1000_J1; 
TH1F *QCD_HT1000to1500_J1; TH1F *QCD_HT1500to2000_J1; TH1F *QCD_HT2000toIn_J1; TH1F *TTJets_J1; TH1F *TTWJets_J1; TH1F *TTZ_J1; TH1F *TTTT_J1; 
TH1F *background_J1;
TH1F *TT_J1;

TH1F *data_J2; TH1F *QCD_HT200to300_J2; TH1F *QCD_HT300to500_J2; TH1F *QCD_HT500to700_J2; TH1F *QCD_HT700to1000_J2; 
TH1F *QCD_HT1000to1500_J2; TH1F *QCD_HT1500to2000_J2; TH1F *QCD_HT2000toIn_J2; TH1F *TTJets_J2; TH1F *TTWJets_J2; TH1F *TTZ_J2; TH1F *TTTT_J2; 
TH1F *background_J2;
TH1F *TT_J2;

TH1F *data_J3; TH1F *QCD_HT200to300_J3; TH1F *QCD_HT300to500_J3; TH1F *QCD_HT500to700_J3; TH1F *QCD_HT700to1000_J3; 
TH1F *QCD_HT1000to1500_J3; TH1F *QCD_HT1500to2000_J3; TH1F *QCD_HT2000toIn_J3; TH1F *TTJets_J3; TH1F *TTWJets_J3; TH1F *TTZ_J3; TH1F *TTTT_J3; 
TH1F *background_J3;
TH1F *TT_J3;

TH1F *data_J4; TH1F *QCD_HT200to300_J4; TH1F *QCD_HT300to500_J4; TH1F *QCD_HT500to700_J4; TH1F *QCD_HT700to1000_J4; 
TH1F *QCD_HT1000to1500_J4; TH1F *QCD_HT1500to2000_J4; TH1F *QCD_HT2000toIn_J4; TH1F *TTJets_J4; TH1F *TTWJets_J4; TH1F *TTZ_J4; TH1F *TTTT_J4; 
TH1F *background_J4;
TH1F *TT_J4;

TH1F *data_qcd1; TH1F *QCD_HT200to300_qcd1; TH1F *QCD_HT300to500_qcd1; TH1F *QCD_HT500to700_qcd1; TH1F *QCD_HT700to1000_qcd1;
TH1F *QCD_HT1000to1500_qcd1; TH1F *QCD_HT1500to2000_qcd1; TH1F *QCD_HT2000toIn_qcd1; TH1F *TTJets_qcd1; TH1F *TTWJets_qcd1; TH1F *TTZ_qcd1; TH1F *TTTT_qcd1;
TH1F *background_qcd1;
TH1F *TT_qcd1;

TH1F *data_qcd2; TH1F *QCD_HT200to300_qcd2; TH1F *QCD_HT300to500_qcd2; TH1F *QCD_HT500to700_qcd2; TH1F *QCD_HT700to1000_qcd2;
TH1F *QCD_HT1000to1500_qcd2; TH1F *QCD_HT1500to2000_qcd2; TH1F *QCD_HT2000toIn_qcd2; TH1F *TTJets_qcd2; TH1F *TTWJets_qcd2; TH1F *TTZ_qcd2; TH1F *TTTT_qcd2;
TH1F *background_qcd2;
TH1F *TT_qcd2;

TH1F *data_pdf1; TH1F *QCD_HT200to300_pdf1; TH1F *QCD_HT300to500_pdf1; TH1F *QCD_HT500to700_pdf1; TH1F *QCD_HT700to1000_pdf1;
TH1F *QCD_HT1000to1500_pdf1; TH1F *QCD_HT1500to2000_pdf1; TH1F *QCD_HT2000toIn_pdf1; TH1F *TTJets_pdf1; TH1F *TTWJets_pdf1; TH1F *TTZ_pdf1; TH1F *TTTT_pdf1;
TH1F *background_pdf1;
TH1F *TT_pdf1;

TH1F *data_pdf2; TH1F *QCD_HT200to300_pdf2; TH1F *QCD_HT300to500_pdf2; TH1F *QCD_HT500to700_pdf2; TH1F *QCD_HT700to1000_pdf2;
TH1F *QCD_HT1000to1500_pdf2; TH1F *QCD_HT1500to2000_pdf2; TH1F *QCD_HT2000toIn_pdf2; TH1F *TTJets_pdf2; TH1F *TTWJets_pdf2; TH1F *TTZ_pdf2; TH1F *TTTT_pdf2;
TH1F *background_pdf2;
TH1F *TT_pdf2;


TH1F *data_TR1; TH1F *QCD_HT200to300_TR1; TH1F *QCD_HT300to500_TR1; TH1F *QCD_HT500to700_TR1; TH1F *QCD_HT700to1000_TR1;
TH1F *QCD_HT1000to1500_TR1; TH1F *QCD_HT1500to2000_TR1; TH1F *QCD_HT2000toIn_TR1; TH1F *TTJets_TR1; TH1F *TTWJets_TR1; TH1F *TTZ_TR1; TH1F *TTTT_TR1;
TH1F *background_TR1;
TH1F *TT_TR1;


TH1F *data_TR2; TH1F *QCD_HT200to300_TR2; TH1F *QCD_HT300to500_TR2; TH1F *QCD_HT500to700_TR2; TH1F *QCD_HT700to1000_TR2;
TH1F *QCD_HT1000to1500_TR2; TH1F *QCD_HT1500to2000_TR2; TH1F *QCD_HT2000toIn_TR2; TH1F *TTJets_TR2; TH1F *TTWJets_TR2; TH1F *TTZ_TR2; TH1F *TTTT_TR2;
TH1F *background_TR2;
TH1F *TT_TR2;
/*}}}*/
