#ifndef LUMIANDPVSEL_H
#define LUMIANDPVSEL_H

#include "eventReader_nano.h"

class LumiAndPVSel
{
public:
    LumiAndPVSel(const Bool_t isData){
        readJSON(m_isdata, GoldenJSONs[m_era], _goodLumis);
    };
    ~LumiAndPVSel(){};

    Bool_t Select(eventForNano *e, const TString era = "2017", const Bool_t isData = kFALSE, Bool_t isHLTSel = kTRUE);
    void clearBranch();

private:
    std::map<Int_t, std::vector<UInt_t>> m_goodLumis;
    // output branches
};

#endif
