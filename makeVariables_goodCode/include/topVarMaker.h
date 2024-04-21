#ifndef TOPVARMAKER_H
#define TOPVARMAKER_H
#include "objVarMaker.h"

class TopVarMaker : public ObjVarMaker
{
public:
    TopVarMaker(TTree *outTree, TString objName, Int_t type = 0);
    ~TopVarMaker();
    void makeVariables(EventForMV *e, const std::vector<ROOT::Math::PtEtaPhiMVector> &jets, std::vector<ROOT::Math::PtEtaPhiMVector> &bjets, const std::vector<ROOT::Math::PtEtaPhiMVector> &leptons, const std::vector<ROOT::Math::PtEtaPhiMVector> &taus);
    void clearBranch();
    void setupLorentzObjs(const EventForMV *e);

private:
    Double_t tops_MHT = -99;
    Double_t tops_HT = -99;
    Double_t tops_invariantMass = -99;
};
#endif