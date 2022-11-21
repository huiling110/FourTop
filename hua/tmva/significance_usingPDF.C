
// #include "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/tmvaglob.h"
#include "tmvaglob.h"

void calSigHisto(const TH1D *BDT_S, const TH1D *BDT_B, TH1D *&sig_h, const TString fin)
{

    Double_t EY_S = 7.37; // 1tau1l
    Double_t EY_B = 2021.04;
    Int_t binNum = BDT_S->GetNbinsX();
    Double_t binRange = (BDT_S->GetXaxis()->GetBinUpEdge(binNum)) - (BDT_S->GetXaxis()->GetBinLowEdge(1));
    Double_t lowX = BDT_S->GetXaxis()->GetXmin();
    Double_t maxX = BDT_S->GetXaxis()->GetXmax();
    // cout<<BDT_S->GetXaxis()->GetBinUpEdge(binNum)<<" "<<BDT_S->GetXaxis()->GetBinLowEdge(1);
    // cout<<"binNum = "<<binNum<<"  binRange ="<<binRange<<"\n";
    // cout<<BDT_S->GetXaxis()->GetXmax()<<" : "<<BDT_S->GetXaxis()->GetBinUpEdge(binNum)<<"\n";
    Double_t gWeight_S = EY_S * binRange / binNum;
    Double_t gWeight_B = EY_B * binRange / binNum;

    TCanvas *c = new TCanvas("c", "c");
    sig_h = new TH1D("sig_h", "sig_h", binNum, BDT_S->GetXaxis()->GetBinLowEdge(1), BDT_S->GetXaxis()->GetBinUpEdge(binNum));
    for (int i = 0; i < binNum; i++)
    {

        Float_t s_BDT = BDT_S->Integral(i, binNum) * gWeight_S;
        Float_t b_BDT = BDT_B->Integral(i, binNum) * gWeight_B;
        Float_t sig_BDT = TMath::Sqrt(2 * ((s_BDT + b_BDT) * log(1 + s_BDT / b_BDT) - s_BDT));
        // cout<<i<<":"<<sig_BDT<<"  ";
        if (s_BDT > 0 && b_BDT > 0)
            sig_h->SetBinContent(i, sig_BDT / TMath::Sqrt(0.4));
    }

    TString s_name = BDT_S->GetName();
    // cout<<"s_BDT Name: "<<BDT_S->GetName()<<"\n";
    // cout<<s_name.Contains( "BDTG")<<"\n";
    TString inputNum = TMVAGlob::getInputNum(fin);
    cout << "inputNum = " << inputNum << "\n";
    TString fileDir, fileName;
    TMVAGlob::getFileDirName(fin, fileDir, fileName);
    Double_t maxSig, bestCut;
    if (s_name.Contains("BDTG"))
    {
        sig_h->SetTitle(Form("Significance of BDTG(%s inputs)", inputNum.Data()));
        sig_h->GetXaxis()->SetRange(1, 35);
        maxSig = sig_h->GetMaximum();
        cout << "BDTG_sigMax = " << maxSig << "\n";
    }
    else
    {
        sig_h->SetTitle(Form("Significance of BDT(%s inputs)", inputNum.Data()));
        sig_h->GetXaxis()->SetRange(1, 30); // 1tau1l
        if (fileName.Contains("1tau2os") or fileName.Contains("1tau2l"))
        {
            cout << "fileName contains 1tau2os"
                 << "\n";
            sig_h->GetXaxis()->SetRange(1, 26); // 1tau2os
        }
        // if ( fileName.Contains( "2tau1l") ){
        if (fileName.Contains("2taull"))
        {
            cout << "fileName contains 2tau1l"
                 << "\n";
            // sig_h->GetXaxis()->SetRange( 1, 22 );
            // sig_h->GetXaxis()->SetRange( 1, 26 );
            sig_h->GetXaxis()->SetRange(1, 28);
            // sig_h->GetXaxis()->SetRange( 1, 21 );
        }
        maxSig = sig_h->GetMaximum();
        cout << "BDT_sigMax = " << maxSig << "\n";
        // cout<<"sigMax = "<<sig_h->GetMaximum()<<"\n";
    }

    bestCut = lowX + sig_h->GetBinWidth(1) * sig_h->GetMaximumBin();
    sig_h->GetXaxis()->SetRange(1, binNum);

    sig_h->SetMaximum(1);
    sig_h->Draw();

    TLatex tl;
    tl.SetNDC();
    tl.SetTextSize(0.033);
    tl.DrawLatex(0.15, 0.19, Form("maximum significance is %f when cutting at %f ", maxSig, bestCut));

    TMVAGlob::imgconv(c, Form("%s%s%s_sig", fileDir.Data(), fileName.Data(), BDT_S->GetName()));
}

void significance_usingPDF(
    // TString fin = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v1/1tau1l_varibleList_15.root"
    // TString fin = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau2os_v1/1tau2os_varibleList_19.root"
    TString fin = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v1/2taull_varibleList_20.root")
{
    TFile *f = new TFile(fin);
    TH1D *BDT_S = (TH1D *)f->Get("dataset/Method_BDT/BDT/MVA_BDT_S");
    TH1D *BDT_B = (TH1D *)f->Get("dataset/Method_BDT/BDT/MVA_BDT_B");
    // same enties in test tree
    // is a pdf because integral is 1
    //  TH1D* BDTG_S = (TH1D*)f->Get( "dataset/Method_BDT/BDTG/MVA_BDTG_S");
    //  TH1D* BDTG_B = (TH1D*)f->Get( "dataset/Method_BDT/BDTG/MVA_BDTG_B");

    // BDT_S->Draw();

    // BDTG_B->Draw("same");
    // cout<<"entries in testTree: "<<t->GetEntries()<<endl;
    // cout<<"BDTG_S_entries = "<<BDTG_S->GetEntries()<<endl;
    // cout<<"BDTG_binNum = "<<BDTG_S->GetNbinsX()<<endl;
    // cout<<"BDTG_S_integral = "<<BDTG_S->Integral()<<endl;
    // cout<<"BDTG_S_integral*binWidth = "<<BDTG_S->Integral()*BDTG_S->GetBinWidth(1)<<endl;

    TH1D *BDT_sig;
    TH1D *BDTG_sig;
    calSigHisto(BDT_S, BDT_B, BDT_sig, fin);
    // calSigHisto( BDTG_S, BDTG_B, BDTG_sig, fin );
}
