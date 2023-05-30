#ifndef LUMIANDPVSEL_H
#define LUMIANDPVSEL_H

#include <iostream>

#include <TString.h>


#include "eventReader_nano.h"
#include "inputMap.h"
#include "usefulFunc.h"

class LumiAndPVSel
{
public:
    LumiAndPVSel(const Bool_t isData, const TString era)
    {
        std::cout << "initialize LumiAndPVSel class........\n";
        readJSON(isData, GoldenJSONs[era], m_goodLumis);
        std::cout << "done LumiAndPVSel initializing.........\n";
    };
    ~LumiAndPVSel(){};

    // Bool_t Select(const Bool_t isData, const eventForNano *e)//??? can not dereference a  const pointer?
    Bool_t Select(const Bool_t isData, eventForNano *e)
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
        return ifGoodLumi&& ifPV;

    };
    // void clearBranch();

private:
    std::map<Int_t, std::vector<UInt_t>> m_goodLumis;
    // output branches
};

#endif
