#include "Process_Class.h"


        
Double_t Process::getGenWeightSum(){
    // TH1D* h_genWeight = new TH1D( "genWeight", "genWeight", 100, -100., 100.);
    // alleventTree->Project( "genWeight", "genWeight_allEvents");
    // h_genWeight->StatOverflows(kTRUE);
    // Double_t sum = h_genWeight->GetMean() * h_genWeight->GetEntries();
    // delete h_genWeight;
    // return sum;

    Double_t igen;
    Runs->SetBranchAddress("genEventSumw", &igen);
    Double_t genWeightSumInitial = 0.0;
    for (int iEntry = 0; Runs->LoadTree(iEntry) >= 0; ++iEntry)
    {
        Runs->GetEntry(iEntry);
        genWeightSumInitial += igen;
    }
    return genWeightSumInitial;
}
TString Process::getProcessName()
{
    TString name = m_fileName;
    // name.Remove( 0, baseDir.Length()  );
    // if ( name.Contains("tZq") ){
    //     name.Remove( name.Index("4f")-1,name.Length());
    // }else if ( name.Contains( "ST_tW") ) {
    //     name.Remove( name.Index("5f")-1, name.Length() );
    // }else if ( name.Contains( "QCD") ){
    //     name.Remove( name.Index( "Tune")-1, name.Length() );
    // }
    // else{
    //     name.Remove( name.First("_"), name.Length());
    // }
    // name = name( 0, name.Index("root")-1 );
    name = name( name.Last('/')+1, name.Index("root")-name.Last('/')-2 );
    // std::cout<<"processName: "<<name<<"\n";
    return name;
}

TH1D* Process::getChannelHist( const TCut cut, const TCut weight ){
    TString hName = getProcessName();
    TH1D* h = new TH1D( hName, hName, 40 , 0 , 40 );//1
    getEventTree()->Project( hName, "jets_number", weight*( cut ));
    channelEY = (TH1D*)h->Clone( hName );
    delete h;
    return channelEY;
}
TH1D* Process::getChannelHist( const TCut cut, const TCut weight,  TString branchName, const Int_t binNum, const Double_t binMin, const Double_t binMax ){
    TString hName = getProcessName();
    TH1D* h = new TH1D( hName, hName, binNum , binMin , binMax );//1
    getEventTree()->Project( hName, branchName, weight*( cut ));
    channelEY = (TH1D*)h->Clone( hName );
    // channelEY->Scale( globalWeight );
    delete h;
    return channelEY;
}

    // ClassDef ( Process,1) ;
