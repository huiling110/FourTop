#include "../include/systWeightCal.h"

SystWeightCal::SystWeightCal(TTree *outTree, Bool_t isData,  Bool_t isRun3):m_isRun3{isRun3}
{
    std::cout<<"Initializing SystWeightCal class \n";
};

void SystWeightCal::Select(eventForNano *e, Bool_t isData){

};