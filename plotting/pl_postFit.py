#!/usr/bin/env python3
"""
pl_postFit.py - Generate pre-fit and post-fit data/MC comparison plots

This script can generate:
1. Pre-fit plots: From template ROOT files (before combine fit)
2. Post-fit plots: From fitDiagnostics ROOT files (after combine fit)

Usage:
    # Post-fit plots only (default, from fitDiagnostics file)
    python3 pl_postFit.py --fit-file /path/to/fitDiagnosticsTest.root

    # Pre-fit plots only (from template files)
    python3 pl_postFit.py --plot-type prefit --config config/analysis_config.yaml

    # Both pre-fit and post-fit plots
    python3 pl_postFit.py --plot-type both --config config/analysis_config.yaml

    # Use config file for paths
    python3 pl_postFit.py --config ../../config/analysis_config.yaml --plot-type postfit
"""

import ROOT
import argparse
import os
import sys

# Add parent directory to path for imports
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import usefulFunc as uf
import pl as plt

# Try to import workflow_utils for config support
try:
    from workflow_utils import load_config, build_hist_path, build_combine_path, get_channel, get_eras
    WORKFLOW_UTILS_AVAILABLE = True
except ImportError:
    WORKFLOW_UTILS_AVAILABLE = False


def parse_args():
    """Parse command line arguments."""
    parser = argparse.ArgumentParser(
        description='Generate pre-fit and/or post-fit data/MC comparison plots',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )

    parser.add_argument(
        '--config', '-c',
        type=str,
        help='Path to YAML config file for path building'
    )
    parser.add_argument(
        '--fit-file', '-f',
        type=str,
        help='Path to fitDiagnostics ROOT file (for post-fit plots)'
    )
    parser.add_argument(
        '--plot-type', '-t',
        type=str,
        choices=['prefit', 'postfit', 'both'],
        default='postfit',
        help='Type of plots to generate (default: postfit)'
    )
    parser.add_argument(
        '--channel',
        type=str,
        help='Analysis channel (e.g., 1tau0l, 1tau1l). Auto-detected from config if not specified.'
    )
    parser.add_argument(
        '--era',
        type=str,
        help='Single era to process (default: all eras from config, then combine to Run2)'
    )
    parser.add_argument(
        '--output-dir', '-o',
        type=str,
        help='Output directory for plots (default: auto-generated based on input)'
    )
    parser.add_argument(
        '--quiet', '-q',
        action='store_true',
        help='Suppress non-essential output'
    )
    parser.add_argument(
        '--no-logy',
        action='store_true',
        help='Use linear scale instead of log scale'
    )
    parser.add_argument(
        '--blind',
        action='store_true',
        help='Blind signal region data'
    )
    parser.add_argument(
        '--vll',
        type=str,
        nargs='?',
        const='VLLm700',
        default='',
        help='Include VLL signal in plots. Optionally specify mass point (default: VLLm700)'
    )

    return parser.parse_args()


def main():
    """Main entry point with argument parsing."""
    args = parse_args()

    # Determine what to run based on arguments
    if args.plot_type in ('postfit', 'both'):
        if args.fit_file:
            run_postfit_plots(args.fit_file, args)
        elif args.config and WORKFLOW_UTILS_AVAILABLE:
            # Auto-detect fit file from config
            config = load_config(args.config)
            fit_file = get_fit_file_from_config(config)
            if fit_file and os.path.exists(fit_file):
                run_postfit_plots(fit_file, args)
            else:
                print(f"Warning: Could not find fitDiagnostics file. Run Stage 4.5 first.")
                if args.plot_type == 'postfit':
                    return 1
        else:
            # Fall back to default hardcoded path
            run_postfit_plots_legacy()

    if args.plot_type in ('prefit', 'both'):
        if args.config and WORKFLOW_UTILS_AVAILABLE:
            config = load_config(args.config)
            run_prefit_plots(config, args)
        else:
            print("Pre-fit plots require --config and workflow_utils. Install PyYAML.")
            return 1

    return 0


def get_fit_file_from_config(config):
    """Get fitDiagnostics file path from config."""
    combination = config.get('combination', {})
    comb_version = combination.get('version', 'combinationV20')
    channel = get_channel(config)
    card_subdir = combination.get('card_dir', f'run2_{channel}_v4_unblind')

    # Standard location for fitDiagnostics
    base_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    fit_file = os.path.join(
        base_path, 'hua', 'combine', comb_version, card_subdir,
        'combineResults', 'postfitPlots', 'fitDiagnosticsTest.root'
    )
    return fit_file


def run_prefit_plots(config, args):
    """
    Generate pre-fit plots from template ROOT files.

    These are the data/MC comparison plots BEFORE the combine fit,
    using the templates created in Stage 4.2/4.2.5.
    """
    print("\n" + "="*80)
    print("Generating PRE-FIT plots from template files")
    print("="*80)

    channel = args.channel or get_channel(config)
    eras = [args.era] if args.era else get_eras(config)

    # Plotting options
    variable = 'BDT'
    ifFakeTau = True
    ifVLL = getattr(args, 'vll', '')  # VLL process name or empty string
    ifMCFTau = False
    ifDoSystmatic = False
    ifPostfit = False  # This is pre-fit
    ifStackSignal = False if ifVLL else True  # Don't stack VLL signal - show as overlay
    ifLogy = not args.no_logy
    ifPrintSB = True
    ifBlind = args.blind

    # Get process list
    sumProList = plt.getSumList(channel, ifFakeTau, ifVLL, ifMCFTau, True)

    # Process each era
    for era in eras:
        print(f"\nProcessing pre-fit for era: {era}")

        # Build template path
        template_path = get_template_path_from_config(config, era)
        if not template_path or not os.path.exists(template_path):
            print(f"  Warning: Template not found: {template_path}")
            continue

        print(f"  Template: {template_path}")

        # Determine output directory
        if args.output_dir:
            plotDir = args.output_dir
        else:
            plotDir = os.path.dirname(template_path) + '/prefitPlots/'
        uf.checkMakeDir(plotDir)

        # Load histograms from template
        iRegion = f'{channel}SR'  # e.g., 1tau0lSR
        sumProcess = load_prefit_histograms(template_path, iRegion, sumProList, variable)

        if not sumProcess:
            print(f"  Warning: No histograms loaded for {era}")
            continue

        # Get systematic dictionary
        sumProSys = plt.getSysDicPL(sumProList, ifDoSystmatic, channel, era, True)

        # Generate plot
        plotName = f'{variable}_{iRegion}_prefit_{era}'
        plt.makeStackPlotNew(sumProcess, sumProList, variable, iRegion, plotDir, False,
                           plotName, era, True, 100, ifStackSignal, ifLogy, ifPrintSB,
                           ifVLL, {}, ifDoSystmatic, ifBlind, ifPostfit)

        print(f"  Saved: {plotDir}{plotName}.png")

    # Create Run2 combination if multiple eras
    if len(eras) > 1:
        print(f"\nCreating Run2 pre-fit combination")
        # This would require loading and combining histograms from all eras
        # Similar to post-fit Run2 combination logic


def get_template_path_from_config(config, era):
    """Build template file path from config for a given era."""
    paths = config.get('paths', {})
    base = paths.get('base', '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA')
    out_version = paths.get('out_version', 'v1baselineHadroBtagWeightAdded')
    in_version = paths.get('in_version', 'v94HadroPreJetVetoHemOnly')
    hist_version = paths.get('hist_version', 'v9BDT1tau0l')
    channel = get_channel(config)

    # Check if smoothed template should be used
    smoothed = config.get('smoothing', {}).get('enabled', False)
    suffix = '_smoothed' if smoothed else ''

    template_name = f'templatesForCombine{channel}_new_notMCFTau_unblind{suffix}.root'
    template_path = f"{base}/{era}/{out_version}_{in_version}/mc/variableHists_{hist_version}/combine/{template_name}"

    return template_path


def load_prefit_histograms(template_path, region, processList, variable):
    """
    Load histograms from template file for pre-fit plotting.

    Template histogram naming: {process}_{region}_{variable}
    e.g., tttt_1tau0lSR_BDT, tt_1tau0lSR_BDT
    """
    file = ROOT.TFile.Open(template_path)
    if not file or file.IsZombie():
        print(f"Error: Cannot open template file: {template_path}")
        return {}

    sumProcess = {}

    for process in processList:
        # Handle data naming
        if process in ['jetHT', 'leptonSum']:
            hist_name = f'data_obs_{region}_{variable}'
        else:
            hist_name = f'{process}_{region}_{variable}'

        hist = file.Get(hist_name)
        if hist:
            hist_clone = hist.Clone(f'{process}_prefit')
            hist_clone.SetDirectory(0)
            sumProcess[process] = hist_clone
        else:
            # Try alternative naming convention
            alt_name = f'{region}_{process}_{variable}'
            hist = file.Get(alt_name)
            if hist:
                hist_clone = hist.Clone(f'{process}_prefit')
                hist_clone.SetDirectory(0)
                sumProcess[process] = hist_clone
            else:
                print(f"  Warning: Histogram not found: {hist_name} or {alt_name}")

    file.Close()
    return sumProcess


def run_postfit_plots(fit_file, args):
    """Run post-fit plotting with the specified fitDiagnostics file."""
    print("\n" + "="*80)
    print("Generating POST-FIT plots from fitDiagnostics file")
    print("="*80)
    print(f"Input: {fit_file}")

    # Call the main post-fit logic
    run_postfit_main(fit_file, args)


def run_postfit_plots_legacy():
    """Legacy main function for backward compatibility."""
    run_postfit_main_legacy()


def _get_plot_options(args):
    """Create plotting options dict from args."""
    ifVLL = getattr(args, 'vll', '')
    return {
        'variable': 'BDT',
        'ifFakeTau': True,
        'ifVLL': ifVLL,  # VLL process name (e.g., 'VLLm700') or empty string
        'ifMCFTau': False,
        'ifDoSystmatic': False,
        'ifPostfit': True,
        'ifStackSignal': False if ifVLL else True,  # Don't stack VLL signal - show as overlay
        'ifLogy': not getattr(args, 'no_logy', False),
        'ifPrintSB': True,
        'ifBlind': getattr(args, 'blind', False),
    }


def _prepare_process_list(channel, opts):
    """Prepare process list with ttX grouping for plotting."""
    sumProList = plt.getSumList(channel, opts['ifFakeTau'], opts['ifVLL'], opts['ifMCFTau'], True)
    sumProList_forLoading = sumProList.copy()

    # Replace ttZ, ttW, ttH with ttX
    for proc in ['ttZ', 'ttW', 'ttH']:
        if proc in sumProList:
            sumProList.remove(proc)

    # Insert ttX after tt
    insert_pos = sumProList.index('tt') + 1 if 'tt' in sumProList else 0
    sumProList.insert(insert_pos, 'ttX')

    return sumProList, sumProList_forLoading


def _plot_channel_eras(histsPerEra, sumProList, opts, iRegion, plotDir, channel):
    """Plot histograms for individual eras."""
    for era, era_hists in histsPerEra.items():
        print(f'\nPlotting {channel} era: {era}')
        for ifit, sumProcess in era_hists.items():
            plotName = f"{opts['variable']}_{iRegion}_{ifit}_{era}"
            plt.makeStackPlotNew(
                sumProcess, sumProList, opts['variable'], iRegion, plotDir, False,
                plotName, era, True, 100, opts['ifStackSignal'], opts['ifLogy'],
                opts['ifPrintSB'], opts['ifVLL'], {}, opts['ifDoSystmatic'],
                opts['ifBlind'], opts['ifPostfit'])


def _plot_run2_combination(combinedHists, sumProList, opts, iRegion, plotDir):
    """Plot Run2 combined histograms."""
    for ifit, sumProcess in combinedHists.items():
        plotName = f"{opts['variable']}_{iRegion}_{ifit}_Run2"
        plt.makeStackPlotNew(
            sumProcess, sumProList, opts['variable'], iRegion, plotDir, False,
            plotName, 'Run2', True, 100, opts['ifStackSignal'], opts['ifLogy'],
            opts['ifPrintSB'], opts['ifVLL'], {}, opts['ifDoSystmatic'],
            opts['ifBlind'], opts['ifPostfit'])


def _plot_multichannel_combination(channels, histsPerChannel, channel_name, region_name, opts, plotDir):
    """Create and plot multi-channel combination."""
    print(f'\n{"="*80}')
    print(f'Creating {channel_name} combined channel')
    print(f'{"="*80}')

    combined = combine_channels(channels, histsPerChannel, channel_name)
    sumProList = get_union_process_list(channels, opts['ifFakeTau'], opts['ifVLL'], opts['ifMCFTau'])
    print(f'Process list for {channel_name}: {sumProList}')

    for ifit, sumProcess in combined.items():
        plotName = f"{opts['variable']}_{region_name}_{ifit}_Run2"
        plt.makeStackPlotNew(
            sumProcess, sumProList, opts['variable'], region_name, plotDir, False,
            plotName, 'Run2', True, 100, opts['ifStackSignal'], opts['ifLogy'],
            opts['ifPrintSB'], opts['ifVLL'], {}, opts['ifDoSystmatic'],
            opts['ifBlind'], opts['ifPostfit'])


def run_postfit_main(fitFile, args):
    """Run post-fit plotting with command-line arguments."""
    opts = _get_plot_options(args)

    print(f'Analyzing fitDiagnostics file: {fitFile}')
    channels_eras = get_channels_and_eras(fitFile)

    print(f'\nFound channels and eras:')
    for channel, eras in channels_eras.items():
        print(f'  {channel}: {eras}')

    fitDir = fitFile.rsplit('/', 1)[0]
    plotDir = f'{fitDir}/postfitPlots/'
    uf.checkMakeDir(plotDir)

    histsPerChannel = {}

    # Process each channel
    for channel, eras in channels_eras.items():
        print(f'\n{"="*80}')
        print(f'Processing channel: {channel}')
        print(f'{"="*80}')

        iRegion = f'SR{channel}'
        sumProList, sumProList_forLoading = _prepare_process_list(channel, opts)
        print(f'Process list for plotting: {sumProList}')

        # Load histograms for all eras
        histsPerEra = {}
        for era in eras:
            print(f'\nLoading histograms for era: {era}')
            histsPerEra[era] = get_histograms(fitFile, iRegion, era, opts['variable'], sumProList_forLoading)

        # Plot individual eras
        _plot_channel_eras(histsPerEra, sumProList, opts, iRegion, plotDir, channel)

        # Create and plot Run2 combination
        print(f'\nCreating Run2 combination for {channel}')
        combinedHists = combine_eras(histsPerEra, sumProList)
        histsPerChannel[channel] = combine_eras_untrimmed(
            fitFile, iRegion, eras, opts['variable'], sumProList_forLoading)

        _plot_run2_combination(combinedHists, sumProList, opts, iRegion, plotDir)

    # Multi-channel combinations
    if '1tau1l' in channels_eras and '1tau2l' in channels_eras:
        _plot_multichannel_combination(
            ['1tau1l', '1tau2l'], histsPerChannel, '1tau1land2l', 'SR1tau1land2l', opts, plotDir)

    if all(ch in channels_eras for ch in ['1tau0l', '1tau1l', '1tau2l']):
        _plot_multichannel_combination(
            ['1tau0l', '1tau1l', '1tau2l'], histsPerChannel, '1tau0l1l2l', 'SR1tau0l1l2l', opts, plotDir)

    print(f'\n{"="*80}')
    print(f'All plots saved to: {plotDir}')
    print(f'{"="*80}')


def run_postfit_main_legacy():
    """Legacy main function for backward compatibility when called without arguments."""
    # Default hardcoded fit file path
    fitFile = '/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV18/run2_3channels_v4_unblind/fitDiagnosticsTest.root'

    # Create a simple args-like object with defaults
    class Args:
        no_logy = False
        blind = False
        output_dir = None

    args = Args()
    run_postfit_main(fitFile, args)


def _parse_region_name(region_name):
    """
    Parse region name to extract channel and era.
    Handles both formats:
    - 'SR1tau0l_2018' (single channel format)
    - 'SR1tau0l_SR1tau0l_2018' (3-channel combination format)
    Returns (channel, era) tuple or (None, None) if parsing fails.
    """
    if '_' not in region_name:
        return None, None

    parts = region_name.split('_')

    # Handle 3-part format: SR{channel}_SR{channel}_{era}
    if len(parts) == 3:
        region_part1, region_part2, era = parts
        if region_part1.startswith('SR') and region_part2.startswith('SR'):
            channel = region_part1[2:]  # Remove 'SR' prefix
            return channel, era

    # Handle 2-part format: SR{channel}_{era}
    if len(parts) == 2:
        region_part, era = parts
        if region_part.startswith('SR'):
            channel = region_part[2:]  # Remove 'SR' prefix
            return channel, era

    return None, None


def get_channels_and_eras(filename):
    '''
    Automatically detect channels and eras from fitDiagnostics file
    Returns: dict with channel: [list of eras]
    Example: {'1tau0l': ['2016preVFP', '2016postVFP', '2017', '2018'], ...}
    '''
    file = ROOT.TFile.Open(filename)
    if not file or file.IsZombie():
        print(f'Error: Cannot open file {filename}')
        return {}

    channels_eras = {}
    shapes_dir = file.Get('shapes_fit_s')

    if not shapes_dir:
        file.Close()
        return channels_eras

    for key in shapes_dir.GetListOfKeys():
        obj = key.ReadObj()
        if not obj.IsA().InheritsFrom(ROOT.TDirectory.Class()):
            continue

        channel, era = _parse_region_name(obj.GetName())
        if channel is None:
            continue

        if channel not in channels_eras:
            channels_eras[channel] = []
        if era not in channels_eras[channel]:
            channels_eras[channel].append(era)

    file.Close()

    # Sort eras for consistent ordering
    for channel in channels_eras:
        channels_eras[channel].sort()

    return channels_eras


def combine_eras(histsPerEra, sumProList):
    '''
    Combine histograms from all eras into Run2 combination (with bin trimming)
    histsPerEra[era][fit][process] = histogram
    Returns: combinedHists[fit][process] = histogram
    '''
    combinedHists = {'prefit': {}, 'fit_s': {}, 'fit_b': {}}

    eras = list(histsPerEra.keys())
    print(f'Combining eras: {eras}')

    for fit in ['prefit', 'fit_s', 'fit_b']:
        for process in sumProList:
            # Start with the first era
            firstEra = eras[0]
            if process in histsPerEra[firstEra][fit]:
                combinedHists[fit][process] = histsPerEra[firstEra][fit][process].Clone(f'{process}_{fit}_Run2')
                combinedHists[fit][process].SetDirectory(0)

                # Add histograms from other eras
                for era in eras[1:]:
                    if process in histsPerEra[era][fit]:
                        combinedHists[fit][process].Add(histsPerEra[era][fit][process])
                    else:
                        print(f'Warning: Process {process} not found in era {era}, fit {fit}')

                # Set title for combined histogram
                combinedHists[fit][process].SetTitle('BDT score')
            else:
                print(f'Warning: Process {process} not found in first era {firstEra}, fit {fit}')

        # Remove trailing empty bins from combined histograms
        combinedHists[fit] = trim_empty_bins(combinedHists[fit])

    return combinedHists


def combine_eras_untrimmed(fitFile, iRegion, eras, variable, sumProList_forLoading):
    '''
    Load and combine histograms from all eras WITHOUT bin trimming
    Used for multi-channel combination to avoid bin mismatch issues
    Returns: combinedHists[fit][process] = histogram (untrimmed)
    '''
    combinedHists = {'prefit': {}, 'fit_s': {}, 'fit_b': {}}

    # Load untrimmed histograms for each era
    histsPerEra_untrimmed = {}
    for era in eras:
        histsPerEra_untrimmed[era] = get_histograms(fitFile, iRegion, era, variable, sumProList_forLoading, trim_bins=False)

    # Combine across eras (they'll all have same bin structure since from same fit file)
    for fit in ['prefit', 'fit_s', 'fit_b']:
        # Get list of all processes from first era
        firstEra = eras[0]
        all_processes = list(histsPerEra_untrimmed[firstEra][fit].keys())

        for process in all_processes:
            if process in histsPerEra_untrimmed[firstEra][fit]:
                combinedHists[fit][process] = histsPerEra_untrimmed[firstEra][fit][process].Clone(f'{process}_{fit}_Run2_untrimmed')
                combinedHists[fit][process].SetDirectory(0)

                # Add histograms from other eras
                for era in eras[1:]:
                    if process in histsPerEra_untrimmed[era][fit]:
                        combinedHists[fit][process].Add(histsPerEra_untrimmed[era][fit][process])

                # Set title for combined histogram
                combinedHists[fit][process].SetTitle('BDT score')

    return combinedHists


def _get_all_channel_processes(channelsToGet, histsPerChannel):
    """Get union of all processes from all channels."""
    all_processes = set()
    for channel in channelsToGet:
        if channel not in histsPerChannel:
            continue
        for fit in ['prefit', 'fit_s', 'fit_b']:
            if fit in histsPerChannel[channel]:
                all_processes.update(histsPerChannel[channel][fit].keys())
    return all_processes


def _find_last_filled_bin(hist):
    """Find the last bin with non-zero content in a histogram."""
    for i in range(hist.GetNbinsX(), 0, -1):
        if hist.GetBinContent(i) > 0:
            return i
    return 0


def _compute_channel_last_bins(channelsToGet, histsPerChannel, fit):
    """Compute last filled bin per channel for right-alignment."""
    channel_last_bins = {}
    max_filled_bin = 0

    for channel in channelsToGet:
        if channel not in histsPerChannel or fit not in histsPerChannel[channel]:
            continue

        channel_max = 0
        for hist in histsPerChannel[channel][fit].values():
            if hist:
                channel_max = max(channel_max, _find_last_filled_bin(hist))

        channel_last_bins[channel] = channel_max
        max_filled_bin = max(max_filled_bin, channel_max)

    return channel_last_bins, max_filled_bin


def _create_extended_histogram(source_hist, name, nbins):
    """Create a new histogram with extended bin count."""
    xaxis = source_hist.GetXaxis()
    bin_width = xaxis.GetBinWidth(1)
    new_hist = ROOT.TH1F(name, source_hist.GetTitle(), nbins,
                         xaxis.GetXmin(), xaxis.GetXmin() + nbins * bin_width)
    new_hist.SetDirectory(0)
    return new_hist


def _add_histogram_with_offset(target, source, offset):
    """Add source histogram to target with bin offset, errors in quadrature."""
    for i in range(1, source.GetNbinsX() + 1):
        target_bin = i + offset
        if target_bin > target.GetNbinsX():
            continue
        target.SetBinContent(target_bin,
                             target.GetBinContent(target_bin) + source.GetBinContent(i))
        err_target = target.GetBinError(target_bin)
        err_source = source.GetBinError(i)
        target.SetBinError(target_bin, (err_target**2 + err_source**2)**0.5)


def _merge_data_histograms(histDict, fit, channel_name):
    """Combine jetHT and leptonSum into single data histogram."""
    data_hist = None
    data_name = None

    for data_process in ['jetHT', 'leptonSum']:
        if data_process not in histDict:
            continue
        if data_hist is None:
            data_hist = histDict[data_process].Clone(f'data_{fit}_{channel_name}')
            data_hist.SetDirectory(0)
            data_name = data_process
        else:
            data_hist.Add(histDict[data_process])
            del histDict[data_process]

    if data_hist is not None and data_name is not None:
        histDict[data_name] = data_hist


def _combine_process_for_fit(process, channelsToGet, histsPerChannel, fit,
                              channel_name, channel_last_bins, max_filled_bin):
    """Combine a single process across channels with right-alignment."""
    combined_hist = None

    for channel in channelsToGet:
        if channel not in histsPerChannel or fit not in histsPerChannel[channel]:
            continue
        if process not in histsPerChannel[channel][fit]:
            continue

        channel_hist = histsPerChannel[channel][fit][process]
        bin_offset = max_filled_bin - channel_last_bins.get(channel, 0)

        if combined_hist is None:
            # Initialize combined histogram
            if channel_hist.GetNbinsX() < max_filled_bin:
                combined_hist = _create_extended_histogram(
                    channel_hist, f'{process}_{fit}_{channel_name}', max_filled_bin)
            else:
                combined_hist = channel_hist.Clone(f'{process}_{fit}_{channel_name}')
                combined_hist.SetDirectory(0)
                combined_hist.Reset()

            # Copy first channel with offset
            for i in range(1, channel_hist.GetNbinsX() + 1):
                combined_hist.SetBinContent(i + bin_offset, channel_hist.GetBinContent(i))
                combined_hist.SetBinError(i + bin_offset, channel_hist.GetBinError(i))
        else:
            _add_histogram_with_offset(combined_hist, channel_hist, bin_offset)

    if combined_hist is not None:
        combined_hist.SetTitle('BDT score')

    return combined_hist


def combine_channels(channelsToGet, histsPerChannel, channel_name):
    '''
    Combine histograms from multiple channels into a single combined channel.
    Bins are RIGHT-ALIGNED so that highest BDT bins are merged together.
    '''
    combinedHists = {'prefit': {}, 'fit_s': {}, 'fit_b': {}}
    print(f'Combining channels: {channelsToGet}')

    all_processes = _get_all_channel_processes(channelsToGet, histsPerChannel)
    print(f'Union process list: {sorted(all_processes)}')

    for fit in ['prefit', 'fit_s', 'fit_b']:
        channel_last_bins, max_filled_bin = _compute_channel_last_bins(
            channelsToGet, histsPerChannel, fit)
        print(f'Last filled bins for {fit}: {channel_last_bins}, max: {max_filled_bin}')

        for process in all_processes:
            combined = _combine_process_for_fit(
                process, channelsToGet, histsPerChannel, fit,
                channel_name, channel_last_bins, max_filled_bin)
            if combined is not None:
                combinedHists[fit][process] = combined
            else:
                print(f'Warning: Process {process} not found for fit {fit}')

        _merge_data_histograms(combinedHists[fit], fit, channel_name)
        combinedHists[fit] = trim_empty_bins(combinedHists[fit])

    return combinedHists


def get_union_process_list(channels, ifFakeTau, ifVLL, ifMCFTau):
    '''
    Get union of process lists from multiple channels, preserving order
    Args:
        channels: List of channel names (e.g., ['1tau1l', '1tau2l'])
        ifFakeTau: Include fake tau background
        ifVLL: Include VLL signal
        ifMCFTau: Use MC fake tau instead of data-driven
    Returns:
        List of processes in union (data process at end)
    '''
    # Get process lists for each channel
    all_processes = []
    data_process = None

    for channel in channels:
        channel_processes = plt.getSumList(channel, ifFakeTau, ifVLL, ifMCFTau, True)
        for proc in channel_processes:
            # Separate data processes (different for different channels)
            if proc in ['jetHT', 'leptonSum']:
                # Keep jetHT preferentially (since combine_channels keeps jetHT when both exist)
                if data_process is None:
                    data_process = proc
                elif proc == 'jetHT':  # Prefer jetHT over leptonSum
                    data_process = 'jetHT'
            elif proc not in all_processes:
                all_processes.append(proc)

    # Add data process at end (if exists)
    if data_process:
        all_processes.append(data_process)

    return all_processes


def trim_empty_bins(histDict):
    '''
    Remove trailing empty bins from all histograms
    histDict: {process: histogram}
    Returns: dict with trimmed histograms
    '''
    if not histDict:
        return histDict

    # Find the last bin with content across all processes
    last_filled_bin = 0
    for process, hist in histDict.items():
        if hist:
            nbins = hist.GetNbinsX()
            # Find last non-empty bin for this histogram
            for bin_num in range(nbins, 0, -1):
                content = hist.GetBinContent(bin_num)
                if content > 0:
                    last_filled_bin = max(last_filled_bin, bin_num)
                    break

    if last_filled_bin == 0:
        print("Warning: All bins are empty!")
        return histDict

    # Get the first histogram to check if trimming is needed
    first_hist = list(histDict.values())[0]
    nbins_original = first_hist.GetNbinsX()

    # Only trim if there are empty bins at the end
    if last_filled_bin >= nbins_original:
        return histDict

    print(f"Trimming histograms from {nbins_original} bins to {last_filled_bin} bins")

    # Create new histograms with trimmed bins
    trimmed_histDict = {}
    for process, hist in histDict.items():
        if hist:
            # Get bin edges for the new histogram
            xaxis = hist.GetXaxis()
            bin_edges = [xaxis.GetBinLowEdge(i) for i in range(1, last_filled_bin + 2)]

            # Create new histogram with trimmed bins
            new_hist = ROOT.TH1F(
                f"{hist.GetName()}_trimmed",
                hist.GetTitle(),
                last_filled_bin,
                bin_edges[0],
                bin_edges[-1]
            )
            new_hist.SetDirectory(0)

            # Copy bin contents and errors
            for bin_num in range(1, last_filled_bin + 1):
                new_hist.SetBinContent(bin_num, hist.GetBinContent(bin_num))
                new_hist.SetBinError(bin_num, hist.GetBinError(bin_num))

            # Copy histogram style
            new_hist.SetLineColor(hist.GetLineColor())
            new_hist.SetFillColor(hist.GetFillColor())
            new_hist.SetMarkerColor(hist.GetMarkerColor())
            new_hist.SetMarkerStyle(hist.GetMarkerStyle())
            new_hist.SetLineWidth(hist.GetLineWidth())

            trimmed_histDict[process] = new_hist

    return trimmed_histDict


def _convert_tgraph_to_hist(graph, total_hist, fit, era):
    """Convert TGraphAsymmErrors to TH1 using total_hist for binning."""
    import ctypes

    data_hist = total_hist.Clone(f"data_{fit}_{era}")
    data_hist.Reset()
    data_hist.SetDirectory(0)

    x = ctypes.c_double(0)
    y = ctypes.c_double(0)
    for i in range(graph.GetN()):
        graph.GetPoint(i, x, y)
        bin_num = data_hist.FindBin(x.value)
        data_hist.SetBinContent(bin_num, y.value)
        err_avg = (graph.GetErrorYlow(i) + graph.GetErrorYhigh(i)) / 2.0
        data_hist.SetBinError(bin_num, err_avg)

    return data_hist


def _load_single_histogram(file, fit, iRegion, era, process):
    """Load a single histogram from file, handling data TGraph conversion."""
    processToGet = 'data' if process in ('leptonSum', 'jetHT') else process

    # Try 3-channel format first: SR{channel}_SR{channel}_{era}
    histname = f'shapes_{fit}/{iRegion}_{iRegion}_{era}/{processToGet}'
    hist = file.Get(histname)

    # Fall back to 2-part format: SR{channel}_{era}
    if not hist:
        histname = f'shapes_{fit}/{iRegion}_{era}/{processToGet}'
        hist = file.Get(histname)
    if not hist:
        print(f"Warning: Histogram {histname} not found in {fit} for era {era}.")
        return None

    hist_clone = hist.Clone(f'{process}_{fit}_{era}')
    if hasattr(hist_clone, 'SetDirectory'):
        hist_clone.SetDirectory(0)

    # Convert TGraphAsymmErrors to TH1 for data
    if process in ('leptonSum', 'jetHT') and hist_clone.ClassName() == 'TGraphAsymmErrors':
        # Try 3-channel format first
        total_hist = file.Get(f'shapes_{fit}/{iRegion}_{iRegion}_{era}/total')
        if not total_hist:
            # Fall back to 2-part format
            total_hist = file.Get(f'shapes_{fit}/{iRegion}_{era}/total')
        if total_hist:
            hist_clone = _convert_tgraph_to_hist(hist_clone, total_hist, fit, era)

    return hist_clone


def _group_ttx_histograms(histDict, fit, era):
    """Group ttZ, ttW, ttH into combined ttX histogram."""
    ttX_hist = None
    for process in ['ttZ', 'ttW', 'ttH']:
        if process not in histDict:
            continue
        if ttX_hist is None:
            ttX_hist = histDict[process].Clone(f"ttX_{fit}_{era}")
            ttX_hist.SetDirectory(0)
        else:
            ttX_hist.Add(histDict[process])
        del histDict[process]

    if ttX_hist is not None:
        histDict['ttX'] = ttX_hist


def get_histograms(filename, iRegion, era, variable, processList, trim_bins=True):
    '''
    Load histograms from fitDiagnostics file for a specific era.
    Args:
        trim_bins: If True, remove trailing empty bins. Set False for multi-channel combination.
    Returns: sumProcessPerFit[fit][process] = histogram
    '''
    file = ROOT.TFile.Open(filename)
    if not file or file.IsZombie():
        print(f'Error: Cannot open file {filename}')
        return {'prefit': {}, 'fit_s': {}, 'fit_b': {}}

    sumProcessPerFit = {'prefit': {}, 'fit_s': {}, 'fit_b': {}}

    for fit in ['prefit', 'fit_s', 'fit_b']:
        for process in processList:
            hist = _load_single_histogram(file, fit, iRegion, era, process)
            if hist:
                sumProcessPerFit[fit][process] = hist

    file.Close()

    # Post-process: group ttX and apply formatting
    for fit in ['prefit', 'fit_s', 'fit_b']:
        _group_ttx_histograms(sumProcessPerFit[fit], fit, era)

        if trim_bins:
            sumProcessPerFit[fit] = trim_empty_bins(sumProcessPerFit[fit])

        for hist in sumProcessPerFit[fit].values():
            hist.SetTitle('BDT score')

    return sumProcessPerFit


if __name__ == "__main__":
    main()
