#define writeHist_forFakeRate_cxx
// The class definition in writeHist_forFakeRate.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//

#include <TH2.h>
#include <TStyle.h>

#include <assert.h>
#include <cmath>
// #include <filesystem>

#include "../src_cpp/usefulFuction.h"
#include "writeHist_forFakeRate.h"

void writeHist_forFakeRate::fillHistsVector(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
{
	if (isRegion)
	{
		eventCount_hists[vectorIndex]->Fill(.0, weight);
	}
}

void writeHist_forFakeRate::fillHistsVectorMyclass(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
{
	// if (isRegion)
	// {
	for (UInt_t i = 0; i < vectorOfVariableRegions.size(); i++)
	{
		vectorOfVariableRegions[i].fillHistVec(vectorIndex, weight, isRegion);
	}
	for (UInt_t i = 0; i < vectorOfVariableRegionsDouble.size(); i++)
	{
		vectorOfVariableRegionsDouble[i].fillHistVec(vectorIndex, weight, isRegion);
	}
	// }
}

void push_backHists(TString variable, Int_t binNum, Double_t minBin, Double_t maxBin, std::vector<TH1D *> &histsVariable, TString m_processName, std::vector<TString> &regions)
{
	for (UInt_t i = 0; i < regions.size(); i++)
	{
		TString iHistName = regions[i] + "_" + m_processName + "_" + variable;
		TH1D *temp = new TH1D(iHistName.Data(), iHistName.Data(), binNum, minBin, maxBin);
		histsVariable.push_back(temp);
	}
}

void writeHist_forFakeRate::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
}

void writeHist_forFakeRate::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
	std::cout << "option in writeHist_forFakeRate: " << option << "\n";

	// this part could be in a function for multiple uses
	// better structure my project so that these commen functionality go to one include dir
	std::vector<TString> optionVect;
	getOption(option, optionVect);
	// for (UInt_t i = 0; i < optionVect.size(); i++)
	// {
	// 	std::cout << optionVect[i] << "\n";
	// }
	m_genWeightSum = std::stod(optionVect[0].Data());
	std::cout << "m_genWeightSum: " << m_genWeightSum << "\n";
	//???maybe there is lose of accuracy due to convertion
	m_outputFolder = optionVect[1];
	m_processName = optionVect[2];
	m_isData = std::stoi(optionVect[3].Data());
	std::cout << "m_isData: " << m_isData << "\n";
	m_version = optionVect[4];
	std::cout << "m_verion: " << m_version << "\n";
	m_era = optionVect[5];
	std::cout << "m_era: " << m_era << "\n";

	// namespace fs = std::filesystem;
	// if ( !fs::exists((m_outputFolder+"variableHists"+ "_"+m_version+"/").Data() )){
	// 	fs::create_directory( (m_outputFolder+"variableHists"+ "_"+m_version+"/").Data());
	// }
	outputFile = new TFile(m_outputFolder + "variableHists" + "_" + m_version + "/" + m_processName + ".root", "RECREATE");

	std::vector<TString> regionsForVariables = {
		"1tau0lSR",
		"1tau0lCR",
		"1tau0lCRLTau",
		"1tau0lVR",
		"1tau0lVRLTau",
		"1tau0lVRLTauNotT", // 5
		"1tau0lSRGen",
		"1tau0lCRGen",
		"1tau0lCRLTauGen",
		"1tau0lVRGen",
		"1tau0lVRLTauGen", // 10
		"1tau0lVRLTauNotTgen",
	};

	push_backHists("eventCount", 2, -1, 1, eventCount_hists, m_processName, regionsForVariables);

	histsForRegions<Double_t> tausL_1pt_class{"tausL_1pt", 20, 20, 220, tausL_1pt};
	histsForRegions<Double_t> tausL_1etaAbs_class{"tausL_1etaAbs", 8, 0, 2.4, tausL_1etaAbs};
	vectorOfVariableRegionsDouble.push_back(tausL_1pt_class);
	vectorOfVariableRegionsDouble.push_back(tausL_1etaAbs_class);
	for (UInt_t ihistvec = 0; ihistvec < vectorOfVariableRegionsDouble.size(); ihistvec++)
	{
		vectorOfVariableRegionsDouble[ihistvec].initializeRegions(regionsForVariables, m_processName);
	}

	std::vector<TString> regionsEtaDivided = {
		"1tau0lCRLTau_Eta1",
		"1tau0lCRLTau_Eta2",
		"1tau0lCRLTau_Eta3",
		"1tau0lCRLTau_Eta4",
		"1tau0lCRLTauGen_Eta1",
		"1tau0lCRLTauGen_Eta2",
		"1tau0lCRLTauGen_Eta3",
		"1tau0lCRLTauGen_Eta4",

		"1tau0lCR_Eta1", // 8
		"1tau0lCR_Eta2",
		"1tau0lCR_Eta3",
		"1tau0lCR_Eta4",
		"1tau0lCRGen_Eta1", // 12
		"1tau0lCRGen_Eta2",
		"1tau0lCRGen_Eta3",
		"1tau0lCRGen_Eta4",

		"1tau0lVRLTauNotT_Eta1", // 16
		"1tau0lVRLTauNotT_Eta2",
		"1tau0lVRLTauNotT_Eta3",
		"1tau0lVRLTauNotT_Eta4",
		"1tau0lVRLTauNotTGen_Eta1",
		"1tau0lVRLTauNotTGen_Eta2",
		"1tau0lVRLTauNotTGen_Eta3",
		"1tau0lVRLTauNotTGen_Eta4",
	};
	// tausL_1pt_eta_class{"tausL_1pt", 20, 20, 220, tausL_1pt};
	tausL_1pt_eta_class.initializeRegions(regionsEtaDivided, m_processName);
}

Bool_t writeHist_forFakeRate::Process(Long64_t entry)
{
	fReader.SetLocalEntry(entry);
	// baseline selection
	Bool_t baseline = *jets_number >= 6 && *jets_6pt > 40.0 && *jets_HT > 500.0;
	if (!baseline)
	{
		return kFALSE;
	}

	// eta bining cut
	// if (!(0 < *tausL_1etaAbs && *tausL_1etaAbs <= 0.6))
	// if (!(0.6 < *tausL_1etaAbs && *tausL_1etaAbs <= 1.2))
	// if (!(1.2 < *tausL_1etaAbs && *tausL_1etaAbs <= 1.8))
	// if (!(1.8 < *tausL_1etaAbs && *tausL_1etaAbs <= 2.4))
	// return kFALSE;

	Double_t basicWeight = 1.0;
	if (!m_isData)
	{
		basicWeight = (*PUweight) * (*EVENT_prefireWeight) * (*EVENT_genWeight);
		// basicWeight = (*PUweight) * (*EVENT_prefireWeight) * (*EVENT_genWeight) * (*tauT_IDSF_weight_new);
		// basicWeight = (*PUweight) * (*EVENT_prefireWeight) * (*EVENT_genWeight) * (*muonIDSF_weight) * (*eleMVAT_IDSF_weight);
	}

	// 1tau0l CR
	Bool_t is1tau0lCR = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 0;
	Bool_t is1tau0lCRLTau = *tausL_number == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 0;
	Bool_t is1tau0lVR = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 1;
	Bool_t is1tau0lVRLTau = *tausL_number == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 1;
	Bool_t is1tau0lVRLTauNotT = *tausL_number == 1 && *tausT_number == 0 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 1;
	fillHistsVector(is1tau0lCR, 1, basicWeight);
	fillHistsVector(is1tau0lCRLTau, 2, basicWeight);
	fillHistsVector(is1tau0lVR, 3, basicWeight);
	fillHistsVector(is1tau0lVRLTau, 4, basicWeight);
	fillHistsVector(is1tau0lVRLTauNotT, 5, basicWeight);

	Bool_t isEta1 = 0 < *tausL_1etaAbs && *tausL_1etaAbs <= 0.6;
	Bool_t isEta2 = 0.6 < *tausL_1etaAbs && *tausL_1etaAbs <= 1.2;
	Bool_t isEta3 = 1.2 < *tausL_1etaAbs && *tausL_1etaAbs <= 1.8;
	Bool_t isEta4 = 1.8 < *tausL_1etaAbs && *tausL_1etaAbs <= 2.4;

	if (!m_isData)
	{
		// be blind for data in signal region
		Bool_t is1tau0lSR = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num >= 2;
		fillHistsVector(is1tau0lSR, 0, basicWeight);

		Bool_t is1tau0lSRGen = *tausT_number == 1 && *tausT_genTauNum == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num >= 2;
		Bool_t is1tau0lCRGen = *tausT_number == 1 && *tausT_genTauNum == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 0;
		Bool_t is1tau0lCRLTauGen = *tausL_number == 1 && *tausL_genTauNum == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 0;
		Bool_t is1tau0lVRGen = *tausT_number == 1 && *tausT_genTauNum == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 1;
		Bool_t is1tau0lVRLTauGen = *tausL_number == 1 && *tausL_genTauNum == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 1;
		Bool_t is1tau0lVRLTauNotTGen = *tausL_number == 1 && *tausT_number == 0 && *tausL_genTauNum == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 1;
		fillHistsVector(is1tau0lSRGen, 6, basicWeight);
		fillHistsVector(is1tau0lCRGen, 7, basicWeight);
		fillHistsVector(is1tau0lCRLTauGen, 8, basicWeight);
		fillHistsVector(is1tau0lVRGen, 9, basicWeight);
		fillHistsVector(is1tau0lVRLTauGen, 10, basicWeight);

		// CR
		fillHistsVectorMyclass(is1tau0lCRLTauGen, 8, basicWeight);
		fillHistsVectorMyclass(is1tau0lCRGen, 7, basicWeight);
		// VR
		fillHistsVectorMyclass(is1tau0lVRLTauNotTGen, 11, basicWeight);

		tausL_1pt_eta_class.fillHistVec(4, basicWeight, is1tau0lCRLTauGen && isEta1);
		tausL_1pt_eta_class.fillHistVec(5, basicWeight, is1tau0lCRLTauGen && isEta2);
		tausL_1pt_eta_class.fillHistVec(6, basicWeight, is1tau0lCRLTauGen && isEta3);
		tausL_1pt_eta_class.fillHistVec(7, basicWeight, is1tau0lCRLTauGen && isEta4);
		tausL_1pt_eta_class.fillHistVec(12, basicWeight, is1tau0lCRGen && isEta1);
		tausL_1pt_eta_class.fillHistVec(13, basicWeight, is1tau0lCRGen && isEta2);
		tausL_1pt_eta_class.fillHistVec(14, basicWeight, is1tau0lCRGen && isEta3);
		tausL_1pt_eta_class.fillHistVec(15, basicWeight, is1tau0lCRGen && isEta4);
		// VR
		tausL_1pt_eta_class.fillHistVec(20, basicWeight, is1tau0lVRLTauNotTGen && isEta1);
		tausL_1pt_eta_class.fillHistVec(21, basicWeight, is1tau0lVRLTauNotTGen && isEta2);
		tausL_1pt_eta_class.fillHistVec(22, basicWeight, is1tau0lVRLTauNotTGen && isEta3);
		tausL_1pt_eta_class.fillHistVec(23, basicWeight, is1tau0lVRLTauNotTGen && isEta4);
	}
	else
	{
		fillHistsVectorMyclass(is1tau0lCRLTau, 2, basicWeight);
		fillHistsVectorMyclass(is1tau0lCR, 1, basicWeight);
		// VR
		fillHistsVectorMyclass(is1tau0lVRLTauNotT, 5, basicWeight);

		tausL_1pt_eta_class.fillHistVec(0, basicWeight, is1tau0lCRLTau && isEta1);
		tausL_1pt_eta_class.fillHistVec(1, basicWeight, is1tau0lCRLTau && isEta2);
		tausL_1pt_eta_class.fillHistVec(2, basicWeight, is1tau0lCRLTau && isEta3);
		tausL_1pt_eta_class.fillHistVec(3, basicWeight, is1tau0lCRLTau && isEta4);
		tausL_1pt_eta_class.fillHistVec(8, basicWeight, is1tau0lCR && isEta1);
		tausL_1pt_eta_class.fillHistVec(9, basicWeight, is1tau0lCR && isEta2);
		tausL_1pt_eta_class.fillHistVec(10, basicWeight, is1tau0lCR && isEta3);
		tausL_1pt_eta_class.fillHistVec(11, basicWeight, is1tau0lCR && isEta4);
		// VR
		tausL_1pt_eta_class.fillHistVec(16, basicWeight, is1tau0lVRLTauNotT && isEta1);
		tausL_1pt_eta_class.fillHistVec(17, basicWeight, is1tau0lVRLTauNotT && isEta2);
		tausL_1pt_eta_class.fillHistVec(18, basicWeight, is1tau0lVRLTauNotT && isEta3);
		tausL_1pt_eta_class.fillHistVec(19, basicWeight, is1tau0lVRLTauNotT && isEta4);
	}

	return kTRUE;
}

void writeHist_forFakeRate::SlaveTerminate()
{
	// The SlaveTerminate() function is called after all entries or objects
	// have been processed. When running with PROOF SlaveTerminate() is called
	// on each slave server.
}

void writeHist_forFakeRate::Terminate()
{
// The Terminate() function is the last function to be called during
// a query. It always runs on the client, it can be used to present
// the results graphically or save the results to file.
#include "lumiAndCrossSection.h"
	Double_t processScale = 1.0;
	if (!m_isData)
	{
		std::cout << m_processName << ": " << lumiMap[m_era] << " " << crossSectionMap[m_processName] << " " << m_genWeightSum << "\n";
		processScale = ((lumiMap[m_era] * crossSectionMap[m_processName]) / m_genWeightSum);
	}

	for (UInt_t j = 0; j < eventCount_hists.size(); j++)
	{

		std::cout << j << "\n";
		eventCount_hists[j]->Scale(processScale);
		eventCount_hists[j]->Print();
	}

	for (UInt_t ihists = 0; ihists < vectorOfVariableRegionsDouble.size(); ihists++)
	{
		vectorOfVariableRegionsDouble[ihists].histsScale(processScale);
		// vectorOfVariableRegionsDouble[ihists].histsPrint();
	}
	tausL_1pt_eta_class.histsScale(processScale);
	Info("Terminate", "outputFile here: %s", outputFile->GetName());
	outputFile->Write();
	outputFile->Close();
}