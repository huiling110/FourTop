# Context: XGB080test Workflow

## Goal
**Complete through Stage 4 with physics results for 1tau1l channel.**
- All 4 eras: 2018, 2017, 2016preVFP, 2016postVFP
- Final deliverables: significance, limits, postfit plots, impact plots

## Purpose
This workflow run tests XGBoost 0.80 compatibility (CentOS7 mode) for yield verification.

## Key Paths
- Config: `config/analysis_config_1tau1l_XGB080test.yaml`
- Stage 1 output: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL{era}/v95XGB080testOS7/`
- Stage 2 output: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}/v1baselineHadro_v95XGB080testOS7/`
- WH output (v1, current): `{stage2_path}/mc/variableHists_v1BDT1tau1l_XGB080testNew/`
- WH output (v0, corrupted tttt.root): `{stage2_path}/mc/variableHists_v0BDT1tau1l_XGB080testNew/`
- Combine: `hua/combine/combinationV22/run2_1tau1l_v4/`

## Environment
- Stages 1-4.4, 4.7: `source setEnv_newNew.sh`
- Stages 4.4.1, 4.5: `cmsenv` in hua/combine/

## Critical Notes
- OS jobs use CentOS7 mode (`hep_sub -os CentOS7`)
- Stage 2.4 fake backgrounds must be regenerated for each version
- Stage 4.3 (smooth) requires ALL 4 eras complete
- WH uses `--systematic complete` for full systematic coverage

## RESOLVED Issue: V22 Large Uncertainties

**Status: FIXED with expanded smoothing (Jan 3, 2026)**

### Problem Summary (RESOLVED)
V22 postfit uncertainties were 4-5x larger than V18. Fixed by:
1. Expanded smoothing config from 24 to 35 systematics
2. Subprocess skipping for low-stats subprocesses
3. Re-generated datacards with smoothed v3 templates

**Before/After Comparison (2018 SR):**
| Process | Old V22 Total | Smoothed V3 | Improvement |
|---------|---------------|-------------|-------------|
| tt      | 120%          | 43%         | **-64%** |
| ttW     | 627%          | 85%         | **-86%** |
| ttZ     | 293%          | 75%         | **-74%** |
| ttH     | 40%           | 26%         | **-35%** |

**Signal Strength**: `r = 1.33 -1.33/+2.24` (Run2 combination)

### Root Cause Analysis (Updated Jan 2, 2026)

**ROOT CAUSES IDENTIFIED** - Two major issues found!

#### Issue 1: JES/JER Systematics Have Wrong Event Counts

**JES and JER systematic variations have ~50% fewer entries than nominal!**

| Systematic | Entries | Ratio vs Nominal |
|------------|---------|------------------|
| Nominal | 555 | 100% |
| JER Up | 285 | 51% ← BUG! |
| JER Down | 267 | 48% ← BUG! |
| AbsoluteMPFBias Up | 280 | 50% ← BUG! |
| ps_fsr Up | 555 | 100% ✓ |

Weight-based systematics (ps_fsr, pileup) are correct (100% entries).
JES/JER are produced by re-running with shifted jets, causing different events to pass selection.

#### Issue 2: 79% of Systematics Have Up/Down in SAME Direction

For tt bin 4, **31 out of 39 significant systematics have Up and Down variations in the same direction**, which is physically impossible for real systematic uncertainties.

| Systematic | Up % | Down % | Issue |
|------------|------|--------|-------|
| CMS_scale_j_AbsoluteMPFBias | +19.1% | +13.5% | Both positive! |
| CMS_scale_j_AbsoluteStat_2018 | +17.6% | +13.5% | Both positive! |
| ps_fsr | -7.3% | +8.5% | ✓ Opposite (correct) |

This happens because:
1. Only ~3 events in tt bin 4 (very low stats)
2. JES variations select different events
3. Random fluctuations dominate over real systematic effect

#### Quantitative Impact

| Source | Template | Combine Prefit | Inflation |
|--------|----------|----------------|-----------|
| tt bin 4 | 80% | 590% | **7.3x** |
| tt bin 1 | 33% | 166% | 5.0x |
| singleTop bin 4 | ~100% | 691% | ~7x |

#### V18 vs V22 Comparison

| Metric | V18 | V22 |
|--------|-----|-----|
| tt definition | tt = tt + ttbb | tt and ttbb separate |
| tt bin 4 events | 10.0 | 2.8 |
| tt bin 4 error | 21.6% | 589.6% |

The tt/ttbb split causes individual processes to have fewer events → higher relative fluctuations → unphysical systematic shapes.

#### Diagnostic Plots Created

```
hua/combine/combinationV22/run2_1tau1l_v4/diagnostics/
├── tt_template_vs_combine_uncertainty.pdf  # Shows 7x inflation
├── tt_systematic_shapes.pdf                # Shows shape variations
└── tt_bin4_root_cause.pdf                  # Up/Down same direction analysis
```

### Recommended Fixes (Priority Order)

1. **Merge tt + ttbb back together** - Restores statistics to V18 levels
2. **Symmetrize Up/Down variations** - Force Down = -Up for problematic systematics
3. **Increase smoothing aggressiveness** - Current smoothing helps but not enough
4. **Add minimum event threshold** - Exclude bins with <5 events from shape fits

| Process | Bin | Template Err | FitDiag Err | Inflation |
|---------|-----|--------------|-------------|-----------|
| tt | 4 | 2.42 (85%) | 16.8 (590%) | **57x** |
| ttZ | 3 | 0.03 (13%) | 2.8 (1175%) | **93x** |
| tttt | 6 | 0.015 (2%) | 1.4 (204%) | **94x** |

**This is NOT a template problem - something in Combine is wrong!**

#### 2. Template Analysis (tt bin 4) - Reasonable Values

- Nominal: 2.849 events
- MC stat error: 0.294 (10.3%)
- 76 shape systematics, each contributing 10-21%
- **Total from template: 2.42 (85%)** ← This is reasonable!
- **But fitDiagnostics shows: 16.8 (590%)** ← 57x inflation!

Largest systematic contributors in template (all reasonable):
- CMS_scale_j_AbsoluteMPFBiasUp: 19.1%
- CMS_scale_t_DeepTau2017v2p1_DM1: 18.9%
- CMS_scale_j_AbsoluteStat_2018Up: 17.6%

#### 3. Suspicious: CMS_res_j_2018 (Jet Resolution) - TO INVESTIGATE

User noticed CMS_res_j_2018 looks abnormal:
- May have many more entries than other systematics
- May be missing uncertainty bars
- **Could be the culprit for the 57x inflation!**

#### 4. Covariance Matrix Shows High Bin-to-Bin Correlations

2018 SR correlation matrix:
- bins 1↔4: 0.90 correlation
- bins 4↔5: 0.92 correlation
- bin 7 anti-correlated with all others (-0.68 to -0.72)

This suggests systematic shapes are creating unphysical inter-bin correlations.

#### 5. WH Output Issues Found

**L1 Prefiring Bug (excluded from template, but indicates WH issue):**
```
ttbar_2l_1tau1lSR_CMS_l1_ecal_prefiring_2018Up: ALL ZEROS
ttbar_2l_1tau1lSR_CMS_l1_ecal_prefiring_2018Down: ALL ZEROS
```

**TTWJetsToQQ Negative Yields:**
```
bin 4: -0.020 ± 0.108 (negative from MC weights)
bin 5: -0.050 ± 0.050
```

#### 6. Subprocess Statistics (2018 1tau1l SR)

| Process | Main Contributor | Events | Notes |
|---------|-----------------|--------|-------|
| tt | ttbar_2l | 15.2 | Only 2l contributes (expected) |
| ttbb | TTBB_4f_TTTo2L2Nu | 36.0 | Only 2l contributes |
| singleTop | st_tW only | 1.4 | st_schan/tchan = 0 events |
| ttW | TTWJetsToLNu | 0.4 | TTWJetsToQQ has negative yields |

### Key Files for Investigation

| File | Purpose |
|------|---------|
| `plotting/smoothTemplate.py` | Smoothing algorithm - check why it's not working |
| `plotting/check_systematic_fluctuations.py` | Diagnostic tool (created Dec 31) |
| `plotting/addTemplateNew.py` | Template generation with subprocess skipping (v3) |
| `hua/src_py/ttttGlobleQuantity.py` | SKIP_SUBPROCESSES config, proChannelDic_forCombine |
| `hua/src_py/usefulFunc.py` | getSumHist with skip_subprocesses parameter |
| `hua/combine/combinationV22/run2_1tau1l_v4/` | V22 combine output |
| `hua/combine/combinationV18/run2_1tau1l/` | V18 reference (working) |

### Diagnostic Tools
```bash
# Analyze systematic fluctuations (template level)
python3 plotting/check_systematic_fluctuations.py TEMPLATE.root --threshold 15

# Subprocess systematic analysis (WH level)
python3 plotting/check_subprocess_systematics.py --config CONFIG --era 2018 --process all --region all --auto-top5
```

**Fluctuation report output**: `{template_dir}/systematic_fluctuations/`
- `fluctuation_report.txt` - Ranked list of problematic variations
- `top5_systematics_{process}.png` - Top 5 systematics per process

**Subprocess analysis output**: `{WH_dir}/subprocess_systematics/{process}_{region}/`
- `compare_{process}_{region}_{syst}.png` - Combined + subprocess shapes

### Most Affected Processes
| Process | Max Variation | Worst Systematics |
|---------|---------------|-------------------|
| ttW | 68% | CMS_scale_j_FlavorPureGluon, TimePtEta |
| singleTop | 60% | ps_fsr, CMS_scale_j_AbsoluteScale |
| ttbb | 49% | QCDscale |
| tt | 44% | CMS_scale_j_FlavorPureGluon |
| ttZ | 41% | ps_fsr |
| ttH | 41% | ps_fsr |

### Smoothing Results (Jan 3, 2026) - VERY EFFECTIVE!

**All fixes implemented and validated:**

#### DONE: Subprocess Skipping (Jan 2-3)
- Implemented subprocess skipping in template generation
- Skipped for 1tau1l: `TTBB_4f_TTToSemiLeptonic`, `ttbar_1l` (< 1% contribution)
- Removed singleTop from 1tau1l combine (only 1.4 events, 294% ps_fsr fluctuation)
- Template output uses v3 naming: `templatesForCombine1tau1l_v3_*`

#### DONE: Enhanced Smoothing (Jan 3)
- Added `--template-version` argument to smoothing script
- Expanded systematics list to 24 (all problematic JES/TES/MET/pileup sources)
- Added graceful handling of missing processes

#### Smoothing Validation Results (Bin 4 Variations):
| Process | Systematic | Before | After | Reduction |
|---------|------------|--------|-------|-----------|
| ttW | CMS_scale_j_FlavorPureGluon Up | +78.8% | +10.1% | **68.7%** |
| ttW | ps_fsr Down | -196.7% | 0% | **Complete fix!** |
| ttW | ps_fsr Up | +111.3% | 0% | **Complete fix!** |
| tt | ps_fsr Down | +19.0% | +7.9% | 11.1% |
| ttbb | CMS_scale_j_FlavorPureGluon Down | -7.6% | 0% | 7.6% |

### Next Steps

1. **Generate datacard with smoothed v3 templates**
2. **Run Combine fit**
3. **Compare prefit uncertainties** - expect significant reduction vs V22

#### Lower Priority (Future)
- Analyze SKIP_SUBPROCESSES for 1tau0l and 1tau2l channels
- Handle negative yields in TTWJetsToQQ
- Fix L1 prefiring bug in WH code (all zeros)

## New Workflow Tools (Dec 31)

| Tool | Purpose | Usage |
|------|---------|-------|
| `scripts/workflow_status.py` | Multi-channel dashboard | `python3 scripts/workflow_status.py` |
| `scripts/check_wh_jobs.py` | WH job monitor | `--config X --all --watch` |
| `scripts/validate_stage.py` | Prerequisites check | `--stage 4.1 --config X --era Y` |
| `/new-task` skill | Scaffold dev-docs | For new multi-session tasks |
| `/status` skill | Status dashboard | Quick overview |

## Related Tasks
- `workflow-1tau0l-xgb080`: 1tau0l channel (WH running)
- After both complete: 3-channel combination

## Useful Commands
```bash
# Check job status
hep_q -u huahuil | grep -c WH_

# Multi-channel status
python3 scripts/workflow_status.py

# Check systematic fluctuations
python3 plotting/check_systematic_fluctuations.py TEMPLATE.root --threshold 15
```

## Last Updated
2026-01-03 (Issue RESOLVED! Combine fit complete with 64-86% uncertainty reduction)
