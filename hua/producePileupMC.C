
void producePileupMC(
    // TString inputFile = ""
){
    TString dir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/tttt/";
    TChain chain("Events");
    chain.Add( dir + "outTree*.root" );

    TH1D * MCPileup = new TH1D( "pileup", "Pileup_nTrueInt", 100, 0, 100);
    chain.Project( "pileup", "Pileup_nTrueInt");

    TFile* outFile = new TFile( "PUHistogram_mc2016_postAPV.root", "RECREATE");
    MCPileup->Write();
    outFile->Close();
}
