

#include <fstream>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

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
    const TString channel = "1tau1l",
    const TString era = "2017",
    Bool_t forVariables = false,
    Bool_t istest = true)
{

    std::cout << "era:" << era << "\n";

    TObjArray *tokens = variableListCsv.Tokenize("/");
    TString csvListName = ((TObjString *)tokens->Last())->GetString();
    tokens->Delete();
    std::cout << "csvName=" << csvListName << "\n";

    TString outfile = channel + csvListName;
    TString outfileName = outDir + outfile + ".root";
    TFile *outputFile = TFile::Open(outfileName, "RECREATE");

    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification");
    TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");
    (TMVA::gConfig().GetVariablePlotting()).fNbins1D = 30;
    TMVA::gConfig().GetVariablePlotting().fNbinsMVAoutput = 30;
    (TMVA::gConfig().GetIONames()).fWeightFileDir = outfile + "_weight/";
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
    //  allProcessMap
    // Process tttt{inputDir + "tttt.root"};
    // Process ttbar_0l{inputDir + "ttbar_0l.root"};
    // Process ttbar_1l{inputDir + "ttbar_1l.root"};
    // Process ttbar_2l{inputDir + "ttbar_2l.root"};
    std::vector<Process> processVec;
    getProcessesVec(inputDir, processVec);
    for (UInt_t i=0;i<processVec.size(); i++){
        if(i==0){
            dataloader->AddSignalTree(processVec.at(i).getTree(), processVec.at(i).getScale());
        }
        else{
            dataloader->AddBackgroundTree(processVec.at(i).getTree(), processVec.at(i).getScale());
        }
    }
    std::cout << "signal and bg tree added \n";

    return 0;
}

int main()
{
    tmvaBDT_training();
}