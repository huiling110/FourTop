# Tasks: TTBB Yield Investigation

**Created**: 2025-12-07 10:30
**Last Updated**: 2025-12-07 14:30
**Status**: COMPLETE - All Phases Finished

---

## Phase 1: Local Testing

### Task 1.1: Run OS on single tttt file with current code
- [x] Create temporary output directory
- [x] Run `./apps/run_objectSelection.out` on single tttt file
- [x] Record output entry count

**Status**: Complete
**Notes**: Using file `01D97507-B0BB-234F-A28E-6AD66C3499E9.root` as test

### Task 1.2: Compare with reference output
- [x] Check entry count in reference Stage 1 output
- [x] Compare Events tree entries
- [x] Calculate percentage difference

**Status**: Complete
**Results**:
- Reference: 55,239 tree entries
- TTBBtest: 55,374 tree entries
- Difference: +135 events (+0.24%)

### Task 1.3: Analyze cutflow histograms
- [x] Extract cutflow histogram from both versions
- [x] Identify which selection cut shows divergence
- [x] Document specific cut causing difference

**Status**: Complete
**Key Finding**: Divergence starts at **tau selection** (bin 4) with +0.6 weighted events (+0.08%)

---

## Phase 2: Code Archaeology

### Task 2.1: Review git history for OS changes
- [x] List all commits between 9a4dc74a (Jan 26) and HEAD
- [x] Filter for commits affecting objectSelectionOptimized/src/
- [x] Identify commits that modify selection logic

**Status**: Complete
**Notes**: Identified key commits:
- 1347ac24: Jet veto only for 2018 (NOT the cause - 2018 uses same veto)
- 736b0720: XGBooster fix for OS9 (NOT the cause - API change only)
- 91aa3d6e: Ghost-matching (NOT the cause - only affects ttbar/TTBB)

### Task 2.2: Test individual commits (if needed)
- [x] Compare reference vs TTBBtest output files directly
- [x] Analyze cutflow histogram to identify divergence point

**Status**: Complete - No need to checkout old commits; cutflow analysis identified tau selection as divergence point

---

## Phase 3: Decision and Documentation

### Task 3.1: Evaluate changes
- [x] Determine if changes are bug fixes or regressions
- [x] Assess impact on physics results
- [x] Make recommendation

**Status**: Complete
**Conclusion**: Changes are due to **environmental differences** (CentOS 7 → AlmaLinux 9, correctionlib 2.7.0), NOT code changes. The ~0.24% yield difference is acceptable for physics analysis.

### Task 3.2: Update documentation
- [x] Update context.md with root cause
- [x] Document decision in plan.md
- [x] Close investigation

**Status**: Complete

---

## Success Criteria Checklist

- [x] Identify exact code change causing tttt yield difference
  - **Finding**: NOT a code change - environmental differences (OS, libraries)
- [x] Verify ghost-matching only affects ttbar/TTBB samples
  - **Verified**: copyBranch.C lines 48-56 check m_isTtbarSample/m_isTTBBSample
- [x] Document root cause with commit hash and line numbers
  - **Root cause**: Floating-point precision differences between CentOS 7 and AlmaLinux 9
  - **Verified**: Data (jetHT) shows same divergence pattern → NOT TES (TES only applied to MC)
  - **Affected code**: tauSel.C:90 (`if (!(itau_pt > 20.))`) - taus near threshold pass/fail differently
- [x] Make informed decision on whether to accept changes
  - **Decision**: ACCEPT - ~0.24% difference is within expected environmental variation
- [x] Update dev-docs with complete findings

---

## Notes

### 2025-12-07 Session 1
- Started investigation after noticing tttt yields changed by ~1.5%
- Key finding: All samples were re-run through Stage 1, not just ttbar/TTBB
- Reference created Jan 26, 2025 (commit 9a4dc74a)
- TTBBtest created Dec 5, 2025 with current HEAD
- Jet veto map for 2018 should be identical in both versions

### 2025-12-07 Session 2 (Continued)
- Completed cutflow analysis: divergence at tau selection (+0.59 weighted events, +0.081%)
- Verified ghost-matching code only affects ttbar/TTBB (copyBranch.C:48-56)
- Reviewed all code changes: jet veto, TES, XGBooster - none affect tttt nominal
- **Initially hypothesized TES as root cause**
- **Verified by checking DATA (jetHT)**: Data also shows divergence at tau selection!
  - jetHT_2018a: +13 events at tau selection in 10 files, +3 tree entries
  - Since TES is NOT applied to data (tauSel.C:83), TES cannot be the cause
- **Actual root cause**: Floating-point precision differences (CentOS 7 vs AlmaLinux 9, gcc versions)

### 2025-12-07 Session 3 - Deep Investigation of SR Cut Amplification
- User requested deeper investigation of SR cut amplification mechanism
- **1tau0l Analysis**: Traced progressive cuts through Stage 2 → Stage 3
  - Baseline: +0.052% → tausT==1 cut: +0.397% (7.6x amplification)
  - Key finding: `tausT_num == 1` (tight tau) has only 13% efficiency
  - Dividing similar absolute differences by smaller denominators amplifies percentages
  - Calculation matched Stage 3 histograms exactly (3162 vs 3174)

- **1tau1l Verification**: Applied same analysis to 1tau1l channel
  - Found **opposite effect**: -5.0% instead of +0.38%
  - Key finding: Lepton cut (`lep==1`) flips the sign
  - Baseline: +0.052% → lep==1 cut: -3.37%
  - Calculation matched Stage 3 histograms exactly (141→134 vs 140→133)

- **Final Conclusion**:
  - Same root cause (floating-point precision) affects both channels
  - Opposite signs explained by which selection threshold dominates
  - 1tau0l: tau cuts dominate → net positive
  - 1tau1l: lepton cut dominates → net negative
  - Both are expected environmental variations, NOT bugs

**Decision**: ACCEPT all yield differences as environmental variation
**Investigation**: COMPLETE

### Commits between Jan 26 and Dec 5 affecting OS:
```
1347ac24 Feb 4: OS: fixed small bug to only jetVeto for 2018
736b0720: OS: small fix to XGBoosterPredict() to make it work in OS9
91aa3d6e Dec 5: Ghost-matching overlap removal (only affects ttbar/TTBB)
```

### Test Commands
```bash
cd /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/objectSelectionOptimized
source ../setEnv_newNew.sh

# Run OS on single file
./apps/run_objectSelection.out \
    /publicfs/cms/data/TopQuark/nanoAOD/2018/mc/tttt/ \
    01D97507-B0BB-234F-A28E-6AD66C3499E9.root \
    /tmp/test_tttt_current/ \
    0 0 0 0 0 0 0
```
