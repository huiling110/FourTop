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
    Double_t pdfWeight=1.;
    Double_t pdfWeight_up=1.;
    Double_t pdfWeight_down=1.;
    Double_t pdfWeightAlphaS_up=1.;
    Double_t pdfWeightAlphaS_down=1.;
    Double_t scaleWeight=1.;
    Double_t scaleWeight_up=1.;
    Double_t scaleWeight_down=1.;
};

#endif
