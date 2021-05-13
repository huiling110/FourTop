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

	TFile *outputfile = new TFile( "tauID_WP_study_output_gencatwithNlep.root", "RECREATE" );

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
			h_recoeff_gen1tau0L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_gen1tau0L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau0L_aft_%d", i);
			sprintf(title, "h_recoeff_gen1tau0L_aft_%d", i);
			h_recoeff_gen1tau0L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_gen1tau0L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_gen1tau0L_%d", i);
			sprintf(title, "h_correct_recoeff_gen1tau0L_%d", i);
			h_correct_recoeff_gen1tau0L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen1tau0L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau0L_bef_%d", i);
			sprintf(title, "h_recopurity_gen1tau0L_bef_%d", i);
			h_recopurity_gen1tau0L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_gen1tau0L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau0L_aft_%d", i);
			sprintf(title, "h_recopurity_gen1tau0L_aft_%d", i);
			h_recopurity_gen1tau0L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_gen1tau0L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_gen1tau0L_%d", i);
			sprintf(title, "h_correct_recopurity_gen1tau0L_%d", i);
			h_correct_recopurity_gen1tau0L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//gen1tau1L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_gen1tau1L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau1L_bef_%d", i);
			sprintf(title, "h_recoeff_gen1tau1L_bef_%d", i);
			h_recoeff_gen1tau1L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_gen1tau1L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau1L_aft_%d", i);
			sprintf(title, "h_recoeff_gen1tau1L_aft_%d", i);
			h_recoeff_gen1tau1L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_gen1tau1L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_gen1tau1L_%d", i);
			sprintf(title, "h_correct_recoeff_gen1tau1L_%d", i);
			h_correct_recoeff_gen1tau1L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen1tau1L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau1L_bef_%d", i);
			sprintf(title, "h_recopurity_gen1tau1L_bef_%d", i);
			h_recopurity_gen1tau1L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_gen1tau1L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau1L_aft_%d", i);
			sprintf(title, "h_recopurity_gen1tau1L_aft_%d", i);
			h_recopurity_gen1tau1L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_gen1tau1L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_gen1tau1L_%d", i);
			sprintf(title, "h_correct_recopurity_gen1tau1L_%d", i);
			h_correct_recopurity_gen1tau1L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//gen1tau2L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_gen1tau2L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau2L_bef_%d", i);
			sprintf(title, "h_recoeff_gen1tau2L_bef_%d", i);
			h_recoeff_gen1tau2L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_gen1tau2L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau2L_aft_%d", i);
			sprintf(title, "h_recoeff_gen1tau2L_aft_%d", i);
			h_recoeff_gen1tau2L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_gen1tau2L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_gen1tau2L_%d", i);
			sprintf(title, "h_correct_recoeff_gen1tau2L_%d", i);
			h_correct_recoeff_gen1tau2L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen1tau2L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau2L_bef_%d", i);
			sprintf(title, "h_recopurity_gen1tau2L_bef_%d", i);
			h_recopurity_gen1tau2L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_gen1tau2L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau2L_aft_%d", i);
			sprintf(title, "h_recopurity_gen1tau2L_aft_%d", i);
			h_recopurity_gen1tau2L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_gen1tau2L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_gen1tau2L_%d", i);
			sprintf(title, "h_correct_recopurity_gen1tau2L_%d", i);
			h_correct_recopurity_gen1tau2L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//gen1tau3L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_gen1tau3L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau3L_bef_%d", i);
			sprintf(title, "h_recoeff_gen1tau3L_bef_%d", i);
			h_recoeff_gen1tau3L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_gen1tau3L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen1tau3L_aft_%d", i);
			sprintf(title, "h_recoeff_gen1tau3L_aft_%d", i);
			h_recoeff_gen1tau3L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_gen1tau3L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_gen1tau3L_%d", i);
			sprintf(title, "h_correct_recoeff_gen1tau3L_%d", i);
			h_correct_recoeff_gen1tau3L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen1tau3L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau3L_bef_%d", i);
			sprintf(title, "h_recopurity_gen1tau3L_bef_%d", i);
			h_recopurity_gen1tau3L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_gen1tau3L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen1tau3L_aft_%d", i);
			sprintf(title, "h_recopurity_gen1tau3L_aft_%d", i);
			h_recopurity_gen1tau3L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_gen1tau3L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_gen1tau3L_%d", i);
			sprintf(title, "h_correct_recopurity_gen1tau3L_%d", i);
			h_correct_recopurity_gen1tau3L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//gen2tau0L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_gen2tau0L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau0L_bef_%d", i);
			sprintf(title, "h_recoeff_gen2tau0L_bef_%d", i);
			h_recoeff_gen2tau0L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_gen2tau0L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau0L_aft_%d", i);
			sprintf(title, "h_recoeff_gen2tau0L_aft_%d", i);
			h_recoeff_gen2tau0L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_gen2tau0L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_gen2tau0L_%d", i);
			sprintf(title, "h_correct_recoeff_gen2tau0L_%d", i);
			h_correct_recoeff_gen2tau0L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen2tau0L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen2tau0L_bef_%d", i);
			sprintf(title, "h_recopurity_gen2tau0L_bef_%d", i);
			h_recopurity_gen2tau0L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_gen2tau0L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen2tau0L_aft_%d", i);
			sprintf(title, "h_recopurity_gen2tau0L_aft_%d", i);
			h_recopurity_gen2tau0L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_gen2tau0L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_gen2tau0L_%d", i);
			sprintf(title, "h_correct_recopurity_gen2tau0L_%d", i);
			h_correct_recopurity_gen2tau0L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//gen2tau1L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_gen2tau1L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau1L_bef_%d", i);
			sprintf(title, "h_recoeff_gen2tau1L_bef_%d", i);
			h_recoeff_gen2tau1L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_gen2tau1L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau1L_aft_%d", i);
			sprintf(title, "h_recoeff_gen2tau1L_aft_%d", i);
			h_recoeff_gen2tau1L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_gen2tau1L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_gen2tau1L_%d", i);
			sprintf(title, "h_correct_recoeff_gen2tau1L_%d", i);
			h_correct_recoeff_gen2tau1L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen2tau1L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen2tau1L_bef_%d", i);
			sprintf(title, "h_recopurity_gen2tau1L_bef_%d", i);
			h_recopurity_gen2tau1L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_gen2tau1L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen2tau1L_aft_%d", i);
			sprintf(title, "h_recopurity_gen2tau1L_aft_%d", i);
			h_recopurity_gen2tau1L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_gen2tau1L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_gen2tau1L_%d", i);
			sprintf(title, "h_correct_recopurity_gen2tau1L_%d", i);
			h_correct_recopurity_gen2tau1L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//gen2tau2L category
		//histos for reconstruction efficiency
		TH1F* h_recoeff_gen2tau2L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau2L_bef_%d", i);
			sprintf(title, "h_recoeff_gen2tau2L_bef_%d", i);
			h_recoeff_gen2tau2L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_gen2tau2L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_gen2tau2L_aft_%d", i);
			sprintf(title, "h_recoeff_gen2tau2L_aft_%d", i);
			h_recoeff_gen2tau2L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_gen2tau2L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_gen2tau2L_%d", i);
			sprintf(title, "h_correct_recoeff_gen2tau2L_%d", i);
			h_correct_recoeff_gen2tau2L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_gen2tau2L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen2tau2L_bef_%d", i);
			sprintf(title, "h_recopurity_gen2tau2L_bef_%d", i);
			h_recopurity_gen2tau2L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_gen2tau2L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_gen2tau2L_aft_%d", i);
			sprintf(title, "h_recopurity_gen2tau2L_aft_%d", i);
			h_recopurity_gen2tau2L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_gen2tau2L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_gen2tau2L_%d", i);
			sprintf(title, "h_correct_recopurity_gen2tau2L_%d", i);
			h_correct_recopurity_gen2tau2L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//nocat category
		//histos for significance
		TH1F* h_significance_nocat[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_significance_nocat_%d", i);
			sprintf(title, "h_significance_nocat_%d", i);
			h_significance_nocat[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction efficiency
		TH1F* h_recoeff_nocat_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_nocat_bef_%d", i);
			sprintf(title, "h_recoeff_nocat_bef_%d", i);
			h_recoeff_nocat_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_nocat_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_nocat_aft_%d", i);
			sprintf(title, "h_recoeff_nocat_aft_%d", i);
			h_recoeff_nocat_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_nocat[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_nocat_%d", i);
			sprintf(title, "h_correct_recoeff_nocat_%d", i);
			h_correct_recoeff_nocat[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_nocat_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_nocat_bef_%d", i);
			sprintf(title, "h_recopurity_nocat_bef_%d", i);
			h_recopurity_nocat_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_nocat_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_nocat_aft_%d", i);
			sprintf(title, "h_recopurity_nocat_aft_%d", i);
			h_recopurity_nocat_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_nocat[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_nocat_%d", i);
			sprintf(title, "h_correct_recopurity_nocat_%d", i);
			h_correct_recopurity_nocat[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//1tau0L category
		//histos for significance
		TH1F* h_significance_1tau0L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_significance_1tau0L_%d", i);
			sprintf(title, "h_significance_1tau0L_%d", i);
			h_significance_1tau0L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction efficiency
		TH1F* h_recoeff_1tau0L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_1tau0L_bef_%d", i);
			sprintf(title, "h_recoeff_1tau0L_bef_%d", i);
			h_recoeff_1tau0L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_1tau0L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_1tau0L_aft_%d", i);
			sprintf(title, "h_recoeff_1tau0L_aft_%d", i);
			h_recoeff_1tau0L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_1tau0L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_1tau0L_%d", i);
			sprintf(title, "h_correct_recoeff_1tau0L_%d", i);
			h_correct_recoeff_1tau0L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_1tau0L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_1tau0L_bef_%d", i);
			sprintf(title, "h_recopurity_1tau0L_bef_%d", i);
			h_recopurity_1tau0L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_1tau0L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_1tau0L_aft_%d", i);
			sprintf(title, "h_recopurity_1tau0L_aft_%d", i);
			h_recopurity_1tau0L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_1tau0L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_1tau0L_%d", i);
			sprintf(title, "h_correct_recopurity_1tau0L_%d", i);
			h_correct_recopurity_1tau0L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//1tau1L category
		//histos for significance
		TH1F* h_significance_1tau1L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_significance_1tau1L_%d", i);
			sprintf(title, "h_significance_1tau1L_%d", i);
			h_significance_1tau1L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction efficiency
		TH1F* h_recoeff_1tau1L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_1tau1L_bef_%d", i);
			sprintf(title, "h_recoeff_1tau1L_bef_%d", i);
			h_recoeff_1tau1L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_1tau1L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_1tau1L_aft_%d", i);
			sprintf(title, "h_recoeff_1tau1L_aft_%d", i);
			h_recoeff_1tau1L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_1tau1L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_1tau1L_%d", i);
			sprintf(title, "h_correct_recoeff_1tau1L_%d", i);
			h_correct_recoeff_1tau1L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_1tau1L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_1tau1L_bef_%d", i);
			sprintf(title, "h_recopurity_1tau1L_bef_%d", i);
			h_recopurity_1tau1L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_1tau1L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_1tau1L_aft_%d", i);
			sprintf(title, "h_recopurity_1tau1L_aft_%d", i);
			h_recopurity_1tau1L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_1tau1L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_1tau1L_%d", i);
			sprintf(title, "h_correct_recopurity_1tau1L_%d", i);
			h_correct_recopurity_1tau1L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//1tau2L category
		//histos for significance
		TH1F* h_significance_1tau2L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_significance_1tau2L_%d", i);
			sprintf(title, "h_significance_1tau2L_%d", i);
			h_significance_1tau2L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction efficiency
		TH1F* h_recoeff_1tau2L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_1tau2L_bef_%d", i);
			sprintf(title, "h_recoeff_1tau2L_bef_%d", i);
			h_recoeff_1tau2L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_1tau2L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_1tau2L_aft_%d", i);
			sprintf(title, "h_recoeff_1tau2L_aft_%d", i);
			h_recoeff_1tau2L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_1tau2L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_1tau2L_%d", i);
			sprintf(title, "h_correct_recoeff_1tau2L_%d", i);
			h_correct_recoeff_1tau2L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_1tau2L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_1tau2L_bef_%d", i);
			sprintf(title, "h_recopurity_1tau2L_bef_%d", i);
			h_recopurity_1tau2L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_1tau2L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_1tau2L_aft_%d", i);
			sprintf(title, "h_recopurity_1tau2L_aft_%d", i);
			h_recopurity_1tau2L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_1tau2L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_1tau2L_%d", i);
			sprintf(title, "h_correct_recopurity_1tau2L_%d", i);
			h_correct_recopurity_1tau2L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		// 1tau3L category
		//histos for significance
		TH1F* h_significance_1tau3L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_significance_1tau3L_%d", i);
			sprintf(title, "h_significance_1tau3L_%d", i);
			h_significance_1tau3L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction efficiency
		TH1F* h_recoeff_1tau3L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_1tau3L_bef_%d", i);
			sprintf(title, "h_recoeff_1tau3L_bef_%d", i);
			h_recoeff_1tau3L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_1tau3L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_1tau3L_aft_%d", i);
			sprintf(title, "h_recoeff_1tau3L_aft_%d", i);
			h_recoeff_1tau3L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_1tau3L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_1tau3L_%d", i);
			sprintf(title, "h_correct_recoeff_1tau3L_%d", i);
			h_correct_recoeff_1tau3L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_1tau3L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_1tau3L_bef_%d", i);
			sprintf(title, "h_recopurity_1tau3L_bef_%d", i);
			h_recopurity_1tau3L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_1tau3L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_1tau3L_aft_%d", i);
			sprintf(title, "h_recopurity_1tau3L_aft_%d", i);
			h_recopurity_1tau3L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_1tau3L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_1tau3L_%d", i);
			sprintf(title, "h_correct_recopurity_1tau3L_%d", i);
			h_correct_recopurity_1tau3L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		// 2tau0L category
		//histos for significance
		TH1F* h_significance_2tau0L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_significance_2tau0L_%d", i);
			sprintf(title, "h_significance_2tau0L_%d", i);
			h_significance_2tau0L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction efficiency
		TH1F* h_recoeff_2tau0L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_2tau0L_bef_%d", i);
			sprintf(title, "h_recoeff_2tau0L_bef_%d", i);
			h_recoeff_2tau0L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_2tau0L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_2tau0L_aft_%d", i);
			sprintf(title, "h_recoeff_2tau0L_aft_%d", i);
			h_recoeff_2tau0L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_2tau0L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_2tau0L_%d", i);
			sprintf(title, "h_correct_recoeff_2tau0L_%d", i);
			h_correct_recoeff_2tau0L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_2tau0L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_2tau0L_bef_%d", i);
			sprintf(title, "h_recopurity_2tau0L_bef_%d", i);
			h_recopurity_2tau0L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_2tau0L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_2tau0L_aft_%d", i);
			sprintf(title, "h_recopurity_2tau0L_aft_%d", i);
			h_recopurity_2tau0L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_2tau0L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_2tau0L_%d", i);
			sprintf(title, "h_correct_recopurity_2tau0L_%d", i);
			h_correct_recopurity_2tau0L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		// 2tau1L category
		//histos for significance
		TH1F* h_significance_2tau1L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_significance_2tau1L_%d", i);
			sprintf(title, "h_significance_2tau1L_%d", i);
			h_significance_2tau1L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction efficiency
		TH1F* h_recoeff_2tau1L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_2tau1L_bef_%d", i);
			sprintf(title, "h_recoeff_2tau1L_bef_%d", i);
			h_recoeff_2tau1L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_2tau1L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_2tau1L_aft_%d", i);
			sprintf(title, "h_recoeff_2tau1L_aft_%d", i);
			h_recoeff_2tau1L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_2tau1L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_2tau1L_%d", i);
			sprintf(title, "h_correct_recoeff_2tau1L_%d", i);
			h_correct_recoeff_2tau1L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_2tau1L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_2tau1L_bef_%d", i);
			sprintf(title, "h_recopurity_2tau1L_bef_%d", i);
			h_recopurity_2tau1L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_2tau1L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_2tau1L_aft_%d", i);
			sprintf(title, "h_recopurity_2tau1L_aft_%d", i);
			h_recopurity_2tau1L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_2tau1L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_2tau1L_%d", i);
			sprintf(title, "h_correct_recopurity_2tau1L_%d", i);
			h_correct_recopurity_2tau1L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		// 2tau2L category
		//histos for significance
		TH1F* h_significance_2tau2L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_significance_2tau2L_%d", i);
			sprintf(title, "h_significance_2tau2L_%d", i);
			h_significance_2tau2L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction efficiency
		TH1F* h_recoeff_2tau2L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_2tau2L_bef_%d", i);
			sprintf(title, "h_recoeff_2tau2L_bef_%d", i);
			h_recoeff_2tau2L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recoeff_2tau2L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recoeff_2tau2L_aft_%d", i);
			sprintf(title, "h_recoeff_2tau2L_aft_%d", i);
			h_recoeff_2tau2L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recoeff_2tau2L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recoeff_2tau2L_%d", i);
			sprintf(title, "h_correct_recoeff_2tau2L_%d", i);
			h_correct_recoeff_2tau2L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		//histos for reconstruction purity
		TH1F* h_recopurity_2tau2L_bef[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_2tau2L_bef_%d", i);
			sprintf(title, "h_recopurity_2tau2L_bef_%d", i);
			h_recopurity_2tau2L_bef[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_recopurity_2tau2L_aft[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_recopurity_2tau2L_aft_%d", i);
			sprintf(title, "h_recopurity_2tau2L_aft_%d", i);
			h_recopurity_2tau2L_aft[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_correct_recopurity_2tau2L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_correct_recopurity_2tau2L_%d", i);
			sprintf(title, "h_correct_recopurity_2tau2L_%d", i);
			h_correct_recopurity_2tau2L[i] = new TH1F(name, title, 50, 0, 200);		
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

			//reco-level categories
			bool is1tau0L[8] = {
				(mytausT_VVTightVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2),
				(mytausT_VTightVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2),
				(mytausT_TightVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2),
				(mytausT_MediumVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2),
				(mytausT_LooseVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2),
				(mytausT_VLooseVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2),
				(mytausT_VVLooseVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2),
				(mytausT_VVVLooseVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2)
			};
			bool is1tau1L[8] = {
				(mytausT_VVTightVsJet->size()==1 && myleptonsMVAT->size()==1 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_VTightVsJet->size()==1 && myleptonsMVAT->size()==1 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_TightVsJet->size()==1 && myleptonsMVAT->size()==1 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_MediumVsJet->size()==1 && myleptonsMVAT->size()==1 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_LooseVsJet->size()==1 && myleptonsMVAT->size()==1 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_VLooseVsJet->size()==1 && myleptonsMVAT->size()==1 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_VVLooseVsJet->size()==1 && myleptonsMVAT->size()==1 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_VVVLooseVsJet->size()==1 && myleptonsMVAT->size()==1 && myjetsL->size()>=6 && mybjetsM->size()>=2)
			}; 
			bool is1tau2L[8] = {
				(mytausT_VVTightVsJet->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_VTightVsJet->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_TightVsJet->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_MediumVsJet->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_LooseVsJet->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_VLooseVsJet->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_VVLooseVsJet->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_VVVLooseVsJet->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2),
			};
			bool is1tau3L[8] = {
				(mytausT_VVTightVsJet->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_VTightVsJet->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_TightVsJet->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_MediumVsJet->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_LooseVsJet->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_VLooseVsJet->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_VVLooseVsJet->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_VVVLooseVsJet->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2),
			};
			bool is2tau0L[8] = {
				(mytausT_VVTightVsJet->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_VTightVsJet->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_TightVsJet->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_MediumVsJet->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_LooseVsJet->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_VLooseVsJet->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_VVLooseVsJet->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2),
				(mytausT_VVVLooseVsJet->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2)
			};
			bool is2tau1L[8] = {
				(mytausT_VVTightVsJet->size()==2 && myleptonsMVAT->size()==1 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_VTightVsJet->size()==2 && myleptonsMVAT->size()==1 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_TightVsJet->size()==2 && myleptonsMVAT->size()==1 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_MediumVsJet->size()==2 && myleptonsMVAT->size()==1 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_LooseVsJet->size()==2 && myleptonsMVAT->size()==1 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_VLooseVsJet->size()==2 && myleptonsMVAT->size()==1 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_VVLooseVsJet->size()==2 && myleptonsMVAT->size()==1 && myjetsL->size()>=4 && mybjetsM->size()>=2),
				(mytausT_VVVLooseVsJet->size()==2 && myleptonsMVAT->size()==1 && myjetsL->size()>=4 && mybjetsM->size()>=2)
			};
			bool is2tau2L[8] = {
				(mytausT_VVTightVsJet->size()==2 && myleptonsMVAT->size()==2 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_VTightVsJet->size()==2 && myleptonsMVAT->size()==2 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_TightVsJet->size()==2 && myleptonsMVAT->size()==2 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_MediumVsJet->size()==2 && myleptonsMVAT->size()==2 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_LooseVsJet->size()==2 && myleptonsMVAT->size()==2 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_VLooseVsJet->size()==2 && myleptonsMVAT->size()==2 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_VVLooseVsJet->size()==2 && myleptonsMVAT->size()==2 && myjetsL->size()>=2 && mybjetsM->size()>=2),
				(mytausT_VVVLooseVsJet->size()==2 && myleptonsMVAT->size()==2 && myjetsL->size()>=2 && mybjetsM->size()>=2)
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

				if (isgen1tau0L && mytausT[i]->size()==1 && myleptonsMVAT->size()==0){

					recoEff(mygenTaus, mytausT[i], h_recoeff_gen1tau0L_bef[i], h_recoeff_gen1tau0L_aft[i], mygenEvtWeight, h_correct_recoeff_gen1tau0L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_gen1tau0L_bef[i], h_recopurity_gen1tau0L_aft[i], mygenEvtWeight, h_correct_recopurity_gen1tau0L[i]);
				}

				if (isgen1tau1L && mytausT[i]->size()==1 && myleptonsMVAT->size()==1){

					recoEff(mygenTaus, mytausT[i], h_recoeff_gen1tau1L_bef[i], h_recoeff_gen1tau1L_aft[i], mygenEvtWeight, h_correct_recoeff_gen1tau1L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_gen1tau1L_bef[i], h_recopurity_gen1tau1L_aft[i], mygenEvtWeight, h_correct_recopurity_gen1tau1L[i]);
				}

				if (isgen1tau2L && mytausT[i]->size()==1 && myleptonsMVAT->size()==2){

					recoEff(mygenTaus, mytausT[i], h_recoeff_gen1tau2L_bef[i], h_recoeff_gen1tau2L_aft[i], mygenEvtWeight, h_correct_recoeff_gen1tau2L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_gen1tau2L_bef[i], h_recopurity_gen1tau2L_aft[i], mygenEvtWeight, h_correct_recopurity_gen1tau2L[i]);
				
				}

				if (isgen1tau3L && mytausT[i]->size()==1 && myleptonsMVAT->size()==3){

					recoEff(mygenTaus, mytausT[i], h_recoeff_gen1tau3L_bef[i], h_recoeff_gen1tau3L_aft[i], mygenEvtWeight, h_correct_recoeff_gen1tau3L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_gen1tau3L_bef[i], h_recopurity_gen1tau3L_aft[i], mygenEvtWeight, h_correct_recopurity_gen1tau3L[i]);

				}

				if (isgen2tau0L && mytausT[i]->size()==2 && myleptonsMVAT->size()==0){

					recoEff(mygenTaus, mytausT[i], h_recoeff_gen2tau0L_bef[i], h_recoeff_gen2tau0L_aft[i], mygenEvtWeight, h_correct_recoeff_gen2tau0L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_gen2tau0L_bef[i], h_recopurity_gen2tau0L_aft[i], mygenEvtWeight, h_correct_recopurity_gen2tau0L[i]);
				
				}


				if (isgen2tau1L && mytausT[i]->size()==2 && myleptonsMVAT->size()==1){

					recoEff(mygenTaus, mytausT[i], h_recoeff_gen2tau1L_bef[i], h_recoeff_gen2tau1L_aft[i], mygenEvtWeight, h_correct_recoeff_gen2tau1L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_gen2tau1L_bef[i], h_recopurity_gen2tau1L_aft[i], mygenEvtWeight, h_correct_recopurity_gen2tau1L[i]);
				
				}

				if (isgen2tau2L && mytausT[i]->size()==2 && myleptonsMVAT->size()==2){

					recoEff(mygenTaus, mytausT[i], h_recoeff_gen2tau2L_bef[i], h_recoeff_gen2tau2L_aft[i], mygenEvtWeight, h_correct_recoeff_gen2tau2L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_gen2tau2L_bef[i], h_recopurity_gen2tau2L_aft[i], mygenEvtWeight, h_correct_recopurity_gen2tau2L[i]);
				
				}

				if (mytausT[i]->size() > 0) h_significance_nocat[i]->Fill(mytausT[i]->at(0).Pt(), mygenEvtWeight);
				recoEff(mygenTaus, mytausT[i], h_recoeff_nocat_bef[i], h_recoeff_nocat_aft[i], mygenEvtWeight, h_correct_recoeff_nocat[i]);
			   	recoPurity(mygenTaus, mytausT[i], h_recopurity_nocat_bef[i], h_recopurity_nocat_aft[i], mygenEvtWeight, h_correct_recopurity_nocat[i]);

				if (is1tau0L[i]) {
					h_significance_1tau0L[i]->Fill(mytausT[i]->at(0).Pt(), mygenEvtWeight);
					recoEff(mygenTaus, mytausT[i], h_recoeff_1tau0L_bef[i], h_recoeff_1tau0L_aft[i], mygenEvtWeight, h_correct_recoeff_1tau0L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_1tau0L_bef[i], h_recopurity_1tau0L_aft[i], mygenEvtWeight, h_correct_recopurity_1tau0L[i]);
				}

				if (is1tau1L[i]) {
					h_significance_1tau1L[i]->Fill(mytausT[i]->at(0).Pt(), mygenEvtWeight);
					recoEff(mygenTaus, mytausT[i], h_recoeff_1tau1L_bef[i], h_recoeff_1tau1L_aft[i], mygenEvtWeight, h_correct_recoeff_1tau1L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_1tau1L_bef[i], h_recopurity_1tau1L_aft[i], mygenEvtWeight, h_correct_recopurity_1tau1L[i]);
				}

				if (is1tau2L[i]) {
					h_significance_1tau2L[i]->Fill(mytausT[i]->at(0).Pt(), mygenEvtWeight);
					recoEff(mygenTaus, mytausT[i], h_recoeff_1tau2L_bef[i], h_recoeff_1tau2L_aft[i], mygenEvtWeight, h_correct_recoeff_1tau2L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_1tau2L_bef[i], h_recopurity_1tau2L_aft[i], mygenEvtWeight, h_correct_recopurity_1tau2L[i]);
				}

				if (is1tau3L[i]) {
					h_significance_1tau3L[i]->Fill(mytausT[i]->at(0).Pt(), mygenEvtWeight);
					recoEff(mygenTaus, mytausT[i], h_recoeff_1tau3L_bef[i], h_recoeff_1tau3L_aft[i], mygenEvtWeight, h_correct_recoeff_1tau3L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_1tau3L_bef[i], h_recopurity_1tau3L_aft[i], mygenEvtWeight, h_correct_recopurity_1tau3L[i]);
				}

				if (is2tau0L[i]) {
					h_significance_2tau0L[i]->Fill(mytausT[i]->at(0).Pt(), mygenEvtWeight);
					recoEff(mygenTaus, mytausT[i], h_recoeff_2tau0L_bef[i], h_recoeff_2tau0L_aft[i], mygenEvtWeight, h_correct_recoeff_2tau0L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_2tau0L_bef[i], h_recopurity_2tau0L_aft[i], mygenEvtWeight, h_correct_recopurity_2tau0L[i]);
				}
			
				if (is2tau1L[i]) {
					h_significance_2tau1L[i]->Fill(mytausT[i]->at(0).Pt(), mygenEvtWeight);
					recoEff(mygenTaus, mytausT[i], h_recoeff_2tau1L_bef[i], h_recoeff_2tau1L_aft[i], mygenEvtWeight, h_correct_recoeff_2tau1L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_2tau1L_bef[i], h_recopurity_2tau1L_aft[i], mygenEvtWeight, h_correct_recopurity_2tau1L[i]);
				}
				
				if (is2tau2L[i]) {
					h_significance_2tau2L[i]->Fill(mytausT[i]->at(0).Pt(), mygenEvtWeight);
					recoEff(mygenTaus, mytausT[i], h_recoeff_2tau2L_bef[i], h_recoeff_2tau2L_aft[i], mygenEvtWeight, h_correct_recoeff_2tau2L[i]);
					recoPurity(mygenTaus, mytausT[i], h_recopurity_2tau2L_bef[i], h_recopurity_2tau2L_aft[i], mygenEvtWeight, h_correct_recopurity_2tau2L[i]);
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
			char recoPurityname[200];
			sprintf(recoEffname, "recoEff_gen1tau0L_%d_", i);
			writeTEfficiency(h_recoeff_gen1tau0L_bef[i], h_recoeff_gen1tau0L_aft[i], h_correct_recoeff_gen1tau0L[i], file_it, recoEffname);
			sprintf(recoPurityname, "recoPurity_gen1tau0L_%d_", i);
			writeTEfficiency(h_recopurity_gen1tau0L_bef[i], h_recopurity_gen1tau0L_aft[i], h_correct_recopurity_gen1tau0L[i], file_it, recoPurityname);

			sprintf(recoEffname, "recoEff_gen1tau1L_%d_", i);
			writeTEfficiency(h_recoeff_gen1tau1L_bef[i], h_recoeff_gen1tau1L_aft[i], h_correct_recoeff_gen1tau1L[i], file_it, recoEffname);
			sprintf(recoPurityname, "recoPurity_gen1tau1L_%d_", i);
			writeTEfficiency(h_recopurity_gen1tau1L_bef[i], h_recopurity_gen1tau1L_aft[i], h_correct_recopurity_gen1tau1L[i], file_it, recoPurityname);

			sprintf(recoEffname, "recoEff_gen1tau2L_%d_", i);
			writeTEfficiency(h_recoeff_gen1tau2L_bef[i], h_recoeff_gen1tau2L_aft[i], h_correct_recoeff_gen1tau2L[i], file_it, recoEffname);
			sprintf(recoPurityname, "recoPurity_gen1tau2L_%d_", i);
			writeTEfficiency(h_recopurity_gen1tau2L_bef[i], h_recopurity_gen1tau2L_aft[i], h_correct_recopurity_gen1tau2L[i], file_it, recoPurityname);

			sprintf(recoEffname, "recoEff_gen1tau3L_%d_", i);
			writeTEfficiency(h_recoeff_gen1tau3L_bef[i], h_recoeff_gen1tau3L_aft[i], h_correct_recoeff_gen1tau3L[i], file_it, recoEffname);
			sprintf(recoPurityname, "recoPurity_gen1tau3L_%d_", i);
			writeTEfficiency(h_recopurity_gen1tau3L_bef[i], h_recopurity_gen1tau3L_aft[i], h_correct_recopurity_gen1tau3L[i], file_it, recoPurityname);

			sprintf(recoEffname, "recoEff_gen2tau0L_%d_", i);
			writeTEfficiency(h_recoeff_gen2tau0L_bef[i], h_recoeff_gen2tau0L_aft[i], h_correct_recoeff_gen2tau0L[i], file_it, recoEffname);
			sprintf(recoPurityname, "recoPurity_gen2tau0L_%d_", i);
			writeTEfficiency(h_recopurity_gen2tau0L_bef[i], h_recopurity_gen2tau0L_aft[i], h_correct_recopurity_gen2tau0L[i], file_it, recoPurityname);

			sprintf(recoEffname, "recoEff_gen2tau1L_%d_", i);
			writeTEfficiency(h_recoeff_gen2tau1L_bef[i], h_recoeff_gen2tau1L_aft[i], h_correct_recoeff_gen2tau1L[i], file_it, recoEffname);
			sprintf(recoPurityname, "recoPurity_gen2tau1L_%d_", i);
			writeTEfficiency(h_recopurity_gen2tau1L_bef[i], h_recopurity_gen2tau1L_aft[i], h_correct_recopurity_gen2tau1L[i], file_it, recoPurityname);
			
			sprintf(recoEffname, "recoEff_gen2tau2L_%d_", i);
			writeTEfficiency(h_recoeff_gen2tau2L_bef[i], h_recoeff_gen2tau2L_aft[i], h_correct_recoeff_gen2tau2L[i], file_it, recoEffname);
			sprintf(recoPurityname, "recoPurity_gen2tau2L_%d_", i);
			writeTEfficiency(h_recopurity_gen2tau2L_bef[i], h_recopurity_gen2tau2L_aft[i], h_correct_recopurity_gen2tau2L[i], file_it, recoPurityname);

			char significancename[200];
			sprintf(significancename, "h_significance_nocat_%d_", i);
			writeHisto(h_significance_nocat[i], file_it, significancename);
			sprintf(recoEffname, "recoEff_nocat_%d_", i);
			sprintf(recoPurityname, "recoPurity_nocat_%d_", i);
			writeTEfficiency(h_recoeff_nocat_bef[i], h_recoeff_nocat_aft[i], h_correct_recoeff_nocat[i], file_it, recoEffname);
			writeTEfficiency(h_recopurity_nocat_bef[i], h_recopurity_nocat_aft[i], h_correct_recopurity_nocat[i], file_it, recoPurityname);

			sprintf(significancename, "h_significance_1tau0L_%d_", i);
			writeHisto(h_significance_1tau0L[i], file_it, significancename);
			sprintf(recoEffname, "recoEff_1tau0L_%d_", i);
			sprintf(recoPurityname, "recoPurity_1tau0L_%d_", i);
			writeTEfficiency(h_recoeff_1tau0L_bef[i], h_recoeff_1tau0L_aft[i], h_correct_recoeff_1tau0L[i], file_it, recoEffname);
			writeTEfficiency(h_recopurity_1tau0L_bef[i], h_recopurity_1tau0L_aft[i], h_correct_recopurity_1tau0L[i], file_it, recoPurityname);

			sprintf(significancename, "h_significance_1tau1L_%d_", i);
			writeHisto(h_significance_1tau1L[i], file_it, significancename);
			sprintf(recoEffname, "recoEff_1tau1L_%d_", i);
			sprintf(recoPurityname, "recoPurity_1tau1L_%d_", i);
			writeTEfficiency(h_recoeff_1tau1L_bef[i], h_recoeff_1tau1L_aft[i], h_correct_recoeff_1tau1L[i], file_it, recoEffname);
			writeTEfficiency(h_recopurity_1tau1L_bef[i], h_recopurity_1tau1L_aft[i], h_correct_recopurity_1tau1L[i], file_it, recoPurityname);

			sprintf(significancename, "h_significance_1tau2L_%d_", i);
			writeHisto(h_significance_1tau2L[i], file_it, significancename);
			sprintf(recoEffname, "recoEff_1tau2L_%d_", i);
			sprintf(recoPurityname, "recoPurity_1tau2L_%d_", i);
			writeTEfficiency(h_recoeff_1tau2L_bef[i], h_recoeff_1tau2L_aft[i], h_correct_recoeff_1tau2L[i], file_it, recoEffname);
			writeTEfficiency(h_recopurity_1tau2L_bef[i], h_recopurity_1tau2L_aft[i], h_correct_recopurity_1tau2L[i], file_it, recoPurityname);

			sprintf(significancename, "h_significance_1tau3L_%d_", i);
			writeHisto(h_significance_1tau3L[i], file_it, significancename);
			sprintf(recoEffname, "recoEff_1tau3L_%d_", i);
			sprintf(recoPurityname, "recoPurity_1tau3L_%d_", i);
			writeTEfficiency(h_recoeff_1tau3L_bef[i], h_recoeff_1tau3L_aft[i], h_correct_recoeff_1tau3L[i], file_it, recoEffname);
			writeTEfficiency(h_recopurity_1tau3L_bef[i], h_recopurity_1tau3L_aft[i], h_correct_recopurity_1tau3L[i], file_it, recoPurityname);

			sprintf(significancename, "h_significance_2tau0L_%d_", i);
			writeHisto(h_significance_2tau0L[i], file_it, significancename);
			sprintf(recoEffname, "recoEff_2tau0L_%d_", i);
			sprintf(recoPurityname, "recoPurity_2tau0L_%d_", i);
			writeTEfficiency(h_recoeff_2tau0L_bef[i], h_recoeff_2tau0L_aft[i], h_correct_recoeff_2tau0L[i], file_it, recoEffname);
			writeTEfficiency(h_recopurity_2tau0L_bef[i], h_recopurity_2tau0L_aft[i], h_correct_recopurity_2tau0L[i], file_it, recoPurityname);

			sprintf(significancename, "h_significance_2tau1L_%d_", i);
			writeHisto(h_significance_2tau1L[i], file_it, significancename);
			sprintf(recoEffname, "recoEff_2tau1L_%d_", i);
			sprintf(recoPurityname, "recoPurity_2tau1L_%d_", i);
			writeTEfficiency(h_recoeff_2tau1L_bef[i], h_recoeff_2tau1L_aft[i], h_correct_recoeff_2tau1L[i], file_it, recoEffname);
			writeTEfficiency(h_recopurity_2tau1L_bef[i], h_recopurity_2tau1L_aft[i], h_correct_recopurity_2tau1L[i], file_it, recoPurityname);
			
			sprintf(significancename, "h_significance_2tau2L_%d_", i);
			writeHisto(h_significance_2tau2L[i], file_it, significancename);
			sprintf(recoEffname, "recoEff_2tau2L_%d_", i);
			sprintf(recoPurityname, "recoPurity_2tau2L_%d_", i);
			writeTEfficiency(h_recoeff_2tau2L_bef[i], h_recoeff_2tau2L_aft[i], h_correct_recoeff_2tau2L[i], file_it, recoEffname);
			writeTEfficiency(h_recopurity_2tau2L_bef[i], h_recopurity_2tau2L_aft[i], h_correct_recopurity_2tau2L[i], file_it, recoPurityname);

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
			delete h_recoeff_gen2tau0L_aft[i];
			delete h_recoeff_gen2tau1L_bef[i];
			delete h_recoeff_gen2tau1L_aft[i];
			delete h_recoeff_gen2tau2L_bef[i];
			delete h_recoeff_gen2tau2L_aft[i];
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
			delete h_significance_nocat[i];
			delete h_recoeff_nocat_bef[i];
			delete h_recoeff_nocat_aft[i];
			delete h_recopurity_nocat_bef[i];
			delete h_recopurity_nocat_aft[i];
			delete h_correct_recoeff_nocat[i];
			delete h_correct_recopurity_nocat[i];
			delete h_significance_1tau0L[i];
			delete h_recoeff_1tau0L_bef[i];
			delete h_recoeff_1tau0L_aft[i];
			delete h_recopurity_1tau0L_bef[i];
			delete h_recopurity_1tau0L_aft[i];
			delete h_correct_recoeff_1tau0L[i];
			delete h_correct_recopurity_1tau0L[i];
			delete h_significance_1tau1L[i];
			delete h_recoeff_1tau1L_bef[i];
			delete h_recoeff_1tau1L_aft[i];
			delete h_recopurity_1tau1L_bef[i];
			delete h_recopurity_1tau1L_aft[i];
			delete h_correct_recoeff_1tau1L[i];
			delete h_correct_recopurity_1tau1L[i];
			delete h_significance_1tau2L[i];
			delete h_recoeff_1tau2L_bef[i];
			delete h_recoeff_1tau2L_aft[i];
			delete h_recopurity_1tau2L_bef[i];
			delete h_recopurity_1tau2L_aft[i];
			delete h_correct_recoeff_1tau2L[i];
			delete h_correct_recopurity_1tau2L[i];
			delete h_significance_1tau3L[i];
			delete h_recoeff_1tau3L_bef[i];
			delete h_recoeff_1tau3L_aft[i];
			delete h_recopurity_1tau3L_bef[i];
			delete h_recopurity_1tau3L_aft[i];
			delete h_correct_recoeff_1tau3L[i];
			delete h_correct_recopurity_1tau3L[i];
			delete h_significance_2tau0L[i];
			delete h_recoeff_2tau0L_bef[i];
			delete h_recoeff_2tau0L_aft[i];
			delete h_recopurity_2tau0L_bef[i];
			delete h_recopurity_2tau0L_aft[i];
			delete h_correct_recoeff_2tau0L[i];
			delete h_correct_recopurity_2tau0L[i];
			delete h_significance_2tau1L[i];
			delete h_recoeff_2tau1L_bef[i];
			delete h_recoeff_2tau1L_aft[i];
			delete h_recopurity_2tau1L_bef[i];
			delete h_recopurity_2tau1L_aft[i];
			delete h_correct_recoeff_2tau1L[i];
			delete h_correct_recopurity_2tau1L[i];
			delete h_significance_2tau2L[i];
			delete h_recoeff_2tau2L_bef[i];
			delete h_recoeff_2tau2L_aft[i];
			delete h_recopurity_2tau2L_bef[i];
			delete h_recopurity_2tau2L_aft[i];
			delete h_correct_recoeff_2tau2L[i];
			delete h_correct_recopurity_2tau2L[i];

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

void recoEff (vector<TLorentzVector> *genTaus, vector<TLorentzVector> *recoTaus, TH1F* hBef, TH1F* hAft, double genW, TH1F* correction_histo) {

	float dRmin = 10.0;
	for (int gTau = 0; gTau < genTaus->size(); gTau++) {

		hBef->Fill(genTaus->at(gTau).Pt(), genW);

		for (int rTau = 0; rTau < recoTaus->size(); rTau++) {

			float dEta = fabs( genTaus->at(gTau).Eta() - recoTaus->at(rTau).Eta() );
			float dPhi = fabs( genTaus->at(gTau).Phi() - recoTaus->at(rTau).Phi() );
			if(dPhi > 3.14159265358979323846) dPhi  = 2*3.14159265358979323846 - dPhi;
			Float_t dR = sqrt( pow(dEta, 2) + pow(dPhi, 2) );
			if ( dR < dRmin ) {
                            
				dRmin = dR;
		                            
			}

		}
	
		if (dRmin < 0.4) hAft->Fill(genTaus->at(gTau).Pt(), genW);
		if (genW < 0 && !(dRmin < 0.4)) correction_histo->Fill(genTaus->at(gTau).Pt(), fabs(genW)); 
	}

}

void recoPurity (vector<TLorentzVector> *genTaus, vector<TLorentzVector> *recoTaus, TH1F* hBef, TH1F* hAft, double genW, TH1F* correction_histo) {

	float dRmin = 10.0;
	for (int rTau = 0; rTau < recoTaus->size(); rTau++) {

		hBef->Fill(recoTaus->at(rTau).Pt(), genW);

		for (int gTau = 0; gTau < genTaus->size(); gTau++) {

			float dEta = fabs( genTaus->at(gTau).Eta() - recoTaus->at(rTau).Eta() );
			float dPhi = fabs( genTaus->at(gTau).Phi() - recoTaus->at(rTau).Phi() );
			if(dPhi > 3.14159265358979323846) dPhi  = 2*3.14159265358979323846 - dPhi;
			Float_t dR = sqrt( pow(dEta, 2) + pow(dPhi, 2) );
			if ( dR < dRmin ) {
                            
				dRmin = dR;
		                            
			}

		}
	
		if (dRmin < 0.4) hAft->Fill(recoTaus->at(rTau).Pt(), genW);
		if (genW < 0 && !(dRmin < 0.4)) correction_histo->Fill(recoTaus->at(rTau).Pt(), fabs(genW)); 
	}

}

void writeHisto(TH1F* histo, map<string, string>::iterator file_it, TString name) {

   	histo->Write(name+file_it->first);

}

void writeTEfficiency(TH1F* hBef, TH1F* hAft, TH1F* correction_histo, map<string, string>::iterator file_it, TString name) {

	std::string hBefName(hBef->GetName());
	hBefName.append("_");
	hBefName.append(file_it->first);
	std::string hAftName(hAft->GetName());
	hAftName.append("_");
	hAftName.append(file_it->first);
	hBef->Write(hBefName.c_str());
	hAft->Write(hAftName.c_str());
   
	TH1F* hBef_corrected = (TH1F*)hBef->Clone("hBef_corrected");
	hBef_corrected->Add(correction_histo);
	hBef_corrected->Add(correction_histo);

	TEfficiency *TEff = 0;
	if(TEfficiency::CheckConsistency(*hAft, *hBef_corrected)){
		
		TEff = new TEfficiency(*hAft, *hBef_corrected);
		TEff->Write(name+file_it->first);
		delete TEff;

    }

}
