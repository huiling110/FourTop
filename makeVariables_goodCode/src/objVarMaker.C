#include <map>

#include "../include/objVarMaker.h"
#include "../include/variablesFunctions.h"

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
    reportEntry("ObjVarMaker::makeVariables");

    clearBranch();

    setupLorentzObjs(e);
    basicVariables();
};

void ObjVarMaker::reportEntry(TString className){
    if(m_entry==0){
        std::cout<<"running "<<className<<"\n";
    }
    m_entry++;
}

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
    // UInt_t objNum = 0;
    switch (m_type)
    {
    case 0:
        getLorentzVec(e->muonsT_pt, e->muonsT_eta, e->muonsT_phi, e->muonsT_mass, objsLorentz);
        break;
    case 1:
        getLorentzVec(e->muonsTopMVAT_pt, e->muonsTopMVAT_eta, e->muonsTopMVAT_phi, e->muonsTopMVAT_mass, objsLorentz);
        break;
    }
};


Int_t ObjVarMaker::getNum(){
    return muons_num;
}



// Provide read-only access to objsLorentz
const std::vector<ROOT::Math::PtEtaPhiMVector>& ObjVarMaker::getLorentzObjs(){
    return objsLorentz;
}

// const std::vector<ROOT::Math::PtEtaPhiMVector>& getObjsLorentz() const {
//     return objsLorentz;
// }

ObjVarMaker::~ObjVarMaker(){};