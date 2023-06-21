#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TStopwatch.h"
#include "TString.h"
#include "TChain.h"

#include "../include/makeVariablesMain.h"
// #include "../include/usefulFunc.h"

void run_objectSelection(
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v58addGenBranches/mc/",
    // TString inputDir = "ttZ",
    // TString inputBase = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelectionOptimized/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/Prompt2022/v0Testing/mc/",
    // TString inputDir = "TTto2L2Nu",
    TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/Prompt2022/v0Testing/data/",
    TString inputDir = "JetMET_G",
    // TString inputDir = "output",
    // TString outputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/cutflowCheck/",
    TString outputDir = "output/",
    Int_t numEntries = 1000)
{
    TStopwatch t;
    t.Start();

    TString inputDir1 = inputBase + inputDir + "/";
    TChain *chain = new TChain("tree");
    chain->Add(inputDir1 + "outTree*.root");
    // chain->Add(inputDir1 + "outTree_0.root");
    std::cout << "all entries in chain: " << chain->GetEntries() << "\n";
    std::cout << "all trees in chain: " << chain->GetNtrees() << "\n";
    TString processName = inputDir;
    MakeVariablesMain mv(inputDir1, chain, outputDir, processName);
    mv.EventLoop(kTRUE, numEntries);
    mv.Terminate();

    t.Stop();
    t.Print();
    return;
}

int main(int argc, char const *argv[])
{
    TString inputDir;
    TString inputProcess;
    TString outputDir;
    Int_t numEntries = 0;
    if (argc < 4)
    {
        std::cout << "not enough input from command line\n";
        run_objectSelection();
    }
    else
    {
        std::cout << "using input from command line\n";
        inputDir = boost::lexical_cast<std::string>(argv[1]);
        inputProcess = boost::lexical_cast<std::string>(argv[2]);
        outputDir = boost::lexical_cast<std::string>(argv[3]);
        numEntries = boost::lexical_cast<Int_t>(argv[4]);
        run_objectSelection( inputDir, inputProcess, outputDir, numEntries);
    }

    return 0;
}