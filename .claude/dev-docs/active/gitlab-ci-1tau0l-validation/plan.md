# Plan: Fix All Systematic Naming Issues for GitLab CI Validation

**Created**: 2025-11-26 10:40
**Last Updated**: 2025-11-28 12:20
**Status**: Phase 5.2 COMPLETE - Templates smoothed, datacards generated, ready for validation
**Source**: ~/.claude/plans/abstract-moseying-thacker.md

---

## Goal

Achieve full GitLab CI check_systematics validation by fixing ALL systematic naming issues through comprehensive updates to BOTH C++ histogram generation and Python datacard generation, ensuring full CMS naming convention compliance.

---

## Executive Summary

Fix all systematic naming issues (originally 46, expanded to include tau ID) through comprehensive updates to BOTH C++ histogram generation and Python datacard generation. The approach ensures histogram names match datacard names exactly, following CMS naming conventions.

**User Requirements**:
- Update C++ and Python code (comprehensive approach)
- Tau fake: `CMS_eff_t_vsEle/vsMu` → `CMS_fake_t_DeepTau2017v2p1_VSe/VSmu` (fully correlated across all years)
- L1 prefiring: Correlate 2016 VFP eras (use unified `_2016`)
- Tau ID: `CMS_eff_t_vsJet*` → `CMS_eff_t_DeepTau2017v2p1_VSjet*` (CMS convention with algorithm name)
- Fix all naming issues at once

---

## Issues Breakdown

1. **B-tag systematics (20 issues)**: Add `fullShape_` prefix ✅ FIXED
   - `CMS_btag_hf` → `CMS_btag_fullShape_hf`
   - Same for: lf, cferr1, cferr2, hfstats1/2, lfstats1/2

2. **JES TimePtEta (1 issue)**: Add year suffix ✅ FIXED
   - `CMS_scale_j_TimePtEta` → `CMS_scale_j_TimePtEta_2016preVFP` (and other eras)

3. **Tau energy scale (16 issues)**: Add algorithm + genTau, merge VFP eras ✅ FIXED
   - `CMS_scale_t_DM0_2016preVFP` → `CMS_scale_t_DeepTau2017v2p1_DM0_genTau_2016`
   - Both 2016preVFP and 2016postVFP → `_2016` (fully correlated)

4. **Tau fake rate (4 issues)**: Rename with algorithm, fully correlate across years ✅ C++ FIXED
   - `CMS_eff_t_vsEle` → `CMS_fake_t_DeepTau2017v2p1_VSe` (NO year suffix)
   - `CMS_eff_t_vsMu` → `CMS_fake_t_DeepTau2017v2p1_VSmu` (NO year suffix)
   - **Class**: `fake_rate` (for GitLab CI validation)

5. **L1 ECAL prefiring (3 issues)**: Merge VFP eras, remove 2018 ✅ C++ FIXED
   - `CMS_l1_ecal_prefiring_2016preVFP/postVFP` → `CMS_l1_ecal_prefiring_2016`
   - Skip `_2018` entry (prefiring only 2016-2017)

6. **Tau ID vs Jet (NEW - discovered during implementation)**: Update to CMS convention ✅ C++ FIXED
   - `CMS_eff_t_vsJet` → `CMS_eff_t_DeepTau2017v2p1_VSjet`
   - `CMS_eff_t_vsJet_stat1_dm0` → `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat1_DM0`
   - `CMS_eff_t_vsJet_stat2_dm0` → `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat2_DM0`
   - `CMS_eff_t_vsJet_syst_dm0` → `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_syst_DM0`
   - `CMS_eff_t_vsJet_syst_alleras` → `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_syst_alleras`
   - **Class**: `tau_identification` (for GitLab CI validation)

---

## Critical Files to Modify

### C++ Files (writeHistGood/)

1. **`include/SystematicManager.h`**
   - B-tag systematics definitions
   - Tau fake rate (rename and split)
   - Add 2016 VFP era mapping logic

2. **`src/functions.C`**
   - Update histogram naming in region-specific code
   - Add VFP era mapping for applicable systematics

### Python Files (plotting/)

3. **`writeDatacard.py`**
   - Lines 7-112: MCSys dictionary (rename all systematic keys)
   - Lines 359-381: getSysDic() function (add VFP era mapping)

4. **`addJESTemplatesToHistFile.py`**
   - Update tau energy scale template naming
   - Add VFP era mapping in template consolidation

---

## Implementation Phases

### ✅ Phase 1-4: Initial Implementation (COMPLETE - 2025-11-26 to 2025-11-27)
- ✅ Updated SystematicManager.h with b-tag, TES, initial tau fake/L1 prefiring changes
- ✅ Updated functions.C histogram naming logic
- ✅ Fixed histogram initialization to match new systematic names
- ✅ Updated Python scripts (addJESTemplatesToHistFile.py, writeDatacard.py)
- ✅ Rebuilt C++ code successfully
- ✅ Tested with single file (2018 era)
- ✅ Fixed segfault issue (histogram initialization mismatch)
- ✅ Fixed job submission scripts (environment sourcing)
- ✅ Submitted 278 jobs (nominal + systematic for all 4 eras)
- ✅ All 278 jobs completed successfully

### ✅ Phase 5.0: Additional C++ Updates for Full CMS Compliance (COMPLETE - 2025-11-27 Session 7)

**Discovery**: During testing, found that tau fake and tau ID naming needed updates for full CMS convention compliance

**Changes Made**:

1. **Tau Fake Rate Correlation** ✅
   - Changed from era-dependent to fully correlated (no year suffix)
   - SystematicManager.h: Set `isEraDependent = false` for tau fakes
   - Verified: `CMS_fake_t_DeepTau2017v2p1_VSe/VSmu` (no `_2018`, `_2017`, etc.)

2. **L1 ECAL Prefiring VFP Mapping** ✅
   - SystematicManager.h: Map 2016preVFP/postVFP → 2016 in base name
   - functions.C: Keep VFP mapping for histogram initialization
   - Verified: Both VFP eras produce `CMS_l1_ecal_prefiring_2016`

3. **Tau ID vs Jet CMS Convention** ✅ (NEW)
   - Updated ALL tau ID systematics to CMS naming convention
   - Main: `CMS_eff_t_vsJet` → `CMS_eff_t_DeepTau2017v2p1_VSjet`
   - Stat: `stat1_dm0` → `dm_stat1_DM0`, `stat2_dm0` → `dm_stat2_DM0`
   - Syst: `syst_dm0` → `dm_syst_DM0`, `syst_alleras` → `dm_syst_alleras`
   - Updated both SystematicManager.h and functions.C
   - Verified all naming with test runs

**Testing Results**:
- ✅ 2018: All systematics named correctly
- ✅ 2016preVFP: L1 prefiring correctly `_2016` (not `_2016preVFP`)
- ✅ 2016postVFP: L1 prefiring correctly `_2016` (not `_2016postVFP`)
- ✅ Tau fakes: No year suffix (fully correlated)
- ✅ Tau ID: All stat1/stat2/syst variations correct with DM0/1/10/11

### ⏳ Phase 5.1: Python Script Updates (CURRENT - 2025-11-27)

**Need to update**:

1. **`plotting/writeDatacard.py`** - MCSys dictionary:
   - Update all tau fake keys: `CMS_eff_t_vsMu/vsEle` → `CMS_fake_t_DeepTau2017v2p1_VSmu/VSe`
   - Update all tau ID keys: `CMS_eff_t_vsJet*` → `CMS_eff_t_DeepTau2017v2p1_VSjet*`
   - Add systematic class metadata:
     - `class: tau_identification` for all tau ID systematics
     - `class: fake_rate` for tau fake systematics

2. **`plotting/addJESTemplatesToHistFile.py`**:
   - Update systematic name mappings for new tau fake/ID names
   - Ensure VFP era mapping works with new names

3. **`plotting/addTemplateNew.py`**:
   - Update systematic name patterns for new tau fake/ID names
   - Verify VFP era handling

4. **`plotting/smooth_systematics_fourTops.py`**:
   - Update systematic name patterns

### Phase 5.2: Full Production Run (Est. 3-6 hours)
- Submit histogram generation jobs for all 4 eras
- Version: `v11BDT1tau0l_CMSNamingComplete`
- Monitor job completion
- Verify histogram names in output files

### Phase 5.3: Template & Datacard Generation (Est. 2 hours)
- Run addJESTemplatesToHistFile.py (template consolidation)
- Run addTemplateNew.py (template generation)
- Run smooth_systematics_fourTops.py (smoothing)
- Run writeDatacard.py (datacard generation for each era)
- Run writeCombinationDatacard.py (combine all eras)
### Phase 5.4: Local Validation (Est. 1 hour)
- Copy new datacard to datacards repo
- Run local check_systematics with systematics_TOP24017.yml
- **Target**: 0 issues (down from 46+)
- Physics validation: significance should match V19 (1.86σ)

### Phase 5.5: GitLab CI Validation (Est. 2 hours)
- Copy template files to datacards repo (if needed)
- Update datacard paths to relative (not absolute /publicfs/)
- Commit and push to datacards repo
- Monitor GitLab CI pipeline
- **Target**: All stages PASS (ValidateDatacards, T2W, MultiDimFit, Impacts)

### Phase 5.6: Documentation (Est. 1 hour)
- Update CMS_NAMING_CONVENTION_UPDATE.md with Phase 5.0 changes
- Update dev-docs (this file, context.md, tasks.md)
- Update ANALYSIS_WORKFLOW.md with final version name
- Archive dev-docs to completed/
- Physics validation (significance = 1.86σ)

### Phase 7: GitLab CI Validation (Est. 2 hours)
- Copy template files if needed
- Update datacard paths to relative
- Commit and push
- Monitor GitLab CI

### Phase 8: Documentation (Est. 2 hours)
- Update CMS_NAMING_CONVENTION_UPDATE.md
- Update dev-docs
- Update ANALYSIS_WORKFLOW.md

---

## Success Criteria

✅ **GitLab CI check_systematics**: 0 issues (down from 46)
✅ **All CI stages pass**: ValidateDatacards, T2W, MultiDimFit, Impacts
✅ **Physics validation**: Significance = 1.86σ (identical to reference)
✅ **2016 VFP correlation**: Both eras use same systematic names (_2016)
✅ **Systematic count**: ~212 nuisances (same as V19)
✅ **Template files**: Updated with new systematic names

---

## Risk Mitigation

**Risk 1**: Tau fake rate split may not have separate event weights
*Mitigation*: Verify event class has separate VSe/VSmu weights before Phase 1

**Risk 2**: Physics results change after systematic renaming
*Mitigation*: Comprehensive validation at Phase 6

**Risk 3**: 2016 VFP correlation affects physics interpretation
*Mitigation*: Document clearly in analysis notes (user confirmed desired behavior)

---

## Estimated Timeline

- **Code changes**: 8 hours (Phases 1-3)
- **Build and test**: 2 hours (Phase 4)
- **Cluster jobs**: 3-4 days (Phase 5)
- **Validation**: 3 hours (Phases 6-7)
- **Documentation**: 2 hours (Phase 8)

**Total**: 5-6 days (including job runtime)

---

**Full plan**: `~/.claude/plans/abstract-moseying-thacker.md`
