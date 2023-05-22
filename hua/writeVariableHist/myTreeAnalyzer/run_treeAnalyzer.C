#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TStopwatch.h"

#include "treeAnalyzer.h"
#include "functions.h"

void run_treeAnalyzer(
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/",
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/",
    TString process = "tttt",
    TString histVersion = "v0_test",
    Bool_t isTest = kTRUE)
{

    TStopwatch t;
    t.Start();
    treeAnalyzer writeBDTHist(inputDir, process, histVersion, isTest);
    writeBDTHist.Init();
    writeBDTHist.LoopTree(); //!!!maybe provide cut and weight as parameter here
    writeBDTHist.Terminate();

    t.Stop();
    t.Print();
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
        run_treeAnalyzer();
    }
    else
    {
        std::cout << "using input from command line\n";
        inputDir = boost::lexical_cast<std::string>(argv[1]);
        inputProcess = boost::lexical_cast<std::string>(argv[2]);
        version = boost::lexical_cast<std::string>(argv[3]);
        isTest = boost::lexical_cast<Bool_t>(argv[4]);
        run_treeAnalyzer(inputDir, inputProcess, version, isTest);
    }

    return 0;
}