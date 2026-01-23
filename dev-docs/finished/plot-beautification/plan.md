# Plot Beautification - Plan

## Approach
Add `--paper` flag to pl_postFit.py that enables all publication settings at once. Create centralized label mappings in fourtop package.

## Implementation Steps

### Phase 1: Create Label System
Create `fourtop/plotting/labels.py`:
- `PROCESS_LABELS_PAPER` - Internal name → paper label
- `REGION_LABELS` - Region code → formatted label
- `get_signal_label()` - Format scaled signal label

### Phase 2: Update Style Functions
Modify `fourtop/plotting/style.py`:
- Add `preliminary` parameter to `addCMSTextToPad()`
- Add `addRegionLabel()` function
- Add `addFitTypeLabel()` function

### Phase 3: Update Plotting Functions
Modify `plotting/pl.py`:
- `addLegend()` - Use paper labels when `ifPaper=True`
- `makeStackPlotNew()` - Add region/fit annotations
- `getHistToData()` - Reduce ratio y-axis divisions

### Phase 4: Add CLI Options
Modify `plotting/pl_postFit.py`:
- Add `--paper` flag
- Output to `publication/` subfolder
- Add `--no-sb` option for S/B text

## Dependencies
- fourtop package must be importable
- Existing plots should remain unchanged (backward compatible)

## Risks
- Breaking existing plotting functionality
- ROOT text positioning issues

## Mitigation
- Keep `--paper` as opt-in flag
- Test baseline first before adding changes
