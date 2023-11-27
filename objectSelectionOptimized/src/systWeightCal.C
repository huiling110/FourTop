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
        Int_t number = e->LHEPdfWeight->GetSize();
        std::cout<<number<<"\n";
    }
};