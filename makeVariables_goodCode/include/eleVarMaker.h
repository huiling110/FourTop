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

private:

    Double_t elesTopMVA_2pt = -99.;
    Double_t elesTopMVA_2eta = -99.;
    Double_t elesTopMVA_2phi = -99.;
    Double_t elesTopMVA_2mass = -99.;
};

#endif