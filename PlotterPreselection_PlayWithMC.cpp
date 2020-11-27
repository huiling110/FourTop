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

  name.push_back("jetsL_number");      bin.push_back(14);     Min.push_back(0);    Max.push_back(20);    axis.push_back("Number of jets");/*{{{*/
name.push_back("jetsL_HT"); bin.push_back(100);     Min.push_back(0);    Max.push_back(10000);    axis.push_back("HT pt[GeV]");
name.push_back("jetsL_MHT"); bin.push_back(100);     Min.push_back(0);    Max.push_back(10000);    axis.push_back("MHT pt[GeV]");
  name.push_back("jetsL_invariantMass");  bin.push_back(100);     Min.push_back(10);    Max.push_back(10000);    axis.push_back("Invariant mass of jets");
 name.push_back("jetsL_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(10000);    axis.push_back("jetsL_transMass");
 name.push_back("jetL_minDeltaR");      bin.push_back(100);     Min.push_back(0);    Max.push_back(6);    axis.push_back("min delta R of loose jets");
 name.push_back("jetsL_centrality");      bin.push_back(100);     Min.push_back(0);    Max.push_back(8);    axis.push_back("jetsL_centrality");
 name.push_back("jetsL_HTDividedByMet");      bin.push_back(100);     Min.push_back(0);    Max.push_back(200);    axis.push_back("HT / MET");
 name.push_back("jetsL_MHTDividedByMet");      bin.push_back(100);     Min.push_back(0);    Max.push_back(200);    axis.push_back("MHT / MET");
 name.push_back("MetDividedByHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("MetDividedByHT");
 name.push_back("jetsL_bScore");      bin.push_back(50);     Min.push_back(0);    Max.push_back(20);    axis.push_back("jetsL_bScore");
 name.push_back("jetsL_average_deltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(10);    axis.push_back("average delta R of loose jets");
 name.push_back("jetsL_4largestBscoreSum");      bin.push_back(50);     Min.push_back(0);    Max.push_back(10);    axis.push_back("jetsL_4largestBscoreSum");
 name.push_back("jetsL_leading2invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(8000);    axis.push_back("jetsL_leading2invariantMass");
 name.push_back("jetsL_rationHT_4toRest");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("jetsL_rationHT_4toRest");
 name.push_back("jetsL_leptonsMVAT_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(5);    axis.push_back("min delta R of loose jets and tight leptons");
 name.push_back("jetsL_tausF_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(10);    axis.push_back("min delta R of loose jets and fakeble taus");
 name.push_back("jetsL_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("jetsL_1pt");
 name.push_back("jetsL_1eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("leading loose jet eta");
 name.push_back("jetsL_1phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("leading loose jet phi");
 name.push_back("jetsL_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("second loose jet pt");
 name.push_back("jetsL_2eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("second loose jet eta");
 name.push_back("jetsL_2phi");      bin.push_back(50);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("second loose jet phi");
 name.push_back("jetsL_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("third loose jet pt");
 name.push_back("jetsL_3eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("third loose jet eta");
 name.push_back("jetsL_3phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("third loose jet phi");
 name.push_back("jetsL_4pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("fourth loose jet pt");
 name.push_back("jetsL_4eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("fourth loose jet eta");
 name.push_back("jetsL_4phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("fourth loose jet phi");
 name.push_back("jetsL_5pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("fifth loose jet pt");
 name.push_back("jetsL_5eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("fifth loose jet eta");
 name.push_back("jetsL_5phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("fifth loose jet phi");
 name.push_back("jetsL_6pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("sixth loose jet pt");
 name.push_back("jetsL_6eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("sixth loose jet eta");
 name.push_back("jetsL_6phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("sixth loose jet phi");
 name.push_back("jetsL_7pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("seventh loose jet pt");
 name.push_back("jetsL_7eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("senventh loose jet eta");
 name.push_back("jetL_7phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("seventh loose jet phi");
 name.push_back("jetsL_8pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("jetsL_8pt");
 name.push_back("jetsL_8eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("eighth loose jet eta");
 name.push_back("jetsL_8phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("eighth loose jet phi");
 name.push_back("jetsL_9pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("nineth loose jet pt");
 name.push_back("jetsL_9eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("nineth loose jet eta");
 name.push_back("jetsL_9phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("nineth loose jet phi");
 name.push_back("jetsL_10pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tenth loose jet pt");
 name.push_back("jetsL_10eta");      bin.push_back(20);     Min.push_back(-3);    Max.push_back(3);    axis.push_back("tenth loose jet eta");
 name.push_back("jetsL_10phi");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("tenth loose jet phi");
 name.push_back("jetsL_11pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("eleventh loose jet pt");
 name.push_back("jetsL_11phi");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("jetsL_11phi");
 name.push_back("jetsL_11eta");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("jetsL_11eta");
 // name.push_back("");      bin.push_back(100);     Min.push_back(0);    Max.push_back();    axis.push_back("");

 name.push_back("bjetsL_num");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("Number of loose b jets");
 name.push_back("bjetsM_num");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("Number of medium b jets");
 name.push_back("bjetsT_num");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of tight b jets");
 name.push_back("bjetsL_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsL_HT");
 name.push_back("bjetsM_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsM_HT");
 name.push_back("bjetsT_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsT_HT");
 name.push_back("bjetsL_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsL_MHT");
 name.push_back("bjetsM_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsM_MHT");
 name.push_back("bjetsT_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsT_MHT");
 name.push_back("bjetsL_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("invariant mass of loose b jets");
 name.push_back("bjetsM_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsM_invariantMass");
 name.push_back("bjetsT_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsT_invariantMass");
 name.push_back("bjetsL_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsL_transMass");
 name.push_back("bjetsM_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsM_transMass");
 name.push_back("bjetsT_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsT_transMass");
 name.push_back("bjetsL_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(6);    axis.push_back("min delta R of loose b jets");
 name.push_back("bjetsM_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(6);    axis.push_back("min delta R of medium b jets");
 name.push_back("bjetsT_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(6);    axis.push_back("min delta R of tight b jets");
 name.push_back("bjetsL_leptonsMVAT_minDeltaR");      bin.push_back(25);     Min.push_back(0);    Max.push_back(5);    axis.push_back("bjetsL_leptonsMVAT_minDeltaR");
 name.push_back("bjetsM_leptonsMVAT_minDeltaR");      bin.push_back(25);     Min.push_back(0);    Max.push_back(5);    axis.push_back("bjetsM_leptonsMVAT_minDeltaR");
 name.push_back("bjetsT_leptonsMVAT_minDeltaR");      bin.push_back(25);     Min.push_back(0);    Max.push_back(5);    axis.push_back("bjetsT_leptonsMVAT_minDeltaR");
 name.push_back("bjetsL_tausF_minDeltaR");      bin.push_back(25);     Min.push_back(0);    Max.push_back(5);    axis.push_back("bjetsL_tausF_minDeltaR");
 name.push_back("bjetsL_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsL_1pt");
 name.push_back("bjetsL_1eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_1eta");
 name.push_back("bjetsL_1phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_1phi");
 name.push_back("bjetsL_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsL_2pt");
 name.push_back("bjetsL_2eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_2eta");
 name.push_back("bjetsL_2phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_2phi");
 name.push_back("bjetsL_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("bjetsL_3pt");
 name.push_back("bjetsL_3eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_3eta");
 name.push_back("bjetsL_3phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_3phi");
 name.push_back("bjetsL_4pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("bjetsL_4pt");
 name.push_back("bjetsL_4eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_4eta");
 name.push_back("bjetsL_4phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_4phi");
 name.push_back("bjetsM_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsM_1pt");
 name.push_back("bjetsM_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsM_2pt");
 name.push_back("bjetsM_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsM_3pt");
 name.push_back("bjetsM_4pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsM_4pt");
 name.push_back("bjetsT_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsT_1pt");
 name.push_back("bjetsT_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsT_2pt");
 name.push_back("bjetsT_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("bjetsT_3pt");
 name.push_back("bjetsT_4pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("bjetsT_4pt");
 // name.push_back("");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("");
//

  name.push_back("forwardJets_num");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("Number of forward jets");
 name.push_back("forwardjet_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("leading forward jet pt");
 name.push_back("forwardjet_1eta");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("forwardjet_1eta");
 name.push_back("forwardjet_1phi");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("forwardjet_1phi");
 name.push_back("forwardjet1_jetsL_minDeltaEta");      bin.push_back(20);     Min.push_back(0);    Max.push_back(5);    axis.push_back("forwardjet1_jetsL_minDeltaEta");
//
name.push_back("Met_pt");  bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);   axis.push_back("Met pt[GeV] ");
name.push_back("Met_phi"); bin.push_back(8);     Min.push_back(-4);   Max.push_back(4);      axis.push_back("Met #phi");
//
//  
 name.push_back("leptonsMVAF_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("Number of fakeble leptons");
 name.push_back("leptonsMVAT_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("Number of Tight Leptons");
 name.push_back("leptonsMVAL_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("leptonsMVAL_number");
 name.push_back("leptonsMVAT_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("leptonsMVAT_transMass");//?
 name.push_back("leptonsMVAF_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("leptonsMVAF_transMass");//?
 name.push_back("leptonsMVAL_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("");//?
 name.push_back("leptonsMVAT_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(3000);    axis.push_back("leading tight lepton pt");
 name.push_back("leptonsMVAT_1eta");      bin.push_back(20);     Min.push_back(-3);    Max.push_back(3);    axis.push_back("leading tight lepton eta");
 name.push_back("leptonsMVAT_1phi");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("leading tight lepton phi");
 name.push_back("leptonsMVAT_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("second tight lepton pt");
 name.push_back("leptonsMVAT_2eta");      bin.push_back(20);     Min.push_back(-3);    Max.push_back(3);    axis.push_back("second tight lepton eta");
 name.push_back("leptonsMVAT_2phi");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("second tight lepton phi");
 name.push_back("leptonsMVAT_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(100);    axis.push_back("third tight lepton pt");
 name.push_back("leptonsMVAT_3eta");      bin.push_back(20);     Min.push_back(-3);    Max.push_back(3);    axis.push_back("third tight lepton eta");
 name.push_back("leptonsMVAT_3phi");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("third tight lepton phi");
 name.push_back("elesMVAL_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of loose electron");
 name.push_back("elesMVAT_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of tight electrons");
 name.push_back("elesMVAF_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of fakeble electrons");
 name.push_back("elesMVAF_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("leading tight electron pt");
 name.push_back("muonsL_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of loose muons");
 name.push_back("muonsT_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of tight mouns");
 name.push_back("muonsF_number");      bin.push_back(100);     Min.push_back(0);    Max.push_back(10);    axis.push_back("muonsF_number");//?
 name.push_back("muonsT_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("muonsT_1pt");//?
 name.push_back("muonsT_1eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("muonsT_1eta");//?
 name.push_back("muonsT_1phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("muonsT_1phi");//?
 name.push_back("muonsT_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("muonsT_2pt");//?
 name.push_back("muonsT_2eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("muonsT_2eta");//?
 name.push_back("muonsT_2phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("muonsT_2phi");//?
 name.push_back("muonsT_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("muonsT_3pt");//?
 name.push_back("muonsT_3eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("muonsT_3eta");//?
 name.push_back("muonsT_3phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("muonsT_3phi");//?

 name.push_back("tausL_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of loose tau");
 name.push_back("tausF_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of fakeble tau");
 name.push_back("tausT_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of fakeble tau");
 name.push_back("tausL_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("MHT of loose tau");
 name.push_back("tausF_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("MHT of fakeble tau");
 name.push_back("tausT_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("MHT of T tau");
 name.push_back("tausL_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("HT of L tau");
 name.push_back("tausF_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausF_HT");
 name.push_back("tausT_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausT_HT");
 name.push_back("tausL_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausL_invariantMass");
 name.push_back("tausF_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("invariant mass of fakeble tau");
 name.push_back("tausT_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausT_invariantMass");
 name.push_back("tausL_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(6);    axis.push_back("min delta R of loose tau");
 name.push_back("tausF_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(6);    axis.push_back("tausF_minDeltaR");
 name.push_back("tausT_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(6);    axis.push_back("tausT_minDeltaR");
 name.push_back("tausF_leptonsT_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("transverse mass of fakeble taus and tight leptons");
 name.push_back("tausT_leptonsT_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("transvese mass of tight taus and tight leptons");
 name.push_back("tausL_leptonsT_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausL_leptonsT_transMass");
 name.push_back("tausF_leptonsT_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("invariant mass of fakeble taus and tight leptons");
 name.push_back("tausL_leptonsT_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausL_leptonsT_invariantMass");
 name.push_back("tausT_leptonsT_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausT_leptonsT_invariantMass");
 name.push_back("tausF_leptonsT_chargeSum");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("charge sum of fakeble taus and tight leptons");
 name.push_back("tausF_leptonsTMVA_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(5);    axis.push_back("min delta R of tight leptons and fakeble taus");
 name.push_back("tausL_leptonsTMVA_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(10);    axis.push_back("tausL_leptonsTMVA_minDeltaR");
 name.push_back("tausT_leptonsTMVA_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(10);    axis.push_back("tausT_leptonsTMVA_minDeltaR");
//? buffer overflow detected. cmsenv might solve the problem
 name.push_back("tauL_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tauL_1pt");
 name.push_back("tauL_1eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("tauL_1eta");
 name.push_back("tauL_1phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("tauL_1phi");
 name.push_back("tauL_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tauL_2pt");
 name.push_back("tauL_2eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("tauL_2eta");
 name.push_back("tauL_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tauL_3pt");
 name.push_back("tauL_3eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("tauL_3eta");
 name.push_back("tauL_3phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("tauL_3phi");
//
 name.push_back("toptagger_num");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5);    axis.push_back("number of tops");
 name.push_back("toptagger_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(6000);    axis.push_back("toptagger_MHT");
 name.push_back("toptagger_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(6000);    axis.push_back("toptagger_HT");
 name.push_back("toptagger_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(6000);    axis.push_back("toptagger_invariantMass");
 name.push_back("toptagger_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(6000);    axis.push_back("toptagger_transMass");
 name.push_back("toptagger_minDeltaR_v1");      bin.push_back(100);     Min.push_back(0);    Max.push_back(6);    axis.push_back("toptagger_minDeltaR_v1");
 name.push_back("toptagger_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("leading top pt");
 name.push_back("toptagger_1eta");      bin.push_back(20);     Min.push_back(-6);    Max.push_back(6);    axis.push_back("toptagger_1eta");
 name.push_back("toptagger_1phi");      bin.push_back(20);     Min.push_back(-6);    Max.push_back(6);    axis.push_back("toptagger_1phi");
 name.push_back("toptagger_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("second top pt");
 name.push_back("toptagger_2eta");      bin.push_back(20);     Min.push_back(-6);    Max.push_back(6);    axis.push_back("toptagger_2eta");
 name.push_back("toptagger_2phi");      bin.push_back(20);     Min.push_back(-6);    Max.push_back(6);    axis.push_back("toptagger_2phi");
 name.push_back("toptagger_3eta");      bin.push_back(20);     Min.push_back(-6);    Max.push_back(6);    axis.push_back("toptagger_3eta");
 name.push_back("toptagger_3phi");      bin.push_back(20);     Min.push_back(-6);    Max.push_back(6);    axis.push_back("toptagger_3phi");
 name.push_back("toptagger_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(5);    axis.push_back("min delta R of tops");
 name.push_back("toptagger_scoreAllTops");      bin.push_back(20);     Min.push_back(0);    Max.push_back(5);    axis.push_back("top tagger score of all tops");/*}}}*/



	  char CUT[1000]; char CUTpre[1000]; char CUTpup1[1000]; char CUTpup2[1000]; char CUTbta1[1000]; char CUTbta2[1000];  char CUTfor1[1000]; char CUTfor2[1000]; char CUTwje1[1000]; char CUTwje2[1000]; char CUTzje1[1000];  char CUTzje2[1000];  char CUTttb1[1000];  char CUTttb2[1000];  char CUTfir1[1000];  char CUTfir2[1000];char CUTqcd1[1000]; char CUTqcd2[1000];char CUTpdf1[1000]; char CUTpdf2[1000]; char CUTtri1[1000]; char CUTtri2[1000];
	  //apply selection cuts here
      //
//    sprintf(CUTpre,"((NumOfTausL>0))");
// vector<string> Channel = {[>"1Tau0L_v2","1Tau1L_v2","1Tau1E_v2","1Tau1Mu_v2","1Tau2OS_v2", "1Tau2SS_v2", "1Tau3L_v2",<]"2Tau0L_v2", "2Tau1L_v2","2Tau2OS_v2","2Tau2SS_v2"   };
vector<string> Channel = { "1Tau0L_v2"   };
// vector<string> Channel = { "1Tau1E_v2"   };
// vector<string> Channel = { "1Tau1Mu_v2"   };
// vector<string> Channel = { "1Tau2OS_v2"   };
// vector<string> Channel = { "1Tau3L_v2"   };
// vector<string> Channel = { "2Tau0L_v2"   };

for ( string ch : Channel){
//    char chann[100] = channel+"==1";
    TString postfix = ch + ".png";
    ch = "channel_"+ ch + "==1";
    const char*    channel= ch.c_str();//.c_str() returns a const char*
//   sprintf(CUTpre,"%s", channel);
//   sprintf(CUTpre,"(jetsL_number>5)&&(bjetsL_num>1)&&(%s)", channel);
   // sprintf(CUTpre,"(jetsL_number>=8)&&(bjetsM_num>=2)&&(%s)", channel);//1Tau0L
   sprintf(CUTpre,"(jetsL_number>=8)&&(bjetsM_num>=2)&&(tausT_number==1)&&(%s)", channel);//1Tau0L for testing
   // sprintf(CUTpre,"(jetsL_number>=9)&&(bjetsM_num>=2&&(leptonsMVAT_number==0))&&(%s)", channel);//1Tau0L for testing
   // sprintf(CUTpre,"(jetsL_number>=6)&&(bjetsM_num>=2) && (tausT_number == 1)&&(%s)", channel);//1Tau1L
   // sprintf(CUTpre,"(jetsL_number>=4)&&(bjetsM_num>=2)&&(%s)", channel);//1Tau2OS AND 1Tau2SS
   // sprintf(CUTpre,"(jetsL_number>=2)&&(bjetsM_num>=2)&&(%s)", channel);//1Tau3L
   // sprintf(CUTpre,"(jetsL_number>=6)&&(bjetsM_num>=2)&&(%s)", channel);//2Tau0L
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


  std::map<float, TString> mymap;
 for(UInt_t i=0; i<1; i++){
  // for(UInt_t i=0; i<name.size(); i++){
	  const char *plot = name[i];
//?need to simply this. or add all this samples would be very time cosuming

        TH1F* TTTT = new TH1F(plot,plot,bin[i],Min[i],Max[i]);//1
        TH1F* TTJets= new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* TTGJets= new TH1F(plot,plot,bin[i],Min[i],Max[i]);TH1F* ttZJets= new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* ttWJets= new TH1F(plot,plot,bin[i],Min[i],Max[i]);TH1F* ttH= new TH1F(plot,plot,bin[i],Min[i],Max[i]); /*TH1F* ttbb = new TH1F(plot,plot,bin[i],Min[i],Max[i]);*/ //6
        TH1F* WZ = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* WWTo2L2Nu = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* WpWpJJ = new TH1F(plot,plot,bin[i],Min[i],Max[i]);TH1F* ZZ = new TH1F(plot,plot,bin[i],Min[i],Max[i]);TH1F* WGJets = new TH1F(plot,plot,bin[i],Min[i],Max[i]);TH1F* ZGJetsToLLG = new TH1F(plot,plot,bin[i],Min[i],Max[i]);//6
        TH1F* WWW = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* WWZ = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* WWG = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* ZZZ = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* WZZ = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* WZG = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* WGG = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* ZGGJets = new TH1F(plot,plot,bin[i],Min[i],Max[i]);//8
        TH1F* WJetsToLNu = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* DYJetsToTauTau = new TH1F(plot,plot,bin[i],Min[i],Max[i]);//2
        TH1F* tZq_ll = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* ST_tW_antitop = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* ST_tW_top = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* TGJets = new TH1F(plot,plot,bin[i],Min[i],Max[i]);TH1F* THW = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* THQ = new TH1F(plot,plot,bin[i],Min[i],Max[i]);//6
        TH1F* VHToNonbb = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* ZHToTauTau = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* ZH_HToBB_ZToLL = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* GluGluHToZZTo4L = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* GluGluHToBB = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* GluGluHToGG = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* GluGluHToMuMu = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* GluGluHToTauTau = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* GluGluHToWWTo2L2Nu = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* GluGluHToWWToLNuQQ = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* VBFHToWWTo2L2Nu = new TH1F(plot,plot,bin[i],Min[i],Max[i]);/* TH1F* VBFHToTauTau = new TH1F(plot,plot,bin[i],Min[i],Max[i]); */TH1F* VBFHToMuMu = new TH1F(plot,plot,bin[i],Min[i],Max[i]); TH1F* VBFHToGG = new TH1F(plot,plot,bin[i],Min[i],Max[i]); 
        vector<TH1F*> BGFiles  {
            TTTT,//0
            TTJets,TTGJets,ttZJets,ttWJets,ttH,/* ttbb, */ //6
            WZ,  WWTo2L2Nu,  WpWpJJ, ZZ, WGJets, ZGJetsToLLG,//12
             WWW,  WWZ,  WWG,  ZZZ,  WZZ,  WZG,  WGG,  ZGGJets,//20
             WJetsToLNu,  DYJetsToTauTau,//22
             tZq_ll,  ST_tW_antitop,  ST_tW_top,  TGJets, THW,  THQ,//28
             VHToNonbb,  ZHToTauTau,  ZH_HToBB_ZToLL,  GluGluHToZZTo4L,  GluGluHToBB,  GluGluHToGG,  GluGluHToMuMu,  GluGluHToTauTau,  GluGluHToWWTo2L2Nu,  GluGluHToWWToLNuQQ,  VBFHToWWTo2L2Nu, /* VBFHToTauTau, */ VBFHToMuMu,  VBFHToGG// 41
        };
//        BGFiles.push_back(TTTT); BGFiles.push_back(TTJets);BGFiles.push_back(TTGJets); BGFiles.push_back(ttZJets); BGFiles.push_back(ttWJets); BGFiles.push_back(ttH); BGFiles.push_back(ttbb);// BGFiles.push_back();     
//        vector<TH1F*> BGFiles_NormalizedToXSection;
//            = {TTJets_SR,TTGJets_SR,ttZJets_SR,ttWJets_SR,ttH_SR,ttbb_SR       };
//        BGFiles_NormalizedToXSection.push_back(TTJets_SR);BGFiles_NormalizedToXSection.push_back(TTGJets_SR); BGFiles_NormalizedToXSection.push_back(ttZJets_SR); BGFiles_NormalizedToXSection.push_back(ttWJets_SR); BGFiles_NormalizedToXSection.push_back(ttH_SR); BGFiles_NormalizedToXSection.push_back(ttbb_SR);             
        TH1::SetDefaultSumw2();// TH1::Sumw2 to force the storage and computation of the sum of the square of weights per bin.umw2 has been called, the error per bin is computed as the sqrt(sum of squares of weights), otherwise the error is set equal to the sqrt(bin content)
        TH1F* background_SR = new TH1F("BG","BG",bin[i],Min[i],Max[i]);
        // TH1F* signalAndBg_beforeScale = new TH1F("allFile", "allFile",bin[i],Min[i],Max[i]);
        // TH1F* background_SR = new TH1F;
        TList *list = new TList;
        // cout<<"signal and bg files ="<< BGFiles.size()<<endl;
        // cout<<"number of weights ="<<bg_scale.size()<<endl;
        // cout<<"number of trees = "<<bgTree.size()<<endl;
        for(UInt_t j = 0; j < BGFiles.size(); j++){
//            TH1F* background = BGFiles[j];
            // GetHisto(CUT,bgTree[j],BGFiles[j],plot,bin[i],Min[i],Max[i]);
// void GetHisto(char CUT[1000], TTree *Tree, TH1F* & histo, const char *plot, int BIN, float MIN, float MAX){[><]
            char input[50]; sprintf(input,"%s>>h(%i,%f,%f)",plot,bin[i],Min[i],Max[i]);
            bgTree[j]->Draw(input,CUT); TH1F* h=(TH1F*)gDirectory->Get("h"); BGFiles[j] = (TH1F*)h->Clone(); delete h; 
        	
            BGFiles[j]->SetDirectory(0);//dir can be 0 in which case the histogram does not belong to any directory.
            // BGFiles[j]->SetName("histo");

            // auto histo = BGFiles[j];
            // bgTree[j]->Project("histo",plot,CUT);
           // BGFiles[j]->Print();
//            cout<<bg_scale[j];
//            *BGFiles_NormalizedToXSection[j] = bg_scale[j]*(*(BGFiles[j])); 

            BGFiles[j]->Scale(bg_scale[j]);
//            if(j==0) *background_SR = *BGFiles_NormalizedToXSection[j];
//            if(j>0) *background_SR  = *background_SR + *(BGFiles_NormalizedToXSection[j]);
//            BGFiles_NormalizedToXSection[j]->Print();            
            // background_SR->Add((BGFiles_NormalizedToXSection[j]),1);
            if(j > 0) background_SR->Add((BGFiles[j]),1);
            // if(j>0) list->Add(BGFiles[j]);
            // double xmax = BGFiles[j]->GetXaxis()->GetXmax();
            // cout<<xmax<<endl;
//            background_SR->Print();
//            cout<<j<<endl;
//          delete (BGFiles[j]);
        }
        // TH1F *bg_forSP = (TH1F*)BGFiles[1]->Clone("bg_forSP");
        // bg_forSP->Reset(); //resets the bin contents and errors of an histogram
        // bg_forSP->Merge(list);
        // bg_forSP->Print();

        if(i==0){
            cout<<endl;
            cout<<"Plotting "<<name[i]<<postfix<<endl;
         //  cout<<"DATA      = "<<data_SR->Integral()<<" +/- "<<dataErr<<endl;/*{{{*/
            cout<<"TTTT   = "<<(BGFiles[0])->Integral()<<endl;
            cout<<"TTJets = "<<BGFiles[1]->Integral()<<endl;
            cout<<"TTX    = "<<BGFiles[2]->Integral()+BGFiles[3]->Integral()+BGFiles[4]->Integral()+BGFiles[5]->Integral()<<endl;
            // cout<<"ttbb   = "<<BGFiles[6]->Integral()<<endl;
            cout<<"VV     = "<<BGFiles[6]->Integral()+BGFiles[7]->Integral()+BGFiles[8]->Integral()+BGFiles[9]->Integral()+BGFiles[10]->Integral()+BGFiles[11]->Integral()<<endl;
            cout<<"VVV    = "<<BGFiles[12]->Integral()+BGFiles[13]->Integral()+BGFiles[14]->Integral()+BGFiles[15]->Integral()+BGFiles[16]->Integral()+BGFiles[17]->Integral()+BGFiles[18]->Integral()+BGFiles[19]->Integral()<<endl;
            cout<<"WJets  = "<<BGFiles[20]->Integral()<<endl;      
            cout<<"DY     = "<<BGFiles[21]->Integral()<<endl;      
            cout<<"ST     = "<<BGFiles[22]->Integral()+BGFiles[23]->Integral()+BGFiles[24]->Integral()+BGFiles[25]->Integral()+BGFiles[26]->Integral()+BGFiles[27]->Integral()<<endl;
            cout<<"H      = "<<BGFiles[28]->Integral()+BGFiles[29]->Integral()+BGFiles[30]->Integral()+BGFiles[31]->Integral()+BGFiles[32]->Integral()+BGFiles[33]->Integral()+BGFiles[34]->Integral()+BGFiles[35]->Integral()+BGFiles[36]->Integral()+BGFiles[37]->Integral()+BGFiles[38]->Integral()+BGFiles[39]->Integral()+BGFiles[40]->Integral()<<endl;
            cout<<"Total BKG = "<<background_SR->Integral()<<endl;
            cout<<endl;
            cout<<"Statistics"<<endl;
            cout<<"TTTT   = "<<(BGFiles[0])->Integral()/bg_scale[0]<<endl;
            cout<<"TTJets = "<<(BGFiles[1]->Integral()/ bg_scale[1])<<endl;
            cout<<"TTX    = "<<(BGFiles[2]->Integral()/ bg_scale[2]) + (BGFiles[3]->Integral()/bg_scale[3]) + (BGFiles[4]->Integral()/bg_scale[4]) + ( BGFiles[5]->Integral()/bg_scale[5]) <<endl;
            // cout<<"ttbb   = "<<(BGFiles[6]->Integral()/bg_scale[6])<<endl;
            cout<<"VV     = "<<(BGFiles[6]->Integral()/bg_scale[6]) +(BGFiles[7]->Integral()/bg_scale[7]) +(BGFiles[8]->Integral()/bg_scale[8]) + (BGFiles[9]->Integral()/bg_scale[9]) + (BGFiles[10]->Integral()/bg_scale[10]) + (BGFiles[11]->Integral()/bg_scale[11]) <<endl;
            cout<<"VVV    = "<<(BGFiles[12]->Integral()/bg_scale[12]) + (BGFiles[13]->Integral()/bg_scale[13]) + (BGFiles[14]->Integral()/bg_scale[14]) + (BGFiles[15]->Integral()/bg_scale[15]) + (BGFiles[16]->Integral()/bg_scale[16]) + (BGFiles[17]->Integral()/bg_scale[17]) + (BGFiles[18]->Integral()/bg_scale[18]) + (BGFiles[19]->Integral()/bg_scale[19]) <<endl;
            cout<<"WJets  = "<<(BGFiles[20]->Integral()*bg_scale[20])<<endl;      
            cout<<"DY     = "<<(BGFiles[21]->Integral()*bg_scale[21])<<endl;      
            cout<<"ST     = "<<(BGFiles[22]->Integral()/bg_scale[22])+(BGFiles[23]->Integral()/bg_scale[23]) + (BGFiles[24]->Integral()/bg_scale[24]) + (BGFiles[25]->Integral()/bg_scale[25]) + (BGFiles[26]->Integral()/bg_scale[26]) + (BGFiles[27]->Integral()/bg_scale[27]) <<endl;
            cout<<"H      = "<<(BGFiles[28]->Integral()/bg_scale[28])+(BGFiles[29]->Integral()/bg_scale[29]) + (BGFiles[30]->Integral()/bg_scale[30]) + (BGFiles[31]->Integral()/bg_scale[31]) + (BGFiles[32]->Integral()/bg_scale[32]) + (BGFiles[33]->Integral()/bg_scale[33]) + (BGFiles[34]->Integral()/bg_scale[34]) + (BGFiles[35]->Integral()/bg_scale[35]) + (BGFiles[36]->Integral()/bg_scale[36]) + (BGFiles[37]->Integral()/bg_scale[37]) + (BGFiles[38]->Integral()/bg_scale[38]) + (BGFiles[39]->Integral()/bg_scale[39]) + (BGFiles[40]->Integral()/bg_scale[40]) <<endl;
        }/*}}}*/

        TCanvas* c1 = new TCanvas("c1","c1",0,0,600,600);
        TPad *c1_2 = new TPad("c1_2", "newpad",0.02,0.10,0.99,0.90);// bottom left point(),
        c1_2->Draw();
        c1_2->cd();

        background_SR->SetLineWidth(2);
        background_SR->SetLineColor(kBlue); 
        background_SR->SetMinimum(0);
    //    hs->SetMaximum(1);
        background_SR->SetMaximum(1.5 * background_SR->GetMaximum());
        background_SR->GetYaxis()->SetTitleSize(0.050);
        background_SR->GetXaxis()->SetTitleSize(0.050);
        background_SR->GetYaxis()->SetLabelSize(0.040);
        background_SR->GetXaxis()->SetLabelSize(0.040); 
        background_SR->SetTitle("");
        background_SR->GetYaxis()->SetTitle("Events");
        background_SR->GetXaxis()->SetTitle(axis[i]);
        background_SR->GetYaxis()->SetTitleOffset(1.00);
        background_SR->GetXaxis()->SetTitleOffset(0.85);//Set distance between the axis and the axis title
        background_SR->DrawNormalized("hist", 1);
        // background_SR->Draw("hist");
        BGFiles[0]->SetLineWidth(2);
        BGFiles[0]->SetLineColor(2);
//        BGFiles[0]->SetLineColor(kViolet-2); 
       // BGFiles[0]->Draw("samehisto");
        BGFiles[0]->DrawNormalized("samehist", 1);
        // BGFiles[0]->Draw("samehist");


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
        TLegendEntry *ple2 = pl2->AddEntry(BGFiles[0], "TTTT",  "L"); 
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
    //    c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v2_NewNtupleAfterEventSelection/Plots/"+NAME+"1Tau3L.png");
        // c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v9_NewNtuple/plots_and_results/tausT/"+NAME+postfix);
        // c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/plotsAndResults/v9/tausT_removettbb/"+NAME+postfix);
        c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/plotsAndResults/v10_ObjectRemoval/"+NAME+postfix);
        
        cout<<"Finished "<<NAME+postfix<<endl;
        c1->Draw();

//        float scale_TTTT = BGFiles[0]->Integral();
//        cout<<scale_TTTT<<endl;
//          cout<<"Total BKG = "<<background_SR->Integral()<<endl;
//          background_SR->Print();
//        vector<float> separation_power;
        //?for different range we have different sp, how to deal with this?
        float sp = separationPower(BGFiles[0], background_SR);
        // float sp = separationPower(BGFiles[0], bg_forSP);
//        separation_power.push_back(sp);
        cout<<NAME<<" separation power"<<sp<<endl;
        std::cout << '\n';
        if(i==(name.size()-1)) cout<<ch<<endl;
        // if(i==2) cout<<ch<<endl;
       // std::map<float, TString> mymap;
        mymap.insert(std::make_pair(sp, NAME));

        for(UInt_t j = 0; j < BGFiles.size(); j++){
             delete (BGFiles[j]);
        }

        delete background_SR;//put delete in the last
  }

    // auto it{ mymap.cbegin() }; // declare a const iterator and assign to start of vector
    // while (it != mymap.cend()) // while it hasn't reach the end
    // {
        // std::cout <<it->second << " = " << it->first  << " "<<endl; // print the value of the element it points to
        // ++it; // and iterate to the next element
    // }
    for (auto rit = mymap.crbegin(); rit != mymap.crend(); ++rit){
        std::cout <<  rit->second << " = "<< rit->first << endl;
        // std::cout << '\n';
    }

//what is SYST and why we do it this way?   
	//how do we exactly include SYST in our histograms?
/*	if(SYST){//15
		MakeHistos(CUTpup1,plot,bin[i],Min[i],Max[i],0,data_P1,background_P1,ZToNuNu_1_P1,ZToNuNu_2_P1,ZToNuNu_3_P1,ZToNuNu_4_P1,ZToNuNu_5_P1,ZToNuNu_6_P1,ZToNuNu_7_P1,
				QCD_1_P1,QCD_2_P1,QCD_3_P1,QCD_4_P1,QCD_5_P1,QCD_6_P1,QCD_7_P1,WToLNu_1_P1,WToLNu_2_P1,WToLNu_3_P1,WToLNu_4_P1,WToLNu_5_P1,WToLNu_6_P1,WToLNu_7_P1,
				 TT_1_P1,TT_2_P1,ST_1_P1,ST_2_P1,ST_3_P1,ST_4_P1,ZZ1_P1,ZZ2_P1,ZZ3_P1,WW1_P1,WW2_P1,WZ1_P1,WZ2_P1,WZ3_P1,ttW_P1,ttZ_P1,tZq_P1,ZZ4_P1,WZ4_P1,
				 tptzm0700lh_P1,tptzm0900lh_P1,tptzm1400lh_P1,tptzm1700lh_P1);

*/
		//according to SYST we reset our bin error to histo_SR
		//
/*	for(int m=1; m<background_SR->GetNbinsX()+1; m++){ //1112
		MakeHistoErrors(m, ZToNuNu_1_SR, ZToNuNu_1_P1, ZToNuNu_1_P2, ZToNuNu_1_F1, ZToNuNu_1_F2, ZToNuNu_1_B1, ZToNuNu_1_B2, ZToNuNu_1_Z1, ZToNuNu_1_Z2, ZToNuNu_1_W1, ZToNuNu_1_W2, ZToNuNu_1_T1, ZToNuNu_1_T2, ZToNuNu_1_J1, ZToNuNu_1_J2, ZToNuNu_1_J3, ZToNuNu_1_J4, ZToNuNu_1_qcd1, ZToNuNu_1_qcd2, ZToNuNu_1_pdf1, ZToNuNu_1_pdf2, ZToNuNu_1_TR1, ZToNuNu_1_TR2);
		}*/
	

//		Double_t dataErr   = 0; Float_t dataYield = data_SR->IntegralAndError(1,TTTT_SR->GetNbinsX()-1,dataErr,"");/*{{{*/
/*		Double_t TTJetsErr   = 0; Float_t TTJetsYield = TTJets_SR->IntegralAndError(1,TTTT_SR->GetNbinsX(),TTJetsErr,"");
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
*/        
        //?why not use result of this?

    
/*    if(i==0){
      cout<<endl;
      cout<<"Plotting "<<name[i]<<endl;
    //  cout<<"DATA      = "<<data_SR->Integral()<<" +/- "<<dataErr<<endl;
      cout<<"TTJets   = "<<TTJets_SR->Integral()<<" +/- "<<	sqrt(TTJetsErr*TTJetsErr)<<endl;
        cout<<"WJets = "<<WJetsToLNu_SR->Integral()<<endl;      
        cout<<"DY = "<<DYJetsToTauTau_SR->Integral()<<endl;      
        cout<<"ttbb = "<<ttbb_SR->Integral()<<endl;      
        cout<<"WZ = "<<WZ_SR->Integral()<<endl;      
        cout<<"WW = "<<WWTo2L2Nu_SR->Integral()<<endl;      
        cout<<"ZZ = "<<ZZ_SR->Integral()<<endl;      
        cout<<"WG = "<<WGJets_SR->Integral()<<endl;      
        cout<<"SINGLE TOP = "<<tZq_ll_SR->Integral()+ST_tW_antitop_SR->Integral()+ST_tW_top_SR->Integral()<<endl;      
        cout<<"H = "<<VHToNonbb_SR->Integral()+ZHToTauTau_SR->Integral()+ZH_HToBB_ZToLL_SR->Integral()+GluGluHToZZTo4L_SR->Integral()+GluGluHToBB_SR->Integral()+GluGluHToGG_SR->Integral()+GluGluHToMuMu_SR->Integral()+GluGluHToTauTau_SR->Integral()+GluGluHToWWTo2L2Nu_SR->Integral()+GluGluHToWWToLNuQQ_SR->Integral()+VBFHToWWTo2L2Nu_SR->Integral()+VBFHToGG_SR->Integral()<<endl;

//	  cout<<"Total BKG = "<<TTJets_SR->Integral()          +TTGJets_SR->Integral()          +ttZJets_SR->Integral()+ttWJets_SR->Integral()+ttbb_SR->Integral()+WZ_SR->Integral()          +ttH_SR->Integral()          +WW_SR->Integral()+WpWpJJ_SR->Integral()          +ZZ_SR->Integral()     " +/- "<<sqrt(TTJetsErr*TTJetsErr            +TTGJetsErr*TTGJetsErr;
      cout<<"TTTT = "<<TTTT_SR->Integral()<<endl;
	  cout<<"Total BKG = "<<background_SR->Integral()<<endl;
      
	}
    TCanvas* c1 = new TCanvas("c1","c1",0,0,600,600);
		TTTT_SR->SetLineWidth(2);
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

//		data_SR->SetLineWidth(2); data_SR->SetLineColor(1); data_SR->SetMarkerColor(1); data_SR->SetMarkerStyle(20); data_SR->SetMarkerSize(1.3);

*/



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
/*
    TPad *c1_2 = new TPad("c1_2", "newpad",0.02,0.10,0.99,0.90);// bottom left point(),
    c1_2->Draw();
    c1_2->cd();
*/    
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
/*
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
    delete background_SR;

*/    
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


void GetHisto_noBoundry(char CUT[1000], TTree *Tree, TH1F* & histo, const char *plot, int BIN, float MIN, float MAX){
  char input[50];
  sprintf(input,"%s>>h(%i)",plot,BIN);
  TH1F *temp = new TH1F("", "", BIN,MIN,MAX);
  if(Tree->Draw(input,CUT)){ Tree->Draw(input,CUT); TH1F* h=(TH1F*)gDirectory->Get("h"); histo = (TH1F*)h->Clone(); delete h; }
    else { histo = (TH1F*)temp->Clone(); }
  histo->SetDirectory(0);//dir can be 0 in which case the histogram does not belong to any directory.
  histo->SetName("histo");
  delete temp;
 }

float separationPower(TH1F* h1, TH1F* h2){
    float norm = 1;
    // h1->Print();
    // h2->Print();
    h1->Scale(norm/h1->Integral());
    h2->Scale(norm/h2->Integral());
  int nbins=h1->GetXaxis()->GetNbins();
//  cout<<nbins<<endl;
  float s=0;
//  float width=h1->GetBinWidth(1);
  for(int i=1;i<nbins+1;i++){
//  for(int i=0;i<nbins;i++){
      if(h1->GetBinContent(i)+h2->GetBinContent(i)!=0)
//      s+=0.5*TMath::Power((h1->GetBinContent(i)-h2->GetBinContent(i))/width,2)/(h1->GetBinContent(i)+h2->GetBinContent(i))*width*width;
      s+=0.5*TMath::Power((h1->GetBinContent(i)-h2->GetBinContent(i)),2)/(h1->GetBinContent(i)+h2->GetBinContent(i));
      //?it seems you do not use width at all.
  }
  return s;
}
//for MC we multiply the scale factor, adjust error accordingly , and make background histogram
//we get histograms based on CUT from MC and data,and we
/*
void MakeHistos(char CUT[1000],const char *plot,int BIN,float MIN,float MAX,int JETSyst,
//                TH1F* &data_func,
TH1F* &background_func,TH1F* &TTJets_func,TH1F* &TTGJets_func,TH1F* &ttZJets_func,  TH1F*  &ttWJets_func,TH1F* &ttH_func,TH1F* &ttbb_func,TH1F* &WZ_func,
//                 TH1F* &WW_func,
TH1F* &WWTo2L2Nu_func, TH1F* &WpWpJJ_func,TH1F* &ZZ_func,TH1F* &WGJets_func, TH1F* &ZGJetsToLLG_func, TH1F* &WWW_func,TH1F* &WWZ_func,TH1F* &WWG_func,TH1F* &ZZZ_func,TH1F* &WZZ_func,TH1F* &WZG_func, TH1F* &WGG_func,TH1F* &ZGGJets_func,TH1F* &WJetsToLNu_func,         TH1F* &DYJetsToTauTau_func, TH1F* &tZq_ll_func,TH1F* &ST_tW_antitop_func, TH1F* &ST_tW_top_func, TH1F* &TGJets_func,TH1F* &THW_func, TH1F* &THQ_func,TH1F* &VHToNonbb_func, TH1F* &ZHToTauTau_func, TH1F* &ZH_HToBB_ZToLL_func, TH1F* &GluGluHToZZTo4L_func, TH1F* &GluGluHToBB_func, TH1F* &GluGluHToGG_func, TH1F* &GluGluHToMuMu_func, TH1F* &GluGluHToTauTau_func, TH1F* &GluGluHToWWTo2L2Nu_func, TH1F* &GluGluHToWWToLNuQQ_func,TH1F* &VBFHToWWTo2L2Nu_func,TH1F* &VBFHToGG_func,  TH1F* &TTTT_func){
                    
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
      
//        else if(JETSyst==1){
//       // GetHisto(CUT, Tree01_J1, data        ,plot,BIN,MIN,MAX);//J1 from JESup directory
//        GetHisto(CUT, Tree02_J1, TTTT ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree03_J1, TTJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree04_J1, TTGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree05_J1, ttZJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree06_J1, ttWJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree07_J1, ttH ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree08_J1, ttbb ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree09_J1, WZ ,plot,BIN,MIN,MAX);
////        GetHisto(CUT, Tree10_J1, WW ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree11_J1, WpWpJJ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree12_J1, ZZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, WGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, ZGJetsToLLG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, WWW ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, WWZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, WWG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, ZZZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, WZZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, WZG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, WGG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, ZGGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, WJetsToLNu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, DYJetsToTauTau ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, tZq_ll ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, tZq_nunu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, ST_tW_antitop ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, ST_tW_top ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, TGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, THW ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, THQ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, VHToNonbb ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, ZHToTauTau ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, ZH_HToBB_ZToLL ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, GluGluHToZZTo4L ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, GluGluHToBB ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, GluGluHToGG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, GluGluHToMuMu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, GluGluHToTauTau ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, GluGluHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, GluGluHToWWToLNuQQ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, VBFHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J1, VBFHToGG ,plot,BIN,MIN,MAX);
//      }
//        else if(JETSyst==2){
//       // GetHisto(CUT, Tree01_J2, data        ,plot,BIN,MIN,MAX);//J2 from JESdo
//        GetHisto(CUT, Tree02_J2, TTTT ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree03_J2, TTJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree04_J2, TTGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree05_J2, ttZJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree06_J2, ttWJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree07_J2, ttH ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree08_J2, ttbb ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree09_J2, WZ ,plot,BIN,MIN,MAX);
////        GetHisto(CUT, Tree10_J2, WW ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree11_J2, WpWpJJ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree12_J2, ZZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, WGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, ZGJetsToLLG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, WWW ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, WWZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, WWG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, ZZZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, WZZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, WZG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, WGG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, ZGGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, WJetsToLNu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, DYJetsToTauTau ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, tZq_ll ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, tZq_nunu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, ST_tW_antitop ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, ST_tW_top ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, TGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, THW ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, THQ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, VHToNonbb ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, ZHToTauTau ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, ZH_HToBB_ZToLL ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, GluGluHToZZTo4L ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, GluGluHToBB ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, GluGluHToGG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, GluGluHToMuMu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, GluGluHToTauTau ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, GluGluHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, GluGluHToWWToLNuQQ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, VBFHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J2, VBFHToGG ,plot,BIN,MIN,MAX);
//      }
//        else if(JETSyst==3){
//       // GetHisto(CUT, Tree01_J3, data        ,plot,BIN,MIN,MAX);//J3 from JERup
//        GetHisto(CUT, Tree02_J3, TTTT ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree03_J3, TTJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree04_J3, TTGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree05_J3, ttZJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree06_J3, ttWJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree07_J3, ttH ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree08_J3, ttbb ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree09_J3, WZ ,plot,BIN,MIN,MAX);
////        GetHisto(CUT, Tree10_J3, WW ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree11_J3, WpWpJJ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree12_J3, ZZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, WGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, ZGJetsToLLG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, WWW ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, WWZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, WWG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, ZZZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, WZZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, WZG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, WGG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, ZGGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, WJetsToLNu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, DYJetsToTauTau ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, tZq_ll ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, tZq_nunu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, ST_tW_antitop ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, ST_tW_top ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, TGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, THW ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, THQ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, VHToNonbb ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, ZHToTauTau ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, ZH_HToBB_ZToLL ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, GluGluHToZZTo4L ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, GluGluHToBB ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, GluGluHToGG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, GluGluHToMuMu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, GluGluHToTauTau ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, GluGluHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, GluGluHToWWToLNuQQ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, VBFHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J3, VBFHToGG ,plot,BIN,MIN,MAX);
//      }
//        else if(JETSyst==4){
//       // GetHisto(CUT, Tree01_J4, data        ,plot,BIN,MIN,MAX);//from JERdo
//        GetHisto(CUT, Tree02_J4, TTTT ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree03_J4, TTJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree04_J4, TTGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree05_J4, ttZJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree06_J4, ttWJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree07_J4, ttH ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree08_J4, ttbb ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree09_J4, WZ ,plot,BIN,MIN,MAX);
////        GetHisto(CUT, Tree10_J4, WW ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree11_J4, WpWpJJ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree12_J4, ZZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, WGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, ZGJetsToLLG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4,WWW ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, WWZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, WWG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, ZZZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, WZZ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, WZG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, WGG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, ZGGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, WJetsToLNu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, DYJetsToTauTau ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, tZq_ll ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, tZq_nunu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, ST_tW_antitop ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, ST_tW_top ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, TGJets ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, THW ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, THQ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, VHToNonbb ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, ZHToTauTau ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, ZH_HToBB_ZToLL ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, GluGluHToZZTo4L ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, GluGluHToBB ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, GluGluHToGG ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, GluGluHToMuMu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, GluGluHToTauTau ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, GluGluHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, GluGluHToWWToLNuQQ ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, VBFHToWWTo2L2Nu ,plot,BIN,MIN,MAX);
//        GetHisto(CUT, Tree13_J4, VBFHToGG ,plot,BIN,MIN,MAX);
//      }

 // TH1F *background = new TH1F("","",data->GetNbinsX(),data->GetXaxis()->GetXmin(),data->GetXaxis()->GetXmax());
      TH1F *background = new TH1F("","",TTTT->GetNbinsX(),TTTT->GetXaxis()->GetXmin(),TTTT->GetXaxis()->GetXmax());
      //for(int j=1; j<data->GetNbinsX()+1; j++){
      for(int j=1; j<TTTT->GetNbinsX()+1; j++){
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
    }
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
*/
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
