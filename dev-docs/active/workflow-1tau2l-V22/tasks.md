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
| 2018 | DONE (V18) | - | - | - | - | - |
| 2017 | DONE (V18) | - | - | - | - | - |
| 2016preVFP | DONE (V18) | - | - | - | - | - |
| 2016postVFP | DONE (V18) | - | - | - | - | - |

## Key Info
- **MV directories exist** for all 4 eras with full systematics (JES, JER, TES, MET, EleScale)
- Stage 1-2 reused from V18: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/`

## Workflow Steps

### Stage 3: WH (Write Histograms)
```bash
source setEnv_newNew.sh
cd writeHistGood/jobs/
python3 makeJob_WH.py --config ../../config/analysis_config_1tau2l_V22.yaml --era ERA --systematic complete
```

### Stage 4.1: addJES
```bash
python3 plotting/addJESTemplatesToHistFile.py --config config/analysis_config_1tau2l_V22.yaml --era ERA --execute --quiet
```

### Stage 4.2: addTemplate
```bash
python3 plotting/addTemplateNew.py --config config/analysis_config_1tau2l_V22.yaml --era ERA
```

### Stage 4.3: smooth (needs all eras)
```bash
python3 plotting/smooth_systematics_fourTops.py --config config/analysis_config_1tau2l_V22.yaml --template-version v3 --quiet
```

### Stage 4.4: writeDatacard
```bash
python3 plotting/writeDatacard.py --config config/analysis_config_1tau2l_V22.yaml --era ERA --template-version v3
```

### Stage 4.4.1: Run2 combination
```bash
cd hua/combine && cmsenv
python3 writeCombinationDatacard.py --config ../../config/analysis_config_1tau2l_V22.yaml --channel 1tau2l
```

### Stage 4.5: combine fits
```bash
bash run_combine_fits.sh ../../config/analysis_config_1tau2l_V22.yaml run2 1tau2l
```

## Next Steps
1. Submit WH for all 4 eras with `--systematic complete`
2. Wait for WH completion
3. Run Stage 4 pipeline

## Last Updated
2026-01-05 09:50
