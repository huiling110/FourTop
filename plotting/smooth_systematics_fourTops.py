import ROOT
import numpy as np
import uproot
import statsmodels.api as sm
import os
import matplotlib.pyplot as plt

import usefulFunc as uf
#!!!source use setEnv_newNew.sh to set up the environment

def main():
    input_template = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/templatesForCombine1tau1l_new.root'
    #!!!1tau1l: CMS_scale_j_FlavorPureGluon, ps_fsr， CMS_scale_j_PileUpDataMC，CMS_scale_j_RelativeSample_2018， CMS_scale_j_TimePtEta，CMS_scale_j_TimePtEta 
    #!!!1tau0l: 
    #!!!1tau2l:
    

    process = 'tt'
    channel = '1tau1lSR'
    sys = 'ps_fsr'
    nom_name = f'{process}_{channel}_BDT'
    up_name = f'{process}_{channel}_{sys}Up_BDT'
    down_name = f'{process}_{channel}_{sys}Down_BDT'
    ifCorrelated = False
    # ifCorrelated = True
   
    
    
    nominal_hist, up_hist, down_hist = getHist_uproot(input_template, nom_name, up_name, down_name) 
    
    if not ifCorrelated:
        # hist_forSmoothing = nominal_hist# hists for smoothing
        # up_forSmoothing = up_hist
        # down_forSmoothing = down_hist
        combined_nominal = nominal_hist.values()
        combined_up = up_hist.values()
        combined_down = down_hist.values()
        combined_var = nominal_hist.variances()
        combined_up_var = up_hist.variances()
        combined_down_var = down_hist.variances()
        print(f'{sys} not correlated for smoothing')
    else:
        # If correlated, we need to combine the histograms across years
        years = ['2016preVFP', '2016postVFP', '2017', '2018']
        combined_nominal, combined_up, combined_down = None, None, None
        combined_var, combined_up_var, combined_down_var = None, None, None
        
        for year in years:
            file_path = input_template.replace('2018', year)
            nominal_hist_year, up_hist_year, down_hist_year = getHist_uproot(file_path, nom_name, up_name, down_name)
            if combined_nominal is None:
                combined_nominal = nominal_hist_year.values()
                combined_up = up_hist_year.values()
                combined_down = down_hist_year.values()
                combined_var = nominal_hist_year.variances()
                combined_up_var = up_hist_year.variances()
                combined_down_var = down_hist_year.variances()
            else:
                combined_nominal += nominal_hist_year.values()
                combined_up += up_hist_year.values()
                combined_down += down_hist_year.values()
                combined_var += nominal_hist_year.variances()
                combined_up_var += up_hist_year.variances()
                combined_down_var += down_hist_year.variances()

        print(f'{sys} correlated for smoothing across years: {years}')
        # Create new histograms for smoothing
        # hist_forSmoothing = uproot.newhistogram(nominal_hist.axis(), values=combined_nominal)
        # up_forSmoothing = uproot.newhistogram(up_hist.axis(), values=combined_up)
        # down_forSmoothing = uproot.newhistogram(down_hist.axis(), values=combined_down)
    
    # nominal = nominal_hist.values()
    # nominal_var = nominal_hist.variances()
    # up = up_hist.values()
    # up_var = up_hist.variances()
    # down = down_hist.values()
    # down_var = down_hist.variances()
    # bin_centers = (nominal_hist.axis().edges()[:-1] + nominal_hist.axis().edges()[1:]) / 2

    # # Set parameters for smoothing
    # n_aux_bins = 1  # Number of auxiliary bins for smoothing, I think it the sub binning of the hist
    # n_reco_bins = len(bin_centers)  # Should match number of bins in histogram
   
    
    # # Apply smoothing
    # new_up, new_down = get_smoothed_up_and_down(
    #     nominal, nominal_var,
    #     up, up_var,
    #     down, down_var,
    #     bin_centers,
    #     n_aux_bins,
    #     n_reco_bins,
    #     ratio_only=False
    # )
    bin_centers = (nominal_hist.axis().edges()[:-1] + nominal_hist.axis().edges()[1:]) / 2
    up_ratio, down_ratio = get_smoothed_up_and_down(combined_nominal, combined_var, combined_up, combined_up_var, combined_down, combined_down_var, bin_centers, 1, True)
    # up_ratio, down_ratio = get_smoothed_up_and_down_new( hist_forSmoothing, up_forSmoothing, down_forSmoothing)
    
    #apply the ratio to the nominal histogram
    nominal = nominal_hist.values()
    new_up = nominal * np.nan_to_num(up_ratio, nan=1.0)
    new_down = nominal * np.nan_to_num(down_ratio, nan=1.0)
    
    
   
    outDir = os.path.dirname(input_template) + '/results/'
    uf.checkMakeDir(outDir)
    postfix = 'correlated' if ifCorrelated else 'uncorrelated'
    plot_smoothed_systematics(nominal_hist, up_hist.values(), down_hist.values(), new_up, new_down, outDir, sys, postfix)


    #???What about fakeTauMC? 
    # plotName = 'smoothed_'
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
    
   

# def process_year(input_template, year, nom_name, up_name, down_name, bin_centers, n_aux_bins, n_reco_bins, smoothing_ratio):
#     # Load histograms for a given year
#     file_path = input_template.replace('2018', year)
#     nominal_hist, up_hist, down_hist = getHist_uproot(file_path, nom_name, up_name, down_name)
#     nominal = nominal_hist.values()
#     nominal_var = nominal_hist.variances()
#     up = up_hist.values()
#     up_var = up_hist.variances()
#     down = down_hist.values()
#     down_var = down_hist.variances()
    
#     # Apply smooth ratio obtained from the combined years
#     new_up = nominal * np.nan_to_num(1 + smoothing_ratio * (up - nominal) / nominal, nan=1.0)
#     new_down = nominal * np.nan_to_num(1 + smoothing_ratio * (down - nominal) / nominal, nan=1.0)
    
#     # Output directory setup
#     outDir = os.path.dirname(file_path) + '/results/'
#     uf.checkMakeDir(outDir)
#     plot_smoothed_systematics(nominal_hist, up, down, new_up, new_down, outDir, sys)
    
#     # Write results to new ROOT file
#     output_file = file_path.replace('.root', f'_smoothed.root')
#     with uproot.recreate(output_file) as f:
#         edges = nominal_hist.axis().edges()
#         f[up_name] = (new_up, edges)
#         f[down_name] = (new_down, edges)
#         f[nom_name] = nominal_hist  # Copy original nominal
#     print(f'Smoothed histograms saved to {output_file}')

# def smooth_correlated(input_template, nom_name, up_name, down_name, ifCorrelated):
#     # Define years to process
#     years = ['2016preVFP', '2016postVFP', '2017', '2018']

#     if ifCorrelated:
#         # Combine histograms across years
#         combined_nominal, combined_nominal_var = None, None
#         combined_up, combined_up_var = None, None
#         combined_down, combined_down_var = None, None
        
#         for year in years:
#             file_path = input_template.replace('2018', year)
#             nominal_hist, up_hist, down_hist = getHist_uproot(file_path, nom_name, up_name, down_name)
#             if combined_nominal is None:
#                 combined_nominal = nominal_hist.values()
#                 combined_nominal_var = nominal_hist.variances()
#                 combined_up = up_hist.values()
#                 combined_up_var = up_hist.variances()
#                 combined_down = down_hist.values()
#                 combined_down_var = down_hist.variances()
#             else:
#                 combined_nominal += nominal_hist.values()
#                 combined_nominal_var += nominal_hist.variances()
#                 combined_up += up_hist.values()
#                 combined_up_var += up_hist.variances()
#                 combined_down += down_hist.values()
#                 combined_down_var += down_hist.variances()
        
#         # Calculate smoothed ratio based on combined data
#         bin_centers = (nominal_hist.axis().edges()[:-1] + nominal_hist.axis().edges()[1:]) / 2
#         n_aux_bins = 1
#         n_reco_bins = len(bin_centers)
#         smoothing_ratio = get_smoothed_up_and_down(
#             combined_nominal, combined_nominal_var,
#             combined_up, combined_up_var,
#             combined_down, combined_down_var,
#             bin_centers, n_aux_bins, n_reco_bins,
#             ratio_only=True
#         )[0]  # Assuming up and down have similar smoothing ratios
        
#         # Process each year with the obtained smoothing_ratio
#         for year in years:
#             process_year(input_template, year, nom_name, up_name, down_name, bin_centers, n_aux_bins, n_reco_bins, smoothing_ratio)
#     else:
#         # Process each year independently without correlation
#         for year in years:
#             process_year(input_template, year, nom_name, up_name, down_name, None, None, None, None)

   
   
   
   
   
    
    
    

def getHist_uproot(input_template, nom_name, up_name, down_name):
    with uproot.open(input_template) as f:
        # Get nominal histogram
        nominal_hist = f[nom_name]
        # Get up variation histogram
        up_hist = f[up_name]
        # Get down variation histogram
        down_hist = f[down_name]
        return nominal_hist, up_hist, down_hist


 
def plot_smoothed_systematics(nominal_hist, up, down, new_up, new_down, outDir, sys_name='', postfix=''):
    # Extract the nominal histogram values, variabilities (errors), and bin edges
    nominal_values, bin_edges = nominal_hist.to_numpy()
    nominal_errors = np.sqrt(nominal_values)  # Statistical uncertainty

    # Calculate bin centers for plotting
    bin_centers = 0.5 * (bin_edges[:-1] + bin_edges[1:])

    plt.figure(figsize=(10, 8))
    
    # Plot nominal histogram with error bars
    plt.errorbar(bin_centers, nominal_values, yerr=nominal_errors, fmt='o', label='Nominal', color='black')

    # Plot original up and down variations
    plt.step(bin_centers, up, where='mid', label=f'{sys_name} Up', linewidth=2, color='red', alpha=0.7)
    plt.step(bin_centers, down, where='mid', label=f'{sys_name} Down', linewidth=2, color='blue', alpha=0.7)

    # Plot smoothed up and down variations
    plt.step(bin_centers, new_up, where='mid', label=f'Smoothed {sys_name} Up', linewidth=2, color='green', linestyle='--', alpha=0.8)
    plt.step(bin_centers, new_down, where='mid', label=f'Smoothed {sys_name} Down', linewidth=2, color='magenta', linestyle='--', alpha=0.8)

    # Set y-axis to log scale
    plt.yscale('log')
    
    # Add legend and labels
    plt.xlabel('Bin Centers')
    plt.ylabel('Counts')
    plt.title(f'Systematic Variations and Smoothed ({sys_name})')
    plt.legend(loc='best')

    # Save the figure
    plt.tight_layout()
    plt.savefig(f'{outDir}systematics_comparison_{sys_name}_{postfix}.png')
    plt.close()    
    print(f'Smoothed systematics plot saved to {outDir}systematics_comparison_{sys_name}_{postfix}.png')
    
 
    
    
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



def get_smoothed_up_and_down_new(nom_hist, up_hist, down_hist):
    nom = nom_hist.values()
    nom_var = nom_hist.variances()
    up = up_hist.values()
    up_var = up_hist.variances()
    down = down_hist.values()
    down_var = down_hist.variances()
    
    bin_centers = (nom_hist.axis().edges()[:-1] + nom_hist.axis().edges()[1:]) / 2
    n_aux_bins = 1  # Number of auxiliary bins for smoothing
    n_reco_bins = len(bin_centers)  # Should match number of bins i
    
    half_ratio = np.where(nom > 0., up / nom, 1.)
    alt_half_ratio = np.where(nom > 0., down / nom, 1.)
    ratio_diff = (half_ratio - alt_half_ratio) / 2. # Calculate the difference in ratios
    diff_smooth = smooth_ratio(ratio_diff, bin_centers, n_aux_bins, n_reco_bins)
    
    up_scale = get_smoothed_scale_factor(diff_smooth, nom, up, nom_var, up_var)
    down_scale = get_smoothed_scale_factor(diff_smooth, nom, down, nom_var, down_var)
    up_ratio = (1 + up_scale * diff_smooth)
    down_ratio = (1 + down_scale * diff_smooth)
    
    return up_ratio, down_ratio

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