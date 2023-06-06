#include "../include/copyBranch.h"
#include "../include/usefulFunc.h"

// CopyBranch(TTree *outTree) : m_outTree{outTree}
CopyBranch::CopyBranch(TTree *outTree)
{
    std::cout<<"Initializing CopyBranch .........\n";
    outTree->Branch("run_", &run_);
    outTree->Branch("event_", &event_);
    outTree->Branch("PV_npvsGood_", &PV_npvsGood_);
    outTree->Branch("Electron_charge_", &Electron_charge_);
    outTree->Branch("Muon_charge_", &Muon_charge_);
    outTree->Branch("MET_pt_", &MET_pt_);
    std::cout<<"Done intializing ...........\n";
    std::cout<<"\n";
};

void CopyBranch::Select(eventForNano *e)
{

    run_ = *e->run;
    event_ = *e->event;
    PV_npvsGood_ = *e->PV_npvsGood;
        copy_TTreeReaderArray_toVector(e->Electron_charge, Electron_charge_);

};
void CopyBranch::clearBranch(){
    Electron_charge_.clear();
    Muon_charge_.clear();

};
