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
#include "gen_efficiencies.h"

void gen_efficiencies() {

	gBenchmark->Start("running time");
	gROOT->ProcessLine(".L Loader.C+");

	map<string, string>::iterator file_it = file.begin();

	TFile *outputfile = new TFile( "gen_efficiencies_output.root", "RECREATE" );

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
		//use array of TH1Fs; 0-th histo corresponds to tighter WP in VsJet; 7-th histo corresponds to looser WP in VsJet
		//gen1tau0L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_gen1tau0L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau0L_bef_%d", i);
			sprintf(title, "h_recoeff_gen1tau0L_bef_%d", i);
			h_recoeff_gen1tau0L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recoeff_gen1tau0L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau0L_aft_%d", i);
			sprintf(title, "h_recoeff_gen1tau0L_aft_%d", i);
			h_recoeff_gen1tau0L_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen1tau0L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau0L_bef_%d", i);
			sprintf(title, "h_recopurity_gen1tau0L_bef_%d", i);
			h_recopurity_gen1tau0L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recopurity_gen1tau0L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau0L_aft_%d", i);
			sprintf(title, "h_recopurity_gen1tau0L_aft_%d", i);
			h_recopurity_gen1tau0L_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		//gen1tau1L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_gen1tau1L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau1L_bef_%d", i);
			sprintf(title, "h_recoeff_gen1tau1L_bef_%d", i);
			h_recoeff_gen1tau1L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recoeff_gen1tau1L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau1L_aft_%d", i);
			sprintf(title, "h_recoeff_gen1tau1L_aft_%d", i);
			h_recoeff_gen1tau1L_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen1tau1L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau1L_bef_%d", i);
			sprintf(title, "h_recopurity_gen1tau1L_bef_%d", i);
			h_recopurity_gen1tau1L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recopurity_gen1tau1L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau1L_aft_%d", i);
			sprintf(title, "h_recopurity_gen1tau1L_aft_%d", i);
			h_recopurity_gen1tau1L_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		//gen1tau2L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_gen1tau2L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau2L_bef_%d", i);
			sprintf(title, "h_recoeff_gen1tau2L_bef_%d", i);
			h_recoeff_gen1tau2L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recoeff_gen1tau2L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau2L_aft_%d", i);
			sprintf(title, "h_recoeff_gen1tau2L_aft_%d", i);
			h_recoeff_gen1tau2L_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen1tau2L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau2L_bef_%d", i);
			sprintf(title, "h_recopurity_gen1tau2L_bef_%d", i);
			h_recopurity_gen1tau2L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recopurity_gen1tau2L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau2L_aft_%d", i);
			sprintf(title, "h_recopurity_gen1tau2L_aft_%d", i);
			h_recopurity_gen1tau2L_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		//gen1tau3L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_gen1tau3L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau3L_bef_%d", i);
			sprintf(title, "h_recoeff_gen1tau3L_bef_%d", i);
			h_recoeff_gen1tau3L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recoeff_gen1tau3L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau3L_aft_%d", i);
			sprintf(title, "h_recoeff_gen1tau3L_aft_%d", i);
			h_recoeff_gen1tau3L_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen1tau3L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau3L_bef_%d", i);
			sprintf(title, "h_recopurity_gen1tau3L_bef_%d", i);
			h_recopurity_gen1tau3L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recopurity_gen1tau3L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau3L_aft_%d", i);
			sprintf(title, "h_recopurity_gen1tau3L_aft_%d", i);
			h_recopurity_gen1tau3L_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		//gen2tau0L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_gen2tau0L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau0L_bef_%d", i);
			sprintf(title, "h_recoeff_gen2tau0L_bef_%d", i);
			h_recoeff_gen2tau0L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recoeff_gen2tau0L_2m_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau0L_2m_aft_%d", i);
			sprintf(title, "h_recoeff_gen2tau0L_2m_aft_%d", i);
			h_recoeff_gen2tau0L_2m_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recoeff_gen2tau0L_1m_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau0L_1m_aft_%d", i);
			sprintf(title, "h_recoeff_gen2tau0L_1m_aft_%d", i);
			h_recoeff_gen2tau0L_1m_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen2tau0L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen2tau0L_bef_%d", i);
			sprintf(title, "h_recopurity_gen2tau0L_bef_%d", i);
			h_recopurity_gen2tau0L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recopurity_gen2tau0L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen2tau0L_aft_%d", i);
			sprintf(title, "h_recopurity_gen2tau0L_aft_%d", i);
			h_recopurity_gen2tau0L_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		//gen2tau1L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_gen2tau1L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau1L_bef_%d", i);
			sprintf(title, "h_recoeff_gen2tau1L_bef_%d", i);
			h_recoeff_gen2tau1L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recoeff_gen2tau1L_2m_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau1L_2m_aft_%d", i);
			sprintf(title, "h_recoeff_gen2tau1L_2m_aft_%d", i);
			h_recoeff_gen2tau1L_2m_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recoeff_gen2tau1L_1m_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau1L_1m_aft_%d", i);
			sprintf(title, "h_recoeff_gen2tau1L_1m_aft_%d", i);
			h_recoeff_gen2tau1L_1m_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen2tau1L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen2tau1L_bef_%d", i);
			sprintf(title, "h_recopurity_gen2tau1L_bef_%d", i);
			h_recopurity_gen2tau1L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recopurity_gen2tau1L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen2tau1L_aft_%d", i);
			sprintf(title, "h_recopurity_gen2tau1L_aft_%d", i);
			h_recopurity_gen2tau1L_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		//gen2tau2L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_gen2tau2L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau2L_bef_%d", i);
			sprintf(title, "h_recoeff_gen2tau2L_bef_%d", i);
			h_recoeff_gen2tau2L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recoeff_gen2tau2L_2m_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau2L_2m_aft_%d", i);
			sprintf(title, "h_recoeff_gen2tau2L_2m_aft_%d", i);
			h_recoeff_gen2tau2L_2m_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recoeff_gen2tau2L_1m_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau2L_1m_aft_%d", i);
			sprintf(title, "h_recoeff_gen2tau2L_1m_aft_%d", i);
			h_recoeff_gen2tau2L_1m_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen2tau2L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen2tau2L_bef_%d", i);
			sprintf(title, "h_recopurity_gen2tau2L_bef_%d", i);
			h_recopurity_gen2tau2L_bef[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
		TH1F* h_recopurity_gen2tau2L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen2tau2L_aft_%d", i);
			sprintf(title, "h_recopurity_gen2tau2L_aft_%d", i);
			h_recopurity_gen2tau2L_aft[i] = new TH1F(name, title, 1, -0.5, 0.5);		
		}
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

		vector<TLorentzVector> *mytausT_VVTightVsJet = {}; 
		mychain.SetBranchAddress("tausT_VVTightVsJet", &mytausT_VVTightVsJet);

		vector<TLorentzVector> *mytausT_VTightVsJet = {}; 
		mychain.SetBranchAddress("tausT_VTightVsJet", &mytausT_VTightVsJet);

		vector<TLorentzVector> *mytausT_TightVsJet = {}; 
		mychain.SetBranchAddress("tausT_TightVsJet", &mytausT_TightVsJet);

		vector<TLorentzVector> *mytausT_MediumVsJet = {}; 
		mychain.SetBranchAddress("tausT_MediumVsJet", &mytausT_MediumVsJet);

		vector<TLorentzVector> *mytausT_LooseVsJet = {}; 
		mychain.SetBranchAddress("tausT_LooseVsJet", &mytausT_LooseVsJet);

		vector<TLorentzVector> *mytausT_VLooseVsJet = {}; 
		mychain.SetBranchAddress("tausT_VLooseVsJet", &mytausT_VLooseVsJet);

		vector<TLorentzVector> *mytausT_VVLooseVsJet = {}; 
		mychain.SetBranchAddress("tausT_VVLooseVsJet", &mytausT_VVLooseVsJet);

		vector<TLorentzVector> *mytausT_VVVLooseVsJet = {}; 
		mychain.SetBranchAddress("tausT_VVVLooseVsJet", &mytausT_VVVLooseVsJet);

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
			/////////////////////////////////////////////////////////////////////
			///////////////////// DEFINE CATEGORY CUTS //////////////////////////
			/////////////////////////////////////////////////////////////////////
			
			//gen-level categories
			bool isgen1tau0L = (mygenTaus->size()==1 && (mygenEles->size() + mygenMuons->size())==0);
			bool isgen1tau1L = (mygenTaus->size()==1 && (mygenEles->size() + mygenMuons->size())==1);
			bool isgen1tau2L = (mygenTaus->size()==1 && (mygenEles->size() + mygenMuons->size())==2);
			bool isgen1tau3L = (mygenTaus->size()==1 && (mygenEles->size() + mygenMuons->size())==3);
			bool isgen2tau0L = (mygenTaus->size()==2 && (mygenEles->size() + mygenMuons->size())==0);
			bool isgen2tau1L = (mygenTaus->size()==2 && (mygenEles->size() + mygenMuons->size())==1);
			bool isgen2tau2L = (mygenTaus->size()==2 && (mygenEles->size() + mygenMuons->size())==2);
			
			bool is1recotau[8] = {

				mytausT_VVTightVsJet->size()==1,
				mytausT_VTightVsJet->size()==1,
				mytausT_TightVsJet->size()==1,
				mytausT_MediumVsJet->size()==1,
				mytausT_LooseVsJet->size()==1,
				mytausT_VLooseVsJet->size()==1,
				mytausT_VVLooseVsJet->size()==1,
				mytausT_VVVLooseVsJet->size()==1

			};

			bool is2recotau[8] = {

				mytausT_VVTightVsJet->size()==2,
				mytausT_VTightVsJet->size()==2,
				mytausT_TightVsJet->size()==2,
				mytausT_MediumVsJet->size()==2,
				mytausT_LooseVsJet->size()==2,
				mytausT_VLooseVsJet->size()==2,
				mytausT_VVLooseVsJet->size()==2,
				mytausT_VVVLooseVsJet->size()==2

			};

			vector<TLorentzVector>* mytausT[8] = {
				mytausT_VVTightVsJet,
				mytausT_VTightVsJet,
				mytausT_TightVsJet,
				mytausT_MediumVsJet,
				mytausT_LooseVsJet,
				mytausT_VLooseVsJet,
				mytausT_VVLooseVsJet,
				mytausT_VVVLooseVsJet
			};


			for (int i = 0; i < 8; i++){

				if (isgen1tau0L && mytausT[i]->size() == 1) {

					h_recoeff_gen1tau0L_bef[i]->Fill(0.0, mygenEvtWeight);

					if (genrecoEff(mygenTaus, mytausT[i]) == 1) h_recoeff_gen1tau0L_aft[i]->Fill(0.0, mygenEvtWeight);
				
				}

				if (isgen1tau1L && mytausT[i]->size() == 1) {

					h_recoeff_gen1tau1L_bef[i]->Fill(0.0, mygenEvtWeight);

					if (genrecoEff(mygenTaus, mytausT[i]) == 1) h_recoeff_gen1tau1L_aft[i]->Fill(0.0, mygenEvtWeight);
				
				}

				if (isgen1tau2L && mytausT[i]->size() == 1) {

					h_recoeff_gen1tau2L_bef[i]->Fill(0.0, mygenEvtWeight);

					if (genrecoEff(mygenTaus, mytausT[i]) == 1) h_recoeff_gen1tau2L_aft[i]->Fill(0.0, mygenEvtWeight);
				
				}

				if (isgen1tau3L && mytausT[i]->size() == 1) {

					h_recoeff_gen1tau3L_bef[i]->Fill(0.0, mygenEvtWeight);

					if (genrecoEff(mygenTaus, mytausT[i]) == 1) h_recoeff_gen1tau3L_aft[i]->Fill(0.0, mygenEvtWeight);
				
				}

				if (isgen2tau0L && mytausT[i]->size() == 2) {

					h_recoeff_gen2tau0L_bef[i]->Fill(0.0, mygenEvtWeight);

					if (genrecoEff(mygenTaus, mytausT[i]) == 1) h_recoeff_gen2tau0L_1m_aft[i]->Fill(0.0, mygenEvtWeight);
					if (genrecoEff(mygenTaus, mytausT[i]) == 2) h_recoeff_gen2tau0L_2m_aft[i]->Fill(0.0, mygenEvtWeight);
				
				}

				if (isgen2tau1L && mytausT[i]->size() == 2) {

					h_recoeff_gen2tau1L_bef[i]->Fill(0.0, mygenEvtWeight);

					if (genrecoEff(mygenTaus, mytausT[i]) == 1) h_recoeff_gen2tau1L_1m_aft[i]->Fill(0.0, mygenEvtWeight);
					if (genrecoEff(mygenTaus, mytausT[i]) == 2) h_recoeff_gen2tau1L_2m_aft[i]->Fill(0.0, mygenEvtWeight);
				
				}

				if (isgen2tau2L && mytausT[i]->size() == 2) {

					h_recoeff_gen2tau2L_bef[i]->Fill(0.0, mygenEvtWeight);

					if (genrecoEff(mygenTaus, mytausT[i]) == 1) h_recoeff_gen2tau2L_1m_aft[i]->Fill(0.0, mygenEvtWeight);
					if (genrecoEff(mygenTaus, mytausT[i]) == 2) h_recoeff_gen2tau2L_2m_aft[i]->Fill(0.0, mygenEvtWeight);
				
				}
				

			}//end loop over different VsJet WPs
			
		
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
		
		for (int i = 0; i < 8; i++) {

			char recoEffname[200];
			sprintf(recoEffname, "recoEff_gen1tau0L_%d_", i);
			writeTEfficiency(h_recoeff_gen1tau0L_bef[i], h_recoeff_gen1tau0L_aft[i], file_it, recoEffname);

			sprintf(recoEffname, "recoEff_gen1tau1L_%d_", i);
			writeTEfficiency(h_recoeff_gen1tau1L_bef[i], h_recoeff_gen1tau1L_aft[i], file_it, recoEffname);

			sprintf(recoEffname, "recoEff_gen1tau2L_%d_", i);
			writeTEfficiency(h_recoeff_gen1tau2L_bef[i], h_recoeff_gen1tau2L_aft[i], file_it, recoEffname);
			
			sprintf(recoEffname, "recoEff_gen1tau3L_%d_", i);
			writeTEfficiency(h_recoeff_gen1tau3L_bef[i], h_recoeff_gen1tau3L_aft[i], file_it, recoEffname);

			sprintf(recoEffname, "recoEff_gen2tau0L_%d_", i);
			writeTEfficiency(h_recoeff_gen2tau0L_bef[i], h_recoeff_gen2tau0L_1m_aft[i], file_it, recoEffname);
			std::string h2m_name_2tau0L(h_recoeff_gen2tau0L_2m_aft[i]->GetName());
			h2m_name_2tau0L.append("_");
			h2m_name_2tau0L.append(file_it->first);
			h_recoeff_gen2tau0L_2m_aft[i]->Write(h2m_name_2tau0L.c_str());

			sprintf(recoEffname, "recoEff_gen2tau1L_%d_", i);
			writeTEfficiency(h_recoeff_gen2tau1L_bef[i], h_recoeff_gen2tau1L_1m_aft[i], file_it, recoEffname);
			std::string h2m_name_2tau1L(h_recoeff_gen2tau1L_2m_aft[i]->GetName());
			h2m_name_2tau1L.append("_");
			h2m_name_2tau1L.append(file_it->first);
			h_recoeff_gen2tau1L_2m_aft[i]->Write(h2m_name_2tau1L.c_str());
			
			sprintf(recoEffname, "recoEff_gen2tau2L_%d_", i);
			writeTEfficiency(h_recoeff_gen2tau2L_bef[i], h_recoeff_gen2tau2L_1m_aft[i], file_it, recoEffname);
			std::string h2m_name_2tau2L(h_recoeff_gen2tau2L_2m_aft[i]->GetName());
			h2m_name_2tau2L.append("_");
			h2m_name_2tau2L.append(file_it->first);
			h_recoeff_gen2tau2L_2m_aft[i]->Write(h2m_name_2tau2L.c_str());

		}
	   

		for (int i = 0; i < 8; i++) {

			delete h_recoeff_gen1tau0L_bef[i];
			delete h_recoeff_gen1tau0L_aft[i];
			delete h_recoeff_gen1tau1L_bef[i];
			delete h_recoeff_gen1tau1L_aft[i];
			delete h_recoeff_gen1tau2L_bef[i];
			delete h_recoeff_gen1tau2L_aft[i];
			delete h_recoeff_gen1tau3L_bef[i];
			delete h_recoeff_gen1tau3L_aft[i];
			delete h_recoeff_gen2tau0L_bef[i];
			delete h_recoeff_gen2tau0L_1m_aft[i];
			delete h_recoeff_gen2tau0L_2m_aft[i];
			delete h_recoeff_gen2tau1L_bef[i];
			delete h_recoeff_gen2tau1L_1m_aft[i];
			delete h_recoeff_gen2tau1L_2m_aft[i];
			delete h_recoeff_gen2tau2L_bef[i];
			delete h_recoeff_gen2tau2L_1m_aft[i];
			delete h_recoeff_gen2tau2L_2m_aft[i];
			delete h_recopurity_gen1tau0L_bef[i];
			delete h_recopurity_gen1tau0L_aft[i];
			delete h_recopurity_gen1tau1L_bef[i];
			delete h_recopurity_gen1tau1L_aft[i];
			delete h_recopurity_gen1tau2L_bef[i];
			delete h_recopurity_gen1tau2L_aft[i];
			delete h_recopurity_gen1tau3L_bef[i];
			delete h_recopurity_gen1tau3L_aft[i];
			delete h_recopurity_gen2tau0L_bef[i];
			delete h_recopurity_gen2tau0L_aft[i];
			delete h_recopurity_gen2tau1L_bef[i];
			delete h_recopurity_gen2tau1L_aft[i];
			delete h_recopurity_gen2tau2L_bef[i];
			delete h_recopurity_gen2tau2L_aft[i];
			
		}

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

int genrecoEff (vector<TLorentzVector> *genTaus, vector<TLorentzVector> *recoTaus) {

	float dRmin = 10.0;
	int countMatches = 0;
	for (int rTau = 0; rTau < recoTaus->size(); rTau++) {

		for (int gTau = 0; gTau < genTaus->size(); gTau++) {

			float dEta = fabs( genTaus->at(gTau).Eta() - recoTaus->at(rTau).Eta() );
			float dPhi = fabs( genTaus->at(gTau).Phi() - recoTaus->at(rTau).Phi() );
			if(dPhi > 3.14159265358979323846) dPhi  = 2*3.14159265358979323846 - dPhi;
			Float_t dR = sqrt( pow(dEta, 2) + pow(dPhi, 2) );
			if ( dR < dRmin ) {
                            
				dRmin = dR;
		                            
			}

		}
	
		if (dRmin < 0.4) countMatches++;
 
	}

	return countMatches;

}

void writeTEfficiency(TH1F* hBef, TH1F* hAft, map<string, string>::iterator file_it, TString name) {

	std::string hBefName(hBef->GetName());
	hBefName.append("_");
	hBefName.append(file_it->first);
	std::string hAftName(hAft->GetName());
	hAftName.append("_");
	hAftName.append(file_it->first);
	hBef->Write(hBefName.c_str());
	hAft->Write(hAftName.c_str());
   
}
