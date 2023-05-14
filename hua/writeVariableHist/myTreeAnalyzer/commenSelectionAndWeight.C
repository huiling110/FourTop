
#include "myEventClass.h"

Bool_t baselineSelection(event *event)
{
    Bool_t pass = kFALSE;
    if (event->jets_number.v() >= 6 && event->bjetsM_num.v() >= 1 && event->jets_HT.v() > 500. && event->jets_6pt.v() > 40.)
    {
        pass = kTRUE;
    }
    return pass;
}
