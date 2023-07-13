#ifndef COMMENFUNCTION_H
#define COMMENFUNCTION_H

#include <TString.h>
#include <TH1D.h>

namespace TTTT{



Bool_t getIsData(TString inputDir);
TString getEra(TString inputDir);

Bool_t isRun3(TString era);
void fillHist(TH1D *&hist, Double_t value, Double_t weight, Bool_t isData);

    Double_t getGenSum(TString inputFile);

}
#endif