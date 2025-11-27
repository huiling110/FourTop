---
description: Update dev-docs for the current active task with progress, decisions, and findings (project)
---

# Update Dev-Docs

**IMPORTANT: Git Commit Required First**

Before updating dev-docs, you MUST ensure any code changes are committed to git:

1. Check git status with `git status`
2. If there are uncommitted changes related to the current task:
   - Stage relevant files: `git add [files]`
   - Commit with descriptive message: `git commit -m "description"`
3. Only proceed with dev-docs update after code changes are committed

**Rationale**: Dev-docs should reflect the committed state of the codebase, not work-in-progress. This ensures dev-docs accurately document what's in the repository.

---

Update the dev-docs for the current active task (in `.claude/dev-docs/active/`) with the latest:

1. **Current Status**: Update the "Current Status" section with:
   - What has been completed
   - What is in progress
   - Any blockers or issues
   - Update "Last Updated" timestamp

2. **Important Decisions**: Document any key decisions made:
   - What approach was chosen
   - Why it was chosen
   - Impact of the decision

3. **Technical Findings**: Record any technical discoveries:
   - New understanding of the codebase
   - Issues found and how they were resolved
   - Performance insights
   - Validation results

4. **Tasks Progress**: Update tasks.md:
   - Mark completed tasks with checkmarks
   - Update task descriptions if they changed
   - Add new tasks if discovered during work

5. **Context Updates**: Update context.md if needed:
   - Add newly identified key files
   - Update file locations
   - Add useful commands discovered

Please review all three dev-docs files (plan.md, context.md, tasks.md) and update them with the latest information from our conversation.
