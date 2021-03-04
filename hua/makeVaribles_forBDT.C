#define makeVaribles_forBDT_cxx
// The class definition in makeVaribles_forBDT.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("makeVaribles_forBDT.C")
// root> T->Process("makeVaribles_forBDT.C","some options")
// root> T->Process("makeVaribles_forBDT.C+")
//


#include "makeVaribles_forBDT.h"
#include <TH2.h>
#include <TStyle.h>

bool comparePt(const TLorentzVector a, const TLorentzVector b) {
    return a.Pt() > b.Pt();
}

// double HTcalculator(vector<TLorentzVector> SelectedJets) {
double HTcalculator( const TTreeReaderArray<TLorentzVector> &SelectedJets) {
    /*{{{*/
  double HTprov = 0;
  for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
    HTprov =
        HTprov + SelectedJets[j].Pt(); //.Pt: the 3 vertor component, scalar
  }
  return HTprov;
} /*}}}*/

double MHTcalculator(const vector<TLorentzVector> & SelectedJets) {
    /*{{{*/
  TLorentzVector SumJets;
  SumJets.SetPtEtaPhiE(0, 0, 0, 0);
  double MHTprov = 0;
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    SumJets = SumJets + SelectedJets[j];
  }
  MHTprov = SumJets.Pt();
  return MHTprov;
} /*}}}*/
///it seems we cant not use TTreeReaderArray as input parameter
//yes we can , just have to pass by address
double MHTcalculator(const TTreeReaderArray<TLorentzVector> &SelectedJets) {
    /*{{{*/
  TLorentzVector SumJets;
  SumJets.SetPtEtaPhiE(0, 0, 0, 0);
  double MHTprov = 0;
  for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
    SumJets = SumJets + SelectedJets[j];
  }
  MHTprov = SumJets.Pt();
  return MHTprov;
} /*}}}*/


// double InvariantMassCalculator(vector<TLorentzVector> SelectedJets) {
double InvariantMassCalculator(const TTreeReaderArray<TLorentzVector>&  SelectedJets) {
  TLorentzVector jet_sum = { 0, 0, 0, 0 };
  for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
    jet_sum = jet_sum + SelectedJets[j];
  }
  double InMass = jet_sum.M();
  return InMass;
}
double InvariantMassCalculator(vector<TLorentzVector> SelectedJets) {
  TLorentzVector jet_sum = { 0, 0, 0, 0 };
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    jet_sum = jet_sum + SelectedJets[j];
  }
  double InMass = jet_sum.M();
  return InMass;
}


double InvariantMass2SysCal(const TTreeReaderArray<TLorentzVector> a,
                            const TTreeReaderArray<TLorentzVector> b) {
  vector<TLorentzVector> vector_sum(a.begin(), a.end());
  vector_sum.insert(vector_sum.end(), b.begin(), b.end());
  /*    TLorentzVector jet_sum = {0,0,0,0};
      for (UInt_t j = 0; j < a.GetSize(); ++j){
          jet_sum = jet_sum + a[j];
      }
      TLorentzVector b_sum = {0,0,0,0};
      for (UInt_t k = 0; k < b.GetSize(); ++k){
          b_sum = b_sum + b[k];
      }*/
  double invariantMass = InvariantMassCalculator(vector_sum);
  return invariantMass;
}

// int ChargeSum(const vector<int> SelectedElectronsMVATIndex, int type) {
  // int charge_sum = 0;
  // for (UInt_t j = 0; j < SelectedElectronsMVATIndex.size(); ++j) {
    // if (type == 0)
      // charge_sum += patElectron_charge_->at(j);
      // charge_sum += patElectron_charge_->at(SelectedElectronsMVATIndex[j]);
    // if (type == 1)
      // charge_sum += Tau_charge_->at(SelectedElectronsMVATIndex[j]);
    // if (type == 2)
      // charge_sum += Muon_charge_->at(SelectedElectronsMVATIndex[j]);
  // }
  // return charge_sum;
// }

double TransEnergyCal(const TLorentzVector SelectedJets) {
  //    TVector3 p =  SelectedJets.Vect();
  double pt = SelectedJets.Pt();
  double trans_energy = sqrt(SelectedJets.M() * SelectedJets.M() + pt * pt);
  return trans_energy;
}

double TransEnergySysCal(const TTreeReaderArray<TLorentzVector>& SelectedJets) {
  double transE = 0;
  for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
    transE += TransEnergyCal(SelectedJets[j]);
  }
  return transE;
}
double TransEnergySysCal(const vector<TLorentzVector>& SelectedJets) {
  double transE = 0;
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    transE += TransEnergyCal(SelectedJets[j]);
  }
  return transE;
}

double TransMassCal(const TTreeReaderArray<TLorentzVector> SelectedJets) {
  double MHT = MHTcalculator(SelectedJets);
  double transE = 0;
  for (UInt_t j = 0; j < SelectedJets.GetSize(); ++j) {
    transE += TransEnergyCal(SelectedJets[j]);
  }
  double trans_mass = sqrt(MHT * MHT + transE * transE);
  return trans_mass;
}

double TransMassSysCal(const TTreeReaderArray<TLorentzVector>& Jets,
                       const vector<TLorentzVector>& Leptons) {
// double TransMassSysCal(const vector<TLorentzVector>& Jets,
                       // const vector<TLorentzVector>& Leptons) {
  double transE1 = TransEnergySysCal(Jets);
  double transE2 = TransEnergySysCal(Leptons);
  TLorentzVector SumJets;
  SumJets.SetPtEtaPhiE(0, 0, 0, 0);
  TLorentzVector SumLeptons;
  SumLeptons.SetPtEtaPhiE(0, 0, 0, 0);
  for (UInt_t j = 0; j < Jets.GetSize(); ++j) {
  // for (UInt_t j = 0; j < Jets.size(); ++j) {
    SumJets = SumJets + Jets[j];
  }
  // for (UInt_t k = 0; k < Leptons.GetSize(); ++k) {
  for (UInt_t k = 0; k < Leptons.size(); ++k) {
    SumLeptons = SumLeptons + Leptons[k];
  }
  TVector3 MHTsum = (SumJets + SumLeptons).Vect();
  double transMass =
      sqrt((transE1 + transE2) * (transE1 + transE2) - MHTsum * MHTsum);
  return transMass;
}

double MinDeltaRCal(const TTreeReaderArray<TLorentzVector> Jets,
                    const TTreeReaderArray<TLorentzVector> Leptons) {
  double deltaR_init = 10;
  double min_deltar = 10;
  double min_deltaR = 10;
  for (UInt_t j = 0; j < Jets.GetSize(); ++j) {
    for (UInt_t k = 0; k < Leptons.GetSize(); ++k) {
      deltaR_init = Jets[j].DeltaR(Leptons[k]);
      if (min_deltar > deltaR_init)
        min_deltar = deltaR_init;
    }
    if (min_deltar < min_deltaR)
      min_deltaR = min_deltar;
  }
  return min_deltaR;
}
double MinDeltaRSingleCal(const TTreeReaderArray<TLorentzVector>& Jets) {
  double min = 10;
  double min_2 = 10;
  double min_3 = 10;
  double min_1 = 10;
  for (UInt_t j = 0; j < Jets.GetSize(); ++j) {
    for (UInt_t k = j + 1; k < Jets.GetSize(); ++k) {
      min_1 = Jets[j].DeltaR(Jets[k]);
      if (min_1 < min)
        min = min_1;
    }
    min_2 = min;
    if (min_2 < min_3)
      min_3 = min_2;
  }
  return min_3;
}





void makeVaribles_forBDT::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void makeVaribles_forBDT::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   TString outFileName = option;
   outputfile = new TFile( outFileName, "RECREATE");
   cout<<outputfile->GetName()<<endl;

   newtree = new TTree( "newtree", "tree for BDT");

   newtree->Branch( "HLT_PFHT450_SixJet40_BTagCSV_p056", &HLT_PFHT450_SixJet40_BTagCSV_p056, "HLT_PFHT450_SixJet40_BTagCSV_p056/I");
   newtree->Branch( "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056", &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056/I");

   newtree->Branch( "Met_pt_", &Met_pt_, "Met_pt_/D");
   newtree->Branch( "Met_phi_", &Met_phi_, "Met_phi_/D");
   newtree->Branch( "muonsL_number", &muonsL_number, "muonsL_number/I");
   newtree->Branch( "muonsF_number", &muonsF_number, "muonsF_number/I");
   newtree->Branch( "muonsT_number", &muonsT_number, "muonsT_number/I");
  newtree->Branch("muonsT_1pt", &muonsT_1pt, "muonsT_1pt/D");
  newtree->Branch("muonsT_1eta", &muonsT_1eta, "muonsT_1eta/D");
  newtree->Branch("muonsT_1phi", &muonsT_1phi, "muonsT_1phi/D");
  newtree->Branch("muonsT_2pt", &muonsT_2pt, "muonsT_2pt/D");
  newtree->Branch("muonsT_2eta", &muonsT_2eta, "muonsT_2eta/D");
  newtree->Branch("muonsT_2phi", &muonsT_2phi, "muonsT_2phi/D");
  newtree->Branch("muonsT_3pt", &muonsT_3pt, "muonsT_3pt/I");
  newtree->Branch("muonsT_3eta", &muonsT_3eta, "muonsT_3eta/I");
  newtree->Branch("muonsT_3phi", &muonsT_3phi, "muonsT_3phi/I");
   newtree->Branch( "elesMVAL_number", &elesMVAL_number, "elesMVAL_number/I");
   newtree->Branch( "elesMVAF_number", &elesMVAF_number, "elesMVAF_number/I");
   newtree->Branch( "elesMVAT_number", &elesMVAT_number, "elesMVAT_number/I");
  newtree->Branch("elesMVAF_1pt", &elesMVAF_1pt,
                  "elesMVAF_1pt/D");
   newtree->Branch( "leptonsMVAT_number", &leptonsMVAT_number, "leptonsMVAT_number/I");
   newtree->Branch( "leptonsMVAF_number", &leptonsMVAF_number, "leptonsMVAF_number/I");
   newtree->Branch( "leptonsMVAL_number", &leptonsMVAL_number, "leptonsMVAL_number/I");
   newtree->Branch( "leptonsMVAT_transMass", &leptonsMVAT_transMass, "leptonsMVAT_transMass/D");
   newtree->Branch( "leptonsMVAF_transMass", &leptonsMVAF_transMass, "leptonsMVAF_transMass/D");
   newtree->Branch( "leptonsMVAL_transMass", &leptonsMVAL_transMass, "leptonsMVAL_transMass/D");
   newtree->Branch( "leptonsMVAT_2SS", &leptonsMVAT_2SS, "leptonsMVAT_2SS/I");
   newtree->Branch( "leptonsMVAT_2OS", &leptonsMVAT_2OS, "leptonsMVAT_2OS/I");
   // newtree->Branch( "", &, "/");
  newtree->Branch("leptonsMVAT_1pt", &leptonsMVAT_1pt,
                  "leptonsMVAT_1pt/D");
  newtree->Branch("leptonsMVAT_1eta", &leptonsMVAT_1eta,
                  "leptonsMVAT_1eta/D");
  newtree->Branch("leptonsMVAT_1phi", &leptonsMVAT_1phi,
                  "leptonsMVAT_1phi/D");
  newtree->Branch("leptonsMVAT_2pt", &leptonsMVAT_2pt,
                  "leptonsMVAT_2pt/D");
  newtree->Branch("leptonsMVAT_2eta", &leptonsMVAT_2eta,
                  "leptonsMVAT_2eta/D");
  newtree->Branch("leptonsMVAT_2phi", &leptonsMVAT_2phi,
                  "leptonsMVAT_2phi/D");
  newtree->Branch("leptonsMVAT_3pt", &leptonsMVAT_3pt,
                  "leptonsMVAT_3pt/D");
  newtree->Branch("leptonsMVAT_3eta", &leptonsMVAT_3eta,
                  "leptonsMVAT_3eta/D");
  newtree->Branch("leptonsMVAT_3phi", &leptonsMVAT_3phi, "leptonsMVAT_3phi/D");

  newtree->Branch("tausL_number", &tausL_number, "tausL_number/I");
  newtree->Branch("tausF_number", &tausF_number, "tausF_number/I");
  newtree->Branch("tausT_number", &tausT_number, "tausT_number/I");
  newtree->Branch("tausL_MHT", &tausL_MHT, "tausL_MHT/D");
  newtree->Branch("tausF_MHT", &tausF_MHT, "tausF_MHT/D");
  newtree->Branch("tausT_MHT", &tausT_MHT, "tausT_MHT/D");
  newtree->Branch("tausL_HT", &tausL_HT, "tausL_HT/D");
  newtree->Branch("tausF_HT", &tausF_HT, "tausF_HT/D");
  newtree->Branch("tausT_HT", &tausT_HT, "tausT_HT/D");
  newtree->Branch("tausL_invariantMass", &tausL_invariantMass,
                  "tausL_invariantMass/D");
  newtree->Branch("tausF_invariantMass", &tausF_invariantMass,   "tausF_invariantMass/D");
  newtree->Branch("tausT_invariantMass", &tausT_invariantMass,   "tausT_invariantMass/D");
  newtree->Branch("tausL_minDeltaR", &tausL_minDeltaR, "tausL_minDeltaR/D");
  newtree->Branch("tausF_minDeltaR", &tausF_minDeltaR, "tausF_minDeltaR/D");
  newtree->Branch("tausT_minDeltaR", &tausT_minDeltaR, "tausT_minDeltaR/D");
  newtree->Branch("tauL_1pt", &tauL_1pt, "tauL_1pt/D");
  newtree->Branch("tauL_1eta", &tauL_1eta, "tauL_1eta/D");
  newtree->Branch("tauL_1phi", &tauL_1phi, "tauL_1phi/D");
  newtree->Branch("tauL_2pt", &tauL_2pt, "tauL_2pt/D");
  newtree->Branch("tauL_2eta", &tauL_2eta, "tauL_2eta/D");
  newtree->Branch("tauL_2phi", &tauL_2phi, "tauL_2phi/D");
  newtree->Branch("tauL_3pt", &tauL_3pt, "tauL_3pt/D");
  newtree->Branch("tauL_3eta", &tauL_3eta, "tauL_3eta/D");
  newtree->Branch("tauL_3phi", &tauL_3phi, "tauL_3phi/D");
  newtree->Branch("tausF_leptonsT_transMass", &tausF_leptonsT_transMass, "tausF_leptonsT_transMass/D");
  newtree->Branch("tausL_leptonsT_transMass", &tausL_leptonsT_transMass, "tausL_leptonsT_transMass/D");
  newtree->Branch("tausT_leptonsT_transMass", &tausT_leptonsT_transMass,
                  "tausT_leptonsT_transMass/D");
  newtree->Branch("tausF_leptonsT_invariantMass", &tausF_leptonsT_invariantMass, "tausF_leptonsT_invariantMass/D");
  newtree->Branch("tausL_leptonsT_invariantMass", &tausL_leptonsT_invariantMass, "tausL_leptonsT_invariantMass/D");
  newtree->Branch("tausT_leptonsT_invariantMass", &tausT_leptonsT_invariantMass, "tausT_leptonsT_invariantMass/D");
  newtree->Branch("tausF_leptonsT_chargeSum", &tausF_leptonsT_chargeSum,
                  "tausF_leptonsT_chargeSum/D");
  newtree->Branch("tausF_leptonsTMVA_minDeltaR", &tausF_leptonsTMVA_minDeltaR, "tausF_leptonsTMVA_minDeltaR/D");
  newtree->Branch("tausL_leptonsTMVA_minDeltaR", &tausL_leptonsTMVA_minDeltaR, "tausL_leptonsTMVA_minDeltaR/D");
  newtree->Branch("tausT_leptonsTMVA_minDeltaR", &tausT_leptonsTMVA_minDeltaR, "tausT_leptonsTMVA_minDeltaR/D");

   // newtree->Branch( "", &, "/");

}

Bool_t makeVaribles_forBDT::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   // fReader.SetEntry(entry);
   fReader.SetLocalEntry(entry);
    fProcessed++;

    //initialize
    HLT_PFHT450_SixJet40_BTagCSV_p056 = -99;
    HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = -99;
    Met_pt_ = -99;
    Met_phi_ = -99;
    muonsL_number=-99;
    muonsF_number=-99;
   muonsT_number=-99;
     muonsT_1pt = -99;
     muonsT_1eta = -99;
     muonsT_1phi = -99;
     muonsT_2pt = -99;
     muonsT_2eta = -99;
     muonsT_2phi = -99;
     muonsT_3pt = -99;
     muonsT_3eta = -99;
     muonsT_3phi = -99;
     elesMVAL_number = -99;
     elesMVAF_number = -99;
     elesMVAT_number = -99;
     elesMVAF_1pt = -99;
     leptonsMVAT_number = -99;
     leptonsMVAF_number = -99;
     leptonsMVAL_number = -99;
     leptonsMVAT_transMass = -99;
     leptonsMVAF_transMass = -99;
     leptonsMVAL_transMass = -99;
     leptonsMVAT_2SS = -99;
     leptonsMVAT_2OS = -99;
     leptonsMVAT_1pt = -99;
     leptonsMVAT_1eta = -99;
     leptonsMVAT_1phi = -99;
     leptonsMVAT_2pt= -99;
     leptonsMVAT_2eta = -99;
     leptonsMVAT_2phi= -99;
     leptonsMVAT_3pt = -99;
     leptonsMVAT_3eta = -99;
     leptonsMVAT_3phi = -99;

     tausL_number=-99;
     tausF_number=-99;
     tausT_number=-99;
     tausL_MHT=-99;
     tausF_MHT=-99;
     tausT_MHT=-99;
     tausL_HT=-99;
     tausF_HT=-99;
     tausT_HT=-99;
     tausL_invariantMass=-99;
     tausF_invariantMass=-99;
     tausT_invariantMass=-99;
     tausF_minDeltaR = -99;
     tausL_minDeltaR = -99;
     tausT_minDeltaR = -99;
     tausF_leptonsT_transMass = -99;
     tausL_leptonsT_transMass = -99;
     tausT_leptonsT_transMass = -99;
     tausF_leptonsT_invariantMass = -99;
     tausL_leptonsT_invariantMass = -99;
     tausT_leptonsT_invariantMass = -99;
     tausF_leptonsT_chargeSum = -99;
     tausF_leptonsTMVA_minDeltaR = -99;
     tausT_leptonsTMVA_minDeltaR = -99;
     tausL_leptonsTMVA_minDeltaR = -99;
     tauL_1pt = -99;
     tauL_1eta = -99;
     tauL_1phi = -99;
     tauL_2pt = -99;
     tauL_2eta = -99;
     tauL_2phi = -99;
     tauL_3pt = -99;
     tauL_3eta = -99;
     tauL_3phi = -99;

      // = -99;
      // = -99;
      // = -99;


    HLT_PFHT450_SixJet40_BTagCSV_p056 = *HLT_PFHT450_SixJet40_BTagCSV_p056_;
    HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_;

    Met_pt_ = *Met_pt;
    Met_phi_ = *Met_phi;

              

    muonsL_number = muonsL.GetSize();
    muonsF_number = muonsF.GetSize();
    muonsT_number = muonsT.GetSize();
    // sort( muonsL.begin(), muonsL.end(), comparePt);
    // sort( muonsF.begin(), muonsF.end(), comparePt);
    sort( muonsT.begin(), muonsT.end(), comparePt);
    if (muonsT_number > 0) {
        muonsT_1pt = muonsT[0].Pt();
        muonsT_1eta = muonsT[0].Eta();
        muonsT_1phi = muonsT[0].Phi();
    }
    if (muonsT_number > 1) {
        muonsT_2pt = muonsT[1].Pt();
        muonsT_2eta = muonsT[1].Eta();
        muonsT_2phi = muonsT[1].Phi();
    }
    if (muonsT_number > 2) {
        muonsT_3pt = muonsT[2].Pt();
        muonsT_3eta = muonsT[2].Eta();
        muonsT_3phi = muonsT[2].Phi();
    }


      elesMVAL_number = eleMVAL.GetSize();
      elesMVAF_number = eleMVAF.GetSize();
      elesMVAT_number = eleMVAT.GetSize();
      sort(eleMVAF.begin(), eleMVAF.end(),  comparePt);
      if (elesMVAF_number > 0) {
        elesMVAF_1pt = eleMVAF[0].Pt();
      }

      vector<TLorentzVector> LeptonsMVAF(muonsF.begin(), muonsF.end());
      LeptonsMVAF.insert(LeptonsMVAF.end(), eleMVAF.begin(), eleMVAF.end());
      vector<TLorentzVector> LeptonsMVAT(muonsT.begin(),  muonsT.end());
      LeptonsMVAT.insert(LeptonsMVAT.end(), eleMVAT.begin(), eleMVAT.end());
      vector<TLorentzVector> LeptonsMVAL(muonsL.begin(),  muonsL.end());
      LeptonsMVAL.insert(LeptonsMVAL.end(), eleMVAL.begin(), eleMVAL.end());
      // TTreeReaderArray<TLorentzVector> LeptonsMVAL(muonsL.begin(),  muonsL.end());//not working

      // vector<int> LeptonsMVATIndex(muonsTIndex.begin(),  muonsTIndex.end());
      // LeptonsMVATIndex.insert(LeptonsMVATIndex.end(), eleMVATIndex.begin(), eleMVATIndex.end());

      leptonsMVAT_number = LeptonsMVAT.size();
      leptonsMVAF_number = LeptonsMVAF.size();
      leptonsMVAL_number = LeptonsMVAL.size();
      //???=0
      // leptonsMVAT_transMass = TransMassCal(LeptonsMVAT);
      // leptonsMVAF_transMass = TransMassCal(LeptonsMVAF);
      // leptonsMVAL_transMass = TransMassCal(LeptonsMVAL);
      // leptonsMVAT_chargeSum = ChargeSum()
      if ( leptonsMVAT_number==2 ) {
          if ( elesMVAT_number==2 ){
              if (patElectron_charge_.At(eleMVAT_index[0])*patElectron_charge_.At(eleMVAT_index[1])==1) leptonsMVAT_2SS = 1;
              else leptonsMVAT_2OS = 1 ;
          }
          if ( elesMVAT_number==1 ){
              if (patElectron_charge_.At(eleMVAT_index[0])*Muon_charge_.At(muonsT_index[0])==1) leptonsMVAT_2SS = 1;
              else leptonsMVAT_2OS = 1 ;
          }
          if ( elesMVAT_number==0){
              if ( Muon_charge_.At(muonsT_index[0])*Muon_charge_.At(muonsT_index[1])==1)  leptonsMVAT_2SS = 1;
              else leptonsMVAT_2OS = 1 ;
          }
      }


      sort(LeptonsMVAT.begin(), LeptonsMVAT.end(), comparePt);
      if (leptonsMVAT_number > 0) {
        leptonsMVAT_1pt = LeptonsMVAT[0].Pt();
        leptonsMVAT_1eta = LeptonsMVAT[0].Eta();
        leptonsMVAT_1phi = LeptonsMVAT[0].Phi();
      
      }
      if (leptonsMVAT_number > 1) {
        leptonsMVAT_2pt = LeptonsMVAT[1].Pt();
        leptonsMVAT_2eta = LeptonsMVAT[1].Eta();
        leptonsMVAT_2phi = LeptonsMVAT[1].Phi();
        
      }
      if (leptonsMVAT_number > 2) {
        leptonsMVAT_3pt = LeptonsMVAT[2].Pt();
        leptonsMVAT_3eta = LeptonsMVAT[2].Eta();
        leptonsMVAT_3phi = LeptonsMVAT[2].Phi();
      }


      // hadronic tau selection
      tausL_number = tausL.GetSize();
      tausF_number = tausF.GetSize();
      tausT_number = tausT.GetSize();
      tausL_MHT = MHTcalculator(tausL);
      tausF_MHT = MHTcalculator(tausF); 
      tausT_MHT = MHTcalculator( tausT); // 900;return the pt sum of,vetctor sum
      tausL_HT = HTcalculator(tausL);
      tausF_HT = HTcalculator(tausF);
      tausT_HT = HTcalculator(tausT);
      tausL_invariantMass = InvariantMassCalculator(tausL);
      tausF_invariantMass = InvariantMassCalculator(tausF);
      tausT_invariantMass = InvariantMassCalculator(tausT);
      tausL_minDeltaR = MinDeltaRSingleCal(tausL);
      tausF_minDeltaR = MinDeltaRSingleCal(tausF);
      tausT_minDeltaR = MinDeltaRSingleCal(tausT);

      tausF_leptonsT_transMass = TransMassSysCal(tausF, LeptonsMVAT);
      tausL_leptonsT_transMass = TransMassSysCal(tausL, LeptonsMVAT);
      tausT_leptonsT_transMass = TransMassSysCal(tausT, LeptonsMVAT);
      // tausF_leptonsT_invariantMass = InvariantMass2SysCal(tausF, LeptonsMVAT);
      // tausL_leptonsT_invariantMass = InvariantMass2SysCal(tausL, LeptonsMVAT);
      // tausT_leptonsT_invariantMass = InvariantMass2SysCal(tausT, LeptonsMVAT);
      // tausF_leptonsT_chargeSum = ChargeSum(tausF_index, 1) +
                                 // ChargeSum(eleMVAT_index, 0) +
                                 // ChargeSum(muonsT_index, 2);
      // tausF_leptonsTMVA_minDeltaR = MinDeltaRCal(LeptonsMVAT, tausF);
      // tausL_leptonsTMVA_minDeltaR = MinDeltaRCal(LeptonsMVAT, tausL);
      // tausT_leptonsTMVA_minDeltaR = MinDeltaRCal(LeptonsMVAT, tausT);

      sort(tausL.begin(), tausL.end(), comparePt);
      if (tausL_number > 0) {
        tauL_1pt = tausL[0].Pt();
        tauL_1eta = tausL[0].Eta();
        tauL_1phi = tausL[0].Phi();
      }
      if (tausL_number > 1) {
        tauL_2pt = tausL[1].Pt();
        tauL_2eta = tausL[1].Eta();
        tauL_2phi = tausL[1].Phi();
      }
      if (tausL_number > 2) {
        tauL_3pt = tausL[2].Pt();
        tauL_3eta = tausL[2].Eta();
        tauL_3phi = tausL[2].Phi();
      }
 






    newtree->Fill();

   return kTRUE;
}

void makeVaribles_forBDT::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void makeVaribles_forBDT::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   outputfile->Write();
   outputfile->Close();

   Info("Terminate", "processed %lld events", fProcessed);
   Info("Terminate", "output file here: %s", outputfile->GetName());

}
