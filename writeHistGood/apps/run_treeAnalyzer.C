#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TStopwatch.h"

#include "../include/treeAnalyzer.h"
#include "../include/functions.h"

void run_treeAnalyzer(
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v8tau1elCut_v60fixeJetBtagBug/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3btagWeightGood_v61fixesLepRemovalBug/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3btagWeightGood_v61fixesLepRemovalBug/data/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1btagWPandRUpdated_v61fixesLepRemovalBug/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022/v0baseline_v0preSel/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v0preSel/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_addTauGenNum_v61fixesLepRemovalBug/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_addTauGenNum_v61fixesLepRemovalBug/mc/",
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_JERUp/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_JESUp/mc/",
    TString process = "tttt",
    // TString process = "ttbar_0l",
    // TString process = "ttbar_1l",
    // TString process = "jetHT_2016E",
    // TString process = "ttZ",
    // TString process = "TTto4Q",
    // TString process = "TTto2L2Nu",
    TString histVersion = "v0_test",
    // Int_t channel = 0,//0: 1tau1l
    TString channel = "1tau1l",//0: 1tau1l
    // Int_t channel = 1,// 1: 1tau0l
    Bool_t isTest = kTRUE)
    // Bool_t isTest = kFALSE)
{

    TStopwatch t;
    t.Start();
    treeAnalyzer writeBDTHist(inputDir, process, histVersion, channel, isTest);
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
    TString channel;
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
        channel = boost::lexical_cast<TString>(argv[4]);
        isTest = boost::lexical_cast<Bool_t>(argv[5]);
        run_treeAnalyzer(inputDir, inputProcess, version, channel, isTest);
    }

    return 0;
}