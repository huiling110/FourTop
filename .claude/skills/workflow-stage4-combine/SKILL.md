---
name: workflow-stage4-combine
description: Stage 4 Templates, Datacards, Combine, and Plots. Use when running addJES, addTemplate, smoothing, writeDatacard, combine fits, postfit plots, or pl.py. Keywords: stage 4, combine, datacard, template, addJES, addTemplate, smooth, writeDatacard, pl.py, postfit, limits, significance, Run2 combination.
---

# Stage 4: Templates, Datacards, Combine, and Plots

## Prerequisites Validation

**Before each sub-stage**, validate prerequisites:
```bash
python3 scripts/validate_stage.py --stage STAGE --config config/CONFIG.yaml --era ERA
```

| Stage | Validation | Requirements |
|-------|------------|--------------|
| 4.1 | `--stage 4.1` | WH nominal + systematics complete |
| 4.2 | `--stage 4.2` | addJES complete (template file exists) |
| 4.3 | `--stage 4.3` | ALL eras have templates (no era needed) |
| 4.4 | `--stage 4.4` | smooth complete (if enabled) |
| 4.5 | `--stage 4.5` | datacard exists |
| 4.7 | `--stage 4.7` | WH + addJES (if systematics) |

## Quick Reference

| Stage | Command |
|-------|---------|
| 4.1 addJES | `python3 plotting/addJESTemplatesToHistFile.py --config CONFIG --era ERA --execute --quiet` |
| 4.2 addTemplate | `python3 plotting/addTemplateNew.py --config CONFIG --era ERA` |
| 4.3 smooth | `python3 plotting/smooth_systematics_fourTops.py --config CONFIG --quiet` (ALL eras, needs `smoothing: true`) |
| 4.4 writeDatacard | `python3 plotting/writeDatacard.py --config CONFIG --era ERA` |
| 4.4.1 Run2 combine | `cd hua/combine && cmsenv && python3 writeCombinationDatacard.py --config CONFIG --channel CH` |
| 4.5 combine fits | `cd hua/combine && bash run_combine_fits.sh CONFIG ERA CHANNEL` (use screen!) |
| 4.6 postfit | `python3 plotting/pl_postFit.py --fit-file FITDIAG.root` |
| 4.7 plots (pl.py) | `python3 plotting/pl.py --config CONFIG --era ERA` (**needs 4.1 addJES for systematics**) |

## Environment

| Stages | Environment |
|--------|-------------|
| 4.1-4.4, 4.6, 4.7 | `source setEnv_newNew.sh` |
| 4.4.1, 4.5 | `cmsenv` (in hua/combine/) |

---

## Stage 4.1: addJES (consolidate systematics)

```bash
python3 plotting/addJESTemplatesToHistFile.py --config config/CONFIG.yaml --era 2018 --execute --quiet
```

- `--execute`: Actually run (default: dry-run)
- Merges JES/JER/TES/MET/EES into nominal files, cleans up sys dirs

## Stage 4.2: addTemplate

```bash
python3 plotting/addTemplateNew.py --config config/CONFIG.yaml --era 2018
```

## Stage 4.3: smooth (SYNC POINT - needs ALL eras)

```bash
python3 plotting/smooth_systematics_fourTops.py --config config/CONFIG.yaml --quiet
```

- Requires `options.smoothing: true` in config
- Mandatory for 1tau1l/1tau0l before writeDatacard

## Stage 4.4: writeDatacard

```bash
python3 plotting/writeDatacard.py --config config/CONFIG.yaml --era 2018
```

## Stage 4.4.1: Run2 combination (SYNC POINT - needs all 4 eras)

```bash
cd hua/combine/
cmsenv  # NOT setEnv_newNew.sh!
python3 writeCombinationDatacard.py --config ../../config/CONFIG.yaml --channel 1tau1l
```

Output: `hua/combine/combinationV{XX}/run2_{channel}_v4/datacard.txt`

## Stage 4.5: combine fits (SLOW - use screen!)

**Before running:** Create symbolic link for combination results:
```bash
cd hua/combine/
ln -sfn $(pwd)/combinationV{XX} /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/run2_combination/combinationV{XX}
```

**Run combine fits:**
```bash
screen -S combine_1tau1l
cd hua/combine/
# For single era:
bash run_combine_fits.sh ../../config/CONFIG.yaml 2018 1tau1l
# For Run2 combination:
bash run_combine_fits.sh ../../config/CONFIG.yaml run2 1tau1l
# Detach: Ctrl+A D | Reattach: screen -r combine_1tau1l
```

Takes 1-2 hours. Runs: workspace, significance, postfit, signal_strength, impacts.

## Stage 4.6: postfit plots

```bash
python3 plotting/pl_postFit.py --fit-file hua/combine/.../fitDiagnosticsTest.root
```

Requires Stage 4.5 complete.

## Stage 4.7: pl.py (pre-fit plots)

**IMPORTANT: Requires Stage 4.1 (addJES) if running with systematics!**

pl.py with `systematics: true` looks for JES/JER/TES/MET/EES histograms in the nominal files. These are merged by addJES.

```bash
# Without systematics (can run immediately after WH nominal)
python3 plotting/pl.py --config config/CONFIG.yaml --era 2018 --no-systematics

# With systematics (requires addJES first!)
python3 plotting/addJESTemplatesToHistFile.py --config config/CONFIG.yaml --era 2018 --execute --quiet
python3 plotting/pl.py --config config/CONFIG.yaml --era 2018 --unblind
```

- Input: WH output (`variableHists_*`)
- Output: `{hist_dir}/results/`
- Config options: `systematics`, `fake_tau`, `mc_fake_tau`, `blind`
- Error if addJES not run: `Unable to find histogram '..._CMS_scale_j_*_BDT'`

---

## Verify Each Sub-stage

```bash
# 4.1: Templates with JES merged (check nominal has JES systematics)
python3 -c "import ROOT; f=ROOT.TFile('plotting/templates_{version}/template_2018.root'); print([k.GetName() for k in f.GetListOfKeys() if 'JES' in k.GetName()][:5])"

# 4.2: addTemplate completed
ls plotting/templates_{version}/*_2018.root | wc -l

# 4.4: Datacards exist
ls plotting/datacard/{version}/datacard_*.txt | wc -l

# 4.4.1: Run2 datacard
cat hua/combine/{combination}/run2_{channel}_v4/datacard.txt | head -5

# 4.5: Combine results
cat hua/combine/{combination}/significance_*.txt
cat hua/combine/{combination}/limits_*.txt

# 4.7: Plots generated
ls plotting/results_{version}/*.pdf | wc -l
```
