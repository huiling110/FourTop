#ifndef JETVARMAKER_H
#define JETVARMAKER_H

#include "objVarMaker.h"
#include "correction.h"
#include "JESVariation.h"

class JetVarMaker : public ObjVarMaker
{
public:
    JetVarMaker(TTree *outTree, TString objName, Int_t type = 0, TString era="2018", UChar_t JESVariation = 0);
    ~JetVarMaker();
    // void makeVariables(EventForMV *e, const std::vector<ROOT::Math::PtEtaPhiMVector>& taus);
    void makeVariables(EventForMV *e, const std::vector<ROOT::Math::PtEtaPhiMVector>& taus, JESVariation& jesVariation);
    void clearBranch();
    void setupLorentzObjs(const EventForMV *e, JESVariation& JESVariation);
    Double_t getHT();
    Double_t getJet_6pt();
    Int_t getJet_num();
    void getJetLeadingVars(const EventForMV *e, const Int_t jetRank, Double_t &jets_pt, Double_t &jets_eta, Double_t &jets_phi, Double_t &jets_btag);
    std::vector<Double_t> getJetsPt_vec() const;
    std::vector<Double_t> getJetsBtags_vec() const;
    std::vector<Double_t> getJetsEta_vec() const;
    std::vector<Int_t> getJetsFlavour_vec (const TTreeReaderArray<Int_t> &jetsFlavour) const;
    std::vector<Double_t> getJetsPtNom_vec(const TTreeReaderArray<Double_t> &jetsPt) const;
    std::pair<Double_t, Double_t> getDxDy() const;

private:
    const UChar_t m_JESVariation = 0; //0: nominal, >=1: variation
    const TString m_era = "2018";
    std::vector<UInt_t> m_removedIndices;//!for JES variation only
    // std::unordered_set<UInt_t> m_removedIndicesSet;//!for JES variation only
    std::vector<Double_t> m_jets_btags;
    std::pair<Double_t, Double_t> m_dxdy;

    Double_t jets_rationHT_4toRest = -99;
    Double_t jets_MHT = -99;
    Double_t jets_HT = -99;
    Double_t jets_invariantMass = -99;
    Double_t jets_transMass = -99;
    Double_t jets_minDeltaR = -99;
    Double_t jets_centrality = -99;
    Double_t jets_bScore = -99;
    Double_t jets_average_deltaR = -99;
    Double_t jets_4largestBscoreSum = -99;
    Double_t jets_4largestBscoreMulti = -99;
    Double_t jets_METDivideHT = -99;
    Double_t jets_HTDivideMET = -99;
    Double_t jets_sphericity = - 99.;
    Double_t jets_aplanarity = -99.0;

    Double_t jets_1btag = -99.0;
    Double_t jets_2btag = -99.0;
    Double_t jets_3btag = -99.0;
    Double_t jets_4btag = -99.0;
    Double_t jets_5btag = -99.0;
    Double_t jets_6btag = -99.0;
    Double_t jets_7btag = -99.0;
    Double_t jets_8btag = -99.0;//???what the fuck? I can not add a variable?
    Double_t jets_9btag = -99.0;
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

    Double_t jets_leptonsMVAT_minDeltaR = -99;
    Double_t jets_tausF_minDeltaR = -99;
    Double_t jets_tausT_minDeltaR = -99.0;
    Double_t jets_tausT_invariantMass = -99.0;

    Double_t MET_pt = -99;
    // Double_t MET_pt_
    Double_t MET_pt_unclusteredUp_ = -99;
    Double_t MET_pt_unclusteredDown_ = -99; 


};

#endif