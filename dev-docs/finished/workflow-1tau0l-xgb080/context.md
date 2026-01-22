# Context: 1tau0l XGB080test Workflow

## Goal
Run 1tau0l analysis for all 4 eras with XGB080test config, matching 1tau1l version.
Final goal: 3-channel combination (1tau0l + 1tau1l + 1tau2l).

## Key Paths
- Config: `config/analysis_config_1tau0l_XGB080test.yaml`
- Stage 1-2: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}/v1baselineHadro_v95XGB080testOS7/`
  (Shared with 1tau1l - already complete)
- WH output: `{stage2_path}/mc/variableHists_v0BDT1tau0l_XGB080testNew/`

## Environment
- Stages 1-4.4, 4.7: `source setEnv_newNew.sh`
- Stages 4.4.1, 4.5: `cmsenv` in hua/combine/

## Critical Notes
- 1tau0l shares OS/MV (Stage 1-2) with 1tau1l - same triggers
- Only need to run WH (Stage 3) onwards
- Use `--systematic complete` for WH submissions (screen required)
- Combination version: V22

## Related Tasks
- `workflow-xgb080test`: 1tau1l XGB080test (Run2 combine currently running)
- After both complete: 3-channel combination with 1tau2l
