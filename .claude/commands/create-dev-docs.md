---
description: Create comprehensive dev-docs with plan, context, and tasks for a new multi-session task
---

# Create Dev-Docs for Multi-Session Task

You are now in **dev-docs creation mode**. Your goal is to:

1. **Gather context efficiently** - Ask targeted questions to understand:
   - What is the task/goal?
   - What files/components are involved?
   - What are the constraints or requirements?
   - What is the current state vs desired state?

2. **Analyze project structure** - Identify relevant:
   - Code files and their purposes
   - Configuration files
   - Documentation
   - Dependencies and interactions

3. **Create comprehensive structured plan** with:
   - **Executive Summary**: 2-3 sentence overview of the task and approach
   - **Problem Statement**: Clear description of what needs to be solved
   - **Current State**: What exists now
   - **Desired State**: What we want to achieve
   - **Phases**: Major stages of work (e.g., Phase 1: Investigation, Phase 2: Implementation)
   - **Tasks**: Specific actionable items within each phase
   - **Risks**: Potential issues and mitigation strategies
   - **Success Criteria**: Measurable outcomes that define completion
   - **Timeline Estimates**: Realistic time expectations for each phase

4. **Generate three files automatically** after plan is formed:

   **File 1: `plan.md`**
   ```markdown
   # Plan: [Task Name]

   **Created**: YYYY-MM-DD HH:MM
   **Status**: Planning / In Progress / Complete
   **Priority**: HIGH / MEDIUM / LOW

   ---

   ## Executive Summary

   [2-3 sentence overview]

   ---

   ## Problem Statement

   [Clear description of what needs to be solved]

   ---

   ## Current State

   [What exists now, including relevant file paths and line numbers]

   ---

   ## Desired State

   [What we want to achieve]

   ---

   ## Approach

   ### Phase 1: [Name] (estimated time)

   **Goals**:
   - Goal 1
   - Goal 2

   **Tasks**:
   1. Task 1
   2. Task 2

   **Deliverables**:
   - Deliverable 1
   - Deliverable 2

   ### Phase 2: [Name] (estimated time)

   [Similar structure]

   ---

   ## Risks and Mitigations

   **Risk 1**: [Description]
   - **Likelihood**: High / Medium / Low
   - **Impact**: High / Medium / Low
   - **Mitigation**: [Strategy]

   ---

   ## Success Criteria

   - [ ] Criterion 1
   - [ ] Criterion 2

   ---

   ## Timeline

   - Phase 1: [X hours/days]
   - Phase 2: [X hours/days]
   - **Total**: [X hours/days]
   ```

   **File 2: `context.md`**
   ```markdown
   # Context: [Task Name]

   **Created**: YYYY-MM-DD HH:MM
   **Last Updated**: YYYY-MM-DD HH:MM

   ---

   ## Problem Overview

   [Brief summary of the problem and why we're solving it]

   ---

   ## Key Files

   **File 1**: `path/to/file.ext`
   - **Purpose**: [What this file does]
   - **Relevant sections**: Lines X-Y, Functions A, B
   - **Notes**: [Important context]

   **File 2**: `path/to/file2.ext`
   - [Similar structure]

   ---

   ## Key Concepts

   **Concept 1**: [Technical concept name]
   - [Explanation relevant to this task]

   **Concept 2**: [Another concept]
   - [Explanation]

   ---

   ## Dependencies

   - Dependency 1: [Why it matters]
   - Dependency 2: [Why it matters]

   ---

   ## Constraints

   - Constraint 1: [Description]
   - Constraint 2: [Description]

   ---

   ## Related Documentation

   - [Link or path to doc 1]
   - [Link or path to doc 2]
   ```

   **File 3: `tasks.md`**
   ```markdown
   # Tasks: [Task Name]

   **Created**: YYYY-MM-DD HH:MM
   **Last Updated**: YYYY-MM-DD HH:MM
   **Status**: [Current phase]

   ---

   ## Phase 1: [Name]

   ### Task 1.1: [Task name]
   - [ ] Subtask 1
   - [ ] Subtask 2
   - [ ] Subtask 3

   **Status**: Not Started / In Progress / Complete / Blocked
   **Notes**: [Any relevant notes]

   ### Task 1.2: [Task name]
   - [ ] Subtask 1
   - [ ] Subtask 2

   **Status**: Not Started / In Progress / Complete / Blocked

   ---

   ## Phase 2: [Name]

   ### Task 2.1: [Task name]
   - [ ] Subtask 1
   - [ ] Subtask 2

   **Status**: Not Started / In Progress / Complete / Blocked

   ---

   ## Success Criteria Checklist

   - [ ] Success criterion 1
   - [ ] Success criterion 2
   - [ ] Success criterion 3

   ---

   ## Notes

   - [Add any ongoing notes, blockers, or important discoveries here]
   ```

## Process

1. **Ask clarifying questions** to gather context (be efficient, max 3-5 questions)
2. **Search and read relevant files** to understand current state
3. **Create the plan** with all sections filled out
4. **Present plan to user** for approval
5. **After approval**, automatically create the three files in `dev-docs/active/[task-name]/`
   - Ask user for task name (suggest one from plan title)
   - Create directory: `dev-docs/active/[task-name]/`
   - Write `plan.md`, `context.md`, `tasks.md`
   - Inform user: "Dev-docs created at dev-docs/active/[task-name]/"

## Important Guidelines

- **Be efficient**: Don't ask unnecessary questions, use existing context from CLAUDE.md and conversation
- **Be specific**: Include file paths with line numbers, not vague references
- **Be realistic**: Timeline estimates should account for actual complexity
- **Be actionable**: Tasks should be specific and measurable
- **Focus on risks**: Anticipate what could go wrong and plan for it
- **Define success clearly**: Make it obvious when the task is complete

---

**Now**: Ask the user what task they want to plan, then follow the process above.
