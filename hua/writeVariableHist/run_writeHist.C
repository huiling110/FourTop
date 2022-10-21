#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TStopwatch.h"

#include <iostream>

void run_writeHist(
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noBaseline_v25noJERNOTES/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noBaseline_v26noJERNOTESwithSorting/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noBaseline_v27noJERnoTESWithObjectRemoval/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noBaseline_v27noJERnoTESWithObjectRemoval/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0noBaseline_v27noJERnoTESWithObjectRemoval/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1noBaselineModifiedDouble_t_v27noJERnoTESWithObjectRemoval/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noBaseline_v28JERTESBack/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0noBaseline_v29LorentzProblemSolvedNoJERnoTES/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baseline_v29LorentzProblemSolvedNoJERnoTES/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0noBaseline_v29LorentzProblemSolvedNoJERnoTES/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noBaseline_v30TESnoJER/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baseline_v33TESnoJERCodeOptimzation/mc/",
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v38TESandJERTauPt20_preselection/data/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v36TESandJERByHuiling/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baseline_v36TESandJERByHuiling/mc/",
    // TString inputProcess = "ttbar_0l",
    // TString inputProcess = "qcd_500to700",
    // TString inputProcess = "tttt",
    // TString inputProcess = 'WJetsToLNu_HT-600To800',
    // TString inputProcess = "WJetsToLNu_HT-400To600",
    TString inputProcess = "jetHT_2016C",
    TString version = "test",
    // TString version = "forCutflow",
    Bool_t isTest = kTRUE,
    // TString selector = "writeHist_fordataMC.C+"
    // TString selector = "writeHist.C+"
    TString selector = "writeHist_forFakeRate.C+")
{
    using namespace std;
    TString inputFile = inputDir + inputProcess + ".root";

    Bool_t isData = kFALSE;
    if (inputDir.Contains("data"))
    {
        isData = kTRUE;
    }

    // get genWeightSumInitial for the process
    Double_t genWeightSumInitial = 1.0;
    TFile *m_file = new TFile(inputFile, "READ");
    if (!isData)
    {
        TTree *Runs = (TTree *)m_file->Get("Runs");
        Double_t igen;
        Runs->SetBranchAddress("genEventSumw", &igen);
        genWeightSumInitial = 0.0;
        for (int iEntry = 0; Runs->LoadTree(iEntry) >= 0; ++iEntry)
        {
            Runs->GetEntry(iEntry);
            genWeightSumInitial += igen;
        }
        // TH1D *h_genWeight = new TH1D("genWeight", "genWeight", 100, -100., 100.);
        // alleventTree->Project("genWeight", "genWeight_allEvents");
        // h_genWeight->StatOverflows(kTRUE);
        // genWeightSumInitial = h_genWeight->GetMean() * h_genWeight->GetEntries();
    }
    m_file->Close();
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

    // chain.Process(selector, option);
    chain.Process(selector, option, 100);

    t.Stop();
    t.Print();
}