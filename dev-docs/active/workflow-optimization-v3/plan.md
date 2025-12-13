# Plan: Workflow Optimization V3

**Created**: 2025-12-12
**Status**: IN PROGRESS (Phase 6)
**Channel**: 1tau1l (test), then all channels
**Test Scope**: 2016preVFP era (WH → Final Result), Run2 combination

---

## Goals

1. **Automated Workflow Execution**: Submit → Wait → Next Stage → Final Result
2. **Compact State Tracking**: Simple per-era status, easy to read/debug
3. **State-Aware Hook+Skill**: Inject relevant context automatically based on workflow state

---

## Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                     User / Claude Session                        │
├─────────────────────────────────────────────────────────────────┤
│  user-prompt-submit.sh hook                                      │
│    ├─ Reads .workflow/state.json                                │
│    └─ Injects <workflow_state>Channel: 1tau1l | Stage: 3...</>  │
├─────────────────────────────────────────────────────────────────┤
│  run_workflow_auto.py (for automated runs)                      │
│    ├─ State machine: submit → wait → next stage                 │
│    ├─ Screen-friendly output                                    │
│    └─ Resume from interruption                                  │
├─────────────────────────────────────────────────────────────────┤
│  .workflow/state.json (compact state file)                      │
│    {"channel": "1tau1l", "eras": {"2017": {"stage": "3", ...}}} │
└─────────────────────────────────────────────────────────────────┘
```

---

## Key Design Decisions

1. **Execution Model**: Hybrid - Screen for active stages + auto-resume via state file
2. **State File**: Compact per-era status (not verbose history)
3. **Skill Loading**: Hook injects state inline (not via separate skill file)
4. **Test Scope**: Single era (2017 1tau1l) first

---

## Components

### 1. Compact State File (`.workflow/state.json`)

```json
{
  "channel": "1tau1l",
  "config": "config/analysis_config_1tau1l_TTBBtest.yaml",
  "eras": {
    "2017": {"stage": "3", "status": "running", "jobs": 897},
    "2018": {"stage": "complete", "status": "done"}
  },
  "next_action": "wait for 2017 WH jobs",
  "last_update": "2025-12-12T10:30:00Z"
}
```

### 2. State Manager (`plotting/workflow_state_v3.py`)

- `CompactWorkflowState` class
- Methods: `update_era()`, `get_era_status()`, `get_summary()`, `initialize()`

### 3. Hook Enhancement (`.claude/hooks/user-prompt-submit.sh`)

- Read V3 state file
- Inject `<workflow_state>` block inline
- Suggest next command

### 4. Automation Script (`run_workflow_auto.py`)

- Full stage progression: 1 → 1.1 → 2 → 2.1 → 3 → 3.1 → 4.1-4.6
- Including Stage 4.5 (combine) and 4.6 (postfit plots)
- Resume capability

---

## Implementation Phases

1. **Phase 1**: State infrastructure (`.workflow/`, `workflow_state_v3.py`)
2. **Phase 2**: Hook enhancement for inline context injection
3. **Phase 3**: Manual test with 2017 1tau1l (WH → result)
4. **Phase 4**: Automation script
5. **Phase 5**: Documentation updates

---

## Success Criteria

1. State file correctly tracks stage/status/jobs
2. Hook injects `<workflow_state>` on workflow prompts
3. 2017 1tau1l completes WH → Stage 4 → Combine → Postfit
4. Automation script supports `--init`, `--status`, `--run`, `--resume`

---

## Related Documentation

- Full plan file: `~/.claude/plans/functional-jumping-dawn.md`
- Previous work: `dev-docs/active/workflow-optimization-v2/`

---

## Session Log

### Session 3 (2025-12-12)
- Fixed verbose output in WH scripts (commit 346d0860)
- User testing JES systematics for 2016postVFP manually
- Phase 3 in progress: manual testing of full pipeline

### Session 7 (2025-12-12)
- Bug fixes in automation: env sourcing, start-stage logic
- 2016preVFP WH nominal+systematics resubmitted (~4000+ jobs)
- Phase 4 testing continues after jobs complete

### Session 8 (2025-12-12)
- 2016preVFP automation test: S4.1-4.4 passed, S4.5 core fit done
- Added file logging to run_workflow_auto.py
- Updated overview.md with V3 automation docs
- Phases 1-5 complete

### Session 9 (2025-12-12)
- **Phase 6 started**: Run2 Combination Support
- Adding Stage 4.4.1 (1-channel Run2 datacard combination)
- Adding Stage 4.4.2 (3-channel Run2 datacard combination)
- Extending writeCombinationDatacard.py for multi-channel mode
