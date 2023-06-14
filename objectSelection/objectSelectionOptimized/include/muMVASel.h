#ifndef MUTOPMVASEL_H
#define MUETOPMVASEL_H



#include "eventReader_nano.h"
#include "usefulFunc.h"
#include "inputMap.h"

class MuSel
{
public:
    MuSel(TTree *outTree, const TString era, const Int_t type = 2);
    ~MuSel();
    void Select(const eventForNano *e);
    std::vector<Double_t>& getEtaVec();
    std::vector<Double_t>& getPhiVec();

    void clearBranch();

private:
    Int_t m_type = 2;
    // output branches
    std::vector<Double_t> muonsTopMVAT_pt;
    std::vector<Double_t> muonsTopMVAT_eta;
    std::vector<Double_t> muonsTopMVAT_phi;
    std::vector<Double_t> muonsTopMVAT_mass;
    std::vector<Int_t> muonsTopMVAT_index;
};

#endif
