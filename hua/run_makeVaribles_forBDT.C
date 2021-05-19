void run_makeVaribles_forBDT(
                        Bool_t istest = true,
                        // Bool_t istest = false,
                        TString inputDir = "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn",
                        // TString inputDir = "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",
                        // TString inputDir = "TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8",
                        TString outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forMVA/test/"
                        // TString outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forMVA/v10_v41/"
                        // TString singleFileName = "v3_1-100.root"
                        )
{
    
    gROOT->ProcessLine(".L Loader.C+");
    
    Bool_t ifMergeAllevent = false;
    if ( !istest){
        ifMergeAllevent = true;
    }
    // TString inputBase = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v43_addSingJetHLT/";
    TString inputBase = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v44_fixedSingJetHLTBugAndAddHLTcut/";

    // TString inputBase = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/test_objectSelction/";
   

    TString inputFile = inputBase + inputDir + "/";
    cout<<"input file:"<<inputFile<<endl;

    TChain chain( "tree");

    chain.Add(inputFile + "v3*.root" );
    cout<<"entries in tree: "<<chain.GetEntries()<<endl;

    TString outputFileName = inputDir + ".root";

    TString selection = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/makeVaribles_forBDT.C";

    
    if ( istest ){
        outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forMVA/test/";
        chain.Process( selection + "+", outputDir + outputFileName, 10000);
        // chain.Process( selection + "+", outputDir + outputFileName, 1000);
    }
    else chain.Process( selection + "+", outputDir + outputFileName);


    if ( ifMergeAllevent){
        cout<<"--------"<<endl;
        cout<<"now comes to add allevents stage"<<endl;
        TFile* file = TFile::Open(  outputDir + outputFileName , "UPDATE");
        // cout<<"file opened :"<<file->GetName();
        TChain chain2( "allevents");
        chain2.Add(inputFile + "v3*.root" );
        cout<<"entries in allevent tree: "<<chain2.GetEntries()<<endl;
        // chain2.ls();
        // chain2.Merge( file, 1000, "C" );
        chain2.Merge( file, 2000 );
        // file->Write();
        // file->Close();
    }


}
 
