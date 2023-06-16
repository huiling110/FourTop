#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TStopwatch.h"
#include "TString.h"

#include "../include/makeVariablesMain.h"
// #include "../include/usefulFunc.h"

void run_objectSelection(
    TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v58addGenBranches/mc/",
    TString inputDir = "ttZ",
    TString outputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/cutflowCheck/",
    Bool_t istest = kTRUE)
{
    TStopwatch t;
    t.Start();

    // Bool_t isData = getIsData(inputDir);
    // TString era = getEra(inputDir);
    // objectSelection os(inputDir, singleFileName, outputDir, isData, era, kTRUE);
    // os.EventLoop(kTRUE, 5000);
    // os.Terminate();
    TString inputDir1 = inputBase + inputDir +"/";
    MakeVariablesMain mv(inputDir1);


    t.Stop();
    t.Print();
    return;
}

int main(int argc, char const *argv[])
{
    TString inputDir;
    TString inputProcess;
    TString version;
    Bool_t isTest = kFALSE;
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
        version = boost::lexical_cast<std::string>(argv[3]);
        isTest = boost::lexical_cast<Bool_t>(argv[4]);
        // run_treeAnalyzer(inputDir, inputProcess, version, isTest);
    }

    return 0;
}