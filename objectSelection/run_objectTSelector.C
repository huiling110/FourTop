
void run_objectTSelector(
                        Bool_t istest = true,
                        // Bool_t istest = false,
                        TString inputDir = "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn/Legacy16V2_TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8addGenWeight/210201_023641/0000/",
                        // TString inputDir = "TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/Legacy16V2_TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8addGenWeight/210201_024239/0000/",
                        // TString inputDir = "JetHT/Legacy16V2_JetHTBlockCHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_v2/210107_060426/0000/",
                        TString outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/test_objectSelction/",
                        // TString outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/checkForEY/",
                        TString singleFileName = "v3_1-1.root")
                        // TString singleFileName = "TauOfTTTT_TopTagger_oldEID_100.root")
{
    gROOT->ProcessLine(".L Loader.C+");

    Bool_t data = false;
    if ( inputDir.Contains( "Block")) data = true;

    TString inputFile; TString inputBase = "/publicfs/cms/data/TopQuark/FourTop_hua/v3/2016/";
    if ( data ){
        inputBase = "/publicfs/cms/data/TopQuark/FourTop_hua/v2/mc/2016/";
    }
    inputFile = inputBase + inputDir;
    TChain chain("TNT/BOOM");
    chain.Add(inputFile+singleFileName);
    
    TString outputFileName(inputDir( 0, inputDir.First("/") ));
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
       outputFileName = outputFileName + dataEra;
       if (inputDir.Contains( "0000")) outputFileName = outputFileName + "_0";
       if (inputDir.Contains( "0001")) outputFileName = outputFileName + "_1";
    }
    outputFileName = outputFileName + "/"+ singleFileName;

    TString selection = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/objectTSelector.C";
    if ( istest ){
        outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/test_objectSelction/";
        // outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/checkForEY/";
        chain.Process( selection + "+", outputDir + outputFileName, 10000);
    }
    else chain.Process( selection + "+", outputDir + outputFileName);


}
