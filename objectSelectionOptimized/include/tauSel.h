#ifndef TAUSEL_H
#define TAUSEL_H

#include "eventReader_nano.h"
#include "usefulFunc.h"
#include "inputMap.h"
#include "correction.h"

class TauSel
{
public:
    TauSel(TTree *outTree, const TString era, Bool_t isData, Bool_t isRun3, const Int_t tauWP = 3, const UChar_t TES = 0);
    ~TauSel();
    void Select(const eventForNano *e, const Bool_t isData, const std::vector<Double_t> &muEtaVec, const std::vector<Double_t> &muPhiVec, const std::vector<Double_t> &eEtaVec, const std::vector<Double_t> &ePhiVec);

    void calTauSF_new(const eventForNano *e, const Bool_t isData);
    Double_t calTES(Int_t itau_decayMode, Double_t itau_pt, Double_t itau_eta, Int_t itau_genPartFlav, std::string tauVsJetWP = "Medium");
    void clearBranch();
    std::vector<Double_t> &getEtaVec();
    std::vector<Double_t> &getPhiVec();
    Int_t getSize();

private:
    Int_t m_tauWP = 3;
    TString m_era;
    const Bool_t m_isData;
    Bool_t m_isRun3=kFALSE;
    const UChar_t m_TES = 0;
    std::unique_ptr<correction::CorrectionSet> cset_tauSF;
    const std::map<Int_t, std::string> tauVsJetWP = {
        {0, "VLoose"},
        {1, "Loose"},
        {2, "Loose"}, //!!!no tau enegy scale for VVLoose
        {3, "Medium"},
        {4, "Tight"},
        {5, "VTight"},
        {6, "Loose"},
        {7, "VVTight"},
    };

    std::vector<Double_t> taus_TES;
    std::vector<Double_t> taus_TES_up;
    std::vector<Double_t> taus_TES_down;

    // output branches
    std::vector<Double_t> taus_pt;
    std::vector<Double_t> taus_eta;
    std::vector<Double_t> taus_phi;
    std::vector<Double_t> taus_mass;

    std::vector<Int_t> taus_decayMode;
    std::vector<UChar_t> taus_genPartFlav;
    std::vector<Int_t> taus_jetIdx;
    std::vector<Int_t> taus_charge;
    std::vector<Double_t> taus_neutralIso;
    std::vector<Double_t> taus_jetPt;
    std::vector<Double_t> taus_jetEta;
    std::vector<Double_t> taus_jetMass;
    std::vector<Double_t> taus_jetPhi;
};

#endif
