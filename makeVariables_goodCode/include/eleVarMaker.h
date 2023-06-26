#ifndef ELEVARMAKER_H
#define ELEVARMAKER_H

#include "objVarMaker.h"

class EleVarMaker : public ObjVarMaker
{
public:
    EleVarMaker(TTree *outTree, TString objName, Int_t type = 0);
    ~EleVarMaker();
    void makeVariables(const EventForMV *e);
    void clearBranch();
    void setupLorentzObjs(const EventForMV *e);
};

#endif