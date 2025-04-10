#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <variant>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"

#include "histsForRegionsMap_class.h"

// common functions for WH

namespace WH{

Double_t getGenSum(TString inputFile);
void initializeHistVec(const std::vector<TString>& regions, std::vector<std::shared_ptr<histForRegionsBase>>& histsForRegion_vec , TString m_processName, event* e );

void readVariableList(TString variableListCsv, std::vector<TString> &variablesName, std::vector<Float_t> &variablesForReader, std::map<TString, Float_t> &varForReaderMap, std::vector<std::variant<Int_t, Double_t>> &variablesOriginAll);

void histRegionVectFill(std::vector<std::shared_ptr<histForRegionsBase>> &histForRegion_vec, Bool_t isRegion, TString region, Double_t weight, Bool_t isData);

void histRegionsVectSetDir(std::vector<std::shared_ptr<histForRegionsBase>> &histForRegion_vec, TFile *&file);
void histRegionsVectScale(std::vector<std::shared_ptr<histForRegionsBase>> &histForRegion_vec, Double_t scale);

void fillDeNu(Bool_t ifPass, TH1D *&de, TH1D *&nu, Double_t var, Double_t weight);
void fillDeNu(Bool_t ifPass, TH2D *&de, TH2D *&nu, Double_t varX, Double_t varY, Double_t weight, const Bool_t isData=kFALSE);
void fillDeNu(Bool_t ifPassNu, Bool_t ifPassDe, TH1D *&de, TH1D *&nu, Double_t var, Double_t weight);

TString getProcessName(const TString processName, Bool_t isRun3);
// template <T>
// void fillDeNu(Bool_t ifPass, T *&de, T *&nu, std::vector<Double_t> varWeight)
// {
//     if (varWeight.size() == 2)
//     {
//         de->Fill(varWeight.at(0), varWeight.at(1));
//         if (ifPass)
//         {
//             nu->Fill(varWeight.at(0), varWeight.at(1))
//         }
//     }
// };

extern std::array<TString, 8> processWithExt;

void getChannelSys(std::vector<TString>& sysRegions,  TString region="1tau1lSR", TString era="2016",   Bool_t isFaketau=kFALSE, Bool_t isFakeLep = kFALSE, TString process="tttt");

Double_t calQCDScaleNor(const TString inputFile, UInt_t index);
Double_t calPDFScaleNor(const TString inputFile, UInt_t index);





}

#endif