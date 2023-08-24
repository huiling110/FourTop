
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


void readVariableList(TString variableListCsv, std::vector<TString> &variablesName)
{
    std::cout << "reading varibleList: " << variableListCsv << "\n";
    std::ifstream fin(variableListCsv);
    std::string line;
    TString ivariable;
    variablesName.clear();
    while (getline(fin, line))
    {
        ivariable = line;
        if (line.size() > 0)
        {
            // std::cout << "ivariable =" << ivariable << "\n";
            variablesName.push_back(ivariable);
        }
    }
    fin.close();
}

void getProcessesVec(TString inputDir, std::vector<Process>& processVec)
{
    std::vector<TString> allProcesses = {
    "tttt", 
    "ttbar_0l",
    "ttbar_2l",
    "ttbar_1l",
    "qcd_50to100",
    "qcd_100to200",
    "qcd_200to300",
    "qcd_300to500",
    "qcd_500to700",
    "qcd_700to1000",
    "qcd_1000to1500",
    "qcd_1500to2000",
    "qcd_2000toInf",

    "ttG",
    "ttZ",  
    "ttW",
    "ttH_bb", 
    "ttH_nonbb", 

    "wz",
    "ww",
    "zz",

    "st_tZq",
    "st_tW_antitop",
    "st_tW_top",

    "WJetsToLNu_HT-200To400",
    "WJetsToLNu_HT-400To600",
    "WJetsToLNu_HT-600To800",
    "WJetsToLNu_HT-800To1200",
    "WJetsToLNu_HT-1200To2500",
    "WJetsToLNu_HT-2500ToInf",
    };

    processVec.clear();
    for(UInt_t i=0; i<allProcesses.size(); i++){
        Process iPro{inputDir+allProcesses.at(i)+".root"};
        processVec.push_back(iPro);
    }

}

int tmvaBDT_training(
    TString inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4forBDT1tau1lCut_v61fixesLepRemovalBug/mc/",
    TString outDir = "output/",
    TString variableListCsv = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v8tau1elCut_v60fixeJetBtagBug/1tau1l_v1/variableList/varibleList_16.csv",
// const TCut g_weight = "EVENT_genWeight *EVENT_prefireWeight *PUweight_*HLT_weight*tauT_IDSF_weight_new*elesTopMVAT_weight * musTopMVAT_weight * btagShape_weight * btagShapeR ";
    const TString g_weight = "EVENT_genWeight *EVENT_prefireWeight *PUweight_*HLT_weight*tauT_IDSF_weight_new*elesTopMVAT_weight * musTopMVAT_weight * btagWPMedium_weight ", //for btag WP
    Bool_t istest = true)
{

    TObjArray *tokens = variableListCsv.Tokenize("/");
    TString csvListName = ((TObjString *)tokens->Last())->GetString();
    tokens->Delete();
    std::cout << "csvName=" << csvListName << "\n";

    // TString outfile = channel + csvListName;
    TString outfileName = outDir + csvListName + ".root";
    TFile *outputFile = TFile::Open(outfileName, "RECREATE");

    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification");
    TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");
    TMVA::Tools::Instance();
    (TMVA::gConfig().GetVariablePlotting()).fNbins1D = 30;
    TMVA::gConfig().GetVariablePlotting().fNbinsMVAoutput = 30;
    // (TMVA::gConfig().GetIONames()).fWeightFileDir = outDir + "_weight/";
    (TMVA::gConfig().GetIONames()).fWeightFileDir =  "weight/";
    TMVA::gConfig().GetIONames().fWeightFileDirPrefix = outDir; // If a non-nul prefix is set in TMVA::gConfig().GetIONames().fWeightFileDirPrefix the weights will be stored in weightfile_prefix/dataset_name/weight_file_name

    // read input variables from csv
    std::vector<TString> variableList;
    readVariableList(variableListCsv, variableList);
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

    // add signal and bg trees
    Double_t allBg = 0;
    std::vector<Process> processVec;
    getProcessesVec(inputDir, processVec);
    for (UInt_t i=0;i<processVec.size(); i++){
        if(processVec.at(i).getTree()->GetEntries()<=0) continue;
        if(i==0){
            std::cout << "add signal tree: " << processVec.at(i).getName() << "\n";
            dataloader->AddSignalTree(processVec.at(i).getTree(), processVec.at(i).getScale());
        }
        else{
            std::cout << "add bg tree: " << processVec.at(i).getName() << "\n";
            dataloader->AddBackgroundTree(processVec.at(i).getTree(), processVec.at(i).getScale());
            allBg = allBg + processVec.at(i).getTree()->GetEntries();
        }
    }
    std::cout << "signal and bg tree added \n";
    // dataloader->SetSignalWeightExpression(g_weight.GetTitle());
    // dataloader->SetBackgroundWeightExpression(g_weight.GetTitle());
    dataloader->SetSignalWeightExpression(g_weight);
    dataloader->SetBackgroundWeightExpression(g_weight);


    //training setup
    Double_t allSignal = processVec.at(0).getTree()->GetEntries();
    std::cout << "allSignal=" << allSignal << "  allBg=" << allBg << "\n";

    char trainingSetup[60];
    sprintf(trainingSetup, "nTrain_Signal=%f:nTrain_Background=%f:nTest_Signal=0:nTest_Background=0:SplitMode=Random:NormMode=EqualNumEvents:!V", allSignal * 0.6, allBg * 0.6);
    std::cout << trainingSetup << "\n";
    dataloader->PrepareTrainingAndTestTree("", "", trainingSetup); // 60% goes to training, 1tau1l

    factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT",
                            // "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
                            "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=30");
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
    TString weight;
    if(argc<3){
        std::cout<<"not enough input\n";
        tmvaBDT_training();
    }else{
        inputDir = boost::lexical_cast<TString>(argv[0]) ;
        outDir = boost::lexical_cast<TString>(argv[1]);
        variableList = boost::lexical_cast<TString>(argv[2]);
        weight = boost::lexical_cast<TString>(argv[3]);
        tmvaBDT_training(inputDir, outDir, variableList, weight);
    }
}