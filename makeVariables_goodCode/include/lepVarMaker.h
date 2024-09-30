#ifndef LEPVARMAKER_H
#define LEPVARMAKER_H

#include <TH2D.h>
#include "objVarMaker.h"

class LepVarMaker : public ObjVarMaker 
{
public:
    LepVarMaker(TTree* tree, TString era, const Bool_t isData, TString objName="lepTopMVAT", UInt_t type=0);
    ~LepVarMaker();
    void makeVariables(const EventForMV* e);
    void clearBranch();

    void processSingleLep(const EventForMV* e, const UInt_t muonSize, const UInt_t eleSize);
    void processingDoubleLep(const EventForMV* e, const UInt_t muonSize, const UInt_t eleSize);
    void setupLorentzObjs(const EventForMV *e);
    Double_t get1pt();
    Double_t get2pt();

private:
    TString m_era;
    const Bool_t m_isData = kFALSE;
    Double_t lepTopMVAT_2invariantMass;
    Bool_t lepTopMVAT_2charge;
    Double_t lepTopMVAT_2pt;
    Double_t lepTopMVAT_2eta;
    Double_t lepTopMVAT_2phi;

    Double_t lepTopMVAF_FRweight;
    Bool_t elesTopMVAF_1isTight;
    Bool_t elesTopMVAF_2isTight;
    Bool_t muonsTopMVAF_1isTight;
    Bool_t muonsTopMVAF_2isTight;
    Bool_t elesTopMVAF_1isTightPrompt;
    Bool_t elesTopMVAF_2isTightPrompt;
    Bool_t muonsTopMVAF_1isTightPrompt;
    Bool_t muonsTopMVAF_2isTightPrompt;
    Bool_t lepTopMVAF_isAR= kFALSE;
    Double_t elesTopMVAF_1ptCorrected;
    Double_t elesTopMVAF_2ptCorrected;
    Double_t muonsTopMVAF_1ptCorrected;
    Double_t muonsTopMVAF_2ptCorrected;
    Double_t lepTopMVAF_1ptCorrected;
    Double_t lepTopMVAF_2ptCorrected;


    std::vector<Double_t> lep_ptConeCorrected;
    std::vector<ROOT::Math::PtEtaPhiMVector> eles;
    std::vector<ROOT::Math::PtEtaPhiMVector> mus;

    TH2D *eleFR_h;
    TH2D *muFR_h;
};

#endif