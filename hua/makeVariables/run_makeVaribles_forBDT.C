
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include <iostream>
#include <boost/lexical_cast.hpp>

void run_makeVaribles_forBDT(
    Bool_t istest = true,
    // Bool_t istest = false,
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v46addPOGIDL/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v49FixedPileUpNoJERTES/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v51TESNewLepObjectRemovalCorrected/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v52noHLTSelection/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v52noHLTButPreSelection/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v55ojectRemovalwithTight/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v54noHLTButPre/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v56NoHLTButPre/mc/",
    TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v57ovelapWithTausF/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v56preselection/mc/",
    TString inputDir = "tttt",
    // TString inputDir = "qcd_100to200",
    // TString inputDir = "jetHT_2016F",
    // TString inputDir = "singleMu_2016F",
    // TString inputDir = "ttbar_1l",
    TString outputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/cutflowCheck/",
    // const TString eventSelectionBit = "0",
    const TString eventSelectionBit = "6",
    // const TString eventSelectionBit = "4",
    Bool_t ifOneSample = kFALSE,
    // Bool_t ifOneSample = kTRUE,
    TString singleSampleName = "outTree_5"
    // 1 for MetFilters, 2 for HLTSelection, 4 for baseline. so 7 if all selection; 0 if no selection
)
{
    // get era from inputBase
    TString sub = inputBase(inputBase.Index("NanoAOD") + 8, inputBase.Length());
    TString era = sub(0, sub.First("/"));
    std::cout << era << "\n";
    era.Remove(era.Index("UL"), 2);
    if (era.Contains("_"))
    {
        era.Remove(era.Index("_"), 1);
    }

    std::cout << "era in run: " << era << "\n";

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
    std::cout << "input file:" << inputFile << "\n";

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

    std::cout << "entries in tree: " << chain.GetEntries() << "\n";

    // TString selection = "makeVaribles_forBDT.C";
    TString selection = "makeVaribles_forBDT";

    TString option = outputDir + ":" + inputDir + ":" + era + ":" + eventSelectionBit + ":";
    std::cout << "option in run: " << option << "\n";

    if (istest)
    {
        // chain.Process(selection + "+", option, 100);
        chain.Process(selection + "+", option, 1000);
        // chain.Process(selection + "+", option, 10000);
    }
    else
    {
        chain.Process(selection + "+", option);
    }

    // add Runs tree
    if (!(inputDir.Contains("jetHT") || inputDir.Contains("singleMu")))
    {
        std::cout << "--------\n";
        std::cout << "now comes to add Runs tree stage\n";
        TFile *file = TFile::Open(outputDir + inputDir + ".root", "UPDATE");
        std::cout << "file opened : " << file->GetName() << "\n";
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
        std::cout << "done merging Runs trees\n";
        // file->Close();
    }
}

int main(int argc, char const *argv[])
{

    Bool_t istest;
    TString inputBase;
    TString inputDir;
    TString outputDir;
    TString eventSelectionBit;
    // TString ifOneSample;
    // TString singleSampleName;
    if (argc < 5)
    {
        std::cout << "not enough input from command line\n";
        run_makeVaribles_forBDT();
    }
    else
    {
        istest = boost::lexical_cast<bool>(argv[1]);
        inputBase = boost::lexical_cast<std::string>(argv[2]);
        inputDir = boost::lexical_cast<std::string>(argv[3]);
        outputDir = boost::lexical_cast<std::string>(argv[4]);
        eventSelectionBit = boost::lexical_cast<std::string>(argv[5]);
        printf("istest=%i \n inputBase=%s \ninputDir=%s\n  outputDir = %s\n eventSelectionBit=%s\n ", istest, inputBase.Data(), inputDir.Data(), outputDir.Data(), eventSelectionBit.Data());
        // run_makeVaribles_forBDT(istest, inputBase, inputDir, outputDir, eventSelectionBit, ifOneSample, singleSampleName);
        run_makeVaribles_forBDT(istest, inputBase, inputDir, outputDir, eventSelectionBit);
    }

    return 0;
}