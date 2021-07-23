
void calSigHisto(const TH1D* BDT_S, const TH1D* BDT_B, TH1D* &sig_h){

    Double_t EY_S = 7.37; //1tau1l
    Double_t EY_B = 2021.04;
    Int_t binNum = BDT_S->GetNbinsX();
    Double_t binRange = ( BDT_S->GetXaxis()->GetBinUpEdge(binNum) ) - ( BDT_S->GetXaxis()->GetBinLowEdge(1) );
    cout<<BDT_S->GetXaxis()->GetBinUpEdge(binNum)<<" "<<BDT_S->GetXaxis()->GetBinLowEdge(1);
    cout<<"binNum = "<<binNum<<"  binRange ="<<binRange<<"\n";
    Double_t gWeight_S = EY_S * binRange / binNum ;
    Double_t gWeight_B = EY_B * binRange / binNum ;

    TCanvas *c = new TCanvas("c", "c")
    sig_h = new TH1D( "sig_h", "sig_h", binNum, BDT_S->GetXaxis()->GetBinLowEdge(1), BDT_S->GetXaxis()->GetBinUpEdge(binNum) );
    for( int i=0;i<binNum;i++ ){
        
        Float_t s_BDT = BDT_S->Integral(i,binNum) * gWeight_S ;
        Float_t b_BDT = BDT_B->Integral(i,binNum) * gWeight_B ;
        Float_t sig_BDT = TMath::Sqrt(2*((s_BDT+b_BDT)*log(1+s_BDT/b_BDT)-s_BDT));
        cout<<i<<":"<<sig_BDT<<"  ";
        if( s_BDT>0 && b_BDT>0 ) sig_h->SetBinContent(i, sig_BDT/TMath::Sqrt(0.4));
    }
    sig_h->SetMaximum( 1);
    sig_h->Draw();


}

void significance_usingPDF(
    TString fin = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v1/1tau1l_varibleList_15.root"
        )
{
    TFile* f=new TFile( fin );
    TH1D* BDT_S = (TH1D*)f->Get( "dataset/Method_BDT/BDT/MVA_BDT_S");
    TH1D* BDT_B = (TH1D*)f->Get( "dataset/Method_BDT/BDT/MVA_BDT_B");
    //same enties in test tree
    //is a pdf because integral is 1
    TH1D* BDTG_S = (TH1D*)f->Get( "dataset/Method_BDT/BDTG/MVA_BDTG_S");
    TH1D* BDTG_B = (TH1D*)f->Get( "dataset/Method_BDT/BDTG/MVA_BDTG_B");

    BDT_S->Draw();

    // BDTG_B->Draw("same");
    // cout<<"entries in testTree: "<<t->GetEntries()<<endl;
    // cout<<"BDTG_S_entries = "<<BDTG_S->GetEntries()<<endl;
    // cout<<"BDTG_binNum = "<<BDTG_S->GetNbinsX()<<endl;
    // cout<<"BDTG_S_integral = "<<BDTG_S->Integral()<<endl;
    // cout<<"BDTG_S_integral*binWidth = "<<BDTG_S->Integral()*BDTG_S->GetBinWidth(1)<<endl;
 
    TH1D* BDT_sig;
    TH1D* BDTG_sig;
    calSigHisto( BDT_S, BDT_B, BDT_sig ) ;
    calSigHisto( BDTG_S, BDTG_B, BDTG_sig );


}
    





/*        

    // Double_t maximumSig = BDTG_significance->GetBinContent(BDTG_significance->GetMaximumBin())/TMath::Sqrt(0.4);
    Double_t maximumSig = BDTG_significance->GetBinContent(BDTG_significance->GetMaximumBin());
    float bestCut = -1 + 0.01*(BDTG_significance->GetMaximumBin());
    cout<<"tight category"<<endl;
    cout<<"best cut : "<<BDTG_significance->GetMaximumBin()<<endl;
    cout<<"signal : "<<BDTG_S->Integral(BDTG_significance->GetMaximumBin(),200)/0.4<<endl;
    cout<<"background : "<<BDTG_B->Integral(BDTG_significance->GetMaximumBin(),200)/0.4<<endl;
    cout<<"significance : "<<maximumSig<<endl;
    //???is this calculation correct?
      TLatex tl;
      tl.SetNDC();
      tl.SetTextSize( 0.033 );
      tl.DrawLatex( 0.15, 0.19, Form("maximum significance is %f when cutting at %f ", maximumSig, bestCut)  );


*/



    
