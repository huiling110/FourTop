---
description: Resume an active task from dev-docs with full context
---

# Resume Active Task

Resume work on an active task by loading its dev-docs context.

## Usage

When user says:
- "Resume [task-name]"
- "Continue [task-name]"
- "Resume from dev-docs"
- Just calls this command: `/resume-task [task-name]`

## What This Command Does

1. **Find the task** in `.claude/dev-docs/active/[task-name]/`

2. **Load all context files**:
   - `plan.md` - Overall strategy, status, phases
   - `context.md` - Key files, commands, technical details
   - `tasks.md` - Checklist of what's done/pending

3. **Present summary** to user:
   - Current status (from plan.md)
   - What was last completed
   - What's next (from tasks.md)
   - Any blockers or issues

4. **Set up TodoWrite** with current tasks from tasks.md

5. **Ready to continue** - Ask user what they want to work on next

## Implementation Steps

1. List all active tasks if no task-name provided:
   ```bash
   ls -1 .claude/dev-docs/active/
   ```

2. If task-name provided, read the three key files:
   - `.claude/dev-docs/active/[task-name]/plan.md`
   - `.claude/dev-docs/active/[task-name]/context.md`
   - `.claude/dev-docs/active/[task-name]/tasks.md`

3. Parse tasks.md to extract:
   - Completed tasks (marked with [x] or ✅)
   - In-progress tasks (current work)
   - Pending tasks (next steps)

4. Create TodoWrite with tasks in proper status

5. Present summary:
   ```
   ## Resuming Task: [task-name]

   **Status**: [from plan.md]
   **Last Updated**: [timestamp from plan.md]

   ### Completed:
   - [list completed tasks]

   ### In Progress:
   - [current task]

   ### Next Steps:
   - [pending tasks]

   ### Key Files:
   - [from context.md]

   What would you like to work on?
   ```

## Example

User: `/resume-task publicfs-cleanup`

Assistant loads:
- `.claude/dev-docs/active/publicfs-cleanup/plan.md`
- `.claude/dev-docs/active/publicfs-cleanup/context.md`
- `.claude/dev-docs/active/publicfs-cleanup/tasks.md`

Then presents:
```
## Resuming Task: publicfs-cleanup

**Status**: 🚀 Cleanup Executing - log/jobSH cleanup in progress
**Last Updated**: 2025-11-27 14:00

### Completed:
- Created three cleanup scripts (manage_systematic_histograms.py, survey_all_files.py, cleanup_logs_jobsh.py)
- Ran comprehensive surveys to identify file quota consumers
- Executed dry-run cleanup (273K files to be freed)
- Started cleanup execution

### In Progress:
- Execute cleanup: zip 191K log files, delete 82K jobSH files (~273K files total)

### Next Steps:
- After successful cleanup, document cleanup scripts in ANALYSIS_WORKFLOW.md Stage 3.4

### Key Files:
- plotting/cleanup_logs_jobsh.py - Main cleanup script
- plotting/manage_systematic_histograms.py - Survey systematic histograms
- plotting/survey_all_files.py - Comprehensive file survey

What would you like to work on?
```

## Notes

- If task directory doesn't exist, list available tasks
- If no active tasks exist, suggest creating one with `/create-dev-docs`
- Always show timestamps to know how stale the context is
- Don't automatically start work - let user choose next action
