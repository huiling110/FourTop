#ifndef SYSTEMATICMANAGER_H
#define SYSTEMATICMANAGER_H

#include <functional>
#include <vector>
#include <string>
#include "TString.h"
#include "myEventClass.h"
#include "histsForRegionsMap_class.h"

/**
 * @brief Manages systematic variations to reduce code duplication
 *
 * This class encapsulates the logic for applying systematic variations
 * to event weights, eliminating ~120 lines of repetitive code.
 */
class SystematicManager {
public:
    struct SystematicVariation {
        TString name;
        std::function<Double_t(event*, Double_t)> upWeightFunc;
        std::function<Double_t(event*, Double_t)> downWeightFunc;
        bool isEraDependent;  // If true, append era to name

        SystematicVariation(
            const TString& sysName,
            std::function<Double_t(event*, Double_t)> upFunc,
            std::function<Double_t(event*, Double_t)> downFunc,
            bool eraDependent = false)
            : name(sysName), upWeightFunc(upFunc), downWeightFunc(downFunc),
              isEraDependent(eraDependent) {}
    };

private:
    std::vector<SystematicVariation> m_systematics;
    TString m_era;

public:
    explicit SystematicManager(const TString& era) : m_era(era) {
        initializeSystematics();
    }

    /**
     * @brief Initialize all systematic variations
     *
     * Defines the systematic variations and their weight calculation functions.
     * This centralizes all systematic handling in one place.
     */
    void initializeSystematics() {
        // Pileup
        m_systematics.emplace_back(
            "CMS_pileup",
            [](event* e, Double_t w) { return (w / e->PUweight_.v()) * e->PUweight_up_.v(); },
            [](event* e, Double_t w) { return (w / e->PUweight_.v()) * e->PUweight_down_.v(); },
            false
        );

        // L1 ECAL Prefiring
        m_systematics.emplace_back(
            "CMS_l1_ecal_prefiring",
            [](event* e, Double_t w) { return (w / e->EVENT_prefireWeight.v()) * e->EVENT_prefireWeight_up.v(); },
            [](event* e, Double_t w) { return (w / e->EVENT_prefireWeight.v()) * e->EVENT_prefireWeight_down.v(); },
            true  // era-dependent
        );

        // Tau ID vs Jet
        m_systematics.emplace_back(
            "CMS_eff_t_vsJet",
            [](event* e, Double_t w) { return (w / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsjet_up.v(); },
            [](event* e, Double_t w) { return (w / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsjet_down.v(); },
            true
        );

        // Tau ID vs Mu
        m_systematics.emplace_back(
            "CMS_eff_t_vsMu",
            [](event* e, Double_t w) { return (w / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsmu_up.v(); },
            [](event* e, Double_t w) { return (w / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsmu_down.v(); },
            true
        );

        // Tau ID vs Ele
        m_systematics.emplace_back(
            "CMS_eff_t_vsEle",
            [](event* e, Double_t w) { return (w / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsele_up.v(); },
            [](event* e, Double_t w) { return (w / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsele_down.v(); },
            true
        );

        // Tau ID stat uncertainties - DM0
        addTauIDStatSystematic("stat1_dm0",
            [](event* e) { return e->tauT_IDSF_weight_new_stat1_dm0_up.v(); },
            [](event* e) { return e->tauT_IDSF_weight_new_stat1_dm0_down.v(); });

        addTauIDStatSystematic("stat1_dm1",
            [](event* e) { return e->tauT_IDSF_weight_new_stat1_dm1_up.v(); },
            [](event* e) { return e->tauT_IDSF_weight_new_stat1_dm1_down.v(); });

        addTauIDStatSystematic("stat1_dm10",
            [](event* e) { return e->tauT_IDSF_weight_new_stat1_dm10_up.v(); },
            [](event* e) { return e->tauT_IDSF_weight_new_stat1_dm10_down.v(); });

        addTauIDStatSystematic("stat1_dm11",
            [](event* e) { return e->tauT_IDSF_weight_new_stat1_dm11_up.v(); },
            [](event* e) { return e->tauT_IDSF_weight_new_stat1_dm11_down.v(); });

        // Tau ID stat2 uncertainties
        addTauIDStatSystematic("stat2_dm0",
            [](event* e) { return e->tauT_IDSF_weight_new_stat2_dm0_up.v(); },
            [](event* e) { return e->tauT_IDSF_weight_new_stat2_dm0_down.v(); });

        addTauIDStatSystematic("stat2_dm1",
            [](event* e) { return e->tauT_IDSF_weight_new_stat2_dm1_up.v(); },
            [](event* e) { return e->tauT_IDSF_weight_new_stat2_dm1_down.v(); });

        addTauIDStatSystematic("stat2_dm10",
            [](event* e) { return e->tauT_IDSF_weight_new_stat2_dm10_up.v(); },
            [](event* e) { return e->tauT_IDSF_weight_new_stat2_dm10_down.v(); });

        addTauIDStatSystematic("stat2_dm11",
            [](event* e) { return e->tauT_IDSF_weight_new_stat2_dm11_up.v(); },
            [](event* e) { return e->tauT_IDSF_weight_new_stat2_dm11_down.v(); });

        // Tau ID systematic uncertainties - all eras
        m_systematics.emplace_back(
            "CMS_eff_t_vsJet_syst_alleras",
            [](event* e, Double_t w) { return (w / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_alleras_up.v(); },
            [](event* e, Double_t w) { return (w / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_alleras_down.v(); },
            false
        );

        // Tau ID systematic - era dependent
        m_systematics.emplace_back(
            "CMS_eff_t_vsJet_syst",
            [](event* e, Double_t w) { return (w / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_era_up.v(); },
            [](event* e, Double_t w) { return (w / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_syst_era_down.v(); },
            true
        );

        // Tau ID syst per DM
        addTauIDSystPerDM("dm0");
        addTauIDSystPerDM("dm1");
        addTauIDSystPerDM("dm10");
        addTauIDSystPerDM("dm11");

        // Lepton scale factors
        addLeptonSystematics();

        // B-tagging systematics
        addBTagSystematics();

        // Trigger systematics
        addTriggerSystematics();
    }

    /**
     * @brief Apply all systematic variations to histograms
     *
     * @param region Analysis region name
     * @param bdtScore BDT discriminant value
     * @param baseWeight Nominal event weight
     * @param passSelection Whether event passes selection
     * @param e Event object with all weights
     * @param histObj Histogram object to fill
     * @param isData Whether this is data (skips systematics)
     */
    void fillSystematics(
        const TString& region,
        Double_t bdtScore,
        Double_t baseWeight,
        Bool_t passSelection,
        event* e,
        histForRegionsBase& histObj,
        Bool_t isData) const {

        if (isData) return;  // No systematics for data

        for (const auto& sys : m_systematics) {
            TString upName = region + "_" + sys.name;
            TString downName = region + "_" + sys.name;

            if (sys.isEraDependent) {
                upName += "_" + m_era;
                downName += "_" + m_era;
            }

            upName += "Up";
            downName += "Down";

            // Calculate varied weights
            Double_t upWeight = sys.upWeightFunc(e, baseWeight);
            Double_t downWeight = sys.downWeightFunc(e, baseWeight);

            // Fill histograms
            histObj.fillHistVec(upName, bdtScore, upWeight, passSelection, isData);
            histObj.fillHistVec(downName, bdtScore, downWeight, passSelection, isData);
        }
    }

private:
    void addTauIDStatSystematic(const TString& dmName,
                                std::function<Double_t(event*)> upFunc,
                                std::function<Double_t(event*)> downFunc) {
        m_systematics.emplace_back(
            "CMS_eff_t_vsJet_" + dmName,
            [upFunc](event* e, Double_t w) { return (w / e->tauT_IDSF_weight_new.v()) * upFunc(e); },
            [downFunc](event* e, Double_t w) { return (w / e->tauT_IDSF_weight_new.v()) * downFunc(e); },
            true
        );
    }

    void addTauIDSystPerDM(const TString& dm) {
        m_systematics.emplace_back(
            "CMS_eff_t_vsJet_syst_" + dm,
            [dm](event* e, Double_t w) {
                Double_t sf_up = 1.0;
                if (dm == "dm0") sf_up = e->tauT_IDSF_weight_new_syst_era_dm0_up.v();
                else if (dm == "dm1") sf_up = e->tauT_IDSF_weight_new_syst_era_dm1_up.v();
                else if (dm == "dm10") sf_up = e->tauT_IDSF_weight_new_syst_era_dm10_up.v();
                else if (dm == "dm11") sf_up = e->tauT_IDSF_weight_new_syst_era_dm11_up.v();
                return (w / e->tauT_IDSF_weight_new.v()) * sf_up;
            },
            [dm](event* e, Double_t w) {
                Double_t sf_down = 1.0;
                if (dm == "dm0") sf_down = e->tauT_IDSF_weight_new_syst_era_dm0_down.v();
                else if (dm == "dm1") sf_down = e->tauT_IDSF_weight_new_syst_era_dm1_down.v();
                else if (dm == "dm10") sf_down = e->tauT_IDSF_weight_new_syst_era_dm10_down.v();
                else if (dm == "dm11") sf_down = e->tauT_IDSF_weight_new_syst_era_dm11_down.v();
                return (w / e->tauT_IDSF_weight_new.v()) * sf_down;
            },
            true
        );
    }

    void addLeptonSystematics() {
        // Electron systematics
        m_systematics.emplace_back(
            "CMS_TOP24017_ttttSS_eff_e_syst",
            [](event* e, Double_t w) { return (w / e->elesTopMVAT_weight_new.v()) * e->elesTopMVAT_weight_sys_up.v(); },
            [](event* e, Double_t w) { return (w / e->elesTopMVAT_weight_new.v()) * e->elesTopMVAT_weight_sys_down.v(); },
            false
        );

        m_systematics.emplace_back(
            "CMS_TOP24017_ttttSS_eff_e_stat",
            [](event* e, Double_t w) { return (w / e->elesTopMVAT_weight_new.v()) * e->elesTopMVAT_weight_stat_up.v(); },
            [](event* e, Double_t w) { return (w / e->elesTopMVAT_weight_new.v()) * e->elesTopMVAT_weight_stat_down.v(); },
            true
        );

        // Muon systematics
        m_systematics.emplace_back(
            "CMS_TOP24017_ttttSS_eff_m_syst",
            [](event* e, Double_t w) { return (w / e->musTopMVAT_weight_new.v()) * e->musTopMVAT_weight_sys_up.v(); },
            [](event* e, Double_t w) { return (w / e->musTopMVAT_weight_new.v()) * e->musTopMVAT_weight_sys_down.v(); },
            false
        );

        m_systematics.emplace_back(
            "CMS_TOP24017_ttttSS_eff_m_stat",
            [](event* e, Double_t w) { return (w / e->musTopMVAT_weight_new.v()) * e->musTopMVAT_weight_stat_up.v(); },
            [](event* e, Double_t w) { return (w / e->musTopMVAT_weight_new.v()) * e->musTopMVAT_weight_stat_down.v(); },
            true
        );
    }

    void addBTagSystematics() {
        // B-tag shape systematics
        m_systematics.emplace_back(
            "CMS_btag_jes",
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_jes_up.v(); },
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_jes_down.v(); },
            false
        );

        m_systematics.emplace_back(
            "CMS_btag_hf",
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_hf_up.v(); },
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_hf_down.v(); },
            false
        );

        m_systematics.emplace_back(
            "CMS_btag_lf",
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_lf_up.v(); },
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_lf_down.v(); },
            false
        );

        // Year-dependent b-tag statistics systematics
        m_systematics.emplace_back(
            "CMS_btag_hfstats1",
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_hfstats1_up.v(); },
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_hfstats1_down.v(); },
            true  // Era-dependent
        );

        m_systematics.emplace_back(
            "CMS_btag_hfstats2",
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_hfstats2_up.v(); },
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_hfstats2_down.v(); },
            true  // Era-dependent
        );

        m_systematics.emplace_back(
            "CMS_btag_lfstats1",
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_lfstats1_up.v(); },
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_lfstats1_down.v(); },
            true  // Era-dependent
        );

        m_systematics.emplace_back(
            "CMS_btag_lfstats2",
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_lfstats2_up.v(); },
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_lfstats2_down.v(); },
            true  // Era-dependent
        );

        // Charm flavor uncertainties (not era-dependent)
        m_systematics.emplace_back(
            "CMS_btag_cferr1",
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_cferr1_up.v(); },
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_cferr1_down.v(); },
            false
        );

        m_systematics.emplace_back(
            "CMS_btag_cferr2",
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_cferr2_up.v(); },
            [](event* e, Double_t w) { return (w / e->btagShape_weight.v()) * e->btagShape_weight_cferr2_down.v(); },
            false
        );

        // B-tag WP (Working Point) systematics
        m_systematics.emplace_back(
            "CMS_btag_fixedWP_comb_bc_correlated",
            [](event* e, Double_t w) { return (w / e->btagWPMT_weight.v()) * e->btagWPMT_weight_bc_correlated_up.v(); },
            [](event* e, Double_t w) { return (w / e->btagWPMT_weight.v()) * e->btagWPMT_weight_bc_correlated_down.v(); },
            false
        );

        m_systematics.emplace_back(
            "CMS_btag_fixedWP_comb_bc_uncorrelated",
            [](event* e, Double_t w) { return (w / e->btagWPMT_weight.v()) * e->btagWPMT_weight_bc_uncorrelated_up.v(); },
            [](event* e, Double_t w) { return (w / e->btagWPMT_weight.v()) * e->btagWPMT_weight_bc_uncorrelated_down.v(); },
            true  // Era-dependent
        );

        m_systematics.emplace_back(
            "CMS_btag_fixedWP_incl_light_correlated",
            [](event* e, Double_t w) { return (w / e->btagWPMT_weight.v()) * e->btagWPMT_weight_l_correlated_up.v(); },
            [](event* e, Double_t w) { return (w / e->btagWPMT_weight.v()) * e->btagWPMT_weight_l_correlated_down.v(); },
            false
        );

        m_systematics.emplace_back(
            "CMS_btag_fixedWP_incl_light_uncorrelated",
            [](event* e, Double_t w) { return (w / e->btagWPMT_weight.v()) * e->btagWPMT_weight_l_uncorrelated_up.v(); },
            [](event* e, Double_t w) { return (w / e->btagWPMT_weight.v()) * e->btagWPMT_weight_l_uncorrelated_down.v(); },
            true  // Era-dependent
        );
    }

    void addTriggerSystematics() {
        m_systematics.emplace_back(
            "CMS_TOP24017_eff_trigger_stats",
            [](event* e, Double_t w) { return (w / e->HLT_weight.v()) * e->HLT_weight_stats_up.v(); },
            [](event* e, Double_t w) { return (w / e->HLT_weight.v()) * e->HLT_weight_stats_down.v(); },
            true
        );

        m_systematics.emplace_back(
            "CMS_TOP24017_ttttSS_eff_trigger",
            [](event* e, Double_t w) { return (w / e->triggerSFLep_weight.v()) * e->triggerSFLep_weight_up.v(); },
            [](event* e, Double_t w) { return (w / e->triggerSFLep_weight.v()) * e->triggerSFLep_weight_down.v(); },
            true
        );
    }

public:
    /**
     * @brief Fill theory systematic variations (QCD scale, PDF, PS)
     *
     * These systematics need normalization factors which are calculated per-sample,
     * so they're handled separately from the detector systematics.
     */
    void fillTheorySystematics(
        const TString& region,
        Double_t bdtScore,
        Double_t baseWeight,
        Bool_t passSelection,
        event* e,
        histForRegionsBase& histObj,
        Bool_t isData,
        Double_t scaleRe_normUp, Double_t scaleRe_normDown,
        Double_t scaleFa_normUp, Double_t scaleFa_normDown,
        Double_t pdfAlphaS_normUp, Double_t pdfAlphaS_normDown,
        Double_t pdf_normUp, Double_t pdf_normDown,
        Double_t PSWeightISR_normUp, Double_t PSWeightISR_normDown,
        Double_t PSWeightFSR_normUp, Double_t PSWeightFSR_normDown) const {

        if (isData) return;

        // QCD scale variations
        histObj.fillHistVec(region + "_QCDscale_renUp", bdtScore,
            baseWeight * e->scaleWeightRe_up_.v() * scaleRe_normUp,
            passSelection, isData);
        histObj.fillHistVec(region + "_QCDscale_renDown", bdtScore,
            baseWeight * e->scaleWeightRe_down_.v() * scaleRe_normDown,
            passSelection, isData);

        histObj.fillHistVec(region + "_QCDscale_facUp", bdtScore,
            baseWeight * e->scaleWeightFa_up_.v() * scaleFa_normUp,
            passSelection, isData);
        histObj.fillHistVec(region + "_QCDscale_facDown", bdtScore,
            baseWeight * e->scaleWeightFa_down_.v() * scaleFa_normDown,
            passSelection, isData);

        // PDF variations
        histObj.fillHistVec(region + "_pdf_alphasUp", bdtScore,
            baseWeight * e->pdfWeightAlphaS_up_.v() * pdfAlphaS_normUp,
            passSelection, isData);
        histObj.fillHistVec(region + "_pdf_alphasDown", bdtScore,
            baseWeight * e->pdfWeightAlphaS_down_.v() * pdfAlphaS_normDown,
            passSelection, isData);

        histObj.fillHistVec(region + "_pdf_00Up", bdtScore,
            baseWeight * e->pdfWeight_up_.v() * pdf_normUp,
            passSelection, isData);
        histObj.fillHistVec(region + "_pdf_00Down", bdtScore,
            baseWeight * e->pdfWeight_down_.v() * pdf_normDown,
            passSelection, isData);

        // Parton shower variations
        histObj.fillHistVec(region + "_ps_isrUp", bdtScore,
            baseWeight * e->PSWeightISR_up_.v() * PSWeightISR_normUp,
            passSelection, isData);
        histObj.fillHistVec(region + "_ps_isrDown", bdtScore,
            baseWeight * e->PSWeightISR_down_.v() * PSWeightISR_normDown,
            passSelection, isData);

        histObj.fillHistVec(region + "_ps_fsrUp", bdtScore,
            baseWeight * e->PSWeightFSR_up_.v() * PSWeightFSR_normUp,
            passSelection, isData);
        histObj.fillHistVec(region + "_ps_fsrDown", bdtScore,
            baseWeight * e->PSWeightFSR_down_.v() * PSWeightFSR_normDown,
            passSelection, isData);
    }

    /**
     * @brief Fill MC fake tau systematic (pt-dependent)
     */
    void fillMCFakeTauSystematic(
        const TString& region,
        Double_t bdtScore,
        Double_t baseWeight,
        Bool_t passSelection,
        event* e,
        histForRegionsBase& histObj,
        Bool_t isData) const {

        if (isData) return;

        // Pt-dependent fake tau systematic
        Double_t tauPt = e->tausT_1pt.v();
        Double_t upFactor = (tauPt < 25.0) ? 1.2 : 1.1;
        Double_t downFactor = (tauPt < 25.0) ? 0.8 : 0.9;

        histObj.fillHistVec(region + "_CMS_TOP24017_fake_t_MCUp", bdtScore,
            baseWeight * upFactor, passSelection, isData);
        histObj.fillHistVec(region + "_CMS_TOP24017_fake_t_MCDown", bdtScore,
            baseWeight * downFactor, passSelection, isData);
    }

    /**
     * @brief Fill data-driven fake tau systematic
     */
    void fillDataDrivenFakeTauSystematic(
        const TString& region,
        Double_t bdtScore,
        event* e,
        histForRegionsBase& histObj,
        Bool_t passSelection,
        Bool_t isData) const {

        if (isData) return;

        histObj.fillHistVec(region + "_CMS_fake_t_" + m_era + "Up", bdtScore,
            e->FR_weight_final_up, passSelection, isData);
        histObj.fillHistVec(region + "_CMS_fake_t_" + m_era + "Down", bdtScore,
            e->FR_weight_final_down, passSelection, isData);
    }
};

#endif // SYSTEMATICMANAGER_H
