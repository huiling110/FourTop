#include <map>

#include "../include/tauVarMaker.h"
#include "../include/variablesFunctions.h"

TauVarMaker::TauVarMaker(TTree *outTree, TString objName, Int_t type) : ObjVarMaker{outTree, objName, type}
{
    std::cout << "Initialzing the derived TauVarMaker........\n";

    outTree->Branch(objName + "_MHT", &taus_MHT);
    outTree->Branch(objName + "_HT", &taus_HT);
    outTree->Branch(objName + "invariantMass", &taus_invariantMass);
    outTree->Branch(objName + "_minDeltaR", &taus_minDeltaR);
    outTree->Branch(objName + "_taus_genTauNum", &taus_genTauNum);

    std::cout << "Done initialization.............\n";
    std::cout << "\n";
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
    // taus_genTauNum = calGenTauNum(e->tausT_genPartFlav);//!!!
}

void TauVarMaker::clearBranch()
{
    ObjVarMaker::clearBranch();
    taus_MHT = -99;
    taus_HT = -99;
    taus_invariantMass = -99;
    taus_minDeltaR = -99;
    taus_genTauNum = -99;
}

void TauVarMaker::setupLorentzObjs(const EventForMV *e)
{
    // overide base ObjValMaker
    UInt_t objNum = 0;
    switch (m_type)
    {
    case 0:
        objNum = e->tausT_pt.GetSize();
         break;
    case 1:
        objNum = e->tausF_pt.GetSize();
         break;
    case 2:
        objNum = e->tausL_pt.GetSize();
         break;
    }

    // for (UInt_t i = 0; i < e->tausT_pt.GetSize(); i++)
    for (UInt_t i = 0; i < objNum; i++)
    {
        ROOT::Math::PtEtaPhiMVector muLorentz{-99, -99, -99, -99};
        switch (m_type)
        {
        case 0:
            muLorentz = {e->tausT_pt.At(i), e->tausT_eta.At(i), e->tausT_phi[i], e->tausT_mass[i]};
            break;
        case 1:
            muLorentz = {e->tausF_pt.At(i), e->tausF_eta.At(i), e->tausF_phi[i], e->tausF_mass[i]};
            break;
        case 2:
            muLorentz = {e->tausL_pt.At(i), e->tausL_eta.At(i), e->tausL_phi[i], e->tausL_mass[i]};
            break;
        }
        // ROOT::Math::PtEtaPhiMVector muLorentz{e->tausT_pt.At(i), e->tausT_eta.At(i), e->tausT_phi[i], e->tausT_mass[i]};
        objsLorentz.push_back(muLorentz);
    }
};

TauVarMaker::~TauVarMaker(){};