# Tasks: 1tau2l V22 Workflow

## Config
- `analysis_config_1tau2l_V22.yaml`
- MV input: V18 (`v94LepPreJetVetoHemOnlyV2`)
- Hist version: `v0BDT1tau2l_V22`
- Combine: `combinationV22`

---

## Status (Jan 6, 2026)

| Era | S1-2 OS/MV | S3 WH | S4.1 addJES | S4.2 template | S4.4 datacard | S4.5 combine |
|-----|------------|-------|-------------|---------------|---------------|--------------|
| 2018 | DONE (V18) | DONE | DONE | DONE | DONE | DONE |
| 2017 | DONE (V18) | DONE | DONE | DONE | DONE | DONE |
| 2016preVFP | DONE (V18) | DONE | DONE | DONE | DONE | DONE |
| 2016postVFP | DONE (V18) | DONE | DONE | DONE | DONE | DONE |
| **Run2** | - | - | - | - | DONE | DONE |

## Combine Results (Run2 1tau2l)
| Metric | Value |
|--------|-------|
| Observed significance | 0.96σ |
| Expected significance | 0.80σ |
| Signal strength (r) | 1.44 +1.96/-1.44 |

Log: `combinationV22/run2_1tau2l_v4/combine_1tau2l_run2_*.log`

## Key Info
- **MV directories exist** for all 4 eras with full systematics (JES, JER, TES, MET, EleScale)
- Stage 1-2 reused from V18
- **Smoothing NOT needed** for 1tau2l (only 1tau0l/1tau1l require smoothing)
- **No ttbb** for 1tau2l (TTBB samples not available for this channel)

## Completed
- WH resubmitted: All 4 eras, ~21k jobs total
- Stage 4.1 addJES: Done for all 4 eras
- Stage 4.2 addTemplate: Done for all 4 eras
- Stage 4.4 writeDatacard: Done for all 4 eras
- Stage 4.4.1 writeCombinationDatacard: Run2 1tau2l
- Stage 4.5 combine: Significance, signal strength, impacts complete

## Code Improvements Made
1. **Template version config-driven** (`versions.template_file: v3`)
   - Updated: `workflow_utils.py`, `addTemplateNew.py`, `writeDatacard.py`

2. **Channel-specific smoothing**
   - 1tau2l: uses non-smoothed template (`smoothing: false`)
   - 1tau0l/1tau1l: use smoothed template (`smoothing: true`)

3. **No ttbb for 1tau2l**
   - Removed from `proChannelDic` and `proChannelDic_forCombine` in `ttttGlobleQuantity.py`

4. **Combine log location**
   - `run_combine_fits.sh`: Log now saved in datacard directory

## Commands Reference

### Stage 4.1-4.4 (no smoothing for 1tau2l)
```bash
python3 plotting/addJESTemplatesToHistFile.py --config config/analysis_config_1tau2l_V22.yaml --era ERA --execute --quiet
python3 plotting/addTemplateNew.py --config config/analysis_config_1tau2l_V22.yaml --era ERA
python3 plotting/writeDatacard.py --config config/analysis_config_1tau2l_V22.yaml --era ERA
```

### Stage 4.4.1-4.5 (Run2 combine)
```bash
cd hua/combine && cmsenv
python3 writeCombinationDatacard.py --config ../../config/analysis_config_1tau2l_V22.yaml --channel 1tau2l
bash run_combine_fits.sh ../../config/analysis_config_1tau2l_V22.yaml run2 1tau2l
```

## Last Updated
2026-01-06 08:50
