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

Double_t get2DSF(Double_t x, Double_t y, TH2D *hist);
Double_t calMuonIDSF(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &muonsT, const TH2D *MuonIDSF, const Int_t type, Bool_t isMuon, Bool_t isData);
Double_t calEleMVA_IDSF(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &eleMVAT, const TH2D *EleIDSF);
Double_t getHLTweight(const Double_t jets_HT, const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &jets, const TH2D *TriggerSF, const TH2D *TriggerSFunc, Bool_t isData);
Double_t calTau_IDSF(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &tausT, const TTreeReaderArray<Int_t> &tausT_genPartFlav, const TString era);
Double_t calTau_IDSF_new(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &tausT, const TTreeReaderArray<Int_t> &tausT_decayMode, const TTreeReaderArray<Int_t> &tausT_genPartFlav, correction::CorrectionSet *cset, std::string syst_vsjet, std::string syst_vsmu, std::string syst_vsele, Bool_t isData);
Double_t calBtagShapeWeight(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &jets, const TTreeReaderArray<Int_t> &jets_flavour, const TTreeReaderArray<Double_t> &jets_btag, correction::CorrectionSet *cset_btag, Bool_t isData);

Double_t HLTWeightCal(Double_t jets_HT, Double_t jets_6pt, Int_t bjets_num, TH2D *triggerHist1b, TH2D *triggerHist2b, TH2D *triggerHist3b, Bool_t isdata);