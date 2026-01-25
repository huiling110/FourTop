/**
 * @file run_variableAnalyzer.C
 * @brief Entry point for input variable histogram generation
 *
 * OUTPUT: inputVarHists_{version}/ (NOT variableHists_ to avoid BDT conflict!)
 *
 * @author Huiling Hua
 * @date 2025-01-25
 */
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "TStopwatch.h"
#include "../include/variableAnalyzer.h"
#include "../include/functions.h"

void run_variableAnalyzer(
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/",
    TString process = "tttt",
    TString channel = "1tau1l",
    TString histVersion = "v0_test",
    Bool_t ifSys = kTRUE,
    Bool_t isTest = kTRUE)
{
    TStopwatch t;
    t.Start();

    variableAnalyzer analyzer(inputDir, process, histVersion, channel, isTest, ifSys);
    analyzer.Init();
    analyzer.LoopTree();
    analyzer.Terminate();

    t.Stop();
    t.Print();
}

int main(int argc, char const *argv[])
{
    TString inputDir;
    TString inputProcess;
    TString version;
    TString channel;
    Bool_t ifSys = kTRUE;
    Bool_t isTest = kFALSE;

    if (argc < 4) {
        std::cout << "not enough input from command line\n";
        std::cout << "Usage: run_variableAnalyzer inputDir process channel version ifSys isTest\n";
        run_variableAnalyzer();
    } else {
        std::cout << "using input from command line\n";
        inputDir = boost::lexical_cast<std::string>(argv[1]);
        inputProcess = boost::lexical_cast<std::string>(argv[2]);
        channel = boost::lexical_cast<std::string>(argv[3]);
        version = boost::lexical_cast<std::string>(argv[4]);
        ifSys = boost::lexical_cast<Bool_t>(argv[5]);
        isTest = boost::lexical_cast<Bool_t>(argv[6]);
        run_variableAnalyzer(inputDir, inputProcess, channel, version, ifSys, isTest);
    }

    return 0;
}
