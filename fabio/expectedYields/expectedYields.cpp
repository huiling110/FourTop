#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TBenchmark.h>
#include <TEfficiency.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TROOT.h> //for gROOT
#include <TSystem.h> // for gSystem
#include "expectedYields.h"

void expectedYields() {

	gBenchmark->Start("running time");
	gROOT->ProcessLine(".L Loader.C+");

	map<string, string>::iterator file_it = file.begin();

	TFile *outputfile = new TFile( "expectedYields_output.root", "RECREATE" );

	while (file_it != file.end()) { //////////////////////// LOOP OVER FILES ///////////////////////

		cout << "Reading process " << file_it->second << "..." << endl;
		TString input_base_dir = file_it->second + "/";

		gSystem->RedirectOutput("/dev/null"); // do not show errors when not finding the following files: will print a custom error a few lines below
		TFile * checkinput = new TFile(input_base_dir + "v3_1-1.root");
		TFile * checkinput2 = new TFile(input_base_dir + "v3_1.root");
		gSystem->RedirectOutput(0,0); // restore the printing to normal behavior
		if (checkinput->IsZombie() && checkinput2->IsZombie()) {
			cout << "+++ INPUT FILES NOT FOUND! SKIPPING +++" << endl;
			file_it++;
			continue;
		} 

		TH1::AddDirectory(kFALSE);
		TH1F* h_1tau0L = new TH1F ("h_1tau0L", "h_1tau0L", 20, 0, 20);
		TH1F* h_1tau1L = new TH1F ("h_1tau1L", "h_1tau1L", 20, 0, 20);
		TH1F* h_1tau2L = new TH1F ("h_1tau2L", "h_1tau2L", 20, 0, 20);
		TH1F* h_1tau3L = new TH1F ("h_1tau3L", "h_1tau3L", 20, 0, 20);
		TH1F* h_2tau0L = new TH1F ("h_2tau0L", "h_2tau0L", 20, 0, 20);
		TH1F* h_2tau1L = new TH1F ("h_2tau1L", "h_2tau1L", 20, 0, 20);
		TH1F* h_2tau2L = new TH1F ("h_2tau2L", "h_2tau2L", 20, 0, 20); 
		TH1::AddDirectory(kTRUE);

		TChain mychain("tree");
		mychain.Add(input_base_dir + "v3*.root");
		TChain mychain2("allevents");
		mychain2.Add(input_base_dir + "v3*.root");
		
		cout << "Computing the sum of gen event weights..." << endl;
		TH1::StatOverflows(kTRUE);
		TH1D * genEvtWeights = new TH1D( "genEvtWeights", "genEvtWeights", 10, -10, 10 );
		double gen_sum_of_weights = 0.0;
		mychain2.Project(genEvtWeights->GetName(), "genWeight_allEvents");
		cout << "genEvtWeights->GetMean(): " << genEvtWeights->GetMean() << endl;
		cout << "genEvtWeights->GetEntries(): " << genEvtWeights->GetEntries() << endl; 
		gen_sum_of_weights = genEvtWeights->GetMean()*genEvtWeights->GetEntries();
		cout << gen_sum_of_weights << endl;
		TH1::StatOverflows(kFALSE);

		double mygenEvtWeight = 0;
		mychain.SetBranchAddress( "EVENT_genWeight_", &mygenEvtWeight );

		vector<TLorentzVector> * mygenTaus = {};
		mychain.SetBranchAddress("genTaus", &mygenTaus);

		vector<TLorentzVector> * mygenEles = {};
		mychain.SetBranchAddress("genEles", &mygenEles);

		vector<TLorentzVector> * mygenMuons = {};
		mychain.SetBranchAddress("genMuons", &mygenMuons);

		vector<TLorentzVector> *myjetsL = {}; 
		mychain.SetBranchAddress("jets", &myjetsL);

		vector<TLorentzVector> *mybjetsM = {}; 
		mychain.SetBranchAddress("bjetsM", &mybjetsM);

		vector<TLorentzVector> *myelesMVAT = {}; 
		mychain.SetBranchAddress("eleMVAT", &myelesMVAT);

		vector<TLorentzVector> *mymuonsT = {}; 
		mychain.SetBranchAddress("muonsT", &mymuonsT);

		vector<TLorentzVector> *mytausT = {}; 
		mychain.SetBranchAddress("tausT", &mytausT);

		vector<TLorentzVector> *myleptonsMVAT = {}; 
		mychain.SetBranchAddress("leptonsMVAT", &myleptonsMVAT);

		// multijet triggers
		int myHLT_PFHT450_SixJet40_BTagCSV_p056 = 0;
		mychain.SetBranchAddress("HLT_PFHT450_SixJet40_BTagCSV_p056_", &myHLT_PFHT450_SixJet40_BTagCSV_p056);

		int myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = 0;
		mychain.SetBranchAddress("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_", &myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056);
 
		//HLT_PFJet450 to recover eff in data
		int myHLT_PFJet450 = 0;
		mychain.SetBranchAddress("HLT_PFJet450_", &myHLT_PFJet450);

		Long64_t nevents = mychain.GetEntries();

		for ( Long64_t ievent = 0; ievent < nevents; ++ievent ) {
			//if (ievent > 100) break;
			if ( !(ievent % 100000 ) ) cout << "ievent  =  " << ievent << endl;
			//get i-th entry in tree
			mychain.GetEntry( ievent );

			//compute HT
			float HT = 0.0;
			int countjetpt = 0;
			for (unsigned int i = 0; i < myjetsL->size(); i ++)  {
   
				if (myjetsL->at(i).Pt() > 35) countjetpt++;
				HT += myjetsL->at(i).Pt();
				
			}
			
			/////////////////////////////////////////////////////////////////////
			///////////////////// DEFINE TRIGGER CUTS ///////////////////////////
			/////////////////////////////////////////////////////////////////////

			bool isSignalTrig = ((myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1 || myHLT_PFJet450 == 1) && HT > 400);

			/////////////////////////////////////////////////////////////////////
			///////////////////// DEFINE CATEGORY CUTS //////////////////////////
			/////////////////////////////////////////////////////////////////////

			//reco-level categories
			bool is1tau0L = (mytausT->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2);
			bool is1tau1L = (mytausT->size()==1 && myleptonsMVAT->size()==1 && myjetsL->size()>=6 && mybjetsM->size()>=2);
			bool is1tau2L = (mytausT->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2);
			bool is1tau3L = (mytausT->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2);
			bool is2tau0L = (mytausT->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2);
			bool is2tau1L = (mytausT->size()==2 && myleptonsMVAT->size()==1 && myjetsL->size()>=4 && mybjetsM->size()>=2);
			bool is2tau2L = (mytausT->size()==2 && myleptonsMVAT->size()==2 && myjetsL->size()>=2 && mybjetsM->size()>=2);

			if (isSignalTrig && is1tau0L) h_1tau0L->Fill(myjetsL->size(), mygenEvtWeight);
			if (isSignalTrig && is1tau1L) h_1tau1L->Fill(myjetsL->size(), mygenEvtWeight);
			if (isSignalTrig && is1tau2L) h_1tau2L->Fill(myjetsL->size(), mygenEvtWeight);
			if (isSignalTrig && is1tau3L) h_1tau3L->Fill(myjetsL->size(), mygenEvtWeight);
			if (isSignalTrig && is2tau0L) h_2tau0L->Fill(myjetsL->size(), mygenEvtWeight);
			if (isSignalTrig && is2tau1L) h_2tau1L->Fill(myjetsL->size(), mygenEvtWeight);
			if (isSignalTrig && is2tau2L) h_2tau2L->Fill(myjetsL->size(), mygenEvtWeight);
						
		
		}//end loop over events

		outputfile->cd();
		
		TH1D * totalWeight = new TH1D("totalWeight", "totalWeight", 1, -0.5, 0.5);
		TH1::AddDirectory(kFALSE);  
		totalWeight->Fill(0.0, gen_sum_of_weights);
		TH1::AddDirectory(kTRUE);
		std::string hTotalWeightName(totalWeight->GetName());		
		hTotalWeightName.append("_");
		hTotalWeightName.append(file_it->first);
	    totalWeight->Write(hTotalWeightName.c_str());
		
		writeHisto(h_1tau0L, file_it, h_1tau0L->GetName());			
		writeHisto(h_1tau1L, file_it, h_1tau1L->GetName());
		writeHisto(h_1tau2L, file_it, h_1tau2L->GetName());
		writeHisto(h_1tau3L, file_it, h_1tau3L->GetName());
		writeHisto(h_2tau0L, file_it, h_2tau0L->GetName());
		writeHisto(h_2tau1L, file_it, h_2tau1L->GetName());
		writeHisto(h_2tau2L, file_it, h_2tau2L->GetName());

		delete totalWeight;
		delete genEvtWeights;
		mychain.Reset();
		mychain2.Reset();
		file_it++;

	}//end loop over files

	outputfile->Close();
	delete outputfile;
	
	gBenchmark->Show("running time");

}//end

void writeHisto(TH1F* histo, map<string, string>::iterator file_it, TString name) {

   	histo->Write(name+file_it->first);

}
