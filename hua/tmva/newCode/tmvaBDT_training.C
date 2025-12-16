#include <boost/lexical_cast.hpp>
#include <fstream>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TCut.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"
#include "TMVA/Config.h"

#include "processClass.h"
#include "../../../myLibrary/commenFunction.h"

// WH (writeHistGood) headers for selection/weight consistency
#include "myEventClass.h"
#include "commenSelectionAndWeight.h"

// For global weight calculation (lumi * xsec / genWeightSum)
#include "../../../src_cpp/lumiAndCrossSection.h"

// Process lists matching proChannelDic in ttttGlobleQuantity.py
// proChannelDic = {
//     '1tau1l': ['fakeTau', 'tt', 'ttbb', 'ttX', 'fakeLepton', 'singleTop', 'tttt', 'jetHT']
//     '1tau0l': ['fakeTau', 'tt', 'ttbb', 'ttX', 'singleTop', 'WJets', 'tttt', 'jetHT']
// }
// Note: jetHT is data, excluded from training

void getProcessesVec(TString inputDir, std::vector<Process>& processVec, const TString channel = "1tau2l", const TString ifVLL=kFALSE)
{
    std::map<TString, std::vector<TString>> allProcesses = {
        // 1tau1l: ['fakeTau', 'tt', 'ttbb', 'ttX', 'fakeLepton', 'singleTop', 'tttt']
        {"1tau1l", {
            "tttt",  // signal (index 0)
            // fakeTau category
            "fakeTau_data_ptMorphed",
            "fakeTau_MC_ptMorphed",
            // tt category
            "ttbar_0l",
            "ttbar_1l",
            "ttbar_2l",
            // ttbb category (NEW)
            "TTBB_4f_TTToHadronic",
            "TTBB_4f_TTToSemiLeptonic",
            "TTBB_4f_TTTo2L2Nu",
            // ttX category
            "TTZToLLNuNu",
            "TTZToQQ",
            "TTWJetsToLNu",
            "TTWJetsToQQ",
            "ttH_bb",
            "ttH_nonbb",
            // fakeLepton category (1tau1l specific)
            "fakeLepton",
            // singleTop category
            "st_tW_antitop",
            "st_tW_top",
            "st_schan_lep",
            "st_tchan",
            // NOTE: No WJets in 1tau1l per proChannelDic
            // NOTE: No jetHT (data)
        }},

        // 1tau0l: ['fakeTau', 'tt', 'ttbb', 'ttX', 'singleTop', 'WJets', 'tttt']
        {"1tau0l", {
            "tttt",  // signal (index 0)
            // fakeTau category
            "fakeTau_data_ptMorphed",
            "fakeTau_MC_ptMorphed",
            // tt category
            "ttbar_0l",
            "ttbar_1l",
            "ttbar_2l",
            // ttbb category (NEW)
            "TTBB_4f_TTToHadronic",
            "TTBB_4f_TTToSemiLeptonic",
            "TTBB_4f_TTTo2L2Nu",
            // ttX category
            "TTZToLLNuNu",
            "TTZToQQ",
            "TTWJetsToLNu",
            "TTWJetsToQQ",
            "ttH_bb",
            "ttH_nonbb",
            // singleTop category
            "st_tW_antitop",
            "st_tW_top",
            "st_schan_lep",
            "st_tchan",
            // WJets category (1tau0l specific)
            "WJetsToLNu_HT-200To400",
            "WJetsToLNu_HT-400To600",
            "WJetsToLNu_HT-600To800",
            "WJetsToLNu_HT-800To1200",
            "WJetsToLNu_HT-1200To2500",
            "WJetsToLNu_HT-2500ToInf",
            // NOTE: No fakeLepton in 1tau0l per proChannelDic
            // NOTE: No jetHT (data)
        }},

        {"1tau2l",{
            "tttt",  // signal (index 0)
            // fakeTau category
            "fakeTau_data_ptMorphed",
            "fakeTau_MC_ptMorphed",
            // tt category
            "ttbar_0l",
            "ttbar_1l",
            "ttbar_2l",
            // ttbb category (NEW)
            "TTBB_4f_TTToHadronic",
            "TTBB_4f_TTToSemiLeptonic",
            "TTBB_4f_TTTo2L2Nu",
            // ttX category
            "TTZToLLNuNu",
            "TTZToQQ",
            "TTWJetsToLNu",
            "TTWJetsToQQ",
            "ttH_bb",
            "ttH_nonbb",
            // fakeLepton category
            "fakeLepton",
            // singleTop category
            "st_tW_antitop",
            "st_tW_top",
            "st_schan_lep",
            "st_tchan",
            // Minor category (1tau2l specific)
            "WZTo3LNu",
            "zz",
            }
        },
    };

    processVec.clear();
    for(UInt_t i=0; i<allProcesses.at(channel).size(); i++){
        TString ifile = inputDir+allProcesses.at(channel).at(i)+".root";
        // Check if file exists before adding
        if(gSystem->AccessPathName(ifile)){
            std::cout << "WARNING: File not found, skipping: " << ifile << "\n";
            continue;
        }
        Process iPro{ifile};
        processVec.push_back(iPro);
    }
}

// Helper function to determine process type for WH selection/weight
// Returns: 0 = regular MC, 1 = fakeTau, 2 = fakeLepton
Int_t getProcessType(const TString& processName) {
    if(processName.Contains("fakeTau")) return 1;
    if(processName.Contains("fakeLepton")) return 2;
    return 0; // regular MC
}

// Helper function to get the appropriate weight expression for each process type
// Based on baseWeightCal() in commenSelectionAndWeight.C
TString getWeightExpression(Int_t processType, const TString& channel) {
    if(processType == 1) {  // fakeTau
        return "FR_weight_final";
    }
    if(processType == 2) {  // fakeLepton
        return "lepTopMVAF_FRweight";
    }
    // Regular MC - channel specific weights from WH
    if(channel == "1tau1l") {
        // From commenSelectionAndWeight.C line 216
        return "EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*elesTopMVAT_weight_new*musTopMVAT_weight_new*btagWPMT_weight*elesTopMVAT_reoSF_weight";
    }
    if(channel == "1tau0l") {
        // From commenSelectionAndWeight.C line 224 (no lepton weights)
        return "EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagShape_weight*btagShapeR";
    }
    if(channel == "1tau2l") {
        // From commenSelectionAndWeight.C line 230
        return "EVENT_genWeight*EVENT_prefireWeight*PUweight_*triggerSFLep_weight*tauT_IDSF_weight_new*elesTopMVAT_weight_new*musTopMVAT_weight_new*btagWPMT_weight*elesTopMVAT_reoSF_weight";
    }
    return "1.0";  // fallback
}

// Helper function to get selection TCut based on process type and channel
// Based on baselineSelection() and SR1tau1lSel() in commenSelectionAndWeight.C
TCut getSelectionCut(Int_t processType, const TString& channel) {
    // Baseline selection (common)
    TCut baseCut = "(jets_num>=6 && bjetsM_num>=2 && jets_HT>500 && jets_6pt>40)";

    // Channel-specific SR selection
    TCut srCut = "";
    if(channel == "1tau1l") {
        // For MC: isTightPrompt lepton, genFlavour tau
        // For fakeTau: !isTight tau
        // For fakeLepton: isAR lepton
        if(processType == 0) {  // MC
            srCut = "(tausF_1isTight && tausF_1genFlavour!=0 && tausF_num==1) && ((elesTopMVAF_1isTightPrompt || muonsTopMVAF_1isTightPrompt) && lepTopMVAF_num==1) && jets_num>=7 && bjetsM_num>=3";
        } else if(processType == 1) {  // fakeTau
            srCut = "(!tausF_1isTight && tausF_num==1) && ((elesTopMVAF_1isTight || muonsTopMVAF_1isTight) && lepTopMVAF_num==1) && jets_num>=7 && bjetsM_num>=3";
        } else {  // fakeLepton
            srCut = "(tausF_1isTight && tausF_num==1) && (lepTopMVAF_isAR && lepTopMVAF_num==1) && jets_num>=7 && bjetsM_num>=3";
        }
    } else if(channel == "1tau0l") {
        if(processType == 0) {  // MC
            srCut = "(tausF_1isTight && tausF_1genFlavour!=0 && tausF_num==1) && (elesTopMVAT_num + muonsTopMVAT_num == 0) && jets_num>=8 && bjetsM_num>=3";
        } else if(processType == 1) {  // fakeTau
            srCut = "(!tausF_1isTight && tausF_num==1) && (elesTopMVAT_num + muonsTopMVAT_num == 0) && jets_num>=8 && bjetsM_num>=3";
        }
        // Note: 1tau0l doesn't have fakeLepton per proChannelDic
    } else if(channel == "1tau2l") {
        if(processType == 0) {  // MC
            srCut = "(tausF_1isTight && tausF_1genFlavour!=0 && tausF_num==1) && (lepTopMVAF_num==2) && jets_num>=4 && bjetsM_num>=2";
        } else if(processType == 1) {  // fakeTau
            srCut = "(!tausF_1isTight && tausF_num==1) && (lepTopMVAF_num==2) && jets_num>=4 && bjetsM_num>=2";
        } else {  // fakeLepton
            srCut = "(tausF_1isTight && tausF_num==1) && (lepTopMVAF_isAR && lepTopMVAF_num==2) && jets_num>=4 && bjetsM_num>=2";
        }
    }

    return baseCut && srCut;
}

int tmvaBDT_training(
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3cut1tau1lSR6thJetpt34_v75OverlapRemovalFTau/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v76WithVLLSample/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v76WithVLLAllMass/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau0lSRTauF_v76WithVLLAllMass/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2cut1tau0lSRTauF_v79HadroPresel/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau0lSRTauF_v80addTauJetVar/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v80addTTExtra1/mc/",
    // TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau2lSR_v84Pre1tau2lLepF2/mc/",
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1cut1tau1lSR_v84HadroPresel/mc/",
    TString outDir = "output/",
    Bool_t isTest = true,
    // TString variableListCsv = "/workfs2/cms/huahuil/4topCode/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau0l.csv",
    // TString variableListCsv = "/workfs2/cms/huahuil/4topCode/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau0l_final26.csv",
    // TString variableListCsv = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau2l.csv",
    // TString variableListCsv = "/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau1l_final30.csv",
    // TString variableListCsv = "/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau1l_final.csv",
    TString variableListCsv = "/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau1l_final.csv",
    const TString channel = "1tau1l",
    const TString ifVLL = "",
    const TString era = "2018"  // Era for lumi lookup (global weight)
    )
{
    std::cout << "inputDir=" << inputDir << "\n";
    std::cout << "channel=" << channel << " ifVLL=" << ifVLL << " era=" << era << "\n\n";

    // Get lumi for this era (for global weight calculation)
    Double_t lumi = 1.0;
    if(TTTT::lumiMap.count(era) > 0) {
        lumi = TTTT::lumiMap.at(era);
        std::cout << "Using lumi for era " << era << ": " << lumi << " pb^-1\n";
    } else {
        std::cout << "WARNING: Era " << era << " not found in lumiMap, using lumi=1.0\n";
    }

    TObjArray *tokens = variableListCsv.Tokenize("/");
    TString csvListName = ((TObjString *)tokens->Last())->GetString();
    tokens->Delete();
    std::cout << "csvName=" << csvListName << "\n";

    TString outfileName = outDir + csvListName + ".root";
    TFile *outputFile = TFile::Open(outfileName, "RECREATE");

    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification");
    TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");
    TMVA::Tools::Instance();
    // (TMVA::gConfig().GetVariablePlotting()).fNbins1D = 30;
    // TMVA::gConfig().GetVariablePlotting().fNbinsMVAoutput = 30;
    (TMVA::gConfig().GetIONames()).fWeightFileDir =  "weight/";
    // TMVA::gConfig().GetIONames().fWeightFileDirPrefix = outDir; // If a non-nul prefix is set in TMVA::gConfig().GetIONames().fWeightFileDirPrefix the weights will be stored in weightfile_prefix/dataset_name/weight_file_name
    TMVA::gConfig().GetIONames().fWeightFileDirPrefix = outDir+ csvListName; // If a non-nul prefix is set in TMVA::gConfig().GetIONames().fWeightFileDirPrefix the weights will be stored in weightfile_prefix/dataset_name/weight_file_name

    // read input variables from csv
    std::vector<TString> variableList;
    TTTT::getVarFromFile(variableListCsv, variableList);
    for (UInt_t i = 0; i < variableList.size(); i++)
    {
        TString ivar = variableList.at(i);
        std::cout << "adding input variable: " << ivar << "\n";
        if (ivar.Contains("num") || ivar.Contains("charge"))
        {
            dataloader->AddVariable(variableList.at(i), 'I');
        }
        else
        {
            dataloader->AddVariable(variableList.at(i), 'F');
        }
    }

    // add signal and bg trees with process-specific selection and weights
    // Using WH-consistent selection and weight expressions
    Long64_t allBg = 2000;
    Long64_t allSignal = 2000;
    std::vector<Process> processVec;
    getProcessesVec(inputDir, processVec, channel, ifVLL);

    // Track weight expressions per process type for later reference
    std::map<Int_t, TString> weightExpressions;
    weightExpressions[0] = getWeightExpression(0, channel);  // MC
    weightExpressions[1] = getWeightExpression(1, channel);  // fakeTau
    weightExpressions[2] = getWeightExpression(2, channel);  // fakeLepton

    std::cout << "Weight expressions:\n";
    std::cout << "  MC: " << weightExpressions[0] << "\n";
    std::cout << "  fakeTau: " << weightExpressions[1] << "\n";
    std::cout << "  fakeLepton: " << weightExpressions[2] << "\n\n";

    // Minimum events threshold after selection
    const Long64_t MIN_EVENTS_THRESHOLD = 50;
    std::vector<TString> skippedProcesses;

    for (UInt_t i=0; i<processVec.size(); i++){
        if(processVec.at(i).getTree()->GetEntries()<=0) continue;

        TString procName = processVec.at(i).getName();
        Int_t procType = getProcessType(procName);
        TCut selCut = getSelectionCut(procType, channel);
        TString weightExpr = weightExpressions[procType];

        // Count events passing selection first (needed for both test and full training)
        Long64_t nPass = processVec.at(i).getTree()->GetEntries(selCut);
        Long64_t nTotal = processVec.at(i).getTree()->GetEntries();

        // Skip background processes with fewer than MIN_EVENTS_THRESHOLD events after selection
        if(i > 0 && nPass < MIN_EVENTS_THRESHOLD) {
            std::cout << "WARNING: Skipping " << procName << " - only " << nPass
                      << " events pass selection (threshold: " << MIN_EVENTS_THRESHOLD << ")\n";
            skippedProcesses.push_back(procName);
            continue;
        }

        // Calculate global weight (processScale = lumi * xsec / genWeightSum)
        // For fake processes, processScale = 1.0 (they already have data-driven weights)
        Double_t processScale = 1.0;
        if(procType == 0) {  // MC process
            TString filePath = processVec.at(i).getInputFile();
            Double_t genWeightSum = TTTT::getGenSum(filePath);

            // Get cross-section for this process
            if(TTTT::crossSectionMap.count(procName) > 0 && genWeightSum > 0) {
                Double_t xsec = TTTT::crossSectionMap.at(procName);
                processScale = (lumi * xsec) / genWeightSum;
                std::cout << "  processScale = " << lumi << " * " << xsec << " / " << genWeightSum << " = " << processScale << "\n";
            } else {
                std::cout << "  WARNING: xsec not found for " << procName << " or genWeightSum=0, using processScale=1.0\n";
            }
        }

        // Signal = tttt (index 0), Background = all others
        if(i == 0){
            std::cout << "signal tree: " << procName << " (type=" << procType << ")\n";
            std::cout << "  selection: " << selCut.GetTitle() << "\n";
            std::cout << "  weight: " << weightExpr << "\n";
            dataloader->AddSignalTree(processVec.at(i).getTree(), processScale);
            dataloader->SetSignalWeightExpression(weightExpr);
            if(!isTest){
                allSignal = allSignal + nPass;
            }
            std::cout << "  entries: " << nTotal << " (pass selection: " << nPass << ")\n";
        }
        else{
            std::cout << "bg tree: " << procName << " (type=" << procType << ")\n";
            std::cout << "  selection: " << selCut.GetTitle() << "\n";
            std::cout << "  weight: " << weightExpr << "\n";

            // Add background tree with processScale as global weight
            dataloader->AddBackgroundTree(processVec.at(i).getTree(), processScale);

            if(!isTest){
                allBg = allBg + nPass;
            }
            std::cout << "  entries: " << nTotal << " (pass selection: " << nPass << ")\n";
        }
    }
    std::cout << "\nsignal and bg trees added\n";

    // Print summary of skipped processes
    if(!skippedProcesses.empty()) {
        std::cout << "\n========================================\n";
        std::cout << "WARNING: " << skippedProcesses.size() << " process(es) skipped due to low statistics (<" << MIN_EVENTS_THRESHOLD << " events):\n";
        for(const auto& proc : skippedProcesses) {
            std::cout << "  - " << proc << "\n";
        }
        std::cout << "========================================\n\n";
    }

    // Set weight expressions
    // Note: TMVA uses a single weight expression for all background trees
    // For proper handling, we'd need to pre-compute weights into the trees
    // For now, use the MC weight expression (majority of background)
    // fakeTau and fakeLepton weights are applied in their respective trees via FR branches
    dataloader->SetBackgroundWeightExpression(weightExpressions[0]);  // Use MC weight as default
    std::cout << "Using MC weight expression for background (note: fakeTau/fakeLepton have their own FR branches)\n";

    std::cout << "allSignal=" << allSignal << "  allBg=" << allBg << "\n";

    // Prepare training and test trees
    // Use empty cut - process-specific selection was already applied when counting events
    // and the trees contain all events (TMVA will handle train/test split)
    TCut emptyCut("");

    // Use 0 for nTrain/nTest to let TMVA use all available events with 50:50 split
    std::string trainingSetup = "SplitMode=Random:NormMode=EqualNumEvents:!V";

    std::cout << "Training setup: " << trainingSetup << "\n";
    std::cout << "Note: Using all available events (no pre-selection in PrepareTrainingAndTestTree)\n";
    dataloader->PrepareTrainingAndTestTree(emptyCut, emptyCut, trainingSetup);

    factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT",
                            // "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
                            // "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=30");
                            // "!H:!V:NTrees=850:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");//trainA: increase MinNodeSize
                            "!H:!V:NTrees=1000:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=30:Shrinkage=0.1");//trainB: increase MinNodeSize
                            // "!H:!V:NTrees=500:MinNodeSize=5%:MaxDepth=3:BoostType=Grad:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=30:Shrinkage=0.1");//trainB: increase MinNodeSize
    // if (Use["BDTB"]) // Bagging
    //   factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTB",
                        //    "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );//default
                        //    "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=30" );
 
//    if (Use["BDTD"]) // Decorrelation + Adaptive Boost
    //   factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTD",
                        //    "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate" );//?strange running time bug

    //!DNN not working yet
      // General layout.
    //   TString layoutString ("Layout=TANH|128,TANH|128,TANH|128,LINEAR");
    //   // Define Training strategy. One could define multiple strategy string separated by the "|" delimiter
    //   TString trainingStrategyString = ("TrainingStrategy=LearningRate=1e-2,Momentum=0.9,"
    //                                     "ConvergenceSteps=20,BatchSize=100,TestRepetitions=1,"
    //                                     "WeightDecay=1e-4,Regularization=None,"
    //                                     "DropConfig=0.0+0.5+0.5+0.5");
    //   // General Options.
    //   TString dnnOptions ("!H:V:ErrorStrategy=CROSSENTROPY:VarTransform=N:"
    //                       "WeightInitialization=XAVIERUNIFORM");
    //   dnnOptions.Append (":"); dnnOptions.Append (layoutString);
    //   dnnOptions.Append (":"); dnnOptions.Append (trainingStrategyString);
    //    // Multi-core CPU implementation.
    // TString cpuOptions = dnnOptions + ":Architecture=CPU";
    // factory->BookMethod(dataloader, TMVA::Types::kDL, "DNN_CPU", cpuOptions);



    factory->TrainAllMethods();
    // Evaluate all MVAs using the set of test events
    factory->TestAllMethods();
    // Evaluate and compare performance of all configured MVAs
    factory->EvaluateAllMethods();
    // Save the output
    outputFile->Close();
    std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
    std::cout << "==> TMVAClassification is done!" << std::endl;

    delete factory;
    delete dataloader;

    return 0;
}

int main(int argc, char const *argv[])
{
    TString inputDir, outDir, variableList;
    TString channel, ifVLL, era;
    Bool_t isTest;
    if (argc < 5)
    {
        std::cout<<"Usage: ./my_program inputDir outDir isTest variableList channel [ifVLL] [era]\n";
        std::cout<<"Running with defaults for testing...\n";
        tmvaBDT_training();
    }
    else
    {
        inputDir = argv[1];
        outDir = argv[2];
        isTest = (std::atoi(argv[3]) != 0);
        variableList = argv[4];
        channel = (argc > 5) ? argv[5] : "1tau1l";
        ifVLL = (argc > 6) ? argv[6] : "";
        era = (argc > 7) ? argv[7] : "2018";
        tmvaBDT_training(inputDir, outDir, isTest, variableList, channel, ifVLL, era);
    }
}