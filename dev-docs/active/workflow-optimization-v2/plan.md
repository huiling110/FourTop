# Plan: Workflow Optimization V2 - V21 Combination

**Created**: 2025-12-11
**Status**: ACTIVE
**Priority**: HIGH
**Branch**: addVLL
**Parent Task**: workflow-optimization (Phases 1-8 complete)

---

## Executive Summary

Complete Run2 four-top analysis with V21 combination (3 channels × 4 years):
1. **Testing** (2018): 1tau1l ✓, 1tau2l
2. **Production**: 1tau1l → 1tau0l → 1tau2l (all 4 years each)
3. **Smoothing**: Per-channel after 4 years complete
4. **Combination**: Per-channel years → 3-channel final
5. **Fix bash permissions** (immediate priority)

---

## Execution Order

```
Phase 1: Testing (2018, no smoothing)
├── 1tau1l 2018 ✓ nearly complete
└── 1tau2l 2018 (create config + run from WH)

Phase 2: 1tau1l Production
├── 2016preVFP, 2016postVFP, 2017 (+ 2018 done)
├── Smoothing (all 4 years)
└── Year combination

Phase 3: 1tau0l Production
├── 2016preVFP, 2016postVFP, 2017, 2018
├── Smoothing (all 4 years)
└── Year combination

Phase 4: 1tau2l Production (Stage 3 WH onwards)
├── 2016preVFP, 2016postVFP, 2017 (+ 2018 done)
└── Year combination (smoothing TBD)

Phase 5: V21 Combination
└── Combine 1tau1l + 1tau0l + 1tau2l
```

---

## Key Decisions

**Bash Permissions** ✅:
- Switch to deny-list approach: `Bash(*)` + strong deny rules
- Eliminates unnecessary prompts

**1tau2l Starting Point** ✅:
- OS/MV data exists → start from Stage 3 (WH)
- No TTBB integration needed

**Smoothing Strategy** ✅:
- Per-channel after each channel's 4 years complete
- Test on 1tau1l first

**Combination Approach** ✅:
- Incremental: combine years per-channel, then combine 3 channels
- Uses `hua/combine/runCombineAll.py`

---

## Implementation Parts

### Part A: Fix Bash Permissions ⚡ IMMEDIATE
- Backup and simplify settings.json
- Keep deny rules, replace allow with `Bash(*)`
- Clear settings.local.json
- **Goal**: Zero prompts for normal commands

### Part B: Complete 1tau1l 2018
- Monitor WH systematic jobs (TES/MET/EleScale)
- Run Stage 4.1-4.4 pipeline
- Skip smoothing (do after all 4 years)

### Part C: Create 1tau2l 2018
- Create config from 1tau1l template
- Run WH nominal (Stage 3)
- Run Stage 4 pipeline (no TTBB)

### Part D: Production (Multi-Year)
- D1: 1tau1l (3 more eras + smoothing + combination)
- D2: 1tau0l (4 eras + smoothing + combination)
- D3: 1tau2l (3 more eras + combination)

### Part E: V21 Combination
- Verify per-channel combinations
- Run 3-channel combination
- Generate final results

### Part F: Dev-Docs
- Create structure ✓
- Track progress in tasks.md
- Update workflow state

---

## Critical Files

**To Create**:
- `config/analysis_config_1tau2l_TTBBtest.yaml`
- Dev-docs files (this file, context.md, tasks.md)

**To Modify**:
- `.claude/settings.json` (simplify permissions)
- `.claude/settings.local.json` (clear)
- `plotting/smooth_systematics_fourTops.py` (add TTBB support if needed)

**To Verify**:
- `hua/combine/runCombineAll.py` (multi-year/channel support)

---

## Success Criteria

**Phase 1** (2018 Testing):
- ✅ Zero permission prompts
- ✅ 1tau1l 2018 complete with systematics
- ✅ 1tau2l 2018 nominal validated

**Phase 2-4** (Production):
- ✅ Each channel: all 4 years + smoothing + year-combo

**Phase 5** (V21):
- ✅ 3-channel combination complete
- ✅ Final results: significance, limits, postfit, impacts

---

## Open Questions

1. **1tau2l systematics**: Run with `systematics: true` for production?
2. **1tau2l smoothing**: Needed/applicable without TTBB?
3. **runCombineAll.py**: Supports `--combine-years` and `--combine-channels`?

---

## Estimated Timeline

- Part A: <1 hour
- Part B: 2-3 hours
- Part C: 1-2 hours
- Part D1: ~6 days
- Part D2: ~8 days
- Part D3: ~3 days
- Part E: 1-2 days

**Total**: ~3-4 weeks (mostly automated job execution)

---

**Last Updated**: 2025-12-11
