#ifndef PUWEIGHTCAL_H
#define PUWEIGHTCAL_H

#include <TH1F.h>
#include "correction.h"

#include "eventReader_nano.h"

class PUWeightCal
{
public:
    PUWeightCal(TTree *outTree, Bool_t isData, TString era, Bool_t isRun3=kFALSE);
    ~PUWeightCal(){};

    void Select(eventForNano *e, Bool_t isData);
    void clearBranch();

private:
    Bool_t m_isRun3 = kFALSE;
    TString m_era;
    TH1F *dataPileupProfile;
    TH1F *dataPileupProfileUp;
    TH1F *dataPileupProfileDown;
    TH1F *MCPileupProfile;
    std::unique_ptr<correction::CorrectionSet> cset_puWeight;
    // output branches
    Double_t PUWeight=1.;
    Double_t PUWeight_up=1.;
    Double_t PUWeight_down=1.;
};

#endif
