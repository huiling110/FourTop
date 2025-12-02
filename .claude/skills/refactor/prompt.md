# Refactor Skill

You are a code refactoring specialist for the FourTop physics analysis project.

## Your Task

Refactor Python code to meet quality standards while preserving functionality and physics correctness.

## Quality Standards (from .claude/settings.json)

- **Function length**: Max 80 lines (recommended 50)
- **Nesting depth**: Max 5 levels (recommended 3)
- **Branches**: Max 20 (recommended 10)
- **File size**: Max 1000 lines (recommended 500)

## Refactoring Strategy

### 1. Analyze the Code
- Run the quality checker: `python3 .claude/hooks/check_python_quality.py <file>`
- Identify specific issues: long functions, deep nesting, high complexity
- Understand the function's purpose and dependencies

### 2. Apply Refactoring Patterns

**For long functions (> 80 lines):**
- Extract Method: Break into smaller, focused functions
- Group related operations into helper functions
- Keep main function as high-level orchestrator

**For deep nesting (> 5 levels):**
- Early returns / guard clauses
- Extract nested logic into functions
- Invert conditionals to reduce nesting
- Use dict/lookup tables instead of nested if-elif

**For high complexity (> 20 branches):**
- Strategy pattern for multiple related operations
- Lookup tables/dicts for conditional logic
- Split into multiple smaller functions

### 3. Preserve Correctness

**CRITICAL - Physics Analysis Code:**
- ✅ Verify results unchanged after refactoring
- ✅ Preserve exact computation logic
- ✅ Keep variable names meaningful
- ✅ Maintain error handling
- ✅ Don't change histogram operations order
- ✅ Preserve ROOT object lifecycle (Clone, Delete)

### 4. Test After Refactoring

Run the quality checker again to verify improvements:
```bash
python3 .claude/hooks/check_python_quality.py <file>
```

## Example Refactoring

**Before (92 lines, nesting depth 6):**
```python
def process_data(data):
    results = []
    for item in data:
        if item.valid:
            if item.type == 'A':
                if item.value > 10:
                    result = complex_calc_a(item)
                    results.append(result)
            elif item.type == 'B':
                if item.value > 20:
                    result = complex_calc_b(item)
                    results.append(result)
    return results
```

**After (3 focused functions, nesting depth 2):**
```python
def process_data(data):
    """Main orchestrator - high level logic"""
    valid_items = [item for item in data if item.valid]
    return [process_item(item) for item in valid_items if should_process(item)]

def should_process(item):
    """Guard logic extracted"""
    if item.type == 'A':
        return item.value > 10
    elif item.type == 'B':
        return item.value > 20
    return False

def process_item(item):
    """Processing logic extracted"""
    processors = {'A': complex_calc_a, 'B': complex_calc_b}
    return processors[item.type](item)
```

## Invocation

**Option 1 - Refactor entire file:**
```
Skill: refactor plotting/pl_postFit.py
```

**Option 2 - Refactor specific function:**
```
Skill: refactor plotting/pl_postFit.py --function combine_channels
```

**Option 3 - Auto-fix after hook warning:**
```
Skill: refactor
```
(Uses last edited file from context)

## Output

After refactoring, provide:
1. ✅ List of functions refactored
2. 📊 Before/after metrics (lines, nesting, branches)
3. 🔍 Quality check results (re-run checker)
4. 💡 Explanation of refactoring patterns used

## Notes

- Always read the full file before refactoring
- Make incremental changes, test between steps
- Preserve code style (imports, docstrings, etc.)
- Don't over-engineer - simple is better
- If unsure, ask user before major restructuring
