#include "PlotterPreselection_PlayWithMC.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1F.h"
#include "THStack.h"
#include "TSystem.h"
#include "TLatex.h"
#include "TLegend.h"
#include <iostream>
#include "TROOT.h"
#include "TMath.h"
void PlotterPreselection_PlayWithMC(){ 
  gROOT->Reset();
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1,0);
  gStyle->SetTitleX(0.5); //title X location 
  gStyle->SetTitleY(0.96); //title Y location 
  gStyle->SetPaintTextFormat(".2f");
  gErrorIgnoreLevel = kError;//?
  using namespace std; 

//  bool SYST = false;

  vector<TString> name;                vector<int> bin;      vector<float> Min;      vector<float> Max;     vector<TString> axis;
//name is plots we want to show   
 
 name.push_back("InvariantMassJets");      bin.push_back(100);     Min.push_back(0);    Max.push_back(4000);    axis.push_back("Invariant mass of jets");
  name.push_back("Centrality");      bin.push_back(100);     Min.push_back(0);    Max.push_back(4);    axis.push_back("Centrality");
 //// name.push_back("Aplanarity");      bin.push_back(100);     Min.push_back(-0.5);    Max.push_back(2000);    axis.push_back("Aplanarity");
  name.push_back("LeadingJetPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("Leading Jet Pt");
 name.push_back("SecondJetPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1500);    axis.push_back("Second Jet Pt");
  name.push_back("ThirdJetPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(500);    axis.push_back("Third Jet Pt");
  name.push_back("FourthJetPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(300);    axis.push_back("Fourth Jet Pt");
  name.push_back("FifthJetPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(200);    axis.push_back("Fifth Jet Pt");
  name.push_back("SixthJetPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(130);    axis.push_back("Sixth Jet Pt");
  name.push_back("SeventhJetPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(90);    axis.push_back("Seventh Jet Pt");
  name.push_back("EighthJetPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(80);    axis.push_back("Eighth Jet Pt");
  name.push_back("LeadingBJetPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(900);    axis.push_back("Leading B Jet Pt");
  name.push_back("SecondBJetPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(500);    axis.push_back("Second B Jet Pt");
  name.push_back("HTDividedByMET");      bin.push_back(100);     Min.push_back(0);    Max.push_back(40);    axis.push_back("HT / MET");
  name.push_back("MHTDividedByMET");      bin.push_back(100);     Min.push_back(0);    Max.push_back(50);    axis.push_back("MHT / MET");
  name.push_back("NighthJetPt");      bin.push_back(100);     Min.push_back(20);    Max.push_back(70);    axis.push_back("Nighth Jet Pt");
 name.push_back("TenthJetPt");      bin.push_back(100);     Min.push_back(20);    Max.push_back(70);    axis.push_back("Tenth Jet Pt");
  name.push_back("ThirdBJetPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(180);    axis.push_back("Third B Jet Pt");
  name.push_back("FourthBJetPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(150);    axis.push_back("Fourth B Jet Pt");
// // name.push_back("FifthBJetPt");      bin.push_back(100);     Min.push_back(-100);    Max.push_back(800);    axis.push_back("Fifth B Jet Pt");
  name.push_back("MinDeltaRJets");      bin.push_back(100);     Min.push_back(0);    Max.push_back(4);    axis.push_back("Min delta R of Jets");
  name.push_back("MaxDeltaRJets");      bin.push_back(100);     Min.push_back(2);    Max.push_back(6);    axis.push_back("Maximum delta R of Jets");
  name.push_back("MinDeltaRBJets");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5);    axis.push_back("Min delta R of B Jets");
  name.push_back("MaxDeltaRBJets");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5);    axis.push_back("Maximum delta R of B Jets");
  name.push_back("NumSelJets");      bin.push_back(12);     Min.push_back(0);    Max.push_back(13);    axis.push_back("Number of jets");
  name.push_back("NumSelBJetsM");      bin.push_back(6);     Min.push_back(0);    Max.push_back(6);    axis.push_back("Number of medium b jets");
 name.push_back("NVertices"); bin.push_back(80);     Min.push_back(0);    Max.push_back(100);    axis.push_back("Number of vertices");
 name.push_back("HT"); bin.push_back(100);     Min.push_back(0);    Max.push_back(2200);    axis.push_back("HT pt[GeV]");
 name.push_back("MHT"); bin.push_back(100);     Min.push_back(0);    Max.push_back(500);    axis.push_back("MHT pt[GeV]");
 name.push_back("Met_pt");  bin.push_back(100);     Min.push_back(0);    Max.push_back(400);   axis.push_back("Met pt[GeV] ");
// name.push_back("Met_phi"); bin.push_back(8);     Min.push_back(-4);   Max.push_back(-4);      axis.push_back("Met #phi");
 
 // name.push_back("");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("");
 // name.push_back("");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("");
//  name.push_back("Sphericity");      bin.push_back(11);     Min.push_back(-0.5);    Max.push_back(10.5);    axis.push_back("Sphericity");
//  name.push_back("");      bin.push_back(11);     Min.push_back(-0.5);    Max.push_back(10.5);    axis.push_back("");
//  name.push_back("");      bin.push_back(11);     Min.push_back(-0.5);    Max.push_back(10.5);    axis.push_back("");
//
//
  /*}}}*/
  
  for(int i=0; i<name.size(); i++){
	  const char *plot = name[i];
	  char CUT[1000]; char CUTpre[1000]; char CUTpup1[1000]; char CUTpup2[1000]; char CUTbta1[1000]; char CUTbta2[1000];  char CUTfor1[1000]; char CUTfor2[1000]; char CUTwje1[1000]; char CUTwje2[1000]; char CUTzje1[1000];  char CUTzje2[1000];  char CUTttb1[1000];  char CUTttb2[1000];  char CUTfir1[1000];  char CUTfir2[1000];char CUTqcd1[1000]; char CUTqcd2[1000];char CUTpdf1[1000]; char CUTpdf2[1000]; char CUTtri1[1000]; char CUTtri2[1000];
	  //apply selection cuts here
      //
      //
    sprintf(CUTpre,"((NumSelLeps==0))");/*{{{*/
// 	sprintf(CUTpre,"((category0==1)&&(Jet1ResolvedPt>0)&&(Jet2ResolvedPt>0)&&(Jet3ResolvedPt>0)&&(MinDeltaPhiJetMet>0.6)&&(TransverseMassMetTop>500)&&(NumSelLeps==0)&&(TopPt>250)&&(MostForwardJetEta<4&&MostForwardJetEta>-4)&&((MostForwardJetEta<-3.139&&MostForwardJetEta>-4||(MostForwardJetEta>-2.65&&MostForwardJetEta<2.65)||MostForwardJetEta>3.139)||(MostForwardJetPt>50)))");
    //sprintf(CUT,    "PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *w_ZToNuNu  *w_WToLNu  *w_ttbar *%s",CUTpre);
	///did we multiply PUWeight etc or not?	//I think yes
	sprintf(CUT,    "PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig      *%s",CUTpre);
	//what is the difinition of PUweight and w_Btag ? what's their value?
//	sprintf(CUTpup1,"PUWeightUP  *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
//	sprintf(CUTpup2,"PUWeightDOWN*w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
//	sprintf(CUTfir1,"PUWeight    *w_Btag    *genWeight  *prefiringweightup  *w_Trig  *%s",CUTpre);
//	sprintf(CUTfir2,"PUWeight    *w_Btag    *genWeight  *prefiringweightdown*w_Trig  *%s",CUTpre);
//	sprintf(CUTbta1,"PUWeight    *w_BtagUp  *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
//	sprintf(CUTbta2,"PUWeight    *w_BtagDown*genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
//	sprintf(CUTzje1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
//	//?CUTzje1 are the same as CUT, what is the point?
//	sprintf(CUTzje2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
//	sprintf(CUTwje1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
//	sprintf(CUTwje2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
//	sprintf(CUTttb1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
//	sprintf(CUTttb2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_Trig  *%s",CUTpre);
//	sprintf(CUTqcd1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_QCDUp    *%s",CUTpre);
//	sprintf(CUTqcd2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_QCDDown  *%s",CUTpre);
//	sprintf(CUTpdf1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_PDFUp    *%s",CUTpre);
//	sprintf(CUTpdf2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_PDFDown  *%s",CUTpre);
//	sprintf(CUTtri1,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_TrigUp   *%s",CUTpre);
//	sprintf(CUTtri2,"PUWeight    *w_Btag    *genWeight  *prefiringweight    *w_TrigDown *%s",CUTpre);
        /*}}}*/
	MakeHistos(CUT,plot,bin[i],Min[i],Max[i],0,/*data_SR,*/background_SR,QCD_HT200to300_SR,     QCD_HT300to500_SR,   QCD_HT500to700_SR,   QCD_HT700to1000_SR,   QCD_HT1000to1500_SR,   QCD_HT1500to2000_SR,   	   QCD_HT2000toIn_SR,   TTJets_SR,   TTWJets_SR,   TTZ_SR,  TT_SR, TTTT_SR );//682

//what is SYST and why we do it this way?   
	//how do we exactly include SYST in our histograms?
/*	if(SYST){//15
		MakeHistos(CUTpup1,plot,bin[i],Min[i],Max[i],0,data_P1,background_P1,ZToNuNu_1_P1,ZToNuNu_2_P1,ZToNuNu_3_P1,ZToNuNu_4_P1,ZToNuNu_5_P1,ZToNuNu_6_P1,ZToNuNu_7_P1,
				QCD_1_P1,QCD_2_P1,QCD_3_P1,QCD_4_P1,QCD_5_P1,QCD_6_P1,QCD_7_P1,WToLNu_1_P1,WToLNu_2_P1,WToLNu_3_P1,WToLNu_4_P1,WToLNu_5_P1,WToLNu_6_P1,WToLNu_7_P1,
				 TT_1_P1,TT_2_P1,ST_1_P1,ST_2_P1,ST_3_P1,ST_4_P1,ZZ1_P1,ZZ2_P1,ZZ3_P1,WW1_P1,WW2_P1,WZ1_P1,WZ2_P1,WZ3_P1,ttW_P1,ttZ_P1,tZq_P1,ZZ4_P1,WZ4_P1,
				 tptzm0700lh_P1,tptzm0900lh_P1,tptzm1400lh_P1,tptzm1700lh_P1);

		MakeHistos(CUTpup2,plot,bin[i],Min[i],Max[i],0,data_P2,background_P2,ZToNuNu_1_P2,ZToNuNu_2_P2,ZToNuNu_3_P2,ZToNuNu_4_P2,ZToNuNu_5_P2,ZToNuNu_6_P2,ZToNuNu_7_P2,
						 QCD_1_P2,QCD_2_P2,QCD_3_P2,QCD_4_P2,QCD_5_P2,QCD_6_P2,QCD_7_P2,WToLNu_1_P2,WToLNu_2_P2,WToLNu_3_P2,WToLNu_4_P2,WToLNu_5_P2,WToLNu_6_P2,WToLNu_7_P2,
					 TT_1_P2,TT_2_P2,ST_1_P2,ST_2_P2,ST_3_P2,ST_4_P2,ZZ1_P2,ZZ2_P2,ZZ3_P2,WW1_P2,WW2_P2,WZ1_P2,WZ2_P2,WZ3_P2,ttW_P2,ttZ_P2,tZq_P2,ZZ4_P2,WZ4_P2,
					 tptzm0700lh_P2,tptzm0900lh_P2,tptzm1400lh_P2,tptzm1700lh_P2);

		MakeHistos(CUTbta1,plot,bin[i],Min[i],Max[i],0,data_B1,background_B1,ZToNuNu_1_B1,ZToNuNu_2_B1,ZToNuNu_3_B1,ZToNuNu_4_B1,ZToNuNu_5_B1,ZToNuNu_6_B1,ZToNuNu_7_B1,
						 QCD_1_B1,QCD_2_B1,QCD_3_B1,QCD_4_B1,QCD_5_B1,QCD_6_B1,QCD_7_B1,WToLNu_1_B1,WToLNu_2_B1,WToLNu_3_B1,WToLNu_4_B1,WToLNu_5_B1,WToLNu_6_B1,WToLNu_7_B1,
					 TT_1_B1,TT_2_B1,ST_1_B1,ST_2_B1,ST_3_B1,ST_4_B1,ZZ1_B1,ZZ2_B1,ZZ3_B1,WW1_B1,WW2_B1,WZ1_B1,WZ2_B1,WZ3_B1,ttW_B1,ttZ_B1,tZq_B1,ZZ4_B1,WZ4_B1,
					 tptzm0700lh_B1,tptzm0900lh_B1,tptzm1400lh_B1,tptzm1700lh_B1);

		MakeHistos(CUTbta2,plot,bin[i],Min[i],Max[i],0,data_B2,background_B2,ZToNuNu_1_B2,ZToNuNu_2_B2,ZToNuNu_3_B2,ZToNuNu_4_B2,ZToNuNu_5_B2,ZToNuNu_6_B2,ZToNuNu_7_B2,
						 QCD_1_B2,QCD_2_B2,QCD_3_B2,QCD_4_B2,QCD_5_B2,QCD_6_B2,QCD_7_B2,WToLNu_1_B2,WToLNu_2_B2,WToLNu_3_B2,WToLNu_4_B2,WToLNu_5_B2,WToLNu_6_B2,WToLNu_7_B2,
					 TT_1_B2,TT_2_B2,ST_1_B2,ST_2_B2,ST_3_B2,ST_4_B2,ZZ1_B2,ZZ2_B2,ZZ3_B2,WW1_B2,WW2_B2,WZ1_B2,WZ2_B2,WZ3_B2,ttW_B2,ttZ_B2,tZq_B2,ZZ4_B2,WZ4_B2,
					 tptzm0700lh_B2,tptzm0900lh_B2,tptzm1400lh_B2,tptzm1700lh_B2);

		MakeHistos(CUTzje1,plot,bin[i],Min[i],Max[i],0,data_Z1,background_Z1,ZToNuNu_1_Z1,ZToNuNu_2_Z1,ZToNuNu_3_Z1,ZToNuNu_4_Z1,ZToNuNu_5_Z1,ZToNuNu_6_Z1,ZToNuNu_7_Z1,
						 QCD_1_Z1,QCD_2_Z1,QCD_3_Z1,QCD_4_Z1,QCD_5_Z1,QCD_6_Z1,QCD_7_Z1,WToLNu_1_Z1,WToLNu_2_Z1,WToLNu_3_Z1,WToLNu_4_Z1,WToLNu_5_Z1,WToLNu_6_Z1,WToLNu_7_Z1,
					 TT_1_Z1,TT_2_Z1,ST_1_Z1,ST_2_Z1,ST_3_Z1,ST_4_Z1,ZZ1_Z1,ZZ2_Z1,ZZ3_Z1,WW1_Z1,WW2_Z1,WZ1_Z1,WZ2_Z1,WZ3_Z1,ttW_Z1,ttZ_Z1,tZq_Z1,ZZ4_Z1,WZ4_Z1,
					 tptzm0700lh_Z1,tptzm0900lh_Z1,tptzm1400lh_Z1,tptzm1700lh_Z1);

		MakeHistos(CUTzje2,plot,bin[i],Min[i],Max[i],0,data_Z2,background_Z2,ZToNuNu_1_Z2,ZToNuNu_2_Z2,ZToNuNu_3_Z2,ZToNuNu_4_Z2,ZToNuNu_5_Z2,ZToNuNu_6_Z2,ZToNuNu_7_Z2,
						 QCD_1_Z2,QCD_2_Z2,QCD_3_Z2,QCD_4_Z2,QCD_5_Z2,QCD_6_Z2,QCD_7_Z2,WToLNu_1_Z2,WToLNu_2_Z2,WToLNu_3_Z2,WToLNu_4_Z2,WToLNu_5_Z2,WToLNu_6_Z2,WToLNu_7_Z2,
					 TT_1_Z2,TT_2_Z2,ST_1_Z2,ST_2_Z2,ST_3_Z2,ST_4_Z2,ZZ1_Z2,ZZ2_Z2,ZZ3_Z2,WW1_Z2,WW2_Z2,WZ1_Z2,WZ2_Z2,WZ3_Z2,ttW_Z2,ttZ_Z2,tZq_Z2,ZZ4_Z2,WZ4_Z2,
					 tptzm0700lh_Z2,tptzm0900lh_Z2,tptzm1400lh_Z2,tptzm1700lh_Z2);
		
		MakeHistos(CUTwje1,plot,bin[i],Min[i],Max[i],0,data_W1,background_W1,ZToNuNu_1_W1,ZToNuNu_2_W1,ZToNuNu_3_W1,ZToNuNu_4_W1,ZToNuNu_5_W1,ZToNuNu_6_W1,ZToNuNu_7_W1,
						 QCD_1_W1,QCD_2_W1,QCD_3_W1,QCD_4_W1,QCD_5_W1,QCD_6_W1,QCD_7_W1,WToLNu_1_W1,WToLNu_2_W1,WToLNu_3_W1,WToLNu_4_W1,WToLNu_5_W1,WToLNu_6_W1,WToLNu_7_W1,
					 TT_1_W1,TT_2_W1,ST_1_W1,ST_2_W1,ST_3_W1,ST_4_W1,ZZ1_W1,ZZ2_W1,ZZ3_W1,WW1_W1,WW2_W1,WZ1_W1,WZ2_W1,WZ3_W1,ttW_W1,ttZ_W1,tZq_W1,ZZ4_W1,WZ4_W1,
					 tptzm0700lh_W1,tptzm0900lh_W1,tptzm1400lh_W1,tptzm1700lh_W1);

		MakeHistos(CUTwje2,plot,bin[i],Min[i],Max[i],0,data_W2,background_W2,ZToNuNu_1_W2,ZToNuNu_2_W2,ZToNuNu_3_W2,ZToNuNu_4_W2,ZToNuNu_5_W2,ZToNuNu_6_W2,ZToNuNu_7_W2,
						 QCD_1_W2,QCD_2_W2,QCD_3_W2,QCD_4_W2,QCD_5_W2,QCD_6_W2,QCD_7_W2,WToLNu_1_W2,WToLNu_2_W2,WToLNu_3_W2,WToLNu_4_W2,WToLNu_5_W2,WToLNu_6_W2,WToLNu_7_W2,
					 TT_1_W2,TT_2_W2,ST_1_W2,ST_2_W2,ST_3_W2,ST_4_W2,ZZ1_W2,ZZ2_W2,ZZ3_W2,WW1_W2,WW2_W2,WZ1_W2,WZ2_W2,WZ3_W2,ttW_W2,ttZ_W2,tZq_W2,ZZ4_W2,WZ4_W2,
					 tptzm0700lh_W2,tptzm0900lh_W2,tptzm1400lh_W2,tptzm1700lh_W2);

		MakeHistos(CUTttb1,plot,bin[i],Min[i],Max[i],0,data_T1,background_T1,ZToNuNu_1_T1,ZToNuNu_2_T1,ZToNuNu_3_T1,ZToNuNu_4_T1,ZToNuNu_5_T1,ZToNuNu_6_T1,ZToNuNu_7_T1,
						 QCD_1_T1,QCD_2_T1,QCD_3_T1,QCD_4_T1,QCD_5_T1,QCD_6_T1,QCD_7_T1,WToLNu_1_T1,WToLNu_2_T1,WToLNu_3_T1,WToLNu_4_T1,WToLNu_5_T1,WToLNu_6_T1,WToLNu_7_T1,
					 TT_1_T1,TT_2_T1,ST_1_T1,ST_2_T1,ST_3_T1,ST_4_T1,ZZ1_T1,ZZ2_T1,ZZ3_T1,WW1_T1,WW2_T1,WZ1_T1,WZ2_T1,WZ3_T1,ttW_T1,ttZ_T1,tZq_T1,ZZ4_T1,WZ4_T1,
					 tptzm0700lh_T1,tptzm0900lh_T1,tptzm1400lh_T1,tptzm1700lh_T1);

		MakeHistos(CUTttb2,plot,bin[i],Min[i],Max[i],0,data_T2,background_T2,ZToNuNu_1_T2,ZToNuNu_2_T2,ZToNuNu_3_T2,ZToNuNu_4_T2,ZToNuNu_5_T2,ZToNuNu_6_T2,ZToNuNu_7_T2,
						 QCD_1_T2,QCD_2_T2,QCD_3_T2,QCD_4_T2,QCD_5_T2,QCD_6_T2,QCD_7_T2,WToLNu_1_T2,WToLNu_2_T2,WToLNu_3_T2,WToLNu_4_T2,WToLNu_5_T2,WToLNu_6_T2,WToLNu_7_T2,
					 TT_1_T2,TT_2_T2,ST_1_T2,ST_2_T2,ST_3_T2,ST_4_T2,ZZ1_T2,ZZ2_T2,ZZ3_T2,WW1_T2,WW2_T2,WZ1_T2,WZ2_T2,WZ3_T2,ttW_T2,ttZ_T2,tZq_T2,ZZ4_T2,WZ4_T2,
					 tptzm0700lh_T2,tptzm0900lh_T2,tptzm1400lh_T2,tptzm1700lh_T2);
		
		MakeHistos(CUTfir1,plot,bin[i],Min[i],Max[i],0,data_F1,background_F1,ZToNuNu_1_F1,ZToNuNu_2_F1,ZToNuNu_3_F1,ZToNuNu_4_F1,ZToNuNu_5_F1,ZToNuNu_6_F1,ZToNuNu_7_F1,
						 QCD_1_F1,QCD_2_F1,QCD_3_F1,QCD_4_F1,QCD_5_F1,QCD_6_F1,QCD_7_F1,WToLNu_1_F1,WToLNu_2_F1,WToLNu_3_F1,WToLNu_4_F1,WToLNu_5_F1,WToLNu_6_F1,WToLNu_7_F1,
					 TT_1_F1,TT_2_F1,ST_1_F1,ST_2_F1,ST_3_F1,ST_4_F1,ZZ1_F1,ZZ2_F1,ZZ3_F1,WW1_F1,WW2_F1,WZ1_F1,WZ2_F1,WZ3_F1,ttW_F1,ttZ_F1,tZq_F1,ZZ4_F1,WZ4_F1,
					 tptzm0700lh_F1,tptzm0900lh_F1,tptzm1400lh_F1,tptzm1700lh_F1);

		MakeHistos(CUTfir2,plot,bin[i],Min[i],Max[i],0,data_F2,background_F2,ZToNuNu_1_F2,ZToNuNu_2_F2,ZToNuNu_3_F2,ZToNuNu_4_F2,ZToNuNu_5_F2,ZToNuNu_6_F2,ZToNuNu_7_F2,
						 QCD_1_F2,QCD_2_F2,QCD_3_F2,QCD_4_F2,QCD_5_F2,QCD_6_F2,QCD_7_F2,WToLNu_1_F2,WToLNu_2_F2,WToLNu_3_F2,WToLNu_4_F2,WToLNu_5_F2,WToLNu_6_F2,WToLNu_7_F2,
					 TT_1_F2,TT_2_F2,ST_1_F2,ST_2_F2,ST_3_F2,ST_4_F2,ZZ1_F2,ZZ2_F2,ZZ3_F2,WW1_F2,WW2_F2,WZ1_F2,WZ2_F2,WZ3_F2,ttW_F2,ttZ_F2,tZq_F2,ZZ4_F2,WZ4_F2,
				 tptzm0700lh_F2,tptzm0900lh_F2,tptzm1400lh_F2,tptzm1700lh_F2);

		MakeHistos(CUTtri1,plot,bin[i],Min[i],Max[i],0,data_TR1,background_TR1,ZToNuNu_1_TR1,ZToNuNu_2_TR1,ZToNuNu_3_TR1,ZToNuNu_4_TR1,ZToNuNu_5_TR1,ZToNuNu_6_TR1,ZToNuNu_7_TR1,
									 QCD_1_TR1,QCD_2_TR1,QCD_3_TR1,QCD_4_TR1,QCD_5_TR1,QCD_6_TR1,QCD_7_TR1,WToLNu_1_TR1,WToLNu_2_TR1,WToLNu_3_TR1,WToLNu_4_TR1,WToLNu_5_TR1,WToLNu_6_TR1,WToLNu_7_TR1,
											 TT_1_TR1,TT_2_TR1,ST_1_TR1,ST_2_TR1,ST_3_TR1,ST_4_TR1,ZZ1_TR1,ZZ2_TR1,ZZ3_TR1,WW1_TR1,WW2_TR1,WZ1_TR1,WZ2_TR1,WZ3_TR1,ttW_TR1,ttZ_TR1,tZq_TR1,ZZ4_TR1,WZ4_TR1,
											 tptzm0700lh_TR1,tptzm0900lh_TR1,tptzm1400lh_TR1,tptzm1700lh_TR1);

		MakeHistos(CUTtri2,plot,bin[i],Min[i],Max[i],0,data_TR2,background_TR2,ZToNuNu_1_TR2,ZToNuNu_2_TR2,ZToNuNu_3_TR2,ZToNuNu_4_TR2,ZToNuNu_5_TR2,ZToNuNu_6_TR2,ZToNuNu_7_TR2,
									 QCD_1_TR2,QCD_2_TR2,QCD_3_TR2,QCD_4_TR2,QCD_5_TR2,QCD_6_TR2,QCD_7_TR2,WToLNu_1_TR2,WToLNu_2_TR2,WToLNu_3_TR2,WToLNu_4_TR2,WToLNu_5_TR2,WToLNu_6_TR2,WToLNu_7_TR2,
											 TT_1_TR2,TT_2_TR2,ST_1_TR2,ST_2_TR2,ST_3_TR2,ST_4_TR2,ZZ1_TR2,ZZ2_TR2,ZZ3_TR2,WW1_TR2,WW2_TR2,WZ1_TR2,WZ2_TR2,WZ3_TR2,ttW_TR2,ttZ_TR2,tZq_TR2,ZZ4_TR2,WZ4_TR2,
											 tptzm0700lh_TR2,tptzm0900lh_TR2,tptzm1400lh_TR2,tptzm1700lh_TR2);

		MakeHistos(CUT,plot,bin[i],Min[i],Max[i],1,data_J1,background_J1,ZToNuNu_1_J1,ZToNuNu_2_J1,ZToNuNu_3_J1,ZToNuNu_4_J1,ZToNuNu_5_J1,ZToNuNu_6_J1,ZToNuNu_7_J1,
						 QCD_1_J1,QCD_2_J1,QCD_3_J1,QCD_4_J1,QCD_5_J1,QCD_6_J1,QCD_7_J1,WToLNu_1_J1,WToLNu_2_J1,WToLNu_3_J1,WToLNu_4_J1,WToLNu_5_J1,WToLNu_6_J1,WToLNu_7_J1,
					 TT_1_J1,TT_2_J1,ST_1_J1,ST_2_J1,ST_3_J1,ST_4_J1,ZZ1_J1,ZZ2_J1,ZZ3_J1,WW1_J1,WW2_J1,WZ1_J1,WZ2_J1,WZ3_J1,ttW_J1,ttZ_J1,tZq_J1,ZZ4_J1,WZ4_J1,
					 tptzm0700lh_J1,tptzm0900lh_J1,tptzm1400lh_J1,tptzm1700lh_J1);

		MakeHistos(CUT,plot,bin[i],Min[i],Max[i],2,data_J2,background_J2,ZToNuNu_1_J2,ZToNuNu_2_J2,ZToNuNu_3_J2,ZToNuNu_4_J2,ZToNuNu_5_J2,ZToNuNu_6_J2,ZToNuNu_7_J2,
						 QCD_1_J2,QCD_2_J2,QCD_3_J2,QCD_4_J2,QCD_5_J2,QCD_6_J2,QCD_7_J2,WToLNu_1_J2,WToLNu_2_J2,WToLNu_3_J2,WToLNu_4_J2,WToLNu_5_J2,WToLNu_6_J2,WToLNu_7_J2,
					 TT_1_J2,TT_2_J2,ST_1_J2,ST_2_J2,ST_3_J2,ST_4_J2,ZZ1_J2,ZZ2_J2,ZZ3_J2,WW1_J2,WW2_J2,WZ1_J2,WZ2_J2,WZ3_J2,ttW_J2,ttZ_J2,tZq_J2,ZZ4_J2,WZ4_J2,
					 tptzm0700lh_J2,tptzm0900lh_J2,tptzm1400lh_J2,tptzm1700lh_J2);

		MakeHistos(CUT,plot,bin[i],Min[i],Max[i],3,data_J3,background_J3,ZToNuNu_1_J3,ZToNuNu_2_J3,ZToNuNu_3_J3,ZToNuNu_4_J3,ZToNuNu_5_J3,ZToNuNu_6_J3,ZToNuNu_7_J3,
						 QCD_1_J3,QCD_2_J3,QCD_3_J3,QCD_4_J3,QCD_5_J3,QCD_6_J3,QCD_7_J3,WToLNu_1_J3,WToLNu_2_J3,WToLNu_3_J3,WToLNu_4_J3,WToLNu_5_J3,WToLNu_6_J3,WToLNu_7_J3,
					 TT_1_J3,TT_2_J3,ST_1_J3,ST_2_J3,ST_3_J3,ST_4_J3,ZZ1_J3,ZZ2_J3,ZZ3_J3,WW1_J3,WW2_J3,WZ1_J3,WZ2_J3,WZ3_J3,ttW_J3,ttZ_J3,tZq_J3,ZZ4_J3,WZ4_J3,
					 tptzm0700lh_J3,tptzm0900lh_J3,tptzm1400lh_J3,tptzm1700lh_J3);

		MakeHistos(CUT,plot,bin[i],Min[i],Max[i],4,data_J4,background_J4,ZToNuNu_1_J4,ZToNuNu_2_J4,ZToNuNu_3_J4,ZToNuNu_4_J4,ZToNuNu_5_J4,ZToNuNu_6_J4,ZToNuNu_7_J4,
						 QCD_1_J4,QCD_2_J4,QCD_3_J4,QCD_4_J4,QCD_5_J4,QCD_6_J4,QCD_7_J4,WToLNu_1_J4,WToLNu_2_J4,WToLNu_3_J4,WToLNu_4_J4,WToLNu_5_J4,WToLNu_6_J4,WToLNu_7_J4,
					 TT_1_J4,TT_2_J4,ST_1_J4,ST_2_J4,ST_3_J4,ST_4_J4,ZZ1_J4,ZZ2_J4,ZZ3_J4,WW1_J4,WW2_J4,WZ1_J4,WZ2_J4,WZ3_J4,ttW_J4,ttZ_J4,tZq_J4,ZZ4_J4,WZ4_J4,
					 tptzm0700lh_J4,tptzm0900lh_J4,tptzm1400lh_J4,tptzm1700lh_J4);

		MakeHistos(CUTqcd1,plot,bin[i],Min[i],Max[i],0,data_qcd1,background_qcd1,ZToNuNu_1_qcd1,ZToNuNu_2_qcd1,ZToNuNu_3_qcd1,ZToNuNu_4_qcd1,ZToNuNu_5_qcd1,ZToNuNu_6_qcd1,ZToNuNu_7_qcd1,
												 QCD_1_qcd1,QCD_2_qcd1,QCD_3_qcd1,QCD_4_qcd1,QCD_5_qcd1,QCD_6_qcd1,QCD_7_qcd1,WToLNu_1_qcd1,WToLNu_2_qcd1,WToLNu_3_qcd1,WToLNu_4_qcd1,WToLNu_5_qcd1,WToLNu_6_qcd1,WToLNu_7_qcd1,
														 TT_1_qcd1,TT_2_qcd1,ST_1_qcd1,ST_2_qcd1,ST_3_qcd1,ST_4_qcd1,ZZ1_qcd1,ZZ2_qcd1,ZZ3_qcd1,WW1_qcd1,WW2_qcd1,WZ1_qcd1,WZ2_qcd1,WZ3_qcd1,ttW_qcd1,ttZ_qcd1,tZq_qcd1,ZZ4_qcd1,WZ4_qcd1,
														 tptzm0700lh_qcd1,tptzm0900lh_qcd1,tptzm1400lh_qcd1,tptzm1700lh_qcd1);

		MakeHistos(CUTqcd2,plot,bin[i],Min[i],Max[i],0,data_qcd2,background_qcd2,ZToNuNu_1_qcd2,ZToNuNu_2_qcd2,ZToNuNu_3_qcd2,ZToNuNu_4_qcd2,ZToNuNu_5_qcd2,ZToNuNu_6_qcd2,ZToNuNu_7_qcd2,
									 QCD_1_qcd2,QCD_2_qcd2,QCD_3_qcd2,QCD_4_qcd2,QCD_5_qcd2,QCD_6_qcd2,QCD_7_qcd2,WToLNu_1_qcd2,WToLNu_2_qcd2,WToLNu_3_qcd2,WToLNu_4_qcd2,WToLNu_5_qcd2,WToLNu_6_qcd2,WToLNu_7_qcd2,
											 TT_1_qcd2,TT_2_qcd2,ST_1_qcd2,ST_2_qcd2,ST_3_qcd2,ST_4_qcd2,ZZ1_qcd2,ZZ2_qcd2,ZZ3_qcd2,WW1_qcd2,WW2_qcd2,WZ1_qcd2,WZ2_qcd2,WZ3_qcd2,ttW_qcd2,ttZ_qcd2,tZq_qcd2,ZZ4_qcd2,WZ4_qcd2,
											 tptzm0700lh_qcd2,tptzm0900lh_qcd2,tptzm1400lh_qcd2,tptzm1700lh_qcd2);

		MakeHistos(CUTpdf1,plot,bin[i],Min[i],Max[i],0,data_pdf1,background_pdf1,ZToNuNu_1_pdf1,ZToNuNu_2_pdf1,ZToNuNu_3_pdf1,ZToNuNu_4_pdf1,ZToNuNu_5_pdf1,ZToNuNu_6_pdf1,ZToNuNu_7_pdf1,
									 QCD_1_pdf1,QCD_2_pdf1,QCD_3_pdf1,QCD_4_pdf1,QCD_5_pdf1,QCD_6_pdf1,QCD_7_pdf1,WToLNu_1_pdf1,WToLNu_2_pdf1,WToLNu_3_pdf1,WToLNu_4_pdf1,WToLNu_5_pdf1,WToLNu_6_pdf1,WToLNu_7_pdf1,
											 TT_1_pdf1,TT_2_pdf1,ST_1_pdf1,ST_2_pdf1,ST_3_pdf1,ST_4_pdf1,ZZ1_pdf1,ZZ2_pdf1,ZZ3_pdf1,WW1_pdf1,WW2_pdf1,WZ1_pdf1,WZ2_pdf1,WZ3_pdf1,ttW_pdf1,ttZ_pdf1,tZq_pdf1,ZZ4_pdf1,WZ4_pdf1,
											 tptzm0700lh_pdf1,tptzm0900lh_pdf1,tptzm1400lh_pdf1,tptzm1700lh_pdf1);

		MakeHistos(CUTpdf2,plot,bin[i],Min[i],Max[i],0,data_pdf2,background_pdf2,ZToNuNu_1_pdf2,ZToNuNu_2_pdf2,ZToNuNu_3_pdf2,ZToNuNu_4_pdf2,ZToNuNu_5_pdf2,ZToNuNu_6_pdf2,ZToNuNu_7_pdf2,
									 QCD_1_pdf2,QCD_2_pdf2,QCD_3_pdf2,QCD_4_pdf2,QCD_5_pdf2,QCD_6_pdf2,QCD_7_pdf2,WToLNu_1_pdf2,WToLNu_2_pdf2,WToLNu_3_pdf2,WToLNu_4_pdf2,WToLNu_5_pdf2,WToLNu_6_pdf2,WToLNu_7_pdf2,
											 TT_1_pdf2,TT_2_pdf2,ST_1_pdf2,ST_2_pdf2,ST_3_pdf2,ST_4_pdf2,ZZ1_pdf2,ZZ2_pdf2,ZZ3_pdf2,WW1_pdf2,WW2_pdf2,WZ1_pdf2,WZ2_pdf2,WZ3_pdf2,ttW_pdf2,ttZ_pdf2,tZq_pdf2,ZZ4_pdf2,WZ4_pdf2,
											 tptzm0700lh_pdf2,tptzm0900lh_pdf2,tptzm1400lh_pdf2,tptzm1700lh_pdf2);
	}
	else {
			CloneHistos();
	}
*/
		//according to SYST we reset our bin error to histo_SR
		//
/*	for(int m=1; m<background_SR->GetNbinsX()+1; m++){ //1112
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
		}*/
	

//		Double_t dataErr   = 0; Float_t dataYield = data_SR->IntegralAndError(1,TTTT_SR->GetNbinsX()-1,dataErr,"");/*{{{*/
		Double_t QCD_HT200to300Err   = 0; Float_t QCD_HT200to300Yield = QCD_HT200to300_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),QCD_HT200to300Err,"");
		Double_t QCD_HT300to500Err   = 0; Float_t QCD_HT300to500Yield = QCD_HT300to500_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),QCD_HT300to500Err,"");
		Double_t QCD_HT500to700Err   = 0; Float_t QCD_HT500to700Yield = QCD_HT500to700_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),QCD_HT500to700Err,"");
		Double_t QCD_HT700to1000Err   = 0; Float_t QCD_HT700to1000Yield = QCD_HT700to1000_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),QCD_HT700to1000Err,"");
		Double_t QCD_HT1500to2000Err   = 0; Float_t QCD_HT1500to2000Yield = QCD_HT1500to2000_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),QCD_HT1500to2000Err,"");
		Double_t QCD_HT2000toInErr   = 0; Float_t QCD_HT2000toInYield = QCD_HT2000toIn_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),QCD_HT2000toInErr,"");
		Double_t QCD_HT1000to1500Err   = 0; Float_t QCD_HT1000to1500Yield = QCD_HT1000to1500_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),QCD_HT1000to1500Err,"");
		Double_t TTJetsErr   = 0; Float_t TTJetsYield = TTJets_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),TTJetsErr,"");
		Double_t TTWJetsErr = 0; Float_t TTWJetsYield = TTWJets_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),TTWJetsErr,"");
		Double_t TTZErr = 0; Float_t TTZYield = TTZ_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),TTZErr,"");
		Double_t TTErr = 0; Float_t TTYield = TT_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),TTErr,"");

		Double_t TTTT_Err= 0; Float_t TTTT_Yield = TTTT_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),TTTT_Err,"");

    if(i==0){
      cout<<endl;
      //cout<<"Plotting "<<name[i]<<endl;
    //  cout<<"DATA      = "<<data_SR->Integral()<<" +/- "<<dataErr<<endl;/*{{{*/
      cout<<"QCD   = "<<QCD_HT200to300_SR->Integral()+QCD_HT300to500_SR->Integral()+QCD_HT500to700_SR->Integral()+QCD_HT700to1000_SR->Integral()+QCD_HT1500to2000_SR->Integral()+QCD_HT2000toIn_SR->Integral()+QCD_HT1000to1500_SR->Integral()<<" +/- "<<
	sqrt(QCD_HT200to300Err*QCD_HT200to300Err+QCD_HT300to500Err*QCD_HT300to500Err+QCD_HT500to700Err*QCD_HT500to700Err+QCD_HT700to1000Err*QCD_HT700to1000Err+QCD_HT1500to2000Err*QCD_HT1500to2000Err+QCD_HT2000toInErr*QCD_HT2000toInErr+QCD_HT1000to1500Err*QCD_HT1000to1500Err)<<endl;
      cout<<"TTJets   = "<<TTJets_SR->Integral()<<" +/- "<<	sqrt(TTJetsErr*TTJetsErr)<<endl;
	  cout<<"TTWJets    = "<<TTWJets_SR->Integral()<<" +/- "<<sqrt(TTWJetsErr*TTWJetsErr)<<endl;
	  cout<<"TTZ       = "<<TTZ_SR->Integral()<<" +/- "<<sqrt(TTZErr*TTZErr)<<endl;
	  cout<<"TT       = "<<TT_SR->Integral()<<" +/- "<<sqrt(TTErr*TTErr)<<endl;
	  cout<<"Total BKG = "<<QCD_HT200to300_SR->Integral()+QCD_HT300to500_SR->Integral()+QCD_HT500to700_SR->Integral()+QCD_HT700to1000_SR->Integral()+QCD_HT1500to2000_SR->Integral()+QCD_HT2000toIn_SR->Integral()+QCD_HT1000to1500_SR->Integral()+TTJets_SR->Integral()+TTWJets_SR->Integral()+TTZ_SR->Integral() +TT_SR->Integral()<<" +/- "<<
		  sqrt(QCD_HT200to300Err*QCD_HT200to300Err+QCD_HT300to500Err*QCD_HT300to500Err+QCD_HT500to700Err*QCD_HT500to700Err+QCD_HT700to1000Err*QCD_HT700to1000Err+QCD_HT1500to2000Err*QCD_HT1500to2000Err+QCD_HT2000toInErr*QCD_HT2000toInErr+QCD_HT1000to1500Err*QCD_HT1000to1500Err+TTJetsErr*TTJetsErr+TTWJetsErr*TTWJetsErr+TTZErr*TTZErr)<<endl;
      cout<<"TTTT = "<<TTTT_SR->Integral()<<" +/- "<<sqrt(TTTT_Err*TTTT_Err)<<endl;
      
	}/*}}}*/

    TCanvas* c1 = new TCanvas("c1","c1",0,0,600,600);


		TTTT_SR->SetLineWidth(2);
        /*{{{*/
		TTTT_SR->SetLineColor(2);
		QCD_HT200to300_SR->SetLineWidth(2); QCD_HT300to500_SR->SetLineWidth(2);QCD_HT500to700_SR->SetLineWidth(2); QCD_HT700to1000_SR->SetLineWidth(2); QCD_HT1500to2000_SR->SetLineWidth(2); QCD_HT2000toIn_SR->SetLineWidth(2); QCD_HT1000to1500_SR->SetLineWidth(2);
		TTJets_SR->SetLineWidth(2);
		TTWJets_SR->SetLineWidth(2);
		TTZ_SR->SetLineWidth(2);
		TT_SR->SetLineWidth(2);

		QCD_HT200to300_SR->SetLineColor(kOrange); QCD_HT300to500_SR->SetLineColor(kOrange);QCD_HT500to700_SR->SetLineColor(kOrange); QCD_HT700to1000_SR->SetLineColor(kOrange); QCD_HT1500to2000_SR->SetLineColor(kOrange); QCD_HT2000toIn_SR->SetLineColor(kOrange); QCD_HT1000to1500_SR->SetLineColor(kOrange);
		TTJets_SR->SetLineColor(kGreen-3);
		TTWJets_SR->SetLineColor(kCyan-4);
		TTZ_SR->SetLineColor(kGreen+3); 
		TT_SR->SetLineColor(kGreen-4); 

		QCD_HT200to300_SR->SetFillColor(kOrange); QCD_HT300to500_SR->SetFillColor(kOrange);QCD_HT500to700_SR->SetFillColor(kOrange); QCD_HT700to1000_SR->SetFillColor(kOrange); QCD_HT1500to2000_SR->SetFillColor(kOrange); QCD_HT2000toIn_SR->SetFillColor(kOrange); QCD_HT1000to1500_SR->SetFillColor(kOrange);
	//	TTJets_SR->SetFillColor(kGreen-3);
	//	TTWJets_SR->SetFillColor(kCyan-4);
	//	TTZ_SR->SetFillColor(kGreen+3);

//		data_SR->SetLineWidth(2); data_SR->SetLineColor(1); data_SR->SetMarkerColor(1); data_SR->SetMarkerStyle(20); data_SR->SetMarkerSize(1.3);/*}}}*/




	//////
	//画下面data/MC的比率计算图
	//////
   /* TPad *c1_1 = new TPad("c1_1","newpad",0.01,0.01,0.99,0.32);
    c1_1->Draw();
    c1_1->cd();
    c1_1->SetTopMargin(0.045);
    c1_1->SetBottomMargin(0.3);
    c1_1->SetRightMargin(0.035);
    c1_1->SetLeftMargin(0.11);
    
    TGraphAsymmErrors *gDATA = new TGraphAsymmErrors(data_SR);	
    gDATA->SetLineWidth(2); 
    gDATA->SetLineColor(1);
    gDATA->SetMarkerColor(1); 
    gDATA->SetMarkerStyle(20); 
    gDATA->SetMarkerSize(1.3);
    for (int i = 0; i < gDATA->GetN(); ++i) {
      double alpha = 1 - 0.6827;
      int M = gDATA->GetY()[i];
      double L =  (M==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,M,1.));//condition ? result_if_true : result_if_false
			//???
      double U =  ROOT::Math::gamma_quantile_c(alpha/2,M+1,1);
      //if(M!=0){
      gDATA->SetPointEYlow(i, M-L);
      gDATA->SetPointEYhigh(i, U-M);
      //}
    }

		//RATIO2 is the gray.
    TH1F *RATIO2 = (TH1F*)background_SR->Clone();
    Double_t x[bin[i]]; Double_t exl[bin[i]]; Double_t exh[bin[i]];
    Double_t y[bin[i]]; Double_t eyl[bin[i]]; Double_t eyh[bin[i]]; 
    for(int m=0; m<background_SR->GetNbinsX(); m++){ 
      x[m]=Min[i]+m*(Max[i]-Min[i])/bin[i]+(Max[i]-Min[i])/(2*bin[i]);
      exl[m]=(Max[i]-Min[i])/(2*bin[i]);
      exh[m]=(Max[i]-Min[i])/(2*bin[i]);
      RATIO2->SetBinContent(m+1,1);
      if(background_SR->GetBinContent(m+1)!=0) {
				y[m]=data_SR->GetBinContent(m+1)/background_SR->GetBinContent(m+1);
				eyl[m]=sqrt(gDATA->GetErrorYlow(m)*gDATA->GetErrorYlow(m))/background_SR->GetBinContent(m+1);
				eyh[m]=sqrt(gDATA->GetErrorYhigh(m)*gDATA->GetErrorYhigh(m))/background_SR->GetBinContent(m+1);
				//it is error of data / background bin content.
				RATIO2->SetBinError(m+1,background_SR->GetBinError(m+1)/background_SR->GetBinContent(m+1));
				//?reflects what?
      }
			else {
				y[m]=-1;
				eyl[m]=0;
				eyh[m]=0;
      }
    }

    TGraphAsymmErrors *RATIO = new TGraphAsymmErrors(bin[i],x,y,exl,exh,eyl,eyh);
    RATIO->Draw("AE0p");
    RATIO->SetMarkerColor(1); 
    RATIO->SetMarkerStyle(21); 
    RATIO->SetMarkerSize(1.0);
    RATIO->SetMaximum(1.7);
    RATIO->SetMinimum(0.3);
    RATIO->SetLineColor(1);
    RATIO->SetLineWidth(2);
    RATIO->GetXaxis()->SetTitleOffset(0.9);
    RATIO->GetYaxis()->SetTitleOffset(0.5);
    RATIO->SetTitle("");
    RATIO->GetYaxis()->SetTitle("observed/expected");
    RATIO->GetXaxis()->SetTitle(axis[i]);
    RATIO->GetXaxis()->SetLabelSize(0.13);
    RATIO->GetYaxis()->SetLabelSize(0.13);
    RATIO->GetXaxis()->SetTitleSize(0.15);
    RATIO->GetYaxis()->SetTitleSize(0.09);
    RATIO->GetYaxis()->SetNdivisions(505);
    RATIO->GetXaxis()->SetRangeUser(Min[i],Max[i]);
    RATIO2->SetFillStyle(3002);
    RATIO2->SetFillColor(12);
    RATIO2->SetLineColor(12);
    RATIO2->SetMarkerSize(0);
    RATIO2->Draw("E2same");
    RATIO->Draw("E0psame");

    TLine* line = new TLine(Min[i],1,Max[i],1);
    line->SetLineColor(2);
    line->SetLineWidth(2);
    line->Draw("same");	
    c1->cd();
    */
	/////
	//画上面的data/MC图
	/////
    TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.30,0.99,0.90);// bottom left point(),
    c1_2->Draw();
    c1_2->cd();
   // c1_2->SetTopMargin(0.08);
   // c1_2->SetBottomMargin(0.02);
   // c1_2->SetRightMargin(0.035);
   // c1_2->SetLeftMargin(0.20);
  
   // THStack *hs = new THStack("hs","hs");
    TH1::SetDefaultSumw2();
    TH1F *hs = new TH1F("hs","h1+h2",bin[i],Min[i],Max[i]);
    //hs->Add(TTZ_SR);
    //hs->Add(TTWJets_SR);
    //hs->Add(TTJets_SR);
    /*hs->Add(QCD_HT200to300_SR);
    hs->Add(QCD_HT300to500_SR);
    hs->Add(QCD_HT500to700_SR);
    hs->Add(QCD_HT700to1000_SR);
    hs->Add(QCD_HT1500to2000_SR);
    hs->Add(QCD_HT2000toIn_SR);
    hs->Add(QCD_HT1000to1500_SR);*/
    hs->Add(QCD_HT200to300_SR,QCD_HT300to500_SR,1,1);
    //hs->Add(QCD_HT300to500_SR,1);
    hs->Add(QCD_HT500to700_SR,1);
    hs->Add(QCD_HT700to1000_SR,1);
    hs->Add(QCD_HT1500to2000_SR,1);
    hs->Add(QCD_HT2000toIn_SR,1);
    hs->Add(QCD_HT1000to1500_SR,1);
	
    
	hs->SetLineWidth(2);
	hs->SetLineColor(kYellow+2); 
  //  hs->Draw("histo");///?
   // hs->Draw("histo NOSTACK");///?
    hs->SetMinimum(0);
//    hs->SetMaximum(1);
    hs->SetMaximum(2 * hs->GetMaximum());
    hs->GetYaxis()->SetTitleSize(0.050);
    hs->GetXaxis()->SetTitleSize(0.040);
    hs->GetYaxis()->SetLabelSize(0.040);
    hs->GetXaxis()->SetLabelSize(0.040); 
    hs->SetTitle("");
    hs->GetYaxis()->SetTitle("Events");
    hs->GetXaxis()->SetTitle(axis[i]);
    hs->GetYaxis()->SetTitleOffset(0.80);
    hs->GetXaxis()->SetTitleOffset(0.85);//Set distance between the axis and the axis title
    hs->DrawNormalized("hist", 1);
    
   // TTTT_SR->Draw("samehisto");
      TTTT_SR->DrawNormalized("samehist", 1);
   // TTJets_SR->Draw("samehisto");
  //  TTWJets_SR->Draw("samehisto");
//    TTZ_SR->Draw("samehisto");
	background_SR->SetLineWidth(2);
	background_SR->SetLineColor(kViolet-2); 
   // background_SR->Draw("samehisto");
    background_SR->DrawNormalized("samehist", 1);
    
    //TH1F * TTX = TTJets_SR + TTWJets_SR + TTZ_SR;
    TH1D *TTX = new TH1D("TTX","h1+h2",bin[i],Min[i],Max[i]);
    TTX->Add(TTJets_SR,TTWJets_SR,1,1);
    TTX->Add(TTZ_SR,1);
	TTX->SetLineWidth(2);
	TTX->SetLineColor(kAzure); 
//    TTX->Draw("samehisto");
    TTX->DrawNormalized("samehist", 1);

   // TTJets_SR->Draw("samehisto");
   // TTWJets_SR->Draw("samehisto");
   // TTZ_SR->Draw("samehisto");
		//why background add up to meet data?
    //data_SR->Draw("E same"); 
    
    //background_SR->SetFillStyle(3005);//3000+pattern_number,FillStyle = 3ijk
    //background_SR->SetFillColor(12);
   // background_SR->SetLineColor(12);
   // background_SR->Draw("E2same");
    
   // float maxy=-10;
   // float ADD=20;
   // for(int ABC=0; ABC<data_SR->GetNbinsX(); ABC++){
     // if(background_SR->GetBinContent(ABC+1)+ADD>=maxy) maxy=background_SR->GetBinContent(ABC+1)+ADD;
     // if(data_SR      ->GetBinContent(ABC+1)+ADD>=maxy) maxy=data_SR      ->GetBinContent(ABC+1)+ADD;
   // }
//    hs->SetMaximum(maxy);
    //hs->SetMaximum(1);
   // hs->SetMinimum(3);
   // c1_2->SetLogy();//Set Lin/Log scale for Y,value = 0 Y scale will be linear,value = 1 Y scale will be logarithmic (base 10)

	/////
	//画图上各种说明文字
	/////
    
    TPad *pad = new TPad("pad","pad",0.01,0.01,0.99,0.99);
    gPad->RedrawAxis();
    TString channelText = "";
    float channelTextFont   = 42;
    float channelTextSize   = 0.06;
    TString cmsText     = "CMS";
    float cmsTextFont   = 61;  // default is helvetic-bold
    bool writeExtraText = true;
    TString extraText   = "MC";
    //TString extraText   = "";
    float extraTextFont = 52;  // default is helvetica-italics
    // text sizes and text offsets with respect to the top frame in unit of the top margin size
    float lumiTextSize     = 0.6;
    float lumiTextOffset   = 0.2;
    float cmsTextSize      = 0.75;
    float cmsTextOffset    = 0.1;  // only used in outOfFrame version
    float relPosX    = 0.045;
    float relPosY    = 0.035;
    float relExtraDY = 1.2;
    // ratio of "CMS" and extra text size
    float extraOverCmsTextSize  = 0.76;
    TString lumi_13TeV;
    lumi_13TeV = "36.773fb^{-1}";
    TString lumiText;
    lumiText += lumi_13TeV;
    lumiText += " (2016, 13 TeV)";
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
    latex.DrawLatex(l+0.01, 0.94,cmsText);
    latex.SetTextFont(extraTextFont);
    latex.SetTextSize(extraTextSize*t);
    latex.DrawLatex(l+0.12, 0.94, extraText); 
    latex.SetTextFont(channelTextFont);
    latex.SetTextSize(channelTextSize);


    //定义图中各个线和直方图的颜色
    TLegend *pl2 = new TLegend(0.65,0.60,0.91,0.91);
    pl2->SetTextSize(0.045); 
    pl2->SetFillColor(0);
  //  TLegendEntry *ple2 = pl2->AddEntry(data_SR, "data",  "L"); 
    TLegendEntry *ple2 = pl2->AddEntry(TTTT_SR, "TTTT",  "L"); 
    ple2 = pl2->AddEntry(hs, "QCD",  "L");
   // ple2 = pl2->AddEntry(TTJets_SR, "TTJets",  "L");
   // ple2 = pl2->AddEntry(TTWJets_SR, "TTWJets",  "L");
   // ple2 = pl2->AddEntry(TTZ_SR, "TTZ",  "L");
    ple2 = pl2->AddEntry(TTX, "TTX",  "L");
    ple2 = pl2->AddEntry(background_SR, "background",  "L");
    pl2->Draw();
    
    TString NAME = name[i];
    cout<<"Finished "<<NAME<<endl;
   //c1->SaveAs(NAME+".pdf");
    //c1->SaveAs(NAME+".png");
    //c1->SaveAs("/publicfs/cms/user/yutz/Tprime/2017_dineutrino/"+NAME+".pdf");
   // c1->SaveAs("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v1/reslult1/"+NAME+".pdf");
    c1->SaveAs("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v3/MC_normalized_wQCDCorrected/"+NAME+".png");
    //c1->SaveAs("/publicfs/cms/user/yutz/Tprime/2017_dineutrino/"+NAME+".png");
    c1->Draw(); 

  }

}

//from Tree, get tree plot, apply CUT and name the new histogram histo.
void GetHisto(char CUT[1000], TTree *Tree, TH1F* & histo, const char *plot, int BIN, float MIN, float MAX){/*{{{*/
  char input[50]; sprintf(input,"%s>>h(%i,%f,%f)",plot,BIN,MIN,MAX);
	//h is histogram name.
  TH1F *temp = new TH1F("", "", BIN,MIN,MAX);
	//Draw() Returns	-1 in case of error or number of selected events in case of success.
	//? not a booleun, type conversion I guess.
	//?guess once we read into the tree, we can get the information in all branches. and for draw we examine every entry.
  if(Tree->Draw(input,CUT)){ Tree->Draw(input,CUT); TH1F* h=(TH1F*)gDirectory->Get("h"); histo = (TH1F*)h->Clone(); delete h; }
	else { histo = (TH1F*)temp->Clone(); }
  histo->SetDirectory(0);//dir can be 0 in which case the histogram does not belong to any directory.
  histo->SetName("histo");
  delete temp;
 }/*}}}*/

//for MC we multiply the scale factor, adjust error accordingly , and make background histogram
//we get histograms based on CUT from MC and data,and we
void MakeHistos(char CUT[1000],const char *plot,int BIN,float MIN,float MAX,int JETSyst,
               /* TH1F* &data_func,*/TH1F* &background_func,TH1F* &QCD_HT200to300_func,TH1F* &QCD_HT300to500_func,TH1F* &QCD_HT500to700_func,  TH1F*  &QCD_HT700to1000_func,TH1F* &QCD_HT1000to1500_func,TH1F* &QCD_HT1500to2000_func,TH1F* &QCD_HT2000toIn_func,
                 TH1F* &TTJets_func,TH1F* &TTWJets_func,TH1F* &TTZ_func,TH1F* &TT_func, TH1F* &TTTT_func){
      //no background
     // TH1F *data;
      TH1F *TTTT;
      TH1F *QCD_HT200to300;
      TH1F *QCD_HT300to500;
      TH1F *QCD_HT500to700;
      TH1F *QCD_HT700to1000;
      TH1F *QCD_HT1000to1500;
      TH1F *QCD_HT1500to2000;
      TH1F *QCD_HT2000toIn;
      TH1F *TTJets;
      TH1F *TTWJets;
      TH1F *TTZ;
      TH1F* TT;
        //what is JETSyst?
        //given at each call of the function.0,1,2,3,or 4
      if(JETSyst==0){
       // GetHisto(CUT, Tree01, data        ,plot,BIN,MIN,MAX);//tree01 different number means different files' tree
        GetHisto(CUT, Tree02, TTTT ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree03, QCD_HT200to300 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree04, QCD_HT300to500 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree05, QCD_HT500to700 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree06, QCD_HT700to1000 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree07, QCD_HT1000to1500 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree08, QCD_HT1500to2000 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree09, QCD_HT2000toIn ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree10, TTJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree11, TTWJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree12, TTZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13, TT ,plot,BIN,MIN,MAX);
      }
        else if(JETSyst==1){
       // GetHisto(CUT, Tree01_J1, data        ,plot,BIN,MIN,MAX);//J1 from JESup directory
        GetHisto(CUT, Tree02_J1, TTTT ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree03_J1, QCD_HT200to300 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree04_J1, QCD_HT300to500 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree05_J1, QCD_HT500to700 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree06_J1, QCD_HT700to1000 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree07_J1, QCD_HT1000to1500 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree08_J1, QCD_HT1500to2000 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree09_J1, QCD_HT2000toIn ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree10_J1, TTJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree11_J1, TTWJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree12_J1, TTZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, TT ,plot,BIN,MIN,MAX);
      }
        else if(JETSyst==2){
       // GetHisto(CUT, Tree01_J2, data        ,plot,BIN,MIN,MAX);//J2 from JESdo
        GetHisto(CUT, Tree02_J2, TTTT ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree03_J2, QCD_HT200to300 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree04_J2, QCD_HT300to500 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree05_J2, QCD_HT500to700 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree06_J2, QCD_HT700to1000 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree07_J2, QCD_HT1000to1500 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree08_J2, QCD_HT1500to2000 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree09_J2, QCD_HT2000toIn ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree10_J2, TTJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree11_J2, TTWJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree12_J2, TTZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, TT ,plot,BIN,MIN,MAX);
      }
        else if(JETSyst==3){
       // GetHisto(CUT, Tree01_J3, data        ,plot,BIN,MIN,MAX);//J3 from JERup
        GetHisto(CUT, Tree02_J3, TTTT ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree03_J3, QCD_HT200to300 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree04_J3, QCD_HT300to500 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree05_J3, QCD_HT500to700 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree06_J3, QCD_HT700to1000 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree07_J3, QCD_HT1000to1500 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree08_J3, QCD_HT1500to2000 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree09_J3, QCD_HT2000toIn ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree10_J3, TTJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree11_J3, TTWJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree12_J3, TTZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, TT ,plot,BIN,MIN,MAX);
      }
        else if(JETSyst==4){
       // GetHisto(CUT, Tree01_J4, data        ,plot,BIN,MIN,MAX);//from JERdo
        GetHisto(CUT, Tree02_J4, TTTT ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree03_J4, QCD_HT200to300 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree04_J4, QCD_HT300to500 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree05_J4, QCD_HT500to700 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree06_J4, QCD_HT700to1000 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree07_J4, QCD_HT1000to1500 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree08_J4, QCD_HT1500to2000 ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree09_J4, QCD_HT2000toIn ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree10_J4, TTJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree11_J4, TTWJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree12_J4, TTZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, TT ,plot,BIN,MIN,MAX);
      }
 // TH1F *background = new TH1F("","",data->GetNbinsX(),data->GetXaxis()->GetXmin(),data->GetXaxis()->GetXmax());
      TH1F *background = new TH1F("","",TTTT->GetNbinsX(),TTTT->GetXaxis()->GetXmin(),TTTT->GetXaxis()->GetXmax());
      //for(int j=1; j<data->GetNbinsX()+1; j++){
      for(int j=1; j<TTTT->GetNbinsX()+1; j++){
            //why do we reset the bin error?
        if(TTTT->GetBinContent(j)>0){TTTT->SetBinError(j,sqrt(wTTTT*wTTTT*TTTT->GetBinContent(j)));}else{TTTT->SetBinError(j,0);}
        if(QCD_HT200to300->GetBinContent(j)>0){QCD_HT200to300->SetBinError(j,sqrt(wQCD200to300*wQCD200to300*QCD_HT200to300->GetBinContent(j)));}else{QCD_HT200to300->SetBinError(j,0);}
        if(QCD_HT300to500->GetBinContent(j)>0){QCD_HT300to500->SetBinError(j,sqrt(wQCD300to500*wQCD300to500*QCD_HT300to500->GetBinContent(j)));}else{QCD_HT300to500->SetBinError(j,0);}
        if(QCD_HT500to700->GetBinContent(j)>0){QCD_HT500to700->SetBinError(j,sqrt(wQCD500to700*wQCD500to700*QCD_HT500to700->GetBinContent(j)));}else{QCD_HT500to700->SetBinError(j,0);}
        if(QCD_HT700to1000 ->GetBinContent(j)>0){QCD_HT700to1000 ->SetBinError(j,sqrt(wQCD700to1000*wQCD700to1000*QCD_HT700to1000 ->GetBinContent(j)));}else{QCD_HT700to1000 ->SetBinError(j,0);}
        if(QCD_HT1000to1500 ->GetBinContent(j)>0){QCD_HT1000to1500 ->SetBinError(j,sqrt(wQCD1000to1500*wQCD1000to1500*QCD_HT1000to1500 ->GetBinContent(j)));}else{QCD_HT1000to1500 ->SetBinError(j,0);}
        if(QCD_HT1500to2000 ->GetBinContent(j)>0){QCD_HT1500to2000 ->SetBinError(j,sqrt(wQCD1500to2000*wQCD1500to2000*QCD_HT1500to2000 ->GetBinContent(j)));}else{QCD_HT1500to2000 ->SetBinError(j,0);}
        if(QCD_HT2000toIn ->GetBinContent(j)>0){QCD_HT2000toIn ->SetBinError(j,sqrt(wQCD2000toIn*wQCD2000toIn*QCD_HT2000toIn ->GetBinContent(j)));}else{QCD_HT2000toIn ->SetBinError(j,0);}
        if(TTJets ->GetBinContent(j)>0){TTJets ->SetBinError(j,sqrt(wTTJets*wTTJets*TTJets ->GetBinContent(j)));}else{TTJets ->SetBinError(j,0);}//wTTJets);}
        if(TTWJets ->GetBinContent(j)>0){TTWJets ->SetBinError(j,sqrt(wTTWJets*wTTWJets*TTWJets ->GetBinContent(j)));}else{TTWJets ->SetBinError(j,0);}//wTTWJets);}
        if(TTZ ->GetBinContent(j)>0){TTZ ->SetBinError(j,sqrt(wTTZ*wTTZ*TTZ ->GetBinContent(j)));}else{TTZ ->SetBinError(j,0);}
        if(TT ->GetBinContent(j)>0){TT ->SetBinError(j,sqrt(wTT*wTT*TT ->GetBinContent(j)));}else{TT ->SetBinError(j,0);}

       // float errdata= data->GetBinError(j)*data->GetBinError(j);
        float errbg =
            + QCD_HT200to300->GetBinError(j)*QCD_HT200to300->GetBinError(j)
            + QCD_HT300to500->GetBinError(j)*QCD_HT300to500->GetBinError(j)
            + QCD_HT500to700->GetBinError(j)*QCD_HT500to700->GetBinError(j)
            + QCD_HT700to1000->GetBinError(j)*QCD_HT700to1000->GetBinError(j)
            + QCD_HT1000to1500->GetBinError(j)*QCD_HT1000to1500->GetBinError(j)
            + QCD_HT1500to2000->GetBinError(j)*QCD_HT1500to2000->GetBinError(j)
            + QCD_HT2000toIn->GetBinError(j)*QCD_HT2000toIn->GetBinError(j)
            + TTJets->GetBinError(j)*TTJets->GetBinError(j)
            + TTWJets->GetBinError(j)*TTWJets->GetBinError(j)
            + TTZ->GetBinError(j)*TTZ->GetBinError(j)
            + TT->GetBinError(j)*TT->GetBinError(j);
        background->SetBinError(j,sqrt(errbg));

        TTTT->SetBinContent(j,wTTTT*TTTT->GetBinContent(j));
        QCD_HT200to300->SetBinContent(j,wQCD200to300*QCD_HT200to300->GetBinContent(j));
        QCD_HT300to500->SetBinContent(j,wQCD300to500*QCD_HT300to500->GetBinContent(j));
        QCD_HT500to700->SetBinContent(j,wQCD500to700*QCD_HT500to700->GetBinContent(j));
        QCD_HT700to1000->SetBinContent(j,wQCD700to1000*QCD_HT700to1000->GetBinContent(j));
        QCD_HT1000to1500->SetBinContent(j,wQCD1000to1500*QCD_HT1000to1500->GetBinContent(j));
        QCD_HT1500to2000->SetBinContent(j,wQCD1500to2000*QCD_HT1500to2000->GetBinContent(j));
        QCD_HT2000toIn->SetBinContent(j,wQCD2000toIn*QCD_HT2000toIn->GetBinContent(j));
        TTJets->SetBinContent(j,wTTJets*TTJets->GetBinContent(j));
        TTWJets->SetBinContent(j,wTTWJets*TTWJets->GetBinContent(j));
        TTZ->SetBinContent(j,wTTZ*TTZ->GetBinContent(j));
        TT->SetBinContent(j,wTT*TT->GetBinContent(j));

        //float DATA = data->GetBinContent(j);
        float bkg0 =QCD_HT200to300->GetBinContent(j)+  QCD_HT300to500->GetBinContent(j)+ QCD_HT500to700->GetBinContent(j)+ QCD_HT700to1000->GetBinContent(j) + QCD_HT1000to1500->GetBinContent(j) + QCD_HT1500to2000->GetBinContent(j) + QCD_HT2000toIn->GetBinContent(j) + TTJets->GetBinContent(j) + TTWJets->GetBinContent(j) + TTZ->GetBinContent(j)+ TT->GetBinContent(j);

        background->SetBinContent(j,bkg0);//difinition at 936
    }

      //why clone then delete?
      background_func  = (TH1F*)background ->Clone(); 
    //  data_func        = (TH1F*)data       ->Clone(); 
      TTTT_func = (TH1F*)TTTT->Clone(); 
      QCD_HT200to300_func = (TH1F*)QCD_HT200to300->Clone(); 
      QCD_HT300to500_func = (TH1F*)QCD_HT300to500->Clone(); 
      QCD_HT500to700_func = (TH1F*)QCD_HT500to700->Clone(); 
      QCD_HT700to1000_func   = (TH1F*)QCD_HT700to1000->Clone(); 
      QCD_HT1000to1500_func   = (TH1F*)QCD_HT1000to1500->Clone(); 
      QCD_HT1500to2000_func   = (TH1F*)QCD_HT1500to2000->Clone();  
      QCD_HT2000toIn_func   = (TH1F*)QCD_HT2000toIn->Clone(); 
      TTJets_func   = (TH1F*)TTJets->Clone();
      TTWJets_func   = (TH1F*)TTWJets->Clone();
      TTZ_func   = (TH1F*)TTZ->Clone();
      TT_func   = (TH1F*)TT->Clone();

      //delete data;
      delete background;delete TTTT; delete QCD_HT200to300;delete QCD_HT300to500; delete QCD_HT500to700; delete QCD_HT700to1000; delete QCD_HT1000to1500; delete QCD_HT1500to2000; delete QCD_HT2000toIn;  delete TTJets;  delete TTWJets;  delete TTZ;  delete TT;
    
}

//reset histo_SR bin erro
//???
/*void MakeHistoErrors(int m, TH1F* &histo_SR, TH1F* histo_P1, TH1F* histo_P2, TH1F* histo_F1, TH1F* histo_F2, TH1F* histo_B1, TH1F* histo_B2, TH1F* histo_Z1, TH1F* histo_Z2, TH1F* histo_W1, TH1F* histo_W2, TH1F* histo_T1, TH1F* histo_T2, TH1F* histo_J1, TH1F* histo_J2, TH1F* histo_J3, TH1F* histo_J4, TH1F* histo_qcd1, TH1F* histo_qcd2, TH1F* histo_pdf1, TH1F* histo_pdf2, TH1F* histo_TR1, TH1F* histo_TR2){
  float ErrMc = histo_SR->GetBinError(m); 
  //??
  float ErrLU = 0.026*histo_SR->GetBinContent(m);
  //??
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
  float TOTAL = sqrt(ErrMc*ErrMc + ErrLU*ErrLU +  ErrPU*ErrPU + ErrFO*ErrFO + ErrBT*ErrBT  +ErrTR*ErrTR  + ErrZJ*ErrZJ + ErrWJ*ErrWJ + ErrTT*ErrTT+ ErrJS*ErrJS + ErrJR*ErrJR + ErrQCD*ErrQCD + ErrPDF*ErrPDF);
  //???why?
  histo_SR ->SetBinError(m,TOTAL);
}
*/

/*void CloneHistos(){
	data_P1 = (TH1F*)data_SR->Clone(); tptzm0700lh_P1 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_P1 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_P1 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_P1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_P1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_P1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_P1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_P1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_P1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_P1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_P1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_P1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_P1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_P1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_P1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_P1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_P1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_P1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_P1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_P1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_P1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_P1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_P1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_P1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_P1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_P1 = (TH1F*)TT_1_SR->Clone(); TT_2_P1 = (TH1F*)TT_2_SR->Clone(); ST_1_P1 = (TH1F*)ST_1_SR->Clone(); ST_2_P1 = (TH1F*)ST_2_SR->Clone();  ST_3_P1 = (TH1F*)ST_3_SR->Clone();  ST_4_P1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_P1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_P1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_P1 = (TH1F*)ZZ3_SR->Clone(); WW1_P1 = (TH1F*)WW1_SR->Clone(); WW2_P1 = (TH1F*)WW2_SR->Clone(); WZ1_P1 = (TH1F*)WZ1_SR->Clone(); WZ2_P1 = (TH1F*)WZ2_SR->Clone();  WZ3_P1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_P1 = (TH1F*)background_SR->Clone();
	ttW_P1 = (TH1F*)ttW_SR->Clone(); ttZ_P1 = (TH1F*)ttZ_SR->Clone(); tZq_P1 = (TH1F*)tZq_SR->Clone(); ZZ4_P1 = (TH1F*)ZZ4_SR->Clone(); WZ4_P1 = (TH1F*)WZ4_SR->Clone();

	data_P2 = (TH1F*)data_SR->Clone(); tptzm0700lh_P2 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_P2 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_P2 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_P2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_P2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_P2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_P2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_P2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_P2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_P2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_P2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_P2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_P2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_P2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_P2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_P2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_P2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_P2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_P2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_P2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_P2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_P2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_P2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_P2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_P2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_P2 = (TH1F*)TT_1_SR->Clone(); TT_2_P2 = (TH1F*)TT_2_SR->Clone(); ST_1_P2 = (TH1F*)ST_1_SR->Clone(); ST_2_P2 = (TH1F*)ST_2_SR->Clone();  ST_3_P2 = (TH1F*)ST_3_SR->Clone();  ST_4_P2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_P2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_P2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_P2 = (TH1F*)ZZ3_SR->Clone(); WW1_P2 = (TH1F*)WW1_SR->Clone();  WW2_P2 = (TH1F*)WW2_SR->Clone(); WZ1_P2 = (TH1F*)WZ1_SR->Clone(); WZ2_P2 = (TH1F*)WZ2_SR->Clone();  WZ3_P2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_P2 = (TH1F*)background_SR->Clone();
	ttW_P2 = (TH1F*)ttW_SR->Clone(); ttZ_P2 = (TH1F*)ttZ_SR->Clone(); tZq_P2 = (TH1F*)tZq_SR->Clone(); ZZ4_P2 = (TH1F*)ZZ4_SR->Clone(); WZ4_P2 = (TH1F*)WZ4_SR->Clone();

	data_F1 = (TH1F*)data_SR->Clone(); tptzm0700lh_F1 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_F1 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_F1 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_F1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_F1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_F1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_F1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_F1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_F1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_F1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_F1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_F1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_F1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_F1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_F1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_F1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_F1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_F1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_F1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_F1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_F1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_F1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_F1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_F1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_F1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_F1 = (TH1F*)TT_1_SR->Clone(); TT_2_F1 = (TH1F*)TT_2_SR->Clone(); ST_1_F1 = (TH1F*)ST_1_SR->Clone(); ST_2_F1 = (TH1F*)ST_2_SR->Clone();  ST_3_F1 = (TH1F*)ST_3_SR->Clone();  ST_4_F1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_F1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_F1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_F1 = (TH1F*)ZZ3_SR->Clone(); WW1_F1 = (TH1F*)WW1_SR->Clone();  WW2_F1 = (TH1F*)WW2_SR->Clone(); WZ1_F1 = (TH1F*)WZ1_SR->Clone(); WZ2_F1 = (TH1F*)WZ2_SR->Clone();  WZ3_F1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_F1 = (TH1F*)background_SR->Clone();
	ttW_F1 = (TH1F*)ttW_SR->Clone(); ttZ_F1 = (TH1F*)ttZ_SR->Clone(); tZq_F1 = (TH1F*)tZq_SR->Clone(); ZZ4_F1 = (TH1F*)ZZ4_SR->Clone(); WZ4_F1 = (TH1F*)WZ4_SR->Clone();

	data_F2 = (TH1F*)data_SR->Clone(); tptzm0700lh_F2 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_F2 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_F2 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_F2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_F2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_F2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_F2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_F2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_F2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_F2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_F2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_F2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_F2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_F2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_F2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_F2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_F2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_F2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_F2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_F2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_F2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_F2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_F2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_F2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_F2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_F2 = (TH1F*)TT_1_SR->Clone(); TT_2_F2 = (TH1F*)TT_2_SR->Clone(); ST_1_F2 = (TH1F*)ST_1_SR->Clone(); ST_2_F2 = (TH1F*)ST_2_SR->Clone();  ST_3_F2 = (TH1F*)ST_3_SR->Clone();  ST_4_F2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_F2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_F2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_F2 = (TH1F*)ZZ3_SR->Clone(); WW1_F2 = (TH1F*)WW1_SR->Clone();  WW2_F2 = (TH1F*)WW2_SR->Clone(); WZ1_F2 = (TH1F*)WZ1_SR->Clone(); WZ2_F2 = (TH1F*)WZ2_SR->Clone();  WZ3_F2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_F2 = (TH1F*)background_SR->Clone();
	ttW_F2 = (TH1F*)ttW_SR->Clone(); ttZ_F2 = (TH1F*)ttZ_SR->Clone(); tZq_F2 = (TH1F*)tZq_SR->Clone(); ZZ4_F2 = (TH1F*)ZZ4_SR->Clone(); WZ4_F2 = (TH1F*)WZ4_SR->Clone();

	data_B1 = (TH1F*)data_SR->Clone(); tptzm0700lh_B1 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_B1 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_B1 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_B1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_B1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_B1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_B1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_B1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_B1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_B1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_B1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_B1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_B1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_B1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_B1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_B1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_B1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_B1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_B1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_B1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_B1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_B1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_B1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_B1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_B1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_B1 = (TH1F*)TT_1_SR->Clone(); TT_2_B1 = (TH1F*)TT_2_SR->Clone(); ST_1_B1 = (TH1F*)ST_1_SR->Clone(); ST_2_B1 = (TH1F*)ST_2_SR->Clone();  ST_3_B1 = (TH1F*)ST_3_SR->Clone();  ST_4_B1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_B1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_B1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_B1 = (TH1F*)ZZ3_SR->Clone(); WW1_B1 = (TH1F*)WW1_SR->Clone();  WW2_B1 = (TH1F*)WW2_SR->Clone(); WZ1_B1 = (TH1F*)WZ1_SR->Clone(); WZ2_B1 = (TH1F*)WZ2_SR->Clone();  WZ3_B1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_B1 = (TH1F*)background_SR->Clone();
	ttW_B1 = (TH1F*)ttW_SR->Clone(); ttZ_B1 = (TH1F*)ttZ_SR->Clone(); tZq_B1 = (TH1F*)tZq_SR->Clone(); ZZ4_B1 = (TH1F*)ZZ4_SR->Clone(); WZ4_B1 = (TH1F*)WZ4_SR->Clone();

	data_B2 = (TH1F*)data_SR->Clone(); tptzm0700lh_B2 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_B2 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_B2 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_B2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_B2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_B2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_B2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_B2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_B2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_B2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_B2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_B2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_B2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_B2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_B2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_B2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_B2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_B2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_B2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_B2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_B2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_B2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_B2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_B2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_B2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_B2 = (TH1F*)TT_1_SR->Clone(); TT_2_B2 = (TH1F*)TT_2_SR->Clone(); ST_1_B2 = (TH1F*)ST_1_SR->Clone(); ST_2_B2 = (TH1F*)ST_2_SR->Clone();  ST_3_B2 = (TH1F*)ST_3_SR->Clone();  ST_4_B2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_B2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_B2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_B2 = (TH1F*)ZZ3_SR->Clone(); WW1_B2 = (TH1F*)WW1_SR->Clone();  WW2_B2 = (TH1F*)WW2_SR->Clone(); WZ1_B2 = (TH1F*)WZ1_SR->Clone(); WZ2_B2 = (TH1F*)WZ2_SR->Clone();  WZ3_B2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_B2 = (TH1F*)background_SR->Clone();
	ttW_B2 = (TH1F*)ttW_SR->Clone(); ttZ_B2 = (TH1F*)ttZ_SR->Clone(); tZq_B2 = (TH1F*)tZq_SR->Clone(); ZZ4_B2 = (TH1F*)ZZ4_SR->Clone(); WZ4_B2 = (TH1F*)WZ4_SR->Clone();

	data_Z1 = (TH1F*)data_SR->Clone(); tptzm0700lh_Z1 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_Z1 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_Z1 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_Z1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_Z1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_Z1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_Z1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_Z1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_Z1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_Z1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_Z1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_Z1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_Z1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_Z1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_Z1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_Z1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_Z1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_Z1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_Z1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_Z1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_Z1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_Z1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_Z1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_Z1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_Z1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_Z1 = (TH1F*)TT_1_SR->Clone(); TT_2_Z1 = (TH1F*)TT_2_SR->Clone(); ST_1_Z1 = (TH1F*)ST_1_SR->Clone(); ST_2_Z1 = (TH1F*)ST_2_SR->Clone();  ST_3_Z1 = (TH1F*)ST_3_SR->Clone();  ST_4_Z1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_Z1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_Z1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_Z1 = (TH1F*)ZZ3_SR->Clone(); WW1_Z1 = (TH1F*)WW1_SR->Clone();  WW2_Z1 = (TH1F*)WW2_SR->Clone(); WZ1_Z1 = (TH1F*)WZ1_SR->Clone(); WZ2_Z1 = (TH1F*)WZ2_SR->Clone();  WZ3_Z1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_Z1 = (TH1F*)background_SR->Clone();
	ttW_Z1 = (TH1F*)ttW_SR->Clone(); ttZ_Z1 = (TH1F*)ttZ_SR->Clone(); tZq_Z1 = (TH1F*)tZq_SR->Clone(); ZZ4_Z1 = (TH1F*)ZZ4_SR->Clone(); WZ4_Z1 = (TH1F*)WZ4_SR->Clone();

	data_Z2 = (TH1F*)data_SR->Clone(); tptzm0700lh_Z2 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_Z2 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_Z2 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_Z2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_Z2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_Z2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_Z2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_Z2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_Z2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_Z2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_Z2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_Z2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_Z2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_Z2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_Z2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_Z2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_Z2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_Z2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_Z2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_Z2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_Z2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_Z2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_Z2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_Z2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_Z2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_Z2 = (TH1F*)TT_1_SR->Clone(); TT_2_Z2 = (TH1F*)TT_2_SR->Clone(); ST_1_Z2 = (TH1F*)ST_1_SR->Clone(); ST_2_Z2 = (TH1F*)ST_2_SR->Clone();  ST_3_Z2 = (TH1F*)ST_3_SR->Clone();  ST_4_Z2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_Z2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_Z2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_Z2 = (TH1F*)ZZ3_SR->Clone(); WW1_Z2 = (TH1F*)WW1_SR->Clone();  WW2_Z2 = (TH1F*)WW2_SR->Clone(); WZ1_Z2 = (TH1F*)WZ1_SR->Clone(); WZ2_Z2 = (TH1F*)WZ2_SR->Clone();  WZ3_Z2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_Z2 = (TH1F*)background_SR->Clone();
	ttW_Z2 = (TH1F*)ttW_SR->Clone(); ttZ_Z2 = (TH1F*)ttZ_SR->Clone(); tZq_Z2 = (TH1F*)tZq_SR->Clone(); ZZ4_Z2 = (TH1F*)ZZ4_SR->Clone(); WZ4_Z2 = (TH1F*)WZ4_SR->Clone();

	data_W1 = (TH1F*)data_SR->Clone(); tptzm0700lh_W1 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_W1 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_W1 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_W1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_W1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_W1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_W1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_W1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_W1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_W1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_W1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_W1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_W1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_W1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_W1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_W1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_W1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_W1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_W1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_W1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_W1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_W1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_W1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_W1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_W1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_W1 = (TH1F*)TT_1_SR->Clone(); TT_2_W1 = (TH1F*)TT_2_SR->Clone(); ST_1_W1 = (TH1F*)ST_1_SR->Clone(); ST_2_W1 = (TH1F*)ST_2_SR->Clone();  ST_3_W1 = (TH1F*)ST_3_SR->Clone();  ST_4_W1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_W1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_W1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_W1 = (TH1F*)ZZ3_SR->Clone(); WW1_W1 = (TH1F*)WW1_SR->Clone();  WW2_W1 = (TH1F*)WW2_SR->Clone(); WZ1_W1 = (TH1F*)WZ1_SR->Clone(); WZ2_W1 = (TH1F*)WZ2_SR->Clone();  WZ3_W1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_W1 = (TH1F*)background_SR->Clone();
	ttW_W1 = (TH1F*)ttW_SR->Clone(); ttZ_W1 = (TH1F*)ttZ_SR->Clone(); tZq_W1 = (TH1F*)tZq_SR->Clone(); ZZ4_W1 = (TH1F*)ZZ4_SR->Clone(); WZ4_W1 = (TH1F*)WZ4_SR->Clone();

	data_W2 = (TH1F*)data_SR->Clone(); tptzm0700lh_W2 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_W2 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_W2 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_W2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_W2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_W2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_W2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_W2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_W2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_W2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_W2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_W2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_W2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_W2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_W2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_W2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_W2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_W2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_W2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_W2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_W2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_W2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_W2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_W2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_W2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_W2 = (TH1F*)TT_1_SR->Clone(); TT_2_W2 = (TH1F*)TT_2_SR->Clone(); ST_1_W2 = (TH1F*)ST_1_SR->Clone(); ST_2_W2 = (TH1F*)ST_2_SR->Clone();  ST_3_W2 = (TH1F*)ST_3_SR->Clone();  ST_4_W2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_W2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_W2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_W2 = (TH1F*)ZZ3_SR->Clone(); WW1_W2 = (TH1F*)WW1_SR->Clone();  WW2_W2 = (TH1F*)WW2_SR->Clone(); WZ1_W2 = (TH1F*)WZ1_SR->Clone(); WZ2_W2 = (TH1F*)WZ2_SR->Clone();  WZ3_W2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_W2 = (TH1F*)background_SR->Clone();
	ttW_W2 = (TH1F*)ttW_SR->Clone(); ttZ_W2 = (TH1F*)ttZ_SR->Clone(); tZq_W2 = (TH1F*)tZq_SR->Clone(); ZZ4_W2 = (TH1F*)ZZ4_SR->Clone(); WZ4_W2 = (TH1F*)WZ4_SR->Clone();

	data_T1 = (TH1F*)data_SR->Clone(); tptzm0700lh_T1 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_T1 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_T1 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_T1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_T1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_T1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_T1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_T1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_T1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_T1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_T1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_T1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_T1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_T1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_T1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_T1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_T1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_T1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_T1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_T1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_T1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_T1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_T1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_T1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_T1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_T1 = (TH1F*)TT_1_SR->Clone(); TT_2_T1 = (TH1F*)TT_2_SR->Clone(); ST_1_T1 = (TH1F*)ST_1_SR->Clone(); ST_2_T1 = (TH1F*)ST_2_SR->Clone();  ST_3_T1 = (TH1F*)ST_3_SR->Clone();  ST_4_T1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_T1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_T1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_T1 = (TH1F*)ZZ3_SR->Clone(); WW1_T1 = (TH1F*)WW1_SR->Clone();  WW2_T1 = (TH1F*)WW2_SR->Clone(); WZ1_T1 = (TH1F*)WZ1_SR->Clone(); WZ2_T1 = (TH1F*)WZ2_SR->Clone();  WZ3_T1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_T1 = (TH1F*)background_SR->Clone();
	ttW_T1 = (TH1F*)ttW_SR->Clone(); ttZ_T1 = (TH1F*)ttZ_SR->Clone(); tZq_T1 = (TH1F*)tZq_SR->Clone(); ZZ4_T1 = (TH1F*)ZZ4_SR->Clone(); WZ4_T1 = (TH1F*)WZ4_SR->Clone();

	data_T2 = (TH1F*)data_SR->Clone(); tptzm0700lh_T2 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_T2 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_T2 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_T2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_T2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_T2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_T2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_T2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_T2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_T2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_T2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_T2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_T2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_T2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_T2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_T2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_T2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_T2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_T2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_T2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_T2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_T2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_T2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_T2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_T2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_T2 = (TH1F*)TT_1_SR->Clone(); TT_2_T2 = (TH1F*)TT_2_SR->Clone(); ST_1_T2 = (TH1F*)ST_1_SR->Clone(); ST_2_T2 = (TH1F*)ST_2_SR->Clone();  ST_3_T2 = (TH1F*)ST_3_SR->Clone();  ST_4_T2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_T2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_T2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_T2 = (TH1F*)ZZ3_SR->Clone(); WW1_T2 = (TH1F*)WW1_SR->Clone();  WW2_T2 = (TH1F*)WW2_SR->Clone(); WZ1_T2 = (TH1F*)WZ1_SR->Clone(); WZ2_T2 = (TH1F*)WZ2_SR->Clone();  WZ3_T2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_T2 = (TH1F*)background_SR->Clone();
	ttW_T2 = (TH1F*)ttW_SR->Clone(); ttZ_T2 = (TH1F*)ttZ_SR->Clone(); tZq_T2 = (TH1F*)tZq_SR->Clone(); ZZ4_T2 = (TH1F*)ZZ4_SR->Clone(); WZ4_T2 = (TH1F*)WZ4_SR->Clone();
	
	data_J1 = (TH1F*)data_SR->Clone(); tptzm0700lh_J1 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_J1 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_J1 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_J1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_J1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_J1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_J1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_J1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_J1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_J1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_J1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_J1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_J1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_J1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_J1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_J1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_J1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_J1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_J1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_J1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_J1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_J1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_J1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_J1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_J1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_J1 = (TH1F*)TT_1_SR->Clone(); TT_2_J1 = (TH1F*)TT_2_SR->Clone(); ST_1_J1 = (TH1F*)ST_1_SR->Clone(); ST_2_J1 = (TH1F*)ST_2_SR->Clone();  ST_3_J1 = (TH1F*)ST_3_SR->Clone();  ST_4_J1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_J1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_J1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_J1 = (TH1F*)ZZ3_SR->Clone(); WW1_J1 = (TH1F*)WW1_SR->Clone();  WW2_J1 = (TH1F*)WW2_SR->Clone(); WZ1_J1 = (TH1F*)WZ1_SR->Clone(); WZ2_J1 = (TH1F*)WZ2_SR->Clone();  WZ3_J1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_J1 = (TH1F*)background_SR->Clone();
	ttW_J1 = (TH1F*)ttW_SR->Clone(); ttZ_J1 = (TH1F*)ttZ_SR->Clone(); tZq_J1 = (TH1F*)tZq_SR->Clone(); ZZ4_J1 = (TH1F*)ZZ4_SR->Clone(); WZ4_J1 = (TH1F*)WZ4_SR->Clone();

	data_J2 = (TH1F*)data_SR->Clone(); tptzm0700lh_J2 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_J2 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_J2 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_J2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_J2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_J2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_J2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_J2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_J2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_J2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_J2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_J2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_J2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_J2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_J2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_J2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_J2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_J2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_J2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_J2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_J2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_J2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_J2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_J2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_J2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_J2 = (TH1F*)TT_1_SR->Clone(); TT_2_J2 = (TH1F*)TT_2_SR->Clone(); ST_1_J2 = (TH1F*)ST_1_SR->Clone(); ST_2_J2 = (TH1F*)ST_2_SR->Clone();  ST_3_J2 = (TH1F*)ST_3_SR->Clone();  ST_4_J2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_J2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_J2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_J2 = (TH1F*)ZZ3_SR->Clone(); WW1_J2 = (TH1F*)WW1_SR->Clone();  WW2_J2 = (TH1F*)WW2_SR->Clone(); WZ1_J2 = (TH1F*)WZ1_SR->Clone(); WZ2_J2 = (TH1F*)WZ2_SR->Clone();  WZ3_J2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_J2 = (TH1F*)background_SR->Clone();
	ttW_J2 = (TH1F*)ttW_SR->Clone(); ttZ_J2 = (TH1F*)ttZ_SR->Clone(); tZq_J2 = (TH1F*)tZq_SR->Clone(); ZZ4_J2 = (TH1F*)ZZ4_SR->Clone(); WZ4_J2 = (TH1F*)WZ4_SR->Clone();

	data_J3 = (TH1F*)data_SR->Clone(); tptzm0700lh_J3 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_J3 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_J3 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_J3 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_J3 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_J3 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_J3 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_J3 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_J3 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_J3 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_J3 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_J3 = (TH1F*)QCD_1_SR->Clone(); QCD_2_J3 = (TH1F*)QCD_2_SR->Clone();  QCD_3_J3 = (TH1F*)QCD_3_SR->Clone();  QCD_4_J3 = (TH1F*)QCD_4_SR->Clone();  QCD_5_J3 = (TH1F*)QCD_5_SR->Clone();  QCD_6_J3 = (TH1F*)QCD_6_SR->Clone();  QCD_7_J3 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_J3 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_J3 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_J3 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_J3 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_J3 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_J3 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_J3 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_J3 = (TH1F*)TT_1_SR->Clone(); TT_2_J3 = (TH1F*)TT_2_SR->Clone(); ST_1_J3 = (TH1F*)ST_1_SR->Clone(); ST_2_J3 = (TH1F*)ST_2_SR->Clone();  ST_3_J3 = (TH1F*)ST_3_SR->Clone();  ST_4_J3 = (TH1F*)ST_4_SR->Clone();
	ZZ1_J3 = (TH1F*)ZZ1_SR->Clone(); ZZ2_J3 = (TH1F*)ZZ2_SR->Clone(); ZZ3_J3 = (TH1F*)ZZ3_SR->Clone(); WW1_J3 = (TH1F*)WW1_SR->Clone();  WW2_J3 = (TH1F*)WW2_SR->Clone(); WZ1_J3 = (TH1F*)WZ1_SR->Clone(); WZ2_J3 = (TH1F*)WZ2_SR->Clone();  WZ3_J3 = (TH1F*)WZ3_SR->Clone(); TH1F *background_J3 = (TH1F*)background_SR->Clone();
	ttW_J3 = (TH1F*)ttW_SR->Clone(); ttZ_J3 = (TH1F*)ttZ_SR->Clone(); tZq_J3 = (TH1F*)tZq_SR->Clone(); ZZ4_J3 = (TH1F*)ZZ4_SR->Clone(); WZ4_J3 = (TH1F*)WZ4_SR->Clone();

	data_J4 = (TH1F*)data_SR->Clone(); tptzm0700lh_J4 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_J4 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_J4 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_J4 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_J4 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_J4 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_J4 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_J4 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_J4 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_J4 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_J4 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_J4 = (TH1F*)QCD_1_SR->Clone(); QCD_2_J4 = (TH1F*)QCD_2_SR->Clone();  QCD_3_J4 = (TH1F*)QCD_3_SR->Clone();  QCD_4_J4 = (TH1F*)QCD_4_SR->Clone();  QCD_5_J4 = (TH1F*)QCD_5_SR->Clone();  QCD_6_J4 = (TH1F*)QCD_6_SR->Clone();  QCD_7_J4 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_J4 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_J4 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_J4 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_J4 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_J4 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_J4 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_J4 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_J4 = (TH1F*)TT_1_SR->Clone(); TT_2_J4 = (TH1F*)TT_2_SR->Clone(); ST_1_J4 = (TH1F*)ST_1_SR->Clone(); ST_2_J4 = (TH1F*)ST_2_SR->Clone();  ST_3_J4 = (TH1F*)ST_3_SR->Clone();  ST_4_J4 = (TH1F*)ST_4_SR->Clone();
	ZZ1_J4 = (TH1F*)ZZ1_SR->Clone(); ZZ2_J4 = (TH1F*)ZZ2_SR->Clone(); ZZ3_J4 = (TH1F*)ZZ3_SR->Clone(); WW1_J4 = (TH1F*)WW1_SR->Clone();  WW2_J4 = (TH1F*)WW2_SR->Clone(); WZ1_J4 = (TH1F*)WZ1_SR->Clone(); WZ2_J4 = (TH1F*)WZ2_SR->Clone();  WZ3_J4 = (TH1F*)WZ3_SR->Clone(); TH1F *background_J4 = (TH1F*)background_SR->Clone();
    ttW_J4 = (TH1F*)ttW_SR->Clone(); ttZ_J4 = (TH1F*)ttZ_SR->Clone(); tZq_J4 = (TH1F*)tZq_SR->Clone(); ZZ4_J4 = (TH1F*)ZZ4_SR->Clone(); WZ4_J4 = (TH1F*)WZ4_SR->Clone();

	data_qcd1 = (TH1F*)data_SR->Clone(); tptzm0700lh_qcd1 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_qcd1 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_qcd1 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_qcd1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_qcd1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_qcd1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_qcd1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_qcd1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_qcd1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_qcd1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_qcd1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_qcd1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_qcd1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_qcd1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_qcd1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_qcd1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_qcd1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_qcd1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_qcd1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_qcd1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_qcd1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_qcd1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_qcd1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_qcd1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_qcd1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_qcd1 = (TH1F*)TT_1_SR->Clone(); TT_2_qcd1 = (TH1F*)TT_2_SR->Clone(); ST_1_qcd1 = (TH1F*)ST_1_SR->Clone(); ST_2_qcd1 = (TH1F*)ST_2_SR->Clone();  ST_3_qcd1 = (TH1F*)ST_3_SR->Clone();  ST_4_qcd1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_qcd1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_qcd1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_qcd1 = (TH1F*)ZZ3_SR->Clone(); WW1_qcd1 = (TH1F*)WW1_SR->Clone(); WW2_qcd1 = (TH1F*)WW2_SR->Clone(); WZ1_qcd1 = (TH1F*)WZ1_SR->Clone(); WZ2_qcd1 = (TH1F*)WZ2_SR->Clone();  WZ3_qcd1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_qcd1 = (TH1F*)background_SR->Clone();
	ttW_qcd1 = (TH1F*)ttW_SR->Clone(); ttZ_qcd1 = (TH1F*)ttZ_SR->Clone(); tZq_qcd1 = (TH1F*)tZq_SR->Clone(); ZZ4_qcd1 = (TH1F*)ZZ4_SR->Clone(); WZ4_qcd1 = (TH1F*)WZ4_SR->Clone();

	data_qcd2 = (TH1F*)data_SR->Clone(); tptzm0700lh_qcd2 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_qcd2 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_qcd2 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_qcd2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_qcd2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_qcd2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_qcd2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_qcd2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_qcd2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_qcd2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_qcd2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_qcd2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_qcd2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_qcd2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_qcd2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_qcd2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_qcd2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_qcd2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_qcd2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_qcd2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_qcd2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_qcd2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_qcd2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_qcd2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_qcd2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_qcd2 = (TH1F*)TT_1_SR->Clone(); TT_2_qcd2 = (TH1F*)TT_2_SR->Clone(); ST_1_qcd2 = (TH1F*)ST_1_SR->Clone(); ST_2_qcd2 = (TH1F*)ST_2_SR->Clone();  ST_3_qcd2 = (TH1F*)ST_3_SR->Clone();  ST_4_qcd2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_qcd2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_qcd2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_qcd2 = (TH1F*)ZZ3_SR->Clone(); WW1_qcd2 = (TH1F*)WW1_SR->Clone(); WW2_qcd2 = (TH1F*)WW2_SR->Clone(); WZ1_qcd2 = (TH1F*)WZ1_SR->Clone(); WZ2_qcd2 = (TH1F*)WZ2_SR->Clone();  WZ3_qcd2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_qcd2 = (TH1F*)background_SR->Clone();
	ttW_qcd2 = (TH1F*)ttW_SR->Clone(); ttZ_qcd2 = (TH1F*)ttZ_SR->Clone(); tZq_qcd2 = (TH1F*)tZq_SR->Clone(); ZZ4_qcd2 = (TH1F*)ZZ4_SR->Clone(); WZ4_qcd2 = (TH1F*)WZ4_SR->Clone();


	data_pdf1 = (TH1F*)data_SR->Clone(); tptzm0700lh_pdf1 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_pdf1 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_pdf1 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_pdf1 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_pdf1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_pdf1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_pdf1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_pdf1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_pdf1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_pdf1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_pdf1 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_pdf1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_pdf1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_pdf1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_pdf1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_pdf1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_pdf1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_pdf1 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_pdf1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_pdf1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_pdf1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_pdf1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_pdf1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_pdf1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_pdf1 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_pdf1 = (TH1F*)TT_1_SR->Clone(); TT_2_pdf1 = (TH1F*)TT_2_SR->Clone(); ST_1_pdf1 = (TH1F*)ST_1_SR->Clone(); ST_2_pdf1 = (TH1F*)ST_2_SR->Clone();  ST_3_pdf1 = (TH1F*)ST_3_SR->Clone();  ST_4_pdf1 = (TH1F*)ST_4_SR->Clone();
	ZZ1_pdf1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_pdf1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_pdf1 = (TH1F*)ZZ3_SR->Clone(); WW1_pdf1 = (TH1F*)WW1_SR->Clone(); WW2_pdf1 = (TH1F*)WW2_SR->Clone(); WZ1_pdf1 = (TH1F*)WZ1_SR->Clone(); WZ2_pdf1 = (TH1F*)WZ2_SR->Clone();  WZ3_pdf1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_pdf1 = (TH1F*)background_SR->Clone();
	ttW_pdf1 = (TH1F*)ttW_SR->Clone(); ttZ_pdf1 = (TH1F*)ttZ_SR->Clone(); tZq_pdf1 = (TH1F*)tZq_SR->Clone(); ZZ4_pdf1 = (TH1F*)ZZ4_SR->Clone(); WZ4_pdf1 = (TH1F*)WZ4_SR->Clone();


	data_pdf2 = (TH1F*)data_SR->Clone(); tptzm0700lh_pdf2 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_pdf2 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_pdf2 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_pdf2 = (TH1F*)tptzm1700lh_SR->Clone();
	ZToNuNu_1_pdf2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_pdf2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_pdf2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_pdf2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_pdf2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_pdf2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_pdf2 = (TH1F*)ZToNuNu_7_SR->Clone();
	QCD_1_pdf2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_pdf2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_pdf2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_pdf2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_pdf2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_pdf2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_pdf2 = (TH1F*)QCD_7_SR->Clone();
	WToLNu_1_pdf2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_pdf2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_pdf2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_pdf2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_pdf2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_pdf2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_pdf2 = (TH1F*)WToLNu_7_SR->Clone();
	TT_1_pdf2 = (TH1F*)TT_1_SR->Clone(); TT_2_pdf2 = (TH1F*)TT_2_SR->Clone(); ST_1_pdf2 = (TH1F*)ST_1_SR->Clone(); ST_2_pdf2 = (TH1F*)ST_2_SR->Clone();  ST_3_pdf2 = (TH1F*)ST_3_SR->Clone();  ST_4_pdf2 = (TH1F*)ST_4_SR->Clone();
	ZZ1_pdf2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_pdf2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_pdf2 = (TH1F*)ZZ3_SR->Clone(); WW1_pdf2 = (TH1F*)WW1_SR->Clone(); WW2_pdf2 = (TH1F*)WW2_SR->Clone(); WZ1_pdf2 = (TH1F*)WZ1_SR->Clone(); WZ2_pdf2 = (TH1F*)WZ2_SR->Clone();  WZ3_pdf2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_pdf2 = (TH1F*)background_SR->Clone();
	ttW_pdf2 = (TH1F*)ttW_SR->Clone(); ttZ_pdf2 = (TH1F*)ttZ_SR->Clone(); tZq_pdf2 = (TH1F*)tZq_SR->Clone(); ZZ4_pdf2 = (TH1F*)ZZ4_SR->Clone(); WZ4_pdf2 = (TH1F*)WZ4_SR->Clone();

        data_TR1 = (TH1F*)data_SR->Clone(); tptzm0700lh_TR1 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_TR1 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_TR1 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_TR1 = (TH1F*)tptzm1700lh_SR->Clone();
        ZToNuNu_1_TR1 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_TR1 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_TR1 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_TR1 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_TR1 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_TR1 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_TR1 = (TH1F*)ZToNuNu_7_SR->Clone();
        QCD_1_TR1 = (TH1F*)QCD_1_SR->Clone(); QCD_2_TR1 = (TH1F*)QCD_2_SR->Clone();  QCD_3_TR1 = (TH1F*)QCD_3_SR->Clone();  QCD_4_TR1 = (TH1F*)QCD_4_SR->Clone();  QCD_5_TR1 = (TH1F*)QCD_5_SR->Clone();  QCD_6_TR1 = (TH1F*)QCD_6_SR->Clone();  QCD_7_TR1 = (TH1F*)QCD_7_SR->Clone();
        WToLNu_1_TR1 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_TR1 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_TR1 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_TR1 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_TR1 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_TR1 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_TR1 = (TH1F*)WToLNu_7_SR->Clone();
        TT_1_TR1 = (TH1F*)TT_1_SR->Clone(); TT_2_TR1 = (TH1F*)TT_2_SR->Clone(); ST_1_TR1 = (TH1F*)ST_1_SR->Clone(); ST_2_TR1 = (TH1F*)ST_2_SR->Clone();  ST_3_TR1 = (TH1F*)ST_3_SR->Clone();  ST_4_TR1 = (TH1F*)ST_4_SR->Clone();
        ZZ1_TR1 = (TH1F*)ZZ1_SR->Clone(); ZZ2_TR1 = (TH1F*)ZZ2_SR->Clone(); ZZ3_TR1 = (TH1F*)ZZ3_SR->Clone(); WW1_TR1 = (TH1F*)WW1_SR->Clone(); WW2_TR1 = (TH1F*)WW2_SR->Clone(); WZ1_TR1 = (TH1F*)WZ1_SR->Clone(); WZ2_TR1 = (TH1F*)WZ2_SR->Clone();  WZ3_TR1 = (TH1F*)WZ3_SR->Clone(); TH1F *background_TR1 = (TH1F*)background_SR->Clone();
        ttW_TR1 = (TH1F*)ttW_SR->Clone(); ttZ_TR1 = (TH1F*)ttZ_SR->Clone(); tZq_TR1 = (TH1F*)tZq_SR->Clone(); ZZ4_TR1 = (TH1F*)ZZ4_SR->Clone(); WZ4_TR1 = (TH1F*)WZ4_SR->Clone();

        data_TR2 = (TH1F*)data_SR->Clone(); tptzm0700lh_TR2 = (TH1F*)tptzm0700lh_SR->Clone(); tptzm0900lh_TR2 = (TH1F*)tptzm0900lh_SR->Clone(); tptzm1400lh_TR2 = (TH1F*)tptzm1400lh_SR->Clone(); tptzm1700lh_TR2 = (TH1F*)tptzm1700lh_SR->Clone();
        ZToNuNu_1_TR2 = (TH1F*)ZToNuNu_1_SR->Clone(); ZToNuNu_2_TR2 = (TH1F*)ZToNuNu_2_SR->Clone();  ZToNuNu_3_TR2 = (TH1F*)ZToNuNu_3_SR->Clone();  ZToNuNu_4_TR2 = (TH1F*)ZToNuNu_4_SR->Clone();  ZToNuNu_5_TR2 = (TH1F*)ZToNuNu_5_SR->Clone();  ZToNuNu_6_TR2 = (TH1F*)ZToNuNu_6_SR->Clone();  ZToNuNu_7_TR2 = (TH1F*)ZToNuNu_7_SR->Clone();
        QCD_1_TR2 = (TH1F*)QCD_1_SR->Clone(); QCD_2_TR2 = (TH1F*)QCD_2_SR->Clone();  QCD_3_TR2 = (TH1F*)QCD_3_SR->Clone();  QCD_4_TR2 = (TH1F*)QCD_4_SR->Clone();  QCD_5_TR2 = (TH1F*)QCD_5_SR->Clone();  QCD_6_TR2 = (TH1F*)QCD_6_SR->Clone();  QCD_7_TR2 = (TH1F*)QCD_7_SR->Clone();
        WToLNu_1_TR2 = (TH1F*)WToLNu_1_SR->Clone(); WToLNu_2_TR2 = (TH1F*)WToLNu_2_SR->Clone();  WToLNu_3_TR2 = (TH1F*)WToLNu_3_SR->Clone();  WToLNu_4_TR2 = (TH1F*)WToLNu_4_SR->Clone();  WToLNu_5_TR2 = (TH1F*)WToLNu_5_SR->Clone();  WToLNu_6_TR2 = (TH1F*)WToLNu_6_SR->Clone();  WToLNu_7_TR2 = (TH1F*)WToLNu_7_SR->Clone();
        TT_1_TR2 = (TH1F*)TT_1_SR->Clone(); TT_2_TR2 = (TH1F*)TT_2_SR->Clone(); ST_1_TR2 = (TH1F*)ST_1_SR->Clone(); ST_2_TR2 = (TH1F*)ST_2_SR->Clone();  ST_3_TR2 = (TH1F*)ST_3_SR->Clone();  ST_4_TR2 = (TH1F*)ST_4_SR->Clone();
        ZZ1_TR2 = (TH1F*)ZZ1_SR->Clone(); ZZ2_TR2 = (TH1F*)ZZ2_SR->Clone(); ZZ3_TR2 = (TH1F*)ZZ3_SR->Clone(); WW1_TR2 = (TH1F*)WW1_SR->Clone(); WW2_TR2 = (TH1F*)WW2_SR->Clone(); WZ1_TR2 = (TH1F*)WZ1_SR->Clone(); WZ2_TR2 = (TH1F*)WZ2_SR->Clone();  WZ3_TR2 = (TH1F*)WZ3_SR->Clone(); TH1F *background_TR2 = (TH1F*)background_SR->Clone();
        ttW_TR2 = (TH1F*)ttW_SR->Clone(); ttZ_TR2 = (TH1F*)ttZ_SR->Clone(); tZq_TR2 = (TH1F*)tZq_SR->Clone(); ZZ4_TR2 = (TH1F*)ZZ4_SR->Clone(); WZ4_TR2 = (TH1F*)WZ4_SR->Clone();
}*/
