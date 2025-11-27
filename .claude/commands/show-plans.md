---
description: Show all active plans in dev-docs with status and last updated time
---

# Active Dev-Docs Plans

Scan and display all active plans from `.claude/dev-docs/active/` directory.

For each active plan, show:
- **Task name** (directory name)
- **Status** (from plan.md)
- **Priority** (from plan.md)
- **Last Updated** (from plan.md or file modification time)
- **Progress** (from tasks.md - count completed vs total tasks)

Use the following tools to gather this information:

1. **List all active task directories**:
```bash
ls -1 .claude/dev-docs/active/
```

2. **For each directory**, read:
   - `plan.md` - Extract status, priority, last updated
   - `tasks.md` - Count completed tasks (lines with `- [x]`)

3. **Display results** in a formatted table:

```
================================================================================
ACTIVE DEV-DOCS PLANS
================================================================================

[Task Name 1]
  Status:       In Progress
  Priority:     HIGH
  Last Updated: 2025-11-27 12:30
  Progress:     5/12 tasks completed (42%)
  Location:     .claude/dev-docs/active/task-name-1/

[Task Name 2]
  Status:       Planning
  Priority:     MEDIUM
  Last Updated: 2025-11-26 15:45
  Progress:     0/8 tasks completed (0%)
  Location:     .claude/dev-docs/active/task-name-2/

================================================================================
Total: 2 active plans
================================================================================
```

4. **If no active plans exist**, show:
```
No active dev-docs plans found.

Use /create-dev-docs to create a new plan for a multi-session task.
```

5. **Additional information**:
   - Provide quick links to view each plan: "Use `Read .claude/dev-docs/active/[task-name]/plan.md` to view details"
   - If a plan hasn't been updated in >7 days, note: "⚠️ Stale - not updated in X days"

**Implementation**: Use Bash and Read tools to gather information, then format and present to user.
