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
{
    // for derived class, I also need the function to be a exetention, what to do?
    //Answer: write the same function in derived class and then call the base part with base::function()
    clearBranch();

    muons_num = e->muonsT_pt.GetSize();
    if (muons_num > 0)
    {
        muons_1pt = e->muonsT_pt.At(0);
        muons_1eta = e->muonsT_eta.At(0);
        muons_1phi = e->muonsT_phi.At(0);
    }
}

void ObjVarMaker::clearBranch()
{ //??? derived class should also have a clearBranch()
    muons_num = -99;
    muons_1pt = -99;
    muons_1eta = -99;
    muons_1phi = -99;
};

ObjVarMaker::~ObjVarMaker(){};