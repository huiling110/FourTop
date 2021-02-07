#define objectTSelector_cxx
// The class definition in objectTSelector.h has been generated automatically
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
// root> T->Process("objectTSelector.C")
// root> T->Process("objectTSelector.C","some options")
// root> T->Process("objectTSelector.C+")
//


#include "objectTSelector.h"
#include <TH2.h>
#include <TStyle.h>

void objectTSelector::SelectMuons(vector<TLorentzVector> &SelectedMuons,
                 vector<int> &SelectedMuonsIndex, int type, int stage) { /*{{{*/
  // changed ISO to ss of TTTT
  // 0 for Loose; 2 for medium 
  // for (UInt_t j = 0; j < Muon_pt->size(); ++j) {
  for (UInt_t j = 0; j < Muon_pt.GetSize(); ++j) {
      //in objectSelection.h Muon_pt_ is global variable
    if (stage == 1 || stage == 2 || stage == 3 || stage == 4) {
      //    if(!(Muon_pt.At(j)>20))                     continue;
    if (!(fabs(Muon_eta.At(j)) < 2.4))
      continue;
    if (stage == 2 || stage == 3 || stage == 4) {
      double pt = Muon_pt.At(j);
      if (type == 0) {
      if (!(Muon_loose.At(j) == 1))
        continue;
    }
    if (type == 1 or type == 2) {
      if(!(pt > 10)) continue;
      if (!(Muon_medium.At(j) == 1))
        continue;
    }
    if (stage == 3 || stage == 4) {
      //    if(type==2){ if(!(Muon_tight.At(j)==1))     continue; }
    //    if(!(Muon_relIsoDeltaBetaR04.At(j)<0.15))   continue;  //loose
    // iso.change to 0.15(tight) from 0.25
    // Muon_relIsoDeltaBetaR04?_
    double I1 = 0.4, I2 = 0, I3 = 0; // looseWP from ss of TTTT
    if(type == 2){
        I1 = 0.16; I2 = 0.76, I3 = 7.2;
    }
    //    if(!((Muon_miniIsoRel.At(j)<I1)|((Muon_jetptratio.At(j)>I2)&&(Muon_ptrel.At(j)>I3))))
    // continue;
    if (!((Muon_miniIsoRel.At(j) < I1) && ((Muon_jetptratio.At(j) > I2) || (Muon_ptrel.At(j) > I3))))      continue;

    if (stage == 4) {
    // IP
    // Muon_IP3Dsig_it;Muon_dz_pv;Muon_dz_bt;Muon_IP3D_sig;Muon_dxy_pv;
    if(!(Muon_dz_bt.At(j)<0.1)) continue;

    //?throwing an instance of 'std::out_of_range'
    if(!(Muon_dxy_bt.At(j)<0.05)) continue;
    if(type == 1 or type == 2) {
      if(!(Muon_IP3D_sig.At(j)<4)) continue;
    }
    //charge
    }// end stage 4
    }// end stage 3
    }// end stage 2 
    }// end stage 1
    //?Muon_jetptratioV2?
    TLorentzVector muon;
    muon.SetPtEtaPhiE(Muon_pt.At(j), Muon_eta.At(j), Muon_phi.At(j),
                      Muon_energy.At(j));
    SelectedMuons.push_back(muon);
    SelectedMuonsIndex.push_back(j);}
} /*}}}*/



void objectTSelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void objectTSelector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
    
   TString  outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/test_objectSelction/";
   TString outFileName = "TTTT.root";
   outputfile = new TFile( outputDir+outFileName, "RECREATE");
   tree = new TTree( "tree", "tree after object selection");

   tree->Branch( "muonsL", &muonsL); 
   tree->Branch( "muonsL_index", &muonsL_index);
   tree->Branch( "HLT_PFHT450_SixJet40_BTagCSV_p056_", &HLT_PFHT450_SixJet40_BTagCSV_p056_, "HLT_PFHT450_SixJet40_BTagCSV_p056_/I");

}

Bool_t objectTSelector::Process(Long64_t entry)
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

   fReader.SetLocalEntry(entry);
   fProcessed++;

    muonsL.clear(); muonsL_index.clear();
	SelectMuons( muonsL, muonsL_index, 0 ,4);

   HLT_PFHT450_SixJet40_BTagCSV_p056_ = *HLT_PFHT450_SixJet40_BTagCSV_p056;

   tree->Fill();

   return kTRUE;
}

void objectTSelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void objectTSelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

    outputfile->Write();
    outputfile->Close();
    
    Info("Terminate", "processed %lld events", fProcessed);

}
