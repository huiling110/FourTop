# Context: XGB080test Workflow

## Purpose
This workflow run tests XGBoost 0.80 compatibility (CentOS7 mode) for yield verification.

## Key Paths
- Config: `config/analysis_config_1tau1l_XGB080test.yaml`
- Stage 1 output: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL{era}/v95XGB080testOS7/`
- Stage 2 output: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}/v1baselineHadro_v95XGB080testOS7/`
- WH output: `{stage2_path}/mc/variableHists_v0BDT1tau1l_XGB080testNew/`

## Environment
- Stages 1-4.4, 4.7: `source setEnv_newNew.sh` (but OS uses setEnv_centos7.sh internally)
- Stages 4.4.1, 4.5: `cmsenv` in hua/combine/

## Critical Notes
- OS jobs use CentOS7 mode (`hep_sub -os CentOS7`)
- Stage 2.4 fake backgrounds must be regenerated for each version
- Stage 4.3 (smooth) requires ALL 4 eras complete
- WH uses `--systematic complete` for full systematic coverage

## 2016 Era Path Discrepancy

**Important**: 2016 has two path naming conventions:
- Old archives: `/publicfs/.../UL2016_preVFP/` (with underscore)
- New output: `/publicfs/.../UL2016preVFP/` (no underscore)

v94 systematic archives are at:
- `UL2016_preVFP/v94HadroPreJetVetoHemOnly_*.zip`
- `UL2016_postVFP/v94HadroPreJetVetoHemOnly_*.zip`

When unzipping for v95, extract to the no-underscore path:
- `UL2016preVFP/v95XGB080testOS7_*/`

## 2016 OS Systematics Strategy

For v95XGB080testOS7:
- **TES (8 variations)**: Submit new jobs (TES corrections differ between versions)
- **JES/JER/MET/EleScale (7 variations)**: Unzip v94 and rename (no physics changes)

## Dual-Library Setup (myLibrary/)

Created to support both CentOS7 (OS stage) and Linux9 (MV/WH stages):

```
myLibrary/
├── libcommenFunction.so -> libcommenFunction_linux9.so  (default)
├── libcommenFunction_linux9.so  (208KB, for MV/WH)
├── libcommenFunction_os7.so     (495KB, for OS)
├── os7/
│   └── libcommenFunction.so -> ../libcommenFunction_os7.so
└── build_os7.sh  (script to rebuild OS7 version)
```

- `setEnv_newNew.sh`: Uses default symlink (Linux9)
- `setEnv_centos7.sh`: Prepends `myLibrary/os7/` to LD_LIBRARY_PATH

## Safety Improvements
- `scripts/archive_and_cleanup.sh` now requires `--confirm` flag to actually delete
- Without `--confirm`, script lists directories and aborts with warning
- Fixed bug: now uses `find -type d` to only match directories (was matching files too)
- New misc skill: `.claude/skills/misc/SKILL.md` documents archive script usage

### Archive Script Usage
```bash
# Dry run
./scripts/archive_and_cleanup.sh --dry-run --era UL2018 --pattern "v95XGB080testOS7"

# Actual run (use screen!)
screen -S archive_2018
./scripts/archive_and_cleanup.sh --confirm --era UL2018 --pattern "v95XGB080testOS7"
```

## Useful Commands
```bash
# Check job status
hep_q -u huahuil

# Check held jobs with reason
hep_q -u huahuil -hold

# Release all held jobs
hep_release -a

# Remove jobs
hep_rm <cluster_id>

# Resubmit held jobs with higher memory
cd objectSelectionOptimized/jobs/
./resubmit_held.sh 6000    # 6GB memory
```

## New Scripts
- `objectSelectionOptimized/jobs/resubmit_held.sh` - Resubmit held jobs with higher memory
  - Uses `hep_q -u $USER | grep " H "` to find held jobs
  - Extracts script name from last column, finds script in jobs directories
  - Default memory: 10GB, usage: `./resubmit_held.sh 12000` for 12GB

- `makeVariables_goodCode/verify_mv_completion.py` - Verify MV stage completion
  - Checks all samples exist for nominal and all 74 systematic variations
  - Compares expected samples from Stage 1 to actual MV output
  - Usage: `python3 verify_mv_completion.py --config ../config/CONFIG.yaml --era 2018`
  - Reports: complete/incomplete/missing directories with details

## Technical Findings

### Ghost Jobs
- Jobs can appear "running" for hours even after completion
- Condor doesn't always update job status correctly
- **Solution**: Check output files exist, then remove with `hep_rm`

### jetHT_2016H Memory Requirements
- These data files are large and need ~8GB+ memory
- Default memory allocation causes jobs to be held
- **Solution**: Resubmit with 12GB memory using `resubmit_held.sh`

### Stage 1.1 OS Systematics
- 15 variations per era: JES, JER×2, MET×2, EleScale×2, TES×8
- Submission takes ~10 minutes per era (use screen/nohup)
- ~35000 jobs per era for full systematic run

## Skill Auto-Injection (2025-12-26)

The `user-prompt-submit.sh` hook now **injects full skill content** when stage keywords detected:

| Keywords | Skill Injected |
|----------|----------------|
| OS, NanoAOD, object selection | `workflow-stage1-os/SKILL.md` |
| MV, BDT, fake tau/lepton | `workflow-stage2-mv/SKILL.md` |
| WH, histogram, write hist | `workflow-stage3-wh/SKILL.md` |
| combine, datacard, template, pl.py | `workflow-stage4-combine/SKILL.md` |

**How it works**: Hook detects keywords in user prompt, cats the skill file content wrapped in `<skill>` tags. Claude receives the skill content automatically without needing to read it manually.

**CLAUDE.md Option C rules**: Added explicit instructions to read skills proactively before verifying stage outputs.

## Skill Learning Protocol

**Update skills as we learn**: When discovering issues, fixes, or useful commands during workflow execution, update the corresponding stage skill immediately:

| Discovery | Update |
|-----------|--------|
| OS memory issues, held jobs | `.claude/skills/workflow-stage1-os/SKILL.md` |
| MV path patterns, fake rate bugs | `.claude/skills/workflow-stage2-mv/SKILL.md` |
| WH file counts, systematic issues | `.claude/skills/workflow-stage3-wh/SKILL.md` |
| Combine fits, datacard fixes | `.claude/skills/workflow-stage4-combine/SKILL.md` |

This ensures knowledge accumulates in skills for future sessions.
