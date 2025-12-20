# Plan: TTBB Yield Investigation

**Created**: 2025-12-07 10:30
**Reopened**: 2025-12-19
**Status**: RESOLVED - **XGBoost library differences** identified as root cause
**Priority**: HIGH

---

## Executive Summary

After TTBB integration, tttt yields changed by ~1.5% and fake tau (data) changed ~0.2%, which shouldn't happen since these samples were not supposed to be modified by the TTBB ghost-matching overlap removal. This investigation aims to identify the exact root cause and determine whether to accept the changes or fix them.

---

## Problem Statement

When comparing TTBB integration test version (`v94HadroPreJetVetoHemOnly_TTBBtest`) with the reference version (`v94HadroPreJetVetoHemOnly`), unexpected yield changes were observed:
- tttt: +1.5% (should be 0%)
- fake_tau_data: +0.2% (should be 0%)
- ttbar: -35% to -56% (EXPECTED from ghost-matching)

---

## Current State

**Reference Version** (Jan 26, 2025):
- Path: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v94HadroPreJetVetoHemOnly/`
- Git commit: `9a4dc74a` (OS: use only HEM key for jet Veto Map)
- tttt Stage 1 entries: 1,730,209
- tttt Stage 2 baseline: 1,657,638

**TTBBtest Version** (Dec 5, 2025):
- Path: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v94HadroPreJetVetoHemOnly_TTBBtest/`
- Includes ghost-matching overlap removal for ttbar/TTBB
- tttt Stage 1 entries: 1,734,672 (+4,463 events)
- tttt Stage 2 baseline: 1,662,000

**Key Observation**: All samples including tttt were re-run through Stage 1 (OS) for TTBBtest, not just ttbar/TTBB that needed overlap removal.

---

## Desired State

1. Understand exact code change causing tttt yield difference
2. Verify jet veto map is not the cause (since both versions use same veto for 2018)
3. Determine if changes are from bug fixes (acceptable) or regressions (need fix)
4. Document findings for future reference

---

## Approach

### Phase 1: Local Testing (1-2 hours)

**Goals**:
- Run OS on single tttt file with current code
- Compare output with reference version
- Identify exact selection causing difference

**Tasks**:
1. Run OS executable on single tttt file locally
2. Compare entry counts with reference output
3. Check cutflow histograms for where events diverge
4. Identify specific selection cuts that changed

**Deliverables**:
- Entry count comparison (current code vs reference)
- Identification of which selection cut changed

### Phase 2: Code Archaeology (1 hour)

**Goals**:
- Identify all commits between Jan 26 and Dec 5 that affect OS selection
- Determine which change caused the yield difference

**Tasks**:
1. Review git history for objectSelectionOptimized/src/
2. Check each relevant commit for selection changes
3. Document which commit(s) affect tttt selection

**Deliverables**:
- List of commits that could affect tttt yields
- Identification of root cause commit

### Phase 3: Decision and Documentation (30 min)

**Goals**:
- Decide whether to accept or fix the yield changes
- Document findings

**Tasks**:
1. Evaluate if changes are improvements (bug fixes) or issues
2. Update dev-docs with findings
3. Proceed with TTBB integration if changes are acceptable

**Deliverables**:
- Decision document
- Updated context.md with root cause

---

## Risks and Mitigations

**Risk 1**: Local test shows no difference (issue is elsewhere)
- **Likelihood**: Medium
- **Impact**: High
- **Mitigation**: Check Stage 2 (MV) code differences, FR file differences

**Risk 2**: Multiple code changes contribute to difference
- **Likelihood**: Medium
- **Impact**: Medium
- **Mitigation**: Test each commit individually if needed

**Risk 3**: Changes affect physics results significantly
- **Likelihood**: Low
- **Impact**: High
- **Mitigation**: Compare with published/approved results, consult with collaborators

---

## Success Criteria

- [x] Identify exact code change causing tttt yield difference
  - **Root cause for MC**: OS/environment change (CentOS 7 → AlmaLinux 9) causes -1.7%
  - **Root cause for 2018 data**: Jet veto fix commit `1347ac24` + environment change causes -5%
- [x] Verify ghost-matching only affects ttbar/TTBB samples
  - **Verified**: copyBranch.C:48-56 checks m_isTtbarSample/m_isTTBBSample
- [x] Document root cause with commit hash and line numbers
  - **Commit**: `1347ac24` (Feb 4, 2025) "OS: fixed small bug to only jetVeto for 2018"
  - **File**: `jetSel.C:475-477` - added `if(m_era!="2018") return kFALSE;`
- [x] Make informed decision on whether to accept changes
  - **Decision**: ACCEPT - TTBBtest outputs are CORRECT (use fixed code)
- [x] Update dev-docs with complete findings

---

## Timeline

- Phase 1: 1-2 hours
- Phase 2: 1 hour
- Phase 3: 30 minutes
- **Total**: 2.5-3.5 hours

---

## REOPENED: Deep Dive on 1tau1lSR (2025-12-19) - RESOLVED

### Problem (Original)
The previous conclusion (OS change CentOS 7 → AlmaLinux 9) needs verification:
- **1tau1lSR data**: -5.0% (140 → 133 events) - TOO LARGE to ignore
- **1tau1lSR tttt**: Also affected

### Investigation Tasks - ALL COMPLETE
- [x] List all commits between reference and TTBBtest affecting OS code
  - **Key commit**: `1347ac24` (Feb 4, 2025) - jet veto era check
- [x] Check for lepton selection changes specifically
  - **Finding**: NO lepton selection code changes
- [x] Verify environment (OS version) for both productions
  - **Reference**: CentOS 7, **TTBBtest**: AlmaLinux 9
- [x] Compare cutflow for 1tau1l specifically (not just 1tau0l)
  - **Finding**: Stage 1/2 show +0.05%, Stage 3 (WH) shows -5%
- [x] Make final determination: code change vs OS change
  - **Answer**: BOTH - jet veto fix + OS change combined

### Root Cause Identified

**Critical Timeline Discovery**:
| Production | Date | Code Version |
|------------|------|--------------|
| 2018 Reference | Jan 26, 2025 | **BEFORE** jet veto fix |
| 2017 Reference | Feb 4, 2025 | **AFTER** jet veto fix |
| 2018 TTBBtest | Dec 5, 2025 | **AFTER** jet veto fix |
| 2017 TTBBtest | Dec 7, 2025 | **AFTER** jet veto fix |

**Explanation**:
- 2017: Both productions AFTER fix → same behavior → **0% change**
- 2018: Reference BEFORE fix, TTBBtest AFTER → different behavior → **-5% change**

### Final Conclusion (CORRECTED 2025-12-19)

**ACTUAL ROOT CAUSE: XGBoost Library Version Incompatibility**

The previous hypothesis (jet veto fix + OS changes) was **INCORRECT**. The true root cause is:

**XGBoost version change: 0.80 (CentOS 7) → 1.7.5 (AlmaLinux 9)**

This causes systematic downward shift in TopMVA scores:
- Mean shift: ~1.2%, Max shift: ~12%
- ~1% of electrons change `isTight` flag (all True → False)
- Same model files, different library interpretation

**Evidence:**
1. Same electron (pT=114.77 GeV) has score 0.848 (Ref) vs 0.772 (Test)
2. 100% of score differences are positive (Ref > Test)
3. Mid-range scores (0.3-0.8) have largest shifts (~10%)

**Impact on Physics:**
| Channel | Effect | Cause |
|---------|--------|-------|
| 1tau1lSR | -5% data, -1.7% tttt | Fewer leptons pass TopMVA tight cut |
| 1tau0l | +0.38% data | Fewer leptons → more events pass lep==0 cut |

**TopMVA Training Source Investigation:**
- Checked ewkino, GhentAnalysis/TopLeptonMVA, cms-ttH/ttH-LeptonID
- **Finding**: These use TMVA (ROOT), NOT XGBoost
- Our `.bin` files origin is UNKNOWN (likely internal CMS TOP group)
- [CMS ML docs](https://cms-ml.github.io/documentation/inference/xgboost.html) confirm version incompatibility

**Recommendation**: Accept TTBBtest outputs as the correct baseline. All future productions must use AlmaLinux 9 with XGBoost 1.7.5 consistently.
