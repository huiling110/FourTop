#include <map>

#include "../include/copyBranches.h"

CopyBranches::CopyBranches(TTree *outTree)
{
    //!!!maybe make these basic variables for all object as base class
    std::cout << "Initializing CopyBranches.....\n";

    outTree->Branch("PV_npvsGood", &PV_npvsGood);

    std::cout << "Done initializing ............\n";
    std::cout << "\n";
};

void CopyBranches::makeVariables(EventForMV *e)
{
    // clearBranch();
    PV_npvsGood = *e->PV_npvsGood_;

};


void CopyBranches::clearBranch()
{ //??? derived class should also have a clearBranch()
};


CopyBranches::~CopyBranches(){};