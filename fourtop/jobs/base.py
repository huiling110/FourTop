"""
Job Submission Base Module
==========================

Base class for HTCondor job submission across all analysis stages.

Usage:
    from fourtop.jobs.base import JobSubmitter

    class MyJobSubmitter(JobSubmitter):
        def generate_command(self, process, input_dir, output_dir):
            return f"./my_app.out {input_dir} {process} {output_dir}"

    submitter = MyJobSubmitter(config, era)
    submitter.submit_all(processes, input_dir, output_dir)
"""

import os
import re
import subprocess
import logging
from pathlib import Path
from typing import List, Dict, Optional, Tuple
from abc import ABC, abstractmethod

logger = logging.getLogger(__name__)


class JobSubmitter(ABC):
    """
    Base class for HTCondor job submission.

    Handles common job submission patterns:
    - Directory structure creation
    - Job script generation
    - HTCondor submission via hep_sub
    - Cluster logging

    Subclasses must implement:
    - generate_command(): Return the command to run in the job
    - get_job_prefix(): Return prefix for job script names (e.g., 'OS', 'MV', 'WH')
    """

    def __init__(
        self,
        config: Dict,
        era: str,
        systematic: Optional[str] = None,
        quiet: bool = False
    ):
        """
        Initialize job submitter.

        Args:
            config: Configuration dictionary from load_config()
            era: Era string (2018, 2017, 2016preVFP, 2016postVFP)
            systematic: Optional systematic variation suffix
            quiet: Reduce output verbosity
        """
        self.config = config
        self.era = era
        self.systematic = systematic
        self.quiet = quiet

        # Extract common config values
        self.channel = config.get('channel', '1tau0l')
        self.versions = config.get('versions', {})
        self.paths = config.get('paths', {})
        self.options = config.get('options', {})

        # Get channel flag for C++ executables
        self.if1tau2l = 1 if self.channel == '1tau2l' else 0

        # HTCondor options
        self.os_type = 'CentOS7'  # Default OS for job execution

    @abstractmethod
    def generate_command(
        self,
        process: str,
        input_dir: str,
        output_dir: str,
        **kwargs
    ) -> str:
        """
        Generate the command to run in the job script.

        Args:
            process: Process name (e.g., 'tttt', 'TTTo2L2Nu')
            input_dir: Input directory path
            output_dir: Output directory path
            **kwargs: Additional arguments for specific job types

        Returns:
            Command string to execute in the job
        """
        pass

    @abstractmethod
    def get_job_prefix(self) -> str:
        """
        Return prefix for job script names.

        Returns:
            Prefix string (e.g., 'OS', 'MV', 'WH')
        """
        pass

    def get_environment_script(self) -> str:
        """
        Return path to environment setup script.

        Override in subclass if different environment is needed.
        """
        fourtop_dir = os.path.dirname(os.path.dirname(os.path.dirname(
            os.path.abspath(__file__)
        )))
        return os.path.join(fourtop_dir, 'setEnv_newNew.sh')

    def get_working_directory(self) -> str:
        """
        Return the working directory for job execution.

        Override in subclass if different directory is needed.
        """
        fourtop_dir = os.path.dirname(os.path.dirname(os.path.dirname(
            os.path.abspath(__file__)
        )))
        return fourtop_dir

    def create_job_directory(self, base_dir: str, job_name: str) -> Tuple[str, str, str]:
        """
        Create job directory structure.

        Args:
            base_dir: Base directory for jobs
            job_name: Name for the job subdirectory

        Returns:
            Tuple of (job_scripts_dir, log_dir, submission_script_path)
        """
        job_dir = os.path.join(base_dir, job_name)
        job_scripts_dir = os.path.join(job_dir, 'scripts')
        log_dir = os.path.join(job_dir, 'log')

        for d in [job_dir, job_scripts_dir, log_dir]:
            os.makedirs(d, exist_ok=True)

        submission_script = os.path.join(job_dir, 'submit_all.sh')

        return job_scripts_dir, log_dir, submission_script

    def write_job_script(
        self,
        script_path: str,
        command: str,
        working_dir: Optional[str] = None,
        env_script: Optional[str] = None
    ) -> None:
        """
        Write individual job shell script.

        Args:
            script_path: Path to write the job script
            command: Command to execute in the job
            working_dir: Working directory (default: FourTop root)
            env_script: Environment script path (default: setEnv_newNew.sh)
        """
        if working_dir is None:
            working_dir = self.get_working_directory()
        if env_script is None:
            env_script = self.get_environment_script()

        with open(script_path, 'w') as f:
            f.write("#!/bin/bash\n")
            f.write("/bin/hostname\n")
            f.write(f"cd {working_dir}\n")
            f.write(f"source {env_script}\n")
            f.write(command + "\n")

        os.chmod(script_path, 0o755)

    def write_submission_script(
        self,
        submission_script: str,
        job_entries: List[Dict[str, str]]
    ) -> None:
        """
        Write HTCondor submission script.

        Args:
            submission_script: Path to submission script
            job_entries: List of dicts with keys: 'script', 'log', 'err'
        """
        with open(submission_script, 'w') as f:
            f.write("#!/bin/bash\n")
            f.write(f"cd {os.path.dirname(submission_script)}\n")
            for entry in job_entries:
                cmd = f"hep_sub -os {self.os_type} {entry['script']} "
                cmd += f"-o {entry['log']} -e {entry['err']}\n"
                f.write(cmd)

        os.chmod(submission_script, 0o755)

    def submit_jobs(
        self,
        submission_script: str,
        dry_run: bool = False
    ) -> Optional[List[str]]:
        """
        Submit jobs via the submission script.

        Args:
            submission_script: Path to submission script
            dry_run: If True, print commands without executing

        Returns:
            List of cluster IDs if successful, None otherwise
        """
        if dry_run:
            if not self.quiet:
                logger.info(f"[DRY RUN] Would execute: bash {submission_script}")
            return None

        if not self.quiet:
            logger.info(f"Submitting jobs from: {submission_script}")

        result = subprocess.run(
            f"bash {submission_script}",
            shell=True,
            capture_output=True,
            text=True
        )

        cluster_ids = []
        for line in result.stdout.split('\n'):
            match = re.search(r'submitted to cluster (\d+)', line)
            if match:
                cluster_ids.append(match.group(1))

        if not self.quiet:
            logger.info(f"Submitted {len(cluster_ids)} cluster(s)")

        return cluster_ids

    def submit_all(
        self,
        processes: List[str],
        input_dir: str,
        output_dir: str,
        job_base_dir: str,
        dry_run: bool = False,
        **kwargs
    ) -> Optional[List[str]]:
        """
        Generate and submit jobs for all processes.

        Args:
            processes: List of process names to submit
            input_dir: Input directory path
            output_dir: Output directory path
            job_base_dir: Base directory for job files
            dry_run: If True, generate scripts but don't submit
            **kwargs: Additional arguments passed to generate_command()

        Returns:
            List of cluster IDs if submitted, None if dry_run
        """
        # Create directory structure
        job_name = f"{self.get_job_prefix()}_{self.era}"
        if self.systematic:
            job_name += f"_{self.systematic}"

        job_scripts_dir, log_dir, submission_script = self.create_job_directory(
            job_base_dir, job_name
        )

        if not self.quiet:
            logger.info(f"Job directory: {os.path.dirname(job_scripts_dir)}")
            logger.info(f"Input: {input_dir}")
            logger.info(f"Output: {output_dir}")

        # Ensure output directory exists
        os.makedirs(output_dir, exist_ok=True)

        # Generate job scripts
        job_entries = []
        for process in processes:
            script_name = f"{self.get_job_prefix()}_{self.era}_{process}.sh"
            script_path = os.path.join(job_scripts_dir, script_name)

            command = self.generate_command(
                process, input_dir, output_dir, **kwargs
            )
            self.write_job_script(script_path, command)

            log_file = os.path.join(log_dir, f"{process}.log")
            err_file = os.path.join(log_dir, f"{process}.err")

            job_entries.append({
                'script': script_path,
                'log': log_file,
                'err': err_file
            })

        if not self.quiet:
            logger.info(f"Generated {len(job_entries)} job scripts")

        # Write submission script
        self.write_submission_script(submission_script, job_entries)

        # Submit
        return self.submit_jobs(submission_script, dry_run)

    def log_cluster_info(
        self,
        csv_path: str,
        cluster_id: str,
        log_dir: str,
        job_dir: str
    ) -> None:
        """
        Log cluster submission info to CSV file.

        Args:
            csv_path: Path to CSV log file
            cluster_id: HTCondor cluster ID
            log_dir: Directory containing job logs
            job_dir: Directory containing job scripts
        """
        with open(csv_path, 'a') as f:
            f.write(f"{cluster_id},{log_dir},{job_dir},0\n")


class BatchJobSubmitter(JobSubmitter):
    """
    Submitter for batch jobs that process multiple input files per process.

    Used when each process directory contains multiple ROOT files that
    need individual jobs (e.g., Stage 1 Object Selection).
    """

    def submit_batch(
        self,
        input_dir: str,
        output_dir: str,
        job_base_dir: str,
        dry_run: bool = False,
        skip_processes: Optional[List[str]] = None,
        **kwargs
    ) -> Optional[List[str]]:
        """
        Submit batch jobs for all files in all process directories.

        Args:
            input_dir: Input directory containing process subdirectories
            output_dir: Output directory path
            job_base_dir: Base directory for job files
            dry_run: If True, generate scripts but don't submit
            skip_processes: List of process names to skip
            **kwargs: Additional arguments passed to generate_command()

        Returns:
            List of cluster IDs if submitted, None if dry_run
        """
        if skip_processes is None:
            skip_processes = []

        # Create directory structure
        job_name = f"{self.get_job_prefix()}_{self.era}"
        if self.systematic:
            job_name += f"_{self.systematic}"

        job_scripts_dir, log_dir, submission_script = self.create_job_directory(
            job_base_dir, job_name
        )

        if not self.quiet:
            logger.info(f"Batch submission for: {input_dir}")
            logger.info(f"Output: {output_dir}")

        all_job_entries = []
        total_jobs = 0

        # Process each subdirectory
        for process in sorted(os.listdir(input_dir)):
            process_input = os.path.join(input_dir, process)
            if not os.path.isdir(process_input):
                continue

            if process in skip_processes:
                if not self.quiet:
                    logger.debug(f"Skipping: {process}")
                continue

            # Get all ROOT files
            root_files = [f for f in os.listdir(process_input) if f.endswith('.root')]
            if not root_files:
                continue

            # Create process output directory
            process_output = os.path.join(output_dir, process)
            process_log_dir = os.path.join(process_output, 'log')
            os.makedirs(process_output, exist_ok=True)
            os.makedirs(process_log_dir, exist_ok=True)

            # Create process job scripts subdirectory
            process_job_dir = os.path.join(job_scripts_dir, process)
            os.makedirs(process_job_dir, exist_ok=True)

            # Generate job for each file
            for idx, root_file in enumerate(root_files):
                script_name = f"{self.get_job_prefix()}_{self.era}_{process}_{idx}.sh"
                script_path = os.path.join(process_job_dir, script_name)

                command = self.generate_command(
                    process,
                    process_input + '/',
                    process_output + '/',
                    input_file=root_file,
                    **kwargs
                )
                self.write_job_script(script_path, command)

                log_file = os.path.join(process_log_dir, f"_{idx}.log")
                err_file = os.path.join(process_log_dir, f"_{idx}.err")

                all_job_entries.append({
                    'script': script_path,
                    'log': log_file,
                    'err': err_file
                })
                total_jobs += 1

            if not self.quiet:
                logger.info(f"  {process}: {len(root_files)} jobs")

        if not self.quiet:
            logger.info(f"Total jobs: {total_jobs}")

        # Write submission script
        self.write_submission_script(submission_script, all_job_entries)

        # Submit
        return self.submit_jobs(submission_script, dry_run)


def get_processes_from_directory(
    input_dir: str,
    skip_patterns: Optional[List[str]] = None
) -> List[str]:
    """
    Get list of processes from a directory.

    Args:
        input_dir: Directory containing process files/directories
        skip_patterns: List of patterns to skip

    Returns:
        List of process names
    """
    if skip_patterns is None:
        skip_patterns = []

    processes = []
    for entry in os.listdir(input_dir):
        # Skip if matches any pattern
        if any(pattern in entry for pattern in skip_patterns):
            continue

        # Check if it's a ROOT file or directory
        full_path = os.path.join(input_dir, entry)
        if entry.endswith('.root') or os.path.isdir(full_path):
            # Extract process name
            process = entry.replace('.root', '')
            processes.append(process)

    return sorted(processes)


def check_input_directory(
    entry: str,
    is_run3: bool = False
) -> bool:
    """
    Check if directory name is a valid input process.

    Filters out non-process directories like 'log', 'variableHists_*', etc.

    Args:
        entry: Directory name to check
        is_run3: Whether this is Run3 data

    Returns:
        True if valid process directory, False otherwise
    """
    # Skip common non-process directories
    skip_patterns = [
        'log', 'variableHists_', 'jobs_', 'workspace',
        '.root', '.txt', '.sh', '.py'
    ]

    for pattern in skip_patterns:
        if pattern in entry:
            return False

    return True
