#include "CMS_lumi.C"
void DrawTransitionFactor(TString path, TString VAR,TString CAT, double X1LEG, double Y1LEG, double X2LEG, double Y2LEG, TString LEGTITLE, bool LOG,int REBIN, TString XTITLE,bool PRINT)
{
  gROOT->ForceStyle();  
  gStyle->SetPaintTextFormat("1.3g"); 

  TH1F  *h[2];
  TFile * inputfile;

  inputfile = TFile::Open(path);
  h[0] = (TH1F*)inputfile->Get("h_QCD_"+VAR+"_SR");//signal region
  h[0]->Rebin(REBIN);
  h[0]->Scale(1/h[0]->Integral());
  h[1] = (TH1F*)inputfile->Get("h_QCD_"+VAR+"_"+CAT);//alternative region
  h[1]->Rebin(REBIN);
  h[1]->Scale(1/h[1]->Integral());
  
 TLegend * legend0 = new TLegend(X1LEG, Y1LEG, X2LEG, Y2LEG, "", "NDC"); 
 legend0->SetHeader(LEGTITLE);
  legend0->SetFillColor(0);
  legend0->SetBorderSize(0);
  legend0->SetTextFont(42);
  legend0->SetTextSize(0.035);
  legend0->AddEntry(h[0], "Signal selection", "f");
  if (CAT=="CR") legend0->AddEntry(h[1], "Control selection", "l");
  if (CAT=="VR") legend0->AddEntry(h[1], "Validation selection", "l");

  TCanvas *can = new TCanvas(VAR+CAT,VAR+CAT,900,600);
  can->SetRightMargin(0.15);
  can->SetBottomMargin(0.25);
  
  
    h[0]->SetLineColor(kBlue-7);
    h[0]->SetFillColor(kBlue-10);
    h[0]->SetFillStyle(3022);
    h[0]->SetLineWidth(2);
    h[0]->GetXaxis()->SetTitleOffset(22.2);
    h[0]->SetXTitle(XTITLE);
    h[0]->SetYTitle("Events / 100 GeV");
    h[0]->SetMinimum(0.01);
    h[0]->Draw("histoE");
    gPad->Update();
    
    h[1]->SetLineColor(kRed);
    h[1]->SetLineWidth(2);
    //move title downwards, remove grid and numbers
//     AK4bbMass_M_MC->SetMaximum(0.22);
//     AK4bbMassC2_M_MC->SetMinimum(-0.00001);
    h[1]->Draw("histosameE");
    gPad->Update();
    
      legend0->Draw();
    
    CMS_lumi(can,4,0);
      
    TH1F *hRatio1 = (TH1F*)h[0]->Clone("Ratio");
    h[0]->SetLabelOffset(999);
    h[0]->SetLabelSize(0);
    hRatio1->SetLineColor(kBlack);
    hRatio1->SetLineWidth(2);
    hRatio1->Divide(h[1]);
     
    TPad *pad1 = new TPad("pad","pad",0.,0.,1.,1.);
    pad1->SetTopMargin(0.77);
    pad1->SetRightMargin(0.15);
    pad1->SetFillColor(0);
    pad1->SetFillStyle(0);
    pad1->Draw();
    gPad->Update();
    pad1->cd(0);
    pad1->SetGridy();
    if (CAT=="CR") hRatio1->SetYTitle("Sig/Ctl");
    if (CAT=="VR") hRatio1->SetYTitle("Sig/Val");
    hRatio1->GetXaxis()->SetTitleOffset(0.95);
    hRatio1->GetYaxis()->SetTitleSize(0.03);
    hRatio1->GetYaxis()->SetLabelSize(0.03);
    hRatio1->GetYaxis()->SetRangeUser(0.4, 1.6);
    hRatio1->GetYaxis()->SetNdivisions(505);
    hRatio1->Draw("p");
    
    TFile *outputfile = new TFile( "QCDTransitionFunctions.root", "UPDATE" );
    //TFile *outputfile = new TFile( "asdowsky.root", "UPDATE" );
    
    TF1 *TransitionFunction;
    if (CAT == "CR") {
    cout << " " << endl << "~~~~~ " << CAT << " ~~~~~" << endl;
    TFitResultPtr r = hRatio1->Fit("pol1", "S");
    TMatrixD cov = r->GetCovarianceMatrix();
    cov.Print();
    cov.Write("CovarianceMatrix"+CAT);
    TransitionFunction = hRatio1->GetFunction("pol1");
    gPad->Update();
    }
    
    if (CAT == "VR") {
    cout << " " << endl << "~~~~~ " << CAT << " ~~~~~" << endl;
    TFitResultPtr r = hRatio1->Fit("pol1", "S");
    TMatrixD cov = r->GetCovarianceMatrix();
    cov.Print();
    cov.Write("CovarianceMatrix"+CAT);
    TransitionFunction = hRatio1->GetFunction("pol1");
    gPad->Update();
    }
    
    
    TransitionFunction->Write("TransitionFunction"+CAT);
    outputfile->Close();

    
  
    
    if (PRINT) {//save plots
    can->SaveAs(VAR+"_"+CAT+".pdf"); 
  }
  
} 
