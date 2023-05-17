#ifndef EVENTREADER_NANO_H
#define EVENTREADER_NANO_H

// class branch
// {
// public:
//     branch(TTree *tree, TString branchName)
//     {
//         tree->SetBranchAddress(branchName, m_value);
//     }

// }

class eventForNano
{
public:
    eventForNano(TTree *tree)
    {
        m_reader = new TTreeReader(tree);
    };
    TTreeReader *m_reader;
    <UInt_t> nElectron = {fReader, "nElectron"};
    std::vector<Float_t> Electron_dxy = {fReader, "Electron_dxy"};
    std::vector<Float_t> Electron_dxyErr = {fReader, "Electron_dxyErr"};
    std::vector<Float_t> Electron_dz = {fReader, "Electron_dz"};
    std::vector<Float_t> Electron_eta = {fReader, "Electron_eta"};
    std::vector<Float_t> Electron_ip3d = {fReader, "Electron_ip3d"};
    std::vector<Float_t> Electron_jetPtRelv2 = {fReader, "Electron_jetPtRelv2"};
    std::vector<Float_t> Electron_jetRelIso = {fReader, "Electron_jetRelIso"};
    std::vector<Float_t> Electron_mass = {fReader, "Electron_mass"};
    std::vector<Float_t> Electron_miniPFRelIso_all = {fReader, "Electron_miniPFRelIso_all"};
    std::vector<Float_t> Electron_miniPFRelIso_chg = {fReader, "Electron_miniPFRelIso_chg"};
    std::vector<Float_t> Electron_mvaFall17V2Iso = {fReader, "Electron_mvaFall17V2Iso"};
    std::vector<Float_t> Electron_mvaFall17V2noIso = {fReader, "Electron_mvaFall17V2noIso"};
    std::vector<Float_t> Electron_pfRelIso03_all = {fReader, "Electron_pfRelIso03_all"};
    std::vector<Float_t> Electron_phi = {fReader, "Electron_phi"};
    std::vector<Float_t> Electron_pt = {fReader, "Electron_pt"};
    std::vector<Float_t> Electron_sip3d = {fReader, "Electron_sip3d"};
    std::vector<Int_t> Electron_charge = {fReader, "Electron_charge"};
    std::vector<Int_t> Electron_cutBased = {fReader, "Electron_cutBased"};
    std::vector<Int_t> Electron_jetIdx = {fReader, "Electron_jetIdx"};
    std::vector<Int_t> Electron_tightCharge = {fReader, "Electron_tightCharge"};
    std::vector<Bool_t> Electron_convVeto = {fReader, "Electron_convVeto"};
    std::vector<UChar_t> Electron_jetNDauCharged = {fReader, "Electron_jetNDauCharged"};
    std::vector<UChar_t> Electron_lostHits = {fReader, "Electron_lostHits"};
    std::vector<Bool_t> Electron_mvaFall17V2Iso_WP80 = {fReader, "Electron_mvaFall17V2Iso_WP80"};
    std::vector<Bool_t> Electron_mvaFall17V2Iso_WP90 = {fReader, "Electron_mvaFall17V2Iso_WP90"};
    std::vector<Bool_t> Electron_mvaFall17V2Iso_WPL = {fReader, "Electron_mvaFall17V2Iso_WPL"};
    std::vector<Bool_t> Electron_mvaFall17V2noIso_WP80 = {fReader, "Electron_mvaFall17V2noIso_WP80"};
    std::vector<Bool_t> Electron_mvaFall17V2noIso_WP90 = {fReader, "Electron_mvaFall17V2noIso_WP90"};
    std::vector<Bool_t> Electron_mvaFall17V2noIso_WPL = {fReader, "Electron_mvaFall17V2noIso_WPL"};
    std::vector<Float_t> GenJet_eta = {fReader, "Electron_dz"}; //!!!need to overwrite for MC!!!

    std::vector<Float_t> GenJet_phi = {fReader, "Electron_dz"};
    std::vector<Float_t> GenJet_pt = {fReader, "Electron_dz"};
    <UInt_t> nGenPart = {fReader, "nElectron"};
    std::vector<Float_t> GenPart_eta = {fReader, "Electron_dz"};
    std::vector<Float_t> GenPart_mass = {fReader, "Electron_dz"};
    std::vector<Float_t> GenPart_phi = {fReader, "Electron_dz"};
    std::vector<Float_t> GenPart_pt = {fReader, "Electron_dz"};
    std::vector<Int_t> GenPart_genPartIdxMother = {fReader, "Electron_charge"};
    std::vector<Int_t> GenPart_pdgId = {fReader, "Electron_charge"};

    <Float_t> Generator_weight = {fReader, "L1PreFiringWeight_Nom"};
    <Float_t> genWeight = {fReader, "L1PreFiringWeight_Nom"};
    std::vector<Float_t> IsoTrack_eta = {fReader, "IsoTrack_eta"};
    std::vector<Float_t> IsoTrack_phi = {fReader, "IsoTrack_phi"};
    std::vector<Float_t> IsoTrack_pt = {fReader, "IsoTrack_pt"};
    <UInt_t> nJet = {fReader, "nJet"};
    std::vector<Float_t> Jet_btagCSVV2 = {fReader, "Jet_btagCSVV2"};
    std::vector<Float_t> Jet_btagDeepB = {fReader, "Jet_btagDeepB"};
    std::vector<Float_t> Jet_btagDeepCvB = {fReader, "Jet_btagDeepCvB"};
    std::vector<Float_t> Jet_btagDeepCvL = {fReader, "Jet_btagDeepCvL"};
    std::vector<Float_t> Jet_btagDeepFlavB = {fReader, "Jet_btagDeepFlavB"};
    std::vector<Float_t> Jet_btagDeepFlavCvB = {fReader, "Jet_btagDeepFlavCvB"};
    std::vector<Float_t> Jet_btagDeepFlavCvL = {fReader, "Jet_btagDeepFlavCvL"};
    std::vector<Float_t> Jet_btagDeepFlavQG = {fReader, "Jet_btagDeepFlavQG"};
    std::vector<Float_t> Jet_eta = {fReader, "Jet_eta"};
    std::vector<Float_t> Jet_mass = {fReader, "Jet_mass"};
    std::vector<Float_t> Jet_phi = {fReader, "Jet_phi"};
    std::vector<Float_t> Jet_pt = {fReader, "Jet_pt"};
    std::vector<Float_t> Jet_rawFactor = {fReader, "Jet_rawFactor"};
    std::vector<Int_t> Jet_jetId = {fReader, "Jet_jetId"};
    <Float_t> L1PreFiringWeight_Dn = {fReader, "L1PreFiringWeight_Dn"};
    <Float_t> L1PreFiringWeight_Nom = {fReader, "L1PreFiringWeight_Nom"};
    <Float_t> L1PreFiringWeight_Up = {fReader, "L1PreFiringWeight_Up"};
    <Float_t> MET_phi = {fReader, "MET_phi"};
    <Float_t> MET_pt = {fReader, "MET_pt"};
    <UInt_t> nMuon = {fReader, "nMuon"};
    std::vector<Float_t> Muon_dxy = {fReader, "Muon_dxy"};
    std::vector<Float_t> Muon_dz = {fReader, "Muon_dz"};
    std::vector<Float_t> Muon_eta = {fReader, "Muon_eta"};
    std::vector<Float_t> Muon_ip3d = {fReader, "Muon_ip3d"};
    std::vector<Float_t> Muon_jetPtRelv2 = {fReader, "Muon_jetPtRelv2"}; // Relative momentum of the lepton with respect to the closest jet after subtracting the lepton
    std::vector<Float_t> Muon_jetRelIso = {fReader, "Muon_jetRelIso"};
    std::vector<Float_t> Muon_mass = {fReader, "Muon_mass"};
    std::vector<Float_t> Muon_miniPFRelIso_all = {fReader, "Muon_miniPFRelIso_all"};
    std::vector<Float_t> Muon_miniPFRelIso_chg = {fReader, "Muon_miniPFRelIso_chg"};
    std::vector<Float_t> Muon_pfRelIso03_all = {fReader, "Muon_pfRelIso03_all"};
    std::vector<Float_t> Muon_pfRelIso04_all = {fReader, "Muon_pfRelIso04_all"};
    std::vector<Float_t> Muon_phi = {fReader, "Muon_phi"};
    std::vector<Float_t> Muon_pt = {fReader, "Muon_pt"};
    std::vector<Float_t> Muon_segmentComp = {fReader, "Muon_segmentComp"};
    std::vector<Float_t> Muon_sip3d = {fReader, "Muon_sip3d"};
    std::vector<Int_t> Muon_charge = {fReader, "Muon_charge"};
    std::vector<Int_t> Muon_jetIdx = {fReader, "Muon_jetIdx"};
    std::vector<Int_t> Muon_tightCharge = {fReader, "Muon_tightCharge"};
    std::vector<UChar_t> Muon_jetNDauCharged = {fReader, "Muon_jetNDauCharged"};
    std::vector<Bool_t> Muon_looseId = {fReader, "Muon_looseId"};
    std::vector<Bool_t> Muon_mediumId = {fReader, "Muon_mediumId"};
    std::vector<UChar_t> Muon_miniIsoId = {fReader, "Muon_miniIsoId"};
    <Float_t> fixedGridRhoFastjetAll = {fReader, "fixedGridRhoFastjetAll"};
    <UInt_t> nTau = {fReader, "nTau"};
    std::vector<Float_t> Tau_dxy = {fReader, "Tau_dxy"};
    std::vector<Float_t> Tau_dz = {fReader, "Tau_dz"};
    std::vector<Float_t> Tau_eta = {fReader, "Tau_eta"};
    std::vector<Float_t> Tau_mass = {fReader, "Tau_mass"};
    std::vector<Float_t> Tau_neutralIso = {fReader, "Tau_neutralIso"};
    std::vector<Float_t> Tau_phi = {fReader, "Tau_phi"};
    std::vector<Float_t> Tau_pt = {fReader, "Tau_pt"};
    std::vector<Int_t> Tau_charge = {fReader, "Tau_charge"};
    std::vector<Int_t> Tau_decayMode = {fReader, "Tau_decayMode"};
    std::vector<Int_t> Tau_jetIdx = {fReader, "Tau_jetIdx"};
    std::vector<Bool_t> Tau_idDecayModeOldDMs = {fReader, "Tau_idDecayModeOldDMs"};
    std::vector<UChar_t> Tau_idDeepTau2017v2p1VSe = {fReader, "Tau_idDeepTau2017v2p1VSe"};
    std::vector<UChar_t> Tau_idDeepTau2017v2p1VSjet = {fReader, "Tau_idDeepTau2017v2p1VSjet"};
    std::vector<UChar_t> Tau_idDeepTau2017v2p1VSmu = {fReader, "Tau_idDeepTau2017v2p1VSmu"};
    <Int_t> genTtbarId = {fReader, "PV_npvs"};
    <Int_t> PV_npvs = {fReader, "PV_npvs"};
    <Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};
    std::vector<Int_t> Jet_hadronFlavour = {fReader, "Electron_charge"};
    std::vector<UChar_t> Tau_genPartFlav = {fReader, "Electron_jetNDauCharged"};
    <Bool_t> Flag_HBHENoiseFilter = {fReader, "Flag_HBHENoiseFilter"};
    <Bool_t> Flag_HBHENoiseIsoFilter = {fReader, "Flag_HBHENoiseIsoFilter"};
    <Bool_t> Flag_CSCTightHaloFilter = {fReader, "Flag_CSCTightHaloFilter"};
    <Bool_t> Flag_CSCTightHaloTrkMuUnvetoFilter = {fReader, "Flag_CSCTightHaloTrkMuUnvetoFilter"};
    <Bool_t> Flag_CSCTightHalo2015Filter = {fReader, "Flag_CSCTightHalo2015Filter"};
    <Bool_t> Flag_globalTightHalo2016Filter = {fReader, "Flag_globalTightHalo2016Filter"};
    <Bool_t> Flag_globalSuperTightHalo2016Filter = {fReader, "Flag_globalSuperTightHalo2016Filter"};
    <Bool_t> Flag_HcalStripHaloFilter = {fReader, "Flag_HcalStripHaloFilter"};
    <Bool_t> Flag_hcalLaserEventFilter = {fReader, "Flag_hcalLaserEventFilter"};
    <Bool_t> Flag_EcalDeadCellTriggerPrimitiveFilter = {fReader, "Flag_EcalDeadCellTriggerPrimitiveFilter"};
    <Bool_t> Flag_EcalDeadCellBoundaryEnergyFilter = {fReader, "Flag_EcalDeadCellBoundaryEnergyFilter"};
    <Bool_t> Flag_ecalBadCalibFilter = {fReader, "Flag_ecalBadCalibFilter"};
    <Bool_t> Flag_goodVertices = {fReader, "Flag_goodVertices"};
    <Bool_t> Flag_eeBadScFilter = {fReader, "Flag_eeBadScFilter"};
    <Bool_t> Flag_ecalLaserCorrFilter = {fReader, "Flag_ecalLaserCorrFilter"};
    <Bool_t> Flag_trkPOGFilters = {fReader, "Flag_trkPOGFilters"};
    <Bool_t> Flag_chargedHadronTrackResolutionFilter = {fReader, "Flag_chargedHadronTrackResolutionFilter"};
    <Bool_t> Flag_muonBadTrackFilter = {fReader, "Flag_muonBadTrackFilter"};
    <Bool_t> Flag_BadChargedCandidateFilter = {fReader, "Flag_BadChargedCandidateFilter"};
    <Bool_t> Flag_BadPFMuonFilter = {fReader, "Flag_BadPFMuonFilter"};
    <Bool_t> Flag_BadPFMuonDzFilter = {fReader, "Flag_BadPFMuonDzFilter"};
    <Bool_t> Flag_hfNoisyHitsFilter = {fReader, "Flag_hfNoisyHitsFilter"};
    <Bool_t> Flag_BadChargedCandidateSummer16Filter = {fReader, "Flag_BadChargedCandidateSummer16Filter"};
    <Bool_t> Flag_BadPFMuonSummer16Filter = {fReader, "Flag_BadPFMuonSummer16Filter"};
    <Bool_t> Flag_trkPOG_manystripclus53X = {fReader, "Flag_trkPOG_manystripclus53X"};
    <Bool_t> Flag_trkPOG_toomanystripclus53X = {fReader, "Flag_trkPOG_toomanystripclus53X"};
    <Bool_t> Flag_trkPOG_logErrorTooManyClusters = {fReader, "Flag_trkPOG_logErrorTooManyClusters"};
    <Bool_t> Flag_METFilters = {fReader, "Flag_METFilters"};

    // I assume these trigger are all present in data and mc
    <Bool_t> HLT_PFJet500 = {fReader, "HLT_PFJet500"};
    <Bool_t> HLT_PFJet450 = {fReader, "HLT_PFJet450"};
    // TRIGGERS FOR 2016
    <Bool_t> HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = {fReader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT450_SixJet40_BTagCSV_p056 = {fReader, "Flag_goodVertices"};
    <Bool_t> HLT_IsoMu24 = {fReader, "Flag_goodVertices"};
    <Bool_t> HLT_IsoMu27 = {fReader, "Flag_goodVertices"}; // read fake branches in header

    // TRIGGERS FOR 2018 MC and data B, C, D
    <Bool_t> HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 = {fReader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 = {fReader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT400_SixPFJet32 = {fReader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT450_SixPFJet36 = {fReader, "Flag_goodVertices"};
    // TRIGGERS FOR 2018 data A
    <Bool_t> HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = {fReader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = {fReader, "Flag_goodVertices"};
    // 2018 for only some small slices of 2018 A (CSV b tag instead of DeepCSV btag)
    <Bool_t> HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = {fReader, "Flag_goodVertices"};

    <Bool_t> HLT_PFHT1050 = {fReader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 = {fReader, "Flag_goodVertices"};

    // HLT 2017
    <Bool_t> HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 = {fReader, "Flag_goodVertices"};
    // data
    <Bool_t> HLT_PFHT430_SixJet40_BTagCSV_p080 = {fReader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT380_SixJet32_DoubleBTagCSV_p075 = {fReader, "Flag_goodVertices"};
}

#endif
