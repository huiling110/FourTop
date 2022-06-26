/**
 * @author Huiling Hua
 * @email huahl@ihep.ac.cn
 * @create date 2021-11-22 22:54:06
 * @modify date 2021-11-22 22:54:06
 * @desc [description]
 */

#include "../EYandSP_usingClass_v3.h"

#include "checkTemplatesForCombine.C"

void makeRootForCombine_1tau0l(){
    // TString inputQCD = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau0l_v1/11bins/QCDshapes_corrected.root";
    TString inputQCD = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau0l_HT/QCDshapes_corrected_UL2016.root";
    TFile *QCDfile = new TFile( inputQCD, "READ" );
    TH1D *QCD_HT = (TH1D*)QCDfile->Get( "h_QCD_HT_SR_DATAcorrected" );
    // QCDfile->Close();
    QCD_HT->Print();
    cout<<QCD_HT->Integral()<<"\n";
    cout<<QCD_HT->GetEntries()<<"\n";


    //output file for combine
    // TString outputName = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau0l_v1/11bins/dataDriven_1tau0l_forCombine.root";
    // TString outputName = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau0l_HT/dataDriven_1tau0l_forCombine.root";
    TString outputName = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v0preselection_fromV14/1tau0l_HT/dataDriven_1tau0l_forCombine.root";
    TFile *output = new TFile( outputName, "RECREATE" );

    //scale to  7679, scale it to the QCD event yield that Fabio estimated by using the fake rate method
    Double_t qcdYield =  5617;
    TH1D* my_QCD_HT = (TH1D*)QCD_HT->Clone();
    my_QCD_HT->Print();
    // my_QCD_HT->Scale( 7679/my_QCD_HT->Integral() );
    my_QCD_HT->Scale(  qcdYield/my_QCD_HT->Integral() );//2016nano
    my_QCD_HT->SetName( "QCD_HT" );
    cout<<my_QCD_HT->GetName()<<"\n"; 
    cout<<"interal after scaling: "<<my_QCD_HT->Integral()<<"\n";

    //HT distribution from other processes other than QCD
    Int_t binNum = QCD_HT->GetXaxis()->GetNbins();
    Double_t binMin = QCD_HT->GetXaxis()->GetXmin();
    Double_t binMax = QCD_HT->GetXaxis()->GetXmax();
    // TH1D* TT = addHistChannel( ES1tau0l, weight, "jets_HT", binNum, binMin, binMax, 1, 4, "TT_HT");//!!addHistChannel has no Lumi
    TH1D* TT = addHistChannel( ES1tau0l, basicWeight, "jets_HT", binNum, binMin, binMax, 1, 4, "TT_HT");
    TT->Scale(lumiMap[era_g]);
    TT->Print();
    // TT->Write();
    TH1D* TTX = addHistChannel( ES1tau0l, basicWeight, "jets_HT", binNum, binMin, binMax, 4, 9, "TTX_HT" );
    TTX->Scale(lumiMap[era_g]);

    TH1D* VV = addHistChannel( ES1tau0l, basicWeight, "jets_HT", binNum, binMin, binMax, 9, 12, "VV_HT" );
    VV->Scale(lumiMap[era_g]);

    TH1D*  SingleTop = addHistChannel( ES1tau0l, basicWeight, "jets_HT", binNum, binMin, binMax, 12, 15, "SingleTop_HT" );
    SingleTop->Scale(lumiMap[era_g]);

    TH1D*  TTTT = addHistChannel( ES1tau0l, basicWeight, "jets_HT", binNum, binMin, binMax, 0, 1, "TTTT_HT" );
    TTTT->Scale(lumiMap[era_g]);



    TH1D* data_obs = addHistChannel( ES1tau0l, basicWeight, "jets_HT", binNum, binMin, binMax, 0, 24, "data_obs_HT" );
    data_obs->Scale(lumiMap[era_g]);
    data_obs->Add( my_QCD_HT);
    data_obs->Print();
    //QCD starts from index 30
    TH1D *allBgs = addHistChannel(ES1tau0l, basicWeight, "jets_HT", binNum, binMin, binMax, 1, 15, "allBgs_HT");
    allBgs->Scale(lumiMap[era_g]);
    cout << "allBGs before QCD = " << allBgs->Integral();
    allBgs->SetDefaultSumw2();
    allBgs->Add(my_QCD_HT);
    cout << "allBGs after QCD = " << allBgs->Integral();



    // TString outFolder = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau0l_HT/templatesPlots/";
    // TString outFolder = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v0preselection_fromV14/1tau0l_HT/templatesPlots/";
    // drawTemplates( TT, outFolder );
    // drawTemplates( TTX, outFolder );
    // drawTemplates( VV, outFolder );
    // drawTemplates( SingleTop, outFolder );
    // drawTemplates( TTTT, outFolder );
    // drawTemplates( my_QCD_HT, outFolder );



    output->Write();
    output->Close();


}

