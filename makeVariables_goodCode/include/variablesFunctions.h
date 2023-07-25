#ifndef VARIABLESFUNCTION_H
#define VARIABLESFUNCTION_H

#include <TROOT.h>
#include "TLorentzVector.h"
#include <Math/Vector4D.h>
#include "TH1D.h"
#include "TH2D.h"
#include <vector>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

#include "correction.h"

void copy_TTreeReaderArray_toVector(const TTreeReaderArray<Int_t> &array, std::vector<Int_t> &vec);
void copy_TTreeReaderArray_toVector(const TTreeReaderArray<Double_t> &array, std::vector<Double_t> &vec);
// {
// 	for (UInt_t i = 0; i < array.GetSize(); i++)
// 	{
// 		vec.push_back(array.At(i));
// 	}
// };

Double_t DeltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2);

Double_t deltRmin(const Double_t eta1, const Double_t phi1, const std::vector<ROOT::Math::PtEtaPhiMVector> &LeptonsMVAF);


Double_t HTcalculator(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets);
Double_t HTcalculator(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets);
Double_t MHTcalculator(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets);
Double_t energyCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

Double_t pzCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

/// it seems we cant not use TTreeReaderArray as input parameter
// yes we can , just have to pass by address
Double_t rationHT_4toRestCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

// Double_t InvariantMassCalculator(std::vector<ROOT::Math::PtEtaPhiMVector> SelectedJets) ;
Double_t InvariantMassCalculator(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets);


Double_t InvariantMass2SysCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &a,
                              const std::vector<ROOT::Math::PtEtaPhiMVector> &b);

// Int_t ChargeSum(const std::vector<Int_t> SelectedElectronsMVATIndex, Int_t type) ;
// Int_t charge_sum = 0;
// for (UInt_t j = 0; j < SelectedElectronsMVATIndex.size(); ++j) {
// if (type == 0)
// charge_sum += patElectron_charge_->at(j);
// charge_sum += patElectron_charge_->at(SelectedElectronsMVATIndex[j]);
// if (type == 1)
// charge_sum += Tau_charge_->at(SelectedElectronsMVATIndex[j]);
// if (type == 2)
// charge_sum += Muon_charge_->at(SelectedElectronsMVATIndex[j]);
// }
// return charge_sum;
// }

Double_t TransEnergyCal(const ROOT::Math::PtEtaPhiMVector& SelectedJets);


Double_t TransEnergySysCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

Double_t TransMassCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

Double_t TransMassSysCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &Jets, const std::vector<ROOT::Math::PtEtaPhiMVector> &Leptons);

Double_t MinDeltaRCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &Jets,
                      const std::vector<ROOT::Math::PtEtaPhiMVector> &Leptons);

Double_t MinDeltaRSingleCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &Jets);

Double_t AverageDeltaRCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

Double_t bscoreSumOf4largestCal(const TTreeReaderArray<Double_t> &SelectedJetsBTags);
Double_t bscoreMultiOf4largestCal(const TTreeReaderArray<Double_t> &SelectedJetsBTags);

Double_t BScoreAllJetsCal(const TTreeReaderArray<Double_t> &SelectedJetsBTags);
Double_t bScoreMultiCal(const TTreeReaderArray<Double_t> &SelectedJetsBTags);
Int_t calGenTauNum(const TTreeReaderArray<Int_t> &tausT_genPartFlav);

Int_t getTauProng(TTreeReaderArray<Int_t> &tausT_decayMode);

Int_t chargeMulCal(TTreeReaderArray<Int_t> &tausT_charge, TTreeReaderArray<Int_t> &Muon_charge_, TTreeReaderArray<Int_t> &muonsT_index, TTreeReaderArray<Int_t> &patElectron_charge_, TTreeReaderArray<Int_t> &eleMVAT_index);

void SpheriltyAplanarityCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets, Double_t &Spher, Double_t &Apla);

Double_t calMuonIDSF(const TTreeReaderArray<Double_t> &muons_pt, const TTreeReaderArray<Double_t> & muons_eta, const TH2D *MuonIDSF, const Int_t type, Bool_t isMuon, Bool_t isData);

Double_t calTau_IDSF_new(const TTreeReaderArray<Double_t> &taus_pt, const TTreeReaderArray<Double_t> &taus_eta, const TTreeReaderArray<Int_t> &tausT_decayMode, const TTreeReaderArray<UChar_t> &tausT_genPartFlav, correction::CorrectionSet *cset, std::string syst_vsjet, std::string syst_vsmu, std::string syst_vsele, Bool_t isData);

Double_t calBtagShapeWeight(const TTreeReaderArray<Double_t> &jets_pt, const TTreeReaderArray<Double_t>& jets_eta, const TTreeReaderArray<Int_t> &jets_flavour, const TTreeReaderArray<Double_t> &jets_btag, correction::CorrectionSet *cset_btag, Bool_t isData, const std::string sys);

Double_t calBtagWPMWeight(const TTreeReaderArray<Double_t> &jets_pt, const TTreeReaderArray<Double_t> &jets_eta, const TTreeReaderArray<Int_t> &jets_flavour, const TTreeReaderArray<Double_t> &jets_btag, correction::CorrectionSet *cset_btag,  TH2D* btagEff_b,  TH2D* btagEff_c,  TH2D* btagEff_l, Bool_t isData, TString era, const std::string sys);
Double_t getBtagEff(TH2D* btagEff_b, TH2D* btagEff_c,  TH2D* btagEff_l, Double_t jetPt, Double_t jetEta, Int_t jetFlavor, Int_t sys);
Double_t get2DSF(Double_t x, Double_t y,  TH2D *hist, UInt_t sys);

Double_t calBtagR(Int_t jets_number, TH1D *btagRHist);
Double_t HLTWeightCal(Double_t jets_HT, Double_t jets_6pt, Int_t bjets_num, TH2D *triggerHist1b, TH2D *triggerHist2b, TH2D *triggerHist3b, Bool_t isdata, UInt_t sys);

void copy_TTreeReaderArray_toVector(const TTreeReaderArray<Double_t> &array, std::vector<Double_t> &vec);



void getLorentzVec(const TTreeReaderArray<Double_t>& ptVec, const TTreeReaderArray<Double_t>& etaVec, const TTreeReaderArray<Double_t>& phiVec, const TTreeReaderArray<Double_t>& massVec, std::vector<ROOT::Math::PtEtaPhiMVector>& outLorVec );

// Double_t TopScoreAllTopsCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector>& SelectedTops) ;
// Double_t init = 0;
// for (UInt_t j = 0; j < SelectedTops.GetSize(); ++j) {
// init = init + TopTagger_discriminator_->at(j);
// }
// return init;
// }

#endif