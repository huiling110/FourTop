#!/bin/bash
# Universal script for running combine fits (Stage 4.5-4.6)
# Usage: ./run_combine_fits.sh CONFIG ERA CHANNEL
#
# Examples:
#   ./run_combine_fits.sh ../../config/analysis_config_1tau1l_TTBBtest.yaml 2018 1tau1l
#   ./run_combine_fits.sh ../../config/analysis_config_1tau0l_TTBBtest.yaml 2017 1tau0l
#   ./run_combine_fits.sh ../../config/analysis_config_1tau1l_TTBBtest.yaml run2 1tau1l  # Run2 combination
#
# Recommended: Run in screen session for long-running jobs
#   screen -S combine_1tau1l_2018
#   ./run_combine_fits.sh ../../config/analysis_config_1tau1l_TTBBtest.yaml 2018 1tau1l
#   Ctrl+A, D (to detach)

# Parse arguments
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 CONFIG_FILE ERA CHANNEL"
    echo ""
    echo "Arguments:"
    echo "  CONFIG_FILE: Path to YAML config (e.g., ../../config/analysis_config_1tau1l_TTBBtest.yaml)"
    echo "  ERA: Era to process (2018, 2017, 2016preVFP, 2016postVFP, run2)"
    echo "  CHANNEL: Channel name (1tau1l, 1tau0l, 1tau2l)"
    echo ""
    echo "Example:"
    echo "  $0 ../../config/analysis_config_1tau1l_TTBBtest.yaml 2018 1tau1l"
    echo "  $0 ../../config/analysis_config_1tau1l_TTBBtest.yaml run2 1tau1l  # Run2 combination"
    exit 1
fi

CONFIG_FILE="$1"
ERA="$2"
CHANNEL="$3"

echo "=== Combine Fits for ${CHANNEL} ${ERA} ==="
echo "Start time: $(date)"
echo "Config: $CONFIG_FILE"
echo ""

# Setup CMSSW environment
echo "Setting up CMSSW environment..."
cd /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`

# Go to combine directory
cd FourTop/hua/combine

# Build datacard directory path from config
# For run2, use the combination datacard; otherwise use per-era datacard
if [ "$ERA" = "run2" ]; then
    # Run2 combination - get combination version from config
    CARDDIR=$(python3 << PYEOF
import sys
sys.path.insert(0, '../../plotting')
from workflow_utils import load_config

config = load_config('$CONFIG_FILE')
combination_version = config['versions'].get('combination', 'V22')
channel = '${CHANNEL}'
# Handle both "V22" and "combinationV22" formats
ver = str(combination_version)
if ver.startswith('combinationV'):
    cardDir = f"{ver}/run2_{channel}_v4/"
elif ver.startswith('V'):
    cardDir = f"combination{ver}/run2_{channel}_v4/"
else:
    cardDir = f"combinationV{ver}/run2_{channel}_v4/"
print(cardDir)
PYEOF
)
else
    # Per-era datacard
    CARDDIR=$(python3 << PYEOF
import sys
sys.path.insert(0, '../../plotting')
from workflow_utils import load_config, build_hist_path

config = load_config('$CONFIG_FILE')
hist_path = build_hist_path(config, '$ERA')
datacard_version = config['versions']['datacard']
cardDir = f"{hist_path}combine/datacardSys_{datacard_version}/"
print(cardDir)
PYEOF
)
fi

echo "Datacard directory: $CARDDIR"
echo ""

# Check if datacard exists
if [ ! -f "${CARDDIR}datacard.txt" ]; then
    echo "ERROR: Datacard not found at ${CARDDIR}datacard.txt"
    echo "Please run Stage 4.3 (writeDatacard) first"
    exit 1
fi

# Create log filename
LOG_FILE="combine_${CHANNEL}_${ERA}_$(date +%Y%m%d_%H%M%S).log"

echo "Running combine with steps: workspace significance exp_significance postfit signal_strength impacts"
echo "Log file: $LOG_FILE"
echo "This will take 1-2 hours..."
echo ""

# Run combine with all steps
# Steps: workspace, significance, exp_significance, postfit, signal_strength, impacts
python3 runCombineAll.py \
    --cardDir "$CARDDIR" \
    --channel "$CHANNEL" \
    --no-blind \
    --steps workspace significance exp_significance postfit signal_strength impacts \
    2>&1 | tee "$LOG_FILE"

EXIT_CODE=${PIPESTATUS[0]}

echo ""
echo "=== Combine Fits Complete ==="
echo "End time: $(date)"
echo "Exit code: $EXIT_CODE"
echo "Log saved to: $(pwd)/$LOG_FILE"

if [ $EXIT_CODE -eq 0 ]; then
    echo "✓ SUCCESS: All combine steps completed"
else
    echo "✗ ERROR: Combine failed with exit code $EXIT_CODE"
    echo "Check log file for details: $LOG_FILE"
fi

exit $EXIT_CODE
