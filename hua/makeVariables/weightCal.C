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

Double_t calEleMVA_IDSF( const TTreeReaderArray<TLorentzVector>& elesMVAT, const TH2D* EleIDSF  ){
	Double_t eleIDSF = 1.0;
	for (UInt_t i = 0; i < elesMVAT.GetSize(); i++) { 
		Int_t binx = EleIDSF->GetXaxis()->FindBin(elesMVAT.At(i).Eta());
		//why no abs here? in the 2D the eta is not
		Int_t biny = EleIDSF->GetYaxis()->FindBin(elesMVAT.At(i).Pt());
		eleIDSF *= EleIDSF->GetBinContent(binx, biny); 
	}
	if (eleIDSF == 0) eleIDSF = 1.0;
	return eleIDSF;
}

Double_t getHLTweight( const Double_t jets_HT, const TTreeReaderArray<TLorentzVector>& jets, const TH2D* TriggerSF, const TH2D* TriggerSFunc  ){
	Double_t triggerSF = 1.0;
	Int_t binx = TriggerSF->GetXaxis()->FindBin(jets_HT);
	Int_t biny = TriggerSF->GetYaxis()->FindBin(jets.GetSize());
	if (jets.GetSize() > 11 ) triggerSF = 1.0;
	else if ( TriggerSFunc->GetBinContent(binx, biny)/TriggerSF->GetBinContent(binx, biny) > 0.50 ) triggerSF = 1.0;
	//???is this setting resonable?
	else triggerSF = TriggerSF->GetBinContent(binx, biny); 
	if (triggerSF == 0) triggerSF = 1.0;
	return triggerSF;
}