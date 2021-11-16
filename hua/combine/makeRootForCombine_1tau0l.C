void makeRootForCombine_1tau0l(){
    TString inputQCD = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau0l_v1/11bins/QCDshapes_corrected.root";
    TFile *QCDfile = new TFile( inputQCD, "READ" );
    TH1D *QCD_HT = (TH1D*)QCDfile->Get( "h_QCD_HT_SR_DATAcorrected" );
    QCD_HT->Print();

    cout<<QCD_HT->Integral()<<"\n";

}

