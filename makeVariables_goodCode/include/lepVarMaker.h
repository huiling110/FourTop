#ifndef LEPVARMAKER_H
#define LEPVARMAKER_H

#include "objVarMaker.h"

class LepVarMaker : public ObjVarMaker 
{
public:
    LepVarMaker(TTree* tree, TString objName="lepTopMVAT", UInt_t type=0);
    ~LepVarMaker();
    void makeVariables(const EventForMV* e);
    void clearBranch();
    // void setupLorentzObjs(std::vector<ROOT::Math::PtEtaPhiMVector>& leptonsMVAT);
    void setupLorentzObjs(const EventForMV *e);

private:
    Double_t lepTopMVAT_2invariantMass;
    Bool_t lepTopMVAT_2charge;
    Double_t lepTopMVAT_2pt;
    Double_t lepTopMVAT_2eta;
    Double_t lepTopMVAT_2phi;

    std::vector<ROOT::Math::PtEtaPhiMVector> eles;
    std::vector<ROOT::Math::PtEtaPhiMVector> mus;
};

#endif