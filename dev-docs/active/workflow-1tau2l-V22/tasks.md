# Tasks: 1tau2l V22 Workflow

## Config
- `analysis_config_1tau2l_V22.yaml`
- MV input: V18 (`v94LepPreJetVetoHemOnlyV2`)
- Hist version: `v0BDT1tau2l_V22`
- Combine: `combinationV22`

---

## Status (Jan 5, 2026)

| Era | S1-2 OS/MV | S3 WH | S4.1 addJES | S4.2-4.3 | S4.4 datacard | S4.5 combine |
|-----|------------|-------|-------------|----------|---------------|--------------|
| 2018 | DONE (V18) | SUBMITTING | - | - | - | - |
| 2017 | DONE (V18) | PENDING | - | - | - | - |
| 2016preVFP | DONE (V18) | PENDING | - | - | - | - |
| 2016postVFP | DONE (V18) | PENDING | - | - | - | - |

## Key Info
- **MV directories exist** for all 4 eras with full systematics (JES, JER, TES, MET, EleScale)
- Stage 1-2 reused from V18
- **Use screen** for WH submission with `--systematic complete`

## In Progress
- Submitting WH for 2018 with `--systematic complete` (takes ~20 min)

## Next Steps
1. Wait for 2018 WH submission to complete
2. Submit WH for 2017, 2016preVFP, 2016postVFP (use screen)
3. Wait for WH jobs to complete (~2-4 hours)
4. Run Stage 4 pipeline

## Commands

### Stage 3: WH (use screen!)
```bash
screen -S wh_1tau2l
source setEnv_newNew.sh
cd writeHistGood/jobs/
python3 makeJob_WH.py --config ../../config/analysis_config_1tau2l_V22.yaml --era ERA --systematic complete
# Ctrl+A, D to detach
```

### Stage 4.1-4.5
```bash
# After WH complete
python3 plotting/addJESTemplatesToHistFile.py --config config/analysis_config_1tau2l_V22.yaml --era ERA --execute --quiet
python3 plotting/addTemplateNew.py --config config/analysis_config_1tau2l_V22.yaml --era ERA
python3 plotting/smooth_systematics_fourTops.py --config config/analysis_config_1tau2l_V22.yaml --template-version v3 --quiet
python3 plotting/writeDatacard.py --config config/analysis_config_1tau2l_V22.yaml --era ERA --template-version v3

cd hua/combine && cmsenv
python3 writeCombinationDatacard.py --config ../../config/analysis_config_1tau2l_V22.yaml --channel 1tau2l
bash run_combine_fits.sh ../../config/analysis_config_1tau2l_V22.yaml run2 1tau2l
```

## Last Updated
2026-01-05 10:25
