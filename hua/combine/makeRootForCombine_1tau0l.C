void makeRootForCombine_1tau0l(){
    TString inputQCD = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau0l_v1/11bins/QCDshapes_corrected.root";
    TFile *QCDfile = new TFile( inputQCD, "READ" );
    TH1D *QCD_HT = (TH1D*)QCDfile->Get( "h_QCD_HT_SR_DATAcorrected" );
    // QCDfile->Close();
    QCD_HT->Print();
    cout<<QCD_HT->Integral()<<"\n";
    cout<<QCD_HT->GetEntries()<<"\n";

    //output file for combine
    TString outputName = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau0l_v1/11bins/dataDriven_1tau0l_forCombine.root";
    TFile *output = new TFile( outputName, "RECREATE" );

    //scale to  7679, scale it to the QCD event yield that Fabio estimated by using the fake rate method
    TH1D* my_QCD_HT = (TH1D*)QCD_HT->Clone();
    // QCDfile->Close();
    my_QCD_HT->Print();
    my_QCD_HT->Scale( 7679/my_QCD_HT->Integral() );
    my_QCD_HT->SetName( "QCD_HT" );
    cout<<my_QCD_HT->GetName()<<"\n"; 
    cout<<"interal after scaling: "<<my_QCD_HT->Integral()<<"\n";

    my_QCD_HT->Write();
    output->Close();

    





}

