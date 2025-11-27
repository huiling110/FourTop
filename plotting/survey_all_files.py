#!/usr/bin/env python3
"""
Survey ALL files in the forMVA directory structure to identify main file quota consumers.

This script counts files at different directory levels:
1. By baseline version (e.g., v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly)
2. By histogram version (e.g., variableHists_v8BDT1tau0l_refactorAndBtagNameFix)
3. By subdirectory type (ROOT files, jobSH/, log/, etc.)

Usage:
    python3 survey_all_files.py --output file_survey.csv
"""

import os
import sys
import csv
import argparse
from pathlib import Path
from datetime import datetime
from collections import defaultdict

BASE_DIR = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA"

def count_files_recursive(dir_path):
    """
    Count all files recursively in a directory.

    Args:
        dir_path: Path to directory

    Returns:
        int: Total file count
    """
    file_count = 0
    try:
        for root, dirs, files in os.walk(dir_path):
            file_count += len(files)
    except (OSError, PermissionError):
        pass
    return file_count


def count_files_by_type(dir_path):
    """
    Count files by subdirectory type (ROOT files, jobSH/, log/, etc.).

    Args:
        dir_path: Path to directory

    Returns:
        dict: File counts by type
    """
    counts = {
        'root_files': 0,      # .root files in main directory
        'jobSH_files': 0,     # Files in jobSH/ subdirectory
        'log_files': 0,       # Files in log/ subdirectory
        'other_files': 0,     # Other files
        'total_files': 0
    }

    try:
        if not os.path.exists(dir_path):
            return counts

        # Count ROOT files in main directory
        for item in os.listdir(dir_path):
            item_path = os.path.join(dir_path, item)
            if os.path.isfile(item_path):
                if item.endswith('.root'):
                    counts['root_files'] += 1
                else:
                    counts['other_files'] += 1

        # Count files in jobSH/ subdirectory
        jobsh_path = os.path.join(dir_path, 'jobSH')
        if os.path.exists(jobsh_path):
            counts['jobSH_files'] = count_files_recursive(jobsh_path)

        # Count files in log/ subdirectory
        log_path = os.path.join(dir_path, 'log')
        if os.path.exists(log_path):
            counts['log_files'] = count_files_recursive(log_path)

        # Count other subdirectories recursively
        for item in os.listdir(dir_path):
            item_path = os.path.join(dir_path, item)
            if os.path.isdir(item_path) and item not in ['jobSH', 'log']:
                counts['other_files'] += count_files_recursive(item_path)

        counts['total_files'] = sum([
            counts['root_files'],
            counts['jobSH_files'],
            counts['log_files'],
            counts['other_files']
        ])

    except (OSError, PermissionError):
        pass

    return counts


def survey_histogram_directories(base_dir=BASE_DIR):
    """
    Survey all histogram directories and count files by type.

    Returns:
        list: List of dicts with survey results
    """
    print(f"Surveying {base_dir} for all histogram directories...")
    print("This will take 10-20 minutes to scan all files...")

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

                    # Infer channel from version name
                    if "1tau0l" in version:
                        channel = "1tau0l"
                    elif "1tau1l" in version:
                        channel = "1tau1l"
                    elif "1tau2l" in version:
                        channel = "1tau2l"
                    else:
                        channel = "unknown"

                    # Count files by type
                    file_counts = count_files_by_type(str(hist_dir))

                    result = {
                        'era': era,
                        'baseline_version': baseline_version,
                        'version': version,
                        'channel': channel,
                        'total_files': file_counts['total_files'],
                        'root_files': file_counts['root_files'],
                        'jobSH_files': file_counts['jobSH_files'],
                        'log_files': file_counts['log_files'],
                        'other_files': file_counts['other_files'],
                        'hist_dir': str(hist_dir)
                    }

                    results.append(result)

    print(f"Surveyed {len(results)} histogram directories")

    # Sort by total_files descending
    results.sort(key=lambda x: x['total_files'], reverse=True)

    return results


def write_survey_report(results, output_file):
    """
    Write survey results to CSV file.

    Args:
        results: List of survey result dicts
        output_file: Path to output CSV file
    """
    fieldnames = [
        'era', 'baseline_version', 'version', 'channel',
        'total_files', 'root_files', 'jobSH_files', 'log_files', 'other_files',
        'hist_dir'
    ]

    with open(output_file, 'w', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        for result in results:
            writer.writerow(result)

    print(f"\nSurvey report written to: {output_file}")
    print(f"Total histogram directories surveyed: {len(results)}")

    # Print summary statistics
    total_files = sum(r['total_files'] for r in results)
    total_root = sum(r['root_files'] for r in results)
    total_jobsh = sum(r['jobSH_files'] for r in results)
    total_log = sum(r['log_files'] for r in results)
    total_other = sum(r['other_files'] for r in results)

    print(f"\n{'='*80}")
    print("SUMMARY")
    print(f"{'='*80}")
    print(f"Total files in all histogram directories: {total_files:,}")
    print(f"  ROOT files:  {total_root:,} ({100*total_root/total_files:.1f}%)")
    print(f"  jobSH files: {total_jobsh:,} ({100*total_jobsh/total_files:.1f}%)")
    print(f"  log files:   {total_log:,} ({100*total_log/total_files:.1f}%)")
    print(f"  other files: {total_other:,} ({100*total_other/total_files:.1f}%)")

    # Print top 20 by total files
    print(f"\n{'='*80}")
    print("Top 20 histogram directories by file count:")
    print(f"{'='*80}")
    for i, r in enumerate(results[:20], 1):
        print(f"{i:2d}. {r['version']:50s} ({r['era']:12s}): {r['total_files']:6,} files")
        print(f"    ROOT: {r['root_files']:5,} | jobSH: {r['jobSH_files']:5,} | log: {r['log_files']:5,} | other: {r['other_files']:5,}")

    # Print aggregated stats by baseline version
    print(f"\n{'='*80}")
    print("File counts aggregated by baseline version:")
    print(f"{'='*80}")

    baseline_stats = defaultdict(lambda: {'total': 0, 'dirs': 0})
    for r in results:
        baseline_stats[r['baseline_version']]['total'] += r['total_files']
        baseline_stats[r['baseline_version']]['dirs'] += 1

    baseline_sorted = sorted(baseline_stats.items(), key=lambda x: x[1]['total'], reverse=True)
    for baseline, stats in baseline_sorted[:10]:
        print(f"{baseline:60s}: {stats['total']:7,} files in {stats['dirs']:3d} dirs")


def main():
    parser = argparse.ArgumentParser(
        description="Survey ALL files in forMVA directory structure",
        formatter_class=argparse.RawDescriptionHelpFormatter
    )

    parser.add_argument('--output', type=str, default='file_survey.csv',
                       help='Output CSV file (default: file_survey.csv)')

    args = parser.parse_args()

    print("Starting comprehensive file survey...")
    print("This will scan ALL files in the forMVA directory structure")
    print("Expected time: 10-20 minutes\n")

    results = survey_histogram_directories()

    if not results:
        print("No histogram directories found")
        return 0

    write_survey_report(results, args.output)

    return 0


if __name__ == '__main__':
    sys.exit(main())
