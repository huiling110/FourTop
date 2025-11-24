class histsForRegionsValue: public histForRegionsBase
{
private:
    Double_t *m_value = nullptr;

public:
    histsForRegionsValue(TString variableName, TString histTitle, TString processName, Int_t bin, Double_t binMin, Double_t binMax, const std::vector<TString> &regions, Double_t* value) : histForRegionsBase(variableName, histTitle, processName, bin, binMin, binMax, regions), m_value{value}{
        std::cout<<"constructing histsForRegionMap derived class with m_value\n\n";
    }
virtual void fillHistVec(TString iRegion, Double_t weight, Bool_t ifFill, Bool_t isData)
{
    if (ifFill && isData)
    {
        m_histsVector[iRegion]->Fill(*m_value);
    }
    if (ifFill && !isData)
    {
        m_histsVector[iRegion]->Fill(*m_value, weight);
    }
}

virtual ~histsForRegionsValue(){
    std::cout<<"destructing histsForRegionsValue\n";
    // delete m_value;
}
};
