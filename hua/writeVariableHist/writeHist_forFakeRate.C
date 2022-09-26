#define writeHist_fordataMC_cxx
// The class definition in writeHist_fordataMC.h has been generated automatically
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
#include "writeHist_fordataMC.h"

void writeHist_fordataMC::fillHistsVector(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
{
	if (isRegion)
	{
		eventCount_hists[vectorIndex]->Fill(.0, weight);
	}
}

void writeHist_fordataMC::fillHistsVectorMyclass(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
{
	if (isRegion)
	{
		for (UInt_t i = 0; i < vectorOfVariableRegions.size(); i++)
		{
			vectorOfVariableRegions[i].fillHistVec(vectorIndex, weight);
		}
		for (UInt_t i = 0; i < vectorOfVariableRegionsDouble.size(); i++)
		{
			vectorOfVariableRegionsDouble[i].fillHistVec(vectorIndex, weight);
		}
	}
}

void push_backHists(TString variable, Int_t binNum, Double_t minBin, Double_t maxBin, std::vector<TH1D *> &histsVariable, TString m_processName, std::vector<TString> &regions)
{
	// std::array<TString, 11> regions = {"1tau0lSR", "1tau0lCR", "1tau0lVR", "1tau0lCR2", "1tau0lCR3", "1tau0lCR4", "1tau1lSR", "1tau1lCR0", "1tau1lCR1", "1tau1lCR2", "1tau1lCR3"};
	// chain.Add(inputFile + "outTree_4.root");
	for (UInt_t i = 0; i < regions.size(); i++)
	{
		TString iHistName = regions[i] + "_" + m_processName + "_" + variable;
		TH1D *temp = new TH1D(iHistName.Data(), iHistName.Data(), binNum, minBin, maxBin);
		histsVariable.push_back(temp);
	}
}

void writeHist_fordataMC::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
}

void writeHist_fordataMC::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
	std::cout << "option in writeHist_fordataMC: " << option << "\n";

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
	// outputFile = new TFile(m_outputFolder + "variableHists" + "_" + m_version + "/" + m_processName + "_variableHists.root", "RECREATE");
	outputFile = new TFile(m_outputFolder + "variableHists" + "_" + m_version + "/" + m_processName + ".root", "RECREATE");

	std::vector<TString> regionsForVariables = {"1tau0lSR", "1tau0lCR", "1tau0lVR", "1tau0lCR2", "1tau0lCR3", "1tau0lCR4", "1tau1lSR", "1tau1lCR0", "1tau1lCR1", "1tau1lCR2", "1tau1lCR3"};
	push_backHists("eventCount", 2, -1, 1, eventCount_hists, m_processName, regionsForVariables);

	vectorOfVariableRegions.clear();
	// histsForRegions eventCount_class{"eventCount", 2, -1.0, 1.0};
	histsForRegions<Int_t> jets_number_class{"jets_number", 10, 6, 15, jets_number};
	histsForRegions<Int_t> bjetsM_number_class{"bjetsM_number", 5, 0, 5, bjetsM_num};
	// vectorOfVariableRegions.push_back(eventCount_class);
	vectorOfVariableRegions.push_back(jets_number_class);
	vectorOfVariableRegions.push_back(bjetsM_number_class);

	histsForRegions<Double_t> jets_1pt_class{"jets_1pt", 10, 100, 600, jets_1pt};
	histsForRegions<Double_t> jets_2pt_class{"jets_2pt", 10, 50, 600, jets_2pt};
	histsForRegions<Double_t> jets_3pt_class{"jets_3pt", 10, 50, 500, jets_3pt};
	histsForRegions<Double_t> jets_4pt_class{"jets_4pt", 10, 25, 300, jets_4pt};
	histsForRegions<Double_t> jets_5pt_class{"jets_5pt", 10, 25, 250, jets_5pt};
	histsForRegions<Double_t> jets_6pt_class{"jets_6pt", 10, 25, 180, jets_6pt};
	histsForRegions<Double_t> jets_HT_class{"jets_HT", 10, 100, 1600, jets_HT};
	histsForRegions<Double_t> jets_bScore_class{"jets_bScore", 10, 0, 2, jets_bScore};
	histsForRegions<Double_t> jets_rationHT_4toRest_class{"jets_rationHT_4toRest", 10, 0, 10, jets_rationHT_4toRest};
	histsForRegions<Double_t> bjetsM_HT_class{"bjetsM_HT", 10, 25, 300, bjetsM_HT};
	histsForRegions<Double_t> bjetsM_MHT_class{"bjetsM_MHT", 10, 25, 300, bjetsM_HT};
	histsForRegions<Double_t> bjetsM_invariantMass_class{"bjetsM_invariantMass", 10, 25, 300, bjetsM_invariantMass};
	histsForRegions<Double_t> bjetsM_1pt_class{"bjetsM_1pt", 10, 25, 300, bjetsM_1pt};
	histsForRegions<Double_t> tausT_1pt_class{"tausT_1pt", 20, 20, 200, tausT_1pt};
	histsForRegions<Double_t> tausT_1eta_class{"tausT_1eta", 10, 0, 3, tausT_1eta};
	histsForRegions<Double_t> tausT_1phi_class{"tausT_1phi", 10, 0, 3, tausT_1phi};
	// histsForRegions<Double_t> {"", 10, , , };
	// histsForRegions<Double_t> {"", 10, , , };
	vectorOfVariableRegionsDouble.push_back(jets_1pt_class);
	vectorOfVariableRegionsDouble.push_back(jets_2pt_class);
	vectorOfVariableRegionsDouble.push_back(jets_3pt_class);
	vectorOfVariableRegionsDouble.push_back(jets_4pt_class);
	vectorOfVariableRegionsDouble.push_back(jets_5pt_class);
	vectorOfVariableRegionsDouble.push_back(jets_6pt_class);
	vectorOfVariableRegionsDouble.push_back(jets_HT_class);
	vectorOfVariableRegionsDouble.push_back(jets_bScore_class);
	vectorOfVariableRegionsDouble.push_back(jets_rationHT_4toRest_class);
	vectorOfVariableRegionsDouble.push_back(bjetsM_HT_class);
	vectorOfVariableRegionsDouble.push_back(bjetsM_MHT_class);
	vectorOfVariableRegionsDouble.push_back(bjetsM_invariantMass_class);
	vectorOfVariableRegionsDouble.push_back(tausT_1pt_class);
	vectorOfVariableRegionsDouble.push_back(tausT_1eta_class);
	vectorOfVariableRegionsDouble.push_back(tausT_1phi_class);
	vectorOfVariableRegionsDouble.push_back(bjetsM_1pt_class);
	// vectorOfVariableRegionsDouble.push_back();

	for (UInt_t ihistvec = 0; ihistvec < vectorOfVariableRegions.size(); ihistvec++)
	{
		vectorOfVariableRegions[ihistvec].initializeRegions(regionsForVariables, m_processName);
	}
	for (UInt_t ihistvec = 0; ihistvec < vectorOfVariableRegionsDouble.size(); ihistvec++)
	{
		vectorOfVariableRegionsDouble[ihistvec].initializeRegions(regionsForVariables, m_processName);
	}
}

Bool_t writeHist_fordataMC::Process(Long64_t entry)
{
	fReader.SetLocalEntry(entry);
	Double_t basicWeight = 1.0;
	if (!m_isData)
	{
		// basicWeight = (*EVENT_genWeight);
		// basicWeight = (*EVENT_prefireWeight) * (*EVENT_genWeight);
		basicWeight = (*PUweight) * (*EVENT_prefireWeight) * (*EVENT_genWeight);
		// basicWeight = (*PUweight) * (*EVENT_prefireWeight) * (*EVENT_genWeight) * (*tauT_IDSF_weight_new);
		// basicWeight = (*PUweight) * (*EVENT_prefireWeight) * (*EVENT_genWeight) * (*muonIDSF_weight) * (*eleMVAT_IDSF_weight);
		// std::cout << "muonIDSF_weight=" << *muonIDSF_weight << " "
		//   << "eleMVAT_IDSF_weight=" << *eleMVAT_IDSF_weight << "tauT_IDSF_weight_new=" << *tauT_IDSF_weight_new << "\n";
	}
	// std::cout << "event weight=" << basicWeight << "\n";

	// baseline selection
	Bool_t baseline = *jets_number >= 6 && *jets_6pt > 40.0 && *jets_HT > 500.0;
	if (!baseline)
	{
		return kFALSE;
	}

	// 1tau0l SR
	if (!m_isData)
	{
		// be blind for data in signal region
		Bool_t is1tau0lSR = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num >= 2;
		Bool_t is1tau1lSR = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number >= 7 && *bjetsM_num >= 2;
		fillHistsVectorMyclass(is1tau0lSR, 0, basicWeight);
		fillHistsVectorMyclass(is1tau1lSR, 6, basicWeight);
		fillHistsVector(is1tau0lSR, 0, basicWeight);
		fillHistsVector(is1tau1lSR, 6, basicWeight);
	}
	// std::vector<TString> regionsForVariables = {"1tau0lSR", "1tau0lCR", "1tau0lVR", "1tau0lCR2", "1tau0lCR3", "1tau0lCR4", "1tau1lSR", "1tau1lCR0", "1tau1lCR1", "1tau1lCR2", "1tau1lCR3"};

	// 1tau0l CR
	Bool_t is1tau0lCR = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 0;
	Bool_t is1tau0lVR = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 1;
	Bool_t is1tau0lCR2 = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number < 8 && *bjetsM_num >= 2;
	Bool_t is1tau0lCR3 = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number < 7 && *bjetsM_num >= 2;
	Bool_t is1tau0lCR4 = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number == 7 && *bjetsM_num >= 2;
	fillHistsVectorMyclass(is1tau0lCR, 1, basicWeight);
	fillHistsVectorMyclass(is1tau0lVR, 2, basicWeight);
	fillHistsVectorMyclass(is1tau0lCR2, 3, basicWeight);
	fillHistsVectorMyclass(is1tau0lCR3, 4, basicWeight);
	fillHistsVectorMyclass(is1tau0lCR4, 5, basicWeight);
	fillHistsVector(is1tau0lCR, 1, basicWeight);
	fillHistsVector(is1tau0lVR, 2, basicWeight);
	fillHistsVector(is1tau0lCR2, 3, basicWeight);
	fillHistsVector(is1tau0lCR3, 4, basicWeight);
	fillHistsVector(is1tau0lCR4, 5, basicWeight);

	// 1tau1lCR
	Bool_t is1tau1lCR0 = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number >= 7 && *bjetsM_num == 1;
	Bool_t is1tau1lCR1 = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number >= 7 && *bjetsM_num == 0;
	Bool_t is1tau1lCR2 = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number == 6 && *bjetsM_num >= 2;
	Bool_t is1tau1lCR3 = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number == 6 && *bjetsM_num < 2;
	fillHistsVectorMyclass(is1tau1lCR3, 10, basicWeight);
	fillHistsVectorMyclass(is1tau1lCR0, 7, basicWeight);
	fillHistsVectorMyclass(is1tau1lCR1, 8, basicWeight);
	fillHistsVectorMyclass(is1tau1lCR2, 9, basicWeight);
	fillHistsVector(is1tau1lCR3, 10, basicWeight);
	fillHistsVector(is1tau1lCR0, 7, basicWeight);
	fillHistsVector(is1tau1lCR1, 8, basicWeight);
	fillHistsVector(is1tau1lCR2, 9, basicWeight);

	return kTRUE;
}

void writeHist_fordataMC::SlaveTerminate()
{
	// The SlaveTerminate() function is called after all entries or objects
	// have been processed. When running with PROOF SlaveTerminate() is called
	// on each slave server.
}

void writeHist_fordataMC::Terminate()
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

	for (UInt_t ihists = 0; ihists < vectorOfVariableRegions.size(); ihists++)
	{
		vectorOfVariableRegions[ihists].histsScale(processScale);
		vectorOfVariableRegions[ihists].histsPrint();
	}
	for (UInt_t ihists = 0; ihists < vectorOfVariableRegionsDouble.size(); ihists++)
	{
		vectorOfVariableRegionsDouble[ihists].histsScale(processScale);
		// vectorOfVariableRegionsDouble[ihists].histsPrint();
	}

	Info("Terminate", "outputFile here:%s", outputFile->GetName());
	outputFile->Write();
	outputFile->Close();
}