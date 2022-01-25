
void producePileupMC(
    // TString inputFile = ""
    // TString era = "2016postVFP"
    // TString era = "2016preVFP"
    // TString era = "2017"
    TString era = "2018"

){
    TString dir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/tttt/";
    TString outName;
    if (era == "2016postVFP"){
        dir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/tttt/";
        outName = "PUHistogram_mc2016_postVFP.root";
    } else if (era == "2016preVFP"){
        dir = "/publicfs/cms/data/TopQuark/nanoAOD/2016APV/mc/tttt/";
        outName = "PUHistogram_mc2016_preVFP.root";
    } else if (era == "2017"){
        dir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/tttt/";
        outName = "PUHistogram_mc2017.root";

    } else if(era == "2018"){
        dir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/tttt/";
        outName = "PUHistogram_mc2018.root";
        };

        TString outDir = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/data_rootFiles/";
        TChain chain("Events");
        chain.Add(dir + "outTree*.root");

        TH1D *MCPileup = new TH1D("pileup", "Pileup_nTrueInt", 100, 0, 100);
        chain.Project("pileup", "Pileup_nTrueInt");

        // TFile *outFile = new TFile(outDir + "PUHistogram_mc2016_postVFP.root", "RECREATE");
        TFile *outFile = new TFile(outDir + outName, "RECREATE");
        MCPileup->Write();
        outFile->Close();
}
