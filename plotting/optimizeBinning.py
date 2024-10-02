import numpy as np
import ROOT
from scipy.optimize import minimize

import usefulFunc as uf
import ttttGlobleQuantity as gq

#to do: maybe consider statical uncertainty in data in the significance calculation
def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/variableHists_v1BDT1tau1l_evenBin/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v84Pre1tau2lLepF2/mc/variableHists_v1BDT1tau2lEvenBin/'
    channel = '1tau2l'
    
    
    era = uf.getEraFromDir(inputDir)
    print('era=', era)
    inputDirDic = uf.getInputDicNew( inputDir)
    uf.checkMakeDir( inputDirDic['mc']+'results/')
    sigHist, bgHist = getSigBgHist(inputDirDic,  era, channel)
    
    # optimizeHists(sigHist, bgHist)
    best_bin_edges, best_significance = optimize_binning(sigHist, bgHist, 1)

    print(f"Optimized bin edges: {best_bin_edges}")
    print(f"Best significance: {best_significance}")

    # Rebin histograms with optimized bin edges
    h_optimized_signal = rebin_histogram(sigHist, best_bin_edges)
    h_optimized_background = rebin_histogram(bgHist, best_bin_edges)

    plot_histograms([h_optimized_signal, h_optimized_background], ["Signal", "Background"], output_filename=inputDirDic['mc']+'results/plot.png', title="Optimized Binning", x_axis_title="BDT", y_axis_title="Events")

def plot_histograms(histograms, legend_names, output_filename="plot.png", title="Histogram Comparison", x_axis_title="X-axis", y_axis_title="Y-axis"):
    if len(histograms) != len(legend_names):
        raise ValueError("The number of histograms and legend names must be the same.")
    
    # Create a canvas
    c1 = ROOT.TCanvas("c1", title, 800, 600)
    #set log scale
    
    
    # Determine the maximum y-value for setting y-axis range
    max_y = max(hist.GetMaximum() for hist in histograms)
    
    # Set line colors for histograms
    colors = [ROOT.kRed, ROOT.kBlue, ROOT.kGreen, ROOT.kMagenta, ROOT.kCyan, ROOT.kOrange]
    
    # Draw histograms
    for i, hist in enumerate(histograms):
        hist.SetLineColor(colors[i % len(colors)])
        hist.SetMaximum(1.2 * max_y)
        hist.SetTitle(title)
        hist.GetXaxis().SetTitle(x_axis_title)
        hist.GetYaxis().SetTitle(y_axis_title)
        draw_option = "HIST" if i == 0 else "HIST SAME"
        hist.Draw(draw_option)
    
    # Create and customize legend
    legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
    for hist, name in zip(histograms, legend_names):
        legend.AddEntry(hist, name, "l")
    legend.Draw()
    
    # c1.setLogy()
    # Save the canvas to a file
    c1.SaveAs(output_filename)
    

# def getSigBgHist(inputDirDic,  era):
def getSigBgHist(inputDirDic,  era, channel = '1tau1l'):
    # sumProList = ['jetHT','tt', 'ttX', 'singleTop', 'WJets', 'tttt'] #1tau1l
    sumProList = gq.proChannelDic[channel]
    region = f'{channel}SR'
    sumProcessPerVar, sumProcessPerVarSys = uf.getSumHist(inputDirDic, [region], sumProList, {}, ['BDT'], era, False )#sumProcessPerVar[ivar][region][sumPro]
    
    sigHist = sumProcessPerVar['BDT'][region]['tttt']
    bgHist = uf.addBGHist(sumProcessPerVar['BDT'], region)
    sigHist.Print()
    bgHist.Print()
    
    return sigHist, bgHist


# Define the significance metric
def significance(bins, signal, background):
    s, _ = np.histogram(signal, bins=bins)
    b, _ = np.histogram(background, bins=bins)
    return np.sum(s / np.sqrt(s + b + 1e-6))  # Add a small term to avoid division by zero

def optimizeHists(signal, background):
    # Initial bin edges
    initial_bins = np.linspace(min(signal.min(), background.min()), max(signal.max(), background.max()), 20)

    # Optimize bin edges
    result = minimize(lambda bins: -significance(bins, signal, background), initial_bins, method='Nelder-Mead')
    optimized_bins = result.x
    print('Optimized bins:', optimized_bins)

# def adaptive_binning(h_signal, target_bin_content):
def adaptive_binning(h_signal, target_bin_content, binWidthRight = 0.01):
    bin_edges = [h_signal.GetXaxis().GetXmin()]
    current_bin_signal = 0
    # current_bin_background = 0

    for i in range(1, h_signal.GetNbinsX() + 1):
        current_bin_signal += h_signal.GetBinContent(i)
        # current_bin_background += h_background.GetBinContent(i)
        
        if current_bin_signal >= target_bin_content or i == h_signal.GetNbinsX():
            bin_edges.append(h_signal.GetXaxis().GetBinUpEdge(i))
            current_bin_signal = 0
            # current_bin_background = 0

    return bin_edges


def calculate_significance(signal, background):
    significance = 0
    for s, b in zip(signal, background):
        if s + b > 0:
            significance += s / ROOT.TMath.Sqrt(s + b)
    return significance

def calculate_asimov_significance(signal, background):
    significance = 0
    for s, b in zip(signal, background):
        if b > 0:
            term1 = (s + b) * np.log(1 + s / b)
            term2 = s
            significance += 2 * (term1 - term2)
    return np.sqrt(significance)


def rebin_histogram(histo, bin_edges):
    new_histo = ROOT.TH1D(histo.GetName() + "_rebin", histo.GetTitle(), len(bin_edges) - 1, np.array(bin_edges)).Clone()
    for i in range(1, histo.GetNbinsX() + 1):
        new_histo.Fill(histo.GetBinCenter(i), histo.GetBinContent(i))
    return new_histo

def optimize_binning(h_signal, h_background, initial_target_bin_content):
    best_significance = 0
    best_bin_edges = []

    # for target_bin_content in range(1, int(h_signal.Integral() / 2), initial_target_bin_content):
    for target_bin_content in range(1, int(h_background.Integral() / 2), initial_target_bin_content):
        bin_edges = adaptive_binning(h_background, target_bin_content)
        # bin_edges = adaptive_binning(h_signal, target_bin_content)
        h_rebinned_signal = rebin_histogram(h_signal, bin_edges)
        h_rebinned_background = rebin_histogram(h_background, bin_edges)

        signal = [h_rebinned_signal.GetBinContent(i) for i in range(1, h_rebinned_signal.GetNbinsX() + 1)]
        background = [h_rebinned_background.GetBinContent(i) for i in range(1, h_rebinned_background.GetNbinsX() + 1)]

        # significance = calculate_significance(signal, background)
        significance = calculate_asimov_significance(signal, background)
        print('target_bin_content=', target_bin_content)
        print('significance=', significance)
        print('bing_edges=', bin_edges, '\n')
        if significance > best_significance:
            best_significance = significance
            best_bin_edges = bin_edges

    return best_bin_edges, best_significance

def optimzeBinning(signalHist, bgHist, binWidth=0.001):
    #get bin range for signalHist 
    minBin = signalHist.GetMinimum()
    maxBin = signalHist.GetMaximum()
    for i in range(minBin, maxBin, binWidth):
        print(i)
        # binEdges = adaptiveBinning(signalHist, rightBinWidth)


if __name__ == '__main__':
    main()