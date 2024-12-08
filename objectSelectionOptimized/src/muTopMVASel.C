#include "../include/muTopMVASel.h"

MuTopMVASel::MuTopMVASel(TTree *outTree, const TString era, const Bool_t isData,  const Bool_t isRun3,const Int_t m_type) : m_type{m_type}, m_era{era}, m_isData{isData}, m_isRun3{isRun3}
{ // m_type for different electrons
    std::cout << "Initializing MuTopMVASel......\n";
    std::cout << "m_era=" << m_era << "; m_isRun3=" << m_isRun3 << "; m_type=" << m_type<< "\n";

    outTree->Branch("muonsTopMVA" +WPMap.at(m_type)+ "_pt", &muonsTopMVAT_pt);
    outTree->Branch("muonsTopMVA" +WPMap.at(m_type)+ "_eta", &muonsTopMVAT_eta);
    outTree->Branch("muonsTopMVA" +WPMap.at(m_type)+ "_phi", &muonsTopMVAT_phi);
    outTree->Branch("muonsTopMVA" +WPMap.at(m_type)+ "_mass", &muonsTopMVAT_mass);
    outTree->Branch("muonsTopMVA" +WPMap.at(m_type)+ "_charge", &muonsTopMVAT_charge);
    // outTree->Branch("muonsTopMVA" +WPMap.at(m_type)+ "_index", &muonsTopMVAT_index);
    outTree->Branch("muonsTopMVA" +WPMap.at(m_type)+ "_topMVAScore", &muonsTopMVAT_topMVAScore);
    outTree->Branch("muonsTopMVA" +WPMap.at(m_type)+ "_genPartFlav", &muonsTopMVAT_genPartFlav);
    if(m_type==1){
        outTree->Branch("muonsTopMVAF_isTight", &muonsTopMVAF_isTight);
        outTree->Branch("muonsTopMVAF_ptConeCorreted", &muonsTopMVAF_ptConeCorreted);
    }

    // set up xgboost booster
    // TString baseDir = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelectionOptimized/";
    // TString baseDir = "/workfs2/cms/huahuil/4topCode/CMSSW_10_6_20/src/FourTop/objectSelectionOptimized/";
    TString baseDir = "./";
    TString muWeight = baseDir + TopMVALeptonMap[era].at(1);
    std::cout << "muWeight: " << muWeight << "\n";
    // BoosterHandle booster;
    XGBoosterCreate(NULL, 0, &m_booster[0]);
    XGBoosterLoadModel(m_booster[0], muWeight.Data());
    std::cout << "Done MuTopMVASel initialization......\n\n";
};

MuTopMVASel::~MuTopMVASel()
{
    XGBoosterFree(m_booster[0]);
};

void MuTopMVASel::Select(const eventForNano *e)
{
    clearBranch();
    // SS of TTTT: 0 for Loose; 2 tight; 1: fake
    // POG: 5: loose
    Double_t topLeptonScore = -99.;
    for (UInt_t j = 0; j < e->Muon_pt.GetSize(); ++j)
    {
        //dealing with differences of nanoAODv9 and nanoAODv12
        Int_t iMu_jetIdx = m_isRun3? std::any_cast<Short_t>(e->Muon_jetIdx.at(j)): std::any_cast<Int_t>(e->Muon_jetIdx.at(j));
        Int_t iMu_tightCharge = m_isRun3? std::any_cast<UChar_t>(e->Muon_tightCharge.at(j)): std::any_cast<Int_t>(e->Muon_tightCharge.at(j));

        if (!(e->Muon_pt.At(j) > 10))
            continue;
        if (!(fabs(e->Muon_eta.At(j)) < 2.4))
            continue;
        if (m_type == 5)
        {
            if (!e->Muon_looseId.At(j))
                continue;
        }
        if (m_type == 0 || m_type == 2|| m_type == 1)
        {

            if (!(fabs(e->Muon_dxy.At(j)) < 0.05))
                continue;
            if (!(fabs(e->Muon_dz.At(j)) < 0.1))
                continue;
            if (!(e->Muon_ip3d.At(j) < 8))
                continue;
            // Iso
            if (!(e->Muon_miniPFRelIso_all.At(j < 0.4)))
                continue;
            // ID
            if (!e->Muon_mediumId.At(j))
                continue;
        }
        if (m_type == 2|| m_type == 1)
        {
            Float_t jetPtRatio = 1. / (e->Muon_jetRelIso[j] + 1.);
            Float_t jetBTag = e->Jet_btagDeepFlavB[iMu_jetIdx];
            std::map<TString, Float_t> inputFeatures = {
                {"pt", e->Muon_pt[j]},
                {"eta", e->Muon_eta[j]},
                {"jetNDauCharged", e->Muon_jetNDauCharged[j]}, // number of charged daughters of the closest jet
                {"miniPFRelIso_chg", e->Muon_miniPFRelIso_chg[j]},
                {"miniPFRelIso_all", e->Muon_miniPFRelIso_all[j]},
                {"jetPtRelv2", e->Muon_jetPtRelv2[j]},         // Relative momentum of the lepton with respect to the closest jet after subtracting the lepton;
                {"jetPtRatio", jetPtRatio},                    // ; Ratio between the lepton and jet transverse momenta
                {"pfRelIso03_all", e->Muon_pfRelIso03_all[j]}, // 44
                {"jetBTag", jetBTag},
                {"sip3d", e->Muon_sip3d[j]},
                {"dxy", e->Muon_dxy[j]},
                {"dz", e->Muon_dz[j]},
                {"mvaFall17V2noIso", e->Muon_segmentComp[j]},
            }; // Compatibility of track segments in the muon system with the expected pattern of a minimum ionizing particle
            topLeptonScore = OS::TopLeptonEvaluate(inputFeatures, m_booster[0]);
            Bool_t isTight = topLeptonScore > 0.64;
            
            if(m_type==2){
                if (!(isTight))                continue;
            }else if(m_type==1){
                Bool_t isFake = jetBTag < 0.025 && jetPtRatio>0.45;
                if (!(isFake || isTight)) continue;
                muonsTopMVAF_isTight.push_back(isTight);
                muonsTopMVAF_ptConeCorreted.push_back(e->Muon_pt[j] * jetPtRatio);
            }
        }

        muonsTopMVAT_pt.push_back(e->Muon_pt.At(j));
        muonsTopMVAT_eta.push_back(e->Muon_eta.At(j));
        muonsTopMVAT_phi.push_back(e->Muon_phi.At(j));
        muonsTopMVAT_mass.push_back(e->Muon_mass.At(j));
        muonsTopMVAT_charge.push_back(e->Muon_charge.At(j));
        muonsTopMVAT_topMVAScore.push_back(topLeptonScore);
        if(!m_isData){
            muonsTopMVAT_genPartFlav.push_back(e->Muon_genPartFlav->At(j));
        }
    }
};

void MuTopMVASel::clearBranch()
{
    muonsTopMVAT_pt.clear();
    muonsTopMVAT_eta.clear();
    muonsTopMVAT_phi.clear();
    muonsTopMVAT_mass.clear();
    muonsTopMVAT_charge.clear();
    muonsTopMVAT_genPartFlav.clear();
    muonsTopMVAT_topMVAScore.clear();
    muonsTopMVAF_isTight.clear();
    muonsTopMVAF_ptConeCorreted.clear();
};

std::vector<Double_t> &MuTopMVASel::getEtaVec()
{
    return muonsTopMVAT_eta;
};
std::vector<Double_t> &MuTopMVASel::getPhiVec()
{
    return muonsTopMVAT_phi;
};

Int_t MuTopMVASel::getSize()
{
    return muonsTopMVAT_pt.size();
};
