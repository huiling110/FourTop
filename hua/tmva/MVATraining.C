
#include "TString.h"
#include "TFile.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"

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
    (TMVA::gConfig().GetIONames()).fWeightFileDir = outfile + "_weight/";
    TMVA::gConfig().GetIONames().fWeightFileDirPrefix = outDir; // If a non-nul prefix is set in TMVA::gConfig().GetIONames().fWeightFileDirPrefix the weights will be stored in weightfile_prefix/dataset_name/weight_file_name

    std::vector<TString> variableNames;
    TTTT::getVarFromFile(variableListCsv, variableNames);

}