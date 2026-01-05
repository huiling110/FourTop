# Context: 1tau2l V22 Workflow

## Purpose
Run 1tau2l channel for V22 combination, reusing V18 MV inputs.

## Key Files

### Config
- `config/analysis_config_1tau2l_V22.yaml`

### MV Input (V18)
- Base: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/`
- Systematic dirs: `_JERUp`, `_JERDown`, `_TESdm0Up`, etc., plus JES dirs

### WH Output
- `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v0BDT1tau2l_V22/`

### Combine Output
- `hua/combine/combinationV22/run2_1tau2l_v4/`

## Versions
- Stage1: `v94LepPreJetVetoHemOnlyV2`
- Stage2: `v1baselineHadroBtagWeightAdded`
- Hist: `v0BDT1tau2l_V22`
- Datacard: `v1_V22`
- Combination: `combinationV22`

## Notes
- 1tau2l uses different trigger than 1tau1l/1tau0l, so separate OS/MV
- Smoothing config exists for 1tau2l in `smooth_systematics_fourTops.py`
