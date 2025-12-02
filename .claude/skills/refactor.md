# Refactor Skill - Python Code Quality

Automatically refactor Python code to meet quality standards while preserving physics correctness.

## When to Use

- After code quality hooks detect issues (exit code 2)
- When improving maintainability of analysis scripts
- After completing a major feature/phase

## Quality Thresholds

From `.claude/settings.json`:
- **Max function lines**: 80 (recommended: 50)
- **Max nesting depth**: 5 (recommended: 3)
- **Max branches**: 20 (recommended: 10)
- **Max file lines**: 1000 (recommended: 500)

## Instructions

### Step 1: Identify Files to Review

Run the quality checker on recently modified Python files:

```bash
# Check specific file
python3 .claude/hooks/check_python_quality.py <file.py>

# Check all modified Python files
git diff --name-only HEAD~5 | grep '\.py$' | xargs -I{} python3 .claude/hooks/check_python_quality.py {}
```

### Step 2: Analyze Issues

For each issue found, identify the root cause:

1. **Long functions (>80 lines)**:
   - Look for logical sections that can be extracted
   - Identify repeated patterns
   - Find setup/cleanup code that can be separated

2. **Deep nesting (>5 levels)**:
   - Use early returns/guard clauses
   - Extract nested logic into helper functions
   - Simplify condition chains

3. **High complexity (>20 branches)**:
   - Use dispatch tables/dictionaries instead of if/elif chains
   - Extract case handling into separate functions
   - Consider strategy pattern for different behaviors

### Step 3: Refactor with Physics Safety

**CRITICAL**: Physics analysis code must remain correct. When refactoring:

1. **Preserve semantics**: Output must be identical before/after
2. **Keep variable names**: Physics variables have meaning (pt, eta, phi, etc.)
3. **Maintain order**: Some operations are order-dependent
4. **Test after refactoring**: Run on small sample to verify

### Step 4: Common Refactoring Patterns

#### Extract Function
```python
# Before: Long function with multiple responsibilities
def process_data():
    # 50 lines of setup
    # 30 lines of processing
    # 20 lines of cleanup

# After: Smaller focused functions
def setup_processing():
    ...
def do_processing(data):
    ...
def cleanup_processing():
    ...
def process_data():
    data = setup_processing()
    result = do_processing(data)
    cleanup_processing()
    return result
```

#### Guard Clauses (reduce nesting)
```python
# Before: Nested conditions
def process(item):
    if item is not None:
        if item.valid:
            if item.ready:
                # actual logic here
                pass

# After: Early returns
def process(item):
    if item is None:
        return
    if not item.valid:
        return
    if not item.ready:
        return
    # actual logic here (less nested)
```

#### Dispatch Table (reduce branches)
```python
# Before: Long if/elif chain
def handle_stage(stage):
    if stage == "4.1":
        run_4_1()
    elif stage == "4.2":
        run_4_2()
    # ... many more

# After: Dictionary dispatch
STAGE_HANDLERS = {
    "4.1": run_4_1,
    "4.2": run_4_2,
    # ...
}
def handle_stage(stage):
    handler = STAGE_HANDLERS.get(stage)
    if handler:
        handler()
```

### Step 5: Verify and Report

After refactoring:
1. Run quality checker again to confirm issues resolved
2. Run any available tests
3. Report changes made and improvements achieved

## Example Workflow

```
User: The code quality check failed for run_workflow.py