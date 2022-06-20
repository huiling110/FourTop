void run_makeVaribles_forBDT(
    Bool_t istest = true,
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v9_allSelection/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v9_allSelection/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v10_JECandTESadded/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v11_JECandTESInObjectSelectinLevel/mc/",
    TString inputBase = "../../objectSelection/",

    // TString inputDir = "tttt",
    TString inputDir = "output/",
    TString outputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/")
{
    
    gROOT->ProcessLine( ".L makeVaribles_forBDT.so");
    
    Bool_t ifMergeAllevent = false;
    if ( !istest){
        ifMergeAllevent = true;
    }
   

    TString inputFile = inputBase + inputDir + "/";
    cout<<"input file:"<<inputFile<<endl;

    TChain chain( "tree");

    chain.Add(inputFile + "outTree*.root" );
    cout<<"entries in tree: "<<chain.GetEntries()<<endl;

    TString outputFileName = inputDir + ".root";

    TString selection = "makeVaribles_forBDT.C";

    
    if ( istest ){
        outputDir = "output/";
        // chain.Process( selection + "+", outputDir + outputFileName, 10000);
        chain.Process( selection + "+", outputDir + outputFileName, 1000);
    }
    else chain.Process( selection + "+", outputDir + outputFileName);


    if ( ifMergeAllevent){
        cout<<"--------"<<endl;
        cout<<"now comes to add allevents stage"<<endl;
        TFile* file = TFile::Open(  outputDir + outputFileName , "UPDATE");
        // cout<<"file opened :"<<file->GetName();
        TChain chain2( "allevents");
        chain2.Add(inputFile + "outTree*.root" );
        cout<<"entries in allevent tree: "<<chain2.GetEntries()<<endl;
        // chain2.ls();
        // chain2.Merge( file, 1000, "C" );
        chain2.Merge( file, 2000 );
        // file->Write();
        // file->Close();
    }


}
 
