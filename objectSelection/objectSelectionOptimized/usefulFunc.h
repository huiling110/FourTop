#ifndef USEFULFUNC_H
#define USEFULFUNC_H
#include <map>

#include <TString.h>

Bool_t getIsData(TString inputDir);

TString getEra(TString inputDir);

void readJSON(const Bool_t isdata, const TString jsonInFile, std::map<Int_t, std::vector<UInt_t>> &_goodLumis);
#endif
