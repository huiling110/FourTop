#ifndef HLTSELECTOR_H
#define HLTSELECTOR_H

#include "eventReader_nano.h"

class HLTSelector
{
public:
    HLTSelector(TTree *outTree) : m_outTree{outTree}
    {
        m_outTree->Branch("HLT_PFHT450_SixJet40_BTagCSV_p056_", &HLT_PFHT450_SixJet40_BTagCSV_p056_);
        m_outTree->Branch("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_", &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_);
        m_outTree->Branch("HLT_PFJet450_", &HLT_PFJet450_);
        m_outTree->Branch("HLT_PFJet500_", &HLT_PFJet500_);
        m_outTree->Branch("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_", &HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_);
        m_outTree->Branch("HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_", &HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_);
        m_outTree->Branch("HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_", &HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_);
        m_outTree->Branch("HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_", &HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_);
        m_outTree->Branch("HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_", &HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_);
        m_outTree->Branch("HLT_PFHT430_SixJet40_BTagCSV_p080_", &HLT_PFHT430_SixJet40_BTagCSV_p080_);
        m_outTree->Branch("HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_", &HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_);
        m_outTree->Branch("HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_", &HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_);
        // m_outTree->Branch("", &);
    };
    ~HLTSelector(){

    };
    // init(){

    // };
    Bool_t Select(eventForNano *e, const TString era = "2017", const Bool_t isData = kFALSE)
    // Bool_t Select(const eventForNano *e, const TString era = "2017", const Bool_t isData = kFALSE)
    {
        clearBranch();
        Bool_t ifPass = kFALSE;
        // the HLT branch pointer null pointer is not exist in a file
        if (era.CompareTo("2016preVFP") == 0 || era.CompareTo("2016postVFP") == 0)
        {
            ifPass = **e->HLT_PFHT450_SixJet40_BTagCSV_p056 || **e->HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 || **e->HLT_PFJet450;
            // ifPass = **(e->HLT_PFJet450);
        }
        else if (era.CompareTo("2017") == 0)
        {
            if (!isData)
            {
                ifPass = **e->HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 || **e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 || **e->HLT_PFJet500;
            }
            else
            {
                if ((*e->run) >= 297050 && (*e->run) <= 306460)
                // if (e->run->Get() >= 297050 && e->run->Get() <= 306460)
                {
                    // 2017 data
                    if (*e->run < 299329)
                    // if (e->run->Get() < 299329)
                    {
                        ifPass = **e->HLT_PFHT430_SixJet40_BTagCSV_p080 || **e->HLT_PFHT380_SixJet32_DoubleBTagCSV_p075 || **e->HLT_PFJet500;
                    }
                    else
                    {
                        ifPass = **e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 || **e->HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 || **e->HLT_PFJet500;
                    }
                }
                else
                {
                    std::cout << "ERROR!!! 2017 data out of range for HLT \n";
                }
            }
        }

        if (ifPass)
        {
            HLT_PFHT450_SixJet40_BTagCSV_p056_ = **e->HLT_PFHT450_SixJet40_BTagCSV_p056;
            HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ = **e->HLT_PFHT400_SixJet30_DoubleBTagCSV_p056;
            HLT_PFJet450_ = **e->HLT_PFJet450;
            // 2017
            HLT_PFJet500_ = **e->HLT_PFJet500;
            ;
        }

        // m_outTree->Fill(); //??? should we fill in every Selector or no need?
        // inconsistent fill could cause strange things

        return ifPass;
    };
    void clearBranch()
    {
        // HLT_PFHT450_SixJet40_BTagCSV_p056_.clear();
    }
    // void

private:
    TTree *m_outTree;
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
