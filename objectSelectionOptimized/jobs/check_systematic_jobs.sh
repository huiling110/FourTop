#!/bin/bash
# Check status of systematic variation jobs for Stage 1 (OS)
# Usage: ./check_systematic_jobs.sh [ERA]
#
# Example:
#   ./check_systematic_jobs.sh 2018

ERA=${1:-"2018"}
BASE_DIR="/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD"
VERSION="v94HadroPreJetVetoHemOnly_TTBBtest"

# Map era to UL directory
case $ERA in
    "2018") UL_ERA="UL2018" ;;
    "2017") UL_ERA="UL2017" ;;
    "2016postVFP"|"2016") UL_ERA="UL2016_postVFP" ;;
    "2016preVFP"|"2016APV") UL_ERA="UL2016_preVFP" ;;
    *) UL_ERA="UL${ERA}" ;;
esac

# All systematic variations (TES only by decay mode, not total)
SYSTEMATICS=(
    "JESPt22"
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
echo "Checking systematic job outputs for $ERA"
echo "============================================"
echo ""

# Check running jobs first
echo "--- Current jobs in queue ---"
hep_q -u $USER 2>/dev/null | head -5
NJOBS=$(hep_q -u $USER 2>/dev/null | grep -c "OS_")
echo "OS jobs running/queued: $NJOBS"
echo ""

# Check each systematic output
echo "--- Output directory status ---"
printf "%-20s %10s %10s %s\n" "Systematic" "MC Files" "Errors" "Status"
echo "------------------------------------------------------------"

for sys in "${SYSTEMATICS[@]}"; do
    OUT_DIR="${BASE_DIR}/${UL_ERA}/${VERSION}_${sys}/mc"

    if [[ -d "$OUT_DIR" ]]; then
        # Count output files
        NFILES=$(find "$OUT_DIR" -name "*.root" 2>/dev/null | wc -l)

        # Count error files with content
        NERRORS=0
        for errfile in $(find "$OUT_DIR" -name "*.err" 2>/dev/null); do
            if [[ -s "$errfile" ]]; then
                ((NERRORS++))
            fi
        done

        if [[ $NFILES -gt 0 && $NERRORS -eq 0 ]]; then
            STATUS="✓ OK"
        elif [[ $NFILES -gt 0 && $NERRORS -gt 0 ]]; then
            STATUS="⚠ Errors"
        else
            STATUS="○ Running"
        fi

        printf "%-20s %10d %10d %s\n" "$sys" "$NFILES" "$NERRORS" "$STATUS"
    else
        printf "%-20s %10s %10s %s\n" "$sys" "-" "-" "✗ Not found"
    fi
done

echo ""
echo "============================================"
echo "To check specific errors:"
echo "  find ${BASE_DIR}/${UL_ERA}/${VERSION}_*/mc -name '*.err' -size +0 | head -5 | xargs tail"
echo "============================================"
