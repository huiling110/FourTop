
void run_objectTSelector(){

    gROOT->ProcessLine(".L Loader.C+");

    TString inputDir = "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn/Legacy16V2_TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8addGenWeight/210201_023641/0000/";
    TString inputFile; TString inputBase = "/publicfs/cms/data/TopQuark/FourTop_hua/v3/2016/";
    inputFile = inputBase + inputDir;
    TChain chain("TNT/BOOM");
    chain.Add(inputFile+"v3*.root");
    
    TString selection = "/publicfs/cms/user/huahuil/code/FourTopTau/CMSSW_10_2_20_UL/src/FourTop/objectTSelector.C";
    chain.Process( selection + "+", "", 1000);



}
