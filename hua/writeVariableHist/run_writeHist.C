
void run_writeHist(
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baselineSelection_fromV15/",
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v16_HLTselection/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v16_HLTselection/data/",
    TString inputProcess = "tttt"
    // TString inputProcess = "tt"
    // TString inputProcess = "jetHT_2016C"
){
    // gROOT->ProcessLine( ".L writeHist.so");


    TString inputFile = inputDir + inputProcess + ".root";

    Bool_t isData = kFALSE;
    if ( inputDir.Contains("data") )  isData = kTRUE;

    //get genWeightSumInitial for the process
    Double_t genWeightSumInitial = 1.0;
    if ( !isData ){
        TFile* m_file =  new TFile( inputFile, "READ");
        TTree* alleventTree = (TTree*)m_file->Get("allevents") ;
        TH1D* h_genWeight = new TH1D( "genWeight", "genWeight", 100, -100., 100.);
        alleventTree->Project( "genWeight", "genWeight_allEvents");
        h_genWeight->StatOverflows(kTRUE);
        genWeightSumInitial = h_genWeight->GetMean() * h_genWeight->GetEntries();
    }
    cout<<"genWeightSumInitial: "<<genWeightSumInitial<<"\n";





    TChain chain("newtree");
    chain.Add( inputFile );

    TString option1 =  std::to_string(genWeightSumInitial);
    TString option = option1 + ":" + inputDir + ":" + inputProcess+":" + isData +":" ;
    cout<<"option in run_writeHist: "<<option<<"\n";


    TStopwatch t;
    t.Start();


    chain.Process( "writeHist.C+", option );

    t.Stop();
    t.Print();


}