#include "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/EYandSP_usingClass_v3.h" 

TH1D* getHist( const TString histName, TFile* input ){
    TH1D* temp = (TH1D*)input->Get( histName + "_MVA_BDT");
    temp->Sumw2();
    return temp;
}


void sumBGsTogether( 
        TString inputName = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau1l_v1/AppResults/TMVApp_1tau1l_11var_forCombine.root"
        ){
    using std::cout;
    // TFile* input = TFile::Open( inputName, "READ");
    TFile* input = TFile::Open( inputName, "UPDATE");

    // TH1D* TTTo2L2Nu = getHist( "TTTo2L2Nu", input );
    // TH1D* TTToHadronic = getHist( "TTToHadronic", input );
    // TH1D* TTToSemiLeptonic = getHist( "TTToSemiLeptonic", input );
    // TTTo2L2Nu->Print();

    Int_t binNum = TTTo2L2Nu->GetXaxis()->GetNbins();
    Double_t binMin = TTTo2L2Nu->GetXaxis()->GetXmin();
    Double_t binMax = TTTo2L2Nu->GetXaxis()->GetXmax();
    // TH1D* TT = new TH1D( "TT", "TT", binNum, binMin, binMax );
    // TT->Add( TTTo2L2Nu, 1.0 );
    // TT->Add( TTToHadronic, 1.0 );
    // TT->Print();
    
    TH1D* TT_BDT = new TH1D( "TT_BDT", "TT_BDT", binNum, binMin, binMax );
    TH1D* TTX_BDT = new TH1D( "TTX_BDT", "TTX_BDT", binNum, binMin, binMax );
    TH1D* VV_BDT = new TH1D( "VV_BDT", "VV_BDT", binNum, binMin, binMax );
    TH1D* VVV_BDT = new TH1D( "VVV_BDT", "VVV_BDT", binNum, binMin, binMax );
    TH1D* WJets_BDT = new TH1D( "WJets_BDT", "WJets_BDT", binNum, binMin, binMax );
    TH1D* DY_BDT = new TH1D( "DY_BDT", "DY_BDT", binNum, binMin, binMax );
    TH1D* SingleTop_BDT = new TH1D( "SingleTop_BDT", "SingleTop_BDT", binNum, binMin, binMax );
    TH1D* TX_BDT = new TH1D( "TX_BDT", "TX_BDT", binNum, binMin, binMax );
    TH1D* QCD_BDT = new TH1D( "QCD_BDT", "QCD_BDT", binNum, binMin, binMax );
    TH1D* iHist ;
    for( UInt_t p=0; p<allProcesses.size(); p++){
        TString iprocessName = allProcesses[p].getProcessName();
        iHist = getHist( iprocessName, input );
        if( 0<p && p<4 ){
            cout<<"adding TT:"<<"\n";
            cout<<"processName = "<<allProcesses[p].getProcessName()<<"\n";
            TT_BDT->Add( iHist, 1.0 );
        }else if( p<8 ){
            cout<<"addding TTX:"<<"\n";
            cout<<"processName = "<<iprocessName<<"\n";
            TTX_BDT->Add( iHist, 1.0 );
        }else if( p<13 ){
            cout<<"adding VV:"<<"\n";
            cout<<"processName = "<<iprocessName<<"\n";
            VV_BDT->Add( iHist, 1.0 );
        }else if( p<21 ){
            cout<<"adding VVV:"<<"\n";
            cout<<"processName = "<<iprocessName<<"\n";
            VVV_BDT->Add( iHist, 1.0 );
        }else if( p<22 ){
            cout<<"adding WJets:\n";
            cout<<"processName = "<<iprocessName<<"\n";
            WJets_BDT->Add( iHist, 1.0 );
        }else if( p<23 ){
            cout<<"adding DY:\n";
            cout<<"processName = "<<iprocessName<<"\n";
            DY_BDT->Add( iHist, 1.0 );
        }else if( p<27 ){
            cout<<"adding SingleTop:\n";
            cout<<"processName = "<<iprocessName<<"\n";
            SingleTop_BDT->Add( iHist, 1.0 );
        }else if( p<30 ){
            cout<<"adding TX:\n";
            TX_BDT->Add( iHist, 1.0 );
        }else if( p<36 ){
            cout<<"adding QCD:\n";
            QCD_BDT->Add( iHist, 1.0 );
        }
        
       delete iHist; 
    }

    TT_BDT->Print();
    VV_BDT->Print();
    VVV_BDT->Print();
    WJets_BDT->Print();
    DY_BDT->Print();
    SingleTop_BDT->Print();
    TX_BDT->Print();
    QCD_BDT->Print();



    // TFile* outfile = new TFile( )
    input->Write();
    input->Close();



}
