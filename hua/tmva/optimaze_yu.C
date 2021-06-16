void optimaze_yu()
{
  // TString fileName="1tau1e_step4RemoveCorrelation75.root";
  TString fileName="/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v1HT400Cut_v44_fixedSingJetHLTBugAndAddHLTcut/1tau1mu_step1_40variables.root";
  TFile* f=new TFile(fileName);
  TTree* t=(TTree*)f->Get("dataset/TestTree");
  float BDTG, weight;
  char className[11];


  t->SetBranchAddress("BDTG",&BDTG);
  t->SetBranchAddress("weight",&weight);
  t->SetBranchAddress("className",className);

  TH1D* h_signal=new TH1D("h_signal","",200,-1,1);
  TH1D* h_bkg=new TH1D("h_bkg","",200,-1,1);
  TH1D* h_signif=new TH1D("h_signifi","",200,-1,1);
  TH1D* h_signif2=new TH1D("h_signifi2","",200,-1,1);

  

  for(int i=0;i<t->GetEntries();i++)
    {
    t->GetEntry(i);
    if(strcmp(className,"Signal")==0) h_signal->Fill(BDTG,weight);
    else h_bkg->Fill(BDTG,weight);
    //???how to understand this weight?
    }
  h_signal->Draw();
  // h_bkg->Draw("same");
  cout<<"entries in testTree: "<<t->GetEntries()<<endl;
  cout<<"BDTG_S_entries = "<<h_signal->GetEntries()<<endl;
  // cout<<"BDTG_binNum = "<<h_signal->GetNbinsX()<<endl;
  cout<<"BDTG_S_integral = "<<h_signal->Integral()<<endl;
  cout<<"BDTG_S_integral*binWidth = "<<h_signal->Integral()*0.01<<endl;
  cout<<"BDTG_B_entries = "<<h_bkg->GetEntries()<<endl;

  //53854 entries for testTree
  cout<<"total"<<endl;
  cout<<"signal : "<<h_signal->Integral()/0.3<<endl;
  cout<<"background : "<<h_bkg->Integral()/0.3<<endl;

  for(int i=0;i<200;i++)
    {
    float signal=h_signal->Integral(i,200);//Return integral of bin contents in range [binx1,binx2].
    float background=h_bkg->Integral(i,200);
    if(signal<0||background<0) continue;
    h_signif->SetBinContent(i,TMath::Sqrt(2*((signal+background)*log(1+signal/background)-signal)));
              // Bool_t useTMVAStyle = kTRUE, TString formula="sqrt(2*((S+B)*log(1+S/B)-S))" )
    }
    h_signif->SetMaximum(1);
    // h_signif->Draw();


  cout<<"tight category"<<endl;
  cout<<"best cut : "<<h_signif->GetMaximumBin()<<endl;
  cout<<"signal : "<<h_signal->Integral(h_signif->GetMaximumBin(),200)/0.3<<endl;
  cout<<"background : "<<h_bkg->Integral(h_signif->GetMaximumBin(),200)/0.3<<endl;
  cout<<"significance : "<<h_signif->GetBinContent(h_signif->GetMaximumBin())/TMath::Sqrt(0.3)<<endl;

  for(int i=0;i<h_signif->GetMaximumBin();i++)
    {
    float signal=h_signal->Integral(i,h_signif->GetMaximumBin());
    float background=h_bkg->Integral(i,h_signif->GetMaximumBin());
    if(signal<0||background<0) continue;
    h_signif2->SetBinContent(i,TMath::Sqrt(2*((signal+background)*log(1+signal/background)-signal)));
    }

  h_signif2->Draw("same");

  cout<<"loose category"<<endl;
  cout<<"best cut : "<<h_signif2->GetMaximumBin()<<endl;
  cout<<"signal : "<<h_signal->Integral(h_signif2->GetMaximumBin(),h_signif->GetMaximumBin())/0.3<<endl;
  cout<<"background : "<<h_bkg->Integral(h_signif2->GetMaximumBin(),h_signif->GetMaximumBin())/0.3<<endl;
  cout<<"significance : "<<h_signif2->GetBinContent(h_signif2->GetMaximumBin())/TMath::Sqrt(0.3)<<endl;




    
}
