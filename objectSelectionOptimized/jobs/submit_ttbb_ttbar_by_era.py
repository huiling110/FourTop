#!/usr/bin/env python3
"""Submit Stage 1 (OS) jobs for TTBB and ttbar samples for any era."""

import os
import sys
import glob
import subprocess
import argparse

# Era configuration
ERA_CONFIG = {
    '2018': {
        'input_base': '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/',
        'output_prefix': 'UL2018',
    },
    '2017': {
        'input_base': '/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/',
        'output_prefix': 'UL2017',
    },
    '2016postVFP': {
        'input_base': '/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/',
        'output_prefix': 'UL2016postVFP',
    },
    '2016preVFP': {
        'input_base': '/publicfs/cms/data/TopQuark/nanoAOD/2016APV/mc/',
        'output_prefix': 'UL2016preVFP',
    },
}

VERSION = 'v94HadroPreJetVetoHemOnly_TTBBtest'
CODE_PATH = '/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/objectSelectionOptimized'

# Samples to process
SAMPLES = [
    'TTBB_4f_TTToHadronic',
    'TTBB_4f_TTToSemiLeptonic',
    'TTBB_4f_TTTo2L2Nu',
    'ttbar_0l',
    'ttbar_1l',
    'ttbar_2l',
]


def create_and_submit_jobs(sample, era, dry_run=False):
    """Create and submit jobs for a single sample."""
    config = ERA_CONFIG[era]
    input_base = config['input_base']
    output_prefix = config['output_prefix']

    output_base = f'/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/{output_prefix}/{VERSION}/mc/'
    jobs_base = f'/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/{output_prefix}/{VERSION}/jobs_eachYear/{output_prefix}/'

    input_dir = f'{input_base}{sample}/'
    output_dir = f'{output_base}{sample}/'
    log_dir = f'{output_dir}log/'
    job_dir = f'{jobs_base}{sample}/'

    # Create directories
    os.makedirs(output_dir, exist_ok=True)
    os.makedirs(log_dir, exist_ok=True)
    os.makedirs(job_dir, exist_ok=True)

    # Get all input files
    input_files = glob.glob(f'{input_dir}*.root')
    n_files = len(input_files)

    if n_files == 0:
        print(f'  {sample}: No input files found in {input_dir}')
        return 0

    print(f'  {sample}: {n_files} input files')

    # Create individual job scripts
    for i, fpath in enumerate(input_files):
        fname = os.path.basename(fpath)
        script_path = f'{job_dir}OS_{output_prefix}{sample}_{i}.sh'

        with open(script_path, 'w') as f:
            f.write('#!/bin/bash\n')
            f.write(f'cd {CODE_PATH}\n')
            # Source full environment for el9 libraries
            f.write('source /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/setEnv_newNew.sh\n')
            f.write(f'./apps/run_objectSelection.out {input_dir} {fname} {output_dir} 0 0 0 0 0 0 0\n')
        os.chmod(script_path, 0o755)

    if dry_run:
        print(f'    [DRY RUN] Would submit {n_files} jobs')
        return n_files

    # Submit jobs using AlmaLinux9 for CMSSW_14 compatibility
    cmd = (f'cd {job_dir} && hep_sub -os AlmaLinux9 '
           f'OS_{output_prefix}{sample}_"%{{ProcId}}".sh '
           f'-o {log_dir}_%{{ProcId}}.log '
           f'-e {log_dir}_%{{ProcId}}.err '
           f'-n {n_files}')

    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    if result.stdout.strip():
        print(f'    {result.stdout.strip()}')
    if result.returncode != 0 and result.stderr:
        print(f'    ERROR: {result.stderr}')

    return n_files


def main():
    parser = argparse.ArgumentParser(description='Submit OS jobs for TTBB/ttbar samples')
    parser.add_argument('--era', type=str, required=True,
                        choices=['2017', '2016postVFP', '2016preVFP', '2018', 'all'],
                        help='Era to process')
    parser.add_argument('--dry-run', action='store_true',
                        help='Create job scripts but do not submit')
    args = parser.parse_args()

    if args.era == 'all':
        eras = ['2017', '2016postVFP', '2016preVFP']
    else:
        eras = [args.era]

    total_jobs = 0
    for era in eras:
        print(f'\n=== Processing {era} ===')
        for sample in SAMPLES:
            n = create_and_submit_jobs(sample, era, dry_run=args.dry_run)
            total_jobs += n

    print(f'\n{"[DRY RUN] " if args.dry_run else ""}Total jobs: {total_jobs}')
    if not args.dry_run:
        print('Check status with: hep_q -u huahuil | grep OS_')


if __name__ == '__main__':
    main()
