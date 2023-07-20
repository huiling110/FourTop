#include <TFile.h>
#include <TCanvas.h>


#include "../include/weightVarMaker.h"
#include "../include/variablesFunctions.h"
#include "../include/inputMap_MV.h"
#include "../../myLibrary/commenFunction.h"

WeightVarMaker::WeightVarMaker(TTree *outTree, TString era, Bool_t isData): m_era{era}, m_isData{isData}
{
    std::cout << "Initializing WeightVarMaker.....\n";

    outTree->Branch("EVENT_prefireWeight", &EVENT_prefireWeight);
    outTree->Branch("EVENT_prefireWeight_up", &EVENT_prefireWeight_up);
    outTree->Branch("EVENT_prefireWeight_down", &EVENT_prefireWeight_down);
    outTree->Branch("EVENT_genWeight", &EVENT_genWeight);
    outTree->Branch("PUweight_", &PUweight_);
    outTree->Branch("PUweight_up_", &PUweight_up_);
    outTree->Branch("PUweight_down_", &PUweight_down_);
    outTree->Branch("btagEfficiency_weight", &btagEfficiency_weight);
    outTree->Branch("muonIDSF_weight", &muonIDSF_weight);
    outTree->Branch("muonIDSF_weight_up", &muonIDSF_weight_up);
    outTree->Branch("muonIDSF_weight_down", &muonIDSF_weight_down);
    outTree->Branch("mounTrackerSF_weight", &mounTrackerSF_weight);
    outTree->Branch("eleMVAT_IDSF_weight", &eleMVAT_IDSF_weight);
    outTree->Branch("eleMVAT_IDSF_weight_up", &eleMVAT_IDSF_weight_up);
    outTree->Branch("eleMVAT_IDSF_weight_down", &eleMVAT_IDSF_weight_down);
    outTree->Branch("eleMVAT_IDSF_weight_backup", &eleMVAT_IDSF_weight_backup);
    outTree->Branch("elesTopMVAT_weight", &elesTopMVAT_weight);
    outTree->Branch("elesTopMVAT_weight_up", &elesTopMVAT_weight_up);
    outTree->Branch("elesTopMVAT_weight_down", &elesTopMVAT_weight_down);
    outTree->Branch("musTopMVAT_weight", &musTopMVAT_weight);
    outTree->Branch("musTopMVAT_weight_up", &musTopMVAT_weight_up);
    outTree->Branch("musTopMVAT_weight_down", &musTopMVAT_weight_down);
    outTree->Branch("tauT_IDSF_weight", &tauT_IDSF_weight);
    outTree->Branch("tauT_IDSF_weight_new", &tauT_IDSF_weight_new);
    outTree->Branch("tauT_IDSF_weight_new_vsjet_up", &tauT_IDSF_weight_new_vsjet_up);
    outTree->Branch("tauT_IDSF_weight_new_vsjet_down", &tauT_IDSF_weight_new_vsjet_down);
    outTree->Branch("tauT_IDSF_weight_new_vsmu_up", &tauT_IDSF_weight_new_vsmu_up);
    outTree->Branch("tauT_IDSF_weight_new_vsmu_down", &tauT_IDSF_weight_new_vsmu_down);
    outTree->Branch("tauT_IDSF_weight_new_vsele_up", &tauT_IDSF_weight_new_vsele_up);
    outTree->Branch("tauT_IDSF_weight_new_vsele_down", &tauT_IDSF_weight_new_vsele_down);
    outTree->Branch("btagShape_weight", &btagShape_weight);

    outTree->Branch("btagShape_weight_jes_up", &btagShape_weight_jes_up);
    outTree->Branch("btagShape_weight_jes_down", &btagShape_weight_jes_down);
    outTree->Branch("btagShape_weight_hf_up", &btagShape_weight_hf_up);
    outTree->Branch("btagShape_weight_hf_down", &btagShape_weight_hf_down);
    outTree->Branch("btagShape_weight_lf_up", &btagShape_weight_lf_up);
    outTree->Branch("btagShape_weight_lf_down", &btagShape_weight_lf_down);
    outTree->Branch("btagShape_weight_hfstats1_up", &btagShape_weight_hfstats1_up);
    outTree->Branch("btagShape_weight_hfstats1_down", &btagShape_weight_hfstats1_down);
    outTree->Branch("btagShape_weight_hfstats2_up", &btagShape_weight_hfstats2_up);
    outTree->Branch("btagShape_weight_hfstats2_down", &btagShape_weight_hfstats2_down);
    outTree->Branch("btagShape_weight_lfstats1_up", &btagShape_weight_lfstats1_up);
    outTree->Branch("btagShape_weight_lfstats1_down", &btagShape_weight_lfstats1_down);
    outTree->Branch("btagShape_weight_lfstats2_up", &btagShape_weight_lfstats2_up);
    outTree->Branch("btagShape_weight_lfstats2_down", &btagShape_weight_lfstats2_down);
    outTree->Branch("btagShape_weight_cferr1_up", &btagShape_weight_cferr1_up);
    outTree->Branch("btagShape_weight_cferr1_down", &btagShape_weight_cferr1_down);
    outTree->Branch("btagShape_weight_cferr2_up", &btagShape_weight_cferr2_up);
    outTree->Branch("btagShape_weight_cferr2_down", &btagShape_weight_cferr2_down);

    outTree->Branch("btagShapeR", &btagShapeR);
    outTree->Branch("HLT_weight", &HLT_weight);
    outTree->Branch("HLT_weight_stats_up", &HLT_weight_stats_up);
    outTree->Branch("HLT_weight_stats_down", &HLT_weight_stats_down);


    // TOP Lepton MVA
    // TFile *eleIDSF_topMVAFile = new TFile((MV::topLeptonSF_files[m_era].at(0)), "READ");
    TFile *eleIDSF_topMVAFile = new TFile((MV::topLeptonSF_files.at(m_era).at(0)), "READ");
    std::cout << "top ele SF file used: " << eleIDSF_topMVAFile->GetName() << "\n";
    eleIDSF_topMVA = (TH2D *)eleIDSF_topMVAFile->Get("EGamma_SF2D");
    eleIDSF_topMVA->SetDirectory(nullptr);
    eleIDSF_topMVAFile->Close();
    delete eleIDSF_topMVAFile;
    TFile *muIDSF_topMVAFile = new TFile((MV::topLeptonSF_files.at(m_era).at(1)), "READ");
    std::cout << "top mu SF file used: " << muIDSF_topMVAFile->GetName() << "\n";
    TCanvas *canvas = (TCanvas *)muIDSF_topMVAFile->Get("cNUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt");
    // muIDSF_topMVA = (TH2D *)muIDSF_topMVAFile->Get("cNUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt");
    muIDSF_topMVA = (TH2D *)canvas->GetPrimitive("NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt");
    muIDSF_topMVA->Print();
    muIDSF_topMVA->SetDirectory(nullptr);
    muIDSF_topMVAFile->Close();
    delete muIDSF_topMVAFile;

    // new SF files from
    TString base = "../../jsonpog-integration/POG/";
    TString tauSF_json = base + MV::json_map.at(m_era).at(1);
    TString btagSF_json = base + MV::json_map.at(m_era).at(2);
    cset = correction::CorrectionSet::from_file(tauSF_json.Data());
    cset_btag = correction::CorrectionSet::from_file(btagSF_json.Data());
    for (auto &corr : *cset)
    {
        printf("Correction: %s\n", corr.first.c_str());
    }
    for (auto &corr : *cset_btag)
    {
        printf("Correction: %s\n", corr.first.c_str());
    }
    // btagR files
    btagRHist = TTTT::getHistogramFromFile(MV::btagR_map.at(m_era), "btagR");
    std::cout << "b tag R file used: " << MV::btagR_map.at(m_era) << "\n";

    std::cout << "Done initializing ............\n";
    std::cout << "\n";
};

void WeightVarMaker::makeVariables(EventForMV *e)
{
    // clearBranch();
    //!!! to be done
    EVENT_prefireWeight = *e->EVENT_prefireWeight_;
    EVENT_prefireWeight_up = *e->EVENT_prefireWeight_up_;
    EVENT_prefireWeight_down = *e->EVENT_prefireWeight_down_;
    EVENT_genWeight = *e->EVENT_genWeight_;
    PUweight_ = *e->PUWeight;
    PUweight_up_ = *e->PUWeight_up;
    PUweight_down_ = *e->PUWeight_down;

    // lepton SF for top mva leptons
    elesTopMVAT_weight = calMuonIDSF(e->elesTopMVAT_pt, e->elesTopMVAT_eta, eleIDSF_topMVA, 0, kFALSE, m_isData); //muon pt and eta
    elesTopMVAT_weight_up = calMuonIDSF(e->elesTopMVAT_pt, e->elesTopMVAT_eta, eleIDSF_topMVA, 1, kFALSE, m_isData);
    elesTopMVAT_weight_down = calMuonIDSF(e->elesTopMVAT_pt, e->elesTopMVAT_eta, eleIDSF_topMVA, 2, kFALSE, m_isData);
    musTopMVAT_weight = calMuonIDSF(e->muonsTopMVAT_pt, e->muonsTopMVAT_eta, muIDSF_topMVA, 0, kTRUE, m_isData);
    musTopMVAT_weight_up = calMuonIDSF(e->muonsTopMVAT_pt, e->muonsTopMVAT_eta, muIDSF_topMVA, 1, kTRUE, m_isData);
    musTopMVAT_weight_down = calMuonIDSF(e->muonsTopMVAT_pt, e->muonsTopMVAT_eta, muIDSF_topMVA, 2, kTRUE, m_isData);

    tauT_IDSF_weight_new = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "nom", "nom", "nom", m_isData);
    tauT_IDSF_weight_new_vsjet_up = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "up", "nom", "nom", m_isData);
    tauT_IDSF_weight_new_vsjet_down = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "down", "nom", "nom", m_isData);
    tauT_IDSF_weight_new_vsmu_up = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "nom", "up", "nom", m_isData);
    tauT_IDSF_weight_new_vsmu_down = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "nom", "down", "nom", m_isData);
    tauT_IDSF_weight_new_vsele_up = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "nom", "nom", "up", m_isData);
    tauT_IDSF_weight_new_vsele_down = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "nom", "nom", "down", m_isData);

    btagShape_weight = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, e->jets_btags, cset_btag.get(), m_isData, "central");
    // btagShape_weight_jes_up = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_jes");
    // btagShape_weight_jes_down = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_jes");
    // btagShape_weight_lf_up = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_lf");
    // btagShape_weight_lf_down = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_lf");
    // btagShape_weight_hf_up = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_hf");
    // btagShape_weight_hf_down = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_hf");
    // btagShape_weight_hfstats1_up = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_hfstats1");
    // btagShape_weight_hfstats1_down = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_hfstats1");
    // btagShape_weight_hfstats2_up = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_hfstats2");
    // btagShape_weight_hfstats2_down = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_hfstats2");
    // btagShape_weight_lfstats1_up = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_lfstats1");
    // btagShape_weight_lfstats1_down = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_lfstats1");
    // btagShape_weight_lfstats2_up = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_lfstats2");
    // btagShape_weight_lfstats2_down = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_lfstats2");
    // btagShape_weight_cferr1_up = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_cferr1");
    // btagShape_weight_cferr1_down = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_cferr1");
    // btagShape_weight_cferr2_up = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_cferr2");
    // btagShape_weight_cferr2_down = calBtagShapeWeight(jets, jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_cferr2");
    // btagShapeR = calBtagR(jets_number, btagRHist);



};

void WeightVarMaker::clearBranch()
{ //??? derived class should also have a clearBranch()
};


WeightVarMaker::~WeightVarMaker(){};