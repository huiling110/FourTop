#ifndef EVENTREADER_NANO_H
#define EVENTREADER_NANO_H

#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>

// #include <vector>
class eventForNano
{
public:
    // eventForNano(TTreeReader reader) : nElectron{reader, "nElectron"}
    // eventForNano(TTreeReader *reader)
    // eventForNano(TTreeReader reader) : m_reader{reader}
    eventForNano(TTreeReader &reader) : // Muon_pt(reader, "Muon_pt"),
                                        //                                     Muon_eta(reader, "Muon_eta"),
                                        //                                     Muon_dz(reader, "Muon_dz"),
                                        //                                     Muon_dxy(reader, "Muon_dxy"),
                                        //                                     Muon_looseId(reader, "Muon_looseId"),
                                        //                                     Muon_miniIsoId(reader, "Muon_miniIsoId"),
                                        //                                     Muon_mediumId(reader, "Muon_mediumId"),
                                        //                                     Muon_ip3d(reader, "Muon_ip3d"),
                                        //                                     Muon_tightCharge(reader, "Muon_tightCharge"),
                                        run(reader, "run"),
                                        luminosityBlock(reader, "luminosityBlock"),
                                        PV_npvsGood(reader, "PV_npvsGood"),
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
                                        nElectron(reader, "nElectron"),
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
                                        Electron_mvaFall17V2noIso(reader, "Electron_mvaFall17V2noIso"),
                                        Electron_phi(reader, "Electron_phi"),
                                        Electron_mass(reader, "Electron_mass"),
                                        // muon
                                        Muon_pt(reader, "Muon_pt"),
                                        Muon_eta(reader, "Muon_eta"),
                                        Muon_looseId(reader, "Muon_looseId"),
                                        Muon_dxy(reader, "Muon_dxy"),
                                        Muon_dz(reader, "Muon_dz"),
                                        Muon_ip3d(reader, "Muon_ip3d"),
                                        Muon_miniPFRelIso_all(reader, "Muon_miniPFRelIso_all"),
                                        Muon_mediumId(reader, "Muon_mediumId"),
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
                                        // tau
                                        Tau_pt(reader, "Tau_pt"),
                                        Tau_mass(reader, "Tau_mass"),
                                        Tau_eta(reader, "Tau_eta"),
                                        Tau_phi(reader, "Tau_phi"),
                                        Tau_dz(reader, "Tau_dz"),
                                        Tau_idDeepTau2017v2p1VSjet(reader, "Tau_idDeepTau2017v2p1VSjet"),
                                        Tau_idDeepTau2017v2p1VSe(reader, "Tau_idDeepTau2017v2p1VSe"),
                                        Tau_idDeepTau2017v2p1VSmu(reader, "Tau_idDeepTau2017v2p1VSmu"),
                                        Tau_decayMode(reader, "Tau_decayMode"),
                                        Tau_genPartFlav(reader, "Tau_genPartFlav"),
                                        Tau_jetIdx(reader, "Tau_jetIdx"),
                                        Tau_charge(reader, "Tau_charge"),
                                        Tau_neutralIso(reader, "Tau_neutralIso"),
                                        // jet
                                        Jet_btagDeepFlavB(reader, "Jet_btagDeepFlavB"),
     Jet_pt(reader, "Jet_pt"),
     Jet_mass(reader, "Jet_mass"),
     Jet_eta(reader, "Jet_eta"),
     Jet_phi(reader, "Jet_phi"),
     Jet_jetId(reader, "Jet_jetId"),
     Jet_btagDeepB(reader, "Jet_btagDeepB"),
     Jet_hadronFlavour(reader, "Jet_hadronFlavour"),
     fixedGridRhoFastjetAll(reader, "fixedGridRhoFastjetAll")
    {
        // dealing with case: HLT branch not existing in this nanofile;
        // assing the reader branch 0 if the branch not existing
        // it seems to reader can not run at all if assosiated with not existing branch
        readPointer(HLT_PFHT450_SixJet40_BTagCSV_p056, reader, "HLT_PFHT450_SixJet40_BTagCSV_p056");
        readPointer(HLT_PFHT400_SixJet30_DoubleBTagCSV_p056, reader, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056");
        readPointer(HLT_PFJet450, reader, "HLT_PFJet450");

        readPointer(HLT_PFJet500, reader, "HLT_PFJet500");
        readPointer(HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94, reader, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94");
        readPointer(HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59, reader, "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59");
        readPointer(HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2, reader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2");
        readPointer(HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5, reader, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5");
        readPointer(HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5, reader, "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5");
        // 2017
        readPointer(HLT_PFHT430_SixJet40_BTagCSV_p080, reader, "HLT_PFHT430_SixJet40_BTagCSV_p080");
        readPointer(HLT_PFHT380_SixJet32_DoubleBTagCSV_p075, reader, "HLT_PFHT380_SixJet32_DoubleBTagCSV_p075");
        readPointer(HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2, reader, "HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2");
        //gen
        readPointer(GenJet_eta, reader, "GenJet_eta");
        readPointer(GenJet_phi, reader, "GenJet_phi");
        readPointer(GenJet_pt, reader, "GenJet_pt");
    };

    // eventForNano(TTreeReader &reader)
    // {
    //     nElectron = new TTreeReaderValue<UInt_t>(reader, "nElectron");
    //     //!!! the pointer initialization is okay but too lengthy to access

    // }

    ~eventForNano()
    {
        // delete m_reader;
        delete HLT_PFHT450_SixJet40_BTagCSV_p056;
    };

    void readPointer(TTreeReaderValue<Bool_t> *&branchPointer, TTreeReader &reader, TString branchName)
    {
        // if (reader.GetTree()->FindBranch("HLT_PFHT450_SixJet40_BTagCSV_p056"))
        if (reader.GetTree()->FindBranch(branchName))
        {
            // HLT_PFHT450_SixJet40_BTagCSV_p056 = new TTreeReaderValue<Bool_t>(reader, "HLT_PFHT450_SixJet40_BTagCSV_p056");
            branchPointer = new TTreeReaderValue<Bool_t>(reader, branchName);
        }
        else
        {
            std::cout << "WARNINIG!!! " << branchName << " not exsit in input nano file\n";
        };
    }
    void readPointer(TTreeReaderValue<Bool_t> *&branchPointer, TTreeReader &reader, TString branchName)
    {
        if (reader.GetTree()->FindBranch(branchName))
        {
            branchPointer = new TTreeReaderValue<Bool_t>(reader, branchName);
        }
        else
        {
            std::cout << "WARNINIG!!! " << branchName << " not exsit in input nano file\n";
        };
    }
    // TTreeReader m_reader;
    //???how to solve the challange that some branches only exist in some files?
    // TTreeReaderValue<UInt_t> nElectron = {m_reader, "nElectron"}; // I guess if m_reader is not properly initialized, this line can not work

    // TTreeReaderArray<Float_t> Muon_pt;
    // TTreeReaderArray<Float_t> Muon_eta;
    // TTreeReaderArray<Float_t> Muon_dz;
    // TTreeReaderArray<Float_t> Muon_dxy;
    // TTreeReaderArray<Bool_t> Muon_looseId;
    // TTreeReaderArray<UChar_t> Muon_miniIsoId;
    // TTreeReaderArray<Bool_t> Muon_mediumId;
    // TTreeReaderArray<Float_t> Muon_ip3d;
    // TTreeReaderArray<Int_t> Muon_tightCharge;

    TTreeReaderValue<UInt_t> run;
    TTreeReaderValue<UInt_t> luminosityBlock;
    TTreeReaderValue<Int_t> PV_npvsGood;

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
    TTreeReaderValue<Bool_t> *HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = nullptr;
    // 2018 for only some small slices of 2018 A (CSV b tag instead of DeepCSV btag)
    TTreeReaderValue<Bool_t> *HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = nullptr;
    // TTreeReaderValue<Bool_t> *HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 = nullptr;
    // 2017
    TTreeReaderValue<Bool_t> *HLT_PFHT430_SixJet40_BTagCSV_p080 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT380_SixJet32_DoubleBTagCSV_p075 = nullptr; // run<299329
    // TTreeReaderValue<Bool_t> *HLT_PFJet500 = nullptr;
    // TTreeReaderValue<Bool_t> *HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = nullptr;
    TTreeReaderValue<Bool_t> *HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 = nullptr; // run<=306460 2017 end
    // TTreeReaderValue<Bool_t> * = nullptr;
    TTreeReaderArray<Float_t> *GenJet_eta = nullptr;
    TTreeReaderArray<Float_t> *GenJet_phi = nullptr;
    TTreeReaderArray<Float_t> *GenJet_pt = nullptr;

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
    TTreeReaderValue<UInt_t> nElectron;
    TTreeReaderArray<Float_t> Electron_pt;
    TTreeReaderArray<Float_t> Electron_eta;
    TTreeReaderArray<Int_t> Electron_cutBased;
    TTreeReaderArray<Float_t> Electron_dxy;
    TTreeReaderArray<Float_t> Electron_dz;
    TTreeReaderArray<Float_t> Electron_ip3d;
    TTreeReaderArray<Float_t> Electron_miniPFRelIso_all;
    TTreeReaderArray<UChar_t> Electron_lostHits;
    TTreeReaderArray<Bool_t> Electron_convVeto;
    TTreeReaderArray<Int_t> Electron_tightCharge;
    TTreeReaderArray<Float_t> Electron_jetRelIso;
    TTreeReaderArray<Int_t> Electron_jetIdx;
    TTreeReaderArray<UChar_t> Electron_jetNDauCharged;
    TTreeReaderArray<Float_t> Electron_miniPFRelIso_chg;
    TTreeReaderArray<Float_t> Electron_jetPtRelv2;
    TTreeReaderArray<Float_t> Electron_pfRelIso03_all;
    TTreeReaderArray<Float_t> Electron_sip3d;
    TTreeReaderArray<Float_t> Electron_mvaFall17V2noIso;
    TTreeReaderArray<Float_t> Electron_phi;
    TTreeReaderArray<Float_t> Electron_mass;
    // muon
    TTreeReaderArray<Float_t> Muon_pt;
    TTreeReaderArray<Float_t> Muon_eta;
    TTreeReaderArray<Bool_t> Muon_looseId;
    TTreeReaderArray<Float_t> Muon_dxy;
    TTreeReaderArray<Float_t> Muon_dz;
    TTreeReaderArray<Float_t> Muon_ip3d;
    TTreeReaderArray<Float_t> Muon_miniPFRelIso_all;
    TTreeReaderArray<Bool_t> Muon_mediumId;
    TTreeReaderArray<Float_t> Muon_jetRelIso;
    TTreeReaderArray<Int_t> Muon_jetIdx;
    TTreeReaderArray<UChar_t> Muon_jetNDauCharged;
    TTreeReaderArray<Float_t> Muon_miniPFRelIso_chg;
    TTreeReaderArray<Float_t> Muon_jetPtRelv2;
    TTreeReaderArray<Float_t> Muon_pfRelIso03_all;
    TTreeReaderArray<Float_t> Muon_segmentComp;
    TTreeReaderArray<Float_t> Muon_sip3d;
    TTreeReaderArray<Float_t> Muon_mass;
    TTreeReaderArray<Float_t> Muon_phi;
    // tau
    TTreeReaderArray<Float_t> Tau_pt;
    TTreeReaderArray<Float_t> Tau_mass;
    TTreeReaderArray<Float_t> Tau_eta;
    TTreeReaderArray<Float_t> Tau_phi;
    TTreeReaderArray<Float_t> Tau_dz;
    TTreeReaderArray<UChar_t> Tau_idDeepTau2017v2p1VSjet;
    TTreeReaderArray<UChar_t> Tau_idDeepTau2017v2p1VSe;
    TTreeReaderArray<UChar_t> Tau_idDeepTau2017v2p1VSmu;
    TTreeReaderArray<Int_t> Tau_decayMode;
    TTreeReaderArray<UChar_t> Tau_genPartFlav;
    TTreeReaderArray<Int_t> Tau_jetIdx;
    TTreeReaderArray<Int_t> Tau_charge;
    TTreeReaderArray<Float_t> Tau_neutralIso;

    TTreeReaderArray<Float_t> Jet_btagDeepFlavB;
    TTreeReaderArray<Float_t> Jet_pt;
    TTreeReaderArray<Float_t> Jet_mass;
    TTreeReaderArray<Float_t> Jet_eta;
    TTreeReaderArray<Float_t> Jet_phi;
    TTreeReaderArray<Float_t> Jet_jetId;
    TTreeReaderArray<Float_t> Jet_btagDeepB;
    TTreeReaderArray<Float_t> Jet_hadronFlavour;
    // TTreeReaderArray<Float_t> Jet_;
    TTreeReaderValue<Float_t> fixedGridRhoFastjetAll;
};

#endif