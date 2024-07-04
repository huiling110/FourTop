import glob
import os
import ROOT
import pandas as pd
import usefulFunc as uf
import ttttGlobleQuantity as gq

def main():
    OSdir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v77HadroPresel/'

    
    subDic ={}
    for isub in (os.listdir(OSdir+'mc/') + os.listdir(OSdir+'data/')):
        print(isub)
        isData = uf.isData(isub)
        preDir = 'data/' if isData else 'mc/'
        icutflow = getHistDir(OSdir+ preDir +isub, 'OScutflow' )
        # print(icutflow)
        subDic[isub] = icutflow
    print(subDic)

    sumDic = sum_histograms(subDic)
    print(sumDic)

    writeCSV(sumDic, OSdir)

def writeCSV(sumDic, OSdir):
    df = histogram_to_dataframe(sumDic)
    outDir = OSdir + 'results/'
    uf.checkMakeDir(outDir)
    df.to_csv(outDir+'cutflow.csv', index=False)
    print(f"Cutflow CSV written to {outDir+'cutflow.csv'}")

def histogram_to_dataframe(hist_dict):
    dic={}
    for subprocess, hist in hist_dict.items():
        icutflow = []
        for bin in range(1, hist.GetNbinsX() + 1):
            bin_content = hist.GetBinContent(bin)
            bin_error = hist.GetBinError(bin)
            bin_label = hist.GetXaxis().GetBinLabel(bin)
            icutflow.append(bin_content)
        dic[subprocess] = icutflow
    
    df = pd.DataFrame.from_dict(dic, orient='index', columns=['initial', 'METFilter', 'HLT', 'tauF>=1', 'jet>=6', 'bjet>1', 'HT>480&6thjet>38'])
    df.reset_index(inplace=True)
    df.rename(columns={'index': 'Process'}, inplace=True)

    print(df)
    return df


def sum_histograms(subprocess_hist_dict ):
    summed_hist_dict = {}
    
    # for subprocess, summed_process in subprocess_to_summed_process.items():
    for subprocess, summed_process in gq.histoGramPerSample.items():
            if subprocess not in subprocess_hist_dict:
                print(f"Warning: Subprocess {subprocess} not found in histogram dictionary")
                continue
            
            hist = subprocess_hist_dict[subprocess]
            
            if summed_process not in summed_hist_dict:
                summed_hist_dict[summed_process] = hist.Clone(summed_process)
                summed_hist_dict[summed_process].SetDirectory(0)  # Detach from the file
            else:
                summed_hist_dict[summed_process].Add(hist)
        
    return summed_hist_dict



def getHistDir(directory, hist_name):
    summed_hist = None
    # Find all ROOT files in the directory
    root_files = glob.glob(os.path.join(directory, '*.root'))
    
    for file_path in root_files:
        # Open the ROOT file
        root_file = ROOT.TFile.Open(file_path)
        if not root_file:
            print(f"Error: Could not open {file_path}")
            continue
        
        # Retrieve the histogram
        hist = root_file.Get(hist_name)
        if not hist:
            print(f"Error: Histogram {hist_name} not found in {file_path}")
            root_file.Close()
            continue
        
        # Check if the histogram is valid
        if not isinstance(hist, ROOT.TH1D):
            print(f"Error: {hist_name} in {file_path} is not a TH1D histogram")
            root_file.Close()
            continue
        
        # Add the histogram to the summed histogram
        if summed_hist is None:
            summed_hist = hist.Clone("summed_hist")
            summed_hist.SetDirectory(0)  # Detach from the file
        else:
            summed_hist.Add(hist)
        
        # Close the ROOT file
        root_file.Close()
    
    return summed_hist

if __name__ == "__main__":
    main()
