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
    outTree->Branch(objName + "_minDeltaR", &bjets_minDeltaR);

    std::cout << "Done initilization........\n";
    std::cout << "\n";
};

void BjetVarMaker::setupLorentzObjs(const EventForMV *e)
{//!!!class should be better initialized rather than like this
    // overide base ObjValMaker
        switch (m_type)
        {
        case 0:
            getLorentzVec(e->bjetsM_pt, e->bjetsM_eta, e->bjetsM_phi, e->bjetsM_mass,  objsLorentz);
            break;
        case 1:
            getLorentzVec(e->bjetsL_pt, e->bjetsL_eta, e->bjetsL_phi, e->bjetsL_mass,objsLorentz);
            break;
        case 2:
            getLorentzVec(e->bjetsT_pt, e->bjetsT_eta, e->bjetsT_phi, e->bjetsT_mass,  objsLorentz);
            break;
        case 3:
            getLorentzVec(e->bjetsPNM_pt, e->bjetsPNM_eta, e->bjetsPNM_phi, e->bjetsPNM_mass,  objsLorentz);
            break;
        case 4:
            getLorentzVec(e->bjetsPTM_pt, e->bjetsPTM_eta, e->bjetsPTM_phi, e->bjetsPTM_mass,  objsLorentz);
            break;
        case 5: 
            getLorentzVec(e->bjetsPTT_pt, e->bjetsPTT_eta, e->bjetsPTT_phi, e->bjetsPTT_mass,  objsLorentz);
            break;
        default:
            std::cout<<"Error: BjetVarMaker::setupLorentzObjs() type not found\n";
            break;
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
    bjets_minDeltaR = MinDeltaRSingleCal(objsLorentz);
};

void BjetVarMaker::clearBranch()
{
    ObjVarMaker::clearBranch();
    bjets_MHT = -99;
    bjets_HT = -99;
    bjets_invariantMass = -99;
    bjets_transMass = -99;
    bjets_minDeltaR = -99.;
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