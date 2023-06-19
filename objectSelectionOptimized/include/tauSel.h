#ifndef TAUSEL_H
#define TAUSEL_H

#include "eventReader_nano.h"
#include "usefulFunc.h"
#include "inputMap.h"
#include "correction.h"

class TauSel
{
public:
    TauSel(TTree *outTree, const TString era, const Int_t tauWP = 3);
    ~TauSel();
    void Select(const eventForNano *e, const Bool_t isData, const std::vector<Double_t> &lepEtaVec, const std::vector<Double_t> &lepPhiVec, const Int_t sysTES = 0);

    void calTauSF_new(const eventForNano *e, const Bool_t isData);
    void clearBranch();
    std::vector<Double_t> &getEtaVec();
    std::vector<Double_t> &getPhiVec();
    Int_t getSize();

private:
    Int_t m_tauWP = 3;
    TString m_era;
    Bool_t m_isRun3=kFALSE;
    std::unique_ptr<correction::CorrectionSet> cset_tauSF;
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
};

#endif
