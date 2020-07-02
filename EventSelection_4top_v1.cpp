#include "EventSelection_4top_v1.h" 
#include "math.h"

void EventSelection_4top_v1(const char * Input = ""){
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameBorderMode(0);//?
  gStyle->SetOptStat("rme");
  gStyle->SetPalette(1,0);
  gStyle->SetTitleX(0.50);
  gStyle->SetTitleY(0.96);
  gStyle->SetPaintTextFormat(".2f");

  bool preselection = true;//associate with selection 
  bool sideband     = false;//associate with selection
//?what's sideband and signal ?
  bool signal       = false;
	//?signal occur nowhere else

	//what does these mean?
  //SYSTEMATICS: 0 is standard, 1 is UP, 2 is down
	//appear in 95
  int SysJes = 0;//jet enenrgy scale 
  int SysJer = 0;//jet  energy resolution 
  
  using namespace std;
  char openTree[500];   sprintf(openTree, "TNT/BOOM");//117 
  vector<string> fileName;
	//what is May18V1_METC.root? if it's data file , what does CDEF mean?
  //fileName.push_back("May18V1_METB.root");/*{{{*/
  //fileName.push_back("May18V1_METC.root");  //2
 // fileName.push_back("May18V1_METD.root");  //3
 // fileName.push_back("May18V1_METE.root");  //4
  //fileName.push_back("May18V1_METF.root");  //5
 /* fileName.push_back("QCD_HT200to300.root");   //6
  fileName.push_back("QCD_HT300to500.root");   //7
  fileName.push_back("QCD_HT500to700.root");   //8
  fileName.push_back("QCD_HT700to1000.root");   //9
  fileName.push_back("QCD_HT1000to1500.root");   //10
  fileName.push_back("QCD_HT1500to2000.root");   //11
  fileName.push_back("QCD_HT2000toIn.root");   //12
  fileName.push_back("TTJets.root");   //13
  fileName.push_back("TT.root");   //14
  fileName.push_back("TTWJetsToQQ.root");   //15
  fileName.push_back("TTZToQQ.root");   //16
  fileName.push_back("TTTT.root");   //17 */
  fileName.push_back(Input);/*}}}*/
 //where is in put?what does input do?
//in line 4, the function parameter.


  for(unsigned int Nfiles=0; Nfiles<fileName.size(); Nfiles++){
    string NewFileprov;
		//do these files already exist or not?what does the number 1 or 2 mean ?
		//file already exist, new file is what we want build.
		//?it seems Jes and Jer can not aplly together?
    if ((SysJes==0)&&(SysJer==0)) NewFileprov = "/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_v2/"+fileName[Nfiles];
    if ((SysJes==1)&&(SysJer==0)) NewFileprov = "/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_v2/JESup/"+fileName[Nfiles];/*{{{*/
    if ((SysJes==2)&&(SysJer==0)) NewFileprov = "/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_v2/JESdo/"+fileName[Nfiles];
    if ((SysJes==0)&&(SysJer==1)) NewFileprov = "/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_v2/JERup/"+fileName[Nfiles];
    if ((SysJes==0)&&(SysJer==2)) NewFileprov = "/publicfs/cms/user/huahuil/FourTop/2016v1/SelectionNew_v2/JERdo/"+fileName[Nfiles];/*}}}*/
    //NewFileprov = fileName[Nfiles];
    //const char *NewFileName = fileName[Nfiles].c_str();
    const char *NewFileName = NewFileprov.c_str();
	//c_str()Returns a pointer to an array that contains a null-terminated sequence of characters (i.e., a C-string) representing the current value of the string object.
    TFile f(NewFileName,"new");
    TTree *NewTree = new TTree("tree","tree");
    TTree *NewTreeSB = new TTree("treeSB","treeSB");
		//?why 2 trees? what's the different?
		//treeSB has something todo with sideband
   //guessing file already exist ?
	 //data and sample is data or MC? where do we get these files ?
	 //where do we put the newfile?
    string FILEprov = "/publicfs/cms/user/huahuil/FourTop/2016v1/"+fileName[Nfiles];
    const char *FILE = FILEprov.c_str();
    TFile *file = TFile::Open(FILE);
		//?
    Tree = (TTree*)file->Get(openTree);
	//what do you mean get open tree from file ?
	//in 26 openTree=
    bool data = true;
	//what does "may..." mean?   guess they are data file name.
	
    if(!(fileName[Nfiles].find("May18V1_MET")!=string::npos )) data = false;
	//find():The position of the first character of the first match.
	//If no matches were found, the function returns string::npos.
	//find May18V1_MET,data=true.
	//what is data?	//if filename is data, data=true. data and MC files have different tree .
    branch(data,NewTree,NewTreeSB,fileName[Nfiles]);//line933
		//Tree->SetBranchAddress;NewTree and SB->Branch
		//every file have the same tree ?
    Int_t nentries = (Int_t)Tree->GetEntries();
		//how do we know the entries of Tree?
		//Read all branches of entry and return total number of bytes read.
    for(int selection=0; selection<3; selection++){
			//? it seems when pre = false, sideband=true,both 1 and 2 will go in the loop.signal=false
      //selection = 0 -> preselection=true; line 19, true
      //selection = 1 -> signal selection; preselection=false and, not continue , that means go to the next line of the loop.
      //selection = 2 -> sideband=true and pre=false; line 14 sideband=false 
    	if(!((preselection  && selection==0) || (!preselection && sideband && (selection==1 || selection==2)) || (!preselection && !sideband && selection==1))) continue;
		//preselection=true ,sideband=false,in this case selection=0
			//?what does sideband and signal do?
//      for (Int_t i=0; i<nentries; i++) {
      for (Int_t i=0; i<100; i++) {
			Long64_t tentry = Tree->LoadTree(i);//Set current entry.
			//?why file name not in the function?
			//what does data do here?
			branchGetEntry(data, tentry,fileName[Nfiles]);//line2241; every branch in Tree, Getentry.  b_Jet_pt->GetEntry(tentry);//is a branch in tree, setadress.
			//why we deal with data and MC differently?
			initializeVar();//line1822  initialize for new tree. category0=0;
			//?why still HLT?
			//
			//
			if(!(HLT_PFHT900_==1 || HLT_PFHT450_SixJet40_BTagCSV_p056_==1||HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ ==1))  continue;//a branch in tree, trigger we choose
			//
			//
			//=1 means pass the trigger?
			//?flag=filter?
			//?what are these Flag_branches?
			//?what choice should we make for our analysis?
			//?how many kinds of these filters are in MiniAOD?
			//?what is the ppossibility of there filter to out signal events?
			if(!(Flag_goodVertices_==1))  continue;//a branch in tree.
			if(!(Flag_globalSuperTightHalo2016Filter_==1))  continue;  
		    if(!(Flag_HBHENoiseFilter_==1))  continue;  
			if(!(Flag_HBHENoiseIsoFilter_==1))  continue;
			if(!(Flag_EcalDeadCellTriggerPrimitiveFilter_==1))  continue;  //a branch in Tree
		    if(!(Flag_BadPFMuonFilter_==1))  continue;  
			//if(!(Flag_BadChargedCandidateFilter_==1))  continue;
//			if(!(Flag_ecalBadCalibReducedMINIAODFilter_==1))  continue;  cout<<"139";
//			??why this filter not work?
			if(data) {if (!(Flag_eeBadScFilter_==1))  continue;}  

			if(!data) GenClassifier(GenZPt,GenWPt);//line2590
			//?according to pdg ID generate usdc quark and GenZPt GenWPt.

			//large met
			bool SelectedMet = false;
			//?how does SysJes impact Met_pt ?
			MetCorrection(SysJes,SysJer,Met_pt);//270 Met_pt in newtree branch.
            if( Met_pt > 200)  SelectedMet = true;//228;parameter in Fillbranches
			//SelectMet(SelectedMet);
			//Met_pt            = Met_type1PF_pt_;
			Met_phi           = Met_type1PF_phi_;//Met_phi branch in newtree and SB

			//Leptonic reject
			//?it seems that we have not save information of leptons other than their number
			vector<TLorentzVector> SelectedElectrons; vector<int> SelectedElectronsIndex;
			vector<TLorentzVector> SelectedMuons;     vector<int> SelectedMuonsIndex;
			SelectElectrons(SelectedElectrons, SelectedElectronsIndex, data);//304
			SelectMuons(SelectedMuons, SelectedMuonsIndex);//320

			//Hadronic Top selection
			vector<float> SelectedJetsCSV;
			vector<float> SelectedBJetsMCSV, SelectedBJetsLCSV, SelectedBJetsTCSV,SelectedForwardJetsCSV; /*{{{*/
			vector<int>   CA8Indices;
			int CA8Index = -1;
			//?not used in the macro
			bool deltaPhiJetMet=true;
			//vector<TLorentzVector> SelectedWJets;       SelectCA8Jets(0,SelectedWJets,  SelectedElectrons,SelectedMuons,CA8Indices, SysJes, SysJer, data, deltaPhiJetMet);   //if(!deltaPhiJetMet)  continue;
			//vector<TLorentzVector> SelectedTopJets;     SelectCA8Jets(1,SelectedTopJets,SelectedElectrons,SelectedMuons,CA8Indices, SysJes, SysJer, data, deltaPhiJetMet);   //if(!deltaPhiJetMet)  continue;
			//if (SelectedWJets.size()>0) continue;
			//if (SelectedTopJets.size()>0) continue;
			//330; return vector of SelectedJets and selectedJetsCSV
			//0,11,12 range for Jet_pfDeepCSVBJetTags is different
			vector<TLorentzVector> SelectedJets;        SelectJets(0,SelectedJets       ,SelectedJetsCSV       ,SelectedElectrons,SelectedMuons, SysJes, SysJer, data, deltaPhiJetMet);  //if(!deltaPhiJetMet)  continue;
			vector<TLorentzVector> SelectedBJetsL;      SelectJets(11,SelectedBJetsL    ,SelectedBJetsLCSV     ,SelectedElectrons,SelectedMuons, SysJes, SysJer, data, deltaPhiJetMet);  //if(!deltaPhiJetMet)  continue;
			vector<TLorentzVector> SelectedBJetsM;      SelectJets(12,SelectedBJetsM    ,SelectedBJetsMCSV     ,SelectedElectrons,SelectedMuons, SysJes, SysJer, data, deltaPhiJetMet);  //if(!deltaPhiJetMet)  continue;
			vector<TLorentzVector> SelectedBJetsT;      SelectJets(13,SelectedBJetsT    ,SelectedBJetsTCSV     ,SelectedElectrons,SelectedMuons, SysJes, SysJer, data, deltaPhiJetMet);  //if(!deltaPhiJetMet)  continue;
			vector<TLorentzVector> SelectedForwardJets; SelectJets(2,SelectedForwardJets,SelectedForwardJetsCSV,SelectedElectrons,SelectedMuons, SysJes, SysJer, data, deltaPhiJetMet);  //if(!deltaPhiJetMet)  continue;

			TLorentzVector Jet1Resolved;     Jet1Resolved.SetPtEtaPhiE(0, 0, 0, 0);
			TLorentzVector Jet2Resolved;     Jet2Resolved.SetPtEtaPhiE(0, 0, 0, 0);
			TLorentzVector Jet3Resolved;     Jet3Resolved.SetPtEtaPhiE(0, 0, 0, 0);
			TLorentzVector TopQuark;         TopQuark.SetPtEtaPhiE(0, 0, 0, 0);
			TLorentzVector TopQuarkResolved; TopQuarkResolved.SetPtEtaPhiE(0, 0, 0, 0);
			bool ResolvedEvent   = false;//parameter in function FillBranch
				//466; give Jet1,2,3,Toppt etc
				//last 2 parameter are TopMassCut and btag
			if(selection==0) ResolvedRegionSelection(ResolvedEvent, SelectedJets, SelectedJetsCSV, TopQuarkResolved, Jet1Resolved, Jet2Resolved, Jet3Resolved, false, false);
			if(selection==1) ResolvedRegionSelection(ResolvedEvent, SelectedJets, SelectedJetsCSV, TopQuarkResolved, Jet1Resolved, Jet2Resolved, Jet3Resolved, false, true );/*{{{*/
			if(selection==2) ResolvedRegionSelection(ResolvedEvent, SelectedJets, SelectedJetsCSV, TopQuarkResolved, Jet1Resolved, Jet2Resolved, Jet3Resolved, false, false);
			if(ResolvedEvent)   TopQuark = TopQuarkResolved;//parameter in Fillbranch
//			if(!ResolvedEvent) continue;/*}}}*/
			NumSelLeps        = SelectedElectrons.size()+SelectedMuons.size();//branch in newtree and SB
//
//
			NumSeEle = SelectedElectrons.size();
			NumSeMu = SelectedMuons.size();
//
//
			NumSelJets        = SelectedJets.size();
			NumSelForwardJets = SelectedForwardJets.size();//185
			NumSelBJetsL      = SelectedBJetsL.size();
			NumSelBJetsM      = SelectedBJetsM.size();//
			NumSelBJetsT      = SelectedBJetsT.size();
			NVertices         = nBestVtx_;
			EVENT_run         = EVENT_run_;
			EVENT_event       = EVENT_event_;
			EVENT_lumiBlock   = EVENT_lumiBlock_;
			EVENT_genHT       = EVENT_genHT_;
			prefiringweight   = EVENT_prefiringweight_;
			prefiringweightup = EVENT_prefiringweightup_;
			prefiringweightdown = EVENT_prefiringweightdown_;
			MHT               = MHTcalculator(SelectedJets);//900;return the pt sum of,vetctor sum
			HT                = HTcalculator(SelectedJets);
//      	if(!(HT>200)) continue;/*}}}*/
		
			//categorization
			if(selection==0){ //PRESELECTION
				if(ResolvedEvent  && SelectedMet)  category0=1; //branch in NewTree and SB 
			}
			else if(selection==1){ //SELECTION
				if(ResolvedEvent && NumSelBJetsM>0 && SelectedMet)     category0=1; 
	      	}
			//then what does category1,2 do?

//      	if(!(category0==1)) continue;//I think this is for calculating the events have passed
	
			//TREE
		    FillBranches(ResolvedEvent,TopQuark,SelectedMet,//2720
			TopQuarkResolved,Jet1Resolved,Jet2Resolved,Jet3Resolved,SelectedForwardJets,SelectedBJetsM);
			
			 
				//WEIGHT
//			if(!data){
//					get_weight_btag(selection,w_Btag, w_BtagUp, w_BtagDown,w_Btag1Up, w_Btag1Down,w_Btag2Up, w_Btag2Down,w_BtagLoose, w_BtagLooseUp, w_BtagLooseDown, fileName[Nfiles]);//606 w_Btagall in NewTree
//					newPUWeight(PUWeight, PUWeightUP, PUWeightDOWN);//2729PUWeigh is a branch in Tree and newTree,PU and UP and DOWN are in New
//					GenWeight(fileName[Nfiles], GenZPt, GenWPt);2681
//					HTSF(fileName[Nfiles],HT,Met_pt,w_ZToNuNu,w_ZToNuNuUp,w_ZToNuNuDown,w_WToLNu,w_WToLNuUp,w_WToLNuDown,w_ttbar,w_ttbarUp,w_ttbarDown);//778
//					TriggerSF(Met_pt, MHT, w_Trig, w_TrigUp, w_TrigDown );
//  	  			QCDWeight(0,8,w_QCDUp,w_QCDDown);//240
//					PDFWeight(10,111,w_PDFUp,w_PDFDown);
//			}
		
			if(selection==0 || selection==1) HistoFill(PUWeight,NewTree);
			else if(selection==2)            HistoFill(PUWeight,NewTreeSB);
		}
	}


    f.cd();
    writeFile(NewTree,NewTreeSB);//2456
    f.Close();
    cout<<"File "<<fileName[Nfiles]<<" ready!"<<endl;
  }
}




//
//
void 


//
//


void QCDWeight(int imin,int imax,float &w_QCDUp ,float &w_QCDDown){/*{{{*/
     TH1F *RMS = new TH1F("", "", 100,-0.5,0.5);
     for(int i=imin; i<imax; i++){
        if(i==5) continue;
        if(i==7) continue;
        int I = 0;
        I=i;
        float ratio = (*genWeights_)[I]/(*genWeights_)[0];
        RMS->Fill(ratio-1);
     }
     w_QCDUp = 1+RMS->GetRMS();
     w_QCDDown = TMath::Max(0.,(1 - RMS->GetRMS()));
     delete RMS;
}/*}}}*/

void PDFWeight(int imin,int imax,float &w_PDFUp ,float &w_PDFDown){/*{{{*/
     TH1F *RMS = new TH1F("", "", 100,-0.5,0.5);
     for(int i=imin; i<imax; i++){
        int I = 0;
        if(i==10) I=0;
        else       I=i;
        float ratio = (*genWeights_)[I]/(*genWeights_)[0];
        RMS->Fill(ratio-1);
     }
     w_PDFUp = 1+RMS->GetRMS();
     w_PDFDown = TMath::Max(0.,(1 - RMS->GetRMS()));
     delete RMS;
}/*}}}*/
//?why do this?
void MetCorrection(int SysJes, int SysJer, float &MET){/*{{{*/
     float METx = Met_type1PF_pt_*TMath::Cos(Met_type1PF_phi_);//in tree branch.
     float METy = Met_type1PF_pt_*TMath::Sin(Met_type1PF_phi_);
     for (UInt_t j = 0; j < Jet_pt_->size(); ++j){ 
	     if(!(Jet_Uncorr_pt_->at(j)>15)) continue;
			 //?Jet_Uncorr_pt in Tbrowser seems not a string ?
	     float jetpt = 0.;
			 ///?what does Jes Jer mean?
			 //?the difference of Jet_pt and Jet_Uncorr_pt?
	     if(SysJes==0 && SysJer==0){jetpt = Jet_Uncorr_pt_->at(j)*Jet_JesSF_->at(j) *Jet_JerSF_->at(j) ;}
	     if(SysJes==1 && SysJer==0){jetpt = Jet_Uncorr_pt_->at(j)*Jet_JesSFup_->at(j) *Jet_JerSF_->at(j) ;}
	     if(SysJes==2 && SysJer==0){jetpt = Jet_Uncorr_pt_->at(j)*Jet_JesSFdown_->at(j)*Jet_JerSF_->at(j) ;}
	     if(SysJes==0 && SysJer==1){jetpt = Jet_Uncorr_pt_->at(j)*Jet_JesSF_->at(j) *Jet_JerSFup_->at(j) ;}
	     if(SysJes==0 && SysJer==2){jetpt = Jet_Uncorr_pt_->at(j)*Jet_JesSF_->at(j) *Jet_JerSFdown_->at(j);}
	     METx = METx + Jet_Uncorr_pt_->at(j)*Jet_JesSF_->at(j)*TMath::Cos(Jet_phi_->at(j)) - jetpt*TMath::Cos(Jet_phi_->at(j));
	     METy = METy + Jet_Uncorr_pt_->at(j)*Jet_JesSF_->at(j)*TMath::Sin(Jet_phi_->at(j)) - jetpt*TMath::Sin(Jet_phi_->at(j));
		 //??
     }
     MET = sqrt(METx*METx + METy*METy);
}/*}}}*/

/*void SelectMet(bool &SelectedMet){ 
    if( Met_type1PF_pt_ > 200)  SelectedMet = true;
}
*/
void SelectElectrons(vector<TLorentzVector> & SelectedElectrons, vector<int> & SelectedElectronsIndex, bool data){/*{{{*/
	//?data does not occur.
  for (UInt_t j = 0; j < patElectron_pt_->size(); ++j){//banch in tree line945
		//what is patElectron_pt?
    if(!(patElectron_pt_->at(j)>20))                 continue;//A continue skips the rest of the body of an iteration-statement.
    if(!(fabs(patElectron_eta_->at(j))<2.4))	     continue;//std::string::at can be used to extract characters by characters from a given string.
    if(!(fabs(patElectron_SCeta_->at(j))<2.5))	     continue;
		//?SCeta?
    if(!(patElectron_inCrack_->at(j)==0))	         continue;
		//?
    if(!(patElectron_isPassLoose_->at(j)==1))	     continue;
    if(!(patElectron_passConversionVeto_->at(j)==1)) continue;
		//?
    //TLorentzVector electron; electron.SetPtEtaPhiE(patElectron_pt_->at(j),patElectron_eta_->at(j),patElectron_phi_->at(j),patElectron_energy_->at(j)*patElectron_energyCorr_->at(j));
    TLorentzVector electron; electron.SetPtEtaPhiE(patElectron_pt_->at(j),patElectron_eta_->at(j),patElectron_phi_->at(j),patElectron_energy_->at(j));
    SelectedElectrons.push_back(electron);
    SelectedElectronsIndex.push_back(j);
  }
}/*}}}*/

void SelectMuons(vector<TLorentzVector> & SelectedMuons, vector<int> & SelectedMuonsIndex){/*{{{*/
  for (UInt_t j = 0; j < Muon_pt_->size(); ++j){
    if(!(Muon_pt_->at(j)>20))                     continue;
    if(!(fabs(Muon_eta_->at(j))<2.4))             continue;
    if(!(Muon_loose_->at(j)==1))                  continue;
    if(!(Muon_relIsoDeltaBetaR04_->at(j)<0.15))   continue;  //loose iso->change to 0.15(tight) from 0.25
		//?Muon_relIsoDeltaBetaR04?_
    TLorentzVector muon; muon.SetPtEtaPhiE(Muon_pt_->at(j),Muon_eta_->at(j),Muon_phi_->at(j),Muon_energy_->at(j));
    SelectedMuons.push_back(muon);
    SelectedMuonsIndex.push_back(j);
  }
}/*}}}*/

//?Selectedelectron and muon not appear in the function body
void SelectJets(int jetType, vector<TLorentzVector> & SelectedJets, vector<float> & SelectedJetsCSV, vector<TLorentzVector> SelectedElectrons, vector<TLorentzVector> SelectedMuons, int SysJes, int SysJer, bool data, bool &deltaPhiJetMet){/*{{{*/
  //jetType=0  -> usual jets
  //jetType=11 -> b-jets L
  //jetType=12 -> b-jets M
  //jetType=13 -> b-jets T
  //jetType=2  -> forward jets
  //MinDeltaPhiJetMet = 99.0;
  float MaxMostForwardJetEta = -99;
	//?is Jet_pt_a string?
	//maybe j means j th jet?
  for (UInt_t j = 0; j < Jet_pt_->size(); ++j){
    float jetpt = 0.;
    if(SysJes==0 && SysJer==0){jetpt = Jet_Uncorr_pt_->at(j)*Jet_JesSF_->at(j)    *Jet_JerSF_->at(j)    ;}
    if(SysJes==1 && SysJer==0){jetpt = Jet_Uncorr_pt_->at(j)*Jet_JesSFup_->at(j)  *Jet_JerSF_->at(j)    ;}
    if(SysJes==2 && SysJer==0){jetpt = Jet_Uncorr_pt_->at(j)*Jet_JesSFdown_->at(j)*Jet_JerSF_->at(j)    ;}
    if(SysJes==0 && SysJer==1){jetpt = Jet_Uncorr_pt_->at(j)*Jet_JesSF_->at(j)    *Jet_JerSFup_->at(j)  ;}
    if(SysJes==0 && SysJer==2){jetpt = Jet_Uncorr_pt_->at(j)*Jet_JesSF_->at(j)    *Jet_JerSFdown_->at(j);}
    if(fabs(Jet_eta_->at(j))>2.65&&fabs(Jet_eta_->at(j))<3.139&&jetpt>50)    continue;
    if(!(jetpt>30))                                        continue;
    if(!(fabs(Jet_eta_->at(j))<5.0))                                        continue;
    if(fabs(Jet_eta_->at(j))<2.4){
      if(!(Jet_neutralHadEnergyFraction_->at(j)<0.90))                      continue;
      if(!(Jet_neutralEmEnergyFraction_->at(j)<0.90))                       continue;
      if(!(Jet_numberOfConstituents_->at(j)>1))                             continue;
      if(!(Jet_chargedHadronEnergyFraction_->at(j)>0.0))                    continue;
      if(!(Jet_chargedMultiplicity_->at(j)>0.0))                            continue;
      //if(!(Jet_chargedEmEnergyFraction_->at(j)<0.99))                       continue;
    }
	else if(fabs(Jet_eta_->at(j))>2.4 && fabs(Jet_eta_->at(j))<2.7){
      if(!(Jet_neutralHadEnergyFraction_->at(j)<0.90))                      continue;
      if(!(Jet_neutralEmEnergyFraction_->at(j)<0.90))                       continue;
      if(!(Jet_numberOfConstituents_->at(j)>1))                             continue;
    }
	else if(fabs(Jet_eta_->at(j))>2.7 && fabs(Jet_eta_->at(j))<3.0){
      if(!(Jet_neutralEmEnergyFraction_->at(j)>0.02))                       continue;
      if(!(Jet_neutralEmEnergyFraction_->at(j)<0.99))                       continue;
      if(!((Jet_numberOfConstituents_->at(j) -Jet_chargedMultiplicity_->at(j)) >2)) continue;
    }
	else if(fabs(Jet_eta_->at(j))>3.0){
      if(!(Jet_neutralEmEnergyFraction_->at(j)<0.90))                       continue;
      if(!(Jet_neutralHadEnergyFraction_->at(j)>0.02))                      continue;
      if(!((Jet_numberOfConstituents_->at(j) -Jet_chargedMultiplicity_->at(j)) >10)) continue;
    }
    if(jetType==11){if(!(Jet_pfDeepCSVBJetTags_->at(j)>0.1522)) continue;}
    if(jetType==12){if(!(Jet_pfDeepCSVBJetTags_->at(j)>0.4941)) continue;}
    if(jetType==13){if(!(Jet_pfDeepCSVBJetTags_->at(j)>0.8001)) continue;}
		//?
    if(jetType==0){
      if (fabs(Jet_eta_->at(j))>MaxMostForwardJetEta) {MaxMostForwardJetEta = fabs(Jet_eta_->at(j)); MostForwardJetEta = Jet_eta_->at(j); MostForwardJetPt = jetpt;}
			//MostForwardJetEta branch in new tree and SB.
    }
		//what does MaxMostForwardJetEta do?
    if(jetType==2) {if(!(fabs(Jet_eta_->at(j))>=2.4))                       continue;if(!(jetpt>30)) continue;}
    else {if(!(fabs(Jet_eta_->at(j))<2.4))		                            continue;}
    if(DeltaPhi(Jet_phi_->at(j),Met_type1PF_phi_)<MinDeltaPhiJetMet) MinDeltaPhiJetMet = DeltaPhi(Jet_phi_->at(j),Met_type1PF_phi_);//880
		//MinDeltaPhiJetMe a branch in newtree and SB
    float SF = jetpt/Jet_pt_->at(j);
    TLorentzVector jet_prov; jet_prov.SetPtEtaPhiM(Jet_pt_->at(j),Jet_eta_->at(j),Jet_phi_->at(j),Jet_mass_->at(j));
    TLorentzVector jet; jet.SetPxPyPzE(SF*jet_prov.Px(),SF*jet_prov.Py(),SF*jet_prov.Pz(),SF*jet_prov.E());
    SelectedJets.push_back(jet);
    SelectedJetsCSV.push_back(Jet_pfDeepCSVBJetTags_->at(j));
		//?
  }

  if(!(MinDeltaPhiJetMet>0.6)) deltaPhiJetMet=false;//used in Selectjets and SelectCA8Jets
}/*}}}*/

void SelectCA8Jets(int CA8jetType,vector<TLorentzVector> & SelectedCA8Jets,vector<TLorentzVector> SelectedElectrons,vector<TLorentzVector> SelectedMuons, vector<int> & CA8Indices, 
		   int SysJes, int SysJer, bool data, bool &deltaPhiJetMet){/*{{{*/
  //CA8jetType=0 -> W-jets
  //CA8jetType=1 -> top-jets
  for (UInt_t j = 0; j < BoostedJet_pt_->size(); ++j){
    float jetpt = 0.;
    if(SysJes==0 && SysJer==0){jetpt = BoostedJet_Uncorr_pt_->at(j)*BoostedJet_JesSF_->at(j)    *BoostedJet_JerSF_->at(j)    ;}
    if(SysJes==1 && SysJer==0){jetpt = BoostedJet_Uncorr_pt_->at(j)*BoostedJet_JesSFup_->at(j)  *BoostedJet_JerSF_->at(j)    ;}
    if(SysJes==2 && SysJer==0){jetpt = BoostedJet_Uncorr_pt_->at(j)*BoostedJet_JesSFdown_->at(j)*BoostedJet_JerSF_->at(j)    ;}
    if(SysJes==0 && SysJer==1){jetpt = BoostedJet_Uncorr_pt_->at(j)*BoostedJet_JesSF_->at(j)    *BoostedJet_JerSFup_->at(j)  ;}
    if(SysJes==0 && SysJer==2){jetpt = BoostedJet_Uncorr_pt_->at(j)*BoostedJet_JesSF_->at(j)    *BoostedJet_JerSFdown_->at(j);}
    float SF = jetpt/BoostedJet_pt_->at(j);
    if(!(jetpt>200)) continue;
    if(!(fabs(BoostedJet_eta_->at(j))<2.4))               continue;
    if(!(BoostedJet_neutralHadEnergyFraction_->at(j)<0.90)) continue;
    if(!(BoostedJet_neutralEmEnergyFraction_->at(j)<0.90)) continue;
    if(!(BoostedJet_numberOfConstituents_->at(j)>1)) continue;
    if(!(BoostedJet_chargedHadronEnergyFraction_->at(j)>0.0)) continue;
    if(!(BoostedJet_chargedMultiplicity_->at(j)>0.0)) continue;
    if(CA8jetType==0){
      if(!(SF*BoostedJet_puppi_softdrop_mass_->at(j)>65 && SF*BoostedJet_puppi_softdrop_mass_->at(j)<105)) continue;
      if(!(BoostedJet_puppi_tau2_->at(j)/BoostedJet_puppi_tau1_->at(j)<0.45)) continue;
    } else if(CA8jetType==1) {
      if(!(jetpt>400))                                                                           continue;
      if(!(SF*BoostedJet_puppi_softdrop_mass_->at(j)>105 && SF*BoostedJet_puppi_softdrop_mass_->at(j)<220)) continue;
      if(!(BoostedJet_puppi_tau3_->at(j)/BoostedJet_puppi_tau2_->at(j)<0.80)) continue;
    }

    TLorentzVector jet_prov; jet_prov.SetPtEtaPhiM(BoostedJet_pt_->at(j),BoostedJet_eta_->at(j),BoostedJet_phi_->at(j),BoostedJet_mass_->at(j));
    TLorentzVector jet; jet.SetPxPyPzE(SF*jet_prov.Px(),SF*jet_prov.Py(),SF*jet_prov.Pz(),SF*jet_prov.E());
    SelectedCA8Jets.push_back(jet);
    CA8Indices.push_back(j);
  }
}/*}}}*/

/*
void ResolvedRegionSelection(bool &ResolvedEvent,vector<TLorentzVector> SelectedJets,vector<float> SelectedJetsCSV,TLorentzVector &TopQuark,
			     TLorentzVector &Jet1,TLorentzVector &Jet2,TLorentzVector &Jet3,bool TopMassCut,bool btag){
  float TopPtMin=250;
  float TopMassInitial=99999;
  for(unsigned int i=0; i<SelectedJets.size(); i++){
    for(unsigned int j=i+1; j<SelectedJets.size(); j++){
      for(unsigned int k=j+1; k<SelectedJets.size(); k++){
		  if(!((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).Pt()>TopPtMin))   continue;
	//if(!(fabs((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).M()-173.1)<TopMassInitial))                                                    continue;
	if(TopMassCut){if(!((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).M()>100 && (SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).M()<300)) continue;}
	if(btag){if(!(SelectedJetsCSV[i]>0.4941 || SelectedJetsCSV[j]>0.4941 || SelectedJetsCSV[k]>0.4941))                                          continue;}
	if(SelectedJetsCSV[i]>SelectedJetsCSV[j] && SelectedJetsCSV[i]>SelectedJetsCSV[k]){
	  Jet1.SetPtEtaPhiE(SelectedJets[i].Pt(),SelectedJets[i].Eta(),SelectedJets[i].Phi(),SelectedJets[i].E());
	  Jet2.SetPtEtaPhiE(SelectedJets[j].Pt(),SelectedJets[j].Eta(),SelectedJets[j].Phi(),SelectedJets[j].E());
	  Jet3.SetPtEtaPhiE(SelectedJets[k].Pt(),SelectedJets[k].Eta(),SelectedJets[k].Phi(),SelectedJets[k].E());
	}
	if(SelectedJetsCSV[j]>SelectedJetsCSV[i] && SelectedJetsCSV[j]>SelectedJetsCSV[k]){
	  Jet1.SetPtEtaPhiE(SelectedJets[j].Pt(),SelectedJets[j].Eta(),SelectedJets[j].Phi(),SelectedJets[j].E());
	  Jet2.SetPtEtaPhiE(SelectedJets[i].Pt(),SelectedJets[i].Eta(),SelectedJets[i].Phi(),SelectedJets[i].E());
	  Jet3.SetPtEtaPhiE(SelectedJets[k].Pt(),SelectedJets[k].Eta(),SelectedJets[k].Phi(),SelectedJets[k].E());
	}
	if(SelectedJetsCSV[k]>SelectedJetsCSV[i] && SelectedJetsCSV[k]>SelectedJetsCSV[j]){
	  Jet1.SetPtEtaPhiE(SelectedJets[k].Pt(),SelectedJets[k].Eta(),SelectedJets[k].Phi(),SelectedJets[k].E());
	  Jet2.SetPtEtaPhiE(SelectedJets[i].Pt(),SelectedJets[i].Eta(),SelectedJets[i].Phi(),SelectedJets[i].E());
	  Jet3.SetPtEtaPhiE(SelectedJets[j].Pt(),SelectedJets[j].Eta(),SelectedJets[j].Phi(),SelectedJets[j].E());
	}
	TopPtMin = (SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).Pt();
	TopMassInitial=fabs((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).M()-173.1);
	TopQuark=(SelectedJets[i]+SelectedJets[j]+SelectedJets[k]);//argument in FillBranches
//	deltaPhiMetTop = DeltaPhi(TopQuark.Phi(),Met_phi);//in NewTree
//	TransverseMassMetTop = sqrt(2*TopQuark.Pt()*Met_pt*(1-cos(deltaPhiMetTop)));
	if(!(TransverseMassMetTop>500)) continue;
	ResolvedEvent=true;//argument in FillBranches
      }
    }
  }
}
*/


void ResolvedRegionSelection(bool &ResolvedEvent,vector<TLorentzVector> SelectedJets,vector<float> SelectedJetsCSV,TLorentzVector &TopQuark,
                            TLorentzVector &Jet1,TLorentzVector &Jet2,TLorentzVector &Jet3,bool TopMassCut,bool btag){/*{{{*/
  float TopPtMin=250;
  //how do we set this number?
  //refresh in the loop
  float TopMassInitial=99999;
  for(unsigned int i=0; i<SelectedJets.size(); i++){
    for(unsigned int j=i+1; j<SelectedJets.size(); j++){
      for(unsigned int k=j+1; k<SelectedJets.size(); k++){
         if(!((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).Pt()>TopPtMin)) continue;
         //if(!(fabs((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).M()-173.1)<TopMassInitial)) continue;
         if(TopMassCut){if(!((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).M()>100 && (SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).M()<300)) continue;}
         if(btag){if(!(SelectedJetsCSV[i]>0.4941 || SelectedJetsCSV[j]>0.4941 || SelectedJetsCSV[k]>0.4941)) continue;}
				 //btag has something to do with CSV?
         float TM = sqrt(2*(SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).Pt()*Met_pt*(1-cos(DeltaPhi((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).Phi(),Met_phi))));
		 //?what is TM?
         if(!(TM>500)) continue;
				 //?what if we have more than one pair of three jet?
         Jet1.SetPtEtaPhiE(SelectedJets[i].Pt(),SelectedJets[i].Eta(),SelectedJets[i].Phi(),SelectedJets[i].E());
         Jet2.SetPtEtaPhiE(SelectedJets[j].Pt(),SelectedJets[j].Eta(),SelectedJets[j].Phi(),SelectedJets[j].E());
         Jet3.SetPtEtaPhiE(SelectedJets[k].Pt(),SelectedJets[k].Eta(),SelectedJets[k].Phi(),SelectedJets[k].E());
         TopPtMin = (SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).Pt();
         TopMassInitial=fabs((SelectedJets[i]+SelectedJets[j]+SelectedJets[k]).M()-173.1);
         TopQuark=(SelectedJets[i]+SelectedJets[j]+SelectedJets[k]);
		 //???will not work if we have more than 1 TopQuark
         deltaPhiMetTop = DeltaPhi(TopQuark.Phi(),Met_phi);//880
         TransverseMassMetTop = sqrt(2*TopQuark.Pt()*Met_pt*(1-cos(deltaPhiMetTop)));//branch in NewTree and SB
         ResolvedEvent=true;
      }
    }
  }
}
/*}}}*/


void PartiallyMergedSelection(bool &PartiallyMerged,vector<TLorentzVector> SelectedWJets,vector<TLorentzVector> SelectedJets,vector<float> SelectedJetsCSV,TLorentzVector &TopQuark,TLorentzVector &Jet1,TLorentzVector &Jet2,bool TopMassCut,bool btag,vector<int> CA8Indices,int & CA8Index,float &WMass_,float &WSubjet_, bool data){/*{{{*/
  float TopPtMin=20;
  float TopMassInitial=99999;
  for(unsigned int i=0; i<SelectedWJets.size(); i++){
    for(unsigned int k=0; k<SelectedJets.size(); k++){
      if(!((SelectedWJets[i]+SelectedJets[k]).Pt()>TopPtMin))                                                        continue;
      //if(!(fabs((SelectedWJets[i]+SelectedJets[k]).M()-173.1)<TopMassInitial))                                     continue;
      if(!(DeltaR(SelectedWJets[i].Eta(),SelectedJets[k].Eta(),SelectedWJets[i].Phi(),SelectedJets[k].Phi())>0.8))   continue;
      if(btag){if(!(SelectedJetsCSV[k]>0.4941))                                                                       continue;}
      if(TopMassCut){if(!((SelectedWJets[i]+SelectedJets[k]).M()>100 && (SelectedWJets[i]+SelectedJets[k]).M()<300)) continue;}
      Jet1.SetPtEtaPhiE(SelectedWJets[i].Pt(),SelectedWJets[i].Eta(),SelectedWJets[i].Phi(),SelectedWJets[i].E());
      Jet2.SetPtEtaPhiE(SelectedJets[k].Pt(),SelectedJets[k].Eta(),SelectedJets[k].Phi(),SelectedJets[k].E());
      TopPtMin = (SelectedWJets[i]+SelectedJets[k]).Pt();
      PartiallyMerged=true;
      TopMassInitial=fabs((SelectedWJets[i]+SelectedJets[k]).M()-173.1);
      TopQuark=(SelectedWJets[i]+SelectedJets[k]);
      CA8Index=CA8Indices[i];
	 
      float SF = (BoostedJet_Uncorr_pt_->at(CA8Indices[i])/BoostedJet_pt_->at(CA8Indices[i]))*BoostedJet_JesSF_->at(CA8Indices[i])*BoostedJet_JerSF_->at(CA8Indices[i]);
      WMass_   = SF*BoostedJet_pruned_mass_->at(CA8Indices[i]);
      WSubjet_ = BoostedJet_tau2_->at(CA8Indices[i])/BoostedJet_tau1_->at(CA8Indices[i]);
    }
  }
}/*}}}*/

void FullyMergedSelection(bool & FullyMerged, vector<TLorentzVector> SelectedTopJets, TLorentzVector &TopQuark,vector<int> CA8Indices,float &TopSoftMass_,float &TopSubjet_, bool data){/*{{{*/
  float TopPtMin=400;
  for(unsigned int i=0; i<SelectedTopJets.size(); i++){
    if(!(SelectedTopJets[i].Pt()>TopPtMin)) continue;
    FullyMerged=true;
    TopPtMin=SelectedTopJets[i].Pt();
    TopQuark=SelectedTopJets[i];
    float SF = (BoostedJet_Uncorr_pt_->at(CA8Indices[i])/BoostedJet_pt_->at(CA8Indices[i]))*BoostedJet_JesSF_->at(CA8Indices[i])*BoostedJet_JerSF_->at(CA8Indices[i]);
    TopSoftMass_  = SF*BoostedJet_softdrop_mass_->at(CA8Indices[i]);
    TopSubjet_    = BoostedJet_tau3_->at(CA8Indices[i])/BoostedJet_tau2_->at(CA8Indices[i]);
  }
}/*}}}*/

void BTagSF(int selection, float JetPt, float JetEta, int flav, float &SF, float &SFerr){/*{{{*/
  bool DoubleUncertainty = false;
  float MinBJetPt = 20.;
  float MaxBJetPt = 1000.;
  float MaxLJetPt = 1000.;
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
  auto btagentry_flav = flav == 5 ? BTagEntry::FLAV_B : (flav == 4 ? BTagEntry::FLAV_C : BTagEntry::FLAV_UDSG);
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
    jet_scalefactor_up = 2*(jet_scalefactor_up - jet_scalefactor) + jet_scalefactor; 
    jet_scalefactor_do = 2*(jet_scalefactor_do - jet_scalefactor) + jet_scalefactor; 
  }
  if(jet_scalefactor==0){
    jet_scalefactor=1;
    jet_scalefactor_up=1;
    jet_scalefactor_do=1;
  }
  SF=jet_scalefactor;
  SFerr=max(fabs(jet_scalefactor-jet_scalefactor_up),fabs(jet_scalefactor-jet_scalefactor_do));
  //cout<<JetPt<<" "<<JetEta<<" "<<flav<<" ("<<btagentry_flav<<") "<<jet_scalefactor<<" "<<jet_scalefactor_up<<" "<<jet_scalefactor_do<<endl;
}/*}}}*/

//w_Btag branch in NewTree and SB
//?what is this doing exactly?
void get_weight_btag(int selection, float &w_Btag, float &w_BtagUp, float &w_BtagDown, float &w_Btag1Up, float &w_Btag1Down, float &w_Btag2Up, float &w_Btag2Down, float &w_BtagLoose, float &w_BtagLooseUp, float &w_BtagLooseDown, string fileName){/*{{{*/
  string FILEprov = "/publicfs/cms/user/yutz/Tprime/2017_dineutrino/BtagEfficiency_new_v3/"+fileName;
  const char *FILE = FILEprov.c_str();
  TFile *fileBTagEfficiency = TFile::Open(FILE);
  float mcTagMedium = 1.;     float mcTagLoose = 1.;
  float mcNoTagMedium = 1.;   float mcNoTagLoose = 1.;
  float dataTagMedium = 1.;   float dataTagLoose = 1.;
  float dataNoTagMedium = 1.; float dataNoTagLoose = 1.;
  float err1Medium = 0.;      float err1Loose = 0.;
  float err2Medium = 0.;      float err2Loose = 0.;
  float err3Medium = 0.;      float err3Loose = 0.;
  float err4Medium = 0.;      float err4Loose = 0.;
  for (UInt_t j = 0; j < Jet_pt_->size(); ++j){
    if(!((Jet_Uncorr_pt_->at(j)*Jet_JesSF_->at(j)*Jet_JerSF_->at(j))>20)) continue;
    if(!(fabs(Jet_eta_->at(j))<2.4))                                      continue;
    if(!(Jet_neutralHadEnergyFraction_->at(j)<0.90))                      continue;
    if(!(Jet_neutralEmEnergyFraction_->at(j)<0.90))                       continue;
    if(!(Jet_numberOfConstituents_->at(j)>1))                             continue;
    if(!(Jet_chargedHadronEnergyFraction_->at(j)>0.0))                    continue;
    if(!(Jet_chargedMultiplicity_->at(j)>0.0))                            continue;
    //if(!(Jet_chargedEmEnergyFraction_->at(j)<0.99))                       continue;
    float JetPt  = (Jet_Uncorr_pt_->at(j)*Jet_JesSF_->at(j)*Jet_JerSF_->at(j)); 
    float JetEta = fabs(Jet_eta_->at(j)); 
    int flav = Jet_hadronFlavour_->at(j);
    float MinBJetPt = 20.;
    float MaxBJetPt = 1000.;
    float MaxLJetPt = 1000.;
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
    float eff   = NUM->GetBinContent(ptBin,etaBin);
    float SF    = 1.0;
    float SFerr = 0.0;
    BTagSF(selection, JetPt, JetEta, flav, SF, SFerr);
    if(Jet_pfDeepCSVBJetTags_->at(j)>0.4941){
      mcTagMedium *= eff;
      dataTagMedium *= eff*SF;
      if(flav==5 || flav ==4)  err1Medium += SFerr/SF; //correlated for b/c
      else err3Medium += SFerr/SF;                     //correlated for light
    }else{
      mcNoTagMedium *= (1- eff);
      dataNoTagMedium *= (1- eff*SF);
      if(flav==5 || flav ==4 ) err2Medium += (-eff*SFerr)/(1-eff*SF); //correlated for b/c
      else err4Medium +=  (-eff*SFerr)/(1-eff*SF);                    //correlated for light
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
    //cout<<JetPt<<" "<<flav<<" "<<ptBin<<" "<<etaBin<<" "<<eff<<" "<<SF<<" "<<SFerr<<endl;
  }
  float wtbtagMedium        = 1; float wtbtagLoose        = 1;
  float wtbtagErrBCMedium   = 0; float wtbtagErrBCLoose   = 0;
  float wtbtagErrUDSGMedium = 0; float wtbtagErrUDSGLoose = 0;
  if((mcNoTagMedium*mcTagMedium)!=0) wtbtagMedium        = (dataNoTagMedium * dataTagMedium ) / ( mcNoTagMedium * mcTagMedium ); 
  if((mcNoTagMedium*mcTagMedium)!=0) wtbtagErrBCMedium   = fabs(err1Medium+err2Medium) * wtbtagMedium;
  if((mcNoTagMedium*mcTagMedium)!=0) wtbtagErrUDSGMedium = fabs(err3Medium+err4Medium) * wtbtagMedium;
  if((mcNoTagLoose*mcTagLoose)!=0) wtbtagLoose        = (dataNoTagLoose * dataTagLoose ) / ( mcNoTagLoose * mcTagLoose ); 
  if((mcNoTagLoose*mcTagLoose)!=0) wtbtagErrBCLoose   = fabs(err1Loose+err2Loose) * wtbtagLoose;
  if((mcNoTagLoose*mcTagLoose)!=0) wtbtagErrUDSGLoose = fabs(err3Loose+err4Loose) * wtbtagLoose;
  w_Btag     = wtbtagMedium; 
  w_BtagUp   = wtbtagMedium+sqrt(wtbtagErrBCMedium*wtbtagErrBCMedium+wtbtagErrUDSGMedium*wtbtagErrUDSGMedium);
  w_BtagDown = wtbtagMedium-sqrt(wtbtagErrBCMedium*wtbtagErrBCMedium+wtbtagErrUDSGMedium*wtbtagErrUDSGMedium);
  w_Btag1Up   = wtbtagMedium+sqrt(wtbtagErrBCMedium*wtbtagErrBCMedium);
  w_Btag1Down = wtbtagMedium-sqrt(wtbtagErrBCMedium*wtbtagErrBCMedium);
  w_Btag2Up   = wtbtagMedium+sqrt(wtbtagErrUDSGMedium*wtbtagErrUDSGMedium);
  w_Btag2Down = wtbtagMedium-sqrt(wtbtagErrUDSGMedium*wtbtagErrUDSGMedium);
  w_BtagLoose     = wtbtagLoose; 
  w_BtagLooseUp   = wtbtagLoose+sqrt(wtbtagErrBCLoose*wtbtagErrBCLoose+wtbtagErrUDSGLoose*wtbtagErrUDSGLoose);
  w_BtagLooseDown = wtbtagLoose-sqrt(wtbtagErrBCLoose*wtbtagErrBCLoose+wtbtagErrUDSGLoose*wtbtagErrUDSGLoose);
  if(selection==2){
    w_Btag     = wtbtagLoose; 
    w_BtagUp   = wtbtagLoose+sqrt(wtbtagErrBCLoose*wtbtagErrBCLoose+wtbtagErrUDSGLoose*wtbtagErrUDSGLoose);
    w_BtagDown = wtbtagLoose-sqrt(wtbtagErrBCLoose*wtbtagErrBCLoose+wtbtagErrUDSGLoose*wtbtagErrUDSGLoose);
    w_Btag1Up   = wtbtagLoose+sqrt(wtbtagErrBCLoose*wtbtagErrBCLoose);
    w_Btag1Down = wtbtagLoose-sqrt(wtbtagErrBCLoose*wtbtagErrBCLoose);
    w_Btag2Up   = wtbtagLoose+sqrt(wtbtagErrUDSGLoose*wtbtagErrUDSGLoose);
    w_Btag2Down = wtbtagLoose-sqrt(wtbtagErrUDSGLoose*wtbtagErrUDSGLoose);
  }
  //cout<<"BTAG WEIGHT  "<<wtbtagErrBC<<" "<<wtbtagErrUDSG<<" "<<w_Btag<<" "<<w_BtagUp<<" "<<endl;
  delete fileBTagEfficiency;
}/*}}}*/

/*void ForwardJetSF(vector<TLorentzVector> SelectedForwardJets, float &w_for_, float &w_forUp_, float &w_forDown_){
  if(SelectedForwardJets.size()>0){
    float eta = eta = SelectedForwardJets[0].Eta(); float pt = SelectedForwardJets[0].Pt();
    int X1=-99; int Y1=-99;
    for(int i=1; i<histoForwardJet->GetXaxis()->GetNbins()+2; i++){
      if(eta<histoForwardJet->GetXaxis()->GetBinLowEdge(i)){ X1=i-1; break; }
    }
    for(int i=1; i<histoForwardJet->GetYaxis()->GetNbins()+2; i++){
      if(pt <histoForwardJet->GetYaxis()->GetBinLowEdge(i)){ Y1=i-1; break; }
    }
    if(pt>=histoForwardJet->GetYaxis()->GetBinLowEdge(histoForwardJet->GetYaxis()->GetNbins()+1)) {Y1=(histoForwardJet->GetYaxis()->GetNbins()+1)-1;}
    float SF = histoForwardJet->GetBinContent(X1,Y1);
    w_for_     = SF;
    w_forUp_   = SF + histoForwardJet->GetBinError(X1,Y1); //w_forUp_   = 1.0;
    w_forDown_ = SF - histoForwardJet->GetBinError(X1,Y1); //w_forDown_ = 1.0;
  }
}*/

void TopSF(TLorentzVector SelectedTopJets, bool FullyMerged, float &w_topJet_, float &w_topJetUp_, float &w_topJetDown_){/*{{{*/
  if(FullyMerged){
    if(SelectedTopJets.Pt()< 550) w_topJet_     = 1.06;
    if(SelectedTopJets.Pt()>=550) w_topJet_     = 1.06;
    if(SelectedTopJets.Pt()< 550) w_topJetUp_   = 1.06+0.09;
    if(SelectedTopJets.Pt()>=550) w_topJetUp_   = 1.06+0.09;
    if(SelectedTopJets.Pt()< 550) w_topJetDown_ = 1.06-0.04;
    if(SelectedTopJets.Pt()>=550) w_topJetDown_ = 1.06-0.04;
  }
}/*}}}*/

void WSF(TLorentzVector WJet, bool PartiallyMerged, float &w_WJet_, float &w_WJetUp_, float &w_WJetDown_, int CA8Index, int SysJes, int SysJer){/*{{{*/
  if(PartiallyMerged){
    bool matched = false;
    GenWBoson(matched, WJet);
    if(matched){
      w_WJet_     = 1.00*1.23*1.11;
      if(SysJes==1) w_WJet_ = 1.00*1.23*1.11 + sqrt(pow(Jet_JesSFup_->at(CA8Index)/Jet_JesSF_->at(CA8Index)-1  ,2) + 0.023*0.023);
      if(SysJes==2) w_WJet_ = 1.00*1.23*1.11 - sqrt(pow(1-Jet_JesSFdown_->at(CA8Index)/Jet_JesSF_->at(CA8Index),2) + 0.023*0.023);
      if(SysJer==1) w_WJet_ = 1.00*1.23*1.11 + sqrt(pow(Jet_JerSFup_->at(CA8Index)/Jet_JerSF_->at(CA8Index)-1  ,2) + 0.018*0.018);
      if(SysJer==2) w_WJet_ = 1.00*1.23*1.11 - sqrt(pow(1-Jet_JerSFdown_->at(CA8Index)/Jet_JerSF_->at(CA8Index),2) + 0.018*0.018);
      w_WJetUp_   = 1.00*1.23*1.11 + (0.08);
      w_WJetDown_ = 1.00*1.23*1.11 - (0.08);
      if(WJet.Pt()>200){
        w_WJetUp_   = 1.00*1.23*1.11 + (0.08 + 0.054*log(WJet.Pt()/200));
        w_WJetDown_ = 1.00*1.23*1.11 - (0.08 + 0.054*log(WJet.Pt()/200));
      }
    }
  }
}/*}}}*/

//?what's the purpose of thisi?
/*
void HTSF(string fileName, float HT, float Met_pt, float &w_SF1, float &w_SF1Up, float &w_SF1Down, float &w_SF2, float &w_SF2Up, float &w_SF2Down, float &w_SF3, float &w_SF3Up, float &w_SF3Down){
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
					//in .h file, from SF_dineutrino/SF_2D.root
           w_SF1 = histoSF1->GetBinContent(htBin,metBin);
           w_SF1Up = histoSF1->GetBinContent(htBin,metBin)+ //778histoSF1->GetBinError(htBin,metBin);
           w_SF1Down = TMath::Max(0.,histoSF1->GetBinContent(htBin,metBin)- histoSF1->GetBinError(htBin,metBin)); 
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
           w_SF2Up = histoSF2->GetBinContent(htBin,metBin)+ histoSF2->GetBinError(htBin,metBin);
           w_SF2Down = TMath::Max(0.,histoSF2->GetBinContent(htBin,metBin)- histoSF2->GetBinError(htBin,metBin)); 
        }
  }
   if(fileName.find("TT")!=string::npos||fileName.find("tZq")!=string::npos||fileName.find("ST")!=string::npos ){	
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
           w_SF3Up = histoSF3->GetBinContent(htBin,metBin)+ histoSF3->GetBinError(htBin,metBin);
           w_SF3Down = TMath::Max(0.,histoSF3->GetBinContent(htBin,metBin)- histoSF3->GetBinError(htBin,metBin)); 
        }
  }

}
*/

void TriggerSF(float Met_pt, float MHT, float &w_Trig, float &w_TrigUp, float &w_TrigDown){/*{{{*/
  int metBin = 0; int mhtBin = 0;
  if (Met_pt>0 && Met_pt<25)    metBin = 1;
  if (Met_pt>25 && Met_pt<50)   metBin = 2;
  if (Met_pt>50 && Met_pt<75)   metBin = 3;
  if (Met_pt>75 && Met_pt<100)  metBin = 4;
  if (Met_pt>100 && Met_pt<125) metBin = 5;
  if (Met_pt>125 && Met_pt<150) metBin = 6;
  if (Met_pt>150 && Met_pt<175) metBin = 7;
  if (Met_pt>175 && Met_pt<200) metBin = 8;
  if (Met_pt>200 && Met_pt<225) metBin = 9;
  if (Met_pt>225 && Met_pt<250) metBin = 10;
  if (Met_pt>250 && Met_pt<300) metBin = 11;
  if (Met_pt>300 && Met_pt<400) metBin = 12;
  if (Met_pt>400 && Met_pt<500) metBin = 13;
  if (Met_pt>500 && Met_pt<1000) metBin = 14;

  if (MHT>0 && MHT<25)    mhtBin = 1;
  if (MHT>25 && MHT<50)   mhtBin = 2;
  if (MHT>50 && MHT<75)   mhtBin = 3;
  if (MHT>75 && MHT<100)  mhtBin = 4;
  if (MHT>100 && MHT<125) mhtBin = 5;
  if (MHT>125 && MHT<150) mhtBin = 6;
  if (MHT>150 && MHT<175) mhtBin = 7;
  if (MHT>175 && MHT<200) mhtBin = 8;
  if (MHT>200 && MHT<225) mhtBin = 9;
  if (MHT>225 && MHT<250) mhtBin = 10;
  if (MHT>250 && MHT<300) mhtBin = 11;
  if (MHT>300 && MHT<400) mhtBin = 12;
  if (MHT>400 && MHT<500) mhtBin = 13;
  if (MHT>500 && MHT<1000) mhtBin = 14;

  if (metBin==0 || mhtBin==0){
     w_Trig = 1; w_TrigUp = 1; w_TrigDown = 1;
  }
   else {
     w_Trig     = histoTrig->GetBinContent(metBin,mhtBin);
     w_TrigUp   = histoTrig->GetBinContent(metBin,mhtBin)+ histoTrig->GetBinError(metBin,mhtBin);
     w_TrigDown = TMath::Max(0.,histoTrig->GetBinContent(metBin,mhtBin)- histoTrig->GetBinError(metBin,mhtBin));
  }
}/*}}}*/

float DeltaR(float eta1, float eta2, float phi1, float phi2){
  float deltaPhi = TMath::Abs(phi1-phi2);
  float deltaEta = eta1-eta2;
  if(deltaPhi > TMath::Pi()) deltaPhi = TMath::TwoPi() - deltaPhi;
  return TMath::Sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
}

float DeltaPhi(float phi1, float phi2){/*{{{*/
  float deltaPhi = TMath::Abs(phi1-phi2);
  if(deltaPhi > TMath::Pi()) deltaPhi = TMath::TwoPi() - deltaPhi;
  return deltaPhi;
}/*}}}*/

float HTcalculator(vector<TLorentzVector> SelectedJets){/*{{{*/
  float HTprov=0;
  for (UInt_t j = 0; j < SelectedJets.size(); ++j){
    HTprov=HTprov+SelectedJets[j].Pt();//.Pt: the 3 vertor component, scalar
  }
  return HTprov;
}/*}}}*/

float MHTcalculator(vector<TLorentzVector> SelectedJets){/*{{{*/
  TLorentzVector SumJets;     SumJets.SetPtEtaPhiE(0, 0, 0, 0);
  float MHTprov=0;
  for (UInt_t j = 0; j < SelectedJets.size(); ++j){
    SumJets=SumJets+SelectedJets[j];
  }
  MHTprov= SumJets.Pt();
  return MHTprov;
}/*}}}*/

//?it seems that fileName doesn't occur in the function .
//
void branch(bool data, TTree *NewTree,TTree *NewTreeSB, string fileName){/*{{{*/
	//Change branch address, dealing with clone trees properly.
	//?
  Tree->SetBranchAddress("Jet_pt",   &Jet_pt_,   &b_Jet_pt);
  Tree->SetBranchAddress("Jet_eta",  &Jet_eta_,  &b_Jet_eta);
  Tree->SetBranchAddress("Jet_phi",  &Jet_phi_,  &b_Jet_phi);
  Tree->SetBranchAddress("Jet_mass", &Jet_mass_, &b_Jet_mass);
  Tree->SetBranchAddress("Jet_JesSF",&Jet_JesSF_,&b_Jet_JesSF);
  Tree->SetBranchAddress("Jet_JesSFup",&Jet_JesSFup_,&b_Jet_JesSFup);
  Tree->SetBranchAddress("Jet_JesSFdown",&Jet_JesSFdown_,&b_Jet_JesSFdown);
  Tree->SetBranchAddress("Jet_JerSF",&Jet_JerSF_,&b_Jet_JerSF);
  Tree->SetBranchAddress("Jet_JerSFup",&Jet_JerSFup_,&b_Jet_JerSFup);
  Tree->SetBranchAddress("Jet_JerSFdown",&Jet_JerSFdown_,&b_Jet_JerSFdown);
  Tree->SetBranchAddress("Jet_Uncorr_pt",   &Jet_Uncorr_pt_,   &b_Jet_Uncorr_pt);
  Tree->SetBranchAddress("Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags", &Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags_, &b_Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags);
  Tree->SetBranchAddress("Jet_pfDeepCSVBJetTags", &Jet_pfDeepCSVBJetTags_, &b_Jet_pfDeepCSVBJetTags);
  Tree->SetBranchAddress("Jet_neutralHadEnergyFraction", &Jet_neutralHadEnergyFraction_, &b_Jet_neutralHadEnergyFraction);
  Tree->SetBranchAddress("Jet_chargedEmEnergyFraction", &Jet_chargedEmEnergyFraction_, &b_Jet_chargedEmEnergyFraction);
  Tree->SetBranchAddress("Jet_neutralEmEnergyFraction", &Jet_neutralEmEnergyFraction_, &b_Jet_neutralEmEnergyFraction);
  Tree->SetBranchAddress("Jet_numberOfConstituents", &Jet_numberOfConstituents_, &b_Jet_numberOfConstituents);
  Tree->SetBranchAddress("Jet_chargedHadronEnergyFraction", &Jet_chargedHadronEnergyFraction_, &b_Jet_chargedHadronEnergyFraction);
  Tree->SetBranchAddress("Jet_chargedMultiplicity", &Jet_chargedMultiplicity_, &b_Jet_chargedMultiplicity);
  if(!data) Tree->SetBranchAddress("Jet_hadronFlavour", &Jet_hadronFlavour_, &b_Jet_hadronFlavour);
  Tree->SetBranchAddress("BoostedJet_pt",   &BoostedJet_pt_,   &b_BoostedJet_pt);
  Tree->SetBranchAddress("BoostedJet_Uncorr_pt",   &BoostedJet_Uncorr_pt_,   &b_BoostedJet_Uncorr_pt);
  Tree->SetBranchAddress("BoostedJet_softdrop_mass",   &BoostedJet_softdrop_mass_,   &b_BoostedJet_softdrop_mass);
  Tree->SetBranchAddress("BoostedJet_puppi_softdrop_mass",   &BoostedJet_puppi_softdrop_mass_,   &b_BoostedJet_puppi_softdrop_mass);
  Tree->SetBranchAddress("BoostedJet_JesSF",&BoostedJet_JesSF_,&b_BoostedJet_JesSF);
  Tree->SetBranchAddress("BoostedJet_JesSFup",&BoostedJet_JesSFup_,&b_BoostedJet_JesSFup);
  Tree->SetBranchAddress("BoostedJet_JesSFdown",&BoostedJet_JesSFdown_,&b_BoostedJet_JesSFdown);
  Tree->SetBranchAddress("BoostedJet_JerSF",&BoostedJet_JerSF_,&b_BoostedJet_JerSF);
  Tree->SetBranchAddress("BoostedJet_JerSFup",&BoostedJet_JerSFup_,&b_BoostedJet_JerSFup);
  Tree->SetBranchAddress("BoostedJet_JerSFdown",&BoostedJet_JerSFdown_,&b_BoostedJet_JerSFdown);
  Tree->SetBranchAddress("BoostedJet_eta",  &BoostedJet_eta_,  &b_BoostedJet_eta);
  Tree->SetBranchAddress("BoostedJet_phi",  &BoostedJet_phi_,  &b_BoostedJet_phi);
  Tree->SetBranchAddress("BoostedJet_mass", &BoostedJet_mass_, &b_BoostedJet_mass);
  Tree->SetBranchAddress("BoostedJet_neutralHadEnergyFraction", &BoostedJet_neutralHadEnergyFraction_, &b_BoostedJet_neutralHadEnergyFraction);
  Tree->SetBranchAddress("BoostedJet_neutralEmEnergyFraction", &BoostedJet_neutralEmEnergyFraction_, &b_BoostedJet_neutralEmEnergyFraction);
  Tree->SetBranchAddress("BoostedJet_chargedEmEnergyFraction", &BoostedJet_chargedEmEnergyFraction_, &b_BoostedJet_chargedEmEnergyFraction);
  Tree->SetBranchAddress("BoostedJet_numberOfConstituents", &BoostedJet_numberOfConstituents_, &b_BoostedJet_numberOfConstituents);
  Tree->SetBranchAddress("BoostedJet_chargedHadronEnergyFraction", &BoostedJet_chargedHadronEnergyFraction_, &b_BoostedJet_chargedHadronEnergyFraction);
  Tree->SetBranchAddress("BoostedJet_chargedMultiplicity", &BoostedJet_chargedMultiplicity_, &b_BoostedJet_chargedMultiplicity);
  Tree->SetBranchAddress("BoostedJet_puppi_tau1",         &BoostedJet_puppi_tau1_,         &b_BoostedJet_puppi_tau1);
  Tree->SetBranchAddress("BoostedJet_puppi_tau2",         &BoostedJet_puppi_tau2_,         &b_BoostedJet_puppi_tau2);
  Tree->SetBranchAddress("BoostedJet_puppi_tau3",         &BoostedJet_puppi_tau3_,         &b_BoostedJet_puppi_tau3);
  Tree->SetBranchAddress("BoostedJet_tau1",         &BoostedJet_tau1_,         &b_BoostedJet_tau1);
  Tree->SetBranchAddress("BoostedJet_tau2",         &BoostedJet_tau2_,         &b_BoostedJet_tau2);
  Tree->SetBranchAddress("BoostedJet_tau3",         &BoostedJet_tau3_,         &b_BoostedJet_tau3);
  Tree->SetBranchAddress("BoostedJet_pruned_mass",  &BoostedJet_pruned_mass_,  &b_BoostedJet_pruned_mass);
  Tree->SetBranchAddress("patElectron_pt",&patElectron_pt_,&b_patElectron_pt);
  Tree->SetBranchAddress("patElectron_eta",&patElectron_eta_,&b_patElectron_eta);
  Tree->SetBranchAddress("patElectron_phi",&patElectron_phi_,&b_patElectron_phi);
  Tree->SetBranchAddress("patElectron_energy",&patElectron_energy_,&b_patElectron_energy);
  Tree->SetBranchAddress("patElectron_SCeta",&patElectron_SCeta_,&b_patElectron_SCeta);
  Tree->SetBranchAddress("patElectron_charge",&patElectron_charge_,&b_patElectron_charge);
  Tree->SetBranchAddress("patElectron_isPassVeto",&patElectron_isPassVeto_,&b_patElectron_isPassVeto);          
  Tree->SetBranchAddress("patElectron_isPassLoose",&patElectron_isPassLoose_,&b_patElectron_isPassLoose);
  Tree->SetBranchAddress("patElectron_isPassMedium",&patElectron_isPassMedium_,&b_patElectron_isPassMedium);
  Tree->SetBranchAddress("patElectron_isPassTight",&patElectron_isPassTight_,&b_patElectron_isPassTight);
  Tree->SetBranchAddress("patElectron_isPassHEEPId",&patElectron_isPassHEEPId_,&b_patElectron_isPassHEEPId);
  Tree->SetBranchAddress("patElectron_passConversionVeto",&patElectron_passConversionVeto_,&b_patElectron_passConversionVeto); 
  Tree->SetBranchAddress("patElectron_inCrack",&patElectron_inCrack_,&b_patElectron_inCrack);
  Tree->SetBranchAddress("patElectron_isMatchedToTrigger",&patElectron_isMatchedToTrigger_,&b_patElectron_isMatchedToTrigger);
  Tree->SetBranchAddress("Muon_pt",&Muon_pt_,&b_Muon_pt);
  Tree->SetBranchAddress("Muon_eta",&Muon_eta_,&b_Muon_eta);
  Tree->SetBranchAddress("Muon_phi",&Muon_phi_,&b_Muon_phi);
  Tree->SetBranchAddress("Muon_energy",&Muon_energy_,&b_Muon_energy);
  Tree->SetBranchAddress("Muon_charge",&Muon_charge_,&b_Muon_charge);
  Tree->SetBranchAddress("Muon_tight",&Muon_tight_,&b_Muon_tight);
  Tree->SetBranchAddress("Muon_medium",&Muon_medium_,&b_Muon_medium);
  Tree->SetBranchAddress("Muon_loose",&Muon_loose_,&b_Muon_loose);
  Tree->SetBranchAddress("Met_type1PF_pt",          &Met_type1PF_pt_,          &b_Met_type1PF_pt);
  Tree->SetBranchAddress("Met_type1PF_phi",         &Met_type1PF_phi_,         &b_Met_type1PF_phi);
  Tree->SetBranchAddress("Met_type1PF_sumEt",         &Met_type1PF_sumEt_,         &b_Met_type1PF_sumEt);
  Tree->SetBranchAddress("Muon_relIsoDeltaBetaR04",&Muon_relIsoDeltaBetaR04_,&b_Muon_relIsoDeltaBetaR04);
  Tree->SetBranchAddress("Muon_isMatchedToTrigger",&Muon_isMatchedToTrigger_,&b_Muon_isMatchedToTrigger);
  Tree->SetBranchAddress("Flag_goodVertices",&Flag_goodVertices_,&b_Flag_goodVertices);
  Tree->SetBranchAddress("Flag_globalSuperTightHalo2016Filter",&Flag_globalSuperTightHalo2016Filter_,&b_Flag_globalSuperTightHalo2016Filter);
  //Tree->SetBranchAddress("Flag_CSCTightHalo2015Filter",&Flag_CSCTightHalo2015Filter_,&b_Flag_CSCTightHalo2015Filter);
  Tree->SetBranchAddress("Flag_HBHENoiseFilter",&Flag_HBHENoiseFilter_,&b_Flag_HBHENoiseFilter);
  Tree->SetBranchAddress("Flag_HBHENoiseIsoFilter",&Flag_HBHENoiseIsoFilter_,&b_Flag_HBHENoiseIsoFilter);
  Tree->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter",&Flag_EcalDeadCellTriggerPrimitiveFilter_,&b_Flag_EcalDeadCellTriggerPrimitiveFilter);
  Tree->SetBranchAddress("Flag_BadPFMuonFilter",&Flag_BadPFMuonFilter_,&b_Flag_BadPFMuonFilter);
  Tree->SetBranchAddress("Flag_BadChargedCandidateFilter",&Flag_BadChargedCandidateFilter_,&b_Flag_BadChargedCandidateFilter);
  Tree->SetBranchAddress("Flag_ecalBadCalibReducedMINIAODFilter",&Flag_ecalBadCalibReducedMINIAODFilter_,&b_Flag_ecalBadCalibReducedMINIAODFilter);
  Tree->SetBranchAddress("Flag_eeBadScFilter",&Flag_eeBadScFilter_,&b_Flag_eeBadScFilter);
  Tree->SetBranchAddress("HLT_DoubleEle33_CaloIdL_MW",&HLT_DoubleEle33_CaloIdL_MW_,&b_HLT_DoubleEle33_CaloIdL_MW);
   Tree->SetBranchAddress("HLT_Mu50",&HLT_Mu50_,&b_HLT_Mu50);
   Tree->SetBranchAddress("HLT_TkMu50",&HLT_TkMu50_,&b_HLT_TkMu50);
  //Tree->SetBranchAddress("HLT_PFHT500_PFMET100_PFMHT100_IDTight", &HLT_PFHT500_PFMET100_PFMHT100_IDTight_, &b_HLT_PFHT500_PFMET100_PFMHT100_IDTight);
  //Tree->SetBranchAddress("HLT_PFHT700_PFMET85_PFMHT85_IDTight", &HLT_PFHT700_PFMET85_PFMHT85_IDTight_, &b_HLT_PFHT700_PFMET85_PFMHT85_IDTight);
  //Tree->SetBranchAddress("HLT_PFHT800_PFMET75_PFMHT75_IDTight", &HLT_PFHT800_PFMET75_PFMHT75_IDTight_, &b_HLT_PFHT800_PFMET75_PFMHT75_IDTight);
	Tree->SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight", &HLT_PFMET120_PFMHT120_IDTight_, &b_HLT_PFMET120_PFMHT120_IDTight);
	Tree->SetBranchAddress("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight", &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_, &b_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight);
  //Tree->SetBranchAddress("HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight", &HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight_,  &b_HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight);
  //Tree->SetBranchAddress("HLT_CaloJet500_NoJetID", &HLT_CaloJet500_NoJetID_, &b_HLT_CaloJet500_NoJetID);
  //Tree->SetBranchAddress("HLT_AK8PFJet500", &HLT_AK8PFJet500_,   &b_HLT_AK8PFJet500);
  // Tree->SetBranchAddress("HLT_PFJet500", &HLT_PFJet500_,         &b_HLT_PFJet500);
//
//                                 add.
  Tree->SetBranchAddress("HLT_PFHT900", &HLT_PFHT900_,         &b_HLT_PFHT900);
  Tree->SetBranchAddress("HLT_PFHT450_SixJet40_BTagCSV_p056", &HLT_PFHT450_SixJet40_BTagCSV_p056_,         &b_HLT_PFHT450_SixJet40_BTagCSV_p056);
  Tree->SetBranchAddress("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056", &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_,         &b_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056);
//
//
  Tree->SetBranchAddress("nBestVtx",&nBestVtx_,&b_nBestVtx);
  Tree->SetBranchAddress("PUWeight",&PUWeight_,&b_PUWeight);
  //Tree->SetBranchAddress("PUWeightUP",&PUWeightUP_,&b_PUWeightUP);
  //Tree->SetBranchAddress("PUWeightDOWN",&PUWeightDOWN_,&b_PUWeightDOWN);
  Tree->SetBranchAddress("EVENT_event",&EVENT_event_,&b_EVENT_event);
  Tree->SetBranchAddress("EVENT_run",&EVENT_run_,&b_EVENT_run);
  Tree->SetBranchAddress("EVENT_lumiBlock",&EVENT_lumiBlock_,&b_EVENT_lumiBlock);
  Tree->SetBranchAddress("EVENT_genHT",&EVENT_genHT_,&b_EVENT_genHT);
	//what is Gen? what does data do?
  if(!data) Tree->SetBranchAddress("Gen_pt",&Gen_pt_,&b_Gen_pt);
  if(!data) Tree->SetBranchAddress("Gen_eta",&Gen_eta_,&b_Gen_eta);
  if(!data) Tree->SetBranchAddress("Gen_phi",&Gen_phi_,&b_Gen_phi);
  if(!data) Tree->SetBranchAddress("Gen_pdg_id",&Gen_pdg_id_,&b_Gen_pdg_id);
  if(!data) Tree->SetBranchAddress("Gen_motherpdg_id",&Gen_motherpdg_id_,&b_Gen_motherpdg_id);
	//?what is these?
  Tree->SetBranchAddress("EVENT_genWeight",&genWeight_,&b_genWeight);
  Tree->SetBranchAddress("EVENT_genWeights",&genWeights_,&b_genWeights);
  Tree->SetBranchAddress("EVENT_prefiringweight",&EVENT_prefiringweight_,&b_EVENT_prefiringweight);
  Tree->SetBranchAddress("EVENT_prefiringweightup",&EVENT_prefiringweightup_,&b_EVENT_prefiringweightup);
  Tree->SetBranchAddress("EVENT_prefiringweightdown",&EVENT_prefiringweightdown_,&b_EVENT_prefiringweightdown);
  //?what does category do?
  NewTree->Branch("category0",         &category0,         "category0/I"         );
  NewTree->Branch("category1",         &category1,         "category1/I"         );
  NewTree->Branch("category2",         &category2,         "category2/I"         );
  NewTree->Branch("TopMass",           &TopMass,           "TopMass/F"           );
  NewTree->Branch("TopMassMerged",     &TopMassMerged,     "TopMassMerged/F"     );
  NewTree->Branch("TopMassPartial",    &TopMassPartial,    "TopMassPartial/F"    );
  NewTree->Branch("TopMassResolved",   &TopMassResolved,   "TopMassResolved/F"   );
  NewTree->Branch("TopPt",             &TopPt,             "TopPt/F"             );
  NewTree->Branch("TopPtMerged",       &TopPtMerged,       "TopPtMerged/F"       );
  NewTree->Branch("TopPtPartial",      &TopPtPartial,      "TopPtPartial/F"      );
  NewTree->Branch("TopPtResolved",     &TopPtResolved,     "TopPtResolved/F"     );
  NewTree->Branch("TopEta",            &TopEta,            "TopEta/F"            );
  NewTree->Branch("TopEtaMerged",      &TopEtaMerged,      "TopEtaMerged/F"      );
  NewTree->Branch("TopEtaPartial",     &TopEtaPartial,     "TopEtaPartial/F"     );
  NewTree->Branch("TopEtaResolved",    &TopEtaResolved,    "TopEtaResolved/F"    );
  NewTree->Branch("TopPhi",            &TopPhi,            "TopPhi/F"            );
  NewTree->Branch("TopPhiMerged",      &TopPhiMerged,      "TopPhiMerged/F"      );
  NewTree->Branch("TopPhiPartial",     &TopPhiPartial,     "TopPhiPartial/F"     );
  NewTree->Branch("TopPhiResolved",    &TopPhiResolved,    "TopPhiResolved/F"    );
  NewTree->Branch("WMassResolved1",    &WMassResolved1,    "WMassResolved1/F"    );
  NewTree->Branch("WMassResolved2",    &WMassResolved2,    "WMassResolved2/F"    );
  NewTree->Branch("WMassResolved3",    &WMassResolved3,    "WMassResolved3/F"    );
  NewTree->Branch("BMass",             &BMass,             "BMass/F"             );
  NewTree->Branch("BCSV",              &BCSV,              "BCSV/F"              );
  NewTree->Branch("BPt",               &BPt,               "BPt/F"               );
  NewTree->Branch("BEta",              &BEta,              "BEta/F"              );
  NewTree->Branch("BPhi",              &BPhi,              "BPhi/F"              );
  NewTree->Branch("ZMass",             &ZMass,             "ZMass/F"             );
  NewTree->Branch("ZPt",               &ZPt,               "ZPt/F"               );
  NewTree->Branch("ZEta",              &ZEta,              "ZEta/F"              );
  NewTree->Branch("ZPhi",              &ZPhi,              "ZPhi/F"              );
   NewTree->Branch("TprimeMass",        &TprimeMass,        "TprimeMass/F"        );
   NewTree->Branch("TprimePt",          &TprimePt,          "TprimePt/F"          );
   NewTree->Branch("TprimeEta",         &TprimeEta,         "TprimeEta/F"         );
   NewTree->Branch("TprimePhi",         &TprimePhi,         "TprimePhi/F"         );
   NewTree->Branch("TprimeResolvedMass",&TprimeResolvedMass,"TprimeResolvedMass/F");
   NewTree->Branch("TprimeResolvedPt",  &TprimeResolvedPt,  "TprimeResolvedPt/F"  );
   NewTree->Branch("TprimeResolvedEta", &TprimeResolvedEta, "TprimeResolvedEta/F" );
   NewTree->Branch("TprimeResolvedPhi", &TprimeResolvedPhi, "TprimeResolvedPhi/F" );
   NewTree->Branch("TprimePartialMass", &TprimePartialMass, "TprimePartialMass/F" );
   NewTree->Branch("TprimePartialPt",   &TprimePartialPt,   "TprimePartialPt/F"   );
   NewTree->Branch("TprimePartialEta",  &TprimePartialEta,  "TprimePartialEta/F"  );
   NewTree->Branch("TprimePartialPhi",  &TprimePartialPhi,  "TprimePartialPhi/F"  );
   NewTree->Branch("TprimeMergedMass",  &TprimeMergedMass,  "TprimeMergedMass/F"  );
   NewTree->Branch("TprimeMergedPt",    &TprimeMergedPt,    "TprimeMergedPt/F"    );
   NewTree->Branch("TprimeMergedEta",   &TprimeMergedEta,   "TprimeMergedEta/F"   );
 NewTree->Branch("TprimeMergedPhi",   &TprimeMergedPhi,   "TprimeMergedPhi/F"   );
 NewTree->Branch("Electron1Pt",       &Electron1Pt,       "Electron1Pt/F"       );
  //give no value of Electron1Pt other than -99
  NewTree->Branch("Electron2Pt",       &Electron2Pt,       "Electron2Pt/F"       );
  NewTree->Branch("Electron1E",        &Electron1E,        "Electron1E/F"        );
  NewTree->Branch("Electron2E",        &Electron2E,        "Electron2E/F"        );
  NewTree->Branch("Muon1Iso",          &Muon1Iso,          "Muon1Iso/F"          );
  NewTree->Branch("Muon2Iso",          &Muon2Iso,          "Muon2Iso/F"          );
  NewTree->Branch("Muon1Pt",           &Muon1Pt,           "Muon1Pt/F"           );
  NewTree->Branch("Muon2Pt",           &Muon2Pt,           "Muon2Pt/F"           );
  NewTree->Branch("Jet1ForwardEta",    &Jet1ForwardEta,    "Jet1ForwardEta/F"    );
  NewTree->Branch("Jet2ForwardEta",    &Jet2ForwardEta,    "Jet2ForwardEta/F"    );
  NewTree->Branch("Jet3ForwardEta",    &Jet3ForwardEta,    "Jet3ForwardEta/F"    );
  NewTree->Branch("Jet1ForwardPt",     &Jet1ForwardPt,     "Jet1ForwardPt/F"     );
  NewTree->Branch("Jet2ForwardPt",     &Jet2ForwardPt,     "Jet2ForwardPt/F"     );
  NewTree->Branch("Jet3ForwardPt",     &Jet3ForwardPt,     "Jet3ForwardPt/F"     );
  NewTree->Branch("Jet1ResolvedPt",    &Jet1ResolvedPt,    "Jet1ResolvedPt/F"    );
 NewTree->Branch("Jet2ResolvedPt",    &Jet2ResolvedPt,    "Jet2ResolvedPt/F"    );
 NewTree->Branch("Jet3ResolvedPt",    &Jet3ResolvedPt,    "Jet3ResolvedPt/F"    );
 NewTree->Branch("Jet1PartialPt",     &Jet1PartialPt,     "Jet1PartialPt/F"     );
  NewTree->Branch("Jet2PartialPt",     &Jet2PartialPt,     "Jet2PartialPt/F"     );
  NewTree->Branch("Jet1MergedPt",      &Jet1MergedPt,      "Jet1MergedPt/F"      );
  NewTree->Branch("Electron1Eta",      &Electron1Eta,      "Electron1Eta/F"      );
  NewTree->Branch("Electron2Eta",      &Electron2Eta,      "Electron2Eta/F"      );
  NewTree->Branch("Muon1Eta",          &Muon1Eta,          "Muon1Eta/F"          );
  NewTree->Branch("Muon2Eta",          &Muon2Eta,          "Muon2Eta/F"          );
  NewTree->Branch("Jet1ResolvedEta",   &Jet1ResolvedEta,   "Jet1ResolvedEta/F"   );
  NewTree->Branch("Jet2ResolvedEta",   &Jet2ResolvedEta,   "Jet2ResolvedEta/F"   );
  NewTree->Branch("Jet3ResolvedEta",   &Jet3ResolvedEta,   "Jet3ResolvedEta/F"   );
  NewTree->Branch("Jet1PartialEta",    &Jet1PartialEta,    "Jet1PartialEta/F"    );
  NewTree->Branch("Jet2PartialEta",    &Jet2PartialEta,    "Jet2PartialEta/F"    );
  NewTree->Branch("Jet1MergedEta",     &Jet1MergedEta,     "Jet1MergedEta/F"     );
  NewTree->Branch("MostForwardJetEta", &MostForwardJetEta, "MostForwardJetEta/F" );
  NewTree->Branch("MostForwardJetPt",  &MostForwardJetPt,  "MostForwardJetPt/F"  );
  NewTree->Branch("Electron1Phi",      &Electron1Phi,      "Electron1Phi/F"      );
  NewTree->Branch("Electron2Phi",      &Electron2Phi,      "Electron2Phi/F"      );
  NewTree->Branch("Muon1Phi",          &Muon1Phi,          "Muon1Phi/F"          );
  NewTree->Branch("Muon2Phi",          &Muon2Phi,          "Muon2Phi/F"          );
  NewTree->Branch("deltaPhiZTop",      &deltaPhiZTop,      "deltaPhiZTop/F"      );
  NewTree->Branch("deltaRZTop",        &deltaRZTop,        "deltaRZTop/F"        );
  NewTree->Branch("deltaPhiZB",        &deltaPhiZB,        "deltaPhiZB/F"        );
  NewTree->Branch("deltaRZB",          &deltaRZB,          "deltaRZB/F"          );
  NewTree->Branch("deltaREle1Ele2",    &deltaREle1Ele2,    "deltaREle1Ele2/F"    );
  NewTree->Branch("deltaRMuo1Muo2",    &deltaRMuo1Muo2,    "deltaRMuo1Muo2/F"    );
  NewTree->Branch("Massb1b2",          &Massb1b2,          "Massb1b2/F"          );
  NewTree->Branch("MinDeltaPhiJetMet", &MinDeltaPhiJetMet, "MinDeltaPhiJetMet/F" );
  NewTree->Branch("MinDeltaPhiBoostedJetMet", &MinDeltaPhiBoostedJetMet, "MinDeltaPhiBoostedJetMet/F" );
  NewTree->Branch("deltaRb1b2",        &deltaRb1b2,        "deltaRb1b2/F"        );
  NewTree->Branch("deltaRb1Lep1",      &deltaRb1Lep1,      "deltaRb1Lep1/F"      );
  NewTree->Branch("deltaRb1Lep2",      &deltaRb1Lep2,      "deltaRb1Lep2/F"      );
  NewTree->Branch("deltaRb2Lep1",      &deltaRb2Lep1,      "deltaRb2Lep1/F"      );
  NewTree->Branch("deltaRb2Lep2",      &deltaRb2Lep2,      "deltaRb2Lep2/F"      );
  NewTree->Branch("NumSelLeps",        &NumSelLeps,        "NumSelLeps/I"        );
//
//
  NewTree->Branch("NumSeEle",          &NumSeEle,          "NumSeEle/I");
  NewTree->Branch("NumSeMu",           &NumSeMu,            "NumSeMu/I");
  NewTree->Branch("InvariantMassJets",  &InvariantMassJets,   "InvariantMassJets/F");
  NewTree->Branch("Centrality",        &Centrality,       "Centrality/F");
  NewTree->Branch("Aplanarity",        &Aplanarity,        "Aplanarity/F")
//
//
  NewTree->Branch("NumSelJets",        &NumSelJets,        "NumSelJets/I"        );
  NewTree->Branch("NumSelForwardJets", &NumSelForwardJets, "NumSelForwardJets/I" );
  NewTree->Branch("NumSelBJetsL",      &NumSelBJetsL,      "NumSelBJetsL/I"      );
  NewTree->Branch("NumSelBJetsM",      &NumSelBJetsM,      "NumSelBJetsM/I"      );
  NewTree->Branch("NumSelBJetsT",      &NumSelBJetsT,      "NumSelBJetsT/I"      );
  NewTree->Branch("NumSelWJets",       &NumSelWJets,       "NumSelWJets/I"       );
  NewTree->Branch("NumSelTopJets",     &NumSelTopJets,     "NumSelTopJets/I"     );
  NewTree->Branch("NVertices",         &NVertices,         "NVertices/I"         );
  NewTree->Branch("HT",                &HT,                "HT/F"                );
  NewTree->Branch("MHT",                &MHT,                "MHT/F"             );
  NewTree->Branch("PUWeight",          &PUWeight,          "PUWeight/F"          );
  NewTree->Branch("PUWeightUP",        &PUWeightUP,        "PUWeightUP/F"        );
  NewTree->Branch("PUWeightDOWN",      &PUWeightDOWN,      "PUWeightDOWN/F"      );
  NewTree->Branch("getTrueNumInteractions",&getTrueNumInteractions,"getTrueNumInteractions/I");
  NewTree->Branch("w_for",             &w_for,             "w_for/F"             );
  NewTree->Branch("w_forUp",           &w_forUp,           "w_forUp/F"           );
  NewTree->Branch("w_forDown",         &w_forDown,         "w_forDown/F"         );
  NewTree->Branch("w_topJet",          &w_topJet,          "w_topJet/F"          );
  NewTree->Branch("w_topJetUp",        &w_topJetUp,        "w_topJetUp/F"        );
  NewTree->Branch("w_topJetDown",      &w_topJetDown,      "w_topJetDown/F"      );
  NewTree->Branch("w_WJet",            &w_WJet,            "w_WJet/F"            );
  NewTree->Branch("w_WJetUp",          &w_WJetUp,          "w_WJetUp/F"          );
  NewTree->Branch("w_WJetDown",        &w_WJetDown,        "w_WJetDown/F"        );
  NewTree->Branch("w_Muon1",           &w_Muon1,           "w_Muon1/F"           );
  NewTree->Branch("w_Muon2",           &w_Muon2,           "w_Muon2/F"           );
  NewTree->Branch("w_Muon1Up",         &w_Muon1Up,         "w_Muon1Up/F"         );
  NewTree->Branch("w_Muon2Up",         &w_Muon2Up,         "w_Muon2Up/F"         );
  NewTree->Branch("w_Muon1Down",       &w_Muon1Down,       "w_Muon1Down/F"       );
  NewTree->Branch("w_Muon2Down",       &w_Muon2Down,       "w_Muon2Down/F"       );
  NewTree->Branch("w_TrigMuon",        &w_TrigMuon,        "w_TrigMuon/F"        );
  NewTree->Branch("w_TrigMuonUp",      &w_TrigMuonUp,      "w_TrigMuonUp/F"      );
  NewTree->Branch("w_TrigMuonDown",    &w_TrigMuonDown,    "w_TrigMuonDown/F"    );
  NewTree->Branch("w_Electron1",       &w_Electron1,       "w_Electron1/F"       );
  NewTree->Branch("w_Electron2",       &w_Electron2,       "w_Electron2/F"       );
  NewTree->Branch("w_Electron1Up",     &w_Electron1Up,     "w_Electron1Up/F"     );
  NewTree->Branch("w_Electron2Up",     &w_Electron2Up,     "w_Electron2Up/F"     );
  NewTree->Branch("w_Electron1Down",   &w_Electron1Down,   "w_Electron1Down/F"   );
  NewTree->Branch("w_Electron2Down",   &w_Electron2Down,   "w_Electron2Down/F"   );
  NewTree->Branch("w_TrigElec",        &w_TrigElec,        "w_TrigElec/F"        );
  NewTree->Branch("w_TrigElecUp",      &w_TrigElecUp,      "w_TrigElecUp/F"      );
  NewTree->Branch("w_TrigElecDown",    &w_TrigElecDown,    "w_TrigElecDown/F"    );
  NewTree->Branch("w_ZToNuNu",         &w_ZToNuNu,         "w_ZToNuNu/F"         );
  NewTree->Branch("w_ZToNuNuUp",       &w_ZToNuNuUp,       "w_ZToNuNuUp/F"       );
  NewTree->Branch("w_ZToNuNuDown",     &w_ZToNuNuDown,     "w_ZToNuNuDown/F"     );
  NewTree->Branch("w_WToLNu",          &w_WToLNu,          "w_WToLNu/F"          );
  NewTree->Branch("w_WToLNuUp",        &w_WToLNuUp,        "w_WToLNuUp/F"        );
  NewTree->Branch("w_WToLNuDown",      &w_WToLNuDown,      "w_WToLNuDown/F"      );
  NewTree->Branch("w_ttbar",           &w_ttbar,           "w_ttbar/F"           );
  NewTree->Branch("w_ttbarUp",         &w_ttbarUp,         "w_ttbarUp/F"         );
  NewTree->Branch("w_ttbarDown",       &w_ttbarDown,       "w_ttbarDown/F"       );
  NewTree->Branch("w_Trig",            &w_Trig,            "w_Trig/F"            );
  NewTree->Branch("w_TrigUp",          &w_TrigUp,          "w_TrigUp/F"          );
  NewTree->Branch("w_TrigDown",        &w_TrigDown,        "w_TrigDown/F"        );
  NewTree->Branch("WMass",             &WMass,             "WMass/F"             );
  NewTree->Branch("WSubjet",           &WSubjet,           "WSubjet/F"           );
  NewTree->Branch("TopSoftMass",       &TopSoftMass,       "TopSoftMass/F"       );
  NewTree->Branch("TopSubjet",         &TopSubjet,         "TopSubjet/F"         );
  NewTree->Branch("w_Btag",            &w_Btag,            "w_Btag/F"            );
  NewTree->Branch("w_BtagUp",          &w_BtagUp,          "w_BtagUp/F"          );
  NewTree->Branch("w_BtagDown",        &w_BtagDown,        "w_BtagDown/F"        );
  NewTree->Branch("w_Btag1Up",         &w_Btag1Up,         "w_Btag1Up/F"         );
  NewTree->Branch("w_Btag1Down",       &w_Btag1Down,       "w_Btag1Down/F"       );
  NewTree->Branch("w_Btag2Up",         &w_Btag2Up,         "w_Btag2Up/F"         );
  NewTree->Branch("w_Btag2Down",       &w_Btag2Down,       "w_Btag2Down/F"       );
  NewTree->Branch("w_BtagLoose",       &w_BtagLoose,       "w_BtagLoose/F"       );
  NewTree->Branch("w_BtagLooseUp",     &w_BtagLooseUp,     "w_BtagLooseUp/F"     );
  NewTree->Branch("w_BtagLooseDown",   &w_BtagLooseDown,   "w_BtagLooseDown/F"   );
  NewTree->Branch("w_QCDUp",           &w_QCDUp,           "w_QCDUp/F"           );
  NewTree->Branch("w_QCDDown",         &w_QCDDown,         "w_QCDDown/F"         );
  NewTree->Branch("w_PDFUp",           &w_PDFUp,           "w_PDFUp/F"           );
  NewTree->Branch("w_PDFDown",         &w_PDFDown,         "w_PDFDown/F"         );
  NewTree->Branch("deltaPhiZTopResolved", &deltaPhiZTopResolved, "deltaPhiZTopResolved/F");
  NewTree->Branch("deltaRZTopResolved",   &deltaRZTopResolved,   "deltaRZTopResolved/F"  );
  NewTree->Branch("deltaPhiZTopPartial",  &deltaPhiZTopPartial,  "deltaPhiZTopPartial/F" );
  NewTree->Branch("deltaRZTopPartial",    &deltaRZTopPartial,    "deltaRZTopPartial/F"   );
  NewTree->Branch("deltaPhiZTopMerged",   &deltaPhiZTopMerged,   "deltaPhiZTopMerged/F"  );
  NewTree->Branch("deltaRZTopMerged",     &deltaRZTopMerged,     "deltaRZTopMerged/F"    );
  NewTree->Branch("deltaRbTop",           &deltaRbTop,           "deltaRbTop/F"          );
  NewTree->Branch("deltaPhiMetTop",       &deltaPhiMetTop,       "deltaPhiMetTop/F"      );
  NewTree->Branch("genWeight",            &genWeight,            "genWeight/F"           );
  NewTree->Branch("genWeights0",          &genWeights0,          "genWeights0/F"         );
  NewTree->Branch("genWeights1",          &genWeights1,          "genWeights1/F"         );
  NewTree->Branch("genWeights2",          &genWeights2,          "genWeights2/F"         );
  NewTree->Branch("genWeights3",          &genWeights3,          "genWeights3/F"         );
  NewTree->Branch("genWeights4",          &genWeights4,          "genWeights4/F"         );
  NewTree->Branch("genWeights5",          &genWeights5,          "genWeights5/F"         );
  NewTree->Branch("genWeights6",          &genWeights6,          "genWeights6/F"         );
  NewTree->Branch("genWeights7",          &genWeights7,          "genWeights7/F"         );
  NewTree->Branch("genWeights8",          &genWeights8,          "genWeights8/F"         );
  NewTree->Branch("genWeights9",          &genWeights9,          "genWeights9/F"         );
  NewTree->Branch("genWeights10",         &genWeights10,         "genWeights10/F"        );
  NewTree->Branch("genWeights11",         &genWeights11,         "genWeights11/F"        );
  NewTree->Branch("genWeights12",         &genWeights12,         "genWeights12/F"        );
  NewTree->Branch("genWeights13",         &genWeights13,         "genWeights13/F"        );
  NewTree->Branch("genWeights14",         &genWeights14,         "genWeights14/F"        );
  NewTree->Branch("genWeights15",         &genWeights15,         "genWeights15/F"        );
  NewTree->Branch("genWeights16",         &genWeights16,         "genWeights16/F"        );
  NewTree->Branch("genWeights17",         &genWeights17,         "genWeights17/F"        );
  NewTree->Branch("genWeights18",         &genWeights18,         "genWeights18/F"        );
  NewTree->Branch("genWeights19",         &genWeights19,         "genWeights19/F"        );
  NewTree->Branch("genWeights20",         &genWeights20,         "genWeights20/F"        );
  NewTree->Branch("genWeights21",         &genWeights21,         "genWeights21/F"        );
  NewTree->Branch("genWeights22",         &genWeights22,         "genWeights22/F"        );
  NewTree->Branch("genWeights23",         &genWeights23,         "genWeights23/F"        );
  NewTree->Branch("genWeights24",         &genWeights24,         "genWeights24/F"        );
  NewTree->Branch("genWeights25",         &genWeights25,         "genWeights25/F"        );
  NewTree->Branch("genWeights26",         &genWeights26,         "genWeights26/F"        );
  NewTree->Branch("genWeights27",         &genWeights27,         "genWeights27/F"        );
  NewTree->Branch("genWeights28",         &genWeights28,         "genWeights28/F"        );
  NewTree->Branch("genWeights29",         &genWeights29,         "genWeights29/F"        );
  NewTree->Branch("genWeights30",         &genWeights30,         "genWeights30/F"        );
  NewTree->Branch("genWeights31",         &genWeights31,         "genWeights31/F"        );
  NewTree->Branch("genWeights32",         &genWeights32,         "genWeights32/F"        );
  NewTree->Branch("genWeights33",         &genWeights33,         "genWeights33/F"        );
  NewTree->Branch("genWeights34",         &genWeights34,         "genWeights34/F"        );
  NewTree->Branch("genWeights35",         &genWeights35,         "genWeights35/F"        );
  NewTree->Branch("genWeights36",         &genWeights36,         "genWeights36/F"        );
  NewTree->Branch("genWeights37",         &genWeights37,         "genWeights37/F"        );
  NewTree->Branch("genWeights38",         &genWeights38,         "genWeights38/F"        );
  NewTree->Branch("genWeights39",         &genWeights39,         "genWeights39/F"        );
  NewTree->Branch("genWeights40",         &genWeights40,         "genWeights40/F"        );
  NewTree->Branch("genWeights41",         &genWeights41,         "genWeights41/F"        );
  NewTree->Branch("genWeights42",         &genWeights42,         "genWeights42/F"        );
  NewTree->Branch("genWeights43",         &genWeights43,         "genWeights43/F"        );
  NewTree->Branch("genWeights44",         &genWeights44,         "genWeights44/F"        );
  NewTree->Branch("genWeights45",         &genWeights45,         "genWeights45/F"        );
  NewTree->Branch("genWeights46",         &genWeights46,         "genWeights46/F"        );
  NewTree->Branch("genWeights47",         &genWeights47,         "genWeights47/F"        );
  NewTree->Branch("genWeights48",         &genWeights48,         "genWeights48/F"        );
  NewTree->Branch("genWeights49",         &genWeights49,         "genWeights49/F"        );
  NewTree->Branch("genWeights50",         &genWeights50,         "genWeights50/F"        );
  NewTree->Branch("genWeights51",         &genWeights51,         "genWeights51/F"        );
  NewTree->Branch("genWeights52",         &genWeights52,         "genWeights52/F"        );
  NewTree->Branch("genWeights53",         &genWeights53,         "genWeights53/F"        );
  NewTree->Branch("genWeights54",         &genWeights54,         "genWeights54/F"        );
  NewTree->Branch("genWeights55",         &genWeights55,         "genWeights55/F"        );
  NewTree->Branch("genWeights56",         &genWeights56,         "genWeights56/F"        );
  NewTree->Branch("genWeights57",         &genWeights57,         "genWeights57/F"        );
  NewTree->Branch("genWeights58",         &genWeights58,         "genWeights58/F"        );
  NewTree->Branch("genWeights59",         &genWeights59,         "genWeights59/F"        );
  NewTree->Branch("genWeights60",         &genWeights60,         "genWeights60/F"        );
  NewTree->Branch("genWeights61",         &genWeights61,         "genWeights61/F"        );
  NewTree->Branch("genWeights62",         &genWeights62,         "genWeights62/F"        );
  NewTree->Branch("genWeights63",         &genWeights63,         "genWeights63/F"        );
  NewTree->Branch("genWeights64",         &genWeights64,         "genWeights64/F"        );
  NewTree->Branch("genWeights65",         &genWeights65,         "genWeights65/F"        );
  NewTree->Branch("genWeights66",         &genWeights66,         "genWeights66/F"        );
  NewTree->Branch("genWeights67",         &genWeights67,         "genWeights67/F"        );
  NewTree->Branch("genWeights68",         &genWeights68,         "genWeights68/F"        );
  NewTree->Branch("genWeights69",         &genWeights69,         "genWeights69/F"        );
  NewTree->Branch("genWeights70",         &genWeights70,         "genWeights70/F"        );
  NewTree->Branch("genWeights71",         &genWeights71,         "genWeights71/F"        );
  NewTree->Branch("genWeights72",         &genWeights72,         "genWeights72/F"        );
  NewTree->Branch("genWeights73",         &genWeights73,         "genWeights73/F"        );
  NewTree->Branch("genWeights74",         &genWeights74,         "genWeights74/F"        );
  NewTree->Branch("genWeights75",         &genWeights75,         "genWeights75/F"        );
  NewTree->Branch("genWeights76",         &genWeights76,         "genWeights76/F"        );
  NewTree->Branch("genWeights77",         &genWeights77,         "genWeights77/F"        );
  NewTree->Branch("genWeights78",         &genWeights78,         "genWeights78/F"        );
  NewTree->Branch("genWeights79",         &genWeights79,         "genWeights79/F"        );
  NewTree->Branch("genWeights80",         &genWeights80,         "genWeights80/F"        );
  NewTree->Branch("genWeights81",         &genWeights81,         "genWeights81/F"        );
  NewTree->Branch("genWeights82",         &genWeights82,         "genWeights82/F"        );
  NewTree->Branch("genWeights83",         &genWeights83,         "genWeights83/F"        );
  NewTree->Branch("genWeights84",         &genWeights84,         "genWeights84/F"        );
  NewTree->Branch("genWeights85",         &genWeights85,         "genWeights85/F"        );
  NewTree->Branch("genWeights86",         &genWeights86,         "genWeights86/F"        );
  NewTree->Branch("genWeights87",         &genWeights87,         "genWeights87/F"        );
  NewTree->Branch("genWeights88",         &genWeights88,         "genWeights88/F"        );
  NewTree->Branch("genWeights89",         &genWeights89,         "genWeights89/F"        );
  NewTree->Branch("genWeights90",         &genWeights90,         "genWeights90/F"        );
  NewTree->Branch("genWeights91",         &genWeights91,         "genWeights91/F"        );
  NewTree->Branch("genWeights92",         &genWeights92,         "genWeights92/F"        );
  NewTree->Branch("genWeights93",         &genWeights93,         "genWeights93/F"        );
  NewTree->Branch("genWeights94",         &genWeights94,         "genWeights94/F"        );
  NewTree->Branch("genWeights95",         &genWeights95,         "genWeights95/F"        );
  NewTree->Branch("genWeights96",         &genWeights96,         "genWeights96/F"        );
  NewTree->Branch("genWeights97",         &genWeights97,         "genWeights97/F"        );
  NewTree->Branch("genWeights98",         &genWeights98,         "genWeights98/F"        );
  NewTree->Branch("genWeights99",         &genWeights99,         "genWeights99/F"        );
  NewTree->Branch("genWeights100",        &genWeights100,        "genWeights100/F"       );
  NewTree->Branch("genWeights101",        &genWeights101,        "genWeights101/F"       );
  NewTree->Branch("genWeights102",        &genWeights102,        "genWeights102/F"       );
  NewTree->Branch("genWeights103",        &genWeights103,        "genWeights103/F"       );
  NewTree->Branch("genWeights104",        &genWeights104,        "genWeights104/F"       );
  NewTree->Branch("genWeights105",        &genWeights105,        "genWeights105/F"       );
  NewTree->Branch("genWeights106",        &genWeights106,        "genWeights106/F"       );
  NewTree->Branch("genWeights107",        &genWeights107,        "genWeights107/F"       );
  NewTree->Branch("genWeights108",        &genWeights108,        "genWeights108/F"       );
  NewTree->Branch("genWeights109",        &genWeights109,        "genWeights109/F"       );
  NewTree->Branch("genWeights110",        &genWeights110,        "genWeights110/F"       );
  NewTree->Branch("genWeights111",        &genWeights111,        "genWeights111/F"       );
  NewTree->Branch("genWeights112",        &genWeights112,        "genWeights112/F"       );
  NewTree->Branch("genWeights113",        &genWeights113,        "genWeights113/F"       );
  NewTree->Branch("genWeights114",        &genWeights114,        "genWeights114/F"       );
  NewTree->Branch("genWeights115",        &genWeights115,        "genWeights115/F"       );
  NewTree->Branch("genWeights116",        &genWeights116,        "genWeights116/F"       );
  NewTree->Branch("genWeights117",        &genWeights117,        "genWeights117/F"       );
  NewTree->Branch("genWeights118",        &genWeights118,        "genWeights118/F"       );
  NewTree->Branch("genWeights119",        &genWeights119,        "genWeights119/F"       );
  NewTree->Branch("genWeights120",        &genWeights120,        "genWeights120/F"       );
  NewTree->Branch("genWeights121",        &genWeights121,        "genWeights121/F"       );
  NewTree->Branch("genWeights122",        &genWeights122,        "genWeights122/F"       );
  NewTree->Branch("genWeights123",        &genWeights123,        "genWeights123/F"       );
  NewTree->Branch("genWeights124",        &genWeights124,        "genWeights124/F"       );
  NewTree->Branch("genWeights125",        &genWeights125,        "genWeights125/F"       );
  NewTree->Branch("genWeights126",        &genWeights126,        "genWeights126/F"       );
  NewTree->Branch("genWeights127",        &genWeights127,        "genWeights127/F"       );
  NewTree->Branch("genWeights128",        &genWeights128,        "genWeights128/F"       );
  NewTree->Branch("genWeights129",        &genWeights129,        "genWeights129/F"       );
  NewTree->Branch("genWeights130",        &genWeights130,        "genWeights130/F"       );
  NewTree->Branch("genWeights131",        &genWeights131,        "genWeights131/F"       );
  NewTree->Branch("genWeights132",        &genWeights132,        "genWeights132/F"       );
  NewTree->Branch("genWeights133",        &genWeights133,        "genWeights133/F"       );
  NewTree->Branch("genWeights134",        &genWeights134,        "genWeights134/F"       );
  NewTree->Branch("genWeights135",        &genWeights135,        "genWeights135/F"       );
  NewTree->Branch("genWeights136",        &genWeights136,        "genWeights136/F"       );
  NewTree->Branch("genWeights137",        &genWeights137,        "genWeights137/F"       );
  NewTree->Branch("genWeights138",        &genWeights138,        "genWeights138/F"       );
  NewTree->Branch("genWeights139",        &genWeights139,        "genWeights139/F"       );
  NewTree->Branch("genWeights140",        &genWeights140,        "genWeights140/F"       );
  NewTree->Branch("genWeights141",        &genWeights141,        "genWeights141/F"       );
  NewTree->Branch("genWeights142",        &genWeights142,        "genWeights142/F"       );
  NewTree->Branch("genWeights143",        &genWeights143,        "genWeights143/F"       );
  NewTree->Branch("genWeights144",        &genWeights144,        "genWeights144/F"       );
  NewTree->Branch("genWeights145",        &genWeights145,        "genWeights145/F"       );
  NewTree->Branch("genWeights146",        &genWeights146,        "genWeights146/F"       );
  NewTree->Branch("genWeights147",        &genWeights147,        "genWeights147/F"       );
  NewTree->Branch("genWeights148",        &genWeights148,        "genWeights148/F"       );
  NewTree->Branch("genWeights149",        &genWeights149,        "genWeights149/F"       );
  NewTree->Branch("genWeights150",        &genWeights150,        "genWeights150/F"       );
  NewTree->Branch("genWeights151",        &genWeights151,        "genWeights151/F"       );
  NewTree->Branch("genWeights152",        &genWeights152,        "genWeights152/F"       );
  NewTree->Branch("genWeights153",        &genWeights153,        "genWeights153/F"       );
  NewTree->Branch("genWeights154",        &genWeights154,        "genWeights154/F"       );
  NewTree->Branch("genWeights155",        &genWeights155,        "genWeights155/F"       );
  NewTree->Branch("genWeights156",        &genWeights156,        "genWeights156/F"       );
  NewTree->Branch("genWeights157",        &genWeights157,        "genWeights157/F"       );
  NewTree->Branch("genWeights158",        &genWeights158,        "genWeights158/F"       );
  NewTree->Branch("genWeights159",        &genWeights159,        "genWeights159/F"       );
  NewTree->Branch("genWeights160",        &genWeights160,        "genWeights160/F"       );
  NewTree->Branch("genWeights161",        &genWeights161,        "genWeights161/F"       );
  NewTree->Branch("genWeights162",        &genWeights162,        "genWeights162/F"       );
  NewTree->Branch("genWeights163",        &genWeights163,        "genWeights163/F"       );
  NewTree->Branch("genWeights164",        &genWeights164,        "genWeights164/F"       );
  NewTree->Branch("genWeights165",        &genWeights165,        "genWeights165/F"       );
  NewTree->Branch("genWeights166",        &genWeights166,        "genWeights166/F"       );
  NewTree->Branch("genWeights167",        &genWeights167,        "genWeights167/F"       );
  NewTree->Branch("genWeights168",        &genWeights168,        "genWeights168/F"       );
  NewTree->Branch("genWeights169",        &genWeights169,        "genWeights169/F"       );
  NewTree->Branch("genWeights170",        &genWeights170,        "genWeights170/F"       );
  NewTree->Branch("genWeights171",        &genWeights171,        "genWeights171/F"       );
  NewTree->Branch("genWeights172",        &genWeights172,        "genWeights172/F"       );
  NewTree->Branch("genWeights173",        &genWeights173,        "genWeights173/F"       );
  NewTree->Branch("genWeights174",        &genWeights174,        "genWeights174/F"       );
  NewTree->Branch("genWeights175",        &genWeights175,        "genWeights175/F"       );
  NewTree->Branch("genWeights176",        &genWeights176,        "genWeights176/F"       );
  NewTree->Branch("genWeights177",        &genWeights177,        "genWeights177/F"       );
  NewTree->Branch("genWeights178",        &genWeights178,        "genWeights178/F"       );
  NewTree->Branch("genWeights179",        &genWeights179,        "genWeights179/F"       );
  NewTree->Branch("genWeights180",        &genWeights180,        "genWeights180/F"       );
  NewTree->Branch("genWeights181",        &genWeights181,        "genWeights181/F"       );
  NewTree->Branch("genWeights182",        &genWeights182,        "genWeights182/F"       );
  NewTree->Branch("genWeights183",        &genWeights183,        "genWeights183/F"       );
  NewTree->Branch("genWeights184",        &genWeights184,        "genWeights184/F"       );
  NewTree->Branch("genWeights185",        &genWeights185,        "genWeights185/F"       );
  NewTree->Branch("genWeights186",        &genWeights186,        "genWeights186/F"       );
  NewTree->Branch("genWeights187",        &genWeights187,        "genWeights187/F"       );
  NewTree->Branch("genWeights188",        &genWeights188,        "genWeights188/F"       );
  NewTree->Branch("genWeights189",        &genWeights189,        "genWeights189/F"       );
  NewTree->Branch("genWeights190",        &genWeights190,        "genWeights190/F"       );
  NewTree->Branch("genWeights191",        &genWeights191,        "genWeights191/F"       );
  NewTree->Branch("genWeights192",        &genWeights192,        "genWeights192/F"       );
  NewTree->Branch("genWeights193",        &genWeights193,        "genWeights193/F"       );
  NewTree->Branch("genWeights194",        &genWeights194,        "genWeights194/F"       );
  NewTree->Branch("genWeights195",        &genWeights195,        "genWeights195/F"       );
  NewTree->Branch("genWeights196",        &genWeights196,        "genWeights196/F"       );
  NewTree->Branch("genWeights197",        &genWeights197,        "genWeights197/F"       );
  NewTree->Branch("genWeights198",        &genWeights198,        "genWeights198/F"       );
  NewTree->Branch("genWeights199",        &genWeights199,        "genWeights199/F"       );
  NewTree->Branch("genWeights200",        &genWeights200,        "genWeights200/F"       );
  NewTree->Branch("genWeights201",        &genWeights201,        "genWeights201/F"       );
  NewTree->Branch("genWeights202",        &genWeights202,        "genWeights202/F"       );
  NewTree->Branch("genWeights203",        &genWeights203,        "genWeights203/F"       );
  NewTree->Branch("genWeights204",        &genWeights204,        "genWeights204/F"       );
  NewTree->Branch("genWeights205",        &genWeights205,        "genWeights205/F"       );
  NewTree->Branch("genWeights206",        &genWeights206,        "genWeights206/F"       );
  NewTree->Branch("genWeights207",        &genWeights207,        "genWeights207/F"       );
  NewTree->Branch("genWeights208",        &genWeights208,        "genWeights208/F"       );
  NewTree->Branch("genWeights209",        &genWeights209,        "genWeights209/F"       );
  NewTree->Branch("genWeights210",        &genWeights210,        "genWeights210/F"       );
  NewTree->Branch("genWeights211",        &genWeights211,        "genWeights211/F"       );
  NewTree->Branch("genWeights212",        &genWeights212,        "genWeights212/F"       );
  NewTree->Branch("dQuark",&dQuark,"dQuark/I");
  NewTree->Branch("uQuark",&uQuark,"uQuark/I");
  NewTree->Branch("sQuark",&sQuark,"sQuark/I");
  NewTree->Branch("cQuark",&cQuark,"cQuark/I");
  NewTree->Branch("bQuark",&bQuark,"bQuark/I");
  NewTree->Branch("tQuark",&tQuark,"tQuark/I");
  NewTree->Branch("EVENT_event",&EVENT_event,"EVENT_event/I");
  NewTree->Branch("EVENT_run",&EVENT_run,"EVENT_run/I");
  NewTree->Branch("EVENT_lumiBlock",&EVENT_lumiBlock,"EVENT_lumiBlock/I");
  NewTree->Branch("EVENT_genHT",&EVENT_genHT,"EVENT_genHT/F");
  NewTree->Branch("prefiringweight",&prefiringweight,"prefiringweight/F");
  NewTree->Branch("prefiringweightup",&prefiringweightup,"prefiringweightup/F");
  NewTree->Branch("prefiringweightdown",&prefiringweightdown,"prefiringweightdown/F");
  NewTree->Branch("Met_pt",&Met_pt,"Met_pt/F");
  NewTree->Branch("Met_phi",&Met_phi,"Met_phi/F");
  NewTree->Branch("TransverseMassMetTop",&TransverseMassMetTop,"TransverseMassMetTop/F");

  
  NewTreeSB->Branch("category0",         &category0,         "category0/I"         );
  NewTreeSB->Branch("category1",         &category1,         "category1/I"         );
  NewTreeSB->Branch("category2",         &category2,         "category2/I"         );
  /*NewTreeSB->Branch("category3",         &category3,         "category3/I"         );
  NewTreeSB->Branch("category4",         &category4,         "category4/I"         );
  NewTreeSB->Branch("category5",         &category5,         "category5/I"         );
  NewTreeSB->Branch("category6",         &category6,         "category6/I"         );
  NewTreeSB->Branch("category7",         &category7,         "category7/I"         );*/
  NewTreeSB->Branch("TopMass",           &TopMass,           "TopMass/F"           );
  NewTreeSB->Branch("TopMassMerged",     &TopMassMerged,     "TopMassMerged/F"     );
  NewTreeSB->Branch("TopMassPartial",    &TopMassPartial,    "TopMassPartial/F"    );
  NewTreeSB->Branch("TopMassResolved",   &TopMassResolved,   "TopMassResolved/F"   );
  NewTreeSB->Branch("TopPt",             &TopPt,             "TopPt/F"             );
  NewTreeSB->Branch("TopPtMerged",       &TopPtMerged,       "TopPtMerged/F"       );
  NewTreeSB->Branch("TopPtPartial",      &TopPtPartial,      "TopPtPartial/F"      );
  NewTreeSB->Branch("TopPtResolved",     &TopPtResolved,     "TopPtResolved/F"     );
  NewTreeSB->Branch("TopEta",            &TopEta,            "TopEta/F"            );
  NewTreeSB->Branch("TopEtaMerged",      &TopEtaMerged,      "TopEtaMerged/F"      );
  NewTreeSB->Branch("TopEtaPartial",     &TopEtaPartial,     "TopEtaPartial/F"     );
  NewTreeSB->Branch("TopEtaResolved",    &TopEtaResolved,    "TopEtaResolved/F"    );
  NewTreeSB->Branch("TopPhi",            &TopPhi,            "TopPhi/F"            );
  NewTreeSB->Branch("TopPhiMerged",      &TopPhiMerged,      "TopPhiMerged/F"      );
  NewTreeSB->Branch("TopPhiPartial",     &TopPhiPartial,     "TopPhiPartial/F"     );
  NewTreeSB->Branch("TopPhiResolved",    &TopPhiResolved,    "TopPhiResolved/F"    );
  NewTreeSB->Branch("WMassResolved1",    &WMassResolved1,    "WMassResolved1/F"    );
  NewTreeSB->Branch("WMassResolved2",    &WMassResolved2,    "WMassResolved2/F"    );
  NewTreeSB->Branch("WMassResolved3",    &WMassResolved3,    "WMassResolved3/F"    );
  NewTreeSB->Branch("BMass",             &BMass,             "BMass/F"             );
  NewTreeSB->Branch("BCSV",              &BCSV,              "BCSV/F"              );
  NewTreeSB->Branch("BPt",               &BPt,               "BPt/F"               );
  NewTreeSB->Branch("BEta",              &BEta,              "BEta/F"              );
  NewTreeSB->Branch("BPhi",              &BPhi,              "BPhi/F"              );
  NewTreeSB->Branch("ZMass",             &ZMass,             "ZMass/F"             );
  NewTreeSB->Branch("ZPt",               &ZPt,               "ZPt/F"               );
  NewTreeSB->Branch("ZEta",              &ZEta,              "ZEta/F"              );
  NewTreeSB->Branch("ZPhi",              &ZPhi,              "ZPhi/F"              );
  NewTreeSB->Branch("TprimeMass",        &TprimeMass,        "TprimeMass/F"        );
  NewTreeSB->Branch("TprimePt",          &TprimePt,          "TprimePt/F"          );
  NewTreeSB->Branch("TprimeEta",         &TprimeEta,         "TprimeEta/F"         );
  NewTreeSB->Branch("TprimePhi",         &TprimePhi,         "TprimePhi/F"         );
  NewTreeSB->Branch("TprimeResolvedMass",&TprimeResolvedMass,"TprimeResolvedMass/F");
  NewTreeSB->Branch("TprimeResolvedPt",  &TprimeResolvedPt,  "TprimeResolvedPt/F"  );
  NewTreeSB->Branch("TprimeResolvedEta", &TprimeResolvedEta, "TprimeResolvedEta/F" );
  NewTreeSB->Branch("TprimeResolvedPhi", &TprimeResolvedPhi, "TprimeResolvedPhi/F" );
  NewTreeSB->Branch("TprimePartialMass", &TprimePartialMass, "TprimePartialMass/F" );
  NewTreeSB->Branch("TprimePartialPt",   &TprimePartialPt,   "TprimePartialPt/F"   );
  NewTreeSB->Branch("TprimePartialEta",  &TprimePartialEta,  "TprimePartialEta/F"  );
  NewTreeSB->Branch("TprimePartialPhi",  &TprimePartialPhi,  "TprimePartialPhi/F"  );
  NewTreeSB->Branch("TprimeMergedMass",  &TprimeMergedMass,  "TprimeMergedMass/F"  );
  NewTreeSB->Branch("TprimeMergedPt",    &TprimeMergedPt,    "TprimeMergedPt/F"    );
  NewTreeSB->Branch("TprimeMergedEta",   &TprimeMergedEta,   "TprimeMergedEta/F"   );
  NewTreeSB->Branch("TprimeMergedPhi",   &TprimeMergedPhi,   "TprimeMergedPhi/F"   );
  NewTreeSB->Branch("Electron1Pt",       &Electron1Pt,       "Electron1Pt/F"       );
  NewTreeSB->Branch("Electron2Pt",       &Electron2Pt,       "Electron2Pt/F"       );
  NewTreeSB->Branch("Electron1E",        &Electron1E,        "Electron1E/F"        );
  NewTreeSB->Branch("Electron2E",        &Electron2E,        "Electron2E/F"        );
  NewTreeSB->Branch("Muon1Iso",          &Muon1Iso,          "Muon1Iso/F"          );
  NewTreeSB->Branch("Muon2Iso",          &Muon2Iso,          "Muon2Iso/F"          );
  NewTreeSB->Branch("Muon1Pt",           &Muon1Pt,           "Muon1Pt/F"           );
  NewTreeSB->Branch("Muon2Pt",           &Muon2Pt,           "Muon2Pt/F"           );
  NewTreeSB->Branch("Jet1ForwardEta",    &Jet1ForwardEta,    "Jet1ForwardEta/F"    );
  NewTreeSB->Branch("Jet2ForwardEta",    &Jet2ForwardEta,    "Jet2ForwardEta/F"    );
  NewTreeSB->Branch("Jet3ForwardEta",    &Jet3ForwardEta,    "Jet3ForwardEta/F"    );
  NewTreeSB->Branch("Jet1ForwardPt",     &Jet1ForwardPt,     "Jet1ForwardPt/F"     );
  NewTreeSB->Branch("Jet2ForwardPt",     &Jet2ForwardPt,     "Jet2ForwardPt/F"     );
  NewTreeSB->Branch("Jet3ForwardPt",     &Jet3ForwardPt,     "Jet3ForwardPt/F"     );
  NewTreeSB->Branch("Jet1ResolvedPt",    &Jet1ResolvedPt,    "Jet1ResolvedPt/F"    );
  NewTreeSB->Branch("Jet2ResolvedPt",    &Jet2ResolvedPt,    "Jet2ResolvedPt/F"    );
  NewTreeSB->Branch("Jet3ResolvedPt",    &Jet3ResolvedPt,    "Jet3ResolvedPt/F"    );
  NewTreeSB->Branch("Jet1PartialPt",     &Jet1PartialPt,     "Jet1PartialPt/F"     );
  NewTreeSB->Branch("Jet2PartialPt",     &Jet2PartialPt,     "Jet2PartialPt/F"     );
  NewTreeSB->Branch("Jet1MergedPt",      &Jet1MergedPt,      "Jet1MergedPt/F"      );
  NewTreeSB->Branch("MostForwardJetEta", &MostForwardJetEta, "MostForwardJetEta/F" );
  NewTreeSB->Branch("MostForwardJetPt",  &MostForwardJetPt,  "MostForwardJetPt/F"  );
  NewTreeSB->Branch("Electron1Eta",      &Electron1Eta,      "Electron1Eta/F"      );
  NewTreeSB->Branch("Electron2Eta",      &Electron2Eta,      "Electron2Eta/F"      );
  NewTreeSB->Branch("Muon1Eta",          &Muon1Eta,          "Muon1Eta/F"          );
  NewTreeSB->Branch("Muon2Eta",          &Muon2Eta,          "Muon2Eta/F"          );
 NewTreeSB->Branch("Jet1ResolvedEta",   &Jet1ResolvedEta,   "Jet1ResolvedEta/F"   );
  NewTreeSB->Branch("Jet2ResolvedEta",   &Jet2ResolvedEta,   "Jet2ResolvedEta/F"   );
  NewTreeSB->Branch("Jet3ResolvedEta",   &Jet3ResolvedEta,   "Jet3ResolvedEta/F"   );
  NewTreeSB->Branch("Jet1PartialEta",    &Jet1PartialEta,    "Jet1PartialEta/F"    );
  NewTreeSB->Branch("Jet2PartialEta",    &Jet2PartialEta,    "Jet2PartialEta/F"    );
  NewTreeSB->Branch("Jet1MergedEta",     &Jet1MergedEta,     "Jet1MergedEta/F"     );
  NewTreeSB->Branch("Electron1Phi",      &Electron1Phi,      "Electron1Phi/F"      );
  NewTreeSB->Branch("Electron2Phi",      &Electron2Phi,      "Electron2Phi/F"      );
  NewTreeSB->Branch("Muon1Phi",          &Muon1Phi,          "Muon1Phi/F"          );
  NewTreeSB->Branch("Muon2Phi",          &Muon2Phi,          "Muon2Phi/F"          );
  NewTreeSB->Branch("deltaPhiZTop",      &deltaPhiZTop,      "deltaPhiZTop/F"      );
  NewTreeSB->Branch("deltaRZTop",        &deltaRZTop,        "deltaRZTop/F"        );
  NewTreeSB->Branch("deltaREle1Ele2",    &deltaREle1Ele2,    "deltaREle1Ele2/F"    );
  NewTreeSB->Branch("deltaRMuo1Muo2",    &deltaRMuo1Muo2,    "deltaRMuo1Muo2/F"    );
  NewTreeSB->Branch("Massb1b2",          &Massb1b2,          "Massb1b2/F"          );
  NewTreeSB->Branch("MinDeltaPhiJetMet", &MinDeltaPhiJetMet, "MinDeltaPhiJetMet/F" );
  NewTreeSB->Branch("MinDeltaPhiBoostedJetMet", &MinDeltaPhiBoostedJetMet, "MinDeltaPhiBoostedJetMet/F" );
  NewTreeSB->Branch("deltaRb1b2",        &deltaRb1b2,        "deltaRb1b2/F"        );
  NewTreeSB->Branch("deltaRb1Lep1",      &deltaRb1Lep1,      "deltaRb1Lep1/F"      );
  NewTreeSB->Branch("deltaRb1Lep2",      &deltaRb1Lep2,      "deltaRb1Lep2/F"      );
  NewTreeSB->Branch("deltaRb2Lep1",      &deltaRb2Lep1,      "deltaRb2Lep1/F"      );
  NewTreeSB->Branch("deltaRb2Lep2",      &deltaRb2Lep2,      "deltaRb2Lep2/F"      );
  NewTreeSB->Branch("NumSelLeps",        &NumSelLeps,        "NumSelLeps/I"        );
// 
//
 NewTreeSB->Branch("NumSeEle",      &NumSeEle,                "NumSeEle");
 NewTreeSB->Branch("NumSeMu",       &NumSeMu,                 "NumSeMu");
 NewTreeSB->Branch("InvariantMassJets",  &InvariantMassJets,   "InvariantMassJets");
//
//
  NewTreeSB->Branch("NumSelJets",        &NumSelJets,        "NumSelJets/I"        );
  NewTreeSB->Branch("NumSelForwardJets", &NumSelForwardJets, "NumSelForwardJets/I" );
  NewTreeSB->Branch("NumSelBJetsL",      &NumSelBJetsL,      "NumSelBJetsL/I"      );
  NewTreeSB->Branch("NumSelBJetsM",      &NumSelBJetsM,      "NumSelBJetsM/I"      );
  NewTreeSB->Branch("NumSelBJetsT",      &NumSelBJetsT,      "NumSelBJetsT/I"      );
  NewTreeSB->Branch("NumSelWJets",       &NumSelWJets,       "NumSelWJets/I"       );
  NewTreeSB->Branch("NumSelTopJets",     &NumSelTopJets,     "NumSelTopJets/I"     );
  NewTreeSB->Branch("NVertices",         &NVertices,         "NVertices/I"         );
  NewTreeSB->Branch("HT",                &HT,                "HT/F"                );
  NewTreeSB->Branch("MHT",                &MHT,                "MHT/F"                );
  NewTreeSB->Branch("PUWeight",          &PUWeight,          "PUWeight/F"          );
  NewTreeSB->Branch("PUWeightUP",        &PUWeightUP,        "PUWeightUP/F"        );
  NewTreeSB->Branch("PUWeightDOWN",      &PUWeightDOWN,      "PUWeightDOWN/F"      );
  NewTreeSB->Branch("getTrueNumInteractions",&getTrueNumInteractions,"getTrueNumInteractions/I");
  NewTreeSB->Branch("w_for",             &w_for,             "w_for/F"             );
  NewTreeSB->Branch("w_forUp",           &w_forUp,           "w_forUp/F"           );
  NewTreeSB->Branch("w_forDown",         &w_forDown,         "w_forDown/F"         );
  NewTreeSB->Branch("w_topJet",          &w_topJet,          "w_topJet/F"          );
  NewTreeSB->Branch("w_topJetUp",        &w_topJetUp,        "w_topJetUp/F"        );
  NewTreeSB->Branch("w_topJetDown",      &w_topJetDown,      "w_topJetDown/F"      );
  NewTreeSB->Branch("w_WJet",            &w_WJet,            "w_WJet/F"            );
  NewTreeSB->Branch("w_WJetUp",          &w_WJetUp,          "w_WJetUp/F"          );
  NewTreeSB->Branch("w_WJetDown",        &w_WJetDown,        "w_WJetDown/F"        );
  NewTreeSB->Branch("w_Muon1",           &w_Muon1,           "w_Muon1/F"           );
  NewTreeSB->Branch("w_Muon2",           &w_Muon2,           "w_Muon2/F"           );
  NewTreeSB->Branch("w_Muon1Up",         &w_Muon1Up,         "w_Muon1Up/F"         );
  NewTreeSB->Branch("w_Muon2Up",         &w_Muon2Up,         "w_Muon2Up/F"         );
  NewTreeSB->Branch("w_Muon1Down",       &w_Muon1Down,       "w_Muon1Down/F"       );
  NewTreeSB->Branch("w_Muon2Down",       &w_Muon2Down,       "w_Muon2Down/F"       );
  NewTreeSB->Branch("w_TrigMuon",        &w_TrigMuon,        "w_TrigMuon/F"        );
  NewTreeSB->Branch("w_TrigMuonUp",      &w_TrigMuonUp,      "w_TrigMuonUp/F"      );
  NewTreeSB->Branch("w_TrigMuonDown",    &w_TrigMuonDown,    "w_TrigMuonDown/F"    );
  NewTreeSB->Branch("w_Electron1",       &w_Electron1,       "w_Electron1/F"       );
  NewTreeSB->Branch("w_Electron2",       &w_Electron2,       "w_Electron2/F"       );
  NewTreeSB->Branch("w_Electron1Up",     &w_Electron1Up,     "w_Electron1Up/F"     );
  NewTreeSB->Branch("w_Electron2Up",     &w_Electron2Up,     "w_Electron2Up/F"     );
  NewTreeSB->Branch("w_Electron1Down",   &w_Electron1Down,   "w_Electron1Down/F"   );
  NewTreeSB->Branch("w_Electron2Down",   &w_Electron2Down,   "w_Electron2Down/F"   );
  NewTreeSB->Branch("w_TrigElec",        &w_TrigElec,        "w_TrigElec/F"        );
  NewTreeSB->Branch("w_TrigElecUp",      &w_TrigElecUp,      "w_TrigElecUp/F"      );
  NewTreeSB->Branch("w_TrigElecDown",    &w_TrigElecDown,    "w_TrigElecDown/F"    );
  NewTreeSB->Branch("w_ZToNuNu",         &w_ZToNuNu,         "w_ZToNuNu/F"         );
  NewTreeSB->Branch("w_ZToNuNuUp",       &w_ZToNuNuUp,       "w_ZToNuNuUp/F"       );
  NewTreeSB->Branch("w_ZToNuNuDown",     &w_ZToNuNuDown,     "w_ZToNuNuDown/F"     );
  NewTreeSB->Branch("w_WToLNu",          &w_WToLNu,          "w_WToLNu/F"          );
  NewTreeSB->Branch("w_WToLNuUp",        &w_WToLNuUp,        "w_WToLNuUp/F"        );
  NewTreeSB->Branch("w_WToLNuDown",      &w_WToLNuDown,      "w_WToLNuDown/F"      );
  NewTreeSB->Branch("w_ttbar",           &w_ttbar,           "w_ttbar/F"           );
  NewTreeSB->Branch("w_ttbarUp",         &w_ttbarUp,         "w_ttbarUp/F"         );
  NewTreeSB->Branch("w_ttbarDown",       &w_ttbarDown,       "w_ttbarDown/F"       );
  NewTreeSB->Branch("w_Trig",            &w_Trig,            "w_Trig/F"            );
  NewTreeSB->Branch("w_TrigUp",          &w_TrigUp,          "w_TrigUp/F"          );
  NewTreeSB->Branch("w_TrigDown",        &w_TrigDown,        "w_TrigDown/F"        );
  NewTreeSB->Branch("WMass",             &WMass,             "WMass/F"             );
  NewTreeSB->Branch("WSubjet",           &WSubjet,           "WSubjet/F"           );
  NewTreeSB->Branch("TopSoftMass",       &TopSoftMass,       "TopSoftMass/F"       );
  NewTreeSB->Branch("TopSubjet",         &TopSubjet,         "TopSubjet/F"         );
  NewTreeSB->Branch("w_Btag",            &w_Btag,            "w_Btag/F"            );
  NewTreeSB->Branch("w_BtagUp",          &w_BtagUp,          "w_BtagUp/F"          );
  NewTreeSB->Branch("w_BtagDown",        &w_BtagDown,        "w_BtagDown/F"        );
  NewTreeSB->Branch("w_Btag1Up",         &w_Btag1Up,         "w_Btag1Up/F"         );
  NewTreeSB->Branch("w_Btag1Down",       &w_Btag1Down,       "w_Btag1Down/F"       );
  NewTreeSB->Branch("w_Btag2Up",         &w_Btag2Up,         "w_Btag2Up/F"         );
  NewTreeSB->Branch("w_Btag2Down",       &w_Btag2Down,       "w_Btag2Down/F"       );
  NewTreeSB->Branch("w_BtagLoose",       &w_BtagLoose,       "w_BtagLoose/F"       );
  NewTreeSB->Branch("w_BtagLooseUp",     &w_BtagLooseUp,     "w_BtagLooseUp/F"     );
  NewTreeSB->Branch("w_BtagLooseDown",   &w_BtagLooseDown,   "w_BtagLooseDown/F"   );
  NewTreeSB->Branch("w_QCDUp",           &w_QCDUp,           "w_QCDUp/F"           );
  NewTreeSB->Branch("w_QCDDown",         &w_QCDDown,         "w_QCDDown/F"         );
  NewTreeSB->Branch("w_PDFUp",           &w_PDFUp,           "w_PDFUp/F"           );
  NewTreeSB->Branch("w_PDFDown",         &w_PDFDown,         "w_PDFDown/F"         );
  NewTreeSB->Branch("deltaPhiZTopResolved", &deltaPhiZTopResolved, "deltaPhiZTopResolved/F");
  NewTreeSB->Branch("deltaRZTopResolved",   &deltaRZTopResolved,   "deltaRZTopResolved/F"  );
  NewTreeSB->Branch("deltaPhiZTopPartial",  &deltaPhiZTopPartial,  "deltaPhiZTopPartial/F" );
  NewTreeSB->Branch("deltaRZTopPartial",    &deltaRZTopPartial,    "deltaRZTopPartial/F"   );
  NewTreeSB->Branch("deltaPhiZTopMerged",   &deltaPhiZTopMerged,   "deltaPhiZTopMerged/F"  );
  NewTreeSB->Branch("deltaRZTopMerged",     &deltaRZTopMerged,     "deltaRZTopMerged/F"    );
  NewTreeSB->Branch("deltaRbTop",           &deltaRbTop,           "deltaRbTop/F"          );
  NewTreeSB->Branch("deltaPhiMetTop",       &deltaPhiMetTop,       "deltaPhiMetTop/F"      );
  NewTreeSB->Branch("genWeight",            &genWeight,            "genWeight/F"           );
  NewTreeSB->Branch("genWeights0",          &genWeights0,          "genWeights0/F"         );
  NewTreeSB->Branch("genWeights1",          &genWeights1,          "genWeights1/F"         );
  NewTreeSB->Branch("genWeights2",          &genWeights2,          "genWeights2/F"         );
  NewTreeSB->Branch("genWeights3",          &genWeights3,          "genWeights3/F"         );
  NewTreeSB->Branch("genWeights4",          &genWeights4,          "genWeights4/F"         );
  NewTreeSB->Branch("genWeights5",          &genWeights5,          "genWeights5/F"         );
  NewTreeSB->Branch("genWeights6",          &genWeights6,          "genWeights6/F"         );
  NewTreeSB->Branch("genWeights7",          &genWeights7,          "genWeights7/F"         );
  NewTreeSB->Branch("genWeights8",          &genWeights8,          "genWeights8/F"         );
  NewTreeSB->Branch("genWeights9",          &genWeights9,          "genWeights9/F"         );
  NewTreeSB->Branch("genWeights10",         &genWeights10,         "genWeights10/F"        );
  NewTreeSB->Branch("genWeights11",         &genWeights11,         "genWeights11/F"        );
  NewTreeSB->Branch("genWeights12",         &genWeights12,         "genWeights12/F"        );
  NewTreeSB->Branch("genWeights13",         &genWeights13,         "genWeights13/F"        );
  NewTreeSB->Branch("genWeights14",         &genWeights14,         "genWeights14/F"        );
  NewTreeSB->Branch("genWeights15",         &genWeights15,         "genWeights15/F"        );
  NewTreeSB->Branch("genWeights16",         &genWeights16,         "genWeights16/F"        );
  NewTreeSB->Branch("genWeights17",         &genWeights17,         "genWeights17/F"        );
  NewTreeSB->Branch("genWeights18",         &genWeights18,         "genWeights18/F"        );
  NewTreeSB->Branch("genWeights19",         &genWeights19,         "genWeights19/F"        );
  NewTreeSB->Branch("genWeights20",         &genWeights20,         "genWeights20/F"        );
  NewTreeSB->Branch("genWeights21",         &genWeights21,         "genWeights21/F"        );
  NewTreeSB->Branch("genWeights22",         &genWeights22,         "genWeights22/F"        );
  NewTreeSB->Branch("genWeights23",         &genWeights23,         "genWeights23/F"        );
  NewTreeSB->Branch("genWeights24",         &genWeights24,         "genWeights24/F"        );
  NewTreeSB->Branch("genWeights25",         &genWeights25,         "genWeights25/F"        );
  NewTreeSB->Branch("genWeights26",         &genWeights26,         "genWeights26/F"        );
  NewTreeSB->Branch("genWeights27",         &genWeights27,         "genWeights27/F"        );
  NewTreeSB->Branch("genWeights28",         &genWeights28,         "genWeights28/F"        );
  NewTreeSB->Branch("genWeights29",         &genWeights29,         "genWeights29/F"        );
  NewTreeSB->Branch("genWeights30",         &genWeights30,         "genWeights30/F"        );
  NewTreeSB->Branch("genWeights31",         &genWeights31,         "genWeights31/F"        );
  NewTreeSB->Branch("genWeights32",         &genWeights32,         "genWeights32/F"        );
  NewTreeSB->Branch("genWeights33",         &genWeights33,         "genWeights33/F"        );
  NewTreeSB->Branch("genWeights34",         &genWeights34,         "genWeights34/F"        );
  NewTreeSB->Branch("genWeights35",         &genWeights35,         "genWeights35/F"        );
  NewTreeSB->Branch("genWeights36",         &genWeights36,         "genWeights36/F"        );
  NewTreeSB->Branch("genWeights37",         &genWeights37,         "genWeights37/F"        );
  NewTreeSB->Branch("genWeights38",         &genWeights38,         "genWeights38/F"        );
  NewTreeSB->Branch("genWeights39",         &genWeights39,         "genWeights39/F"        );
  NewTreeSB->Branch("genWeights40",         &genWeights40,         "genWeights40/F"        );
  NewTreeSB->Branch("genWeights41",         &genWeights41,         "genWeights41/F"        );
  NewTreeSB->Branch("genWeights42",         &genWeights42,         "genWeights42/F"        );
  NewTreeSB->Branch("genWeights43",         &genWeights43,         "genWeights43/F"        );
  NewTreeSB->Branch("genWeights44",         &genWeights44,         "genWeights44/F"        );
  NewTreeSB->Branch("genWeights45",         &genWeights45,         "genWeights45/F"        );
  NewTreeSB->Branch("genWeights46",         &genWeights46,         "genWeights46/F"        );
  NewTreeSB->Branch("genWeights47",         &genWeights47,         "genWeights47/F"        );
  NewTreeSB->Branch("genWeights48",         &genWeights48,         "genWeights48/F"        );
  NewTreeSB->Branch("genWeights49",         &genWeights49,         "genWeights49/F"        );
  NewTreeSB->Branch("genWeights50",         &genWeights50,         "genWeights50/F"        );
  NewTreeSB->Branch("genWeights51",         &genWeights51,         "genWeights51/F"        );
  NewTreeSB->Branch("genWeights52",         &genWeights52,         "genWeights52/F"        );
  NewTreeSB->Branch("genWeights53",         &genWeights53,         "genWeights53/F"        );
  NewTreeSB->Branch("genWeights54",         &genWeights54,         "genWeights54/F"        );
  NewTreeSB->Branch("genWeights55",         &genWeights55,         "genWeights55/F"        );
  NewTreeSB->Branch("genWeights56",         &genWeights56,         "genWeights56/F"        );
  NewTreeSB->Branch("genWeights57",         &genWeights57,         "genWeights57/F"        );
  NewTreeSB->Branch("genWeights58",         &genWeights58,         "genWeights58/F"        );
  NewTreeSB->Branch("genWeights59",         &genWeights59,         "genWeights59/F"        );
  NewTreeSB->Branch("genWeights60",         &genWeights60,         "genWeights60/F"        );
  NewTreeSB->Branch("genWeights61",         &genWeights61,         "genWeights61/F"        );
  NewTreeSB->Branch("genWeights62",         &genWeights62,         "genWeights62/F"        );
  NewTreeSB->Branch("genWeights63",         &genWeights63,         "genWeights63/F"        );
  NewTreeSB->Branch("genWeights64",         &genWeights64,         "genWeights64/F"        );
  NewTreeSB->Branch("genWeights65",         &genWeights65,         "genWeights65/F"        );
  NewTreeSB->Branch("genWeights66",         &genWeights66,         "genWeights66/F"        );
  NewTreeSB->Branch("genWeights67",         &genWeights67,         "genWeights67/F"        );
  NewTreeSB->Branch("genWeights68",         &genWeights68,         "genWeights68/F"        );
  NewTreeSB->Branch("genWeights69",         &genWeights69,         "genWeights69/F"        );
  NewTreeSB->Branch("genWeights70",         &genWeights70,         "genWeights70/F"        );
  NewTreeSB->Branch("genWeights71",         &genWeights71,         "genWeights71/F"        );
  NewTreeSB->Branch("genWeights72",         &genWeights72,         "genWeights72/F"        );
  NewTreeSB->Branch("genWeights73",         &genWeights73,         "genWeights73/F"        );
  NewTreeSB->Branch("genWeights74",         &genWeights74,         "genWeights74/F"        );
  NewTreeSB->Branch("genWeights75",         &genWeights75,         "genWeights75/F"        );
  NewTreeSB->Branch("genWeights76",         &genWeights76,         "genWeights76/F"        );
  NewTreeSB->Branch("genWeights77",         &genWeights77,         "genWeights77/F"        );
  NewTreeSB->Branch("genWeights78",         &genWeights78,         "genWeights78/F"        );
  NewTreeSB->Branch("genWeights79",         &genWeights79,         "genWeights79/F"        );
  NewTreeSB->Branch("genWeights80",         &genWeights80,         "genWeights80/F"        );
  NewTreeSB->Branch("genWeights81",         &genWeights81,         "genWeights81/F"        );
  NewTreeSB->Branch("genWeights82",         &genWeights82,         "genWeights82/F"        );
  NewTreeSB->Branch("genWeights83",         &genWeights83,         "genWeights83/F"        );
  NewTreeSB->Branch("genWeights84",         &genWeights84,         "genWeights84/F"        );
  NewTreeSB->Branch("genWeights85",         &genWeights85,         "genWeights85/F"        );
  NewTreeSB->Branch("genWeights86",         &genWeights86,         "genWeights86/F"        );
  NewTreeSB->Branch("genWeights87",         &genWeights87,         "genWeights87/F"        );
  NewTreeSB->Branch("genWeights88",         &genWeights88,         "genWeights88/F"        );
  NewTreeSB->Branch("genWeights89",         &genWeights89,         "genWeights89/F"        );
  NewTreeSB->Branch("genWeights90",         &genWeights90,         "genWeights90/F"        );
  NewTreeSB->Branch("genWeights91",         &genWeights91,         "genWeights91/F"        );
  NewTreeSB->Branch("genWeights92",         &genWeights92,         "genWeights92/F"        );
  NewTreeSB->Branch("genWeights93",         &genWeights93,         "genWeights93/F"        );
  NewTreeSB->Branch("genWeights94",         &genWeights94,         "genWeights94/F"        );
  NewTreeSB->Branch("genWeights95",         &genWeights95,         "genWeights95/F"        );
  NewTreeSB->Branch("genWeights96",         &genWeights96,         "genWeights96/F"        );
  NewTreeSB->Branch("genWeights97",         &genWeights97,         "genWeights97/F"        );
  NewTreeSB->Branch("genWeights98",         &genWeights98,         "genWeights98/F"        );
  NewTreeSB->Branch("genWeights99",         &genWeights99,         "genWeights99/F"        );
  NewTreeSB->Branch("genWeights100",        &genWeights100,        "genWeights100/F"       );
  NewTreeSB->Branch("genWeights101",        &genWeights101,        "genWeights101/F"       );
  NewTreeSB->Branch("genWeights102",        &genWeights102,        "genWeights102/F"       );
  NewTreeSB->Branch("genWeights103",        &genWeights103,        "genWeights103/F"       );
  NewTreeSB->Branch("genWeights104",        &genWeights104,        "genWeights104/F"       );
  NewTreeSB->Branch("genWeights105",        &genWeights105,        "genWeights105/F"       );
  NewTreeSB->Branch("genWeights106",        &genWeights106,        "genWeights106/F"       );
  NewTreeSB->Branch("genWeights107",        &genWeights107,        "genWeights107/F"       );
  NewTreeSB->Branch("genWeights108",        &genWeights108,        "genWeights108/F"       );
  NewTreeSB->Branch("genWeights109",        &genWeights109,        "genWeights109/F"       );
  NewTreeSB->Branch("genWeights110",        &genWeights110,        "genWeights110/F"       );
  NewTreeSB->Branch("genWeights111",        &genWeights111,        "genWeights111/F"       );
  NewTreeSB->Branch("genWeights112",        &genWeights112,        "genWeights112/F"       );
  NewTreeSB->Branch("genWeights113",        &genWeights113,        "genWeights113/F"       );
  NewTreeSB->Branch("genWeights114",        &genWeights114,        "genWeights114/F"       );
  NewTreeSB->Branch("genWeights115",        &genWeights115,        "genWeights115/F"       );
  NewTreeSB->Branch("genWeights116",        &genWeights116,        "genWeights116/F"       );
  NewTreeSB->Branch("genWeights117",        &genWeights117,        "genWeights117/F"       );
  NewTreeSB->Branch("genWeights118",        &genWeights118,        "genWeights118/F"       );
  NewTreeSB->Branch("genWeights119",        &genWeights119,        "genWeights119/F"       );
  NewTreeSB->Branch("genWeights120",        &genWeights120,        "genWeights120/F"       );
  NewTreeSB->Branch("genWeights121",        &genWeights121,        "genWeights121/F"       );
  NewTreeSB->Branch("genWeights122",        &genWeights122,        "genWeights122/F"       );
  NewTreeSB->Branch("genWeights123",        &genWeights123,        "genWeights123/F"       );
  NewTreeSB->Branch("genWeights124",        &genWeights124,        "genWeights124/F"       );
  NewTreeSB->Branch("genWeights125",        &genWeights125,        "genWeights125/F"       );
  NewTreeSB->Branch("genWeights126",        &genWeights126,        "genWeights126/F"       );
  NewTreeSB->Branch("genWeights127",        &genWeights127,        "genWeights127/F"       );
  NewTreeSB->Branch("genWeights128",        &genWeights128,        "genWeights128/F"       );
  NewTreeSB->Branch("genWeights129",        &genWeights129,        "genWeights129/F"       );
  NewTreeSB->Branch("genWeights130",        &genWeights130,        "genWeights130/F"       );
  NewTreeSB->Branch("genWeights131",        &genWeights131,        "genWeights131/F"       );
  NewTreeSB->Branch("genWeights132",        &genWeights132,        "genWeights132/F"       );
  NewTreeSB->Branch("genWeights133",        &genWeights133,        "genWeights133/F"       );
  NewTreeSB->Branch("genWeights134",        &genWeights134,        "genWeights134/F"       );
  NewTreeSB->Branch("genWeights135",        &genWeights135,        "genWeights135/F"       );
  NewTreeSB->Branch("genWeights136",        &genWeights136,        "genWeights136/F"       );
  NewTreeSB->Branch("genWeights137",        &genWeights137,        "genWeights137/F"       );
  NewTreeSB->Branch("genWeights138",        &genWeights138,        "genWeights138/F"       );
  NewTreeSB->Branch("genWeights139",        &genWeights139,        "genWeights139/F"       );
  NewTreeSB->Branch("genWeights140",        &genWeights140,        "genWeights140/F"       );
  NewTreeSB->Branch("genWeights141",        &genWeights141,        "genWeights141/F"       );
  NewTreeSB->Branch("genWeights142",        &genWeights142,        "genWeights142/F"       );
  NewTreeSB->Branch("genWeights143",        &genWeights143,        "genWeights143/F"       );
  NewTreeSB->Branch("genWeights144",        &genWeights144,        "genWeights144/F"       );
  NewTreeSB->Branch("genWeights145",        &genWeights145,        "genWeights145/F"       );
  NewTreeSB->Branch("genWeights146",        &genWeights146,        "genWeights146/F"       );
  NewTreeSB->Branch("genWeights147",        &genWeights147,        "genWeights147/F"       );
  NewTreeSB->Branch("genWeights148",        &genWeights148,        "genWeights148/F"       );
  NewTreeSB->Branch("genWeights149",        &genWeights149,        "genWeights149/F"       );
  NewTreeSB->Branch("genWeights150",        &genWeights150,        "genWeights150/F"       );
  NewTreeSB->Branch("genWeights151",        &genWeights151,        "genWeights151/F"       );
  NewTreeSB->Branch("genWeights152",        &genWeights152,        "genWeights152/F"       );
  NewTreeSB->Branch("genWeights153",        &genWeights153,        "genWeights153/F"       );
  NewTreeSB->Branch("genWeights154",        &genWeights154,        "genWeights154/F"       );
  NewTreeSB->Branch("genWeights155",        &genWeights155,        "genWeights155/F"       );
  NewTreeSB->Branch("genWeights156",        &genWeights156,        "genWeights156/F"       );
  NewTreeSB->Branch("genWeights157",        &genWeights157,        "genWeights157/F"       );
  NewTreeSB->Branch("genWeights158",        &genWeights158,        "genWeights158/F"       );
  NewTreeSB->Branch("genWeights159",        &genWeights159,        "genWeights159/F"       );
  NewTreeSB->Branch("genWeights160",        &genWeights160,        "genWeights160/F"       );
  NewTreeSB->Branch("genWeights161",        &genWeights161,        "genWeights161/F"       );
  NewTreeSB->Branch("genWeights162",        &genWeights162,        "genWeights162/F"       );
  NewTreeSB->Branch("genWeights163",        &genWeights163,        "genWeights163/F"       );
  NewTreeSB->Branch("genWeights164",        &genWeights164,        "genWeights164/F"       );
  NewTreeSB->Branch("genWeights165",        &genWeights165,        "genWeights165/F"       );
  NewTreeSB->Branch("genWeights166",        &genWeights166,        "genWeights166/F"       );
  NewTreeSB->Branch("genWeights167",        &genWeights167,        "genWeights167/F"       );
  NewTreeSB->Branch("genWeights168",        &genWeights168,        "genWeights168/F"       );
  NewTreeSB->Branch("genWeights169",        &genWeights169,        "genWeights169/F"       );
  NewTreeSB->Branch("genWeights170",        &genWeights170,        "genWeights170/F"       );
  NewTreeSB->Branch("genWeights171",        &genWeights171,        "genWeights171/F"       );
  NewTreeSB->Branch("genWeights172",        &genWeights172,        "genWeights172/F"       );
  NewTreeSB->Branch("genWeights173",        &genWeights173,        "genWeights173/F"       );
  NewTreeSB->Branch("genWeights174",        &genWeights174,        "genWeights174/F"       );
  NewTreeSB->Branch("genWeights175",        &genWeights175,        "genWeights175/F"       );
  NewTreeSB->Branch("genWeights176",        &genWeights176,        "genWeights176/F"       );
  NewTreeSB->Branch("genWeights177",        &genWeights177,        "genWeights177/F"       );
  NewTreeSB->Branch("genWeights178",        &genWeights178,        "genWeights178/F"       );
  NewTreeSB->Branch("genWeights179",        &genWeights179,        "genWeights179/F"       );
  NewTreeSB->Branch("genWeights180",        &genWeights180,        "genWeights180/F"       );
  NewTreeSB->Branch("genWeights181",        &genWeights181,        "genWeights181/F"       );
  NewTreeSB->Branch("genWeights182",        &genWeights182,        "genWeights182/F"       );
  NewTreeSB->Branch("genWeights183",        &genWeights183,        "genWeights183/F"       );
  NewTreeSB->Branch("genWeights184",        &genWeights184,        "genWeights184/F"       );
  NewTreeSB->Branch("genWeights185",        &genWeights185,        "genWeights185/F"       );
  NewTreeSB->Branch("genWeights186",        &genWeights186,        "genWeights186/F"       );
  NewTreeSB->Branch("genWeights187",        &genWeights187,        "genWeights187/F"       );
  NewTreeSB->Branch("genWeights188",        &genWeights188,        "genWeights188/F"       );
  NewTreeSB->Branch("genWeights189",        &genWeights189,        "genWeights189/F"       );
  NewTreeSB->Branch("genWeights190",        &genWeights190,        "genWeights190/F"       );
  NewTreeSB->Branch("genWeights191",        &genWeights191,        "genWeights191/F"       );
  NewTreeSB->Branch("genWeights192",        &genWeights192,        "genWeights192/F"       );
  NewTreeSB->Branch("genWeights193",        &genWeights193,        "genWeights193/F"       );
  NewTreeSB->Branch("genWeights194",        &genWeights194,        "genWeights194/F"       );
  NewTreeSB->Branch("genWeights195",        &genWeights195,        "genWeights195/F"       );
  NewTreeSB->Branch("genWeights196",        &genWeights196,        "genWeights196/F"       );
  NewTreeSB->Branch("genWeights197",        &genWeights197,        "genWeights197/F"       );
  NewTreeSB->Branch("genWeights198",        &genWeights198,        "genWeights198/F"       );
  NewTreeSB->Branch("genWeights199",        &genWeights199,        "genWeights199/F"       );
  NewTreeSB->Branch("genWeights200",        &genWeights200,        "genWeights200/F"       );
  NewTreeSB->Branch("genWeights201",        &genWeights201,        "genWeights201/F"       );
  NewTreeSB->Branch("genWeights202",        &genWeights202,        "genWeights202/F"       );
  NewTreeSB->Branch("genWeights203",        &genWeights203,        "genWeights203/F"       );
  NewTreeSB->Branch("genWeights204",        &genWeights204,        "genWeights204/F"       );
  NewTreeSB->Branch("genWeights205",        &genWeights205,        "genWeights205/F"       );
  NewTreeSB->Branch("genWeights206",        &genWeights206,        "genWeights206/F"       );
  NewTreeSB->Branch("genWeights207",        &genWeights207,        "genWeights207/F"       );
  NewTreeSB->Branch("genWeights208",        &genWeights208,        "genWeights208/F"       );
  NewTreeSB->Branch("genWeights209",        &genWeights209,        "genWeights209/F"       );
  NewTreeSB->Branch("genWeights210",        &genWeights210,        "genWeights210/F"       );
  NewTreeSB->Branch("genWeights211",        &genWeights211,        "genWeights211/F"       );
  NewTreeSB->Branch("genWeights212",        &genWeights212,        "genWeights212/F"       );
  NewTreeSB->Branch("dQuark",&dQuark,"dQuark/I");
  NewTreeSB->Branch("uQuark",&uQuark,"uQuark/I");
  NewTreeSB->Branch("sQuark",&sQuark,"sQuark/I");
  NewTreeSB->Branch("cQuark",&cQuark,"cQuark/I");
  NewTreeSB->Branch("bQuark",&bQuark,"bQuark/I");
  NewTreeSB->Branch("tQuark",&tQuark,"tQuark/I");
  NewTreeSB->Branch("EVENT_event",&EVENT_event,"EVENT_event/I");
  NewTreeSB->Branch("EVENT_run",&EVENT_run,"EVENT_run/I");
  NewTreeSB->Branch("EVENT_lumiBlock",&EVENT_lumiBlock,"EVENT_lumiBlock/I");
  NewTreeSB->Branch("EVENT_genHT",&EVENT_genHT,"EVENT_genHT/F");
  NewTreeSB->Branch("prefiringweight",&prefiringweight,"prefiringweight/F");
  NewTreeSB->Branch("prefiringweightup",&prefiringweightup,"prefiringweightup/F");
  NewTreeSB->Branch("prefiringweightdown",&prefiringweightdown,"prefiringweightdown/F");
  NewTreeSB->Branch("Met_pt",&Met_pt,"Met_pt/F");
  NewTreeSB->Branch("Met_phi",&Met_phi,"Met_phi/F");
  NewTreeSB->Branch("TransverseMassMetTop",&TransverseMassMetTop,"TransverseMassMetTop/F");
}/*}}}*/

void initializeVar(){/*{{{*/
  category0=0;
  category1=0;
  category2=0;
  category3=0;
  category4=0;
  category5=0;
  category6=0;
  category7=0;
  BMass=-99;
  BCSV=-99;
  BPt=-99;
  BEta=-99;
  BPhi=-99;
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
  ZMass=-99;
  ZPt=-99;
  ZEta=-99;
  ZPhi=-99;
  TprimeMass=-99;
  TprimePt=-99;
  TprimeEta=-99;
  TprimePhi=-99;
  TprimeResolvedMass=-99;
  TprimeResolvedPt=-99;
  TprimeResolvedEta=-99;
  TprimeResolvedPhi=-99;
  TprimePartialMass=-99;
  TprimePartialPt=-99;
  TprimePartialEta=-99;
  TprimePartialPhi=-99;
  TprimeMergedMass=-99;
  TprimeMergedPt=-99;
  TprimeMergedEta=-99;
  TprimeMergedPhi=-99;
  Electron1Pt=-99;
  Electron2Pt=-99;
  Electron1E=-99;
  Electron2E=-99;
  Muon1Iso=-99;
  Muon2Iso=-99;
  Muon1Pt=-99;
  Muon2Pt=-99;
 Electron1Eta=-99;
  Electron2Eta=-99;
  Muon1Eta=-99;
  Muon2Eta=-99;
  Electron1Phi=-99;
  Electron2Phi=-99;
  Muon1Phi=-99;
  Muon2Phi=-99;
  deltaPhiZTop=-99;
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
  deltaPhiMetTop=-99.;
  Massb1b2=-99;
  MinDeltaPhiJetMet=99.;
  MinDeltaPhiBoostedJetMet=99.;
  deltaRb1b2=-99;
  deltaRb1Lep1=-99;
  deltaRb1Lep2=-99;
  deltaRb2Lep1=-99;
  deltaRb2Lep2=-99;
  Jet1ForwardEta=-99;
  Jet2ForwardEta=-99;
  Jet3ForwardEta=-99;
  Jet1ForwardPt=-99;
  Jet2ForwardPt=-99;
  Jet3ForwardPt=-99;
  Jet1ResolvedPt=-99;
  Jet2ResolvedPt=-99;
  Jet3ResolvedPt=-99;
  Jet1PartialPt=-99;
  Jet2PartialPt=-99;
  Jet1MergedPt=-99;
  Jet1ResolvedEta=-99;
  Jet2ResolvedEta=-99;
  Jet3ResolvedEta=-99;
  Jet1PartialEta=-99;
  Jet2PartialEta=-99;
  Jet1MergedEta=-99;
  MostForwardJetEta=-99;
  MostForwardJetPt=-99;
  NumSelLeps=-99;
//
//
  NumSeEle=-99;
  NumSeMu=-99;
  InvariantMassJets=-99;
  Centrality=-99;
  Aplanarity=-99;
//
//
  NumSelJets=-99;
  NumSelForwardJets=-99;
  NumSelBJetsL=-99;
  NumSelBJetsM=-99;
  NumSelBJetsT=-99;
  NumSelWJets=-99;
  NumSelTopJets=-99;
  NVertices=-99;
  HT=-99;
  MHT=-99;
  PUWeight=1;
  PUWeightUP=1;
  PUWeightDOWN=1;
  EVENT_event=-99;
  EVENT_run=-99;
  EVENT_lumiBlock=-99;
  EVENT_genHT=-99;
  prefiringweight = 1;
  prefiringweightup = 1;
  prefiringweightdown = 1;
  Met_pt = -99.;
  Met_phi = -99.;
  getTrueNumInteractions=-99;
  w_for = 1;
  w_forUp = 1;
  w_forDown = 1;
  w_topJet = 1;
  w_topJetUp = 1;
  w_topJetDown = 1;
  w_WJet   = 1;
  w_WJetUp   = 1;
  w_WJetDown   = 1;
  w_Muon1  = 1;
  w_Muon2  = 1;
  w_Muon1Up  = 1;
  w_Muon2Up  = 1;
  w_Muon1Down  = 1;
  w_Muon2Down  = 1;
  w_TrigMuon  = 1;
  w_TrigMuonUp  = 1;
  w_TrigMuonDown  = 1;
  w_Electron1  = 1;
  w_Electron2  = 1;
  w_Electron1Up  = 1;
  w_Electron2Up  = 1;
  w_Electron1Down  = 1;
  w_Electron2Down  = 1;
  w_TrigElec  = 1;
  w_TrigElecUp  = 1;
  w_TrigElecDown  = 1;
  w_ZToNuNu=1;
  w_ZToNuNuUp=1;
  w_ZToNuNuDown=1;
  w_WToLNu=1;
  w_WToLNuUp=1;
  w_WToLNuDown=1;
  w_ttbar=1;
  w_ttbarUp=1;
  w_ttbarDown=1;
  w_Trig  = 1;
  w_TrigUp  = 1;
  w_TrigDown  = 1;
  WMass = -99;
  WSubjet = -99;
  TopSoftMass = -99;
  TopSubjet = -99;
  w_Btag=1;
  w_BtagUp=1;
  w_BtagDown=1;
  w_Btag1Up=1;
  w_Btag1Down=1;
  w_Btag2Up=1;
  w_Btag2Down=1;
  w_BtagLoose=1;
  w_BtagLooseUp=1;
  w_BtagLooseDown=1;
  w_QCDUp=1;
  w_QCDDown=1;
  w_PDFUp=1;
  w_PDFDown=1;
  genWeight=1;
  genWeights0=1;
  genWeights1=1;
  genWeights2=1;
  genWeights3=1;
  genWeights4=1;
  genWeights5=1;
  genWeights6=1;
  genWeights7=1;
  genWeights8=1;
  genWeights9=1;
  genWeights10=1;
  genWeights11=1;
  genWeights12=1;
  genWeights13=1;
  genWeights14=1;
  genWeights15=1;
  genWeights16=1;
  genWeights17=1;
  genWeights18=1;
  genWeights19=1;
  genWeights20=1;
  genWeights21=1;
  genWeights22=1;
  genWeights23=1;
  genWeights24=1;
  genWeights25=1;
  genWeights26=1;
  genWeights27=1;
  genWeights28=1;
  genWeights29=1;
  genWeights30=1;
  genWeights31=1;
  genWeights32=1;
  genWeights33=1;
  genWeights34=1;
  genWeights35=1;
  genWeights36=1;
  genWeights37=1;
  genWeights38=1;
  genWeights39=1;
  genWeights40=1;
  genWeights41=1;
  genWeights42=1;
  genWeights43=1;
  genWeights44=1;
  genWeights45=1;
  genWeights46=1;
  genWeights47=1;
  genWeights48=1;
  genWeights49=1;
  genWeights50=1;
  genWeights51=1;
  genWeights52=1;
  genWeights53=1;
  genWeights54=1;
  genWeights55=1;
  genWeights56=1;
  genWeights57=1;
  genWeights58=1;
  genWeights59=1;
  genWeights60=1;
  genWeights61=1;
  genWeights62=1;
  genWeights63=1;
  genWeights64=1;
  genWeights65=1;
  genWeights66=1;
  genWeights67=1;
  genWeights68=1;
  genWeights69=1;
  genWeights70=1;
  genWeights71=1;
  genWeights72=1;
  genWeights73=1;
  genWeights74=1;
  genWeights75=1;
  genWeights76=1;
  genWeights77=1;
  genWeights78=1;
  genWeights79=1;
  genWeights80=1;
  genWeights81=1;
  genWeights82=1;
  genWeights83=1;
  genWeights84=1;
  genWeights85=1;
  genWeights86=1;
  genWeights87=1;
  genWeights88=1;
  genWeights89=1;
  genWeights90=1;
  genWeights91=1;
  genWeights92=1;
  genWeights93=1;
  genWeights94=1;
  genWeights95=1;
  genWeights96=1;
  genWeights97=1;
  genWeights98=1;
  genWeights99=1;
  genWeights100=1;
  genWeights101=1;
  genWeights102=1;
  genWeights103=1;
  genWeights104=1;
  genWeights105=1;
  genWeights106=1;
  genWeights107=1;
  genWeights108=1;
  genWeights109=1;
  genWeights110=1;
  genWeights111=1;
  genWeights112=1;
  genWeights113=1;
  genWeights114=1;
  genWeights115=1;
  genWeights116=1;
  genWeights117=1;
  genWeights118=1;
  genWeights119=1;
  genWeights120=1;
  genWeights121=1;
  genWeights122=1;
  genWeights123=1;
  genWeights124=1;
  genWeights125=1;
  genWeights126=1;
  genWeights127=1;
  genWeights128=1;
  genWeights129=1;
  genWeights130=1;
  genWeights131=1;
  genWeights132=1;
  genWeights133=1;
  genWeights134=1;
  genWeights135=1;
  genWeights136=1;
  genWeights137=1;
  genWeights138=1;
  genWeights139=1;
  genWeights140=1;
  genWeights141=1;
  genWeights142=1;
  genWeights143=1;
  genWeights144=1;
  genWeights145=1;
  genWeights146=1;
  genWeights147=1;
  genWeights148=1;
  genWeights149=1;
  genWeights150=1;
  genWeights151=1;
  genWeights152=1;
  genWeights153=1;
  genWeights154=1;
  genWeights155=1;
  genWeights156=1;
  genWeights157=1;
  genWeights158=1;
  genWeights159=1;
  genWeights160=1;
  genWeights161=1;
  genWeights162=1;
  genWeights163=1;
  genWeights164=1;
  genWeights165=1;
  genWeights166=1;
  genWeights167=1;
  genWeights168=1;
  genWeights169=1;
  genWeights170=1;
  genWeights171=1;
  genWeights172=1;
  genWeights173=1;
  genWeights174=1;
  genWeights175=1;
  genWeights176=1;
  genWeights177=1;
  genWeights178=1;
  genWeights179=1;
  genWeights180=1;
  genWeights181=1;
  genWeights182=1;
  genWeights183=1;
  genWeights184=1;
  genWeights185=1;
  genWeights186=1;
  genWeights187=1;
  genWeights188=1;
  genWeights189=1;
  genWeights190=1;
  genWeights191=1;
  genWeights192=1;
  genWeights193=1;
  genWeights194=1;
  genWeights195=1;
  genWeights196=1;
  genWeights197=1;
  genWeights198=1;
  genWeights199=1;
  genWeights200=1;
  genWeights201=1;
  genWeights202=1;
  genWeights203=1;
  genWeights204=1;
  genWeights205=1;
  genWeights206=1;
  genWeights207=1;
  genWeights208=1;
  genWeights209=1;
  genWeights210=1;
  genWeights211=1;
  genWeights212=1;
  GenZPt=-99.;
  GenWPt=-99.;
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
}/*}}}*/
//?filename not occur
//
void branchGetEntry(bool data, Long64_t tentry, string fileName){/*{{{*/
 //GetEntry?
 //?is that OK fileName not in the function?
 //?why the b_?
  b_Jet_pt->GetEntry(tentry);//is a branch in tree, setadress.
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
  b_Jet_neutralHadEnergyFraction->GetEntry(tentry);
  b_Jet_chargedEmEnergyFraction->GetEntry(tentry);
  b_Jet_neutralEmEnergyFraction->GetEntry(tentry);
  b_Jet_numberOfConstituents->GetEntry(tentry);
  b_Jet_chargedHadronEnergyFraction->GetEntry(tentry);
  b_Jet_chargedMultiplicity->GetEntry(tentry);
  if(!data) b_Jet_hadronFlavour->GetEntry(tentry);
  b_BoostedJet_pt->GetEntry(tentry);
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
  b_BoostedJet_chargedMultiplicity->GetEntry(tentry);
  //b_TopTagging_topMass->GetEntry(tentry);
  //b_TopTagging_minMass->GetEntry(tentry);
  //b_TopTagging_nSubJets->GetEntry(tentry);
  b_patElectron_pt->GetEntry(tentry);
  b_patElectron_eta->GetEntry(tentry);
  b_patElectron_phi->GetEntry(tentry);
  b_patElectron_energy->GetEntry(tentry);
  //b_patElectron_energyCorr->GetEntry(tentry);
  b_patElectron_SCeta->GetEntry(tentry);
  b_patElectron_charge->GetEntry(tentry);
  b_patElectron_isPassVeto->GetEntry(tentry);          
  b_patElectron_isPassLoose->GetEntry(tentry);
  b_patElectron_isPassMedium->GetEntry(tentry);
  b_patElectron_isPassTight->GetEntry(tentry);
  b_patElectron_isPassHEEPId->GetEntry(tentry);
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
  b_Muon_isMatchedToTrigger->GetEntry(tentry);
  b_Met_type1PF_pt->GetEntry(tentry);
  b_Met_type1PF_phi->GetEntry(tentry);
  b_Met_type1PF_sumEt->GetEntry(tentry);
  b_HLT_DoubleEle33_CaloIdL_MW->GetEntry(tentry);
   b_HLT_Mu50->GetEntry(tentry);
   b_HLT_TkMu50->GetEntry(tentry);
   // b_HLT_PFHT500_PFMET100_PFMHT100_IDTight->GetEntry(tentry);
   // b_HLT_PFHT700_PFMET85_PFMHT85_IDTight->GetEntry(tentry);
   // b_HLT_PFHT800_PFMET75_PFMHT75_IDTight->GetEntry(tentry);
 b_HLT_PFMET120_PFMHT120_IDTight->GetEntry(tentry);
  b_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight->GetEntry(tentry);
  // b_HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight->GetEntry(tentry);
  // b_HLT_CaloJet500_NoJetID->GetEntry(tentry);
  // b_HLT_AK8PFJet500->GetEntry(tentry);
  // b_HLT_PFJet500->GetEntry(tentry);
  // b_HLT_PFHT1050->GetEntry(tentry);
  //
  //
  b_HLT_PFHT900->GetEntry(tentry);
  b_HLT_PFHT450_SixJet40_BTagCSV_p056->GetEntry(tentry);
  b_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 ->GetEntry(tentry);
 //
 //
  b_Flag_goodVertices->GetEntry(tentry);
  //b_Flag_CSCTightHalo2015Filter->GetEntry(tentry);
  b_Flag_HBHENoiseFilter->GetEntry(tentry);
  b_Flag_HBHENoiseIsoFilter->GetEntry(tentry);
  b_Flag_EcalDeadCellTriggerPrimitiveFilter->GetEntry(tentry);
  b_Flag_BadPFMuonFilter->GetEntry(tentry);
  b_Flag_BadChargedCandidateFilter->GetEntry(tentry);
  b_Flag_ecalBadCalibReducedMINIAODFilter->GetEntry(tentry);
  b_Flag_eeBadScFilter->GetEntry(tentry);
  b_Flag_globalSuperTightHalo2016Filter->GetEntry(tentry);
  b_nBestVtx->GetEntry(tentry);
  b_PUWeight->GetEntry(tentry);
  //b_PUWeightUP->GetEntry(tentry);
  //b_PUWeightDOWN->GetEntry(tentry);
  b_EVENT_run->GetEntry(tentry);
  b_EVENT_event->GetEntry(tentry);
  b_EVENT_lumiBlock->GetEntry(tentry);
  b_EVENT_genHT->GetEntry(tentry);
  b_EVENT_prefiringweight->GetEntry(tentry);
  b_EVENT_prefiringweightup->GetEntry(tentry);
  b_EVENT_prefiringweightdown->GetEntry(tentry);
  b_genWeight->GetEntry(tentry);
  if(!data) b_Gen_pt->GetEntry(tentry);
  if(!data) b_Gen_eta->GetEntry(tentry);
  if(!data) b_Gen_phi->GetEntry(tentry);
  if(!data) b_Gen_pdg_id->GetEntry(tentry);
  if(!data) b_Gen_motherpdg_id->GetEntry(tentry);
  b_genWeights->GetEntry(tentry);
}/*}}}*/

void HistoFill(float puweight,TTree *NewTree){
	//?has nothing to do with puweigh,why use puweight then?
  NewTree->Fill();
}

void writeFile(TTree *NewTree,TTree *NewTreeSB){
  NewTree->Write();
  NewTreeSB->Write();
}

void fillgenWeights(){/*{{{*/
  genWeights0       = (*genWeights_)[0];
  genWeights1       = (*genWeights_)[1];
  genWeights2       = (*genWeights_)[2];
  genWeights3       = (*genWeights_)[3];
  genWeights4       = (*genWeights_)[4];
  genWeights5       = (*genWeights_)[5];
  genWeights6       = (*genWeights_)[6];
  genWeights7       = (*genWeights_)[7];
  genWeights8       = (*genWeights_)[8];
  genWeights9       = (*genWeights_)[9];
  genWeights10      = (*genWeights_)[10];
  genWeights11      = (*genWeights_)[11];
  genWeights12      = (*genWeights_)[12];
  genWeights13      = (*genWeights_)[13];
  genWeights14      = (*genWeights_)[14];
  genWeights15      = (*genWeights_)[15];
  genWeights16      = (*genWeights_)[16];
  genWeights17      = (*genWeights_)[17];
  genWeights18      = (*genWeights_)[18];
  genWeights19      = (*genWeights_)[19];
  genWeights20      = (*genWeights_)[20];
  genWeights21      = (*genWeights_)[21];
  genWeights22      = (*genWeights_)[22];
  genWeights23      = (*genWeights_)[23];
  genWeights24      = (*genWeights_)[24];
  genWeights25      = (*genWeights_)[25];
  genWeights26      = (*genWeights_)[26];
  genWeights27      = (*genWeights_)[27];
  genWeights28      = (*genWeights_)[28];
  genWeights29      = (*genWeights_)[29];
  genWeights30      = (*genWeights_)[30];
  genWeights31      = (*genWeights_)[31];
  genWeights32      = (*genWeights_)[32];
  genWeights33      = (*genWeights_)[33];
  genWeights34      = (*genWeights_)[34];
  genWeights35      = (*genWeights_)[35];
  genWeights36      = (*genWeights_)[36];
  genWeights37      = (*genWeights_)[37];
  genWeights38      = (*genWeights_)[38];
  genWeights39      = (*genWeights_)[39];
  genWeights40      = (*genWeights_)[40];
  genWeights41      = (*genWeights_)[41];
  genWeights42      = (*genWeights_)[42];
  genWeights43      = (*genWeights_)[43];
  genWeights44      = (*genWeights_)[44];
  genWeights45      = (*genWeights_)[45];
  genWeights46      = (*genWeights_)[46];
  genWeights47      = (*genWeights_)[47];
  genWeights48      = (*genWeights_)[48];
  genWeights49      = (*genWeights_)[49];
  genWeights50      = (*genWeights_)[50];
  genWeights51      = (*genWeights_)[51];
  genWeights52      = (*genWeights_)[52];
  genWeights53      = (*genWeights_)[53];
  genWeights54      = (*genWeights_)[54];
  genWeights55      = (*genWeights_)[55];
  genWeights56      = (*genWeights_)[56];
  genWeights57      = (*genWeights_)[57];
  genWeights58      = (*genWeights_)[58];
  genWeights59      = (*genWeights_)[59];
  genWeights60      = (*genWeights_)[60];
  genWeights61      = (*genWeights_)[61];
  genWeights62      = (*genWeights_)[62];
  genWeights63      = (*genWeights_)[63];
  genWeights64      = (*genWeights_)[64];
  genWeights65      = (*genWeights_)[65];
  genWeights66      = (*genWeights_)[66];
  genWeights67      = (*genWeights_)[67];
  genWeights68      = (*genWeights_)[68];
  genWeights69      = (*genWeights_)[69];
  genWeights70      = (*genWeights_)[70];
  genWeights71      = (*genWeights_)[71];
  genWeights72      = (*genWeights_)[72];
  genWeights73      = (*genWeights_)[73];
  genWeights74      = (*genWeights_)[74];
  genWeights75      = (*genWeights_)[75];
  genWeights76      = (*genWeights_)[76];
  genWeights77      = (*genWeights_)[77];
  genWeights78      = (*genWeights_)[78];
  genWeights79      = (*genWeights_)[79];
  genWeights80      = (*genWeights_)[80];
  genWeights81      = (*genWeights_)[81];
  genWeights82      = (*genWeights_)[82];
  genWeights83      = (*genWeights_)[83];
  genWeights84      = (*genWeights_)[84];
  genWeights85      = (*genWeights_)[85];
  genWeights86      = (*genWeights_)[86];
  genWeights87      = (*genWeights_)[87];
  genWeights88      = (*genWeights_)[88];
  genWeights89      = (*genWeights_)[89];
  genWeights90      = (*genWeights_)[90];
  genWeights91      = (*genWeights_)[91];
  genWeights92      = (*genWeights_)[92];
  genWeights93      = (*genWeights_)[93];
  genWeights94      = (*genWeights_)[94];
  genWeights95      = (*genWeights_)[95];
  genWeights96      = (*genWeights_)[96];
  genWeights97      = (*genWeights_)[97];
  genWeights98      = (*genWeights_)[98];
  genWeights99      = (*genWeights_)[99];
  genWeights100     = (*genWeights_)[100];
  genWeights101     = (*genWeights_)[101];
  genWeights102     = (*genWeights_)[102];
  genWeights103     = (*genWeights_)[103];
  genWeights104     = (*genWeights_)[104];
  genWeights105     = (*genWeights_)[105];
  genWeights106     = (*genWeights_)[106];
  genWeights107     = (*genWeights_)[107];
  genWeights108     = (*genWeights_)[108];
  genWeights109     = (*genWeights_)[109];
  genWeights110     = (*genWeights_)[110];
  genWeights111     = (*genWeights_)[111];
  genWeights112     = (*genWeights_)[112];
  genWeights113     = (*genWeights_)[113];
  genWeights114     = (*genWeights_)[114];
  genWeights115     = (*genWeights_)[115];
  genWeights116     = (*genWeights_)[116];
  genWeights117     = (*genWeights_)[117];
  genWeights118     = (*genWeights_)[118];
  genWeights119     = (*genWeights_)[119];
  genWeights120     = (*genWeights_)[120];
  genWeights121     = (*genWeights_)[121];
  genWeights122     = (*genWeights_)[122];
  genWeights123     = (*genWeights_)[123];
  genWeights124     = (*genWeights_)[124];
  genWeights125     = (*genWeights_)[125];
  genWeights126     = (*genWeights_)[126];
  genWeights127     = (*genWeights_)[127];
  genWeights128     = (*genWeights_)[128];
  genWeights129     = (*genWeights_)[129];
  genWeights130     = (*genWeights_)[130];
  genWeights131     = (*genWeights_)[131];
  genWeights132     = (*genWeights_)[132];
  genWeights133     = (*genWeights_)[133];
  genWeights134     = (*genWeights_)[134];
  genWeights135     = (*genWeights_)[135];
  genWeights136     = (*genWeights_)[136];
  genWeights137     = (*genWeights_)[137];
  genWeights138     = (*genWeights_)[138];
  genWeights139     = (*genWeights_)[139];
  genWeights140     = (*genWeights_)[140];
  genWeights141     = (*genWeights_)[141];
  genWeights142     = (*genWeights_)[142];
  genWeights143     = (*genWeights_)[143];
  genWeights144     = (*genWeights_)[144];
  genWeights145     = (*genWeights_)[145];
  genWeights146     = (*genWeights_)[146];
  genWeights147     = (*genWeights_)[147];
  genWeights148     = (*genWeights_)[148];
  genWeights149     = (*genWeights_)[149];
  genWeights150     = (*genWeights_)[150];
  genWeights151     = (*genWeights_)[151];
  genWeights152     = (*genWeights_)[152];
  genWeights153     = (*genWeights_)[153];
  genWeights154     = (*genWeights_)[154];
  genWeights155     = (*genWeights_)[155];
  genWeights156     = (*genWeights_)[156];
  genWeights157     = (*genWeights_)[157];
  genWeights158     = (*genWeights_)[158];
  genWeights159     = (*genWeights_)[159];
  genWeights160     = (*genWeights_)[160];
  genWeights161     = (*genWeights_)[161];
  genWeights162     = (*genWeights_)[162];
  genWeights163     = (*genWeights_)[163];
  genWeights164     = (*genWeights_)[164];
  genWeights165     = (*genWeights_)[165];
  genWeights166     = (*genWeights_)[166];
  genWeights167     = (*genWeights_)[167];
  genWeights168     = (*genWeights_)[168];
  genWeights169     = (*genWeights_)[169];
  genWeights170     = (*genWeights_)[170];
  genWeights171     = (*genWeights_)[171];
  genWeights172     = (*genWeights_)[172];
  genWeights173     = (*genWeights_)[173];
  genWeights174     = (*genWeights_)[174];
  genWeights175     = (*genWeights_)[175];
  genWeights176     = (*genWeights_)[176];
  genWeights177     = (*genWeights_)[177];
  genWeights178     = (*genWeights_)[178];
  genWeights179     = (*genWeights_)[179];
  genWeights180     = (*genWeights_)[180];
  genWeights181     = (*genWeights_)[181];
  genWeights182     = (*genWeights_)[182];
  genWeights183     = (*genWeights_)[183];
  genWeights184     = (*genWeights_)[184];
  genWeights185     = (*genWeights_)[185];
  genWeights186     = (*genWeights_)[186];
  genWeights187     = (*genWeights_)[187];
  genWeights188     = (*genWeights_)[188];
  genWeights189     = (*genWeights_)[189];
  genWeights190     = (*genWeights_)[190];
  genWeights191     = (*genWeights_)[191];
  genWeights192     = (*genWeights_)[192];
  genWeights193     = (*genWeights_)[193];
  genWeights194     = (*genWeights_)[194];
  genWeights195     = (*genWeights_)[195];
  genWeights196     = (*genWeights_)[196];
  genWeights197     = (*genWeights_)[197];
  genWeights198     = (*genWeights_)[198];
  genWeights199     = (*genWeights_)[199];
  genWeights200     = (*genWeights_)[200];
  genWeights201     = (*genWeights_)[201];
  genWeights202     = (*genWeights_)[202];
  genWeights203     = (*genWeights_)[203];
  genWeights204     = (*genWeights_)[204];
  genWeights205     = (*genWeights_)[205];
  genWeights206     = (*genWeights_)[206];
  genWeights207     = (*genWeights_)[207];
  genWeights208     = (*genWeights_)[208];
  genWeights209     = (*genWeights_)[209];
  genWeights210     = (*genWeights_)[210];
  genWeights211     = (*genWeights_)[211];
  genWeights212     = (*genWeights_)[212];
}/*}}}*/

void GenClassifier(float &GenZPt_,float &GenWPt_){/*{{{*/
    for (UInt_t j = 0; j < Gen_pt_->size(); ++j) {
    //cout<<j<<" "<<Gen_pdg_id_->at(j)<<" "<<Gen_motherpdg_id_->at(j)<<" "<<Gen_pt_->at(j)<<endl;
	//std::string::at can be used to extract characters by characters from a given string.
	//?what is Gen_pt? is Gen_pt of the final state? if so, how can we have Z and W ?
    if(abs(Gen_pdg_id_->at(j))==1 && (abs(Gen_motherpdg_id_->at(j))==2212 || abs(Gen_motherpdg_id_->at(j))==21)) dQuark = dQuark + 1;//dQuark a branch in newtree and newtreeSB
    if(abs(Gen_pdg_id_->at(j))==2 && (abs(Gen_motherpdg_id_->at(j))==2212 || abs(Gen_motherpdg_id_->at(j))==21)) uQuark = uQuark + 1;
    if(abs(Gen_pdg_id_->at(j))==3 && (abs(Gen_motherpdg_id_->at(j))==2212 || abs(Gen_motherpdg_id_->at(j))==21)) sQuark = sQuark + 1;
    if(abs(Gen_pdg_id_->at(j))==4 && (abs(Gen_motherpdg_id_->at(j))==2212 || abs(Gen_motherpdg_id_->at(j))==21)) cQuark = cQuark + 1;
    if(abs(Gen_pdg_id_->at(j))==5 && (abs(Gen_motherpdg_id_->at(j))==2212 || abs(Gen_motherpdg_id_->at(j))==21)) bQuark = bQuark + 1;
    if(abs(Gen_pdg_id_->at(j))==6 && (abs(Gen_motherpdg_id_->at(j))==2212 || abs(Gen_motherpdg_id_->at(j))==21)) tQuark = tQuark + 1;
	if(abs(Gen_pdg_id_->at(j))==23) GenZPt_ = Gen_pt_->at(j);// in function GenWeight
	if(abs(Gen_pdg_id_->at(j))==24) GenWPt_ = Gen_pt_->at(j);
  }
}/*}}}*/


void GenWBoson(bool &matched, TLorentzVector Wjet){/*{{{*/
  double dr1=99;  double dr2=99;  double dr3=99;  double dr4=99;  double dr5=99;  double dr6=99; 
  double dr7=99;  double dr8=99;  double dr9=99;  double dr10=99; double dr11=99; double dr12=99; 
  double dr13=99; double dr14=99; double dr15=99; double dr16=99; double dr17=99; double dr18=99; 
  for (UInt_t j = 0; j < Gen_pt_->size(); ++j) {
    //cout<<j<<" "<<Gen_pdg_id_->at(j)<<" "<<Gen_motherpdg_id_->at(j)<<" "<<Gen_pt_->at(j)<<endl;
    if(abs(Gen_pdg_id_->at(j))==1 && abs(Gen_motherpdg_id_->at(j))==24) dr1 = DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(abs(Gen_pdg_id_->at(j))==2 && abs(Gen_motherpdg_id_->at(j))==24) dr2 = DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(abs(Gen_pdg_id_->at(j))==3 && abs(Gen_motherpdg_id_->at(j))==24) dr3 = DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(abs(Gen_pdg_id_->at(j))==4 && abs(Gen_motherpdg_id_->at(j))==24) dr4 = DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(abs(Gen_pdg_id_->at(j))==5 && abs(Gen_motherpdg_id_->at(j))==24) dr5 = DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(abs(Gen_pdg_id_->at(j))==6 && abs(Gen_motherpdg_id_->at(j))==24) dr6 = DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(   (Gen_pdg_id_->at(j))==1 && abs(Gen_motherpdg_id_->at(j))==23) dr7 = DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(   (Gen_pdg_id_->at(j))==2 && abs(Gen_motherpdg_id_->at(j))==23) dr8 = DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(   (Gen_pdg_id_->at(j))==3 && abs(Gen_motherpdg_id_->at(j))==23) dr9 = DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(   (Gen_pdg_id_->at(j))==4 && abs(Gen_motherpdg_id_->at(j))==23) dr10= DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(   (Gen_pdg_id_->at(j))==5 && abs(Gen_motherpdg_id_->at(j))==23) dr11= DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(   (Gen_pdg_id_->at(j))==6 && abs(Gen_motherpdg_id_->at(j))==23) dr12= DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(   (Gen_pdg_id_->at(j))==-1&& abs(Gen_motherpdg_id_->at(j))==23) dr13= DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(   (Gen_pdg_id_->at(j))==-2&& abs(Gen_motherpdg_id_->at(j))==23) dr14= DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(   (Gen_pdg_id_->at(j))==-3&& abs(Gen_motherpdg_id_->at(j))==23) dr15= DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(   (Gen_pdg_id_->at(j))==-4&& abs(Gen_motherpdg_id_->at(j))==23) dr16= DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(   (Gen_pdg_id_->at(j))==-5&& abs(Gen_motherpdg_id_->at(j))==23) dr17= DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
    if(   (Gen_pdg_id_->at(j))==-6&& abs(Gen_motherpdg_id_->at(j))==23) dr18= DeltaR(Wjet.Eta(),Gen_eta_->at(j),Wjet.Phi(),Gen_phi_->at(j));
  }
  if((dr2 <0.8 && dr1 <0.8) || (dr2 <0.8 && dr3 <0.8) || (dr2 <0.8 && dr5 <0.8)) matched=true; //W -> ud/us/ub
  if((dr4 <0.8 && dr1 <0.8) || (dr4 <0.8 && dr3 <0.8) || (dr4 <0.8 && dr5 <0.8)) matched=true; //W -> cd/cs/cb
  //if((dr7 <0.8 && dr13<0.8) || (dr8 <0.8 && dr14<0.8) || (dr9 <0.8 && dr15<0.8)) matched=true; //Z -> dd/uu/ss
  //if((dr10<0.8 && dr16<0.8) || (dr11<0.8 && dr17<0.8) || (dr12<0.8 && dr18<0.8)) matched=true; //Z -> cc/bb/tt
}/*}}}*/

//?what is GenWeight doing?
void GenWeight(string fileName, float GenZPt_,float GenWPt_){/*{{{*/
  genWeight=(genWeight_)/abs(genWeight_);// genWeight_ in Tree, genWeight in NewTree
  //?what is genWeight? what does it do?
  if(fileName.find("DY")!=string::npos || fileName.find("ZToNuNu")!=string::npos) {
    if(GenZPt_>0) genWeight = functZPt->Eval(GenZPt_);//functZPt TF1 in .h 102
	//Eval, evaluation of Chebyshev polynomials
    else genWeight = 1;
    }
  if(fileName.find("WToLNu")!=string::npos) {
    if(GenWPt_>0) genWeight = functWPt->Eval(GenWPt_);
    else genWeight = 1;
    }

}/*}}}*/

void newPUWeight(float &puweight,float &puweightUP,float &puweightDOWN){/*{{{*/
  double *npuProbs = 0;
  double *npuProbsNEW = 0;
  unsigned int nPUMax = 99;
	//?whatis these?
  double npu_Moriond18Scenario[99] =  {3.39597497605e-05,6.63688402133e-06,1.39533611284e-05,3.64963078209e-05,6.00872171664e-05,9.33932578027e-05,0.000120591524486,0.000128694546198,0.000361697233219,0.000361796847553,0.000702474896113,0.00133766053707,0.00237817050805,0.00389825605651,0.00594546732588,0.00856825906255,0.0116627396044,0.0148793350787,0.0179897368379,0.0208723871946,0.0232564170641,0.0249826433945,0.0262245860346,0.0272704617569,0.0283301107549,0.0294006137386,0.0303026836965,0.0309692426278,0.0308818046328,0.0310566806228,0.0309692426278,0.0310566806228,0.0310566806228,0.0310566806228,0.0307696426944,0.0300103336052,0.0288355370103,0.0273233309106,0.0264343533951,0.0255453758796,0.0235877272306,0.0215627588047,0.0195825559393,0.0177296309658,0.0160560731931,0.0146022004183,0.0134080690078,0.0129586991411,0.0125093292745,0.0124360740539,0.0123547104433,0.0123953922486,0.0124360740539,0.0124360740539,0.0123547104433,0.0124360740539,0.0123387597772,0.0122414455005,0.011705203844,0.0108187105305,0.00963985508986,0.00827210065136,0.00683770076341,0.00545237697118,0.00420456901556,0.00367513566191,0.00314570230825,0.0022917978982,0.00163221454973,0.00114065309494,0.000784838366118,0.000533204105387,0.000358474034915,0.000238881117601,0.0001984254989,0.000157969880198,0.00010375646169,6.77366175538e-05,4.39850477645e-05,2.84298066026e-05,1.83041729561e-05,1.17473542058e-05,7.51982735129e-06,6.16160108867e-06,4.80337482605e-06,3.06235473369e-06,1.94863396999e-06,1.23726800704e-06,7.83538083774e-07,4.94602064224e-07,3.10989480331e-07,1.94628487765e-07,1.57888581037e-07,1.2114867431e-07,7.49518929908e-08,4.6060444984e-08,2.81008884326e-08,1.70121486128e-08,1.02159894812e-08};
  double npu_Moriond18ScenarioNEW[99] =  {0.0164731,0.000829522,0.000939881,0.000589732,0.000665918,0.00111637,0.00125813,0.000933965,0.00145441,0.00184519,0.00159332,0.00242139,0.00314767,0.00548591,0.00684822,0.010836,0.0130551,0.0144512,0.0182305,0.0212894,0.0216204,0.0229435,0.0243586,0.0243769,0.0249553,0.0269723,0.0255303,0.0269896,0.0277803,0.0279493,0.0271844,0.0273721,0.0293261,0.0282731,0.0287164,0.0283037,0.0265103,0.0255473,0.0240064,0.0233137,0.0232938,0.0224567,0.0196284,0.0156212,0.0137627,0.0136596,0.0128352,0.0120469,0.0128242,0.0121217,0.0136477,0.0136083,0.0134189,0.0129351,0.0141632,0.0136156,0.0141845,0.0124658,0.0128498,0.0125589,0.0102669,0.0092894,0.00807026,0.00702602,0.0047661,0.00401915,0.00351898,0.00288564,0.00166122,0.0015046,0.000773104,0.000499557,0.000796673,0.0006105,0.000630528,0.000145819,0.000191135,0.000340493,0.000193567,0.000678164,0.000393724,0.000442431,0.000641926,0.000615461,0.000139089,0.000793345,0.000240982,0.00049623,0.00010741,0.000147015,0.0002128,1.14866e-05,1.75821e-05,9.66776e-05,3.37481e-05,0.000457706,2.37272e-07,4.74544e-07,9.06185e-05};
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
    const double npu_estimated = histoOldPU ->GetBinContent(histoOldPU ->GetXaxis()->FindBin(npu));//histoOldPU in header 98
    result[npu] = npu_estimated / npuProbs[npu];
    s += npu_estimated;
    const double npu_estimatedNEW   = histoNewPU  ->GetBinContent(histoNewPU  ->GetXaxis()->FindBin(npu));
    const double npu_estimatedNEWUp = histoNewPUUp->GetBinContent(histoNewPUUp->GetXaxis()->FindBin(npu));
    const double npu_estimatedNEWDo = histoNewPUDo->GetBinContent(histoNewPUDo->GetXaxis()->FindBin(npu));
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
}/*}}}*/

void FillBranches(bool ResolvedEvent,TLorentzVector TopQuark,bool SelectedMet,TLorentzVector TopQuarkResolved,TLorentzVector Jet1Resolved,TLorentzVector Jet2Resolved,TLorentzVector Jet3Resolved,vector<TLorentzVector> SelectedForwardJets,vector<TLorentzVector> SelectedBJets){/*{{{*/
  int NumSelBJets = SelectedBJets.size();
  if(ResolvedEvent){
    TopMass=TopQuark.M();
    TopPt  =TopQuark.Pt();
    TopEta =TopQuark.Eta();
    TopPhi =TopQuark.Phi();
  }
	//?why the same condition in two parts?
  if(ResolvedEvent){
    TopMassResolved=TopQuarkResolved.M();//branch in NewTree and SB
    TopPtResolved=TopQuarkResolved.Pt();
    TopEtaResolved=TopQuarkResolved.Eta();
    TopPhiResolved=TopQuarkResolved.Phi();
    Jet1ResolvedPt = Jet1Resolved.Pt();
    Jet2ResolvedPt = Jet2Resolved.Pt(); 
    Jet3ResolvedPt = Jet3Resolved.Pt();
    Jet1ResolvedEta = Jet1Resolved.Eta();
    Jet2ResolvedEta = Jet2Resolved.Eta(); 
    Jet3ResolvedEta = Jet3Resolved.Eta();
    WMassResolved1 = (Jet1Resolved+Jet2Resolved).M();
    WMassResolved2 = (Jet1Resolved+Jet3Resolved).M();
    WMassResolved3 = (Jet2Resolved+Jet3Resolved).M();
  }
  if(SelectedForwardJets.size()>0) Jet1ForwardPt=SelectedForwardJets[0].Pt();
  if(SelectedForwardJets.size()>1) Jet2ForwardPt=SelectedForwardJets[1].Pt();
  if(SelectedForwardJets.size()>2) Jet3ForwardPt=SelectedForwardJets[2].Pt();
  if(SelectedForwardJets.size()>0) Jet1ForwardEta=SelectedForwardJets[0].Eta();
  if(SelectedForwardJets.size()>1) Jet2ForwardEta=SelectedForwardJets[1].Eta();
  if(SelectedForwardJets.size()>2) Jet3ForwardEta=SelectedForwardJets[2].Eta();
}/*}}}*/
