# Plan: FourTop Analysis Workflow Optimization

**Created**: 2025-12-08
**Status**: PLANNING
**Priority**: HIGH
**Branch**: addVLL

---

## Executive Summary

Design a unified, clean workflow system that:
1. Has a **minimal, essential YAML config** (no unnecessary parameters)
2. Uses **consistent patterns** across ALL stages
3. Removes all **commented-out hardcoded paths** from scripts
4. Enables **single-command execution** of full pipeline or any stage
5. Integrates with **Claude via skills and hooks**

---

## Current State Analysis

### Config Usage Patterns (INCONSISTENT)

| Stage | Script | Config Support | Problems |
|-------|--------|----------------|----------|
| 1 (OS) | makeJob_OS_fromRuobing2.py | Own YAML functions + params | 50+ commented paths |
| 2 (MV) | makeJob_makeVaribles_forBDT.py | None | Hardcoded paths |
| 2.4 | createFaketauTree.py | None | 40+ commented paths |
| 3 (WH) | makeJob_forWriteHist.py | Function params | run_workflow creates temp scripts |
| 4.1 | addJESTemplatesToHistFile.py | --config + workflow_utils | Fallback to hardcoded |
| 4.2 | addTemplateNew.py | --config + workflow_utils | Fallback to hardcoded |
| 4.3 | writeDatacard.py | --config + workflow_utils | Fallback to hardcoded |
| 4.4 | writeCombinationDatacard.py | --config | Works but messy |
| 4.5 | runCombineAll.py | Argparse | No config support |

### Key Problems Identified

1. **Inconsistent config access**: 4+ different patterns
2. **~200+ commented paths** across scripts (maintenance nightmare)
3. **No single source of truth** for path building
4. **Unclear which config parameters** are essential vs redundant
5. **No validation** - wrong paths discovered at runtime

---

## Proposed Architecture

### 1. Minimal Essential Config Schema

**Principle**: Only include parameters that:
- Change between analysis versions
- Are needed by multiple stages
- Cannot be derived from other parameters

```yaml
# analysis_config.yaml - MINIMAL ESSENTIAL PARAMETERS
# =======================================================
# Last updated: 2025-12-08
# Usage: python3 run_workflow.py --config config/analysis_config.yaml --stage all

metadata:
  name: "1tau0l_TTBBtest"
  description: "TTBB integration test"
  created: "2025-12-08"

# -----------------------------
# VERSION IDENTIFIERS (CORE)
# -----------------------------
# These 4 strings define the entire path structure
versions:
  stage1: "v94HadroPreJetVetoHemOnly"      # Object selection output
  stage2: "v1baselineHadro"                 # Variable calculation output
  hist: "v0BDT1tau0l_TTBBtest"             # Histogram output
  datacard: "v1_TTBBtest"                   # Datacard output
  combination: "combinationV21"             # Combine output

# -----------------------------
# ANALYSIS CONFIGURATION
# -----------------------------
channel: "1tau0l"   # Options: 1tau0l, 1tau1l, 1tau2l

eras:
  - "2018"
  - "2017"
  - "2016preVFP"
  - "2016postVFP"

# -----------------------------
# OPTIONS (boolean flags)
# -----------------------------
options:
  fake_tau: true           # Use fake tau estimation
  mc_fake_tau: false       # MC-based (true) vs data-driven (false)
  blind: false             # Blind signal region
  systematics: true        # Enable systematics
  smoothing: false         # Apply systematic smoothing

# -----------------------------
# PATHS (derived, but configurable)
# Defaults work for standard setup - override only if needed
# -----------------------------
paths:
  nanoaod_base: "/publicfs/cms/data/TopQuark/nanoAOD"
  output_base: "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD"
```

**What's REMOVED** (can be derived):
- `out_version`, `in_version` → replaced by `versions.stage1`, `versions.stage2`
- `base` → renamed to `output_base` for clarity
- `regions`, `variables` → can be derived from channel
- Separate `stage2`, `stage3` sections → not needed
- `combination.card_dir` → can be derived from channel + version

### 2. Unified Path Building in workflow_utils.py

```python
# workflow_utils.py - SINGLE SOURCE OF TRUTH for all path building

def build_stage1_input(config: dict, era: str) -> str:
    """NanoAOD input path for Stage 1."""
    base = config['paths']['nanoaod_base']
    year = era_to_year(era)  # 2016preVFP -> 2016
    return f"{base}/{year}/mc/"

def build_stage1_output(config: dict, era: str) -> str:
    """Stage 1 output (object selection)."""
    base = config['paths']['output_base']
    era_dir = era_to_UL(era)  # 2016preVFP -> UL2016APV
    version = config['versions']['stage1']
    return f"{base}/{era_dir}/{version}/mc/"

def build_stage2_output(config: dict, era: str) -> str:
    """Stage 2 output (variables for BDT)."""
    base = config['paths']['output_base']
    v1 = config['versions']['stage2']
    v2 = config['versions']['stage1']
    return f"{base}/forMVA/{era}/{v1}_{v2}/mc/"

def build_hist_output(config: dict, era: str) -> str:
    """Stage 3 output (histograms)."""
    stage2 = build_stage2_output(config, era)
    hist_version = config['versions']['hist']
    return f"{stage2}variableHists_{hist_version}/"

def build_combine_output(config: dict, era: str) -> str:
    """Stage 4 combine directory."""
    return build_hist_output(config, era) + "combine/"

def build_datacard_output(config: dict, era: str) -> str:
    """Stage 4.3 datacard directory."""
    combine = build_combine_output(config, era)
    dc_version = config['versions']['datacard']
    return f"{combine}datacardSys_{dc_version}/"

def build_combination_output(config: dict) -> str:
    """Stage 4.4/4.5 combination directory."""
    comb_version = config['versions']['combination']
    channel = config['channel']
    dc_version = config['versions']['datacard']
    return f"hua/combine/{comb_version}/run2_{channel}_{dc_version}/"

def get_channel(config: dict) -> str:
    return config['channel']

def get_eras(config: dict) -> list:
    return config['eras']

def get_regions(config: dict) -> list:
    """Derive regions from channel."""
    channel = config['channel']
    if channel == '1tau0l':
        return ['1tau0lSR', '1tau0lCRMR', '1tau0lVR']
    elif channel == '1tau1l':
        return ['1tau1lSR', 'l1tau1lCR12']
    elif channel == '1tau2l':
        return ['1tau2lSR', '1tau2lCR3']
    return []
```

### 3. Consistent Script Pattern

**Design Goal: Every script runs BOTH standalone AND via run_workflow.py**

```bash
# Standalone usage (user runs directly)
python3 plotting/createFaketauTree.py --config config/analysis_config.yaml --era 2018
python3 plotting/addTemplateNew.py --config config/analysis_config.yaml --era 2018

# Orchestrated usage (run_workflow.py calls scripts internally)
python3 run_workflow.py --config config/analysis_config.yaml --stage 2.4 --era 2018
python3 run_workflow.py --config config/analysis_config.yaml --stage all
```

**ALL scripts MUST follow this pattern:**

```python
#!/usr/bin/env python3
"""Script description.

Standalone usage:
    python3 script.py --config config/analysis_config.yaml --era 2018
    python3 script.py --config config/analysis_config.yaml  # all eras

Via workflow runner:
    python3 run_workflow.py --stage X.X --config config/analysis_config.yaml
"""
import argparse
from workflow_utils import load_config, build_XXXXX_path

def create_parser():
    parser = argparse.ArgumentParser(description='...')
    parser.add_argument('--config', '-c', required=True,
                        help='Path to YAML config file')
    parser.add_argument('--era', '-e',
                        help='Era to process (default: all from config)')
    parser.add_argument('--quiet', '-q', action='store_true',
                        help='Reduce output verbosity')
    return parser

def main():
    args = create_parser().parse_args()
    config = load_config(args.config)
    eras = [args.era] if args.era else config['eras']

    for era in eras:
        # Use workflow_utils for ALL paths
        input_path = build_stage2_output(config, era)
        output_path = build_hist_output(config, era)
        # ... do work ...

if __name__ == '__main__':
    main()
```

**Key rules:**
1. `--config` is REQUIRED (no fallback to hardcoded)
2. Use `workflow_utils` for ALL path building
3. NO commented-out paths in scripts
4. `--quiet` flag for reduced output
5. Scripts are SELF-SUFFICIENT - don't require run_workflow.py

### 4. Scripts to Refactor

| Script | Changes Needed |
|--------|----------------|
| createFaketauTree.py | Add argparse, remove 45 commented paths |
| createFakeLeptonTree.py | Add argparse, remove hardcoded paths |
| makeJob_forWriteHist.py | Add --config, use workflow_utils |
| makeJob_OS_fromRuobing2.py | Standardize config loading |
| makeJob_makeVaribles_forBDT.py | Add --config support |
| addJESTemplatesToHistFile.py | Remove fallback paths |
| addTemplateNew.py | Remove fallback paths |
| writeDatacard.py | Remove fallback paths |

### 5. run_workflow.py as Orchestrator

**Single entry point for all operations:**

```bash
# Full pipeline
python3 run_workflow.py --config config/my_analysis.yaml --stage all

# Single stage
python3 run_workflow.py --config config/my_analysis.yaml --stage 2.4 --era 2018

# Stage groups
python3 run_workflow.py --config config/my_analysis.yaml --stage 3-4  # Hist + Analysis

# Dry run
python3 run_workflow.py --config config/my_analysis.yaml --stage 4 --dry-run

# Resume from stage
python3 run_workflow.py --config config/my_analysis.yaml --stage all --resume-from 3.3
```

**run_workflow.py responsibilities:**
1. Load config ONCE
2. Validate config before running
3. Call individual scripts with correct paths
4. Handle environment switching (setEnv vs cmsenv)
5. Track progress and handle errors

---

## Implementation Phases

### Phase 1: Config Schema Cleanup (1-2 sessions)

1. **Define final minimal config schema**
2. **Update workflow_utils.py** with all path builders
3. **Add config validation** - fail fast on missing/invalid keys
4. **Create migration script** - convert old configs to new format
5. **Test with existing Stage 4 scripts**

### Phase 2: Stage 4 Script Cleanup (1 session)

1. Remove all commented-out paths from:
   - addJESTemplatesToHistFile.py
   - addTemplateNew.py
   - writeDatacard.py
   - smooth_systematics_fourTops.py
2. Make --config required (no fallback)
3. Test all Stage 4 scripts

### Phase 3: Stage 2.4 Integration (1 session)

1. Add argparse to createFaketauTree.py
2. Add argparse to createFakeLeptonTree.py
3. Remove all commented-out paths
4. Add to run_workflow.py

### Phase 4: Stage 3 Integration (1 session)

1. Update makeJob_forWriteHist.py to use workflow_utils
2. Remove temp script creation from run_workflow.py
3. Test histogram production

### Phase 5: Stage 1-2 Integration (1-2 sessions)

1. Update makeJob_OS_fromRuobing2.py
2. Update makeJob_makeVaribles_forBDT.py
3. Add Stage 1 and 2 to run_workflow.py
4. Test full pipeline

### Phase 6: Claude Integration (1 session)

1. Create `workflow` skill for Claude
2. Create environment check hook
3. Test with various user requests

---

## Claude Integration Design

### Workflow Skill (`.claude/skills/workflow.md`)

```markdown
# Workflow Skill

## Trigger when user says:
- "run stage X", "run workflow", "submit jobs"
- "create histograms", "run analysis", "run combine"

## Instructions:

1. **Identify stage(s) requested**
   - Map user request to stage number(s)

2. **Check environment**
   - Stage 4.4, 4.5: requires cmsenv
   - All others: requires setEnv_newNew.sh

3. **Find config file**
   - Look in config/ directory
   - Ask user if multiple configs exist

4. **Execute with correct command**
   ```bash
   source setEnv_newNew.sh  # or cmsenv for 4.4/4.5
   python3 run_workflow.py --config CONFIG --stage STAGE
   ```

5. **Track progress**
   - Update dev-docs if exists
   - Report output path when complete
```

### Environment Hook (`.claude/hooks/pre-tool-use.sh`)

```bash
#!/bin/bash
# Pre-tool-use hook: Check environment before workflow commands

if [[ "$TOOL_NAME" == "Bash" ]]; then
    # Check for combine scripts requiring cmsenv
    if [[ "$COMMAND" =~ "writeCombinationDatacard" ]] || \
       [[ "$COMMAND" =~ "runCombineAll" ]] || \
       [[ "$COMMAND" =~ "run_workflow.py" && "$COMMAND" =~ "4\.[45]" ]]; then

        if [[ -z "$CMSSW_BASE" ]]; then
            echo "WARNING: This command requires cmsenv environment."
            echo "Run: source /cvmfs/cms.cern.ch/cmsset_default.sh && cmsenv"
        fi
    fi
fi
```

---

## Success Criteria

1. **Single command runs full analysis**: `python3 run_workflow.py --stage all`
2. **Config is minimal**: <50 lines, only essential parameters
3. **No hardcoded paths in scripts**: All removed
4. **Consistent pattern**: All scripts use same argparse pattern
5. **Claude integration works**: Skill triggers correctly
6. **Clear error messages**: Invalid config caught early

---

## Risk Assessment

| Risk | Impact | Mitigation |
|------|--------|------------|
| Breaking existing workflows | HIGH | Phase rollout, test each stage |
| Config migration issues | MEDIUM | Provide migration script |
| Claude skill too aggressive | LOW | Clear trigger patterns |
| Compatibility with old code | MEDIUM | Keep workflow_utils backward compatible |

---

## Questions for User

1. **Config schema**: Is the proposed minimal schema acceptable?
2. **Mandatory --config**: OK to remove fallback to hardcoded paths?
3. **Stage 1-2 priority**: Should we include Stage 1-2 now or later?
4. **Smoothing**: Is smoothing ever used? Can we simplify?

---

## Next Steps

1. User reviews and approves this plan
2. Start Phase 1: Define final config schema
3. Implement in order: Config → Stage 4 → Stage 2.4 → Stage 3 → Stage 1-2 → Claude
