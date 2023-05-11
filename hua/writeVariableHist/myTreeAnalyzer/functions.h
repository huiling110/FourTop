#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"

// common functions for WH

Double_t getGenSum(TString inputFile);
TString getEra(TString inputDir);

#endif