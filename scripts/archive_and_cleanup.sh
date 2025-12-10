#!/bin/bash
# =============================================================================
# archive_and_cleanup.sh
# Safely zip and delete Stage 1 (OS) systematic directories
#
# Usage:
#   ./archive_and_cleanup.sh [--dry-run] [--era ERA] [--pattern PATTERN]
#
# Example:
#   ./archive_and_cleanup.sh --dry-run --era UL2018 --pattern "v94HadroPreJetVetoHemOnly_TTBBtest"
#   nohup ./archive_and_cleanup.sh --era UL2018 --pattern "v94HadroPreJetVetoHemOnly_TTBBtest" > archive.log 2>&1 &
#
# Safety features:
#   - Dry-run mode by default (must remove --dry-run to actually delete)
#   - Verifies zip integrity before deleting
#   - Creates detailed log file
#   - Skips nominal directory (no suffix)
#   - Saves file list before deletion for recovery
#   - Archives stored in same directory as source (e.g., UL2018/)
# =============================================================================

set -e  # Exit on error

# Default values
DRY_RUN=false
ERA="UL2018"
PATTERN="v94HadroPreJetVetoHemOnly_TTBBtest"
BASE_DIR="/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD"

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --dry-run)
            DRY_RUN=true
            shift
            ;;
        --era)
            ERA="$2"
            shift 2
            ;;
        --pattern)
            PATTERN="$2"
            shift 2
            ;;
        --help|-h)
            echo "Usage: $0 [--dry-run] [--era ERA] [--pattern PATTERN]"
            echo ""
            echo "Options:"
            echo "  --dry-run       Show what would be done without actually doing it"
            echo "  --era           Era directory (default: UL2018)"
            echo "  --pattern       Directory name pattern to match (default: v94HadroPreJetVetoHemOnly_TTBBtest)"
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

# Setup - archive files go in the same directory as source
SOURCE_DIR="${BASE_DIR}/${ERA}"
ARCHIVE_DIR="${SOURCE_DIR}"  # Same as source directory
TIMESTAMP=$(date +%Y%m%d_%H%M%S)
LOG_FILE="${ARCHIVE_DIR}/archive_${PATTERN}_${TIMESTAMP}.log"

# Logging function
log() {
    local msg="[$(date '+%Y-%m-%d %H:%M:%S')] $1"
    echo "$msg"
    echo "$msg" >> "$LOG_FILE"
}

log "=============================================="
log "Archive and Cleanup Script"
log "=============================================="
log "ERA: ${ERA}"
log "PATTERN: ${PATTERN}"
log "SOURCE_DIR: ${SOURCE_DIR}"
log "ARCHIVE_DIR: ${ARCHIVE_DIR}"
log "DRY_RUN: ${DRY_RUN}"
log "=============================================="

# Find directories matching pattern (systematic variations only, not nominal)
# Nominal has no suffix after the pattern, systematics have _SYS suffix
DIRS=$(ls -d ${SOURCE_DIR}/${PATTERN}_* 2>/dev/null || true)

if [ -z "$DIRS" ]; then
    log "ERROR: No directories found matching pattern: ${SOURCE_DIR}/${PATTERN}_*"
    exit 1
fi

# Count directories
DIR_COUNT=$(echo "$DIRS" | wc -l)
log "Found ${DIR_COUNT} directories to archive"

# Process each directory
PROCESSED=0
FAILED=0
SKIPPED=0

for DIR in $DIRS; do
    DIR_NAME=$(basename "$DIR")
    ZIP_NAME="${DIR_NAME}.tar.gz"
    ZIP_PATH="${ARCHIVE_DIR}/${ZIP_NAME}"
    FILE_LIST="${ARCHIVE_DIR}/${DIR_NAME}_filelist.txt"

    PROCESSED=$((PROCESSED + 1))
    log ""
    log "[${PROCESSED}/${DIR_COUNT}] Processing: ${DIR_NAME}"

    # Check if already archived
    if [ -f "$ZIP_PATH" ]; then
        log "  SKIP: Archive already exists: ${ZIP_PATH}"
        SKIPPED=$((SKIPPED + 1))
        continue
    fi

    if [ "$DRY_RUN" = true ]; then
        log "  DRY-RUN: Would create ${ZIP_PATH}"
        log "  DRY-RUN: Would delete ${DIR}"
        continue
    fi

    # Get directory stats (only when actually processing)
    FILE_COUNT=$(find "$DIR" -type f 2>/dev/null | wc -l)
    DIR_SIZE=$(du -sh "$DIR" 2>/dev/null | cut -f1)
    log "  Files: ${FILE_COUNT}, Size: ${DIR_SIZE}"

    # Save file list for recovery
    log "  Saving file list to: ${FILE_LIST}"
    find "$DIR" -type f > "$FILE_LIST"

    # Create tar.gz archive (faster than zip for large directories)
    log "  Creating archive: ${ZIP_PATH}"
    START_TIME=$(date +%s)

    if tar -czf "$ZIP_PATH" -C "${SOURCE_DIR}" "$DIR_NAME" 2>> "$LOG_FILE"; then
        END_TIME=$(date +%s)
        DURATION=$((END_TIME - START_TIME))
        ZIP_SIZE=$(du -sh "$ZIP_PATH" 2>/dev/null | cut -f1)
        log "  Archive created in ${DURATION}s, size: ${ZIP_SIZE}"

        # Verify archive integrity
        log "  Verifying archive integrity..."
        if tar -tzf "$ZIP_PATH" > /dev/null 2>&1; then
            log "  Archive verified successfully"

            # Delete original directory
            log "  Deleting original directory..."
            if rm -rf "$DIR"; then
                log "  SUCCESS: Deleted ${DIR}"
            else
                log "  ERROR: Failed to delete ${DIR}"
                FAILED=$((FAILED + 1))
            fi
        else
            log "  ERROR: Archive verification failed, keeping original directory"
            rm -f "$ZIP_PATH"
            FAILED=$((FAILED + 1))
        fi
    else
        log "  ERROR: Failed to create archive"
        rm -f "$ZIP_PATH"
        FAILED=$((FAILED + 1))
    fi
done

log ""
log "=============================================="
log "Summary"
log "=============================================="
log "Total directories: ${DIR_COUNT}"
log "Processed: ${PROCESSED}"
log "Skipped (already archived): ${SKIPPED}"
log "Failed: ${FAILED}"
log "Log file: ${LOG_FILE}"
log "=============================================="

if [ "$DRY_RUN" = true ]; then
    log ""
    log "This was a DRY RUN. No changes were made."
    log "To actually archive and delete, run without --dry-run flag."
fi

exit 0
