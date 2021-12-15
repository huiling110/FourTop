
class Process
{
    //it seems you lack a deconstructor for this class
    private:
        TString m_fileName;
        Double_t m_sigma;
        TFile* m_file;
        TTree *eventTree;
        TTree *alleventTree;
        TH1D *channelEY;
    public:
        Process( TString fileName, Double_t sigma)
            :m_fileName{ fileName}, m_sigma{ sigma}
        {
            m_file = TFile::Open( m_fileName);
            eventTree = (TTree*)m_file->Get( "newtree");
            alleventTree = (TTree*)m_file->Get("allevents");
        }

        TTree* getEventTree(){
            // return (TTree*)m_file->Get( "newtree");
            return eventTree;
        }
        // TTree* getAllEventTree(){
            // return alleventTree;
        // }
        Double_t getSigma(){
            return m_sigma;
        }
        Double_t getGenWeightSum(){
           TH1D* h_genWeight = new TH1D( "genWeight", "genWeight", 100, -100., 100.);
           alleventTree->Project( "genWeight", "genWeight_allEvents");
           h_genWeight->StatOverflows(kTRUE);
            Double_t sum = h_genWeight->GetMean() * h_genWeight->GetEntries();
            delete h_genWeight;
            return sum;
           // return h_genWeight->GetMean() * h_genWeight->GetEntries();
        }
        Double_t getScale(){
            return m_sigma/getGenWeightSum();
        }
        TString getProcessName(){
            TString name = m_fileName;
            name.Remove( 0, baseDir.Length()  );
            if ( name.Contains("tZq") ){
                name.Remove( name.Index("4f")-1,name.Length());
                // cout<<"name"<<"\n";
            }else if ( name.Contains( "ST_tW") ) {
                name.Remove( name.Index("5f")-1, name.Length() );
            }else if ( name.Contains( "QCD") ){
                name.Remove( name.Index( "Tune")-1, name.Length() );
            }
            else{
                name.Remove( name.First("_"), name.Length());
            }
            // std::cout<<m_fileName<<"\n";
            return name;
        }

        TH1D* getChannelHist( const TCut cut, const TCut weight ){
            TString hName = getProcessName();
            TH1D* h = new TH1D( hName, hName, 40 , 0 , 40 );//1
            getEventTree()->Project( hName, "jets_number", weight*( cut ));
            channelEY = (TH1D*)h->Clone( hName );
            delete h;
            return channelEY;
        }
        TH1D* getChannelHist( const TCut cut, const TCut weight,  TString branchName, const Int_t binNum, const Double_t binMin, const Double_t binMax ){
            TString hName = getProcessName();
            TH1D* h = new TH1D( hName, hName, binNum , binMin , binMax );//1
            getEventTree()->Project( hName, branchName, weight*( cut ));
            channelEY = (TH1D*)h->Clone( hName );
            // channelEY->Scale( globalWeight );
            delete h;
            return channelEY;
        }

        // Double_t getChannelYield( const TCut cut, const TCut weight ){
        // }
};