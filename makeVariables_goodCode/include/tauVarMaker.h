#ifndef TAUVARMAKER_H
#define TAUVARMAKER_H

// #include "TLorentzVector.h"
// #include <Math/Vector4D.h>
// #include "eventReader_forMV.h"
#include "objVarMaker.h"

class TauVarMaker : public ObjVarMaker
{
public:
    TauVarMaker(TTree *outTree, TString objName, Int_t type = 0);
    ~TauVarMaker();
    void makeVariables(const EventForMV *e);
    // void makeVariables(const &std::vector<ROOT::Math::PtEtaPhiMVector> objsLorentz);
    void clearBranch();
    void setupLorentzObjs(const EventForMV *e);

private:
    Double_t taus_MHT = -99;
    Double_t taus_HT = -99;
    Double_t taus_invariantMass = -99;
    Double_t taus_minDeltaR = -99;
    Int_t taus_genTauNum = -99;
    Double_t taus_leptonsT_transMass = -99; //!!!later
    Double_t taus_leptonsT_invariantMass = -99;
    Double_t taus_leptonsTMVA_minDeltaR = -99;
    Int_t taus_leptonsTopMVA_chargeMulti = -99;
    Double_t taus_prongNum = -99;
    Double_t taus_1decayMode = -99;
    Double_t taus_1jetPt = -99;
    Double_t taus_1jetEtaAbs = -99;
    Bool_t taus_1charge = -99;
    Double_t taus_1neutralIso = -99;
};

#endif