#include <map>

#include "../include/muonVarMaker.h"

MuonVarMaker::MuonVarMaker(TTree *outTree, const Int_t type) : m_type{type}
{
    //!!!maybe make these basic variables for all object as base class
    std::cout << "Initializing MuonVarMaker.....\n";
    std::map<Int_t, TString> typeObjMap = {
        {0, "T"},
        {1, "F"},
        {2, "L"},
    };

    outTree->Branch("muons" + typeObjMap[m_type] + "_num", &muons_num);
    outTree->Branch("muons" + typeObjMap[m_type] + "_1pt", &muons_1pt);

    std::cout << "Done initializing ............\n";
    std::cout << "\n";
};

void MuonVarMaker::makeVariables(const EventForMV *e)
{
    clearBranch();

    muons_num = e->muonsT_pt.GetSize();
    if (muons_num > 0)
    {
        muons_1pt = e->muonsT_pt.At(0);
        muons_1eta = e->muonsT_eta.At(0);
        muons_1phi = e->muonsT_phi.At(0);
    }
}

void MuonVarMaker::clearBranch()
{
    muons_num = -99;
    muons_1pt = -99;
    muons_1eta = -99;
    muons_1phi = -99;
};

MuonVarMaker::~MuonVarMaker(){};