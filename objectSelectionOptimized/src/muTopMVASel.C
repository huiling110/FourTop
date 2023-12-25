#include "../include/muTopMVASel.h"

MuTopMVASel::MuTopMVASel(TTree *outTree, const TString era, const Int_t m_type) : m_type{m_type}
{ // m_type for different electrons
    std::cout << "Initializing MuTopMVASel......\n";
    outTree->Branch("muonsTopMVAT_pt", &muonsTopMVAT_pt);
    outTree->Branch("muonsTopMVAT_eta", &muonsTopMVAT_eta);
    outTree->Branch("muonsTopMVAT_phi", &muonsTopMVAT_phi);
    outTree->Branch("muonsTopMVAT_mass", &muonsTopMVAT_mass);
    outTree->Branch("muonsTopMVAT_index", &muonsTopMVAT_index);
    outTree->Branch("muonsTopMVAT_topMVAScore", &muonsTopMVAT_topMVAScore);
    // outTree->Branch("muonsTopMVAT_", &muonsTopMVAT_);

    // set up xgboost booster
    TString baseDir = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelectionOptimized/";
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
    // SS of TTTT: 0 for Loose; 2 tight
    // POG: 5: loose
    Double_t topLeptonScore = -99.;
    for (UInt_t j = 0; j < e->Muon_pt.GetSize(); ++j)
    {
        if (!(e->Muon_pt.At(j) > 10))
            continue;
        if (!(fabs(e->Muon_eta.At(j)) < 2.4))
            continue;
        if (m_type == 5)
        {
            if (!e->Muon_looseId.At(j))
                continue;
        }
        if (m_type == 0 || m_type == 2)
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
        if (m_type == 2)
        {
            Float_t jetPtRatio = 1. / (e->Muon_jetRelIso[j] + 1.);
            // Float_t jetBTag = e->Jet_btagDeepFlavB[e->Muon_jetIdx[j]];//!!!
            Float_t jetBTag = 0.4;
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
            if (!(topLeptonScore > 0.64))
                continue;
        }

        muonsTopMVAT_pt.push_back(e->Muon_pt.At(j));
        muonsTopMVAT_eta.push_back(e->Muon_eta.At(j));
        muonsTopMVAT_phi.push_back(e->Muon_phi.At(j));
        muonsTopMVAT_mass.push_back(e->Muon_mass.At(j));
        muonsTopMVAT_index.push_back(j);
        muonsTopMVAT_topMVAScore.push_back(topLeptonScore);
    }
};

void MuTopMVASel::clearBranch()
{
    muonsTopMVAT_pt.clear();
    muonsTopMVAT_eta.clear();
    muonsTopMVAT_phi.clear();
    muonsTopMVAT_mass.clear();
    muonsTopMVAT_index.clear();
    muonsTopMVAT_topMVAScore.clear();
};

std::vector<Double_t> &MuTopMVASel::getEtaVec()
{
    return muonsTopMVAT_eta;
};
std::vector<Double_t> &MuTopMVASel::getPhiVec()
{
    return muonsTopMVAT_phi;
};
