#include "../include/lepVarMaker.h"
#include "../include/variablesFunctions.h"

LepVarMaker::LepVarMaker(TTree* outTree, TString objName, const UInt_t type):ObjVarMaker(outTree, objName, type){
   std::cout<<"Initializing LepVarMaker"<<std::endl;

   outTree->Branch("lepTopMVAT_2invariantMass", &lepTopMVAT_2invariantMass);

   std::cout<<"Initialization done\n\n";
}

void LepVarMaker::makeVariables(std::vector<ROOT::Math::PtEtaPhiMVector>& leptonsMVAT){
    clearBranch();
    setupLorentzObjs(leptonsMVAT);
    basicVariables();

    lepTopMVAT_2invariantMass = InvariantMassCalculator(objsLorentz);
}

void LepVarMaker::clearBranch(){
    ObjVarMaker::clearBranch();
    lepTopMVAT_2invariantMass = -99;
}

void LepVarMaker::setupLorentzObjs(std::vector<ROOT::Math::PtEtaPhiMVector>& leptonsMVAT){
    objsLorentz.clear();
    for (UInt_t i = 0; i < leptonsMVAT.size(); i++){
        objsLorentz.push_back(leptonsMVAT[i]);
    }
}

LepVarMaker::~LepVarMaker(){
    std::cout<<"Deleting LepVarMaker"<<std::endl;
}
