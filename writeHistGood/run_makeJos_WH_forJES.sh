#!/bin/bash

# Submit systematic variation (WH) jobs for specified channel for all years
# This script can reuse parameters from nominal job submission
#
# Usage:
#   bash run_makeJos_WH_forJES.sh [<channel> <version> <in_version>]
#
# Examples:
#   # Use parameters from nominal job submission
#   bash run_makeJos_WH_forJES.sh
#
#   # Or provide parameters explicitly
#   bash run_makeJos_WH_forJES.sh 1tau0l v8BDT1tau0l_refactorAndBtagNameFix v94HadroPreJetVetoHemOnly

CONFIG_FILE=".nominal_jobs_config"

# Function to load parameters from config
load_config() {
    if [ -f "${CONFIG_FILE}" ]; then
        source "${CONFIG_FILE}"
        echo "Loaded parameters from ${CONFIG_FILE}:"
        echo "  CHANNEL=${CHANNEL}"
        echo "  VERSION=${VERSION}"
        echo "  IN_VERSION=${IN_VERSION}"
        echo "  OUT_VERSION=${OUT_VERSION}"
        return 0
    else
        return 1
    fi
}

# Function to show usage
show_usage() {
    echo "Usage: bash run_makeJos_WH_forJES.sh [<channel> <version> <in_version>]"
    echo ""
    echo "Examples:"
    echo "  # Use saved parameters from nominal jobs"
    echo "  bash run_makeJos_WH_forJES.sh"
    echo ""
    echo "  # Or provide parameters explicitly"
    echo "  bash run_makeJos_WH_forJES.sh 1tau0l v8BDT1tau0l_refactorAndBtagNameFix v94HadroPreJetVetoHemOnly"
}

# Parse command-line arguments or load from config
if [ $# -eq 0 ]; then
    # No arguments - try to load from config
    if ! load_config; then
        echo "Error: No parameters provided and no config file found."
        echo "Run nominal jobs first with run_nominal_jobs.sh to save parameters."
        echo ""
        show_usage
        exit 1
    fi
elif [ $# -eq 3 ]; then
    # All arguments provided
    CHANNEL="$1"
    VERSION="$2"
    IN_VERSION="$3"
    OUT_VERSION="v1baselineHadroBtagWeightAdded"
elif [ $# -eq 1 ] && [ "$1" == "-h" ] || [ "$1" == "--help" ]; then
    show_usage
    exit 0
else
    echo "Error: Invalid number of arguments."
    echo ""
    show_usage
    exit 1
fi

# Validate channel
if [[ ! "${CHANNEL}" =~ ^1tau[012]l$ ]]; then
    echo "Error: Invalid channel '${CHANNEL}'. Must be 1tau0l, 1tau1l, or 1tau2l"
    exit 1
fi

echo ""
echo "========================================="
echo "Submitting systematic variation (WH) jobs"
echo "========================================="
echo "Channel: ${CHANNEL}"
echo "Version: ${VERSION}"
echo "In Version: ${IN_VERSION}"
echo "Out Version: ${OUT_VERSION}"
echo ""
echo "Jobs will submit:"
echo "  - JES variations: 27 sources × 2 = 54 jobs"
echo "  - JER variations: 2 jobs"
echo "  - TES variations: 4 decay modes × 2 = 8 jobs"
echo "  - MET variations: 2 jobs"
echo "  - EES variations: 2 jobs"
echo "  Total: ~68 systematic jobs per year"
echo "========================================="
echo ""

# 2018 (skip if already submitted)
# echo "Submitting 2018 ${CHANNEL} jobs..."
# nohup python3 jobs/makeJob_WH_forJES.py \
#     --inputDirBase "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/" \
#     --inVersion "${IN_VERSION}" \
#     --outVersion "${OUT_VERSION}" \
#     --channel "${CHANNEL}" \
#     --version "${VERSION}" \
#     > log_2018_${CHANNEL}.log 2>&1 &
# echo "  → log_2018_${CHANNEL}.log"
echo "Skipping 2018 (already submitted)"

# 2017
echo "Submitting 2017 ${CHANNEL} jobs..."
nohup bash -c "source ../setEnv_newNew.sh && python3 jobs/makeJob_WH_forJES.py \
    --inputDirBase '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/' \
    --inVersion '${IN_VERSION}' \
    --outVersion '${OUT_VERSION}' \
    --channel '${CHANNEL}' \
    --version '${VERSION}'" \
    > log_2017_${CHANNEL}.log 2>&1 &
echo "  → log_2017_${CHANNEL}.log"

# 2016preVFP
echo "Submitting 2016preVFP ${CHANNEL} jobs..."
nohup bash -c "source ../setEnv_newNew.sh && python3 jobs/makeJob_WH_forJES.py \
    --inputDirBase '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/' \
    --inVersion '${IN_VERSION}' \
    --outVersion '${OUT_VERSION}' \
    --channel '${CHANNEL}' \
    --version '${VERSION}'" \
    > log_2016preVFP_${CHANNEL}.log 2>&1 &
echo "  → log_2016preVFP_${CHANNEL}.log"

# 2016postVFP
echo "Submitting 2016postVFP ${CHANNEL} jobs..."
nohup bash -c "source ../setEnv_newNew.sh && python3 jobs/makeJob_WH_forJES.py \
    --inputDirBase '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/' \
    --inVersion '${IN_VERSION}' \
    --outVersion '${OUT_VERSION}' \
    --channel '${CHANNEL}' \
    --version '${VERSION}'" \
    > log_2016postVFP_${CHANNEL}.log 2>&1 &
echo "  → log_2016postVFP_${CHANNEL}.log"

echo ""
echo "========================================="
echo "✓ All WH jobs submitted in background"
echo "========================================="
echo ""
echo "Monitor progress with:"
echo "  tail -f log_2018_${CHANNEL}.log"
echo "  tail -f log_2017_${CHANNEL}.log"
echo "  tail -f log_2016preVFP_${CHANNEL}.log"
echo "  tail -f log_2016postVFP_${CHANNEL}.log"
echo ""