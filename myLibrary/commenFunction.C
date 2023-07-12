#include "commenFunction.h"

#include <iostream>

namespace TTTT
{

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
        else if (inputDir.Contains("2022"))
        {
            era = "2022";
        }
        else
        {
            std::cout << "ERROR!!! get era not success!!!\n";
        }
        return era;
    }

    Bool_t isRun3(TString era)
    {
        Bool_t isRun3 = kFALSE;
        if (era.CompareTo("2022") == 0)
        {
            isRun3 = kTRUE;
        }
        return isRun3;
    }

    void fillHist(TH1D*& hist, Double_t value, Double_t weight, Bool_t isData){
        if( !isData){
            hist->Fill(value, weight);
        }else{
            hist->Fill(value);
        }
    }

}