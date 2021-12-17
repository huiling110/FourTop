
void drawHistDistribution(
    // TString inputFile = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau0l_v1/11bins/dataDriven_1tau0l_forCombine.root"
    TString inputFile = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/2tau0l_HT/11bins/dataDriven_2tau0l_forCombine.root"
){
    TFile* input = new TFile( inputFile, "Read");
    TH1D* TTTT = (TH1D*)input->Get( "TTTT_HT");
    TTTT->Scale(  1 / TTTT->Integral() );
    TTTT->SetLineColor(kRed);
    TTTT->SetMaximum(0.4);
    TH1D *allBgs = (TH1D *)input->Get("allBgs_HT");
    allBgs->Scale(1 / allBgs->Integral());

    TCanvas *c1 = new TCanvas( "c1", "HT distribution");
    TTTT->Draw();
    allBgs->Draw("same");
    // c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau0l_v1/11bins/histPlots/HT_distribution.png");
    c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/2tau0l_HT/11bins/histPlots/HT_distribution.png");
}