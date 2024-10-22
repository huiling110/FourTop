#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TStopwatch.h"

#include "../include/writeHist_forDataMC.h"
#include "../include/functions.h"
#include "../../myLibrary/commenFunction.h"
#include "../include/writeHist_btagEff.h"
#include "../include/writeHist_btagShapeR.h"
#include "../include/writeHist_fakeRate.h"
#include "../include/writeHist_HLTeff.h"

void run_treeAnalyzer(
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardro_btagMTWeight_v76WithVLLAllMass/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v77forBtagMeasurement/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v77forBtagMeasurement/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v77ForHLT/mc/", //!!!for HLT
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v77HadroPresel/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v77HadroPresel/data/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v79forHLT/mc/", //!for HLT
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v79HadroPresel/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v79forHLT/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v79forHLT/data/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v79forHLT/data/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHardroHLTSF_v79HadroPresel/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHardro_FRweightSys_v79HadroPresel/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHardro_FRweightSys_v79HadroPresel/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v80addTauJetVar/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v80addTTExtra/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v82for1tau2l/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baseline1tau2l_noTauCut_v82for1tau2l/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baseline1tau2l_noLepCut_v83for1tau2lEleEtaCut/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v2_v84fakeLeptonUpdateV2/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2lNotLepCut_v84Pre1tau2lNoLepCut/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v84Pre1tau2lLepF2/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v84Pre1tau2lLepF2/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v84Pre1tau2lNoLepCut/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v84Pre1tau2lNoLepCut/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v84Pre1tau2lLepF2V2/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018//v0baselineHardro_v84HadroPresel/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v85HadroPreselTauOverlap0.5/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardroFRUpdated_v85HadroPreselTauOverlap0.5/mc/",
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardroFRUpdated_v85HadroPreselTauOverlap0.5/data/",

    // TString process = "tttt",
    // TString process = "fakeTau_data",
    // TString process = "fakeLepton",
    // TString process = "WZTo3LNu",
    // TString process = "TTTo2L2Nu",
    // TString process = "TTToSemiLeptonic",
    // TString process = "TTToHadronic",
    // TString process = "VLL_EN_M600",
    // TString process = "fakeTau_tauF",
    TString process = "jetHT_2018d",
    // TString process = "singleMu_2016E_v2",
    // TString process = "BTagCSV_2017f",
    // TString process = "ttbar_0l",
    // TString process = "ttbar_2l",
    // TString channel = "1tau1l",
    TString channel = "1tau0l",
    TString histVersion = "v0_test",
    Bool_t isTest = kTRUE)
// Bool_t isTest = kFALSE)
{
    TStopwatch t;
    t.Start();

    Bool_t is1tau2l = channel=="1tau2l";
    std::cout<<"is1tau2l in run_WH_forDataMC="<<is1tau2l<<"\n"; 
    // WH_forDataMC writeHist(inputDir, process, kFALSE, histVersion, isTest, is1tau2l);
    // WH_forDataMC writeHist(inputDir, process, kTRUE, histVersion, isTest);//!faketau, for 1tau0l
    // WriteHist_btagEff writeHist(inputDir, process, histVersion, isTest);
    // WriteHist_btagShapeR writeHist(inputDir, process, histVersion, isTest);
    WH_fakeRate writeHist(inputDir, process, histVersion, isTest);
    // WH_HLTeff writeHist(inputDir, process, histVersion, isTest);

    writeHist.Init();
    UInt_t entry = 0;
    if (isTest)
    {
        entry = 10000;
    }
    writeHist.LoopTree(entry); //!!!maybe provide cut and weight as parameter here
    writeHist.Terminate();

    t.Stop();
    t.Print();
}

int main(int argc, char const *argv[])
{
    TString inputDir;
    TString inputProcess;
    TString channel;
    TString version;
    Bool_t isTest = kFALSE;
    if (argc < 5)
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
        isTest = boost::lexical_cast<Bool_t>(argv[5]);
        run_treeAnalyzer(inputDir, inputProcess, channel, version, isTest);
    }

    return 0;
}