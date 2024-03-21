#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TStopwatch.h"
#include "TString.h"

#include "../include/objectSelectionNano.h"
#include "../../myLibrary/commenFunction.h"

void run_objectSelection(
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/wz/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/data/jetHT_2017c/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/data/jetHT_2018b/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022preEE_v3/mc/TTTT/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022postEE_v3/mc/TTTT/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022postEE_v3/mc/TTtoLNu2Q/",
    TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022postEE_v3/mc/TTto2L2Nu/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022postEE_v3/mc/TTto4Q/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022postEE_v3/data/JetMET2022F/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022preEE_v3/data/JetMET2022D/",
    // TString singleFileName = "outTree_0.root",
    TString singleFileName = "tree_1.root", // run3, output of nanoAOD tool
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2022/",
    // TString singleFileName = "0182c6a5-2284-4d01-9af9-b31cf5d0cd07.root",
    TString outputDir = "./output/",
    // Int_t eventNum = 1000)
Int_t eventNum = 10000)
// Int_t eventNum = 0)
{
    TStopwatch t;
    t.Start();

    Bool_t isData = TTTT::getIsData(inputDir);
    TString era = TTTT::getEra(inputDir);
    const Bool_t isRun3 = TTTT::isRun3(era);
    if(eventNum >0) {
        outputDir = outputDir + era + "/";
    }
    TString temp = inputDir(0, inputDir.Last('/'));
    TString m_processName = temp(temp.Last('/')+1, temp.Length()-temp.Last('/'));

    const UChar_t eleScale = 3;
    const UChar_t eleSmear = 3;
    const UChar_t JESSys = 3;
    objectSelection os(inputDir, singleFileName, outputDir, isData, era, m_processName, isRun3, kTRUE, eleScale, eleSmear, JESSys);

    Int_t JER = 3; //0 : JER nominal
    // Int_t JER = 2; 
    // Int_t JER = 1;
    Int_t JES = 3;
    // Int_t JES = 1;//up
    // Int_t JES = 2;//down
    // Int_t TES = 0; //0: nominal
    // Int_t TES = 1;//up
    // Int_t TES = 2; //down
    Int_t TES = 3; //
    // os.EventLoop(kTRUE, kFALSE, eventNum, TES, JER, JES); //no HLT selection, for HLT study
    // os.EventLoop(kTRUE, kTRUE, eventNum, TES, JER, JES); //with HLT and preselection
    os.EventLoop(kTRUE, kTRUE, eventNum, TES, JER, JES); //with HLT and preselection
    // os.EventLoop(kFALSE, kFALSE, eventNum, TES, JER); //no selection

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