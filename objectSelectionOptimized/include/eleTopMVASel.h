#ifndef ELETOPMVASEL_H
#define ELETOPMVASEL_H

// #include <vector.h>

#include "eventReader_nano.h"
#include "usefulFunc.h"
#include "inputMap.h"
#include </cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/include/xgboost/c_api.h>

class EleTopMVASel
{
public:
    EleTopMVASel(TTree *outTree, const TString era, const Bool_t isRun3=kFALSE, const Int_t type = 2);
    ~EleTopMVASel();
    void Select(const eventForNano *e);
    std::vector<Double_t> &getEtaVec();
    std::vector<Double_t> &getPhiVec();
    Int_t getSize();

    void clearBranch();

private:
    Int_t m_type = 2;
    TString m_era;
    Bool_t m_isRun3 = kFALSE;
    // BoosterHandle m_booster[2];
    BoosterHandle m_booster[1];
    // output branches
    std::vector<Double_t> elesTopMVAT_pt;
    std::vector<Double_t> elesTopMVAT_eta;
    std::vector<Double_t> elesTopMVAT_phi;
    std::vector<Double_t> elesTopMVAT_mass;
    std::vector<Int_t> elesTopMVAT_charge;
    std::vector<Int_t> elesTopMVAT_index;
    std::vector<Double_t> elesTopMVAT_topMVAScore;
};

#endif
