# Context: Workflow Optimization V3

**Created**: 2025-12-12
**Last Updated**: 2025-12-12 (Session 3)
**Status**: ACTIVE

---

## Background

This task continues from workflow-optimization-v2, which completed:
- Bash permissions simplification (deny-list approach)
- 1tau1l 2018 full testing with all 74 systematics
- Unified `makeJob_WH.py` script
- JES cleanup bug fix

**Problem with V2**: The workflow state tracking (`.workflow_state.json`) became too verbose (1254 lines, 52+ history entries), making it hard to read and debug.

---

## Current Infrastructure

### Files to Reference (Read Only)
| File | Purpose |
|------|---------|
| `run_workflow.py` | Stage definitions, job monitoring (lines 249-272, 478-520) |
| `plotting/workflow_utils.py` | WorkflowState class (lines 550-718) |
| `.workflow_state.json` | Current verbose state (to be replaced) |
| `.claude/hooks/user-prompt-submit.sh` | Keyword-based context injection |
| `.claude/skills/workflow/*.md` | Stage-specific skill files |

### Job Patterns
- Submission: `hep_sub` via generated `subAllProcess.sh`
- Monitoring: `hep_q -u $USER` polling every 60s
- Unified WH: `makeJob_WH.py --systematic nominal|all|complete`

---

## V3 Design Decisions

| Aspect | V2 (Current) | V3 (New) |
|--------|--------------|----------|
| State file | 1254 lines, nested structure | ~30 lines, flat per-era |
| History | 52+ entries, keeps 100 | None (just current state) |
| Skill loading | Keyword → skill file reference | State → inline injection |
| Automation | Manual stage-by-stage | Full automation in screen |
| Stage 4.5/4.6 | Manual screen | Automated with env switching |

---

## Files to Create/Modify

### New Files
| File | Purpose | Est. Lines |
|------|---------|------------|
| `.workflow/state.json` | Compact state | ~30 |
| `plotting/workflow_state_v3.py` | State manager class | ~150 |
| `run_workflow_auto.py` | Automation script | ~400 |

### Modified Files
| File | Changes |
|------|---------|
| `.claude/hooks/user-prompt-submit.sh` | Add V3 state reading + inline injection |
| `writeHistGood/jobs/makeJob_WH.py` | Add quiet mode, grouped summary output |
| `writeHistGood/jobs/makeJob_forWriteHist.py` | Add quiet parameter, remove verbose prints |

---

## Test Plan: 2016postVFP 1tau1l

**Prerequisites**:
- MV systematics for 2016postVFP complete
- Config: `config/analysis_config_1tau1l_TTBBtest.yaml`

**Stages to Execute**:
1. Stage 3: WH nominal (~71 jobs)
2. Stage 3.1: WH systematics (~4,366 jobs)
3. Stage 4.1: addJES consolidation
4. Stage 4.2: addTemplate
5. Stage 4.3: writeDatacard
6. Stage 4.4: plots
7. Stage 4.5: combine (~1-2 hours)
8. Stage 4.6: postfit plots

---

## Environment Requirements

| Stages | Environment | Command |
|--------|-------------|---------|
| 1-4.4 | ROOT/Python | `source setEnv_newNew.sh` |
| 4.5-4.6 | CMSSW | `source /cvmfs/cms.cern.ch/cmsset_default.sh && cmsenv` |

---

## Session Log

### Session 1 (2025-12-12)
- Created dev-docs structure
- Planning complete, implementation starting
- Next: Create `.workflow/` and `workflow_state_v3.py`
