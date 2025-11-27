#!/usr/bin/env python3
"""
Unified tool to survey and cleanup systematic histogram directories.

This script provides two modes:
1. Survey mode (default): Scan for nominal histogram directories, identify
   associated systematic variations, count files, check consolidation status
2. Cleanup mode (--cleanup): Delete systematic variation files after consolidation

Usage:
    # Survey all versions
    python3 manage_systematic_histograms.py --output report.csv

    # Cleanup specific version (dry-run)
    python3 manage_systematic_histograms.py --cleanup --version v8BDT1tau0l_refactorAndBtagNameFix --dry-run

    # Execute cleanup
    python3 manage_systematic_histograms.py --cleanup --version v8BDT1tau0l_refactorAndBtagNameFix --execute
"""

import os
import sys
import csv
import argparse
from pathlib import Path
from datetime import datetime
import subprocess

# Import cleanup functions from existing script
from addJESTemplatesToHistFile import (
    find_systematic_directories,
    cleanup_systematic_histogram_directory
)

# ============================================================================
# Configuration
# ============================================================================

BASE_DIR = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA"

# ============================================================================
# Survey Functions
# ============================================================================

def find_all_nominal_directories(base_dir=BASE_DIR):
    """
    Find all nominal histogram directories.

    Returns:
        list: List of paths to nominal histogram directories
    """
    print(f"Scanning {base_dir} for nominal histogram directories...")
    print("This may take a few minutes...")

    nominal_dirs = []

    # Pattern: [base_dir]/[era]/[baseline_version]/mc/variableHists_v*/
    for era_dir in Path(base_dir).iterdir():
        if not era_dir.is_dir():
            continue
        era = era_dir.name
        if era not in ["2016preVFP", "2016postVFP", "2017", "2018"]:
            continue

        for baseline_dir in era_dir.iterdir():
            if not baseline_dir.is_dir():
                continue

            mc_dir = baseline_dir / "mc"
            if not mc_dir.exists():
                continue

            for hist_dir in mc_dir.iterdir():
                if hist_dir.is_dir() and hist_dir.name.startswith("variableHists_"):
                    nominal_dirs.append(str(hist_dir))

    print(f"Found {len(nominal_dirs)} nominal histogram directories")
    return nominal_dirs


def count_files_in_directory(dir_path):
    """
    Count total files and calculate total size in a directory.

    Args:
        dir_path: Path to directory

    Returns:
        tuple: (file_count, size_in_bytes)
    """
    file_count = 0
    total_size = 0

    try:
        for root, dirs, files in os.walk(dir_path):
            file_count += len(files)
            for file in files:
                try:
                    file_path = os.path.join(root, file)
                    total_size += os.path.getsize(file_path)
                except (OSError, FileNotFoundError):
                    # Skip files that can't be accessed
                    pass
    except (OSError, PermissionError):
        pass

    return file_count, total_size


def extract_info_from_nominal_dir(nominal_dir):
    """
    Extract era, version, channel from nominal directory path.

    Args:
        nominal_dir: Path to nominal directory

    Returns:
        dict: Dictionary with era, version, channel, baseline_version
    """
    # Path structure: .../forMVA/[era]/[baseline]/mc/variableHists_[version]/
    parts = Path(nominal_dir).parts

    # Find indices
    try:
        forMVA_idx = parts.index("forMVA")
        era = parts[forMVA_idx + 1]
        baseline_version = parts[forMVA_idx + 2]
        version = Path(nominal_dir).name.replace("variableHists_", "")

        # Infer channel from version name
        if "1tau0l" in version:
            channel = "1tau0l"
        elif "1tau1l" in version:
            channel = "1tau1l"
        elif "1tau2l" in version:
            channel = "1tau2l"
        else:
            channel = "unknown"

        return {
            "era": era,
            "version": version,
            "channel": channel,
            "baseline_version": baseline_version
        }
    except (ValueError, IndexError):
        return {
            "era": "unknown",
            "version": Path(nominal_dir).name.replace("variableHists_", ""),
            "channel": "unknown",
            "baseline_version": "unknown"
        }


def check_consolidation_status(nominal_dir):
    """
    Check if systematic histograms have been consolidated into nominal files.

    This is a heuristic check: if systematic variation directories exist but
    are empty or have very few files, consolidation likely happened.

    Args:
        nominal_dir: Path to nominal directory

    Returns:
        str: "yes", "no", or "unknown"
    """
    # For now, return "unknown" - full implementation would open ROOT files
    # and check for systematic histogram names
    # This can be enhanced later if needed
    return "unknown"


def survey_all_nominal_directories(base_dir=BASE_DIR):
    """
    Survey all nominal histogram directories and their systematic variations.

    Returns:
        list: List of dicts with survey results for each nominal directory
    """
    nominal_dirs = find_all_nominal_directories(base_dir)

    results = []

    for i, nominal_dir in enumerate(nominal_dirs, 1):
        if i % 100 == 0:
            print(f"  Processed {i}/{len(nominal_dirs)} directories...")

        info = extract_info_from_nominal_dir(nominal_dir)

        # Find systematic directories
        try:
            sys_dirs = find_systematic_directories(nominal_dir)
        except Exception as e:
            print(f"  Warning: Error finding systematic dirs for {nominal_dir}: {e}")
            sys_dirs = []

        # Count files in systematic directories
        total_sys_files = 0
        total_sys_size = 0

        for sys_dir in sys_dirs:
            if os.path.exists(sys_dir):
                file_count, size_bytes = count_files_in_directory(sys_dir)
                total_sys_files += file_count
                total_sys_size += size_bytes

        # Check consolidation status
        consolidated = check_consolidation_status(nominal_dir)

        result = {
            "version": info["version"],
            "era": info["era"],
            "channel": info["channel"],
            "baseline_version": info["baseline_version"],
            "nominal_dir": nominal_dir,
            "num_sys_dirs": len(sys_dirs),
            "total_sys_files": total_sys_files,
            "total_sys_size_MB": total_sys_size / (1024 * 1024),
            "consolidated": consolidated,
        }

        results.append(result)

    # Sort by total_sys_files descending
    results.sort(key=lambda x: x["total_sys_files"], reverse=True)

    return results


def write_survey_report(results, output_file):
    """
    Write survey results to CSV file.

    Args:
        results: List of survey result dicts
        output_file: Path to output CSV file
    """
    fieldnames = [
        "version", "era", "channel", "baseline_version",
        "num_sys_dirs", "total_sys_files", "total_sys_size_MB",
        "consolidated", "nominal_dir"
    ]

    with open(output_file, 'w', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        for result in results:
            writer.writerow(result)

    print(f"\nSurvey report written to: {output_file}")
    print(f"Total nominal directories surveyed: {len(results)}")

    # Print summary
    total_files = sum(r["total_sys_files"] for r in results)
    total_size_gb = sum(r["total_sys_size_MB"] for r in results) / 1024

    print(f"Total systematic files found: {total_files:,}")
    print(f"Total size: {total_size_gb:.2f} GB")

    if results:
        print(f"\nTop 10 versions by file count:")
        for i, r in enumerate(results[:10], 1):
            print(f"  {i}. {r['version']} ({r['era']}): {r['total_sys_files']:,} files, "
                  f"{r['total_sys_size_MB']:.1f} MB")


# ============================================================================
# Cleanup Functions
# ============================================================================

def filter_survey_results(results, version=None, era=None, consolidated_only=False, min_files=0):
    """
    Filter survey results based on criteria.

    Args:
        results: List of survey result dicts
        version: Filter by version name (None = all)
        era: Filter by era (None = all)
        consolidated_only: Only include consolidated versions
        min_files: Minimum number of files to include

    Returns:
        list: Filtered list of results
    """
    filtered = results

    if version:
        filtered = [r for r in filtered if r["version"] == version]

    if era:
        filtered = [r for r in filtered if r["era"] == era]

    if consolidated_only:
        filtered = [r for r in filtered if r["consolidated"] == "yes"]

    if min_files > 0:
        filtered = [r for r in filtered if r["total_sys_files"] >= min_files]

    return filtered


def get_quota_info():
    """
    Get current file quota information.

    Returns:
        dict: Quota information or None if command fails
    """
    try:
        result = subprocess.run(
            ['lfs', 'quota', '-u', os.environ.get('USER', 'huahuil'), '/publicfs'],
            capture_output=True,
            text=True,
            timeout=30
        )

        if result.returncode == 0:
            # Parse output
            lines = result.stdout.strip().split('\n')
            if len(lines) >= 2:
                # Second line has the data
                parts = lines[1].split()
                if len(parts) >= 7:
                    return {
                        "files_used": int(parts[4]),
                        "files_limit": int(parts[6]),
                        "files_percent": (int(parts[4]) / int(parts[6])) * 100
                    }
    except Exception as e:
        print(f"Warning: Could not get quota info: {e}")

    return None


def cleanup_filtered_directories(filtered_results, dry_run=True, log_file=None):
    """
    Cleanup systematic directories for filtered nominal directories.

    Args:
        filtered_results: Filtered list of survey results
        dry_run: If True, only show what would be deleted
        log_file: Path to log file (None = auto-generate)

    Returns:
        dict: Summary statistics
    """
    if not filtered_results:
        print("No directories match the filter criteria")
        return {}

    # Generate log file name if not provided
    if log_file is None:
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        log_file = f"cleanup_log_{timestamp}.txt"

    # Get initial quota
    quota_before = get_quota_info()

    print("="*80)
    print(f"Cleanup Mode: {'DRY-RUN (no deletions)' if dry_run else 'EXECUTE (will delete!)'}")
    print("="*80)
    print(f"Found {len(filtered_results)} nominal directories matching filters")
    print(f"Log file: {log_file}")
    print("="*80)

    if quota_before:
        print(f"File quota BEFORE: {quota_before['files_used']:,} / {quota_before['files_limit']:,} "
              f"({quota_before['files_percent']:.1f}%)")
        print("="*80)

    total_files_deleted = 0
    total_size_freed_mb = 0
    total_sys_dirs_cleaned = 0

    with open(log_file, 'w') as log:
        log.write(f"Cleanup log - {datetime.now()}\n")
        log.write(f"Mode: {'DRY-RUN' if dry_run else 'EXECUTE'}\n")
        log.write("="*80 + "\n\n")

        for i, result in enumerate(filtered_results, 1):
            print(f"\n[{i}/{len(filtered_results)}] Processing: {result['version']} ({result['era']})")
            log.write(f"\n[{i}/{len(filtered_results)}] {result['version']} ({result['era']})\n")
            log.write(f"Nominal dir: {result['nominal_dir']}\n")

            # Find systematic directories
            try:
                sys_dirs = find_systematic_directories(result['nominal_dir'])
            except Exception as e:
                error_msg = f"Error finding systematic dirs: {e}"
                print(f"  {error_msg}")
                log.write(f"  {error_msg}\n")
                continue

            if not sys_dirs:
                msg = "  No systematic directories found"
                print(msg)
                log.write(msg + "\n")
                continue

            print(f"  Found {len(sys_dirs)} systematic directories")
            log.write(f"  Found {len(sys_dirs)} systematic directories\n")

            # Cleanup each systematic directory
            for sys_dir in sys_dirs:
                if not os.path.exists(sys_dir):
                    continue

                try:
                    files_deleted, size_freed_mb = cleanup_systematic_histogram_directory(
                        sys_dir, dry_run=dry_run
                    )

                    total_files_deleted += files_deleted
                    total_size_freed_mb += size_freed_mb
                    total_sys_dirs_cleaned += 1

                    log.write(f"    {os.path.basename(sys_dir)}: {files_deleted} files, "
                             f"{size_freed_mb:.1f} MB\n")

                except Exception as e:
                    error_msg = f"    Error cleaning {sys_dir}: {e}"
                    print(error_msg)
                    log.write(error_msg + "\n")

    # Get final quota
    quota_after = get_quota_info()

    print("\n" + "="*80)
    print("Cleanup Summary")
    print("="*80)
    print(f"Nominal directories processed: {len(filtered_results)}")
    print(f"Systematic directories cleaned: {total_sys_dirs_cleaned}")
    print(f"Total files {'would be deleted' if dry_run else 'deleted'}: {total_files_deleted:,}")
    print(f"Total space {'would be freed' if dry_run else 'freed'}: {total_size_freed_mb:.1f} MB "
          f"({total_size_freed_mb/1024:.2f} GB)")

    if quota_before and quota_after and not dry_run:
        files_freed = quota_before['files_used'] - quota_after['files_used']
        print(f"\nFile quota BEFORE: {quota_before['files_used']:,} ({quota_before['files_percent']:.1f}%)")
        print(f"File quota AFTER:  {quota_after['files_used']:,} ({quota_after['files_percent']:.1f}%)")
        print(f"Files freed: {files_freed:,}")

    print(f"\nLog written to: {log_file}")
    print("="*80)

    return {
        "nominal_dirs_processed": len(filtered_results),
        "sys_dirs_cleaned": total_sys_dirs_cleaned,
        "files_deleted": total_files_deleted,
        "size_freed_mb": total_size_freed_mb,
        "quota_before": quota_before,
        "quota_after": quota_after
    }


# ============================================================================
# Main
# ============================================================================

def main():
    parser = argparse.ArgumentParser(
        description="Survey and cleanup systematic histogram directories",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Survey all versions (read-only)
  python3 manage_systematic_histograms.py --output report.csv

  # Cleanup specific version (dry-run)
  python3 manage_systematic_histograms.py --cleanup --version v8BDT1tau0l_refactorAndBtagNameFix --dry-run

  # Execute cleanup
  python3 manage_systematic_histograms.py --cleanup --version v8BDT1tau0l_refactorAndBtagNameFix --execute

  # Cleanup all consolidated versions (dry-run)
  python3 manage_systematic_histograms.py --cleanup --consolidated-only --dry-run
"""
    )

    # Mode selection
    parser.add_argument('--cleanup', action='store_true',
                       help='Cleanup mode (default: survey mode)')

    # Survey mode options
    parser.add_argument('--output', type=str, default='cleanup_report.csv',
                       help='Output CSV file for survey mode (default: cleanup_report.csv)')

    # Filters (for cleanup mode)
    parser.add_argument('--version', type=str,
                       help='Filter by version name')
    parser.add_argument('--era', type=str, choices=['2016preVFP', '2016postVFP', '2017', '2018'],
                       help='Filter by era')
    parser.add_argument('--consolidated-only', action='store_true',
                       help='Only process consolidated versions')
    parser.add_argument('--min-files', type=int, default=0,
                       help='Minimum number of files to process')

    # Cleanup mode options
    parser.add_argument('--dry-run', action='store_true', default=False,
                       help='Dry-run mode (default for cleanup)')
    parser.add_argument('--execute', action='store_true',
                       help='Actually execute cleanup (required for deletion)')

    # Logging
    parser.add_argument('--log-file', type=str,
                       help='Custom log file path')

    args = parser.parse_args()

    # Validation
    if args.cleanup:
        if not any([args.version, args.era, args.consolidated_only, args.min_files > 0]):
            print("Error: In cleanup mode, you must specify at least one filter:")
            print("  --version, --era, --consolidated-only, or --min-files")
            return 1

        # Default to dry-run unless --execute is specified
        if not args.execute:
            args.dry_run = True

        if args.execute and args.dry_run:
            print("Error: Cannot specify both --execute and --dry-run")
            return 1

    # Run survey
    print("Starting survey...")
    results = survey_all_nominal_directories()

    if not results:
        print("No nominal histogram directories found")
        return 0

    # Survey mode: write report and exit
    if not args.cleanup:
        write_survey_report(results, args.output)
        return 0

    # Cleanup mode: filter and cleanup
    print("\nFiltering results...")
    filtered = filter_survey_results(
        results,
        version=args.version,
        era=args.era,
        consolidated_only=args.consolidated_only,
        min_files=args.min_files
    )

    if not filtered:
        print("No directories match the filter criteria")
        return 0

    print(f"Found {len(filtered)} directories matching filters")
    print(f"\nFilters applied:")
    if args.version:
        print(f"  Version: {args.version}")
    if args.era:
        print(f"  Era: {args.era}")
    if args.consolidated_only:
        print(f"  Consolidated only: yes")
    if args.min_files > 0:
        print(f"  Minimum files: {args.min_files}")

    # Calculate totals
    total_files = sum(r['total_sys_files'] for r in filtered)
    total_size_gb = sum(r['total_sys_size_MB'] for r in filtered) / 1024

    print(f"\nTotal systematic files to {'process' if args.dry_run else 'DELETE'}: {total_files:,}")
    print(f"Total size: {total_size_gb:.2f} GB")

    if not args.dry_run:
        print("\n" + "!"*80)
        print("WARNING: You are about to DELETE files!")
        print("!"*80)
        response = input("\nType 'yes' to confirm deletion: ")
        if response.lower() != 'yes':
            print("Cleanup cancelled")
            return 0

    # Execute cleanup
    summary = cleanup_filtered_directories(
        filtered,
        dry_run=args.dry_run,
        log_file=args.log_file
    )

    return 0


if __name__ == '__main__':
    sys.exit(main())
