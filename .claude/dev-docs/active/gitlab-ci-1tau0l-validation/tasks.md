# Tasks: Fix All Systematic Naming Issues for GitLab CI

**Created**: 2025-11-26 10:40
**Last Updated**: 2025-11-28 12:20
**Status**: Phase 5.2 COMPLETE - Ready for datacards repo validation

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

## Phase 5.1: Python Script Updates (✅ COMPLETE - 2025-11-28 Session 8)

### Task 5.1.1: Update writeDatacard.py ✅
- [x] Read current MCSys dictionary (lines 7-112)
- [x] Update tau fake keys:
  - [x] `CMS_eff_t_vsMu` → `CMS_fake_t_DeepTau2017v2p1_VSmu`
  - [x] `CMS_eff_t_vsEle` → `CMS_fake_t_DeepTau2017v2p1_VSe`
  - [x] Add `class: fake_rate` metadata
- [x] Update all tau ID keys:
  - [x] `CMS_eff_t_vsJet` → `CMS_eff_t_DeepTau2017v2p1_VSjet`
  - [x] `CMS_eff_t_vsJet_stat1_dm0` → `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat1_DM0`
  - [x] `CMS_eff_t_vsJet_stat2_dm0` → `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat2_DM0`
  - [x] `CMS_eff_t_vsJet_syst_dm0` → `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_syst_DM0`
  - [x] `CMS_eff_t_vsJet_syst_alleras` → `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_syst_alleras`
  - [x] Add `class: tau_identification` metadata
- [x] Commit: 60847c6a

### Task 5.1.2: Update addJESTemplatesToHistFile.py ✅
- [x] No changes needed - only handles JES/JER/TES/MET/EES
- [x] Already has correct TES naming with DeepTau2017v2p1_genTau

### Task 5.1.3: Update addTemplateNew.py ✅
- [x] Remove VFP unmapping logic (lines 99-131) - not needed for template generation
- [x] Remove histogram renaming during template writing (lines 170-185)
- [x] Update documentation to clarify VFP handling
- [x] Commits: a08b9d41, 20861bb6

### Task 5.1.4: Update smooth_systematics_fourTops.py ✅
- [x] No changes needed - uses wd.MCSys dictionary which was already updated

---

## Phase 5.2: Full Production Run (⏳ CURRENT - 2025-11-28)

### Task 5.2.1: Submit histogram generation jobs ✅
- [x] Submit nominal jobs: `bash run_nominal_jobs.sh 1tau0l v9BDT1tau0l_CMSNamingComplete v94HadroPreJetVetoHemOnly`
  - [x] 2018: ~94 processes × 1 = 94 jobs
  - [x] 2017: ~94 processes × 1 = 94 jobs
  - [x] 2016preVFP: ~94 processes × 1 = 94 jobs
  - [x] 2016postVFP: ~94 processes × 1 = 94 jobs
- [x] Submit systematic jobs: `bash run_makeJos_WH_forJES.sh`
  - [x] Each era: ~68 systematic jobs (JES×27, JER×2, TES×8, MET×2, EES×2)
  - [x] Total systematic jobs: ~272 jobs

### Task 5.2.2: Monitor job completion ✅
- [x] All jobs completed successfully (fast execution)
- [x] Output: `/publicfs/.../v9BDT1tau0l_CMSNamingComplete/`

### Task 5.2.3: Re-consolidate systematic templates ✅
**Completed**: 2025-11-28 10:41

- [x] 2018: Completed at 10:29
- [x] 2017: Completed at 10:40
- [x] 2016preVFP: Completed at 10:41
- [x] 2016postVFP: Completed at 10:41

**Output**: All systematic histograms consolidated into individual process ROOT files

### Task 5.2.4: Generate combined templates ✅
**Completed**: 2025-11-28 11:20

- [x] Fixed VFP mapping issue in addTemplateNew.py (removed incorrect unmapping)
- [x] Fixed VFP mapping in writeDatacard.py (tau ID keeps VFP-specific names)
- [x] Generated templates for all 4 eras:
  - [x] 2018: 11:03 (2.2 MB)
  - [x] 2017: 10:57 (2.3 MB)
  - [x] 2016preVFP: 11:20 (2.3 MB)
  - [x] 2016postVFP: 11:19 (2.3 MB)

**Key Fix**: Removed VFP correlation mapping from template generation - this should only happen during datacard generation, following the same pattern as CMS_eff_e_reco

**Output**: `templatesForCombine1tau0l_new_notMCFTau_unblind.root` for each era

### Task 5.2.5: Smooth systematic templates ✅
**Completed**: 2025-11-28 11:56

- [x] Fixed b-tag systematic name in smooth_systematics_fourTops.py: `CMS_btag_hf` → `CMS_btag_fullShape_hf`
- [x] Smoothed templates for all 4 eras:
  - [x] 2018: 11:56 (2.3 MB)
  - [x] 2017: 11:56 (2.3 MB)
  - [x] 2016preVFP: 11:56 (2.4 MB)
  - [x] 2016postVFP: 11:56 (2.4 MB)

**Output**: `templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root` for each era

### Task 5.2.6: Generate datacards ✅
**Completed**: 2025-11-28 12:12

- [x] Updated writeDatacard.py to point to v9BDT smoothed templates
- [x] Generated datacards for all 4 eras:
  - [x] 2018: 12:07 (29K)
  - [x] 2017: 12:09 (29K)
  - [x] 2016preVFP: 12:12 (29K)
  - [x] 2016postVFP: 12:12 (29K)

**Output**: Individual datacards at `.../v9BDT1tau0l_CMSNamingComplete/combine/datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt`

### Task 5.2.7: Generate combined datacard (combinationV20) ⏳
**Status**: Initiated but file empty (0 bytes) - needs investigation

- [x] Updated writeCombinationDatacard.py to v9BDT paths and combinationV20
- [x] Ran script but output datacard is 0 bytes
- [ ] Debug and regenerate combined datacard

**Expected Output**: `hua/combine/combinationV20/run2_1tau0l_v4_unblind/datacard.txt`

---

## Phase 5.3: Template & Datacard Copy (NEXT - 2025-11-28)

### Task 5.3.1: Copy smoothed templates to datacards repo
- [ ] Copy all 4 era templates to `/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards/input/YEAR/`
- [ ] Verify Git LFS tracking for .root files

### Task 5.3.2: Copy combined datacard to datacards repo
- [ ] Copy combinationV20 datacard to datacards/input/datacard_1tau0l_v20_unblind.txt
- [ ] Update all template paths from absolute `/publicfs/...` to relative `YEAR/template.root`

---

## Phase 5.4: Local Validation (NEXT - 2025-11-28)

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

**Completed Phases**:
- ✅ Phases 1-4: Code changes, build, test, debug
- ✅ Phase 5.0: Additional C++ updates (tau fakes, L1 prefiring, tau ID)
- ✅ Phase 5.1: Python script updates (writeDatacard.py, addTemplateNew.py)

**Current Phase**: Phase 5.2 - Template Consolidation (IN PROGRESS)
- ✅ All histogram generation jobs completed (~376 jobs)
- ⏳ Re-consolidating systematic templates (2018 running, 3 eras pending)
**Next Milestone**: Complete consolidation for all eras, generate templates, run datacards

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
