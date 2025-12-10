#!/usr/bin/env python3
"""
Stage 2 (MV - Make Variables) job submission script.

Submits jobs to compute BDT input variables from Stage 1 (OS) output.

Usage:
    # Nominal (all eras from config)
    python3 makeJob_makeVaribles_forBDT.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml

    # Specific era
    python3 makeJob_makeVaribles_forBDT.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018

    # With systematic variation
    python3 makeJob_makeVaribles_forBDT.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --sys JERUp

    # Dry run (show commands without submitting)
    python3 makeJob_makeVaribles_forBDT.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --dry-run
"""
import argparse
import os
import subprocess
import sys

# Add plotting directory for workflow_utils
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', 'plotting'))
from workflow_utils import (
    load_config, get_eras, get_channel, get_channel_if1tau2l,
    build_stage1_output, build_stage2_output, ERA_TO_UL
)

import usefulFunc as uf


def create_parser():
    """Create argument parser."""
    parser = argparse.ArgumentParser(
        description='Submit Stage 2 (MV) jobs for FourTop analysis',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )
    parser.add_argument(
        '--config', '-c', required=True,
        help='Path to YAML config file (required)'
    )
    parser.add_argument(
        '--era', '-e',
        help='Era to process (default: all from config). For 2016, processes both pre/postVFP.'
    )
    parser.add_argument(
        '--sys', '-s',
        help='Input systematic variation suffix (e.g., JERUp, TESdm0Down, JESPt22)'
    )
    parser.add_argument(
        '--output-sys',
        help='Output systematic variation suffix (for JES: JESup_SOURCE or JESDown_SOURCE). If not set, uses --sys'
    )
    parser.add_argument(
        '--jes-variation', type=int, default=0,
        help='JES variation index for JESPt22 input (0=none, use with --sys JESPt22)'
    )
    parser.add_argument(
        '--jes-type', type=int, default=0, choices=[0, 1, 2],
        help='JES variation type: 0=none, 1=up, 2=down (use with --jes-variation)'
    )
    parser.add_argument(
        '--mc-only', action='store_true',
        help='Process only MC samples (skip data)'
    )
    parser.add_argument(
        '--dry-run', '-n', action='store_true',
        help='Show commands without submitting jobs'
    )
    parser.add_argument(
        '--quiet', '-q', action='store_true',
        help='Reduce output verbosity'
    )
    return parser


def get_eras_to_process(config, era_arg):
    """Get list of eras to process based on config and CLI argument."""
    if era_arg:
        # Handle '2016' -> both 2016preVFP and 2016postVFP
        if era_arg == '2016':
            return ['2016preVFP', '2016postVFP']
        return [era_arg]
    return get_eras(config)


def get_input_output_dirs(config, era, input_systematic=None, output_systematic=None, mc_only=False):
    """
    Build input/output directory mapping for an era.

    Args:
        config: Configuration dictionary.
        era: Era string.
        input_systematic: Systematic suffix for input (Stage 1) path.
        output_systematic: Systematic suffix for output (Stage 2) path. If None, uses input_systematic.
        mc_only: If True, only return MC directories.

    Returns dict: {data_type: [input_dir, output_dir]}

    Note:
        JES variations have special path format: {stage2}_JES{up/Down}_{source}_{stage1}_JESPt22
        Other systematics use: {stage2}_{stage1}_{systematic}
    """
    # If output_systematic not specified, use input_systematic
    if output_systematic is None:
        output_systematic = input_systematic

    input_base = build_stage1_output(config, era, input_systematic).rstrip('/')

    # JES variations have special output path format
    if output_systematic and (output_systematic.startswith('JESup_') or output_systematic.startswith('JESDown_')):
        output_base = _build_jes_output_path(config, era, output_systematic)
    else:
        output_base = build_stage2_output(config, era, output_systematic).rstrip('/')

    dirs = {}
    # MC
    # JES output_base doesn't include data_type, non-JES output_base includes /mc
    if output_systematic and (output_systematic.startswith('JESup_') or output_systematic.startswith('JESDown_')):
        dirs['mc'] = [f"{input_base}/mc/", f"{output_base}/mc/"]
    else:
        dirs['mc'] = [f"{input_base}/mc/", f"{output_base}/"]

    # Data (unless mc_only)
    if not mc_only:
        if output_systematic and (output_systematic.startswith('JESup_') or output_systematic.startswith('JESDown_')):
            data_output = _build_jes_output_path(config, era, output_systematic)
            dirs['data'] = [f"{input_base}/data/", f"{data_output}/data/"]
        else:
            data_output = build_stage2_output(config, era, output_systematic, data_type='data').rstrip('/')
            dirs['data'] = [f"{input_base}/data/", f"{data_output}/"]

    return dirs


def _build_jes_output_path(config, era, jes_systematic):
    """
    Build JES output path with special format.

    JES format: {output_base}/{era}/{stage2}_{jes_systematic}_{stage1}_JESPt22

    Args:
        config: Configuration dictionary.
        era: Era string.
        jes_systematic: JES systematic (e.g., 'JESup_AbsoluteMPFBias_AK4PFchs').

    Returns:
        Path without trailing / or data_type subdirectory.
    """
    paths = config['paths']
    versions = config['versions']
    stage1 = versions['stage1']
    stage2 = versions['stage2']

    # Format: {stage2}_{jes_systematic}_{stage1}_JESPt22
    dir_name = f"{stage2}_{jes_systematic}_{stage1}_JESPt22"

    return os.path.join(paths['output_base'], era, dir_name)


def generate_jobs_for_dir(input_dir, output_dir, era_key, job_dir, if1tau2l,
                          jes_type=0, jes_variation=0, quiet=False):
    """Generate job scripts for a single input directory."""
    sub_script = os.path.join(job_dir, f"{era_key}_subAll.sh")
    jobs_dir = os.path.join(job_dir, f"{era_key}_jobs")

    # Clean and create jobs directory
    if os.path.exists(jobs_dir):
        subprocess.run(['rm', '-rf', jobs_dir], check=True)
    os.makedirs(jobs_dir, exist_ok=True)
    os.makedirs(output_dir, exist_ok=True)

    if not quiet:
        print(f"  Input:  {input_dir}")
        print(f"  Output: {output_dir}")
        print(f"  Jobs:   {jobs_dir}")

    # Check input directory exists
    if not os.path.exists(input_dir):
        print(f"  WARNING: Input directory does not exist: {input_dir}")
        return None

    # Write submission script
    with open(sub_script, 'w') as f:
        f.write("#!/bin/bash\n")
        f.write(f"cd {job_dir}\n")

    job_count = 0
    for entry in os.listdir(input_dir):
        if not uf.checkIfInputDic(entry, isRun3=False):
            continue

        job_file = os.path.join(jobs_dir, f"MV_{era_key}_{entry}.sh")
        write_job_script(job_file, input_dir, entry, output_dir, if1tau2l, jes_type, jes_variation)

        # Add to submission script
        log_dir = os.path.join(output_dir, "log")
        os.makedirs(log_dir, exist_ok=True)
        log_file = os.path.join(log_dir, f"{entry}.log")
        err_file = os.path.join(log_dir, f"{entry}.err")

        with open(sub_script, 'a') as f:
            f.write(f"hep_sub {job_file} -o {log_file} -e {err_file}\n")
        job_count += 1

    # Make scripts executable
    subprocess.run(f"chmod 755 {jobs_dir}/*.sh", shell=True, check=False)
    subprocess.run(['chmod', '755', sub_script], check=False)

    if not quiet:
        print(f"  Generated {job_count} jobs")

    return sub_script if job_count > 0 else None


def write_job_script(job_file, input_dir, entry, output_dir, if1tau2l, jes_type, jes_variation):
    """Write individual job script."""
    code_dir = os.path.dirname(os.path.abspath(__file__))
    code_dir = os.path.dirname(code_dir)  # makeVariables_goodCode/
    project_root = os.path.dirname(code_dir)  # FourTop/

    with open(job_file, 'w') as f:
        f.write("#!/bin/bash\n")
        f.write("/bin/hostname\n")
        f.write(f"cd {project_root}\n")
        f.write("source setEnv_newNew.sh\n")
        f.write("cd makeVariables_goodCode\n")
        cmd = f"./apps/run_makeVariables.out {input_dir} {entry} {output_dir} 0 {if1tau2l} {jes_type} {jes_variation}"
        f.write(cmd + "\n")


def main():
    args = create_parser().parse_args()

    # Load config
    config = load_config(args.config)
    if1tau2l = get_channel_if1tau2l(config)
    channel = get_channel(config)

    if not args.quiet:
        print(f"=== Stage 2 (MV) Job Submission ===")
        print(f"Config: {args.config}")
        print(f"Channel: {channel} (if1tau2l={if1tau2l})")
        if args.sys:
            print(f"Systematic: {args.sys}")
        if args.jes_variation:
            print(f"JES variation: index={args.jes_variation}, type={args.jes_type}")
        print()

    # Determine eras to process
    eras = get_eras_to_process(config, args.era)

    # Build job version string for directory naming
    # For JES: use output_sys (e.g., JESup_AbsoluteMPFBias_AK4PFchs) to create unique job dirs
    # For other systematics: use sys (e.g., TESdm0Up)
    versions = config['versions']
    job_version = f"{versions['stage2']}_{versions['stage1']}"
    if args.output_sys:
        job_version = f"{job_version}_{args.output_sys}"
    elif args.sys:
        job_version = f"{job_version}_{args.sys}"

    job_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), job_version)
    os.makedirs(job_dir, exist_ok=True)

    if not args.quiet:
        print(f"Job directory: {job_dir}")
        print()

    # Create master submission script
    master_script = os.path.join(job_dir, "subAllofAll.sh")
    with open(master_script, 'w') as f:
        f.write("#!/bin/bash\n")
        f.write(f"cd {job_dir}\n")

    sub_scripts = []
    for era in eras:
        if not args.quiet:
            print(f"--- Processing era: {era} ---")

        # For JES, input uses --sys (JESPt22), output uses --output-sys (JESup_SOURCE)
        output_sys = args.output_sys if args.output_sys else args.sys
        dirs = get_input_output_dirs(config, era, args.sys, output_sys, args.mc_only)

        for data_type, (input_dir, output_dir) in dirs.items():
            era_key = f"{era}_{data_type}"
            sub_script = generate_jobs_for_dir(
                input_dir, output_dir, era_key, job_dir, if1tau2l,
                args.jes_type, args.jes_variation, args.quiet
            )
            if sub_script:
                sub_scripts.append(sub_script)
                with open(master_script, 'a') as f:
                    f.write(f"bash {os.path.basename(sub_script)}\n")

        if not args.quiet:
            print()

    subprocess.run(['chmod', '755', master_script], check=False)

    if not args.quiet:
        print(f"Master submission script: {master_script}")

    # Submit jobs
    if args.dry_run:
        print("\n[DRY RUN] Would execute:")
        print(f"  bash {master_script}")
    else:
        print(f"\nSubmitting jobs...")
        uf.sumbitJobs(master_script)
        print("Jobs submitted!")


if __name__ == "__main__":
    main()
