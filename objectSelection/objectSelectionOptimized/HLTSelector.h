#ifndef HLTSELECTOR_H
#define HLTSELECTOR_H

#include "eventReader_nano.h"

class HLTSelector
{
public:
    // HLTSelector(TTree *outTree) : m_outTree{outTree}
    HLTSelector(TTree *outTree)
    {
        outTree->Branch("HLT_PFHT450_SixJet40_BTagCSV_p056_", &HLT_PFHT450_SixJet40_BTagCSV_p056_);
        outTree->Branch("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_", &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_);
        outTree->Branch("HLT_PFJet450_", &HLT_PFJet450_);
        outTree->Branch("HLT_PFJet500_", &HLT_PFJet500_);
        outTree->Branch("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_", &HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_);
        outTree->Branch("HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_", &HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_);
        outTree->Branch("HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_", &HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_);
        outTree->Branch("HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_", &HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_);
        outTree->Branch("HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_", &HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_);
        outTree->Branch("HLT_PFHT430_SixJet40_BTagCSV_p080_", &HLT_PFHT430_SixJet40_BTagCSV_p080_);
        outTree->Branch("HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_", &HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_);
        outTree->Branch("HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_", &HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_);
        // outTree->Branch("", &);
    };
    ~HLTSelector(){
    };

    Bool_t Select(eventForNano *e, const TString era = "2017", const Bool_t isData = kFALSE, Bool_t isHLTSel = kTRUE)
    // Bool_t Select(const eventForNano *e, const TString era = "2017", const Bool_t isData = kFALSE)
    {
        // Here I manully set the branch value = nanoAOD value only when the trigger is supposed to work in the run period;
        // otherwise trigger=false;
        clearBranch();
        Bool_t ifPass = kFALSE;
        // the HLT branch pointer null pointer is not exist in a file
        if (era.CompareTo("2016preVFP") == 0 || era.CompareTo("2016postVFP") == 0)
        {
            // std::cout<<"HLT 2016\n";
            ifPass = **e->HLT_PFHT450_SixJet40_BTagCSV_p056 || **e->HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 || **e->HLT_PFJet450;
            // ifPass = **(e->HLT_PFJet450);
        }
        else if (era.CompareTo("2017") == 0)
        {
            // std::cout<<"HLT 2017\n";
            HLT_PFJet500_ = **e->HLT_PFJet500;
            if (!isData)
            {
                ifPass = **e->HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 || **e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 || **e->HLT_PFJet500;
                HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_ = **e->HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2;
                HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ = **e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5;
            }
            else
            {
                if ((*e->run) >= 297050 && (*e->run) <= 306460)
                {
                    // 2017 data
                    if (*e->run < 299329)
                    {
                        ifPass = **e->HLT_PFHT430_SixJet40_BTagCSV_p080 || **e->HLT_PFHT380_SixJet32_DoubleBTagCSV_p075 || **e->HLT_PFJet500;
                        HLT_PFHT430_SixJet40_BTagCSV_p080_ = **e->HLT_PFHT430_SixJet40_BTagCSV_p080;
                        HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_ = **e->HLT_PFHT380_SixJet32_DoubleBTagCSV_p075;
                    }
                    else
                    {
                        ifPass = **e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 || **e->HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 || **e->HLT_PFJet500;
                        HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ = **e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5;
                        HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_ = **e->HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2;
                    }
                }
                else
                {
                    std::cout << "ERROR!!! 2017 data out of range for HLT \n";
                }
            }
        }
        else if (era.CompareTo("2018") == 0)
        {
            HLT_PFJet500_ = **e->HLT_PFJet500;
            if (!isData)
            {
                ifPass = **e->HLT_PFJet500  || **e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 || **e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 ;
                HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = **e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 ;
                HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ =**e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 ;
            }
            else
            {
                if (*e->run >= 315257 && *e->run <= 325173)
                {
                    // 2018
                    if (*e->run < 315974)
                    {
                        ifPass = **e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5  || **e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2  || **e->HLT_PFJet500 ;
                        HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ = **e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5;
                        HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = **e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2;
                    }
                    else if (*e->run < 317509)
                    {
                        ifPass = **e->HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5  || **e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 || **e->HLT_PFJet500 ;
                        HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_ = **e->HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5;
                        HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = **e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2;
                    }
                    else
                    {
                        ifPass = **e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59  || **e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 || **e->HLT_PFJet500 ;
                        HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = **e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59;
                        HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ = **e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94;
                    }
                }
                else
                {
                    std::cout << "ERROR!!! 2018 data out of range for HLT \n";
                }
            }
        }
        // m_outTree->Fill(); //??? should we fill in every Selector or no need?
        // inconsistent fill could cause strange things
        if (!isHLTSel)
        {
            ifPass = kTRUE;
        }
        // std::cout<<"ifHLT="<<ifPass<<"\n";
        return ifPass;
    };
    void clearBranch()
    {
        HLT_PFHT450_SixJet40_BTagCSV_p056_ = kFALSE;
        HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ = kFALSE;
        HLT_PFJet450_ = kFALSE;
        HLT_PFJet500_ = kFALSE;
        HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ = kFALSE;
        HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = kFALSE;
        // TRIGGERS FOR 2018 data A
        HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = kFALSE;
        HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_ = kFALSE;
        HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ = kFALSE;
        // 2017
        HLT_PFHT430_SixJet40_BTagCSV_p080_ = kFALSE;
        HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_ = kFALSE;    // run<299329
        HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_ = kFALSE; // run<=306460 2017 end
    }
    // void

private:
    // TTree *m_outTree;
    // output branches
    Bool_t HLT_PFHT450_SixJet40_BTagCSV_p056_ = kFALSE;
    Bool_t HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ = kFALSE;
    Bool_t HLT_PFJet450_ = kFALSE;
    Bool_t HLT_PFJet500_ = kFALSE;
    Bool_t HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ = kFALSE;
    Bool_t HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = kFALSE;
    // TRIGGERS FOR 2018 data A
    Bool_t HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = kFALSE;
    Bool_t HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_ = kFALSE;
    Bool_t HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ = kFALSE;
    // 2017
    Bool_t HLT_PFHT430_SixJet40_BTagCSV_p080_ = kFALSE;
    Bool_t HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_ = kFALSE;    // run<299329
    Bool_t HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_ = kFALSE; // run<=306460 2017 end
};

#endif
