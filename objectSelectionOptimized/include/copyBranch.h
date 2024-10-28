#ifndef COPYBRANCH_H
#define COPYBRANCH_H

#include "eventReader_nano.h"

class CopyBranch
{
public:
    CopyBranch(TTree *outTree, const TString processes, const Bool_t isData =kFALSE, const Bool_t isRun3=kFALSE);
    ~CopyBranch(){};

    void Select(eventForNano *e, Bool_t isData);
    void clearBranch();
    void overlapRemovalSamples(const eventForNano* e);

private:
    // output branches
    Bool_t m_isRun3;
    const Bool_t m_isData;
    TString m_processName;
    Bool_t m_isGammaSample;
    Bool_t m_isNotGammaSample;

    UInt_t run_;
    ULong64_t event_;
    UInt_t luminosityBlock_;
    Int_t PV_npvsGood_;
    Double_t MET_pt_;
    Double_t MET_phi_;
    Double_t EVENT_prefireWeight_;
    Double_t EVENT_prefireWeight_up_;
    Double_t EVENT_prefireWeight_down_;
    Double_t EVENT_genWeight_;
    //therectical uncertainties
    std::vector<Float_t> LHEPdfWeight_;
    // std::vector<Int_t> Electron_charge_;
    // std::vector<Int_t> Muon_charge_;
    std::vector<Int_t> GenPart_genPartIdxMother_;
    std::vector<Int_t> GenPart_pdgId_ ;
};

#endif
