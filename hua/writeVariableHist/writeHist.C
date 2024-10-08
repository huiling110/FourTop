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

#include <TH2.h>
#include <TStyle.h>

#include <assert.h>
#include <cmath>
// #include <filesystem>

#include "../src_cpp/usefulFuction.h"
#include "writeHist.h"

void writeHist::fillHistsVector(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
{
	if (isRegion)
	{
		// 1tau0lCR
		//  std::printf( "%i : %f : %f \n", *jets_number, *jets_HT, weight );
		jetsNumber_forYieldCount_hists[vectorIndex]->Fill(*jets_number, weight);
		jetsNumber_hists[vectorIndex]->Fill(*jets_number, weight);
		jets_HT_hists[vectorIndex]->Fill(*jets_HT, weight);
		jets_bScore_hists[vectorIndex]->Fill(*jets_bScore, weight);
		jets_1pt_hists[vectorIndex]->Fill(*jets_1pt, weight);
		tausT_HT_hists[vectorIndex]->Fill(*tausT_HT, weight);
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

	std::vector<TString> regionsEC = {"whInitial", "baseline1", "baseline2", "baseline3", "1tau0lSRmoun", "1tau0lSRele", "1tau0lSRtau", "1tau0lSRjet", "1tau0lSRbjet", "1tau0lSR", "1tau1lSR", "1tau2lSR", "2tau0lSR", "2tau1lSR", "1tau1lSRtau", "1tau1lSRlep", "1tau1lSRjet", "1tau1lSRbjet"};
	// std::vector<TString> regionsEC = {"whInitial", "baseline1", "baseline2", "baseline3", "1tau0lSRmoun", "1tau0lSRele", "1tau0lSRtau", "1tau0lSRjet", "1tau0lSRbjet"};
	push_backHists("eventCount", 2, -1, 1, eventCount_hists, m_processName, regionsEC);

	cutFlowTree = new TTree("cutFlowTree", "cutFlowTree");
	cutFlowTree->Branch("event_", &event_);
	// cutFlowTree->Bracnh()
	cutFlowTree->Branch("jets_6pt_", &jets_6pt_);
	cutFlowTree->Branch("ifPassJets_6pt", &ifPassJets_6pt);
	cutFlowTree->Branch("ifPass6jets", &ifPass6jets);
	cutFlowTree->Branch("ifPassHT500", &ifPassHT500);
	// cutFlowTree->Branch("")
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
	Double_t basicWeight = (*EVENT_prefireWeight) * (*EVENT_genWeight);
	// Double_t basicWeight = (*PUweight) * (*EVENT_prefireWeight) * (*EVENT_genWeight);

	// test
	// if (!(*event == 2567375 || *event == 2279051))
	// 	return kFALSE;
	// std::cout << std::setprecision(18) << *jets_6pt << "\n";
	if (m_isData)
	{
		basicWeight = 1.0;
	}
	eventCount_hists[0]->Fill(0.0, basicWeight);

	if (*jets_number >= 6)
	{
		eventCount_hists[1]->Fill(.0, basicWeight);
		ifPass6jets = kTRUE;
	}
	else
	{
		ifPass6jets = kFALSE;
	}
	// if (TMath::Abs((*jets_6pt - 40.0)) < TMath::Limits<Double_t>::Epsilon())
	// {
	// 	std::cout << std::setprecision(18) << *jets_6pt << "\n";
	// 	std::cout << (*jets_6pt > 40.0) << "\n";
	// 	std::cout << "event with 40 pt: " << *event << "\n";
	// }
	if ((*jets_number >= 6) && (*jets_6pt > 40.0))
	{
		eventCount_hists[2]->Fill(.0, basicWeight);
		ifPassJets_6pt = kTRUE;
	}
	else
	{
		ifPassJets_6pt = kFALSE;
	}
	if (*jets_number >= 6 && *jets_6pt > 40.0 && *jets_HT > 500.0)
	{
		eventCount_hists[3]->Fill(.0, basicWeight);
		ifPassHT500 = kTRUE;
	}
	else
	{
		ifPassHT500 = kFALSE;
		return kFALSE;
	}
	event_ = *event;
	// std::cout << *event << "\n";
	jets_6pt_ = *jets_6pt;

	// std::vector<TString> regionsEC = {"whInitial",  "baseline1", "baseline2", "baseline3", "1tau0lSRmoun", "1tau0lSRele", "1tau0lSRtau", "1tau0lSRjet", "1tau0lSRbjet", "1tau0lSR", "1tau1lSR", "1tau2lSR", "2tau0lSR", "2tau1lSR", "1tau1lSRtau", "1tau1lSRlep", "1tau1lSRjet", "1tau1lSRbjet"};
	if (!m_isData)
	{
		// if (*leptonsMVAT_number == 0)
		if (*muonsT_number == 0)
		{
			eventCount_hists[4]->Fill(.0, basicWeight);
		}
		if (*elesMVAT_number == 0 && *muonsT_number == 0)
		{
			eventCount_hists[5]->Fill(.0, basicWeight);
		}

		if (*elesMVAT_number == 0 && *muonsT_number == 0 && *tausT_number == 1)
		{
			eventCount_hists[6]->Fill(.0, basicWeight);
		}
		if (*elesMVAT_number == 0 && *muonsT_number == 0 && *tausT_number == 1 && *jets_number >= 8)
		{
			eventCount_hists[7]->Fill(.0, basicWeight);
		}
		if (*elesMVAT_number == 0 && *muonsT_number == 0 && *tausT_number == 1 && *jets_number >= 8 && *bjetsM_num >= 2)
		{
			eventCount_hists[8]->Fill(.0, basicWeight);
		}
		if (*tausT_number == 1 && *leptonsMVAT_number == 0 && *jets_number >= 8 && *bjetsM_num >= 2)
		{
			// 1tau0l
			eventCount_hists[9]->Fill(.0, basicWeight);
		}
		if (*tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number >= 7 && *bjetsM_num >= 2)
		{
			// 1tau1l
			eventCount_hists[10]->Fill(.0, basicWeight);
		}
		if (*tausT_number == 1 && *leptonsMVAT_number == 2 && *jets_number >= 6 && *bjetsM_num >= 2)
		{
			eventCount_hists[11]->Fill(.0, basicWeight);
		}
		if (*tausT_number == 2 && *leptonsMVAT_number == 0 && *jets_number >= 7 && *bjetsM_num >= 2)
		{
			eventCount_hists[12]->Fill(.0, basicWeight);
		}
		if (*tausT_number == 2 && *leptonsMVAT_number == 1 && *jets_number >= 6 && *bjetsM_num >= 2)
		{
			eventCount_hists[13]->Fill(.0, basicWeight);
		}
		if (*tausT_number == 1)
		{
			eventCount_hists[14]->Fill(.0, basicWeight);
		}
		if (*tausT_number == 1 && *leptonsMVAT_number == 1)
		// if (*tausT_number == 1 && (*muonsT_number + *elesMVAT_number) == 1)
		{
			eventCount_hists[15]->Fill(.0, basicWeight);
		}
		if (*tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number >= 7)
		{
			eventCount_hists[16]->Fill(.0, basicWeight);
		}
		if (*tausT_number == 1 && *leptonsMVAT_number == 1 && *jets_number >= 7 && *bjetsM_num >= 2)
		{
			eventCount_hists[17]->Fill(.0, basicWeight);
		}
	}

	cutFlowTree->Fill();
	// std::array<TString, 11> regddions = { "1tau0lSR", "1tau0lCR", "1tau0lVR", "1tau0lCR2", "1tau0lCR3", "1tau0lCR4", "1tau1lSR", "1tau1lCR0", "1tau1lCR1", "1tau1lCR2", "1tau1lCR3"};
	// 1tau0l CR

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
#include "lumiAndCrossSection.h"
	// the results graphically or save the results to file.
	Double_t processScale = 1.0;
	if (!m_isData)
	{
		std::cout << m_processName << ": " << lumiMap[m_era] << " " << crossSectionMap[m_processName] << " " << m_genWeightSum << "\n";
		processScale = ((lumiMap[m_era] * crossSectionMap[m_processName]) / m_genWeightSum);
	}
	// std::cout<<processScale<<"\n";

	for (UInt_t j = 0; j < eventCount_hists.size(); j++)
	{
		eventCount_hists[j]->Scale(processScale);
		eventCount_hists[j]->Print();
		// std::cout<<"raw: "<<eventCount_hists[j]->GetEntries();
	}

	cutFlowTree->BuildIndex("event_");

	outputFile->Write();
	outputFile->Close();
	Info("Terminate", "outputFile here:%s", outputFile->GetName());
}