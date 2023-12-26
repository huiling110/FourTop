#include "../include/copyBranch.h"
#include "../include/usefulFunc.h"
#include <iostream>
#include <any>

// CopyBranch(TTree *outTree) : m_outTree{outTree}
CopyBranch::CopyBranch(TTree *outTree)
{
    std::cout << "Initializing CopyBranch .........\n";
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
    outTree->Branch("EVENT_genWeight_", &EVENT_genWeight_);
    outTree->Branch("LHEPdfWeight_", &LHEPdfWeight_);
    std::cout << "Done intializing ...........\n";
    std::cout << "\n";
};

void CopyBranch::Select(eventForNano *e, Bool_t isData)
{
    clearBranch();//!!!important

    run_ = *e->run;
    event_ = *e->event;

    // PV_npvsGood_ = *e->PV_npvsGood;
    // PV_npvsGood_ = e->PV_npvsGood;
    e->PV_npvsGood.Print();
    // std::cout<<"PV_npvsGood="<<e->PV_npvsGood.branchReader->GetSize()<<"\n";
    // PV_npvsGood_ = *(std::any_cast<TTreeReaderValue<UChar_t>>(e->PV_npvsGood.GetValue()));
    PV_npvsGood_ = std::any_cast<UChar_t>(e->PV_npvsGood.GetValue());
    std::cout<<"PV_npvsGood_="<<PV_npvsGood_<<"\n";

    // EVENT_prefireWeight_ = *e->L1PreFiringWeight_Nom;
    // EVENT_prefireWeight_up_ = *e->L1PreFiringWeight_Up;
    // EVENT_prefireWeight_down_ = *e->L1PreFiringWeight_Dn;
    if (!isData)
    {
        EVENT_genWeight_ = **e->genWeight;
    }
    else
    {
        EVENT_genWeight_ = 1;
    }
    // LHEPdfWeight_ = **e->LHEPdfWeight;
    //!!!causing too much memory consumption!!!???
    // maybe template argument deduction  is not working well, not the culprit
    OS::copy_TTreeReaderArray_toVector<Int_t>(e->Electron_charge, Electron_charge_); // this line is fine
    OS::copy_TTreeReaderArray_toVector<Int_t>(e->Muon_charge, Muon_charge_);         // this okay too
    // OS::copy_TTreeReaderArray_toVector<Float_t>(e->LHEPdfWeight, LHEPdfWeight_);
    // if (!isData)
    // {
    // copy_TTreeReaderArray_toVector<Int_t>(*e->GenPart_genPartIdxMother, GenPart_genPartIdxMother_);
    //!!!???it seem this is causing the memery exceeding problem
    // copy_TTreeReaderArray_toVector<Int_t>(static_cast<TTreeReaderArray<Int_t>>(*e->GenPart_genPartIdxMother), GenPart_genPartIdxMother_); //???it seem this is causing the memery exceeding problem
    // copy_TTreeReaderArray_toVector<Int_t>(*e->GenPart_pdgId, GenPart_pdgId_ );
    // }
};
void CopyBranch::clearBranch()
{
    Electron_charge_.clear();
    Muon_charge_.clear();
    GenPart_genPartIdxMother_.clear();
    GenPart_pdgId_.clear();
    LHEPdfWeight_.clear();
};
