#ifndef ELEMVASEL_H
#define ELEMVASEL_H

#include <random>
#include "correction.h"

#include "eventReader_nano.h"
#include "usefulFunc.h"
#include "inputMap.h"

class EleMVASel
{
public:
    EleMVASel(TTree *outTree, const TString era, const Bool_t isData, Bool_t isRun3, const Int_t type = 2, const UChar_t eleSys = 3, const UChar_t eleSmear = 3);
    ~EleMVASel();

    Double_t getEleScale(UChar_t gain, UInt_t run, Double_t eta, Double_t r9, Double_t et);

    Double_t getEleSmear(Double_t eta, Double_t r9);
    void Select(eventForNano *e);
    std::vector<Double_t>& getEtaVec();
    std::vector<Double_t>& getPhiVec();
    ULong_t getTotal();

    void clearBranch();

private:
    Int_t m_type = 2;
    TString m_era;
    const Bool_t m_isData = kFALSE;
    Bool_t m_isRun3 = kFALSE;
    ULong_t m_entry = 0;
    const UChar_t m_Sys_scale = 0; // 0:nominal; 1:up; 2:down; 3: none
    const UChar_t m_Sys_smear = 0;
    std::mt19937 m_rng{125};
    // m_rng = std::mt19937(125);

    std::unique_ptr<correction::CorrectionSet> cset_eleScale;//!!!only for run3
    // output branches
    std::vector<Double_t> muonsTopMVAT_pt;
    std::vector<Double_t> muonsTopMVAT_eta;
    std::vector<Double_t> muonsTopMVAT_phi;
    std::vector<Double_t> muonsTopMVAT_mass;
    std::vector<Int_t> muonsTopMVAT_charge;
    std::vector<Int_t> muonsTopMVAT_index;
    ULong_t m_objTotal=0;
};

#endif
