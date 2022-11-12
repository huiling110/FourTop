/**
 * File              : sumBGsTogether.C
 * Author            : Huiling Hua <huahl@ihep.ac.cn>
 * Date              : 05.10.2021
 * Last Modified Date: 05.10.2021
 * Last Modified By  : Huiling Hua <huahl@ihep.ac.cn>
 */
#include "../../EYandSP_usingClass_v3.h"

TH1D *getHist(const TString histName, TFile *input, Bool_t isMVA)
{
    TH1D *temp;
    if (isMVA)
    {

        temp = (TH1D *)input->Get(histName + "_MVA_BDT");
    }
    else
    {
        temp = (TH1D *)input->Get(histName + "_HT");
    }
    temp->Sumw2();
    return temp;
}

void sumBGsTogether_Nano(
    // TString inputName = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2/1tau1l_v1/AppResults_11bins/TMVApp_1tau1l_10var_forComresubmit_bine.root"
    // TString inputName = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_20bins/TMVApp_1tau1l_10var_forCombine.root"
    TString inputName = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/AppResults_30bins/TMVApp_1tau1l_10var_forCombine.root")
{
    using std::cout;
    TFile *input = TFile::Open(inputName, "UPDATE");

    TH1::SetDefaultSumw2();
    TH1D *TTTo2L2Nu = getHist("ttbar_2l", input, true);

    Int_t binNum = TTTo2L2Nu->GetXaxis()->GetNbins();
    Double_t binMin = TTTo2L2Nu->GetXaxis()->GetXmin();
    Double_t binMax = TTTo2L2Nu->GetXaxis()->GetXmax();

    TH1D *TT_MVA_BDT = new TH1D("tt_MVA_BDT", "tt_MVA_BDT", binNum, binMin, binMax);
    TH1D *TTX_MVA_BDT = new TH1D("ttX_MVA_BDT", "ttX_MVA_BDT", binNum, binMin, binMax);
    TH1D *VV_MVA_BDT = new TH1D("VV_MVA_BDT", "VV_MVA_BDT", binNum, binMin, binMax);
    TH1D *SingleTop_MVA_BDT = new TH1D("singleTop_MVA_BDT", "singleTop_MVA_BDT", binNum, binMin, binMax);
    TH1D *QCD_MVA_BDT = new TH1D("qcd_MVA_BDT", "qcd_MVA_BDT", binNum, binMin, binMax);
    // TH1D *WJets_MVA_BDT = new TH1D("WJets_MVA_BDT", "WJets_MVA_BDT", binNum, binMin, binMax);
    TH1D *allBgs_MVA_BDT = new TH1D("allBgs_MVA_BDT", "allBgs_MVA_BDT", binNum, binMin, binMax);
    TT_MVA_BDT->Sumw2();
    TH1D *iHist;
    for (UInt_t p = 0; p < allProcesses.size(); p++)
    {
        TString iprocessName = allProcesses[p].getProcessName();
        iHist = getHist(iprocessName, input, true);
        if (p == 0)
            continue;
        if (0 < p && p < 4)
        {
            cout << "adding TT:"
                 << "\n";
            cout << "processName = " << allProcesses[p].getProcessName() << "\n";
            TT_MVA_BDT->Add(iHist, 1.0);
        }
        else if (p < 9)
        {
            cout << "addding TTX:"
                 << "\n";
            cout << "processName = " << iprocessName << "\n";
            TTX_MVA_BDT->Add(iHist, 1.0);
        }
        else if (p < 12)
        {
            cout << "adding VV:"
                 << "\n";
            cout << "processName = " << iprocessName << "\n";
            VV_MVA_BDT->Add(iHist, 1.0);
        }
        else if (p < 15)
        {
            cout << "adding SingleTop:\n";
            cout << "processName = " << iprocessName << "\n";
            SingleTop_MVA_BDT->Add(iHist, 1.0);
        }
        else
        {
            cout << "adding QCD:\n";
            cout << "processName = " << iprocessName << "\n";
            QCD_MVA_BDT->Add(iHist, 1.0);
        }
        allBgs_MVA_BDT->Add(iHist, 1.0);

        delete iHist;
    }

    TT_MVA_BDT->Print();
    VV_MVA_BDT->Print();
    SingleTop_MVA_BDT->Print();
    QCD_MVA_BDT->Print();
    allBgs_MVA_BDT->Print();

    // TFile* outfile = new TFile( )
    input->Write();
    input->Close();
}
