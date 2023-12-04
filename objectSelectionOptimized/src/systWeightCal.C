#include "../include/systWeightCal.h"
#include "../include/usefulFunc.h"
#include <algorithm>

SystWeightCal::SystWeightCal(TTree *outTree, Bool_t isData,  Bool_t isRun3):m_isRun3{isRun3}
{
    std::cout<<"Initializing SystWeightCal class \n";

    outTree->Branch("pdfWeight", &pdfWeight);
    outTree->Branch("pdfWeight_up", &pdfWeight_up);
    outTree->Branch("pdfWeight_down", &pdfWeight_down);
    outTree->Branch("pdfWeightAlphaS_up", &pdfWeightAlphaS_up);
    outTree->Branch("pdfWeightAlphaS_down", &pdfWeightAlphaS_down);
    outTree->Branch("scaleWeight", &scaleWeight);
    outTree->Branch("scaleWeight_up", &scaleWeight_up);
    outTree->Branch("scaleWeight_down", &scaleWeight_down);
    outTree->Branch("scaleWeightRe_up", &scaleWeightRe_up);
    outTree->Branch("scaleWeightRe_down", &scaleWeightRe_down);
    outTree->Branch("scaleWeightFa_up", &scaleWeightFa_up);
    outTree->Branch("scaleWeightFa_down", &scaleWeightFa_down);

    std::cout<<"Done SystWeightCal initialization.......\n\n";
};

void SystWeightCal::Select(eventForNano *e, Bool_t isData){
    if(!isData){
        //LHE pdf variation weights (w_var / w_nominal) for LHA IDs 306000 - 306102
        // pdf weight from Jan:
        // first 100 replicas of default pdf set, last 2 weights(101,102) variations of strong couplings
        // 1) 100 weights 100 variations on templates, then quadratic sum of the residuals (*) of the 100 variations(sqrt(sum_i( (w_i-w_0)^2 )))
        // 3) and 4) no difference if the pdf weights are all event weights?
        // 5): seperate uncertainty of alphaS, (101,102)
        //! I am using 4):
        // Double_t pdfMean = TMath::Mean(e->LHEPdfWeight->begin(), e->LHEPdfWeight->end());
        // Double_t pdfStd = TMath::StdDev(e->LHEPdfWeight->begin(), e->LHEPdfWeight->end());
        Double_t pdfUnc = OS::quadraticSum(*(e->LHEPdfWeight), 1., 100);
        pdfWeight_up = 1.+pdfUnc;
        pdfWeight_down = 1.-pdfUnc;
        pdfWeightAlphaS_up = e->LHEPdfWeight->At(101);
        pdfWeightAlphaS_down = e->LHEPdfWeight->At(102);

        //scale weight//???seems wrong
        //2: up; 0.5:down
        //envelope to consider: upup, downdown;up or down; no up and down
        //LHE scale variation weights (w_var / w_nominal); [0] is renscfact=0.5d0 facscfact=0.5d0 ; [1] is renscfact=0.5d0 facscfact=1d0 ; [2] is renscfact=0.5d0 facscfact=2d0 ; [3] is renscfact=1d0 facscfact=0.5d0 ; [4] is renscfact=1d0 facscfact=1d0 ; [5] is renscfact=1d0 facscfact=2d0 ; [6] is renscfact=2d0 facscfact=0.5d0 ; [7] is renscfact=2d0 facscfact=1d0 ; [8] is renscfact=2d0 facscfact=2d0
        // std::vector<Double_t> vec={e->LHEScaleWeight->At(0), e->LHEScaleWeight->At(1), e->LHEScaleWeight->At(3), e->LHEScaleWeight->At(4), e->LHEScaleWeight->At(5), e->LHEScaleWeight->At(7), e->LHEScaleWeight->At(8)}  ;
        std::vector<Double_t> vec={e->LHEScaleWeight->At(0), e->LHEScaleWeight->At(1), e->LHEScaleWeight->At(3), e->LHEScaleWeight->At(5), e->LHEScaleWeight->At(7), e->LHEScaleWeight->At(8)}  ;//this one should be correct
        // std::vector<Double_t> vec={e->LHEScaleWeight->At(1), e->LHEScaleWeight->At(2), e->LHEScaleWeight->At(3), e->LHEScaleWeight->At(4), e->LHEScaleWeight->At(6), e->LHEScaleWeight->At(8)}  ;
        // scaleWeight_up = std::max_element(e->LHEScaleWeight->begin(), e->LHEScaleWeight->end());
        // scaleWeight_down = std::min_element(e->LHEScaleWeight->begin(), e->LHEScaleWeight->end());
        scaleWeight_up = *(std::max_element(vec.begin(), vec.end()));
        scaleWeight_down =*( std::min_element(vec.begin(), vec.end()));
        scaleWeightRe_up = e->LHEScaleWeight->At(7);
        scaleWeightRe_down = e->LHEScaleWeight->At(1);
        scaleWeightFa_up = e->LHEScaleWeight->At(5);
        scaleWeightFa_down = e->LHEScaleWeight->At(3);
    }
};