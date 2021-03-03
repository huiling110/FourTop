void run_makeVaribles_forBDT(
                        Bool_t istest = true,
                        // Bool_t istest = false,
                        TString inputDir = "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn",
                        TString outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/test_objectSelction/"
                        // TString singleFileName = "v3_1-100.root"
                        )
{
    
    gROOT->ProcessLine(".L Loader.C+");

    TString inputBase = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v30_fixedChargeBranchBug/";
    TString inputFile = inputBase + inputDir + "/";

    TChain chain( "tree");
    // chain.Add(inputFile+singleFileName);
    chain.Add(inputFile + "v3*.root" );

    TString outputFileName = inputDir + ".root";

    TString selection = "/publicfs/cms/user/huahuil/code/FourTopTau/CMSSW_10_2_20_UL/src/FourTop/hua/makeVaribles_forBDT.C";


    if ( istest ){
        outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forMVA/test/";
        chain.Process( selection + "+", outputDir + outputFileName, 10000);
    }
    else chain.Process( selection + "+", outputDir + outputFileName);



}
 
