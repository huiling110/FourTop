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

// #include "./test/BTagEntry.h"
// #include "test/BTagCalibration.h"
// #include "test/BTagCalibrationReader.h"

Double_t calMuonIDSF(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &muonsT, const TH2D *MuonIDSF, const Int_t type, Bool_t isMuon, Bool_t isData);
Double_t calEleMVA_IDSF(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &eleMVAT, const TH2D *EleIDSF);
Double_t getHLTweight(const Double_t jets_HT, const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &jets, const TH2D *TriggerSF, const TH2D *TriggerSFunc, Bool_t isData);
Double_t calTau_IDSF(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &tausT, const TTreeReaderArray<Int_t> &tausT_genPartFlav, const TString era);
Double_t calTau_IDSF_new(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &tausT, const TTreeReaderArray<Int_t> &tausT_decayMode, const TTreeReaderArray<Int_t> &tausT_genPartFlav, correction::CorrectionSet *cset, std::string syst_vsjet, std::string syst_vsmu, std::string syst_vsele, Bool_t isData);