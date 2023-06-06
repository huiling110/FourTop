
#include "myEventClass.h"

Bool_t baselineSelection(event *event)
{
    Bool_t pass = event->jets_number.v() >= 6 && event->bjetsM_num.v() >= 1 && event->jets_HT.v() > 500. && event->jets_6pt.v() > 40.;
    return pass;
}

Bool_t SR1tau1lSel(event *e, const Int_t channel=0)
{
    Int_t lepNum = e->elesTopMVAT_number.v() + e->muonsTopMVAT_number.v();
    Bool_t SR1tau1l =kFALSE;
    switch (channel)
    {
    case 0:
        SR1tau1l = e->tausT_number.v() == 1 && lepNum == 1 && e->jets_number.v() >= 7 && e->bjetsM_num.v() >= 2;
        break;
    case 1:
        SR1tau1l = e->tausT_number.v() == 1 && lepNum == 1 && e->jets_number.v() >= 8 && e->bjetsM_num.v() >= 2;
        break;
    default:
        break;
    }
    return SR1tau1l;
}

Double_t baseWeightCal(event *e)
{
    // Double_t basicWeight = EVENT_prefireWeight * EVENT_genWeight * PUweight_ * HLT_weight * tauT_IDSF_weight_new * elesTopMVAT_weight * musTopMVAT_weight * btagShape_weight * btagShapeR;
    Double_t basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v() * e->btagShape_weight.v() * e->btagShapeR.v();
    return basicWeight;
}