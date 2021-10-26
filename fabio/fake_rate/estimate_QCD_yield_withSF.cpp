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
#include "estimate_QCD_yield.h"
#include "../scale_factors/BTagCalibrationStandalone.h"
#include "../scale_factors/BTagCalibrationStandalone.cpp"
#include "../scale_factors/evalEventSF.C"
#define NBINSX 4

void estimate_QCD_yield_withSF() {

	gBenchmark->Start("running time");
	gROOT->ProcessLine(".L Loader.C+");

	//////////////////////////////////////////////////
	///////// SET UP B-TAGGING SCALE FACTORS /////////
	//////////////////////////////////////////////////

	// set up calibration + reader
    cout << "Loading the .csv file..." << endl;
    
	std::string inputCSVfile = "../scale_factors/DeepJet_2016LegacySF_V1.csv";  
	std::string measType = "iterativefit";
	std::string sysType = "central";
	std::string sysTypeJESUp = "up_jes";
	std::string sysTypeJESDown = "down_jes";
	std::string sysTypeHFUp = "up_hf";
	std::string sysTypeHFDown = "down_hf";
	std::string sysTypeLFUp = "up_lf";
	std::string sysTypeLFDown = "down_lf";
	std::string sysTypehfstats1Up = "up_hfstats1";
	std::string sysTypehfstats1Down = "down_hfstats1";
	std::string sysTypehfstats2Up = "up_hfstats2";
	std::string sysTypehfstats2Down = "down_hfstats2";
	std::string sysTypelfstats1Up = "up_lfstats1";
	std::string sysTypelfstats1Down = "down_lfstats1";
	std::string sysTypelfstats2Up = "up_lfstats2";
	std::string sysTypelfstats2Down = "down_lfstats2";
	std::string sysTypecfErr1Up = "up_cferr1";
	std::string sysTypecfErr1Down = "down_cferr1";
	std::string sysTypecfErr2Up = "up_cferr2";
	std::string sysTypecfErr2Down = "down_cferr2";
    
    BTagCalibration calib("DeepJet", inputCSVfile);
    
    BTagCalibrationReader CSVreader(BTagEntry::OP_RESHAPING, sysType, {sysTypeJESUp, sysTypeJESDown, sysTypeHFUp, sysTypeHFDown, sysTypeLFUp, sysTypeLFDown, sysTypehfstats1Up, sysTypehfstats1Down, sysTypehfstats2Up, sysTypehfstats2Down, sysTypelfstats1Up, sysTypelfstats1Down, sysTypelfstats2Up, sysTypelfstats2Down, sysTypecfErr1Up, sysTypecfErr1Down, sysTypecfErr2Up, sysTypecfErr2Down});       
    CSVreader.load(calib, BTagEntry::FLAV_B, measType);
    CSVreader.load(calib, BTagEntry::FLAV_C, measType);
    CSVreader.load(calib, BTagEntry::FLAV_UDSG, measType);
    
    cout << "Input CSV weight file = " << inputCSVfile << "; measurementType = " << measType << ";" << endl;
	
	//////////////////////////////////////////////////
	//////////////////////////////////////////////////
	//////////////////////////////////////////////////

	//////////////////////////////////////////////////
	////////// SET UP TRIGGER SCALE FACTORS //////////
	//////////////////////////////////////////////////

	TFile * input_TriggerSF = new TFile( "../scale_factors/TriggerSF_2D.root", "READ" );
	TH2D * triggerSF = (TH2D*)input_TriggerSF->Get("SF_njetsVsHT");

	//////////////////////////////////////////////////
	//////////////////////////////////////////////////
	//////////////////////////////////////////////////

	Float_t binsX[NBINSX+1] = {20, 30, 75, 150, 300};

	TFile *outputfile = new TFile( "tauF_Pt_QCD_withSF.root", "RECREATE" );

	//total QCD yield
	TH1F * h_QCD_yield_CR = new TH1F("h_QCD_yield_CR", "h_QCD_yield_CR", 1, 0, 3000);
	h_QCD_yield_CR->Sumw2();
	TH1F * h_QCD_yield_SR = new TH1F("h_QCD_yield_SR", "h_QCD_yield_SR", 1, 0, 3000);
	h_QCD_yield_SR->Sumw2();

	map<string, string>::iterator file_it = file.begin();
	map<string, float>::iterator xsec_it = xsec.begin();

	
	while (file_it != file.end()) { //////////////////////// LOOP OVER FILES ///////////////////////

		cout << "Reading process " << file_it->second << "..." << endl;
		TString input_base_dir = file_it->second + "/";

		//fake rates
		TH1F * h_tauF_pt_eta0to1p5_bef = new TH1F("h_tauF_pt_eta0to1p5_bef", "h_tauF_pt_eta0to1p5_bef; #tau_{h} p_{T} [GeV]", NBINSX, binsX);
		TH1F * h_tauF_pt_eta0to1p5_aft = new TH1F("h_tauF_pt_eta0to1p5_aft", "h_tauF_pt_eta0to1p5_aft; #tau_{h} p_{T} [GeV]", NBINSX, binsX);
		TH1F * h_tauF_pt_eta1p5to2p3_bef = new TH1F("h_tauF_pt_eta1p5to2p3_bef", "h_tauF_pt_eta1p5to2p3_bef; #tau_{h} p_{T} [GeV]", NBINSX, binsX);
		TH1F * h_tauF_pt_eta1p5to2p3_aft = new TH1F("h_tauF_pt_eta1p5to2p3_aft", "h_tauF_pt_eta1p5to2p3_aft; #tau_{h} p_{T} [GeV]", NBINSX, binsX);

		//number of fakeable-non-tight taus
		TH1F * h_nTaus_FnotT_eta0to1p5_AR = new TH1F("h_nTaus_FnotT_eta0to1p5_AR", "h_nTaus_FnotT_eta0to1p5_AR; #tau_{h} p_{T} [GeV]", NBINSX, binsX);
		TH1F * h_nTaus_FnotT_eta1p5to2p3_AR = new TH1F("h_nTaus_FnotT_eta1p5to2p3_AR", "h_nTaus_FnotT_eta1p5to2p3_AR; #tau_{h} p_{T} [GeV]", NBINSX, binsX);
		TH1F * h_nTaus_FnotT_eta0to1p5_CR = new TH1F("h_nTaus_FnotT_eta0to1p5_CR", "h_nTaus_FnotT_eta0to1p5_CR; #tau_{h} p_{T} [GeV]", NBINSX, binsX);
		TH1F * h_nTaus_FnotT_eta1p5to2p3_CR = new TH1F("h_nTaus_FnotT_eta1p5to2p3_CR", "h_nTaus_FnotT_eta1p5to2p3_CR; #tau_{h} p_{T} [GeV]", NBINSX, binsX);

		//deltaR between fakeable and tight taus (for debugging purposes)
		TH1F * deltaR_FT_eta0to1p5 = new TH1F("deltaR_FT_eta0to1p5", "deltaR_FT_eta0to1p5", 50, 0, 5);
		TH1F * deltaR_FT_eta1p5to2p3 = new TH1F("deltaR_FT_eta1p5to2p3", "deltaR_FT_eta1p5to2p3", 50, 0, 5);

		string data = "JetHT";
		TChain mychain("tree");
		if (!(file_it->first.find(data) !=std::string::npos)) mychain.Add(input_base_dir + "v3*.root"); 
		else mychain.Add(input_base_dir + "TauOfTTTT*.root");
		TChain mychain2("allevents");
		if (!(file_it->first.find(data) !=std::string::npos)) mychain2.Add(input_base_dir + "v3*.root");

		cout << "Computing the sum of gen event weights..." << endl;
		TH1::StatOverflows(kTRUE);
		TH1D * genEvtWeights = new TH1D("genEvtWeights", "genEvtWeights", 10, -10, 10 );
		double gen_sum_of_weights = 0.0;
		if (!(file_it->first.find(data) !=std::string::npos)) {
			mychain2.Project(genEvtWeights->GetName(), "genWeight_allEvents");
			cout << "genEvtWeights->GetMean(): " << genEvtWeights->GetMean() << endl;
			cout << "genEvtWeights->GetEntries(): " << genEvtWeights->GetEntries() << endl; 
			gen_sum_of_weights = genEvtWeights->GetMean()*genEvtWeights->GetEntries();
			cout << gen_sum_of_weights << endl;
		}
		TH1::StatOverflows(kFALSE);
		
		double mygenEvtWeight = 1;//set to one, and then if it's MC...
		if (!(file_it->first.find(data) !=std::string::npos)) mychain.SetBranchAddress( "EVENT_genWeight_", &mygenEvtWeight ); //...get the generator weight
		
		double myPUWeight = 1;//set to one, and then if it's MC...
		if (!(file_it->first.find(data) !=std::string::npos)) mychain.SetBranchAddress( "PUWeight_", &myPUWeight ); //...get the PU weight

		double myprefireWeight = 1;//set to one, and then if it's MC...
		if (!(file_it->first.find(data) !=std::string::npos)) mychain.SetBranchAddress( "EVENT_prefireWeight_", &myprefireWeight ); //...get the PU weight

		vector<TLorentzVector> *myjetsL = {}; 
		mychain.SetBranchAddress("jets", &myjetsL);

		vector<TLorentzVector> *mybjetsM = {}; 
		mychain.SetBranchAddress("bjetsM", &mybjetsM);

		vector<int> *myjets_flavor = {}; 
		mychain.SetBranchAddress("jets_flavour", &myjets_flavor);

		vector<double> *myjets_btags = {}; 
		mychain.SetBranchAddress("jets_btags", &myjets_btags);

		vector<TLorentzVector> *myelesMVAT = {}; 
		mychain.SetBranchAddress("eleMVAT", &myelesMVAT);

		vector<TLorentzVector> *mymuonsT = {}; 
		mychain.SetBranchAddress("muonsT", &mymuonsT);

		vector<TLorentzVector> *mytausT = {}; 
		mychain.SetBranchAddress("tausT", &mytausT);

		vector<TLorentzVector> *mytausF = {}; 
		mychain.SetBranchAddress("tausF", &mytausF);

		vector<TLorentzVector> *myleptonsMVAT = {}; 
		mychain.SetBranchAddress("leptonsMVAT", &myleptonsMVAT);

		Long64_t nevents = mychain.GetEntries();

		for ( Long64_t ievent = 0; ievent < nevents; ++ievent ) {
			//if (ievent > 100) break;
			if ( !(ievent % 100000 ) ) cout << "ievent  =  " << ievent << endl;
			//get i-th entry in tree
			mychain.GetEntry( ievent );
			/////////////////////////////////////////////////////////////////////
			///////////////////// DEFINE CATEGORY CUTS //////////////////////////
			/////////////////////////////////////////////////////////////////////
			
			//compute HT
			float HT = 0.0;
			for (unsigned int i = 0; i < myjetsL->size(); i ++) HT += myjetsL->at(i).Pt();

			//application region (estimate number of fakeable but non tight taus here)
			bool is1tau0L_AR = (mytausF->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2); //ask for 1 fakeable tau here, will ask for no tight taus after

			//control region (estimate fake rate here)
			bool is1tau0L_CR = (mytausF->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==0); //ask for 1 fakeable tau here, will ask for 1 tight tau after
	
			//signal region
			bool is1tau0L_SR = (mytausT->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2);

			if (HT > 400) {

				double * mybtagWeight;
				mybtagWeight = evalEventSF(myjetsL, myjets_flavor, myjets_btags, CSVreader);
				
				double mytriggerWeight = triggerSF->GetBinContent(triggerSF->FindBin(HT, myjetsL->size()));
				if (mytriggerWeight == 0.0) mytriggerWeight = 1.0; //correct if HT, njets out of range

				if (is1tau0L_AR) {

					if (mytausT->size() == 0) {// compute number of fakeable-non-tight events in AR

						if ( fabs( mytausF->at(0).Eta() ) < 1.5 ) h_nTaus_FnotT_eta0to1p5_AR->Fill(mytausF->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * mybtagWeight[0]);
						if ( fabs( mytausF->at(0).Eta() ) > 1.5 && fabs( mytausF->at(0).Eta() ) < 2.3 ) h_nTaus_FnotT_eta1p5to2p3_AR->Fill(mytausF->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * mybtagWeight[0]);
					
					}

				}// end if AR

				if (is1tau0L_CR) {

					if (mytausT->size() == 0) {// compute number of fakeable-non-tight events in CR

						if ( fabs( mytausF->at(0).Eta() ) < 1.5 ) h_nTaus_FnotT_eta0to1p5_CR->Fill(mytausF->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * mybtagWeight[0]);
						if ( fabs( mytausF->at(0).Eta() ) > 1.5 && fabs( mytausF->at(0).Eta() ) < 2.3 ) h_nTaus_FnotT_eta1p5to2p3_CR->Fill(mytausF->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * mybtagWeight[0]);
					
					}
					
					if (mytausT->size() == 1) {

						if(!(file_it->first.find(data) !=std::string::npos)) h_QCD_yield_CR->Fill(mytausF->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * mybtagWeight[0] * LUMI2016*xsec_it->second/gen_sum_of_weights);
						else h_QCD_yield_CR->Fill(mytausF->at(0).Pt());

					}

					if ( fabs( mytausF->at(0).Eta() ) < 1.5 ) {// compute fake rates

						h_tauF_pt_eta0to1p5_bef->Fill(mytausF->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * mybtagWeight[0]);
						if (mytausT->size() == 1 && fabs( mytausT->at(0).Eta() ) < 1.5) {

							h_tauF_pt_eta0to1p5_aft->Fill(mytausF->at(0).Pt() , mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * mybtagWeight[0]);
							Float_t dEta = fabs( mytausF->at(0).Eta() - mytausT->at(0).Eta() );
							Float_t dPhi = fabs( mytausF->at(0).Phi() - mytausT->at(0).Phi() );
							if(dPhi > 3.14159265358979323846) dPhi  = 2*3.14159265358979323846 - dPhi;
							Float_t dR = sqrt( pow(dEta, 2) + pow(dPhi, 2) );
							deltaR_FT_eta0to1p5->Fill(dR , mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * mybtagWeight[0]);

						}

					}

					if ( fabs( mytausF->at(0).Eta() ) > 1.5 && fabs( mytausF->at(0).Eta() ) < 2.3 ) {

						h_tauF_pt_eta1p5to2p3_bef->Fill(mytausF->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * mybtagWeight[0]);
						if ( mytausT->size() == 1 && fabs( mytausT->at(0).Eta() ) > 1.5 && fabs( mytausT->at(0).Eta() ) < 2.3 ) {

							h_tauF_pt_eta1p5to2p3_aft->Fill(mytausF->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * mybtagWeight[0]);
							Float_t dEta = fabs( mytausF->at(0).Eta() - mytausT->at(0).Eta() );
							Float_t dPhi = fabs( mytausF->at(0).Phi() - mytausT->at(0).Phi() );
							if(dPhi > 3.14159265358979323846) dPhi  = 2*3.14159265358979323846 - dPhi;
							Float_t dR = sqrt( pow(dEta, 2) + pow(dPhi, 2) );
							deltaR_FT_eta1p5to2p3->Fill(dR, mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * mybtagWeight[0]);

						}

					}
				
				}// end if CR

				if (is1tau0L_SR && !(file_it->first.find(data) !=std::string::npos)) h_QCD_yield_SR->Fill(mytausF->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * mybtagWeight[0] * LUMI2016*xsec_it->second/gen_sum_of_weights);
				
			}// end HT cut			
		
		}//end loop over events

		TH1D * totalWeight = new TH1D("totalWeight", "totalWeight", 1, -0.5, 0.5);
		TH1::AddDirectory(kFALSE);
		if (!(file_it->first.find(data) !=std::string::npos)) {  
			totalWeight->Fill(0.0, gen_sum_of_weights);
		}
		TH1::AddDirectory(kTRUE);
		 
		outputfile->cd();

		writeHisto(h_nTaus_FnotT_eta0to1p5_AR, file_it);
		writeHisto(h_nTaus_FnotT_eta1p5to2p3_AR, file_it);
		writeHisto(h_nTaus_FnotT_eta0to1p5_CR, file_it);
		writeHisto(h_nTaus_FnotT_eta1p5to2p3_CR, file_it);
		writeHisto(deltaR_FT_eta0to1p5, file_it);
		writeHisto(deltaR_FT_eta1p5to2p3, file_it);
		writeTEfficiency(h_tauF_pt_eta0to1p5_bef, h_tauF_pt_eta0to1p5_aft, file_it, "FR_eta0to1p5_");
		writeTEfficiency(h_tauF_pt_eta1p5to2p3_bef, h_tauF_pt_eta1p5to2p3_aft, file_it, "FR_eta1p5to2p3_");

		if (!(file_it->first.find(data) !=std::string::npos)) {
			std::string hTotalWeightName(totalWeight->GetName());
			hTotalWeightName.append("_");
			hTotalWeightName.append(file_it->first);
			totalWeight->Write(hTotalWeightName.c_str());
		}

		delete h_nTaus_FnotT_eta0to1p5_AR;
		delete h_nTaus_FnotT_eta1p5to2p3_AR;
		delete h_nTaus_FnotT_eta0to1p5_CR;
		delete h_nTaus_FnotT_eta1p5to2p3_CR;
		delete h_tauF_pt_eta0to1p5_bef;
		delete h_tauF_pt_eta0to1p5_aft;
		delete h_tauF_pt_eta1p5to2p3_bef;
		delete h_tauF_pt_eta1p5to2p3_aft;
		delete deltaR_FT_eta0to1p5;
		delete deltaR_FT_eta1p5to2p3;
		delete totalWeight;
		delete genEvtWeights;

		mychain.Reset();
		mychain2.Reset();
		xsec_it++;
		file_it++;

	}//end loop over files

	h_QCD_yield_CR->Write();
	delete h_QCD_yield_CR;
	h_QCD_yield_SR->Write();
	delete h_QCD_yield_SR;
	
	outputfile->Close();
	delete outputfile;
	
	gBenchmark->Show("running time");

}//end

void writeHisto(TH1F* histo, map<string, string>::iterator file_it) {
	std::string histoName(histo->GetName());
	histoName.append("_");
	histoName.append(file_it->first);
   	histo->Write(histoName.c_str());

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
  //TH1F *hRatio = (TH1F*)hAft->Clone("");
  //hRatio->Divide(hBef);
  //hRatio->Write(name);
  
  TEfficiency *TEff = 0;
  if(TEfficiency::CheckConsistency(*hAft, *hBef)){
            
    TEff = new TEfficiency(*hAft, *hBef);
    TEff->Write(name+file_it->first);
    delete TEff;
    }
}
