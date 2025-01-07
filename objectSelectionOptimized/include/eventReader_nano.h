#ifndef EVENTREADER_NANO_H
#define EVENTREADER_NANO_H

#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>
#include "usefulFunc.h"
#include "dynimicBranchReader.h"
// #include "dynanicBranchReader_noTemp.h"
// #include "TTreeReaderValueDerived.h"

// #include <vector>
class eventForNano
{
public:
    eventForNano(TTreeReader &reader) : // Muon_pt(reader, "Muon_pt"),
                                        run(reader, "run"),
                                        luminosityBlock(reader, "luminosityBlock"),
                                        PV_npvsGood(reader, "PV_npvsGood"), //initializing for type dynamicBranchReader
                                        event(reader, "event"),
                                        GenPart_genPartIdxMother(reader, "GenPart_genPartIdxMother"),
                                        Flag_goodVertices(reader, "Flag_goodVertices"),
                                        Flag_globalSuperTightHalo2016Filter(reader, "Flag_globalSuperTightHalo2016Filter"),
                                        Flag_HBHENoiseFilter(reader, "Flag_HBHENoiseFilter"),
                                        Flag_HBHENoiseIsoFilter(reader, "Flag_HBHENoiseIsoFilter"),
                                        Flag_EcalDeadCellTriggerPrimitiveFilter(reader, "Flag_EcalDeadCellTriggerPrimitiveFilter"),
                                        Flag_BadPFMuonFilter(reader, "Flag_BadPFMuonFilter"),
                                        Flag_BadPFMuonDzFilter(reader, "Flag_BadPFMuonDzFilter"),
                                        Flag_eeBadScFilter(reader, "Flag_eeBadScFilter"),
                                        Flag_ecalBadCalibFilter(reader, "Flag_ecalBadCalibFilter"),
                                        //
                                        // nElectron(reader, "nElectron"),
                                        Electron_pt(reader, "Electron_pt"),
                                        Electron_eta(reader, "Electron_eta"),
                                        Electron_cutBased(reader, "Electron_cutBased"),
                                        Electron_dxy(reader, "Electron_dxy"),
                                        Electron_dz(reader, "Electron_dz"),
                                        Electron_ip3d(reader, "Electron_ip3d"),
                                        Electron_miniPFRelIso_all(reader, "Electron_miniPFRelIso_all"),
                                        Electron_lostHits(reader, "Electron_lostHits"),
                                        Electron_convVeto(reader, "Electron_convVeto"),
                                        Electron_tightCharge(reader, "Electron_tightCharge"),
                                        Electron_jetRelIso(reader, "Electron_jetRelIso"),
                                        Electron_jetIdx(reader, "Electron_jetIdx"),
                                        Electron_jetNDauCharged(reader, "Electron_jetNDauCharged"),
                                        Electron_miniPFRelIso_chg(reader, "Electron_miniPFRelIso_chg"),
                                        Electron_jetPtRelv2(reader, "Electron_jetPtRelv2"),
                                        Electron_pfRelIso03_all(reader, "Electron_pfRelIso03_all"),
                                        Electron_sip3d(reader, "Electron_sip3d"),
                                        Electron_phi(reader, "Electron_phi"),
                                        Electron_mass(reader, "Electron_mass"),
                                        Electron_charge(reader, "Electron_charge"),
                                        Electron_r9(reader, "Electron_r9"),
                                        Electron_seedGain(reader, "Electron_seedGain"),
                                        Electron_mvaFall17V2noIso_WPL(reader, "Electron_mvaFall17V2noIso_WPL"),
                                        // muon
                                        Muon_pt(reader, "Muon_pt"),
                                        Muon_eta(reader, "Muon_eta"),
                                        Muon_looseId(reader, "Muon_looseId"),
                                        Muon_dxy(reader, "Muon_dxy"),
                                        Muon_dz(reader, "Muon_dz"),
                                        Muon_ip3d(reader, "Muon_ip3d"),
                                        Muon_miniPFRelIso_all(reader, "Muon_miniPFRelIso_all"),
                                        Muon_mediumId(reader, "Muon_mediumId"),
                                        Muon_tightId(reader, "Muon_tightId"),
                                        Muon_jetRelIso(reader, "Muon_jetRelIso"),
                                        Muon_jetIdx(reader, "Muon_jetIdx"),
                                        Muon_jetNDauCharged(reader, "Muon_jetNDauCharged"),
                                        Muon_miniPFRelIso_chg(reader, "Muon_miniPFRelIso_chg"),
                                        Muon_jetPtRelv2(reader, "Muon_jetPtRelv2"),
                                        Muon_pfRelIso03_all(reader, "Muon_pfRelIso03_all"),
                                        Muon_segmentComp(reader, "Muon_segmentComp"),
                                        Muon_sip3d(reader, "Muon_sip3d"),
                                        Muon_mass(reader, "Muon_mass"),
                                        Muon_phi(reader, "Muon_phi"),
                                        Muon_charge(reader, "Muon_charge"),
                                        Muon_miniIsoId(reader, "Muon_miniIsoId"),
                                        Muon_tightCharge(reader, "Muon_tightCharge"),
                                        Muon_nTrackerLayers(reader, "Muon_nTrackerLayers"),
                                        // tau
                                        Tau_pt(reader, "Tau_pt"),
                                        Tau_mass(reader, "Tau_mass"),
                                        Tau_eta(reader, "Tau_eta"),
                                        Tau_phi(reader, "Tau_phi"),
                                        Tau_dz(reader, "Tau_dz"),
                                        Tau_idDeepTau2017v2p1VSjet(reader, "Tau_idDeepTau2017v2p1VSjet"),
                                        Tau_idDeepTau2017v2p1VSe(reader, "Tau_idDeepTau2017v2p1VSe"),
                                        Tau_idDeepTau2017v2p1VSmu(reader, "Tau_idDeepTau2017v2p1VSmu"),
                                        // Tau_idDeepTau2018v2p5VSjet(reader, "Tau_idDeepTau2018v2p5VSjet"),
                                        // Tau_idDeepTau2018v2p5VSe(reader, "Tau_idDeepTau2018v2p5VSe"),
                                        // Tau_idDeepTau2018v2p5VSmu(reader, "Tau_idDeepTau2018v2p5VSmu"),
                                        Tau_decayMode(reader, "Tau_decayMode"),
                                        Tau_jetIdx(reader, "Tau_jetIdx"),
                                        Tau_charge(reader, "Tau_charge"),
                                        Tau_neutralIso(reader, "Tau_neutralIso"),
                                        // Tau_idDecayModeNewDMs(reader, "Tau_idDecayModeNewDMs"),
                                        // jet
                                        Jet_btagDeepFlavB(reader, "Jet_btagDeepFlavB"),
                                        Jet_pt(reader, "Jet_pt"),
                                        Jet_mass(reader, "Jet_mass"),
                                        Jet_eta(reader, "Jet_eta"),
                                        Jet_phi(reader, "Jet_phi"),
                                        Jet_jetId(reader, "Jet_jetId"),
                                        Jet_hadronFlavour(reader, "Jet_hadronFlavour"),
                                        Jet_area(reader, "Jet_area"),
                                        MET_pt(reader, "MET_pt"),
                                        MET_phi(reader, "MET_phi"),
                                        MET_MetUnclustEnUpDeltaX(reader, "MET_MetUnclustEnUpDeltaX"),
                                        MET_MetUnclustEnUpDeltaY(reader, "MET_MetUnclustEnUpDeltaY")

    {
        // dealing with case: HLT branch not existing in this nanofile;
        // assing the reader branch 0 if the branch not existing
        // it seems to reader can not run at all if assosiated with not existing branch
        OS::readPointer(L1PreFiringWeight_Nom, reader, "L1PreFiringWeight_Nom");
        OS::readPointer(L1PreFiringWeight_Up, reader, "L1PreFiringWeight_Up");
        OS::readPointer(L1PreFiringWeight_Dn, reader, "L1PreFiringWeight_Dn");

        OS::readPointer(HLT_PFHT450_SixJet40_BTagCSV_p056, reader, "HLT_PFHT450_SixJet40_BTagCSV_p056");
        OS::readPointer(HLT_PFHT400_SixJet30_DoubleBTagCSV_p056, reader, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056");
        OS::readPointer(HLT_PFJet450, reader, "HLT_PFJet450");

        OS::readPointer(HLT_PFJet500, reader, "HLT_PFJet500");
        OS::readPointer(HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94, reader, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94");
        OS::readPointer(HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59, reader, "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59");
        OS::readPointer(HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2, reader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2");
        OS::readPointer(HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5, reader, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5");
        OS::readPointer(HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5, reader, "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5");
        OS::readPointer(HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5, reader, "HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5");
        //
        OS::readPointer(HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ, reader, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ");
        OS::readPointer(HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8, reader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8");//!this should be back up trigger path, and it's not active all year in 2017
        OS::readPointer(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, reader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
        OS::readPointer(HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, reader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
        // 2017
        OS::readPointer(HLT_PFHT430_SixJet40_BTagCSV_p080, reader, "HLT_PFHT430_SixJet40_BTagCSV_p080");
        OS::readPointer(HLT_PFHT380_SixJet32_DoubleBTagCSV_p075, reader, "HLT_PFHT380_SixJet32_DoubleBTagCSV_p075");
        OS::readPointer(HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2, reader, "HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2");
        OS::readPointer(HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0, reader, "HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0");
        OS::readPointer(HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07, reader, "HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07");
        OS::readPointer(HLT_PFHT1050, reader, "HLT_PFHT1050");
        // 2022
        OS::readPointer(HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94, reader, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94");
        OS::readPointer(HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59, reader, "HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59");
        OS::readPointer(HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5, reader, "HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5");
        OS::readPointer(HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5, reader, "HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5");
        OS::readPointer(HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5, reader, "HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5");
        //
        OS::readPointer(HLT_IsoMu24, reader, "HLT_IsoMu24");
        OS::readPointer(HLT_IsoMu27, reader, "HLT_IsoMu27");
        OS::readPointer(HLT_IsoTkMu24, reader, "HLT_IsoTkMu24");
        OS::readPointer(HLT_Ele32_WPTight_Gsf, reader, "HLT_Ele32_WPTight_Gsf");
        OS::readPointer(HLT_Ele35_WPTight_Gsf, reader, "HLT_Ele35_WPTight_Gsf");
        OS::readPointer(HLT_Ele27_WPTight_Gsf, reader, "HLT_Ele27_WPTight_Gsf");

        OS::readPointer(HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8, reader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8");
        OS::readPointer(HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL, reader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL");
        OS::readPointer(HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ, reader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ");
        //2016
        OS::readPointer(HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL, reader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL");
        OS::readPointer(HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ, reader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ");
        OS::readPointer(HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ, reader, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ");
        OS::readPointer(HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL, reader, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL");
        OS::readPointer(HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ, reader, "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ");
        OS::readPointer(HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL, reader, "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL");
        OS::readPointer(HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL, reader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL");
        OS::readPointer(HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL, reader, "HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
        OS::readPointer(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL, reader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");


        // OS::readPointer(HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1, reader, "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1");
        // OS::readPointer(HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1, reader, "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1");
        // OS::readPointer(HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1, reader, "HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1");


        // gen
        OS::readPointerArray(GenJet_eta, reader, "GenJet_eta");
        OS::readPointerArray(GenJet_phi, reader, "GenJet_phi");
        OS::readPointerArray(GenJet_pt, reader, "GenJet_pt");
        OS::readPointerArray(GenPart_pdgId, reader, "GenPart_pdgId");
        // OS::readPointerArray(GenPart_genPartIdxMother, reader, "GenPart_genPartIdxMother");
        OS::readPointer(Pileup_nTrueInt, reader, "Pileup_nTrueInt");
        OS::readPointer(genWeight, reader, "genWeight");
        OS::readPointerArray(Tau_genPartFlav, reader, "Tau_genPartFlav");
        OS::readPointer(nGenVisTau, reader, "nGenVisTau");
        OS::readPointerArray(Electron_genPartFlav, reader, "Electron_genPartFlav");
        OS::readPointerArray(Muon_genPartFlav, reader, "Muon_genPartFlav");
        OS::readPointerArray(GenPart_eta, reader, "GenPart_eta");
        OS::readPointerArray(GenPart_phi, reader, "GenPart_phi");
        OS::readPointerArray(GenPart_pt, reader, "GenPart_pt");
        OS::readPointerArray(GenPart_statusFlags, reader, "GenPart_statusFlags");
        OS::readPointerArray(Muon_genPartIdx, reader, "Muon_genPartIdx");

        // other branch not consistent between run2 and run3
        OS::readPointerArray(Electron_mvaFall17V2noIso, reader, "Electron_mvaFall17V2noIso");
        // OS::readPointerArray(Electron_mvaNoIso_Fall17V2, reader, "Electron_mvaNoIso_Fall17V2");
        OS::readPointerArray(Electron_mvaNoIso, reader, "Electron_mvaNoIso");
        OS::readPointerArray(Electron_mvaFall17V2Iso_WP90, reader, "Electron_mvaFall17V2Iso_WP90");
        // OS::readPointerArray(Electron_mvaIso_Fall17V2_WP90, reader, "Electron_mvaIso_Fall17V2_WP90");
        OS::readPointerArray(Electron_mvaIso_WP90, reader, "Electron_mvaIso_WP90");
        OS::readPointerArray(Tau_idDeepTau2018v2p5VSjet, reader, "Tau_idDeepTau2018v2p5VSjet");
        OS::readPointerArray(Tau_idDeepTau2018v2p5VSe, reader, "Tau_idDeepTau2018v2p5VSe");
        OS::readPointerArray(Tau_idDeepTau2018v2p5VSmu, reader, "Tau_idDeepTau2018v2p5VSmu");
        OS::readPointerArray(Tau_idDecayModeNewDMs, reader, "Tau_idDecayModeNewDMs");
        //
        OS::readPointerArray(Jet_btagDeepB, reader, "Jet_btagDeepB");
        OS::readPointerArray(Jet_btagPNetB, reader, "Jet_btagPNetB");
        OS::readPointerArray(Jet_btagRobustParTAK4B, reader, "Jet_btagRobustParTAK4B");
        //
        OS::readPointer(fixedGridRhoFastjetAll, reader, "fixedGridRhoFastjetAll");
        OS::readPointer(Rho_fixedGridRhoFastjetAll, reader, "Rho_fixedGridRhoFastjetAll");
        OS::readPointerArray(LHEPdfWeight, reader, "LHEPdfWeight");
        OS::readPointerArray(LHEScaleWeight, reader, "LHEScaleWeight");
        OS::readPointerArray(PSWeight, reader, "PSWeight");

    };

    // eventForNano(TTreeReader &reader)
    // {
    //     nElectron = new TTreeReaderValue<UInt_t>(reader, "nElectron");
    //     //!!! the pointer initialization is okay but too lengthy to access

    // }

    ~eventForNano(){
        //!!! seems to cause problem together with delete e
        // delete HLT_PFHT450_SixJet40_BTagCSV_p056;
        //!!!delete other pointers
    };

    TTreeReaderValue<UInt_t> run;
    TTreeReaderValue<UInt_t> luminosityBlock;
    // TTreeReaderValue<Int_t> PV_npvsGood;
    DynamicBranchReader PV_npvsGood; ////!!! UChar_t in nanoAOD v12

    TTreeReaderValue<ULong64_t> event;
    TTreeReaderValue<Float_t>* L1PreFiringWeight_Nom = nullptr;//!!!not existing in nanoAOD v12
    TTreeReaderValue<Float_t>* L1PreFiringWeight_Up = nullptr;
    TTreeReaderValue<Float_t>* L1PreFiringWeight_Dn = nullptr;

    // HLT reading: tricky!!!
    // for some files the trigger not present, trigger branch not exsit
    // for some files cross the run range of trigger validity, trigger branch exsit but the subset invalid range is set to 0. need to further check this through
    // 2016 trigger
    // TTreeReaderValue<Bool_t> HLT_PFHT450_SixJet40_BTagCSV_p056;
    TTreeReaderValue<Bool_t> *HLT_PFHT450_SixJet40_BTagCSV_p056 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFJet450 = nullptr;
    // TTreeReaderValue<Bool_t> * = nullptr;
    // 2018
    TTreeReaderValue<Bool_t> *HLT_PFJet500 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 = nullptr;
    // TRIGGERS FOR 2018 data A
    TTreeReaderValue<Bool_t> *HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = nullptr; //17.7	315252	317488	
    TTreeReaderValue<Bool_t> *HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = nullptr;
    // 2018 for only some small slices of 2018 A (CSV b tag instead of DeepCSV btag)
    TTreeReaderValue<Bool_t> *HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 = nullptr;//active lumi 59.8
    //dileptonic triggers 
    TTreeReaderValue<Bool_t> *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = nullptr;
    TTreeReaderValue<Bool_t> *HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = nullptr;
    TTreeReaderValue<Bool_t> *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = nullptr;
    //single lepton triggers
    TTreeReaderValue<Bool_t> *HLT_IsoMu24 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_IsoMu27 = nullptr; //only 2017
    TTreeReaderValue<Bool_t> *HLT_IsoTkMu24 = nullptr;//extra for 2016
    TTreeReaderValue<Bool_t> *HLT_Ele32_WPTight_Gsf = nullptr;
    TTreeReaderValue<Bool_t> *HLT_Ele35_WPTight_Gsf = nullptr;//only 2017
    TTreeReaderValue<Bool_t> *HLT_Ele27_WPTight_Gsf = nullptr;//only 2016
    //2017
    TTreeReaderValue<Bool_t> *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = nullptr;
    TTreeReaderValue<Bool_t> *HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = nullptr;
    // TTreeReaderValue<Bool_t> *HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = nullptr;
    //2016
    TTreeReaderValue<Bool_t>*    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL = nullptr;
    TTreeReaderValue<Bool_t>*    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = nullptr;
    TTreeReaderValue<Bool_t>*    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = nullptr;
    TTreeReaderValue<Bool_t>*    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL = nullptr;
    TTreeReaderValue<Bool_t>*    HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = nullptr;
    TTreeReaderValue<Bool_t>*    HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL = nullptr;
    // TTreeReaderValue<Bool_t>*    // HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = nullptr;
    // TTreeReaderValue<Bool_t>*    // // HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v(24.9 272760 284044 = nullptr;
    TTreeReaderValue<Bool_t>*    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL = nullptr;
    TTreeReaderValue<Bool_t>*    HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = nullptr;
    TTreeReaderValue<Bool_t>*    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = nullptr;
    // HLT_IsoMu24 OR HLT_IsoTkMu24
    // HLT_Ele27_WPTight_Gsf




    // 2017
    TTreeReaderValue<Bool_t> *HLT_PFHT430_SixJet40_BTagCSV_p080 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT380_SixJet32_DoubleBTagCSV_p075 = nullptr; // run<299329
    // TTreeReaderValue<Bool_t> *HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 = nullptr; // run<=306460 2017 end
    TTreeReaderValue<Bool_t> *HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0 = nullptr; // run>=299368; BtagCSV dataset in 2017
    TTreeReaderValue<Bool_t> *HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT1050 = nullptr;

    // 2022
    TTreeReaderValue<Bool_t> *HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5 = nullptr;
    //

    //tau triggers
    // TTreeReaderValue<Bool_t> *HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1 = nullptr;
    // TTreeReaderValue<Bool_t> *HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1 = nullptr;
    // TTreeReaderValue<Bool_t> *HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1 = nullptr;


    TTreeReaderArray<Float_t> *GenJet_eta = nullptr;
    TTreeReaderArray<Float_t> *GenJet_phi = nullptr;
    TTreeReaderArray<Float_t> *GenJet_pt = nullptr;
    TTreeReaderArray<Int_t> *GenPart_pdgId = nullptr;
    DynamicBranchReader GenPart_genPartIdxMother;
    TTreeReaderValue<Float_t> *Pileup_nTrueInt = nullptr;
    TTreeReaderValue<Float_t> *genWeight = nullptr;
    TTreeReaderArray<Float_t> *GenPart_eta = nullptr;
    TTreeReaderArray<Float_t> *GenPart_phi = nullptr;
    TTreeReaderArray<Float_t> *GenPart_pt = nullptr;
    TTreeReaderArray<Int_t> *GenPart_statusFlags = nullptr;
    TTreeReaderArray<Int_t> *Muon_genPartIdx = nullptr;
    //theoretical 
    // TTreeReaderArray<Float_t> LHEPdfWeight ; //LHE pdf variation weights (w_var / w_nominal) for LHA IDs 306000 - 306102
    //https://lhapdf.hepforge.org/pdfsets

    TTreeReaderArray<UChar_t> *Tau_genPartFlav = nullptr;
    TTreeReaderValue<UInt_t> *nGenVisTau = nullptr;

    // METFilters
    TTreeReaderValue<Bool_t> Flag_goodVertices;
    TTreeReaderValue<Bool_t> Flag_globalSuperTightHalo2016Filter;
    TTreeReaderValue<Bool_t> Flag_HBHENoiseFilter;
    TTreeReaderValue<Bool_t> Flag_HBHENoiseIsoFilter;
    TTreeReaderValue<Bool_t> Flag_EcalDeadCellTriggerPrimitiveFilter;
    TTreeReaderValue<Bool_t> Flag_BadPFMuonFilter;
    TTreeReaderValue<Bool_t> Flag_BadPFMuonDzFilter;
    TTreeReaderValue<Bool_t> Flag_eeBadScFilter;
    TTreeReaderValue<Bool_t> Flag_ecalBadCalibFilter;

    //
    // TTreeReaderValue<UInt_t> nElectron; //!!!
    TTreeReaderArray<Float_t> Electron_pt;
    TTreeReaderArray<Float_t> Electron_eta;
    // TTreeReaderArray<Int_t> Electron_cutBased;//!!!
    DynamicBranchReader Electron_cutBased;//!!!UChar_t in nanoAOD v12
    TTreeReaderArray<Float_t> Electron_dxy;
    TTreeReaderArray<Float_t> Electron_dz;
    TTreeReaderArray<Float_t> Electron_ip3d;
    TTreeReaderArray<Float_t> Electron_miniPFRelIso_all;
    TTreeReaderArray<UChar_t> Electron_lostHits;
    TTreeReaderArray<Bool_t> Electron_convVeto;
    DynamicBranchReader Electron_tightCharge; //!!!
    TTreeReaderArray<Float_t> Electron_jetRelIso;
    DynamicBranchReader Electron_jetIdx;//!!!
    TTreeReaderArray<UChar_t> Electron_jetNDauCharged;
    TTreeReaderArray<Float_t> Electron_miniPFRelIso_chg;
    TTreeReaderArray<Float_t> Electron_jetPtRelv2;
    TTreeReaderArray<Float_t> Electron_pfRelIso03_all;
    TTreeReaderArray<Float_t> Electron_sip3d;
    TTreeReaderArray<Float_t> *Electron_mvaFall17V2noIso=nullptr;    //??? not vailable in Run3
    // TTreeReaderArray<Float_t> *Electron_mvaNoIso_Fall17V2;   //??? not vailable in run2
    TTreeReaderArray<Float_t> *Electron_mvaNoIso = nullptr; //!!!nanoAODv12, MVA noIso ID score, Winter22V1
    TTreeReaderArray<Bool_t> *Electron_mvaFall17V2Iso_WP90;  //!!!run2
    // TTreeReaderArray<Bool_t> *Electron_mvaIso_Fall17V2_WP90; //!!!run3 not available in nanoAODv12
    TTreeReaderArray<Bool_t> *Electron_mvaIso_WP90 = nullptr; //!!!nanoAODv12, MVA Iso ID WP90, Winter22V1
    TTreeReaderArray<Float_t> Electron_phi;
    TTreeReaderArray<Float_t> Electron_mass;
    TTreeReaderArray<Int_t> Electron_charge;
    TTreeReaderArray<Float_t> Electron_r9;
    TTreeReaderArray<UChar_t> Electron_seedGain;
    TTreeReaderArray<Bool_t> Electron_mvaFall17V2noIso_WPL;
    TTreeReaderArray<UChar_t>* Electron_genPartFlav = nullptr; //Flavour of genParticle (DressedLeptons for electrons) for MC matching to status==1 electrons or photons: 1 = prompt electron (including gamma*->mu mu), 15 = electron from prompt tau, 22 = prompt photon (likely conversion), 5 = electron from b, 4 = electron from c, 3 = electron from light or unknown, 0 = unmatched
    // muon
    TTreeReaderArray<Float_t> Muon_pt;
    TTreeReaderArray<Float_t> Muon_eta;
    TTreeReaderArray<Bool_t> Muon_looseId;
    TTreeReaderArray<Float_t> Muon_dxy;
    TTreeReaderArray<Float_t> Muon_dz;
    TTreeReaderArray<Float_t> Muon_ip3d;
    TTreeReaderArray<Float_t> Muon_miniPFRelIso_all;
    TTreeReaderArray<Bool_t> Muon_mediumId;
    TTreeReaderArray<Bool_t> Muon_tightId;
    TTreeReaderArray<Float_t> Muon_jetRelIso;
    DynamicBranchReader Muon_jetIdx; //!!!
    TTreeReaderArray<UChar_t> Muon_jetNDauCharged;
    TTreeReaderArray<Float_t> Muon_miniPFRelIso_chg;
    TTreeReaderArray<Float_t> Muon_jetPtRelv2;
    TTreeReaderArray<Float_t> Muon_pfRelIso03_all;
    TTreeReaderArray<Float_t> Muon_segmentComp;
    TTreeReaderArray<Float_t> Muon_sip3d;
    TTreeReaderArray<Float_t> Muon_mass;
    TTreeReaderArray<Float_t> Muon_phi;
    TTreeReaderArray<Int_t> Muon_charge;
    TTreeReaderArray<UChar_t> Muon_miniIsoId;
    TTreeReaderArray<UChar_t>* Muon_genPartFlav = nullptr;
    DynamicBranchReader Muon_tightCharge; //!!!
    TTreeReaderArray<Int_t> Muon_nTrackerLayers;
    // tau
    TTreeReaderArray<Float_t> Tau_pt;
    TTreeReaderArray<Float_t> Tau_mass;
    TTreeReaderArray<Float_t> Tau_eta;
    TTreeReaderArray<Float_t> Tau_phi;
    TTreeReaderArray<Float_t> Tau_dz;
    TTreeReaderArray<UChar_t> Tau_idDeepTau2017v2p1VSjet;
    TTreeReaderArray<UChar_t> Tau_idDeepTau2017v2p1VSe;
    TTreeReaderArray<UChar_t> Tau_idDeepTau2017v2p1VSmu;
    TTreeReaderArray<UChar_t> *Tau_idDeepTau2018v2p5VSjet = nullptr ; //!!!run3
    TTreeReaderArray<UChar_t> *Tau_idDeepTau2018v2p5VSe = nullptr;
    TTreeReaderArray<UChar_t> *Tau_idDeepTau2018v2p5VSmu = nullptr;
    DynamicBranchReader Tau_decayMode;//!!!
    DynamicBranchReader Tau_jetIdx;//!!!
    DynamicBranchReader Tau_charge;//!!!
    TTreeReaderArray<Float_t> Tau_neutralIso;
    TTreeReaderArray<Bool_t>* Tau_idDecayModeNewDMs=nullptr;//!!!nanoAODv12

    TTreeReaderArray<Float_t> Jet_btagDeepFlavB;
    TTreeReaderArray<Float_t>* Jet_btagDeepB = nullptr;
    TTreeReaderArray<Float_t>* Jet_btagPNetB = nullptr;
    TTreeReaderArray<Float_t>* Jet_btagRobustParTAK4B = nullptr;
    TTreeReaderArray<Float_t> Jet_pt;
    TTreeReaderArray<Float_t> Jet_mass;
    TTreeReaderArray<Float_t> Jet_eta;
    TTreeReaderArray<Float_t> Jet_phi;
    DynamicBranchReader Jet_jetId;//!!!
    DynamicBranchReader Jet_hadronFlavour;
    TTreeReaderArray<Float_t> Jet_area;
    TTreeReaderValue<Float_t> *fixedGridRhoFastjetAll = nullptr;    //!!!not existing in nanoAOD v12
    TTreeReaderValue<Float_t>* Rho_fixedGridRhoFastjetAll = nullptr;//nanoAODv12

    TTreeReaderValue<Float_t> MET_pt;
    TTreeReaderValue<Float_t> MET_phi;
    TTreeReaderValue<Float_t> MET_MetUnclustEnUpDeltaX;
    TTreeReaderValue<Float_t> MET_MetUnclustEnUpDeltaY;

    TTreeReaderArray<Float_t> *LHEPdfWeight = nullptr;
    TTreeReaderArray<Float_t> *LHEScaleWeight = nullptr;
    TTreeReaderArray<Float_t> *PSWeight = nullptr;
};

#endif