import ROOT
import usefulFunc as uf
import pl as plt
#

def main():
    channel = '1tau2l'
    era = '2018'
    fitFile = '/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV18/run2_1tau2l_v4_unblind/fitDiagnosticsTest.root'
    iRegion = 'SR1tau2l' #format in the fitDiagnostics file
    
    
    variable = 'BDT'
    # iRegion = '1tau2lSR'
    ifFakeTau = True
    ifVLL = False
    ifMCFTau = False
    ifDoSystmatic = False
    ifPostfit = True  # Flag to indicate this is a postfit plot (uncertainties already include stat+syst from fit)
    ifStackSignal = True
    ifLogy = True
    ifPrintSB = True
    ifBlind = False
    sumProList = plt.getSumList(channel, ifFakeTau, ifVLL, ifMCFTau, True)

    # Keep original list with ttZ, ttW, ttH for loading from file
    sumProList_forLoading = sumProList.copy()

    # Replace ttZ, ttW, ttH with ttX in the process list for plotting
    # (the get_histograms function will load and merge these histograms)
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

    sumProSys = plt.getSysDicPL(sumProList, ifDoSystmatic, channel, era, True)
    #change the key of data back to leptonSum

    # getSumProHist_fromfitTest()
    sumProcessPerFit = {}
    #get hists for all sumprocess in a dictionary of the format nominal: {{process:hist}}
    sumProcessPerFit = get_histograms(fitFile, iRegion, era, variable, sumProList_forLoading)
    #change the key of data back to leptonSum for all fit types
    #print the structure of sumProcessPerFit
    

   
    #get the dir of fitFile
    fitDir = fitFile.rsplit('/', 1)[0]
    plotDir = f'{fitDir}/postfitPlots/'  
    uf.checkMakeDir(plotDir)
    
   
    for ifit in sumProcessPerFit.keys():
        sumProcess = sumProcessPerFit[ifit]
        plotName = f'{variable}_{iRegion}_{ifit}'

        plt.makeStackPlotNew(sumProcess, sumProList, variable, iRegion, plotDir, False, plotName, era, True, 100, ifStackSignal, ifLogy, ifPrintSB, ifVLL, {}, ifDoSystmatic, ifBlind, ifPostfit)
        # makeStackPlotNew(sumProcessPerVar[variable][iRegion], sumProList, variable, iRegion, plotDir, False, plotName, era, True, 100, ifStackSignal, ifLogy, ifPrintSB, ifVLL, sumProcessPerVarSys[variable][iRegion], ifDoSystmatic, ifBlind) 

def get_histograms(filename, iRegion, era, variable, processList):
    '''nominal: {{process:hist}}'''
    # Open the ROOT file
    file = ROOT.TFile.Open(filename)
    # Create the dictionary to store histograms
    sumProcessPerFit = {'prefit': {}, 'fit_s': {}, 'fit_b': {} }

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
                hist_clone = hist.Clone()
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
                        data_hist = total_hist.Clone(f"data_{fit}")
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
                print(f"Warning: Histogram {histname} not found in {fit}.")

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
                    ttX_hist = sumProcessPerFit[fit][process].Clone(f"ttX_{fit}")
                    ttX_hist.SetDirectory(0)
                else:
                    # Add subsequent histograms
                    ttX_hist.Add(sumProcessPerFit[fit][process])
                # Remove the individual process
                del sumProcessPerFit[fit][process]

        # Add the combined ttX histogram
        if ttX_hist is not None:
            sumProcessPerFit[fit]['ttX'] = ttX_hist

    return sumProcessPerFit


if __name__ == "__main__":
    main()