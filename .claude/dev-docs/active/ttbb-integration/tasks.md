# TTBB Integration - Task Checklist

**Last Updated**: 2025-12-05 15:30
**Current Phase**: Phase 5 - Stage 1 COMPLETE for 2018, ready for Stage 2

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
- [x] TTBB output files created and verified
- [x] ttbar output files created and verified
- [x] All 3826 jobs completed (hep_q shows 0 jobs)
- [x] Verify ttbar event counts reduced (overlap removal working) - **VERIFIED**
  - ~2.04% of ttbar events have additional b-jets to remove
  - m_isTtbarSample correctly detected in job logs
  - TTBB samples confirmed to have 6-8 additional b-quarks per event

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

### Session 4 (2025-12-05 15:30)
- All Stage 1 jobs completed (3826 jobs finished, hep_q shows 0 remaining)
- Output verified at `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v94HadroPreJetVetoHemOnly_TTBBtest/mc/`
- TTBB outputs: Hadronic (66M), SemiLeptonic (56M, 15 files), 2L2Nu (12M)
- ttbar_1l output: 570M, 391 files
- Updated Claude Code settings with comprehensive Linux commands
- Next: Verify overlap removal is working by comparing event counts
