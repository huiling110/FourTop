#ifndef JETVARMAKER_H
#define JETVARMAKER_H

#include "objVarMaker.h"

class JetVarMaker : public ObjVarMaker
{
public:
    JetVarMaker(TTree *outTree, TString objName, Int_t type = 0);
    ~JetVarMaker();
    void makeVariables(const EventForMV *e);
    void clearBranch();
    void setupLorentzObjs(const EventForMV *e);
    Double_t getHT();
    Double_t getJet_6pt();
    Int_t getJet_num();
    void getJetLeadingVars(const EventForMV *e, const Int_t jetRank, Double_t &jets_pt, Double_t &jets_eta, Double_t &jets_phi, Double_t &jets_btag);

private:
    Double_t jets_rationHT_4toRest = -99;
    Double_t jets_MHT = -99;
    Double_t jets_HT = -99;
    Double_t jets_invariantMass = -99;
    Double_t jets_transMass = -99;
    Double_t jets_minDeltaR = -99;
    Double_t jets_bScore = -99;
    Double_t jets_bScoreMultiply = -99;
    Double_t jets_average_deltaR = -99;
    Double_t jets_4largestBscoreSum = -99;
    Double_t jets_4largestBscoreMulti = -99;
    Double_t jets_HTDividedByMet = -99;
    Double_t jets_MetDividedByHT = -99;
    Double_t jets_MHTDividedByMet = -99;
    Double_t jets_spherilty = -99.0;
    Double_t jets_aplanarity = -99.0;
    Double_t jets_1btag = -99.0;
    Double_t jets_2btag = -99.0;
    Double_t jets_3btag = -99.0;
    Double_t jets_4btag = -99.0;
    Double_t jets_5btag = -99.0;
    Double_t jets_6btag = -99.0;
    Double_t jets_7btag = -99.0;
    // Double_t jets_8btag = -99.0;
    // Double_t jets_9btag = -99.0;
    // Double_t jets_10btag = -99.0;
    // Double_t jets_11btag = -99.0;
    // Double_t jets_12btag = -99.0;
    Double_t jets_2pt = -99.0;
    Double_t jets_2eta = -99.0;
    Double_t jets_2phi = -99.0;
    Double_t jets_3pt = -99.0;
    Double_t jets_3eta = -99.0;
    Double_t jets_3phi = -99.0;
    Double_t jets_4pt = -99.0;
    Double_t jets_4eta = -99.0;
    Double_t jets_4phi = -99.0;
    Double_t jets_5pt = -99.0;
    Double_t jets_5eta = -99.0;
    Double_t jets_5phi = -99.0;
    Double_t jets_6pt = -99.0;
    Double_t jets_6eta = -99.0;
    Double_t jets_6phi = -99.0;
    Double_t jets_7pt = -99.0;
    Double_t jets_7eta = -99.0;
    Double_t jets_7phi = -99.0;
    Double_t jets_8pt = -99.0;
    Double_t jets_8eta = -99.0;
    Double_t jets_8phi = -99.0;
    Double_t jets_9pt = -99.0;
    Double_t jets_9eta = -99.0;
    Double_t jets_9phi = -99.0;
    Double_t jets_10pt = -99.0;
    Double_t jets_10eta = -99.0;
    Double_t jets_10phi = -99.0;
    Double_t jets_11pt = -99.0;
    Double_t jets_11eta = -99.0;
    Double_t jets_11phi = -99.0;

    Double_t jets_leptonsMVAT_minDeltaR = -99;
    Double_t jets_tausF_minDeltaR = -99;
    Double_t jets_tausT_minDeltaR = -99.0;
    Double_t jets_tausT_invariantMass = -99.0;
};

#endif