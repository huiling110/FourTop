#include <map>

#include "../include/eleVarMaker.h"
#include "../include/variablesFunctions.h"

EleVarMaker::EleVarMaker(TTree *outTree, TString objName, Int_t type) : ObjVarMaker{outTree, objName, type}
{
    std::cout << "Initialzing the derived EleVarMaker........\n";


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
}

void EleVarMaker::clearBranch()
{
    ObjVarMaker::clearBranch();
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
    default:
        break;
    }

};

EleVarMaker::~EleVarMaker(){};