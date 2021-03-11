#include "eventYieldAndSerepartianPower.h"

#include "TH1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1D.h"
#include "THStack.h"
#include "TSystem.h"
#include "TLatex.h"
#include "TLegend.h"
#include <iostream>
#include "TROOT.h"
#include "TMath.h"
#include "TString.h"
#include "TCut.h"


void eventYieldAndSerepartianPower(){ 
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

  vector<TString> variablelist;                vector<int> bin;      vector<float> Min;      vector<float> Max;     vector<TString> axis;
//variablelist is plots we want to show   
//?is there a more clever way to push_back all in a loop?

  variablelist.push_back("jetsL_number");      bin.push_back(40);     Min.push_back(0);    Max.push_back(40);    axis.push_back("Number of jets");
  /*{{{*/
// variablelist.push_back("jetsL_HT"); bin.push_back(100);     Min.push_back(0);    Max.push_back(10000);    axis.push_back("HT pt[GeV]");
// variablelist.push_back("jetsL_MHT"); bin.push_back(100);     Min.push_back(0);    Max.push_back(10000);    axis.push_back("MHT pt[GeV]");
  // variablelist.push_back("jetsL_invariantMass");  bin.push_back(100);     Min.push_back(10);    Max.push_back(10000);    axis.push_back("Invariant mass of jets");
 // variablelist.push_back("jetsL_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(10000);    axis.push_back("jetsL_transMass");
 // variablelist.push_back("jetL_minDeltaR");      bin.push_back(100);     Min.push_back(0);    Max.push_back(6);    axis.push_back("min delta R of loose jets");
 // variablelist.push_back("jetsL_centrality");      bin.push_back(100);     Min.push_back(0);    Max.push_back(8);    axis.push_back("jetsL_centrality");
 // variablelist.push_back("jetsL_HTDividedByMet");      bin.push_back(100);     Min.push_back(0);    Max.push_back(200);    axis.push_back("HT / MET");
 // variablelist.push_back("jetsL_MHTDividedByMet");      bin.push_back(100);     Min.push_back(0);    Max.push_back(200);    axis.push_back("MHT / MET");
 // variablelist.push_back("MetDividedByHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("MetDividedByHT");
 // variablelist.push_back("jetsL_bScore");      bin.push_back(50);     Min.push_back(0);    Max.push_back(20);    axis.push_back("jetsL_bScore");
 // variablelist.push_back("jetsL_average_deltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(10);    axis.push_back("average delta R of loose jets");
 // variablelist.push_back("jetsL_4largestBscoreSum");      bin.push_back(50);     Min.push_back(0);    Max.push_back(10);    axis.push_back("jetsL_4largestBscoreSum");
 // variablelist.push_back("jetsL_leading2invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(8000);    axis.push_back("jetsL_leading2invariantMass");
 // variablelist.push_back("jetsL_rationHT_4toRest");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("jetsL_rationHT_4toRest");
  // variablelist.push_back("jetsL_leptonsMVAT_minDeltaR");      bin.push_back(10);     Min.push_back(0);    Max.push_back( 2);    axis.push_back("min delta R of loose jets and tight leptons");
  //Error in <TH1F::DrawNormalized>: Sum of weights is null. Cannot normalize histogram: BG
  //this is correct because after the CUT the event is indeed 0;
  // variablelist.push_back("jetsL_tausF_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(10);    axis.push_back("min delta R of loose jets and fakeble taus");
 // variablelist.push_back("jetsL_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("jetsL_1pt");
 // variablelist.push_back("jetsL_1eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("leading loose jet eta");
 // variablelist.push_back("jetsL_1phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("leading loose jet phi");
 // variablelist.push_back("jetsL_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("second loose jet pt");
 // variablelist.push_back("jetsL_2eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("second loose jet eta");
 // variablelist.push_back("jetsL_2phi");      bin.push_back(50);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("second loose jet phi");
 // variablelist.push_back("jetsL_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("third loose jet pt");
 // variablelist.push_back("jetsL_3eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("third loose jet eta");
 // variablelist.push_back("jetsL_3phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("third loose jet phi");
 // variablelist.push_back("jetsL_4pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("fourth loose jet pt");
 // variablelist.push_back("jetsL_4eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("fourth loose jet eta");
 // variablelist.push_back("jetsL_4phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("fourth loose jet phi");
 // variablelist.push_back("jetsL_5pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("fifth loose jet pt");
 // variablelist.push_back("jetsL_5eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("fifth loose jet eta");
 // variablelist.push_back("jetsL_5phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("fifth loose jet phi");
 // variablelist.push_back("jetsL_6pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("sixth loose jet pt");
 // variablelist.push_back("jetsL_6eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("sixth loose jet eta");
 // variablelist.push_back("jetsL_6phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("sixth loose jet phi");
 // variablelist.push_back("jetsL_7pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("seventh loose jet pt");
 // variablelist.push_back("jetsL_7eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("senventh loose jet eta");
 // variablelist.push_back("jetL_7phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("seventh loose jet phi");
 // variablelist.push_back("jetsL_8pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("jetsL_8pt");
 // variablelist.push_back("jetsL_8eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("eighth loose jet eta");
 // variablelist.push_back("jetsL_8phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("eighth loose jet phi");
 // variablelist.push_back("jetsL_9pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("nineth loose jet pt");
 // variablelist.push_back("jetsL_9eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("nineth loose jet eta");
 // variablelist.push_back("jetsL_9phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("nineth loose jet phi");
 // variablelist.push_back("jetsL_10pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tenth loose jet pt");
 // variablelist.push_back("jetsL_10eta");      bin.push_back(20);     Min.push_back(-3);    Max.push_back(3);    axis.push_back("tenth loose jet eta");
 // variablelist.push_back("jetsL_10phi");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("tenth loose jet phi");
 // variablelist.push_back("jetsL_11pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("eleventh loose jet pt");
 // variablelist.push_back("jetsL_11phi");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("jetsL_11phi");
 // variablelist.push_back("jetsL_11eta");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("jetsL_11eta");
 // variablelist.push_back("");      bin.push_back(100);     Min.push_back(0);    Max.push_back();    axis.push_back("");

 // variablelist.push_back("bjetsL_num");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("Number of loose b jets");
 // variablelist.push_back("bjetsM_num");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("Number of medium b jets");
 // variablelist.push_back("bjetsT_num");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of tight b jets");
 // variablelist.push_back("bjetsL_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsL_HT");
 // variablelist.push_back("bjetsM_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsM_HT");
 // variablelist.push_back("bjetsT_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsT_HT");
 // variablelist.push_back("bjetsL_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsL_MHT");
 // variablelist.push_back("bjetsM_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsM_MHT");
 // variablelist.push_back("bjetsT_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsT_MHT");
 // variablelist.push_back("bjetsL_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("invariant mass of loose b jets");
 // variablelist.push_back("bjetsM_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsM_invariantMass");
 // variablelist.push_back("bjetsT_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsT_invariantMass");
 // variablelist.push_back("bjetsL_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsL_transMass");
 // variablelist.push_back("bjetsM_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsM_transMass");
 // variablelist.push_back("bjetsT_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("bjetsT_transMass");
 // variablelist.push_back("bjetsL_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(6);    axis.push_back("min delta R of loose b jets");
 // variablelist.push_back("bjetsM_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(6);    axis.push_back("min delta R of medium b jets");
 // variablelist.push_back("bjetsT_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(6);    axis.push_back("min delta R of tight b jets");
 // variablelist.push_back("bjetsL_leptonsMVAT_minDeltaR");      bin.push_back(25);     Min.push_back(0);    Max.push_back(5);    axis.push_back("bjetsL_leptonsMVAT_minDeltaR");
 // variablelist.push_back("bjetsM_leptonsMVAT_minDeltaR");      bin.push_back(25);     Min.push_back(0);    Max.push_back(5);    axis.push_back("bjetsM_leptonsMVAT_minDeltaR");
 // variablelist.push_back("bjetsT_leptonsMVAT_minDeltaR");      bin.push_back(25);     Min.push_back(0);    Max.push_back(5);    axis.push_back("bjetsT_leptonsMVAT_minDeltaR");
 // variablelist.push_back("bjetsL_tausF_minDeltaR");      bin.push_back(25);     Min.push_back(0);    Max.push_back(5);    axis.push_back("bjetsL_tausF_minDeltaR");
 // variablelist.push_back("bjetsL_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsL_1pt");
 // variablelist.push_back("bjetsL_1eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_1eta");
 // variablelist.push_back("bjetsL_1phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_1phi");
 // variablelist.push_back("bjetsL_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsL_2pt");
 // variablelist.push_back("bjetsL_2eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_2eta");
 // variablelist.push_back("bjetsL_2phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_2phi");
 // variablelist.push_back("bjetsL_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("bjetsL_3pt");
 // variablelist.push_back("bjetsL_3eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_3eta");
 // variablelist.push_back("bjetsL_3phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_3phi");
 // variablelist.push_back("bjetsL_4pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("bjetsL_4pt");
 // variablelist.push_back("bjetsL_4eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_4eta");
 // variablelist.push_back("bjetsL_4phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("bjetsL_4phi");
 // variablelist.push_back("bjetsM_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsM_1pt");
 // variablelist.push_back("bjetsM_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsM_2pt");
 // variablelist.push_back("bjetsM_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsM_3pt");
 // variablelist.push_back("bjetsM_4pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsM_4pt");
 // variablelist.push_back("bjetsT_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsT_1pt");
 // variablelist.push_back("bjetsT_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(2000);    axis.push_back("bjetsT_2pt");
 // variablelist.push_back("bjetsT_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("bjetsT_3pt");
 // variablelist.push_back("bjetsT_4pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("bjetsT_4pt");
 // variablelist.push_back("");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("");
//

  // variablelist.push_back("forwardJets_num");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("Number of forward jets");
 // variablelist.push_back("forwardjet_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("leading forward jet pt");
 // variablelist.push_back("forwardjet_1eta");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("forwardjet_1eta");
 // variablelist.push_back("forwardjet_1phi");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("forwardjet_1phi");
 // variablelist.push_back("forwardjet1_jetsL_minDeltaEta");      bin.push_back(20);     Min.push_back(0);    Max.push_back(5);    axis.push_back("forwardjet1_jetsL_minDeltaEta");
//
// variablelist.push_back("Met_pt");  bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);   axis.push_back("Met pt[GeV] ");
// variablelist.push_back("Met_phi"); bin.push_back(8);     Min.push_back(-4);   Max.push_back(4);      axis.push_back("Met #phi");
//
//  
 // variablelist.push_back("leptonsMVAF_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("Number of fakeble leptons");
 // variablelist.push_back("leptonsMVAT_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("Number of Tight Leptons");
 // variablelist.push_back("leptonsMVAL_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("leptonsMVAL_number");
 // variablelist.push_back("leptonsMVAT_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("leptonsMVAT_transMass");//?
 // variablelist.push_back("leptonsMVAF_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("leptonsMVAF_transMass");//?
 // variablelist.push_back("leptonsMVAL_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("");//?
 // variablelist.push_back("leptonsMVAT_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(3000);    axis.push_back("leading tight lepton pt");
 // variablelist.push_back("leptonsMVAT_1eta");      bin.push_back(20);     Min.push_back(-3);    Max.push_back(3);    axis.push_back("leading tight lepton eta");
 // variablelist.push_back("leptonsMVAT_1phi");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("leading tight lepton phi");
 // variablelist.push_back("leptonsMVAT_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("second tight lepton pt");
 // variablelist.push_back("leptonsMVAT_2eta");      bin.push_back(20);     Min.push_back(-3);    Max.push_back(3);    axis.push_back("second tight lepton eta");
 // variablelist.push_back("leptonsMVAT_2phi");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("second tight lepton phi");
 // variablelist.push_back("leptonsMVAT_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(100);    axis.push_back("third tight lepton pt");
 // variablelist.push_back("leptonsMVAT_3eta");      bin.push_back(20);     Min.push_back(-3);    Max.push_back(3);    axis.push_back("third tight lepton eta");
 // variablelist.push_back("leptonsMVAT_3phi");      bin.push_back(20);     Min.push_back(-4);    Max.push_back(4);    axis.push_back("third tight lepton phi");
 // variablelist.push_back("elesMVAL_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of loose electron");
 // variablelist.push_back("elesMVAT_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of tight electrons");
 // variablelist.push_back("elesMVAF_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of fakeble electrons");
 // variablelist.push_back("elesMVAF_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("leading tight electron pt");
 // variablelist.push_back("muonsL_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of loose muons");
 // variablelist.push_back("muonsT_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of tight mouns");
 // variablelist.push_back("muonsF_number");      bin.push_back(100);     Min.push_back(0);    Max.push_back(10);    axis.push_back("muonsF_number");//?
 // variablelist.push_back("muonsT_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("muonsT_1pt");//?
 // variablelist.push_back("muonsT_1eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("muonsT_1eta");//?
 // variablelist.push_back("muonsT_1phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("muonsT_1phi");//?
 // variablelist.push_back("muonsT_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("muonsT_2pt");//?
 // variablelist.push_back("muonsT_2eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("muonsT_2eta");//?
 // variablelist.push_back("muonsT_2phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("muonsT_2phi");//?
 // variablelist.push_back("muonsT_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5000);    axis.push_back("muonsT_3pt");//?
 // variablelist.push_back("muonsT_3eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("muonsT_3eta");//?
 // variablelist.push_back("muonsT_3phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("muonsT_3phi");//?
//
 // variablelist.push_back("tausL_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of loose tau");
 // variablelist.push_back("tausF_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of fakeble tau");
 // variablelist.push_back("tausT_number");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("number of fakeble tau");
 // variablelist.push_back("tausL_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("MHT of loose tau");
 // variablelist.push_back("tausF_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("MHT of fakeble tau");
 // variablelist.push_back("tausT_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("MHT of T tau");
 // variablelist.push_back("tausL_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("HT of L tau");
 // variablelist.push_back("tausF_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausF_HT");
 // variablelist.push_back("tausT_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausT_HT");
 // variablelist.push_back("tausL_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausL_invariantMass");
 // variablelist.push_back("tausF_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("invariant mass of fakeble tau");
 // variablelist.push_back("tausT_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausT_invariantMass");
 // variablelist.push_back("tausL_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(6);    axis.push_back("min delta R of loose tau");
 // variablelist.push_back("tausF_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(6);    axis.push_back("tausF_minDeltaR");
 // variablelist.push_back("tausT_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(6);    axis.push_back("tausT_minDeltaR");
 // variablelist.push_back("tausF_leptonsT_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("transverse mass of fakeble taus and tight leptons");
 // variablelist.push_back("tausT_leptonsT_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("transvese mass of tight taus and tight leptons");
 // variablelist.push_back("tausL_leptonsT_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausL_leptonsT_transMass");
 // variablelist.push_back("tausF_leptonsT_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("invariant mass of fakeble taus and tight leptons");
 // variablelist.push_back("tausL_leptonsT_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausL_leptonsT_invariantMass");
 // variablelist.push_back("tausT_leptonsT_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tausT_leptonsT_invariantMass");
 // variablelist.push_back("tausF_leptonsT_chargeSum");      bin.push_back(10);     Min.push_back(0);    Max.push_back(10);    axis.push_back("charge sum of fakeble taus and tight leptons");
 // variablelist.push_back("tausF_leptonsTMVA_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(5);    axis.push_back("min delta R of tight leptons and fakeble taus");
 // variablelist.push_back("tausL_leptonsTMVA_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(10);    axis.push_back("tausL_leptonsTMVA_minDeltaR");
 // variablelist.push_back("tausT_leptonsTMVA_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(10);    axis.push_back("tausT_leptonsTMVA_minDeltaR");
 // variablelist.push_back("tauL_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tauL_1pt");
 // variablelist.push_back("tauL_1eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("tauL_1eta");
 // variablelist.push_back("tauL_1phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("tauL_1phi");
 // variablelist.push_back("tauL_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tauL_2pt");
 // variablelist.push_back("tauL_2eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("tauL_2eta");
 // variablelist.push_back("tauL_3pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("tauL_3pt");
 // variablelist.push_back("tauL_3eta");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("tauL_3eta");
 // variablelist.push_back("tauL_3phi");      bin.push_back(20);     Min.push_back(-5);    Max.push_back(5);    axis.push_back("tauL_3phi");

 // variablelist.push_back("toptagger_num");      bin.push_back(100);     Min.push_back(0);    Max.push_back(5);    axis.push_back("number of tops");
 // variablelist.push_back("toptagger_MHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(6000);    axis.push_back("toptagger_MHT");
 // variablelist.push_back("toptagger_HT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(6000);    axis.push_back("toptagger_HT");
 // variablelist.push_back("toptagger_invariantMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(6000);    axis.push_back("toptagger_invariantMass");
 // variablelist.push_back("toptagger_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(6000);    axis.push_back("toptagger_transMass");
 // variablelist.push_back("toptagger_minDeltaR_v1");      bin.push_back(100);     Min.push_back(0);    Max.push_back(6);    axis.push_back("toptagger_minDeltaR_v1");
 // variablelist.push_back("toptagger_1pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("leading top pt");
 // variablelist.push_back("toptagger_1eta");      bin.push_back(20);     Min.push_back(-6);    Max.push_back(6);    axis.push_back("toptagger_1eta");
 // variablelist.push_back("toptagger_1phi");      bin.push_back(20);     Min.push_back(-6);    Max.push_back(6);    axis.push_back("toptagger_1phi");
 // variablelist.push_back("toptagger_2pt");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("second top pt");
 // variablelist.push_back("toptagger_2eta");      bin.push_back(20);     Min.push_back(-6);    Max.push_back(6);    axis.push_back("toptagger_2eta");
 // variablelist.push_back("toptagger_2phi");      bin.push_back(20);     Min.push_back(-6);    Max.push_back(6);    axis.push_back("toptagger_2phi");
 // variablelist.push_back("toptagger_3eta");      bin.push_back(20);     Min.push_back(-6);    Max.push_back(6);    axis.push_back("toptagger_3eta");
 // variablelist.push_back("toptagger_3phi");      bin.push_back(20);     Min.push_back(-6);    Max.push_back(6);    axis.push_back("toptagger_3phi");
 // variablelist.push_back("toptagger_minDeltaR");      bin.push_back(20);     Min.push_back(0);    Max.push_back(5);    axis.push_back("min delta R of tops");
 // variablelist.push_back("toptagger_scoreAllTops");      bin.push_back(20);     Min.push_back(0);    Max.push_back(5);    axis.push_back("top tagger score of all tops");[>}}}<]



  //apply selection cuts here
const TCut ES1tau0l_step1 = "tausT_number==1 ";
const TCut ES1tau1e_step1 = "tausT_number==1 ";
const TCut ES1tau1m_step1 = "tausT_number==1 ";
const TCut ES1tau2os_step1 = "tausT_number==1 ";
const TCut ES1tau2ss_step1 = "tausT_number==1 ";
const TCut ES1tau3l_step1 = "tausT_number==1 ";
const TCut ES2tau0l_step1 = "tausT_number==2 ";
const TCut ES2tau1e_step1 = "tausT_number==2 ";
const TCut ES2tau1m_step1 = "tausT_number==2 ";
const TCut ES2tau2os_step1 = "tausT_number==2 ";
const TCut ES2tau2ss_step1 = "tausT_number==2 ";
//step2
const TCut ES1tau0l_step2 = "tausT_number==1 && leptonsMVAT_number==0 ";
const TCut ES1tau1e_step2 = "tausT_number==1 && elesMVAT_number==1 ";
const TCut ES1tau1m_step2 = "tausT_number==1 && muonsT_number==1 ";
const TCut ES1tau2os_step2 = "tausT_number==1 && leptonsMVAT_number==2 && leptonsMVAT_2OS==1  ";
const TCut ES1tau2ss_step2 = "tausT_number==1 && leptonsMVAT_number==2 && leptonsMVAT_2SS==1 ";
const TCut ES1tau3l_step2 = "tausT_number==1 && leptonsMVAT_number==3 ";
const TCut ES2tau0l_step2 = "tausT_number==2 && leptonsMVAT_number==0 ";
const TCut ES2tau1e_step2 = "tausT_number==2 && elesMVAT_number==1 ";
const TCut ES2tau1m_step2 = "tausT_number==2 && muonsT_number==0 ";
const TCut ES2tau2os_step2 = "tausT_number==2 && leptonsMVAT_number==2 && leptonsMVAT_2OS==1  ";
const TCut ES2tau2ss_step2 = "tausT_number==2 && leptonsMVAT_number==2 && leptonsMVAT_2SS==1 ";
//step3
const TCut ES1tau0l_step3 = "tausT_number==1 && leptonsMVAT_number==0 &&  jetsL_number>=8 ";
const TCut ES1tau1e_step3 = "tausT_number==1 && elesMVAT_number==1 &&  jetsL_number>=6 ";
const TCut ES1tau1m_step3 = "tausT_number==1 && muonsT_number==1 &&  jetsL_number>=6 ";
const TCut ES1tau2os_step3 = "tausT_number==1 && leptonsMVAT_number==2 && leptonsMVAT_2OS==1  &&  jetsL_number>=4 ";
const TCut ES1tau2ss_step3 = "tausT_number==1 && leptonsMVAT_number==2 && leptonsMVAT_2SS==1 &&  jetsL_number>=4 ";
const TCut ES1tau3l_step3 = "tausT_number==1 && leptonsMVAT_number==3 &&  jetsL_number>=2 ";
const TCut ES2tau0l_step3 = "tausT_number==2 && leptonsMVAT_number==0 &&  jetsL_number>=6 ";
const TCut ES2tau1e_step3 = "tausT_number==2 && elesMVAT_number==1 &&  jetsL_number>=4 ";
const TCut ES2tau1m_step3 = "tausT_number==2 && muonsT_number==0 &&  jetsL_number>=4 ";
const TCut ES2tau2os_step3 = "tausT_number==2 && leptonsMVAT_number==2 && leptonsMVAT_2OS==1  && jetsL_number>=2 ";
const TCut ES2tau2ss_step3 = "tausT_number==2 && leptonsMVAT_number==2 && leptonsMVAT_2SS==1 &&  jetsL_number>=2 ";
//step4
      //
const TCut ES1tau0l = "tausT_number==1 && leptonsMVAT_number==0 &&  jetsL_number>=8 && bjetsM_num>=2";
const TCut ES1tau1e = "tausT_number==1 && elesMVAT_number==1 && leptonsMVAT_number==1 &&  jetsL_number>=6 && bjetsM_num>=2";
const TCut ES1tau1m = "tausT_number==1 && muonsT_number==1 && leptonsMVAT_number==1&& jetsL_number>=6 && bjetsM_num>=2";
const TCut ES1tau2os = "tausT_number==1 && leptonsMVAT_number==2 && leptonsMVAT_2OS==1  &&  jetsL_number>=4 && bjetsM_num>=2";
const TCut ES1tau2ss = "tausT_number==1 && leptonsMVAT_number==2 && leptonsMVAT_2SS==1 &&  jetsL_number>=4 && bjetsM_num>=2";
const TCut ES1tau3l = "tausT_number==1 && leptonsMVAT_number==3 &&  jetsL_number>=2 && bjetsM_num>=2";
const TCut ES2tau0l = "tausT_number==2 && leptonsMVAT_number==0 &&  jetsL_number>=6 && bjetsM_num>=2";
const TCut ES2tau1e = "tausT_number==2 && elesMVAT_number==1 && leptonsMVAT_number==1 && jetsL_number>=4 && bjetsM_num>=2";
const TCut ES2tau1m = "tausT_number==2 && muonsT_number==1 && leptonsMVAT_number==1 &&  jetsL_number>=4 && bjetsM_num>=2";
const TCut ES2tau2os = "tausT_number==2 && leptonsMVAT_number==2 && leptonsMVAT_2OS==1  && jetsL_number>=2 && bjetsM_num>=2";
const TCut ES2tau2ss = "tausT_number==2 && leptonsMVAT_number==2 && leptonsMVAT_2SS==1 &&  jetsL_number>=2 && bjetsM_num>=2";
const TCut weight = "EVENT_genWeight";

vector<string> channelName = { "1Tau0L", "1Tau1E", "1Tau1Mu", "1Tau2OS", "1Tau2SS", "1Tau3L","2Tau0L", "2Tau1E", "2Tau1Mu", "2Tau2OS", "2Tau2SS"   };
vector<TCut>   channelCut   = { ES1tau0l, ES1tau1e,  ES1tau1m, ES1tau2os, ES1tau2ss, ES1tau3l, ES2tau0l, ES2tau1e, ES2tau1m, ES2tau2os, ES2tau2ss };
vector<TCut>   channelCut_step1   = { ES1tau0l_step1, ES1tau1e_step1,  ES1tau1m_step1, ES1tau2os_step1, ES1tau2ss_step1, ES1tau3l_step1, ES2tau0l_step1, ES2tau1e_step1, ES2tau1m_step1, ES2tau2os_step1, ES2tau2ss_step1};
vector<TCut>   channelCut_step2   = { ES1tau0l_step2, ES1tau1e_step2,  ES1tau1m_step2, ES1tau2os_step2, ES1tau2ss_step2, ES1tau3l_step2, ES2tau0l_step2, ES2tau1e_step2, ES2tau1m_step2, ES2tau2os_step2, ES2tau2ss_step2 };
vector<TCut>   channelCut_step3   = { ES1tau0l_step3, ES1tau1e_step3,  ES1tau1m_step3, ES1tau2os_step3, ES1tau2ss_step3, ES1tau3l_step3, ES2tau0l_step3, ES2tau1e_step3, ES2tau1m_step3, ES2tau2os_step3, ES2tau2ss_step3 };




// for (UInt_t  cha=0; cha<channelName.size(); cha++){
for (UInt_t  cha=0; cha<1; cha++){
    TString postfix = channelName[cha] + ".png";
    std::map<float, TString> mymap;
    for(UInt_t i=0; i<1; i++){
  // for(UInt_t i=0; i<variablelist.size(); i++){
  	    const char *plot = variablelist[i];

        TH1D* TTTT = new TH1D("TTTT",plot,bin[i],Min[i],Max[i]);//1
        TH1D* TTTo2L2Nu = new TH1D( "TT",plot,bin[i],Min[i],Max[i]); TH1D* TTToHadronic = new TH1D( "TT",plot,bin[i],Min[i],Max[i]); 
        TH1D* TTGJets = new TH1D( "TTGJets",plot,bin[i],Min[i],Max[i]);TH1D* ttZJets = new TH1D( "ttZJets",plot,bin[i],Min[i],Max[i]); TH1D* ttWJets = new TH1D( "ttWJets",plot,bin[i],Min[i],Max[i]);TH1D* ttH = new TH1D( "ttH",plot,bin[i],Min[i],Max[i]); /*TH1D* ttbb = new TH1D( "ttbb",plot,bin[i],Min[i],Max[i]);*/ //6
        TH1D* WZ = new TH1D( "WZ",plot,bin[i],Min[i],Max[i]); TH1D* WWTo2L2Nu = new TH1D( "WWTo2L2Nu",plot,bin[i],Min[i],Max[i]); TH1D* WpWpJJ = new TH1D( "WpWpJJ",plot,bin[i],Min[i],Max[i]);TH1D* ZZ = new TH1D( "ZZ",plot,bin[i],Min[i],Max[i]);TH1D* WGJets = new TH1D( "WGJets",plot,bin[i],Min[i],Max[i]);TH1D* ZGJetsToLLG = new TH1D( "ZGJetsToLLG",plot,bin[i],Min[i],Max[i]);//6
        TH1D* WWW = new TH1D( "WWW",plot,bin[i],Min[i],Max[i]); TH1D* WWZ = new TH1D( "WWZ",plot,bin[i],Min[i],Max[i]); TH1D* WWG = new TH1D( "WWG",plot,bin[i],Min[i],Max[i]); TH1D* ZZZ = new TH1D( "ZZZ",plot,bin[i],Min[i],Max[i]); TH1D* WZZ = new TH1D( "WZZ",plot,bin[i],Min[i],Max[i]); TH1D* WZG = new TH1D( "WZG",plot,bin[i],Min[i],Max[i]); TH1D* WGG = new TH1D( "WGG",plot,bin[i],Min[i],Max[i]); TH1D* ZGGJets = new TH1D( "ZGGJets",plot,bin[i],Min[i],Max[i]);//8
        TH1D* WJetsToLNu = new TH1D( "WJetsToLNu",plot,bin[i],Min[i],Max[i]); TH1D* DYJetsToTauTau = new TH1D( "DYJetsToTauTau",plot,bin[i],Min[i],Max[i]);//2
        TH1D* tZq_ll = new TH1D( "tZq_ll",plot,bin[i],Min[i],Max[i]); TH1D* ST_tW_antitop = new TH1D( "ST_tW_antitop",plot,bin[i],Min[i],Max[i]); TH1D* ST_tW_top = new TH1D( "ST_tW_top",plot,bin[i],Min[i],Max[i]); TH1D* TGJets = new TH1D( "TGJets",plot,bin[i],Min[i],Max[i]);TH1D* THW = new TH1D( "THW",plot,bin[i],Min[i],Max[i]); TH1D* THQ = new TH1D( "THQ",plot,bin[i],Min[i],Max[i]);//6
        TH1D* VHToNonbb = new TH1D( "VHToNonbb",plot,bin[i],Min[i],Max[i]); TH1D* ZHToTauTau = new TH1D( "ZHToTauTau",plot,bin[i],Min[i],Max[i]); TH1D* ZH_HToBB_ZToLL = new TH1D( "ZH_HToBB_ZToLL",plot,bin[i],Min[i],Max[i]); TH1D* GluGluHToZZTo4L = new TH1D( "GluGluHToZZTo4L",plot,bin[i],Min[i],Max[i]); TH1D* GluGluHToBB = new TH1D( "GluGluHToBB",plot,bin[i],Min[i],Max[i]); TH1D* GluGluHToGG = new TH1D( "GluGluHToGG",plot,bin[i],Min[i],Max[i]); TH1D* GluGluHToMuMu = new TH1D( "GluGluHToMuMu",plot,bin[i],Min[i],Max[i]); TH1D* GluGluHToTauTau = new TH1D( "GluGluHToTauTau",plot,bin[i],Min[i],Max[i]); TH1D* GluGluHToWWTo2L2Nu = new TH1D( "GluGluHToWWTo2L2Nu",plot,bin[i],Min[i],Max[i]); TH1D* GluGluHToWWToLNuQQ = new TH1D( "GluGluHToWWToLNuQQ",plot,bin[i],Min[i],Max[i]); TH1D* VBFHToWWTo2L2Nu = new TH1D( "VBFHToWWTo2L2Nu",plot,bin[i],Min[i],Max[i]);/* TH1D* VBFHToTauTau = new TH1D( "VBFHToTauTau",plot,bin[i],Min[i],Max[i]); */TH1D* VBFHToMuMu = new TH1D( "VBFHToMuMu",plot,bin[i],Min[i],Max[i]); TH1D* VBFHToGG = new TH1D( "VBFHToGG",plot,bin[i],Min[i],Max[i]); 
        vector<TH1D*> allHistos  {
            TTTT,//0
            TTTo2L2Nu, TTToHadronic,
            // TTGJets,ttZJets,ttWJets,ttH, //5
            // WZ,  WWTo2L2Nu,  WpWpJJ, ZZ, WGJets, ZGJetsToLLG,//11
             // WWW,  WWZ,  WWG,  ZZZ,  WZZ,  WZG,  WGG,  ZGGJets,//19
             // WJetsToLNu,  DYJetsToTauTau,//21
             // tZq_ll,  ST_tW_antitop,  ST_tW_top,  TGJets, THW,  THQ,//27
             // VHToNonbb,  ZHToTauTau,  ZH_HToBB_ZToLL,  GluGluHToZZTo4L,  GluGluHToBB,  GluGluHToGG,  GluGluHToMuMu,  GluGluHToTauTau,  GluGluHToWWTo2L2Nu,  GluGluHToWWToLNuQQ,  VBFHToWWTo2L2Nu, [> VBFHToTauTau, <] VBFHToMuMu,  VBFHToGG// 40
        };
        // TH1::SetDefaultSumw2();// TH1::Sumw2 to force the storage and computation of the sum of the square of weights per bin.umw2 has been called, the error per bin is computed as the sqrt(sum of squares of weights), otherwise the error is set equal to the sqrt(bin content)
        TH1D* background_SR = new TH1D("BG","BG",bin[i],Min[i],Max[i]);

        // cout<<"signal and bg files ="<< allHistos.size()<<endl;
        // cout<<"number of trees = "<<allTree.size()<<endl;
        TString hname ;
        double scale;
        Double_t sumGenWeights = -99;
        TH1D* h_genWeight = new TH1D( "genWeight", "genWeight", 100, -100., 100.);
        for(UInt_t j = 0; j < allHistos.size(); j++){
            // char input[50]; sprintf(input,"%s>>h(%i,%f,%f)",plot,bin[i],Min[i],Max[i]);
            hname = allHistos[j]->GetName();
            
            h_genWeight->Reset( "ICES");
            h_genWeight->Print();
            allTree_gen[j]->Project( "genWeight", "genWeight_allEvents");
            h_genWeight->Print();
            sumGenWeights = h_genWeight->GetMean() * h_genWeight->GetEntries();
            cout<<"sumGenWeights = "<<sumGenWeights<<endl;

            // allTree[j]->Project( hname, plot, weight*channelCut[cha] );//step4
            allTree[j]->Project(hname,plot, weight);//step0
            // allTree[j]->Project( hname, "jetsL_number", weight);//step0
            // allTree[j]->Project(hname,plot, weight*channelCut_step1[cha]);//step1
            // allTree[j]->Project(hname,plot, weight*channelCut_step2[cha]);//step2
            // allTree[j]->Project(hname,plot, weight*channelCut_step3[cha]);//step3
           allHistos[j]->Print();


            // scale = allSigmas[j]/allgenWeights[j]->GetSumOfWeights();
            scale = allSigmas[j]/sumGenWeights;
            allHistos[j]->Scale(scale);
            // if( j==1 ) cout<<allgenWeights[j]->GetSumOfWeights()<<endl;
            if(j > 0) background_SR->Add((allHistos[j]),1);
//            background_SR->Print();

        }

        if(i==0){
            cout<<endl;
            cout<<"Plotting "<<variablelist[i]<<postfix<<endl;
            cout<<"TTTT   = "<<(allHistos[0])->Integral()<<endl;
            cout<<"TT     = "<<allHistos[1]->Integral()<<endl;
            // cout<<"TTX    = "<<allHistos[2]->Integral()+allHistos[3]->Integral()+allHistos[4]->Integral()+allHistos[5]->Integral()<<endl;
            // cout<<"VV     = "<<allHistos[6]->Integral()+allHistos[7]->Integral()+allHistos[8]->Integral()+allHistos[9]->Integral()+allHistos[10]->Integral()+allHistos[11]->Integral()<<endl;
            // cout<<"VVV    = "<<allHistos[12]->Integral()+allHistos[13]->Integral()+allHistos[14]->Integral()+allHistos[15]->Integral()+allHistos[16]->Integral()+allHistos[17]->Integral()+allHistos[18]->Integral()+allHistos[19]->Integral()<<endl;
            // cout<<"WJets  = "<<allHistos[20]->Integral()<<endl;
            // cout<<"DY     = "<<allHistos[21]->Integral()<<endl;
            // cout<<"ST     = "<<allHistos[22]->Integral()+allHistos[23]->Integral()+allHistos[24]->Integral()+allHistos[25]->Integral()+allHistos[26]->Integral()+allHistos[27]->Integral()<<endl;
            // cout<<"H      = "<<allHistos[28]->Integral()+allHistos[29]->Integral()+allHistos[30]->Integral()+allHistos[31]->Integral()+allHistos[32]->Integral()+allHistos[33]->Integral()+allHistos[34]->Integral()+allHistos[35]->Integral()+allHistos[36]->Integral()+allHistos[37]->Integral()+allHistos[38]->Integral()+allHistos[39]->Integral()+allHistos[40]->Integral()<<endl;
            cout<<"Total BKG    = "<<background_SR->Integral()<<endl;
            // cout<<"significance = "<<allHistos[0]->Integral()/(sqrt((allHistos[0])->Integral()+background_SR->Integral()));
            cout<<endl;
            
            cout<<"Statistics"<<endl;
            cout<<"TTTT   = "<<(allHistos[0])->Integral()/allScales_v2[0]<<endl;
            cout<<"TT     = "<<(allHistos[1]->Integral()/ allScales_v2[1])<<endl;
            // cout<<"TTX    = "<<(allHistos[2]->Integral()/ allScales_v2[2]) + (allHistos[3]->Integral()/allScales_v2[3]) + (allHistos[4]->Integral()/allScales_v2[4]) + ( allHistos[5]->Integral()/allScales_v2[5]) <<endl;
            // cout<<"VV     = "<<(allHistos[6]->Integral()/allScales_v2[6]) +(allHistos[7]->Integral()/allScales_v2[7]) +(allHistos[8]->Integral()/allScales_v2[8]) + (allHistos[9]->Integral()/allScales_v2[9]) + (allHistos[10]->Integral()/allScales_v2[10]) + (allHistos[11]->Integral()/allScales_v2[11]) <<endl;
            // cout<<"VVV    = "<<(allHistos[12]->Integral()/allScales_v2[12]) + (allHistos[13]->Integral()/allScales_v2[13]) + (allHistos[14]->Integral()/allScales_v2[14]) + (allHistos[15]->Integral()/allScales_v2[15]) + (allHistos[16]->Integral()/allScales_v2[16]) + (allHistos[17]->Integral()/allScales_v2[17]) + (allHistos[18]->Integral()/allScales_v2[18]) + (allHistos[19]->Integral()/allScales_v2[19]) <<endl;
            // cout<<"WJets  = "<<(allHistos[20]->Integral()*allScales_v2[20])<<endl;
            // cout<<"DY     = "<<(allHistos[21]->Integral()*allScales_v2[21])<<endl;
            // cout<<"ST     = "<<(allHistos[22]->Integral()/allScales_v2[22])+(allHistos[23]->Integral()/allScales_v2[23]) + (allHistos[24]->Integral()/allScales_v2[24]) + (allHistos[25]->Integral()/allScales_v2[25]) + (allHistos[26]->Integral()/allScales_v2[26]) + (allHistos[27]->Integral()/allScales_v2[27]) <<endl;
            // cout<<"H      = "<<(allHistos[28]->Integral()/allScales_v2[28])+(allHistos[29]->Integral()/allScales_v2[29]) + (allHistos[30]->Integral()/allScales_v2[30]) + (allHistos[31]->Integral()/allScales_v2[31]) + (allHistos[32]->Integral()/allScales_v2[32]) + (allHistos[33]->Integral()/allScales_v2[33]) + (allHistos[34]->Integral()/allScales_v2[34]) + (allHistos[35]->Integral()/allScales_v2[35]) + (allHistos[36]->Integral()/allScales_v2[36]) + (allHistos[37]->Integral()/allScales_v2[37]) + (allHistos[38]->Integral()/allScales_v2[38]) + (allHistos[39]->Integral()/allScales_v2[39]) + (allHistos[40]->Integral()/allScales_v2[40]) <<endl;
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
        allHistos[0]->SetLineWidth(2);
        allHistos[0]->SetLineColor(2);
//        allHistos[0]->SetLineColor(kViolet-2); 
       // allHistos[0]->Draw("samehisto");
        allHistos[0]->DrawNormalized("samehist", 1);
        // allHistos[0]->Draw("samehist");


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
        TLegendEntry *ple2 = pl2->AddEntry(allHistos[0], "TTTT",  "L"); 
    //    ple2 = pl2->AddEntry(hs, "TTX",  "L");
       // ple2 = pl2->AddEntry(TTJets_SR, "TTJets",  "L");
       // ple2 = pl2->AddEntry(WpWpJJ_SR, "WpWpJJ",  "L");
       // ple2 = pl2->AddEntry(ZZ_SR, "ZZ",  "L");
    //    ple2 = pl2->AddEntry(TTX, "TTX",  "L");
    //    ple2 = pl2->AddEntry(TT_SR, "TT",  "L");
        ple2 = pl2->AddEntry(background_SR, "background",  "L");
        pl2->Draw();
       

 
        TString NAME = variablelist[i];
       //c1->SaveAs(NAME+".pdf");
       // c1->SaveAs("/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_PlayWithMC_v1/reslult1/"+NAME+".pdf");
        c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/plotsAndResults/test/"+NAME+postfix);
        
        cout<<"Finished "<<NAME+postfix<<endl;
        c1->Draw();

        //?for different range we have different sp, how to deal with this?
        float sp = separationPower(allHistos[0], background_SR);
        cout<<NAME<<" separation power"<<sp<<endl;
        std::cout << '\n';
        if(i==(variablelist.size()-1)) cout<<channelName[cha]<<endl;
       // std::map<float, TString> mymap;
        mymap.insert(std::make_pair(sp, NAME));

        for(UInt_t j = 0; j < allHistos.size(); j++){
             delete (allHistos[j]);
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

}
}


float separationPower(TH1D* h1, TH1D* h2){
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
