# VLL Integration Plan

**Task**: Integrate VLL (Vector-Like Lepton) options into runCombineAll.py
**Created**: 2025-12-03
**Last Updated**: 2025-12-03 12:25
**Status**: Implementation Complete, Testing in Progress
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

## Reference

- Reference file: `/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/runCombineAll.py`
- Approved plan: `/afs/ihep.ac.cn/users/h/huahuil/.claude/plans/flickering-cooking-starling.md`
