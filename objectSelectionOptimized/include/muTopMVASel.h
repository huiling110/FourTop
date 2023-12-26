#ifndef MUTOPMVASEL_H
#define MUETOPMVASEL_H



#include "eventReader_nano.h"
#include "usefulFunc.h"
#include "inputMap.h"
#include </cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/include/xgboost/c_api.h>

class MuTopMVASel
{
public:
    MuTopMVASel(TTree *outTree, const TString era, const Bool_t isRun3, const Int_t type = 2);
    ~MuTopMVASel();
    void Select(const eventForNano *e);
    std::vector<Double_t>& getEtaVec();
    std::vector<Double_t>& getPhiVec();

    void clearBranch();

private:
    const TString m_era;
    const Bool_t m_isRun3;
    Int_t m_type = 2;
    BoosterHandle m_booster[1];
    // output branches
    std::vector<Double_t> muonsTopMVAT_pt;
    std::vector<Double_t> muonsTopMVAT_eta;
    std::vector<Double_t> muonsTopMVAT_phi;
    std::vector<Double_t> muonsTopMVAT_mass;
    std::vector<Int_t> muonsTopMVAT_index;
    std::vector<Double_t> muonsTopMVAT_topMVAScore;
};

#endif
