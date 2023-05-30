#ifndef USEFULFUNC_H
#define USEFULFUNC_H
#include <map>

#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include <TROOT.h>
#include <vector>

#include "TFormula.h"
#include <TRandom3.h>
#include "TLorentzVector.h"
#include <Math/Vector4D.h>
#include </cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/include/xgboost/c_api.h>
#include <TString.h>

Bool_t getIsData(TString inputDir);

TString getEra(TString inputDir);

void readJSON(const Bool_t isdata, const TString jsonInFile, std::map<Int_t, std::vector<UInt_t>> &_goodLumis);

Double_t TopLeptonEvaluate(std::map<TString, Float_t> &inputFeatures, const BoosterHandle &booster);

#endif
