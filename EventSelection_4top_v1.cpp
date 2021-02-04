#include "EventSelection_4top_v1.h"
#include "math.h"
#include <algorithm>

void EventSelection_4top_v1(
    const bool istest = true,
    // const TString input = "TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root",
    // const TString input = "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8.root",
    // const TString input = "Legacy16V2_TauBlockBHLTToptaggerAdded_EJetMetUpdated_oldEIDBack_0000.root",
    const TString inputDir = "TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8/Legacy16V2_TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8addGenWeight/210201_023242/0000/",
    const TString outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/NewNtupleAfterEventSelection_test/v3/")
       // const TString outputDir = "/publicfs/cms/user/fabioiemmi/TauOfTTTT/2016v1/tests/")
{
    gStyle->SetCanvasColor(0);
    gStyle->SetFrameBorderMode(0); //?
    gStyle->SetOptStat("rme");
    gStyle->SetPalette(1, 0);
    gStyle->SetTitleX(0.50);
    gStyle->SetTitleY(0.96);
    gStyle->SetPaintTextFormat(".2f");
  
    const bool isHLTstudy = false;
    const bool preselection = true; // associate with selection
    const bool sideband = false;    // associate with selection
    //?what's sideband and signal ?
    const bool signal = false;
    //?signal occur nowhere else	//what does these mean?
    // SYSTEMATICS: 0 is standard, 1 is UP, 2 is down
    const int SysJes = 0; // jet enenrgy scale
    const int SysJer = 0; // jet  energy resolution
  
    using namespace std;
  
      TString newFile; // file already exist, new file is what we want build.
      //?it seems Jes and Jer can not aplly together?
      // TString input = inputDir.ReplaceAll( "/Legacy16V2*0000/", "")  ;
      TString input = "TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root";
      cout<<input<<endl;
      if ((SysJes == 0) && (SysJer == 0)) newFile = outputDir + "NoJEC/" + input;
      if ((SysJes == 1) && (SysJer == 0))  newFile = outputDir + "JESup/" + input;
      if ((SysJes == 2) && (SysJer == 0))  newFile = outputDir + "JESdo/" + input;
      if ((SysJes == 0) && (SysJer == 1))  newFile = outputDir + "JERdo/" + input;
      if ((SysJes == 0) && (SysJer == 2))  newFile = outputDir + "JERup/" + input;
      bool data = true;
      cout << "data" << data << endl;
      //    if(fileName.size()==0) break;
      if ( !(input.Contains( "TauBlock")))   data = false; // find():The position of the first character of the first // match.
      cout << "data" << data << endl;
      cout<<"New file here : "<<newFile<<endl;
      //    TFile f(newFile,"new");//Create a new file and open it for // writing, if the file already exists the file is not opened.
      TFile f(newFile, "RECREATE"); // Create a new file, if the file already// exists it will be overwritten.
      TTree *NewTree = new TTree("tree", "tree");
      TTree *NewTreeSB = new TTree("treeSB", "treeSB");
      //why 2 trees? what's the different?		//treeSB has something todo with sideband
      TString inputFile; TString inputBase = "/publicfs/cms/data/TopQuark/FourTop_hua/v3/2016/";
      if (data)    inputFile = inputBase + inputDir;
      else inputFile = inputBase + inputDir;
      static TChain chain("TNT/BOOM");
      chain.Add(inputFile+"v3*.root");
      // chain.Print();
      // const char *FILE = inputFile.c_str();
      // TFile *file = TFile::Open(inputFile);
      // Tree = (TTree *)file->Get(openTree); // sprintf(openTree, "TNT/BOOM")
      Long64_t nentries =    (Int_t)chain.GetEntries(); // how do we know the entries of Tree?//Read
      for (int selection = 0; selection < 3; selection++) {
        //? it seems when pre = false, sideband=true,both 1 and 2 will go in the
        // loop.signal=false
        // selection = 0 -> preselection=true; line 19, true
        // selection = 1 -> signal selection; preselection=false and, not continue
        // , that means go to the next line of the loop.
        // selection = 2 -> sideband=true and pre=false; line 14 sideband=false
        if (!((preselection && selection == 0) ||
              (!preselection && sideband && (selection == 1 || selection == 2)) ||
              (!preselection && !sideband && selection == 1)))
          continue;
        // preselection=true ,sideband=false,in this case selection=0
        //what does sideband and signal do?
        //        branch(data,selection,NewTree,NewTreeSB,input);Tree->SetBranchAddress;NewTree and SB->Branch
        chain.SetBranchAddress("Jet_pt", &Jet_pt_, &b_Jet_pt);
        branch(data, selection, NewTree,  NewTreeSB , chain); // Tree->SetBranchAddress("Jet_pt",   &Jet_pt_,   &b_Jet_pt);
        //???chain is in local scope, cannot be seen in branch?
        Long64_t NumOfEvents;
        if (istest) {
          NumOfEvents = 1000;
        } else {
          NumOfEvents = nentries;
        }
        for (Long64_t i = 0; i < NumOfEvents; i++) {
          Long64_t tentry = chain.LoadTree(i); // Set current entry.
          branchGetEntry(data, tentry);        // every branch in Tree, Getentry.        // b_Jet_pt->GetEntry(tentry);//is a branch in tree, setadress.
  
          h_genWeight->Fill( 0.0 , genWeight_ );
  
  
          initializeVar(); // initialize for new tree.
          if ( !isHLTstudy ){
               //			if(!(HLT_PFHT900_==1 ||
              // HLT_PFHT450_SixJet40_BTagCSV_p056_==1||HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_==1))  continue;//a branch in tree, trigger we choose
              if (!(Flag_goodVertices_ == 1))
                continue; // a branch in tree.
              if (!(Flag_globalSuperTightHalo2016Filter_ == 1))
                continue;
              if (!(Flag_HBHENoiseFilter_ == 1))
                continue;
              if (!(Flag_HBHENoiseIsoFilter_ == 1))
                continue;
              if (!(Flag_EcalDeadCellTriggerPrimitiveFilter_ == 1))
                continue; // a branch in Tree
              if (!(Flag_BadPFMuonFilter_ == 1))
                continue;
              //			if(!(Flag_ecalBadCalibReducedMINIAODFilter_==1))
              // continue;
              //			why this filter not work?//applied only in 2017 and 2018
              if (data) {
                if (!(Flag_eeBadScFilter_ == 1)) continue;
              }
          }
          
          
          //HLT branches
           HLT_PFHT900  = HLT_PFHT900_;
           HLT_PFHT450_SixJet40_BTagCSV_p056  = HLT_PFHT450_SixJet40_BTagCSV_p056_;
           HLT_PFHT400_SixJet30_DoubleBTagCSV_p056  = HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_;
           HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg  = HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_;
           HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg  = HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_;
           HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg  = HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_;
           HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg  = HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_;
           HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg  = HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_;
           HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg  = HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_;
           HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg  = HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_;//this HLT doesn't exist in ntuple
  
           HLT_Ele27_eta2p1_WPTight_Gsf  = HLT_Ele27_eta2p1_WPTight_Gsf_;
           HLT_Ele27_eta2p1_WPLoose_Gsf  = HLT_Ele27_eta2p1_WPLoose_Gsf_;
           HLT_Ele27_WPTight_Gsf  = HLT_Ele27_WPTight_Gsf_;
           HLT_IsoMu22  = HLT_IsoMu22_;
           HLT_Ele25_eta2p1_WPTight_Gsf  = HLT_Ele25_eta2p1_WPTight_Gsf_;
           HLT_IsoTkMu22  = HLT_IsoTkMu22_;
           HLT_IsoMu24  = HLT_IsoMu24_;
           HLT_IsoTkMu24  = HLT_IsoTkMu24_;
           HLT_IsoMu22_eta2p1  = HLT_IsoMu22_eta2p1_;
           HLT_IsoTkMu22_eta2p1  = HLT_IsoTkMu22_eta2p1_;
           HLT_Mu50  = HLT_Mu50_;
           HLT_TkMu50  = HLT_TkMu50_;
           HLT_Ele32_WPTight_Gsf  = HLT_Ele32_WPTight_Gsf_;
           HLT_Ele35_WPTight_Gsf  = HLT_Ele35_WPTight_Gsf_;
           HLT_IsoMu27  = HLT_IsoMu27_;
 
          HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20  = HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_;
          HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1  = HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_;
          HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30  = HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_;
          HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1  = HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_;
          HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1  = HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_;
          HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1  = HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_;
          HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1  = HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_;
          HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1  = HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_;
  
          HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf  = HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_;
          HLT_DoubleEle33_CaloIdL_MW  = HLT_DoubleEle33_CaloIdL_MW_;
          HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW  = HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_;
          HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ  = HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
          HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL  = HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_;
          HLT_DoubleMu33NoFiltersNoVtx  = HLT_DoubleMu33NoFiltersNoVtx_;
          HLT_DoubleMu23NoFiltersNoVtxDisplaced  = HLT_DoubleMu23NoFiltersNoVtxDisplaced_;
          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ  = HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_;
          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8  = HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_;
          HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL = HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_;
          HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_;
          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL  = HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_;
          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ  = HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
          HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL = HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_;
          HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ = HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_;
          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL  = HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_;
          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ  = HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL  = HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_;
          HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ  = HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
  
          HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL  = HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_;
          HLT_Mu8_DiEle12_CaloIdL_TrackIdL  = HLT_Mu8_DiEle12_CaloIdL_TrackIdL_;
          HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ  = HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_;
          HLT_TripleMu_12_10_5  = HLT_TripleMu_12_10_5_;
          HLT_DiMu9_Ele9_CaloIdL_TrackIdL  = HLT_DiMu9_Ele9_CaloIdL_TrackIdL_;
  
  
  
          //gen tau and lepton
          if ( !data ){
              vector<TLorentzVector> genTaus; 
              vector<TLorentzVector> genEles;
              vector<TLorentzVector> genMuons;
              selectGenTaus(genTaus);
              selectGenEles(genEles);
              selectGenMuons(genMuons);
          sort(genEles.begin(), genEles.end(), compEle);
          sort(genMuons.begin(), genMuons.end(), compEle);
              genTaus_number = genTaus.size();
              genEles_number = genEles.size();
              genMuons_number = genMuons.size();
          
          for (int i = 0; i < genEles_number; i++) {
  
            genEle_pt.push_back(genEles.at(i).Pt());
            genEle_eta.push_back(genEles.at(i).Eta());
            genEle_phi.push_back(genEles.at(i).Phi());
            genEle_E.push_back(genEles.at(i).E());
            
          }
  
          for (int i = 0; i < genMuons_number; i++) {
  
            genMuon_pt.push_back(genMuons.at(i).Pt());
            genMuon_eta.push_back(genMuons.at(i).Eta());
            genMuon_phi.push_back(genMuons.at(i).Phi());
            genMuon_E.push_back(genMuons.at(i).E());
            
          }
          }
  
  
          if (!data)
            GenClassifier(GenZPt, GenWPt); // according to pdg ID generate the
                                           // number of  usdc quark and GenZPt
                                           // GenWPt.
          // not sure what our analysis can do with it
  
          // met
          //?need to check met
          //			bool SelectedMet = false;
          //?how does SysJes impact Met_pt ?//?do we still have to correct Met?
          MetCorrection(SysJes, SysJer, Met_pt); // Met_pt in newtree branch.
          // why have to do this MetCorrection//take jet SF into
          // consideration.correct met_pt
          //            if( Met_pt > 200)  SelectedMet = true;//228;parameter in
          // Fillbranches
          // we don't care about Met so much
          // Met_pt            = Met_type1PF_pt_;
          Met_phi = Met_type1PF_phi_; // Met_phi branch in newtree and SB
  
          // lepton selection
          vector<TLorentzVector> SelectedElectronsL;
          vector<int> SelectedElectronsLIndex;
          vector<TLorentzVector> SelectedElectronsM;
          vector<int> SelectedElectronsMIndex;
          vector<TLorentzVector> SelectedElectronsT;
          vector<int> SelectedElectronsTIndex;
          vector<TLorentzVector> SelectedElectronsVeto;
          vector<int> SelectedElectronsVetoIndex;
          SelectElectrons(SelectedElectronsL, SelectedElectronsLIndex, 0);//cut based ID
          SelectElectrons(SelectedElectronsM, SelectedElectronsMIndex, 1);
          SelectElectrons(SelectedElectronsT, SelectedElectronsTIndex, 2);
          SelectElectrons(SelectedElectronsVeto, SelectedElectronsVetoIndex, 3); 
  
          eleL_number = SelectedElectronsL.size();
          eleM_number = SelectedElectronsM.size();
          eleT_number = SelectedElectronsT.size();
  
          vector<TLorentzVector> SelectedMuonsL;
          vector<int> SelectedMuonsLIndex;
          vector<TLorentzVector> SelectedMuonsF;
          vector<int> SelectedMuonsFIndex;
          vector<TLorentzVector> SelectedMuonsT;
          vector<int> SelectedMuonsTIndex;
          SelectMuons(SelectedMuonsL, SelectedMuonsLIndex, 0, 4);
          SelectMuons(SelectedMuonsF, SelectedMuonsFIndex, 1, 4);
          SelectMuons(SelectedMuonsT, SelectedMuonsTIndex, 2, 4);//this T is actually the medium in SS
  
      sort(SelectedMuonsL.begin(), SelectedMuonsL.end(), compEle);
          sort(SelectedMuonsF.begin(), SelectedMuonsF.end(), compEle);
          sort(SelectedMuonsT.begin(), SelectedMuonsT.end(), compEle);
  
          muonsL_number = SelectedMuonsL.size();
          muonsF_number = SelectedMuonsF.size();
          muonsT_number = SelectedMuonsT.size();
  
      for (int i = 0; i < muonsL_number; i++) {
  
            muonL_pt.push_back(SelectedMuonsL.at(i).Pt());
            muonL_eta.push_back(SelectedMuonsL.at(i).Eta());
            muonL_phi.push_back(SelectedMuonsL.at(i).Phi());
            muonL_E.push_back(SelectedMuonsL.at(i).E());
            
          }
  
      for (int i = 0; i < muonsF_number; i++) {
  
            muonF_pt.push_back(SelectedMuonsF.at(i).Pt());
            muonF_eta.push_back(SelectedMuonsF.at(i).Eta());
            muonF_phi.push_back(SelectedMuonsF.at(i).Phi());
            muonF_E.push_back(SelectedMuonsF.at(i).E());
            
          }
  
      for (int i = 0; i < muonsT_number; i++) {
  
            muonT_pt.push_back(SelectedMuonsT.at(i).Pt());
            muonT_eta.push_back(SelectedMuonsT.at(i).Eta());
            muonT_phi.push_back(SelectedMuonsT.at(i).Phi());
            muonT_E.push_back(SelectedMuonsT.at(i).E());
            
          }
  
      //store here information about muons at each stage
      // stage 0
      vector<TLorentzVector> SelectedMuonsL_s0;
          vector<int> SelectedMuonsLIndex_s0;
          vector<TLorentzVector> SelectedMuonsF_s0;
          vector<int> SelectedMuonsFIndex_s0;
          vector<TLorentzVector> SelectedMuonsT_s0;
          vector<int> SelectedMuonsTIndex_s0;
          SelectMuons(SelectedMuonsL_s0, SelectedMuonsLIndex_s0, 0, 0);
          SelectMuons(SelectedMuonsF_s0, SelectedMuonsFIndex_s0, 1, 0);
          SelectMuons(SelectedMuonsT_s0, SelectedMuonsTIndex_s0, 2, 0);//this T is actually the medium in SS
         
      sort(SelectedMuonsL_s0.begin(), SelectedMuonsL_s0.end(), compEle);
          sort(SelectedMuonsF_s0.begin(), SelectedMuonsF_s0.end(), compEle);
          sort(SelectedMuonsT_s0.begin(), SelectedMuonsT_s0.end(), compEle);
  
      muonsL_number_s0 = SelectedMuonsL_s0.size();
          muonsF_number_s0 = SelectedMuonsF_s0.size();
          muonsT_number_s0 = SelectedMuonsT_s0.size();
  
      for (int i = 0; i < muonsL_number_s0; i++) {
   
            muonL_pt_s0.push_back(SelectedMuonsL_s0.at(i).Pt());
            muonL_eta_s0.push_back(SelectedMuonsL_s0.at(i).Eta());
            muonL_phi_s0.push_back(SelectedMuonsL_s0.at(i).Phi());
            muonL_E_s0.push_back(SelectedMuonsL_s0.at(i).E());
            
          }
  
      for (int i = 0; i < muonsF_number_s0; i++) {
  
            muonF_pt_s0.push_back(SelectedMuonsF_s0.at(i).Pt());
            muonF_eta_s0.push_back(SelectedMuonsF_s0.at(i).Eta());
            muonF_phi_s0.push_back(SelectedMuonsF_s0.at(i).Phi());
            muonF_E_s0.push_back(SelectedMuonsF_s0.at(i).E());
            
          }
  
      for (int i = 0; i < muonsT_number_s0; i++) {
  
            muonT_pt_s0.push_back(SelectedMuonsT_s0.at(i).Pt());
            muonT_eta_s0.push_back(SelectedMuonsT_s0.at(i).Eta());
            muonT_phi_s0.push_back(SelectedMuonsT_s0.at(i).Phi());
            muonT_E_s0.push_back(SelectedMuonsT_s0.at(i).E());
            
          }
  
      // stage 1                                                                                                                                                                            
          vector<TLorentzVector> SelectedMuonsL_s1;
          vector<int> SelectedMuonsLIndex_s1;
          vector<TLorentzVector> SelectedMuonsF_s1;
          vector<int> SelectedMuonsFIndex_s1;
          vector<TLorentzVector> SelectedMuonsT_s1;
          vector<int> SelectedMuonsTIndex_s1;
          SelectMuons(SelectedMuonsL_s1, SelectedMuonsLIndex_s1, 0, 1);
          SelectMuons(SelectedMuonsF_s1, SelectedMuonsFIndex_s1, 1, 1);
          SelectMuons(SelectedMuonsT_s1, SelectedMuonsTIndex_s1, 2, 1);//this T is actually the medium in
  
      sort(SelectedMuonsL_s1.begin(), SelectedMuonsL_s1.end(), compEle);
          sort(SelectedMuonsF_s1.begin(), SelectedMuonsF_s1.end(), compEle);
          sort(SelectedMuonsT_s1.begin(), SelectedMuonsT_s1.end(), compEle);
      
          muonsL_number_s1 = SelectedMuonsL_s1.size();
          muonsF_number_s1 = SelectedMuonsF_s1.size();
          muonsT_number_s1 = SelectedMuonsT_s1.size();
      
      for (int i = 0; i < muonsL_number_s1; i++) {
  
        muonL_pt_s1.push_back(SelectedMuonsL_s1.at(i).Pt());
        muonL_eta_s1.push_back(SelectedMuonsL_s1.at(i).Eta());
        muonL_phi_s1.push_back(SelectedMuonsL_s1.at(i).Phi());
        muonL_E_s1.push_back(SelectedMuonsL_s1.at(i).E());
  
      }
  
          for (int i = 0; i < muonsF_number_s1; i++) {
  
        muonF_pt_s1.push_back(SelectedMuonsF_s1.at(i).Pt());
        muonF_eta_s1.push_back(SelectedMuonsF_s1.at(i).Eta());
        muonF_phi_s1.push_back(SelectedMuonsF_s1.at(i).Phi());
        muonF_E_s1.push_back(SelectedMuonsF_s1.at(i).E());
  
      }
  
          for (int i = 0; i < muonsT_number_s1; i++) {
  
        muonT_pt_s1.push_back(SelectedMuonsT_s1.at(i).Pt());
        muonT_eta_s1.push_back(SelectedMuonsT_s1.at(i).Eta());
        muonT_phi_s1.push_back(SelectedMuonsT_s1.at(i).Phi());
        muonT_E_s1.push_back(SelectedMuonsT_s1.at(i).E());
      
          }
  
      // stage 2                                                                                                                                                                             
          vector<TLorentzVector> SelectedMuonsL_s2;
          vector<int> SelectedMuonsLIndex_s2;
          vector<TLorentzVector> SelectedMuonsF_s2;
          vector<int> SelectedMuonsFIndex_s2;
          vector<TLorentzVector> SelectedMuonsT_s2;
          vector<int> SelectedMuonsTIndex_s2;
          SelectMuons(SelectedMuonsL_s2, SelectedMuonsLIndex_s2, 0, 2);
          SelectMuons(SelectedMuonsF_s2, SelectedMuonsFIndex_s2, 1, 2);
          SelectMuons(SelectedMuonsT_s2, SelectedMuonsTIndex_s2, 2, 2);//this T is actually the medium in SS 
  
      sort(SelectedMuonsL_s2.begin(), SelectedMuonsL_s2.end(), compEle);
          sort(SelectedMuonsF_s2.begin(), SelectedMuonsF_s2.end(), compEle);
          sort(SelectedMuonsT_s2.begin(), SelectedMuonsT_s2.end(), compEle);
                                                                                       
          muonsL_number_s2 = SelectedMuonsL_s2.size();
          muonsF_number_s2 = SelectedMuonsF_s2.size();
          muonsT_number_s2 = SelectedMuonsT_s2.size();
          
      for (int i = 0; i < muonsL_number_s2; i++) {
  
        muonL_pt_s2.push_back(SelectedMuonsL_s2.at(i).Pt());
        muonL_eta_s2.push_back(SelectedMuonsL_s2.at(i).Eta());
        muonL_phi_s2.push_back(SelectedMuonsL_s2.at(i).Phi());
        muonL_E_s2.push_back(SelectedMuonsL_s2.at(i).E());
  
      }
  
          for (int i = 0; i < muonsF_number_s2; i++) {
  
        muonF_pt_s2.push_back(SelectedMuonsF_s2.at(i).Pt());
        muonF_eta_s2.push_back(SelectedMuonsF_s2.at(i).Eta());
        muonF_phi_s2.push_back(SelectedMuonsF_s2.at(i).Phi());
        muonF_E_s2.push_back(SelectedMuonsF_s2.at(i).E());
  
      }
  
          for (int i = 0; i < muonsT_number_s2; i++) {
  
        muonT_pt_s2.push_back(SelectedMuonsT_s2.at(i).Pt());
        muonT_eta_s2.push_back(SelectedMuonsT_s2.at(i).Eta());
        muonT_phi_s2.push_back(SelectedMuonsT_s2.at(i).Phi());
        muonT_E_s2.push_back(SelectedMuonsT_s2.at(i).E());
      
          }
  
      // stage 3
          vector<TLorentzVector> SelectedMuonsL_s3;
          vector<int> SelectedMuonsLIndex_s3;
          vector<TLorentzVector> SelectedMuonsF_s3;
          vector<int> SelectedMuonsFIndex_s3;
          vector<TLorentzVector> SelectedMuonsT_s3;
          vector<int> SelectedMuonsTIndex_s3;
          SelectMuons(SelectedMuonsL_s3, SelectedMuonsLIndex_s3, 0, 3);
          SelectMuons(SelectedMuonsF_s3, SelectedMuonsFIndex_s3, 1, 3);
          SelectMuons(SelectedMuonsT_s3, SelectedMuonsTIndex_s3, 2, 3);//this T is actually the medium in SS                                                                                      
      sort(SelectedMuonsL_s3.begin(), SelectedMuonsL_s3.end(), compEle);
          sort(SelectedMuonsF_s3.begin(), SelectedMuonsF_s3.end(), compEle);
          sort(SelectedMuonsT_s3.begin(), SelectedMuonsT_s3.end(), compEle);
  
          muonsL_number_s3 = SelectedMuonsL_s3.size();
          muonsF_number_s3 = SelectedMuonsF_s3.size();
          muonsT_number_s3 = SelectedMuonsT_s3.size();
  
      for (int i = 0; i < muonsL_number_s3; i++) {
  
        muonL_pt_s3.push_back(SelectedMuonsL_s3.at(i).Pt());
        muonL_eta_s3.push_back(SelectedMuonsL_s3.at(i).Eta());
        muonL_phi_s3.push_back(SelectedMuonsL_s3.at(i).Phi());
        muonL_E_s3.push_back(SelectedMuonsL_s3.at(i).E());
  
      }
  
          for (int i = 0; i < muonsF_number_s3; i++) {
  
        muonF_pt_s3.push_back(SelectedMuonsF_s3.at(i).Pt());
        muonF_eta_s3.push_back(SelectedMuonsF_s3.at(i).Eta());
        muonF_phi_s3.push_back(SelectedMuonsF_s3.at(i).Phi());
        muonF_E_s3.push_back(SelectedMuonsF_s3.at(i).E());
  
      }
  
          for (int i = 0; i < muonsT_number_s3; i++) {
  
        muonT_pt_s3.push_back(SelectedMuonsT_s3.at(i).Pt());
        muonT_eta_s3.push_back(SelectedMuonsT_s3.at(i).Eta());
        muonT_phi_s3.push_back(SelectedMuonsT_s3.at(i).Phi());
        muonT_E_s3.push_back(SelectedMuonsT_s3.at(i).E());
      
          }
      
  
      vector<TLorentzVector> LeptonsT(SelectedMuonsT.begin(),
                                          SelectedMuonsT.end());
          LeptonsT.insert(LeptonsT.end(), SelectedElectronsT.begin(),
                          SelectedElectronsT.end());
          leptonsL_number = SelectedElectronsL.size() +
                            SelectedMuonsL.size(); // branch in newtree and SB
          leptonsT_number = SelectedElectronsT.size() + SelectedMuonsT.size();
          leptonsT_number_v2 = LeptonsT.size();
  
          // lepton MVA
          vector<TLorentzVector> SelectedElectronsMVAL;
          vector<int> SelectedElectronsMVALIndex;
          vector<TLorentzVector> SelectedElectronsMVAF;
          vector<int> SelectedElectronsMVAFIndex; // F for fakeble
          vector<TLorentzVector> SelectedElectronsMVAT;
          vector<int> SelectedElectronsMVATIndex;
          SelectElectronsMVA(SelectedElectronsMVAL, SelectedElectronsMVALIndex,
                             0, 4);
          SelectElectronsMVA(SelectedElectronsMVAF, SelectedElectronsMVAFIndex,
                             1, 4);
          SelectElectronsMVA(SelectedElectronsMVAT, SelectedElectronsMVATIndex,
                             2, 4);
      sort(SelectedElectronsMVAL.begin(), SelectedElectronsMVAL.end(), compEle);
      sort(SelectedElectronsMVAF.begin(), SelectedElectronsMVAF.end(), compEle);
      sort(SelectedElectronsMVAT.begin(), SelectedElectronsMVAT.end(), compEle);
          
      elesMVAL_number = SelectedElectronsMVAL.size();
          elesMVAF_number = SelectedElectronsMVAF.size();
          elesMVAT_number = SelectedElectronsMVAT.size();
  
      for (int i = 0; i < elesMVAL_number; i++) {
  
            eleMVAL_pt.push_back(SelectedElectronsMVAL.at(i).Pt());
            eleMVAL_eta.push_back(SelectedElectronsMVAL.at(i).Eta());
            eleMVAL_phi.push_back(SelectedElectronsMVAL.at(i).Phi());
            eleMVAL_E.push_back(SelectedElectronsMVAL.at(i).E());
            
          }
  
      for (int i = 0; i < elesMVAF_number; i++) {
  
            eleMVAF_pt.push_back(SelectedElectronsMVAF.at(i).Pt());
            eleMVAF_eta.push_back(SelectedElectronsMVAF.at(i).Eta());
            eleMVAF_phi.push_back(SelectedElectronsMVAF.at(i).Phi());
            eleMVAF_E.push_back(SelectedElectronsMVAF.at(i).E());
            
          }
  
      for (int i = 0; i < elesMVAT_number; i++) {
  
            eleMVAT_pt.push_back(SelectedElectronsMVAT.at(i).Pt());
            eleMVAT_eta.push_back(SelectedElectronsMVAT.at(i).Eta());
            eleMVAT_phi.push_back(SelectedElectronsMVAT.at(i).Phi());
            eleMVAT_E.push_back(SelectedElectronsMVAT.at(i).E());
            
          }
  
      // store here information for electrons at each stage
      // stage 0
      vector<TLorentzVector> SelectedElectronsMVAL_s0;
          vector<int> SelectedElectronsMVALIndex_s0;
          vector<TLorentzVector> SelectedElectronsMVAF_s0;
          vector<int> SelectedElectronsMVAFIndex_s0; // F for fakeble
          vector<TLorentzVector> SelectedElectronsMVAT_s0;
          vector<int> SelectedElectronsMVATIndex_s0;
          SelectElectronsMVA(SelectedElectronsMVAL_s0, SelectedElectronsMVALIndex_s0,
                             0, 0);
          SelectElectronsMVA(SelectedElectronsMVAF_s0, SelectedElectronsMVAFIndex_s0,
                             1, 0);
          SelectElectronsMVA(SelectedElectronsMVAT_s0, SelectedElectronsMVATIndex_s0,
                             2, 0);
  
      sort(SelectedElectronsMVAL_s0.begin(), SelectedElectronsMVAL_s0.end(), compEle);
          sort(SelectedElectronsMVAF_s0.begin(), SelectedElectronsMVAF_s0.end(), compEle);
          sort(SelectedElectronsMVAT_s0.begin(), SelectedElectronsMVAT_s0.end(), compEle);
  
      elesMVAL_number_s0 = SelectedElectronsMVAL_s0.size();
          elesMVAF_number_s0 = SelectedElectronsMVAF_s0.size();
          elesMVAT_number_s0 = SelectedElectronsMVAT_s0.size();
  
      for (int i = 0; i < elesMVAL_number_s0; i++) {
  
            eleMVAL_pt_s0.push_back(SelectedElectronsMVAL_s0.at(i).Pt());
            eleMVAL_eta_s0.push_back(SelectedElectronsMVAL_s0.at(i).Eta());
            eleMVAL_phi_s0.push_back(SelectedElectronsMVAL_s0.at(i).Phi());
            eleMVAL_E_s0.push_back(SelectedElectronsMVAL_s0.at(i).E());
            
          }
  
      for (int i = 0; i < elesMVAF_number_s0; i++) {
  
            eleMVAF_pt_s0.push_back(SelectedElectronsMVAF_s0.at(i).Pt());
            eleMVAF_eta_s0.push_back(SelectedElectronsMVAF_s0.at(i).Eta());
            eleMVAF_phi_s0.push_back(SelectedElectronsMVAF_s0.at(i).Phi());
            eleMVAF_E_s0.push_back(SelectedElectronsMVAF_s0.at(i).E());
            
          }
  
      for (int i = 0; i < elesMVAT_number_s0; i++) {
  
            eleMVAT_pt_s0.push_back(SelectedElectronsMVAT_s0.at(i).Pt());
            eleMVAT_eta_s0.push_back(SelectedElectronsMVAT_s0.at(i).Eta());
            eleMVAT_phi_s0.push_back(SelectedElectronsMVAT_s0.at(i).Phi());
            eleMVAT_E_s0.push_back(SelectedElectronsMVAT_s0.at(i).E());
            
          }
      
  
      // stage 1
      vector<TLorentzVector> SelectedElectronsMVAL_s1;
          vector<int> SelectedElectronsMVALIndex_s1;
          vector<TLorentzVector> SelectedElectronsMVAF_s1;
          vector<int> SelectedElectronsMVAFIndex_s1; // F for fakeble
          vector<TLorentzVector> SelectedElectronsMVAT_s1;
          vector<int> SelectedElectronsMVATIndex_s1;
          SelectElectronsMVA(SelectedElectronsMVAL_s1, SelectedElectronsMVALIndex_s1,
                             0, 1);
          SelectElectronsMVA(SelectedElectronsMVAF_s1, SelectedElectronsMVAFIndex_s1,
                             1, 1);
          SelectElectronsMVA(SelectedElectronsMVAT_s1, SelectedElectronsMVATIndex_s1,
                             2, 1);
  
      sort(SelectedElectronsMVAL_s1.begin(), SelectedElectronsMVAL_s1.end(), compEle);
          sort(SelectedElectronsMVAF_s1.begin(), SelectedElectronsMVAF_s1.end(), compEle);
          sort(SelectedElectronsMVAT_s1.begin(), SelectedElectronsMVAT_s1.end(), compEle);
  
      elesMVAL_number_s1 = SelectedElectronsMVAL_s1.size();
          elesMVAF_number_s1 = SelectedElectronsMVAF_s1.size();
          elesMVAT_number_s1 = SelectedElectronsMVAT_s1.size();
  
      for (int i = 0; i < elesMVAL_number_s1; i++) {
  
            eleMVAL_pt_s1.push_back(SelectedElectronsMVAL_s1.at(i).Pt());
            eleMVAL_eta_s1.push_back(SelectedElectronsMVAL_s1.at(i).Eta());
            eleMVAL_phi_s1.push_back(SelectedElectronsMVAL_s1.at(i).Phi());
            eleMVAL_E_s1.push_back(SelectedElectronsMVAL_s1.at(i).E());
            
          }
  
      for (int i = 0; i < elesMVAF_number_s1; i++) {
  
            eleMVAF_pt_s1.push_back(SelectedElectronsMVAF_s1.at(i).Pt());
            eleMVAF_eta_s1.push_back(SelectedElectronsMVAF_s1.at(i).Eta());
            eleMVAF_phi_s1.push_back(SelectedElectronsMVAF_s1.at(i).Phi());
            eleMVAF_E_s1.push_back(SelectedElectronsMVAF_s1.at(i).E());
            
          }
  
      for (int i = 0; i < elesMVAT_number_s1; i++) {
  
            eleMVAT_pt_s1.push_back(SelectedElectronsMVAT_s1.at(i).Pt());
            eleMVAT_eta_s1.push_back(SelectedElectronsMVAT_s1.at(i).Eta());
            eleMVAT_phi_s1.push_back(SelectedElectronsMVAT_s1.at(i).Phi());
            eleMVAT_E_s1.push_back(SelectedElectronsMVAT_s1.at(i).E());
            
          }
  
      // stage 2
      vector<TLorentzVector> SelectedElectronsMVAL_s2;
          vector<int> SelectedElectronsMVALIndex_s2;
          vector<TLorentzVector> SelectedElectronsMVAF_s2;
          vector<int> SelectedElectronsMVAFIndex_s2; // F for fakeble
          vector<TLorentzVector> SelectedElectronsMVAT_s2;
          vector<int> SelectedElectronsMVATIndex_s2;
          SelectElectronsMVA(SelectedElectronsMVAL_s2, SelectedElectronsMVALIndex_s2,
                             0, 2);
          SelectElectronsMVA(SelectedElectronsMVAF_s2, SelectedElectronsMVAFIndex_s2,
                             1, 2);
          SelectElectronsMVA(SelectedElectronsMVAT_s2, SelectedElectronsMVATIndex_s2,
                             2, 2);
  
      sort(SelectedElectronsMVAL_s2.begin(), SelectedElectronsMVAL_s2.end(), compEle);
          sort(SelectedElectronsMVAF_s2.begin(), SelectedElectronsMVAF_s2.end(), compEle);
          sort(SelectedElectronsMVAT_s2.begin(), SelectedElectronsMVAT_s2.end(), compEle);
  
      elesMVAL_number_s2 = SelectedElectronsMVAL_s2.size();
          elesMVAF_number_s2 = SelectedElectronsMVAF_s2.size();
          elesMVAT_number_s2 = SelectedElectronsMVAT_s2.size();
  
      for (int i = 0; i < elesMVAL_number_s2; i++) {
  
            eleMVAL_pt_s2.push_back(SelectedElectronsMVAL_s2.at(i).Pt());
            eleMVAL_eta_s2.push_back(SelectedElectronsMVAL_s2.at(i).Eta());
            eleMVAL_phi_s2.push_back(SelectedElectronsMVAL_s2.at(i).Phi());
            eleMVAL_E_s2.push_back(SelectedElectronsMVAL_s2.at(i).E());
            
          }
  
      for (int i = 0; i < elesMVAF_number_s2; i++) {
  
            eleMVAF_pt_s2.push_back(SelectedElectronsMVAF_s2.at(i).Pt());
            eleMVAF_eta_s2.push_back(SelectedElectronsMVAF_s2.at(i).Eta());
            eleMVAF_phi_s2.push_back(SelectedElectronsMVAF_s2.at(i).Phi());
            eleMVAF_E_s2.push_back(SelectedElectronsMVAF_s2.at(i).E());
            
          }
  
      for (int i = 0; i < elesMVAT_number_s2; i++) {
  
            eleMVAT_pt_s2.push_back(SelectedElectronsMVAT_s2.at(i).Pt());
            eleMVAT_eta_s2.push_back(SelectedElectronsMVAT_s2.at(i).Eta());
            eleMVAT_phi_s2.push_back(SelectedElectronsMVAT_s2.at(i).Phi());
            eleMVAT_E_s2.push_back(SelectedElectronsMVAT_s2.at(i).E());
            
          }
  
      // stage 3
      vector<TLorentzVector> SelectedElectronsMVAL_s3;
          vector<int> SelectedElectronsMVALIndex_s3;
          vector<TLorentzVector> SelectedElectronsMVAF_s3;
          vector<int> SelectedElectronsMVAFIndex_s3; // F for fakeble
          vector<TLorentzVector> SelectedElectronsMVAT_s3;
          vector<int> SelectedElectronsMVATIndex_s3;
          SelectElectronsMVA(SelectedElectronsMVAL_s3, SelectedElectronsMVALIndex_s3,
                             0, 3);
          SelectElectronsMVA(SelectedElectronsMVAF_s3, SelectedElectronsMVAFIndex_s3,
                             1, 3);
          SelectElectronsMVA(SelectedElectronsMVAT_s3, SelectedElectronsMVATIndex_s3,
                             2, 3);
  
      sort(SelectedElectronsMVAL_s3.begin(), SelectedElectronsMVAL_s3.end(), compEle);
          sort(SelectedElectronsMVAF_s3.begin(), SelectedElectronsMVAF_s3.end(), compEle);
          sort(SelectedElectronsMVAT_s3.begin(), SelectedElectronsMVAT_s3.end(), compEle);
  
      elesMVAL_number_s3 = SelectedElectronsMVAL_s3.size();
          elesMVAF_number_s3 = SelectedElectronsMVAF_s3.size();
          elesMVAT_number_s3 = SelectedElectronsMVAT_s3.size();
  
      for (int i = 0; i < elesMVAL_number_s3; i++) {
  
            eleMVAL_pt_s3.push_back(SelectedElectronsMVAL_s3.at(i).Pt());
            eleMVAL_eta_s3.push_back(SelectedElectronsMVAL_s3.at(i).Eta());
            eleMVAL_phi_s3.push_back(SelectedElectronsMVAL_s3.at(i).Phi());
            eleMVAL_E_s3.push_back(SelectedElectronsMVAL_s3.at(i).E());
            
          }
  
      for (int i = 0; i < elesMVAF_number_s3; i++) {
  
            eleMVAF_pt_s3.push_back(SelectedElectronsMVAF_s3.at(i).Pt());
            eleMVAF_eta_s3.push_back(SelectedElectronsMVAF_s3.at(i).Eta());
            eleMVAF_phi_s3.push_back(SelectedElectronsMVAF_s3.at(i).Phi());
            eleMVAF_E_s3.push_back(SelectedElectronsMVAF_s3.at(i).E());
            
          }
  
      for (int i = 0; i < elesMVAT_number_s3; i++) {
  
            eleMVAT_pt_s3.push_back(SelectedElectronsMVAT_s3.at(i).Pt());
            eleMVAT_eta_s3.push_back(SelectedElectronsMVAT_s3.at(i).Eta());
            eleMVAT_phi_s3.push_back(SelectedElectronsMVAT_s3.at(i).Phi());
            eleMVAT_E_s3.push_back(SelectedElectronsMVAT_s3.at(i).E());
            
          }
  
          vector<TLorentzVector> LeptonsMVAF(SelectedMuonsF.begin(), SelectedMuonsF.end());
          LeptonsMVAF.insert(LeptonsMVAF.end(), SelectedElectronsMVAF.begin(), SelectedElectronsMVAF.end());
          vector<TLorentzVector> LeptonsMVAT(SelectedMuonsT.begin(),  SelectedMuonsT.end());
          LeptonsMVAT.insert(LeptonsMVAT.end(), SelectedElectronsMVAT.begin(), SelectedElectronsMVAT.end());
          vector<TLorentzVector> LeptonsMVAL(SelectedMuonsL.begin(),  SelectedMuonsL.end());
          LeptonsMVAL.insert(LeptonsMVAL.end(), SelectedElectronsMVAL.begin(), SelectedElectronsMVAL.end());
  
          vector<int> LeptonsMVATIndex(SelectedMuonsTIndex.begin(),  SelectedMuonsTIndex.end());
          LeptonsMVATIndex.insert(LeptonsMVATIndex.end(), SelectedElectronsMVATIndex.begin(), SelectedElectronsMVATIndex.end());
  
          leptonsMVAT_number = LeptonsMVAT.size();
          leptonsMVAF_number = LeptonsMVAF.size();
          leptonsMVAL_number = LeptonsMVAL.size();
          leptonsMVAT_transMass = TransMassCal(LeptonsMVAT);
          leptonsMVAF_transMass = TransMassCal(LeptonsMVAF);
          leptonsMVAL_transMass = TransMassCal(LeptonsMVAL);
          // leptonsMVAT_chargeSum = ChargeSum()
          if ( leptonsMVAT_number==2 ) {
              if ( elesMVAT_number==2 ){
                  if (patElectron_charge_->at(SelectedElectronsMVATIndex[0])*patElectron_charge_->at(SelectedElectronsMVATIndex[1])==1) leptonsMVAT_2SS = 1;
                  else leptonsMVAT_2OS = 1 ;
              }
              if ( elesMVAT_number==1 ){
                  if (patElectron_charge_->at(SelectedElectronsMVATIndex[0])*Muon_charge_->at(SelectedMuonsTIndex[0])==1) leptonsMVAT_2SS = 1;
                  else leptonsMVAT_2OS = 1 ;
              }
              if ( elesMVAT_number==0){
                  if ( Muon_charge_->at(SelectedMuonsTIndex[0])*Muon_charge_->at(SelectedMuonsTIndex[1])==1)  leptonsMVAT_2SS = 1;
                  else leptonsMVAT_2OS = 1 ;
              }
          }
          //            leptonsTMVA_maxDeltaEta =
  
          sort(SelectedElectronsMVAF.begin(), SelectedElectronsMVAF.end(),
               compEle);
          if (elesMVAF_number > 0) {
            elesMVAF_1pt = SelectedElectronsMVAF[0].Pt();
          }
  
          sort(LeptonsMVAT.begin(), LeptonsMVAT.end(), compEle);
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
  
          sort(SelectedMuonsT.begin(), SelectedMuonsT.end(), compEle);
          if (muonsT_number > 0) {
            muonsT_1pt = SelectedMuonsT[0].Pt();
            muonsT_1eta = SelectedMuonsT[0].Eta();
            muonsT_1phi = SelectedMuonsT[0].Phi();
          }
          if (muonsT_number > 1) {
            muonsT_2pt = SelectedMuonsT[1].Pt();
            muonsT_2eta = SelectedMuonsT[1].Eta();
            muonsT_2phi = SelectedMuonsT[1].Phi();
          }
          if (muonsT_number > 2) {
            muonsT_3pt = SelectedMuonsT[2].Pt();
            muonsT_3eta = SelectedMuonsT[2].Eta();
            muonsT_3phi = SelectedMuonsT[2].Phi();
          }
  
          // Cone-pT of selected leptons
  
          // hadronic tau selection
          vector<TLorentzVector> SelectedTausL;
          vector<int> SelectedTausLIndex;
          vector<TLorentzVector> SelectedTausF;
          vector<int> SelectedTausFIndex;
          vector<TLorentzVector> SelectedTausT;
          vector<int> SelectedTausTIndex;
          SelectTaus(SelectedTausL, SelectedTausLIndex, 1, LeptonsMVAL);
          SelectTaus(SelectedTausF, SelectedTausFIndex, 2, LeptonsMVAL);
          SelectTaus(SelectedTausT, SelectedTausTIndex, 3, LeptonsMVAL); // tight
          tausL_number = SelectedTausL.size();
          tausF_number = SelectedTausF.size();
          tausT_number = SelectedTausT.size();
          tausL_MHT = MHTcalculator(SelectedTausL);
          tausF_MHT = MHTcalculator(
              SelectedTausF); // 900;return the pt sum of,vetctor sum
          tausT_MHT = MHTcalculator(
              SelectedTausT); // 900;return the pt sum of,vetctor sum
          tausL_HT = HTcalculator(SelectedTausL);
          tausF_HT = HTcalculator(SelectedTausF);
          tausT_HT = HTcalculator(SelectedTausT);
          tausL_invariantMass = InvariantMassCalculator(SelectedTausL);
          tausF_invariantMass = InvariantMassCalculator(SelectedTausF);
          tausT_invariantMass = InvariantMassCalculator(SelectedTausT);
          tausL_minDeltaR = MinDeltaRSingleCal(SelectedTausL);
          tausF_minDeltaR = MinDeltaRSingleCal(SelectedTausF);
          tausT_minDeltaR = MinDeltaRSingleCal(SelectedTausT);
  
          tausF_leptonsT_transMass = TransMassSysCal(SelectedTausF, LeptonsMVAT);
          tausL_leptonsT_transMass = TransMassSysCal(SelectedTausL, LeptonsMVAT);
          tausT_leptonsT_transMass = TransMassSysCal(SelectedTausT, LeptonsMVAT);
          tausF_leptonsT_invariantMass = InvariantMass2SysCal(SelectedTausF, LeptonsMVAT);
          tausL_leptonsT_invariantMass = InvariantMass2SysCal(SelectedTausL, LeptonsMVAT);
          tausT_leptonsT_invariantMass = InvariantMass2SysCal(SelectedTausT, LeptonsMVAT);
          tausF_leptonsT_chargeSum = ChargeSum(SelectedTausFIndex, 1) +
                                     ChargeSum(SelectedElectronsMVATIndex, 0) +
                                     ChargeSum(SelectedMuonsTIndex, 2);
          tausF_leptonsTMVA_minDeltaR = MinDeltaRCal(LeptonsMVAT, SelectedTausF);
          tausL_leptonsTMVA_minDeltaR = MinDeltaRCal(LeptonsMVAT, SelectedTausL);
          tausT_leptonsTMVA_minDeltaR = MinDeltaRCal(LeptonsMVAT, SelectedTausT);
  
          sort(SelectedTausL.begin(), SelectedTausL.end(), compEle);
          if (tausL_number > 0) {
            tauL_1pt = SelectedTausL[0].Pt();
            tauL_1eta = SelectedTausL[0].Eta();
            tauL_1phi = SelectedTausL[0].Phi();
          }
          if (tausL_number > 1) {
            tauL_2pt = SelectedTausL[1].Pt();
            tauL_2eta = SelectedTausL[1].Eta();
            tauL_2phi = SelectedTausL[1].Phi();
          }
          if (tausL_number > 0) {
            tauL_3pt = SelectedTausL[0].Pt();
            tauL_3eta = SelectedTausL[0].Eta();
            tauL_3phi = SelectedTausL[0].Phi();
          }
  
  
  
  
          // jet and B jet selection
          vector<double> SelectedJetsBTags;
          vector<double> SelectedBJetsMBTtags, SelectedBJetsLBTags,
              SelectedBJetsTBTags, SelectedForwardJetsBTags; 
          int CA8Index = -1;
          //?what does CA8Index do?
          //?not used in the macro
          // bool deltaPhiJetMet = true; // used in SelectedJets
          // vector<TLorentzVector> SelectedWJets;
          // SelectCA8Jets(0,SelectedWJets,
          // SelectedElectrons,SelectedMuons,CA8Indices, SysJes, SysJer, data,
          // deltaPhiJetMet);   //if(!deltaPhiJetMet)  continue;
          // vector<TLorentzVector> SelectedTopJets;
          // SelectCA8Jets(1,SelectedTopJets,SelectedElectrons,SelectedMuons,CA8Indices,
          // SysJes, SysJer, data, deltaPhiJetMet);   //if(!deltaPhiJetMet)
          bool deepJet = true;
          vector<TLorentzVector> SelectedJets; vector<int> SelectedJetsIndex;
          SelectJets(0, deepJet, SelectedJets, SelectedJetsBTags,SelectedJetsIndex, SysJes, SysJer,  LeptonsMVAF, SelectedTausL); 
          vector<TLorentzVector> SelectedBJetsL; vector<int> SelectedBJetsLIndex;
          SelectJets(11, deepJet, SelectedBJetsL, SelectedBJetsLBTags, SelectedBJetsLIndex, SysJes,  SysJer, LeptonsMVAF, SelectedTausL ); 
          vector<TLorentzVector> SelectedBJetsM; vector<int> SelectedBJetsMIndex;
          SelectJets(12, deepJet, SelectedBJetsM, SelectedBJetsMBTtags, SelectedBJetsMIndex, SysJes, SysJer, LeptonsMVAF, SelectedTausL ); 
          vector<TLorentzVector> SelectedBJetsT; vector<int> SelectedBJetsTIndex;
          SelectJets(13, deepJet, SelectedBJetsT, SelectedBJetsTBTags, SelectedBJetsTIndex, SysJes, SysJer, LeptonsMVAF, SelectedTausL ); 
          vector<TLorentzVector> SelectedForwardJets; vector<int> SelectedForwardJetsIndex;
          SelectJets(2, deepJet, SelectedForwardJets, SelectedForwardJetsBTags, SelectedForwardJetsIndex, SysJes, SysJer, LeptonsMVAF, SelectedTausL);
  
          jetsL_number = SelectedJets.size();
          jetsL_MHT =  MHTcalculator(SelectedJets); // 900;return the pt sum of,vetctor sum
          jetsL_HT = HTcalculator(SelectedJets);
          jetsL_invariantMass = InvariantMassCalculator(SelectedJets);
          jetsL_transMass = TransMassCal(SelectedJets);
          jetL_minDeltaR = MinDeltaRSingleCal(SelectedJets);
          jetsL_centrality = jetsL_HT / jetsL_invariantMass;
          jetsL_bScore = BScoreAllJetsCal(SelectedJetsBTags);
          jetsL_average_deltaR = AverageDeltaRCal(SelectedJets);
          jetsL_4largestBscoreSum = bscoreSumOf4largestCal(SelectedJetsBTags);
          if (Met_pt == 0) {
            jetsL_HTDividedByMet = 0;
          } else {
            jetsL_HTDividedByMet = jetsL_HT / Met_pt;
          }
          MetDividedByHT = Met_pt / jetsL_HT;
          jetsL_MHTDividedByMet = jetsL_MHT / Met_pt;
          jetsL_leptonsMVAT_minDeltaR = MinDeltaRCal(SelectedJets, LeptonsMVAT);
          jetsL_tausF_minDeltaR = MinDeltaRCal(SelectedJets, SelectedTausF);
  
          bjetsL_num = SelectedBJetsL.size();
          bjetsM_num = SelectedBJetsM.size(); //
          bjetsT_num = SelectedBJetsT.size();
          bjetsL_HT = HTcalculator(SelectedBJetsL);
          bjetsM_HT = HTcalculator(SelectedBJetsM);
          bjetsT_HT = HTcalculator(SelectedBJetsT);
          bjetsL_MHT =  MHTcalculator(SelectedBJetsL); // 900;return the pt sum of,vetctor sum
          bjetsM_MHT =  MHTcalculator(SelectedBJetsM); // 900;return the pt sum of,vetctor sum
          bjetsT_MHT =  MHTcalculator(SelectedBJetsT); // 900;return the pt sum of,vetctor sum
          bjetsL_invariantMass = InvariantMassCalculator(SelectedBJetsL);
          bjetsM_invariantMass = InvariantMassCalculator(SelectedBJetsM);
          bjetsT_invariantMass = InvariantMassCalculator(SelectedBJetsT);
          bjetsL_transMass = TransMassCal(SelectedBJetsL);
          bjetsM_transMass = TransMassCal(SelectedBJetsM);
          bjetsT_transMass = TransMassCal(SelectedBJetsT);
          bjetsL_minDeltaR = MinDeltaRSingleCal(SelectedBJetsL);
          bjetsM_minDeltaR = MinDeltaRSingleCal(SelectedBJetsM);
          bjetsT_minDeltaR = MinDeltaRSingleCal(SelectedBJetsT);
          bjetsL_leptonsMVAT_minDeltaR = MinDeltaRCal(SelectedBJetsL, LeptonsMVAT);
          bjetsM_leptonsMVAT_minDeltaR = MinDeltaRCal(SelectedBJetsM, LeptonsMVAT);
          bjetsT_leptonsMVAT_minDeltaR = MinDeltaRCal(SelectedBJetsT, LeptonsMVAT);
          bjetsL_tausF_minDeltaR = MinDeltaRCal(SelectedBJetsL, SelectedTausF);
  
  
          forwardJets_num = SelectedForwardJets.size(); // 185
  
          vector<double> MinMaxDeltaPhiJets;
          MinMaxDeltaPhiCal(SelectedJets, MinMaxDeltaPhiJets);
          MinDeltaPhiJets = MinMaxDeltaPhiJets[0];
  
          sort(SelectedBJetsL.begin(), SelectedBJetsL.end(), compEle);
          if (bjetsL_num > 0) {/*{{{*/
            bjetsL_1pt = SelectedBJetsL[0].Pt();
            bjetsL_1eta = SelectedBJetsL[0].Eta();
            bjetsL_1phi = SelectedBJetsL[0].Phi();
          }
          if (bjetsL_num > 1) {
            bjetsL_2pt = SelectedBJetsL[1].Pt();
            bjetsL_2eta = SelectedBJetsL[1].Eta();
            bjetsL_2phi = SelectedBJetsL[1].Phi();
          }
          if (bjetsL_num > 2) {
            bjetsL_3pt = SelectedBJetsL[2].Pt();
            bjetsL_3eta = SelectedBJetsL[2].Eta();
            bjetsL_3phi = SelectedBJetsL[2].Phi();
          }
          if (bjetsL_num > 3) {
            bjetsL_4pt = SelectedBJetsL[3].Pt();
            bjetsL_4eta = SelectedBJetsL[3].Eta();
            bjetsL_4phi = SelectedBJetsL[3].Phi();
          }
  
          sort(SelectedBJetsM.begin(), SelectedBJetsM.end(), compEle);
          if (bjetsM_num > 0) {
            bjetsM_1pt = SelectedBJetsM[0].Pt();
            bjetsM_1eta = SelectedBJetsM[0].Eta();
            bjetsM_1phi = SelectedBJetsM[0].Phi();
          }
          if (bjetsM_num > 1) {
            bjetsM_2pt = SelectedBJetsM[1].Pt();
            bjetsM_2eta = SelectedBJetsM[1].Eta();
            bjetsM_2phi = SelectedBJetsM[1].Phi();
          }
          if (bjetsM_num > 2) {
            bjetsM_3pt = SelectedBJetsM[2].Pt();
            bjetsM_3eta = SelectedBJetsM[2].Eta();
            bjetsM_3phi = SelectedBJetsM[2].Phi();
          }
          if (bjetsM_num > 3) {
            bjetsM_4pt = SelectedBJetsM[3].Pt();
            bjetsM_4eta = SelectedBJetsM[3].Eta();
            bjetsM_4phi = SelectedBJetsM[3].Phi();
          }
  
          sort(SelectedBJetsT.begin(), SelectedBJetsT.end(), compEle);
          if (bjetsT_num > 0) {
            bjetsT_1pt = SelectedBJetsT[0].Pt();
            bjetsT_1eta = SelectedBJetsT[0].Eta();
            bjetsT_1phi = SelectedBJetsT[0].Phi();
          }
          if (bjetsT_num > 1) {
            bjetsT_2pt = SelectedBJetsT[1].Pt();
            bjetsT_2eta = SelectedBJetsT[1].Eta();
            bjetsT_2phi = SelectedBJetsT[1].Phi();
          }
          if (bjetsT_num > 2) {
            bjetsT_3pt = SelectedBJetsT[2].Pt();
            bjetsT_3eta = SelectedBJetsT[2].Eta();
            bjetsT_3phi = SelectedBJetsT[2].Phi();
          }
          if (bjetsT_num > 3) {
            bjetsT_4pt = SelectedBJetsT[3].Pt();
            bjetsT_4eta = SelectedBJetsT[3].Eta();
            bjetsT_4phi = SelectedBJetsT[3].Phi();
          }/*}}}*/
  
  
          sort(SelectedForwardJets.begin(), SelectedForwardJets.end(), compEle);
          if (forwardJets_num > 0) {
            forwardjet_1pt = SelectedForwardJets[0].Pt();
            forwardjet_1eta = fabs(SelectedForwardJets[0].Eta());
            forwardjet_1phi = SelectedForwardJets[0].Phi();
            forwardjet1_jetsL_minDeltaEta =
                MinDeltaEtaCal(SelectedForwardJets[0], SelectedJets);
          }
  
          sort(SelectedJets.begin(), SelectedJets.end(), compEle);
          if (jetsL_number > 0) {/*{{{*/
            jetsL_1pt = SelectedJets[0].Pt();
            jetsL_1eta = SelectedJets[0].Eta();
            jetsL_1phi = SelectedJets[0].Phi();
          }
          if (jetsL_number > 1) {
            jetsL_2pt = SelectedJets[1].Pt();
            jetsL_2eta = SelectedJets[1].Eta();
            jetsL_2phi = SelectedJets[1].Phi();
            jetsL_leading2invariantMass = (SelectedJets[0]+SelectedJets[1]).M();
          }
          if (jetsL_number > 2) {
            jetsL_3pt = SelectedJets[2].Pt();
            jetsL_3eta = SelectedJets[2].Eta();
            jetsL_3phi = SelectedJets[2].Phi();
          }
          if (jetsL_number > 3) {
            jetsL_4pt = SelectedJets[3].Pt();
            jetsL_4eta = SelectedJets[3].Eta();
            jetsL_4phi = SelectedJets[3].Phi();
          }
          if (jetsL_number > 4) {
            jetsL_5pt = SelectedJets[4].Pt();
            jetsL_5eta = SelectedJets[4].Eta();
            jetsL_5phi = SelectedJets[4].Phi();
            jetsL_rationHT_4toRest = rationHT_4toRestCal(SelectedJets);
          }
          if (jetsL_number > 5) {
            jetsL_6pt = SelectedJets[5].Pt();
            jetsL_6eta = SelectedJets[5].Eta();
            jetsL_6phi = SelectedJets[5].Phi();
          }
          if (jetsL_number > 6) {
            jetsL_7pt = SelectedJets[6].Pt();
            jetsL_7eta = SelectedJets[6].Eta();
            jetL_7phi = SelectedJets[6].Phi();
          }
          if (jetsL_number > 7) {
            jetsL_8pt = SelectedJets[7].Pt();
            jetsL_8eta = SelectedJets[7].Eta();
            jetsL_8phi = SelectedJets[7].Phi();
          }
          if (jetsL_number > 8) {
            jetsL_9pt = SelectedJets[8].Pt();
            jetsL_9eta = SelectedJets[8].Eta();
            jetsL_9phi = SelectedJets[8].Phi();
          }
          if (jetsL_number > 9) {
            jetsL_10pt = SelectedJets[9].Pt();
            jetsL_10eta = SelectedJets[9].Eta();
            jetsL_10phi = SelectedJets[9].Phi();
          }
          if (jetsL_number > 10) {
            jetsL_11pt = SelectedJets[10].Pt();
            jetsL_11eta = SelectedJets[10].Eta();
            jetsL_11phi = SelectedJets[10].Phi();
          }/*}}}*/
  
          //event preselection
          if ( !isHLTstudy){
              if (!(tausL_number > 0))      continue;
              if (!(jetsL_number > 3))      continue;
              if (!(bjetsL_num > 1))        continue;
          }
          //channel selection for MVA
          // if (!((channel_1Tau0L_v2 == 1) &&(tausT_number == 1)&& (jetsL_number >= 8) && (bjetsM_num >=2))) continue;//for 1Tau0L
          
          //
          //
          //
          //
          // Hadronic Top selection
          // using resuts of SUSY toptagger here
          vector<TLorentzVector> SelectedTops;
          SelectTops(SelectedTops);
          toptagger_num = SelectedTops.size();
          toptagger_MHT =  MHTcalculator(SelectedTops); // 900;return the pt sum of,vetctor sum
          toptagger_HT = HTcalculator(SelectedTops);
          toptagger_invariantMass = InvariantMassCalculator(SelectedTops);
          toptagger_transMass = TransMassCal(SelectedTops);
          toptagger_minDeltaR_v1 = MinDeltaRSingleCal(SelectedTops);
          toptagger_scoreAllTops = TopScoreAllTopsCal(SelectedTops);
          toptagger_leptonsMVAT_minDeltaR = MinDeltaRCal(SelectedTops, LeptonsMVAT);
          sort(SelectedTops.begin(), SelectedTops.end(), compEle);
          if (toptagger_num > 0) {
            toptagger_1pt = SelectedTops[0].Pt();
            toptagger_1eta = SelectedTops[0].Eta();
            toptagger_1phi = SelectedTops[0].Phi();
          }
          if (toptagger_num > 1) {
            toptagger_2pt = SelectedTops[1].Pt();
            toptagger_2eta = SelectedTops[1].Eta();
            toptagger_2phi = SelectedTops[1].Phi();
            vector<double> MinMaxDeltaRTops;
            MinMaxdeltaRJetsCal(SelectedTops, MinMaxDeltaRTops);
            toptagger_minDeltaR = MinMaxDeltaRTops[0];
            toptagger_maxDeltaR = MinMaxDeltaRTops[1];
          }
          if (toptagger_num > 2) {
            toptagger_3pt = SelectedTops[2].Pt();
            toptagger_3eta = SelectedTops[2].Eta();
            toptagger_3phi = SelectedTops[2].Phi();
          }
  
          // only top that decay into 3 jets
          /*			TLorentzVector Jet1Resolved;
          Jet1Resolved.SetPtEtaPhiE(0, 0, 0, 0);
                                  TLorentzVector Jet2Resolved;
          Jet2Resolved.SetPtEtaPhiE(0, 0, 0, 0);
                                  TLorentzVector Jet3Resolved;
          Jet3Resolved.SetPtEtaPhiE(0, 0, 0, 0);
                                  TLorentzVector HadronicTopQuark;
          HadronicTopQuark.SetPtEtaPhiE(0, 0, 0, 0);
                                  TLorentzVector HadronicTopQuarkResolved;
          HadronicTopQuarkResolved.SetPtEtaPhiE(0, 0, 0, 0);
                                  bool ResolvedEvent   = false;//parameter in
          function FillBranch
                                          //466; give Jet1,2,3,Toppt etc
          //last 2 parameter are TopMassCut and btag
                          //ResolvedRegionSelection need modification because it
          only have 1 top
          //			if(selection==0)
          ResolvedRegionSelection(ResolvedEvent, SelectedJets, SelectedJetsBTags,
          HadronicTopQuarkResolved, Jet1Resolved, Jet2Resolved, Jet3Resolved,
          false, false);
                                  if(selection==0)
          ResolvedRegionSelection(ResolvedEvent, SelectedJets, SelectedJetsBTags,
          HadronicTopQuarkResolved, Jet1Resolved, Jet2Resolved, Jet3Resolved,
          true, true);
                                  if(selection==1)
          ResolvedRegionSelection(ResolvedEvent, SelectedJets, SelectedJetsBTags,
          HadronicTopQuarkResolved, Jet1Resolved, Jet2Resolved, Jet3Resolved,
          false, true );
                                  if(selection==2)
          ResolvedRegionSelection(ResolvedEvent, SelectedJets, SelectedJetsBTags,
          HadronicTopQuarkResolved, Jet1Resolved, Jet2Resolved, Jet3Resolved,
          false, false);
                                  if(ResolvedEvent)   HadronicTopQuark =
          HadronicTopQuarkResolved;//parameter in Fillbranch
                      //HadronicTopQuark and HadronicTopQuarkResolved are
          identical
          //			if(!ResolvedEvent) continue;
          //			//?use funtion to give value, wouldn't it be
          useless?
                              WriteTopRelatedBranches(ResolvedEvent,HadronicTopQuark,SelectedMet,HadronicTopQuarkResolved,Jet1Resolved,Jet2Resolved,Jet3Resolved,SelectedForwardJets,SelectedBJetsM);
          */
          NVertices = nBestVtx_;
          EVENT_run = EVENT_run_;
          EVENT_event = EVENT_event_;
          EVENT_lumiBlock = EVENT_lumiBlock_;
          EVENT_genHT = EVENT_genHT_;
          prefiringweight = EVENT_prefireWeight_;
          prefiringweightup = EVENT_prefireWeightUp_;
          prefiringweightdown = EVENT_prefireWeightDown_;
          puWeight = PUWeight_ ;
          EVENT_genWeight = genWeight_;
  
  
          // WEIGHT
          //if(!data){
          //		get_weight_btag(selection,w_Btag,
          //      w_BtagUp, w_BtagDown,w_Btag1Up, w_Btag1Down,w_Btag2Up,
          //      w_Btag2Down,w_BtagLoose, w_BtagLooseUp, w_BtagLooseDown,input);//606 w_Btagall in NewTree
          //		newPUWeight(PUWeight, PUWeightUP,PUWeightDOWN);//PUWeigh is a branch in Tree and newTree,PU and UP and DOWN are in New
          //		GenWeight(input,GenZPt,GenWPt);2681
                  // HTSF(input,HT,Met_pt,w_ZToNuNu,w_ZToNuNuUp,w_ZToNuNuDown,w_WToLNu,w_WToLNuUp,w_WToLNuDown,w_ttbar,w_ttbarUp,w_ttbarDown);//778
                  // TriggerSF(Met_pt, jetsL_MHT, w_Trig, w_TrigUp, w_TrigDown );
                 // QCDWeight(0,8,w_QCDUp,w_QCDDown);//240
                  // PDFWeight(10,111,w_PDFUp,w_PDFDown);
          //			}
  
          if (selection == 0 || selection == 1)
            NewTree->Fill();
          else if (selection == 2)
            HistoFill(PUWeight, NewTreeSB);
        }
      }
  
      f.cd();
      NewTree->Write();
      h_genWeight->Write();
      f.Close();
      cout << "File " << input << " ready!" << endl;
    // }
}

void QCDWeight(int imin, int imax, double &w_QCDUp, double &w_QCDDown) { /*{{{*/
  TH1D *RMS = new TH1D("", "", 100, -0.5, 0.5);
  for (int i = imin; i < imax; i++) {
    if (i == 5)
      continue;
    if (i == 7)
      continue;
    int I = 0;
    I = i;
    double ratio = (*genWeights_)[I] / (*genWeights_)[0];
    RMS->Fill(ratio - 1);
  }
  w_QCDUp = 1 + RMS->GetRMS();
  w_QCDDown = TMath::Max(0., (1 - RMS->GetRMS()));
  delete RMS;
} /*}}}*/

void PDFWeight(int imin, int imax, double &w_PDFUp, double &w_PDFDown) { /*{{{*/
  TH1D *RMS = new TH1D("", "", 100, -0.5, 0.5);
  for (int i = imin; i < imax; i++) {
    int I = 0;
    if (i == 10)
      I = 0;
    else
      I = i;
    double ratio = (*genWeights_)[I] / (*genWeights_)[0];
    RMS->Fill(ratio - 1);
  }
  w_PDFUp = 1 + RMS->GetRMS();
  w_PDFDown = TMath::Max(0., (1 - RMS->GetRMS()));
  delete RMS;
} /*}}}*/
//?why do this?
void MetCorrection(int SysJes, int SysJer, double &MET) { /*{{{*/
  double METx =
      Met_type1PF_pt_ * TMath::Cos(Met_type1PF_phi_); // in tree branch.
  double METy = Met_type1PF_pt_ * TMath::Sin(Met_type1PF_phi_);
  for (UInt_t j = 0; j < Jet_pt_->size(); ++j) {
    if (!(Jet_Uncorr_pt_->at(j) > 15))
      continue;
    double jetpt = 0.;
    //?the difference of Jet_pt and Jet_Uncorr_pt?
    if (SysJes == 0 && SysJer == 0) {
      jetpt = Jet_Uncorr_pt_->at(j) * Jet_JesSF_->at(j) * Jet_JerSF_->at(j);
    }
    if (SysJes == 1 && SysJer == 0) {
      jetpt = Jet_Uncorr_pt_->at(j) * Jet_JesSFup_->at(j) * Jet_JerSF_->at(j);
    }
    if (SysJes == 2 && SysJer == 0) {
      jetpt = Jet_Uncorr_pt_->at(j) * Jet_JesSFdown_->at(j) * Jet_JerSF_->at(j);
    }
    if (SysJes == 0 && SysJer == 1) {
      jetpt = Jet_Uncorr_pt_->at(j) * Jet_JesSF_->at(j) * Jet_JerSFup_->at(j);
    }
    if (SysJes == 0 && SysJer == 2) {
      jetpt = Jet_Uncorr_pt_->at(j) * Jet_JesSF_->at(j) * Jet_JerSFdown_->at(j);
    }
    METx = METx + Jet_Uncorr_pt_->at(j) * Jet_JesSF_->at(j) *
                      TMath::Cos(Jet_phi_->at(j)) -
           jetpt * TMath::Cos(Jet_phi_->at(j));
    METy = METy + Jet_Uncorr_pt_->at(j) * Jet_JesSF_->at(j) *
                      TMath::Sin(Jet_phi_->at(j)) -
           jetpt * TMath::Sin(Jet_phi_->at(j));
    //??
  }
  MET = sqrt(METx * METx + METy * METy);
} /*}}}*/

void selectGenTaus( vector<TLorentzVector> &genTaus ){
    for (UInt_t j = 0; j < Gen_pt_->size(); ++j) {
        if(!(abs(Gen_motherpdg_id_->at(j))==24 && abs(Gen_pdg_id_->at(j))==15)) continue;//tau:15; top:6;W:
        TLorentzVector gentau;
        gentau.SetPtEtaPhiE(Gen_pt_->at(j), Gen_eta_->at(j), Gen_phi_->at(j), Gen_energy_->at(j));
        genTaus.push_back(gentau);
    }
}
void selectGenEles( vector<TLorentzVector> &genEles ){
    for (UInt_t j = 0; j < Gen_pt_->size(); ++j) {
        if(!(abs(Gen_motherpdg_id_->at(j))==24 && abs(Gen_pdg_id_->at(j))==11)) continue;//tau:15; ele:11;
        TLorentzVector genele;
        genele.SetPtEtaPhiE(Gen_pt_->at(j), Gen_eta_->at(j), Gen_phi_->at(j), Gen_energy_->at(j));
        genEles.push_back(genele);
    }
}
void selectGenMuons( vector<TLorentzVector> &genMuons ){
    for (UInt_t j = 0; j < Gen_pt_->size(); ++j) {
        if(!(abs(Gen_motherpdg_id_->at(j))==24  && abs(Gen_pdg_id_->at(j))==13)) continue;//tau:15; top:6;W:;muon:13
        TLorentzVector genmuon;
        genmuon.SetPtEtaPhiE(Gen_pt_->at(j), Gen_eta_->at(j), Gen_phi_->at(j), Gen_energy_->at(j));
        genMuons.push_back(genmuon);
    }
}

void SelectElectrons(vector<TLorentzVector> &SelectedElectrons,
                     vector<int> &SelectedElectronsIndex, int type) { /*{{{*/
  //?data does not occur.
  // 0; loose
  // 1;medium
  // 2;tight
  // 3;veto
  for (UInt_t j = 0; j < patElectron_pt_->size(); ++j) { // banch in tree
                                                         // line945
    // what is patElectron_pt?
    if (!(patElectron_pt_->at(j) > 20))
      continue; // A continue skips the rest of the body of an
                // iteration-statement.
    if (!(fabs(patElectron_eta_->at(j)) < 2.4))
      continue; // std::string::at can be used to extract characters by
                // characters from a given string.
    //    if(!(fabs(patElectron_SCeta_->at(j))<2.5))	     continue;
    // SCeta?//super cluster
    //    if(!(patElectron_inCrack_->at(j)==0))	         continue;
    //?//1.4442<fabs(EleSCeta) && fabs(EleSCeta)<1.5660
    //    if(!(patElectron_isPassLoose_->at(j)==1))	     continue;
    //    if(!(patElectron_passConversionVeto_->at(j)==1)) continue;//no need to
    // do it because already implemented in VID
    if (type == 0) {
      if (!(patElectron_cutBasedElectronID_Fall17_94X_V2_loose_->at(j) == 1))
        continue;
    }
    if (type == 1) {
      if (!(patElectron_cutBasedElectronID_Fall17_94X_V2_medium_->at(j) == 1))
        continue;
    }
    if (type == 2) {
      if (!(patElectron_cutBasedElectronID_Fall17_94X_V2_tight_->at(j) == 1))
        continue;
    }
    if (type == 3) {
      if (!(patElectron_cutBasedElectronID_Fall17_94X_V2_veto_->at(j) == 1))
        continue;
    }
    // TLorentzVector electron;
    // electron.SetPtEtaPhiE(patElectron_pt_->at(j),patElectron_eta_->at(j),patElectron_phi_->at(j),patElectron_energy_->at(j)*patElectron_energyCorr_->at(j));
    TLorentzVector electron;
    electron.SetPtEtaPhiE(patElectron_pt_->at(j), patElectron_eta_->at(j),
                          patElectron_phi_->at(j), patElectron_energy_->at(j));
    SelectedElectrons.push_back(electron);
    SelectedElectronsIndex.push_back(j);
  }
} /*}}}*/

void SelectElectronsMVA(vector<TLorentzVector> &SelectedElectrons,
                        vector<int> &SelectedElectronsIndex, int type, int stage) {
  // 0 for VLoose; 1 for VLooseFO(fakeble object); 2 for tight
  // 2016 - MVANoIso94XV2, from SUSY
  for (UInt_t j = 0; j < patElectron_pt_->size(); ++j) { // banch in tree
                                                         // line945
    if (stage == 1 || stage == 2 || stage == 3 || stage == 4) {

      double pt = patElectron_pt_->at(j);
      double eta = patElectron_eta_->at(j);
      double MVA_value = patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Values_->at(j);
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
    if (!((patElectron_miniIsoRel_->at(j) < I1) && ((patElectron_jetptratio_->at(j) > I2) ||   (patElectron_ptrel_->at(j) > I3))))      continue;
    //?if we apply this for tight , the number would be very low.

    if (stage == 4) {

      
    // emulation selection

    // IP
    //?
    // patElectron_IP3Dsig;patElectron_IP3D_sig;patElectron_sIP3D_sig;patElectron_d0;patElectron_gsfTrack_dz_pv;
    if (!(patElectron_d0_->at(j) < 0.05))
      continue;
    if (!(patElectron_gsfTrack_dz_pv_->at(j) < 0.1))
      continue;
    if (type == 1 or type == 2) {
      if (!(patElectron_IP3D_sig_->at(j) < 4))
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
    electron.SetPtEtaPhiE(patElectron_pt_->at(j), patElectron_eta_->at(j),
                          patElectron_phi_->at(j), patElectron_energy_->at(j));
    SelectedElectrons.push_back(electron);
    SelectedElectronsIndex.push_back(j);
  }
}

void SelectMuons(vector<TLorentzVector> &SelectedMuons,
                 vector<int> &SelectedMuonsIndex, int type, int stage) { /*{{{*/
  // changed ISO to ss of TTTT
  // 0 for Loose; 2 for medium 
  for (UInt_t j = 0; j < Muon_pt_->size(); ++j) {

    if (stage == 1 || stage == 2 || stage == 3 || stage == 4) {

      //    if(!(Muon_pt_->at(j)>20))                     continue;
    if (!(fabs(Muon_eta_->at(j)) < 2.4))
      continue;
    
    if (stage == 2 || stage == 3 || stage == 4) {
      double pt = Muon_pt_->at(j);
      if (type == 0) {
      if (!(Muon_loose_->at(j) == 1))
        continue;
    }
    if (type == 1 or type == 2) {
      if(!(pt > 10)) continue;
      if (!(Muon_medium_->at(j) == 1))
        continue;
    }
    
    if (stage == 3 || stage == 4) {

      //    if(type==2){ if(!(Muon_tight_->at(j)==1))     continue; }
    //    if(!(Muon_relIsoDeltaBetaR04_->at(j)<0.15))   continue;  //loose
    // iso->change to 0.15(tight) from 0.25
    // Muon_relIsoDeltaBetaR04?_
    double I1 = 0.4, I2 = 0, I3 = 0; // looseWP from ss of TTTT
    if(type == 2){
        I1 = 0.16; I2 = 0.76, I3 = 7.2;
    }
    //    if(!((Muon_miniIsoRel_->at(j)<I1)|((Muon_jetptratio_->at(j)>I2)&&(Muon_ptrel_->at(j)>I3))))
    // continue;
    if (!((Muon_miniIsoRel_->at(j) < I1) && ((Muon_jetptratio_->at(j) > I2) || (Muon_ptrel_->at(j) > I3))))      continue;

    if (stage == 4) {
      
      
    // IP
    // Muon_IP3Dsig_it;Muon_dz_pv;Muon_dz_bt;Muon_IP3D_sig;Muon_dxy_pv;
    if(!(Muon_dz_bt_->at(j)<0.1)) continue;

    //?throwing an instance of 'std::out_of_range'
    if(!(Muon_dxy_bt_->at(j)<0.05)) continue;
    if(type == 1 or type == 2) {
      if(!(Muon_IP3D_sig_->at(j)<4)) continue;
    }

    //charge

    }// end stage 4


    }// end stage 3
      
    }// end stage 2 

      
    }// end stage 1
    
    //?Muon_jetptratioV2?
    TLorentzVector muon;
    muon.SetPtEtaPhiE(Muon_pt_->at(j), Muon_eta_->at(j), Muon_phi_->at(j),
                      Muon_energy_->at(j));
    SelectedMuons.push_back(muon);
    SelectedMuonsIndex.push_back(j);}
  
} /*}}}*/


void SelectTaus(vector<TLorentzVector> &SelectedTaus,  vector<int> &SelectedTausIndex,const Int_t TauWP, const vector<TLorentzVector> LeptonsMVAL) {
  // this is tau ID in ttH
  // 1:loose;2:fakeble;3:tight
  for (UInt_t j = 0; j < Tau_pt_->size(); ++j) {/*{{{*/
    if (!(Tau_pt_->at(j) > 20))
      continue;
    if (!(Tau_eta_->at(j) < 2.3 && Tau_eta_->at(j) > -2.3))
      continue;
    //       if(!(Tau_leadChargedCandDz_pv_->at(j)<0.2)) continue;
    if (!(Tau_packedLeadTauCand_dz_->at(j) < 0.2))
      continue; // missing dz
    //?use which dz still need more thinking
    if (!(Tau_decayModeFindingNewDMs_->at(j) == 1))
      continue;
    //???not sure why all taus is 1? if so no point in this requirement. //?not
    // sure, is seem all are 1;
    if (TauWP == 2 || TauWP == 3) {
       if( Tau_decayMode_->at(j) == 5 || Tau_decayMode_->at(j) == 6)      continue;} // for decay mode
    if (TauWP == 1) {
      if (!(Tau_byVVLooseDeepTau2017v2p1VSjet_->at(j) > 0.5))
        continue;
    }
    if (TauWP == 2) {
      if (!(Tau_byVVLooseDeepTau2017v2p1VSjet_->at(j) > 0.5 &&
            Tau_byVLooseDeepTau2017v2p1VSmu_->at(j) > 0.5 &&
            Tau_byVVVLooseDeepTau2017v2p1VSe_->at(j) > 0.5))
        continue;
    }
    if (TauWP == 3) { // channel specific in ttH. use the tight from 1t 1l
      if (!(Tau_byVLooseDeepTau2017v2p1VSmu_->at(j) > 0.5 &&
            Tau_byVVVLooseDeepTau2017v2p1VSe_->at(j) > 0.5 &&
            Tau_byMediumDeepTau2017v2p1VSjet_->at(j) > 0.5))
        continue;
    }
    //overlap removal
    double minDeltaR_lep;
    minDeltaR_lep = deltRmin(Tau_eta_->at(j), Tau_phi_->at(j), LeptonsMVAL);
    if( !(minDeltaR_lep >= 0.3 )) continue;

    //?need err handling
    TLorentzVector tau;
    tau.SetPtEtaPhiE(Tau_pt_->at(j), Tau_eta_->at(j), Tau_phi_->at(j),
                     Tau_energy_->at(j));
    SelectedTaus.push_back(tau);
    SelectedTausIndex.push_back(j);
  }
}/*}}}*/

void SelectJets(const int jetType,const  bool deepJet, vector<TLorentzVector> &SelectedJets,
                vector<double> &SelectedJetsBTags, vector<int> &SelectedJetsIndex , const int SysJes, const int SysJer, const vector<TLorentzVector> LeptonsMVAF, const vector<TLorentzVector> SelectedTausL  /*, bool &deltaPhiJetMet*/) {
  // this is for 2016data
  // jetType=0  -> usual jets; we use loose ID
  // here.https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2016
  // jetType=11 -> b-jets L
  // jetType=12 -> b-jets M
  // jetType=13 -> b-jets T
  // jetType=2  -> forward jets
  // MinDeltaPhiJetMet = 99.0;
  double MaxMostForwardJetEta = -99; /*{{{*/
  for (UInt_t j = 0; j < Jet_pt_->size(); ++j) {
    double jetpt = 0.;
    if (SysJes == 0 && SysJer == 0) {
      jetpt = Jet_Uncorr_pt_->at(j) * Jet_JesSF_->at(j) * Jet_JerSF_->at(j);
    }
    if (SysJes == 1 && SysJer == 0) {
      jetpt = Jet_Uncorr_pt_->at(j) * Jet_JesSFup_->at(j) * Jet_JerSF_->at(j);
    }
    if (SysJes == 2 && SysJer == 0) {
      jetpt = Jet_Uncorr_pt_->at(j) * Jet_JesSFdown_->at(j) * Jet_JerSF_->at(j);
    }
    if (SysJes == 0 && SysJer == 1) {
      jetpt = Jet_Uncorr_pt_->at(j) * Jet_JesSF_->at(j) * Jet_JerSFup_->at(j);
    }
    if (SysJes == 0 && SysJer == 2) {
      jetpt = Jet_Uncorr_pt_->at(j) * Jet_JesSF_->at(j) * Jet_JerSFdown_->at(j);
    }
    //    if(fabs(Jet_eta_->at(j))>2.65&&fabs(Jet_eta_->at(j))<3.139&&jetpt>50)
    // continue;
    //    ?what does this do?
    if (!(jetpt > 25))
      continue;
    double NHF = Jet_neutralHadEnergyFraction_->at(j);
    double NEMF = Jet_neutralEmEnergyFraction_->at(j);
    double CHF = Jet_chargedHadronEnergyFraction_->at(j);
    double MUF = Jet_muonEnergyFraction_->at(j);
    double CEMF = Jet_chargedEmEnergyFraction_->at(j);
    double NumConst = Jet_numberOfConstituents_->at(j);
    double NumNeutralParticles =
        Jet_numberOfConstituents_->at(j) - Jet_chargedMultiplicity_->at(j);
    double CHM = Jet_chargedMultiplicity_->at(j);
    if (!(fabs(Jet_eta_->at(j)) < 5.0))
      continue;
    // it seems that b jet also have to meet below requirements?
    // yes
    if (fabs(Jet_eta_->at(j)) < 2.4) {
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
    } else if (fabs(Jet_eta_->at(j)) > 2.4 && fabs(Jet_eta_->at(j)) < 2.7) {
      if (!(NHF < 0.99))
        continue;
      if (!(NEMF < 0.99))
        continue;
      if (!(NumConst > 1))
        continue;
      //   if(!(MUF<0.8)) continue;
    } else if (fabs(Jet_eta_->at(j)) > 2.7 && fabs(Jet_eta_->at(j)) < 3.0) {
      if (!(NEMF > 0.01))
        continue;
      if (!(NHF < 0.98))
        continue;
      if (!(NumNeutralParticles > 2))
        continue;
    } else if (fabs(Jet_eta_->at(j)) > 3.0) {
      if (!(NEMF < 0.90))
        continue;
      if (!(NumNeutralParticles > 10))
        continue;
    }

    if (deepJet) {//https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
      if (jetType == 11) {
        if (!(Jet_pfDeepFlavourBJetTags_->at(j) > 0.0614))
          continue;
      }
      if (jetType == 12) {
        if (!(Jet_pfDeepFlavourBJetTags_->at(j) > 0.3093))
          continue;
      }
      if (jetType == 13) {
        if (!(Jet_pfDeepFlavourBJetTags_->at(j) > 0.7221))
          continue;
      }
    } else {
      if (jetType == 11) {
        if (!(Jet_pfDeepCSVBJetTags_->at(j) > 0.2217))
          continue;
      }
      if (jetType == 12) {
        if (!(Jet_pfDeepCSVBJetTags_->at(j) > 0.6321))
          continue;
      }
      if (jetType == 13) {
        if (!(Jet_pfDeepCSVBJetTags_->at(j) > 0.8953))
          continue;
      }
    }
    // find mostforwardjeteta
    if (jetType == 0) { // normal jet
      if (fabs(Jet_eta_->at(j)) > MaxMostForwardJetEta) {
        MaxMostForwardJetEta = fabs(Jet_eta_->at(j));
        MostForwardJetEta = Jet_eta_->at(j);
        MostForwardJetPt = jetpt;//a branch in new tree
      } // MostForwardJetEta branch in new tree and SB.
      if (!(fabs(Jet_eta_->at(j)) < 2.4))
        continue;
    }
    if (jetType == 2) { // forwardjet
      if (!(fabs(Jet_eta_->at(j)) >= 2.4 && fabs(Jet_eta_->at(j)) <= 5))
        continue;
      if (!(jetpt > 25))
        continue;
      if (fabs(Jet_eta_->at(j)) >= 2.7 && fabs(Jet_eta_->at(j)) <= 3.0) {
        if (!(jetpt > 60.0))
          continue;
      }
    }
    // if (DeltaPhi(Jet_phi_->at(j), Met_type1PF_phi_) < MinDeltaPhiJetMet)
      // MinDeltaPhiJetMet = DeltaPhi( Jet_phi_->at(j),   Met_type1PF_phi_); // MinDeltaPhiJetMe a branch in newtree and SB
      //
      // overlap removal
    double deltaR = 0;
    double minDeltaR = 100;
    for (UInt_t lep = 0; lep < LeptonsMVAF.size(); lep++){
        deltaR =  DeltaR( LeptonsMVAF[lep].Eta(), Jet_eta_->at(j), LeptonsMVAF[lep].Phi(), Jet_phi_->at(j));
        if ( deltaR < minDeltaR ) minDeltaR = deltaR ;//The continue statement provides a convenient way to jump to the end of the loop body for the current iteration.
    }
    if ( !( minDeltaR >= 0.4 ) ) continue;
    double deltaR_tau =0;
    double minDeltaR_tau = 100;
    for ( UInt_t tau = 0; tau < SelectedTausL.size(); tau++){
        deltaR_tau =  DeltaR( SelectedTausL[tau].Eta(), Jet_eta_->at(j), SelectedTausL[tau].Phi(), Jet_phi_->at(j));
        if ( deltaR < minDeltaR_tau ) minDeltaR_tau = deltaR_tau;
    }
    if ( !(minDeltaR_tau >= 0.4)) continue;

    //jet jet removal
    // double deltaR_jet = 0;
    // double minDeltaR_jet = 100;
    // for (UInt_t k = j+1; k < Jet_pt_->size(); ++k) {
        // deltaR_jet = DeltaR( Jet_eta_->at(k), Jet_eta_->at(j), Jet_phi_->at(k), Jet_phi_->at(j));
        // if ( deltaR_jet < minDeltaR_jet  ) minDeltaR_jet = deltaR_jet;
    // }
    // if ( !(minDeltaR_jet >= 0.4 )) continue;

    double SF = jetpt / Jet_pt_->at(j);
    TLorentzVector jet_prov;
    jet_prov.SetPtEtaPhiM(Jet_pt_->at(j), Jet_eta_->at(j), Jet_phi_->at(j),
                          Jet_mass_->at(j));
    TLorentzVector jet;
    jet.SetPxPyPzE(SF * jet_prov.Px(), SF * jet_prov.Py(), SF * jet_prov.Pz(),
                   SF * jet_prov.E());
    //?is this  step necessary?
    //???why do this?
    SelectedJets.push_back(jet);
    SelectedJetsIndex.push_back(j);
    if (deepJet) {
      SelectedJetsBTags.push_back(Jet_pfDeepFlavourBJetTags_->at(j));
    } else {
      SelectedJetsBTags.push_back(Jet_pfDeepCSVBJetTags_->at(j));
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

void SelectTops(vector<TLorentzVector> &SelectedTops) {
  for (UInt_t j = 0; j < TopTagger_type_->size(); ++j) {
    if (!(TopTagger_type_->at(j) == 3))
      continue; // resolved
    //        if(!(TopTagger_discriminator_->at(j)>0.6)) continue;
    //        ??not sure of the effect of discriminator
    TLorentzVector jet1;
    jet1.SetPtEtaPhiM(Jet_pt_->at(TopTagger_jet1Idx_->at(j)),
                      Jet_eta_->at(TopTagger_jet1Idx_->at(j)), Jet_phi_->at(j),
                      Jet_mass_->at(TopTagger_jet1Idx_->at(j)));
    TLorentzVector jet2;
    jet2.SetPtEtaPhiM(Jet_pt_->at(TopTagger_jet2Idx_->at(j)),
                      Jet_eta_->at(TopTagger_jet2Idx_->at(j)), Jet_phi_->at(j),
                      Jet_mass_->at(TopTagger_jet2Idx_->at(j)));
    TLorentzVector jet3;
    jet3.SetPtEtaPhiM(Jet_pt_->at(TopTagger_jet3Idx_->at(j)),
                      Jet_eta_->at(TopTagger_jet3Idx_->at(j)), Jet_phi_->at(j),
                      Jet_mass_->at(TopTagger_jet3Idx_->at(j)));

    /*        double top_pt =
    Jet_pt_->at(TopTagger_jet1Idx_->at(j))+Jet_pt_->at(TopTagger_jet2Idx_->at(j))+Jet_pt_->at(TopTagger_jet3Idx_->at(j));//this
    top_pt calculation is wrong
    //         TopPtMin =
    (SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).Pt();//refresh in the loop
           // top_eta and phi need modification
            double top_eta =
    Jet_eta_->at(TopTagger_jet1Idx_->at(j))+Jet_eta_->at(TopTagger_jet2Idx_->at(j))+Jet_eta_->at(TopTagger_jet3Idx_->at(j));
            double top_phi =
    Jet_phi_->at(TopTagger_jet1Idx_->at(j))+Jet_phi_->at(TopTagger_jet2Idx_->at(j))+Jet_phi_->at(TopTagger_jet3Idx_->at(j));
            double top_m =
    Jet_mass_->at(TopTagger_jet1Idx_->at(j))+Jet_mass_->at(TopTagger_jet2Idx_->at(j))+Jet_mass_->at(TopTagger_jet3Idx_->at(j));*/
    //        TLorentzVector top;
    // top.SetPtEtaPhiM(top_pt,top_eta,top_phi,top_m);
    TLorentzVector top;
    top = jet1 + jet2 + jet3;
    SelectedTops.push_back(top);
  }
}

double TopScoreAllTopsCal(const vector<TLorentzVector> SelectedTops) {
  double init = 0;
  for (UInt_t j = 0; j < SelectedTops.size(); ++j) {
    init = init + TopTagger_discriminator_->at(j);
  }
  return init;
}

/*
void SelectCA8Jets(int CA8jetType,vector<TLorentzVector> &
SelectedCA8Jets,vector<TLorentzVector> SelectedElectrons,vector<TLorentzVector>
SelectedMuons, vector<int> & CA8Indices,
                   int SysJes, int SysJer, bool data, bool &deltaPhiJetMet){
  //CA8jetType=0 -> W-jets
  //CA8jetType=1 -> top-jets
  for (UInt_t j = 0; j < BoostedJet_pt_->size(); ++j){
    double jetpt = 0.;
    if(SysJes==0 && SysJer==0){jetpt =
BoostedJet_Uncorr_pt_->at(j)*BoostedJet_JesSF_->at(j)
*BoostedJet_JerSF_->at(j)    ;}
    if(SysJes==1 && SysJer==0){jetpt =
BoostedJet_Uncorr_pt_->at(j)*BoostedJet_JesSFup_->at(j)
*BoostedJet_JerSF_->at(j)    ;}
    if(SysJes==2 && SysJer==0){jetpt =
BoostedJet_Uncorr_pt_->at(j)*BoostedJet_JesSFdown_->at(j)*BoostedJet_JerSF_->at(j)
;}
    if(SysJes==0 && SysJer==1){jetpt =
BoostedJet_Uncorr_pt_->at(j)*BoostedJet_JesSF_->at(j)
*BoostedJet_JerSFup_->at(j)  ;}
    if(SysJes==0 && SysJer==2){jetpt =
BoostedJet_Uncorr_pt_->at(j)*BoostedJet_JesSF_->at(j)
*BoostedJet_JerSFdown_->at(j);}
    double SF = jetpt/BoostedJet_pt_->at(j);
    if(!(jetpt>200)) continue;
    if(!(fabs(BoostedJet_eta_->at(j))<2.4))               continue;
    if(!(BoostedJet_neutralHadEnergyFraction_->at(j)<0.90)) continue;
    if(!(BoostedJet_neutralEmEnergyFraction_->at(j)<0.90)) continue;
    if(!(BoostedJet_numberOfConstituents_->at(j)>1)) continue;
    if(!(BoostedJet_chargedHadronEnergyFraction_->at(j)>0.0)) continue;
    if(!(BoostedJet_chargedMultiplicity_->at(j)>0.0)) continue;
    if(CA8jetType==0){
      if(!(SF*BoostedJet_puppi_softdrop_mass_->at(j)>65 &&
SF*BoostedJet_puppi_softdrop_mass_->at(j)<105)) continue;//wmass = 80
      if(!(BoostedJet_puppi_tau2_->at(j)/BoostedJet_puppi_tau1_->at(j)<0.45))
continue;
      //????what is softdrop and tau?
    }
    else if(CA8jetType==1) {
      if(!(jetpt>400)) continue;
      if(!(SF*BoostedJet_puppi_softdrop_mass_->at(j)>105 &&
SF*BoostedJet_puppi_softdrop_mass_->at(j)<220)) continue;
      if(!(BoostedJet_puppi_tau3_->at(j)/BoostedJet_puppi_tau2_->at(j)<0.80))
continue;
    }

    TLorentzVector jet_prov;
jet_prov.SetPtEtaPhiM(BoostedJet_pt_->at(j),BoostedJet_eta_->at(j),BoostedJet_phi_->at(j),BoostedJet_mass_->at(j));
    TLorentzVector jet;
jet.SetPxPyPzE(SF*jet_prov.Px(),SF*jet_prov.Py(),SF*jet_prov.Pz(),SF*jet_prov.E());
    SelectedCA8Jets.push_back(jet);
    CA8Indices.push_back(j);
  }
}
*/
/*
void ResolvedRegionSelection(bool &ResolvedEvent,vector<TLorentzVector>
SelectedJets,vector<double> SelectedJetsBTags,TLorentzVector &HadronicTopQuark,
                             TLorentzVector &Jet1,TLorentzVector
&Jet2,TLorentzVector &Jet3,bool TopMassCut,bool btag){
  double TopPtMin=250;
  double TopMassInitial=99999;
  for(unsigned int i=0; i<SelectedJets.size(); i++){
    for(unsigned int j=i+1; j<SelectedJets.size(); j++){
      for(unsigned int k=j+1; k<SelectedJets.size(); k++){
                  if(!((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).Pt()>TopPtMin))
continue;
        //if(!(fabs((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).M()-173.1)<TopMassInitial))
continue;
        if(TopMassCut){if(!((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).M()>100
&& (SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).M()<300)) continue;}
        if(btag){if(!(SelectedJetsBTags[i]>0.4941 || SelectedJetsBTags[j]>0.4941
|| SelectedJetsBTags[k]>0.4941)) continue;}
        if(SelectedJetsBTags[i]>SelectedJetsBTags[j] &&
SelectedJetsBTags[i]>SelectedJetsBTags[k]){
          Jet1.SetPtEtaPhiE(SelectedJets[i].Pt(),SelectedJets[i].Eta(),SelectedJets[i].Phi(),SelectedJets[i].E());
          Jet2.SetPtEtaPhiE(SelectedJets[j].Pt(),SelectedJets[j].Eta(),SelectedJets[j].Phi(),SelectedJets[j].E());
          Jet3.SetPtEtaPhiE(SelectedJets[k].Pt(),SelectedJets[k].Eta(),SelectedJets[k].Phi(),SelectedJets[k].E());
        }
        if(SelectedJetsBTags[j]>SelectedJetsBTags[i] &&
SelectedJetsBTags[j]>SelectedJetsBTags[k]){
          Jet1.SetPtEtaPhiE(SelectedJets[j].Pt(),SelectedJets[j].Eta(),SelectedJets[j].Phi(),SelectedJets[j].E());
          Jet2.SetPtEtaPhiE(SelectedJets[i].Pt(),SelectedJets[i].Eta(),SelectedJets[i].Phi(),SelectedJets[i].E());
          Jet3.SetPtEtaPhiE(SelectedJets[k].Pt(),SelectedJets[k].Eta(),SelectedJets[k].Phi(),SelectedJets[k].E());
        }
        if(SelectedJetsBTags[k]>SelectedJetsBTags[i] &&
SelectedJetsBTags[k]>SelectedJetsBTags[j]){
          Jet1.SetPtEtaPhiE(SelectedJets[k].Pt(),SelectedJets[k].Eta(),SelectedJets[k].Phi(),SelectedJets[k].E());
          Jet2.SetPtEtaPhiE(SelectedJets[i].Pt(),SelectedJets[i].Eta(),SelectedJets[i].Phi(),SelectedJets[i].E());
          Jet3.SetPtEtaPhiE(SelectedJets[j].Pt(),SelectedJets[j].Eta(),SelectedJets[j].Phi(),SelectedJets[j].E());
        }
        TopPtMin = (SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).Pt();
        TopMassInitial=fabs((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).M()-173.1);
        HadronicTopQuark=(SelectedJets[i]+SelectedJets[j]+SelectedJets[k]);//argument
in WriteTopRelatedBranches
//	deltaPhiMetTop = DeltaPhi(HadronicTopQuark.Phi(),Met_phi);//in NewTree
//	TransverseMassMetTop =
sqrt(2*HadronicTopQuark.Pt()*Met_pt*(1-cos(deltaPhiMetTop)));
        if(!(TransverseMassMetTop>500)) continue;
        ResolvedEvent=true;//argument in WriteTopRelatedBranches
      }
    }
  }
}
*/

// I think this function only works for top decay to 3 jets
void ResolvedRegionSelection(bool &ResolvedEvent,
                             vector<TLorentzVector> SelectedJets,
                             vector<double> SelectedJetsBTags,
                             TLorentzVector &HadronicTopQuark,
                             TLorentzVector &Jet1, TLorentzVector &Jet2,
                             TLorentzVector &Jet3, bool TopMassCut,
                             bool btag) { /*{{{*/
  double TopPtMin = 250;                  // refresh in the loop
  // how do we set this number?
  double TopMassInitial = 99999;
  for (unsigned int i = 0; i < SelectedJets.size(); i++) {
    for (unsigned int j = i + 1; j < SelectedJets.size(); j++) {
      for (unsigned int k = j + 1; k < SelectedJets.size(); k++) {
        if (!((SelectedJets[i] + SelectedJets[j] + SelectedJets[k]).Pt() >
              TopPtMin))
          continue;
        // if(!(fabs((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).M()-173.1)<TopMassInitial))
        // continue;
        if (TopMassCut) {
          if (!((SelectedJets[i] + SelectedJets[j] + SelectedJets[k]).M() >
                    100 &&
                (SelectedJets[i] + SelectedJets[j] + SelectedJets[k]).M() <
                    300))
            continue;
        }
        if (btag) {
          if (!(SelectedJetsBTags[i] > 0.6321 ||
                SelectedJetsBTags[j] > 0.6321 || SelectedJetsBTags[k] > 0.6321))
            continue;
        } // require a least 1  medium b jet
        // double TM =
        // sqrt(2*(SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).Pt()*Met_pt*(1-cos(DeltaPhi((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).Phi(),Met_phi))));
        //?what is TM?
        // if(!(TM>500)) continue;
        //???why make this cut?
        //?what if we have more than one pair of three jet?
        Jet1.SetPtEtaPhiE(SelectedJets[i].Pt(), SelectedJets[i].Eta(),
                          SelectedJets[i].Phi(), SelectedJets[i].E());
        Jet2.SetPtEtaPhiE(SelectedJets[j].Pt(), SelectedJets[j].Eta(),
                          SelectedJets[j].Phi(), SelectedJets[j].E());
        Jet3.SetPtEtaPhiE(SelectedJets[k].Pt(), SelectedJets[k].Eta(),
                          SelectedJets[k].Phi(), SelectedJets[k].E());
        TopPtMin = (SelectedJets[i] + SelectedJets[j] + SelectedJets[k])
                       .Pt(); // refresh in the loop
        TopMassInitial = fabs(
            (SelectedJets[i] + SelectedJets[j] + SelectedJets[k]).M() - 173.1);
        HadronicTopQuark =
            (SelectedJets[i] + SelectedJets[j] + SelectedJets[k]);
        //???will not work if we have more than 1 HadronicTopQuark
        deltaPhiMetTop =
            DeltaPhi(HadronicTopQuark.Phi(), Met_phi); // branch in new tree
        TransverseMassMetTop =
            sqrt(2 * HadronicTopQuark.Pt() * Met_pt *
                 (1 - cos(deltaPhiMetTop))); // branch in NewTree and SB
        ResolvedEvent = true;
      }
    }
  }
}
/*}}}*/
/*
void PartiallyMergedSelection(bool &PartiallyMerged,vector<TLorentzVector>
SelectedWJets,vector<TLorentzVector> SelectedJets,vector<double>
SelectedJetsBTags,TLorentzVector &HadronicTopQuark,TLorentzVector
&Jet1,TLorentzVector &Jet2,bool TopMassCut,bool btag,vector<int> CA8Indices,int
& CA8Index,double &WMass_,double &WSubjet_, bool data){
  double TopPtMin=20;
  double TopMassInitial=99999;
  for(unsigned int i=0; i<SelectedWJets.size(); i++){
    for(unsigned int k=0; k<SelectedJets.size(); k++){
      if(!((SelectedWJets[i]+SelectedJets[k]).Pt()>TopPtMin)) continue;
      //if(!(fabs((SelectedWJets[i]+SelectedJets[k]).M()-173.1)<TopMassInitial))
continue;
      if(!(DeltaR(SelectedWJets[i].Eta(),SelectedJets[k].Eta(),SelectedWJets[i].Phi(),SelectedJets[k].Phi())>0.8))
continue;
      if(btag){if(!(SelectedJetsBTags[k]>0.4941)) continue;}
      if(TopMassCut){if(!((SelectedWJets[i]+SelectedJets[k]).M()>100 &&
(SelectedWJets[i]+SelectedJets[k]).M()<300)) continue;}
      Jet1.SetPtEtaPhiE(SelectedWJets[i].Pt(),SelectedWJets[i].Eta(),SelectedWJets[i].Phi(),SelectedWJets[i].E());
      Jet2.SetPtEtaPhiE(SelectedJets[k].Pt(),SelectedJets[k].Eta(),SelectedJets[k].Phi(),SelectedJets[k].E());
      TopPtMin = (SelectedWJets[i]+SelectedJets[k]).Pt();
      PartiallyMerged=true;
      TopMassInitial=fabs((SelectedWJets[i]+SelectedJets[k]).M()-173.1);
      HadronicTopQuark=(SelectedWJets[i]+SelectedJets[k]);
      CA8Index=CA8Indices[i];

      double SF =
(BoostedJet_Uncorr_pt_->at(CA8Indices[i])/BoostedJet_pt_->at(CA8Indices[i]))*BoostedJet_JesSF_->at(CA8Indices[i])*BoostedJet_JerSF_->at(CA8Indices[i]);
      WMass_   = SF*BoostedJet_pruned_mass_->at(CA8Indices[i]);
      WSubjet_ =
BoostedJet_tau2_->at(CA8Indices[i])/BoostedJet_tau1_->at(CA8Indices[i]);
    }
  }
}

void FullyMergedSelection(bool & FullyMerged, vector<TLorentzVector>
SelectedTopJets, TLorentzVector &HadronicTopQuark,vector<int> CA8Indices,double
&TopSoftMass_,double &TopSubjet_, bool data){
  double TopPtMin=400;
  for(unsigned int i=0; i<SelectedTopJets.size(); i++){
    if(!(SelectedTopJets[i].Pt()>TopPtMin)) continue;
    FullyMerged=true;
    TopPtMin=SelectedTopJets[i].Pt();
    HadronicTopQuark=SelectedTopJets[i];
    double SF =
(BoostedJet_Uncorr_pt_->at(CA8Indices[i])/BoostedJet_pt_->at(CA8Indices[i]))*BoostedJet_JesSF_->at(CA8Indices[i])*BoostedJet_JerSF_->at(CA8Indices[i]);
    TopSoftMass_  = SF*BoostedJet_softdrop_mass_->at(CA8Indices[i]);
    TopSubjet_    =
BoostedJet_tau3_->at(CA8Indices[i])/BoostedJet_tau2_->at(CA8Indices[i]);
  }
}
*/

/*
void BTagSF(int selection, double JetPt, double JetEta, int flav, double &SF,
double &SFerr){
  bool DoubleUncertainty = false;
  double MinBJetPt = 20.;
  double MaxBJetPt = 1000.;
  double MaxLJetPt = 1000.;
  if((flav==5 || flav==4) && JetPt<=MinBJetPt){
    JetPt = MinBJetPt+0.1;
    DoubleUncertainty = true;
  }
  if((flav==5 || flav==4) && JetPt>=MaxBJetPt){
    JetPt = MaxBJetPt-0.1;
    DoubleUncertainty = true;
  }
  if(flav==0 && JetPt>=MaxLJetPt){
    JetPt = MaxLJetPt-0.1;
    DoubleUncertainty = true;
  }
  auto btagentry_flav = flav == 5 ? BTagEntry::FLAV_B : (flav == 4 ?
BTagEntry::FLAV_C : BTagEntry::FLAV_UDSG);
  double jet_scalefactor = 1;
  double jet_scalefactor_up = 0;
  double jet_scalefactor_do = 0;
  if(selection==0 || selection==1){
    if(flav==5 || flav==4){
      jet_scalefactor    = readerMComb.eval(btagentry_flav, JetEta, JetPt);
      jet_scalefactor_up = readerMComb_up.eval(btagentry_flav, JetEta, JetPt);
      jet_scalefactor_do = readerMComb_do.eval(btagentry_flav, JetEta, JetPt);
    } else {
      jet_scalefactor    = readerMIncl.eval(btagentry_flav, JetEta, JetPt);
      jet_scalefactor_up = readerMIncl_up.eval(btagentry_flav, JetEta, JetPt);
      jet_scalefactor_do = readerMIncl_do.eval(btagentry_flav, JetEta, JetPt);
    }
  } else if(selection==2){
    if(flav==5 || flav==4){
      jet_scalefactor    = readerLComb.eval(btagentry_flav, JetEta, JetPt);
      jet_scalefactor_up = readerLComb_up.eval(btagentry_flav, JetEta, JetPt);
      jet_scalefactor_do = readerLComb_do.eval(btagentry_flav, JetEta, JetPt);
    } else {
      jet_scalefactor    = readerLIncl.eval(btagentry_flav, JetEta, JetPt);
      jet_scalefactor_up = readerLIncl_up.eval(btagentry_flav, JetEta, JetPt);
      jet_scalefactor_do = readerLIncl_do.eval(btagentry_flav, JetEta, JetPt);
    }
  }
  if(DoubleUncertainty) {
    jet_scalefactor_up = 2*(jet_scalefactor_up - jet_scalefactor) +
jet_scalefactor;
    jet_scalefactor_do = 2*(jet_scalefactor_do - jet_scalefactor) +
jet_scalefactor;
  }
  if(jet_scalefactor==0){
    jet_scalefactor=1;
    jet_scalefactor_up=1;
    jet_scalefactor_do=1;
  }
  SF=jet_scalefactor;
  SFerr=max(fabs(jet_scalefactor-jet_scalefactor_up),fabs(jet_scalefactor-jet_scalefactor_do));
  //cout<<JetPt<<" "<<JetEta<<" "<<flav<<" ("<<btagentry_flav<<")
"<<jet_scalefactor<<" "<<jet_scalefactor_up<<" "<<jet_scalefactor_do<<endl;
}

*/
// w_Btag branch in NewTree and SB
//?what is this doing exactly?
/*
void get_weight_btag(int selection, double &w_Btag, double &w_BtagUp, double
&w_BtagDown, double &w_Btag1Up, double &w_Btag1Down, double &w_Btag2Up, double
&w_Btag2Down, double &w_BtagLoose, double &w_BtagLooseUp, double
&w_BtagLooseDown, string fileName){
  string inputFile =
"/publicfs/cms/user/yutz/Tprime/2017_dineutrino/BtagEfficiency_new_v3/"+fileName;
  const char *FILE = FILEprov.c_str();
  TFile *fileBTagEfficiency = TFile::Open(FILE);
  double mcTagMedium = 1.;     double mcTagLoose = 1.;
  double mcNoTagMedium = 1.;   double mcNoTagLoose = 1.;
  double dataTagMedium = 1.;   double dataTagLoose = 1.;
  double dataNoTagMedium = 1.; double dataNoTagLoose = 1.;
  double err1Medium = 0.;      double err1Loose = 0.;
  double err2Medium = 0.;      double err2Loose = 0.;
  double err3Medium = 0.;      double err3Loose = 0.;
  double err4Medium = 0.;      double err4Loose = 0.;
  for (UInt_t j = 0; j < Jet_pt_->size(); ++j){
    if(!((Jet_Uncorr_pt_->at(j)*Jet_JesSF_->at(j)*Jet_JerSF_->at(j))>20))
continue;
    if(!(fabs(Jet_eta_->at(j))<2.4)) continue;
    if(!(Jet_neutralHadEnergyFraction_->at(j)<0.90)) continue;
    if(!(Jet_neutralEmEnergyFraction_->at(j)<0.90)) continue;
    if(!(Jet_numberOfConstituents_->at(j)>1)) continue;
    if(!(Jet_chargedHadronEnergyFraction_->at(j)>0.0)) continue;
    if(!(Jet_chargedMultiplicity_->at(j)>0.0)) continue;
    //if(!(Jet_chargedEmEnergyFraction_->at(j)<0.99)) continue;
    double JetPt  = (Jet_Uncorr_pt_->at(j)*Jet_JesSF_->at(j)*Jet_JerSF_->at(j));
    double JetEta = fabs(Jet_eta_->at(j));
    int flav = Jet_hadronFlavour_->at(j);
    double MinBJetPt = 20.;
    double MaxBJetPt = 1000.;
    double MaxLJetPt = 1000.;
    if((flav==5 || flav==4) && JetPt<MinBJetPt){
      JetPt = MinBJetPt;
    }
    if((flav==5 || flav==4) && JetPt>MaxBJetPt){
      JetPt = MaxBJetPt;
    }
    if(flav==0 && JetPt>MaxLJetPt){
      JetPt = MaxLJetPt;
    }
    TH2F *NUM = (TH2F*)fileBTagEfficiency->Get("histM_b_passing_");
    TH2F *DEN = (TH2F*)fileBTagEfficiency->Get("histM_b_total_");
    if(selection==0 || selection==1){
      if(flav == 5) {
        NUM = (TH2F*)fileBTagEfficiency->Get("histM_b_passing_");
        DEN = (TH2F*)fileBTagEfficiency->Get("histM_b_total_");
      }else if( flav==4){
        NUM = (TH2F*)fileBTagEfficiency->Get("histM_c_passing_");
        DEN = (TH2F*)fileBTagEfficiency->Get("histM_c_total_");
      }else{
        NUM = (TH2F*)fileBTagEfficiency->Get("histM_udsg_passing_");
        DEN = (TH2F*)fileBTagEfficiency->Get("histM_udsg_total_");
      }
    } else if(selection==2){
      if(flav == 5) {
        NUM = (TH2F*)fileBTagEfficiency->Get("histL_b_passing_");
        DEN = (TH2F*)fileBTagEfficiency->Get("histL_b_total_");
      }else if( flav==4){
        NUM = (TH2F*)fileBTagEfficiency->Get("histL_c_passing_");
        DEN = (TH2F*)fileBTagEfficiency->Get("histL_c_total_");
      }else{
        NUM = (TH2F*)fileBTagEfficiency->Get("histL_udsg_passing_");
        DEN = (TH2F*)fileBTagEfficiency->Get("histL_udsg_total_");
      }
    }
    NUM->Divide(DEN);
    int etaBin = 1;
    int ptBin = 1;
    if(JetPt>19  && JetPt<=30)   ptBin = 1;
    if(JetPt>30  && JetPt<=50)   ptBin = 2;
    if(JetPt>50  && JetPt<=70)   ptBin = 3;
    if(JetPt>70  && JetPt<=100)  ptBin = 4;
    if(JetPt>100 && JetPt<=140)  ptBin = 5;
    if(JetPt>140 && JetPt<=200)  ptBin = 6;
    if(JetPt>200 && JetPt<=300)  ptBin = 7;
    if(JetPt>300 && JetPt<=600)  ptBin = 8;
    if(JetPt>600 && JetPt<=1000) ptBin = 9;
    if(flav!=5 && flav!=4)       ptBin = 1;
    double eff   = NUM->GetBinContent(ptBin,etaBin);
    double SF    = 1.0;
    double SFerr = 0.0;
    BTagSF(selection, JetPt, JetEta, flav, SF, SFerr);
    if(Jet_pfDeepCSVBJetTags_->at(j)>0.4941){
      mcTagMedium *= eff;
      dataTagMedium *= eff*SF;
      if(flav==5 || flav ==4)  err1Medium += SFerr/SF; //correlated for b/c
      else err3Medium += SFerr/SF;                     //correlated for light
    }else{
      mcNoTagMedium *= (1- eff);
      dataNoTagMedium *= (1- eff*SF);
      if(flav==5 || flav ==4 ) err2Medium += (-eff*SFerr)/(1-eff*SF);
//correlated for b/c
      else err4Medium +=  (-eff*SFerr)/(1-eff*SF); //correlated for light
    }
    if(Jet_pfDeepCSVBJetTags_->at(j)>0.1522){
      mcTagLoose *= eff;
      dataTagLoose *= eff*SF;
      if(flav==5 || flav ==4)  err1Loose += SFerr/SF;
      else err3Loose += SFerr/SF;
    }else{
      mcNoTagLoose *= (1- eff);
      dataNoTagLoose *= (1- eff*SF);
      if(flav==5 || flav ==4 ) err2Loose += (-eff*SFerr)/(1-eff*SF);
      else err4Loose +=  (-eff*SFerr)/(1-eff*SF);
    }
    delete NUM; delete DEN;
    //cout<<JetPt<<" "<<flav<<" "<<ptBin<<" "<<etaBin<<" "<<eff<<" "<<SF<<"
"<<SFerr<<endl;
  }
  double wtbtagMedium        = 1; double wtbtagLoose        = 1;
  double wtbtagErrBCMedium   = 0; double wtbtagErrBCLoose   = 0;
  double wtbtagErrUDSGMedium = 0; double wtbtagErrUDSGLoose = 0;
  if((mcNoTagMedium*mcTagMedium)!=0) wtbtagMedium        = (dataNoTagMedium *
dataTagMedium ) / ( mcNoTagMedium * mcTagMedium );
  if((mcNoTagMedium*mcTagMedium)!=0) wtbtagErrBCMedium   =
fabs(err1Medium+err2Medium) * wtbtagMedium;
  if((mcNoTagMedium*mcTagMedium)!=0) wtbtagErrUDSGMedium =
fabs(err3Medium+err4Medium) * wtbtagMedium;
  if((mcNoTagLoose*mcTagLoose)!=0) wtbtagLoose        = (dataNoTagLoose *
dataTagLoose ) / ( mcNoTagLoose * mcTagLoose );
  if((mcNoTagLoose*mcTagLoose)!=0) wtbtagErrBCLoose   =
fabs(err1Loose+err2Loose) * wtbtagLoose;
  if((mcNoTagLoose*mcTagLoose)!=0) wtbtagErrUDSGLoose =
fabs(err3Loose+err4Loose) * wtbtagLoose;
  w_Btag     = wtbtagMedium;
  w_BtagUp   =
wtbtagMedium+sqrt(wtbtagErrBCMedium*wtbtagErrBCMedium+wtbtagErrUDSGMedium*wtbtagErrUDSGMedium);
  w_BtagDown =
wtbtagMedium-sqrt(wtbtagErrBCMedium*wtbtagErrBCMedium+wtbtagErrUDSGMedium*wtbtagErrUDSGMedium);
  w_Btag1Up   = wtbtagMedium+sqrt(wtbtagErrBCMedium*wtbtagErrBCMedium);
  w_Btag1Down = wtbtagMedium-sqrt(wtbtagErrBCMedium*wtbtagErrBCMedium);
  w_Btag2Up   = wtbtagMedium+sqrt(wtbtagErrUDSGMedium*wtbtagErrUDSGMedium);
  w_Btag2Down = wtbtagMedium-sqrt(wtbtagErrUDSGMedium*wtbtagErrUDSGMedium);
  w_BtagLoose     = wtbtagLoose;
  w_BtagLooseUp   =
wtbtagLoose+sqrt(wtbtagErrBCLoose*wtbtagErrBCLoose+wtbtagErrUDSGLoose*wtbtagErrUDSGLoose);
  w_BtagLooseDown =
wtbtagLoose-sqrt(wtbtagErrBCLoose*wtbtagErrBCLoose+wtbtagErrUDSGLoose*wtbtagErrUDSGLoose);
  if(selection==2){
    w_Btag     = wtbtagLoose;
    w_BtagUp   =
wtbtagLoose+sqrt(wtbtagErrBCLoose*wtbtagErrBCLoose+wtbtagErrUDSGLoose*wtbtagErrUDSGLoose);
    w_BtagDown =
wtbtagLoose-sqrt(wtbtagErrBCLoose*wtbtagErrBCLoose+wtbtagErrUDSGLoose*wtbtagErrUDSGLoose);
    w_Btag1Up   = wtbtagLoose+sqrt(wtbtagErrBCLoose*wtbtagErrBCLoose);
    w_Btag1Down = wtbtagLoose-sqrt(wtbtagErrBCLoose*wtbtagErrBCLoose);
    w_Btag2Up   = wtbtagLoose+sqrt(wtbtagErrUDSGLoose*wtbtagErrUDSGLoose);
    w_Btag2Down = wtbtagLoose-sqrt(wtbtagErrUDSGLoose*wtbtagErrUDSGLoose);
  }
  //cout<<"BTAG WEIGHT  "<<wtbtagErrBC<<" "<<wtbtagErrUDSG<<" "<<w_Btag<<"
"<<w_BtagUp<<" "<<endl;
  delete fileBTagEfficiency;
}
*/

/*void ForwardJetSF(vector<TLorentzVector> SelectedForwardJets, double &w_for_,
double &w_forUp_, double &w_forDown_){
  if(SelectedForwardJets.size()>0){
    double eta = eta = SelectedForwardJets[0].Eta(); double pt =
SelectedForwardJets[0].Pt();
    int X1=-99; int Y1=-99;
    for(int i=1; i<histoForwardJet->GetXaxis()->GetNbins()+2; i++){
      if(eta<histoForwardJet->GetXaxis()->GetBinLowEdge(i)){ X1=i-1; break; }
    }
    for(int i=1; i<histoForwardJet->GetYaxis()->GetNbins()+2; i++){
      if(pt <histoForwardJet->GetYaxis()->GetBinLowEdge(i)){ Y1=i-1; break; }
    }
    if(pt>=histoForwardJet->GetYaxis()->GetBinLowEdge(histoForwardJet->GetYaxis()->GetNbins()+1))
{Y1=(histoForwardJet->GetYaxis()->GetNbins()+1)-1;}
    double SF = histoForwardJet->GetBinContent(X1,Y1);
    w_for_     = SF;
    w_forUp_   = SF + histoForwardJet->GetBinError(X1,Y1); //w_forUp_   = 1.0;
    w_forDown_ = SF - histoForwardJet->GetBinError(X1,Y1); //w_forDown_ = 1.0;
  }
}*/

void TopSF(TLorentzVector SelectedTopJets, bool FullyMerged, double &w_topJet_,
           double &w_topJetUp_, double &w_topJetDown_) { /*{{{*/
  if (FullyMerged) {
    if (SelectedTopJets.Pt() < 550)
      w_topJet_ = 1.06;
    if (SelectedTopJets.Pt() >= 550)
      w_topJet_ = 1.06;
    if (SelectedTopJets.Pt() < 550)
      w_topJetUp_ = 1.06 + 0.09;
    if (SelectedTopJets.Pt() >= 550)
      w_topJetUp_ = 1.06 + 0.09;
    if (SelectedTopJets.Pt() < 550)
      w_topJetDown_ = 1.06 - 0.04;
    if (SelectedTopJets.Pt() >= 550)
      w_topJetDown_ = 1.06 - 0.04;
  }
} /*}}}*/

void WSF(TLorentzVector WJet, bool PartiallyMerged, double &w_WJet_,
         double &w_WJetUp_, double &w_WJetDown_, int CA8Index, int SysJes,
         int SysJer) { /*{{{*/
  if (PartiallyMerged) {
    bool matched = false;
    GenWBoson(matched, WJet);
    if (matched) {
      w_WJet_ = 1.00 * 1.23 * 1.11;
      if (SysJes == 1)
        w_WJet_ =
            1.00 * 1.23 * 1.11 +
            sqrt(pow(Jet_JesSFup_->at(CA8Index) / Jet_JesSF_->at(CA8Index) - 1,
                     2) +
                 0.023 * 0.023);
      if (SysJes == 2)
        w_WJet_ =
            1.00 * 1.23 * 1.11 - sqrt(pow(1 - Jet_JesSFdown_->at(CA8Index) /
                                                  Jet_JesSF_->at(CA8Index),
                                          2) +
                                      0.023 * 0.023);
      if (SysJer == 1)
        w_WJet_ =
            1.00 * 1.23 * 1.11 +
            sqrt(pow(Jet_JerSFup_->at(CA8Index) / Jet_JerSF_->at(CA8Index) - 1,
                     2) +
                 0.018 * 0.018);
      if (SysJer == 2)
        w_WJet_ =
            1.00 * 1.23 * 1.11 - sqrt(pow(1 - Jet_JerSFdown_->at(CA8Index) /
                                                  Jet_JerSF_->at(CA8Index),
                                          2) +
                                      0.018 * 0.018);
      w_WJetUp_ = 1.00 * 1.23 * 1.11 + (0.08);
      w_WJetDown_ = 1.00 * 1.23 * 1.11 - (0.08);
      if (WJet.Pt() > 200) {
        w_WJetUp_ = 1.00 * 1.23 * 1.11 + (0.08 + 0.054 * log(WJet.Pt() / 200));
        w_WJetDown_ =
            1.00 * 1.23 * 1.11 - (0.08 + 0.054 * log(WJet.Pt() / 200));
      }
    }
  }
} /*}}}*/

//?what's the purpose of thisi?
/*
void HTSF(TString fileName, double HT, double Met_pt, double &w_SF1, double
&w_SF1Up, double &w_SF1Down, double &w_SF2, double &w_SF2Up, double &w_SF2Down,
double &w_SF3, double &w_SF3Up, double &w_SF3Down){
  if(fileName.find("ZToNuNu")!=string::npos ){
        int htBin = 0;   int metBin = 0;
        if (HT>200 && HT<400) htBin = 1;
        if (HT>400 && HT<600) htBin = 2;
        if (HT>600 && HT<800) htBin = 3;
        if (HT>800 && HT<1200) htBin = 4;
        if (HT>1200 && HT<3000) htBin = 5;
        if (Met_pt>200 && Met_pt<400) metBin = 1;
        if (Met_pt>400 && Met_pt<700) metBin = 2;
        if (Met_pt>700 && Met_pt<1600) metBin = 3;
        if (htBin==0 || metBin==0){
           w_SF1=1; w_SF1Up=1; w_SF1Down=1;
        }  else {
                                        //?what is histoSF1
                                        //in .h file, from
SF_dineutrino/SF_2D.root
           w_SF1 = histoSF1->GetBinContent(htBin,metBin);
           w_SF1Up = histoSF1->GetBinContent(htBin,metBin)+
//778histoSF1->GetBinError(htBin,metBin);
           w_SF1Down = TMath::Max(0.,histoSF1->GetBinContent(htBin,metBin)-
histoSF1->GetBinError(htBin,metBin));
        }
  }
  if(fileName.find("WToLNu")!=string::npos ){
        int htBin = 0;   int metBin = 0;
        if (HT>200 && HT<400) htBin = 1;
        if (HT>400 && HT<600) htBin = 2;
        if (HT>600 && HT<800) htBin = 3;
        if (HT>800 && HT<1200) htBin = 4;
        if (HT>1200 && HT<3000) htBin = 5;
        if (Met_pt>200 && Met_pt<400) metBin = 1;
        if (Met_pt>400 && Met_pt<700) metBin = 2;
        if (Met_pt>700 && Met_pt<1600) metBin = 3;
        if (htBin==0 || metBin==0){
           w_SF2=1; w_SF2Up=1; w_SF2Down=1;
        }  else {
           w_SF2 = histoSF2->GetBinContent(htBin,metBin);
           w_SF2Up = histoSF2->GetBinContent(htBin,metBin)+
histoSF2->GetBinError(htBin,metBin);
           w_SF2Down = TMath::Max(0.,histoSF2->GetBinContent(htBin,metBin)-
histoSF2->GetBinError(htBin,metBin));
        }
  }
   if(fileName.find("TT")!=string::npos||fileName.find("tZq")!=string::npos||fileName.find("ST")!=string::npos
){
        int htBin = 0;   int metBin = 0;
        if (HT>200 && HT<400) htBin = 1;
        if (HT>400 && HT<600) htBin = 2;
        if (HT>600 && HT<800) htBin = 3;
        if (HT>800 && HT<1200) htBin = 4;
        if (HT>1200 && HT<3000) htBin = 5;
        if (Met_pt>200 && Met_pt<400) metBin = 1;
        if (Met_pt>400 && Met_pt<700) metBin = 2;
        if (Met_pt>700 && Met_pt<1600) metBin = 3;
        if (htBin==0 || metBin==0){
           w_SF3=1; w_SF3Up=1; w_SF3Down=1;
        }  else {
           w_SF3 = histoSF3->GetBinContent(htBin,metBin);
           w_SF3Up = histoSF3->GetBinContent(htBin,metBin)+
histoSF3->GetBinError(htBin,metBin);
           w_SF3Down = TMath::Max(0.,histoSF3->GetBinContent(htBin,metBin)-
histoSF3->GetBinError(htBin,metBin));
        }
  }

}
*/

void TriggerSF(double Met_pt, double jetsL_MHT, double &w_Trig,
               double &w_TrigUp, double &w_TrigDown) { /*{{{*/
  int metBin = 0;
  int mhtBin = 0;
  if (Met_pt > 0 && Met_pt < 25)
    metBin = 1;
  if (Met_pt > 25 && Met_pt < 50)
    metBin = 2;
  if (Met_pt > 50 && Met_pt < 75)
    metBin = 3;
  if (Met_pt > 75 && Met_pt < 100)
    metBin = 4;
  if (Met_pt > 100 && Met_pt < 125)
    metBin = 5;
  if (Met_pt > 125 && Met_pt < 150)
    metBin = 6;
  if (Met_pt > 150 && Met_pt < 175)
    metBin = 7;
  if (Met_pt > 175 && Met_pt < 200)
    metBin = 8;
  if (Met_pt > 200 && Met_pt < 225)
    metBin = 9;
  if (Met_pt > 225 && Met_pt < 250)
    metBin = 10;
  if (Met_pt > 250 && Met_pt < 300)
    metBin = 11;
  if (Met_pt > 300 && Met_pt < 400)
    metBin = 12;
  if (Met_pt > 400 && Met_pt < 500)
    metBin = 13;
  if (Met_pt > 500 && Met_pt < 1000)
    metBin = 14;

  if (jetsL_MHT > 0 && jetsL_MHT < 25)
    mhtBin = 1;
  if (jetsL_MHT > 25 && jetsL_MHT < 50)
    mhtBin = 2;
  if (jetsL_MHT > 50 && jetsL_MHT < 75)
    mhtBin = 3;
  if (jetsL_MHT > 75 && jetsL_MHT < 100)
    mhtBin = 4;
  if (jetsL_MHT > 100 && jetsL_MHT < 125)
    mhtBin = 5;
  if (jetsL_MHT > 125 && jetsL_MHT < 150)
    mhtBin = 6;
  if (jetsL_MHT > 150 && jetsL_MHT < 175)
    mhtBin = 7;
  if (jetsL_MHT > 175 && jetsL_MHT < 200)
    mhtBin = 8;
  if (jetsL_MHT > 200 && jetsL_MHT < 225)
    mhtBin = 9;
  if (jetsL_MHT > 225 && jetsL_MHT < 250)
    mhtBin = 10;
  if (jetsL_MHT > 250 && jetsL_MHT < 300)
    mhtBin = 11;
  if (jetsL_MHT > 300 && jetsL_MHT < 400)
    mhtBin = 12;
  if (jetsL_MHT > 400 && jetsL_MHT < 500)
    mhtBin = 13;
  if (jetsL_MHT > 500 && jetsL_MHT < 1000)
    mhtBin = 14;

  if (metBin == 0 || mhtBin == 0) {
    w_Trig = 1;
    w_TrigUp = 1;
    w_TrigDown = 1;
  } else {
    w_Trig = histoTrig->GetBinContent(metBin, mhtBin);
    w_TrigUp = histoTrig->GetBinContent(metBin, mhtBin) +
               histoTrig->GetBinError(metBin, mhtBin);
    w_TrigDown = TMath::Max(0., histoTrig->GetBinContent(metBin, mhtBin) -
                                    histoTrig->GetBinError(metBin, mhtBin));
  }
} /*}}}*/

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

double DeltaPhi(double phi1, double phi2) { /*{{{*/
  double deltaPhi = TMath::Abs(phi1 - phi2);
  if (deltaPhi > TMath::Pi())
    deltaPhi = TMath::TwoPi() - deltaPhi;
  return deltaPhi;
} /*}}}*/

void MinMaxDeltaPhiCal(vector<TLorentzVector> SelectedJets,
                       vector<double> &MinMaxDeltaPhi) {
  double initMaxPhi = 0;
  double MaxPhi = 0;
  double initMin = 1000000;
  double MinPhi = 1000000;
  double deltaPhi = 0;
  double Eta = 0;
  double Eta2 = 0;
  double Phi = 0;
  double Phi2 = 0;
  if (SelectedJets.size() > 1) {
    for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
      Eta = SelectedJets[j].Eta();
      Phi = SelectedJets[j].Phi();
      for (UInt_t k = j + 1; k < SelectedJets.size(); ++k) {
        Eta2 = SelectedJets[k].Eta();
        Phi2 = SelectedJets[k].Phi();
        deltaPhi = DeltaPhi(Phi, Phi2);
        if (deltaPhi > initMaxPhi)
          initMaxPhi = deltaPhi;
        if (deltaPhi < initMin)
          initMin = deltaPhi;
      }
      if (initMaxPhi > MaxPhi)
        MaxPhi = initMaxPhi;
      if (initMin < MinPhi)
        MinPhi = initMin;
    }
  } else {
    MaxPhi = -1;
    MinPhi = -1; // means have less than 2 jets
  }
  MinMaxDeltaPhi.push_back(MinPhi); // cout<<MinPhi<<"  ";
  MinMaxDeltaPhi.push_back(MaxPhi);
} 

double MinDeltaEtaCal(const TLorentzVector jets,
                      const vector<TLorentzVector> SelectedJets) {
  double eta_1 = jets.Eta();
  double min_deltaEta = 10;
  double init = 0;
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    init = fabs(SelectedJets[j].Eta() - eta_1);
    if (init < min_deltaEta)
      min_deltaEta = init;
  }
  return min_deltaEta;
}

double HTcalculator(vector<TLorentzVector> SelectedJets) { /*{{{*/
  double HTprov = 0;
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    HTprov =
        HTprov + SelectedJets[j].Pt(); //.Pt: the 3 vertor component, scalar
  }
  return HTprov;
} /*}}}*/

double MHTcalculator(vector<TLorentzVector> SelectedJets) { /*{{{*/
  TLorentzVector SumJets;
  SumJets.SetPtEtaPhiE(0, 0, 0, 0);
  double MHTprov = 0;
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    SumJets = SumJets + SelectedJets[j];
  }
  MHTprov = SumJets.Pt();
  return MHTprov;
} /*}}}*/

double rationHT_4toRestCal(vector<TLorentzVector> SelectedJets){
    vector<TLorentzVector> leading4 ;
    vector<TLorentzVector> rest;
    for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
        if ( j < 4 ) leading4.push_back(SelectedJets[j]);
        if ( j >= 4) rest.push_back(SelectedJets[j]);
    }
    if ( SelectedJets.size() > 4){
        return HTcalculator(leading4)/HTcalculator(rest);
    }
    else return -99;
}
//
//
double
InvariantMassLike_Calculator(vector<TLorentzVector> SelectedJets) { /*{{{*/
  double InM = 0;
  double SumE = 0;
  double MHT = MHTcalculator(SelectedJets);
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    SumE = SumE + SelectedJets[j].E();
  }
  InM = sqrt(SumE * SumE - MHT * MHT);
  return InM;
} /*}}}*/
double InvariantMassCalculator(vector<TLorentzVector> SelectedJets) {
  //	double SumE = 0;
  //    TVector3 p = {0,0,0} ;
  TLorentzVector jet_sum = { 0, 0, 0, 0 };
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    jet_sum = jet_sum + SelectedJets[j];
  }
  double InMass = jet_sum.M();
  return InMass;
}
double InvariantMass2SysCal(const vector<TLorentzVector> a,
                            const vector<TLorentzVector> b) {
  vector<TLorentzVector> vector_sum(a.begin(), a.end());
  vector_sum.insert(vector_sum.end(), b.begin(), b.end());
  /*    TLorentzVector jet_sum = {0,0,0,0};
      for (UInt_t j = 0; j < a.size(); ++j){
          jet_sum = jet_sum + a[j];
      }
      TLorentzVector b_sum = {0,0,0,0};
      for (UInt_t k = 0; k < b.size(); ++k){
          b_sum = b_sum + b[k];
      }*/
  double invariantMass = InvariantMassCalculator(vector_sum);
  return invariantMass;
}

int ChargeSum(const vector<int> SelectedElectronsMVATIndex, int type) {
  int charge_sum = 0;
  for (UInt_t j = 0; j < SelectedElectronsMVATIndex.size(); ++j) {
    if (type == 0)
      // charge_sum += patElectron_charge_->at(j);
      charge_sum += patElectron_charge_->at(SelectedElectronsMVATIndex[j]);
    if (type == 1)
      charge_sum += Tau_charge_->at(SelectedElectronsMVATIndex[j]);
    if (type == 2)
      charge_sum += Muon_charge_->at(SelectedElectronsMVATIndex[j]);
  }
  return charge_sum;
}

double TransEnergyCal(const TLorentzVector SelectedJets) {
  //    TVector3 p =  SelectedJets.Vect();
  double pt = SelectedJets.Pt();
  double trans_energy = sqrt(SelectedJets.M() * SelectedJets.M() + pt * pt);
  return trans_energy;
}
double TransEnergySysCal(const vector<TLorentzVector> SelectedJets) {
  double transE = 0;
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    transE += TransEnergyCal(SelectedJets[j]);
  }
  return transE;
}
double TransMassCal(const vector<TLorentzVector> SelectedJets) {
  double MHT = MHTcalculator(SelectedJets);
  double transE = 0;
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    transE += TransEnergyCal(SelectedJets[j]);
  }
  double trans_mass = sqrt(MHT * MHT + transE * transE);
  return trans_mass;
}

double TransMassSysCal(const vector<TLorentzVector> Jets,
                       const vector<TLorentzVector> Leptons) {
  double transE1 = TransEnergySysCal(Jets);
  double transE2 = TransEnergySysCal(Leptons);
  TLorentzVector SumJets;
  SumJets.SetPtEtaPhiE(0, 0, 0, 0);
  TLorentzVector SumLeptons;
  SumLeptons.SetPtEtaPhiE(0, 0, 0, 0);
  for (UInt_t j = 0; j < Jets.size(); ++j) {
    SumJets = SumJets + Jets[j];
  }
  for (UInt_t k = 0; k < Leptons.size(); ++k) {
    SumLeptons = SumLeptons + Leptons[k];
  }
  TVector3 MHTsum = (SumJets + SumLeptons).Vect();
  double transMass =
      sqrt((transE1 + transE2) * (transE1 + transE2) - MHTsum * MHTsum);
  return transMass;
}

double MinDeltaRCal(const vector<TLorentzVector> Jets,
                    const vector<TLorentzVector> Leptons) {
  double deltaR_init = 10;
  double min_deltar = 10;
  double min_deltaR = 10;
  for (UInt_t j = 0; j < Jets.size(); ++j) {
    for (UInt_t k = 0; k < Leptons.size(); ++k) {
      deltaR_init = Jets[j].DeltaR(Leptons[k]);
      if (min_deltar > deltaR_init)
        min_deltar = deltaR_init;
    }
    if (min_deltar < min_deltaR)
      min_deltaR = min_deltar;
  }
  return min_deltaR;
}
double MinDeltaRSingleCal(const vector<TLorentzVector> Jets) {
  double min = 10;
  double min_2 = 10;
  double min_3 = 10;
  double min_1 = 10;
  for (UInt_t j = 0; j < Jets.size(); ++j) {
    for (UInt_t k = j + 1; k < Jets.size(); ++k) {
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

/*double AplanarityCalcullator(vector<TLorentzVector> SelectedJets){
        double PtSquare = 0;
        double PtPt = -1;
         for (UInt_t j = 0; j < SelectedJets.size(); ++j){
                PtSquare = PtSquare+SelcctedJets.Pt()*SelectedJets.Pt();

        for (UInt_t k = j+1; k < SelectedJets.size(); ++j){

                }

         }
}	*/

double LeadingJetPtCal(vector<TLorentzVector> SelectedJets) { /*{{{*/
  double Initial = -1; // assuming Pt all positive
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    UInt_t k = j + 1;
    if (SelectedJets[k].Pt() > Initial)
      Initial = SelectedJets[k].Pt();
  }
  return Initial;
} /*}}}*/

// double deltaRJetsCal(vector<TLorentzVector> SelectedJets){/*{{{*/
// double init = 0;
// double init2 = 0;
// double deltaR = 0;
//    double Eta = 0;
//    double Eta2 = 0;
//    double Phi = 0;
//    double Phi2 = 0;
//    for (UInt_t j = 0; j < SelectedJets.size(); ++j){
//        for(UInt_t k = j+1; k< SelectedJets.size();++k){
//            Eta = SelectedJets[j].Eta();
//            Eta2 = SelectedJets[k].Eta();
//            Phi = SelectedJets[j].Phi();
//            Phi2 = SelectedJets[k].Phi();
//            deltaR = DeltaR(Eta,Eta2,Phi,Phi2);
//            if(deltaR > init) init = deltaR;
//        }
//        if (init>init2) init2 = init;
//    }
//    return init2;
//}/*}}}*/

void MinMaxdeltaRJetsCal(vector<TLorentzVector> SelectedJets,
                         vector<double> &MinMaxDeltaR) { /*{{{*/
  double init = 0;
  double init2 = 0;
  double initMin1 = 1000000;
  double initMin2 = 1000000;
  double deltaR = 0;
  double Eta = 0;
  double Eta2 = 0;
  double Phi = 0;
  double Phi2 = 0;
  if (SelectedJets.size() > 1) {
    for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
      Eta = SelectedJets[j].Eta();
      Phi = SelectedJets[j].Phi();
      for (UInt_t k = j + 1; k < SelectedJets.size(); ++k) {
        Eta2 = SelectedJets[k].Eta();
        Phi2 = SelectedJets[k].Phi();
        deltaR = DeltaR(Eta, Eta2, Phi, Phi2);
        if (deltaR > init)
          init = deltaR;
        if (deltaR < initMin1)
          initMin1 = deltaR;
      }
      if (init > init2)
        init2 = init;
      if (initMin1 < initMin2)
        initMin2 = initMin1;
    }
  } else {
    initMin2 = -1; // means have less than 2 jets
    init2 = -1;
  }
  MinMaxDeltaR.push_back(initMin2); // cout<<initMin2<<"  ";
  MinMaxDeltaR.push_back(init2);
  // cout<<MinMaxDeltaR[0];
} /*}}}*/

double AverageDeltaRCal(const vector<TLorentzVector> SelectedJets) {
  double eta_1;
  double phi_1;
  double eta_2;
  double phi_2;
  double sum_delta_R = 0.0;
  const Int_t num = SelectedJets.size();
  for (UInt_t j = 0; j < SelectedJets.size(); ++j) {
    eta_1 = SelectedJets[j].Eta();
    phi_1 = SelectedJets[j].Phi();
    for (UInt_t k = 0; k < SelectedJets.size(); ++k) {
      if (k != j) {
        eta_2 = SelectedJets[k].Eta();
        phi_2 = SelectedJets[k].Phi();
        sum_delta_R = sum_delta_R + DeltaR(eta_1, eta_2, phi_1, phi_2);
      }
    }
  }
  sum_delta_R = sum_delta_R / ((num - 1) * num);
  return sum_delta_R;
}

void sort_jetPt(const vector<TLorentzVector> SelectedJets,
                vector<double> &JetsPtSorted) { /*{{{*/
  UInt_t size = 0;
  size = SelectedJets.size();
  int k = 0;
  double JetsPt[size];
  for (UInt_t j = 0; j < size; ++j) {
    JetsPt[j] = SelectedJets[j].Pt();
  }
  sort(JetsPt, JetsPt + size); // Sorts the elements in the range [first,last)
                               // into ascending order.
  for (UInt_t i = 0; i < size; ++i) {
    k = size - i - 1;                  //-1 because starts with 0
    JetsPtSorted.push_back(JetsPt[k]); // std::reverse
  }
} /*}}}*/
/*
void AddTwoVectors(const vector<TLorentzVector> SelectedMuonsT, const
vector<TLorentzVector> SelectedElectronsMVAT, vector<TLorentzVector> &
SelectedLeptonsMVAT){
    SelectedLeptonsMVAT = SeletedMuonsT;
    for(auto ele = SelectedElectronsMVAT.begin(), ele !=
SelectedElectronsMVAT.end(), ++ele){
        SelectedLeptonsMVAT.push_back(ele);
    }
}
*/

// bool compEle(const edm::Ptr<flashgg::Electron>& a, const
// edm::Ptr<flashgg::Electron>& b)
bool compEle(const TLorentzVector a, const TLorentzVector b) {
  return a.Pt() > b.Pt();
}

//?no correct
void FindLeadingToThirdPtIndex(const vector<TLorentzVector> SelectedJets,
                               const vector<double> JetsPtSorted,
                               Int_t &LeadingPtIndex, Int_t &SecondPtIndex,
                               Int_t &ThirdPtIndex) {
  Int_t size = SelectedJets.size();
  double leading_pt = -99;
  double second_pt = -99;
  double third_pt = -99;
  if (size > 0)
    leading_pt = JetsPtSorted[0];
  if (size > 1)
    second_pt = JetsPtSorted[1];
  if (size > 2)
    third_pt = JetsPtSorted[2];
  for (Int_t j = 0; j < size; ++j) {
    if (SelectedJets[j].Pt() == leading_pt)
      LeadingPtIndex = j;
    if (SelectedJets[j].Pt() == second_pt)
      SecondPtIndex = j;
    if (SelectedJets[j].Pt() == third_pt)
      ThirdPtIndex = j;
  }
}

double BScoreAllJetsCal(const vector<double> SelectedJetsBTags) {
  double initB = 0;
  for (UInt_t j = 0; j < SelectedJetsBTags.size(); ++j) {
    initB = initB + SelectedJetsBTags[j];
  }
  return initB;
}


double bscoreSumOf4largestCal(const vector<double> SelectedJetsBTags) {
    vector<double> jetsBtags = SelectedJetsBTags;
    sort(jetsBtags.begin(),jetsBtags.end());
    reverse(jetsBtags.begin(),jetsBtags.end());
    double sum = -99;
    if(SelectedJetsBTags.size()>3) {
        sum = jetsBtags[0]+jetsBtags[1]+jetsBtags[2]+jetsBtags[3];
    }
    else{
        sum =  -99;
    }
    return sum;
}
// it seems that fileName doesn't occur in the function .
void branch(bool data, int selection, TTree *NewTree,
            TTree *NewTreeSB, TChain& chain) { /*{{{*/
  // Change branch address, dealing with clone trees properly.	//copy the
  // branch Jet_pt to b_Jet_pt
  chain.SetBranchAddress("Jet_pt", &Jet_pt_, &b_Jet_pt);
  chain.SetBranchAddress("Jet_eta", &Jet_eta_, &b_Jet_eta);
  chain.SetBranchAddress("Jet_phi", &Jet_phi_, &b_Jet_phi);
  chain.SetBranchAddress("Jet_mass", &Jet_mass_, &b_Jet_mass);
  chain.SetBranchAddress("Jet_JesSF", &Jet_JesSF_, &b_Jet_JesSF);
  chain.SetBranchAddress("Jet_JesSFup", &Jet_JesSFup_, &b_Jet_JesSFup);
  chain.SetBranchAddress("Jet_JesSFdown", &Jet_JesSFdown_, &b_Jet_JesSFdown);
  chain.SetBranchAddress("Jet_JerSF", &Jet_JerSF_, &b_Jet_JerSF);
  chain.SetBranchAddress("Jet_JerSFup", &Jet_JerSFup_, &b_Jet_JerSFup);
  chain.SetBranchAddress("Jet_JerSFdown", &Jet_JerSFdown_, &b_Jet_JerSFdown);
  chain.SetBranchAddress("Jet_Uncorr_pt", &Jet_Uncorr_pt_, &b_Jet_Uncorr_pt);
  chain.SetBranchAddress("Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags",
                         &Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags_,
                         &b_Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags);
  chain.SetBranchAddress("Jet_pfDeepCSVBJetTags", &Jet_pfDeepCSVBJetTags_,
                         &b_Jet_pfDeepCSVBJetTags);
  chain.SetBranchAddress("Jet_pfDeepFlavourBJetTags",
                         &Jet_pfDeepFlavourBJetTags_,
                         &b_Jet_pfDeepFlavourBJetTags);
  chain.SetBranchAddress("Jet_neutralHadEnergyFraction",
                         &Jet_neutralHadEnergyFraction_,
                         &b_Jet_neutralHadEnergyFraction);
  chain.SetBranchAddress("Jet_chargedEmEnergyFraction",
                         &Jet_chargedEmEnergyFraction_,
                         &b_Jet_chargedEmEnergyFraction);
  chain.SetBranchAddress("Jet_neutralEmEnergyFraction",
                         &Jet_neutralEmEnergyFraction_,
                         &b_Jet_neutralEmEnergyFraction);
  chain.SetBranchAddress("Jet_numberOfConstituents", &Jet_numberOfConstituents_,
                         &b_Jet_numberOfConstituents);
  chain.SetBranchAddress("Jet_chargedHadronEnergyFraction",
                         &Jet_chargedHadronEnergyFraction_,
                         &b_Jet_chargedHadronEnergyFraction);
  chain.SetBranchAddress("Jet_chargedMultiplicity", &Jet_chargedMultiplicity_,
                         &b_Jet_chargedMultiplicity);
  if (!data)
    chain.SetBranchAddress("Jet_hadronFlavour", &Jet_hadronFlavour_,
                           &b_Jet_hadronFlavour);
  chain.SetBranchAddress("Jet_muonEnergyFraction", &Jet_muonEnergyFraction_,
                         &b_Jet_muonEnergyFraction);
  /*
    chain.SetBranchAddress("BoostedJet_pt",   &BoostedJet_pt_,
    &b_BoostedJet_pt);
    chain.SetBranchAddress("BoostedJet_Uncorr_pt",   &BoostedJet_Uncorr_pt_,
    &b_BoostedJet_Uncorr_pt);
    chain.SetBranchAddress("BoostedJet_softdrop_mass",
    &BoostedJet_softdrop_mass_,   &b_BoostedJet_softdrop_mass);
    chain.SetBranchAddress("BoostedJet_puppi_softdrop_mass",
    &BoostedJet_puppi_softdrop_mass_,   &b_BoostedJet_puppi_softdrop_mass);
    chain.SetBranchAddress("BoostedJet_JesSF",&BoostedJet_JesSF_,&b_BoostedJet_JesSF);
    chain.SetBranchAddress("BoostedJet_JesSFup",&BoostedJet_JesSFup_,&b_BoostedJet_JesSFup);
    chain.SetBranchAddress("BoostedJet_JesSFdown",&BoostedJet_JesSFdown_,&b_BoostedJet_JesSFdown);
    chain.SetBranchAddress("BoostedJet_JerSF",&BoostedJet_JerSF_,&b_BoostedJet_JerSF);
    chain.SetBranchAddress("BoostedJet_JerSFup",&BoostedJet_JerSFup_,&b_BoostedJet_JerSFup);
    chain.SetBranchAddress("BoostedJet_JerSFdown",&BoostedJet_JerSFdown_,&b_BoostedJet_JerSFdown);
    chain.SetBranchAddress("BoostedJet_eta",  &BoostedJet_eta_,
    &b_BoostedJet_eta);
    chain.SetBranchAddress("BoostedJet_phi",  &BoostedJet_phi_,
    &b_BoostedJet_phi);
    chain.SetBranchAddress("BoostedJet_mass", &BoostedJet_mass_,
    &b_BoostedJet_mass);
    chain.SetBranchAddress("BoostedJet_neutralHadEnergyFraction",
    &BoostedJet_neutralHadEnergyFraction_,
    &b_BoostedJet_neutralHadEnergyFraction);
    chain.SetBranchAddress("BoostedJet_neutralEmEnergyFraction",
    &BoostedJet_neutralEmEnergyFraction_,
    &b_BoostedJet_neutralEmEnergyFraction);
    chain.SetBranchAddress("BoostedJet_chargedEmEnergyFraction",
    &BoostedJet_chargedEmEnergyFraction_,
    &b_BoostedJet_chargedEmEnergyFraction);
    chain.SetBranchAddress("BoostedJet_numberOfConstituents",
    &BoostedJet_numberOfConstituents_, &b_BoostedJet_numberOfConstituents);
    chain.SetBranchAddress("BoostedJet_chargedHadronEnergyFraction",
    &BoostedJet_chargedHadronEnergyFraction_,
    &b_BoostedJet_chargedHadronEnergyFraction);
    chain.SetBranchAddress("BoostedJet_chargedMultiplicity",
    &BoostedJet_chargedMultiplicity_, &b_BoostedJet_chargedMultiplicity);
    chain.SetBranchAddress("BoostedJet_puppi_tau1",
    &BoostedJet_puppi_tau1_,         &b_BoostedJet_puppi_tau1);
    chain.SetBranchAddress("BoostedJet_puppi_tau2",
    &BoostedJet_puppi_tau2_,         &b_BoostedJet_puppi_tau2);
    chain.SetBranchAddress("BoostedJet_puppi_tau3",
    &BoostedJet_puppi_tau3_,         &b_BoostedJet_puppi_tau3);
    chain.SetBranchAddress("BoostedJet_tau1",         &BoostedJet_tau1_,
    &b_BoostedJet_tau1);
    chain.SetBranchAddress("BoostedJet_tau2",         &BoostedJet_tau2_,
    &b_BoostedJet_tau2);
    chain.SetBranchAddress("BoostedJet_tau3",         &BoostedJet_tau3_,
    &b_BoostedJet_tau3);
    chain.SetBranchAddress("BoostedJet_pruned_mass",  &BoostedJet_pruned_mass_,
    &b_BoostedJet_pruned_mass);
    */
  chain.SetBranchAddress("patElectron_pt", &patElectron_pt_, &b_patElectron_pt);
  chain.SetBranchAddress("patElectron_eta", &patElectron_eta_,
                         &b_patElectron_eta);
  chain.SetBranchAddress("patElectron_phi", &patElectron_phi_,
                         &b_patElectron_phi);
  chain.SetBranchAddress("patElectron_energy", &patElectron_energy_,
                         &b_patElectron_energy);
  chain.SetBranchAddress("patElectron_SCeta", &patElectron_SCeta_,
                         &b_patElectron_SCeta);
  chain.SetBranchAddress("patElectron_charge", &patElectron_charge_,
                         &b_patElectron_charge);
  chain.SetBranchAddress("patElectron_Et", &patElectron_Et_, &b_patElectron_Et);
  chain.SetBranchAddress("patElectron_pdgId", &patElectron_pdgId_,
                         &b_patElectron_pdgId);
  chain.SetBranchAddress("patElectron_relIsoDeltaBeta",
                         &patElectron_relIsoDeltaBeta_,
                         &b_patElectron_relIsoDeltaBeta);
  chain.SetBranchAddress("patElectron_relIsoRhoEA_Update",
                         &patElectron_relIsoRhoEA_Update_,
                         &b_patElectron_relIsoRhoEA_Update);
  if (!data)
    chain.SetBranchAddress("patElectron_gen_pdgId", &patElectron_gen_pdgId_,
                           &b_patElectron_gen_pdgId);
  if (!data)
    chain.SetBranchAddress(
        "patElectron_gen_isDirectPromptTauDecayProductFinalState",
        &patElectron_gen_isDirectPromptTauDecayProductFinalState_,
        &b_patElectron_gen_isDirectPromptTauDecayProductFinalState);
  //  chain.SetBranchAddress("",&_,&b_);
  chain.SetBranchAddress("patElectron_mvaEleID_Fall17_noIso_V2_wp80",
                         &patElectron_mvaEleID_Fall17_noIso_V2_wp80_,
                         &b_patElectron_mvaEleID_Fall17_noIso_V2_wp80);
  chain.SetBranchAddress("patElectron_mvaEleID_Fall17_iso_V2_wp80",
                         &patElectron_mvaEleID_Fall17_iso_V2_wp80_,
                         &b_patElectron_mvaEleID_Fall17_iso_V2_wp80);
  chain.SetBranchAddress("patElectron_mvaEleID_Fall17_iso_V2_wp90",
                         &patElectron_mvaEleID_Fall17_iso_V2_wp90_,
                         &b_patElectron_mvaEleID_Fall17_iso_V2_wp90);
  chain.SetBranchAddress("patElectron_mvaEleID_Fall17_noIso_V2_wp90",
                         &patElectron_mvaEleID_Fall17_noIso_V2_wp90_,
                         &b_patElectron_mvaEleID_Fall17_noIso_V2_wp90);
  chain.SetBranchAddress("patElectron_mvaEleID_Fall17_iso_V2_wpLoose",
                         &patElectron_mvaEleID_Fall17_iso_V2_wpLoose_,
                         &b_patElectron_mvaEleID_Fall17_iso_V2_wpLoose);
  chain.SetBranchAddress("patElectron_mvaEleID_Fall17_noIso_V2_wpLoose",
                         &patElectron_mvaEleID_Fall17_noIso_V2_wpLoose_,
                         &b_patElectron_mvaEleID_Fall17_noIso_V2_wpLoose);
  chain.SetBranchAddress(
      "patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Values",
      &patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Values_,
      &b_patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Values);
  chain.SetBranchAddress(
      "patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Categories",
      &patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Categories_,
      &b_patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Categories);
  chain.SetBranchAddress(
      "patElectron_ElectronMVAEstimatorRun2Fall17IsoV2Values",
      &patElectron_ElectronMVAEstimatorRun2Fall17IsoV2Values_,
      &b_patElectron_ElectronMVAEstimatorRun2Fall17IsoV2Values);
  chain.SetBranchAddress(
      "patElectron_ElectronMVAEstimatorRun2Fall17IsoV2Categories",
      &patElectron_ElectronMVAEstimatorRun2Fall17IsoV2Categories_,
      &b_patElectron_ElectronMVAEstimatorRun2Fall17IsoV2Categories);
  chain.SetBranchAddress(
      "patElectron_mvaEleID_Spring16_GeneralPurpose_V1_wp80",
      &patElectron_mvaEleID_Spring16_GeneralPurpose_V1_wp80_,
      &b_patElectron_mvaEleID_Spring16_GeneralPurpose_V1_wp80);
  chain.SetBranchAddress(
      "patElectron_mvaEleID_Spring16_GeneralPurpose_V1_wp90",
      &patElectron_mvaEleID_Spring16_GeneralPurpose_V1_wp90_,
      &b_patElectron_mvaEleID_Spring16_GeneralPurpose_V1_wp90);
  chain.SetBranchAddress(
      "patElectron_MVAValue_ElectronMVAEstimatorRun2Spring16GeneralPurposeV1",
      &patElectron_MVAValue_ElectronMVAEstimatorRun2Spring16GeneralPurposeV1_,
      &b_patElectron_MVAValue_ElectronMVAEstimatorRun2Spring16GeneralPurposeV1);
  chain.SetBranchAddress("patElectron_cutBasedElectronID_Fall17_94X_V2_loose",
                         &patElectron_cutBasedElectronID_Fall17_94X_V2_loose_,
                         &b_patElectron_cutBasedElectronID_Fall17_94X_V2_loose);
  chain.SetBranchAddress(
      "patElectron_cutBasedElectronID_Fall17_94X_V2_medium",
      &patElectron_cutBasedElectronID_Fall17_94X_V2_medium_,
      &b_patElectron_cutBasedElectronID_Fall17_94X_V2_medium);
  chain.SetBranchAddress("patElectron_cutBasedElectronID_Fall17_94X_V2_tight",
                         &patElectron_cutBasedElectronID_Fall17_94X_V2_tight_,
                         &b_patElectron_cutBasedElectronID_Fall17_94X_V2_tight);
  chain.SetBranchAddress("patElectron_cutBasedElectronID_Fall17_94X_V2_veto",
                         &patElectron_cutBasedElectronID_Fall17_94X_V2_veto_,
                         &b_patElectron_cutBasedElectronID_Fall17_94X_V2_veto);
  chain.SetBranchAddress("patElectron_heepElectronID_HEEPV70",
                         &patElectron_heepElectronID_HEEPV70_,
                         &b_patElectron_heepElectronID_HEEPV70);
  // chain.SetBranchAddress("",&_,&b_);
  /* chain.SetBranchAddress("patElectron_isPassVeto",&patElectron_isPassVeto_,&b_patElectron_isPassVeto);
   chain.SetBranchAddress("patElectron_isPassLoose",&patElectron_isPassLoose_,&b_patElectron_isPassLoose);
   chain.SetBranchAddress("patElectron_isPassMedium",&patElectron_isPassMedium_,&b_patElectron_isPassMedium);
   chain.SetBranchAddress("patElectron_isPassTight",&patElectron_isPassTight_,&b_patElectron_isPassTight);
   chain.SetBranchAddress("patElectron_isPassHEEPId",&patElectron_isPassHEEPId_,&b_patElectron_isPassHEEPId);*/
  chain.SetBranchAddress("patElectron_passConversionVeto",
                         &patElectron_passConversionVeto_,
                         &b_patElectron_passConversionVeto);
  chain.SetBranchAddress("patElectron_inCrack", &patElectron_inCrack_,
                         &b_patElectron_inCrack);
  chain.SetBranchAddress("patElectron_isMatchedToTrigger",
                         &patElectron_isMatchedToTrigger_,
                         &b_patElectron_isMatchedToTrigger);

  chain.SetBranchAddress("patElectron_miniIsoRel", &patElectron_miniIsoRel_,
                         &b_patElectron_miniIsoRel);
  chain.SetBranchAddress("patElectron_jetptratio", &patElectron_jetptratio_,
                         &b_patElectron_jetptratio);
  chain.SetBranchAddress("patElectron_ptrel", &patElectron_ptrel_,
                         &b_patElectron_ptrel);
  chain.SetBranchAddress("patElectron_d0", &patElectron_d0_, &b_patElectron_d0);
  chain.SetBranchAddress("patElectron_gsfTrack_dz_pv",
                         &patElectron_gsfTrack_dz_pv_,
                         &b_patElectron_gsfTrack_dz_pv);
  chain.SetBranchAddress("patElectron_IP3D_sig", &patElectron_IP3D_sig_,
                         &b_patElectron_IP3D_sig);
  //  chain.SetBranchAddress("",&_,&b_);

  chain.SetBranchAddress("Muon_pt", &Muon_pt_, &b_Muon_pt);
  chain.SetBranchAddress("Muon_eta", &Muon_eta_, &b_Muon_eta);
  chain.SetBranchAddress("Muon_phi", &Muon_phi_, &b_Muon_phi);
  chain.SetBranchAddress("Muon_energy", &Muon_energy_, &b_Muon_energy);
  chain.SetBranchAddress("Muon_charge", &Muon_charge_, &b_Muon_charge);
  chain.SetBranchAddress("Muon_tight", &Muon_tight_, &b_Muon_tight);
  chain.SetBranchAddress("Muon_medium", &Muon_medium_, &b_Muon_medium);
  chain.SetBranchAddress("Muon_loose", &Muon_loose_, &b_Muon_loose);
  chain.SetBranchAddress("Met_type1PF_pt", &Met_type1PF_pt_, &b_Met_type1PF_pt);
  chain.SetBranchAddress("Met_type1PF_phi", &Met_type1PF_phi_,
                         &b_Met_type1PF_phi);
  chain.SetBranchAddress("Met_type1PF_sumEt", &Met_type1PF_sumEt_,
                         &b_Met_type1PF_sumEt);
  chain.SetBranchAddress("Muon_relIsoDeltaBetaR04", &Muon_relIsoDeltaBetaR04_,
                         &b_Muon_relIsoDeltaBetaR04);
  chain.SetBranchAddress("Muon_miniIsoRel", &Muon_miniIsoRel_,
                         &b_Muon_miniIsoRel);
  chain.SetBranchAddress("Muon_ptrel", &Muon_ptrel_, &b_Muon_ptrel);
  chain.SetBranchAddress("Muon_jetptratio", &Muon_jetptratio_,
                         &b_Muon_jetptratio);
  chain.SetBranchAddress("Muon_jetptratioV2", &Muon_jetptratioV2_,
                         &b_Muon_jetptratioV2);
  chain.SetBranchAddress("Muon_isMatchedToTrigger", &Muon_isMatchedToTrigger_,
                         &b_Muon_isMatchedToTrigger);
  chain.SetBranchAddress("Muon_dz_pv", &Muon_dz_pv_, &b_Muon_dz_pv);
  chain.SetBranchAddress("Muon_dz_bt", &Muon_dz_bt_, &b_Muon_dz_bt);
  chain.SetBranchAddress("Muon_IP3D_sig", &Muon_IP3D_sig_, &b_Muon_IP3D_sig);
  chain.SetBranchAddress("Muon_dxy_pv", &Muon_dxy_pv_, &b_Muon_dxy_pv);
  chain.SetBranchAddress("Muon_dxy_bt", &Muon_dxy_bt_, &b_Muon_dxy_bt);

  chain.SetBranchAddress("TopTagger_type", &TopTagger_type_, &b_TopTagger_type);
  chain.SetBranchAddress("TopTagger_discriminator", &TopTagger_discriminator_,
                         &b_TopTagger_discriminator);
  chain.SetBranchAddress("TopTagger_jet1Idx", &TopTagger_jet1Idx_,
                         &b_TopTagger_jet1Idx);
  chain.SetBranchAddress("TopTagger_jet2Idx", &TopTagger_jet2Idx_,
                         &b_TopTagger_jet2Idx);
  chain.SetBranchAddress("TopTagger_jet3Idx", &TopTagger_jet3Idx_,
                         &b_TopTagger_jet3Idx);

  chain.SetBranchAddress("Tau_pt", &Tau_pt_, &b_Tau_pt);
  chain.SetBranchAddress("Tau_eta", &Tau_eta_, &b_Tau_eta);
  chain.SetBranchAddress("Tau_leadChargedCandDz_pv", &Tau_leadChargedCandDz_pv_,
                         &b_Tau_leadChargedCandDz_pv);
  chain.SetBranchAddress("Tau_packedLeadTauCand_dz", &Tau_packedLeadTauCand_dz_,
                         &b_Tau_packedLeadTauCand_dz);
  chain.SetBranchAddress("Tau_phi", &Tau_phi_, &b_Tau_phi);
  chain.SetBranchAddress("Tau_energy", &Tau_energy_, &b_Tau_energy);
  chain.SetBranchAddress("Tau_px", &Tau_px_, &b_Tau_px);
  chain.SetBranchAddress("Tau_py", &Tau_py_, &b_Tau_py);
  chain.SetBranchAddress("Tau_pz", &Tau_pz_, &b_Tau_pz);
  chain.SetBranchAddress("Tau_p", &Tau_p_, &b_Tau_p);
  /*  chain.SetBranchAddress("Tau_leadChargedCandPt",&Tau_leadChargedCandPt_,&b_Tau_leadChargedCandPt);
    chain.SetBranchAddress("Tau_leadChargedCandEta",&Tau_leadChargedCandEta_,&b_Tau_leadChargedCandEta);
    chain.SetBranchAddress("Tau_leadChargedCandPhi",&Tau_leadChargedCandPhi_,&b_Tau_leadChargedCandPhi);
    chain.SetBranchAddress("Tau_leadChargedCandE",&Tau_leadChargedCandE_,&b_Tau_leadChargedCandE);*/
  chain.SetBranchAddress("Tau_charge", &Tau_charge_, &b_Tau_charge);
  chain.SetBranchAddress("Tau_decayModeFinding", &Tau_decayModeFinding_,
                         &b_Tau_decayModeFinding);
  chain.SetBranchAddress("Tau_decayModeFindingNewDMs",
                         &Tau_decayModeFindingNewDMs_,
                         &b_Tau_decayModeFindingNewDMs);
  chain.SetBranchAddress("Tau_decayMode", &Tau_decayMode_, &b_Tau_decayMode);
  chain.SetBranchAddress("Tau_againstMuonLoose3", &Tau_againstMuonLoose3_,
                         &b_Tau_againstMuonLoose3);
  chain.SetBranchAddress("Tau_againstMuonTight3", &Tau_againstMuonTight3_,
                         &b_Tau_againstMuonTight3);
  /*  chain.SetBranchAddress("Tau_againstElectronVLooseMVA6",&Tau_againstElectronVLooseMVA6_,&b_Tau_againstElectronVLooseMVA6);
    chain.SetBranchAddress("Tau_againstElectronLooseMVA6",&Tau_againstElectronLooseMVA6_,&b_Tau_againstElectronLooseMVA6);
    chain.SetBranchAddress("Tau_againstElectronMediumMVA6",&Tau_againstElectronMediumMVA6_,&b_Tau_againstElectronMediumMVA6);
    chain.SetBranchAddress("Tau_againstElectronTightMVA6",&Tau_againstElectronTightMVA6_,&b_Tau_againstElectronTightMVA6);
    chain.SetBranchAddress("Tau_chargedIsoPtSum",&Tau_chargedIsoPtSum_,&b_Tau_chargedIsoPtSum);
    chain.SetBranchAddress("Tau_neutralIsoPtSum",&Tau_neutralIsoPtSum_,&b_Tau_neutralIsoPtSum);
    chain.SetBranchAddress("Tau_puCorrPtSum",&Tau_puCorrPtSum_,&b_Tau_puCorrPtSum);*/
  /*  chain.SetBranchAddress("Tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT",&Tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_,&b_Tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT);
    chain.SetBranchAddress("Tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&Tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT_,&b_Tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
    chain.SetBranchAddress("Tau_byIsolationMVArun2017v2DBoldDMdR0p3wLTraw2017",&Tau_byIsolationMVArun2017v2DBoldDMdR0p3wLTraw2017_,&b_Tau_byIsolationMVArun2017v2DBoldDMdR0p3wLTraw2017);
    chain.SetBranchAddress("Tau_byVVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017",&Tau_byVVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_,&b_Tau_byVVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017);
    chain.SetBranchAddress("Tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017",&Tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_,&b_Tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017);*/
  chain.SetBranchAddress("Tau_byDeepTau2017v2p1VSjetraw",
                         &Tau_byDeepTau2017v2p1VSjetraw_,
                         &b_Tau_byDeepTau2017v2p1VSjetraw);
  chain.SetBranchAddress("Tau_byVVVLooseDeepTau2017v2p1VSjet",
                         &Tau_byVVVLooseDeepTau2017v2p1VSjet_,
                         &b_Tau_byVVVLooseDeepTau2017v2p1VSjet);
  chain.SetBranchAddress("Tau_byVVLooseDeepTau2017v2p1VSjet",
                         &Tau_byVVLooseDeepTau2017v2p1VSjet_,
                         &b_Tau_byVVLooseDeepTau2017v2p1VSjet);
  chain.SetBranchAddress("Tau_byVLooseDeepTau2017v2p1VSjet",
                         &Tau_byVLooseDeepTau2017v2p1VSjet_,
                         &b_Tau_byVLooseDeepTau2017v2p1VSjet);
  chain.SetBranchAddress("Tau_byLooseDeepTau2017v2p1VSjet",
                         &Tau_byLooseDeepTau2017v2p1VSjet_,
                         &b_Tau_byLooseDeepTau2017v2p1VSjet);
  chain.SetBranchAddress("Tau_byMediumDeepTau2017v2p1VSjet",
                         &Tau_byMediumDeepTau2017v2p1VSjet_,
                         &b_Tau_byMediumDeepTau2017v2p1VSjet);
  chain.SetBranchAddress("Tau_byTightDeepTau2017v2p1VSjet",
                         &Tau_byTightDeepTau2017v2p1VSjet_,
                         &b_Tau_byTightDeepTau2017v2p1VSjet);
  chain.SetBranchAddress("Tau_byVTightDeepTau2017v2p1VSjet",
                         &Tau_byVTightDeepTau2017v2p1VSjet_,
                         &b_Tau_byVTightDeepTau2017v2p1VSjet);
  chain.SetBranchAddress("Tau_byVVTightDeepTau2017v2p1VSjet",
                         &Tau_byVVTightDeepTau2017v2p1VSjet_,
                         &b_Tau_byVVTightDeepTau2017v2p1VSjet);
  chain.SetBranchAddress("Tau_byDeepTau2017v2p1VSmuraw",
                         &Tau_byDeepTau2017v2p1VSmuraw_,
                         &b_Tau_byDeepTau2017v2p1VSmuraw);
  chain.SetBranchAddress("Tau_byVLooseDeepTau2017v2p1VSmu",
                         &Tau_byVLooseDeepTau2017v2p1VSmu_,
                         &b_Tau_byVLooseDeepTau2017v2p1VSmu);
  chain.SetBranchAddress("Tau_byLooseDeepTau2017v2p1VSmu",
                         &Tau_byLooseDeepTau2017v2p1VSmu_,
                         &b_Tau_byLooseDeepTau2017v2p1VSmu);
  chain.SetBranchAddress("Tau_byMediumDeepTau2017v2p1VSmu",
                         &Tau_byMediumDeepTau2017v2p1VSmu_,
                         &b_Tau_byMediumDeepTau2017v2p1VSmu);
  chain.SetBranchAddress("Tau_byTightDeepTau2017v2p1VSmu",
                         &Tau_byTightDeepTau2017v2p1VSmu_,
                         &b_Tau_byTightDeepTau2017v2p1VSmu);
  chain.SetBranchAddress("Tau_byDeepTau2017v2p1VSeraw",
                         &Tau_byDeepTau2017v2p1VSeraw_,
                         &b_Tau_byDeepTau2017v2p1VSeraw);
  chain.SetBranchAddress("Tau_byVVVLooseDeepTau2017v2p1VSe",
                         &Tau_byVVVLooseDeepTau2017v2p1VSe_,
                         &b_Tau_byVVVLooseDeepTau2017v2p1VSe);
  chain.SetBranchAddress("Tau_byVVLooseDeepTau2017v2p1VSe",
                         &Tau_byVVLooseDeepTau2017v2p1VSe_,
                         &b_Tau_byVVLooseDeepTau2017v2p1VSe);
  chain.SetBranchAddress("Tau_byVLooseDeepTau2017v2p1VSe",
                         &Tau_byVLooseDeepTau2017v2p1VSe_,
                         &b_Tau_byVLooseDeepTau2017v2p1VSe);
  chain.SetBranchAddress("Tau_byLooseDeepTau2017v2p1VSe",
                         &Tau_byLooseDeepTau2017v2p1VSe_,
                         &b_Tau_byLooseDeepTau2017v2p1VSe);
  chain.SetBranchAddress("Tau_byMediumDeepTau2017v2p1VSe",
                         &Tau_byMediumDeepTau2017v2p1VSe_,
                         &b_Tau_byMediumDeepTau2017v2p1VSe);
  chain.SetBranchAddress("Tau_byTightDeepTau2017v2p1VSe",
                         &Tau_byTightDeepTau2017v2p1VSe_,
                         &b_Tau_byTightDeepTau2017v2p1VSe);
  chain.SetBranchAddress("Tau_byVTightDeepTau2017v2p1VSe",
                         &Tau_byVTightDeepTau2017v2p1VSe_,
                         &b_Tau_byVTightDeepTau2017v2p1VSe);
  chain.SetBranchAddress("Tau_byVVTightDeepTau2017v2p1VSe",
                         &Tau_byVVTightDeepTau2017v2p1VSe_,
                         &b_Tau_byVVTightDeepTau2017v2p1VSe);
  //  chain.SetBranchAddress("",&_,&b_);

  chain.SetBranchAddress("Flag_goodVertices", &Flag_goodVertices_,
                         &b_Flag_goodVertices);
  chain.SetBranchAddress("Flag_globalSuperTightHalo2016Filter",
                         &Flag_globalSuperTightHalo2016Filter_,
                         &b_Flag_globalSuperTightHalo2016Filter);
  // chain.SetBranchAddress("Flag_CSCTightHalo2015Filter",&Flag_CSCTightHalo2015Filter_,&b_Flag_CSCTightHalo2015Filter);
  chain.SetBranchAddress("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter_,
                         &b_Flag_HBHENoiseFilter);
  chain.SetBranchAddress("Flag_HBHENoiseIsoFilter", &Flag_HBHENoiseIsoFilter_,
                         &b_Flag_HBHENoiseIsoFilter);
  chain.SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter",
                         &Flag_EcalDeadCellTriggerPrimitiveFilter_,
                         &b_Flag_EcalDeadCellTriggerPrimitiveFilter);
  chain.SetBranchAddress("Flag_BadPFMuonFilter", &Flag_BadPFMuonFilter_,
                         &b_Flag_BadPFMuonFilter);
  chain.SetBranchAddress("Flag_BadChargedCandidateFilter",
                         &Flag_BadChargedCandidateFilter_,
                         &b_Flag_BadChargedCandidateFilter);
  //  chain.SetBranchAddress("Flag_ecalBadCalibReducedMINIAODFilter",&Flag_ecalBadCalibReducedMINIAODFilter_,&b_Flag_ecalBadCalibReducedMINIAODFilter);
  chain.SetBranchAddress("Flag_eeBadScFilter", &Flag_eeBadScFilter_,
                         &b_Flag_eeBadScFilter);
  chain.SetBranchAddress("Flag_METFilters", &Flag_METFilters_,
                         &b_Flag_METFilters);

  chain.SetBranchAddress("HLT_DoubleEle33_CaloIdL_MW",
                         &HLT_DoubleEle33_CaloIdL_MW_,
                         &b_HLT_DoubleEle33_CaloIdL_MW);
  chain.SetBranchAddress("HLT_Mu50", &HLT_Mu50_, &b_HLT_Mu50);
  //
  //                                 add.
  chain.SetBranchAddress("HLT_PFHT900", &HLT_PFHT900_, &b_HLT_PFHT900);
  chain.SetBranchAddress("HLT_PFHT450_SixJet40_BTagCSV_p056", &HLT_PFHT450_SixJet40_BTagCSV_p056_, &b_HLT_PFHT450_SixJet40_BTagCSV_p056);
  chain.SetBranchAddress("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056", &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_,&b_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056);
  chain.SetBranchAddress("HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg", &HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_, &b_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg);
  chain.SetBranchAddress("HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg", &HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_, &b_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg);
  chain.SetBranchAddress("HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg", &HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_, &b_HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg);
  chain.SetBranchAddress("HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg", &HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_, &b_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg);
  chain.SetBranchAddress("HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg", &HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_, &b_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg);
  chain.SetBranchAddress("HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg", &HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_, &b_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg);
  chain.SetBranchAddress("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg", &HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_, &b_HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg);

  chain.SetBranchAddress("HLT_Ele27_eta2p1_WPTight_Gsf", &HLT_Ele27_eta2p1_WPTight_Gsf_, &b_HLT_Ele27_eta2p1_WPTight_Gsf);
  chain.SetBranchAddress("HLT_Ele27_eta2p1_WPLoose_Gsf", &HLT_Ele27_eta2p1_WPLoose_Gsf_, &b_HLT_Ele27_eta2p1_WPLoose_Gsf);
  chain.SetBranchAddress("HLT_Ele27_WPTight_Gsf", &HLT_Ele27_WPTight_Gsf_, &b_HLT_Ele27_WPTight_Gsf);
  chain.SetBranchAddress("HLT_Ele25_eta2p1_WPTight_Gsf", &HLT_Ele25_eta2p1_WPTight_Gsf_, &b_HLT_Ele25_eta2p1_WPTight_Gsf);
  chain.SetBranchAddress("HLT_IsoMu22", &HLT_IsoMu22_, &b_HLT_IsoMu22);
  chain.SetBranchAddress("HLT_IsoTkMu22", &HLT_IsoTkMu22_, &b_HLT_IsoTkMu22);
  chain.SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24_, &b_HLT_IsoMu24);
  chain.SetBranchAddress("HLT_IsoTkMu24", &HLT_IsoTkMu24_, &b_HLT_IsoTkMu24);
  chain.SetBranchAddress("HLT_IsoMu22_eta2p1", &HLT_IsoMu22_eta2p1_, &b_HLT_IsoMu22_eta2p1);
  chain.SetBranchAddress("HLT_IsoTkMu22_eta2p1", &HLT_IsoTkMu22_eta2p1_, &b_HLT_IsoTkMu22_eta2p1);
  chain.SetBranchAddress("HLT_Mu50", &HLT_Mu50_, &b_HLT_Mu50);
  chain.SetBranchAddress("HLT_TkMu50", &HLT_TkMu50_, &b_HLT_TkMu50);
  chain.SetBranchAddress("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf_, &b_HLT_Ele32_WPTight_Gsf);
  chain.SetBranchAddress("HLT_Ele35_WPTight_Gsf", &HLT_Ele35_WPTight_Gsf_, &b_HLT_Ele35_WPTight_Gsf);
  chain.SetBranchAddress("HLT_IsoMu27", &HLT_IsoMu27_, &b_HLT_IsoMu27);

  chain.SetBranchAddress("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_, &b_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20);
  chain.SetBranchAddress("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_, &b_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1);
  chain.SetBranchAddress("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_, &b_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30);
  chain.SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_, &b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1);
  chain.SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_, &b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1);
  chain.SetBranchAddress("HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1", &HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_, &b_HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1);
  chain.SetBranchAddress("HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1", &HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_, &b_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1);
  chain.SetBranchAddress("HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1", &HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_, &b_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1);

  chain.SetBranchAddress("HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf", &HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_, &b_HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf);
  chain.SetBranchAddress("HLT_DoubleEle33_CaloIdL_MW", &HLT_DoubleEle33_CaloIdL_MW_, &b_HLT_DoubleEle33_CaloIdL_MW);
  chain.SetBranchAddress("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW", &HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_, &b_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW);
  chain.SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_, &b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
  chain.SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_, &b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL);
  chain.SetBranchAddress("HLT_DoubleMu33NoFiltersNoVtx", &HLT_DoubleMu33NoFiltersNoVtx_, &b_HLT_DoubleMu33NoFiltersNoVtx);
  chain.SetBranchAddress("HLT_DoubleMu23NoFiltersNoVtxDisplaced", &HLT_DoubleMu23NoFiltersNoVtxDisplaced_, &b_HLT_DoubleMu23NoFiltersNoVtxDisplaced);
  chain.SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_, &b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
  chain.SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_, &b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8);
  // chain.SetBranchAddress("", &_, &b_);
  chain.SetBranchAddress("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_, &b_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL);
  chain.SetBranchAddress("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_, &b_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ);
  chain.SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_, &b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
  chain.SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_, &b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
  chain.SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_, &b_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL);
  chain.SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_, &b_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ);
  chain.SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_, &b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
  chain.SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_, &b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
  chain.SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_, &b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL);
  chain.SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_, &b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);

  chain.SetBranchAddress("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL", &HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_, &b_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL);
  chain.SetBranchAddress("HLT_Mu8_DiEle12_CaloIdL_TrackIdL", &HLT_Mu8_DiEle12_CaloIdL_TrackIdL_, &b_HLT_Mu8_DiEle12_CaloIdL_TrackIdL);
  chain.SetBranchAddress("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ", &HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_, &b_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ);
  chain.SetBranchAddress("HLT_TripleMu_12_10_5", &HLT_TripleMu_12_10_5_, &b_HLT_TripleMu_12_10_5);
  chain.SetBranchAddress("HLT_DiMu9_Ele9_CaloIdL_TrackIdL", &HLT_DiMu9_Ele9_CaloIdL_TrackIdL_, &b_HLT_DiMu9_Ele9_CaloIdL_TrackIdL);
  // chain.SetBranchAddress("", &_, &b_);
  //
  //
  chain.SetBranchAddress("nBestVtx", &nBestVtx_, &b_nBestVtx);
  chain.SetBranchAddress("PUWeight", &PUWeight_, &b_PUWeight);
  // chain.SetBranchAddress("PUWeightUP",&PUWeightUP_,&b_PUWeightUP);
  // chain.SetBranchAddress("PUWeightDOWN",&PUWeightDOWN_,&b_PUWeightDOWN);
  chain.SetBranchAddress("EVENT_event", &EVENT_event_, &b_EVENT_event);
  chain.SetBranchAddress("EVENT_run", &EVENT_run_, &b_EVENT_run);
  chain.SetBranchAddress("EVENT_lumiBlock", &EVENT_lumiBlock_,
                         &b_EVENT_lumiBlock);
  chain.SetBranchAddress("EVENT_genHT", &EVENT_genHT_, &b_EVENT_genHT);
  // what is Gen? what does data do?
  if (!data)
    chain.SetBranchAddress("Gen_pt", &Gen_pt_, &b_Gen_pt);
  if (!data)
    chain.SetBranchAddress("Gen_energy", &Gen_energy_, &b_Gen_energy);
  if (!data)
    chain.SetBranchAddress("Gen_charge", &Gen_charge_, &b_Gen_charge);
  if (!data)
    chain.SetBranchAddress("Gen_eta", &Gen_eta_, &b_Gen_eta);
  if (!data)
    chain.SetBranchAddress("Gen_phi", &Gen_phi_, &b_Gen_phi);
  if (!data)
    chain.SetBranchAddress("Gen_pdg_id", &Gen_pdg_id_, &b_Gen_pdg_id);
  if (!data)
    chain.SetBranchAddress("Gen_motherpdg_id", &Gen_motherpdg_id_,
                           &b_Gen_motherpdg_id);
  //  if(!data) chain.SetBranchAddress("Gen_charge",&Gen_charge_,&b_Gen_charge);
  //  if(!data) chain.SetBranchAddress("",&,&);
  //  if(!data) chain.SetBranchAddress("",&,&);
  //?what is these?
  chain.SetBranchAddress("EVENT_genWeight", &genWeight_, &b_genWeight);
  chain.SetBranchAddress("EVENT_genWeights", &genWeights_, &b_genWeights);
  chain.SetBranchAddress("EVENT_prefireWeight", &EVENT_prefireWeight_,
                         &b_EVENT_prefireWeight);
  chain.SetBranchAddress("EVENT_prefireWeightUp", &EVENT_prefireWeightUp_,
                         &b_EVENT_prefireWeightUp);
  chain.SetBranchAddress("EVENT_prefireWeightDown", &EVENT_prefireWeightDown_,   &b_EVENT_prefireWeightDown);
  chain.SetBranchAddress("PUWeight", &PUWeight_,   &b_PUWeight);



  NewTree->Branch("HLT_PFHT450_SixJet40_BTagCSV_p056", &HLT_PFHT450_SixJet40_BTagCSV_p056, "HLT_PFHT450_SixJet40_BTagCSV_p056/I");
  NewTree->Branch("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056", &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056,"HLT_PFHT400_SixJet30_DoubleBTagCSV_p056/I");
  NewTree->Branch("HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg", &HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg, "HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg/I");
  NewTree->Branch("HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg", &HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg, "HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg/I");
  NewTree->Branch("HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg", &HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg, "HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg/I");
  NewTree->Branch("HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg", &HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg, "HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg/I");
  NewTree->Branch("HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg", &HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg, "HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg/I");
  NewTree->Branch("HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg", &HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg, "HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg/I");
  NewTree->Branch("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg", &HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg, "HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg/I");

  NewTree->Branch("HLT_Ele27_eta2p1_WPTight_Gsf", &HLT_Ele27_eta2p1_WPTight_Gsf, "HLT_Ele27_eta2p1_WPTight_Gsf/I");
  NewTree->Branch("HLT_Ele27_eta2p1_WPLoose_Gsf", &HLT_Ele27_eta2p1_WPLoose_Gsf, "HLT_Ele27_eta2p1_WPLoose_Gsf/I");
  NewTree->Branch("HLT_Ele27_WPTight_Gsf", &HLT_Ele27_WPTight_Gsf, "HLT_Ele27_WPTight_Gsf/I");
  NewTree->Branch("HLT_Ele25_eta2p1_WPTight_Gsf", &HLT_Ele25_eta2p1_WPTight_Gsf, "HLT_Ele25_eta2p1_WPTight_Gsf/I");
  NewTree->Branch("HLT_IsoMu22", &HLT_IsoMu22, "HLT_IsoMu22/I");
  NewTree->Branch("HLT_IsoTkMu22", &HLT_IsoTkMu22, "HLT_IsoTkMu22/I");
  NewTree->Branch("HLT_IsoMu24", &HLT_IsoMu24, "HLT_IsoMu24/I");
  NewTree->Branch("HLT_IsoTkMu24", &HLT_IsoTkMu24, "HLT_IsoTkMu24/I");
  NewTree->Branch("HLT_IsoMu22_eta2p1", &HLT_IsoMu22_eta2p1, "HLT_IsoMu22_eta2p1/I");
  NewTree->Branch("HLT_IsoTkMu22_eta2p1", &HLT_IsoTkMu22_eta2p1, "HLT_IsoTkMu22_eta2p1/I");
  NewTree->Branch("HLT_Mu50", &HLT_Mu50, "HLT_Mu50/I");
  NewTree->Branch("HLT_TkMu50", &HLT_TkMu50, "HLT_TkMu50/I");
  NewTree->Branch("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf, "HLT_Ele32_WPTight_Gsf/I");
  NewTree->Branch("HLT_Ele35_WPTight_Gsf", &HLT_Ele35_WPTight_Gsf, "HLT_Ele35_WPTight_Gsf/I");
  NewTree->Branch("HLT_IsoMu27", &HLT_IsoMu27, "HLT_IsoMu27/I");

  NewTree->Branch("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20/I");
  NewTree->Branch("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1/I");
  NewTree->Branch("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30/I");
  NewTree->Branch("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1, "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1/I");
  NewTree->Branch("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1, "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1/I");
  NewTree->Branch("HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1", &HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1, "HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1/I");
  NewTree->Branch("HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1", &HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1, "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1/I");
  NewTree->Branch("HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1", &HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1, "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1/I");

  NewTree->Branch("HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf", &HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf, "HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf/I");
  NewTree->Branch("HLT_DoubleEle33_CaloIdL_MW", &HLT_DoubleEle33_CaloIdL_MW, "HLT_DoubleEle33_CaloIdL_MW/I");
  NewTree->Branch("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW", &HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW, "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW/I");
  NewTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ/I");
  NewTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL/I");
  NewTree->Branch("HLT_DoubleMu33NoFiltersNoVtx", &HLT_DoubleMu33NoFiltersNoVtx, "HLT_DoubleMu33NoFiltersNoVtx/I");
  NewTree->Branch("HLT_DoubleMu23NoFiltersNoVtxDisplaced", &HLT_DoubleMu23NoFiltersNoVtxDisplaced, "HLT_DoubleMu23NoFiltersNoVtxDisplaced/I");
  NewTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ/I");
  NewTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8/I");
  NewTree->Branch("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL/I");
  NewTree->Branch("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ/I");
  NewTree->Branch("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL/I");
  NewTree->Branch("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ/I");
  NewTree->Branch("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL, "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL/I");
  NewTree->Branch("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ, "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ/I");
  NewTree->Branch("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL/I");
  NewTree->Branch("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ/I");
  NewTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL/I");
  NewTree->Branch("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ/I");

  NewTree->Branch("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL", &HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL, "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL/I");
  NewTree->Branch("HLT_Mu8_DiEle12_CaloIdL_TrackIdL", &HLT_Mu8_DiEle12_CaloIdL_TrackIdL, "HLT_Mu8_DiEle12_CaloIdL_TrackIdL/I");
  NewTree->Branch("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ", &HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ, "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ/I");
  NewTree->Branch("HLT_TripleMu_12_10_5", &HLT_TripleMu_12_10_5, "HLT_TripleMu_12_10_5/I");
  NewTree->Branch("HLT_DiMu9_Ele9_CaloIdL_TrackIdL", &HLT_DiMu9_Ele9_CaloIdL_TrackIdL, "HLT_DiMu9_Ele9_CaloIdL_TrackIdL/I");


  NewTree->Branch("genTaus_number", &genTaus_number, "genTaus_number/I");
  NewTree->Branch("genEles_number", &genEles_number, "genEles_number/I");
  NewTree->Branch("genEle_pt", &genEle_pt);
  NewTree->Branch("genEle_eta", &genEle_eta);
  NewTree->Branch("genEle_phi", &genEle_phi);
  NewTree->Branch("genEle_E", &genEle_E);
  NewTree->Branch("genMuons_number", &genMuons_number, "genMuons_number/I");
  NewTree->Branch("genMuon_pt", &genMuon_pt);
  NewTree->Branch("genMuon_eta", &genMuon_eta);
  NewTree->Branch("genMuon_phi", &genMuon_phi);
  NewTree->Branch("genMuon_E", &genMuon_E);

  NewTree->Branch("TopMass", &TopMass, "TopMass/D");
  NewTree->Branch("TopMassMerged", &TopMassMerged, "TopMassMerged/D");
  NewTree->Branch("TopMassPartial", &TopMassPartial, "TopMassPartial/D");
  NewTree->Branch("TopMassResolved", &TopMassResolved, "TopMassResolved/D");
  NewTree->Branch("TopPt", &TopPt, "TopPt/D");
  NewTree->Branch("TopPtMerged", &TopPtMerged, "TopPtMerged/D");
  NewTree->Branch("TopPtPartial", &TopPtPartial, "TopPtPartial/D");
  NewTree->Branch("TopPtResolved", &TopPtResolved, "TopPtResolved/D");
  NewTree->Branch("TopEta", &TopEta, "TopEta/D");
  NewTree->Branch("TopEtaMerged", &TopEtaMerged, "TopEtaMerged/D");
  NewTree->Branch("TopEtaPartial", &TopEtaPartial, "TopEtaPartial/D");
  NewTree->Branch("TopEtaResolved", &TopEtaResolved, "TopEtaResolved/D");
  NewTree->Branch("TopPhi", &TopPhi, "TopPhi/D");
  NewTree->Branch("TopPhiMerged", &TopPhiMerged, "TopPhiMerged/D");
  NewTree->Branch("TopPhiPartial", &TopPhiPartial, "TopPhiPartial/D");
  NewTree->Branch("TopPhiResolved", &TopPhiResolved, "TopPhiResolved/D");
  NewTree->Branch("WMassResolved1", &WMassResolved1, "WMassResolved1/D");
  NewTree->Branch("WMassResolved2", &WMassResolved2, "WMassResolved2/D");
  NewTree->Branch("WMassResolved3", &WMassResolved3, "WMassResolved3/D");
  NewTree->Branch("BMass", &BMass, "BMass/D");
  NewTree->Branch("BCSV", &BCSV, "BCSV/D");
  NewTree->Branch("BPt", &BPt, "BPt/D");
  NewTree->Branch("BEta", &BEta, "BEta/D");
  NewTree->Branch("BPhi", &BPhi, "BPhi/D");
  NewTree->Branch("ZMass", &ZMass, "ZMass/D");
  NewTree->Branch("ZPt", &ZPt, "ZPt/D");
  NewTree->Branch("ZEta", &ZEta, "ZEta/D");
  NewTree->Branch("ZPhi", &ZPhi, "ZPhi/D");
  NewTree->Branch("Jet1ForwardEta", &Jet1ForwardEta, "Jet1ForwardEta/D");
  NewTree->Branch("Jet2ForwardEta", &Jet2ForwardEta, "Jet2ForwardEta/D");
  NewTree->Branch("Jet3ForwardEta", &Jet3ForwardEta, "Jet3ForwardEta/D");
  NewTree->Branch("Jet1ForwardPt", &Jet1ForwardPt, "Jet1ForwardPt/D");
  NewTree->Branch("Jet2ForwardPt", &Jet2ForwardPt, "Jet2ForwardPt/D");
  NewTree->Branch("Jet3ForwardPt", &Jet3ForwardPt, "Jet3ForwardPt/D");
  NewTree->Branch("Jet1ResolvedPt", &Jet1ResolvedPt, "Jet1ResolvedPt/D");
  NewTree->Branch("Jet2ResolvedPt", &Jet2ResolvedPt, "Jet2ResolvedPt/D");
  NewTree->Branch("Jet3ResolvedPt", &Jet3ResolvedPt, "Jet3ResolvedPt/D");
  NewTree->Branch("Jet1PartialPt", &Jet1PartialPt, "Jet1PartialPt/D");
  NewTree->Branch("Jet2PartialPt", &Jet2PartialPt, "Jet2PartialPt/D");
  NewTree->Branch("Jet1MergedPt", &Jet1MergedPt, "Jet1MergedPt/D");
  NewTree->Branch("Jet1ResolvedEta", &Jet1ResolvedEta, "Jet1ResolvedEta/D");
  NewTree->Branch("Jet2ResolvedEta", &Jet2ResolvedEta, "Jet2ResolvedEta/D");
  NewTree->Branch("Jet3ResolvedEta", &Jet3ResolvedEta, "Jet3ResolvedEta/D");
  NewTree->Branch("Jet1PartialEta", &Jet1PartialEta, "Jet1PartialEta/D");
  NewTree->Branch("Jet2PartialEta", &Jet2PartialEta, "Jet2PartialEta/D");
  NewTree->Branch("Jet1MergedEta", &Jet1MergedEta, "Jet1MergedEta/D");
  NewTree->Branch("MostForwardJetEta", &MostForwardJetEta,
                  "MostForwardJetEta/D");
  NewTree->Branch("MostForwardJetPt", &MostForwardJetPt, "MostForwardJetPt/D");
  NewTree->Branch("deltaRZTop", &deltaRZTop, "deltaRZTop/D");
  NewTree->Branch("deltaPhiZB", &deltaPhiZB, "deltaPhiZB/D");
  NewTree->Branch("deltaRZB", &deltaRZB, "deltaRZB/D");
  NewTree->Branch("deltaREle1Ele2", &deltaREle1Ele2, "deltaREle1Ele2/D");
  NewTree->Branch("deltaRMuo1Muo2", &deltaRMuo1Muo2, "deltaRMuo1Muo2/D");
  NewTree->Branch("Massb1b2", &Massb1b2, "Massb1b2/D");
  // NewTree->Branch("MinDeltaPhiJetMet", &MinDeltaPhiJetMet,
                  // "MinDeltaPhiJetMet/D");
  NewTree->Branch("MinDeltaPhiBoostedJetMet", &MinDeltaPhiBoostedJetMet,
                  "MinDeltaPhiBoostedJetMet/D");
  NewTree->Branch("deltaRb1b2", &deltaRb1b2, "deltaRb1b2/D");
  NewTree->Branch("deltaRb1Lep1", &deltaRb1Lep1, "deltaRb1Lep1/D");
  NewTree->Branch("deltaRb1Lep2", &deltaRb1Lep2, "deltaRb1Lep2/D");
  NewTree->Branch("deltaRb2Lep1", &deltaRb2Lep1, "deltaRb2Lep1/D");
  NewTree->Branch("deltaRb2Lep2", &deltaRb2Lep2, "deltaRb2Lep2/D");

  NewTree->Branch("leptonsL_number", &leptonsL_number, "leptonsL_number/I");
  NewTree->Branch("leptonsT_number", &leptonsT_number, "leptonsT_number/I");
  NewTree->Branch("leptonsT_number_v2", &leptonsT_number_v2,
                  "leptonsT_number_v2/I");
  NewTree->Branch("leptonsMVAF_number", &leptonsMVAF_number,
                  "leptonsMVAF_number/I");
  NewTree->Branch("leptonsMVAT_number", &leptonsMVAT_number,"leptonsMVAT_number/I");
  NewTree->Branch("leptonsMVAL_number", &leptonsMVAL_number,"leptonsMVAL_number/I");
  NewTree->Branch("leptonsMVAT_transMass", &leptonsMVAT_transMass, "leptonsMVAT_transMass/I");
  NewTree->Branch("leptonsMVAF_transMass", &leptonsMVAF_transMass, "leptonsMVAF_transMass/I");
  NewTree->Branch("leptonsMVAL_transMass", &leptonsMVAL_transMass, "leptonsMVAL_transMass/I");
  NewTree->Branch("leptonsMVAT_1pt", &leptonsMVAT_1pt,
                  "leptonsMVAT_1pt/D");
  NewTree->Branch("leptonsMVAT_1eta", &leptonsMVAT_1eta,
                  "leptonsMVAT_1eta/D");
  NewTree->Branch("leptonsMVAT_1phi", &leptonsMVAT_1phi,
                  "leptonsMVAT_1phi/D");
  NewTree->Branch("leptonsMVAT_2pt", &leptonsMVAT_2pt,
                  "leptonsMVAT_2pt/D");
  NewTree->Branch("leptonsMVAT_2eta", &leptonsMVAT_2eta,
                  "leptonsMVAT_2eta/D");
  NewTree->Branch("leptonsMVAT_2phi", &leptonsMVAT_2phi,
                  "leptonsMVAT_2phi/D");
  NewTree->Branch("leptonsMVAT_3pt", &leptonsMVAT_3pt,
                  "leptonsMVAT_3pt/D");
  NewTree->Branch("leptonsMVAT_3eta", &leptonsMVAT_3eta,
                  "leptonsMVAT_3eta/D");
  NewTree->Branch("leptonsMVAT_3phi", &leptonsMVAT_3phi, "leptonsMVAT_3phi/D");
  NewTree->Branch("leptonsMVAT_2SS", &leptonsMVAT_2SS, "leptonsMVAT_2SS/I");
  NewTree->Branch("leptonsMVAT_2OS", &leptonsMVAT_2OS, "leptonsMVAT_2OS/I");
  NewTree->Branch("elesMVAL_number", &elesMVAL_number, "elesMVAL_number/I");
  NewTree->Branch("elesMVAF_number", &elesMVAF_number, "elesMVAF_number/I");
  NewTree->Branch("elesMVAT_number", &elesMVAT_number, "elesMVAT_number/I");
  NewTree->Branch("elesMVAL_number_s0", &elesMVAL_number_s0, "elesMVAL_number_s0/I");
  NewTree->Branch("elesMVAF_number_s0", &elesMVAF_number_s0, "elesMVAF_number_s0/I");
  NewTree->Branch("elesMVAT_number_s0", &elesMVAT_number_s0, "elesMVAT_number_s0/I");
  NewTree->Branch("elesMVAL_number_s1", &elesMVAL_number_s1, "elesMVAL_number_s1/I");
  NewTree->Branch("elesMVAF_number_s1", &elesMVAF_number_s1, "elesMVAF_number_s1/I");
  NewTree->Branch("elesMVAT_number_s1", &elesMVAT_number_s1, "elesMVAT_number_s1/I");
  NewTree->Branch("elesMVAL_number_s2", &elesMVAL_number_s2, "elesMVAL_number_s2/I");
  NewTree->Branch("elesMVAF_number_s2", &elesMVAF_number_s2, "elesMVAF_number_s2/I");
  NewTree->Branch("elesMVAT_number_s2", &elesMVAT_number_s2, "elesMVAT_number_s2/I");
  NewTree->Branch("elesMVAL_number_s3", &elesMVAL_number_s3, "elesMVAL_number_s3/I");
  NewTree->Branch("elesMVAF_number_s3", &elesMVAF_number_s3, "elesMVAF_number_s3/I");
  NewTree->Branch("elesMVAT_number_s3", &elesMVAT_number_s3, "elesMVAT_number_s3/I");
  NewTree->Branch("eleMVAL_pt", &eleMVAL_pt);
  NewTree->Branch("eleMVAL_eta", &eleMVAL_eta);
  NewTree->Branch("eleMVAL_phi", &eleMVAL_phi);
  NewTree->Branch("eleMVAL_E", &eleMVAL_E);
  NewTree->Branch("eleMVAF_pt", &eleMVAF_pt);
  NewTree->Branch("eleMVAF_eta", &eleMVAF_eta);
  NewTree->Branch("eleMVAF_phi", &eleMVAF_phi);
  NewTree->Branch("eleMVAF_E", &eleMVAF_E);
  NewTree->Branch("eleMVAT_pt", &eleMVAT_pt);
  NewTree->Branch("eleMVAT_eta", &eleMVAT_eta);
  NewTree->Branch("eleMVAT_phi", &eleMVAT_phi);
  NewTree->Branch("eleMVAT_E", &eleMVAT_E);
  NewTree->Branch("eleMVAL_pt_s0", &eleMVAL_pt_s0);
  NewTree->Branch("eleMVAL_eta_s0", &eleMVAL_eta_s0);
  NewTree->Branch("eleMVAL_phi_s0", &eleMVAL_phi_s0);
  NewTree->Branch("eleMVAL_E_s0", &eleMVAL_E_s0);
  NewTree->Branch("eleMVAF_pt_s0", &eleMVAF_pt_s0);
  NewTree->Branch("eleMVAF_eta_s0", &eleMVAF_eta_s0);
  NewTree->Branch("eleMVAF_phi_s0", &eleMVAF_phi_s0);
  NewTree->Branch("eleMVAF_E_s0", &eleMVAF_E_s0);
  NewTree->Branch("eleMVAT_pt_s0", &eleMVAT_pt_s0);
  NewTree->Branch("eleMVAT_eta_s0", &eleMVAT_eta_s0);
  NewTree->Branch("eleMVAT_phi_s0", &eleMVAT_phi_s0);
  NewTree->Branch("eleMVAT_E_s0", &eleMVAT_E_s0);
  NewTree->Branch("eleMVAL_pt_s1", &eleMVAL_pt_s1);
  NewTree->Branch("eleMVAL_eta_s1", &eleMVAL_eta_s1);
  NewTree->Branch("eleMVAL_phi_s1", &eleMVAL_phi_s1);
  NewTree->Branch("eleMVAL_E_s1", &eleMVAL_E_s1);
  NewTree->Branch("eleMVAF_pt_s1", &eleMVAF_pt_s1);
  NewTree->Branch("eleMVAF_eta_s1", &eleMVAF_eta_s1);
  NewTree->Branch("eleMVAF_phi_s1", &eleMVAF_phi_s1);
  NewTree->Branch("eleMVAF_E_s1", &eleMVAF_E_s1);
  NewTree->Branch("eleMVAT_pt_s1", &eleMVAT_pt_s1);
  NewTree->Branch("eleMVAT_eta_s1", &eleMVAT_eta_s1);
  NewTree->Branch("eleMVAT_phi_s1", &eleMVAT_phi_s1);
  NewTree->Branch("eleMVAT_E_s1", &eleMVAT_E_s1);
  NewTree->Branch("eleMVAL_pt_s2", &eleMVAL_pt_s2);
  NewTree->Branch("eleMVAL_eta_s2", &eleMVAL_eta_s2);
  NewTree->Branch("eleMVAL_phi_s2", &eleMVAL_phi_s2);
  NewTree->Branch("eleMVAL_E_s2", &eleMVAL_E_s2);
  NewTree->Branch("eleMVAF_pt_s2", &eleMVAF_pt_s2);
  NewTree->Branch("eleMVAF_eta_s2", &eleMVAF_eta_s2);
  NewTree->Branch("eleMVAF_phi_s2", &eleMVAF_phi_s2);
  NewTree->Branch("eleMVAF_E_s2", &eleMVAF_E_s2);
  NewTree->Branch("eleMVAT_pt_s2", &eleMVAT_pt_s2);
  NewTree->Branch("eleMVAT_eta_s2", &eleMVAT_eta_s2);
  NewTree->Branch("eleMVAT_phi_s2", &eleMVAT_phi_s2);
  NewTree->Branch("eleMVAT_E_s2", &eleMVAT_E_s2);
  NewTree->Branch("eleMVAL_pt_s3", &eleMVAL_pt_s3);
  NewTree->Branch("eleMVAL_eta_s3", &eleMVAL_eta_s3);
  NewTree->Branch("eleMVAL_phi_s3", &eleMVAL_phi_s3);
  NewTree->Branch("eleMVAL_E_s3", &eleMVAL_E_s3);
  NewTree->Branch("eleMVAF_pt_s3", &eleMVAF_pt_s3);
  NewTree->Branch("eleMVAF_eta_s3", &eleMVAF_eta_s3);
  NewTree->Branch("eleMVAF_phi_s3", &eleMVAF_phi_s3);
  NewTree->Branch("eleMVAF_E_s3", &eleMVAF_E_s3);
  NewTree->Branch("eleMVAT_pt_s3", &eleMVAT_pt_s3);
  NewTree->Branch("eleMVAT_eta_s3", &eleMVAT_eta_s3);
  NewTree->Branch("eleMVAT_phi_s3", &eleMVAT_phi_s3);
  NewTree->Branch("eleMVAT_E_s3", &eleMVAT_E_s3);

  NewTree->Branch("eleL_number", &eleL_number, "eleL_number/I");
  NewTree->Branch("eleM_number", &eleM_number, "eleM_number/I");
  NewTree->Branch("eleT_number", &eleT_number, "eleT_number/I");
  NewTree->Branch("elesMVAF_1pt", &elesMVAF_1pt,
                  "elesMVAF_1pt/D");
  NewTree->Branch("muonsL_number", &muonsL_number, "muonsL_number/I");
  NewTree->Branch("muonsF_number", &muonsF_number, "muonsF_number/I");
  NewTree->Branch("muonsT_number", &muonsT_number, "muonsT_number/I");
  NewTree->Branch("muonsL_number_s0", &muonsL_number_s0, "muonsL_number_s0/I");
  NewTree->Branch("muonsF_number_s0", &muonsF_number_s0, "muonsF_number_s0/I");
  NewTree->Branch("muonsT_number_s0", &muonsT_number_s0, "muonsT_number_s0/I");
  NewTree->Branch("muonsL_number_s1", &muonsL_number_s1, "muonsL_number_s1/I");
  NewTree->Branch("muonsF_number_s1", &muonsF_number_s1, "muonsF_number_s1/I");
  NewTree->Branch("muonsT_number_s1", &muonsT_number_s1, "muonsT_number_s1/I");
  NewTree->Branch("muonsL_number_s2", &muonsL_number_s2, "muonsL_number_s2/I");
  NewTree->Branch("muonsF_number_s2", &muonsF_number_s2, "muonsF_number_s2/I");
  NewTree->Branch("muonsT_number_s2", &muonsT_number_s2, "muonsT_number_s2/I");
  NewTree->Branch("muonsL_number_s3", &muonsL_number_s3, "muonsL_number_s3/I");
  NewTree->Branch("muonsF_number_s3", &muonsF_number_s3, "muonsF_number_s3/I");
  NewTree->Branch("muonsT_number_s3", &muonsT_number_s3, "muonsT_number_s3/I");

  NewTree->Branch("muonL_pt", &muonL_pt);
  NewTree->Branch("muonL_eta", &muonL_eta);
  NewTree->Branch("muonL_phi", &muonL_phi);
  NewTree->Branch("muonL_E", &muonL_E);
  NewTree->Branch("muonF_pt", &muonF_pt);
  NewTree->Branch("muonF_eta", &muonF_eta);
  NewTree->Branch("muonF_phi", &muonF_phi);
  NewTree->Branch("muonF_E", &muonF_E);
  NewTree->Branch("muonT_pt", &muonT_pt);
  NewTree->Branch("muonT_eta", &muonT_eta);
  NewTree->Branch("muonT_phi", &muonT_phi);
  NewTree->Branch("muonT_E", &muonT_E);
  NewTree->Branch("muonL_pt_s0", &muonL_pt_s0);
  NewTree->Branch("muonL_eta_s0", &muonL_eta_s0);
  NewTree->Branch("muonL_phi_s0", &muonL_phi_s0);
  NewTree->Branch("muonL_E_s0", &muonL_E_s0);
  NewTree->Branch("muonF_pt_s0", &muonF_pt_s0);
  NewTree->Branch("muonF_eta_s0", &muonF_eta_s0);
  NewTree->Branch("muonF_phi_s0", &muonF_phi_s0);
  NewTree->Branch("muonF_E_s0", &muonF_E_s0);
  NewTree->Branch("muonT_pt_s0", &muonT_pt_s0);
  NewTree->Branch("muonT_eta_s0", &muonT_eta_s0);
  NewTree->Branch("muonT_phi_s0", &muonT_phi_s0);
  NewTree->Branch("muonT_E_s0", &muonT_E_s0);
  NewTree->Branch("muonL_pt_s1", &muonL_pt_s1);
  NewTree->Branch("muonL_eta_s1", &muonL_eta_s1);
  NewTree->Branch("muonL_phi_s1", &muonL_phi_s1);
  NewTree->Branch("muonL_E_s1", &muonL_E_s1);
  NewTree->Branch("muonF_pt_s1", &muonF_pt_s1);
  NewTree->Branch("muonF_eta_s1", &muonF_eta_s1);
  NewTree->Branch("muonF_phi_s1", &muonF_phi_s1);
  NewTree->Branch("muonF_E_s1", &muonF_E_s1);
  NewTree->Branch("muonT_pt_s1", &muonT_pt_s1);
  NewTree->Branch("muonT_eta_s1", &muonT_eta_s1);
  NewTree->Branch("muonT_phi_s1", &muonT_phi_s1);
  NewTree->Branch("muonT_E_s1", &muonT_E_s1);
  NewTree->Branch("muonL_pt_s2", &muonL_pt_s2);
  NewTree->Branch("muonL_eta_s2", &muonL_eta_s2);
  NewTree->Branch("muonL_phi_s2", &muonL_phi_s2);
  NewTree->Branch("muonL_E_s2", &muonL_E_s2);
  NewTree->Branch("muonF_pt_s2", &muonF_pt_s2);
  NewTree->Branch("muonF_eta_s2", &muonF_eta_s2);
  NewTree->Branch("muonF_phi_s2", &muonF_phi_s2);
  NewTree->Branch("muonF_E_s2", &muonF_E_s2);
  NewTree->Branch("muonT_pt_s2", &muonT_pt_s2);
  NewTree->Branch("muonT_eta_s2", &muonT_eta_s2);
  NewTree->Branch("muonT_phi_s2", &muonT_phi_s2);
  NewTree->Branch("muonT_E_s2", &muonT_E_s2);
  NewTree->Branch("muonL_pt_s3", &muonL_pt_s3);
  NewTree->Branch("muonL_eta_s3", &muonL_eta_s3);
  NewTree->Branch("muonL_phi_s3", &muonL_phi_s3);
  NewTree->Branch("muonL_E_s3", &muonL_E_s3);
  NewTree->Branch("muonF_pt_s3", &muonF_pt_s3);
  NewTree->Branch("muonF_eta_s3", &muonF_eta_s3);
  NewTree->Branch("muonF_phi_s3", &muonF_phi_s3);
  NewTree->Branch("muonF_E_s3", &muonF_E_s3);
  NewTree->Branch("muonT_pt_s3", &muonT_pt_s3);
  NewTree->Branch("muonT_eta_s3", &muonT_eta_s3);
  NewTree->Branch("muonT_phi_s3", &muonT_phi_s3);
  NewTree->Branch("muonT_E_s3", &muonT_E_s3);
  NewTree->Branch("muonsT_1pt", &muonsT_1pt, "muonsT_1pt/D");
  NewTree->Branch("muonsT_1eta", &muonsT_1eta, "muonsT_1eta/D");
  NewTree->Branch("muonsT_1phi", &muonsT_1phi, "muonsT_1phi/D");
  NewTree->Branch("muonsT_2pt", &muonsT_2pt, "muonsT_2pt/D");
  NewTree->Branch("muonsT_2eta", &muonsT_2eta, "muonsT_2eta/D");
  NewTree->Branch("muonsT_2phi", &muonsT_2phi, "muonsT_2phi/D");
  NewTree->Branch("muonsT_3pt", &muonsT_3pt, "muonsT_3pt/I");
  NewTree->Branch("muonsT_3eta", &muonsT_3eta, "muonsT_3eta/I");
  NewTree->Branch("muonsT_3phi", &muonsT_3phi, "muonsT_3phi/I");

  NewTree->Branch("jetsL_number", &jetsL_number, "jetsL_number/I");
  NewTree->Branch("jetsL_HT", &jetsL_HT, "jetsL_HT/D");
  NewTree->Branch("jetsL_MHT", &jetsL_MHT, "jetsL_MHT/D");
  NewTree->Branch("jetsL_invariantMass", &jetsL_invariantMass,
                  "jetsL_invariantMass/D");
  NewTree->Branch("jetsL_transMass", &jetsL_transMass, "jetsL_transMass/D");
  NewTree->Branch("jetL_minDeltaR", &jetL_minDeltaR, "jetL_minDeltaR/D");
  NewTree->Branch("jetsL_centrality", &jetsL_centrality, "jetsL_centrality/D");
  NewTree->Branch("Aplanarity", &Aplanarity, "Aplanarity/D");
  // NewTree->Branch("MaxdeltaRJets",        &MaxdeltaRJets, "MaxdeltaRJets/D");
  NewTree->Branch("Sphericity", &Sphericity, "Sphericity/D");
  // NewTree->Branch("MindeltaRJets",     &MindeltaRJets, "MindeltaRJets/D");
  NewTree->Branch("LeadingJetpfDeepFlavourBJetTags",
                  &LeadingJetpfDeepFlavourBJetTags,
                  "LeadingJetpfDeepFlavourBJetTags/D");
  NewTree->Branch("SecondJetpfDeepFlavourBJetTags",
                  &SecondJetpfDeepFlavourBJetTags,
                  "SecondJetpfDeepFlavourBJetTags/D");
  NewTree->Branch("ThirdJetpfDeepFlavourBJetTags",
                  &ThirdJetpfDeepFlavourBJetTags,
                  "ThirdJetpfDeepFlavourBJetTags/D");
  NewTree->Branch("jetsL_bScore", &jetsL_bScore, "jetsL_bScore/D");
  NewTree->Branch("jetsL_average_deltaR", &jetsL_average_deltaR, "&jetsL_average_deltaR/D");
  NewTree->Branch("jetsL_4largestBscoreSum", &jetsL_4largestBscoreSum,"jetsL_4largestBscoreSum/D");
  NewTree->Branch("jetsL_leading2invariantMass", &jetsL_leading2invariantMass,"jetsL_leading2invariantMass/D");
  NewTree->Branch("jetsL_rationHT_4toRest", &jetsL_rationHT_4toRest,"jetsL_rationHT_4toRest/D");

  NewTree->Branch("jetsL_leptonsMVAT_minDeltaR", &jetsL_leptonsMVAT_minDeltaR,
                  "jetsL_leptonsMVAT_minDeltaR/D");
  NewTree->Branch("jetsL_tausF_minDeltaR", &jetsL_tausF_minDeltaR,
                  "jetsL_tausF_minDeltaR/D");
  NewTree->Branch("jetsL_1pt", &jetsL_1pt, "jetsL_1pt/D");
  NewTree->Branch("jetsL_1eta", &jetsL_1eta, "jetsL_1eta/D");
  NewTree->Branch("jetsL_1phi", &jetsL_1phi, "jetsL_1phi/D");
  NewTree->Branch("jetsL_2pt", &jetsL_2pt, "jetsL_2pt/D");
  NewTree->Branch("jetsL_2eta", &jetsL_2eta, "jetsL_2eta/D");
  NewTree->Branch("jetsL_2phi", &jetsL_2phi, "jetsL_2phi/D");
  NewTree->Branch("jetsL_3pt", &jetsL_3pt, "jetsL_3pt/D");
  NewTree->Branch("jetsL_3eta", &jetsL_3eta, "jetsL_3eta/D");
  NewTree->Branch("jetsL_3phi", &jetsL_3phi, "jetsL_3phi/D");
  NewTree->Branch("jetsL_4pt", &jetsL_4pt, "jetsL_4pt/D");
  NewTree->Branch("jetsL_4eta", &jetsL_4eta, "jetsL_4eta/D");
  NewTree->Branch("jetsL_4phi", &jetsL_4phi, "jetsL_4phi/D");
  NewTree->Branch("jetsL_5pt", &jetsL_5pt, "jetsL_5pt/D");
  NewTree->Branch("jetsL_5eta", &jetsL_5eta, "jetsL_5eta/D");
  NewTree->Branch("jetsL_5phi", &jetsL_5phi, "jetsL_5phi/D");
  NewTree->Branch("jetsL_6pt", &jetsL_6pt, "jetsL_6pt/D");
  NewTree->Branch("jetsL_6eta", &jetsL_6eta, "jetsL_6eta/D");
  NewTree->Branch("jetsL_6phi", &jetsL_6phi, "jetsL_6phi/D");
  NewTree->Branch("jetsL_7pt", &jetsL_7pt, "jetsL_7pt/D");
  NewTree->Branch("jetsL_7eta", &jetsL_7eta, "jetsL_7eta/D");
  NewTree->Branch("jetL_7phi", &jetL_7phi, "jetL_7phi/D");
  NewTree->Branch("jetsL_8pt", &jetsL_8pt, "jetsL_8pt/D");
  NewTree->Branch("jetsL_8eta", &jetsL_8eta, "jetsL_8eta/D");
  NewTree->Branch("jetsL_8phi", &jetsL_8phi, "jetsL_8phi/D");
  NewTree->Branch("jetsL_9pt", &jetsL_9pt, "jetsL_9pt/D");
  NewTree->Branch("jetsL_9eta", &jetsL_9eta, "jetsL_9eta/D");
  NewTree->Branch("jetsL_9phi", &jetsL_9phi, "jetsL_9phi/D");
  NewTree->Branch("jetsL_10pt", &jetsL_10pt, "jetsL_10pt/D");
  NewTree->Branch("jetsL_10eta", &jetsL_10eta, "jetsL_10eta/D");
  NewTree->Branch("jetsL_10phi", &jetsL_10phi, "jetsL_10phi/D");
  NewTree->Branch("jetsL_11pt", &jetsL_11pt, "jetsL_11pt/D");
  NewTree->Branch("jetsL_11eta", &jetsL_11eta, "jetsL_11eta/D");
  NewTree->Branch("jetsL_11phi", &jetsL_11phi, "jetsL_11phi/D");
  NewTree->Branch("jetsL_HTDividedByMet", &jetsL_HTDividedByMet, "jetsL_HTDividedByMet/D");
  NewTree->Branch("MetDividedByHT", &MetDividedByHT, "MetDividedByHT/D");
  NewTree->Branch("jetsL_MHTDividedByMet", &jetsL_MHTDividedByMet, "jetsL_MHTDividedByMet/D");

  NewTree->Branch("bjetsL_num", &bjetsL_num, "bjetsL_num/I");
  NewTree->Branch("bjetsM_num", &bjetsM_num, "bjetsM_num/I");
  NewTree->Branch("bjetsT_num", &bjetsT_num, "bjetsT_num/I");
  NewTree->Branch("bjetsL_HT", &bjetsL_HT, "bjetsL_HT/D");
  NewTree->Branch("bjetsM_HT", &bjetsM_HT, "bjetsM_HT/D");
  NewTree->Branch("bjetsT_HT", &bjetsT_HT, "bjetsT_HT/D");
  NewTree->Branch("bjetsL_MHT", &bjetsL_MHT, "bjetsL_MHT/D");
  NewTree->Branch("bjetsM_MHT", &bjetsM_MHT, "bjetsM_MHT/D");
  NewTree->Branch("bjetsT_MHT", &bjetsT_MHT, "bjetsT_MHT/D");
  NewTree->Branch("bjetsL_invariantMass", &bjetsL_invariantMass,
                  "bjetsL_invariantMass/D");
  NewTree->Branch("bjetsM_invariantMass", &bjetsM_invariantMass,
                  "bjetsM_invariantMass/D");
  NewTree->Branch("bjetsT_invariantMass", &bjetsT_invariantMass,
                  "bjetsT_invariantMass/D");
  NewTree->Branch("bjetsL_transMass", &bjetsL_transMass, "bjetsL_transMass/D");
  NewTree->Branch("bjetsM_transMass", &bjetsM_transMass, "bjetsM_transMass/D");
  NewTree->Branch("bjetsT_transMass", &bjetsT_transMass, "bjetsT_transMass/D");
  NewTree->Branch("bjetsL_minDeltaR", &bjetsL_minDeltaR, "bjetsL_minDeltaR/D");
  NewTree->Branch("bjetsM_minDeltaR", &bjetsM_minDeltaR, "bjetsM_minDeltaR/D");
  NewTree->Branch("bjetsT_minDeltaR", &bjetsT_minDeltaR, "bjetsT_minDeltaR/D");
  NewTree->Branch("bjetsL_leptonsMVAT_minDeltaR", &bjetsL_leptonsMVAT_minDeltaR, "bjetsL_leptonsMVAT_minDeltaR/D");
  NewTree->Branch("bjetsM_leptonsMVAT_minDeltaR", &bjetsM_leptonsMVAT_minDeltaR, "bjetsM_leptonsMVAT_minDeltaR/D");
  NewTree->Branch("bjetsT_leptonsMVAT_minDeltaR", &bjetsT_leptonsMVAT_minDeltaR, "bjetsT_leptonsMVAT_minDeltaR/D");
  NewTree->Branch("bjetsL_tausF_minDeltaR", &bjetsL_tausF_minDeltaR, "bjetsL_tausF_minDeltaR/D");
  // NewTree->Branch("", &, "/D");
  NewTree->Branch("bjetsL_1pt", &bjetsL_1pt, "bjetsL_1pt/D");
  NewTree->Branch("bjetsL_1eta", &bjetsL_1eta, "bjetsL_1eta/D");
  NewTree->Branch("bjetsL_1phi", &bjetsL_1phi, "bjetsL_1phi/D");
  NewTree->Branch("bjetsL_2pt", &bjetsL_2pt, "bjetsL_2pt/D");
  NewTree->Branch("bjetsL_2eta", &bjetsL_2eta, "bjetsL_2eta/D");
  NewTree->Branch("bjetsL_2phi", &bjetsL_2phi, "bjetsL_2phi/D");
  NewTree->Branch("bjetsL_3pt", &bjetsL_3pt, "bjetsL_3pt/D");
  NewTree->Branch("bjetsL_3eta", &bjetsL_3eta, "bjetsL_3eta/D");
  NewTree->Branch("bjetsL_3phi", &bjetsL_3phi, "bjetsL_3phi/D");
  NewTree->Branch("bjetsL_4pt", &bjetsL_4pt, "bjetsL_4pt/D");
  NewTree->Branch("bjetsL_4eta", &bjetsL_4eta, "bjetsL_4eta/D");
  NewTree->Branch("bjetsL_4phi", &bjetsL_4phi, "bjetsL_4phi/D");
  NewTree->Branch("bjetsM_1pt", &bjetsM_1pt, "bjetsM_1pt/D");
  NewTree->Branch("bjetsM_1eta", &bjetsM_1eta, "bjetsM_1eta/D");
  NewTree->Branch("bjetsM_1phi", &bjetsM_1phi, "bjetsM_1phi/D");
  NewTree->Branch("bjetsM_2pt", &bjetsM_2pt, "bjetsM_2pt/D");
  NewTree->Branch("bjetsM_2eta", &bjetsM_2eta, "bjetsM_2eta/D");
  NewTree->Branch("bjetsM_2phi", &bjetsM_2phi, "bjetsM_2phi/D");
  NewTree->Branch("bjetsM_3pt", &bjetsM_3pt, "bjetsM_3pt/D");
  NewTree->Branch("bjetsM_3eta", &bjetsM_3eta, "bjetsM_3eta/D");
  NewTree->Branch("bjetsM_3phi", &bjetsM_3phi, "bjetsM_3phi/D");
  NewTree->Branch("bjetsM_4pt", &bjetsM_4pt, "bjetsM_4pt/D");
  NewTree->Branch("bjetsM_4eta", &bjetsM_4eta, "bjetsM_4eta/D");
  NewTree->Branch("bjetsM_4phi", &bjetsM_4phi, "bjetsM_4phi/D");
  NewTree->Branch("bjetsT_1pt", &bjetsT_1pt, "bjetsT_1pt/D");
  NewTree->Branch("bjetsT_1eta", &bjetsT_1eta, "bjetsT_1eta/D");
  NewTree->Branch("bjetsT_1phi", &bjetsT_1phi, "bjetsT_1phi/D");
  NewTree->Branch("bjetsT_2pt", &bjetsT_2pt, "bjetsT_2pt/D");
  NewTree->Branch("bjetsT_2eta", &bjetsT_2eta, "bjetsT_2eta/D");
  NewTree->Branch("bjetsT_2phi", &bjetsT_2phi, "bjetsT_2phi/D");
  NewTree->Branch("bjetsT_3pt", &bjetsT_3pt, "bjetsT_3pt/D");
  NewTree->Branch("bjetsT_3eta", &bjetsT_3eta, "bjetsT_3eta/D");
  NewTree->Branch("bjetsT_3phi", &bjetsT_3phi, "bjetsT_3phi/D");
  NewTree->Branch("bjetsT_4pt", &bjetsT_4pt, "bjetsT_4pt/D");
  NewTree->Branch("bjetsT_4eta", &bjetsT_4eta, "bjetsT_4eta/D");
  NewTree->Branch("bjetsT_4phi", &bjetsT_4phi, "bjetsT_4phi/D");

  NewTree->Branch("forwardJets_num", &forwardJets_num, "forwardJets_num/I");
  NewTree->Branch("forwardjet_1pt", &forwardjet_1pt, "forwardjet_1pt/D");
  NewTree->Branch("forwardjet_1eta", &forwardjet_1eta, "forwardjet_1eta/D");
  NewTree->Branch("forwardjet_1phi", &forwardjet_1phi, "forwardjet_1phi/D");
  NewTree->Branch("forwardjet1_jetsL_minDeltaEta",
                  &forwardjet1_jetsL_minDeltaEta,
                  "forwardjet1_jetsL_minDeltaEta/D");

  NewTree->Branch("tausL_number", &tausL_number, "tausL_number/I");
  NewTree->Branch("tausF_number", &tausF_number, "tausF_number/I");
  NewTree->Branch("tausT_number", &tausT_number, "tausT_number/I");
  NewTree->Branch("tausL_MHT", &tausL_MHT, "tausL_MHT/D");
  NewTree->Branch("tausF_MHT", &tausF_MHT, "tausF_MHT/D");
  NewTree->Branch("tausT_MHT", &tausT_MHT, "tausT_MHT/D");
  NewTree->Branch("tausL_HT", &tausL_HT, "tausL_HT/D");
  NewTree->Branch("tausF_HT", &tausF_HT, "tausF_HT/D");
  NewTree->Branch("tausT_HT", &tausT_HT, "tausT_HT/D");
  NewTree->Branch("tausL_invariantMass", &tausL_invariantMass,
                  "tausL_invariantMass/D");
  NewTree->Branch("tausF_invariantMass", &tausF_invariantMass,   "tausF_invariantMass/D");
  NewTree->Branch("tausT_invariantMass", &tausT_invariantMass,   "tausT_invariantMass/D");
  NewTree->Branch("tausL_minDeltaR", &tausL_minDeltaR, "tausL_minDeltaR/D");
  NewTree->Branch("tausF_minDeltaR", &tausF_minDeltaR, "tausF_minDeltaR/D");
  NewTree->Branch("tausT_minDeltaR", &tausT_minDeltaR, "tausT_minDeltaR/D");
  NewTree->Branch("tauL_1pt", &tauL_1pt, "tauL_1pt/D");
  NewTree->Branch("tauL_1eta", &tauL_1eta, "tauL_1eta/D");
  NewTree->Branch("tauL_1phi", &tauL_1phi, "tauL_1phi/D");
  NewTree->Branch("tauL_2pt", &tauL_2pt, "tauL_2pt/D");
  NewTree->Branch("tauL_2eta", &tauL_2eta, "tauL_2eta/D");
  NewTree->Branch("tauL_2phi", &tauL_2phi, "tauL_2phi/D");
  NewTree->Branch("tauL_3pt", &tauL_3pt, "tauL_3pt/D");
  NewTree->Branch("tauL_3eta", &tauL_3eta, "tauL_3eta/D");
  NewTree->Branch("tauL_3phi", &tauL_3phi, "tauL_3phi/D");
  NewTree->Branch("tausF_leptonsT_transMass", &tausF_leptonsT_transMass, "tausF_leptonsT_transMass/D");
  NewTree->Branch("tausL_leptonsT_transMass", &tausL_leptonsT_transMass, "tausL_leptonsT_transMass/D");
  NewTree->Branch("tausT_leptonsT_transMass", &tausT_leptonsT_transMass,
                  "tausT_leptonsT_transMass/D");
  NewTree->Branch("tausF_leptonsT_invariantMass", &tausF_leptonsT_invariantMass, "tausF_leptonsT_invariantMass/D");
  NewTree->Branch("tausL_leptonsT_invariantMass", &tausL_leptonsT_invariantMass, "tausL_leptonsT_invariantMass/D");
  NewTree->Branch("tausT_leptonsT_invariantMass", &tausT_leptonsT_invariantMass, "tausT_leptonsT_invariantMass/D");
  NewTree->Branch("tausF_leptonsT_chargeSum", &tausF_leptonsT_chargeSum,
                  "tausF_leptonsT_chargeSum/D");
  NewTree->Branch("tausF_leptonsTMVA_minDeltaR", &tausF_leptonsTMVA_minDeltaR, "tausF_leptonsTMVA_minDeltaR/D");
  NewTree->Branch("tausL_leptonsTMVA_minDeltaR", &tausL_leptonsTMVA_minDeltaR, "tausL_leptonsTMVA_minDeltaR/D");
  NewTree->Branch("tausT_leptonsTMVA_minDeltaR", &tausT_leptonsTMVA_minDeltaR, "tausT_leptonsTMVA_minDeltaR/D");

  NewTree->Branch("Met_pt", &Met_pt, "Met_pt/D");
  NewTree->Branch("Met_phi", &Met_phi, "Met_phi/D");
  NewTree->Branch("TransverseMassMetTop", &TransverseMassMetTop,
                  "TransverseMassMetTop/D");

  NewTree->Branch("toptagger_num", &toptagger_num, "toptagger_num/I");
  NewTree->Branch("toptagger_MHT", &toptagger_MHT, "toptagger_MHT/D");
  NewTree->Branch("toptagger_HT", &toptagger_HT, "toptagger_HT/D");
  NewTree->Branch("toptagger_invariantMass", &toptagger_invariantMass, "toptagger_invariantMass/D");
  NewTree->Branch("toptagger_transMass", &toptagger_transMass, "toptagger_transMass/D");
  NewTree->Branch("toptagger_minDeltaR_v1", &toptagger_minDeltaR_v1, "toptagger_minDeltaR_v1/D");
  NewTree->Branch("toptagger_1pt", &toptagger_1pt, "toptagger_1pt/I");
  NewTree->Branch("toptagger_1eta", &toptagger_1eta, "toptagger_1eta/I");
  NewTree->Branch("toptagger_1phi", &toptagger_1phi, "toptagger_1phi/I");
  NewTree->Branch("toptagger_2pt", &toptagger_2pt, "toptagger_2pt/D");
  NewTree->Branch("toptagger_2eta", &toptagger_2eta, "toptagger_2eta/D");
  NewTree->Branch("toptagger_2phi", &toptagger_2phi, "toptagger_2phi/D");
  NewTree->Branch("toptagger_3pt", &toptagger_3pt, "toptagger_3pt/D");
  NewTree->Branch("toptagger_3eta", &toptagger_3eta, "toptagger_3eta/D");
  NewTree->Branch("toptagger_3phi", &toptagger_3phi, "toptagger_3phi/D");
  NewTree->Branch("toptagger_minDeltaR", &toptagger_minDeltaR, "toptagger_minDeltaR/D");
  NewTree->Branch("toptagger_maxDeltaR", &toptagger_maxDeltaR, "toptagger_maxDeltaR/D");
  NewTree->Branch("toptagger_scoreAllTops", &toptagger_scoreAllTops, "toptagger_scoreAllTops/D");
  NewTree->Branch("toptagger_leptonsMVAT_minDeltaR", &toptagger_leptonsMVAT_minDeltaR, "toptagger_leptonsMVAT_minDeltaR/D");
  //
  //
  NewTree->Branch("NumSelWJets", &NumSelWJets, "NumSelWJets/I");
  NewTree->Branch("NumSelTopJets", &NumSelTopJets, "NumSelTopJets/I");
  NewTree->Branch("NVertices", &NVertices, "NVertices/I");
  NewTree->Branch("PUWeight", &PUWeight, "PUWeight/D");
  NewTree->Branch("PUWeightUP", &PUWeightUP, "PUWeightUP/D");
  NewTree->Branch("PUWeightDOWN", &PUWeightDOWN, "PUWeightDOWN/D");
  NewTree->Branch("getTrueNumInteractions", &getTrueNumInteractions,
                  "getTrueNumInteractions/I");
  NewTree->Branch("w_for", &w_for, "w_for/D");
  NewTree->Branch("w_forUp", &w_forUp, "w_forUp/D");
  NewTree->Branch("w_forDown", &w_forDown, "w_forDown/D");
  NewTree->Branch("w_topJet", &w_topJet, "w_topJet/D");
  NewTree->Branch("w_topJetUp", &w_topJetUp, "w_topJetUp/D");
  NewTree->Branch("w_topJetDown", &w_topJetDown, "w_topJetDown/D");
  NewTree->Branch("w_WJet", &w_WJet, "w_WJet/D");
  NewTree->Branch("w_WJetUp", &w_WJetUp, "w_WJetUp/D");
  NewTree->Branch("w_WJetDown", &w_WJetDown, "w_WJetDown/D");
  NewTree->Branch("w_Muon1", &w_Muon1, "w_Muon1/D");
  NewTree->Branch("w_Muon2", &w_Muon2, "w_Muon2/D");
  NewTree->Branch("w_Muon1Up", &w_Muon1Up, "w_Muon1Up/D");
  NewTree->Branch("w_Muon2Up", &w_Muon2Up, "w_Muon2Up/D");
  NewTree->Branch("w_Muon1Down", &w_Muon1Down, "w_Muon1Down/D");
  NewTree->Branch("w_Muon2Down", &w_Muon2Down, "w_Muon2Down/D");
  NewTree->Branch("w_TrigMuon", &w_TrigMuon, "w_TrigMuon/D");
  NewTree->Branch("w_TrigMuonUp", &w_TrigMuonUp, "w_TrigMuonUp/D");
  NewTree->Branch("w_TrigMuonDown", &w_TrigMuonDown, "w_TrigMuonDown/D");
  NewTree->Branch("w_Electron1", &w_Electron1, "w_Electron1/D");
  NewTree->Branch("w_Electron2", &w_Electron2, "w_Electron2/D");
  NewTree->Branch("w_Electron1Up", &w_Electron1Up, "w_Electron1Up/D");
  NewTree->Branch("w_Electron2Up", &w_Electron2Up, "w_Electron2Up/D");
  NewTree->Branch("w_Electron1Down", &w_Electron1Down, "w_Electron1Down/D");
  NewTree->Branch("w_Electron2Down", &w_Electron2Down, "w_Electron2Down/D");
  NewTree->Branch("w_TrigElec", &w_TrigElec, "w_TrigElec/D");
  NewTree->Branch("w_TrigElecUp", &w_TrigElecUp, "w_TrigElecUp/D");
  NewTree->Branch("w_TrigElecDown", &w_TrigElecDown, "w_TrigElecDown/D");
  NewTree->Branch("w_ZToNuNu", &w_ZToNuNu, "w_ZToNuNu/D");
  NewTree->Branch("w_ZToNuNuUp", &w_ZToNuNuUp, "w_ZToNuNuUp/D");
  NewTree->Branch("w_ZToNuNuDown", &w_ZToNuNuDown, "w_ZToNuNuDown/D");
  NewTree->Branch("w_WToLNu", &w_WToLNu, "w_WToLNu/D");
  NewTree->Branch("w_WToLNuUp", &w_WToLNuUp, "w_WToLNuUp/D");
  NewTree->Branch("w_WToLNuDown", &w_WToLNuDown, "w_WToLNuDown/D");
  NewTree->Branch("w_ttbar", &w_ttbar, "w_ttbar/D");
  NewTree->Branch("w_ttbarUp", &w_ttbarUp, "w_ttbarUp/D");
  NewTree->Branch("w_ttbarDown", &w_ttbarDown, "w_ttbarDown/D");
  NewTree->Branch("w_Trig", &w_Trig, "w_Trig/D");
  NewTree->Branch("w_TrigUp", &w_TrigUp, "w_TrigUp/D");
  NewTree->Branch("w_TrigDown", &w_TrigDown, "w_TrigDown/D");
  NewTree->Branch("WMass", &WMass, "WMass/D");
  NewTree->Branch("WSubjet", &WSubjet, "WSubjet/D");
  NewTree->Branch("TopSoftMass", &TopSoftMass, "TopSoftMass/D");
  NewTree->Branch("TopSubjet", &TopSubjet, "TopSubjet/D");
  NewTree->Branch("w_Btag", &w_Btag, "w_Btag/D");
  NewTree->Branch("w_BtagUp", &w_BtagUp, "w_BtagUp/D");
  NewTree->Branch("w_BtagDown", &w_BtagDown, "w_BtagDown/D");
  NewTree->Branch("w_Btag1Up", &w_Btag1Up, "w_Btag1Up/D");
  NewTree->Branch("w_Btag1Down", &w_Btag1Down, "w_Btag1Down/D");
  NewTree->Branch("w_Btag2Up", &w_Btag2Up, "w_Btag2Up/D");
  NewTree->Branch("w_Btag2Down", &w_Btag2Down, "w_Btag2Down/D");
  NewTree->Branch("w_BtagLoose", &w_BtagLoose, "w_BtagLoose/D");
  NewTree->Branch("w_BtagLooseUp", &w_BtagLooseUp, "w_BtagLooseUp/D");
  NewTree->Branch("w_BtagLooseDown", &w_BtagLooseDown, "w_BtagLooseDown/D");
  NewTree->Branch("w_QCDUp", &w_QCDUp, "w_QCDUp/D");
  NewTree->Branch("w_QCDDown", &w_QCDDown, "w_QCDDown/D");
  NewTree->Branch("w_PDFUp", &w_PDFUp, "w_PDFUp/D");
  NewTree->Branch("w_PDFDown", &w_PDFDown, "w_PDFDown/D");
  NewTree->Branch("deltaPhiZTopResolved", &deltaPhiZTopResolved,
                  "deltaPhiZTopResolved/D");
  NewTree->Branch("deltaRZTopResolved", &deltaRZTopResolved,
                  "deltaRZTopResolved/D");
  NewTree->Branch("deltaPhiZTopPartial", &deltaPhiZTopPartial,
                  "deltaPhiZTopPartial/D");
  NewTree->Branch("deltaRZTopPartial", &deltaRZTopPartial,
                  "deltaRZTopPartial/D");
  NewTree->Branch("deltaPhiZTopMerged", &deltaPhiZTopMerged,
                  "deltaPhiZTopMerged/D");
  NewTree->Branch("deltaRZTopMerged", &deltaRZTopMerged, "deltaRZTopMerged/D");
  NewTree->Branch("deltaRbTop", &deltaRbTop, "deltaRbTop/D");
  NewTree->Branch("deltaPhiMetTop", &deltaPhiMetTop, "deltaPhiMetTop/D");
  NewTree->Branch("genWeight", &genWeight, "genWeight/D");
  NewTree->Branch("dQuark", &dQuark, "dQuark/I");
  NewTree->Branch("uQuark", &uQuark, "uQuark/I");
  NewTree->Branch("sQuark", &sQuark, "sQuark/I");
  NewTree->Branch("cQuark", &cQuark, "cQuark/I");
  NewTree->Branch("bQuark", &bQuark, "bQuark/I");
  NewTree->Branch("tQuark", &tQuark, "tQuark/I");
  NewTree->Branch("EVENT_event", &EVENT_event, "EVENT_event/I");
  NewTree->Branch("EVENT_run", &EVENT_run, "EVENT_run/I");
  NewTree->Branch("EVENT_lumiBlock", &EVENT_lumiBlock, "EVENT_lumiBlock/I");
  NewTree->Branch("EVENT_genHT", &EVENT_genHT, "EVENT_genHT/D");
  NewTree->Branch("prefiringweight", &prefiringweight, "prefiringweight/D");
  NewTree->Branch("prefiringweightup", &prefiringweightup,
                  "prefiringweightup/D");
  NewTree->Branch("prefiringweightdown", &prefiringweightdown,  "prefiringweightdown/D");
  NewTree->Branch("puWeight", &puWeight,  "puWeight/D");
  NewTree->Branch("EVENT_genWeight", &EVENT_genWeight,  "EVENT_genWeight/D");

  if (selection == 2) {
    NewTreeSB->Branch("TopMass", &TopMass, "TopMass/D");
    NewTreeSB->Branch("TopMassMerged", &TopMassMerged, "TopMassMerged/D");
    NewTreeSB->Branch("TopMassPartial", &TopMassPartial, "TopMassPartial/D");
    NewTreeSB->Branch("TopMassResolved", &TopMassResolved, "TopMassResolved/D");
    NewTreeSB->Branch("TopPt", &TopPt, "TopPt/D");
    NewTreeSB->Branch("TopPtMerged", &TopPtMerged, "TopPtMerged/D");
    NewTreeSB->Branch("TopPtPartial", &TopPtPartial, "TopPtPartial/D");
    NewTreeSB->Branch("TopPtResolved", &TopPtResolved, "TopPtResolved/D");
    NewTreeSB->Branch("TopEta", &TopEta, "TopEta/D");
    NewTreeSB->Branch("TopEtaMerged", &TopEtaMerged, "TopEtaMerged/D");
    NewTreeSB->Branch("TopEtaPartial", &TopEtaPartial, "TopEtaPartial/D");
    NewTreeSB->Branch("TopEtaResolved", &TopEtaResolved, "TopEtaResolved/D");
    NewTreeSB->Branch("TopPhi", &TopPhi, "TopPhi/D");
    NewTreeSB->Branch("TopPhiMerged", &TopPhiMerged, "TopPhiMerged/D");
    NewTreeSB->Branch("TopPhiPartial", &TopPhiPartial, "TopPhiPartial/D");
    NewTreeSB->Branch("TopPhiResolved", &TopPhiResolved, "TopPhiResolved/D");
    NewTreeSB->Branch("WMassResolved1", &WMassResolved1, "WMassResolved1/D");
    NewTreeSB->Branch("WMassResolved2", &WMassResolved2, "WMassResolved2/D");
    NewTreeSB->Branch("WMassResolved3", &WMassResolved3, "WMassResolved3/D");
    NewTreeSB->Branch("BMass", &BMass, "BMass/D");
    NewTreeSB->Branch("BCSV", &BCSV, "BCSV/D");
    NewTreeSB->Branch("BPt", &BPt, "BPt/D");
    NewTreeSB->Branch("BEta", &BEta, "BEta/D");
    NewTreeSB->Branch("BPhi", &BPhi, "BPhi/D");
    NewTreeSB->Branch("ZMass", &ZMass, "ZMass/D");
    NewTreeSB->Branch("ZPt", &ZPt, "ZPt/D");
    NewTreeSB->Branch("ZEta", &ZEta, "ZEta/D");
    NewTreeSB->Branch("ZPhi", &ZPhi, "ZPhi/D");
    NewTreeSB->Branch("Jet1ForwardEta", &Jet1ForwardEta, "Jet1ForwardEta/D");
    NewTreeSB->Branch("Jet2ForwardEta", &Jet2ForwardEta, "Jet2ForwardEta/D");
    NewTreeSB->Branch("Jet3ForwardEta", &Jet3ForwardEta, "Jet3ForwardEta/D");
    NewTreeSB->Branch("Jet1ForwardPt", &Jet1ForwardPt, "Jet1ForwardPt/D");
    NewTreeSB->Branch("Jet2ForwardPt", &Jet2ForwardPt, "Jet2ForwardPt/D");
    NewTreeSB->Branch("Jet3ForwardPt", &Jet3ForwardPt, "Jet3ForwardPt/D");
    NewTreeSB->Branch("Jet1ResolvedPt", &Jet1ResolvedPt, "Jet1ResolvedPt/D");
    NewTreeSB->Branch("Jet2ResolvedPt", &Jet2ResolvedPt, "Jet2ResolvedPt/D");
    NewTreeSB->Branch("Jet3ResolvedPt", &Jet3ResolvedPt, "Jet3ResolvedPt/D");
    NewTreeSB->Branch("Jet1PartialPt", &Jet1PartialPt, "Jet1PartialPt/D");
    NewTreeSB->Branch("Jet2PartialPt", &Jet2PartialPt, "Jet2PartialPt/D");
    NewTreeSB->Branch("Jet1MergedPt", &Jet1MergedPt, "Jet1MergedPt/D");
    NewTreeSB->Branch("MostForwardJetEta", &MostForwardJetEta,
                      "MostForwardJetEta/D");
    NewTreeSB->Branch("MostForwardJetPt", &MostForwardJetPt,
                      "MostForwardJetPt/D");
    NewTreeSB->Branch("Jet1ResolvedEta", &Jet1ResolvedEta, "Jet1ResolvedEta/D");
    NewTreeSB->Branch("Jet2ResolvedEta", &Jet2ResolvedEta, "Jet2ResolvedEta/D");
    NewTreeSB->Branch("Jet3ResolvedEta", &Jet3ResolvedEta, "Jet3ResolvedEta/D");
    NewTreeSB->Branch("Jet1PartialEta", &Jet1PartialEta, "Jet1PartialEta/D");
    NewTreeSB->Branch("Jet2PartialEta", &Jet2PartialEta, "Jet2PartialEta/D");
    NewTreeSB->Branch("Jet1MergedEta", &Jet1MergedEta, "Jet1MergedEta/D");
    NewTreeSB->Branch("deltaRZTop", &deltaRZTop, "deltaRZTop/D");
    NewTreeSB->Branch("deltaREle1Ele2", &deltaREle1Ele2, "deltaREle1Ele2/D");
    NewTreeSB->Branch("deltaRMuo1Muo2", &deltaRMuo1Muo2, "deltaRMuo1Muo2/D");
    NewTreeSB->Branch("Massb1b2", &Massb1b2, "Massb1b2/D");
    // NewTreeSB->Branch("MinDeltaPhiJetMet", &MinDeltaPhiJetMet,
                      // "MinDeltaPhiJetMet/D");
    NewTreeSB->Branch("MinDeltaPhiBoostedJetMet", &MinDeltaPhiBoostedJetMet,
                      "MinDeltaPhiBoostedJetMet/D");
    NewTreeSB->Branch("deltaRb1b2", &deltaRb1b2, "deltaRb1b2/D");
    NewTreeSB->Branch("deltaRb1Lep1", &deltaRb1Lep1, "deltaRb1Lep1/D");
    NewTreeSB->Branch("deltaRb1Lep2", &deltaRb1Lep2, "deltaRb1Lep2/D");
    NewTreeSB->Branch("deltaRb2Lep1", &deltaRb2Lep1, "deltaRb2Lep1/D");
    NewTreeSB->Branch("deltaRb2Lep2", &deltaRb2Lep2, "deltaRb2Lep2/D");
    NewTreeSB->Branch("leptonsL_number", &leptonsL_number, "leptonsL_number/I");
    //
    //
    NewTreeSB->Branch("eleL_number", &eleL_number, "eleL_number");
    NewTreeSB->Branch("muonsL_number", &muonsL_number, "muonsL_number");
    NewTreeSB->Branch("jetsL_invariantMass", &jetsL_invariantMass,
                      "jetsL_invariantMass/D");
    NewTreeSB->Branch("jetsL_centrality", &jetsL_centrality,
                      "jetsL_centrality/D");
    NewTreeSB->Branch("Aplanarity", &Aplanarity, "Aplanarity/D");
    //
    //
    NewTreeSB->Branch("jetsL_number", &jetsL_number, "jetsL_number/I");
    NewTreeSB->Branch("forwardJets_num", &forwardJets_num, "forwardJets_num/I");
    NewTreeSB->Branch("bjetsL_num", &bjetsL_num, "bjetsL_num/I");
    NewTreeSB->Branch("bjetsM_num", &bjetsM_num, "bjetsM_num/I");
    NewTreeSB->Branch("bjetsT_num", &bjetsT_num, "bjetsT_num/I");
    NewTreeSB->Branch("NumSelWJets", &NumSelWJets, "NumSelWJets/I");
    NewTreeSB->Branch("NumSelTopJets", &NumSelTopJets, "NumSelTopJets/I");
    NewTreeSB->Branch("NVertices", &NVertices, "NVertices/I");
    NewTreeSB->Branch("jetsL_HT", &jetsL_HT, "jetsL_HT/D");
    NewTreeSB->Branch("jetsL_MHT", &jetsL_MHT, "jetsL_MHT/D");
    NewTreeSB->Branch("PUWeight", &PUWeight, "PUWeight/D");
    NewTreeSB->Branch("PUWeightUP", &PUWeightUP, "PUWeightUP/D");
    NewTreeSB->Branch("PUWeightDOWN", &PUWeightDOWN, "PUWeightDOWN/D");
    NewTreeSB->Branch("getTrueNumInteractions", &getTrueNumInteractions,
                      "getTrueNumInteractions/I");
    NewTreeSB->Branch("w_for", &w_for, "w_for/D");
    NewTreeSB->Branch("w_forUp", &w_forUp, "w_forUp/D");
    NewTreeSB->Branch("w_forDown", &w_forDown, "w_forDown/D");
    NewTreeSB->Branch("w_topJet", &w_topJet, "w_topJet/D");
    NewTreeSB->Branch("w_topJetUp", &w_topJetUp, "w_topJetUp/D");
    NewTreeSB->Branch("w_topJetDown", &w_topJetDown, "w_topJetDown/D");
    NewTreeSB->Branch("w_WJet", &w_WJet, "w_WJet/D");
    NewTreeSB->Branch("w_WJetUp", &w_WJetUp, "w_WJetUp/D");
    NewTreeSB->Branch("w_WJetDown", &w_WJetDown, "w_WJetDown/D");
    NewTreeSB->Branch("w_Muon1", &w_Muon1, "w_Muon1/D");
    NewTreeSB->Branch("w_Muon2", &w_Muon2, "w_Muon2/D");
    NewTreeSB->Branch("w_Muon1Up", &w_Muon1Up, "w_Muon1Up/D");
    NewTreeSB->Branch("w_Muon2Up", &w_Muon2Up, "w_Muon2Up/D");
    NewTreeSB->Branch("w_Muon1Down", &w_Muon1Down, "w_Muon1Down/D");
    NewTreeSB->Branch("w_Muon2Down", &w_Muon2Down, "w_Muon2Down/D");
    NewTreeSB->Branch("w_TrigMuon", &w_TrigMuon, "w_TrigMuon/D");
    NewTreeSB->Branch("w_TrigMuonUp", &w_TrigMuonUp, "w_TrigMuonUp/D");
    NewTreeSB->Branch("w_TrigMuonDown", &w_TrigMuonDown, "w_TrigMuonDown/D");
    NewTreeSB->Branch("w_Electron1", &w_Electron1, "w_Electron1/D");
    NewTreeSB->Branch("w_Electron2", &w_Electron2, "w_Electron2/D");
    NewTreeSB->Branch("w_Electron1Up", &w_Electron1Up, "w_Electron1Up/D");
    NewTreeSB->Branch("w_Electron2Up", &w_Electron2Up, "w_Electron2Up/D");
    NewTreeSB->Branch("w_Electron1Down", &w_Electron1Down, "w_Electron1Down/D");
    NewTreeSB->Branch("w_Electron2Down", &w_Electron2Down, "w_Electron2Down/D");
    NewTreeSB->Branch("w_TrigElec", &w_TrigElec, "w_TrigElec/D");
    NewTreeSB->Branch("w_TrigElecUp", &w_TrigElecUp, "w_TrigElecUp/D");
    NewTreeSB->Branch("w_TrigElecDown", &w_TrigElecDown, "w_TrigElecDown/D");
    NewTreeSB->Branch("w_ZToNuNu", &w_ZToNuNu, "w_ZToNuNu/D");
    NewTreeSB->Branch("w_ZToNuNuUp", &w_ZToNuNuUp, "w_ZToNuNuUp/D");
    NewTreeSB->Branch("w_ZToNuNuDown", &w_ZToNuNuDown, "w_ZToNuNuDown/D");
    NewTreeSB->Branch("w_WToLNu", &w_WToLNu, "w_WToLNu/D");
    NewTreeSB->Branch("w_WToLNuUp", &w_WToLNuUp, "w_WToLNuUp/D");
    NewTreeSB->Branch("w_WToLNuDown", &w_WToLNuDown, "w_WToLNuDown/D");
    NewTreeSB->Branch("w_ttbar", &w_ttbar, "w_ttbar/D");
    NewTreeSB->Branch("w_ttbarUp", &w_ttbarUp, "w_ttbarUp/D");
    NewTreeSB->Branch("w_ttbarDown", &w_ttbarDown, "w_ttbarDown/D");
    NewTreeSB->Branch("w_Trig", &w_Trig, "w_Trig/D");
    NewTreeSB->Branch("w_TrigUp", &w_TrigUp, "w_TrigUp/D");
    NewTreeSB->Branch("w_TrigDown", &w_TrigDown, "w_TrigDown/D");
    NewTreeSB->Branch("WMass", &WMass, "WMass/D");
    NewTreeSB->Branch("WSubjet", &WSubjet, "WSubjet/D");
    NewTreeSB->Branch("TopSoftMass", &TopSoftMass, "TopSoftMass/D");
    NewTreeSB->Branch("TopSubjet", &TopSubjet, "TopSubjet/D");
    NewTreeSB->Branch("w_Btag", &w_Btag, "w_Btag/D");
    NewTreeSB->Branch("w_BtagUp", &w_BtagUp, "w_BtagUp/D");
    NewTreeSB->Branch("w_BtagDown", &w_BtagDown, "w_BtagDown/D");
    NewTreeSB->Branch("w_Btag1Up", &w_Btag1Up, "w_Btag1Up/D");
    NewTreeSB->Branch("w_Btag1Down", &w_Btag1Down, "w_Btag1Down/D");
    NewTreeSB->Branch("w_Btag2Up", &w_Btag2Up, "w_Btag2Up/D");
    NewTreeSB->Branch("w_Btag2Down", &w_Btag2Down, "w_Btag2Down/D");
    NewTreeSB->Branch("w_BtagLoose", &w_BtagLoose, "w_BtagLoose/D");
    NewTreeSB->Branch("w_BtagLooseUp", &w_BtagLooseUp, "w_BtagLooseUp/D");
    NewTreeSB->Branch("w_BtagLooseDown", &w_BtagLooseDown, "w_BtagLooseDown/D");
    NewTreeSB->Branch("w_QCDUp", &w_QCDUp, "w_QCDUp/D");
    NewTreeSB->Branch("w_QCDDown", &w_QCDDown, "w_QCDDown/D");
    NewTreeSB->Branch("w_PDFUp", &w_PDFUp, "w_PDFUp/D");
    NewTreeSB->Branch("w_PDFDown", &w_PDFDown, "w_PDFDown/D");
    NewTreeSB->Branch("deltaPhiZTopResolved", &deltaPhiZTopResolved,
                      "deltaPhiZTopResolved/D");
    NewTreeSB->Branch("deltaRZTopResolved", &deltaRZTopResolved,
                      "deltaRZTopResolved/D");
    NewTreeSB->Branch("deltaPhiZTopPartial", &deltaPhiZTopPartial,
                      "deltaPhiZTopPartial/D");
    NewTreeSB->Branch("deltaRZTopPartial", &deltaRZTopPartial,
                      "deltaRZTopPartial/D");
    NewTreeSB->Branch("deltaPhiZTopMerged", &deltaPhiZTopMerged,
                      "deltaPhiZTopMerged/D");
    NewTreeSB->Branch("deltaRZTopMerged", &deltaRZTopMerged,
                      "deltaRZTopMerged/D");
    NewTreeSB->Branch("deltaRbTop", &deltaRbTop, "deltaRbTop/D");
    NewTreeSB->Branch("deltaPhiMetTop", &deltaPhiMetTop, "deltaPhiMetTop/D");
    NewTreeSB->Branch("genWeight", &genWeight, "genWeight/D");
    NewTreeSB->Branch("dQuark", &dQuark, "dQuark/I");
    NewTreeSB->Branch("uQuark", &uQuark, "uQuark/I");
    NewTreeSB->Branch("sQuark", &sQuark, "sQuark/I");
    NewTreeSB->Branch("cQuark", &cQuark, "cQuark/I");
    NewTreeSB->Branch("bQuark", &bQuark, "bQuark/I");
    NewTreeSB->Branch("tQuark", &tQuark, "tQuark/I");
    NewTreeSB->Branch("EVENT_event", &EVENT_event, "EVENT_event/I");
    NewTreeSB->Branch("EVENT_run", &EVENT_run, "EVENT_run/I");
    NewTreeSB->Branch("EVENT_lumiBlock", &EVENT_lumiBlock, "EVENT_lumiBlock/I");
    NewTreeSB->Branch("EVENT_genHT", &EVENT_genHT, "EVENT_genHT/D");
    NewTreeSB->Branch("prefiringweight", &prefiringweight, "prefiringweight/D");
    NewTreeSB->Branch("prefiringweightup", &prefiringweightup,
                      "prefiringweightup/D");
    NewTreeSB->Branch("prefiringweightdown", &prefiringweightdown,
                      "prefiringweightdown/D");
    NewTreeSB->Branch("Met_pt", &Met_pt, "Met_pt/D");
    NewTreeSB->Branch("Met_phi", &Met_phi, "Met_phi/D");
    NewTreeSB->Branch("TransverseMassMetTop", &TransverseMassMetTop,
                      "TransverseMassMetTop/D");
  }
} /*}}}*/

void initializeVar() { /*{{{*/

 HLT_PFHT900 = -99; 
 HLT_PFHT450_SixJet40_BTagCSV_p056 = -99; 
 HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = -99; 
 HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg = -99;  
 HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg = -99;  
 HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg = -99;   
 HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg = -99;  
 HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg = -99;  
 HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg = -99;  
 HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg = -99;  
 HLT_Ele27_eta2p1_WPTight_Gsf = -99;  
 HLT_Ele27_eta2p1_WPLoose_Gsf =-99;
 HLT_Ele27_WPTight_Gsf = -99;  
 HLT_IsoMu22 = -99;  
 HLT_Ele25_eta2p1_WPTight_Gsf = -99;  
 HLT_IsoTkMu22 = -99;  
 HLT_IsoMu24 = -99;  
 HLT_IsoTkMu24 = -99;  
 HLT_IsoMu22_eta2p1 = -99;  
 HLT_IsoTkMu22_eta2p1 = -99;  
 HLT_Mu50 = -99;  
 HLT_TkMu50 = -99;  
 HLT_Ele32_WPTight_Gsf = -99;  
 HLT_Ele35_WPTight_Gsf = -99;  
 HLT_IsoMu27 = -99;  

    HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20 = -99; 
    HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1 = -99; 
    HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30 = -99; 
    HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1 = -99; 
    HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1 = -99; 
    HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1 = -99; 
    HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1 = -99; 
    HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1 = -99; 

    HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf = -99; 
    HLT_DoubleEle33_CaloIdL_MW = -99; 
    HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW = -99; 
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = -99; 
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = -99; 
    HLT_DoubleMu33NoFiltersNoVtx = -99; 
    HLT_DoubleMu23NoFiltersNoVtxDisplaced = -99; 
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = -99; 
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 = -99; 
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL = -99;
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = -99;
    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL = -99; 
    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = -99; 
    HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL = -99;
    HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ = -99;
    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = -99; 
    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = -99; 
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL = -99; 
    HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = -99; 

    HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL = -99; 
    HLT_Mu8_DiEle12_CaloIdL_TrackIdL = -99; 
    HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ = -99; 
    HLT_TripleMu_12_10_5 = -99; 
    HLT_DiMu9_Ele9_CaloIdL_TrackIdL = -99; 


    genTaus_number = -99;
 genEles_number = -99;
 genEle_pt.clear();
 genEle_eta.clear();
 genEle_phi.clear();
 genEle_E.clear();
 genMuons_number = -99;
 genMuon_pt.clear();
 genMuon_eta.clear();
 genMuon_phi.clear();
 genMuon_E.clear();

 TopMass=-99;
 TopMassMerged=-99;
 TopMassPartial=-99;
 TopMassResolved=-99;
 TopPt=-99;
 TopPtMerged=-99;
 TopPtPartial=-99;
 TopPtResolved=-99;
 TopEta=-99;
 TopEtaMerged=-99;
 TopEtaPartial=-99;
 TopEtaResolved=-99;
 TopPhi=-99;
 TopPhiMerged=-99;
 TopPhiPartial=-99;
 TopPhiResolved=-99;
 WMassResolved1=-99;
 WMassResolved2=-99;
 WMassResolved3=-99;
 BMass=-99;
 BCSV=-99;
 BPt=-99;
 BEta=-99;
 BPhi=-99;
 ZMass=-99;
 ZPt=-99;
 ZEta=-99;
 ZPhi=-99;
 Jet1ForwardPt=-99;
 Jet2ForwardPt=-99;
 Jet3ForwardPt=-99;
 Jet1ResolvedPt=-99;
 Jet2ResolvedPt=-99;
 Jet3ResolvedPt=-99;
 Jet1PartialPt=-99;
 Jet2PartialPt=-99;
 Jet1MergedPt=-99;
 Jet1ForwardEta=-99;
 Jet2ForwardEta=-99;
 Jet3ForwardEta=-99;
 Jet1ResolvedEta=-99;
 Jet2ResolvedEta=-99;
 Jet3ResolvedEta=-99;
 Jet1PartialEta=-99;
 Jet2PartialEta=-99;
 Jet1MergedEta=-99;
 MostForwardJetEta=-99;
 MostForwardJetPt=-99;
 deltaPhiZB=-99;
 deltaRZB=-99;
 deltaRZTop=-99;
 deltaPhiZTopResolved=-99;
 deltaRZTopResolved=-99;
 deltaPhiZTopPartial=-99;
 deltaRZTopPartial=-99;
 deltaPhiZTopMerged=-99;
 deltaRZTopMerged=-99;
 deltaRbTop=-99;
 deltaREle1Ele2=-99;
 deltaRMuo1Muo2=-99;
 deltaREle1Ele2M=-99;
 deltaRMuo1Muo2M=-99;
 Massb1b2=-99;
 deltaRb1b2=-99;
 deltaRb1Lep1=-99;
 deltaRb1Lep2=-99;
 deltaRb2Lep1=-99;
 deltaRb2Lep2=-99;
 deltaPhiMetTop=-99.;
 MinDeltaPhiBoostedJetMet=99.;

   leptonsL_number=-99;
 leptonsT_number=-99;
 leptonsT_number_v2=-99;
 leptonsMVAF_number=-99;
 leptonsMVAT_number=-99;
 leptonsMVAL_number=-99;
 leptonsMVAT_transMass = -99;
 leptonsMVAF_transMass = -99;
 leptonsMVAL_transMass = -99;
 elesMVAF_1pt = -99;
 leptonsMVAT_1pt = -99;
 leptonsMVAT_1eta = -99;
 leptonsMVAT_1phi = -99;
 leptonsMVAT_2pt= -99;
 leptonsMVAT_2eta = -99;
 leptonsMVAT_2phi= -99;
 leptonsMVAT_3pt = -99;
 leptonsMVAT_3eta = -99;
 leptonsMVAT_3phi = -99;
   leptonsMVAT_2SS = 0;
   leptonsMVAT_2OS = 0;

 muonsT_number=-99;
   muonsL_number=-99;
  muonsF_number = -99;
  muonsL_number_s0=-99;
  muonsF_number_s0=-99;
  muonsT_number_s0=-99;
  muonsL_number_s1=-99;
  muonsF_number_s1=-99;
  muonsT_number_s1=-99;
  muonsL_number_s2=-99;
  muonsF_number_s2=-99;
  muonsT_number_s2=-99;
  muonsL_number_s3=-99;
  muonsF_number_s3=-99;
  muonsT_number_s3=-99;
  muonL_pt.clear();
  muonL_eta.clear();
  muonL_phi.clear();
  muonL_E.clear();
  muonF_pt.clear();
  muonF_eta.clear();
  muonF_phi.clear();
  muonF_E.clear();
  muonT_pt.clear();
  muonT_eta.clear();
  muonT_phi.clear();
  muonT_E.clear();
  muonL_pt_s0.clear();
  muonL_eta_s0.clear();
  muonL_phi_s0.clear();
  muonL_E_s0.clear();
  muonF_pt_s0.clear();
  muonF_eta_s0.clear();
  muonF_phi_s0.clear();
  muonF_E_s0.clear();
  muonT_pt_s0.clear();
  muonT_eta_s0.clear();
  muonT_phi_s0.clear();
  muonT_E_s0.clear();
  muonL_pt_s1.clear();
  muonL_eta_s1.clear();
  muonL_phi_s1.clear();
  muonL_E_s1.clear();
  muonF_pt_s1.clear();
  muonF_eta_s1.clear();
  muonF_phi_s1.clear();
  muonF_E_s1.clear();
  muonT_pt_s1.clear();
  muonT_eta_s1.clear();
  muonT_phi_s1.clear();
  muonT_E_s1.clear();
  muonL_pt_s2.clear();
  muonL_eta_s2.clear();
  muonL_phi_s2.clear();
  muonL_E_s2.clear();
  muonF_pt_s2.clear();
  muonF_eta_s2.clear();
  muonF_phi_s2.clear();
  muonF_E_s2.clear();
  muonT_pt_s2.clear();
  muonT_eta_s2.clear();
  muonT_phi_s2.clear();
  muonT_E_s2.clear();
  muonL_pt_s3.clear();
  muonL_eta_s3.clear();
  muonL_phi_s3.clear();
  muonL_E_s3.clear();
  muonF_pt_s3.clear();
  muonF_eta_s3.clear();
  muonF_phi_s3.clear();
  muonF_E_s3.clear();
  muonT_pt_s3.clear();
  muonT_eta_s3.clear();
  muonT_phi_s3.clear();
  muonT_E_s3.clear();

 muonsT_1pt = -99;
 muonsT_1eta = -99;
 muonsT_1phi = -99;
 muonsT_2pt = -99;
 muonsT_2eta = -99;
 muonsT_2phi = -99;
 muonsT_3pt = -99;
 muonsT_3eta = -99;
 muonsT_3phi = -99;

 elesMVAL_number=-99;
 elesMVAF_number=-99;
 elesMVAT_number=-99;
 elesMVAL_number_s0=-99;
 elesMVAF_number_s0=-99;
 elesMVAT_number_s0=-99;
 elesMVAL_number_s1=-99;
 elesMVAF_number_s1=-99;
 elesMVAT_number_s1=-99;
 elesMVAL_number_s2=-99;
 elesMVAF_number_s2=-99;
 elesMVAT_number_s2=-99;
 elesMVAL_number_s3=-99;
 elesMVAF_number_s3=-99;
 elesMVAT_number_s3=-99;

 eleMVAL_pt.clear(); 
 eleMVAL_eta.clear();
 eleMVAL_phi.clear();
 eleMVAL_E.clear();
 eleMVAF_pt.clear(); 
 eleMVAF_eta.clear();
 eleMVAF_phi.clear();
 eleMVAF_E.clear();
 eleMVAT_pt.clear(); 
 eleMVAT_eta.clear();
 eleMVAT_phi.clear();
 eleMVAT_E.clear();
 eleMVAL_pt_s0.clear();
 eleMVAL_eta_s0.clear();
 eleMVAL_phi_s0.clear();
 eleMVAL_E_s0.clear();
 eleMVAF_pt_s0.clear();
 eleMVAF_eta_s0.clear();
 eleMVAF_phi_s0.clear();
 eleMVAF_E_s0.clear();
 eleMVAT_pt_s0.clear();
 eleMVAT_eta_s0.clear();
 eleMVAT_phi_s0.clear();
 eleMVAT_E_s0.clear();
 eleMVAL_pt_s1.clear();
 eleMVAL_eta_s1.clear();
 eleMVAL_phi_s1.clear();
 eleMVAL_E_s1.clear();
 eleMVAF_pt_s1.clear();
 eleMVAF_eta_s1.clear();
 eleMVAF_phi_s1.clear();
 eleMVAF_E_s1.clear();
 eleMVAT_pt_s1.clear();
 eleMVAT_eta_s1.clear();
 eleMVAT_phi_s1.clear();
 eleMVAT_E_s1.clear();
 eleMVAL_pt_s2.clear();
 eleMVAL_eta_s2.clear();
 eleMVAL_phi_s2.clear();
 eleMVAL_E_s2.clear();
 eleMVAF_pt_s2.clear();
 eleMVAF_eta_s2.clear();
 eleMVAF_phi_s2.clear();
 eleMVAF_E_s2.clear();
 eleMVAT_pt_s2.clear();
 eleMVAT_eta_s2.clear();
 eleMVAT_phi_s2.clear();
 eleMVAT_E_s2.clear();
 eleMVAL_pt_s3.clear();
 eleMVAL_eta_s3.clear();
 eleMVAL_phi_s3.clear();
 eleMVAL_E_s3.clear();
 eleMVAF_pt_s3.clear();
 eleMVAF_eta_s3.clear();
 eleMVAF_phi_s3.clear();
 eleMVAF_E_s3.clear();
 eleMVAT_pt_s3.clear();
 eleMVAT_eta_s3.clear();
 eleMVAT_phi_s3.clear();
 eleMVAT_E_s3.clear();

//
//
   eleL_number=-99;
   eleM_number=-99;
   eleT_number=-99;
   jetsL_invariantMass=-99;
 bjetsL_invariantMass= -99;
 bjetsM_invariantMass= -99;
 bjetsT_invariantMass= -99;
 jetsL_transMass = -99;
 bjetsL_transMass = -99;
 bjetsM_transMass = -99;
 bjetsT_transMass = -99;
 jetL_minDeltaR = -99;
 bjetsL_minDeltaR = -99;
 bjetsM_minDeltaR = -99;
 bjetsT_minDeltaR = -99;
 bjetsL_leptonsMVAT_minDeltaR = -99;
 bjetsM_leptonsMVAT_minDeltaR = -99;
 bjetsT_leptonsMVAT_minDeltaR = -99;
 bjetsL_tausF_minDeltaR = -99;
   jetsL_centrality=-99;
   Aplanarity=-99;
   Sphericity=-99;
 jetsL_HTDividedByMet=-99;
 MetDividedByHT=-99;
 jetsL_MHTDividedByMet=-99;


 LeadingJetpfDeepFlavourBJetTags=-99;
 SecondJetpfDeepFlavourBJetTags=-99;
 ThirdJetpfDeepFlavourBJetTags=-99;
 jetsL_bScore=-99;

 jetsL_average_deltaR = -99;
 jetsL_4largestBscoreSum = -99;
 jetsL_leading2invariantMass = -99;
 jetsL_rationHT_4toRest = -99;
 MinDeltaPhiJets=-99;
 jetsL_leptonsMVAT_minDeltaR = -99;
 jetsL_tausF_minDeltaR = -99;
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
 bjetsT_4pt = -99;
 bjetsT_4eta = -99;
 bjetsT_4phi = -99;
 bjetsT_3pt = -99;
 bjetsT_3eta = -99;
 bjetsT_3phi = -99;

 forwardjet_1pt = -99;
 forwardjet_1eta = -99;
 forwardjet_1phi = -99;
 forwardjet1_jetsL_minDeltaEta = -99;
 jetsL_1pt = -99;
 jetsL_1phi = -99;
 jetsL_1eta = -99;
 jetsL_2pt = -99;
 jetsL_2eta = -99;
 jetsL_2phi = -99;
 jetsL_3pt = -99;
 jetsL_3eta = -99;
 jetsL_3phi = -99;
 jetsL_4pt = -99;
 jetsL_4eta = -99;
 jetsL_4phi = -99;
 jetsL_5pt = -99;
 jetsL_5eta = -99;
 jetsL_5phi = -99;
 jetsL_6pt = -99;
 jetsL_6eta = -99;
 jetsL_6phi = -99;
 jetsL_7pt = -99;
 jetsL_7eta = -99;
 jetL_7phi = -99;
 jetsL_8pt = -99;
 jetsL_8eta = -99;
 jetsL_8phi = -99;
 jetsL_9pt = -99;
 jetsL_9eta = -99;
 jetsL_9phi = -99;
 jetsL_10pt = -99;
 jetsL_10eta = -99;
 jetsL_10phi = -99;
 jetsL_11pt = -99;
 jetsL_11eta = -99;
 jetsL_11phi = -99;

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
 toptagger_minDeltaR=-99;
 toptagger_maxDeltaR=-99;
 toptagger_scoreAllTops=-99;
 toptagger_leptonsMVAT_minDeltaR=-99;
//
//
   jetsL_number=-99;
   forwardJets_num=-99;
   bjetsL_num=-99;
   bjetsM_num=-99;
   bjetsT_num=-99;
   NumSelWJets=-99;
   NumSelTopJets=-99;
   NVertices=-99;
 jetsL_HT=-99;
 bjetsT_HT=-99;
 bjetsM_HT=-99;
 bjetsL_HT=-99;
 bjetsT_MHT=-99;
 bjetsM_MHT=-99;
 bjetsL_MHT=-99;
 jetsL_MHT=-99;
 PUWeight= -99;
 PUWeightUP= -99;
 PUWeightDOWN= -99;
 EVENT_event=-99;
 EVENT_run=-99;
 EVENT_lumiBlock=-99;
 EVENT_genHT=-99;
 Met_pt = -99.;
 Met_phi = -99.;
 getTrueNumInteractions=-99;
 w_for = -99;
 w_forUp = -99;
 w_forDown = -99;
 w_topJet = -99;
 w_topJetUp = -99;
 w_topJetDown = -99;
 w_WJet   = -99;
 w_WJetUp = -99;
 w_WJetDown = -99;
 w_Muon1  = -99;
 w_Muon2  = -99;
 w_Muon1Up  = -99;
 w_Muon2Up  = -99;
 w_Muon1Down  = -99;
 w_Muon2Down  = -99;
 w_Electron1  = -99;
 w_Electron2  = -99;
 w_Electron1Up  = -99;
 w_Electron2Up  = -99;
 w_Electron1Down  = -99;
 w_Electron2Down  = -99;
 w_TrigMuon= -99;
 w_TrigMuonUp= -99;
 w_TrigMuonDown= -99;
 w_TrigElec= -99;
 w_TrigElecUp= -99;
 w_TrigElecDown= -99;
 w_ZToNuNu= -99;
 w_ZToNuNuUp= -99;
 w_ZToNuNuDown= -99;
 w_WToLNu= -99;
 w_WToLNuUp= -99;
 w_WToLNuDown= -99;
 w_ttbar= -99;
 w_ttbarUp= -99;
 w_ttbarDown= -99;
 w_Trig= -99;
 w_TrigUp= -99;
 w_TrigDown= -99;
 WMass = -99;
 WSubjet = -99;
 TopSoftMass = -99;
 TopSubjet = -99;
 w_Btag= -99;
 w_BtagUp= -99;
 w_BtagDown= -99;
 w_Btag1Up= -99;
 w_Btag1Down= -99;
 w_Btag2Up= -99;
 w_Btag2Down= -99;
 w_BtagLoose= -99;
 w_BtagLooseUp= -99;
 w_BtagLooseDown= -99;
 prefiringweight = -99;
 prefiringweightup = -99;
 prefiringweightdown = -99;
 puWeight = -99;
 EVENT_genWeight = -99;
 GenZPt=-99.;
 GenWPt=-99.;

 genWeight= -99;
 w_QCDUp = -99;
 w_QCDDown = -99;
 w_PDFUp = -99;
 w_PDFDown = -99;
 dQuark=0;
 uQuark=0;
 sQuark=0;
 cQuark=0;
 bQuark=0;
 tQuark=0;
 TriggeringElePt  = -1.;
 TriggeringMuoPt  = -1.;
 TriggeringEleEta = -1.;
 TriggeringMuoEta = -1.;
 TransverseMassMetTop = -99;
} /*}}}*/
  //?filename not occur
  //
// void branchGetEntry(bool data, Long64_t tentry, string fileName){
void branchGetEntry(bool data, Long64_t tentry) { 
    /*{{{*/
  b_Jet_pt->GetEntry(tentry); // is a branch in tree, setadress.
  b_Jet_eta->GetEntry(tentry);
  b_Jet_phi->GetEntry(tentry);
  b_Jet_mass->GetEntry(tentry);
  b_Jet_JesSF->GetEntry(tentry);
  b_Jet_JesSFup->GetEntry(tentry);
  b_Jet_JesSFdown->GetEntry(tentry);
  b_Jet_JerSF->GetEntry(tentry);
  b_Jet_JerSFup->GetEntry(tentry);
  b_Jet_JerSFdown->GetEntry(tentry);
  b_Jet_Uncorr_pt->GetEntry(tentry);
  b_Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags->GetEntry(tentry);
  b_Jet_pfDeepCSVBJetTags->GetEntry(tentry);
  b_Jet_pfDeepFlavourBJetTags->GetEntry(tentry);
  b_Jet_neutralHadEnergyFraction->GetEntry(tentry);
  b_Jet_chargedEmEnergyFraction->GetEntry(tentry);
  b_Jet_neutralEmEnergyFraction->GetEntry(tentry);
  b_Jet_numberOfConstituents->GetEntry(tentry);
  b_Jet_chargedHadronEnergyFraction->GetEntry(tentry);
  b_Jet_chargedMultiplicity->GetEntry(tentry);
  if (!data)
    b_Jet_hadronFlavour->GetEntry(tentry);
  b_Jet_muonEnergyFraction->GetEntry(tentry);
  /*  b_BoostedJet_pt->GetEntry(tentry);
    b_BoostedJet_Uncorr_pt->GetEntry(tentry);
    b_BoostedJet_softdrop_mass->GetEntry(tentry);
    b_BoostedJet_puppi_softdrop_mass->GetEntry(tentry);
    b_BoostedJet_JesSF->GetEntry(tentry);
    b_BoostedJet_JesSFup->GetEntry(tentry);
    b_BoostedJet_JesSFdown->GetEntry(tentry);
    b_BoostedJet_JerSF->GetEntry(tentry);
    b_BoostedJet_JerSFup->GetEntry(tentry);
    b_BoostedJet_JerSFdown->GetEntry(tentry);
    b_BoostedJet_eta->GetEntry(tentry);
    b_BoostedJet_phi->GetEntry(tentry);
    b_BoostedJet_mass->GetEntry(tentry);
    b_BoostedJet_tau1->GetEntry(tentry);
    b_BoostedJet_tau2->GetEntry(tentry);
    b_BoostedJet_tau3->GetEntry(tentry);
    b_BoostedJet_puppi_tau1->GetEntry(tentry);
    b_BoostedJet_puppi_tau2->GetEntry(tentry);
    b_BoostedJet_puppi_tau3->GetEntry(tentry);
    b_BoostedJet_pruned_mass->GetEntry(tentry);
    b_BoostedJet_neutralHadEnergyFraction->GetEntry(tentry);
    b_BoostedJet_neutralEmEnergyFraction->GetEntry(tentry);
    b_BoostedJet_chargedEmEnergyFraction->GetEntry(tentry);
    //b_BoostedJet_neutralEmEmEnergyFraction->GetEntry(tentry);
    b_BoostedJet_numberOfConstituents->GetEntry(tentry);
    b_BoostedJet_chargedHadronEnergyFraction->GetEntry(tentry);
    b_BoostedJet_chargedMultiplicity->GetEntry(tentry);*/
  // b_TopTagging_topMass->GetEntry(tentry);
  // b_TopTagging_minMass->GetEntry(tentry);
  // b_TopTagging_nSubJets->GetEntry(tentry);
  b_patElectron_pt->GetEntry(tentry);
  b_patElectron_eta->GetEntry(tentry);
  b_patElectron_phi->GetEntry(tentry);
  b_patElectron_energy->GetEntry(tentry);
  // b_patElectron_energyCorr->GetEntry(tentry);
  b_patElectron_SCeta->GetEntry(tentry);
  b_patElectron_charge->GetEntry(tentry);
  b_patElectron_Et->GetEntry(tentry);
  b_patElectron_pdgId->GetEntry(tentry);
  b_patElectron_relIsoDeltaBeta->GetEntry(tentry);
  b_patElectron_relIsoRhoEA_Update->GetEntry(tentry);
  b_patElectron_gen_pdgId->GetEntry(tentry);
  b_patElectron_gen_isDirectPromptTauDecayProductFinalState->GetEntry(tentry);
  //->GetEntry(tentry);
  b_patElectron_mvaEleID_Fall17_noIso_V2_wp80->GetEntry(tentry);
  b_patElectron_mvaEleID_Fall17_iso_V2_wp80->GetEntry(tentry);
  b_patElectron_mvaEleID_Fall17_iso_V2_wp90->GetEntry(tentry);
  b_patElectron_mvaEleID_Fall17_noIso_V2_wp90->GetEntry(tentry);
  b_patElectron_mvaEleID_Fall17_iso_V2_wpLoose->GetEntry(tentry);
  b_patElectron_mvaEleID_Fall17_noIso_V2_wpLoose->GetEntry(tentry);
  b_patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Values->GetEntry(tentry);
  b_patElectron_ElectronMVAEstimatorRun2Fall17NoIsoV2Categories->GetEntry(
      tentry);
  b_patElectron_ElectronMVAEstimatorRun2Fall17IsoV2Values->GetEntry(tentry);
  b_patElectron_ElectronMVAEstimatorRun2Fall17IsoV2Categories->GetEntry(tentry);
  b_patElectron_mvaEleID_Spring16_GeneralPurpose_V1_wp80->GetEntry(tentry);
  b_patElectron_mvaEleID_Spring16_GeneralPurpose_V1_wp90->GetEntry(tentry);
  b_patElectron_MVAValue_ElectronMVAEstimatorRun2Spring16GeneralPurposeV1
      ->GetEntry(tentry);
  b_patElectron_cutBasedElectronID_Fall17_94X_V2_loose->GetEntry(tentry);
  b_patElectron_cutBasedElectronID_Fall17_94X_V2_medium->GetEntry(tentry);
  b_patElectron_cutBasedElectronID_Fall17_94X_V2_tight->GetEntry(tentry);
  b_patElectron_cutBasedElectronID_Fall17_94X_V2_veto->GetEntry(tentry);
  b_patElectron_heepElectronID_HEEPV70->GetEntry(tentry);

  b_patElectron_miniIsoRel->GetEntry(tentry);
  b_patElectron_jetptratio->GetEntry(tentry);
  b_patElectron_ptrel->GetEntry(tentry);
  b_patElectron_d0->GetEntry(tentry);
  b_patElectron_gsfTrack_dz_pv->GetEntry(tentry);
  b_patElectron_IP3D_sig->GetEntry(tentry);

  //  ->GetEntry(tentry);
  /*  b_patElectron_isPassVeto->GetEntry(tentry);
    b_patElectron_isPassLoose->GetEntry(tentry);
    b_patElectron_isPassMedium->GetEntry(tentry);
    b_patElectron_isPassTight->GetEntry(tentry);
    b_patElectron_isPassHEEPId->GetEntry(tentry);*/
  b_patElectron_passConversionVeto->GetEntry(tentry);
  b_patElectron_inCrack->GetEntry(tentry);
  b_patElectron_isMatchedToTrigger->GetEntry(tentry);
  b_Muon_pt->GetEntry(tentry);
  b_Muon_eta->GetEntry(tentry);
  b_Muon_phi->GetEntry(tentry);
  b_Muon_energy->GetEntry(tentry);
  b_Muon_charge->GetEntry(tentry);
  b_Muon_tight->GetEntry(tentry);
  b_Muon_loose->GetEntry(tentry);
  b_Muon_medium->GetEntry(tentry);
  b_Muon_relIsoDeltaBetaR04->GetEntry(tentry);
  b_Muon_miniIsoRel->GetEntry(tentry);
  b_Muon_ptrel->GetEntry(tentry);
  b_Muon_jetptratio->GetEntry(tentry);
  b_Muon_jetptratioV2->GetEntry(tentry);
  
  b_Muon_isMatchedToTrigger->GetEntry(tentry);
  b_Muon_dz_pv->GetEntry(tentry);

  b_Muon_dxy_bt->GetEntry(tentry);
  b_Muon_dz_bt->GetEntry(tentry);
  b_Muon_IP3D_sig->GetEntry(tentry);

  b_TopTagger_type->GetEntry(tentry);
  b_TopTagger_discriminator->GetEntry(tentry);
  b_TopTagger_jet1Idx->GetEntry(tentry);
  b_TopTagger_jet2Idx->GetEntry(tentry);
  b_TopTagger_jet3Idx->GetEntry(tentry);

  b_Tau_pt->GetEntry(tentry);
  b_Tau_eta->GetEntry(tentry);
  b_Tau_leadChargedCandDz_pv->GetEntry(tentry);
  b_Tau_packedLeadTauCand_dz->GetEntry(tentry);
  b_Tau_phi->GetEntry(tentry);
  b_Tau_energy->GetEntry(tentry);
  b_Tau_px->GetEntry(tentry);
  b_Tau_pz->GetEntry(tentry);
  b_Tau_p->GetEntry(tentry);
  b_Tau_charge->GetEntry(tentry);
  b_Tau_decayModeFinding->GetEntry(tentry);
  b_Tau_decayModeFindingNewDMs->GetEntry(tentry);
  b_Tau_decayMode->GetEntry(tentry);
  b_Tau_againstMuonLoose3->GetEntry(tentry);
  b_Tau_againstMuonTight3->GetEntry(tentry);
  b_Tau_byDeepTau2017v2p1VSjetraw->GetEntry(tentry);
  b_Tau_byVVVLooseDeepTau2017v2p1VSjet->GetEntry(tentry);
  b_Tau_byVVLooseDeepTau2017v2p1VSjet->GetEntry(tentry);
  b_Tau_byVLooseDeepTau2017v2p1VSjet->GetEntry(tentry);
  b_Tau_byLooseDeepTau2017v2p1VSjet->GetEntry(tentry);
  b_Tau_byMediumDeepTau2017v2p1VSjet->GetEntry(tentry);
  b_Tau_byTightDeepTau2017v2p1VSjet->GetEntry(tentry);
  b_Tau_byVTightDeepTau2017v2p1VSjet->GetEntry(tentry);
  b_Tau_byVVTightDeepTau2017v2p1VSjet->GetEntry(tentry);
  b_Tau_byDeepTau2017v2p1VSmuraw->GetEntry(tentry);
  b_Tau_byVLooseDeepTau2017v2p1VSmu->GetEntry(tentry);
  b_Tau_byLooseDeepTau2017v2p1VSmu->GetEntry(tentry);
  b_Tau_byMediumDeepTau2017v2p1VSmu->GetEntry(tentry);
  b_Tau_byTightDeepTau2017v2p1VSmu->GetEntry(tentry);
  b_Tau_byDeepTau2017v2p1VSeraw->GetEntry(tentry);
  b_Tau_byVVVLooseDeepTau2017v2p1VSe->GetEntry(tentry);
  b_Tau_byVVLooseDeepTau2017v2p1VSe->GetEntry(tentry);
  b_Tau_byVLooseDeepTau2017v2p1VSe->GetEntry(tentry);
  b_Tau_byLooseDeepTau2017v2p1VSe->GetEntry(tentry);
  b_Tau_byMediumDeepTau2017v2p1VSe->GetEntry(tentry);
  b_Tau_byTightDeepTau2017v2p1VSe->GetEntry(tentry);
  b_Tau_byVTightDeepTau2017v2p1VSe->GetEntry(tentry);
  b_Tau_byVVTightDeepTau2017v2p1VSe->GetEntry(tentry);
  //  ->GetEntry(tentry);
  b_Met_type1PF_pt->GetEntry(tentry);
  b_Met_type1PF_phi->GetEntry(tentry);
  b_Met_type1PF_sumEt->GetEntry(tentry);
  b_HLT_DoubleEle33_CaloIdL_MW->GetEntry(tentry);
  b_HLT_Mu50->GetEntry(tentry);
  b_HLT_TkMu50->GetEntry(tentry);
  //
  //
  b_HLT_PFHT900->GetEntry(tentry);
  b_HLT_PFHT450_SixJet40_BTagCSV_p056->GetEntry(tentry);
  b_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056->GetEntry(tentry);
 b_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg->GetEntry(tentry);
 b_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg->GetEntry(tentry);
 b_HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg->GetEntry(tentry);
 b_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg->GetEntry(tentry);
 b_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg->GetEntry(tentry);
 b_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg->GetEntry(tentry);
 b_HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg->GetEntry(tentry);

 b_HLT_Ele27_eta2p1_WPTight_Gsf->GetEntry(tentry);
 b_HLT_Ele27_eta2p1_WPLoose_Gsf->GetEntry(tentry);
 b_HLT_Ele27_WPTight_Gsf->GetEntry(tentry);
 b_HLT_IsoMu22->GetEntry(tentry);
 b_HLT_Ele25_eta2p1_WPTight_Gsf->GetEntry(tentry);
 b_HLT_IsoTkMu22->GetEntry(tentry);
 b_HLT_IsoMu24->GetEntry(tentry);
 b_HLT_IsoTkMu24->GetEntry(tentry);
 b_HLT_IsoMu22_eta2p1->GetEntry(tentry);
 b_HLT_IsoTkMu22_eta2p1->GetEntry(tentry);
 b_HLT_Mu50->GetEntry(tentry);
 b_HLT_TkMu50->GetEntry(tentry);
 b_HLT_Ele32_WPTight_Gsf->GetEntry(tentry);
 b_HLT_Ele35_WPTight_Gsf->GetEntry(tentry);
 b_HLT_IsoMu27->GetEntry(tentry);

    b_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20->GetEntry(tentry);
    b_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1->GetEntry(tentry);
    b_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30->GetEntry(tentry);
    b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1->GetEntry(tentry);
    b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1->GetEntry(tentry);
    b_HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1->GetEntry(tentry);
    b_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1->GetEntry(tentry);
    b_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1->GetEntry(tentry);

    b_HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf->GetEntry(tentry);
    b_HLT_DoubleEle33_CaloIdL_MW->GetEntry(tentry);
    b_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW->GetEntry(tentry);
    b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ->GetEntry(tentry);
    b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL->GetEntry(tentry);
    b_HLT_DoubleMu33NoFiltersNoVtx->GetEntry(tentry);
    b_HLT_DoubleMu23NoFiltersNoVtxDisplaced->GetEntry(tentry);
    b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ->GetEntry(tentry);
    b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8->GetEntry(tentry);
    b_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL->GetEntry(tentry);
    b_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ->GetEntry(tentry);
    b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL->GetEntry(tentry);
    b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ->GetEntry(tentry);
    b_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL->GetEntry(tentry);
    b_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ->GetEntry(tentry);
    b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL->GetEntry(tentry);
    b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ->GetEntry(tentry);
    b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL->GetEntry(tentry);
    b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ->GetEntry(tentry);

    b_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL->GetEntry(tentry);
    b_HLT_Mu8_DiEle12_CaloIdL_TrackIdL->GetEntry(tentry);
    b_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ->GetEntry(tentry);
    b_HLT_TripleMu_12_10_5->GetEntry(tentry);
    b_HLT_DiMu9_Ele9_CaloIdL_TrackIdL->GetEntry(tentry);




  //
  //
  b_Flag_goodVertices->GetEntry(tentry);
  // b_Flag_CSCTightHalo2015Filter->GetEntry(tentry);
  b_Flag_HBHENoiseFilter->GetEntry(tentry);
  b_Flag_HBHENoiseIsoFilter->GetEntry(tentry);
  b_Flag_EcalDeadCellTriggerPrimitiveFilter->GetEntry(tentry);
  b_Flag_BadPFMuonFilter->GetEntry(tentry);
  b_Flag_BadChargedCandidateFilter->GetEntry(tentry);
  //  b_Flag_ecalBadCalibReducedMINIAODFilter->GetEntry(tentry);
  b_Flag_eeBadScFilter->GetEntry(tentry);
  b_Flag_METFilters->GetEntry(tentry); // add
  b_Flag_globalSuperTightHalo2016Filter->GetEntry(tentry);
  b_nBestVtx->GetEntry(tentry);
  b_PUWeight->GetEntry(tentry);
  // b_PUWeightUP->GetEntry(tentry);
  // b_PUWeightDOWN->GetEntry(tentry);
  b_EVENT_run->GetEntry(tentry);
  b_EVENT_event->GetEntry(tentry);
  b_EVENT_lumiBlock->GetEntry(tentry);
  b_EVENT_genHT->GetEntry(tentry);
  b_EVENT_prefireWeight->GetEntry(tentry);
  b_EVENT_prefireWeightUp->GetEntry(tentry);
  b_EVENT_prefireWeightDown->GetEntry(tentry);
  b_PUWeight->GetEntry(tentry);
  b_genWeight->GetEntry(tentry);
  if (!data)
    b_Gen_pt->GetEntry(tentry);
  if (!data)
    b_Gen_eta->GetEntry(tentry);
  if (!data)
    b_Gen_phi->GetEntry(tentry);
  if (!data)
    b_Gen_charge->GetEntry(tentry);
  if (!data)
    b_Gen_energy->GetEntry(tentry);
  if (!data)
    b_Gen_pdg_id->GetEntry(tentry);
  if (!data)
    b_Gen_motherpdg_id->GetEntry(tentry);
  b_genWeights->GetEntry(tentry);
} /*}}}*/

void HistoFill(double puweight, TTree *NewTree) {
  // has nothing to do with puweigh,why use puweight then?
  NewTree->Fill();
}
/*
void writeFile(TTree *NewTree,TTree *NewTreeSB){
  NewTree->Write();
  NewTreeSB->Write();
}*/

void GenClassifier(double &GenZPt_, double &GenWPt_) { /*{{{*/
  for (UInt_t j = 0; j < Gen_pt_->size(); ++j) {
    // cout<<j<<" "<<Gen_pdg_id_->at(j)<<" "<<Gen_motherpdg_id_->at(j)<<"
    // "<<Gen_pt_->at(j)<<endl;
    // std::string::at can be used to extract characters by characters from a
    //?what is Gen_pt? is Gen_pt of the final state? if so, how can we have Z
    // and W ?
    if (abs(Gen_pdg_id_->at(j)) == 1 &&
        (abs(Gen_motherpdg_id_->at(j)) == 2212 ||
         abs(Gen_motherpdg_id_->at(j)) == 21))
      dQuark = dQuark + 1; // dQuark a branch in newtree and newtreeSB
    if (abs(Gen_pdg_id_->at(j)) == 2 &&
        (abs(Gen_motherpdg_id_->at(j)) == 2212 ||
         abs(Gen_motherpdg_id_->at(j)) == 21))
      uQuark = uQuark + 1;
    if (abs(Gen_pdg_id_->at(j)) == 3 &&
        (abs(Gen_motherpdg_id_->at(j)) == 2212 ||
         abs(Gen_motherpdg_id_->at(j)) == 21))
      sQuark = sQuark + 1;
    if (abs(Gen_pdg_id_->at(j)) == 4 &&
        (abs(Gen_motherpdg_id_->at(j)) == 2212 ||
         abs(Gen_motherpdg_id_->at(j)) == 21))
      cQuark = cQuark + 1;
    if (abs(Gen_pdg_id_->at(j)) == 5 &&
        (abs(Gen_motherpdg_id_->at(j)) == 2212 ||
         abs(Gen_motherpdg_id_->at(j)) == 21))
      bQuark = bQuark + 1;
    if (abs(Gen_pdg_id_->at(j)) == 6 &&
        (abs(Gen_motherpdg_id_->at(j)) == 2212 ||
         abs(Gen_motherpdg_id_->at(j)) == 21))
      tQuark = tQuark + 1;
    if (abs(Gen_pdg_id_->at(j)) == 23)
      GenZPt_ = Gen_pt_->at(j); // in function GenWeight
    if (abs(Gen_pdg_id_->at(j)) == 24)
      GenWPt_ = Gen_pt_->at(j);
  }
} /*}}}*/

void GenWBoson(bool &matched, TLorentzVector Wjet) { /*{{{*/
  double dr1 = 99;
  double dr2 = 99;
  double dr3 = 99;
  double dr4 = 99;
  double dr5 = 99;
  double dr6 = 99;
  double dr7 = 99;
  double dr8 = 99;
  double dr9 = 99;
  double dr10 = 99;
  double dr11 = 99;
  double dr12 = 99;
  double dr13 = 99;
  double dr14 = 99;
  double dr15 = 99;
  double dr16 = 99;
  double dr17 = 99;
  double dr18 = 99;
  for (UInt_t j = 0; j < Gen_pt_->size(); ++j) {
    // cout<<j<<" "<<Gen_pdg_id_->at(j)<<" "<<Gen_motherpdg_id_->at(j)<<"
    // "<<Gen_pt_->at(j)<<endl;
    if (abs(Gen_pdg_id_->at(j)) == 1 && abs(Gen_motherpdg_id_->at(j)) == 24)
      dr1 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if (abs(Gen_pdg_id_->at(j)) == 2 && abs(Gen_motherpdg_id_->at(j)) == 24)
      dr2 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if (abs(Gen_pdg_id_->at(j)) == 3 && abs(Gen_motherpdg_id_->at(j)) == 24)
      dr3 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if (abs(Gen_pdg_id_->at(j)) == 4 && abs(Gen_motherpdg_id_->at(j)) == 24)
      dr4 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if (abs(Gen_pdg_id_->at(j)) == 5 && abs(Gen_motherpdg_id_->at(j)) == 24)
      dr5 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if (abs(Gen_pdg_id_->at(j)) == 6 && abs(Gen_motherpdg_id_->at(j)) == 24)
      dr6 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if ((Gen_pdg_id_->at(j)) == 1 && abs(Gen_motherpdg_id_->at(j)) == 23)
      dr7 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if ((Gen_pdg_id_->at(j)) == 2 && abs(Gen_motherpdg_id_->at(j)) == 23)
      dr8 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if ((Gen_pdg_id_->at(j)) == 3 && abs(Gen_motherpdg_id_->at(j)) == 23)
      dr9 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if ((Gen_pdg_id_->at(j)) == 4 && abs(Gen_motherpdg_id_->at(j)) == 23)
      dr10 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if ((Gen_pdg_id_->at(j)) == 5 && abs(Gen_motherpdg_id_->at(j)) == 23)
      dr11 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if ((Gen_pdg_id_->at(j)) == 6 && abs(Gen_motherpdg_id_->at(j)) == 23)
      dr12 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if ((Gen_pdg_id_->at(j)) == -1 && abs(Gen_motherpdg_id_->at(j)) == 23)
      dr13 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if ((Gen_pdg_id_->at(j)) == -2 && abs(Gen_motherpdg_id_->at(j)) == 23)
      dr14 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if ((Gen_pdg_id_->at(j)) == -3 && abs(Gen_motherpdg_id_->at(j)) == 23)
      dr15 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if ((Gen_pdg_id_->at(j)) == -4 && abs(Gen_motherpdg_id_->at(j)) == 23)
      dr16 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if ((Gen_pdg_id_->at(j)) == -5 && abs(Gen_motherpdg_id_->at(j)) == 23)
      dr17 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
    if ((Gen_pdg_id_->at(j)) == -6 && abs(Gen_motherpdg_id_->at(j)) == 23)
      dr18 = DeltaR(Wjet.Eta(), Gen_eta_->at(j), Wjet.Phi(), Gen_phi_->at(j));
  }
  if ((dr2 < 0.8 && dr1 < 0.8) || (dr2 < 0.8 && dr3 < 0.8) ||
      (dr2 < 0.8 && dr5 < 0.8))
    matched = true; // W -> ud/us/ub
  if ((dr4 < 0.8 && dr1 < 0.8) || (dr4 < 0.8 && dr3 < 0.8) ||
      (dr4 < 0.8 && dr5 < 0.8))
    matched = true; // W -> cd/cs/cb
  // if((dr7 <0.8 && dr13<0.8) || (dr8 <0.8 && dr14<0.8) || (dr9 <0.8 &&
  // dr15<0.8)) matched=true; //Z -> dd/uu/ss
  // if((dr10<0.8 && dr16<0.8) || (dr11<0.8 && dr17<0.8) || (dr12<0.8 &&
  // dr18<0.8)) matched=true; //Z -> cc/bb/tt
} /*}}}*/

//?what is GenWeight doing?
/*
void GenWeight(string fileName, double GenZPt_,double GenWPt_){
  genWeight=(genWeight_)/abs(genWeight_);// genWeight_ in Tree, genWeight in
NewTree
  //?what is genWeight? what does it do?
  if(fileName.find("DY")!=string::npos ||
fileName.find("ZToNuNu")!=string::npos) {
    if(GenZPt_>0) genWeight = functZPt->Eval(GenZPt_);//functZPt TF1 in .h 102
        //Eval, evaluation of Chebyshev polynomials
    else genWeight = 1;
    }
  if(fileName.find("WToLNu")!=string::npos) {
    if(GenWPt_>0) genWeight = functWPt->Eval(GenWPt_);
    else genWeight = 1;
    }

}
*/
/*
void newPUWeight(double &puweight,double &puweightUP,double &puweightDOWN){
  double *npuProbs = 0;
  double *npuProbsNEW = 0;
  unsigned int nPUMax = 99;
        //?whatis these?
  double npu_Moriond18Scenario[99] =
{3.39597497605e-05,6.63688402133e-06,1.39533611284e-05,3.64963078209e-05,6.00872171664e-05,9.33932578027e-05,0.000120591524486,0.000128694546198,0.000361697233219,0.000361796847553,0.000702474896113,0.00133766053707,0.00237817050805,0.00389825605651,0.00594546732588,0.00856825906255,0.0116627396044,0.0148793350787,0.0179897368379,0.0208723871946,0.0232564170641,0.0249826433945,0.0262245860346,0.0272704617569,0.0283301107549,0.0294006137386,0.0303026836965,0.0309692426278,0.0308818046328,0.0310566806228,0.0309692426278,0.0310566806228,0.0310566806228,0.0310566806228,0.0307696426944,0.0300103336052,0.0288355370103,0.0273233309106,0.0264343533951,0.0255453758796,0.0235877272306,0.0215627588047,0.0195825559393,0.0177296309658,0.0160560731931,0.0146022004183,0.0134080690078,0.0129586991411,0.0125093292745,0.0124360740539,0.0123547104433,0.0123953922486,0.0124360740539,0.0124360740539,0.0123547104433,0.0124360740539,0.0123387597772,0.0122414455005,0.011705203844,0.0108187105305,0.00963985508986,0.00827210065136,0.00683770076341,0.00545237697118,0.00420456901556,0.00367513566191,0.00314570230825,0.0022917978982,0.00163221454973,0.00114065309494,0.000784838366118,0.000533204105387,0.000358474034915,0.000238881117601,0.0001984254989,0.000157969880198,0.00010375646169,6.77366175538e-05,4.39850477645e-05,2.84298066026e-05,1.83041729561e-05,1.17473542058e-05,7.51982735129e-06,6.16160108867e-06,4.80337482605e-06,3.06235473369e-06,1.94863396999e-06,1.23726800704e-06,7.83538083774e-07,4.94602064224e-07,3.10989480331e-07,1.94628487765e-07,1.57888581037e-07,1.2114867431e-07,7.49518929908e-08,4.6060444984e-08,2.81008884326e-08,1.70121486128e-08,1.02159894812e-08};
  double npu_Moriond18ScenarioNEW[99] =
{0.0164731,0.000829522,0.000939881,0.000589732,0.000665918,0.00111637,0.00125813,0.000933965,0.00145441,0.00184519,0.00159332,0.00242139,0.00314767,0.00548591,0.00684822,0.010836,0.0130551,0.0144512,0.0182305,0.0212894,0.0216204,0.0229435,0.0243586,0.0243769,0.0249553,0.0269723,0.0255303,0.0269896,0.0277803,0.0279493,0.0271844,0.0273721,0.0293261,0.0282731,0.0287164,0.0283037,0.0265103,0.0255473,0.0240064,0.0233137,0.0232938,0.0224567,0.0196284,0.0156212,0.0137627,0.0136596,0.0128352,0.0120469,0.0128242,0.0121217,0.0136477,0.0136083,0.0134189,0.0129351,0.0141632,0.0136156,0.0141845,0.0124658,0.0128498,0.0125589,0.0102669,0.0092894,0.00807026,0.00702602,0.0047661,0.00401915,0.00351898,0.00288564,0.00166122,0.0015046,0.000773104,0.000499557,0.000796673,0.0006105,0.000630528,0.000145819,0.000191135,0.000340493,0.000193567,0.000678164,0.000393724,0.000442431,0.000641926,0.000615461,0.000139089,0.000793345,0.000240982,0.00049623,0.00010741,0.000147015,0.0002128,1.14866e-05,1.75821e-05,9.66776e-05,3.37481e-05,0.000457706,2.37272e-07,4.74544e-07,9.06185e-05};
  npuProbs = npu_Moriond18Scenario;
  npuProbsNEW = npu_Moriond18ScenarioNEW;
  std::vector<double> result(nPUMax,0.);
  std::vector<double> resultNEW(nPUMax,0.);
  std::vector<double> resultNEWUp(nPUMax,0.);
  std::vector<double> resultNEWDo(nPUMax,0.);
  double s = 0.;
  double sNEW   = 0.;
  double sNEWUp = 0.;
  double sNEWDo = 0.;
  for(unsigned int npu = 0; npu < nPUMax; ++npu) {
    const double npu_estimated = histoOldPU ->GetBinContent(histoOldPU
->GetXaxis()->FindBin(npu));//histoOldPU in header 98
    result[npu] = npu_estimated / npuProbs[npu];
    s += npu_estimated;
    const double npu_estimatedNEW   = histoNewPU  ->GetBinContent(histoNewPU
->GetXaxis()->FindBin(npu));
    const double npu_estimatedNEWUp =
histoNewPUUp->GetBinContent(histoNewPUUp->GetXaxis()->FindBin(npu));
    const double npu_estimatedNEWDo =
histoNewPUDo->GetBinContent(histoNewPUDo->GetXaxis()->FindBin(npu));
    resultNEW[npu]   = npu_estimatedNEW   / npuProbsNEW[npu];
    resultNEWUp[npu] = npu_estimatedNEWUp / npuProbsNEW[npu];
    resultNEWDo[npu] = npu_estimatedNEWDo / npuProbsNEW[npu];
    sNEW   += npu_estimatedNEW;
    sNEWUp += npu_estimatedNEWUp;
    sNEWDo += npu_estimatedNEWDo;
  }
  unsigned int NPU = -1;
  for(unsigned int npu = 0; npu < nPUMax; ++npu) {
    result[npu] /= s;
    resultNEW[npu]   /= sNEW;
    resultNEWUp[npu] /= sNEWUp;
    resultNEWDo[npu] /= sNEWDo;
    //if(result[npu]==PUWeight_) NPU = npu;
    if(result[npu]<PUWeight_*1.0001 && result[npu]>PUWeight_*0.9999) NPU = npu;
  }
  if (NPU==-1) return;
  //cout<<NPU<<" "<<PUWeight_<<" "<<resultNEW[NPU]<<" "<<resultNEWUp[NPU]<<endl;
  if(resultNEW[NPU]<9999)   puweight     = resultNEW[NPU];
  if(resultNEWUp[NPU]<9999) puweightUP   = resultNEWUp[NPU];
  if(resultNEWDo[NPU]<9999) puweightDOWN = resultNEWDo[NPU];
  getTrueNumInteractions=NPU;
}
*/
void WriteTopRelatedBranches(bool ResolvedEvent,
                             TLorentzVector HadronicTopQuark, bool SelectedMet,
                             TLorentzVector HadronicTopQuarkResolved,
                             TLorentzVector Jet1Resolved,
                             TLorentzVector Jet2Resolved,
                             TLorentzVector Jet3Resolved,
                             vector<TLorentzVector> SelectedForwardJets,
                             vector<TLorentzVector> SelectedBJets) { /*{{{*/
  int NumSelBJets = SelectedBJets.size();
  if (ResolvedEvent) {
    TopMass = HadronicTopQuark.M();
    TopPt = HadronicTopQuark.Pt();
    TopEta = HadronicTopQuark.Eta();
    TopPhi = HadronicTopQuark.Phi();
  }
  //?why the same condition in two parts?
  if (ResolvedEvent) {
    TopMassResolved = HadronicTopQuarkResolved.M(); // branch in NewTree and SB
    TopPtResolved = HadronicTopQuarkResolved.Pt();
    TopEtaResolved = HadronicTopQuarkResolved.Eta();
    TopPhiResolved = HadronicTopQuarkResolved.Phi();
    Jet1ResolvedPt = Jet1Resolved.Pt();
    Jet2ResolvedPt = Jet2Resolved.Pt();
    Jet3ResolvedPt = Jet3Resolved.Pt();
    Jet1ResolvedEta = Jet1Resolved.Eta();
    Jet2ResolvedEta = Jet2Resolved.Eta();
    Jet3ResolvedEta = Jet3Resolved.Eta();
    WMassResolved1 = (Jet1Resolved + Jet2Resolved).M();
    WMassResolved2 = (Jet1Resolved + Jet3Resolved).M();
    WMassResolved3 = (Jet2Resolved + Jet3Resolved).M();
  }
  if (SelectedForwardJets.size() > 0)
    Jet1ForwardPt = SelectedForwardJets[0].Pt();
  if (SelectedForwardJets.size() > 1)
    Jet2ForwardPt = SelectedForwardJets[1].Pt();
  if (SelectedForwardJets.size() > 2)
    Jet3ForwardPt = SelectedForwardJets[2].Pt();
  if (SelectedForwardJets.size() > 0)
    Jet1ForwardEta = SelectedForwardJets[0].Eta();
  if (SelectedForwardJets.size() > 1)
    Jet2ForwardEta = SelectedForwardJets[1].Eta();
  if (SelectedForwardJets.size() > 2)
    Jet3ForwardEta = SelectedForwardJets[2].Eta();
} /*}}}*/
