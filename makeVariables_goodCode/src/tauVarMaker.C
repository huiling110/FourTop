#include <map>

#include "../include/tauVarMaker.h"
#include "../include/variablesFunctions.h"

TauVarMaker::TauVarMaker(TTree *outTree, TString objName) : ObjVarMaker{outTree, objName}
{
    std::cout << "Initialzing the derived TauVarMaker........\n";

    outTree->Branch(objName + "_MHT", &taus_MHT);
    outTree->Branch(objName + "_HT", &taus_HT);
    outTree->Branch(objName + "invariantMass", &taus_invariantMass);
    outTree->Branch(objName + "_minDeltaR", &taus_minDeltaR);

    std::cout << "Done initialization.............\n";
};

void TauVarMaker::makeVariables(const EventForMV *e)
{
    // for derived class, I also need the function to be a exetention, what to do?
    // Answer: write the same function in derived class and then call the base part with base::function()
    // it would be much convenient if we can have a object collection: muonsT
    // or I make a map of object name and object lorentz in this class

    clearBranch();

    setupLorentzObjs(e); //!!! crucial to overide base class!!!

    ObjVarMaker::basicVariables();

    taus_MHT = MHTcalculator(objsLorentz); // 900;return the pt sum of,vetctor sum
    taus_HT = HTcalculator(objsLorentz);
    taus_invariantMass = InvariantMassCalculator(objsLorentz);
    // taus_minDeltaR = MinDeltaRSingleCal(objsLorentz);//!!!
}

void TauVarMaker::clearBranch()
{
    ObjVarMaker::clearBranch();
    taus_MHT = -99;
    taus_HT = -99;
    taus_invariantMass = -99;
    taus_minDeltaR = -99;
}

void TauVarMaker::setupLorentzObjs(const EventForMV *e)
{
    // overide base ObjValMaker
    for (UInt_t i = 0; i < e->tausT_pt.GetSize(); i++)
    {
        ROOT::Math::PtEtaPhiMVector muLorentz{e->tausT_pt.At(i), e->tausT_eta.At(i), e->tausT_phi[i], e->tausT_mass[i]};
        objsLorentz.push_back(muLorentz);
    }
};

TauVarMaker::~TauVarMaker(){};