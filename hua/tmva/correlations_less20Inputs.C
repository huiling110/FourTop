// #include "tmvaglob.C"
#include "TH1.h"
#include "TH2.h"
#include "TPaletteAxis.h"
#include "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/tmvaglob.h"
// #include "/workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/src/FourTop/hua/tmva/tmvaglob.h"

// this macro plots the correlation matrix of the various input
// variables used in TMVA (e.g. running TMVAnalysis.C).  Signal and
// Background are plotted separately

// input: - Input file (result from TMVA),
//        - use of colors or grey scale
//        - use of TMVA plotting TStyle
// void correlations( TString fin = "TMVA.root", Bool_t isRegression = kFALSE,
void correlations_less20Inputs(
        TString fin = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v1/1tau1l_varibleList_17.root",
                                Bool_t isRegression = kFALSE, 
                   Bool_t greyScale = kFALSE, Bool_t useTMVAStyle = kTRUE )
{

   // set style and remove existing canvas'
   TMVAGlob::Initialize( useTMVAStyle );

   // checks if file with name "fin" is already open, and if not opens one
   TFile* file = TMVAGlob::OpenFile( fin );  

   // signal and background or regression problem
   Int_t ncls = (isRegression ? 1 : 2 );
   // TString hName[2] = { "CorrelationMatrixS", "CorrelationMatrixB" };
   TString hName[2] = { "dataset/CorrelationMatrixS", "dataset/CorrelationMatrixB" };
   //array of 2 strings, cool
   if (isRegression) hName[0]= "CorrelationMatrix";
   // const Int_t width = 600;
   const Int_t width = 800;
   // const Int_t width = 1000;
   // const Int_t width = 1200;
   for (Int_t ic=0; ic<ncls; ic++) {
        // ncls = 2 if is Classification
      TH2* h2 = dynamic_cast<TH2*> (file->Get( hName[ic] ));
      //Safely converts pointers and references to classes up, down, and sideways along the inheritance hierarchy
      if(!h2) {
         cout << "Did not find histogram " << hName[ic] << " in " << fin << endl;
         continue;
      }
    
      //
        TString inputNum = fin;
        inputNum.Remove( 0,  inputNum.Last( '_' )+1 );
        inputNum.Remove( inputNum.First('.'), inputNum.Length() );
        cout<<"\n";
        // cout<<"inputNum: "<<inputNum<<"\n";
        cout<<"\n";

      TCanvas* c = new TCanvas( hName[ic], 
                                // Form("Correlations between MVA input variables (%s)",  (isRegression ? "" : (ic==0 ? "signal" : "background"))),
                                Form("Correlations between MVA (%s)input variables (%s)", inputNum.Data(), (isRegression ? "" : (ic==0 ? "signal" : "background"))), 
                                ic*(width+5)+200, 0, width, width ); 
      // Float_t newMargin1 = 0.13;
      // Float_t newMargin2 = 0.15;
      Float_t newMargin1 = 0.20;
      Float_t newMargin2 = 0.22;
      if (TMVAGlob::UsePaperStyle) newMargin2 = 0.22;

      c->SetGrid();
      c->SetTicks();
      c->SetLeftMargin  ( newMargin2 );
      c->SetBottomMargin( newMargin2 );
      c->SetRightMargin ( newMargin1 );
      c->SetTopMargin   ( newMargin1 );
      gStyle->SetPalette( 1, 0 );//if ncolors == 1 && colors == 0, a Rainbow Color map is created with 50 colors
      //The color palette is used by the histogram classes 


      gStyle->SetPaintTextFormat( "3g" );

      // h2->SetMarkerSize( 1.5 );
      h2->SetMarkerSize( 0.8 );//marker is the number on the grid
      // h2->SetMarkerSize( 0.6 );//marker is the number on the grid
      h2->SetMarkerColor( 0 );
      // Float_t labelSize = 0.040;
      // Float_t labelSize = 0.030;
      Float_t labelSize = 0.025;
      h2->GetXaxis()->SetLabelSize( labelSize );
      // h2->GetXaxis()->SetLabelSize( 0.02 );
      h2->GetYaxis()->SetLabelSize( labelSize );
      // h2->LabelsOption( "d" );//"d" draw labels down (start of label left adjusted)
      h2->LabelsOption( "v" );
      h2->SetLabelOffset( 0.011 );// label offset on x axis    

      h2->Draw("colz"); // color pads   
      c->Update();
      //?when is it nessesary to update canvas?

      // modify properties of paletteAxis
      TPaletteAxis* paletteAxis = (TPaletteAxis*)h2->GetListOfFunctions()->FindObject( "palette" );
      paletteAxis->SetLabelSize( 0.03 );
      paletteAxis->SetX1NDC( paletteAxis->GetX1NDC() + 0.02 );

      h2->Draw("textsame");  // add text

      // add comment    
      // TText* t = new TText( 0.53, 0.88, "Linear correlation coefficients in %" );
      TText* t = new TText( 0.53, 0.88, Form("(%s input variables) ", inputNum.Data() ) );
      t->SetNDC();
      t->SetTextSize( 0.026 );
      t->AppendPad();    

      // TMVAGlob::plot_logo( );
      c->Update();

      // TString fname = "plots/";
      // fname += hName[ic];
        TString ihName = hName[ic];
        ihName.Remove( 0, ihName.First( '/' )+1 );
        TString inputFile = fin;
        TString fileDir = inputFile.Remove( inputFile.Last( '/')+1, inputFile.Length()-inputFile.Last( '/') );
        fileDir = fileDir + "results/";
        TString inputFile2 = fin;
        TString fileName = inputFile2.Remove( 0, inputFile2.Last( '/')+1 );
        fileName.Remove( fileName.Length()-5, fileName.Length() );
        cout<<"fileNAME = "<<fileName<<"\n";
        cout<<"fileDir = "<<fileDir<<"\n";
        TMVAGlob::imgconv( c, Form("%s%s%s",fileDir.Data(),fileName.Data(), ihName.Data() ) );
      // TMVAGlob::imgconv( c, fname );
   }
}
