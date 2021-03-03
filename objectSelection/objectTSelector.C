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


Double_t DeltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2) {
  Double_t deltaPhi = TMath::Abs(phi1 - phi2);
  Double_t deltaEta = eta1 - eta2;
  if (deltaPhi > TMath::Pi())
    deltaPhi = TMath::TwoPi() - deltaPhi;
  return TMath::Sqrt(deltaEta * deltaEta + deltaPhi * deltaPhi);
}


Double_t deltRmin(const Double_t eta1, const Double_t phi1, const vector<TLorentzVector> LeptonsMVAF){
    Double_t deltaR = 0;
    Double_t minDeltaR = 100;
    for (UInt_t lep = 0; lep < LeptonsMVAF.size(); lep++){
        deltaR =  DeltaR( LeptonsMVAF[lep].Eta(), eta1, LeptonsMVAF[lep].Phi(), phi1);
        if ( deltaR < minDeltaR ) minDeltaR = deltaR ;//The continue statement provides a convenient way to jump to the end of the loop body for the current iteration.
    }
    return minDeltaR; 
}

bool compEle(const TLorentzVector a, const TLorentzVector b) {
    return a.Pt() > b.Pt();
}

void copy_TTreeReaderArray_toVector( const TTreeReaderArray<double> &array, vector<Double_t> & vec){
    for( UInt_t i=0; i< array.GetSize(); i++){
        vec.push_back( array.At(i));
    }
}




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

   if ( option.Contains( "JetHT") ) isdata = true;
   cout<<"is data?: "<<isdata<<endl;
    
   // TString inName = fChain->GetName();
   // cout<<inName<<endl;
   TString outFileName = option;
   outputfile = new TFile( outFileName, "RECREATE");
   cout<<outputfile->GetName()<<endl;
   // cout<<outputfile->IsZombie()<<endl;
   
   h_genWeight = new TH1D( "h_genweight", "h_genweight", 1,-0.5, 0.5);

   tree = new TTree( "tree", "tree after object selection");

   tree->Branch( "muonsL", &muonsL);
   tree->Branch( "muonsL_index", &muonsL_index);
   tree->Branch( "muonsF", &muonsF );
   tree->Branch( "muonsF_index", &muonsF_index );
   tree->Branch( "muonsT", &muonsT );
   tree->Branch( "muonsT_index", &muonsT_index );
   tree->Branch( "eleMVAL", &eleMVAL );
   tree->Branch( "eleMVAF", &eleMVAF );
   tree->Branch( "eleMVAT", &eleMVAT );
   tree->Branch( "eleMVAL_index", &eleMVAL_index );
   tree->Branch( "eleMVAF_index", &eleMVAF_index );
   tree->Branch( "eleMVAT_index", &eleMVAT_index );
   tree->Branch( "eleMVAL_IsoT",  &eleMVAL_IsoT );
   tree->Branch( "eleMVAL_IsoT_index", &eleMVAL_IsoT_index );
   tree->Branch( "eleMVAF_IsoT", &eleMVAF_IsoT );
   tree->Branch( "eleMVAF_IsoT_index", &eleMVAF_IsoT_index );
   tree->Branch( "eleMVAT_IsoT", &eleMVAT_IsoT );
   tree->Branch( "eleMVAT_IsoT_index", &eleMVAT_IsoT_index );

   tree->Branch( "tausL", &tausL );
   tree->Branch( "tausF", &tausF );
   tree->Branch( "tausT", &tausT );
   tree->Branch( "tausL_index", &tausL_index );
   tree->Branch( "tausF_index", &tausF_index );
   tree->Branch( "tausT_index", &tausT_index );
   tree->Branch( "jets", &jets );
   tree->Branch( "jets_index", &jets_index );
   tree->Branch( "jets_btags", &jets_btags );
   tree->Branch( "bjetsL", &bjetsL );
   tree->Branch( "bjetsL_index", &bjetsL_index );
   tree->Branch( "bjetsL_btags", &bjetsL_btags );
   tree->Branch( "bjetsM", &bjetsM );
   tree->Branch( "bjetsM_index", &bjetsM_index );
   tree->Branch( "bjetsM_btags", &bjetsM_btags );
   tree->Branch( "bjetsT", &bjetsT );
   tree->Branch( "bjetsT_index", &bjetsT_index );
   tree->Branch( "bjetsT_btags", &bjetsT_btags );
   tree->Branch( "forwardJets", &forwardJets );
   tree->Branch( "forwardJets_index", &forwardJets_index );
   tree->Branch( "forwardJets_btags", &forwardJets_btags );
   // tree->Branch( "", & );
   tree->Branch( "patElectron_charge_", &patElectron_charge_  );
   tree->Branch( "Tau_charge_", &Tau_charge_ );
   tree->Branch( "Muon_charge_", &Muon_charge_ );
   if ( !isdata ){
       tree->Branch( "genTaus", &genTaus );
       tree->Branch( "genEles", &genEles );
       tree->Branch( "genMuons", &genMuons );
   }
   tree->Branch( "Met_pt", &Met_pt, "Met_pt/D" );
   tree->Branch( "Met_phi", &Met_phi, "Met_phi/D" );
   tree->Branch( "tops_toptagger", &tops_toptagger);

   tree->Branch( "EVENT_prefireWeight_", &EVENT_prefireWeight_, "EVENT_prefireWeight_/D" );
   if ( !isdata ){
       tree->Branch( "EVENT_genWeight__", &EVENT_genWeight_, "EVENT_genWeight_/D" );
   }


    tree->Branch( "HLT_PFHT450_SixJet40_BTagCSV_p056_", &HLT_PFHT450_SixJet40_BTagCSV_p056_, "HLT_PFHT450_SixJet40_BTagCSV_p056_/I");
    tree->Branch( "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_", &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_/I");
    tree->Branch( "HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_", &HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_, "HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_/I");
    tree->Branch( "HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_", &HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_, "HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_/I");
    tree->Branch( "HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_", &HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_, "HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_/I");
    tree->Branch( "HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_", &HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_, "HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_/I");
    tree->Branch( "HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_", &HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_, "HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_/I");
    tree->Branch( "HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_", &HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_, "HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_/I");
    tree->Branch( "HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_", &HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_, "HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_/I");//this HLT doesn't exist in ntuple
 
    tree->Branch( "HLT_Ele27_eta2p1_WPTight_Gsf_", &HLT_Ele27_eta2p1_WPTight_Gsf_, "HLT_Ele27_eta2p1_WPTight_Gsf_/I");
    tree->Branch( "HLT_Ele27_eta2p1_WPLoose_Gsf_", &HLT_Ele27_eta2p1_WPLoose_Gsf_, "HLT_Ele27_eta2p1_WPLoose_Gsf_/I");
    tree->Branch( "HLT_Ele27_WPTight_Gsf_", &HLT_Ele27_WPTight_Gsf_, "HLT_Ele27_WPTight_Gsf_/I");
    tree->Branch( "HLT_IsoMu22_", &HLT_IsoMu22_, "HLT_IsoMu22_/I");
    tree->Branch( "HLT_Ele25_eta2p1_WPTight_Gsf_", &HLT_Ele25_eta2p1_WPTight_Gsf_, "HLT_Ele25_eta2p1_WPTight_Gsf_/I");
    tree->Branch( "HLT_IsoTkMu22_", &HLT_IsoTkMu22_, "HLT_IsoTkMu22_/I");
    tree->Branch( "HLT_IsoMu24_", &HLT_IsoMu24_, "HLT_IsoMu24_/I");
    tree->Branch( "HLT_IsoTkMu24_", &HLT_IsoTkMu24_, "HLT_IsoTkMu24_/I");
    tree->Branch( "HLT_IsoMu22_eta2p1_", &HLT_IsoMu22_eta2p1_, "HLT_IsoMu22_eta2p1_/I");
    tree->Branch( "HLT_IsoTkMu22_eta2p1_", &HLT_IsoTkMu22_eta2p1_, "HLT_IsoTkMu22_eta2p1_/I");
    tree->Branch( "HLT_Mu50_", &HLT_Mu50_, "HLT_Mu50_/I");
    tree->Branch( "HLT_TkMu50_", &HLT_TkMu50_, "HLT_TkMu50_/I");
    tree->Branch( "HLT_Ele32_WPTight_Gsf_", &HLT_Ele32_WPTight_Gsf_, "HLT_Ele32_WPTight_Gsf_/I");
    tree->Branch( "HLT_Ele35_WPTight_Gsf_", &HLT_Ele35_WPTight_Gsf_, "HLT_Ele35_WPTight_Gsf_/I");
    tree->Branch( "HLT_IsoMu27_", &HLT_IsoMu27_, "HLT_IsoMu27_/I");

    tree->Branch( "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_/I");
    tree->Branch( "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_/I");
    tree->Branch( "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_/I");
    tree->Branch( "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_, "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_/I");
    tree->Branch( "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_, "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_/I");
    tree->Branch( "HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_", &HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_, "HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_/I");
    tree->Branch( "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_", &HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_, "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_/I");
    tree->Branch( "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_", &HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_, "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_/I");

    tree->Branch( "HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_", &HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_, "HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_/I");
    tree->Branch( "HLT_DoubleEle33_CaloIdL_MW_", &HLT_DoubleEle33_CaloIdL_MW_, "HLT_DoubleEle33_CaloIdL_MW_/I");
    tree->Branch( "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_", &HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_, "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_/I");
    tree->Branch( "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_/I");
    tree->Branch( "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_/I");
    tree->Branch( "HLT_DoubleMu33NoFiltersNoVtx_", &HLT_DoubleMu33NoFiltersNoVtx_, "HLT_DoubleMu33NoFiltersNoVtx_/I");
    tree->Branch( "HLT_DoubleMu23NoFiltersNoVtxDisplaced_", &HLT_DoubleMu23NoFiltersNoVtxDisplaced_, "HLT_DoubleMu23NoFiltersNoVtxDisplaced_/I");
    tree->Branch( "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_/I");
    tree->Branch( "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_/I");
    tree->Branch( "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_/I");
    tree->Branch( "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_/I");
    tree->Branch( "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_/I");
    tree->Branch( "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_/I");
    tree->Branch( "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_", &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_, "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_/I");
    tree->Branch( "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_", &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_, "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_/I");
    tree->Branch( "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_/I");
    tree->Branch( "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_/I");
    tree->Branch( "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_/I");
    tree->Branch( "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_/I");

    tree->Branch( "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_", &HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_, "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_/I");
    tree->Branch( "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_", &HLT_Mu8_DiEle12_CaloIdL_TrackIdL_, "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_/I");
    tree->Branch( "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_", &HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_, "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_/I");
    tree->Branch( "HLT_TripleMu_12_10_5_", &HLT_TripleMu_12_10_5_, "HLT_TripleMu_12_10_5_/I");
    tree->Branch( "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_", &HLT_DiMu9_Ele9_CaloIdL_TrackIdL_, "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_/I");
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

   //
   if ( !isdata ){
       h_genWeight->Fill( 0.0 , *EVENT_genWeight );
   }

   //MET filters
    if (!(*Flag_goodVertices == 1)) return kFALSE; // a branch in tree.
    if (!(*Flag_globalSuperTightHalo2016Filter == 1))    return kFALSE;
    if (!(*Flag_HBHENoiseFilter == 1))        return kFALSE;
    if (!(*Flag_HBHENoiseIsoFilter == 1))        return kFALSE;
    if (!(*Flag_EcalDeadCellTriggerPrimitiveFilter == 1))        return kFALSE; // a branch in Tree
    if (!(*Flag_BadPFMuonFilter == 1))      return kFALSE;
      //			if(!(*Flag_ecalBadCalibReducedMINIAODFilter==1))
      // return kFALSE;
      //			why this filter not work?//applied only in 2017 and 2018
      if (isdata) {  if (!(*Flag_eeBadScFilter == 1)) return kFALSE;}
    
    //HLT
    HLT_PFHT450_SixJet40_BTagCSV_p056_ = *HLT_PFHT450_SixJet40_BTagCSV_p056;
    HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ = *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056;
    HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_ = *HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg;
    HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_ = *HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg;
    HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_ = *HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg;
    HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_ = *HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg;
    HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_ = *HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg;
    HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_ = *HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg;
    HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_ = *HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg;//this HLT doesn't exist in ntuple
 
    HLT_Ele27_eta2p1_WPTight_Gsf_ = *HLT_Ele27_eta2p1_WPTight_Gsf;
    HLT_Ele27_eta2p1_WPLoose_Gsf_ = *HLT_Ele27_eta2p1_WPLoose_Gsf;
    HLT_Ele27_WPTight_Gsf_ = *HLT_Ele27_WPTight_Gsf;
    HLT_IsoMu22_ = *HLT_IsoMu22;
    HLT_Ele25_eta2p1_WPTight_Gsf_ = *HLT_Ele25_eta2p1_WPTight_Gsf;
    HLT_IsoTkMu22_ = *HLT_IsoTkMu22;
    HLT_IsoMu24_ = *HLT_IsoMu24;
    HLT_IsoTkMu24_ = *HLT_IsoTkMu24;
    HLT_IsoMu22_eta2p1_ = *HLT_IsoMu22_eta2p1;
    HLT_IsoTkMu22_eta2p1_ = *HLT_IsoTkMu22_eta2p1;
    HLT_Mu50_ = *HLT_Mu50;
    HLT_TkMu50_ = *HLT_TkMu50;
    HLT_Ele32_WPTight_Gsf_ = *HLT_Ele32_WPTight_Gsf;
    HLT_Ele35_WPTight_Gsf_ = *HLT_Ele35_WPTight_Gsf;
    HLT_IsoMu27_ = *HLT_IsoMu27;

    HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_ = *HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20;
    HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_ = *HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1;
    HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_ = *HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30;
    HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_ = *HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1;
    HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_ = *HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1;
    HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_ = *HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1;
    HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_ = *HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1;
    HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_ = *HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1;

    HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_ = *HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf;
    HLT_DoubleEle33_CaloIdL_MW_ = *HLT_DoubleEle33_CaloIdL_MW;
    HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_ = *HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW;
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_ = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
    HLT_DoubleMu33NoFiltersNoVtx_ = *HLT_DoubleMu33NoFiltersNoVtx;
    HLT_DoubleMu23NoFiltersNoVtxDisplaced_ = *HLT_DoubleMu23NoFiltersNoVtxDisplaced;
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_ = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_ = *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_ = *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_ = *HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_ = *HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
    HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_ = *HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL;
    HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_ = *HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ;
    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_ = *HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ = *HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_ = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
    HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_ = *HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;

    HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_ = *HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;
    HLT_Mu8_DiEle12_CaloIdL_TrackIdL_ = *HLT_Mu8_DiEle12_CaloIdL_TrackIdL;
    HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_ = *HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ;
    HLT_TripleMu_12_10_5_ = *HLT_TripleMu_12_10_5;
    HLT_DiMu9_Ele9_CaloIdL_TrackIdL_ = *HLT_DiMu9_Ele9_CaloIdL_TrackIdL;

    muonsL.clear(); muonsL_index.clear();
    muonsF.clear(); muonsF_index.clear();
    muonsT.clear(); muonsT_index.clear();
    eleMVAL.clear(); eleMVAL_index.clear();
    eleMVAF.clear(); eleMVAF_index.clear();
    eleMVAT.clear(); eleMVAT_index.clear();
    eleMVAL_IsoT.clear(); eleMVAL_IsoT_index.clear();
    eleMVAF_IsoT.clear(); eleMVAF_IsoT_index.clear();
    eleMVAT_IsoT.clear(); eleMVAT_IsoT_index.clear();
    // .clear(); _index.clear();
    tausL.clear(); tausL_index.clear();
    tausF.clear(); tausF_index.clear();
    tausT.clear(); tausT_index.clear();
    jets.clear(); jets_index.clear(); jets_btags.clear();
    bjetsL.clear(); bjetsL_index.clear(); bjetsL_btags.clear();
    bjetsM.clear(); bjetsM_index.clear(); bjetsM_btags.clear();
    bjetsT.clear(); bjetsT_index.clear(); bjetsT_btags.clear();
    forwardJets.clear(); forwardJets_index.clear(); forwardJets_btags.clear();
    patElectron_charge_.clear();
    Tau_charge_.clear();
    Muon_charge_.clear();

    tops_toptagger.clear();
    // .clear(); _index.clear();

    SelectMuons( muonsL, muonsL_index, 0 ,4);// sort( muonsL.begin(), muonsL.end(), compEle);
    SelectMuons( muonsF, muonsF_index, 1, 4);// sort( muonsF.begin(), muonsF.end(), compEle);
    SelectMuons( muonsT, muonsT_index, 2, 4); //sort( muonsT.begin(), muonsT.end(), compEle);

    SelectElectronsMVA( eleMVAL, eleMVAL_index, 0, 4, false );// sort( eleMVAL.begin(), eleMVAL.end(), compEle);
    SelectElectronsMVA( eleMVAF, eleMVAF_index, 1, 4, false );// sort( eleMVAF.begin(), eleMVAF.end(), compEle);
    SelectElectronsMVA( eleMVAT, eleMVAT_index, 2, 4, false ); //sort( eleMVAT.begin(), eleMVAT.end(), compEle);
    SelectElectronsMVA( eleMVAL_IsoT, eleMVAL_IsoT_index, 0, 4, true );
    SelectElectronsMVA( eleMVAF_IsoT, eleMVAF_IsoT_index, 1, 4, true );
    SelectElectronsMVA( eleMVAT_IsoT, eleMVAT_IsoT_index, 2, 4, true );

    SelectTaus( tausL, tausL_index, 1, eleMVAL); //sort( tausL.begin(), tausL.end(), compEle);
    SelectTaus( tausF, tausF_index, 2, eleMVAL); //sort( tausF.begin(), tausF.end(), compEle);
    SelectTaus( tausT, tausT_index, 3 , eleMVAL);// sort( tausT.begin(), tausT.end(), compEle);
    
    bool deepJet = true;
    bool SysJes = 0; bool SysJer=0;
    SelectJets( 0, deepJet, jets, jets_btags, jets_index, SysJes, SysJer, eleMVAF, tausL);
    // sort( jets.begin(), jets.end(), compEle);
    SelectJets( 11, deepJet, bjetsL, bjetsL_btags, bjetsL_index, SysJes, SysJer,  eleMVAF, tausL);
    // sort( bjetsL.begin(), bjetsL.end(), compEle);
    SelectJets( 12, deepJet, bjetsM, bjetsM_btags, bjetsM_index,  SysJes, SysJer, eleMVAF, tausL);
    // sort( bjetsM.begin(), bjetsM.end(), compEle);
    SelectJets( 13, deepJet, bjetsT, bjetsT_btags, bjetsT_index, SysJes, SysJer, eleMVAF, tausL);
    // sort( bjetsT.begin(), bjetsT.end(), compEle);
    SelectJets( 2, deepJet, forwardJets, forwardJets_btags, forwardJets_index, SysJes,  SysJer,  eleMVAF, tausL);
    // sort( forwardJets.begin(), forwardJets.end(), compEle);

    // patElectron_charge_ = patElectron_charge; //= not working
    // cout<<patElectron_charge.GetSize();
    if ( patElectron_charge.GetSize() > 0 ){
        copy_TTreeReaderArray_toVector( patElectron_charge, patElectron_charge_);}
    if ( Tau_charge.GetSize()>0 ){
        copy_TTreeReaderArray_toVector( Tau_charge, Tau_charge_);
    }
    if ( Muon_charge.GetSize()>0 ){
        copy_TTreeReaderArray_toVector( Muon_charge, Muon_charge_);
    }

    MetCorrection(SysJes, SysJer, Met_pt);
    Met_phi = *Met_type1PF_phi; 
    
    SelectTops( tops_toptagger);

    //gen information
    if ( !isdata ){
        genTaus.clear();
        genEles.clear();
        genMuons.clear();
        selectGenTaus(genTaus);
        selectGenEles(genEles);
        selectGenMuons(genMuons);
    }

    EVENT_prefireWeight_ = *EVENT_prefireWeight;
    if ( !isdata ){
        EVENT_genWeight_ = *EVENT_genWeight;
    }

    //preselection
    if ( !( tausL.size()>0)) return kFALSE;
    if ( !( jets.size()>3))  return kFALSE;
    if ( !( bjetsL.size()>1)) return kFALSE;

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
    Info("Terminate", "output file here: %s", outputfile->GetName());

}


void objectTSelector::SelectMuons(vector<TLorentzVector> &SelectedMuons,
                 vector<Int_t> &SelectedMuonsIndex,const Int_t type, const Int_t stage) { /*{{{*/
  // changed ISO to ss of TTTT
  // 0 for Loose; 2 for medium 
  for (UInt_t j = 0; j < Muon_pt.GetSize(); ++j) {
      //in objectSelection.h Muon_pt_ is global variable
      if (stage == 1 || stage == 2 || stage == 3 || stage == 4) {
          if(!(Muon_pt.At(j)>10))                     continue;
          if (!(fabs(Muon_eta.At(j)) < 2.4))        continue;
          if (stage == 2 || stage == 3 || stage == 4) {
              // Double_t pt = Muon_pt.At(j);
              if (type == 0) {
              if (!(Muon_loose.At(j) == 1))              continue;
              }
              if (type == 1 or type == 2) {
                // if(!(pt > 10)) continue;
                if (!(Muon_medium.At(j) == 1))
                  continue;
              }
              if (stage == 3 || stage == 4) {
                    //    if(type==2){ if(!(Muon_tight.At(j)==1))     continue; }
                  //    if(!(Muon_relIsoDeltaBetaR04.At(j)<0.15))   continue;  //loose
                  // iso.change to 0.15(tight) from 0.25
                  // Muon_relIsoDeltaBetaR04?_
                  Double_t I1 = 0.4, I2 = 0, I3 = 0; // looseWP from ss of TTTT
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
      SelectedMuonsIndex.push_back(j);
  }
} /*}}}*/



void objectTSelector::SelectElectronsMVA(vector<TLorentzVector> &SelectedElectrons,vector<Int_t> &SelectedElectronsIndex, const Int_t type, const Int_t stage, const bool isTightIso ) {
  // 0 for VLoose; 1 for VLooseFO(fakeble object); 2 for tight
  // 2016 - MVANoIso94XV2, from SUSY
  /*{{{*/
    for (UInt_t j = 0; j < patElectron_pt.GetSize(); ++j) { // banch in tree
        if (stage == 1 || stage == 2 || stage == 3 || stage == 4) {
            Double_t pt = patElectron_pt.At(j);
            Double_t eta = patElectron_eta.At(j);
            Double_t MVA_value = patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Values.At(j);
            Double_t raw_MVA_value = 0.5 * log ( (1 + MVA_value)/(1 - MVA_value) );
            if (!(fabs(eta) < 2.5))  continue;
            if (!(pt > 10))         continue;
            if (stage == 2 || stage == 3 || stage  == 4) {
              //id
                if (fabs(eta) < 0.8) {
                  if (type == 2) {
                    // if(!(pt > 10)) continue;
                    if (10 < pt && pt < 40) {
                      if (!(raw_MVA_value > (3.447 + 0.063 * (pt - 25))))
                        continue;
                    }
                    if (pt >= 40) {
                      if (!(raw_MVA_value > 4.392))
                        continue;
                    }
                  }
                  if (type == 0) {
                    if (5 < pt && pt < 10) {
                      if (!(raw_MVA_value > 1.309))
                        continue;
                    }
                    if (10 < pt && pt < 25) {
                      if (!(raw_MVA_value > ( 0.887 + 0.088 * (pt - 25))))
                        continue;
                    }
                    if (pt >= 25) {
                      if (!(raw_MVA_value > 0.887))
                        continue;
                    }
                  }
                  if (type == 1) {
                    if (5 < pt && pt < 10) {
                      if (!(raw_MVA_value > (-0.259)))
                        continue;
                    }
                    if (10 < pt && pt <= 25) {
                      if (!(raw_MVA_value >( (-0.388) + 0.109 * (pt - 25))))
                        continue;
                    }
                    if (pt >= 25) {
                      if (!(raw_MVA_value > (-0.388)))
                        continue;
                    }
                  }
                }
                if (0.8 <= fabs(eta) && fabs(eta) < 1.479) {
                  if (type == 2) {
                if(!(pt > 10)) continue;
                    if (10 < pt && pt < 40) {
                      if (!(raw_MVA_value > (2.522 + 0.058 * (pt - 25))))
                        continue;
                    }
                    if (pt >= 40) {
                      if (!(raw_MVA_value > 3.392))
                        continue;
                    }
                  }
                  if (type == 0) {
                    if (5 < pt && pt <= 10) {
                      if (!(raw_MVA_value > 0.373))
                        continue;
                    }
                    if (10 < pt && pt < 25) {
                      if (!(raw_MVA_value > (0.112 + 0.099 * (pt - 25))))
                        continue;
                    }
                    if (pt >= 25) {
                      if (!(raw_MVA_value > 0.112))
                        continue;
                    }
                  }
                  if (type == 1) {
                    if (5 < pt && pt <= 10) {
                      if (!(raw_MVA_value > (-0.256)))
                        continue;
                    }
                    if (10 < pt && pt < 25) {
                      if (!(raw_MVA_value > (-0.696) + 0.106 * (pt - 25)))
                        continue;
                    }
                    if (pt >= 25) {
                      if (!(raw_MVA_value > (-0.696)))
                        continue;
                    }
                  }
                }
                if (1.479 <= fabs(eta) && fabs(eta) < 2.5) {
                  if (type == 2) {
                    if(!(pt > 10)) continue;
                    if (10 < pt && pt < 40) {
                      if (!(raw_MVA_value > (1.555 + 0.075 * (pt - 25))))
                        continue;
                    }
                    if (pt >= 40) {
                      if (!(raw_MVA_value > 2.680))
                        continue;
                    }
                  }
                  if (type == 0) {
                    if (5 < pt && pt <= 10) {
                      if (!(raw_MVA_value > 0.071))
                        continue;
                    }
                    if (10 < pt && pt < 25) {
                      if (!(raw_MVA_value > ((-0.017) + 0.137 * (pt - 25))))
                        continue;
                    }
                    if (pt >= 25) {
                      if (!(raw_MVA_value > (-0.017)))
                        continue;
                    }
                  }
                  if (type == 1) {
                    if (5 < pt && pt <= 10) {
                      if (!(raw_MVA_value > (-1.630)))
                        continue;
                    }
                    if (10 < pt && pt < 25) {
                      if (!(raw_MVA_value > ((-1.219) + 0.148 * (pt - 25))))
                        continue;
                    }
                    if (pt >= 25) {
                      if (!(raw_MVA_value > (-1.219)))
                        continue;
                    }
                  }
                }
                
                if (stage == 3 || stage == 4) {
                     // ISO
                    Double_t I1 = 0.4, I2 = 0, I3 = 0;
                    if (type == 0 || type == 1) {
                      I1 = 0.4;
                      I2 = 0;
                      I3 = 0;
                    } // looseWP from ss of TTTT}
                    if(type == 2) {
                        if ( isTightIso ) I1 = 0.12; I2 = 0.80; I3 = 7.2;
                    }//TightWP of SS
                    //    ??patElectron_jetptratioV2?
                    if (!((patElectron_miniIsoRel.At(j) < I1) && ((patElectron_jetptratio.At(j) > I2) ||   (patElectron_ptrel.At(j) > I3))))      continue;
                    //?if we apply this for tight , the number would be very low.
                
                    if (stage == 4) {
                        // emulation selection
                        // IP
                        //?
                        // patElectron_IP3Dsig;patElectron_IP3D_sig;patElectron_sIP3D_sig;patElectron_d0;patElectron_gsfTrack_dz_pv;
                        if (!(patElectron_d0.At(j) < 0.05))
                          continue;
                        if (!(patElectron_gsfTrack_dz_pv.At(j) < 0.1))
                          continue;
                        if (type == 1 or type == 2) {
                          if (!(patElectron_IP3D_sig.At(j) < 4))
                            continue;
                        }
                        // charge
                        // patElectron_inCrack
                        //?missing inner hits;conversion veto;tight charge not avalible on ntuple
                    }// end stage 4
                
                }// end stage 3
                  
            }// end stage 2
      
        }// end stage 1
    
        TLorentzVector electron;
        electron.SetPtEtaPhiE(patElectron_pt.At(j), patElectron_eta.At(j),
                              patElectron_phi.At(j), patElectron_energy.At(j));
        SelectedElectrons.push_back(electron);
        SelectedElectronsIndex.push_back(j);
    }
}/*}}}*/

void objectTSelector::SelectTaus(vector<TLorentzVector> &SelectedTaus,  vector<Int_t> &SelectedTausIndex,const Int_t TauWP, const vector<TLorentzVector> LeptonsMVAL) {
  // this is tau ID in ttH
  // 1:loose;2:fakeble;3:tight
  for (UInt_t j = 0; j < Tau_pt.GetSize(); ++j) {/*{{{*/
    if (!(Tau_pt.At(j) > 20))
      continue;
    if (!(Tau_eta.At(j) < 2.3 && Tau_eta.At(j) > -2.3))
      continue;
    //       if(!(Tau_leadChargedCandDz_pv.At(j)<0.2)) continue;
    if (!(Tau_packedLeadTauCand_dz.At(j) < 0.2))
      continue; // missing dz
    //?use which dz still need more thinking
    if (!(Tau_decayModeFindingNewDMs.At(j) == 1))
      continue;
    //???not sure why all taus is 1? if so no point in this requirement. //?not
    // sure, is seem all are 1;
    if (TauWP == 2 || TauWP == 3) {
       if( Tau_decayMode.At(j) == 5 || Tau_decayMode.At(j) == 6)      continue;} // for decay mode
    if (TauWP == 1) {
      if (!(Tau_byVVLooseDeepTau2017v2p1VSjet.At(j) > 0.5))
        continue;
    }
    if (TauWP == 2) {
      if (!(Tau_byVVLooseDeepTau2017v2p1VSjet.At(j) > 0.5 &&
            Tau_byVLooseDeepTau2017v2p1VSmu.At(j) > 0.5 &&
            Tau_byVVVLooseDeepTau2017v2p1VSe.At(j) > 0.5))
        continue;
    }
    if (TauWP == 3) { // channel specific in ttH. use the tight from 1t 1l
      if (!(Tau_byVLooseDeepTau2017v2p1VSmu.At(j) > 0.5 &&
            Tau_byVVVLooseDeepTau2017v2p1VSe.At(j) > 0.5 &&
            Tau_byMediumDeepTau2017v2p1VSjet.At(j) > 0.5))
        continue;
    }
    //overlap removal
    Double_t minDeltaR_lep;
    minDeltaR_lep = deltRmin(Tau_eta.At(j), Tau_phi.At(j), LeptonsMVAL);
    if( !(minDeltaR_lep >= 0.3 )) continue;

    //?need err handling
    TLorentzVector tau;
    tau.SetPtEtaPhiE(Tau_pt.At(j), Tau_eta.At(j), Tau_phi.At(j),
                     Tau_energy.At(j));
    SelectedTaus.push_back(tau);
    SelectedTausIndex.push_back(j);
  }
}/*}}}*/

void objectTSelector::SelectJets(const Int_t jetType,const  bool deepJet, vector<TLorentzVector> &SelectedJets,
                vector<Double_t> &SelectedJetsBTags, vector<Int_t> &SelectedJetsIndex , const Int_t SysJes, const Int_t SysJer, const vector<TLorentzVector> LeptonsMVAF, const vector<TLorentzVector> SelectedTausL  /*, bool &deltaPhiJetMet*/) {
  // this is for 2016data
  // jetType=0  -> usual jets; we use loose ID
  // here.https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2016
  // jetType=11 -> b-jets L
  // jetType=12 -> b-jets M
  // jetType=13 -> b-jets T
  // jetType=2  -> forward jets
  // MinDeltaPhiJetMet = 99.0;
  Double_t MostForwardJetEta =-99;
  Double_t MostForwardJetPt = -99;
  Double_t MaxMostForwardJetEta = -99; /*{{{*/
  for (UInt_t j = 0; j < Jet_pt.GetSize(); ++j) {
    Double_t jetpt = 0.;
    if (SysJes == 0 && SysJer == 0) {
      jetpt = Jet_Uncorr_pt.At(j) * Jet_JesSF.At(j) * Jet_JerSF.At(j);
    }
    if (SysJes == 1 && SysJer == 0) {
      jetpt = Jet_Uncorr_pt.At(j) * Jet_JesSFup.At(j) * Jet_JerSF.At(j);
    }
    if (SysJes == 2 && SysJer == 0) {
      jetpt = Jet_Uncorr_pt.At(j) * Jet_JesSFdown.At(j) * Jet_JerSF.At(j);
    }
    if (SysJes == 0 && SysJer == 1) {
      jetpt = Jet_Uncorr_pt.At(j) * Jet_JesSF.At(j) * Jet_JerSFup.At(j);
    }
    if (SysJes == 0 && SysJer == 2) {
      jetpt = Jet_Uncorr_pt.At(j) * Jet_JesSF.At(j) * Jet_JerSFdown.At(j);
    }
    //    if(fabs(Jet_eta.At(j))>2.65&&fabs(Jet_eta.At(j))<3.139&&jetpt>50)
    // continue;
    //    ?what does this do?
    if (!(jetpt > 25))
      continue;
    Double_t NHF = Jet_neutralHadEnergyFraction.At(j);
    Double_t NEMF = Jet_neutralEmEnergyFraction.At(j);
    Double_t CHF = Jet_chargedHadronEnergyFraction.At(j);
    Double_t MUF = Jet_muonEnergyFraction.At(j);
    Double_t CEMF = Jet_chargedEmEnergyFraction.At(j);
    Double_t NumConst = Jet_numberOfConstituents.At(j);
    Double_t NumNeutralParticles =
        Jet_numberOfConstituents.At(j) - Jet_chargedMultiplicity.At(j);
    Double_t CHM = Jet_chargedMultiplicity.At(j);
    if (!(fabs(Jet_eta.At(j)) < 5.0))
      continue;
    // it seems that b jet also have to meet below requirements?
    // yes
    if (fabs(Jet_eta.At(j)) < 2.4) {
      if (!(NHF < 0.99))
        continue;
      if (!(NEMF < 0.99))
        continue;
      if (!(NumConst > 1))
        continue;
      //        if(!(MUF<0.8)) continue;
      if (!(CHF > 0))
        continue;
      if (!(CHM > 0))
        continue;
      if (!(CEMF < 0.99))
        continue;
    } else if (fabs(Jet_eta.At(j)) > 2.4 && fabs(Jet_eta.At(j)) < 2.7) {
      if (!(NHF < 0.99))
        continue;
      if (!(NEMF < 0.99))
        continue;
      if (!(NumConst > 1))
        continue;
      //   if(!(MUF<0.8)) continue;
    } else if (fabs(Jet_eta.At(j)) > 2.7 && fabs(Jet_eta.At(j)) < 3.0) {
      if (!(NEMF > 0.01))
        continue;
      if (!(NHF < 0.98))
        continue;
      if (!(NumNeutralParticles > 2))
        continue;
    } else if (fabs(Jet_eta.At(j)) > 3.0) {
      if (!(NEMF < 0.90))
        continue;
      if (!(NumNeutralParticles > 10))
        continue;
    }

    if (deepJet) {//https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
      if (jetType == 11) {
        if (!(Jet_pfDeepFlavourBJetTags.At(j) > 0.0614))
          continue;
      }
      if (jetType == 12) {
        if (!(Jet_pfDeepFlavourBJetTags.At(j) > 0.3093))
          continue;
      }
      if (jetType == 13) {
        if (!(Jet_pfDeepFlavourBJetTags.At(j) > 0.7221))
          continue;
      }
    } else {
      if (jetType == 11) {
        if (!(Jet_pfDeepCSVBJetTags.At(j) > 0.2217))
          continue;
      }
      if (jetType == 12) {
        if (!(Jet_pfDeepCSVBJetTags.At(j) > 0.6321))
          continue;
      }
      if (jetType == 13) {
        if (!(Jet_pfDeepCSVBJetTags.At(j) > 0.8953))
          continue;
      }
    }
    // find mostforwardjeteta
    if (jetType == 0) { // normal jet
      if (fabs(Jet_eta.At(j)) > MaxMostForwardJetEta) {
        MaxMostForwardJetEta = fabs(Jet_eta.At(j));
        MostForwardJetEta = Jet_eta.At(j);
        MostForwardJetPt = jetpt;//a branch in new tree
      } // MostForwardJetEta branch in new tree and SB.
      if (!(fabs(Jet_eta.At(j)) < 2.4))
        continue;
    }
    if (jetType == 2) { // forwardjet
      if (!(fabs(Jet_eta.At(j)) >= 2.4 && fabs(Jet_eta.At(j)) <= 5))
        continue;
      if (!(jetpt > 25))
        continue;
      if (fabs(Jet_eta.At(j)) >= 2.7 && fabs(Jet_eta.At(j)) <= 3.0) {
        if (!(jetpt > 60.0))
          continue;
      }
    }
    // if (DeltaPhi(Jet_phi.At(j), Met_type1PF_phi_) < MinDeltaPhiJetMet)
      // MinDeltaPhiJetMet = DeltaPhi( Jet_phi.At(j),   Met_type1PF_phi_); // MinDeltaPhiJetMe a branch in newtree and SB
      //
      // overlap removal
    Double_t deltaR = 0;
    Double_t minDeltaR = 100;
    for (UInt_t lep = 0; lep < LeptonsMVAF.size(); lep++){
        deltaR =  DeltaR( LeptonsMVAF[lep].Eta(), Jet_eta.At(j), LeptonsMVAF[lep].Phi(), Jet_phi.At(j));
        if ( deltaR < minDeltaR ) minDeltaR = deltaR ;//The continue statement provides a convenient way to jump to the end of the loop body for the current iteration.
    }
    if ( !( minDeltaR >= 0.4 ) ) continue;
    Double_t deltaR_tau =0;
    Double_t minDeltaR_tau = 100;
    for ( UInt_t tau = 0; tau < SelectedTausL.size(); tau++){
        deltaR_tau =  DeltaR( SelectedTausL[tau].Eta(), Jet_eta.At(j), SelectedTausL[tau].Phi(), Jet_phi.At(j));
        if ( deltaR < minDeltaR_tau ) minDeltaR_tau = deltaR_tau;
    }
    if ( !(minDeltaR_tau >= 0.4)) continue;

    //jet jet removal
    // Double_t deltaR_jet = 0;
    // Double_t minDeltaR_jet = 100;
    // for (UInt_t k = j+1; k < Jet_pt_->size(); ++k) {
        // deltaR_jet = DeltaR( Jet_eta.At(k), Jet_eta.At(j), Jet_phi.At(k), Jet_phi.At(j));
        // if ( deltaR_jet < minDeltaR_jet  ) minDeltaR_jet = deltaR_jet;
    // }
    // if ( !(minDeltaR_jet >= 0.4 )) continue;

    Double_t SF = jetpt / Jet_pt.At(j);
    TLorentzVector jet_prov;
    jet_prov.SetPtEtaPhiM(Jet_pt.At(j), Jet_eta.At(j), Jet_phi.At(j),
                          Jet_mass.At(j));
    TLorentzVector jet;
    jet.SetPxPyPzE(SF * jet_prov.Px(), SF * jet_prov.Py(), SF * jet_prov.Pz(),
                   SF * jet_prov.E());
    //?is this  step necessary?
    //???why do this?
    SelectedJets.push_back(jet);
    SelectedJetsIndex.push_back(j);
    if (deepJet) {
      SelectedJetsBTags.push_back(Jet_pfDeepFlavourBJetTags.At(j));
    } else {
      SelectedJetsBTags.push_back(Jet_pfDeepCSVBJetTags.At(j));
    }
  }
  //jetjet overlap removal
    // Double_t deltaR_jet = 0;
    // for ( UInt_t jet = 0; jet < SelectedJets.size(); jet++){
        // deltaR_jet = 10;
        // for (UInt_t k = jet+1; k < SelectedJets.size(); ++k) {
            // deltaR_jet = DeltaR( SelectedJets[k].Eta(), SelectedJets[jet].Eta(), SelectedJets[k].Phi(), SelectedJets[jet].Phi() );
            // if ( deltaR_jet < 0.4){
                // if ( SelectedJets[jet].Pt() > SelectedJets[k].Pt()) SelectedJets.erase( SelectedJets.begin()+k);
                // else  SelectedJets.erase( SelectedJets.begin()+jet);
            // }
        // }
    // }

} /*}}}*/

void objectTSelector::SelectTops(vector<TLorentzVector> &SelectedTops) {
  for (UInt_t j = 0; j < TopTagger_type.GetSize(); ++j) {
    if (!(TopTagger_type.At(j) == 3))
      continue; // resolved
    //        if(!(TopTagger_discriminator.At(j)>0.6)) continue;
    //        ??not sure of the effect of discriminator
    TLorentzVector jet1;
    jet1.SetPtEtaPhiM(Jet_pt.At(TopTagger_jet1Idx.At(j)),
                      Jet_eta.At(TopTagger_jet1Idx.At(j)), Jet_phi.At(j),
                      Jet_mass.At(TopTagger_jet1Idx.At(j)));
    TLorentzVector jet2;
    jet2.SetPtEtaPhiM(Jet_pt.At(TopTagger_jet2Idx.At(j)),
                      Jet_eta.At(TopTagger_jet2Idx.At(j)), Jet_phi.At(j),
                      Jet_mass.At(TopTagger_jet2Idx.At(j)));
    TLorentzVector jet3;
    jet3.SetPtEtaPhiM(Jet_pt.At(TopTagger_jet3Idx.At(j)),
                      Jet_eta.At(TopTagger_jet3Idx.At(j)), Jet_phi.At(j),
                      Jet_mass.At(TopTagger_jet3Idx.At(j)));

    /*        Double_t top_pt =
    Jet_pt.At(TopTagger_jet1Idx.At(j))+Jet_pt.At(TopTagger_jet2Idx.At(j))+Jet_pt.At(TopTagger_jet3Idx.At(j));//this
    top_pt calculation is wrong
    //         TopPtMin =
    (SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).Pt();//refresh in the loop
           // top_eta and phi need modification
            Double_t top_eta =
    Jet_eta.At(TopTagger_jet1Idx.At(j))+Jet_eta.At(TopTagger_jet2Idx.At(j))+Jet_eta.At(TopTagger_jet3Idx.At(j));
            Double_t top_phi =
    Jet_phi.At(TopTagger_jet1Idx.At(j))+Jet_phi.At(TopTagger_jet2Idx.At(j))+Jet_phi.At(TopTagger_jet3Idx.At(j));
            Double_t top_m =
    Jet_mass.At(TopTagger_jet1Idx.At(j))+Jet_mass.At(TopTagger_jet2Idx.At(j))+Jet_mass.At(TopTagger_jet3Idx.At(j));*/
    //        TLorentzVector top;
    // top.SetPtEtaPhiM(top_pt,top_eta,top_phi,top_m);
    TLorentzVector top;
    top = jet1 + jet2 + jet3;
    SelectedTops.push_back(top);
  }
}

void objectTSelector::MetCorrection(Int_t SysJes, Int_t SysJer, Double_t &MET) { /*{{{*/
  Double_t METx =
      (*Met_type1PF_pt) * TMath::Cos(*Met_type1PF_phi); // in tree branch.
  Double_t METy = (*Met_type1PF_pt) * TMath::Sin(*Met_type1PF_phi);
  for (UInt_t j = 0; j < Jet_pt.GetSize(); ++j) {
    if (!(Jet_Uncorr_pt.At(j) > 15))
      continue;
    Double_t jetpt = 0.;
    //?the difference of Jet_pt and Jet_Uncorr_pt?
    if (SysJes == 0 && SysJer == 0) {
      jetpt = Jet_Uncorr_pt.At(j) * Jet_JesSF.At(j) * Jet_JerSF.At(j);
    }
    if (SysJes == 1 && SysJer == 0) {
      jetpt = Jet_Uncorr_pt.At(j) * Jet_JesSFup.At(j) * Jet_JerSF.At(j);
    }
    if (SysJes == 2 && SysJer == 0) {
      jetpt = Jet_Uncorr_pt.At(j) * Jet_JesSFdown.At(j) * Jet_JerSF.At(j);
    }
    if (SysJes == 0 && SysJer == 1) {
      jetpt = Jet_Uncorr_pt.At(j) * Jet_JesSF.At(j) * Jet_JerSFup.At(j);
    }
    if (SysJes == 0 && SysJer == 2) {
      jetpt = Jet_Uncorr_pt.At(j) * Jet_JesSF.At(j) * Jet_JerSFdown.At(j);
    }
    METx = METx + Jet_Uncorr_pt.At(j) * Jet_JesSF.At(j) *
                      TMath::Cos(Jet_phi.At(j)) -
           jetpt * TMath::Cos(Jet_phi.At(j));
    METy = METy + Jet_Uncorr_pt.At(j) * Jet_JesSF.At(j) *
                      TMath::Sin(Jet_phi.At(j)) -
           jetpt * TMath::Sin(Jet_phi.At(j));
    //??
  }
  MET = sqrt(METx * METx + METy * METy);
} /*}}}*/

void objectTSelector::selectGenTaus( vector<TLorentzVector> &genTaus ){
    for (UInt_t j = 0; j < Gen_pt.GetSize(); ++j) {
        if(!(abs(Gen_motherpdg_id.At(j))==24 && abs(Gen_pdg_id.At(j))==15)) continue;//tau:15; top:6;W:
        TLorentzVector gentau;
        gentau.SetPtEtaPhiE(Gen_pt.At(j), Gen_eta.At(j), Gen_phi.At(j), Gen_energy.At(j));
        genTaus.push_back(gentau);
    }
}
void objectTSelector::selectGenEles( vector<TLorentzVector> &genEles ){
    for (UInt_t j = 0; j < Gen_pt.GetSize(); ++j) {
        if(!(abs(Gen_motherpdg_id.At(j))==24 && abs(Gen_pdg_id.At(j))==11)) continue;//tau:15; ele:11;
        TLorentzVector genele;
        genele.SetPtEtaPhiE(Gen_pt.At(j), Gen_eta.At(j), Gen_phi.At(j), Gen_energy.At(j));
        genEles.push_back(genele);
    }
}
void objectTSelector::selectGenMuons( vector<TLorentzVector> &genMuons ){
    for (UInt_t j = 0; j < Gen_pt.GetSize(); ++j) {
        if(!(abs(Gen_motherpdg_id.At(j))==24  && abs(Gen_pdg_id.At(j))==13)) continue;//tau:15; top:6;W:;muon:13
        TLorentzVector genmuon;
        genmuon.SetPtEtaPhiE(Gen_pt.At(j), Gen_eta.At(j), Gen_phi.At(j), Gen_energy.At(j));
        genMuons.push_back(genmuon);
    }
}

