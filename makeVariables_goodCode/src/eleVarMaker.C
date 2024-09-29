#include <map>

#include "../include/eleVarMaker.h"
#include "../include/variablesFunctions.h"

EleVarMaker::EleVarMaker(TTree *outTree, TString objName, Int_t type) : ObjVarMaker{outTree, objName, type}
{
    std::cout << "Initialzing the derived EleVarMaker........\n";

    outTree->Branch(objName + "_2pt", &elesTopMVA_2pt);
    outTree->Branch(objName + "_2eta", &elesTopMVA_2eta);
    outTree->Branch(objName + "_2phi", &elesTopMVA_2phi);
    outTree->Branch(objName + "_2mass", &elesTopMVA_2mass);

    std::cout << "Done initialization.............\n";
    std::cout << "\n";
};

void EleVarMaker::makeVariables(const EventForMV *e)
{
    // for derived class, I also need the function to be a exetention, what to do?
    // Answer: write the same function in derived class and then call the base part with base::function()

    clearBranch();

    setupLorentzObjs(e); //!!! crucial to overide base class!!!

    ObjVarMaker::basicVariables();

    elesTopMVA_2pt = muons_num>1 ? objsLorentz[1].Pt() : -99.;
    elesTopMVA_2eta = muons_num>1 ? objsLorentz[1].Eta() : -99.;
    elesTopMVA_2phi = muons_num>1 ? objsLorentz[1].Phi() : -99.;
    elesTopMVA_2mass = muons_num>1 ? objsLorentz[1].M() : -99.;


}

void EleVarMaker::clearBranch()
{
    ObjVarMaker::clearBranch();

    elesTopMVA_2pt = -99.;
    elesTopMVA_2eta = -99.;
    elesTopMVA_2phi = -99.;
    elesTopMVA_2mass = -99.;
}

void EleVarMaker::setupLorentzObjs(const EventForMV *e)
{
    // overide base ObjValMaker
    //!!! it means for every event we need to evaluate m_type
    switch(m_type){
    case 0:
        getLorentzVec(e->elesMVAT_pt, e->elesMVAT_eta, e->elesMVAT_phi, e->elesMVAT_mass, objsLorentz);
        break;
    case 1:
        getLorentzVec(e->elesTopMVAT_pt, e->elesTopMVAT_eta, e->elesTopMVAT_phi, e->elesTopMVAT_mass, objsLorentz);
        break;
    case 2:
        getLorentzVec(e->elesTopMVAF_pt, e->elesTopMVAF_eta, e->elesTopMVAF_phi, e->elesTopMVAF_mass, objsLorentz);
        break;
    case 3:
       getLorentzVec(e->muonsTopMVAT_pt, e->muonsTopMVAT_eta, e->muonsTopMVAT_phi, e->muonsTopMVAT_mass, objsLorentz);
         break;
    case 4:
       getLorentzVec(e->muonsTopMVAF_pt, e->muonsTopMVAF_eta, e->muonsTopMVAF_phi, e->muonsTopMVAF_mass, objsLorentz);
         break;
    default:
        break;
    }

};

EleVarMaker::~EleVarMaker(){};