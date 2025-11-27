# Plan: Fix 46 Systematic Naming Issues for GitLab CI Validation

**Created**: 2025-11-26 10:40
**Last Updated**: 2025-11-27 (Updated with comprehensive plan)
**Status**: Active
**Source**: ~/.claude/plans/abstract-moseying-thacker.md

---

## Goal

Achieve full GitLab CI check_systematics validation by fixing all 46 systematic naming issues through comprehensive updates to BOTH C++ histogram generation and Python datacard generation.

---

## Executive Summary

Fix all 46 systematic naming issues through comprehensive updates to BOTH C++ histogram generation and Python datacard generation. The approach ensures histogram names match datacard names exactly, following CMS naming conventions.

**User Requirements**:
- Update C++ and Python code (comprehensive approach)
- Split tau fake: `CMS_eff_t_vsEle/vsMu` → `CMS_fake_t_DeepTau2017v2p1_VSe/VSmu`
- Correlate 2016 VFP eras: use same name "2016" for both preVFP and postVFP
- Fix all 46 issues at once

---

## Issues Breakdown

1. **B-tag systematics (20 issues)**: Add `fullShape_` prefix
   - `CMS_btag_hf` → `CMS_btag_fullShape_hf`
   - Same for: lf, cferr1, cferr2, hfstats1/2, lfstats1/2

2. **JES TimePtEta (1 issue)**: Add year suffix
   - `CMS_scale_j_TimePtEta` → `CMS_scale_j_TimePtEta_2016preVFP` (and other eras)

3. **Tau energy scale (16 issues)**: Add algorithm + genTau, merge VFP eras
   - `CMS_scale_t_DM0_2016preVFP` → `CMS_scale_t_DeepTau2017v2p1_DM0_genTau_2016`
   - Both 2016preVFP and 2016postVFP → `_2016` (fully correlated)

4. **Tau fake rate (4 issues)**: Split into VSe/VSmu with algorithm
   - `CMS_eff_t_vsEle` → `CMS_fake_t_DeepTau2017v2p1_VSe`
   - `CMS_eff_t_vsMu` → `CMS_fake_t_DeepTau2017v2p1_VSmu`

5. **L1 ECAL prefiring (3 issues)**: Merge VFP eras, remove 2018
   - `CMS_l1_ecal_prefiring_2016preVFP/postVFP` → `CMS_l1_ecal_prefiring_2016`
   - Remove `_2018` entry (prefiring only 2016-2017)

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

### Phase 1: C++ Code Changes (Est. 4 hours)
- Update SystematicManager.h with all systematic name changes
- Add VFP era mapping helper function
- Update functions.C histogram naming logic

### Phase 2: Python Template Consolidation (Est. 2 hours)
- Update addJESTemplatesToHistFile.py with new naming
- Add VFP era mapping for template consolidation

### Phase 3: Python Datacard Generation (Est. 2 hours)
- Update MCSys dictionary in writeDatacard.py
- Add VFP era mapping in getSysDic() function

### Phase 4: Build and Test (Est. 2 hours)
- Rebuild C++ code
- Test with single file (2018 era first)
- Verify histogram names are correct
- Test 2016 VFP correlation

### Phase 5: Full Production (Est. 3-4 days)
- Generate histograms for all eras (cluster jobs)
- Monitor jobs
- Consolidate templates
- Smooth systematics
- Generate datacards
- Combine datacards

### Phase 6: Local Validation (Est. 1 hour)
- Copy new datacard to datacards repo
- Run local check_systematics
- Verify 0 issues
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
