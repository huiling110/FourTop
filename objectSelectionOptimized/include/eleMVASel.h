#ifndef ELEMVASEL_H
#define ELEMVASEL_H

#include "correction.h"

#include "eventReader_nano.h"
#include "usefulFunc.h"
#include "inputMap.h"

class EleMVASel
{
public:
    EleMVASel(TTree *outTree, const TString era, Bool_t isRun3, const Int_t type = 2);
    ~EleMVASel();
    void Select(const eventForNano *e);
    std::vector<Double_t>& getEtaVec();
    std::vector<Double_t>& getPhiVec();
    ULong_t getTotal();

    void clearBranch();

private:
    Int_t m_type = 2;
    TString m_era;
    Bool_t m_isRun3 = kFALSE;
    ULong_t m_entry = 0;

    std::unique_ptr<correction::CorrectionSet> cset_eleScale;//!!!only for run3
    std::unique_ptr<correction::CorrectionSet> cset_eleSmear;//!!!only for run3
    // output branches
    std::vector<Double_t> muonsTopMVAT_pt;
    std::vector<Double_t> muonsTopMVAT_eta;
    std::vector<Double_t> muonsTopMVAT_phi;
    std::vector<Double_t> muonsTopMVAT_mass;
    std::vector<Int_t> muonsTopMVAT_index;
    ULong_t m_objTotal=0;
};

#endif
