import os
import subprocess
import argparse
import sys
import logging
from pathlib import Path


#!!! Update: Now supports both Python 2 and Python 3 (CMSSW_14_1_0_pre4 uses Python 3)

# Setup logging
logging.basicConfig(
    level=logging.INFO,
    format='[%(asctime)s] [%(levelname)s] %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S'
)
logger = logging.getLogger(__name__)


def ensure_dir(directory):
    """Safely create directory if it doesn't exist

    Args:
        directory: Path to directory to create

    Returns:
        Path object of the created/existing directory
    """
    dir_path = Path(directory)
    dir_path.mkdir(parents=True, exist_ok=True)
    logger.debug(f"Ensured directory exists: {directory}")
    return dir_path


def ensure_dir_with_fallback(target_dir, fallback_name, current_dir=None):
    """Create directory with automatic fallback to current directory on permission errors

    Args:
        target_dir: Desired directory path to create
        fallback_name: Name of directory to create in current dir if target fails
        current_dir: Current working directory (if None, uses os.getcwd())

    Returns:
        str: Path to the successfully created directory
    """
    if current_dir is None:
        current_dir = os.getcwd()

    try:
        ensure_dir(target_dir)
        logger.info(f"Output directory: {target_dir}")
        return target_dir
    except (PermissionError, OSError):
        logger.warning(f"Cannot write to {target_dir} (no permission), using current directory instead")
        fallback_dir = os.path.join(current_dir, fallback_name)
        ensure_dir(fallback_dir)
        logger.info(f"Output directory: {fallback_dir}")
        return fallback_dir


def ensure_writable_carddir(cardDir, current_dir=None):
    """Ensure we have a writable directory for processing datacards

    If cardDir has no write permission, creates a temp directory in current_dir,
    copies all .txt datacards there, and returns the writable directory path.

    Args:
        cardDir: Original card directory path (may be read-only)
        current_dir: Current working directory (if None, uses os.getcwd())

    Returns:
        str: Path to writable directory containing datacards (ends with /)
    """
    if current_dir is None:
        current_dir = os.getcwd()

    # Ensure cardDir ends with /
    if not cardDir.endswith('/'):
        cardDir += '/'

    # Check if cardDir has write permission
    if os.access(cardDir, os.W_OK):
        # Has write permission, use original directory
        return cardDir

    # No write permission, create temp working directory in current dir
    dirname = os.path.basename(cardDir.rstrip('/'))
    working_cardDir = os.path.join(current_dir, f'temp_{dirname}/')
    os.makedirs(working_cardDir, exist_ok=True)
    logger.warning(f"No write permission for {cardDir}, using working directory: {working_cardDir}")

    # Copy all .txt datacards to working directory
    import shutil
    for en in os.listdir(cardDir):
        if '.txt' in en:
            src = os.path.join(cardDir, en)
            dst = os.path.join(working_cardDir, en)
            shutil.copy2(src, dst)
            logger.info(f"Copied {en} to working directory")

    return working_cardDir


def get_workspace_file(cardDir, ifVLL=False, channel='1tau1l'):
    """Auto-detect and return the path to the workspace file

    Args:
        cardDir: Card directory path (should end with /)
        ifVLL: If True, use VLL-specific datacard naming (datacard_{channel}.root)
        channel: Analysis channel (e.g., '1tau1l', '1tau0l', '1tau2l') - used for VLL analysis

    Returns:
        str: Path to the workspace file, or None if not found
    """
    workspaceDir = cardDir + 'workspace/'

    if ifVLL:
        # Try channel-specific datacard first
        datacardFile = os.path.join(workspaceDir, f'datacard_{channel}.root')
        if not os.path.isfile(datacardFile):
            # If specified channel file doesn't exist, find what actually exists
            logger.warning(f"Specified datacard_{channel}.root not found, searching for available workspace files...")
            available_workspaces = [f for f in os.listdir(workspaceDir) if f.endswith('.root') and f.startswith('datacard_')]
            if available_workspaces:
                datacardFile = os.path.join(workspaceDir, available_workspaces[0])
                detected_channel = available_workspaces[0].replace('datacard_', '').replace('.root', '')
                logger.info(f"Auto-detected workspace: {available_workspaces[0]} (channel: {detected_channel})")
            else:
                logger.error(f"No workspace files found in {workspaceDir}")
                return None
        else:
            logger.info(f"Using VLL datacard: datacard_{channel}.root")
    else:
        datacardFile = os.path.join(workspaceDir, 'datacard.root')
        logger.info(f"Using tttt datacard: datacard.root")

    return datacardFile


def main():
    """Main entry point for running complete Combine analysis workflow"""
    parser = argparse.ArgumentParser(
        description="Run complete CMS Combine statistical analysis workflow for four-top search",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Blinded analysis (expected limits only)
  python runCombineAll.py --cardDir combinationV18/run2_1tau1l_v4/ --ifBlind

  # Unblinded analysis (observed data)
  python runCombineAll.py --cardDir combinationV18/run2_1tau1l_v4_unblind/ --no-blind

  # Run only specific steps
  python runCombineAll.py --cardDir combinationV18/run2_1tau1l_v4/ --steps workspace limits

  # VLL analysis (Vector-Like Lepton search)
  python runCombineAll.py --cardDir combinationV10/run2_1tau1l_VLLm600/ --no-blind --ifVLL --channel 1tau1l

  # VLL analysis with specific steps
  python runCombineAll.py --cardDir combinationV10/run2_1tau0l_VLLm650/ --no-blind --ifVLL --channel 1tau0l --steps gof
        """
    )
    parser.add_argument('--cardDir', type=str, required=True,
                        help='Directory containing datacards (must end with /)')
    parser.add_argument('--ifBlind', '--blind', dest='ifBlind', action='store_true',
                        help='Run blinded analysis (expected limits only)')
    parser.add_argument('--no-blind', '--ifBlind=False', dest='ifBlind', action='store_false',
                        help='Run unblinded analysis (use observed data)')
    parser.add_argument('--steps', nargs='+',
                        choices=['workspace', 'limits', 'significance', 'impacts', 'postfit', 'signal_strength', 'gof'],
                        help='Run only specific steps (default: all)')
    parser.add_argument('--skip-impacts', action='store_true',
                        help='Skip impact calculation (can be time-consuming)')
    parser.add_argument('--ifVLL', '--VLL', dest='ifVLL', action='store_true',
                        help='Run VLL (Vector-Like Lepton) analysis instead of tttt analysis')
    parser.add_argument('--channel', type=str, default='1tau1l',
                        help='Analysis channel for VLL (e.g., 1tau1l, 1tau0l, 1tau2l). Only used with --ifVLL')
    parser.set_defaults(ifBlind=False, ifVLL=False)  # Default to unblinded for backward compatibility

    args = parser.parse_args()

    # Validate and normalize cardDir path
    cardDir = args.cardDir
    if not cardDir.endswith('/'):
        cardDir += '/'

    if not os.path.exists(cardDir):
        logger.error(f"Card directory does not exist: {cardDir}")
        sys.exit(1)

    ifBlind = args.ifBlind
    ifVLL = args.ifVLL
    channel = args.channel

    logger.info("="*80)
    analysis_type = "VLL Search" if ifVLL else "Four-Top Search"
    logger.info(f"CMS Combine Analysis Workflow - {analysis_type}")
    logger.info("="*80)
    logger.info(f"Card directory: {cardDir}")
    logger.info(f"Analysis mode: {'BLINDED (expected)' if ifBlind else 'UNBLINDED (observed)'}")
    if ifVLL:
        logger.info(f"VLL analysis channel: {channel}")
    logger.info("="*80)


    # Determine which steps to run
    steps = args.steps if args.steps else ['workspace', 'limits', 'significance', 'impacts', 'postfit', 'signal_strength', 'gof']

    try:
        # Step 1: Convert datacards to workspaces
        # Track the working directory (may differ from cardDir if permissions required fallback)
        working_cardDir = cardDir

        if 'workspace' in steps:
            logger.info("\n" + "="*80)
            logger.info("STEP 1: Converting datacards to RooWorkspace")
            logger.info("="*80)
            working_cardDir = cardToWorkspaces(cardDir)

        # Step 2: Calculate limits
        if 'limits' in steps:
            logger.info("\n" + "="*80)
            logger.info("STEP 2: Calculating expected/observed limits")
            logger.info("="*80)
            runCombineSig(working_cardDir, True, ifBlind, ifVLL, channel)  #!Step 3 - Asymptotic limits

        # Step 3: Calculate significance
        if 'significance' in steps:
            logger.info("\n" + "="*80)
            logger.info("STEP 3: Calculating significance")
            logger.info("="*80)
            runCombineSig(working_cardDir, False, ifBlind, ifVLL, channel)

        # Step 4: Impact plots (time-consuming, can be skipped)
        if 'impacts' in steps and not args.skip_impacts:
            logger.info("\n" + "="*80)
            logger.info("STEP 4: Calculating systematic impacts (this may take a while...)")
            logger.info("="*80)
            runImpact(working_cardDir, ifBlind, ifVLL, channel)
            # For VLL analysis, also run B-only constrained impacts
            if ifVLL:
                logger.info("\n" + "="*80)
                logger.info("STEP 4b: Running B-only constrained impacts (VLL)")
                logger.info("="*80)
                runImpactSnapshot(working_cardDir, ifVLL, channel)

        # Step 5: Post-fit plots
        if 'postfit' in steps:
            logger.info("\n" + "="*80)
            logger.info("STEP 5: Generating post-fit plots")
            logger.info("="*80)
            runPostFitPlots(working_cardDir, ifVLL, channel)  #!Step 2 of unblinding

        # Step 6: Signal strength measurement
        if 'signal_strength' in steps:
            logger.info("\n" + "="*80)
            logger.info("STEP 6: Measuring signal strength")
            logger.info("="*80)
            measureSignalStrength(working_cardDir, ifVLL, channel)  #!Step 3 of unblinding

        # Step 7: Goodness of fit
        if 'gof' in steps:
            logger.info("\n" + "="*80)
            logger.info("STEP 7: Goodness-of-fit test")
            logger.info("="*80)
            goodnessOfFit(working_cardDir, ifVLL, channel)  #!Step 4 of unblinding

        logger.info("\n" + "="*80)
        logger.info("✓ Analysis workflow completed successfully!")
        logger.info("="*80)

    except Exception as e:
        logger.error(f"Analysis workflow failed: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)


def goodnessOfFit(cardDir, ifVLL=False, channel='1tau1l'):
    '''
        Perform goodness-of-fit test to assess the quality of the fit
        Reference:
        https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/latest/part3/commonstatsmethods/?h=good#goodness-of-fit-tests

        Args:
            cardDir: Directory containing datacards and workspaces
            ifVLL: If True, use VLL-specific datacard naming (datacard_{channel}.root)
            channel: Analysis channel (e.g., '1tau1l', '1tau0l', '1tau2l') - used for VLL analysis
    '''
    # Auto-detect which workspace file actually exists (important when workspace step was run)
    datacardFile = get_workspace_file(cardDir, ifVLL, channel)
    if datacardFile is None:
        return

    outFolder = cardDir + 'combineResults/'
    goodnessOfFitDir = outFolder + 'goodnessOfFit/'

    original_dir = os.getcwd()

    # Try to create directory in cardDir; if no write permission, use current dir
    goodnessOfFitDir = ensure_dir_with_fallback(goodnessOfFitDir, 'goodnessOfFit', original_dir)

    #cd goodnessOfFitDir
    os.chdir(goodnessOfFitDir) #!don't need to cd in run_runCombineAll.sh anymore
    logger.info(f"Working directory: {goodnessOfFitDir}")

    try:
        # VLL-specific options: freeze r=0 for background-only hypothesis
        vll_opts = ' --setParameters r=0 --freezeParameters r' if ifVLL else ''

        # Run goodness-of-fit test on observed data
        gofObservedCommand = 'combine -M GoodnessOfFit {} --algo saturated -n .observed{}'.format(datacardFile, vll_opts)
        runCommand(gofObservedCommand)

        # Generate toys for expected distribution
        # OPTION 1: Single file approach (faster but can crash with large N)
        gofToysCommand = 'combine -M GoodnessOfFit {} --algo saturated -t 100{}'.format(datacardFile, vll_opts)
        plot1 = 'combineTool.py -M CollectGoodnessOfFit --input higgsCombine.observed.GoodnessOfFit.mH120.root higgsCombineTest.GoodnessOfFit.mH120.123456.root -o gof.json'
        # OPTION 2: Separate files approach (more robust, recommended for large N)
        # Use combineTool to generate toys in separate files (more robust against crashes)
        # --seed 1:100:1 means: start seed 1, end seed 100, step 1 = 100 toys in separate files
        # gofToysCommand = 'combineTool.py -M GoodnessOfFit {} --algo saturated -t 1 --seed 1:100:1 -n .gof_toys'.format(datacardFile)
        # plot1 = 'combineTool.py -M CollectGoodnessOfFit --input higgsCombine.observed.GoodnessOfFit.mH120.root higgsCombine.gof_toys.GoodnessOfFit.mH120.*.root -o gof.json'
        runCommand(gofToysCommand)

        #plot GOF results
        # Collect all toy files using wildcards
        runCommand(plot1)
        plotGofCommand = 'plotGof.py gof.json --statistic saturated --mass 120.0 -o gof_plot'
        runCommand(plotGofCommand)

        print('Goodness-of-fit results here: ', goodnessOfFitDir)
        print('\n' + '='*60)
        print('Goodness-of-Fit Test Results:')
        print('='*60)

    finally:
        os.chdir(original_dir)
        logger.debug(f"Returned to directory: {original_dir}")


def measureSignalStrength(cardDir, ifVLL=False, channel='1tau1l'):
    '''
        Measure signal strength using MultiDimFit method
        Reference: https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/latest/part5/longexercise/#e-signal-strength-measurement-and-uncertainty-breakdown

        Args:
            cardDir: Directory containing datacards and workspaces
            ifVLL: If True, use VLL-specific datacard naming (datacard_{channel}.root)
            channel: Analysis channel (e.g., '1tau1l', '1tau0l', '1tau2l') - used for VLL analysis
    '''
    # Auto-detect which workspace file actually exists (important when workspace step was run)
    datacardFile = get_workspace_file(cardDir, ifVLL, channel)
    if datacardFile is None:
        return

    outFolder = cardDir + 'combineResults/'
    signalStrengthDir = outFolder + 'signalStrength/'

    #cd to output directory so combine saves files there
    original_dir = os.getcwd()

    # Try to create directory in cardDir; if no write permission, use current dir
    signalStrengthDir = ensure_dir_with_fallback(signalStrengthDir, 'signalStrength', original_dir)
    os.chdir(signalStrengthDir)  #!don't need to cd in run_runCombineAll.sh anymore
    logger.info(f"Working directory: {signalStrengthDir}")

    try:
        # Likelihood scan
        scanCommand = 'combine -M MultiDimFit {} --algo grid --points 100 --rMin 0 --rMax 20 --redefineSignalPOIs r -n .scan'.format(datacardFile)
        runCommand(scanCommand)

        # Fit with only statistical uncertainty (freeze all nuisance parameters)
        fitSnapCommand = f'combine -M MultiDimFit {datacardFile} -n .snapshot --rMin 0 --rMax 20 --saveWorkspace'
        runCommand(fitSnapCommand)
        freezeAllCommand = 'combine -M MultiDimFit higgsCombine.snapshot.MultiDimFit.mH120.root -n .freezeAll --rMin 0 --rMax 20 --algo grid --points 100 --freezeParameters allConstrainedNuisances --snapshotName MultiDimFit'
        runCommand(freezeAllCommand)
        
        # python plot1DScan.py higgsCombine.part3E.MultiDimFit.mH200.root --others 'higgsCombine.part3E.freezeAll.MultiDimFit.mH200.root:FreezeAll:2' -o freeze_second_attempt --breakdown Syst,Stat
        # fitStatCommand = 'combine -M MultiDimFit {} --algo singles --redefineSignalPOIs r --freezeParameters allConstrainedNuisances --rMin 0 --rMax 10 -n .stat'.format(datacardFile)
        # runCommand(fitStatCommand)
        # Plot likelihood scan (plot1DScan.py is in PATH after cmsenv)
        # Overlay stat-only scan to show total vs statistical uncertainty, systematic is derived
        plotScanCommand = "plot1DScan.py higgsCombine.scan.MultiDimFit.mH120.root --others 'higgsCombine.freezeAll.MultiDimFit.mH120.root:StatOnly:2' -o scan_plot --breakdown Syst,Stat"
        runCommand(plotScanCommand)

        # Report uncertainties
        print('Signal strength results here: ', signalStrengthDir)
        print('\n' + '='*60)
        print('Signal Strength and Uncertainty Breakdown:')
        print('='*60)

        # Extract values from ROOT files using combine's output format
        extractTotal = 'cd {} && combine -M MultiDimFit higgsCombineTest.MultiDimFit.mH120.root --algo singles --redefineSignalPOIs r --saveWorkspace 2>&1 | grep "r :"'.format(signalStrengthDir)
        extractStat = 'cd {} && combine -M MultiDimFit higgsCombine.stat.MultiDimFit.mH120.root --algo singles --redefineSignalPOIs r --saveWorkspace 2>&1 | grep "r :"'.format(signalStrengthDir)

        print('\nRunning uncertainty extraction...')
        runCommand(extractTotal)
        runCommand(extractStat)

        print('\nTo extract the values manually, run:')
        print('cd {} && combine -M MultiDimFit higgsCombineTest.MultiDimFit.mH120.root --algo singles --redefineSignalPOIs r --saveWorkspace 2>&1 | grep "r :"'.format(signalStrengthDir))
        print('cd {} && combine -M MultiDimFit higgsCombine.stat.MultiDimFit.mH120.root --algo singles --redefineSignalPOIs r --saveWorkspace 2>&1 | grep "r :"'.format(signalStrengthDir))
        print('\nSystematic uncertainty = sqrt(total_unc^2 - stat_unc^2)')
        print('='*60)

    finally:
        os.chdir(original_dir)
        logger.debug(f"Returned to directory: {original_dir}")


def runPostFitPlots(cardDir, ifVLL=False, channel='1tau1l'):
    '''Using CMSSW14_1_0_pre4 to run postfit plots

    Args:
        cardDir: Directory containing datacards and workspaces
        ifVLL: If True, use VLL-specific datacard naming
        channel: Analysis channel (e.g., '1tau1l', '1tau0l', '1tau2l')
    '''
    original_dir = os.getcwd()

    datacardFile = get_workspace_file(cardDir, ifVLL, channel)
    # Convert to absolute path before cd'ing (workspace path is relative to original dir)
    datacardFile = os.path.abspath(datacardFile)

    outFolder = cardDir + 'combineResults/'
    postfitDir = outFolder+ 'postfitPlots/'
    # Try to create directory in cardDir; if no write permission, use current dir
    postfitDir = ensure_dir_with_fallback(postfitDir, 'postfitPlots', original_dir)
    os.chdir(postfitDir)  #!don't need to cd in run_runCombineAll.sh anymore
    logger.info(f"Working directory: {postfitDir}")

    fitCommand = 'combine -M FitDiagnostics {}  --rMin 0 --rMax 20 --saveShapes --saveWithUncertainties --cminDefaultMinimizerStrategy 0'.format(datacardFile) #generate fitDiagnostics_postfit.root
    runCommand(fitCommand)
    #[WARNING]: Unable to determine uncertainties on all fit parameters in b-only fit. The option --saveWithUncertainties will be ignored as it would lead to incorrect results --> This means the covariance matrix calculated in FitDiagnostics was not correct.
    # plotCommand = 'python diffNuisances.py fitDiagnostics_postfit.root --all --output-file {}/nuisancePostFit.txt '.format(postfitDir)
    # plotCommand2 = 'python plotNuisances.py -i {}/nuisancePostFit.txt -o {}/nuisancePostFit '.format(postfitDir, postfitDir)
    # mv = 'mv fitDiagnostics_postfit.root nuisancesPostFit.pdf combine_logger.out {}'.format(postfitDir)
    # runCommand(plotCommand)
    # runCommand(plotCommand2)
    # print('postfitPlots here: ', postfitDir+'nuisancePostFit.pdf')

    os.chdir(original_dir)
    logger.debug(f"Returned to directory: {original_dir}")

    
    
def runImpact(cardDir, ifBlind=True, ifVLL=False, channel='1tau1l'):
    '''Generate systematic impact plots showing which uncertainties affect the measurement most

    Args:
        cardDir: Directory containing datacards and workspaces
        ifBlind: If True, run blinded analysis
        ifVLL: If True, run VLL analysis with r=0 frozen
        channel: Analysis channel (e.g., '1tau1l', '1tau0l', '1tau2l')
    '''
    original_dir = os.getcwd()

    # VLL-specific options: freeze r=0 and allow negative r for impact fits
    vll_opts = ' --rMin -1 --setParameters r=0 --freezeParameters r' if ifVLL else ''

    for ifile in os.listdir(cardDir+'workspace/'):
        if ifile.find('root')>0:
            logger.info(f'Processing workspace: {ifile}')
            outFolder = cardDir + 'combineResults/'
            wf = cardDir + 'workspace/' + ifile

            impacDir = outFolder+ 'impactResult/'

            # Try to create directory in cardDir; if no write permission, use current dir
            impacDir = ensure_dir_with_fallback(impacDir, 'impactResult', original_dir)

            #cd to output directory so combine saves files there
            os.chdir(impacDir)  #!don't need to cd in run_runCombineAll.sh anymore
            logger.info(f"Working directory: {impacDir}")

            step1 = 'combineTool.py -M Impacts -d {} -m 125 --doInitialFit --robustFit 1{}'.format(wf, vll_opts)
            step2 = 'combineTool.py -M Impacts -d {} -m 125 --robustFit 1 --doFits --parallel 8 --job-mode "interactive"{}'.format(wf, vll_opts)
            step3 = 'combineTool.py -M Impacts -d {} -m 125 -robustFit 1 -o {}/impacts.json{}'.format(wf, impacDir, vll_opts)
            step4 = 'plotImpacts.py -i {}impacts.json -o impacts'.format(impacDir)
            runCommand(step1)
            runCommand(step2)
            runCommand(step3)
            runCommand(step4)
            # Note: Files are already in impacDir since we cd'd there
            # This mv handles case when combine writes to a different location
            mv = f'mv higgsCombine_paramFit*.root impacts.pdf combine_logger.out {impacDir}/ 2>/dev/null || true'
            runCommand(mv, check_returncode=False)
            logger.info(f'Impact plot saved: {impacDir}impacts.pdf')

    os.chdir(original_dir)
    logger.debug(f"Returned to directory: {original_dir}")


def runImpactSnapshot(cardDir, ifVLL=False, channel='1tau1l'):
    """Generate impact plots using B-only constrained snapshot (for VLL analysis)

    This creates a snapshot workspace with r=0 frozen, then runs impacts using
    the snapshot. This is the recommended approach for VLL/BSM analyses.

    Args:
        cardDir: Directory containing datacards and workspaces
        ifVLL: If True, use VLL-specific datacard naming
        channel: Analysis channel (e.g., '1tau1l', '1tau0l', '1tau2l')
    """
    original_dir = os.getcwd()
    workspaceDir = os.path.join(cardDir, 'workspace/')
    outFolder = os.path.join(cardDir, 'combineResults/')

    # Ensure output directory exists
    ensure_dir(outFolder)

    for ifile in os.listdir(workspaceDir):
        if ifile.endswith('.root') and 'higgsCombine' not in ifile:
            iname = ifile.split('.root')[0]
            original_wf = os.path.join(workspaceDir, ifile)

            impacDir = os.path.join(outFolder, 'impactResult_' + iname + '/')

            # Try to create directory; if no write permission, use current dir
            impacDir = ensure_dir_with_fallback(impacDir, 'impactResult_' + iname, original_dir)

            os.chdir(impacDir)
            logger.info(f"Working directory: {impacDir}")
            logger.info(f"Processing: {iname} (B-only constrained snapshot)")

            snapshot_name = "MultiDimFit"

            # Step 0: Create snapshot with r=0 frozen
            step0_cmd = (
                f"combine -M MultiDimFit {original_wf} -n .SnapshotBOnly "
                f"--saveWorkspace "
                f"--setParameters r=0 --freezeParameters r "
                f"--rMin -20 --rMax 20 -m 125"
            )
            runCommand(step0_cmd)

            snapshot_file = "higgsCombine.SnapshotBOnly.MultiDimFit.mH125.root"

            if not os.path.exists(snapshot_file):
                logger.error("Snapshot generation failed!")
                os.chdir(original_dir)
                continue

            target_snapshot = os.path.join(impacDir, snapshot_file)
            os.rename(snapshot_file, target_snapshot)

            # Step 1: Initial fit using snapshot
            step1 = (
                f"combineTool.py -M Impacts -d {target_snapshot} -m 125 "
                f"--snapshotName {snapshot_name} "
                f"--doInitialFit --robustFit 1 --rMin -10 --rMax 10"
            )

            # Step 2: Run fits for each nuisance parameter
            step2 = (
                f"combineTool.py -M Impacts -d {target_snapshot} -m 125 "
                f"--snapshotName {snapshot_name} "
                f"--robustFit 1 --doFits --rMin -10 --rMax 10 --parallel 20"
            )

            # Step 3: Collect impacts into JSON
            json_file = os.path.join(impacDir, 'impacts.json')
            step3 = (
                f"combineTool.py -M Impacts -d {target_snapshot} -m 125 "
                f"--snapshotName {snapshot_name} "
                f"--robustFit 1 -o {json_file} --rMin -10 --rMax 10"
            )

            # Step 4: Plot impacts
            pdf_file = os.path.join(impacDir, 'impacts')
            step4 = f"plotImpacts.py -i {json_file} -o {pdf_file}"

            runCommand(step1)
            runCommand(step2)
            runCommand(step3)
            runCommand(step4)

            logger.info(f"Impact Plot (B-only constrained) saved to: {pdf_file}.pdf")

            # Cleanup: move intermediate files to output directory
            cleanup = f"mv higgsCombine_paramFit*.root {impacDir}/ 2>/dev/null || true"
            runCommand(cleanup, check_returncode=False)

    os.chdir(original_dir)
    logger.debug(f"Returned to directory: {original_dir}")


def runCommand(com, check_returncode=True):
    """Execute a shell command with proper error handling

    Args:
        com: Command string to execute
        check_returncode: If True, raise exception on non-zero return code

    Returns:
        Tuple of (stdout, stderr, returncode)

    Raises:
        subprocess.CalledProcessError: If command fails and check_returncode=True
    """
    logger.info(f"Running: {com}")
    # Set environment to ignore user site-packages, use only CMSSW packages
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

        # Log output
        if stdout:
            logger.info(f"stdout: {stdout}")
        if stderr:
            # Some combine tools print to stderr even on success
            if returncode != 0:
                logger.error(f"stderr: {stderr}")
            else:
                print(stderr)  # Print stderr directly for successful commands

        if check_returncode and returncode != 0:
            logger.error(f"Command failed with return code {returncode}: {com}")
            raise subprocess.CalledProcessError(returncode, com, output=stdout, stderr=stderr)

        logger.info(f"✓ Command completed (exit code: {returncode})")
        return stdout, stderr, returncode

    except Exception as e:
        logger.error(f"Failed to execute command: {com}")
        logger.error(f"Error: {e}")
        if check_returncode:
            raise
        return None, None, -1
    

def copyCombineResultsToDir( cardDir ):
    """Copy combine output ROOT files to results directory"""
    resultsDir = cardDir+ 'combineResults/'
    current_dir = os.getcwd()

    # Try to create directory in cardDir; if no write permission, use current dir
    resultsDir = ensure_dir_with_fallback(resultsDir, 'combineResults', current_dir)

    logger.info(f'Copying results to: {resultsDir}')
    # command = 'mv higgsCombineTMVApp*root {}'.format( resultsDir  )
    command = 'mv higgsCombine*root {}'.format( resultsDir  )
    process = subprocess.Popen( command, shell=True )
    out = process.communicate()


def runCombineSig( cardDir, isLimit, ifBlind=True, ifVLL=False, channel='1tau1l' ):
    """Run combine for limits (isLimit=True) or significance (isLimit=False)

    Args:
        cardDir: Directory containing datacards and workspaces
        isLimit: If True, calculate limits; if False, calculate significance
        ifBlind: If True, run blinded analysis (expected); if False, use observed data
        ifVLL: If True, running VLL analysis (for logging purposes)
        channel: Analysis channel (e.g., '1tau1l', '1tau0l', '1tau2l') - used for VLL logging
    """
    original_dir = os.getcwd()

    # Auto-detect which workspace file actually exists (important when workspace step was run)
    datacardFile = get_workspace_file(cardDir, ifVLL, channel)
    if datacardFile is None:
        return

    workspaceDir = cardDir + 'workspace/'
    resultDir = workspaceDir+'results/'

    # Try to create results directory in workspace; if no write permission, create in current dir
    resultDir = ensure_dir_with_fallback(resultDir, 'results', original_dir)

    # Try to cd to card directory; if no permission, stay in current directory
    try:
        os.chdir(cardDir)  #!don't need to cd in run_runCombineAll.sh anymore
        logger.info(f"Working directory: {cardDir}")
        workdir = cardDir
    except (PermissionError, OSError):
        logger.warning(f"Cannot write to {cardDir} (no permission), staying in current directory")
        # Stay in original directory - combine outputs will be created here
        workdir = original_dir
        logger.info(f"Working directory: {workdir}")

    analysis_type = "VLL" if ifVLL else "tttt"
    calc_type = "Limits" if isLimit else "Significance"
    blind_mode = "blinded (expected)" if ifBlind else "unblinded (observed)"
    logger.info(f"Running {analysis_type} {calc_type} calculation - {blind_mode}")
    if ifVLL:
        logger.info(f"VLL channel: {channel}")

    # Generate command name based on datacard filename
    iname = '_' + datacardFile.split('/')[-1].split('.root')[0]

    expectSignal = 0 if ifVLL else 1
    # VLL-specific options for significance: freeze r=0 for background-only hypothesis
    # Note: These options have no effect on AsymptoticLimits (scans r regardless of initial params)
    vll_opts = ' --setParameters r=0 --freezeParameters r' if ifVLL else ''

    if isLimit:
        if ifBlind:
            # significanceCommand = 'combine -M AsymptoticLimits {rootFile} --run blind --name {name}'.format( rootFile=datacardFile, name=iname )
            significanceCommand = 'combine -M AsymptoticLimits {rootFile} --run blind -t -{expectSignal} --name {name}'.format( rootFile=datacardFile, name=iname, expectSignal=expectSignal )
        else:
            # Note: VLL options (--setParameters r=0 --freezeParameters r) have no effect on AsymptoticLimits
            # because this method scans r from rMin to rMax regardless of initial parameters
            significanceCommand = 'combine -M AsymptoticLimits {rootFile} --name {name}'.format( rootFile=datacardFile, name=iname )
    else:
        # Significance calculation
        if ifBlind:
            # KEY DIFFERENCE: VLL uses --expectSignal=0 (background-only), tttt uses --expectSignal=1
            significanceCommand = 'combine -M Significance {rootFile} -t -1 --expectSignal={signal} --name {name}'.format(
                rootFile=datacardFile, signal=expectSignal, name=iname )
        else:
            significanceCommand = 'combine -M Significance {rootFile} --name {name} --plot significance{vll}'.format( rootFile=datacardFile, name=iname, vll=vll_opts )

    runCommand(significanceCommand)
    os.chdir(original_dir)
    logger.debug(f"Returned to directory: {original_dir}")


def cardToWorkspaces( cardDir):
    """Convert text datacards to RooWorkspace ROOT files"""
    logger.info('Converting datacards to workspaces...')
    original_dir = os.getcwd()
    workspace_count = 0

    # Ensure we have a writable directory to work in
    working_cardDir = ensure_writable_carddir(cardDir, original_dir)

    #cd to working card directory for workspace creation
    os.chdir(working_cardDir)  #!don't need to cd in run_runCombineAll.sh anymore
    logger.info(f"Working directory: {working_cardDir}")

    for en in os.listdir( working_cardDir ):
        if not '.txt' in en: continue
        idatacard = en
        idatacard = working_cardDir +  idatacard
        if os.path.isfile( idatacard ):
            logger.info(f'Processing datacard: {idatacard}')
            iworkspaceName = en[:]
            iworkspaceName = iworkspaceName.replace('.txt', '.root' )
            logger.info(f'Workspace name: {iworkspaceName}')

            # Create workspace directory in the working card directory (which is already writable)
            iworkspaceDir = working_cardDir + 'workspace/'
            ensure_dir(iworkspaceDir)
            logger.info(f'Output directory: {iworkspaceDir}')
    #
            iworkspace = iworkspaceDir + iworkspaceName
            command = 'text2workspace.py {da} -o {work}'.format( da=idatacard, work=iworkspace )
            logger.info(f'Running: {command}')

            env = os.environ.copy()
            env['PYTHONNOUSERSITE'] = '1'
            iprocess = subprocess.Popen( [command], shell=True, env=env )
            output = iprocess.communicate()[0]
            # output = iprocess.communicate()
            if output:
                logger.debug(output)
            workspace_count += 1

    logger.info(f'✓ Workspace transformation complete! Created {workspace_count} workspace(s)\n')

    os.chdir(original_dir)
    logger.debug(f"Returned to directory: {original_dir}")

    # Return the working card directory so subsequent steps know where workspaces are located
    return working_cardDir



if __name__ == '__main__':
    main()
