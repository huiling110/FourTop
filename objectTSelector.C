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


double DeltaR(double eta1, double eta2, double phi1, double phi2) {
  double deltaPhi = TMath::Abs(phi1 - phi2);
  double deltaEta = eta1 - eta2;
  if (deltaPhi > TMath::Pi())
    deltaPhi = TMath::TwoPi() - deltaPhi;
  return TMath::Sqrt(deltaEta * deltaEta + deltaPhi * deltaPhi);
}


double deltRmin(const double eta1, const double phi1, const vector<TLorentzVector> LeptonsMVAF){
    double deltaR = 0;
    double minDeltaR = 100;
    for (UInt_t lep = 0; lep < LeptonsMVAF.size(); lep++){
        deltaR =  DeltaR( LeptonsMVAF[lep].Eta(), eta1, LeptonsMVAF[lep].Phi(), phi1);
        if ( deltaR < minDeltaR ) minDeltaR = deltaR ;//The continue statement provides a convenient way to jump to the end of the loop body for the current iteration.
    }
    return minDeltaR; 
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
    
   TString  outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/test_objectSelction/";
   TString outFileName = "TTTT.root";
   outputfile = new TFile( outputDir+outFileName, "RECREATE");
   tree = new TTree( "tree", "tree after object selection");

   tree->Branch( "muonsL", &muonsL); 
   tree->Branch( "muonsL_index", &muonsL_index);
   tree->Branch( "muonsF", &muonsF );
   tree->Branch( "muonsF_index", &muonsF_index );
   tree->Branch( "muonsT", &muonsT );
   tree->Branch( "eleMVAL", &eleMVAL );
   tree->Branch( "eleMVAF", &eleMVAF );
   tree->Branch( "eleMVAT", &eleMVAT );
   tree->Branch( "eleMVAL_index", &eleMVAL_index );
   tree->Branch( "eleMVAF_index", &eleMVAF_index );
   tree->Branch( "eleMVAT_index", &eleMVAT_index );
   tree->Branch( "tausL", &tausL );
   tree->Branch( "tausF", &tausF );
   tree->Branch( "tausT", &tausT );
   tree->Branch( "tausL_index", &tausL_index );
   tree->Branch( "tausF_index", &tausF_index );
   tree->Branch( "tausT_index", &tausT_index );
   // tree->Branch( "", & );
   // tree->Branch( "", & );
   // tree->Branch( "", & );
   // tree->Branch( "", & );
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
    muonsF.clear(); muonsF_index.clear();
    muonsT.clear(); muonsT_index.clear();
    eleMVAL.clear(); eleMVAL_index.clear();
    eleMVAF.clear(); eleMVAF_index.clear();
    eleMVAT.clear(); eleMVAT_index.clear();
    tausL.clear(); tausL_index.clear();
    tausF.clear(); tausF_index.clear();
    tausT.clear(); tausT_index.clear();
    // .clear(); _index.clear();
    // .clear(); _index.clear();

	SelectMuons( muonsL, muonsL_index, 0 ,4);
    SelectMuons( muonsF, muonsF_index, 1, 4);
    SelectMuons( muonsT, muonsT_index, 2, 4);

    SelectElectronsMVA(eleMVAL, eleMVAL_index, 0, 4 );
    SelectElectronsMVA( eleMVAF, eleMVAF_index, 1, 4);
    SelectElectronsMVA( eleMVAT, eleMVAT_index, 2, 4);

    SelectTaus( tausL, tausL_index, 1, eleMVAL);
    SelectTaus( tausF, tausF_index, 2, eleMVAL);
    SelectTaus( tausT, tausT_index, 3 , eleMVAL);

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



void objectTSelector::SelectElectronsMVA(vector<TLorentzVector> &SelectedElectrons,vector<int> &SelectedElectronsIndex, int type, int stage) {
  // 0 for VLoose; 1 for VLooseFO(fakeble object); 2 for tight
  // 2016 - MVANoIso94XV2, from SUSY
  for (UInt_t j = 0; j < patElectron_pt.GetSize(); ++j) { // banch in tree
                                                         // line945
    if (stage == 1 || stage == 2 || stage == 3 || stage == 4) {

      double pt = patElectron_pt.At(j);
      double eta = patElectron_eta.At(j);
      double MVA_value = patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Values.At(j);
      double raw_MVA_value = 0.5 * log ( (1 + MVA_value)/(1 - MVA_value) );
      if (!(fabs(eta) < 2.5))
      continue;
    
      if (stage == 2 || stage == 3 || stage  == 4) {

	//id
    if (fabs(eta) < 0.8) {
      if (type == 2) {
	if(!(pt > 10)) continue;
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
    double I1 = 0.4, I2 = 0, I3 = 0;
    if (type == 0 || type == 1) {
      I1 = 0.4;
      I2 = 0;
      I3 = 0;
    } // looseWP from ss of TTTT}
    // if(type == 2) {I1 = 0.12; I2 = 0.80; I3 = 7.2;    }//TightWP of SS
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
}

void objectTSelector::SelectTaus(vector<TLorentzVector> &SelectedTaus,  vector<int> &SelectedTausIndex,const Int_t TauWP, const vector<TLorentzVector> LeptonsMVAL) {
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
    double minDeltaR_lep;
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

void objectTSelector::SelectJets(const int jetType,const  bool deepJet, vector<TLorentzVector> &SelectedJets,
                vector<double> &SelectedJetsBTags, vector<int> &SelectedJetsIndex , const int SysJes, const int SysJer, const vector<TLorentzVector> LeptonsMVAF, const vector<TLorentzVector> SelectedTausL  /*, bool &deltaPhiJetMet*/) {
  // this is for 2016data
  // jetType=0  -> usual jets; we use loose ID
  // here.https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2016
  // jetType=11 -> b-jets L
  // jetType=12 -> b-jets M
  // jetType=13 -> b-jets T
  // jetType=2  -> forward jets
  // MinDeltaPhiJetMet = 99.0;
  double MostForwardJetEta =-99;
  double MostForwardJetPt = -99;
  double MaxMostForwardJetEta = -99; /*{{{*/
  for (UInt_t j = 0; j < Jet_pt.GetSize(); ++j) {
    double jetpt = 0.;
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
    double NHF = Jet_neutralHadEnergyFraction.At(j);
    double NEMF = Jet_neutralEmEnergyFraction.At(j);
    double CHF = Jet_chargedHadronEnergyFraction.At(j);
    double MUF = Jet_muonEnergyFraction.At(j);
    double CEMF = Jet_chargedEmEnergyFraction.At(j);
    double NumConst = Jet_numberOfConstituents.At(j);
    double NumNeutralParticles =
        Jet_numberOfConstituents.At(j) - Jet_chargedMultiplicity.At(j);
    double CHM = Jet_chargedMultiplicity.At(j);
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
    double deltaR = 0;
    double minDeltaR = 100;
    for (UInt_t lep = 0; lep < LeptonsMVAF.size(); lep++){
        deltaR =  DeltaR( LeptonsMVAF[lep].Eta(), Jet_eta.At(j), LeptonsMVAF[lep].Phi(), Jet_phi.At(j));
        if ( deltaR < minDeltaR ) minDeltaR = deltaR ;//The continue statement provides a convenient way to jump to the end of the loop body for the current iteration.
    }
    if ( !( minDeltaR >= 0.4 ) ) continue;
    double deltaR_tau =0;
    double minDeltaR_tau = 100;
    for ( UInt_t tau = 0; tau < SelectedTausL.size(); tau++){
        deltaR_tau =  DeltaR( SelectedTausL[tau].Eta(), Jet_eta.At(j), SelectedTausL[tau].Phi(), Jet_phi.At(j));
        if ( deltaR < minDeltaR_tau ) minDeltaR_tau = deltaR_tau;
    }
    if ( !(minDeltaR_tau >= 0.4)) continue;

    //jet jet removal
    // double deltaR_jet = 0;
    // double minDeltaR_jet = 100;
    // for (UInt_t k = j+1; k < Jet_pt_->size(); ++k) {
        // deltaR_jet = DeltaR( Jet_eta.At(k), Jet_eta.At(j), Jet_phi.At(k), Jet_phi.At(j));
        // if ( deltaR_jet < minDeltaR_jet  ) minDeltaR_jet = deltaR_jet;
    // }
    // if ( !(minDeltaR_jet >= 0.4 )) continue;

    double SF = jetpt / Jet_pt.At(j);
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
    // double deltaR_jet = 0;
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

    /*        double top_pt =
    Jet_pt.At(TopTagger_jet1Idx.At(j))+Jet_pt.At(TopTagger_jet2Idx.At(j))+Jet_pt.At(TopTagger_jet3Idx.At(j));//this
    top_pt calculation is wrong
    //         TopPtMin =
    (SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).Pt();//refresh in the loop
           // top_eta and phi need modification
            double top_eta =
    Jet_eta.At(TopTagger_jet1Idx.At(j))+Jet_eta.At(TopTagger_jet2Idx.At(j))+Jet_eta.At(TopTagger_jet3Idx.At(j));
            double top_phi =
    Jet_phi.At(TopTagger_jet1Idx.At(j))+Jet_phi.At(TopTagger_jet2Idx.At(j))+Jet_phi.At(TopTagger_jet3Idx.At(j));
            double top_m =
    Jet_mass.At(TopTagger_jet1Idx.At(j))+Jet_mass.At(TopTagger_jet2Idx.At(j))+Jet_mass.At(TopTagger_jet3Idx.At(j));*/
    //        TLorentzVector top;
    // top.SetPtEtaPhiM(top_pt,top_eta,top_phi,top_m);
    TLorentzVector top;
    top = jet1 + jet2 + jet3;
    SelectedTops.push_back(top);
  }
}




