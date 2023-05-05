#ifndef USEFULFUNCTION_H
#define USEFULFUNCTION_H

#include <string>
#include <iostream>

#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

void getOption(TString option, std::vector<TString> &optionVec);

Double_t getGenSum(TString inputFile);

// template <typename T>
// T *getHistogramFromFile(TString filename, TString histname)
TH1D *getHistogramFromFile(TString filename, const char *histname);

void histFill(Bool_t ifFill, Bool_t isData, Double_t weight, Double_t variableVal, TH1D *&hist);

// void copy_TTreeReaderArray_toVector(const TTreeReaderArray<Double_t> &array, vector<Double_t> &vec)
// {
//     for (UInt_t i = 0; i < array.GetSize(); i++)
//     {
//         vec.push_back(array.At(i));
//     }
// }

#endif