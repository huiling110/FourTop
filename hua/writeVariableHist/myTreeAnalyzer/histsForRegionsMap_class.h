#ifndef HISTFORREGIONSMAP_CLASS_H
#define HISTFORREGIONSMAP_CLASS_H

#include <iterator>
#include <map>
#include <iostream>

#include "TString.h"
#include "TH1D.h"
#include "TFile.h"
// #include ""

// template <typename Temp>
class histsForRegionsMap
{
private:
    TString m_variableName;
    TString m_histTitle;
    TString m_processName;
    Int_t m_binNum;
    Double_t m_binMin;
    Double_t m_binMax;
    std::map<TString, TH1D *> m_histsVector;

public:
    // default constructor
    histsForRegionsMap(TString variableName = "", TString histTitle = "", TString processName = "", Int_t bin = 0, Double_t binMin = 0.0, Double_t binMax = 0.0) : m_variableName{variableName}, m_histTitle{histTitle}, m_processName{processName}, m_binNum{bin}, m_binMin{binMin}, m_binMax{binMax} {};
    histsForRegionsMap(TString variableName, TString histTitle, TString processName, Int_t bin, Double_t binMin, Double_t binMax, const std::vector<TString> &regions) : m_variableName{variableName}, m_histTitle{histTitle}, m_processName{processName}, m_binNum{bin}, m_binMin{binMin}, m_binMax{binMax}
    {
        for (UInt_t i = 0; i < regions.size(); i++)
        {
            // TString iHistName = regions[i] + "_" + m_processName + "_" + m_variableName;
            TString iHistName = m_processName + "_" + regions[i] + "_" + m_variableName;
            TH1D *temp;
            temp = new TH1D(iHistName.Data(), m_histTitle.Data(), m_binNum, m_binMin, m_binMax);
            temp->Sumw2();
            m_histsVector[regions[i]] = temp;
        }
    };
    void setHistsMap(const std::vector<TString> &regions);
    void fillHistVec(TString iRegion, Double_t value, Double_t weight, Bool_t ifFill = kTRUE, Bool_t isData = kFALSE);
    void print();
    void setDir(TFile *file);
    void scale(Double_t scale);
};

#endif