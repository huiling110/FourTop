#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TStopwatch.h"
#include "TString.h"

#include "../include/objectSelectionNano.h"
#include "../../myLibrary/commenFunction.h"

void run_objectSelection(
    TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/ttbar_2l/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/ttbar_1l/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/ttbar_0l/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/13p6TeV/2022/mc/TTtoLNu2Q/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/13p6TeV/2022/mc/TTto4Q/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/data/jetHT_2017c/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/NanoPost/mc/TTto4Q/",
    // TString singleFileName = "outTree_30.root",
    TString singleFileName = "outTree_0.root",
    // TString singleFileName = "tree_1.root",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2022/",
    // TString singleFileName = "0182c6a5-2284-4d01-9af9-b31cf5d0cd07.root",
    TString outputDir = "./output/",
    // Int_t eventNum = 5000)
    Int_t eventNum = 30)
// Int_t eventNum = 0)
// Bool_t istest = kTRUE)
{
    TStopwatch t;
    t.Start();

    Bool_t isData = TTTT::getIsData(inputDir);
    TString era = TTTT::getEra(inputDir);
    const Bool_t isRun3 = TTTT::isRun3(era);
    objectSelection os(inputDir, singleFileName, outputDir, isData, era, isRun3, kTRUE);
    // os.EventLoop(kTRUE, eventNum);
    os.EventLoop(kFALSE, eventNum);
    os.Terminate();

    t.Stop();
    t.Print();
    return;
}

int main(int argc, char const *argv[])
{
    TString inputDir;
    TString singleFileName;
    TString outputDir;
    Int_t eventNum = 0;
    if (argc < 4)
    {
        std::cout << "not enough input from command line\n";
        run_objectSelection();
    }
    else
    {
        std::cout << "using input from command line\n";
        inputDir = boost::lexical_cast<std::string>(argv[1]);
        singleFileName = boost::lexical_cast<std::string>(argv[2]);
        outputDir = boost::lexical_cast<std::string>(argv[3]);
        eventNum = boost::lexical_cast<Int_t>(argv[4]);
        run_objectSelection(inputDir, singleFileName, outputDir, eventNum);
    }

    return 0;
}