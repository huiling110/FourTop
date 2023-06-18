#include <map>

#include "../include/tauVarMaker.h"

TauVarMaker::TauVarMaker(TTree *outTree, TString objName) : ObjVarMaker{outTree, objName} {};

void TauVarMaker::makeVariables(const EventForMV *e)
// void TauVarMaker::makeVariables(const &std::vector<ROOT::Math::PtEtaPhiMVector> objsLorentz)
{
    // for derived class, I also need the function to be a exetention, what to do?
    // Answer: write the same function in derived class and then call the base part with base::function()
    // it would be much convenient if we can have a object collection: muonsT
    // or I make a map of object name and object lorentz in this class

    clearBranch();

    setupLorentzObjs(e);
    muons_num = objsLorentz.size();
    if (muons_num > 0)
    {
        muons_1pt = objsLorentz[0].Pt();
        muons_1eta = fabs(objsLorentz[0].Eta());
        muons_1phi = fabs(objsLorentz[0].Phi());
    }
}

void TauVarMaker::setupLorentzObjs(const EventForMV *e)
{
    // to be overiden by derived class
    for (UInt_t i = 0; i < e->tausT_pt.GetSize(); i++)
    {
        ROOT::Math::PtEtaPhiMVector muLorentz{e->tausT_pt.At(i), e->tausT_eta.At(i), e->tausT_phi[i], e->tausT_mass[i]};
        objsLorentz.push_back(muLorentz);
    }
};

TauVarMaker::~TauVarMaker(){};