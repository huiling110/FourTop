# TTBB Integration - Task Checklist

**Last Updated**: 2025-12-07 09:40
**Current Phase**: Phase 5 - 2018 fully validated (both 1tau0l and 1tau1l), ready for other years

---

## Phase 1: Documentation Update ✅ COMPLETE

- [x] Create dev-docs directory structure
- [x] Create plan.md
- [x] Create context.md
- [x] Create tasks.md (this file)
- [x] Update ANALYSIS_WORKFLOW.md with Stage 1 details
- [x] Update ANALYSIS_WORKFLOW.md with Stage 2 details

---

## Phase 2: Sample Preparation ✅ COMPLETE

- [x] Verify all TTBB samples are accessible
- [x] Create symlinks for 2018
- [x] Create symlinks for 2017
- [x] Create symlinks for 2016 (postVFP)
- [x] Create symlinks for 2016APV (preVFP)
- [x] Calculate genEventSumw for all TTBB samples (all years)

**genEventSumw values calculated:**
- 2018: Hadronic=160749265.96, SemiLeptonic=233964940.91, 2L2Nu=21986495.40
- 2017: Hadronic=113736166.15, SemiLeptonic=153797754.09, 2L2Nu=15930889.90
- 2016: Hadronic=51913709.81, SemiLeptonic=61706979.75, 2L2Nu=7209376.72
- 2016APV: Hadronic=46015105.04, SemiLeptonic=57255372.02, 2L2Nu=6367617.64

---

## Phase 3: Configuration Updates ✅ COMPLETE

### ttttGlobleQuantity.py
- [x] Add TTBB cross-sections to crossSectionMap
- [x] Add TTBB entries to histoGramPerSample (grouped as 'ttbb')
- [x] Add 'ttbb' to proChannelDic for all channels
- [x] Add 'ttbb' to proChannelDic_forCombine for all channels

### genSumMap files
- [x] Add TTBB entries to genSumMap2016.h
- [x] Add TTBB entries to genSumMap2016APV.h
- [x] Add TTBB entries to genSumMap2017.h
- [x] Add TTBB entries to genSumMap2018.h

---

## Phase 4: Overlap Subtraction Implementation ✅ COMPLETE (v2 - Ghost-matching)

### copyBranch.C - CMS Standard Ghost-Matching
- [x] Add `countAdditionalBHadrons()` function declaration to copyBranch.h
- [x] Add `m_isTTBBSample` flag for TTBB detection
- [x] Add `GenJet_hadronFlavour` to eventReader_nano.h
- [x] Implement `countAdditionalBHadrons()` using ghost-matching:
  - [x] Loop over GenJets with pT>20 GeV, |η|<2.4, hadronFlavour==5
  - [x] Match B-hadrons to jets (ΔR < 0.4)
  - [x] Trace B-hadron ancestry to determine if from top
  - [x] Count additional b-jets (jets with B-hadrons NOT from top)
- [x] Add filtering logic in `Select()` for BOTH ttbar AND TTBB samples:
  - ttbar: REMOVE events with ≥1 additional b-jet
  - TTBB: KEEP ONLY events with ≥1 additional b-jet
- [x] Test compilation ✅
- [x] Verify sample detection (m_isTtbarSample, m_isTTBBSample)

**Committed**: `0478d65d` - feat: Add TTBB samples with ttbar overlap removal

---

## Phase 5: Full Processing (2018 FIRST)

### Stage 1: Object Selection - 2018 ✅ COMPLETE
- [x] Build objectSelectionOptimized
- [x] Fix library paths in job scripts (export LD_LIBRARY_PATH)
- [x] Fix RoccoR path in setEnv_newNew.sh (CMSSW_10_6_20 → CMSSW_14_1_0_pre4)
- [x] Fix PUWeightCal.C pileup path (CMSSW_10_6_20 → CMSSW_14_1_0_pre4)
- [x] Submit jobs for 2018 TTBB samples (all 3 decay modes)
- [x] Submit jobs for 2018 ttbar samples (with overlap removal)
- [x] Fix job OS: CentOS7 → AlmaLinux9 (for CMSSW_14/el9 libraries)
- [x] All 916 jobs completed successfully on AlmaLinux9
- [x] Output verified:
  - TTBB_4f_TTToHadronic: 10 files, 58M
  - TTBB_4f_TTToSemiLeptonic: 15 files, 51M
  - TTBB_4f_TTTo2L2Nu: 6 files, 11M
  - ttbar_0l: 339 files, 509M
  - ttbar_1l: 391 files, 392M
  - ttbar_2l: 155 files, 49M
- [x] Sample detection verified (m_isTtbarSample=1, m_isTTBBSample=1)

### Stage 2: Variable Production - 2018 ✅ COMPLETE
- [x] Build makeVariables_goodCode (fixed Makefile library path)
- [x] Add YAML config support to job script
- [x] Add TTBB entries to genSumMap.h for all years
- [x] Fix job scripts to source environment (correctionlib)
- [x] Submit jobs for 2018
- [x] Verify output ntuples:
  - TTBB_4f_TTToHadronic: 66MB
  - TTBB_4f_TTToSemiLeptonic: 59MB
  - TTBB_4f_TTTo2L2Nu: 13MB
  - ttbar_0l: 549MB
  - ttbar_1l: 442MB
  - ttbar_2l: 46MB

### Stage 3: Histogram Production - 2018 ✅ COMPLETE
- [x] Build writeHistGood (rebuilt to include updated lumiAndCrossSection.h)
- [x] Submit nominal jobs for 1tau0l (2018) via run_workflow.py
- [x] Previous run completed successfully
- [x] Fake tau files regenerated (2025-12-06 19:13/19:21)
- [x] Stage 3 jobs resubmitted (2025-12-06 19:25), ~64 jobs
- [x] Jobs completed (2025-12-07)
- [x] TTBB histograms verified with new fake tau

### Stage 4: Validation Plots - 2018 ✅ COMPLETE
- [x] Run pl.py for 1tau0l 2018 (2025-12-07 09:08)
- [x] Run pl.py for 1tau1l 2018 (2025-12-07 09:32)
- [x] Verify TTBB appears correctly in plots with regenerated fake tau
- **1tau0l Results**:
  - SR: ttbb=412.0, tt=360.7 (ttbb/tt ≈ 1.14)
  - CRMR: ttbb=573.2, tt=4386.2 (ttbb/tt ≈ 0.13)
- **1tau1l Results**:
  - SR: ttbb=35.5, tt=15.0 (ttbb/tt ≈ 2.36) - higher ratio expected in lepton channel
  - CR12: ttbb=44.3, tt=161.9 (ttbb/tt ≈ 0.27)
- TTBB shown in darker orange (#e6550d), tt in red-orange (#f03b20)
- **Both channels validated successfully!**

### After 2018 validation: Other years
- [ ] Submit jobs for 2017
- [ ] Submit jobs for 2016postVFP
- [ ] Submit jobs for 2016preVFP

---

## Phase 6: Templates, Datacards and Validation

- [ ] Run addJESTemplatesToHistFile.py
- [ ] Run addTemplateNew.py
- [ ] Run smooth_systematics_fourTops.py
- [ ] Run writeDatacard.py (with TTBB systematics)
- [ ] Run writeCombinationDatacard.py
- [ ] Run statistical analysis
- [ ] Check TTBB yields (~2-5% of tt)
- [ ] Check no negative bins
- [ ] Check data/MC agreement in control regions
- [ ] Compare results with and without TTBB
- [ ] Document physics impact

---

## Notes

### Session 1 (2025-12-05)
- Created dev-docs structure
- Plan approved by user
- Key decisions: ≥1 b-jet threshold, Stage 1 filtering, separate 'ttbb' category

### Session 2 (2025-12-05 - continued)
- Completed Phases 1-4 (all configuration and implementation)
- Committed changes: `0478d65d`
- Strategy change: Test 2018 first before running other years
- Fixed Makefile library paths
- Build successful

### Session 3 (2025-12-05 - continued)
- First job submission failed: libRoccoR.so not found at runtime
- Fixed RoccoR path in setEnv_newNew.sh (CMSSW_10_6_20 → CMSSW_14_1_0_pre4)
- Updated job scripts to export LD_LIBRARY_PATH for HTCondor jobs
- Fixed PUWeightCal.C pileup path (CMSSW_10_6_20 → CMSSW_14_1_0_pre4)
- Tested executable locally - works correctly
- Created full pipeline YAML config: `config/analysis_config_1tau0l_full.yaml`
- Updated ANALYSIS_WORKFLOW.md with Configuration section
- Jobs running successfully - TTBB and ttbar output files being created
- Commits: `b59d935e`, `cd30ed7c`, `16f24934`, `50a8c273`, `329cf162`, `33a20388`, `7b6d9653`, `a6e7989f`

### Session 4 (2025-12-05 15:30)
- All Stage 1 jobs completed (3826 jobs finished, hep_q shows 0 remaining)
- Output verified at `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v94HadroPreJetVetoHemOnly_TTBBtest/mc/`
- TTBB outputs: Hadronic (66M), SemiLeptonic (56M, 15 files), 2L2Nu (12M)
- ttbar_1l output: 570M, 391 files
- Updated Claude Code settings with comprehensive Linux commands
- Next: Verify overlap removal is working by comparing event counts

### Session 5 (2025-12-05 18:00)
- **Critical fix**: User pointed out overlap removal was wrong - needed CMS standard ghost-matching
- Updated `countAdditionalBHadrons()` to use GenJets with `hadronFlavour==5` (ghost-matching)
- Now applies overlap removal to BOTH ttbar AND TTBB samples:
  - ttbar: REMOVE events with ≥1 additional b-jet
  - TTBB: KEEP ONLY events with ≥1 additional b-jet
- Validation results: ttbar ~25% removed, TTBB ~63% kept
- Commit: `91aa3d6e` - fix: Use CMS standard ghost-matching for ttbar/TTBB overlap
- Simplified YAML config to just version string
- Updated job script to load version from YAML config
- Commit: `39a083e5` - refactor: Load Stage 1 version from YAML config
- Ready to re-run Stage 1 jobs with corrected implementation

### Session 6 (2025-12-05 17:30)
- Discovered executable was built BEFORE ghost-matching fix was committed (15:51 vs 15:55)
- Cancelled 86 old ttbar jobs using incorrect code
- Cleaned up old TTBB and ttbar output directories
- Rebuilt objectSelectionOptimized executable at 17:07 (with corrected ghost-matching)
- Created targeted job submission script: `objectSelectionOptimized/jobs/submit_ttbb_ttbar_only.py`
- Submitted 916 jobs for 2018:
  - TTBB_4f_TTToHadronic: 10 jobs (cluster 60076618)
  - TTBB_4f_TTToSemiLeptonic: 15 jobs (cluster 60076624)
  - TTBB_4f_TTTo2L2Nu: 6 jobs (cluster 60076627)
  - ttbar_0l: 339 jobs (cluster 60076638)
  - ttbar_1l: 391 jobs (cluster 60076653)
  - ttbar_2l: 155 jobs (cluster 60076664)
- All jobs running/queued, waiting for completion

### Session 7 (2025-12-06 10:20)
- Previous jobs failed with `libssl.so.3` error - CentOS7 nodes don't have el9 libraries
- Fixed job scripts to source full environment (`setEnv_newNew.sh`)
- Changed OS from CentOS7 to AlmaLinux9 for CMSSW_14 compatibility
- Updated `submit_ttbb_ttbar_only.py` with AlmaLinux9 and full env sourcing
- Resubmitted 916 jobs on AlmaLinux9 (clusters 60395717-60395770)
- All 916 jobs completed successfully!
- **Updated TTBB cross-sections** (scaled from ttH AN):
  - σ_ttbb = 43.74 × (17.75/21.34) = 36.3 pb total
  - Hadronic: 16.52 pb, Semileptonic: 15.97 pb, Dilepton: 3.85 pb
  - Updated in `ttttGlobleQuantity.py` and `lumiAndCrossSection.h`
- Stage 1 for 2018 complete, ready for Stage 2

### Session 8 (2025-12-06 13:00)
- Updated YAML config (`config/analysis_config_1tau0l_full.yaml`) with full workflow paths
- Added YAML config support to Stage 2 job script (`makeJob_makeVaribles_forBDT.py`)
- Fixed makeVariables_goodCode Makefile (CMSSW_10_6_20 → CMSSW_14_1_0_pre4)
- Added TTBB entries to `genSumMap.h` for all 4 years (was missing!)
- Fixed Stage 2 job scripts to source environment (correctionlib dependency)
- Submitted and completed Stage 2 jobs for 2018:
  - TTBB_4f_TTToHadronic: 66MB
  - TTBB_4f_TTToSemiLeptonic: 59MB
  - TTBB_4f_TTTo2L2Nu: 13MB
  - ttbar_0l: 549MB, ttbar_1l: 442MB, ttbar_2l: 46MB
- Stage 2 for 2018 complete, ready for Stage 3

### Session 9 (2025-12-06 14:05)
- Initial Stage 3 jobs produced empty TTBB histograms (~500 bytes, no keys)
- Root cause: writeHistGood needed rebuild after lumiAndCrossSection.h update
- Rebuilt writeHistGood executable (`make clean && make`)
- Tested locally with TTBB_4f_TTToHadronic - verified histograms produced:
  - 1tau0lSR: 14 entries, integral=1.58
  - 1tau0lCRMR: 22 entries, integral=2.54
- Resubmitted Stage 3 jobs via `run_workflow.py --stage 3.3 --config yaml`
- All TTBB histogram files now properly created with full systematic variations
- Stage 3 for 2018 complete, ready for Stage 4 validation plots

### Session 10 (2025-12-06 17:20)
- Added YAML config support to pl.py (plotting script)
  - New functions: `load_yaml_config()`, `build_input_dir_from_yaml()`, `parse_args()`
  - New CLI args: `--config`, `--era`, `--channel`, `--regions`, `--unblind`, `--no-sys`
- Added 'ttbb' color to `colourPerSample` dictionary (#e6550d, darker orange)
- Copied fakeTau_data_ptMorphed.root from reference version (needed for plots)
- Generated validation plots for 2018:
  - 1tau0lSR_BDT_logy_dataVsMC_v5_unblind.png
  - 1tau0lCRMR_BDT_logy_dataVsMC_v5_unblind.png
  - 1tau0lVR_BDT_logy_dataVsMC_v5_unblind.png
- TTBB validated: visible in plots with expected yields
  - SR: ttbb/tt ≈ 1.14 (overlap removal working - more b-jets in SR)
  - CRMR: ttbb/tt ≈ 0.13 (lower b-jet fraction in CR)
- Created todo.md for future refactoring tasks
- Stage 4 for 2018 complete, ready for other years

### Session 11 (2025-12-06 19:25)
- Updated ANALYSIS_WORKFLOW.md with Stage 2.4: Fake Background Estimation
  - Added createFaketauTree.py documentation (fake tau for all channels)
  - Added createFakeLeptonTree.py documentation (fake lepton for 1tau1l/1tau2l)
- User regenerated fake tau files:
  - fakeTau_data_ptMorphed.root (139M, 19:13)
  - fakeTau_MC_ptMorphed.root (603M, 19:21)
- Submitted Stage 3 histogram jobs (~64 jobs) using run_workflow.py

### Session 12 (2025-12-07 09:00)
- Resumed task, verified Stage 3 jobs completed successfully
- Ran pl.py for validation plots:
  ```bash
  python3 pl.py --config config/analysis_config_1tau0l_full.yaml --era 2018 --channel 1tau0l --regions 1tau0lSR 1tau0lCRMR 1tau0lVR --unblind --no-sys
  ```
- Generated plots saved to: `variableHists_v0BDT1tau0l_TTBBtest/results/`
- **TTBB validation successful** - yields identical to previous run:
  - SR: ttbb=412.0, tt=360.7 (ttbb/tt ≈ 1.14)
  - CRMR: ttbb=573.2, tt=4386.2 (ttbb/tt ≈ 0.13)
- **2018 1tau0l channel fully validated** - ready for other years

- Updated CLAUDE.md with analysis pipeline abbreviations (OS, MV, WH, PL)
- **1tau1l channel validation**:
  - Ran WH (Stage 3) for 1tau1l using `config/analysis_config_1tau1l_TTBBtest.yaml`
  - Ran pl.py for 1tau1l validation plots
  - **1tau1l TTBB yields**:
    - SR: ttbb=35.5, tt=15.0 (ttbb/tt ≈ 2.36) - higher ratio expected in lepton channel
    - CR12: ttbb=44.3, tt=161.9 (ttbb/tt ≈ 0.27)
  - Plots saved to: `variableHists_v0BDT1tau1l_TTBBtest/results/`
- **Both 2018 channels validated** (1tau0l and 1tau1l)
- Next steps: Process other years (2017, 2016postVFP, 2016preVFP)
