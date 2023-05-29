#include "usefulFunc.h"

#include <iostream>
#include <TString.h>

Bool_t getIsData(TString inputDir)
{
    Bool_t isData;
    if (inputDir.Contains("mc"))
    {
        isData = kFALSE;
    }
    else
    {
        isData = kTRUE;
    }
    return isData;
}

TString getEra(TString inputDir)
{
    TString era;
    if (inputDir.Contains("2017"))
    {
        era = "2017";
    }
    else if (inputDir.Contains("2018"))
    {
        era = "2018";
    }
    else if (inputDir.Contains("2016APV"))
    {
        era = "2016preVFP";
    }
    else if (inputDir.Contains("2016"))
    {
        era = "2016postVFP";
    }
    else
    {
        std::cout << "ERROR!!! get era not success!!!\n";
    }
    return era;
}
