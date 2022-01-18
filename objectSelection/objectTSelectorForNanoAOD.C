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
#include "../TauPOG/TauIDSFs/src/TauIDSFTool.cc"
#include <TH2.h>
#include <TStyle.h>


///////////////////////
void printElements(const vector<Double_t>& jets_btags, const vector<TLorentzVector>& jets ){
    for( UInt_t j = 0; j<jets_btags.size(); j++ ){
        std::cout<<jets[j].Pt()<<":"<<jets_btags[j]<<" ";
        // std::cout<<jets_btags[j]<<"  ";
    }
    std::cout<<"  \n";
}

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

void copy_TTreeReaderArray_toVector( const TTreeReaderArray<Float_t> &array, vector<Double_t> & vec){
    for( UInt_t i=0; i< array.GetSize(); i++){
        vec.push_back( array.At(i));
    }
}
void copy_TTreeReaderArray_toVector( const TTreeReaderArray<Int_t> &array, vector<Double_t> & vec){
    for( UInt_t i=0; i< array.GetSize(); i++){
        vec.push_back( array.At(i));
    }
}


// void jetsSubstructBjets(vector<TLorentzVector>& nonbjets, const vector<Double_t> &bjets_btags,const vector<Double_t> &jets_btags,  const vector<TLorentzVector>& jets ){
void jetsSubstructBjets(vector<TLorentzVector>& nonbjets,   const vector<TLorentzVector>& jets, const vector<TLorentzVector>& bjets ){
    // for( UInt_t jet =0; jet<jets_btags.size(); jet++){
        // if ( jets_btags[jet]== bjets_btags[jet]){
            // nonbjets.push_back( jets[jet]);
        // }
    // }
    Bool_t findMatchingB = false;
    for( UInt_t j=0; j<jets.size(); j++){
        for ( UInt_t i=0; i<bjets.size(); i++){
            if ( bjets[i] == jets[j] )  {
                // nonbjets.push_back( jets[j]);
                findMatchingB = true;
                break;
            }
        }
        if ( !findMatchingB ) nonbjets.push_back( jets[j]);
        findMatchingB = false;
    }
}

    // SelectJets(0, deepJet, jets, jets_btags, jets_index, jets_flavour, SysJes, SysJer, leptonsMVAL, tausL);
void sortJetAndFlavorAndBcore( vector<TLorentzVector>& jets, vector<Double_t>& jets_btags, vector<Int_t> jets_flavour ){
    sort( jets_btags.begin(), jets_btags.end(), [&](std::size_t i,std::size_t j){
            return jets[i].Pt()>jets[j].Pt();
            } );
} 

void readSmearingFile(TString _path, std::vector<std::vector<std::string>> & _resolution, std::string & _resFormula) {

    std::ifstream file(_path);
    std::string lineStr;
    bool firstLine = true;
    while (std::getline(file,lineStr)){
        std::stringstream ss(lineStr);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);
        if (firstLine){
            //if reading resolution file, store formula
            if (vstrings.size() > 5) _resFormula = vstrings[5];
            //else, store a toy formula
            else _resFormula = "none";
            firstLine = false;
            continue;
        }

        _resolution.push_back(vstrings);

    }

}

void getMatchingToGen (TTreeReaderArray<Float_t> &recoEta, TTreeReaderArray<Float_t> &recoPhi, TTreeReaderArray<Float_t> &genEta, TTreeReaderArray<Float_t> &genPhi, vector<int> & matchingIdx) { // why do I need to pass the TTreeReaderArray by reference? If not, errors are prompted 
    // Error in <TTreeReader::RegisterValueReader>: Error registering reader for GenJet_phi: TTreeReaderValue/Array objects must be created before the call to Next() / SetEntry() / SetLocalEntry(), or after TTreeReader::Restart()!
    
    for (unsigned int i = 0; i < recoEta.GetSize(); i++) {
        
        float dRmin = 10.0;
        int matchIdx = -1;
        int idx = -1;
        for (unsigned int j = 0; j < genEta.GetSize(); j++) {

            Double_t dr = DeltaR(recoEta.At(i), genEta.At(j), recoPhi.At(i), genPhi.At(j));
            //cout << "dr: " << dr << endl;
            if (dr < dRmin) {

                dRmin = dr;
                idx = j;

            }
                
        }
        
        if (dRmin < 0.2) matchIdx = idx;
        matchingIdx.push_back(matchIdx);

    }

}

float GetJerFromFile(float eta, std::vector<std::vector<std::string>>  resSFs, int central){
    for (auto res: resSFs){//go through all the lines
        if (eta < std::stof(res[0]) || eta > std::stof(res[1])) continue; //if jet eta out of range, move to next line
        return std::stof(res[central+3]); //get SF. central == 0 ---> nominal, central == 1/2 ---> Down/Up
    }
    return 1.;
}

float GetStochasticFactor(float pt, float eta, float rho, std::vector<std::vector<std::string> >  resolution, TString  resFormula){
  
    TFormula resForm("",resFormula);

    for (auto res : resolution){
        //skip if not in the right bin
        if (eta < std::stof(res[0]) || eta > std::stof(res[1]) || rho < std::stof(res[2]) || rho > std::stof(res[3])) continue;
        resForm.SetParameter(0,std::stof(res[7]));
        resForm.SetParameter(1,std::stof(res[8]));
        resForm.SetParameter(2,std::stof(res[9]));
        resForm.SetParameter(3,std::stof(res[10]));
    }
    return resForm.Eval(pt);

}

float GetSmearFactor(float pt, float genPt, float eta, float rho, float jer_sf, std::vector<std::vector<std::string> > resolution, TString resFormula, TRandom3 ran){
    
    float smearFactor = 1.;
    float relpterr = GetStochasticFactor(pt,eta,rho,resolution,resFormula);
    if (genPt > 0. && (abs(pt-genPt)<3*relpterr*pt)) {
        double dPt = pt - genPt;
        smearFactor = 1 + (jer_sf - 1.) * dPt / pt;
     
    }
    else {
        smearFactor = 1 + ran.Gaus(0,relpterr)*std::sqrt(std::max(0.,(jer_sf*jer_sf)-1.));
        if (smearFactor <= 0.) smearFactor = 1.;
    }
    return smearFactor;
}

/////////////////////////









void objectTSelectorForNanoAOD::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void objectTSelectorForNanoAOD::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

///////////////////////////////////////

   if ( option.Contains( "JetHT")|| option.Contains( "SingleMuon") ) isdata = true;
   cout<<"is data?: "<<isdata<<endl;
    
   // TString inName = fChain->GetName();
   // cout<<inName<<endl;
   TString outFileName = option;
   outputfile = new TFile( outFileName, "RECREATE");
   cout<<"outputFileName: "<<outputfile->GetName()<<endl;
   
   
   h_genWeight = new TH1D( "h_genweight", "h_genweight", 1,-0.5, 0.5);

   tree = new TTree( "tree", "tree after object selection");
   allEvents = new TTree( "allevents", "events before any selection");

   allEvents->Branch( "genWeight_allEvents", &genWeight_allEvents, "genWeight_allEvents/D");

   makeBranch( tree, isdata );

   //Set up branch for pileup correction
   //inputPUFile_data = new TFile("/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/pileupCalc/2016/PUHistogram_data2016_postAPV.root", "READ");
   //inputPUFile_mc = new TFile("/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/pileupCalc/2016/PUHistogram_mc2016_postAPV.root", "READ");
   inputPUFile_data = new TFile("/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/pileupCalc/2016/PileupHistogram-goldenJSON-13tev-2016-postVFP-69200ub-99bins.root", "READ");
   inputPUFile_dataUp = new TFile("/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/pileupCalc/2016/PileupHistogram-goldenJSON-13tev-2016-postVFP-72400ub-99bins.root", "READ");
   inputPUFile_dataDown = new TFile("/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/pileupCalc/2016/PileupHistogram-goldenJSON-13tev-2016-postVFP-66000ub-99bins.root", "READ");
   inputPUFile_mc = new TFile("/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/pileupCalc/2016/PUHistogram_mc2016_postAPV.root", "READ");
   //Get needed histograms
    dataPileupProfile = (TH1F*)inputPUFile_data->Get("pileup");
    dataPileupProfileUp = (TH1F*)inputPUFile_dataUp->Get("pileup");
    dataPileupProfileDown = (TH1F*)inputPUFile_dataDown->Get("pileup");
    MCPileupProfile = (TH1F*)inputPUFile_mc->Get("pileup");
    //Scale to unit area for a fair comparison
    dataPileupProfile->Scale(1.0/dataPileupProfile->Integral());
    dataPileupProfileUp->Scale(1.0/dataPileupProfileUp->Integral());
    dataPileupProfileDown->Scale(1.0/dataPileupProfileDown->Integral());
    MCPileupProfile->Scale(1.0/MCPileupProfile->Integral());

    //Read files for jet smearing in MC
    readSmearingFile( "/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/smearing/2016/Summer20UL16_JRV3_MC_PtResolution_AK4PFchs.txt", resolution, resFormula );
    readSmearingFile( "/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/smearing/2016/Summer20UL16_JRV3_MC_SF_AK4PFchs.txt", resSFs, toyResFormula );    
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

   genWeight_allEvents = -99;
   //CHANGE HERE TO RUN ON DATA
   if ( !isdata ){
       h_genWeight->Fill( 0.0 , *Generator_weight );
       genWeight_allEvents = *Generator_weight;
   }
   
   allEvents->Fill();


   //MET filters
    if ( MetFilters ){
        if (!(*Flag_goodVertices == 1)) return kFALSE; // a branch in tree.
        if (!(*Flag_globalSuperTightHalo2016Filter == 1))    return kFALSE;
        if (!(*Flag_HBHENoiseFilter == 1))        return kFALSE;
        if (!(*Flag_HBHENoiseIsoFilter == 1))        return kFALSE;
        if (!(*Flag_EcalDeadCellTriggerPrimitiveFilter == 1))        return kFALSE; // a branch in Tree
        if (!(*Flag_BadPFMuonFilter == 1))      return kFALSE;
          //			if(!(*Flag_ecalBadCalibReducedMINIAODFilter==1))  return kFALSE;
          //			why this filter not work?//applied only in 2017 and 2018
        //CHANGE HERE TO RUN ON DATA 
		//if (isdata) {  if (!(*Flag_eeBadScFilter == 1)) return kFALSE;}
    }
    copyFlags();

    //HLT
    if ( HLTSelection){
        if (!(*HLT_PFHT450_SixJet40_BTagCSV_p056 == 1 ||*HLT_PFHT400_SixJet30_DoubleBTagCSV_p056==1 || *HLT_PFJet450 == 1) ) return kFALSE;
    }
    copyHLT();

    initializeBrancheValues();

    //Compute the per-event PU weight
    if (MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(*Pileup_nTrueInt)) > 0) {

        PUWeight_ = dataPileupProfile->GetBinContent(dataPileupProfile->FindBin(*Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(*Pileup_nTrueInt));
        PUWeight_Up = dataPileupProfileUp->GetBinContent(dataPileupProfileUp->FindBin(*Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(*Pileup_nTrueInt));
        PUWeight_Down = dataPileupProfileDown->GetBinContent(dataPileupProfileDown->FindBin(*Pileup_nTrueInt)) / MCPileupProfile->GetBinContent(MCPileupProfile->FindBin(*Pileup_nTrueInt));

    }
    

    vector<int> matchingIndices;
    getMatchingToGen(Jet_eta, Jet_phi, GenJet_eta, GenJet_phi, matchingIndices); //if a reco jet is unmatched, the corresponding gen jet pt will be 0
    vector<float> jetSmearingFactors;
    vector<float> jetSmearingFactorsUp;
    vector<float> jetSmearingFactorsDown;
    for (unsigned int i = 0; i < *nJet; i++) {

        float resSF = GetJerFromFile(Jet_eta.At(i), resSFs, 0);
        float resSFUp = GetJerFromFile(Jet_eta.At(i), resSFs, 2);
        float resSFDown = GetJerFromFile(Jet_eta.At(i), resSFs, 1);
        float smearFactor = GetSmearFactor(Jet_pt.At(i), GenJet_pt.At(matchingIndices.at(i)), Jet_eta.At(i), *fixedGridRhoFastjetAll, resSF, resolution, resFormula, jet_jer_myran);
        float smearFactorUp = GetSmearFactor(Jet_pt.At(i), GenJet_pt.At(matchingIndices.at(i)), Jet_eta.At(i), *fixedGridRhoFastjetAll, resSFUp, resolution, resFormula, jet_jer_myran);
        float smearFactorDown = GetSmearFactor(Jet_pt.At(i), GenJet_pt.At(matchingIndices.at(i)), Jet_eta.At(i), *fixedGridRhoFastjetAll, resSFDown, resolution, resFormula, jet_jer_myran);
        jetSmearingFactors.push_back(smearFactor);
        jetSmearingFactorsUp.push_back(smearFactorUp);
        jetSmearingFactorsDown.push_back(smearFactorDown);

    }

    vector<float> tauTESFactors;
    vector<float> tauTESFactorsUp;
    vector<float> tauTESFactorsDown;

    for (unsigned int i = 0; i < *nTau; i++) {
        
        TauESTool TESTool = TauESTool("UL2016_postVFP","DeepTau2017v2p1VSjet");
        float TESSF = TESTool.getTES(Tau_pt.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "");
        float TESSFUp = TESTool.getTES(Tau_pt.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "Up");
        float TESSFDown= TESTool.getTES(Tau_pt.At(i), Tau_decayMode.At(i), Tau_genPartFlav.At(i), "Down");
        tauTESFactors.push_back(TESSF);
        tauTESFactorsUp.push_back(TESSFUp);
        tauTESFactorsDown.push_back(TESSFDown);
        
    }

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
    SelectTaus( tausL, tauTESFactors, tausL_index, tausL_decayMode, tausL_genPartFlav, 1, leptonsMVAL); sort( tausL.begin(), tausL.end(), compEle);
    SelectTaus( tausF, tauTESFactors, tausF_index, tausF_decayMode, tausF_genPartFlav, 2, leptonsMVAL); sort( tausF.begin(), tausF.end(), compEle);
    SelectTaus( tausT, tauTESFactors, tausT_index, tausT_decayMode, tausT_genPartFlav, 3, leptonsMVAL); sort( tausT.begin(), tausT.end(), compEle);
    //Up TES
    SelectTaus( tausL_TESUp, tauTESFactorsUp, tausL_TESUp_index, tausL_TESUp_decayMode, tausL_TESUp_genPartFlav, 1, leptonsMVAL); sort( tausL_TESUp.begin(), tausL_TESUp.end(), compEle);
    SelectTaus( tausF_TESUp, tauTESFactorsUp, tausF_TESUp_index, tausF_TESUp_decayMode, tausF_TESUp_genPartFlav, 2, leptonsMVAL); sort( tausF_TESUp.begin(), tausF_TESUp.end(), compEle);
    SelectTaus( tausT_TESUp, tauTESFactorsUp, tausT_TESUp_index, tausT_TESUp_decayMode, tausT_TESUp_genPartFlav, 3, leptonsMVAL); sort( tausT_TESUp.begin(), tausT_TESUp.end(), compEle);
    //Down TES
    SelectTaus( tausL_TESDown, tauTESFactorsDown, tausL_TESDown_index, tausL_TESDown_decayMode, tausL_TESDown_genPartFlav, 1, leptonsMVAL); sort( tausL_TESDown.begin(), tausL_TESDown.end(), compEle);
    SelectTaus( tausF_TESDown, tauTESFactorsDown, tausF_TESDown_index, tausF_TESDown_decayMode, tausF_TESDown_genPartFlav, 2, leptonsMVAL); sort( tausF_TESDown.begin(), tausF_TESDown.end(), compEle);
    SelectTaus( tausT_TESDown, tauTESFactorsDown, tausT_TESDown_index, tausT_TESDown_decayMode, tausT_TESDown_genPartFlav, 3, leptonsMVAL); sort( tausT_TESDown.begin(), tausT_TESDown.end(), compEle);
    //???does here imply we need at least 1 leptons
    tausT_total = tausT_total + tausT.size();
    tausF_total = tausF_total + tausF.size();
    tausL_total = tausL_total + tausL.size();

    bool deepJet = true;
    bool SysJes = 0; bool SysJer=0;
    SelectJets(0, deepJet, jetSmearingFactors, jets, jets_btags, jets_index, jets_flavour, SysJes, SysJer, leptonsMVAL, tausL);
    SelectJets(0, deepJet, jetSmearingFactorsUp, jets_smearedUp, jets_btags_smearedUp, jets_index_smearedUp, jets_flavour_smearedUp, SysJes, SysJer, leptonsMVAL, tausL);
    SelectJets(0, deepJet, jetSmearingFactorsDown, jets_smearedDown, jets_btags_smearedDown, jets_index_smearedDown, jets_flavour_smearedDown, SysJes, SysJer, leptonsMVAL, tausL);
    // tprintElements( jets_btags, jets );
    // sort( jets.begin(), jets.end(), compEle);
    // pt are sorted in MINIAOD
    SelectJets(11, deepJet, jetSmearingFactors, bjetsL, bjetsL_btags, bjetsL_index, bjetsL_flavour, SysJes, SysJer,  leptonsMVAL, tausL);
    SelectJets(11, deepJet, jetSmearingFactorsUp, bjetsL_smearedUp, bjetsL_btags_smearedUp, bjetsL_index_smearedUp, bjetsL_flavour_smearedUp, SysJes, SysJer,  leptonsMVAL, tausL);
    SelectJets(11, deepJet, jetSmearingFactorsDown, bjetsL_smearedDown, bjetsL_btags_smearedDown, bjetsL_index_smearedDown, bjetsL_flavour_smearedDown, SysJes, SysJer,  leptonsMVAL, tausL);
    sort( bjetsL.begin(), bjetsL.end(), compEle);
    sort( bjetsL_smearedUp.begin(), bjetsL_smearedUp.end(), compEle);
    sort( bjetsL_smearedDown.begin(), bjetsL_smearedDown.end(), compEle);
    SelectJets(12, deepJet, jetSmearingFactors, bjetsM, bjetsM_btags, bjetsM_index, bjetsM_flavour,  SysJes, SysJer, leptonsMVAL, tausL);
    SelectJets(12, deepJet, jetSmearingFactorsUp, bjetsM_smearedUp, bjetsM_btags_smearedUp, bjetsM_index_smearedUp, bjetsM_flavour_smearedUp, SysJes, SysJer,  leptonsMVAL, tausL);
    SelectJets(12, deepJet, jetSmearingFactorsDown, bjetsM_smearedDown, bjetsM_btags_smearedDown, bjetsM_index_smearedDown, bjetsM_flavour_smearedDown, SysJes, SysJer,  leptonsMVAL, tausL);
    sort( bjetsM.begin(), bjetsM.end(), compEle);
    sort( bjetsM_smearedUp.begin(), bjetsM_smearedUp.end(), compEle);
    sort( bjetsM_smearedDown.begin(), bjetsM_smearedDown.end(), compEle);
    SelectJets(13, deepJet, jetSmearingFactors, bjetsT, bjetsT_btags, bjetsT_index, bjetsT_flavour, SysJes, SysJer, leptonsMVAL, tausL);
    SelectJets(13, deepJet, jetSmearingFactorsUp, bjetsT_smearedUp, bjetsT_btags_smearedUp, bjetsT_index_smearedUp, bjetsT_flavour_smearedUp, SysJes, SysJer,  leptonsMVAL, tausL);
    SelectJets(13, deepJet, jetSmearingFactorsDown, bjetsT_smearedDown, bjetsT_btags_smearedDown, bjetsT_index_smearedDown, bjetsT_flavour_smearedDown, SysJes, SysJer,  leptonsMVAL, tausL);
    sort( bjetsT.begin(), bjetsT.end(), compEle);
    sort( bjetsT_smearedUp.begin(), bjetsT_smearedUp.end(), compEle);
    sort( bjetsT_smearedDown.begin(), bjetsT_smearedDown.end(), compEle);
    SelectJets(2, deepJet, jetSmearingFactors, forwardJets, forwardJets_btags, forwardJets_index, forwardJets_flavour, SysJes,  SysJer,  leptonsMVAL, tausL);
    sort( forwardJets.begin(), forwardJets.end(), compEle);
    matchingIndices.clear();
    jetSmearingFactors.clear();
    jetSmearingFactorsUp.clear();
    jetSmearingFactorsDown.clear();
    tauTESFactors.clear();
    tauTESFactorsUp.clear();
    tauTESFactorsDown.clear();

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
    // PUWeight_ = *PUWeight;
    //???can not fine pileup weight in NanoAOD

    //CHANGE HERE TO RUN ON DATA
	
	if ( !isdata ){
        EVENT_genWeight_ = *genWeight;
    }
	
    //preselection
    if (preselection) {
        if ( !( tausL.size()>0)) return kFALSE;
		if ( !( jets.size()>1))  return kFALSE;
        if ( !( bjetsL.size()>1)) return kFALSE;
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

    inputPUFile_data->Close();
    delete inputPUFile_data;
    inputPUFile_dataUp->Close();
    delete inputPUFile_dataUp;
    inputPUFile_dataDown->Close();
    delete inputPUFile_dataDown;
    inputPUFile_mc->Close();
    delete inputPUFile_mc;

///////////////////////////////
    outputfile->Write();
    outputfile->Close();
    Info("Terminate", "processed %lld events", fProcessed);
    Info("Terminate", "passed %lld events", eventsPassed);
    Info("Terminate", "output file here: %s", outputfile->GetName());
///////////////////////////////




}


/////////////////
void objectTSelectorForNanoAOD::makeBranch( TTree* tree, Bool_t isdata ){
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
   tree->Branch( "tausF", &tausF );
   tree->Branch( "tausT", &tausT );
   tree->Branch( "tausL_index", &tausL_index );
   tree->Branch( "tausF_index", &tausF_index );
   tree->Branch( "tausT_index", &tausT_index );
   tree->Branch( "tausL_decayMode", &tausL_decayMode );
   tree->Branch( "tausF_decayMode", &tausF_decayMode );
   tree->Branch( "tausT_decayMode", &tausT_decayMode );
   tree->Branch( "tausL_genPartFlav", &tausL_genPartFlav );
   tree->Branch( "tausF_genPartFlav", &tausF_genPartFlav );
   tree->Branch( "tausT_genPartFlav", &tausT_genPartFlav );
   tree->Branch( "tausL_TESUp", &tausL_TESUp );
   tree->Branch( "tausF_TESUp", &tausF_TESUp );
   tree->Branch( "tausT_TESUp", &tausT_TESUp );
   tree->Branch( "tausL_TESUp_index", &tausL_TESUp_index );
   tree->Branch( "tausF_TESUp_index", &tausF_TESUp_index );
   tree->Branch( "tausT_TESUp_index", &tausT_TESUp_index );
   tree->Branch( "tausL_TESUp_decayMode", &tausL_TESUp_decayMode );
   tree->Branch( "tausF_TESUp_decayMode", &tausF_TESUp_decayMode );
   tree->Branch( "tausT_TESUp_decayMode", &tausT_TESUp_decayMode );
   tree->Branch( "tausL_TESUp_genPartFlav", &tausL_TESUp_genPartFlav );
   tree->Branch( "tausF_TESUp_genPartFlav", &tausF_TESUp_genPartFlav );
   tree->Branch( "tausT_TESUp_genPartFlav", &tausT_TESUp_genPartFlav );
   tree->Branch( "tausL_TESDown", &tausL_TESDown );
   tree->Branch( "tausF_TESDown", &tausF_TESDown );
   tree->Branch( "tausT_TESDown", &tausT_TESDown );
   tree->Branch( "tausL_TESDown_index", &tausL_TESDown_index );
   tree->Branch( "tausF_TESDown_index", &tausF_TESDown_index );
   tree->Branch( "tausT_TESDown_index", &tausT_TESDown_index );
   tree->Branch( "tausL_TESDown_decayMode", &tausL_TESDown_decayMode );
   tree->Branch( "tausF_TESDown_decayMode", &tausF_TESDown_decayMode );
   tree->Branch( "tausT_TESDown_decayMode", &tausT_TESDown_decayMode );
   tree->Branch( "tausL_TESDown_genPartFlav", &tausL_TESDown_genPartFlav );
   tree->Branch( "tausF_TESDown_genPartFlav", &tausF_TESDown_genPartFlav );
   tree->Branch( "tausT_TESDown_genPartFlav", &tausT_TESDown_genPartFlav );
   tree->Branch( "jets", &jets );
   tree->Branch( "jets_index", &jets_index );
   tree->Branch( "jets_flavour", &jets_flavour );
   tree->Branch( "jets_btags", &jets_btags );
   tree->Branch( "jets_smearedUp", &jets_smearedUp );
   tree->Branch( "jets_index_smearedUp", &jets_index_smearedUp );
   tree->Branch( "jets_flavour_smearedUp", &jets_flavour_smearedUp );
   tree->Branch( "jets_btags_smearedUp", &jets_btags_smearedUp );
   tree->Branch( "jets_smearedDown", &jets_smearedDown );
   tree->Branch( "jets_index_smearedDown", &jets_index_smearedDown );
   tree->Branch( "jets_flavour_smearedDown", &jets_flavour_smearedDown );
   tree->Branch( "jets_btags_smearedDown", &jets_btags_smearedDown );
   tree->Branch( "bjetsL", &bjetsL );
   tree->Branch( "bjetsL_index", &bjetsL_index );
   tree->Branch( "bjetsL_flavour", &bjetsL_flavour );
   tree->Branch( "bjetsL_btags", &bjetsL_btags );
   tree->Branch( "bjetsL_smearedUp", &bjetsL_smearedUp );
   tree->Branch( "bjetsL_index_smearedUp", &bjetsL_index_smearedUp );
   tree->Branch( "bjetsL_flavour", &bjetsL_flavour_smearedUp );
   tree->Branch( "bjetsL_btags_smearedUp", &bjetsL_btags_smearedUp );
   tree->Branch( "bjetsL_smearedDown", &bjetsL_smearedDown );
   tree->Branch( "bjetsL_index_smearedDown", &bjetsL_index_smearedDown );
   tree->Branch( "bjetsL_flavour", &bjetsL_flavour_smearedDown );
   tree->Branch( "bjetsL_btags_smearedDown", &bjetsL_btags_smearedDown );
   tree->Branch( "bjetsM", &bjetsM );
   tree->Branch( "bjetsM_index", &bjetsM_index );
   tree->Branch( "bjetsM_flavour", &bjetsM_flavour );
   tree->Branch( "bjetsM_btags", &bjetsM_btags );
   tree->Branch( "bjetsM_smearedUp", &bjetsM_smearedUp );
   tree->Branch( "bjetsM_index_smearedUp", &bjetsM_index_smearedUp );
   tree->Branch( "bjetsM_flavour", &bjetsM_flavour_smearedUp );
   tree->Branch( "bjetsM_btags_smearedUp", &bjetsM_btags_smearedUp );
   tree->Branch( "bjetsM_smearedDown", &bjetsM_smearedDown );
   tree->Branch( "bjetsM_index_smearedDown", &bjetsM_index_smearedDown );
   tree->Branch( "bjetsM_flavour", &bjetsM_flavour_smearedDown );
   tree->Branch( "bjetsM_btags_smearedDown", &bjetsM_btags_smearedDown );
   tree->Branch( "bjetsT", &bjetsT );
   tree->Branch( "bjetsT_index", &bjetsT_index );
   tree->Branch( "bjetsT_flavour", &bjetsT_flavour );
   tree->Branch( "bjetsT_btags", &bjetsT_btags );
   tree->Branch( "bjetsT_smearedUp", &bjetsT_smearedUp );
   tree->Branch( "bjetsT_index_smearedUp", &bjetsT_index_smearedUp );
   tree->Branch( "bjetsT_flavour", &bjetsT_flavour_smearedUp );
   tree->Branch( "bjetsT_btags_smearedUp", &bjetsT_btags_smearedUp );
   tree->Branch( "bjetsT_smearedDown", &bjetsT_smearedDown );
   tree->Branch( "bjetsT_index_smearedDown", &bjetsT_index_smearedDown );
   tree->Branch( "bjetsT_flavour", &bjetsT_flavour_smearedDown );
   tree->Branch( "bjetsT_btags_smearedDown", &bjetsT_btags_smearedDown );
   tree->Branch( "forwardJets", &forwardJets );
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
   
   if ( !isdata ){
       tree->Branch( "genTaus", &genTaus );
       tree->Branch( "genEles", &genEles );
       tree->Branch( "genMuons", &genMuons );
   }
   
   tree->Branch( "Met_pt", &Met_pt, "Met_pt/D" );
   tree->Branch( "Met_phi", &Met_phi, "Met_phi/D" );
   tree->Branch( "tops_toptagger", &tops_toptagger);

   tree->Branch( "EVENT_prefireWeight_", &EVENT_prefireWeight_, "EVENT_prefireWeight_/D" );
   tree->Branch( "PUWeight_", &PUWeight_, "PUWeight_/D");
   tree->Branch( "PUWeight_Up", &PUWeight_Up, "PUWeight_Up/D");
   tree->Branch( "PUWeight_Down", &PUWeight_Down, "PUWeight_Down/D");
   //CHANGE HERE TO RUN ON DATA
   
   if ( !isdata ){
       tree->Branch( "EVENT_genWeight_", &EVENT_genWeight_, "EVENT_genWeight_/D" );
   }
   
   tree->Branch( "Flag_goodVertices_", &Flag_goodVertices_, "Flag_goodVertices_/I");
   tree->Branch( "Flag_globalSuperTightHalo2016Filter_", &Flag_globalSuperTightHalo2016Filter_, "Flag_globalSuperTightHalo2016Filter_/I");
   tree->Branch( "Flag_HBHENoiseFilter_", &Flag_HBHENoiseFilter_, "Flag_HBHENoiseFilter_/I");
   tree->Branch( "Flag_HBHENoiseIsoFilter_", &Flag_HBHENoiseIsoFilter_, "Flag_HBHENoiseIsoFilter_/I");
   tree->Branch( "Flag_EcalDeadCellTriggerPrimitiveFilter_", &Flag_EcalDeadCellTriggerPrimitiveFilter_, "Flag_EcalDeadCellTriggerPrimitiveFilter_/I");
   tree->Branch( "Flag_BadPFMuonFilter_", &Flag_BadPFMuonFilter_, "Flag_BadPFMuonFilter_/I");
   tree->Branch( "Flag_eeBadScFilter_", &Flag_eeBadScFilter_, "Flag_eeBadScFilter_/I");

    tree->Branch( "HLT_PFHT450_SixJet40_BTagCSV_p056_", &HLT_PFHT450_SixJet40_BTagCSV_p056_, "HLT_PFHT450_SixJet40_BTagCSV_p056_/I");
    tree->Branch( "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_", &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_/I");
    tree->Branch( "HLT_PFJet450_", &HLT_PFJet450_, "HLT_PFJet450_/I");
	tree->Branch( "HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_", &HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_, "HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_/I");
    tree->Branch( "HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_", &HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_, "HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_/I");
    // tree->Branch( "HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_", &HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_, "HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_/I");
    // tree->Branch( "HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_", &HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_, "HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_/I");
    // tree->Branch( "HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_", &HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_, "HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_/I");
    // tree->Branch( "HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_", &HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_, "HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_/I");
    // tree->Branch( "HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_", &HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_, "HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_/I");//this HLT doesn't exist in ntuple
 
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
    // tree->Branch( "HLT_Ele35_WPTight_Gsf_", &HLT_Ele35_WPTight_Gsf_, "HLT_Ele35_WPTight_Gsf_/I");
    tree->Branch( "HLT_IsoMu27_", &HLT_IsoMu27_, "HLT_IsoMu27_/I");

    tree->Branch( "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_/I");
    tree->Branch( "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_/I");
    tree->Branch( "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_/I");
    // tree->Branch( "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_, "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_/I");
    // tree->Branch( "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_, "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_/I");
    tree->Branch( "HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_", &HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_, "HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_/I");
    // tree->Branch( "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_", &HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_, "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_/I");
    // tree->Branch( "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_", &HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_, "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_/I");

    tree->Branch( "HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_", &HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_, "HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_/I");
    tree->Branch( "HLT_DoubleEle33_CaloIdL_MW_", &HLT_DoubleEle33_CaloIdL_MW_, "HLT_DoubleEle33_CaloIdL_MW_/I");
    tree->Branch( "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_", &HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_, "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_/I");
    tree->Branch( "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_/I");
    tree->Branch( "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_/I");
    tree->Branch( "HLT_DoubleMu33NoFiltersNoVtx_", &HLT_DoubleMu33NoFiltersNoVtx_, "HLT_DoubleMu33NoFiltersNoVtx_/I");
    tree->Branch( "HLT_DoubleMu23NoFiltersNoVtxDisplaced_", &HLT_DoubleMu23NoFiltersNoVtxDisplaced_, "HLT_DoubleMu23NoFiltersNoVtxDisplaced_/I");
    tree->Branch( "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_/I");
    // tree->Branch( "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_/I");
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
    // tree->Branch( "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_", &HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_, "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_/I");
    tree->Branch( "HLT_TripleMu_12_10_5_", &HLT_TripleMu_12_10_5_, "HLT_TripleMu_12_10_5_/I");
    tree->Branch( "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_", &HLT_DiMu9_Ele9_CaloIdL_TrackIdL_, "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_/I");
/*}}}*/
}

void objectTSelectorForNanoAOD::SelectMuons(vector<TLorentzVector> &SelectedMuons,   vector<Int_t> &SelectedMuonsIndex,const Int_t type) { 
  // changed ISO to ss of TTTT
  // 0 for Loose; 1 fakeble; 2 tight 
    for (UInt_t j = 0; j < Muon_pt.GetSize(); ++j) {
        //in objectSelection.h Muon_pt_ is global variable
        if(!(Muon_pt.At(j)>10))                     continue;
        if (!(fabs(Muon_eta.At(j)) < 2.4))        continue;
        //ID
        if (type == 0) {
            if (!(Muon_looseId.At(j) == 1))              continue;
        }
        if (type == 1 or type == 2) {
            if (!(Muon_mediumId.At(j) == 1))     continue;
        }
        //ISO
        Double_t I1 = 0.4, I2 = 0, I3 = 0; // loose:WP from ss of TTTT
        if(type == 2){
            I1 = 0.16; I2 = 0.76, I3 = 7.2;
        }
        //Muon_jetRelIso = 1/ptRatio-1; ptRatio = 1/(Muon_jetRelIso+1)
        if (  !( (Muon_miniPFRelIso_all.At(j) < I1) && ((1/(Muon_jetRelIso.At(j)+1) > I2) || (Muon_jetPtRelv2.At(j) > I3))  )  )     continue;
        // IP
        if(!(fabs(Muon_dz.At(j))<0.1)) continue;
        if(!(fabs(Muon_dxy.At(j))<0.05)) continue;
        if(type == 1 or type == 2) {
          if(!(fabs(Muon_ip3d.At(j))<4)) continue;
        }
        //charge,The quality of the charge reconstruction 
        if ( type==1 || type==2 ){
            if ( !(Muon_tightCharge.At(j)<2) ) continue;
        }
        
        TLorentzVector muon;
        // muon.SetPtEtaPhiE(Muon_pt.At(j), Muon_eta.At(j), Muon_phi.At(j),
        muon.SetPtEtaPhiM(Muon_pt.At(j), Muon_eta.At(j), Muon_phi.At(j),
                          Muon_mass.At(j));
        SelectedMuons.push_back(muon);
        SelectedMuonsIndex.push_back(j);
    }
}


void objectTSelectorForNanoAOD::SelectElectronsMVA(vector<TLorentzVector> &SelectedElectrons,   vector<Int_t> &SelectedElectronsIndex, const Int_t type) {
  // 0 for VLoose; 1 for VLooseFO(fakeble object); 2 for tight
  // 2016 - MVANoIso94XV2, from SUSY
    for (UInt_t j = 0; j < Electron_pt.GetSize(); ++j) { /*{{{*/
        Double_t pt = Electron_pt.At(j);
        Double_t eta = Electron_eta.At(j);
        Double_t MVA_value = Electron_mvaFall17V2noIso.At(j);
        Double_t raw_MVA_value = 0.5 * log ( (1 + MVA_value)/(1 - MVA_value) );
        if (!(fabs(eta) < 2.5))      continue;
        if (!(pt > 10))         continue;
        // cout << "Electron_pt=" <<pt<<"\n ";

            // id
        if (fabs(eta) < 0.8)
        {
            if (type == 2) {
                if (10 < pt && pt < 40) {
                  if (!(raw_MVA_value > (3.447 + 0.063 * (pt - 25))))      continue;
                }
                if (pt >= 40) {
                  if (!(raw_MVA_value > 4.392))   continue;
                }
            }
            if (type == 0 || type==1) {
                if (5 < pt && pt < 10) {
                  if (!(raw_MVA_value > 1.309))  continue;
                }
                if (10 < pt && pt < 25) {
                  if (!(raw_MVA_value > ( 0.887 + 0.088 * (pt - 25))))  continue;
                }
                if (pt >= 25) {
                  if (!(raw_MVA_value > 0.887))  continue;
                }
            }
        }
        if (0.8 <= fabs(eta) && fabs(eta) < 1.479) {
            if (type == 2) {
                if (10 < pt && pt < 40) {
                    if (!(raw_MVA_value > (2.522 + 0.058 * (pt - 25))))      continue;
                }
                if (pt >= 40) {
                    if (!(raw_MVA_value > 3.392))      continue;
                }
            }
            if (type == 0 || type==1 ) {
                if (5 < pt && pt <= 10) {
                  if (!(raw_MVA_value > 0.373))           continue;
                }
                if (10 < pt && pt < 25) {
                  if (!(raw_MVA_value > (0.112 + 0.099 * (pt - 25))))    continue;
                }
                if (pt >= 25) {
                  if (!(raw_MVA_value > 0.112))     continue;
                }
            }
        }
        if (1.479 <= fabs(eta) && fabs(eta) < 2.5) {
            if (type == 2) {
                if (10 < pt && pt < 40) {
                  if (!(raw_MVA_value > (1.555 + 0.075 * (pt - 25))))         continue;
                }
                if (pt >= 40) {
                  if (!(raw_MVA_value > 2.680))                continue;
                }
            }
            if (type == 0 || type==1) {
                if (5 < pt && pt <= 10) {
                  if (!(raw_MVA_value > 0.071))   continue;
                }
                if (10 < pt && pt < 25) {
                  if (!(raw_MVA_value > ((-0.017) + 0.137 * (pt - 25))))   continue;
                }
                if (pt >= 25) {
                  if (!(raw_MVA_value > (-0.017)))              continue;
                }
            }
        }

         // ISO
        Double_t I1 = 0.4, I2 = 0, I3 = 0;
        if (type == 0 || type == 1) {
            I1 = 0.4;         I2 = 0;      I3 = 0;
        } // looseWP from ss of TTTT}
        if(type == 2) {I1 = 0.12; I2 = 0.80; I3 = 7.2;    }//TightWP of SS
        if (  !(  (Electron_miniPFRelIso_all.At(j) < I1) && (( 1/(Electron_jetRelIso.At(j)+1) > I2) || (Electron_jetPtRelv2.At(j) > I3))  )  )     continue;
  
      // IP
        if (!(fabs(Electron_dxy.At(j)) < 0.05))    continue;
        if (!(fabs(Electron_dz.At(j)) < 0.1))        continue;
        if (type == 1 or type == 2) {
            if (!((Electron_ip3d.At(j)) < 4))          continue;
        }
    
        //the number of missing pixel hits and a conversion veto based on the vertex fit probability. To reject electrons originating from photon conversion
        // cout << "Electron_lostHits= " << static_cast<int>(Eleictron_lostHits.At(j)) << "\n";
        //UChar_t is just int with 1 bit
        if (type == 0)
        {
            if ( !(Electron_lostHits.At(j)<=1) )  continue;
        }
        if ( type==1 || type==2 ){
            if ( !(Electron_lostHits.At(j)==0))  continue;
        }
        if ( !(Electron_convVeto.At(j)==1)) continue;
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


void objectTSelectorForNanoAOD::SelectTaus(vector<TLorentzVector> &SelectedTaus, vector<float> tauTESFactors, vector<Int_t> &SelectedTausIndex, vector<Int_t> &SelectedTausDecayMode, vector<int> &SelectedTausGenPartFlav, const Int_t TauWP, const vector<TLorentzVector> LeptonsMVAL) {
  // this is tau ID in ttH
  // 1:loose;2:fakeble;3:tight
  
  for (UInt_t j = 0; j < Tau_pt.GetSize(); ++j) {/*{{{*/
      
      if (!(Tau_pt.At(j)*tauTESFactors.at(j) > 20))     continue;
    if (!(Tau_eta.At(j) < 2.3 && Tau_eta.At(j) > -2.3))      continue;
    if (!( TMath::Abs(Tau_dz.At(j)) < 0.2) )      continue; 
    //???why no dxy requirement?
    // if (!(Tau_idDecayModeOldDMs.At(j) == 0))      continue;//already in NANOAOD
    if (TauWP == 2 || TauWP == 3) {
       if( Tau_decayMode.At(j) == 5 || Tau_decayMode.At(j) == 6)      continue;} // for decay mode
    if (TauWP == 1) {
      // if (!(Tau_byVVLooseDeepTau2017v2p1VSjet.At(j) > 0.5))        continue;
      if (!(Tau_idDeepTau2017v2p1VSjet.At(j)>2 ))        continue;
      // bitmask 1 = VVVLoose, 2 = VVLoose, 4 = VLoose, 8 = Loose, 16 = Medium, 32 = Tight, 64 = VTight, 128 = VVTight
    }
    if (TauWP == 2) {
      if ( !(Tau_idDeepTau2017v2p1VSjet.At(j) > 2 && Tau_idDeepTau2017v2p1VSmu.At(j) > 4 && Tau_idDeepTau2017v2p1VSe.At(j) > 1) )        continue;
    }
    if (TauWP == 3) { // channel specific in ttH. use the tight from 1t 1l
      if ( !( Tau_idDeepTau2017v2p1VSjet.At(j)>16 && Tau_idDeepTau2017v2p1VSmu.At(j) > 4 && Tau_idDeepTau2017v2p1VSe.At(j) > 1 ) )        continue;
    }
    //overlap removal
    Double_t minDeltaR_lep;
    if ( LeptonsMVAL.size() > 0){
        minDeltaR_lep = deltRmin(Tau_eta.At(j), Tau_phi.At(j), LeptonsMVAL);
        if( !(minDeltaR_lep >= 0.4 )) continue;
    }
    //?need err handling
    TLorentzVector tau;
    tau.SetPtEtaPhiM(Tau_pt.At(j), Tau_eta.At(j), Tau_phi.At(j),
                     Tau_mass.At(j));
    tau *= tauTESFactors.at(j); //apply TES correction
    SelectedTaus.push_back(tau);
    SelectedTausIndex.push_back(j);
    SelectedTausDecayMode.push_back(Tau_decayMode.At(j));
    SelectedTausGenPartFlav.push_back(Tau_genPartFlav.At(j));
  }
}/*}}}*/


void objectTSelectorForNanoAOD::SelectJets(const Int_t jetType, const bool deepJet, vector<float> jetSmearingFactors, vector<TLorentzVector> &SelectedJets,
                vector<Double_t> &SelectedJetsBTags, vector<Int_t> &SelectedJetsIndex, vector<Int_t> &SelectedJetsFlavor, const Int_t SysJes, const Int_t SysJer, const vector<TLorentzVector> LeptonsMVAF, const vector<TLorentzVector> SelectedTausL  /*, bool &deltaPhiJetMet*/) {
    // jetType=0  -> usual jets; we use loose ID
    // jetType=11 -> b-jets L, jetType=12 -> b-jets M, jetType=13 -> b-jets T, jetType=2  -> forward jets
    Double_t MostForwardJetEta =-99;/*{{{*/
    Double_t MostForwardJetPt = -99;
    Double_t MaxMostForwardJetEta = -99; 
    for (UInt_t j = 0; j < Jet_pt.GetSize(); ++j) {
        Double_t jetpt = Jet_pt[j]*jetSmearingFactors.at(j);
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
                if (!(Jet_btagDeepFlavB.At(j) > 0.0614))
                    continue;
            }
            if (jetType == 12) {
                if (!(Jet_btagDeepFlavB.At(j) > 0.3093))
                    continue;
            }
            if (jetType == 13) {
                if (!(Jet_btagDeepFlavB.At(j) > 0.7221))
                    continue;
            }
        } else {
            if (jetType == 11) {
                if (!(Jet_btagDeepB.At(j) > 0.2217))
                    continue;
            }
            if (jetType == 12) {
                if (!(Jet_btagDeepB.At(j) > 0.6321))
                    continue;
            }
            if (jetType == 13) {
                if (!(Jet_btagDeepB.At(j) > 0.8953))
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
        // Double_t SF = jetpt / Jet_pt.At(j);
        Double_t SF =1;
        TLorentzVector jet_prov;
        jet_prov.SetPtEtaPhiM(Jet_pt.At(j), Jet_eta.At(j), Jet_phi.At(j),
                Jet_mass.At(j));
        TLorentzVector jet;
        jet.SetPxPyPzE(SF * jet_prov.Px() * jetSmearingFactors.at(j), SF * jet_prov.Py() * jetSmearingFactors.at(j), SF * jet_prov.Pz() * jetSmearingFactors.at(j), SF * jet_prov.E() * jetSmearingFactors.at(j));
        //?is this  step necessary?
        //???why do this?
        SelectedJets.push_back(jet);
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
/*}}}*/
void objectTSelectorForNanoAOD::selectGenTaus( vector<TLorentzVector> &genTaus ){
    for (UInt_t j = 0; j < GenPart_pt.GetSize(); ++j) {
        if(!(abs(GenPart_genPartIdxMother.At(j))==24 && abs(GenPart_pdgId.At(j))==15)) continue;//tau:15; top:6;W:
        TLorentzVector gentau;
        gentau.SetPtEtaPhiM(GenPart_pt.At(j), GenPart_eta.At(j), GenPart_phi.At(j), GenPart_mass.At(j));
        genTaus.push_back(gentau);
    }
}
void objectTSelectorForNanoAOD::selectGenEles( vector<TLorentzVector> &genEles ){
    for (UInt_t j = 0; j < GenPart_pt.GetSize(); ++j) {
        if(!(abs(GenPart_genPartIdxMother.At(j))==24 && abs(GenPart_pdgId.At(j))==11)) continue;//tau:15; ele:11;
        TLorentzVector genele;
        genele.SetPtEtaPhiM(GenPart_pt.At(j), GenPart_eta.At(j), GenPart_phi.At(j), GenPart_mass.At(j));
        genEles.push_back(genele);
    }
}
void objectTSelectorForNanoAOD::selectGenMuons( vector<TLorentzVector> &genMuons ){
    for (UInt_t j = 0; j < GenPart_pt.GetSize(); ++j) {
        if(!(abs(GenPart_genPartIdxMother.At(j))==24  && abs(GenPart_pdgId.At(j))==13)) continue;//tau:15; top:6;W:;muon:13
        TLorentzVector genmuon;
        genmuon.SetPtEtaPhiM(GenPart_pt.At(j), GenPart_eta.At(j), GenPart_phi.At(j), GenPart_mass.At(j));
        genMuons.push_back(genmuon);
    }
}

void objectTSelectorForNanoAOD::copyHLT(){
    HLT_PFHT450_SixJet40_BTagCSV_p056_ = *HLT_PFHT450_SixJet40_BTagCSV_p056;
    HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ = *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056;
	HLT_PFJet450_ = *HLT_PFJet450;
    //???it seems some triggers are not present in NanoAOD
    HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_ = *HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg;
    HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_ = *HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg;
    // HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_ = *HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg;
    // HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_ = *HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg;
    // HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_ = *HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg;
    // HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_ = *HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg;
    // HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_ = *HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg;//this HLT doesn't exist in ntuple
 
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
    // HLT_Ele35_WPTight_Gsf_ = *HLT_Ele35_WPTight_Gsf;
    HLT_IsoMu27_ = *HLT_IsoMu27;

    HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_ = *HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20;
    HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_ = *HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1;
    HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_ = *HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30;
    // HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_ = *HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1;
    // HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_ = *HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1;
    HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_ = *HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1;
    // HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_ = *HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1;
    // HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_ = *HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1;

    HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_ = *HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf;
    HLT_DoubleEle33_CaloIdL_MW_ = *HLT_DoubleEle33_CaloIdL_MW;
    HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_ = *HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW;
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_ = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
    HLT_DoubleMu33NoFiltersNoVtx_ = *HLT_DoubleMu33NoFiltersNoVtx;
    HLT_DoubleMu23NoFiltersNoVtxDisplaced_ = *HLT_DoubleMu23NoFiltersNoVtxDisplaced;
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_ = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
    // HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
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
    // HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_ = *HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ;
    HLT_TripleMu_12_10_5_ = *HLT_TripleMu_12_10_5;
    HLT_DiMu9_Ele9_CaloIdL_TrackIdL_ = *HLT_DiMu9_Ele9_CaloIdL_TrackIdL;
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
    tausL.clear(); tausL_index.clear(); tausL_genPartFlav.clear(); tausL_decayMode.clear();
    tausF.clear(); tausF_index.clear(); tausF_genPartFlav.clear(); tausF_decayMode.clear();
    tausT.clear(); tausT_index.clear(); tausT_genPartFlav.clear(); tausT_decayMode.clear();
    
    tausL_TESUp.clear(); tausL_TESUp_index.clear(); tausL_TESUp_genPartFlav.clear(); tausL_TESUp_decayMode.clear();
    tausF_TESUp.clear(); tausF_TESUp_index.clear(); tausF_TESUp_genPartFlav.clear(); tausF_TESUp_decayMode.clear();
    tausT_TESUp.clear(); tausT_TESUp_index.clear(); tausT_TESUp_genPartFlav.clear(); tausT_TESUp_decayMode.clear();
    tausL_TESDown.clear(); tausL_TESDown_index.clear(); tausL_TESDown_genPartFlav.clear(); tausL_TESDown_decayMode.clear();
    tausF_TESDown.clear(); tausF_TESDown_index.clear(); tausF_TESDown_genPartFlav.clear(); tausF_TESDown_decayMode.clear();
    tausT_TESDown.clear(); tausT_TESDown_index.clear(); tausT_TESDown_genPartFlav.clear(); tausT_TESDown_decayMode.clear();
    jets.clear(); jets_index.clear(); jets_flavour.clear(); jets_btags.clear();
    jets_smearedUp.clear(); jets_index_smearedUp.clear(); jets_flavour_smearedUp.clear(); jets_btags_smearedUp.clear();
    jets_smearedDown.clear(); jets_index_smearedDown.clear(); jets_flavour_smearedDown.clear(); jets_btags_smearedDown.clear();
    bjetsL.clear(); bjetsL_index.clear(); bjetsL_flavour.clear(); bjetsL_btags.clear();
    bjetsL_smearedUp.clear(); bjetsL_index_smearedUp.clear(); bjetsL_flavour_smearedUp.clear(); bjetsL_btags_smearedUp.clear();
    bjetsL_smearedDown.clear(); bjetsL_index_smearedDown.clear(); bjetsL_flavour_smearedDown.clear(); bjetsL_btags_smearedDown.clear();
    bjetsM.clear(); bjetsM_index.clear(); bjetsM_flavour.clear(); bjetsM_btags.clear();
    bjetsM_smearedUp.clear(); bjetsM_index_smearedUp.clear(); bjetsM_flavour_smearedUp.clear(); bjetsM_btags_smearedUp.clear();
    bjetsM_smearedDown.clear(); bjetsM_index_smearedDown.clear(); bjetsM_flavour_smearedDown.clear(); bjetsM_btags_smearedDown.clear();
    bjetsT.clear(); bjetsT_index.clear(); bjetsT_flavour.clear(); bjetsT_btags.clear();
    bjetsT_smearedUp.clear(); bjetsT_index_smearedUp.clear(); bjetsT_flavour_smearedUp.clear(); bjetsT_btags_smearedUp.clear();
    bjetsT_smearedDown.clear(); bjetsT_index_smearedDown.clear(); bjetsT_flavour_smearedDown.clear(); bjetsT_btags_smearedDown.clear();
    forwardJets.clear(); forwardJets_index.clear(); forwardJets_flavour.clear(); forwardJets_btags.clear();
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

}
