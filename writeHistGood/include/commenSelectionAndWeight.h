#ifndef COMMENSELETIONCANDWEIGHT_H
#define COMMENSELETIONCANDWEIGHT_H

#include "myEventClass.h"

Bool_t baselineSelection(event *event);

Bool_t SR1tau1lSel(event *e, const Int_t channel, Bool_t isRun3 = kFALSE);

Double_t baseWeightCal(event *e, const Bool_t isRun3 = kFALSE);

#endif