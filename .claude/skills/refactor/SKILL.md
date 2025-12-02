---
name: refactor
description: Automatically refactor Python code to meet quality standards while preserving physics correctness. Handles long functions (>80 lines), deep nesting (>5 levels), and high complexity (>20 branches). Use when code quality hooks detect issues or when improving maintainability of analysis scripts.
---

# Refactor Skill

Refactors Python code in the FourTop physics analysis project to meet quality standards.

## When to Use

- After code quality hooks report issues
- When functions exceed 80 lines
- When nesting depth exceeds 5 levels
- When branch complexity exceeds 20 decisions
- When improving code maintainability

## Quality Standards

From `.claude/settings.json`:
- Function length: Max 80 lines (recommended 50)
- Nesting depth: Max 5 levels (recommended 3)
- Branches: Max 20 (recommended 10)

## Refactoring Approach

1. **Analyze**: Run quality checker to identify issues
2. **Extract Methods**: Break long functions into focused helpers
3. **Reduce Nesting**: Use early returns and guard clauses
4. **Simplify Logic**: Replace nested if-elif with lookup tables
5. **Verify**: Ensure physics results unchanged

## Critical Constraints

For physics analysis code:
- ✅ Preserve exact computation logic
- ✅ Maintain ROOT histogram operations order
- ✅ Keep error propagation intact
- ✅ Don't change numerical results

See `prompt.md` for detailed methodology.
