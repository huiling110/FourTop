#include "../include/bjetVarMaker.h"
#include "../include/variablesFunctions.h"

BjetVarMaker::BjetVarMaker(TTree *outTree, TString objName, Int_t type) : ObjVarMaker(outTree, objName, type)
{
    std::cout << "Initialize BjetVarMaker class..................................\n";
    std::cout << "objName=" << objName << "  type=" << type << "\n";
    std::cout << "Done initializing BjetVarMaker class................................\n";

    outTree->Branch(objName + "_MHT", &bjets_MHT);
    outTree->Branch(objName + "_HT", &bjets_HT);
    outTree->Branch(objName + "_invariantMass", &bjets_invariantMass);
    outTree->Branch(objName + "_transMass", &bjets_transMass);

    std::cout << "Done initilization........\n";
    std::cout << "\n";
};

void BjetVarMaker::setupLorentzObjs(const EventForMV *e)
{//!!!class should be better initialized rather than like this
    // overide base ObjValMaker
    UInt_t objNum = 0;
    switch (m_type)
    {
    case 0:
        objNum = e->bjetsM_pt.GetSize();
        break;
    case 1:
        objNum = e->bjetsL_pt.GetSize();
        break;
    case 2:
        objNum = e->bjetsT_pt.GetSize();
        break;
    case 3:
        objNum = e->bjetsPNM_pt.GetSize();
        break;
    }

    for (UInt_t i = 0; i < objNum; i++)
    {
        ROOT::Math::PtEtaPhiMVector muLorentz{-99, -99, -99, -99};
        switch (m_type)
        {
        case 0:
            muLorentz = {e->bjetsM_pt[i], e->bjetsM_eta[i], e->bjetsM_phi[i], e->bjetsM_mass[i]};
            break;
        case 1:
            muLorentz = {e->bjetsL_pt[i], e->bjetsL_eta[i], e->bjetsL_phi[i], e->bjetsL_mass[i]};
            break;
        case 2:
            muLorentz = {e->bjetsT_pt[i], e->bjetsT_eta[i], e->bjetsT_phi[i], e->bjetsT_mass[i]};
            break;
        case 3:
            muLorentz = {e->bjetsPNM_pt[i], e->bjetsPNM_eta[i], e->bjetsPNM_phi[i], e->bjetsPNM_mass[i]};
            break;
        }
        objsLorentz.push_back(muLorentz);
    }
}

void BjetVarMaker::makeVariables(const EventForMV *e)
{
    ObjVarMaker::reportEntry("BjetVarMaker::makeVariables()");
    clearBranch();
    setupLorentzObjs(e);
    ObjVarMaker::basicVariables();

    bjets_MHT = HTcalculator(objsLorentz);
    bjets_HT = MHTcalculator(objsLorentz);
    bjets_invariantMass = InvariantMassCalculator(objsLorentz);
    bjets_transMass = TransMassCal(objsLorentz);
};

void BjetVarMaker::clearBranch()
{
    ObjVarMaker::clearBranch();
    bjets_MHT = -99;
    bjets_HT = -99;
    bjets_invariantMass = -99;
    bjets_transMass = -99;
};

Int_t BjetVarMaker::getJet_num()
{
    return muons_num;
};
 
BjetVarMaker::~BjetVarMaker()
{
    std::cout << "Done BjetVarMaker class......................\n";
    std::cout << "\n";
};