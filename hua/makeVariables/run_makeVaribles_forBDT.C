
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include <iostream>

// int main(int argc, char const *argv[])
// {
//     /* code */
//     run_makeVaribles_forBDT();
//     return 0;
// }

void run_makeVaribles_forBDT(
    Bool_t istest = true,
    // Bool_t istest = false,
    // TString inputBase = " /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v29LorentzProblemSolvedNoJERnoTES/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v30TESnoJER/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v27noJERnoTESWithObjectRemoval/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v32TESnoJER/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v33TESnoJERCodeOptimzation/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v36TESandJERByHuiling/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v38TESandJERTauPt20_preselection/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v39addTauBranches/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v40addTauJetEtau/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v40addTauJetEtau/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v41addVertexSelection/mc/",
    TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v42fixedChargeType/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v41addVertexSelection/mc/",
    // TString inputBase = "/scratchfs/cms/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v40addTauJetEtau/mc/",
    // TString inputBase = "/scratchfs/cms/huahuil/tauOfTTTT_NanoAOD/UL2017/v42fixedChargeType/mc/",

    TString inputDir = "tttt",
    // TString inputDir = "qcd_100to200",
    // TString inputDir = "jetHT_2016F",
    // TString inputDir = "ttbar_0l",
    TString outputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/cutflowCheck/",
    const TString eventSelectionBit = "7",
    // const TString eventSelectionBit = "3",
    Bool_t ifOneSample = kFALSE,
    // Bool_t ifOneSample = kTRUE,
    TString singleSampleName = "outTree_5"
    // 1 for MetFilters, 2 for HLTSelection, 4 for baseline. so 7 if all selection; 0 if no selection
)
{
    // get era from inputBase
    TString sub = inputBase(inputBase.Index("NanoAOD") + 8, inputBase.Length());
    TString era = sub(0, sub.First("/"));
    cout << era << "\n";
    era.Remove(era.Index("UL"), 2);
    era.Remove(era.Index("_"), 1);
    cout << "era in run: " << era << "\n";

    gROOT->ProcessLine(".L makeVaribles_forBDT.so");

    Bool_t ifMergeAllevent = false;
    if (!istest)
    {
        ifMergeAllevent = true;
    }
    else
    {
        outputDir = "output/";
    }

    TString inputFile = inputBase + inputDir + "/";
    cout << "input file:" << inputFile << endl;

    TChain chain("tree");
    if (ifOneSample)
    {
        chain.Add(inputFile + singleSampleName + ".root");
        inputDir = singleSampleName;
    }
    else
    {
        chain.Add(inputFile + "outTree*.root");
    }

    cout << "entries in tree: " << chain.GetEntries() << endl;

    // TString selection = "makeVaribles_forBDT.C";
    TString selection = "makeVaribles_forBDT";

    TString option = outputDir + ":" + inputDir + ":" + era + ":" + eventSelectionBit + ":";
    cout << "option in run: " << option << "\n";

    if (istest)
    {
        chain.Process(selection + "+", option, 1000);
        // chain.Process(selection + "+", option, 10000);
    }
    else
    {
        chain.Process(selection + "+", option);
    }

    // add Runs tree
    if (!inputDir.Contains("jetHT"))
    {
        cout << "--------" << endl;
        cout << "now comes to add Runs tree stage\n";
        TFile *file = TFile::Open(outputDir + inputDir + ".root", "UPDATE");
        cout << "file opened :" << file->GetName() << "\n";
        TChain chain2("Runs");
        if (ifOneSample)
        {
            chain2.Add(inputFile + singleSampleName + ".root");
        }
        else
        {
            chain2.Add(inputFile + "outTree*.root");
        }
        chain2.Merge(file, 2000);
        cout << "done merging Runs trees\n";
    }
}
