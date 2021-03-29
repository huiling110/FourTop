void getEnties(){
    
    TString inputDir = "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn";
    // TString inputBase = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v40_fixedHLTBugWithPreselection/";
    TString inputBase = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v35_preselection/";

    TString inputFile = inputBase + inputDir + "/";
    cout<<"input file:"<<inputFile<<endl;

    TChain chain( "tree");
    chain.Add(inputFile + "v3*.root" );
    cout<<"entries in tree: "<<chain.GetEntries()<<endl;




}
