# TTBB Integration - Task Checklist

**Last Updated**: 2025-12-05 13:15
**Current Phase**: Phase 5 - Stage 1 running for 2018

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

## Phase 4: Overlap Subtraction Implementation ✅ COMPLETE

### copyBranch.C
- [x] Add `countAdditionalBJets()` function declaration to copyBranch.h
- [x] Implement `countAdditionalBJets()` in copyBranch.C:
  - [x] Find top quarks (pdgId=6)
  - [x] Find b-quarks from top decay (pdgId=5, mother=top)
  - [x] Count b-quarks NOT from top with pT>20, |η|<2.5
- [x] Add filtering logic in `Select()` for ttbar samples
- [x] Test compilation ✅
- [x] Fix Makefile library paths (CMSSW_10_6_20 -> CMSSW_14_1_0_pre4)
- [ ] Validate with small test run

**Committed**: `0478d65d` - feat: Add TTBB samples with ttbar overlap removal

---

## Phase 5: Full Processing (2018 FIRST)

### Stage 1: Object Selection - 2018
- [x] Build objectSelectionOptimized
- [x] Fix library paths in job scripts (export LD_LIBRARY_PATH)
- [x] Fix RoccoR path in setEnv_newNew.sh (CMSSW_10_6_20 → CMSSW_14_1_0_pre4)
- [x] Fix PUWeightCal.C pileup path (CMSSW_10_6_20 → CMSSW_14_1_0_pre4)
- [x] Submit jobs for 2018 TTBB samples (all 3 decay modes)
- [x] Submit jobs for 2018 ttbar samples (with overlap removal)
- [x] TTBB output files being created (verified)
- [x] ttbar output files being created (verified)
- [ ] Verify ttbar event counts reduced (overlap removal working)
- [ ] Wait for all jobs to complete (~1398 remaining)

### Stage 2: Variable Production - 2018
- [ ] Build makeVariables_goodCode
- [ ] Submit jobs for 2018
- [ ] Verify output ntuples

### Stage 3: Histogram Production - 2018
- [ ] Build writeHistGood
- [ ] Submit nominal jobs for 1tau0l (2018)
- [ ] Verify TTBB histograms exist

### Stage 4: Validation Plots - 2018
- [ ] Run pl.py for 2018
- [ ] Verify TTBB appears correctly in plots

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
- Status: ~1398 jobs remaining (down from 3826)
