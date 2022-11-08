
void drawHistDistribution(
    // TString inputFile = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/2tau0l_HT/11bins/dataDriven_2tau0l_forCombine.root"
    // TString inputFile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau0l_HT/dataDriven_1tau0l_forCombine.root"
    // TString inputFile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/2tau1l_HT/HT_2tau1l_forCombine.root"
    TString inputFile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_20bins/TMVApp_1tau1l_10var_forCombine.root")
{
    Bool_t isMVA = false;
    if (inputFile.Comtains("App"))
        isMVA = true;

    TFile *input = new TFile(inputFile, "Read");

    TString histPost = "_HT";
    if (isMVA)
        histPost = "_MVA_BDT";
    // TH1D *TTTT = (TH1D *)input->Get("TTTT" + histPost);
    TH1D *TTTT = (TH1D *)input->Get("tttt" + histPost);
    TTTT->Scale(1 / TTTT->Integral());
    TTTT->SetLineColor(kRed);
    TTTT->SetMaximum(0.4);
    TH1D *allBgs = (TH1D *)input->Get("allBgs" + histPost);
    allBgs->Scale(1 / allBgs->Integral());

    TCanvas *c1 = new TCanvas("c1", "HT distribution");
    if (isMVA)
        c1->SetTittle("BDT distribution");
    TTTT->Draw();
    allBgs->Draw("same");

    TString outFileName;
    if (!isMVA)
    {
        outFileName = inputFile.ReplaceAll(".root", "_HTshape.png");
    }
    else
    {
        outFileName = inputFile.ReplaceAll(".root", "_BDTshape.png");
    }
    c1->SaveAs(outFileName);
}