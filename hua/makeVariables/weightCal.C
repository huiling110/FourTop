#include "weightCal.h"


Double_t calMuonIDSF( const TTreeReaderArray<TLorentzVector>& muonsT, const TH2D* MuonIDSF  ){
	Double_t muonIDSF = 1.0;	
	for (UInt_t i = 0; i < muonsT.GetSize(); i++) {
		Int_t binx = MuonIDSF->GetXaxis()->FindBin(fabs(muonsT.At(i).Eta()));
		Int_t biny = MuonIDSF->GetYaxis()->FindBin(muonsT.At(i).Pt());
		muonIDSF *= MuonIDSF->GetBinContent(binx, biny);
	}
	if (muonIDSF == 0) muonIDSF = 1.0;
	return muonIDSF;
}