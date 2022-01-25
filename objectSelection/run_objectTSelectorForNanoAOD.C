#include <iostream>
#include "TString.h"
#include "TChain.h"
#include "TROOT.h"

void run_objectTSelectorForNanoAOD(
    Bool_t istest = true,
    // Bool_t istest = false,
    TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/tttt/",
    TString outputDir = "/publicfs/cms/user/fabioiemmi/TauOfTTTT/test_tobjectSelector/",
    TString singleFileName = "outTree_0.root",
    // Bool_t ishuiling = false
    Bool_t ishuiling = true
    )
{
    gROOT->ProcessLine(".L Loader.C+");

    Bool_t isData = false;
    if ( inputDir.Contains( "Block")) isData = true;

    TString inputFile; 
    inputFile = inputDir + singleFileName;
    cout << "inputFile: " << inputFile << "\n";
    TChain chain("Events");
    chain.Add( inputFile );
    
    // TString outputFileName(inputDir(0, inputDir.First("/") ));
    // outputFileName = outputFileName + singleFileName;

    TString selection;
    TString option;
    Int_t eventNum = 100;
    if (ishuiling) selection = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/objectTSelectorForNanoAOD.C";
    else selection = "/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/objectSelection/objectTSelectorForNanoAOD.C";
    if ( istest ){
        if (ishuiling) outputDir = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/output/";
        else outputDir = "/publicfs/cms/user/fabioiemmi/TauOfTTTT/test_tobjectSelector/";
        eventNum = 100;
    }
    TString outputFile;
    outputFile = outputDir + singleFileName;
    cout << "outputFile: "<< outputFile << endl;
    option = outputFile;
    
    if ( istest )    chain.Process( selection + "+", option, eventNum );
    else  chain.Process(selection + "+", option);
}
