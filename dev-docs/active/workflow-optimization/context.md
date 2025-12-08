# Context: FourTop Workflow Optimization

**Created**: 2025-12-08
**Last Updated**: 2025-12-08
**Status**: PLANNING

---

## Problem Statement

The FourTop analysis workflow has grown organically with inconsistent config patterns:
- ~200+ commented-out hardcoded paths across scripts
- 4+ different config loading patterns
- No single source of truth for path building
- Unclear which config parameters are essential

---

## Key Files

### Config System
- `config/analysis_config_1tau0l_full.yaml` - Current config example
- `plotting/workflow_utils.py` - Path building utilities (to be extended)
- `run_workflow.py` - Master workflow runner

### Scripts to Refactor (Priority Order)

**Phase 1-2: Config + Stage 4**
- `plotting/addJESTemplatesToHistFile.py` - Remove fallback paths
- `plotting/addTemplateNew.py` - Remove fallback paths
- `plotting/writeDatacard.py` - Remove fallback paths
- `plotting/smooth_systematics_fourTops.py` - Remove fallback paths

**Phase 3: Stage 2.4**
- `plotting/createFaketauTree.py` - Add argparse, 45 commented paths to remove
- `plotting/createFakeLeptonTree.py` - Add argparse

**Phase 4: Stage 3**
- `writeHistGood/jobs/makeJob_forWriteHist.py` - Add workflow_utils

**Phase 5: Stage 1-2**
- `objectSelectionOptimized/jobs/makeJob_OS_fromRuobing2.py` - Standardize
- `makeVariables_goodCode/jobs/makeJob_makeVaribles_forBDT.py` - Add argparse

### Claude Integration
- `.claude/skills/workflow.md` - To be created
- `.claude/hooks/pre-tool-use.sh` - To be created

---

## Path Structure Reference

```
Stage 1 Input:  /publicfs/cms/data/TopQuark/nanoAOD/{YEAR}/mc/
Stage 1 Output: /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL{ERA}/{STAGE1_VERSION}/mc/
Stage 2 Output: /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{ERA}/{STAGE2}_{STAGE1}/mc/
Stage 3 Output: .../mc/variableHists_{HIST_VERSION}/
Stage 4 Combine: .../combine/
Stage 4.4/4.5: hua/combine/{COMB_VERSION}/run2_{CHANNEL}_{DC_VERSION}/
```

---

## Environment Requirements

| Stages | Environment | Command |
|--------|-------------|---------|
| 1, 2, 2.4, 3, 4.1-4.3, 4.6 | ROOT/Python | `source setEnv_newNew.sh` |
| 4.4, 4.5 | CMSSW/Combine | `cmsenv` |

---

## Related Work

- `dev-docs/active/workflow-code-quality/` - Previous workflow improvements (Phase 1-3)
- `ANALYSIS_WORKFLOW.md` - Detailed workflow documentation

---

## Commands

```bash
# Current workflow (Stage 4 only)
source setEnv_newNew.sh
python3 run_workflow.py --stage 4 --config config/analysis_config_1tau0l_full.yaml

# Check config contents
cat config/analysis_config_1tau0l_full.yaml

# Count commented paths in scripts
grep -c "^[[:space:]]*#.*inputDir" plotting/*.py
```
