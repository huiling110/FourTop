/// \file
/// \ingroup tutorial_tmva
/// \notebook -nodraw
/// This macro provides a simple example on how to use the trained classifiers
/// within an analysis module
/// - Project   : TMVA - a Root-integrated toolkit for multivariate data analysis
/// - Package   : TMVA
/// - Exectuable: TMVAClassificationApplication
///
/// \macro_output
/// \macro_code
/// \author Andreas Hoecker

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/EYandSP_usingClass_v2.h"

using namespace TMVA;

// void evaluateMVA( std::map<std::string,int> Use, TString processName, TTree* theTree , TH1F* &histBdt, TH1F* &histBdtG ){
void evaluateMVA( std::map<std::string,int> Use, TString processName, TTree* theTree, Double_t processScale, Int_t channel ){
   // Create the Reader object
    
    std::cout<<"process Name: "<<processName<<"\n";

   TH1F *histBdt(0); 
   TH1F *histBdtG(0);
   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
   // Float_t var1, var2;
   // Float_t var3, var4;
   // reader->AddVariable( "myvar1 := var1+var2", &var1 );
   // reader->AddVariable( "myvar2 := var1-var2", &var2 );
   // reader->AddVariable( "var3",                &var3 );
   // reader->AddVariable( "var4",                &var4 );
   Float_t jets_bScore, jets_7pt, toptagger_HT, bjetsM_invariantMass, jets_6pt, jets_transMass, jets_rationHT_4toRest, nonbjetsM_4pt, bjetsM_minDeltaR, toptagger_3pt, toptagger_MHT;
   // Double_t jets_bScore, jets_7pt, toptagger_HT, bjetsM_invariantMass, jets_6pt, jets_transMass, jets_rationHT_4toRest, nonbjetsM_4pt, bjetsM_minDeltaR, toptagger_3pt, toptagger_MHT;
   reader->AddVariable( "jets_bScore",         &jets_bScore );
   reader->AddVariable( "jets_7pt",         &jets_7pt );
   reader->AddVariable( "toptagger_HT",         &toptagger_HT );
   reader->AddVariable( "bjetsM_invariantMass",         &bjetsM_invariantMass );
   reader->AddVariable( "jets_6pt",         &jets_6pt );
   reader->AddVariable( "jets_transMass",         &jets_transMass );
   reader->AddVariable( "jets_rationHT_4toRest",         &jets_rationHT_4toRest );
   reader->AddVariable( "nonbjetsM_4pt",         &nonbjetsM_4pt );
   reader->AddVariable( "bjetsM_minDeltaR",         &bjetsM_minDeltaR );
   reader->AddVariable( "toptagger_3pt",         &toptagger_3pt );
   reader->AddVariable( "toptagger_MHT",         &toptagger_MHT );
    // ifstream fin( variableListCsv);
    // string line ;
    // TString ivariable;
    // vector<TString> variables {};
    // Int_t num = 1;
    // while ( getline( fin, line ) ){
            // ivariable = line;
            // if( line.size()>0)  {
                // variables.push_back( ivariable);
//
            // }
        // reader->AddVariable( line, variables[num-2]);
        // num = num+1;
    // }
    // fin.close();

   // Spectator variables declared in the training have to be added to the reader, too
   // Float_t spec1,spec2;
   // reader->AddSpectator( "spec1 := var1*2",   &spec1 );
   // reader->AddSpectator( "spec2 := var1*3",   &spec2 );

   // Float_t Category_cat1, Category_cat2, Category_cat3;
   // if (Use["Category"]){
      // Add artificial spectators for distinguishing categories
      // reader->AddSpectator( "Category_cat1 := var3<=0",             &Category_cat1 );
      // reader->AddSpectator( "Category_cat2 := (var3>0)&&(var4<0)",  &Category_cat2 );
      // reader->AddSpectator( "Category_cat3 := (var3>0)&&(var4>=0)", &Category_cat3 );
   // }

   // Book the MVA methods

   // TString dir    = "dataset/weights/";
   TString prefix = "TMVAClassification";
   TString dir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v2/dataset/1tau1l_varibleList_11_weight/";

   // Book method(s)
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
         reader->BookMVA( methodName, weightfile );
      }
   }

   // Book output histograms
   UInt_t nbin = 100;

   if (Use["BDT"])           histBdt     = new TH1F( processName+"_MVA_BDT",           "MVA_BDT",           nbin, -0.8, 0.8 );
   if (Use["BDTG"])          histBdtG    = new TH1F( processName+"_MVA_BDTG",          "MVA_BDTG",          nbin, -1.0, 1.0 );
   // if (Use["BDTB"])          histBdtB    = new TH1F( "MVA_BDTB",          "MVA_BDTB",          nbin, -1.0, 1.0 );
   // if (Use["BDTD"])          histBdtD    = new TH1F( "MVA_BDTD",          "MVA_BDTD",          nbin, -0.8, 0.8 );
   // if (Use["BDTF"])          histBdtF    = new TH1F( "MVA_BDTF",          "MVA_BDTF",          nbin, -1.0, 1.0 );

   // PDEFoam also returns per-event error, fill in histogram, and also fill significance
   // if (Use["PDEFoam"]) {
      // histPDEFoam    = new TH1F( "MVA_PDEFoam",       "MVA_PDEFoam",              nbin,  0, 1 );
      // histPDEFoamErr = new TH1F( "MVA_PDEFoamErr",    "MVA_PDEFoam error",        nbin,  0, 1 );
      // histPDEFoamSig = new TH1F( "MVA_PDEFoamSig",    "MVA_PDEFoam significance", nbin,  0, 10 );
   // }
//
   // Book example histogram for probability (the other methods are done similarly)
   // TH1F *probHistFi(0), *rarityHistFi(0);
   // if (Use["Fisher"]) {
      // probHistFi   = new TH1F( "MVA_Fisher_Proba",  "MVA_Fisher_Proba",  nbin, 0, 1 );
      // rarityHistFi = new TH1F( "MVA_Fisher_Rarity", "MVA_Fisher_Rarity", nbin, 0, 1 );
   // }

   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //
   // TFile *input(0);
   // TString fname = "./tmva_class_example.root";
   // if (!gSystem->AccessPathName( fname )) {
      // input = TFile::Open( fname ); // check if file in local directory exists
   // }
   // else {
      // TFile::SetCacheFileDir(".");
      // input = TFile::Open("http://root.cern.ch/files/tmva_class_example.root", "CACHEREAD"); // if not: download from ROOT server
   // }
   // if (!input) {
      // std::cout << "ERROR: could not open data file" << std::endl;
      // exit(1);
   // }
   // std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;

   // Event loop

   // Prepare the event tree
   // - Here the variable names have to corresponds to your tree
   // - You can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
   // std::cout << "--- Select signal sample" << std::endl;
   // TTree* theTree = TTTT.getEventTree();
   // Float_t userVar1, userVar2;
   // theTree->SetBranchAddress( "var1", &userVar1 );
   // theTree->SetBranchAddress( "var2", &userVar2 );
   // theTree->SetBranchAddress( "var3", &var3 );
   // theTree->SetBranchAddress( "var4", &var4 );

   Double_t jets_bScore_origin, jets_7pt_origin, toptagger_HT_origin, bjetsM_invariantMass_origin, jets_6pt_origin, jets_transMass_origin, jets_rationHT_4toRest_origin, nonbjetsM_4pt_origin, bjetsM_minDeltaR_origin, toptagger_3pt_origin, toptagger_MHT_origin;
   theTree->SetBranchAddress( "jets_bScore",         &jets_bScore_origin );
   theTree->SetBranchAddress( "jets_7pt",         &jets_7pt_origin );
   theTree->SetBranchAddress( "toptagger_HT",         &toptagger_HT_origin );
   theTree->SetBranchAddress( "bjetsM_invariantMass",         &bjetsM_invariantMass_origin );
   theTree->SetBranchAddress( "jets_6pt",         &jets_6pt_origin );
   theTree->SetBranchAddress( "jets_transMass",         &jets_transMass_origin );
   theTree->SetBranchAddress( "jets_rationHT_4toRest",         &jets_rationHT_4toRest_origin );
   theTree->SetBranchAddress( "nonbjetsM_4pt",         &nonbjetsM_4pt_origin );
   theTree->SetBranchAddress( "bjetsM_minDeltaR",         &bjetsM_minDeltaR_origin );
   theTree->SetBranchAddress( "toptagger_3pt",         &toptagger_3pt_origin );
   theTree->SetBranchAddress( "toptagger_MHT",         &toptagger_MHT_origin );
   //for selection
   // Float_t tausT_number, leptonsMVAT_number, jets_number, bjetsM_num, jets_HT;
   Int_t tausT_number, leptonsMVAT_number, jets_number, bjetsM_num;
   Double_t jets_HT;
   theTree->SetBranchAddress( "tausT_number",     &tausT_number );
   theTree->SetBranchAddress( "leptonsMVAT_number",     &leptonsMVAT_number );
   theTree->SetBranchAddress( "jets_number",     &jets_number );
   theTree->SetBranchAddress( "bjetsM_num",     &bjetsM_num );
   theTree->SetBranchAddress( "jets_HT",     &jets_HT );
   Double_t EVENT_genWeight, EVENT_prefireWeight, PUWeight;
   theTree->SetBranchAddress( "EVENT_genWeight",     &EVENT_genWeight );
   theTree->SetBranchAddress( "EVENT_prefireWeight",     &EVENT_prefireWeight );
   theTree->SetBranchAddress( "PUWeight",     &PUWeight );

   // Efficiency calculator for cut method
   Int_t    nSelCutsGA = 0;
   Double_t effS       = 0.7;

   std::vector<Float_t> vecVar(4); // vector for EvaluateMVA tests

   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {
   // for (Long64_t ievt=0; ievt<1000;ievt++) {

      // if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

      theTree->GetEntry(ievt);

      // var1 = userVar1 + userVar2;
      // var2 = userVar1 - userVar2;
      
   // Float_t jets_bScore, jets_7pt, toptagger_HT, bjetsM_invariantMass, jets_6pt, jets_transMass, jets_rationHT_4toRest, nonbjetsM_4pt, bjetsM_minDeltaR, toptagger_3pt, toptagger_MHT;
      jets_bScore = jets_bScore_origin;
      jets_7pt = jets_7pt_origin;
      toptagger_HT = toptagger_HT_origin;
      bjetsM_invariantMass = bjetsM_invariantMass_origin;
      jets_6pt = jets_6pt_origin;
      jets_transMass = jets_transMass_origin;
      jets_rationHT_4toRest = jets_rationHT_4toRest_origin;
      nonbjetsM_4pt = nonbjetsM_4pt;
      bjetsM_minDeltaR = bjetsM_minDeltaR_origin;
      toptagger_3pt = toptagger_3pt_origin;
      toptagger_MHT = toptagger_MHT_origin;
      //channel selection
       if ( !(tausT_number==1 && leptonsMVAT_number==1&& jets_number>=6 && bjetsM_num>=2 && jets_HT>400) ) continue; 
       // if ( ievt<100 )       cout<<"jets_bSore = "<<jets_bScore<<"\n";


      // Return the MVA outputs and fill into histograms
        Double_t eventWeight = EVENT_genWeight*EVENT_prefireWeight*PUWeight;
        // std::cout<<"eventWeight = "<<eventWeight<<"\n";

      // if (Use["BDT"          ])   histBdt    ->Fill( reader->EvaluateMVA( "BDT method") *eventWeight );
      if (Use["BDT"          ])   histBdt    ->Fill( reader->EvaluateMVA( "BDT method"), eventWeight );
      if (Use["BDTG"         ])   histBdtG   ->Fill( reader->EvaluateMVA( "BDTG method"), eventWeight );

   }

   delete reader;
   // Get elapsed time
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();
   std::cout<<"histBdt before scale: "<<histBdt->Integral()<<"\n";
   // std::cout<<"processScale = "<<processScale<<"\n";
   histBdt->Scale(processScale);
   histBdtG->Scale(processScale);

   std::cout<<"histBdt after scale: "<<histBdt->Integral()<<"\n";

   // TFile *target  = new TFile( "TMVApp.root","UPDATE" );
   // histBdt->Print();
   TString s_channel;
   if ( channel==1 )       s_channel = "1tau1l";
   // TFile *target  = new TFile( "TMVApp_" + s_channel + ".root","UPDATE" );
   TFile *target  = new TFile( "TMVApp_" + s_channel + "_forCombine.root","UPDATE" );
    
   if (Use["BDT"          ])   histBdt    ->Write();
   if (Use["BDTG"         ])   histBdtG   ->Write();
   delete histBdt;
   delete histBdtG;

   target->Close();

   std::cout <<target->GetName()<< ": containing the MVA output histograms" << std::endl;
}


void TMVAClassificationApplication_multipleSamples( TString myMethodList = "" )
{

   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // Cut optimisation
   //
   // Boosted Decision Trees
   Use["BDT"]             = 1; // uses Adaptive Boost
   Use["BDTG"]            = 1; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting
   //
   // ---------------------------------------------------------------
   // Use["Plugin"]          = 0;
   Use["Category"]        = 0;
   // Use["SVM_Gauss"]       = 0;
   // Use["SVM_Poly"]        = 0;
   // Use["SVM_Lin"]         = 0;

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassificationApplication" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod
                      << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
               std::cout << it->first << " ";
            }
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   Int_t channel = 1;
    for ( UInt_t p=0; p<allProcesses.size(); p++){
    // for ( UInt_t p=0; p<1; p++){
       evaluateMVA(Use, allProcesses[p].getProcessName(), allProcesses[p].getEventTree(), LUMI*allProcesses[p].getScale(),channel );
        
    }



   std::cout << "==> TMVAClassificationApplication is done!" << std::endl << std::endl;
}

int main( int argc, char** argv )
{
   TString methodList;
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(",");
      methodList += regMethod;
   }
   TMVAClassificationApplication_multipleSamples(methodList);
   return 0;
}
