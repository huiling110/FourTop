/**
 * @author Huiling Hua
 * @email huahl@ihep.ac.cn
 * @create date 2021-11-19 17:40:24
 * @modify date 2021-11-19 17:40:24
 * @desc [description]
 */

#include "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/EYandSP_usingClass_v3.h"


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

    //HT distribution from other processes other than QCD
    Int_t binNum = QCD_HT->GetXaxis()->GetNbins();
    Double_t binMin = QCD_HT->GetXaxis()->GetXmin();
    Double_t binMax = QCD_HT->GetXaxis()->GetXmax();
    // TH1D* TT = TTTo2L2Nu.getChannelHist( ES1tau0l, weight, "jets_HT", binNum, binMin, binMax );
    // TT->Add( TTToHadronic.getChannelHist( ES1tau0l, weight, "jets_HT", binNum, binMin, binMax ) );
    // TT->Add( TTToSemiLeptonic.getChannelHist( ES1tau0l, weight,"jets_HT", binNum, binMin, binMax ) );
    TH1D* TT = addHistChannel( ES1tau0l, weight, "jets_HT", binNum, binMin, binMax, 1, 4, "TT_HT");
    TT->Print();
    TT->Write();

    TH1D* ttX = addHistChannel( ES1tau0l, weight, "jets_HT", binNum, binMin, binMax, 4, 8, "ttX_HT" );
    ttX->Print();

    TH1D* VV = addHistChannel( ES1tau0l, weight, "jets_HT", binNum, binMin, binMax, 8, 13, "VV_HT" );

    TH1D* VVV = addHistChannel( ES1tau0l, weight, "jets_HT", binNum, binMin, binMax, 13, 21, "VVV_HT" );

    TH1D* WJets = addHistChannel( ES1tau0l, weight, "jets_HT", binNum, binMin, binMax, 21, 22, "WJets_HT" );

    TH1D* DYJets = addHistChannel( ES1tau0l, weight, "jets_HT", binNum, binMin, binMax, 22, 23, "DYJets_HT" );
    TH1D*  singleTop = addHistChannel( ES1tau0l, weight, "jets_HT", binNum, binMin, binMax, 23, 27, "singleTop_HT" );
    TH1D*  TX= addHistChannel( ES1tau0l, weight, "jets_HT", binNum, binMin, binMax, 27, 30, "TX_HT" );

    //data_obs
    
    TH1D*  TTTT = addHistChannel( ES1tau0l, weight, "jets_HT", binNum, binMin, binMax, 0, 1, "TTTT_HT" );
    TH1D* data_obs = addHistChannel( ES1tau0l, weight, "jets_HT", binNum, binMin, binMax, 0, 30, "data_obs_HT" );
    // data_obs->Add( TTTT );
    // data_obs->SetName( "data_obs_HT" ); 


    // my_QCD_HT->Write();
    output->Write();
    output->Close();

    





}

