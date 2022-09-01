
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
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v18HLTSelection/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v19HLTSelection/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v20FixedSelectJetsBug/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v22addedRunsTree/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v24noJER/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v25noJERNOTES/mc/",
    TString inputBase = " /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/crossCheck_noOverlap/",
    // TString inputBase = "../../objectSelection/",

    TString inputDir = "tttt",
    // TString inputDir = "qcd_100to200",
    // TString inputDir = "jetHT_2016D",
    // TString inputDir = "ttbar_0l",
    TString outputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/",
    // const TString eventSelectionBit = "7"
    const TString eventSelectionBit = "3"
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

    chain.Add(inputFile + "outTree*.root");
    cout << "entries in tree: " << chain.GetEntries() << endl;

    // TString selection = "makeVaribles_forBDT.C";
    TString selection = "makeVaribles_forBDT";

    TString option = outputDir + ":" + inputDir + ":" + era + ":" + eventSelectionBit + ":";
    cout << "option in run: " << option << "\n";

    if (istest)
    {
        chain.Process(selection + "+", option, 100);
        // chain.Process(selection + "+", option, 10000);
        // chain.Process(selection + "+", option);
    }
    else
        chain.Process(selection + "+", option);

    cout << "--------" << endl;
    cout << "now comes to add Runs tree stage\n";
    TFile *file = TFile::Open(outputDir + inputDir + ".root", "UPDATE");
    cout << "file opened :" << file->GetName() << "\n";

    // add Runs tree
    TChain chain2("Runs");
    chain2.Add(inputFile + "outTree*.root");
    // chain2.Add(inputFile + "outTree_4.root");
    chain2.Merge(file, 2000);
    cout << "done merging Runs trees\n";
}
