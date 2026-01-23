---
paths:
  - "dev-docs/**/*"
  - "**/*.md"
globs:
  - "**/plan*.md"
  - "**/tasks*.md"
---

# Dev-Docs Requirement - MUST FOLLOW

## After Plan Mode Approval

When ExitPlanMode is approved (user accepts plan), you MUST IMMEDIATELY:

1. **Create dev-docs directory**: `dev-docs/active/{task-name}/`
2. **Create 3 files**:
   - `context.md` - Goal, key files, environment, critical notes
   - `plan.md` - Approach, steps, dependencies, risks
   - `tasks.md` - Status table, session notes, next steps

## Example Structure

```
dev-docs/active/plot-beautification/
├── context.md   # What: goal, files, environment
├── plan.md      # How: approach, steps, risks
└── tasks.md     # Status: table, session notes
```

## When to Create

- After plan approval for ANY multi-step task
- Before starting implementation work
- For tasks expected to span multiple sessions

## Updating Dev-Docs

- Update `tasks.md` status table as you complete items
- Add session notes at end of each session
- Move to `dev-docs/finished/` when task complete
