#include "../include/goodLumiAndPVSel.h"

LumiAndPVSel::LumiAndPVSel(const Bool_t isData, const TString era, Bool_t isRun3) : m_era{era}, m_isRun3{isRun3}
{
    std::cout << "initialize LumiAndPVSel class........\n";
    std::cout << "m_era=" << m_era <<" m_isRun3="<<m_isRun3<< "\n";
    OS::readJSON(isData, GoldenJSONs[era], m_goodLumis);
    std::cout << "done LumiAndPVSel initializing.........\n";
    std::cout << "\n";
};

Bool_t LumiAndPVSel::Select(const Bool_t isData, eventForNano *e)
{
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGoodLumiSectionsJSONFile
    if(m_entry==0){
        std::cout<<"running LumiAndPVSel::Select()\n";
    }
    Bool_t ifGoodLumi = kTRUE;
    // if (isData)
    if (isData&&(!m_isRun3))
    {
        if (m_goodLumis.find(*e->run) == m_goodLumis.end())
        {
            ifGoodLumi = kFALSE;
        }
        else
        { // if run number is in map
            Bool_t keepEvent = false;
            for (Int_t i = 0; i < m_goodLumis[*e->run].size() / 2.; i++)
            {
                if (*e->luminosityBlock >= m_goodLumis[*e->run][i * 2] && *e->luminosityBlock <= m_goodLumis[*e->run][i * 2 + 1])
                {
                    keepEvent = true;
                    break;
                }
            }
            if (!keepEvent)
            {
                // veto luminosity blocks not in JSON
                ifGoodLumi = kFALSE;
            }
        }
    }
    //
    Bool_t ifPV = kFALSE;
    Int_t PV__npvsGood = OS::getValForDynamicReader<UChar_t>(m_isRun3, e->PV_npvsGood);
    // if (*e->PV_npvsGood > 0)
    if(PV__npvsGood>0)
    {
        ifPV = kTRUE;
    }

    Bool_t ifPass = ifGoodLumi && ifPV;
    //!!! temparorily set ifPass=true for 2022
    // if (m_isRun3)
    // {
    //     ifPass = kTRUE;
    // }

    m_entry++;

    return ifPass;
};
