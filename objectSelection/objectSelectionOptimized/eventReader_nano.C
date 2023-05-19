#ifndef EVENTREADER_NANO_H
#define EVENTREADER_NANO_H

#include <vector>
// #include "TTreeReader.h"
// #include "TTreeReaderArray.h"
// class branch
// {
// public:
//     branch(TTree *tree, TString branchName)
//     {
//         tree->SetBranchAddress(branchName, m_value);
//     }

// }1
class eventForNano
{
public:
    // eventForNano(TTreeReader& reader) : m_reader{reader},
    // nElectron(m_reader, "nElectron")
    // eventForNano(TTreeReader *reader)
    // eventForNano(TTreeReader *reader)
    eventForNano(TTree *tree) : m_tree{tree}
    {
        // m_tree->SetBranchStatus("*", 0);
        readBranch("nElectron", nElectron);
        // readBranch("Electron_dxy", Electron_dxy);
        // m_tree->SetBranchAddress("Electron_dxy", &Electron_dxy);
        m_tree->SetBranchAddress("Electron_dxy", &Electron_dxy);
        // tree->SetBranchStatus("nElectron", 1);
        // tree->SetBranchAddress("nElectron", &nElectron);
        // m_reader = reader;
        // m_reader = new TTreeReader(tree);
        // nElectron = TTreeReaderValue<UInt_t>{reader, "nElectron"}; // I guess if m_reader is not properly initialized, this line can not work
        // nElectron = {reader, "nElectron"}; // I guess if m_reader is not properly initialized, this line can not work

        // Electron_dxy = (m_reader, "Electron_dxy");
    }
    ~eventForNano(){
        // delete m_reader;
    };
    template <typename T>
    void readBranch(TString branch, T &address)
    {
        m_tree->SetBranchStatus(branch, 1);
        m_tree->SetBranchAddress(branch, &address);
    };

    // public:
    UInt_t nElectron;
    std::vector<Float_t> Electron_dxy; //???not sure why can not read with  vector
    // std::array<Float_t> Electrion_dxy;
    // TTreeReader m_reader;
    //???how to solve the challange that some branches only exist in some files?
    // TTreeReaderValue<UInt_t> nElectron; // I guess if m_reader is not properly initialized, this line can not work
    //???can TTreeReaderValue<> be decalred but not initialized?
    // TTreeReaderArray<Float_t> Electron_dxy;
    /*
    std::vector<Float_t> Electron_dxyErr = {m_reader, "Electron_dxyErr"};
    std::vector<Float_t> Electron_dz = {m_reader, "Electron_dz"};
    std::vector<Float_t> Electron_eta = {m_reader, "Electron_eta"};
    std::vector<Float_t> Electron_ip3d = {m_reader, "Electron_ip3d"};
    std::vector<Float_t> Electron_jetPtRelv2 = {m_reader, "Electron_jetPtRelv2"};
    std::vector<Float_t> Electron_jetRelIso = {m_reader, "Electron_jetRelIso"};
    std::vector<Float_t> Electron_mass = {m_reader, "Electron_mass"};
    std::vector<Float_t> Electron_miniPFRelIso_all = {m_reader, "Electron_miniPFRelIso_all"};
    std::vector<Float_t> Electron_miniPFRelIso_chg = {m_reader, "Electron_miniPFRelIso_chg"};
    std::vector<Float_t> Electron_mvaFall17V2Iso = {m_reader, "Electron_mvaFall17V2Iso"};
    std::vector<Float_t> Electron_mvaFall17V2noIso = {m_reader, "Electron_mvaFall17V2noIso"};
    std::vector<Float_t> Electron_pfRelIso03_all = {m_reader, "Electron_pfRelIso03_all"};
    std::vector<Float_t> Electron_phi = {m_reader, "Electron_phi"};
    std::vector<Float_t> Electron_pt = {m_reader, "Electron_pt"};
    std::vector<Float_t> Electron_sip3d = {m_reader, "Electron_sip3d"};
    std::vector<Int_t> Electron_charge = {m_reader, "Electron_charge"};
    std::vector<Int_t> Electron_cutBased = {m_reader, "Electron_cutBased"};
    std::vector<Int_t> Electron_jetIdx = {m_reader, "Electron_jetIdx"};
    std::vector<Int_t> Electron_tightCharge = {m_reader, "Electron_tightCharge"};
    std::vector<Bool_t> Electron_convVeto = {m_reader, "Electron_convVeto"};
    std::vector<UChar_t> Electron_jetNDauCharged = {m_reader, "Electron_jetNDauCharged"};
    std::vector<UChar_t> Electron_lostHits = {m_reader, "Electron_lostHits"};
    std::vector<Bool_t> Electron_mvaFall17V2Iso_WP80 = {m_reader, "Electron_mvaFall17V2Iso_WP80"};
    std::vector<Bool_t> Electron_mvaFall17V2Iso_WP90 = {m_reader, "Electron_mvaFall17V2Iso_WP90"};
    std::vector<Bool_t> Electron_mvaFall17V2Iso_WPL = {m_reader, "Electron_mvaFall17V2Iso_WPL"};
    std::vector<Bool_t> Electron_mvaFall17V2noIso_WP80 = {m_reader, "Electron_mvaFall17V2noIso_WP80"};
    std::vector<Bool_t> Electron_mvaFall17V2noIso_WP90 = {m_reader, "Electron_mvaFall17V2noIso_WP90"};
    std::vector<Bool_t> Electron_mvaFall17V2noIso_WPL = {m_reader, "Electron_mvaFall17V2noIso_WPL"};
    std::vector<Float_t> GenJet_eta = {m_reader, "Electron_dz"}; //!!!need to overwrite for MC!!!

    std::vector<Float_t> GenJet_phi = {m_reader, "Electron_dz"};
    std::vector<Float_t> GenJet_pt = {m_reader, "Electron_dz"};
    <UInt_t> nGenPart = {m_reader, "nElectron"};
    std::vector<Float_t> GenPart_eta = {m_reader, "Electron_dz"};
    std::vector<Float_t> GenPart_mass = {m_reader, "Electron_dz"};
    std::vector<Float_t> GenPart_phi = {m_reader, "Electron_dz"};
    std::vector<Float_t> GenPart_pt = {m_reader, "Electron_dz"};
    std::vector<Int_t> GenPart_genPartIdxMother = {m_reader, "Electron_charge"};
    std::vector<Int_t> GenPart_pdgId = {m_reader, "Electron_charge"};

    <Float_t> Generator_weight = {m_reader, "L1PreFiringWeight_Nom"};
    <Float_t> genWeight = {m_reader, "L1PreFiringWeight_Nom"};
    std::vector<Float_t> IsoTrack_eta = {m_reader, "IsoTrack_eta"};
    std::vector<Float_t> IsoTrack_phi = {m_reader, "IsoTrack_phi"};
    std::vector<Float_t> IsoTrack_pt = {m_reader, "IsoTrack_pt"};
    <UInt_t> nJet = {m_reader, "nJet"};
    std::vector<Float_t> Jet_btagCSVV2 = {m_reader, "Jet_btagCSVV2"};
    std::vector<Float_t> Jet_btagDeepB = {m_reader, "Jet_btagDeepB"};
    std::vector<Float_t> Jet_btagDeepCvB = {m_reader, "Jet_btagDeepCvB"};
    std::vector<Float_t> Jet_btagDeepCvL = {m_reader, "Jet_btagDeepCvL"};
    std::vector<Float_t> Jet_btagDeepFlavB = {m_reader, "Jet_btagDeepFlavB"};
    std::vector<Float_t> Jet_btagDeepFlavCvB = {m_reader, "Jet_btagDeepFlavCvB"};
    std::vector<Float_t> Jet_btagDeepFlavCvL = {m_reader, "Jet_btagDeepFlavCvL"};
    std::vector<Float_t> Jet_btagDeepFlavQG = {m_reader, "Jet_btagDeepFlavQG"};
    std::vector<Float_t> Jet_eta = {m_reader, "Jet_eta"};
    std::vector<Float_t> Jet_mass = {m_reader, "Jet_mass"};
    std::vector<Float_t> Jet_phi = {m_reader, "Jet_phi"};
    std::vector<Float_t> Jet_pt = {m_reader, "Jet_pt"};
    std::vector<Float_t> Jet_rawFactor = {m_reader, "Jet_rawFactor"};
    std::vector<Int_t> Jet_jetId = {m_reader, "Jet_jetId"};
    <Float_t> L1PreFiringWeight_Dn = {m_reader, "L1PreFiringWeight_Dn"};
    <Float_t> L1PreFiringWeight_Nom = {m_reader, "L1PreFiringWeight_Nom"};
    <Float_t> L1PreFiringWeight_Up = {m_reader, "L1PreFiringWeight_Up"};
    <Float_t> MET_phi = {m_reader, "MET_phi"};
    <Float_t> MET_pt = {m_reader, "MET_pt"};
    <UInt_t> nMuon = {m_reader, "nMuon"};
    std::vector<Float_t> Muon_dxy = {m_reader, "Muon_dxy"};
    std::vector<Float_t> Muon_dz = {m_reader, "Muon_dz"};
    std::vector<Float_t> Muon_eta = {m_reader, "Muon_eta"};
    std::vector<Float_t> Muon_ip3d = {m_reader, "Muon_ip3d"};
    std::vector<Float_t> Muon_jetPtRelv2 = {m_reader, "Muon_jetPtRelv2"}; // Relative momentum of the lepton with respect to the closest jet after subtracting the lepton
    std::vector<Float_t> Muon_jetRelIso = {m_reader, "Muon_jetRelIso"};
    std::vector<Float_t> Muon_mass = {m_reader, "Muon_mass"};
    std::vector<Float_t> Muon_miniPFRelIso_all = {m_reader, "Muon_miniPFRelIso_all"};
    std::vector<Float_t> Muon_miniPFRelIso_chg = {m_reader, "Muon_miniPFRelIso_chg"};
    std::vector<Float_t> Muon_pfRelIso03_all = {m_reader, "Muon_pfRelIso03_all"};
    std::vector<Float_t> Muon_pfRelIso04_all = {m_reader, "Muon_pfRelIso04_all"};
    std::vector<Float_t> Muon_phi = {m_reader, "Muon_phi"};
    std::vector<Float_t> Muon_pt = {m_reader, "Muon_pt"};
    std::vector<Float_t> Muon_segmentComp = {m_reader, "Muon_segmentComp"};
    std::vector<Float_t> Muon_sip3d = {m_reader, "Muon_sip3d"};
    std::vector<Int_t> Muon_charge = {m_reader, "Muon_charge"};
    std::vector<Int_t> Muon_jetIdx = {m_reader, "Muon_jetIdx"};
    std::vector<Int_t> Muon_tightCharge = {m_reader, "Muon_tightCharge"};
    std::vector<UChar_t> Muon_jetNDauCharged = {m_reader, "Muon_jetNDauCharged"};
    std::vector<Bool_t> Muon_looseId = {m_reader, "Muon_looseId"};
    std::vector<Bool_t> Muon_mediumId = {m_reader, "Muon_mediumId"};
    std::vector<UChar_t> Muon_miniIsoId = {m_reader, "Muon_miniIsoId"};
    <Float_t> fixedGridRhoFastjetAll = {m_reader, "fixedGridRhoFastjetAll"};
    <UInt_t> nTau = {m_reader, "nTau"};
    std::vector<Float_t> Tau_dxy = {m_reader, "Tau_dxy"};
    std::vector<Float_t> Tau_dz = {m_reader, "Tau_dz"};
    std::vector<Float_t> Tau_eta = {m_reader, "Tau_eta"};
    std::vector<Float_t> Tau_mass = {m_reader, "Tau_mass"};
    std::vector<Float_t> Tau_neutralIso = {m_reader, "Tau_neutralIso"};
    std::vector<Float_t> Tau_phi = {m_reader, "Tau_phi"};
    std::vector<Float_t> Tau_pt = {m_reader, "Tau_pt"};
    std::vector<Int_t> Tau_charge = {m_reader, "Tau_charge"};
    std::vector<Int_t> Tau_decayMode = {m_reader, "Tau_decayMode"};
    std::vector<Int_t> Tau_jetIdx = {m_reader, "Tau_jetIdx"};
    std::vector<Bool_t> Tau_idDecayModeOldDMs = {m_reader, "Tau_idDecayModeOldDMs"};
    std::vector<UChar_t> Tau_idDeepTau2017v2p1VSe = {m_reader, "Tau_idDeepTau2017v2p1VSe"};
    std::vector<UChar_t> Tau_idDeepTau2017v2p1VSjet = {m_reader, "Tau_idDeepTau2017v2p1VSjet"};
    std::vector<UChar_t> Tau_idDeepTau2017v2p1VSmu = {m_reader, "Tau_idDeepTau2017v2p1VSmu"};
    <Int_t> genTtbarId = {m_reader, "PV_npvs"};
    <Int_t> PV_npvs = {m_reader, "PV_npvs"};
    <Int_t> PV_npvsGood = {m_reader, "PV_npvsGood"};
    std::vector<Int_t> Jet_hadronFlavour = {m_reader, "Electron_charge"};
    std::vector<UChar_t> Tau_genPartFlav = {m_reader, "Electron_jetNDauCharged"};
    <Bool_t> Flag_HBHENoiseFilter = {m_reader, "Flag_HBHENoiseFilter"};
    <Bool_t> Flag_HBHENoiseIsoFilter = {m_reader, "Flag_HBHENoiseIsoFilter"};
    <Bool_t> Flag_CSCTightHaloFilter = {m_reader, "Flag_CSCTightHaloFilter"};
    <Bool_t> Flag_CSCTightHaloTrkMuUnvetoFilter = {m_reader, "Flag_CSCTightHaloTrkMuUnvetoFilter"};
    <Bool_t> Flag_CSCTightHalo2015Filter = {m_reader, "Flag_CSCTightHalo2015Filter"};
    <Bool_t> Flag_globalTightHalo2016Filter = {m_reader, "Flag_globalTightHalo2016Filter"};
    <Bool_t> Flag_globalSuperTightHalo2016Filter = {m_reader, "Flag_globalSuperTightHalo2016Filter"};
    <Bool_t> Flag_HcalStripHaloFilter = {m_reader, "Flag_HcalStripHaloFilter"};
    <Bool_t> Flag_hcalLaserEventFilter = {m_reader, "Flag_hcalLaserEventFilter"};
    <Bool_t> Flag_EcalDeadCellTriggerPrimitiveFilter = {m_reader, "Flag_EcalDeadCellTriggerPrimitiveFilter"};
    <Bool_t> Flag_EcalDeadCellBoundaryEnergyFilter = {m_reader, "Flag_EcalDeadCellBoundaryEnergyFilter"};
    <Bool_t> Flag_ecalBadCalibFilter = {m_reader, "Flag_ecalBadCalibFilter"};
    <Bool_t> Flag_goodVertices = {m_reader, "Flag_goodVertices"};
    <Bool_t> Flag_eeBadScFilter = {m_reader, "Flag_eeBadScFilter"};
    <Bool_t> Flag_ecalLaserCorrFilter = {m_reader, "Flag_ecalLaserCorrFilter"};
    <Bool_t> Flag_trkPOGFilters = {m_reader, "Flag_trkPOGFilters"};
    <Bool_t> Flag_chargedHadronTrackResolutionFilter = {m_reader, "Flag_chargedHadronTrackResolutionFilter"};
    <Bool_t> Flag_muonBadTrackFilter = {m_reader, "Flag_muonBadTrackFilter"};
    <Bool_t> Flag_BadChargedCandidateFilter = {m_reader, "Flag_BadChargedCandidateFilter"};
    <Bool_t> Flag_BadPFMuonFilter = {m_reader, "Flag_BadPFMuonFilter"};
    <Bool_t> Flag_BadPFMuonDzFilter = {m_reader, "Flag_BadPFMuonDzFilter"};
    <Bool_t> Flag_hfNoisyHitsFilter = {m_reader, "Flag_hfNoisyHitsFilter"};
    <Bool_t> Flag_BadChargedCandidateSummer16Filter = {m_reader, "Flag_BadChargedCandidateSummer16Filter"};
    <Bool_t> Flag_BadPFMuonSummer16Filter = {m_reader, "Flag_BadPFMuonSummer16Filter"};
    <Bool_t> Flag_trkPOG_manystripclus53X = {m_reader, "Flag_trkPOG_manystripclus53X"};
    <Bool_t> Flag_trkPOG_toomanystripclus53X = {m_reader, "Flag_trkPOG_toomanystripclus53X"};
    <Bool_t> Flag_trkPOG_logErrorTooManyClusters = {m_reader, "Flag_trkPOG_logErrorTooManyClusters"};
    <Bool_t> Flag_METFilters = {m_reader, "Flag_METFilters"};

    // I assume these trigger are all present in data and mc
    <Bool_t> HLT_PFJet500 = {m_reader, "HLT_PFJet500"};
    <Bool_t> HLT_PFJet450 = {m_reader, "HLT_PFJet450"};
    // TRIGGERS FOR 2016
    <Bool_t> HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = {m_reader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT450_SixJet40_BTagCSV_p056 = {m_reader, "Flag_goodVertices"};
    <Bool_t> HLT_IsoMu24 = {m_reader, "Flag_goodVertices"};
    <Bool_t> HLT_IsoMu27 = {m_reader, "Flag_goodVertices"}; // read fake branches in header

    // TRIGGERS FOR 2018 MC and data B, C, D
    <Bool_t> HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 = {m_reader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 = {m_reader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT400_SixPFJet32 = {m_reader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT450_SixPFJet36 = {m_reader, "Flag_goodVertices"};
    // TRIGGERS FOR 2018 data A
    <Bool_t> HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = {m_reader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = {m_reader, "Flag_goodVertices"};
    // 2018 for only some small slices of 2018 A (CSV b tag instead of DeepCSV btag)
    <Bool_t> HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = {m_reader, "Flag_goodVertices"};

    <Bool_t> HLT_PFHT1050 = {m_reader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 = {m_reader, "Flag_goodVertices"};

    // HLT 2017
    <Bool_t> HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 = {m_reader, "Flag_goodVertices"};
    // data
    <Bool_t> HLT_PFHT430_SixJet40_BTagCSV_p080 = {m_reader, "Flag_goodVertices"};
    <Bool_t> HLT_PFHT380_SixJet32_DoubleBTagCSV_p075 = {m_reader, "Flag_goodVertices"};
    */
private:
    TTree *m_tree;
};

#endif
