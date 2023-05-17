//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar  3 16:58:43 2021 by ROOT version 6.12/07
// from TTree tree/tree after object selection
// found on file: /publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v30_fixedChargeBranchBug/TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn/v3_1-1.root
//////////////////////////////////////////////////////////

#ifndef makeVaribles_forBDT_h
#define makeVaribles_forBDT_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include "TLorentzVector.h"
#include <Math/Vector4D.h>
#include "TH1D.h"
#include "TString.h"
#include "TH2D.h"
#include <vector>
#include "variablesFunctions.h"
// #include "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/scale_factors/btagWeightCal.h"

#include "correction.h"

class makeVaribles_forBDT : public TSelector
{
public:
    TTreeReader fReader; //! the tree reader
    TTree *fChain = 0;   //! pointer to the analyzed TTree or TChain

    // add
    //   BTagCalibrationReader CSVreader;
    //  BTagCalibrationReader CSVreader(BTagEntry::OP_RESHAPING, sysType, {sysTypeJESUp, sysTypeJESDown, sysTypeHFUp, sysTypeHFDown, sysTypeLFUp, sysTypeLFDown, sysTypehfstats1Up, sysTypehfstats1Down, sysTypehfstats2Up, sysTypehfstats2Down, sysTypelfstats1Up, sysTypelfstats1Down, sysTypelfstats2Up, sysTypelfstats2Down, sysTypecfErr1Up, sysTypecfErr1Down, sysTypecfErr2Up, sysTypecfErr2Down});
    //  Int_t m_selectionBit;
    Bool_t m_MetFilters = false;
    Bool_t m_baselineSelection = false;
    Bool_t m_HLTSelection = false;
    Long64_t fProcessed = 0;
    Double_t fProcessed_genWeight = 0;
    Long64_t fPassingMetFilters = 0;
    Long64_t fPassingHLT = 0;
    Double_t fPassingHLT_genWeight = 0;
    Long64_t fPassingPreselection = 0;
    //    TString fprocessName;
    //    TString era = "2016preVFP";
    TString m_era = "2016postVFP";
    Bool_t m_isData = false;
    TString m_processName;
    TFile *outputfile;
    TTree *newtree;
    TH1D *eventCount_baseline;
    TH1D *eventCount_mvInitial;

    TH2D *MuonIDSF;
    TH2D *muonTrackerSF_hist;
    TH2D *EleIDSF;
    // TH2D *TriggerSF;
    // TH2D *TriggerSFunc;
    TH2D *triggerHist1b;
    TH2D *triggerHist2b;
    TH2D *triggerHist3b;
    TH2D *eleIDSF_topMVA;
    TH2D *muIDSF_topMVA;

    std::unique_ptr<correction::CorrectionSet> cset;
    std::unique_ptr<correction::CorrectionSet> cset_btag;
    // std::unique_ptr<correction::CorrectionSet> cset_JES;
    TH1D *btagRHist;

    // branches in the newtree
    // same order as initialize
    ULong64_t event;
    Int_t Flag_goodVertices;
    Int_t Flag_globalSuperTightHalo2016Filter;
    Int_t Flag_HBHENoiseFilter;
    Int_t Flag_HBHENoiseIsoFilter;
    Int_t Flag_EcalDeadCellTriggerPrimitiveFilter;
    Int_t Flag_BadPFMuonFilter;
    Int_t Flag_eeBadScFilter;
    Int_t HLT_PFHT450_SixJet40_BTagCSV_p056;
    Int_t HLT_PFHT400_SixJet30_DoubleBTagCSV_p056;
    Int_t HLT_PFJet450;
    Int_t HLT_IsoMu24;
    Int_t HLT_IsoMu27;
    Int_t HLT_PFJet500 = -99;
    Int_t HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = -99;
    Int_t HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = -99;
    Int_t HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = -99;
    Int_t HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 = -99;
    Int_t HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 = -99;
    // 2017
    Int_t HLT_PFHT430_SixJet40_BTagCSV_p080;
    Int_t HLT_PFHT380_SixJet32_DoubleBTagCSV_p075;
    Int_t HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2;

    Int_t PV_npvs;
    Int_t PV_npvsGood;

    Double_t EVENT_prefireWeight;
    Double_t EVENT_prefireWeight_up;
    Double_t EVENT_prefireWeight_down;
    Double_t EVENT_genWeight;
    Double_t PUweight_;
    Double_t PUweight_up_;
    Double_t PUweight_down_;
    Double_t btagEfficiency_weight;
    // Double_t HLTefficiency_weight;
    Double_t muonIDSF_weight;
    Double_t muonIDSF_weight_up;
    Double_t muonIDSF_weight_down;
    Double_t mounTrackerSF_weight;
    Double_t eleMVAT_IDSF_weight;
    Double_t eleMVAT_IDSF_weight_up;
    Double_t eleMVAT_IDSF_weight_down;
    Double_t eleMVAT_IDSF_weight_backup;
    Double_t elesTopMVAT_weight;
    Double_t elesTopMVAT_weight_up;
    Double_t elesTopMVAT_weight_down;
    Double_t musTopMVAT_weight;
    Double_t musTopMVAT_weight_up;
    Double_t musTopMVAT_weight_down;
    Double_t tauT_IDSF_weight;
    Double_t tauT_IDSF_weight_new;
    Double_t tauT_IDSF_weight_new_vsjet_up;
    Double_t tauT_IDSF_weight_new_vsjet_down;
    Double_t tauT_IDSF_weight_new_vsmu_up;
    Double_t tauT_IDSF_weight_new_vsmu_down;
    Double_t tauT_IDSF_weight_new_vsele_up;
    Double_t tauT_IDSF_weight_new_vsele_down;
    Double_t btagShape_weight = 1.0;

    Double_t btagShape_weight_jes_up = 1.0;
    Double_t btagShape_weight_jes_down = 1.0;
    Double_t btagShape_weight_hf_up = 1.0;
    Double_t btagShape_weight_hf_down = 1.0;
    Double_t btagShape_weight_lf_up = 1.0;
    Double_t btagShape_weight_lf_down = 1.0;
    Double_t btagShape_weight_hfstas1_up = 1.0;
    Double_t btagShape_weight_hfstas1_down = 1.0;
    Double_t btagShape_weight_hfstas2_up = 1.0;
    Double_t btagShape_weight_hfstas2_down = 1.0;
    Double_t btagShape_weight_lfstas1_up = 1.0;
    Double_t btagShape_weight_lfstas1_down = 1.0;
    Double_t btagShape_weight_lfstas2_up = 1.0;
    Double_t btagShape_weight_lfstas2_down = 1.0;
    Double_t btagShape_weight_cferr1_up = 1.0;
    Double_t btagShape_weight_cferr1_down = 1.0;

    Double_t btagShapeR = 1.0;
    Double_t HLT_weight = 1.0;
    Double_t HLT_weight_up = 1.0;
    Double_t HLT_weight_down = 1.0;

    Double_t MET_pt;
    Double_t MET_phi;
    Int_t muonsL_number;
    Int_t muonsF_number;
    Int_t muonsT_number;
    Double_t muonsT_1pt;
    Double_t muonsT_1eta;
    Double_t muonsT_1phi;
    Double_t muonsT_2pt;
    Double_t muonsT_2eta;
    Double_t muonsT_2phi;
    Double_t muonsT_3pt;
    Double_t muonsT_3eta;
    Double_t muonsT_3phi;
    Int_t elesMVAL_number;
    Int_t elesMVAF_number;
    Int_t elesMVAT_number;
    Double_t elesMVAF_1pt;
    Int_t leptonsMVAT_number;
    Int_t leptonsMVAF_number;
    Int_t leptonsMVAL_number;
    Double_t leptonsMVAT_transMass;
    Double_t leptonsMVAF_transMass;
    Double_t leptonsMVAL_transMass;
    Int_t leptonsMVAT_2SS;
    Int_t leptonsMVAT_2OS;
    Double_t leptonsMVAT_1pt = -99.0;
    Double_t leptonsMVAT_1eta = -99.0;
    Double_t leptonsMVAT_1phi = -99.0;

    Int_t elesTopMVAT_number = -99;
    Int_t muonsTopMVAT_number = -99;
    Int_t elesTopMVAL_number = -99;
    Int_t muonsTopMVAL_number = -99;
    Int_t muonsTopMVALPOG_number = -99;
    Int_t elesTopMVALPOG_number = -99;
    Int_t elesTopMVAVPOG_number = -99;
    Double_t elesTopMVAT_1pt = -99;
    Double_t elesTopMVAT_1eta = -99;
    Double_t elesTopMVAT_1phi = -99;
    Int_t elesTopMVAT_1char = -99;
    Double_t muonsTopMVAT_1pt = -99;
    Double_t muonsTopMVAT_1eta = -99;
    Double_t muonsTopMVAT_1phi = -99;
    Int_t muonsTopMVAT_1char = -99;

    Int_t tausT_number_TESup = -99;
    Int_t tausT_number_TESdown = -99;

    Int_t tausL_number = -99;
    Int_t tausF_number = -99;
    Int_t tausT_number = -99;
    Double_t tausL_MHT = -99.0;
    Double_t tausF_MHT = -99.0;
    Double_t tausT_MHT = -99.0;
    Double_t tausL_HT = -99.0;
    Double_t tausF_HT = -99.0;
    Double_t tausT_HT = -99.0;
    Double_t tausL_invariantMass = -99.0;
    Double_t tausF_invariantMass = -99.0;
    Double_t tausT_invariantMass = -99.0;
    Double_t tausF_minDeltaR = -99.0;
    Double_t tausL_minDeltaR = -99.0;
    Double_t tausT_minDeltaR = -99.0;
    Int_t tausT_genTauNum = 0;
    Int_t tausL_genTauNum = 0;
    Int_t tausF_genTauNum = -99;
    Double_t tausT_leptonsT_transMass = -99.0;
    Double_t tausF_leptonsT_invariantMass = -99.0;
    Double_t tausL_leptonsT_invariantMass = -99.0;
    Double_t tausT_leptonsT_invariantMass = -99.0;
    Int_t tausF_leptonsT_chargeSum = -99;
    Double_t tausF_leptonsTMVA_minDeltaR = -99.0;
    Double_t tausT_leptonsTMVA_minDeltaR = -99.0;
    Double_t tausL_leptonsTMVA_minDeltaR = -99.0;
    Int_t tausT_leptonsTMVA_chargeMulti = -99;
    Int_t tausT_leptonsTopMVA_chargeMulti = -99;
    Int_t tausT_prongNum = -99;
    Int_t tausL_prongNum = -99;
    Int_t tausF_prongNum = -99;

    Double_t tausT_1pt = -99.0;
    Double_t tausT_1eta = -99.0;
    Double_t tausT_1phi = -99.0;
    Double_t tausF_1pt = -99.0;
    Double_t tausF_1eta = -99.0;
    Double_t tausF_1phi = -99.0;
    Int_t tausL_1decayMode = -99;
    Int_t tausF_1decayMode = -99;
    Int_t tausT_1decayMode = -99;
    Double_t tausT_1jetPt = -99.0;
    Double_t tausF_1jetPt = -99.0;
    Double_t tausT_1jetEtaAbs = -99.0;
    Double_t tausF_1jetEtaAbs = -99.0;
    Int_t tausT_1charge = 0;
    Int_t tausF_1charge = 0;
    Double_t tausT_1neutralIso = -99.0;
    Double_t tausF_1neutralIso = -99.0;
    Double_t tausT_2pt = -99.0;
    Double_t tausT_2eta = -99.0;
    Double_t tausT_2phi = -99.0;
    Double_t tausT_3pt = -99.0;
    Double_t tausT_3eta = -99.0;
    Double_t tausT_3phi = -99.0;
    Double_t tausL_1pt = -99.0;
    Double_t tausL_1eta = -99.0;
    Double_t tausL_1etaAbs = -99.0;
    Double_t tausL_1phi = -99.0;

    //
    // Double_t ;
    // Double_t jets_HT_JECup = -99.0;
    // Double_t jets_HT_JECdown = -99.0;
    // Int_t jets_number_JECup = -99.;
    // Int_t jets_number_JECdown = -99;
    Int_t jets_number = -99;
    Double_t jets_MHT = -99.0;
    Double_t jets_HT = -99.0;
    Double_t jets_invariantMass = -99.0;
    Double_t jets_transMass = -99.0;
    Double_t jets_minDeltaR = -99.0;
    Double_t jets_centrality = -99.0;
    Double_t jets_bScore = -99.0;
    Double_t jets_bScoreMultiply = -99.0;
    Double_t jets_average_deltaR = -99.0;
    Double_t jets_4largestBscoreSum = -99.0;
    Double_t jets_4largestBscoreMulti = -99.0;
    Double_t jets_leading2invariantMass = -99.0;
    Double_t jets_rationHT_4toRest = -99.0;
    Double_t jets_HTDividedByMet = -99.0;
    Double_t MetDividedByHT = -99.0;
    Double_t jets_MHTDividedByMet = -99.0;
    Double_t jets_leptonsMVAT_minDeltaR = -99.0;
    Double_t jets_tausF_minDeltaR = -99.0;
    Double_t jets_tausT_minDeltaR = -99.0;
    Double_t jets_tausT_invariantMass = -99.0;
    // Double_t = -99.0;

    Double_t jets_spherilty = -99.0;
    Double_t jets_aplanarity = -99.0;
    Double_t jets_1pt = -99.0;
    Double_t jets_1phi = -99.0;
    Double_t jets_1btag = -99.0;
    Double_t jets_2btag = -99.0;
    Double_t jets_3btag = -99.0;
    Double_t jets_4btag = -99.0;
    Double_t jets_5btag = -99.0;
    Double_t jets_6btag = -99.0;
    Double_t jets_7btag = -99.0;
    Double_t jets_1eta = -99.0;
    Double_t jets_2pt = -99.0;
    Double_t jets_2eta = -99.0;
    Double_t jets_2phi = -99.0;
    Double_t jets_3pt = -99.0;
    Double_t jets_3eta = -99.0;
    Double_t jets_3phi = -99.0;
    Double_t jets_4pt = -99.0;
    Double_t jets_4eta = -99.0;
    Double_t jets_4phi = -99.0;
    Double_t jets_5pt = -99.0;
    Double_t jets_5eta = -99.0;
    Double_t jets_5phi = -99.0;
    Double_t jets_6pt = -99.0;
    Double_t jets_6eta = -99.0;
    Double_t jets_6phi = -99.0;
    Double_t jets_7pt = -99.0;
    Double_t jets_7eta = -99.0;
    Double_t jets_7phi = -99.0;
    Double_t jets_8pt = -99.0;
    Double_t jets_8eta = -99.0;
    Double_t jets_8phi = -99.0;
    Double_t jets_9pt = -99.0;
    Double_t jets_9eta = -99.0;
    Double_t jets_9phi = -99.0;
    Double_t jets_10pt = -99.0;
    Double_t jets_10eta = -99.0;
    Double_t jets_10phi = -99.0;
    Double_t jets_11pt = -99.0;
    Double_t jets_11eta = -99.0;
    Double_t jets_11phi = -99.0;

    Int_t jetsT_num = -99;
    Double_t jetsT_1pt = -99.0;
    Double_t jetsT_1phi = -99.0;
    Double_t jetsT_1eta = -99.0;
    Double_t jetsT_2pt = -99.0;
    Double_t jetsT_2eta = -99.0;
    Double_t jetsT_2phi = -99.0;
    Double_t jetsT_3pt = -99.0;
    Double_t jetsT_3eta = -99.0;
    Double_t jetsT_3phi = -99.0;
    Double_t jetsT_4pt = -99.0;
    Double_t jetsT_4eta = -99.0;
    Double_t jetsT_4phi = -99.0;
    Double_t jetsT_5pt = -99.0;
    Double_t jetsT_5eta = -99.0;
    Double_t jetsT_5phi = -99.0;
    Double_t jetsT_6pt = -99.0;
    Double_t jetsT_6eta = -99.0;
    Double_t jetsT_6phi = -99.0;
    Double_t jetsT_7pt = -99.0;
    Double_t jetsT_7eta = -99.0;
    Double_t jetsT_7phi = -99.0;
    Double_t jetsT_8pt = -99.0;
    Double_t jetsT_8eta = -99.0;
    Double_t jetsT_8phi = -99.0;
    Double_t jetsT_9pt = -99.0;
    Double_t jetsT_9eta = -99.0;
    Double_t jetsT_9phi = -99.0;
    Double_t jetsT_10pt = -99.0;
    Double_t jetsT_10eta = -99.0;
    Double_t jetsT_10phi = -99.0;

    Int_t bjetsL_num = -99;
    Int_t bjetsM_num = -99;
    Int_t bjetsT_num = -99;
    Double_t bjetsL_HT = -99.0;
    Double_t bjetsM_HT = -99.0;
    Double_t bjetsT_HT = -99.0;
    Double_t bjetsL_MHT = -99.0;
    Double_t bjetsM_MHT = -99.0;
    Double_t bjetsT_MHT = -99.0;
    Double_t bjetsL_invariantMass = -99.0;
    Double_t bjetsM_invariantMass = -99.0;
    Double_t bjetsT_invariantMass = -99.0;
    Double_t bjetsL_transMass = -99.0;
    Double_t bjetsM_transMass = -99.0;
    Double_t bjetsT_transMass = -99.0;
    Double_t bjetsL_minDeltaR = 0;
    Double_t bjetsM_minDeltaR = 0;
    Double_t bjetsT_minDeltaR = 0;
    Double_t bjetsL_leptonsMVAT_minDeltaR = -99.0;
    Double_t bjetsM_leptonsMVAT_minDeltaR = -99.0;
    Double_t bjetsT_leptonsMVAT_minDeltaR = -99.0;
    Double_t bjetsL_tausF_minDeltaR = -99.0;
    Double_t bjetsL_1pt = -99.0;
    Double_t bjetsL_1eta = -99.0;
    Double_t bjetsL_1phi = -99.0;
    Double_t bjetsL_2pt = -99.0;
    Double_t bjetsL_2eta = -99.0;
    Double_t bjetsL_2phi = -99.0;
    Double_t bjetsL_4pt = -99.0;
    Double_t bjetsL_4eta = -99.0;
    Double_t bjetsL_4phi = -99.0;
    Double_t bjetsL_3pt = -99.0;
    Double_t bjetsL_3eta = -99.0;
    Double_t bjetsL_3phi = -99.0;
    Double_t bjetsM_1pt = -99.0;
    Double_t bjetsM_1eta = -99.0;
    Double_t bjetsM_1phi = -99.0;
    Double_t bjetsM_1btag = -99.0;
    Double_t bjetsM_2btag = -99.0;
    Double_t bjetsM_3btag = -99.0;
    Double_t bjetsM_2pt = -99.0;
    Double_t bjetsM_2eta = -99.0;
    Double_t bjetsM_2phi = -99.0;
    Double_t bjetsM_4pt = -99.0;
    Double_t bjetsM_4eta = -99.0;
    Double_t bjetsM_4phi = -99.0;
    Double_t bjetsM_3pt = -99.0;
    Double_t bjetsM_3eta = -99.0;
    Double_t bjetsM_3phi = -99.0;
    Double_t bjetsT_1pt = -99.0;
    Double_t bjetsT_1eta = -99.0;
    Double_t bjetsT_1phi = -99.0;
    Double_t bjetsT_2pt = -99.0;
    Double_t bjetsT_2eta = -99.0;
    Double_t bjetsT_2phi = -99.0;
    Double_t bjetsT_3pt = -99.0;
    Double_t bjetsT_3eta = -99.0;
    Double_t bjetsT_3phi = -99.0;
    Double_t bjetsT_4pt = -99.0;
    Double_t bjetsT_4eta = -99.0;
    Double_t bjetsT_4phi = -99.0;

    // Int_t nonbjetsL_num = -99;
    Int_t nonbjetsM_num = -99;
    // Int_t nonbjetsT_num = -99;
    // Double_t nonbjetsL_1pt = -99;
    // Double_t nonbjetsL_1eta = -99;
    // Double_t nonbjetsL_1phi = -99;
    // Double_t nonbjetsL_2pt = -99;
    // Double_t nonbjetsL_2eta = -99;
    // Double_t nonbjetsL_2phi = -99;
    // Double_t nonbjetsL_4pt = -99;
    // Double_t nonbjetsL_4eta = -99;
    // Double_t nonbjetsL_4phi = -99;
    // Double_t nonbjetsL_3pt = -99;
    // Double_t nonbjetsL_3eta = -99;
    // Double_t nonbjetsL_3phi = -99;
    // Double_t nonbjetsM_1pt = -99;
    // Double_t nonbjetsM_1eta = -99;
    // Double_t nonbjetsM_1phi = -99;
    // Double_t nonbjetsM_2pt = -99;
    // Double_t nonbjetsM_2eta = -99;
    // Double_t nonbjetsM_2phi = -99;
    // Double_t nonbjetsM_4pt = -99;
    // Double_t nonbjetsM_4eta = -99;
    // Double_t nonbjetsM_4phi = -99;
    // Double_t nonbjetsM_3pt = -99;
    // Double_t nonbjetsM_3eta = -99;
    // Double_t nonbjetsM_3phi = -99;
    // Double_t nonbjetsT_1pt = -99;
    // Double_t nonbjetsT_1eta = -99;
    // Double_t nonbjetsT_1phi = -99;
    // Double_t nonbjetsT_2pt = -99;
    // Double_t nonbjetsT_2eta = -99;
    // Double_t nonbjetsT_2phi = -99;
    // Double_t nonbjetsT_3pt = -99;
    // Double_t nonbjetsT_3eta = -99;
    // Double_t nonbjetsT_3phi = -99;
    // Double_t nonbjetsT_4pt = -99;
    // Double_t nonbjetsT_4eta = -99;
    // Double_t nonbjetsT_4phi = -99;

    Int_t forwardJets_num = -99;
    Int_t genBs_num = -99;
    std::vector<Int_t> GenPart_genPartIdxMother;
    std::vector<Int_t> GenPart_pdgId;

    Int_t toptagger_num = -99;
    Double_t toptagger_MHT = -99.0;
    Double_t toptagger_HT = -99.0;
    Double_t toptagger_invariantMass = -99.0;
    Double_t toptagger_transMass = -99.0;
    Double_t toptagger_minDeltaR_v1 = -99.0;

    Double_t toptagger_1pt = -99.0;
    Double_t toptagger_1eta = -99.0;
    Double_t toptagger_1phi = -99.0;
    Double_t toptagger_2pt = -99.0;
    Double_t toptagger_2eta = -99.0;
    Double_t toptagger_2phi = -99.0;
    Double_t toptagger_3pt = -99.0;
    Double_t toptagger_3eta = -99.0;
    Double_t toptagger_3phi = -99.0;
    Double_t toptagger_scoreAllTops = 99;
    Double_t toptagger_leptonsMVAT_minDeltaR = -99.0;

    TTreeReaderValue<ULong64_t> event_ = {fReader, "event_"};
    TTreeReaderValue<Int_t> Flag_goodVertices_ = {fReader, "Flag_goodVertices_"};
    TTreeReaderValue<Int_t> Flag_globalSuperTightHalo2016Filter_ = {fReader, "Flag_globalSuperTightHalo2016Filter_"};
    TTreeReaderValue<Int_t> Flag_HBHENoiseFilter_ = {fReader, "Flag_HBHENoiseFilter_"};
    TTreeReaderValue<Int_t> Flag_HBHENoiseIsoFilter_ = {fReader, "Flag_HBHENoiseIsoFilter_"};
    TTreeReaderValue<Int_t> Flag_EcalDeadCellTriggerPrimitiveFilter_ = {fReader, "Flag_EcalDeadCellTriggerPrimitiveFilter_"};
    TTreeReaderValue<Int_t> Flag_BadPFMuonFilter_ = {fReader, "Flag_BadPFMuonFilter_"};
    TTreeReaderValue<Int_t> Flag_BadPFMuonDzFilter_ = {fReader, "Flag_BadPFMuonDzFilter_"};
    TTreeReaderValue<Int_t> Flag_ecalBadCalibFilter_ = {fReader, "Flag_ecalBadCalibFilter_"};
    TTreeReaderValue<Int_t> Flag_eeBadScFilter_ = {fReader, "Flag_eeBadScFilter_"};
    TTreeReaderValue<Int_t> HLT_PFHT450_SixJet40_BTagCSV_p056_ = {fReader, "HLT_PFHT450_SixJet40_BTagCSV_p056_"};
    TTreeReaderValue<Int_t> HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ = {fReader, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_"};
    TTreeReaderValue<Int_t> HLT_PFJet450_ = {fReader, "HLT_PFJet450_"};
    TTreeReaderValue<Int_t> HLT_PFJet500_ = {fReader, "HLT_PFJet500_"};
    TTreeReaderValue<Int_t> HLT_IsoMu24_ = {fReader, "HLT_IsoMu24_"};
    TTreeReaderValue<Int_t> HLT_IsoMu27_ = {fReader, "HLT_IsoMu27_"};
    // 2018
    TTreeReaderValue<Int_t> HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ = {fReader, "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_"};
    TTreeReaderValue<Int_t> HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = {fReader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_"};
    TTreeReaderValue<Int_t> HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_ = {fReader, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_"};
    TTreeReaderValue<Int_t> HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = {fReader, "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_"};
    TTreeReaderValue<Int_t> HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ = {fReader, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_"};
    // 2017
    TTreeReaderValue<Int_t> HLT_PFHT430_SixJet40_BTagCSV_p080_ = {fReader, "HLT_PFHT430_SixJet40_BTagCSV_p080_"};
    TTreeReaderValue<Int_t> HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_ = {fReader, "HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_"};
    TTreeReaderValue<Int_t> HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_ = {fReader, "HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_"};

    // Readers to access the data (delete the ones you do not need).
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> muonsL = {fReader, "muonsL"};
    // TTreeReaderArray<Int_t> muonsL_index = {fReader, "muonsL_index"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> muonsF = {fReader, "muonsF"};
    // TTreeReaderArray<Int_t> muonsF_index = {fReader, "muonsF_index"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> muonsT = {fReader, "muonsT"};
    TTreeReaderArray<Int_t> muonsT_index = {fReader, "muonsT_index"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> eleMVAL = {fReader, "eleMVAL"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> eleMVAF = {fReader, "eleMVAF"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> eleMVAT = {fReader, "eleMVAT"};
    // TTreeReaderArray<Int_t> eleMVAL_index = {fReader, "eleMVAL_index"};
    // TTreeReaderArray<Int_t> eleMVAF_index = {fReader, "eleMVAF_index"};
    TTreeReaderArray<Int_t> eleMVAT_index = {fReader, "eleMVAT_index"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> leptonsMVAF = {fReader, "leptonsMVAF"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> leptonsMVAT = {fReader, "leptonsMVAT"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> leptonsMVAL = {fReader, "leptonsMVAL"};

    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> elesTopMVAT = {fReader, "elesTopMVAT"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> muonsTopMVAT = {fReader, "muonsTopMVAT"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> elesTopMVAL = {fReader, "elesTopMVAL"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> muonsTopMVAL = {fReader, "muonsTopMVAL"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> muonsTopMVALPOG = {fReader, "muonsTopMVALPOG"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> elesTopMVALPOG = {fReader, "elesTopMVALPOG"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> elesTopMVAVPOG = {fReader, "elesTopMVAVPOG"};
    TTreeReaderArray<Int_t> elesTopMVAT_index = {fReader, "elesTopMVAT_index"};
    TTreeReaderArray<Int_t> muonsTopMVAT_index = {fReader, "muonsTopMVAT_index"};
    // TTreeReaderArray<Int_t>  = {fReader, ""};
    // TTreeReaderArray<Int_t>  = {fReader, ""};
    // TTreeReaderArray<Int_t>  = {fReader, ""};

    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> tausL = {fReader, "tausL"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> tausF = {fReader, "tausF"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> tausT = {fReader, "tausT"};
    TTreeReaderArray<Int_t> tausT_decayMode = {fReader, "tausT_decayMode"};
    TTreeReaderArray<Int_t> tausL_decayMode = {fReader, "tausL_decayMode"};
    TTreeReaderArray<Int_t> tausF_decayMode = {fReader, "tausF_decayMode"};
    TTreeReaderArray<Int_t> tausT_genPartFlav = {fReader, "tausT_genPartFlav"};
    TTreeReaderArray<Int_t> tausL_genPartFlav = {fReader, "tausL_genPartFlav"};
    TTreeReaderArray<Int_t> tausF_genPartFlav = {fReader, "tausF_genPartFlav"};
    TTreeReaderArray<Double_t> tausT_jetPt = {fReader, "tausT_jetPt"};
    TTreeReaderArray<Double_t> tausF_jetPt = {fReader, "tausF_jetPt"};
    TTreeReaderArray<Double_t> tausT_jetEta = {fReader, "tausT_jetEta"};
    TTreeReaderArray<Double_t> tausF_jetEta = {fReader, "tausF_jetEta"};
    TTreeReaderArray<Int_t> tausT_charge = {fReader, "tausT_charge"};
    TTreeReaderArray<Int_t> tausF_charge = {fReader, "tausF_charge"};
    TTreeReaderArray<Double_t> tausT_neutralIso = {fReader, "tausT_neutralIso"};
    TTreeReaderArray<Double_t> tausF_neutralIso = {fReader, "tausF_neutralIso"};

    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> jets = {fReader, "jets"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> jetsT = {fReader, "jetsT"};
    TTreeReaderArray<Int_t> jets_index = {fReader, "jets_index"};
    TTreeReaderArray<Int_t> jets_flavour = {fReader, "jets_flavour"};
    TTreeReaderArray<Double_t> jets_btags = {fReader, "jets_btags"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> jets_JECup = {fReader, "jets_JECup"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> jets_JECdown = {fReader, "jets_JECdown"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> bjetsL = {fReader, "bjetsL"};
    // TTreeReaderArray<Int_t> bjetsL_index = {fReader, "bjetsL_index"};
    // TTreeReaderArray<Double_t> bjetsL_btags = {fReader, "bjetsL_btags"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> bjetsM = {fReader, "bjetsM"};
    TTreeReaderArray<Int_t> bjetsM_index = {fReader, "bjetsM_index"};
    TTreeReaderArray<Double_t> bjetsM_btags = {fReader, "bjetsM_btags"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> bjetsT = {fReader, "bjetsT"};
    // TTreeReaderArray<Int_t> bjetsT_index = {fReader, "bjetsT_index"};
    // TTreeReaderArray<Double_t> bjetsT_btags = {fReader, "bjetsT_btags"};
    // TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> nonbjetsT = {fReader, "nonbjetsT"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> nonbjetsM = {fReader, "nonbjetsM"};
    // TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> nonbjetsL = {fReader, "nonbjetsL"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> forwardJets = {fReader, "forwardJets"};
    // TTreeReaderArray<Int_t> forwardJets_index = {fReader, "forwardJets_index"};
    // TTreeReaderArray<Double_t> forwardJets_btags = {fReader, "forwardJets_btags"};
    TTreeReaderArray<Int_t> patElectron_charge_ = {fReader, "patElectron_charge_"};
    // TTreeReaderArray<Double_t> Tau_charge_ = {fReader, "Tau_charge_"};
    TTreeReaderArray<Int_t> Muon_charge_ = {fReader, "Muon_charge_"};
    // TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> genTaus = {fReader, "genTaus"};
    // TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> genEles = {fReader, "genEles"};
    // TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> genMuons = {fReader, "genMuons"};
    TTreeReaderValue<Double_t> MET_pt_ = {fReader, "MET_pt_"};
    TTreeReaderValue<Double_t> MET_phi_ = {fReader, "MET_phi_"};
    TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> genBs = {fReader, "genBs"};
    TTreeReaderArray<Int_t> GenPart_genPartIdxMother_ = {fReader, "GenPart_genPartIdxMother_"};
    TTreeReaderArray<Int_t> GenPart_pdgId_ = {fReader, "GenPart_pdgId_"};

    TTreeReaderValue<Double_t> EVENT_prefireWeight_ = {fReader, "EVENT_prefireWeight_"};
    TTreeReaderValue<Double_t> EVENT_prefireWeight_up_ = {fReader, "EVENT_prefireWeight_up_"};
    TTreeReaderValue<Double_t> EVENT_prefireWeight_down_ = {fReader, "EVENT_prefireWeight_down_"};
    TTreeReaderValue<Double_t> EVENT_genWeight_ = {fReader, "EVENT_genWeight_"};
    TTreeReaderValue<Double_t> PUWeight = {fReader, "PUWeight"};
    TTreeReaderValue<Double_t> PUWeight_Down = {fReader, "PUWeight_Down"};
    TTreeReaderValue<Double_t> PUWeight_Up = {fReader, "PUWeight_Up"};
    TTreeReaderValue<Int_t> PV_npvs_ = {fReader, "PV_npvs_"};         // total number of reconstructed primary vertices
    TTreeReaderValue<Int_t> PV_npvsGood_ = {fReader, "PV_npvsGood_"}; // total number of reconstructed primary vertices
    // TTreeReaderValue<Double_t>  = {fReader, ""};

    // TTreeReaderValue<Int_t> HLT_PFHT450_SixJet40_BTagCSV_p056_ = {fReader, "HLT_PFHT450_SixJet40_BTagCSV_p056_"};
    // TTreeReaderValue<Int_t> HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ = {fReader, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_"};
    // TTreeReaderValue<Int_t> HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_ = {fReader, "HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_"};
    // TTreeReaderValue<Int_t> HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_ = {fReader, "HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_"};
    // TTreeReaderValue<Int_t> HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_ = {fReader, "HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_"};
    // TTreeReaderValue<Int_t> HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_ = {fReader, "HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_"};
    // TTreeReaderValue<Int_t> HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_ = {fReader, "HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_"};
    // TTreeReaderValue<Int_t> HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_ = {fReader, "HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_"};
    // TTreeReaderValue<Int_t> HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_ = {fReader, "HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_"};
    // TTreeReaderValue<Int_t> HLT_Ele27_eta2p1_WPTight_Gsf_ = {fReader, "HLT_Ele27_eta2p1_WPTight_Gsf_"};
    // TTreeReaderValue<Int_t> HLT_Ele27_eta2p1_WPLoose_Gsf_ = {fReader, "HLT_Ele27_eta2p1_WPLoose_Gsf_"};
    // TTreeReaderValue<Int_t> HLT_Ele27_WPTight_Gsf_ = {fReader, "HLT_Ele27_WPTight_Gsf_"};
    // TTreeReaderValue<Int_t> HLT_IsoMu22_ = {fReader, "HLT_IsoMu22_"};
    // TTreeReaderValue<Int_t> HLT_Ele25_eta2p1_WPTight_Gsf_ = {fReader, "HLT_Ele25_eta2p1_WPTight_Gsf_"};
    // TTreeReaderValue<Int_t> HLT_IsoTkMu22_ = {fReader, "HLT_IsoTkMu22_"};
    // TTreeReaderValue<Int_t> HLT_IsoMu24_ = {fReader, "HLT_IsoMu24_"};
    // TTreeReaderValue<Int_t> HLT_IsoTkMu24_ = {fReader, "HLT_IsoTkMu24_"};
    // TTreeReaderValue<Int_t> HLT_IsoMu22_eta2p1_ = {fReader, "HLT_IsoMu22_eta2p1_"};
    // TTreeReaderValue<Int_t> HLT_IsoTkMu22_eta2p1_ = {fReader, "HLT_IsoTkMu22_eta2p1_"};
    // TTreeReaderValue<Int_t> HLT_Mu50_ = {fReader, "HLT_Mu50_"};
    // TTreeReaderValue<Int_t> HLT_TkMu50_ = {fReader, "HLT_TkMu50_"};
    // TTreeReaderValue<Int_t> HLT_Ele32_WPTight_Gsf_ = {fReader, "HLT_Ele32_WPTight_Gsf_"};
    // TTreeReaderValue<Int_t> HLT_Ele35_WPTight_Gsf_ = {fReader, "HLT_Ele35_WPTight_Gsf_"};
    // TTreeReaderValue<Int_t> HLT_IsoMu27_ = {fReader, "HLT_IsoMu27_"};
    // TTreeReaderValue<Int_t> HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_ = {fReader, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_"};
    // TTreeReaderValue<Int_t> HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_ = {fReader, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_"};
    // TTreeReaderValue<Int_t> HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_ = {fReader, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_"};
    // TTreeReaderValue<Int_t> HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_ = {fReader, "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_"};
    // TTreeReaderValue<Int_t> HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_ = {fReader, "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_"};
    // TTreeReaderValue<Int_t> HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_ = {fReader, "HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_"};
    // TTreeReaderValue<Int_t> HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_ = {fReader, "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_"};
    // TTreeReaderValue<Int_t> HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_ = {fReader, "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_"};
    // TTreeReaderValue<Int_t> HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_ = {fReader, "HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_"};
    // TTreeReaderValue<Int_t> HLT_DoubleEle33_CaloIdL_MW_ = {fReader, "HLT_DoubleEle33_CaloIdL_MW_"};
    // TTreeReaderValue<Int_t> HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_ = {fReader, "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_"};
    // TTreeReaderValue<Int_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_"};
    // TTreeReaderValue<Int_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_"};
    // TTreeReaderValue<Int_t> HLT_DoubleMu33NoFiltersNoVtx_ = {fReader, "HLT_DoubleMu33NoFiltersNoVtx_"};
    // TTreeReaderValue<Int_t> HLT_DoubleMu23NoFiltersNoVtxDisplaced_ = {fReader, "HLT_DoubleMu23NoFiltersNoVtxDisplaced_"};
    // TTreeReaderValue<Int_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_ = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_"};
    // TTreeReaderValue<Int_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_"};
    // TTreeReaderValue<Int_t> HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_ = {fReader, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_"};
    // TTreeReaderValue<Int_t> HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_ = {fReader, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_"};
    // TTreeReaderValue<Int_t> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_ = {fReader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_"};
    // TTreeReaderValue<Int_t> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_ = {fReader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_"};
    // TTreeReaderValue<Int_t> HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_ = {fReader, "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_"};
    // TTreeReaderValue<Int_t> HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_ = {fReader, "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_"};
    // TTreeReaderValue<Int_t> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_ = {fReader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_"};
    // TTreeReaderValue<Int_t> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ = {fReader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_"};
    // TTreeReaderValue<Int_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_ = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_"};
    // TTreeReaderValue<Int_t> HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_ = {fReader, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_"};
    // TTreeReaderValue<Int_t> HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_ = {fReader, "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_"};
    // TTreeReaderValue<Int_t> HLT_Mu8_DiEle12_CaloIdL_TrackIdL_ = {fReader, "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_"};
    // TTreeReaderValue<Int_t> HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_ = {fReader, "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_"};
    // TTreeReaderValue<Int_t> HLT_TripleMu_12_10_5_ = {fReader, "HLT_TripleMu_12_10_5_"};
    // TTreeReaderValue<Int_t> HLT_DiMu9_Ele9_CaloIdL_TrackIdL_ = {fReader, "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_"};

    makeVaribles_forBDT(TTree * /*tree*/ = 0) {}
    virtual ~makeVaribles_forBDT() {}
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
    void InitializeBranches();
    void initializeBReader();
    ;
    void makeBranchForTree();
    void initializeInputFiles(const TString era);
    ClassDef(makeVaribles_forBDT, 0);
};

#endif

#ifdef makeVaribles_forBDT_cxx
void makeVaribles_forBDT::Init(TTree *tree)
{
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the reader is initialized.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    fReader.SetTree(tree);
}

Bool_t makeVaribles_forBDT::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

#endif // #ifdef makeVaribles_forBDT_cxx
