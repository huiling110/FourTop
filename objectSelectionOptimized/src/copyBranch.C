#include "../include/copyBranch.h"
#include "../include/usefulFunc.h"
#include <iostream>
#include <any>
#include <set>

CopyBranch::CopyBranch(TTree *outTree, const TString processName, const Bool_t isData, const Bool_t isRun3, const UChar_t MET_sys):m_processName{processName}, m_isData{isData}, m_isRun3{isRun3}, m_MET_sys{MET_sys} 
{
    std::cout << "Initializing CopyBranch .........\n";
    std::cout<<"m_isRun3="<<m_isRun3<<" m_MET_sys="<<static_cast<Int_t>(m_MET_sys)<<"\n";

    m_isGammaSample = m_processName=="ttG" || m_processName=="ZGToLLG" || m_processName=="WGToLNuG" || m_processName=="TGJets";
    m_isNotGammaSample = m_processName.Contains("ttbar") || m_processName.Contains("DYJets") || m_processName.Contains("WJets") || m_processName.Contains("st_");
    m_isTtbarSample = m_processName.Contains("ttbar");  // For ttbar/ttbb overlap removal
    m_isTTBBSample = m_processName.Contains("TTBB");    // For TTBB samples
    std::cout<<"m_isGammaSample="<<m_isGammaSample<<"\n";
    std::cout<<"m_isNotGammaSample="<<m_isNotGammaSample<<"\n";
    std::cout<<"m_isTtbarSample="<<m_isTtbarSample<<"\n";
    std::cout<<"m_isTTBBSample="<<m_isTTBBSample<<"\n";

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

Bool_t CopyBranch::Select(eventForNano *e, Bool_t isData)
{
    clearBranch();//!!!important

    Bool_t ifRemoveEvent = overlapRemovalSamples(e);

    // ttbar/ttbb overlap removal using B-hadrons (CMS standard)
    // - ttbar: REMOVE events with >=1 additional B-hadron (covered by TTBB)
    // - TTBB: KEEP ONLY events with >=1 additional B-hadron (correct phase space)
    if (!isData && (m_isTtbarSample || m_isTTBBSample) && !ifRemoveEvent) {
        Int_t nAdditionalBHadrons = countAdditionalBHadrons(e);
        if (m_isTtbarSample && nAdditionalBHadrons >= 1) {
            ifRemoveEvent = kTRUE;  // Remove ttbar event with additional B-hadrons (overlap with TTBB)
        }
        if (m_isTTBBSample && nAdditionalBHadrons < 1) {
            ifRemoveEvent = kTRUE;  // Remove TTBB event WITHOUT additional B-hadrons (not in tt+bb phase space)
        }
    }

    run_ = *e->run;
    event_ = *e->event;
    luminosityBlock_ = *e->luminosityBlock;

    Double_t Met_XUp = (*e->MET_pt*TMath::Sin(*e->MET_phi) + *e->MET_MetUnclustEnUpDeltaX );
    Double_t Met_YUp = (*e->MET_pt*TMath::Cos(*e->MET_phi) + *e->MET_MetUnclustEnUpDeltaY );
    Double_t Met_XDown = (*e->MET_pt*TMath::Sin(*e->MET_phi) - *e->MET_MetUnclustEnUpDeltaX );
    Double_t Met_YDown = (*e->MET_pt*TMath::Cos(*e->MET_phi) - *e->MET_MetUnclustEnUpDeltaY );
    switch (m_MET_sys)
    { 
        case 0:
            MET_pt_ = *e->MET_pt;
            MET_phi_ = *e->MET_phi;
            break;
        case 1:
            MET_pt_ = TMath::Sqrt(Met_XUp*Met_XUp + Met_YUp*Met_YUp);
            MET_phi_ = TMath::ATan2(Met_XUp, Met_YUp);
            break;
        case 2:
            MET_pt_ = TMath::Sqrt(Met_XDown*Met_XDown + Met_YDown*Met_YDown);
            MET_phi_ = TMath::ATan2(Met_XDown, Met_YDown);
            break;  
        default: //error and exit the program
            std::cerr << "Error: MET_sys is not 0, 1, or 2\n";
            break;
    }




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

    Bool_t ifRemove = kTRUE;
    if(m_isGammaSample){
        //except events if all prompt photons not radiated from partons?
        //accept if at least one prompt photon not radiated from partons?
        for (size_t i = 0; i < e->GenPart_pdgId->GetSize(); i++)
        {
            // std::cout<<"e->GenParr_statusFlags->At(i)="<<e->GenPart_statusFlags->At(i)<<"\n"; //!!!statusFlags has very big index number, not as discribed in nanoAOD v9
            if (std::abs(e->GenPart_pdgId->At(i)) == 22 && e->GenPart_pt->At(i)>10. && e->GenPart_statusFlags->At(i)>0)
            {
                Bool_t removeIGen = OS::overlapRemove(e->GenPart_eta->At(i), e->GenPart_phi->At(i), partonsEtaVec, partonsPhiVec, 0.05); //if overlap with parton
                if(!removeIGen){
                        ifRemove = kFALSE;
                        break; // exit a loop prematurely when a certain condition is met.
                }
            }
        }
        return ifRemove;
    }
    if(m_isNotGammaSample){
        //for ttbar, DY, W, st, should remove events if all prompt photons radiated from partons
        ifRemove = kFALSE;
        for(size_t i=0; i<e->GenPart_pdgId->GetSize(); i++){
            if(std::abs(e->GenPart_pdgId->At(i))==22 && e->GenPart_pt->At(i)>10. && e->GenPart_statusFlags->At(i)>0){
                //check if only have leptons, quarks, gluons, and bosons as parents
                Int_t parentPdgId = OS::getValForDynamicReader<Short_t>(m_isRun3, e->GenPart_genPartIdxMother, i);
                Bool_t parentGood = std::abs(e->GenPart_pdgId->At(parentPdgId))<7 || std::abs(e->GenPart_pdgId->At(parentPdgId))==21 || std::abs(e->GenPart_pdgId->At(parentPdgId))==24 || std::abs(e->GenPart_pdgId->At(parentPdgId))==23 || std::abs(e->GenPart_pdgId->At(parentPdgId))==25; //<7=quarks, 21=gluons, 24=W, 23=Z, 25=Higgs
                if(!parentGood){
                    // std::cout<<"parentPdgId="<<e->GenPart_pdgId->At(parentPdgId)<<"\n";//maily phi mesons
                    continue;
                }//!seems essential to keep the gamma from meson decay
                Bool_t removeIGen = OS::overlapRemove(e->GenPart_eta->At(i), e->GenPart_phi->At(i), partonsEtaVec, partonsPhiVec, 0.05); //if overlap with parton
                if(removeIGen){
                    ifRemove = kTRUE;
                    break; // exit a loop prematurely when a certain condition is met.
                }
                // ifRemove = ifRemove && removeIGen;
            }
        }

        return ifRemove;
    }

    return ifRemove;

}

Int_t CopyBranch::countAdditionalBHadrons(const eventForNano* e) {
    // Count additional b-jets using ghost-matching (CMS standard from ttH paper)
    // "based on the flavour of the additional jets at the particle level that do not originate
    // from the top quark decays. The jet flavour is defined using the ghost-matching procedure"
    // Particle-level jets: pT > 20 GeV, |eta| < 2.4, hadronFlavour == 5 (b-jet)

    Int_t additionalBJets = 0;
    size_t nGenJet = e->GenJet_pt->GetSize();
    size_t nGenPart = e->GenPart_pdgId->GetSize();

    // Loop over GenJets
    for (size_t j = 0; j < nGenJet; j++) {
        // Apply kinematic cuts (CMS standard)
        if (e->GenJet_pt->At(j) < 20.0) continue;
        if (std::abs(e->GenJet_eta->At(j)) > 2.4) continue;

        // Check if it's a b-jet (hadronFlavour == 5)
        if (e->GenJet_hadronFlavour->At(j) != 5) continue;

        // Ghost-matching: Find B-hadrons matched to this jet (ΔR < 0.4)
        // and check if any matched B-hadron is NOT from top decay
        Bool_t hasNonTopBHadron = kFALSE;

        for (size_t p = 0; p < nGenPart; p++) {
            Int_t absId = std::abs(e->GenPart_pdgId->At(p));

            // Check if it's a B-hadron (mesons: 500-599, baryons: 5000-5999)
            Bool_t isBHadron = (absId >= 500 && absId < 600) || (absId >= 5000 && absId < 6000);
            if (!isBHadron) continue;
            if (e->GenPart_pt->At(p) < 5.0) continue;  // B-hadron pT cut

            // Calculate ΔR between jet and B-hadron
            Float_t deta = e->GenJet_eta->At(j) - e->GenPart_eta->At(p);
            Float_t dphi = e->GenJet_phi->At(j) - e->GenPart_phi->At(p);
            while (dphi > M_PI) dphi -= 2*M_PI;
            while (dphi < -M_PI) dphi += 2*M_PI;
            Float_t dR = std::sqrt(deta*deta + dphi*dphi);

            if (dR > 0.4) continue;  // Ghost-matching cone

            // Trace ancestry to check if B-hadron comes from top decay
            Bool_t fromTop = kFALSE;
            Int_t currentIdx = OS::getValForDynamicReader<Short_t>(m_isRun3, e->GenPart_genPartIdxMother, p);
            Int_t maxIterations = 30;
            Int_t iterations = 0;

            while (currentIdx >= 0 && static_cast<size_t>(currentIdx) < nGenPart && iterations < maxIterations) {
                if (std::abs(e->GenPart_pdgId->At(currentIdx)) == 6) {
                    fromTop = kTRUE;
                    break;
                }
                currentIdx = OS::getValForDynamicReader<Short_t>(m_isRun3, e->GenPart_genPartIdxMother, currentIdx);
                iterations++;
            }

            if (!fromTop) {
                hasNonTopBHadron = kTRUE;
                break;  // Found at least one non-top B-hadron, jet is "additional"
            }
        }

        if (hasNonTopBHadron) {
            additionalBJets++;
        }
    }

    return additionalBJets;
}