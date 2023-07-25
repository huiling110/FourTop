#include <map>

#include "../include/objVarMaker.h"

ObjVarMaker::ObjVarMaker(TTree *outTree, TString objName, Int_t type) : m_type{type}
{
    //!!!maybe make these basic variables for all object as base class
    std::cout << "Initializing ObjVarMaker.....\n";
    std::cout << "m_type: " << m_type << "\n";

    outTree->Branch(objName + "_num", &muons_num);
    outTree->Branch(objName + "_1pt", &muons_1pt);
    outTree->Branch(objName + "_1eta", &muons_1eta);
    outTree->Branch(objName + "_1phi", &muons_1phi);

    std::cout << "Done initializing ............\n";
    std::cout << "\n";
};

void ObjVarMaker::makeVariables(const EventForMV *e)
// void ObjVarMaker::makeVariables(const &std::vector<ROOT::Math::PtEtaPhiMVector> objsLorentz)
{
    // for derived class, I also need the function to be a exetention, what to do?
    // Answer: write the same function in derived class and then call the base part with base::function()
    // it would be much convenient if we can have a object collection: muonsT
    // or I make a map of object name and object lorentz in this class

    clearBranch();

    setupLorentzObjs(e);
    basicVariables();
};

void ObjVarMaker::basicVariables()
{
    muons_num = objsLorentz.size();
    if (muons_num > 0)
    {
        muons_1pt = objsLorentz[0].Pt();
        muons_1eta = fabs(objsLorentz[0].Eta());
        muons_1phi = fabs(objsLorentz[0].Phi());
    }
}

void ObjVarMaker::clearBranch()
{ //??? derived class should also have a clearBranch()
    muons_num = -99;
    muons_1pt = -99;
    muons_1eta = -99;
    muons_1phi = -99;
    objsLorentz.clear();
};

void ObjVarMaker::setupLorentzObjs(const EventForMV *e)
{
    // to be overiden by derived class
    UInt_t objNum = 0;
    switch (m_type)
    {
    case 0:
        objNum = e->muonsT_pt.GetSize();
        break;
    case 1:
        objNum = e->muonsTopMVAT_pt.GetSize();
        break;
    }
    for (UInt_t i = 0; i < objNum; i++)
    {
        Double_t objPt = -99;
        Double_t objEta = -99;
        Double_t objPhi = -99;
        Double_t objMass = -99;
        switch (m_type)
        {
        case 0:
            objPt = e->muonsT_pt[i];
            objEta = e->muonsT_eta[i];
            objPhi = e->muonsT_phi[i];
            objMass = e->muonsT_mass[i];
            break;
        case 1: //!!!loose and fake muon not in OS
            objPt = e->muonsTopMVAT_pt[i];
            objEta = e->muonsTopMVAT_eta[i];
            objPhi = e->muonsTopMVAT_phi[i];
            objMass = e->muonsTopMVAT_mass[i];
            break;
            // case 2:
            //     objPt = e->muonsL_pt[i];
            //     objEta = e->muonsL_eta[i];
            //     objPhi = e->muonsL_phi[i];
            //     objMass = e->muonsL_mass[i];
            //     break;
        }
        ROOT::Math::PtEtaPhiMVector muLorentz{objPt, objEta, objPhi, objMass};
        objsLorentz.push_back(muLorentz);
    }
};

Int_t ObjVarMaker::getNum(){
    return muons_num;
}

ObjVarMaker::~ObjVarMaker(){};