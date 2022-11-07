#ifndef PROCESS_CLASS_H
#define PROCESS_CLASS_H

#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TROOT.h"
#include "TMath.h"
#include "TString.h"
#include "TCut.h"
#include <iostream>



class Process
{
    //it seems you lack a deconstructor for this class
    private:
        TString m_fileName;
        Double_t m_sigma;
        TFile* m_file;
        TTree *eventTree;
        // TTree *alleventTree;
        TTree* Runs;
        TH1D *channelEY;
        // const Double_t m_LUMI;
    public:
        Process( TString fileName, Double_t sigma)
            :m_fileName{ fileName}, m_sigma{ sigma}
        {
            m_file = TFile::Open( m_fileName);
            eventTree = (TTree*)m_file->Get( "newtree");
            // alleventTree = (TTree*)m_file->Get("allevents");
            Runs = (TTree *)m_file->Get("Runs");
        }
        //???deconstructor not working?
        /*
        ~Process(){
           delete m_file;
           delete eventTree;
           delete alleventTree;
           delete channelEY; 
        }
        */

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
        Double_t getGenWeightSum();
        Double_t getScale(){
            return m_sigma/getGenWeightSum();
        }
        TString getProcessName();
        

        TH1D* getChannelHist( const TCut cut, const TCut weight );
        
        TH1D* getChannelHist( const TCut cut, const TCut weight,  TString branchName, const Int_t binNum, const Double_t binMin, const Double_t binMax );
        

    // ClassDef ( Process,1) ;
};

#endif