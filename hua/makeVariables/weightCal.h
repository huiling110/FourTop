#include <TROOT.h>
#include "TLorentzVector.h"
#include "TH1D.h"
#include "TH2D.h"
#include <vector>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>


Double_t calMuonIDSF( const TTreeReaderArray<TLorentzVector>& muonsT, const TH2D* MuonIDSF  );
Double_t calEleMVA_IDSF( const TTreeReaderArray<TLorentzVector>& eleMVAT, const TH2D* EleIDSF  );
Double_t getHLTweight( const Double_t jets_HT, const TTreeReaderArray<TLorentzVector>& jets );