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


    HLT_PFHT450_SixJet40_BTagCSV_p056 = *HLT_PFHT450_SixJet40_BTagCSV_p056_;
    HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_;

    Met_pt_ = *Met_pt;
    Met_phi_ = *Met_phi;

    sort( muonsL.begin(), muonsL.end(), comparePt);
    sort( muonsF.begin(), muonsF.end(), comparePt);
    sort( muonsT.begin(), muonsT.end(), comparePt);
    muonsL_number = muonsL.GetSize();
    muonsF_number = muonsF.GetSize();
    muonsT_number = muonsT.GetSize();
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
