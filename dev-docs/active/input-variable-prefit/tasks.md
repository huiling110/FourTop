# Task Status

## Implementation

| Task | Status | Notes |
|------|--------|-------|
| Modify addTemplateNew.py | Done | Added `--variables` arg |
| Modify datacards.py | Done | Added `variable` and `region` params |
| Modify writeDatacard.py | Done | Added `--variable` and `--region` args |
| Create plot_prefit_inputvar.py | Done | Linear y-axis, no legend counts |
| Create run_inputvar_prefit_pipeline.py | Done | Automation script |
| Fix datacards.py column width | Done | 22→25 chars for CRMR region names |
| Add --keep-sys-dirs to addJES calls | Done | CRITICAL for multi-variable workflow |

## Testing - 1tau0l

| Variable | SR | CRMR | VR | Notes |
|----------|-----|------|-----|-------|
| tausT_1pt | ✓ 7298/6951 | ✓ 54512/50408 | ✓ 8649/8041 | Complete |
| tausF_1jetPt | ✓ 7227/6886 | ✓ 53953/49931 | ✓ 8576/7964 | Complete |
| jets_HT | ✓ 7275/6889 | ✓ 55024/50492 | ✓ 8751/8067 | Complete |
| tausF_1prongNum | - | ✓ 55508/51021 | - | CRMR only |
| tausT_prongNum | - | ✗ | - | tttt=0 in CRMR (zero signal) |

## Testing - 1tau1l

| Variable | CR2 | Notes |
|----------|-----|-------|
| tausT_1jetEtaAbs | Pending | WH jobs running |

## CRITICAL: --keep-sys-dirs

**addJES deletes systematic directories by default!**

When running addJES for input variables, ALWAYS use `--keep-sys-dirs`:
```bash
python3 plotting/addJESTemplatesToHistFile.py \
    --config CONFIG.yaml --era ERA --mode variables \
    --variables VAR --execute --quiet --keep-sys-dirs
```

If you ran addJES without this flag, systematic dirs are deleted and you must resubmit WH:
```bash
cd writeHistGood/jobs/
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era ERA --systematic complete --mode variables
```

## Session Notes

### 2026-01-26 (session 4)

**Plot styling improvements:**
- Fixed x-axis binning: combine FitDiagnostics loses original range
- Added VARIABLE_BINNING dict to restore correct x-axis values
- Added VARIABLE_XLIM dict for zooming to relevant range
- Fixed prong number: shift bins by -0.5 so prong 1,3 appear at 1,3 (not 1.5,3.5)
- Moved region/Pre-fit label to top-left, on separate lines
- Increased legend fontsize from 15 to 17
- Removed data count from legend

**WH jobs status:**
- 1tau1l: All 4 eras submitted (~17,771 jobs total)
- 1tau2l: All 4 eras submitting

### 2026-01-25 (session 3)

**1tau0l prefit plots COMPLETE:**
- tausT_1pt: SR, CRMR, VR ✓
- tausF_1jetPt: SR, CRMR, VR ✓
- jets_HT: SR, CRMR, VR ✓
- tausF_1prongNum: CRMR ✓

**tausT_prongNum issue:**
- CRMR has tttt=0 (zero signal events in control region)
- writeDatacard.py fails when signal process removed
- Used tausF_1prongNum instead for prong number plot

**1tau1l WH jobs submitted:**
- 2018: 4441 jobs (mode=variables)
- 2017/2016preVFP/2016postVFP: Submitting

**Next:** tausT_1jetEtaAbs CR2 for 1tau1l (after WH complete)

### 2026-01-25 (session 2)

- Created plot_prefit_inputvar.py for input variable prefit plots
- Added region support (SR, CRMR, VR) to writeDatacard.py
- Fixed column width bug in datacards.py (CRMR names too long)
- Created automation script run_inputvar_prefit_pipeline.py
- Successfully plotted tausT_1pt for all 3 regions (SR, CRMR, VR)
- **CRITICAL BUG DISCOVERED**: addJES deleted systematic dirs (no --keep-sys-dirs used)
- Updated Stage 5 skill with --keep-sys-dirs warnings
- Need to resubmit WH for 1tau0l systematics

## Files Created

- `plotting/plotting_paper/plot_prefit_inputvar.py` - New plotting script
- `scripts/run_inputvar_prefit_pipeline.py` - Automation script
- `hua/combine/combinationV23/run2_1tau0l_tausT_1pt_{SR,CRMR,VR}/` - Combination dirs

## Next Steps

1. ~~**1tau0l prefit plots**~~ DONE
2. **Wait for 1tau1l WH jobs** (~1 hour per era, 4 eras = ~4 hours)
3. 1tau1l: addJES, addTemplate, writeDatacard for tausT_1jetEtaAbs CR2
4. 1tau1l: Run combine and generate prefit plot

## Completed 1tau0l Prefit Plots

| Variable | Regions | Location |
|----------|---------|----------|
| tausT_1pt | SR, CRMR, VR | `combinationV23/run2_1tau0l_tausT_1pt_{SR,CRMR,VR}/` |
| tausF_1jetPt | SR, CRMR, VR | `combinationV23/run2_1tau0l_tausF_1jetPt_{SR,CRMR,VR}/` |
| jets_HT | SR, CRMR, VR | `combinationV23/run2_1tau0l_jets_HT_{SR,CRMR,VR}/` |
| tausF_1prongNum | CRMR | `combinationV23/run2_1tau0l_tausF_1prongNum_CRMR/` |

## 1tau1l Target

| Variable | Region | Status |
|----------|--------|--------|
| tausT_1jetEtaAbs | CR2 | WH jobs submitted (17,771 total) |

## 1tau2l Target

| Variable | Region | Status |
|----------|--------|--------|
| bjetsM_num | CR3 | WH jobs submitting |

## WH Job Counts (mode=variables)

| Channel | 2018 | 2017 | 2016preVFP | 2016postVFP | Total |
|---------|------|------|------------|-------------|-------|
| 1tau1l | 4441 | 4447 | 4443 | 4440 | 17,771 |
| 1tau2l | - | - | - | - | Submitting |
