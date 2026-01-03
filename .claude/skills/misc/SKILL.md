---
name: misc
description: Miscellaneous utilities - archiving, cleanup, disk management. Keywords: archive, zip, cleanup, disk, storage, tar.gz
---

# Miscellaneous Utilities

## Archive and Cleanup Script

Archives (tar.gz) and deletes Stage 1 OS systematic directories to save disk space.

**Location**: `scripts/archive_and_cleanup.sh`

### Pre-Archiving Checklist

**IMPORTANT**: Before archiving OS systematics, verify downstream stages completed successfully:

```bash
# 1. Verify MV systematics all completed (files exist + valid ROOT)
cd makeVariables_goodCode/
python3 verify_mv_completion.py --config ../config/CONFIG.yaml --era 2018 --validate

# 2. Only archive OS after MV shows "ALL COMPLETE (validated)"
```

This ensures OS files aren't deleted while still needed for reprocessing.

### Usage

```bash
# Dry run (see what would happen)
./scripts/archive_and_cleanup.sh --dry-run --era UL2018 --pattern "v95XGB080testOS7"

# Actually archive and delete (use screen!)
screen -S archive_2018
./scripts/archive_and_cleanup.sh --confirm --era UL2018 --pattern "v95XGB080testOS7"
# Detach: Ctrl+A D

# Or run detached directly
screen -dmS archive_2018 bash -c './scripts/archive_and_cleanup.sh --confirm --era UL2018 --pattern "v95XGB080testOS7" > /tmp/archive.log 2>&1'
```

### Options

| Flag | Description |
|------|-------------|
| `--dry-run` | Show what would be done without doing it |
| `--confirm` | **Required** to actually delete (safety feature) |
| `--era` | Era directory (e.g., UL2018, UL2017) |
| `--pattern` | Directory name pattern to match |

### Safety Features

- Requires `--confirm` flag to actually delete
- Verifies tar.gz integrity before deleting original
- Creates file list backup before deletion
- Skips nominal directory (no suffix)
- Archives stored in same directory as source

### Monitor Progress

```bash
# Check screen session
screen -r archive_2018

# Check log
tail -f /tmp/archive.log

# Check created archives
ls -lh /publicfs/.../UL2018/*.tar.gz
```

### Typical Runtime

- ~13 minutes per directory (4.7GB compressed)
- 9 TES directories = ~2 hours total

---

## Systematic Fluctuation Checker

Analyzes template files to identify systematic variations with large bin-to-bin fluctuations that may indicate smoothing issues or low statistics.

**Location**: `plotting/check_systematic_fluctuations.py`

### Basic Usage

```bash
source setEnv_newNew.sh

# Basic analysis (threshold 10%)
python3 plotting/check_systematic_fluctuations.py TEMPLATE.root

# Custom threshold (e.g., 15%)
python3 plotting/check_systematic_fluctuations.py TEMPLATE.root --threshold 15

# Full analysis with all plots
python3 plotting/check_systematic_fluctuations.py TEMPLATE.root \
    --threshold 10 \
    --total-systematic \
    --top-per-process 5
```

### Options

| Flag | Description |
|------|-------------|
| `--threshold N` | Minimum fluctuation score to report (default: 10%) |
| `--total-systematic` | Generate total systematic uncertainty plot per process |
| `--top-per-process N` | Plot top N systematics per process |
| `--no-plots` | Skip plot generation, only print report |
| `--max-plots N` | Maximum number of systematics to plot (default: 30) |
| `--compare-smoothed FILE` | Compare with smoothed template |
| `--datacard FILE` | Filter systematics using datacard |
| `--channel NAME` | Channel name (default: 1tau1l) |

### Example Commands

```bash
# Check fluctuations on smoothed template
python3 plotting/check_systematic_fluctuations.py \
    /path/to/templatesForCombine1tau1l_v3_smoothed.root \
    --threshold 10 --total-systematic --top-per-process 5

# Compare before/after smoothing
python3 plotting/check_systematic_fluctuations.py \
    /path/to/original.root \
    --compare-smoothed /path/to/smoothed.root \
    --top-per-process 5

# Quick report without plots
python3 plotting/check_systematic_fluctuations.py TEMPLATE.root --no-plots
```

### Output

Output is saved to `{template_dir}/systematic_fluctuations/`:
- `fluctuation_report.txt` - Ranked list of problematic variations
- `top5_systematics_{process}.png` - Top 5 systematics per process
- `total_systematic_{process}.png` - Total uncertainty per process
- `systematic_*.png` - Individual systematic shape comparisons

### Interpretation

| Score | Meaning |
|-------|---------|
| < 10% | Acceptable |
| 10-30% | Monitor |
| 30-50% | Consider smoothing |
| > 50% | Requires fixing (smoothing or merging) |

### Key Metrics

- **Max%**: Maximum variation in any bin
- **RMS%**: Root-mean-square of variations across bins
- **Max Δ**: Maximum bin-to-bin change (shape distortion indicator)
