#include "weightCal.h"
// #include "TauPOG/TauIDSFs/src/TauIDSFTool.cc"
// #include "../../TauPOG/TauIDSFs/interface/TauIDSFTool.h"
#include "TauPOG/TauIDSFs/interface/TauIDSFTool.h"
// #include "correction.h"

using namespace correction;

Double_t calMuonIDSF(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &muonsT, const TH2D *MuonIDSF, const Int_t type, Bool_t isMuon, Bool_t isData)
{
	Double_t muonIDSF = 1.0;
	if (!isData)
	{
		for (UInt_t i = 0; i < muonsT.GetSize(); i++)
		{
			Int_t binx;
			if (isMuon)
			{
				binx = MuonIDSF->GetXaxis()->FindBin(fabs(muonsT.At(i).Eta())); // fabs for muons, no abs for electron
			}
			else
			{
				binx = MuonIDSF->GetXaxis()->FindBin((muonsT.At(i).Eta())); // fabs for muons, no abs for electron
			}
			Int_t biny = MuonIDSF->GetYaxis()->FindBin(muonsT.At(i).Pt());
			Double_t iMuonSF = MuonIDSF->GetBinContent(binx, biny);
			// Double_t iMuonSF_up = iMuonSF+ MuonIDSF->GetBinErrorUp(binx, biny);
			// Double_t iMuonSF_down = iMuonSF-MuonIDSF->GetBinErrorLow(binx, biny);
			Double_t iMuonSF_up = iMuonSF + MuonIDSF->GetBinError(binx, biny);
			Double_t iMuonSF_down = iMuonSF - MuonIDSF->GetBinError(binx, biny);
			if (type == 0)
			{
				muonIDSF *= iMuonSF;
			}
			else if (type == 1)
			{
				muonIDSF *= iMuonSF_up;
			}
			else if (type == 2)
			{
				muonIDSF *= iMuonSF_down;
			}
		}
		if (muonIDSF == 0)
			muonIDSF = 1.0;
	}
	return muonIDSF;
}

Double_t calEleMVA_IDSF(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &elesMVAT, const TH2D *EleIDSF)
{
	Double_t eleIDSF = 1.0;
	for (UInt_t i = 0; i < elesMVAT.GetSize(); i++)
	{
		Int_t binx = EleIDSF->GetXaxis()->FindBin(elesMVAT.At(i).Eta());
		// why no abs here? in the 2D the eta is not
		Int_t biny = EleIDSF->GetYaxis()->FindBin(elesMVAT.At(i).Pt());
		eleIDSF *= EleIDSF->GetBinContent(binx, biny);
	}
	if (eleIDSF == 0)
		eleIDSF = 1.0;
	return eleIDSF;
}

Double_t calTau_IDSF(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &tausT, const TTreeReaderArray<Int_t> &tausT_genPartFlav, const TString era, const std::string &unc_jet, const std::string &unc_e, const std::string &unc_mu)
{
	// TauIDSFTool VSjetIDTool = TauIDSFTool(era,"DeepTau2017v2p1VSjet","Medium", false, false, true);
	TauIDSFTool VSjetIDTool = TauIDSFTool(era.Data(), "DeepTau2017v2p1VSjet", "Medium", false, false, true);
	TauIDSFTool VSeIDTool = TauIDSFTool(era.Data(), "DeepTau2017v2p1VSe", "VVLoose", false, false, true);					// no VVVLoose histogram in file, use VVLoose and add +3% uncertainty (recommended by TAU POG conveners)
	TauIDSFTool VSmuIDTool = TauIDSFTool(fromULtoReReco(era.Data()), "DeepTau2017v2p1VSmu", "VLoose", false, false, false); // No UL measurement for these SFs? UL file is not present! Also, set otherVSlepWP to false, VLoose histogram is available

	Double_t tauIDSF = 1.0;
	for (UInt_t i = 0; i < tausT.GetSize(); i++)
	{
		Double_t VSjetSF = VSjetIDTool.getSFvsPT(tausT.At(i).Pt(), tausT_genPartFlav.At(i), unc_jet);
		Double_t VSeSF = VSeIDTool.getSFvsEta(fabs(tausT.At(i).Eta()), tausT_genPartFlav.At(i), unc_e);
		Double_t VSmuSF = VSmuIDTool.getSFvsEta(fabs(tausT.At(i).Eta()), tausT_genPartFlav.At(i), unc_mu);

		tauIDSF *= VSjetSF;
		tauIDSF *= VSeSF;
		tauIDSF *= VSmuSF;
	}
	if (tauIDSF == 0)
		tauIDSF = 1.0;
	return tauIDSF;
}

Double_t getHLTweight(const Double_t jets_HT, const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &jets, const TH2D *TriggerSF, const TH2D *TriggerSFunc, Bool_t isData)
{
	Double_t triggerSF = 1.0;
	if (!isData && TriggerSF->GetEntries() != 0)
	{
		Int_t binx = TriggerSF->GetXaxis()->FindBin(jets_HT);
		Int_t biny = TriggerSF->GetYaxis()->FindBin(jets.GetSize());
		if (jets.GetSize() > 11)
			triggerSF = 1.0;
		else if (TriggerSFunc->GetBinContent(binx, biny) / TriggerSF->GetBinContent(binx, biny) > 0.50)
			triggerSF = 1.0;
		//???is this setting resonable?
		else
			triggerSF = TriggerSF->GetBinContent(binx, biny);
		if (triggerSF == 0)
			triggerSF = 1.0;
	}
	else
	{
		triggerSF = 1.0;
	}
	return triggerSF;
}

Double_t calTau_IDSF_new(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &tausT, const TTreeReaderArray<Int_t> &tausT_decayMode, const TTreeReaderArray<Int_t> &tausT_genPartFlav, correction::CorrectionSet *cset, std::string syst_vsjet, std::string syst_vsmu, std::string syst_vsele, Bool_t isData)
{
	// read from official json file
	// syst='nom', 'up' or  'down'.
	Double_t sf = 1.0;
	if (!isData)
	{
		auto corr_vsjet = cset->at("DeepTau2017v2p1VSjet");
		auto corr_vsmu = cset->at("DeepTau2017v2p1VSmu");
		auto corr_vsele = cset->at("DeepTau2017v2p1VSe");
		for (UInt_t i = 0; i < tausT.GetSize(); i++)
		{
			Double_t ipt = tausT.At(i).Pt();
			Int_t idecayMode = tausT_decayMode.At(i);
			Int_t igenMatch = tausT_genPartFlav.At(i);
			Double_t ieta = tausT.At(i).Eta();
			Double_t sf_vsJet = corr_vsjet->evaluate({ipt, idecayMode, igenMatch, "Medium", syst_vsjet, "pt"}); //???not sure if is should be 5 or the genmatch of the tau
			Double_t sf_vsmu = corr_vsmu->evaluate({ieta, igenMatch, "VLoose", syst_vsmu});
			Double_t sf_vsele = corr_vsele->evaluate({ieta, igenMatch, "VVLoose", syst_vsele}); // no VVVLoose histogram in file, use VVLoose and add +3% uncertainty (recommended by TAU POG conveners)
			sf *= sf_vsJet;
			sf *= sf_vsmu;
			sf *= sf_vsele;
		}
	}
	return sf;
}

Double_t calBtagShapeWeight(const TTreeReaderArray<ROOT::Math::PtEtaPhiMVector> &jets, const TTreeReaderArray<Int_t> &jets_flavour, const TTreeReaderArray<Double_t> &jets_btag, correction::CorrectionSet *cset_btag, Bool_t isData)
{
	// https://twiki.cern.ch/twiki/bin/view/CMS/BTagCalibration#Using_b_tag_scale_factors_in_you
	// https://gitlab.cern.ch/cms-nanoAOD/jsonpog-integration/-/blob/master/examples/btvExample.py
	Double_t sf = 1.0;
	if (!isData)
	{
		auto corr_deepJet = cset_btag->at("deepJet_shape");
		for (UInt_t j = 0; j < jets.GetSize(); j++)
		{
			Double_t ijetSF = corr_deepJet->evaluate({"central", jets_flavour.At(j), std::abs(jets.At(j).Eta()), jets.At(j).Pt(), jets_btag.At(j)});
			sf *= ijetSF;
		}
	}
	// std::cout << "btagSF = " << sf << "\n";
	return sf;
}