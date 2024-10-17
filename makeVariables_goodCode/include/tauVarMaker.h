#ifndef TAUVARMAKER_H
#define TAUVARMAKER_H

#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include "TTreeReaderValue.h"
// #include "TLorentzVector.h"
// #include <Math/Vector4D.h>
// #include "eventReader_forMV.h"
#include "objVarMaker.h"

class TauVarMaker : public ObjVarMaker
{
public:
    TauVarMaker(TTree *outTree, TString objName, Int_t type = 0);
    ~TauVarMaker();
    void makeVariables( EventForMV *e, const std::vector<ROOT::Math::PtEtaPhiMVector>& leptonsMVAT);
    void tauVariables(const TTreeReaderArray<Double_t>& tau_jetPt, const TTreeReaderArray<Double_t>& tau_jetEta, const TTreeReaderArray<Double_t>& tau_jetPhi, const TTreeReaderArray<Double_t>& tau_jetMass, const TTreeReaderArray<UChar_t>& tau_genPartFlav, const TTreeReaderArray<Int_t>& tau_decayMode, const TTreeReaderArray<Int_t>& tau_charge, const TTreeReaderArray<Int_t>& ele_charge, const TTreeReaderArray<Int_t>& muon_charge, Double_t MET_pt, Double_t MET_phi);

    void clearBranch();
    void setupLorentzObjs(const EventForMV *e);
    Int_t getTauGenNum();

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
    Int_t taus_1decayMode = -99;
    Int_t taus_1prongNum = -99;
    Int_t taus_1lepton1_charge = -99;
    Int_t taus_leptons_charge = -99;
    Double_t taus_1jetPt = -99;
    Double_t taus_1jetEtaAbs = -99;
    Int_t taus_1charge = -99;
    Double_t taus_1neutralIso = -99;
    Int_t taus_1genFlavour = -99;

    Double_t taus_1lepton1_deltaR = -99; //delta R of leading and leading lepton
    Double_t taus_1Met_transMass = -99.;
    Double_t taus_1lepton1Met1_stransMass = -99.;

    Double_t taus_jet_invariantMass = -99.;
    Double_t taus_jet1_Met_transMass = -99.;

    Int_t leptons_2charge = -99;

    Bool_t tausF_1isTight = kFALSE;
    Bool_t tausF_1isTightPrompt = kFALSE;

};

#endif