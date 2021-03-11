void run_makeVaribles_forBDT(
                        // Bool_t istest = true,
                        Bool_t istest = false,
                        TString inputDir = "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn",
                        TString outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forMVA/v1/"
                        // TString singleFileName = "v3_1-100.root"
                        )
{
    
    gROOT->ProcessLine(".L Loader.C+");

    TString inputBase = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v32_addedalleventsTree/";
    // TString inputBase = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/test_objectSelction/";
   

    TString inputFile = inputBase + inputDir + "/";
    cout<<"input file:"<<inputFile<<endl;

    TChain chain( "tree");
    // chain.Add(inputFile+singleFileName);
    chain.Add(inputFile + "v3*.root" );

    TString outputFileName = inputDir + ".root";

    TString selection = "/publicfs/cms/user/huahuil/code/FourTopTau/CMSSW_10_2_20_UL/src/FourTop/hua/makeVaribles_forBDT.C";

    if ( istest ){
        outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forMVA/test/";
        chain.Process( selection + "+", outputDir + outputFileName, 10000);
        // chain.Process( selection + "+", outputDir + outputFileName, 1000);
    }
    else chain.Process( selection + "+", outputDir + outputFileName);


    cout<<"--------"<<endl;
    cout<<"---------"<<endl;
    cout<<"now comes to add allevents stage"<<endl;
    TFile* file = TFile::Open(  outputDir + outputFileName , "UPDATE");
    cout<<"file opened :"<<file->GetName();
    TChain chain2( "allevents");
    chain2.Add(inputFile + "v3*.root" );
    // chain2.ls();
    // chain2.Merge( file, 1000, "C" );
    chain2.Merge( file, 2000 );
    // chain2.Merge( file, "C" );
    // chain2.Merge( file );
    // file->Write();
    // file->Close();



}
 
