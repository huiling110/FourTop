#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TStopwatch.h"

#include <iostream>
#include <boost/lexical_cast.hpp>

#include "../src_cpp/usefulFuction.h"

void run_writeHist(
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3HLTWeightUpdatedBugFixed_v56NoHLTButPre/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v6baseline_v56NoHLTButPre/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v57ovelapWithTausF/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v57ovelapWithTausF/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baslineNoHLT_v57ovelapWithTausF/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/",
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/",
    // TString inputProcess = "ttbar_0l",
    // TString inputProcess = "qcd_500to700",
    TString inputProcess = "tttt",
    // TString inputProcess = "ttbar_1l",
    // TString inputProcess = "wz",
    // TString inputProcess = 'WJetsToLNu_HT-600To800',
    // TString inputProcess = "jetHT_2016C",
    TString version = "test",
    // TString version = "overlapCheck",
    Bool_t isTest = kTRUE,
    // TString selector = "writeHist_fordataMC.C+") // 1tau1l)
    // TString selector = "writeHist_forFakeRate.C+" // 1tau0l
    TString selector = "writeHist_forFakeRate_3etaBin.C+") // 1tau0l
    // TString selector = "writeHist_forBtagRCal.C+")
    // TString selector = "writeHist_forSystematic.C+"
    // TString selector = "writeHist_forHLT.C+") // for tttt signal study
    // TString selector = "writeHist_forHLTStudy.C+") // for HLT study
    // TString selector = "writeHist_BDT.C+")
{
    using namespace std;
    TString inputFile = inputDir + inputProcess + ".root";
    std::cout << "input file: " << inputFile << "\n";

    Bool_t isData = kFALSE;
    if (inputDir.Contains("data"))
    {
        isData = kTRUE;
    }

    // get genWeightSumInitial for the process
    Double_t genWeightSumInitial = 1.0;
    if (!isData)
    {
        genWeightSumInitial = getGenSum(inputFile);
    }
    std::cout << inputProcess << ": "
              << "genWeightSumInitial: " << genWeightSumInitial << "\n";

    // get era
    TString temp = inputDir(inputDir.Index("forMVA/") + 7, inputDir.Sizeof());
    TString era = temp(0, temp.First("/"));

    TChain chain("newtree");
    chain.Add(inputFile);

    TString sumGenWeight = std::to_string(genWeightSumInitial);
    // TString option = inputDir + ":" + inputProcess + ":" + isData + ":" + version + ":" + era + ":";
    TString option = sumGenWeight + ":" + inputDir + ":" + inputProcess + ":" + isData + ":" + version + ":" + era + ":";
    std::cout << "option in run_writeHist: " << option << "\n";

    TStopwatch t;
    t.Start();

    // what if the chain is empty? it seems the selector it not run at all theu
    // chain.Print();
    std::cout << "entires in chain: " << chain.GetEntries() << "\n";
    // chain.Process(selector, option);
    chain.Process(selector, option, 1000);

    t.Stop();
    t.Print();
}

int main(int argc, char const *argv[])
{

    TString inputDir;
    TString inputProcess;
    TString version;
    Bool_t isTest;
    if (argc < 4)
    {
        std::cout << "not enough input from command line\n";
        run_writeHist();
    }
    else
    {
        inputDir = boost::lexical_cast<std::string>(argv[1]);
        inputProcess = boost::lexical_cast<std::string>(argv[2]);
        version = boost::lexical_cast<std::string>(argv[3]);
        isTest = boost::lexical_cast<bool>(argv[4]);
        // printf("istest=%i \n inputBase=%s \ninputDir=%s\n  outputDir = %s\n eventSelectionBit=%s\n ", istest, inputBase.Data(), inputDir.Data(), outputDir.Data(), eventSelectionBit.Data());
        run_writeHist(inputDir, inputProcess, version, isTest);
    }

    return 0;
}