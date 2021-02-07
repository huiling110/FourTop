void runVariblesTree(){
    std::cout << "Run VariblesTree " << std::endl;
    
    TFile *file = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/NewNtupleAfterEventSelection_test/v3/NoJEC/TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn.root");
    TTree *tree = (TTree*) file->Get("tree");
    // TString selector = "/publicfs/cms/user/huahuil/code/FourTopTau/CMSSW_10_2_20_UL/src/FourTop/hua/makeVariblesTree.C";
    TString selector = "/publicfs/cms/user/huahuil/code/FourTopTau/CMSSW_10_2_20_UL/src/FourTop/hua/makeVariblesTree_v2.C";
    tree->Process(selector + "+", "", 1000 );
}
