#ifndef INPUTMAP_MV_H
#define INPUTMAP_MV_H

namespace MV
{

    // top lepton mva
    inline const std::map<TString, std::array<TString, 2>> topLeptonSF_files = {
        // {"2016preVFP", {"./input/topMVASF/ele/2016APV/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2016HIPM/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
        // {"2016postVFP", {"./input/topMVASF/ele/2016/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2016/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
        // {"2017", {"./input/topMVASF/ele/2017/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2017/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
        // {"2018", {"./input/topMVASF/ele/2018/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2018/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
        {"2022preEE", {"./input/topMVASF/ele/2018/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2018/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},//!!!
        {"2022postEE", {"./input/ele2022SF/passingMVA122Xwp90isoV1/2022postEE/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2018/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},//!!!
        {"2018", {"./input/leptonSF_UL/egammaEffi.txt_EGM2D_TOPULMVA_UL2018.root", "./input/leptonSF_UL/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt_ALL_UL2018.root"}},
        {"2017", {"./input/leptonSF_UL/egammaEffi.txt_EGM2D_TOPULMVA_UL2017.root", "./input/leptonSF_UL/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt_ALL_UL2017.root"}},
        {"2016postVFP", {"./input/leptonSF_UL/egammaEffi.txt_EGM2D_TOPULMVA_UL2016PostVFP.root", "./input/leptonSF_UL/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt_ALL_UL2016PostVFP.root"}},
        {"2016preVFP", {"./input/leptonSF_UL/egammaEffi.txt_EGM2D_TOPULMVA_UL2016PreVFP.root", "./input/leptonSF_UL/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt_ALL_UL2016PreVFP.root"}},

    };

    inline const std::map<TString, TString> triggerSF_map = {
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2baslineNoHLT_v57ovelapWithTausF/mc/variableHists_v0_HLTSFMeasure/results/baseline1Muon1b_triggerSF.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baslineNoHLT_v57ovelapWithTausF/mc/variableHists_v0_HLTSFMeasure/results/baseline1Muon1b_triggerSF.root"},
        // {"2022preEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baslineNoHLT_v57ovelapWithTausF/mc/variableHists_v0_HLTSFMeasure/results/baseline1Muon1b_triggerSF.root"},
        // {"2022postEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baslineNoHLT_v57ovelapWithTausF/mc/variableHists_v0_HLTSFMeasure/results/baseline1Muon1b_triggerSF.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet45/results/baseline1Muon1b_triggerSF.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT600/results/baseline1Muon1b_triggerSF.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT600BinA/results/baseline1Muon1b_triggerSF.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT600BinD/results/baseline1Muon1b_triggerSF.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT600BinE/results/baseline1Muon1b_triggerSF.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinE/results/baseline1Muon1b_triggerSF.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/results/baseline1Muon1b_triggerSF.root"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/results/baseline1Muon1b_triggerSFTest.root"},
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/results/baseline1Muon1b_triggerSF_new.root"},
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/results/baseline1Muon1b_triggerSF_new.root"},
        {"2022postEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v3NotHLTPre/mc/variableHists_v0_HLTSFMeasure/results/baseline1Muon1b_triggerSF_v0.root"},
        {"2022preEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/results/baseline1Muon1b_triggerSF.root"},//!!!To be updated
        // {"2018", " /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Jet6pt32_v75NoHLTNoTauHT400Jet6pt30/mc/variableHists_v2HLT_6thjetPt34BinK/results/baseline1Muon1b_triggerSF_v0.root"},
        // {"2018", " /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Jet6pt32_v75NoHLTNoTauHT400Jet6pt30/mc/variableHists_v2HLT_6thjetPt34BinL/results/baseline1Muon1b_triggerSF_v0.root"},
        // {"2018", " /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Jet6pt32_v75NoHLTNoTauHT400Jet6pt30/mc/variableHists_v2HLT_6thjetPt34BinN/results/baseline1Muon1b_triggerSF_v0.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Jet6pt32_v75NoHLTNoTauHT400Jet6pt30/mc/variableHists_v3HLT_4bRegionBinZ/results/baseline1Muon4b_triggerSF_v0.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Jet6pt32_v75NoHLTNoTauHT400Jet6pt30/mc/variableHists_v4HLT_4bDifBinningDifBBinA/results/baseline1Muon4b_triggerSF_v0.root"}
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Jet6pt32_v75NoHLTNoTauHT400Jet6pt30/mc/variableHists_v4HLT_4bDifBinningDifBBinC/results/"}
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v77ForHLT/mc/variableHists_v0HLTMeasure/results/"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v77ForHLT/mc/variableHists_v1HLT_varyingCutOnBjetBinD/results/"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v79forHLT/mc/variableHists_v0HLTMeasure/results/"},
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v79forHLT/mc/variableHists_v0HLTMeasureBinB/results/"},//!!!
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v79forHLT/mc/
        //
        {"2018", "../inputFiles/triggerSF/2018/v0baselineHardro_v77ForHLT/mc/variableHists_v1HLT_varyingCutOnBjetBinD/results/"},
        {"2017", "../inputFiles/triggerSF/2017/v0baselineHardro_v79forHLT/mc/variableHists_v0HLTMeasure/results/"},
        {"2016preVFP", "../inputFiles/triggerSF/2016preVFP/v0baselineHardro_v79forHLT/mc/variableHists_v0HLTMeasureBinB/results/"},//!!!
        {"2016postVFP", "../inputFiles/triggerSF/2016postVFP/v0baselineHardro_v79forHLT/mc/variableHists_v0HLTMeasureBinB/results/"},//!!!
    };

    inline const std::map<TString, std::array<TString, 4>> json_map = {
        {"2016preVFP", {"JME/2016preVFP_UL/jet_jerc.json", "TAU/2016preVFP_UL/tau.json", "BTV/2016preVFP_UL/btagging.json", "EGM/2016preVFP_UL/electron.json"}},
        {"2016postVFP", {"JME/2016postVFP_UL/jet_jerc.json", "TAU/2016postVFP_UL/tau.json", "BTV/2016postVFP_UL/btagging.json", "EGM/2016postVFP_UL/electron.json"}},
        {"2017", {"JME/2017_UL/jet_jerc.json", "TAU/2017_UL/tau.json", "BTV/2017_UL/btagging.json", "EGM/2017_UL/electron.json"}},
        {"2018", {"JME/2018_UL/jet_jerc.json", "TAU/2018_UL/tau.json", "BTV/2018_UL/btagging.json", "EGM/2018_UL/electron.json"}},
        {"2022preEE", {"JME/2018_UL/jet_jerc.json", "../newRun3/TAU/2022_preEE/tau_DeepTau2018v2p5_2022_preEE.json", "BTV/2022_Summer22/btagging.json", "EGM/2018_UL/electron.json"}},
        {"2022postEE", {"JME/2018_UL/jet_jerc.json", "../newRun3/TAU/2022_postEE/tau_DeepTau2018v2p5_2022_postEE.json", "BTV/2022_Summer22EE/btagging.json", "EGM/2018_UL/electron.json"}},
    };

    inline const std::map<TString, std::array<TString, 3>> json_muon2022 = {
            {"2022postEE", {"MUO/2022EE_27Jun2023/muon_JPsi.json", "MUO/2022EE_27Jun2023/muon_Z.json", "MUO/2022EE_27Jun2023/muon_HighPt.json"}},
            {"2022preEE", {"MUO/2022_27Jun2023/muon_JPsi.json", "MUO/2022_27Jun2023/muon_Z.json", "MUO/2022_27Jun2023/muon_HighPt.json"}},
            // {"2022preEE", {"../newRun3/muonefficiencies/Run3/2022/2022_Jpsi/ScaleFactors_Muon_Jpsi_ID_2022_schemaV2.json", "../newRun3/muonefficiencies/Run3/2022/2022_Z/ScaleFactors_Muon_Z_ID_ISO_2022_schemaV2.json", "../newRun3/muonefficiencies/Run3/2022/2022_HighPt/ScaleFactors_Muon_highPt_IDISO_2022_schemaV2.json"}},
            {"2016preVFP", {"MUO/2022_27Jun2023/muon_JPsi.json", "MUO/2022_27Jun2023/muon_Z.json", "MUO/2022_27Jun2023/muon_HighPt.json"}},
            {"2016postVFP", {"MUO/2022_27Jun2023/muon_JPsi.json", "MUO/2022_27Jun2023/muon_Z.json", "MUO/2022_27Jun2023/muon_HighPt.json"}},
            {"2017", {"MUO/2022_27Jun2023/muon_JPsi.json", "MUO/2022_27Jun2023/muon_Z.json", "MUO/2022_27Jun2023/muon_HighPt.json"}},
            {"2018", {"MUO/2022_27Jun2023/muon_JPsi.json", "MUO/2022_27Jun2023/muon_Z.json", "MUO/2022_27Jun2023/muon_HighPt.json"}},
        };

    inline const std::map<TString, TString> btagR_map = {
        // {"2016", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v0btagRCal/results/btagR.root"},
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v0btagRCal/results/btagR.root"},
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v0btagRCal/results/btagR.root"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3HLTWeightUpdatedBugFixed_v56NoHLTButPre/mc/variableHists_v6_btagRMeasure/results/1tau0lNoBbtagR.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3HLTWeightUpdatedBugFixed_v56NoHLTButPre/mc/variableHists_v6_btagRMeasure/results/1tau0lNoBbtagR.root"}, //!!! to be updated!!!
        // {"2016", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/mc/variableHists_v1_btagRMeasure/results/1tauNoBbtagR.root"},
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/mc/variableHists_v1_btagRMeasure/results/1tauNoBbtagR.root"},
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/mc/variableHists_v1_btagRMeasure/results/1tauNoBbtagR.root"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/mc/variableHists_v1_btagRMeasure/results/1tauNoBbtagR.root"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v5newBtagEff_v60fixeJetBtagBug/mc/variableHists_v6forBtagRMeasure/results/bShapeR.root"},
        {"2016", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2eraBugFixed_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2eraBugFixed_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/mc/variableHists_v1_btagRMeasure/results/1tauNoBbtagR.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        {"2022preEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        {"2022postEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        {"2018", "./input/btagR/2018/bShapeR.root"},
        {"2017", "./input/btagR/2017/bShapeR.root"},
        {"2016preVFP", "./input/btagR/2016preVFP/bShapeR.root"},
        {"2016postVFP", "./input/btagR/2016postVFP/bShapeR.root"},
    };

    inline const std::map<TString, TString> btagWPEff_map = {
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2btagShapeWeightCorrected_v60fixeJetBtagBug/mc/variableHists_v2_btagEffBugFixed/results/bEff_B.root"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3btagWPWeightGood_v60fixeJetBtagBug/mc/variableHists_v3btagEffNewRegion/results/bEff_B.root"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2btagShapeWeightCorrected_v60fixeJetBtagBug/mc/variableHists_v2_btagEffBugFixed/results/bEff_B.root"},
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2btagShapeWeightCorrected_v60fixeJetBtagBug/mc/variableHists_v2_btagEffBugFixed/results/bEff_B.root"},
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2eraBugFixed_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2eraBugFixed_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2btagShapeWeightCorrected_v60fixeJetBtagBug/mc/variableHists_v2_btagEffBugFixed/results/bEff_B.root"}, //!!!
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        // {"2022preEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        {"2022postEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0NoBtagSel_v3NoHLTNoBtagButTauSel/mc/variableHists_v0_btagEffMeasure_histNameChange//results/bEff_B.root"},
        {"2022preEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0NoBtagSel_v3NoHLTNoBtagButTauSel/mc/variableHists_v0_btagEffMeasure_histNameChange//results/bEff_B.root"},//!!
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT350_v75NotHLTNoBJetTauT/mc/variableHists_v0_btagEffMeasure/results/"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v77forBtagMeasurement/mc/variableHists_v0_btagEffMeasure/results/"},    
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v77forBtagMeasurement/mc/variableHists_v0_btagEffMeasure/results/"},    
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v77forBtagMeasurement/mc/variableHists_v0_btagEffMeasure/results/"},    
        {"2018", "../inputFiles/btagWPEff/2018/effM/"},
        {"2017", "../inputFiles/btagWPEff/2017/effM/"},
        {"2016preVFP", "../inputFiles/btagWPEff/2016preVFP/effM/"},
        {"2016postVFP", "../inputFiles/btagWPEff/2016postVFP/effM/"},
    };
    inline const std::map<TString, TString> btagWPTEff_map = {
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT350_v75NotHLTNoBJetTauT/mc/variableHists_v0_btagEffMeasureT/results/"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v77forBtagMeasurement/mc/variableHists_v0_btagEffMeasureT/results/"},    
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v77forBtagMeasurement/mc/variableHists_v0_btagEffMeasureT/results/"},    
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v77forBtagMeasurement/mc/variableHists_v0_btagEffMeasureT/results/"},  
        {"2018", "../inputFiles/btagWPEff/2018/effT/"},
        {"2017", "../inputFiles/btagWPEff/2017/effT/"},
        {"2016preVFP", "../inputFiles/btagWPEff/2016preVFP/effT/"},
        {"2016postVFP", "../inputFiles/btagWPEff/2016postVFP/effT/"},
        {"2022pre", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT350_v75NotHLTNoBJetTauT/mc/variableHists_v0_btagEffMeasureT/results/bEff_B.root"},     //!
        {"2022post", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT350_v75NotHLTNoBJetTauT/mc/variableHists_v0_btagEffMeasureT/results/bEff_B.root"},    //!
    };

    inline const std::map<TString, std::array<TString,2>> FR_map = {
        {"2018",{ "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_v0FR_measure1prong_jetEta/results/fakeRateInPtEta.root", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_v0FR_measureNot1prong_jetEta/results/fakeRateInPtEta.root"}},
        {"2017", {"/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v79HadroPresel/mc/variableHists_v0FR_measure1prong/results/fakeRateInPtEta.root", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v79HadroPresel/mc/variableHists_v0FR_measure3prong/results/fakeRateInPtEta.root/"}},//!to be updated 
        {"2016postVFP", {"/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHardroHLTSF_v79HadroPresel/mc/variableHists_v0FR_measure1prong/results/fakeRateInPtEta.root", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHardroHLTSF_v79HadroPresel/mc/variableHists_v0FR_measure3prong/results/fakeRateInPtEta.root/"}},//!to be updated
        {"2016preVFP", {"/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHardroHLTSF_v79HadroPresel/mc/variableHists_v0FR_measure1prong/results/fakeRateInPtEta.root", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHardroHLTSF_v79HadroPresel/mc/variableHists_v0FR_measure3prong/results/fakeRateInPtEta.root/"}},//!to be updated
    };
    inline const std::map<TString, TString> FR_mapNew = {
    //     {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v85HadroPreselTauOverlap0.5/mc/variableHists_v0FR_measure3prongNew/results/fakeRateInPtEtaProng.root"},
    //     {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v86HadroPreSelWithTTWTTZNLO/mc/variableHists_v0FRMeasure/results/fakeRateInPtEtaProng.root"},
    //     {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0FRMeasure/results/fakeRateInPtEtaProng.root"},
    //     {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0FRMeasure/results/fakeRateInPtEtaProng.root"},
        // {"2018", "../inputFiles/tauFR/2018/fakeRateInPtEtaProng.root"},
        {"2017", "../inputFiles/tauFR/2017/fakeRateInPtEtaProng.root"},
        {"2016preVFP", "../inputFiles/tauFR/2016preVFP/fakeRateInPtEtaProng.root"},
        {"2016postVFP", "../inputFiles/tauFR/2016postVFP/fakeRateInPtEtaProng.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0FRMeasureBinB/results/fakeRateInPtEtaProng.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0FRMeasureBinC/results/fakeRateInPtEtaProng.root"},
        {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0FRMeasure/results/fakeRateInPtEtaProng.root"},
    };

    inline const std::map<TString, std::array<TString, 2>> lepFR_map = {
        {"2016preVFP", {"../inputFiles/FR_fromSS/fakeRateMap_data_electron_2016Merged_mT.root", "../inputFiles/FR_fromSS/fakeRateMap_data_muon_2016Merged_mT.root"}},
        {"2016postVFP", {"../inputFiles/FR_fromSS/fakeRateMap_data_electron_2016Merged_mT.root", "../inputFiles/FR_fromSS/fakeRateMap_data_muon_2016Merged_mT.root"}},
        {"2017", {"../inputFiles/FR_fromSS/fakeRateMap_data_electron_2017_mT.root", "../inputFiles/FR_fromSS/fakeRateMap_data_muon_2017_mT.root"}},
        {"2018", {"../inputFiles/FR_fromSS/fakeRateMap_data_electron_2018_mT.root", "../inputFiles/FR_fromSS/fakeRateMap_data_muon_2018_mT.root"}},
    };


inline const std::array<TString, 27> JES_uncer = {
    "AbsoluteMPFBias_AK4PFchs",
    "AbsoluteScale_AK4PFchs",
    "AbsoluteStat_AK4PFchs",
    "FlavorQCD_AK4PFchs",
    "Fragmentation_AK4PFchs",
    "PileUpDataMC_AK4PFchs",
    "PileUpPtBB_AK4PFchs",
    "PileUpPtEC1_AK4PFchs",
    "PileUpPtEC2_AK4PFchs",
    "PileUpPtHF_AK4PFchs",
    "PileUpPtRef_AK4PFchs",
    "RelativeFSR_AK4PFchs",
    "RelativeJEREC1_AK4PFchs",
    "RelativeJEREC2_AK4PFchs",
    "RelativeJERHF_AK4PFchs",
    "RelativePtBB_AK4PFchs",
    "RelativePtEC1_AK4PFchs",
    "RelativePtEC2_AK4PFchs",
    "RelativePtHF_AK4PFchs",
    "RelativeBal_AK4PFchs",
    "RelativeSample_AK4PFchs",
    "RelativeStatEC_AK4PFchs",
    "RelativeStatFSR_AK4PFchs",
    "RelativeStatHF_AK4PFchs",
    "SinglePionECAL_AK4PFchs",
    "SinglePionHCAL_AK4PFchs",
    "TimePtEta_AK4PFchs",
};


};


#endif