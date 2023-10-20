
#include "TString.h"
#include "TFile.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"

#include "../../myLibrary/commenFunction.h"
#include "../EYandSP_usingClass_v3.h"



void MVATraining(
                TString outDir = "output/",
                TString variableListCsv = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v8tau1elCut_v60fixeJetBtagBug/1tau1l_v1/variableList/varibleList_16.csv",
                const TString era = "2018",
                Bool_t istest = true

){
    //assumming that input tree already have cut on SR
    //training with 'BDT' and 'BDTD'
    TString outfileName = outDir + "BDTTraing.root";
    TFile *outputFile = TFile::Open(outfileName, "RECREATE");

    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification");// The first argument is the user-defined job name that will reappear in the names of the weight files containing the training results.
    TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");
    (TMVA::gConfig().GetVariablePlotting()).fNbins1D = 30;
    TMVA::gConfig().GetVariablePlotting().fNbinsMVAoutput = 30;
    // (TMVA::gConfig().GetIONames()).fWeightFileDir = outfile + "_weight/";
    (TMVA::gConfig().GetIONames()).fWeightFileDir = outDir + "_weight/";
    // TMVA::gConfig().GetIONames().fWeightFileDirPrefix = outDir; // If a non-nul prefix is set in TMVA::gConfig().GetIONames().fWeightFileDirPrefix the weights will be stored in weightfile_prefix/dataset_name/weight_file_name

    std::vector<TString> variableNames;
    TTTT::getVarFromFile(variableListCsv, variableNames);
    for (UInt_t i=0; i<variableNames.size(); i++){
        TString ivar = variableNames.at(i);
        if (ivar.Contains("num") || ivar.Contains("charge"))
        {
            dataloader->AddVariable(ivar, 'I');
        }
        else
        {
            dataloader->AddVariable(ivar, 'F');
        }
    }

    dataloader->AddSignalTree(eraProcess_Map[era][0].getEventTree(), TTTT::lumiMap.at(era) * eraProcess_Map[era][0].getScale());
    for (UInt_t p = 1; p < eraProcess_Map[era].size(); p++)
    {
        if (eraProcess_Map[era][p].getEventTree()->GetEntries() == 0)
        {
            std::cout << "empty process: " << eraProcess_Map[era][p].getProcessName() << "\n";
            continue;
        }
        std::cout << "adding background for training: " << eraProcess_Map[era][p].getProcessName() << "\n";
        dataloader->AddBackgroundTree(eraProcess_Map[era][p].getEventTree(), TTTT::lumiMap.at(era) * eraProcess_Map[era][p].getScale());
    }
    dataloader->SetSignalWeightExpression(g_weight.GetTitle());
    dataloader->SetBackgroundWeightExpression(g_weight.GetTitle());


    Double_t allSignal = eraProcess_Map[era][0].getEventTree()->GetEntries();
    Double_t allBg = 0;
    for (UInt_t i = 1; i < eraProcess_Map[era].size(); i++)
    {
        allBg = allBg + eraProcess_Map[era][i].getEventTree()->GetEntries();
    }
    std::cout << "allSignalEvents: " << allSignal << "\n";
    std::cout << "allBgEvents: " << allBg << "\n";

    char trainingSetup[100];
    sprintf(trainingSetup, "nTrain_Signal=%f:nTrain_Background=%f:nTest_Signal=0:nTest_Background=0:SplitMode=Random:NormMode=EqualNumEvents:!V", allSignal * 0.6, allBg * 0.6);
    if (istest)
    {
        dataloader->PrepareTrainingAndTestTree(
            // cutForSandB, cutForSandB,
            "", "",
            "nTrain_Signal=1000:nTrain_Background=1000:nTest_Signal=1000:nTest_Background=1000:SplitMode=Random:NormMode=NumEvents:!V");
    }
    else
    {
        dataloader->PrepareTrainingAndTestTree("", "", trainingSetup); // 60% goes to training, 1tau1l
                                                                       // means raw entries
                                                                       // dataloader->PrepareTrainingAndTestTree( cutForSandB, cutForSandB, trainingSetup );
    }


    factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT",
                            "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=30");
    factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDTD",
                            "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate");

    // Train MVAs using the set of training events
    factory->TrainAllMethods();
    // Evaluate all MVAs using the set of test events
    factory->TestAllMethods();
    // Evaluate and compare performance of all configured MVAs
    factory->EvaluateAllMethods();
    // --------------------------------------------------------------

    // Save the output
    outputFile->Close();
    std::cout << "input dir: " << baseDir << endl;
    std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
    std::cout << "==> TMVAClassification is done!" << std::endl;

    delete factory;
    delete dataloader;
}