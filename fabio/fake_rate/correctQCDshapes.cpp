//take the QCD shape obtained from data in CR and computed a "shifted up" and a "shifted down" version. This is done by fitting the Signal/Control ratio in MC QCD with a straight line and using this line with up and down parameters to compute the shifted shapes

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>
#include <TCanvas.h>
#include <TEfficiency.h>
#include <TLatex.h>
#include <TStyle.h>
#include <sstream>
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include <Math/Math.h>
#include <TLorentzVector.h>
#include <Math/Vector3D.h>
#include <Math/DisplacementVector3D.h>
#include <Math/Vector3Dfwd.h>

#include <iostream>




using namespace std;


void correctQCDshapes () {

gROOT->ForceStyle();  
gStyle->SetPaintTextFormat("1.3g"); 

//take QCD shapes from data
TFile *inputDATAfile;
inputDATAfile = TFile::Open("tauF_Pt_DATA.root");

TH1F *h_QCD_HT_CR = (TH1F*)inputDATAfile->Get("h_QCD_HT_CR");
TH1F *h_QCD_HT_VR = (TH1F*)h_QCD_HT_CR->Clone("h_QCD_HT_VR");
TH1F *h_QCD_HT_SR = (TH1F*)h_QCD_HT_CR->Clone("h_QCD_HT_SR");

//clone them to further shift them up and down
TH1F *h_QCD_HT_VRUp = (TH1F*)h_QCD_HT_CR->Clone("h_QCD_HT_VRUp");
TH1F *h_QCD_HT_VRDown = (TH1F*)h_QCD_HT_CR->Clone("h_QCD_HT_VRDown");
TH1F *h_QCD_HT_SRUp = (TH1F*)h_QCD_HT_CR->Clone("h_QCD_HT_SRUp");
TH1F *h_QCD_HT_SRDown = (TH1F*)h_QCD_HT_CR->Clone("h_QCD_HT_SRDown");

//TAKE THE TRANSITION FUNCTIONS OBTAINED WITH THE COVARIANCE METHOD
TFile *inputTFfile;
inputTFfile = TFile::Open("QCDshiftedTransitionfunctions.root");
TF1 *TransitionFunctionVR= (TF1*)inputTFfile->Get("TransitionFunctionVRnominal");
TF1 *TransitionFunctionVRUp= (TF1*)inputTFfile->Get("TransitionFunctionVRUp");
TF1 *TransitionFunctionVRDown= (TF1*)inputTFfile->Get("TransitionFunctionVRDown");
TF1 *TransitionFunctionSR= (TF1*)inputTFfile->Get("TransitionFunctionSRnominal");
TF1 *TransitionFunctionSRUp= (TF1*)inputTFfile->Get("TransitionFunctionSRUp");
TF1 *TransitionFunctionSRDown= (TF1*)inputTFfile->Get("TransitionFunctionSRDown");

Float_t binwidth = ( h_QCD_HT_CR->GetXaxis()->GetXmax() - h_QCD_HT_CR->GetXaxis()->GetXmin() ) / ( h_QCD_HT_CR->GetSize() - 2 ); 
 
for(int i = 1; i < 11; i++ ){
     
    //apply transition functions
    h_QCD_HT_VR->SetBinContent     (i, h_QCD_HT_CR->GetBinContent(i) * TransitionFunctionVR->Eval(h_QCD_HT_CR->GetXaxis()->GetXmin() + i*binwidth - binwidth/2));
	h_QCD_HT_VRUp->SetBinContent   (i, h_QCD_HT_CR->GetBinContent(i) * TransitionFunctionVRUp->Eval(h_QCD_HT_CR->GetXaxis()->GetXmin() + i*binwidth - binwidth/2));
	h_QCD_HT_VRDown->SetBinContent (i, h_QCD_HT_CR->GetBinContent(i) * TransitionFunctionVRDown->Eval(h_QCD_HT_CR->GetXaxis()->GetXmin() + i*binwidth - binwidth/2));
	h_QCD_HT_SR->SetBinContent     (i, h_QCD_HT_CR->GetBinContent(i) * TransitionFunctionSR->Eval(h_QCD_HT_CR->GetXaxis()->GetXmin() + i*binwidth - binwidth/2));
	h_QCD_HT_SRUp->SetBinContent   (i, h_QCD_HT_CR->GetBinContent(i) * TransitionFunctionSRUp->Eval(h_QCD_HT_CR->GetXaxis()->GetXmin() + i*binwidth - binwidth/2));
	h_QCD_HT_SRDown->SetBinContent (i, h_QCD_HT_CR->GetBinContent(i) * TransitionFunctionSRDown->Eval(h_QCD_HT_CR->GetXaxis()->GetXmin() + i*binwidth - binwidth/2));

}
 
TFile *outputfile = new TFile( "QCDshapes_corrected.root", "RECREATE" );
h_QCD_HT_CR->Write("h_QCD_HT_CR");
h_QCD_HT_VR->Write("h_QCD_HT_VR_DATAcorrected");
h_QCD_HT_VRUp->Write("h_QCD_HT_VRUp_DATAcorrected");
h_QCD_HT_VRDown->Write("h_QCD_HT_VRDown_DATAcorrected");
h_QCD_HT_SR->Write("h_QCD_HT_SR_DATAcorrected");
h_QCD_HT_SRUp->Write("h_QCD_HT_SRUp_DATAcorrected");
h_QCD_HT_SRDown->Write("h_QCD_HT_SRDown_DATAcorrected");

outputfile->Close();
delete outputfile;


}



