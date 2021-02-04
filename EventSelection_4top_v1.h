//#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
//#include "CondFormats/BTauObjects/interface/BTagCalibrationReader.h"
#include "TBranch.h"
#include "TTree.h"
#include "TFile.h"
#include "TStyle.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TChain.h"
#include <iostream>


//BTagCalibration not working in 102
//void branch(bool data,int selecton, TTree *NewTree, TTree *NewTreeSB, string fileName);
void branch(bool data,int selecton, TTree *NewTree, TTree *NewTreeSB, TChain &chain );
/*{{{*/
void SelectMet(bool &SelectedMet);
void selectGenTaus( vector<TLorentzVector> &genTaus );
void selectGenEles( vector<TLorentzVector> &genEles );
void selectGenMuons( vector<TLorentzVector> &genMuons );
void SelectElectrons(vector<TLorentzVector> & SelectedElectrons, vector<int> & SelectedElectronsIndex, int type);
void SelectElectronsMVA(vector<TLorentzVector> & SelectedElectrons, vector<int> & SelectedElectronsIndex, int type, int stage);
void SelectMuons(vector<TLorentzVector> & SelectedMuons, vector<int> & SelectedMuonsIndex, int type, int stage);
void SelectTaus(vector<TLorentzVector>& SelectedTaus,vector<int> & SelectedTausIndex,const Int_t TauWP, const vector<TLorentzVector> LeptonsMVAL);
void SelectZBoson(bool electrons,bool muons ,bool &SelectedZBoson,TLorentzVector &ZBoson,TLorentzVector &Lep1,TLorentzVector &Lep2,vector<TLorentzVector> SelectedLeptons,vector<int> SelectedLeptonsIndex,double dRLep1Lep2,double Zpt,double leadLepPt);
//void SelectJets(int jetType,vector<TLorentzVector> & SelectedJets, vector<double> & SelectedJetsCSV, vector<TLorentzVector> SelectedElectrons, vector<TLorentzVector> SelectedMuons,
//		int SysJes, int SysJer, bool data, bool &deltaPhiJetMet);
void SelectJets(const int jetType,const bool deepJet,  vector<TLorentzVector> & SelectedJets, vector<double> & SeclectedJetsBTags, vector<int> &SelectedJetsIndex, const int SysJes, const int SysJer, const vector<TLorentzVector> LeptonsMVAF, const vector<TLorentzVector> SelectedTausL  /*,  bool  &deltaPhiJetMet*/);
void SelectCA8Jets(int CA8jetType, vector<TLorentzVector> & SelectedWJets, vector<TLorentzVector> SelectedElectrons, vector<TLorentzVector> SelectedMuons, vector<int> & CA8Indices,
		int SysJes, int SysJer, bool data, bool &deltaPhiJetMet);
void ResolvedRegionSelection(bool &ResolvedEvent,vector<TLorentzVector> SelectedJets,vector<double> SelectedJetsCSV,TLorentzVector &TopQuark,
			     TLorentzVector &Jet1,TLorentzVector &Jet2,TLorentzVector &Jet3,bool TopMassCut,bool btag);
void PartiallyMergedSelection(bool &PartiallyMerged,vector<TLorentzVector> SelectedWJets,vector<TLorentzVector> SelectedJets,vector<double> SelectedJetsCSV,TLorentzVector &TopQuark,
			      TLorentzVector &Jet1,TLorentzVector &Jet2,bool TopMassCut,bool btag,vector<int> CA8Indices,int & CA8Index,double &WMass_,double &WSubjet_, bool data);
void FullyMergedSelection(bool & FullyMerged, vector<TLorentzVector> SelectedTopJets, TLorentzVector &TopQuark,vector<int> CA8Indices,double &TopSoftMass_,double &TopSubjet_, bool data);
//void BTagSF(double JetPt, double JetEta, int flav, double &SF, double &SFerr);
void get_weight_btag(int selection, double &w_Btag, double &w_BtagUp, double &w_BtagDown, double &w_Btag1Up, double &w_Btag1Down, double &w_Btag2Up, double &w_Btag2Down, double &w_BtagLoose, double &w_BtagLooseUp, double &w_BtagLooseDown, string fileName);
void WSF(TLorentzVector WJet, bool PartiallyMerged, double &w_WJet_, double &w_WJetUp_, double &w_WJetDown_, int CA8Index, int SysJes, int SysJer);
void TopSF(TLorentzVector SelectedTopJets, bool FullyMerged, double &w_topJet_, double &w_topJetUp_, double &w_topJetDown_);
void ForwardJetSF(vector<TLorentzVector> SelectedForwardJets, double &w_for_, double &w_forUp_, double &w_forDown_);
void MuonSF(bool SelectedZBosonMuons, double pt, double eta, double &w_Muon_, double &w_MuonUp_, double &w_MuonDown_);
void ElectronSF(bool SelectedZBosonElectrons, double pt, double eta, double &w_Electron_, double &w_ElectronUp_, double &w_ElectronDown_);
void MuonTriggerSF(double pt, double eta);
void ElectronTriggerSF(double pt, double eta);

double DeltaR(double eta1, double eta2, double phi1, double phi2);
double deltRmin(const double eta1, const double phi1, const vector<TLorentzVector> LeptonsMVAF);
double DeltaPhi(double phi1, double phi2);
double HTcalculator(vector<TLorentzVector> SelectedJets);
double MHTcalculator(vector<TLorentzVector> SelectedJets);
double rationHT_4toRestCal(vector<TLorentzVector> SelectedJets);
bool compEle(const TLorentzVector a , const  TLorentzVector b);
//
double InvariantMassLike_Calculator(vector<TLorentzVector> SelectedJets);
double InvariantMassCalculator(vector<TLorentzVector> SelectedJets);
double InvariantMass2SysCal(const vector<TLorentzVector> a, const vector<TLorentzVector> b);
int ChargeSum(const vector<int> SelectedElectronsMVATIndex, int type);
double TransEnergyCal(const TLorentzVector SelectedJets);
double TransEnergySysCal(const vector<TLorentzVector> SelectedJets);
 double TransMassCal(const vector<TLorentzVector> SelectedJets);
 double TransMassSysCal(const vector<TLorentzVector> Jets, const vector<TLorentzVector> Leptons);
 double MinDeltaRCal(const vector<TLorentzVector> Jets, const vector<TLorentzVector> Leptons);
 double MinDeltaRSingleCal(const vector<TLorentzVector> Jets);
double AplanarityCalculator(vector<TLorentzVector> SelectedJets);
double LeadingJetPtCal(vector<TLorentzVector> SelectedJets);
double deltaRJetsCal(vector<TLorentzVector> SelectedJets);
void sort_jetPt(const vector<TLorentzVector> SelectedJets,vector<double> &JetsPtSorted);
void AddTwoVectors(const vector<TLorentzVector> SelectedMuonsT, const vector<TLorentzVector> SelectedElectronsMVAT,  vector<TLorentzVector> & SelectedLeptonsMVAT);
void FindLeadingToThirdPtIndex(const vector<TLorentzVector> SelectedJets,const vector<double> JetsPtSorted, Int_t &LeadingPtIndex, Int_t     &SecondPtIndex, Int_t &ThirdPtIndex);
double BScoreAllJetsCal(vector<double> SeclectedJetsBTags);
double bscoreSumOf4largestCal(const vector<double> SelectedJetsBTags) ;
void MinMaxdeltaRJetsCal(vector<TLorentzVector> SelectedJets,vector<double>& MinMaxDeltaR);
double AverageDeltaRCal(const vector<TLorentzVector> SelectedJets);
void MinMaxDeltaPhiCal(vector<TLorentzVector> SelectedJets,vector<double> &MinMaxDeltaPhi);
 double MinDeltaEtaCal(const TLorentzVector jets,const vector<TLorentzVector> SelectedJets);
void SelectTops(vector<TLorentzVector> & SelectedTops);
double TopScoreAllTopsCal(const vector<TLorentzVector>  SelectedTops);
////
//
void branchGetEntry(bool data, Long64_t tentry);
void HistoFill(double pileupReweight,TTree *NewTree);
void writeFile(TTree *NewTree,TTree *NewTreeSB);
void initializeVar();
void fillgenWeights();
void GenClassifier(double &GenZPt_,double &GenWPt_);
void GenWBoson(bool &matched, TLorentzVector Wjet);
void GenWeight(string fileName, double GenZPt_,double GenWPt_);
//void newPUWeight(double &puweight,double &puweightUP,double &puweightDOWN);
void WriteTopRelatedBranches(bool ResolvedEvent,TLorentzVector TopQuark,bool SelectedMet,TLorentzVector TopQuarkResolved,TLorentzVector Jet1Resolved,TLorentzVector Jet2Resolved,TLorentzVector Jet3Resolved,vector<TLorentzVector> SelectedForwardJets,vector<TLorentzVector> SelectedBJets);
void HTSF(string fileName, double HT, double Met_pt, double &w_SF1, double &w_SF1Up, double &w_SF1Down, double &w_SF2, double &w_SF2Up, double &w_SF2Down, double &w_SF3, double &w_SF3Up, double &w_SF3Down);
void TriggerSF(double HT, double jetsL_MHT, double &w_Trig, double &w_TrigUp, double &w_TrigDown);
void QCDWeight(int imin,int imax,double &w_QCDUp ,double &w_QCDDown);
void PDFWeight(int imin,int imax,double &w_PDFUp ,double &w_PDFDown);
void MetCorrection(int SysJes, int SysJer, double &MET);/*}}}*/
//BTAG SF
//???what does this do?
/*
BTagCalibration calib("CSVv2", "SF_dineutrino/DeepCSV_94XSF_V2_B_F.csv");
  //BTagCalibration calib("DeepCSV", "SF_dineutrino/DeepCSV_94XSF_V2_B_F.csv");
BTagCalibrationReader readerTIncl(&calib,      BTagEntry::OP_TIGHT, "incl",   "central");
BTagCalibrationReader readerTIncl_up(&calib,   BTagEntry::OP_TIGHT, "incl",   "up");
BTagCalibrationReader readerTIncl_do(&calib,   BTagEntry::OP_TIGHT, "incl",   "down");
BTagCalibrationReader readerTComb(&calib,    BTagEntry::OP_TIGHT, "comb", "central");
BTagCalibrationReader readerTComb_up(&calib, BTagEntry::OP_TIGHT, "comb", "up");
BTagCalibrationReader readerTComb_do(&calib, BTagEntry::OP_TIGHT, "comb", "down");
BTagCalibrationReader readerMIncl(&calib,      BTagEntry::OP_MEDIUM, "incl",   "central");
BTagCalibrationReader readerMIncl_up(&calib,   BTagEntry::OP_MEDIUM, "incl",   "up");
BTagCalibrationReader readerMIncl_do(&calib,   BTagEntry::OP_MEDIUM, "incl",   "down");
BTagCalibrationReader readerMComb(&calib,    BTagEntry::OP_MEDIUM, "comb", "central");
BTagCalibrationReader readerMComb_up(&calib, BTagEntry::OP_MEDIUM, "comb", "up");
BTagCalibrationReader readerMComb_do(&calib, BTagEntry::OP_MEDIUM, "comb", "down");
BTagCalibrationReader readerLIncl(&calib,      BTagEntry::OP_LOOSE,  "incl",   "central");
BTagCalibrationReader readerLIncl_up(&calib,   BTagEntry::OP_LOOSE,  "incl",   "up");
BTagCalibrationReader readerLIncl_do(&calib,   BTagEntry::OP_LOOSE,  "incl",   "down");
BTagCalibrationReader readerLComb(&calib,    BTagEntry::OP_LOOSE,  "comb", "central");
BTagCalibrationReader readerLComb_up(&calib, BTagEntry::OP_LOOSE,  "comb", "up");
BTagCalibrationReader readerLComb_do(&calib, BTagEntry::OP_LOOSE,  "comb", "down");
*/
//Lepton SF
//???
TFile *fileForwardJet    = new TFile("SF_dineutrino/ForwardJetSFFinal.root");/*{{{*/
TFile *fileMuonTrig      = new TFile("SF_dineutrino/EfficienciesAndSF_RunBtoF_Nov17Nov2017.root");
TFile *fileElectron1     = new TFile("SF_dineutrino/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root");
TFile *fileElectron2     = new TFile("SF_dineutrino/egammaEffi.txt_EGM2D_runBCDEF_passingTight94X.root");
TFile *fileElectronTrig  = new TFile("SF_dineutrino/ElectronTriggerSF.root");
TFile *fileOldPU         = new TFile("SF_dineutrino/PileUpReweighting2017.root");
TFile *fileNewPU         = new TFile("SF_dineutrino/PileUpReweighting2017_v1.root");
TFile *fileNewPUUp       = new TFile("SF_dineutrino/PileUpReweighting2017Up.root");
TFile *fileNewPUDo       = new TFile("SF_dineutrino/PileUpReweighting2017Do.root");
TFile *fileZPt           = new TFile("SF_dineutrino/scalefactors_v4.root");/*}}}*/
//TFile *fileHT_SF         = new TFile("SF_dineutrino/SF_2D_veto.root");
TFile *fileHT_SF         = new TFile("SF_dineutrino/SF_2D.root");/*{{{*/
TFile *fileTrig          = new TFile("SF_dineutrino/2DTrigger_SingleElectron_2017.root");
TH2F  *histoForwardJet   = (TH2F*)fileForwardJet->Get("histo");
TH2F  *histoMuonTrig     = (TH2F*)fileMuonTrig->Get("Mu50_PtEtaBins/abseta_pt_ratio");
TH2F  *histoElectron1    = (TH2F*)fileElectron1->Get("EGamma_SF2D");
TH2F  *histoElectron2    = (TH2F*)fileElectron2->Get("EGamma_SF2D");
TH2F  *histoElectronTrig = (TH2F*)fileElectronTrig->Get("eta_pt");
TH1F  *histoOldPU        = (TH1F*)fileOldPU  ->Get("pileup");
TH1F  *histoNewPU        = (TH1F*)fileNewPU  ->Get("pileup");
TH1F  *histoNewPUUp      = (TH1F*)fileNewPUUp->Get("pileup");
TH1F  *histoNewPUDo      = (TH1F*)fileNewPUDo->Get("pileup");
TF1   *functZPt          = (TF1*) fileZPt->Get("z_ewkcorr/z_ewkcorr_func");
TF1   *functWPt          = (TF1*) fileZPt->Get("w_ewkcorr/w_ewkcorr_func");
TH2F   *histoSF1         = (TH2F*) fileHT_SF->Get("SF1_h");
TH2F   *histoSF2         = (TH2F*) fileHT_SF->Get("SF2_h");
TH2F   *histoSF3         = (TH2F*) fileHT_SF->Get("SF3_h");
TH2F   *histoTrig        = (TH2F*) fileTrig ->Get("h_METvsMHT_EFF");/*}}}*/


TH1D  *h_genWeight = new TH1D( "h_genweight", "h_genweight", 1,-0.5, 0.5);
TTree *Tree;

//RECO INFO
vector <double> * Jet_pt_;   TBranch *b_Jet_pt;/*{{{*/
vector <double> * Jet_eta_;  TBranch *b_Jet_eta;
vector <double> * Jet_phi_;  TBranch *b_Jet_phi;
vector <double> * Jet_mass_; TBranch *b_Jet_mass;
vector <double> * Jet_JesSF_;TBranch *b_Jet_JesSF;
vector <double> * Jet_JesSFup_;TBranch *b_Jet_JesSFup;
vector <double> * Jet_JesSFdown_;TBranch *b_Jet_JesSFdown;
vector <double> * Jet_JerSF_;TBranch *b_Jet_JerSF;
vector <double> * Jet_JerSFup_;TBranch *b_Jet_JerSFup;
vector <double> * Jet_JerSFdown_;TBranch *b_Jet_JerSFdown;
vector <double> * Jet_Uncorr_pt_; TBranch *b_Jet_Uncorr_pt;
vector <double> * Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags_;              TBranch *b_Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags;
vector <double> * Jet_pfDeepCSVBJetTags_;           TBranch *b_Jet_pfDeepCSVBJetTags;
vector <double>* Jet_pfDeepFlavourBJetTags_; TBranch* b_Jet_pfDeepFlavourBJetTags;
vector <double> * Jet_neutralHadEnergyFraction_;    TBranch *b_Jet_neutralHadEnergyFraction;
vector <double> * Jet_chargedEmEnergyFraction_;     TBranch *b_Jet_chargedEmEnergyFraction;
vector <double> * Jet_neutralEmEnergyFraction_;   TBranch *b_Jet_neutralEmEnergyFraction;
vector <double> * Jet_numberOfConstituents_;        TBranch *b_Jet_numberOfConstituents;
vector <double> * Jet_chargedHadronEnergyFraction_; TBranch *b_Jet_chargedHadronEnergyFraction;
vector <double> * Jet_chargedMultiplicity_;         TBranch *b_Jet_chargedMultiplicity;
vector <double> * Jet_hadronFlavour_; TBranch *b_Jet_hadronFlavour;
vector <double>* Jet_muonEnergyFraction_; TBranch* b_Jet_muonEnergyFraction;
/*vector <double> * BoostedJet_pt_;        TBranch *b_BoostedJet_pt;
vector <double> * BoostedJet_Uncorr_pt_; TBranch *b_BoostedJet_Uncorr_pt;
vector <double> * BoostedJet_softdrop_mass_; TBranch *b_BoostedJet_softdrop_mass;
vector <double> * BoostedJet_puppi_softdrop_mass_; TBranch *b_BoostedJet_puppi_softdrop_mass;
vector <double> * BoostedJet_JesSF_;TBranch *b_BoostedJet_JesSF;
vector <double> * BoostedJet_JesSFup_;TBranch *b_BoostedJet_JesSFup;
vector <double> * BoostedJet_JesSFdown_;TBranch *b_BoostedJet_JesSFdown;
vector <double> * BoostedJet_JerSF_;TBranch *b_BoostedJet_JerSF;
vector <double> * BoostedJet_JerSFup_;TBranch *b_BoostedJet_JerSFup;
vector <double> * BoostedJet_JerSFdown_;TBranch *b_BoostedJet_JerSFdown;
vector <double> * BoostedJet_eta_;  TBranch *b_BoostedJet_eta;
vector <double> * BoostedJet_phi_;  TBranch *b_BoostedJet_phi;
vector <double> * BoostedJet_mass_; TBranch *b_BoostedJet_mass;
vector <double> * BoostedJet_tau1_; TBranch *b_BoostedJet_tau1;
vector <double> * BoostedJet_tau2_; TBranch *b_BoostedJet_tau2;
vector <double> * BoostedJet_tau3_; TBranch *b_BoostedJet_tau3;
vector <double> * BoostedJet_puppi_tau1_; TBranch *b_BoostedJet_puppi_tau1;
vector <double> * BoostedJet_puppi_tau2_; TBranch *b_BoostedJet_puppi_tau2;
vector <double> * BoostedJet_puppi_tau3_; TBranch *b_BoostedJet_puppi_tau3;
vector <double> * BoostedJet_pruned_mass_;  TBranch *b_BoostedJet_pruned_mass;
vector <double> * BoostedJet_neutralHadEnergyFraction_;    TBranch *b_BoostedJet_neutralHadEnergyFraction;
vector <double> * BoostedJet_neutralEmEnergyFraction_;    TBranch *b_BoostedJet_neutralEmEnergyFraction;
vector <double> * BoostedJet_chargedEmEnergyFraction_;     TBranch *b_BoostedJet_chargedEmEnergyFraction;
vector <double> * BoostedJet_neutralEmEmEnergyFraction_;     TBranch *b_BoostedJet_neutralEmEmEnergyFraction;
vector <double> * BoostedJet_numberOfConstituents_;        TBranch *b_BoostedJet_numberOfConstituents;
vector <double> * BoostedJet_chargedHadronEnergyFraction_; TBranch *b_BoostedJet_chargedHadronEnergyFraction;
vector <double> * BoostedJet_chargedMultiplicity_;         TBranch *b_BoostedJet_chargedMultiplicity;*/
vector <double> * TopTagging_topMass_;  TBranch *b_TopTagging_topMass;
vector <double> * TopTagging_minMass_;  TBranch *b_TopTagging_minMass;
vector <double> * TopTagging_wMass_; TBranch *b_TopTagging_wMass;
vector <double> * TopTagging_nSubJets_; TBranch *b_TopTagging_nSubJets;
vector <double> * patElectron_pt_; TBranch *b_patElectron_pt;
vector <double> * patElectron_eta_; TBranch *b_patElectron_eta;
vector <double> * patElectron_phi_; TBranch *b_patElectron_phi;
vector <double> * patElectron_energy_; TBranch *b_patElectron_energy;
vector <double> * patElectron_energyCorr_; TBranch *b_patElectron_energyCorr;
vector <double> * patElectron_SCeta_; TBranch *b_patElectron_SCeta;
vector <int> * patElectron_charge_; TBranch *b_patElectron_charge;
vector <double> * patElectron_Et_; TBranch *b_patElectron_Et;
vector <int>* patElectron_pdgId_; TBranch* b_patElectron_pdgId;
vector <double>* patElectron_relIsoDeltaBeta_; TBranch* b_patElectron_relIsoDeltaBeta;
vector <double>* patElectron_relIsoRhoEA_Update_; TBranch* b_patElectron_relIsoRhoEA_Update;
vector <int>* patElectron_gen_pdgId_; TBranch* b_patElectron_gen_pdgId;
vector <int>* patElectron_gen_isDirectPromptTauDecayProductFinalState_; TBranch* b_patElectron_gen_isDirectPromptTauDecayProductFinalState;
vector <int>* patElectron_mvaEleID_Fall17_noIso_V2_wp80_; TBranch *b_patElectron_mvaEleID_Fall17_noIso_V2_wp80;
vector <int>* patElectron_mvaEleID_Fall17_iso_V2_wp80_; TBranch* b_patElectron_mvaEleID_Fall17_iso_V2_wp80;
vector <int>* patElectron_mvaEleID_Fall17_iso_V2_wp90_; TBranch* b_patElectron_mvaEleID_Fall17_iso_V2_wp90;
vector <int>* patElectron_mvaEleID_Fall17_noIso_V2_wp90_; TBranch* b_patElectron_mvaEleID_Fall17_noIso_V2_wp90;
vector <int>* patElectron_mvaEleID_Fall17_iso_V2_wpLoose_; TBranch* b_patElectron_mvaEleID_Fall17_iso_V2_wpLoose;
vector <int>* patElectron_mvaEleID_Fall17_noIso_V2_wpLoose_; TBranch* b_patElectron_mvaEleID_Fall17_noIso_V2_wpLoose;
vector <double>* patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Values_; TBranch* b_patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Values;
vector <double>* patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Categories_; TBranch* b_patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Categories;
vector <double>* patElectron_ElectronMVAEstimatorRun2Fall17IsoV2Values_; TBranch* b_patElectron_ElectronMVAEstimatorRun2Fall17IsoV2Values;
vector <double>* patElectron_ElectronMVAEstimatorRun2Fall17IsoV2Categories_; TBranch* b_patElectron_ElectronMVAEstimatorRun2Fall17IsoV2Categories;
vector <double>* patElectron_mvaEleID_Spring16_GeneralPurpose_V1_wp80_; TBranch* b_patElectron_mvaEleID_Spring16_GeneralPurpose_V1_wp80;
vector <int>* patElectron_mvaEleID_Spring16_GeneralPurpose_V1_wp90_; TBranch* b_patElectron_mvaEleID_Spring16_GeneralPurpose_V1_wp90;
vector <double>* patElectron_MVAValue_ElectronMVAEstimatorRun2Spring16GeneralPurposeV1_; TBranch* b_patElectron_MVAValue_ElectronMVAEstimatorRun2Spring16GeneralPurposeV1;
vector <int>* patElectron_cutBasedElectronID_Fall17_94X_V2_medium_; TBranch* b_patElectron_cutBasedElectronID_Fall17_94X_V2_medium;
vector <int>* patElectron_cutBasedElectronID_Fall17_94X_V2_loose_; TBranch* b_patElectron_cutBasedElectronID_Fall17_94X_V2_loose;
vector <int>* patElectron_cutBasedElectronID_Fall17_94X_V2_tight_; TBranch* b_patElectron_cutBasedElectronID_Fall17_94X_V2_tight;
vector <int>* patElectron_cutBasedElectronID_Fall17_94X_V2_veto_; TBranch* b_patElectron_cutBasedElectronID_Fall17_94X_V2_veto;
vector <int>* patElectron_heepElectronID_HEEPV70_; TBranch* b_patElectron_heepElectronID_HEEPV70;
vector <double> * patElectron_d0_; TBranch *b_patElectron_d0;
vector <double> * patElectron_gsfTrack_dz_pv_; TBranch *b_patElectron_gsfTrack_dz_pv;
vector <int> * patElectron_expectedMissingInnerHits_; TBranch *b_patElectron_expectedMissingInnerHits;
vector <int> * patElectron_passConversionVeto_; TBranch *b_patElectron_passConversionVeto;
vector <double> * patElectron_isoChargedHadrons_; TBranch *b_patElectron_isoChargedHadrons;
vector <double> * patElectron_isoNeutralHadrons_; TBranch *b_patElectron_isoNeutralHadrons;
vector <double> * patElectron_isoPhotons_; TBranch *b_patElectron_isoPhotons;
vector <double> * patElectron_isoPU_; TBranch *b_patElectron_isoPU;
vector <double> * patElectron_dEtaIn_; TBranch *b_patElectron_dEtaIn;
vector <double> * patElectron_dPhiIn_; TBranch *b_patElectron_dPhiIn;
vector <double> * patElectron_full5x5_sigmaIetaIeta_; TBranch *b_patElectron_full5x5_sigmaIetaIeta;
vector <double> * patElectron_hOverE_; TBranch *b_patElectron_hOverE;
vector <double> * patElectron_ooEmooP_; TBranch *b_patElectron_ooEmooP;
vector <double> * patElectron_relIsoRhoEA_; TBranch *b_patElectron_relIsoRhoEA;
vector <double> * patElectron_inCrack_; TBranch *b_patElectron_inCrack;
vector <int> * patElectron_isMatchedToTrigger_; TBranch *b_patElectron_isMatchedToTrigger;

vector <double>* patElectron_miniIsoRel_; TBranch *b_patElectron_miniIsoRel;
vector <double>* patElectron_jetptratio_; TBranch *b_patElectron_jetptratio;
vector <double>* patElectron_ptrel_; TBranch *b_patElectron_ptrel;
vector <double>* patElectron_IP3D_sig_; TBranch *b_patElectron_IP3D_sig;

vector <double> * Muon_pt_; TBranch *b_Muon_pt;
vector <double> * Muon_eta_; TBranch *b_Muon_eta;
vector <double> * Muon_phi_; TBranch *b_Muon_phi;
vector <double> * Muon_energy_; TBranch *b_Muon_energy;
vector <int> * Muon_charge_; TBranch *b_Muon_charge;
vector <int> * Muon_tight_; TBranch *b_Muon_tight;
vector <int> * Muon_medium_; TBranch *b_Muon_medium;
vector <int> * Muon_loose_; TBranch *b_Muon_loose;
vector <int> * Muon_soft_; TBranch *b_Muon_soft;
vector <int> * Muon_isHighPt_; TBranch *b_Muon_isHighPt;
vector <int> * Muon_pf_; TBranch *b_Muon_pf;
vector <double> * Muon_dxy_pv_; TBranch *b_Muon_dxy_pv;
vector <double> * Muon_dz_pv_; TBranch *b_Muon_dz_pv;
vector <double> * Muon_dxy_bt_; TBranch *b_Muon_dxy_bt;
vector <double> * Muon_dz_bt_; TBranch *b_Muon_dz_bt;
vector <int> * Muon_isGlobal_; TBranch *b_Muon_isGlobal;
vector <double> * Muon_isoCharged_; TBranch *b_Muon_isoCharged;
vector <double> * Muon_isoSum_; TBranch *b_Muon_isoSum;
vector <double> * Muon_isoCharParPt_; TBranch *b_Muon_isoCharParPt;
vector <double> * Muon_relIsoDeltaBetaR04_; TBranch *b_Muon_relIsoDeltaBetaR04;
vector <double> * Muon_miniIsoRel_; TBranch *b_Muon_miniIsoRel;
vector <double> * Muon_ptrel_; TBranch *b_Muon_ptrel;
vector <double> * Muon_jetptratio_; TBranch *b_Muon_jetptratio;
vector <double> * Muon_jetptratioV2_; TBranch *b_Muon_jetptratioV2;
vector <double>* Muon_IP3D_sig_; TBranch* b_Muon_IP3D_sig;


vector <int> * Muon_isMatchedToTrigger_; TBranch *b_Muon_isMatchedToTrigger;
vector <int> * Muon_pdgId_; TBranch *b_Muon_pdgId;

vector <int>* TopTagger_type_; TBranch* b_TopTagger_type;
vector <double>* TopTagger_discriminator_; TBranch* b_TopTagger_discriminator;
vector <int>* TopTagger_jet1Idx_; TBranch* b_TopTagger_jet1Idx;
vector <int>* TopTagger_jet2Idx_; TBranch* b_TopTagger_jet2Idx;
vector <int>* TopTagger_jet3Idx_; TBranch* b_TopTagger_jet3Idx;

vector <double>* Tau_pt_; TBranch* b_Tau_pt;
vector <double>* Tau_eta_; TBranch* b_Tau_eta;
vector <double>* Tau_leadChargedCandDz_pv_; TBranch* b_Tau_leadChargedCandDz_pv;
vector <double>* Tau_packedLeadTauCand_dz_; TBranch* b_Tau_packedLeadTauCand_dz;
vector <double>* Tau_phi_; TBranch* b_Tau_phi;
vector <double>* Tau_energy_; TBranch* b_Tau_energy;
vector <double>* Tau_px_; TBranch* b_Tau_px;
vector <double>* Tau_py_; TBranch* b_Tau_py;
vector <double>* Tau_pz_; TBranch* b_Tau_pz;
vector <double>* Tau_p_; TBranch* b_Tau_p;
vector <double>* Tau_charge_; TBranch* b_Tau_charge;
vector <int>* Tau_decayModeFinding_; TBranch* b_Tau_decayModeFinding;
vector <int>* Tau_decayModeFindingNewDMs_; TBranch* b_Tau_decayModeFindingNewDMs;
vector <int>* Tau_decayMode_; TBranch* b_Tau_decayMode;
vector <int>* Tau_againstMuonLoose3_; TBranch* b_Tau_againstMuonLoose3;
vector <int>* Tau_againstMuonTight3_; TBranch* b_Tau_againstMuonTight3;
vector <int>* Tau_byDeepTau2017v2p1VSjetraw_; TBranch* b_Tau_byDeepTau2017v2p1VSjetraw;
vector <int>* Tau_byVVVLooseDeepTau2017v2p1VSjet_; TBranch* b_Tau_byVVVLooseDeepTau2017v2p1VSjet;
vector <int>* Tau_byVVLooseDeepTau2017v2p1VSjet_; TBranch* b_Tau_byVVLooseDeepTau2017v2p1VSjet;
vector <int>* Tau_byVLooseDeepTau2017v2p1VSjet_; TBranch* b_Tau_byVLooseDeepTau2017v2p1VSjet;
vector <int>* Tau_byLooseDeepTau2017v2p1VSjet_; TBranch* b_Tau_byLooseDeepTau2017v2p1VSjet;
vector <int>* Tau_byMediumDeepTau2017v2p1VSjet_; TBranch* b_Tau_byMediumDeepTau2017v2p1VSjet;
vector <int>* Tau_byTightDeepTau2017v2p1VSjet_; TBranch* b_Tau_byTightDeepTau2017v2p1VSjet;
vector <int>* Tau_byVTightDeepTau2017v2p1VSjet_; TBranch* b_Tau_byVTightDeepTau2017v2p1VSjet;
vector <int>* Tau_byVVTightDeepTau2017v2p1VSjet_; TBranch* b_Tau_byVVTightDeepTau2017v2p1VSjet;
vector <int>* Tau_byDeepTau2017v2p1VSmuraw_; TBranch* b_Tau_byDeepTau2017v2p1VSmuraw;
vector <int>* Tau_byVLooseDeepTau2017v2p1VSmu_; TBranch* b_Tau_byVLooseDeepTau2017v2p1VSmu;
vector <int>* Tau_byLooseDeepTau2017v2p1VSmu_; TBranch* b_Tau_byLooseDeepTau2017v2p1VSmu;
vector <int>* Tau_byMediumDeepTau2017v2p1VSmu_; TBranch* b_Tau_byMediumDeepTau2017v2p1VSmu;
vector <int>* Tau_byTightDeepTau2017v2p1VSmu_; TBranch* b_Tau_byTightDeepTau2017v2p1VSmu;
vector <int>* Tau_byDeepTau2017v2p1VSeraw_; TBranch* b_Tau_byDeepTau2017v2p1VSeraw;
vector <int>* Tau_byVVVLooseDeepTau2017v2p1VSe_; TBranch* b_Tau_byVVVLooseDeepTau2017v2p1VSe;
vector <int>* Tau_byVVLooseDeepTau2017v2p1VSe_; TBranch* b_Tau_byVVLooseDeepTau2017v2p1VSe;
vector <int>* Tau_byVLooseDeepTau2017v2p1VSe_; TBranch* b_Tau_byVLooseDeepTau2017v2p1VSe;
vector <int>* Tau_byLooseDeepTau2017v2p1VSe_; TBranch* b_Tau_byLooseDeepTau2017v2p1VSe;
vector <int>* Tau_byMediumDeepTau2017v2p1VSe_; TBranch* b_Tau_byMediumDeepTau2017v2p1VSe;
vector <int>* Tau_byTightDeepTau2017v2p1VSe_; TBranch* b_Tau_byTightDeepTau2017v2p1VSe;
vector <int>* Tau_byVTightDeepTau2017v2p1VSe_; TBranch* b_Tau_byVTightDeepTau2017v2p1VSe;
vector <int>* Tau_byVVTightDeepTau2017v2p1VSe_; TBranch* b_Tau_byVVTightDeepTau2017v2p1VSe;
//vector <>* _; TBranch* ;
//vector <>* _; TBranch* ;

  int HLT_Ele27_eta2p1_WP75_Gsf_; TBranch *b_HLT_Ele27_eta2p1_WP75_Gsf;
//
//add
int HLT_PFHT900_; TBranch *b_HLT_PFHT900;
int HLT_PFHT450_SixJet40_BTagCSV_p056_; TBranch *b_HLT_PFHT450_SixJet40_BTagCSV_p056;
int HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_; TBranch *b_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056;
int HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_;  TBranch *b_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg ;
int HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_;  TBranch *b_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg ;
int HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_;   TBranch * b_HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg ;
int HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_;  TBranch *b_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg ;
int HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_;  TBranch *b_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg ;
int HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_;  TBranch *b_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg ;
int HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_;  TBranch *b_HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg ;

int HLT_Ele27_eta2p1_WPTight_Gsf_;  TBranch *b_HLT_Ele27_eta2p1_WPTight_Gsf ;
int HLT_Ele27_eta2p1_WPLoose_Gsf_; TBranch *b_HLT_Ele27_eta2p1_WPLoose_Gsf;
int HLT_Ele27_WPTight_Gsf_;  TBranch *b_HLT_Ele27_WPTight_Gsf ;
int HLT_IsoMu22_;  TBranch *b_HLT_IsoMu22 ;
int HLT_Ele25_eta2p1_WPTight_Gsf_;  TBranch *b_HLT_Ele25_eta2p1_WPTight_Gsf ;
int HLT_IsoTkMu22_;  TBranch *b_HLT_IsoTkMu22 ;
int HLT_IsoMu24_;  TBranch *b_HLT_IsoMu24 ;
int HLT_IsoTkMu24_;  TBranch *b_HLT_IsoTkMu24 ;
int HLT_IsoMu22_eta2p1_;  TBranch *b_HLT_IsoMu22_eta2p1 ;
int HLT_IsoTkMu22_eta2p1_;  TBranch *b_HLT_IsoTkMu22_eta2p1 ;
int HLT_Mu50_;  TBranch *b_HLT_Mu50 ;
int HLT_TkMu50_;  TBranch *b_HLT_TkMu50 ;
int HLT_Ele32_WPTight_Gsf_;  TBranch *b_HLT_Ele32_WPTight_Gsf ;
int HLT_Ele35_WPTight_Gsf_;  TBranch *b_HLT_Ele35_WPTight_Gsf ;
int HLT_IsoMu27_;  TBranch *b_HLT_IsoMu27 ;

   int HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_; TBranch *b_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20;
   int HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_; TBranch *b_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1;
   int HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_; TBranch *b_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30;
   int HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_; TBranch *b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1;
   int HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_; TBranch *b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1;
   int HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_; TBranch *b_HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1;
   int HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_; TBranch *b_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1;
   int HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_; TBranch *b_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1;

   int HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_; TBranch *b_HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf;
   int HLT_DoubleEle33_CaloIdL_MW_; TBranch *b_HLT_DoubleEle33_CaloIdL_MW;
   int HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_; TBranch *b_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW;
   int HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_; TBranch *b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   int HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_; TBranch *b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
   int HLT_DoubleMu33NoFiltersNoVtx_; TBranch *b_HLT_DoubleMu33NoFiltersNoVtx;
   int HLT_DoubleMu23NoFiltersNoVtxDisplaced_; TBranch *b_HLT_DoubleMu23NoFiltersNoVtxDisplaced;
   int HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_; TBranch *b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
   int HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_; TBranch *b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
   int HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_; TBranch *b_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
   int HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_; TBranch *b_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
   int HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_; TBranch *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
   int HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_; TBranch *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
   int HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_; TBranch *b_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL;
   int HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_; TBranch *b_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ;
   int HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_; TBranch *b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
   int HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_; TBranch *b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   int HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_; TBranch *b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
   int HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_; TBranch *b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;

   int HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_; TBranch *b_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;
   int HLT_Mu8_DiEle12_CaloIdL_TrackIdL_; TBranch *b_HLT_Mu8_DiEle12_CaloIdL_TrackIdL;
   int HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_; TBranch *b_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ;
   int HLT_TripleMu_12_10_5_; TBranch *b_HLT_TripleMu_12_10_5;
   int HLT_DiMu9_Ele9_CaloIdL_TrackIdL_; TBranch *b_HLT_DiMu9_Ele9_CaloIdL_TrackIdL;




//
//
int Flag_goodVertices_; TBranch *b_Flag_goodVertices;
int Flag_globalSuperTightHalo2016Filter_; TBranch *b_Flag_globalSuperTightHalo2016Filter;
int Flag_CSCTightHalo2015Filter_; TBranch *b_Flag_CSCTightHalo2015Filter;
int Flag_HBHENoiseFilter_; TBranch *b_Flag_HBHENoiseFilter;
int Flag_HBHENoiseIsoFilter_; TBranch *b_Flag_HBHENoiseIsoFilter;
int Flag_EcalDeadCellTriggerPrimitiveFilter_; TBranch *b_Flag_EcalDeadCellTriggerPrimitiveFilter;
int Flag_BadPFMuonFilter_; TBranch *b_Flag_BadPFMuonFilter;
int Flag_BadChargedCandidateFilter_; TBranch *b_Flag_BadChargedCandidateFilter;
//int Flag_ecalBadCalibReducedMINIAODFilter_; TBranch *b_Flag_ecalBadCalibReducedMINIAODFilter;
int Flag_eeBadScFilter_; TBranch *b_Flag_eeBadScFilter;
int Flag_METFilters_; TBranch *b_Flag_METFilters;
int nBestVtx_; TBranch *b_nBestVtx;
double PUWeight_; TBranch *b_PUWeight;
double PUWeightUP_; TBranch *b_PUWeightUP;
double PUWeightDOWN_; TBranch *b_PUWeightDOWN;
int HLT_PFHT500_PFMET100_PFMHT100_IDTight_;        TBranch * b_HLT_PFHT500_PFMET100_PFMHT100_IDTight;
int HLT_PFHT700_PFMET85_PFMHT85_IDTight_;          TBranch * b_HLT_PFHT700_PFMET85_PFMHT85_IDTight;
int HLT_PFHT800_PFMET75_PFMHT75_IDTight_;          TBranch * b_HLT_PFHT800_PFMET75_PFMHT75_IDTight;
//int HLT_PFMET120_PFMHT120_IDTight_;                TBranch * b_HLT_PFMET120_PFMHT120_IDTight;
//int HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_;        TBranch * b_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight;
int HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight_;     TBranch * b_HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight;
int HLT_CaloJet500_NoJetID_;                       TBranch * b_HLT_CaloJet500_NoJetID;
int HLT_AK8PFJet500_;                              TBranch * b_HLT_AK8PFJet500;
int HLT_PFJet500_;                                 TBranch * b_HLT_PFJet500;
int HLT_PFHT1050_;                                 TBranch * b_HLT_PFHT1050;
double Met_type1PF_pt_;  TBranch * b_Met_type1PF_pt;
double Met_type1PF_phi_; TBranch * b_Met_type1PF_phi;
double Met_type1PF_sumEt_; TBranch * b_Met_type1PF_sumEt;
vector<double> * genWeights_ = new std::vector<double>; TBranch *b_genWeights;
double genWeight_; TBranch *b_genWeight;
double bWeight_; TBranch *b_bWeight;
vector <double> * Gen_pt_; TBranch *b_Gen_pt;
vector <double> * Gen_eta_; TBranch *b_Gen_eta;
vector <double> * Gen_phi_; TBranch *b_Gen_phi;
vector <double> * Gen_pdg_id_; TBranch *b_Gen_pdg_id;
vector <double> * Gen_motherpdg_id_; TBranch *b_Gen_motherpdg_id;
vector <double> * Gen_energy_; TBranch *b_Gen_energy;
vector <double> * Gen_charge_; TBranch *b_Gen_charge;


//int EVENT_event_; TBranch *b_EVENT_event;
ULong64_t EVENT_event_; TBranch *b_EVENT_event;
int EVENT_run_; TBranch *b_EVENT_run;
int EVENT_lumiBlock_; TBranch *b_EVENT_lumiBlock;
double EVENT_genHT_; TBranch *b_EVENT_genHT;
double EVENT_prefireWeight_; TBranch *b_EVENT_prefireWeight;
double EVENT_prefireWeightUp_; TBranch *b_EVENT_prefireWeightUp;
double EVENT_prefireWeightDown_; TBranch *b_EVENT_prefireWeightDown;
/*}}}*/

//for new tree
/*{{{*/



int HLT_PFHT900 = -99; 
int HLT_PFHT450_SixJet40_BTagCSV_p056 = -99; 
int HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = -99; 
int HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg = -99;  
int HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg = -99;  
int HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg = -99;   
int HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg = -99;  
int HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg = -99;  
int HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg = -99;  
int HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg = -99;  
int HLT_Ele27_eta2p1_WPTight_Gsf = -99;  
int HLT_Ele27_eta2p1_WPLoose_Gsf =-99;
int HLT_Ele27_WPTight_Gsf = -99;  
int HLT_IsoMu22 = -99;  
int HLT_Ele25_eta2p1_WPTight_Gsf = -99;  
int HLT_IsoTkMu22 = -99;  
int HLT_IsoMu24 = -99;  
int HLT_IsoTkMu24 = -99;  
int HLT_IsoMu22_eta2p1 = -99;  
int HLT_IsoTkMu22_eta2p1 = -99;  
int HLT_Mu50 = -99;  
int HLT_TkMu50 = -99;  
int HLT_Ele32_WPTight_Gsf = -99;  
int HLT_Ele35_WPTight_Gsf = -99;  
int HLT_IsoMu27 = -99;  

   int HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20 = -99; 
   int HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1 = -99; 
   int HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30 = -99; 
   int HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1 = -99; 
   int HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1 = -99; 
   int HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1 = -99; 
   int HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1 = -99; 
   int HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1 = -99; 

   int HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf = -99; 
   int HLT_DoubleEle33_CaloIdL_MW = -99; 
   int HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW = -99; 
   int HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = -99; 
   int HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = -99; 
   int HLT_DoubleMu33NoFiltersNoVtx = -99; 
   int HLT_DoubleMu23NoFiltersNoVtxDisplaced = -99; 
   int HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = -99; 
   int HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 = -99; 
   int HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL = -99;
   int HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = -99;
   int HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL = -99; 
   int HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = -99; 
   int HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL = -99;
   int HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ = -99;
   int HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = -99; 
   int HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = -99; 
   int HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL = -99; 
   int HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = -99; 

   int HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL = -99; 
   int HLT_Mu8_DiEle12_CaloIdL_TrackIdL = -99; 
   int HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ = -99; 
   int HLT_TripleMu_12_10_5 = -99; 
   int HLT_DiMu9_Ele9_CaloIdL_TrackIdL = -99; 


int    genTaus_number = -99;
int genEles_number = -99;
vector <double> genEle_pt;
vector <double> genEle_eta;
vector <double> genEle_phi;
vector <double> genEle_E;
int genMuons_number = -99;
vector <double> genMuon_pt;
vector <double> genMuon_eta;
vector <double> genMuon_phi;
vector <double> genMuon_E;


double TopMass=-99;
double TopMassMerged=-99;
double TopMassPartial=-99;
double TopMassResolved=-99;
double TopPt=-99;
double TopPtMerged=-99;
double TopPtPartial=-99;
double TopPtResolved=-99;
double TopEta=-99;
double TopEtaMerged=-99;
double TopEtaPartial=-99;
double TopEtaResolved=-99;
double TopPhi=-99;
double TopPhiMerged=-99;
double TopPhiPartial=-99;
double TopPhiResolved=-99;
double WMassResolved1=-99;
double WMassResolved2=-99;
double WMassResolved3=-99;
double BMass=-99;
double BCSV=-99;
double BPt=-99;
double BEta=-99;
double BPhi=-99;
double ZMass=-99;
double ZPt=-99;
double ZEta=-99;
double ZPhi=-99;
double Jet1ForwardPt=-99;
double Jet2ForwardPt=-99;
double Jet3ForwardPt=-99;
double Jet1ResolvedPt=-99;
double Jet2ResolvedPt=-99;
double Jet3ResolvedPt=-99;
double Jet1PartialPt=-99;
double Jet2PartialPt=-99;
double Jet1MergedPt=-99;
double Jet1ForwardEta=-99;
double Jet2ForwardEta=-99;
double Jet3ForwardEta=-99;
double Jet1ResolvedEta=-99;
double Jet2ResolvedEta=-99;
double Jet3ResolvedEta=-99;
double Jet1PartialEta=-99;
double Jet2PartialEta=-99;
double Jet1MergedEta=-99;
double MostForwardJetEta=-99;
double MostForwardJetPt=-99;
double deltaPhiZB=-99;
double deltaRZB=-99;
double deltaRZTop=-99;
double deltaPhiZTopResolved=-99;
double deltaRZTopResolved=-99;
double deltaPhiZTopPartial=-99;
double deltaRZTopPartial=-99;
double deltaPhiZTopMerged=-99;
double deltaRZTopMerged=-99;
double deltaRbTop=-99;
double deltaREle1Ele2=-99;
double deltaRMuo1Muo2=-99;
double deltaREle1Ele2M=-99;
double deltaRMuo1Muo2M=-99;
double Massb1b2=-99;
double deltaRb1b2=-99;
double deltaRb1Lep1=-99;
double deltaRb1Lep2=-99;
double deltaRb2Lep1=-99;
double deltaRb2Lep2=-99;
double deltaPhiMetTop=-99.;
double MinDeltaPhiBoostedJetMet=99.;

int   leptonsL_number=-99;
int leptonsT_number=-99;
int leptonsT_number_v2=-99;
int leptonsMVAF_number=-99;
int leptonsMVAT_number=-99;
int leptonsMVAL_number=-99;
double leptonsMVAT_transMass = -99;
double leptonsMVAF_transMass = -99;
double leptonsMVAL_transMass = -99;
double elesMVAF_1pt = -99;
double leptonsMVAT_1pt = -99;
double leptonsMVAT_1eta = -99;
double leptonsMVAT_1phi = -99;
double leptonsMVAT_2pt= -99;
double leptonsMVAT_2eta = -99;
double leptonsMVAT_2phi= -99;
double leptonsMVAT_3pt = -99;
double leptonsMVAT_3eta = -99;
double leptonsMVAT_3phi = -99;
int   leptonsMVAT_2SS = 0;
int   leptonsMVAT_2OS = 0;

int muonsT_number=-99;
int   muonsL_number=-99;
int  muonsF_number = -99;
vector <double>  muonL_pt;
vector <double>  muonL_eta;
vector <double>  muonL_phi;
vector <double>  muonL_E;

vector <double>  muonF_pt;
vector <double>  muonF_eta;
vector <double>  muonF_phi;
vector <double>  muonF_E;

vector <double>  muonT_pt;
vector <double>  muonT_eta;
vector <double>  muonT_phi;
vector <double>  muonT_E;

int muonsT_number_s0=-99;
int   muonsL_number_s0=-99;
int  muonsF_number_s0 = -99;
vector <double>  muonL_pt_s0;
vector <double>  muonL_eta_s0;
vector <double>  muonL_phi_s0;
vector <double>  muonL_E_s0;

vector <double>  muonF_pt_s0;
vector <double>  muonF_eta_s0;
vector <double>  muonF_phi_s0;
vector <double>  muonF_E_s0;

vector <double>  muonT_pt_s0;
vector <double>  muonT_eta_s0;
vector <double>  muonT_phi_s0;
vector <double>  muonT_E_s0; 

int muonsT_number_s1=-99;
int   muonsL_number_s1=-99;
int  muonsF_number_s1 = -99;
vector <double>  muonL_pt_s1;
vector <double>  muonL_eta_s1;
vector <double>  muonL_phi_s1;
vector <double>  muonL_E_s1;

vector <double>  muonF_pt_s1;
vector <double>  muonF_eta_s1;
vector <double>  muonF_phi_s1;
vector <double>  muonF_E_s1;

vector <double>  muonT_pt_s1;
vector <double>  muonT_eta_s1;
vector <double>  muonT_phi_s1;
vector <double>  muonT_E_s1;

int muonsT_number_s2=-99;
int   muonsL_number_s2=-99;
int  muonsF_number_s2 = -99;
vector <double>  muonL_pt_s2;
vector <double>  muonL_eta_s2;
vector <double>  muonL_phi_s2;
vector <double>  muonL_E_s2;

vector <double>  muonF_pt_s2;
vector <double>  muonF_eta_s2;
vector <double>  muonF_phi_s2;
vector <double>  muonF_E_s2;

vector <double>  muonT_pt_s2;
vector <double>  muonT_eta_s2;
vector <double>  muonT_phi_s2;
vector <double>  muonT_E_s2;

int muonsT_number_s3=-99;
int   muonsL_number_s3=-99;
int  muonsF_number_s3 = -99;
vector <double>  muonL_pt_s3;
vector <double>  muonL_eta_s3;
vector <double>  muonL_phi_s3;
vector <double>  muonL_E_s3;

vector <double>  muonF_pt_s3;
vector <double>  muonF_eta_s3;
vector <double>  muonF_phi_s3;
vector <double>  muonF_E_s3;

vector <double>  muonT_pt_s3;
vector <double>  muonT_eta_s3;
vector <double>  muonT_phi_s3;
vector <double>  muonT_E_s3;

double muonsT_1pt = -99;
double muonsT_1eta = -99;
double muonsT_1phi = -99;
double muonsT_2pt = -99;
double muonsT_2eta = -99;
double muonsT_2phi = -99;
double muonsT_3pt = -99;
double muonsT_3eta = -99;
double muonsT_3phi = -99;

int elesMVAL_number=-99;
int elesMVAF_number=-99;
int elesMVAT_number=-99;
vector <double>  eleMVAL_pt;
vector <double>  eleMVAL_eta;
vector <double>  eleMVAL_phi;
vector <double>  eleMVAL_E;

vector <double>  eleMVAF_pt;
vector <double>  eleMVAF_eta;
vector <double>  eleMVAF_phi;
vector <double>  eleMVAF_E;

vector <double>  eleMVAT_pt;
vector <double>  eleMVAT_eta;
vector <double>  eleMVAT_phi;
vector <double>  eleMVAT_E;

int elesMVAL_number_s0=-99;
int elesMVAF_number_s0=-99;
int elesMVAT_number_s0=-99;
vector <double>  eleMVAL_pt_s0;
vector <double>  eleMVAL_eta_s0;
vector <double>  eleMVAL_phi_s0;
vector <double>  eleMVAL_E_s0;

vector <double>  eleMVAF_pt_s0;
vector <double>  eleMVAF_eta_s0;
vector <double>  eleMVAF_phi_s0;
vector <double>  eleMVAF_E_s0;

vector <double>  eleMVAT_pt_s0;
vector <double>  eleMVAT_eta_s0;
vector <double>  eleMVAT_phi_s0;
vector <double>  eleMVAT_E_s0;

int elesMVAL_number_s1=-99;
int elesMVAF_number_s1=-99;
int elesMVAT_number_s1=-99;
vector <double>  eleMVAL_pt_s1;
vector <double>  eleMVAL_eta_s1;
vector <double>  eleMVAL_phi_s1;
vector <double>  eleMVAL_E_s1;

vector <double>  eleMVAF_pt_s1;
vector <double>  eleMVAF_eta_s1;
vector <double>  eleMVAF_phi_s1;
vector <double>  eleMVAF_E_s1;

vector <double>  eleMVAT_pt_s1;
vector <double>  eleMVAT_eta_s1;
vector <double>  eleMVAT_phi_s1;
vector <double>  eleMVAT_E_s1;

int elesMVAL_number_s2=-99;
int elesMVAF_number_s2=-99;
int elesMVAT_number_s2=-99;
vector <double>  eleMVAL_pt_s2;
vector <double>  eleMVAL_eta_s2;
vector <double>  eleMVAL_phi_s2;
vector <double>  eleMVAL_E_s2;

vector <double>  eleMVAF_pt_s2;
vector <double>  eleMVAF_eta_s2;
vector <double>  eleMVAF_phi_s2;
vector <double>  eleMVAF_E_s2;

vector <double>  eleMVAT_pt_s2;
vector <double>  eleMVAT_eta_s2;
vector <double>  eleMVAT_phi_s2;
vector <double>  eleMVAT_E_s2;

int elesMVAL_number_s3=-99;
int elesMVAF_number_s3=-99;
int elesMVAT_number_s3=-99;
vector <double>  eleMVAL_pt_s3;
vector <double>  eleMVAL_eta_s3;
vector <double>  eleMVAL_phi_s3;
vector <double>  eleMVAL_E_s3;

vector <double>  eleMVAF_pt_s3;
vector <double>  eleMVAF_eta_s3;
vector <double>  eleMVAF_phi_s3;
vector <double>  eleMVAF_E_s3;

vector <double>  eleMVAT_pt_s3;
vector <double>  eleMVAT_eta_s3;
vector <double>  eleMVAT_phi_s3;
vector <double>  eleMVAT_E_s3;

//
//
int   eleL_number=-99;
int   eleM_number=-99;
int   eleT_number=-99;
double   jetsL_invariantMass=-99;
double bjetsL_invariantMass= -99;
double bjetsM_invariantMass= -99;
double bjetsT_invariantMass= -99;
double jetsL_transMass = -99;
double bjetsL_transMass = -99;
double bjetsM_transMass = -99;
double bjetsT_transMass = -99;
double jetL_minDeltaR = -99;
double bjetsL_minDeltaR = -99;
double bjetsM_minDeltaR = -99;
double bjetsT_minDeltaR = -99;
double bjetsL_leptonsMVAT_minDeltaR = -99;
double bjetsM_leptonsMVAT_minDeltaR = -99;
double bjetsT_leptonsMVAT_minDeltaR = -99;
double bjetsL_tausF_minDeltaR = -99;
double   jetsL_centrality=-99;
double   Aplanarity=-99;
//double   MaxdeltaRJets=-99;
double   Sphericity=-99;
//double MindeltaRJets=-99;
double jetsL_HTDividedByMet=-99;
double MetDividedByHT=-99;
double jetsL_MHTDividedByMet=-99;


double LeadingJetpfDeepFlavourBJetTags=-99;
double SecondJetpfDeepFlavourBJetTags=-99;
double ThirdJetpfDeepFlavourBJetTags=-99;
double jetsL_bScore=-99;

double jetsL_average_deltaR = -99;
double jetsL_4largestBscoreSum = -99;
double jetsL_leading2invariantMass = -99;
double jetsL_rationHT_4toRest = -99;
double MinDeltaPhiJets=-99;
double jetsL_leptonsMVAT_minDeltaR = -99;
double jetsL_tausF_minDeltaR = -99;
double bjetsL_1pt = -99;
double bjetsL_1eta = -99;
double bjetsL_1phi = -99;
double bjetsL_2pt = -99;
double bjetsL_2eta = -99;
double bjetsL_2phi = -99;
double bjetsL_4pt = -99;
double bjetsL_4eta = -99;
double bjetsL_4phi = -99;
double bjetsL_3pt = -99;
double bjetsL_3eta = -99;
double bjetsL_3phi = -99;
double bjetsM_1pt = -99;
double bjetsM_1eta = -99;
double bjetsM_1phi = -99;
double bjetsM_2pt = -99;
double bjetsM_2eta = -99;
double bjetsM_2phi = -99;
double bjetsM_4pt = -99;
double bjetsM_4eta = -99;
double bjetsM_4phi = -99;
double bjetsM_3pt = -99;
double bjetsM_3eta = -99;
double bjetsM_3phi = -99;
double bjetsT_1pt = -99;
double bjetsT_1eta = -99;
double bjetsT_1phi = -99;
double bjetsT_2pt = -99;
double bjetsT_2eta = -99;
double bjetsT_2phi = -99;
double bjetsT_4pt = -99;
double bjetsT_4eta = -99;
double bjetsT_4phi = -99;
double bjetsT_3pt = -99;
double bjetsT_3eta = -99;
double bjetsT_3phi = -99;

double forwardjet_1pt = -99;
double forwardjet_1eta = -99;
double forwardjet_1phi = -99;
double forwardjet1_jetsL_minDeltaEta = -99;
double jetsL_1pt = -99;
double jetsL_1phi = -99;
double jetsL_1eta = -99;
double jetsL_2pt = -99;
double jetsL_2eta = -99;
double jetsL_2phi = -99;
double jetsL_3pt = -99;
double jetsL_3eta = -99;
double jetsL_3phi = -99;
double jetsL_4pt = -99;
double jetsL_4eta = -99;
double jetsL_4phi = -99;
double jetsL_5pt = -99;
double jetsL_5eta = -99;
double jetsL_5phi = -99;
double jetsL_6pt = -99;
double jetsL_6eta = -99;
double jetsL_6phi = -99;
double jetsL_7pt = -99;
double jetsL_7eta = -99;
double jetL_7phi = -99;
double jetsL_8pt = -99;
double jetsL_8eta = -99;
double jetsL_8phi = -99;
double jetsL_9pt = -99;
double jetsL_9eta = -99;
double jetsL_9phi = -99;
double jetsL_10pt = -99;
double jetsL_10eta = -99;
double jetsL_10phi = -99;
double jetsL_11pt = -99;
double jetsL_11eta = -99;
double jetsL_11phi = -99;

int tausL_number=-99;
int tausF_number=-99;
int tausT_number=-99;
double tausL_MHT=-99;
double tausF_MHT=-99;
double tausT_MHT=-99;
double tausL_HT=-99;
double tausF_HT=-99;
double tausT_HT=-99;
double tausL_invariantMass=-99;
double tausF_invariantMass=-99;
double tausT_invariantMass=-99;
double tausF_minDeltaR = -99;
double tausL_minDeltaR = -99;
double tausT_minDeltaR = -99;
double tausF_leptonsT_transMass = -99;
double tausL_leptonsT_transMass = -99;
double tausT_leptonsT_transMass = -99;
double tausF_leptonsT_invariantMass = -99;
double tausL_leptonsT_invariantMass = -99;
double tausT_leptonsT_invariantMass = -99;
int tausF_leptonsT_chargeSum = -99;
double tausF_leptonsTMVA_minDeltaR = -99;
double tausT_leptonsTMVA_minDeltaR = -99;
double tausL_leptonsTMVA_minDeltaR = -99;
double tauL_1pt = -99;
double tauL_1eta = -99;
double tauL_1phi = -99;
double tauL_2pt = -99;
double tauL_2eta = -99;
double tauL_2phi = -99;
double tauL_3pt = -99;
double tauL_3eta = -99;
double tauL_3phi = -99;

int toptagger_num=-99;
double toptagger_MHT = -99;
double toptagger_HT = -99;
double toptagger_invariantMass = -99;
double toptagger_transMass = -99;
double toptagger_minDeltaR_v1 = -99;

double toptagger_1pt=-99;
double toptagger_1eta = -99;
double toptagger_1phi = -99;
double toptagger_2pt=-99;
double toptagger_2eta=-99;
double toptagger_2phi=-99;
double toptagger_3pt = -99;
double toptagger_3eta = -99;
double toptagger_3phi = -99;
double toptagger_minDeltaR=-99;
double toptagger_maxDeltaR=-99;
double toptagger_scoreAllTops=-99;
double toptagger_leptonsMVAT_minDeltaR=-99;
//
//
int   jetsL_number=-99;
int   forwardJets_num=-99;
int   bjetsL_num=-99;
int   bjetsM_num=-99;
int   bjetsT_num=-99;
int   NumSelWJets=-99;
int   NumSelTopJets=-99;
int   NVertices=-99;
double jetsL_HT=-99;
double bjetsT_HT=-99;
double bjetsM_HT=-99;
double bjetsL_HT=-99;
double bjetsT_MHT=-99;
double bjetsM_MHT=-99;
double bjetsL_MHT=-99;
double jetsL_MHT=-99;
double PUWeight= -99;
double PUWeightUP= -99;
double PUWeightDOWN= -99;
int EVENT_event=-99;
int EVENT_run=-99;
int EVENT_lumiBlock=-99;
double EVENT_genHT=-99;
double Met_pt = -99.;
double Met_phi = -99.;
int getTrueNumInteractions=-99;
double w_for = -99;
double w_forUp = -99;
double w_forDown = -99;
double w_topJet = -99;
double w_topJetUp = -99;
double w_topJetDown = -99;
double w_WJet   = -99;
double w_WJetUp = -99;
double w_WJetDown = -99;
double w_Muon1  = -99;
double w_Muon2  = -99;
double w_Muon1Up  = -99;
double w_Muon2Up  = -99;
double w_Muon1Down  = -99;
double w_Muon2Down  = -99;
double w_Electron1  = -99;
double w_Electron2  = -99;
double w_Electron1Up  = -99;
double w_Electron2Up  = -99;
double w_Electron1Down  = -99;
double w_Electron2Down  = -99;
double w_TrigMuon= -99;
double w_TrigMuonUp= -99;
double w_TrigMuonDown= -99;
double w_TrigElec= -99;
double w_TrigElecUp= -99;
double w_TrigElecDown= -99;
double w_ZToNuNu= -99;
double w_ZToNuNuUp= -99;
double w_ZToNuNuDown= -99;
double w_WToLNu= -99;
double w_WToLNuUp= -99;
double w_WToLNuDown= -99;
double w_ttbar= -99;
double w_ttbarUp= -99;
double w_ttbarDown= -99;
double w_Trig= -99;
double w_TrigUp= -99;
double w_TrigDown= -99;
double WMass = -99;
double WSubjet = -99;
double TopSoftMass = -99;
double TopSubjet = -99;
double w_Btag= -99;
double w_BtagUp= -99;
double w_BtagDown= -99;
double w_Btag1Up= -99;
double w_Btag1Down= -99;
double w_Btag2Up= -99;
double w_Btag2Down= -99;
double w_BtagLoose= -99;
double w_BtagLooseUp= -99;
double w_BtagLooseDown= -99;
double prefiringweight = -99;
double prefiringweightup = -99;
double prefiringweightdown = -99;
double puWeight = -99;
double EVENT_genWeight = -99;
double GenZPt=-99.;
double GenWPt=-99.;

double genWeight= -99;
double w_QCDUp = -99;
double w_QCDDown = -99;
double w_PDFUp = -99;
double w_PDFDown = -99;
int dQuark=0;
int uQuark=0;
int sQuark=0;
int cQuark=0;
int bQuark=0;
int tQuark=0;
double TriggeringElePt  = -1.;
double TriggeringMuoPt  = -1.;
double TriggeringEleEta = -1.;
double TriggeringMuoEta = -1.;
double TransverseMassMetTop = -99;

/*}}}*/
