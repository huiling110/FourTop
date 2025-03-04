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
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018//v0baselineHardro_v84HadroPresel/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v85HadroPreselTauOverlap0.5/mc/", 
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardroFRUpdated_v85HadroPreselTauOverlap0.5/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardroFRUpdated_v85HadroPreselTauOverlap0.5/data/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v86HadroPreSelWithTTWTTZNLO/data/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v86HadroPreSelWithTTWTTZNLO/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v86HadroPreSelWithTTWTTZNLO/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v91TESAddedHadroPre/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v93HadroPreJetVetoPileupID/mc/",
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/",
    // TString process = "tttt",
    // TString process = "fakeTau_data",
    // TString process = "WZTo3LNu",
    // TString process = "fakeTau_tauF",
    TString process = "jetHT_2018d",
    // TString process = "jetHT_2017d",
    // TString process = "singleMu_2016E_v2",
    // TString process = "BTagCSV_2017f",
    // TString process = "ttbar_2l",
    TString channel = "1tau1l",
    // TString channel = "1tau0l",
    TString histVersion = "v0_test",
Bool_t isTest = kTRUE)
// Bool_t isTest = kFALSE)
{
    TStopwatch t;
    t.Start();

    Bool_t is1tau2l = channel=="1tau2l";
    std::cout<<"is1tau2l in run_WH_forDataMC="<<is1tau2l<<"\n"; 
    // WH_forDataMC writeHist(inputDir, process, kTRUE, histVersion, isTest, is1tau2l); //!m_ifFakeTau=True as default for 1tau0l, only impacts 1tau0l tau selection. For 1tau1l and 1tau2l, tauT=1
    // WH_forDataMC writeHist(inputDir, process, kTRUE, histVersion, isTest, is1tau2l, kTRUE); //!m_ifSys=True
    // WH_forDataMC writeHist(inputDir, process, kFALSE, histVersion, isTest, is1tau2l);//!not asking tau to be genuine, validation check for not estimating fakeTau bg, but use all MC(qcd)
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