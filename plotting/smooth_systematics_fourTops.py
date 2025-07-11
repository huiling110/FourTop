import ROOT
import numpy as np
import uproot
import statsmodels.api as sm
import os

import usefulFunc as uf
#!!!source use setEnv_newNew.sh to set up the environment

def main():
    input_template = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/templatesForCombine1tau1l_new.root'
    
#!!!Modify the moothing algorithm     

# def process_systematics(input_file, output_file):
    process = 'tt'
    channel = '1tau1lSR'
    sys = 'ps_fsr'
    nom_name = f'{process}_{channel}_BDT'
    up_name = f'{process}_{channel}_{sys}Up_BDT'
    down_name = f'{process}_{channel}_{sys}Down_BDT'
   
    
    nominal_hist, up_hist, down_hist = getHist_uproot(input_template, nom_name, up_name, down_name) 
    nominal = nominal_hist.values()
    nominal_var = nominal_hist.variances()
    up = up_hist.values()
    up_var = up_hist.variances()
    down = down_hist.values()
    down_var = down_hist.variances()
    bin_centers = (nominal_hist.axis().edges()[:-1] + nominal_hist.axis().edges()[1:]) / 2
    # Read input ROOT file
    # with uproot.open(input_template) as f:
    #     # Get nominal histogram (replace 'nominal_hist' with your actual hist name)
    #     nominal_hist = f[nom_name]
    #     # print(type(nominal_hist)) #<class 'uproot.models.TH.Model_TH1D_v3'>
    #     nominal = nominal_hist.values()
    #     nominal_var = nominal_hist.variances()
        
    #     # Get up variation (replace 'up_hist' with your actual hist name)
    #     up_hist = f[up_name] 
    #     up = up_hist.values()
    #     up_var = up_hist.variances()
        
    #     # Get down variation (replace 'down_hist' with your actual hist name)
    #     down_hist = f[down_name]
    #     down = down_hist.values()
    #     down_var = down_hist.variances()

    #     # Get bin centers from nominal histogram
    #     edges = nominal_hist.axis().edges()
    #     bin_centers = (edges[:-1] + edges[1:]) / 2

    # Set parameters for smoothing
    n_aux_bins = 1  # Number of auxiliary bins for smoothing, I think it the sub binning of the hist
    n_reco_bins = len(bin_centers)  # Should match number of bins in histogram
    
    # Apply smoothing
    new_up, new_down = get_smoothed_up_and_down(
        nominal, nominal_var,
        up, up_var,
        down, down_var,
        bin_centers,
        n_aux_bins,
        n_reco_bins,
        ratio_only=False
    )
   
    # outDir = uf.
    outDir = os.path.dirname(input_template) + '/results/'
    uf.checkMakeDir(outDir)
    print(outDir)
    # plot_smoothed_systematics(nominal_hist, up_hist, down_hist, new_up, new_down, outDir, sys)



    output_file = input_template.replace('.root', f'_smoothed.root')
    # Write results to new ROOT file
    with uproot.recreate(output_file) as f:
        # Use original bin edges
        edges = nominal_hist.axis().edges()
        
        # Store smoothed histograms
        f[up_name] = (new_up, edges)
        f[down_name] = (new_down, edges)
        f[nom_name] = nominal_hist  # Copy original nominal
    print(f'Smoothed histograms saved to {output_file}')

def getHist_uproot(input_template, nom_name, up_name, down_name):
    with uproot.open(input_template) as f:
        # Get nominal histogram
        nominal_hist = f[nom_name]
        # Get up variation histogram
        up_hist = f[up_name]
        # Get down variation histogram
        down_hist = f[down_name]
    # Convert uproot histograms to ROOT TH1 objects
        return nominal_hist, up_hist, down_hist

def plot_smoothed_systematics(nominal_hist, up_hist, down_hist, new_up, new_down, outDir, sys_name=''):
    # Create a canvas
    canvas = ROOT.TCanvas("canvas", "Systematics Comparison", 800, 600)
    canvas.SetLogy()  # Set y-axis to logarithmic scale

    # Set drawing style for histograms
    up_hist.SetLineColor(ROOT.kRed)  # Original up: red
    down_hist.SetLineColor(ROOT.kBlue)  # Original down: blue
    new_up.SetLineColor(ROOT.kGreen+2)  # Smoothed up: green
    new_down.SetLineColor(ROOT.kMagenta+2)  # Smoothed down: magenta

    # Set line width for better visibility
    up_hist.SetLineWidth(2)
    down_hist.SetLineWidth(2)
    new_up.SetLineWidth(2)
    new_down.SetLineWidth(2)

    # Draw all histograms
    nominal_hist.Draw("HIST")  # Draw nominal histogram
    up_hist.Draw("HIST SAME")  # Draw original "up" variation
    down_hist.Draw("HIST SAME")  # Draw original "down" variation
    new_up.Draw("HIST SAME")  # Draw smoothed "up" variation
    new_down.Draw("HIST SAME")  # Draw smoothed "down" variation

    # Add legend
    legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
    legend.AddEntry(up_hist, "Original Up", "l")
    legend.AddEntry(down_hist, "Original Down", "l")
    legend.AddEntry(new_up, "Smoothed Up", "l")
    legend.AddEntry(new_down, "Smoothed Down", "l")
    legend.Draw()

    # Save the canvas
    canvas.SaveAs(f"{outDir}/systematics_comparison.png")
    canvas.Close()

    
    
 
    
    
def smooth_ratio(ratio, bin_centers, n_aux_bins, n_reco_bins):
    '''from ttbb'''
    # smooth the ratio
    #n_aux_bins: represents the number of auxiliary bins, which might serve as a higher-level categorization or segmentation of your data 
    for iaux in range(n_aux_bins):
        sel_bins = slice(iaux * n_reco_bins, (iaux+1) * n_reco_bins) #explain: 
        if len(ratio.shape) == 1:
            # background processes are separate
            if n_reco_bins > 5:#???Why only smooth if more than 5 bins? doesn't make sense to me
                ratio[sel_bins] = sm.nonparametric.lowess(ratio[sel_bins], bin_centers, xvals=bin_centers)
                # Locally Weighted Scatterplot Smoothing (LOWESS);
        else:
            # signal processes are a list of processes
            for iproc in range(len(ratio)):
                if n_reco_bins > 5:
                    ratio[iproc][sel_bins] = sm.nonparametric.lowess(ratio[iproc][sel_bins], bin_centers, xvals=bin_centers)

    return ratio


def get_smoothed_up_and_down( nom_hist, nom_variance, up_hist, up_variance, down_hist, down_variance, bin_centers, n_aux_bins, n_reco_bins, ratio_only=False ):
    #from ttbb
    '''use up and down variations of a systematic to smooth them, by using the difference in each of their ratios to the nominal.
       the shapes of the systematic templates are constrained to be opposite to each other, up to some overall scaling.
      Taken from:
            https://cms.cern.ch/iCMS/jsp/openfile.jsp?tp=draft&files=AN2018_077_v4.pdf'''

    half_ratio = np.where( nom_hist > 0., up_hist / nom_hist, 1. )
    alt_half_ratio = np.where( nom_hist > 0., down_hist / nom_hist, 1. )
    ratio_diff = (half_ratio - alt_half_ratio)/2.
    diff_smooth = smooth_ratio( ratio_diff, bin_centers, n_aux_bins, n_reco_bins )

    up_scale = get_smoothed_scale_factor( diff_smooth, nom_hist, up_hist, nom_variance, up_variance)
    down_scale = get_smoothed_scale_factor( diff_smooth, nom_hist, down_hist, nom_variance, down_variance)

    up_ratio = (1 + up_scale*diff_smooth)
    down_ratio = ( 1 + down_scale*diff_smooth)
    if ratio_only:
        return up_ratio, down_ratio

    new_var_up = nom_hist * np.nan_to_num(up_ratio, nan=1.0)
    new_var_down = nom_hist * np.nan_to_num(down_ratio, nan=1.0)
    return new_var_up, new_var_down

def get_smoothed_scale_factor( smoothed_ratio_diff, nom_hist, var_hist, nom_var, var_var):
    '''determine an overall systematic template smoothing which minimizes the chi-squared between
        the smoothed systematic and the unsmoothed template it is derived from.
        Taken from:
             https://cms.cern.ch/iCMS/jsp/openfile.jsp?tp=draft&files=AN2018_077_v4.pdf'''

    total_var = np.sqrt( nom_var + var_var)
    unsmoothed_diff = var_hist - nom_hist
    ratio_factor = smoothed_ratio_diff * nom_hist
    numerator = np.sum( ratio_factor * unsmoothed_diff / total_var )
    denominator = np.sum( (ratio_factor / np.sqrt(total_var))**2 )
    return numerator/denominator


def get_smoothed_up_and_down( nom_hist, nom_variance, up_hist, up_variance, down_hist, down_variance, bin_centers, n_aux_bins, n_reco_bins, ratio_only=False ):
    '''use up and down variations of a systematic to smooth them, by using the difference in each of their ratios to the nominal.
       the shapes of the systematic templates are constrained to be opposite to each other, up to some overall scaling.
      Taken from:
            https://cms.cern.ch/iCMS/jsp/openfile.jsp?tp=draft&files=AN2018_077_v4.pdf'''

    half_ratio = np.where( nom_hist > 0., up_hist / nom_hist, 1. )
    alt_half_ratio = np.where( nom_hist > 0., down_hist / nom_hist, 1. )
    ratio_diff = (half_ratio - alt_half_ratio)/2.
    diff_smooth = smooth_ratio( ratio_diff, bin_centers, n_aux_bins, n_reco_bins )

    up_scale = get_smoothed_scale_factor( diff_smooth, nom_hist, up_hist, nom_variance, up_variance)
    down_scale = get_smoothed_scale_factor( diff_smooth, nom_hist, down_hist, nom_variance, down_variance)

    up_ratio = (1 + up_scale*diff_smooth)
    down_ratio = ( 1 + down_scale*diff_smooth)
    if ratio_only:
        return up_ratio, down_ratio

    new_var_up = nom_hist * np.nan_to_num(up_ratio, nan=1.0)
    new_var_down = nom_hist * np.nan_to_num(down_ratio, nan=1.0)
    return new_var_up, new_var_down

if __name__ == '__main__':
    main()