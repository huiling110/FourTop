#define writeHist_cxx
// The class definition in writeHist.h has been generated automatically
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
// root> T->Process("writeHist.C")
// root> T->Process("writeHist.C","some options")
// root> T->Process("writeHist.C+")
//


#include "writeHist.h"
#include <TH2.h>
#include <TStyle.h>

#include <assert.h>
#include <cmath>

// void getvOptionFromRunMacro( const TString option, std::vector<TString>& m_options ){
//    TString option1 = option(0, option.First(":"));
//     TString temp = option;
//     TString option2 = temp.Remove(0, option.First(":")+1);
//     option2 = option2(0, option2.First(":"));
   //  TString option3 = temp.Remove(0, temp.First(":")+1);
   //  option3 = option3(0, option3.First(":"));
   //  TString option4 = temp.Remove(0, temp.First(":")+1 );
   //  option4 = option4(0, option4.First(":"));
   //  TString option5 = temp.Remove(0, temp.First(":")+1 );
// }
void writeHist::fillHistsVector( Bool_t isRegion, UInt_t vectorIndex, Double_t weight ){
	if( isRegion ){
		//1tau0lCR
		// std::printf( "%i : %f : %f \n", *jets_number, *jets_HT, weight );
		jetsNumber_forYieldCount_hists[vectorIndex]->Fill( *jets_number, weight );
		jetsNumber_hists[vectorIndex]->Fill( *jets_number, weight );
		jets_HT_hists[vectorIndex]->Fill( *jets_HT, weight );
		jets_bScore_hists[vectorIndex]->Fill( *jets_bScore, weight );
		tausT_HT_hists[vectorIndex]->Fill( *tausT_HT, weight );
	}

}




void push_backHists( TString variable, Int_t binNum, Double_t minBin, Double_t maxBin, std::vector<TH1D*>& histsVariable, TString m_processName ){
    std::array<TString, 11> regions = { "1tau0lSR", "1tau0lCR", "1tau0lVR", "1tau0lCR2", "1tau0lCR3", "1tau0lCR4", "1tau1lSR", "1tau1lCR0", "1tau1lCR1", "1tau1lCR2", "1tau1lCR3"};
	// UInt_t startInx = 0;
	// if ( isData ) startInx = 1;
	for ( UInt_t i=0; i<regions.size(); i++){
		// 1250015d::co12<<regions[i]<<"\n";
		TString iHistName =  regions[i]+"_"+ m_processName +"_" + variable;
		TH1D* temp = new TH1D( iHistName.Data(), iHistName.Data(), binNum, minBin, maxBin );
		histsVariable.push_back( temp );
	}

}



void writeHist::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void writeHist::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
    std::cout<<"option in writeHist: "<<option<<"\n";

	//this part could be in a function for multiple uses
	//???better structure my project so that these commen functionality go to one include dir
    TString option1 = option(0, option.First(":"));
    TString temp = option;
    TString option2 = temp.Remove(0, temp.First(":")+1);
    option2 = option2(0, option2.First(":"));
    TString option3 = temp.Remove(0, temp.First(":")+1);
    option3 = option3(0, option3.First(":"));
    TString option4 = temp.Remove(0, temp.First(":")+1);
    option4 = option4(0, option4.First(":"));
	

	m_outputFolder = option2;
	m_processName = option3;
	m_isData = std::stoi(option4.Data());
	std::cout<<"m_isData: "<<m_isData<<"\n";


    m_genWeightSum = std::stod(option1.Data());
    std::cout<<"m_genWeightSum: "<<m_genWeightSum<<"\n";
    //???maybe there is lose of accuracy due to convertion

    // outputFile = new TFile( m_outputFolder+"variableHists/"+m_processName+ "_variableHists.root", "RECREATE" );
    outputFile = new TFile( m_outputFolder+"variableHists"+ "_"+m_version+"/" +m_processName+ "_variableHists.root", "RECREATE" );

    // hist_jetsNumber = new TH1D( "jetsNumber_forYieldCount", "number of jets", 40, 0, 40 );
	push_backHists( "jetsNumber_forYieldCount", 40, 0, 40, jetsNumber_forYieldCount_hists, m_processName );
	push_backHists( "jets_number", 10, 6, 15, jetsNumber_hists, m_processName );
	push_backHists( "jets_HT", 100, 500, 1500, jets_HT_hists, m_processName );
	push_backHists( "jets_bScore", 100, 0, 5, jets_bScore_hists, m_processName );
	push_backHists( "tausT_HT", 100, 30, 300, tausT_HT_hists, m_processName );


	// std::vector<std::vector<TH1D*>> vectorOfVector = { jetsNumber_hists, jets_HT_hists, jets_bScore_hists, tausT_HT_hists };


	// std::map<TString, std::vector<TH1D*>> = {
	// 	("1tau0l_SR", hists_1tau0lSR),

	// }

}

Bool_t writeHist::Process(Long64_t entry)
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

	if ( *tausT_number<1 ) return kFALSE;

    Double_t basicWeight = (*PUweight)*(*EVENT_prefireWeight)*(*EVENT_genWeight);
	if ( m_isData ){
		// assert( (basicWeight-1.0)<std::epsilon ); 
		basicWeight = 1.0;
	}
	// std::cout<<"basicWeight: "<<basicWeight<<"\n";
	//Expression to be evaluated. If this expression evaluates to 0, this causes an assertion failure that terminates the program.
	//1tau0l SR
	if ( !m_isData ){
		// be blind for data in signal region
		Bool_t is1tau0lSR = *tausT_number==1 && *leptonsMVAT_number==0 &&  *jets_number>=8 && *bjetsM_num>=2 ;
		fillHistsVector( is1tau0lSR, 0, basicWeight );
		Bool_t is1tau1lSR = *tausT_number==1 && *leptonsMVAT_number==1 &&  *jets_number>=7 && *bjetsM_num>=2;
		fillHistsVector( is1tau1lSR, 6, basicWeight );
	}

    // 1tau0l CR
	Bool_t is1tau0lCR = *tausT_number==1 && *leptonsMVAT_number==0 &&  *jets_number>=8 && *bjetsM_num==1;
	fillHistsVector( is1tau0lCR, 1, basicWeight );
	Bool_t is1tau0lVR = *tausT_number==1 && *leptonsMVAT_number==0 &&  *jets_number>=8 && *bjetsM_num==0;
	fillHistsVector( is1tau0lVR, 2, basicWeight );
	Bool_t is1tau0lCR2 =  *tausT_number==1 && *leptonsMVAT_number==0 &&  *jets_number<8 && *bjetsM_num>=2;
	fillHistsVector( is1tau0lCR2, 3, basicWeight );
	Bool_t is1tau0lCR3 = *tausT_number==1 && *leptonsMVAT_number==0 &&  *jets_number<7 && *bjetsM_num>=2;
	fillHistsVector( is1tau0lCR3, 4, basicWeight );
	Bool_t is1tau0lCR4 = *tausT_number==1 && *leptonsMVAT_number==0 &&  *jets_number==7 && *bjetsM_num>=2;
	fillHistsVector( is1tau0lCR4, 5, basicWeight );

	//1tau1lCR
	Bool_t is1tau1lCR0 =  *tausT_number==1 && *leptonsMVAT_number==1 &&  *jets_number>=7 && *bjetsM_num==1 ;
	fillHistsVector( is1tau1lCR0, 7, basicWeight );
	Bool_t is1tau1lCR1 =  *tausT_number==1 && *leptonsMVAT_number==1 &&  *jets_number>=7 && *bjetsM_num==0 ;
	fillHistsVector( is1tau1lCR1, 8, basicWeight );
	Bool_t is1tau1lCR2 =  *tausT_number==1 && *leptonsMVAT_number==1 &&  *jets_number==6 && *bjetsM_num>=2 ;
	fillHistsVector( is1tau1lCR2, 9, basicWeight );
	Bool_t is1tau1lCR3 =  *tausT_number==1 && *leptonsMVAT_number==1 &&  *jets_number==6 && *bjetsM_num<2 ;
	fillHistsVector( is1tau1lCR3, 10, basicWeight );
	// Bool_t is1tau1lCR4 =  *tausT_number==1 && *leptonsMVAT_number==1 &&  *jets_number<=4 && *bjetsM_num>=2 ;
	// fillHistsVector( is1tau1lCR4, 11, basicWeight );








   return kTRUE;
}

void writeHist::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void writeHist::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

	#include "../crossSectionMap.h"
	Double_t processScale = 1.0;
	if ( !m_isData ){
		processScale  = (36330* crossSectionMap[m_processName] )/ m_genWeightSum;
	}


	for( UInt_t j=0; j<jetsNumber_hists.size(); j++ ){

		std::cout<<j<<"\n";
		jetsNumber_forYieldCount_hists[j]->Scale( processScale );
		jetsNumber_forYieldCount_hists[j]->Print();
		jetsNumber_hists[j]->Scale( processScale );
		jetsNumber_hists[j]->Print();
		jets_HT_hists[j]->Scale( processScale );
		jets_HT_hists[j]->Print();
		jets_bScore_hists[j]->Scale( processScale );
		tausT_HT_hists[j]->Scale( processScale );
	}
	// std::cout<<jetsNumber_hists[0]->GetXaxis()->GetXmin()<<"; "<<jetsNumber_hists[0]->GetXaxis()->GetXmax()<<"\n";
	// jetsNumber_hists[0]->GetXaxis()->SetRange( 1, jetsNumber_hists[0]->GetNbinsX()+1 ) ;
   // std::cout<<jetsNumber_hists[0]->GetNbinsX()<<"\n";

	outputFile->Write();
	outputFile->Close();
    Info("Terminate", "outputFile here:%s", outputFile->GetName());

}