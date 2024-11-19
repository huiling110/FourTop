#ifndef COMMENSELETIONCANDWEIGHT_H
#define COMMENSELETIONCANDWEIGHT_H

#include "myEventClass.h"

Bool_t baselineSelection(event *event, const Bool_t isRun3 = kFALSE, Bool_t is1tau2l=kFALSE);
Bool_t HLTSel(event *e, const TString m_era);

Bool_t SR1tau1lSel(event *e, const Int_t channel, Bool_t isRun3, Bool_t isFakeTau=kFALSE, Bool_t isFakeLepton=kFALSE, Bool_t isMC=kTRUE , Bool_t ifFakeTau=kTRUE);

Double_t baseWeightCal(event *e,  UInt_t entry=0, const Bool_t isRun3 = kFALSE, Bool_t isData = kFALSE, Int_t channel=0, const Bool_t isFakeTau=kFALSE, const Bool_t isFakeLepton=kFALSE);

#endif