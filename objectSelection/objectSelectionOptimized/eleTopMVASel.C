#include "eleTopMVASel.h"


    EleTopMVASel::EleTopMVASel(TTree *outTree, const TString era, const Int_t type) : m_type{type}
    { // type for different electrons
        std::cout << "Initializing EleTopMVASel......\n";
        outTree->Branch("elesTopMVAT_pt", &elesTopMVAT_pt);
        outTree->Branch("elesTopMVAT_eta", &elesTopMVAT_eta);
        outTree->Branch("elesTopMVAT_phi", &elesTopMVAT_phi);
        outTree->Branch("elesTopMVAT_mass", &elesTopMVAT_mass);
        outTree->Branch("elesTopMVAT_index", &elesTopMVAT_index);
        outTree->Branch("elesTopMVAT_topMVAScore", &elesTopMVAT_topMVAScore);
        // outTree->Branch("elesTopMVAT_", &elesTopMVAT_);
        
        // set up xgboost booster
        TString eleWeight = TopMVALeptonMap[era].at(0);
        // TString muWeight = TopMVALeptonMap[era].at(1);
        std::cout << "eleWeight: " << eleWeight << "\n";
        // BoosterHandle booster;
        XGBoosterCreate(NULL, 0, &m_booster[0]);
        XGBoosterLoadModel(m_booster[0], eleWeight.Data());
        // XGBoosterCreate(NULL, 0, &m_booster[1]);
        // XGBoosterLoadModel(m_booster[1], muWeight.Data());
        std::cout << "Done EleTopMVASel initialization......\n";
    };

    EleTopMVASel::~EleTopMVASel(){
        XGBoosterFree(m_booster[0]);
        // XGBoosterFree(m_booster[1]);
    };

    void EleTopMVASel::Select(const eventForNano *e)
    {
        clearBranch();
        // 0: loose, 2: tight;
        // POG: 4: veto; 5:POG loose
        for (UInt_t j = 0; j < e->Electron_pt.GetSize(); ++j)
        {
            Double_t pt = e->Electron_pt.At(j);
            Double_t eta = e->Electron_eta.At(j);
            Double_t topMVAScore = -99.;
            if (!(fabs(eta) < 2.5))
                continue;
            if (!(pt > 10))
                continue;
            if (m_type == 5)
            {
                if (!(e->Electron_cutBased[j] >= 2)) // cut-based ID Fall17 V2 (0:fail, 1:veto, 2:loose, 3:medium, 4:tight)
                    continue;
            }
            if (m_type == 4)
            {
                if (!(e->Electron_cutBased[j] >= 1)) // cut-based ID Fall17 V2 (0:fail, 1:veto, 2:loose, 3:medium, 4:tight)
                    continue;
            }
            if (m_type == 0 || m_type == 2)
            {
                // IP
                if (!(fabs(e->Electron_dxy.At(j)) < 0.05))
                    continue;
                if (!(fabs(e->Electron_dz.At(j)) < 0.1))
                    continue;
                if (!((e->Electron_ip3d.At(j)) < 8))
                    continue;
                // Iso
                if (!(e->Electron_miniPFRelIso_all.At(j) < 0.4)) // mini PF relative isolation, total (with scaled rho*EA PU corrections)
                    continue;

                if (!(int(e->Electron_lostHits.At(j)) < 1))
                    continue;
            }
            if (m_type == 2)
            {
                if (!e->Electron_convVeto.At(j))
                    continue;                             // the number of missing pixel hits and a conversion veto based on the vertex fit probability. To reject electrons originating from photon conversion
                if (!(e->Electron_tightCharge.At(j) > 0)) //??? Tight charge criteria (0:none, 1:isGsfScPixChargeConsistent, 2:isGsfCtfScPixChargeConsistent)
                    continue;
                // TOP UL Lepton MVA
                Float_t jetPtRatio = 1. / (e->Electron_jetRelIso[j] + 1.);
                // Float_t jetBTag = Jet_btagDeepB[e->Electron_jetIdx[j]];
                Float_t jetBTag = e->Jet_btagDeepFlavB[e->Electron_jetIdx[j]];
                std::map<TString, Float_t> inputFeatures = {
                    {"pt", e->Electron_pt[j]},
                    {"eta", e->Electron_eta[j]},
                    {"jetNDauCharged", e->Electron_jetNDauCharged.At(j)},
                    {"miniPFRelIso_chg", e->Electron_miniPFRelIso_chg[j]},
                    {"miniPFRelIso_all", e->Electron_miniPFRelIso_all[j]},
                    {"jetPtRelv2", e->Electron_jetPtRelv2[j]},
                    {"jetPtRatio", jetPtRatio},
                    {"pfRelIso03_all", e->Electron_pfRelIso03_all[j]},
                    {"jetBTag", jetBTag},
                    {"sip3d", e->Electron_sip3d[j]},
                    {"dxy", e->Electron_dxy[j]},
                    {"dz", e->Electron_dz[j]},
                    {"mvaFall17V2noIso", e->Electron_mvaFall17V2noIso[j]}};
                topMVAScore = TopLeptonEvaluate(inputFeatures, m_booster[0]);
                if (!(topMVAScore > 0.81))
                    continue;
            }

            // ROOT::Math::PtEtaPhiMVector electron(e->Electron_pt.At(j), e->Electron_eta.At(j), e->Electron_phi.At(j), Electron_mass.At(j));
            // SelectedElectrons.push_back(electron);
            // SelectedElectronsIndex.push_back(j);
            // SelectedEleTopMVAScore.push_back(topMVAScore);
            elesTopMVAT_pt.push_back(e->Electron_pt.At(j));
            elesTopMVAT_eta.push_back(e->Electron_eta.At(j));
            elesTopMVAT_phi.push_back(e->Electron_phi.At(j));
            elesTopMVAT_mass.push_back(e->Electron_mass.At(j));
            elesTopMVAT_index.push_back(j);
            elesTopMVAT_topMVAScore.push_back(topMVAScore);
        } //
    };

    void EleTopMVASel::clearBranch()
    {
        elesTopMVAT_pt.clear();
        elesTopMVAT_eta.clear();
        elesTopMVAT_phi.clear();
        elesTopMVAT_mass.clear();
        elesTopMVAT_index.clear();
        elesTopMVAT_topMVAScore.clear();
    };

