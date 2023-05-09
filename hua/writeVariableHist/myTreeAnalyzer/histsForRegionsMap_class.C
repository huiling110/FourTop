#include "histsForRegionsMap_class.h"

void histsForRegionsMap::fillHistVec(TString iRegion, Double_t value, Double_t weight, Bool_t ifFill = kTRUE, Bool_t isData = kFALSE)
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
void histsForRegionsMap::print()
{
    for (auto it = m_histsVector.begin(); it != m_histsVector.end(); ++it)
    {
        std::cout << it->first << " : \n";
        it->second->Print();
    }
}
// void fillHistVecAbs(UInt_t iRegion, Double_t weight)
// {
//     m_histsVector[iRegion]->Fill(TMath::Abs(*m_variableRef), weight);
// }
// void histsScale(Double_t scale)
// {
//     for (UInt_t ire = 0; ire < m_histsVector.size(); ire++)
//     {
//         m_histsVector[ire]->Scale(scale);
//     }
// }
// void histsPrint()
// {
//     for (UInt_t ire = 0; ire < m_histsVector.size(); ire++)
//     {
//         m_histsVector[ire]->Print();
//     }
// }

// void initializeRef(TTreeReaderValue<Int_t>& variableInTree){
//    m_vri
// }
}
;