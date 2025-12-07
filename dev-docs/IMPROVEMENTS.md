# Dev-Docs System Improvements

**Date**: 2025-11-26
**Based on**: Reddit best practices example

---

## Changes Made

### 1. Per-Task Directory Structure

**Before**:
```
.claude/dev-docs/
├── current-plan.md      # Shared, one task at a time
├── context.md
└── tasks.md
```

**After**:
```
.claude/dev-docs/
├── active/              # Multiple concurrent tasks
│   ├── vll-m850/
│   │   ├── plan.md
│   │   ├── context.md
│   │   └── tasks.md
│   └── 1tau2l-analysis/
│       ├── plan.md
│       ├── context.md
│       └── tasks.md
├── completed/           # Archived tasks
└── TEMPLATE_*.md
```

**Benefits**:
- Support multiple concurrent tasks
- Clear separation between tasks
- Easy to archive completed work
- Task-specific names are more discoverable

---

### 2. Improved Template Structure

**Added to all templates**:
- ✅ **Created** timestamp (when task started)
- ✅ **Last Updated** timestamp (last modification)
- ✅ Simplified filenames: `plan.md` instead of `current-plan.md`

**Example**:
```markdown
# Plan: VLL M850 Integration

**Created**: 2025-11-26 10:00
**Last Updated**: 2025-11-26 15:30
**Status**: Active
```

**Benefits**:
- Know when task started vs. last touched
- Track staleness (if Last Updated is old, may need refresh)
- Better audit trail

---

### 3. Updated Workflow

**Starting a task**:
```bash
# Old way (shared files, manual naming)
cp TEMPLATE_current-plan.md current-plan.md

# New way (per-task directory)
mkdir -p .claude/dev-docs/active/vll-m850/
cd .claude/dev-docs/active/vll-m850/
cp ../../TEMPLATE_plan.md plan.md
cp ../../TEMPLATE_context.md context.md
cp ../../TEMPLATE_tasks.md tasks.md
```

**Resuming**:
```
User: "Continue vll-m850 from dev-docs"

Claude:
1. Checks .claude/dev-docs/active/
2. Finds vll-m850/
3. Reads plan.md, context.md, tasks.md
4. Continues work
```

**Completing**:
```bash
# Archive when done
mv .claude/dev-docs/active/vll-m850 .claude/dev-docs/completed/
```

---

### 4. Updated CLAUDE.md

**Changed**:
- Location reference: `.claude/dev-docs/active/[task-name]/` (was `.claude/dev-docs/`)
- File names: `plan.md`, `context.md`, `tasks.md` (was `current-plan.md`, etc.)
- Added: Instructions for archiving completed tasks
- Added: Timestamp update requirement

**AI Assistant will now**:
1. Check `.claude/dev-docs/active/` for existing tasks
2. Read all three files from task directory
3. Update timestamps when modifying files
4. Suggest archiving when task is complete

---

## Key Improvements Inspired by Example

From the Reddit example CLAUDE.md:

1. ✅ **Per-task directories** - "~/dev/active/[task-name]/" pattern
2. ✅ **Task-specific naming** - "[task-name]-plan.md" → we use `task-name/plan.md`
3. ✅ **Active directory** - Clear place to check for ongoing work
4. ✅ **Timestamps** - "Last Updated" tracking
5. ✅ **Immediate updates** - "Mark tasks complete immediately"
6. ✅ **Auto-check on continue** - Check /dev/active/ for tasks

---

## What We Kept Different

**Our approach vs. example**:

| Aspect | Example | Our Approach | Reason |
|--------|---------|--------------|---------|
| File naming | `[task]-plan.md` | `plan.md` in `[task]/` | Simpler, already in task dir |
| Location | `~/dev/active/` | `.claude/dev-docs/active/` | Keep in project, not home |
| Plan trigger | After exiting plan mode | Manual or on-demand | More flexible for physics tasks |

---

## Benefits Summary

**Before** (v1):
- ❌ Could only track one task at a time
- ❌ Generic filenames (`current-plan.md`)
- ❌ No archive system
- ❌ No timestamps for staleness tracking

**After** (v2):
- ✅ Multiple concurrent tasks supported
- ✅ Clear per-task organization
- ✅ Archive completed tasks to `completed/`
- ✅ Timestamps track creation and updates
- ✅ Easy to see what's active vs. done
- ✅ Better scalability for long-term project

---

## Next Steps

1. **Test on real task**: Use for next major analysis task
2. **Refine templates**: Adjust based on actual usage
3. **Consider automation**: Slash command to create new task directory?
4. **Add to hooks**: Remind to update timestamps before context compaction

---

*Continuous improvement based on community best practices*
