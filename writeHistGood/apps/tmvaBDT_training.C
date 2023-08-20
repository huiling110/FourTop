
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

int tmvaBDT_training(TString myMethodList = "",
                                         TString outDir = "output/",
                                        TString variableListCsv = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v8tau1elCut_v60fixeJetBtagBug/1tau1l_v1/variableList/varibleList_16.csv",
                                         const TString channel = "1tau1l",
                                         const TString era = "2017",
                                         Bool_t forVariables = false,
                                         Bool_t istest = true){

    std::cout << "era:" << era << "\n";

    TObjArray* tokens = variableListCsv.Tokenize("/");
    TString csvListName = ((TObjString*)tokens->Last())->GetString();
    tokens->Delete();
    std::cout << "csvName=" << csvListName << "\n";

    TString outfile = channel + csvListName;
    TString   outfileName = outDir + outfile + ".root";
    TFile *outputFile = TFile::Open(outfileName, "RECREATE");

    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification");

    return 0;
}

// in main(){
//     TMVAClassification_variableFileInput();
// }