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
#include "tauID_WP_study.h"

void tauID_WP_study() {

	gBenchmark->Start("running time");
	gROOT->ProcessLine(".L Loader.C+");

	map<string, string>::iterator file_it = file.begin();

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
		//use array of TH1Fs; 0-th histo corresponds to tighter WP in VsJet; 6-th histo corresponds to looser QP in VsJet
		// 1tau0L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_1tau0L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_1tau0L_bef_%d", i);
			sprintf(title, "h_recoeff_1tau0L_bef_%d", i);
			h_recoeff_1tau0L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_1tau0L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_1tau0L_bef_%d", i);
			sprintf(title, "h_recopurity_1tau0L_bef_%d", i);
			h_recopurity_1tau0L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		// 1tau1L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_1tau1L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_1tau1L_bef_%d", i);
			sprintf(title, "h_recoeff_1tau1L_bef_%d", i);
			h_recoeff_1tau1L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_1tau1L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_1tau1L_bef_%d", i);
			sprintf(title, "h_recopurity_1tau1L_bef_%d", i);
			h_recopurity_1tau1L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		// 1tau2L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_1tau2L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_1tau2L_bef_%d", i);
			sprintf(title, "h_recoeff_1tau2L_bef_%d", i);
			h_recoeff_1tau2L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_1tau2L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_1tau2L_bef_%d", i);
			sprintf(title, "h_recopurity_1tau2L_bef_%d", i);
			h_recopurity_1tau2L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		// 1tau3L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_1tau3L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_1tau3L_bef_%d", i);
			sprintf(title, "h_recoeff_1tau3L_bef_%d", i);
			h_recoeff_1tau3L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_1tau3L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_1tau3L_bef_%d", i);
			sprintf(title, "h_recopurity_1tau3L_bef_%d", i);
			h_recopurity_1tau3L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		// 2tau0L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_2tau0L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_2tau0L_bef_%d", i);
			sprintf(title, "h_recoeff_2tau0L_bef_%d", i);
			h_recoeff_2tau0L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_2tau0L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_2tau0L_bef_%d", i);
			sprintf(title, "h_recopurity_2tau0L_bef_%d", i);
			h_recopurity_2tau0L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		// 2tau1L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_2tau1L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_2tau1L_bef_%d", i);
			sprintf(title, "h_recoeff_2tau1L_bef_%d", i);
			h_recoeff_2tau1L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_2tau1L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_2tau1L_bef_%d", i);
			sprintf(title, "h_recopurity_2tau1L_bef_%d", i);
			h_recopurity_2tau1L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		// 2tau2L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_2tau2L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_2tau2L_bef_%d", i);
			sprintf(title, "h_recoeff_2tau2L_bef_%d", i);
			h_recoeff_2tau2L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_2tau2L_bef[7];
		for (int i = 0; i < 7; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_2tau2L_bef_%d", i);
			sprintf(title, "h_recopurity_2tau2L_bef_%d", i);
			h_recopurity_2tau2L_bef[i] = new TH1F(name, title, 30, 0, 30);
		
		}
		TH1::AddDirectory(kTRUE);

		TChain mychain("tree");
		mychain.Add(input_base_dir + "v3*.root");
		TChain mychain2("allevents");
		mychain2.Add(input_base_dir + "v3*.root");
		
		cout << "Computing the sum of gen event weights..." << endl;
		TH1::StatOverflows(kTRUE);
		TH1D * genEvtWeights = new TH1D("genEvtWeights", "genEvtWeights", 10, -10, 10 );
		double gen_sum_of_weights = 0.0;
		mychain2.Project(genEvtWeights->GetName(), "genWeight_allEvents");
		cout << "genEvtWeights->GetMean(): " << genEvtWeights->GetMean() << endl;
		cout << "genEvtWeights->GetEntries(): " << genEvtWeights->GetEntries() << endl; 
		gen_sum_of_weights = genEvtWeights->GetMean()*genEvtWeights->GetEntries();
		cout << gen_sum_of_weights << endl;
		TH1::StatOverflows(kFALSE);

		double mygenEvtWeight = 0;
		mychain.SetBranchAddress( "EVENT_genWeight_", &mygenEvtWeight );

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
			if (ievent > 100) break;
			if ( !(ievent % 100000 ) ) cout << "ievent  =  " << ievent << endl;
			//get i-th entry in tree
			mychain.GetEntry( ievent );
			if (!(mygenEvtWeight > 0)) continue;
			/////////////////////////////////////////////////////////////////////
			///////////////////// DEFINE CATEGORY CUTS //////////////////////////
			/////////////////////////////////////////////////////////////////////
			/*
			bool is1tau0L = (mytausT->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2);
			bool is1tau1e = (mytausT->size()==1 && myleptonsMVAT->size() == 1 && myelesMVAT->size()==1 && myjetsL->size()>=6 && mybjetsM->size()>=2);
			bool is1tau1mu = (mytausT->size()==1 && myleptonsMVAT->size() == 1 && mymuonsT->size()==1 &&  myjetsL->size()>=6 && mybjetsM->size()>=2);
			bool is1tau2L = (mytausT->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2);
			bool is1tau3L = (mytausT->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2);
			bool is2tau0L = (mytausT->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2);
			bool is2tau1e = (mytausT->size()==2 && myleptonsMVAT->size() == 1 && myelesMVAT->size()==1 &&  myjetsL->size()>=4 && mybjetsM->size()>=2);
			bool is2tau1mu = (mytausT->size()==2 && myleptonsMVAT->size() == 1 && mymuonsT->size()==1 &&  myjetsL->size()>=4 && mybjetsM->size()>=2);
			bool is2tau2L = (mytausT->size()==2 && (myelesMVAT->size()+mymuonsT->size())==2 && myjetsL->size()>=2 && mybjetsM->size()>=2);
			*/
			/////////////////////////////////////////////////////////////////////
			///////////////////// DEFINE TRIGGER CUTS ///////////////////////////
			/////////////////////////////////////////////////////////////////////

			bool isSignalTrig = (myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1 || myHLT_PFJet450 == 1);
		
		}//end loop over events
		
		file_it++;

	}//end loop over files

}//end
