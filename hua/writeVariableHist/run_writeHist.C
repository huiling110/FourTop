#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TStopwatch.h"

#include <iostream>

#include "../src_cpp/usefulFuction.h"

void run_writeHist(
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_v41addVertexSelection/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v9addBtagWeight_v42fixedChargeType/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v9addBtagWeight_v42fixedChargeType/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v10addPV_npvsGood_baseline_v42fixedChargeType/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v44addSSLeptons/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v45newLepBugFixed/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v46addPOGIDL/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1AddTOPLepVariables_v46addPOGIDL/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1AddTOPLepVariables_v49FixedPileUpNoJERTES/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1AddTOPLepVariables_v49FixedPileUpJERAndTES/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v2aadTopLepWeight_v49FixedPileUpJERAndTES/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v3addjetBtagVar_v49FixedPileUpOnlyJER/mc/",
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v3addjetBtagVar_v50switchRawPtJERNoTES/mc/",
    // TString inputProcess = "ttbar_0l",
    // TString inputProcess = "qcd_500to700",
    TString inputProcess = "tttt",
    // TString inputProcess = "wz",
    // TString inputProcess = 'WJetsToLNu_HT-600To800',
    // TString inputProcess = "jetHT_2016C",
    TString version = "test",
    // TString version = "forCutflow",
    Bool_t isTest = kTRUE,
    TString selector = "writeHist_fordataMC.C+" // 1tau1l)
    // TString selector = "writeHist_forFakeRate.C+" // 1tau0l
    // TString selector = "writeHist_forFakeRate_3etaBin.C+" // 1tau0l
    // TString selector = "writeHist_forBtagRCal.C+"
)
{
    using namespace std;
    TString inputFile = inputDir + inputProcess + ".root";
    std::cout << "input file: " << inputFile << "\n";

    Bool_t isData = kFALSE;
    if (inputDir.Contains("data"))
    {
        isData = kTRUE;
    }

    // get genWeightSumInitial for the process
    Double_t genWeightSumInitial = 1.0;
    if (!isData)
    {
        genWeightSumInitial = getGenSum(inputFile);
    }
    std::cout << inputProcess << ": "
              << "genWeightSumInitial: " << genWeightSumInitial << "\n";

    // get era
    TString temp = inputDir(inputDir.Index("forMVA/") + 7, inputDir.Sizeof());
    // std::cout<<temp<<"\n";
    TString era = temp(0, temp.First("/"));
    std::cout << "era: " << era << "\n";

    TChain chain("newtree");
    chain.Add(inputFile);

    TString sumGenWeight = std::to_string(genWeightSumInitial);
    // TString option = inputDir + ":" + inputProcess + ":" + isData + ":" + version + ":" + era + ":";
    TString option = sumGenWeight + ":" + inputDir + ":" + inputProcess + ":" + isData + ":" + version + ":" + era + ":";
    std::cout << "option in run_writeHist: " << option << "\n";

    TStopwatch t;
    t.Start();

    // what if the chain is empty? it seems the selector it not run at all theu
    // chain.Print();
    std::cout << "entires in chain: " << chain.GetEntries() << "\n";
    chain.Process(selector, option);
    // chain.Process(selector, option, 100);

    t.Stop();
    t.Print();
}