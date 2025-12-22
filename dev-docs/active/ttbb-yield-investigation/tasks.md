# Tasks: TTBB Yield Investigation

**Created**: 2025-12-07 10:30
**Last Updated**: 2025-12-22
**Status**: **COMPLETE** - XGBoost library version (0.80 vs 1.7.5) **EXPERIMENTALLY VERIFIED** as root cause

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

---

## Phase 4: REOPENED Investigation (2025-12-19)

### Task 4.1: Cross-Era Comparison
- [x] Compare 2017 vs 2018 1tau1lSR data yields

**Results:**
| Year | Reference | TTBBtest | Diff | % Change |
|------|-----------|----------|------|----------|
| 2018 data | 145 | 133 | -12 | **-8.28%** |
| 2017 data | 114 | 109 | -5 | **-4.39%** |
| 2018 tttt | 4.924 | 3.467 | -1.458 | **-29.60%** |
| 2017 tttt | 3.290 | 2.357 | -0.933 | **-28.36%** |

### Task 4.2: Stage-by-Stage Comparison
- [x] Check Stage 2 (MV) tree entries

**Stage 2 (MV) tttt entries:**
- 2018: 1,657,638 → 1,661,996 (+0.26%)

**Key Finding:** At Stage 2, TTBBtest has MORE entries (+0.26%), but at Stage 3 WH 1tau1lSR, TTBBtest has FEWER events (-30%).

### Task 4.3: WH Production Dates
- [x] Check when WH outputs were produced

| Version | Date | Path |
|---------|------|------|
| Reference | April 10, 2025 | variableHists_v0BDT1tau1lAddMCFakeT |
| TTBBtest | December 11, 2025 | variableHists_v0BDT1tau1l_TTBBtest |

### Task 4.4: Code Archaeology (WH)
- [x] Check WH code changes between Apr-Dec 2025

**Commits affecting writeHistGood/:**
- `17514fa5` (Aug 3): Changed 2nd lepton pT cut 13→20 GeV - **ONLY affects 1tau2l**
- No changes found affecting 1tau1l selection

### CORRECTED COMPARISON (using v3BDT1tau1lV18_fakeTauDataDriven as reference)

**Previous comparison used wrong reference** (v0BDT1tau1lAddMCFakeT). Corrected comparison:

| Sample | 2017 Change | 2018 Change |
|--------|-------------|-------------|
| **Data** | **0.00%** (109→109) | **-5.00%** (140→133) |
| **tttt** | -1.70% (2.40→2.36) | -1.70% (3.53→3.47) |

### KEY FINDINGS (2025-12-19)

1. **tttt shows consistent -1.7% across both years** → Likely OS/environmental effect
2. **2017 data shows NO change** → Code is working correctly
3. **2018 data shows -5% drop** → 2018-SPECIFIC issue, NOT OS change

### ROOT CAUSE ANALYSIS

The 2018-specific data drop could be due to:
- HEM veto map differences (only applied to 2018)
- Different jet veto map versions
- Input data file differences at Stage 1

The jet veto code confirms HEM veto is 2018-only:
```cpp
Bool_t JetSel::jetVetoMap(Double_t eta, Double_t phi){
    if(m_era!="2018"){
        return kFALSE;  // Only applied for 2018
    }
    ...
}
```

### CONCLUSION

1. **OS change hypothesis PARTIALLY CONFIRMED for MC**: The consistent -1.7% drop in tttt for both years is consistent with floating-point precision differences from OS migration.

2. **2018 data issue is SEPARATE**: The -5% drop in 2018 data (while 2017 data unchanged) suggests a 2018-specific issue, possibly related to HEM veto or jet veto map differences.

3. **Recommendation**: Investigate the 2018 jet veto map differences between reference and TTBBtest Stage 1 outputs.

### Task 4.5: Deep Dive Investigation (2025-12-19 continued)
- [x] Compare Stage 1 (OS) tree entries for 2018 data
- [x] Compare Stage 2 (MV) tree entries for 2018 data
- [x] Check Stage 1 production dates for reference vs TTBBtest
- [x] Identify root cause commit

**Stage Comparison Results (2018 Data):**
| Stage | Reference | TTBBtest | Diff | % Change |
|-------|-----------|----------|------|----------|
| Stage 1 (OS) | 269,807 | 269,953 | +146 | **+0.054%** |
| Stage 2 (MV) | 230,780 | 230,900 | +120 | **+0.052%** |
| Stage 3 (WH) 1tau1lSR | 140 | 133 | -7 | **-5.00%** |

**Key Finding**: Stage 1/2 show MORE entries in TTBBtest, but Stage 3 shows FEWER. The -5% drop happens at WH selection.

**Production Dates:**
| File | Reference | TTBBtest |
|------|-----------|----------|
| 2017 Stage 1 | Feb 4, 2025 | Dec 7, 2025 |
| 2018 Stage 1 | Jan 26, 2025 | Dec 5, 2025 |

**CRITICAL FINDING**: The jet veto fix was committed on Feb 4, 2025:
- 2018 Reference (Jan 26): Produced BEFORE the jet veto fix
- 2018 TTBBtest (Dec 5): Produced AFTER the jet veto fix
- 2017 Reference (Feb 4): Produced AFTER the jet veto fix (same day)
- 2017 TTBBtest (Dec 7): Produced AFTER the jet veto fix

---

## FINAL ROOT CAUSE IDENTIFIED

### Commit 1347ac24 (Feb 4, 2025): "OS: fixed small bug to only jetVeto for 2018"

This commit added an era check to the HEM jet veto function:

```cpp
Bool_t JetSel::jetVetoMap(Double_t eta, Double_t phi){
    if(m_era!="2018"){
        return kFALSE;  // ADDED: Skip veto for non-2018 eras
    }
    // HEM1516 veto logic...
}
```

**Before fix**: All eras called jetVetoMap → potential issues with non-2018 veto maps
**After fix**: Only 2018 calls jetVetoMap → correct behavior

### Why 2017 shows 0% change but 2018 shows -5%:

1. **2017 Reference vs TTBBtest**: BOTH produced after the fix (Feb 4 and Dec 7)
   - Both correctly skip HEM veto for 2017
   - Same code, same behavior → **0% net change** (small fluctuations cancel out)

2. **2018 Reference vs TTBBtest**: Reference produced BEFORE fix (Jan 26), TTBBtest AFTER (Dec 5)
   - Different code versions for HEM veto handling
   - Different environments (CentOS 7 vs AlmaLinux 9, correctionlib versions)
   - Combined effect → **-5% systematic shift**

### tttt MC shows -1.7% for both years:
This is consistent with OS/environmental differences (floating-point precision) affecting both years equally, since the jet veto fix doesn't affect MC (MC doesn't have HEM failure).

---

## CONCLUSIONS

1. **2017 data 0% change**: Expected - both productions used same code (after jet veto fix)

2. **2018 data -5% change**: Due to combination of:
   - Jet veto code fix (1347ac24)
   - Environment change (CentOS 7 → AlmaLinux 9)
   - Possibly different correctionlib versions handling HEM veto maps

3. **tttt MC -1.7%**: OS/environmental floating-point differences, NOT code changes

4. **Action**: The 2018 Stage 1 outputs should be regenerated on the NEW system (AlmaLinux 9) to have consistent reference. The current TTBBtest outputs are CORRECT (using the fixed code).

**Investigation Status**: RESOLVED

### Final Summary (2025-12-19)

Root causes identified and documented:

1. **tttt MC (-1.70% both years)**: OS/environment change (CentOS 7 → AlmaLinux 9) - acceptable
2. **2017 1tau1lSR data (0.00%)**: No change because both productions were after jet veto fix
3. **2018 1tau1lSR data (-5.00%)**: Jet veto fix (1347ac24) + OS changes - 2018 reference was produced before fix
4. **1tau1l CR (-2.5% both years)**: Lepton selection boundary effects from OS changes

**Key verification**: 2017 1tau1lSR shows 0% change (109→109) while 2018 shows -5% (140→133), confirming the jet veto fix is relevant for 2018.

**Recommendation**: Accept TTBBtest outputs as the correct baseline. The 2018 reference was produced with buggy code (before jet veto era check fix)

---

## Phase 5: Channel Comparison Verification (2025-12-19)

### Comprehensive Stage-by-Stage Comparison

| Stage | 2017 Data | 2018 Data |
|-------|-----------|-----------|
| **Stage 1 (OS)** | +0.061% (176,075→176,183) | +0.054% (269,807→269,953) |
| **Stage 2 (MV)** | +0.064% (149,589→149,685) | +0.052% (230,780→230,900) |

| Stage 3 (WH) | 2017 Data | 2018 Data |
|--------------|-----------|-----------|
| **1tau0lSR** | **+0.05%** (2002→2003) | **+0.38%** (3162→3174) |
| **1tau0lCRMR** | **+0.22%** (15134→15168) | **+0.18%** (23146→23188) |
| **1tau1lSR** | **0.00%** (109→109) | **-5.00%** (140→133) |
| **1tau1lCR12** | **-2.42%** (413→403) | **-2.48%** (605→590) |

### KEY DISCOVERY: Jet Veto Hypothesis is WRONG!

1. **Stage 1 & 2**: Both years show POSITIVE differences (~+0.05-0.06%)
   - TTBBtest has MORE entries than Reference
   - Consistent with OS/environment floating-point changes

2. **1tau0l Channel**: POSITIVE differences (+0.05% to +0.38%)
   - Same direction as Stage 1/2 ✓
   - Amplified by tight SR cuts (expected behavior)

3. **1tau1l Channel**: NEGATIVE differences (-2.4% to -5%)
   - **OPPOSITE direction from Stage 1/2!** ✗
   - Sign FLIPS between Stage 2 (+0.05%) and Stage 3 (-2.5% to -5%)
   - This CANNOT be explained by jet veto fix

### Corrected Root Cause Analysis

The issue is **NOT** in Stage 1 (OS) jet veto. The issue is **specific to 1tau1l WH selection**.

Possible causes at WH step:
- Different WH code between Reference (Sep 2025) and TTBBtest (Dec 2025)
- Different selection logic for 1tau1l vs 1tau0l
- BDT version difference (v3BDT vs v0BDT) affecting selection

### Next Steps (SUPERSEDED by Phase 6 findings)
- [x] Check WH code changes between Sep-Dec 2025 for 1tau1l - NOT the cause
- [x] Compare 1tau1l vs 1tau0l selection code - NOT the cause
- [x] Verify BDT version doesn't affect selection (only binning) - CONFIRMED

---

## Phase 6: Deep Verification of Variable Definitions (2025-12-19)

### Task 6.1: Verify OS and MV Code Changes
- [x] List all commits affecting objectSelectionOptimized between Jan 26 - Dec 5, 2025
- [x] List all commits affecting makeVariables_goodCode between Apr 10 - Dec 7, 2025
- [x] Check for variable definition changes in MV

**Findings:**
- OS commits: 60+ commits, key ones: jet veto fix (1347ac24), XGBoost API fix (736b0720), TES bug fix (d2a30a14)
- MV commits: Only 1 relevant (e309047b - JES comment change, no functional impact)
- MV variable bug fix (50182812 - Mar 11) was BEFORE both reference and TTBBtest

### Task 6.2: Direct Comparison of Stage 2 Variable Values
- [x] Compare branch structure between Reference and TTBBtest
- [x] Compare variable values for same events

**Findings:**
- Branch structure: IDENTICAL (498 branches in both)
- Entry counts: Ref=1,657,638, Test=1,661,996 (+0.26%)
- **Variable mismatches for SAME events (1000 events checked):**
  - lepTopMVAT_num: 8 (0.8%)
  - jets_num: 2 (0.2%)
  - bjetsM_num: 1 (0.1%)
  - bjetsM_leptons_minDeltaR: 8 (0.8%) - correlated with lepton count

### Task 6.3: Trace Lepton Differences to Stage 1
- [x] Compare Stage 1 lepton counts for same events
- [x] Identify which electrons are disappearing

**Findings:**
- 45 mismatches in 5000 events (0.9%)
- ALL mismatches: electrons DISAPPEARING in TTBBtest
- Electron pT values that disappear: 114.8 GeV, 87.4 GeV, 23.1 GeV - NOT near threshold!

### Task 6.4: Identify Root Cause - XGBoost TopMVA
- [x] Compare electron TopMVA scores between versions
- [x] Verify XGBoost API changes

**CRITICAL FINDINGS:**

| Event | Ref TopMVA | Test TopMVA | Diff | Effect |
|-------|------------|-------------|------|--------|
| 292756 | 0.848 | 0.772 | -0.076 | isTight: True→False |
| Mean (100 events) | - | - | 0.0126 | - |
| Max diff | - | - | 0.123 | - |

**Root Cause**: XGBoost library/API differences between CentOS 7 and AlmaLinux 9 cause:
1. Different TopMVA scores (mean diff ~1.3%, max diff ~12%)
2. ~2% of electrons have isTight flag changes
3. Some electrons completely removed from collection

### Task 6.5: Update Documentation
- [x] Update context.md with XGBoost root cause
- [x] Update tasks.md with Phase 6 findings

---

## FINAL CONCLUSIONS (2025-12-19)

### Root Causes Identified

| Issue | Root Cause | Evidence |
|-------|-----------|----------|
| **Lepton count differences** | XGBoost TopMVA score shift | Same electron, score 0.848→0.772 |
| **1tau1l -5% data** | Fewer leptons pass TopMVA tight | lepTopMVAT_num differs in 0.8% of events |
| **1tau0l +0.38% data** | Fewer leptons → more lep==0 | Consistent with lepton reduction |
| **tttt -1.7%** | Combination of lepton + floating-point | Both channels affected |

### Key Technical Details

1. **XGBoost API change** (commit 736b0720):
   - Old: `XGBoosterPredict(booster, dtest, 0, 0, &out_len, &f)`
   - New: `XGBoosterPredict(booster, dtest, 0, 0, 0, &out_len, &f)`

2. **Production timeline**:
   - Reference: Jan 26, 2025 (CentOS 7, old XGBoost)
   - TTBBtest: Dec 5, 2025 (AlmaLinux 9, new XGBoost)

### Recommendations

1. **Do NOT dismiss as "floating-point precision"** - this is a significant ML inference shift
2. **Regenerate all Stage 1 outputs** on AlmaLinux 9 for consistency
3. **Document XGBoost version** used for each production
4. **Consider freezing XGBoost version** in the environment setup

---

## Phase 7: Detailed XGBoost Investigation (2025-12-19 continued)

### Task 7.1: Comprehensive TopMVA Score Comparison
- [x] Compare all electron TopMVA scores between versions
- [x] Analyze score distribution by score range
- [x] Verify direction of score shift

**Findings:**
- 6,149 electrons compared across 31,395 common events
- **100% of differences are positive** (Ref > Test) - systematic downward shift
- Mean shift: 0.012 (1.2%), Max shift: 0.124 (12.4%)
- Mid-range scores (0.3-0.8) have largest shifts (~10%)
- High scores (>0.95) have smallest shifts (~0.4%)

### Task 7.2: Investigate XGBoost Library Versions
- [x] Check Makefile for XGBoost paths
- [x] Compare library versions between environments

**Findings:**

| Environment | XGBoost Version | Path |
|-------------|-----------------|------|
| CentOS 7 (Ref) | **0.80** | `slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh` |
| AlmaLinux 9 | **1.7.5** | `el9_amd64_gcc14/external/py3-xgboost/1.7.5-...` |

**Major version jump** from 0.80 to 1.7.5 (~4 years of development).

### Task 7.3: Verify Model Files
- [x] Check if model files changed

**Finding:** Model files are **IDENTICAL** (same files from June 2024). The difference is purely in library interpretation.

### Task 7.4: Quantify Impact on Physics Selection
- [x] Count isTight flag changes

**Findings:**
- isTight threshold: 0.81
- Total isTight changes: 64 (1.04%)
- All changes are True → False (0 False → True)
- Electrons near threshold (score 0.75-0.85): 44 cross from pass to fail

---

## FINAL RECOMMENDATIONS

### Option 1: Regenerate All Stage 1 on AlmaLinux 9 (Recommended)

**Pros:**
- Consistent environment going forward
- Can use latest bug fixes and features
- No need to maintain CentOS 7 compatibility

**Cons:**
- Requires rerunning all Stage 1 jobs (~1-2 weeks of jobs)
- Invalidates previous reference outputs

**Steps:**
1. Regenerate all Stage 1 outputs for all years (2016-2018) on AlmaLinux 9
2. Regenerate Stage 2 (MV) outputs
3. Regenerate Stage 3 (WH) outputs
4. Update reference paths in config files

### Option 2: Fix XGBoost Version Mismatch

**Approach:** Use a compatible XGBoost version on AlmaLinux 9 that produces same results as 0.80

**Challenges:**
- XGBoost 0.80 may not be available for el9
- Would require extensive testing to verify compatibility
- May not be possible due to API changes

### Option 3: Accept Systematic Shift (NOT Recommended)

**Why not recommended:**
- ~1% lepton efficiency change is significant for physics
- Different effective selection between old and new runs
- Would need to document and justify the systematic difference

---

## Verification Commands

```bash
# Check XGBoost version in Makefile
grep XGBOOST objectSelectionOptimized/Makefile

# Check available XGBoost versions
ls /cvmfs/cms.cern.ch/el9_amd64_gcc14/external/py3-xgboost/
ls /cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/

# Compare TopMVA scores between files (Python)
# See context.md for full comparison script
```

---

## Phase 8: Why XGBoost Scores Differ (2025-12-19)

### Task 8.1: Investigate XGBoost API Changes
- [x] Check new API documentation for XGBoosterPredict
- [x] Compare old vs new API signatures

**Findings:**
- Old API (0.80): `XGBoosterPredict(handle, dmat, option_mask, ntree_limit, out_len, out_result)`
- New API (1.7.5): `XGBoosterPredict(handle, dmat, option_mask, ntree_limit, training, out_len, out_result)`
- The `training` parameter affects DART booster dropout behavior

### Task 8.2: Research XGBoost Version Compatibility
- [x] Search for known issues with version compatibility
- [x] Check official documentation

**Findings from XGBoost GitHub and Docs:**

1. **Model format**: Our `.bin` files use old binary format. XGBoost recommends JSON format for cross-version compatibility.

2. **CPU predictor optimizations**: [Issue #6350](https://github.com/dmlc/xgboost/issues/6350) confirms CPU predictor optimizations can cause different floating-point errors.

3. **32-bit vs 64-bit**: XGBoost uses 32-bit exponentiation in sigmoid. Mixing with 64-bit calculations causes differences.

4. **Major version changes**: 0.80 → 1.0 → 1.7 includes:
   - Hist algorithm improvements
   - DMatrix refactoring
   - Prediction caching changes
   - JSON model format introduction (1.0)

### Task 8.3: Determine if This is Expected Behavior
- [x] Analyze whether differences are "bugs" or "known incompatibility"

**Conclusion:**
The ~1.2% mean score difference (up to 12% max) is **EXPECTED BEHAVIOR** for XGBoost 0.80 → 1.7.5 migration. This is documented in XGBoost issues and is due to:
- Algorithm optimizations
- Floating-point handling changes
- Model format interpretation differences

This is **NOT a bug** in our code - it's a known limitation of XGBoost cross-version compatibility.

---

## FINAL VERDICT

### Root Cause Summary

| Factor | Impact |
|--------|--------|
| XGBoost version | 0.80 → 1.7.5 (major jump) |
| Model format | Old binary (.bin) |
| API change | Added `training` parameter |
| Predictor optimizations | Different FP handling |
| Result | ~1.2% systematic score shift |

### What Should Be Done

**Immediate (Required):**
1. Accept that Reference (CentOS 7 + XGBoost 0.80) and TTBBtest (AlmaLinux 9 + XGBoost 1.7.5) are **incompatible**
2. Choose ONE environment as the baseline going forward

**Short-term (Recommended):**
1. Regenerate all Stage 1 outputs on AlmaLinux 9 with XGBoost 1.7.5
2. This ensures consistent TopMVA evaluation across all samples

**Long-term (Best Practice):**
1. Retrain TopMVA models using XGBoost 1.7.5
2. Export as JSON format for future compatibility
3. Document XGBoost version in production logs

### Sources

- [XGBoost Issue #3664: Different predictions between versions](https://github.com/dmlc/xgboost/issues/3664)
- [XGBoost Issue #6350: CPU predictor differences](https://github.com/dmlc/xgboost/issues/6350)
- [XGBoost Model IO Documentation](https://xgboost.readthedocs.io/en/stable/tutorials/saving_model.html)
- [XGBoost 1.7 Release Notes](https://xgboost.readthedocs.io/en/release_1.7.0/)

---

### Commits between Jan 26 and Dec 5 affecting OS:
```
1347ac24 Feb 4: OS: fixed small bug to only jetVeto for 2018  ← NOT the root cause (disproved)
736b0720: OS: small fix to XGBoosterPredict() to make it work in OS9
91aa3d6e Dec 5: Ghost-matching overlap removal (only affects ttbar/TTBB)
```

---

## Phase 9: TopMVA Training Source Investigation (2025-12-19)

### Task 9.1: Investigate ewkino Repository
- [x] Check https://github.com/NielsVdBossche/ewkino for TopMVA implementation

**Findings:**
- **Ewkino does NOT calculate TopMVA** - it reads pre-computed values from NanoAOD
- Source: `objects/src/LightLepton.cc:41`
  ```cpp
  _leptonMVATOPUL( leptonReader._Lepton_TOPLeptonMVAUL[leptonIndex] )
  ```
- This is different from our approach where we calculate TopMVA on-the-fly using XGBoost

### Task 9.2: Check GhentAnalysis/TopLeptonMVA
- [x] Check https://github.com/GhentAnalysis/TopLeptonMVA for training code

**Findings:**
- **Uses TMVA (ROOT's toolkit), NOT XGBoost directly**
- Training file: `Train/train.py` uses `TMVA::Factory` with BDTG method
- Weight format: `.weights.xml` (TMVA format)
- Files: `TMVA_BDTG_TOP_elec_2018.weights.xml`, etc.

### Task 9.3: Check cms-ttH/ttH-LeptonID
- [x] Check https://github.com/cms-ttH/ttH-LeptonID

**Findings:**
- Uses TMVA, exports `.weights.xml` files
- Data folder contains: `el_BDTG.weights.xml`, `mu_BDTG.weights.xml`
- Repository last updated 2019

### Task 9.4: Determine Origin of Our XGBoost .bin Files
- [x] Check our weight files
- [x] Try to find training source

**Our weight files:**
```
objectSelectionOptimized/input/TopLeptonMVA/mvaWeights_new/
├── el_TOPUL18_XGB.weights.bin  (361,626 bytes, June 5, 2024)
├── mu_TOPUL18_XGB.weights.bin  (293,249 bytes, June 5, 2024)
└── ... (all eras)
```

**Origin: UNKNOWN** - The exact training source for these XGBoost binary files could NOT be found publicly.

**Possible origins:**
1. Internal CMS TOP group training (not public)
2. Conversion from TMVA models to XGBoost
3. Custom training by Ghent/ttH groups

### Task 9.5: Check CMS ML Documentation
- [x] Review https://cms-ml.github.io/documentation/inference/xgboost.html

**Key Findings:**

| SCRAM_ARCH | XGBoost Version |
|------------|-----------------|
| slc7_amd64_gcc700 | **0.80** |
| slc7_amd64_gcc900 | **1.3.3** |
| el9_amd64_gcc14 | **1.7.5** (our current) |

**CMS ML Warning:**
> "Different major versions have different behavior."

---

## Phase 9 Conclusions

### Why We Cannot Determine Training XGBoost Version

1. **No public training repository** uses XGBoost for TopMVA
2. **GhentAnalysis/TopLeptonMVA** uses TMVA (ROOT), not XGBoost
3. **Our .bin files** are in XGBoost binary format, but origin is unknown
4. **Ewkino** reads TopMVA from NanoAOD, doesn't calculate it

### Key Difference: Our Approach vs Others

| Framework | TopMVA Approach |
|-----------|-----------------|
| **FourTop (us)** | Calculate on-the-fly using XGBoost C API |
| **Ewkino** | Read from NanoAOD branch `Lepton_TOPLeptonMVAUL` |
| **GhentAnalysis** | Use TMVA BDTG with XML weights |

Our approach of on-the-fly XGBoost evaluation is unique and requires XGBoost version consistency.

### Final Recommendation

Since we cannot determine the original training XGBoost version:

**Option 1: Accept Current State (Recommended)**
- All future productions use XGBoost 1.7.5 consistently
- Accept TTBBtest as the new baseline
- Document that Reference (XGBoost 0.80) is incompatible

**Option 2: Request Information**
- Contact TOP PAG for original training scripts/version
- May take time and may not be available

**Option 3: Retrain**
- Retrain TopMVA with XGBoost 1.7.5
- Export in JSON format for future compatibility
- Most work but ensures reproducibility

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

---

## Phase 10: CentOS7 XGBoost 0.80 Verification Test (2025-12-20)

**Goal**: Verify that XGBoost library version (0.80 vs 1.7.5) is the root cause of yield differences by running OS step on CentOS7.

**Version String**: `v95XGB080testOS7`
**Era**: 2018 only
**Channel**: 1tau1l

### Task 10.1: Code Changes for CentOS7 Compatibility
- [x] Switch XGBoost API in usefulFunc.C (6 params → 5 params)
- [x] Switch XGBoost paths in Makefile to 0.80
- [x] Create setEnv_centos7.sh environment script
- [x] Create analysis_config_1tau1l_XGB080test.yaml

### Task 10.2: Build and Test
- [x] Build on CentOS7 using `hep_container shell CentOS7`
- [x] Local test on single file (XGBoost 0.80 loads successfully)

### Task 10.3: Submit and Run Pipeline
- [x] Modify makeJob_OS_fromRuobing2.py for CentOS7 (`-os CentOS7`)
- [x] Submit OS jobs for 2018 (3502 jobs submitted, cluster 66243965-66244036)
- [x] Wait for OS jobs to complete
- [x] Run Stage 2 (MV) - 72 jobs submitted (cluster 66246744+)
- [ ] Wait for Stage 2 to complete
- [ ] Generate fake backgrounds (Stage 2.4)
- [ ] Run Stage 3 (WH) histograms

### Task 10.4: Compare Results
- [x] **Stage 1 (OS) Entry Comparison - BREAKTHROUGH!**
- [ ] Run pl.py for visual comparison
- [ ] Compare final 1tau1lSR yields

### BREAKTHROUGH RESULT (2025-12-20) - **CONFIRMED**

**Stage 1 (OS) Tree Entry Comparison:**

| Sample | XGB080 Test (CentOS7) | Reference | TTBBtest (AlmaLinux9) | XGB080 vs Ref |
|--------|----------------------|-----------|----------------------|---------------|
| **tttt** | **1,730,209** | **1,730,209** | 1,734,672 | **0 (+0.000%)** |
| **Data** | **269,807** | **269,807** | 269,953 | **0 (+0.000%)** |

**XGB080 Test matches Reference EXACTLY - zero difference!**

This **conclusively confirms**:
1. ✅ **XGBoost library version (0.80 vs 1.7.5) IS the root cause**
2. ✅ Same code + Same XGBoost version = Identical results
3. ✅ TTBBtest differs due to XGBoost 1.7.5 (not floating-point precision)
4. ✅ Previous "OS floating-point" hypothesis was **WRONG**

**Stage 2 (MV)**: Completed (on CentOS7)
**Stage 2.4 (Fake)**: Completed
**Stage 3 (WH)**: BLOCKED - MV code version mismatch

### WH Blockage Investigation (2025-12-22)

**Initial error**: WH jobs report missing branches (`MET_phi`, `bjetsPNM_num`, etc.)

**Verification**: Checked MV file directly with Python/ROOT:
```
newtree;70: 1,657,638 entries, 498 branches
  MET_phi: EXISTS
  bjetsPNM_num: EXISTS
  jets_btagsPT_: EXISTS

newtree;69: 1,650,618 entries, 498 branches
  MET_phi: EXISTS
  bjetsPNM_num: EXISTS
  jets_btagsPT_: EXISTS
```

**Finding**: All "missing" branches ACTUALLY EXIST in both tree cycles. The WH job failure has a different root cause (under investigation).

Since Stage 1 + Stage 2 already **conclusively confirms** the hypothesis, WH verification is supplementary.

### Final Outcome (Stage 1 + Stage 2 Confirmation)

**Stage 1 (OS) Comparison:**
| Metric | Reference | TTBBtest | XGB080 Test |
|--------|-----------|----------|-------------|
| tttt | 1,730,209 | 1,734,672 (+0.26%) | **1,730,209 (0.000%)** |
| Data total | 269,807 | 269,953 (+0.05%) | **269,807 (0.000%)** |

**Stage 2 (MV) Comparison (2025-12-22):**
| Metric | Reference | TTBBtest | XGB080 Test |
|--------|-----------|----------|-------------|
| tttt | 1,657,638 | 1,661,996 (+0.26%) | **1,657,638 (0.000%)** |
| Data total | 230,780 | 230,900 (+0.05%) | **230,780 (0.000%)** |

**Both Stage 1 AND Stage 2 show XGB080 Test = Reference EXACTLY (0.000%)!**

**Conclusion**: XGBoost 0.80 (CentOS7) produces IDENTICAL results to Reference at both OS and MV stages. The yield differences in TTBBtest are caused by XGBoost 1.7.5 (AlmaLinux9).

### Files Modified
- `objectSelectionOptimized/src/usefulFunc.C` - XGBoost API (line 105-106)
- `objectSelectionOptimized/Makefile` - XGBoost paths (lines 28-33)
- `setEnv_centos7.sh` - NEW CentOS7 environment
- `config/analysis_config_1tau1l_XGB080test.yaml` - NEW test config
- `objectSelectionOptimized/jobs/makeJob_OS_fromRuobing2.py` - hep_sub -os CentOS7

---

## Phase 11: WH TFile Caching Bug Fix (2025-12-22)

### Bug Description
WH jobs failed with "Tree 'Runs' not found" causing `processScale: inf` despite the Runs tree existing in the file.

### Root Cause
ROOT's `TFile::Open()` caches file connections by path. When `calQCDScaleNor` and `calPDFScaleNor` called `TFile::Open()` on the same path as `m_file`, they received the same cached TFile pointer. Their `file->Close()` calls then closed the file owned by `m_file`, causing `getGenSum()` to fail.

**Bug Origin**: Commit `3f947cbf` (July 14, 2025) changed `m_file` from constructor-body assignment to inline `std::unique_ptr` initialization. This was done to fix a "corrupted size vs. prev_size" memory issue, but inadvertently introduced the caching bug.

### Fix Applied
- Added `TFile*` overloads for `calQCDScaleNor` and `calPDFScaleNor` that don't close the file
- Updated `treeAnalyzer.C` to use `m_file.get()` instead of opening new files
- Commit: `eaf05636`

### Verification
```bash
# Test run successful:
genWeightSumInitial: 106025  # Correct (was 0)
processScale: 0.0075447       # Correct (was inf)
tttt_1tau1lSR_BDT: 80,144 entries, sum=3.527  # Correct (was inf)
```

### Files Modified
- `writeHistGood/include/functions.h` - Added TFile* overload declarations
- `writeHistGood/src/functions.C` - Added TFile* overload implementations
- `writeHistGood/src/treeAnalyzer.C` - Use m_file.get() for scale functions
