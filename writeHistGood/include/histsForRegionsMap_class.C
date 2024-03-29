// #include "../include/histsForRegionsMap_class.h"

template <typename T>
void histsForRegionsMap<T>::setHistsMap(const std::vector<TString> &regions)
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
void histsForRegionsMap<T>::fillHistVec(TString iRegion, Double_t value, Double_t weight, Bool_t ifFill, Bool_t isData)
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
void histsForRegionsMap<T>::fillHistVec(TString iRegion, Double_t weight, Bool_t ifFill, Bool_t isData)
{
    if (ifFill && isData)
    {
        m_histsVector[iRegion]->Fill(m_branch->v());
    }
    if (ifFill && !isData)
    {
        m_histsVector[iRegion]->Fill(m_branch->v(), weight);
    }
}

void histsForRegionsMap<T>::print()
{
    for (auto it = m_histsVector.begin(); it != m_histsVector.end(); ++it)
    {
        std::cout << it->first << " : \n";
        it->second->Print();
    }
}

void histsForRegionsMap<T>::setDir(TFile *file)
{
    for (auto it = m_histsVector.begin(); it != m_histsVector.end(); ++it)
    {
        it->second->SetDirectory(file);
    }
}

void histsForRegionsMap<T>::scale(Double_t scale)
{
    for (auto it = m_histsVector.begin(); it != m_histsVector.end(); ++it)
    {
        it->second->Scale(scale);
    }
}

histsForRegionsMap<T>::~histsForRegionsMap<T>(){
    // delete m_histsVector;
}
