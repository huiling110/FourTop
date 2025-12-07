# Plan: TTBB Yield Investigation

**Created**: 2025-12-07 10:30
**Status**: COMPLETE
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

- [ ] Identify exact code change causing tttt yield difference
- [ ] Verify ghost-matching only affects ttbar/TTBB samples
- [ ] Document root cause with commit hash and line numbers
- [ ] Make informed decision on whether to accept changes
- [ ] Update dev-docs with complete findings

---

## Timeline

- Phase 1: 1-2 hours
- Phase 2: 1 hour
- Phase 3: 30 minutes
- **Total**: 2.5-3.5 hours
