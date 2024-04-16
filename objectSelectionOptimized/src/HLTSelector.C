#include "../include/HLTSelector.h"

HLTSelector::HLTSelector(TTree *outTree, const TString era, const Bool_t isData, const Bool_t isRun3): m_era{era}, m_isData{isData}, m_isRun3{isRun3}
{
    std::cout<<"Initializing HLTSelector...........\n";
    std::cout<<"m_era="<<m_era<<" isData="<<m_isData<<" isRun3="<<m_isRun3<<"\n";


    outTree->Branch("HLT_PFHT450_SixJet40_BTagCSV_p056_", &HLT_PFHT450_SixJet40_BTagCSV_p056_);
    outTree->Branch("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_", &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_);
    outTree->Branch("HLT_PFJet450_", &HLT_PFJet450_);
    outTree->Branch("HLT_PFJet500_", &HLT_PFJet500_);
    outTree->Branch("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_", &HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_);
    outTree->Branch("HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_", &HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_);
    outTree->Branch("HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_", &HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_);
    outTree->Branch("HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_", &HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_);
    outTree->Branch("HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_", &HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_);
    outTree->Branch("HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_", &HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_);
    outTree->Branch("HLT_PFHT430_SixJet40_BTagCSV_p080_", &HLT_PFHT430_SixJet40_BTagCSV_p080_);
    outTree->Branch("HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_", &HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_);
    outTree->Branch("HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_", &HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_);
    outTree->Branch("HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_", &HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_);
    outTree->Branch("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_", &HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_);
    outTree->Branch("HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5_", &HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5_);
    outTree->Branch("HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5_", &HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5_);
    outTree->Branch("HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5_", &HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5_);

    outTree->Branch("HLT_IsoMu24_", &HLT_IsoMu24_);
    outTree->Branch("HLT_IsoMu27_", &HLT_IsoMu27_);

    outTree->Branch("HLT_Ele24_eta2p1_WPTight_Gsf_LooseDeepTauPFTauHPS30_eta2p1_CrossL1_", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseDeepTauPFTauHPS30_eta2p1_CrossL1_);
    outTree->Branch("HLT_IsoMu20_eta2p1_LooseDeepTauPFTauHPS27_eta2p1_CrossL1_", &HLT_IsoMu20_eta2p1_LooseDeepTauPFTauHPS27_eta2p1_CrossL1_);
    outTree->Branch("HLT_LooseDeepTauPFTauHPS180_L2NN_eta2p1_", &HLT_LooseDeepTauPFTauHPS180_L2NN_eta2p1_);


    std::cout<<"Done HLTSelector initializing .............\n";
    std::cout<<"\n";
};

Bool_t HLTSelector::Select(eventForNano *e,  const Bool_t isHLTSel)
{
    // Here I manully set the branch value = nanoAOD value only when the trigger is supposed to work in the run period;
    // otherwise trigger=false;
    clearBranch();
    HLT_IsoMu24_ = **e->HLT_IsoMu24;
    HLT_IsoMu27_ = **e->HLT_IsoMu27;
    Bool_t ifPass = kFALSE;
    // the HLT branch pointer null pointer is not exist in a file
    if (m_era.CompareTo("2016preVFP") == 0 || m_era.CompareTo("2016postVFP") == 0)
    {
        // std::cout<<"HLT 2016\n";
        ifPass = **e->HLT_PFHT450_SixJet40_BTagCSV_p056 || **e->HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 || **e->HLT_PFJet450;
        HLT_PFHT450_SixJet40_BTagCSV_p056_ = **e->HLT_PFHT450_SixJet40_BTagCSV_p056;
        HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_ = **e->HLT_PFHT400_SixJet30_DoubleBTagCSV_p056;
        HLT_PFJet450_ = **e->HLT_PFJet450;
    }
    else if (m_era.CompareTo("2017") == 0)
    {
        // std::cout<<"HLT 2017\n"; 
        HLT_PFJet500_ = **e->HLT_PFJet500;
        if (!m_isData)
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
    else if (m_era.CompareTo("2018") == 0)
    {
        HLT_PFJet500_ = **e->HLT_PFJet500;
        HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_ = **e->HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5;

        if (!m_isData)
        {
            // ifPass = **e->HLT_PFJet500 || **e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 || **e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94;
            HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = **e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59;
            HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ = **e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94;
            // ifPass = HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ || HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_;
            ifPass = HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ || HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ || HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_ ;
        }
        else
        {
            if (*e->run >= 315252 && *e->run <= 325175)
            {
                // 2018
                if (*e->run < 315974)
                {
                    // ifPass = **e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 || **e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 || **e->HLT_PFJet500;
                    HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ = **e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5;
                    HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = **e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2;
                    // ifPass = HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ || HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_;
                    ifPass = HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_ || HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ ||HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_;
                    
                }
                else if (*e->run < 317509)
                {
                    // ifPass = **e->HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 || **e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 || **e->HLT_PFJet500;
                    HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_ = **e->HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5;
                    HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ = **e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2;
                    // ifPass = HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_ || HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_;
                    ifPass = HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_ || HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_ || HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_;
                }
                else
                {
                    // ifPass = **e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 || **e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 || **e->HLT_PFJet500;
                    HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ = **e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59;
                    HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ = **e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94;
                    // ifPass = HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ || HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_;
                    ifPass = HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ || HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ || HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_;
                }
            }
            else
            {
                std::cout << "ERROR!!! 2018 data out of range for HLT \n";
            }
        }
    }else if(m_era.CompareTo("2022")==0 || m_era.CompareTo("2022postEE")==0 || m_era.CompareTo("2022preEE")==0){
        // ifPass = **e->HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59 || **e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94|| **e->HLT_PFJet500;
        HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_ = **e->HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59;
        HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_ = **e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94;
        HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5_ = **e->HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5;
        HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5_ = **e->HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5;
        HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5_ = **e->HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5;
        HLT_PFJet500_ = **e->HLT_PFJet500; //!should probably romove this trigger
        ifPass = HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_ || HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_ || HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5_ || HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5_ || HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5_ || HLT_PFJet500_;
    }
    if (!isHLTSel)
    {
        ifPass = kTRUE;
    }
    // std::cout<<"ifHLT="<<ifPass<<"\n";
    return ifPass;
};

Bool_t HLTSelector::SelectTauTri(const eventForNano *e, const Bool_t ifHLTSel)
{
    Bool_t ifPass = kFALSE;
    if(m_isRun3){
        HLT_Ele24_eta2p1_WPTight_Gsf_LooseDeepTauPFTauHPS30_eta2p1_CrossL1_ = **e->HLT_Ele24_eta2p1_WPTight_Gsf_LooseDeepTauPFTauHPS30_eta2p1_CrossL1;
        HLT_IsoMu20_eta2p1_LooseDeepTauPFTauHPS27_eta2p1_CrossL1_ = **e->HLT_IsoMu20_eta2p1_LooseDeepTauPFTauHPS27_eta2p1_CrossL1;
        HLT_LooseDeepTauPFTauHPS180_L2NN_eta2p1_ = **e->HLT_LooseDeepTauPFTauHPS180_L2NN_eta2p1;
    }

    if (!ifHLTSel)
    {
        ifPass = kTRUE;
    }

    return ifPass;
}

void HLTSelector::clearBranch()
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
    HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_ = kFALSE;
    // 2017
    HLT_PFHT430_SixJet40_BTagCSV_p080_ = kFALSE;
    HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_ = kFALSE;    // run<299329
    HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_ = kFALSE; // run<=306460 2017 end
};
