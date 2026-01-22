#!/usr/bin/env python3
"""
Resubmit failed OS jobs using existing job scripts.

Uses the job scripts already created by makeJob_OS_fromRuobing2.py.
Maps missing/corrupted files to their job script index and resubmits.

Usage:
    python3 submit_os_resubmit.py --config CONFIG --era 2018 --systematic JESPt22 [--dry-run]
"""

import os
import argparse
import subprocess
import glob

from fourtop.workflow import load_config, build_stage1_output, build_stage1_input, ERA_TO_UL

# Import check script functions
from check_os_systematics import check_os_output


def find_job_script_index(jobs_dir: str, sample: str, filename: str, era_ul: str) -> int:
    """
    Find the job script index for a given file.

    The job scripts are indexed by the order files appear in glob.glob().
    We need to match the filename to find its index.
    """
    sample_job_dir = os.path.join(jobs_dir, era_ul, sample)
    if not os.path.exists(sample_job_dir):
        return -1

    # Read each job script to find the one with this filename
    for script in os.listdir(sample_job_dir):
        if not script.endswith('.sh'):
            continue
        script_path = os.path.join(sample_job_dir, script)
        with open(script_path) as f:
            content = f.read()
            if filename in content:
                # Extract index from script name: OS_UL2018tttt_0.sh -> 0
                idx = script.rsplit('_', 1)[1].replace('.sh', '')
                return int(idx)
    return -1


def resubmit_jobs(config: dict, era: str, systematic: str, dry_run: bool = False):
    """
    Resubmit failed OS jobs using existing job scripts.
    """
    era_ul = ERA_TO_UL.get(era, f'UL{era}')

    # Get output directory where job scripts are stored
    output_dir = build_stage1_output(config, era, systematic)
    jobs_dir = os.path.join(output_dir, 'jobs_eachYear')

    if not os.path.exists(jobs_dir):
        print(f"ERROR: Job scripts directory not found: {jobs_dir}")
        return

    # Check for missing/corrupted files
    print(f"Checking for missing/corrupted files...")
    results = check_os_output(config, era, systematic, verbose=False)

    missing = results['missing']
    corrupted = results['corrupted']

    if not missing and not corrupted:
        print("All files OK! Nothing to resubmit.")
        return

    print(f"Found {len(missing)} missing, {len(corrupted)} corrupted files")

    # Group by sample
    by_sample = {}
    for filepath, _ in missing:
        sample, filename = filepath.split('/', 1)
        if sample not in by_sample:
            by_sample[sample] = []
        by_sample[sample].append(filename)

    for item in corrupted:
        filepath = item[0]
        sample, filename = filepath.split('/', 1)
        if sample not in by_sample:
            by_sample[sample] = []
        by_sample[sample].append(filename)

    # Log directory for resubmitted jobs
    log_dir = os.path.join(output_dir, 'mc', 'resubmit_logs')
    os.makedirs(log_dir, exist_ok=True)

    total_submitted = 0

    for sample, files in sorted(by_sample.items()):
        sample_job_dir = os.path.join(jobs_dir, era_ul, sample)

        if not os.path.exists(sample_job_dir):
            print(f"  WARNING: Job scripts not found for {sample}")
            continue

        # Find indices for each file
        indices = []
        for filename in files:
            idx = find_job_script_index(jobs_dir, sample, filename, era_ul)
            if idx >= 0:
                indices.append(idx)
            else:
                print(f"  WARNING: Could not find job script for {sample}/{filename}")

        if not indices:
            continue

        print(f"  {sample}: {len(indices)} jobs to resubmit")

        # Resubmit each job individually
        sample_log_dir = os.path.join(log_dir, sample)
        os.makedirs(sample_log_dir, exist_ok=True)

        for idx in indices:
            script_name = f"OS_{era_ul}{sample}_{idx}.sh"
            script_path = os.path.join(sample_job_dir, script_name)

            if not os.path.exists(script_path):
                print(f"    WARNING: Script not found: {script_path}")
                continue

            log_file = os.path.join(sample_log_dir, f"_{idx}.log")
            err_file = os.path.join(sample_log_dir, f"_{idx}.err")

            cmd = [
                'hep_sub',
                '-os', 'CentOS7',
                script_path,
                '-o', log_file,
                '-e', err_file,
            ]

            if dry_run:
                if total_submitted < 5:
                    print(f"    Would submit: {script_name}")
            else:
                try:
                    subprocess.run(cmd, check=True, capture_output=True)
                    total_submitted += 1
                except subprocess.CalledProcessError as e:
                    print(f"    Failed to submit {script_name}: {e}")

        if not dry_run:
            total_submitted += len(indices)

    if dry_run:
        print(f"\nDry run complete. Would submit jobs for {len(by_sample)} samples.")
    else:
        print(f"\nSubmitted {total_submitted} jobs.")
        print(f"Logs in: {log_dir}")
        print(f"Monitor with: hep_q -u $USER | grep OS_{era_ul}")


def main():
    parser = argparse.ArgumentParser(description='Resubmit failed OS jobs')
    parser.add_argument('--config', '-c', required=True, help='Config file')
    parser.add_argument('--era', '-e', required=True, help='Era')
    parser.add_argument('--systematic', '-s', required=True, help='Systematic (e.g., JESPt22)')
    parser.add_argument('--dry-run', '-n', action='store_true', help='Dry run')
    args = parser.parse_args()

    config = load_config(args.config)
    resubmit_jobs(config, args.era, args.systematic, args.dry_run)


if __name__ == '__main__':
    main()
