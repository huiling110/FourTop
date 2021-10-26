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

#define NBINSX 4

void estimate_QCD_yield() {

	gBenchmark->Start("running time");
	gROOT->ProcessLine(".L Loader.C+");

	Float_t binsX[NBINSX+1] = {20, 30, 75, 150, 300};

	TFile *outputfile = new TFile( "tauF_Pt_QCD.root", "RECREATE" );

	//total QCD yield
	TH1F * h_QCD_yield_CR = new TH1F("h_QCD_yield_CR", "h_QCD_yield_CR", 1, 0, 3000);
	h_QCD_yield_CR->Sumw2();
	TH1F * h_QCD_yield_AR = new TH1F("h_QCD_yield_AR", "h_QCD_yield_AR", 1, 0, 3000);
	h_QCD_yield_AR->Sumw2();
	TH1F * h_QCD_yield_SR = new TH1F("h_QCD_yield_SR", "h_QCD_yield_SR", 1, 0, 3000);
	h_QCD_yield_SR->Sumw2();
	//set up histograms for transition factor computation
	TH1F * h_QCD_HT_CR = new TH1F("h_QCD_HT_CR", "h_QCD_HT_CR", 11, 400, 1500);
	h_QCD_HT_CR->Sumw2();
	TH1F * h_QCD_HT_looseCR = new TH1F("h_QCD_HT_looseCR", "h_QCD_HT_looseCR", 11, 400, 1500);
	h_QCD_HT_looseCR->Sumw2();
	TH1F * h_QCD_HT_VR = new TH1F("h_QCD_HT_VR", "h_QCD_HT_VR", 11, 400, 1500);
	h_QCD_HT_VR->Sumw2();
	TH1F * h_QCD_HT_SR = new TH1F("h_QCD_HT_SR", "h_QCD_HT_SR", 11, 400, 1500);
	h_QCD_HT_SR->Sumw2();
	

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
		TH1F * h_nTaus_FnotT_eta0to1p5_VR = new TH1F("h_nTaus_FnotT_eta0to1p5_VR", "h_nTaus_FnotT_eta0to1p5_VR; #tau_{h} p_{T} [GeV]", NBINSX, binsX);
		TH1F * h_nTaus_FnotT_eta1p5to2p3_VR = new TH1F("h_nTaus_FnotT_eta1p5to2p3_VR", "h_nTaus_FnotT_eta1p5to2p3_VR; #tau_{h} p_{T} [GeV]", NBINSX, binsX);

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

			//validation region (perform closure test for FR method here)
			bool is1tau0L_VR = (mytausF->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==1); //ask for 1 fakeable tau here, will ask for no tight taus after

			//control region (estimate fake rate here)
			bool is1tau0L_CR = (mytausF->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==0); //ask for 1 fakeable tau here, will ask for 1 tight tau after
	
			//loose control region (attempt to estimate QCD shape with higher stats)
			bool is1tau0L_looseCR = (mytausF->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()==0); //ask for 1 fakeable tau here, will ask for 1 tight tau after

			//signal region
			bool is1tau0L_SR = (mytausT->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2);

			if (HT > 400) {

				if (is1tau0L_AR) {

					if (mytausT->size() == 0) {// compute number of fakeable-non-tight events in AR
						if(!(file_it->first.find(data) !=std::string::npos)) h_QCD_yield_AR->Fill(mytausF->at(0).Pt(), mygenEvtWeight*LUMI2016*xsec_it->second/gen_sum_of_weights);
						else h_QCD_yield_AR->Fill(mytausF->at(0).Pt());

						if ( fabs( mytausF->at(0).Eta() ) < 1.5 ) h_nTaus_FnotT_eta0to1p5_AR->Fill(mytausF->at(0).Pt(), mygenEvtWeight);
						if ( fabs( mytausF->at(0).Eta() ) > 1.5 && fabs( mytausF->at(0).Eta() ) < 2.3 ) h_nTaus_FnotT_eta1p5to2p3_AR->Fill(mytausF->at(0).Pt(), mygenEvtWeight);
					
					}

				}// end if AR

				if (is1tau0L_VR) {

					if (mytausT->size() == 1) {
						
						if(!(file_it->first.find(data) !=std::string::npos)) h_QCD_HT_VR->Fill(HT, mygenEvtWeight*LUMI2016*xsec_it->second/gen_sum_of_weights);
						else h_QCD_HT_VR->Fill(HT);
					}
					if (mytausT->size() == 0) {// compute number of fakeable-non-tight events in VR
						
						if ( fabs( mytausF->at(0).Eta() ) < 1.5 ) h_nTaus_FnotT_eta0to1p5_VR->Fill(mytausF->at(0).Pt(), mygenEvtWeight);
						if ( fabs( mytausF->at(0).Eta() ) > 1.5 && fabs( mytausF->at(0).Eta() ) < 2.3 ) h_nTaus_FnotT_eta1p5to2p3_VR->Fill(mytausF->at(0).Pt(), mygenEvtWeight);
					
					}

				}// end if AR

				if (is1tau0L_CR) {

					if (mytausT->size() == 1) {

						if(!(file_it->first.find(data) !=std::string::npos)) h_QCD_HT_CR->Fill(HT, mygenEvtWeight*LUMI2016*xsec_it->second/gen_sum_of_weights);
						else h_QCD_HT_CR->Fill(HT);

					}
					if (mytausT->size() == 0) {// compute number of fakeable-non-tight events in CR

						if ( fabs( mytausF->at(0).Eta() ) < 1.5 ) h_nTaus_FnotT_eta0to1p5_CR->Fill(mytausF->at(0).Pt(), mygenEvtWeight);
						if ( fabs( mytausF->at(0).Eta() ) > 1.5 && fabs( mytausF->at(0).Eta() ) < 2.3 ) h_nTaus_FnotT_eta1p5to2p3_CR->Fill(mytausF->at(0).Pt(), mygenEvtWeight);
					
					}
					
					if (mytausT->size() == 1) {

						if(!(file_it->first.find(data) !=std::string::npos)) h_QCD_yield_CR->Fill(mytausF->at(0).Pt(), mygenEvtWeight*LUMI2016*xsec_it->second/gen_sum_of_weights);
						else h_QCD_yield_CR->Fill(mytausF->at(0).Pt());

					}

					if ( fabs( mytausF->at(0).Eta() ) < 1.5 ) {// compute fake rates

						h_tauF_pt_eta0to1p5_bef->Fill(mytausF->at(0).Pt(), mygenEvtWeight);
						if (mytausT->size() == 1 && fabs( mytausT->at(0).Eta() ) < 1.5) {

							h_tauF_pt_eta0to1p5_aft->Fill(mytausF->at(0).Pt(), mygenEvtWeight);
							Float_t dEta = fabs( mytausF->at(0).Eta() - mytausT->at(0).Eta() );
							Float_t dPhi = fabs( mytausF->at(0).Phi() - mytausT->at(0).Phi() );
							if(dPhi > 3.14159265358979323846) dPhi  = 2*3.14159265358979323846 - dPhi;
							Float_t dR = sqrt( pow(dEta, 2) + pow(dPhi, 2) );
							deltaR_FT_eta0to1p5->Fill(dR, mygenEvtWeight);

						}

					}

					if ( fabs( mytausF->at(0).Eta() ) > 1.5 && fabs( mytausF->at(0).Eta() ) < 2.3 ) {

						h_tauF_pt_eta1p5to2p3_bef->Fill(mytausF->at(0).Pt() , mygenEvtWeight);
						if ( mytausT->size() == 1 && fabs( mytausT->at(0).Eta() ) > 1.5 && fabs( mytausT->at(0).Eta() ) < 2.3 ) {

							h_tauF_pt_eta1p5to2p3_aft->Fill(mytausF->at(0).Pt(), mygenEvtWeight);
							Float_t dEta = fabs( mytausF->at(0).Eta() - mytausT->at(0).Eta() );
							Float_t dPhi = fabs( mytausF->at(0).Phi() - mytausT->at(0).Phi() );
							if(dPhi > 3.14159265358979323846) dPhi  = 2*3.14159265358979323846 - dPhi;
							Float_t dR = sqrt( pow(dEta, 2) + pow(dPhi, 2) );
							deltaR_FT_eta1p5to2p3->Fill(dR, mygenEvtWeight);

						}

					}
				
				}// end if CR

				if (is1tau0L_looseCR) {

					if (mytausT->size() == 1) {

						if(!(file_it->first.find(data) !=std::string::npos)) h_QCD_HT_looseCR->Fill(HT, mygenEvtWeight*LUMI2016*xsec_it->second/gen_sum_of_weights);
						else h_QCD_HT_looseCR->Fill(HT);

					}

				}

				if (is1tau0L_SR && !(file_it->first.find(data) !=std::string::npos)) {

					h_QCD_yield_SR->Fill(mytausF->at(0).Pt(), mygenEvtWeight*LUMI2016*xsec_it->second/gen_sum_of_weights);
					h_QCD_HT_SR->Fill(HT, mygenEvtWeight*LUMI2016*xsec_it->second/gen_sum_of_weights);
				}

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
		writeHisto(h_nTaus_FnotT_eta0to1p5_VR, file_it);
		writeHisto(h_nTaus_FnotT_eta1p5to2p3_VR, file_it);
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

		delete h_tauF_pt_eta0to1p5_bef;
		delete h_tauF_pt_eta0to1p5_aft;
		delete h_tauF_pt_eta1p5to2p3_bef;
		delete h_tauF_pt_eta1p5to2p3_aft;
		delete totalWeight;
		delete genEvtWeights;

		mychain.Reset();
		mychain2.Reset();
		xsec_it++;
		file_it++;

	}//end loop over files

	h_QCD_yield_CR->Write();
	delete h_QCD_yield_CR;
	h_QCD_yield_AR->Write();
	delete h_QCD_yield_AR;
	h_QCD_yield_SR->Write();
	delete h_QCD_yield_SR;
	h_QCD_HT_CR->Write();
	delete h_QCD_HT_CR;
	h_QCD_HT_looseCR->Write();
	delete h_QCD_HT_looseCR;
	h_QCD_HT_VR->Write();
	delete h_QCD_HT_VR;
	h_QCD_HT_SR->Write();
	delete h_QCD_HT_SR;	
	outputfile->Close();
	delete outputfile;
	
	gBenchmark->Show("running time");

}//end

void writeHisto(TH1F* histo, map<string, string>::iterator file_it) {
	std::string histoName(histo->GetName());
	histoName.append("_");
	histoName.append(file_it->first);
   	histo->Write(histoName.c_str());
	delete histo;
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
