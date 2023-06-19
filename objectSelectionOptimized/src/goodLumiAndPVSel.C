#include "../include/goodLumiAndPVSel.h"

    LumiAndPVSel::LumiAndPVSel(const Bool_t isData, const TString era): m_era{era}
    {
        std::cout << "initialize LumiAndPVSel class........\n";
        std::cout<<"m_era="<<m_era<<"\n";
        readJSON(isData, GoldenJSONs[era], m_goodLumis);
        std::cout << "done LumiAndPVSel initializing.........\n";
        std::cout<<"\n";
    };

    Bool_t LumiAndPVSel::Select(const Bool_t isData, eventForNano *e)
    {
        // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGoodLumiSectionsJSONFile
        Bool_t ifGoodLumi = kTRUE;
        if (isData)
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
        if (*e->PV_npvsGood > 0)
        {
            ifPV = kTRUE;
        }

        Bool_t ifPass = ifGoodLumi&& ifPV;
        //!!! temparorily set ifPass=true for 2022
        if(m_era.CompareTo("2022")==0){
            ifPass = kTRUE;
        }


        return ifPass;

    };

