//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Feb  6 23:41:58 2021 by ROOT version 6.20/06
// from TTree tree/tree
// found on file: /publicfs/cms/user/huahuil/TauOfTTTT/2016v1/NewNtupleAfterEventSelection_test/v3/NoJEC/TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn.root
//////////////////////////////////////////////////////////

#ifndef makeVariblesTree_v2_h
#define makeVariblesTree_v2_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>

#include "TLorentzVector.h"



class makeVariblesTree_v2 : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Int_t> HLT_PFHT450_SixJet40_BTagCSV_p056 = {fReader, "HLT_PFHT450_SixJet40_BTagCSV_p056"};
   TTreeReaderValue<Int_t> HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = {fReader, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056"};
   TTreeReaderValue<Int_t> HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg = {fReader, "HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg"};
   TTreeReaderValue<Int_t> HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg = {fReader, "HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg"};
   TTreeReaderValue<Int_t> HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg = {fReader, "HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg"};
   TTreeReaderValue<Int_t> HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg = {fReader, "HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg"};
   TTreeReaderValue<Int_t> HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg = {fReader, "HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg"};
   TTreeReaderValue<Int_t> HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg = {fReader, "HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg"};
   TTreeReaderValue<Int_t> HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg = {fReader, "HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg"};
   TTreeReaderValue<Int_t> HLT_Ele27_eta2p1_WPTight_Gsf = {fReader, "HLT_Ele27_eta2p1_WPTight_Gsf"};
   TTreeReaderValue<Int_t> HLT_Ele27_eta2p1_WPLoose_Gsf = {fReader, "HLT_Ele27_eta2p1_WPLoose_Gsf"};
   TTreeReaderValue<Int_t> HLT_Ele27_WPTight_Gsf = {fReader, "HLT_Ele27_WPTight_Gsf"};
   TTreeReaderValue<Int_t> HLT_Ele25_eta2p1_WPTight_Gsf = {fReader, "HLT_Ele25_eta2p1_WPTight_Gsf"};
   TTreeReaderValue<Int_t> HLT_IsoMu22 = {fReader, "HLT_IsoMu22"};
   TTreeReaderValue<Int_t> HLT_IsoTkMu22 = {fReader, "HLT_IsoTkMu22"};
   TTreeReaderValue<Int_t> HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
   TTreeReaderValue<Int_t> HLT_IsoTkMu24 = {fReader, "HLT_IsoTkMu24"};
   TTreeReaderValue<Int_t> HLT_IsoMu22_eta2p1 = {fReader, "HLT_IsoMu22_eta2p1"};
   TTreeReaderValue<Int_t> HLT_IsoTkMu22_eta2p1 = {fReader, "HLT_IsoTkMu22_eta2p1"};
   TTreeReaderValue<Int_t> HLT_Mu50 = {fReader, "HLT_Mu50"};
   TTreeReaderValue<Int_t> HLT_TkMu50 = {fReader, "HLT_TkMu50"};
   TTreeReaderValue<Int_t> HLT_Ele32_WPTight_Gsf = {fReader, "HLT_Ele32_WPTight_Gsf"};
   TTreeReaderValue<Int_t> HLT_Ele35_WPTight_Gsf = {fReader, "HLT_Ele35_WPTight_Gsf"};
   TTreeReaderValue<Int_t> HLT_IsoMu27 = {fReader, "HLT_IsoMu27"};
   TTreeReaderValue<Int_t> HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20 = {fReader, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20"};
   TTreeReaderValue<Int_t> HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1 = {fReader, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1"};
   TTreeReaderValue<Int_t> HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30 = {fReader, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30"};
   TTreeReaderValue<Int_t> HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1 = {fReader, "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1"};
   TTreeReaderValue<Int_t> HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1 = {fReader, "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1"};
   TTreeReaderValue<Int_t> HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1 = {fReader, "HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1"};
   TTreeReaderValue<Int_t> HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1 = {fReader, "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1"};
   TTreeReaderValue<Int_t> HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1 = {fReader, "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1"};
   TTreeReaderValue<Int_t> HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf = {fReader, "HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf"};
   TTreeReaderValue<Int_t> HLT_DoubleEle33_CaloIdL_MW = {fReader, "HLT_DoubleEle33_CaloIdL_MW"};
   TTreeReaderValue<Int_t> HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW = {fReader, "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW"};
   TTreeReaderValue<Int_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};
   TTreeReaderValue<Int_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"};
   TTreeReaderValue<Int_t> HLT_DoubleMu33NoFiltersNoVtx = {fReader, "HLT_DoubleMu33NoFiltersNoVtx"};
   TTreeReaderValue<Int_t> HLT_DoubleMu23NoFiltersNoVtxDisplaced = {fReader, "HLT_DoubleMu23NoFiltersNoVtxDisplaced"};
   TTreeReaderValue<Int_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"};
   TTreeReaderValue<Int_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8"};
   TTreeReaderValue<Int_t> HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL = {fReader, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL"};
   TTreeReaderValue<Int_t> HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = {fReader, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ"};
   TTreeReaderValue<Int_t> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL"};
   TTreeReaderValue<Int_t> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"};
   TTreeReaderValue<Int_t> HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL"};
   TTreeReaderValue<Int_t> HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ"};
   TTreeReaderValue<Int_t> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL"};
   TTreeReaderValue<Int_t> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};
   TTreeReaderValue<Int_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL"};
   TTreeReaderValue<Int_t> HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"};
   TTreeReaderValue<Int_t> HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL = {fReader, "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL"};
   TTreeReaderValue<Int_t> HLT_Mu8_DiEle12_CaloIdL_TrackIdL = {fReader, "HLT_Mu8_DiEle12_CaloIdL_TrackIdL"};
   TTreeReaderValue<Int_t> HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ = {fReader, "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ"};
   TTreeReaderValue<Int_t> HLT_TripleMu_12_10_5 = {fReader, "HLT_TripleMu_12_10_5"};
   TTreeReaderValue<Int_t> HLT_DiMu9_Ele9_CaloIdL_TrackIdL = {fReader, "HLT_DiMu9_Ele9_CaloIdL_TrackIdL"};
   TTreeReaderValue<Int_t> genTaus_number = {fReader, "genTaus_number"};
   TTreeReaderValue<Int_t> genEles_number = {fReader, "genEles_number"};
   TTreeReaderArray<double> genEle_pt = {fReader, "genEle_pt"};
   TTreeReaderArray<double> genEle_eta = {fReader, "genEle_eta"};
   TTreeReaderArray<double> genEle_phi = {fReader, "genEle_phi"};
   TTreeReaderArray<double> genEle_E = {fReader, "genEle_E"};
   TTreeReaderValue<Int_t> genMuons_number = {fReader, "genMuons_number"};
   TTreeReaderArray<double> genMuon_pt = {fReader, "genMuon_pt"};
   TTreeReaderArray<double> genMuon_eta = {fReader, "genMuon_eta"};
   TTreeReaderArray<double> genMuon_phi = {fReader, "genMuon_phi"};
   TTreeReaderArray<double> genMuon_E = {fReader, "genMuon_E"};
   TTreeReaderArray<TLorentzVector> SelectedElectronsL = {fReader, "SelectedElectronsL"};
   TTreeReaderArray<int> SelectedElectronsLIndex = {fReader, "SelectedElectronsLIndex"};
   TTreeReaderArray<TLorentzVector> SelectedElectronsM = {fReader, "SelectedElectronsM"};
   TTreeReaderArray<TLorentzVector> SelectedElectronsT = {fReader, "SelectedElectronsT"};
   TTreeReaderArray<TLorentzVector> SelectedElectronsVeto = {fReader, "SelectedElectronsVeto"};
   TTreeReaderArray<int> SelectedElectronsMIndex = {fReader, "SelectedElectronsMIndex"};
   TTreeReaderArray<int> SelectedElectronsTIndex = {fReader, "SelectedElectronsTIndex"};
   TTreeReaderArray<int> SelectedElectronsVetoIndex = {fReader, "SelectedElectronsVetoIndex"};
   TTreeReaderValue<Double_t> TopMass = {fReader, "TopMass"};
   TTreeReaderValue<Double_t> TopMassMerged = {fReader, "TopMassMerged"};
   TTreeReaderValue<Double_t> TopMassPartial = {fReader, "TopMassPartial"};
   TTreeReaderValue<Double_t> TopMassResolved = {fReader, "TopMassResolved"};
   TTreeReaderValue<Double_t> TopPt = {fReader, "TopPt"};
   TTreeReaderValue<Double_t> TopPtMerged = {fReader, "TopPtMerged"};
   TTreeReaderValue<Double_t> TopPtPartial = {fReader, "TopPtPartial"};
   TTreeReaderValue<Double_t> TopPtResolved = {fReader, "TopPtResolved"};
   TTreeReaderValue<Double_t> TopEta = {fReader, "TopEta"};
   TTreeReaderValue<Double_t> TopEtaMerged = {fReader, "TopEtaMerged"};
   TTreeReaderValue<Double_t> TopEtaPartial = {fReader, "TopEtaPartial"};
   TTreeReaderValue<Double_t> TopEtaResolved = {fReader, "TopEtaResolved"};
   TTreeReaderValue<Double_t> TopPhi = {fReader, "TopPhi"};
   TTreeReaderValue<Double_t> TopPhiMerged = {fReader, "TopPhiMerged"};
   TTreeReaderValue<Double_t> TopPhiPartial = {fReader, "TopPhiPartial"};
   TTreeReaderValue<Double_t> TopPhiResolved = {fReader, "TopPhiResolved"};
   TTreeReaderValue<Double_t> WMassResolved1 = {fReader, "WMassResolved1"};
   TTreeReaderValue<Double_t> WMassResolved2 = {fReader, "WMassResolved2"};
   TTreeReaderValue<Double_t> WMassResolved3 = {fReader, "WMassResolved3"};
   TTreeReaderValue<Double_t> BMass = {fReader, "BMass"};
   TTreeReaderValue<Double_t> BCSV = {fReader, "BCSV"};
   TTreeReaderValue<Double_t> BPt = {fReader, "BPt"};
   TTreeReaderValue<Double_t> BEta = {fReader, "BEta"};
   TTreeReaderValue<Double_t> BPhi = {fReader, "BPhi"};
   TTreeReaderValue<Double_t> ZMass = {fReader, "ZMass"};
   TTreeReaderValue<Double_t> ZPt = {fReader, "ZPt"};
   TTreeReaderValue<Double_t> ZEta = {fReader, "ZEta"};
   TTreeReaderValue<Double_t> ZPhi = {fReader, "ZPhi"};
   TTreeReaderValue<Double_t> Jet1ForwardEta = {fReader, "Jet1ForwardEta"};
   TTreeReaderValue<Double_t> Jet2ForwardEta = {fReader, "Jet2ForwardEta"};
   TTreeReaderValue<Double_t> Jet3ForwardEta = {fReader, "Jet3ForwardEta"};
   TTreeReaderValue<Double_t> Jet1ForwardPt = {fReader, "Jet1ForwardPt"};
   TTreeReaderValue<Double_t> Jet2ForwardPt = {fReader, "Jet2ForwardPt"};
   TTreeReaderValue<Double_t> Jet3ForwardPt = {fReader, "Jet3ForwardPt"};
   TTreeReaderValue<Double_t> Jet1ResolvedPt = {fReader, "Jet1ResolvedPt"};
   TTreeReaderValue<Double_t> Jet2ResolvedPt = {fReader, "Jet2ResolvedPt"};
   TTreeReaderValue<Double_t> Jet3ResolvedPt = {fReader, "Jet3ResolvedPt"};
   TTreeReaderValue<Double_t> Jet1PartialPt = {fReader, "Jet1PartialPt"};
   TTreeReaderValue<Double_t> Jet2PartialPt = {fReader, "Jet2PartialPt"};
   TTreeReaderValue<Double_t> Jet1MergedPt = {fReader, "Jet1MergedPt"};
   TTreeReaderValue<Double_t> Jet1ResolvedEta = {fReader, "Jet1ResolvedEta"};
   TTreeReaderValue<Double_t> Jet2ResolvedEta = {fReader, "Jet2ResolvedEta"};
   TTreeReaderValue<Double_t> Jet3ResolvedEta = {fReader, "Jet3ResolvedEta"};
   TTreeReaderValue<Double_t> Jet1PartialEta = {fReader, "Jet1PartialEta"};
   TTreeReaderValue<Double_t> Jet2PartialEta = {fReader, "Jet2PartialEta"};
   TTreeReaderValue<Double_t> Jet1MergedEta = {fReader, "Jet1MergedEta"};
   TTreeReaderValue<Double_t> MostForwardJetEta = {fReader, "MostForwardJetEta"};
   TTreeReaderValue<Double_t> MostForwardJetPt = {fReader, "MostForwardJetPt"};
   TTreeReaderValue<Double_t> deltaRZTop = {fReader, "deltaRZTop"};
   TTreeReaderValue<Double_t> deltaPhiZB = {fReader, "deltaPhiZB"};
   TTreeReaderValue<Double_t> deltaRZB = {fReader, "deltaRZB"};
   TTreeReaderValue<Double_t> deltaREle1Ele2 = {fReader, "deltaREle1Ele2"};
   TTreeReaderValue<Double_t> deltaRMuo1Muo2 = {fReader, "deltaRMuo1Muo2"};
   TTreeReaderValue<Double_t> Massb1b2 = {fReader, "Massb1b2"};
   TTreeReaderValue<Double_t> MinDeltaPhiBoostedJetMet = {fReader, "MinDeltaPhiBoostedJetMet"};
   TTreeReaderValue<Double_t> deltaRb1b2 = {fReader, "deltaRb1b2"};
   TTreeReaderValue<Double_t> deltaRb1Lep1 = {fReader, "deltaRb1Lep1"};
   TTreeReaderValue<Double_t> deltaRb1Lep2 = {fReader, "deltaRb1Lep2"};
   TTreeReaderValue<Double_t> deltaRb2Lep1 = {fReader, "deltaRb2Lep1"};
   TTreeReaderValue<Double_t> deltaRb2Lep2 = {fReader, "deltaRb2Lep2"};
   TTreeReaderValue<Int_t> leptonsL_number = {fReader, "leptonsL_number"};
   TTreeReaderValue<Int_t> leptonsT_number = {fReader, "leptonsT_number"};
   TTreeReaderValue<Int_t> leptonsT_number_v2 = {fReader, "leptonsT_number_v2"};
   TTreeReaderValue<Int_t> leptonsMVAF_number = {fReader, "leptonsMVAF_number"};
   TTreeReaderValue<Int_t> leptonsMVAT_number = {fReader, "leptonsMVAT_number"};
   TTreeReaderValue<Int_t> leptonsMVAL_number = {fReader, "leptonsMVAL_number"};
   TTreeReaderValue<Int_t> leptonsMVAT_transMass = {fReader, "leptonsMVAT_transMass"};
   TTreeReaderValue<Int_t> leptonsMVAF_transMass = {fReader, "leptonsMVAF_transMass"};
   TTreeReaderValue<Int_t> leptonsMVAL_transMass = {fReader, "leptonsMVAL_transMass"};
   TTreeReaderValue<Double_t> leptonsMVAT_1pt = {fReader, "leptonsMVAT_1pt"};
   TTreeReaderValue<Double_t> leptonsMVAT_1eta = {fReader, "leptonsMVAT_1eta"};
   TTreeReaderValue<Double_t> leptonsMVAT_1phi = {fReader, "leptonsMVAT_1phi"};
   TTreeReaderValue<Double_t> leptonsMVAT_2pt = {fReader, "leptonsMVAT_2pt"};
   TTreeReaderValue<Double_t> leptonsMVAT_2eta = {fReader, "leptonsMVAT_2eta"};
   TTreeReaderValue<Double_t> leptonsMVAT_2phi = {fReader, "leptonsMVAT_2phi"};
   TTreeReaderValue<Double_t> leptonsMVAT_3pt = {fReader, "leptonsMVAT_3pt"};
   TTreeReaderValue<Double_t> leptonsMVAT_3eta = {fReader, "leptonsMVAT_3eta"};
   TTreeReaderValue<Double_t> leptonsMVAT_3phi = {fReader, "leptonsMVAT_3phi"};
   TTreeReaderValue<Int_t> leptonsMVAT_2SS = {fReader, "leptonsMVAT_2SS"};
   TTreeReaderValue<Int_t> leptonsMVAT_2OS = {fReader, "leptonsMVAT_2OS"};
   TTreeReaderValue<Int_t> elesMVAL_number = {fReader, "elesMVAL_number"};
   TTreeReaderValue<Int_t> elesMVAF_number = {fReader, "elesMVAF_number"};
   TTreeReaderValue<Int_t> elesMVAT_number = {fReader, "elesMVAT_number"};
   TTreeReaderValue<Int_t> elesMVAL_number_s0 = {fReader, "elesMVAL_number_s0"};
   TTreeReaderValue<Int_t> elesMVAF_number_s0 = {fReader, "elesMVAF_number_s0"};
   TTreeReaderValue<Int_t> elesMVAT_number_s0 = {fReader, "elesMVAT_number_s0"};
   TTreeReaderValue<Int_t> elesMVAL_number_s1 = {fReader, "elesMVAL_number_s1"};
   TTreeReaderValue<Int_t> elesMVAF_number_s1 = {fReader, "elesMVAF_number_s1"};
   TTreeReaderValue<Int_t> elesMVAT_number_s1 = {fReader, "elesMVAT_number_s1"};
   TTreeReaderValue<Int_t> elesMVAL_number_s2 = {fReader, "elesMVAL_number_s2"};
   TTreeReaderValue<Int_t> elesMVAF_number_s2 = {fReader, "elesMVAF_number_s2"};
   TTreeReaderValue<Int_t> elesMVAT_number_s2 = {fReader, "elesMVAT_number_s2"};
   TTreeReaderValue<Int_t> elesMVAL_number_s3 = {fReader, "elesMVAL_number_s3"};
   TTreeReaderValue<Int_t> elesMVAF_number_s3 = {fReader, "elesMVAF_number_s3"};
   TTreeReaderValue<Int_t> elesMVAT_number_s3 = {fReader, "elesMVAT_number_s3"};
   TTreeReaderArray<double> eleMVAL_pt = {fReader, "eleMVAL_pt"};
   TTreeReaderArray<double> eleMVAL_eta = {fReader, "eleMVAL_eta"};
   TTreeReaderArray<double> eleMVAL_phi = {fReader, "eleMVAL_phi"};
   TTreeReaderArray<double> eleMVAL_E = {fReader, "eleMVAL_E"};
   TTreeReaderArray<double> eleMVAF_pt = {fReader, "eleMVAF_pt"};
   TTreeReaderArray<double> eleMVAF_eta = {fReader, "eleMVAF_eta"};
   TTreeReaderArray<double> eleMVAF_phi = {fReader, "eleMVAF_phi"};
   TTreeReaderArray<double> eleMVAF_E = {fReader, "eleMVAF_E"};
   TTreeReaderArray<double> eleMVAT_pt = {fReader, "eleMVAT_pt"};
   TTreeReaderArray<double> eleMVAT_eta = {fReader, "eleMVAT_eta"};
   TTreeReaderArray<double> eleMVAT_phi = {fReader, "eleMVAT_phi"};
   TTreeReaderArray<double> eleMVAT_E = {fReader, "eleMVAT_E"};
   TTreeReaderArray<double> eleMVAL_pt_s0 = {fReader, "eleMVAL_pt_s0"};
   TTreeReaderArray<double> eleMVAL_eta_s0 = {fReader, "eleMVAL_eta_s0"};
   TTreeReaderArray<double> eleMVAL_phi_s0 = {fReader, "eleMVAL_phi_s0"};
   TTreeReaderArray<double> eleMVAL_E_s0 = {fReader, "eleMVAL_E_s0"};
   TTreeReaderArray<double> eleMVAF_pt_s0 = {fReader, "eleMVAF_pt_s0"};
   TTreeReaderArray<double> eleMVAF_eta_s0 = {fReader, "eleMVAF_eta_s0"};
   TTreeReaderArray<double> eleMVAF_phi_s0 = {fReader, "eleMVAF_phi_s0"};
   TTreeReaderArray<double> eleMVAF_E_s0 = {fReader, "eleMVAF_E_s0"};
   TTreeReaderArray<double> eleMVAT_pt_s0 = {fReader, "eleMVAT_pt_s0"};
   TTreeReaderArray<double> eleMVAT_eta_s0 = {fReader, "eleMVAT_eta_s0"};
   TTreeReaderArray<double> eleMVAT_phi_s0 = {fReader, "eleMVAT_phi_s0"};
   TTreeReaderArray<double> eleMVAT_E_s0 = {fReader, "eleMVAT_E_s0"};
   TTreeReaderArray<double> eleMVAL_pt_s1 = {fReader, "eleMVAL_pt_s1"};
   TTreeReaderArray<double> eleMVAL_eta_s1 = {fReader, "eleMVAL_eta_s1"};
   TTreeReaderArray<double> eleMVAL_phi_s1 = {fReader, "eleMVAL_phi_s1"};
   TTreeReaderArray<double> eleMVAL_E_s1 = {fReader, "eleMVAL_E_s1"};
   TTreeReaderArray<double> eleMVAF_pt_s1 = {fReader, "eleMVAF_pt_s1"};
   TTreeReaderArray<double> eleMVAF_eta_s1 = {fReader, "eleMVAF_eta_s1"};
   TTreeReaderArray<double> eleMVAF_phi_s1 = {fReader, "eleMVAF_phi_s1"};
   TTreeReaderArray<double> eleMVAF_E_s1 = {fReader, "eleMVAF_E_s1"};
   TTreeReaderArray<double> eleMVAT_pt_s1 = {fReader, "eleMVAT_pt_s1"};
   TTreeReaderArray<double> eleMVAT_eta_s1 = {fReader, "eleMVAT_eta_s1"};
   TTreeReaderArray<double> eleMVAT_phi_s1 = {fReader, "eleMVAT_phi_s1"};
   TTreeReaderArray<double> eleMVAT_E_s1 = {fReader, "eleMVAT_E_s1"};
   TTreeReaderArray<double> eleMVAL_pt_s2 = {fReader, "eleMVAL_pt_s2"};
   TTreeReaderArray<double> eleMVAL_eta_s2 = {fReader, "eleMVAL_eta_s2"};
   TTreeReaderArray<double> eleMVAL_phi_s2 = {fReader, "eleMVAL_phi_s2"};
   TTreeReaderArray<double> eleMVAL_E_s2 = {fReader, "eleMVAL_E_s2"};
   TTreeReaderArray<double> eleMVAF_pt_s2 = {fReader, "eleMVAF_pt_s2"};
   TTreeReaderArray<double> eleMVAF_eta_s2 = {fReader, "eleMVAF_eta_s2"};
   TTreeReaderArray<double> eleMVAF_phi_s2 = {fReader, "eleMVAF_phi_s2"};
   TTreeReaderArray<double> eleMVAF_E_s2 = {fReader, "eleMVAF_E_s2"};
   TTreeReaderArray<double> eleMVAT_pt_s2 = {fReader, "eleMVAT_pt_s2"};
   TTreeReaderArray<double> eleMVAT_eta_s2 = {fReader, "eleMVAT_eta_s2"};
   TTreeReaderArray<double> eleMVAT_phi_s2 = {fReader, "eleMVAT_phi_s2"};
   TTreeReaderArray<double> eleMVAT_E_s2 = {fReader, "eleMVAT_E_s2"};
   TTreeReaderArray<double> eleMVAL_pt_s3 = {fReader, "eleMVAL_pt_s3"};
   TTreeReaderArray<double> eleMVAL_eta_s3 = {fReader, "eleMVAL_eta_s3"};
   TTreeReaderArray<double> eleMVAL_phi_s3 = {fReader, "eleMVAL_phi_s3"};
   TTreeReaderArray<double> eleMVAL_E_s3 = {fReader, "eleMVAL_E_s3"};
   TTreeReaderArray<double> eleMVAF_pt_s3 = {fReader, "eleMVAF_pt_s3"};
   TTreeReaderArray<double> eleMVAF_eta_s3 = {fReader, "eleMVAF_eta_s3"};
   TTreeReaderArray<double> eleMVAF_phi_s3 = {fReader, "eleMVAF_phi_s3"};
   TTreeReaderArray<double> eleMVAF_E_s3 = {fReader, "eleMVAF_E_s3"};
   TTreeReaderArray<double> eleMVAT_pt_s3 = {fReader, "eleMVAT_pt_s3"};
   TTreeReaderArray<double> eleMVAT_eta_s3 = {fReader, "eleMVAT_eta_s3"};
   TTreeReaderArray<double> eleMVAT_phi_s3 = {fReader, "eleMVAT_phi_s3"};
   TTreeReaderArray<double> eleMVAT_E_s3 = {fReader, "eleMVAT_E_s3"};
   TTreeReaderValue<Double_t> elesMVAF_1pt = {fReader, "elesMVAF_1pt"};
   TTreeReaderValue<Int_t> muonsL_number = {fReader, "muonsL_number"};
   TTreeReaderValue<Int_t> muonsF_number = {fReader, "muonsF_number"};
   TTreeReaderValue<Int_t> muonsT_number = {fReader, "muonsT_number"};
   TTreeReaderValue<Int_t> muonsL_number_s0 = {fReader, "muonsL_number_s0"};
   TTreeReaderValue<Int_t> muonsF_number_s0 = {fReader, "muonsF_number_s0"};
   TTreeReaderValue<Int_t> muonsT_number_s0 = {fReader, "muonsT_number_s0"};
   TTreeReaderValue<Int_t> muonsL_number_s1 = {fReader, "muonsL_number_s1"};
   TTreeReaderValue<Int_t> muonsF_number_s1 = {fReader, "muonsF_number_s1"};
   TTreeReaderValue<Int_t> muonsT_number_s1 = {fReader, "muonsT_number_s1"};
   TTreeReaderValue<Int_t> muonsL_number_s2 = {fReader, "muonsL_number_s2"};
   TTreeReaderValue<Int_t> muonsF_number_s2 = {fReader, "muonsF_number_s2"};
   TTreeReaderValue<Int_t> muonsT_number_s2 = {fReader, "muonsT_number_s2"};
   TTreeReaderValue<Int_t> muonsL_number_s3 = {fReader, "muonsL_number_s3"};
   TTreeReaderValue<Int_t> muonsF_number_s3 = {fReader, "muonsF_number_s3"};
   TTreeReaderValue<Int_t> muonsT_number_s3 = {fReader, "muonsT_number_s3"};
   TTreeReaderArray<double> muonL_pt = {fReader, "muonL_pt"};
   TTreeReaderArray<double> muonL_eta = {fReader, "muonL_eta"};
   TTreeReaderArray<double> muonL_phi = {fReader, "muonL_phi"};
   TTreeReaderArray<double> muonL_E = {fReader, "muonL_E"};
   TTreeReaderArray<double> muonF_pt = {fReader, "muonF_pt"};
   TTreeReaderArray<double> muonF_eta = {fReader, "muonF_eta"};
   TTreeReaderArray<double> muonF_phi = {fReader, "muonF_phi"};
   TTreeReaderArray<double> muonF_E = {fReader, "muonF_E"};
   TTreeReaderArray<double> muonT_pt = {fReader, "muonT_pt"};
   TTreeReaderArray<double> muonT_eta = {fReader, "muonT_eta"};
   TTreeReaderArray<double> muonT_phi = {fReader, "muonT_phi"};
   TTreeReaderArray<double> muonT_E = {fReader, "muonT_E"};
   TTreeReaderArray<double> muonL_pt_s0 = {fReader, "muonL_pt_s0"};
   TTreeReaderArray<double> muonL_eta_s0 = {fReader, "muonL_eta_s0"};
   TTreeReaderArray<double> muonL_phi_s0 = {fReader, "muonL_phi_s0"};
   TTreeReaderArray<double> muonL_E_s0 = {fReader, "muonL_E_s0"};
   TTreeReaderArray<double> muonF_pt_s0 = {fReader, "muonF_pt_s0"};
   TTreeReaderArray<double> muonF_eta_s0 = {fReader, "muonF_eta_s0"};
   TTreeReaderArray<double> muonF_phi_s0 = {fReader, "muonF_phi_s0"};
   TTreeReaderArray<double> muonF_E_s0 = {fReader, "muonF_E_s0"};
   TTreeReaderArray<double> muonT_pt_s0 = {fReader, "muonT_pt_s0"};
   TTreeReaderArray<double> muonT_eta_s0 = {fReader, "muonT_eta_s0"};
   TTreeReaderArray<double> muonT_phi_s0 = {fReader, "muonT_phi_s0"};
   TTreeReaderArray<double> muonT_E_s0 = {fReader, "muonT_E_s0"};
   TTreeReaderArray<double> muonL_pt_s1 = {fReader, "muonL_pt_s1"};
   TTreeReaderArray<double> muonL_eta_s1 = {fReader, "muonL_eta_s1"};
   TTreeReaderArray<double> muonL_phi_s1 = {fReader, "muonL_phi_s1"};
   TTreeReaderArray<double> muonL_E_s1 = {fReader, "muonL_E_s1"};
   TTreeReaderArray<double> muonF_pt_s1 = {fReader, "muonF_pt_s1"};
   TTreeReaderArray<double> muonF_eta_s1 = {fReader, "muonF_eta_s1"};
   TTreeReaderArray<double> muonF_phi_s1 = {fReader, "muonF_phi_s1"};
   TTreeReaderArray<double> muonF_E_s1 = {fReader, "muonF_E_s1"};
   TTreeReaderArray<double> muonT_pt_s1 = {fReader, "muonT_pt_s1"};
   TTreeReaderArray<double> muonT_eta_s1 = {fReader, "muonT_eta_s1"};
   TTreeReaderArray<double> muonT_phi_s1 = {fReader, "muonT_phi_s1"};
   TTreeReaderArray<double> muonT_E_s1 = {fReader, "muonT_E_s1"};
   TTreeReaderArray<double> muonL_pt_s2 = {fReader, "muonL_pt_s2"};
   TTreeReaderArray<double> muonL_eta_s2 = {fReader, "muonL_eta_s2"};
   TTreeReaderArray<double> muonL_phi_s2 = {fReader, "muonL_phi_s2"};
   TTreeReaderArray<double> muonL_E_s2 = {fReader, "muonL_E_s2"};
   TTreeReaderArray<double> muonF_pt_s2 = {fReader, "muonF_pt_s2"};
   TTreeReaderArray<double> muonF_eta_s2 = {fReader, "muonF_eta_s2"};
   TTreeReaderArray<double> muonF_phi_s2 = {fReader, "muonF_phi_s2"};
   TTreeReaderArray<double> muonF_E_s2 = {fReader, "muonF_E_s2"};
   TTreeReaderArray<double> muonT_pt_s2 = {fReader, "muonT_pt_s2"};
   TTreeReaderArray<double> muonT_eta_s2 = {fReader, "muonT_eta_s2"};
   TTreeReaderArray<double> muonT_phi_s2 = {fReader, "muonT_phi_s2"};
   TTreeReaderArray<double> muonT_E_s2 = {fReader, "muonT_E_s2"};
   TTreeReaderArray<double> muonL_pt_s3 = {fReader, "muonL_pt_s3"};
   TTreeReaderArray<double> muonL_eta_s3 = {fReader, "muonL_eta_s3"};
   TTreeReaderArray<double> muonL_phi_s3 = {fReader, "muonL_phi_s3"};
   TTreeReaderArray<double> muonL_E_s3 = {fReader, "muonL_E_s3"};
   TTreeReaderArray<double> muonF_pt_s3 = {fReader, "muonF_pt_s3"};
   TTreeReaderArray<double> muonF_eta_s3 = {fReader, "muonF_eta_s3"};
   TTreeReaderArray<double> muonF_phi_s3 = {fReader, "muonF_phi_s3"};
   TTreeReaderArray<double> muonF_E_s3 = {fReader, "muonF_E_s3"};
   TTreeReaderArray<double> muonT_pt_s3 = {fReader, "muonT_pt_s3"};
   TTreeReaderArray<double> muonT_eta_s3 = {fReader, "muonT_eta_s3"};
   TTreeReaderArray<double> muonT_phi_s3 = {fReader, "muonT_phi_s3"};
   TTreeReaderArray<double> muonT_E_s3 = {fReader, "muonT_E_s3"};
   TTreeReaderValue<Double_t> muonsT_1pt = {fReader, "muonsT_1pt"};
   TTreeReaderValue<Double_t> muonsT_1eta = {fReader, "muonsT_1eta"};
   TTreeReaderValue<Double_t> muonsT_1phi = {fReader, "muonsT_1phi"};
   TTreeReaderValue<Double_t> muonsT_2pt = {fReader, "muonsT_2pt"};
   TTreeReaderValue<Double_t> muonsT_2eta = {fReader, "muonsT_2eta"};
   TTreeReaderValue<Double_t> muonsT_2phi = {fReader, "muonsT_2phi"};
   TTreeReaderValue<Int_t> muonsT_3pt = {fReader, "muonsT_3pt"};
   TTreeReaderValue<Int_t> muonsT_3eta = {fReader, "muonsT_3eta"};
   TTreeReaderValue<Int_t> muonsT_3phi = {fReader, "muonsT_3phi"};
   TTreeReaderValue<Int_t> jetsL_number = {fReader, "jetsL_number"};
   TTreeReaderValue<Double_t> jetsL_HT = {fReader, "jetsL_HT"};
   TTreeReaderValue<Double_t> jetsL_MHT = {fReader, "jetsL_MHT"};
   TTreeReaderValue<Double_t> jetsL_invariantMass = {fReader, "jetsL_invariantMass"};
   TTreeReaderValue<Double_t> jetsL_transMass = {fReader, "jetsL_transMass"};
   TTreeReaderValue<Double_t> jetL_minDeltaR = {fReader, "jetL_minDeltaR"};
   TTreeReaderValue<Double_t> jetsL_centrality = {fReader, "jetsL_centrality"};
   TTreeReaderValue<Double_t> Aplanarity = {fReader, "Aplanarity"};
   TTreeReaderValue<Double_t> Sphericity = {fReader, "Sphericity"};
   TTreeReaderValue<Double_t> LeadingJetpfDeepFlavourBJetTags = {fReader, "LeadingJetpfDeepFlavourBJetTags"};
   TTreeReaderValue<Double_t> SecondJetpfDeepFlavourBJetTags = {fReader, "SecondJetpfDeepFlavourBJetTags"};
   TTreeReaderValue<Double_t> ThirdJetpfDeepFlavourBJetTags = {fReader, "ThirdJetpfDeepFlavourBJetTags"};
   TTreeReaderValue<Double_t> jetsL_bScore = {fReader, "jetsL_bScore"};
   TTreeReaderValue<Double_t> &jetsL_average_deltaR = {fReader, "jetsL_average_deltaR"};
   TTreeReaderValue<Double_t> jetsL_4largestBscoreSum = {fReader, "jetsL_4largestBscoreSum"};
   TTreeReaderValue<Double_t> jetsL_leading2invariantMass = {fReader, "jetsL_leading2invariantMass"};
   TTreeReaderValue<Double_t> jetsL_rationHT_4toRest = {fReader, "jetsL_rationHT_4toRest"};
   TTreeReaderValue<Double_t> jetsL_leptonsMVAT_minDeltaR = {fReader, "jetsL_leptonsMVAT_minDeltaR"};
   TTreeReaderValue<Double_t> jetsL_tausF_minDeltaR = {fReader, "jetsL_tausF_minDeltaR"};
   TTreeReaderValue<Double_t> jetsL_1pt = {fReader, "jetsL_1pt"};
   TTreeReaderValue<Double_t> jetsL_1eta = {fReader, "jetsL_1eta"};
   TTreeReaderValue<Double_t> jetsL_1phi = {fReader, "jetsL_1phi"};
   TTreeReaderValue<Double_t> jetsL_2pt = {fReader, "jetsL_2pt"};
   TTreeReaderValue<Double_t> jetsL_2eta = {fReader, "jetsL_2eta"};
   TTreeReaderValue<Double_t> jetsL_2phi = {fReader, "jetsL_2phi"};
   TTreeReaderValue<Double_t> jetsL_3pt = {fReader, "jetsL_3pt"};
   TTreeReaderValue<Double_t> jetsL_3eta = {fReader, "jetsL_3eta"};
   TTreeReaderValue<Double_t> jetsL_3phi = {fReader, "jetsL_3phi"};
   TTreeReaderValue<Double_t> jetsL_4pt = {fReader, "jetsL_4pt"};
   TTreeReaderValue<Double_t> jetsL_4eta = {fReader, "jetsL_4eta"};
   TTreeReaderValue<Double_t> jetsL_4phi = {fReader, "jetsL_4phi"};
   TTreeReaderValue<Double_t> jetsL_5pt = {fReader, "jetsL_5pt"};
   TTreeReaderValue<Double_t> jetsL_5eta = {fReader, "jetsL_5eta"};
   TTreeReaderValue<Double_t> jetsL_5phi = {fReader, "jetsL_5phi"};
   TTreeReaderValue<Double_t> jetsL_6pt = {fReader, "jetsL_6pt"};
   TTreeReaderValue<Double_t> jetsL_6eta = {fReader, "jetsL_6eta"};
   TTreeReaderValue<Double_t> jetsL_6phi = {fReader, "jetsL_6phi"};
   TTreeReaderValue<Double_t> jetsL_7pt = {fReader, "jetsL_7pt"};
   TTreeReaderValue<Double_t> jetsL_7eta = {fReader, "jetsL_7eta"};
   TTreeReaderValue<Double_t> jetL_7phi = {fReader, "jetL_7phi"};
   TTreeReaderValue<Double_t> jetsL_8pt = {fReader, "jetsL_8pt"};
   TTreeReaderValue<Double_t> jetsL_8eta = {fReader, "jetsL_8eta"};
   TTreeReaderValue<Double_t> jetsL_8phi = {fReader, "jetsL_8phi"};
   TTreeReaderValue<Double_t> jetsL_9pt = {fReader, "jetsL_9pt"};
   TTreeReaderValue<Double_t> jetsL_9eta = {fReader, "jetsL_9eta"};
   TTreeReaderValue<Double_t> jetsL_9phi = {fReader, "jetsL_9phi"};
   TTreeReaderValue<Double_t> jetsL_10pt = {fReader, "jetsL_10pt"};
   TTreeReaderValue<Double_t> jetsL_10eta = {fReader, "jetsL_10eta"};
   TTreeReaderValue<Double_t> jetsL_10phi = {fReader, "jetsL_10phi"};
   TTreeReaderValue<Double_t> jetsL_11pt = {fReader, "jetsL_11pt"};
   TTreeReaderValue<Double_t> jetsL_11eta = {fReader, "jetsL_11eta"};
   TTreeReaderValue<Double_t> jetsL_11phi = {fReader, "jetsL_11phi"};
   TTreeReaderValue<Double_t> jetsL_HTDividedByMet = {fReader, "jetsL_HTDividedByMet"};
   TTreeReaderValue<Double_t> MetDividedByHT = {fReader, "MetDividedByHT"};
   TTreeReaderValue<Double_t> jetsL_MHTDividedByMet = {fReader, "jetsL_MHTDividedByMet"};
   TTreeReaderValue<Int_t> bjetsL_num = {fReader, "bjetsL_num"};
   TTreeReaderValue<Int_t> bjetsM_num = {fReader, "bjetsM_num"};
   TTreeReaderValue<Int_t> bjetsT_num = {fReader, "bjetsT_num"};
   TTreeReaderValue<Double_t> bjetsL_HT = {fReader, "bjetsL_HT"};
   TTreeReaderValue<Double_t> bjetsM_HT = {fReader, "bjetsM_HT"};
   TTreeReaderValue<Double_t> bjetsT_HT = {fReader, "bjetsT_HT"};
   TTreeReaderValue<Double_t> bjetsL_MHT = {fReader, "bjetsL_MHT"};
   TTreeReaderValue<Double_t> bjetsM_MHT = {fReader, "bjetsM_MHT"};
   TTreeReaderValue<Double_t> bjetsT_MHT = {fReader, "bjetsT_MHT"};
   TTreeReaderValue<Double_t> bjetsL_invariantMass = {fReader, "bjetsL_invariantMass"};
   TTreeReaderValue<Double_t> bjetsM_invariantMass = {fReader, "bjetsM_invariantMass"};
   TTreeReaderValue<Double_t> bjetsT_invariantMass = {fReader, "bjetsT_invariantMass"};
   TTreeReaderValue<Double_t> bjetsL_transMass = {fReader, "bjetsL_transMass"};
   TTreeReaderValue<Double_t> bjetsM_transMass = {fReader, "bjetsM_transMass"};
   TTreeReaderValue<Double_t> bjetsT_transMass = {fReader, "bjetsT_transMass"};
   TTreeReaderValue<Double_t> bjetsL_minDeltaR = {fReader, "bjetsL_minDeltaR"};
   TTreeReaderValue<Double_t> bjetsM_minDeltaR = {fReader, "bjetsM_minDeltaR"};
   TTreeReaderValue<Double_t> bjetsT_minDeltaR = {fReader, "bjetsT_minDeltaR"};
   TTreeReaderValue<Double_t> bjetsL_leptonsMVAT_minDeltaR = {fReader, "bjetsL_leptonsMVAT_minDeltaR"};
   TTreeReaderValue<Double_t> bjetsM_leptonsMVAT_minDeltaR = {fReader, "bjetsM_leptonsMVAT_minDeltaR"};
   TTreeReaderValue<Double_t> bjetsT_leptonsMVAT_minDeltaR = {fReader, "bjetsT_leptonsMVAT_minDeltaR"};
   TTreeReaderValue<Double_t> bjetsL_tausF_minDeltaR = {fReader, "bjetsL_tausF_minDeltaR"};
   TTreeReaderValue<Double_t> bjetsL_1pt = {fReader, "bjetsL_1pt"};
   TTreeReaderValue<Double_t> bjetsL_1eta = {fReader, "bjetsL_1eta"};
   TTreeReaderValue<Double_t> bjetsL_1phi = {fReader, "bjetsL_1phi"};
   TTreeReaderValue<Double_t> bjetsL_2pt = {fReader, "bjetsL_2pt"};
   TTreeReaderValue<Double_t> bjetsL_2eta = {fReader, "bjetsL_2eta"};
   TTreeReaderValue<Double_t> bjetsL_2phi = {fReader, "bjetsL_2phi"};
   TTreeReaderValue<Double_t> bjetsL_3pt = {fReader, "bjetsL_3pt"};
   TTreeReaderValue<Double_t> bjetsL_3eta = {fReader, "bjetsL_3eta"};
   TTreeReaderValue<Double_t> bjetsL_3phi = {fReader, "bjetsL_3phi"};
   TTreeReaderValue<Double_t> bjetsL_4pt = {fReader, "bjetsL_4pt"};
   TTreeReaderValue<Double_t> bjetsL_4eta = {fReader, "bjetsL_4eta"};
   TTreeReaderValue<Double_t> bjetsL_4phi = {fReader, "bjetsL_4phi"};
   TTreeReaderValue<Double_t> bjetsM_1pt = {fReader, "bjetsM_1pt"};
   TTreeReaderValue<Double_t> bjetsM_1eta = {fReader, "bjetsM_1eta"};
   TTreeReaderValue<Double_t> bjetsM_1phi = {fReader, "bjetsM_1phi"};
   TTreeReaderValue<Double_t> bjetsM_2pt = {fReader, "bjetsM_2pt"};
   TTreeReaderValue<Double_t> bjetsM_2eta = {fReader, "bjetsM_2eta"};
   TTreeReaderValue<Double_t> bjetsM_2phi = {fReader, "bjetsM_2phi"};
   TTreeReaderValue<Double_t> bjetsM_3pt = {fReader, "bjetsM_3pt"};
   TTreeReaderValue<Double_t> bjetsM_3eta = {fReader, "bjetsM_3eta"};
   TTreeReaderValue<Double_t> bjetsM_3phi = {fReader, "bjetsM_3phi"};
   TTreeReaderValue<Double_t> bjetsM_4pt = {fReader, "bjetsM_4pt"};
   TTreeReaderValue<Double_t> bjetsM_4eta = {fReader, "bjetsM_4eta"};
   TTreeReaderValue<Double_t> bjetsM_4phi = {fReader, "bjetsM_4phi"};
   TTreeReaderValue<Double_t> bjetsT_1pt = {fReader, "bjetsT_1pt"};
   TTreeReaderValue<Double_t> bjetsT_1eta = {fReader, "bjetsT_1eta"};
   TTreeReaderValue<Double_t> bjetsT_1phi = {fReader, "bjetsT_1phi"};
   TTreeReaderValue<Double_t> bjetsT_2pt = {fReader, "bjetsT_2pt"};
   TTreeReaderValue<Double_t> bjetsT_2eta = {fReader, "bjetsT_2eta"};
   TTreeReaderValue<Double_t> bjetsT_2phi = {fReader, "bjetsT_2phi"};
   TTreeReaderValue<Double_t> bjetsT_3pt = {fReader, "bjetsT_3pt"};
   TTreeReaderValue<Double_t> bjetsT_3eta = {fReader, "bjetsT_3eta"};
   TTreeReaderValue<Double_t> bjetsT_3phi = {fReader, "bjetsT_3phi"};
   TTreeReaderValue<Double_t> bjetsT_4pt = {fReader, "bjetsT_4pt"};
   TTreeReaderValue<Double_t> bjetsT_4eta = {fReader, "bjetsT_4eta"};
   TTreeReaderValue<Double_t> bjetsT_4phi = {fReader, "bjetsT_4phi"};
   TTreeReaderValue<Int_t> forwardJets_num = {fReader, "forwardJets_num"};
   TTreeReaderValue<Double_t> forwardjet_1pt = {fReader, "forwardjet_1pt"};
   TTreeReaderValue<Double_t> forwardjet_1eta = {fReader, "forwardjet_1eta"};
   TTreeReaderValue<Double_t> forwardjet_1phi = {fReader, "forwardjet_1phi"};
   TTreeReaderValue<Double_t> forwardjet1_jetsL_minDeltaEta = {fReader, "forwardjet1_jetsL_minDeltaEta"};
   TTreeReaderValue<Int_t> tausL_number = {fReader, "tausL_number"};
   TTreeReaderValue<Int_t> tausF_number = {fReader, "tausF_number"};
   TTreeReaderValue<Int_t> tausT_number = {fReader, "tausT_number"};
   TTreeReaderValue<Double_t> tausL_MHT = {fReader, "tausL_MHT"};
   TTreeReaderValue<Double_t> tausF_MHT = {fReader, "tausF_MHT"};
   TTreeReaderValue<Double_t> tausT_MHT = {fReader, "tausT_MHT"};
   TTreeReaderValue<Double_t> tausL_HT = {fReader, "tausL_HT"};
   TTreeReaderValue<Double_t> tausF_HT = {fReader, "tausF_HT"};
   TTreeReaderValue<Double_t> tausT_HT = {fReader, "tausT_HT"};
   TTreeReaderValue<Double_t> tausL_invariantMass = {fReader, "tausL_invariantMass"};
   TTreeReaderValue<Double_t> tausF_invariantMass = {fReader, "tausF_invariantMass"};
   TTreeReaderValue<Double_t> tausT_invariantMass = {fReader, "tausT_invariantMass"};
   TTreeReaderValue<Double_t> tausL_minDeltaR = {fReader, "tausL_minDeltaR"};
   TTreeReaderValue<Double_t> tausF_minDeltaR = {fReader, "tausF_minDeltaR"};
   TTreeReaderValue<Double_t> tausT_minDeltaR = {fReader, "tausT_minDeltaR"};
   TTreeReaderValue<Double_t> tauL_1pt = {fReader, "tauL_1pt"};
   TTreeReaderValue<Double_t> tauL_1eta = {fReader, "tauL_1eta"};
   TTreeReaderValue<Double_t> tauL_1phi = {fReader, "tauL_1phi"};
   TTreeReaderValue<Double_t> tauL_2pt = {fReader, "tauL_2pt"};
   TTreeReaderValue<Double_t> tauL_2eta = {fReader, "tauL_2eta"};
   TTreeReaderValue<Double_t> tauL_2phi = {fReader, "tauL_2phi"};
   TTreeReaderValue<Double_t> tauL_3pt = {fReader, "tauL_3pt"};
   TTreeReaderValue<Double_t> tauL_3eta = {fReader, "tauL_3eta"};
   TTreeReaderValue<Double_t> tauL_3phi = {fReader, "tauL_3phi"};
   TTreeReaderValue<Double_t> tausF_leptonsT_transMass = {fReader, "tausF_leptonsT_transMass"};
   TTreeReaderValue<Double_t> tausL_leptonsT_transMass = {fReader, "tausL_leptonsT_transMass"};
   TTreeReaderValue<Double_t> tausT_leptonsT_transMass = {fReader, "tausT_leptonsT_transMass"};
   TTreeReaderValue<Double_t> tausF_leptonsT_invariantMass = {fReader, "tausF_leptonsT_invariantMass"};
   TTreeReaderValue<Double_t> tausL_leptonsT_invariantMass = {fReader, "tausL_leptonsT_invariantMass"};
   TTreeReaderValue<Double_t> tausT_leptonsT_invariantMass = {fReader, "tausT_leptonsT_invariantMass"};
   TTreeReaderValue<Double_t> tausF_leptonsT_chargeSum = {fReader, "tausF_leptonsT_chargeSum"};
   TTreeReaderValue<Double_t> tausF_leptonsTMVA_minDeltaR = {fReader, "tausF_leptonsTMVA_minDeltaR"};
   TTreeReaderValue<Double_t> tausL_leptonsTMVA_minDeltaR = {fReader, "tausL_leptonsTMVA_minDeltaR"};
   TTreeReaderValue<Double_t> tausT_leptonsTMVA_minDeltaR = {fReader, "tausT_leptonsTMVA_minDeltaR"};
   TTreeReaderValue<Double_t> Met_pt = {fReader, "Met_pt"};
   TTreeReaderValue<Double_t> Met_phi = {fReader, "Met_phi"};
   TTreeReaderValue<Double_t> TransverseMassMetTop = {fReader, "TransverseMassMetTop"};
   TTreeReaderValue<Int_t> toptagger_num = {fReader, "toptagger_num"};
   TTreeReaderValue<Double_t> toptagger_MHT = {fReader, "toptagger_MHT"};
   TTreeReaderValue<Double_t> toptagger_HT = {fReader, "toptagger_HT"};
   TTreeReaderValue<Double_t> toptagger_invariantMass = {fReader, "toptagger_invariantMass"};
   TTreeReaderValue<Double_t> toptagger_transMass = {fReader, "toptagger_transMass"};
   TTreeReaderValue<Double_t> toptagger_minDeltaR_v1 = {fReader, "toptagger_minDeltaR_v1"};
   TTreeReaderValue<Int_t> toptagger_1pt = {fReader, "toptagger_1pt"};
   TTreeReaderValue<Int_t> toptagger_1eta = {fReader, "toptagger_1eta"};
   TTreeReaderValue<Int_t> toptagger_1phi = {fReader, "toptagger_1phi"};
   TTreeReaderValue<Double_t> toptagger_2pt = {fReader, "toptagger_2pt"};
   TTreeReaderValue<Double_t> toptagger_2eta = {fReader, "toptagger_2eta"};
   TTreeReaderValue<Double_t> toptagger_2phi = {fReader, "toptagger_2phi"};
   TTreeReaderValue<Double_t> toptagger_3pt = {fReader, "toptagger_3pt"};
   TTreeReaderValue<Double_t> toptagger_3eta = {fReader, "toptagger_3eta"};
   TTreeReaderValue<Double_t> toptagger_3phi = {fReader, "toptagger_3phi"};
   TTreeReaderValue<Double_t> toptagger_minDeltaR = {fReader, "toptagger_minDeltaR"};
   TTreeReaderValue<Double_t> toptagger_maxDeltaR = {fReader, "toptagger_maxDeltaR"};
   TTreeReaderValue<Double_t> toptagger_scoreAllTops = {fReader, "toptagger_scoreAllTops"};
   TTreeReaderValue<Double_t> toptagger_leptonsMVAT_minDeltaR = {fReader, "toptagger_leptonsMVAT_minDeltaR"};
   TTreeReaderValue<Int_t> NumSelWJets = {fReader, "NumSelWJets"};
   TTreeReaderValue<Int_t> NumSelTopJets = {fReader, "NumSelTopJets"};
   TTreeReaderValue<Int_t> NVertices = {fReader, "NVertices"};
   TTreeReaderValue<Double_t> PUWeight = {fReader, "PUWeight"};
   TTreeReaderValue<Double_t> PUWeightUP = {fReader, "PUWeightUP"};
   TTreeReaderValue<Double_t> PUWeightDOWN = {fReader, "PUWeightDOWN"};
   TTreeReaderValue<Int_t> getTrueNumInteractions = {fReader, "getTrueNumInteractions"};
   TTreeReaderValue<Double_t> w_for = {fReader, "w_for"};
   TTreeReaderValue<Double_t> w_forUp = {fReader, "w_forUp"};
   TTreeReaderValue<Double_t> w_forDown = {fReader, "w_forDown"};
   TTreeReaderValue<Double_t> w_topJet = {fReader, "w_topJet"};
   TTreeReaderValue<Double_t> w_topJetUp = {fReader, "w_topJetUp"};
   TTreeReaderValue<Double_t> w_topJetDown = {fReader, "w_topJetDown"};
   TTreeReaderValue<Double_t> w_WJet = {fReader, "w_WJet"};
   TTreeReaderValue<Double_t> w_WJetUp = {fReader, "w_WJetUp"};
   TTreeReaderValue<Double_t> w_WJetDown = {fReader, "w_WJetDown"};
   TTreeReaderValue<Double_t> w_Muon1 = {fReader, "w_Muon1"};
   TTreeReaderValue<Double_t> w_Muon2 = {fReader, "w_Muon2"};
   TTreeReaderValue<Double_t> w_Muon1Up = {fReader, "w_Muon1Up"};
   TTreeReaderValue<Double_t> w_Muon2Up = {fReader, "w_Muon2Up"};
   TTreeReaderValue<Double_t> w_Muon1Down = {fReader, "w_Muon1Down"};
   TTreeReaderValue<Double_t> w_Muon2Down = {fReader, "w_Muon2Down"};
   TTreeReaderValue<Double_t> w_TrigMuon = {fReader, "w_TrigMuon"};
   TTreeReaderValue<Double_t> w_TrigMuonUp = {fReader, "w_TrigMuonUp"};
   TTreeReaderValue<Double_t> w_TrigMuonDown = {fReader, "w_TrigMuonDown"};
   TTreeReaderValue<Double_t> w_Electron1 = {fReader, "w_Electron1"};
   TTreeReaderValue<Double_t> w_Electron2 = {fReader, "w_Electron2"};
   TTreeReaderValue<Double_t> w_Electron1Up = {fReader, "w_Electron1Up"};
   TTreeReaderValue<Double_t> w_Electron2Up = {fReader, "w_Electron2Up"};
   TTreeReaderValue<Double_t> w_Electron1Down = {fReader, "w_Electron1Down"};
   TTreeReaderValue<Double_t> w_Electron2Down = {fReader, "w_Electron2Down"};
   TTreeReaderValue<Double_t> w_TrigElec = {fReader, "w_TrigElec"};
   TTreeReaderValue<Double_t> w_TrigElecUp = {fReader, "w_TrigElecUp"};
   TTreeReaderValue<Double_t> w_TrigElecDown = {fReader, "w_TrigElecDown"};
   TTreeReaderValue<Double_t> w_ZToNuNu = {fReader, "w_ZToNuNu"};
   TTreeReaderValue<Double_t> w_ZToNuNuUp = {fReader, "w_ZToNuNuUp"};
   TTreeReaderValue<Double_t> w_ZToNuNuDown = {fReader, "w_ZToNuNuDown"};
   TTreeReaderValue<Double_t> w_WToLNu = {fReader, "w_WToLNu"};
   TTreeReaderValue<Double_t> w_WToLNuUp = {fReader, "w_WToLNuUp"};
   TTreeReaderValue<Double_t> w_WToLNuDown = {fReader, "w_WToLNuDown"};
   TTreeReaderValue<Double_t> w_ttbar = {fReader, "w_ttbar"};
   TTreeReaderValue<Double_t> w_ttbarUp = {fReader, "w_ttbarUp"};
   TTreeReaderValue<Double_t> w_ttbarDown = {fReader, "w_ttbarDown"};
   TTreeReaderValue<Double_t> w_Trig = {fReader, "w_Trig"};
   TTreeReaderValue<Double_t> w_TrigUp = {fReader, "w_TrigUp"};
   TTreeReaderValue<Double_t> w_TrigDown = {fReader, "w_TrigDown"};
   TTreeReaderValue<Double_t> WMass = {fReader, "WMass"};
   TTreeReaderValue<Double_t> WSubjet = {fReader, "WSubjet"};
   TTreeReaderValue<Double_t> TopSoftMass = {fReader, "TopSoftMass"};
   TTreeReaderValue<Double_t> TopSubjet = {fReader, "TopSubjet"};
   TTreeReaderValue<Double_t> w_Btag = {fReader, "w_Btag"};
   TTreeReaderValue<Double_t> w_BtagUp = {fReader, "w_BtagUp"};
   TTreeReaderValue<Double_t> w_BtagDown = {fReader, "w_BtagDown"};
   TTreeReaderValue<Double_t> w_Btag1Up = {fReader, "w_Btag1Up"};
   TTreeReaderValue<Double_t> w_Btag1Down = {fReader, "w_Btag1Down"};
   TTreeReaderValue<Double_t> w_Btag2Up = {fReader, "w_Btag2Up"};
   TTreeReaderValue<Double_t> w_Btag2Down = {fReader, "w_Btag2Down"};
   TTreeReaderValue<Double_t> w_BtagLoose = {fReader, "w_BtagLoose"};
   TTreeReaderValue<Double_t> w_BtagLooseUp = {fReader, "w_BtagLooseUp"};
   TTreeReaderValue<Double_t> w_BtagLooseDown = {fReader, "w_BtagLooseDown"};
   TTreeReaderValue<Double_t> w_QCDUp = {fReader, "w_QCDUp"};
   TTreeReaderValue<Double_t> w_QCDDown = {fReader, "w_QCDDown"};
   TTreeReaderValue<Double_t> w_PDFUp = {fReader, "w_PDFUp"};
   TTreeReaderValue<Double_t> w_PDFDown = {fReader, "w_PDFDown"};
   TTreeReaderValue<Double_t> deltaPhiZTopResolved = {fReader, "deltaPhiZTopResolved"};
   TTreeReaderValue<Double_t> deltaRZTopResolved = {fReader, "deltaRZTopResolved"};
   TTreeReaderValue<Double_t> deltaPhiZTopPartial = {fReader, "deltaPhiZTopPartial"};
   TTreeReaderValue<Double_t> deltaRZTopPartial = {fReader, "deltaRZTopPartial"};
   TTreeReaderValue<Double_t> deltaPhiZTopMerged = {fReader, "deltaPhiZTopMerged"};
   TTreeReaderValue<Double_t> deltaRZTopMerged = {fReader, "deltaRZTopMerged"};
   TTreeReaderValue<Double_t> deltaRbTop = {fReader, "deltaRbTop"};
   TTreeReaderValue<Double_t> deltaPhiMetTop = {fReader, "deltaPhiMetTop"};
   TTreeReaderValue<Double_t> genWeight = {fReader, "genWeight"};
   TTreeReaderValue<Int_t> dQuark = {fReader, "dQuark"};
   TTreeReaderValue<Int_t> uQuark = {fReader, "uQuark"};
   TTreeReaderValue<Int_t> sQuark = {fReader, "sQuark"};
   TTreeReaderValue<Int_t> cQuark = {fReader, "cQuark"};
   TTreeReaderValue<Int_t> bQuark = {fReader, "bQuark"};
   TTreeReaderValue<Int_t> tQuark = {fReader, "tQuark"};
   TTreeReaderValue<Int_t> EVENT_event = {fReader, "EVENT_event"};
   TTreeReaderValue<Int_t> EVENT_run = {fReader, "EVENT_run"};
   TTreeReaderValue<Int_t> EVENT_lumiBlock = {fReader, "EVENT_lumiBlock"};
   TTreeReaderValue<Double_t> EVENT_genHT = {fReader, "EVENT_genHT"};
   TTreeReaderValue<Double_t> prefiringweight = {fReader, "prefiringweight"};
   TTreeReaderValue<Double_t> prefiringweightup = {fReader, "prefiringweightup"};
   TTreeReaderValue<Double_t> prefiringweightdown = {fReader, "prefiringweightdown"};
   TTreeReaderValue<Double_t> puWeight = {fReader, "puWeight"};
   TTreeReaderValue<Double_t> EVENT_genWeight = {fReader, "EVENT_genWeight"};


   makeVariblesTree_v2(TTree * /*tree*/ =0) { }
   virtual ~makeVariblesTree_v2() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(makeVariblesTree_v2,0);

};

#endif

#ifdef makeVariblesTree_v2_cxx
void makeVariblesTree_v2::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t makeVariblesTree_v2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef makeVariblesTree_v2_cxx
