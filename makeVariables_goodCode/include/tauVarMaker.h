#ifndef TAUVARMAKER_H
#define TAUVARMAKER_H

// #include "TLorentzVector.h"
// #include <Math/Vector4D.h>
// #include "eventReader_forMV.h"
#include "objVarMaker.h"

class TauVarMaker : public ObjVarMaker
{
public:
    TauVarMaker(TTree *outTree, TString objName);
    ~TauVarMaker();
    void makeVariables(const EventForMV *e);
    // void makeVariables(const &std::vector<ROOT::Math::PtEtaPhiMVector> objsLorentz);
    void clearBranch();
    void setupLorentzObjs(const EventForMV *e);

private:
    Double_t taus_MHT = -99;
};

#endif