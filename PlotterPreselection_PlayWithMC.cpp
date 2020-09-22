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
#include "TString.h"
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
//?is there a more clever way to push_back all in a loop? 
 name.push_back("InvariantMassJets");      bin.push_back(100);     Min.push_back(0);    Max.push_back(4000);    axis.push_back("Invariant mass of jets");/*{{{*/
  name.push_back("Centrality");      bin.push_back(100);     Min.push_back(0);    Max.push_back(4);    axis.push_back("Centrality");
//// //// name.push_back("Aplanarity");      bin.push_back(100);     Min.push_back(-0.5);    Max.push_back(2000);    axis.push_back("Aplanarity");
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
 // name.push_back("FifthBJetPt");      bin.push_back(100);     Min.push_back(-100);    Max.push_back(800);    axis.push_back("Fifth B Jet Pt");
  name.push_back("MinDeltaRJets");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2.5);    axis.push_back("Min delta R of Jets");
  name.push_back("MaxDeltaRJets");      bin.push_back(100);     Min.push_back(2);    Max.push_back(6);    axis.push_back("Maximum delta R of Jets");
  name.push_back("MinDeltaRBJets");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5);    axis.push_back("Min delta R of B Jets");
  name.push_back("MaxDeltaRBJets");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5);    axis.push_back("Maximum delta R of B Jets");
  name.push_back("NumSelJets");      bin.push_back(12);     Min.push_back(0);    Max.push_back(13);    axis.push_back("Number of jets");
  name.push_back("NumSelBJetsM");      bin.push_back(6);     Min.push_back(0);    Max.push_back(6);    axis.push_back("Number of medium b jets");
 //name.push_back("NVertices"); bin.push_back(80);     Min.push_back(0);    Max.push_back(100);    axis.push_back("Number of vertices");
 name.push_back("HT"); bin.push_back(100);     Min.push_back(0);    Max.push_back(2200);    axis.push_back("HT pt[GeV]");
 name.push_back("MHT"); bin.push_back(100);     Min.push_back(0);    Max.push_back(500);    axis.push_back("MHT pt[GeV]");
 name.push_back("Met_pt");  bin.push_back(100);     Min.push_back(0);    Max.push_back(400);   axis.push_back("Met pt[GeV] ");
// name.push_back("Met_phi"); bin.push_back(8);     Min.push_back(-4);   Max.push_back(-4);      axis.push_back("Met #phi");

  name.push_back("LeadingLeptonPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(400);    axis.push_back("Leading lepton pt");
  name.push_back("SecondLeptonPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(200);    axis.push_back("Second lepton pt");
  name.push_back("ThirdLeptonPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(100);    axis.push_back("Third lepton pt");
  name.push_back("LeadingTauPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(800);    axis.push_back("Leading tau pt");
  name.push_back("SecondTauPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(300);    axis.push_back("Second tau pt");
  name.push_back("NumofTops");      bin.push_back(5);     Min.push_back(0);    Max.push_back(5);    axis.push_back("Number of tops");
  name.push_back("LeadingTopPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(800);    axis.push_back("Leading top pt");
  name.push_back("SecondTopPt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(500);    axis.push_back("Second top pt");
//  name.push_back("");      bin.push_back(11);     Min.push_back(-0.5);    Max.push_back(10.5);    axis.push_back("");
//  name.push_back("");      bin.push_back(11);     Min.push_back(-0.5);    Max.push_back(10.5);    axis.push_back("");/*}}}*/
//
	  char CUT[1000]; char CUTpre[1000]; char CUTpup1[1000]; char CUTpup2[1000]; char CUTbta1[1000]; char CUTbta2[1000];  char CUTfor1[1000]; char CUTfor2[1000]; char CUTwje1[1000]; char CUTwje2[1000]; char CUTzje1[1000];  char CUTzje2[1000];  char CUTttb1[1000];  char CUTttb2[1000];  char CUTfir1[1000];  char CUTfir2[1000];char CUTqcd1[1000]; char CUTqcd2[1000];char CUTpdf1[1000]; char CUTpdf2[1000]; char CUTtri1[1000]; char CUTtri2[1000];
	  //apply selection cuts here
      //
//    sprintf(CUTpre,"((NumOfTausL>0))");
//    sprintf(CUTpre,"((channel_2Tau0L==1))");   TString postfix = "2Tau0L.png";
//    sprintf(CUTpre,"((channel_2Tau1L==1))");   TString postfix = "2Tau1L.png";
//vector<string> Channel = {"1Tau0L_v2","1Tau1L_v2","1Tau1E_v2","1Tau1Mu","1Tau2OS", "1Tau2SS", "1Tau3L", "2Tau1L","2Tau2OS","2Tau2SS"   };
//vector<string> Channel = { "1Tau0L"   };
vector<string> Channel = { "2Tau0L_v2"   };
for ( string ch : Channel){
//    char chann[100] = channel+"==1";
    TString postfix = ch + ".png";
    ch = "channel_"+ ch + "==1";
    const char*    channel= ch.c_str();//.c_str() returns a const char*
//   sprintf(CUTpre,channel);
   sprintf(CUTpre,"%s", channel);
    /*{{{*/
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
//  for(int i=0; i<name.size(); i++){
  for(UInt_t i=0; i<name.size(); i++){
	  const char *plot = name[i];
	MakeHistos(CUT,plot,bin[i],Min[i],Max[i],0,/*data_SR,*/background_SR, TTJets_SR,    TTGJets_SR,  ttZJets_SR,   ttWJets_SR,   ttH_SR,   ttbb_SR,   	   WZ_SR, /*  WW_SR,  */WWTo2L2Nu_SR, WpWpJJ_SR,   ZZ_SR, WGJets_SR, ZGJetsToLLG_SR, WWW_SR, WWZ_SR, WWG_SR, ZZZ_SR, WZZ_SR, WZG_SR, WGG_SR,ZGGJets_SR, WJetsToLNu_SR,          DYJetsToTauTau_SR, tZq_ll_SR,ST_tW_antitop_SR, ST_tW_top_SR, TGJets_SR,THW_SR, 
 THQ_SR,VHToNonbb_SR, ZHToTauTau_SR, ZH_HToBB_ZToLL_SR, GluGluHToZZTo4L_SR, GluGluHToBB_SR, GluGluHToGG_SR,       GluGluHToMuMu_SR, GluGluHToTauTau_SR, GluGluHToWWTo2L2Nu_SR, GluGluHToWWToLNuQQ_SR,VBFHToWWTo2L2Nu_SR,       VBFHToGG_SR, 
   TTTT_SR );//682
//?need to simply this. or add all this samples would be very time cosuming

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
		Double_t TTJetsErr   = 0; Float_t TTJetsYield = TTJets_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),TTJetsErr,"");
		Double_t TTGJetsErr   = 0; Float_t TTGJetsYield = TTGJets_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),TTGJetsErr,"");
		Double_t ttZJetsErr   = 0; Float_t ttZJetsYield = ttZJets_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),ttZJetsErr,"");
		Double_t ttWJetsErr   = 0; Float_t ttWJetsYield = ttWJets_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),ttWJetsErr,"");
		Double_t ttbbErr   = 0; Float_t ttbbYield = ttbb_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),ttbbErr,"");
		Double_t WZErr   = 0; Float_t WZYield = WZ_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),WZErr,"");
//		Double_t ttHErr   = 0; Float_t ttHYield = ttH_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),ttHErr,"");
//		Double_t WWErr   = 0; Float_t WWYield = WW_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),WWErr,"");
		Double_t WpWpJJErr = 0; Float_t WpWpJJYield = WpWpJJ_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),WpWpJJErr,"");
		Double_t ZZErr = 0; Float_t ZZYield = ZZ_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),ZZErr,"");
		Double_t TTTT_Err= 0; Float_t TTTT_Yield = TTTT_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),TTTT_Err,"");
        //?why not use result of this?

    if(i==0){
      cout<<endl;
      cout<<"Plotting "<<name[i]<<endl;
    //  cout<<"DATA      = "<<data_SR->Integral()<<" +/- "<<dataErr<<endl;/*{{{*/
      cout<<"TTJets   = "<<TTJets_SR->Integral()<<" +/- "<<	sqrt(TTJetsErr*TTJetsErr)<<endl;
//	  cout<<"WpWpJJ    = "<<WpWpJJ_SR->Integral()<<" +/- "<<sqrt(WpWpJJErr*WpWpJJErr)<<endl;
//	  cout<<"ZZ       = "<<ZZ_SR->Integral()<<" +/- "<<sqrt(ZZErr*ZZErr)<<endl;
//	  cout<<"TT       = "<<TT_SR->Integral()<<" +/- "<<sqrt(TTErr*TTErr)<<endl;

	  cout<<"Total BKG = "<<TTJets_SR->Integral()
          +TTGJets_SR->Integral()
          +ttZJets_SR->Integral()+ttWJets_SR->Integral()+ttbb_SR->Integral()+WZ_SR->Integral()
//          +ttH_SR->Integral()
//          +WW_SR->Integral()+WpWpJJ_SR->Integral()
          +ZZ_SR->Integral()
//          +TT_SR->Integral()<<
//           " +/- "<<sqrt(TTJetsErr*TTJetsErr
                  +TTGJetsErr*TTGJetsErr;
  //                +ttZJetsErr*ttZJetsErr+ttWJetsErr*ttWJetsErr+ttbbErr*ttbbErr+WZErr*WZErr/*+ttHErr*ttHErr+WWErr*WWErr+WpWpJJErr*WpWpJJErr+ZZErr*ZZErr*/)<<endl;
      cout<<"TTTT = "<<TTTT_SR->Integral()<<" +/- "<<sqrt(TTTT_Err*TTTT_Err)<<"or"<<TTTT_Yield<<endl;
	  cout<<"Total BKG = "<<background_SR->Integral()<<endl;
      
	}/*}}}*/

    TCanvas* c1 = new TCanvas("c1","c1",0,0,600,600);
		TTTT_SR->SetLineWidth(2);
        /*{{{*/
		TTTT_SR->SetLineColor(2);
		TTJets_SR->SetLineWidth(2); 
        TTGJets_SR->SetLineWidth(2);
        ttZJets_SR->SetLineWidth(2); ttWJets_SR->SetLineWidth(2); ttbb_SR->SetLineWidth(2); WZ_SR->SetLineWidth(2); 
        //ttH_SR->SetLineWidth(2);
//		WW_SR->SetLineWidth(2);
		WpWpJJ_SR->SetLineWidth(2);
//		ZZ_SR->SetLineWidth(2);
//		TT_SR->SetLineWidth(2);

		TTJets_SR->SetLineColor(kOrange); 
        TTGJets_SR->SetLineColor(kOrange);
        ttZJets_SR->SetLineColor(kOrange); ttWJets_SR->SetLineColor(kOrange); ttbb_SR->SetLineColor(kOrange); WZ_SR->SetLineColor(kOrange); 
//        ttH_SR->SetLineColor(kOrange);
//		WW_SR->SetLineColor(kGreen-3);
		WpWpJJ_SR->SetLineColor(kCyan-4);
//		ZZ_SR->SetLineColor(kGreen+3); 
//		TT_SR->SetLineColor(kGreen-4); 

		TTJets_SR->SetFillColor(kOrange); 
        TTGJets_SR->SetFillColor(kOrange);
        ttZJets_SR->SetFillColor(kOrange); ttWJets_SR->SetFillColor(kOrange); ttbb_SR->SetFillColor(kOrange); WZ_SR->SetFillColor(kOrange); 
//        ttH_SR->SetFillColor(kOrange);
	//	WW_SR->SetFillColor(kGreen-3);
	//	WpWpJJ_SR->SetFillColor(kCyan-4);
	//	ZZ_SR->SetFillColor(kGreen+3);

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
//    TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.30,0.99,0.90);// bottom left point(),
    TPad *c1_2 = new TPad("c1_2", "newpad",0.02,0.10,0.99,0.90);// bottom left point(),
    c1_2->Draw();
    c1_2->cd();
   // c1_2->SetTopMargin(0.08);
   // c1_2->SetBottomMargin(0.02);
   // c1_2->SetRightMargin(0.035);
   // c1_2->SetLeftMargin(0.20);
 /* 
   // THStack *hs = new THStack("hs","hs");
    TH1::SetDefaultSumw2();
    TH1F *hs = new TH1F("hs","h1+h2",bin[i],Min[i],Max[i]);
    //hs->Add(ZZ_SR);
    //hs->Add(WpWpJJ_SR);
    //hs->Add(TTJets_SR);
   hs->Add(TTJets_SR);
    hs->Add(TTGJets_SR);
    hs->Add(ttZJets_SR);
    hs->Add(ttWJets_SR);
    hs->Add(ttbb_SR);
    hs->Add(WZ_SR);
    hs->Add(ttH_SR);
//    hs->Add(WW_SR,TTGJets_SR,1,1);//TTG
    hs->Add(TTJets_SR,ttZJets_SR,1,1);//TTG
//    hs->Add(ttZJets_SR,1);
//    hs->Add(ttWJets_SR,1);
//    hs->Add(ttH_SR,1);
//    hs->Add(ttbb_SR,1);
//    hs->Add(WZ_SR,1);
	
    
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
    */
   // TTTT_SR->Draw("samehisto");
   //
    TTTT_SR->SetMinimum(0);
//    hs->SetMaximum(1);
    TTTT_SR->SetMaximum(3 * TTTT_SR->GetMaximum());
    TTTT_SR->GetYaxis()->SetTitleSize(0.050);
    TTTT_SR->GetXaxis()->SetTitleSize(0.050);
    TTTT_SR->GetYaxis()->SetLabelSize(0.040);
    TTTT_SR->GetXaxis()->SetLabelSize(0.040); 
    TTTT_SR->SetTitle("");
    TTTT_SR->GetYaxis()->SetTitle("Events");
    TTTT_SR->GetXaxis()->SetTitle(axis[i]);
    TTTT_SR->GetYaxis()->SetTitleOffset(1.00);
    TTTT_SR->GetXaxis()->SetTitleOffset(0.85);//Set distance between the axis and the axis title
    TTTT_SR->DrawNormalized("hist", 1);
//    TTTT_SR->DrawNormalized("samehist", 1);
   // TTJets_SR->Draw("samehisto");
  //  WpWpJJ_SR->Draw("samehisto");
//    ZZ_SR->Draw("samehisto");
	background_SR->SetLineWidth(2);
	background_SR->SetLineColor(kViolet-2); 
   // background_SR->Draw("samehisto");
    background_SR->DrawNormalized("samehist", 1);
   /* 
    //TH1F * TTX = TTJets_SR + WpWpJJ_SR + ZZ_SR;
    TH1D *TTX = new TH1D("TTX","h1+h2",bin[i],Min[i],Max[i]);
    TTX->Add(ZZ_SR,WpWpJJ_SR,1,1);
//    TTX->Add(TTJets_SR,WpWpJJ_SR,1,1);
//    TTX->Add(ZZ_SR,1);
	TTX->SetLineWidth(2);
	TTX->SetLineColor(kAzure); 
//    TTX->Draw("samehisto");
    TTX->DrawNormalized("samehist", 1);
//	TT_SR->SetLineWidth(2);
//	TT_SR->SetLineColor(kOrange); 
//    TTX->Draw("samehisto");
    //TT_SR->DrawNormalized("samehist", 1);
*/
   // TTJets_SR->Draw("samehisto");
   // WpWpJJ_SR->Draw("samehisto");
   // ZZ_SR->Draw("samehisto");
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
    lumi_13TeV = "35.9fb^{-1}";
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
//    ple2 = pl2->AddEntry(hs, "TTX",  "L");
   // ple2 = pl2->AddEntry(TTJets_SR, "TTJets",  "L");
   // ple2 = pl2->AddEntry(WpWpJJ_SR, "WpWpJJ",  "L");
   // ple2 = pl2->AddEntry(ZZ_SR, "ZZ",  "L");
//    ple2 = pl2->AddEntry(TTX, "TTX",  "L");
//    ple2 = pl2->AddEntry(TT_SR, "TT",  "L");
    ple2 = pl2->AddEntry(background_SR, "background",  "L");
    pl2->Draw();
    
    TString NAME = name[i];
   //c1->SaveAs(NAME+".pdf");
   // c1->SaveAs("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v1/reslult1/"+NAME+".pdf");
//    c1->SaveAs("/publicfs/cms/user/huahuil/FourTop/2016v1/PlayWithMC_RemoveHLT_PFHT900/MC_NormalizedRmTTJets/"+NAME+".png");
//    c1->SaveAs("/publicfs/cms/user/huahuil/FourTop/2016v1/PlayWithMC_RemoveHLT_PFHT900/MC_NormalizedRmTTJets/"+NAME+".eps");
//    c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v1_NewNtupleAfterEventSelection/Plots_test/"+NAME+".png");
//    c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v2_NewNtupleAfterEventSelection/Plots_test/"+NAME+".png");
//    c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v2_NewNtupleAfterEventSelection/Plots/"+NAME+"1Tau3L.png");
    c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v3_NewNtupleAfterEventSelection/plots/"+NAME+postfix);
    cout<<"Finished "<<NAME+postfix<<endl;
//    c1->Draw(); 

  }
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
               /* TH1F* &data_func,*/TH1F* &background_func,TH1F* &TTJets_func,TH1F* &TTGJets_func,TH1F* &ttZJets_func,  TH1F*  &ttWJets_func,TH1F* &ttH_func,TH1F* &ttbb_func,TH1F* &WZ_func,
                /* TH1F* &WW_func,*/TH1F* &WWTo2L2Nu_func, TH1F* &WpWpJJ_func,TH1F* &ZZ_func,TH1F* &WGJets_func, TH1F* &ZGJetsToLLG_func, TH1F* &WWW_func,TH1F* &WWZ_func,TH1F* &WWG_func,TH1F* &ZZZ_func,TH1F* &WZZ_func,TH1F* &WZG_func, TH1F* &WGG_func,TH1F* &ZGGJets_func,TH1F* &WJetsToLNu_func,         TH1F* &DYJetsToTauTau_func, TH1F* &tZq_ll_func,TH1F* &ST_tW_antitop_func, TH1F* &ST_tW_top_func, TH1F* &TGJets_func,TH1F* &THW_func, TH1F* &THQ_func,TH1F* &VHToNonbb_func, TH1F* &ZHToTauTau_func, TH1F* &ZH_HToBB_ZToLL_func, TH1F* &GluGluHToZZTo4L_func, TH1F* &GluGluHToBB_func, TH1F* &GluGluHToGG_func, TH1F* &GluGluHToMuMu_func, TH1F* &GluGluHToTauTau_func, TH1F* &GluGluHToWWTo2L2Nu_func, TH1F* &GluGluHToWWToLNuQQ_func,TH1F* &VBFHToWWTo2L2Nu_func,TH1F* &VBFHToGG_func,  TH1F* &TTTT_func){
      //no background
     // TH1F *data;
      TH1F *TTTT;
      TH1F *TTJets;
      TH1F *TTGJets;
      TH1F *ttZJets;
      TH1F *ttWJets;
      TH1F *ttH;
      TH1F *ttbb;
      TH1F *WZ;
//      TH1F *WW;
      TH1F *WWTo2L2Nu;
      TH1F *WpWpJJ;
      TH1F *ZZ;
      TH1F* WGJets;
      TH1F* ZGJetsToLLG;
      TH1F* WWW;
      TH1F* WWZ;
      TH1F* WWG;
      TH1F* ZZZ;
      TH1F* WZZ;
      TH1F* WZG;
      TH1F* WGG;
      TH1F* ZGGJets;
      TH1F* WJetsToLNu;

      TH1F* DYJetsToTauTau;
      TH1F* tZq_ll;
//      TH1F* tZq_nunu;
      TH1F* ST_tW_antitop;
      TH1F* ST_tW_top;
      TH1F* TGJets;
      TH1F* THW;
      TH1F* THQ;
      TH1F* VHToNonbb;
      TH1F* ZHToTauTau;
      TH1F* ZH_HToBB_ZToLL;
      TH1F* GluGluHToZZTo4L;
      TH1F* GluGluHToBB;
      TH1F* GluGluHToGG;
      TH1F* GluGluHToMuMu;
      TH1F* GluGluHToTauTau;
      TH1F* GluGluHToWWTo2L2Nu;
      TH1F* GluGluHToWWToLNuQQ;
      TH1F* VBFHToWWTo2L2Nu;
      TH1F* VBFHToGG;
        //what is JETSyst?
        //given at each call of the function.0,1,2,3,or 4
      if(JETSyst==0){
       // GetHisto(CUT, Tree01, data        ,plot,BIN,MIN,MAX);//tree01 different number means different files' tree
        GetHisto(CUT, Tree02, TTTT ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree03, TTJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree04, TTGJets ,plot,BIN,MIN,MAX);////TTGJets
        GetHisto(CUT, Tree05, ttZJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree06, ttWJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree07, ttH ,plot,BIN,MIN,MAX);//ttH
        GetHisto(CUT, Tree08, ttbb ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree09, WZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree10, WW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree10_1, WWTo2L2Nu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree11, WpWpJJ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree12, ZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13, WGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree14, ZGJetsToLLG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree15, WWW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree16, WWZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree17, WWG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree18, ZZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree19, WZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree20, WZG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree21, WGG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree22, ZGGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree22, WJetsToLNu ,plot,BIN,MIN,MAX);

        GetHisto(CUT, Tree24, DYJetsToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree25, tZq_ll ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree26, tZq_nunu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree27, ST_tW_antitop ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree28, ST_tW_top ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree29, TGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree30, THW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree31, THQ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree32, VHToNonbb ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree33, ZHToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree34, ZH_HToBB_ZToLL ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree35, GluGluHToZZTo4L ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree36, GluGluHToBB ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree37, GluGluHToGG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree38, GluGluHToMuMu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree39, GluGluHToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree40, GluGluHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree41, GluGluHToWWToLNuQQ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree42, VBFHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree43, VBFHToGG ,plot,BIN,MIN,MAX);
      }
      /*
        else if(JETSyst==1){
       // GetHisto(CUT, Tree01_J1, data        ,plot,BIN,MIN,MAX);//J1 from JESup directory
        GetHisto(CUT, Tree02_J1, TTTT ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree03_J1, TTJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree04_J1, TTGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree05_J1, ttZJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree06_J1, ttWJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree07_J1, ttH ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree08_J1, ttbb ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree09_J1, WZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree10_J1, WW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree11_J1, WpWpJJ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree12_J1, ZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, WGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, ZGJetsToLLG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, WWW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, WWZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, WWG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, ZZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, WZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, WZG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, WGG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, ZGGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, WJetsToLNu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, DYJetsToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, tZq_ll ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, tZq_nunu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, ST_tW_antitop ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, ST_tW_top ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, TGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, THW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, THQ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, VHToNonbb ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, ZHToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, ZH_HToBB_ZToLL ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, GluGluHToZZTo4L ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, GluGluHToBB ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, GluGluHToGG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, GluGluHToMuMu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, GluGluHToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, GluGluHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, GluGluHToWWToLNuQQ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, VBFHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J1, VBFHToGG ,plot,BIN,MIN,MAX);
      }
        else if(JETSyst==2){
       // GetHisto(CUT, Tree01_J2, data        ,plot,BIN,MIN,MAX);//J2 from JESdo
        GetHisto(CUT, Tree02_J2, TTTT ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree03_J2, TTJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree04_J2, TTGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree05_J2, ttZJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree06_J2, ttWJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree07_J2, ttH ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree08_J2, ttbb ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree09_J2, WZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree10_J2, WW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree11_J2, WpWpJJ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree12_J2, ZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, WGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, ZGJetsToLLG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, WWW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, WWZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, WWG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, ZZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, WZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, WZG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, WGG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, ZGGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, WJetsToLNu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, DYJetsToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, tZq_ll ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, tZq_nunu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, ST_tW_antitop ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, ST_tW_top ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, TGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, THW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, THQ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, VHToNonbb ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, ZHToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, ZH_HToBB_ZToLL ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, GluGluHToZZTo4L ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, GluGluHToBB ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, GluGluHToGG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, GluGluHToMuMu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, GluGluHToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, GluGluHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, GluGluHToWWToLNuQQ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, VBFHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J2, VBFHToGG ,plot,BIN,MIN,MAX);
      }
        else if(JETSyst==3){
       // GetHisto(CUT, Tree01_J3, data        ,plot,BIN,MIN,MAX);//J3 from JERup
        GetHisto(CUT, Tree02_J3, TTTT ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree03_J3, TTJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree04_J3, TTGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree05_J3, ttZJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree06_J3, ttWJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree07_J3, ttH ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree08_J3, ttbb ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree09_J3, WZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree10_J3, WW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree11_J3, WpWpJJ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree12_J3, ZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, WGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, ZGJetsToLLG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, WWW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, WWZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, WWG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, ZZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, WZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, WZG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, WGG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, ZGGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, WJetsToLNu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, DYJetsToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, tZq_ll ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, tZq_nunu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, ST_tW_antitop ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, ST_tW_top ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, TGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, THW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, THQ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, VHToNonbb ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, ZHToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, ZH_HToBB_ZToLL ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, GluGluHToZZTo4L ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, GluGluHToBB ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, GluGluHToGG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, GluGluHToMuMu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, GluGluHToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, GluGluHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, GluGluHToWWToLNuQQ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, VBFHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J3, VBFHToGG ,plot,BIN,MIN,MAX);
      }
        else if(JETSyst==4){
       // GetHisto(CUT, Tree01_J4, data        ,plot,BIN,MIN,MAX);//from JERdo
        GetHisto(CUT, Tree02_J4, TTTT ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree03_J4, TTJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree04_J4, TTGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree05_J4, ttZJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree06_J4, ttWJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree07_J4, ttH ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree08_J4, ttbb ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree09_J4, WZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree10_J4, WW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree11_J4, WpWpJJ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree12_J4, ZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, WGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, ZGJetsToLLG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4,WWW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, WWZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, WWG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, ZZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, WZZ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, WZG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, WGG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, ZGGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, WJetsToLNu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, DYJetsToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, tZq_ll ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, tZq_nunu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, ST_tW_antitop ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, ST_tW_top ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, TGJets ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, THW ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, THQ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, VHToNonbb ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, ZHToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, ZH_HToBB_ZToLL ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, GluGluHToZZTo4L ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, GluGluHToBB ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, GluGluHToGG ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, GluGluHToMuMu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, GluGluHToTauTau ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, GluGluHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, GluGluHToWWToLNuQQ ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, VBFHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
        GetHisto(CUT, Tree13_J4, VBFHToGG ,plot,BIN,MIN,MAX);
      }
*/

 // TH1F *background = new TH1F("","",data->GetNbinsX(),data->GetXaxis()->GetXmin(),data->GetXaxis()->GetXmax());
      TH1F *background = new TH1F("","",TTTT->GetNbinsX(),TTTT->GetXaxis()->GetXmin(),TTTT->GetXaxis()->GetXmax());
      //for(int j=1; j<data->GetNbinsX()+1; j++){
      for(int j=1; j<TTTT->GetNbinsX()+1; j++){/*{{{*/
            //why do we reset the bin error?
        if(TTTT->GetBinContent(j)>0){TTTT->SetBinError(j,sqrt(wTTTT*wTTTT*TTTT->GetBinContent(j)));}else{TTTT->SetBinError(j,0);}
        if(TTJets->GetBinContent(j)>0){TTJets->SetBinError(j,sqrt(wTTJets*wTTJets*TTJets->GetBinContent(j)));}else{TTJets->SetBinError(j,0);}
        if(TTGJets->GetBinContent(j)>0){TTGJets->SetBinError(j,sqrt(wTTGJets*wTTGJets*TTGJets->GetBinContent(j)));}else{TTGJets->SetBinError(j,0);}
        if(ttZJets->GetBinContent(j)>0){ttZJets->SetBinError(j,sqrt(wttZJets*wttZJets*ttZJets->GetBinContent(j)));}else{ttZJets->SetBinError(j,0);}
        if(ttWJets ->GetBinContent(j)>0){ttWJets ->SetBinError(j,sqrt(wttWJets*wttWJets*ttWJets ->GetBinContent(j)));}else{ttWJets ->SetBinError(j,0);}
        if(ttH ->GetBinContent(j)>0){ttH ->SetBinError(j,sqrt(wttH*wttH*ttH ->GetBinContent(j)));}else{ttH ->SetBinError(j,0);}
        if(ttbb ->GetBinContent(j)>0){ttbb ->SetBinError(j,sqrt(wttbb*wttbb*ttbb ->GetBinContent(j)));}else{ttbb ->SetBinError(j,0);}
        if(WZ ->GetBinContent(j)>0){WZ ->SetBinError(j,sqrt(wWZ*wWZ*WZ ->GetBinContent(j)));}else{WZ ->SetBinError(j,0);}
//        if(WW ->GetBinContent(j)>0){WW ->SetBinError(j,sqrt(wWW*wWW*WW ->GetBinContent(j)));}else{WW ->SetBinError(j,0);}//wWW);}
        if(WWTo2L2Nu ->GetBinContent(j)>0){WWTo2L2Nu ->SetBinError(j,sqrt(wWWTo2L2Nu*wWWTo2L2Nu*WWTo2L2Nu ->GetBinContent(j)));}else{WWTo2L2Nu ->SetBinError(j,0);}//wWWTo2L2Nu);}
        if(WpWpJJ ->GetBinContent(j)>0){WpWpJJ ->SetBinError(j,sqrt(wWpWpJJ*wWpWpJJ*WpWpJJ ->GetBinContent(j)));}else{WpWpJJ ->SetBinError(j,0);}//wWpWpJJ);}
        if(ZZ ->GetBinContent(j)>0){ZZ ->SetBinError(j,sqrt(wZZ*wZZ*ZZ ->GetBinContent(j)));}else{ZZ ->SetBinError(j,0);}
        if(WGJets ->GetBinContent(j)>0){WGJets ->SetBinError(j,sqrt(wWGJets*wWGJets*WGJets ->GetBinContent(j)));}else{WGJets ->SetBinError(j,0);}
        if(ZGJetsToLLG ->GetBinContent(j)>0){ZGJetsToLLG ->SetBinError(j,sqrt(wZGJetsToLLG*wZGJetsToLLG*ZGJetsToLLG ->GetBinContent(j)));}else{ZGJetsToLLG ->SetBinError(j,0);}
        if(WWW ->GetBinContent(j)>0){ WWW->SetBinError(j,sqrt(wWWW*wWWW* WWW->GetBinContent(j)));}else{ WWW->SetBinError(j,0);}
        if(WWZ ->GetBinContent(j)>0){WWZ ->SetBinError(j,sqrt(wWWZ*wWWZ*WWZ ->GetBinContent(j)));}else{WWZ ->SetBinError(j,0);}
        if(WWG ->GetBinContent(j)>0){WWG ->SetBinError(j,sqrt(wWWG*wWWG*WWG ->GetBinContent(j)));}else{WWG ->SetBinError(j,0);}
        if(ZZZ ->GetBinContent(j)>0){ZZZ ->SetBinError(j,sqrt(wZZZ*wZZZ*ZZZ ->GetBinContent(j)));}else{ZZZ ->SetBinError(j,0);}
        if(WZZ ->GetBinContent(j)>0){WZZ ->SetBinError(j,sqrt(wWZZ*wWZZ*WZZ ->GetBinContent(j)));}else{WZZ ->SetBinError(j,0);}
        if(WZG ->GetBinContent(j)>0){WZG ->SetBinError(j,sqrt(wWZG*wWZG*WZG ->GetBinContent(j)));}else{WZG ->SetBinError(j,0);}
        if(WGG ->GetBinContent(j)>0){WGG ->SetBinError(j,sqrt(wWGG*wWGG*WGG ->GetBinContent(j)));}else{WGG ->SetBinError(j,0);}
        if(ZGGJets ->GetBinContent(j)>0){ZGGJets ->SetBinError(j,sqrt(wZGGJets*wZGGJets*ZGGJets ->GetBinContent(j)));}else{ZGGJets ->SetBinError(j,0);}
        if(WJetsToLNu ->GetBinContent(j)>0){WJetsToLNu ->SetBinError(j,sqrt(wWJetsToLNu*wWJetsToLNu*WJetsToLNu ->GetBinContent(j)));}else{WJetsToLNu ->SetBinError(j,0);}
        if(DYJetsToTauTau ->GetBinContent(j)>0){DYJetsToTauTau ->SetBinError(j,sqrt(wDYJetsToTauTau*wDYJetsToTauTau*DYJetsToTauTau ->GetBinContent(j)));}else{DYJetsToTauTau ->SetBinError(j,0);}
        if(tZq_ll ->GetBinContent(j)>0){tZq_ll ->SetBinError(j,sqrt(wtZq_ll*wtZq_ll*tZq_ll ->GetBinContent(j)));}else{tZq_ll ->SetBinError(j,0);}
//        if(tZq_nunu ->GetBinContent(j)>0){tZq_nunu ->SetBinError(j,sqrt(wtZq_nunu*wtZq_nunu*tZq_nunu ->GetBinContent(j)));}else{tZq_nunu ->SetBinError(j,0);}
        if(ST_tW_antitop ->GetBinContent(j)>0){ST_tW_antitop ->SetBinError(j,sqrt(wST_tW_antitop*wST_tW_antitop*ST_tW_antitop ->GetBinContent(j)));}else{ST_tW_antitop ->SetBinError(j,0);}
        if(ST_tW_top ->GetBinContent(j)>0){ST_tW_top ->SetBinError(j,sqrt(wST_tW_top*wST_tW_top*ST_tW_top ->GetBinContent(j)));}else{ST_tW_top ->SetBinError(j,0);}
        if(TGJets ->GetBinContent(j)>0){TGJets ->SetBinError(j,sqrt(wTGJets*wTGJets*TGJets ->GetBinContent(j)));}else{TGJets ->SetBinError(j,0);}
        if(THW ->GetBinContent(j)>0){THW ->SetBinError(j,sqrt(wTHW*wTHW*THW ->GetBinContent(j)));}else{THW ->SetBinError(j,0);}
        if(THQ ->GetBinContent(j)>0){THQ ->SetBinError(j,sqrt(wTHQ*wTHQ*THQ ->GetBinContent(j)));}else{THQ ->SetBinError(j,0);}
        if(VHToNonbb ->GetBinContent(j)>0){VHToNonbb ->SetBinError(j,sqrt(wVHToNonbb*wVHToNonbb*VHToNonbb ->GetBinContent(j)));}else{VHToNonbb ->SetBinError(j,0);}
        if(ZHToTauTau ->GetBinContent(j)>0){ZHToTauTau ->SetBinError(j,sqrt(wZHToTauTau*wZHToTauTau*ZHToTauTau ->GetBinContent(j)));}else{ZHToTauTau ->SetBinError(j,0);}
        if(ZH_HToBB_ZToLL ->GetBinContent(j)>0){ZH_HToBB_ZToLL ->SetBinError(j,sqrt(wZH_HToBB_ZToLL*wZH_HToBB_ZToLL*ZH_HToBB_ZToLL ->GetBinContent(j)));}else{ZH_HToBB_ZToLL ->SetBinError(j,0);}
        if(GluGluHToZZTo4L ->GetBinContent(j)>0){GluGluHToZZTo4L ->SetBinError(j,sqrt(wGluGluHToZZTo4L*wGluGluHToZZTo4L*GluGluHToZZTo4L ->GetBinContent(j)));}else{GluGluHToZZTo4L ->SetBinError(j,0);}
        if(GluGluHToBB ->GetBinContent(j)>0){GluGluHToBB ->SetBinError(j,sqrt(wGluGluHToBB*wGluGluHToBB*GluGluHToBB ->GetBinContent(j)));}else{GluGluHToBB ->SetBinError(j,0);}
        if(GluGluHToGG ->GetBinContent(j)>0){GluGluHToGG ->SetBinError(j,sqrt(wGluGluHToGG*wGluGluHToGG*GluGluHToGG ->GetBinContent(j)));}else{GluGluHToGG ->SetBinError(j,0);}
        if(GluGluHToMuMu ->GetBinContent(j)>0){GluGluHToMuMu ->SetBinError(j,sqrt(wGluGluHToMuMu*wGluGluHToMuMu*GluGluHToMuMu ->GetBinContent(j)));}else{GluGluHToMuMu ->SetBinError(j,0);}
        if(GluGluHToTauTau ->GetBinContent(j)>0){GluGluHToTauTau ->SetBinError(j,sqrt(wGluGluHToTauTau*wGluGluHToTauTau*GluGluHToTauTau ->GetBinContent(j)));}else{GluGluHToTauTau ->SetBinError(j,0);}
        if(GluGluHToWWTo2L2Nu ->GetBinContent(j)>0){GluGluHToWWTo2L2Nu ->SetBinError(j,sqrt(wGluGluHToWWTo2L2Nu*wGluGluHToWWTo2L2Nu*GluGluHToWWTo2L2Nu ->GetBinContent(j)));}else{GluGluHToWWTo2L2Nu ->SetBinError(j,0);}
        if(GluGluHToWWToLNuQQ ->GetBinContent(j)>0){GluGluHToWWToLNuQQ ->SetBinError(j,sqrt(wGluGluHToWWToLNuQQ*wGluGluHToWWToLNuQQ*GluGluHToWWToLNuQQ ->GetBinContent(j)));}else{GluGluHToWWToLNuQQ ->SetBinError(j,0);}
        if(VBFHToWWTo2L2Nu ->GetBinContent(j)>0){VBFHToWWTo2L2Nu ->SetBinError(j,sqrt(wVBFHToWWTo2L2Nu*wVBFHToWWTo2L2Nu*VBFHToWWTo2L2Nu ->GetBinContent(j)));}else{VBFHToWWTo2L2Nu ->SetBinError(j,0);}
        if(VBFHToGG ->GetBinContent(j)>0){VBFHToGG ->SetBinError(j,sqrt(wVBFHToGG*wVBFHToGG*VBFHToGG ->GetBinContent(j)));}else{VBFHToGG ->SetBinError(j,0);}

       // float errdata= data->GetBinError(j)*data->GetBinError(j);
        float errbg =
            + TTJets->GetBinError(j)*TTJets->GetBinError(j)
            + TTGJets->GetBinError(j)*TTGJets->GetBinError(j)
            + ttZJets->GetBinError(j)*ttZJets->GetBinError(j)
            + ttWJets->GetBinError(j)*ttWJets->GetBinError(j)
            + ttH->GetBinError(j)*ttH->GetBinError(j)
            + ttbb->GetBinError(j)*ttbb->GetBinError(j)
            + WZ->GetBinError(j)*WZ->GetBinError(j)
           // + WW->GetBinError(j)*WW->GetBinError(j)
            + WWTo2L2Nu->GetBinError(j)*WWTo2L2Nu->GetBinError(j)
            + WpWpJJ->GetBinError(j)*WpWpJJ->GetBinError(j)
            + ZZ->GetBinError(j)*ZZ->GetBinError(j)
            + WGJets->GetBinError(j)*WGJets->GetBinError(j)
            + ZGJetsToLLG->GetBinError(j)*ZGJetsToLLG->GetBinError(j)
            + WWW->GetBinError(j)*WWW->GetBinError(j)
            + WWZ->GetBinError(j)*WWZ->GetBinError(j)
            + WWG->GetBinError(j)*WWG->GetBinError(j)
            + ZZZ->GetBinError(j)*ZZZ->GetBinError(j)
            + WZZ->GetBinError(j)*WZZ->GetBinError(j)
            + WZG->GetBinError(j)*WZG->GetBinError(j)
            + WGG->GetBinError(j)*WGG->GetBinError(j)
            + WJetsToLNu->GetBinError(j)*WJetsToLNu->GetBinError(j)
            + ZGGJets->GetBinError(j)*ZGGJets->GetBinError(j)
            + DYJetsToTauTau->GetBinError(j)*DYJetsToTauTau->GetBinError(j)
            + tZq_ll->GetBinError(j)*tZq_ll->GetBinError(j)
//            + tZq_nunu->GetBinError(j)*tZq_nunu->GetBinError(j)
            + ST_tW_antitop->GetBinError(j)*ST_tW_antitop->GetBinError(j)
            + ST_tW_top->GetBinError(j)*ST_tW_top->GetBinError(j)
            + TGJets->GetBinError(j)*TGJets->GetBinError(j)
            + THW->GetBinError(j)*THW->GetBinError(j)
            + THQ->GetBinError(j)*THQ->GetBinError(j)
            + VHToNonbb->GetBinError(j)*VHToNonbb->GetBinError(j)
            + ZHToTauTau->GetBinError(j)*ZHToTauTau->GetBinError(j)
            + ZH_HToBB_ZToLL->GetBinError(j)*ZH_HToBB_ZToLL->GetBinError(j)
            + GluGluHToZZTo4L->GetBinError(j)*GluGluHToZZTo4L->GetBinError(j)
            + GluGluHToBB->GetBinError(j)*GluGluHToBB->GetBinError(j)
            + GluGluHToGG->GetBinError(j)*GluGluHToGG->GetBinError(j)
            + GluGluHToMuMu->GetBinError(j)*GluGluHToMuMu->GetBinError(j)
            + GluGluHToTauTau->GetBinError(j)*GluGluHToTauTau->GetBinError(j)
            + GluGluHToWWTo2L2Nu->GetBinError(j)*GluGluHToWWTo2L2Nu->GetBinError(j)
            + GluGluHToWWToLNuQQ->GetBinError(j)*GluGluHToWWToLNuQQ->GetBinError(j)
            + VBFHToWWTo2L2Nu->GetBinError(j)*VBFHToWWTo2L2Nu->GetBinError(j)
            + VBFHToGG->GetBinError(j)*VBFHToGG->GetBinError(j);
        background->SetBinError(j,sqrt(errbg));

        TTTT->SetBinContent(j,wTTTT*TTTT->GetBinContent(j));
        TTJets->SetBinContent(j,wTTJets*TTJets->GetBinContent(j));
        TTGJets->SetBinContent(j,wTTGJets*TTGJets->GetBinContent(j));
        ttZJets->SetBinContent(j,wttZJets*ttZJets->GetBinContent(j));
        ttWJets->SetBinContent(j,wttWJets*ttWJets->GetBinContent(j));
        ttH->SetBinContent(j,wttH*ttH->GetBinContent(j));
        ttbb->SetBinContent(j,wttbb*ttbb->GetBinContent(j));
        WZ->SetBinContent(j,wWZ*WZ->GetBinContent(j));
//        WW->SetBinContent(j,wWW*WW->GetBinContent(j));
        WWTo2L2Nu->SetBinContent(j,wWWTo2L2Nu*WWTo2L2Nu->GetBinContent(j));
        WpWpJJ->SetBinContent(j,wWpWpJJ*WpWpJJ->GetBinContent(j));
        ZZ->SetBinContent(j,wZZ*ZZ->GetBinContent(j));
        WGJets->SetBinContent(j,wWGJets*WGJets->GetBinContent(j));
        ZGJetsToLLG->SetBinContent(j,wZGJetsToLLG*ZGJetsToLLG->GetBinContent(j));
        WWW->SetBinContent(j,wWWW*WWW->GetBinContent(j));
        WWZ->SetBinContent(j,wWWZ*WWZ->GetBinContent(j));
        WWG->SetBinContent(j,wWWG*WWG->GetBinContent(j));
        ZZZ->SetBinContent(j,wZZZ*ZZZ->GetBinContent(j));
        WZZ->SetBinContent(j,wWZZ*WZZ->GetBinContent(j));
        WZG->SetBinContent(j,wWZG*WZG->GetBinContent(j));
        WGG->SetBinContent(j,wWGG*WGG->GetBinContent(j));
        ZGGJets->SetBinContent(j,wZGGJets*ZGGJets->GetBinContent(j));
        WJetsToLNu->SetBinContent(j,wWJetsToLNu*WJetsToLNu->GetBinContent(j));
        DYJetsToTauTau->SetBinContent(j,wDYJetsToTauTau*DYJetsToTauTau->GetBinContent(j));
        tZq_ll->SetBinContent(j,wtZq_ll*tZq_ll->GetBinContent(j));
//        tZq_nunu->SetBinContent(j,wtZq_nunu*tZq_nunu->GetBinContent(j));
        ST_tW_antitop->SetBinContent(j,wST_tW_antitop*ST_tW_antitop->GetBinContent(j));
        ST_tW_top->SetBinContent(j,wST_tW_top*ST_tW_top->GetBinContent(j));
        TGJets->SetBinContent(j,wTGJets*TGJets->GetBinContent(j));
        THW->SetBinContent(j,wTHW*THW->GetBinContent(j));
        THQ->SetBinContent(j,wTHQ*THQ->GetBinContent(j));
        VHToNonbb->SetBinContent(j,wVHToNonbb*VHToNonbb->GetBinContent(j));
        ZHToTauTau->SetBinContent(j,wZHToTauTau*ZHToTauTau->GetBinContent(j));
        ZH_HToBB_ZToLL->SetBinContent(j,wZH_HToBB_ZToLL*ZH_HToBB_ZToLL->GetBinContent(j));
        GluGluHToZZTo4L->SetBinContent(j,wGluGluHToZZTo4L*GluGluHToZZTo4L->GetBinContent(j));
        GluGluHToBB->SetBinContent(j,wGluGluHToBB*GluGluHToBB->GetBinContent(j));
        GluGluHToGG->SetBinContent(j,wGluGluHToGG*GluGluHToGG->GetBinContent(j));
        GluGluHToMuMu->SetBinContent(j,wGluGluHToMuMu*GluGluHToMuMu->GetBinContent(j));
        GluGluHToTauTau->SetBinContent(j,wGluGluHToTauTau*GluGluHToTauTau->GetBinContent(j));
        GluGluHToWWTo2L2Nu->SetBinContent(j,wGluGluHToWWTo2L2Nu*GluGluHToWWTo2L2Nu->GetBinContent(j));
        GluGluHToWWToLNuQQ->SetBinContent(j,wGluGluHToWWToLNuQQ*GluGluHToWWToLNuQQ->GetBinContent(j));
        VBFHToWWTo2L2Nu->SetBinContent(j,wVBFHToWWTo2L2Nu*VBFHToWWTo2L2Nu->GetBinContent(j));
        VBFHToGG->SetBinContent(j,wVBFHToGG*VBFHToGG->GetBinContent(j));

        //float DATA = data->GetBinContent(j);
        float bkg0 =TTJets->GetBinContent(j)
            +  TTGJets->GetBinContent(j)
            + ttZJets->GetBinContent(j)+ ttWJets->GetBinContent(j) 
            + ttH->GetBinContent(j) 
            + ttbb->GetBinContent(j) + WZ->GetBinContent(j)  + WpWpJJ->GetBinContent(j) 
            + ZZ->GetBinContent(j)
            + WGJets->GetBinContent(j)
            + ZGJetsToLLG->GetBinContent(j)
            + WWW->GetBinContent(j)
            + WWZ->GetBinContent(j)
            + WWG->GetBinContent(j)
            + ZZZ->GetBinContent(j)
            + WZZ->GetBinContent(j)
            + WZG->GetBinContent(j)
            + WGG->GetBinContent(j)
            + ZGGJets->GetBinContent(j)
            + WJetsToLNu->GetBinContent(j)
            + DYJetsToTauTau->GetBinContent(j)
            + tZq_ll->GetBinContent(j)
//            + tZq_nunu->GetBinContent(j)
            + ST_tW_antitop->GetBinContent(j)
            + ST_tW_top->GetBinContent(j)
            + TGJets->GetBinContent(j)
            + THW->GetBinContent(j)
            + THQ->GetBinContent(j)
            + VHToNonbb->GetBinContent(j)
            + ZHToTauTau->GetBinContent(j)
            + ZH_HToBB_ZToLL->GetBinContent(j)
            + GluGluHToZZTo4L->GetBinContent(j)
            + GluGluHToBB->GetBinContent(j)
            + GluGluHToGG->GetBinContent(j)
            + GluGluHToMuMu->GetBinContent(j)
            + GluGluHToTauTau->GetBinContent(j)
            + GluGluHToWWTo2L2Nu->GetBinContent(j)
            + GluGluHToWWToLNuQQ->GetBinContent(j)
            + VBFHToWWTo2L2Nu->GetBinContent(j)
            + VBFHToGG->GetBinContent(j);
        background->SetBinContent(j,bkg0);//difinition at 936
    }/*}}}*/
      //why clone then delete? because we have to pass value to parameters
      background_func  = (TH1F*)background ->Clone(); 
    //  data_func        = (TH1F*)data       ->Clone(); 
      TTTT_func = (TH1F*)TTTT->Clone(); 
      TTJets_func = (TH1F*)TTJets->Clone(); 
      TTGJets_func = (TH1F*)TTGJets->Clone(); 
      ttZJets_func = (TH1F*)ttZJets->Clone(); 
      ttWJets_func   = (TH1F*)ttWJets->Clone(); 
      ttH_func   = (TH1F*)ttH->Clone(); 
      ttbb_func   = (TH1F*)ttbb->Clone();  
      WZ_func   = (TH1F*)WZ->Clone(); 
//      WW_func   = (TH1F*)WW->Clone();
      WWTo2L2Nu_func   = (TH1F*)WWTo2L2Nu->Clone();
      WpWpJJ_func   = (TH1F*)WpWpJJ->Clone();
      ZZ_func   = (TH1F*)ZZ->Clone();
      WGJets_func   = (TH1F*)WGJets->Clone();
      ZGJetsToLLG_func   = (TH1F*)ZGJetsToLLG->Clone();
      WWW_func   = (TH1F*)WWW->Clone();
      WWZ_func   = (TH1F*)WWZ->Clone();
      WWG_func   = (TH1F*)WWG->Clone();
      ZZZ_func   = (TH1F*)ZZZ->Clone();
      WZZ_func   = (TH1F*)WZZ->Clone();
      WZG_func   = (TH1F*)WZG->Clone();
      WGG_func   = (TH1F*)WGG->Clone();
      ZGGJets_func   = (TH1F*)ZGGJets->Clone();
      WJetsToLNu_func   = (TH1F*)WJetsToLNu->Clone();
      DYJetsToTauTau_func   = (TH1F*)DYJetsToTauTau->Clone();
      tZq_ll_func   = (TH1F*)tZq_ll->Clone();
//      tZq_nunu_func   = (TH1F*)tZq_nunu->Clone();
      ST_tW_antitop_func   = (TH1F*)ST_tW_antitop->Clone();
      ST_tW_top_func   = (TH1F*)ST_tW_top->Clone();
      TGJets_func   = (TH1F*)TGJets->Clone();
      THW_func   = (TH1F*)THW->Clone();
      THQ_func   = (TH1F*)THQ->Clone();
      VHToNonbb_func   = (TH1F*)VHToNonbb->Clone();
      ZHToTauTau_func   = (TH1F*)ZHToTauTau->Clone();
      ZH_HToBB_ZToLL_func   = (TH1F*)ZH_HToBB_ZToLL->Clone();
      GluGluHToZZTo4L_func   = (TH1F*)GluGluHToZZTo4L->Clone();
      GluGluHToBB_func   = (TH1F*)GluGluHToBB->Clone();
      GluGluHToGG_func   = (TH1F*)GluGluHToGG->Clone();
      GluGluHToMuMu_func   = (TH1F*)GluGluHToMuMu->Clone();
      GluGluHToTauTau_func   = (TH1F*)GluGluHToTauTau->Clone();
      GluGluHToWWTo2L2Nu_func   = (TH1F*)GluGluHToWWTo2L2Nu->Clone();
      GluGluHToWWToLNuQQ_func   = (TH1F*)GluGluHToWWToLNuQQ->Clone();
      VBFHToWWTo2L2Nu_func   = (TH1F*)VBFHToWWTo2L2Nu->Clone();
      VBFHToGG_func   = (TH1F*)VBFHToGG->Clone();

      //delete data;
      delete background;delete TTTT; delete TTJets;
      delete TTGJets;
      delete ttZJets; delete ttWJets; 
      delete ttH;
      delete ttbb; delete WZ; 
//      delete WW;
      delete WWTo2L2Nu;
      delete WpWpJJ; 
      delete ZZ;  
      delete WGJets;  
      delete ZGJetsToLLG;  
      delete WWW;  
      delete WWZ;  
      delete WWG;  
      delete ZZZ;  
      delete WZZ;  
      delete WZG;  
      delete WGG;  
      delete ZGGJets;  
      delete WJetsToLNu;  
      delete DYJetsToTauTau;  
      delete tZq_ll;  
//      delete tZq_nunu;  
      delete ST_tW_antitop;  
      delete ST_tW_top;  
      delete TGJets;  
      delete THW;  
      delete THQ;  
      delete VHToNonbb;  
      delete ZHToTauTau;  
      delete ZH_HToBB_ZToLL;  
      delete GluGluHToZZTo4L;  
      delete GluGluHToBB;  
      delete GluGluHToGG;  
      delete GluGluHToMuMu;  
      delete GluGluHToTauTau;  
      delete GluGluHToWWTo2L2Nu;  
      delete GluGluHToWWToLNuQQ;  
      delete VBFHToWWTo2L2Nu;  
      delete VBFHToGG;  
    
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
