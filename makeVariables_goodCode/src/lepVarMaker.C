#include "../include/lepVarMaker.h"
#include "../include/variablesFunctions.h"

LepVarMaker::LepVarMaker(TTree* outTree, TString objName, const UInt_t type):ObjVarMaker(outTree, objName, type){
   std::cout<<"Initializing LepVarMaker"<<std::endl;

   std::map<UInt_t, TString> lepTypeMap={
       {0, "lepTopMVAT"},
       {1, "lepTopMVAF"},
    //    {2, "lepTopMVAT"},
    };

    outTree->Branch("lepTopMVAT_2invariantMass", &lepTopMVAT_2invariantMass);
    outTree->Branch("lepTopMVAT_2pt", &lepTopMVAT_2pt);
    outTree->Branch("lepTopMVAT_2eta", &lepTopMVAT_2eta);
    outTree->Branch("lepTopMVAT_2phi", &lepTopMVAT_2phi);
    outTree->Branch("lepTopMVAT_2charge", &lepTopMVAT_2charge);

   std::cout<<"Initialization done\n\n";
}

// void LepVarMaker::makeVariables(std::vector<ROOT::Math::PtEtaPhiMVector>& leptonsMVAT){
void LepVarMaker::makeVariables(const EventForMV* e){
    clearBranch();
    setupLorentzObjs(e);
    basicVariables();

    lepTopMVAT_2invariantMass =  muons_num>1? InvariantMassCalculator(objsLorentz): -99;
    lepTopMVAT_2pt = muons_num > 1 ? objsLorentz[1].Pt() : -99;
    lepTopMVAT_2eta = muons_num > 1 ? objsLorentz[1].Eta() : -99;
    lepTopMVAT_2phi = muons_num > 1 ? objsLorentz[1].Phi() : -99;

    //
    // lepTopMVAF_1isTight = ;
    // lepTopMVAF_2isTight = ;
    // lepTopMVAF_1isTightPrompt = ;
    // lepTopMVAF_2isTightPrompt = ;
    
    // lepTopMVAF_FRweight = 1.0;
    // if(lepTopMVAF_1isTight && !lepTopMVAF_2isTight){
    //     lepTopMVAF_FRweight = 1.0; //FR2/1-FR2
    // }
    //for 1tau1l 


}

void LepVarMaker::clearBranch(){
    ObjVarMaker::clearBranch();
    lepTopMVAT_2invariantMass = -99;
    lepTopMVAT_2pt = -99;
    lepTopMVAT_2eta = -99;
    lepTopMVAT_2phi = -99;
}

// void LepVarMaker::setupLorentzObjs(std::vector<ROOT::Math::PtEtaPhiMVector>& leptonsMVAT){
void LepVarMaker::setupLorentzObjs(const EventForMV *e){
    // objsLorentz.clear();
    // for (UInt_t i = 0; i < leptonsMVAT.size(); i++){
    //     objsLorentz.push_back(leptonsMVAT[i]);
    // }
    switch(m_type){
        case 0:
            getLorentzVec(e->elesTopMVAT_pt, e->elesTopMVAT_eta, e->elesTopMVAT_phi, e->elesTopMVAT_mass, eles);
            getLorentzVec(e->muonsTopMVAT_pt, e->muonsTopMVAT_eta, e->muonsTopMVAT_phi, e->muonsTopMVAT_mass, mus);
        // std::vector<ROOT::Math::PtEtaPhiMVector> leptonsMVAT;
        // addLorentzVector(muonTopTVarMaker.getLorentzObjs(), eleTopVarMaker.getLorentzObjs(), leptonsMVAT);//Pt already sorted
            addLorentzVector(mus, eles, objsLorentz);
            break;
        case 1:
            getLorentzVec(e->elesTopMVAF_pt, e->elesTopMVAF_eta, e->elesTopMVAF_phi, e->elesTopMVAF_mass, eles);
            getLorentzVec(e->muonsTopMVAF_pt, e->muonsTopMVAF_eta, e->muonsTopMVAF_phi, e->muonsTopMVAF_mass, mus);
            addLorentzVector(mus, eles, objsLorentz);
            break;
        default:
            break;
    }
}

LepVarMaker::~LepVarMaker(){
    std::cout<<"Deleting LepVarMaker"<<std::endl;
}
