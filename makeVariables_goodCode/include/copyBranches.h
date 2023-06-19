#ifndef COPYBRANCHES_H
#define COPYBRANCHES_H

#include "eventReader_forMV.h"

class CopyBranches
{
public:
    CopyBranches(TTree *outTree);
    ~CopyBranches();
    void makeVariables(EventForMV *e);
    void clearBranch();

private:
    // output branches
    Int_t PV_npvsGood;

};

#endif