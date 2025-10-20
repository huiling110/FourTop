import ROOT
import usefulFunc as uf
import pl as plt
#

def main():
    channel = '1tau2l'
    fitFile = '/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV18/run2_1tau2l_v4_unblind/fitDiagnosticsTest.root'
    iRegion = 'SR1tau2l' #format in the fitDiagnostics file

    # Define all eras to process
    eras = ['2018', '2017', '2016preVFP', '2016postVFP']

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

    # Get process list
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

    print('Process list for plotting:', sumProList)

    # Load histograms for all eras from the same file
    histsPerEra = {}  # histsPerEra[era][fit][process] = histogram
    for era in eras:
        print(f'\nLoading histograms for era: {era}')
        histsPerEra[era] = get_histograms(fitFile, iRegion, era, variable, sumProList_forLoading)

    # Setup output directory
    fitDir = fitFile.rsplit('/', 1)[0]
    plotDir = f'{fitDir}/postfitPlots/'
    uf.checkMakeDir(plotDir)

    # Plot individual eras
    for era in eras:
        print(f'\nPlotting era: {era}')
        sumProSys = plt.getSysDicPL(sumProList, ifDoSystmatic, channel, era, True)

        for ifit in histsPerEra[era].keys():
            sumProcess = histsPerEra[era][ifit]
            plotName = f'{variable}_{iRegion}_{ifit}_{era}'

            plt.makeStackPlotNew(sumProcess, sumProList, variable, iRegion, plotDir, False,
                               plotName, era, True, 100, ifStackSignal, ifLogy, ifPrintSB,
                               ifVLL, {}, ifDoSystmatic, ifBlind, ifPostfit)

    # Create and plot Run2 combination
    print('\nCreating Run2 combination')
    combinedHists = combine_eras(histsPerEra, sumProList)

    sumProSys = plt.getSysDicPL(sumProList, ifDoSystmatic, channel, 'Run2', True)

    for ifit in combinedHists.keys():
        sumProcess = combinedHists[ifit]
        plotName = f'{variable}_{iRegion}_{ifit}_Run2'

        plt.makeStackPlotNew(sumProcess, sumProList, variable, iRegion, plotDir, False,
                           plotName, 'Run2', True, 100, ifStackSignal, ifLogy, ifPrintSB,
                           ifVLL, {}, ifDoSystmatic, ifBlind, ifPostfit)

    print(f'\nAll plots saved to: {plotDir}')


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

    return combinedHists


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

        # Set x-axis label to 'BDT score' for all histograms
        for process, hist in sumProcessPerFit[fit].items():
            hist.SetTitle('BDT score')

    return sumProcessPerFit


if __name__ == "__main__":
    main()
