void MakeHistos(char CUT[1000],const char *plot,int BIN,float MIN,float MAX,int JETSyst,
		TH1F* &data_func,TH1F* &background_func,TH1F* &QCD_HT200to300_func,TH1F* &QCD_HT300to500_func,TH1F* &QCD_HT500to700_func,TH1F* &QCD_HT700to1000_func,TH1F* &QCD_HT1000to1500_func,TH1F* &QCD_HT1500to2000_func,TH1F* &QCD_HT2000toIn_func,
		TH1F* &TTJets_func,TH1F* &TTWJets_func,TH1F* &TTZ_func,
		TH1F* &TTTT_func);
void MakeHistoErrors(int m, TH1F* &histo_SR, TH1F* histo_P1, TH1F* histo_P2, TH1F* histo_F1, TH1F* histo_F2, TH1F* histo_B1, TH1F* histo_B2, TH1F* histo_Z1, TH1F* histo_Z2, TH1F* histo_W1, TH1F* histo_W2, TH1F* histo_T1, TH1F* histo_T2, TH1F* histo_J1, TH1F* histo_J2, TH1F* histo_J3, TH1F* histo_J4, TH1F* histo_qcd1, TH1F* histo_qcd2, TH1F* histo_pdf1, TH1F* histo_pdf2, TH1F* histo_TR1, TH1F* histo_TR2);
void CloneHistos();

int SigSF = 1;
//float LUMI  = 41500.0; 
float LUMI = 36733 //36.773 /fb
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
float wTTJets = (LUMI*746.7)(29509487-14335648);//7.467e+02 +- 2.820e+00 pb
//float wTT = (LUMI*730.6)/()   //750 //7.306e+02 +- 5.572e-01 pb
float wTTWJets = (LUMI*0.4062)/(631804-201494);// 4.062e-01 +- 8.103e-04 pb
float wTTZ = (LUMI*0.5297)/(550282-199118)//5.297e-01 +- 7.941e-04 pb

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
//
//
//float w0700 = SigSF*(0.5*0.5*5.820 *0.25*LUMI/(386981-1075)); //SIG1/*{{{*/
//float w40 = (3.05*LUMI/(4297198-1269149)); //WZTo1L3Nu/*}}}*/

//TFile *file01 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/data.root");/*{{{*/
TFile *file02 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/TTTT.root");
TFile *file03 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/QCD_HT200to300.root");
TFile *file04 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/QCD_HT300to500.root");
TFile *file05 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/QCD_HT500to700.root");
TFile *file06 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/QCD_HT700to1000.root");
TFile *file07 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/QCD_HT1000to1500.root");
TFile *file08 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/QCD_HT1500to2000.root");
TFile *file09 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/QCD_HT2000toIn.root");
TFile *file10 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/TTJets.root");
TFile *file11 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/TTWJetsToQQ.root");
TFile *file12 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/TTZToQQ.root");
//TFile *file13 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/Tprime_1800.root");
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
/*}}}*/

//TFile *file01_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESup/data.root");/*{{{*/
TFile *file02_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESup/TTTT.root");
TFile *file03_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESup/QCD_HT200to300.root");
TFile *file04_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESup/QCD_HT300to500.root");
TFile *file05_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESup/QCD_HT500to700.root");
TFile *file06_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESup/QCD_HT700to1000.root");
TFile *file07_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESup/QCD_HT1000to1500.root");
TFile *file08_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESup/QCD_HT1500to2000.root");
TFile *file09_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESup/QCD_HT2000toIn.root");
TFile *file10_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESup/TTJets.root");
TFile *file11_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESup/TTWJetsToQQ.root");
TFile *file12_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESup/TTZToQQ.root");
//TFile *file13_J1 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESup/Tprime_1800.root");
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
//TTree *Tree13_J1 = (TTree*)file13_J1->Get("tree");
/*}}}*/

//TFile *file01_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESdo/data.root");/*{{{*/
TFile *file02_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESdo/TTTT.root");
TFile *file03_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESdo/QCD_HT200to300.root");
TFile *file04_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESdo/QCD_HT300to500.root");
TFile *file05_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESdo/QCD_HT500to700.root");
TFile *file06_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESdo/QCD_HT700to1000.root");
TFile *file07_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESdo/QCD_HT1000to1500.root");
TFile *file08_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESdo/QCD_HT1500to2000.root");
TFile *file09_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESdo/QCD_HT2000toIn.root");
TFile *file10_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESdo/TTJets.root");
TFile *file11_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESdo/TTWJetsToQQ.root");
TFile *file12_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESdo/TTZToQQ.root");
//TFile *file13_J2 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JESdo/Tprime_1800.root");
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
//TTree *Tree13_J2 = (TTree*)file13_J2->Get("tree");
/*}}}*/



//TFile *file01_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERup/data.root");/*{{{*/
TFile *file02_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERup/TTTT.root");
TFile *file03_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERup/QCD_HT200to300.root");
TFile *file04_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERup/QCD_HT300to500.root");
TFile *file05_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERup/QCD_HT500to700.root");
TFile *file06_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERup/QCD_HT700to1000.root");
TFile *file07_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERup/QCD_HT1000to1500.root");
TFile *file08_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERup/QCD_HT1500to2000.root");
TFile *file09_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERup/QCD_HT2000toIn.root");
TFile *file10_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERup/TTJets.root");
TFile *file11_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERup/TTWJetsToQQ.root");
TFile *file12_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERup/TTZToQQ.root");
//TFile *file13_J3 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERup/Tprime_1800.root");
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
//TTree *Tree13_J3 = (TTree*)file13_J3->Get("tree");
/*}}}*/
//TFile *file01_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERdo/data.root");/*{{{*/
TFile *file02_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERdo/TTTT.root");
TFile *file03_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERdo/QCD_HT200to300.root");
TFile *file04_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERdo/QCD_HT300to500.root");
TFile *file05_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERdo/QCD_HT500to700.root");
TFile *file06_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERdo/QCD_HT700to1000.root");
TFile *file07_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERdo/QCD_HT1000to1500.root");
TFile *file08_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERdo/QCD_HT1500to2000.root");
TFile *file09_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERdo/QCD_HT2000toIn.root");
TFile *file10_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERdo/TTJets.root");
TFile *file11_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERdo/TTWJetsToQQ.root");
TFile *file12_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERdo/TTZToQQ.root");
//TFile *file13_J4 = TFile::Open("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC/JERdo/Tprime_1800.root");
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
//TTree *Tree13_J4 = (TTree*)file13_J4->Get("tree");
/*}}}*/

                                                    

TH1F *data_SR; TH1F *tptzm0700lh_SR; TH1F *tptzm0900lh_SR; TH1F *tptzm1400lh_SR; TH1F *tptzm1700lh_SR; /*{{{*/
TH1F *ZToNuNu_1_SR; TH1F *ZToNuNu_2_SR; TH1F *ZToNuNu_3_SR; TH1F *ZToNuNu_4_SR; TH1F *ZToNuNu_5_SR; TH1F *ZToNuNu_6_SR; TH1F *ZToNuNu_7_SR; 
TH1F *QCD_1_SR; TH1F *QCD_2_SR; TH1F *QCD_3_SR; TH1F *QCD_4_SR; TH1F *QCD_5_SR; TH1F *QCD_6_SR; TH1F *QCD_7_SR; 
TH1F *WToLNu_1_SR; TH1F *WToLNu_2_SR; TH1F *WToLNu_3_SR; TH1F *WToLNu_4_SR; TH1F *WToLNu_5_SR; TH1F *WToLNu_6_SR; TH1F *WToLNu_7_SR; 
TH1F *TT_1_SR; TH1F *TT_2_SR; TH1F *ST_1_SR; TH1F *ST_2_SR; TH1F *ST_3_SR; TH1F *ST_4_SR; 
TH1F *ZZ1_SR; TH1F *ZZ2_SR; TH1F *ZZ3_SR; TH1F *WW1_SR; TH1F *WW2_SR; TH1F *WZ1_SR; TH1F *WZ2_SR; TH1F *WZ3_SR; TH1F *WToLNu_SR; TH1F *background_SR;
TH1F *ttW_SR; TH1F *ttZ_SR; TH1F *tZq_SR; TH1F *ZZ4_SR; TH1F *WZ4_SR; 

TH1F *data_P1; TH1F *tptzm0700lh_P1; TH1F *tptzm0900lh_P1; TH1F *tptzm1400lh_P1; TH1F *tptzm1700lh_P1; 
TH1F *ZToNuNu_1_P1; TH1F *ZToNuNu_2_P1; TH1F *ZToNuNu_3_P1; TH1F *ZToNuNu_4_P1; TH1F *ZToNuNu_5_P1; TH1F *ZToNuNu_6_P1; TH1F *ZToNuNu_7_P1; 
TH1F *QCD_1_P1; TH1F *QCD_2_P1; TH1F *QCD_3_P1; TH1F *QCD_4_P1; TH1F *QCD_5_P1; TH1F *QCD_6_P1; TH1F *QCD_7_P1; 
TH1F *WToLNu_1_P1; TH1F *WToLNu_2_P1; TH1F *WToLNu_3_P1; TH1F *WToLNu_4_P1; TH1F *WToLNu_5_P1; TH1F *WToLNu_6_P1; TH1F *WToLNu_7_P1; 
TH1F *TT_1_P1; TH1F *TT_2_P1; TH1F *ST_1_P1; TH1F *ST_2_P1; TH1F *ST_3_P1; TH1F *ST_4_P1; 
TH1F *ZZ1_P1; TH1F *ZZ2_P1; TH1F *ZZ3_P1; TH1F *WW1_P1; TH1F *WW2_P1; TH1F *WZ1_P1; TH1F *WZ2_P1; TH1F *WZ3_P1; TH1F *WToLNu_P1; TH1F *background_P1;
TH1F *ttW_P1; TH1F *ttZ_P1; TH1F *tZq_P1; TH1F *ZZ4_P1; TH1F *WZ4_P1; 

TH1F *data_P2; TH1F *tptzm0700lh_P2; TH1F *tptzm0900lh_P2; TH1F *tptzm1400lh_P2; TH1F *tptzm1700lh_P2; 
TH1F *ZToNuNu_1_P2; TH1F *ZToNuNu_2_P2; TH1F *ZToNuNu_3_P2; TH1F *ZToNuNu_4_P2; TH1F *ZToNuNu_5_P2; TH1F *ZToNuNu_6_P2; TH1F *ZToNuNu_7_P2; 
TH1F *QCD_1_P2; TH1F *QCD_2_P2; TH1F *QCD_3_P2; TH1F *QCD_4_P2; TH1F *QCD_5_P2; TH1F *QCD_6_P2; TH1F *QCD_7_P2; 
TH1F *WToLNu_1_P2; TH1F *WToLNu_2_P2; TH1F *WToLNu_3_P2; TH1F *WToLNu_4_P2; TH1F *WToLNu_5_P2; TH1F *WToLNu_6_P2; TH1F *WToLNu_7_P2; 
TH1F *TT_1_P2; TH1F *TT_2_P2; TH1F *ST_1_P2; TH1F *ST_2_P2; TH1F *ST_3_P2; TH1F *ST_4_P2; 
TH1F *ZZ1_P2; TH1F *ZZ2_P2; TH1F *ZZ3_P2; TH1F *WW1_P2; TH1F *WW2_P2; TH1F *WZ1_P2; TH1F *WZ2_P2; TH1F *WZ3_P2; TH1F *WToLNu_P2; TH1F *background_P2;
TH1F *ttW_P2; TH1F *ttZ_P2; TH1F *tZq_P2; TH1F *ZZ4_P2; TH1F *WZ4_P2; 

TH1F *data_F1; TH1F *tptzm0700lh_F1; TH1F *tptzm0900lh_F1; TH1F *tptzm1400lh_F1; TH1F *tptzm1700lh_F1; 
TH1F *ZToNuNu_1_F1; TH1F *ZToNuNu_2_F1; TH1F *ZToNuNu_3_F1; TH1F *ZToNuNu_4_F1; TH1F *ZToNuNu_5_F1; TH1F *ZToNuNu_6_F1; TH1F *ZToNuNu_7_F1; 
TH1F *QCD_1_F1; TH1F *QCD_2_F1; TH1F *QCD_3_F1; TH1F *QCD_4_F1; TH1F *QCD_5_F1; TH1F *QCD_6_F1; TH1F *QCD_7_F1; 
TH1F *WToLNu_1_F1; TH1F *WToLNu_2_F1; TH1F *WToLNu_3_F1; TH1F *WToLNu_4_F1; TH1F *WToLNu_5_F1; TH1F *WToLNu_6_F1; TH1F *WToLNu_7_F1; 
TH1F *TT_1_F1; TH1F *TT_2_F1; TH1F *ST_1_F1; TH1F *ST_2_F1; TH1F *ST_3_F1; TH1F *ST_4_F1; 
TH1F *ZZ1_F1; TH1F *ZZ2_F1; TH1F *ZZ3_F1; TH1F *WW1_F1; TH1F *WW2_F1; TH1F *WZ1_F1; TH1F *WZ2_F1; TH1F *WZ3_F1; TH1F *WToLNu_F1; TH1F *background_F1;
TH1F *ttW_F1; TH1F *ttZ_F1; TH1F *tZq_F1; TH1F *ZZ4_F1; TH1F *WZ4_F1; 

TH1F *data_F2; TH1F *tptzm0700lh_F2; TH1F *tptzm0900lh_F2; TH1F *tptzm1400lh_F2; TH1F *tptzm1700lh_F2; 
TH1F *ZToNuNu_1_F2; TH1F *ZToNuNu_2_F2; TH1F *ZToNuNu_3_F2; TH1F *ZToNuNu_4_F2; TH1F *ZToNuNu_5_F2; TH1F *ZToNuNu_6_F2; TH1F *ZToNuNu_7_F2; 
TH1F *QCD_1_F2; TH1F *QCD_2_F2; TH1F *QCD_3_F2; TH1F *QCD_4_F2; TH1F *QCD_5_F2; TH1F *QCD_6_F2; TH1F *QCD_7_F2; 
TH1F *WToLNu_1_F2; TH1F *WToLNu_2_F2; TH1F *WToLNu_3_F2; TH1F *WToLNu_4_F2; TH1F *WToLNu_5_F2; TH1F *WToLNu_6_F2; TH1F *WToLNu_7_F2; 
TH1F *TT_1_F2; TH1F *TT_2_F2; TH1F *ST_1_F2; TH1F *ST_2_F2; TH1F *ST_3_F2; TH1F *ST_4_F2; 
TH1F *ZZ1_F2; TH1F *ZZ2_F2; TH1F *ZZ3_F2; TH1F *WW1_F2; TH1F *WW2_F2; TH1F *WZ1_F2; TH1F *WZ2_F2; TH1F *WZ3_F2; TH1F *WToLNu_F2; TH1F *background_F2;
TH1F *ttW_F2; TH1F *ttZ_F2; TH1F *tZq_F2; TH1F *ZZ4_F2; TH1F *WZ4_F2; 

TH1F *data_B1; TH1F *tptzm0700lh_B1; TH1F *tptzm0900lh_B1; TH1F *tptzm1400lh_B1; TH1F *tptzm1700lh_B1; 
TH1F *ZToNuNu_1_B1; TH1F *ZToNuNu_2_B1; TH1F *ZToNuNu_3_B1; TH1F *ZToNuNu_4_B1; TH1F *ZToNuNu_5_B1; TH1F *ZToNuNu_6_B1; TH1F *ZToNuNu_7_B1; 
TH1F *QCD_1_B1; TH1F *QCD_2_B1; TH1F *QCD_3_B1; TH1F *QCD_4_B1; TH1F *QCD_5_B1; TH1F *QCD_6_B1; TH1F *QCD_7_B1; 
TH1F *WToLNu_1_B1; TH1F *WToLNu_2_B1; TH1F *WToLNu_3_B1; TH1F *WToLNu_4_B1; TH1F *WToLNu_5_B1; TH1F *WToLNu_6_B1; TH1F *WToLNu_7_B1; 
TH1F *TT_1_B1; TH1F *TT_2_B1; TH1F *ST_1_B1; TH1F *ST_2_B1; TH1F *ST_3_B1; TH1F *ST_4_B1; 
TH1F *ZZ1_B1; TH1F *ZZ2_B1; TH1F *ZZ3_B1; TH1F *WW1_B1; TH1F *WW2_B1; TH1F *WZ1_B1; TH1F *WZ2_B1; TH1F *WZ3_B1; TH1F *WToLNu_B1; TH1F *background_B1;
TH1F *ttW_B1; TH1F *ttZ_B1; TH1F *tZq_B1; TH1F *ZZ4_B1; TH1F *WZ4_B1; 

TH1F *data_B2; TH1F *tptzm0700lh_B2; TH1F *tptzm0900lh_B2; TH1F *tptzm1400lh_B2; TH1F *tptzm1700lh_B2; 
TH1F *ZToNuNu_1_B2; TH1F *ZToNuNu_2_B2; TH1F *ZToNuNu_3_B2; TH1F *ZToNuNu_4_B2; TH1F *ZToNuNu_5_B2; TH1F *ZToNuNu_6_B2; TH1F *ZToNuNu_7_B2; 
TH1F *QCD_1_B2; TH1F *QCD_2_B2; TH1F *QCD_3_B2; TH1F *QCD_4_B2; TH1F *QCD_5_B2; TH1F *QCD_6_B2; TH1F *QCD_7_B2; 
TH1F *WToLNu_1_B2; TH1F *WToLNu_2_B2; TH1F *WToLNu_3_B2; TH1F *WToLNu_4_B2; TH1F *WToLNu_5_B2; TH1F *WToLNu_6_B2; TH1F *WToLNu_7_B2; 
TH1F *TT_1_B2; TH1F *TT_2_B2; TH1F *ST_1_B2; TH1F *ST_2_B2; TH1F *ST_3_B2; TH1F *ST_4_B2; 
TH1F *ZZ1_B2; TH1F *ZZ2_B2; TH1F *ZZ3_B2; TH1F *WW1_B2; TH1F *WW2_B2; TH1F *WZ1_B2; TH1F *WZ2_B2; TH1F *WZ3_B2; TH1F *WToLNu_B2; TH1F *background_B2;
TH1F *ttW_B2; TH1F *ttZ_B2; TH1F *tZq_B2; TH1F *ZZ4_B2; TH1F *WZ4_B2; 

TH1F *data_Z1; TH1F *tptzm0700lh_Z1; TH1F *tptzm0900lh_Z1; TH1F *tptzm1400lh_Z1; TH1F *tptzm1700lh_Z1; 
TH1F *ZToNuNu_1_Z1; TH1F *ZToNuNu_2_Z1; TH1F *ZToNuNu_3_Z1; TH1F *ZToNuNu_4_Z1; TH1F *ZToNuNu_5_Z1; TH1F *ZToNuNu_6_Z1; TH1F *ZToNuNu_7_Z1; 
TH1F *QCD_1_Z1; TH1F *QCD_2_Z1; TH1F *QCD_3_Z1; TH1F *QCD_4_Z1; TH1F *QCD_5_Z1; TH1F *QCD_6_Z1; TH1F *QCD_7_Z1; 
TH1F *WToLNu_1_Z1; TH1F *WToLNu_2_Z1; TH1F *WToLNu_3_Z1; TH1F *WToLNu_4_Z1; TH1F *WToLNu_5_Z1; TH1F *WToLNu_6_Z1; TH1F *WToLNu_7_Z1; 
TH1F *TT_1_Z1; TH1F *TT_2_Z1; TH1F *ST_1_Z1; TH1F *ST_2_Z1; TH1F *ST_3_Z1; TH1F *ST_4_Z1; 
TH1F *ZZ1_Z1; TH1F *ZZ2_Z1; TH1F *ZZ3_Z1; TH1F *WW1_Z1; TH1F *WW2_Z1; TH1F *WZ1_Z1; TH1F *WZ2_Z1; TH1F *WZ3_Z1; TH1F *WToLNu_Z1; TH1F *background_Z1;
TH1F *ttW_Z1; TH1F *ttZ_Z1; TH1F *tZq_Z1; TH1F *ZZ4_Z1; TH1F *WZ4_Z1; 

TH1F *data_Z2; TH1F *tptzm0700lh_Z2; TH1F *tptzm0900lh_Z2; TH1F *tptzm1400lh_Z2; TH1F *tptzm1700lh_Z2; 
TH1F *ZToNuNu_1_Z2; TH1F *ZToNuNu_2_Z2; TH1F *ZToNuNu_3_Z2; TH1F *ZToNuNu_4_Z2; TH1F *ZToNuNu_5_Z2; TH1F *ZToNuNu_6_Z2; TH1F *ZToNuNu_7_Z2; 
TH1F *QCD_1_Z2; TH1F *QCD_2_Z2; TH1F *QCD_3_Z2; TH1F *QCD_4_Z2; TH1F *QCD_5_Z2; TH1F *QCD_6_Z2; TH1F *QCD_7_Z2; 
TH1F *WToLNu_1_Z2; TH1F *WToLNu_2_Z2; TH1F *WToLNu_3_Z2; TH1F *WToLNu_4_Z2; TH1F *WToLNu_5_Z2; TH1F *WToLNu_6_Z2; TH1F *WToLNu_7_Z2; 
TH1F *TT_1_Z2; TH1F *TT_2_Z2; TH1F *ST_1_Z2; TH1F *ST_2_Z2; TH1F *ST_3_Z2; TH1F *ST_4_Z2; 
TH1F *ZZ1_Z2; TH1F *ZZ2_Z2; TH1F *ZZ3_Z2; TH1F *WW1_Z2; TH1F *WW2_Z2; TH1F *WZ1_Z2; TH1F *WZ2_Z2; TH1F *WZ3_Z2; TH1F *WToLNu_Z2; TH1F *background_Z2;
TH1F *ttW_Z2; TH1F *ttZ_Z2; TH1F *tZq_Z2; TH1F *ZZ4_Z2; TH1F *WZ4_Z2; 

TH1F *data_W1; TH1F *tptzm0700lh_W1; TH1F *tptzm0900lh_W1; TH1F *tptzm1400lh_W1; TH1F *tptzm1700lh_W1; 
TH1F *ZToNuNu_1_W1; TH1F *ZToNuNu_2_W1; TH1F *ZToNuNu_3_W1; TH1F *ZToNuNu_4_W1; TH1F *ZToNuNu_5_W1; TH1F *ZToNuNu_6_W1; TH1F *ZToNuNu_7_W1; 
TH1F *QCD_1_W1; TH1F *QCD_2_W1; TH1F *QCD_3_W1; TH1F *QCD_4_W1; TH1F *QCD_5_W1; TH1F *QCD_6_W1; TH1F *QCD_7_W1; 
TH1F *WToLNu_1_W1; TH1F *WToLNu_2_W1; TH1F *WToLNu_3_W1; TH1F *WToLNu_4_W1; TH1F *WToLNu_5_W1; TH1F *WToLNu_6_W1; TH1F *WToLNu_7_W1; 
TH1F *TT_1_W1; TH1F *TT_2_W1; TH1F *ST_1_W1; TH1F *ST_2_W1; TH1F *ST_3_W1; TH1F *ST_4_W1; 
TH1F *ZZ1_W1; TH1F *ZZ2_W1; TH1F *ZZ3_W1; TH1F *WW1_W1; TH1F *WW2_W1; TH1F *WZ1_W1; TH1F *WZ2_W1; TH1F *WZ3_W1; TH1F *WToLNu_W1; TH1F *background_W1;
TH1F *ttW_W1; TH1F *ttZ_W1; TH1F *tZq_W1; TH1F *ZZ4_W1; TH1F *WZ4_W1; 

TH1F *data_W2; TH1F *tptzm0700lh_W2; TH1F *tptzm0900lh_W2; TH1F *tptzm1400lh_W2; TH1F *tptzm1700lh_W2; 
TH1F *ZToNuNu_1_W2; TH1F *ZToNuNu_2_W2; TH1F *ZToNuNu_3_W2; TH1F *ZToNuNu_4_W2; TH1F *ZToNuNu_5_W2; TH1F *ZToNuNu_6_W2; TH1F *ZToNuNu_7_W2; 
TH1F *QCD_1_W2; TH1F *QCD_2_W2; TH1F *QCD_3_W2; TH1F *QCD_4_W2; TH1F *QCD_5_W2; TH1F *QCD_6_W2; TH1F *QCD_7_W2; 
TH1F *WToLNu_1_W2; TH1F *WToLNu_2_W2; TH1F *WToLNu_3_W2; TH1F *WToLNu_4_W2; TH1F *WToLNu_5_W2; TH1F *WToLNu_6_W2; TH1F *WToLNu_7_W2; 
TH1F *TT_1_W2; TH1F *TT_2_W2; TH1F *ST_1_W2; TH1F *ST_2_W2; TH1F *ST_3_W2; TH1F *ST_4_W2; 
TH1F *ZZ1_W2; TH1F *ZZ2_W2; TH1F *ZZ3_W2; TH1F *WW1_W2; TH1F *WW2_W2; TH1F *WZ1_W2; TH1F *WZ2_W2; TH1F *WZ3_W2; TH1F *WToLNu_W2; TH1F *background_W2;
TH1F *ttW_W2; TH1F *ttZ_W2; TH1F *tZq_W2; TH1F *ZZ4_W2; TH1F *WZ4_W2; 

TH1F *data_T1; TH1F *tptzm0700lh_T1; TH1F *tptzm0900lh_T1; TH1F *tptzm1400lh_T1; TH1F *tptzm1700lh_T1; 
TH1F *ZToNuNu_1_T1; TH1F *ZToNuNu_2_T1; TH1F *ZToNuNu_3_T1; TH1F *ZToNuNu_4_T1; TH1F *ZToNuNu_5_T1; TH1F *ZToNuNu_6_T1; TH1F *ZToNuNu_7_T1; 
TH1F *QCD_1_T1; TH1F *QCD_2_T1; TH1F *QCD_3_T1; TH1F *QCD_4_T1; TH1F *QCD_5_T1; TH1F *QCD_6_T1; TH1F *QCD_7_T1; 
TH1F *WToLNu_1_T1; TH1F *WToLNu_2_T1; TH1F *WToLNu_3_T1; TH1F *WToLNu_4_T1; TH1F *WToLNu_5_T1; TH1F *WToLNu_6_T1; TH1F *WToLNu_7_T1; 
TH1F *TT_1_T1; TH1F *TT_2_T1; TH1F *ST_1_T1; TH1F *ST_2_T1; TH1F *ST_3_T1; TH1F *ST_4_T1; 
TH1F *ZZ1_T1; TH1F *ZZ2_T1; TH1F *ZZ3_T1; TH1F *WW1_T1; TH1F *WW2_T1; TH1F *WZ1_T1; TH1F *WZ2_T1; TH1F *WZ3_T1; TH1F *WToLNu_T1; TH1F *background_T1;
TH1F *ttW_T1; TH1F *ttZ_T1; TH1F *tZq_T1; TH1F *ZZ4_T1; TH1F *WZ4_T1; 

TH1F *data_T2; TH1F *tptzm0700lh_T2; TH1F *tptzm0900lh_T2; TH1F *tptzm1400lh_T2; TH1F *tptzm1700lh_T2; 
TH1F *ZToNuNu_1_T2; TH1F *ZToNuNu_2_T2; TH1F *ZToNuNu_3_T2; TH1F *ZToNuNu_4_T2; TH1F *ZToNuNu_5_T2; TH1F *ZToNuNu_6_T2; TH1F *ZToNuNu_7_T2; 
TH1F *QCD_1_T2; TH1F *QCD_2_T2; TH1F *QCD_3_T2; TH1F *QCD_4_T2; TH1F *QCD_5_T2; TH1F *QCD_6_T2; TH1F *QCD_7_T2; 
TH1F *WToLNu_1_T2; TH1F *WToLNu_2_T2; TH1F *WToLNu_3_T2; TH1F *WToLNu_4_T2; TH1F *WToLNu_5_T2; TH1F *WToLNu_6_T2; TH1F *WToLNu_7_T2; 
TH1F *TT_1_T2; TH1F *TT_2_T2; TH1F *ST_1_T2; TH1F *ST_2_T2; TH1F *ST_3_T2; TH1F *ST_4_T2; 
TH1F *ZZ1_T2; TH1F *ZZ2_T2; TH1F *ZZ3_T2; TH1F *WW1_T2; TH1F *WW2_T2; TH1F *WZ1_T2; TH1F *WZ2_T2; TH1F *WZ3_T2; TH1F *WToLNu_T2; TH1F *background_T2;
TH1F *ttW_T2; TH1F *ttZ_T2; TH1F *tZq_T2; TH1F *ZZ4_T2; TH1F *WZ4_T2; 

TH1F *data_J1; TH1F *tptzm0700lh_J1; TH1F *tptzm0900lh_J1; TH1F *tptzm1400lh_J1; TH1F *tptzm1700lh_J1; 
TH1F *ZToNuNu_1_J1; TH1F *ZToNuNu_2_J1; TH1F *ZToNuNu_3_J1; TH1F *ZToNuNu_4_J1; TH1F *ZToNuNu_5_J1; TH1F *ZToNuNu_6_J1; TH1F *ZToNuNu_7_J1; 
TH1F *QCD_1_J1; TH1F *QCD_2_J1; TH1F *QCD_3_J1; TH1F *QCD_4_J1; TH1F *QCD_5_J1; TH1F *QCD_6_J1; TH1F *QCD_7_J1; 
TH1F *WToLNu_1_J1; TH1F *WToLNu_2_J1; TH1F *WToLNu_3_J1; TH1F *WToLNu_4_J1; TH1F *WToLNu_5_J1; TH1F *WToLNu_6_J1; TH1F *WToLNu_7_J1; 
TH1F *TT_1_J1; TH1F *TT_2_J1; TH1F *ST_1_J1; TH1F *ST_2_J1; TH1F *ST_3_J1; TH1F *ST_4_J1; 
TH1F *ZZ1_J1; TH1F *ZZ2_J1; TH1F *ZZ3_J1; TH1F *WW1_J1; TH1F *WW2_J1; TH1F *WZ1_J1; TH1F *WZ2_J1; TH1F *WZ3_J1; TH1F *WToLNu_J1; TH1F *background_J1;
TH1F *ttW_J1; TH1F *ttZ_J1; TH1F *tZq_J1; TH1F *ZZ4_J1; TH1F *WZ4_J1; 

TH1F *data_J2; TH1F *tptzm0700lh_J2; TH1F *tptzm0900lh_J2; TH1F *tptzm1400lh_J2; TH1F *tptzm1700lh_J2; 
TH1F *ZToNuNu_1_J2; TH1F *ZToNuNu_2_J2; TH1F *ZToNuNu_3_J2; TH1F *ZToNuNu_4_J2; TH1F *ZToNuNu_5_J2; TH1F *ZToNuNu_6_J2; TH1F *ZToNuNu_7_J2; 
TH1F *QCD_1_J2; TH1F *QCD_2_J2; TH1F *QCD_3_J2; TH1F *QCD_4_J2; TH1F *QCD_5_J2; TH1F *QCD_6_J2; TH1F *QCD_7_J2; 
TH1F *WToLNu_1_J2; TH1F *WToLNu_2_J2; TH1F *WToLNu_3_J2; TH1F *WToLNu_4_J2; TH1F *WToLNu_5_J2; TH1F *WToLNu_6_J2; TH1F *WToLNu_7_J2; 
TH1F *TT_1_J2; TH1F *TT_2_J2; TH1F *ST_1_J2; TH1F *ST_2_J2; TH1F *ST_3_J2; TH1F *ST_4_J2; 
TH1F *ZZ1_J2; TH1F *ZZ2_J2; TH1F *ZZ3_J2; TH1F *WW1_J2; TH1F *WW2_J2; TH1F *WZ1_J2; TH1F *WZ2_J2; TH1F *WZ3_J2; TH1F *WToLNu_J2; TH1F *background_J2;
TH1F *ttW_J2; TH1F *ttZ_J2; TH1F *tZq_J2; TH1F *ZZ4_J2; TH1F *WZ4_J2; 

TH1F *data_J3; TH1F *tptzm0700lh_J3; TH1F *tptzm0900lh_J3; TH1F *tptzm1400lh_J3; TH1F *tptzm1700lh_J3; 
TH1F *ZToNuNu_1_J3; TH1F *ZToNuNu_2_J3; TH1F *ZToNuNu_3_J3; TH1F *ZToNuNu_4_J3; TH1F *ZToNuNu_5_J3; TH1F *ZToNuNu_6_J3; TH1F *ZToNuNu_7_J3; 
TH1F *QCD_1_J3; TH1F *QCD_2_J3; TH1F *QCD_3_J3; TH1F *QCD_4_J3; TH1F *QCD_5_J3; TH1F *QCD_6_J3; TH1F *QCD_7_J3; 
TH1F *WToLNu_1_J3; TH1F *WToLNu_2_J3; TH1F *WToLNu_3_J3; TH1F *WToLNu_4_J3; TH1F *WToLNu_5_J3; TH1F *WToLNu_6_J3; TH1F *WToLNu_7_J3; 
TH1F *TT_1_J3; TH1F *TT_2_J3; TH1F *ST_1_J3; TH1F *ST_2_J3; TH1F *ST_3_J3; TH1F *ST_4_J3; 
TH1F *ZZ1_J3; TH1F *ZZ2_J3; TH1F *ZZ3_J3; TH1F *WW1_J3; TH1F *WW2_J3; TH1F *WZ1_J3; TH1F *WZ2_J3; TH1F *WZ3_J3; TH1F *WToLNu_J3; TH1F *background_J3;
TH1F *ttW_J3; TH1F *ttZ_J3; TH1F *tZq_J3; TH1F *ZZ4_J3; TH1F *WZ4_J3; 

TH1F *data_J4; TH1F *tptzm0700lh_J4; TH1F *tptzm0900lh_J4; TH1F *tptzm1400lh_J4; TH1F *tptzm1700lh_J4; 
TH1F *ZToNuNu_1_J4; TH1F *ZToNuNu_2_J4; TH1F *ZToNuNu_3_J4; TH1F *ZToNuNu_4_J4; TH1F *ZToNuNu_5_J4; TH1F *ZToNuNu_6_J4; TH1F *ZToNuNu_7_J4; 
TH1F *QCD_1_J4; TH1F *QCD_2_J4; TH1F *QCD_3_J4; TH1F *QCD_4_J4; TH1F *QCD_5_J4; TH1F *QCD_6_J4; TH1F *QCD_7_J4; 
TH1F *WToLNu_1_J4; TH1F *WToLNu_2_J4; TH1F *WToLNu_3_J4; TH1F *WToLNu_4_J4; TH1F *WToLNu_5_J4; TH1F *WToLNu_6_J4; TH1F *WToLNu_7_J4; 
TH1F *TT_1_J4; TH1F *TT_2_J4; TH1F *ST_1_J4; TH1F *ST_2_J4; TH1F *ST_3_J4; TH1F *ST_4_J4; 
TH1F *ZZ1_J4; TH1F *ZZ2_J4; TH1F *ZZ3_J4; TH1F *WW1_J4; TH1F *WW2_J4; TH1F *WZ1_J4; TH1F *WZ2_J4; TH1F *WZ3_J4; TH1F *WToLNu_J4; TH1F *background_J4;
TH1F *ttW_J4; TH1F *ttZ_J4; TH1F *tZq_J4; TH1F *ZZ4_J4; TH1F *WZ4_J4; 

TH1F *data_qcd1; TH1F *tptzm0700lh_qcd1; TH1F *tptzm0900lh_qcd1; TH1F *tptzm1400lh_qcd1; TH1F *tptzm1700lh_qcd1;
TH1F *ZToNuNu_1_qcd1; TH1F *ZToNuNu_2_qcd1; TH1F *ZToNuNu_3_qcd1; TH1F *ZToNuNu_4_qcd1; TH1F *ZToNuNu_5_qcd1; TH1F *ZToNuNu_6_qcd1; TH1F *ZToNuNu_7_qcd1;
TH1F *QCD_1_qcd1; TH1F *QCD_2_qcd1; TH1F *QCD_3_qcd1; TH1F *QCD_4_qcd1; TH1F *QCD_5_qcd1; TH1F *QCD_6_qcd1; TH1F *QCD_7_qcd1;
TH1F *WToLNu_1_qcd1; TH1F *WToLNu_2_qcd1; TH1F *WToLNu_3_qcd1; TH1F *WToLNu_4_qcd1; TH1F *WToLNu_5_qcd1; TH1F *WToLNu_6_qcd1; TH1F *WToLNu_7_qcd1;
TH1F *TT_1_qcd1; TH1F *TT_2_qcd1; TH1F *ST_1_qcd1; TH1F *ST_2_qcd1; TH1F *ST_3_qcd1; TH1F *ST_4_qcd1;
TH1F *ZZ1_qcd1; TH1F *ZZ2_qcd1; TH1F *ZZ3_qcd1; TH1F *WW1_qcd1; TH1F *WW2_qcd1; TH1F *WZ1_qcd1; TH1F *WZ2_qcd1; TH1F *WZ3_qcd1; TH1F *WToLNu_qcd1; TH1F *background_qcd1;
TH1F *ttW_qcd1; TH1F *ttZ_qcd1; TH1F *tZq_qcd1; TH1F *ZZ4_qcd1; TH1F *WZ4_qcd1;

TH1F *data_qcd2; TH1F *tptzm0700lh_qcd2; TH1F *tptzm0900lh_qcd2; TH1F *tptzm1400lh_qcd2; TH1F *tptzm1700lh_qcd2;
TH1F *ZToNuNu_1_qcd2; TH1F *ZToNuNu_2_qcd2; TH1F *ZToNuNu_3_qcd2; TH1F *ZToNuNu_4_qcd2; TH1F *ZToNuNu_5_qcd2; TH1F *ZToNuNu_6_qcd2; TH1F *ZToNuNu_7_qcd2;
TH1F *QCD_1_qcd2; TH1F *QCD_2_qcd2; TH1F *QCD_3_qcd2; TH1F *QCD_4_qcd2; TH1F *QCD_5_qcd2; TH1F *QCD_6_qcd2; TH1F *QCD_7_qcd2;
TH1F *WToLNu_1_qcd2; TH1F *WToLNu_2_qcd2; TH1F *WToLNu_3_qcd2; TH1F *WToLNu_4_qcd2; TH1F *WToLNu_5_qcd2; TH1F *WToLNu_6_qcd2; TH1F *WToLNu_7_qcd2;
TH1F *TT_1_qcd2; TH1F *TT_2_qcd2; TH1F *ST_1_qcd2; TH1F *ST_2_qcd2; TH1F *ST_3_qcd2; TH1F *ST_4_qcd2;
TH1F *ZZ1_qcd2; TH1F *ZZ2_qcd2; TH1F *ZZ3_qcd2; TH1F *WW1_qcd2; TH1F *WW2_qcd2; TH1F *WZ1_qcd2; TH1F *WZ2_qcd2; TH1F *WZ3_qcd2; TH1F *WToLNu_qcd2; TH1F *background_qcd2;
TH1F *ttW_qcd2; TH1F *ttZ_qcd2; TH1F *tZq_qcd2; TH1F *ZZ4_qcd2; TH1F *WZ4_qcd2;

TH1F *data_pdf1; TH1F *tptzm0700lh_pdf1; TH1F *tptzm0900lh_pdf1; TH1F *tptzm1400lh_pdf1; TH1F *tptzm1700lh_pdf1;
TH1F *ZToNuNu_1_pdf1; TH1F *ZToNuNu_2_pdf1; TH1F *ZToNuNu_3_pdf1; TH1F *ZToNuNu_4_pdf1; TH1F *ZToNuNu_5_pdf1; TH1F *ZToNuNu_6_pdf1; TH1F *ZToNuNu_7_pdf1;
TH1F *QCD_1_pdf1; TH1F *QCD_2_pdf1; TH1F *QCD_3_pdf1; TH1F *QCD_4_pdf1; TH1F *QCD_5_pdf1; TH1F *QCD_6_pdf1; TH1F *QCD_7_pdf1;
TH1F *WToLNu_1_pdf1; TH1F *WToLNu_2_pdf1; TH1F *WToLNu_3_pdf1; TH1F *WToLNu_4_pdf1; TH1F *WToLNu_5_pdf1; TH1F *WToLNu_6_pdf1; TH1F *WToLNu_7_pdf1;
TH1F *TT_1_pdf1; TH1F *TT_2_pdf1; TH1F *ST_1_pdf1; TH1F *ST_2_pdf1; TH1F *ST_3_pdf1; TH1F *ST_4_pdf1;
TH1F *ZZ1_pdf1; TH1F *ZZ2_pdf1; TH1F *ZZ3_pdf1; TH1F *WW1_pdf1; TH1F *WW2_pdf1; TH1F *WZ1_pdf1; TH1F *WZ2_pdf1; TH1F *WZ3_pdf1; TH1F *WToLNu_pdf1; TH1F *background_pdf1;
TH1F *ttW_pdf1; TH1F *ttZ_pdf1; TH1F *tZq_pdf1; TH1F *ZZ4_pdf1; TH1F *WZ4_pdf1;

TH1F *data_pdf2; TH1F *tptzm0700lh_pdf2; TH1F *tptzm0900lh_pdf2; TH1F *tptzm1400lh_pdf2; TH1F *tptzm1700lh_pdf2;
TH1F *ZToNuNu_1_pdf2; TH1F *ZToNuNu_2_pdf2; TH1F *ZToNuNu_3_pdf2; TH1F *ZToNuNu_4_pdf2; TH1F *ZToNuNu_5_pdf2; TH1F *ZToNuNu_6_pdf2; TH1F *ZToNuNu_7_pdf2;
TH1F *QCD_1_pdf2; TH1F *QCD_2_pdf2; TH1F *QCD_3_pdf2; TH1F *QCD_4_pdf2; TH1F *QCD_5_pdf2; TH1F *QCD_6_pdf2; TH1F *QCD_7_pdf2;
TH1F *WToLNu_1_pdf2; TH1F *WToLNu_2_pdf2; TH1F *WToLNu_3_pdf2; TH1F *WToLNu_4_pdf2; TH1F *WToLNu_5_pdf2; TH1F *WToLNu_6_pdf2; TH1F *WToLNu_7_pdf2;
TH1F *TT_1_pdf2; TH1F *TT_2_pdf2; TH1F *ST_1_pdf2; TH1F *ST_2_pdf2; TH1F *ST_3_pdf2; TH1F *ST_4_pdf2;
TH1F *ZZ1_pdf2; TH1F *ZZ2_pdf2; TH1F *ZZ3_pdf2; TH1F *WW1_pdf2; TH1F *WW2_pdf2; TH1F *WZ1_pdf2; TH1F *WZ2_pdf2; TH1F *WZ3_pdf2; TH1F *WToLNu_pdf2; TH1F *background_pdf2;
TH1F *ttW_pdf2; TH1F *ttZ_pdf2; TH1F *tZq_pdf2; TH1F *ZZ4_pdf2; TH1F *WZ4_pdf2;


TH1F *data_TR1; TH1F *tptzm0700lh_TR1; TH1F *tptzm0900lh_TR1; TH1F *tptzm1400lh_TR1; TH1F *tptzm1700lh_TR1;
TH1F *ZToNuNu_1_TR1; TH1F *ZToNuNu_2_TR1; TH1F *ZToNuNu_3_TR1; TH1F *ZToNuNu_4_TR1; TH1F *ZToNuNu_5_TR1; TH1F *ZToNuNu_6_TR1; TH1F *ZToNuNu_7_TR1;
TH1F *QCD_1_TR1; TH1F *QCD_2_TR1; TH1F *QCD_3_TR1; TH1F *QCD_4_TR1; TH1F *QCD_5_TR1; TH1F *QCD_6_TR1; TH1F *QCD_7_TR1;
TH1F *WToLNu_1_TR1; TH1F *WToLNu_2_TR1; TH1F *WToLNu_3_TR1; TH1F *WToLNu_4_TR1; TH1F *WToLNu_5_TR1; TH1F *WToLNu_6_TR1; TH1F *WToLNu_7_TR1;
TH1F *TT_1_TR1; TH1F *TT_2_TR1; TH1F *ST_1_TR1; TH1F *ST_2_TR1; TH1F *ST_3_TR1; TH1F *ST_4_TR1;
TH1F *ZZ1_TR1; TH1F *ZZ2_TR1; TH1F *ZZ3_TR1; TH1F *WW1_TR1; TH1F *WW2_TR1; TH1F *WZ1_TR1; TH1F *WZ2_TR1; TH1F *WZ3_TR1; TH1F *WToLNu_TR1; TH1F *background_TR1;
TH1F *ttW_TR1; TH1F *ttZ_TR1; TH1F *tZq_TR1; TH1F *ZZ4_TR1; TH1F *WZ4_TR1;


TH1F *data_TR2; TH1F *tptzm0700lh_TR2; TH1F *tptzm0900lh_TR2; TH1F *tptzm1400lh_TR2; TH1F *tptzm1700lh_TR2;
TH1F *ZToNuNu_1_TR2; TH1F *ZToNuNu_2_TR2; TH1F *ZToNuNu_3_TR2; TH1F *ZToNuNu_4_TR2; TH1F *ZToNuNu_5_TR2; TH1F *ZToNuNu_6_TR2; TH1F *ZToNuNu_7_TR2;
TH1F *QCD_1_TR2; TH1F *QCD_2_TR2; TH1F *QCD_3_TR2; TH1F *QCD_4_TR2; TH1F *QCD_5_TR2; TH1F *QCD_6_TR2; TH1F *QCD_7_TR2;
TH1F *WToLNu_1_TR2; TH1F *WToLNu_2_TR2; TH1F *WToLNu_3_TR2; TH1F *WToLNu_4_TR2; TH1F *WToLNu_5_TR2; TH1F *WToLNu_6_TR2; TH1F *WToLNu_7_TR2;
TH1F *TT_1_TR2; TH1F *TT_2_TR2; TH1F *ST_1_TR2; TH1F *ST_2_TR2; TH1F *ST_3_TR2; TH1F *ST_4_TR2;
TH1F *ZZ1_TR2; TH1F *ZZ2_TR2; TH1F *ZZ3_TR2; TH1F *WW1_TR2; TH1F *WW2_TR2; TH1F *WZ1_TR2; TH1F *WZ2_TR2; TH1F *WZ3_TR2; TH1F *WToLNu_TR2; TH1F *background_TR2;
TH1F *ttW_TR2; TH1F *ttZ_TR2; TH1F *tZq_TR2; TH1F *ZZ4_TR2; TH1F *WZ4_TR2;/*}}}*/
