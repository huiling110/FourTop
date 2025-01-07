#ifndef BJETVARMAKER_H
#define BJETVARMAKER_H

#include "objVarMaker.h"
#include "JESVariation.h"   

class BjetVarMaker : public ObjVarMaker
{
public:
    BjetVarMaker(TTree *outTree, TString objName, Int_t type = 0, UChar_t JESVariation = 0, UChar_t JESType = 0);
    ~BjetVarMaker();
    void makeVariables( EventForMV *e, const std::vector<ROOT::Math::PtEtaPhiMVector> &leptons, const std::vector<ROOT::Math::PtEtaPhiMVector> &tausT, const std::vector<ROOT::Math::PtEtaPhiMVector> &tausF, JESVariation& jesVariation, Double_t METpt, Double_t METphi);
    void clearBranch();
    void setupLorentzObjs(const EventForMV *e, JESVariation& jesVariation);
    Int_t getJet_num();

private:
    const UChar_t m_JESType = 0;
    const UChar_t m_JESVariation = 0;

    Double_t bjets_MHT = -99;
    Double_t bjets_HT = -99;
    Double_t bjets_invariantMass = -99;
    Double_t bjets_transMass = -99;
    Double_t bjets_minDeltaR = -99.;
    Double_t bjets_2leptons2_stransMass = -99.;
    Double_t bjets_2tauT1lep1_stransMass = -99.;
    Double_t bjets_2tauF1lep1_stransMass = -99.;
    Double_t bjets_2MET_stransMass = -99.;
    Double_t bjets_leptons_minDeltaR = -99.;
    Double_t bjets_tausT_minDeltaR = -99.;
    Double_t bjets_tausF_minDeltaR = -99.;

    Double_t bjets_2pt = -99.;
    Double_t bjets_3pt = -99.;
};



#endif