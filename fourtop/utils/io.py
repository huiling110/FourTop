"""
I/O and File Operations
=======================

File and directory manipulation utilities.

Usage:
    from fourtop.utils.io import checkMakeDir, runCommand

    checkMakeDir('/path/to/dir')
    runCommand('ls -la')
"""

import os
import subprocess
from typing import Optional


def checkMakeDir(folder: str, ifDelete: bool = False) -> None:
    """
    Create directory if it doesn't exist.

    Args:
        folder: Path to directory
        ifDelete: If True and directory exists, delete contents
    """
    if not os.path.exists(folder):
        os.makedirs(folder, exist_ok=True)
    elif ifDelete:
        os.system('rm -rf ' + folder + '/*')


def runCommand(command: str, ifDryRun: bool = False) -> Optional[str]:
    """
    Run a shell command.

    Args:
        command: Command string to execute
        ifDryRun: If True, print command but don't execute

    Returns:
        Command output or None
    """
    print('Running command:', command)
    if not ifDryRun:
        process = subprocess.run(command, shell=True, capture_output=True, text=True)
        if process.stdout:
            print(process.stdout)
        if process.returncode != 0 and process.stderr:
            print('Error:', process.stderr)
        return process.stdout
    print('Done running command\n')
    return None


def submitJobs(jobsh: str) -> None:
    """
    Submit jobs via shell script.

    Args:
        jobsh: Path to job submission script
    """
    print('Starting to submit jobs')
    command = f'bash {jobsh}'
    process = subprocess.run(command, shell=True)
    output = process.stdout
    print(output)
    print('Jobs submitted')


def getInputDic(inVersion: str, histVersion: str, era: str) -> dict:
    """
    Get input directory dictionary for final hists folder structure.

    Args:
        inVersion: Input version string
        histVersion: Histogram version string
        era: Era string (e.g., '2018')

    Returns:
        Dictionary with 'mc' and 'data' paths
    """
    inputDirBase = f'/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}/'
    return {
        'mc': f'{inputDirBase}{inVersion}/mc/{histVersion}/',
        'data': f'{inputDirBase}{inVersion}/data/{histVersion}/',
    }


def getInputDicNew(inputDirMC: str) -> dict:
    """
    Get input directory dictionary from MC path.

    Args:
        inputDirMC: Path to MC directory

    Returns:
        Dictionary with 'mc' and 'data' paths
    """
    return {
        'mc': inputDirMC,
        'data': inputDirMC.replace('mc', 'data'),
    }


def getDirDic(inputMC: str) -> dict:
    """
    Create directory dictionary from MC path.

    Args:
        inputMC: MC input directory path

    Returns:
        Dictionary with 'mc' and 'data' keys
    """
    return {
        'mc': inputMC,
        'data': inputMC.replace('mc', 'data')
    }
