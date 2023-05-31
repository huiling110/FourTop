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

// #include "muTopMVASel.h"//circular include 
// #include "eleTopMVASel.h"


Bool_t getIsData(TString inputDir);

TString getEra(TString inputDir);

void readJSON(const Bool_t isdata, const TString jsonInFile, std::map<Int_t, std::vector<UInt_t>> &_goodLumis);

Double_t TopLeptonEvaluate(std::map<TString, Float_t> &inputFeatures, const BoosterHandle &booster);

Double_t DeltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2) ;
Double_t deltRmin(const Double_t eta1, const Double_t phi1, const std::vector<Double_t>& lepEtaVec, const std::vector<Double_t>& lepPhiVec);

Bool_t descendingComparator(const Double_t& a, const Double_t& b);
void addTwoObjs(const std::vector<Double_t> &muEtaVec, const std::vector<Double_t> &eleEtaVec, std::vector<Double_t> &lepEtaVec);
// void getLepEtaPhi(std::vector<Double_t> &lepEtaVec, std::vector<Double_t> &lepPhiVec, EleTopMVASel &eleTopMVATSel, MuTopMVASel &muTopMVATSel);

#endif
