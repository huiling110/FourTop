#include "EYandSP_usingClass_v3.h"

void generateHTfor1tau0l(){
    TString QCD = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/QCDshapes_corrected.root";
    TFile* QCD_fabio = new TFile( QCD, "READ");
    TH1D* qcd_SR = (TH1D*)QCD_fabio->Get("h_QCD_HT_SR_DATAcorrected");
    qcd_SR->Print();
    Int_t binNum = qcd_SR->GetXaxis()->GetNbins();
    cout<<"binNum = "<<binNum<<"\n";

}

