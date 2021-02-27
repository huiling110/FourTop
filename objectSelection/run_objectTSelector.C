
void run_objectTSelector(Bool_t istest = true,
                        TString inputDir = "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn/Legacy16V2_TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8addGenWeight/210201_023641/0000/",
                        TString outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v27_objectSelection/",
                        TString singleFileName = "v3_1-100.root")
{
    gROOT->ProcessLine(".L Loader.C+");

    TString inputFile; TString inputBase = "/publicfs/cms/data/TopQuark/FourTop_hua/v3/2016/";
    inputFile = inputBase + inputDir;
    TChain chain("TNT/BOOM");
    // chain.Add(inputFile+"v3*.root");
    chain.Add(inputFile+singleFileName);
    
    TString outputFileName(inputDir( 0, inputDir.First("/") ));
    // outputFileName = outputFileName + ".root";
    outputFileName = outputFileName + "/"+ singleFileName;
    // outputFileName = outputFileName + singleFileName;
    TString selection = "/publicfs/cms/user/huahuil/code/FourTopTau/CMSSW_10_2_20_UL/src/FourTop/objectSelection/objectTSelector.C";
    if ( istest ){
        outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/test_objectSelction/";
        chain.Process( selection + "+", outputDir + outputFileName, 1000);
    }
    else chain.Process( selection + "+", outputDir + outputFileName);


}
