#!/bin/bash
# Submit all systematic variations for Stage 1 (OS)
# Usage: ./submit_all_systematics.sh CONFIG ERA
#
# Example:
#   ./submit_all_systematics.sh ../../config/analysis_config_1tau0l_TTBBtest.yaml 2018

CONFIG=${1:-"../../config/analysis_config_1tau0l_TTBBtest.yaml"}
ERA=${2:-"2018"}

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Resolve config to absolute path before changing directory
if [[ "${CONFIG:0:1}" != "/" ]]; then
    CONFIG="$(cd "$(dirname "$CONFIG")" && pwd)/$(basename "$CONFIG")"
fi

cd "$SCRIPT_DIR/../.."

# Source environment
source setEnv_newNew.sh

# All systematic variations (TES only by decay mode, not total)
SYSTEMATICS=(
    "JES"
    "JERUp"
    "JERDown"
    "METUp"
    "METDown"
    "EleScaleUp"
    "EleScaleDown"
    "TESdm0Up"
    "TESdm0Down"
    "TESdm1Up"
    "TESdm1Down"
    "TESdm10Up"
    "TESdm10Down"
    "TESdm11Up"
    "TESdm11Down"
)

echo "============================================"
echo "Submitting ${#SYSTEMATICS[@]} systematic variations"
echo "Config: $CONFIG"
echo "Era: $ERA"
echo "============================================"
echo ""

for sys in "${SYSTEMATICS[@]}"; do
    echo "--------------------------------------------"
    echo "Submitting: $sys"
    echo "--------------------------------------------"
    python3 objectSelectionOptimized/jobs/makeJob_OS_fromRuobing2.py \
        --config "$CONFIG" \
        --era "$ERA" \
        --sys "$sys" \
        --quiet
    echo ""
done

echo "============================================"
echo "All systematic jobs submitted!"
echo "Monitor with: hep_q -u \$USER"
echo "============================================"
