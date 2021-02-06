
void makeSelector(){
    TFile *file = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/NewNtupleAfterEventSelection_test/v3/NoJEC/TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn.root");
    TTree *tree = (TTree*) file->Get("tree");
    tree->MakeSelector("makeVariblesTree");

}
