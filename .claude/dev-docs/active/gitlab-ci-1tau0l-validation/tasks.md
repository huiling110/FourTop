# Tasks: Fix All Systematic Naming Issues for GitLab CI

**Created**: 2025-11-26 10:40
**Last Updated**: 2025-11-27 22:40
**Status**: Phase 5.1 IN PROGRESS - C++ complete, Python updates pending

---

## Phase 5.0: Additional C++ Updates (✅ COMPLETE - 2025-11-27 Session 7)

### Task 5.0.1: Update tau fake correlation ✅
- [x] Update SystematicManager.h: Set `isEraDependent = false` for tau fakes
- [x] Verify histograms have no year suffix

### Task 5.0.2: Update L1 prefiring VFP mapping ✅
- [x] Update SystematicManager.h: Map 2016preVFP/postVFP → 2016 in base name
- [x] Update functions.C: Keep VFP mapping for histogram initialization
- [x] Test with 2016preVFP and 2016postVFP samples

### Task 5.0.3: Update tau ID naming to CMS convention ✅
- [x] Update SystematicManager.h:
  - [x] Main: `CMS_eff_t_vsJet` → `CMS_eff_t_DeepTau2017v2p1_VSjet`
  - [x] Stat: Update addTauIDStatSystematic to use `dm_stat1/2_DM0` pattern
  - [x] Syst: Update addTauIDSystPerDM to use `dm_syst_DM0` pattern
  - [x] Syst alleras: `CMS_eff_t_vsJet_syst_alleras` → `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_syst_alleras`
- [x] Update functions.C: Update all tau ID systematic names
- [x] Rebuild C++ code
- [x] Test with 2018, 2016preVFP, 2016postVFP samples

---

## Phase 5.1: Python Script Updates (⏳ CURRENT)

### Task 5.1.1: Update writeDatacard.py
- [ ] Read current MCSys dictionary (lines 7-112)
- [ ] Update tau fake keys:
  - [ ] `CMS_eff_t_vsMu` → `CMS_fake_t_DeepTau2017v2p1_VSmu`
  - [ ] `CMS_eff_t_vsEle` → `CMS_fake_t_DeepTau2017v2p1_VSe`
  - [ ] Add `class: fake_rate` metadata
- [ ] Update all tau ID keys:
  - [ ] `CMS_eff_t_vsJet` → `CMS_eff_t_DeepTau2017v2p1_VSjet`
  - [ ] `CMS_eff_t_vsJet_stat1_dm0` → `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat1_DM0`
  - [ ] `CMS_eff_t_vsJet_stat2_dm0` → `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat2_DM0`
  - [ ] `CMS_eff_t_vsJet_syst_dm0` → `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_syst_DM0`
  - [ ] `CMS_eff_t_vsJet_syst_alleras` → `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_syst_alleras`
  - [ ] Add `class: tau_identification` metadata
- [ ] Update getSysDic() function for VFP era mapping (if needed)

### Task 5.1.2: Update addJESTemplatesToHistFile.py
- [ ] Update systematic name mappings for tau fake/ID
- [ ] Verify VFP era mapping works with new names

### Task 5.1.3: Update addTemplateNew.py
- [ ] Update systematic name patterns for tau fake/ID
- [ ] Verify VFP era handling

### Task 5.1.4: Update smooth_systematics_fourTops.py
- [ ] Update systematic name patterns for tau fake/ID

---

## Phase 5.2: Full Production Run

### Task 5.2.1: Submit histogram generation jobs
- [ ] Clean previous v10BDT test output
- [ ] Submit nominal jobs: `bash run_nominal_jobs.sh 1tau0l v11BDT1tau0l_CMSNamingComplete v94HadroPreJetVetoHemOnly`
- [ ] Submit systematic jobs: `bash run_makeJos_WH_forJES.sh`
- [ ] Monitor jobs: `hep_q | grep huahuil | wc -l`

### Task 5.2.2: Monitor job completion
- [ ] Wait for all jobs to complete (~3-6 hours)
- [ ] Check for failed jobs: `cd jobs/ && python3 checkJobResult.py`
- [ ] Verify histogram names in output ROOT files

---

## Phase 6: Local Validation (Est. 1 hour)

### Task 6.1: Copy datacard to datacards repo
- [ ] Copy combinationV20 datacard to datacards/input/
- [ ] Name: datacard_1tau0l_v20_unblind.txt

### Task 6.2: Run local check_systematics
- [ ] cd datacards repo
- [ ] cmsenv
- [ ] Run check_names.py with systematics dicts
- [ ] **Target**: 0 issues (down from 46)

### Task 6.3: Physics validation
- [ ] cd hua/combine/
- [ ] Run runCombineAll.py with V20 datacard
- [ ] Verify significance = 1.86σ (same as V19)

---

## Phase 7: GitLab CI Validation (Est. 2 hours)

### Task 7.1: Copy template files to datacards repo
- [ ] Copy templatesForCombine1tau0l_v20.root for all 4 eras
- [ ] Use Git LFS for large files

### Task 7.2: Update datacard paths
- [ ] Edit datacard to use relative paths
- [ ] Pattern: /publicfs/.../combine/ → ${era}/

### Task 7.3: Commit and push
- [ ] git add datacard + templates + systematics submodule
- [ ] Create comprehensive commit message
- [ ] git push origin master

### Task 7.4: Monitor GitLab CI
- [ ] Check pipeline URL
- [ ] Monitor validate_datacards stage
- [ ] Monitor text2workspace stage
- [ ] Monitor fit_diagnostics stage
- [ ] Monitor impacts stage
- [ ] **Target**: All stages PASS

---

## Phase 8: Documentation (Est. 2 hours)

### Task 8.1: Update CMS_NAMING_CONVENTION_UPDATE.md
- [ ] Document all 46 systematic name changes
- [ ] Note V20 as fully CMS-compliant version
- [ ] Include GitLab CI validation results

### Task 8.2: Update dev-docs
- [ ] Mark all tasks complete
- [ ] Document final validation results
- [ ] Archive to completed/

### Task 8.3: Update ANALYSIS_WORKFLOW.md
- [ ] Note new version: v8BDT1tau0l_V20_CMSNamingComplete
- [ ] Document systematic naming conventions used

---

## Progress Tracking

**Completed Phases**: Phases 1-4 (Code changes, build, test, debug) ✅
**Current Phase**: Phase 5 - Full Production (IN PROGRESS)
**Jobs Submitted**: 278 total (nominal + systematic for all 4 eras)
**Jobs Running**: 225 running, 53 queued (as of 2025-11-27 19:00)
**Next Milestone**: Wait for jobs to complete (~3-6 hours), then consolidate templates

---

## Blockers / Issues

**Current**: ✅ **RESOLVED - Segfault fixed!**

**Issue Details** (2025-11-27):
- **Root cause**: Histogram initialization in `functions.C::getChannelSys()` used OLD systematic names, but `SystematicManager::fillSystematics()` tried to fill with NEW names
- **Mismatch**: `CMS_eff_t_vsMu/vsEle` (old) vs `CMS_fake_t_DeepTau2017v2p1_VSmu/VSe` (new)
- **Fix**: Updated `functions.C` lines 430-437 to use new systematic names
- **Commit**: `5afc7774` - fix: Update tau fake rate systematic names in histogram initialization

**Testing Results**:
- Test WITHOUT systematics (ifSys=0): ✅ Passes
- Test WITH systematics (ifSys=1): ✅ **NOW PASSES** (was segfault)
- Verified systematic names in output ROOT file
  - ✅ `CMS_fake_t_DeepTau2017v2p1_VSe/VSmu`
  - ✅ `CMS_btag_fullShape_*`
  - ✅ L1 prefiring 2018 exists but has 0 entries (correctly skipped)

**Remaining Risks**:
- ⚠️ Full production run not yet tested (cluster jobs)
- ⚠️ Physics validation must match V19 results (1.86σ significance)

---

## Notes

- All tasks should be marked complete immediately when finished
- Update "Last Updated" timestamp when modifying this file
- Validate physics results after each major phase
- Keep V19 results as reference for comparison

---

**Next task**: Start Phase 1, Task 1.1 (Update B-tag systematics)
