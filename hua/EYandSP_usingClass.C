#include "EYandSP_usingClass.h"

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
#include "TStopwatch.h"


void EYandSP_usingClass(){ 
    TStopwatch t;
    t.Start();

    Bool_t ifSP = false;
    // Bool_t ifSP = true;

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

  vector<TString> variablelist;                vector<Int_t> bin;      vector<Double_t> Min;      vector<Double_t> Max;     vector<TString> axis;
//variablelist is plots we want to show   
//?is there a more clever way to push_back all in a loop?

  variablelist.push_back("jetsL_number");      bin.push_back(40);     Min.push_back(0);    Max.push_back(40);    axis.push_back("Number of jets");
  /*{{{*/
variablelist.push_back("jetsL_HT"); bin.push_back(100);     Min.push_back(0);    Max.push_back(10000);    axis.push_back("HT pt[GeV]");
variablelist.push_back("jetsL_MHT"); bin.push_back(100);     Min.push_back(0);    Max.push_back(10000);    axis.push_back("MHT pt[GeV]");
  variablelist.push_back("jetsL_invariantMass");  bin.push_back(100);     Min.push_back(10);    Max.push_back(10000);    axis.push_back("Invariant mass of jets");
 variablelist.push_back("jetsL_transMass");      bin.push_back(100);     Min.push_back(0);    Max.push_back(10000);    axis.push_back("jetsL_transMass");
 variablelist.push_back("jetL_minDeltaR");      bin.push_back(100);     Min.push_back(0);    Max.push_back(6);    axis.push_back("min delta R of loose jets");
 variablelist.push_back("jetsL_centrality");      bin.push_back(100);     Min.push_back(0);    Max.push_back(8);    axis.push_back("jetsL_centrality");
 variablelist.push_back("jetsL_HTDividedByMet");      bin.push_back(100);     Min.push_back(0);    Max.push_back(200);    axis.push_back("HT / MET");
 variablelist.push_back("jetsL_MHTDividedByMet");      bin.push_back(100);     Min.push_back(0);    Max.push_back(200);    axis.push_back("MHT / MET");
 variablelist.push_back("MetDividedByHT");      bin.push_back(100);     Min.push_back(0);    Max.push_back(1000);    axis.push_back("MetDividedByHT");
 variablelist.push_back("jetsL_bScore");      bin.push_back(50);     Min.push_back(0);    Max.push_back(20);    axis.push_back("jetsL_bScore");
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
const TCut weight = "EVENT_genWeight*EVENT_prefireWeight*PUWeight";

vector<string> channelName = { "1Tau0L", "1Tau1E", "1Tau1Mu", "1Tau2OS", "1Tau2SS", "1Tau3L","2Tau0L", "2Tau1E", "2Tau1Mu", "2Tau2OS", "2Tau2SS"   };
vector<TCut>   channelCut   = { ES1tau0l, ES1tau1e,  ES1tau1m, ES1tau2os, ES1tau2ss, ES1tau3l, ES2tau0l, ES2tau1e, ES2tau1m, ES2tau2os, ES2tau2ss };
vector<TCut>   channelCut_step1   = { ES1tau0l_step1, ES1tau1e_step1,  ES1tau1m_step1, ES1tau2os_step1, ES1tau2ss_step1, ES1tau3l_step1, ES2tau0l_step1, ES2tau1e_step1, ES2tau1m_step1, ES2tau2os_step1, ES2tau2ss_step1};
vector<TCut>   channelCut_step2   = { ES1tau0l_step2, ES1tau1e_step2,  ES1tau1m_step2, ES1tau2os_step2, ES1tau2ss_step2, ES1tau3l_step2, ES2tau0l_step2, ES2tau1e_step2, ES2tau1m_step2, ES2tau2os_step2, ES2tau2ss_step2 };
vector<TCut>   channelCut_step3   = { ES1tau0l_step3, ES1tau1e_step3,  ES1tau1m_step3, ES1tau2os_step3, ES1tau2ss_step3, ES1tau3l_step3, ES2tau0l_step3, ES2tau1e_step3, ES2tau1m_step3, ES2tau2os_step3, ES2tau2ss_step3 };

TCut MetFilters = "Flag_goodVertices==1 && Flag_globalSuperTightHalo2016Filter==1 && Flag_HBHENoiseFilter==1 && Flag_HBHENoiseIsoFilter==1 && Flag_EcalDeadCellTriggerPrimitiveFilter==1 && Flag_BadPFMuonFilter==1";
TCut trigger = "HLT_PFHT450_SixJet40_BTagCSV_p056==1 || HLT_PFHT400_SixJet30_DoubleBTagCSV_p056==1";





TH1D* TTTT_h ;//1
TH1D* TTTo2L2Nu_h ; TH1D* TTToHadronic_h ; TH1D* TTToSemiLeptonic_h ;
TH1D* TTGJets_h ;TH1D* ttZJets_h ; TH1D* ttWJets_h ;TH1D* ttH_h ; /*TH1D* ttbb_h ;*/ //6
TH1D* WZ_h ; TH1D* WW_h ; TH1D* ZZ_h ;TH1D* WGJets_h ;TH1D* ZGJetsToLLG_h ;//6
TH1D* WWW_h ; TH1D* WWZ_h ; TH1D* WWG_h ; TH1D* ZZZ_h ; TH1D* WZZ_h ; TH1D* WZG_h ; TH1D* WGG_h ; TH1D* ZGGJets_h ;//8
TH1D* WJetsToLNu_h ; TH1D* DYJetsToTauTau_h ;//2
TH1D* tZq_ll_h ;TH1D* tZq_nunu_h;  TH1D* ST_tW_antitop_h ; TH1D* ST_tW_top_h ; TH1D* TGJets_h ;TH1D* THW_h ; TH1D* THQ_h ;//6
TH1D* QCD_HT200to300_h; TH1D* QCD_HT300to500_h; TH1D* QCD_HT500to700_h; TH1D* QCD_HT700to1000_h;  TH1D* QCD_HT1000to1500_h; TH1D* QCD_HT1500to2000_h; TH1D* QCD_HT2000toInf_h;
TH1D* VHToNonbb_h ; TH1D* ZHToTauTau_h ; TH1D* ZH_HToBB_ZToLL_h ; TH1D* GluGluHToZZTo4L_h ; TH1D* GluGluHToBB_h ; TH1D* GluGluHToGG_h ; TH1D* GluGluHToMuMu_h ; TH1D* GluGluHToTauTau_h ; TH1D* GluGluHToWWTo2L2Nu_h ; TH1D* GluGluHToWWToLNuQQ_h ; TH1D* VBFHToWWTo2L2Nu_h ; TH1D* VBFHToTauTau_h ; TH1D* VBFHToMuMu_h ; TH1D* VBFHToGG_h ; 
TH1D* background_SR;
vector<TH1D*> allHistos;

// Double_t TTTT_entries; //0
// Double_t TTTo2L2Nu_entries; Double_t  TTToHadronic_entries; Double_t  TTToSemiLeptonic_entries; //3
// Double_t TTGJets_entries; Double_t  ttZJets_entries; Double_t ttWJets_entries; Double_t  ttH_entries; //7
// Double_t WZ_entries; Double_t  WW_entries; Double_t  ZZ_entries; Double_t  WGJets_entries; Double_t  ZGJetsToLLG_entries; //12
// Double_t WWW_entries; Double_t  WWZ_entries; Double_t  [>WWG<] ZZZ_entries; Double_t  WZZ_entries; Double_t  WZG_entries; Double_t  WGG_entries; Double_t  ZGGJets_entries;//20
// WJetsToLNu_entries; Double_t  DYJetsToTauTau_entries;//22
// Double_t tZq_ll_entries; [> tZq_nunu_entries; Double_t <] Double_t ST_tW_antitop_entries; Double_t  ST_tW_top_entries;  //26
// Double_t TGJets_entries; Double_t  THW_entries; Double_t  THQ_entries; //29
// Double_t QCD_HT200to300_entries; Double_t  QCD_HT300to500_entries; Double_t  QCD_HT500to700_entries; Double_t  QCD_HT700to1000_entries; Double_t  QCD_HT1000to1500_entries; Double_t  QCD_HT1500to2000_entries; Double_t  QCD_HT2000toInf_entries;
// VHToNonbb_entries; Double_t  [>ZHToTauTau_entries; Double_t */ ZH_HToBB_ZToLL_entries; Double_t /* GluGluHToZZTo4L_entries; Double_t */ /*GluGluHToBB.*/ GluGluHToGG_entries; Double_t  GluGluHToMuMu_entries; Double_t  GluGluHToTauTau_entries; Double_t  GluGluHToWWTo2L2Nu_entries; Double_t  GluGluHToWWToLNuQQ_entries; Double_t /* VBFHToWWTo2L2Nu_entries; Double_t  VBFHToTauTau_entries; Double_t  <]VBFHToMuMu_entries; Double_t  VBFHToGG_entries;
// vector<Double_t> rawEntries;
// for (UInt_t  cha=0; cha<channelName.size(); cha++){
for (UInt_t  cha=0; cha<1; cha++){
    TString postfix = channelName[cha] + ".png";
    cout<<channelName[cha]<<endl;
    std::map<Double_t, TString> mymap;

    for(UInt_t i=0; i<1; i++){
    // for(UInt_t i=0; i<variablelist.size(); i++){
  	    const char *plot = variablelist[i];

         TTTT_h = new TH1D("TTTT",plot,bin[i],Min[i],Max[i]);//1
         TTTo2L2Nu_h = new TH1D( "TTTo2L2Nu", plot,bin[i],Min[i],Max[i]);  TTToHadronic_h = new TH1D( "TTToHadronic",plot,bin[i],Min[i],Max[i]);  TTToSemiLeptonic_h = new TH1D( "TTToSemiLeptonic",plot,bin[i],Min[i],Max[i]);
         TTGJets_h = new TH1D( "TTGJets",plot,bin[i],Min[i],Max[i]); ttZJets_h = new TH1D( "ttZJets",plot,bin[i],Min[i],Max[i]);  ttWJets_h = new TH1D( "ttWJets",plot,bin[i],Min[i],Max[i]); ttH_h = new TH1D( "ttH",plot,bin[i],Min[i],Max[i]); /* ttbb_h = new TH1D( "ttbb",plot,bin[i],Min[i],Max[i]);*/ //6
         WZ_h = new TH1D( "WZ",plot,bin[i],Min[i],Max[i]);  WW_h = new TH1D( "WW",plot,bin[i],Min[i],Max[i]);  ZZ_h = new TH1D( "ZZ",plot,bin[i],Min[i],Max[i]); WGJets_h = new TH1D( "WGJets",plot,bin[i],Min[i],Max[i]); ZGJetsToLLG_h = new TH1D( "ZGJetsToLLG",plot,bin[i],Min[i],Max[i]);//6
         WWW_h = new TH1D( "WWW",plot,bin[i],Min[i],Max[i]);  WWZ_h = new TH1D( "WWZ",plot,bin[i],Min[i],Max[i]);  WWG_h = new TH1D( "WWG",plot,bin[i],Min[i],Max[i]);  ZZZ_h = new TH1D( "ZZZ",plot,bin[i],Min[i],Max[i]);  WZZ_h = new TH1D( "WZZ",plot,bin[i],Min[i],Max[i]);  WZG_h = new TH1D( "WZG",plot,bin[i],Min[i],Max[i]);  WGG_h = new TH1D( "WGG",plot,bin[i],Min[i],Max[i]);  ZGGJets_h = new TH1D( "ZGGJets",plot,bin[i],Min[i],Max[i]);//8
         WJetsToLNu_h = new TH1D( "WJetsToLNu",plot,bin[i],Min[i],Max[i]);  DYJetsToTauTau_h = new TH1D( "DYJetsToTauTau",plot,bin[i],Min[i],Max[i]);//2
         tZq_ll_h = new TH1D( "tZq_ll",plot,bin[i],Min[i],Max[i]);  tZq_nunu_h =  new TH1D( "tZq_nunu", plot,bin[i],Min[i],Max[i]); ST_tW_antitop_h = new TH1D( "ST_tW_antitop",plot,bin[i],Min[i],Max[i]);  ST_tW_top_h = new TH1D( "ST_tW_top",plot,bin[i],Min[i],Max[i]);  TGJets_h = new TH1D( "TGJets",plot,bin[i],Min[i],Max[i]); THW_h = new TH1D( "THW",plot,bin[i],Min[i],Max[i]);  THQ_h = new TH1D( "THQ",plot,bin[i],Min[i],Max[i]);//6
         VHToNonbb_h = new TH1D( "VHToNonbb",plot,bin[i],Min[i],Max[i]);  ZHToTauTau_h = new TH1D( "ZHToTauTau",plot,bin[i],Min[i],Max[i]);  ZH_HToBB_ZToLL_h = new TH1D( "ZH_HToBB_ZToLL",plot,bin[i],Min[i],Max[i]);  GluGluHToZZTo4L_h = new TH1D( "GluGluHToZZTo4L",plot,bin[i],Min[i],Max[i]);  GluGluHToBB_h = new TH1D( "GluGluHToBB",plot,bin[i],Min[i],Max[i]);  GluGluHToGG_h = new TH1D( "GluGluHToGG",plot,bin[i],Min[i],Max[i]);  GluGluHToMuMu_h = new TH1D( "GluGluHToMuMu",plot,bin[i],Min[i],Max[i]);  GluGluHToTauTau_h = new TH1D( "GluGluHToTauTau",plot,bin[i],Min[i],Max[i]);  GluGluHToWWTo2L2Nu_h = new TH1D( "GluGluHToWWTo2L2Nu",plot,bin[i],Min[i],Max[i]);  GluGluHToWWToLNuQQ_h = new TH1D( "GluGluHToWWToLNuQQ",plot,bin[i],Min[i],Max[i]);  VBFHToWWTo2L2Nu_h = new TH1D( "VBFHToWWTo2L2Nu",plot,bin[i],Min[i],Max[i]);  VBFHToTauTau_h = new TH1D( "VBFHToTauTau",plot,bin[i],Min[i],Max[i]);  VBFHToMuMu_h = new TH1D( "VBFHToMuMu",plot,bin[i],Min[i],Max[i]);  VBFHToGG_h = new TH1D( "VBFHToGG",plot,bin[i],Min[i],Max[i]); 
         QCD_HT200to300_h = new TH1D( "QCD_HT200to300_h",plot,bin[i],Min[i],Max[i]); QCD_HT300to500_h = new TH1D( "QCD_HT300to500_h",plot,bin[i],Min[i],Max[i]); QCD_HT500to700_h = new TH1D( "QCD_HT500to700_h",plot,bin[i],Min[i],Max[i]); QCD_HT700to1000_h = new TH1D( "QCD_HT700to1000_h",plot,bin[i],Min[i],Max[i]); QCD_HT1000to1500_h = new TH1D( "QCD_HT1000to1500_h",plot,bin[i],Min[i],Max[i]); QCD_HT1500to2000_h = new TH1D( "QCD_HT1500to2000_h",plot,bin[i],Min[i],Max[i]); QCD_HT2000toInf_h = new TH1D( "QCD_HT2000toInf_h",plot,bin[i],Min[i],Max[i]);
        allHistos.clear();
        allHistos = {
            TTTT_h, //0
            TTTo2L2Nu_h, TTToHadronic_h, TTToSemiLeptonic_h, //3
            TTGJets_h, ttZJets_h,ttWJets_h, ttH_h, //7
            WZ_h, WW_h, ZZ_h, WGJets_h, ZGJetsToLLG_h, //12
            WWW_h, WWZ_h, WWG_h, ZZZ_h, WZZ_h, WZG_h, WGG_h, ZGGJets_h,//20
            WJetsToLNu_h, DYJetsToTauTau_h,//22
            tZq_ll_h, tZq_nunu_h, ST_tW_antitop_h, ST_tW_top_h,//26
            TGJets_h, THW_h, THQ_h, //29
            QCD_HT200to300_h, QCD_HT300to500_h, QCD_HT500to700_h, QCD_HT700to1000_h, QCD_HT1000to1500_h, QCD_HT1500to2000_h, QCD_HT2000toInf_h,
            // VHToNonbb_h, [>ZHToTauTau_h,*/ ZH_HToBB_ZToLL_h,/* GluGluHToZZTo4L_h,*/ /*GluGluHToBB.*/ GluGluHToGG_h, GluGluHToMuMu_h, GluGluHToTauTau_h, GluGluHToWWTo2L2Nu_h, GluGluHToWWToLNuQQ_h,/* VBFHToWWTo2L2Nu_h, VBFHToTauTau_h,<] VBFHToMuMu_h, VBFHToGG_h,
        };
        // TH1::SetDefaultSumw2();// TH1::Sumw2 to force the storage and computation of the sum of the square of weights per bin.umw2 has been called, the error per bin is computed as the sqrt(sum of squares of weights), otherwise the error is set equal to the sqrt(bin content)
        background_SR = new TH1D("BG","BG",bin[i],Min[i],Max[i]);

        // cout<<"signal and bg files ="<< allHistos.size()<<endl;
        // cout<<"number of trees = "<<allTree.size()<<endl;
        TString hname ;
        Double_t scale;
        Double_t sumGenWeights = -99;
        // for(UInt_t j = 0; j < allHistos.size(); j++){
        for(UInt_t j = 0; j < 1; j++){
        // for(UInt_t j = 0; j < 4; j++){
            hname = allHistos[j]->GetName();
            
            
            // allProcesses[j].getEventTree()->Project( hname, plot, weight);
            // allProcesses[j].getEventTree()->Project( hname, plot, weight*MetFilters);
            // allProcesses[j].getEventTree()->Project( hname, plot, weight*(MetFilters+trigger));
            // allProcesses[j].getEventTree()->Project( hname, plot, weight*(channelCut_step1[cha]+MetFilters+trigger));
            // allProcesses[j].getEventTree()->Project( hname, plot, weight*(channelCut_step2[cha]+MetFilters+trigger));
            // allProcesses[j].getEventTree()->Project( hname, plot, weight*(channelCut_step3[cha]+MetFilters+trigger));
            // allProcesses[j].getEventTree()->Project( hname, plot, weight*(channelCut[cha]+MetFilters+trigger));
            allProcesses[j].getEventTree()->Project( hname, plot, weight*(channelCut[cha]));
            // allHistos[j]->Print();
            if ( i==0 ){
                cout<<allHistos[j]->GetName()<<":"<<endl;
                cout<<"raw entries =  "<<allHistos[j]->GetEntries()<<endl;
                cout<<"weighted    =  "<<allHistos[j]->Integral()<<endl;
            }
            sumGenWeights = allProcesses[j].getGenWeightSum();
            scale = LUMI* allProcesses[j].getSigma()/sumGenWeights;
            allHistos[j]->Scale(scale);
            if ( i ==0){
                cout<<"event yield = "<<allHistos[j]->Integral()<<endl;
                cout<<"\n";
            }
            if(j > 0) background_SR->Add((allHistos[j]),1);
//            background_SR->Print();
        }
        if ( i ==0){
            cout<<"Total BKG    = "<<background_SR->Integral()<<endl;
            cout<<"\n";
        }

        // if(i==0){
            // cout<<endl;
            // cout<<"Plotting "<<variablelist[i]<<postfix<<endl;
            // cout<<" TTTT            = "<<(allHistos[0])->Integral()<<endl;
            // cout<<" TTTT            = "<<TTTT_h->Integral()<<endl;
            // cout<<" TTTo2L2Nu       = "<<TTTo2L2Nu_h->Integral()<<endl;
            // cout<<" TTToHadronic    = "<<TTToHadronic_h->Integral()<<endl;
            // cout<<" TTToSemiLeptonic= "<<TTToSemiLeptonic_h->Integral()<<endl;
            // cout<<" TTX             = "<<ttZJets_h->Integral()
                                    // + ttWJets_h->Integral()
                                    // + ttH_h->Integral()<<endl;
            // cout<<" VV              = "<<WZ_h->Integral()
                                    // + WW_h->Integral()
                                    // + ZZ_h->Integral()
                                    // + WGJets_h->Integral()
                                    // + ZGJetsToLLG_h->Integral()<<endl;
            // cout<<" VVV             = "<<WWW_h->Integral()
                                    // + WWZ_h->Integral()
                                    // + ZZZ_h->Integral()
                                    // + WZZ_h->Integral()
                                    // + WZG_h->Integral()
                                    // + WGG_h->Integral()
                                    // + ZGGJets_h->Integral()<<endl;
            // cout<<"WJets  = "<<allHistos[20]->Integral()<<endl;
            // cout<<" DY              = "<<DYJetsToTauTau_h->Integral()<<endl;
            // cout<<" ST              = "<<tZq_ll_h->Integral()
                                    // + ST_tW_antitop_h->Integral() + ST_tW_top_h->Integral()<<endl;
            // cout<<" TX              = "<<TGJets_h->Integral()
                                    // + THW_h->Integral()
                                    // + THQ_h->Integral()<<endl;
            // cout<<" QCD             = "<< QCD_HT200to300_h->Integral()+ QCD_HT300to500_h->Integral()+ QCD_HT500to700_h->Integral()+ QCD_HT700to1000_h->Integral()+ QCD_HT1000to1500_h->Integral()+ QCD_HT1500to2000_h->Integral()+ QCD_HT2000toInf_h->Integral()<<endl;
            // cout<<"H      = "<<allHistos[28]->Integral()+allHistos[29]->Integral()+allHistos[30]->Integral()+allHistos[31]->Integral()+allHistos[32]->Integral()+allHistos[33]->Integral()+allHistos[34]->Integral()+allHistos[35]->Integral()+allHistos[36]->Integral()+allHistos[37]->Integral()+allHistos[38]->Integral()+allHistos[39]->Integral()+allHistos[40]->Integral()<<endl;
            // cout<<" Total BKG       = "<<background_SR->Integral()<<endl;
            // cout<<"significance = "<<allHistos[0]->Integral()/(sqrt((allHistos[0])->Integral()+background_SR->Integral()));
            // cout<<endl;
            
            // cout<<"Statistics"<<endl;
            // cout<<"TTTT   = "<<TTTT_entries<<endl;
            // cout<<"TT     = "<<(allHistos[1]->Integral()/ allScales_v2[1])<<endl;
            // cout<<"TTX    = "<<(allHistos[2]->Integral()/ allScales_v2[2]) + (allHistos[3]->Integral()/allScales_v2[3]) + (allHistos[4]->Integral()/allScales_v2[4]) + ( allHistos[5]->Integral()/allScales_v2[5]) <<endl;
            // cout<<"VV     = "<<(allHistos[6]->Integral()/allScales_v2[6]) +(allHistos[7]->Integral()/allScales_v2[7]) +(allHistos[8]->Integral()/allScales_v2[8]) + (allHistos[9]->Integral()/allScales_v2[9]) + (allHistos[10]->Integral()/allScales_v2[10]) + (allHistos[11]->Integral()/allScales_v2[11]) <<endl;
            // cout<<"VVV    = "<<(allHistos[12]->Integral()/allScales_v2[12]) + (allHistos[13]->Integral()/allScales_v2[13]) + (allHistos[14]->Integral()/allScales_v2[14]) + (allHistos[15]->Integral()/allScales_v2[15]) + (allHistos[16]->Integral()/allScales_v2[16]) + (allHistos[17]->Integral()/allScales_v2[17]) + (allHistos[18]->Integral()/allScales_v2[18]) + (allHistos[19]->Integral()/allScales_v2[19]) <<endl;
            // cout<<"WJets  = "<<(allHistos[20]->Integral()*allScales_v2[20])<<endl;
            // cout<<"DY     = "<<(allHistos[21]->Integral()*allScales_v2[21])<<endl;
            // cout<<"ST     = "<<(allHistos[22]->Integral()/allScales_v2[22])+(allHistos[23]->Integral()/allScales_v2[23]) + (allHistos[24]->Integral()/allScales_v2[24]) + (allHistos[25]->Integral()/allScales_v2[25]) + (allHistos[26]->Integral()/allScales_v2[26]) + (allHistos[27]->Integral()/allScales_v2[27]) <<endl;
            // cout<<"H      = "<<(allHistos[28]->Integral()/allScales_v2[28])+(allHistos[29]->Integral()/allScales_v2[29]) + (allHistos[30]->Integral()/allScales_v2[30]) + (allHistos[31]->Integral()/allScales_v2[31]) + (allHistos[32]->Integral()/allScales_v2[32]) + (allHistos[33]->Integral()/allScales_v2[33]) + (allHistos[34]->Integral()/allScales_v2[34]) + (allHistos[35]->Integral()/allScales_v2[35]) + (allHistos[36]->Integral()/allScales_v2[36]) + (allHistos[37]->Integral()/allScales_v2[37]) + (allHistos[38]->Integral()/allScales_v2[38]) + (allHistos[39]->Integral()/allScales_v2[39]) + (allHistos[40]->Integral()/allScales_v2[40]) <<endl;
        // }


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
        Double_t channelTextFont   = 42;
        Double_t channelTextSize   = 0.06;
        TString cmsText     = "CMS";
        Double_t cmsTextFont   = 61;  // default is helvetic-bold
        bool writeExtraText = true;
        TString extraText   = "MC";
        //TString extraText   = "";
        Double_t extraTextFont = 52;  // default is helvetica-italics
        // text sizes and text offsets with respect to the top frame in unit of the top margin size
        Double_t lumiTextSize     = 0.6;
        Double_t lumiTextOffset   = 0.2;
        Double_t cmsTextSize      = 0.75;
        Double_t cmsTextOffset    = 0.1;  // only used in outOfFrame version
        Double_t relPosX    = 0.045;
        Double_t relPosY    = 0.035;
        Double_t relExtraDY = 1.2;
        // ratio of "CMS" and extra text size
        Double_t extraOverCmsTextSize  = 0.76;
        TString lumi_13TeV;
        lumi_13TeV = "35.9fb^{-1}";
        TString lumiText;
        lumiText += lumi_13TeV;
        lumiText += " (2016, 13 TeV)";
        Double_t t = pad->GetTopMargin();
        Double_t b = pad->GetBottomMargin();
        Double_t r = pad->GetRightMargin();
        Double_t l = pad->GetLeftMargin();
        TLatex latex;
        latex.SetNDC();
        latex.SetTextAngle(0);
        latex.SetTextColor(kBlack);    
        Double_t extraTextSize = extraOverCmsTextSize*cmsTextSize;
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
        c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/plotsAndResults/test/"+NAME+postfix);
        
        cout<<"Finished "<<NAME+postfix<<endl;
        c1->Draw();

        //?for different range we have different sp, how to deal with this?
        if ( ifSP ){
            Double_t sp = separationPower(allHistos[0], background_SR);
            cout<<NAME<<" separation power"<<sp<<endl;
            std::cout << '\n';
            if(i==(variablelist.size()-1)) cout<<channelName[cha]<<endl;
            mymap.insert(std::make_pair(sp, NAME));
        }


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
    if ( ifSP ){
        for (auto rit = mymap.crbegin(); rit != mymap.crend(); ++rit){
            std::cout <<  rit->second << " = "<< rit->first << endl;
            // std::cout << '\n';
        }
    }

//what is SYST and why we do it this way?   
	//how do we exactly include SYST in our histograms?

}
    t.Stop();
    t.Print();
}


Double_t separationPower(TH1D* h1, TH1D* h2){
    Double_t norm = 1;
    // h1->Print();
    // h2->Print();
    h1->Scale(norm/h1->Integral());
    h2->Scale(norm/h2->Integral());
  Int_t nbins=h1->GetXaxis()->GetNbins();
//  cout<<nbins<<endl;
  Double_t s=0;
//  Double_t width=h1->GetBinWidth(1);
  for(Int_t i=1;i<nbins+1;i++){
//  for(Int_t i=0;i<nbins;i++){
      if(h1->GetBinContent(i)+h2->GetBinContent(i)!=0)
//      s+=0.5*TMath::Power((h1->GetBinContent(i)-h2->GetBinContent(i))/width,2)/(h1->GetBinContent(i)+h2->GetBinContent(i))*width*width;
      s+=0.5*TMath::Power((h1->GetBinContent(i)-h2->GetBinContent(i)),2)/(h1->GetBinContent(i)+h2->GetBinContent(i));
      //?it seems you do not use width at all.
  }
  return s;
}
