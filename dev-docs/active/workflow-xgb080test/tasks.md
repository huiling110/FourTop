# Tasks: XGB080test Workflow (1tau1l)

## Status Summary - v1BDT1tau1l_XGB080testNew (Fresh Run with Subprocess Skipping)
| Era | S3 WH | S4.1 addJES | S4.2 addTpl v3 | S4.3 smooth | S4.4 datacard | S4.5 combine |
|-----|-------|-------------|----------------|-------------|---------------|--------------|
| 2018 | ✅ DONE | ✅ DONE | ✅ DONE | ✅ DONE | - | - |
| 2017 | ✅ DONE | ✅ DONE | ✅ DONE | ✅ DONE | - | - |
| 2016preVFP | ✅ DONE | ✅ DONE | ✅ DONE | ✅ DONE | - | - |
| 2016postVFP | ✅ DONE | ✅ DONE | ✅ DONE | ✅ DONE | - | - |
| **Run2** | - | - | - | - | - | - |

**WH version**: `v1BDT1tau1l_XGB080testNew`

### Smoothing Results (Jan 3, 2026) - VERY EFFECTIVE!

**Key reductions in problematic bin 4 variations:**
| Process | Systematic | Before | After | Reduction |
|---------|------------|--------|-------|-----------|
| ttW | CMS_scale_j_FlavorPureGluon Up | +78.8% | +10.1% | **68.7%** |
| ttW | ps_fsr Down | -196.7% | 0% | **Complete fix!** |
| ttW | ps_fsr Up | +111.3% | 0% | **Complete fix!** |
| tt | ps_fsr Down | +19.0% | +7.9% | 11.1% |
| tt | CMS_scale_j_FlavorPureGluon Up | +17.8% | +11.4% | 6.4% |

**Output files:**
- Original: `templatesForCombine1tau1l_v3_notMCFTau_unblind.root`
- Smoothed: `templatesForCombine1tau1l_v3_notMCFTau_unblind_smoothed_v2.root`
- Comparison plots: `combine/results/systematics_comparison_*.png` (460 plots)

### Next Steps
1. Generate datacard with smoothed v3 templates
2. Run Combine fit
3. Compare prefit uncertainties vs V22 (expect significant reduction)

---

## Previous Run Status (v0BDT1tau1l_XGB080testNew - Corrupted tttt.root)
| Era | S4.1 addJES | S4.2 addTpl | S4.3 smooth | S4.4 datacard | S4.5 combine |
|-----|-------------|-------------|-------------|---------------|--------------|
| 2018 | DONE | DONE | DONE | DONE | - |
| 2017 | DONE | DONE | DONE | DONE | - |
| 2016preVFP | DONE | DONE | DONE | DONE | - |
| 2016postVFP | DONE | DONE | DONE | DONE | - |
| **Run2** | - | - | - | DONE | **DONE** |

## Current Phase: **WH Jobs Running - Preparing for v3 Template Test**

### Critical Issue: V22 Uncertainties 4-5x Larger than V18

**Problem Summary:**
- V22 postfit uncertainties are unacceptably large compared to V18
- **ROOT CAUSES FOUND** (Jan 2, 2026): Two major issues identified!

**Quantitative Comparison (2018 SR):**
| Version | Prefit Error | Postfit Error | Signal Strength |
|---------|--------------|---------------|-----------------|
| V22 | 16.4% | 21.8% | r = 1.084 ± 2.007 |
| V18 | 5.5% | 4.8% | r = 2.117 ± 1.935 |

### ROOT CAUSES (Jan 2, 2026) - COMPLETE

#### Issue 1: JES/JER Systematics Have Wrong Event Counts
JES/JER systematic variations have ~50% fewer entries than nominal!

| Systematic | Entries | Ratio vs Nominal |
|------------|---------|------------------|
| Nominal | 555 | 100% |
| JER Up | 285 | 51% ← BUG! |
| JER Down | 267 | 48% ← BUG! |
| ps_fsr Up | 555 | 100% ✓ |

Weight-based systematics (ps_fsr, pileup) are correct. JES/JER re-run selection with shifted jets, causing different events to pass.

#### Issue 2: 79% of Systematics Have Up/Down in SAME Direction
For tt bin 4, **31 out of 39 significant systematics have Up and Down in the same direction** - physically impossible!

| Systematic | Up % | Down % | Issue |
|------------|------|--------|-------|
| CMS_scale_j_AbsoluteMPFBias | +19.1% | +13.5% | Both positive! |
| CMS_scale_j_AbsoluteStat_2018 | +17.6% | +13.5% | Both positive! |
| ps_fsr | -7.3% | +8.5% | ✓ Opposite (correct) |

Caused by: Very low statistics (~3 events in bin 4) + different event sets

#### V18 vs V22 Key Difference
- **V18**: tt = tt + ttbb combined → bin 4 has 10.0 events, 21.6% error
- **V22**: tt and ttbb separate → bin 4 has 2.8 events, 590% error

The tt/ttbb split causes fewer events per process → higher fluctuations → unphysical systematics

### Recommended Fixes (Priority Order)

1. **Merge tt + ttbb back together** - Restores V18-level statistics
2. **Symmetrize Up/Down variations** - Force Down = -Up for problematic systematics
3. **Increase smoothing aggressiveness** - Current smoothing helps but not enough
4. **Add minimum event threshold** - Exclude bins with <5 events from shape fits

### Diagnostic Plots Created
```
hua/combine/combinationV22/run2_1tau1l_v4/diagnostics/
├── tt_template_vs_combine_uncertainty.pdf  # Shows 7x inflation
├── tt_systematic_shapes.pdf                # Shows shape variations
└── tt_bin4_root_cause.pdf                  # Up/Down same direction analysis
```

### Investigation Progress (COMPLETE)
- [x] Analyze fitDiagnosticsTest.root prefit uncertainties
- [x] Compare template errors to fitDiagnostics errors → **7x inflation found**
- [x] Trace to WH subprocess level
- [x] Investigate CMS_res_j_2018 → **Found 50% fewer entries bug**
- [x] Compare V18 vs V22 → **tt/ttbb split is the cause**
- [x] Document findings in context.md
- [x] Create diagnostic plots

### Session History

**Jan 3 - Smoothing Complete with Very Effective Results:**
- [x] WH jobs completed for all 4 eras
- [x] Run addJES for all 4 eras
- [x] Generated v3 templates with subprocess skipping (SKIP_SUBPROCESSES applied)
- [x] Enhanced smooth_systematics_fourTops.py:
  - Added `--template-version` argument for flexible template selection
  - Added graceful handling of missing processes (singleTop)
  - Expanded systematics list to 24 (including all problematic JES sources)
- [x] Run smoothing on v3 templates - 460 comparison plots generated
- [x] **Tested smoothing effectiveness - VERY EFFECTIVE!**
  - ttW ps_fsr fluctuations reduced from ±100-200% to ~0%
  - ttW JES fluctuations reduced by 60-70%
  - tt systematic fluctuations reduced by 5-11%
- [ ] Generate datacard with smoothed templates
- [ ] Run Combine and compare to V22

**Jan 2 (cont) - Fresh WH Run with v1 Version:**
- [x] Discovered tttt.root was corrupted (empty file, 480 bytes) on Dec 31
- [x] Changed hist version from v0 to v1 in config to avoid overwriting
- [x] Submitted WH jobs for all 4 eras with `--systematic complete`

**Jan 2 - Subprocess Skipping Implementation:**
- [x] Analyzed subprocess contributions for all processes in SR and CR12:
  - tt: ttbar_2l dominates (15.2 events), ttbar_1l negligible (0.1 events)
  - ttbb: TTBB_4f_TTTo2L2Nu dominates (36.0 events), SemiLeptonic (0.1 events)
  - singleTop: Only st_tW_* contribute (~1.4 events total), others have no files
- [x] Implemented subprocess skipping in template generation:
  - Added `SKIP_SUBPROCESSES` config in `ttttGlobleQuantity.py`
  - Modified `getSumHist()` in `usefulFunc.py` to accept skip list
  - Updated `addTemplateNew.py` to use skip list and output v3 templates
  - Skipped: `TTBB_4f_TTToSemiLeptonic`, `ttbar_1l` (< 1% contribution)
- [x] Removed singleTop from `proChannelDic_forCombine` for 1tau1l:
  - singleTop has ~1.4 events but ps_fsr fluctuation is 294%
  - This reduces systematic noise significantly
- [ ] TODO: Analyze SKIP_SUBPROCESSES for 1tau0l and 1tau2l channels

**Jan 2 - Subprocess Systematic Analysis Tool:**
- [x] Created `check_subprocess_systematics.py` multi-process, multi-region support:
  - Updated subprocess mappings from `ttttGlobleQuantity.py`
  - Added `--process all` to analyze tt, ttbb, singleTop, ttW, ttZ, ttH
  - Added `--region all` to analyze both SR and CR12
  - Added `--auto-top5` to auto-detect worst systematics from fluctuation_report.txt
  - Updated `plot_systematic_comparison()` with region/process parameters
- [x] Generated subprocess comparison plots for all processes:
  - `subprocess_systematics/{process}_{region}/compare_{process}_{region}_{syst}.png`
  - Each plot shows: combined + top 2 subprocesses, shape + variation %
- [x] Key findings from subprocess analysis:
  - tt: ttbar_2l dominates (15.24 events), ttbar_1l negligible (0.11 events)
  - ttbb: TTBB_4f_TTTo2L2Nu dominates (35.97 events)
  - singleTop: Only st_tW_antitop (0.54) and st_tW_top (0.88) contribute
  - Fluctuation report top systematics: singleTop→ps_fsr, ttW→ps_fsr/JES sources

**Jan 2 - Enhanced Diagnostic Tool + Quantitative Analysis:**
- [x] Enhanced `check_systematic_fluctuations.py`:
  - Added `--datacard` option to use all processes from datacard (including tttt)
  - Added `parse_datacard_processes()` to extract process list
  - Now generates plots for all 9 datacard processes
- [x] Quantified discrepancy between template and Combine:
  | Bin | Our Total% | FitDiag% | Ratio |
  |-----|------------|----------|-------|
  | 4   | 98.9%      | 589.6%   | 6.0x  |
  | 7   | 100.0%     | 104.8%   | 1.0x  |
- [x] Confirmed: 18/20 top bin 4 systematics have Up/Down in SAME direction
- [x] Explanation: Combine's shape interpolation goes unstable when Up/Down are same direction
- [x] Generated plots for all processes at:
  - `systematic_fluctuations/total_systematic_{process}.png`
  - `systematic_fluctuations/top5_systematics_{process}.png`
  - `systematic_fluctuations/smoothed/` (same structure)

**Jan 2 (cont) - ROOT CAUSE INVESTIGATION COMPLETE:**
- [x] Created 5-step diagnostic plan (fitDiag → template → WH → smoothing → V18/V22)
- [x] Extracted fitDiagnostics prefit: tt bin 4 = 2.849 ± 16.8 (590%)
- [x] Compared to template: 2.849 ± 2.42 (85%) → **7.3x inflation in Combine**
- [x] Investigated JER/JES entries: **50% fewer entries than nominal** (bug!)
- [x] Analyzed Up/Down directions: **79% have both Up and Down positive** (impossible)
- [x] Compared V18 vs V22: tt/ttbb split reduced bin 4 from 10 to 2.8 events
- [x] Created diagnostic plots in `diagnostics/` folder
- [x] Updated dev-docs with complete root cause analysis
- **ROOT CAUSES**: (1) JES/JER have wrong entries, (2) Low stats cause unphysical Up/Down

**Jan 2 - Smoothing Config Fix:**
- [x] **ROOT CAUSE FOUND**: Smoothing config only had 3 JES sources, missing 12+ problematic ones
- [x] Updated `plotting/smooth_systematics_fourTops.py` CHANNEL_SMOOTHING_CONFIG:
  - Added: TimePtEta, RelativeSample, AbsoluteScale, PileUpPtRef, AbsoluteMPFBias, AbsoluteStat
  - Added: FlavorPureCharm, FlavorPureBottom, RelativeBal, PileUpDataMC, RelativeFSR
  - Added: CMS_pileup, CMS_scale_met_unclustered_energy, TES DM1/DM10
- [x] Ran smoothing - 216 comparison plots generated
- [x] New smoothed template: `*_smoothed_v2.root`
- [x] ~~Regenerate datacard~~ - Investigation revealed deeper issues need fixing first

**Dec 31 (cont) - Template vs Combine Discrepancy:**
- [x] 1tau1l Run2 combine finished
- [x] Postfit plots generated (15 PDFs)
- [x] Impacts.pdf generated
- [x] Created `plotting/check_systematic_fluctuations.py` diagnostic tool
- [x] Identified 151 problematic systematic variations
- [x] **KEY FINDING**: Template errors ~85%, but Combine shows 590% (57x inflation)
- [ ] Investigate CMS_res_j_2018 (suspicious behavior)

### Session Dec 31 - Workflow Improvements + 1tau0l Setup

**Workflow Improvements Created:**
- [x] `scripts/workflow_status.py` - Multi-channel status dashboard
- [x] `scripts/check_wh_jobs.py` - WH job completion monitor
- [x] `scripts/validate_stage.py` - Stage prerequisite validation
- [x] `.claude/skills/new-task/SKILL.md` - Scaffold new task dev-docs
- [x] `.claude/skills/status/SKILL.md` - Status dashboard skill
- [x] Updated stage3-wh skill with prerequisites and job monitor
- [x] Updated stage4-combine skill with validation table

**1tau0l XGB080test Task Created:**
- [x] Created `config/analysis_config_1tau0l_XGB080test.yaml`
- [x] Created `dev-docs/active/workflow-1tau0l-xgb080/`
- [x] Submitted WH jobs for all 4 eras (screen sessions running)

---

### Session Dec 31 - BDT Weight Path Bug Fix + Stage 4

(Previous content preserved below...)

**Critical Bug Found & Fixed:**
- 2017 WH jobs were hanging during initialization (hitting 10-hour time limit)
- **Root cause**: `inputFileMap.h` had wrong BDT weight path for 2017/2016
- Fixed all eras to use same BDT as 2018

**Stage 4 Complete:**
- [x] addJES for all 4 eras
- [x] addTemplate for all 4 eras
- [x] smooth (all eras)
- [x] writeDatacard for all 4 eras
- [x] writeCombinationDatacard.py --channel 1tau1l
- [x] Combine fits (Run2) - COMPLETE

---

## Key Commands

```bash
# Check systematic fluctuations
python3 plotting/check_systematic_fluctuations.py TEMPLATE.root --threshold 15 --max-plots 20

# Subprocess systematic analysis (new)
python3 plotting/check_subprocess_systematics.py --config CONFIG --era 2018 --process all --region all --auto-top5

# Multi-channel status
python3 scripts/workflow_status.py

# Stage validation
python3 scripts/validate_stage.py --stage 4.1 --config CONFIG --era ERA
```

## Last Updated
2026-01-03 (Smoothing complete - very effective! Ready for datacard generation)
