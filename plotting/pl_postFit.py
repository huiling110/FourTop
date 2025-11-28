import ROOT
import usefulFunc as uf
import pl as plt
#

def main():
    # Fit file with 3 channels (1tau0l, 1tau1l, 1tau2l)
    fitFile = '/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV18/run2_3channels_v4_unblind/fitDiagnosticsTest.root'
    # Previous single channel fit file:
    # fitFile = '/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV18/run2_1tau2l_v4_unblind/fitDiagnosticsTest.root'
    # fitFile = '/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV18/run2_1tau0l_v4_unblind_smoothed_check/combineResults/postfitPlots/fitDiagnosticsTest.root'

    variable = 'BDT'
    # Plotting options
    ifFakeTau = True
    ifVLL = False
    ifMCFTau = False
    ifDoSystmatic = False
    ifPostfit = True  # Flag to indicate this is a postfit plot (uncertainties already include stat+syst from fit)
    ifStackSignal = True
    ifLogy = True
    ifPrintSB = True
    ifBlind = False

    # Automatically detect channels and eras from the file
    print(f'Analyzing fitDiagnostics file: {fitFile}')
    channels_eras = get_channels_and_eras(fitFile)

    print(f'\nFound channels and eras:')
    for channel, eras in channels_eras.items():
        print(f'  {channel}: {eras}')

    # Setup output directory
    fitDir = fitFile.rsplit('/', 1)[0]
    plotDir = f'{fitDir}/postfitPlots/'
    uf.checkMakeDir(plotDir)

    # Dictionary to store Run2 combined histograms per channel (for multi-channel combination)
    histsPerChannel = {}  # histsPerChannel[channel][fit][process] = histogram

    # Process each channel
    for channel, eras in channels_eras.items():
        print(f'\n{"="*80}')
        print(f'Processing channel: {channel}')
        print(f'{"="*80}')

        iRegion = f'SR{channel}'  # e.g., SR1tau0l, SR1tau1l, SR1tau2l

        # Get process list for this channel
        sumProList = plt.getSumList(channel, ifFakeTau, ifVLL, ifMCFTau, True)

        # Keep original list with ttZ, ttW, ttH for loading from file
        sumProList_forLoading = sumProList.copy()

        # Replace ttZ, ttW, ttH with ttX in the process list for plotting
        processes_to_group = ['ttZ', 'ttW', 'ttH']
        for proc in processes_to_group:
            if proc in sumProList:
                sumProList.remove(proc)
        # Add ttX at the position where ttZ was (or after tt if ttZ wasn't there)
        if 'tt' in sumProList:
            tt_index = sumProList.index('tt')
            sumProList.insert(tt_index + 1, 'ttX')
        else:
            sumProList.insert(0, 'ttX')

        print(f'Process list for plotting: {sumProList}')

        # Load histograms for all eras from the same file
        histsPerEra = {}  # histsPerEra[era][fit][process] = histogram
        for era in eras:
            print(f'\nLoading histograms for era: {era}')
            histsPerEra[era] = get_histograms(fitFile, iRegion, era, variable, sumProList_forLoading)

        # Plot individual eras
        for era in eras:
            print(f'\nPlotting {channel} era: {era}')
            sumProSys = plt.getSysDicPL(sumProList, ifDoSystmatic, channel, era, True)

            for ifit in histsPerEra[era].keys():
                sumProcess = histsPerEra[era][ifit]
                plotName = f'{variable}_{iRegion}_{ifit}_{era}'

                plt.makeStackPlotNew(sumProcess, sumProList, variable, iRegion, plotDir, False,
                                   plotName, era, True, 100, ifStackSignal, ifLogy, ifPrintSB,
                                   ifVLL, {}, ifDoSystmatic, ifBlind, ifPostfit)

        # Create and plot Run2 combination for this channel
        print(f'\nCreating Run2 combination for {channel}')
        combinedHists = combine_eras(histsPerEra, sumProList)

        # Store UNTRIMMED Run2 combined histograms for multi-channel combination
        # (we need untrimmed histograms to avoid merging issues when channels have different bin counts)
        combinedHistsUntrimmed = combine_eras_untrimmed(fitFile, iRegion, eras, variable, sumProList_forLoading)
        histsPerChannel[channel] = combinedHistsUntrimmed

        sumProSys = plt.getSysDicPL(sumProList, ifDoSystmatic, channel, 'Run2', True)

        for ifit in combinedHists.keys():
            sumProcess = combinedHists[ifit]
            plotName = f'{variable}_{iRegion}_{ifit}_Run2'

            plt.makeStackPlotNew(sumProcess, sumProList, variable, iRegion, plotDir, False,
                               plotName, 'Run2', True, 100, ifStackSignal, ifLogy, ifPrintSB,
                               ifVLL, {}, ifDoSystmatic, ifBlind, ifPostfit)

    # Multi-channel combinations
    # 1. Combine 1tau1l + 1tau2l (leptonic channels)
    if '1tau1l' in channels_eras and '1tau2l' in channels_eras:
        print(f'\n{"="*80}')
        print(f'Creating 1tau1l + 1tau2l combined channel')
        print(f'{"="*80}')

        # Combine channels
        combined_1tau1l2l = combine_channels(
            ['1tau1l', '1tau2l'],
            histsPerChannel,
            '1tau1land2l'
        )

        # Get union process list
        sumProList_1l2l = get_union_process_list(['1tau1l', '1tau2l'], ifFakeTau, ifVLL, ifMCFTau)

        print(f'Process list for 1tau1l+1tau2l: {sumProList_1l2l}')

        # Plot for each fit type
        for ifit in ['prefit', 'fit_s', 'fit_b']:
            sumProcess = combined_1tau1l2l[ifit]
            plotName = f'{variable}_SR1tau1land2l_{ifit}_Run2'

            plt.makeStackPlotNew(sumProcess, sumProList_1l2l, variable, 'SR1tau1land2l',
                               plotDir, False, plotName, 'Run2', True, 100, ifStackSignal,
                               ifLogy, ifPrintSB, ifVLL, {}, ifDoSystmatic, ifBlind, ifPostfit)

    # 2. Combine all channels (1tau0l + 1tau1l + 1tau2l)
    if '1tau0l' in channels_eras and '1tau1l' in channels_eras and '1tau2l' in channels_eras:
        print(f'\n{"="*80}')
        print(f'Creating all channels combined')
        print(f'{"="*80}')

        # Combine all channels
        combined_all = combine_channels(
            ['1tau0l', '1tau1l', '1tau2l'],
            histsPerChannel,
            '1tau0l1l2l'
        )

        # Get union process list for all channels
        sumProList_all = get_union_process_list(['1tau0l', '1tau1l', '1tau2l'], ifFakeTau, ifVLL, ifMCFTau)

        print(f'Process list for all channels: {sumProList_all}')

        # Plot for each fit type
        for ifit in ['prefit', 'fit_s', 'fit_b']:
            sumProcess = combined_all[ifit]
            plotName = f'{variable}_SR1tau0l1l2l_{ifit}_Run2'

            plt.makeStackPlotNew(sumProcess, sumProList_all, variable, 'SR1tau0l1l2l',
                               plotDir, False, plotName, 'Run2', True, 100, ifStackSignal,
                               ifLogy, ifPrintSB, ifVLL, {}, ifDoSystmatic, ifBlind, ifPostfit)

    print(f'\n{"="*80}')
    print(f'All plots saved to: {plotDir}')
    if '1tau1l' in channels_eras and '1tau2l' in channels_eras:
        print(f'  - Created 1tau1l+1tau2l combined channel plots')
    if '1tau0l' in channels_eras and '1tau1l' in channels_eras and '1tau2l' in channels_eras:
        print(f'  - Created all-channels combined plots')
    print(f'{"="*80}')


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

    # Check shapes_fit_s directory for available regions
    shapes_dir = file.Get('shapes_fit_s')
    if shapes_dir:
        keys = shapes_dir.GetListOfKeys()
        for key in keys:
            obj = key.ReadObj()
            if obj.IsA().InheritsFrom(ROOT.TDirectory.Class()):
                region_name = obj.GetName()  # e.g., 'SR1tau0l_2018'

                # Parse region name to extract channel and era
                # Format: SR{channel}_{era}
                if '_' in region_name:
                    parts = region_name.split('_')
                    if len(parts) == 2:
                        region_part = parts[0]  # SR1tau0l
                        era = parts[1]  # 2018

                        # Extract channel from region (remove 'SR' prefix)
                        if region_part.startswith('SR'):
                            channel = region_part[2:]  # 1tau0l, 1tau1l, 1tau2l

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


def combine_channels(channelsToGet, histsPerChannel, channel_name):
    '''
    Combine histograms from multiple channels into a single combined channel
    Bins are RIGHT-ALIGNED so that highest BDT bins from all channels are merged together
    Args:
        channelsToGet: List of channels to combine (e.g., ['1tau1l', '1tau2l'])
        histsPerChannel: Dict structure {channel: {fit: {process: histogram}}}
        channel_name: Name for combined channel (e.g., '1tau1l_1tau2l')
    Returns:
        combinedHists[fit][process] = combined histogram
    '''
    combinedHists = {'prefit': {}, 'fit_s': {}, 'fit_b': {}}

    print(f'Combining channels: {channelsToGet}')

    # Get union of all processes from all channels
    all_processes = set()
    for channel in channelsToGet:
        if channel in histsPerChannel:
            # Check all fit types to get complete process list
            for fit in ['prefit', 'fit_s', 'fit_b']:
                if fit in histsPerChannel[channel]:
                    all_processes.update(histsPerChannel[channel][fit].keys())

    print(f'Union process list: {sorted(all_processes)}')

    for fit in ['prefit', 'fit_s', 'fit_b']:
        # First, find the maximum number of bins across all channels for this fit
        max_bins = 0
        for channel in channelsToGet:
            if channel in histsPerChannel and fit in histsPerChannel[channel]:
                # Get any histogram from this channel to check bin count
                for process in histsPerChannel[channel][fit]:
                    hist = histsPerChannel[channel][fit][process]
                    if hist:
                        max_bins = max(max_bins, hist.GetNbinsX())
                        break

        print(f'Maximum bins for {fit}: {max_bins}')

        for process in all_processes:
            combined_hist = None

            # Combine histograms from all channels with RIGHT alignment
            for channel in channelsToGet:
                if channel in histsPerChannel and fit in histsPerChannel[channel]:
                    if process in histsPerChannel[channel][fit]:
                        channel_hist = histsPerChannel[channel][fit][process]

                        if combined_hist is None:
                            # Create combined histogram with max_bins
                            combined_hist = channel_hist.Clone(f'{process}_{fit}_{channel_name}')
                            combined_hist.SetDirectory(0)
                            combined_hist.Reset()  # Clear contents

                            # If this first histogram has fewer bins than max, we'll add it right-aligned
                            nbins_channel = channel_hist.GetNbinsX()
                            bin_offset = max_bins - nbins_channel  # Offset for right-alignment

                            # Copy bin contents with offset
                            for i in range(1, nbins_channel + 1):
                                combined_hist.SetBinContent(i + bin_offset, channel_hist.GetBinContent(i))
                                combined_hist.SetBinError(i + bin_offset, channel_hist.GetBinError(i))
                        else:
                            # Add subsequent channels with right-alignment
                            nbins_channel = channel_hist.GetNbinsX()
                            bin_offset = max_bins - nbins_channel

                            for i in range(1, nbins_channel + 1):
                                combined_bin = i + bin_offset
                                combined_hist.SetBinContent(
                                    combined_bin,
                                    combined_hist.GetBinContent(combined_bin) + channel_hist.GetBinContent(i)
                                )
                                # Add errors in quadrature
                                err_combined = combined_hist.GetBinError(combined_bin)
                                err_channel = channel_hist.GetBinError(i)
                                combined_hist.SetBinError(
                                    combined_bin,
                                    (err_combined**2 + err_channel**2)**0.5
                                )

            if combined_hist is not None:
                # Set title for combined histogram
                combined_hist.SetTitle('BDT score')
                combinedHists[fit][process] = combined_hist
            else:
                print(f'Warning: Process {process} not found in any channel for fit {fit}')

        # Combine jetHT and leptonSum into a single data histogram if both exist
        data_hist = None
        data_name = None
        for data_process in ['jetHT', 'leptonSum']:
            if data_process in combinedHists[fit]:
                if data_hist is None:
                    data_hist = combinedHists[fit][data_process].Clone(f'data_{fit}_{channel_name}')
                    data_hist.SetDirectory(0)
                    data_name = data_process
                else:
                    # Add the second data histogram to the first
                    data_hist.Add(combinedHists[fit][data_process])
                    # Remove the second data process
                    del combinedHists[fit][data_process]

        # Replace the first data process with the combined data histogram
        if data_hist is not None and data_name is not None:
            combinedHists[fit][data_name] = data_hist

        # Remove trailing empty bins from combined histograms
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


def get_histograms(filename, iRegion, era, variable, processList, trim_bins=True):
    '''
    Load histograms from fitDiagnostics file for a specific era
    Args:
        trim_bins: If True, remove trailing empty bins (default). Set to False for multi-channel combination.
    Returns: sumProcessPerFit[fit][process] = histogram
    '''
    # Open the ROOT file
    file = ROOT.TFile.Open(filename)
    if not file or file.IsZombie():
        print(f'Error: Cannot open file {filename}')
        return {'prefit': {}, 'fit_s': {}, 'fit_b': {}}

    # Create the dictionary to store histograms
    sumProcessPerFit = {'prefit': {}, 'fit_s': {}, 'fit_b': {}}

    # Iterate over prefit and postfit
    for fit in ['prefit', 'fit_s', 'fit_b']:
        # Attempt to find histograms for each process
        for process in processList:
            # Construct the histogram name based on fit, region, era, variable and process
            if process == 'leptonSum' or process == 'jetHT':
                processToGet = 'data'
            else:
                processToGet = process
            histname = f'shapes_{fit}/{iRegion}_{era}/{processToGet}'
            # Retrieve the histogram from the file
            hist = file.Get(histname)

            if hist:
                # Clone the histogram to keep it in memory after file closure
                hist_clone = hist.Clone(f'{process}_{fit}_{era}')
                # SetDirectory(0) detaches the histogram from the file
                # Only histograms have SetDirectory, not TGraphs
                if hasattr(hist_clone, 'SetDirectory'):
                    hist_clone.SetDirectory(0)

                # For data, convert TGraphAsymmErrors to TH1
                if (process == 'leptonSum' or process == 'jetHT') and hist_clone.ClassName() == 'TGraphAsymmErrors':
                    # Get the total histogram to get binning
                    total_hist = file.Get(f'shapes_{fit}/{iRegion}_{era}/total')
                    if total_hist:
                        # Create a histogram with the same binning as total
                        data_hist = total_hist.Clone(f"data_{fit}_{era}")
                        data_hist.Reset()
                        data_hist.SetDirectory(0)

                        # Fill the histogram from TGraph points
                        import ctypes
                        x = ctypes.c_double(0)
                        y = ctypes.c_double(0)
                        for i in range(hist_clone.GetN()):
                            hist_clone.GetPoint(i, x, y)
                            bin_num = data_hist.FindBin(x.value)
                            data_hist.SetBinContent(bin_num, y.value)
                            # Set error as the average of up and down errors
                            err_low = hist_clone.GetErrorYlow(i)
                            err_high = hist_clone.GetErrorYhigh(i)
                            data_hist.SetBinError(bin_num, (err_low + err_high) / 2.0)

                        hist_clone = data_hist

                sumProcessPerFit[fit][process] = hist_clone
            else:
                print(f"Warning: Histogram {histname} not found in {fit} for era {era}.")

    # Close the ROOT file
    file.Close()

    # Group ttW, ttH, and ttZ into ttX
    for fit in ['prefit', 'fit_s', 'fit_b']:
        ttX_hist = None
        processes_to_combine = ['ttZ', 'ttW', 'ttH']

        for process in processes_to_combine:
            if process in sumProcessPerFit[fit]:
                if ttX_hist is None:
                    # Clone the first histogram as the base for ttX
                    ttX_hist = sumProcessPerFit[fit][process].Clone(f"ttX_{fit}_{era}")
                    ttX_hist.SetDirectory(0)
                else:
                    # Add subsequent histograms
                    ttX_hist.Add(sumProcessPerFit[fit][process])
                # Remove the individual process
                del sumProcessPerFit[fit][process]

        # Add the combined ttX histogram
        if ttX_hist is not None:
            sumProcessPerFit[fit]['ttX'] = ttX_hist

        # Remove trailing empty bins (only if trim_bins=True)
        if trim_bins:
            sumProcessPerFit[fit] = trim_empty_bins(sumProcessPerFit[fit])

        # Set x-axis label to 'BDT score' for all histograms
        for process, hist in sumProcessPerFit[fit].items():
            hist.SetTitle('BDT score')

    return sumProcessPerFit


if __name__ == "__main__":
    main()
