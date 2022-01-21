
void producePileupMC(
    // TString inputFile = ""
){
    TString dir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/tttt/";
    TChain chain("Events");
    chain.Add( dir + "outTree*.root" );

    TH1D * MCPileup = new TH1D( "MCPileup", "MCPileup", 0, 100, 100);
    chain.Project( "MCPileup", "Pileup_nPU");

    TFile* outFile = new TFile( "PUHistogram_mc2016_postAPV.root", "CREATE");
    MCPileup->Write();
    outFile->Close();
}
