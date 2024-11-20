#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TStopwatch.h"
#include "TString.h"

#include "../include/objectSelectionNano.h"
#include "../../myLibrary/commenFunction.h"

void run_objectSelection(
    TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/ttG/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/ZGToLLG/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/ttbar_2l/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/ttbar_0l/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/TTWJetsToLNu/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/data/jetHT_2017c/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/data/jetHT_2017d/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/data/jetHT_2017b/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/data/singleMu_2017b/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/data/MuonEG_2017f/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/data/singleMu_2016F/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/data/BTagCSV_2017c/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/data/jetHT_2018a/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/data/doubleMu_2018a/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/data/MuonEG_2018a/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/VLL_EE_M600/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/VLL_EN_M800/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/data/MuonEG_2016f/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/data/singleE_2016G/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016APV/data/singleE_2016B_v2/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016APV/data/singleE_2016D/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/data/MuonEG_2016h/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/data/MuonEG_2016h/",
    // TString singleFileName = "outTree_2.root",
    // TString singleFileName = "01D97507-B0BB-234F-A28E-6AD66C3499E9.root",//2018 tttt
    TString singleFileName = "02151677-7D45-7940-803F-3FA5A101D504.root",//2017, tttt
    // TString singleFileName = "0BF1CAC0-066F-6C41-89EF-6F7B67A8E1D7.root",
    // TString singleFileName = "NanoAODv9_10.root",
    // TString singleFileName = "tree_1.root", // run3, output of nanoAOD tool
    TString outputDir = "./output/",
    Int_t eventNum = 1000)
// Int_t eventNum = 10000)
// Int_t eventNum = 0)
{
    TStopwatch t;
    t.Start();
    std::cout<<"input file="<<inputDir<<singleFileName<<"\n";

    Bool_t isData = TTTT::getIsData(inputDir);
    TString era = TTTT::getEra(inputDir);
    const Bool_t isRun3 = TTTT::isRun3(era);
    if(eventNum >0) {
        outputDir = outputDir + era + "/";
    }
    TString temp = inputDir(0, inputDir.Last('/'));
    TString m_processName = temp(temp.Last('/')+1, temp.Length()-temp.Last('/'));

    const UChar_t eleScale = 0;
    const UChar_t eleSmear = 0;
    // const UChar_t JESSys = 0;
    const UChar_t JESSys = 2; //norminal
    const UChar_t JERSys = 0; //norminal
    const Int_t JESSysUncerType = 26; // In range 0-26
    // const UChar_t TES = 3; //no correction
    const UChar_t TES = 0; //no correction
    // const Bool_t if1tau2l = kTRUE;//!
    const Bool_t if1tau2l = kFALSE;//!
    std::cout << "eleScale=" << static_cast<unsigned int>(eleScale) << " eleSmear=" << static_cast<unsigned int>(eleSmear) << " JESSys=" << static_cast<unsigned int>(JESSys) << " JESSysUncerType=" << JESSysUncerType<< " TES=" << static_cast<unsigned int>(TES) <<" JERSys="<<static_cast<unsigned int>(JERSys)<< "\n\n";
    objectSelection os(inputDir, singleFileName, outputDir, isData, era, m_processName, isRun3, kTRUE, eleScale, eleSmear, JESSys, JERSys, JESSysUncerType, TES, if1tau2l);

    // const Bool_t tauSel = kFALSE; //for HLT
    const Bool_t tauSel = kTRUE;
    // const Bool_t HLTSel = kFALSE;
    const Bool_t HLTSel = kTRUE;
    os.EventLoop(tauSel, kTRUE, HLTSel, eventNum); // preselection
    // os.EventLoop(tauSel, kFALSE, HLTSel, eventNum); //no selection

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