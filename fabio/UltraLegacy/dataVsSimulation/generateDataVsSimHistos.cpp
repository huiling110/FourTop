#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TBenchmark.h>
#include <TEfficiency.h>
#include "generateDataVsSimHistos.h"
#include <TChain.h>
#include <TROOT.h> //for gROOT
#include <TSystem.h> // for gSystem
//tools for b tagging SFs implementation
#include "../tools/BTagCalibrationStandalone.cpp"
#include "../tools/evalEventSF.C"
#include "../tools/evalEventSF_fixedWP.C"
//tools for DeepTau SFs implementation
#include "../../../TauPOG/TauIDSFs/src/TauIDSFTool.cc"
#include "../tools/debug.cpp"
void generateDataVsSimHistos(string year, string analyzer, string dir) {

gBenchmark->Start("running time");
gROOT->ProcessLine(".L Loader.C+");


 cout << "////////////////////////////////////////////////////////" << endl;
 cout << "////////////////////////////////////////////////////////" << endl;
 cout << "  ////////////////////////////////////////////////////////" << endl;
 cout << "///// ///////////////////////////////////////////////////" << endl;
 cout << "/////////  REMEMBER TO UPDATE TRIGGER NAMES AND SET UP TRIGGER SF AND CHECK HT CUT!!! //////////" << endl;
 cout << "///////////// ///////////////////////////////////////////" << endl;
 cout << "///////////////// ///////////////////////////////////////" << endl;
 cout << "///////////////////// ///////////////////////////////////" << endl;
 cout << "////////////////////////////////////////////////////////" << endl;


 //////////////////////////////////////////////////
 /////////// SET UP MUON SCALE FACTORS ////////////
 //////////////////////////////////////////////////
 TFile* input_MuonIDSF = new TFile( TString(MUOSF_files[year]), "READ" );
 TH2F * MuonIDSF = (TH2F*)input_MuonIDSF->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
 MuonIDSF->SetDirectory(nullptr);
 input_MuonIDSF->Close();
 delete input_MuonIDSF;
 //////////////////////////////////////////////////
 ///////// SET UP ELECTRON SCALE FACTORS //////////
 //////////////////////////////////////////////////
 TFile* input_EleIDSF = new TFile( TString(EGammaSF_files[year]), "READ" );
 TH2F * EleIDSF = (TH2F*)input_EleIDSF->Get("EGamma_SF2D");
 EleIDSF->SetDirectory(nullptr);
 input_EleIDSF->Close();
 delete input_EleIDSF;
 //////////////////////////////////////////////////
 ////////// SET UP TRIGGER SCALE FACTORS //////////
 //////////////////////////////////////////////////
 TFile* input_TrigSF = new TFile( TString(TRGSF_files[year]), "READ" );
 TH2F * TriggerSF = (TH2F*)input_TrigSF->Get("SF_njetsVsHT_"+TString(year));
 TH2F * TriggerSFunc = (TH2F*)input_TrigSF->Get("SF_njetsVsHTerrors_"+TString(year));
 TriggerSF->SetDirectory(nullptr);
 TriggerSFunc->SetDirectory(nullptr);
 input_TrigSF->Close();
 delete input_TrigSF;
 //////////////////////////////////////////////////
 /////////// SET UP TAU SCALE FACTORS /////////////
 //////////////////////////////////////////////////
 TauIDSFTool VSjetIDTool = TauIDSFTool(year,"DeepTau2017v2p1VSjet","Medium", false, false, true);
 TauIDSFTool VSeIDTool = TauIDSFTool(year,"DeepTau2017v2p1VSe","VVLoose", false, false, true); //no VVVLoose histogram in file, use VVLoose and add +3% uncertainty (recommended by TAU POG conveners)
 TauIDSFTool VSmuIDTool = TauIDSFTool(fromULtoReReco(year),"DeepTau2017v2p1VSmu","VLoose", false, false, false); //No UL measurement for these SFs? UL file is not present! Also, set otherVSlepWP to false, VLoose histogram is available
 
 //////////////////////////////////////////////////
 ////////// LOAD B TAGGING EFFICIENCIES ///////////
 //////////////////////////////////////////////////
 TFile* input_btagEff = new TFile( TString(btagEff_files[year]), "READ" );
 TEfficiency * btagEff_b_tttt = (TEfficiency*)input_btagEff->Get("btagEff_b_tttt");
 TEfficiency * btagEff_c_tttt = (TEfficiency*)input_btagEff->Get("btagEff_c_tttt");
 TEfficiency * btagEff_udsg_tttt = (TEfficiency*)input_btagEff->Get("btagEff_udsg_tttt");
 TEfficiency * btagEff_b_ttbar = (TEfficiency*)input_btagEff->Get("btagEff_b_ttbar");
 TEfficiency * btagEff_c_ttbar = (TEfficiency*)input_btagEff->Get("btagEff_c_ttbar");
 TEfficiency * btagEff_udsg_ttbar = (TEfficiency*)input_btagEff->Get("btagEff_udsg_ttbar");
 TEfficiency * btagEff_b_QCD = (TEfficiency*)input_btagEff->Get("btagEff_b_QCD");
 TEfficiency * btagEff_c_QCD = (TEfficiency*)input_btagEff->Get("btagEff_c_QCD");
 TEfficiency * btagEff_udsg_QCD = (TEfficiency*)input_btagEff->Get("btagEff_udsg_QCD");
 TEfficiency * btagEff_b_ttX = (TEfficiency*)input_btagEff->Get("btagEff_b_ttX");
 TEfficiency * btagEff_c_ttX = (TEfficiency*)input_btagEff->Get("btagEff_c_ttX");
 TEfficiency * btagEff_udsg_ttX = (TEfficiency*)input_btagEff->Get("btagEff_udsg_ttX");
 TEfficiency * btagEff_b_ST = (TEfficiency*)input_btagEff->Get("btagEff_b_ST");
 TEfficiency * btagEff_c_ST = (TEfficiency*)input_btagEff->Get("btagEff_c_ST");
 TEfficiency * btagEff_udsg_ST = (TEfficiency*)input_btagEff->Get("btagEff_udsg_ST");
 btagEff_b_tttt->SetDirectory(nullptr);
 btagEff_c_tttt->SetDirectory(nullptr);
 btagEff_udsg_tttt->SetDirectory(nullptr);
 btagEff_b_ttbar->SetDirectory(nullptr);
 btagEff_c_ttbar->SetDirectory(nullptr);
 btagEff_udsg_ttbar->SetDirectory(nullptr);
 btagEff_b_QCD->SetDirectory(nullptr);
 btagEff_c_QCD->SetDirectory(nullptr);
 btagEff_udsg_QCD->SetDirectory(nullptr);
 btagEff_b_ttX->SetDirectory(nullptr);
 btagEff_c_ttX->SetDirectory(nullptr);
 btagEff_udsg_ttX->SetDirectory(nullptr);
 btagEff_b_ST->SetDirectory(nullptr);
 btagEff_c_ST->SetDirectory(nullptr);
 btagEff_udsg_ST->SetDirectory(nullptr);
 input_btagEff->Close();
 delete input_btagEff;
 //////////////////////////////////////////////////
 ///////// SET UP B-TAGGING SCALE FACTORS /////////
 //////////////////////////////////////////////////
  
 // set up calibration + reader
 cout << "Loading the .csv file..." << endl;

 std::string inputCSVfile = BTVSF_files_fixedWP[year];
 const std::string tagger = "DeepJet";
 std::string measType = "iterativefit";
 std::string measTypeIncl = "incl";
 std::string measTypeComb = "comb";
 std::string sysType = "central";
 std::string sysTypecorrelatedUp = "up_correlated";
 std::string sysTypecorrelatedDown = "down_correlated";
 std::string sysTypeuncorrelatedUp = "up_uncorrelated";
 std::string sysTypeuncorrelatedDown = "down_uncorrelated";
 
 BTagCalibration calib(tagger, inputCSVfile);
 BTagCalibrationReader CSVreader(BTagEntry::OP_MEDIUM, sysType, {sysTypecorrelatedUp, sysTypecorrelatedDown, sysTypeuncorrelatedUp, sysTypeuncorrelatedDown});
 CSVreader.load(calib, BTagEntry::FLAV_B, measTypeComb);
 CSVreader.load(calib, BTagEntry::FLAV_C, measTypeComb);
 CSVreader.load(calib, BTagEntry::FLAV_UDSG, measTypeIncl);
 
 cout << "Input CSV weight file = " << inputCSVfile << "; measurementType = " << measTypeComb << "/" << measTypeIncl << ";" << endl;


 map<string, string>::iterator file_it = file[year].begin();

 while (file_it != file[year].end()) { //////////////////////// LOOP OVER FILES ///////////////////////
   
     cout << "Reading process " << file_it->second.c_str() << "..." << endl;
     TString filename = "Histos_" + file_it->second + "_" + TString(year) + ".root";
     TFile * outputfile = new TFile( "rootFiles/"+filename, "RECREATE" );
    
     TH1::SetDefaultSumw2(kTRUE);

     TH1::AddDirectory(kFALSE);
		//1tau0L validation region (used to validate FR method)
        TH1F * h_jets_HT_1tau0L_CR = new TH1F("h_jets_HT_1tau0L_CR", "h_jets_HT_1tau0L_CR", 11, 400, 1500);
		TH1F * h_jets_HT_1tau0L_VR = new TH1F("h_jets_HT_1tau0L_VR", "h_jets_HT_1tau0L_VR", 11, 400, 1500);
		TH1F * h_jets_HT_1tau0L_SR = new TH1F("h_jets_HT_1tau0L_SR", "h_jets_HT_1tau0L_SR", 11, 400, 1500);

		//1tau0L category 
		TH1F * h_jets_number_1tau0L = new TH1F("h_jets_number_1tau0L", "h_jets_number_1tau0L", 15, 0, 15);
        TH1F * h_taus_1pt_1tau0L = new TH1F("h_taus_1pt_1tau0L", "h_taus_1pt_1tau0L", 40, 0, 200);
		TH1F * h_bjetsM_number_1tau0L = new TH1F("h_bjetsM_number_1tau0L", "h_bjetsM_number_1tau0L", 10, 0, 10);
		TH1F * h_jets_bScore_1tau0L = new TH1F("h_jets_bScore_1tau0L", "h_jets_bScore_1tau0L", 70, 0.5, 7.5);
		TH1F * h_bjetsM_1score_1tau0L = new TH1F("h_bjetsM_1score_1tau0L", "h_bjetsM_1score_1tau0L", 20, 0.5, 1);
		TH1F * h_bjetsM_2score_1tau0L = new TH1F("h_bjetsM_2score_1tau0L", "h_bjetsM_2score_1tau0L", 20, 0.5, 1);
		TH1F * h_jets_aplanarity_1tau0L = new TH1F("h_jets_aplanarity_1tau0L", "h_jets_aplanarity_1tau0L", 20, 0, 0.4);
		TH1F * h_jets_sphericity_1tau0L = new TH1F("h_jets_sphericity_1tau0L", "h_jets_sphericity_1tau0L", 40, 0, 1);
		TH1F * h_jets_ratioHT_4toRest_1tau0L = new TH1F("h_jets_ratioHT_4toRest_1tau0L", "h_jets_ratioHT_4toRest_1tau0L", 40, 0, 20);
		TH1F * h_jets_transMass_1tau0L = new TH1F("h_jets_transMass_1tau0L", "h_jets_transMass_1tau0L", 150, 0, 3000);
		TH1F * h_bjetsM_minDeltaR_1tau0L = new TH1F("h_bjetsM_minDeltaR_1tau0L", "h_bjetsM_minDeltaR_1tau0L", 25, 0, 5);

		//1tau1L category
		//input BDT variables
		TH1F * h_jets_bScore_1tau1L = new TH1F("h_jets_bScore_1tau1L", "h_jets_bScore_1tau1L", 70, 0.5, 7.5);
		TH1F * h_jets_7pt_1tau1L = new TH1F("h_jets_7pt_1tau1L", "h_jets_7pt_1tau1L", 40, 0, 200);
		TH1F * h_toptagger_HT_1tau1L = new TH1F("h_toptagger_HT_1tau1L", "h_toptagger_HT_1tau1L", 150, 0, 1500);
		TH1F * h_bjetsM_invariantMass_1tau1L = new TH1F("h_bjetsM_invariantMass_1tau1L", "h_bjetsM_invariantMass_1tau1L", 100, 0, 2500);
		TH1F * h_jets_6pt_1tau1L = new TH1F("h_jets_6pt_1tau1L", "h_jets_6pt_1tau1L", 40, 0, 200);
		TH1F * h_jets_transMass_1tau1L = new TH1F("h_jets_transMass_1tau1L", "h_jets_transMass_1tau1L", 150, 0, 3000);
		TH1F * h_jets_ratioHT_4toRest_1tau1L = new TH1F("h_jets_ratioHT_4toRest_1tau1L", "h_jets_ratioHT_4toRest_1tau1L", 40, 0, 20);
		TH1F * h_nonbjetsM_4pt_1tau1L = new TH1F("h_nonbjetsM_4pt_1tau1L", "h_nonbjetsM_4pt_1tau1L", 50, 0, 500);
		TH1F * h_bjetsM_minDeltaR_1tau1L = new TH1F("h_bjetsM_minDeltaR_1tau1L", "h_bjetsM_minDeltaR_1tau1L", 25, 0, 5);
		TH1F * h_toptagger_3pt_1tau1L = new TH1F("h_toptagger_3pt_1tau1L", "h_toptagger_3pt_1tau1L", 50, 0, 500);
		TH1F * h_toptagger_MHT_1tau1L = new TH1F("h_toptagger_MHT_1tau1L", "h_toptagger_MHT_1tau1L", 50, 0, 500);
        TH1F * h_leptonsMVAL_number_1tau1L = new TH1F("h_leptonsMVAL_number_1tau1L", "h_leptonsMVAL_number_1tau1L", 10, 0, 10);
        TH1F * h_taus_1pt_1tau1L = new TH1F("h_taus_1pt_1tau1L", "h_taus_1pt_1tau1L", 40, 0, 200);

		//1tau2L category
		//input BDT variables
		TH1F * h_jets_bScore_1tau2L = new TH1F("h_jets_bScore_1tau2L", "h_jets_bScore_1tau2L", 70, 0.5, 7.5);
		TH1F * h_bjetsM_3pt_1tau2L = new TH1F("h_bjetsM_3pt_1tau2L", "h_bjetsM_3pt_1tau2L", 50, 0, 500);
        TH1F * h_jets_number_1tau2L = new TH1F("h_jets_number_1tau2L", "h_jets_number_1tau2L", 15, 0, 15);
		TH1F * h_jets_ratioHT_4toRest_1tau2L = new TH1F("h_jets_ratioHT_4toRest_1tau2L", "h_jets_ratioHT_4toRest_1tau2L", 40, 0, 20);
		TH1F * h_toptagger_transMass_1tau2L = new TH1F("h_toptagger_transMass_1tau2L", "h_toptagger_transMass_1tau2L", 150, 0, 3000);
        TH1F * h_bjetsM_invariantMass_1tau2L = new TH1F("h_bjetsM_invariantMass_1tau2L", "h_bjetsM_invariantMass_1tau2L", 100, 0, 2500);
        TH1F * h_bjetsM_minDeltaR_1tau2L = new TH1F("h_bjetsM_minDeltaR_1tau2L", "h_bjetsM_minDeltaR_1tau2L", 25, 0, 5);
        TH1F * h_bjetsM_4pt_1tau2L = new TH1F("h_bjetsM_4pt_1tau2L", "h_bjetsM_4pt_1tau2L", 40, 0, 200);
        TH1F * h_jets_HT_1tau2L = new TH1F("h_jets_HT_1tau2L", "h_jets_HT_1tau2L", 11, 400, 1500);
		TH1F * h_jets_4pt_1tau2L = new TH1F("h_jets_4pt_1tau2L", "h_jets_4pt_1tau2L", 40, 0, 200);
        TH1F * h_jets_aplanarity_1tau2L = new TH1F("h_jets_aplanarity_1tau2L", "h_jets_aplanarity_1tau2L", 20, 0, 0.4);
		TH1F * h_toptagger_1pt_1tau2L = new TH1F("h_toptagger_1pt_1tau2L", "h_toptagger_1pt_1tau2L", 50, 0, 500);
		TH1F * h_jets_tausF_minDeltaR_1tau2L = new TH1F("h_jets_tausF_minDeltaR_1tau2L", "h_jets__tausF_minDeltaR_1tau2L", 25, 0, 5);
		TH1F * h_tausF_MHT_1tau2L = new TH1F("h_tausF_MHT_1tau2L", "h_tausF_MHT_1tau2L", 50, 0, 500);
		
		TH1F * h_jets_minDeltaR_1tau2L = new TH1F("h_jets_minDeltaR_1tau2L", "h_jets_minDeltaR_1tau2L", 25, 0, 5);
        TH1F * h_taus_1pt_1tau2L = new TH1F("h_taus_1pt_1tau2L", "h_taus_1pt_1tau2L", 40, 0, 200);

		//1tau3L category
		TH1F * h_jets_HT_1tau3L = new TH1F("h_jets_HT_1tau3L", "h_jets_HT_1tau3L", 11, 400, 1500);
        TH1F * h_taus_1pt_1tau3L = new TH1F("h_taus_1pt_1tau3L", "h_taus_1pt_1tau3L", 40, 0, 200);
		TH1F * h_jets_bScore_1tau3L = new TH1F("h_jets_bScore_1tau3L", "h_jets_bScore_1tau3L", 70, 0.5, 7.5);
		TH1F * h_jets_number_1tau3L = new TH1F("h_jets_number_1tau3L", "h_jets_number_1tau3L", 15, 0, 15);
		TH1F * h_jets_ratioHT_4toRest_1tau3L = new TH1F("h_jets_ratioHT_4toRest_1tau3L", "h_jets_ratioHT_4toRest_1tau3L", 40, 0, 20);
        TH1F * h_jets_1pt_1tau3L = new TH1F("h_jets_1pt_1tau3L", "h_jets_1pt_1tau3L", 40, 0, 400);
        TH1F * h_jets_aplanarity_1tau3L = new TH1F("h_jets_aplanarity_1tau3L", "h_jets_aplanarity_1tau3L", 20, 0, 0.4);
        TH1F * h_jets_minDeltaR_1tau3L = new TH1F("h_jets_minDeltaR_1tau3L", "h_jets_minDeltaR_1tau3L", 25, 0, 5);

		//2tau0L category
		TH1F * h_jets_HT_2tau0L = new TH1F("h_jets_HT_2tau0L", "h_jets_HT_2tau0L", 11, 400, 1500);
        TH1F * h_taus_1pt_2tau0L = new TH1F("h_taus_1pt_2tau0L", "h_taus_1pt_2tau0L", 40, 0, 200);
        TH1F * h_jets_bScore_2tau0L = new TH1F("h_jets_bScore_2tau0L", "h_jets_bScore_2tau0L", 70, 0.5, 7.5);
		TH1F * h_jets_number_2tau0L = new TH1F("h_jets_number_2tau0L", "h_jets_number_2tau0L", 15, 0, 15);
		TH1F * h_jets_ratioHT_4toRest_2tau0L = new TH1F("h_jets_ratioHT_4toRest_2tau0L", "h_jets_ratioHT_4toRest_2tau0L", 40, 0, 20);
        TH1F * h_jets_1pt_2tau0L = new TH1F("h_jets_1pt_2tau0L", "h_jets_1pt_2tau0L", 40, 0, 400);
        TH1F * h_jets_aplanarity_2tau0L = new TH1F("h_jets_aplanarity_2tau0L", "h_jets_aplanarity_2tau0L", 20, 0, 0.4);
        TH1F * h_jets_minDeltaR_2tau0L = new TH1F("h_jets_minDeltaR_2tau0L", "h_jets_minDeltaR_2tau0L", 25, 0, 5);
        
		//2tau1L category
		//input BDT variables
		TH1F * h_jets_HTDividedByMET_2tau1L = new TH1F("h_jets_HTDividedByMET_2tau1L", "h_jets_HTDividedByMET_2tau1L", 50, 0, 100);
		TH1F * h_tausT_MHT_2tau1L = new TH1F("h_tausT_MHT_2tau1L", "h_tausT_MHT_2tau1L", 50, 0, 500);
		TH1F * h_jets_bScore_2tau1L = new TH1F("h_jets_bScore_2tau1L", "h_jets_bScore_2tau1L", 70, 0.5, 7.5);
		TH1F * h_jets_6pt_2tau1L = new TH1F("h_jets_6pt_2tau1L", "h_jets_6pt_2tau1L", 40, 0, 200);
		TH1F * h_bjetsM_minDeltaR_2tau1L = new TH1F("h_bjetsM_minDeltaR_2tau1L", "h_bjetsM_minDeltaR_2tau1L", 25, 0, 5);
		TH1F * h_jets_ratioHT_4toRest_2tau1L = new TH1F("h_jets_ratioHT_4toRest_2tau1L", "h_jets_ratioHT_4toRest_2tau1L", 40, 0, 20);
		TH1F * h_toptagger_invariantMass_2tau1L = new TH1F("h_toptagger_invariantMass_2tau1L", "h_toptagger_invariantMass_2tau1L", 100, 0, 2500);
		TH1F * h_bjetsM_invariantMass_2tau1L = new TH1F("h_bjetsM_invariantMass_2tau1L", "h_bjetsM_invariantMass_2tau1L", 100, 0, 2500);
		TH1F * h_jets_4pt_2tau1L = new TH1F("h_jets_4pt_2tau1L", "h_jets_4pt_2tau1L", 40, 0, 200);
		TH1F * h_toptagger_1pt_2tau1L = new TH1F("h_toptagger_1pt_2tau1L", "h_toptagger_1pt_2tau1L", 50, 0, 500);
		TH1F * h_jets_tausF_minDeltaR_2tau1L = new TH1F("h_jets_tausF_minDeltaR_2tau1L", "h_jets__tausF_minDeltaR_2tau1L", 25, 0, 5);
		TH1F * h_jets_minDeltaR_2tau1L = new TH1F("h_jets_minDeltaR_2tau1L", "h_jets_minDeltaR_2tau1L", 25, 0, 5);
		TH1F * h_jets_average_DeltaR_2tau1L = new TH1F("h_jets_average_DeltaR_2tau1L", "h_jets_average_DeltaR_2tau1L", 25, 0, 5);
		//TH1F * h_tausL_HT_2tau1L = new TH1F("h_tausL_HT_2tau1L", "h_tausL_HT_2tau1L", 150, 0, 1500);
		
        TH1F * h_taus_1pt_2tau1L = new TH1F("h_taus_1pt_2tau1L", "h_taus_1pt_2tau1L", 40, 0, 200);

		//2tau2L category
		TH1F * h_jets_HT_2tau2L = new TH1F("h_jets_HT_2tau2L", "h_jets_HT_2tau2L", 11, 400, 1500);
        TH1F * h_taus_1pt_2tau2L = new TH1F("h_taus_1pt_2tau2L", "h_taus_1pt_2tau2L", 40, 0, 200);
        TH1F * h_jets_bScore_2tau2L = new TH1F("h_jets_bScore_2tau2L", "h_jets_bScore_2tau2L", 70, 0.5, 7.5);
		TH1F * h_jets_number_2tau2L = new TH1F("h_jets_number_2tau2L", "h_jets_number_2tau2L", 15, 0, 15);
		TH1F * h_jets_ratioHT_4toRest_2tau2L = new TH1F("h_jets_ratioHT_4toRest_2tau2L", "h_jets_ratioHT_4toRest_2tau2L", 40, 0, 20);
        TH1F * h_jets_1pt_2tau2L = new TH1F("h_jets_1pt_2tau2L", "h_jets_1pt_2tau2L", 40, 0, 400);
        TH1F * h_jets_aplanarity_2tau2L = new TH1F("h_jets_aplanarity_2tau2L", "h_jets_aplanarity_2tau2L", 20, 0, 0.4);
        TH1F * h_jets_minDeltaR_2tau2L = new TH1F("h_jets_minDeltaR_2tau2L", "h_jets_minDeltaR_2tau2L", 25, 0, 5);

        //2tauXL category
        TH1F * h_jets_bScore_2tauXL = new TH1F("h_jets_bScore_2tauXL", "h_jets_bScore_2tauXL", 70, 0.5, 7.5);
        TH1F * h_jets_4largestBScoreSum_2tauXL = new TH1F("h_jets_4largestBScoreSum_2tauXL", "h_jets_4largestBScoreSum_2tauXL", 70, 0.5, 7.5);
        TH1F * h_leptonsMVAL_transMass_2tauXL = new TH1F("h_leptonsMVAL_transMass_2tauXL", "h_leptonsMVAL_transMass_2tauXL", 100, 0, 500);
        TH1F * h_jets_number_2tauXL = new TH1F("h_jets_number_2tauXL", "h_jets_number_2tauXL", 20, 0, 20);
        TH1F * h_bjetsM_invariantMass_2tauXL = new TH1F("h_bjetsM_invariantMass_2tauXL", "h_bjetsM_invariantMass_2tauXL", 100, 0, 2500);
        //TH1F * h_tausL_leptonsT_invariantMass_2tauXL = new TH1F("h_tausL_leptonsT_invariantMass_2tauXL", "h_tausL_leptonsT_invariantMass_2tauXL", 100, 0, 2500);
        TH1F * h_jets_transMass_2tauXL = new TH1F("h_jets_transMass_2tauXL", "h_jets_transMass_2tauXL", 100, 0, 2500);
        TH1F * h_jets_6pt_2tauXL = new TH1F("h_jets_6pt_2tauXL", "h_jets_6pt_2tauXL", 40, 0, 200);
		TH1F * h_toptagger_transMass_2tauXL = new TH1F("h_toptagger_transMass_2tauXL", "h_toptagger_transMass_2tauXL", 150, 0, 3000);
        TH1F * h_bjetsM_minDeltaR_2tauXL = new TH1F("h_bjetsM_minDeltaR_2tauXL", "h_bjetsM_minDeltaR_2tauXL", 25, 0, 5);
        TH1F * h_nonbjetsM_4pt_2tauXL = new TH1F("h_nonbjetsM_4pt_2tauXL", "h_nonbjetsM_4pt_2tauXL", 50, 0, 500);
        TH1F * h_Met_pt_2tauXL = new TH1F("h_Met_pt_2tauXL", "h_Met_pt_2tauXL", 200, 0, 2000);     
        TH1::AddDirectory(kTRUE);

        string data = "data";
        TString input_dir;
        TString base_dir;
        if (analyzer == "fabio") base_dir = TString("/publicfs/cms/user/fabioiemmi/TauOfTTTT_NanoAOD/");
        else if (analyzer == "huiling") base_dir = TString("/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/");
        else {
            
            std::cout << "*** ERROR: The analyzer name is invalid. Exiting. ***" << endl;
            return;

        }
        if (!(file_it->first.find(data) !=std::string::npos)) input_dir = base_dir + TString(year) + "/" + TString(dir) + "/mc/" + TString(file_it->second) + "/";
        else input_dir = base_dir + TString(year) + "/" + TString(dir) + "/data/" + TString(file_it->second) + "/";
        cout << "Reading process " << input_dir << "..." << endl;
        if (gSystem->AccessPathName(input_dir + "outTree_0.root")) {

            std::cout << "*** ERROR: file you are trying to read does not exist. Exiting. ***" << endl;
            return;
        }

        TChain mychain("tree");
        if (!(file_it->first.find(data) !=std::string::npos)) mychain.Add(input_dir + "outTree*.root"); 
        else mychain.Add(input_dir + "outTree*.root");
        TChain mychain2("allevents");
        if (!(file_it->first.find(data) !=std::string::npos)) mychain2.Add(input_dir + "outTree*.root");
        
		TH1::StatOverflows(kTRUE);
		TH1D * genEvtWeights = new TH1D( "genEvtWeights", "genEvtWeights", 10, -10, 10 );
		double gen_sum_of_weights = 0.0;
		if (!(file_it->first.find(data) !=std::string::npos)) {
            cout << "Computing the sum of gen event weights..." << endl;
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

		vector<TLorentzVector> *mynonbjetsM = {}; 
		mychain.SetBranchAddress("nonbjetsM", &mynonbjetsM);

		vector<TLorentzVector> *myelesMVAT = {}; 
		mychain.SetBranchAddress("eleMVAT", &myelesMVAT);

		vector<TLorentzVector> *mymuonsT = {}; 
		mychain.SetBranchAddress("muonsT", &mymuonsT);

		vector<TLorentzVector> *mytausT = {}; 
		mychain.SetBranchAddress("tausT", &mytausT);

        vector<int> *mytausT_genPartFlav = {};
        mychain.SetBranchAddress("tausT_genPartFlav", &mytausT_genPartFlav);
        
		vector<TLorentzVector> *mytausF = {}; 
		mychain.SetBranchAddress("tausF", &mytausF);
        /*
		vector<TLorentzVector> *mytausL = {}; 
		mychain.SetBranchAddress("tausL", &mytausL);
        */
		vector<TLorentzVector> *myleptonsMVAT = {}; 
		mychain.SetBranchAddress("leptonsMVAT", &myleptonsMVAT);

        vector<TLorentzVector> *myleptonsMVAL = {}; 
		mychain.SetBranchAddress("leptonsMVAL", &myleptonsMVAL);

		vector<TLorentzVector> *myresolvedTops = {}; 
		mychain.SetBranchAddress("tops_toptagger", &myresolvedTops);

		double myMET = 0;
		mychain.SetBranchAddress("Met_pt", &myMET);

        int mygenTtbarId = 0;
        mychain.SetBranchAddress("genTtbarId_", &mygenTtbarId);

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
			HT = HTCalculator(myjetsL);

			bool is1tau0L = (mytausT->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()>=2);
			bool is1tau0L_VR = (mytausT->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==1);
            bool is1tau0L_CR = (mytausT->size()==1 && myleptonsMVAT->size()==0 && myjetsL->size()>=8 && mybjetsM->size()==0);
			//bool is1tau1L = (mytausT->size()==1 && myleptonsMVAT->size() == 1 && myjetsL->size()>=6 && mybjetsM->size()>=2);
            bool is1tau1L = (mytausT->size()==1 && myleptonsMVAT->size() == 1 && myjetsL->size()>=7 && mybjetsM->size()>=2);
			//bool is1tau2L = (mytausT->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=4 && mybjetsM->size()>=2);
			bool is1tau2L = (mytausT->size()==1 && myleptonsMVAT->size()==2 && myjetsL->size()>=6 && mybjetsM->size()>=2);
            bool is1tau3L = (mytausT->size()==1 && myleptonsMVAT->size()==3 && myjetsL->size()>=2 && mybjetsM->size()>=2);
			//bool is2tau0L = (mytausT->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=6 && mybjetsM->size()>=2);
			bool is2tau0L = (mytausT->size()==2 && myleptonsMVAT->size()==0 && myjetsL->size()>=7 && mybjetsM->size()>=2);
            //bool is2tau1L = (mytausT->size()==2 && myleptonsMVAT->size() == 1 &&  myjetsL->size()>=4 && mybjetsM->size()>=2);
            bool is2tau1L = (mytausT->size()==2 && myleptonsMVAT->size() == 1 &&  myjetsL->size()>=6 && mybjetsM->size()>=2);
			bool is2tau2L = (mytausT->size()==2 && (myelesMVAT->size()+mymuonsT->size())==2 && myjetsL->size()>=2 && mybjetsM->size()>=2);
            bool is2tauXL = (is2tau1L || is2tau2L);

            Float_t HTcut = 1000000.0;
			if (TString(year).Contains("2016")) HTcut = 500.0;
            else {

                cout << "*** ERROR. You did not set up an HT cut for this year. Exiting." << endl;
                return;
            
            }
            if ( !(myjetsL->size() >=6 ) ) continue;
            if ( !(myjetsL->at(5).Pt() > 40) ) continue;
            
			if (HT > HTcut) {

                //////////////////////////////////////////////////////////////////
                /////////////////////////////////////////////////////////////////
                ///////////////// GET SCALE FACTORS ////////////////////////////
                ///////////////////////////////////////////////////////////////
                /////////////////////////////////////////////////////////////

                //Get Tau ID scale factors
                float tauIDSF = 1.0;
                if (!(file_it->first.find(data) !=std::string::npos)) { //read SFs only if MC process

                    for (int i = 0; i < mytausT->size(); i ++) {

                        double VSjetSF = VSjetIDTool.getSFvsPT(mytausT->at(i).Pt(), mytausT_genPartFlav->at(i), "");
                        double VSeSF = VSeIDTool.getSFvsEta(fabs(mytausT->at(i).Eta()), mytausT_genPartFlav->at(i), "");
                        double VSmuSF = VSmuIDTool.getSFvsEta(fabs(mytausT->at(i).Eta()), mytausT_genPartFlav->at(i), "");

                        tauIDSF *= VSjetSF;
                        tauIDSF *= VSeSF;
                        tauIDSF *= VSmuSF;

                    }

                    if (tauIDSF == 0) tauIDSF = 1.0;

                }

                //Get Muon ID scale factor
                float muonIDSF = 1.0;
                if (!(file_it->first.find(data) !=std::string::npos)) { //read SFs only if MC process
                
                    for (int i = 0; i < mymuonsT->size(); i++) {
                        Int_t binx = MuonIDSF->GetXaxis()->FindBin(fabs(mymuonsT->at(i).Eta()));
                        Int_t biny = MuonIDSF->GetYaxis()->FindBin(mymuonsT->at(i).Pt());
                        muonIDSF *= MuonIDSF->GetBinContent(binx, biny);
                    }
                    if (muonIDSF == 0) muonIDSF = 1.0;

                }

                //Get Ele ID scale factor
                float eleIDSF = 1.0;
                if (!(file_it->first.find(data) !=std::string::npos)) { //read SFs only if MC process
                
                    for (int i = 0; i < myelesMVAT->size(); i++) { 
                        Int_t binx = EleIDSF->GetXaxis()->FindBin(myelesMVAT->at(i).Eta());
                        Int_t biny = EleIDSF->GetYaxis()->FindBin(myelesMVAT->at(i).Pt());
                        eleIDSF *= EleIDSF->GetBinContent(binx, biny); 
                    }
                    if (eleIDSF == 0) eleIDSF = 1.0;

                }

                //Get trigger scale factor
                float triggerSF = 1.0;
                if (!(file_it->first.find(data) !=std::string::npos)) { //read SFs only if MC process
                    
                    Int_t binx = TriggerSF->GetXaxis()->FindBin(HT);
                    Int_t biny = TriggerSF->GetYaxis()->FindBin(myjetsL->size());
                    if (myjetsL->size() > 11 ) triggerSF = 1.0;
                    else if ( TriggerSFunc->GetBinContent(binx, biny)/TriggerSF->GetBinContent(binx, biny) > 0.50 ) triggerSF = 1.0;
                    else triggerSF = TriggerSF->GetBinContent(binx, biny); 
                    if (triggerSF == 0) triggerSF = 1.0;

                }

                Double_t mybtagWeight;
                if ( file_it->first.find("tttt") !=std::string::npos ) mybtagWeight = evalEventSF_fixedWP(sysType, myjetsL, myjets_flavor, myjets_btags, DeepJetM[year], CSVreader, btagEff_b_tttt, btagEff_c_tttt, btagEff_udsg_tttt);
                if ( file_it->first.find("  ttbar") !=std::string::npos ) mybtagWeight = evalEventSF_fixedWP(sysType, myjetsL, myjets_flavor, myjets_btags, DeepJetM[year], CSVreader, btagEff_b_ttbar, btagEff_c_ttbar, btagEff_udsg_ttbar);
                if ( file_it->first.find("QCD") !=std::string::npos ) mybtagWeight = evalEventSF_fixedWP(sysType, myjetsL, myjets_flavor, myjets_btags, DeepJetM[year], CSVreader, btagEff_b_QCD, btagEff_c_QCD, btagEff_udsg_QCD);
                if ( file_it->first.find("+jets") !=std::string::npos || file_it->first.find("ttH") !=std::string::npos ) mybtagWeight = evalEventSF_fixedWP(sysType, myjetsL, myjets_flavor, myjets_btags, DeepJetM[year], CSVreader, btagEff_b_ttX, btagEff_c_ttX, btagEff_udsg_ttX);
                if ( file_it->first.find("st_") !=std::string::npos ) mybtagWeight = evalEventSF_fixedWP(sysType, myjetsL, myjets_flavor, myjets_btags, DeepJetM[year], CSVreader, btagEff_b_ST, btagEff_c_ST, btagEff_udsg_ST);
                if ( file_it->first.find(data) !=std::string::npos ) mybtagWeight = 1.0; // if reading data, set b tagging SF to 1
            
                //Get ttbb correction   
                Float_t ttbbWeight;
                if ( file_it->first.find("ttbar") !=std::string::npos ) {

                    if (mygenTtbarId%100 > 50) ttbbWeight = 1.2; // if ttbb, scale up by 1.2
                    else ttbbWeight = non_ttbb_SF[year][file_it->first]; //if not, scale down by ttbar-process dependent factor
            
                }
                else ttbbWeight = 1.0;

                if (is1tau0L_VR) h_jets_HT_1tau0L_VR->Fill(HT, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                if (is1tau0L_CR) h_jets_HT_1tau0L_CR->Fill(HT, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);

                if (is1tau0L) {

                    h_jets_HT_1tau0L_SR->Fill(HT, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_taus_1pt_1tau0L->Fill(mytausT->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_jets_number_1tau0L->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_bjetsM_number_1tau0L->Fill(mybjetsM->size(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_jets_bScore_1tau0L->Fill(bTagScoreAllJetsCalculator(myjets_btags), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    int countjet = 0;
                    for (int i = 0; i < myjetsL->size(); i++) {

                        if (myjets_btags->at(i) > DeepJetM[TString(year)]) { //deepJet M WP

                            if (countjet == 0) h_bjetsM_1score_1tau0L->Fill(myjets_btags->at(i), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                            else h_bjetsM_2score_1tau0L->Fill(myjets_btags->at(i), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                            countjet += 1;
                            if (countjet >= 2) break;

                        }//end M b tagged

                    }// end loop over jets

                    double sphericity, aplanarity;
                    SphericityAplanarityCal(myjetsL, sphericity, aplanarity);
                    h_jets_aplanarity_1tau0L->Fill(aplanarity, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_jets_sphericity_1tau0L->Fill(sphericity, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_jets_ratioHT_4toRest_1tau0L->Fill(ratioHT_4toRestCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_jets_transMass_1tau0L->Fill(MTCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_bjetsM_minDeltaR_1tau0L->Fill(MinDeltaRSingleCalculator(mybjetsM), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);

                }

                if(is1tau1L) {

                    h_jets_bScore_1tau1L->Fill(bTagScoreAllJetsCalculator(myjets_btags), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    double jets_7pt;
                    if (myjetsL->size() >= 7) jets_7pt = myjetsL->at(6).Pt();
                    else jets_7pt = -99.0;
                    h_jets_7pt_1tau1L->Fill(jets_7pt, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_toptagger_HT_1tau1L->Fill(HTCalculator(myresolvedTops), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_bjetsM_invariantMass_1tau1L->Fill(InvariantMassCalculator(mybjetsM), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_6pt_1tau1L->Fill(myjetsL->at(5).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_transMass_1tau1L->Fill(MTCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_ratioHT_4toRest_1tau1L->Fill(ratioHT_4toRestCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    double nonbjetsM_4pt;
                    if (mynonbjetsM->size() >= 4) nonbjetsM_4pt = mynonbjetsM->at(3).Pt();
                    else nonbjetsM_4pt = -99.0;
                    h_nonbjetsM_4pt_1tau1L->Fill(nonbjetsM_4pt, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_bjetsM_minDeltaR_1tau1L->Fill(MinDeltaRSingleCalculator(mybjetsM), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    double toptagger_3pt;
                    if (myresolvedTops->size() >=3) toptagger_3pt = myresolvedTops->at(2).Pt();
                    else toptagger_3pt = -99.0;
                    h_toptagger_3pt_1tau1L->Fill(toptagger_3pt, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_toptagger_MHT_1tau1L->Fill(SysPtCalculator(myresolvedTops), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_leptonsMVAL_number_1tau1L->Fill(myleptonsMVAL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_taus_1pt_1tau1L->Fill(mytausT->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                }

                if (is1tau2L) {
                    
                    h_jets_bScore_1tau2L->Fill(bTagScoreAllJetsCalculator(myjets_btags), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    double bjetsM_3pt;
                    if (mybjetsM->size() >= 3) bjetsM_3pt = mybjetsM->at(2).Pt();
                    else bjetsM_3pt = -99.0;
                    h_bjetsM_3pt_1tau2L->Fill(bjetsM_3pt, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_number_1tau2L->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_ratioHT_4toRest_1tau2L->Fill(ratioHT_4toRestCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_toptagger_transMass_1tau2L->Fill(MTCalculator(myresolvedTops), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_bjetsM_invariantMass_1tau2L->Fill(InvariantMassCalculator(mybjetsM), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_bjetsM_minDeltaR_1tau2L->Fill(MinDeltaRSingleCalculator(mybjetsM), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    double bjetsM_4pt;
                    if (mybjetsM->size() >= 4) bjetsM_4pt = mybjetsM->at(3).Pt();
                    else bjetsM_4pt = -99.0;
                    h_bjetsM_4pt_1tau2L->Fill(bjetsM_4pt, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_HT_1tau2L->Fill(HT, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_4pt_1tau2L->Fill(myjetsL->at(3).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    double sphericity, aplanarity;
                    SphericityAplanarityCal(myjetsL, sphericity, aplanarity);
                    h_jets_aplanarity_1tau2L->Fill(aplanarity, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    double toptagger_1pt;
                    if (myresolvedTops->size() >=1) toptagger_1pt = myresolvedTops->at(0).Pt();
                    else toptagger_1pt = -99.0;
                    h_toptagger_1pt_1tau2L->Fill(toptagger_1pt, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_tausF_MHT_1tau2L->Fill(SysPtCalculator(mytausF), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_tausF_minDeltaR_1tau2L->Fill(MinDeltaRCal(myjetsL, mytausF), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_minDeltaR_1tau2L->Fill(MinDeltaRSingleCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_taus_1pt_1tau2L->Fill(mytausT->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);

                }

                if (is1tau3L) {

                    h_jets_HT_1tau3L->Fill(HT, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_taus_1pt_1tau3L->Fill(mytausT->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_bScore_1tau3L->Fill(bTagScoreAllJetsCalculator(myjets_btags), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_number_1tau3L->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_ratioHT_4toRest_1tau3L->Fill(ratioHT_4toRestCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_1pt_1tau3L->Fill(myjetsL->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    double sphericity, aplanarity;
                    SphericityAplanarityCal(myjetsL, sphericity, aplanarity);
                    h_jets_aplanarity_1tau3L->Fill(aplanarity, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_minDeltaR_1tau3L->Fill(MinDeltaRSingleCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                }

                if (is2tau0L) {

                    h_jets_HT_2tau0L->Fill(HT, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_taus_1pt_2tau0L->Fill(mytausT->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_jets_bScore_2tau0L->Fill(bTagScoreAllJetsCalculator(myjets_btags), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_jets_number_2tau0L->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_jets_ratioHT_4toRest_2tau0L->Fill(ratioHT_4toRestCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_jets_1pt_2tau0L->Fill(myjetsL->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    double sphericity, aplanarity;
                    SphericityAplanarityCal(myjetsL, sphericity, aplanarity);
                    h_jets_aplanarity_2tau0L->Fill(aplanarity, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);
                    h_jets_minDeltaR_2tau0L->Fill(MinDeltaRSingleCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * mybtagWeight);

                }

                if (is2tau1L) {

                    h_jets_HTDividedByMET_2tau1L->Fill(HT/myMET, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_tausT_MHT_2tau1L->Fill(SysPtCalculator(mytausT), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_bScore_2tau1L->Fill(bTagScoreAllJetsCalculator(myjets_btags), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    double jets_6pt;
                    if (myjetsL->size() >= 6) jets_6pt = myjetsL->at(5).Pt();
                    else jets_6pt = -99.0;
                    h_jets_6pt_2tau1L->Fill(jets_6pt, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_bjetsM_minDeltaR_2tau1L->Fill(MinDeltaRSingleCalculator(mybjetsM), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_ratioHT_4toRest_2tau1L->Fill(ratioHT_4toRestCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_toptagger_invariantMass_2tau1L->Fill(InvariantMassCalculator(myresolvedTops), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_bjetsM_invariantMass_2tau1L->Fill(InvariantMassCalculator(mybjetsM), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_4pt_2tau1L->Fill(myjetsL->at(3).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    double toptagger_1pt;
                    if (myresolvedTops->size() >=1) toptagger_1pt = myresolvedTops->at(0).Pt();
                    else toptagger_1pt = -99.0;
                    h_toptagger_1pt_2tau1L->Fill(toptagger_1pt, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_tausF_minDeltaR_2tau1L->Fill(MinDeltaRCal(myjetsL, mytausF), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_minDeltaR_2tau1L->Fill(MinDeltaRSingleCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_average_DeltaR_2tau1L->Fill(AverageDeltaRCal(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    //h_tausL_HT_2tau1L->Fill(HTCalculator(mytausL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_taus_1pt_2tau1L->Fill(mytausT->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                }

                if (is2tau2L) {

                    h_jets_HT_2tau2L->Fill(HT, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_taus_1pt_2tau2L->Fill(mytausT->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_bScore_2tau2L->Fill(bTagScoreAllJetsCalculator(myjets_btags), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_number_2tau2L->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_ratioHT_4toRest_2tau2L->Fill(ratioHT_4toRestCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_1pt_2tau2L->Fill(myjetsL->at(0).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    double sphericity, aplanarity;
                    SphericityAplanarityCal(myjetsL, sphericity, aplanarity);
                    h_jets_aplanarity_2tau2L->Fill(aplanarity, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_minDeltaR_2tau2L->Fill(MinDeltaRSingleCalculator(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);

                }

                if (is2tauXL) {

                    h_jets_bScore_2tauXL->Fill(bTagScoreAllJetsCalculator(myjets_btags), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_4largestBScoreSum_2tauXL->Fill(bscoreSumOf4largestCal(myjets_btags), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_leptonsMVAL_transMass_2tauXL->Fill(TransMassCal(myleptonsMVAL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_number_2tauXL->Fill(myjetsL->size(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_bjetsM_invariantMass_2tauXL->Fill(InvariantMassCalculator(mybjetsM), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    //h_tausL_leptonsT_invariantMass_2tauXL->Fill(InvariantMass2SysCal(mytausL, myleptonsMVAT), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_jets_transMass_2tauXL->Fill(TransMassCal(myjetsL), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    double jets_6pt;
                    if (myjetsL->size() >= 6) jets_6pt = myjetsL->at(5).Pt();
                    else jets_6pt = -99.0;
                    h_jets_6pt_2tauXL->Fill(jets_6pt, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_toptagger_transMass_2tauXL->Fill(MTCalculator(myresolvedTops), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_bjetsM_minDeltaR_2tauXL->Fill(MinDeltaRSingleCalculator(mybjetsM), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    double nonbjetsM_4pt;
                    if (mynonbjetsM->size() >= 4) nonbjetsM_4pt = mynonbjetsM->at(3).Pt();
                    else nonbjetsM_4pt = -99.0;
                    h_nonbjetsM_4pt_2tauXL->Fill(nonbjetsM_4pt, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);
                    h_Met_pt_2tauXL->Fill(myMET, mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * triggerSF * eleIDSF * muonIDSF * mybtagWeight);

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

		writeHisto(h_jets_HT_1tau0L_VR, file_it);
        writeHisto(h_jets_HT_1tau0L_CR, file_it);
		if (!(file_it->first.find(data) !=std::string::npos)) writeHisto(h_jets_HT_1tau0L_SR, file_it);
        writeHisto(h_taus_1pt_1tau0L, file_it);
		writeHisto(h_jets_number_1tau0L, file_it);
		writeHisto(h_bjetsM_number_1tau0L, file_it);
		writeHisto(h_jets_bScore_1tau0L, file_it);
		writeHisto(h_bjetsM_1score_1tau0L, file_it);
		writeHisto(h_bjetsM_2score_1tau0L, file_it);
		writeHisto(h_jets_aplanarity_1tau0L, file_it);
		writeHisto(h_jets_sphericity_1tau0L, file_it);
		writeHisto(h_jets_ratioHT_4toRest_1tau0L, file_it);
		writeHisto(h_jets_transMass_1tau0L, file_it);
		writeHisto(h_bjetsM_minDeltaR_1tau0L, file_it);

		writeHisto(h_jets_bScore_1tau1L, file_it);
		writeHisto(h_jets_7pt_1tau1L, file_it);
		writeHisto(h_toptagger_HT_1tau1L, file_it);
		writeHisto(h_bjetsM_invariantMass_1tau1L, file_it);
		writeHisto(h_jets_6pt_1tau1L, file_it);
		writeHisto(h_jets_transMass_1tau1L, file_it);
		writeHisto(h_jets_ratioHT_4toRest_1tau1L, file_it);
		writeHisto(h_nonbjetsM_4pt_1tau1L, file_it);
		writeHisto(h_bjetsM_minDeltaR_1tau1L, file_it);
		writeHisto(h_toptagger_3pt_1tau1L, file_it);
		writeHisto(h_toptagger_MHT_1tau1L, file_it);
        writeHisto(h_leptonsMVAL_number_1tau1L, file_it);
        writeHisto(h_taus_1pt_1tau1L, file_it);

		writeHisto(h_jets_bScore_1tau2L, file_it);
        writeHisto(h_bjetsM_3pt_1tau2L, file_it);
		writeHisto(h_jets_number_1tau2L, file_it);
		writeHisto(h_jets_ratioHT_4toRest_1tau2L, file_it);
		writeHisto(h_toptagger_transMass_1tau2L, file_it);
        writeHisto(h_bjetsM_invariantMass_1tau2L, file_it);
        writeHisto(h_bjetsM_minDeltaR_1tau2L, file_it);
        writeHisto(h_bjetsM_4pt_1tau2L, file_it);
        writeHisto(h_jets_HT_1tau2L, file_it);
		writeHisto(h_jets_4pt_1tau2L, file_it);
        writeHisto(h_jets_aplanarity_1tau2L, file_it);
		writeHisto(h_toptagger_1pt_1tau2L, file_it);
        writeHisto(h_jets_tausF_minDeltaR_1tau2L, file_it);
        writeHisto(h_tausF_MHT_1tau2L, file_it);
		writeHisto(h_jets_minDeltaR_1tau2L, file_it);
        writeHisto(h_taus_1pt_1tau2L, file_it);

		if (!(file_it->first.find(data) !=std::string::npos)) writeHisto(h_jets_HT_1tau3L, file_it);
        writeHisto(h_taus_1pt_1tau3L, file_it);
        writeHisto(h_jets_bScore_1tau3L, file_it);
		writeHisto(h_jets_number_1tau3L, file_it);
		writeHisto(h_jets_ratioHT_4toRest_1tau3L, file_it);
		writeHisto(h_jets_1pt_1tau3L, file_it);
		writeHisto(h_jets_aplanarity_1tau3L, file_it);
		writeHisto(h_jets_minDeltaR_1tau3L, file_it);
		
		if (!(file_it->first.find(data) !=std::string::npos)) writeHisto(h_jets_HT_2tau0L, file_it);
        writeHisto(h_taus_1pt_2tau0L, file_it);
        writeHisto(h_jets_bScore_2tau0L, file_it);
		writeHisto(h_jets_number_2tau0L, file_it);
		writeHisto(h_jets_ratioHT_4toRest_2tau0L, file_it);
		writeHisto(h_jets_1pt_2tau0L, file_it);
		writeHisto(h_jets_aplanarity_2tau0L, file_it);
		writeHisto(h_jets_minDeltaR_2tau0L, file_it);

		writeHisto(h_jets_HTDividedByMET_2tau1L, file_it);
		writeHisto(h_tausT_MHT_2tau1L, file_it);
		writeHisto(h_jets_bScore_2tau1L, file_it);
		writeHisto(h_jets_6pt_2tau1L, file_it);
		writeHisto(h_bjetsM_minDeltaR_2tau1L, file_it);
		writeHisto(h_jets_ratioHT_4toRest_2tau1L, file_it);
		writeHisto(h_toptagger_invariantMass_2tau1L, file_it);
		writeHisto(h_bjetsM_invariantMass_2tau1L, file_it);
		writeHisto(h_jets_4pt_2tau1L, file_it);
		writeHisto(h_toptagger_1pt_2tau1L, file_it);
		writeHisto(h_jets_tausF_minDeltaR_2tau1L, file_it);
		writeHisto(h_jets_minDeltaR_2tau1L, file_it);
		writeHisto(h_jets_average_DeltaR_2tau1L, file_it);
		//writeHisto(h_tausL_HT_2tau1L, file_it);
        writeHisto(h_taus_1pt_2tau1L, file_it);

		if (!(file_it->first.find(data) !=std::string::npos)) writeHisto(h_jets_HT_2tau2L, file_it);
        writeHisto(h_taus_1pt_2tau2L, file_it);
        writeHisto(h_jets_bScore_2tau2L, file_it);
		writeHisto(h_jets_number_2tau2L, file_it);
		writeHisto(h_jets_ratioHT_4toRest_2tau2L, file_it);
		writeHisto(h_jets_1pt_2tau2L, file_it);
		writeHisto(h_jets_aplanarity_2tau2L, file_it);
		writeHisto(h_jets_minDeltaR_2tau2L, file_it);

        writeHisto(h_jets_bScore_2tauXL, file_it);
        writeHisto(h_jets_4largestBScoreSum_2tauXL, file_it);
        writeHisto(h_leptonsMVAL_transMass_2tauXL, file_it);
        writeHisto(h_jets_number_2tauXL, file_it);
        writeHisto(h_bjetsM_invariantMass_2tauXL, file_it);
        //writeHisto(h_tausL_leptonsT_invariantMass_2tauXL, file_it);
        writeHisto(h_jets_transMass_2tauXL, file_it);
        writeHisto(h_jets_6pt_2tauXL, file_it);
        writeHisto(h_toptagger_transMass_2tauXL, file_it);
        writeHisto(h_bjetsM_minDeltaR_2tauXL, file_it);
        writeHisto(h_nonbjetsM_4pt_2tauXL, file_it);
        writeHisto(h_Met_pt_2tauXL, file_it);

		delete totalWeight;
		delete genEvtWeights;

		mychain.Reset();
		mychain2.Reset();

		outputfile->Close();
		delete outputfile;

		file_it++;

	}//end loop over files

	//outputfile->Close();
	//delete outputfile;
	//input_TriggerSF->Close();
	//delete input_TriggerSF;
    
	gBenchmark->Show("running time");

}//end


void writeHisto(TH1F* histo, map<string, string>::iterator file_it) {
	
	
   	histo->Write(TString(histo->GetName())+"_"+(file_it->first).c_str());
	delete histo;
}

float HTCalculator ( vector<TLorentzVector> * jets ) {

	float HT = 0;
	for (int i = 0; i < jets->size(); i++) {

		HT += jets->at(i).Pt();
	
	}
	return HT;

}

double bTagScoreAllJetsCalculator ( vector<double> * btag_scores ) {

	float sum = 0;
	for (int i = 0; i < btag_scores->size(); i++) {

		sum += btag_scores->at(i);
	
	}
	return sum;

}

double InvariantMassCalculator(vector<TLorentzVector> * jets) {

	TLorentzVector jet_sum = { 0, 0, 0, 0 };
	for (int i = 0; i < jets->size(); ++i) {

		jet_sum = jet_sum + jets->at(i);

	}
	return jet_sum.M();
}
double SysPtCalculator(vector<TLorentzVector> * jets) {

	TLorentzVector SumJets;
	SumJets.SetPtEtaPhiE(0, 0, 0, 0);
	double syspt = 0;
	for (UInt_t i = 0; i < jets->size(); ++i) {
		SumJets += jets->at(i);
	}
	return SumJets.Pt();

}

double TransEnergyCalculator(TLorentzVector jet) {

	double pt = jet.Pt();
	double trans_energy = sqrt(jet.M() * jet.M() + pt * pt);
	return trans_energy;
}

double TransEnergySysCalculator(vector<TLorentzVector> * jets) {
	double transE = 0;
	for (UInt_t i = 0; i < jets->size(); ++i) {
		transE += TransEnergyCalculator(jets->at(i));
	}
	return transE;
}

double MTCalculator(vector<TLorentzVector> * jets) {
	double sysPt = SysPtCalculator(jets);
	double sysEt = TransEnergySysCalculator(jets);
	double trans_mass = sqrt(sysPt * sysPt + sysEt * sysEt);
	return trans_mass;
}

double ratioHT_4toRestCalculator(vector<TLorentzVector> * jets) {

	vector<TLorentzVector> leading4;
    vector<TLorentzVector> rest;
    for (UInt_t i = 0; i < jets->size(); ++i) {
        if ( i < 4 ) leading4.push_back(jets->at(i));
        if ( i >= 4) rest.push_back(jets->at(i));
    }
    if (jets->size() > 4){
        return HTCalculator(&leading4)/HTCalculator(&rest);
    }
    else return -99;
}

double MinDeltaRSingleCalculator(vector<TLorentzVector> * jets) {
	double min = 10;
	double min_2 = 10;
	double min_3 = 10;
	double min_1 = 10;
	for (UInt_t j = 0; j < jets->size(); ++j) {
		for (UInt_t k = j + 1; k < jets->size(); ++k) {
			min_1 = jets->at(j).DeltaR(jets->at(k));
			if (min_1 < min)
				min = min_1;
		}
		min_2 = min;
		if (min_2 < min_3)
			min_3 = min_2;
	}
	return min_3;
}

double energyCal( vector<TLorentzVector> * jets ) {
    double sumE = 0;
    for (UInt_t j = 0; j < jets->size(); ++j) {
        sumE += jets->at(j).E();
    }
    return sumE;
}

double pzCal( vector<TLorentzVector> * jets ) {
    double sumPz = 0;
    for (UInt_t j = 0; j < jets->size(); ++j) {
        sumPz += jets->at(j).Pz();
    }
    return sumPz;
}

void SphericityAplanarityCal( vector<TLorentzVector> * jets, double& Spher, double& Apla ) {
    
    //AK8 jets
    TVector3 Bst; 
    TLorentzVector momAK8J;
    UInt_t mynJets = jets->size();
    float  momAK8JB[mynJets][4];//matrix?
   
    double sume = energyCal( jets );
    double sumpz = pzCal( jets );
    if(sume !=0.){ //sume = sum of jet energy
        Bst.SetZ(-sumpz/sume);
        for(UInt_t idx=0; idx < mynJets; idx++){
            // momAK8J.SetPx(ak8Jet[idx].Px());
            // momAK8J.SetPy(ak8Jet[idx].Py());
            // momAK8J.SetPz(ak8Jet[idx].Pz());
            // momAK8J.SetE(ak8Jet[idx].E());
            momAK8J = jets->at(idx);;
            // now do the boost
            momAK8J.Boost(Bst); 

            momAK8JB[idx][0] = momAK8J.Px(); 
            momAK8JB[idx][1] = momAK8J.Py(); 
            momAK8JB[idx][2] = momAK8J.Pz(); 
            momAK8JB[idx][3] = momAK8J.E(); 
        }
    }
    
    //AK4 jets
    // TLorentzVector momAK4J;
    // float  momAK4JB[myak4jet_nJets][4];
	//
    // if(sume !=0.){
	// for(int idx=0; idx < myak4jet_nJets; idx++){
	// momAK4J.SetPx(ak4Jet[idx].Px());
	// momAK4J.SetPy(ak4Jet[idx].Py());
	// momAK4J.SetPz(ak4Jet[idx].Pz());
	// momAK4J.SetE(ak4Jet[idx].E());
	// momAK4J.Boost(Bst);
	//
	// momAK4JB[idx][0] = momAK4J.Px();
	// momAK4JB[idx][1] = momAK4J.Py();
	// momAK4JB[idx][2] = momAK4J.Pz();
	// momAK4JB[idx][3] = momAK4J.E();
	// }
    // }
    
    // prepare the momentum tensor

    TMatrixDSym momten2(3); //Instantation of TMatrixTSym<double>     
    momten2(0,0)=0; 
    momten2(1,1)=0;  
    momten2(2,2)=0;  
    momten2(0,1)=0; 
    momten2(0,2)=0; 
    momten2(1,2)=0;  

    Float_t sump2=0.;
    
    //AK8 jets
    for(UInt_t idx = 0; idx < mynJets; idx++){
        momten2(0,0) += momAK8JB[idx][0] * momAK8JB[idx][0];
        momten2(1,1) += momAK8JB[idx][1] * momAK8JB[idx][1];
        momten2(2,2) += momAK8JB[idx][2] * momAK8JB[idx][2];
        momten2(0,1) += momAK8JB[idx][0] * momAK8JB[idx][1];
        momten2(0,2) += momAK8JB[idx][0] * momAK8JB[idx][2];
        momten2(1,2) += momAK8JB[idx][1] * momAK8JB[idx][2];
        
        sump2 +=   momAK8JB[idx][3] * momAK8JB[idx][3];
    }
    
    //AK4 jets
    //???why does it feel like double counting AK8 and AK4 JETS
    // for(int idx = 0; idx < myak4jet_nJets; idx++){
	// momten2(0,0) += momAK4JB[idx][0] * momAK4JB[idx][0];
	// momten2(1,1) += momAK4JB[idx][1] * momAK4JB[idx][1];
	// momten2(2,2) += momAK4JB[idx][2] * momAK4JB[idx][2];
	// momten2(0,1) += momAK4JB[idx][0] * momAK4JB[idx][1];
	// momten2(0,2) += momAK4JB[idx][0] * momAK4JB[idx][2];
	// momten2(1,2) += momAK4JB[idx][1] * momAK4JB[idx][2];
	//
	// sump2 +=   momAK4JB[idx][3] * momAK4JB[idx][3];
    // }
    
    if( sump2 != 0) {
        momten2(0,0) = momten2(0,0)/sump2;
        momten2(1,1) = momten2(1,1)/sump2;
        momten2(2,2) = momten2(2,2)/sump2;
        momten2(0,1) = momten2(0,1)/sump2;
        momten2(0,2) = momten2(0,2)/sump2;
        momten2(1,2) = momten2(1,2)/sump2;
        momten2(1,0) = momten2(0,1);
        momten2(2,0) = momten2(0,2);
        momten2(2,1) = momten2(1,2);
    }
    else {
        momten2(0,0) = 0;
        momten2(1,1) = 0;
        momten2(2,2) = 0;
        momten2(0,1) = momten2(1,0) = 0;
        momten2(0,2) = momten2(2,0) = 0;
        momten2(1,2) = momten2(2,1) = 0;
    }
    
    // find the eigenvalues

    TVectorD eigval(3);
    
    TMatrixDSymEigen eigen(momten2);
    eigval  = eigen.GetEigenValues();
    
    Spher = 3./2.*(eigval(2)+eigval(1));
    Apla = 3./2.*eigval(2);
}

double MinDeltaRCal(vector<TLorentzVector> * jets, vector<TLorentzVector> * leptons) {
	double deltaR_init = 10;
	double min_deltar = 10;
	double min_deltaR = 10;
	for (UInt_t j = 0; j < jets->size(); ++j) {
		for (UInt_t k = 0; k < leptons->size(); ++k) {
			deltaR_init = jets->at(j).DeltaR(leptons->at(k));
			if (min_deltar > deltaR_init)
				min_deltar = deltaR_init;
		}
		if (min_deltar < min_deltaR)
			min_deltaR = min_deltar;
	}
	return min_deltaR;
}

double DeltaR(double eta1, double eta2, double phi1, double phi2) {
	double deltaPhi = TMath::Abs(phi1 - phi2);
	double deltaEta = eta1 - eta2;
	if (deltaPhi > TMath::Pi())
		deltaPhi = TMath::TwoPi() - deltaPhi;
	return TMath::Sqrt(deltaEta * deltaEta + deltaPhi * deltaPhi);
}

double AverageDeltaRCal(vector<TLorentzVector> * jets) {
	double eta_1;
	double phi_1;
	double eta_2;
	double phi_2;
	double sum_delta_R = 0.0;
	const Int_t num = jets->size();
	for (UInt_t j = 0; j < jets->size(); ++j) {
		eta_1 = jets->at(j).Eta();
		phi_1 = jets->at(j).Phi();
		for (UInt_t k = 0; k < jets->size(); ++k) {
			if (k != j) {
				eta_2 = jets->at(k).Eta();
				phi_2 = jets->at(k).Phi();
				sum_delta_R = sum_delta_R + DeltaR(eta_1, eta_2, phi_1, phi_2);
			}
		}
	}
	sum_delta_R = sum_delta_R / ((num - 1) * num);
	return sum_delta_R;
}

double bscoreSumOf4largestCal( vector<double> * btag_scores ) {
    sort(btag_scores->begin(),btag_scores->end());
    reverse(btag_scores->begin(),btag_scores->end());
    double sum = -99;
    if(btag_scores->size()>3) {
        sum = btag_scores->at(0)+btag_scores->at(1)+btag_scores->at(2)+btag_scores->at(3);
    }
    else{
        sum =  -99;
    }
    return sum;
}

double TransMassCal(vector<TLorentzVector> * jets) {
  double MHT = SysPtCalculator(jets);
  double transE = 0;
  for (int j = 0; j < jets->size(); ++j) {
      transE += TransEnergyCalculator(jets->at(j));
  }
  double trans_mass = sqrt(MHT * MHT + transE * transE);
  return trans_mass;
}

Double_t InvariantMass2SysCal(vector<TLorentzVector> * a, vector<TLorentzVector> * b) {
  vector<TLorentzVector> vector_sum(a->begin(), a->end());
  vector_sum.insert(vector_sum.end(), b->begin(), b->end());
  vector<TLorentzVector> * Vector_sum = &vector_sum;
  Double_t invariantMass = InvariantMassCalculator(Vector_sum);
  return invariantMass;
}
