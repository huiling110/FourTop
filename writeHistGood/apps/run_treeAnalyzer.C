#include <iostream>
#include <boost/lexical_cast.hpp>
#include "TStopwatch.h"
#include "../include/treeAnalyzer.h"
#include "../include/functions.h"

void run_treeAnalyzer(
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/",//!Updated with new MV
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_JESup_RelativeSample_AK4PFchs_v94HadroPreJetVetoHemOnly_JESPt22/mc/",//!Updated with new MV
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1_v94LepPreJetVetoHemOnly/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_tauFMorph_v94LepPreJetVetoHemOnly/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorph_v94HadroPreJetVetoHemOnly/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/", //!v14
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/", //!v14
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_JESDown_AbsoluteMPFBias_AK4PFchs_v94HadroPreJetVetoHemOnly_JESPt22/mc/", 
    TString process = "tttt",
    // TString process = "ttbar_1l",
    // TString process = "fakeLepton",
    // TString process  = "fakeTau_data",
    // TString process  = "fakeTau_data_ptMorphed",
    // TString process = "ttbar_0l",
    // TString process = "ttbar_2l",
    // TString process = "jetHT_2018a",
    // Int_t channel = 0,//0: 1tau1l
    TString channel = "1tau1l",//
    // TString channel = "1tau0l",//
    // TString channel = "1tau2l",//
    TString histVersion = "v0_test",//
    // Bool_t ifSys = kTRUE,
    Bool_t ifSys = kFALSE,
    Bool_t isTest = kTRUE)
    // Bool_t isTest = kFALSE)
{
    TStopwatch t;
    t.Start();
    treeAnalyzer writeBDTHist(inputDir, process, histVersion, channel, isTest, ifSys);
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
    Bool_t ifSys = kTRUE;
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
        channel = boost::lexical_cast<std::string>(argv[3]);
        version = boost::lexical_cast<std::string>(argv[4]);
        ifSys = boost::lexical_cast<Bool_t>(argv[5]);
        isTest = boost::lexical_cast<Bool_t>(argv[6]);
        run_treeAnalyzer(inputDir, inputProcess,   channel, version,  ifSys, isTest);

    }

    return 0;
}