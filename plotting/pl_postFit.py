import ROOT
import usefulFunc as uf
import pl as plt
#

def main():
    # Fit file with 3 channels (1tau0l, 1tau1l, 1tau2l)
    fitFile = '/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV18/run2_3channels_v4_unblind/fitDiagnosticsTest.root'
    # Previous single channel fit file:
    # fitFile = '/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV18/run2_1tau2l_v4_unblind/fitDiagnosticsTest.root'

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

        sumProSys = plt.getSysDicPL(sumProList, ifDoSystmatic, channel, 'Run2', True)

        for ifit in combinedHists.keys():
            sumProcess = combinedHists[ifit]
            plotName = f'{variable}_{iRegion}_{ifit}_Run2'

            plt.makeStackPlotNew(sumProcess, sumProList, variable, iRegion, plotDir, False,
                               plotName, 'Run2', True, 100, ifStackSignal, ifLogy, ifPrintSB,
                               ifVLL, {}, ifDoSystmatic, ifBlind, ifPostfit)

    print(f'\n{"="*80}')
    print(f'All plots saved to: {plotDir}')
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
    Combine histograms from all eras into Run2 combination
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


def get_histograms(filename, iRegion, era, variable, processList):
    '''
    Load histograms from fitDiagnostics file for a specific era
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

        # Remove trailing empty bins
        sumProcessPerFit[fit] = trim_empty_bins(sumProcessPerFit[fit])

        # Set x-axis label to 'BDT score' for all histograms
        for process, hist in sumProcessPerFit[fit].items():
            hist.SetTitle('BDT score')

    return sumProcessPerFit


if __name__ == "__main__":
    main()
