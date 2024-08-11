#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TStopwatch.h"
#include "TString.h"
#include "TChain.h"

#include "../include/makeVariablesMain.h"
#include "../../myLibrary/commenFunction.h"

void run_objectSelection(
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/V75NoHLTNoTauBjet2/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v75NoHLTNoTauHT400Jet6pt30/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v77ForHLT/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v76WithVLLSample/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v76WithVLLAllMass/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v77ForHLT/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v77forBtagMeasurement/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v77forBtagMeasurement/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v77HadroPresel/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v77HadroPresel/data/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v79forHLT/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v79forHLT/data/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v79HadroPresel/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v79forHLT/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v79forHLT/data/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v79HadroPresel/tttt/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v79HadroPresel/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v80addTauJetVar/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v80addTauJetVar/mc/",
    TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v80addTauJetVar/mc/",

    TString inputDir = "tttt",
    // TString inputDir = "VLL_EE_M600",
    // TString inputDir = "VLL_EE_M800",
    // TString inputDir = "ttbar_0l",
    // TString inputDir = "ttbar_1l",
    // TString inputDir = "jetHT_2017f",
    // TString inputDir = "BTagCSV_2017c",
    // TString inputDir = "JetMET2022D",
    // TString inputDir = "singleMu_2017b",
    // TString inputDir = "singleMu_2016F",
    // TString inputDir = "ttbar_1l",
    // TString inputBase = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelectionOptimized/",
    // TString inputDir = "TTto4Q",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/Prompt2022/v0Testing/data/",
    // TString inputDir = "JetMET_G",
    // TString inputDir = "output",
    TString outputDir = "output/",
    // Int_t numEntries = 100000)
    Int_t numEntries = 3000)
    // Int_t numEntries = 10000)
    // Int_t numEntries = 0)
{
    TStopwatch t;
    t.Start();

    TString inputDir1 = inputBase + inputDir + "/";
    TString processName = inputDir;
    Bool_t isData = TTTT::getIsData(inputDir1);
    TString era = TTTT::getEra2(inputDir1);
    Bool_t isRun3 = TTTT::isRun3(era);
    std::cout << "isRun3=" << isRun3 << " era=" << era << "\n";

    MakeVariablesMain mv(inputDir1, outputDir, processName, isData, era, isRun3);
    Bool_t baseline = kTRUE;
    // Bool_t baseline = kFALSE;
    // mv.EventLoop(baseline, kTRUE, numEntries); //1tau1l cut 
    mv.EventLoop(baseline, kFALSE, numEntries);
    mv.Terminate();

    t.Stop();
    t.Print();
    return;
}


int main(int argc, char const *argv[])
{
    TString inputDir;
    TString inputProcess;
    TString outputDir;
    Int_t numEntries = 0;
    if (argc < 4)
    {
        std::cout << "not enough input from command line\n";
        run_objectSelection();
    }
    else
    {
        std::cout << "using input from command line\n";
        inputDir = boost::lexical_cast<std::string>(argv[1]);
        inputProcess = boost::lexical_cast<std::string>(argv[2]);
        outputDir = boost::lexical_cast<std::string>(argv[3]);
        numEntries = boost::lexical_cast<Int_t>(argv[4]);
        run_objectSelection(inputDir, inputProcess, outputDir, numEntries);
    }

    return 0;
}