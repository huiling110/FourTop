#include "../include/lepVarMaker.h"
#include "../include/variablesFunctions.h"

LepVarMaker::LepVarMaker(TTree* outTree, TString objName, const UInt_t type):ObjVarMaker(outTree, objName, type){
   std::cout<<"Initializing LepVarMaker"<<std::endl;

   outTree->Branch("lepTopMVAT_2invariantMass", &lepTopMVAT_2invariantMass);
    outTree->Branch("lepTopMVAT_2pt", &lepTopMVAT_2pt);
    outTree->Branch("lepTopMVAT_2eta", &lepTopMVAT_2eta);
    outTree->Branch("lepTopMVAT_2phi", &lepTopMVAT_2phi);

   std::cout<<"Initialization done\n\n";
}

void LepVarMaker::makeVariables(std::vector<ROOT::Math::PtEtaPhiMVector>& leptonsMVAT){
    clearBranch();
    setupLorentzObjs(leptonsMVAT);
    basicVariables();

    lepTopMVAT_2invariantMass = InvariantMassCalculator(objsLorentz);
    lepTopMVAT_2pt = muons_num > 1 ? objsLorentz[1].Pt() : -99;
    lepTopMVAT_2eta = muons_num > 1 ? objsLorentz[1].Eta() : -99;
    lepTopMVAT_2phi = muons_num > 1 ? objsLorentz[1].Phi() : -99;
}

void LepVarMaker::clearBranch(){
    ObjVarMaker::clearBranch();
    lepTopMVAT_2invariantMass = -99;
    lepTopMVAT_2pt = -99;
    lepTopMVAT_2eta = -99;
    lepTopMVAT_2phi = -99;
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
