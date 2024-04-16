#ifndef COPYBRANCH_H
#define COPYBRANCH_H

#include "eventReader_nano.h"

class CopyBranch
{
public:
    CopyBranch(TTree *outTree, const Bool_t isRun3=kFALSE);
    ~CopyBranch(){};

    void Select(eventForNano *e, Bool_t isData);
    void clearBranch();

private:
    // output branches
    Bool_t m_isRun3;
    UInt_t run_;
    ULong64_t event_;
    Int_t PV_npvsGood_;
    Double_t MET_pt_;
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
