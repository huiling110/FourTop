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

void histRegionVectFill(std::vector<std::shared_ptr<histForRegionsBase>>& histForRegion_vec, Bool_t isRegion, TString region, Double_t weight, Bool_t isData );

#endif