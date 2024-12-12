#ifndef MUTOPMVASEL_H
#define MUETOPMVASEL_H
#include "eventReader_nano.h"
#include "usefulFunc.h"
#include "inputMap.h"
#include </cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/include/xgboost/c_api.h>
// #include "../../../roccor/RoccoR.cc"
#include "../../../roccor/RoccoR.h"
// #include "/workfs2/cms/huahuil/CMSSW_10_6_20/src/roccor/RoccoR.h"

class MuTopMVASel
{
public:
    MuTopMVASel(TTree *outTree, const TString era, const Bool_t isData, const Bool_t isRun3, const Int_t type = 2);
    ~MuTopMVASel();
    void Select(const eventForNano *e);
    std::vector<Double_t>& getEtaVec();
    std::vector<Double_t>& getPhiVec();
    Int_t getSize();

    void clearBranch();
    ULong_t getTotal();

private:
    const TString m_era;
    const Bool_t m_isData;
    const Bool_t m_isRun3;
    Int_t m_type = 2;
    BoosterHandle m_booster[1];
    ULong_t m_muTotal = 0;
    // RoccoR  m_rc;
    RoccoR m_rc = RoccoR(muonES.at(m_era).Data());

    // output branches
    std::vector<Double_t> muonsTopMVAT_pt;
    std::vector<Double_t> muonsTopMVAT_eta;
    std::vector<Double_t> muonsTopMVAT_phi;
    std::vector<Double_t> muonsTopMVAT_mass;
    std::vector<Int_t> muonsTopMVAT_charge;
    // std::vector<Int_t> muonsTopMVAT_index;
    std::vector<Double_t> muonsTopMVAT_topMVAScore;
    std::vector<UChar_t> muonsTopMVAT_genPartFlav;//Flavour of genParticle for MC matching to status==1 muons: 1 = prompt muon (including gamma*->mu mu), 15 = muon from prompt tau, 5 = muon from b, 4 = muon from c, 3 = muon from light or unknown, 0 = unmatched
    std::vector<Bool_t> muonsTopMVAF_isTight;
    std::vector<Double_t> muonsTopMVAF_ptConeCorreted;

    const std::map<Int_t, TString> WPMap = {
        {0, "L"},
        {2, "T"},
        {1, "F"},
    };
};

#endif
