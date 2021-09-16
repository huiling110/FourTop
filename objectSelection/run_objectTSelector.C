#include <iostream>
#include "TString.h"
#include "TChain.h"
#include "TROOT.h"

void run_objectTSelector(
                        Bool_t istest = true,
                        // Bool_t istest = false,
                        TString inputDir = "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn/Legacy16V2_TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8addGenWeight/210201_023641/0000/",
						//TString inputDir = "ZZ_TuneCUETP8M1_13TeV-pythia8/Legacy16V2_ZZ_TuneCUETP8M1_13TeV-pythia8addGenWeight/210201_032809/0000/",
						//TString inputDir = "SingleMuon/Legacy16V2_SMuBlockBv3/210304_135358/0000/",
                        // TString inputDir = "TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/Legacy16V2_TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8addGenWeight/210201_024239/0000/",
                        //TString inputDir = "JetHT/Legacy16V2_JetHTBlockCHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_060426/0000/",
                        //TString inputDir = "SingleMuon/Legacy16V2_SMuBlockBv3/210304_135358/0000/",
                        //TString outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/test_objectSelction/",
						TString outputDir = "/publicfs/cms/user/fabioiemmi/TauOfTTTT/test_tobjectSelector/",
                        TString singleFileName = "v3_1-1.root",
						//TString singleFileName = "v3_1.root",
						//TString singleFileName = "TauOfTTTT_TopTagger_oldEID_100.root", //this is for data
                        // Bool_t ishuiling = false)
                        Bool_t ishuiling = true)
                        // TString singleFileName = "TauOfTTTT_TopTagger_oldEID_100.root")
{
    gROOT->ProcessLine(".L Loader.C+");

    Bool_t data = false;
    if ( inputDir.Contains( "Block")) data = true;

    TString inputFile; TString inputBase = "/publicfs/cms/data/TopQuark/FourTop_hua/v3/2016/";
    if ( data ){//only for JETHT
         inputBase = "/publicfs/cms/data/TopQuark/FourTop_hua/v2/mc/2016/";
    }
    inputFile = inputBase + inputDir;
    TChain chain("TNT/BOOM");
    chain.Add(inputFile+singleFileName);
    
    TString outputFileName(inputDir(0, inputDir.First("/") ));
	cout << outputFileName << endl;
    if ( data ){
       // TString dataEar(inputDir( inputDir.First("/"), inputDir.Sizeof())) ;
       // dataEar.Remove(0,1 );
       // TString dataEra( dataEar(0, dataEar.First("/")));
       // cout<<dataEar;
       TString dataEra;
       if ( inputDir.Contains( "BlockB")) dataEra = "B";
       if ( inputDir.Contains( "BlockC")) dataEra = "C";
       if ( inputDir.Contains( "BlockD")) dataEra = "D";
       if ( inputDir.Contains( "BlockE")) dataEra = "E";
       if ( inputDir.Contains( "BlockF")) dataEra = "F";
       if ( inputDir.Contains( "BlockG")) dataEra = "G";
       if ( inputDir.Contains( "BlockH")) dataEra = "H";
	   cout << outputFileName << endl;
	   outputFileName = outputFileName + dataEra;
	   cout << outputFileName << endl;
	   if (inputDir.Contains( "0000")) outputFileName = outputFileName + "_0";
       if (inputDir.Contains( "0001")) outputFileName = outputFileName + "_1";
    }
    outputFileName = outputFileName + "/"+ singleFileName;

    TString selection;
    if (ishuiling) selection = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/objectTSelector.C";
    else selection = "/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/objectSelection/objectTSelector.C";
    if ( istest ){
        if (ishuiling) outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/test_objectSelction/";
        else outputDir = "/publicfs/cms/user/fabioiemmi/TauOfTTTT/test_tobjectSelector/";
        // chain.Process( selection + "+", outputDir + outputFileName, 10000);
        chain.Process( selection + "+", outputDir + outputFileName, 1000);
    }
    else chain.Process( selection + "+", outputDir + outputFileName);


}
