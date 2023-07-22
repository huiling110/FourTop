#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <variant>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"

#include "histsForRegionsMap_class.h"

// common functions for WH

Double_t getGenSum(TString inputFile);
void readVariableList(TString variableListCsv, std::vector<TString> &variablesName, std::vector<Float_t> &variablesForReader, std::map<TString, Float_t> &varForReaderMap, std::vector<std::variant<Int_t, Double_t>> &variablesOriginAll);

void histRegionVectFill(std::vector<std::shared_ptr<histForRegionsBase>> &histForRegion_vec, Bool_t isRegion, TString region, Double_t weight, Bool_t isData);

void histRegionsVectSetDir(std::vector<std::shared_ptr<histForRegionsBase>> &histForRegion_vec, TFile *&file);
void histRegionsVectScale(std::vector<std::shared_ptr<histForRegionsBase>> &histForRegion_vec, Double_t scale);

void fillDeNu(Bool_t ifPass, TH1D *&de, TH1D *&nu, Double_t var, Double_t weight);
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

#endif