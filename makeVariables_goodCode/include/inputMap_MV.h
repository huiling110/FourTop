#ifndef INPUTMAP_MV_H
#define INPUTMAP_MV_H

namespace MV
{

    // top lepton mva
    inline const std::map<TString, std::array<TString, 2>> topLeptonSF_files = {
        {"2016preVFP", {"./input/topMVASF/ele/2016APV/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2016HIPM/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
        {"2016postVFP", {"./input/topMVASF/ele/2016/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2016/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
        {"2017", {"./input/topMVASF/ele/2017/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2017/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
        {"2018", {"./input/topMVASF/ele/2018/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2018/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},
        {"2022preEE", {"./input/topMVASF/ele/2018/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2018/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},//!!!
        {"2022postEE", {"./input/ele2022SF/passingMVA122Xwp90isoV1/2022postEE/egammaEffi.txt_EGM2D.root", "./input/topMVASF/mu/2018/NUM_LeptonMvaMedium_DEN_TrackerMuons_abseta_pt.root"}},//!!!

    };

    inline const std::map<TString, TString> triggerSF_map = {
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v8add2DHist/results/baseline1Muon1b_triggerSF.root"},
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v8add2DHist/results/baseline1Muon1b_triggerSF.root"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v8add2DHist/results/baseline1Muon1b_triggerSF.root"}, // to be updated!!!
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baslineNoHLT_v54noHLTButPre/mc/variableHists_v0triggerEff/results/baseline1Muon1b_triggerSF.root"},
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v55ojectRemovalwithTightNoHLT/mc/variableHists_v1triigerEff_btagShapeWeight/results/baseline1Muon1b_triggerSF.root"},
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v55ojectRemovalwithTightNoHLT/mc/variableHists_v1triigerEff_btagShapeWeight/results/baseline1Muon1b_triggerSF.root"},
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v57ovelapWithTausF/mc/variableHists_v0_HLTSFMeasure/results/baseline1Muon1b_triggerSF.root"},
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v57ovelapWithTausF/mc/variableHists_v0_HLTSFMeasure/results/baseline1Muon1b_triggerSF.root"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2baslineNoHLTBugFixed_v56NoHLTButPre/mc/variableHists_v1triigerEff_btagShapeWeight/results/baseline1Muon1b_triggerSF.root"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2baslineNoHLTBugFixed_v56NoHLTButPre/mc/variableHists_v0_triggerSFNewRange/results/baseline1Muon1b_triggerSF.root"},
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
        {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/results/baseline1Muon1b_triggerSFTest.root"},
        {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/results/baseline1Muon1b_triggerSF_new.root"},
        {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/results/baseline1Muon1b_triggerSF_new.root"},
        {"2022postEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v3NotHLTPre/mc/variableHists_v0_HLTSFMeasure/results/baseline1Muon1b_triggerSF_v0.root"},
        {"2022preEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/results/baseline1Muon1b_triggerSF.root"},//!!!To be updated
        {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineBtagUpdated_V75NoHLTNoTauBjet2Jet6/mc/variableHists_v0HLT/results/baseline1Muon1b_triggerSF_v0.root"}
    };

    inline const std::map<TString, std::array<TString, 3>> json_map = {
        {"2016preVFP", {"JME/2016preVFP_UL/jet_jerc.json", "TAU/2016preVFP_UL/tau.json", "BTV/2016preVFP_UL/btagging.json"}},
        {"2016postVFP", {"JME/2016postVFP_UL/jet_jerc.json", "TAU/2016postVFP_UL/tau.json", "BTV/2016postVFP_UL/btagging.json"}},
        {"2017", {"JME/2017_UL/jet_jerc.json", "TAU/2017_UL/tau.json", "BTV/2017_UL/btagging.json"}},
        {"2018", {"JME/2018_UL/jet_jerc.json", "TAU/2018_UL/tau.json", "BTV/2018_UL/btagging.json"}},
        {"2022preEE", {"JME/2018_UL/jet_jerc.json", "../newRun3/TAU/2022_preEE/tau_DeepTau2018v2p5_2022_preEE.json", "BTV/2022_Summer22/btagging.json"}},
        {"2022postEE", {"JME/2018_UL/jet_jerc.json", "../newRun3/TAU/2022_postEE/tau_DeepTau2018v2p5_2022_postEE.json", "BTV/2022_Summer22EE/btagging.json"}},
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
        {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2eraBugFixed_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2eraBugFixed_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/mc/variableHists_v1_btagRMeasure/results/1tauNoBbtagR.root"},
        {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        {"2022preEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
        {"2022postEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/results/bShapeR.root"},
    };

    inline const std::map<TString, TString> btagWPEff_map = {
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2btagShapeWeightCorrected_v60fixeJetBtagBug/mc/variableHists_v2_btagEffBugFixed/results/bEff_B.root"},
        // {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3btagWPWeightGood_v60fixeJetBtagBug/mc/variableHists_v3btagEffNewRegion/results/bEff_B.root"},
        {"2017", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        // {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2btagShapeWeightCorrected_v60fixeJetBtagBug/mc/variableHists_v2_btagEffBugFixed/results/bEff_B.root"},
        // {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2btagShapeWeightCorrected_v60fixeJetBtagBug/mc/variableHists_v2_btagEffBugFixed/results/bEff_B.root"},
        {"2016preVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2eraBugFixed_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        {"2016postVFP", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2eraBugFixed_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2btagShapeWeightCorrected_v60fixeJetBtagBug/mc/variableHists_v2_btagEffBugFixed/results/bEff_B.root"}, //!!!
        // {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        // {"2022preEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/results/bEff_B.root"},
        {"2022postEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0NoBtagSel_v3NoHLTNoBtagButTauSel/mc/variableHists_v0_btagEffMeasure_histNameChange//results/bEff_B.root"},
        {"2022preEE", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0NoBtagSel_v3NoHLTNoBtagButTauSel/mc/variableHists_v0_btagEffMeasure_histNameChange//results/bEff_B.root"},//!!
        {"2018", "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT350_v75NotHLTNoBJetTauT/mc/variableHists_v0_btagEffMeasure/results/bEff_B.root"},
    };
};
#endif