void significanceDisstribution()
{
    TString fileName="/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v1HT400Cut_v44_fixedSingJetHLTBugAndAddHLTcut/1tau1mu_step1_40variables.root";
    // TString fileName="/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v1HT400Cut_v44_fixedSingJetHLTBugAndAddHLTcut/1tau1e_step2RemoveBjetsTL.root";
    TFile* f=new TFile(fileName);
    TTree* t=(TTree*)f->Get("dataset/TestTree");
    Float_t BDTG, weight;
    Float_t BDT, weightBDT;
    char className[11];


    t->SetBranchAddress("BDTG",&BDTG);
    t->SetBranchAddress("BDT",&BDT);
    t->SetBranchAddress("weight",&weight);
    t->SetBranchAddress("className",className);

    TH1D* BDTG_S=new TH1D("BDTG_S","",200,-1,1);
    TH1D* BDTG_B=new TH1D("BDTG_B","",200,-1,1);
    TH1D* BDTG_significance=new TH1D("BDTG_significancei","",200,-1,1);
    // TH1D* h_signif2=new TH1D("h_signifi2","",200,-1,1);//for the so called loose category
    TH1D* BDT_S=new TH1D("BDT_S","",200,-1,1);
    TH1D* BDT_B=new TH1D("BDT_B","",200,-1,1);
    TH1D* BDT_significance=new TH1D("BDT_significance","",200,-1,1);

    

    for(int i=0;i<t->GetEntries();i++){
        t->GetEntry(i);
        if(strcmp(className,"Signal")==0) {
            BDTG_S->Fill(BDTG,weight);
            BDT_S->Fill(BDT,weight);
        }
        else {
            BDTG_B->Fill(BDTG,weight);
            BDT_B->Fill(BDT,weight);
        }
        //???how to understand this weight?
    }
    // BDTG_S->Draw();
    // BDTG_B->Draw("same");
    cout<<"entries in testTree: "<<t->GetEntries()<<endl;
    cout<<"BDTG_S_entries = "<<BDTG_S->GetEntries()<<endl;
    // cout<<"BDTG_binNum = "<<BDTG_S->GetNbinsX()<<endl;
    cout<<"BDTG_S_integral = "<<BDTG_S->Integral()<<endl;
    cout<<"BDTG_S_integral*binWidth = "<<BDTG_S->Integral()*0.01<<endl;
    cout<<"BDTG_B_entries = "<<BDTG_B->GetEntries()<<endl;

    //53854 entries for testTree
    cout<<"total"<<endl;
    cout<<"signal : "<<BDTG_S->Integral()/0.4<<endl;
    cout<<"background : "<<BDTG_B->Integral()/0.4<<endl;

    //calculate significance
    for(int i=0;i<200;i++){
        float signal=BDTG_S->Integral(i,200);//Return integral of bin contents in range [binx1,binx2].
        float background=BDTG_B->Integral(i,200);
        float sig = TMath::Sqrt(2*((signal+background)*log(1+signal/background)-signal));
        if ( signal>0 && background>0 ) BDTG_significance->SetBinContent(i, sig/TMath::Sqrt(0.4));


        Float_t s_BDT = BDT_S->Integral(i,200);
        Float_t b_BDT = BDT_B->Integral(i,200);
        Float_t sig_BDT = TMath::Sqrt(2*((s_BDT+b_BDT)*log(1+s_BDT/b_BDT)-s_BDT));
        cout<<i<<":"<<sig_BDT<<"  ";
        // if (!isnan(sig) && !isinf(sig) ) BDTG_significance->SetBinContent(i, sig/TMath::Sqrt(0.4));
        // if( !isnan(sig_BDT)&&!isinf(sig_BDT) ) BDT_significance->SetBinContent(i, sig_BDT/TMath::Sqrt(0.4));
        if( s_BDT>0 && b_BDT>0 ) BDT_significance->SetBinContent(i, sig_BDT/TMath::Sqrt(0.4));
        // BDTG_significance->SetBinContent(i,TMath::Sqrt(2*((signal+background)*log(1+signal/background)-signal)));
     }
    BDTG_significance->SetMaximum(0.5);
    // BDTG_significance->Draw("same");
    BDTG_significance->Draw();

    BDT_significance->Print();
    BDT_significance->Draw("same");

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
      // Int_t maxbin = info->sSig->GetMaximumBin();
      // info->line1 = tl.DrawLatex( 0.15, 0.23, Form("For %1.0f signal and %1.0f background", fNSignal, fNBackground));
      // tl.DrawLatex( 0.15, 0.19, "events the maximum "+GetLatexFormula()+" is");
      tl.DrawLatex( 0.15, 0.19, Form("maximum significance is %f when cutting at %f ", maximumSig, bestCut)  );

  //loose category
  //???what is the point of this loose category
  // for(int i=0;i<BDTG_significance->GetMaximumBin();i++)
    // {
    // float signal=BDTG_S->Integral(i,BDTG_significance->GetMaximumBin());
    // float background=BDTG_B->Integral(i,BDTG_significance->GetMaximumBin());
    // if(signal<0||background<0) continue;
    // h_signif2->SetBinContent(i,TMath::Sqrt(2*((signal+background)*log(1+signal/background)-signal)));
    // }

  // h_signif2->Draw("same");

  // cout<<"loose category"<<endl;
  // cout<<"best cut : "<<h_signif2->GetMaximumBin()<<endl;
  // cout<<"signal : "<<BDTG_S->Integral(h_signif2->GetMaximumBin(),BDTG_significance->GetMaximumBin())/0.3<<endl;
  // cout<<"background : "<<BDTG_B->Integral(h_signif2->GetMaximumBin(),BDTG_significance->GetMaximumBin())/0.3<<endl;
  // cout<<"significance : "<<h_signif2->GetBinContent(h_signif2->GetMaximumBin())/TMath::Sqrt(0.3)<<endl;




    
}
