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
    TFile* input = TFile::Open( inputName, "READ");

    // TTTo2L2Nu, TTToHadronic, TTToSemiLeptonic, //3
    // TH1D* TTTo2L2Nu = (TH1D*)input->Get( "TTTo2L2Nu_MVA_BDT");
    TH1D* TTTo2L2Nu = getHist( "TTTo2L2Nu", input );
    TH1D* TTToHadronic = getHist( "TTToHadronic", input );
    TH1D* TTToSemiLeptonic = getHist( "TTToSemiLeptonic", input );
    TTTo2L2Nu->Print();

    Int_t binNum = TTTo2L2Nu->GetXaxis()->GetNbins();
    Double_t binMin = TTTo2L2Nu->GetXaxis()->GetXmin();
    Double_t binMax = TTTo2L2Nu->GetXaxis()->GetXmax();
    TH1D* TT = new TH1D( "TT", "TT", binNum, binMin, binMax );
    TT->Add( TTTo2L2Nu, 1.0 );
    TT->Add( TTToHadronic, 1.0 );
    TT->Print();
    
    TH1D* TT_BDT = new TH1D( "TT_BDT", "TT_BDT", binNum, binMin, binMax );
    TH1D* TTX_BDT = new TH1D( "TT_BDT", "TT_BDT", binNum, binMin, binMax );
    for( UInt_t p=0; p<allProcesses.size(); p++){
        TString iprocessName = allProcesses[p].getProcessName();
        TH1D* iHist = getHist( iprocessName, input );
        if( 0<p && p<4 ){
            cout<<"adding TT:"<<"\n";
            cout<<"processName = "<<allProcesses[p].getProcessName()<<"\n";
            TT_BDT->Add( iHist, 1.0 );
            TT_BDT->Print();
        }else if( p<8 ){
            cout<<"addding TTX"<<"\n";
            cout<<"processName = "<<iprocessName<<"\n";
            TTX_BDT->Add( iHist, 1.0 );
        }

        

    }




}
