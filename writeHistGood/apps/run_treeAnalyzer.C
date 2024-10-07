#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TStopwatch.h"

#include "../include/treeAnalyzer.h"
#include "../include/functions.h"

void run_treeAnalyzer(
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v76For1tau2l/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v75OverlapRemovalFTau/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_newTriSFBinD_v75OverlapRemovalFTau/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baselineHardro_FRweightSys_v76WithVLLSample/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_newTriSFBinD_v76WithVLLSample/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baselineHardro_FRweightSys_v76WithVLLAllMass/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHardro_FRweightSys_v79HadroPresel/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardro_btagMTWeight_v76WithVLLAllMass/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardro_btagMTWeight_v76WithVLLAllMass/data/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHardro_FRweightSys_v79HadroPresel/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v80addTauJetVar/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v80addTauJetVar/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v81addSysSum/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v84Pre1tau2lLepF2/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v84Pre1tau2lLepF2/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v84Pre1tau2lLepF2/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v84Pre1tau2lLepF2V2/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v84Pre1tau2lLepF2V2/mc/",
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v84Pre1tau2lLepF2V2/mc/",
    TString process = "tttt",
    // TString process = "fakeLepton",
    // TString process = "st_tZq",
    // TString process = "fakeTau_tauF",
    // TString process = "ttbar_0l",
    // TString process = "ttbar_2l",
    // TString process = "jetHT_2016E",
    // TString process = "jetHT_2018a",
    TString histVersion = "v0_test",
    // Int_t channel = 0,//0: 1tau1l
    // TString channel = "1tau1l",//0: 1tau1l
    // TString channel = "1tau0l",//
    TString channel = "1tau2l",//
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
        channel = boost::lexical_cast<std::string>(argv[4]);
        isTest = boost::lexical_cast<Bool_t>(argv[5]);
        run_treeAnalyzer(inputDir, inputProcess, version, channel, isTest);
    }

    return 0;
}