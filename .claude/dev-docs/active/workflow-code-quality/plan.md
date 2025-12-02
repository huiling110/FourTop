# Plan: FourTop Workflow Automation

**Created**: 2025-12-02
**Status**: Phase 3A-C COMPLETE, Phase 3E COMPLETE (Stages 4.5/4.6), Phase 3D Testing in Progress
**Priority**: HIGH
**Last Updated**: 2025-12-02 13:50 (Added Stage 4.5 runCombineAll, Stage 4.6 fit plots)

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

## Phase 3: Full End-to-End Workflow (1tau1l Channel) - IN PROGRESS

**Goal**: Extend workflow to include Stage 3 (histogram production jobs) and validate on 1tau1l channel with comprehensive logging.

**Channel**: 1tau1l (different from Phase 2 validation which used 1tau0l)

### Phase 3A: Extend run_workflow.py with Stage 3

**Status**: COMPLETE ✅

**Tasks**:
- [x] **3A.1**: Add Stage 3.3 definition to STAGES dict (nominal job submission)
- [x] **3A.2**: Add Stage 3.3.1 definition (shape systematic job submission)
- [x] **3A.3**: Add Stage 3.4 definition (job monitoring/waiting)
- [x] **3A.4**: Implement `run_stage_3_3()` - submit nominal jobs via hep_sub
- [x] **3A.5**: Implement `run_stage_3_3_1()` - submit JES/JER/TES/MET jobs
- [x] **3A.6**: Implement `run_stage_3_4()` - monitor jobs until completion using hep_q
- [x] **3A.7**: Add comprehensive logging to all stages (file + console)

**Key Functions Added**:
- `build_input_dir()` - Build input path from config for a given era
- `get_running_jobs()` - Query hep_q for job count
- `run_stage_3_3()` - Submit nominal histogram jobs
- `run_stage_3_3_1()` - Submit systematic jobs (per era)
- `run_stage_3_3_1_parallel()` - Submit systematic jobs for ALL eras concurrently
- `run_stage_3_4()` - Poll job status until complete
- `run_full_stage_3()` - Run all Stage 3 substages (uses parallel by default)
- `run_full_pipeline()` - Run Stage 3 + Stage 4 end-to-end

**Performance Optimization**:
- Added `--stage all` to run full pipeline (Stage 3 → Stage 4) in one command
- Parallel systematic job submission reduces Stage 3.3.1 from ~2h → ~35min
- Uses `ThreadPoolExecutor` for concurrent era processing

**Commits**: b235a545, a81cbbc5, 146978c5

**New Stages to Add**:
```
3.3   - Submit Nominal Histogram Jobs (hep_sub)
3.3.1 - Submit Shape Systematic Jobs (JES/JER/TES/MET/EES)
3.4   - Monitor Jobs Until Completion
```

### Phase 3B: Create 1tau1l Configuration

**Status**: COMPLETE ✅

**Tasks**:
- [x] **3B.1**: Create `config/analysis_config_1tau1l.yaml`
- [x] **3B.2**: Set correct hist_version for 1tau1l (v10BDT1tau1l_WorkflowTest)
- [x] **3B.3**: Configure regions: ['1tau1lSR', '1tau1lCR12']
- [x] **3B.4**: Configure smoothing systematics for 1tau1l
- [x] **3B.5**: Set combination directory (combinationV22)

**Commits**: 2c037763

### Phase 3C: Add Logging System

**Status**: COMPLETE ✅

**Tasks**:
- [x] **3C.1**: Create setup_logging() function in run_workflow.py
- [x] **3C.2**: Add `--log-file` argument to run_workflow.py
- [x] **3C.3**: Log all command executions with timestamps
- [x] **3C.4**: Log stage start/end times and duration
- [x] **3C.5**: Log any errors/warnings with context
- [x] **3C.6**: Log workflow completion status

**Commits**: 2c037763, (pending)

**Log Format**:
```
[2025-12-02 15:30:00] INFO  | Stage 3.3 | Starting nominal job submission
[2025-12-02 15:30:05] INFO  | Stage 3.3 | Submitted 21 jobs for 2018 era
[2025-12-02 15:30:10] INFO  | Stage 3.3 | Duration: 10s
```

### Phase 3E: Add Complete Workflow Stages (4.5, 4.6)

**Status**: COMPLETE ✅

**Tasks**:
- [x] **3E.1**: Add Stage 4.5 (runCombineAll.py) to run_workflow.py
- [x] **3E.2**: Add Stage 4.6 (fit plots) to run_workflow.py
- [x] **3E.3**: Add `run_stage_4_5()` function - runs combine analysis
- [x] **3E.4**: Add `run_stage_4_6()` function - generates fit plots
- [x] **3E.5**: Add argparse to pl_postFit.py (--config, --plot-type, --fit-file)
- [x] **3E.6**: Add pre-fit plotting capability to pl_postFit.py
- [x] **3E.7**: Add command-line flags: --no-combine, --no-plots, --combine-steps, --blind

**New Features**:
- Stage 4.5: `python3 run_workflow.py --stage 4.5` runs complete combine analysis
- Stage 4.6: `python3 run_workflow.py --stage 4.6` generates pre-fit and post-fit plots
- pl_postFit.py now supports: `--plot-type prefit|postfit|both`

### Phase 3D: Full Pipeline Test (1tau1l)

**Tasks**:
- [ ] **3D.1**: Run full workflow: `python3 run_workflow.py --stage 3 --config config/analysis_config_1tau1l.yaml`
- [ ] **3D.2**: Monitor Stage 3.3 (nominal jobs) completion
- [ ] **3D.3**: Monitor Stage 3.3.1 (systematic jobs) completion
- [ ] **3D.4**: Run Stage 4.1 (consolidate shape systematics)
- [ ] **3D.5**: Run Stage 4.2 (create templates)
- [ ] **3D.6**: Run Stage 4.2.5 (smooth systematics)
- [ ] **3D.7**: Run Stage 4.3 (write datacards)
- [ ] **3D.8**: Run Stage 4.4 (combine datacards)
- [ ] **3D.9**: Run combine analysis (significance, limits)
- [ ] **3D.10**: Verify results match previous 1tau1l analysis

### Validation Checklist (1tau1l)

| Check | Status |
|-------|--------|
| Nominal histograms produced for all 4 eras | ⏳ |
| Shape systematic histograms produced for all 4 eras | ⏳ |
| Templates exist for 2018, 2017, 2016preVFP, 2016postVFP | ⏳ |
| Datacards contain all expected systematics | ⏳ |
| Combined Run2 datacard generated | ⏳ |
| Combine workspace created successfully | ⏳ |
| Expected limit consistent with previous 1tau1l | ⏳ |
| Significance consistent with previous 1tau1l | ⏳ |
| Log file contains complete workflow history | ⏳ |

---

## Final Deliverables

| File | Purpose |
|------|---------|
| `config/analysis_config.yaml` | Central YAML configuration |
| `config/versions/config_v9BDT1tau0l_CMSNamingComplete.yaml` | Version snapshot |
| `plotting/workflow_utils.py` | Config utilities (load_config, build_*_path) |
| `run_workflow.py` | Master workflow runner |

**Commits**: 36726cea, 8759883a, 238f2e68, a7835693, d6e22275, 19fc919c, 4023e100, fa47bdf1, 014c1608, 6a6d0f3c, 3a334827
