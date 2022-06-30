void run_makeVaribles_forBDT(
    Bool_t istest = true,
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v9_allSelection/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v9_allSelection/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v10_JECandTESadded/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v12_addedMissingBranch/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v14_MetFilterHLTSelection//mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v15_0selection//mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v16_HLTselection/mc/",
    TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v16_HLTselection/data/",
    // TString inputBase = "../../objectSelection/",

    // TString inputDir = "tttt",
    TString inputDir = "jetHT_2016D",
    // TString inputDir = "ttbar_2l",
    // TString inputDir = "output/",
    TString outputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/",
    const TString eventSelectionBit = "7"  
    // 1 for MetFilters, 2 for HLTSelection, 4 for baseline. so 7 if all selection; 0 if no selection 
    )
{
    //get era from inputBase
    TString sub = inputBase( inputBase.Index("NanoAOD")+8, inputBase.Length());
    TString era = sub(0, sub.First("/") );
    cout<<era<<"\n";
    era.Remove( era.Index("UL"), 2  );
    era.Remove( era.Index("_") , 1 );
    cout<<"era in run: "<<era<<"\n";
   

    gROOT->ProcessLine( ".L makeVaribles_forBDT.so");
    
    Bool_t ifMergeAllevent = false;
    if ( !istest){
        ifMergeAllevent = true;
    }else{
        outputDir = "output/";
    }
   

    TString inputFile = inputBase + inputDir + "/";
    cout<<"input file:"<<inputFile<<endl;

    TChain chain( "tree");

    chain.Add(inputFile + "outTree*.root" );
    cout<<"entries in tree: "<<chain.GetEntries()<<endl;

    TString outputFileName = inputDir + ".root";

    TString selection = "makeVaribles_forBDT.C";

    TString option = outputDir+outputFileName + ":" + era +":" + eventSelectionBit + ":";
    cout<<"option in run: "<<option<<"\n";

    if ( istest ){
        chain.Process( selection + "+", option, 100);
        chain.Process( selection + "+", option, 1000);
    }
    else chain.Process( selection + "+", option);


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
 
