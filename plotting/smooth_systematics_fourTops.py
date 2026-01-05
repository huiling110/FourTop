import argparse
import ROOT
import numpy as np
import uproot
import statsmodels.api as sm
import os
import matplotlib.pyplot as plt

import usefulFunc as uf
import writeDatacard as wd
#!!!source setEnv_newNew.sh to set up the environment

# Import workflow utilities for config-based path building
try:
    from workflow_utils import (
        load_config, build_template_path, get_channel, get_options,
        get_template_suffix, get_eras
    )
    WORKFLOW_UTILS_AVAILABLE = True
except ImportError:
    WORKFLOW_UTILS_AVAILABLE = False

# Global quiet flag for controlling verbose output
QUIET = False

# ===== Channel-specific smoothing settings =====
# Systematics and processes to smooth for each channel
# Updated 2026-01-03: Added all remaining JES systematics from v3 fluctuation report
# See: plots/systematic_fluctuations/fluctuation_report.txt
CHANNEL_SMOOTHING_CONFIG = {
    '1tau1l': {
        'systematics': [
            # Theory uncertainties
            'ps_fsr', 'ps_isr', 'QCDscale_ren', 'QCDscale_fac',
            # JES - Correlated across years
            'CMS_scale_j_FlavorPureGluon',
            'CMS_scale_j_FlavorPureQuark',
            'CMS_scale_j_FlavorPureCharm',
            'CMS_scale_j_FlavorPureBottom',
            'CMS_scale_j_Fragmentation',
            'CMS_scale_j_AbsoluteScale',
            'CMS_scale_j_AbsoluteMPFBias',
            'CMS_scale_j_PileUpDataMC',
            'CMS_scale_j_PileUpPtRef',
            'CMS_scale_j_RelativeFSR',
            'CMS_scale_j_RelativeBal',
            'CMS_scale_j_RelativeSample',
            'CMS_scale_j_SinglePionECAL',    # Added Jan 3 - 42% ttZ
            'CMS_scale_j_SinglePionHCAL',    # Added Jan 3 - 41% ttZ
            'CMS_scale_j_PileUpPtBB',        # Added Jan 3 - 103% ttW!
            'CMS_scale_j_PileUpPtEC1',       # Added Jan 3 - 62% ttW
            'CMS_scale_j_RelativePtBB',      # Added Jan 3 - 42% ttZ
            # JES - Year-uncorrelated (need year suffix matching)
            'CMS_scale_j_TimePtEta',
            'CMS_scale_j_AbsoluteStat',
            'CMS_scale_j_RelativeJEREC1',    # Added Jan 3 - 91% ttW
            'CMS_scale_j_RelativeStatEC',    # Added Jan 3 - 64% ttW
            'CMS_scale_j_RelativeStatFSR',   # Added Jan 3 - 41% ttZ
            'CMS_scale_j_RelativePtEC1',     # Added Jan 3 - 40% ttZ
            # JER
            'CMS_res_j',
            # B-tagging
            'CMS_btag_fixedWP_comb_bc_correlated',
            # TES
            'CMS_scale_t_DeepTau2017v2p1_DM0_genTau',  # Added Jan 3 - 50% ttZ
            'CMS_scale_t_DeepTau2017v2p1_DM1_genTau',
            'CMS_scale_t_DeepTau2017v2p1_DM10_genTau',
            # Electron scale - Added Jan 3 - 45% tt
            'CMS_scale_e',
            # MET
            'CMS_scale_met_unclustered_energy',
            # Pileup
            'CMS_pileup',
        ],
        'processes': ['tt', 'ttbb', 'ttH', 'ttZ', 'ttW', 'singleTop']
    },
    '1tau0l': {
        'systematics': [
            # Theory uncertainties
            'ps_fsr', 'ps_isr', 'QCDscale_fac', 'QCDscale_ren',
            # JES - expanded list matching 1tau1l
            'CMS_scale_j_FlavorPureGluon',
            'CMS_scale_j_TimePtEta',
            'CMS_scale_j_RelativeSample',
            'CMS_scale_j_AbsoluteScale',
            'CMS_scale_j_PileUpPtRef',
            'CMS_scale_j_AbsoluteMPFBias',
            'CMS_scale_j_AbsoluteStat',
            'CMS_scale_j_FlavorPureQuark',
            'CMS_scale_j_FlavorPureCharm',
            'CMS_scale_j_RelativeBal',
            'CMS_scale_j_FlavorPureBottom',
            'CMS_scale_j_PileUpDataMC',
            'CMS_scale_j_Fragmentation',
            'CMS_scale_j_RelativeFSR',
            'CMS_scale_j_SinglePionHCAL',  # Added - in top impacts
            'CMS_scale_j_SinglePionECAL',  # Added
            # JER
            'CMS_res_j',
            # B-tagging (shape-based for 1tau0l) - expanded
            'CMS_btag_fullShape_hf',
            'CMS_btag_fullShape_lf',       # Added - in top impacts
            'CMS_btag_fullShape_cferr1',   # Added - in top impacts
            'CMS_btag_fullShape_cferr2',   # Added
            # TES - Added matching 1tau1l
            'CMS_scale_t_DeepTau2017v2p1_DM0_genTau',
            'CMS_scale_t_DeepTau2017v2p1_DM1_genTau',
            'CMS_scale_t_DeepTau2017v2p1_DM10_genTau',
            'CMS_scale_t_DeepTau2017v2p1_DM11_genTau',
            # MET
            'CMS_scale_met_unclustered_energy',
            # PDF
            'pdf_alphas',
            'pdf_00',  # PDF envelope - critical for ttbb (bin 12 has +22%/-43% variation)
            # Pileup
            'CMS_pileup',
        ],
        'processes': ['tt', 'ttH', 'ttZ', 'ttW', 'WJets', 'ttbb'],
    },
    '1tau2l': {
        'systematics': [
            # Theory uncertainties
            'ps_fsr', 'ps_isr', 'QCDscale_fac', 'QCDscale_ren',
            # JES - expanded list
            'CMS_scale_j_FlavorPureGluon',
            'CMS_scale_j_TimePtEta',
            'CMS_scale_j_RelativeSample',
            'CMS_scale_j_AbsoluteScale',
            'CMS_scale_j_PileUpPtRef',
            'CMS_scale_j_AbsoluteMPFBias',
            'CMS_scale_j_AbsoluteStat',
            'CMS_scale_j_FlavorPureQuark',
            'CMS_scale_j_FlavorPureCharm',
            'CMS_scale_j_RelativeBal',
            'CMS_scale_j_FlavorPureBottom',
            'CMS_scale_j_PileUpDataMC',
            'CMS_scale_j_Fragmentation',
            'CMS_scale_j_RelativeFSR',
            # JER
            'CMS_res_j',
            # Pileup
            'CMS_pileup',
        ],
        'processes': ['tt', 'ttbb', 'ttH', 'ttZ', 'ttW', 'singleTop']
    }
}

def main():
    global QUIET
    parser = argparse.ArgumentParser(description='Apply LOWESS smoothing to systematic variations')
    parser.add_argument('--quiet', '-q', action='store_true', help='Suppress verbose output')
    parser.add_argument('--config', '-c', type=str, help='Path to YAML config file')
    parser.add_argument('--template-version', '-t', type=str, default='new',
                        help='Template version suffix (e.g., "new", "v3"). Default: new')
    args = parser.parse_args()
    QUIET = args.quiet

    # Validate arguments
    if args.config and not WORKFLOW_UTILS_AVAILABLE:
        parser.error("workflow_utils not available. Install pyyaml or use hardcoded paths.")

    # Config-based settings (new workflow)
    if args.config:
        config = load_config(args.config)
        channel_name = get_channel(config)
        channel = f"{channel_name}SR"  # e.g., '1tau0lSR'
        options = get_options(config)
        suffix = get_template_suffix(config)
        years = get_eras(config)

        # Check if smoothing is enabled in config
        if not options.get('smoothing', False):
            print(f"Smoothing is disabled in config (options.smoothing=false). Skipping.")
            return

        # Replace 'new' with the specified template version if different
        if args.template_version != 'new':
            suffix = suffix.replace('_new', f'_{args.template_version}')

        # Build template path for 2018 (base year, others derived from it)
        input_template = build_template_path(config, '2018', channel_name, suffix, smoothed=False)

        # Get channel-specific smoothing settings
        if channel_name not in CHANNEL_SMOOTHING_CONFIG:
            print(f"Warning: No smoothing config for channel {channel_name}. Skipping.")
            return

        smooth_config = CHANNEL_SMOOTHING_CONFIG[channel_name]
        sysList = smooth_config['systematics']
        processList = smooth_config['processes']
        # Get additional processes that should be smoothed except for pdf_alphas
        processes_no_pdf_alphas = smooth_config.get('processes_no_pdf_alphas', [])
        # Combine all processes for the full list
        allProcessList = processList + processes_no_pdf_alphas

        if not QUIET:
            print(f"Using config: {args.config}")
            print(f"Channel: {channel}")
            print(f"Template: {input_template}")
            print(f"Systematics to smooth: {sysList}")
            print(f"Processes: {processList}")
            if processes_no_pdf_alphas:
                print(f"Processes excluded from pdf_alphas: {processes_no_pdf_alphas}")

    # ===== Legacy hardcoded settings (for backward compatibility) =====
    else:
        channel = '1tau0lSR'
        sysList = CHANNEL_SMOOTHING_CONFIG['1tau0l']['systematics']
        processList = CHANNEL_SMOOTHING_CONFIG['1tau0l']['processes']
        processes_no_pdf_alphas = CHANNEL_SMOOTHING_CONFIG['1tau0l'].get('processes_no_pdf_alphas', [])
        allProcessList = processList + processes_no_pdf_alphas
        input_template = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v9BDT1tau0l_CMSNamingComplete/combine/templatesForCombine1tau0l_new_notMCFTau_unblind.root'
        years = ['2016preVFP', '2016postVFP', '2017', '2018']
    outDir = os.path.dirname(input_template) + '/results/'
    uf.checkMakeDir(outDir)

    dic_sys = getSmoothedDic(input_template, sysList, allProcessList, channel, years, outDir, processes_no_pdf_alphas)
    
    
   
    if not QUIET:
        print(f'\nSmoothing completed for all processes and years. Saving smoothed histograms...')
    for year in years:
        output_file = input_template.replace('.root', f'_smoothed_v2.root')  # v2: preserves variances
        output_file = output_file.replace('2018', year)
        inputYear = input_template.replace('2018', year)

        # Use ROOT to properly preserve SumW2 (MC stat errors)
        # uproot loses variance info when writing with (data, edges) tuple
        infile_root = ROOT.TFile.Open(inputYear, "READ")
        outfile_root = ROOT.TFile.Open(output_file, "RECREATE")

        for key in infile_root.GetListOfKeys():
            hist_name = key.GetName()
            obj = infile_root.Get(hist_name)

            if not obj or not obj.InheritsFrom("TH1"):
                continue

            ipro, ichannel, isys = extract_parts_from_name(hist_name)

            if isys in dic_sys and ipro in dic_sys[isys] and year in dic_sys[isys][ipro] and ichannel == channel:
                if not QUIET:
                    print('!!! replace histogram:', hist_name, 'with smoothed values for', isys, ipro, year)
                if 'Up_BDT' in hist_name:
                    hist_data = dic_sys[isys][ipro][year][0]
                elif 'Down_BDT' in hist_name:
                    hist_data = dic_sys[isys][ipro][year][1]
                else:
                    # Copy unchanged
                    outfile_root.cd()
                    obj.Write()
                    continue

                # Clone and update bin contents, preserving SumW2 structure
                h_new = obj.Clone()
                for i in range(1, h_new.GetNbinsX() + 1):
                    h_new.SetBinContent(i, hist_data[i-1])
                    # Preserve original error (MC stat)
                    # h_new.SetBinError(i, obj.GetBinError(i))  # Keep original error
                outfile_root.cd()
                h_new.Write()
            else:
                # Copy other histograms without modification
                outfile_root.cd()
                obj.Write()

        infile_root.Close()
        outfile_root.Close()
        if not QUIET:
            print(f'Smoothed histograms saved to {output_file}')
                
    
    
def getSmoothedDic(input_template, sysList, processList, channel, years, outDir, processes_no_pdf_alphas=None):
    if processes_no_pdf_alphas is None:
        processes_no_pdf_alphas = []
    dic_sys = {}
    for sys in sysList:
        ifCorrelated = wd.MCSys[sys][0]
        ifProcessCorrelated = wd.MCSys[sys][3]
        if not QUIET:
            print(f'\nProcessing systematic: {sys}, correlated: {ifCorrelated}, ifProcessCorrelated: {ifProcessCorrelated}')
        dic_sys[sys] = {}

        for process in processList:
            # Skip processes that shouldn't be smoothed for pdf_alphas
            if sys == 'pdf_alphas' and process in processes_no_pdf_alphas:
                if not QUIET:
                    print(f'  Skipping {process} for {sys} (excluded in config)')
                continue
            dic_sys[sys][process] = {}

            for iyear in years:
                nom_name, up_name, down_name = getHistName(sys, process, channel, iyear, ifCorrelated, ifProcessCorrelated)
                iFile = input_template.replace('2018', iyear)
                if not QUIET:
                    print(f'Processing file: {iFile}')
                try:
                    nominal_hist, up_hist, down_hist = getHist_uproot(iFile, nom_name, up_name, down_name)
                except Exception as e:
                    if not QUIET:
                        print(f'  Skipping {process} for {sys}/{iyear}: histogram not found')
                    continue 
                
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
        if not QUIET:
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

        if not QUIET:
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
    if not QUIET:
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


if __name__ == '__main__':
    main()