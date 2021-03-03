
void makeSelector(){
    // TFile *file = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/NewNtupleAfterEventSelection_test/v3/NoJEC/TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn.root");
    TFile *file = TFile::Open("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v30_fixedChargeBranchBug/TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn/v3_1-1.root");
    TTree *tree = (TTree*) file->Get("tree");
    tree->MakeSelector("makeVaribles_forBDT");

}
