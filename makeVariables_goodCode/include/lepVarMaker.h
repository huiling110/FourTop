#ifndef LEPVARMAKER_H
#define LEPVARMAKER_H

#include <TH2D.h>
#include "objVarMaker.h"

class LepVarMaker : public ObjVarMaker 
{
public:
    LepVarMaker(TTree* tree, TString era, TString objName="lepTopMVAT", UInt_t type=0);
    ~LepVarMaker();
    void makeVariables(const EventForMV* e);
    void clearBranch();
    // void setupLorentzObjs(std::vector<ROOT::Math::PtEtaPhiMVector>& leptonsMVAT);
    void setupLorentzObjs(const EventForMV *e);

private:
    TString m_era;
    Double_t lepTopMVAT_2invariantMass;
    Bool_t lepTopMVAT_2charge;
    Double_t lepTopMVAT_2pt;
    Double_t lepTopMVAT_2eta;
    Double_t lepTopMVAT_2phi;

    Double_t lepTopMVAF_FRweight;
    Bool_t lepTopMVAF_1isTight;
    Bool_t lepTopMVAF_2isTight;
    Bool_t lepTopMVAF_1isTightPrompt;
    Bool_t lepTopMVAF_2isTightPrompt;

    std::vector<ROOT::Math::PtEtaPhiMVector> eles;
    std::vector<ROOT::Math::PtEtaPhiMVector> mus;

    TH2D *eleFR_h;
    TH2D *muFR_h;
};

#endif