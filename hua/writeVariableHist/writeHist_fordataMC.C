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
		jetsNumber_hists[vectorIndex]->Fill(*jets_number, weight);
		jets_HT_hists[vectorIndex]->Fill(*jets_HT, weight);
		jets_bScore_hists[vectorIndex]->Fill(*jets_bScore, weight);
		jets_1pt_hists[vectorIndex]->Fill(*jets_1pt, weight);

		tausT_HT_hists[vectorIndex]->Fill(*tausT_HT, weight);
		tausT_1pt_hists[vectorIndex]->Fill(*tausT_1pt, weight);
		tausT_1eta_hists[vectorIndex]->Fill(*tausT_1eta, weight);

		bjetsM_MHT_hists[vectorIndex]->Fill(*bjetsM_MHT, weight);
		bjets_Number_hists[vectorIndex]->Fill(*bjetsM_num, weight);
		bjets_HT_hists[vectorIndex]->Fill(*bjetsM_HT, weight);
		bjets_1pt_hists[vectorIndex]->Fill(*bjetsM_1pt, weight);

		jets_bScoreMultiply_hists[vectorIndex]->Fill(*jets_bScoreMultiply, weight);
		jets_2pt_hists[vectorIndex]->Fill(*jets_2pt, weight);
		jets_3pt_hists[vectorIndex]->Fill(*jets_3pt, weight);
		jets_4pt_hists[vectorIndex]->Fill(*jets_4pt, weight);
		jets_5pt_hists[vectorIndex]->Fill(*jets_5pt, weight);
		jets_6pt_hists[vectorIndex]->Fill(*jets_6pt, weight);
		jets_HTto4rest_hists[vectorIndex]->Fill(*jets_rationHT_4toRest, weight);
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

	push_backHists("jets_number", 10, 6, 15, jetsNumber_hists, m_processName, regionsForVariables);
	push_backHists("jets_HT", 10, 500, 1500, jets_HT_hists, m_processName, regionsForVariables);
	push_backHists("jets_bScore", 10, 0.5, 2.0, jets_bScore_hists, m_processName, regionsForVariables);
	push_backHists("jets_1pt", 10, 80, 500, jets_1pt_hists, m_processName, regionsForVariables);

	push_backHists("tausT_HT", 10, 20, 200, tausT_HT_hists, m_processName, regionsForVariables);
	push_backHists("tausT_1eta", 10, -3, 3, tausT_1eta_hists, m_processName, regionsForVariables);
	// push_backHists("", 10, 20, 200, _hists, m_processName, regionsForVariables);

	push_backHists("tausT_1pt", 10, 20, 200, tausT_1pt_hists, m_processName, regionsForVariables);
	push_backHists("bjetsM_MHT", 10, 20, 200, bjetsM_MHT_hists, m_processName, regionsForVariables);
	push_backHists("bjetsM_Number", 5, 0, 5, bjets_Number_hists, m_processName, regionsForVariables);
	push_backHists("bjetsM_HT", 10, 20, 200, bjets_HT_hists, m_processName, regionsForVariables);
	push_backHists("bjetsM_1pt", 10, 50, 500, bjets_1pt_hists, m_processName, regionsForVariables);
	push_backHists("jets_bScoreMultiply", 10, 0, 1, jets_bScoreMultiply_hists, m_processName, regionsForVariables);
	push_backHists("jets_2pt", 10, 100, 300, jets_2pt_hists, m_processName, regionsForVariables);
	push_backHists("jets_3pt", 10, 100, 300, jets_3pt_hists, m_processName, regionsForVariables);
	push_backHists("jets_4pt", 10, 100, 300, jets_4pt_hists, m_processName, regionsForVariables);
	push_backHists("jets_5pt", 10, 100, 300, jets_5pt_hists, m_processName, regionsForVariables);
	push_backHists("jets_6pt", 10, 40, 200, jets_6pt_hists, m_processName, regionsForVariables);
	push_backHists("jets_HTto4rest", 10, 1, 10, jets_HTto4rest_hists, m_processName, regionsForVariables);

	vectorOfVariableRegions.clear();
	// histsForRegions eventCount_class{"eventCount", 2, -1.0, 1.0};
	histsForRegions<Int_t> jets_number_class{"jets_numberNew", 10, 6, 15, jets_number};
	histsForRegions<Int_t> bjetsM_number_class{"bjetsM_numberNew", 5, 0, 5, bjetsM_num};
	// vectorOfVariableRegions.push_back(eventCount_class);
	vectorOfVariableRegions.push_back(jets_number_class);
	vectorOfVariableRegions.push_back(bjetsM_number_class);

	histsForRegions<Double_t> jets_1pt_class{"jets_1ptNew", 10, 100, 600, jets_1pt};
	histsForRegions<Double_t> jets_2pt_class{"jets_2ptNew", 10, 100, 600, jets_2pt};
	vectorOfVariableRegionsDouble.push_back(jets_1pt_class);
	vectorOfVariableRegionsDouble.push_back(jets_2pt_class);

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
	// for testing of step by step baseline cut
	Double_t basicWeight = (*EVENT_prefireWeight) * (*EVENT_genWeight);
	// Double_t basicWeight = (*PUweight) * (*EVENT_prefireWeight) * (*EVENT_genWeight);
	if (m_isData)
	{
		basicWeight = 1.0;
	}

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
		fillHistsVector(is1tau0lSR, 0, basicWeight);
		Bool_t is1tau1lSR = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number >= 7 && *bjetsM_num >= 2;
		fillHistsVector(is1tau1lSR, 6, basicWeight);
		fillHistsVectorMyclass(is1tau0lSR, 0, basicWeight);
		fillHistsVectorMyclass(is1tau1lSR, 6, basicWeight);
	}
	// std::vector<TString> regionsForVariables = {"1tau0lSR", "1tau0lCR", "1tau0lVR", "1tau0lCR2", "1tau0lCR3", "1tau0lCR4", "1tau1lSR", "1tau1lCR0", "1tau1lCR1", "1tau1lCR2", "1tau1lCR3"};

	// 1tau0l CR
	Bool_t is1tau0lCR = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 0;
	fillHistsVector(is1tau0lCR, 1, basicWeight);
	Bool_t is1tau0lVR = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num == 1;
	fillHistsVector(is1tau0lVR, 2, basicWeight);
	Bool_t is1tau0lCR2 = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number < 8 && *bjetsM_num >= 2;
	fillHistsVector(is1tau0lCR2, 3, basicWeight);
	Bool_t is1tau0lCR3 = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number < 7 && *bjetsM_num >= 2;
	fillHistsVector(is1tau0lCR3, 4, basicWeight);
	Bool_t is1tau0lCR4 = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number == 7 && *bjetsM_num >= 2;
	fillHistsVector(is1tau0lCR4, 5, basicWeight);
	fillHistsVectorMyclass(is1tau0lCR, 1, basicWeight);
	fillHistsVectorMyclass(is1tau0lVR, 2, basicWeight);
	fillHistsVectorMyclass(is1tau0lCR2, 3, basicWeight);
	fillHistsVectorMyclass(is1tau0lCR3, 4, basicWeight);
	fillHistsVectorMyclass(is1tau0lCR4, 5, basicWeight);

	// 1tau1lCR
	Bool_t is1tau1lCR0 = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number >= 7 && *bjetsM_num == 1;
	fillHistsVector(is1tau1lCR0, 7, basicWeight);
	Bool_t is1tau1lCR1 = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number >= 7 && *bjetsM_num == 0;
	fillHistsVector(is1tau1lCR1, 8, basicWeight);
	Bool_t is1tau1lCR2 = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number == 6 && *bjetsM_num >= 2;
	fillHistsVector(is1tau1lCR2, 9, basicWeight);
	Bool_t is1tau1lCR3 = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number == 6 && *bjetsM_num < 2;
	fillHistsVectorMyclass(is1tau1lCR3, 10, basicWeight);
	fillHistsVectorMyclass(is1tau1lCR0, 7, basicWeight);
	fillHistsVectorMyclass(is1tau1lCR1, 8, basicWeight);
	fillHistsVectorMyclass(is1tau1lCR2, 9, basicWeight);
	fillHistsVectorMyclass(is1tau1lCR3, 10, basicWeight);

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
	// std::cout<<processScale<<"\n";
	// std::cout << __LINE__ << "\n";

	for (UInt_t j = 0; j < eventCount_hists.size(); j++)
	{

		std::cout << j << "\n";
		eventCount_hists[j]->Scale(processScale);
		eventCount_hists[j]->Print();
		jetsNumber_hists[j]->Scale(processScale);
		jets_HT_hists[j]->Scale(processScale);
		jets_bScore_hists[j]->Scale(processScale);
		jets_1pt_hists[j]->Scale(processScale);

		tausT_HT_hists[j]->Scale(processScale);
		tausT_1pt_hists[j]->Scale(processScale);
		tausT_1eta_hists[j]->Scale(processScale);
		// [j]->Scale(processScale);

		bjetsM_MHT_hists[j]->Scale(processScale);
		// bjetsM_MHT_hists[j]->Print();
		bjets_Number_hists[j]->Scale(processScale);
		bjets_Number_hists[j]->Print();
		bjets_HT_hists[j]->Scale(processScale);
		bjets_1pt_hists[j]->Scale(processScale);
		jets_bScoreMultiply_hists[j]->Scale(processScale);
		jets_2pt_hists[j]->Scale(processScale);
		jets_3pt_hists[j]->Scale(processScale);
		jets_4pt_hists[j]->Scale(processScale);
		jets_5pt_hists[j]->Scale(processScale);
		jets_6pt_hists[j]->Scale(processScale);
		jets_HTto4rest_hists[j]->Scale(processScale);
	}

	for (UInt_t ihists = 0; ihists < vectorOfVariableRegions.size(); ihists++)
	{
		vectorOfVariableRegions[ihists].histsScale(processScale);
		vectorOfVariableRegions[ihists].histsPrint();
	}
	for (UInt_t ihists = 0; ihists < vectorOfVariableRegionsDouble.size(); ihists++)
	{
		vectorOfVariableRegionsDouble[ihists].histsScale(processScale);
		vectorOfVariableRegionsDouble[ihists].histsPrint();
	}

	Info("Terminate", "outputFile here:%s", outputFile->GetName());
	outputFile->Write();
	outputFile->Close();
}