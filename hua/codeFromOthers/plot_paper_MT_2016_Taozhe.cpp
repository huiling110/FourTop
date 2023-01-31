#include "plot_paper_MT_2016.h"

void plot_paper_MT_2016(){ 
  gROOT->Reset();
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1,0);
  gStyle->SetTitleX(0.5); //title X location 
  gStyle->SetTitleY(0.96); //title Y location 
  gStyle->SetPaintTextFormat(".2f");
  gErrorIgnoreLevel = kError;
  using namespace std; 

  bool SYST = true;
 
  int year = 2016;
  vector<TString> name;                vector<int> bin;      vector<float> Min;      vector<float> Max;     vector<TString> axis;
  /*
  name.push_back("Jet1ResolvedPt"); bin.push_back(40);     Min.push_back(0);    Max.push_back(1600);    axis.push_back("jet1(resolved) pt [GeV]");
  name.push_back("Jet2ResolvedPt"); bin.push_back(40);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("jet2(resolved) pt [GeV]");
  name.push_back("Jet3ResolvedPt"); bin.push_back(40);     Min.push_back(0);    Max.push_back(900);    axis.push_back("jet3(resolved) pt [GeV]");

  name.push_back("Jet1ResolvedEta"); bin.push_back(40);     Min.push_back(-2.5);    Max.push_back(2.5);    axis.push_back("jet1(resolved) #eta");
  name.push_back("Jet2ResolvedEta"); bin.push_back(40);     Min.push_back(-2.5);    Max.push_back(2.5);    axis.push_back("jet2(resolved) #eta");
  name.push_back("Jet3ResolvedEta"); bin.push_back(40);     Min.push_back(-2.5);    Max.push_back(2.5);    axis.push_back("jet3(resolved) #eta");
  
  name.push_back("TopMass"); bin.push_back(20);     Min.push_back(0);    Max.push_back(500);    axis.push_back("Top Mass[GeV]");
  name.push_back("TopPt");   bin.push_back(40);     Min.push_back(200);    Max.push_back(1700);   axis.push_back("Top pt[GeV] ");
  name.push_back("TopEta");  bin.push_back(40);     Min.push_back(-3);   Max.push_back(3);      axis.push_back("Top #eta");
  */
  //name.push_back("Met_pt");  bin.push_back(40);     Min.push_back(200);    Max.push_back(1700);   axis.push_back("Met pt[GeV] ");
  //name.push_back("Met_phi"); bin.push_back(40);     Min.push_back(-3);   Max.push_back(3);      axis.push_back("Met #phi");
  name.push_back("TransverseMassMetTop"); bin.push_back(25);     Min.push_back(500);    Max.push_back(3000);    axis.push_back("TransverseMassMetTop");
  
  //name.push_back("deltaPhiMetTop"); bin.push_back(30);     Min.push_back(0);    Max.push_back(3);    axis.push_back("#Delta#phi(Met,top)");
  //name.push_back("MinDeltaPhiJetMet"); bin.push_back(30);     Min.push_back(0);    Max.push_back(3);    axis.push_back("Min#Delta#phi(Met,Jet)");
  //name.push_back("HT"); bin.push_back(36);     Min.push_back(200);    Max.push_back(3000);    axis.push_back("HT pt[GeV]");
  //name.push_back("MHT"); bin.push_back(40);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("MHT pt[GeV]");
  /*
  name.push_back("MostForwardJetPt"); bin.push_back(40);     Min.push_back(0);    Max.push_back(1500);    axis.push_back("Most Forward Jet pt [GeV]");
  name.push_back("MostForwardJetEta"); bin.push_back(40);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("Most Forward Jet #eta");
  name.push_back("NumSelForwardJets"); bin.push_back(5);     Min.push_back(-0.5);    Max.push_back(5.5);    axis.push_back("Number of forward jets");
  
  name.push_back("NumSelBJetsM");      bin.push_back(5);     Min.push_back(-0.5);    Max.push_back(5.5);    axis.push_back("Number of medium b-jets");
  name.push_back("NVertices"); bin.push_back(80);     Min.push_back(0);    Max.push_back(80);    axis.push_back("Number of vertices");
  name.push_back("NumSelJets");      bin.push_back(11);     Min.push_back(-0.5);    Max.push_back(10.5);    axis.push_back("Number of jets"); 
  */
  for(int i=0; i<name.size(); i++){
    const char *plot = name[i];
    char CUT[1000]; char CUTpre[1000]; char CUTpup1[1000]; char CUTpup2[1000]; char CUTbta1[1000]; char CUTbta2[1000];  char CUTfor1[1000]; char CUTfor2[1000]; char CUTwje1[1000]; char CUTwje2[1000]; char CUTzje1[1000];  char CUTzje2[1000];  char CUTttb1[1000];  char CUTttb2[1000];  char CUTfir1[1000];  char CUTfir2[1000];char CUTqcd1[1000]; char CUTqcd2[1000];char CUTpdf1[1000]; char CUTpdf2[1000]; char CUTtri1[1000]; char CUTtri2[1000];
    
     for(int category=0; category<2; category++){    
      
        if(category==0) sprintf(CUTpre,"((category0==1)&&(Jet1ResolvedPt>0)&&(Jet2ResolvedPt>0)&&(Jet3ResolvedPt>0)&&(MinDeltaPhiJetMet>0.6)&&(TransverseMassMetTop>500)&&(NumSelLeps==0)&&(TopPt>250)&&(MostForwardJetEta>-4&&MostForwardJetEta<4)&&(NumSelForwardJets==0))");	
        if(category==1) sprintf(CUTpre,"((category0==1)&&(Jet1ResolvedPt>0)&&(Jet2ResolvedPt>0)&&(Jet3ResolvedPt>0)&&(MinDeltaPhiJetMet>0.6)&&(TransverseMassMetTop>500)&&(NumSelLeps==0)&&(TopPt>250)&&(MostForwardJetEta>-4&&MostForwardJetEta<4)&&(NumSelForwardJets>0))");	
	sprintf(CUT,    "PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *w_ZToNuNu  *w_WToLNu  *w_ttbar *%s",CUTpre);
	//sprintf(CUT,    "PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig      *%s",CUTpre);
        /*	
        sprintf(CUTpup1,"PUWeightUP  *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
	sprintf(CUTpup2,"PUWeightDOWN*w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
	sprintf(CUTfir1,"PUWeight    *w_Btag    *genWeight  *prefiringweightup  *w_Trig  *%s",CUTpre);
	sprintf(CUTfir2,"PUWeight    *w_Btag    *genWeight  *prefiringweightdown*w_Trig  *%s",CUTpre);
	sprintf(CUTbta1,"PUWeight    *w_BtagUp  *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
	sprintf(CUTbta2,"PUWeight    *w_BtagDown*genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
	sprintf(CUTzje1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
	sprintf(CUTzje2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
	sprintf(CUTwje1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
	sprintf(CUTwje2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
	sprintf(CUTttb1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
	sprintf(CUTttb2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
	sprintf(CUTqcd1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_QCDUp    *%s",CUTpre);
	sprintf(CUTqcd2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_QCDDown  *%s",CUTpre);
	sprintf(CUTpdf1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_PDFUp    *%s",CUTpre);
	sprintf(CUTpdf2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_PDFDown  *%s",CUTpre);
        sprintf(CUTtri1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_TrigUp   *%s",CUTpre);
        sprintf(CUTtri2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_TrigDown *%s",CUTpre);
        */
        	
        sprintf(CUTpup1,"PUWeightUP  *w_Btag    *genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        sprintf(CUTpup2,"PUWeightDOWN*w_Btag    *genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        sprintf(CUTfir1,"PUWeight    *w_Btag    *genWeight  *prefiringweightup  *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        sprintf(CUTfir2,"PUWeight    *w_Btag    *genWeight  *prefiringweightdown*w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        sprintf(CUTbta1,"PUWeight    *w_BtagUp  *genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        sprintf(CUTbta2,"PUWeight    *w_BtagDown*genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        sprintf(CUTzje1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        sprintf(CUTzje2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        sprintf(CUTwje1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        sprintf(CUTwje2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        sprintf(CUTttb1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        sprintf(CUTttb2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        sprintf(CUTqcd1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *w_QCDUp   *%s",CUTpre);
        sprintf(CUTqcd2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *w_QCDDown *%s",CUTpre);
        sprintf(CUTpdf1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *w_PDFUp   *%s",CUTpre);
        sprintf(CUTpdf2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig*w_ZToNuNu    *w_WToLNu    *w_ttbar  *w_PDFDown *%s",CUTpre);
        sprintf(CUTtri1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_TrigUp   *w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        sprintf(CUTtri2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_TrigDown *w_ZToNuNu    *w_WToLNu    *w_ttbar  *%s",CUTpre);
        
	MakeHistos(CUT,plot,bin[i],Min[i],Max[i],0,data_SR,background_SR,ZToNuNu_1_SR,ZToNuNu_2_SR,ZToNuNu_3_SR,ZToNuNu_4_SR,ZToNuNu_5_SR,ZToNuNu_6_SR,ZToNuNu_7_SR,
			QCD_1_SR,QCD_2_SR,QCD_3_SR,QCD_4_SR,QCD_5_SR,QCD_6_SR,QCD_7_SR,WToLNu_1_SR,WToLNu_2_SR,WToLNu_3_SR,WToLNu_4_SR,WToLNu_5_SR,WToLNu_6_SR,WToLNu_7_SR,
			TT_1_SR,TT_2_SR,ST_1_SR,ST_2_SR,ST_3_SR,ST_4_SR,ZZ1_SR,ZZ2_SR,ZZ3_SR,WW1_SR,WW2_SR,WZ1_SR,WZ2_SR,WZ3_SR,ttW_SR,ttZ_SR,tZq_SR,ZZ4_SR,WZ4_SR,
			tptzm0800lh_SR,tptzm1200lh_SR,tptzm1600lh_SR,tptzm1700lh_SR);
       
	if(SYST){
	MakeHistos(CUTpup1,plot,bin[i],Min[i],Max[i],0,data_P1,background_P1,ZToNuNu_1_P1,ZToNuNu_2_P1,ZToNuNu_3_P1,ZToNuNu_4_P1,ZToNuNu_5_P1,ZToNuNu_6_P1,ZToNuNu_7_P1,
		       QCD_1_P1,QCD_2_P1,QCD_3_P1,QCD_4_P1,QCD_5_P1,QCD_6_P1,QCD_7_P1,WToLNu_1_P1,WToLNu_2_P1,WToLNu_3_P1,WToLNu_4_P1,WToLNu_5_P1,WToLNu_6_P1,WToLNu_7_P1,
			   TT_1_P1,TT_2_P1,ST_1_P1,ST_2_P1,ST_3_P1,ST_4_P1,ZZ1_P1,ZZ2_P1,ZZ3_P1,WW1_P1,WW2_P1,WZ1_P1,WZ2_P1,WZ3_P1,ttW_P1,ttZ_P1,tZq_P1,ZZ4_P1,WZ4_P1,
			   tptzm0800lh_P1,tptzm1200lh_P1,tptzm1600lh_P1,tptzm1700lh_P1);

	MakeHistos(CUTpup2,plot,bin[i],Min[i],Max[i],0,data_P2,background_P2,ZToNuNu_1_P2,ZToNuNu_2_P2,ZToNuNu_3_P2,ZToNuNu_4_P2,ZToNuNu_5_P2,ZToNuNu_6_P2,ZToNuNu_7_P2,
		       QCD_1_P2,QCD_2_P2,QCD_3_P2,QCD_4_P2,QCD_5_P2,QCD_6_P2,QCD_7_P2,WToLNu_1_P2,WToLNu_2_P2,WToLNu_3_P2,WToLNu_4_P2,WToLNu_5_P2,WToLNu_6_P2,WToLNu_7_P2,
			   TT_1_P2,TT_2_P2,ST_1_P2,ST_2_P2,ST_3_P2,ST_4_P2,ZZ1_P2,ZZ2_P2,ZZ3_P2,WW1_P2,WW2_P2,WZ1_P2,WZ2_P2,WZ3_P2,ttW_P2,ttZ_P2,tZq_P2,ZZ4_P2,WZ4_P2,
			   tptzm0800lh_P2,tptzm1200lh_P2,tptzm1600lh_P2,tptzm1700lh_P2);

	MakeHistos(CUTbta1,plot,bin[i],Min[i],Max[i],0,data_B1,background_B1,ZToNuNu_1_B1,ZToNuNu_2_B1,ZToNuNu_3_B1,ZToNuNu_4_B1,ZToNuNu_5_B1,ZToNuNu_6_B1,ZToNuNu_7_B1,
		       QCD_1_B1,QCD_2_B1,QCD_3_B1,QCD_4_B1,QCD_5_B1,QCD_6_B1,QCD_7_B1,WToLNu_1_B1,WToLNu_2_B1,WToLNu_3_B1,WToLNu_4_B1,WToLNu_5_B1,WToLNu_6_B1,WToLNu_7_B1,
			   TT_1_B1,TT_2_B1,ST_1_B1,ST_2_B1,ST_3_B1,ST_4_B1,ZZ1_B1,ZZ2_B1,ZZ3_B1,WW1_B1,WW2_B1,WZ1_B1,WZ2_B1,WZ3_B1,ttW_B1,ttZ_B1,tZq_B1,ZZ4_B1,WZ4_B1,
			   tptzm0800lh_B1,tptzm1200lh_B1,tptzm1600lh_B1,tptzm1700lh_B1);

	MakeHistos(CUTbta2,plot,bin[i],Min[i],Max[i],0,data_B2,background_B2,ZToNuNu_1_B2,ZToNuNu_2_B2,ZToNuNu_3_B2,ZToNuNu_4_B2,ZToNuNu_5_B2,ZToNuNu_6_B2,ZToNuNu_7_B2,
		       QCD_1_B2,QCD_2_B2,QCD_3_B2,QCD_4_B2,QCD_5_B2,QCD_6_B2,QCD_7_B2,WToLNu_1_B2,WToLNu_2_B2,WToLNu_3_B2,WToLNu_4_B2,WToLNu_5_B2,WToLNu_6_B2,WToLNu_7_B2,
			   TT_1_B2,TT_2_B2,ST_1_B2,ST_2_B2,ST_3_B2,ST_4_B2,ZZ1_B2,ZZ2_B2,ZZ3_B2,WW1_B2,WW2_B2,WZ1_B2,WZ2_B2,WZ3_B2,ttW_B2,ttZ_B2,tZq_B2,ZZ4_B2,WZ4_B2,
			   tptzm0800lh_B2,tptzm1200lh_B2,tptzm1600lh_B2,tptzm1700lh_B2);

	MakeHistos(CUTzje1,plot,bin[i],Min[i],Max[i],0,data_Z1,background_Z1,ZToNuNu_1_Z1,ZToNuNu_2_Z1,ZToNuNu_3_Z1,ZToNuNu_4_Z1,ZToNuNu_5_Z1,ZToNuNu_6_Z1,ZToNuNu_7_Z1,
		       QCD_1_Z1,QCD_2_Z1,QCD_3_Z1,QCD_4_Z1,QCD_5_Z1,QCD_6_Z1,QCD_7_Z1,WToLNu_1_Z1,WToLNu_2_Z1,WToLNu_3_Z1,WToLNu_4_Z1,WToLNu_5_Z1,WToLNu_6_Z1,WToLNu_7_Z1,
			   TT_1_Z1,TT_2_Z1,ST_1_Z1,ST_2_Z1,ST_3_Z1,ST_4_Z1,ZZ1_Z1,ZZ2_Z1,ZZ3_Z1,WW1_Z1,WW2_Z1,WZ1_Z1,WZ2_Z1,WZ3_Z1,ttW_Z1,ttZ_Z1,tZq_Z1,ZZ4_Z1,WZ4_Z1,
			   tptzm0800lh_Z1,tptzm1200lh_Z1,tptzm1600lh_Z1,tptzm1700lh_Z1);

	MakeHistos(CUTzje2,plot,bin[i],Min[i],Max[i],0,data_Z2,background_Z2,ZToNuNu_1_Z2,ZToNuNu_2_Z2,ZToNuNu_3_Z2,ZToNuNu_4_Z2,ZToNuNu_5_Z2,ZToNuNu_6_Z2,ZToNuNu_7_Z2,
		       QCD_1_Z2,QCD_2_Z2,QCD_3_Z2,QCD_4_Z2,QCD_5_Z2,QCD_6_Z2,QCD_7_Z2,WToLNu_1_Z2,WToLNu_2_Z2,WToLNu_3_Z2,WToLNu_4_Z2,WToLNu_5_Z2,WToLNu_6_Z2,WToLNu_7_Z2,
			   TT_1_Z2,TT_2_Z2,ST_1_Z2,ST_2_Z2,ST_3_Z2,ST_4_Z2,ZZ1_Z2,ZZ2_Z2,ZZ3_Z2,WW1_Z2,WW2_Z2,WZ1_Z2,WZ2_Z2,WZ3_Z2,ttW_Z2,ttZ_Z2,tZq_Z2,ZZ4_Z2,WZ4_Z2,
			   tptzm0800lh_Z2,tptzm1200lh_Z2,tptzm1600lh_Z2,tptzm1700lh_Z2);
	
	MakeHistos(CUTwje1,plot,bin[i],Min[i],Max[i],0,data_W1,background_W1,ZToNuNu_1_W1,ZToNuNu_2_W1,ZToNuNu_3_W1,ZToNuNu_4_W1,ZToNuNu_5_W1,ZToNuNu_6_W1,ZToNuNu_7_W1,
		       QCD_1_W1,QCD_2_W1,QCD_3_W1,QCD_4_W1,QCD_5_W1,QCD_6_W1,QCD_7_W1,WToLNu_1_W1,WToLNu_2_W1,WToLNu_3_W1,WToLNu_4_W1,WToLNu_5_W1,WToLNu_6_W1,WToLNu_7_W1,
			   TT_1_W1,TT_2_W1,ST_1_W1,ST_2_W1,ST_3_W1,ST_4_W1,ZZ1_W1,ZZ2_W1,ZZ3_W1,WW1_W1,WW2_W1,WZ1_W1,WZ2_W1,WZ3_W1,ttW_W1,ttZ_W1,tZq_W1,ZZ4_W1,WZ4_W1,
			   tptzm0800lh_W1,tptzm1200lh_W1,tptzm1600lh_W1,tptzm1700lh_W1);

	MakeHistos(CUTwje2,plot,bin[i],Min[i],Max[i],0,data_W2,background_W2,ZToNuNu_1_W2,ZToNuNu_2_W2,ZToNuNu_3_W2,ZToNuNu_4_W2,ZToNuNu_5_W2,ZToNuNu_6_W2,ZToNuNu_7_W2,
		       QCD_1_W2,QCD_2_W2,QCD_3_W2,QCD_4_W2,QCD_5_W2,QCD_6_W2,QCD_7_W2,WToLNu_1_W2,WToLNu_2_W2,WToLNu_3_W2,WToLNu_4_W2,WToLNu_5_W2,WToLNu_6_W2,WToLNu_7_W2,
			   TT_1_W2,TT_2_W2,ST_1_W2,ST_2_W2,ST_3_W2,ST_4_W2,ZZ1_W2,ZZ2_W2,ZZ3_W2,WW1_W2,WW2_W2,WZ1_W2,WZ2_W2,WZ3_W2,ttW_W2,ttZ_W2,tZq_W2,ZZ4_W2,WZ4_W2,
			   tptzm0800lh_W2,tptzm1200lh_W2,tptzm1600lh_W2,tptzm1700lh_W2);

	MakeHistos(CUTttb1,plot,bin[i],Min[i],Max[i],0,data_T1,background_T1,ZToNuNu_1_T1,ZToNuNu_2_T1,ZToNuNu_3_T1,ZToNuNu_4_T1,ZToNuNu_5_T1,ZToNuNu_6_T1,ZToNuNu_7_T1,
		       QCD_1_T1,QCD_2_T1,QCD_3_T1,QCD_4_T1,QCD_5_T1,QCD_6_T1,QCD_7_T1,WToLNu_1_T1,WToLNu_2_T1,WToLNu_3_T1,WToLNu_4_T1,WToLNu_5_T1,WToLNu_6_T1,WToLNu_7_T1,
			   TT_1_T1,TT_2_T1,ST_1_T1,ST_2_T1,ST_3_T1,ST_4_T1,ZZ1_T1,ZZ2_T1,ZZ3_T1,WW1_T1,WW2_T1,WZ1_T1,WZ2_T1,WZ3_T1,ttW_T1,ttZ_T1,tZq_T1,ZZ4_T1,WZ4_T1,
			   tptzm0800lh_T1,tptzm1200lh_T1,tptzm1600lh_T1,tptzm1700lh_T1);

	MakeHistos(CUTttb2,plot,bin[i],Min[i],Max[i],0,data_T2,background_T2,ZToNuNu_1_T2,ZToNuNu_2_T2,ZToNuNu_3_T2,ZToNuNu_4_T2,ZToNuNu_5_T2,ZToNuNu_6_T2,ZToNuNu_7_T2,
		       QCD_1_T2,QCD_2_T2,QCD_3_T2,QCD_4_T2,QCD_5_T2,QCD_6_T2,QCD_7_T2,WToLNu_1_T2,WToLNu_2_T2,WToLNu_3_T2,WToLNu_4_T2,WToLNu_5_T2,WToLNu_6_T2,WToLNu_7_T2,
			   TT_1_T2,TT_2_T2,ST_1_T2,ST_2_T2,ST_3_T2,ST_4_T2,ZZ1_T2,ZZ2_T2,ZZ3_T2,WW1_T2,WW2_T2,WZ1_T2,WZ2_T2,WZ3_T2,ttW_T2,ttZ_T2,tZq_T2,ZZ4_T2,WZ4_T2,
			   tptzm0800lh_T2,tptzm1200lh_T2,tptzm1600lh_T2,tptzm1700lh_T2);
	
	MakeHistos(CUTfir1,plot,bin[i],Min[i],Max[i],0,data_F1,background_F1,ZToNuNu_1_F1,ZToNuNu_2_F1,ZToNuNu_3_F1,ZToNuNu_4_F1,ZToNuNu_5_F1,ZToNuNu_6_F1,ZToNuNu_7_F1,
		       QCD_1_F1,QCD_2_F1,QCD_3_F1,QCD_4_F1,QCD_5_F1,QCD_6_F1,QCD_7_F1,WToLNu_1_F1,WToLNu_2_F1,WToLNu_3_F1,WToLNu_4_F1,WToLNu_5_F1,WToLNu_6_F1,WToLNu_7_F1,
			   TT_1_F1,TT_2_F1,ST_1_F1,ST_2_F1,ST_3_F1,ST_4_F1,ZZ1_F1,ZZ2_F1,ZZ3_F1,WW1_F1,WW2_F1,WZ1_F1,WZ2_F1,WZ3_F1,ttW_F1,ttZ_F1,tZq_F1,ZZ4_F1,WZ4_F1,
			   tptzm0800lh_F1,tptzm1200lh_F1,tptzm1600lh_F1,tptzm1700lh_F1);

	MakeHistos(CUTfir2,plot,bin[i],Min[i],Max[i],0,data_F2,background_F2,ZToNuNu_1_F2,ZToNuNu_2_F2,ZToNuNu_3_F2,ZToNuNu_4_F2,ZToNuNu_5_F2,ZToNuNu_6_F2,ZToNuNu_7_F2,
		       QCD_1_F2,QCD_2_F2,QCD_3_F2,QCD_4_F2,QCD_5_F2,QCD_6_F2,QCD_7_F2,WToLNu_1_F2,WToLNu_2_F2,WToLNu_3_F2,WToLNu_4_F2,WToLNu_5_F2,WToLNu_6_F2,WToLNu_7_F2,
			   TT_1_F2,TT_2_F2,ST_1_F2,ST_2_F2,ST_3_F2,ST_4_F2,ZZ1_F2,ZZ2_F2,ZZ3_F2,WW1_F2,WW2_F2,WZ1_F2,WZ2_F2,WZ3_F2,ttW_F2,ttZ_F2,tZq_F2,ZZ4_F2,WZ4_F2,
			   tptzm0800lh_F2,tptzm1200lh_F2,tptzm1600lh_F2,tptzm1700lh_F2);

        MakeHistos(CUTtri1,plot,bin[i],Min[i],Max[i],0,data_TR1,background_TR1,ZToNuNu_1_TR1,ZToNuNu_2_TR1,ZToNuNu_3_TR1,ZToNuNu_4_TR1,ZToNuNu_5_TR1,ZToNuNu_6_TR1,ZToNuNu_7_TR1,
                       QCD_1_TR1,QCD_2_TR1,QCD_3_TR1,QCD_4_TR1,QCD_5_TR1,QCD_6_TR1,QCD_7_TR1,WToLNu_1_TR1,WToLNu_2_TR1,WToLNu_3_TR1,WToLNu_4_TR1,WToLNu_5_TR1,WToLNu_6_TR1,WToLNu_7_TR1,
                           TT_1_TR1,TT_2_TR1,ST_1_TR1,ST_2_TR1,ST_3_TR1,ST_4_TR1,ZZ1_TR1,ZZ2_TR1,ZZ3_TR1,WW1_TR1,WW2_TR1,WZ1_TR1,WZ2_TR1,WZ3_TR1,ttW_TR1,ttZ_TR1,tZq_TR1,ZZ4_TR1,WZ4_TR1,
                           tptzm0800lh_TR1,tptzm1200lh_TR1,tptzm1600lh_TR1,tptzm1700lh_TR1);

        MakeHistos(CUTtri2,plot,bin[i],Min[i],Max[i],0,data_TR2,background_TR2,ZToNuNu_1_TR2,ZToNuNu_2_TR2,ZToNuNu_3_TR2,ZToNuNu_4_TR2,ZToNuNu_5_TR2,ZToNuNu_6_TR2,ZToNuNu_7_TR2,
                       QCD_1_TR2,QCD_2_TR2,QCD_3_TR2,QCD_4_TR2,QCD_5_TR2,QCD_6_TR2,QCD_7_TR2,WToLNu_1_TR2,WToLNu_2_TR2,WToLNu_3_TR2,WToLNu_4_TR2,WToLNu_5_TR2,WToLNu_6_TR2,WToLNu_7_TR2,
                           TT_1_TR2,TT_2_TR2,ST_1_TR2,ST_2_TR2,ST_3_TR2,ST_4_TR2,ZZ1_TR2,ZZ2_TR2,ZZ3_TR2,WW1_TR2,WW2_TR2,WZ1_TR2,WZ2_TR2,WZ3_TR2,ttW_TR2,ttZ_TR2,tZq_TR2,ZZ4_TR2,WZ4_TR2,
                           tptzm0800lh_TR2,tptzm1200lh_TR2,tptzm1600lh_TR2,tptzm1700lh_TR2);

	MakeHistos(CUT,plot,bin[i],Min[i],Max[i],1,data_J1,background_J1,ZToNuNu_1_J1,ZToNuNu_2_J1,ZToNuNu_3_J1,ZToNuNu_4_J1,ZToNuNu_5_J1,ZToNuNu_6_J1,ZToNuNu_7_J1,
		       QCD_1_J1,QCD_2_J1,QCD_3_J1,QCD_4_J1,QCD_5_J1,QCD_6_J1,QCD_7_J1,WToLNu_1_J1,WToLNu_2_J1,WToLNu_3_J1,WToLNu_4_J1,WToLNu_5_J1,WToLNu_6_J1,WToLNu_7_J1,
			   TT_1_J1,TT_2_J1,ST_1_J1,ST_2_J1,ST_3_J1,ST_4_J1,ZZ1_J1,ZZ2_J1,ZZ3_J1,WW1_J1,WW2_J1,WZ1_J1,WZ2_J1,WZ3_J1,ttW_J1,ttZ_J1,tZq_J1,ZZ4_J1,WZ4_J1,
			   tptzm0800lh_J1,tptzm1200lh_J1,tptzm1600lh_J1,tptzm1700lh_J1);

	MakeHistos(CUT,plot,bin[i],Min[i],Max[i],2,data_J2,background_J2,ZToNuNu_1_J2,ZToNuNu_2_J2,ZToNuNu_3_J2,ZToNuNu_4_J2,ZToNuNu_5_J2,ZToNuNu_6_J2,ZToNuNu_7_J2,
		       QCD_1_J2,QCD_2_J2,QCD_3_J2,QCD_4_J2,QCD_5_J2,QCD_6_J2,QCD_7_J2,WToLNu_1_J2,WToLNu_2_J2,WToLNu_3_J2,WToLNu_4_J2,WToLNu_5_J2,WToLNu_6_J2,WToLNu_7_J2,
			   TT_1_J2,TT_2_J2,ST_1_J2,ST_2_J2,ST_3_J2,ST_4_J2,ZZ1_J2,ZZ2_J2,ZZ3_J2,WW1_J2,WW2_J2,WZ1_J2,WZ2_J2,WZ3_J2,ttW_J2,ttZ_J2,tZq_J2,ZZ4_J2,WZ4_J2,
			   tptzm0800lh_J2,tptzm1200lh_J2,tptzm1600lh_J2,tptzm1700lh_J2);

	MakeHistos(CUT,plot,bin[i],Min[i],Max[i],3,data_J3,background_J3,ZToNuNu_1_J3,ZToNuNu_2_J3,ZToNuNu_3_J3,ZToNuNu_4_J3,ZToNuNu_5_J3,ZToNuNu_6_J3,ZToNuNu_7_J3,
		       QCD_1_J3,QCD_2_J3,QCD_3_J3,QCD_4_J3,QCD_5_J3,QCD_6_J3,QCD_7_J3,WToLNu_1_J3,WToLNu_2_J3,WToLNu_3_J3,WToLNu_4_J3,WToLNu_5_J3,WToLNu_6_J3,WToLNu_7_J3,
			   TT_1_J3,TT_2_J3,ST_1_J3,ST_2_J3,ST_3_J3,ST_4_J3,ZZ1_J3,ZZ2_J3,ZZ3_J3,WW1_J3,WW2_J3,WZ1_J3,WZ2_J3,WZ3_J3,ttW_J3,ttZ_J3,tZq_J3,ZZ4_J3,WZ4_J3,
			   tptzm0800lh_J3,tptzm1200lh_J3,tptzm1600lh_J3,tptzm1700lh_J3);

	MakeHistos(CUT,plot,bin[i],Min[i],Max[i],4,data_J4,background_J4,ZToNuNu_1_J4,ZToNuNu_2_J4,ZToNuNu_3_J4,ZToNuNu_4_J4,ZToNuNu_5_J4,ZToNuNu_6_J4,ZToNuNu_7_J4,
		       QCD_1_J4,QCD_2_J4,QCD_3_J4,QCD_4_J4,QCD_5_J4,QCD_6_J4,QCD_7_J4,WToLNu_1_J4,WToLNu_2_J4,WToLNu_3_J4,WToLNu_4_J4,WToLNu_5_J4,WToLNu_6_J4,WToLNu_7_J4,
			   TT_1_J4,TT_2_J4,ST_1_J4,ST_2_J4,ST_3_J4,ST_4_J4,ZZ1_J4,ZZ2_J4,ZZ3_J4,WW1_J4,WW2_J4,WZ1_J4,WZ2_J4,WZ3_J4,ttW_J4,ttZ_J4,tZq_J4,ZZ4_J4,WZ4_J4,
			   tptzm0800lh_J4,tptzm1200lh_J4,tptzm1600lh_J4,tptzm1700lh_J4);

	MakeHistos(CUTqcd1,plot,bin[i],Min[i],Max[i],0,data_qcd1,background_qcd1,ZToNuNu_1_qcd1,ZToNuNu_2_qcd1,ZToNuNu_3_qcd1,ZToNuNu_4_qcd1,ZToNuNu_5_qcd1,ZToNuNu_6_qcd1,ZToNuNu_7_qcd1,
                       QCD_1_qcd1,QCD_2_qcd1,QCD_3_qcd1,QCD_4_qcd1,QCD_5_qcd1,QCD_6_qcd1,QCD_7_qcd1,WToLNu_1_qcd1,WToLNu_2_qcd1,WToLNu_3_qcd1,WToLNu_4_qcd1,WToLNu_5_qcd1,WToLNu_6_qcd1,WToLNu_7_qcd1,
                           TT_1_qcd1,TT_2_qcd1,ST_1_qcd1,ST_2_qcd1,ST_3_qcd1,ST_4_qcd1,ZZ1_qcd1,ZZ2_qcd1,ZZ3_qcd1,WW1_qcd1,WW2_qcd1,WZ1_qcd1,WZ2_qcd1,WZ3_qcd1,ttW_qcd1,ttZ_qcd1,tZq_qcd1,ZZ4_qcd1,WZ4_qcd1,
                           tptzm0800lh_qcd1,tptzm1200lh_qcd1,tptzm1600lh_qcd1,tptzm1700lh_qcd1);

        MakeHistos(CUTqcd2,plot,bin[i],Min[i],Max[i],0,data_qcd2,background_qcd2,ZToNuNu_1_qcd2,ZToNuNu_2_qcd2,ZToNuNu_3_qcd2,ZToNuNu_4_qcd2,ZToNuNu_5_qcd2,ZToNuNu_6_qcd2,ZToNuNu_7_qcd2,
                       QCD_1_qcd2,QCD_2_qcd2,QCD_3_qcd2,QCD_4_qcd2,QCD_5_qcd2,QCD_6_qcd2,QCD_7_qcd2,WToLNu_1_qcd2,WToLNu_2_qcd2,WToLNu_3_qcd2,WToLNu_4_qcd2,WToLNu_5_qcd2,WToLNu_6_qcd2,WToLNu_7_qcd2,
                           TT_1_qcd2,TT_2_qcd2,ST_1_qcd2,ST_2_qcd2,ST_3_qcd2,ST_4_qcd2,ZZ1_qcd2,ZZ2_qcd2,ZZ3_qcd2,WW1_qcd2,WW2_qcd2,WZ1_qcd2,WZ2_qcd2,WZ3_qcd2,ttW_qcd2,ttZ_qcd2,tZq_qcd2,ZZ4_qcd2,WZ4_qcd2,
                           tptzm0800lh_qcd2,tptzm1200lh_qcd2,tptzm1600lh_qcd2,tptzm1700lh_qcd2);

        MakeHistos(CUTpdf1,plot,bin[i],Min[i],Max[i],0,data_pdf1,background_pdf1,ZToNuNu_1_pdf1,ZToNuNu_2_pdf1,ZToNuNu_3_pdf1,ZToNuNu_4_pdf1,ZToNuNu_5_pdf1,ZToNuNu_6_pdf1,ZToNuNu_7_pdf1,
                       QCD_1_pdf1,QCD_2_pdf1,QCD_3_pdf1,QCD_4_pdf1,QCD_5_pdf1,QCD_6_pdf1,QCD_7_pdf1,WToLNu_1_pdf1,WToLNu_2_pdf1,WToLNu_3_pdf1,WToLNu_4_pdf1,WToLNu_5_pdf1,WToLNu_6_pdf1,WToLNu_7_pdf1,
                           TT_1_pdf1,TT_2_pdf1,ST_1_pdf1,ST_2_pdf1,ST_3_pdf1,ST_4_pdf1,ZZ1_pdf1,ZZ2_pdf1,ZZ3_pdf1,WW1_pdf1,WW2_pdf1,WZ1_pdf1,WZ2_pdf1,WZ3_pdf1,ttW_pdf1,ttZ_pdf1,tZq_pdf1,ZZ4_pdf1,WZ4_pdf1,
                           tptzm0800lh_pdf1,tptzm1200lh_pdf1,tptzm1600lh_pdf1,tptzm1700lh_pdf1);

        MakeHistos(CUTpdf2,plot,bin[i],Min[i],Max[i],0,data_pdf2,background_pdf2,ZToNuNu_1_pdf2,ZToNuNu_2_pdf2,ZToNuNu_3_pdf2,ZToNuNu_4_pdf2,ZToNuNu_5_pdf2,ZToNuNu_6_pdf2,ZToNuNu_7_pdf2,
                       QCD_1_pdf2,QCD_2_pdf2,QCD_3_pdf2,QCD_4_pdf2,QCD_5_pdf2,QCD_6_pdf2,QCD_7_pdf2,WToLNu_1_pdf2,WToLNu_2_pdf2,WToLNu_3_pdf2,WToLNu_4_pdf2,WToLNu_5_pdf2,WToLNu_6_pdf2,WToLNu_7_pdf2,
                           TT_1_pdf2,TT_2_pdf2,ST_1_pdf2,ST_2_pdf2,ST_3_pdf2,ST_4_pdf2,ZZ1_pdf2,ZZ2_pdf2,ZZ3_pdf2,WW1_pdf2,WW2_pdf2,WZ1_pdf2,WZ2_pdf2,WZ3_pdf2,ttW_pdf2,ttZ_pdf2,tZq_pdf2,ZZ4_pdf2,WZ4_pdf2,
                           tptzm0800lh_pdf2,tptzm1200lh_pdf2,tptzm1600lh_pdf2,tptzm1700lh_pdf2);
	}else {
      CloneHistos();
    }
	
	for(int m=1; m<background_SR->GetNbinsX()+1; m++){ 
        MakeHistoErrors(m, ZToNuNu_1_SR, ZToNuNu_1_P1, ZToNuNu_1_P2, ZToNuNu_1_F1, ZToNuNu_1_F2, ZToNuNu_1_B1, ZToNuNu_1_B2, ZToNuNu_1_Z1, ZToNuNu_1_Z2, ZToNuNu_1_W1, ZToNuNu_1_W2, ZToNuNu_1_T1, ZToNuNu_1_T2, ZToNuNu_1_J1, ZToNuNu_1_J2, ZToNuNu_1_J3, ZToNuNu_1_J4, ZToNuNu_1_qcd1, ZToNuNu_1_qcd2, ZToNuNu_1_pdf1, ZToNuNu_1_pdf2, ZToNuNu_1_TR1, ZToNuNu_1_TR2);
	MakeHistoErrors(m, ZToNuNu_2_SR, ZToNuNu_2_P1, ZToNuNu_2_P2, ZToNuNu_2_F1, ZToNuNu_2_F2, ZToNuNu_2_B1, ZToNuNu_2_B2, ZToNuNu_2_Z1, ZToNuNu_2_Z2, ZToNuNu_2_W1, ZToNuNu_2_W2, ZToNuNu_2_T1, ZToNuNu_2_T2, ZToNuNu_2_J1, ZToNuNu_2_J2, ZToNuNu_2_J3, ZToNuNu_2_J4, ZToNuNu_2_qcd1, ZToNuNu_2_qcd2, ZToNuNu_2_pdf1, ZToNuNu_2_pdf2, ZToNuNu_2_TR1, ZToNuNu_2_TR2);
	MakeHistoErrors(m, ZToNuNu_3_SR, ZToNuNu_3_P1, ZToNuNu_3_P2, ZToNuNu_3_F1, ZToNuNu_3_F2, ZToNuNu_3_B1, ZToNuNu_3_B2, ZToNuNu_3_Z1, ZToNuNu_3_Z2, ZToNuNu_3_W1, ZToNuNu_3_W2, ZToNuNu_3_T1, ZToNuNu_3_T2, ZToNuNu_3_J1, ZToNuNu_3_J2, ZToNuNu_3_J3, ZToNuNu_3_J4, ZToNuNu_3_qcd1, ZToNuNu_3_qcd2, ZToNuNu_3_pdf1, ZToNuNu_3_pdf2, ZToNuNu_3_TR1, ZToNuNu_3_TR2);
	MakeHistoErrors(m, ZToNuNu_4_SR, ZToNuNu_4_P1, ZToNuNu_4_P2, ZToNuNu_4_F1, ZToNuNu_4_F2, ZToNuNu_4_B1, ZToNuNu_4_B2, ZToNuNu_4_Z1, ZToNuNu_4_Z2, ZToNuNu_4_W1, ZToNuNu_4_W2, ZToNuNu_4_T1, ZToNuNu_4_T2, ZToNuNu_4_J1, ZToNuNu_4_J2, ZToNuNu_4_J3, ZToNuNu_4_J4, ZToNuNu_4_qcd1, ZToNuNu_4_qcd2, ZToNuNu_4_pdf1, ZToNuNu_4_pdf2, ZToNuNu_4_TR1, ZToNuNu_4_TR2);
	MakeHistoErrors(m, ZToNuNu_5_SR, ZToNuNu_5_P1, ZToNuNu_5_P2, ZToNuNu_5_F1, ZToNuNu_5_F2, ZToNuNu_5_B1, ZToNuNu_5_B2, ZToNuNu_5_Z1, ZToNuNu_5_Z2, ZToNuNu_5_W1, ZToNuNu_5_W2, ZToNuNu_5_T1, ZToNuNu_5_T2, ZToNuNu_5_J1, ZToNuNu_5_J2, ZToNuNu_5_J3, ZToNuNu_5_J4, ZToNuNu_5_qcd1, ZToNuNu_5_qcd2, ZToNuNu_5_pdf1, ZToNuNu_5_pdf2, ZToNuNu_5_TR1, ZToNuNu_5_TR2);
	MakeHistoErrors(m, ZToNuNu_6_SR, ZToNuNu_6_P1, ZToNuNu_6_P2, ZToNuNu_6_F1, ZToNuNu_6_F2, ZToNuNu_6_B1, ZToNuNu_6_B2, ZToNuNu_6_Z1, ZToNuNu_6_Z2, ZToNuNu_6_W1, ZToNuNu_6_W2, ZToNuNu_6_T1, ZToNuNu_6_T2, ZToNuNu_6_J1, ZToNuNu_6_J2, ZToNuNu_6_J3, ZToNuNu_6_J4, ZToNuNu_6_qcd1, ZToNuNu_6_qcd2, ZToNuNu_6_pdf1, ZToNuNu_6_pdf2, ZToNuNu_6_TR1, ZToNuNu_6_TR2);
	MakeHistoErrors(m, ZToNuNu_7_SR, ZToNuNu_7_P1, ZToNuNu_7_P2, ZToNuNu_7_F1, ZToNuNu_7_F2, ZToNuNu_7_B1, ZToNuNu_7_B2, ZToNuNu_7_Z1, ZToNuNu_7_Z2, ZToNuNu_7_W1, ZToNuNu_7_W2, ZToNuNu_7_T1, ZToNuNu_7_T2, ZToNuNu_7_J1, ZToNuNu_7_J2, ZToNuNu_7_J3, ZToNuNu_7_J4, ZToNuNu_7_qcd1, ZToNuNu_7_qcd2, ZToNuNu_7_pdf1, ZToNuNu_7_pdf2, ZToNuNu_7_TR1, ZToNuNu_7_TR2);
   
	MakeHistoErrors(m, QCD_1_SR, QCD_1_P1, QCD_1_P2, QCD_1_F1, QCD_1_F2, QCD_1_B1, QCD_1_B2, QCD_1_Z1, QCD_1_Z2, QCD_1_W1, QCD_1_W2, QCD_1_T1, QCD_1_T2, QCD_1_J1, QCD_1_J2, QCD_1_J3, QCD_1_J4, QCD_1_qcd1, QCD_1_qcd2, QCD_1_pdf1, QCD_1_pdf2, QCD_1_TR1, QCD_1_TR2);
	MakeHistoErrors(m, QCD_2_SR, QCD_2_P1, QCD_2_P2, QCD_2_F1, QCD_2_F2, QCD_2_B1, QCD_2_B2, QCD_2_Z1, QCD_2_Z2, QCD_2_W1, QCD_2_W2, QCD_2_T1, QCD_2_T2, QCD_2_J1, QCD_2_J2, QCD_2_J3, QCD_2_J4, QCD_2_qcd1, QCD_2_qcd2, QCD_2_pdf1, QCD_2_pdf2, QCD_2_TR1, QCD_2_TR2);
	MakeHistoErrors(m, QCD_3_SR, QCD_3_P1, QCD_3_P2, QCD_3_F1, QCD_3_F2, QCD_3_B1, QCD_3_B2, QCD_3_Z1, QCD_3_Z2, QCD_3_W1, QCD_3_W2, QCD_3_T1, QCD_3_T2, QCD_3_J1, QCD_3_J2, QCD_3_J3, QCD_3_J4, QCD_3_qcd1, QCD_3_qcd2, QCD_3_pdf1, QCD_3_pdf2, QCD_3_TR1, QCD_3_TR2);
	MakeHistoErrors(m, QCD_4_SR, QCD_4_P1, QCD_4_P2, QCD_4_F1, QCD_4_F2, QCD_4_B1, QCD_4_B2, QCD_4_Z1, QCD_4_Z2, QCD_4_W1, QCD_4_W2, QCD_4_T1, QCD_4_T2, QCD_4_J1, QCD_4_J2, QCD_4_J3, QCD_4_J4, QCD_4_qcd1, QCD_4_qcd2, QCD_4_pdf1, QCD_4_pdf2, QCD_4_TR1, QCD_4_TR2);
	MakeHistoErrors(m, QCD_5_SR, QCD_5_P1, QCD_5_P2, QCD_5_F1, QCD_5_F2, QCD_5_B1, QCD_5_B2, QCD_5_Z1, QCD_5_Z2, QCD_5_W1, QCD_5_W2, QCD_5_T1, QCD_5_T2, QCD_5_J1, QCD_5_J2, QCD_5_J3, QCD_5_J4, QCD_5_qcd1, QCD_5_qcd2, QCD_5_pdf1, QCD_5_pdf2, QCD_5_TR1, QCD_5_TR2);
	MakeHistoErrors(m, QCD_6_SR, QCD_6_P1, QCD_6_P2, QCD_6_F1, QCD_6_F2, QCD_6_B1, QCD_6_B2, QCD_6_Z1, QCD_6_Z2, QCD_6_W1, QCD_6_W2, QCD_6_T1, QCD_6_T2, QCD_6_J1, QCD_6_J2, QCD_6_J3, QCD_6_J4, QCD_6_qcd1, QCD_6_qcd2, QCD_6_pdf1, QCD_6_pdf2, QCD_6_TR1, QCD_6_TR2);
	MakeHistoErrors(m, QCD_7_SR, QCD_7_P1, QCD_7_P2, QCD_7_F1, QCD_7_F2, QCD_7_B1, QCD_7_B2, QCD_7_Z1, QCD_7_Z2, QCD_7_W1, QCD_7_W2, QCD_7_T1, QCD_7_T2, QCD_7_J1, QCD_7_J2, QCD_7_J3, QCD_7_J4, QCD_7_qcd1, QCD_7_qcd2, QCD_7_pdf1, QCD_7_pdf2, QCD_7_TR1, QCD_7_TR2);
	
	MakeHistoErrors(m, WToLNu_1_SR, WToLNu_1_P1, WToLNu_1_P2, WToLNu_1_F1, WToLNu_1_F2, WToLNu_1_B1, WToLNu_1_B2, WToLNu_1_Z1, WToLNu_1_Z2, WToLNu_1_W1, WToLNu_1_W2, WToLNu_1_T1, WToLNu_1_T2, WToLNu_1_J1, WToLNu_1_J2, WToLNu_1_J3, WToLNu_1_J4, WToLNu_1_qcd1, WToLNu_1_qcd2, WToLNu_1_pdf1, WToLNu_1_pdf2, WToLNu_1_TR1, WToLNu_1_TR2);
	MakeHistoErrors(m, WToLNu_2_SR, WToLNu_2_P1, WToLNu_2_P2, WToLNu_2_F1, WToLNu_2_F2, WToLNu_2_B1, WToLNu_2_B2, WToLNu_2_Z1, WToLNu_2_Z2, WToLNu_2_W1, WToLNu_2_W2, WToLNu_2_T1, WToLNu_2_T2, WToLNu_2_J1, WToLNu_2_J2, WToLNu_2_J3, WToLNu_2_J4, WToLNu_2_qcd1, WToLNu_2_qcd2, WToLNu_2_pdf1, WToLNu_2_pdf2, WToLNu_2_TR1, WToLNu_2_TR2);
	MakeHistoErrors(m, WToLNu_3_SR, WToLNu_3_P1, WToLNu_3_P2, WToLNu_3_F1, WToLNu_3_F2, WToLNu_3_B1, WToLNu_3_B2, WToLNu_3_Z1, WToLNu_3_Z2, WToLNu_3_W1, WToLNu_3_W2, WToLNu_3_T1, WToLNu_3_T2, WToLNu_3_J1, WToLNu_3_J2, WToLNu_3_J3, WToLNu_3_J4, WToLNu_3_qcd1, WToLNu_3_qcd2, WToLNu_3_pdf1, WToLNu_3_pdf2, WToLNu_3_TR1, WToLNu_3_TR2);
	MakeHistoErrors(m, WToLNu_4_SR, WToLNu_4_P1, WToLNu_4_P2, WToLNu_4_F1, WToLNu_4_F2, WToLNu_4_B1, WToLNu_4_B2, WToLNu_4_Z1, WToLNu_4_Z2, WToLNu_4_W1, WToLNu_4_W2, WToLNu_4_T1, WToLNu_4_T2, WToLNu_4_J1, WToLNu_4_J2, WToLNu_4_J3, WToLNu_4_J4, WToLNu_4_qcd1, WToLNu_4_qcd2, WToLNu_4_pdf1, WToLNu_4_pdf2, WToLNu_4_TR1, WToLNu_4_TR2);
	MakeHistoErrors(m, WToLNu_5_SR, WToLNu_5_P1, WToLNu_5_P2, WToLNu_5_F1, WToLNu_5_F2, WToLNu_5_B1, WToLNu_5_B2, WToLNu_5_Z1, WToLNu_5_Z2, WToLNu_5_W1, WToLNu_5_W2, WToLNu_5_T1, WToLNu_5_T2, WToLNu_5_J1, WToLNu_5_J2, WToLNu_5_J3, WToLNu_5_J4, WToLNu_5_qcd1, WToLNu_5_qcd2, WToLNu_5_pdf1, WToLNu_5_pdf2, WToLNu_5_TR1, WToLNu_5_TR2);
	MakeHistoErrors(m, WToLNu_6_SR, WToLNu_6_P1, WToLNu_6_P2, WToLNu_6_F1, WToLNu_6_F2, WToLNu_6_B1, WToLNu_6_B2, WToLNu_6_Z1, WToLNu_6_Z2, WToLNu_6_W1, WToLNu_6_W2, WToLNu_6_T1, WToLNu_6_T2, WToLNu_6_J1, WToLNu_6_J2, WToLNu_6_J3, WToLNu_6_J4, WToLNu_6_qcd1, WToLNu_6_qcd2, WToLNu_6_pdf1, WToLNu_6_pdf2, WToLNu_6_TR1, WToLNu_6_TR2);
	MakeHistoErrors(m, WToLNu_7_SR, WToLNu_7_P1, WToLNu_7_P2, WToLNu_7_F1, WToLNu_7_F2, WToLNu_7_B1, WToLNu_7_B2, WToLNu_7_Z1, WToLNu_7_Z2, WToLNu_7_W1, WToLNu_7_W2, WToLNu_7_T1, WToLNu_7_T2, WToLNu_7_J1, WToLNu_7_J2, WToLNu_7_J3, WToLNu_7_J4, WToLNu_7_qcd1, WToLNu_7_qcd2, WToLNu_7_pdf1, WToLNu_7_pdf2, WToLNu_7_TR1, WToLNu_7_TR2);
	
	MakeHistoErrors(m, TT_1_SR, TT_1_P1, TT_1_P2, TT_1_F1, TT_1_F2, TT_1_B1, TT_1_B2, TT_1_Z1, TT_1_Z2, TT_1_W1, TT_1_W2, TT_1_T1, TT_1_T2, TT_1_J1, TT_1_J2, TT_1_J3, TT_1_J4, TT_1_qcd1, TT_1_qcd2, TT_1_pdf1, TT_1_pdf2, TT_1_TR1, TT_1_TR2);
	MakeHistoErrors(m, TT_2_SR, TT_2_P1, TT_2_P2, TT_2_F1, TT_2_F2, TT_2_B1, TT_2_B2, TT_2_Z1, TT_2_Z2, TT_2_W1, TT_2_W2, TT_2_T1, TT_2_T2, TT_2_J1, TT_2_J2, TT_2_J3, TT_2_J4, TT_2_qcd1, TT_2_qcd2, TT_2_pdf1, TT_2_pdf2, TT_2_TR1, TT_2_TR2);
	
	MakeHistoErrors(m, ST_1_SR, ST_1_P1, ST_1_P2, ST_1_F1, ST_1_F2, ST_1_B1, ST_1_B2, ST_1_Z1, ST_1_Z2, ST_1_W1, ST_1_W2, ST_1_T1, ST_1_T2, ST_1_J1, ST_1_J2, ST_1_J3, ST_1_J4, ST_1_qcd1, ST_1_qcd2, ST_1_pdf1, ST_1_pdf2, ST_1_TR1, ST_1_TR2);
	MakeHistoErrors(m, ST_2_SR, ST_2_P1, ST_2_P2, ST_2_F1, ST_2_F2, ST_2_B1, ST_2_B2, ST_2_Z1, ST_2_Z2, ST_2_W1, ST_2_W2, ST_2_T1, ST_2_T2, ST_2_J1, ST_2_J2, ST_2_J3, ST_2_J4, ST_2_qcd1, ST_2_qcd2, ST_2_pdf1, ST_2_pdf2, ST_2_TR1, ST_2_TR2);
	MakeHistoErrors(m, ST_3_SR, ST_3_P1, ST_3_P2, ST_3_F1, ST_3_F2, ST_3_B1, ST_3_B2, ST_3_Z1, ST_3_Z2, ST_3_W1, ST_3_W2, ST_3_T1, ST_3_T2, ST_3_J1, ST_3_J2, ST_3_J3, ST_3_J4, ST_3_qcd1, ST_3_qcd2, ST_3_pdf1, ST_3_pdf2, ST_3_TR1, ST_3_TR2);
	MakeHistoErrors(m, ST_4_SR, ST_4_P1, ST_4_P2, ST_4_F1, ST_4_F2, ST_4_B1, ST_4_B2, ST_4_Z1, ST_4_Z2, ST_4_W1, ST_4_W2, ST_4_T1, ST_4_T2, ST_4_J1, ST_4_J2, ST_4_J3, ST_4_J4, ST_4_qcd1, ST_4_qcd2, ST_4_pdf1, ST_4_pdf2, ST_4_TR1, ST_4_TR2);
	
	MakeHistoErrors(m, ZZ1_SR, ZZ1_P1, ZZ1_P2, ZZ1_F1, ZZ1_F2, ZZ1_B1, ZZ1_B2, ZZ1_Z1, ZZ1_Z2, ZZ1_W1, ZZ1_W2, ZZ1_T1, ZZ1_T2, ZZ1_J1, ZZ1_J2, ZZ1_J3, ZZ1_J4, ZZ1_qcd1, ZZ1_qcd2, ZZ1_pdf1, ZZ1_pdf2, ZZ1_TR1, ZZ1_TR2);
	MakeHistoErrors(m, ZZ2_SR, ZZ2_P1, ZZ2_P2, ZZ2_F1, ZZ2_F2, ZZ2_B1, ZZ2_B2, ZZ2_Z1, ZZ2_Z2, ZZ2_W1, ZZ2_W2, ZZ2_T1, ZZ2_T2, ZZ2_J1, ZZ2_J2, ZZ2_J3, ZZ2_J4, ZZ2_qcd1, ZZ2_qcd2, ZZ2_pdf1, ZZ2_pdf2, ZZ2_TR1, ZZ2_TR2);
	MakeHistoErrors(m, ZZ3_SR, ZZ3_P1, ZZ3_P2, ZZ3_F1, ZZ3_F2, ZZ3_B1, ZZ3_B2, ZZ3_Z1, ZZ3_Z2, ZZ3_W1, ZZ3_W2, ZZ3_T1, ZZ3_T2, ZZ3_J1, ZZ3_J2, ZZ3_J3, ZZ3_J4, ZZ3_qcd1, ZZ3_qcd2, ZZ3_pdf1, ZZ3_pdf2, ZZ3_TR1, ZZ3_TR2);
	
	MakeHistoErrors(m, WW1_SR, WW1_P1, WW1_P2, WW1_F1, WW1_F2, WW1_B1, WW1_B2, WW1_Z1, WW1_Z2, WW1_W1, WW1_W2, WW1_T1, WW1_T2, WW1_J1, WW1_J2, WW1_J3, WW1_J4, WW1_qcd1, WW1_qcd2, WW1_pdf1, WW1_pdf2, WW1_TR1, WW1_TR2);
	MakeHistoErrors(m, WW2_SR, WW2_P1, WW2_P2, WW2_F1, WW2_F2, WW2_B1, WW2_B2, WW2_Z1, WW2_Z2, WW2_W1, WW2_W2, WW2_T1, WW2_T2, WW2_J1, WW2_J2, WW2_J3, WW2_J4, WW2_qcd1, WW2_qcd2, WW2_pdf1, WW2_pdf2, WW2_TR1, WW2_TR2);
	
	MakeHistoErrors(m, WZ1_SR, WZ1_P1, WZ1_P2, WZ1_F1, WZ1_F2, WZ1_B1, WZ1_B2, WZ1_Z1, WZ1_Z2, WZ1_W1, WZ1_W2, WZ1_T1, WZ1_T2, WZ1_J1, WZ1_J2, WZ1_J3, WZ1_J4, WZ1_qcd1, WZ1_qcd2, WZ1_pdf1, WZ1_pdf2, WZ1_TR1, WZ1_TR2);
	MakeHistoErrors(m, WZ2_SR, WZ2_P1, WZ2_P2, WZ2_F1, WZ2_F2, WZ2_B1, WZ2_B2, WZ2_Z1, WZ2_Z2, WZ2_W1, WZ2_W2, WZ2_T1, WZ2_T2, WZ2_J1, WZ2_J2, WZ2_J3, WZ2_J4, WZ2_qcd1, WZ2_qcd2, WZ2_pdf1, WZ2_pdf2, WZ2_TR1, WZ2_TR2);
	MakeHistoErrors(m, WZ3_SR, WZ3_P1, WZ3_P2, WZ3_F1, WZ3_F2, WZ3_B1, WZ3_B2, WZ3_Z1, WZ3_Z2, WZ3_W1, WZ3_W2, WZ3_T1, WZ3_T2, WZ3_J1, WZ3_J2, WZ3_J3, WZ3_J4, WZ3_qcd1, WZ3_qcd2, WZ3_pdf1, WZ3_pdf2, WZ3_TR1, WZ3_TR2);
	MakeHistoErrors(m, ttW_SR, ttW_P1, ttW_P2, ttW_F1, ttW_F2, ttW_B1, ttW_B2, ttW_Z1, ttW_Z2, ttW_W1, ttW_W2, ttW_T1, ttW_T2, ttW_J1, ttW_J2, ttW_J3, ttW_J4, ttW_qcd1, ttW_qcd2, ttW_pdf1, ttW_pdf2, ttW_TR1, ttW_TR2);
	MakeHistoErrors(m, ttZ_SR, ttZ_P1, ttZ_P2, ttZ_F1, ttZ_F2, ttZ_B1, ttZ_B2, ttZ_Z1, ttZ_Z2, ttZ_W1, ttZ_W2, ttZ_T1, ttZ_T2, ttZ_J1, ttZ_J2, ttZ_J3, ttZ_J4, ttZ_qcd1, ttZ_qcd2, ttZ_pdf1, ttZ_pdf2, ttZ_TR1, ttZ_TR2);
	MakeHistoErrors(m, tZq_SR, tZq_P1, tZq_P2, tZq_F1, tZq_F2, tZq_B1, tZq_B2, tZq_Z1, tZq_Z2, tZq_W1, tZq_W2, tZq_T1, tZq_T2, tZq_J1, tZq_J2, tZq_J3, tZq_J4, tZq_qcd1, tZq_qcd2, tZq_pdf1, tZq_pdf2, tZq_TR1, tZq_TR2);
	MakeHistoErrors(m, ZZ4_SR, ZZ4_P1, ZZ4_P2, ZZ4_F1, ZZ4_F2, ZZ4_B1, ZZ4_B2, ZZ4_Z1, ZZ4_Z2, ZZ4_W1, ZZ4_W2, ZZ4_T1, ZZ4_T2, ZZ4_J1, ZZ4_J2, ZZ4_J3, ZZ4_J4, ZZ4_qcd1, ZZ4_qcd2, ZZ4_pdf1, ZZ4_pdf2, ZZ4_TR1, ZZ4_TR2);
	MakeHistoErrors(m, WZ4_SR, WZ4_P1, WZ4_P2, WZ4_F1, WZ4_F2, WZ4_B1, WZ4_B2, WZ4_Z1, WZ4_Z2, WZ4_W1, WZ4_W2, WZ4_T1, WZ4_T2, WZ4_J1, WZ4_J2, WZ4_J3, WZ4_J4, WZ4_qcd1, WZ4_qcd2, WZ4_pdf1, WZ4_pdf2, WZ4_TR1, WZ4_TR2);
	background_SR->SetBinError(m,sqrt(
					ZToNuNu_1_SR->GetBinError(m)*ZToNuNu_1_SR->GetBinError(m)+
					ZToNuNu_2_SR->GetBinError(m)*ZToNuNu_2_SR->GetBinError(m)+
					ZToNuNu_3_SR->GetBinError(m)*ZToNuNu_3_SR->GetBinError(m)+
					ZToNuNu_4_SR->GetBinError(m)*ZToNuNu_4_SR->GetBinError(m)+
					ZToNuNu_5_SR->GetBinError(m)*ZToNuNu_5_SR->GetBinError(m)+
					ZToNuNu_6_SR->GetBinError(m)*ZToNuNu_6_SR->GetBinError(m)+
					ZToNuNu_7_SR->GetBinError(m)*ZToNuNu_7_SR->GetBinError(m)+
					QCD_1_SR->GetBinError(m)*QCD_1_SR->GetBinError(m)+
					QCD_2_SR->GetBinError(m)*QCD_2_SR->GetBinError(m)+
					QCD_3_SR->GetBinError(m)*QCD_3_SR->GetBinError(m)+
					QCD_4_SR->GetBinError(m)*QCD_4_SR->GetBinError(m)+
					QCD_5_SR->GetBinError(m)*QCD_5_SR->GetBinError(m)+
					QCD_6_SR->GetBinError(m)*QCD_6_SR->GetBinError(m)+
					QCD_7_SR->GetBinError(m)*QCD_7_SR->GetBinError(m)+
					WToLNu_1_SR->GetBinError(m)*WToLNu_1_SR->GetBinError(m)+
					WToLNu_2_SR->GetBinError(m)*WToLNu_2_SR->GetBinError(m)+
					WToLNu_3_SR->GetBinError(m)*WToLNu_3_SR->GetBinError(m)+
					WToLNu_4_SR->GetBinError(m)*WToLNu_4_SR->GetBinError(m)+
					WToLNu_5_SR->GetBinError(m)*WToLNu_5_SR->GetBinError(m)+
					WToLNu_6_SR->GetBinError(m)*WToLNu_6_SR->GetBinError(m)+
					WToLNu_7_SR->GetBinError(m)*WToLNu_7_SR->GetBinError(m)+
					TT_1_SR->GetBinError(m)*TT_1_SR->GetBinError(m)+
					TT_2_SR->GetBinError(m)*TT_2_SR->GetBinError(m)+
					ST_1_SR->GetBinError(m)*ST_1_SR->GetBinError(m)+
					ST_2_SR->GetBinError(m)*ST_2_SR->GetBinError(m)+
					ST_3_SR->GetBinError(m)*ST_3_SR->GetBinError(m)+
					ST_4_SR->GetBinError(m)*ST_4_SR->GetBinError(m)+
					WW1_SR->GetBinError(m)*WW1_SR->GetBinError(m)+
					WW2_SR->GetBinError(m)*WW2_SR->GetBinError(m)+
					WZ1_SR->GetBinError(m)*WZ1_SR->GetBinError(m)+
					WZ2_SR->GetBinError(m)*WZ2_SR->GetBinError(m)+
					WZ3_SR->GetBinError(m)*WZ3_SR->GetBinError(m)+
					WZ4_SR->GetBinError(m)*WZ4_SR->GetBinError(m)+
					ZZ1_SR->GetBinError(m)*ZZ1_SR->GetBinError(m)+
					ZZ2_SR->GetBinError(m)*ZZ2_SR->GetBinError(m)+
					ZZ3_SR->GetBinError(m)*ZZ3_SR->GetBinError(m)+
					ZZ4_SR->GetBinError(m)*ZZ4_SR->GetBinError(m)+
					ttW_SR->GetBinError(m)*ttW_SR->GetBinError(m)+
					ttZ_SR->GetBinError(m)*ttZ_SR->GetBinError(m)+
					tZq_SR->GetBinError(m)*tZq_SR->GetBinError(m)
					));
	}

        for(int k=1; k<data_SR->GetNbinsX()+1; k++){
           data_paper->SetBinContent(k,data_SR->GetBinContent(k));
           background_paper->SetBinContent(k,background_SR->GetBinContent(k));
           tptzm0800lh_paper->SetBinContent(k,tptzm0800lh_SR->GetBinContent(k));
           tptzm1200lh_paper->SetBinContent(k,tptzm1200lh_SR->GetBinContent(k));
           tptzm1600lh_paper->SetBinContent(k,tptzm1600lh_SR->GetBinContent(k));
           tptzm1700lh_paper->SetBinContent(k,tptzm1700lh_SR->GetBinContent(k));
           ZToNuNu_1_paper->SetBinContent(k,ZToNuNu_1_SR->GetBinContent(k));        
           ZToNuNu_2_paper->SetBinContent(k,ZToNuNu_2_SR->GetBinContent(k));        
           ZToNuNu_3_paper->SetBinContent(k,ZToNuNu_3_SR->GetBinContent(k));        
           ZToNuNu_4_paper->SetBinContent(k,ZToNuNu_4_SR->GetBinContent(k));        
           ZToNuNu_5_paper->SetBinContent(k,ZToNuNu_5_SR->GetBinContent(k));        
           ZToNuNu_6_paper->SetBinContent(k,ZToNuNu_6_SR->GetBinContent(k));        
           ZToNuNu_7_paper->SetBinContent(k,ZToNuNu_7_SR->GetBinContent(k));        
           WToLNu_1_paper->SetBinContent(k,WToLNu_1_SR->GetBinContent(k));        
           WToLNu_2_paper->SetBinContent(k,WToLNu_2_SR->GetBinContent(k));        
           WToLNu_3_paper->SetBinContent(k,WToLNu_3_SR->GetBinContent(k));        
           WToLNu_4_paper->SetBinContent(k,WToLNu_4_SR->GetBinContent(k));        
           WToLNu_5_paper->SetBinContent(k,WToLNu_5_SR->GetBinContent(k));        
           WToLNu_6_paper->SetBinContent(k,WToLNu_6_SR->GetBinContent(k));        
           WToLNu_7_paper->SetBinContent(k,WToLNu_7_SR->GetBinContent(k));        
           QCD_1_paper->SetBinContent(k,QCD_1_SR->GetBinContent(k));        
           QCD_2_paper->SetBinContent(k,QCD_2_SR->GetBinContent(k));        
           QCD_3_paper->SetBinContent(k,QCD_3_SR->GetBinContent(k));        
           QCD_4_paper->SetBinContent(k,QCD_4_SR->GetBinContent(k));        
           QCD_5_paper->SetBinContent(k,QCD_5_SR->GetBinContent(k));        
           QCD_6_paper->SetBinContent(k,QCD_6_SR->GetBinContent(k));        
           QCD_7_paper->SetBinContent(k,QCD_7_SR->GetBinContent(k));        
           TT_1_paper->SetBinContent(k,TT_1_SR->GetBinContent(k));        
           TT_2_paper->SetBinContent(k,TT_2_SR->GetBinContent(k));        
           ST_1_paper->SetBinContent(k,ST_1_SR->GetBinContent(k));        
           ST_2_paper->SetBinContent(k,ST_2_SR->GetBinContent(k));        
           ST_3_paper->SetBinContent(k,ST_3_SR->GetBinContent(k));        
           ST_4_paper->SetBinContent(k,ST_4_SR->GetBinContent(k));        
           ZZ1_paper->SetBinContent(k,ZZ1_SR->GetBinContent(k));        
           ZZ2_paper->SetBinContent(k,ZZ2_SR->GetBinContent(k));        
           ZZ3_paper->SetBinContent(k,ZZ3_SR->GetBinContent(k));        
           ZZ4_paper->SetBinContent(k,ZZ4_SR->GetBinContent(k));        
           WZ1_paper->SetBinContent(k,WZ1_SR->GetBinContent(k));        
           WZ2_paper->SetBinContent(k,WZ2_SR->GetBinContent(k));        
           WZ3_paper->SetBinContent(k,WZ3_SR->GetBinContent(k));        
           WZ4_paper->SetBinContent(k,WZ4_SR->GetBinContent(k));        
           WW1_paper->SetBinContent(k,WW1_SR->GetBinContent(k));        
           WW2_paper->SetBinContent(k,WW2_SR->GetBinContent(k));        
           ttW_paper->SetBinContent(k,ttW_SR->GetBinContent(k));        
           ttZ_paper->SetBinContent(k,ttZ_SR->GetBinContent(k));        
           tZq_paper->SetBinContent(k,tZq_SR->GetBinContent(k));        


           data_paper->SetBinError(k,data_SR->GetBinError(k));
           background_paper->SetBinError(k,background_SR->GetBinError(k));
           tptzm0800lh_paper->SetBinError(k,tptzm0800lh_SR->GetBinError(k));
           tptzm1200lh_paper->SetBinError(k,tptzm1200lh_SR->GetBinError(k));
           tptzm1600lh_paper->SetBinError(k,tptzm1600lh_SR->GetBinError(k));
           tptzm1700lh_paper->SetBinError(k,tptzm1700lh_SR->GetBinError(k));
           ZToNuNu_1_paper->SetBinError(k,ZToNuNu_1_SR->GetBinError(k));        
           ZToNuNu_2_paper->SetBinError(k,ZToNuNu_2_SR->GetBinError(k));        
           ZToNuNu_3_paper->SetBinError(k,ZToNuNu_3_SR->GetBinError(k));        
           ZToNuNu_4_paper->SetBinError(k,ZToNuNu_4_SR->GetBinError(k));        
           ZToNuNu_5_paper->SetBinError(k,ZToNuNu_5_SR->GetBinError(k));        
           ZToNuNu_6_paper->SetBinError(k,ZToNuNu_6_SR->GetBinError(k));        
           ZToNuNu_7_paper->SetBinError(k,ZToNuNu_7_SR->GetBinError(k));        
           WToLNu_1_paper->SetBinError(k,WToLNu_1_SR->GetBinError(k));        
           WToLNu_2_paper->SetBinError(k,WToLNu_2_SR->GetBinError(k));        
           WToLNu_3_paper->SetBinError(k,WToLNu_3_SR->GetBinError(k));        
           WToLNu_4_paper->SetBinError(k,WToLNu_4_SR->GetBinError(k));        
           WToLNu_5_paper->SetBinError(k,WToLNu_5_SR->GetBinError(k));        
           WToLNu_6_paper->SetBinError(k,WToLNu_6_SR->GetBinError(k));        
           WToLNu_7_paper->SetBinError(k,WToLNu_7_SR->GetBinError(k));        
           QCD_1_paper->SetBinError(k,QCD_1_SR->GetBinError(k));        
           QCD_2_paper->SetBinError(k,QCD_2_SR->GetBinError(k));        
           QCD_3_paper->SetBinError(k,QCD_3_SR->GetBinError(k));        
           QCD_4_paper->SetBinError(k,QCD_4_SR->GetBinError(k));        
           QCD_5_paper->SetBinError(k,QCD_5_SR->GetBinError(k));        
           QCD_6_paper->SetBinError(k,QCD_6_SR->GetBinError(k));        
           QCD_7_paper->SetBinError(k,QCD_7_SR->GetBinError(k));        
           TT_1_paper->SetBinError(k,TT_1_SR->GetBinError(k));        
           TT_2_paper->SetBinError(k,TT_2_SR->GetBinError(k));        
           ST_1_paper->SetBinError(k,ST_1_SR->GetBinError(k));        
           ST_2_paper->SetBinError(k,ST_2_SR->GetBinError(k));        
           ST_3_paper->SetBinError(k,ST_3_SR->GetBinError(k));        
           ST_4_paper->SetBinError(k,ST_4_SR->GetBinError(k));        
           ZZ1_paper->SetBinError(k,ZZ1_SR->GetBinError(k));        
           ZZ2_paper->SetBinError(k,ZZ2_SR->GetBinError(k));        
           ZZ3_paper->SetBinError(k,ZZ3_SR->GetBinError(k));        
           ZZ4_paper->SetBinError(k,ZZ4_SR->GetBinError(k));        
           WZ1_paper->SetBinError(k,WZ1_SR->GetBinError(k));        
           WZ2_paper->SetBinError(k,WZ2_SR->GetBinError(k));        
           WZ3_paper->SetBinError(k,WZ3_SR->GetBinError(k));        
           WZ4_paper->SetBinError(k,WZ4_SR->GetBinError(k));        
           WW1_paper->SetBinError(k,WW1_SR->GetBinError(k));        
           WW2_paper->SetBinError(k,WW2_SR->GetBinError(k));        
           ttW_paper->SetBinError(k,ttW_SR->GetBinError(k));        
           ttZ_paper->SetBinError(k,ttZ_SR->GetBinError(k));        
           tZq_paper->SetBinError(k,tZq_SR->GetBinError(k));        
        }
      

        char NewFileName[500];
 
        char Year[2]; sprintf(Year,"%i",   year); TString YEAR = Year;
        if (category==0) sprintf(NewFileName, "h_MT_validation_nofwd_resolved_datadriven_"+YEAR+".root");
        if (category==1) sprintf(NewFileName, "h_MT_validation_fwd_resolved_datadriven_"+YEAR+".root");
  
        TFile f(NewFileName,"new");

        ST = (TH1F*)Hist->Clone(); 
        TT = (TH1F*)Hist->Clone(); 
        ttV = (TH1F*)Hist->Clone(); 
        VV = (TH1F*)Hist->Clone(); 
        QCD = (TH1F*)Hist->Clone(); 
        WToLNu = (TH1F*)Hist->Clone(); 
        ZToNuNu = (TH1F*)Hist->Clone(); 
	ST->Add(ST_1_paper);
	ST->Add(ST_2_paper);
	ST->Add(ST_3_paper);
	ST->Add(ST_4_paper);
	TT->Add(TT_1_paper);
	TT->Add(TT_2_paper);
	ttV->Add(ttZ_paper);
	ttV->Add(ttW_paper);
	ttV->Add(tZq_paper);
	VV->Add(ZZ1_paper);
	VV->Add(ZZ2_paper);
	VV->Add(ZZ3_paper);
	VV->Add(ZZ4_paper);
	VV->Add(WZ1_paper);
	VV->Add(WZ2_paper);
	VV->Add(WZ3_paper);
	VV->Add(WZ4_paper);
	VV->Add(WW1_paper);
	VV->Add(WW2_paper);
	QCD->Add(QCD_1_paper);
	QCD->Add(QCD_2_paper);
	QCD->Add(QCD_3_paper);
	QCD->Add(QCD_4_paper);
	QCD->Add(QCD_5_paper);
	QCD->Add(QCD_6_paper);
	QCD->Add(QCD_7_paper);
	WToLNu->Add(WToLNu_1_paper);
	WToLNu->Add(WToLNu_2_paper);
	WToLNu->Add(WToLNu_3_paper);
	WToLNu->Add(WToLNu_4_paper);
	WToLNu->Add(WToLNu_5_paper);
	WToLNu->Add(WToLNu_6_paper);
	WToLNu->Add(WToLNu_7_paper);
	ZToNuNu->Add(ZToNuNu_1_paper);
	ZToNuNu->Add(ZToNuNu_2_paper);
	ZToNuNu->Add(ZToNuNu_3_paper);
	ZToNuNu->Add(ZToNuNu_4_paper);
	ZToNuNu->Add(ZToNuNu_5_paper);
	ZToNuNu->Add(ZToNuNu_6_paper);
	ZToNuNu->Add(ZToNuNu_7_paper);
        data = (TH1F*)data_paper->Clone();

	data      ->SetName("Data");   
	ZToNuNu   ->SetName("ZJets");    
	WToLNu    ->SetName("WJets");   
	TT        ->SetName("ttbar");   
	ST        ->SetName("SingleTop");   
	QCD       ->SetName("QCD");   
	VV        ->SetName("VV");   
	ttV       ->SetName("ttV");
        
         
	data      ->Write();
	ZToNuNu   ->Write();
	WToLNu    ->Write();
	TT        ->Write();
	ST        ->Write();   
	QCD       ->Write();  
	VV        ->Write(); 
	ttV       ->Write();
	
	tptzm0800lh_paper->SetLineWidth(2); tptzm1200lh_paper->SetLineWidth(2); tptzm1600lh_paper->SetLineWidth(2); tptzm1700lh_paper->SetLineWidth(2); 
	tptzm0800lh_paper->SetLineColor(2); tptzm1200lh_paper->SetLineColor(2); tptzm1600lh_paper->SetLineColor(2); tptzm1700lh_paper->SetLineColor(2); 
        tptzm1200lh_paper->SetLineStyle(2); tptzm1600lh_paper->SetLineStyle(4);

	ZToNuNu_1_paper->SetLineWidth(2); ZToNuNu_2_paper->SetLineWidth(2);ZToNuNu_3_paper->SetLineWidth(2); ZToNuNu_4_paper->SetLineWidth(2); ZToNuNu_5_paper->SetLineWidth(2); ZToNuNu_6_paper->SetLineWidth(2); ZToNuNu_7_paper->SetLineWidth(2);
	QCD_1_paper->SetLineWidth(2); QCD_2_paper->SetLineWidth(2);QCD_3_paper->SetLineWidth(2); QCD_4_paper->SetLineWidth(2); QCD_5_paper->SetLineWidth(2); QCD_6_paper->SetLineWidth(2); QCD_7_paper->SetLineWidth(2);
	WToLNu_1_paper->SetLineWidth(2); WToLNu_2_paper->SetLineWidth(2); WToLNu_3_paper->SetLineWidth(2); WToLNu_4_paper->SetLineWidth(2); WToLNu_5_paper->SetLineWidth(2); WToLNu_6_paper->SetLineWidth(2); WToLNu_7_paper->SetLineWidth(2);
	TT_1_paper->SetLineWidth(2); TT_2_paper->SetLineWidth(2);
	ST_1_paper->SetLineWidth(2); ST_2_paper->SetLineWidth(2); ST_3_paper->SetLineWidth(2); ST_4_paper->SetLineWidth(2); 
	ZZ1_paper->SetLineWidth(2); ZZ2_paper->SetLineWidth(2); ZZ3_paper->SetLineWidth(2); ZZ4_paper->SetLineWidth(2); WW1_paper->SetLineWidth(2); WW2_paper->SetLineWidth(2); WZ1_paper->SetLineWidth(2); WZ2_paper->SetLineWidth(2); WZ3_paper->SetLineWidth(2); WZ4_paper->SetLineWidth(2);
	ttW_paper->SetLineWidth(2); ttZ_paper->SetLineWidth(2); tZq_paper->SetLineWidth(2);

	ZToNuNu_1_paper->SetLineColor(kOrange); ZToNuNu_2_paper->SetLineColor(kOrange);ZToNuNu_3_paper->SetLineColor(kOrange); ZToNuNu_4_paper->SetLineColor(kOrange); ZToNuNu_5_paper->SetLineColor(kOrange); ZToNuNu_6_paper->SetLineColor(kOrange); ZToNuNu_7_paper->SetLineColor(kOrange);
	QCD_1_paper->SetLineColor(kGreen-4); QCD_2_paper->SetLineColor(kGreen-4);QCD_3_paper->SetLineColor(kGreen-4); QCD_4_paper->SetLineColor(kGreen-4); QCD_5_paper->SetLineColor(kGreen-4); QCD_6_paper->SetLineColor(kGreen-4); QCD_7_paper->SetLineColor(kGreen-4);
	WToLNu_1_paper->SetLineColor(kOrange); WToLNu_2_paper->SetLineColor(kOrange); WToLNu_3_paper->SetLineColor(kOrange); WToLNu_4_paper->SetLineColor(kOrange); WToLNu_5_paper->SetLineColor(kOrange); WToLNu_6_paper->SetLineColor(kOrange); WToLNu_7_paper->SetLineColor(kOrange);
	TT_1_paper->SetLineColor(kGreen+2); TT_2_paper->SetLineColor(kGreen+2);
	ST_1_paper->SetLineColor(kGreen+2); ST_2_paper->SetLineColor(kGreen+2); ST_3_paper->SetLineColor(kGreen+2); ST_4_paper->SetLineColor(kGreen+2); 
	ZZ1_paper->SetLineColor(kGreen-4); ZZ2_paper->SetLineColor(kGreen-4); ZZ3_paper->SetLineColor(kGreen-4); ZZ4_paper->SetLineColor(kGreen-4); WW1_paper->SetLineColor(kGreen-4); WW2_paper->SetLineColor(kGreen-4); WZ1_paper->SetLineColor(kGreen-4); WZ2_paper->SetLineColor(kGreen-4); WZ3_paper->SetLineColor(kGreen-4); WZ4_paper->SetLineColor(kGreen-4);
	ttW_paper->SetLineColor(kGreen+2); ttZ_paper->SetLineColor(kGreen+2); tZq_paper->SetLineColor(kGreen+2);

	ZToNuNu_1_paper->SetFillColor(kOrange); ZToNuNu_2_paper->SetFillColor(kOrange);ZToNuNu_3_paper->SetFillColor(kOrange); ZToNuNu_4_paper->SetFillColor(kOrange); ZToNuNu_5_paper->SetFillColor(kOrange); ZToNuNu_6_paper->SetFillColor(kOrange); ZToNuNu_7_paper->SetFillColor(kOrange);
	QCD_1_paper->SetFillColor(kGreen-4); QCD_2_paper->SetFillColor(kGreen-4);QCD_3_paper->SetFillColor(kGreen-4); QCD_4_paper->SetFillColor(kGreen-4); QCD_5_paper->SetFillColor(kGreen-4); QCD_6_paper->SetFillColor(kGreen-4); QCD_7_paper->SetFillColor(kGreen-4);
	WToLNu_1_paper->SetFillColor(kOrange); WToLNu_2_paper->SetFillColor(kOrange); WToLNu_3_paper->SetFillColor(kOrange); WToLNu_4_paper->SetFillColor(kOrange); WToLNu_5_paper->SetFillColor(kOrange); WToLNu_6_paper->SetFillColor(kOrange); WToLNu_7_paper->SetFillColor(kOrange);
	TT_1_paper->SetFillColor(kGreen+2); TT_2_paper->SetFillColor(kGreen+2); 
	ST_1_paper->SetFillColor(kGreen+2); ST_2_paper->SetFillColor(kGreen+2); ST_3_paper->SetFillColor(kGreen+2); ST_4_paper->SetFillColor(kGreen+2); 
	ZZ1_paper->SetFillColor(kGreen-4); ZZ2_paper->SetFillColor(kGreen-4); ZZ3_paper->SetFillColor(kGreen-4); ZZ4_paper->SetFillColor(kGreen-4); WW1_paper->SetFillColor(kGreen-4); WW2_paper->SetFillColor(kGreen-4); WZ1_paper->SetFillColor(kGreen-4); WZ2_paper->SetFillColor(kGreen-4); WZ3_paper->SetFillColor(kGreen-4); WZ4_paper->SetFillColor(kGreen-4); 
	ttW_paper->SetFillColor(kGreen+2); ttZ_paper->SetFillColor(kGreen+2); tZq_paper->SetFillColor(kGreen+2);

	data_paper->SetLineWidth(2); data_paper->SetLineColor(1); data_paper->SetMarkerColor(1); data_paper->SetMarkerStyle(20); data_paper->SetMarkerSize(1.3);

	Double_t dataErr   = 0; Float_t dataYield = data_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX()-1,dataErr,"");
	Double_t ZToNuNu_1Err   = 0; Float_t ZToNuNu_1Yield = ZToNuNu_1_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ZToNuNu_1Err,"");
	Double_t ZToNuNu_2Err   = 0; Float_t ZToNuNu_2Yield = ZToNuNu_2_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ZToNuNu_2Err,"");
	Double_t ZToNuNu_3Err   = 0; Float_t ZToNuNu_3Yield = ZToNuNu_3_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ZToNuNu_3Err,"");
	Double_t ZToNuNu_4Err   = 0; Float_t ZToNuNu_4Yield = ZToNuNu_4_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ZToNuNu_4Err,"");
	Double_t ZToNuNu_5Err   = 0; Float_t ZToNuNu_5Yield = ZToNuNu_5_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ZToNuNu_5Err,"");
	Double_t ZToNuNu_6Err   = 0; Float_t ZToNuNu_6Yield = ZToNuNu_6_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ZToNuNu_6Err,"");
	Double_t ZToNuNu_7Err   = 0; Float_t ZToNuNu_7Yield = ZToNuNu_7_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ZToNuNu_7Err,"");
	Double_t QCD_1Err   = 0; Float_t QCD_1Yield = QCD_1_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),QCD_1Err,"");
	Double_t QCD_2Err   = 0; Float_t QCD_2Yield = QCD_2_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),QCD_2Err,"");
	Double_t QCD_3Err   = 0; Float_t QCD_3Yield = QCD_3_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),QCD_3Err,"");
	Double_t QCD_4Err   = 0; Float_t QCD_4Yield = QCD_4_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),QCD_4Err,"");
	Double_t QCD_5Err   = 0; Float_t QCD_5Yield = QCD_5_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),QCD_5Err,"");
	Double_t QCD_6Err   = 0; Float_t QCD_6Yield = QCD_6_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),QCD_6Err,"");
	Double_t QCD_7Err   = 0; Float_t QCD_7Yield = QCD_7_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),QCD_7Err,"");
	Double_t WToLNu_1Err = 0; Float_t WToLNu_1Yield = WToLNu_1_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),WToLNu_1Err,"");
	Double_t WToLNu_2Err = 0; Float_t WToLNu_2Yield = WToLNu_2_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),WToLNu_2Err,"");
	Double_t WToLNu_3Err = 0; Float_t WToLNu_3Yield = WToLNu_3_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),WToLNu_3Err,"");
	Double_t WToLNu_4Err = 0; Float_t WToLNu_4Yield = WToLNu_4_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),WToLNu_4Err,"");
	Double_t WToLNu_5Err = 0; Float_t WToLNu_5Yield = WToLNu_5_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),WToLNu_5Err,"");
	Double_t WToLNu_6Err = 0; Float_t WToLNu_6Yield = WToLNu_6_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),WToLNu_6Err,"");
	Double_t WToLNu_7Err = 0; Float_t WToLNu_7Yield = WToLNu_7_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),WToLNu_7Err,"");
	Double_t TT_1Err = 0; Float_t TT_1Yield = TT_1_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),TT_1Err,"");
	Double_t TT_2Err = 0; Float_t TT_2Yield = TT_2_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),TT_2Err,"");
	Double_t ST_1Err = 0; Float_t ST_1Yield = ST_1_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ST_1Err,"");
	Double_t ST_2Err = 0; Float_t ST_2Yield = ST_2_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ST_2Err,"");
	Double_t ST_3Err = 0; Float_t ST_3Yield = ST_3_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ST_3Err,"");
	Double_t ST_4Err = 0; Float_t ST_4Yield = ST_4_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ST_4Err,"");
	Double_t ZZ1Err    = 0; Float_t ZZ1Yield  = ZZ1_SR ->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ZZ1Err, "");
	Double_t ZZ2Err    = 0; Float_t ZZ2Yield  = ZZ2_SR ->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ZZ2Err, "");
	Double_t ZZ3Err    = 0; Float_t ZZ3Yield  = ZZ3_SR ->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ZZ3Err, "");
	Double_t ZZ4Err    = 0; Float_t ZZ4Yield  = ZZ4_SR ->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ZZ4Err, "");
	Double_t WZ1Err    = 0; Float_t WZ1Yield  = WZ1_SR ->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),WZ1Err, "");
	Double_t WZ2Err    = 0; Float_t WZ2Yield  = WZ2_SR ->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),WZ2Err, "");
	Double_t WZ3Err    = 0; Float_t WZ3Yield  = WZ3_SR ->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),WZ3Err, "");
	Double_t WZ4Err    = 0; Float_t WZ4Yield  = WZ4_SR ->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),WZ4Err, "");
	Double_t WW1Err    = 0; Float_t WW1Yield  = WW1_SR ->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),WW1Err, "");
	Double_t WW2Err    = 0; Float_t WW2Yield  = WW2_SR ->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),WW2Err, "");
	Double_t ttWErr    = 0; Float_t ttWYield  = ttW_SR ->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ttWErr, "");
	Double_t ttZErr    = 0; Float_t ttZYield  = ttZ_SR ->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),ttZErr, "");
	Double_t tZqErr    = 0; Float_t tZqYield  = tZq_SR ->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),tZqErr, "");

	Double_t tptzm0800_Err= 0; Float_t tptzm0800_Yield = tptzm0800lh_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),tptzm0800_Err,"");
	Double_t tptzm1200_Err= 0; Float_t tptzm1200_Yield = tptzm1200lh_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),tptzm1200_Err,"");
	Double_t tptzm1600_Err= 0; Float_t tptzm1600_Yield = tptzm1600lh_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),tptzm1600_Err,"");
	Double_t tptzm1700_Err= 0; Float_t tptzm1700_Yield = tptzm1700lh_SR->IntegralAndError(1,tptzm0800lh_SR->GetNbinsX(),tptzm1700_Err,"");

    if(i==0){
      cout<<endl;
      //cout<<"Plotting "<<name[i]<<endl;
      cout<<"DATA      = "<<data_SR->Integral()<<" +/- "<<dataErr<<endl;
      cout<<"ZToNuNu   = "<<ZToNuNu_1_SR->Integral()+ZToNuNu_2_SR->Integral()+ZToNuNu_3_SR->Integral()+ZToNuNu_4_SR->Integral()+ZToNuNu_5_SR->Integral()+ZToNuNu_6_SR->Integral()+ZToNuNu_7_SR->Integral()<<" +/- "<<
	sqrt(ZToNuNu_1Err*ZToNuNu_1Err+ZToNuNu_2Err*ZToNuNu_2Err+ZToNuNu_3Err*ZToNuNu_3Err+ZToNuNu_4Err*ZToNuNu_4Err+ZToNuNu_5Err*ZToNuNu_5Err+ZToNuNu_6Err*ZToNuNu_6Err+ZToNuNu_7Err*ZToNuNu_7Err)<<endl;
      cout<<"QCD       = "<<QCD_1_SR->Integral()+QCD_2_SR->Integral()+QCD_3_SR->Integral()+QCD_4_SR->Integral()+QCD_5_SR->Integral()+QCD_6_SR->Integral()+QCD_7_SR->Integral()<<" +/- "<<
	sqrt(QCD_1Err*QCD_1Err+QCD_2Err*QCD_2Err+QCD_3Err*QCD_3Err+QCD_4Err*QCD_4Err+QCD_5Err*QCD_5Err+QCD_6Err*QCD_6Err+QCD_7Err*QCD_7Err)<<endl;
	  cout<<"WToLNu    = "<<WToLNu_1_SR->Integral()+WToLNu_2_SR->Integral()+WToLNu_3_SR->Integral()+WToLNu_4_SR->Integral()+WToLNu_5_SR->Integral()+WToLNu_6_SR->Integral()+WToLNu_7_SR->Integral()<<" +/- "<<sqrt(WToLNu_1Err*WToLNu_1Err+WToLNu_2Err*WToLNu_2Err+WToLNu_3Err*WToLNu_3Err+WToLNu_4Err*WToLNu_4Err+WToLNu_5Err*WToLNu_5Err+WToLNu_6Err*WToLNu_6Err+WToLNu_7Err*WToLNu_7Err)<<endl;
      //cout<<"WToLNu    = "<<WToLNu_SR->Integral()<<" +/- "<<sqrt(WToLNu_Err*WToLNu_Err)<<endl;
	  cout<<"TT        = "<<TT_1_SR->Integral()+TT_2_SR->Integral()<<" +/- "<<sqrt(TT_1Err*TT_1Err+TT_2Err*TT_2Err)<<endl;
	  cout<<"ST        = "<<ST_1_SR->Integral()+ST_2_SR->Integral()+ST_3_SR->Integral()+ST_4_SR->Integral()<<" +/- "<<sqrt(ST_1Err*ST_1Err+ST_2Err*ST_2Err+ST_3Err*ST_3Err+ST_4Err*ST_4Err)<<endl;
      cout<<"Diboson   = "<<ZZ1_SR->Integral()+ZZ2_SR->Integral()+ZZ3_SR->Integral()+ZZ4_SR->Integral()+WZ1_SR->Integral()+WZ2_SR->Integral()+WZ3_SR->Integral()+WZ4_SR->Integral()+WW1_SR->Integral()+WW2_SR->Integral()<<" +/- "<<sqrt(ZZ1Err*ZZ1Err+ZZ2Err*ZZ2Err+ZZ3Err*ZZ3Err+ZZ4Err*ZZ4Err+WZ1Err*WZ1Err+WZ2Err*WZ2Err+WZ3Err*WZ3Err+WZ4Err*WZ4Err+WW1Err*WW1Err+WW2Err*WW2Err)<<endl;
      cout<<"ttV+tZq   = "<<ttW_SR->Integral()+ttZ_SR->Integral()+tZq_SR->Integral()<<" +/- "<<sqrt(ttWErr*ttWErr+ttZErr*ttZErr+tZqErr*tZqErr)<<endl;
	  cout<<"Total BKG = "<<ZToNuNu_1_SR->Integral()+ZToNuNu_2_SR->Integral()+ZToNuNu_3_SR->Integral()+ZToNuNu_4_SR->Integral()+ZToNuNu_5_SR->Integral()+ZToNuNu_6_SR->Integral()+ZToNuNu_7_SR->Integral()+QCD_1_SR->Integral()+QCD_2_SR->Integral()+QCD_3_SR->Integral()+QCD_4_SR->Integral()+QCD_5_SR->Integral()+QCD_6_SR->Integral()+QCD_7_SR->Integral()+WToLNu_1_SR->Integral()+WToLNu_2_SR->Integral()+WToLNu_3_SR->Integral()+WToLNu_4_SR->Integral()+WToLNu_5_SR->Integral()+WToLNu_6_SR->Integral()+WToLNu_7_SR->Integral()+TT_1_SR->Integral()+TT_2_SR->Integral()+ST_1_SR->Integral()+ST_2_SR->Integral()+ST_3_SR->Integral()+ST_4_SR->Integral()+ZZ1_SR->Integral()+ZZ2_SR->Integral()+ZZ3_SR->Integral()+ZZ4_SR->Integral()+WZ1_SR->Integral()+WZ2_SR->Integral()+WZ3_SR->Integral()+WZ4_SR->Integral()+WW1_SR->Integral()+WW2_SR->Integral()+ttW_SR->Integral()+ttZ_SR->Integral()+tZq_SR->Integral()<<" +/- "<<
		  sqrt(ZToNuNu_1Err*ZToNuNu_1Err+ZToNuNu_2Err*ZToNuNu_2Err+ZToNuNu_3Err*ZToNuNu_3Err+ZToNuNu_4Err*ZToNuNu_4Err+ZToNuNu_5Err*ZToNuNu_5Err+ZToNuNu_6Err*ZToNuNu_6Err+ZToNuNu_7Err*ZToNuNu_7Err+QCD_1Err*QCD_1Err+QCD_2Err*QCD_2Err+QCD_3Err*QCD_3Err+QCD_4Err*QCD_4Err+QCD_5Err*QCD_5Err+QCD_6Err*QCD_6Err+QCD_7Err*QCD_7Err+WToLNu_1Err*WToLNu_1Err+WToLNu_2Err*WToLNu_2Err+WToLNu_3Err*WToLNu_3Err+WToLNu_4Err*WToLNu_4Err+WToLNu_5Err*WToLNu_5Err+WToLNu_6Err*WToLNu_6Err+WToLNu_7Err*WToLNu_7Err+ZZ1Err*ZZ1Err+ZZ2Err*ZZ2Err+ZZ3Err*ZZ3Err+ZZ4Err*ZZ4Err+WZ1Err*WZ1Err+WZ2Err*WZ2Err+WZ3Err*WZ3Err+WZ4Err*WZ4Err+WW1Err*WW1Err+WW2Err*WW2Err+ST_1Err*ST_1Err+ST_2Err*ST_2Err+ST_3Err*ST_3Err+ST_4Err*ST_4Err+TT_1Err*TT_1Err+TT_2Err*TT_2Err+ttWErr*ttWErr+ttZErr*ttZErr+tZqErr*tZqErr)<<endl;
      cout<<"Tprime LH 0800 = "<<tptzm0800lh_SR->Integral()<<" +/- "<<sqrt(tptzm0800_Err*tptzm0800_Err)<<endl;
	  cout<<"Tprime LH 1200 = "<<tptzm1200lh_SR->Integral()<<" +/- "<<sqrt(tptzm1200_Err*tptzm1200_Err)<<endl;
	  cout<<"Tprime LH 1600 = "<<tptzm1600lh_SR->Integral()<<" +/- "<<sqrt(tptzm1600_Err*tptzm1600_Err)<<endl;
	  cout<<"Tprime LH 1700 = "<<tptzm1700lh_SR->Integral()<<" +/- "<<sqrt(tptzm1700_Err*tptzm1700_Err)<<endl;
	}

    TCanvas* c1 = new TCanvas("c1","c1",0,0,600,600);

	//////
	//画下面data/MC的比率计算图
	//////
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    TPad *c1_1 = new TPad("c1_1","newpad",0.01,0.01,0.99,0.32);
    c1_1->Draw();
    c1_1->cd();
    c1_1->SetTopMargin(0.045);
    c1_1->SetBottomMargin(0.35);//0.3
    c1_1->SetRightMargin(0.035);
    c1_1->SetLeftMargin(0.12);
    
    TGraphAsymmErrors *gDATA = new TGraphAsymmErrors(data_paper);	
    gDATA->SetLineWidth(2); 
    gDATA->SetLineColor(1);
    gDATA->SetMarkerColor(1); 
    gDATA->SetMarkerStyle(20); 
    gDATA->SetMarkerSize(1.3);
    for (int i = 0; i < gDATA->GetN(); ++i) {
      double alpha = 1 - 0.6827;
      int M = gDATA->GetY()[i];
      double L =  (M==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,M,1.));
      double U =  ROOT::Math::gamma_quantile_c(alpha/2,M+1,1);
      //if(M!=0){
      gDATA->SetPointEYlow(i, M-L);
      gDATA->SetPointEYhigh(i, U-M);
      //}
    }
    TH1F *RATIO2 = (TH1F*)background_paper->Clone();
    TH1F *RATIOG = (TH1F*)(data_paper->Clone("ratiog"));
    RATIOG->SetLineWidth(2);
    RATIOG->SetMarkerColor(1);
    RATIOG->SetMarkerStyle(20);
    RATIOG->SetMarkerSize(1.3);

    Double_t x[bin[i]]; Double_t exl[bin[i]]; Double_t exh[bin[i]];
    Double_t y[bin[i]]; Double_t eyl[bin[i]]; Double_t eyh[bin[i]]; 
    for(int m=0; m<background_paper->GetNbinsX(); m++){ 
      x[m]=Min[i]+m*(Max[i]-Min[i])/bin[i]+(Max[i]-Min[i])/(2*bin[i]);
      exl[m]=(Max[i]-Min[i])/(2*bin[i]);
      exh[m]=(Max[i]-Min[i])/(2*bin[i]);
      RATIO2->SetBinContent(m+1,1);
      if(background_paper->GetBinContent(m+1)!=0) {
	y[m]=data_paper->GetBinContent(m+1)/background_paper->GetBinContent(m+1);
	eyl[m]=sqrt(gDATA->GetErrorYlow(m)*gDATA->GetErrorYlow(m))/background_paper->GetBinContent(m+1);
	eyh[m]=sqrt(gDATA->GetErrorYhigh(m)*gDATA->GetErrorYhigh(m))/background_paper->GetBinContent(m+1);
	RATIO2->SetBinError(m+1,background_paper->GetBinError(m+1)/background_paper->GetBinContent(m+1));
      } else {
	y[m]=-1;
	eyl[m]=0;
	eyh[m]=0;
      }
    }

    TGraphAsymmErrors *RATIO = new TGraphAsymmErrors(bin[i],x,y,exl,exh,eyl,eyh);
    RATIOG->Divide(background_paper);
    //RATIO->Draw("AE0p");
    RATIOG->Draw("epx0e0");
    RATIOG->SetMarkerColor(1); 
    RATIOG->SetMarkerStyle(20); 
    RATIOG->SetMarkerSize(1.0);
    if(category==0) {RATIOG->SetMaximum(2);RATIOG->SetMinimum(0);}
    if(category==1) {RATIOG->SetMaximum(2);RATIOG->SetMinimum(0);}
    RATIOG->SetLineColor(1);
    RATIOG->SetLineWidth(2);
    RATIOG->GetXaxis()->SetTitleOffset(1.09);
    RATIOG->GetXaxis()->SetLabelOffset(0.06);
    RATIOG->GetYaxis()->SetTitleOffset(0.30);//0.35
    RATIOG->SetTitle("");
    RATIOG->GetYaxis()->SetTitle("#frac{Data}{Bkg}");
    RATIOG->GetXaxis()->SetTitle("M_{T} [TeV]");
    RATIOG->GetXaxis()->SetLabelSize(0.15);//0.13
    RATIOG->GetYaxis()->SetLabelSize(0.12); //0.1
    RATIOG->GetXaxis()->SetTitleSize(0.15);//0.13
    RATIOG->GetYaxis()->SetTitleSize(0.15);//0.13
    RATIOG->GetYaxis()->CenterTitle();
    RATIOG->GetYaxis()->SetNdivisions(503);
    RATIOG->GetXaxis()->SetRangeUser(Min[i],Max[i]);
    RATIO2->SetFillStyle(3005);
    RATIO2->SetFillColor(12);
    RATIO2->SetLineColor(0);
    RATIO2->SetMarkerSize(0);
    RATIO2->Draw("E2same");
    //RATIO->Draw("E0psame");
    RATIOG->Draw("same epx0e0");

    TLine* line = new TLine(0.5,1,3,1);
    line->SetLineColor(1);
    //line->SetLineWidth(1);
    line->Draw("same");	
    c1->cd();
    
	/////
	//画上面的data/MC图
	/////
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.32,0.99,1.0);
    c1_2->Draw();
    c1_2->cd();
    c1_2->SetTopMargin(0.08);
    c1_2->SetBottomMargin(0.02);
    c1_2->SetRightMargin(0.035);
    c1_2->SetLeftMargin(0.12);
    
    THStack *hs = new THStack("hs","hs");
    hs->Add(ST_1_paper);
    hs->Add(ST_2_paper);
    hs->Add(ST_3_paper);
    hs->Add(ST_4_paper);
    hs->Add(TT_1_paper);
    hs->Add(TT_2_paper);
    hs->Add(ttZ_paper);
    hs->Add(ttW_paper);
    hs->Add(tZq_paper);
    hs->Add(ZZ1_paper);
    hs->Add(ZZ2_paper);
    hs->Add(ZZ3_paper);
    hs->Add(ZZ4_paper);
    hs->Add(WZ1_paper);
    hs->Add(WZ2_paper);
    hs->Add(WZ3_paper);
    hs->Add(WZ4_paper);
    hs->Add(WW1_paper);
    hs->Add(WW2_paper);
    hs->Add(QCD_1_paper);
    hs->Add(QCD_2_paper);
    hs->Add(QCD_3_paper);
    hs->Add(QCD_4_paper);
    hs->Add(QCD_5_paper);
    hs->Add(QCD_6_paper);
    hs->Add(QCD_7_paper);
    hs->Add(WToLNu_1_paper);
    hs->Add(WToLNu_2_paper);
    hs->Add(WToLNu_3_paper);
    hs->Add(WToLNu_4_paper);
    hs->Add(WToLNu_5_paper);
    hs->Add(WToLNu_6_paper);
    hs->Add(WToLNu_7_paper);
    hs->Add(ZToNuNu_1_paper);
    hs->Add(ZToNuNu_2_paper);
    hs->Add(ZToNuNu_3_paper);
    hs->Add(ZToNuNu_4_paper);
    hs->Add(ZToNuNu_5_paper);
    hs->Add(ZToNuNu_6_paper);
    hs->Add(ZToNuNu_7_paper);
	
    
    hs->Draw("histo");
    hs->SetMinimum(0);
    hs->GetYaxis()->SetTitleSize(0.065);//0.055
    hs->GetXaxis()->SetTitleSize(0.045);
    hs->GetYaxis()->SetLabelSize(0.065);//0.055
    hs->GetXaxis()->SetLabelSize(0.0); 
    hs->SetTitle("");
    hs->GetYaxis()->SetTitle("Events / 0.1 TeV");
    hs->GetXaxis()->SetTitle("");
    hs->GetYaxis()->SetTitleOffset(0.95);
    hs->GetXaxis()->SetTitleOffset(0.85);
    //tptzm0800lh_SR->Draw("samehisto");
    //tptzm1200lh_SR->Draw("samehisto");
    //tptzm1600lh_SR->Draw("samehisto");
    //data_paper->Draw("E same"); 
    data_paper->Draw("same epx0e0"); 
    
    background_paper->SetFillStyle(3005);
    background_paper->SetFillColor(12);
    background_paper->SetLineColor(12);
    background_paper->Draw("E2same");
    
    float maxy=-10;
    float ADD=20;
    for(int ABC=0; ABC<data_paper->GetNbinsX(); ABC++){
      if(background_paper->GetBinContent(ABC+1)+ADD>=maxy) maxy=background_paper->GetBinContent(ABC+1)+ADD;
      if(data_paper      ->GetBinContent(ABC+1)+ADD>=maxy) maxy=data_paper      ->GetBinContent(ABC+1)+ADD;
    }
    hs->SetMaximum(maxy);
    hs->SetMaximum(1000000);
    hs->SetMinimum(0.5);
    c1_2->SetLogy();

	/////
	//画图上各种说明文字
	/////
    TPad *pad = new TPad("pad","pad",0.01,0.01,0.99,0.99);
    gPad->RedrawAxis();
    TString channelText = "";
    float channelTextFont   = 42;
    float channelTextSize   = 0.060;
    TString cmsText     = "CMS";
    float cmsTextFont   = 61;  // default is helvetic-bold
    bool writeExtraText = true;
    TString extraText   = "Preliminary";
    //TString extraText   = "";
    float extraTextFont = 52;  // default is helvetica-italics
    // text sizes and text offsets with respect to the top frame in unit of the top margin size
    float lumiTextSize     = 0.7;
    float lumiTextOffset   = 0.2;
    float cmsTextSize      = 0.75;
    float cmsTextOffset    = 0.1;  // only used in outOfFrame version
    float relPosX    = 0.045;
    float relPosY    = 0.035;
    float relExtraDY = 1.2;
    // ratio of "CMS" and extra text size
    float extraOverCmsTextSize  = 0.76;
    TString lumi_13TeV;
    lumi_13TeV = "36.3 fb^{-1}";
    TString lumiText;
    lumiText += lumi_13TeV;
    lumiText += " (13 TeV)";
    TString channelText1;
    channelText1 = "Validation region";
    TString channelText2;
    if(category==0) {channelText2 = "0 forward jets";}
    if(category==1) {channelText2 = "#geq 1 forward jet";}
    float t = pad->GetTopMargin();
    float b = pad->GetBottomMargin();
    float r = pad->GetRightMargin();
    float l = pad->GetLeftMargin();
    TLatex latex;
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);    
    float extraTextSize = extraOverCmsTextSize*cmsTextSize;
    latex.SetTextFont(42);
    latex.SetTextAlign(31); 
    latex.SetTextSize(lumiTextSize*t);    
    latex.DrawLatex(1-r+0.06,0.94,lumiText);
    latex.SetTextFont(cmsTextFont);
    latex.SetTextAlign(11); 
    latex.SetTextSize(cmsTextSize*t);    
    //latex.DrawLatex(l+0.01, 0.94,cmsText);
    //latex.DrawLatex(l+0.045, 1-t+lumiTextOffset*t-0.08,cmsText);
    latex.DrawLatex(l+0.165, 1-t+lumiTextOffset*t-0.1,cmsText);//0.075
    latex.SetTextFont(extraTextFont);
    latex.SetTextSize(extraTextSize*t);
    //latex.DrawLatex(l+0.12, 0.94, extraText); 
    //latex.DrawLatex(l+0.165, 1-t+lumiTextOffset*t-0.08, extraText);
    latex.SetTextFont(channelTextFont);
    latex.SetTextSize(channelTextSize);
    latex.DrawLatex(l+0.165, 1-t+lumiTextOffset*t-0.19, channelText1);
    latex.DrawLatex(l+0.165, 1-t+lumiTextOffset*t-0.28, channelText2);
    //latex.DrawLatex(l+0.02, 0.94, channelText2);


    //定义图中各个线和直方图的颜色
    TLegend *pl2 = new TLegend(0.645,0.45,0.95,0.90);
    pl2->SetTextSize(0.055); 
    pl2->SetTextFont(62); 
    pl2->SetFillColor(0);
    pl2->SetFillStyle(0);
    TLegendEntry *ple2 = pl2->AddEntry(data_paper, "Data",  "PE"); 
    ple2 = pl2->AddEntry(ZToNuNu_1_paper, "W/Z + jets",  "F");
    ple2 = pl2->AddEntry(QCD_1_paper, "Other",  "F");
    ple2 = pl2->AddEntry(ST_1_paper, "t#bar{t}",  "F");
    ple2 = pl2->AddEntry(RATIO2, "Stat+syst",  "F");
    //ple2 = pl2->AddEntry(ttZ_SR, "ttV and tZq (V = Z or W)",  "F");
    //ple2 = pl2->AddEntry(tptzm0800lh_SR, "T, M=0.8TeV, #sigma#times100 ",  "L"); 
    //ple2 = pl2->AddEntry(tptzm1200lh_SR, "T, M=1.2TeV, #sigma#times100 ",  "L"); 
    //ple2 = pl2->AddEntry(tptzm1600lh_SR, "T, M=1.6TeV, #sigma#times100 ",  "L"); 
    //ple2 = pl2->AddEntry(tptzm1700lh_SR, "T, M=1.7TeV, #sigma#times100",  "L"); 
    pl2->SetBorderSize(0);
    pl2->Draw();
    
    TString NAME = name[i];
    char cat[2]; sprintf(cat,"%i",   category); TString CAT = cat;
    cout<<"Finished "<<NAME<<endl;
    c1->SaveAs(NAME+"_cat"+CAT+".pdf");
    c1->SaveAs(NAME+"_cat"+CAT+".jpg");
    //c1->SaveAs(NAME+".root");
    //c1->SaveAs("/publicfs/cms/user/yutz/Tprime/2016_dineutrino/"+NAME+".pdf");
    //c1->SaveAs("/publicfs/cms/user/yutz/Tprime/2016_dineutrino/"+NAME+".png");
    //c1->Draw(); 
    }
  }

}


void GetHisto(char CUT[1000], TTree *Tree, TH1F* & histo, const char *plot, int BIN, float MIN, float MAX){
  char input[50]; sprintf(input,"%s>>h(%i,%f,%f)",plot,BIN,MIN,MAX);
  TH1F *temp = new TH1F("", "", BIN,MIN,MAX);
  if(Tree->Draw(input,CUT)){ Tree->Draw(input,CUT); TH1F* h=(TH1F*)gDirectory->Get("h"); histo = (TH1F*)h->Clone(); delete h; } else { histo = (TH1F*)temp->Clone(); }
  histo->SetDirectory(0);
  histo->SetName("histo");
  delete temp;
 }


void MakeHistos(char CUT[1000],const char *plot,int BIN,float MIN,float MAX,int JETSyst,
		TH1F* &data_func,TH1F* &background_func,TH1F* &ZToNuNu_1_func,TH1F* &ZToNuNu_2_func,TH1F* &ZToNuNu_3_func,TH1F* &ZToNuNu_4_func,TH1F* &ZToNuNu_5_func,TH1F* &ZToNuNu_6_func,TH1F* &ZToNuNu_7_func,
		TH1F* &QCD_1_func,TH1F* &QCD_2_func,TH1F* &QCD_3_func,TH1F* &QCD_4_func,TH1F* &QCD_5_func,TH1F* &QCD_6_func,TH1F* &QCD_7_func,
		TH1F* &WToLNu_1_func,TH1F* &WToLNu_2_func,TH1F* &WToLNu_3_func,TH1F* &WToLNu_4_func,TH1F* &WToLNu_5_func,TH1F* &WToLNu_6_func,TH1F* &WToLNu_7_func,
		TH1F* &TT_1_func,TH1F* &TT_2_func,TH1F* &ST_1_func,TH1F* &ST_2_func,TH1F* &ST_3_func,TH1F* &ST_4_func,
		TH1F* &ZZ1_func,TH1F* &ZZ2_func,TH1F* &ZZ3_func,TH1F* &WW1_func,TH1F* &WW2_func,TH1F* &WZ1_func,TH1F* &WZ2_func,TH1F* &WZ3_func, 
		TH1F* &ttW_func,TH1F* &ttZ_func,TH1F* &tZq_func,TH1F* &ZZ4_func,TH1F* &WZ4_func,
		TH1F* &tptzm0800lh_func,TH1F* &tptzm1200lh_func,TH1F* &tptzm1600lh_func,TH1F* &tptzm1700lh_func){
  TH1F *data; TH1F *tptzm0800lh; TH1F *tptzm1200lh; TH1F *tptzm1600lh; TH1F *tptzm1700lh; 
  TH1F *ZToNuNu_1; TH1F *ZToNuNu_2; TH1F *ZToNuNu_3; TH1F *ZToNuNu_4; TH1F *ZToNuNu_5; TH1F *ZToNuNu_6; TH1F *ZToNuNu_7; 
  TH1F *QCD_1; TH1F *QCD_2; TH1F *QCD_3; TH1F *QCD_4; TH1F *QCD_5; TH1F *QCD_6; TH1F *QCD_7; 
  TH1F *WToLNu_1; TH1F *WToLNu_2; TH1F *WToLNu_3; TH1F *WToLNu_4; TH1F *WToLNu_5; TH1F *WToLNu_6; TH1F *WToLNu_7;
  TH1F *TT_1; TH1F *TT_2; TH1F *ST_1; TH1F *ST_2; TH1F *ST_3; TH1F *ST_4; 
  TH1F *ZZ1; TH1F *ZZ2; TH1F *ZZ3; TH1F *WZ1; TH1F *WZ2; TH1F *WZ3; TH1F *WW1; TH1F *WW2; 
  TH1F *ttW; TH1F *ttZ; TH1F *tZq; TH1F *ZZ4; TH1F *WZ4;
   
 
  if(JETSyst==0){
    GetHisto(CUT, Tree01, data        ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree03, tptzm0800lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree07, tptzm1200lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree11, tptzm1600lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree12, tptzm1700lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree14, ZToNuNu_1   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree15, ZToNuNu_2   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree16, ZToNuNu_3   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree17, ZToNuNu_4   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree18, ZToNuNu_5   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree19, ZToNuNu_6   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree20, ZToNuNu_7   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree21, QCD_1      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree22, QCD_2      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree23, QCD_3      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree24, QCD_4      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree25, QCD_5      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree26, QCD_6      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree27, QCD_7      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree28, WToLNu_1   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree29, WToLNu_2   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree30, WToLNu_3   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree31, WToLNu_4   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree32, WToLNu_5   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree33, WToLNu_6   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree34, WToLNu_7   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree35, TT_1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree36, TT_2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree37, ST_1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree38, ST_2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree39, ST_3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree40, ST_4    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree41, ZZ1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree42, ZZ2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree43, ZZ3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree44, WW1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree45, WW2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree46, WZ1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree47, WZ2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree48, WZ3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree49, ttW    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree50, ttZ    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree51, tZq    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree52, ZZ4    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree53, WZ4    ,plot,BIN,MIN,MAX);
  } else if(JETSyst==1){
    GetHisto(CUT, Tree01_J1, data        ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree03_J1, tptzm0800lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree07_J1, tptzm1200lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree11_J1, tptzm1600lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree12_J1, tptzm1700lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree14_J1, ZToNuNu_1   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree15_J1, ZToNuNu_2   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree16_J1, ZToNuNu_3   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree17_J1, ZToNuNu_4   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree18_J1, ZToNuNu_5   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree19_J1, ZToNuNu_6   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree20_J1, ZToNuNu_7   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree21_J1, QCD_1      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree22_J1, QCD_2      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree23_J1, QCD_3      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree24_J1, QCD_4      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree25_J1, QCD_5      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree26_J1, QCD_6      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree27_J1, QCD_7      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree28_J1, WToLNu_1   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree29_J1, WToLNu_2   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree30_J1, WToLNu_3   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree31_J1, WToLNu_4   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree32_J1, WToLNu_5   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree33_J1, WToLNu_6   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree34_J1, WToLNu_7   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree35_J1, TT_1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree36_J1, TT_2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree37_J1, ST_1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree38_J1, ST_2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree39_J1, ST_3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree40_J1, ST_4    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree41_J1, ZZ1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree42_J1, ZZ2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree43_J1, ZZ3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree44_J1, WW1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree45_J1, WW2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree46_J1, WZ1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree47_J1, WZ2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree48_J1, WZ3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree49_J1, ttW    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree50_J1, ttZ    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree51_J1, tZq    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree52_J1, ZZ4    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree53_J1, WZ4    ,plot,BIN,MIN,MAX);
  }else if(JETSyst==2){
    GetHisto(CUT, Tree01_J2, data        ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree03_J2, tptzm0800lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree07_J2, tptzm1200lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree11_J2, tptzm1600lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree12_J2, tptzm1700lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree14_J2, ZToNuNu_1   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree15_J2, ZToNuNu_2   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree16_J2, ZToNuNu_3   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree17_J2, ZToNuNu_4   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree18_J2, ZToNuNu_5   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree19_J2, ZToNuNu_6   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree20_J2, ZToNuNu_7   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree21_J2, QCD_1      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree22_J2, QCD_2      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree23_J2, QCD_3      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree24_J2, QCD_4      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree25_J2, QCD_5      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree26_J2, QCD_6      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree27_J2, QCD_7      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree28_J2, WToLNu_1   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree29_J2, WToLNu_2   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree30_J2, WToLNu_3   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree31_J2, WToLNu_4   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree32_J2, WToLNu_5   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree33_J2, WToLNu_6   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree34_J2, WToLNu_7   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree35_J2, TT_1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree36_J2, TT_2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree37_J2, ST_1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree38_J2, ST_2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree39_J2, ST_3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree40_J2, ST_4    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree41_J2, ZZ1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree42_J2, ZZ2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree43_J2, ZZ3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree44_J2, WW1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree45_J2, WW2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree46_J2, WZ1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree47_J2, WZ2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree48_J2, WZ3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree49_J2, ttW    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree50_J2, ttZ    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree51_J2, tZq    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree52_J2, ZZ4    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree53_J2, WZ4    ,plot,BIN,MIN,MAX);
  }else if(JETSyst==3){
    GetHisto(CUT, Tree01_J3, data        ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree03_J3, tptzm0800lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree07_J3, tptzm1200lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree11_J3, tptzm1600lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree12_J3, tptzm1700lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree14_J3, ZToNuNu_1   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree15_J3, ZToNuNu_2   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree16_J3, ZToNuNu_3   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree17_J3, ZToNuNu_4   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree18_J3, ZToNuNu_5   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree19_J3, ZToNuNu_6   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree20_J3, ZToNuNu_7   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree21_J3, QCD_1      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree22_J3, QCD_2      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree23_J3, QCD_3      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree24_J3, QCD_4      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree25_J3, QCD_5      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree26_J3, QCD_6      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree27_J3, QCD_7      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree28_J3, WToLNu_1   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree29_J3, WToLNu_2   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree30_J3, WToLNu_3   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree31_J3, WToLNu_4   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree32_J3, WToLNu_5   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree33_J3, WToLNu_6   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree34_J3, WToLNu_7   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree35_J3, TT_1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree36_J3, TT_2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree37_J3, ST_1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree38_J3, ST_2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree39_J3, ST_3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree40_J3, ST_4    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree41_J3, ZZ1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree42_J3, ZZ2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree43_J3, ZZ3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree44_J3, WW1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree45_J3, WW2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree46_J3, WZ1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree47_J3, WZ2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree48_J3, WZ3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree49_J3, ttW    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree50_J3, ttZ    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree51_J3, tZq    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree52_J3, ZZ4    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree53_J3, WZ4    ,plot,BIN,MIN,MAX);
  }else if(JETSyst==4){
    GetHisto(CUT, Tree01_J4, data        ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree03_J4, tptzm0800lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree07_J4, tptzm1200lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree11_J4, tptzm1600lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree12_J4, tptzm1700lh ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree14_J4, ZToNuNu_1   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree15_J4, ZToNuNu_2   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree16_J4, ZToNuNu_3   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree17_J4, ZToNuNu_4   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree18_J4, ZToNuNu_5   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree19_J4, ZToNuNu_6   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree20_J4, ZToNuNu_7   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree21_J4, QCD_1      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree22_J4, QCD_2      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree23_J4, QCD_3      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree24_J4, QCD_4      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree25_J4, QCD_5      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree26_J4, QCD_6      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree27_J4, QCD_7      ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree28_J4, WToLNu_1   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree29_J4, WToLNu_2   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree30_J4, WToLNu_3   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree31_J4, WToLNu_4   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree32_J4, WToLNu_5   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree33_J4, WToLNu_6   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree34_J4, WToLNu_7   ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree35_J4, TT_1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree36_J4, TT_2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree37_J4, ST_1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree38_J4, ST_2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree39_J4, ST_3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree40_J4, ST_4    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree41_J4, ZZ1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree42_J4, ZZ2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree43_J4, ZZ3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree44_J4, WW1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree45_J4, WW2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree46_J4, WZ1    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree47_J4, WZ2    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree48_J4, WZ3    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree49_J4, ttW    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree50_J4, ttZ    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree51_J4, tZq    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree52_J4, ZZ4    ,plot,BIN,MIN,MAX);
    GetHisto(CUT, Tree53_J4, WZ4    ,plot,BIN,MIN,MAX);
  }
  TH1F *background = new TH1F("","",data->GetNbinsX(),data->GetXaxis()->GetXmin(),data->GetXaxis()->GetXmax());
  for(int j=1; j<data->GetNbinsX()+1; j++){
    if(tptzm0800lh->GetBinContent(j)>0){tptzm0800lh->SetBinError(j,sqrt(w0800*w0800*tptzm0800lh->GetBinContent(j)));}else{tptzm0800lh->SetBinError(j,0);}
    if(tptzm1200lh->GetBinContent(j)>0){tptzm1200lh->SetBinError(j,sqrt(w1200*w1200*tptzm1200lh->GetBinContent(j)));}else{tptzm1200lh->SetBinError(j,0);}
    if(tptzm1600lh->GetBinContent(j)>0){tptzm1600lh->SetBinError(j,sqrt(w1600*w1600*tptzm1600lh->GetBinContent(j)));}else{tptzm1600lh->SetBinError(j,0);}
    if(tptzm1700lh->GetBinContent(j)>0){tptzm1700lh->SetBinError(j,sqrt(w1700*w1700*tptzm1700lh->GetBinContent(j)));}else{tptzm1700lh->SetBinError(j,0);}
    if(ZToNuNu_1 ->GetBinContent(j)>0){ZToNuNu_1 ->SetBinError(j,sqrt(w01*w01*ZToNuNu_1 ->GetBinContent(j)));}else{ZToNuNu_1 ->SetBinError(j,0);}//w01);}
    if(ZToNuNu_2 ->GetBinContent(j)>0){ZToNuNu_2 ->SetBinError(j,sqrt(w02*w02*ZToNuNu_2 ->GetBinContent(j)));}else{ZToNuNu_2 ->SetBinError(j,0);}//w02);}
    if(ZToNuNu_3 ->GetBinContent(j)>0){ZToNuNu_3 ->SetBinError(j,sqrt(w03*w03*ZToNuNu_3 ->GetBinContent(j)));}else{ZToNuNu_3 ->SetBinError(j,0);}//w03);}
    if(ZToNuNu_4 ->GetBinContent(j)>0){ZToNuNu_4 ->SetBinError(j,sqrt(w04*w04*ZToNuNu_4 ->GetBinContent(j)));}else{ZToNuNu_4 ->SetBinError(j,0);}//w04);}
    if(ZToNuNu_5 ->GetBinContent(j)>0){ZToNuNu_5 ->SetBinError(j,sqrt(w05*w05*ZToNuNu_5 ->GetBinContent(j)));}else{ZToNuNu_5 ->SetBinError(j,0);}//w05);}
    if(ZToNuNu_6 ->GetBinContent(j)>0){ZToNuNu_6 ->SetBinError(j,sqrt(w06*w06*ZToNuNu_6 ->GetBinContent(j)));}else{ZToNuNu_6 ->SetBinError(j,0);}//w06);}
    if(ZToNuNu_7 ->GetBinContent(j)>0){ZToNuNu_7 ->SetBinError(j,sqrt(w07*w07*ZToNuNu_7 ->GetBinContent(j)));}else{ZToNuNu_7 ->SetBinError(j,0);}//w07);}
    if(QCD_1->GetBinContent(j)>0){QCD_1 ->SetBinError(j,sqrt(w08*w08*QCD_1 ->GetBinContent(j)));}else{QCD_1 ->SetBinError(j,0);}//w08);}
    if(QCD_2->GetBinContent(j)>0){QCD_2 ->SetBinError(j,sqrt(w09*w09*QCD_2 ->GetBinContent(j)));}else{QCD_2 ->SetBinError(j,0);}//w09);}
    if(QCD_3->GetBinContent(j)>0){QCD_3 ->SetBinError(j,sqrt(w10*w10*QCD_3 ->GetBinContent(j)));}else{QCD_3 ->SetBinError(j,0);}//w10);}
    if(QCD_4->GetBinContent(j)>0){QCD_4 ->SetBinError(j,sqrt(w11*w11*QCD_4 ->GetBinContent(j)));}else{QCD_4 ->SetBinError(j,0);}//w11);}
    if(QCD_5->GetBinContent(j)>0){QCD_5 ->SetBinError(j,sqrt(w12*w12*QCD_5 ->GetBinContent(j)));}else{QCD_5 ->SetBinError(j,0);}//w12);}
    if(QCD_6->GetBinContent(j)>0){QCD_6 ->SetBinError(j,sqrt(w13*w13*QCD_6 ->GetBinContent(j)));}else{QCD_6 ->SetBinError(j,0);}//w13);}
    if(QCD_7->GetBinContent(j)>0){QCD_7 ->SetBinError(j,sqrt(w14*w14*QCD_7 ->GetBinContent(j)));}else{QCD_7 ->SetBinError(j,0);}//w14);}
    if(WToLNu_1->GetBinContent(j)>0){WToLNu_1->SetBinError(j,sqrt(w15*w15*WToLNu_1->GetBinContent(j)));}else{WToLNu_1->SetBinError(j,0);}//w15);}
    if(WToLNu_2->GetBinContent(j)>0){WToLNu_2->SetBinError(j,sqrt(w16*w16*WToLNu_2->GetBinContent(j)));}else{WToLNu_2->SetBinError(j,0);}//w16);}
    if(WToLNu_3->GetBinContent(j)>0){WToLNu_3->SetBinError(j,sqrt(w17*w17*WToLNu_3->GetBinContent(j)));}else{WToLNu_3->SetBinError(j,0);}//w17);}
    if(WToLNu_4->GetBinContent(j)>0){WToLNu_4->SetBinError(j,sqrt(w18*w18*WToLNu_4->GetBinContent(j)));}else{WToLNu_4->SetBinError(j,0);}//w18);}
    if(WToLNu_5->GetBinContent(j)>0){WToLNu_5->SetBinError(j,sqrt(w19*w19*WToLNu_5->GetBinContent(j)));}else{WToLNu_5->SetBinError(j,0);}//w19);}
    if(WToLNu_6->GetBinContent(j)>0){WToLNu_6->SetBinError(j,sqrt(w20*w20*WToLNu_6->GetBinContent(j)));}else{WToLNu_6->SetBinError(j,0);}//w20);}
    if(WToLNu_7->GetBinContent(j)>0){WToLNu_7->SetBinError(j,sqrt(w21*w21*WToLNu_7->GetBinContent(j)));}else{WToLNu_7->SetBinError(j,0);}//w21);}
    if(TT_1->GetBinContent(j)>0){TT_1->SetBinError(j,sqrt(w22*w22*TT_1->GetBinContent(j)));}else{TT_1->SetBinError(j,0);}//w22);}
    if(TT_2->GetBinContent(j)>0){TT_2->SetBinError(j,sqrt(w23*w23*TT_2->GetBinContent(j)));}else{TT_2->SetBinError(j,0);}//w23);}
    if(ST_1->GetBinContent(j)>0){ST_1->SetBinError(j,sqrt(w24*w24*ST_1->GetBinContent(j)));}else{ST_1->SetBinError(j,0);}//w24);}
    if(ST_2->GetBinContent(j)>0){ST_2->SetBinError(j,sqrt(w25*w25*ST_2->GetBinContent(j)));}else{ST_2->SetBinError(j,0);}//w25);}
    if(ST_3->GetBinContent(j)>0){ST_3->SetBinError(j,sqrt(w26*w26*ST_3->GetBinContent(j)));}else{ST_3->SetBinError(j,0);}//w26);}
    if(ST_4->GetBinContent(j)>0){ST_4->SetBinError(j,sqrt(w27*w27*ST_4->GetBinContent(j)));}else{ST_4->SetBinError(j,0);}//w27);}
    if(ZZ1->GetBinContent(j)>0){ZZ1->SetBinError(j,sqrt(w28*w28*ZZ1->GetBinContent(j)));}else{ZZ1->SetBinError(j,0);}//w28);}
    if(ZZ2->GetBinContent(j)>0){ZZ2->SetBinError(j,sqrt(w29*w29*ZZ2->GetBinContent(j)));}else{ZZ2->SetBinError(j,0);}//w29);}
    if(ZZ3->GetBinContent(j)>0){ZZ3->SetBinError(j,sqrt(w30*w30*ZZ3->GetBinContent(j)));}else{ZZ3->SetBinError(j,0);}//w30);}
    if(WW1->GetBinContent(j)>0){WW1->SetBinError(j,sqrt(w31*w31*WW1->GetBinContent(j)));}else{WW1->SetBinError(j,0);}//w31);}
    if(WW2->GetBinContent(j)>0){WW2->SetBinError(j,sqrt(w32*w32*WW2->GetBinContent(j)));}else{WW2->SetBinError(j,0);}//w32);}
    if(WZ1->GetBinContent(j)>0){WZ1->SetBinError(j,sqrt(w33*w33*WZ1->GetBinContent(j)));}else{WZ1->SetBinError(j,0);}//w33);}
    if(WZ2->GetBinContent(j)>0){WZ2->SetBinError(j,sqrt(w34*w34*WZ2->GetBinContent(j)));}else{WZ2->SetBinError(j,0);}//w34);}
    if(WZ3->GetBinContent(j)>0){WZ3->SetBinError(j,sqrt(w35*w35*WZ3->GetBinContent(j)));}else{WZ3->SetBinError(j,0);}//w35);}
    if(ttW->GetBinContent(j)>0){ttW->SetBinError(j,sqrt(w36*w36*ttW->GetBinContent(j)));}else{ttW->SetBinError(j,0);}//w36);}
    if(ttZ->GetBinContent(j)>0){ttZ->SetBinError(j,sqrt(w37*w37*ttZ->GetBinContent(j)));}else{ttZ->SetBinError(j,0);}//w37);}
    if(tZq->GetBinContent(j)>0){tZq->SetBinError(j,sqrt(w38*w38*tZq->GetBinContent(j)));}else{tZq->SetBinError(j,0);}//w38);}
    if(ZZ4->GetBinContent(j)>0){ZZ4->SetBinError(j,sqrt(w39*w39*ZZ4->GetBinContent(j)));}else{ZZ4->SetBinError(j,0);}//w39);}
    if(WZ4->GetBinContent(j)>0){WZ4->SetBinError(j,sqrt(w40*w40*WZ4->GetBinContent(j)));}else{WZ4->SetBinError(j,0);}//w40);}

    float err00 = data->GetBinError(j)*data->GetBinError(j);
    float err01 = ZToNuNu_1->GetBinError(j)*ZToNuNu_1->GetBinError(j) + ZToNuNu_2->GetBinError(j)*ZToNuNu_2->GetBinError(j) + ZToNuNu_3->GetBinError(j)*ZToNuNu_3->GetBinError(j) + ZToNuNu_4->GetBinError(j)*ZToNuNu_4->GetBinError(j) + ZToNuNu_5->GetBinError(j)*ZToNuNu_5->GetBinError(j) + ZToNuNu_6->GetBinError(j)*ZToNuNu_6->GetBinError(j) + ZToNuNu_7->GetBinError(j)*ZToNuNu_7->GetBinError(j);
    float err02 = QCD_1->GetBinError(j)*QCD_1->GetBinError(j) + QCD_2->GetBinError(j)*QCD_2->GetBinError(j) + QCD_3->GetBinError(j)*QCD_3->GetBinError(j) + QCD_4->GetBinError(j)*QCD_4->GetBinError(j) + QCD_5->GetBinError(j)*QCD_5->GetBinError(j) + QCD_6->GetBinError(j)*QCD_6->GetBinError(j) + QCD_7->GetBinError(j)*QCD_7->GetBinError(j);
    float err03 = WToLNu_1->GetBinError(j)*WToLNu_1->GetBinError(j)+WToLNu_2->GetBinError(j)*WToLNu_2->GetBinError(j)+WToLNu_3->GetBinError(j)*WToLNu_3->GetBinError(j)+WToLNu_4->GetBinError(j)*WToLNu_4->GetBinError(j)+WToLNu_5->GetBinError(j)*WToLNu_5->GetBinError(j)+WToLNu_6->GetBinError(j)*WToLNu_6->GetBinError(j)+WToLNu_7->GetBinError(j)*WToLNu_7->GetBinError(j);
    float err04 = TT_1->GetBinError(j)*TT_1->GetBinError(j)+TT_2->GetBinError(j)*TT_2->GetBinError(j);
    float err05 = ST_1->GetBinError(j)*ST_1->GetBinError(j) + ST_2->GetBinError(j)*ST_2->GetBinError(j)+ ST_3->GetBinError(j)*ST_3->GetBinError(j)+ ST_4->GetBinError(j)*ST_4->GetBinError(j);
    float err06 = ZZ1->GetBinError(j)*ZZ1->GetBinError(j) + ZZ2->GetBinError(j)*ZZ2->GetBinError(j) + ZZ3->GetBinError(j)*ZZ3->GetBinError(j) + ZZ4->GetBinError(j)*ZZ4->GetBinError(j) + WW1->GetBinError(j)*WW1->GetBinError(j) + WW2->GetBinError(j)*WW2->GetBinError(j) + WZ1->GetBinError(j)*WZ1->GetBinError(j) + WZ2->GetBinError(j)*WZ2->GetBinError(j) + WZ3->GetBinError(j)*WZ3->GetBinError(j)+ WZ4->GetBinError(j)*WZ4->GetBinError(j); 
    float err07 = ttW->GetBinError(j)*ttW->GetBinError(j) + ttZ->GetBinError(j)*ttZ->GetBinError(j) + tZq->GetBinError(j)*tZq->GetBinError(j);
    background->SetBinError(j,sqrt(err01+err02+err03+err04+err05+err06+err07));

    tptzm0800lh->SetBinContent(j,w0800*tptzm0800lh->GetBinContent(j));
    tptzm1200lh->SetBinContent(j,w1200*tptzm1200lh->GetBinContent(j));
    tptzm1600lh->SetBinContent(j,w1600*tptzm1600lh->GetBinContent(j));
    tptzm1700lh->SetBinContent(j,w1700*tptzm1700lh->GetBinContent(j));
    ZToNuNu_1->SetBinContent(j,w01*ZToNuNu_1->GetBinContent(j));
    ZToNuNu_2->SetBinContent(j,w02*ZToNuNu_2->GetBinContent(j));
    ZToNuNu_3->SetBinContent(j,w03*ZToNuNu_3->GetBinContent(j));
    ZToNuNu_4->SetBinContent(j,w04*ZToNuNu_4->GetBinContent(j));
    ZToNuNu_5->SetBinContent(j,w05*ZToNuNu_5->GetBinContent(j));
    ZToNuNu_6->SetBinContent(j,w06*ZToNuNu_6->GetBinContent(j));
    ZToNuNu_7->SetBinContent(j,w07*ZToNuNu_7->GetBinContent(j));
    QCD_1->SetBinContent(j,w08*QCD_1->GetBinContent(j));
    QCD_2->SetBinContent(j,w09*QCD_2->GetBinContent(j));
    QCD_3->SetBinContent(j,w10*QCD_3->GetBinContent(j));
    QCD_4->SetBinContent(j,w11*QCD_4->GetBinContent(j));
    QCD_5->SetBinContent(j,w12*QCD_5->GetBinContent(j));
    QCD_6->SetBinContent(j,w13*QCD_6->GetBinContent(j));
    QCD_7->SetBinContent(j,w14*QCD_7->GetBinContent(j));
    WToLNu_1->SetBinContent(j,w15*WToLNu_1->GetBinContent(j));
    WToLNu_2->SetBinContent(j,w16*WToLNu_2->GetBinContent(j));
    WToLNu_3->SetBinContent(j,w17*WToLNu_3->GetBinContent(j));
    WToLNu_4->SetBinContent(j,w18*WToLNu_4->GetBinContent(j));
    WToLNu_5->SetBinContent(j,w19*WToLNu_5->GetBinContent(j));
    WToLNu_6->SetBinContent(j,w20*WToLNu_6->GetBinContent(j));
    WToLNu_7->SetBinContent(j,w21*WToLNu_7->GetBinContent(j));
    TT_1->SetBinContent(j,w22*TT_1->GetBinContent(j));
    TT_2->SetBinContent(j,w23*TT_2->GetBinContent(j));
    ST_1->SetBinContent(j,w24*ST_1->GetBinContent(j));
    ST_2->SetBinContent(j,w25*ST_2->GetBinContent(j));
    ST_3->SetBinContent(j,w26*ST_3->GetBinContent(j));
    ST_4->SetBinContent(j,w27*ST_4->GetBinContent(j));
    ZZ1->SetBinContent(j,w28*ZZ1->GetBinContent(j));
    ZZ2->SetBinContent(j,w29*ZZ2->GetBinContent(j));
    ZZ3->SetBinContent(j,w30*ZZ3->GetBinContent(j));
    WW1->SetBinContent(j,w31*WW1->GetBinContent(j));
    WW2->SetBinContent(j,w32*WW2->GetBinContent(j));
    WZ1->SetBinContent(j,w33*WZ1->GetBinContent(j));
    WZ2->SetBinContent(j,w34*WZ2->GetBinContent(j));
    WZ3->SetBinContent(j,w35*WZ3->GetBinContent(j));
    ttW->SetBinContent(j,w36*ttW->GetBinContent(j));
    ttZ->SetBinContent(j,w37*ttZ->GetBinContent(j));
    tZq->SetBinContent(j,w38*tZq->GetBinContent(j));
    ZZ4->SetBinContent(j,w39*ZZ4->GetBinContent(j));
    WZ4->SetBinContent(j,w40*WZ4->GetBinContent(j));

    float DATA = data->GetBinContent(j);
    float bkg0 = ZToNuNu_1->GetBinContent(j) + ZToNuNu_2->GetBinContent(j) + ZToNuNu_3->GetBinContent(j) + ZToNuNu_4->GetBinContent(j) + ZToNuNu_5->GetBinContent(j) + ZToNuNu_6->GetBinContent(j) + ZToNuNu_7->GetBinContent(j);
    float bkg1 = QCD_1->GetBinContent(j) + QCD_2->GetBinContent(j) + QCD_3->GetBinContent(j) + QCD_4->GetBinContent(j) + QCD_5->GetBinContent(j) + QCD_6->GetBinContent(j) + QCD_7->GetBinContent(j);
    float bkg2 = WToLNu_1->GetBinContent(j) + WToLNu_2->GetBinContent(j) + WToLNu_3->GetBinContent(j) + WToLNu_4->GetBinContent(j) + WToLNu_5->GetBinContent(j) + WToLNu_6->GetBinContent(j)+ WToLNu_7->GetBinContent(j);
    float bkg3 = TT_1->GetBinContent(j) + TT_2->GetBinContent(j);
    float bkg4 = ST_1 ->GetBinContent(j) + ST_2 ->GetBinContent(j) + ST_3 ->GetBinContent(j) + ST_4 ->GetBinContent(j);
    float bkg5 = ZZ1->GetBinContent(j)+ZZ2->GetBinContent(j)+ZZ3->GetBinContent(j)+ZZ4->GetBinContent(j)+WW1->GetBinContent(j)+WW2->GetBinContent(j)+WZ1->GetBinContent(j)+WZ2->GetBinContent(j)+WZ3->GetBinContent(j)+WZ4->GetBinContent(j);
    float bkg6 = ttW->GetBinContent(j) + ttZ->GetBinContent(j) + tZq->GetBinContent(j);

    background->SetBinContent(j,bkg0+bkg1+bkg2+bkg3+bkg4+bkg5+bkg6);
    
  }

  background_func  = (TH1F*)background ->Clone(); 
  data_func        = (TH1F*)data       ->Clone(); 
  tptzm0800lh_func = (TH1F*)tptzm0800lh->Clone(); 
  tptzm1200lh_func = (TH1F*)tptzm1200lh->Clone(); 
  tptzm1600lh_func = (TH1F*)tptzm1600lh->Clone(); 
  tptzm1700lh_func = (TH1F*)tptzm1700lh->Clone(); 
  ZToNuNu_1_func   = (TH1F*)ZToNuNu_1->Clone(); 
  ZToNuNu_2_func   = (TH1F*)ZToNuNu_2->Clone(); 
  ZToNuNu_3_func   = (TH1F*)ZToNuNu_3->Clone();  
  ZToNuNu_4_func   = (TH1F*)ZToNuNu_4->Clone(); 
  ZToNuNu_5_func   = (TH1F*)ZToNuNu_5->Clone();
  ZToNuNu_6_func   = (TH1F*)ZToNuNu_6->Clone();
  ZToNuNu_7_func   = (TH1F*)ZToNuNu_7->Clone();
  QCD_1_func = (TH1F*)QCD_1->Clone();    
  QCD_2_func = (TH1F*)QCD_2->Clone();
  QCD_3_func = (TH1F*)QCD_3->Clone(); 
  QCD_4_func = (TH1F*)QCD_4->Clone();
  QCD_5_func = (TH1F*)QCD_5->Clone();  
  QCD_6_func = (TH1F*)QCD_6->Clone(); 
  QCD_7_func = (TH1F*)QCD_7->Clone();
  WToLNu_1_func = (TH1F*)WToLNu_1->Clone(); 
  WToLNu_2_func = (TH1F*)WToLNu_2->Clone();
  WToLNu_3_func = (TH1F*)WToLNu_3->Clone();
  WToLNu_4_func = (TH1F*)WToLNu_4->Clone();
  WToLNu_5_func = (TH1F*)WToLNu_5->Clone();
  WToLNu_6_func = (TH1F*)WToLNu_6->Clone();
  WToLNu_7_func = (TH1F*)WToLNu_7->Clone();
  TT_1_func = (TH1F*)TT_1->Clone();  
  TT_2_func = (TH1F*)TT_2->Clone();
  ST_1_func = (TH1F*)ST_1->Clone();    
  ST_2_func = (TH1F*)ST_2->Clone();    
  ST_3_func = (TH1F*)ST_3->Clone();    
  ST_4_func = (TH1F*)ST_4->Clone();    
  ZZ1_func  = (TH1F*)ZZ1->Clone(); 
  ZZ2_func  = (TH1F*)ZZ2->Clone();
  ZZ3_func  = (TH1F*)ZZ3->Clone(); 
  ZZ4_func  = (TH1F*)ZZ4->Clone(); 
  WW1_func  = (TH1F*)WW1->Clone(); 
  WW2_func  = (TH1F*)WW2->Clone(); 
  WZ1_func  = (TH1F*)WZ1->Clone(); 
  WZ2_func  = (TH1F*)WZ2->Clone();
  WZ3_func  = (TH1F*)WZ3->Clone();
  WZ4_func  = (TH1F*)WZ4->Clone();
  ttW_func  = (TH1F*)ttW->Clone();
  ttZ_func  = (TH1F*)ttZ->Clone();
  tZq_func  = (TH1F*)tZq->Clone();

  delete data; delete background; delete ZToNuNu_1; delete ZToNuNu_2; delete ZToNuNu_3; delete ZToNuNu_4;  delete ZToNuNu_5;  delete ZToNuNu_6;  delete ZToNuNu_7;  
  delete QCD_1; delete QCD_2; delete QCD_3; delete QCD_4; delete QCD_5; delete QCD_6; delete QCD_7; 
  delete WToLNu_1; delete WToLNu_2; delete WToLNu_3; delete WToLNu_4; delete WToLNu_5; delete WToLNu_6; delete WToLNu_7; 
  delete TT_1; delete TT_2; delete ST_1; delete ST_2;  delete ST_3; delete ST_4;  
  delete WW1; delete WW2; delete WZ1; delete WZ2; delete WZ3; delete WZ4; delete ZZ1; delete ZZ2;  delete ZZ3; delete ZZ4;
  delete ttW; delete ttZ; delete tZq;
}


void MakeHistoErrors(int m, TH1F* &histo_SR, TH1F* histo_P1, TH1F* histo_P2, TH1F* histo_F1, TH1F* histo_F2, TH1F* histo_B1, TH1F* histo_B2, TH1F* histo_Z1, TH1F* histo_Z2, TH1F* histo_W1, TH1F* histo_W2, TH1F* histo_T1, TH1F* histo_T2, TH1F* histo_J1, TH1F* histo_J2, TH1F* histo_J3, TH1F* histo_J4, TH1F* histo_qcd1, TH1F* histo_qcd2, TH1F* histo_pdf1, TH1F* histo_pdf2, TH1F* histo_TR1, TH1F* histo_TR2){
  float ErrMc = histo_SR->GetBinError(m); 
  float ErrLU = 0.026*histo_SR->GetBinContent(m);
  float ErrPU = max(fabs(histo_SR->GetBinContent(m)-histo_P1->GetBinContent(m)),fabs(histo_SR->GetBinContent(m)-histo_P2->GetBinContent(m)));
  float ErrFO = max(fabs(histo_SR->GetBinContent(m)-histo_F1->GetBinContent(m)),fabs(histo_SR->GetBinContent(m)-histo_F2->GetBinContent(m))); 
  float ErrBT = max(fabs(histo_SR->GetBinContent(m)-histo_B1->GetBinContent(m)),fabs(histo_SR->GetBinContent(m)-histo_B2->GetBinContent(m))); 
  float ErrTR = max(fabs(histo_SR->GetBinContent(m)-histo_TR1->GetBinContent(m)),fabs(histo_SR->GetBinContent(m)-histo_TR2->GetBinContent(m)));
  float ErrZJ = max(fabs(histo_SR->GetBinContent(m)-histo_Z1->GetBinContent(m)),fabs(histo_SR->GetBinContent(m)-histo_Z2->GetBinContent(m))); 
  float ErrWJ = max(fabs(histo_SR->GetBinContent(m)-histo_W1->GetBinContent(m)),fabs(histo_SR->GetBinContent(m)-histo_W2->GetBinContent(m)));
  float ErrTT = max(fabs(histo_SR->GetBinContent(m)-histo_T1->GetBinContent(m)),fabs(histo_SR->GetBinContent(m)-histo_T2->GetBinContent(m)));
  float ErrJS = max(fabs(histo_SR->GetBinContent(m)-histo_J1->GetBinContent(m)),fabs(histo_SR->GetBinContent(m)-histo_J2->GetBinContent(m))); 
  float ErrJR = max(fabs(histo_SR->GetBinContent(m)-histo_J3->GetBinContent(m)),fabs(histo_SR->GetBinContent(m)-histo_J4->GetBinContent(m))); 
  float ErrQCD= max(fabs(histo_SR->GetBinContent(m)-histo_qcd1->GetBinContent(m)),fabs(histo_SR->GetBinContent(m)-histo_qcd2->GetBinContent(m)));
  float ErrPDF= max(fabs(histo_SR->GetBinContent(m)-histo_pdf1->GetBinContent(m)),fabs(histo_SR->GetBinContent(m)-histo_pdf2->GetBinContent(m)));
  float TOTAL = sqrt(ErrMc*ErrMc + ErrLU*ErrLU +  ErrPU*ErrPU + ErrFO*ErrFO + ErrBT*ErrBT +ErrTR*ErrTR + ErrZJ*ErrZJ + ErrWJ*ErrWJ + ErrTT*ErrTT+ ErrJS*ErrJS + ErrJR*ErrJR + ErrQCD*ErrQCD + ErrPDF*ErrPDF);
  histo_SR ->SetBinError(m,TOTAL);
}

void CloneHistos(){
	data_P1 = (TH1F*)data_SR->Clone(); tptzm0800lh_P1 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_P1 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_P1 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_P1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_P1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_P1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_P1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_P1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_P1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_P1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_P1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_P1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_P1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_P1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_P1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_P1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_P1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_P1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_P1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_P1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_P1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_P1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_P1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_P1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_P1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_P1 = (TH1F*)TT_1_SR->Clone(); TT_2_P1 = (TH1F*)TT_2_SR->Clone(); ST_1_P1 = (TH1F*)ST_1_SR->Clone(); ST_2_P1 = (TH1F*)ST_2_SR->Clone();  ST_3_P1 = (TH1F*)ST_3_SR->Clone();  ST_4_P1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_P1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_P1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_P1 = (TH1F*)ZZ3_SR->Clone(); WW1_P1 = (TH1F*)WW1_SR->Clone(); WW2_P1 = (TH1F*)WW2_SR->Clone(); WZ1_P1 = (TH1F*)WZ1_SR->Clone(); WZ2_P1 = (TH1F*)WZ2_SR->Clone();  WZ3_P1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_P1 = (TH1F*)background_SR->Clone();
	ttW_P1 = (TH1F*)ttW_SR->Clone(); ttZ_P1 = (TH1F*)ttZ_SR->Clone(); tZq_P1 = (TH1F*)tZq_SR->Clone(); ZZ4_P1 = (TH1F*)ZZ4_SR->Clone(); WZ4_P1 = (TH1F*)WZ4_SR->Clone();

	data_P2 = (TH1F*)data_SR->Clone(); tptzm0800lh_P2 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_P2 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_P2 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_P2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_P2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_P2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_P2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_P2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_P2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_P2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_P2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_P2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_P2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_P2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_P2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_P2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_P2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_P2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_P2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_P2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_P2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_P2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_P2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_P2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_P2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_P2 = (TH1F*)TT_1_SR->Clone(); TT_2_P2 = (TH1F*)TT_2_SR->Clone(); ST_1_P2 = (TH1F*)ST_1_SR->Clone(); ST_2_P2 = (TH1F*)ST_2_SR->Clone();  ST_3_P2 = (TH1F*)ST_3_SR->Clone();  ST_4_P2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_P2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_P2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_P2 = (TH1F*)ZZ3_SR->Clone(); WW1_P2 = (TH1F*)WW1_SR->Clone();  WW2_P2 = (TH1F*)WW2_SR->Clone(); WZ1_P2 = (TH1F*)WZ1_SR->Clone(); WZ2_P2 = (TH1F*)WZ2_SR->Clone();  WZ3_P2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_P2 = (TH1F*)background_SR->Clone();
	ttW_P2 = (TH1F*)ttW_SR->Clone(); ttZ_P2 = (TH1F*)ttZ_SR->Clone(); tZq_P2 = (TH1F*)tZq_SR->Clone(); ZZ4_P2 = (TH1F*)ZZ4_SR->Clone(); WZ4_P2 = (TH1F*)WZ4_SR->Clone();

	data_F1 = (TH1F*)data_SR->Clone(); tptzm0800lh_F1 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_F1 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_F1 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_F1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_F1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_F1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_F1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_F1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_F1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_F1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_F1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_F1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_F1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_F1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_F1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_F1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_F1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_F1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_F1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_F1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_F1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_F1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_F1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_F1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_F1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_F1 = (TH1F*)TT_1_SR->Clone(); TT_2_F1 = (TH1F*)TT_2_SR->Clone(); ST_1_F1 = (TH1F*)ST_1_SR->Clone(); ST_2_F1 = (TH1F*)ST_2_SR->Clone();  ST_3_F1 = (TH1F*)ST_3_SR->Clone();  ST_4_F1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_F1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_F1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_F1 = (TH1F*)ZZ3_SR->Clone(); WW1_F1 = (TH1F*)WW1_SR->Clone();  WW2_F1 = (TH1F*)WW2_SR->Clone(); WZ1_F1 = (TH1F*)WZ1_SR->Clone(); WZ2_F1 = (TH1F*)WZ2_SR->Clone();  WZ3_F1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_F1 = (TH1F*)background_SR->Clone();
	ttW_F1 = (TH1F*)ttW_SR->Clone(); ttZ_F1 = (TH1F*)ttZ_SR->Clone(); tZq_F1 = (TH1F*)tZq_SR->Clone(); ZZ4_F1 = (TH1F*)ZZ4_SR->Clone(); WZ4_F1 = (TH1F*)WZ4_SR->Clone();

	data_F2 = (TH1F*)data_SR->Clone(); tptzm0800lh_F2 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_F2 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_F2 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_F2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_F2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_F2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_F2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_F2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_F2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_F2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_F2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_F2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_F2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_F2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_F2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_F2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_F2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_F2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_F2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_F2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_F2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_F2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_F2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_F2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_F2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_F2 = (TH1F*)TT_1_SR->Clone(); TT_2_F2 = (TH1F*)TT_2_SR->Clone(); ST_1_F2 = (TH1F*)ST_1_SR->Clone(); ST_2_F2 = (TH1F*)ST_2_SR->Clone();  ST_3_F2 = (TH1F*)ST_3_SR->Clone();  ST_4_F2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_F2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_F2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_F2 = (TH1F*)ZZ3_SR->Clone(); WW1_F2 = (TH1F*)WW1_SR->Clone();  WW2_F2 = (TH1F*)WW2_SR->Clone(); WZ1_F2 = (TH1F*)WZ1_SR->Clone(); WZ2_F2 = (TH1F*)WZ2_SR->Clone();  WZ3_F2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_F2 = (TH1F*)background_SR->Clone();
	ttW_F2 = (TH1F*)ttW_SR->Clone(); ttZ_F2 = (TH1F*)ttZ_SR->Clone(); tZq_F2 = (TH1F*)tZq_SR->Clone(); ZZ4_F2 = (TH1F*)ZZ4_SR->Clone(); WZ4_F2 = (TH1F*)WZ4_SR->Clone();

	data_B1 = (TH1F*)data_SR->Clone(); tptzm0800lh_B1 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_B1 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_B1 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_B1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_B1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_B1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_B1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_B1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_B1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_B1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_B1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_B1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_B1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_B1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_B1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_B1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_B1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_B1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_B1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_B1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_B1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_B1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_B1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_B1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_B1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_B1 = (TH1F*)TT_1_SR->Clone(); TT_2_B1 = (TH1F*)TT_2_SR->Clone(); ST_1_B1 = (TH1F*)ST_1_SR->Clone(); ST_2_B1 = (TH1F*)ST_2_SR->Clone();  ST_3_B1 = (TH1F*)ST_3_SR->Clone();  ST_4_B1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_B1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_B1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_B1 = (TH1F*)ZZ3_SR->Clone(); WW1_B1 = (TH1F*)WW1_SR->Clone();  WW2_B1 = (TH1F*)WW2_SR->Clone(); WZ1_B1 = (TH1F*)WZ1_SR->Clone(); WZ2_B1 = (TH1F*)WZ2_SR->Clone();  WZ3_B1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_B1 = (TH1F*)background_SR->Clone();
	ttW_B1 = (TH1F*)ttW_SR->Clone(); ttZ_B1 = (TH1F*)ttZ_SR->Clone(); tZq_B1 = (TH1F*)tZq_SR->Clone(); ZZ4_B1 = (TH1F*)ZZ4_SR->Clone(); WZ4_B1 = (TH1F*)WZ4_SR->Clone();

	data_B2 = (TH1F*)data_SR->Clone(); tptzm0800lh_B2 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_B2 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_B2 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_B2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_B2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_B2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_B2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_B2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_B2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_B2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_B2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_B2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_B2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_B2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_B2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_B2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_B2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_B2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_B2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_B2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_B2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_B2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_B2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_B2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_B2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_B2 = (TH1F*)TT_1_SR->Clone(); TT_2_B2 = (TH1F*)TT_2_SR->Clone(); ST_1_B2 = (TH1F*)ST_1_SR->Clone(); ST_2_B2 = (TH1F*)ST_2_SR->Clone();  ST_3_B2 = (TH1F*)ST_3_SR->Clone();  ST_4_B2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_B2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_B2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_B2 = (TH1F*)ZZ3_SR->Clone(); WW1_B2 = (TH1F*)WW1_SR->Clone();  WW2_B2 = (TH1F*)WW2_SR->Clone(); WZ1_B2 = (TH1F*)WZ1_SR->Clone(); WZ2_B2 = (TH1F*)WZ2_SR->Clone();  WZ3_B2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_B2 = (TH1F*)background_SR->Clone();
	ttW_B2 = (TH1F*)ttW_SR->Clone(); ttZ_B2 = (TH1F*)ttZ_SR->Clone(); tZq_B2 = (TH1F*)tZq_SR->Clone(); ZZ4_B2 = (TH1F*)ZZ4_SR->Clone(); WZ4_B2 = (TH1F*)WZ4_SR->Clone();

	data_Z1 = (TH1F*)data_SR->Clone(); tptzm0800lh_Z1 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_Z1 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_Z1 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_Z1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_Z1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_Z1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_Z1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_Z1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_Z1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_Z1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_Z1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_Z1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_Z1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_Z1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_Z1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_Z1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_Z1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_Z1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_Z1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_Z1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_Z1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_Z1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_Z1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_Z1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_Z1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_Z1 = (TH1F*)TT_1_SR->Clone(); TT_2_Z1 = (TH1F*)TT_2_SR->Clone(); ST_1_Z1 = (TH1F*)ST_1_SR->Clone(); ST_2_Z1 = (TH1F*)ST_2_SR->Clone();  ST_3_Z1 = (TH1F*)ST_3_SR->Clone();  ST_4_Z1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_Z1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_Z1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_Z1 = (TH1F*)ZZ3_SR->Clone(); WW1_Z1 = (TH1F*)WW1_SR->Clone();  WW2_Z1 = (TH1F*)WW2_SR->Clone(); WZ1_Z1 = (TH1F*)WZ1_SR->Clone(); WZ2_Z1 = (TH1F*)WZ2_SR->Clone();  WZ3_Z1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_Z1 = (TH1F*)background_SR->Clone();
	ttW_Z1 = (TH1F*)ttW_SR->Clone(); ttZ_Z1 = (TH1F*)ttZ_SR->Clone(); tZq_Z1 = (TH1F*)tZq_SR->Clone(); ZZ4_Z1 = (TH1F*)ZZ4_SR->Clone(); WZ4_Z1 = (TH1F*)WZ4_SR->Clone();

	data_Z2 = (TH1F*)data_SR->Clone(); tptzm0800lh_Z2 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_Z2 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_Z2 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_Z2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_Z2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_Z2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_Z2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_Z2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_Z2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_Z2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_Z2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_Z2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_Z2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_Z2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_Z2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_Z2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_Z2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_Z2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_Z2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_Z2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_Z2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_Z2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_Z2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_Z2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_Z2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_Z2 = (TH1F*)TT_1_SR->Clone(); TT_2_Z2 = (TH1F*)TT_2_SR->Clone(); ST_1_Z2 = (TH1F*)ST_1_SR->Clone(); ST_2_Z2 = (TH1F*)ST_2_SR->Clone();  ST_3_Z2 = (TH1F*)ST_3_SR->Clone();  ST_4_Z2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_Z2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_Z2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_Z2 = (TH1F*)ZZ3_SR->Clone(); WW1_Z2 = (TH1F*)WW1_SR->Clone();  WW2_Z2 = (TH1F*)WW2_SR->Clone(); WZ1_Z2 = (TH1F*)WZ1_SR->Clone(); WZ2_Z2 = (TH1F*)WZ2_SR->Clone();  WZ3_Z2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_Z2 = (TH1F*)background_SR->Clone();
	ttW_Z2 = (TH1F*)ttW_SR->Clone(); ttZ_Z2 = (TH1F*)ttZ_SR->Clone(); tZq_Z2 = (TH1F*)tZq_SR->Clone(); ZZ4_Z2 = (TH1F*)ZZ4_SR->Clone(); WZ4_Z2 = (TH1F*)WZ4_SR->Clone();

	data_W1 = (TH1F*)data_SR->Clone(); tptzm0800lh_W1 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_W1 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_W1 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_W1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_W1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_W1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_W1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_W1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_W1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_W1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_W1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_W1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_W1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_W1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_W1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_W1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_W1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_W1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_W1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_W1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_W1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_W1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_W1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_W1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_W1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_W1 = (TH1F*)TT_1_SR->Clone(); TT_2_W1 = (TH1F*)TT_2_SR->Clone(); ST_1_W1 = (TH1F*)ST_1_SR->Clone(); ST_2_W1 = (TH1F*)ST_2_SR->Clone();  ST_3_W1 = (TH1F*)ST_3_SR->Clone();  ST_4_W1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_W1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_W1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_W1 = (TH1F*)ZZ3_SR->Clone(); WW1_W1 = (TH1F*)WW1_SR->Clone();  WW2_W1 = (TH1F*)WW2_SR->Clone(); WZ1_W1 = (TH1F*)WZ1_SR->Clone(); WZ2_W1 = (TH1F*)WZ2_SR->Clone();  WZ3_W1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_W1 = (TH1F*)background_SR->Clone();
	ttW_W1 = (TH1F*)ttW_SR->Clone(); ttZ_W1 = (TH1F*)ttZ_SR->Clone(); tZq_W1 = (TH1F*)tZq_SR->Clone(); ZZ4_W1 = (TH1F*)ZZ4_SR->Clone(); WZ4_W1 = (TH1F*)WZ4_SR->Clone();

	data_W2 = (TH1F*)data_SR->Clone(); tptzm0800lh_W2 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_W2 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_W2 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_W2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_W2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_W2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_W2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_W2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_W2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_W2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_W2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_W2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_W2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_W2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_W2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_W2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_W2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_W2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_W2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_W2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_W2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_W2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_W2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_W2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_W2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_W2 = (TH1F*)TT_1_SR->Clone(); TT_2_W2 = (TH1F*)TT_2_SR->Clone(); ST_1_W2 = (TH1F*)ST_1_SR->Clone(); ST_2_W2 = (TH1F*)ST_2_SR->Clone();  ST_3_W2 = (TH1F*)ST_3_SR->Clone();  ST_4_W2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_W2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_W2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_W2 = (TH1F*)ZZ3_SR->Clone(); WW1_W2 = (TH1F*)WW1_SR->Clone();  WW2_W2 = (TH1F*)WW2_SR->Clone(); WZ1_W2 = (TH1F*)WZ1_SR->Clone(); WZ2_W2 = (TH1F*)WZ2_SR->Clone();  WZ3_W2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_W2 = (TH1F*)background_SR->Clone();
	ttW_W2 = (TH1F*)ttW_SR->Clone(); ttZ_W2 = (TH1F*)ttZ_SR->Clone(); tZq_W2 = (TH1F*)tZq_SR->Clone(); ZZ4_W2 = (TH1F*)ZZ4_SR->Clone(); WZ4_W2 = (TH1F*)WZ4_SR->Clone();

	data_T1 = (TH1F*)data_SR->Clone(); tptzm0800lh_T1 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_T1 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_T1 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_T1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_T1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_T1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_T1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_T1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_T1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_T1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_T1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_T1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_T1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_T1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_T1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_T1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_T1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_T1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_T1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_T1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_T1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_T1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_T1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_T1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_T1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_T1 = (TH1F*)TT_1_SR->Clone(); TT_2_T1 = (TH1F*)TT_2_SR->Clone(); ST_1_T1 = (TH1F*)ST_1_SR->Clone(); ST_2_T1 = (TH1F*)ST_2_SR->Clone();  ST_3_T1 = (TH1F*)ST_3_SR->Clone();  ST_4_T1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_T1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_T1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_T1 = (TH1F*)ZZ3_SR->Clone(); WW1_T1 = (TH1F*)WW1_SR->Clone();  WW2_T1 = (TH1F*)WW2_SR->Clone(); WZ1_T1 = (TH1F*)WZ1_SR->Clone(); WZ2_T1 = (TH1F*)WZ2_SR->Clone();  WZ3_T1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_T1 = (TH1F*)background_SR->Clone();
	ttW_T1 = (TH1F*)ttW_SR->Clone(); ttZ_T1 = (TH1F*)ttZ_SR->Clone(); tZq_T1 = (TH1F*)tZq_SR->Clone(); ZZ4_T1 = (TH1F*)ZZ4_SR->Clone(); WZ4_T1 = (TH1F*)WZ4_SR->Clone();

	data_T2 = (TH1F*)data_SR->Clone(); tptzm0800lh_T2 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_T2 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_T2 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_T2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_T2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_T2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_T2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_T2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_T2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_T2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_T2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_T2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_T2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_T2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_T2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_T2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_T2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_T2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_T2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_T2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_T2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_T2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_T2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_T2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_T2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_T2 = (TH1F*)TT_1_SR->Clone(); TT_2_T2 = (TH1F*)TT_2_SR->Clone(); ST_1_T2 = (TH1F*)ST_1_SR->Clone(); ST_2_T2 = (TH1F*)ST_2_SR->Clone();  ST_3_T2 = (TH1F*)ST_3_SR->Clone();  ST_4_T2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_T2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_T2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_T2 = (TH1F*)ZZ3_SR->Clone(); WW1_T2 = (TH1F*)WW1_SR->Clone();  WW2_T2 = (TH1F*)WW2_SR->Clone(); WZ1_T2 = (TH1F*)WZ1_SR->Clone(); WZ2_T2 = (TH1F*)WZ2_SR->Clone();  WZ3_T2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_T2 = (TH1F*)background_SR->Clone();
	ttW_T2 = (TH1F*)ttW_SR->Clone(); ttZ_T2 = (TH1F*)ttZ_SR->Clone(); tZq_T2 = (TH1F*)tZq_SR->Clone(); ZZ4_T2 = (TH1F*)ZZ4_SR->Clone(); WZ4_T2 = (TH1F*)WZ4_SR->Clone();
	
	data_J1 = (TH1F*)data_SR->Clone(); tptzm0800lh_J1 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_J1 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_J1 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_J1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_J1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_J1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_J1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_J1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_J1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_J1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_J1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_J1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_J1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_J1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_J1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_J1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_J1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_J1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_J1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_J1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_J1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_J1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_J1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_J1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_J1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_J1 = (TH1F*)TT_1_SR->Clone(); TT_2_J1 = (TH1F*)TT_2_SR->Clone(); ST_1_J1 = (TH1F*)ST_1_SR->Clone(); ST_2_J1 = (TH1F*)ST_2_SR->Clone();  ST_3_J1 = (TH1F*)ST_3_SR->Clone();  ST_4_J1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_J1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_J1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_J1 = (TH1F*)ZZ3_SR->Clone(); WW1_J1 = (TH1F*)WW1_SR->Clone();  WW2_J1 = (TH1F*)WW2_SR->Clone(); WZ1_J1 = (TH1F*)WZ1_SR->Clone(); WZ2_J1 = (TH1F*)WZ2_SR->Clone();  WZ3_J1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_J1 = (TH1F*)background_SR->Clone();
	ttW_J1 = (TH1F*)ttW_SR->Clone(); ttZ_J1 = (TH1F*)ttZ_SR->Clone(); tZq_J1 = (TH1F*)tZq_SR->Clone(); ZZ4_J1 = (TH1F*)ZZ4_SR->Clone(); WZ4_J1 = (TH1F*)WZ4_SR->Clone();

	data_J2 = (TH1F*)data_SR->Clone(); tptzm0800lh_J2 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_J2 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_J2 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_J2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_J2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_J2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_J2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_J2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_J2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_J2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_J2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_J2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_J2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_J2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_J2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_J2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_J2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_J2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_J2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_J2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_J2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_J2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_J2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_J2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_J2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_J2 = (TH1F*)TT_1_SR->Clone(); TT_2_J2 = (TH1F*)TT_2_SR->Clone(); ST_1_J2 = (TH1F*)ST_1_SR->Clone(); ST_2_J2 = (TH1F*)ST_2_SR->Clone();  ST_3_J2 = (TH1F*)ST_3_SR->Clone();  ST_4_J2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_J2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_J2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_J2 = (TH1F*)ZZ3_SR->Clone(); WW1_J2 = (TH1F*)WW1_SR->Clone();  WW2_J2 = (TH1F*)WW2_SR->Clone(); WZ1_J2 = (TH1F*)WZ1_SR->Clone(); WZ2_J2 = (TH1F*)WZ2_SR->Clone();  WZ3_J2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_J2 = (TH1F*)background_SR->Clone();
	ttW_J2 = (TH1F*)ttW_SR->Clone(); ttZ_J2 = (TH1F*)ttZ_SR->Clone(); tZq_J2 = (TH1F*)tZq_SR->Clone(); ZZ4_J2 = (TH1F*)ZZ4_SR->Clone(); WZ4_J2 = (TH1F*)WZ4_SR->Clone();

	data_J3 = (TH1F*)data_SR->Clone(); tptzm0800lh_J3 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_J3 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_J3 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_J3 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_J3 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_J3 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_J3 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_J3 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_J3 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_J3 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_J3 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_J3 = (TH1F*)QCD_1_SR->Clone(); QCD_2_J3 = (TH1F*)QCD_2_SR->Clone();  QCD_3_J3 = (TH1F*)QCD_3_SR->Clone();  QCD_4_J3 = (TH1F*)QCD_4_SR->Clone();  QCD_5_J3 = (TH1F*)QCD_5_SR->Clone();  QCD_6_J3 = (TH1F*)QCD_6_SR->Clone();  QCD_7_J3 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_J3 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_J3 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_J3 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_J3 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_J3 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_J3 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_J3 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_J3 = (TH1F*)TT_1_SR->Clone(); TT_2_J3 = (TH1F*)TT_2_SR->Clone(); ST_1_J3 = (TH1F*)ST_1_SR->Clone(); ST_2_J3 = (TH1F*)ST_2_SR->Clone();  ST_3_J3 = (TH1F*)ST_3_SR->Clone();  ST_4_J3 = (TH1F*)ST_4_SR->Clone();
	ZZ1_J3 = (TH1F*)ZZ1_SR->Clone(); ZZ2_J3 = (TH1F*)ZZ2_SR->Clone(); ZZ3_J3 = (TH1F*)ZZ3_SR->Clone(); WW1_J3 = (TH1F*)WW1_SR->Clone();  WW2_J3 = (TH1F*)WW2_SR->Clone(); WZ1_J3 = (TH1F*)WZ1_SR->Clone(); WZ2_J3 = (TH1F*)WZ2_SR->Clone();  WZ3_J3 = (TH1F*)WZ3_SR->Clone(); TH1F *background_J3 = (TH1F*)background_SR->Clone();
	ttW_J3 = (TH1F*)ttW_SR->Clone(); ttZ_J3 = (TH1F*)ttZ_SR->Clone(); tZq_J3 = (TH1F*)tZq_SR->Clone(); ZZ4_J3 = (TH1F*)ZZ4_SR->Clone(); WZ4_J3 = (TH1F*)WZ4_SR->Clone();

	data_J4 = (TH1F*)data_SR->Clone(); tptzm0800lh_J4 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_J4 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_J4 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_J4 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_J4 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_J4 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_J4 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_J4 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_J4 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_J4 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_J4 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_J4 = (TH1F*)QCD_1_SR->Clone(); QCD_2_J4 = (TH1F*)QCD_2_SR->Clone();  QCD_3_J4 = (TH1F*)QCD_3_SR->Clone();  QCD_4_J4 = (TH1F*)QCD_4_SR->Clone();  QCD_5_J4 = (TH1F*)QCD_5_SR->Clone();  QCD_6_J4 = (TH1F*)QCD_6_SR->Clone();  QCD_7_J4 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_J4 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_J4 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_J4 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_J4 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_J4 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_J4 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_J4 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_J4 = (TH1F*)TT_1_SR->Clone(); TT_2_J4 = (TH1F*)TT_2_SR->Clone(); ST_1_J4 = (TH1F*)ST_1_SR->Clone(); ST_2_J4 = (TH1F*)ST_2_SR->Clone();  ST_3_J4 = (TH1F*)ST_3_SR->Clone();  ST_4_J4 = (TH1F*)ST_4_SR->Clone();
	ZZ1_J4 = (TH1F*)ZZ1_SR->Clone(); ZZ2_J4 = (TH1F*)ZZ2_SR->Clone(); ZZ3_J4 = (TH1F*)ZZ3_SR->Clone(); WW1_J4 = (TH1F*)WW1_SR->Clone();  WW2_J4 = (TH1F*)WW2_SR->Clone(); WZ1_J4 = (TH1F*)WZ1_SR->Clone(); WZ2_J4 = (TH1F*)WZ2_SR->Clone();  WZ3_J4 = (TH1F*)WZ3_SR->Clone(); TH1F *background_J4 = (TH1F*)background_SR->Clone();
    ttW_J4 = (TH1F*)ttW_SR->Clone(); ttZ_J4 = (TH1F*)ttZ_SR->Clone(); tZq_J4 = (TH1F*)tZq_SR->Clone(); ZZ4_J4 = (TH1F*)ZZ4_SR->Clone(); WZ4_J4 = (TH1F*)WZ4_SR->Clone();

	data_qcd1 = (TH1F*)data_SR->Clone(); tptzm0800lh_qcd1 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_qcd1 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_qcd1 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_qcd1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_qcd1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_qcd1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_qcd1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_qcd1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_qcd1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_qcd1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_qcd1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_qcd1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_qcd1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_qcd1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_qcd1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_qcd1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_qcd1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_qcd1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_qcd1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_qcd1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_qcd1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_qcd1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_qcd1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_qcd1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_qcd1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_qcd1 = (TH1F*)TT_1_SR->Clone(); TT_2_qcd1 = (TH1F*)TT_2_SR->Clone(); ST_1_qcd1 = (TH1F*)ST_1_SR->Clone(); ST_2_qcd1 = (TH1F*)ST_2_SR->Clone();  ST_3_qcd1 = (TH1F*)ST_3_SR->Clone();  ST_4_qcd1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_qcd1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_qcd1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_qcd1 = (TH1F*)ZZ3_SR->Clone(); WW1_qcd1 = (TH1F*)WW1_SR->Clone(); WW2_qcd1 = (TH1F*)WW2_SR->Clone(); WZ1_qcd1 = (TH1F*)WZ1_SR->Clone(); WZ2_qcd1 = (TH1F*)WZ2_SR->Clone();  WZ3_qcd1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_qcd1 = (TH1F*)background_SR->Clone();
	ttW_qcd1 = (TH1F*)ttW_SR->Clone(); ttZ_qcd1 = (TH1F*)ttZ_SR->Clone(); tZq_qcd1 = (TH1F*)tZq_SR->Clone(); ZZ4_qcd1 = (TH1F*)ZZ4_SR->Clone(); WZ4_qcd1 = (TH1F*)WZ4_SR->Clone();

	data_qcd2 = (TH1F*)data_SR->Clone(); tptzm0800lh_qcd2 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_qcd2 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_qcd2 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_qcd2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_qcd2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_qcd2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_qcd2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_qcd2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_qcd2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_qcd2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_qcd2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_qcd2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_qcd2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_qcd2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_qcd2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_qcd2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_qcd2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_qcd2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_qcd2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_qcd2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_qcd2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_qcd2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_qcd2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_qcd2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_qcd2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_qcd2 = (TH1F*)TT_1_SR->Clone(); TT_2_qcd2 = (TH1F*)TT_2_SR->Clone(); ST_1_qcd2 = (TH1F*)ST_1_SR->Clone(); ST_2_qcd2 = (TH1F*)ST_2_SR->Clone();  ST_3_qcd2 = (TH1F*)ST_3_SR->Clone();  ST_4_qcd2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_qcd2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_qcd2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_qcd2 = (TH1F*)ZZ3_SR->Clone(); WW1_qcd2 = (TH1F*)WW1_SR->Clone(); WW2_qcd2 = (TH1F*)WW2_SR->Clone(); WZ1_qcd2 = (TH1F*)WZ1_SR->Clone(); WZ2_qcd2 = (TH1F*)WZ2_SR->Clone();  WZ3_qcd2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_qcd2 = (TH1F*)background_SR->Clone();
	ttW_qcd2 = (TH1F*)ttW_SR->Clone(); ttZ_qcd2 = (TH1F*)ttZ_SR->Clone(); tZq_qcd2 = (TH1F*)tZq_SR->Clone(); ZZ4_qcd2 = (TH1F*)ZZ4_SR->Clone(); WZ4_qcd2 = (TH1F*)WZ4_SR->Clone();


	data_pdf1 = (TH1F*)data_SR->Clone(); tptzm0800lh_pdf1 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_pdf1 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_pdf1 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_pdf1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_pdf1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_pdf1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_pdf1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_pdf1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_pdf1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_pdf1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_pdf1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_pdf1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_pdf1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_pdf1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_pdf1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_pdf1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_pdf1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_pdf1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_pdf1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_pdf1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_pdf1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_pdf1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_pdf1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_pdf1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_pdf1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_pdf1 = (TH1F*)TT_1_SR->Clone(); TT_2_pdf1 = (TH1F*)TT_2_SR->Clone(); ST_1_pdf1 = (TH1F*)ST_1_SR->Clone(); ST_2_pdf1 = (TH1F*)ST_2_SR->Clone();  ST_3_pdf1 = (TH1F*)ST_3_SR->Clone();  ST_4_pdf1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_pdf1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_pdf1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_pdf1 = (TH1F*)ZZ3_SR->Clone(); WW1_pdf1 = (TH1F*)WW1_SR->Clone(); WW2_pdf1 = (TH1F*)WW2_SR->Clone(); WZ1_pdf1 = (TH1F*)WZ1_SR->Clone(); WZ2_pdf1 = (TH1F*)WZ2_SR->Clone();  WZ3_pdf1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_pdf1 = (TH1F*)background_SR->Clone();
	ttW_pdf1 = (TH1F*)ttW_SR->Clone(); ttZ_pdf1 = (TH1F*)ttZ_SR->Clone(); tZq_pdf1 = (TH1F*)tZq_SR->Clone(); ZZ4_pdf1 = (TH1F*)ZZ4_SR->Clone(); WZ4_pdf1 = (TH1F*)WZ4_SR->Clone();


	data_pdf2 = (TH1F*)data_SR->Clone(); tptzm0800lh_pdf2 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_pdf2 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_pdf2 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_pdf2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_pdf2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_pdf2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_pdf2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_pdf2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_pdf2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_pdf2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_pdf2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_pdf2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_pdf2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_pdf2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_pdf2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_pdf2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_pdf2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_pdf2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_pdf2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_pdf2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_pdf2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_pdf2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_pdf2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_pdf2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_pdf2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_pdf2 = (TH1F*)TT_1_SR->Clone(); TT_2_pdf2 = (TH1F*)TT_2_SR->Clone(); ST_1_pdf2 = (TH1F*)ST_1_SR->Clone(); ST_2_pdf2 = (TH1F*)ST_2_SR->Clone();  ST_3_pdf2 = (TH1F*)ST_3_SR->Clone();  ST_4_pdf2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_pdf2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_pdf2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_pdf2 = (TH1F*)ZZ3_SR->Clone(); WW1_pdf2 = (TH1F*)WW1_SR->Clone(); WW2_pdf2 = (TH1F*)WW2_SR->Clone(); WZ1_pdf2 = (TH1F*)WZ1_SR->Clone(); WZ2_pdf2 = (TH1F*)WZ2_SR->Clone();  WZ3_pdf2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_pdf2 = (TH1F*)background_SR->Clone();
	ttW_pdf2 = (TH1F*)ttW_SR->Clone(); ttZ_pdf2 = (TH1F*)ttZ_SR->Clone(); tZq_pdf2 = (TH1F*)tZq_SR->Clone(); ZZ4_pdf2 = (TH1F*)ZZ4_SR->Clone(); WZ4_pdf2 = (TH1F*)WZ4_SR->Clone();


	data_TR1 = (TH1F*)data_SR->Clone(); tptzm0800lh_TR1 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_TR1 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_TR1 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_TR1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_TR1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_TR1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_TR1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_TR1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_TR1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_TR1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_TR1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_TR1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_TR1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_TR1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_TR1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_TR1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_TR1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_TR1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_TR1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_TR1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_TR1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_TR1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_TR1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_TR1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_TR1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_TR1 = (TH1F*)TT_1_SR->Clone(); TT_2_TR1 = (TH1F*)TT_2_SR->Clone(); ST_1_TR1 = (TH1F*)ST_1_SR->Clone(); ST_2_TR1 = (TH1F*)ST_2_SR->Clone();  ST_3_TR1 = (TH1F*)ST_3_SR->Clone();  ST_4_TR1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_TR1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_TR1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_TR1 = (TH1F*)ZZ3_SR->Clone(); WW1_TR1 = (TH1F*)WW1_SR->Clone(); WW2_TR1 = (TH1F*)WW2_SR->Clone(); WZ1_TR1 = (TH1F*)WZ1_SR->Clone(); WZ2_TR1 = (TH1F*)WZ2_SR->Clone();  WZ3_TR1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_TR1 = (TH1F*)background_SR->Clone();
	ttW_TR1 = (TH1F*)ttW_SR->Clone(); ttZ_TR1 = (TH1F*)ttZ_SR->Clone(); tZq_TR1 = (TH1F*)tZq_SR->Clone(); ZZ4_TR1 = (TH1F*)ZZ4_SR->Clone(); WZ4_TR1 = (TH1F*)WZ4_SR->Clone();


	data_TR2 = (TH1F*)data_SR->Clone(); tptzm0800lh_TR2 = (TH1F*)tptzm0800lh_SR->Clone(); tptzm1200lh_TR2 = (TH1F*)tptzm1200lh_SR->Clone(); tptzm1600lh_TR2 = (TH1F*)tptzm1600lh_SR->Clone(); tptzm1700lh_TR2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_TR2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_TR2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_TR2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_TR2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_TR2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_TR2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_TR2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_TR2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_TR2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_TR2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_TR2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_TR2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_TR2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_TR2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_TR2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_TR2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_TR2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_TR2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_TR2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_TR2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_TR2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_TR2 = (TH1F*)TT_1_SR->Clone(); TT_2_TR2 = (TH1F*)TT_2_SR->Clone(); ST_1_TR2 = (TH1F*)ST_1_SR->Clone(); ST_2_TR2 = (TH1F*)ST_2_SR->Clone();  ST_3_TR2 = (TH1F*)ST_3_SR->Clone();  ST_4_TR2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_TR2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_TR2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_TR2 = (TH1F*)ZZ3_SR->Clone(); WW1_TR2 = (TH1F*)WW1_SR->Clone(); WW2_TR2 = (TH1F*)WW2_SR->Clone(); WZ1_TR2 = (TH1F*)WZ1_SR->Clone(); WZ2_TR2 = (TH1F*)WZ2_SR->Clone();  WZ3_TR2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_TR2 = (TH1F*)background_SR->Clone();
	ttW_TR2 = (TH1F*)ttW_SR->Clone(); ttZ_TR2 = (TH1F*)ttZ_SR->Clone(); tZq_TR2 = (TH1F*)tZq_SR->Clone(); ZZ4_TR2 = (TH1F*)ZZ4_SR->Clone(); WZ4_TR2 = (TH1F*)WZ4_SR->Clone();

}
