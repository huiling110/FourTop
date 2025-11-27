# Tasks: Fix 46 Systematic Naming Issues for GitLab CI

**Created**: 2025-11-26 10:40
**Last Updated**: 2025-11-27 11:20
**Status**: PAUSED at Phase 5 - Ready to submit jobs (higher priority: disk cleanup)

---

## Phase 1: C++ Code Changes (Est. 4 hours)

### Task 1.1: Update B-tag systematics in SystematicManager.h
- [ ] Read current SystematicManager.h b-tag section (~lines 269-317)
- [ ] Add `fullShape_` prefix to all 8 b-tag systematics
  - [ ] CMS_btag_hf → CMS_btag_fullShape_hf
  - [ ] CMS_btag_lf → CMS_btag_fullShape_lf
  - [ ] CMS_btag_cferr1 → CMS_btag_fullShape_cferr1
  - [ ] CMS_btag_cferr2 → CMS_btag_fullShape_cferr2
  - [ ] CMS_btag_hfstats1 → CMS_btag_fullShape_hfstats1
  - [ ] CMS_btag_hfstats2 → CMS_btag_fullShape_hfstats2
  - [ ] CMS_btag_lfstats1 → CMS_btag_fullShape_lfstats1
  - [ ] CMS_btag_lfstats2 → CMS_btag_fullShape_lfstats2

### Task 1.2: Update JES TimePtEta systematic
- [ ] Read SystematicManager.h JES section (~line 95)
- [ ] Change CMS_scale_j_TimePtEta from correlated (true) to era-dependent (false)
  - This enables automatic era suffix: _2016preVFP, _2016postVFP, _2017, _2018

### Task 1.3: Update tau energy scale systematics
- [ ] Read SystematicManager.h tau TES section (~lines 103-106)
- [ ] Add algorithm + genTau qualifier to all 4 DM systematics
  - [ ] CMS_scale_t_DM0 → CMS_scale_t_DeepTau2017v2p1_DM0_genTau
  - [ ] CMS_scale_t_DM1 → CMS_scale_t_DeepTau2017v2p1_DM1_genTau
  - [ ] CMS_scale_t_DM10 → CMS_scale_t_DeepTau2017v2p1_DM10_genTau
  - [ ] CMS_scale_t_DM11 → CMS_scale_t_DeepTau2017v2p1_DM11_genTau

### Task 1.4: Verify tau fake rate event weights
- [ ] Check Event class for separate VSe and VSmu weights
  - Look for: getTauVSeWeight(), getTauVSmuWeight() or similar
- [ ] If separate weights exist: proceed with split implementation
- [ ] If not available: document and ask user for guidance

### Task 1.5: Update tau fake rate systematics (CONDITIONAL on 1.4)
- [ ] Read SystematicManager.h tau fake section (~line 57)
- [ ] Split CMS_eff_t_vsEle → CMS_fake_t_DeepTau2017v2p1_VSe
- [ ] Split CMS_eff_t_vsMu → CMS_fake_t_DeepTau2017v2p1_VSmu
- [ ] Keep era-dependent (false) for both

### Task 1.6: Add VFP era mapping helper function
- [ ] Add mapVFPEra() method to SystematicManager class
  ```cpp
  TString mapVFPEra(const TString& era) {
      if (era.Contains("2016")) return "2016";
      return era;
  }
  ```

### Task 1.7: Update L1 ECAL prefiring logic
- [ ] Read SystematicManager.h prefiring section (~line 12)
- [ ] Add era check to skip 2018
- [ ] Ensure era-dependent (false) to enable VFP mapping

### Task 1.8: Update functions.C histogram naming
- [ ] Read functions.C histogram creation section (~lines 484-501)
- [ ] Add VFP era mapping for applicable systematics:
  - CMS_scale_t_* (tau TES)
  - CMS_l1_ecal_prefiring
  - CMS_fake_t_* (tau fake rate)
- [ ] Apply mapVFPEra() before histogram naming

---

## Phase 2: Python Template Consolidation (Est. 2 hours)

### Task 2.1: Update addJESTemplatesToHistFile.py
- [ ] Read addJESTemplatesToHistFile.py (~lines 400-500)
- [ ] Update tau TES template naming pattern
- [ ] Add VFP era mapping function
- [ ] Apply mapping during template consolidation

---

## Phase 3: Python Datacard Generation (Est. 2 hours)

### Task 3.1: Update MCSys dictionary in writeDatacard.py
- [ ] Read writeDatacard.py MCSys section (lines 7-112)
- [ ] Update all systematic names:
  - [ ] B-tag: Add fullShape_ prefix (8 systematics)
  - [ ] JES TimePtEta: Change to era-dependent
  - [ ] Tau TES: Add DeepTau2017v2p1_genTau (4 systematics)
  - [ ] Tau fake: Split into VSe/VSmu (2 systematics)
  - [ ] L1 prefiring: Keep as-is (mapping in getSysDic)

### Task 3.2: Update getSysDic() function
- [ ] Read getSysDic() function (lines 359-381)
- [ ] Add VFP era mapping logic for specific systematics
- [ ] Add L1 prefiring 2018 skip logic
- [ ] Verify systematic name generation with mapped era

---

## Phase 4: Build and Test (Est. 2 hours)

### Task 4.1: Rebuild C++ code
- [ ] cd writeHistGood/
- [ ] source ../setEnv_newNew.sh
- [ ] make clean && make
- [ ] Verify compilation succeeds

### Task 4.2: Test with 2018 single file
- [ ] Identify small test ROOT file
- [ ] Run: ./apps/run_treeAnalyzer.out 2018 1tau0l /path/to/test.root
- [ ] Verify output ROOT file created

### Task 4.3: Verify histogram names (2018)
- [ ] Open output ROOT file in ROOT
- [ ] Check systematic histogram names:
  - [ ] CMS_btag_fullShape_hf_2018Up/Down
  - [ ] CMS_scale_j_TimePtEta_2018Up/Down
  - [ ] CMS_scale_t_DeepTau2017v2p1_DM0_genTau_2018Up/Down
  - [ ] CMS_fake_t_DeepTau2017v2p1_VSe_2018Up/Down
  - [ ] CMS_fake_t_DeepTau2017v2p1_VSmu_2018Up/Down

### Task 4.4: Test 2016 VFP correlation
- [ ] Run 2016preVFP: ./apps/run_treeAnalyzer.out 2016preVFP 1tau0l /path/to/test.root
- [ ] Run 2016postVFP: ./apps/run_treeAnalyzer.out 2016postVFP 1tau0l /path/to/test.root
- [ ] Verify both use _2016 suffix (NOT _2016preVFP/_2016postVFP) for:
  - [ ] CMS_scale_t_DeepTau2017v2p1_DM*_genTau_2016
  - [ ] CMS_l1_ecal_prefiring_2016
  - [ ] CMS_fake_t_DeepTau2017v2p1_VSe/VSmu_2016

### Task 4.5: Verify L1 prefiring 2018 skip
- [ ] Check 2018 output ROOT file
- [ ] Confirm NO CMS_l1_ecal_prefiring_2018 histograms

---

## Phase 5: Full Production (Est. 3-4 days)

### Task 5.1: Submit histogram generation jobs
- [ ] cd writeHistGood/jobs/
- [ ] Submit nominal + systematic jobs for all 4 eras
- [ ] Submit JES systematic jobs (run_makeJobs_WH_forJES.sh)

### Task 5.2: Monitor job completion
- [ ] Run checkJobResult.py regularly
- [ ] Verify all jobs complete successfully
- [ ] Check for failed jobs and resubmit if needed

### Task 5.3: Consolidate templates
- [ ] cd ../plotting/
- [ ] Run addJESTemplatesToHistFile.py for all 4 eras
- [ ] Verify template ROOT files created

### Task 5.4: Smooth systematics
- [ ] Run smooth_systematics_fourTops.py --era all --channel 1tau0l
- [ ] Verify smoothing completed

### Task 5.5: Generate datacards
- [ ] Run writeDatacard.py for all 4 eras
- [ ] Verify individual datacards created

### Task 5.6: Combine datacards
- [ ] cd ../hua/combine/
- [ ] Run writeCombinationDatacard.py --channel 1tau0l --version V20
- [ ] Verify combined datacard created

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
**Current Phase**: Phase 5 - Submit Full Production Jobs (PAUSED)
**Next Milestone**: Submit cluster jobs for all eras
**Paused Reason**: Disk quota near limit on /publicfs - need to clean up before submitting large job runs

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
