
void makeTSelector(

){

    TString inputFile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baselineSelection_fromV15/tttt.root";

    // TChain chain("TNT/BOOM");
    // chain.Add(inputFile+"v3*.root");
    // chain.MakeSelector("objectTSelector");
    // chain.MakeClass("objectTSelector_Mclass");

    TString selectorName = "writeHist";

    TChain nanoEventChain("newtree");
    nanoEventChain.Add(inputFile);
    nanoEventChain.MakeSelector( selectorName.Data() );
}
