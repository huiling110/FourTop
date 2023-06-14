#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TString.h"
#include "TChain.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TFile.h"

void run_objectTSelectorForNanoAOD(
    Bool_t istest = true,
    // Bool_t istest = false,
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/tttt/",
    TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/ttbar_2l/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/data/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/tttt/",
    // TString inputDir = "/scratchfs/cms/huahuil/tauOfTTTT_NanoAOD/nanoAOD/2018/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016APV/mc/tttt/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016APV/data/jetHT_2016D/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016APV/data/jetHT_2016C/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/data/jetHT_2016H/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2016/data/singleMu_2016F/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/data/jetHT_2018b/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2018/data/jetHT_2018c/",
    // TString inputDir = "/publicfs/cms/data/TopQuark/nanoAOD/2017/data/jetHT_2017c/",
    // TString outputDir = "/publicfs/cms/user/fabioiemmi/TauOfTTTT/test_tobjectSelector/",
    TString outputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/crossCheck_noOverlap/tttt/",
    TString singleFileName = "outTree_0.root",
    // TString singleFileName = "outTree_1.root",
    // 1 for MetFilters, 2 for HLTSelection, 4 for preSelection. so 7 if all selection; 0 if no selection
    // TString eventSelectionBit = "3"
    TString eventSelectionBit = "7")
{
    using namespace std;
    // gROOT->SetMacroPath("/workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/src/FourTophua/objectSelection/");
    gROOT->ProcessLine(".L objectTSelectorForNanoAOD.so");

    // determine era and isData from inputDir
    TString era = "2016";
    Bool_t isData = true;
    TString dataSet = "mc";
    if (inputDir.Contains("mc"))
    {
        era = inputDir(inputDir.Index("nanoAOD") + 8, (inputDir.Index("mc") - inputDir.Index("nanoAOD") - 9));
        isData = false;
    }
    else
    {
        TString tempo = inputDir;
        tempo.Remove(0, inputDir.Index("data") + 4);
        era = tempo(tempo.Index("nanoAOD") + 8, (tempo.Index("data") - tempo.Index("nanoAOD") - 9));
        dataSet = tempo(tempo.Index("data") + 5, tempo.Length() - tempo.Index("data") - 6);
        cout << "dataSet in run: " << dataSet << "\n";
    }
    cout << "era is: " << era << "\n";

    if (era.CompareTo("2016") == 0)
    {
        era = "2016postVFP";
    }
    else if (era.CompareTo("2016APV") == 0)
    {
        era = "2016preVFP";
    }
    cout << "era is: " << era << "\n";
    cout << "selectionBit is:" << eventSelectionBit << "\n";
    cout << "isdata: " << isData << "\n";

    TString inputFile = inputDir + singleFileName;
    cout << "inputFile: " << inputFile << "\n";
    TChain chain("Events");
    chain.Add(inputFile);

    // TString outputFileName(inputDir(0, inputDir.First("/") ));
    // outputFileName = outputFileName + singleFileName;

    TString selection;
    TString option;
    Int_t eventNum = 100;
    // selection = "objectTSelectorForNanoAOD.C";
    selection = "objectTSelectorForNanoAOD"; // gROOT->ProcessLine(".L selection");
    if (istest)
    {
        outputDir = "output/";
        // eventNum = 100;
        eventNum = 1000;
        // eventNum = 10000;
    }
    TString outputFile;
    outputFile = outputDir + singleFileName;
    cout << "outputFile: " << outputFile << endl;
    option = outputFile + ":" + era + ":" + eventSelectionBit + ":" + isData + ":" + dataSet;
    cout << "option in run: " << option << "\n";

    TStopwatch t;
    t.Start();
    if (istest)
    {
        chain.Process(selection + "+", option, eventNum);
    }
    else
    {
        chain.Process(selection + "+", option);
    }

    // get Runs tree
    if (!isData)
    {
        TFile *inputRoot = TFile::Open(inputFile, "READ");
        TTree *runs = (TTree *)inputRoot->Get("Runs");
        runs->SetBranchStatus("*", 0);
        runs->SetBranchStatus("genEventSumw", 1);
        // runs->Print();

        TFile *outFile = TFile::Open(outputFile, "UPDATE");
        TTree *runsForOut = runs->CloneTree();
        // runsForOut->CopyEntries(runs);
        // runsForOut->Print();
        runsForOut->Write();
        outFile->Write();
        // outFile->ls();
        outFile->Close();

        inputRoot->Close();
    }
    t.Stop();
    t.Print();
}

int main(int argc, char const *argv[])
{

    Bool_t istest;
    TString inputDir;
    TString outputDir;
    TString singleFileName;
    TString eventSelectionBit;
    if (argc < 6)
    {
        std::cout << "not enough input from command line\n";
    }
    else
    {
        istest = boost::lexical_cast<bool>(argv[1]);
        inputDir = boost::lexical_cast<std::string>(argv[2]);
        outputDir = boost::lexical_cast<std::string>(argv[3]);
        singleFileName = boost::lexical_cast<std::string>(argv[4]);
        eventSelectionBit = boost::lexical_cast<std::string>(argv[5]);
        printf("istest=%i \n inputDir=%s \n outputDir=%s\n singleFileName=%s\n eventSelectionBit=%s\n ", istest, inputDir.Data(), outputDir.Data(), singleFileName.Data(), eventSelectionBit.Data());
        run_objectTSelectorForNanoAOD(istest, inputDir, outputDir, singleFileName, eventSelectionBit);
    }
    run_objectTSelectorForNanoAOD();

    return 0;
}