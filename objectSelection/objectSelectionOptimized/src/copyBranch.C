#include "../include/copyBranch.h"

// CopyBranch(TTree *outTree) : m_outTree{outTree}
CopyBranch::CopyBranch(TTree *outTree)
{
    outTree->Branch("run_", &run_);
    outTree->Branch("event_", &event_);
};
// CopyBranch::~CopyBranch(){};

// Bool_t Select(const eventForNano *e, const TString era = "2017", const Bool_t isData = kFALSE)
// Bool_t CopyBranch::Select(eventForNano *e, const TString era = "2017", const Bool_t isData = kFALSE, Bool_t isHLTSel = kTRUE)
void CopyBranch::Select(eventForNano *e)
{
    // Here I manully set the branch value = nanoAOD value only when the trigger is supposed to work in the run period;
    // otherwise trigger=false;
    // clearBranch();

    run_ = *e->run;
    event_ = *e->event;
};
void CopyBranch::clearBranch(){

};
