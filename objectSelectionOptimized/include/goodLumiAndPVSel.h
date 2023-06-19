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
    LumiAndPVSel(const Bool_t isData, const TString era);
    ~LumiAndPVSel(){};

    // Bool_t Select(const Bool_t isData, const eventForNano *e)//??? can not dereference a  const pointer?
    Bool_t Select(const Bool_t isData, eventForNano *e);

private:
    TString m_era;
    std::map<Int_t, std::vector<UInt_t>> m_goodLumis;
    // output branches
};

#endif
