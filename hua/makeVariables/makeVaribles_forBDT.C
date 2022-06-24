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
#include <TMatrixDSym.h>
#include <TVectorD.h>

#include "weightCal.h"
// #include "../../TauPOG/TauIDSFs/src/TauIDSFTool.cc"
//???need change
// #include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
//???not sure how to use class from cmssw








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
   std::cout<<outputfile->GetName()<<"\n";

   newtree = new TTree( "newtree", "tree for BDT");

   makeBranchForTree( newtree, wantFilterHLTBranches);
    // initializeBReader();
    initializeInputFiles( era );
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
    InitializeBranches();

    if ( wantFilterHLTBranches ){
        Flag_goodVertices = *Flag_goodVertices_;
        Flag_globalSuperTightHalo2016Filter = *Flag_globalSuperTightHalo2016Filter_;
        Flag_HBHENoiseFilter = *Flag_HBHENoiseFilter_;
        Flag_HBHENoiseIsoFilter = *Flag_HBHENoiseIsoFilter_;
        Flag_EcalDeadCellTriggerPrimitiveFilter = *Flag_EcalDeadCellTriggerPrimitiveFilter_;
        Flag_BadPFMuonFilter = *Flag_BadPFMuonFilter_;
        Flag_eeBadScFilter = *Flag_eeBadScFilter_;
        HLT_PFHT450_SixJet40_BTagCSV_p056 = *HLT_PFHT450_SixJet40_BTagCSV_p056_;
        HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_;
        HLT_PFJet450 = *HLT_PFJet450_;
    }

	if ( HLTSelection ){
		if ( fProcessed==1 ) std::cout<<"doing HTL selection\n";
        if (era.CompareTo("2016preVFP")==0 || era.CompareTo("2016postVFP")==0) {
            if( !( *HLT_PFHT450_SixJet40_BTagCSV_p056_==1 || *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_==1 || *HLT_PFJet450_==1  )  ) return kFALSE;
        }
	}

	fPassingHLT++;





    Met_pt_ = *Met_pt;
    Met_phi_ = *Met_phi;
              

    muonsL_number = muonsL.GetSize();
    muonsF_number = muonsF.GetSize();
    muonsT_number = muonsT.GetSize();
    if (muonsT_number > 0) {
        muonsT_1pt = muonsT[0].Pt();
        muonsT_1eta = fabs(muonsT[0].Eta());
        muonsT_1phi = fabs(muonsT[0].Phi());
    }
    if (muonsT_number > 1) {
        muonsT_2pt = muonsT[1].Pt();
        muonsT_2eta = fabs(muonsT[1].Eta());
        muonsT_2phi = fabs(muonsT[1].Phi());
    }
    if (muonsT_number > 2) {
        muonsT_3pt = muonsT[2].Pt();
        muonsT_3eta = fabs(muonsT[2].Eta());
        muonsT_3phi = fabs(muonsT[2].Phi());
    }


      elesMVAL_number = eleMVAL.GetSize();
      elesMVAF_number = eleMVAF.GetSize();
      elesMVAT_number = eleMVAT.GetSize();
      if (elesMVAF_number > 0) {
        elesMVAF_1pt = eleMVAF[0].Pt();
      }
      //???add more electron variables


      leptonsMVAT_number = leptonsMVAT.GetSize();
      leptonsMVAF_number = leptonsMVAF.GetSize();
      leptonsMVAL_number = leptonsMVAL.GetSize();
      leptonsMVAT_transMass = TransMassCal(leptonsMVAT);
      leptonsMVAF_transMass = TransMassCal(leptonsMVAF);
      leptonsMVAL_transMass = TransMassCal(leptonsMVAL);
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


      if (leptonsMVAT_number > 0) {
        leptonsMVAT_1pt = leptonsMVAT[0].Pt();
        leptonsMVAT_1eta = fabs(leptonsMVAT[0].Eta());
        leptonsMVAT_1phi = fabs(leptonsMVAT[0].Phi());
      
      }
      if (leptonsMVAT_number > 1) {
        leptonsMVAT_2pt = leptonsMVAT[1].Pt();
        leptonsMVAT_2eta = fabs(leptonsMVAT[1].Eta());
        leptonsMVAT_2phi = fabs(leptonsMVAT[1].Phi());
        
      }
      if (leptonsMVAT_number > 2) {
        leptonsMVAT_3pt = leptonsMVAT[2].Pt();
        leptonsMVAT_3eta = fabs(leptonsMVAT[2].Eta());
        leptonsMVAT_3phi = fabs(leptonsMVAT[2].Phi());
      }

		//tau TES sys
		tausT_number_TESup = tausT_TESup.GetSize();
		tausT_number_TESdown = tausT_TESdown.GetSize();

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

      tausF_leptonsT_transMass = TransMassSysCal(tausF, leptonsMVAT);
      tausL_leptonsT_transMass = TransMassSysCal(tausL, leptonsMVAT);
      tausT_leptonsT_transMass = TransMassSysCal(tausT, leptonsMVAT);
      tausF_leptonsT_invariantMass = InvariantMass2SysCal(tausF, leptonsMVAT);
      tausL_leptonsT_invariantMass = InvariantMass2SysCal(tausL, leptonsMVAT);
      tausT_leptonsT_invariantMass = InvariantMass2SysCal(tausT, leptonsMVAT);
      // tausF_leptonsT_chargeSum = ChargeSum(tausF_index, 1) +  ChargeSum(eleMVAT_index, 0) +   ChargeSum(muonsT_index, 2);
      tausF_leptonsTMVA_minDeltaR = MinDeltaRCal(leptonsMVAT, tausF);
      tausL_leptonsTMVA_minDeltaR = MinDeltaRCal(leptonsMVAT, tausL);
      tausT_leptonsTMVA_minDeltaR = MinDeltaRCal(leptonsMVAT, tausT);

      // sort(tausL.begin(), tausL.end(), comparePt);
      if (tausL_number > 0) {
        tauL_1pt = tausL[0].Pt();
        tauL_1eta = fabs(tausL[0].Eta());
        tauL_1phi = fabs(tausL[0].Phi());
      }
      if (tausL_number > 1) {
        tauL_2pt = tausL[1].Pt();
        tauL_2eta = fabs(tausL[1].Eta());
        tauL_2phi = fabs(tausL[1].Phi());
      }
      if (tausL_number > 2) {
        tauL_3pt = tausL[2].Pt();
        tauL_3eta = fabs(tausL[2].Eta());
        tauL_3phi = fabs(tausL[2].Phi());
      }

	//for jets JEC
      jets_HT_JECup = HTcalculator(jets_JECup);
      jets_HT_JECdown = HTcalculator(jets_JECdown);
      jets_number_JECup = jets_JECup.GetSize();
      jets_number_JECdown = jets_JECdown.GetSize();

      //jets
      jets_number = jets.GetSize();
      jets_MHT =  MHTcalculator(jets); // 900;return the pt sum of,vetctor sum
      jets_HT = HTcalculator(jets);
      jets_invariantMass = InvariantMassCalculator(jets);
      jets_transMass = TransMassCal(jets);
      jets_minDeltaR = MinDeltaRSingleCal(jets);
      jets_centrality = jets_HT / jets_invariantMass;
      jets_bScore = BScoreAllJetsCal( jets_btags );//sum of btags
      jets_bScoreMultiply = bScoreMultiCal( jets_btags );
      jets_average_deltaR = AverageDeltaRCal(jets);
      jets_4largestBscoreSum = bscoreSumOf4largestCal( jets_btags);
      jets_4largestBscoreMulti = bscoreMultiOf4largestCal( jets_btags );
      if (Met_pt_ == 0) {
        jets_HTDividedByMet = 0;
      } else {
        jets_HTDividedByMet = jets_HT / Met_pt_;
      }
      MetDividedByHT = Met_pt_ / jets_HT;
      jets_MHTDividedByMet = jets_MHT / Met_pt_;
      jets_leptonsMVAT_minDeltaR = MinDeltaRCal(jets, leptonsMVAT);
      jets_tausF_minDeltaR = MinDeltaRCal(jets, tausF);

      //
    //aplanarity and sphericity
      SpheriltyAplanarityCal( jets, jets_spherilty, jets_aplanarity ); 



      if (jets_number > 0) {/*{{{*/
        jets_1pt = jets[0].Pt();
        jets_1eta = fabs(jets[0].Eta());
        jets_1phi = fabs(jets[0].Phi());
      }
      if (jets_number > 1) {
        jets_2pt = jets[1].Pt();
        jets_2eta = fabs(jets[1].Eta());
        jets_2phi = fabs(jets[1].Phi());
        jets_leading2invariantMass = (jets[0]+jets[1]).M();
      }
      if (jets_number > 2) {
        jets_3pt = jets[2].Pt();
        jets_3eta = fabs(jets[2].Eta());
        jets_3phi = fabs(jets[2].Phi());
      }
      if (jets_number > 3) {
        jets_4pt = jets[3].Pt();
        jets_4eta = fabs(jets[3].Eta());
        jets_4phi = fabs(jets[3].Phi());
      }
      if (jets_number > 4) {
        jets_5pt = jets[4].Pt();
        jets_5eta = fabs(jets[4].Eta());
        jets_5phi = fabs(jets[4].Phi());
        jets_rationHT_4toRest = rationHT_4toRestCal(jets);
      }
      if (jets_number > 5) {
        jets_6pt = jets[5].Pt();
        jets_6eta = fabs(jets[5].Eta());
        jets_6phi = fabs(jets[5].Phi());
      }
      if (jets_number > 6) {
        jets_7pt = jets[6].Pt();
        jets_7eta = fabs(jets[6].Eta());
        jetL_7phi = fabs(jets[6].Phi());
        //???
      }
      if (jets_number > 7) {
        jets_8pt = jets[7].Pt();
        jets_8eta = fabs(jets[7].Eta());
        jets_8phi = fabs(jets[7].Phi());
      }
      if (jets_number > 8) {
        jets_9pt = jets[8].Pt();
        jets_9eta = fabs(jets[8].Eta());
        jets_9phi = fabs(jets[8].Phi());
      }
      if (jets_number > 9) {
        jets_10pt = jets[9].Pt();
        jets_10eta = fabs(jets[9].Eta());
        jets_10phi = fabs(jets[9].Phi());
      }
      if (jets_number > 10) {
        jets_11pt = jets[10].Pt();
        jets_11eta = fabs(jets[10].Eta());
        jets_11phi = fabs(jets[10].Phi());
      }/*}}}*/
 

      bjetsL_num = bjetsL.GetSize();
      bjetsM_num = bjetsM.GetSize(); //
      bjetsT_num = bjetsT.GetSize();
      bjetsL_HT = HTcalculator(bjetsL);
      bjetsM_HT = HTcalculator(bjetsM);
      bjetsT_HT = HTcalculator(bjetsT);
      bjetsL_MHT =  MHTcalculator(bjetsL); // 900;return the pt sum of,vetctor sum
      bjetsM_MHT =  MHTcalculator(bjetsM); // 900;return the pt sum of,vetctor sum
      bjetsT_MHT =  MHTcalculator(bjetsT); // 900;return the pt sum of,vetctor sum
      bjetsL_invariantMass = InvariantMassCalculator(bjetsL);
      bjetsM_invariantMass = InvariantMassCalculator(bjetsM);
      bjetsT_invariantMass = InvariantMassCalculator(bjetsT);
      bjetsL_transMass = TransMassCal(bjetsL);
      bjetsM_transMass = TransMassCal(bjetsM);
      bjetsT_transMass = TransMassCal(bjetsT);
      bjetsL_minDeltaR = MinDeltaRSingleCal(bjetsL);
      bjetsM_minDeltaR = MinDeltaRSingleCal(bjetsM);
      bjetsT_minDeltaR = MinDeltaRSingleCal(bjetsT);
      bjetsL_leptonsMVAT_minDeltaR = MinDeltaRCal(bjetsL, leptonsMVAT);
      bjetsM_leptonsMVAT_minDeltaR = MinDeltaRCal(bjetsM, leptonsMVAT);
      bjetsT_leptonsMVAT_minDeltaR = MinDeltaRCal(bjetsT, leptonsMVAT);
      bjetsL_tausF_minDeltaR = MinDeltaRCal(bjetsL, tausF);


      // cant use sort //because it is of type TTreeReaderArray
      if (bjetsL_num > 0) {/*{{{*/
        bjetsL_1pt = bjetsL[0].Pt();
        bjetsL_1eta = fabs(bjetsL[0].Eta());
        bjetsL_1phi = fabs(bjetsL[0].Phi());
      }
      if (bjetsL_num > 1) {
        bjetsL_2pt = bjetsL[1].Pt();
        bjetsL_2eta = fabs(bjetsL[1].Eta());
        bjetsL_2phi = fabs(bjetsL[1].Phi());
      }
      if (bjetsL_num > 2) {
        bjetsL_3pt = bjetsL[2].Pt();
        bjetsL_3eta = fabs(bjetsL[2].Eta());
        bjetsL_3phi = fabs(bjetsL[2].Phi());
      }
      if (bjetsL_num > 3) {
        bjetsL_4pt = bjetsL[3].Pt();
        bjetsL_4eta = fabs(bjetsL[3].Eta());
        bjetsL_4phi = fabs(bjetsL[3].Phi());
      }

      if (bjetsM_num > 0) {
        bjetsM_1pt = bjetsM[0].Pt();
        bjetsM_1eta = fabs(bjetsM[0].Eta());
        bjetsM_1phi = fabs(bjetsM[0].Phi());
      }
      if (bjetsM_num > 1) {
        bjetsM_2pt = bjetsM[1].Pt();
        bjetsM_2eta = fabs(bjetsM[1].Eta());
        bjetsM_2phi = fabs(bjetsM[1].Phi());
      }
      if (bjetsM_num > 2) {
        bjetsM_3pt = bjetsM[2].Pt();
        bjetsM_3eta = fabs(bjetsM[2].Eta());
        bjetsM_3phi = fabs(bjetsM[2].Phi());
      }
      if (bjetsM_num > 3) {
        bjetsM_4pt = bjetsM[3].Pt();
        bjetsM_4eta = fabs(bjetsM[3].Eta());
        bjetsM_4phi = fabs(bjetsM[3].Phi());
      }

      if (bjetsT_num > 0) {
        bjetsT_1pt = bjetsT[0].Pt();
        bjetsT_1eta = fabs(bjetsT[0].Eta());
        bjetsT_1phi = fabs(bjetsT[0].Phi());
      }
      if (bjetsT_num > 1) {
        bjetsT_2pt = bjetsT[1].Pt();
        bjetsT_2eta = fabs(bjetsT[1].Eta());
        bjetsT_2phi = fabs(bjetsT[1].Phi());
      }
      if (bjetsT_num > 2) {
        bjetsT_3pt = bjetsT[2].Pt();
        bjetsT_3eta = fabs(bjetsT[2].Eta());
        bjetsT_3phi = fabs(bjetsT[2].Phi());
      }
      if (bjetsT_num > 3) {
        bjetsT_4pt = bjetsT[3].Pt();
        bjetsT_4eta = fabs(bjetsT[3].Eta());
        bjetsT_4phi = fabs(bjetsT[3].Phi());
      }/*}}}*/

      nonbjetsL_num = nonbjetsL.GetSize();
      nonbjetsM_num = nonbjetsM.GetSize();
      nonbjetsT_num = nonbjetsT.GetSize();
      if (nonbjetsL_num > 0) {/*{{{*/
        nonbjetsL_1pt = nonbjetsL[0].Pt();
        nonbjetsL_1eta = fabs(nonbjetsL[0].Eta());
        nonbjetsL_1phi = fabs(nonbjetsL[0].Phi());
      }
      if (nonbjetsL_num > 1) {
        nonbjetsL_2pt = nonbjetsL[1].Pt();
        nonbjetsL_2eta = fabs(nonbjetsL[1].Eta());
        nonbjetsL_2phi = fabs(nonbjetsL[1].Phi());
      }
      if (nonbjetsL_num > 2) {
        nonbjetsL_3pt = nonbjetsL[2].Pt();
        nonbjetsL_3eta = fabs(nonbjetsL[2].Eta());
        nonbjetsL_3phi = fabs(nonbjetsL[2].Phi());
      }
      if (nonbjetsL_num > 3) {
        nonbjetsL_4pt = nonbjetsL[3].Pt();
        nonbjetsL_4eta = fabs(nonbjetsL[3].Eta());
        nonbjetsL_4phi = fabs(nonbjetsL[3].Phi());
      }

      if (nonbjetsM_num > 0) {
        nonbjetsM_1pt = nonbjetsM[0].Pt();
        nonbjetsM_1eta = fabs(nonbjetsM[0].Eta());
        nonbjetsM_1phi = fabs(nonbjetsM[0].Phi());
      }
      if (nonbjetsM_num > 1) {
        nonbjetsM_2pt = nonbjetsM[1].Pt();
        nonbjetsM_2eta = fabs(nonbjetsM[1].Eta());
        nonbjetsM_2phi = fabs(nonbjetsM[1].Phi());
      }
      if (nonbjetsM_num > 2) {
        nonbjetsM_3pt = nonbjetsM[2].Pt();
        nonbjetsM_3eta = fabs(nonbjetsM[2].Eta());
        nonbjetsM_3phi = fabs(nonbjetsM[2].Phi());
      }
      if (nonbjetsM_num > 3) {
        nonbjetsM_4pt = nonbjetsM[3].Pt();
        nonbjetsM_4eta = fabs(nonbjetsM[3].Eta());
        nonbjetsM_4phi = fabs(nonbjetsM[3].Phi());
      }

      if (nonbjetsT_num > 0) {
        nonbjetsT_1pt = nonbjetsT[0].Pt();
        nonbjetsT_1eta = fabs(nonbjetsT[0].Eta());
        nonbjetsT_1phi = fabs(nonbjetsT[0].Phi());
      }
      if (nonbjetsT_num > 1) {
        nonbjetsT_2pt = nonbjetsT[1].Pt();
        nonbjetsT_2eta = fabs(nonbjetsT[1].Eta());
        nonbjetsT_2phi = fabs(nonbjetsT[1].Phi());
      }
      if (nonbjetsT_num > 2) {
        nonbjetsT_3pt = nonbjetsT[2].Pt();
        nonbjetsT_3eta = fabs(nonbjetsT[2].Eta());
        nonbjetsT_3phi = fabs(nonbjetsT[2].Phi());
      }
      if (nonbjetsT_num > 3) {
        nonbjetsT_4pt = nonbjetsT[3].Pt();
        nonbjetsT_4eta = fabs(nonbjetsT[3].Eta());
        nonbjetsT_4phi = fabs(nonbjetsT[3].Phi());
      }/*}}}*/

      forwardJets_num = forwardJets.GetSize();

      toptagger_num = tops_toptagger.GetSize();
      toptagger_MHT =  MHTcalculator(tops_toptagger); // 900;return the pt sum of,vetctor sum
      toptagger_HT = HTcalculator(tops_toptagger);
      toptagger_invariantMass = InvariantMassCalculator(tops_toptagger);
      toptagger_transMass = TransMassCal(tops_toptagger);
      toptagger_minDeltaR_v1 = MinDeltaRSingleCal(tops_toptagger);
      // toptagger_scoreAllTops = TopScoreAllTopsCal(tops_toptagger);
      toptagger_leptonsMVAT_minDeltaR = MinDeltaRCal(tops_toptagger, leptonsMVAT);
      if (toptagger_num > 0) {
        toptagger_1pt = tops_toptagger[0].Pt();
        toptagger_1eta = fabs(tops_toptagger[0].Eta());
        toptagger_1phi = fabs(tops_toptagger[0].Phi());
      }
      if (toptagger_num > 1) {
        toptagger_2pt = tops_toptagger[1].Pt();
        toptagger_2eta = fabs(tops_toptagger[1].Eta());
        toptagger_2phi = fabs(tops_toptagger[1].Phi());
        std::vector<Double_t> MinMaxDeltaRTops;
      }
      if (toptagger_num > 2) {
        toptagger_3pt = tops_toptagger[2].Pt();
        toptagger_3eta = fabs(tops_toptagger[2].Eta());
        toptagger_3phi = fabs(tops_toptagger[2].Phi());
      }


     //weights
     EVENT_prefireWeight = *EVENT_prefireWeight_;
     EVENT_genWeight = *EVENT_genWeight_;
     PUWeight = *PUWeight_;
     PUWeight_do = *PUWeight_Down;
     PUWeight_up = *PUWeight_Up;
    //  Double_t* allBtagSF = evalEventSF( jets, jets_flavour, jets_btags, CSVreader );
    //  btagEfficiency_weight = allBtagSF[0];
    //  btagEfficiency_weight = calBTagSF( );
    HLTefficiency_weight = getHLTweight( jets_HT, jets, TriggerSF, TriggerSFunc ); 
    muonIDSF_weight = calMuonIDSF( muonsT, MuonIDSF, 0, kTRUE );
    muonIDSF_weight_up = calMuonIDSF( muonsT, MuonIDSF, 1, kTRUE );
    muonIDSF_weight_down = calMuonIDSF( muonsT, MuonIDSF, 2, kTRUE );
    // mounTrackerSF_weight = calMuonIDSF( muonsT, muonTrackerSF_hist, 0 );
    //???tracker file has some problems

	// EleIDSF->Print();
    eleMVAT_IDSF_weight = calEleMVA_IDSF( eleMVAT, EleIDSF );
    eleMVAT_IDSF_weight_backup = calMuonIDSF( eleMVAT, EleIDSF, 0, kFALSE );
	eleMVAT_IDSF_weight_up = calMuonIDSF( eleMVAT, EleIDSF, 1, kFALSE );
    eleMVAT_IDSF_weight_down = calMuonIDSF( eleMVAT, EleIDSF, 2, false );

	  // tauT_IDSF_weight = calTau_IDSF( tausT, tausT_genPartFlav, era );//
    tauT_IDSF_weight_new = calTau_IDSF_new( tausT, tausT_decayMode, tausT_genPartFlav, cset.get(), "nom", "nom", "nom" );
	tauT_IDSF_weight_new_vsjetUp = calTau_IDSF_new(tausT, tausT_decayMode, tausT_genPartFlav, cset.get(), "up", "nom", "nom");
	tauT_IDSF_weight_new_vsjetDown = calTau_IDSF_new(tausT, tausT_decayMode, tausT_genPartFlav, cset.get(), "down", "nom", "nom");
    tauT_IDSF_weight_new_vsmuUp = calTau_IDSF_new( tausT, tausT_decayMode, tausT_genPartFlav, cset.get(), "nom", "up", "nom" );
    tauT_IDSF_weight_new_vsmuDown = calTau_IDSF_new( tausT, tausT_decayMode, tausT_genPartFlav, cset.get(), "nom", "down", "nom" );
    tauT_IDSF_weight_new_vseleUp = calTau_IDSF_new( tausT, tausT_decayMode, tausT_genPartFlav, cset.get(), "nom", "nom", "up" );
    tauT_IDSF_weight_new_vseleDown = calTau_IDSF_new( tausT, tausT_decayMode, tausT_genPartFlav, cset.get(), "nom", "nom", "down" );
	//copy weight from

	if (preselection)
    {
    //   if (!(jets_HT > 400))  return kFALSE;
      	if (!(jets_HT>500  && jets_6pt>40))  return kFALSE;
    }
	fPassingPreselection++;

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
   Info("Terminate", "passing HLT events: %lld", fPassingHLT );
   Info("Terminate", "passing preselection: %lld", fPassingPreselection );
   Info("Terminate", "output file here: %s", outputfile->GetName());

}


void makeVaribles_forBDT::initializeInputFiles( const TString era ){
#include "inputFileClass.h"
    //muon ID 
    TFile* input_MuonIDSF = new TFile( MUOSF_files[era], "READ" );
    // input_MuonIDSF = new TFile( MUOSF_files[era], "READ" );
    // input_MuonIDSF->Print();
	MuonIDSF = (TH2D*)input_MuonIDSF->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt")->Clone();
	// TH2D* MuonIDSF = (TH2D*)input_MuonIDSF->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
	MuonIDSF->Print();
	MuonIDSF->SetDirectory(nullptr);
	input_MuonIDSF->Close();
	delete input_MuonIDSF;

	//muon traker
	TFile* muonTracerSF_file = new TFile( muonSF_tracker[era], "READ");
	muonTrackerSF_hist = (TH2D*)muonTracerSF_file->Get("NUM_TrackerMuons_DEN_genTracks");
	muonTrackerSF_hist->Print();
	MuonIDSF->SetDirectory(nullptr);
	muonTracerSF_file->Close();
	delete muonTracerSF_file;
  //muon ISO
  // TFile* muonIsoSF_file = new TFlie( muonSF_iso[era], "READ");
  // muonIsoSF_hist = (TH2D*)muonIsoSF_file->Get()


	//eGamma
	TFile* input_EleIDSF = new TFile( TString(EGammaSF_files[era]), "READ" );
	EleIDSF = (TH2D*)input_EleIDSF->Get("EGamma_SF2D");
	EleIDSF->SetDirectory(nullptr);
	input_EleIDSF->Close();
	delete input_EleIDSF;
	EleIDSF->Print();

	//trigger
	TFile* input_TrigSF = new TFile( TString(TRGSF_files[era]), "READ" );
	// TriggerSF = (TH2D*)input_TrigSF->Get("SF_njetsVsHT_"+era);
	// TriggerSFunc = (TH2D*)input_TrigSF->Get("SF_njetsVsHTerrors_"+era);
	TriggerSF = (TH2D*)input_TrigSF->Get("SF_njetsVsHT_"+ map_era[era]);
	TriggerSFunc = (TH2D*)input_TrigSF->Get("SF_njetsVsHTerrors_"+ map_era[era] );
	TriggerSF->SetDirectory(nullptr);
	TriggerSFunc->SetDirectory(nullptr);
	input_TrigSF->Close();
	delete input_TrigSF;

	//new SF files from 
	#include "../../objectSelection/inputMap.h"
	// TString tauSF_json = "../../../jsonpog-integration/POG/TAU/2016preVFP_UL/tau.json" ;
	TString base = "../../../jsonpog-integration/POG/";
	TString tauSF_json = base  + json_map[era].at(1) ;
	cset = correction::CorrectionSet::from_file(tauSF_json.Data());
	for (auto& corr : *cset) {
        printf("Correction: %s\n", corr.first.c_str());
    }
	// std::string JES_json = "JME/2016preVFP_UL/jet_jerc.json";
	// cset_JES = correction::CorrectionSet::from_file(JES_json);
}

void makeVaribles_forBDT::makeBranchForTree( TTree* newtree, Bool_t wantFilterHLTBranches ){
   if ( wantFilterHLTBranches ){
       newtree->Branch( "Flag_goodVertices", &Flag_goodVertices, "Flag_goodVertices/I");
       newtree->Branch( "Flag_globalSuperTightHalo2016Filter", &Flag_globalSuperTightHalo2016Filter, "Flag_globalSuperTightHalo2016Filter/I");
       newtree->Branch( "Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter, "Flag_HBHENoiseFilter/I");
       newtree->Branch( "Flag_HBHENoiseIsoFilter", &Flag_HBHENoiseIsoFilter, "Flag_HBHENoiseIsoFilter/I");
       newtree->Branch( "Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter, "Flag_EcalDeadCellTriggerPrimitiveFilter/I");
       newtree->Branch( "Flag_BadPFMuonFilter", &Flag_BadPFMuonFilter, "Flag_BadPFMuonFilter/I");
       newtree->Branch( "Flag_eeBadScFilter", &Flag_eeBadScFilter, "Flag_eeBadScFilter/I");

        newtree->Branch( "HLT_PFHT450_SixJet40_BTagCSV_p056", &HLT_PFHT450_SixJet40_BTagCSV_p056, "HLT_PFHT450_SixJet40_BTagCSV_p056/I");
        newtree->Branch( "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056", &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056/I");
       newtree->Branch( "HLT_PFJet450", &HLT_PFJet450, "HLT_PFJet450/I");

   }
   
   newtree->Branch( "EVENT_prefireWeight", &EVENT_prefireWeight, "EVENT_prefireWeight/D");
   newtree->Branch( "EVENT_genWeight", &EVENT_genWeight, "EVENT_genWeight/D");
   newtree->Branch( "PUWeight",  &PUWeight,  "PUWeight/D");
   newtree->Branch( "PUWeight_up",  &PUWeight_up,  "PUWeight_up/D");
   newtree->Branch( "PUWeight_do",  &PUWeight_do,  "PUWeight_do/D");
   newtree->Branch( "btagEfficiency_weight",  &btagEfficiency_weight,  "btagEfficiency_weight/D");
   newtree->Branch( "HLTefficiency_weight",  &HLTefficiency_weight, "HLTefficiency_weight/D");
   newtree->Branch( "muonIDSF_weight", &muonIDSF_weight, "muonIDSF_weight/D");
   newtree->Branch( "muonIDSF_weight_up", &muonIDSF_weight_up, "muonIDSF_weight_up/D");
   newtree->Branch( "muonIDSF_weight_down", &muonIDSF_weight_down, "muonIDSF_weight_down/D");
   newtree->Branch( "mounTrackerSF_weight", &mounTrackerSF_weight, "mounTrackerSF_weight/D");

   newtree->Branch( "eleMVAT_IDSF_weight", &eleMVAT_IDSF_weight, "eleMVAT_IDSF_weight/D");
   newtree->Branch( "eleMVAT_IDSF_weight_up", &eleMVAT_IDSF_weight_up, "eleMVAT_IDSF_weight_up/D");
   newtree->Branch( "eleMVAT_IDSF_weight_down", &eleMVAT_IDSF_weight_down, "eleMVAT_IDSF_weight_down/D");
   newtree->Branch( "eleMVAT_IDSF_weight_backup", &eleMVAT_IDSF_weight_backup, "eleMVAT_IDSF_weight_backup/D");
   newtree->Branch( "tauT_IDSF_weight", &tauT_IDSF_weight, "tauT_IDSF_weight/D");
   newtree->Branch( "tauT_IDSF_weight_new", &tauT_IDSF_weight_new, "tauT_IDSF_weight_new/D");
   newtree->Branch( "tauT_IDSF_weight_new_vsjetUp", &tauT_IDSF_weight_new_vsjetUp, "tauT_IDSF_weight_new_vsjetUp/D");
   newtree->Branch( "tauT_IDSF_weight_new_vsjetDown", &tauT_IDSF_weight_new_vsjetDown, "tauT_IDSF_weight_new_vsjetDown/D");
   newtree->Branch( "tauT_IDSF_weight_new_vsmuUp", &tauT_IDSF_weight_new_vsmuUp, "tauT_IDSF_weight_new_vsmuUp/D");
   newtree->Branch( "tauT_IDSF_weight_new_vsmuDown", &tauT_IDSF_weight_new_vsmuDown, "tauT_IDSF_weight_new_vsmuDown/D");
   newtree->Branch( "tauT_IDSF_weight_new_vseleUp", &tauT_IDSF_weight_new_vseleUp, "tauT_IDSF_weight_new_vseleUp/D");
   newtree->Branch( "tauT_IDSF_weight_new_vseleDown", &tauT_IDSF_weight_new_vseleDown, "tauT_IDSF_weight_new_vseleDown/D");

//    newtree->Branch( "", &, "/D");
//    newtree->Branch( "", &, "/D");

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
  newtree->Branch("muonsT_3pt", &muonsT_3pt, "muonsT_3pt/D");
  newtree->Branch("muonsT_3eta", &muonsT_3eta, "muonsT_3eta/D");
  newtree->Branch("muonsT_3phi", &muonsT_3phi, "muonsT_3phi/D");
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

  newtree->Branch("tausT_number_TESup", &tausT_number_TESup, "tausT_number_TESup/I");
  newtree->Branch("tausT_number_TESdown", &tausT_number_TESdown, "tausT_number_TESdown/I");
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
   //
   //
   //
  newtree->Branch("jets_HT_JECup", &jets_HT_JECup, "jets_HT_JECup/D");
  newtree->Branch("jets_HT_JECdown", &jets_HT_JECdown, "jets_HT_JECdown/D");
   newtree->Branch( "jets_number_JECup", &jets_number_JECup, "jets_number_JECup/D");
   newtree->Branch( "jets_number_JECdown", &jets_number_JECdown, "jets_number_JECdown/D");

  newtree->Branch("jets_number", &jets_number, "jets_number/I");
  newtree->Branch("jets_HT", &jets_HT, "jets_HT/D");
  newtree->Branch("jets_MHT", &jets_MHT, "jets_MHT/D");
  newtree->Branch("jets_invariantMass", &jets_invariantMass,
                  "jets_invariantMass/D");
  newtree->Branch("jets_transMass", &jets_transMass, "jets_transMass/D");
  newtree->Branch("jets_minDeltaR", &jets_minDeltaR, "jets_minDeltaR/D");
  newtree->Branch("jets_centrality", &jets_centrality, "jets_centrality/D");
  newtree->Branch("jets_bScore", &jets_bScore, "jets_bScore/D");
  newtree->Branch("jets_bScoreMultiply",  &jets_bScoreMultiply, "jets_bScoreMultiply/D");
  newtree->Branch("jets_average_deltaR", &jets_average_deltaR, "&jets_average_deltaR/D");
  newtree->Branch("jets_4largestBscoreSum", &jets_4largestBscoreSum,"jets_4largestBscoreSum/D");
  newtree->Branch("jets_4largestBscoreMulti", &jets_4largestBscoreMulti, "jets_4largestBscoreMulti/D");
  newtree->Branch("jets_leading2invariantMass", &jets_leading2invariantMass,"jets_leading2invariantMass/D");
  newtree->Branch("jets_rationHT_4toRest", &jets_rationHT_4toRest,"jets_rationHT_4toRest/D");

  newtree->Branch("jets_leptonsMVAT_minDeltaR", &jets_leptonsMVAT_minDeltaR,
                  "jets_leptonsMVAT_minDeltaR/D");
  newtree->Branch("jets_tausF_minDeltaR", &jets_tausF_minDeltaR,
                  "jets_tausF_minDeltaR/D");
  newtree->Branch("jets_HTDividedByMet", &jets_HTDividedByMet, "jets_HTDividedByMet/D");
  newtree->Branch("MetDividedByHT", &MetDividedByHT, "MetDividedByHT/D");
  newtree->Branch("jets_MHTDividedByMet", &jets_MHTDividedByMet, "jets_MHTDividedByMet/D");
  newtree->Branch("jets_spherilty", &jets_spherilty, "jets_spherilty/D");
  newtree->Branch("jets_aplanarity", &jets_aplanarity, "jets_aplanarity/D");
  newtree->Branch("jets_1pt", &jets_1pt, "jets_1pt/D");
  newtree->Branch("jets_1eta", &jets_1eta, "jets_1eta/D");
  newtree->Branch("jets_1phi", &jets_1phi, "jets_1phi/D");
  newtree->Branch("jets_2pt", &jets_2pt, "jets_2pt/D");
  newtree->Branch("jets_2eta", &jets_2eta, "jets_2eta/D");
  newtree->Branch("jets_2phi", &jets_2phi, "jets_2phi/D");
  newtree->Branch("jets_3pt", &jets_3pt, "jets_3pt/D");
  newtree->Branch("jets_3eta", &jets_3eta, "jets_3eta/D");
  newtree->Branch("jets_3phi", &jets_3phi, "jets_3phi/D");
  newtree->Branch("jets_4pt", &jets_4pt, "jets_4pt/D");
  newtree->Branch("jets_4eta", &jets_4eta, "jets_4eta/D");
  newtree->Branch("jets_4phi", &jets_4phi, "jets_4phi/D");
  newtree->Branch("jets_5pt", &jets_5pt, "jets_5pt/D");
  newtree->Branch("jets_5eta", &jets_5eta, "jets_5eta/D");
  newtree->Branch("jets_5phi", &jets_5phi, "jets_5phi/D");
  newtree->Branch("jets_6pt", &jets_6pt, "jets_6pt/D");
  newtree->Branch("jets_6eta", &jets_6eta, "jets_6eta/D");
  newtree->Branch("jets_6phi", &jets_6phi, "jets_6phi/D");
  newtree->Branch("jets_7pt", &jets_7pt, "jets_7pt/D");
  newtree->Branch("jets_7eta", &jets_7eta, "jets_7eta/D");
  newtree->Branch("jetL_7phi", &jetL_7phi, "jetL_7phi/D");
  newtree->Branch("jets_8pt", &jets_8pt, "jets_8pt/D");
  newtree->Branch("jets_8eta", &jets_8eta, "jets_8eta/D");
  newtree->Branch("jets_8phi", &jets_8phi, "jets_8phi/D");
  newtree->Branch("jets_9pt", &jets_9pt, "jets_9pt/D");
  newtree->Branch("jets_9eta", &jets_9eta, "jets_9eta/D");
  newtree->Branch("jets_9phi", &jets_9phi, "jets_9phi/D");
  newtree->Branch("jets_10pt", &jets_10pt, "jets_10pt/D");
  newtree->Branch("jets_10eta", &jets_10eta, "jets_10eta/D");
  newtree->Branch("jets_10phi", &jets_10phi, "jets_10phi/D");
  newtree->Branch("jets_11pt", &jets_11pt, "jets_11pt/D");
  newtree->Branch("jets_11eta", &jets_11eta, "jets_11eta/D");
  newtree->Branch("jets_11phi", &jets_11phi, "jets_11phi/D");

  newtree->Branch("bjetsL_num", &bjetsL_num, "bjetsL_num/I");
  newtree->Branch("bjetsM_num", &bjetsM_num, "bjetsM_num/I");
  newtree->Branch("bjetsT_num", &bjetsT_num, "bjetsT_num/I");
  newtree->Branch("bjetsL_HT", &bjetsL_HT, "bjetsL_HT/D");
  newtree->Branch("bjetsM_HT", &bjetsM_HT, "bjetsM_HT/D");
  newtree->Branch("bjetsT_HT", &bjetsT_HT, "bjetsT_HT/D");
  newtree->Branch("bjetsL_MHT", &bjetsL_MHT, "bjetsL_MHT/D");
  newtree->Branch("bjetsM_MHT", &bjetsM_MHT, "bjetsM_MHT/D");
  newtree->Branch("bjetsT_MHT", &bjetsT_MHT, "bjetsT_MHT/D");
  newtree->Branch("bjetsL_invariantMass", &bjetsL_invariantMass,
                  "bjetsL_invariantMass/D");
  newtree->Branch("bjetsM_invariantMass", &bjetsM_invariantMass,
                  "bjetsM_invariantMass/D");
  newtree->Branch("bjetsT_invariantMass", &bjetsT_invariantMass,
                  "bjetsT_invariantMass/D");
  newtree->Branch("bjetsL_transMass", &bjetsL_transMass, "bjetsL_transMass/D");
  newtree->Branch("bjetsM_transMass", &bjetsM_transMass, "bjetsM_transMass/D");
  newtree->Branch("bjetsT_transMass", &bjetsT_transMass, "bjetsT_transMass/D");
  newtree->Branch("bjetsL_minDeltaR", &bjetsL_minDeltaR, "bjetsL_minDeltaR/D");
  newtree->Branch("bjetsM_minDeltaR", &bjetsM_minDeltaR, "bjetsM_minDeltaR/D");
  newtree->Branch("bjetsT_minDeltaR", &bjetsT_minDeltaR, "bjetsT_minDeltaR/D");
  newtree->Branch("bjetsL_leptonsMVAT_minDeltaR", &bjetsL_leptonsMVAT_minDeltaR, "bjetsL_leptonsMVAT_minDeltaR/D");
  newtree->Branch("bjetsM_leptonsMVAT_minDeltaR", &bjetsM_leptonsMVAT_minDeltaR, "bjetsM_leptonsMVAT_minDeltaR/D");
  newtree->Branch("bjetsT_leptonsMVAT_minDeltaR", &bjetsT_leptonsMVAT_minDeltaR, "bjetsT_leptonsMVAT_minDeltaR/D");
  newtree->Branch("bjetsL_tausF_minDeltaR", &bjetsL_tausF_minDeltaR, "bjetsL_tausF_minDeltaR/D");
  // newtree->Branch("", &, "/D");
  newtree->Branch("bjetsL_1pt", &bjetsL_1pt, "bjetsL_1pt/D");
  newtree->Branch("bjetsL_1eta", &bjetsL_1eta, "bjetsL_1eta/D");
  newtree->Branch("bjetsL_1phi", &bjetsL_1phi, "bjetsL_1phi/D");
  newtree->Branch("bjetsL_2pt", &bjetsL_2pt, "bjetsL_2pt/D");
  newtree->Branch("bjetsL_2eta", &bjetsL_2eta, "bjetsL_2eta/D");
  newtree->Branch("bjetsL_2phi", &bjetsL_2phi, "bjetsL_2phi/D");
  newtree->Branch("bjetsL_3pt", &bjetsL_3pt, "bjetsL_3pt/D");
  newtree->Branch("bjetsL_3eta", &bjetsL_3eta, "bjetsL_3eta/D");
  newtree->Branch("bjetsL_3phi", &bjetsL_3phi, "bjetsL_3phi/D");
  newtree->Branch("bjetsL_4pt", &bjetsL_4pt, "bjetsL_4pt/D");
  newtree->Branch("bjetsL_4eta", &bjetsL_4eta, "bjetsL_4eta/D");
  newtree->Branch("bjetsL_4phi", &bjetsL_4phi, "bjetsL_4phi/D");
  newtree->Branch("bjetsM_1pt", &bjetsM_1pt, "bjetsM_1pt/D");
  newtree->Branch("bjetsM_1eta", &bjetsM_1eta, "bjetsM_1eta/D");
  newtree->Branch("bjetsM_1phi", &bjetsM_1phi, "bjetsM_1phi/D");
  newtree->Branch("bjetsM_2pt", &bjetsM_2pt, "bjetsM_2pt/D");
  newtree->Branch("bjetsM_2eta", &bjetsM_2eta, "bjetsM_2eta/D");
  newtree->Branch("bjetsM_2phi", &bjetsM_2phi, "bjetsM_2phi/D");
  newtree->Branch("bjetsM_3pt", &bjetsM_3pt, "bjetsM_3pt/D");
  newtree->Branch("bjetsM_3eta", &bjetsM_3eta, "bjetsM_3eta/D");
  newtree->Branch("bjetsM_3phi", &bjetsM_3phi, "bjetsM_3phi/D");
  newtree->Branch("bjetsM_4pt", &bjetsM_4pt, "bjetsM_4pt/D");
  newtree->Branch("bjetsM_4eta", &bjetsM_4eta, "bjetsM_4eta/D");
  newtree->Branch("bjetsM_4phi", &bjetsM_4phi, "bjetsM_4phi/D");
  newtree->Branch("bjetsT_1pt", &bjetsT_1pt, "bjetsT_1pt/D");
  newtree->Branch("bjetsT_1eta", &bjetsT_1eta, "bjetsT_1eta/D");
  newtree->Branch("bjetsT_1phi", &bjetsT_1phi, "bjetsT_1phi/D");
  newtree->Branch("bjetsT_2pt", &bjetsT_2pt, "bjetsT_2pt/D");
  newtree->Branch("bjetsT_2eta", &bjetsT_2eta, "bjetsT_2eta/D");
  newtree->Branch("bjetsT_2phi", &bjetsT_2phi, "bjetsT_2phi/D");
  newtree->Branch("bjetsT_3pt", &bjetsT_3pt, "bjetsT_3pt/D");
  newtree->Branch("bjetsT_3eta", &bjetsT_3eta, "bjetsT_3eta/D");
  newtree->Branch("bjetsT_3phi", &bjetsT_3phi, "bjetsT_3phi/D");
  newtree->Branch("bjetsT_4pt", &bjetsT_4pt, "bjetsT_4pt/D");
  newtree->Branch("bjetsT_4eta", &bjetsT_4eta, "bjetsT_4eta/D");
  newtree->Branch("bjetsT_4phi", &bjetsT_4phi, "bjetsT_4phi/D");

  newtree->Branch("nonbjetsL_num", &nonbjetsL_num, "nonbjetsL_num/I");
  newtree->Branch("nonbjetsM_num", &nonbjetsM_num, "nonbjetsM_num/I");
  newtree->Branch("nonbjetsT_num", &nonbjetsT_num, "nonbjetsT_num/I");
  newtree->Branch("nonbjetsL_1pt", &nonbjetsL_1pt, "nonbjetsL_1pt/D");
  newtree->Branch("nonbjetsL_1eta", &nonbjetsL_1eta, "nonbjetsL_1eta/D");
  newtree->Branch("nonbjetsL_1phi", &nonbjetsL_1phi, "nonbjetsL_1phi/D");
  newtree->Branch("nonbjetsL_2pt", &nonbjetsL_2pt, "nonbjetsL_2pt/D");
  newtree->Branch("nonbjetsL_2eta", &nonbjetsL_2eta, "nonbjetsL_2eta/D");
  newtree->Branch("nonbjetsL_2phi", &nonbjetsL_2phi, "nonbjetsL_2phi/D");
  newtree->Branch("nonbjetsL_3pt", &nonbjetsL_3pt, "nonbjetsL_3pt/D");
  newtree->Branch("nonbjetsL_3eta", &nonbjetsL_3eta, "nonbjetsL_3eta/D");
  newtree->Branch("nonbjetsL_3phi", &nonbjetsL_3phi, "nonbjetsL_3phi/D");
  newtree->Branch("nonbjetsL_4pt", &nonbjetsL_4pt, "nonbjetsL_4pt/D");
  newtree->Branch("nonbjetsL_4eta", &nonbjetsL_4eta, "nonbjetsL_4eta/D");
  newtree->Branch("nonbjetsL_4phi", &nonbjetsL_4phi, "nonbjetsL_4phi/D");
  newtree->Branch("nonbjetsM_1pt", &nonbjetsM_1pt, "nonbjetsM_1pt/D");
  newtree->Branch("nonbjetsM_1eta", &nonbjetsM_1eta, "nonbjetsM_1eta/D");
  newtree->Branch("nonbjetsM_1phi", &nonbjetsM_1phi, "nonbjetsM_1phi/D");
  newtree->Branch("nonbjetsM_2pt", &nonbjetsM_2pt, "nonbjetsM_2pt/D");
  newtree->Branch("nonbjetsM_2eta", &nonbjetsM_2eta, "nonbjetsM_2eta/D");
  newtree->Branch("nonbjetsM_2phi", &nonbjetsM_2phi, "nonbjetsM_2phi/D");
  newtree->Branch("nonbjetsM_3pt", &nonbjetsM_3pt, "nonbjetsM_3pt/D");
  newtree->Branch("nonbjetsM_3eta", &nonbjetsM_3eta, "nonbjetsM_3eta/D");
  newtree->Branch("nonbjetsM_3phi", &nonbjetsM_3phi, "nonbjetsM_3phi/D");
  newtree->Branch("nonbjetsM_4pt", &nonbjetsM_4pt, "nonbjetsM_4pt/D");
  newtree->Branch("nonbjetsM_4eta", &nonbjetsM_4eta, "nonbjetsM_4eta/D");
  newtree->Branch("nonbjetsM_4phi", &nonbjetsM_4phi, "nonbjetsM_4phi/D");
  newtree->Branch("nonbjetsT_1pt", &nonbjetsT_1pt, "nonbjetsT_1pt/D");
  newtree->Branch("nonbjetsT_1eta", &nonbjetsT_1eta, "nonbjetsT_1eta/D");
  newtree->Branch("nonbjetsT_1phi", &nonbjetsT_1phi, "nonbjetsT_1phi/D");
  newtree->Branch("nonbjetsT_2pt", &nonbjetsT_2pt, "nonbjetsT_2pt/D");
  newtree->Branch("nonbjetsT_2eta", &nonbjetsT_2eta, "nonbjetsT_2eta/D");
  newtree->Branch("nonbjetsT_2phi", &nonbjetsT_2phi, "nonbjetsT_2phi/D");
  newtree->Branch("nonbjetsT_3pt", &nonbjetsT_3pt, "nonbjetsT_3pt/D");
  newtree->Branch("nonbjetsT_3eta", &nonbjetsT_3eta, "nonbjetsT_3eta/D");
  newtree->Branch("nonbjetsT_3phi", &nonbjetsT_3phi, "nonbjetsT_3phi/D");
  newtree->Branch("nonbjetsT_4pt", &nonbjetsT_4pt, "nonbjetsT_4pt/D");
  newtree->Branch("nonbjetsT_4eta", &nonbjetsT_4eta, "nonbjetsT_4eta/D");
  newtree->Branch("nonbjetsT_4phi", &nonbjetsT_4phi, "nonbjetsT_4phi/D");

  newtree->Branch("forwardJets_num", &forwardJets_num, "forwardJets_num/I");

  newtree->Branch("toptagger_num", &toptagger_num, "toptagger_num/I");
  newtree->Branch("toptagger_MHT", &toptagger_MHT, "toptagger_MHT/D");
  newtree->Branch("toptagger_HT", &toptagger_HT, "toptagger_HT/D");
  newtree->Branch("toptagger_invariantMass", &toptagger_invariantMass, "toptagger_invariantMass/D");
  newtree->Branch("toptagger_transMass", &toptagger_transMass, "toptagger_transMass/D");
  newtree->Branch("toptagger_minDeltaR_v1", &toptagger_minDeltaR_v1, "toptagger_minDeltaR_v1/D");
  newtree->Branch("toptagger_1pt", &toptagger_1pt, "toptagger_1pt/I");
  newtree->Branch("toptagger_1eta", &toptagger_1eta, "toptagger_1eta/I");
  newtree->Branch("toptagger_1phi", &toptagger_1phi, "toptagger_1phi/I");
  newtree->Branch("toptagger_2pt", &toptagger_2pt, "toptagger_2pt/D");
  newtree->Branch("toptagger_2eta", &toptagger_2eta, "toptagger_2eta/D");
  newtree->Branch("toptagger_2phi", &toptagger_2phi, "toptagger_2phi/D");
  newtree->Branch("toptagger_3pt", &toptagger_3pt, "toptagger_3pt/D");
  newtree->Branch("toptagger_3eta", &toptagger_3eta, "toptagger_3eta/D");
  newtree->Branch("toptagger_3phi", &toptagger_3phi, "toptagger_3phi/D");
  newtree->Branch("toptagger_scoreAllTops", &toptagger_scoreAllTops, "toptagger_scoreAllTops/D");
  newtree->Branch("toptagger_leptonsMVAT_minDeltaR", &toptagger_leptonsMVAT_minDeltaR, "toptagger_leptonsMVAT_minDeltaR/D");

}
 /* 
void makeVaribles_forBDT::initializeBReader(){
    std::cout << "Loading the .csv file..." << "\n";
    
	std::string inputCSVfile = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/scale_factors/DeepJet_2016LegacySF_V1.csv";  
    //?might be wrong csv file
	std::string measType = "iterativefit";
	std::string sysType = "central";
	std::string sysTypeJESUp = "up_jes";
	std::string sysTypeJESDown = "down_jes";
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
    
    // BTagCalibrationReader CSVreader(BTagEntry::OP_RESHAPING, sysType, {sysTypeJESUp, sysTypeJESDown, sysTypeHFUp, sysTypeHFDown, sysTypeLFUp, sysTypeLFDown, sysTypehfstats1Up, sysTypehfstats1Down, sysTypehfstats2Up, sysTypehfstats2Down, sysTypelfstats1Up, sysTypelfstats1Down, sysTypelfstats2Up, sysTypelfstats2Down, sysTypecfErr1Up, sysTypecfErr1Down, sysTypecfErr2Up, sysTypecfErr2Down});
    CSVreader = BTagCalibrationReader(BTagEntry::OP_RESHAPING, sysType, {sysTypeJESUp, sysTypeJESDown, sysTypeHFUp, sysTypeHFDown, sysTypeLFUp, sysTypeLFDown, sysTypehfstats1Up, sysTypehfstats1Down, sysTypehfstats2Up, sysTypehfstats2Down, sysTypelfstats1Up, sysTypelfstats1Down, sysTypelfstats2Up, sysTypelfstats2Down, sysTypecfErr1Up, sysTypecfErr1Down, sysTypecfErr2Up, sysTypecfErr2Down});
    CSVreader.load(calib, BTagEntry::FLAV_B, measType);
    CSVreader.load(calib, BTagEntry::FLAV_C, measType);
    CSVreader.load(calib, BTagEntry::FLAV_UDSG, measType);
    
    std::cout << "Input CSV weight file = " << inputCSVfile << "; measurementType = " << measType << ";" << "\n";

}
*/

void makeVaribles_forBDT::InitializeBranches()
{
    EVENT_prefireWeight  = -99;
    EVENT_genWeight = -99;
    PUWeight = -99;
    PUWeight_do = -99;
    PUWeight_up = -99;
    btagEfficiency_weight = -99;
    HLTefficiency_weight = -99;
	  muonIDSF_weight = -99;
	  muonIDSF_weight_up = -99;
	  muonIDSF_weight_down = -99;
    mounTrackerSF_weight = -99;
	  eleMVAT_IDSF_weight = -99;
	  eleMVAT_IDSF_weight_up = -99;
	  eleMVAT_IDSF_weight_down = -99;
    eleMVAT_IDSF_weight_backup = -99;
	  tauT_IDSF_weight = -99;
	  tauT_IDSF_weight_new = -99;
	  tauT_IDSF_weight_new_vsjetUp = -99;
	  tauT_IDSF_weight_new_vsjetDown = -99;

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

     tausT_number_TESup=-99;
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

	 jets_HT_JECup = -99.;
	 jets_HT_JECdown = -99.;
	 jets_number_JECup = -99.;
	 jets_number_JECdown = -99.;

	 jets_number = -99;
	 jets_MHT = -99;
	 jets_HT = -99;
	 jets_invariantMass = -99;
	 jets_transMass = -99;
	 jets_minDeltaR = -99;
	 jets_centrality = -99;
	 jets_bScore = -99;
	 jets_bScoreMultiply = -99;
	 jets_average_deltaR = -99;
	 jets_4largestBscoreSum = -99;
	 jets_4largestBscoreMulti = -99;
	 jets_leading2invariantMass = -99;
	 jets_rationHT_4toRest = -99;
	 jets_HTDividedByMet = -99;
	 MetDividedByHT = -99;
	 jets_MHTDividedByMet = -99;
     jets_leptonsMVAT_minDeltaR= -99;
     jets_tausF_minDeltaR= -99;
     jets_spherilty = -99;
     jets_aplanarity = -99;
    jets_1pt = -99;
     jets_1phi = -99;
     jets_1eta = -99;
     jets_2pt = -99;
     jets_2eta = -99;
     jets_2phi = -99;
     jets_3pt = -99;
     jets_3eta = -99;
     jets_3phi = -99;
     jets_4pt = -99;
     jets_4eta = -99;
     jets_4phi = -99;
     jets_5pt = -99;
     jets_5eta = -99;
     jets_5phi = -99;
     jets_6pt = -99;
     jets_6eta = -99;
     jets_6phi = -99;
     jets_7pt = -99;
     jets_7eta = -99;
     jetL_7phi = -99;
     jets_8pt = -99;
     jets_8eta = -99;
     jets_8phi = -99;
     jets_9pt = -99;
     jets_9eta = -99;
     jets_9phi = -99;
     jets_10pt = -99;
     jets_10eta = -99;
     jets_10phi = -99;
     jets_11pt = -99;
     jets_11eta = -99;
     jets_11phi = -99;

     bjetsL_num = -99;
     bjetsM_num= -99;
     bjetsT_num= -99;
     bjetsL_HT= -99;
     bjetsM_HT= -99;
     bjetsT_HT= -99;
     bjetsL_MHT= -99;
     bjetsM_MHT= -99;
     bjetsT_MHT= -99;
     bjetsL_invariantMass= -99;
     bjetsM_invariantMass= -99;
     bjetsT_invariantMass= -99;
     bjetsL_transMass= -99;
     bjetsM_transMass= -99;
     bjetsT_transMass= -99;
     bjetsL_minDeltaR= -99;
     bjetsM_minDeltaR= -99;
     bjetsT_minDeltaR= -99;
     bjetsL_leptonsMVAT_minDeltaR= -99;
     bjetsM_leptonsMVAT_minDeltaR= -99;
     bjetsT_leptonsMVAT_minDeltaR= -99;
     bjetsL_tausF_minDeltaR= -99;
     bjetsL_1pt = -99;
     bjetsL_1eta = -99;
     bjetsL_1phi = -99;
     bjetsL_2pt = -99;
     bjetsL_2eta = -99;
     bjetsL_2phi = -99;
     bjetsL_4pt = -99;
     bjetsL_4eta = -99;
     bjetsL_4phi = -99;
     bjetsL_3pt = -99;
     bjetsL_3eta = -99;
     bjetsL_3phi = -99;
     bjetsM_1pt = -99;
     bjetsM_1eta = -99;
     bjetsM_1phi = -99;
     bjetsM_2pt = -99;
     bjetsM_2eta = -99;
     bjetsM_2phi = -99;
     bjetsM_4pt = -99;
     bjetsM_4eta = -99;
     bjetsM_4phi = -99;
     bjetsM_3pt = -99;
     bjetsM_3eta = -99;
     bjetsM_3phi = -99;
     bjetsT_1pt = -99;
     bjetsT_1eta = -99;
     bjetsT_1phi = -99;
     bjetsT_2pt = -99;
     bjetsT_2eta = -99;
     bjetsT_2phi = -99;
     bjetsT_3pt = -99;
     bjetsT_3eta = -99;
     bjetsT_3phi = -99;
     bjetsT_4pt = -99;
     bjetsT_4eta = -99;
     bjetsT_4phi = -99;

     nonbjetsL_num = -99;
     nonbjetsM_num= -99;
     nonbjetsT_num= -99;
     nonbjetsL_1pt = -99;
     nonbjetsL_1eta = -99;
     nonbjetsL_1phi = -99;
     nonbjetsL_2pt = -99;
     nonbjetsL_2eta = -99;
     nonbjetsL_2phi = -99;
     nonbjetsL_4pt = -99;
     nonbjetsL_4eta = -99;
     nonbjetsL_4phi = -99;
     nonbjetsL_3pt = -99;
     nonbjetsL_3eta = -99;
     nonbjetsL_3phi = -99;
     nonbjetsM_1pt = -99;
     nonbjetsM_1eta = -99;
     nonbjetsM_1phi = -99;
     nonbjetsM_2pt = -99;
     nonbjetsM_2eta = -99;
     nonbjetsM_2phi = -99;
     nonbjetsM_4pt = -99;
     nonbjetsM_4eta = -99;
     nonbjetsM_4phi = -99;
     nonbjetsM_3pt = -99;
     nonbjetsM_3eta = -99;
     nonbjetsM_3phi = -99;
     nonbjetsT_1pt = -99;
     nonbjetsT_1eta = -99;
     nonbjetsT_1phi = -99;
     nonbjetsT_2pt = -99;
     nonbjetsT_2eta = -99;
     nonbjetsT_2phi = -99;
     nonbjetsT_3pt = -99;
     nonbjetsT_3eta = -99;
     nonbjetsT_3phi = -99;
     nonbjetsT_4pt = -99;
     nonbjetsT_4eta = -99;
     nonbjetsT_4phi = -99;

     forwardJets_num = -99;
     toptagger_num=-99;
     toptagger_MHT = -99;
     toptagger_HT = -99;
     toptagger_invariantMass = -99;
     toptagger_transMass = -99;
     toptagger_minDeltaR_v1 = -99;
    
     toptagger_1pt=-99;
     toptagger_1eta = -99;
     toptagger_1phi = -99;
     toptagger_2pt=-99;
     toptagger_2eta=-99;
     toptagger_2phi=-99;
     toptagger_3pt = -99;
     toptagger_3eta = -99;
     toptagger_3phi = -99;
     toptagger_scoreAllTops=-99;
     toptagger_leptonsMVAT_minDeltaR=-99;

}

