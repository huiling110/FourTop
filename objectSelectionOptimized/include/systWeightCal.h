#ifndef SYSTWEIGHTCAL_H
#define SYSTWEIGHTCAL_H

#include <TH1F.h>

#include "eventReader_nano.h"

class SystWeightCal
{
public:
    SystWeightCal(TTree *outTree, Bool_t isData,  Bool_t isRun3=kFALSE);
    ~SystWeightCal(){};

    void Select(eventForNano *e, Bool_t isData);
    void clearBranch();

private:
    Bool_t m_isRun3 = kFALSE;
    // output branches
    Double_t PUWeight=1.;
    Double_t PUWeight_up=1.;
    Double_t PUWeight_down=1.;
};

#endif
