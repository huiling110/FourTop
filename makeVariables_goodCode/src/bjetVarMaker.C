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
    // for (UInt_t i = 0; i < objNum; i++)
    // {
        // ROOT::Math::PtEtaPhiMVector muLorentz{-99, -99, -99, -99};
        switch (m_type)
        {
        case 0:
            // muLorentz = {e->bjetsM_pt[i], e->bjetsM_eta[i], e->bjetsM_phi[i], e->bjetsM_mass[i]};
            getLorentzVec(e->bjetsM_pt, e->bjetsM_eta, e->bjetsM_phi, e->bjetsM_mass,  objsLorentz);
            break;
        case 1:
            // muLorentz = {e->bjetsL_pt[i], e->bjetsL_eta[i], e->bjetsL_phi[i], e->bjetsL_mass[i]};
            getLorentzVec(e->bjetsL_pt, e->bjetsL_eta, e->bjetsL_phi, e->bjetsL_mass,objsLorentz);
            break;
        case 2:
            // muLorentz = {e->bjetsT_pt[i], e->bjetsT_eta[i], e->bjetsT_phi[i], e->bjetsT_mass[i]};
            getLorentzVec(e->bjetsT_pt, e->bjetsT_eta, e->bjetsT_phi, e->bjetsT_mass,  objsLorentz);
            break;
        case 3:
            // muLorentz = {e->bjetsPNM_pt[i], e->bjetsPNM_eta[i], e->bjetsPNM_phi[i], e->bjetsPNM_mass[i]};
            getLorentzVec(e->bjetsPNM_pt, e->bjetsPNM_eta, e->bjetsPNM_phi, e->bjetsPNM_mass,  objsLorentz);
            break;
        case 4:
            // muLorentz = {e->bjetsPTM_pt[i], e->bjetsPTM_eta[i], e->bjetsPTM_phi[i], e->bjetsPTM_mass[i]};
            getLorentzVec(e->bjetsPTM_pt, e->bjetsPTM_eta, e->bjetsPTM_phi, e->bjetsPTM_mass,  objsLorentz);
            break;
        case 5: 
            getLorentzVec(e->bjetsPTT_pt, e->bjetsPTT_eta, e->bjetsPTT_phi, e->bjetsPTT_mass,  objsLorentz);
            break;
        default:
            std::cout<<"Error: BjetVarMaker::setupLorentzObjs() type not found\n";
            break;
        }
        // objsLorentz.push_back(muLorentz);
    // }
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