
#include "myEventClass.h"

Bool_t baselineSelection(event *event)
{
    Bool_t pass = event->jets_number.v() >= 6 && event->bjetsM_num.v() >= 1 && event->jets_HT.v() > 500. && event->jets_6pt.v() > 40.;
    return pass;
}

Bool_t SR1tau1lSel(event *e)
{
    Int_t lepNum = e->elesTopMVAT_number.v() + e->muonsTopMVAT_number.v();
    Bool_t SR1tau1l = e->tausT_number.v() == 1 && lepNum == 1 && e->jets_number.v() >= 7 && e->bjetsM_num.v() >= 2;
    return SR1tau1l;
}
