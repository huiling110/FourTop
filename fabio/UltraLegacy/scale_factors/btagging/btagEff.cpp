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

void btagEff(string year, string analyzer, string dir) {

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
 map<string, string>::iterator file_it = file[year].begin();

while (file_it != file[year].end()) { //////////////////////// LOOP OVER FILES ///////////////////////

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

     
    TH2::AddDirectory(kFALSE); 
    TH2F * h_btagEff_den_b = new TH2F ("h_btagEff_den_b", "h_btagEff_den_b; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_b = new TH2F ("h_btagEff_num_b", "h_btagEff_num_b; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_den_c = new TH2F ("h_btagEff_den_c", "h_btagEff_den_c; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_c = new TH2F ("h_btagEff_num_c", "h_btagEff_num_c; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_den_udsg = new TH2F ("h_btagEff_den_udsg", "h_btagEff_den_udsg; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2F * h_btagEff_num_udsg = new TH2F ("h_btagEff_num_udsg", "h_btagEff_num_udsg; p_{T} [GeV]; #eta", NBINSX, binsX, NBINSY, binsY );
    TH2::AddDirectory(kTRUE);

    TChain mychain("tree");
    if (!(file_it->first.find(data) !=std::string::npos)) mychain.Add(input_dir + "outTree*.root"); 
    else mychain.Add(input_dir + "outTree*.root");
    TChain mychain2("allevents");
    if (!(file_it->first.find(data) !=std::string::npos)) mychain2.Add(input_dir + "outTree*.root");

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

    int mygenTtbarId = 0;
    mychain.SetBranchAddress("genTtbarId_", &mygenTtbarId);
    
    Long64_t nevents = mychain.GetEntries();

    for ( Long64_t ievent = 0; ievent < nevents; ++ievent ) {
        if (ievent > 5000000) break;
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

            //Get ttbb correction
            Float_t ttbbWeight;
            if ( file_it->first.find("ttbar") !=std::string::npos ) {

                if (mygenTtbarId%100 > 50) ttbbWeight = 1.2; // if ttbb, scale up by 1.2
                else ttbbWeight = non_ttbb_SF[year][file_it->first]; //if not, scale down by ttbar-process dependent factor
            
            }
            else ttbbWeight = 1.0;

            //loop over jets
            for (unsigned int i = 0; i < myjetsL->size(); i++) {
                if (fabs(myjets_flavor->at(i))==5) { // b jets
                    
                    h_btagEff_den_b->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF * ttbbWeight);

                    if (myjets_btags->at(i) > DeepJetM[year]) {
                        h_btagEff_num_b->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF * ttbbWeight);

                    }
                }// end b flavor

                else if (fabs(myjets_flavor->at(i))==4) { // c jets

                    h_btagEff_den_c->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF * ttbbWeight);
                    
                    if (myjets_btags->at(i) > DeepJetM[year]) {

                        h_btagEff_num_c->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF * ttbbWeight);

                    }
                }//end c flavor

                else { // light jets
                    
                    h_btagEff_den_udsg->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF * ttbbWeight);
                    
                    if (myjets_btags->at(i) > DeepJetM[year]) {
                        h_btagEff_num_udsg->Fill(fabs(myjetsL->at(i).Eta()), myjetsL->at(i).Pt(), mygenEvtWeight * myPUWeight * myprefireWeight * tauIDSF * eleIDSF * muonIDSF * ttbbWeight);
                        
                    }

                }//end light flavor
            
            }// end loop over jets

    }//end loop over events

    TH1D * totalWeight = new TH1D("totalWeight", "totalWeight", 1, -0.5, 0.5);
    TH1::AddDirectory(kFALSE);
    if (!(file_it->first.find(data) !=std::string::npos)) {  
        totalWeight->Fill(0.0, gen_sum_of_weights);
    }
    TH1::AddDirectory(kTRUE);

    outputfile->cd();

    writeTEfficiency2D(h_btagEff_den_b, h_btagEff_num_b, file_it, "btagEff_b_");
    writeTEfficiency2D(h_btagEff_den_c, h_btagEff_num_c, file_it, "btagEff_c_");
    writeTEfficiency2D(h_btagEff_den_udsg, h_btagEff_num_udsg, file_it, "btagEff_udsg_");

    std::string hTotalWeightName(totalWeight->GetName());
    hTotalWeightName.append("_");
    hTotalWeightName.append(file_it->first);
    totalWeight->Write(hTotalWeightName.c_str());
    
    delete myjetsL;
    delete myjets_flavor;
    delete myjets_btags;
    delete mybjetsM;
    delete myelesMVAT;
    delete mymuonsT;
    delete mytausT;
    delete mytausT_genPartFlav;
    delete myleptonsMVAT;
    
    delete h_btagEff_den_b;
    delete h_btagEff_num_b;
    delete h_btagEff_den_c;
    delete h_btagEff_num_c;
    delete h_btagEff_den_udsg;
    delete h_btagEff_num_udsg;
   
    delete genEvtWeights;
    delete totalWeight;
    
    mychain.Reset();
    mychain2.Reset();

    file_it++;

    }//end loop over files     
 
 delete MuonIDSF; 
 delete EleIDSF;
 outputfile->Close();
 delete outputfile;

 gBenchmark->Show("running time");

}//end

void writeTEfficiency2D(TH2F* hBef, TH2F* hAft, map<string, string>::iterator file_it, TString name) {

    std::string hBefName(hBef->GetName());
    hBefName.append("_");
    hBefName.append(file_it->first);
    std::string hAftName(hAft->GetName());
    hAftName.append("_");
    hAftName.append(file_it->first);
    hBef->Write(hBefName.c_str());
    hAft->Write(hAftName.c_str());
 
    TEfficiency *TEff = 0;
    if(TEfficiency::CheckConsistency(*hAft, *hBef)){
            
        TEff = new TEfficiency(*hAft, *hBef);
        TEff->Write(name+file_it->first);
        delete TEff;

    }
    
}
