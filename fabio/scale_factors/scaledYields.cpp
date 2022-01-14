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
#include "scaledYields.h"
//tools for b tagging SFs implementation
#include "BTagCalibrationStandalone.h"
#include "BTagCalibrationStandalone.cpp"
#include "evalEventSF.C"
//tools for DeepTau SFs implementation
#include "TauPOG/TauIDSFs/interface/TauIDSFTool.h"

void scaledYields() {

	gBenchmark->Start("running time");
	gROOT->ProcessLine(".L Loader.C+");
	
	//////////////////////////////////////////////////
	///////// SET UP B-TAGGING SCALE FACTORS /////////
	//////////////////////////////////////////////////
    /*
	// set up calibration + reader
    cout << "Loading the .csv file..." << endl;
    
	std::string inputCSVfile = "DeepJet_2016LegacySF_V1_TuneCP5_JESreduced.csv";  
	std::string measType = "iterativefit";
	std::string sysType = "central";
	std::string sysTypejesUp = "up_jes";
	std::string sysTypejesDown = "down_jes";
    std::string sysTypejesEC2_2016Up = "up_jesEC2_2016";
	std::string sysTypejesEC2_2016Down = "down_jesEC2_2016";
    std::string sysTypejesEC2Up = "up_jesEC2";
	std::string sysTypejesEC2Down = "down_jesEC2";
    std::string sysTypejesBBEC1Up = "up_jesBBEC1";
	std::string sysTypejesBBEC1Down = "down_jesBBEC1";
    std::string sysTypejesAbsoluteUp = "up_jesAbsolute";
	std::string sysTypejesAbsoluteDown = "down_jesAbsolute";
    std::string sysTypejesAbsolute_2016Up = "up_jesAbsolute_2016";
	std::string sysTypejesAbsolute_2016Down = "down_jesAbsolute_2016";
    std::string sysTypejesHFUp = "up_jesHF";
	std::string sysTypejesHFDown = "down_jesHF";
    std::string sysTypejesFlavorQCDUp = "up_jesFlavorQCD";
	std::string sysTypejesFlavorQCDDown = "down_jesFlavorQCD";
    std::string sysTypejesBBEC1_2016Up = "up_jesBBEC1_2016";
	std::string sysTypejesBBEC1_2016Down = "down_jesBBEC1_2016";
    std::string sysTypejesRelativeBalUp = "up_jesRelativeBal";
	std::string sysTypejesRelativeBalDown = "down_jesRelativeBal";
    std::string sysTypejesHF_2016Up = "up_jesHF_2016";
	std::string sysTypejesHF_2016Down = "down_jesHF_2016";
    std::string sysTypejesRelativeSample_2016Up = "up_jesRelativeSample_2016";
	std::string sysTypejesRelativeSample_2016Down = "down_jesRelativeSample_2016";
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
    
    BTagCalibrationReader CSVreader(BTagEntry::OP_RESHAPING, sysType, {sysTypejesUp, sysTypejesDown, sysTypejesEC2_2016Up, sysTypejesEC2_2016Down, sysTypejesEC2Up, sysTypejesEC2Down, sysTypejesBBEC1Up, sysTypejesBBEC1Down, sysTypejesAbsoluteUp, sysTypejesAbsoluteDown, sysTypejesAbsolute_2016Up, sysTypejesAbsolute_2016Down, sysTypejesHFUp, sysTypejesHFDown, sysTypejesFlavorQCDUp, sysTypejesFlavorQCDDown, sysTypejesBBEC1_2016Up, sysTypejesBBEC1_2016Down, sysTypejesRelativeBalUp, sysTypejesRelativeBalDown, sysTypejesHF_2016Up, sysTypejesHF_2016Down, sysTypejesRelativeSample_2016Up, sysTypejesRelativeSample_2016Down, sysTypeHFUp, sysTypeHFDown, sysTypeLFUp, sysTypeLFDown, sysTypehfstats1Up, sysTypehfstats1Down, sysTypehfstats2Up, sysTypehfstats2Down, sysTypelfstats1Up, sysTypelfstats1Down, sysTypelfstats2Up, sysTypelfstats2Down, sysTypecfErr1Up, sysTypecfErr1Down, sysTypecfErr2Up, sysTypecfErr2Down});       
    CSVreader.load(calib, BTagEntry::FLAV_B, measType);
    CSVreader.load(calib, BTagEntry::FLAV_C, measType);
    CSVreader.load(calib, BTagEntry::FLAV_UDSG, measType);
    
    cout << "Input CSV weight file = " << inputCSVfile << "; measurementType = " << measType << ";" << endl;
	*/
	//////////////////////////////////////////////////
	//////////////////////////////////////////////////
	//////////////////////////////////////////////////

    //////////////////////////////////////////////////
	////////// SET UP DeepTau SCALE FACTORS //////////
	//////////////////////////////////////////////////
    //comment out the deep tau part for now; we are not ready to implement it yet
    /*

    std::vector<std::string> years = {
        
        "2016Legacy",
        //"2017ReReco",
        //"2018ReReco",

    };

    std::vector<std::string> WPs   = {//

        "Loose",
        "Medium",
        "Tight"

    };

    std::vector<std::string> IDs   = {

        "DeepTau2017v2p1VSjet", //2017 here has nothing to do with the year of data taking
        "DeepTau2017v2p1VSe",
        "DeepTau2017v2p1VSmu",
    };
    */
	//////////////////////////////////////////////////
	////////// SET UP TRIGGER SCALE FACTORS //////////
	//////////////////////////////////////////////////

	TFile * input_TriggerSF = new TFile( "TriggerSF_2D_2jetsinpresel.root", "READ" );
	TH2D * triggerSF = (TH2D*)input_TriggerSF->Get("SF_njetsVsHT");

	//////////////////////////////////////////////////
	//////////////////////////////////////////////////
	//////////////////////////////////////////////////
	
    //////////////////////////////////////////////////
	////////// SET UP ELECTRON SCALE FACTORS /////////
	//////////////////////////////////////////////////

    TFile * input_EGammaSF = new TFile( "electronSFs/2016LegacyReReco_ElectronTight_Fall17V2.root", "READ" );
	TH2F * EGammaSF = (TH2F*)input_EGammaSF->Get("EGamma_SF2D");
    TFile * input_SUSYEleSF = new TFile( "electronSFs/ElectronScaleFactors_Run2016.root", "READ" );
	TH2F * SUSYEleIDplusIPSF = (TH2F*)input_SUSYEleSF->Get("Run2016_MVATightTightIP2D3D");
    TH2F * SUSYEleISOSF = (TH2F*)input_SUSYEleSF->Get("Run2016_MultiIsoT");

    //////////////////////////////////////////////////
	//////////////////////////////////////////////////
	//////////////////////////////////////////////////
	
    //////////////////////////////////////////////////
	//////////// SET UP MUON SCALE FACTORS ///////////
	//////////////////////////////////////////////////

    TFile* input_MuonIDSF = new TFile( "muonSFs/TnP_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root" );
    TH2F * MuonIDSF = (TH2F*)input_MuonIDSF->Get("SF");
    TFile* input_MuonISOSF = new TFile( "muonSFs/TnP_NUM_MultiIsoMedium_DENOM_MediumID_VAR_map_pt_eta.root" );
    TH2F * MuonISOSF = (TH2F*)input_MuonISOSF->Get("SF");
    TFile* input_MuonIP2DSF = new TFile( "muonSFs/TnP_NUM_TightIP2D_DENOM_MediumID_VAR_map_pt_eta.root" );
    TH2F * MuonIP2DSF = (TH2F*)input_MuonIP2DSF->Get("SF");
    TFile* input_MuonIP3DSF = new TFile( "muonSFs/TnP_NUM_TightIP3D_DENOM_MediumID_VAR_map_pt_eta.root" );
    TH2F * MuonIP3DSF = (TH2F*)input_MuonIP3DSF->Get("SF");

    //////////////////////////////////////////////////
	//////////////////////////////////////////////////
	//////////////////////////////////////////////////

	map<string, string>::iterator file_it = file.begin();
    map<string, TH1F*>::iterator PSEF_it = PSEF.begin();

	//TFile *outputfile = new TFile( "scaledYields_output.root", "RECREATE" );
    TFile *outputfile = new TFile( "asd.root", "RECREATE" );

	while (file_it != file.end()) { //////////////////////// LOOP OVER FILES ///////////////////////
   
		cout << "Reading process " << file_it->second << "..." << endl;
		TString input_base_dir = file_it->second + "/";

		TH1::AddDirectory(kFALSE); 
		TH1F * h_1tau0L_noW = new TH1F("h_1tau0L_noW", "h_1tau0L_noW", 20, 0, 20);
		TH1F * h_1tau0L_CR_noW = new TH1F("h_1tau0L_CR_noW", "h_1tau0L_CR_noW", 20, 0, 20); //control region for FR method
		TH1F * h_1tau0L_VR_noW = new TH1F("h_1tau0L_VR_noW", "h_1tau0L_VR_noW", 20, 0, 20); //validation region for FR method
		TH1F * h_1tau1L_noW = new TH1F("h_1tau1L_noW", "h_1tau1L_noW", 20, 0, 20);
		TH1F * h_1tau2L_noW = new TH1F("h_1tau2L_noW", "h_1tau2L_noW", 20, 0, 20);
		TH1F * h_1tau3L_noW = new TH1F("h_1tau3L_noW", "h_1tau3L_noW", 20, 0, 20);
		TH1F * h_2tau0L_noW = new TH1F("h_2tau0L_noW", "h_2tau0L_noW", 20, 0, 20);
		TH1F * h_2tau1L_noW = new TH1F("h_2tau1L_noW", "h_2tau1L_noW", 20, 0, 20);
		TH1F * h_2tau2L_noW = new TH1F("h_2tau2L_noW", "h_2tau2L_noW", 20, 0, 20);

		TH1F * h_1tau0L = new TH1F("h_1tau0L", "h_1tau0L", 20, 0, 20);
		TH1F * h_1tau0L_CR = new TH1F("h_1tau0L_CR", "h_1tau0L_CR", 20, 0, 20); //control region for FR method
		TH1F * h_1tau0L_VR = new TH1F("h_1tau0L_VR", "h_1tau0L_VR", 20, 0, 20); //validation region for FR method
		TH1F * h_1tau1L = new TH1F("h_1tau1L", "h_1tau1L", 20, 0, 20);
		TH1F * h_1tau2L = new TH1F("h_1tau2L", "h_1tau2L", 20, 0, 20);
		TH1F * h_1tau3L = new TH1F("h_1tau3L", "h_1tau3L", 20, 0, 20);
		TH1F * h_2tau0L = new TH1F("h_2tau0L", "h_2tau0L", 20, 0, 20);
		TH1F * h_2tau1L = new TH1F("h_2tau1L", "h_2tau1L", 20, 0, 20);
		TH1F * h_2tau2L = new TH1F("h_2tau2L", "h_2tau2L", 20, 0, 20);
		TH1::AddDirectory(kTRUE);

		string data = "JetHT";
		TChain mychain("tree");
		//if (!(file_it->first.find(data) !=std::string::npos)) mychain.Add(input_base_dir + "v3*.root"); 
		if (!(file_it->first.find(data) !=std::string::npos)) mychain.Add(input_base_dir + "out*.root");
        else mychain.Add(input_base_dir + "TauOfTTTT*.root");
		TChain mychain2("allevents");
		//if (!(file_it->first.find(data) !=std::string::npos)) mychain2.Add(input_base_dir + "v3*.root");
        if (!(file_it->first.find(data) !=std::string::npos)) mychain2.Add(input_base_dir + "out*.root");
		
		cout << "Computing the sum of gen event weights..." << endl;
		TH1::StatOverflows(kTRUE);
		TH1D * genEvtWeights = new TH1D( "genEvtWeights", "genEvtWeights", 10, -10, 10 );
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

		vector<int> *myjets_flavor = {}; 
		mychain.SetBranchAddress("jets_flavour", &myjets_flavor);

		vector<double> *myjets_btags = {}; 
		mychain.SetBranchAddress("jets_btags", &myjets_btags);

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

		vector<TLorentzVector> *myresolvedTops = {}; 
		mychain.SetBranchAddress("tops_toptagger", &myresolvedTops);

		Long64_t nevents = mychain.GetEntries();

		for ( Long64_t ievent = 0; ievent < nevents; ++ievent ) {
			if (ievent > 100) break;
			if ( !(ievent % 100000 ) ) cout << "ievent  =  " << ievent << endl;
			//get i-th entry in tree
			mychain.GetEntry( ievent );
			/////////////////////////////////////////////////////////////////////
			///////////////////// DEFINE CATEGORY CUTS //////////////////////////
			/////////////////////////////////////////////////////////////////////
			
			//compute HT
			float HT = 0.0;
			for (unsigned int i = 0; i < myjetsL->size(); i ++) HT += myjetsL->at(i).Pt();

			bool is1tau0L = (mytausT->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2);
			bool is1tau0L_CR = (mytausT->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==0);
			bool is1tau0L_VR = (mytausT->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==1);
			bool is1tau1L = (mytausT->size()==1 && myleptonsMVAT->size() == 1 && myjetsL->size()>=6 && mybjetsM->size()>=2);
			bool is1tau2L = (mytausT->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2);
			bool is1tau3L = (mytausT->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2);
			bool is2tau0L = (mytausT->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2);
			bool is2tau1L = (mytausT->size()==2 && myleptonsMVAT->size() == 1 &&  myjetsL->size()>=4 && mybjetsM->size()>=2);
			bool is2tau2L = (mytausT->size()==2 && (myelesMVAT->size()+mymuonsT->size())==2 && myjetsL->size()>=2 && mybjetsM->size()>=2);
			
			if (HT > 400) {

				if (!(file_it->first.find(data) !=std::string::npos)) {

					if(is1tau0L) h_1tau0L_noW->Fill(myjetsL->size(), mygenEvtWeight);
					if(is1tau0L_CR) h_1tau0L_CR_noW->Fill(myjetsL->size(), mygenEvtWeight);
					if(is1tau0L_VR) h_1tau0L_VR_noW->Fill(myjetsL->size(), mygenEvtWeight);
					if(is1tau1L) h_1tau1L_noW->Fill(myjetsL->size(), mygenEvtWeight);
					if(is1tau2L) h_1tau2L_noW->Fill(myjetsL->size(), mygenEvtWeight);
					if(is1tau3L) h_1tau3L_noW->Fill(myjetsL->size(), mygenEvtWeight);
					if(is2tau0L) h_2tau0L_noW->Fill(myjetsL->size(), mygenEvtWeight);
					if(is2tau1L) h_2tau1L_noW->Fill(myjetsL->size(), mygenEvtWeight);
					if(is2tau2L) h_2tau2L_noW->Fill(myjetsL->size(), mygenEvtWeight);
                    
                    /*
					double * mybtagWeight;
					mybtagWeight = evalEventSF(myjetsL, myjets_flavor, myjets_btags, CSVreader);
				    */
					double mytriggerWeight = triggerSF->GetBinContent(triggerSF->FindBin(HT, myjetsL->size()));
					if (mytriggerWeight == 0.0) mytriggerWeight = 1.0; //correct if HT, njets out of range
					
					if(is1tau0L) h_1tau0L->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight  /* * mybtagWeight[0]*PSEF_it->second->GetBinContent(PSEF_it->second->FindBin(myjetsL->size())) */);
					if(is1tau0L_CR) h_1tau0L_CR->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight  /* * mybtagWeight[0]*PSEF_it->second->GetBinContent(PSEF_it->second->FindBin(myjetsL->size())) */);
					if(is1tau0L_VR) h_1tau0L_VR->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight  /* * mybtagWeight[0]*PSEF_it->second->GetBinContent(PSEF_it->second->FindBin(myjetsL->size())) */);
					if(is1tau1L) {

                        float myEleSF = 1.0;
                        for (int i = 0; i < myelesMVAT->size(); i++) {

                            //if (ievent % 1000 == 0) cout << "Ele eta: " << myelesMVAT->at(i).Eta() << " Ele pt: " << myelesMVAT->at(i).Pt() << endl;
                            myEleSF *= EGammaSF->GetBinContent(EGammaSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                            myEleSF *= SUSYEleIDplusIPSF->GetBinContent(SUSYEleIDplusIPSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                            myEleSF *= SUSYEleISOSF->GetBinContent(SUSYEleISOSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                        }
                        if (myEleSF == 0) myEleSF = 1.0;
                        float myMuSF = 1.0;
                        for (int i = 0; i < mymuonsT->size(); i++) {
                            //if (ievent % 1000 == 0) cout << "Mu eta: " << mymuonsT->at(i).Eta() << " Mu pt: " << mymuonsT->at(i).Pt() << endl;
                            myMuSF *= MuonIDSF->GetBinContent(MuonIDSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            myMuSF *= MuonISOSF->GetBinContent(MuonISOSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            myMuSF *= MuonIP2DSF->GetBinContent(MuonIP2DSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            myMuSF *= MuonIP3DSF->GetBinContent(MuonIP3DSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            
                        }
                        if (myMuSF == 0) myMuSF = 1.0;
                        
                        //if (ievent % 1000 == 0) cout << "EleSF: " << myEleSF << " MuSF: " << myMuSF << endl;
                        h_1tau1L->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * myEleSF * myMuSF  /* * mybtagWeight[0]*PSEF_it->second->GetBinContent(PSEF_it->second->FindBin(myjetsL->size())) */);
					
                    }
                    if(is1tau2L){

                        float myEleSF = 1.0;
                        for (int i = 0; i < myelesMVAT->size(); i++) {

                            myEleSF *= EGammaSF->GetBinContent(EGammaSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                            myEleSF *= SUSYEleIDplusIPSF->GetBinContent(SUSYEleIDplusIPSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                            myEleSF *= SUSYEleISOSF->GetBinContent(SUSYEleISOSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                        }
                        if (myEleSF == 0) myEleSF = 1.0;
                        float myMuSF = 1.0;
                        for (int i = 0; i < mymuonsT->size(); i++) {

                            myMuSF *= MuonIDSF->GetBinContent(MuonIDSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            myMuSF *= MuonISOSF->GetBinContent(MuonISOSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            myMuSF *= MuonIP2DSF->GetBinContent(MuonIP2DSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            myMuSF *= MuonIP3DSF->GetBinContent(MuonIP3DSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            
                        }
                        if (myMuSF == 0) myMuSF = 1.0;
                        h_1tau2L->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * myEleSF * myMuSF  /* * mybtagWeight[0]*PSEF_it->second->GetBinContent(PSEF_it->second->FindBin(myjetsL->size())) */);
                        
                    } 
					if(is1tau3L) {

                        float myEleSF = 1.0;
                        for (int i = 0; i < myelesMVAT->size(); i++) {

                            myEleSF *= EGammaSF->GetBinContent(EGammaSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                            myEleSF *= SUSYEleIDplusIPSF->GetBinContent(SUSYEleIDplusIPSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                            myEleSF *= SUSYEleISOSF->GetBinContent(SUSYEleISOSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                        }
                        if (myEleSF == 0) myEleSF = 1.0;
                        h_1tau3L->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * myEleSF  /* * mybtagWeight[0]*PSEF_it->second->GetBinContent(PSEF_it->second->FindBin(myjetsL->size())) */);
                    }

					if(is2tau0L) h_2tau0L->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight  /* * mybtagWeight[0]*PSEF_it->second->GetBinContent(PSEF_it->second->FindBin(myjetsL->size())) */);
					if(is2tau1L) {

                        float myEleSF = 1.0;
                        for (int i = 0; i < myelesMVAT->size(); i++) {

                            myEleSF *= EGammaSF->GetBinContent(EGammaSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                            myEleSF *= SUSYEleIDplusIPSF->GetBinContent(SUSYEleIDplusIPSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                            myEleSF *= SUSYEleISOSF->GetBinContent(SUSYEleISOSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                        }
                        if (myEleSF == 0) myEleSF = 1.0;
                        float myMuSF = 1.0;
                        for (int i = 0; i < mymuonsT->size(); i++) {

                            myMuSF *= MuonIDSF->GetBinContent(MuonIDSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            myMuSF *= MuonISOSF->GetBinContent(MuonISOSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            myMuSF *= MuonIP2DSF->GetBinContent(MuonIP2DSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            myMuSF *= MuonIP3DSF->GetBinContent(MuonIP3DSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            
                        }
                        if (myMuSF == 0) myMuSF = 1.0;
                        h_2tau1L->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * myEleSF *myMuSF  /* * mybtagWeight[0]*PSEF_it->second->GetBinContent(PSEF_it->second->FindBin(myjetsL->size())) */);

                    }
					if(is2tau2L) {

                        float myEleSF = 1.0;
                        for (int i = 0; i < myelesMVAT->size(); i++) {

                            myEleSF *= EGammaSF->GetBinContent(EGammaSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                            myEleSF *= SUSYEleIDplusIPSF->GetBinContent(SUSYEleIDplusIPSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                            myEleSF *= SUSYEleISOSF->GetBinContent(SUSYEleISOSF->FindBin(myelesMVAT->at(i).Eta(),myelesMVAT->at(i).Pt()));
                        }
                        if (myEleSF == 0) myEleSF = 1.0;
                        float myMuSF = 1.0;
                        for (int i = 0; i < mymuonsT->size(); i++) {

                            myMuSF *= MuonIDSF->GetBinContent(MuonIDSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            myMuSF *= MuonISOSF->GetBinContent(MuonISOSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            myMuSF *= MuonIP2DSF->GetBinContent(MuonIP2DSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            myMuSF *= MuonIP3DSF->GetBinContent(MuonIP3DSF->FindBin(mymuonsT->at(i).Pt(), fabs(mymuonsT->at(i).Eta())));
                            
                        }
                        if (myMuSF == 0) myMuSF = 1.0;
                        h_2tau2L->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * mytriggerWeight * myEleSF *myMuSF  /* * mybtagWeight[0]*PSEF_it->second->GetBinContent(PSEF_it->second->FindBin(myjetsL->size())) */);

                    }
				
					//delete mybtagWeight;

				}

				else {
				
					if(is1tau0L) h_1tau0L_noW->Fill(myjetsL->size());
					if(is1tau0L_CR) h_1tau0L_CR_noW->Fill(myjetsL->size());
					if(is1tau0L_VR) h_1tau0L_VR_noW->Fill(myjetsL->size());
					if(is1tau1L) h_1tau1L_noW->Fill(myjetsL->size());
					if(is1tau2L) h_1tau2L_noW->Fill(myjetsL->size());
					if(is1tau3L) h_1tau3L_noW->Fill(myjetsL->size());
					if(is2tau0L) h_2tau0L_noW->Fill(myjetsL->size());
					if(is2tau1L) h_2tau1L_noW->Fill(myjetsL->size());
					if(is2tau2L) h_2tau2L_noW->Fill(myjetsL->size());

					if(is1tau0L) h_1tau0L->Fill(myjetsL->size());
					if(is1tau0L_CR) h_1tau0L_CR->Fill(myjetsL->size());
					if(is1tau0L_VR) h_1tau0L_VR->Fill(myjetsL->size());
					if(is1tau1L) h_1tau1L->Fill(myjetsL->size());
					if(is1tau2L) h_1tau2L->Fill(myjetsL->size());
					if(is1tau3L) h_1tau3L->Fill(myjetsL->size());
					if(is2tau0L) h_2tau0L->Fill(myjetsL->size());
					if(is2tau1L) h_2tau1L->Fill(myjetsL->size());
					if(is2tau2L) h_2tau2L->Fill(myjetsL->size());

				}

			}//end HT>400

			

		}//end loop over events

		outputfile->cd();
		
		TH1D * totalWeight = new TH1D("totalWeight", "totalWeight", 1, -0.5, 0.5);
		TH1::AddDirectory(kFALSE);
		if (!(file_it->first.find(data) !=std::string::npos)) {  
			totalWeight->Fill(0.0, gen_sum_of_weights);
			std::string hTotalWeightName(totalWeight->GetName());		
			hTotalWeightName.append("_");
			hTotalWeightName.append(file_it->first);
			totalWeight->Write(hTotalWeightName.c_str());
		}
		TH1::AddDirectory(kTRUE);
		
		writeHisto(h_1tau0L_noW, file_it);
		writeHisto(h_1tau0L, file_it);
		writeHisto(h_1tau0L_CR_noW, file_it);
		writeHisto(h_1tau0L_CR, file_it);
		writeHisto(h_1tau0L_VR_noW, file_it);
		writeHisto(h_1tau0L_VR, file_it);
		writeHisto(h_1tau1L_noW, file_it);
		writeHisto(h_1tau1L, file_it);
		writeHisto(h_1tau2L_noW, file_it);
		writeHisto(h_1tau2L, file_it);
		writeHisto(h_1tau3L_noW, file_it);
		writeHisto(h_1tau3L, file_it);
		writeHisto(h_2tau0L_noW, file_it);
		writeHisto(h_2tau0L, file_it);
		writeHisto(h_2tau1L_noW, file_it);
		writeHisto(h_2tau1L, file_it);
		writeHisto(h_2tau2L_noW, file_it);
		writeHisto(h_2tau2L, file_it);

		delete totalWeight;
		delete genEvtWeights;
		mychain.Reset();
		mychain2.Reset();
		file_it++;
        PSEF_it++;

	}//end loop over files

	outputfile->Close();
	delete outputfile;
	input_TriggerSF->Close();
	delete input_TriggerSF;
    input_EGammaSF->Close();
    delete input_EGammaSF;
    input_SUSYEleSF->Close();
    delete input_SUSYEleSF;
    input_MuonIDSF->Close();
    delete input_MuonIDSF;
    input_MuonISOSF->Close();
    delete input_MuonISOSF;
    input_MuonIP2DSF->Close();
    delete input_MuonIP2DSF;
    input_MuonIP3DSF->Close();
    delete input_MuonIP3DSF;
	
	gBenchmark->Show("running time");

}//end


void writeHisto(TH1F* histo, map<string, string>::iterator file_it) {
	
	
   	histo->Write(TString(histo->GetName())+"_"+(file_it->first).c_str());
	delete histo;

}

