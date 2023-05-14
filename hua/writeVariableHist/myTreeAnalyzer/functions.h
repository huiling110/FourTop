#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <variant>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"

// common functions for WH

Double_t getGenSum(TString inputFile);
TString getEra(TString inputDir);
Bool_t getIsData(TString inputDir);
// void readVariableList(TString variableListCsv, std::vector<TString> &variablesName, std::vector<Float_t> &variablesForReader, std::vector<std::variant<Int_t, Double_t>> &variablesOriginAll);
void readVariableList(TString variableListCsv, std::vector<TString> &variablesName, std::vector<Float_t> &variablesForReader, std::map<TString, Float_t> &varForReaderMap, std::vector<std::variant<Int_t, Double_t>> &variablesOriginAll);

#endif