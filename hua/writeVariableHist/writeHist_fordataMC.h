//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 28 02:15:42 2022 by ROOT version 6.22/09
// from TChain newtree/
//////////////////////////////////////////////////////////

#ifndef writeHist_fordataMC_h
#define writeHist_fordataMC_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

#include <TH1D.h>

// Headers needed by this particular selector

class writeHist_fordataMC : public TSelector
{
public:
   TTreeReader fReader; //! the tree reader
   TTree *fChain = 0;   //! pointer to the analyzed TTree or TChain

   // my member variables
   Bool_t m_isData;
   Double_t m_genWeightSum;
   TString m_outputFolder;
   TString m_processName;
   TString m_era;
   // TString m_version = "v1moreVariables";
   TString m_version;
   // std::vector<TString> m_options;
   TFile *outputFile;
   //!!!hists need to be scalec in terminate function
   //???make this variables easier to add
   // TH1D* whInitial;
   std::vector<TH1D *> eventCount_hists;
   std::vector<TH1D *> jetsNumber_hists;
   std::vector<TH1D *> jets_HT_hists;
   std::vector<TH1D *> jets_bScore_hists;
   std::vector<TH1D *> jets_1pt_hists;

   std::vector<TH1D *> tausT_HT_hists;
   std::vector<TH1D *> tausT_1pt_hists;
   std::vector<TH1D *> tausT_1eta_hists;
   // std::vector<TH1D *> _hists;

   std::vector<TH1D *> bjetsM_MHT_hists;
   std::vector<TH1D *> bjets_Number_hists;
   std::vector<TH1D *> bjets_1pt_hists;
   std::vector<TH1D *> bjets_HT_hists;

   std::vector<TH1D *> jets_bScoreMultiply_hists;
   std::vector<TH1D *> jets_2pt_hists;
   std::vector<TH1D *> jets_3pt_hists;
   std::vector<TH1D *> jets_4pt_hists;
   std::vector<TH1D *> jets_5pt_hists;
   std::vector<TH1D *> jets_6pt_hists;
   std::vector<TH1D *> jets_HTto4rest_hists;

   // variables to be writen to hists

   // regions to consider

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<ULong64_t>
       event = {fReader, "event"};
   TTreeReaderValue<Int_t> Flag_goodVertices = {fReader, "Flag_goodVertices"};
   TTreeReaderValue<Int_t> Flag_globalSuperTightHalo2016Filter = {fReader, "Flag_globalSuperTightHalo2016Filter"};
   TTreeReaderValue<Int_t> Flag_HBHENoiseFilter = {fReader, "Flag_HBHENoiseFilter"};
   TTreeReaderValue<Int_t> Flag_HBHENoiseIsoFilter = {fReader, "Flag_HBHENoiseIsoFilter"};
   TTreeReaderValue<Int_t> Flag_EcalDeadCellTriggerPrimitiveFilter = {fReader, "Flag_EcalDeadCellTriggerPrimitiveFilter"};
   TTreeReaderValue<Int_t> Flag_BadPFMuonFilter = {fReader, "Flag_BadPFMuonFilter"};
   TTreeReaderValue<Int_t> Flag_eeBadScFilter = {fReader, "Flag_eeBadScFilter"};
   TTreeReaderValue<Int_t> HLT_PFHT450_SixJet40_BTagCSV_p056 = {fReader, "HLT_PFHT450_SixJet40_BTagCSV_p056"};
   TTreeReaderValue<Int_t> HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = {fReader, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056"};
   TTreeReaderValue<Int_t> HLT_PFJet450 = {fReader, "HLT_PFJet450"};
   TTreeReaderValue<Double_t> EVENT_prefireWeight = {fReader, "EVENT_prefireWeight"};
   TTreeReaderValue<Double_t> EVENT_prefireWeight_up = {fReader, "EVENT_prefireWeight_up"};
   TTreeReaderValue<Double_t> EVENT_prefireWeight_down = {fReader, "EVENT_prefireWeight_down"};
   TTreeReaderValue<Double_t> EVENT_genWeight = {fReader, "EVENT_genWeight"};
   TTreeReaderValue<Double_t> PUweight = {fReader, "PUweight"};
   TTreeReaderValue<Double_t> PUweight_up = {fReader, "PUweight_up"};
   TTreeReaderValue<Double_t> PUweight_down = {fReader, "PUweight_down"};
   TTreeReaderValue<Double_t> btagEfficiency_weight = {fReader, "btagEfficiency_weight"};
   TTreeReaderValue<Double_t> HLTefficiency_weight = {fReader, "HLTefficiency_weight"};
   TTreeReaderValue<Double_t> muonIDSF_weight = {fReader, "muonIDSF_weight"};
   TTreeReaderValue<Double_t> muonIDSF_weight_up = {fReader, "muonIDSF_weight_up"};
   TTreeReaderValue<Double_t> muonIDSF_weight_down = {fReader, "muonIDSF_weight_down"};
   TTreeReaderValue<Double_t> mounTrackerSF_weight = {fReader, "mounTrackerSF_weight"};
   TTreeReaderValue<Double_t> eleMVAT_IDSF_weight = {fReader, "eleMVAT_IDSF_weight"};
   TTreeReaderValue<Double_t> eleMVAT_IDSF_weight_up = {fReader, "eleMVAT_IDSF_weight_up"};
   TTreeReaderValue<Double_t> eleMVAT_IDSF_weight_down = {fReader, "eleMVAT_IDSF_weight_down"};
   TTreeReaderValue<Double_t> eleMVAT_IDSF_weight_backup = {fReader, "eleMVAT_IDSF_weight_backup"};
   TTreeReaderValue<Double_t> tauT_IDSF_weight = {fReader, "tauT_IDSF_weight"};
   TTreeReaderValue<Double_t> tauT_IDSF_weight_new = {fReader, "tauT_IDSF_weight_new"};
   TTreeReaderValue<Double_t> tauT_IDSF_weight_new_vsjet_up = {fReader, "tauT_IDSF_weight_new_vsjet_up"};
   TTreeReaderValue<Double_t> tauT_IDSF_weight_new_vsjet_down = {fReader, "tauT_IDSF_weight_new_vsjet_down"};
   TTreeReaderValue<Double_t> tauT_IDSF_weight_new_vsmu_up = {fReader, "tauT_IDSF_weight_new_vsmu_up"};
   TTreeReaderValue<Double_t> tauT_IDSF_weight_new_vsmu_down = {fReader, "tauT_IDSF_weight_new_vsmu_down"};
   TTreeReaderValue<Double_t> tauT_IDSF_weight_new_vsele_up = {fReader, "tauT_IDSF_weight_new_vsele_up"};
   TTreeReaderValue<Double_t> tauT_IDSF_weight_new_vsele_down = {fReader, "tauT_IDSF_weight_new_vsele_down"};
   TTreeReaderValue<Double_t> Met_pt_ = {fReader, "Met_pt_"};
   TTreeReaderValue<Double_t> Met_phi_ = {fReader, "Met_phi_"};
   TTreeReaderValue<Int_t> muonsL_number = {fReader, "muonsL_number"};
   TTreeReaderValue<Int_t> muonsF_number = {fReader, "muonsF_number"};
   TTreeReaderValue<Int_t> muonsT_number = {fReader, "muonsT_number"};
   TTreeReaderValue<Double_t> muonsT_1pt = {fReader, "muonsT_1pt"};
   TTreeReaderValue<Double_t> muonsT_1eta = {fReader, "muonsT_1eta"};
   TTreeReaderValue<Double_t> muonsT_1phi = {fReader, "muonsT_1phi"};
   TTreeReaderValue<Double_t> muonsT_2pt = {fReader, "muonsT_2pt"};
   TTreeReaderValue<Double_t> muonsT_2eta = {fReader, "muonsT_2eta"};
   TTreeReaderValue<Double_t> muonsT_2phi = {fReader, "muonsT_2phi"};
   TTreeReaderValue<Double_t> muonsT_3pt = {fReader, "muonsT_3pt"};
   TTreeReaderValue<Double_t> muonsT_3eta = {fReader, "muonsT_3eta"};
   TTreeReaderValue<Double_t> muonsT_3phi = {fReader, "muonsT_3phi"};
   TTreeReaderValue<Int_t> elesMVAL_number = {fReader, "elesMVAL_number"};
   TTreeReaderValue<Int_t> elesMVAF_number = {fReader, "elesMVAF_number"};
   TTreeReaderValue<Int_t> elesMVAT_number = {fReader, "elesMVAT_number"};
   TTreeReaderValue<Double_t> elesMVAF_1pt = {fReader, "elesMVAF_1pt"};
   TTreeReaderValue<Int_t> leptonsMVAT_number = {fReader, "leptonsMVAT_number"};
   TTreeReaderValue<Int_t> leptonsMVAF_number = {fReader, "leptonsMVAF_number"};
   TTreeReaderValue<Int_t> leptonsMVAL_number = {fReader, "leptonsMVAL_number"};
   TTreeReaderValue<Double_t> leptonsMVAT_transMass = {fReader, "leptonsMVAT_transMass"};
   TTreeReaderValue<Double_t> leptonsMVAF_transMass = {fReader, "leptonsMVAF_transMass"};
   TTreeReaderValue<Double_t> leptonsMVAL_transMass = {fReader, "leptonsMVAL_transMass"};
   TTreeReaderValue<Int_t> leptonsMVAT_2SS = {fReader, "leptonsMVAT_2SS"};
   TTreeReaderValue<Int_t> leptonsMVAT_2OS = {fReader, "leptonsMVAT_2OS"};
   TTreeReaderValue<Double_t> leptonsMVAT_1pt = {fReader, "leptonsMVAT_1pt"};
   TTreeReaderValue<Double_t> leptonsMVAT_1eta = {fReader, "leptonsMVAT_1eta"};
   TTreeReaderValue<Double_t> leptonsMVAT_1phi = {fReader, "leptonsMVAT_1phi"};
   TTreeReaderValue<Double_t> leptonsMVAT_2pt = {fReader, "leptonsMVAT_2pt"};
   TTreeReaderValue<Double_t> leptonsMVAT_2eta = {fReader, "leptonsMVAT_2eta"};
   TTreeReaderValue<Double_t> leptonsMVAT_2phi = {fReader, "leptonsMVAT_2phi"};
   TTreeReaderValue<Double_t> leptonsMVAT_3pt = {fReader, "leptonsMVAT_3pt"};
   TTreeReaderValue<Double_t> leptonsMVAT_3eta = {fReader, "leptonsMVAT_3eta"};
   TTreeReaderValue<Double_t> leptonsMVAT_3phi = {fReader, "leptonsMVAT_3phi"};
   TTreeReaderValue<Int_t> tausT_number_TESup = {fReader, "tausT_number_TESup"};
   TTreeReaderValue<Int_t> tausT_number_TESdown = {fReader, "tausT_number_TESdown"};
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
   TTreeReaderValue<Double_t> tausT_1pt = {fReader, "tausT_1pt"};
   TTreeReaderValue<Double_t> tausT_1eta = {fReader, "tausT_1eta"};
   TTreeReaderValue<Double_t> tausT_1phi = {fReader, "tausT_1phi"};
   TTreeReaderValue<Double_t> tausT_2pt = {fReader, "tausT_2pt"};
   TTreeReaderValue<Double_t> tausT_2eta = {fReader, "tausT_2eta"};
   TTreeReaderValue<Double_t> tausT_2phi = {fReader, "tausT_2phi"};
   TTreeReaderValue<Double_t> tausT_3pt = {fReader, "tausT_3pt"};
   TTreeReaderValue<Double_t> tausT_3eta = {fReader, "tausT_3eta"};
   TTreeReaderValue<Double_t> tausT_3phi = {fReader, "tausT_3phi"};
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
   TTreeReaderValue<Double_t> jets_HT_JECup = {fReader, "jets_HT_JECup"};
   TTreeReaderValue<Double_t> jets_HT_JECdown = {fReader, "jets_HT_JECdown"};
   TTreeReaderValue<Int_t> jets_number_JECup = {fReader, "jets_number_JECup"};
   TTreeReaderValue<Int_t> jets_number_JECdown = {fReader, "jets_number_JECdown"};
   TTreeReaderValue<Int_t> jets_number = {fReader, "jets_number"};
   TTreeReaderValue<Double_t> jets_HT = {fReader, "jets_HT"};
   TTreeReaderValue<Double_t> jets_MHT = {fReader, "jets_MHT"};
   TTreeReaderValue<Double_t> jets_invariantMass = {fReader, "jets_invariantMass"};
   TTreeReaderValue<Double_t> jets_transMass = {fReader, "jets_transMass"};
   TTreeReaderValue<Double_t> jets_minDeltaR = {fReader, "jets_minDeltaR"};
   TTreeReaderValue<Double_t> jets_centrality = {fReader, "jets_centrality"};
   TTreeReaderValue<Double_t> jets_bScore = {fReader, "jets_bScore"};
   TTreeReaderValue<Double_t> jets_bScoreMultiply = {fReader, "jets_bScoreMultiply"};
   // TTreeReaderValue<Double_t> jets_average_deltaR = {fReader, "jets_average_deltaR"};//??? probmatic
   TTreeReaderValue<Double_t> jets_4largestBscoreSum = {fReader, "jets_4largestBscoreSum"};
   TTreeReaderValue<Double_t> jets_4largestBscoreMulti = {fReader, "jets_4largestBscoreMulti"};
   TTreeReaderValue<Double_t> jets_leading2invariantMass = {fReader, "jets_leading2invariantMass"};
   TTreeReaderValue<Double_t> jets_rationHT_4toRest = {fReader, "jets_rationHT_4toRest"};
   TTreeReaderValue<Double_t> jets_leptonsMVAT_minDeltaR = {fReader, "jets_leptonsMVAT_minDeltaR"};
   TTreeReaderValue<Double_t> jets_tausF_minDeltaR = {fReader, "jets_tausF_minDeltaR"};
   TTreeReaderValue<Double_t> jets_HTDividedByMet = {fReader, "jets_HTDividedByMet"};
   TTreeReaderValue<Double_t> MetDividedByHT = {fReader, "MetDividedByHT"};
   TTreeReaderValue<Double_t> jets_MHTDividedByMet = {fReader, "jets_MHTDividedByMet"};
   TTreeReaderValue<Double_t> jets_spherilty = {fReader, "jets_spherilty"};
   TTreeReaderValue<Double_t> jets_aplanarity = {fReader, "jets_aplanarity"};
   TTreeReaderValue<Double_t> jets_1pt = {fReader, "jets_1pt"};
   TTreeReaderValue<Double_t> jets_1eta = {fReader, "jets_1eta"};
   TTreeReaderValue<Double_t> jets_1phi = {fReader, "jets_1phi"};
   TTreeReaderValue<Double_t> jets_2pt = {fReader, "jets_2pt"};
   TTreeReaderValue<Double_t> jets_2eta = {fReader, "jets_2eta"};
   TTreeReaderValue<Double_t> jets_2phi = {fReader, "jets_2phi"};
   TTreeReaderValue<Double_t> jets_3pt = {fReader, "jets_3pt"};
   TTreeReaderValue<Double_t> jets_3eta = {fReader, "jets_3eta"};
   TTreeReaderValue<Double_t> jets_3phi = {fReader, "jets_3phi"};
   TTreeReaderValue<Double_t> jets_4pt = {fReader, "jets_4pt"};
   TTreeReaderValue<Double_t> jets_4eta = {fReader, "jets_4eta"};
   TTreeReaderValue<Double_t> jets_4phi = {fReader, "jets_4phi"};
   TTreeReaderValue<Double_t> jets_5pt = {fReader, "jets_5pt"};
   TTreeReaderValue<Double_t> jets_5eta = {fReader, "jets_5eta"};
   TTreeReaderValue<Double_t> jets_5phi = {fReader, "jets_5phi"};
   TTreeReaderValue<Double_t> jets_6pt = {fReader, "jets_6pt"};
   TTreeReaderValue<Double_t> jets_6eta = {fReader, "jets_6eta"};
   TTreeReaderValue<Double_t> jets_6phi = {fReader, "jets_6phi"};
   TTreeReaderValue<Double_t> jets_7pt = {fReader, "jets_7pt"};
   TTreeReaderValue<Double_t> jets_7eta = {fReader, "jets_7eta"};
   TTreeReaderValue<Double_t> jets_7phi = {fReader, "jets_7phi"};
   TTreeReaderValue<Double_t> jets_8pt = {fReader, "jets_8pt"};
   TTreeReaderValue<Double_t> jets_8eta = {fReader, "jets_8eta"};
   TTreeReaderValue<Double_t> jets_8phi = {fReader, "jets_8phi"};
   TTreeReaderValue<Double_t> jets_9pt = {fReader, "jets_9pt"};
   TTreeReaderValue<Double_t> jets_9eta = {fReader, "jets_9eta"};
   TTreeReaderValue<Double_t> jets_9phi = {fReader, "jets_9phi"};
   TTreeReaderValue<Double_t> jets_10pt = {fReader, "jets_10pt"};
   TTreeReaderValue<Double_t> jets_10eta = {fReader, "jets_10eta"};
   TTreeReaderValue<Double_t> jets_10phi = {fReader, "jets_10phi"};
   TTreeReaderValue<Double_t> jets_11pt = {fReader, "jets_11pt"};
   TTreeReaderValue<Double_t> jets_11eta = {fReader, "jets_11eta"};
   TTreeReaderValue<Double_t> jets_11phi = {fReader, "jets_11phi"};
   // TTreeReaderValue<Int_t> bjetsL_num = {fReader, "bjetsL_num"};
   TTreeReaderValue<Int_t> bjetsM_num = {fReader, "bjetsM_num"};
   // TTreeReaderValue<Int_t> bjetsT_num = {fReader, "bjetsT_num"};
   // TTreeReaderValue<Double_t> bjetsL_HT = {fReader, "bjetsL_HT"};
   TTreeReaderValue<Double_t> bjetsM_HT = {fReader, "bjetsM_HT"};
   // TTreeReaderValue<Double_t> bjetsT_HT = {fReader, "bjetsT_HT"};
   // TTreeReaderValue<Double_t> bjetsL_MHT = {fReader, "bjetsL_MHT"};
   TTreeReaderValue<Double_t> bjetsM_MHT = {fReader, "bjetsM_MHT"};
   // TTreeReaderValue<Double_t> bjetsT_MHT = {fReader, "bjetsT_MHT"};
   // TTreeReaderValue<Double_t> bjetsL_invariantMass = {fReader, "bjetsL_invariantMass"};
   TTreeReaderValue<Double_t> bjetsM_invariantMass = {fReader, "bjetsM_invariantMass"};
   // TTreeReaderValue<Double_t> bjetsT_invariantMass = {fReader, "bjetsT_invariantMass"};
   // TTreeReaderValue<Double_t> bjetsL_transMass = {fReader, "bjetsL_transMass"};
   // TTreeReaderValue<Double_t> bjetsM_transMass = {fReader, "bjetsM_transMass"};
   // TTreeReaderValue<Double_t> bjetsT_transMass = {fReader, "bjetsT_transMass"};
   // TTreeReaderValue<Double_t> bjetsL_minDeltaR = {fReader, "bjetsL_minDeltaR"};
   // TTreeReaderValue<Double_t> bjetsM_minDeltaR = {fReader, "bjetsM_minDeltaR"};
   // TTreeReaderValue<Double_t> bjetsT_minDeltaR = {fReader, "bjetsT_minDeltaR"};
   // TTreeReaderValue<Double_t> bjetsL_leptonsMVAT_minDeltaR = {fReader, "bjetsL_leptonsMVAT_minDeltaR"};
   // TTreeReaderValue<Double_t> bjetsM_leptonsMVAT_minDeltaR = {fReader, "bjetsM_leptonsMVAT_minDeltaR"};
   // TTreeReaderValue<Double_t> bjetsT_leptonsMVAT_minDeltaR = {fReader, "bjetsT_leptonsMVAT_minDeltaR"};
   // TTreeReaderValue<Double_t> bjetsL_tausF_minDeltaR = {fReader, "bjetsL_tausF_minDeltaR"};
   // TTreeReaderValue<Double_t> bjetsL_1pt = {fReader, "bjetsL_1pt"};
   // TTreeReaderValue<Double_t> bjetsL_1eta = {fReader, "bjetsL_1eta"};
   // TTreeReaderValue<Double_t> bjetsL_1phi = {fReader, "bjetsL_1phi"};
   // TTreeReaderValue<Double_t> bjetsL_2pt = {fReader, "bjetsL_2pt"};
   // TTreeReaderValue<Double_t> bjetsL_2eta = {fReader, "bjetsL_2eta"};
   // TTreeReaderValue<Double_t> bjetsL_2phi = {fReader, "bjetsL_2phi"};
   // TTreeReaderValue<Double_t> bjetsL_3pt = {fReader, "bjetsL_3pt"};
   // TTreeReaderValue<Double_t> bjetsL_3eta = {fReader, "bjetsL_3eta"};
   // TTreeReaderValue<Double_t> bjetsL_3phi = {fReader, "bjetsL_3phi"};
   // TTreeReaderValue<Double_t> bjetsL_4pt = {fReader, "bjetsL_4pt"};
   // TTreeReaderValue<Double_t> bjetsL_4eta = {fReader, "bjetsL_4eta"};
   // TTreeReaderValue<Double_t> bjetsL_4phi = {fReader, "bjetsL_4phi"};
   TTreeReaderValue<Double_t> bjetsM_1pt = {fReader, "bjetsM_1pt"};
   // TTreeReaderValue<Double_t> bjetsM_1eta = {fReader, "bjetsM_1eta"};
   // TTreeReaderValue<Double_t> bjetsM_1phi = {fReader, "bjetsM_1phi"};
   // TTreeReaderValue<Double_t> bjetsM_2pt = {fReader, "bjetsM_2pt"};
   // TTreeReaderValue<Double_t> bjetsM_2eta = {fReader, "bjetsM_2eta"};
   // TTreeReaderValue<Double_t> bjetsM_2phi = {fReader, "bjetsM_2phi"};
   // TTreeReaderValue<Double_t> bjetsM_3pt = {fReader, "bjetsM_3pt"};
   // TTreeReaderValue<Double_t> bjetsM_3eta = {fReader, "bjetsM_3eta"};
   // TTreeReaderValue<Double_t> bjetsM_3phi = {fReader, "bjetsM_3phi"};
   // TTreeReaderValue<Double_t> bjetsM_4pt = {fReader, "bjetsM_4pt"};
   // TTreeReaderValue<Double_t> bjetsM_4eta = {fReader, "bjetsM_4eta"};
   // TTreeReaderValue<Double_t> bjetsM_4phi = {fReader, "bjetsM_4phi"};
   // TTreeReaderValue<Double_t> bjetsT_1pt = {fReader, "bjetsT_1pt"};
   // TTreeReaderValue<Double_t> bjetsT_1eta = {fReader, "bjetsT_1eta"};
   // TTreeReaderValue<Double_t> bjetsT_1phi = {fReader, "bjetsT_1phi"};
   // TTreeReaderValue<Double_t> bjetsT_2pt = {fReader, "bjetsT_2pt"};
   // TTreeReaderValue<Double_t> bjetsT_2eta = {fReader, "bjetsT_2eta"};
   // TTreeReaderValue<Double_t> bjetsT_2phi = {fReader, "bjetsT_2phi"};
   // TTreeReaderValue<Double_t> bjetsT_3pt = {fReader, "bjetsT_3pt"};
   // TTreeReaderValue<Double_t> bjetsT_3eta = {fReader, "bjetsT_3eta"};
   // TTreeReaderValue<Double_t> bjetsT_3phi = {fReader, "bjetsT_3phi"};
   // TTreeReaderValue<Double_t> bjetsT_4pt = {fReader, "bjetsT_4pt"};
   // TTreeReaderValue<Double_t> bjetsT_4eta = {fReader, "bjetsT_4eta"};
   // TTreeReaderValue<Double_t> bjetsT_4phi = {fReader, "bjetsT_4phi"};
   // TTreeReaderValue<Int_t> nonbjetsL_num = {fReader, "nonbjetsL_num"};
   // TTreeReaderValue<Int_t> nonbjetsM_num = {fReader, "nonbjetsM_num"};
   // TTreeReaderValue<Int_t> nonbjetsT_num = {fReader, "nonbjetsT_num"};
   // TTreeReaderValue<Double_t> nonbjetsL_1pt = {fReader, "nonbjetsL_1pt"};
   // TTreeReaderValue<Double_t> nonbjetsL_1eta = {fReader, "nonbjetsL_1eta"};
   // TTreeReaderValue<Double_t> nonbjetsL_1phi = {fReader, "nonbjetsL_1phi"};
   // TTreeReaderValue<Double_t> nonbjetsL_2pt = {fReader, "nonbjetsL_2pt"};
   // TTreeReaderValue<Double_t> nonbjetsL_2eta = {fReader, "nonbjetsL_2eta"};
   // TTreeReaderValue<Double_t> nonbjetsL_2phi = {fReader, "nonbjetsL_2phi"};
   // TTreeReaderValue<Double_t> nonbjetsL_3pt = {fReader, "nonbjetsL_3pt"};
   // TTreeReaderValue<Double_t> nonbjetsL_3eta = {fReader, "nonbjetsL_3eta"};
   // TTreeReaderValue<Double_t> nonbjetsL_3phi = {fReader, "nonbjetsL_3phi"};
   // TTreeReaderValue<Double_t> nonbjetsL_4pt = {fReader, "nonbjetsL_4pt"};
   // TTreeReaderValue<Double_t> nonbjetsL_4eta = {fReader, "nonbjetsL_4eta"};
   // TTreeReaderValue<Double_t> nonbjetsL_4phi = {fReader, "nonbjetsL_4phi"};
   // TTreeReaderValue<Double_t> nonbjetsM_1pt = {fReader, "nonbjetsM_1pt"};
   // TTreeReaderValue<Double_t> nonbjetsM_1eta = {fReader, "nonbjetsM_1eta"};
   // TTreeReaderValue<Double_t> nonbjetsM_1phi = {fReader, "nonbjetsM_1phi"};
   // TTreeReaderValue<Double_t> nonbjetsM_2pt = {fReader, "nonbjetsM_2pt"};
   // TTreeReaderValue<Double_t> nonbjetsM_2eta = {fReader, "nonbjetsM_2eta"};
   // TTreeReaderValue<Double_t> nonbjetsM_2phi = {fReader, "nonbjetsM_2phi"};
   // TTreeReaderValue<Double_t> nonbjetsM_3pt = {fReader, "nonbjetsM_3pt"};
   // TTreeReaderValue<Double_t> nonbjetsM_3eta = {fReader, "nonbjetsM_3eta"};
   // TTreeReaderValue<Double_t> nonbjetsM_3phi = {fReader, "nonbjetsM_3phi"};
   // TTreeReaderValue<Double_t> nonbjetsM_4pt = {fReader, "nonbjetsM_4pt"};
   // TTreeReaderValue<Double_t> nonbjetsM_4eta = {fReader, "nonbjetsM_4eta"};
   // TTreeReaderValue<Double_t> nonbjetsM_4phi = {fReader, "nonbjetsM_4phi"};
   // TTreeReaderValue<Double_t> nonbjetsT_1pt = {fReader, "nonbjetsT_1pt"};
   // TTreeReaderValue<Double_t> nonbjetsT_1eta = {fReader, "nonbjetsT_1eta"};
   // TTreeReaderValue<Double_t> nonbjetsT_1phi = {fReader, "nonbjetsT_1phi"};
   // TTreeReaderValue<Double_t> nonbjetsT_2pt = {fReader, "nonbjetsT_2pt"};
   // TTreeReaderValue<Double_t> nonbjetsT_2eta = {fReader, "nonbjetsT_2eta"};
   // TTreeReaderValue<Double_t> nonbjetsT_2phi = {fReader, "nonbjetsT_2phi"};
   // TTreeReaderValue<Double_t> nonbjetsT_3pt = {fReader, "nonbjetsT_3pt"};
   // TTreeReaderValue<Double_t> nonbjetsT_3eta = {fReader, "nonbjetsT_3eta"};
   // TTreeReaderValue<Double_t> nonbjetsT_3phi = {fReader, "nonbjetsT_3phi"};
   // TTreeReaderValue<Double_t> nonbjetsT_4pt = {fReader, "nonbjetsT_4pt"};
   // TTreeReaderValue<Double_t> nonbjetsT_4eta = {fReader, "nonbjetsT_4eta"};
   // TTreeReaderValue<Double_t> nonbjetsT_4phi = {fReader, "nonbjetsT_4phi"};
   TTreeReaderValue<Int_t> forwardJets_num = {fReader, "forwardJets_num"};
   // TTreeReaderValue<Int_t> toptagger_num = {fReader, "toptagger_num"};
   // TTreeReaderValue<Double_t> toptagger_MHT = {fReader, "toptagger_MHT"};
   // TTreeReaderValue<Double_t> toptagger_HT = {fReader, "toptagger_HT"};
   // TTreeReaderValue<Double_t> toptagger_invariantMass = {fReader, "toptagger_invariantMass"};
   // TTreeReaderValue<Double_t> toptagger_transMass = {fReader, "toptagger_transMass"};
   // TTreeReaderValue<Double_t> toptagger_minDeltaR_v1 = {fReader, "toptagger_minDeltaR_v1"};
   // TTreeReaderValue<Int_t> toptagger_1pt = {fReader, "toptagger_1pt"};
   // TTreeReaderValue<Int_t> toptagger_1eta = {fReader, "toptagger_1eta"};
   // TTreeReaderValue<Int_t> toptagger_1phi = {fReader, "toptagger_1phi"};
   // TTreeReaderValue<Double_t> toptagger_2pt = {fReader, "toptagger_2pt"};
   // TTreeReaderValue<Double_t> toptagger_2eta = {fReader, "toptagger_2eta"};
   // TTreeReaderValue<Double_t> toptagger_2phi = {fReader, "toptagger_2phi"};
   // TTreeReaderValue<Double_t> toptagger_3pt = {fReader, "toptagger_3pt"};
   // TTreeReaderValue<Double_t> toptagger_3eta = {fReader, "toptagger_3eta"};
   // TTreeReaderValue<Double_t> toptagger_3phi = {fReader, "toptagger_3phi"};
   // TTreeReaderValue<Double_t> toptagger_scoreAllTops = {fReader, "toptagger_scoreAllTops"};
   // TTreeReaderValue<Double_t> toptagger_leptonsMVAT_minDeltaR = {fReader, "toptagger_leptonsMVAT_minDeltaR"};

   writeHist_fordataMC(TTree * /*tree*/ = 0) {}
   virtual ~writeHist_fordataMC() {}
   virtual Int_t Version() const { return 2; }
   virtual void Begin(TTree *tree);
   virtual void SlaveBegin(TTree *tree);
   virtual void Init(TTree *tree);
   virtual Bool_t Notify();
   virtual Bool_t Process(Long64_t entry);
   virtual Int_t GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void SetOption(const char *option) { fOption = option; }
   virtual void SetObject(TObject *obj) { fObject = obj; }
   virtual void SetInputList(TList *input) { fInput = input; }
   virtual TList *GetOutputList() const { return fOutput; }
   virtual void SlaveTerminate();
   virtual void Terminate();

   // functions I add
   void fillHistsVector(Bool_t isRegion, UInt_t vectorIndex, Double_t weight);

   ClassDef(writeHist_fordataMC, 0);
};

#endif

#ifdef writeHist_fordataMC_cxx
void writeHist_fordataMC::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t writeHist_fordataMC::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef writeHist_fordataMC_cxx
