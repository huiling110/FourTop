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
// we should use a better way of modulization of code rather the include copy here
#include <TH2.h>
#include <TStyle.h>

#include <cassert>
#include "objectTSelectorForNanoAOD.h"
#include "utilityFunctions.h"
///////////////////////

void objectTSelectorForNanoAOD::Begin(TTree * /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
}

// void objectTSelectorForNanoAOD::SlaveBegin(TTree * /*tree*/)
void objectTSelectorForNanoAOD::SlaveBegin(TTree *fChain)
// void objectTSelectorForNanoAOD::SlaveBegin(TTree * fReader)
{
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
    std::cout << "option in TSelector : " << option << "\n";
    getOptionFromRunMacro(option);

    getRunRange(fChain);
    std::cout << "runRange: " << runRange[0] << ":" << runRange[1] << "\n";
    intializaTreeBranches(isdata, dataSet);

    //???

    h_forEY_initial = new TH1D("h_initial", "h_initial", 2, -1, 1);
    h_forEY_HLT = new TH1D("h_afterHLT", "h_afterHLT", 2, -1, 1);
    h_forEY_preSelection = new TH1D("h_afterpreSelection", "h_afterpreSelection", 2, -1, 1);

    newTree = new TTree("tree", "tree after object selection");

    makeBranch(newTree);

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
    Double_t basicWeight = 1.0;
    if (!isdata)
    {
        basicWeight = (*Generator_weight) * (*L1PreFiringWeight_Nom);
    }
    h_forEY_initial->Fill(0.0, basicWeight);

    if (!isdata)
    {
        genWeight_allEvents = *Generator_weight;
    }

    // good lumi selection
    //???todo: examination of selectGoodLumi()
    Bool_t ifGoodLumi = selectGoodLumi();
    if (!ifGoodLumi && isdata)
    {
        return kFALSE;
    }
    eventsPassedJSON++;

    // MET filters
    if (MetFilters)
    {
        // recommendations from here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#MET_Filter_Recommendations_for_R
        if (!(*Flag_goodVertices == 1))
            return kFALSE; // a branch in tree.
        if (!(*Flag_globalSuperTightHalo2016Filter == 1))
            return kFALSE;
        if (!(*Flag_HBHENoiseFilter == 1))
            return kFALSE;
        if (!(*Flag_HBHENoiseIsoFilter == 1))
            return kFALSE;
        if (!(*Flag_EcalDeadCellTriggerPrimitiveFilter == 1))
            return kFALSE; // a branch in Tree
        if (!(*Flag_BadPFMuonFilter == 1))
            return kFALSE;
        if (!(*Flag_BadPFMuonDzFilter == 1))
            return kFALSE;
        // if ( era == "2017" || era == "2018" ){
        if (!(*Flag_ecalBadCalibFilter == 1))
            return kFALSE; // for UL 2016 has this flag too
        // }
        // if (isdata) {  if (!(*Flag_eeBadScFilter == 1)) return kFALSE;}
        if (!(*Flag_eeBadScFilter == 1))
            return kFALSE; // for UL this filter exists for 2016 MC too
    }
    eventsPassedMETFilters++;
    copyFlags();

    // HLT

    if (HLTSelection)
    {
        if (era.CompareTo("2016preVFP") == 0 || era.CompareTo("2016postVFP") == 0)
        {
            // std::cout<<"HLT selection for 2016"<<"\n";
            if (!(*HLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1 || *HLT_PFJet450 == 1))
                return kFALSE;
        }
        else if (era.CompareTo("2018") == 0)
        {
            if (!isdata)
            {
                if (!(*HLT_PFJet500 == 1 || *HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 == 1 || *HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 == 1))
                    return kFALSE;
            }
            else
            {
                if (*run >= 315257 && *run <= 325173)
                {
                    // 2018
                    HLT_PFJet500_ = *HLT_PFJet500;
                    if (*run < 315974)
                    {
                        if (!(*HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 == 1 || *HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 == 1))
                            return kFALSE;
                    }
                    else if (*run < 317509)
                    {
                        if (!(*HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 == 1 || *HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 == 1))
                            return kFALSE;
                    }
                    else
                    {
                        if (!(*HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 == 1 || *HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 == 1))
                            return kFALSE;
                    }
                }
            }
        }
    }

    eventsPassedHLT++;
    h_forEY_HLT->Fill(0.0, basicWeight);

    //!!!very important to give value to default values to variables for each event!!!
    initializeBrancheValues();
    //!!!branch variable intialization to prevent them from get values from last event

    run_ = *run;
    event_ = *event;
    copyHLT_new(isdata, dataSet);

    // Compute the per-event PU weight
    //???todo: switch this to json
    if (!isdata)
    {
        if (MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(*Pileup_nTrueInt)) > 0)
        {
            PUWeight = dataPileupProfile->GetBinContent(dataPileupProfile->FindBin(*Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(*Pileup_nTrueInt));
            PUWeight_Up = dataPileupProfileUp->GetBinContent(dataPileupProfileUp->FindBin(*Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(*Pileup_nTrueInt));
            PUWeight_Down = dataPileupProfileDown->GetBinContent(dataPileupProfileDown->FindBin(*Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(*Pileup_nTrueInt));
        }
    }
    PV_npvs_ = *PV_npvs;
    PV_npvsGood_ = *PV_npvsGood;
    if (!isdata)
    {
        genTtbarId_ = *genTtbarId;
    }

    SelectMuons(muonsL, muonsL_index, 0);
    sort(muonsL.begin(), muonsL.end(), compEle);
    SelectMuons(muonsF, muonsF_index, 1);
    sort(muonsF.begin(), muonsF.end(), compEle);
    SelectMuons(muonsT, muonsT_index, 2);
    sort(muonsT.begin(), muonsT.end(), compEle);
    mounsT_total = mounsT_total + muonsT.size();
    mounsF_total = mounsF_total + muonsF.size();
    mounsL_total = mounsL_total + muonsL.size();

    SelectElectronsMVA(eleMVAT, eleMVAT_index, 2);
    SelectElectronsMVA(eleMVAF, eleMVAF_index, 1);
    SelectElectronsMVA(eleMVAL, eleMVAL_index, 0);
    sort(eleMVAL.begin(), eleMVAL.end(), compEle);
    sort(eleMVAF.begin(), eleMVAF.end(), compEle);
    sort(eleMVAT.begin(), eleMVAT.end(), compEle);
    elesT_total = elesT_total + eleMVAT.size();
    elesF_total = elesF_total + eleMVAF.size();
    elesL_total = elesL_total + eleMVAL.size();

    leptonsMVAF = muonsF;
    leptonsMVAF.insert(leptonsMVAF.end(), eleMVAF.begin(), eleMVAF.end());
    sort(leptonsMVAF.begin(), leptonsMVAF.end(), compEle);
    leptonsMVAT = muonsT;
    leptonsMVAT.insert(leptonsMVAT.end(), eleMVAT.begin(), eleMVAT.end());
    sort(leptonsMVAT.begin(), leptonsMVAT.end(), compEle);
    leptonsMVAL = muonsL;
    leptonsMVAL.insert(leptonsMVAL.end(), eleMVAL.begin(), eleMVAL.end());
    sort(leptonsMVAL.begin(), leptonsMVAL.end(), compEle);

    // nominal taus
    //  calTauSF( isdata );
    calTauSF_new(); // calculate taus_TES_up  taus_TES_down
    // Int_t tauTES = 4; // 4 means no TES
    Int_t tauTES = 0; //
    SelectTaus(tausL, tausL_index, tausL_decayMode, tausL_genPartFlav, 1, leptonsMVAL, tauTES);
    SelectTaus(tausF, tausF_index, tausF_decayMode, tausF_genPartFlav, 2, leptonsMVAL, tauTES);
    SelectTaus(tausT, tausT_index, tausT_decayMode, tausT_genPartFlav, 3, leptonsMVAL, tauTES);
    SelectTaus(tausT_TESup, tausT_index_TESup, tausT_decayMode_TESup, tausT_genPartFlav_TESup, 3, leptonsMVAL, 1);
    SelectTaus(tausT_TESdown, tausT_index_TESdown, tausT_decayMode_TESdown, tausT_genPartFlav_TESdown, 3, leptonsMVAL, 2);
    sort(tausT.begin(), tausT.end(), compEle);
    sort(tausF.begin(), tausF.end(), compEle);
    sort(tausL.begin(), tausL.end(), compEle);
    sort(tausT_TESup.begin(), tausT_TESup.end(), compEle);
    sort(tausT_TESdown.begin(), tausT_TESdown.end(), compEle);
    //  //???does here imply we need at least 1 leptons
    tausT_total = tausT_total + tausT.size();
    tausF_total = tausF_total + tausF.size();
    tausL_total = tausL_total + tausL.size();

    bool deepJet = true;
    calJetSmearFactors(isdata);                                                      // Duncan's way
    calJER_SF(isdata, JER_SF_new, JER_SF_new_up, JER_SF_new_down, cset_jerSF.get()); //???from json, needs more work

    Bool_t ifJER = kFALSE;
    // Bool_t ifJER = kTRUE;
    SelectJets(ifJER, 0, deepJet, jets, jets_btags, jets_index, jets_flavour, leptonsMVAL, tausL, 0);
    SelectJets(ifJER, 0, deepJet, jets_JECup, jets_btags_JECup, jets_index_JECup, jets_flavour_JECup, leptonsMVAL, tausL, 1);
    SelectJets(ifJER, 0, deepJet, jets_JECdown, jets_btags_JECdown, jets_index_JECdown, jets_flavour_JECdown, leptonsMVAL, tausL, 2);
    sort(jets.begin(), jets.end(), compEle);
    sort(jets_JECup.begin(), jets_JECup.end(), compEle);
    sort(jets_JECdown.begin(), jets_JECdown.end(), compEle);
    // std::cout << "jets size" << jets.size() << "\n";
    // printElements( jets_btags, jets );
    // std::cout<<"jets_JECup:  "; printElements( jets_btags_JECup, jets_JECup );
    // std::cout<<"jets_JECdown:  "; printElements( jets_btags_JECdown, jets_JECdown );
    // pt are sorted in MINIAOD
    SelectJets(ifJER, 11, deepJet, bjetsL, bjetsL_btags, bjetsL_index, bjetsL_flavour, leptonsMVAL, tausL, 0);
    SelectJets(ifJER, 12, deepJet, bjetsM, bjetsM_btags, bjetsM_index, bjetsM_flavour, leptonsMVAL, tausL, 0);
    SelectJets(ifJER, 13, deepJet, bjetsT, bjetsT_btags, bjetsT_index, bjetsT_flavour, leptonsMVAL, tausL, 0);
    SelectJets(ifJER, 2, deepJet, forwardJets, forwardJets_btags, forwardJets_index, forwardJets_flavour, leptonsMVAL, tausL, 0);
    sort(bjetsL.begin(), bjetsL.end(), compEle);
    sort(bjetsM.begin(), bjetsM.end(), compEle);
    sort(bjetsT.begin(), bjetsT.end(), compEle);

    jetsSubstructBjets(nonbjetsL, jets, bjetsL);
    jetsSubstructBjets(nonbjetsM, jets, bjetsM);
    jetsSubstructBjets(nonbjetsT, jets, bjetsT);
    // cout<<"nonb="<<nonbjetsL.size()<<" bjet="<<bjetsL.size()<<" jets="<<jets.size()<<endl;
    jets_total = jets_total + jets.size();
    bjetsM_total = bjetsM_total + bjetsM.size();

    if (Electron_charge.GetSize() > 0)
    {
        copy_TTreeReaderArray_toVector(Electron_charge, patElectron_charge_);
    }
    if (Tau_charge.GetSize() > 0)
    {
        copy_TTreeReaderArray_toVector(Tau_charge, Tau_charge_);
    }
    if (Muon_charge.GetSize() > 0)
    {
        copy_TTreeReaderArray_toVector(Muon_charge, Muon_charge_);
    }

    // MetCorrection(SysJes, SysJer, Met_pt);
    // Met_phi = *Met_type1PF_phi;

    // SelectTops( tops_toptagger);
    // sort( tops_toptagger.begin(), tops_toptagger.end(), compEle);

    if (!isdata)
    {
        genTaus.clear();
        genEles.clear();
        genMuons.clear();
        selectGenTaus(genTaus);
        selectGenEles(genEles);
        selectGenMuons(genMuons);
    }

    EVENT_prefireWeight_ = *L1PreFiringWeight_Nom;
    EVENT_prefireWeight_up_ = *L1PreFiringWeight_Up;
    EVENT_prefireWeight_down_ = *L1PreFiringWeight_Dn;

    if (!isdata)
    {
        EVENT_genWeight_ = *genWeight;
    }
    else
    {
        EVENT_genWeight_ = 1;
    }

    // preSelection
    if (preSelection)
    {
        if (!(tausT.size() > 0))
            return kFALSE;
        if (!(jets.size() > 5))
            return kFALSE;
        // if (!(bjetsL.size() > 1))
        // return kFALSE;
    }
    h_forEY_preSelection->Fill(0.0, basicWeight);

    eventsPassed++;
    newTree->Fill();

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
    Info("Terminate", "mouns: T %lld, F %lld, L %lld", mounsT_total, mounsF_total, mounsL_total);
    Info("Terminate", "electrons: T %lld, F %lld, L %lld", elesT_total, elesF_total, elesL_total);
    Info("Terminate", "taus: T %lld, F %lld, L %lld", tausT_total, tausF_total, tausL_total);
    Info("Terminate", "jets: %lld", jets_total);
    Info("Terminate", "bjets: M %lld", bjetsM_total);
    Info("Terminate", "output file here: %s", outputfile->GetName());
    ///////////////////////////////
}

/////////////////
void objectTSelectorForNanoAOD::makeBranch(TTree *newTree)
{
    newTree->Branch("muonsL", &muonsL);
    newTree->Branch("muonsL_index", &muonsL_index);
    newTree->Branch("muonsF", &muonsF);
    newTree->Branch("muonsF_index", &muonsF_index);
    newTree->Branch("muonsT", &muonsT);
    newTree->Branch("muonsT_index", &muonsT_index);
    newTree->Branch("eleMVAL", &eleMVAL);
    newTree->Branch("eleMVAF", &eleMVAF);
    newTree->Branch("eleMVAT", &eleMVAT);
    newTree->Branch("eleMVAL_index", &eleMVAL_index);
    newTree->Branch("eleMVAF_index", &eleMVAF_index);
    newTree->Branch("eleMVAT_index", &eleMVAT_index);
    newTree->Branch("leptonsMVAF", &leptonsMVAF);
    newTree->Branch("leptonsMVAT", &leptonsMVAT);
    newTree->Branch("leptonsMVAL", &leptonsMVAL);

    newTree->Branch("tausL", &tausL);
    newTree->Branch("tausF", &tausF);
    newTree->Branch("tausT", &tausT);
    newTree->Branch("tausL_index", &tausL_index);
    newTree->Branch("tausF_index", &tausF_index);
    newTree->Branch("tausT_index", &tausT_index);
    newTree->Branch("tausL_decayMode", &tausL_decayMode);
    newTree->Branch("tausF_decayMode", &tausF_decayMode);
    newTree->Branch("tausT_decayMode", &tausT_decayMode);
    newTree->Branch("tausL_genPartFlav", &tausL_genPartFlav);
    newTree->Branch("tausF_genPartFlav", &tausF_genPartFlav);
    newTree->Branch("tausT_genPartFlav", &tausT_genPartFlav);
    newTree->Branch("tausT_TESup", &tausT_TESup);
    newTree->Branch("tausT_index_TESup", &tausT_index_TESup);
    newTree->Branch("tausT_decayMode_TESup", &tausT_decayMode_TESup);
    newTree->Branch("tausT_genPartFlav_TESup", &tausT_genPartFlav_TESup);
    newTree->Branch("tausT_TESdown", &tausT_TESdown);
    newTree->Branch("tausT_index_TESdown", &tausT_index_TESdown);
    newTree->Branch("tausT_decayMode_TESdown", &tausT_decayMode_TESdown);
    newTree->Branch("tausT_genPartFlav_TESdown", &tausT_genPartFlav_TESdown);

    newTree->Branch("jets", &jets);
    newTree->Branch("jets_JESuncer", &jets_JESuncer);
    newTree->Branch("jets_index", &jets_index);
    newTree->Branch("jets_flavour", &jets_flavour);
    newTree->Branch("jets_btags", &jets_btags);
    newTree->Branch("jets_JECup", &jets_JECup);
    newTree->Branch("jets_index_JECup", &jets_index_JECup);
    newTree->Branch("jets_flavour_JECup", &jets_flavour_JECup);
    newTree->Branch("jets_btags_JECup", &jets_btags_JECup);
    newTree->Branch("jets_JECdown", &jets_JECdown);
    newTree->Branch("jets_index_JECdown", &jets_index_JECdown);
    newTree->Branch("jets_flavour_JECdown", &jets_flavour_JECdown);
    newTree->Branch("jets_btags_JECdown", &jets_btags_JECdown);
    newTree->Branch("bjetsL", &bjetsL);
    newTree->Branch("bjetsL_index", &bjetsL_index);
    newTree->Branch("bjetsL_flavour", &bjetsL_flavour);
    newTree->Branch("bjetsL_btags", &bjetsL_btags);
    newTree->Branch("bjetsM", &bjetsM);
    newTree->Branch("bjetsM_index", &bjetsM_index);
    newTree->Branch("bjetsM_flavour", &bjetsM_flavour);
    newTree->Branch("bjetsM_btags", &bjetsM_btags);
    newTree->Branch("bjetsT", &bjetsT);
    newTree->Branch("bjetsT_index", &bjetsT_index);
    newTree->Branch("bjetsT_flavour", &bjetsT_flavour);
    newTree->Branch("bjetsT_btags", &bjetsT_btags);
    newTree->Branch("forwardJets", &forwardJets);
    newTree->Branch("forwardJets_index", &forwardJets_index);
    newTree->Branch("forwardJets_flavour", &forwardJets_flavour);
    newTree->Branch("forwardJets_btags", &forwardJets_btags);
    newTree->Branch("nonbjetsL", &nonbjetsL);
    newTree->Branch("nonbjetsM", &nonbjetsM);
    newTree->Branch("nonbjetsT", &nonbjetsT);
    newTree->Branch("patElectron_charge_", &patElectron_charge_);
    newTree->Branch("Tau_charge_", &Tau_charge_);
    newTree->Branch("Muon_charge_", &Muon_charge_);
    // CHANGE HERE TO RUN ON DATA

    newTree->Branch("genTaus", &genTaus);
    newTree->Branch("genEles", &genEles);
    newTree->Branch("genMuons", &genMuons);

    newTree->Branch("Met_pt", &Met_pt, "Met_pt/D");
    newTree->Branch("Met_phi", &Met_phi, "Met_phi/D");
    newTree->Branch("tops_toptagger", &tops_toptagger);

    newTree->Branch("EVENT_prefireWeight_", &EVENT_prefireWeight_, "EVENT_prefireWeight_/D");
    newTree->Branch("EVENT_prefireWeight_up_", &EVENT_prefireWeight_up_, "EVENT_prefireWeight_up_/D");
    newTree->Branch("EVENT_prefireWeight_down_", &EVENT_prefireWeight_down_, "EVENT_prefireWeight_down_/D");
    newTree->Branch("PUWeight", &PUWeight, "PUWeight/D");
    newTree->Branch("PUWeight_Up", &PUWeight_Up, "PUWeight_Up/D");
    newTree->Branch("PUWeight_Down", &PUWeight_Down, "PUWeight_Down/D");
    // CHANGE HERE TO RUN ON DATA

    newTree->Branch("EVENT_genWeight_", &EVENT_genWeight_, "EVENT_genWeight_/D");

    newTree->Branch("PV_npvs_", &PV_npvs_, "PV_npvs_/I");
    newTree->Branch("PV_npvsGood_", &PV_npvsGood_, "PV_npvsGood_/I");
    newTree->Branch("genTtbarId_", &genTtbarId_, "genTtbarId_/I");
    //???change flags to Int_t type;
    newTree->Branch("Flag_goodVertices_", &Flag_goodVertices_, "Flag_goodVertices_/I");
    newTree->Branch("Flag_globalSuperTightHalo2016Filter_", &Flag_globalSuperTightHalo2016Filter_, "Flag_globalSuperTightHalo2016Filter_/I");
    newTree->Branch("Flag_HBHENoiseFilter_", &Flag_HBHENoiseFilter_, "Flag_HBHENoiseFilter_/I");
    newTree->Branch("Flag_HBHENoiseIsoFilter_", &Flag_HBHENoiseIsoFilter_, "Flag_HBHENoiseIsoFilter_/I");
    newTree->Branch("Flag_EcalDeadCellTriggerPrimitiveFilter_", &Flag_EcalDeadCellTriggerPrimitiveFilter_, "Flag_EcalDeadCellTriggerPrimitiveFilter_/I");
    newTree->Branch("Flag_BadPFMuonFilter_", &Flag_BadPFMuonFilter_, "Flag_BadPFMuonFilter_/I");
    newTree->Branch("Flag_BadPFMuonDzFilter_", &Flag_BadPFMuonDzFilter_, "Flag_BadPFMuonDzFilter_/I");
    newTree->Branch("Flag_ecalBadCalibFilter_", &Flag_ecalBadCalibFilter_, "Flag_ecalBadCalibFilter_/I");
    newTree->Branch("Flag_eeBadScFilter_", &Flag_eeBadScFilter_, "Flag_eeBadScFilter_/I");

    newTree->Branch("run_", &run_, "run_/i"); // i : a 32 bit unsigned integer (UInt_t)
    newTree->Branch("event_", &event_);       // If the address points to a single numerical variable, the leaflist is optional:

    newTree->Branch("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_", &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_/I");
    newTree->Branch("HLT_PFHT450_SixJet40_BTagCSV_p056_", &HLT_PFHT450_SixJet40_BTagCSV_p056_, "HLT_PFHT450_SixJet40_BTagCSV_p056_/I");
    newTree->Branch("HLT_PFJet450_", &HLT_PFJet450_, "HLT_PFJet450_/I");
    newTree->Branch("HLT_IsoMu24_", &HLT_IsoMu24_, "HLT_IsoMu24_/I");
    newTree->Branch("HLT_IsoMu27_", &HLT_IsoMu27_, "HLT_IsoMu27_/I");

    // 2018////////////
    //  newTree->Branch( "", &, "/I");
    newTree->Branch("HLT_PFHT1050_", &HLT_PFHT1050_, "HLT_PFHT1050_/I");
    newTree->Branch("HLT_PFJet500_", &HLT_PFJet500_, "HLT_PFJet500_/I");
    newTree->Branch("HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_", &HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_, "HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_/I");
    newTree->Branch("HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_", &HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_, "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_/I");
    newTree->Branch("HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_", &HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_/I");
    newTree->Branch("HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_", &HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_/I");
    newTree->Branch("HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_", &HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_, "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_/I");
    newTree->Branch("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_", &HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_/I");
}

void objectTSelectorForNanoAOD::SelectMuons(std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedMuons, std::vector<Int_t> &SelectedMuonsIndex, const Int_t type)
{
    // changed ISO to ss of TTTT
    // 0 for Loose; 1 fakeble; 2 tight
    for (UInt_t j = 0; j < Muon_pt.GetSize(); ++j)
    {
        // in objectSelection.h Muon_pt_ is global variable

        if (!(Muon_pt.At(j) > 10))
            continue;
        if (!(fabs(Muon_eta.At(j)) < 2.4))
            continue;
        if (!(fabs(Muon_dz.At(j)) < 0.1))
            continue;
        if (!(fabs(Muon_dxy.At(j)) < 0.05))
            continue;
        // ID
        if (type == 0)
        {
            if (!Muon_looseId.At(j))
                continue;
            if (!(int(Muon_miniIsoId.At(j)) >= 1))
                //???do we need to int() the unsigned char here?
                continue;
        }
        if (type == 1)
        {
            if (!Muon_mediumId.At(j))
                continue;
            if (!(int(Muon_miniIsoId.At(j)) >= 1))
                //???do we need to int() the unsigned char here?
                continue;
            if (!(fabs(Muon_ip3d.At(j)) < 4))
                continue;
            if (!(Muon_tightCharge.At(j) == 2))
                continue;
        }
        if (type == 2)
        {
            if (!Muon_mediumId.At(j))
                continue;
            if (!(int(Muon_miniIsoId.At(j)) >= 3))
                continue;
            if (!(fabs(Muon_ip3d.At(j)) < 4))
                continue;
            if (!(Muon_tightCharge.At(j) == 2))
                continue;
        }
        // ISO
        // IP
        // charge,The quality of the charge reconstruction
        ROOT::Math::PtEtaPhiMVector muon(Muon_pt.At(j), Muon_eta.At(j), Muon_phi.At(j), Muon_mass.At(j));
        // muon.SetPtEtaPhiE(Muon_pt.At(j), Muon_eta.At(j), Muon_phi.At(j),
        // muon.SetPtEtaPhiM(Muon_pt.At(j), Muon_eta.At(j), Muon_phi.At(j), Muon_mass.At(j));
        SelectedMuons.push_back(muon);
        SelectedMuonsIndex.push_back(j);
    }
}

void objectTSelectorForNanoAOD::SelectElectronsMVA(std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedElectrons, std::vector<Int_t> &SelectedElectronsIndex, const Int_t type)
{
    // 0 for VLoose; 1 for VLooseFO(fakeble object); 2 for tight
    // 2016 - MVANoIso94XV2, from SUSY
    for (UInt_t j = 0; j < Electron_pt.GetSize(); ++j)
    { /*{{{*/
        Double_t pt = Electron_pt.At(j);
        Double_t eta = Electron_eta.At(j);
        if (!(fabs(eta) < 2.5))
            continue;
        if (!(pt > 10))
            continue;
        if (!Electron_mvaFall17V2Iso_WP90.At(j))
            continue; // note: after switching from SUSY ID to EGamma ID, there's no difference in ID between loose, fakeable and tight electrons
        // note bis: use *Iso* MVA discriminator, it comes from a MVA method trained with iso variables as input features. A WP on this discriminator implies ISO requirements
        if (!Electron_convVeto.At(j))
            continue;
        // the number of missing pixel hits and a conversion veto based on the vertex fit probability. To reject electrons originating from photon conversion

        // IP
        if (!(fabs(Electron_dxy.At(j)) < 0.05))
            continue;
        if (!(fabs(Electron_dz.At(j)) < 0.1))
            continue;
        if (type == 0)
        {
            if (!(int(Electron_lostHits.At(j)) <= 1))
                continue;
        }
        if (type == 1 || type == 2)
        {
            if (!(int(Electron_lostHits.At(j)) == 0))
                continue;
            if (!((Electron_ip3d.At(j)) < 4))
                continue;
        }
        // tight charge
        // Electron_tightCharge	Int_t	Tight charge criteria (0:none, 1:isGsfScPixChargeConsistent, 2:isGsfCtfScPixChargeConsistent)
        //???not sure which one to use, drop for now

        ROOT::Math::PtEtaPhiMVector electron(Electron_pt.At(j), Electron_eta.At(j), Electron_phi.At(j), Electron_mass.At(j));
        // electron.SetPtEtaPhiM(Electron_pt.At(j), Electron_eta.At(j), Electron_phi.At(j), Electron_mass.At(j));
        SelectedElectrons.push_back(electron);
        SelectedElectronsIndex.push_back(j);
    }
}
/*}}}*/

void objectTSelectorForNanoAOD::SelectTaus(std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedTaus, std::vector<Int_t> &SelectedTausIndex, std::vector<Int_t> &SelectedTausDecayMode, std::vector<Int_t> &SelectedTausGenPartFlav, const Int_t TauWP, const std::vector<ROOT::Math::PtEtaPhiMVector> LeptonsMVAL, const Int_t sysTES)
{
    // this is tau ID in ttH
    // 1:loose;2:fakeble;3:tight
    for (UInt_t j = 0; j < *nTau; ++j)
    {
        Double_t itau_pt = Tau_pt.At(j);
        Double_t itau_mass = Tau_mass.At(j);
        switch (sysTES)
        {
        case 0:
            itau_pt *= taus_TES[j];
            itau_mass *= taus_TES[j];
            break;
        case 1:
            itau_pt *= taus_TES_up[j];
            itau_mass *= taus_TES_up[j];
            break;
        case 2:
            itau_pt *= taus_TES_down[j];
            itau_mass *= taus_TES_down[j];
            break;
        default:
            // std::cout << "tau pt and mass not corrected!!!"
            //           << "\n";
            break;
        }

        if (!(itau_pt > 20))
            continue;
        if (!(Tau_eta.At(j) < 2.3 && Tau_eta.At(j) > -2.3))
            continue;
        if (!(TMath::Abs(Tau_dz.At(j)) < 0.2))
            continue;
        //???why no dxy requirement?
        // if (!(Tau_idDecayModeOldDMs.At(j) == 0))      continue;//already in NANOAOD
        if (TauWP == 1)
        {
            bool isVSjetVVLoose = Tau_idDeepTau2017v2p1VSjet.At(j) & (1 << 1); // check if the 2nd bit (VVLoose WP) is 1
            // bitwise shift operators are the right-shift operator (>>
            //&: bitwise and operator; only 1&1=1; 0&anything = 0
            // 1<<1 = 2 = 00000010
            // converting unsigned char to bool: uchar_t ->int->bool; if 2nd bit is 1 isVSjetVVLoose=true; if 2nd bit is 0 isVSjetVVLoose = false
            if (!isVSjetVVLoose)
                continue;
            // bitmask 1 = VVVLoose, 2 = VVLoose, 4 = VLoose, 8 = Loose, 16 = Medium, 32 = Tight, 64 = VTight, 128 = VVTight
        }
        if (TauWP == 2)
        {
            bool isVSjetVVLoose = Tau_idDeepTau2017v2p1VSjet.At(j) & (1 << 1); // check if the 2nd bit (VVLoose WP) is 1
            bool isVSeVVVLoose = Tau_idDeepTau2017v2p1VSe.At(j) & (1 << 0);    // check if the 1st bit (VVVLoose WP) is 1
            bool isVSmuVLoose = Tau_idDeepTau2017v2p1VSmu.At(j) & (1 << 0);    // check if the 1st bit (VLoose WP) is 1
            if (!(isVSjetVVLoose && isVSeVVVLoose && isVSmuVLoose))
                continue;
            if (Tau_decayMode.At(j) == 5 || Tau_decayMode.At(j) == 6)
                continue;
        }
        if (TauWP == 3)
        { // channel specific in ttH. use the tight from 1t 1l

            bool isVSjetM = Tau_idDeepTau2017v2p1VSjet.At(j) & (1 << 4);    // check if the 5th bit (Medium WP) is 1
            bool isVSeVVVLoose = Tau_idDeepTau2017v2p1VSe.At(j) & (1 << 0); // check if the 1st bit (VVVLoose WP) is 1
            bool isVSmuVLoose = Tau_idDeepTau2017v2p1VSmu.At(j) & (1 << 0); // check if the 1st bit (VLoose WP) is 1
            if (!(isVSjetM && isVSeVVVLoose && isVSmuVLoose))
                continue;
            if (Tau_decayMode.At(j) == 5 || Tau_decayMode.At(j) == 6)
                continue;
        }
        // overlap removal
        Double_t minDeltaR_lep;
        if (LeptonsMVAL.size() > 0)
        {
            minDeltaR_lep = deltRmin(Tau_eta.At(j), Tau_phi.At(j), LeptonsMVAL);
            if (!(minDeltaR_lep >= 0.4))
            {
                continue;
            }
        }

        //?need err handling
        ROOT::Math::PtEtaPhiMVector tau(itau_pt, Tau_eta.At(j), Tau_phi.At(j), itau_mass);
        // tau.SetPtEtaPhiM(itau_pt, Tau_eta.At(j), Tau_phi.At(j), itau_mass); // here the pt and mass are already corrected
        // TLorentzVector itau  = taus_TES.at(j)*tau;
        SelectedTaus.push_back(tau);
        SelectedTausIndex.push_back(j);
        SelectedTausDecayMode.push_back(Tau_decayMode.At(j));
        SelectedTausGenPartFlav.push_back(Tau_genPartFlav.At(j));
    }
} /*}}}*/

void objectTSelectorForNanoAOD::SelectJets(Bool_t ifJER, const Int_t jetType, const bool deepJet, std::vector<ROOT::Math::PtEtaPhiMVector> &SelectedJets, std::vector<Double_t> &SelectedJetsBTags, std::vector<Int_t> &SelectedJetsIndex, std::vector<Int_t> &SelectedJetsFlavor, const std::vector<ROOT::Math::PtEtaPhiMVector> LeptonsMVAF, const std::vector<ROOT::Math::PtEtaPhiMVector> SelectedTausL, const Int_t sysJEC)
{
#include "inputMap.h"
    // jetType=0  -> usual jets; we use loose ID
    // jetType=11 -> b-jets L, jetType=12 -> b-jets M, jetType=13 -> b-jets T, jetType=2  -> forward jets
    Double_t MaxMostForwardJetEta = -99;
    for (UInt_t j = 0; j < Jet_pt.GetSize(); ++j)
    {
        Double_t jetpt = static_cast<Double_t>(Jet_pt.At(j));
        Double_t ijetMass = Jet_mass.At(j);
        Double_t ijetEta = Jet_eta.At(j);
        Double_t ijetPhi = Jet_phi.At(j);
        if (ifJER)
        {
            // jetpt = jetpt * JER_SF_new.at(j);
            // ijetMass = ijetMass * JER_SF_new.at(j);
            jetpt *= jetSmearingFactors[j];
            ijetMass *= jetSmearingFactors[j];
        }
        // maybe scaling only changes pt and mass? yes!
        switch (sysJEC)
        {
        case 0:
            break;
        case 1:
            jetpt = jetpt * (1 + jets_JESuncer[j]);
            ijetMass *= (1 + jets_JESuncer[j]);
            break;
        case 2:
            jetpt *= (1 - jets_JESuncer[j]);
            ijetMass *= (1 - jets_JESuncer[j]);
            break;
        default:
            break;
        }
        // here SF_up or SF_down should also be apllied.
        if (!(jetpt > 25))
            continue;
        if (!(fabs(ijetEta) < 5.0))
            continue;
        // cout << "jetId = " << Jet_jetId.At(j)<<"\n";
        if (!(Jet_jetId.At(j) > 0))
            continue; // Jet ID flags bit1 is loose (always false in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
        // Jet ID flags bit1 is loose (always ：wfalse in 2017 since it does not exist), bit2 is tight, bit3 is tightLepVeto
        // passlooseID*1+passtightID*2+passtightLepVetoID*4

        if (jetType == 11 || jetType == 12 || jetType == 13)
        {
            if (!(fabs(ijetEta) < 2.4))
                continue;
        }
        if (deepJet)
        { // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
            if (jetType == 11)
            {
                if (!(Jet_btagDeepFlavB.At(j) > DeepJetL[era]))
                    continue;
            }
            if (jetType == 12)
            {
                if (!(Jet_btagDeepFlavB.At(j) > DeepJetM[era]))
                    continue;
            }
            if (jetType == 13)
            {
                if (!(Jet_btagDeepFlavB.At(j) > DeepJetT[era]))
                    continue;
            }
        }
        else
        {
            if (jetType == 11)
            {
                if (!(Jet_btagDeepB.At(j) > DeepCSVL[era]))
                    continue;
            }
            if (jetType == 12)
            {
                if (!(Jet_btagDeepB.At(j) > DeepCSVM[era]))
                    continue;
            }
            if (jetType == 13)
            {
                if (!(Jet_btagDeepB.At(j) > DeepCSVT[era]))
                    continue;
            }
        }
        // find mostforwardjeteta
        if (jetType == 0)
        { // normal jet
            if (fabs(ijetEta) > MaxMostForwardJetEta)
            {
                MaxMostForwardJetEta = fabs(ijetEta);
            } // MostForwardJetEta branch in new tree and SB.
            if (!(fabs(ijetEta) < 2.4))
                continue;
        }
        if (jetType == 2)
        { // forwardjet
            if (!(fabs(ijetEta) >= 2.4 && fabs(ijetEta) <= 5))
                continue;
            if (!(jetpt > 25))
                continue;
            if (fabs(ijetEta) >= 2.7 && fabs(ijetEta) <= 3.0)
            {
                if (!(jetpt > 60.0))
                    continue;
            }
        }
        // overlap removal
        if (LeptonsMVAF.size() > 0)
        {
            Double_t deltaR = 0;
            Double_t minDeltaR = 100;
            for (UInt_t lep = 0; lep < LeptonsMVAF.size(); lep++)
            {
                deltaR = DeltaR(LeptonsMVAF[lep].Eta(), ijetEta, LeptonsMVAF[lep].Phi(), ijetPhi);
                if (deltaR < minDeltaR)
                    minDeltaR = deltaR; // The continue statement provides a convenient way to jump to the end of the loop body for the current iteration.
            }
            if (!(minDeltaR >= 0.4))
                continue;
        }
        if (SelectedTausL.size() > 0)
        {
            Double_t deltaR_tau = 0;
            Double_t minDeltaR_tau = 100;
            for (UInt_t tau = 0; tau < SelectedTausL.size(); tau++)
            {
                deltaR_tau = DeltaR(SelectedTausL[tau].Eta(), ijetEta, SelectedTausL[tau].Phi(), ijetPhi);
                if (deltaR_tau < minDeltaR_tau)
                    minDeltaR_tau = deltaR_tau;
            }
            if (!(minDeltaR_tau >= 0.4))
                continue;
        }
        ROOT::Math::PtEtaPhiMVector jet_prov(jetpt, ijetEta, ijetPhi, ijetMass);
        SelectedJets.push_back(jet_prov);
        // std::cout<<"jet : "<<jet_prov.Pt()<<", "<<jet_prov.Eta()<<", "<<jet_prov.Phi()<<","<<jet_prov.M()<<"\n";
        // std::cout<<"jet scale manually: "<<jet.Pt()<<", "<<jet.Eta()<<", "<<jet.Phi()<<","<<jet.M()<<"\n";
        // std::cout<<"jet scale: "<<jet_scaled.Pt()<<", "<<jet_scaled.Eta()<<", "<<jet_scaled.Phi()<<", "<<jet_scaled.M()<<"\n";
        // std::cout << std::setprecision(18) << SelectedJets[5].Pt() << "\n";

        SelectedJetsIndex.push_back(j);
        // CHANGE HERE TO RUN ON DATA
        SelectedJetsFlavor.push_back(Jet_hadronFlavour.At(j));
        if (deepJet)
        {
            SelectedJetsBTags.push_back(Jet_btagDeepFlavB.At(j));
        }
        else
        {
            SelectedJetsBTags.push_back(Jet_btagDeepB.At(j));
        }
    }
}

void objectTSelectorForNanoAOD::selectGenTaus(std::vector<ROOT::Math::PtEtaPhiMVector> &genTaus)
{
    for (UInt_t j = 0; j < GenPart_pt.GetSize(); ++j)
    {
        if (!(abs(GenPart_genPartIdxMother.At(j)) == 24 && abs(GenPart_pdgId.At(j)) == 15))
            continue; // tau:15; top:6;W:
        ROOT::Math::PtEtaPhiMVector gentau(GenPart_pt.At(j), GenPart_eta.At(j), GenPart_phi.At(j), GenPart_mass.At(j));
        // gentau.SetPtEtaPhiM(GenPart_pt.At(j), GenPart_eta.At(j), GenPart_phi.At(j), GenPart_mass.At(j));
        genTaus.push_back(gentau);
    }
}
void objectTSelectorForNanoAOD::selectGenEles(std::vector<ROOT::Math::PtEtaPhiMVector> &genEles)
{
    for (UInt_t j = 0; j < GenPart_pt.GetSize(); ++j)
    {
        if (!(abs(GenPart_genPartIdxMother.At(j)) == 24 && abs(GenPart_pdgId.At(j)) == 11))
            continue; // tau:15; ele:11;
        ROOT::Math::PtEtaPhiMVector genele(GenPart_pt.At(j), GenPart_eta.At(j), GenPart_phi.At(j), GenPart_mass.At(j));
        // genele.SetPtEtaPhiM(GenPart_pt.At(j), GenPart_eta.At(j), GenPart_phi.At(j), GenPart_mass.At(j));
        genEles.push_back(genele);
    }
}
void objectTSelectorForNanoAOD::selectGenMuons(std::vector<ROOT::Math::PtEtaPhiMVector> &genMuons)
{
    for (UInt_t j = 0; j < GenPart_pt.GetSize(); ++j)
    {
        if (!(abs(GenPart_genPartIdxMother.At(j)) == 24 && abs(GenPart_pdgId.At(j)) == 13))
            continue; // tau:15; top:6;W:;muon:13
        ROOT::Math::PtEtaPhiMVector genmuon(GenPart_pt.At(j), GenPart_eta.At(j), GenPart_phi.At(j), GenPart_mass.At(j));
        // genmuon.SetPtEtaPhiM(GenPart_pt.At(j), GenPart_eta.At(j), GenPart_phi.At(j), GenPart_mass.At(j));
        genMuons.push_back(genmuon);
    }
}

void objectTSelectorForNanoAOD::copyHLT_new(const Bool_t isdata, const TString dataset)
{

    HLT_IsoMu24_ = *HLT_IsoMu24;
    HLT_IsoMu27_ = *HLT_IsoMu27;

    if (era.CompareTo("2016preVFP") == 0 || era.CompareTo("2016postVFP") == 0)
    {
        HLT_PFHT450_SixJet40_BTagCSV_p056_ = *HLT_PFHT450_SixJet40_BTagCSV_p056;
        HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ = *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056;
        HLT_PFJet450_ = *HLT_PFJet450;
    }

    if (!isdata)
    {
        if (era.CompareTo("2018") == 0)
        {
            // should be the same as in intializaTreeBranches
            HLT_PFHT1050_ = *HLT_PFHT1050; // 297050	306460; 315257	325172
            HLT_PFJet500_ = *HLT_PFJet500;
            HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_ = *HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5;
            HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = *HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59;
            HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ = *HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94;
        }
    }
    else
    { // data
        if (*run >= 315257 && *run <= 325173)
        {
            // 2018
            HLT_PFHT1050_ = *HLT_PFHT1050; // 297050	306460; 315257	325172
            HLT_PFJet500_ = *HLT_PFJet500;
            HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_ = *HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5;
            if (*run < 315974)
            {
                HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ = *HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5;
                HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = *HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2;
            }
            else if (*run < 317509)
            {
                HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_ = *HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5;
                HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = *HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2;
            }
            else
            {
                HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = *HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59;
                HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ = *HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94;
            }
        }
    }
}

Bool_t objectTSelectorForNanoAOD::selectGoodLumi()
{
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGoodLumiSectionsJSONFile
    Bool_t ifGoodLumi = kTRUE;
    if (isdata)
    {
        if (_goodLumis.find(*run) == _goodLumis.end())
        {
            ifGoodLumi = kFALSE;
        }
        else
        { // if run number is in map
            Bool_t keepEvent = false;
            for (Int_t i = 0; i < _goodLumis[*run].size() / 2.; i++)
            {
                if (*luminosityBlock >= _goodLumis[*run][i * 2] && *luminosityBlock <= _goodLumis[*run][i * 2 + 1])
                {
                    keepEvent = true;
                    break;
                }
            }
            if (!keepEvent)
            {
                // veto luminosity blocks not in JSON
                ifGoodLumi = kFALSE;
            }
        }
    }
    return ifGoodLumi;
}

void objectTSelectorForNanoAOD::copyFlags()
{
    Flag_goodVertices_ = *Flag_goodVertices;
    Flag_globalSuperTightHalo2016Filter_ = *Flag_globalSuperTightHalo2016Filter;
    Flag_HBHENoiseFilter_ = *Flag_HBHENoiseFilter;
    Flag_HBHENoiseIsoFilter_ = *Flag_HBHENoiseIsoFilter;
    Flag_EcalDeadCellTriggerPrimitiveFilter_ = *Flag_EcalDeadCellTriggerPrimitiveFilter;
    Flag_BadPFMuonFilter_ = *Flag_BadPFMuonFilter;
    Flag_BadPFMuonDzFilter_ = *Flag_BadPFMuonDzFilter;
    Flag_ecalBadCalibFilter_ = *Flag_ecalBadCalibFilter;
    Flag_eeBadScFilter_ = *Flag_eeBadScFilter;
}

void objectTSelectorForNanoAOD::initializeBrancheValues()
{
    muonsL.clear();
    muonsL_index.clear();
    muonsF.clear();
    muonsF_index.clear();
    muonsT.clear();
    muonsT_index.clear();
    eleMVAL.clear();
    eleMVAL_index.clear();
    eleMVAF.clear();
    eleMVAF_index.clear();
    eleMVAT.clear();
    eleMVAT_index.clear();
    leptonsMVAF.clear();
    leptonsMVAT.clear();
    leptonsMVAL.clear();

    taus_TES.clear();
    taus_TES_up.clear();
    taus_TES_down.clear();
    tausL.clear();
    tausL_index.clear();
    tausL_genPartFlav.clear();
    tausL_decayMode.clear();
    tausF.clear();
    tausF_index.clear();
    tausF_genPartFlav.clear();
    tausF_decayMode.clear();
    tausT.clear();
    tausT_index.clear();
    tausT_genPartFlav.clear();
    tausT_decayMode.clear();
    tausT_TESup.clear();
    tausT_index_TESup.clear();
    tausT_genPartFlav_TESup.clear();
    tausT_decayMode_TESup.clear();
    tausT_TESdown.clear();
    tausT_index_TESdown.clear();
    tausT_genPartFlav_TESdown.clear();
    tausT_decayMode_TESdown.clear();

    jets.clear();
    jets_index.clear();
    jets_flavour.clear();
    jets_btags.clear();
    jets_JECup.clear();
    jets_index_JECup.clear();
    jets_flavour_JECup.clear();
    jets_btags_JECup.clear();
    jets_JECdown.clear();
    jets_index_JECdown.clear();
    jets_flavour_JECdown.clear();
    jets_btags_JECdown.clear();
    jets_JESuncer.clear();
    JER_SF_new.clear();
    JER_SF_new_up.clear();
    JER_SF_new_down.clear();
    bjetsL.clear();
    bjetsL_index.clear();
    bjetsL_flavour.clear();
    bjetsL_btags.clear();
    bjetsM.clear();
    bjetsM_index.clear();
    bjetsM_flavour.clear();
    bjetsM_btags.clear();
    bjetsT.clear();
    bjetsT_index.clear();
    bjetsT_flavour.clear();
    bjetsT_btags.clear();
    forwardJets.clear();
    forwardJets_index.clear();
    forwardJets_flavour.clear();
    forwardJets_btags.clear();
    nonbjetsL.clear();
    nonbjetsM.clear();
    nonbjetsT.clear();

    patElectron_charge_.clear();
    Tau_charge_.clear();
    Muon_charge_.clear();
    tops_toptagger.clear();
    EVENT_prefireWeight_ = -99;
    EVENT_prefireWeight_up_ = -99;
    EVENT_prefireWeight_down_ = -99;
    PUWeight = -99;
    PUWeight_Up = -99;
    PUWeight_Down = -99;
    EVENT_genWeight_ = -99;

    run_ = 0;
    event_ = 0;

    HLT_PFHT450_SixJet40_BTagCSV_p056_ = -99;
    HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ = -99;
    HLT_PFJet450_ = -99;
    HLT_IsoMu24_ = -99;
    HLT_IsoMu27_ = -99;

    // 2018
    HLT_PFHT1050_ = -99;
    HLT_PFJet500_ = -99;
    HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_ = -99;
    HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ = -99;
    HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = -99;
    HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_ = -99;
    HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = -99;
    HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ = -99;
}

void objectTSelectorForNanoAOD::setupInputFile()
{
#include "inputMap.h"

    std::cout << "setting up input file now........\n";
    // jec files
    TString jsonBase = "../../jsonpog-integration/POG/";
    // std::string jer_file = "../../jsonpog-integration/POG/JME/2016preVFP_UL/jet_jerc.json";
    // same file for JER and JES
    // cset_jerSF = correction::CorrectionSet::from_file(jer_file);
    std::cout << "JEC file: " << jsonBase + json_map[era].at(0) << "\n";
    cset_jerSF = correction::CorrectionSet::from_file((jsonBase + json_map[era].at(0)).Data());
    for (auto &corr : *cset_jerSF)
    {
        printf("JEC Correction : %s\n", corr.first.c_str());
    }

    // TString tauSF_json = "../../jsonpog-integration/POG/TAU/2016preVFP_UL/tau.json" ;
    // cset_tauSF = correction::CorrectionSet::from_file(tauSF_json.Data());
    cset_tauSF = correction::CorrectionSet::from_file((jsonBase + json_map[era].at(1)).Data());
    for (auto &corr : *cset_tauSF)
    {
        printf("tauSF Correction: %s\n", corr.first.c_str());
    }

    if (!isdata)
    {
        //???era
        TString jetSmearing_PtFile = "../smearing/UL2016_postVFP/Summer20UL16_JRV3_MC_PtResolution_AK4PFchs.txt";
        TString jetSmearing_MCFile = "../smearing/UL2016_postVFP/Summer20UL16_JRV3_MC_SF_AK4PFchs.txt";

        // Set up branch for pileup correction
        if (era.CompareTo("2016postVFP") == 0)
        {
            inputPUFile_data = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-postVFP-69200ub-99bins.root", "READ");
            inputPUFile_dataUp = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-postVFP-72400ub-99bins.root", "READ");
            inputPUFile_dataDown = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-postVFP-66000ub-99bins.root", "READ");
            inputPUFile_mc = new TFile("../data_rootFiles/PUHistogram_mc2016_postVFP.root", "READ");

            // jetSmearing_PtFile = "../data_rootFiles/smearing/UL2016_postVFP/Summer20UL16_JRV3_MC_PtResolution_AK4PFchs.txt";
            // jetSmearing_MCFile = "../data_rootFiles/smearing/UL2016_postVFP/Summer20UL16_JRV3_MC_SF_AK4PFchs.txt";
        }
        else if (era.CompareTo("2016preVFP") == 0)
        {
            inputPUFile_data = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-preVFP-69200ub-99bins.root", "READ");
            inputPUFile_dataUp = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-preVFP-72400ub-99bins.root", "READ");
            inputPUFile_dataDown = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2016-preVFP-66000ub-99bins.root", "READ");
            inputPUFile_mc = new TFile("../data_rootFiles/PUHistogram_mc2016_preVFP.root", "READ");

            // jetSmearing_PtFile = "../data_rootFiles/smearing/UL2016_preVFP/Summer20UL16APV_JRV3_MC_PtResolution_AK4PFchs.txt";
            // jetSmearing_MCFile = "../data_rootFiles/smearing/UL2016_preVFP/Summer20UL16APV_JRV3_MC_SF_AK4PFchs.txt";
        }
        else if (era.CompareTo("2017") == 0)
        {
            inputPUFile_data = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2017-69200ub-99bins.root", "READ");
            inputPUFile_dataUp = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2017-72400ub-99bins.root", "READ");
            inputPUFile_dataDown = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2017-66000ub-99bins.root", "READ");
            inputPUFile_mc = new TFile("../data_rootFiles/PUHistogram_mc2017.root", "READ");

            // jetSmearing_PtFile = "../dada_rootFiles/smearing/UL2017/Summer19UL17_JRV3_MC_PtResolution_AK4PFchs.txt";
            // jetSmearing_MCFile = "../data_rootFiles/smearing/UL2017/Summer19UL17_JRV3_MC_SF_AK4PFchs.txt";
        }
        else if (era.CompareTo("2018") == 0)
        {
            inputPUFile_data = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2018-69200ub-99bins.root", "READ");
            inputPUFile_dataUp = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2018-72400ub-99bins.root", "READ");
            inputPUFile_dataDown = new TFile("../data_rootFiles/PileupHistogram-goldenJSON-13tev-2018-66000ub-99bins.root", "READ");
            inputPUFile_mc = new TFile("../data_rootFiles/PUHistogram_mc2018.root", "READ");

            // jetSmearing_PtFile = "../data_rootFiles/smearing/UL2018/Summer19UL18_JRV2_MC_PtResolution_AK4PFchs.txt";
            // jetSmearing_MCFile = "../data_rootFiles/smearing/UL2018/Summer19UL18_JRV2_MC_SF_AK4PFchs.txt";
        }
        std::cout << "pileup file used : " << inputPUFile_data->GetName() << "\n";
        // std::cout<<"jetSmearing file used: "<<jetSmearing_PtFile<<"\n"<<jetSmearing_MCFile<<"\n";
        // Get needed histograms
        dataPileupProfile = (TH1F *)inputPUFile_data->Get("pileup");
        dataPileupProfileUp = (TH1F *)inputPUFile_dataUp->Get("pileup");
        dataPileupProfileDown = (TH1F *)inputPUFile_dataDown->Get("pileup");
        MCPileupProfile = (TH1F *)inputPUFile_mc->Get("pileup");
        // Scale to unit area for a fair comparison
        dataPileupProfile->Scale(1.0 / dataPileupProfile->Integral());
        dataPileupProfileUp->Scale(1.0 / dataPileupProfileUp->Integral());
        dataPileupProfileDown->Scale(1.0 / dataPileupProfileDown->Integral());
        MCPileupProfile->Scale(1.0 / MCPileupProfile->Integral());

        readSmearingFile(jetSmearing_PtFile, resolution, resFormula);
        readSmearingFile(jetSmearing_MCFile, resSFs, toyResFormula);
    }
    else
    {
        std::cout << "data not setting up jetSmearing and pile files"
                  << "\n";
        std::cout << "setting up lumilosity json files for data\n";
        // TString jsonInFile = GoldenJSONs[era];
        // readJSON(isdata, jsonInFile, _goodLumis);
        readJSON(isdata, GoldenJSONs[era], _goodLumis);
    }

    std::cout << "done setting input file........................\n";
}

void objectTSelectorForNanoAOD::getOptionFromRunMacro(const TString option)
{

    TString option1 = option(0, option.First(":"));
    TString temp = option;
    TString option2 = temp.Remove(0, option.First(":") + 1);
    option2 = option2(0, option2.First(":"));
    // std::cout<<"temp: "<<temp<<"\n";
    TString option3 = temp.Remove(0, temp.First(":") + 1);
    option3 = option3(0, option3.First(":"));
    TString option4 = temp.Remove(0, temp.First(":") + 1);
    option4 = option4(0, option4.First(":"));
    TString option5 = temp.Remove(0, temp.First(":") + 1);

    std::cout << "option1: " << option1 << "\n";
    std::cout << "option2: " << option2 << "\n";
    std::cout << "option3: " << option3 << "\n";
    std::cout << "option4: " << option4 << "\n";
    std::cout << "option5: " << option5 << "\n";

    era = option2;
    std::cout << "era is: " << era << "\n";
    if (option4.CompareTo("0") == 0)
        isdata = false;
    else
        isdata = true;
    std::cout << "isdata  in TSelector: " << isdata << "\n";
    dataSet = option5;
    Int_t eventSelection = std::stoi(option3.Data());
    // 1 for MetFilters, 2 for HLTSelection, 4 for preSelection. so 7 if all selection; 0 if no selection
    std::cout << "eventSelection in selector: " << eventSelection << "\n";
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
    if (eventSelection == 0)
    {
        MetFilters = false;
        HLTSelection = false;
        preSelection = false;
    }
    if (eventSelection == 1)
    {
        MetFilters = true;
        HLTSelection = false;
        preSelection = false;
    }
    if (eventSelection == 2)
    {
        MetFilters = false;
        HLTSelection = true;
        preSelection = false;
    }
    if (eventSelection == 3)
    {
        MetFilters = true;
        HLTSelection = true;
        preSelection = false;
    }
    if (eventSelection == 4)
    {
        MetFilters = false;
        HLTSelection = false;
        preSelection = true;
    }
    if (eventSelection == 5)
    {
        MetFilters = true;
        HLTSelection = false;
        preSelection = true;
    }
    if (eventSelection == 6)
    {
        MetFilters = false;
        HLTSelection = true;
        preSelection = true;
    }
    if (eventSelection == 7)
    {
        MetFilters = true;
        HLTSelection = true;
        preSelection = true;
    }
    std::cout << "MetFilters = " << MetFilters << "; HLTSelection = " << HLTSelection << "; preSelection = " << preSelection << "\n";
    TString outFileName = option1;
    outputfile = new TFile(outFileName, "RECREATE");
    std::cout << "outputFileName: " << outputfile->GetName() << "\n";
}

void objectTSelectorForNanoAOD::getRunRange(TTree *fChain)
{
    TH1F *runHist = new TH1F("runHist", "runHist", 52412, 272760, 325172); // 324581 range from 2016run to 2018
    fChain->Project("runHist", "run");
    std::cout << "tree Name: " << fChain->GetName() << "\n";
    // std::cout<<"Min in runHist: "<<runHist->GetMinimum()<<"\n";//GetMaximum returns the maximum along Y, not along X
    // std::cout<<"run entries:"<<runHist->GetEntries()<<"\n";
    runRange[0] = 272760 - 1 + runHist->FindFirstBinAbove();
    runRange[1] = 272760 - 1 + runHist->FindLastBinAbove();
    // histogram can not give us the accurate run range
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

void objectTSelectorForNanoAOD::intializaTreeBranches(const Bool_t isdata, const TString dataset)
{
    // overriding for MC files

    HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
    HLT_IsoMu27 = {fReader, "HLT_IsoMu27"};

    if (era.CompareTo("2016preVFP") == 0 || era.CompareTo("2016postVFP") == 0)
    {
        HLT_PFHT450_SixJet40_BTagCSV_p056 = {fReader, "HLT_PFHT450_SixJet40_BTagCSV_p056"};
        HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = {fReader, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056"};
        HLT_PFJet450 = {fReader, "HLT_PFJet450"};
    }

    if (!isdata)
    {
        std::cout << "running over: MC"
                  << "\n";
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
        // HLT for MC

        if (era.CompareTo("2018") == 0)
        {

            HLT_PFHT1050 = {fReader, "HLT_PFHT1050"}; // 297050	306460; 315257	325172
            HLT_PFJet500 = {fReader, "HLT_PFJet500"};
            HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 = {fReader, "HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5"};

            // HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = { fReader, "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5"};//checked
            // HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = { fReader, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5"};//checked
            HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 = {fReader, "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59"};

            // HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = {fReader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"};
            HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 = {fReader, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94"};
        }
    }
    else
    { // data
        std::cout << "running over: " << dataSet << "\n";

        if (runRange[0] >= 315257 && runRange[1] <= 325172)
        { // 2018
            // we are assuming no nanoAOD file has triggers cross ranges
            //  if the condition is false, the program is terminated and an error message is displayed.
            // assert( !(runRange[0]<315974 && runRange[1]>315974) );
            // assert( !(runRange[0]<317509 && runRange[1]>317509) );
            assert(!(runRange[0] < 315974 && runRange[1] >= 317509));

            HLT_PFHT1050 = {fReader, "HLT_PFHT1050"}; // 297050	306460; 315257	325172
            HLT_PFJet500 = {fReader, "HLT_PFJet500"};
            HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 = {fReader, "HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5"};
            if (runRange[1] < 315974)
            {
                HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = {fReader, "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5"}; // checked
                HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = {fReader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"};
            }
            else if (runRange[0] >= 315974 && runRange[1] < 317509)
            {
                HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = {fReader, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5"}; // checked
                HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = {fReader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"};
            }
            else if (runRange[0] >= 317509 && runRange[1] < 325173)
            {
                HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 = {fReader, "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59"};
                HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 = {fReader, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94"};
            }
            else if (runRange[0] < 315974 && 315974 <= runRange[1] && runRange[1] < 317509)
            {
                HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = {fReader, "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5"};         // checked
                HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = {fReader, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5"}; // checked
                HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = {fReader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"};
            }
            else if (315974 <= runRange[0] && runRange[0] < 317509 && 317509 <= runRange[1] && runRange[1] < 325173)
            {
                HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = {fReader, "HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5"}; // checked
                HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 = {fReader, "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59"};
                HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = {fReader, "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"};
                HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 = {fReader, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94"};
            }
        }
    }
}

void objectTSelectorForNanoAOD::calJetSmearFactors(const Bool_t isdata)
{
    std::vector<Int_t> *matchingIndices{new std::vector<Int_t>};
    getMatchingToGen(Jet_eta, Jet_phi, GenJet_eta, GenJet_phi, matchingIndices); // if a reco jet is unmatched, the corresponding gen jet pt will be 0
    jetSmearingFactors.clear();
    jetSmearingFactorsUp.clear();
    jetSmearingFactorsDown.clear();
    Double_t smearFactor = 1.0;
    Double_t smearFactorUp = 1.0;
    Double_t smearFactorDown = 1.0;
    for (UInt_t i = 0; i < *nJet; i++)
    {
        if (!isdata)
        {
            Double_t resSF = GetJerFromFile(Jet_eta.At(i), resSFs, 0);
            Double_t resSFUp = GetJerFromFile(Jet_eta.At(i), resSFs, 2);
            Double_t resSFDown = GetJerFromFile(Jet_eta.At(i), resSFs, 1);
            smearFactor = GetSmearFactor(Jet_pt.At(i), GenJet_pt.At(matchingIndices->at(i)), Jet_eta.At(i), *fixedGridRhoFastjetAll, resSF, resolution, resFormula, jet_jer_myran);
            smearFactorUp = GetSmearFactor(Jet_pt.At(i), GenJet_pt.At(matchingIndices->at(i)), Jet_eta.At(i), *fixedGridRhoFastjetAll, resSFUp, resolution, resFormula, jet_jer_myran);
            smearFactorDown = GetSmearFactor(Jet_pt.At(i), GenJet_pt.At(matchingIndices->at(i)), Jet_eta.At(i), *fixedGridRhoFastjetAll, resSFDown, resolution, resFormula, jet_jer_myran);
        }
        jetSmearingFactors.push_back(smearFactor);
        jetSmearingFactorsUp.push_back(smearFactorUp);
        jetSmearingFactorsDown.push_back(smearFactorDown);
    }
    delete matchingIndices;
}

void objectTSelectorForNanoAOD::calJER_SF(const Bool_t isdata, std::vector<Double_t> &jer_sf, std::vector<Double_t> &jer_sf_up, std::vector<Double_t> &jer_sf_down, correction::CorrectionSet *cset_jerSF)
{
// https://gitlab.cern.ch/cms-nanoAOD/jsonpog-integration/-/blob/master/examples/jercExample.py
// https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution#JER_Scaling_factors_and_Uncertai
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution
#include "inputMap.h"
    // TString input = "Summer20UL16APV_JRV3_MC_ScaleFactor_AK4PFchs";
    // TString input = JER_SF_map[era] ;
    // auto corr_jerSF = cset_jerSF->at(input.Data());
    auto corr_jerSF = cset_jerSF->at(corr_SF_map[era].at(0).Data());
    // std::cout<<"jerSF input: \n";
    // for ( UInt_t i=0;  i<corr_jerSF->inputs().size(); i++){
    //     std::cout<<corr_jerSF->inputs()[i].name()<<" ";
    // }
    // TString jesSFName = "Summer19UL16APV_V7_MC";
    // TString jesSFName_MC_L1 = jesSFName + TString("_L1FastJet_AK4PFchs");
    // TString jesSFName_MC_L1 = "Summer19UL16APV_V7_MC_L1FastJet_AK4PFchs";
    // auto corr_jesSF_L1 = cset_jerSF->at(jesSFName_MC_L1.Data());

    //???not sure how to get the JEC uncertainty for data yet?
    // https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/jetmetHelperRun2.py
    // TString unc = "Summer19UL16APV_V7_MC_Total_AK4PFchs";
    // auto corr_jesUncer = cset_jerSF->at(unc.Data());
    auto corr_jesUncer = cset_jerSF->at(corr_SF_map[era].at(1).Data());
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
        if (!isdata)
        {
            iSF = corr_jerSF->evaluate({Jet_eta.At(i), "nom"});
            iSF_up = corr_jerSF->evaluate({Jet_eta.At(i), "up"});
            iSF_down = corr_jerSF->evaluate({Jet_eta.At(i), "down"});

            // iSF_JES = corr_jesSF_L1->evaluate({ieta, ipt, "nom"});
            // iSF_JES = corr_jesSF_L1->evaluate({ Jet_area.At(i), ieta, ipt, 0.0 });
            iSF_JESuncer = corr_jesUncer->evaluate({ieta, ipt});
        }
        // std::cout << "iJERSF: " << iSF << "\n";
        // std::cout<<"iSF_JES"<<iSF_JESuncer<<"\n";
        jer_sf.push_back(iSF);
        jer_sf_up.push_back(iSF_up);
        jer_sf_down.push_back(iSF_down);
        jets_JESuncer.push_back(iSF_JESuncer);
    }
}

void objectTSelectorForNanoAOD::calTauSF_new()
{
    // https://gitlab.cern.ch/cms-tau-pog/jsonpog-integration/-/blob/master/examples/tauExample.py
    auto corr_tauES = cset_tauSF->at("tau_energy_scale");
    //???i assume it contains the correction to genuine tau and genuine electrons?
    Double_t iTES_sf = 1.0;
    Double_t iTES_sf_up = 1.0;
    Double_t iTES_sf_down = 1.0;
    for (UInt_t i = 0; i < *nTau; i++)
    {
        if (!isdata)
        {
            // corr4.evaluate(pt,eta,dm,5,"DeepTau2017v2p1",syst)
            // no sf for decaymode 5 and 6
            if (!(Tau_decayMode.At(i) == 5 || Tau_decayMode.At(i) == 6))
            {
                iTES_sf = corr_tauES->evaluate({Tau_pt.At(i), Tau_eta.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "DeepTau2017v2p1", "nom"});
                iTES_sf_up = corr_tauES->evaluate({Tau_pt.At(i), Tau_eta.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "DeepTau2017v2p1", "up"});
                iTES_sf_down = corr_tauES->evaluate({Tau_pt.At(i), Tau_eta.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "DeepTau2017v2p1", "down"});
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
    Double_t TESSF = 1.0;
    Double_t TESSFUp = 1.0;
    Double_t TESSFDown = 1.0;
    Double_t FESSF = 1.0;
    Double_t FESSFUp = 1.0;
    Double_t FESSFDown = 1.0;
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