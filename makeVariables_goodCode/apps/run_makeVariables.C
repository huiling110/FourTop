#include <iostream>
#include <boost/lexical_cast.hpp>
#include "TStopwatch.h"
#include "TString.h"
#include "TChain.h"

#include "../include/makeVariablesMain.h"
#include "../../myLibrary/commenFunction.h"

void run_objectSelection(
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v84Pre1tau2lLepF2V2/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v84Pre1tau2lLepF2V2/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v84HadroPresel/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v84HadroPresel/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v84HadroPresel/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v85HadroPreselTauOverlap0.5/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v86HadroPreSelWithGammaRemoval/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v86HadroPreSelWithTTWTTZNLO/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v86HadroPreSelWithTTWTTZNLO/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v86HadroPreSelWithTTWTTZNLO/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v86LepPreSel/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v87LepPreSel_GammaRemovalBugFixed/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v87addPdfPSWeightSum/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v88PSWeightFixedLepPre/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v88PSWeightFixedHadroPre/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v88PSWeightFixedHadroPre/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v88PSWeightFixedHadroPre/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v89HadroPre_JESPt22/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v89HadroPre_JESPt22/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2017/v89HadroPre_JESPt22/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v90MuonESHadroPre/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v90MuonESHadroPre_JESPt22/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v91TESAddedHadroPre/mc/",
    // TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v91TESAddedHadroPre_TESdm0Down/mc/",
    TString inputBase = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018//v91TESAddedHadroPre_JESPt20/mc/",
    TString inputDir = "tttt",
    // TString inputDir = "TTWJetsToLNu",
    // TString inputDir = "TTZToLLNuNu",
    // TString inputDir = "ttG",
    // TString inputDir = "ZGToLLG",
    // TString inputDir = "WZTo3LNu",
    // TString inputDir = "wz",
    // TString inputDir = "DYJetsToLL_M-50",
    // TString inputDir = "VLL_EE_M600",
    // TString inputDir = "ttbar_0l",
    // TString inputDir = "ttbar_1l",
    // TString inputDir = "ttbar_2l",
    // TString inputDir = "jetHT_2017f",
    // TString inputDir = "BTagCSV_2017c",
    // TString inputDir = "singleMu_2018b",
    // TString inputDir = "TTToSemiLeptonic10", //extra ttbar for training
    // TString inputDir = "TTTo2L2Nu0",
    // TString inputDir = "doubleMu_2018b",
    TString outputDir = "output/",
    // Int_t numEntries = 100)
    Int_t numEntries = 3000,
    // Int_t numEntries = 0,
    // Bool_t if1tau2l = kTRUE; //!
    Bool_t if1tau2l = kFALSE, //!!!
    // UChar_t JESVariationType = 1, //!!!0: nominal, 1: up, 2: down
    UChar_t JESVariationType = 0, //!!!0: nominal, 1: up, 2: down
    // UChar_t JESVariationType = 2, //!!!0: nominal, 1: up, 2: down
    // UChar_t JESVariation = 0 //ordering of the source of systematic uncertainties for  JES
    UChar_t JESVariation = 0 //ordering of the source of systematic uncertainties for  JES
    )
{
    TStopwatch t;
    t.Start();

    TString inputDir1 = inputBase + inputDir + "/";
    TString processName = inputDir;
    Bool_t isData = TTTT::getIsData(inputDir1);
    TString era = TTTT::getEra2(inputDir1);
    Bool_t isRun3 = TTTT::isRun3(era);
    std::cout << "isRun3=" << isRun3 << " era=" << era << "\n";
    std::cout<<"JESVariationType="<<static_cast<int>(JESVariationType)<<"   JESVariation="<<static_cast<int>(JESVariation)<<"\n";
    std::cout<<"finishing run_MakeVariables\n\n";

    MakeVariablesMain mv(inputDir1, outputDir, processName, isData, era, isRun3, if1tau2l, JESVariation, JESVariationType);
    Bool_t baseline = kTRUE;
    mv.EventLoop(baseline, kFALSE, numEntries);
    //mv.EventLoop(baseline, kTRUE, numEntries); //!channel cut, for BDT training only 
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
    Bool_t if1tau2l = kFALSE;
    UChar_t JESVariationType = 0;
    UChar_t JESVariation = 0;
    if (argc < 7)
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
        if1tau2l = boost::lexical_cast<Bool_t>(argv[5]);
        // JESVariationType = boost::lexical_cast<UChar_t>(argv[6]);
        JESVariationType = static_cast<UChar_t>(boost::lexical_cast<int>(argv[6]));
        JESVariation = static_cast<UChar_t>(boost::lexical_cast<int>(argv[7]));
        run_objectSelection(inputDir, inputProcess, outputDir, numEntries, if1tau2l, JESVariationType, JESVariation);
    }

    return 0;
}