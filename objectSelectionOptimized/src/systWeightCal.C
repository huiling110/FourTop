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
    outTree->Branch("PSWeight_up", &PSWeight_up);
    outTree->Branch("PSWeight_down", &PSWeight_down);

    std::cout<<"Done SystWeightCal initialization.......\n\n";
};

void SystWeightCal::Select(eventForNano *e, Bool_t isData){
    clearBranch();
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
        Double_t pdfUnc = 0.;
        if (e->LHEPdfWeight != nullptr)
        {//!!!some files like wz don't have LHE branches, assign nominal 1 to them
        //!!!https://cms-talk.web.cern.ch/t/lhepdfweights-in-nanoaodv9/17688/4?u=akapoor
            pdfUnc = OS::quadraticSum(*(e->LHEPdfWeight), 1., 100);
            pdfWeightAlphaS_up = e->LHEPdfWeight->At(101);
            pdfWeightAlphaS_down = e->LHEPdfWeight->At(102);
        }
        pdfWeight_up = 1.+pdfUnc;
        pdfWeight_down = 1.-pdfUnc;
        //might have to store all 100 variation for alternative studies

        //scale weight//???seems wrong
        //2: up; 0.5:down
        //envelope to consider: upup, downdown;up or down; no up and down
        //LHE scale variation weights (w_var / w_nominal); [0] is renscfact=0.5d0 facscfact=0.5d0 ; [1] is renscfact=0.5d0 facscfact=1d0 ; [2] is renscfact=0.5d0 facscfact=2d0 ; [3] is renscfact=1d0 facscfact=0.5d0 ; [4] is renscfact=1d0 facscfact=1d0 ; [5] is renscfact=1d0 facscfact=2d0 ; [6] is renscfact=2d0 facscfact=0.5d0 ; [7] is renscfact=2d0 facscfact=1d0 ; [8] is renscfact=2d0 facscfact=2d0
        // std::vector<Double_t> vec={e->LHEScaleWeight->At(0), e->LHEScaleWeight->At(1), e->LHEScaleWeight->At(3), e->LHEScaleWeight->At(4), e->LHEScaleWeight->At(5), e->LHEScaleWeight->At(7), e->LHEScaleWeight->At(8)}  ;
        if (e->LHEScaleWeight!=nullptr){
            //!w_var / w_nominal
            std::vector<Double_t> vec={e->LHEScaleWeight->At(0), e->LHEScaleWeight->At(1), e->LHEScaleWeight->At(3), e->LHEScaleWeight->At(5), e->LHEScaleWeight->At(7), e->LHEScaleWeight->At(8)}  ;//this one should be correct
            scaleWeight_up = *(std::max_element(vec.begin(), vec.end()));
            scaleWeight_down =*( std::min_element(vec.begin(), vec.end()));
            scaleWeightRe_up = e->LHEScaleWeight->At(7);
            scaleWeightRe_down = e->LHEScaleWeight->At(1);
            scaleWeightFa_up = e->LHEScaleWeight->At(5);
            scaleWeightFa_down = e->LHEScaleWeight->At(3);
            scaleWeight = e->LHEScaleWeight->At(4);
            //Jan suggested scale the systematic weights by the nominal weight
        }

        if(e->PSWeight!=nullptr){//PS weights (w_var / w_nominal); [0] is ISR=2 FSR=1; [1] is ISR=1 FSR=2[2] is ISR=0.5 FSR=1; [3] is ISR=1 FSR=0.5;
        //Recommendation: default variations with factor 2 and 0.5 
            PSWeight_up = e->PSWeight->At(0);
            PSWeight_down = e->PSWeight->At(3);
        }
    }
};

void SystWeightCal::clearBranch(){
    pdfWeight=1.;
    pdfWeight_up=1.;
    pdfWeight_down=1.;
    pdfWeightAlphaS_up=1.;
    pdfWeightAlphaS_down=1.;
    scaleWeight=1.;
    scaleWeight_up=1.;
    scaleWeight_down=1.;
    scaleWeightRe_up=1.;
    scaleWeightRe_down=1.;
    scaleWeightFa_up=1.;
    scaleWeightFa_down=1.;
    PSWeight_up=1.;
    PSWeight_down=1.;
};