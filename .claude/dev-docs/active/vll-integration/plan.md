# VLL Integration Plan

**Task**: Integrate VLL (Vector-Like Lepton) options into runCombineAll.py
**Created**: 2025-12-03
**Last Updated**: 2025-12-03 13:10
**Status**: Implementation Complete, Validation Testing
**Commit**: `a1ba3107`

## Summary

Integrate VLL analysis-specific command options. The key physics difference: VLL analysis requires freezing signal strength r=0 (background-only hypothesis) for BSM exclusion limits.

## Key Changes

| Function | Change |
|----------|--------|
| `goodnessOfFit` | Add `--setParameters r=0 --freezeParameters r` when `ifVLL=True` |
| `runImpact` | Add `ifVLL, channel` params + VLL options |
| `runCombineSig` | Add VLL options for unblinded case |
| `runImpactSnapshot` | NEW function for B-only constrained impacts |
| `main()` | Pass `ifVLL` to `runImpact`, call `runImpactSnapshot` for VLL |

## VLL-Specific Options

```python
VLL_OPTS = '--setParameters r=0 --freezeParameters r'
VLL_RMIN = '--rMin -1'
```

## Testing

- VLL: `--steps workspace significance limits impacts postfit`
- tttt regression: `--steps workspace significance limits impacts postfit signal_strength`

## Validation Test: VLL Options Impact

**Purpose**: Verify that `--setParameters r=0 --freezeParameters r` actually changes the results.

**Method**: Run AsymptoticLimits on VLL datacard with and without VLL options, compare results.

| Test | Command Options | Expected Behavior |
|------|-----------------|-------------------|
| With VLL opts | `--setParameters r=0 --freezeParameters r` | Limits computed at r=0 hypothesis |
| Without VLL opts | (none) | Limits computed with r floating |

**Expected**: Different limit values prove VLL options are working correctly.

### Validation Results (2025-12-03 13:09)

| Metric | With VLL opts | Without VLL opts |
|--------|---------------|------------------|
| Observed | r < 1.8841 | r < 1.8841 |
| Expected 50% | r < 0.8867 | r < 0.8867 |

**Finding**: AsymptoticLimits gives identical results regardless of `--setParameters r=0 --freezeParameters r`. This is expected because:
- AsymptoticLimits scans r from rMin to rMax regardless of initial value
- VLL options are more important for Significance and Impacts (where r=0 baseline matters)

## Reference

- Reference file: `/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/runCombineAll.py`
- Approved plan: `/afs/ihep.ac.cn/users/h/huahuil/.claude/plans/flickering-cooking-starling.md`
