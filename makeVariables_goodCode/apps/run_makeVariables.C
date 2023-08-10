#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TStopwatch.h"
#include "TString.h"
#include "TChain.h"

#include "../include/makeVariablesMain.h"
#include "../../myLibrary/commenFunction.h"

void run_objectSelection(
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v58addGenBranches/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v59newOScode/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v60fixeJetBtagBug/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v61fixesLepRemovalBug/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v61fixesLepRemovalBug/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v61fixesLepRemovalBug/mc/",
    TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v61fixesLepRemovalBug/mc/",

    // TString inputDir = "ttZ",
    TString inputDir = "tttt",
    // TString inputDir = "ttbar_0l",
    // TString inputDir = "jetHT_2017f",
    // TString inputDir = "ttbar_1l",
    // TString inputBase = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelectionOptimized/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/Prompt2022/v0Testing/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/ReReco2022PreEE/v1newCrab/mc/",
    // TString inputDir = "TTto2L2Nu",
    // TString inputDir = "TTto4Q",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/Prompt2022/v0Testing/data/",
    // TString inputDir = "JetMET_G",
    // TString inputDir = "output",
    // TString outputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/cutflowCheck/",
    TString outputDir = "output/",
    Int_t numEntries = 1000)
{
    TStopwatch t;
    t.Start();

    TString inputDir1 = inputBase + inputDir + "/";
    TString processName = inputDir;
    Bool_t    isData = TTTT::getIsData(inputDir1);
    TString    era = TTTT::getEra2(inputDir1);
    Bool_t isRun3 = TTTT::isRun3(era);
    // std::cout << "isRun3=" << isRun3 << "\n";

    MakeVariablesMain mv(inputDir1, outputDir, processName, isData, era, isRun3);
    // mv.EventLoop(kTRUE,kTRUE, numEntries); //1tau1l cut
    mv.EventLoop(kTRUE,kFALSE, numEntries);
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