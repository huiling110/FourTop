/*
 * @author Huiling Hua
 * @email huahl@ihep.ac.cn
 * @create date 2021-12-08 02:46:13
 * @modify date 2021-12-08 02:46:13
 * @desc [description]
 */
#define objectTSelectorForNanoAOD_cxx
// The class definition in objectTSelectorForNanoAOD.h has been generated automatically
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
// root> T->Process("objectTSelectorForNanoAOD.C")
// root> T->Process("objectTSelectorForNanoAOD.C","some options")
// root> T->Process("objectTSelectorForNanoAOD.C+")
//
#include "objectTSelectorForNanoAOD.h"
#include "utilityFunctions.h"
//we should use a better way of modulization of code rather the include copy here???
#include <TH2.h>
#include <TStyle.h>

#include <cassert>
///////////////////////

void objectTSelectorForNanoAOD::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

// void objectTSelectorForNanoAOD::SlaveBegin(TTree * /*tree*/)
void objectTSelectorForNanoAOD::SlaveBegin(TTree * fChain)
// void objectTSelectorForNanoAOD::SlaveBegin(TTree * fReader)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   
   TString option = GetOption();
   std::cout<<"option in TSelector : "<<option<<"\n";
   getOptionFromRunMacro( option );



    getRunRange( fChain );
    std::cout<<"runRange: "<<runRange[0]<<":"<<runRange[1]<<"\n";
    intializaTreeBranches( isdata, dataSet );
   
    TString jsonInFile = GoldenJSONs[era];
    // readJSON( isdata, jsonInFile,  _goodLumis );

   
   
   h_genWeight = new TH1D( "h_genweight", "h_genweight", 1,-0.5, 0.5);

   tree = new TTree( "tree", "tree after object selection");
   allEvents = new TTree( "allevents", "events before any selection");

   allEvents->Branch( "genWeight_allEvents", &genWeight_allEvents, "genWeight_allEvents/D");

   makeBranch( tree );

    setupInputFile();
    // setupTauSFTool( isdata );





///////////////////////////////////////

}

Bool_t objectTSelectorForNanoAOD::Process(Long64_t entry)
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

///////////////////////////////////////
   fProcessed++;
   TString option = GetOption(); //used to know the number of the input file and apply HLT accordingly
    //test

    //allEvents new tree
   genWeight_allEvents = -99;
   //CHANGE HERE TO RUN ON DATA
   if ( !isdata ){
       h_genWeight->Fill( 0.0 , *Generator_weight );
       genWeight_allEvents = *Generator_weight;
   }
   allEvents->Fill();


    //!!!branch variable intialization to prevent them from get values from last event

    //good lumi selection
    /*
    //???readJSON function has problems in CMSSW_12_2_4
   if(isdata) {
       if ( _goodLumis.find(*run) == _goodLumis.end() ) return kFALSE;
       else { //if run number is in map
           Bool_t keepEvent = false;
           for ( Int_t i ; i < _goodLumis[*run].size()/2.; i++){
               if ( *luminosityBlock >= _goodLumis[*run][i*2] && *luminosityBlock <= _goodLumis[*run][i*2+1] ) {
        o          keepEvent = true;
                   break;
               }
           }
           if (!keepEvent) return kFALSE; //veto luminosity blocks not in JSON
       }
   }
   */
   eventsPassedJSON++;
   
   //MET filters
   if ( MetFilters ){
        //recommendations from here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#MET_Filter_Recommendations_for_R
        if (!(*Flag_goodVertices == 1)) return kFALSE; // a branch in tree.
        if (!(*Flag_globalSuperTightHalo2016Filter == 1))    return kFALSE;
        if (!(*Flag_HBHENoiseFilter == 1))        return kFALSE;
        if (!(*Flag_HBHENoiseIsoFilter == 1))        return kFALSE;
        if (!(*Flag_EcalDeadCellTriggerPrimitiveFilter == 1))        return kFALSE; // a branch in Tree
        if (!(*Flag_BadPFMuonFilter == 1))      return kFALSE;
        if (!(*Flag_BadPFMuonDzFilter == 1))      return kFALSE;
        if (!(*Flag_eeBadScFilter == 1))      return kFALSE;
        // if ( era == "2017" || era == "2018" ){
            if(!(*Flag_ecalBadCalibFilter==1))  return kFALSE;//for UL 2016 has this flag too
        // }
		// if (isdata) {  if (!(*Flag_eeBadScFilter == 1)) return kFALSE;}
	    if (!(*Flag_eeBadScFilter == 1)) return kFALSE; //for UL this filter exists for 2016 MC too
    }
   eventsPassedMETFilters++;
    copyFlags();

    

    //HLT
    if (HLTSelection){
        if (era.CompareTo("2016preVFP")==0 || era.CompareTo("2016postVFP")==0) {
            // std::cout<<"HLT selection for 2016"<<"\n";
            if( !( *HLT_PFHT450_SixJet40_BTagCSV_p056==1 || *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056==1 || *HLT_PFJet450==1  )  ) return kFALSE;
        }
    }
    eventsPassedHLT++;
    //!!!very important to give value to default values to variables for each event!!!
    initializeBrancheValues();

    run_ = *run;
    copyHLT_new( isdata, dataSet );


    //Compute the per-event PU weight
    if ( !isdata ){
        if (MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(*Pileup_nTrueInt)) > 0) {
            PUWeight_ = dataPileupProfile->GetBinContent(dataPileupProfile->FindBin(*Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(*Pileup_nTrueInt));
            PUWeight_Up = dataPileupProfileUp->GetBinContent(dataPileupProfileUp->FindBin(*Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(*Pileup_nTrueInt));
            PUWeight_Down = dataPileupProfileDown->GetBinContent(dataPileupProfileDown->FindBin(*Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(*Pileup_nTrueInt));
        }
    }
    PV_npvs_ = *PV_npvs;
    PV_npvsGood_ = *PV_npvsGood;
    if ( !isdata )genTtbarId_ = *genTtbarId;

    



    SelectMuons( muonsL, muonsL_index, 0 ); sort( muonsL.begin(), muonsL.end(), compEle);
    SelectMuons( muonsF, muonsF_index, 1); sort( muonsF.begin(), muonsF.end(), compEle);
    SelectMuons( muonsT, muonsT_index, 2);sort( muonsT.begin(), muonsT.end(), compEle);
    mounsT_total = mounsT_total + muonsT.size();
    mounsF_total = mounsF_total + muonsF.size();
    mounsL_total = mounsL_total + muonsL.size();

    SelectElectronsMVA( eleMVAT, eleMVAT_index, 2 ); 
    SelectElectronsMVA( eleMVAF, eleMVAF_index, 1 ); 
    SelectElectronsMVA( eleMVAL, eleMVAL_index, 0 ); 
    sort( eleMVAL.begin(), eleMVAL.end(), compEle);
    sort( eleMVAF.begin(), eleMVAF.end(), compEle);
    sort( eleMVAT.begin(), eleMVAT.end(), compEle);
    elesT_total = elesT_total + eleMVAT.size();
    elesF_total = elesF_total + eleMVAF.size();
    elesL_total = elesL_total + eleMVAL.size();

    leptonsMVAF = muonsF;    leptonsMVAF.insert(leptonsMVAF.end(), eleMVAF.begin(), eleMVAF.end());
    sort( leptonsMVAF.begin(), leptonsMVAF.end(), compEle);
    leptonsMVAT = muonsT;  leptonsMVAT.insert(leptonsMVAT.end(), eleMVAT.begin(), eleMVAT.end());
    sort( leptonsMVAT.begin(), leptonsMVAT.end(), compEle);
    leptonsMVAL = muonsL; leptonsMVAL.insert(leptonsMVAL.end(), eleMVAL.begin(), eleMVAL.end());
    sort( leptonsMVAL.begin(), leptonsMVAL.end(), compEle);

    //nominal taus
    // calTauSF( isdata );
    calTauSF_new();
    SelectTaus( tausL, tausL_TESup, tausL_TESdown, tausL_index, tausL_decayMode, tausL_genPartFlav, 1, leptonsMVAL);
    // sort( tausL.begin(), tausL.end(), compEle);
    SelectTaus( tausF, tausF_TESup, tausF_TESdown, tausF_index, tausF_decayMode, tausF_genPartFlav, 2, leptonsMVAL); 
    //sort( tausF.begin(), tausF.end(), compEle);
    SelectTaus( tausT, tausT_TESup, tausT_TESdown, tausT_index, tausT_decayMode, tausT_genPartFlav, 3, leptonsMVAL); 
    //sort( tausT.begin(), tausT.end(), compEle);
    // //Up TES
    // //Down TES
    // //Up FES
    // //Down FES
    // //???does here imply we need at least 1 leptons
    tausT_total = tausT_total + tausT.size();
    tausF_total = tausF_total + tausF.size();
	tausL_total = tausL_total + tausL.size();
	
	
	
	

    bool deepJet = true;
    // calJetSmearFactors(  isdata );
    calJER_SF(isdata, JER_SF_new, JER_SF_new_up, JER_SF_new_down, cset_jerSF.get() );
    // std::cout << "JER_SF_new " << JER_SF_new.size() << "\n";

    SelectJets(0, deepJet, jets, jets_btags, jets_index, jets_flavour, leptonsMVAL, tausL, 0);
    // std::cout << "jets size" << jets.size() << "\n";
    // tprintElements( jets_btags, jets );
    // sort( jets.begin(), jets.end(), compEle);
    // pt are sorted in MINIAOD
    // SelectJets(11, deepJet, bjetsL, bjetsL_JERup, bjetsL_JERdown, bjetsL_btags, bjetsL_index, bjetsL_flavour, leptonsMVAL, tausL);
    // sort( bjetsL.begin(), bjetsL.end(), compEle);
    // SelectJets(12, deepJet, bjetsM, bjetsM_JERup, bjetsM_JERdown, bjetsM_btags, bjetsM_index, bjetsM_flavour,  leptonsMVAL, tausL);
    // sort( bjetsM.begin(), bjetsM.end(), compEle);
    // SelectJets(13, deepJet, bjetsT, bjetsT_JERup, bjetsT_JERdown, bjetsT_btags, bjetsT_index, bjetsT_flavour, leptonsMVAL, tausL);
    // sort( bjetsT.begin(), bjetsT.end(), compEle);
    // SelectJets(2, deepJet,  forwardJets, forwardJets_JERup, forwardJets_JERdown, forwardJets_btags, forwardJets_index, forwardJets_flavour,  leptonsMVAL, tausL);
    // sort( forwardJets.begin(), forwardJets.end(), compEle);

    jetsSubstructBjets( nonbjetsL,jets, bjetsL );
    jetsSubstructBjets( nonbjetsM, jets, bjetsM );
    jetsSubstructBjets( nonbjetsT, jets, bjetsT );
    // cout<<"nonb="<<nonbjetsL.size()<<" bjet="<<bjetsL.size()<<" jets="<<jets.size()<<endl;
    jets_total = jets_total + jets.size();
    bjetsM_total = bjetsM_total + bjetsM.size();


    if ( Electron_charge.GetSize() > 0 ){
        copy_TTreeReaderArray_toVector( Electron_charge, patElectron_charge_);}
    if ( Tau_charge.GetSize()>0 ){
        copy_TTreeReaderArray_toVector( Tau_charge, Tau_charge_);
    }
    if ( Muon_charge.GetSize()>0 ){
        copy_TTreeReaderArray_toVector( Muon_charge, Muon_charge_);
    }


    // MetCorrection(SysJes, SysJer, Met_pt);
    // Met_phi = *Met_type1PF_phi; 

    // SelectTops( tops_toptagger);
    // sort( tops_toptagger.begin(), tops_toptagger.end(), compEle);

    if ( !isdata ){
        genTaus.clear();
        genEles.clear();
        genMuons.clear();
        selectGenTaus(genTaus);
        selectGenEles(genEles);
        selectGenMuons(genMuons);
    }

    EVENT_prefireWeight_ = *L1PreFiringWeight_Nom;

	
	if ( !isdata ){
        EVENT_genWeight_ = *genWeight;
    }
	
    //preSelection
    if (preSelection) {
        if ( !( tausL.size()>0)) return kFALSE;
		if ( !( jets.size()>5))  return kFALSE;
        if ( !( bjetsL.size()>1)) return kFALSE;
        //if ( !( bjetsL.size()>2)) return kFALSE;
    }




    eventsPassed++;
    tree->Fill();

///////////////////////////////////////








   return kTRUE;
}

void objectTSelectorForNanoAOD::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void objectTSelectorForNanoAOD::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

    // inputPUFile_data->Close();
    // delete inputPUFile_data;
    // inputPUFile_dataUp->Close();
    // delete inputPUFile_dataUp;
    // inputPUFile_dataDown->Close();
    // delete inputPUFile_dataDown;
    // inputPUFile_mc->Close();
    // delete inputPUFile_mc;
///////////////////////////////
    outputfile->Write();
    outputfile->Close();
    Info("Terminate", "processed %lld events", fProcessed);
    Info("Terminate", "passed JSON %lld events", eventsPassedJSON);
    Info("Terminate", "passed MET filters %lld events", eventsPassedMETFilters);
    Info("Terminate", "passed HLT %lld events", eventsPassedHLT);
    Info("Terminate", "passed preselection %lld events", eventsPassed);
    Info("Terminate", "output file here: %s", outputfile->GetName());
///////////////////////////////




}


/////////////////
void objectTSelectorForNanoAOD::makeBranch( TTree* tree ){
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
   tree->Branch( "leptonsMVAF", &leptonsMVAF );
   tree->Branch( "leptonsMVAT", &leptonsMVAT );
   tree->Branch( "leptonsMVAL", &leptonsMVAL );
   tree->Branch( "tausL", &tausL );
   tree->Branch( "tausL_TESup", &tausL_TESup );
   tree->Branch( "tausL_TESdown", &tausL_TESdown );
   tree->Branch( "tausF", &tausF );
   tree->Branch( "tausF_TESup", &tausF_TESup );
   tree->Branch( "tausF_TESdown", &tausF_TESdown );
   tree->Branch( "tausT", &tausT );
   tree->Branch( "tausT_TESdown", &tausT_TESdown );
   tree->Branch( "tausT_TESup", &tausT_TESup );
   tree->Branch( "tausL_index", &tausL_index );
   tree->Branch( "tausF_index", &tausF_index );
   tree->Branch( "tausT_index", &tausT_index );
   tree->Branch( "tausL_decayMode", &tausL_decayMode );
   tree->Branch( "tausF_decayMode", &tausF_decayMode );
   tree->Branch( "tausT_decayMode", &tausT_decayMode );
   tree->Branch( "tausL_genPartFlav", &tausL_genPartFlav );
   tree->Branch( "tausF_genPartFlav", &tausF_genPartFlav );
   tree->Branch( "tausT_genPartFlav", &tausT_genPartFlav );
//    tree->Branch( "tausL_TESUp", &tausL_TESUp );
//    tree->Branch( "tausF_TESUp", &tausF_TESUp );
//    tree->Branch( "tausT_TESUp", &tausT_TESUp );
//    tree->Branch( "tausL_TESUp_index", &tausL_TESUp_index );
//    tree->Branch( "tausF_TESUp_index", &tausF_TESUp_index );
//    tree->Branch( "tausT_TESUp_index", &tausT_TESUp_index );
//    tree->Branch( "tausL_TESUp_decayMode", &tausL_TESUp_decayMode );
   //tree->Branch( "tausF_TESUp_decayMode", &tausF_TESUp_decayMode );
//    tree->Branch( "tausT_TESUp_decayMode", &tausT_TESUp_decayMode );
   //tree->Branch( "tausL_TESUp_genPartFlav", &tausL_TESUp_genPartFlav );
   //tree->Branch( "tausF_TESUp_genPartFlav", &tausF_TESUp_genPartFlav );
//    tree->Branch( "tausT_TESUp_genPartFlav", &tausT_TESUp_genPartFlav );
   //tree->Branch( "tausL_TESDown", &tausL_TESDown );
   //tree->Branch( "tausF_TESDown", &tausF_TESDown );
//    tree->Branch( "tausT_TESDown", &tausT_TESDown );
   //tree->Branch( "tausL_TESDown_index", &tausL_TESDown_index );
   //tree->Branch( "tausF_TESDown_index", &tausF_TESDown_index );
//    tree->Branch( "tausT_TESDown_index", &tausT_TESDown_index );
   //tree->Branch( "tausL_TESDown_decayMode", &tausL_TESDown_decayMode );
   //tree->Branch( "tausF_TESDown_decayMode", &tausF_TESDown_decayMode );
//    tree->Branch( "tausT_TESDown_decayMode", &tausT_TESDown_decayMode );
   //tree->Branch( "tausL_TESDown_genPartFlav", &tausL_TESDown_genPartFlav );
   //tree->Branch( "tausF_TESDown_genPartFlav", &tausF_TESDown_genPartFlav );
//    tree->Branch( "tausT_TESDown_genPartFlav", &tausT_TESDown_genPartFlav );
   //tree->Branch( "tausL_FESUp", &tausL_FESUp );
   //tree->Branch( "tausF_FESUp", &tausF_FESUp );
//    tree->Branch( "tausT_FESUp", &tausT_FESUp );
   //tree->Branch( "tausL_FESUp_index", &tausL_FESUp_index );
   //tree->Branch( "tausF_FESUp_index", &tausF_FESUp_index );
//    tree->Branch( "tausT_FESUp_index", &tausT_FESUp_index );
   //tree->Branch( "tausL_FESUp_decayMode", &tausL_FESUp_decayMode );
   //tree->Branch( "tausF_FESUp_decayMode", &tausF_FESUp_decayMode );
//    tree->Branch( "tausT_FESUp_decayMode", &tausT_FESUp_decayMode );
   //tree->Branch( "tausL_FESUp_genPartFlav", &tausL_FESUp_genPartFlav );
   //tree->Branch( "tausF_FESUp_genPartFlav", &tausF_FESUp_genPartFlav );
//    tree->Branch( "tausT_FESUp_genPartFlav", &tausT_FESUp_genPartFlav );
   //tree->Branch( "tausL_FESDown", &tausL_FESDown );
   //tree->Branch( "tausF_FESDown", &tausF_FESDown );
//    tree->Branch( "tausT_FESDown", &tausT_FESDown );
   //tree->Branch( "tausL_FESDown_index", &tausL_FESDown_index );
   //tree->Branch( "tausF_FESDown_index", &tausF_FESDown_index );
//    tree->Branch( "tausT_FESDown_index", &tausT_FESDown_index );
   //tree->Branch( "tausL_FESDown_decayMode", &tausL_FESDown_decayMode );
   //tree->Branch( "tausF_FESDown_decayMode", &tausF_FESDown_decayMode );
//    tree->Branch( "tausT_FESDown_decayMode", &tausT_FESDown_decayMode );
   //tree->Branch( "tausL_FESDown_genPartFlav", &tausL_FESDown_genPartFlav );
   //tree->Branch( "tausF_FESDown_genPartFlav", &tausF_FESDown_genPartFlav );
//    tree->Branch( "tausT_FESDown_genPartFlav", &tausT_FESDown_genPartFlav );

   tree->Branch( "jets", &jets );
   tree->Branch("jets_index", &jets_index);
   tree->Branch("jets_JERup", &jets_JERup);
   tree->Branch("jets_JERdown", &jets_JERdown);
   tree->Branch("jets_JESuncer", &jets_JESuncer);
   tree->Branch("jets_index", &jets_index);
   tree->Branch( "jets_flavour", &jets_flavour );
   tree->Branch( "jets_btags", &jets_btags );
   tree->Branch( "bjetsL", &bjetsL );
   tree->Branch( "bjetsL_JERup", &bjetsL_JERup );
   tree->Branch( "bjetsL_JERdown", &bjetsL_JERdown );
   tree->Branch( "bjetsL_index", &bjetsL_index );
   tree->Branch( "bjetsL_flavour", &bjetsL_flavour );
   tree->Branch( "bjetsL_btags", &bjetsL_btags );
   tree->Branch( "bjetsM", &bjetsM );
   tree->Branch( "bjetsM_JERup", &bjetsM_JERup );
   tree->Branch( "bjetsM_JERdown", &bjetsM_JERdown );
   tree->Branch( "bjetsM_index", &bjetsM_index );
   tree->Branch( "bjetsM_flavour", &bjetsM_flavour );
   tree->Branch( "bjetsM_btags", &bjetsM_btags );
   tree->Branch( "bjetsT", &bjetsT );
   tree->Branch( "bjetsT_JERup", &bjetsT_JERup );
   tree->Branch( "bjetsT_JERdown", &bjetsT_JERdown );
   tree->Branch( "bjetsT_index", &bjetsT_index );
   tree->Branch( "bjetsT_flavour", &bjetsT_flavour );
   tree->Branch( "bjetsT_btags", &bjetsT_btags );
   tree->Branch( "forwardJets", &forwardJets );
   tree->Branch( "forwardJets_JERup", &forwardJets_JERup );
   tree->Branch( "forwardJets_JERdown", &forwardJets_JERdown );
   tree->Branch( "forwardJets_index", &forwardJets_index );
   tree->Branch( "forwardJets_flavour", &forwardJets_flavour );
   tree->Branch( "forwardJets_btags", &forwardJets_btags );
   tree->Branch( "nonbjetsL", &nonbjetsL );
   tree->Branch( "nonbjetsM", &nonbjetsM );
   tree->Branch( "nonbjetsT", &nonbjetsT );
   tree->Branch( "patElectron_charge_", &patElectron_charge_  );
   tree->Branch( "Tau_charge_", &Tau_charge_ );
   tree->Branch( "Muon_charge_", &Muon_charge_ );
   //CHANGE HERE TO RUN ON DATA
   
//    if ( !isdata ){
       tree->Branch( "genTaus", &genTaus );
       tree->Branch( "genEles", &genEles );
       tree->Branch( "genMuons", &genMuons );
//    }
   
   tree->Branch( "Met_pt", &Met_pt, "Met_pt/D" );
   tree->Branch( "Met_phi", &Met_phi, "Met_phi/D" );
   tree->Branch( "tops_toptagger", &tops_toptagger);

   tree->Branch( "EVENT_prefireWeight_", &EVENT_prefireWeight_, "EVENT_prefireWeight_/D" );
   tree->Branch( "PUWeight_", &PUWeight_, "PUWeight_/D");
   tree->Branch( "PUWeight_Up", &PUWeight_Up, "PUWeight_Up/D");
   tree->Branch( "PUWeight_Down", &PUWeight_Down, "PUWeight_Down/D");
   //CHANGE HERE TO RUN ON DATA
   
       tree->Branch( "EVENT_genWeight_", &EVENT_genWeight_, "EVENT_genWeight_/D" );

   tree->Branch("PV_npvs_", &PV_npvs_, "PV_npvs_/I");
   tree->Branch("PV_npvsGood_", &PV_npvsGood_, "PV_npvsGood_/I");
   tree->Branch("genTtbarId_", &genTtbarId_, "genTtbarId_/I");
   tree->Branch("Flag_goodVertices_", &Flag_goodVertices_, "Flag_goodVertices_/I");
   tree->Branch( "Flag_globalSuperTightHalo2016Filter_", &Flag_globalSuperTightHalo2016Filter_, "Flag_globalSuperTightHalo2016Filter_/I");
   tree->Branch( "Flag_HBHENoiseFilter_", &Flag_HBHENoiseFilter_, "Flag_HBHENoiseFilter_/I");
   tree->Branch( "Flag_HBHENoiseIsoFilter_", &Flag_HBHENoiseIsoFilter_, "Flag_HBHENoiseIsoFilter_/I");
   tree->Branch( "Flag_EcalDeadCellTriggerPrimitiveFilter_", &Flag_EcalDeadCellTriggerPrimitiveFilter_, "Flag_EcalDeadCellTriggerPrimitiveFilter_/I");
   tree->Branch( "Flag_BadPFMuonFilter_", &Flag_BadPFMuonFilter_, "Flag_BadPFMuonFilter_/I");
   tree->Branch( "Flag_eeBadScFilter_", &Flag_eeBadScFilter_, "Flag_eeBadScFilter_/I");
   
        tree->Branch( "run_", &run_, "run_/i");//i : a 32 bit unsigned integer (UInt_t)

       tree->Branch( "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_", &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_/I");
       tree->Branch( "HLT_PFHT450_SixJet40_BTagCSV_p056_", &HLT_PFHT450_SixJet40_BTagCSV_p056_, "HLT_PFHT450_SixJet40_BTagCSV_p056_/I");
       tree->Branch( "HLT_PFJet450_", &HLT_PFJet450_, "HLT_PFJet450_/I");
       tree->Branch( "HLT_IsoMu24_", &HLT_IsoMu24_, "HLT_IsoMu24_/I");
       tree->Branch( "HLT_IsoMu27_", &HLT_IsoMu27_, "HLT_IsoMu27_/I");

        //2018////////////
        // tree->Branch( "", &, "/I");
        tree->Branch( "HLT_PFHT1050_", &HLT_PFHT1050_, "HLT_PFHT1050_/I");
        tree->Branch( "HLT_PFJet500_", &HLT_PFJet500_, "HLT_PFJet500_/I");
        tree->Branch( "HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_", &HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_, "HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_/I");
        tree->Branch( "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_", &HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_, "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_/I");
        tree->Branch( "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_", &HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_/I");
        tree->Branch( "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_", &HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_/I");
        tree->Branch( "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_", &HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_, "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_/I");
        tree->Branch( "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_", &HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_/I");

}

void objectTSelectorForNanoAOD::SelectMuons(std::vector<TLorentzVector> &SelectedMuons,   std::vector<Int_t> &SelectedMuonsIndex,const Int_t type) { 
  // changed ISO to ss of TTTT
  // 0 for Loose; 1 fakeble; 2 tight 
    for (UInt_t j = 0; j < Muon_pt.GetSize(); ++j) {
        //in objectSelection.h Muon_pt_ is global variable
        
        if(!(Muon_pt.At(j)>10))                     continue;
        if (!(fabs(Muon_eta.At(j)) < 2.4))        continue;
        //ID
        if (type == 0) {
            if ( !Muon_looseId.At(j) )              continue;
        }
        if (type == 1 or type == 2) {
            if ( !Muon_mediumId.At(j) )     continue;
        }
        //ISO
        if (type == 0 || type == 1) {

            if ( !( int(Muon_miniIsoId.At(j)) >= 1) ) continue;

        }
        if (type == 2) {

            if ( !( int(Muon_miniIsoId.At(j)) >=3) ) continue;

        }
        
        // IP
        if(!(fabs(Muon_dz.At(j))<0.1)) continue;
        if(!(fabs(Muon_dxy.At(j))<0.05)) continue;
        if(type == 1 or type == 2) {
          if(!(fabs(Muon_ip3d.At(j))<4)) continue;
        }
        
        //charge,The quality of the charge reconstruction 
        if ( type==1 || type==2 ){
            if ( !(Muon_tightCharge.At(j)==2) ) continue;
        }
        
        TLorentzVector muon;
        // muon.SetPtEtaPhiE(Muon_pt.At(j), Muon_eta.At(j), Muon_phi.At(j),
        muon.SetPtEtaPhiM(Muon_pt.At(j), Muon_eta.At(j), Muon_phi.At(j),
                          Muon_mass.At(j));
        SelectedMuons.push_back(muon);
        SelectedMuonsIndex.push_back(j);
    }
}


void objectTSelectorForNanoAOD::SelectElectronsMVA(std::vector<TLorentzVector> &SelectedElectrons,   std::vector<Int_t> &SelectedElectronsIndex, const Int_t type) {
  // 0 for VLoose; 1 for VLooseFO(fakeble object); 2 for tight
  // 2016 - MVANoIso94XV2, from SUSY
    for (UInt_t j = 0; j < Electron_pt.GetSize(); ++j) { /*{{{*/
        Double_t pt = Electron_pt.At(j);
        Double_t eta = Electron_eta.At(j);
        if (!(fabs(eta) < 2.5))      continue;
        if (!(pt > 10))         continue;
        if (!Electron_mvaFall17V2Iso_WP90.At(j)) continue; //note: after switching from SUSY ID to EGamma ID, there's no difference in ID between loose, fakeable and tight electrons
        //note bis: use *Iso* MVA discriminator, it comes from a MVA method trained with iso variables as input features. A WP on this discriminator implies ISO requirements

        // IP 
        if (!(fabs(Electron_dxy.At(j)) < 0.05))    continue;
        if (!(fabs(Electron_dz.At(j)) < 0.1))        continue;
        if (type == 1 or type == 2) {
            if (!((Electron_ip3d.At(j)) < 4))          continue;
        }
        
        //the number of missing pixel hits and a conversion veto based on the vertex fit probability. To reject electrons originating from photon conversion
        if (type == 0)
        {
            if ( !(int(Electron_lostHits.At(j))<=1) )  continue;
        }
        if ( type==1 || type==2 ){
            if ( !(int(Electron_lostHits.At(j))==0))  continue;
        }
        if ( !Electron_convVeto.At(j) ) continue;
        // tight charge
        //Electron_tightCharge	Int_t	Tight charge criteria (0:none, 1:isGsfScPixChargeConsistent, 2:isGsfCtfScPixChargeConsistent)
        //???not sure which one to use, drop for now
      
        TLorentzVector electron;
        electron.SetPtEtaPhiM(Electron_pt.At(j), Electron_eta.At(j), Electron_phi.At(j), Electron_mass.At(j));
        SelectedElectrons.push_back(electron);
        SelectedElectronsIndex.push_back(j);
    }
}
/*}}}*/


// void objectTSelectorForNanoAOD::SelectTaus(std::vector<TLorentzVector> &SelectedTaus, std::vector<Float_t> tauESFactors, std::vector<Float_t> tauFESFactors, std::vector<Int_t> &SelectedTausIndex, std::vector<Int_t> &SelectedTausDecayMode, std::vector<Int_t> &SelectedTausGenPartFlav, const Int_t TauWP, const std::vector<TLorentzVector> LeptonsMVAL) {
void objectTSelectorForNanoAOD::SelectTaus(std::vector<TLorentzVector> &SelectedTaus, std::vector<TLorentzVector>& taus_TESup, std::vector<TLorentzVector>& taus_TESdown,  std::vector<Int_t> &SelectedTausIndex, std::vector<Int_t> &SelectedTausDecayMode, std::vector<Int_t> &SelectedTausGenPartFlav, const Int_t TauWP, const std::vector<TLorentzVector> LeptonsMVAL) {
  // this is tau ID in ttH
  // 1:loose;2:fakeble;3:tight
  
  for (UInt_t j = 0; j < Tau_pt.GetSize(); ++j) {/*{{{*/
      
    // if (!(Tau_pt.At(j)*tauESFactors.at(j)*tauFESFactors.at(j) > 20))     continue;
    if (!(Tau_pt.At(j)*taus_TES.at(j) > 20))     continue;
    if (!(Tau_eta.At(j) < 2.3 && Tau_eta.At(j) > -2.3))      continue;
    if (!( TMath::Abs(Tau_dz.At(j)) < 0.2) )      continue; 
    //???why no dxy requirement?
    // if (!(Tau_idDecayModeOldDMs.At(j) == 0))      continue;//already in NANOAOD
    if (TauWP == 2 || TauWP == 3) {
       if( Tau_decayMode.At(j) == 5 || Tau_decayMode.At(j) == 6)      continue;} // for decay mode
    if (TauWP == 1) {
      bool isVSjetVVLoose = Tau_idDeepTau2017v2p1VSjet.At(j) & (1 << 1); //check if the 2nd bit (VVLoose WP) is 1
      if (!isVSjetVVLoose)        continue;
      // bitmask 1 = VVVLoose, 2 = VVLoose, 4 = VLoose, 8 = Loose, 16 = Medium, 32 = Tight, 64 = VTight, 128 = VVTight
    }
    if (TauWP == 2) {
        bool isVSjetVVLoose = Tau_idDeepTau2017v2p1VSjet.At(j) & (1 << 1); //check if the 2nd bit (VVLoose WP) is 1
        bool isVSeVVVLoose = Tau_idDeepTau2017v2p1VSe.At(j) & (1 << 0); //check if the 1st bit (VVVLoose WP) is 1
        bool isVSmuVLoose = Tau_idDeepTau2017v2p1VSmu.At(j) & (1 << 0); //check if the 1st bit (VLoose WP) is 1
      if ( !( isVSjetVVLoose && isVSeVVVLoose && isVSmuVLoose ) )        continue;
    }
    if (TauWP == 3) { // channel specific in ttH. use the tight from 1t 1l
        
        bool isVSjetM = Tau_idDeepTau2017v2p1VSjet.At(j) & (1 << 4); //check if the 5th bit (Medium WP) is 1
        bool isVSeVVVLoose = Tau_idDeepTau2017v2p1VSe.At(j) & (1 << 0); //check if the 1st bit (VVVLoose WP) is 1
        bool isVSmuVLoose = Tau_idDeepTau2017v2p1VSmu.At(j) & (1 << 0); //check if the 1st bit (VLoose WP) is 1
        if ( !( isVSjetM && isVSeVVVLoose && isVSmuVLoose ) )        continue;
    }
    //overlap removal
    Double_t minDeltaR_lep;
    if ( LeptonsMVAL.size() > 0){
        minDeltaR_lep = deltRmin(Tau_eta.At(j), Tau_phi.At(j), LeptonsMVAL);
        if( !(minDeltaR_lep >= 0.4 )) continue;
    }
    //?need err handling
    TLorentzVector tau;
    tau.SetPtEtaPhiM(Tau_pt.At(j), Tau_eta.At(j), Tau_phi.At(j), Tau_mass.At(j));
    // tau *= tauESFactors.at(j); //apply TES correction
    // tau *= tauFESFactors.at(j); //apply FES correction
    TLorentzVector itau  = taus_TES.at(j)*tau;
    
 
    //???is is correct to apply in vector?
    // do we require gennuine electron? we do, in the TES class
    SelectedTaus.push_back(itau);
    taus_TESup.push_back(tau*taus_TES_up.at(j));
    taus_TESdown.push_back(tau*taus_TES_down.at(j));
    SelectedTausIndex.push_back(j);
    SelectedTausDecayMode.push_back(Tau_decayMode.At(j));
    SelectedTausGenPartFlav.push_back(Tau_genPartFlav.At(j));
  }
}/*}}}*/


void objectTSelectorForNanoAOD::SelectJets(const Int_t jetType, const bool deepJet,  std::vector<TLorentzVector> &SelectedJets, std::vector<Double_t> &SelectedJetsBTags, std::vector<Int_t> &SelectedJetsIndex, std::vector<Int_t> &SelectedJetsFlavor,  const std::vector<TLorentzVector> LeptonsMVAF, const std::vector<TLorentzVector> SelectedTausL,  const Int_t sysJEC  ) {
    // jetType=0  -> usual jets; we use loose ID
    // jetType=11 -> b-jets L, jetType=12 -> b-jets M, jetType=13 -> b-jets T, jetType=2  -> forward jets
    Double_t MaxMostForwardJetEta = -99; 
    for (UInt_t j = 0; j < Jet_pt.GetSize(); ++j) {
        Double_t jetpt = Jet_pt[j]*JER_SF_new.at(j);
        switch (sysJEC)
        {
        case 0:
            jetpt = jetpt;
            break;
        case 1:
            jetpt = jetpt * (1 + jets_JESuncer[j]);
            break;
        case 3:
            jetpt *= (1 - jets_JESuncer[j]);
        default:
            break;
        }
        //here SF_up or SF_down should also be apllied.
        if (!(jetpt > 25))       continue;
        if (!(fabs(Jet_eta.At(j)) < 5.0))   continue;
        // cout << "jetId = " << Jet_jetId.At(j)<<"\n";
        if (!(Jet_jetId.At(j) >0)) continue;//Jet ID flags bit1 is loose (always false in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
        //Jet ID flags bit1 is loose (always ：wfalse in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
        //passlooseID*1+passtightID*2+passtightLepVetoID*4

        if ( jetType == 11 || jetType == 12 || jetType == 13 ) {
            if( !( fabs(Jet_eta.At(j))<2.4) ) continue;
        }
        if (deepJet) {//https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
            if (jetType == 11) {
                if (!(Jet_btagDeepFlavB.At(j) > DeepJetL[era]))
                    continue;
            }
            if (jetType == 12) {
                if (!(Jet_btagDeepFlavB.At(j) > DeepJetM[era]))
                    continue;
            }
            if (jetType == 13) {
                if (!(Jet_btagDeepFlavB.At(j) > DeepJetT[era]))
                    continue;
            }
        } else {
            if (jetType == 11) {
                if (!(Jet_btagDeepB.At(j) > DeepCSVL[era]))
                    continue;
            }
            if (jetType == 12) {
                if (!(Jet_btagDeepB.At(j) > DeepCSVM[era]))
                    continue;
            }
            if (jetType == 13) {
                if (!(Jet_btagDeepB.At(j) > DeepCSVT[era]))
                    continue;
            }
        }
        // find mostforwardjeteta
        if (jetType == 0) { // normal jet
            if (fabs(Jet_eta.At(j)) > MaxMostForwardJetEta) {
                MaxMostForwardJetEta = fabs(Jet_eta.At(j));
            } // MostForwardJetEta branch in new tree and SB.
            if (!(fabs(Jet_eta.At(j)) < 2.4))
                continue;
        }
        if (jetType == 2) { // forwardjet
            if (!(fabs(Jet_eta.At(j)) >= 2.4 && fabs(Jet_eta.At(j)) <= 5))       continue;
            if (!(jetpt > 25))             continue;
            if (fabs(Jet_eta.At(j)) >= 2.7 && fabs(Jet_eta.At(j)) <= 3.0) {
                if (!(jetpt > 60.0))      continue;
            }
        }
        // overlap removal
        if ( LeptonsMVAF.size()>0 ){
            Double_t deltaR = 0;
                Double_t minDeltaR = 100;
                for (UInt_t lep = 0; lep < LeptonsMVAF.size(); lep++){
                    deltaR =  DeltaR( LeptonsMVAF[lep].Eta(), Jet_eta.At(j), LeptonsMVAF[lep].Phi(), Jet_phi.At(j));
                        if ( deltaR < minDeltaR ) minDeltaR = deltaR ;//The continue statement provides a convenient way to jump to the end of the loop body for the current iteration.
                }
            if ( !( minDeltaR >= 0.4 ) ) continue;
        }
        if ( SelectedTausL.size()>0 ){
            Double_t deltaR_tau =0;
                Double_t minDeltaR_tau = 100;
                for ( UInt_t tau = 0; tau < SelectedTausL.size(); tau++){
                    deltaR_tau =  DeltaR( SelectedTausL[tau].Eta(), Jet_eta.At(j), SelectedTausL[tau].Phi(), Jet_phi.At(j));
                        if ( deltaR_tau < minDeltaR_tau ) minDeltaR_tau = deltaR_tau;
                }
            if ( !(minDeltaR_tau >= 0.4)) continue;
        }
        
        TLorentzVector jet_prov;
        jet_prov.SetPtEtaPhiM(Jet_pt.At(j), Jet_eta.At(j), Jet_phi.At(j), Jet_mass.At(j));
        TLorentzVector jet;
        // jet.SetPxPyPzE(jet_prov.Px() * jetSmearingFactors.at(j), jet_prov.Py() * jetSmearingFactors.at(j), jet_prov.Pz() * jetSmearingFactors.at(j), jet_prov.E() * jetSmearingFactors.at(j));
        jet.SetPxPyPzE(jet_prov.Px() * JER_SF_new.at(j), jet_prov.Py() * JER_SF_new.at(j), jet_prov.Pz() * JER_SF_new.at(j), jet_prov.E() * JER_SF_new.at(j));
        SelectedJets.push_back(jet);

        TLorentzVector ijet_JERup;
        Double_t iJER_up = JER_SF_new_up.at(j);
        ijet_JERup.SetPxPyPzE(jet_prov.Px() * iJER_up, jet_prov.Py() * iJER_up, jet_prov.Pz() * iJER_up, jet_prov.E() * iJER_up);
        jets_JERup.push_back( ijet_JERup );
        TLorentzVector ijet_JERdown;
        Double_t iJER_down = JER_SF_new_down.at(j);
        ijet_JERdown.SetPxPyPzE(jet_prov.Px() * iJER_down, jet_prov.Py() * iJER_down, jet_prov.Pz() * iJER_down, jet_prov.E() * iJER_down);
        jets_JERdown.push_back( ijet_JERdown );

        SelectedJetsIndex.push_back(j);
        //CHANGE HERE TO RUN ON DATA
		SelectedJetsFlavor.push_back(Jet_hadronFlavour.At(j));
        if (deepJet) {
            SelectedJetsBTags.push_back(Jet_btagDeepFlavB.At(j));
        } else {
            SelectedJetsBTags.push_back(Jet_btagDeepB.At(j));
        }
    }

}








void objectTSelectorForNanoAOD::selectGenTaus( std::vector<TLorentzVector> &genTaus ){
    for (UInt_t j = 0; j < GenPart_pt.GetSize(); ++j) {
        if(!(abs(GenPart_genPartIdxMother.At(j))==24 && abs(GenPart_pdgId.At(j))==15)) continue;//tau:15; top:6;W:
        TLorentzVector gentau;
        gentau.SetPtEtaPhiM(GenPart_pt.At(j), GenPart_eta.At(j), GenPart_phi.At(j), GenPart_mass.At(j));
        genTaus.push_back(gentau);
    }
}
void objectTSelectorForNanoAOD::selectGenEles( std::vector<TLorentzVector> &genEles ){
    for (UInt_t j = 0; j < GenPart_pt.GetSize(); ++j) {
        if(!(abs(GenPart_genPartIdxMother.At(j))==24 && abs(GenPart_pdgId.At(j))==11)) continue;//tau:15; ele:11;
        TLorentzVector genele;
        genele.SetPtEtaPhiM(GenPart_pt.At(j), GenPart_eta.At(j), GenPart_phi.At(j), GenPart_mass.At(j));
        genEles.push_back(genele);
    }
}
void objectTSelectorForNanoAOD::selectGenMuons( std::vector<TLorentzVector> &genMuons ){
    for (UInt_t j = 0; j < GenPart_pt.GetSize(); ++j) {
        if(!(abs(GenPart_genPartIdxMother.At(j))==24  && abs(GenPart_pdgId.At(j))==13)) continue;//tau:15; top:6;W:;muon:13
        TLorentzVector genmuon;
        genmuon.SetPtEtaPhiM(GenPart_pt.At(j), GenPart_eta.At(j), GenPart_phi.At(j), GenPart_mass.At(j));
        genMuons.push_back(genmuon);
    }
}

void objectTSelectorForNanoAOD::copyHLT_new(  const Bool_t isdata, const TString dataset ){


    HLT_IsoMu24_ = *HLT_IsoMu24;
    HLT_IsoMu27_ = *HLT_IsoMu27;

    if (era.CompareTo("2016preVFP")==0 || era.CompareTo("2016postVFP")==0) {
        HLT_PFHT450_SixJet40_BTagCSV_p056_ = *HLT_PFHT450_SixJet40_BTagCSV_p056 ;
        HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ = *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056;
        HLT_PFJet450_ = *HLT_PFJet450;
    }


    if ( !isdata){
         if( era.CompareTo("2018")==0){
             //should be the same as in intializaTreeBranches
                HLT_PFHT1050_ = *HLT_PFHT1050;//297050	306460; 315257	325172
                HLT_PFJet500_ = *HLT_PFJet500;
                HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_ = *HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5;
                HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = *HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59;
                HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ = *HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94;
         }

    }else{ //data
        if (  *run>=315257 && *run<=325173   ){
            //2018
            HLT_PFHT1050_ = *HLT_PFHT1050;//297050	306460; 315257	325172
            HLT_PFJet500_ = *HLT_PFJet500;
            HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_ = *HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5;
            if ( *run<315974 ){
                HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ = *HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5;
                HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = *HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2;

            }else if( *run<317509 ){
                HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_ = *HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5;
                HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = *HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2;
            }else{
                HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = *HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59;
                HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ = *HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94;
            }
        }
    }
}


void objectTSelectorForNanoAOD::copyFlags(){
    Flag_goodVertices_ = *Flag_goodVertices;
    Flag_globalSuperTightHalo2016Filter_ = *Flag_globalSuperTightHalo2016Filter;
    Flag_HBHENoiseFilter_ = *Flag_HBHENoiseFilter;
    Flag_HBHENoiseIsoFilter_ = *Flag_HBHENoiseIsoFilter;
    Flag_EcalDeadCellTriggerPrimitiveFilter_ = *Flag_EcalDeadCellTriggerPrimitiveFilter;
    Flag_BadPFMuonFilter_ = *Flag_BadPFMuonFilter;
    Flag_eeBadScFilter_ = *Flag_eeBadScFilter;

}

void objectTSelectorForNanoAOD::initializeBrancheValues(){
    muonsL.clear(); muonsL_index.clear();
    muonsF.clear(); muonsF_index.clear();
    muonsT.clear(); muonsT_index.clear();
    eleMVAL.clear(); eleMVAL_index.clear();
    eleMVAF.clear(); eleMVAF_index.clear();
    eleMVAT.clear(); eleMVAT_index.clear();
    leptonsMVAF.clear();
    leptonsMVAT.clear();
    leptonsMVAL.clear();

    taus_TES.clear(); taus_TES_up.clear(); taus_TES_down.clear();
    tausL.clear(); tausL_index.clear(); tausL_genPartFlav.clear(); tausL_decayMode.clear();
    tausF.clear(); tausF_index.clear(); tausF_genPartFlav.clear(); tausF_decayMode.clear();
    tausT.clear(); tausT_index.clear(); tausT_genPartFlav.clear(); tausT_decayMode.clear();
    tausL_TESup.clear(); tausL_TESdown.clear();
    tausF_TESup.clear(); tausF_TESdown.clear();
    tausT_TESup.clear(); tausT_TESdown.clear();
    
    
    // tausL_TESUp.clear(); tausL_TESUp_index.clear(); tausL_TESUp_genPartFlav.clear(); tausL_TESUp_decayMode.clear();
    // tausF_TESUp.clear(); tausF_TESUp_index.clear(); tausF_TESUp_genPartFlav.clear(); tausF_TESUp_decayMode.clear();
    // tausT_TESUp.clear(); tausT_TESUp_index.clear(); tausT_TESUp_genPartFlav.clear(); tausT_TESUp_decayMode.clear();
    // tausL_TESDown.clear(); tausL_TESDown_index.clear(); tausL_TESDown_genPartFlav.clear(); tausL_TESDown_decayMode.clear();
    // tausF_TESDown.clear(); tausF_TESDown_index.clear(); tausF_TESDown_genPartFlav.clear(); tausF_TESDown_decayMode.clear();
    // tausT_TESDown.clear(); tausT_TESDown_index.clear(); tausT_TESDown_genPartFlav.clear(); tausT_TESDown_decayMode.clear();
    // tausL_FESUp.clear(); tausL_FESUp_index.clear(); tausL_FESUp_genPartFlav.clear(); tausL_FESUp_decayMode.clear();
    // tausF_FESUp.clear(); tausF_FESUp_index.clear(); tausF_FESUp_genPartFlav.clear(); tausF_FESUp_decayMode.clear();
    // tausT_FESUp.clear(); tausT_FESUp_index.clear(); tausT_FESUp_genPartFlav.clear(); tausT_FESUp_decayMode.clear();
    // tausL_FESDown.clear(); tausL_FESDown_index.clear(); tausL_FESDown_genPartFlav.clear(); tausL_FESDown_decayMode.clear();
    // tausF_FESDown.clear(); tausF_FESDown_index.clear(); tausF_FESDown_genPartFlav.clear(); tausF_FESDown_decayMode.clear();
    // tausT_FESDown.clear(); tausT_FESDown_index.clear(); tausT_FESDown_genPartFlav.clear(); tausT_FESDown_decayMode.clear();

    jets.clear();   jets_index.clear(); jets_flavour.clear(); jets_btags.clear();
    jets_JERup.clear(); jets_JERdown.clear();
    jets_JESuncer.clear();
    JER_SF_new.clear(); JER_SF_new_up.clear();
    JER_SF_new_down.clear();
    bjetsL.clear(); bjetsL_index.clear(); bjetsL_flavour.clear(); bjetsL_btags.clear(); 
    bjetsL_JERdown.clear();
    bjetsL_JERup.clear();
    bjetsM.clear(); bjetsM_JERup.clear();
    bjetsM_JERdown.clear();
    bjetsM_index.clear();
    bjetsM_flavour.clear();
    bjetsM_btags.clear();
    bjetsT.clear(); bjetsT_JERup.clear();
    bjetsT_JERdown.clear();
    bjetsT_index.clear();
    bjetsT_flavour.clear();
    bjetsT_btags.clear();
    forwardJets.clear();  forwardJets_index.clear(); forwardJets_flavour.clear(); forwardJets_btags.clear();
    forwardJets_JERup.clear(); forwardJets_JERdown.clear();
    nonbjetsL.clear();
    nonbjetsM.clear();
    nonbjetsT.clear();

    patElectron_charge_.clear();
    Tau_charge_.clear();
    Muon_charge_.clear();
    tops_toptagger.clear();
    EVENT_prefireWeight_ = -99;
    PUWeight_ = -99;
    PUWeight_Up = -99;
    PUWeight_Down = -99;
    EVENT_genWeight_ = -99;


    run_ = 0;

    HLT_PFHT450_SixJet40_BTagCSV_p056_ = -99;
    HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ = -99;
	HLT_PFJet450_= -99;
    HLT_IsoMu24_ = -99;
    HLT_IsoMu27_ = -99;



    //2018
    HLT_PFHT1050_ = -99;
    HLT_PFJet500_ = -99;
    HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_ = -99;
    HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ = -99;
    HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = -99;
    HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_ = -99;
    HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = -99;
    HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ = -99;

}

// void objectTSelectorForNanoAOD::setupInputFile( const Bool_t isdata, correction::CorrectionSet* cset_jerSF ){
void objectTSelectorForNanoAOD::setupInputFile(  ){
    #include "inputMap.h"

    std::cout<<"setting up input file now........\n";
    //jec files
    TString jsonBase = "../../jsonpog-integration/POG/";
    // std::string jer_file = "../../jsonpog-integration/POG/JME/2016preVFP_UL/jet_jerc.json";
    //same file for JER and JES
    // cset_jerSF = correction::CorrectionSet::from_file(jer_file);
    cset_jerSF = correction::CorrectionSet::from_file( (jsonBase + json_map[era].at(0)).Data() );
	for (auto& corr : *cset_jerSF) {
        printf("JEC Correction : %s\n", corr.first.c_str());
    }

	// TString tauSF_json = "../../jsonpog-integration/POG/TAU/2016preVFP_UL/tau.json" ;
	// cset_tauSF = correction::CorrectionSet::from_file(tauSF_json.Data());
	cset_tauSF = correction::CorrectionSet::from_file( (jsonBase + json_map[era].at(1)).Data() );
	for (auto& corr : *cset_tauSF) {
        printf("tauSF Correction: %s\n", corr.first.c_str());
    }





    if ( !isdata ){
        // TString jetSmearing_PtFile = "../smearing/UL2016_postVFP/Summer20UL16_JRV3_MC_PtResolution_AK4PFchs.txt";
        // TString jetSmearing_MCFile = "../smearing/UL2016_postVFP/Summer20UL16_JRV3_MC_SF_AK4PFchs.txt";

        //Set up branch for pileup correction
        if ( era.CompareTo("2016postVFP")==0 ){
                inputPUFile_data = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-postVFP-69200ub-99bins.root", "READ");
                inputPUFile_dataUp = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-postVFP-72400ub-99bins.root", "READ");
                inputPUFile_dataDown = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-postVFP-66000ub-99bins.root", "READ");
                inputPUFile_mc = new TFile("../data_rootFiles/PUHistogram_mc2016_postVFP.root", "READ");

                // jetSmearing_PtFile = "../data_rootFiles/smearing/UL2016_postVFP/Summer20UL16_JRV3_MC_PtResolution_AK4PFchs.txt";
                // jetSmearing_MCFile = "../data_rootFiles/smearing/UL2016_postVFP/Summer20UL16_JRV3_MC_SF_AK4PFchs.txt";
        }else if( era.CompareTo("2016preVFP")==0 ){
                inputPUFile_data = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-preVFP-69200ub-99bins.root", "READ");
                inputPUFile_dataUp = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-preVFP-72400ub-99bins.root", "READ");
                inputPUFile_dataDown = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-preVFP-66000ub-99bins.root", "READ");
                inputPUFile_mc = new TFile("../data_rootFiles/PUHistogram_mc2016_preVFP.root", "READ");

                // jetSmearing_PtFile = "../data_rootFiles/smearing/UL2016_preVFP/Summer20UL16APV_JRV3_MC_PtResolution_AK4PFchs.txt";
                // jetSmearing_MCFile = "../data_rootFiles/smearing/UL2016_preVFP/Summer20UL16APV_JRV3_MC_SF_AK4PFchs.txt";

        }else if( era.CompareTo("2017")==0 ){
                inputPUFile_data = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2017-69200ub-99bins.root", "READ");
                inputPUFile_dataUp = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2017-72400ub-99bins.root", "READ");
                inputPUFile_dataDown = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2017-66000ub-99bins.root", "READ");
                inputPUFile_mc = new TFile("../data_rootFiles/PUHistogram_mc2017.root", "READ");

                // jetSmearing_PtFile = "../dada_rootFiles/smearing/UL2017/Summer19UL17_JRV3_MC_PtResolution_AK4PFchs.txt";
                // jetSmearing_MCFile = "../data_rootFiles/smearing/UL2017/Summer19UL17_JRV3_MC_SF_AK4PFchs.txt";

        }else if( era.CompareTo("2018")==0 ){
                inputPUFile_data = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2018-69200ub-99bins.root", "READ");
                inputPUFile_dataUp = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2018-72400ub-99bins.root", "READ");
                inputPUFile_dataDown = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2018-66000ub-99bins.root", "READ");
                inputPUFile_mc = new TFile("../data_rootFiles/PUHistogram_mc2018.root", "READ");

                // jetSmearing_PtFile = "../data_rootFiles/smearing/UL2018/Summer19UL18_JRV2_MC_PtResolution_AK4PFchs.txt";
                // jetSmearing_MCFile = "../data_rootFiles/smearing/UL2018/Summer19UL18_JRV2_MC_SF_AK4PFchs.txt";
        }
        std::cout << "pileup file used : " << inputPUFile_data->GetName() << "\n";
        // std::cout<<"jetSmearing file used: "<<jetSmearing_PtFile<<"\n"<<jetSmearing_MCFile<<"\n";
        //Get needed histograms
        dataPileupProfile = (TH1F *)inputPUFile_data->Get("pileup");
        dataPileupProfileUp = (TH1F *)inputPUFile_dataUp->Get("pileup");
        dataPileupProfileDown = (TH1F *)inputPUFile_dataDown->Get("pileup");
        MCPileupProfile = (TH1F *)inputPUFile_mc->Get("pileup");
        //Scale to unit area for a fair comparison
        dataPileupProfile->Scale(1.0 / dataPileupProfile->Integral());
        dataPileupProfileUp->Scale(1.0 / dataPileupProfileUp->Integral());
        dataPileupProfileDown->Scale(1.0 / dataPileupProfileDown->Integral());
        MCPileupProfile->Scale(1.0 / MCPileupProfile->Integral());

        // readSmearingFile( jetSmearing_PtFile, resolution, resFormula );
        // readSmearingFile( jetSmearing_MCFile, resSFs, toyResFormula );

    }else{
        std::cout<<"data not setting up jetSmearing and pile files"<<"\n";
    }


    std::cout<<"done setting input file........................\n";

}

void objectTSelectorForNanoAOD::getOptionFromRunMacro( const TString option ){

   TString option1 = option(0, option.First(":"));
    TString temp = option;
    TString option2 = temp.Remove(0, option.First(":")+1);
    option2 = option2(0, option2.First(":"));
    // std::cout<<"temp: "<<temp<<"\n";
    TString option3 = temp.Remove(0, temp.First(":")+1);
    option3 = option3(0, option3.First(":"));
    TString option4 = temp.Remove(0, temp.First(":")+1 );
    option4 = option4(0, option4.First(":"));
    TString option5 = temp.Remove(0, temp.First(":")+1 );

    std::cout << "option1: " << option1 << "\n";
    std::cout << "option2: " << option2 << "\n";
    std::cout<<"option3: "<<option3<<"\n";
    std::cout<<"option4: "<<option4<<"\n";
    std::cout<<"option5: "<<option5<<"\n";


   era = option2;
   std::cout << "era is: " << era << "\n";
   if ( option4.CompareTo( "0")==0 ) isdata = false;
   else isdata = true;
   std::cout<<"isdata  in TSelector: "<<isdata<<"\n"; 
   dataSet = option5;
   Int_t eventSelection = std::stoi( option3.Data() );
   // 1 for MetFilters, 2 for HLTSelection, 4 for preSelection. so 7 if all selection; 0 if no selection 
   std::cout<<"eventSelection in selector: "<<eventSelection<<"\n";
    // switch ( eventSelection ){
    //     case 0:
    //         MetFilters = false; HLTSelection = false; preSelection = false;
    //         return;
    //     case 1:
    //         MetFilters = true; HLTSelection = false; preSelection = false;
    //         return;
    //     case 2:
    //         MetFilters = false; HLTSelection = true; preSelection = false;
    //         return;
    //     case 3:
    //         MetFilters = true; HLTSelection = true; preSelection = false;
    //         return;
    //     case 4:
    //         MetFilters = false; HLTSelection = false; preSelection = true;
    //         return;
    //     case 5:
    //         MetFilters = true; HLTSelection = false; preSelection = true;
    //         return;
    //     case 6:
    //         MetFilters = false; HLTSelection = true; preSelection = true;
    //         return;
    //     case 7:
    //         MetFilters = true; HLTSelection = true; preSelection = true;
    //         return;
    // }
        if ( eventSelection ==  0) {
            MetFilters = false; HLTSelection = false; preSelection = false;
        }
        if ( eventSelection ==  1 ) {
            MetFilters = true; HLTSelection = false; preSelection = false;
        }
        if ( eventSelection ==  2 ) {
            MetFilters = false; HLTSelection = true; preSelection = false;
        }
        if ( eventSelection ==  3 ) {
            MetFilters = true; HLTSelection = true; preSelection = false;
        }
        if ( eventSelection ==  4 ) {
            MetFilters = false; HLTSelection = false; preSelection = true;
        }
        if ( eventSelection ==  5 ) {
            MetFilters = true; HLTSelection = false; preSelection = true;
        }
        if ( eventSelection ==  6 ) {
            MetFilters = false; HLTSelection = true; preSelection = true;
        }
        if ( eventSelection ==  7 ) {
            MetFilters = true; HLTSelection = true; preSelection = true;
        }
    std::cout<<"MetFilters = "<<MetFilters<<"; HLTSelection = "<<HLTSelection<<"; preSelection = "<<preSelection<<"\n";
   TString outFileName = option1;
   outputfile = new TFile( outFileName, "RECREATE");
   std::cout<<"outputFileName: "<<outputfile->GetName()<<"\n";
}

void objectTSelectorForNanoAOD::getRunRange( TTree* fChain ){
    TH1F* runHist = new TH1F( "runHist", "runHist",  52412, 272760,  325172 );  //324581 range from 2016run to 2018
    fChain->Project( "runHist", "run" );
    std::cout<<"tree Name: "<<fChain->GetName()<<"\n";
    // std::cout<<"Min in runHist: "<<runHist->GetMinimum()<<"\n";//GetMaximum returns the maximum along Y, not along X
    // std::cout<<"run entries:"<<runHist->GetEntries()<<"\n";
    runRange[0] =  272760 - 1 +runHist->FindFirstBinAbove();
    runRange[1] = 272760-1 + runHist->FindLastBinAbove();
    //histogram can not give us the accurate run range
    delete runHist;
    /*
    UInt_t runMin = 400000;
    UInt_t runMax = 1;
    // fChain->SetBranchStatus("*", false);
    fChain->SetBranchStatus("run", true);
    UInt_t runInBegin;
    fChain->SetBranchAddress( "run", &runInBegin );
    for (int iEntry = 0; fChain->LoadTree(iEntry) >= 0; ++iEntry) {
        // Load the data for the given tree entry
        fChain->GetEntry(iEntry);
        if( runInBegin< runMin ){
            runMin = runInBegin;
        }
        if ( runInBegin > runMax ){
            runMax = runInBegin;
        }
    }
    runRange[0] = runMin;
    runRange[1] = runMax;
    */

// 
}


void objectTSelectorForNanoAOD::intializaTreeBranches( const Bool_t isdata, const TString dataset ){
    //overriding for MC files

    HLT_IsoMu24 = { fReader, "HLT_IsoMu24"};
    HLT_IsoMu27 = { fReader, "HLT_IsoMu27"};

    if (era.CompareTo("2016preVFP")==0 || era.CompareTo("2016postVFP")==0) {
        HLT_PFHT450_SixJet40_BTagCSV_p056 = { fReader, "HLT_PFHT450_SixJet40_BTagCSV_p056"};
        HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = { fReader, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056"};
        HLT_PFJet450 = { fReader, "HLT_PFJet450"};
    }

   if( !isdata ){
       std::cout<<"running over: MC"<<"\n";
        GenJet_eta = {fReader, "GenJet_eta"};
        GenJet_phi = {fReader, "GenJet_phi"};
        GenJet_pt = {fReader, "GenJet_pt"};
        nGenPart = {fReader, "nGenPart"};
        GenPart_eta = {fReader, "GenPart_eta"};
        GenPart_mass = {fReader, "GenPart_mass"};
        GenPart_phi = {fReader, "GenPart_phi"};
        GenPart_pt = {fReader, "GenPart_pt"};
        GenPart_genPartIdxMother = {fReader, "GenPart_genPartIdxMother"};
        GenPart_pdgId = {fReader, "GenPart_pdgId"};
        Generator_weight = {fReader, "Generator_weight"};
        genWeight = {fReader, "genWeight"};
         Pileup_nTrueInt = {fReader, "Pileup_nTrueInt"};
        Jet_hadronFlavour = {fReader, "Jet_hadronFlavour"};
         Tau_genPartFlav = {fReader, "Tau_genPartFlav"};
         genTtbarId = {fReader, "genTtbarId"};
         //HLT for MC

         if (era.CompareTo("2018")==0) {
           
             HLT_PFHT1050 = { fReader, "HLT_PFHT1050"};//297050	306460; 315257	325172
             HLT_PFJet500 = { fReader, "HLT_PFJet500"};
             HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 = { fReader, "HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5"};

            // HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = { fReader, "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5"};//checked
            // HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = { fReader, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5"};//checked
            HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 = { fReader, "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59"};

            // HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = {fReader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"};
            HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 = { fReader, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94"};
         }


   }else{//data
        std::cout<<"running over: "<<dataSet<<"\n";

        if ( runRange[0] >= 315257 && runRange[1]<=325172  ){ //2018
            //we are assuming no nanoAOD file has triggers cross ranges
                // if the condition is false, the program is terminated and an error message is displayed.
            // assert( !(runRange[0]<315974 && runRange[1]>315974) );
            // assert( !(runRange[0]<317509 && runRange[1]>317509) );
            assert( !(runRange[0]<315974 && runRange[1]>=317509) );

            HLT_PFHT1050 = { fReader, "HLT_PFHT1050"};//297050	306460; 315257	325172
            HLT_PFJet500 = { fReader, "HLT_PFJet500"};
            HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 = { fReader, "HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5"};
            if ( runRange[1]<315974 ){
                HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = { fReader, "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5"};//checked
                HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = {fReader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"};
            }else if( runRange[0]>=315974 && runRange[1]<317509 ){
                HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = { fReader, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5"};//checked
                HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = {fReader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"};
            }else if( runRange[0]>=317509 && runRange[1]<325173)	{
                HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 = { fReader, "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59"};
                HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 = { fReader, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94"};
            }else if( runRange[0]<315974 && 315974<=runRange[1] && runRange[1]<317509 ){
                HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = { fReader, "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5"};//checked
                HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = { fReader, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5"};//checked
                HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = {fReader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"};
            }else if( 315974<=runRange[0] && runRange[0]<317509  && 317509<=runRange[1]&&runRange[1]<325173 ){
                HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = { fReader, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5"};//checked
                HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 = { fReader, "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59"};
                HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = {fReader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"};
                HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 = { fReader, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94"};
            }




        }

   
   }
}

/*
void objectTSelectorForNanoAOD::calJetSmearFactors( const Bool_t isdata  ){
    std::vector<Int_t>* matchingIndices   { new std::vector<Int_t>} ;
    getMatchingToGen(Jet_eta, Jet_phi, GenJet_eta, GenJet_phi, matchingIndices); //if a reco jet is unmatched, the corresponding gen jet pt will be 0
    jetSmearingFactors.clear();
    jetSmearingFactorsUp.clear();
    jetSmearingFactorsDown.clear();
    Float_t smearFactor = 1.0;
    Float_t smearFactorUp = 1.0;
    Float_t smearFactorDown = 1.0;
    for (UInt_t i = 0; i < *nJet; i++) {
        if ( !isdata ){
            Float_t resSF = GetJerFromFile(Jet_eta.At(i), resSFs, 0);
            Float_t resSFUp = GetJerFromFile(Jet_eta.At(i), resSFs, 2);
            Float_t resSFDown = GetJerFromFile(Jet_eta.At(i), resSFs, 1);
            smearFactor = GetSmearFactor(Jet_pt.At(i), GenJet_pt.At(matchingIndices->at(i)), Jet_eta.At(i), *fixedGridRhoFastjetAll, resSF, resolution, resFormula, jet_jer_myran);
            smearFactorUp = GetSmearFactor(Jet_pt.At(i), GenJet_pt.At(matchingIndices->at(i)), Jet_eta.At(i), *fixedGridRhoFastjetAll, resSFUp, resolution, resFormula, jet_jer_myran);
            smearFactorDown = GetSmearFactor(Jet_pt.At(i), GenJet_pt.At(matchingIndices->at(i)), Jet_eta.At(i), *fixedGridRhoFastjetAll, resSFDown, resolution, resFormula, jet_jer_myran);
        }else{
            smearFactor = 1.0;
            smearFactorUp = 1.0;
            smearFactorDown = 1.0;
        }
        jetSmearingFactors.push_back(smearFactor);
        jetSmearingFactorsUp.push_back(smearFactorUp);
        jetSmearingFactorsDown.push_back(smearFactorDown);

    }
    delete matchingIndices;

}
*/

void objectTSelectorForNanoAOD::calJER_SF( const Bool_t isdata, std::vector<Double_t>&  jer_sf, std::vector<Double_t>& jer_sf_up, std::vector<Double_t>& jer_sf_down, correction::CorrectionSet* cset_jerSF  ){
    //https://gitlab.cern.ch/cms-nanoAOD/jsonpog-integration/-/blob/master/examples/jercExample.py
    //https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution#JER_Scaling_factors_and_Uncertai
    #include "inputMap.h"
    // TString input = "Summer20UL16APV_JRV3_MC_ScaleFactor_AK4PFchs";
    // TString input = JER_SF_map[era] ;
    // auto corr_jerSF = cset_jerSF->at(input.Data());
    auto corr_jerSF = cset_jerSF->at( corr_SF_map[era].at(0).Data()  );

    // TString jesSFName = "Summer19UL16APV_V7_MC";
    // TString jesSFName_MC_L1 = jesSFName + TString("_L1FastJet_AK4PFchs");
    // TString jesSFName_MC_L1 = "Summer19UL16APV_V7_MC_L1FastJet_AK4PFchs";
    // auto corr_jesSF_L1 = cset_jerSF->at(jesSFName_MC_L1.Data());

    //???not sure how to get the JEC uncertainty for data yet?
    //https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/jetmetHelperRun2.py
    // TString unc = "Summer19UL16APV_V7_MC_Total_AK4PFchs";
    // auto corr_jesUncer = cset_jerSF->at(unc.Data());
    auto corr_jesUncer = cset_jerSF->at( corr_SF_map[era].at(1).Data() );
    //???does the MC_Total include the JER uncertainty?

    Double_t iSF = 1.0;
    Double_t iSF_up = 1.0;
    Double_t iSF_down = 1.0;
    Double_t iSF_JESuncer = 0.0;
    for (UInt_t i = 0; i < *nJet; i++)
    {
        Double_t ieta = Jet_eta.At(i);
        Double_t ipt = Jet_pt.At(i);
        // not in a pT-dependent format, strong pT dependency at high eta is however observed to be reduced in UL
        if ( !isdata ){
            //???it seems the evaluate is cause runtime issue
            iSF = corr_jerSF->evaluate( {Jet_eta.At(i), "nom"});
            iSF_up = corr_jerSF->evaluate( {Jet_eta.At(i), "up"});
            iSF_down = corr_jerSF->evaluate( {Jet_eta.At(i), "down"});

            // iSF_JES = corr_jesSF_L1->evaluate({ieta, ipt, "nom"});
            // iSF_JES = corr_jesSF_L1->evaluate({ Jet_area.At(i), ieta, ipt, 0.0 });
            iSF_JESuncer = corr_jesUncer->evaluate({ieta, ipt} );
        }
        // std::cout << "iJERSF: " << iSF << "\n";
        // std::cout<<"iSF_JES"<<iSF_JESuncer<<"\n";
        jer_sf.push_back(iSF);
        jer_sf_up.push_back(iSF_up);
        jer_sf_down.push_back(iSF_down);
        jets_JESuncer.push_back(iSF_JESuncer);
    }
}

void objectTSelectorForNanoAOD::calTauSF_new( ){
    //https://gitlab.cern.ch/cms-tau-pog/jsonpog-integration/-/blob/master/examples/tauExample.py
    auto corr_tauES = cset_tauSF->at("tau_energy_scale");
    //???i assume it contains the correction to genuine tau and genuine electrons?
    Double_t iTES_sf = 1.0;
    Double_t iTES_sf_up = 1.0;
    Double_t iTES_sf_down = 1.0;
    for (UInt_t i = 0; i < *nTau; i++) {
        if(!isdata){
            //corr4.evaluate(pt,eta,dm,5,"DeepTau2017v2p1",syst)
            //no sf for decaymode 5 and 6
            if( !(Tau_decayMode.At(i)==5 || Tau_decayMode.At(i)==6) ){
                iTES_sf = corr_tauES->evaluate( {Tau_pt.At(i), Tau_eta.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "DeepTau2017v2p1", "nom"} );
                iTES_sf_up = corr_tauES->evaluate( {Tau_pt.At(i), Tau_eta.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "DeepTau2017v2p1", "up"} );
                iTES_sf_down = corr_tauES->evaluate( {Tau_pt.At(i), Tau_eta.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "DeepTau2017v2p1", "down"} );
            }
            // std::cout << "iTES_sf: " << iTES_sf << "\n";
            // std::cout << "iTES_sf_up: " << iTES_sf_up << "\n";
            // std::cout << "iTES_sf_down: " << iTES_sf_down << "\n";
        }
        taus_TES.push_back(iTES_sf);
        taus_TES_up.push_back(iTES_sf_up);
        taus_TES_down.push_back(iTES_sf_down);
    }

}

/*
void objectTSelectorForNanoAOD::setupTauSFTool( const Bool_t isdata){
    if ( !isdata ){
        if ( era.CompareTo( "2016postVFP")==0 ){
        //    std::cout<<__LINE__<<"\n";
            TESTool = TauESTool("UL2016_postVFP","DeepTau2017v2p1VSjet");
            FESTool = TauFESTool("2016Legacy","DeepTau2017v2p1VSe"); //no measurement for 2016 UL, use ReReco instead

        }else if( era.CompareTo( "2016preVFP")==0 ){
            TESTool = TauESTool("UL2016_preVFP","DeepTau2017v2p1VSjet");
            FESTool = TauFESTool("2016Legacy","DeepTau2017v2p1VSe"); //no measurement for 2016 UL, use ReReco instead

        }else if( era.CompareTo("2017")==0 ){
            TESTool = TauESTool("UL2017","DeepTau2017v2p1VSjet");
            FESTool = TauFESTool("2017ReReco","DeepTau2017v2p1VSe"); //no measurement for 2017 UL, use ReReco instead

        }else if( era.CompareTo("2018")==0 ){
            TESTool = TauESTool("UL2018","DeepTau2017v2p1VSjet");
            FESTool = TauFESTool("2018ReReco","DeepTau2017v2p1VSe"); //no measurement for 2018 UL, use ReReco instead

        }

    }else{
        std::cout<<"data not setting up TauESTool or TAUFESTool"<<"\n";
    }

}


void objectTSelectorForNanoAOD::calTauSF( const Bool_t isdata ){
    tauESFactors.clear();
    tauESFactorsUp.clear();
    tauESFactorsDown.clear();
    tauFESFactors.clear();
    tauFESFactorsUp.clear();
    tauFESFactorsDown.clear();
    Float_t TESSF = 1.0;
    Float_t TESSFUp = 1.0;
    Float_t TESSFDown = 1.0;
    Float_t FESSF = 1.0;
    Float_t FESSFUp = 1.0;
    Float_t FESSFDown = 1.0;
    for (UInt_t i = 0; i < *nTau; i++) {
        if ( !isdata ){
            TESSF = TESTool.getTES(Tau_pt.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "");
            TESSFUp = TESTool.getTES(Tau_pt.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "Up");
            TESSFDown= TESTool.getTES(Tau_pt.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "Down");
        }
        tauESFactors.push_back(TESSF);
        tauESFactorsUp.push_back(TESSFUp);
        tauESFactorsDown.push_back(TESSFDown);
    }

    //misidentified electron energy scale (FES), fake taus which is genuine electrons
    for (UInt_t i = 0; i < *nTau; i++) {
        if ( !isdata ){
            FESSF = FESTool.getFES(Tau_eta.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "");
            FESSFUp = FESTool.getFES(Tau_eta.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "Up");
            FESSFDown= FESTool.getFES(Tau_eta.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "Down");
        }
        tauFESFactors.push_back(FESSF);
        tauFESFactorsUp.push_back(FESSFUp);
        tauFESFactorsDown.push_back(FESSFDown);
    }

}
*/