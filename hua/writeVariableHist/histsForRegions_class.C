#include <iterator>

template <typename Temp>
class histsForRegions
{
private:
    TString m_variableName;
    TString m_histTitle;
    Int_t m_binNum;
    Double_t m_binMin;
    Double_t m_binMax;
    // Double_t *m_binRange; //???need to add initialization for this
    std::vector<TH1D *> m_histsVector;
    TTreeReaderValue<Temp> &m_variableRef;

public:
    histsForRegions(TString variableName, TString histTitle, Int_t bin, Double_t binMin, Double_t binMax, TTreeReaderValue<Temp> &variableRef) : m_variableName{variableName}, m_histTitle{histTitle}, m_binNum{bin}, m_binMin{binMin}, m_binMax{binMax}, m_variableRef{variableRef} {};

    void initializeRegions(std::vector<TString> &regions, TString m_processName)
    {
        for (UInt_t i = 0; i < regions.size(); i++)
        {
            TString iHistName = regions[i] + "_" + m_processName + "_" + m_variableName;
            TH1D *temp;
            temp = new TH1D(iHistName.Data(), m_histTitle.Data(), m_binNum, m_binMin, m_binMax);
            temp->Sumw2();
            m_histsVector.push_back(temp);
        }
    };
    void fillHistVec(UInt_t iRegion, Double_t weight, Bool_t ifFill = kTRUE)
    {
        if (ifFill)
        {
            m_histsVector[iRegion]->Fill(*m_variableRef, weight);
        }
    }
    void fillHistVecAbs(UInt_t iRegion, Double_t weight)
    {
        m_histsVector[iRegion]->Fill(TMath::Abs(*m_variableRef), weight);
    }
    void histsScale(Double_t scale)
    {
        for (UInt_t ire = 0; ire < m_histsVector.size(); ire++)
        {
            m_histsVector[ire]->Scale(scale);
        }
    }
    void histsPrint()
    {
        for (UInt_t ire = 0; ire < m_histsVector.size(); ire++)
        {
            m_histsVector[ire]->Print();
        }
    }

    // void initializeRef(TTreeReaderValue<Int_t>& variableInTree){
    //    m_vri
    // }
};