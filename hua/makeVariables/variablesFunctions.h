
#include <TROOT.h>
#include "TLorentzVector.h"
#include <Math/Vector4D.h>
#include "TH1D.h"
#include <vector>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

Double_t DeltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2);

Double_t deltRmin(const Double_t eta1, const Double_t phi1, const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &LeptonsMVAF);

void copy_TTreeReaderArray_toVector(const TTreeReaderArray<double> &array, std::vector<Double_t> &vec);

Double_t HTcalculator(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &SelectedJets);
Double_t HTcalculator(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets);
Double_t MHTcalculator(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets);
Double_t energyCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

Double_t pzCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

/// it seems we cant not use TTreeReaderArray as input parameter
// yes we can , just have to pass by address
Double_t MHTcalculator(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &SelectedJets);
Double_t rationHT_4toRestCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

// Double_t InvariantMassCalculator(std::vector<ROOT::Math::PtEtaPhiMVector> SelectedJets) ;
Double_t InvariantMassCalculator(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

Double_t InvariantMassCalculator(std::vector<ROOT::Math::PtEtaPhiMVector> SelectedJets);

Double_t InvariantMass2SysCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &a,
                              const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &b);

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

Double_t TransEnergyCal(const ROOT::Math::PtEtaPhiMVector SelectedJets);

Double_t TransEnergySysCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

Double_t TransEnergySysCal(const std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

Double_t TransMassCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

Double_t TransMassSysCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &Jets, const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &Leptons);

Double_t MinDeltaRCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &Jets,
                      const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &Leptons);

Double_t MinDeltaRSingleCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &Jets);

Double_t AverageDeltaRCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &SelectedJets);

Double_t bscoreSumOf4largestCal(const TTreeReaderArray<Double_t> &SelectedJetsBTags);
Double_t bscoreMultiOf4largestCal(const TTreeReaderArray<Double_t> &SelectedJetsBTags);

Double_t BScoreAllJetsCal(const TTreeReaderArray<Double_t> &SelectedJetsBTags);
Double_t bScoreMultiCal(const TTreeReaderArray<Double_t> &SelectedJetsBTags);
Int_t calGenTauNum(const TTreeReaderArray<Int_t> &tausT_genPartFlav);

Int_t getTauProng(TTreeReaderArray<Int_t> &tausT_decayMode);

void SpheriltyAplanarityCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &SelectedJets, Double_t &Spher, Double_t &Apla);

// Double_t TopScoreAllTopsCal(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector>& SelectedTops) ;
// Double_t init = 0;
// for (UInt_t j = 0; j < SelectedTops.GetSize(); ++j) {
// init = init + TopTagger_discriminator_->at(j);
// }
// return init;
// }
