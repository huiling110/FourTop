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
#include "savePSEFs.h"
//tools for b tagging SFs implementation
#include "../BTagCalibrationStandalone.h"
#include "../BTagCalibrationStandalone.cpp"
#include "../evalEventSF.C"
#define nbins 4

void savePSEFs() {
    
    Float_t bins[nbins+1] = {2,3,6,8,30};
    TH1::SetDefaultSumw2(kTRUE);
    TH1F* sumW_tttt_bef = new TH1F("sumW_tttt_bef", "sumW_tttt_bef", nbins, bins); // before b tag weights
    TH1F* sumW_tttt_aft = new TH1F("sumW_tttt_aft", "sumW_tttt_aft", nbins, bins); // after b tag weights
    TH1F* sumW_ttbar_bef = new TH1F("sumW_ttbar_bef", "sumW_ttbar_bef", nbins, bins); // before b tag weights
    TH1F* sumW_ttbar_aft = new TH1F("sumW_ttbar_aft", "sumW_ttbar_aft", nbins, bins); // after b tag weights
    TH1F* sumW_QCD_bef = new TH1F("sumW_QCD_bef", "sumW_QCD_bef", nbins, bins); // before b tag weights
    TH1F* sumW_QCD_aft = new TH1F("sumW_QCD_aft", "sumW_QCD_aft", nbins, bins); // after b tag weights
    TH1F* sumW_ttX_bef = new TH1F("sumW_ttX_bef", "sumW_ttX_bef", nbins, bins); // before b tag weights
    TH1F* sumW_ttX_aft = new TH1F("sumW_ttX_aft", "sumW_ttX_aft", nbins, bins); // after b tag weights
    TH1F* sumW_ST_bef = new TH1F("sumW_ST_bef", "sumW_ST_bef", nbins, bins); // before b tag weights
    TH1F* sumW_ST_aft = new TH1F("sumW_ST_aft", "sumW_ST_aft", nbins, bins); // after b tag weights
    TH1F* sumW_SH_bef = new TH1F("sumW_SH_bef", "sumW_SH_bef", nbins, bins); // before b tag weights
    TH1F* sumW_SH_aft = new TH1F("sumW_SH_aft", "sumW_SH_aft", nbins, bins); // after b tag weights


	gBenchmark->Start("running time");
	gROOT->ProcessLine(".L Loader.C+");
	
	//////////////////////////////////////////////////
	///////// SET UP B-TAGGING SCALE FACTORS /////////
	//////////////////////////////////////////////////
    
	// set up calibration + reader
    cout << "Loading the .csv file..." << endl;
    
	std::string inputCSVfile = "../DeepJet_2016LegacySF_V1_TuneCP5_JESreduced.csv";  
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
	
	map<string, string>::iterator file_it = file.begin();
    map<string, float>::iterator xsec_it = xsec.begin();

	TFile *outputfile = new TFile( "PSEFs.root", "RECREATE" );

	while (file_it != file.end()) { //////////////////////// LOOP OVER FILES ///////////////////////
   
		cout << "Reading process " << file_it->second << "..." << endl;
		TString input_base_dir = file_it->second + "/";

		TChain mychain("tree");
		mychain.Add(input_base_dir + "v3*.root"); 
		TChain mychain2("allevents");
		mychain2.Add(input_base_dir + "v3*.root");
		
		cout << "Computing the sum of gen event weights..." << endl;
		TH1::StatOverflows(kTRUE);
		TH1D * genEvtWeights = new TH1D( "genEvtWeights", "genEvtWeights", 10, -10, 10 );
		double gen_sum_of_weights = 0.0;
        mychain2.Project(genEvtWeights->GetName(), "genWeight_allEvents");
        cout << "genEvtWeights->GetMean (): " << genEvtWeights->GetMean() << endl;
        cout << "genEvtWeights->GetEntries(): " << genEvtWeights->GetEntries() << endl; 
        gen_sum_of_weights = genEvtWeights->GetMean()*genEvtWeights->GetEntries();
        cout << gen_sum_of_weights << endl;
		TH1::StatOverflows(kFALSE);

		double mygenEvtWeight = 1;//set to one, and then if it's MC...
		mychain.SetBranchAddress( "EVENT_genWeight_", &mygenEvtWeight ); //...get the generator weight
		
		double myPUWeight = 1;//set to one, and then if it's MC...
		mychain.SetBranchAddress( "PUWeight_", &myPUWeight ); //...get the PU weight

		double myprefireWeight = 1;//set to one, and then if it's MC...
		mychain.SetBranchAddress( "EVENT_prefireWeight_", &myprefireWeight ); //...get the PU weight

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
			//if (ievent > 100) break;
			if ( !(ievent % 100000 ) ) cout << "ievent  =  " << ievent << endl;
			//get i-th entry in tree
			mychain.GetEntry( ievent );
			
			//compute HT
			float HT = 0.0;
			for (unsigned int i = 0; i < myjetsL->size(); i ++) HT += myjetsL->at(i).Pt();

			if (HT > 400) {

                double * mybtagWeight;
                mybtagWeight = evalEventSF(myjetsL, myjets_flavor, myjets_btags, CSVreader);

                if ( file_it->first.find("tttt") !=std::string::npos ) {

                    sumW_tttt_bef->Fill(myjetsL->size(), LUMI2016*xsec_it->second/gen_sum_of_weights);
                    sumW_tttt_aft->Fill(myjetsL->size(), LUMI2016*xsec_it->second/gen_sum_of_weights * mybtagWeight[0]);
                }

                if ( file_it->first.find("ttbar") !=std::string::npos ) {

                    sumW_ttbar_bef->Fill(myjetsL->size(), LUMI2016*xsec_it->second/gen_sum_of_weights);
                    sumW_ttbar_aft->Fill(myjetsL->size(), LUMI2016*xsec_it->second/gen_sum_of_weights * mybtagWeight[0]);
                }

                if ( file_it->first.find("QCD") !=std::string::npos ) {

                    sumW_QCD_bef->Fill(myjetsL->size(), LUMI2016*xsec_it->second/gen_sum_of_weights);
                    sumW_QCD_aft->Fill(myjetsL->size(), LUMI2016*xsec_it->second/gen_sum_of_weights * mybtagWeight[0]);
                }

                if ( file_it->first.find("+jets") !=std::string::npos || file_it->first.find("ttH") !=std::string::npos ) {

                    sumW_ttX_bef->Fill(myjetsL->size(), LUMI2016*xsec_it->second/gen_sum_of_weights);
                    sumW_ttX_aft->Fill(myjetsL->size(), LUMI2016*xsec_it->second/gen_sum_of_weights * mybtagWeight[0]);
                }

                if ( file_it->first.find("ST_") !=std::string::npos || file_it->first.find("tZq") !=std::string::npos ) {

                    sumW_ST_bef->Fill(myjetsL->size(), LUMI2016*xsec_it->second/gen_sum_of_weights);
                    sumW_ST_aft->Fill(myjetsL->size(), LUMI2016*xsec_it->second/gen_sum_of_weights * mybtagWeight[0]);
                }

                if ( file_it->first.find("ggH") !=std::string::npos || file_it->first.find("VBF") !=std::string::npos ) {

                    sumW_SH_bef->Fill(myjetsL->size(), LUMI2016*xsec_it->second/gen_sum_of_weights);
                    sumW_SH_aft->Fill(myjetsL->size(), LUMI2016*xsec_it->second/gen_sum_of_weights * mybtagWeight[0]);
                }

                delete mybtagWeight;

			}//end HT>400

		}//end loop over events

		delete genEvtWeights;
		mychain.Reset();
		mychain2.Reset();
		file_it++;
        xsec_it++;
	}//end loop over files

    outputfile->cd();
    TH1F* PSEF_tttt;
    PSEF_tttt = (TH1F*)sumW_tttt_bef->Clone("PSEF_tttt");
    PSEF_tttt->Divide(sumW_tttt_aft);
    sumW_tttt_bef->Write();
	sumW_tttt_aft->Write();
    PSEF_tttt->Write();
    TH1F* PSEF_ttbar;
    PSEF_ttbar = (TH1F*)sumW_ttbar_bef->Clone("PSEF_ttbar");
    PSEF_ttbar->Divide(sumW_ttbar_aft);
    sumW_ttbar_bef->Write();
	sumW_ttbar_aft->Write();
    PSEF_ttbar->Write();
    TH1F* PSEF_QCD;
    PSEF_QCD = (TH1F*)sumW_QCD_bef->Clone("PSEF_QCD");
    PSEF_QCD->Divide(sumW_QCD_aft);
    sumW_QCD_bef->Write();
	sumW_QCD_aft->Write();
    PSEF_QCD->Write();
    TH1F* PSEF_ttX;
    PSEF_ttX = (TH1F*)sumW_ttX_bef->Clone("PSEF_ttX");
    PSEF_ttX->Divide(sumW_ttX_aft);
    sumW_ttX_bef->Write();
	sumW_ttX_aft->Write();
    PSEF_ttX->Write();
    TH1F* PSEF_ST;
    PSEF_ST = (TH1F*)sumW_ST_bef->Clone("PSEF_ST");
    PSEF_ST->Divide(sumW_ST_aft);
    sumW_ST_bef->Write();
	sumW_ST_aft->Write();
    PSEF_ST->Write();
    TH1F* PSEF_SH;
    PSEF_SH = (TH1F*)sumW_SH_bef->Clone("PSEF_SH");
    PSEF_SH->Divide(sumW_SH_aft);
    sumW_SH_bef->Write();
	sumW_SH_aft->Write();
    PSEF_SH->Write();
    outputfile->Close();
	delete outputfile;	
	gBenchmark->Show("running time");

}//end

