# Plan: FourTop Workflow Automation

**Created**: 2025-12-02
**Status**: COMPLETE ✅
**Priority**: HIGH
**Last Updated**: 2025-12-02

---

## Executive Summary

Create a complete workflow automation system for the FourTop analysis, covering Stage 3 (histogram production) through Stage 4 (combine results). Uses versioned YAML configuration files and a single master script for running the entire workflow.

---

## Phase 1 Status: COMPLETE ✅

- Fixed duplicate function in smooth_systematics_fourTops.py
- Added --quiet flag to writeDatacard.py, addTemplateNew.py, smooth_systematics_fourTops.py
- All scripts tested and committed (36726cea, 8759883a)

---

## Phase 2: Workflow Automation System - COMPLETE ✅

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
│   │   ├── config_v9BDT1tau0l_CMSNamingComplete.yaml
│   │   └── ...
├── run_workflow.py                   # Master workflow script
└── plotting/
    ├── workflow_utils.py             # Shared config loading utilities
    └── ... (existing scripts with --config support)
```

### Implementation Sub-Phases

| Phase | Description | Status |
|-------|-------------|--------|
| 2A | Configuration System | COMPLETE ✅ |
| 2B | Script Modifications (add --config) | COMPLETE ✅ |
| 2C | Master Workflow Script | COMPLETE ✅ |
| 2D | Testing & Documentation | COMPLETE ✅ |

---

## Success Criteria - ALL MET ✅

- [x] Config system loads and validates correctly
- [x] All plotting scripts accept --config flag
- [x] run_workflow.py executes all stages in order
- [x] Config versioning saves/loads correctly
- [x] Backward compatibility maintained
- [x] Full workflow test passes for 1tau0l channel (Stages 4.2-4.4)

**Known Issue**: Stage 4.1 JES path pattern needs update for v9 version naming convention.

---

## Phase 3: Full Workflow Validation - NOT STARTED

Final validation step to verify the automated workflow produces correct physics results.

### Tasks

- [ ] **3.1**: Run full Stage 4 pipeline with `run_workflow.py --stage 4`
- [ ] **3.2**: Verify template files created for all 4 eras
- [ ] **3.3**: Verify datacards generated with correct systematics
- [ ] **3.4**: Run combine analysis (limits, significance, signal strength)
- [ ] **3.5**: Generate result plots:
  - Pre-fit/post-fit distributions
  - Systematic impact plots
  - Limit plots
  - Signal strength measurements
- [ ] **3.6**: Compare results with previous manual workflow to ensure consistency
- [ ] **3.7**: Document any discrepancies and resolution

### Validation Checklist

| Check | Status |
|-------|--------|
| Templates exist for 2018, 2017, 2016preVFP, 2016postVFP | ⏳ |
| Datacards contain all expected systematics | ⏳ |
| Combined Run2 datacard generated | ⏳ |
| Combine workspace created successfully | ⏳ |
| Expected limit consistent with previous | ⏳ |
| Significance consistent with previous | ⏳ |
| Pre-fit plots show correct distributions | ⏳ |
| Post-fit plots show good data/MC agreement | ⏳ |
| Impact plot shows reasonable systematic pulls | ⏳ |

---

## Final Deliverables

| File | Purpose |
|------|---------|
| `config/analysis_config.yaml` | Central YAML configuration |
| `config/versions/config_v9BDT1tau0l_CMSNamingComplete.yaml` | Version snapshot |
| `plotting/workflow_utils.py` | Config utilities (load_config, build_*_path) |
| `run_workflow.py` | Master workflow runner |

**Commits**: 36726cea, 8759883a, 238f2e68, a7835693, d6e22275, 19fc919c, 4023e100, fa47bdf1, 014c1608, 6a6d0f3c, 3a334827
