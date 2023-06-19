#ifndef PUWEIGHTCAL_H
#define PUWEIGHTCAL_H

#include <TH1F.h>

#include "eventReader_nano.h"

class PUWeightCal
{
public:
    PUWeightCal(TTree *outTree, Bool_t isData, TString era);
    ~PUWeightCal(){};

    void Select(eventForNano *e, Bool_t isData);
    void clearBranch();

private:
    TH1F *dataPileupProfile;
    TH1F *dataPileupProfileUp;
    TH1F *dataPileupProfileDown;
    TH1F *MCPileupProfile;
    // output branches
    Double_t PUWeight=1.;
    Double_t PUWeight_up=1.;
    Double_t PUWeight_down=1.;
};

#endif
