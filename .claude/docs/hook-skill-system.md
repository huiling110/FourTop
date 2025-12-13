# Hook + Skill System Documentation

**Created**: 2025-12-13
**Version**: V3.1 (with path injection)

---

## Overview

The hook+skill system provides context-aware assistance for the FourTop analysis workflow. It automatically detects workflow-related prompts and injects relevant context.

```
┌─────────────────────────────────────────────────────────────────┐
│                      Architecture                                │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│  User Prompt ──► user-prompt-submit.sh (hook)                   │
│                      │                                           │
│                      ├─ Detect workflow keywords                 │
│                      ├─ Read .workflow/state.json                │
│                      └─ Inject <workflow_state> block            │
│                              │                                   │
│                              ▼                                   │
│  Claude sees: original prompt + <workflow_state>                │
│                              │                                   │
│                              ▼                                   │
│  Claude reads: .workflow/state.json for concrete paths          │
│                              │                                   │
│                              ▼                                   │
│  Skills (.claude/skills/workflow/*.md) for stage details        │
│                                                                  │
└─────────────────────────────────────────────────────────────────┘
```

---

## Components

### 1. Hook: `user-prompt-submit.sh`

**Location**: `.claude/hooks/user-prompt-submit.sh`

**Triggers on keywords**:
- Stage words: `stage`, `run`, `submit`, `job`, `histogram`, `datacard`, `template`, `combine`
- Abbreviations: `os`, `mv`, `wh`, `pl`
- Era words: `2018`, `2017`, `2016`, `run2`
- Script names: `addjes`, `addtemplate`, `makejob`

**Injects**:
```xml
<workflow_state>
Channel: 1tau1l | 2017: S3 submitted | 2018: S4.5 running
Hist version: v0BDT1tau1l_TTBBtest
Next: wait for 2017 WH jobs
Cmd: hep_q -u $USER

<paths era="2017">
hist_dir: /publicfs/.../variableHists_v0BDT1tau1l_TTBBtest
verify: ls {hist_dir}/*.root 2>/dev/null | wc -l
</paths>

>>> IMPORTANT: Read .workflow/state.json for all era paths <<<
</workflow_state>
```

### 2. State File: `.workflow/state.json`

**Location**: `.workflow/state.json`

**Contains** (V3.1 format):
```json
{
  "channel": "1tau1l",
  "config": "config/analysis_config_1tau1l_TTBBtest.yaml",
  "versions": {
    "stage1": "v94HadroPreJetVetoHemOnly_TTBBtest",
    "stage2": "v1baselineHadro",
    "hist": "v0BDT1tau1l_TTBBtest"
  },
  "eras": {
    "2017": {
      "stage": "3",
      "status": "submitted",
      "paths": {
        "hist_dir": "/publicfs/.../variableHists_v0BDT1tau1l_TTBBtest",
        "log_dir": "{hist_dir}/log",
        "job_dir": "{hist_dir}/jobSH",
        "combine_dir": "{hist_dir}/combine",
        "templates": "{hist_dir}/combine/templatesForCombine1tau1l_*.root"
      }
    }
  }
}
```

**Key feature**: Concrete paths are pre-computed and stored, so Claude doesn't need to build them.

### 3. State Manager: `plotting/workflow_state_v3.py`

**Key methods**:
```python
state = CompactWorkflowState()

# Initialize with path computation
state.initialize('1tau1l', 'config/...yaml', ['2017', '2018'])

# Get paths for an era
paths = state.get_era_paths('2017')
print(paths['hist_dir'])  # Full concrete path

# Refresh paths after config change
state.refresh_paths()

# Get verification commands
cmds = state.get_verification_commands('2017')
print(cmds['count_histograms'])  # Ready-to-run command
```

**CLI**:
```bash
# Refresh paths from config
python3 plotting/workflow_state_v3.py --refresh-paths

# Show paths for an era
python3 plotting/workflow_state_v3.py --paths 2017

# Show status
python3 plotting/workflow_state_v3.py --status
```

### 4. Skills: `.claude/skills/workflow/`

| File | Purpose |
|------|---------|
| `overview.md` | Stage order, environment, automation commands |
| `stage1-os.md` | Object Selection details |
| `stage2-mv.md` | Make Variables details |
| `stage3-wh.md` | Histogram production (WH) details |
| `stage4-combine.md` | Templates, datacards, combine details |

---

## Context Flow

### On User Prompt (keyword detected)

```
1. Hook fires (user-prompt-submit.sh)
2. Hook reads .workflow/state.json
3. Hook injects <workflow_state> with:
   - Era status summary
   - Active era paths
   - Suggested next command
   - Reminder to read state.json
4. Claude sees injected context
```

### During Autonomous Execution

```
1. Claude should READ .workflow/state.json first
2. State file has all concrete paths
3. No need to build paths or read config
4. Verification commands ready to copy-paste
```

**Key rule in CLAUDE.md**:
> Before ANY workflow operation, read `.workflow/state.json` to get concrete paths.

---

## Maintaining Context

### Problem
During autonomous execution (accept edits on), the hook only fires on user prompts, not between tool calls. Claude can lose context mid-execution.

### Solution (Option D - Hybrid)

1. **Initial prompt**: Hook injects state + paths + strong reminder
2. **State file**: Contains everything needed (self-documenting)
3. **CLAUDE.md rule**: Instructs to read state.json before workflow ops
4. **Skill files**: Detailed stage commands when needed

### When to Refresh Paths

```bash
# After config changes
python3 plotting/workflow_state_v3.py --refresh-paths

# After stage transitions (automatic in run_workflow_auto.py)
# After version changes
```

---

## Adding New Features

### Adding a New Stage

1. Add to `STAGE_ORDER` in `workflow_state_v3.py`
2. Add stage command to `_get_stage_command()`
3. Update skill file (e.g., `stage4-combine.md`)
4. Update `overview.md` stage order diagram

### Adding New Path Types

1. Update `compute_paths()` in `workflow_state_v3.py`:
   ```python
   return {
       "hist_dir": hist_dir,
       "new_path": f"{hist_dir}/new_subdir",
       ...
   }
   ```

2. Update `get_verification_commands()` if needed

3. Run `--refresh-paths` to update state

### Adding Hook Keywords

Edit `.claude/hooks/user-prompt-submit.sh`:
```bash
if [[ "$prompt_lower" =~ (existing|keywords|new_keyword) ]]; then
    return 0
fi
```

---

## Troubleshooting

### Hook not firing
- Check keyword patterns in `check_workflow_patterns()`
- Verify state file exists: `ls .workflow/state.json`

### Wrong paths in state
- Run: `python3 plotting/workflow_state_v3.py --refresh-paths`
- Check config file versions match actual directories

### Claude not seeing context
- Verify hook output: `bash .claude/hooks/user-prompt-submit.sh` with test prompt
- Check CLAUDE.md rule is present

---

## Future Improvements

1. **Pre-tool-use hook**: Inject context before workflow-related Bash commands
2. **Path validation**: Verify paths exist when computing
3. **Multi-channel state**: Track multiple channels simultaneously
4. **History**: Optional stage completion history

---

## Related Files

| File | Purpose |
|------|---------|
| `.workflow/state.json` | Compact state with paths |
| `.claude/hooks/user-prompt-submit.sh` | Keyword detection + injection |
| `plotting/workflow_state_v3.py` | State management + path computation |
| `plotting/workflow_utils.py` | Path building functions |
| `CLAUDE.md` | Project rules including workflow rule |
