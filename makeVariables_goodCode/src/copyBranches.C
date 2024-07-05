#include <map>

#include "../include/copyBranches.h"
#include "../include/variablesFunctions.h"

CopyBranches::CopyBranches(TTree *outTree)
{
    //!!!maybe make these basic variables for all object as base class
    std::cout << "Initializing CopyBranches.....\n";

    outTree->Branch("PV_npvsGood", &PV_npvsGood);

    outTree->Branch("HLT_PFHT450_SixJet40_BTagCSV_p056", &HLT_PFHT450_SixJet40_BTagCSV_p056);
    outTree->Branch("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056", &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056);
    outTree->Branch("HLT_PFJet450", &HLT_PFJet450);
    outTree->Branch("HLT_IsoMu24", &HLT_IsoMu24);
    outTree->Branch("HLT_IsoMu27", &HLT_IsoMu27);
    outTree->Branch("HLT_PFJet500", &HLT_PFJet500);
    outTree->Branch("HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5", &HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5);
    outTree->Branch("HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2", &HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2);
    outTree->Branch("HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5", &HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5);
    outTree->Branch("HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59", &HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59);
    outTree->Branch("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94", &HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94);
    outTree->Branch("HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5", &HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5);
    // 2017
    outTree->Branch("HLT_PFHT430_SixJet40_BTagCSV_p080", &HLT_PFHT430_SixJet40_BTagCSV_p080);
    outTree->Branch("HLT_PFHT380_SixJet32_DoubleBTagCSV_p075", &HLT_PFHT380_SixJet32_DoubleBTagCSV_p075);
    outTree->Branch("HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2", &HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2);
    outTree->Branch("HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0", &HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0);
    outTree->Branch("HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07", &HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07);
    outTree->Branch("HLT_PFHT1050", &HLT_PFHT1050);
    // 2022
    outTree->Branch("HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59", &HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59);
    outTree->Branch("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94", &HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94);
    outTree->Branch("HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5", &HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5);
    outTree->Branch("HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5", &HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5);
    outTree->Branch("HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5", &HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5);

    outTree->Branch("MET_pt", &MET_pt);
    outTree->Branch("MET_phi", &MET_phi);

    outTree->Branch("jets_pt_", &jets_pt_);
    outTree->Branch("jets_eta_", &jets_eta_);
    outTree->Branch("jets_btags_", &jets_btags_);
    outTree->Branch("jets_btagsPN_", &jets_btagsPN_);
    outTree->Branch("jets_btagsPT_", &jets_btagsPT_);
    outTree->Branch("jets_flavour_", &jets_flavour_);

    std::cout << "Done initializing ............\n";
    std::cout << "\n";
};

void CopyBranches::makeVariables(EventForMV *e)
{
    reportEntry("CopyBranch::makeVariables()");

    clearBranch();
    PV_npvsGood = *e->PV_npvsGood_;
    MET_pt = *e->MET_pt_;

    //
    HLT_PFHT450_SixJet40_BTagCSV_p056 = *e->HLT_PFHT450_SixJet40_BTagCSV_p056_;
    HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = *e->HLT_PFHT400_SixJet30_DoubleBTagCSV_p056_;
    HLT_PFJet450 = *e->HLT_PFJet450_;
    HLT_IsoMu24 = *e->HLT_IsoMu24_;
    HLT_IsoMu27 = *e->HLT_IsoMu27_;
    HLT_PFJet500 = *e->HLT_PFJet500_;
    HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 = *e->HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_;
    HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 = *e->HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_;
    HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 = *e->HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5_;
    HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 = *e->HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_;
    HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 = *e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_;
    HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 = *e->HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_;
    // 2017
    HLT_PFHT430_SixJet40_BTagCSV_p080 = *e->HLT_PFHT430_SixJet40_BTagCSV_p080_;
    HLT_PFHT380_SixJet32_DoubleBTagCSV_p075 = *e->HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_;
    HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 = *e->HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_;
    HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0 = *e->HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0_;
    HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07 = *e->HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07_;
    HLT_PFHT1050 = *e->HLT_PFHT1050_;
    //2022
    HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59 = *e->HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_;
    HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94 = *e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_;
    HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5 = *e->HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepJet_4p5_;
    HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5 = *e->HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepJet_4p5_;
    HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5 = *e->HLT_PFHT400_FivePFJet_120_120_60_30_30_DoublePFBTagDeepJet_4p5_;
    


    copy_TTreeReaderArray_toVector(e->jets_pt, jets_pt_);
    copy_TTreeReaderArray_toVector(e->jets_eta, jets_eta_);
    copy_TTreeReaderArray_toVector(e->jets_btags, jets_btags_);
    copy_TTreeReaderArray_toVector(e->jets_btagsPN, jets_btagsPN_);
    copy_TTreeReaderArray_toVector(e->jets_btagsPT, jets_btagsPT_);
    copy_TTreeReaderArray_toVector(e->jets_flavour, jets_flavour_);

};

void CopyBranches::reportEntry(TString className){
    if(m_entry==0){
    std::cout << "running " << className << "\n";
    }
    m_entry++;
};

void CopyBranches::clearBranch(){
    //??? derived class should also have a clearBranch()
    jets_pt_.clear();
    jets_eta_.clear();
    jets_btags_.clear();
    jets_btagsPN_.clear();
    jets_btagsPT_.clear();
    jets_flavour_.clear();
};

CopyBranches::~CopyBranches(){
};