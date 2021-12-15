#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TROOT.h"
#include "TMath.h"
#include "TString.h"
// #include "TCut.h"
// #include "TPRegexp.h

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
        Process( TString fileName, Double_t sigma);
        //     :m_fileName{ fileName}, m_sigma{ sigma}
        // {
        //     m_file = TFile::Open( m_fileName);
        //     eventTree = (TTree*)m_file->Get( "newtree");
        //     alleventTree = (TTree*)m_file->Get("allevents");
        // }

        TTree* getEventTree();
        Double_t getSigma();
        Double_t getGenWeightSum();
        Double_t getScale();
        TString getProcessName();
        TH1D* getChannelHist( const TCut cut, const TCut weight );
        TH1D* getChannelHist( const TCut cut, const TCut weight,  TString branchName, const Int_t binNum, const Double_t binMin, const Double_t binMax );

};
