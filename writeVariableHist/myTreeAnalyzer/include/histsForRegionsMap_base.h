#ifndef HISTSFORREGIONSMAP_BASH_H
#define HISTSFORREGIONSMAP_BASH_H

#include <map>
#include "TString.h"
#include "TH1D.h"


class histForRegionsBase{
// private:
protected:
    TString m_variableName;
    TString m_histTitle;
    TString m_processName;
    Int_t m_binNum;
    Double_t m_binMin;
    Double_t m_binMax;
    std::map<TString, TH1D *> m_histsVector;


public:
    // default constructor
    histForRegionsBase(TString variableName = "", TString histTitle = "", TString processName = "", Int_t bin = 0, Double_t binMin = 0.0, Double_t binMax = 0.0) : m_variableName{variableName}, m_histTitle{histTitle}, m_processName{processName}, m_binNum{bin}, m_binMin{binMin}, m_binMax{binMax} {
        std::cout << "Initializing histForRegionsBase constructor 0\n";
    };
    histForRegionsBase(TString variableName, TString histTitle, TString processName, Int_t bin, Double_t binMin, Double_t binMax, const std::vector<TString> &regions) : m_variableName{variableName}, m_histTitle{histTitle}, m_processName{processName}, m_binNum{bin}, m_binMin{binMin}, m_binMax{binMax}
    {
        std::cout << "Initializing histForRegionsBase constructor 1\n";
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

    virtual ~histForRegionsBase(){
    };


void setHistsMap(const std::vector<TString> &regions)
{
    for (UInt_t i = 0; i < regions.size(); i++)
    {
        TString iHistName = regions[i] + "_" + m_processName + "_" + m_variableName;
        TH1D *temp;
        temp = new TH1D(iHistName.Data(), m_histTitle.Data(), m_binNum, m_binMin, m_binMax);
        temp->Sumw2();
        m_histsVector[regions[i]] = temp;
    }
}
void fillHistVec(TString iRegion, Double_t value, Double_t weight, Bool_t ifFill, Bool_t isData)
{
    if (ifFill && isData)
    {
        m_histsVector[iRegion]->Fill(value);
    }
    if (ifFill && !isData)
    {
        m_histsVector[iRegion]->Fill(value, weight);
    }
}
virtual void fillHistVec(TString iRegion, Double_t weight, Bool_t ifFill, Bool_t isData);
// {
//     if (ifFill && isData)
//     {
//         m_histsVector[iRegion]->Fill(m_branch->v());
//     }
//     if (ifFill && !isData)
//     {
//         m_histsVector[iRegion]->Fill(m_branch->v(), weight);
//     }
// }

void print()
{
    for (auto it = m_histsVector.begin(); it != m_histsVector.end(); ++it)
    {
        std::cout << it->first << " : \n";
        it->second->Print();
    }
}

void setDir(TFile *file)
{
    for (auto it = m_histsVector.begin(); it != m_histsVector.end(); ++it)
    {
        it->second->SetDirectory(file);
    }
}

void scale(Double_t scale)
{
    for (auto it = m_histsVector.begin(); it != m_histsVector.end(); ++it)
    {
        it->second->Scale(scale);
    }
}
};
#endif