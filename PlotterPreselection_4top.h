void MakeHistos(char CUT[1000],const char *plot,int BIN,float MIN,float MAX,int JETSyst,
		TH1F* &data_func,TH1F* &background_func,TH1F* &ZToNuNu_1_func,TH1F* &ZToNuNu_2_func,TH1F* &ZToNuNu_3_func,TH1F* &ZToNuNu_4_func,TH1F* &ZToNuNu_5_func,TH1F* &ZToNuNu_6_func,TH1F* &ZToNuNu_7_func,
		TH1F* &QCD_1_func,TH1F* &QCD_2_func,TH1F* &QCD_3_func,TH1F* &QCD_4_func,TH1F* &QCD_5_func,TH1F* &QCD_6_func,TH1F* &QCD_7_func,
		TH1F* &WToLNu_1_func,TH1F* &WToLNu_2_func,TH1F* &WToLNu_3_func,TH1F* &WToLNu_4_func,TH1F* &WToLNu_5_func,TH1F* &WToLNu_6_func,TH1F* &WToLNu_7_func,
		TH1F* &TT_1_func,TH1F* &TT_2_func,TH1F* &ST_1_func,TH1F* &ST_2_func,TH1F* &ST_3_func,TH1F* &ST_4_func,
		TH1F* &ZZ1_func,TH1F* &ZZ2_func,TH1F* &ZZ3_func,TH1F* &WW1_func,TH1F* &WW2_func,TH1F* &WZ1_func,TH1F* &WZ2_func,TH1F* &WZ3_func,
		TH1F* &ttW_func,TH1F* &ttZ_func,TH1F* &tZq_func,TH1F* &ZZ4_func,TH1F* &WZ4_func,
		TH1F* &tptzm0700lh_func,TH1F* &tptzm1000lh_func,TH1F* &tptzm1400lh_func,TH1F* &tptzm1700lh_func);
void MakeHistoErrors(int m, TH1F* &histo_SR, TH1F* histo_P1, TH1F* histo_P2, TH1F* histo_F1, TH1F* histo_F2, TH1F* histo_B1, TH1F* histo_B2, TH1F* histo_Z1, TH1F* histo_Z2, TH1F* histo_W1, TH1F* histo_W2, TH1F* histo_T1, TH1F* histo_T2, TH1F* histo_J1, TH1F* histo_J2, TH1F* histo_J3, TH1F* histo_J4, TH1F* histo_qcd1, TH1F* histo_qcd2, TH1F* histo_pdf1, TH1F* histo_pdf2, TH1F* histo_TR1, TH1F* histo_TR2);
void CloneHistos();

int SigSF = 1;
float LUMI  = 41500.0; 
//?where to get this LUMI
/*float w0700 = SigSF*(0.5*0.5*5.820 *0.25*LUMI/388056); //SIG1
float w0800 = SigSF*(0.5*0.5*3.860 *0.25*LUMI/400000.0); //SIG2
float w0900 = SigSF*(0.5*0.5*2.720 *0.25*LUMI/400000.0); //SIG3
float w1000 = SigSF*(0.5*0.5*1.952 *0.25*LUMI/396804.0); //SIG4
float w1100 = SigSF*(0.5*0.5*1.352 *0.25*LUMI/400000.0); //SIG5
float w1200 = SigSF*(0.5*0.5*0.984 *0.25*LUMI/400000.0); //SIG6
float w1300 = SigSF*(0.5*0.5*0.716 *0.25*LUMI/400000.0); //SIG7
float w1400 = SigSF*(0.5*0.5*0.540 *0.25*LUMI/524920.0); //SIG8
float w1500 = SigSF*(0.5*0.5*0.408 *0.25*LUMI/400000.0); //SIG9
float w1600 = SigSF*(0.5*0.5*0.304 *0.25*LUMI/386506.0); //SIG10
float w1700 = SigSF*(0.5*0.5*0.232 *0.25*LUMI/400000.0); //SIG11
float w1800 = SigSF*(0.5*0.5*0.174 *0.25*LUMI/122350.0); //SIG12
float w01 = (384.1*LUMI/(22719867-17399));    //ZToNuNu_HT100to200    
float w02 = (118.1*LUMI/(22281118-29545));     //ZToNuNu_HT200to400    
float w03 = (14.7*LUMI/(125874-283));       //ZToNuNu_HT400to600  
float w04 = (3.35*LUMI/(5681118-16476));     //ZToNuNu_HT600to800        
float w05 = (1.41*LUMI/(2049928-8149));     //ZToNuNu_HT800to1200
float w06 = (0.316*LUMI/(336640-2308));      //ZToNuNu_HT1200to2500      
float w07 = (0.00722*LUMI/(6590-144));      //ZToNuNu_HT2500toInf       
float w08 = (1559000*LUMI/(58615835-33141));       //QCD_HT200to300            
float w09 = (315900*LUMI/(60261123-55454));       //QCD_HT300to500           
float w10 = (29070*LUMI/(55807110-82875));     //QCD_HT500to700            
float w11 = (5962*LUMI/(47621862-102938));    //QCD_HT700to1000           
float w12 = (1005*LUMI/(16540462-55166));   //QCD_HT1000to1500      
float w13 = (101.8*LUMI/(11346246-61670));   //QCD_HT1500to2000      
float w14 = (20.54*LUMI/(5883436-57870));  //QCD_HT2000toInf 
float w15 = (1695.*LUMI/(35628930-28989));    //WToLNu_HT100to200
float w16 = (532.4*LUMI/(21221364-29153));    //WToLNu_HT200to400
float w17 = (61.6*LUMI/(14167255-31319));    //WToLNu_HT400to600
float w18 = (12.4*LUMI/(20704008-60637));    //WToLNu_HT600to800
float w19 = (5.77*LUMI/(17725829-69475));    //WToLNu_HT800to1200
float w20 = (1.023*LUMI/(16115840-106518));    //WToLNu_HT1200to2500
float w21 = (0.0248*LUMI/(9925823-204036));    //WToLNu_HT2500toInf
float w22 = (88.290*LUMI/(67811384-275514));     //TTbar1 2L2Nu
float w23 = (365.34*LUMI/(110673640-449496));    //TTbar2 semileptonic               
float w24 = (80.95*LUMI/64245900);   //ST_t-channel_antitop  
float w25 = (136.02*LUMI/122546500);   //ST_t-channel_top      
float w26 = (38.06*LUMI/(7506372-28818));  //ST_tW_antitop.root     
float w27 = (38.06*LUMI/(7552459-29165));     //ST_tW_top     
float w28 = (1.204*LUMI/(7375752-37377)); //ZZTo4L
float w29 = (3.222*LUMI/(22464492-4961538)); //ZZTo2L2Q
float w30 = (0.5644*LUMI/(8739213-5555)); //ZZTo2L2Nu
float w31 = (10.48*LUMI/(1996263-3737)); //WWTo2L2Nu
float w32 = (43.53*LUMI/(8768702-16658)); //WWToLNuQQ
float w33 = (10.73*LUMI/(15145868-3851450)); //WZTo1L1Nu2Q
float w34 = (5.606*LUMI/(22424294-5533088)); //WZTo2L2Q
float w35 = (4.43*LUMI/(11595047-2660106)); //WZTo3LNu  
float w36 = (0.2125*LUMI/(3698933-1081991)); //TTWToLNu
float w37 = (0.2253*LUMI/(5503976-1973714)); //TTZToLLNuNu
float w38 = (0.1655*LUMI/(606483-356517)); //tZq.root
float w39 = (4.072*LUMI/(50622785-11448369)); //ZZTo2Q2Nu
float w40 = (3.05*LUMI/(3581186-1057330)); //WZTo1L3Nu*/

//???what's these number?where to get these number?
//
float w0700 = SigSF*(0.5*0.5*5.820 *0.25*LUMI/(386981-1075)); //SIG1/*{{{*/
float w0800 = SigSF*(0.5*0.5*3.860 *0.25*LUMI/(398725-1275)); //SIG2
float w0900 = SigSF*(0.5*0.5*2.720 *0.25*LUMI/(398612-1388)); //SIG3
float w1000 = SigSF*(0.5*0.5*1.952 *0.25*LUMI/(395111-1693)); //SIG4
float w1100 = SigSF*(0.5*0.5*1.352 *0.25*LUMI/(398189-1811)); //SIG5
float w1200 = SigSF*(0.5*0.5*0.984 *0.25*LUMI/(398013-1987)); //SIG6
float w1300 = SigSF*(0.5*0.5*0.716 *0.25*LUMI/(397830-2170)); //SIG7
float w1400 = SigSF*(0.5*0.5*0.540 *0.25*LUMI/(397517-2483)); //SIG8
float w1500 = SigSF*(0.5*0.5*0.408 *0.25*LUMI/(397278-2722)); //SIG9
float w1600 = SigSF*(0.5*0.5*0.304 *0.25*LUMI/(383697-2809)); //SIG10
float w1700 = SigSF*(0.5*0.5*0.232 *0.25*LUMI/(396851-3149)); //SIG11
float w1800 = SigSF*(0.5*0.5*0.174 *0.25*LUMI/(382864-3306)); //SIG12
float w01 = (384.1*LUMI/(22719867-17399));    //ZToNuNu_HT100to200    
float w02 = (118.1*LUMI/(21647213-28703));     //ZToNuNu_HT200to400    
float w03 = (14.7*LUMI/(9114505-19615));  //ZToNuNu_HT400to600  
float w04 = (3.35*LUMI/(5681118-16476));     //ZToNuNu_HT600to800        
//float w05 = (1.68*LUMI/(1956431-7779));     //ZToNuNu_HT800to1200 
float w05 = (1.41*LUMI/(2049928-8149));     //ZToNuNu_HT800to1200
float w06 = (0.316*LUMI/(336640-2308));      //ZToNuNu_HT1200to2500      
float w07 = (0.00722*LUMI/(6590-144));      //ZToNuNu_HT2500toInf       
float w08 = (1559000*LUMI/(58900255-33342));       //QCD_HT200to300            
float w09 = (315900*LUMI/(60543436-55717));       //QCD_HT300to500           
float w10 = (29070*LUMI/(56337485-83665));     //QCD_HT500to700            
float w11 = (5962*LUMI/(47891321-103562));    //QCD_HT700to1000           
float w12 = (1005*LUMI/(16540462-55166));   //QCD_HT1000to1500      
float w13 = (101.8*LUMI/(11571519-62915));   //QCD_HT1500to2000      
float w14 = (20.54*LUMI/(5883436-57870));  //QCD_HT2000toInf 
float w15 = (1695.*LUMI/(36219177-29444));    //WToLNu_HT100to200
float w16 = (532.4*LUMI/(21221364-29153));    //WToLNu_HT200to400
float w17 = (61.6*LUMI/(14281694-31580));    //WToLNu_HT400to600
float w18 = (12.4*LUMI/(21645698-63389));    //WToLNu_HT600to800
float w19 = (5.77*LUMI/(20352859-79869));    //WToLNu_HT800to1200
float w20 = (1.023*LUMI/(20125258-133366));    //WToLNu_HT1200to2500
float w21 = (0.0248*LUMI/(20940983-430266));    //WToLNu_HT2500toInf
float w22 = (88.290*LUMI/(66708701-271041));     //TTbar1 2L2Nu
float w23 = (365.34*LUMI/(109485551-444833));    //TTbar2 semileptonic               
float w24 = (80.95*LUMI/64818800);   //ST_t-channel_antitop  
float w25 = (136.02*LUMI/63405500);   //ST_t-channel_top      
float w26 = (38.06*LUMI/(7751218-29652));  //ST_tW_antitop.root     
float w27 = (38.06*LUMI/(7552459-29165));     //ST_tW_top     
float w28 = (1.204*LUMI/(6932744-35109)); //ZZTo4L
float w29 = (3.222*LUMI/(22804606-5036312)); //ZZTo2L2Q
float w30 = (0.5644*LUMI/(8739213-5555)); //ZZTo2L2Nu
float w31 = (10.48*LUMI/(1996263-3737)); //WWTo2L2Nu
float w32 = (43.53*LUMI/(8768702-16658)); //WWToLNuQQ
float w33 = (10.73*LUMI/(15216736-3869637)); //WZTo1L1Nu2Q
float w34 = (5.606*LUMI/(22123387-5458777)); //WZTo2L2Q
float w35 = (4.43*LUMI/(8851251-2030645)); //WZTo3LNu  
float w36 = (0.2125*LUMI/(3806020-1113654)); //TTWToLNu
float w37 = (0.2253*LUMI/(5567105-1996385)); //TTZToLLNuNu
float w38 = (0.1655*LUMI/(606483-356517)); //tZq.root
float w39 = (4.072*LUMI/(50705267-11467047)); //ZZTo2Q2Nu
float w40 = (3.05*LUMI/(4297198-1269149)); //WZTo1L3Nu/*}}}*/

TFile *file01 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/data.root");/*{{{*/
//?whatis the different Tprime files?1
//
TFile *file02 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/Tprime_0700.root");
TFile *file03 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/Tprime_0800.root");
TFile *file04 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/Tprime_0900.root");
TFile *file05 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/Tprime_1000.root");
TFile *file06 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/Tprime_1100.root");
TFile *file07 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/Tprime_1200.root");
TFile *file08 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/Tprime_1300.root");
TFile *file09 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/Tprime_1400.root");
TFile *file10 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/Tprime_1500.root");
TFile *file11 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/Tprime_1600.root");
TFile *file12 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/Tprime_1700.root");
TFile *file13 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/Tprime_1800.root");
TFile *file14 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ZToNuNu_HT100to200.root");
TFile *file15 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ZToNuNu_HT200to400.root");
TFile *file16 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ZToNuNu_HT400to600.root");
TFile *file17 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ZToNuNu_HT600to800.root");
TFile *file18 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ZToNuNu_HT800to1200.root");
TFile *file19 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ZToNuNu_HT1200to2500.root");
TFile *file20 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ZToNuNu_HT2500toInf.root");
TFile *file21 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/QCD_HT200to300.root");
TFile *file22 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/QCD_HT300to500.root");
TFile *file23 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/QCD_HT500to700.root");
TFile *file24 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/QCD_HT700to1000.root");
TFile *file25 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/QCD_HT1000to1500.root");
TFile *file26 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/QCD_HT1500to2000.root");
TFile *file27 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/QCD_HT2000toInf.root");
TFile *file28 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/WToLNu_HT100to200.root");
TFile *file29 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/WToLNu_HT200to400.root");
TFile *file30 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/WToLNu_HT400to600.root");
TFile *file31 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/WToLNu_HT600to800.root");
TFile *file32 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/WToLNu_HT800to1200.root");
TFile *file33 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/WToLNu_HT1200to2500.root");
TFile *file34 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/WToLNu_HT2500toInf.root");
TFile *file35 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/TTTo2L2Nu.root  ");
TFile *file36 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/TTToSemiLeptonic.root");
TFile *file37 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ST_t-channel_antitop.root");
TFile *file38 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ST_t-channel_top.root");
TFile *file39 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ST_tW_antitop.root");
TFile *file40 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ST_tW_top.root");
TFile *file41 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ZZTo4L.root");
TFile *file42 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ZZTo2L2Q.root");
TFile *file43 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ZZTo2L2Nu.root");
TFile *file44 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/WWTo2L2Nu.root");
TFile *file45 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/WWToLNuQQ.root");
TFile *file46 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/WZTo1L1Nu2Q.root ");
TFile *file47 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/WZTo2L2Q.root");
TFile *file48 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/WZTo3LNu.root");
TFile *file49 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/TTWToLNu.root");
TFile *file50 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/TTZToLLNuNu.root");
TFile *file51 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/tZq.root");
TFile *file52 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/ZZTo2Q2Nu.root");
TFile *file53 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/WZTo1L3Nu.root");

TTree *Tree01 = (TTree*)file01->Get("tree");
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
TTree *Tree26 = (TTree*)file26->Get("tree");
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
TTree *Tree43 = (TTree*)file43->Get("tree");
TTree *Tree44 = (TTree*)file44->Get("tree");
TTree *Tree45 = (TTree*)file45->Get("tree");
TTree *Tree46 = (TTree*)file46->Get("tree");
TTree *Tree47 = (TTree*)file47->Get("tree");
TTree *Tree48 = (TTree*)file48->Get("tree");
TTree *Tree49 = (TTree*)file49->Get("tree");
TTree *Tree50 = (TTree*)file50->Get("tree");
TTree *Tree51 = (TTree*)file51->Get("tree");
TTree *Tree52 = (TTree*)file52->Get("tree");
TTree *Tree53 = (TTree*)file53->Get("tree");/*}}}*/

TFile *file01_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/data.root");/*{{{*/
TFile *file02_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/Tprime_0700.root");
TFile *file03_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/Tprime_0800.root");
TFile *file04_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/Tprime_0900.root");
TFile *file05_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/Tprime_1000.root");
TFile *file06_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/Tprime_1100.root");
TFile *file07_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/Tprime_1200.root");
TFile *file08_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/Tprime_1300.root");
TFile *file09_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/Tprime_1400.root");
TFile *file10_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/Tprime_1500.root");
TFile *file11_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/Tprime_1600.root");
TFile *file12_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/Tprime_1700.root");
TFile *file13_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/Tprime_1800.root");
TFile *file14_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ZToNuNu_HT100to200.root");
TFile *file15_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ZToNuNu_HT200to400.root");
TFile *file16_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ZToNuNu_HT400to600.root");
TFile *file17_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ZToNuNu_HT600to800.root");
TFile *file18_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ZToNuNu_HT800to1200.root");
TFile *file19_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ZToNuNu_HT1200to2500.root");
TFile *file20_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ZToNuNu_HT2500toInf.root");
TFile *file21_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/QCD_HT200to300.root");
TFile *file22_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/QCD_HT300to500.root");
TFile *file23_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/QCD_HT500to700.root");
TFile *file24_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/QCD_HT700to1000.root");
TFile *file25_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/QCD_HT1000to1500.root");
TFile *file26_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/QCD_HT1500to2000.root");
TFile *file27_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/QCD_HT2000toInf.root");
TFile *file28_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/WToLNu_HT100to200.root");
TFile *file29_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/WToLNu_HT200to400.root");
TFile *file30_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/WToLNu_HT400to600.root");
TFile *file31_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/WToLNu_HT600to800.root");
TFile *file32_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/WToLNu_HT800to1200.root");
TFile *file33_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/WToLNu_HT1200to2500.root");
TFile *file34_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/WToLNu_HT2500toInf.root");
TFile *file35_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/TTTo2L2Nu.root  ");
TFile *file36_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/TTToSemiLeptonic.root");
TFile *file37_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ST_t-channel_antitop.root");
TFile *file38_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ST_t-channel_top.root");
TFile *file39_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ST_tW_antitop.root");
TFile *file40_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ST_tW_top.root");
TFile *file41_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ZZTo4L.root");
TFile *file42_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ZZTo2L2Q.root");
TFile *file43_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ZZTo2L2Nu.root");
TFile *file44_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/WWTo2L2Nu.root");
TFile *file45_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/WWToLNuQQ.root");
TFile *file46_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/WZTo1L1Nu2Q.root ");
TFile *file47_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/WZTo2L2Q.root");
TFile *file48_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/WZTo3LNu.root");
TFile *file49_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/TTWToLNu.root");
TFile *file50_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/TTZToLLNuNu.root");
TFile *file51_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/tZq.root");
TFile *file52_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/ZZTo2Q2Nu.root");
TFile *file53_J1 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESup/WZTo1L3Nu.root");
TTree *Tree01_J1 = (TTree*)file01_J1->Get("tree");
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
TTree *Tree14_J1 = (TTree*)file14_J1->Get("tree");
TTree *Tree15_J1 = (TTree*)file15_J1->Get("tree");
TTree *Tree16_J1 = (TTree*)file16_J1->Get("tree");
TTree *Tree17_J1 = (TTree*)file17_J1->Get("tree");
TTree *Tree18_J1 = (TTree*)file18_J1->Get("tree");
TTree *Tree19_J1 = (TTree*)file19_J1->Get("tree");
TTree *Tree20_J1 = (TTree*)file20_J1->Get("tree");
TTree *Tree21_J1 = (TTree*)file21_J1->Get("tree");
TTree *Tree22_J1 = (TTree*)file22_J1->Get("tree");
TTree *Tree23_J1 = (TTree*)file23_J1->Get("tree");
TTree *Tree24_J1 = (TTree*)file24_J1->Get("tree");
TTree *Tree25_J1 = (TTree*)file25_J1->Get("tree");
TTree *Tree26_J1 = (TTree*)file26_J1->Get("tree");
TTree *Tree27_J1 = (TTree*)file27_J1->Get("tree");
TTree *Tree28_J1 = (TTree*)file28_J1->Get("tree");
TTree *Tree29_J1 = (TTree*)file29_J1->Get("tree");
TTree *Tree30_J1 = (TTree*)file30_J1->Get("tree");
TTree *Tree31_J1 = (TTree*)file31_J1->Get("tree");
TTree *Tree32_J1 = (TTree*)file32_J1->Get("tree");
TTree *Tree33_J1 = (TTree*)file33_J1->Get("tree");
TTree *Tree34_J1 = (TTree*)file34_J1->Get("tree");
TTree *Tree35_J1 = (TTree*)file35_J1->Get("tree");
TTree *Tree36_J1 = (TTree*)file36_J1->Get("tree");
TTree *Tree37_J1 = (TTree*)file37_J1->Get("tree");
TTree *Tree38_J1 = (TTree*)file38_J1->Get("tree");
TTree *Tree39_J1 = (TTree*)file39_J1->Get("tree");
TTree *Tree40_J1 = (TTree*)file40_J1->Get("tree");
TTree *Tree41_J1 = (TTree*)file41_J1->Get("tree");
TTree *Tree42_J1 = (TTree*)file42_J1->Get("tree");
TTree *Tree43_J1 = (TTree*)file43_J1->Get("tree");
TTree *Tree44_J1 = (TTree*)file44_J1->Get("tree");
TTree *Tree45_J1 = (TTree*)file45_J1->Get("tree");
TTree *Tree46_J1 = (TTree*)file46_J1->Get("tree");
TTree *Tree47_J1 = (TTree*)file47_J1->Get("tree");
TTree *Tree48_J1 = (TTree*)file48_J1->Get("tree");
TTree *Tree49_J1 = (TTree*)file49_J1->Get("tree");
TTree *Tree50_J1 = (TTree*)file50_J1->Get("tree");
TTree *Tree51_J1 = (TTree*)file51_J1->Get("tree");
TTree *Tree52_J1 = (TTree*)file52_J1->Get("tree");
TTree *Tree53_J1 = (TTree*)file53_J1->Get("tree");/*}}}*/

TFile *file01_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/data.root");/*{{{*/
TFile *file02_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/Tprime_0700.root");
TFile *file03_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/Tprime_0800.root");
TFile *file04_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/Tprime_0900.root");
TFile *file05_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/Tprime_1000.root");
TFile *file06_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/Tprime_1100.root");
TFile *file07_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/Tprime_1200.root");
TFile *file08_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/Tprime_1300.root");
TFile *file09_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/Tprime_1400.root");
TFile *file10_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/Tprime_1500.root");
TFile *file11_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/Tprime_1600.root");
TFile *file12_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/Tprime_1700.root");
TFile *file13_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/Tprime_1800.root");
TFile *file14_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ZToNuNu_HT100to200.root");
TFile *file15_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ZToNuNu_HT200to400.root");
TFile *file16_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ZToNuNu_HT400to600.root");
TFile *file17_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ZToNuNu_HT600to800.root");
TFile *file18_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ZToNuNu_HT800to1200.root");
TFile *file19_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ZToNuNu_HT1200to2500.root");
TFile *file20_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ZToNuNu_HT2500toInf.root");
TFile *file21_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/QCD_HT200to300.root");
TFile *file22_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/QCD_HT300to500.root");
TFile *file23_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/QCD_HT500to700.root");
TFile *file24_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/QCD_HT700to1000.root");
TFile *file25_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/QCD_HT1000to1500.root");
TFile *file26_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/QCD_HT1500to2000.root");
TFile *file27_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/QCD_HT2000toInf.root");
TFile *file28_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/WToLNu_HT100to200.root");
TFile *file29_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/WToLNu_HT200to400.root");
TFile *file30_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/WToLNu_HT400to600.root");
TFile *file31_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/WToLNu_HT600to800.root");
TFile *file32_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/WToLNu_HT800to1200.root");
TFile *file33_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/WToLNu_HT1200to2500.root");
TFile *file34_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/WToLNu_HT2500toInf.root");
TFile *file35_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/TTTo2L2Nu.root  ");
TFile *file36_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/TTToSemiLeptonic.root");
TFile *file37_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ST_t-channel_antitop.root");
TFile *file38_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ST_t-channel_top.root");
TFile *file39_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ST_tW_antitop.root");
TFile *file40_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ST_tW_top.root");
TFile *file41_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ZZTo4L.root");
TFile *file42_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ZZTo2L2Q.root");
TFile *file43_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ZZTo2L2Nu.root");
TFile *file44_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/WWTo2L2Nu.root");
TFile *file45_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/WWToLNuQQ.root");
TFile *file46_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/WZTo1L1Nu2Q.root ");
TFile *file47_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/WZTo2L2Q.root");
TFile *file48_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/WZTo3LNu.root");
TFile *file49_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/TTWToLNu.root");
TFile *file50_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/TTZToLLNuNu.root");
TFile *file51_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/tZq.root");
TFile *file52_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/ZZTo2Q2Nu.root");
TFile *file53_J2 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JESdo/WZTo1L3Nu.root");
TTree *Tree01_J2 = (TTree*)file01_J2->Get("tree");
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
TTree *Tree14_J2 = (TTree*)file14_J2->Get("tree");
TTree *Tree15_J2 = (TTree*)file15_J2->Get("tree");
TTree *Tree16_J2 = (TTree*)file16_J2->Get("tree");
TTree *Tree17_J2 = (TTree*)file17_J2->Get("tree");
TTree *Tree18_J2 = (TTree*)file18_J2->Get("tree");
TTree *Tree19_J2 = (TTree*)file19_J2->Get("tree");
TTree *Tree20_J2 = (TTree*)file20_J2->Get("tree");
TTree *Tree21_J2 = (TTree*)file21_J2->Get("tree");
TTree *Tree22_J2 = (TTree*)file22_J2->Get("tree");
TTree *Tree23_J2 = (TTree*)file23_J2->Get("tree");
TTree *Tree24_J2 = (TTree*)file24_J2->Get("tree");
TTree *Tree25_J2 = (TTree*)file25_J2->Get("tree");
TTree *Tree26_J2 = (TTree*)file26_J2->Get("tree");
TTree *Tree27_J2 = (TTree*)file27_J2->Get("tree");
TTree *Tree28_J2 = (TTree*)file28_J2->Get("tree");
TTree *Tree29_J2 = (TTree*)file29_J2->Get("tree");
TTree *Tree30_J2 = (TTree*)file30_J2->Get("tree");
TTree *Tree31_J2 = (TTree*)file31_J2->Get("tree");
TTree *Tree32_J2 = (TTree*)file32_J2->Get("tree");
TTree *Tree33_J2 = (TTree*)file33_J2->Get("tree");
TTree *Tree34_J2 = (TTree*)file34_J2->Get("tree");
TTree *Tree35_J2 = (TTree*)file35_J2->Get("tree");
TTree *Tree36_J2 = (TTree*)file36_J2->Get("tree");
TTree *Tree37_J2 = (TTree*)file37_J2->Get("tree");
TTree *Tree38_J2 = (TTree*)file38_J2->Get("tree");
TTree *Tree39_J2 = (TTree*)file39_J2->Get("tree");
TTree *Tree40_J2 = (TTree*)file40_J2->Get("tree");
TTree *Tree41_J2 = (TTree*)file41_J2->Get("tree");
TTree *Tree42_J2 = (TTree*)file42_J2->Get("tree");
TTree *Tree43_J2 = (TTree*)file43_J2->Get("tree");
TTree *Tree44_J2 = (TTree*)file44_J2->Get("tree");
TTree *Tree45_J2 = (TTree*)file45_J2->Get("tree");
TTree *Tree46_J2 = (TTree*)file46_J2->Get("tree");
TTree *Tree47_J2 = (TTree*)file47_J2->Get("tree");
TTree *Tree48_J2 = (TTree*)file48_J2->Get("tree");
TTree *Tree49_J2 = (TTree*)file49_J2->Get("tree");
TTree *Tree50_J2 = (TTree*)file50_J2->Get("tree");
TTree *Tree51_J2 = (TTree*)file51_J2->Get("tree");
TTree *Tree52_J2 = (TTree*)file52_J2->Get("tree");
TTree *Tree53_J2 = (TTree*)file53_J2->Get("tree");/*}}}*/

TFile *file01_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/data.root");/*{{{*/
TFile *file02_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/Tprime_0700.root");
TFile *file03_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/Tprime_0800.root");
TFile *file04_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/Tprime_0900.root");
TFile *file05_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/Tprime_1000.root");
TFile *file06_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/Tprime_1100.root");
TFile *file07_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/Tprime_1200.root");
TFile *file08_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/Tprime_1300.root");
TFile *file09_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/Tprime_1400.root");
TFile *file10_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/Tprime_1500.root");
TFile *file11_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/Tprime_1600.root");
TFile *file12_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/Tprime_1700.root");
TFile *file13_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/Tprime_1800.root");
TFile *file14_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ZToNuNu_HT100to200.root");
TFile *file15_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ZToNuNu_HT200to400.root");
TFile *file16_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ZToNuNu_HT400to600.root");
TFile *file17_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ZToNuNu_HT600to800.root");
TFile *file18_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ZToNuNu_HT800to1200.root");
TFile *file19_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ZToNuNu_HT1200to2500.root");
TFile *file20_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ZToNuNu_HT2500toInf.root");
TFile *file21_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/QCD_HT200to300.root");
TFile *file22_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/QCD_HT300to500.root");
TFile *file23_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/QCD_HT500to700.root");
TFile *file24_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/QCD_HT700to1000.root");
TFile *file25_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/QCD_HT1000to1500.root");
TFile *file26_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/QCD_HT1500to2000.root");
TFile *file27_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/QCD_HT2000toInf.root");
TFile *file28_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/WToLNu_HT100to200.root");
TFile *file29_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/WToLNu_HT200to400.root");
TFile *file30_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/WToLNu_HT400to600.root");
TFile *file31_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/WToLNu_HT600to800.root");
TFile *file32_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/WToLNu_HT800to1200.root");
TFile *file33_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/WToLNu_HT1200to2500.root");
TFile *file34_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/WToLNu_HT2500toInf.root");
TFile *file35_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/TTTo2L2Nu.root  ");
TFile *file36_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/TTToSemiLeptonic.root");
TFile *file37_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ST_t-channel_antitop.root");
TFile *file38_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ST_t-channel_top.root");
TFile *file39_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ST_tW_antitop.root");
TFile *file40_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ST_tW_top.root");
TFile *file41_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ZZTo4L.root");
TFile *file42_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ZZTo2L2Q.root");
TFile *file43_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ZZTo2L2Nu.root");
TFile *file44_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/WWTo2L2Nu.root");
TFile *file45_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/WWToLNuQQ.root");
TFile *file46_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/WZTo1L1Nu2Q.root ");
TFile *file47_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/WZTo2L2Q.root");
TFile *file48_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/WZTo3LNu.root");
TFile *file49_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/TTWToLNu.root");
TFile *file50_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/TTZToLLNuNu.root");
TFile *file51_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/tZq.root");
TFile *file52_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/ZZTo2Q2Nu.root");
TFile *file53_J3 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERup/WZTo1L3Nu.root");
TTree *Tree01_J3 = (TTree*)file01_J3->Get("tree");
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
TTree *Tree14_J3 = (TTree*)file14_J3->Get("tree");
TTree *Tree15_J3 = (TTree*)file15_J3->Get("tree");
TTree *Tree16_J3 = (TTree*)file16_J3->Get("tree");
TTree *Tree17_J3 = (TTree*)file17_J3->Get("tree");
TTree *Tree18_J3 = (TTree*)file18_J3->Get("tree");
TTree *Tree19_J3 = (TTree*)file19_J3->Get("tree");
TTree *Tree20_J3 = (TTree*)file20_J3->Get("tree");
TTree *Tree21_J3 = (TTree*)file21_J3->Get("tree");
TTree *Tree22_J3 = (TTree*)file22_J3->Get("tree");
TTree *Tree23_J3 = (TTree*)file23_J3->Get("tree");
TTree *Tree24_J3 = (TTree*)file24_J3->Get("tree");
TTree *Tree25_J3 = (TTree*)file25_J3->Get("tree");
TTree *Tree26_J3 = (TTree*)file26_J3->Get("tree");
TTree *Tree27_J3 = (TTree*)file27_J3->Get("tree");
TTree *Tree28_J3 = (TTree*)file28_J3->Get("tree");
TTree *Tree29_J3 = (TTree*)file29_J3->Get("tree");
TTree *Tree30_J3 = (TTree*)file30_J3->Get("tree");
TTree *Tree31_J3 = (TTree*)file31_J3->Get("tree");
TTree *Tree32_J3 = (TTree*)file32_J3->Get("tree");
TTree *Tree33_J3 = (TTree*)file33_J3->Get("tree");
TTree *Tree34_J3 = (TTree*)file34_J3->Get("tree");
TTree *Tree35_J3 = (TTree*)file35_J3->Get("tree");
TTree *Tree36_J3 = (TTree*)file36_J3->Get("tree");
TTree *Tree37_J3 = (TTree*)file37_J3->Get("tree");
TTree *Tree38_J3 = (TTree*)file38_J3->Get("tree");
TTree *Tree39_J3 = (TTree*)file39_J3->Get("tree");
TTree *Tree40_J3 = (TTree*)file40_J3->Get("tree");
TTree *Tree41_J3 = (TTree*)file41_J3->Get("tree");
TTree *Tree42_J3 = (TTree*)file42_J3->Get("tree");
TTree *Tree43_J3 = (TTree*)file43_J3->Get("tree");
TTree *Tree44_J3 = (TTree*)file44_J3->Get("tree");
TTree *Tree45_J3 = (TTree*)file45_J3->Get("tree");
TTree *Tree46_J3 = (TTree*)file46_J3->Get("tree");
TTree *Tree47_J3 = (TTree*)file47_J3->Get("tree");
TTree *Tree48_J3 = (TTree*)file48_J3->Get("tree");
TTree *Tree49_J3 = (TTree*)file49_J3->Get("tree");
TTree *Tree50_J3 = (TTree*)file50_J3->Get("tree");
TTree *Tree51_J3 = (TTree*)file51_J3->Get("tree");
TTree *Tree52_J3 = (TTree*)file52_J3->Get("tree");
TTree *Tree53_J3 = (TTree*)file53_J3->Get("tree");/*}}}*/

TFile *file01_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/data.root");/*{{{*/
TFile *file02_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/Tprime_0700.root");
TFile *file03_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/Tprime_0800.root");
TFile *file04_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/Tprime_0900.root");
TFile *file05_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/Tprime_1000.root");
TFile *file06_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/Tprime_1100.root");
TFile *file07_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/Tprime_1200.root");
TFile *file08_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/Tprime_1300.root");
TFile *file09_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/Tprime_1400.root");
TFile *file10_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/Tprime_1500.root");
TFile *file11_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/Tprime_1600.root");
TFile *file12_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/Tprime_1700.root");
TFile *file13_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/Tprime_1800.root");
TFile *file14_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ZToNuNu_HT100to200.root");
TFile *file15_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ZToNuNu_HT200to400.root");
TFile *file16_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ZToNuNu_HT400to600.root");
TFile *file17_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ZToNuNu_HT600to800.root");
TFile *file18_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ZToNuNu_HT800to1200.root");
TFile *file19_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ZToNuNu_HT1200to2500.root");
TFile *file20_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ZToNuNu_HT2500toInf.root");
TFile *file21_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/QCD_HT200to300.root");
TFile *file22_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/QCD_HT300to500.root");
TFile *file23_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/QCD_HT500to700.root");
TFile *file24_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/QCD_HT700to1000.root");
TFile *file25_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/QCD_HT1000to1500.root");
TFile *file26_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/QCD_HT1500to2000.root");
TFile *file27_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/QCD_HT2000toInf.root");
TFile *file28_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/WToLNu_HT100to200.root");
TFile *file29_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/WToLNu_HT200to400.root");
TFile *file30_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/WToLNu_HT400to600.root");
TFile *file31_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/WToLNu_HT600to800.root");
TFile *file32_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/WToLNu_HT800to1200.root");
TFile *file33_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/WToLNu_HT1200to2500.root");
TFile *file34_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/WToLNu_HT2500toInf.root");
TFile *file35_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/TTTo2L2Nu.root  ");
TFile *file36_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/TTToSemiLeptonic.root");
TFile *file37_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ST_t-channel_antitop.root");
TFile *file38_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ST_t-channel_top.root");
TFile *file39_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ST_tW_antitop.root");
TFile *file40_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ST_tW_top.root");
TFile *file41_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ZZTo4L.root");
TFile *file42_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ZZTo2L2Q.root");
TFile *file43_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ZZTo2L2Nu.root");
TFile *file44_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/WWTo2L2Nu.root");
TFile *file45_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/WWToLNuQQ.root");
TFile *file46_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/WZTo1L1Nu2Q.root ");
TFile *file47_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/WZTo2L2Q.root");
TFile *file48_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/WZTo3LNu.root");
TFile *file49_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/TTWToLNu.root");
TFile *file50_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/TTZToLLNuNu.root");
TFile *file51_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/tZq.root");
TFile *file52_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/ZZTo2Q2Nu.root");
TFile *file53_J4 = TFile::Open("/publicfs/cms/user/huahuil/Preselection_new_v11/JERdo/WZTo1L3Nu.root");
TTree *Tree01_J4 = (TTree*)file01_J4->Get("tree");
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
TTree *Tree14_J4 = (TTree*)file14_J4->Get("tree");
TTree *Tree15_J4 = (TTree*)file15_J4->Get("tree");
TTree *Tree16_J4 = (TTree*)file16_J4->Get("tree");
TTree *Tree17_J4 = (TTree*)file17_J4->Get("tree");
TTree *Tree18_J4 = (TTree*)file18_J4->Get("tree");
TTree *Tree19_J4 = (TTree*)file19_J4->Get("tree");
TTree *Tree20_J4 = (TTree*)file20_J4->Get("tree");
TTree *Tree21_J4 = (TTree*)file21_J4->Get("tree");
TTree *Tree22_J4 = (TTree*)file22_J4->Get("tree");
TTree *Tree23_J4 = (TTree*)file23_J4->Get("tree");
TTree *Tree24_J4 = (TTree*)file24_J4->Get("tree");
TTree *Tree25_J4 = (TTree*)file25_J4->Get("tree");
TTree *Tree26_J4 = (TTree*)file26_J4->Get("tree");
TTree *Tree27_J4 = (TTree*)file27_J4->Get("tree");
TTree *Tree28_J4 = (TTree*)file28_J4->Get("tree");
TTree *Tree29_J4 = (TTree*)file29_J4->Get("tree");
TTree *Tree30_J4 = (TTree*)file30_J4->Get("tree");
TTree *Tree31_J4 = (TTree*)file31_J4->Get("tree");
TTree *Tree32_J4 = (TTree*)file32_J4->Get("tree");
TTree *Tree33_J4 = (TTree*)file33_J4->Get("tree");
TTree *Tree34_J4 = (TTree*)file34_J4->Get("tree");
TTree *Tree35_J4 = (TTree*)file35_J4->Get("tree");
TTree *Tree36_J4 = (TTree*)file36_J4->Get("tree");
TTree *Tree37_J4 = (TTree*)file37_J4->Get("tree");
TTree *Tree38_J4 = (TTree*)file38_J4->Get("tree");
TTree *Tree39_J4 = (TTree*)file39_J4->Get("tree");
TTree *Tree40_J4 = (TTree*)file40_J4->Get("tree");
TTree *Tree41_J4 = (TTree*)file41_J4->Get("tree");
TTree *Tree42_J4 = (TTree*)file42_J4->Get("tree");
TTree *Tree43_J4 = (TTree*)file43_J4->Get("tree");
TTree *Tree44_J4 = (TTree*)file44_J4->Get("tree");
TTree *Tree45_J4 = (TTree*)file45_J4->Get("tree");
TTree *Tree46_J4 = (TTree*)file46_J4->Get("tree");
TTree *Tree47_J4 = (TTree*)file47_J4->Get("tree");
TTree *Tree48_J4 = (TTree*)file48_J4->Get("tree");
TTree *Tree49_J4 = (TTree*)file49_J4->Get("tree");
TTree *Tree50_J4 = (TTree*)file50_J4->Get("tree");
TTree *Tree51_J4 = (TTree*)file51_J4->Get("tree");
TTree *Tree52_J4 = (TTree*)file52_J4->Get("tree");
TTree *Tree53_J4 = (TTree*)file53_J4->Get("tree");/*}}}*/

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
