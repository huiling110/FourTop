#include <TROOT.h>
#include "TLorentzVector.h"
#include "TH1D.h"
#include "TH2D.h"
#include <vector>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

#include "correction.h"

Double_t calMuonIDSF( const TTreeReaderArray<TLorentzVector>& muonsT, const TH2D* MuonIDSF , const Int_t type , Bool_t isMuon );
Double_t calEleMVA_IDSF( const TTreeReaderArray<TLorentzVector>& eleMVAT, const TH2D* EleIDSF  );
Double_t getHLTweight( const Double_t jets_HT, const TTreeReaderArray<TLorentzVector>& jets, const TH2D* TriggerSF, const TH2D* TriggerSFunc );
Double_t calTau_IDSF(  const TTreeReaderArray<TLorentzVector>& tausT,  const TTreeReaderArray<Int_t>& tausT_genPartFlav, const TString era);
Double_t calTau_IDSF_new(const TTreeReaderArray<TLorentzVector> &tausT, const TTreeReaderArray<Int_t>& tausT_decayMode, const TTreeReaderArray<Int_t> &tausT_genPartFlav, correction::CorrectionSet* cset);