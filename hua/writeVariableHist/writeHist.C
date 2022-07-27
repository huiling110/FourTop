#define writeHist_cxx
// The class definition in writeHist.h has been generated automatically
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
// root> T->Process("writeHist.C")
// root> T->Process("writeHist.C","some options")
// root> T->Process("writeHist.C+")
//

#include "writeHist.h"
#include <TH2.h>
#include <TStyle.h>

#include <assert.h>
#include <cmath>
// #include <filesystem>

// void getvOptionFromRunMacro( const TString option, std::vector<TString>& m_options ){
//    TString option1 = option(0, option.First(":"));
//     TString temp = option;
//     TString option2 = temp.Remove(0, option.First(":")+1);
//     option2 = option2(0, option2.First(":"));
//  TString option3 = temp.Remove(0, temp.First(":")+1);
//  option3 = option3(0, option3.First(":"));
//  TString option4 = temp.Remove(0, temp.First(":")+1 );
//  option4 = option4(0, option4.First(":"));
//  TString option5 = temp.Remove(0, temp.First(":")+1 );
// }
void writeHist::fillHistsVector(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
{
	if (isRegion)
	{
		// 1tau0lCR
		//  std::printf( "%i : %f : %f \n", *jets_number, *jets_HT, weight );
		jetsNumber_forYieldCount_hists[vectorIndex]->Fill(*jets_number, weight);
		onlyGenWeight_hists[vectorIndex]->Fill(0.0, weight);
		jetsNumber_hists[vectorIndex]->Fill(*jets_number, weight);
		jets_HT_hists[vectorIndex]->Fill(*jets_HT, weight);
		jets_bScore_hists[vectorIndex]->Fill(*jets_bScore, weight);
		jets_1pt_hists[vectorIndex]->Fill(*jets_1pt, weight);
		tausT_HT_hists[vectorIndex]->Fill(*tausT_HT, weight);
	}
}

void push_backHists(TString variable, Int_t binNum, Double_t minBin, Double_t maxBin, std::vector<TH1D *> &histsVariable, TString m_processName)
{
	// std::array<TString, 12> regions = {"1tau0lSR", "1tau0lCR", "1tau0lVR", "1tau0lCR2", "1tau0lCR3", "1tau0lCR4", "1tau1lSR", "1tau1lCR0", "1tau1lCR1", "1tau1lCR2", "1tau1lCR3", "baseline"};
	std::array<TString, 3> regions = {"baseline1", "baseline2", "baseline3"};
	for (UInt_t i = 0; i < regions.size(); i++)
	{
		TString iHistName = regions[i] + "_" + m_processName + "_" + variable;
		TH1D *temp = new TH1D(iHistName.Data(), iHistName.Data(), binNum, minBin, maxBin);
		histsVariable.push_back(temp);
	}
}

void writeHist::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
}

void writeHist::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
	std::cout << "option in writeHist: " << option << "\n";

	// this part could be in a function for multiple uses
	//???better structure my project so that these commen functionality go to one include dir
	TString temp = option;
	TString option1 = option(0, option.First(":"));
	TString option3 = temp.Remove(0, temp.First(":") + 1);
	option3 = option3(0, option3.First(":"));
	TString option4 = temp.Remove(0, temp.First(":") + 1);
	option4 = option4(0, option4.First(":"));
	temp.Remove(0, temp.First(":") + 1);
	TString option5 = temp(0, temp.First(":"));

	temp.Remove(0, temp.First(":") + 1);
	m_era = temp(0, temp.First(":"));
	std::cout << "m_era: " << m_era << "\n";

	m_version = option5;
	std::cout << "m_verion: " << m_version << "\n";

	m_outputFolder = option1;
	m_processName = option3;
	m_isData = std::stoi(option4.Data());
	std::cout << "m_isData: " << m_isData << "\n";

	// m_genWeightSum = std::stod(option1.Data());
	// std::cout << "m_genWeightSum: " << m_genWeightSum << "\n";
	//???maybe there is lose of accuracy due to convertion

	// namespace fs = std::filesystem;
	// if ( !fs::exists((m_outputFolder+"variableHists"+ "_"+m_version+"/").Data() )){
	// 	fs::create_directory( (m_outputFolder+"variableHists"+ "_"+m_version+"/").Data());
	// }
	// outputFile = new TFile(m_outputFolder + "variableHists" + "_" + m_version + "/" + m_processName + "_variableHists.root", "RECREATE");
	outputFile = new TFile(m_outputFolder + "variableHists" + "_" + m_version + "/" + m_processName + ".root", "RECREATE");

	// hist_jetsNumber = new TH1D( "jetsNumber_forYieldCount", "number of jets", 40, 0, 40 );
	push_backHists("jetsNumber_forYieldCount", 40, 0, 40, jetsNumber_forYieldCount_hists, m_processName);
	push_backHists("onlyGenWeight", 2, -1, 1, onlyGenWeight_hists, m_processName);
	push_backHists("jets_number", 10, 6, 15, jetsNumber_hists, m_processName);
	push_backHists("jets_HT", 40, 500, 1500, jets_HT_hists, m_processName);
	push_backHists("jets_bScore", 30, 0, 3, jets_bScore_hists, m_processName);
	push_backHists("jets_1pt", 40, 60, 200, jets_1pt_hists, m_processName);
	push_backHists("tausT_HT", 40, 20, 200, tausT_HT_hists, m_processName);
}

Bool_t writeHist::Process(Long64_t entry)
{
	// The Process() function is called for each entry in the tree (or possibly
	// keyed object in the case of PROOF) to be processed. The entry argument
	// specifies which entry in the currently loaded tree is to be processed.
	// When processing keyed objects with PROOF, the object is already loaded
	// and is available via the fObject pointer.
	//
	// This function should contain the \"body\" of the analysis. It can contain
	// simple or elaborate selection criteria, run algorithms on the data
	// of the event and typically fill histograms.
	//
	// The processing can be stopped by calling Abort().
	//
	// Use fStatus to set the return value of TTree::Process().
	//
	// The return value is currently not used.

	fReader.SetLocalEntry(entry);

	// for testing of step by step baseline cut
	Double_t basicWeight = (*PUweight) * (*EVENT_prefireWeight) * (*EVENT_genWeight);
	if (m_isData)
	{
		basicWeight = 1.0;
	}

	if (*jets_number >= 6)
	{
		fillHistsVector(true, 0, basicWeight);
	}
	if (*jets_number >= 6 && *jets_6pt >= 40)
	{
		fillHistsVector(true, 1, basicWeight);
	}
	if (*jets_HT > 500 && *jets_number >= 6 && *jets_6pt > 40)
	{
		fillHistsVector(true, 2, basicWeight);
	}

	/*
		if (*tausT_number < 1)
			return kFALSE;
		if (!(*jets_HT > 500 && *jets_6pt > 40 && *jets_number >= 6))
			return kFALSE;

		Double_t basicWeight = (*PUweight) * (*EVENT_prefireWeight) * (*EVENT_genWeight);
		// Double_t basicWeight = *EVENT_genWeight;
		// Double_t basicWeight = (*EVENT_genWeight);
		if (m_isData)
		{
			basicWeight = 1.0;
		}
		// std::cout<<"basicWeight: "<<basicWeight<<"\n";
		// Expression to be evaluated. If this expression evaluates to 0, this causes an assertion failure that terminates the program.
		// 1tau0l SR
		if (!m_isData)
		{
			// be blind for data in signal region
			Bool_t is1tau0lSR = *tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num >= 2;
			fillHistsVector(is1tau0lSR, 0, basicWeight);
			Bool_t is1tau1lSR = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number >= 7 && *bjetsM_num >= 2;
			fillHistsVector(is1tau1lSR, 6, basicWeight);
		}

		// std::array<TString, 11> regions = { "1tau0lSR", "1tau0lCR", "1tau0lVR", "1tau0lCR2", "1tau0lCR3", "1tau0lCR4", "1tau1lSR", "1tau1lCR0", "1tau1lCR1", "1tau1lCR2", "1tau1lCR3"};
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

		// 1tau1lCR
		Bool_t is1tau1lCR0 = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number >= 7 && *bjetsM_num == 1;
		fillHistsVector(is1tau1lCR0, 7, basicWeight);
		Bool_t is1tau1lCR1 = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number >= 7 && *bjetsM_num == 0;
		fillHistsVector(is1tau1lCR1, 8, basicWeight);
		Bool_t is1tau1lCR2 = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number == 6 && *bjetsM_num >= 2;
		fillHistsVector(is1tau1lCR2, 9, basicWeight);
		Bool_t is1tau1lCR3 = *tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number == 6 && *bjetsM_num < 2;
		fillHistsVector(is1tau1lCR3, 10, basicWeight);
		// Bool_t is1tau1lCR4 =  *tausT_number==1 && *leptonsMVAT_number==1 &&  *jets_number<=4 && *bjetsM_num>=2 ;
		// fillHistsVector( is1tau1lCR4, 11, basicWeight );

		Bool_t isBaseline = *jets_HT > 500 && *jets_6pt > 40;
		fillHistsVector(isBaseline, 11, basicWeight);
	*/
	return kTRUE;
}

void writeHist::SlaveTerminate()
{
	// The SlaveTerminate() function is called after all entries or objects
	// have been processed. When running with PROOF SlaveTerminate() is called
	// on each slave server.
}

void writeHist::Terminate()
{
	// The Terminate() function is the last function to be called during
	// a query. It always runs on the client, it can be used to present
	// the results graphically or save the results to file.
	/*
	#include "../crossSectionMap.h"
		Double_t processScale = 1.0;
		if (!m_isData)
		{
			std::cout << m_processName << ": " << lumiMap[m_era] << " " << crossSectionMap[m_processName] << " " << m_genWeightSum << "\n";
			processScale = ((lumiMap[m_era] * crossSectionMap[m_processName]) / m_genWeightSum);
		}
		// std::cout<<processScale<<"\n";

		for (UInt_t j = 0; j < jetsNumber_hists.size(); j++)
		{

			std::cout << j << "\n";
			jetsNumber_forYieldCount_hists[j]->Scale(processScale);
			jetsNumber_forYieldCount_hists[j]->Print();
			onlyGenWeight_hists[j]->Scale(processScale);
			onlyGenWeight_hists[j]->Print();
			jetsNumber_hists[j]->Scale(processScale);
			jets_HT_hists[j]->Scale(processScale);
			jets_bScore_hists[j]->Scale(processScale);
			jets_1pt_hists[j]->Scale(processScale);
			tausT_HT_hists[j]->Scale(processScale);
		}

		*/
	// getting event count histo from input file
	// TDirectory *outFileDir = gDirectory->GetDirectory("");
	// TFile *input = new TFile(m_outputFolder + m_processName + ".root", "READ");
	// TH1D *jetsNumber_initial = (TH1D *)input->Get("jetsNumber_initial")->Clone("initial_" + m_processName + "_jetsNumber_forYieldCount");
	// jetsNumber_initial->SetDirectory(outFileDir);
	// jetsNumber_initial->Scale(processScale);
	// jetsNumber_initial->Print();
	// TH1D *jetsNumber_HLT = (TH1D *)input->Get("jetsNumber_HLT")->Clone("HLT_" + m_processName + "_jetsNumber_forYieldCount");
	// jetsNumber_HLT->SetDirectory(outFileDir);
	// jetsNumber_HLT->Scale(processScale);
	// jetsNumber_HLT->Print();
	// TH1D *jetsNumber_baseline = (TH1D *)input->Get("jetsNumber_baseline")->Clone("baseline_" + m_processName + "_jetsNumber_forYieldCount");
	// jetsNumber_baseline->SetDirectory(outFileDir);
	// jetsNumber_baseline->Scale(processScale);
	// jetsNumber_baseline->Print();

	// input->Close();

	// outFileDir->cd();
	// jetsNumber_initial->Write();
	outputFile->Write();
	outputFile->Close();
	Info("Terminate", "outputFile here:%s", outputFile->GetName());
}