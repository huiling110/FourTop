
void makeTSelector(

){
    TString inputBase = "/publicfs/cms/data/TopQuark/FourTop_hua/v3/2016/";
    TString inputDir = "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn/Legacy16V2_TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8addGenWeight/210201_023641/0000/";
    TString inputFile; 
    inputFile = inputBase + inputDir;

    inputFile = "/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/tttt/outTree_0.root";

    // TChain chain("TNT/BOOM");
    // chain.Add(inputFile+"v3*.root");
    // chain.MakeSelector("objectTSelector");
    // chain.MakeClass("objectTSelector_Mclass");

    TString objectSelectorName = "objectTSelectorForNanoAOD";

    TChain nanoEventChain("Events");
    nanoEventChain.Add(inputFile);
    nanoEventChain.MakeSelector("objectTSelectorForNanoAOD");
}
