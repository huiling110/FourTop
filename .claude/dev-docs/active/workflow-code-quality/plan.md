# Plan: FourTop Workflow Automation

**Created**: 2025-12-02
**Status**: In Progress
**Priority**: HIGH

---

## Executive Summary

Create a complete workflow automation system for the FourTop analysis, covering Stage 3 (histogram production) through Stage 4 (combine results). Uses versioned YAML configuration files and a single master script for running the entire workflow.

---

## Phase 1 Status: COMPLETE ✅

- Fixed duplicate function in smooth_systematics_fourTops.py
- Added --quiet flag to writeDatacard.py, addTemplateNew.py, smooth_systematics_fourTops.py
- All scripts tested and committed (36726cea, 8759883a)

---

## Phase 2: Workflow Automation System

### User Preferences
- **Scope**: Stage 3-4 full (histogram jobs + plotting + combine)
- **Config History**: Versioned config files (config_v9BDT.yaml, config_v8BDT.yaml)
- **Automation Style**: Single master script (like runCombineAll.py)

### Architecture

```
FourTop/
├── config/
│   ├── analysis_config.yaml          # Current active configuration
│   ├── versions/                     # Historical configs
│   │   ├── config_v9BDT1tau0l.yaml
│   │   └── ...
├── run_workflow.py                   # Master workflow script
└── plotting/
    ├── workflow_utils.py             # Shared config loading utilities
    └── ... (existing scripts with --config support)
```

### Implementation Sub-Phases

| Phase | Description | Status |
|-------|-------------|--------|
| 2A | Configuration System | Not Started |
| 2B | Script Modifications (add --config) | Not Started |
| 2C | Master Workflow Script | Not Started |
| 2D | Testing & Documentation | Not Started |

---

## Success Criteria

- [ ] Config system loads and validates correctly
- [ ] All plotting scripts accept --config flag
- [ ] run_workflow.py executes all stages in order
- [ ] Stage 3 job submission works via workflow
- [ ] Config versioning saves/loads correctly
- [ ] Backward compatibility maintained
- [ ] Full workflow test passes for 1tau0l channel
