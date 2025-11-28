# Tasks: Fix All Systematic Naming Issues for GitLab CI

**Created**: 2025-11-26 10:40
**Last Updated**: 2025-11-28 14:30
**Status**: ✅ ALL PHASES COMPLETE - Validation successful!

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
**Completed**: 2025-11-28 12:27 (regenerated)

- [x] Fixed writeDatacard.py column width (60 → 70) for long systematic names
- [x] Regenerated datacards for all 4 eras:
  - [x] 2018: 12:27 (30K)
  - [x] 2017: 12:27 (30K)
  - [x] 2016preVFP: 12:27 (30K)
  - [x] 2016postVFP: 12:27 (30K)

**Key Fix**: Column width increased to accommodate `CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat1_DM0_2016preVFP` (59 chars + " shape")

**Output**: Individual datacards at `.../v9BDT1tau0l_CMSNamingComplete/combine/datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt`

### Task 5.2.7: Generate combined datacard (combinationV20) ✅
**Completed**: 2025-11-28 12:27

- [x] Updated writeCombinationDatacard.py to v9BDT paths and combinationV20
- [x] Fixed datacard parsing error (column width issue)
- [x] Successfully generated combined datacard (164K)

**Output**: `hua/combine/combinationV20/run2_1tau0l_v4_unblind/datacard.txt`

---

## Phase 5.3: Template & Datacard Copy (✅ COMPLETE - 2025-11-28 12:30)

### Task 5.3.1: Copy smoothed templates to datacards repo ✅
**Completed**: 2025-11-28 12:29

- [x] Copied all 4 era templates to `/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards/input/YEAR/`
  - [x] 2018: 2.3 MB
  - [x] 2017: 2.3 MB
  - [x] 2016preVFP: 2.4 MB
  - [x] 2016postVFP: 2.4 MB
- [x] Git LFS handles .root files automatically

### Task 5.3.2: Copy combined datacard to datacards repo ✅
**Completed**: 2025-11-28 12:30

- [x] Copied combinationV20 datacard to datacards/input/datacard_1tau0l_v20_unblind.txt
- [x] Updated all template paths from absolute `/publicfs/...` to relative `YEAR/template.root`

---

## Phase 5.4: Systematics Dictionary Update (✅ COMPLETE - 2025-11-28 12:35)

### Task 5.4.1: Update systematics_TOP24017.yml ✅
**Completed**: 2025-11-28 12:35

Added new CMS naming convention entries:
- [x] `CMS_l1_ecal_prefiring_2016` (correlated VFP eras)
- [x] `CMS_fake_t_DeepTau2017v2p1_VSmu` (class: fake_rate, fully correlated)
- [x] `CMS_fake_t_DeepTau2017v2p1_VSe` (class: fake_rate, fully correlated)
- [x] `CMS_eff_t_DeepTau2017v2p1_VSjet_*` (class: tau_identification, all stat/syst variations)
- [x] `CMS_btag_fullShape_*` (all 8 b-tag systematics with fullShape prefix)
- [x] `CMS_scale_j_TimePtEta_YEAR` (per-era entries)
- [x] `CMS_scale_t_DeepTau2017v2p1_DM*_genTau_YEAR` (TES with 2016 VFP correlation)
- [x] `lumi_13TeV_1718` (correlated 2017-2018)

### Task 5.4.2: Commit changes to repos ✅
**Completed**: 2025-11-28 12:33

- [x] FourTop repo: Committed writeDatacard.py column width fix (commit 33c5ba16)
- [x] Datacards repo: Committed v20 datacard, templates, and systematics updates (commit 3f25162)

---

## Phase 5.5: Remove Redundant Main Tau ID Systematic (✅ COMPLETE - 2025-11-28 Session 10)

### Task 5.5.1: Identify and remove redundant systematic ✅
**Completed**: 2025-11-28 13:37
- [x] User identified `CMS_eff_t_DeepTau2017v2p1_VSjet_{YEAR}` as redundant (already split into stat/syst per DM)
- [x] Commented out in writeDatacard.py MCSys dictionary (line 28)
- [x] Commented out in systematics_TOP24017.yml (lines 128-131)

### Task 5.5.2: Regenerate all 4 era datacards ✅
**Completed**: 2025-11-28 13:36
- [x] 2018: Updated inputTemplate parameter and regenerated (already done earlier)
- [x] 2017: User regenerated manually
- [x] 2016preVFP: Updated inputTemplate to v9BDT path and regenerated
- [x] 2016postVFP: Updated inputTemplate to v9BDT path and regenerated
- [x] Verified all 4 era datacards do NOT contain main tau ID systematic

### Task 5.5.3: Regenerate combined datacard ✅
**Completed**: 2025-11-28 13:36
- [x] Used combineCards.py with proper CMSSW environment
- [x] Generated combinationV20/run2_1tau0l_v4_unblind/datacard.txt (161K)
- [x] Verified combined datacard does NOT contain main tau ID systematic
- [x] Copied to datacards repo with relative paths

### Task 5.5.4: Update systematics_TOP24017.yml class assignments ✅
**Completed**: 2025-11-28 13:13
- [x] Changed `CMS_fake_t_{YEAR}` class from `fake_rate` to `custom`
- [x] Changed `pdf_00` class from `pdf` to `custom`
- [x] Reduced check_systematics issues from 9 → 5 (then to 3 after class change)

---

## Phase 5.6: Local Validation (✅ COMPLETE - 2025-11-28)

### Task 5.6.1: Copy datacard to datacards repo ✅
**Completed**: 2025-11-28 13:37
- [x] Copied combinationV20 datacard to datacards/input/datacard_1tau0l_v20_unblind.txt
- [x] Updated paths from absolute to relative

### Task 5.6.2: Run local check_systematics ✅
**Completed**: 2025-11-28 14:25
- [x] Run check_names.py with systematics dicts
- [x] **Result**: ✅ 202 nuisances checked, 0 issues (down from original 46 issues!)

### Task 5.6.3: Commit and push to datacards repo ✅
**Completed**: 2025-11-28 14:28
- [x] Committed v20 datacard, systematics_TOP24017.yml updates, removed v19 datacard
- [x] Commit 25c5686: "feat: Update 1tau0l datacard to v20 with full CMS naming compliance"
- [x] User pushed manually (SSH permission issue resolved externally)

---

## Phase 5.7: GitLab CI Validation (✅ COMPLETE - 2025-11-28)

### Task 5.7.1: Monitor pipeline ✅
**Completed**: 2025-11-28 14:30
- [x] User confirmed: check_names.py passed in CI pipeline
- [x] All stages passed successfully

---

## 🎉 FINAL SUMMARY

**Task completed successfully!** All systematic naming issues resolved.

**Validation Results**:
- ✅ Local validation: 202 nuisances, 0 issues
- ✅ GitLab CI validation: check_names.py passed
- ✅ **Down from 46 naming issues to 0 issues**

**Key Accomplishments**:
1. Fixed all 46 systematic naming issues for CMS compliance
2. Updated C++ histogram generation (SystematicManager.h, functions.C)
3. Updated Python datacard generation (writeDatacard.py, addTemplateNew.py)
4. Generated v9BDT1tau0l_CMSNamingComplete histograms (278 jobs)
5. Created combinationV20 datacard (161K, 202 systematics)
6. Passed all local and GitLab CI validation

**Version**: v9BDT1tau0l_CMSNamingComplete / combinationV20
**Datacard**: datacard_1tau0l_v20_unblind.txt
**Date Completed**: 2025-11-28

---

## Phase 5.6: Local Validation (IN PROGRESS - 2025-11-28)

### Task 5.6.1: Copy datacard to datacards repo ✅
**Completed**: 2025-11-28 13:37
- [x] Copied combinationV20 datacard to datacards/input/datacard_1tau0l_v20_unblind.txt
- [x] Updated paths from absolute to relative

### Task 5.6.2: Run local check_systematics ⏳
- [ ] Run check_names.py with systematics dicts
- [ ] **Expected**: ~5 custom systematic warnings (down from original 46 issues)

### Task 5.6.3: Physics validation
- [ ] cd hua/combine/
- [ ] Run runCombineAll.py with V20 datacard (OPTIONAL - user may skip)
- [ ] Verify significance = 1.86σ (same as V19)

---

## Phase 5.7: GitLab CI Validation (PENDING)

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
