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
#include "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/EYandSP_usingClass_v3.h"

using namespace TMVA;
using std::cout;

void writeHistToFile( const TH1F* hist, TString outFile ){
   TFile *target  = new TFile( outFile,"UPDATE" );
   hist->Write();
   delete hist;
   target->Close();
   std::cout <<"Hist saved in: "<<target->GetName()<< std::endl;
}
void evaluateMVA( std::map<std::string,int> Use, TString processName, TTree* theTree, Double_t processScale, TH1F* &data_BDT, TH1F* data_BDTG, Bool_t writeData, Int_t channel, TString outputDir, TString variableListCsv, TString weightDir, const Int_t binNum  ){
   // Create the Reader object
   
    cout<<"\n";
    cout<<"\n";
    std::cout<<"process Name: "<<processName<<"\n";

   TH1F *histBdt(0); 
   TH1F *histBdtG(0);
   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
   // Float_t jets_bScore, jets_7pt, toptagger_HT, bjetsM_invariantMass, jets_6pt, jets_transMass, jets_rationHT_4toRest, nonbjetsM_4pt, bjetsM_minDeltaR, toptagger_3pt, toptagger_MHT;
   //???type has to be Float_t

    ifstream fin( variableListCsv);
    string line ;
    TString ivariable;
    vector<TString> variablesName {};

    vector<Float_t> variablesForReader;
    vector<Double_t> variablesOrigin;
    // map<TString, Float_t>;
    while ( getline( fin, line ) ){
        ivariable = line;
        if( line.size()>0)  {
            variablesName.push_back( ivariable);
            variablesForReader.push_back( 0.0 );
            variablesOrigin.push_back( 0.0);
        }
    }
    fin.close();
    UInt_t variableNum = variablesName.size();
    for ( UInt_t v = 0; v<variableNum; v++ ){
        reader->AddVariable( variablesName[v], &variablesForReader[v] );

    }

   // Spectator variables declared in the training have to be added to the reader, too
   // Float_t spec1,spec2;
   // reader->AddSpectator( "spec1 := var1*2",   &spec1 );
   // reader->AddSpectator( "spec2 := var1*3",   &spec2 );


   // Book the MVA methods
   TString prefix = "TMVAClassification";
   // Book method(s)
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = weightDir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
         reader->BookMVA( methodName, weightfile );
      }
   }

   // Book output histograms
   // UInt_t binNum = 100;
   // UInt_t binNum = 11;

   if (Use["BDT"])           histBdt     = new TH1F( processName+"_MVA_BDT",           "MVA_BDT",           binNum, -0.8, 0.8 );
   if (Use["BDTG"])          histBdtG    = new TH1F( processName+"_MVA_BDTG",          "MVA_BDTG",          binNum, -1.0, 1.0 );


   // std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;

   // Event loop

   // Prepare the event tree
   // - Here the variable names have to corresponds to your tree
   // - You can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
    for ( UInt_t i=0; i<variableNum; i++ ){
        theTree->SetBranchAddress( variablesName[i], &variablesOrigin[i] );
    }

   //for selection
   // Float_t tausT_number, leptonsMVAT_number, jets_number, bjetsM_num, jets_HT;
   Int_t tausT_number, leptonsMVAT_number, jets_number, bjetsM_num;
   Double_t jets_HT;
   theTree->SetBranchAddress( "tausT_number",     &tausT_number );
   theTree->SetBranchAddress( "leptonsMVAT_number",     &leptonsMVAT_number );
   theTree->SetBranchAddress( "jets_number",     &jets_number );
   theTree->SetBranchAddress( "bjetsM_num",     &bjetsM_num );
   theTree->SetBranchAddress( "jets_HT",     &jets_HT );
   Double_t EVENT_genWeight, EVENT_prefireWeight, PUWeight, btagEfficiency_weight, HLTefficiency_weight;
   theTree->SetBranchAddress( "EVENT_genWeight",     &EVENT_genWeight );
   theTree->SetBranchAddress( "EVENT_prefireWeight",     &EVENT_prefireWeight );
   theTree->SetBranchAddress( "PUWeight",     &PUWeight );
   theTree->SetBranchAddress( "btagEfficiency_weight",     &btagEfficiency_weight );
   theTree->SetBranchAddress( "HLTefficiency_weight",     &HLTefficiency_weight );

   // Efficiency calculator for cut method
   Int_t    nSelCutsGA = 0;
   Double_t effS       = 0.7;

   std::vector<Float_t> vecVar(4); // vector for EvaluateMVA tests

   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {
   // for (Long64_t ievt=0; ievt<1000;ievt++) {


      theTree->GetEntry(ievt);

      
      // jets_bScore = jets_bScore_origin;
      // toptagger_MHT = toptagger_MHT_origin;
      for ( UInt_t j = 0; j<variableNum; j++ ){
          // variablesForReader[j] = variablesOrigin[j];
          variablesForReader.at(j) = variablesOrigin.at(j);
          // cout<<variablesForReader[j]<<" "<<variablesOrigin[j]<<"\n";
          // cout<<variablesName[j]<<": "<<variablesForReader[j]<<" "<<variablesOrigin[j]<<"\n";
          // cout<<variablesOrigin[j]<<"\n";
      }
      // cout<<"\n";
      //channel selection
      if (channel==1){
         if ( !(tausT_number==1 && leptonsMVAT_number==1&& jets_number>=6 && bjetsM_num>=2 && jets_HT>400) ) continue; //1tau1l
      }
      if ( channel==4){//1tau2l
         if ( !(tausT_number==1 && leptonsMVAT_number==2&& jets_number>=4 && bjetsM_num>=2 && jets_HT>400) ) continue; //1tau1l
      } 
      if ( channel==5){//2tauXl
         if ( !(tausT_number==2&&bjetsM_num>=2&&jets_HT>400 && (  (leptonsMVAT_number==0&&jets_number>=6)||(leptonsMVAT_number==1&& jets_number>=4)||(leptonsMVAT_number==2&&jets_number>=2)      ) ))  continue;
      }


      // Return the MVA outputs and fill into histograms
        Double_t eventWeight = EVENT_genWeight*EVENT_prefireWeight*PUWeight*btagEfficiency_weight*HLTefficiency_weight;

      // if (Use["BDT"          ])   histBdt    ->Fill( reader->EvaluateMVA( "BDT method") *eventWeight );
      if (Use["BDT"          ])   histBdt    ->Fill( reader->EvaluateMVA( "BDT method"), eventWeight );
      if (Use["BDTG"         ])   histBdtG   ->Fill( reader->EvaluateMVA( "BDTG method"), eventWeight );

   }

   delete reader;
   // Get elapsed time
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();
   std::cout<<"histBdt before scale: "<<histBdt->Integral()<<"\n";
   histBdt->Scale(processScale);
   histBdtG->Scale(processScale);
   std::cout<<"histBdt after scale: "<<histBdt->Integral()<<"\n";

   //
   *data_BDT = *data_BDT + *histBdt;
   *data_BDTG = *data_BDTG + *histBdtG;

   TString s_channel;
   if ( channel==1 )       s_channel = "1tau1l";
   if ( channel==4 )  s_channel = "1tau2l";
   if ( channel==5 )  s_channel = "2tauXl";
   TString s_variableNum = std::to_string(variableNum);
   // TString outFileName = "TMVApp_" + s_channel + "_forCombine.root";
   TString outFileName = outputDir + "TMVApp_" + s_channel + "_"+ s_variableNum + "var_forCombine.root";
   // TString outFileName = "TMVApp_" + s_channel + "_forCombineTest1000.root";
   writeHistToFile( histBdt, outFileName );
   writeHistToFile( histBdtG, outFileName );
   if ( writeData )  {
       writeHistToFile( data_BDT, outFileName );
       writeHistToFile( data_BDTG, outFileName );
   }

}


void TMVAClassificationApplication_multipleSamples( TString myMethodList = "",
        // TString outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v2/AppResults/",
        TString outputDir = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/outputFile/",
        // TString variableListCsv = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v2/variableList/varibleList_11.csv",
       // TString weightDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v2/dataset/1tau1l_varibleList_11_weight/",
        TString variableListCsv = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau1l_v1/variableList/varibleList_11.csv",
        TString weightDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau1l_v1/dataset/1tau1l_varibleList_11_weight/",
        // const Int_t channel = 3//2tau1l
        const Int_t channel = 1,//1tau1l
        // const Int_t channel = 4//1tau2l
        // const Int_t channel = 5,//1tau2l
        const  Int_t binNum = 100

        )
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

   // UInt_t binNum = 100;
    // UInt_t binNum = 11;

   TH1F* data_BDT = new TH1F( "data_obs_MVA_BDT", "data_obs_MVA_BDT", binNum, -0.8, 0.8 );//for combine
   TH1F* data_BDTG = new TH1F( "data_obs_MVA_BDTG", "data_obs_MVA_BDTG", binNum, -1.0, 1.0 );
    for ( UInt_t p=0; p<allProcesses.size(); p++){
    // for ( UInt_t p=0; p<1; p++){
       evaluateMVA(Use, allProcesses[p].getProcessName(), allProcesses[p].getEventTree(), LUMI*allProcesses[p].getScale(), data_BDT, data_BDTG, false,  channel, outputDir, variableListCsv, weightDir, binNum );       
       if ( p==allProcesses.size()-1 ){
           evaluateMVA(Use, allProcesses[p].getProcessName(), allProcesses[p].getEventTree(), LUMI*allProcesses[p].getScale(), data_BDT, data_BDTG, true,  channel, outputDir, variableListCsv, weightDir, binNum );
       }
    }


   std::cout << "==> TMVAClassificationApplication is done!" << std::endl << std::endl;
}

// int main( int argc, char** argv )
// {
   // TString methodList;
   // for (int i=1; i<argc; i++) {
      // TString regMethod(argv[i]);
      // if(regMethod=="-b" || regMethod=="--batch") continue;
      // if (!methodList.IsNull()) methodList += TString(",");
      // methodList += regMethod;
   // }
   // TMVAClassificationApplication_multipleSamples(methodList);
   // return 0;
// }
