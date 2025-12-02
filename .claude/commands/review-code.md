# Review Code Quality

Review recently modified Python files for code quality issues.

## Instructions

1. **Find modified files** - Check git status and recent commits for changed Python files

2. **Run quality checker** on each file:
   ```bash
   python3 .claude/hooks/check_python_quality.py <file.py>
   ```

3. **Summarize issues** in a table format:
   | File | Issues | Warnings |
   |------|--------|----------|
   | ... | ... | ... |

4. **For each issue**, identify:
   - Which function has the problem
   - What type of issue (long function, deep nesting, high complexity)
   - Suggested refactoring approach

5. **Ask user** if they want to:
   - Fix issues now (invoke the `refactor` skill)
   - Defer to later
   - Ignore specific issues

## Quality Thresholds (from settings.json)

- Function length: max 80 lines, recommended 50
- Nesting depth: max 5, recommended 3
- Branches: max 20, recommended 10
- File length: max 1000, recommended 500

## Arguments

- No arguments: Review all uncommitted Python files
- `<file.py>`: Review specific file
- `--recent N`: Review files changed in last N commits
