# Dev-Docs System

**Purpose**: Maintain context through long analysis workflows and across Claude Code session resets.

---

## Directory Structure

```
.claude/dev-docs/
├── active/                    # Currently active tasks
│   ├── task-name-1/
│   │   ├── plan.md           # The accepted plan
│   │   ├── context.md        # Key files, decisions
│   │   └── tasks.md          # Work checklist
│   └── task-name-2/
│       └── ...
├── completed/                 # Archived completed tasks
│   └── old-task/
│       └── ...
└── TEMPLATE_*.md             # Templates for new tasks
```

---

## Starting a Major Task

### Automatic Creation (After Plan Mode)

**When exiting plan mode with an accepted plan**, Claude will automatically:
1. Ask for a task name (suggests from plan title)
2. Create `.claude/dev-docs/active/[task-name]/` directory
3. Generate `plan.md` from the accepted plan
4. Generate `context.md` with key files identified during planning
5. Generate `tasks.md` from plan steps
6. Inform you: "Dev-docs created at .claude/dev-docs/active/[task-name]/"

**Then proceed directly to implementation with full task tracking in place.**

---

### Manual Creation (Without Plan Mode)

### 1. Create Task Directory
```bash
mkdir -p .claude/dev-docs/active/[task-name]/
cd .claude/dev-docs/active/[task-name]/
```

### 2. Create Documents from Templates
```bash
cp ../../TEMPLATE_plan.md plan.md
cp ../../TEMPLATE_context.md context.md
cp ../../TEMPLATE_tasks.md tasks.md
```

### 3. Fill in the Documents
- **plan.md**: Goal, approach, validation plan
- **context.md**: Key file paths (with line numbers), decisions, constraints
- **tasks.md**: Detailed checklist of work items

### 4. Update Regularly
- Mark tasks complete **immediately** (don't batch)
- Add "Last Updated: YYYY-MM-DD HH:MM" timestamp to each file
- Update context when you discover important information

---

## Continuing Tasks

### For AI Assistant (Claude)
1. **Check for active tasks**: Look in `.claude/dev-docs/active/`
2. **Read all three files** before proceeding
3. **Update timestamps** when modifying files

### For User
Resume with: `"Continue [task-name] from dev-docs"`

Claude will automatically:
- Find the task directory in `.claude/dev-docs/active/`
- Read plan.md, context.md, tasks.md
- Continue exactly where you left off

---

## Archiving Completed Tasks

When a task is complete:
```bash
mv .claude/dev-docs/active/[task-name] .claude/dev-docs/completed/
```

This keeps the `active/` directory clean and focused on current work.

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
