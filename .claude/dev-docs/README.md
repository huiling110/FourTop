# Dev-Docs System

**Purpose**: Maintain context through long analysis workflows and across Claude Code session resets.

---

## Overview

This directory contains three types of documents for tracking major tasks:

1. **current-plan.md** - The approved strategy and approach
2. **context.md** - Key files, decisions, and architectural notes
3. **tasks.md** - Checklist of work items

---

## How to Use

### Starting a Major Task

1. **Create/update current-plan.md** with:
   - Goal (what you're trying to achieve)
   - Approach (high-level strategy)
   - Validation plan (how to verify success)

2. **Update context.md** with:
   - Key file paths and line numbers
   - Important decisions made
   - Technical constraints or gotchas

3. **Initialize tasks.md** with:
   - Checklist of concrete work items
   - Mark items as [ ] pending or [x] completed

### During Work

- Update **tasks.md** as you complete items
- Add to **context.md** when you discover important information
- Update **current-plan.md** if the approach changes

### Before Context Compaction

**CRITICAL**: Update all three files before context is compacted or session ends:

1. **tasks.md**: Mark completed items, add new discovered tasks
2. **context.md**: Note any important decisions or file locations
3. **current-plan.md**: Update if approach has evolved

### Resuming Work

In a new session, simply reference the dev-docs:

```
"Continue [task name] from .claude/dev-docs/"
```

Claude will read all three files to understand where you left off.

---

## Example Workflow

**Task**: Add new VLL signal sample (850 GeV mass point)

**Before starting**:
```bash
# Update current-plan.md with goal and approach
# Update context.md with relevant file paths
# Create tasks.md checklist
```

**During work**:
```
[x] Locate input files
[x] Add to inputList
[ ] Update run_treeAnalyzer.C  ← Currently here
[ ] Submit jobs
...
```

**Before context reset**:
```bash
# Update all three files with current state
# In next session: "Continue VLL 850 integration"
```

---

## Tips

- **Be specific**: "writeHistGood/apps/run_treeAnalyzer.C:45" not "main code"
- **Note blockers**: If stuck, document what's blocking you
- **Update frequently**: Don't wait until context is almost full
- **Reference validation**: Note expected outputs, event counts, etc.

---

## File Templates

See template files in this directory:
- `TEMPLATE_current-plan.md`
- `TEMPLATE_context.md`
- `TEMPLATE_tasks.md`

Copy and customize for your specific task.

---

*Part of COLLABORATION_IMPROVEMENTS.md initiative (2025-11-26)*
