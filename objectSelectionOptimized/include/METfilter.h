#ifndef METFILTER_H
#define METFILTER_H

#include <iostream>

#include <TString.h>

#include "eventReader_nano.h"
// #include "inputMap.h"
#include "usefulFunc.h"

class METFilter
{
public:
    METFilter(TString era, const Bool_t isRun3);
    ~METFilter(){};

    Bool_t Select(const TString era, eventForNano *e);

private:
    Bool_t m_isRun3 = kFALSE;
    // output branches
};

#endif
