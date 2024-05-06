#include <TFile.h>
#include <TCanvas.h>


#include "../include/weightVarMaker.h"
#include "../include/variablesFunctions.h"
#include "../include/inputMap_MV.h"
#include "../../myLibrary/commenFunction.h"

WeightVarMaker::WeightVarMaker(TTree *outTree, TString era, Bool_t isData, const Bool_t isRun3): m_era{era}, m_isData{isData}, m_isRun3{isRun3}
{
    std::cout << "Initializing WeightVarMaker.....\n";
    std::cout<<"m_era="<<m_era<<" m_isData="<<m_isData<<" m_isRun3="<<m_isRun3<<"\n";

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
    outTree->Branch("tauT_IDSF_weight_new", &tauT_IDSF_weight_new);
    outTree->Branch("tauTT_IDSF_weight_new", &tauTT_IDSF_weight_new);
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
    //
    outTree->Branch("btagWPMedium_weight", &btagWPMedium_weight);
    outTree->Branch("btagWPMedium_weight_up", &btagWPMedium_weight_up);
    outTree->Branch("btagWPMedium_weight_down", &btagWPMedium_weight_down);

    outTree->Branch("HLT_weight", &HLT_weight);
    outTree->Branch("HLT_weight_stats_up", &HLT_weight_stats_up);
    outTree->Branch("HLT_weight_stats_down", &HLT_weight_stats_down);
    outTree->Branch("FR_weight", &FR_weight);

    //theory weight
    outTree->Branch("pdfWeight_up_", &pdfWeight_up_);
    outTree->Branch("pdfWeight_down_", &pdfWeight_down_);
    outTree->Branch("pdfWeightAlphaS_up_", &pdfWeightAlphaS_up_);
    outTree->Branch("pdfWeightAlphaS_down_", &pdfWeightAlphaS_down_);
    outTree->Branch("scaleWeight_up_", &scaleWeight_up_);
    outTree->Branch("scaleWeight_down_", &scaleWeight_down_);
    outTree->Branch("scaleWeightRe_up_", &scaleWeightRe_up_);
    outTree->Branch("scaleWeightRe_down_", &scaleWeightRe_down_);
    outTree->Branch("scaleWeightFa_up_", &scaleWeightFa_up_);
    outTree->Branch("scaleWeightFa_down_", &scaleWeightFa_down_);

    // TOP Lepton MVA
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

    //muon 2022 SFs
    TString base = "../../jsonpog-integration/POG/";
    TString muonSF_json = base + MV::json_muon2022.at(m_era).at(0); 
    std::cout<<"muonSF low Pt json="<<muonSF_json<<"\n";
    std::cout<<"muonSF medium Pt json="<<base + MV::json_muon2022.at(m_era).at(1)<<"\n";
    std::cout<<"muonSF high Pt json="<<base + MV::json_muon2022.at(m_era).at(2)<<"\n";
    cset_muonLPt = correction::CorrectionSet::from_file( (base + MV::json_muon2022.at(m_era).at(0)).Data()); 
    cset_muonMPt = correction::CorrectionSet::from_file( (base + MV::json_muon2022.at(m_era).at(1)).Data()); 
    cset_muonHPt = correction::CorrectionSet::from_file( (base + MV::json_muon2022.at(m_era).at(2)).Data()); 
    std::cout << "\n";
    // for (auto &corr : *cset_muonLPt)  
    // {
    //     printf("Correction: %s\n", corr.first.c_str());
    // }
    // std::cout << "\n";
    // for (auto &corr : *cset_muonMPt)
    // {
    //     printf("Correction: %s\n", corr.first.c_str());
    // }
    // for (auto &corr : *cset_muonHPt)  
    // {
    //     printf("Correction: %s\n", corr.first.c_str());
    // }

    // new SF files from
    TString tauSF_json = base + MV::json_map.at(m_era).at(1);
    TString btagSF_json = base + MV::json_map.at(m_era).at(2);
    std::cout<<"tauSF json="<<tauSF_json<<"\n";
    std::cout << "btagSF_json=" << btagSF_json << "\n";
    cset = correction::CorrectionSet::from_file(tauSF_json.Data());//for tau
    cset_btag = correction::CorrectionSet::from_file(btagSF_json.Data());
    // for (auto &corr : *cset)  
    // {
    //     printf("Correction: %s\n", corr.first.c_str());
    // }
    // for (auto &corr : *cset_btag)
    // {
    //     printf("Correction: %s\n", corr.first.c_str());
    // }
    // btagR files
    btagRHist = TTTT::getHistogramFromFile<TH1D>(MV::btagR_map.at(m_era), "btagR");
    std::cout << "b tag R file used: " << MV::btagR_map.at(m_era) << "\n";

    //btag WP efficieny files
    btagEffHist_b = TTTT::getHistogramFromFile<TH2D>(MV::btagWPEff_map.at(m_era), "jets_ptEta_genB");
    std::cout << "b tag WP file used: " << MV::btagWPEff_map.at(m_era) << "\n";
    TString btagEff_b = MV::btagWPEff_map.at(m_era);
    TString btagEff_c = btagEff_b.ReplaceAll("bEff_B", "bEff_C");
    TString btagEff_l = btagEff_b.ReplaceAll("bEff_C", "bEff_L");
    btagEffHist_c = TTTT::getHistogramFromFile<TH2D>(btagEff_c, "jets_ptEta_genC");
    btagEffHist_l = TTTT::getHistogramFromFile<TH2D>(btagEff_l, "jets_ptEta_genL");
    btagEffHist_b->Print();
    btagEffHist_c->Print();
    btagEffHist_l->Print();
    std::cout<<"\n";

    // trigger
    TString trigger1b = MV::triggerSF_map.at(m_era);
    triggerHist1b = TTTT::getHistogramFromFile<TH2D>(trigger1b, "singleMu_SF");
    TString triggerSFName2b = trigger1b.ReplaceAll("1b", "2b");
    triggerHist2b = TTTT::getHistogramFromFile<TH2D>(triggerSFName2b, "singleMu_SF");
    TString triggerSFName3b = triggerSFName2b.ReplaceAll("2b_", "3b_");
    triggerHist3b = TTTT::getHistogramFromFile<TH2D>(triggerSFName3b, "singleMu_SF");
    std::cout << "getting 1b trigger SF file: " << trigger1b << "\n";


        //get FR
        TFile* file=new TFile("/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_v0FR_measure1prong_jetEta/results/fakeRateInPtEta.root", "READ"); 
        TFile* file3Prong=new TFile("/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_v0FR_measureNot1prong_jetEta/results/fakeRateInPtEta.root", "READ"); 
        std::cout<<"FR files used: "<<file->GetName()<<"\n"<<file3Prong->GetName()<<"\n";
        // Assuming these graphs are already created and stored in the ROOT file
        m_graphs.emplace_back(0.0, 0.8, 1, dynamic_cast<TGraphAsymmErrors*>(file->Get("fakeRate_Eta1")));
        m_graphs.emplace_back(0.8, 1.5, 1, dynamic_cast<TGraphAsymmErrors*>(file->Get("fakeRate_Eta2")));
        m_graphs.emplace_back(1.5, 2.7, 1, dynamic_cast<TGraphAsymmErrors*>(file->Get("fakeRate_Eta3")));
        m_graphs.emplace_back(0.0, 0.8, 3, dynamic_cast<TGraphAsymmErrors*>(file3Prong->Get("fakeRate_Eta1"))); //!3 is not 3 but not 1
        m_graphs.emplace_back(0.8, 1.5, 3, dynamic_cast<TGraphAsymmErrors*>(file3Prong->Get("fakeRate_Eta2")));
        m_graphs.emplace_back(1.5, 2.7, 3, dynamic_cast<TGraphAsymmErrors*>(file3Prong->Get("fakeRate_Eta3")));



    std::cout << "Done initializing ............\n";
    std::cout << "\n";
};

void WeightVarMaker::makeVariables(EventForMV *e, const Double_t jets_HT, const Double_t jets_6pt, const Int_t bjetsM_num)
{
    reportEntry("WeightVarMaker::makeVariables()");
    // clearBranch();
    //!!! to be done
    EVENT_prefireWeight = *e->EVENT_prefireWeight_;
    EVENT_prefireWeight_up = *e->EVENT_prefireWeight_up_;
    EVENT_prefireWeight_down = *e->EVENT_prefireWeight_down_;
    EVENT_genWeight = *e->EVENT_genWeight_;
    PUweight_ = *e->PUWeight;
    PUweight_up_ = *e->PUWeight_up;
    PUweight_down_ = *e->PUWeight_down;

    //copy
    pdfWeight_up_ = *e->pdfWeight_up;
    pdfWeight_down_ = *e->pdfWeight_down;
    pdfWeightAlphaS_up_ = *e->pdfWeightAlphaS_up;
    pdfWeightAlphaS_down_ = *e->pdfWeightAlphaS_down;
    scaleWeight_up_ = *e->scaleWeight_up;
    scaleWeight_down_ = *e->scaleWeight_down;
    scaleWeightRe_up_ = *e->scaleWeightRe_up;
    scaleWeightRe_down_ = *e->scaleWeightRe_down;
    scaleWeightFa_up_ = *e->scaleWeightFa_up;
    scaleWeightFa_down_ = *e->scaleWeightFa_down;

    // lepton SF for top mva leptons
    elesTopMVAT_weight = calMuonIDSF(e->elesTopMVAT_pt, e->elesTopMVAT_eta, eleIDSF_topMVA, 0, kFALSE, m_isData); //muon pt and eta
    elesTopMVAT_weight_up = calMuonIDSF(e->elesTopMVAT_pt, e->elesTopMVAT_eta, eleIDSF_topMVA, 1, kFALSE, m_isData);
    elesTopMVAT_weight_down = calMuonIDSF(e->elesTopMVAT_pt, e->elesTopMVAT_eta, eleIDSF_topMVA, 2, kFALSE, m_isData);
    musTopMVAT_weight = calMuonIDSF(e->muonsTopMVAT_pt, e->muonsTopMVAT_eta, muIDSF_topMVA, 0, kTRUE, m_isData);
    musTopMVAT_weight_up = calMuonIDSF(e->muonsTopMVAT_pt, e->muonsTopMVAT_eta, muIDSF_topMVA, 1, kTRUE, m_isData);
    musTopMVAT_weight_down = calMuonIDSF(e->muonsTopMVAT_pt, e->muonsTopMVAT_eta, muIDSF_topMVA, 2, kTRUE, m_isData);
    //!!!normal leptons
    eleMVAT_IDSF_weight = calMuonIDSF(e->elesMVAT_pt, e->elesMVAT_eta, eleIDSF_topMVA, 0, kFALSE, m_isData);
    eleMVAT_IDSF_weight_up = calMuonIDSF(e->elesMVAT_pt, e->elesMVAT_eta, eleIDSF_topMVA, 1, kFALSE, m_isData);
    eleMVAT_IDSF_weight_down = calMuonIDSF(e->elesMVAT_pt, e->elesMVAT_eta, eleIDSF_topMVA, 2, kFALSE, m_isData);

    //sf for run3 muonPOG ID and ISO        
    //!!!suspect this is causing the run time error:  what():  Index above bounds in Binning for input argument 1 value: 1064.129272
    muonIDSF_weight = calMuonIDSF_json(e->muonsT_eta, e->muonsT_pt, cset_muonLPt.get(), cset_muonMPt.get(), cset_muonHPt.get(), 0, m_isData);//!!!check input muon collection
    muonIDSF_weight_up = calMuonIDSF_json(e->muonsT_eta, e->muonsT_pt, cset_muonLPt.get(), cset_muonMPt.get(), cset_muonHPt.get(), 1, m_isData);//!!!check input muon collection
    muonIDSF_weight_down = calMuonIDSF_json(e->muonsT_eta, e->muonsT_pt, cset_muonLPt.get(), cset_muonMPt.get(), cset_muonHPt.get(), 2, m_isData);//!!!check input muon collection

    tauT_IDSF_weight_new = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "nom", "nom", "nom",  "Medium", m_isData, m_isRun3);
    tauT_IDSF_weight_new_vsjet_up = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "up", "nom", "nom", "Medium", m_isData, m_isRun3);
    tauT_IDSF_weight_new_vsjet_down = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "down", "nom", "nom", "Medium", m_isData, m_isRun3);
    tauT_IDSF_weight_new_vsmu_up = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "nom", "up", "nom", "Medium", m_isData, m_isRun3);
    tauT_IDSF_weight_new_vsmu_down = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "nom", "down", "nom", "Medium", m_isData, m_isRun3);
    tauT_IDSF_weight_new_vsele_up = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "nom", "nom", "up", "Medium", m_isData, m_isRun3);
    tauT_IDSF_weight_new_vsele_down = calTau_IDSF_new(e->tausT_pt, e->tausT_eta, e->tausT_decayMode, e->tausT_genPartFlav, cset.get(), "nom", "nom", "down", "Medium", m_isData, m_isRun3);
    tauTT_IDSF_weight_new = calTau_IDSF_new(e->tausTT_pt, e->tausTT_eta, e->tausTT_decayMode, e->tausTT_genPartFlav, cset.get(), "nom", "nom", "nom",  "Tight", m_isData, m_isRun3);

    // TTreeReaderArray<Double_t>& jets_btags = (m_isRun3) ? e->jets_btags : e->jets_btagsPT;
    TTreeReaderArray<Double_t>& jets_btags = (m_isRun3) ? e->jets_btagsPT : e->jets_btags;
    btagShape_weight = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "central");
    btagShape_weight_jes_up = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_jes");
    btagShape_weight_jes_down = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_jes");
    btagShape_weight_lf_up = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_lf");
    btagShape_weight_lf_down = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_lf");
    btagShape_weight_hf_up = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_hf");
    btagShape_weight_hf_down = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_hf");
    btagShape_weight_hfstats1_up = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_hfstats1");
    btagShape_weight_hfstats1_down = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_hfstats1");
    btagShape_weight_hfstats2_up = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_hfstats2");
    btagShape_weight_hfstats2_down = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_hfstats2");
    btagShape_weight_lfstats1_up = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_lfstats1");
    btagShape_weight_lfstats1_down = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_lfstats1");
    btagShape_weight_lfstats2_up = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_lfstats2");
    btagShape_weight_lfstats2_down = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_lfstats2");
    btagShape_weight_cferr1_up = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_cferr1");
    btagShape_weight_cferr1_down = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_cferr1");
    btagShape_weight_cferr2_up = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "up_cferr2");
    btagShape_weight_cferr2_down = calBtagShapeWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), m_isData, "down_cferr2");
    btagShapeR = calBtagR(e->jets_pt.GetSize(), btagRHist);

    //btag WorkingPoint
    btagWPMedium_weight = calBtagWPMWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), btagEffHist_b, btagEffHist_c, btagEffHist_l, m_isData, m_era, "central", m_isRun3);
    btagWPMedium_weight_up = calBtagWPMWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), btagEffHist_b, btagEffHist_c, btagEffHist_l, m_isData, m_era, "up", m_isRun3) ;
    btagWPMedium_weight_down = calBtagWPMWeight(e->jets_pt, e->jets_eta, e->jets_flavour, jets_btags, cset_btag.get(), btagEffHist_b, btagEffHist_c, btagEffHist_l, m_isData, m_era, "down", m_isRun3) ;

    HLT_weight = HLTWeightCal(jets_HT, jets_6pt, bjetsM_num, triggerHist1b, triggerHist2b, triggerHist3b, m_isData, 0);
    HLT_weight_stats_up = HLTWeightCal(jets_HT, jets_6pt, bjetsM_num, triggerHist1b, triggerHist2b, triggerHist3b, m_isData, 1);
    HLT_weight_stats_down = HLTWeightCal(jets_HT, jets_6pt, bjetsM_num, triggerHist1b, triggerHist2b, triggerHist3b, m_isData, 2);

    Bool_t ifFR = kFALSE;
    if(e->tausF_jetPt.GetSize()>0){
        Int_t tauProng =  e->tausF_decayMode.At(0)/5 + 1 ;
        tauProng = tauProng==1? 1 : 3;
        ifFR = TTTT::getFRandError(m_graphs, e->tausF_jetEta.At(0), tauProng, e->tausF_jetPt.At(0), FR_weight, FR_weight_up, FR_weight_down);
    }
    // std::cout<<"FR_weight="<<FR_weight<<" FR_weight_up="<<FR_weight_up<<" FR_weight_down="<<FR_weight_down<<"\n";
    FR_weight = FR_weight / (1. - FR_weight);
    FR_weight = ifFR? FR_weight : -99; 


};

void WeightVarMaker::clearBranch()
{ //??? derived class should also have a clearBranch()
};

void WeightVarMaker::reportEntry(TString className){
    if(m_entry==0){
        std::cout<<"running "<<className<<"\n";
    }
    m_entry++;
}

WeightVarMaker::~WeightVarMaker(){};