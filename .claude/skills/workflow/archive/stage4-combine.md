# Stage 4: Templates, Datacards, Combine, and Plots

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
| 4.7 plots (pl.py) | `python3 plotting/pl.py --config CONFIG --era ERA` (**runs after WH, no deps**) |

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

```bash
screen -S combine_1tau1l
cd hua/combine/
bash run_combine_fits.sh ../../config/CONFIG.yaml 2018 1tau1l
# Detach: Ctrl+A D | Reattach: screen -r combine_1tau1l
```

Takes 1-2 hours. Runs: workspace, significance, postfit, signal_strength, impacts.

## Stage 4.6: postfit plots

```bash
python3 plotting/pl_postFit.py --fit-file hua/combine/.../fitDiagnosticsTest.root
```

Requires Stage 4.5 complete.

## Stage 4.7: pl.py (pre-fit plots)

**Can run immediately after Stage 3 WH - no dependencies on 4.1-4.6**

```bash
python3 plotting/pl.py --config config/CONFIG.yaml --era 2018
```

- Input: WH output (`variableHists_*`)
- Output: `{hist_dir}/results/`
- Config options: `systematics`, `fake_tau`, `mc_fake_tau`, `blind`
