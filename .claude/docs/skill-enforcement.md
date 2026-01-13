# Skill Enforcement System

**Created**: 2025-01-13
**Purpose**: Force Claude to invoke workflow skills before running stage-specific commands

---

## Overview

The skill enforcement system ensures Claude always has the correct context (paths, prerequisites, commands) before running workflow commands. It uses a marker-based blocking mechanism.

## Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                    Skill Enforcement Flow                        │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│  1. Claude tries to run: python3 plotting/pl.py ...             │
│                              │                                   │
│  2. pre-tool-use.sh fires:  ▼                                   │
│     - Detects "pl.py" → Stage 4                                 │
│     - Checks marker: /tmp/.claude_skill_workflow-stage4_$USER   │
│     - Marker missing/expired → EXIT 2 (BLOCKED)                 │
│                              │                                   │
│  3. Claude sees error:      ▼                                   │
│     "🚫 BLOCKED: Stage 4 skill not invoked!"                    │
│     "You MUST invoke: Skill('workflow-stage4-combine')"         │
│                              │                                   │
│  4. Claude invokes:         ▼                                   │
│     Skill("workflow-stage4-combine")                            │
│                              │                                   │
│  5. post-tool-use.sh fires: ▼                                   │
│     - Creates marker file with timestamp                        │
│                              │                                   │
│  6. Claude retries:         ▼                                   │
│     python3 plotting/pl.py ...                                  │
│     - Marker exists & valid → ALLOWED                           │
│                                                                  │
└─────────────────────────────────────────────────────────────────┘
```

## Components

### 1. pre-tool-use.sh (Blocking Hook)

**Location**: `.claude/hooks/pre-tool-use.sh`

**Function**: `check_workflow_skill_blocking()`

**Blocked Commands by Stage**:

| Stage | Skill | Blocked Patterns |
|-------|-------|------------------|
| 1 | workflow-stage1-os | `makeJob_OS`, `submit_all_systematics.sh` |
| 2 | workflow-stage2-mv | `makeJob_MV`, `createFaketau`, `createFakeLepton` |
| 3 | workflow-stage3-wh | `makeJob_WH.py`, `run_treeAnalyzer` |
| 4 | workflow-stage4-combine | `addJES`, `addTemplate`, `smooth_systematics`, `writeDatacard`, `pl.py`, `writeCombination`, `run_combine`, `runCombine`, `plotVariables` |

**Marker Check**:
```bash
marker_file="/tmp/.claude_skill_${skill_name}_$USER"
# Valid for 30 minutes (1800 seconds)
if [[ $age -lt 1800 ]]; then
    return 0  # Allow
fi
return 1  # Block (exit 2)
```

### 2. post-tool-use.sh (Marker Creation)

**Location**: `.claude/hooks/post-tool-use.sh`

**Function**: Creates marker file when `Skill()` tool is invoked

```bash
if [[ "$tool_name" == "Skill" && "$skill_name" =~ ^workflow ]]; then
    echo "$(date +%s)" > "/tmp/.claude_skill_${skill_name}_$USER"
fi
```

### 3. user-prompt-submit.sh (Keyword Detection)

**Location**: `.claude/hooks/user-prompt-submit.sh`

Also creates markers when user prompt contains stage keywords (lines 250-259).

## Marker Files

**Location**: `/tmp/.claude_skill_${skill_name}_${USER}`

**Content**: Unix timestamp of creation

**Validity**: 30 minutes

**Examples**:
- `/tmp/.claude_skill_workflow-stage1-os_huahuil`
- `/tmp/.claude_skill_workflow-stage2-mv_huahuil`
- `/tmp/.claude_skill_workflow-stage3-wh_huahuil`
- `/tmp/.claude_skill_workflow-stage4-combine_huahuil`

## Adding New Blocked Commands

Edit `.claude/hooks/pre-tool-use.sh`, function `check_workflow_skill_blocking()`:

```bash
# Stage 4: Plotting/Datacard/Combine
elif [[ "$cmd" =~ addJES.*\.py || "$cmd" =~ pl\.py || "$cmd" =~ NEW_PATTERN ]]; then
    skill_name="workflow-stage4-combine"
    stage_name="Stage 4 (Plotting/Combine)"
fi
```

## Troubleshooting

### Command blocked but skill was invoked

Check marker file:
```bash
ls -la /tmp/.claude_skill_*_$USER
cat /tmp/.claude_skill_workflow-stage4-combine_$USER
```

### Marker expired

Markers are valid for 30 minutes. Re-invoke the skill:
```
Skill("workflow-stage4-combine")
```

### Hook not blocking

Test hook directly:
```bash
echo '{"tool_name": "Bash", "tool_input": {"command": "python3 plotting/pl.py --help"}}' | \
    bash .claude/hooks/pre-tool-use.sh
echo "Exit code: $?"  # Should be 2 if blocked
```

## Related Files

| File | Purpose |
|------|---------|
| `.claude/hooks/pre-tool-use.sh` | BLOCKS commands, checks marker |
| `.claude/hooks/post-tool-use.sh` | Creates marker on Skill() call |
| `.claude/hooks/user-prompt-submit.sh` | Creates marker on keyword detection |
| `.claude/settings.json` | Hook configuration |
| `.claude/skills/workflow-stage*/SKILL.md` | Stage-specific skill content |
