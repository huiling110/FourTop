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
#include "QCD_CR.h"

void QCD_CR() {

	gBenchmark->Start("running time");
	gROOT->ProcessLine(".L Loader.C+");

	map<string, string>::iterator file_it = file.begin();

	TFile *outputfile = new TFile( "QCD_CR_output.root", "RECREATE" );

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
		//1tau0L category
		//histos for yield
		TH1F* h_yield_1tau0L[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_yield_1tau0L_%d", i);
			sprintf(title, "h_yield_1tau0L_%d", i);
			h_yield_1tau0L[i] = new TH1F(name, title, 50, 0, 200);		
		}
		TH1F* h_yield_1tau0L_ctl[8];
		for (int i = 0; i < 8; i++) {
			char name[200];
			char title[200];
			sprintf(name, "h_yield_1tau0L_ctl_%d", i);
			sprintf(title, "h_yield_1tau0L_ctl_%d", i);
			h_yield_1tau0L_ctl[i] = new TH1F(name, title, 50, 0, 200);		
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
			
			//reco-level categories
			//signal categories
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
			
			//control categories
			bool is1tau0L_ctl[8] = {
				(mytausT_VVTightVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==0),
				(mytausT_VTightVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==0),
				(mytausT_TightVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==0),
				(mytausT_MediumVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==0),
				(mytausT_LooseVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==0),
				(mytausT_VLooseVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==0),
				(mytausT_VVLooseVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==0),
				(mytausT_VVVLooseVsJet->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==0)
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
			

			 //compute HT
			float HT = 0.0;
			int countjetpt = 0;
			for (unsigned int i = 0; i < myjetsL->size(); i ++)  {
   
				HT += myjetsL->at(i).Pt();

			}

			if ( ( myHLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || myHLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1|| myHLT_PFJet450 == 1 ) && HT > 400 ) {

				for (int i = 0; i < 8; i++){

					if (is1tau0L[i]) {
				
						h_yield_1tau0L[i]->Fill(mytausT[i]->at(0).Pt(), mygenEvtWeight);
				   
					}

					if (is1tau0L_ctl[i]) {
				
						h_yield_1tau0L_ctl[i]->Fill(mytausT[i]->at(0).Pt(), mygenEvtWeight);
				   
					}
				
				}//end loop over different VsJet WPs

			}//end trigger requirements			
		
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

			char yieldname[200];
			sprintf(yieldname, "h_yield_1tau0L_%d_", i);
			writeHisto(h_yield_1tau0L[i], file_it, yieldname);
			
			sprintf(yieldname, "h_yield_1tau0L_ctl_%d_", i);
			writeHisto(h_yield_1tau0L_ctl[i], file_it, yieldname);
			
		}
	   

		for (int i = 0; i < 8; i++) {

			delete h_yield_1tau0L[i];
			delete h_yield_1tau0L_ctl[i];
			
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

void writeHisto(TH1F* histo, map<string, string>::iterator file_it, TString name) {

   	histo->Write(name+file_it->first);

}
