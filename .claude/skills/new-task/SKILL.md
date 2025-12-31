---
name: new-task
description: Create a new task with dev-docs structure. Use when starting a new multi-session task. Keywords: new task, create task, dev-docs, scaffold, template.
---

# New Task Skill

Creates dev-docs structure for a new task under `dev-docs/active/`.

## Usage

```
/new-task <task-name> [--channel CHANNEL] [--description "DESCRIPTION"]
```

## What It Creates

```
dev-docs/active/{task-name}/
├── context.md   # Goal, key paths, environment, critical notes
├── plan.md      # Implementation phases, dependencies
└── tasks.md     # Status table, session notes, next steps
```

## Template: context.md

```markdown
# Context: {TASK_NAME}

## Goal
{DESCRIPTION}

## Key Paths
- Config: `config/analysis_config_{channel}_{version}.yaml`
- Stage 1-2: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}/...`
- WH output: `{stage2_path}/mc/variableHists_{hist}/`

## Environment
- Stages 1-4.4, 4.7: `source setEnv_newNew.sh`
- Stages 4.4.1, 4.5: `cmsenv` in hua/combine/

## Critical Notes
- [Add task-specific notes]

## Related Tasks
- [Link to related dev-docs tasks]
```

## Template: plan.md

```markdown
# Plan: {TASK_NAME}

## Phases

### Phase 1: Setup
- [ ] Create/verify config
- [ ] Check Stage 1-2 status

### Phase 2: Stage 3 (WH)
- [ ] Submit WH for all eras with `--systematic complete`
- [ ] Wait for completion

### Phase 3: Stage 4
- [ ] addJES for all eras
- [ ] addTemplate for all eras
- [ ] smooth (sync point)
- [ ] writeDatacard for all eras

### Phase 4: Combination
- [ ] writeCombinationDatacard
- [ ] Run combine fits

## Dependencies
- [List dependencies on other tasks/channels]
```

## Template: tasks.md

```markdown
# Tasks: {TASK_NAME}

## Status Summary
| Era | S1-2 OS/MV | S3 WH | S4.1 addJES | S4.2-4.4 | S4.5 combine |
|-----|------------|-------|-------------|----------|--------------|
| 2018 | - | - | - | - | - |
| 2017 | - | - | - | - | - |
| 2016preVFP | - | - | - | - | - |
| 2016postVFP | - | - | - | - | - |
| **Run2** | - | - | - | - | PENDING |

## Current Phase: Setup

### Session {DATE}

**Completed:**
- [ ] Task created

**Next Steps:**
- [ ] [First step]

## Last Updated
{TIMESTAMP}
```

## Implementation

When this skill is invoked, Claude should:

1. Parse arguments for task-name, channel, description
2. Create directory: `dev-docs/active/{task-name}/`
3. Create context.md, plan.md, tasks.md from templates
4. Customize based on channel (1tau0l, 1tau1l, 1tau2l)
5. Report created files

## Example

```
/new-task workflow-1tau0l-v2 --channel 1tau0l --description "Run 1tau0l with v2BDT for validation"
```

Creates:
```
dev-docs/active/workflow-1tau0l-v2/
├── context.md   (channel=1tau0l, description filled)
├── plan.md      (standard phases)
└── tasks.md     (status table ready)
```
