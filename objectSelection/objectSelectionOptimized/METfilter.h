#ifndef METFILTER_H
#define METFILTER_H

#include <iostream>

#include <TString.h>


#include "eventReader_nano.h"
#include "inputMap.h"
#include "usefulFunc.h"

class METFilter
{
public:
    METFilter();
    ~METFilter(){};

    Bool_t Select(const TString era, eventForNano *e);

private:
    // output branches
};

#endif
