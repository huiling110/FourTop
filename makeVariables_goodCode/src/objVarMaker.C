#include <map>

#include "../include/objVarMaker.h"

ObjVarMaker::ObjVarMaker(TTree *outTree,  TString objName)  
{
    //!!!maybe make these basic variables for all object as base class
    std::cout << "Initializing ObjVarMaker.....\n";
    // std::map<Int_t, TString> typeObjMap = {
    //     {0, "T"},
    //     {1, "F"},
    //     {2, "L"},
    // };

    // outTree->Branch("muons" + typeObjMap[m_type] + "_num", &muons_num);
    // outTree->Branch("muons" + typeObjMap[m_type] + "_1pt", &muons_1pt);
    // outTree->Branch("muons" + typeObjMap[m_type] + "_1eta", &muons_1eta);
    // outTree->Branch("muons" + typeObjMap[m_type] + "_1phi", &muons_1phi);
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
    //Answer: write the same function in derived class and then call the base part with base::function()
    //it would be much convenient if we can have a object collection: muonsT
    //or I make a map of object name and object lorentz in this class

    clearBranch();

    setupLorentzObjs(e);
    basicVariables();
};

void ObjVarMaker::basicVariables(){
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

void ObjVarMaker::setupLorentzObjs(const EventForMV* e){
    // to be overiden by derived class
    for(UInt_t i=0; i<e->muonsT_pt.GetSize(); i++){
        ROOT::Math::PtEtaPhiMVector muLorentz{e->muonsT_pt.At(i), e->muonsT_eta.At(i), e->muonsT_phi[i], e->muonsT_mass[i]};
        objsLorentz.push_back(muLorentz);
    }
};

ObjVarMaker::~ObjVarMaker(){};