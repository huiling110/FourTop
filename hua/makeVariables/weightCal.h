#include <TROOT.h>
#include "TLorentzVector.h"
#include "TH1D.h"
#include "TH2D.h"
#include <vector>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>


Double_t calMuonIDSF( const TTreeReaderArray<TLorentzVector>& muonsT, const TH2D* MuonIDSF  );