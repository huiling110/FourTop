#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TBenchmark.h>
#include <TEfficiency.h>
#include "btagEff.h"
#include <TChain.h>
#include <TLorentzVector.h>
#include <TROOT.h> //for gROOT
#include <TSystem.h> // for gSystem
//tools for b tagging SFs implementation
#include "../../tools/BTagCalibrationStandalone.cpp"
#include "../../tools/evalEventSF.C"
//tools for DeepTau SFs implementation
#include "../../../../TauPOG/TauIDSFs/src/TauIDSFTool.cc"
//debugging tools
#include "../../tools/debug.cpp"
#define NBINSX 3
#define NBINSY 8
//using namespace std;

void btagEff(string year, string dir) {

 gBenchmark->Start("running time");
 gROOT->ProcessLine(".L Loader.C+");

 cout << "////////////////////////////////////////////////////////" << endl;
 cout << "////////////////////////////////////////////////////////" << endl;
 cout << "////////////////////////////////////////////////////////" << endl;
 cout << "////////////////////////////////////////////////////////" << endl;
 cout << "///////// REMEMBER TO UPDATE TRIGGER NAMES!!! //////////" << endl;
 cout << "////////////////////////////////////////////////////////" << endl;
 cout << "////////////////////////////////////////////////////////" << endl;
 cout << "////////////////////////////////////////////////////////" << endl;
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
 /////////// SET UP TAU SCALE FACTORS /////////////
 //////////////////////////////////////////////////
 TauIDSFTool VSjetIDTool = TauIDSFTool(year,"DeepTau2017v2p1VSjet","Medium", false, false, true);
 TauIDSFTool VSeIDTool = TauIDSFTool(year,"DeepTau2017v2p1VSe","VVLoose", false, false, true); //no VVVLoose histogram in file, use VVLoose and add +3% uncertainty (recommended by TAU POG conveners)
 TauIDSFTool VSmuIDTool = TauIDSFTool(fromULtoReReco(year),"DeepTau2017v2p1VSmu","VLoose", false, false, false); //No UL measurement for these SFs? UL file is not present! Also, set otherVSlepWP to false, VLoose histogram is available
	
 Float_t binsX[NBINSX+1] = {0.0,0.8,1.6,2.4};
 Float_t binsY[NBINSY+1] = {20.,30.,50.,70.,100.,140.,300.,600.,1000};

 TFile *outputfile = new TFile( "btagEff_output_" + TString(year) + ".root", "RECREATE" ); 
 
    TH2::AddDirectory(kFALSE); 
    TH2F * h_btagEff_den_b_tttt = new TH2F ("h_btagEff_den_b_tttt", "h_btagEff_den_b_tttt; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_b_tttt = new TH2F ("h_btagEff_num_b_tttt", "h_btagEff_num_b_tttt; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_den_c_tttt = new TH2F ("h_btagEff_den_c_tttt", "h_btagEff_den_c_tttt; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_c_tttt = new TH2F ("h_btagEff_num_c_tttt", "h_btagEff_num_c_tttt; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_den_udsg_tttt = new TH2F ("h_btagEff_den_udsg_tttt", "h_btagEff_den_udsg_tttt; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_udsg_tttt = new TH2F ("h_btagEff_num_udsg_tttt", "h_btagEff_num_udsg_tttt; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    
    TH2F * h_btagEff_den_b_ttbar = new TH2F ("h_btagEff_den_b_ttbar", "h_btagEff_den_b_ttbar; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_b_ttbar = new TH2F ("h_btagEff_num_b_ttbar", "h_btagEff_num_b_ttbar; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_den_c_ttbar = new TH2F ("h_btagEff_den_c_ttbar", "h_btagEff_den_c_ttbar; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_c_ttbar = new TH2F ("h_btagEff_num_c_ttbar", "h_btagEff_num_c_ttbar; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_den_udsg_ttbar = new TH2F ("h_btagEff_den_udsg_ttbar", "h_btagEff_den_udsg_ttbar; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_udsg_ttbar = new TH2F ("h_btagEff_num_udsg_ttbar", "h_btagEff_num_udsg_ttbar; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );

    TH2F * h_btagEff_den_b_QCD = new TH2F ("h_btagEff_den_b_QCD", "h_btagEff_den_b_QCD; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_b_QCD = new TH2F ("h_btagEff_num_b_QCD", "h_btagEff_num_b_QCD; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_den_c_QCD = new TH2F ("h_btagEff_den_c_QCD", "h_btagEff_den_c_QCD; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_c_QCD = new TH2F ("h_btagEff_num_c_QCD", "h_btagEff_num_c_QCD; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_den_udsg_QCD = new TH2F ("h_btagEff_den_udsg_QCD", "h_btagEff_den_udsg_QCD; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_udsg_QCD = new TH2F ("h_btagEff_num_udsg_QCD", "h_btagEff_num_udsg_QCD; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    
    TH2F * h_btagEff_den_b_ttX = new TH2F ("h_btagEff_den_b_ttX", "h_btagEff_den_b_ttX; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_b_ttX = new TH2F ("h_btagEff_num_b_ttX", "h_btagEff_num_b_ttX; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_den_c_ttX = new TH2F ("h_btagEff_den_c_ttX", "h_btagEff_den_c_ttX; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_c_ttX = new TH2F ("h_btagEff_num_c_ttX", "h_btagEff_num_c_ttX; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_den_udsg_ttX = new TH2F ("h_btagEff_den_udsg_ttX", "h_btagEff_den_udsg_ttX; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_udsg_ttX = new TH2F ("h_btagEff_num_udsg_ttX", "h_btagEff_num_udsg_ttX; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    
    TH2F * h_btagEff_den_b_ST = new TH2F ("h_btagEff_den_b_ST", "h_btagEff_den_b_ST; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_b_ST = new TH2F ("h_btagEff_num_b_ST", "h_btagEff_num_b_ST; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_den_c_ST = new TH2F ("h_btagEff_den_c_ST", "h_btagEff_den_c_ST; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_c_ST = new TH2F ("h_btagEff_num_c_ST", "h_btagEff_num_c_ST; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_den_udsg_ST = new TH2F ("h_btagEff_den_udsg_ST", "h_btagEff_den_udsg_ST; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_udsg_ST = new TH2F ("h_btagEff_num_udsg_ST", "h_btagEff_num_udsg_ST; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2::AddDirectory(kTRUE); 

 map<string, string>::iterator file_it = file[year].begin();

while (file_it != file[year].end()) { //////////////////////// LOOP OVER FILES ///////////////////////

    string data = "data";
    TString input_dir;
    if (!(file_it->first.find(data) !=std::string::npos)) input_dir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/" + TString(year) + "/" + TString(dir) + "/mc/" + TString(file_it->second) + "/";
    else input_dir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/" + TString(year) + "/" + TString(dir) + "/data/" + TString(file_it->second) + "/";
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

    double mygenEvtWeight = 1;
    double myPUWeight = 1;
    double myprefireWeight = 1;;

    //if running on data, do not set the gen event weight address
    if (!(file_it->first.find(data) !=std::string::npos)) {

        mychain.SetBranchAddress( "EVENT_genWeight_", &mygenEvtWeight );
        mychain.SetBranchAddress( "PUWeight_", &myPUWeight );
        mychain.SetBranchAddress( "EVENT_prefireWeight_", &myprefireWeight );

    }
    
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

    vector<int> *mytausT_genPartFlav = {};
    mychain.SetBranchAddress("tausT_genPartFlav", &mytausT_genPartFlav);
    
    vector<TLorentzVector> *myleptonsMVAT = {}; 
    mychain.SetBranchAddress("leptonsMVAT", &myleptonsMVAT);

    Long64_t nevents = mychain.GetEntries();

    for ( Long64_t ievent = 0; ievent < nevents; ++ievent ) {
        //if (ievent > 100) break;
        if ( !(ievent % 100000 ) ) cout << "ievent  =  " << ievent << endl;
        //get i-th entry in tree
        mychain.GetEntry( ievent );
        if (!(mygenEvtWeight > 0)) continue; //ignore negative-weighted events when dealing with TEfficiencies
        
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

            //loop over jets
            for (unsigned int i = 0; i < myjetsL->size(); i++) {
                if (fabs(myjets_flavor->at(i))==5) { // b jets
                    
                    if ( file_it->first.find("tttt") !=std::string::npos ) h_btagEff_den_b_tttt->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    if ( file_it->first.find("ttbar") !=std::string::npos ) h_btagEff_den_b_ttbar->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    if ( file_it->first.find("QCD") !=std::string::npos ) h_btagEff_den_b_QCD->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    if ( file_it->first.find("+jets") !=std::string::npos || file_it->first.find("ttH") !=std::string::npos ) h_btagEff_den_b_ttX->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    if ( file_it->first.find("st_") !=std::string::npos ) h_btagEff_den_b_ST->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);

                    if (myjets_btags->at(i) > DeepJetM[year]) {
                        if ( file_it->first.find("tttt") !=std::string::npos ) h_btagEff_num_b_tttt->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                        if ( file_it->first.find("ttbar") !=std::string::npos ) h_btagEff_num_b_ttbar->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                        if ( file_it->first.find("QCD") !=std::string::npos ) h_btagEff_num_b_QCD->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                        if ( file_it->first.find("+jets") !=std::string::npos || file_it->first.find("ttH") !=std::string::npos ) h_btagEff_num_b_ttX->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                        if ( file_it->first.find("st_") !=std::string::npos ) h_btagEff_num_b_ST->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);

                    }
                }// end b flavor

                else if (fabs(myjets_flavor->at(i))==4) { // c jets

                    if ( file_it->first.find("tttt") !=std::string::npos ) h_btagEff_den_c_tttt->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    if ( file_it->first.find("ttbar") !=std::string::npos ) h_btagEff_den_c_ttbar->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    if ( file_it->first.find("QCD") !=std::string::npos ) h_btagEff_den_c_QCD->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    if ( file_it->first.find("+jets") !=std::string::npos || file_it->first.find("ttH") !=std::string::npos ) h_btagEff_den_c_ttX->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    if ( file_it->first.find("st_") !=std::string::npos ) h_btagEff_den_c_ST->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);

                    if (myjets_btags->at(i) > DeepJetM[year]) {

                        if ( file_it->first.find("tttt") !=std::string::npos ) h_btagEff_num_c_tttt->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                        if ( file_it->first.find("ttbar") !=std::string::npos ) h_btagEff_num_c_ttbar->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                        if ( file_it->first.find("QCD") !=std::string::npos ) h_btagEff_num_c_QCD->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                        if ( file_it->first.find("+jets") !=std::string::npos || file_it->first.find("ttH") !=std::string::npos ) h_btagEff_num_c_ttX->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                        if ( file_it->first.find("st_") !=std::string::npos ) h_btagEff_num_c_ST->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);

                    }
                }//end c flavor

                else { // light jets
                    
                    if ( file_it->first.find("tttt") !=std::string::npos ) h_btagEff_den_udsg_tttt->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    if ( file_it->first.find("ttbar") !=std::string::npos ) h_btagEff_den_udsg_ttbar->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    if ( file_it->first.find("QCD") !=std::string::npos ) h_btagEff_den_udsg_QCD->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    if ( file_it->first.find("+jets") !=std::string::npos || file_it->first.find("ttH") !=std::string::npos ) h_btagEff_den_udsg_ttX->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    if ( file_it->first.find("st_") !=std::string::npos ) h_btagEff_den_udsg_ST->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    if (myjets_btags->at(i) > DeepJetM[year]) {
                        if ( file_it->first.find("tttt") !=std::string::npos ) h_btagEff_num_udsg_tttt->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                        if ( file_it->first.find("ttbar") !=std::string::npos ) h_btagEff_num_udsg_ttbar->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                        if ( file_it->first.find("QCD") !=std::string::npos ) h_btagEff_num_udsg_QCD->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                        if ( file_it->first.find("+jets") !=std::string::npos || file_it->first.find("ttH") !=std::string::npos ) h_btagEff_num_udsg_ttX->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                        if ( file_it->first.find("st_") !=std::string::npos ) h_btagEff_num_udsg_ST->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF);
                    }

                }//end light flavor
            
            }// end loop over jets

  
    }//end loop over events

    delete myjetsL;
    delete myjets_flavor;
    delete myjets_btags;
    delete mybjetsM;
    delete myelesMVAT;
    delete mymuonsT;
    delete mytausT;
    delete mytausT_genPartFlav;
    delete myleptonsMVAT;
    
    mychain.Reset();
    mychain2.Reset();

    file_it++;

    }//end loop over files

 outputfile->cd();

 writeTEfficiency2D(h_btagEff_den_b_tttt, h_btagEff_num_b_tttt, "btagEff_b_tttt");
 writeTEfficiency2D(h_btagEff_den_c_tttt, h_btagEff_num_c_tttt, "btagEff_c_tttt");
 writeTEfficiency2D(h_btagEff_den_udsg_tttt, h_btagEff_num_udsg_tttt, "btagEff_udsg_tttt");
    
 writeTEfficiency2D(h_btagEff_den_b_ttbar, h_btagEff_num_b_ttbar, "btagEff_b_ttbar");
 writeTEfficiency2D(h_btagEff_den_c_ttbar, h_btagEff_num_c_ttbar, "btagEff_c_ttbar");
 writeTEfficiency2D(h_btagEff_den_udsg_ttbar, h_btagEff_num_udsg_ttbar, "btagEff_udsg_ttbar");

 writeTEfficiency2D(h_btagEff_den_b_QCD, h_btagEff_num_b_QCD, "btagEff_b_QCD");
 writeTEfficiency2D(h_btagEff_den_c_QCD, h_btagEff_num_c_QCD, "btagEff_c_QCD");
 writeTEfficiency2D(h_btagEff_den_udsg_QCD, h_btagEff_num_udsg_QCD, "btagEff_udsg_QCD");
    
 writeTEfficiency2D(h_btagEff_den_b_ttX, h_btagEff_num_b_ttX, "btagEff_b_ttX");
 writeTEfficiency2D(h_btagEff_den_c_ttX, h_btagEff_num_c_ttX, "btagEff_c_ttX");
 writeTEfficiency2D(h_btagEff_den_udsg_ttX, h_btagEff_num_udsg_ttX, "btagEff_udsg_ttX");
    
 writeTEfficiency2D(h_btagEff_den_b_ST, h_btagEff_num_b_ST, "btagEff_b_ST");
 writeTEfficiency2D(h_btagEff_den_c_ST, h_btagEff_num_c_ST, "btagEff_c_ST");
 writeTEfficiency2D(h_btagEff_den_udsg_ST, h_btagEff_num_udsg_ST, "btagEff_udsg_ST");
    
 
 delete h_btagEff_den_b_tttt;
 delete h_btagEff_num_b_tttt;
 delete h_btagEff_den_c_tttt;
 delete h_btagEff_num_c_tttt;
 delete h_btagEff_den_udsg_tttt;
 delete h_btagEff_num_udsg_tttt;

 delete h_btagEff_den_b_ttbar;
 delete h_btagEff_num_b_ttbar;
 delete h_btagEff_den_c_ttbar;
 delete h_btagEff_num_c_ttbar;
 delete h_btagEff_den_udsg_ttbar;
 delete h_btagEff_num_udsg_ttbar;

 delete h_btagEff_den_b_QCD;
 delete h_btagEff_num_b_QCD;
 delete h_btagEff_den_c_QCD;
 delete h_btagEff_num_c_QCD;
 delete h_btagEff_den_udsg_QCD;
 delete h_btagEff_num_udsg_QCD;

 delete h_btagEff_den_b_ttX;
 delete h_btagEff_num_b_ttX;
 delete h_btagEff_den_c_ttX;
 delete h_btagEff_num_c_ttX;
 delete h_btagEff_den_udsg_ttX;
 delete h_btagEff_num_udsg_ttX;

 delete h_btagEff_den_b_ST;
 delete h_btagEff_num_b_ST;
 delete h_btagEff_den_c_ST;
 delete h_btagEff_num_c_ST;
 delete h_btagEff_den_udsg_ST;
 delete h_btagEff_num_udsg_ST;

 
 delete MuonIDSF; 
 delete EleIDSF;
 outputfile->Close();
 delete outputfile;

 gBenchmark->Show("running time");

}//end



void writeTEfficiency(TH1F* hBef, TH1F* hAft, TString name) {

    std::string hBefName(hBef->GetName());
    std::string hAftName(hAft->GetName());
    hBef->Write(hBefName.c_str());
    hAft->Write(hAftName.c_str());

    TEfficiency *TEff = 0;
    if(TEfficiency::CheckConsistency(*hAft, *hBef)){
        
        TEff = new TEfficiency(*hAft, *hBef);
        TEff->Write(name);
        delete TEff;
    
    }

}

void writeTEfficiency2D(TH2F* hBef, TH2F* hAft, TString name) {

    std::string hBefName(hBef->GetName());
    std::string hAftName(hAft->GetName());
    hBef->Write(hBefName.c_str());
    hAft->Write(hAftName.c_str());
  
    TEfficiency *TEff = 0;
    if(TEfficiency::CheckConsistency(*hAft, *hBef)){
            
        TEff = new TEfficiency(*hAft, *hBef);
        TEff->Write(name);
        delete TEff;

    }
    
}
