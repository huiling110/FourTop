#ifndef COPYBRANCH_H
#define COPYBRANCH_H

#include "eventReader_nano.h"

class CopyBranch
{
public:
    CopyBranch(TTree *outTree);
    ~CopyBranch(){};

    void Select(eventForNano *e);
    void clearBranch();

private:
    // output branches
    UInt_t run_;
    ULong64_t event_;
    Int_t PV_npvsGood_;
    Double_t MET_pt_;
    std::vector<Int_t> Electron_charge_;
    std::vector<Int_t> Muon_charge_;
};

#endif
