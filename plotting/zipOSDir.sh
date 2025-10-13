#!/bin/bash

# --- User Settings ---
BASE_DIR="/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/"  # Edit this as needed

# List subdirectories to zip, separated by space
# SUBDIRS=("run1" "run2" "data_exp" "test123")
# SUBDIRS=("v94LepPreJetVetoHemOnlyV2_EleScaleDown" "v94LepPreJetVetoHemOnlyV2_EleScaleUp")
SUBDIRS=("v94LepPreJetVetoHemOnlyV2_TESdm1Up" "v94LepPreJetVetoHemOnlyV2_TESdm1Down" "v94LepPreJetVetoHemOnlyV2_TESp1Up" "v94LepPreJetVetoHemOnlyV2_TESp1Down")
# ---------------------

if [ ! -d "$BASE_DIR" ]; then
    echo "Base directory $BASE_DIR not found!"
    exit 1
fi

for SUBDIR in "${SUBDIRS[@]}"; do
    SUBDIR=$(echo "$SUBDIR" | xargs)  # Trim whitespace
    if [ -z "$SUBDIR" ]; then continue; fi

    FULL_PATH="$BASE_DIR/$SUBDIR"
    # if [ -d "$FULL_PATH" ]; then
    #     echo "Zipping $FULL_PATH -> $BASE_DIR/${SUBDIR}.zip"
    #     # (cd "$BASE_DIR" && zip -r "${SUBDIR}.zip" "$SUBDIR")
    #     nohup bash -c "(cd '$BASE_DIR' && zip -r '${SUBDIR}.zip' '$SUBDIR')" > "${BASE_DIR}/${SUBDIR}.log" 2>&1 &
    # else
    #     echo "Warning: $FULL_PATH not found, skipping."
    # fi

    if [ -d "$FULL_PATH" ]; then
        echo "Zipping $FULL_PATH -> $BASE_DIR/${SUBDIR}.zip"
        nohup bash -c "(cd '$BASE_DIR' && zip -r '${SUBDIR}.zip' '$SUBDIR' && rm -rf '$SUBDIR')" > "${BASE_DIR}/${SUBDIR}.log" 2>&1 &
        PID=$!
        
        # Wait for the background process to finish
        wait $PID
        
        # Check if the zip process was successful
        if [ $? -eq 0 ]; then
            echo "Successfully zipped and removed $FULL_PATH"
        else
            echo "Error zipping $FULL_PATH, not deleting $SUBDIR"
        fi
    else
        echo "Warning: $FULL_PATH not found, skipping."
    fi


done