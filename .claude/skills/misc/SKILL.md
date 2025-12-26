---
name: misc
description: Miscellaneous utilities - archiving, cleanup, disk management. Keywords: archive, zip, cleanup, disk, storage, tar.gz
---

# Miscellaneous Utilities

## Archive and Cleanup Script

Archives (tar.gz) and deletes Stage 1 OS systematic directories to save disk space.

**Location**: `scripts/archive_and_cleanup.sh`

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
