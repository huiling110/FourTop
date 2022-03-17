#include <iostream>
#include "TString.h"
#include "TChain.h"
#include "TROOT.h"


void run_objectTSelectorForNanoAOD(
    Bool_t istest = true,
    // Bool_t istest = false,
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/dy/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016APV/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016APV/data/jetHT_2016D/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016APV/data/jetHT_2016C/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/data/singleMu_2016G/",
    TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/tttt/",
    TString outputDir = "/publicfs/cms/user/fabioiemmi/TauOfTTTT/test_tobjectSelector/",
    TString singleFileName = "outTree_0.root",
   // 1 for MetFilters, 2 for HLTSelection, 4 for preSelection. so 7 if all selection; 0 if no selection 
    // TString eventSelectionBit = "7",  
    TString eventSelectionBit = "5",  
    // TString eventSelectionBit = "0",  
    // Bool_t ishuiling = false
    Bool_t ishuiling = true
    )
{
    // gROOT->ProcessLine(".L Loader.C+");
    gROOT->ProcessLine( ".L objectTSelectorForNanoAOD.so");

    //determine era and isData from inputDir
    TString era = "2016";
    Bool_t isData = true;
    TString dataSet = "mc" ;
    if (inputDir.Contains( "mc" )) {
        era = inputDir( inputDir.Index("nanoAOD")+8, (inputDir.Index("mc")-inputDir.Index("nanoAOD")-9) );
        isData = false;
    }else{
        TString tempo = inputDir;
        tempo.Remove( 0, inputDir.Index("data")+4);
        era = tempo( tempo.Index("nanoAOD")+8, (tempo.Index("data")-tempo.Index("nanoAOD")-9) );
        dataSet = tempo( tempo.Index("data")+5, tempo.Length()-tempo.Index("data")-6 ) ;
        cout<<"dataSet in run: "<<dataSet<<"\n";
    }
    cout<<"era is: "<<era<<"\n";
    
    if ( era.CompareTo( "2016" )==0) {
        era = "2016postVFP";
    }else if( era.CompareTo( "2016APV")==0 ){
        era = "2016preVFP";
    }
    cout<<"era is: "<<era<<"\n";
    cout<<"selectionBit is:"<<eventSelectionBit<<"\n";
    cout<<"isdata: "<<isData<<"\n";


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
    selection = "objectTSelectorForNanoAOD.C";
    if ( istest ){
        outputDir = "output/";
        eventNum = 100;
        // eventNum = 1000;
    }
    TString outputFile;
    outputFile = outputDir + singleFileName;
    cout << "outputFile: "<< outputFile << endl;
    // option = outputFile + ":2016postVP";
    // option = outputFile + ":" + era + ":"+ eventSelectionBit;
    option = outputFile + ":" + era + ":"+ eventSelectionBit + ":" + isData + ":"+ dataSet;
    cout<<"option in run: "<<option<<"\n";

    TStopwatch t;
    t.Start();
    if ( istest )  {
        chain.Process( selection + "+", option, eventNum );
    }else  { 
        chain.Process(selection + "+", option);
    }
    t.Stop();
    t.Print();
}
