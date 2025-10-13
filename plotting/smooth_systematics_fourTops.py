import ROOT
import numpy as np
import uproot
import statsmodels.api as sm
import os
import matplotlib.pyplot as plt

import usefulFunc as uf
import writeDatacard as wd
#!!!source setEnv_newNew.sh to set up the environment

def main():
    # input_template = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/templatesForCombine1tau1l_new.root' #Only need to offer 2018 templte, all other years will be processed automatically
    #!!!1tau1l: CMS_scale_j_FlavorPureGluon, ps_fsr， CMS_scale_j_PileUpDataMC，CMS_scale_j_RelativeSample_2018， CMS_scale_j_TimePtEta，CMS_scale_j_TimePtEta, 
    # !!!ps_isr_tt, QCDscale_ren_tt, QCDscale_fac_tt 

    #!!!1tau0l: 
    #!!!1tau2l:
    

    # processList = ['tt', 'ttH', 'ttZ', 'ttW', 'fakeTauMC']
    # sysList  = ['ps_fsr', 'CMS_scale_j_FlavorPureGluon', 'CMS_scale_j_PileUpDataMC', 'CMS_scale_j_FlavorPureQuark', 'CMS_scale_j_RelativeSample', 'CMS_scale_j_FlavorPureBottom', 'CMS_scale_j_AbsoluteMPFBias', 'CMS_res_j', 'ps_isr', 'QCDscale_ren', 'QCDscale_fac'] #process correlated systematics
    # # processList = ['tt']
    # sysList = ['ps_fsr']
    # # sysList = ['ps_isr']# process uncorrelated systematics
    # channel = '1tau1lSR'
    # sysList = ['ps_fsr', 'ps_isr', 'QCDscale_ren', 'QCDscale_fac', 'CMS_scale_j_FlavorPureGluon', 'CMS_scale_j_Fragmentation', 'CMS_btag_fixedWP_comb_bc_correlated', 'CMS_scale_j_FlavorPureQuark'] #!No btag shape uncertainty in 1tau1l channel
    # processList = ['tt', 'ttH', 'ttZ', 'ttW', 'singleTop']
    # input_template = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/combine/templatesForCombine1tau1l_new_notMCFTau.root'
    # input_template = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/combine/templatesForCombine1tau1l_new_notMCFTau_unblind.root'
    
    
    channel = '1tau0lSR'
    sysList = ['ps_fsr', 'CMS_btag_shape_hf', 'ps_isr', 'CMS_scale_j_FlavorPureGluon', 'pdf_alphas', 'QCDscale_fac', 'QCDscale_ren', 'CMS_res_j', 'CMS_scale_j_FlavorPureQuark'] 
    # processList = ['tt', 'ttH', 'ttZ', 'ttW', 'singleTop', 'WJets']
    processList = ['tt', 'ttH', 'ttZ', 'ttW',  'WJets']
    input_template = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/combine/templatesForCombine1tau0l_new_notMCFTau_unblind.root'
    
   
    years = ['2016preVFP', '2016postVFP', '2017', '2018']
    outDir = os.path.dirname(input_template) + '/results/'
    uf.checkMakeDir(outDir)
   
    dic_sys = getSmoothedDic(input_template, sysList, processList, channel, years, outDir)
    
    
   
    print(f'\nSmoothing completed for all processes and years. Saving smoothed histograms...')
    for year in years:    
        output_file = input_template.replace('.root', f'_smoothed.root')
        output_file = output_file.replace('2018', year)
        inputYear = input_template.replace('2018', year)
        with uproot.open(inputYear) as infile:
            with uproot.recreate(output_file) as outfile:
                # print('input: ', input_template, 'output:', output_file)
                for key, obj in infile.items():
                    # hist_name = key
                    hist_name = key.split(';')[0]  #!!!Fixe; or else extra ;1;1 in the hist name for the output file
                    
                    ipro, ichannel, isys = extract_parts_from_name(hist_name) 
                    # print(f'Processing histogram: {hist_name}, process: {ipro}, channel: {ichannel}, sys: {isys}')
                    
                    if isys in dic_sys and ipro in dic_sys[isys] and year in dic_sys[isys][ipro] and ichannel == channel:
                        print('!!! replace histogram:', hist_name, 'with smoothed values for', isys, ipro, year)
                        # Decide whether it's an 'Up' or 'Down' variation and replace accordingly
                        # if hist_name.contains("Up_BDT"):
                        if 'Up_BDT' in hist_name:
                            hist_data = dic_sys[isys][ipro][year][0]
                        elif 'Down_BDT' in hist_name:
                            hist_data = dic_sys[isys][ipro][year][1]
                    
                    # The original edges are used here; adjust if needed for new data shape
                        edges = obj.axes[0].edges()
                        outfile[hist_name] = (hist_data, edges)

                    else:
                        # Copy other histograms without modification
                        outfile[hist_name] = obj  
        print(f'Smoothed histograms saved to {output_file}')
                
    
    
def getSmoothedDic(input_template, sysList, processList, channel, years, outDir):
    dic_sys = {} 
    for sys in sysList:
        ifCorrelated = wd.MCSys[sys][0]
        ifProcessCorrelated = wd.MCSys[sys][3] 
        print(f'\nProcessing systematic: {sys}, correlated: {ifCorrelated}, ifProcessCorrelated: {ifProcessCorrelated}')
        dic_sys[sys] = {}
     
        for process in processList:
            dic_sys[sys][process] = {}
            
            for iyear in years:
                # if not iyear == '2018': continue
                nom_name, up_name, down_name = getHistName(sys, process, channel, iyear, ifCorrelated, ifProcessCorrelated) 
                iFile = input_template.replace('2018', iyear)
                print(f'Processing file: {iFile}')
                nominal_hist, up_hist, down_hist = getHist_uproot(iFile, nom_name, up_name, down_name) 
                
                combined_nominal, combined_var, combined_up, combined_up_var, combined_down, combined_down_var = getForSmooth(input_template, sys, process, channel, years, iyear, ifCorrelated, ifProcessCorrelated)
                bin_centers = (nominal_hist.axis().edges()[:-1] + nominal_hist.axis().edges()[1:]) / 2
                up_ratio, down_ratio = get_smoothed_up_and_down(combined_nominal, combined_var, combined_up, combined_up_var, combined_down, combined_down_var, bin_centers, 1, len(bin_centers), True)
            
                up_new = nominal_hist.values() * np.nan_to_num(up_ratio, nan=1.0)
                down_new = nominal_hist.values() * np.nan_to_num(down_ratio, nan=1.0)
                plot_smoothed_systematics(nominal_hist, up_hist.values(), down_hist.values(), up_new, down_new, outDir, sys, f'{iyear}_{process}_{channel}')
                
                dic_sys[sys][process][iyear] = (up_new, down_new)
    return dic_sys
                
                

def extract_parts_from_name(hist_name):
    # Split the string to identify known segments
    parts = hist_name.split('_')
    
    if len(parts) < 3:
        raise ValueError(f"Unexpected histogram name format: {hist_name}")

    process = parts[0]
    channel = parts[1]
    
    # Combine parts[2:-1] for sys, because sys can include multiple underscores
    # parts[-1] should be like 'sysYearUp_BDT' or 'sysUp_BDT'
    sys_and_variation = '_'.join(parts[2:-1])
    # print(sys_and_variation)#somehow BDT lost here

    # Find where 'Up' or 'Down' is in the last part
    if sys_and_variation.endswith('Up') or sys_and_variation.endswith('Down'):
        # No year segment
        # sys = sys_and_variation[:-2] if sys_and_variation.endswith('Up_BDT') else sys_and_variation[:-4]
        sys = sys_and_variation.replace('Up', '').replace('Down', '').replace('_2017', '').replace('_2018', '').replace('_2016preVFP', '').replace('_2016postVFP', '')
        
    else:
        # Last part contains a year segment
        sys = sys_and_variation
        
    return process, channel, sys
    


 
def applyRatioEachYear(input_template, nom_name, up_name, down_name, up_ratio, down_ratio, years, ifCorrelated, outDir, sys) :
    #apply to each year separately
    dict_years = {}
    for year in years:
        file_path = input_template.replace('2018', year)
        nominal_hist_year, up_hist_year, down_hist_year = getHist_uproot(file_path, nom_name, up_name, down_name)
        new_up_year = nominal_hist_year.values() * np.nan_to_num(up_ratio, nan=1.0)
        new_down_year = nominal_hist_year.values() * np.nan_to_num(down_ratio, nan=1.0)
    
        postfix = 'correlated' if ifCorrelated else 'uncorrelated'
        postfix += year
        # plot_smoothed_systematics(nominal_hist, up_hist.values(), down_hist.values(), new_up, new_down, outDir, sys, postfix)
        plot_smoothed_systematics(nominal_hist_year, up_hist_year.values(), down_hist_year.values(), new_up_year, new_down_year, outDir, sys, postfix)
        
        dict_years[year] = (new_up_year, new_down_year)
        
    return dict_years 
    
def getHistName(sys, process, channel, iyear, ifCorrelated, ifProcessCorrelated=False):
    # Get the histogram names based on the systematic, process, channel, and correlation status
    nominal = f'{process}_{channel}_BDT'
    sysName = sys if ifProcessCorrelated else f'{sys}_{process}'
    
    if ifCorrelated:
        up = f'{process}_{channel}_{sysName}Up_BDT'
        down = f'{process}_{channel}_{sysName}Down_BDT'
    else:
        up = f'{process}_{channel}_{sysName}_{iyear}Up_BDT'
        down = f'{process}_{channel}_{sysName}_{iyear}Down_BDT'
    return nominal, up, down
         
  
def getForSmooth(input_template, sys, process,  channel, years, iyear, ifCorrelated=True, ifProcessCorrelated=False):
    nominal_name, up_name, down_name = getHistName(sys, process, channel, iyear, ifCorrelated, ifProcessCorrelated)
    # print(f'Getting histograms for {sys} in year {iyear}: {nominal_name}, {up_name}, {down_name}')
    if not ifCorrelated:
        nominal_hist, up_hist, down_hist = getHist_uproot(input_template.replace('2018', iyear), nominal_name, up_name, down_name)
        combined_nominal = nominal_hist.values()
        combined_up = up_hist.values()
        combined_down = down_hist.values()
        combined_var = nominal_hist.variances()
        combined_up_var = up_hist.variances()
        combined_down_var = down_hist.variances()
        print(f'{sys} not correlated for smoothing')
    else:
        # If correlated, we need to combine the histograms across years
        combined_nominal, combined_up, combined_down = None, None, None
        combined_var, combined_up_var, combined_down_var = None, None, None
        
        for year in years:
            file_path = input_template.replace('2018', year)
            nominal_hist_year, up_hist_year, down_hist_year = getHist_uproot(file_path, nominal_name, up_name, down_name)
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

    return combined_nominal, combined_var, combined_up, combined_up_var, combined_down, combined_down_var



    
   


   
   
   
   
   
    
    
    

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
    plt.title(f'Systematic Variations and Smoothed ({sys_name}_{postfix})')
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