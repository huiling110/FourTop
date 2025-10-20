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
    ifStackSignal = True
    ifLogy = True
    ifPrintSB = True
    ifBlind = False
    sumProList = plt.getSumList(channel, ifFakeTau, ifVLL, ifMCFTau, True)    
    #change leptonSum in sumProList to data
    # if 'leptonSum' in sumProList:
    #     sumProList[sumProList.index('leptonSum')] = 'data'
    # print("sumProList:", sumProList)
    sumProSys = plt.getSysDicPL(sumProList, ifDoSystmatic, channel, era, True)    
    #change the key of data back to leptonSum

    # getSumProHist_fromfitTest()
    sumProcessPerFit = {}
    #get hists for all sumprocess in a dictionary of the format nominal: {{process:hist}}
    sumProcessPerFit = get_histograms(fitFile, iRegion, era, variable, sumProList)
    #change the key of data back to leptonSum for all fit types
   
   
    #get the dir of fitFile
    fitDir = fitFile.rsplit('/', 1)[0]
    plotDir = f'{fitDir}/postfitPlots/'  
    uf.checkMakeDir(plotDir)
    
   
    for ifit in sumProcessPerFit.keys():
        sumProcess = sumProcessPerFit[ifit]
        plotName = f'{variable}_{iRegion}_{ifit}'
        plt.makeStackPlotNew(sumProcess, sumProList, variable, iRegion, plotDir, False, plotName, era, True, 100, ifStackSignal, ifLogy, ifPrintSB, ifVLL, {}, ifDoSystmatic, ifBlind)
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
                # If histogram is found, add it to the dictionary
                sumProcessPerFit[fit][process] = hist
            else:
                print(f"Warning: Histogram {histname} not found in {fit}.")

    # Close the ROOT file
    file.Close()
    
    return sumProcessPerFit


if __name__ == "__main__":
    main()