#ifndef BJETVARMAKER_H
#define BJETVARMAKER_H

#include "objVarMaker.h"

class BjetVarMaker : public ObjVarMaker
{
public:
    BjetVarMaker(TTree *outTree, TString objName, Int_t type = 0);
    ~BjetVarMaker();
    void makeVariables( EventForMV *e, const std::vector<ROOT::Math::PtEtaPhiMVector> &leptons, const std::vector<ROOT::Math::PtEtaPhiMVector> &taus);
    void clearBranch();
    void setupLorentzObjs(const EventForMV *e);
    Int_t getJet_num();

private:
    Double_t bjets_MHT = -99;
    Double_t bjets_HT = -99;
    Double_t bjets_invariantMass = -99;
    Double_t bjets_transMass = -99;
    Double_t bjets_minDeltaR = -99.;
    Double_t bjets_2leptons2_stransMass = -99.;
    Double_t bjets_2tau1lep1_stransMass = -99.;
    Double_t bjets_2MET_stransMass = -99.;
    Double_t bjets_leptons_minDeltaR = -99.;
    Double_t bjets_taus_minDeltaR = -99.;

    Double_t bjets_2pt = -99.;
    Double_t bjets_3pt = -99.;
};



#endif