#include "../include/copyBranch.h"
#include "../include/usefulFunc.h"
#include <iostream>
#include <any>

CopyBranch::CopyBranch(TTree *outTree, const TString processName, const Bool_t isData, const Bool_t isRun3):m_processName{processName}, m_isData{isData}, m_isRun3{isRun3}
{
    std::cout << "Initializing CopyBranch .........\n";
    std::cout<<"m_isRun3="<<m_isRun3<<"\n";

    m_isGammaSample = m_processName=="ttG" || m_processName=="ZGToLLG" || m_processName=="WGToLNuG" || m_processName=="TGJets";
    m_isNotGammaSample = m_processName.Contains("ttbar") || m_processName.Contains("DYJets") || m_processName.Contains("WJets") || m_processName.Contains("st_");
    std::cout<<"m_isGammaSample="<<m_isGammaSample<<"\n";
    std::cout<<"m_isNotGammaSample="<<m_isNotGammaSample<<"\n";

    outTree->Branch("run_", &run_);
    outTree->Branch("event_", &event_);
    outTree->Branch("luminosityBlock_", &luminosityBlock_);
    outTree->Branch("PV_npvsGood_", &PV_npvsGood_);
    outTree->Branch("MET_pt_", &MET_pt_);
    outTree->Branch("MET_phi_", &MET_phi_);

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

// void CopyBranch::Select(eventForNano *e, Bool_t isData)
Bool_t CopyBranch::Select(eventForNano *e, Bool_t isData)
{
    clearBranch();//!!!important

    Bool_t ifRemoveEvent = overlapRemovalSamples(e);

    run_ = *e->run;
    event_ = *e->event;
    luminosityBlock_ = *e->luminosityBlock;
    MET_pt_ = *e->MET_pt;
    MET_phi_ = *e->MET_phi;

    if (m_isRun3){
        PV_npvsGood_ = std::any_cast<UChar_t>(e->PV_npvsGood.GetValue());//nanoAODv12
    }else{
        PV_npvsGood_ = std::any_cast<Int_t>(e->PV_npvsGood.GetValue());//nanoAODv9
    }

    if (e->L1PreFiringWeight_Nom){
        EVENT_prefireWeight_ = **e->L1PreFiringWeight_Nom;
        EVENT_prefireWeight_up_ = **e->L1PreFiringWeight_Up;
        EVENT_prefireWeight_down_ = **e->L1PreFiringWeight_Dn;
    }
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
    // OS::copy_TTreeReaderArray_toVector<Int_t>(e->Electron_charge, Electron_charge_); // this line is fine
    // OS::copy_TTreeReaderArray_toVector<Int_t>(e->Muon_charge, Muon_charge_);         // this okay too
    // OS::copy_TTreeReaderArray_toVector<Float_t>(e->LHEPdfWeight, LHEPdfWeight_);
    // if (!isData)
    // {
    // copy_TTreeReaderArray_toVector<Int_t>(*e->GenPart_genPartIdxMother, GenPart_genPartIdxMother_);
    //!!!???it seem this is causing the memery exceeding problem
    // copy_TTreeReaderArray_toVector<Int_t>(static_cast<TTreeReaderArray<Int_t>>(*e->GenPart_genPartIdxMother), GenPart_genPartIdxMother_); //???it seem this is causing the memery exceeding problem
    // copy_TTreeReaderArray_toVector<Int_t>(*e->GenPart_pdgId, GenPart_pdgId_ );
    // }


    return ifRemoveEvent;
};
void CopyBranch::clearBranch()
{
    GenPart_genPartIdxMother_.clear();
    GenPart_pdgId_.clear();
    LHEPdfWeight_.clear();
};

Bool_t CopyBranch::overlapRemovalSamples(const eventForNano* e){
//overlap removal for Gamma processes 
    Bool_t ifRemove = kFALSE;
    if((!m_isGammaSample)&&(!m_isNotGammaSample)){
        return kFALSE;
    }

    std::vector<Double_t> partonsEtaVec;
    std::vector<Double_t> partonsPhiVec;
    for (size_t j = 0; j < e->GenPart_pdgId->GetSize(); j++)
    {
        if (std::abs(e->GenPart_pdgId->At(j)) < 7 || std::abs(e->GenPart_pdgId->At(j)) == 21)
        {
            partonsEtaVec.push_back(e->GenPart_eta->At(j));
            partonsPhiVec.push_back(e->GenPart_phi->At(j));
        }
    }
    //impove the above code


    if(m_isGammaSample){
        //should exist gen photon pt>10 and delta R> 0.05 with parton , for gamma sample
        ifRemove = kTRUE;
        for (size_t i = 0; i < e->GenPart_pdgId->GetSize(); i++)
        {
            if (std::abs(e->GenPart_pdgId->At(i)) == 22 && e->GenPart_pt->At(i)>10.)
            {
               Bool_t removeIGen = OS::overlapRemove(e->GenPart_eta->At(i), e->GenPart_phi->At(i), partonsEtaVec, partonsPhiVec, 0.05); //if overlap with parton
                if(!removeIGen){
                     ifRemove = kFALSE;
                     break; // exit a loop prematurely when a certain condition is met.
                }
            }
        }
    }else if(m_isNotGammaSample){
       ifRemove = kFALSE;
        for (size_t i = 0; i < e->GenPart_pdgId->GetSize(); i++)
        {
            if (std::abs(e->GenPart_pdgId->At(i)) == 22 && e->GenPart_pt->At(i)>10.)
            {
               Bool_t removeIGen = OS::overlapRemove(e->GenPart_eta->At(i), e->GenPart_phi->At(i), partonsEtaVec, partonsPhiVec, 0.05); 
                if(removeIGen){
                     ifRemove = kTRUE;
                     break; // exit a loop prematurely when a certain condition is met.
                }
            }
        } 
    }


    return ifRemove;

}