# TTBB Integration - Task Checklist

**Last Updated**: 2025-12-05
**Current Phase**: Phase 2 - Sample Preparation

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

## Phase 4: Overlap Subtraction Implementation 🔄 IN PROGRESS

### copyBranch.C
- [ ] Add `countAdditionalBJets()` function declaration to copyBranch.h
- [ ] Implement `countAdditionalBJets()` in copyBranch.C:
  - [ ] Find top quarks (pdgId=6)
  - [ ] Find b-quarks from top decay (pdgId=5, mother=top)
  - [ ] Count b-quarks NOT from top with pT>20, |η|<2.5
- [ ] Add filtering logic in `Select()` for ttbar samples
- [ ] Test compilation
- [ ] Validate with small test run

---

## Phase 5: Full Processing

### Stage 1: Object Selection
- [ ] Build objectSelectionOptimized
- [ ] Submit jobs for 2018
- [ ] Submit jobs for 2017
- [ ] Submit jobs for 2016postVFP
- [ ] Submit jobs for 2016preVFP
- [ ] Verify TTBB output files created
- [ ] Verify ttbar event counts reduced (overlap removal working)

### Stage 2: Variable Production
- [ ] Build makeVariables_goodCode
- [ ] Submit jobs for all years
- [ ] Verify output ntuples

### Stage 3: Histogram Production
- [ ] Build writeHistGood
- [ ] Submit nominal jobs for 1tau0l
- [ ] Submit nominal jobs for 1tau1l
- [ ] Submit nominal jobs for 1tau2l
- [ ] Submit systematic jobs
- [ ] Verify TTBB histograms exist

### Stage 4: Templates and Datacards
- [ ] Run addJESTemplatesToHistFile.py
- [ ] Run addTemplateNew.py
- [ ] Run smooth_systematics_fourTops.py
- [ ] Run writeDatacard.py (with TTBB systematics)
- [ ] Run writeCombinationDatacard.py
- [ ] Run statistical analysis

---

## Phase 6: Validation

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
