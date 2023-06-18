#ifndef OBJVARMAKER_H
#define OBJVARMAKER_H

#include "eventReader_forMV.h"

class ObjVarMaker
{
public:
    // ObjVarMaker(TTree *outTree, const Int_t type = 0);
    ObjVarMaker(TTree *outTree, const Int_t type, TString objName);
    ~ObjVarMaker();
    void makeVariables(const EventForMV *e);
    void clearBranch();

private:
    Int_t m_type = 0;
    // output branches
    Int_t muons_num = -99;
    Double_t muons_1pt = -99;
    Double_t muons_1eta = -99;
    Double_t muons_1phi = -99;
};

#endif