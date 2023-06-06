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
    outTree->Branch("EVENT_prefireWeight_", &EVENT_prefireWeight_);
    outTree->Branch("EVENT_prefireWeight_up_", &EVENT_prefireWeight_up_);
    outTree->Branch("EVENT_prefireWeight_down_", &EVENT_prefireWeight_down_);
    outTree->Branch("GenPart_pdgId_", &GenPart_pdgId_);
    outTree->Branch("GenPart_genPartIdxMother_", &GenPart_genPartIdxMother_);
    std::cout<<"Done intializing ...........\n";
    std::cout<<"\n";
};

void CopyBranch::Select(eventForNano *e, Bool_t isData)
{

    run_ = *e->run;
    event_ = *e->event;
    PV_npvsGood_ = *e->PV_npvsGood;
    EVENT_prefireWeight_ = *e->L1PreFiringWeight_Nom;
    EVENT_prefireWeight_up_ = *e->L1PreFiringWeight_Up;
    EVENT_prefireWeight_down_ = *e->L1PreFiringWeight_Dn;
    copy_TTreeReaderArray_toVector(e->Electron_charge, Electron_charge_);
    copy_TTreeReaderArray_toVector(e->Muon_charge, Muon_charge_);
    if (!isData){
    copy_TTreeReaderArray_toVector(*e->GenPart_genPartIdxMother, GenPart_genPartIdxMother_ );
    copy_TTreeReaderArray_toVector(*e->GenPart_pdgId, GenPart_pdgId_ );
    }

};
void CopyBranch::clearBranch(){
    Electron_charge_.clear();
    Muon_charge_.clear();
    GenPart_genPartIdxMother_.clear();
    GenPart_pdgId_.clear();


};
