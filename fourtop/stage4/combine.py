"""
CMS Combine Runner
==================

Run CMS Combine statistical analysis workflow.

Usage:
    from fourtop.stage4.combine import (
        ensure_dir, ensure_dir_with_fallback, runCommand
    )
"""

import os
import subprocess
import logging
from pathlib import Path


logger = logging.getLogger(__name__)


def ensure_dir(directory: str) -> Path:
    """
    Safely create directory if it doesn't exist.

    Args:
        directory: Path to directory to create

    Returns:
        Path object of the created/existing directory
    """
    dir_path = Path(directory)
    dir_path.mkdir(parents=True, exist_ok=True)
    logger.debug(f"Ensured directory exists: {directory}")
    return dir_path


def ensure_dir_with_fallback(
    target_dir: str,
    fallback_name: str,
    current_dir: str = None
) -> str:
    """
    Create directory with automatic fallback to current directory on permission errors.

    Args:
        target_dir: Desired directory path to create
        fallback_name: Name of directory to create in current dir if target fails
        current_dir: Current working directory (if None, uses os.getcwd())

    Returns:
        Path to the successfully created directory
    """
    if current_dir is None:
        current_dir = os.getcwd()

    try:
        ensure_dir(target_dir)
        logger.info(f"Output directory: {target_dir}")
        return target_dir
    except (PermissionError, OSError):
        logger.warning(f"Cannot write to {target_dir}, using current directory instead")
        fallback_dir = os.path.join(current_dir, fallback_name)
        ensure_dir(fallback_dir)
        logger.info(f"Output directory: {fallback_dir}")
        return fallback_dir


def ensure_writable_carddir(cardDir: str, current_dir: str = None) -> str:
    """
    Ensure we have a writable directory for processing datacards.

    If cardDir has no write permission, creates a temp directory in current_dir,
    copies all .txt datacards there, and returns the writable directory path.

    Args:
        cardDir: Original card directory path (may be read-only)
        current_dir: Current working directory (if None, uses os.getcwd())

    Returns:
        Path to writable directory containing datacards (ends with /)
    """
    import shutil

    if current_dir is None:
        current_dir = os.getcwd()

    # Ensure cardDir ends with /
    if not cardDir.endswith('/'):
        cardDir += '/'

    # Check if cardDir has write permission
    if os.access(cardDir, os.W_OK):
        return cardDir

    # No write permission, create temp working directory in current dir
    dirname = os.path.basename(cardDir.rstrip('/'))
    working_cardDir = os.path.join(current_dir, f'temp_{dirname}/')
    os.makedirs(working_cardDir, exist_ok=True)
    logger.warning(f"No write permission for {cardDir}, using: {working_cardDir}")

    # Copy all .txt datacards to working directory
    for en in os.listdir(cardDir):
        if '.txt' in en:
            src = os.path.join(cardDir, en)
            dst = os.path.join(working_cardDir, en)
            shutil.copy2(src, dst)
            logger.info(f"Copied {en} to working directory")

    return working_cardDir


def get_workspace_file(
    cardDir: str,
    ifVLL: bool = False,
    channel: str = '1tau1l'
) -> str:
    """
    Auto-detect and return the path to the workspace file.

    Args:
        cardDir: Card directory path (should end with /)
        ifVLL: If True, use VLL-specific datacard naming
        channel: Analysis channel (e.g., '1tau1l', '1tau0l', '1tau2l')

    Returns:
        Path to the workspace file, or None if not found
    """
    workspaceDir = cardDir + 'workspace/'

    if ifVLL:
        datacardFile = os.path.join(workspaceDir, f'datacard_{channel}.root')
        if not os.path.isfile(datacardFile):
            logger.warning(f"datacard_{channel}.root not found, searching...")
            available = [f for f in os.listdir(workspaceDir)
                        if f.endswith('.root') and f.startswith('datacard_')]
            if available:
                datacardFile = os.path.join(workspaceDir, available[0])
                logger.info(f"Auto-detected: {available[0]}")
            else:
                logger.error(f"No workspace files found in {workspaceDir}")
                return None
        else:
            logger.info(f"Using VLL datacard: datacard_{channel}.root")
    else:
        datacardFile = os.path.join(workspaceDir, 'datacard.root')
        logger.info("Using tttt datacard: datacard.root")

    return datacardFile


def runCommand(com: str, check_returncode: bool = True):
    """
    Execute a shell command with proper error handling.

    Args:
        com: Command string to execute
        check_returncode: If True, raise exception on non-zero return code

    Returns:
        Tuple of (stdout, stderr, returncode)

    Raises:
        subprocess.CalledProcessError: If command fails and check_returncode=True
    """
    logger.info(f"Running: {com}")
    env = os.environ.copy()
    env['PYTHONNOUSERSITE'] = '1'

    try:
        process = subprocess.Popen(
            com,
            shell=True,
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            universal_newlines=True
        )
        stdout, stderr = process.communicate()
        returncode = process.returncode

        if stdout:
            logger.info(f"stdout: {stdout}")
        if stderr:
            if returncode != 0:
                logger.error(f"stderr: {stderr}")
            else:
                print(stderr)

        if check_returncode and returncode != 0:
            logger.error(f"Command failed (exit code {returncode}): {com}")
            raise subprocess.CalledProcessError(returncode, com, output=stdout, stderr=stderr)

        logger.info(f"✓ Command completed (exit code: {returncode})")
        return stdout, stderr, returncode

    except Exception as e:
        logger.error(f"Failed to execute: {com}")
        logger.error(f"Error: {e}")
        if check_returncode:
            raise
        return None, None, -1


def cardToWorkspaces(cardDir: str) -> str:
    """
    Convert text datacards to RooWorkspace ROOT files.

    Args:
        cardDir: Directory containing .txt datacards

    Returns:
        Path to working directory containing workspaces
    """
    logger.info('Converting datacards to workspaces...')
    original_dir = os.getcwd()
    workspace_count = 0

    working_cardDir = ensure_writable_carddir(cardDir, original_dir)
    working_cardDir = os.path.abspath(working_cardDir)
    if not working_cardDir.endswith('/'):
        working_cardDir += '/'

    os.chdir(working_cardDir)
    logger.info(f"Working directory: {working_cardDir}")

    for en in os.listdir(working_cardDir):
        if '.txt' not in en:
            continue
        idatacard = working_cardDir + en
        if os.path.isfile(idatacard):
            logger.info(f'Processing: {idatacard}')
            iworkspaceName = en.replace('.txt', '.root')

            iworkspaceDir = working_cardDir + 'workspace/'
            ensure_dir(iworkspaceDir)

            iworkspace = iworkspaceDir + iworkspaceName
            command = f'text2workspace.py {idatacard} -o {iworkspace}'
            logger.info(f'Running: {command}')

            env = os.environ.copy()
            env['PYTHONNOUSERSITE'] = '1'
            process = subprocess.Popen([command], shell=True, env=env)
            output = process.communicate()[0]
            if output:
                logger.debug(output)
            workspace_count += 1

    logger.info(f'✓ Created {workspace_count} workspace(s)')

    os.chdir(original_dir)
    return working_cardDir
