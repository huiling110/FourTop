#include "weightCal.h"
// #include "TauPOG/TauIDSFs/src/TauIDSFTool.cc"
// #include "../../TauPOG/TauIDSFs/interface/TauIDSFTool.h"
#include "TauPOG/TauIDSFs/interface/TauIDSFTool.h"


Double_t calMuonIDSF( const TTreeReaderArray<TLorentzVector>& muonsT, const TH2D* MuonIDSF, const Int_t type, Bool_t isMuon  ){
	Double_t muonIDSF = 1.0;	
	for (UInt_t i = 0; i < muonsT.GetSize(); i++) {
		Int_t binx;
		if ( isMuon ){
			binx = MuonIDSF->GetXaxis()->FindBin(fabs(muonsT.At(i).Eta()));//fabs for muons, no abs for electron
		}else{
			binx = MuonIDSF->GetXaxis()->FindBin((muonsT.At(i).Eta()));//fabs for muons, no abs for electron
		}
		Int_t biny = MuonIDSF->GetYaxis()->FindBin(muonsT.At(i).Pt());
		Double_t iMuonSF = MuonIDSF->GetBinContent(binx, biny);
		// Double_t iMuonSF_up = iMuonSF+ MuonIDSF->GetBinErrorUp(binx, biny);
		// Double_t iMuonSF_down = iMuonSF-MuonIDSF->GetBinErrorLow(binx, biny);
		Double_t iMuonSF_up = iMuonSF+ MuonIDSF->GetBinError(binx, biny);
		Double_t iMuonSF_down = iMuonSF-MuonIDSF->GetBinError(binx, biny);
		if( type==0 ){
			muonIDSF *= iMuonSF;
		} else if( type==1 ){
			muonIDSF *= iMuonSF_up;
		}else if ( type==2 ){
			muonIDSF *= iMuonSF_down;
		}
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

Double_t calTau_IDSF(  const TTreeReaderArray<TLorentzVector>& tausT,  const TTreeReaderArray<Int_t>& tausT_genPartFlav, const TString era){
	// TauIDSFTool VSjetIDTool = TauIDSFTool(era,"DeepTau2017v2p1VSjet","Medium", false, false, true);
	TauIDSFTool VSjetIDTool = TauIDSFTool(era.Data(),"DeepTau2017v2p1VSjet","Medium", false, false, true);
	TauIDSFTool VSeIDTool = TauIDSFTool(era.Data(),"DeepTau2017v2p1VSe","VVLoose", false, false, true); //no VVVLoose histogram in file, use VVLoose and add +3% uncertainty (recommended by TAU POG conveners)
	TauIDSFTool VSmuIDTool = TauIDSFTool(fromULtoReReco(era.Data()),"DeepTau2017v2p1VSmu","VLoose", false, false, false); //No UL measurement for these SFs? UL file is not present! Also, set otherVSlepWP to false, VLoose histogram is available

	Double_t tauIDSF = 1.0;
	for (UInt_t i = 0; i < tausT.GetSize(); i ++) {
		Double_t VSjetSF = VSjetIDTool.getSFvsPT( tausT.At(i).Pt(), tausT_genPartFlav.At(i), "");
		Double_t VSeSF = VSeIDTool.getSFvsEta(fabs(tausT.At(i).Eta()), tausT_genPartFlav.At(i), "");
		Double_t VSmuSF = VSmuIDTool.getSFvsEta(fabs(tausT.At(i).Eta()), tausT_genPartFlav.At(i), "");

		tauIDSF *= VSjetSF;
		tauIDSF *= VSeSF;
		tauIDSF *= VSmuSF;
	}
	if (tauIDSF == 0) tauIDSF = 1.0;
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