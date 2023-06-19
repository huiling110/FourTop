#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TStopwatch.h"
#include "TString.h"

#include "../include/objectSelectionNano.h"
#include "../include/usefulFunc.h"

void run_objectSelection(
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/ttbar_2l/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/ttbar_1l/",
    TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/13p6TeV/2022/mc/TTtoLNu2Q/",
    TString singleFileName = "outTree_0.root",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2022/",
    // TString singleFileName = "0182c6a5-2284-4d01-9af9-b31cf5d0cd07.root",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/data/jetHT_2017c/",
    TString outputDir = "./output/",
    Bool_t istest = kTRUE)
{
    TStopwatch t;
    t.Start();


    Bool_t isData = getIsData(inputDir);
    TString era = getEra(inputDir);
    objectSelection os(inputDir, singleFileName, outputDir, isData, era, kTRUE);
    // os.EventLoop(kTRUE, 5000);
    os.EventLoop(kTRUE, 1000);
    os.Terminate();

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

    //!!!all events tree

    return 0;
}