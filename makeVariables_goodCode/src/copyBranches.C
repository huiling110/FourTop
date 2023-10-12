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
    // 2017
    outTree->Branch("HLT_PFHT430_SixJet40_BTagCSV_p080", &HLT_PFHT430_SixJet40_BTagCSV_p080);
    outTree->Branch("HLT_PFHT380_SixJet32_DoubleBTagCSV_p075", &HLT_PFHT380_SixJet32_DoubleBTagCSV_p075);
    outTree->Branch("HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2", &HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2);
    // 2022
    outTree->Branch("HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59", &HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59);
    outTree->Branch("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94", &HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94);

    outTree->Branch("MET_pt", &MET_pt);
    outTree->Branch("MET_phi", &MET_phi);

    outTree->Branch("jets_pt_", &jets_pt_);
    outTree->Branch("jets_eta_", &jets_eta_);
    outTree->Branch("jets_btags_", &jets_btags_);
    outTree->Branch("jets_flavour_", &jets_flavour_);

    std::cout << "Done initializing ............\n";
    std::cout << "\n";
};

void CopyBranches::makeVariables(EventForMV *e)
{
    reportEntry("CopyBranch::makeVariables()");

    clearBranch();
    PV_npvsGood = *e->PV_npvsGood_;

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
    // 2017
    HLT_PFHT430_SixJet40_BTagCSV_p080 = *e->HLT_PFHT430_SixJet40_BTagCSV_p080_;
    HLT_PFHT380_SixJet32_DoubleBTagCSV_p075 = *e->HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_;
    HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 = *e->HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_;
    //2022
    HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59 = *e->HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_;
    HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94 = *e->HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_;


    copy_TTreeReaderArray_toVector(e->jets_pt, jets_pt_);
    copy_TTreeReaderArray_toVector(e->jets_eta, jets_eta_);
    copy_TTreeReaderArray_toVector(e->jets_btags, jets_btags_);
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
    jets_flavour_.clear();
};

CopyBranches::~CopyBranches(){
};