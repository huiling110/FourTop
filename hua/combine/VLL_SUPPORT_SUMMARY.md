# VLL Support Implementation Summary

## Overview
Added comprehensive VLL (Vector-Like Lepton) analysis support to `runCombineAll.py` while maintaining full backward compatibility with existing four-top (tttt) analysis workflows.

## Changes Made

### 1. New Command-Line Arguments

**File**: `runCombineAll.py` (Lines 63-67)

```python
parser.add_argument('--ifVLL', '--VLL', dest='ifVLL', action='store_true',
                    help='Run VLL (Vector-Like Lepton) analysis instead of tttt analysis')
parser.add_argument('--channel', type=str, default='1tau1l',
                    help='Analysis channel for VLL (e.g., 1tau1l, 1tau0l, 1tau2l). Only used with --ifVLL')
parser.set_defaults(ifBlind=False, ifVLL=False)
```

### 2. Enhanced Main Function

**File**: `runCombineAll.py` (Lines 80-98)

- Extracts VLL parameters from arguments
- Displays analysis type (VLL Search vs Four-Top Search)
- Shows channel information for VLL analyses
- Passes VLL parameters to all relevant functions

```python
ifVLL = args.ifVLL
channel = args.channel

analysis_type = "VLL Search" if ifVLL else "Four-Top Search"
logger.info(f"CMS Combine Analysis Workflow - {analysis_type}")
if ifVLL:
    logger.info(f"VLL analysis channel: {channel}")
```

### 3. Updated Functions with VLL Support

#### A. `goodnessOfFit()` - Lines 160-225

**Changes**:
- Added `ifVLL=False` and `channel='1tau1l'` parameters
- Uses channel-specific datacard for VLL: `datacard_{channel}.root`
- Falls back to `datacard.root` for tttt analysis
- Logs which datacard is being used
- Added try/finally for safe directory management

```python
def goodnessOfFit(cardDir, ifVLL=False, channel='1tau1l'):
    if ifVLL:
        datacardFile = cardDir + f'workspace/datacard_{channel}.root'
        logger.info(f"Using VLL datacard: datacard_{channel}.root")
    else:
        datacardFile = cardDir + 'workspace/datacard.root'
        logger.info(f"Using tttt datacard: datacard.root")
```

#### B. `measureSignalStrength()` - Lines 228-296

**Changes**:
- Added `ifVLL=False` and `channel='1tau1l'` parameters
- Uses channel-specific datacard for VLL: `datacard_{channel}.root`
- Falls back to `datacard.root` for tttt analysis
- Logs which datacard is being used

```python
def measureSignalStrength(cardDir, ifVLL=False, channel='1tau1l'):
    if ifVLL:
        datacardFile = cardDir + f'workspace/datacard_{channel}.root'
        logger.info(f"Using VLL datacard: datacard_{channel}.root")
    else:
        datacardFile = cardDir + 'workspace/datacard.root'
        logger.info(f"Using tttt datacard: datacard.root")
```

#### C. `runCombineSig()` - Lines 439-490

**Changes**:
- Added `ifVLL=False` and `channel='1tau1l'` parameters
- Enhanced logging shows:
  - Analysis type (tttt/VLL)
  - Calculation type (Limits/Significance)
  - Blind mode (blinded/unblinded)
  - VLL channel when applicable
- Processes all ROOT files in workspace directory (works for both tttt and VLL)

```python
def runCombineSig(cardDir, isLimit, ifBlind=True, ifVLL=False, channel='1tau1l'):
    analysis_type = "VLL" if ifVLL else "tttt"
    calc_type = "Limits" if isLimit else "Significance"
    blind_mode = "blinded (expected)" if ifBlind else "unblinded (observed)"
    logger.info(f"Running {analysis_type} {calc_type} calculation - {blind_mode}")
    if ifVLL:
        logger.info(f"VLL channel: {channel}")
```

### 4. Updated Function Calls in Main Workflow

**File**: `runCombineAll.py` (Lines 117, 124, 146, 153)

All VLL-aware functions now receive the VLL parameters:

```python
# Limits calculation
runCombineSig(cardDir, True, ifBlind, ifVLL, channel)

# Significance calculation
runCombineSig(cardDir, False, ifBlind, ifVLL, channel)

# Signal strength measurement
measureSignalStrength(cardDir, ifVLL, channel)

# Goodness-of-fit test
goodnessOfFit(cardDir, ifVLL, channel)
```

### 5. Updated Help and Documentation

**Help message examples** (Lines 51-55):

```bash
# VLL analysis (Vector-Like Lepton search)
python runCombineAll.py --cardDir combinationV10/run2_1tau1l_VLLm600/ --no-blind --ifVLL --channel 1tau1l

# VLL analysis with specific steps
python runCombineAll.py --cardDir combinationV10/run2_1tau0l_VLLm650/ --no-blind --ifVLL --channel 1tau0l --steps gof
```

## Key Design Decisions

### 1. Datacard Naming Convention
- **tttt analysis**: Uses `datacard.root` (generic name)
- **VLL analysis**: Uses `datacard_{channel}.root` (channel-specific)
- This is the primary difference between tttt and VLL workflows

### 2. Backward Compatibility
- All VLL parameters have default values (`ifVLL=False`, `channel='1tau1l'`)
- Without `--ifVLL` flag, behavior is identical to original code
- All existing tttt workflows work unchanged

### 3. Other Functions (No Changes Needed)
The following functions work for both tttt and VLL without modification:
- `cardToWorkspaces()` - Processes all `.txt` datacards in directory
- `runPostFitPlots()` - Processes all `.root` files in workspace
- `runImpact()` - Processes all `.root` files in workspace
- `copyCombineResultsToDir()` - Moves all result files

These functions iterate over files in the workspace directory, so they automatically handle both tttt and VLL datacard naming schemes.

## Usage Examples

### Four-Top (tttt) Analysis (unchanged)
```bash
# Traditional tttt analysis - no changes needed
python3 runCombineAll.py --cardDir combinationV18/run2_1tau1l_v4_unblind/ --no-blind
```

### VLL Analysis (new)
```bash
# Full VLL analysis workflow
python3 runCombineAll.py --cardDir combinationV10/run2_1tau1l_VLLm600/ --no-blind --ifVLL --channel 1tau1l

# VLL with specific steps
python3 runCombineAll.py --cardDir combinationV10/run2_1tau0l_VLLm650/ --no-blind --ifVLL --channel 1tau0l --steps workspace limits gof

# VLL blinded analysis
python3 runCombineAll.py --cardDir combinationV10/run2_1tau2l_VLLm700/ --ifBlind --ifVLL --channel 1tau2l
```

## Testing

✅ Python syntax validated
✅ Help message displays correctly with VLL options
✅ All arguments parse correctly with defaults
✅ Backward compatible - tttt workflows unchanged

## Files Modified

1. **`runCombineAll.py`** - Main analysis script with VLL support
2. **`IMPROVEMENTS.md`** - Updated with VLL feature documentation
3. **`VLL_SUPPORT_SUMMARY.md`** - This comprehensive summary (NEW)

## Reference

Implementation based on `/publicfs/cms/user/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/runCombineAll.py` which demonstrated the VLL-specific datacard naming pattern.
