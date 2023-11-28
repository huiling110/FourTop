#include "../include/systWeightCal.h"

SystWeightCal::SystWeightCal(TTree *outTree, Bool_t isData,  Bool_t isRun3):m_isRun3{isRun3}
{
    std::cout<<"Initializing SystWeightCal class \n";

    outTree->Branch("pdfWeight", &pdfWeight);
    outTree->Branch("pdfWeight_up", &pdfWeight_up);
    outTree->Branch("pdfWeight_down", &pdfWeight_down);

    std::cout<<"Done SystWeightCal initialization.......\n\n";
};

void SystWeightCal::Select(eventForNano *e, Bool_t isData){
    if(!isData){
        // Int_t number = e->LHEPdfWeight->GetSize();
        // Double_t pdfMean = TMath::Mean(e->LHEPdfWeight->begin(), e->LHEPdfWeight->end());
        Double_t pdfStd = TMath::StdDev(e->LHEPdfWeight->begin(), e->LHEPdfWeight->end());
        // std::cout<<number<<" mean="<<pdfMean<<" std="<<pdfStd<<"\n";
        // Double_t pdfUnc = pdfStd/pdfMean;
        Double_t pdfUnc = pdfStd;
        pdfWeight = 1.;
        pdfWeight_up = 1.+pdfUnc;
        pdfWeight_down = 1.-pdfUnc;
    }
};