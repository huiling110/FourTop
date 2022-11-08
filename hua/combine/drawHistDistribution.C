/**
 * @author Huiling Hua
 * @email huahl@ihep.ac.cn
 * @create date 2022-11-09 03:18:58
 * @modify date 2022-11-09 03:18:58
 * @desc [description]
 */

void drawHistDistribution(
    // TString inputFile = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/2tau0l_HT/11bins/dataDriven_2tau0l_forCombine.root"
    // TString inputFile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau0l_HT/dataDriven_1tau0l_forCombine.root"
    // TString inputFile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/2tau1l_HT/HT_2tau1l_forCombine.root"
    // TString inputFile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_20bins/TMVApp_1tau1l_10var_forCombine.root"
    TString inputAppDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/AppResults_30bins/",
    TString appFile = "TMVApp_1tau1l_10var_forCombine.root")
{
    TString inputFile = inputAppDir + appFile;
    Bool_t isMVA = false;
    if (inputFile.Contains("App"))
        isMVA = true;

    TFile *input = new TFile(inputFile, "Read");

    TString histPost = "_HT";
    if (isMVA)
        histPost = "_MVA_BDT";
    // TH1D *TTTT = (TH1D *)input->Get("TTTT" + histPost);
    TH1D *TTTT = (TH1D *)input->Get("tttt" + histPost);
    // TTTT->Scale(1 / TTTT->Integral());
    TTTT->Scale(100);
    TTTT->SetLineColor(kRed);
    TTTT->SetMaximum(0.4);
    TH1D *allBgs = (TH1D *)input->Get("allBgs" + histPost);
    // allBgs->Scale(1 / allBgs->Integral());

    TCanvas *c1 = new TCanvas("c1", "HT distribution");
    if (isMVA)
    {
        TTTT->SetName("BDT distribution");
    }
    allBgs->Draw();
    TTTT->Draw("same");

    TString outFileName;
    if (!isMVA)
    {
        outFileName = inputFile.ReplaceAll(".root", "_HTshape.png");
    }
    else
    {
        // outFileName = inputFile.ReplaceAll(".root", "_BDTshape.png");
        outFileName = appFile.ReplaceAll(".root", "_BDTTemplates.png");
        outFileName = inputAppDir + "results/" + outFileName;
    }
    c1->SaveAs(outFileName);
    cout << "plots saved here: " << outFileName << "\n";
}