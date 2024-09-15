#ifndef LEPVARMAKER_H
#define LEPVARMAKER_H

#include "objVarMaker.h"

class LepVarMaker : public ObjVarMaker 
{
public:
    LepVarMaker(TTree* tree, TString objName="lepTopMVAT", UInt_t type=0);
    ~LepVarMaker();
    void makeVariables(std::vector<ROOT::Math::PtEtaPhiMVector>& leptonsMVAT);
    void clearBranch();
    void setupLorentzObjs(std::vector<ROOT::Math::PtEtaPhiMVector>& leptonsMVAT);

private:
    Double_t lepTopMVAT_2invariantMass;
};

#endif