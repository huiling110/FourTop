#!/usr/bin/env python3
"""
Cleanup log/ and jobSH/ directories from histogram directories to free file quota.

These directories contain:
- log/: Job execution logs (can be compressed or deleted)
- jobSH/: Job submission scripts (can be regenerated, safe to delete)

Usage:
    # Survey mode (default, read-only)
    python3 cleanup_logs_jobsh.py --output cleanup_logs_report.csv

    # Cleanup mode (dry-run)
    python3 cleanup_logs_jobsh.py --cleanup --dry-run

    # Execute cleanup
    python3 cleanup_logs_jobsh.py --cleanup --execute
"""

import os
import sys
import csv
import shutil
import argparse
import subprocess
from pathlib import Path
from datetime import datetime

BASE_DIR = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA"

def count_files_in_directory(dir_path):
    """Count files recursively in a directory."""
    file_count = 0
    try:
        for root, dirs, files in os.walk(dir_path):
            file_count += len(files)
    except (OSError, PermissionError):
        pass
    return file_count


def get_directory_size_mb(dir_path):
    """Get directory size in MB."""
    total_size = 0
    try:
        for root, dirs, files in os.walk(dir_path):
            for file in files:
                try:
                    file_path = os.path.join(root, file)
                    total_size += os.path.getsize(file_path)
                except (OSError, FileNotFoundError):
                    pass
    except (OSError, PermissionError):
        pass
    return total_size / (1024 * 1024)


def survey_cleanup_targets(base_dir=BASE_DIR):
    """
    Survey all histogram directories for log/ and jobSH/ cleanup targets.

    Returns:
        list: List of dicts with survey results
    """
    print(f"Surveying {base_dir} for log/ and jobSH/ directories...")
    print("This may take 5-10 minutes...")

    results = []
    processed = 0

    # Pattern: [base_dir]/[era]/[baseline_version]/mc/variableHists_*/
    for era_dir in Path(base_dir).iterdir():
        if not era_dir.is_dir():
            continue
        era = era_dir.name
        if era not in ["2016preVFP", "2016postVFP", "2017", "2018"]:
            continue

        for baseline_dir in era_dir.iterdir():
            if not baseline_dir.is_dir():
                continue
            baseline_version = baseline_dir.name

            mc_dir = baseline_dir / "mc"
            if not mc_dir.exists():
                continue

            for hist_dir in mc_dir.iterdir():
                if hist_dir.is_dir() and hist_dir.name.startswith("variableHists_"):
                    processed += 1
                    if processed % 100 == 0:
                        print(f"  Processed {processed} directories...")

                    version = hist_dir.name.replace("variableHists_", "")

                    # Check for log/ and jobSH/ directories
                    log_dir = hist_dir / "log"
                    jobsh_dir = hist_dir / "jobSH"

                    log_files = count_files_in_directory(str(log_dir)) if log_dir.exists() else 0
                    log_size_mb = get_directory_size_mb(str(log_dir)) if log_dir.exists() else 0

                    jobsh_files = count_files_in_directory(str(jobsh_dir)) if jobsh_dir.exists() else 0
                    jobsh_size_mb = get_directory_size_mb(str(jobsh_dir)) if jobsh_dir.exists() else 0

                    total_files = log_files + jobsh_files
                    total_size_mb = log_size_mb + jobsh_size_mb

                    if total_files > 0:  # Only record if there are files to cleanup
                        result = {
                            'era': era,
                            'baseline_version': baseline_version,
                            'version': version,
                            'log_files': log_files,
                            'log_size_mb': log_size_mb,
                            'jobsh_files': jobsh_files,
                            'jobsh_size_mb': jobsh_size_mb,
                            'total_files': total_files,
                            'total_size_mb': total_size_mb,
                            'hist_dir': str(hist_dir)
                        }
                        results.append(result)

    print(f"Found {len(results)} histogram directories with log/jobSH files")

    # Sort by total_files descending
    results.sort(key=lambda x: x['total_files'], reverse=True)

    return results


def write_survey_report(results, output_file):
    """Write survey results to CSV file."""
    fieldnames = [
        'era', 'baseline_version', 'version',
        'log_files', 'log_size_mb', 'jobsh_files', 'jobsh_size_mb',
        'total_files', 'total_size_mb', 'hist_dir'
    ]

    with open(output_file, 'w', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        for result in results:
            writer.writerow(result)

    print(f"\nSurvey report written to: {output_file}")
    print(f"Total histogram directories with log/jobSH: {len(results)}")

    # Summary
    total_files = sum(r['total_files'] for r in results)
    total_log_files = sum(r['log_files'] for r in results)
    total_jobsh_files = sum(r['jobsh_files'] for r in results)
    total_size_gb = sum(r['total_size_mb'] for r in results) / 1024

    print(f"\n{'='*80}")
    print("SUMMARY")
    print(f"{'='*80}")
    print(f"Total files in log/ and jobSH/: {total_files:,}")
    print(f"  log/ files:   {total_log_files:,} ({100*total_log_files/total_files:.1f}%)")
    print(f"  jobSH/ files: {total_jobsh_files:,} ({100*total_jobsh_files/total_files:.1f}%)")
    print(f"Total size: {total_size_gb:.2f} GB")

    print(f"\nTop 10 by file count:")
    for i, r in enumerate(results[:10], 1):
        print(f"{i:2d}. {r['version']:50s} ({r['era']:12s}): {r['total_files']:5,} files")
        print(f"    log: {r['log_files']:4,} | jobSH: {r['jobsh_files']:4,}")


def get_quota_info():
    """Get current file quota information."""
    try:
        result = subprocess.run(
            ['lfs', 'quota', '-u', os.environ.get('USER', 'huahuil'), '/publicfs'],
            capture_output=True,
            text=True,
            timeout=30
        )

        if result.returncode == 0:
            lines = result.stdout.strip().split('\n')
            if len(lines) >= 2:
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


def cleanup_directory(dir_path, dry_run=True):
    """
    Delete a directory and return files deleted.

    Args:
        dir_path: Path to directory to delete
        dry_run: If True, only simulate deletion

    Returns:
        int: Number of files that would be/were deleted
    """
    if not os.path.exists(dir_path):
        return 0

    file_count = count_files_in_directory(dir_path)

    if not dry_run:
        try:
            shutil.rmtree(dir_path)
        except Exception as e:
            print(f"    Error deleting {dir_path}: {e}")
            return 0

    return file_count


def zip_log_directory(log_dir, dry_run=True):
    """
    Zip a log/ directory to save space while preserving logs.

    Args:
        log_dir: Path to log/ directory
        dry_run: If True, only simulate zipping

    Returns:
        tuple: (files_in_dir, files_freed) - files_freed accounts for zip file created
    """
    if not os.path.exists(log_dir):
        return 0, 0

    file_count = count_files_in_directory(log_dir)

    if file_count == 0:
        return 0, 0

    # Check if already zipped
    parent_dir = os.path.dirname(log_dir)
    zip_path = os.path.join(parent_dir, "log.zip")

    if os.path.exists(zip_path):
        # Already zipped, just delete the log/ directory
        if not dry_run:
            try:
                shutil.rmtree(log_dir)
            except Exception as e:
                print(f"    Error deleting {log_dir}: {e}")
                return file_count, 0
        return file_count, file_count

    # Zip the directory
    if not dry_run:
        try:
            # Create zip file
            shutil.make_archive(
                base_name=os.path.join(parent_dir, "log"),
                format='zip',
                root_dir=parent_dir,
                base_dir='log'
            )

            # Delete the original directory
            shutil.rmtree(log_dir)

        except Exception as e:
            print(f"    Error zipping {log_dir}: {e}")
            return file_count, 0

    # Files freed = file_count - 1 (for the zip file created)
    files_freed = file_count - 1 if file_count > 1 else 0

    return file_count, files_freed


def cleanup_logs_and_jobsh(survey_results, dry_run=True, log_file=None):
    """
    Cleanup log/ and jobSH/ directories.

    Args:
        survey_results: List of survey result dicts
        dry_run: If True, only show what would be deleted
        log_file: Path to log file (None = auto-generate)

    Returns:
        dict: Summary statistics
    """
    if not survey_results:
        print("No directories to cleanup")
        return {}

    # Generate log file name if not provided
    if log_file is None:
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        log_file = f"cleanup_logs_jobsh_{timestamp}.txt"

    # Get initial quota
    quota_before = get_quota_info()

    print("="*80)
    print(f"Cleanup Mode: {'DRY-RUN (no deletions)' if dry_run else 'EXECUTE (will delete!)'}")
    print("="*80)
    print(f"Found {len(survey_results)} histogram directories with log/jobSH files")
    print(f"Log file: {log_file}")
    print("="*80)

    if quota_before:
        print(f"File quota BEFORE: {quota_before['files_used']:,} / {quota_before['files_limit']:,} "
              f"({quota_before['files_percent']:.1f}%)")
        print("="*80)

    total_files_deleted = 0
    total_log_files = 0
    total_jobsh_files = 0
    dirs_cleaned = 0

    with open(log_file, 'w') as log:
        log.write(f"Cleanup log - {datetime.now()}\n")
        log.write(f"Mode: {'DRY-RUN' if dry_run else 'EXECUTE'}\n")
        log.write("="*80 + "\n\n")

        for i, result in enumerate(survey_results, 1):
            if i % 100 == 0:
                print(f"  Processed {i}/{len(survey_results)} directories...")

            hist_dir = Path(result['hist_dir'])
            log_dir = hist_dir / "log"
            jobsh_dir = hist_dir / "jobSH"

            # Zip log/ directory (preserves logs while freeing space)
            log_files_count = 0
            log_files_freed = 0
            if log_dir.exists():
                log_files_count, log_files_freed = zip_log_directory(str(log_dir), dry_run)
                total_log_files += log_files_freed

            # Delete jobSH/ directory (can be regenerated)
            jobsh_files_deleted = 0
            if jobsh_dir.exists():
                jobsh_files_deleted = cleanup_directory(str(jobsh_dir), dry_run)
                total_jobsh_files += jobsh_files_deleted

            files_freed_this_dir = log_files_freed + jobsh_files_deleted
            if files_freed_this_dir > 0:
                total_files_deleted += files_freed_this_dir
                dirs_cleaned += 1
                log.write(f"{result['version']} ({result['era']}):\n")
                log.write(f"  log/: {log_files_count} files → zipped (freed {log_files_freed})\n")
                log.write(f"  jobSH/: {jobsh_files_deleted} files deleted\n")

    # Get final quota
    quota_after = get_quota_info()

    print("\n" + "="*80)
    print("Cleanup Summary")
    print("="*80)
    print(f"Directories cleaned: {dirs_cleaned}")
    print(f"Total files {'would be freed' if dry_run else 'freed'}: {total_files_deleted:,}")
    print(f"  log/ files:   {total_log_files:,} (zipped, not deleted)")
    print(f"  jobSH/ files: {total_jobsh_files:,} (deleted)")

    if quota_before and quota_after and not dry_run:
        files_freed = quota_before['files_used'] - quota_after['files_used']
        print(f"\nFile quota BEFORE: {quota_before['files_used']:,} ({quota_before['files_percent']:.1f}%)")
        print(f"File quota AFTER:  {quota_after['files_used']:,} ({quota_after['files_percent']:.1f}%)")
        print(f"Files freed: {files_freed:,}")

    print(f"\nLog written to: {log_file}")
    print("="*80)

    return {
        "dirs_cleaned": dirs_cleaned,
        "files_deleted": total_files_deleted,
        "log_files": total_log_files,
        "jobsh_files": total_jobsh_files,
        "quota_before": quota_before,
        "quota_after": quota_after
    }


def main():
    parser = argparse.ArgumentParser(
        description="Cleanup log/ and jobSH/ directories from histogram directories",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Survey (read-only)
  python3 cleanup_logs_jobsh.py --output cleanup_logs_report.csv

  # Cleanup (dry-run)
  python3 cleanup_logs_jobsh.py --cleanup --dry-run

  # Execute cleanup
  python3 cleanup_logs_jobsh.py --cleanup --execute
"""
    )

    # Mode selection
    parser.add_argument('--cleanup', action='store_true',
                       help='Cleanup mode (default: survey mode)')

    # Survey mode options
    parser.add_argument('--output', type=str, default='cleanup_logs_report.csv',
                       help='Output CSV file for survey mode')

    # Cleanup mode options
    parser.add_argument('--dry-run', action='store_true', default=False,
                       help='Dry-run mode (show what would be deleted)')
    parser.add_argument('--execute', action='store_true',
                       help='Actually execute cleanup (required for deletion)')
    parser.add_argument('--yes', action='store_true',
                       help='Skip confirmation prompt (auto-confirm)')

    # Logging
    parser.add_argument('--log-file', type=str,
                       help='Custom log file path')

    args = parser.parse_args()

    # Validation
    if args.cleanup:
        # Default to dry-run unless --execute is specified
        if not args.execute:
            args.dry_run = True

        if args.execute and args.dry_run:
            print("Error: Cannot specify both --execute and --dry-run")
            return 1

    # Run survey
    print("Starting survey of log/ and jobSH/ directories...")
    results = survey_cleanup_targets()

    if not results:
        print("No log/ or jobSH/ directories found")
        return 0

    # Survey mode: write report and exit
    if not args.cleanup:
        write_survey_report(results, args.output)
        return 0

    # Cleanup mode
    total_files = sum(r['total_files'] for r in results)

    print(f"\nTotal files to {'process' if args.dry_run else 'DELETE'}: {total_files:,}")

    if not args.dry_run and not args.yes:
        print("\n" + "!"*80)
        print("WARNING: You are about to cleanup log/ and jobSH/ directories!")
        print("!"*80)
        print("\nActions:")
        print("  - log/:   Will be ZIPPED (preserved for debugging, space freed)")
        print("  - jobSH/: Will be DELETED (can be regenerated)")
        print("\nThis action cannot be undone!")
        response = input("\nType 'yes' to confirm: ")
        if response.lower() != 'yes':
            print("Cleanup cancelled")
            return 0

    # Execute cleanup
    summary = cleanup_logs_and_jobsh(
        results,
        dry_run=args.dry_run,
        log_file=args.log_file
    )

    return 0


if __name__ == '__main__':
    sys.exit(main())
