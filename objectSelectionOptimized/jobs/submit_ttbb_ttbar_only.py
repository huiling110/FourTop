#!/usr/bin/env python3
"""Submit Stage 1 jobs for TTBB and ttbar samples only."""

import os
import glob
import subprocess

# Configuration
era = '2018'
version = 'v94HadroPreJetVetoHemOnly_TTBBtest'
input_base = '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/'
output_base = f'/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/{version}/mc/'
jobs_base = f'/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/{version}/jobs_eachYear/UL2018/'
code_path = '/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/objectSelectionOptimized'

# Samples to process
samples = [
    'TTBB_4f_TTToHadronic',
    'TTBB_4f_TTToSemiLeptonic',
    'TTBB_4f_TTTo2L2Nu',
    'ttbar_0l',
    'ttbar_1l',
    'ttbar_2l',
]

def create_and_submit_jobs(sample):
    """Create and submit jobs for a single sample."""
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
    print(f'{sample}: {n_files} input files')

    # Create individual job scripts
    for i, fpath in enumerate(input_files):
        fname = os.path.basename(fpath)
        script_path = f'{job_dir}OS_UL2018{sample}_{i}.sh'

        with open(script_path, 'w') as f:
            f.write('#!/bin/bash\n')
            f.write(f'cd {code_path}\n')
            # Source full environment for el9 libraries (libssl.so.3, etc.)
            f.write('source /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/setEnv_newNew.sh\n')
            f.write(f'./apps/run_objectSelection.out {input_dir} {fname} {output_dir} 0 0 0 0 0 0 0\n')
        os.chmod(script_path, 0o755)

    # Create submission script
    submit_script = f'{jobs_base}{sample}.sh'
    with open(submit_script, 'w') as f:
        f.write(f'cd {job_dir}\n\n')
        f.write(f'hep_sub -os CentOS7 OS_UL2018{sample}_"%{{ProcId}}".sh ')
        f.write(f'-o {log_dir}_%{{ProcId}}.log ')
        f.write(f'-e {log_dir}_%{{ProcId}}.err ')
        f.write(f'-n {n_files}\n')
    os.chmod(submit_script, 0o755)

    # Submit jobs (use AlmaLinux9 for CMSSW_14 compatibility)
    print(f'Submitting {n_files} jobs for {sample}...')
    result = subprocess.run(f'cd {job_dir} && hep_sub -os AlmaLinux9 OS_UL2018{sample}_"%{{ProcId}}".sh -o {log_dir}_%{{ProcId}}.log -e {log_dir}_%{{ProcId}}.err -n {n_files}',
                          shell=True, capture_output=True, text=True)
    print(result.stdout)
    if result.stderr:
        print(f'stderr: {result.stderr}')

    return n_files

if __name__ == '__main__':
    total_jobs = 0
    for sample in samples:
        n = create_and_submit_jobs(sample)
        total_jobs += n

    print(f'\nTotal jobs submitted: {total_jobs}')
    print('Check status with: hep_q -u huahuil | grep -E "TTBB|ttbar"')
