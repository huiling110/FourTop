# VLL Integration Plan

**Task**: Integrate VLL (Vector-Like Lepton) options into runCombineAll.py
**Created**: 2025-12-03
**Last Updated**: 2025-12-03 13:25
**Status**: Implementation Complete, Code Refined
**Commits**: `a1ba3107`, `e606c987`, `5c28b581`

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

### Code Change Based on Validation (commit e606c987)

Removed redundant VLL options from `runCombineSig()` for AsymptoticLimits:
```python
# Before: significanceCommand = '... --name {name}{vll}'.format(..., vll=vll_opts)
# After:  significanceCommand = '... --name {name}'.format(...)
```

VLL options now only applied to Significance calculation (where r=0 baseline matters).

### Educational Tutorial (commit 5c28b581)

Created `hua/combine/asymptotic_limits_tutorial.py` demonstrating step-by-step CLs calculation.

## MC Toys Validation

**Purpose**: Verify AsymptoticLimits results with exact MC toy calculation (HybridNew method).

**Method**: Run `combine -M HybridNew` which uses pseudo-experiments instead of asymptotic approximations.

| Method | Approach | Speed | Accuracy |
|--------|----------|-------|----------|
| AsymptoticLimits | Analytical approximation | Fast (~10 min) | Good for high stats |
| HybridNew | MC pseudo-experiments | Slow (~hours) | Exact |

**Commands**:
```bash
# Asymptotic (already done)
combine -M AsymptoticLimits workspace.root

# MC Toys
combine -M HybridNew workspace.root --LHCmode LHC-limits --saveToys --saveHybridResult -T 500 --expectedFromGrid 0.5
```

**Expected**: Results should be consistent within statistical uncertainties.

## Detailed AsymptoticLimits with Intermediate Values

**Purpose**: Understand the internal calculation steps of AsymptoticLimits.

**Verbose flags**:
- `-v 3`: Verbose level 3 (show fit details)
- `--cminDefaultMinimizerStrategy 0`: Faster minimization
- `--X-rtd MINIMIZER_verbose=3`: Detailed minimizer output

**Key intermediate values to observe**:
1. Global fit result (best-fit r and nuisance parameters)
2. Profile likelihood at each r value scanned
3. CLs calculation at each point
4. Interpolation to find 95% CL limit

**Command**:
```bash
combine -M AsymptoticLimits workspace.root -v 3 --name _verbose 2>&1 | tee limit_verbose.log
```

## Reference

- Reference file: `/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/runCombineAll.py`
- Approved plan: `/afs/ihep.ac.cn/users/h/huahuil/.claude/plans/flickering-cooking-starling.md`
