#!/usr/bin/env python3

import os
from argparse import ArgumentParser

import numpy as np
import pandas as pd

import matplotlib; matplotlib.use('agg')
import matplotlib.pyplot as plt
import seaborn as sns
import mplhep
import mplhep.cms

import ttbb_unfolding.utils as tu

import statsmodels.api as sm
import scipy
import re
import copy


def check_compatibility_pval(nom_hist, nom_variance, var_hist, var_variance, p_val_threshold=0.05, norm_threshold=0.01):
    # signal processes are an array of entries, so loop over them separately
    if len(nom_hist.shape) > 1:
        template_types= []
        norms = []
        for nh, nv, vh, vv in zip(nom_hist, nom_variance, var_hist, var_variance):
            comp, norm = check_compatibility_pval(nh, nv, vh, vv, p_val_threshold, norm_threshold)
            template_types += comp
            norms += norm
        return template_types, norms

    # get norm = ratio of syst/nominal
    norm, norm_err = tu.get_norm_and_error(nom_hist, nom_variance, var_hist, var_variance)

    # calculate chi2 value and associated pvalue
    chi_sq, p_val = tu.chi2_ww(nom_hist, nom_variance, var_hist, var_variance)

    # determine template type
    template_type = tu.SystType.SHAPE
    if p_val > p_val_threshold:
        #print("shape contribution negligible, converting into rate")
        template_type = tu.SystType.RATE
        if abs(norm - 1.) < norm_err:
            #print(f"normalzation {norm:.3f} +- {norm_err:.3f} negligible")
            template_type = tu.SystType.DELETE
        elif abs(norm - 1.) < norm_threshold:
            #print(f"normalization {norm:.3f} negligible")
            template_type = tu.SystType.DELETE

    return [template_type], [norm]

def get_combine_shape_effect(h1, h2):
    shape_effect = 2*np.abs(h2 - h1) /( np.abs(h2) + np.abs(h1) )
    return shape_effect.sum()


def check_compatibility_combine(nom_hist, nom_variance, var_hist, var_variance, shape_threshold=0.001, norm_threshold=0.01):
    # signal processes are an array of entries, so loop over them separately
    if len(nom_hist.shape) > 1:
        template_types = []
        norms = []
        for nh, nv, vh, vv in zip(nom_hist, nom_variance, var_hist, var_variance):
            comp, norm = check_compatibility_combine(nh, nv, vh, vv, shape_threshold, norm_threshold)
            template_types += comp
            norms += norm
        return template_types, norms

    # get norm
    norm, norm_err = tu.get_norm_and_error(nom_hist, nom_variance, var_hist, var_variance)

    # calculate shape effect via combine formula
    # https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/part3/validation/#uncertainty-probably-has-no-genuine-shape-effect
    shape_effect = get_combine_shape_effect(nom_hist, var_hist/norm)

    # determine template type
    template_type = tu.SystType.SHAPE
    if shape_effect < shape_threshold:
        #print("shape contribution negligible, converting into rate")
        template_type = tu.SystType.RATE
        if abs(norm - 1.) < norm_err:
            #print(f"normalzation {norm:.3f} +- {norm_err:.3f} negligible")
            template_type = tu.SystType.DELETE
        elif abs(norm - 1.) < norm_threshold:
            #print(f"normalization {norm:.3f} negligible")
            template_type = tu.SystType.DELETE

    return [template_type], [norm]


def get_bin_centers(edges):
    return (edges[1:] + edges[:-1])/2.


def smooth_ratio(ratio, bin_centers, n_aux_bins, n_reco_bins):
    # smooth the ratio
    for iaux in range(n_aux_bins):
        sel_bins = slice(iaux * n_reco_bins, (iaux+1) * n_reco_bins)
        if len(ratio.shape) == 1:
            # background processes are separate
            if n_reco_bins > 5:
                ratio[sel_bins] = sm.nonparametric.lowess(ratio[sel_bins], bin_centers, xvals=bin_centers)
        else:
            # signal processes are a list of processes
            for iproc in range(len(ratio)):
                if n_reco_bins > 5:
                    ratio[iproc][sel_bins] = sm.nonparametric.lowess(ratio[iproc][sel_bins], bin_centers, xvals=bin_centers)

    return ratio



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

def add_compatibility_and_norm(df_row, compatibility, norm):
    for i, val in enumerate(compatibility):
        df_row["template_type"][i] = val
    for i, val in enumerate(norm):
        df_row["template_norm"][i] = val

def smooth_systematic_global(syst_df, nom_df, syst, reco_bins, aux_bins, alt_syst_df=None):
    do_alt = alt_syst_df is not None

    # get bin centers and bin numbers
    bin_centers = get_bin_centers(np.array(reco_bins))
    n_reco_bins = len(reco_bins) - 1
    n_aux_bins = len(aux_bins) - 1

    # loop over different hist types available
    for hist_type in syst_df["hist_type"].unique():
        # get dfs for nominal and variation with all eras and channels
        nom_hist_df = nom_df[(nom_df.hist_type == hist_type)]
        var_hist_df = syst_df[(syst_df.hist_type == hist_type)]
        if do_alt:
            hist_type_mask = (alt_syst_df.hist_type == hist_type)
            alt_var_hist_df = alt_syst_df.loc[hist_type_mask,:]
        assert len(nom_hist_df) == len(var_hist_df)

        # sum over eras and channels
        var_hist = np.array([h.view().value for h in var_hist_df["hist"]]).sum(axis=0)
        var_variance = np.array([h.view().variance for h in var_hist_df["hist"]]).sum(axis=0)
        nom_hist = np.array([h.view().value for h in nom_hist_df["hist"]]).sum(axis=0)
        nom_variance = np.array([h.view().variance for h in nom_hist_df["hist"]]).sum(axis=0)
        if do_alt:
            alt_var_hist = np.array([h.view().value for h in alt_var_hist_df["hist"]]).sum(axis=0)
            alt_var_variance = np.array([h.view().variance for h in alt_var_hist_df["hist"]]).sum(axis=0)

        # check compatibility between nominal histogram and varied histogram
        # NOTE: this uses the default variation and not the smoothed one!
        compatibility, norm = check_compatibility_pval(nom_hist, nom_variance, var_hist, var_variance)
        if do_alt:
            alt_compatibility, alt_norm = check_compatibility_pval(nom_hist, nom_variance, alt_var_hist, alt_var_variance)

        # get a smoothed ratio
        if do_alt:
            up_ratio, down_ratio = get_smoothed_up_and_down( nom_hist, nom_variance,
                                                                 var_hist, var_variance,
                                                                 alt_var_hist, alt_var_variance,
                                                                 bin_centers, n_aux_bins, n_reco_bins,
                                                                 ratio_only=True)

        else:
            ratio = smooth_ratio(np.where(nom_hist > 0., var_hist / nom_hist, 1.), bin_centers, n_aux_bins, n_reco_bins)

        # loop over single histograms per era and channel and apply the averaged ratio
        for idx, entry in var_hist_df.iterrows():
            single_nom_hist_df = nom_hist_df[(nom_hist_df.era == entry["era"]) & (nom_hist_df.channel == entry["channel"])]
            if len(single_nom_hist_df) != 1:
                raise Exception(f"Could not find the nominal histogram for era={entry['era']}, channel={entry['channel']}")
            nom_hist = np.maximum(single_nom_hist_df["hist"].iloc[0].view().value, 0.)

            if do_alt:
                alt_mask = (alt_var_hist_df.era == entry["era"]) & (alt_var_hist_df.channel == entry["channel"])
                sel_alt_hist_df = alt_var_hist_df.loc[alt_mask,:]
                if len(sel_alt_hist_df) != 1:
                    raise Exception(f"Could not find the down variation histogram for era={entry['era']}, channel={entry['channel']}, found length {len(sel_alt_hist_df)}. {sel_alt_hist_df}")
                single_alt_hist_df = sel_alt_hist_df.iloc[0]

                new_var_up = nom_hist * np.nan_to_num(up_ratio, nan=1.0)
                new_var_down = nom_hist * np.nan_to_num(down_ratio, nan=1.0)
                entry["hist_lowess"].view().value = new_var_up
                single_alt_hist_df["hist_lowess"].view().value = new_var_down
            else:
                new_var = nom_hist * np.nan_to_num(ratio, nan=1.0)
                entry["hist_lowess"].view().value = new_var

            add_compatibility_and_norm(entry, compatibility, norm)
            if do_alt:
                add_compatibility_and_norm( single_alt_hist_df, alt_compatibility, alt_norm)

def smooth_systematic(syst_df, nom_df, syst, reco_bins, aux_bins, alt_syst_df=None):
    do_alt = alt_syst_df is not None
    # get bin centers and bin numbers
    bin_centers = get_bin_centers(np.array(reco_bins))
    n_reco_bins = len(reco_bins) - 1
    n_aux_bins = len(aux_bins) - 1

    # loop over all channels and eras
    for (era, channel), df in syst_df.groupby(["era", "channel"]):

        # if it is a signal there are multiple entries, reco matrices and combined histograms
        for idx, entry in df.iterrows():
            # get the variation histogram
            var_hist = np.maximum(entry["hist"].view().value, 0.)
            var_variance = np.maximum(entry["hist"].view().variance, 0.)

            # figure out which is the nominal histogram for that
            nom_hist_df = nom_df[(nom_df.era == era) & (nom_df.channel == channel) & (nom_df.hist_type == entry["hist_type"])]
            if len(nom_hist_df) != 1:
                raise Exception(f"Could not find the nominal histogram for era={era}, channel={channel}")
            nom_hist = np.maximum(nom_hist_df["hist"].iloc[0].view().value, 0.)
            nom_variance = np.maximum(nom_hist_df["hist"].iloc[0].view().variance, 0.)

            if do_alt:
                alt_mask = (alt_syst_df.era == era) & (alt_syst_df.channel == channel) & (alt_syst_df.hist_type == entry["hist_type"])
                sel_alt_hist_df = alt_syst_df[alt_mask]
                if len(sel_alt_hist_df) != 1:
                    raise Exception(f"Could not find the alt histogram for era={era}, channel={channel}: {sel_alt_hist_df}")
                alt_hist_df = sel_alt_hist_df.iloc[0]
                alt_hist = np.maximum(alt_hist_df["hist"].view().value, 0.)
                alt_variance = np.maximum(alt_hist_df["hist"].view().variance, 0.)


            # build the ratio
            if do_alt:
                new_var_up, new_var_down = get_smoothed_up_and_down( nom_hist, nom_variance,
                                                                     var_hist, var_variance,
                                                                     alt_hist, alt_variance,
                                                                     bin_centers, n_aux_bins, n_reco_bins )

                entry["hist_lowess"].view().value = new_var_up
                alt_hist_df["hist_lowess"].view().value = new_var_down
            else:
                ratio = smooth_ratio(np.where(nom_hist > 0., var_hist / nom_hist, 1.), bin_centers, n_aux_bins, n_reco_bins)
                new_var = nom_hist * np.nan_to_num(ratio, nan=1.0)
                entry["hist_lowess"].view().value = new_var

            # check compatibility between nominal histogram and smoothed variation
            if do_alt:
                compatibility, norm = check_compatibility_combine(nom_hist, nom_variance, new_var_up, var_variance)
                alt_compatibility, alt_norm = check_compatibility_combine(nom_hist, nom_variance, new_var_down, alt_variance)
                add_compatibility_and_norm(entry, compatibility, norm)
                add_compatibility_and_norm( alt_hist_df, alt_compatibility, alt_norm)
            else:
                compatibility, norm = check_compatibility_combine(nom_hist, nom_variance, new_var, var_variance)
                add_compatibility_and_norm(entry, compatibility, norm)


def get_reco_and_aux_bins(df, obs, hist_store):
    # get info about reco bins
    any_reco = df[(df.hist_type == tu.HistType.RECO) & (df.observable == obs)].iloc[0]
    reco_name = any_reco["plot_name"]  # any reco histogram
    reco_bins = hist_store.plots_cfg["reco_plots"][reco_name]["bins"]

    # get info about auxiliary obs.
    any_mig_mat = df[(df.hist_type == tu.HistType.MIG_RECO) & (df.observable == obs)].iloc[0]
    aux_name = any_mig_mat["aux_name"]
    aux_config = hist_store.plots_cfg.get("auxiliary_observables", None)
    if aux_config is not None:
        aux_bins = aux_config[aux_name]["bins"]
    else: #provide some meaningless bin edges for a 1-binned histogram, since there is no auxiliary observable
        aux_bins = [0.,1.]
    return reco_bins, aux_bins


def plot_syst_compatibility(values, out_file):
    x_labels = sorted(list(values.keys()), key=lambda x: x[::-1])
    y_labels = set()
    for k in x_labels:
        y_labels |= set(values[k].keys())
    y_labels = sorted(list(y_labels), key=lambda x: x[::-1])

    matrix = []
    for obs in x_labels:
        row = []
        for nuis in y_labels:
            val = values[obs].get(nuis, np.nan)
            row.append( values[obs].get(nuis, np.nan) )
        matrix.append( np.array(row) )
    matrix = np.array(matrix)

    with plt.style.context(mplhep.style.CMS):
        fig, ax = plt.subplots(figsize=(10+len(y_labels),10+len(x_labels)))
        sns.heatmap(matrix, vmin=-1, vmax=1.2, center=0, square=True, annot=True,
            fmt=".2f", ax=ax, cbar=False, xticklabels=y_labels, yticklabels=x_labels)
        ax.minorticks_off()
        fig.tight_layout()
        fig.savefig(out_file)
        print(f"figure saved at {out_file}")
        plt.close(fig)

def get_type_plot_value(typ, norm):
    if typ == tu.SystType.SHAPE:
        return -1
    elif typ == tu.SystType.DELETE:
        return 0
    else:
        return norm

def plot_global_systs(df, plot_path):
    values = {}
    for (obs, process, syst), obs_df in df.groupby(["observable", "process", "syst"]):
        if not obs in values:
            values[obs] = {}

        # if we have a length of two that means there is a migration matrix and a combined histogram for signal
        if len(obs_df["hist_type"].unique()) == 2:
            # only use the migration matrix
            obs_df = obs_df[(obs_df.hist_type == tu.HistType.MIG_RECO)]

        # there should be in principle now eight entries per df only differing in era and channel
        # hard-code it for now with that expectation
        if len(obs_df) != 8:
            raise Exception(f"invalid df for {obs}, {process}, {syst}: {obs_df}")

        # values are the same of each era and channel so just pick the first
        template_type = obs_df.iloc[0]["template_type"]
        template_norm = obs_df.iloc[0]["template_norm"]
        for i, (typ, norm) in enumerate(zip(template_type, template_norm)):
            if len(template_type) != 1:
                y = f"{process}_bin_{i}__{syst}"
            else:
                y = f"{process}__{syst}"
            values[obs][y] = get_type_plot_value(typ, norm)

    out_file = os.path.join(plot_path, "systematics_global.pdf")
    plot_syst_compatibility(values, out_file)

def plot_each_obs(systs, df, plot_path):
    for (obs), obs_df in df.groupby(["observable"]):
        values = {}
        for (era, channel, process, syst), single_df in obs_df.groupby(["era", "channel", "process", "syst"]):
            # if we have a length of two that means there is a migration matrix and a combined histogram for signal
            if len(single_df) == 2:
                # only use the migration matrix 
                single_df = single_df[single_df.hist_type == tu.HistType.MIG_RECO]

            if len(single_df) != 1:
                raise Exception(f"invalid df for {obs}: {single_df}")

            template_type = single_df.iloc[0]["template_type"]
            template_norm = single_df.iloc[0]["template_norm"]
            for i, (typ, norm) in enumerate(zip(template_type, template_norm)):
                if len(template_type) != 1:
                    x = f"{channel}__{era}__{process}_bin_{i}"
                else:
                    x = f"{channel}__{era}__{process}"
                if not x in values:
                    values[x] = {}
                values[x][syst] = get_type_plot_value(typ, norm)

        out_file = os.path.join(plot_path, f"systematics_{obs}.pdf")
        plot_syst_compatibility(values, out_file)


def symmetrize_template_types(df, syst_pairs):
    # loop over syst pairs
    for syst in syst_pairs:

        # split df for systs
        syst_df = df.loc[df.syst.isin(syst_pairs[syst]), :]

        # loop over observables processes eras and channels
        for (obs, process, era, channel), temp_df in syst_df.groupby(["observable", "process", "era", "channel"]):

            # might have migration matrix and reco hist for signal, so loop also over hist types
            for hist_type in temp_df["hist_type"].unique():
                symm_df = temp_df[temp_df.hist_type == hist_type]
                if len(symm_df) != len(syst_pairs[syst]):
                    raise Exception(f"invalid df for {obs} {process} {era} {channel} {syst}: {symm_df}")

                # get template types of variations that belong together
                template_types = np.array([np.array(values) for values in symm_df["template_type"].values])

                # homogenize compatibilities
                if np.all(template_types == tu.SystType.SHAPE):
                    continue # homogenous shape effects
                elif np.any(template_types == tu.SystType.SHAPE):
                    #print(f"some templates have shape effect, converting all to shape")
                    for i, row in symm_df.iterrows():
                        for j in range(len(row["template_type"])):
                            row["template_type"][j] = tu.SystType.SHAPE
                elif np.all(template_types == tu.SystType.RATE):
                    continue # all templates already have rates
                elif np.any(template_types == tu.SystType.RATE):
                    #print(f"at least one template has a rate effect")
                    for i, row in symm_df.iterrows():
                        for j in range(len(row["template_type"])):
                            row["template_type"][j] = tu.SystType.RATE


def transfer_nuisances(df, syst_regex, from_tag, to_tag):
    transfer_systs = [s for s in df["syst"].unique() if re.match(syst_regex, s)]
    origin_df = df[(df.signal_tag == from_tag) & (df.syst.isin(transfer_systs))]
    origin_df_nom = df[(df.signal_tag == from_tag) & (df.syst == "")]

    #make a copy dataframe to put the new transfered systematic in
    #also need to also copy the histogram objects explicitly
    target_df = copy.deepcopy(origin_df)
    target_df["hist"] = origin_df["hist"].apply( copy.deepcopy )
    target_df["hist_lowess"] = origin_df["hist_lowess"].apply( copy.deepcopy )

    target_df_nom = df[(df.signal_tag == to_tag) & (df.syst == "")]


    for (obs, process, syst), cut_df in target_df.groupby(["observable", "process", "syst"]):
        # get correspoding nominal 4FS process name
        target_proc = process.replace(from_tag, to_tag)
        print(f"transfering syst {syst} from {from_tag} to {to_tag} for {obs} {process}")


        # get nominal entries
        cut_target_nom = target_df_nom[(target_df_nom.observable == obs) & (target_df_nom.process == target_proc)]
        cut_origin_nom = origin_df_nom[(origin_df_nom.observable == obs) & (origin_df_nom.process == process)]
        cut_origin_var = origin_df[(origin_df.observable == obs) & (origin_df.process == process) & (origin_df.syst == syst)]

        # loop over eras and channels and separate entries from MIG_RECO and RECO
        for (channel, era), single_df in cut_df.groupby(["channel", "era"]):
            for i, row in single_df.iterrows():
                hist_type = row["hist_type"]

                # get nominal entries
                target_nom = cut_target_nom[(cut_target_nom.channel == channel) & (cut_target_nom.era == era) & (cut_target_nom.hist_type == hist_type)]
                origin_nom = cut_origin_nom[(cut_origin_nom.channel == channel) & (cut_origin_nom.era == era) & (cut_origin_nom.hist_type == hist_type)]
                origin_var = cut_origin_var[(cut_origin_var.channel == channel) & (cut_origin_var.era == era) & (cut_origin_var.hist_type == hist_type)]
                if len(target_nom) != 1:
                    raise Exception(f"couldnt identify nominal histogram of {to_tag} for transfer")
                if len(origin_nom) != 1:
                    raise Exception(f"couldnt identify nominal histogram of {from_tag} for transfer")
                if len(origin_var) != 1:
                    raise Exception(f"couldnt identify nominal histogram of {from_tag} for transfer")

                # get nominal and varied values of original
                og_nom = origin_nom.iloc[0]["hist"].view().value
                og_var = origin_var.iloc[0]["hist"].view().value
                og_var_smoothed = origin_var.iloc[0]["hist_lowess"].view().value

                def safe_ratio(ratio):
                    ratio = np.nan_to_num(ratio, nan=1.)
                    ratio = np.maximum(ratio, 0.)  # make sure it's non-negative
                    ratio = np.where(ratio > 0, ratio, 1.)  # make sure we don't apply a ratio of 0 in case the original nominal histogram was 0 somewhere
                    return ratio

                # build ratios from 5FS information
                ratio = safe_ratio(og_var / og_nom)
                ratio_smooth = safe_ratio(og_var_smoothed / og_nom)

                # get nominal values of target
                new_nom = target_nom.iloc[0]["hist"].view().value

                # build new histograms from nominal 4FS with 5FS ratio
                new_var = new_nom * ratio
                new_var_smooth = new_nom * ratio_smooth

                # update relevant entry values
                row["hist"].view().value = new_var
                row["hist_lowess"].view().value = new_var_smooth

    # edit column content of new variations
    target_df["process"].replace(from_tag, to_tag, regex=True, inplace=True)
    target_df["ooa"].replace(from_tag, to_tag, regex=True, inplace=True)
    target_df["signal_tag"].replace(from_tag, to_tag, regex=True, inplace=True)

    # remove rows from original df that already contain these rows to be added
    len_og = len(df)
    df = df[~((df.signal_tag == to_tag) & (df.syst.isin(transfer_systs)))]
    removed_lines = len_og - len(df)
    if removed_lines > 0:
        print(f"Removed {removed_lines} entries from histograms dataframe before adding new ones...")

    # concatenate new df
    df_new = pd.concat([df, target_df], ignore_index=True)
    added_lines = len(df_new) - len(df)
    print(f"Added {added_lines} new entries to histograms dataframe")

    return df_new






if __name__ == '__main__':
    parser = ArgumentParser(usage="%(prog)s [options]")
    parser.add_argument('--read-hdf', help="histogram h5 file to read the histograms and smooth them. If no h5 file is given, histograms will be loaded from the input dir and saved to histograms.h5 in that directory.")
    parser.add_argument('-i', '--inputdir', help="Directory containing the ROOT input files")
    parser.add_argument('--unf-cfg', required=True, help="Unfolding config file from bamboo")
    parser.add_argument('--plt-cfg', required=True, help="Unfolding plots config file from bamboo")
    parser.add_argument('--proc-cfg', required=True, help="Process config file from normalize_group_samples.py")
    parser.add_argument('-j', '--nprocs', type=int, default=8, help='number of subprocesses to run. [default: %(default)s].')
    parser.add_argument("--lowess-regex", help="regex for systematics to smooth via lowess smoothing")
    parser.add_argument("--global-lowess-regex", help="regex for systematics to smooth via global lowess smoothing averaged over eras and channels")
    args = parser.parse_args()

    print("Building histogram DF...")
    hist_store = tu.HistStore(args.unf_cfg, args.plt_cfg, args.proc_cfg)

    inputdir = args.inputdir if args.inputdir else os.path.dirname(args.read_hdf)

    # load df
    if args.read_hdf:
       df = tu.load_from_hdf5(args.read_hdf)
    else:
        # build DF and load the histograms from the ROOT files
        print(f'building histogram DF from the hist store!')
        df = hist_store.build_df_uproot(inputdir, store_hists=True, nprocs=args.nprocs)

    # define new column for lowess histograms
    df["hist_lowess"] = copy.deepcopy(df["hist"].values)

    # define new column for template type
    def get_dummy_array(x, val=1.0):
        # each entry has to be the length of the histogram
        # i.e. 1 for all but migration matrices, which are len(genbins)
        if len(x) == 1:
            return np.array([val])
        else:
            return np.array([val for _ in range(x[0])])
    template_type = [get_dummy_array(hist.view().value.shape, val=tu.SystType.SHAPE) for hist in df["hist"]]
    template_norm = [get_dummy_array(hist.view().value.shape, val=1.0) for hist in df["hist"]]
    df["template_type"] = template_type
    df["template_norm"] = template_norm

    # get reco df to reduce unecessary loops
    reco_df = df[ (df.hist_type == tu.HistType.RECO) | (df.hist_type == tu.HistType.MIG_RECO) ]

    global_smooth_systs = set()
    single_smooth_systs = set()
    # loop over all processes and observables
    for (process, obs), obs_df in reco_df.groupby(["process", "observable"]):

        # get the df with nominal histograms for this
        nom_df = obs_df[ obs_df["syst"] == "" ]

        # get reco and aux bins for the observable
        reco_bins, aux_bins = get_reco_and_aux_bins(df, obs, hist_store)

        new = False
        # loop overs systematics
        systs_smoothed = []
        for (syst), syst_df in obs_df.groupby(["syst"]):

            syst_is_up = re.search('Up$', syst) is not None
            syst_is_down = re.search('Down$', syst) is not None
            if syst_is_up:
                syst_up = syst
                syst_base = syst[:-2]
                syst_down = f'{syst_base}Down'
            elif syst_is_down:
                syst_down = syst
                syst_base = syst[:-4]
                syst_up = f'{syst_base}Up'
            else:
                syst_up = syst
                syst_down = None
                syst_base = syst
                #raise ValueError(f'Systematic {syst} isnt an up or down variation, I dont know what to do!')

            if syst_base in systs_smoothed: continue

            systs_smoothed.append(syst_base)

            syst_up_df = syst_df if syst_is_up else obs_df.loc[obs_df["syst"] == syst_up,:]
            syst_down_df = None
            if syst_down is not None:
                syst_down_df = syst_df if syst_is_down else obs_df.loc[obs_df["syst"] == syst_down, :]

            smoothed = False
            # systematics with global smoothing over all eras/channels (e.g hdamp?)
            if args.global_lowess_regex:
                if re.match(args.global_lowess_regex, syst_base):
                    print(f"Performing GLOBAL smoothing for p={process}, obs={obs} for syst={syst_base}")
                    smooth_systematic_global(syst_up_df, nom_df, syst, reco_bins, aux_bins, alt_syst_df=syst_down_df)
                    smoothed = True
                    global_smooth_systs.add(syst_up)
                    if syst_down is not None:
                        global_smooth_systs.add(syst_down)


            # systematics with smoothing based on each distribution alone
            if args.lowess_regex:
                if not smoothed and re.match(args.lowess_regex, syst_base):
                    print(f"Performing SEPARATE smoothing for p={process}, obs={obs} for syst={syst_base}")
                    syst_df = smooth_systematic(syst_up_df, nom_df, syst, reco_bins, aux_bins, alt_syst_df=syst_down_df)
                    single_smooth_systs.add(syst_up)
                    if syst_down is not None:
                        single_smooth_systs.add(syst_down)


    # setup output directory
    out_dir = os.path.join(inputdir, "syst_smoothing")
    if not os.path.exists(out_dir):
        os.mkdir(out_dir)
    # setup output directory for after symmetrization
    out_dir_symm = os.path.join(inputdir, "syst_smoothing_symm")
    if not os.path.exists(out_dir_symm):
        os.mkdir(out_dir_symm)

    # transfer CR and tune variations fon 5FS to 4FS
    # can in principle be hard coded as this doesnt change...
    df = transfer_nuisances(df, syst_regex="CR|erdON|tune|pdf_alphaS|pdfAlphaS", from_tag="powheg_5FS", to_tag="powheg_4FS")

    # new reco df including also added columns
    reco_df = df[ (df.hist_type == tu.HistType.RECO) | (df.hist_type == tu.HistType.MIG_RECO) ]

    if len(global_smooth_systs) > 0:
        print('plotting global smoothed systs')
        # draw summary of global smoothed systematics
        smooth_df = reco_df[(reco_df.syst.isin(global_smooth_systs))]
        plot_global_systs(smooth_df, out_dir)

        # get pairs of systematics
        syst_pairs = tu.get_syst_pairs(global_smooth_systs)
        symmetrize_template_types(smooth_df, syst_pairs)
        plot_global_systs(smooth_df, out_dir_symm)



    if len(single_smooth_systs) > 0:
        # draw summaries of separately smoothed systematics
        print('plotting single smoothed systs')
        smooth_df = reco_df[(reco_df.syst.isin(single_smooth_systs))]
        plot_each_obs(single_smooth_systs, smooth_df, out_dir)

        # get pairs of systematics
        syst_pairs = tu.get_syst_pairs(single_smooth_systs)
        symmetrize_template_types(smooth_df, syst_pairs)
        plot_each_obs(single_smooth_systs, smooth_df, out_dir_symm)

    # save output file
    tu.save_to_hdf5(df, args.read_hdf if args.read_hdf else os.path.join(inputdir, 'histograms.h5'))
    print("updated dataframe with 'hist_lowess' column.")


