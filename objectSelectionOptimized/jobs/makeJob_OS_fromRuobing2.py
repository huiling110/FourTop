#!/usr/bin/env python3
"""
Stage 1: Object Selection Job Submission Script

Submits jobs for object selection (NanoAOD -> skimmed ntuples).

Standalone usage:
    python3 makeJob_OS_fromRuobing2.py --config ../../config/analysis_config.yaml --era 2018
    python3 makeJob_OS_fromRuobing2.py --config ../../config/analysis_config.yaml  # all eras

Via workflow runner:
    python3 run_workflow.py --stage 1 --config config/analysis_config.yaml

Requirements:
    - Source environment first: source setEnv_newNew.sh
    - YAML config with versions.stage1 defined
"""

import os
import sys
import subprocess
import re
import glob
import argparse

# Add plotting directory to path for workflow_utils
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', 'plotting'))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', 'hua', 'src_py'))

from workflow_utils import (
    load_config,
    get_eras,
    get_channel,
    get_versions,
    get_channel_if1tau2l,
    build_stage1_input,
    build_stage1_output,
    ERA_TO_UL,
)
import ttttGlobleQuantity as gq
import usefulFunc as uf


# =============================================================================
# Systematic Variation Handling
# =============================================================================

# TES values: 0=nominal, 1=Up, 2=Down, 3-10=decay mode variations
TES_SUFFIX = {
    1: 'TESUp', 2: 'TESDown',
    3: 'TESdm0Up', 4: 'TESdm0Down',
    5: 'TESdm1Up', 6: 'TESdm1Down',
    7: 'TESdm10Up', 8: 'TESdm10Down',
    9: 'TESdm11Up', 10: 'TESdm11Down',
}

SYS_SUFFIX = {1: 'Up', 2: 'Down'}


def get_systematic_suffix(TES: int, eleScale: int, JESSys: int, JERSys: int, METSys: int) -> str:
    """
    Build systematic suffix from variation parameters.

    Returns empty string for nominal, or suffix like '_JESUp', '_TESdm0Down', etc.
    """
    # Check for multiple non-zero systematics
    non_zero = [p for p in [TES, eleScale, JESSys, JERSys, METSys] if p != 0]
    if len(non_zero) > 1:
        raise ValueError("Only one systematic parameter can be non-zero at a time")

    if TES != 0:
        if TES not in TES_SUFFIX:
            raise ValueError(f"Invalid TES value: {TES}")
        return TES_SUFFIX[TES]
    elif eleScale != 0:
        return f"EleScale{SYS_SUFFIX[eleScale]}"
    elif JESSys != 0:
        return "JESPt22"  # JES uses fixed suffix
    elif JERSys != 0:
        return f"JER{SYS_SUFFIX[JERSys]}"
    elif METSys != 0:
        return f"MET{SYS_SUFFIX[METSys]}"

    return ""  # Nominal


# =============================================================================
# Job Script Generation
# =============================================================================

def prepare_job_script(
    input_dir: str,
    output_dir: str,
    script_path: str,
    input_file: str,
    TES: int,
    eleScale: int,
    JESSys: int,
    JERSys: int,
    METSys: int,
    if1tau2l: int
):
    """Write a single job script for one input file."""
    app_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    with open(script_path, 'w') as f:
        f.write("#!/bin/bash\n")
        f.write(f"cd {app_dir}\n")
        # Set library paths for RoccoR and myLibrary (needed for HTCondor jobs)
        f.write("export LD_LIBRARY_PATH=/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/roccor:"
                "/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/myLibrary:$LD_LIBRARY_PATH\n")
        command = (f"./apps/run_objectSelection.out {input_dir} {input_file} {output_dir} "
                   f"{TES} {eleScale} {JESSys} {JERSys} {METSys} {if1tau2l} 0")
        f.write(command)


def make_jobs_for_directory(
    input_dir: str,
    output_dir: str,
    job_scripts_folder: str,
    is_data: bool,
    era: str,
    is_run3: bool,
    skip_processes: list,
    TES: int,
    eleScale: int,
    JESSys: int,
    JERSys: int,
    METSys: int,
    if1tau2l: int,
    quiet: bool = False
):
    """Create and submit jobs for all processes in a directory."""
    all_processes = os.listdir(input_dir)

    # Adjust output for data vs MC
    output_subdir = 'data/' if is_data else 'mc/'
    output_dir = os.path.join(output_dir, output_subdir)
    uf.checkMakeDir(output_dir)

    for process in all_processes:
        if not quiet:
            print(f'Processing: {process}')

        if not uf.checkIfInputDic(process, is_run3):
            continue

        # Check if process should be skipped
        process_group = gq.histoGramPerSample.get(process)
        if process_group in skip_processes:
            if not quiet:
                print(f'  Skipping {process} (group: {process_group})')
            continue

        # Setup directories
        process_job_dir = os.path.join(job_scripts_folder, process)
        if os.path.exists(process_job_dir):
            subprocess.run(f'rm -fr {process_job_dir}', shell=True)
        os.makedirs(process_job_dir)

        process_output_dir = os.path.join(output_dir, process)
        log_dir = os.path.join(process_output_dir, 'log')
        uf.checkMakeDir(process_output_dir)
        uf.checkMakeDir(log_dir)

        # Create submission script
        submit_script = os.path.join(job_scripts_folder, f"{process}.sh")
        if os.path.exists(submit_script):
            os.remove(submit_script)

        sample_dir = os.path.join(input_dir, process)
        sample_files = glob.glob(os.path.join(sample_dir, "*.root"))

        if not sample_files:
            continue

        # Create individual job scripts
        for idx, _ in enumerate(sample_files):
            entry = os.path.basename(sample_files[idx])
            job_name = f'OS_{era}{process}_{idx}.sh'
            job_path = os.path.join(process_job_dir, job_name)
            prepare_job_script(
                sample_dir + '/', process_output_dir + '/', job_path, entry,
                TES, eleScale, JESSys, JERSys, METSys, if1tau2l
            )

        # Submit jobs
        job_pattern = f'OS_{era}{process}_"%{{ProcId}}".sh'
        log_file = os.path.join(log_dir, '_%{ProcId}.log')
        err_file = os.path.join(log_dir, '_%{ProcId}.err')

        submit_cmd = (f"hep_sub {process_job_dir}/{job_pattern} "
                      f"-o {log_file} -e {err_file} -n {len(sample_files)}")

        result = subprocess.run(submit_cmd, shell=True, capture_output=True, text=True)

        if result.returncode == 0:
            match = re.search(r'submitted to cluster (\d+)', result.stdout)
            if match:
                cluster_id = match.group(1)
                if not quiet:
                    print(f"  Submitted cluster: {cluster_id} ({len(sample_files)} jobs)")

                # Log cluster info
                csv_path = os.path.join(job_scripts_folder, 'cluster_logs.csv')
                with open(csv_path, 'a') as f:
                    f.write(f"{cluster_id},{log_dir},{process_job_dir},0\n")
        else:
            print(f"  Submit failed: {result.stderr}")

        # Make scripts executable
        os.system(f'chmod 777 {process_job_dir}/*sh')

        if not quiet:
            print(f'  Done with: {process}\n')


def make_sub_all_script(jobs_dir: str, era: str):
    """Create a script to submit all jobs for an era."""
    sub_all_file = os.path.join(jobs_dir, f"subAllJobs{era}.sh")
    era_dir = os.path.join(jobs_dir, era)

    if os.path.exists(sub_all_file):
        os.remove(sub_all_file)

    with open(sub_all_file, 'w') as f:
        f.write("#!/bin/bash\n")
        f.write(f"cd {era_dir}\n")
        for item in os.listdir(era_dir):
            if item.endswith('.sh'):
                f.write(f"sh {item}\n")

    os.chmod(sub_all_file, 0o777)


# =============================================================================
# Main Entry Points
# =============================================================================

def run_stage1(
    config: dict,
    era: str,
    TES: int = 0,
    eleScale: int = 0,
    JESSys: int = 0,
    JERSys: int = 0,
    METSys: int = 0,
    quiet: bool = False
):
    """
    Run Stage 1 job submission for a single era.

    Args:
        config: Configuration dictionary from workflow_utils.load_config()
        era: Era string (2018, 2017, 2016preVFP, 2016postVFP)
        TES, eleScale, JESSys, JERSys, METSys: Systematic variation parameters
        quiet: Reduce output verbosity
    """
    # Get systematic suffix
    sys_suffix = get_systematic_suffix(TES, eleScale, JESSys, JERSys, METSys)
    is_systematic = bool(sys_suffix)

    # Get paths using workflow_utils
    input_dir = build_stage1_input(config, era)
    output_dir = build_stage1_output(config, era, sys_suffix if sys_suffix else None)

    # Get channel info
    if1tau2l = get_channel_if1tau2l(config)
    channel = get_channel(config)

    # Determine which processes to skip
    if if1tau2l:  # 1tau2l channel
        skip_processes = ['jetHT', 'BTagCSV', 'qcd', 'ttExtra']
        if is_systematic:
            skip_processes += ['singleMu', 'singleE', 'doubleMu', 'muonEG', 'eGamma', 'doubleEG']
    else:  # 1tau0l or 1tau1l
        skip_processes = ['singleMu', 'singleE', 'doubleMu', 'muonEG', 'eGamma', 'doubleEG', 'ttExtra', 'Minor']
        if is_systematic:
            skip_processes += ['jetHT', 'BTagCSV', 'qcd']

    if not quiet:
        print(f"\n{'='*60}")
        print(f"Stage 1: Object Selection")
        print(f"{'='*60}")
        print(f"Era: {era}")
        print(f"Channel: {channel} (if1tau2l={if1tau2l})")
        print(f"Systematic: {sys_suffix if sys_suffix else 'nominal'}")
        print(f"Input: {input_dir}")
        print(f"Output: {output_dir}")
        print(f"Skip processes: {skip_processes}")
        print(f"{'='*60}\n")

    # Setup job directories
    uf.checkMakeDir(output_dir)
    jobs_dir = os.path.join(output_dir, 'jobs_eachYear')
    uf.checkMakeDir(jobs_dir)

    era_ul = ERA_TO_UL.get(era, f'UL{era}')
    job_scripts_folder = os.path.join(jobs_dir, era_ul)

    if os.path.exists(job_scripts_folder):
        subprocess.run(f'rm -fr {job_scripts_folder}', shell=True)
        if not quiet:
            print(f'Removing old job folder: {job_scripts_folder}')
    uf.checkMakeDir(job_scripts_folder)

    is_run3 = uf.isRun3(input_dir)

    # Submit MC jobs
    mc_input = os.path.join(input_dir, 'mc')
    if os.path.exists(mc_input):
        make_jobs_for_directory(
            mc_input, output_dir, job_scripts_folder, False, era_ul, is_run3,
            skip_processes, TES, eleScale, JESSys, JERSys, METSys, if1tau2l, quiet
        )

    # Submit data jobs
    data_input = os.path.join(input_dir, 'data')
    if os.path.exists(data_input):
        make_jobs_for_directory(
            data_input, output_dir, job_scripts_folder, True, era_ul, is_run3,
            skip_processes, TES, eleScale, JESSys, JERSys, METSys, if1tau2l, quiet
        )

    # Create combined submission script
    make_sub_all_script(jobs_dir, era_ul)

    # Start monitoring script (optional)
    speed_script = '/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/objectSelectionOptimized/jobs/speedOS.py'
    if os.path.exists(speed_script):
        csv_path = os.path.join(job_scripts_folder, 'cluster_logs.csv')
        log_path = os.path.join(job_scripts_folder, 'output.log')
        subprocess.run(f"nohup python3 {speed_script} {csv_path} > {log_path} 2>&1 &", shell=True)

    if not quiet:
        version = get_versions(config)['stage1']
        print(f"\nDone submitting jobs for: {version} ({era})")


def create_parser():
    """Create argument parser."""
    parser = argparse.ArgumentParser(
        description='Stage 1: Submit Object Selection jobs',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Submit nominal jobs for 2018
  python3 makeJob_OS_fromRuobing2.py --config ../../config/analysis_config.yaml --era 2018

  # Submit for all eras in config
  python3 makeJob_OS_fromRuobing2.py --config ../../config/analysis_config.yaml

  # Dry run (show what would be done)
  python3 makeJob_OS_fromRuobing2.py --config ../../config/analysis_config.yaml --dry-run

  # Submit JES systematic variation
  python3 makeJob_OS_fromRuobing2.py --config ../../config/analysis_config.yaml --era 2018 --sys JES
        """
    )
    parser.add_argument('--config', '-c', type=str, required=True,
                        help='Path to YAML config file')
    parser.add_argument('--era', '-e', type=str, default=None,
                        help='Era to process (default: all from config)')
    parser.add_argument('--dry-run', action='store_true',
                        help='Print configuration without submitting')
    parser.add_argument('--quiet', '-q', action='store_true',
                        help='Reduce output verbosity')
    parser.add_argument('--sys', type=str, default=None,
                        choices=['JES', 'JERUp', 'JERDown', 'METUp', 'METDown',
                                 'EleScaleUp', 'EleScaleDown',
                                 'TESUp', 'TESDown', 'TESdm0Up', 'TESdm0Down',
                                 'TESdm1Up', 'TESdm1Down', 'TESdm10Up', 'TESdm10Down',
                                 'TESdm11Up', 'TESdm11Down'],
                        help='Systematic variation to run')
    return parser


def parse_systematic(sys_name: str) -> tuple:
    """Parse systematic name to parameter tuple (TES, eleScale, JESSys, JERSys, METSys)."""
    if sys_name is None:
        return (0, 0, 0, 0, 0)

    sys_map = {
        'JES': (0, 0, 1, 0, 0),
        'JERUp': (0, 0, 0, 1, 0),
        'JERDown': (0, 0, 0, 2, 0),
        'METUp': (0, 0, 0, 0, 1),
        'METDown': (0, 0, 0, 0, 2),
        'EleScaleUp': (0, 1, 0, 0, 0),
        'EleScaleDown': (0, 2, 0, 0, 0),
        'TESUp': (1, 0, 0, 0, 0),
        'TESDown': (2, 0, 0, 0, 0),
        'TESdm0Up': (3, 0, 0, 0, 0),
        'TESdm0Down': (4, 0, 0, 0, 0),
        'TESdm1Up': (5, 0, 0, 0, 0),
        'TESdm1Down': (6, 0, 0, 0, 0),
        'TESdm10Up': (7, 0, 0, 0, 0),
        'TESdm10Down': (8, 0, 0, 0, 0),
        'TESdm11Up': (9, 0, 0, 0, 0),
        'TESdm11Down': (10, 0, 0, 0, 0),
    }
    return sys_map.get(sys_name, (0, 0, 0, 0, 0))


def main():
    """Main entry point."""
    args = create_parser().parse_args()

    # Load config using workflow_utils
    config = load_config(args.config)

    # Get eras to process
    eras = [args.era] if args.era else get_eras(config)

    # Parse systematic
    TES, eleScale, JESSys, JERSys, METSys = parse_systematic(args.sys)

    if not args.quiet:
        print(f"Config: {args.config}")
        print(f"Version: {get_versions(config)['stage1']}")
        print(f"Channel: {get_channel(config)}")
        print(f"Eras: {eras}")
        print(f"Systematic: {args.sys if args.sys else 'nominal'}")

    if args.dry_run:
        print("\n[DRY RUN] Would submit jobs for above configuration")
        for era in eras:
            input_dir = build_stage1_input(config, era)
            output_dir = build_stage1_output(config, era,
                         get_systematic_suffix(TES, eleScale, JESSys, JERSys, METSys) or None)
            print(f"\n  Era {era}:")
            print(f"    Input:  {input_dir}")
            print(f"    Output: {output_dir}")
        return

    # Submit jobs for each era
    for era in eras:
        run_stage1(
            config, era,
            TES=TES, eleScale=eleScale, JESSys=JESSys, JERSys=JERSys, METSys=METSys,
            quiet=args.quiet
        )


if __name__ == "__main__":
    main()
