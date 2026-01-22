"""
Datacard Writer
===============

Generate CMS Combine datacards from template ROOT files.

Usage:
    from fourtop.stage4.datacards import DatacardWriter, write_shape_datacard

    writer = DatacardWriter(config, era)
    writer.write(template_path, output_dir)
"""

from typing import Dict, List, Optional, Tuple
import ROOT

from fourtop.constants.systematics import MCSYS
from fourtop.utils.process import isData


def getSysDic(
    processes: List[str],
    channel: str,
    era: str,
    ifForPlot: bool = False
) -> Dict[str, List]:
    """
    Build systematic dictionary for Combine datacard.

    Args:
        processes: List of process names
        channel: Channel name (1tau0l, 1tau1l, 1tau2l)
        era: Era string (2018, 2017, 2016preVFP, 2016postVFP)
        ifForPlot: If True, don't decorrelate systematics for different processes

    Returns:
        Dictionary mapping systematic name to [type, {process: value}]
        Example: {'pdf_00': ['shape', {'tt': 1, 'ttX': 1, 'fakeTau': 0, ...}]}
    """
    sysDic = {}
    for sys, sysList in MCSYS.items():
        # Skip L1 ECAL prefiring for 2018 (only applies to 2016-2017)
        if sys == 'CMS_l1_ecal_prefiring' and era == '2018':
            continue

        sysPre = sys if sysList[0] else f"{sys}_{era}"

        # VFP era mapping: Correlate 2016preVFP and 2016postVFP for specific systematics
        # by using unified "2016" suffix instead of separate preVFP/postVFP
        if era in ['2016preVFP', '2016postVFP']:
            # Electron reconstruction efficiency
            if sys == 'CMS_eff_e_reco':
                sysPre = f"{sys}_2016"
            # Tau energy scale (all DM modes)
            elif sys.startswith('CMS_scale_t_DeepTau2017v2p1_DM'):
                sysPre = f"{sys}_2016"
            # L1 ECAL prefiring
            elif sys == 'CMS_l1_ecal_prefiring':
                sysPre = f"{sys}_2016"
            # Note: Tau ID keeps VFP-specific names
            # Note: Tau fake rates are fully correlated (no year suffix)

        if not sysList[3] and sysList[1] == 0:  # process-uncorrelated systematic
            if ifForPlot:
                sysName = [sysPre]
            else:
                sysName = [f"{sysPre}_{ipro}" for ipro in processes if 'fake' not in ipro]
        else:
            sysName = [sysPre]

        for isys in sysName:
            sysDic[isys] = []
            sysDic[isys].append("shape")
            proSysDic = getProSysDic(isys, sysList, processes, channel, ifForPlot)
            sysDic[isys].append(proSysDic)

    return sysDic


def getProSysDic(
    sys: str,
    sysList: List,
    processes: List[str],
    channel: str = '1tau1l',
    ifCombine: bool = False
) -> Dict[str, int]:
    """
    Get process-specific systematic dictionary.

    Args:
        sys: Systematic name
        sysList: Systematic configuration [isCorrelated, whichProcess, channelBits, isProcessCorrelated]
        processes: List of process names
        channel: Channel name
        ifCombine: If True, for combine (process-correlated), else for plotting

    Returns:
        Dictionary mapping process name to 0 or 1
    """
    # Channel bitmask
    channelMask = {
        '1tau1l': 0b100,
        '1tau0l': 0b010,
        '1tau2l': 0b001
    }.get(channel, 0b100)

    proSys = {}
    for ipro in processes:
        if isData(ipro):
            continue

        if ipro == 'fakeTau':
            proSys[ipro] = 1 if sysList[1] == 1 and ((sysList[2] & channelMask) != 0) else 0
        elif ipro == 'fakeLepton':
            proSys[ipro] = 1 if sysList[1] == 2 and ((sysList[2] & channelMask) != 0) else 0
        elif ipro == 'Minor':
            # Not considering any systematic for Minor processes
            proSys[ipro] = 0
        else:
            if not sysList[3]:  # process uncorrelated systematic
                if not ifCombine:
                    proName = sys.split('_')[-1]
                    proSys[ipro] = 1 if sysList[1] == 0 and (sysList[2] & channelMask != 0) and ipro == proName else 0
                else:
                    proSys[ipro] = 1 if sysList[1] == 0 and (sysList[2] & channelMask != 0) else 0
            else:
                proSys[ipro] = 1 if sysList[1] == 0 and (sysList[2] & channelMask != 0) else 0

            # Exclude certain systematics from singleTop
            if ipro == 'singleTop' and sys in ['pdf_alphas', 'pdf_normalised', 'QCDscale_Re_normalised',
                                                 'QCDscale_Fa_normalised', 'ISR_normalised', 'FSR_normalised']:
                proSys[ipro] = 0
            if ipro == 'singleTop' and channel == '1tau2l':
                proSys[ipro] = 0
            # Exclude pdf_alphas from ttbb due to low statistics
            if ipro == 'ttbb' and sys == 'pdf_alphas':
                proSys[ipro] = 0
            if ipro == 'fakeTauMC' and sysList[1] == 3 and ((sysList[2] & channelMask) != 0):
                proSys[ipro] = 1

    return proSys


def getProSysDicForPlotting(
    processes: List[str],
    ifSys: bool = False,
    channel: str = '1tau1l',
    era: str = '2018',
    forCombine: bool = False
) -> Dict[str, List[str]]:
    """
    Get systematic dictionary per process for plotting.

    This inverts the getSysDic result to provide a mapping from
    each process to its list of applicable systematics.
    Used by pl.py for validation plots with systematic bands.

    Args:
        processes: List of process names
        ifSys: If False, return empty dict (no systematics)
        channel: Channel name ('1tau0l', '1tau1l', '1tau2l')
        era: Era string ('2018', '2017', '2016preVFP', '2016postVFP')
        forCombine: If True, use combine-compatible systematic names

    Returns:
        Dictionary mapping process name to list of systematic names
        Example: {'tt': ['pdf_00', 'pdf_01', ...], 'ttX': [...], ...}
    """
    if not ifSys:
        return {}

    sumProSys: Dict[str, List[str]] = {}

    # Remove data process from list (not needed for systematics)
    proc_list = processes.copy()
    data_process = 'leptonSum' if channel == '1tau2l' else 'jetHT'
    if data_process in proc_list:
        proc_list.remove(data_process)

    # Get systematic dictionary from getSysDic
    proSys = getSysDic(proc_list, channel, era, forCombine)

    # Invert: from {sys: [type, {proc: 0/1}]} to {proc: [sys1, sys2, ...]}
    for ipro in proc_list:
        sumProSys[ipro] = []
        for isys, sysList in proSys.items():
            # sysList = [type, {process: 0/1}]
            if len(sysList) >= 2 and isinstance(sysList[1], dict):
                if sysList[1].get(ipro, 0) == 1:
                    sumProSys[ipro].append(isys)

    return sumProSys


def addLumi(sysDic: Dict, era: str, processes: List[str]) -> None:
    """
    Add luminosity uncertainties to systematic dictionary.

    Args:
        sysDic: Systematic dictionary (modified in place)
        era: Era string
        processes: List of process names
    """
    # Map VFP eras to year for CMS naming convention
    yearMap = {
        '2016preVFP': '2016',
        '2016postVFP': '2016',
        '2017': '2017',
        '2018': '2018'
    }
    year = yearMap[era]

    # Luminosity values: [uncorrelated, correlated 3 years, correlated 2017-2018]
    lumiMap = {
        '2016preVFP': [1.01, 1.006, 0],
        '2016postVFP': [1.01, 1.006, 0],
        '2017': [1.02, 1.009, 1.006],
        '2018': [1.015, 1.02, 1.002]
    }

    sysDic['lumi_13TeV_correlated'] = []
    sysDic[f'lumi_{year}'] = []
    sysDic['lumi_13TeV_1718'] = []

    sysDic['lumi_13TeV_correlated'].append("lnN")
    sysDic[f'lumi_{year}'].append("lnN")
    sysDic['lumi_13TeV_1718'].append("lnN")

    iDicCorrelated = {}
    iDicUncorrelated = {}
    iDic20172018 = {}

    for ipro in processes:
        if ipro in ['fakeTau', 'fakeLepton']:
            iDicCorrelated[ipro] = 0
            iDicUncorrelated[ipro] = 0
            iDic20172018[ipro] = 0
        else:
            iDicCorrelated[ipro] = lumiMap[era][1]
            iDicUncorrelated[ipro] = lumiMap[era][0]
            iDic20172018[ipro] = lumiMap[era][2]

    sysDic['lumi_13TeV_correlated'].append(iDicCorrelated)
    sysDic[f'lumi_{year}'].append(iDicUncorrelated)
    sysDic['lumi_13TeV_1718'].append(iDic20172018)


def addProcessNormalization(sysDic: Dict, processes: List[str]) -> None:
    """
    Add process normalization systematics to systematic dictionary.

    Args:
        sysDic: Systematic dictionary (modified in place)
        processes: List of process names
    """
    proNormalDic = {
        'tttt': 0.1,
        'tt': 0.05,  # https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
        'singleTop': 0.2,
        'WJets': 0.1,
        'Minor': 0.2,
        'ttZ': 0.119,
        'ttW': 0.102,
        'ttH': 0.084,
        # Note: 'ttbb' uses param constraint instead - see write_shape_datacard()
    }

    for ipro, inorm in proNormalDic.items():
        sysDic[f"CMS_TOP24017_norm_{ipro}"] = []
        sysDic[f"CMS_TOP24017_norm_{ipro}"].append("lnN")
        proDic = {}
        for ipro2 in processes:
            if ipro2 == ipro:
                proDic[ipro2] = 1 + inorm
            else:
                proDic[ipro2] = 0
        sysDic[f"CMS_TOP24017_norm_{ipro}"].append(proDic)

    # Add FR uncertainty for fakeLepton
    sysDic['CMS_TOP24017_norm_fakeLepton_sys'] = []
    sysDic['CMS_TOP24017_norm_fakeLepton_sys'].append("lnN")
    sysDic['CMS_TOP24017_norm_fakeLepton_stats'] = []
    sysDic['CMS_TOP24017_norm_fakeLepton_stats'].append("lnN")

    proDic = {}
    for ipro in processes:
        if ipro == 'fakeLepton':
            proDic[ipro] = 1.2
        else:
            proDic[ipro] = 0
    sysDic['CMS_TOP24017_norm_fakeLepton_sys'].append(proDic)
    sysDic['CMS_TOP24017_norm_fakeLepton_stats'].append(proDic)


def remove0Process(
    processes: List[str],
    inputTemplate: str,
    channel: str,
    quiet: bool = False
) -> None:
    """
    Remove processes with zero integral from the process list.

    Args:
        processes: List of process names (modified in place)
        inputTemplate: Path to template ROOT file
        channel: Channel name
        quiet: If True, suppress output
    """
    rootFile = ROOT.TFile(inputTemplate, "READ")
    to_remove = []

    for ipro in processes:
        histName = f"{ipro}_{channel}SR_BDT"
        hist = rootFile.Get(histName)
        if hist is None:
            if not quiet:
                print(f'hist is None: {histName}')
        elif hist.Integral() < 0.00000001:
            if not quiet:
                print(f"remove {ipro} process (zero integral)")
            to_remove.append(ipro)

    for ipro in to_remove:
        processes.remove(ipro)

    rootFile.Close()


def write_shape_datacard(
    output_file: str,
    root_file: str,
    channel_name: str,
    processes: List[str],
    systematics: Dict,
    era: str = '2018'
) -> None:
    """
    Write a shape datacard for CMS Combine.

    Args:
        output_file: Name of the text file to write the datacard to
        root_file: Name of the ROOT file containing histograms
        channel_name: Name of the analysis channel
        processes: List of process names
        systematics: Dictionary of systematic uncertainties structured as:
            { "uncertainty_name": [type, { "process_name": value }] }
        era: Era string for bin naming
    """
    num_processes = len(processes)
    signal_index = processes.index('tttt')

    # Column widths for formatting
    process_col_width = 70
    value_col_width = 22
    channelNameName = f"SR{channel_name}_{era}"

    rates = "rate".ljust(process_col_width)
    proString = "process".ljust(process_col_width)
    binString = "bin".ljust(process_col_width)

    lines = [
        "imax 1  number of channels",
        f"jmax {num_processes - 1}  number of background processes",
        "kmax *  number of nuisance parameters (sources of systematic uncertainties)",
        "---------------",
        f"shapes * {channelNameName} {root_file} $PROCESS_{channel_name}SR_BDT $PROCESS_{channel_name}SR_$SYSTEMATIC_BDT",
        "---------------",
        f"bin         {channelNameName}",
        "observation -1",
        "---------------",
        f"{binString}{''.join([channelNameName.ljust(value_col_width) for _ in range(num_processes)])}",
        f"{proString}{''.join([proc.ljust(value_col_width) for proc in processes])}",
        f"{proString}{''.join([str(signal_index - i).ljust(value_col_width) for i in range(num_processes)])}",
        f"{rates}{''.join(['-1'.ljust(value_col_width) for _ in range(num_processes)])}",
        "---------------"
    ]

    # Add systematic lines
    for unc_name, (unc_type, uncertainties) in systematics.items():
        line = f"{unc_name} {unc_type}".ljust(process_col_width)
        ilist = []
        for proc in processes:
            iuncer = uncertainties[proc] if uncertainties[proc] != 0 else '-'
            ilist.append(f"{iuncer}".ljust(value_col_width))
        line += " ".join(ilist)
        lines.append(line)

    # Add MC statistical uncertainties
    lines.append("---------------")
    lines.append(f"{channelNameName} autoMCStats 10 0 1")

    # Add TTBB Gaussian parameter constraint
    if 'ttbb' in processes:
        lines.append("---------------")
        lines.append("# TTBB normalization: Gaussian constraint at 1.19 with sigma=0.13")
        lines.append("CMS_TOP24017_norm_ttbb param 1.19 0.13")

    # Write to file
    with open(output_file, 'w') as f:
        for line in lines:
            f.write(line + "\n")
    print(f"Datacard written to {output_file}")


class DatacardWriter:
    """
    Writer class for CMS Combine datacards.

    Generates datacards from template ROOT files with proper
    systematic uncertainties and process configuration.

    Usage:
        writer = DatacardWriter(config, era)
        writer.write(template_path, output_dir)
    """

    def __init__(self, config: dict, era: str, quiet: bool = False):
        """
        Initialize datacard writer.

        Args:
            config: Analysis configuration dictionary
            era: Era string (2018, 2017, etc.)
            quiet: If True, suppress output
        """
        self.config = config
        self.era = era
        self.quiet = quiet

        self.channel = None
        self.processes = None

    def write(self, template_path: str, output_dir: str) -> str:
        """
        Write datacard from template file.

        Args:
            template_path: Path to template ROOT file
            output_dir: Output directory for datacard

        Returns:
            Path to created datacard file
        """
        from fourtop.workflow import get_channel, get_options
        from fourtop.utils import checkMakeDir
        import pl as pl  # Legacy import for getSumList

        self.channel = get_channel(self.config)
        options = get_options(self.config)
        ifFTauMC = options.get('mc_fake_tau', False)

        # Get process list
        self.processes = pl.getSumList(self.channel, True, False, ifFTauMC, True)
        if self.channel == '1tau2l':
            self.processes.remove('leptonSum')
        else:
            self.processes.remove('jetHT')

        if not self.quiet:
            print(f"Processes: {self.processes}")

        # Remove zero-integral processes
        remove0Process(self.processes, template_path, self.channel, self.quiet)

        # Build systematic dictionary
        sysDic = getSysDic(self.processes, self.channel, self.era)
        addLumi(sysDic, self.era, self.processes)
        addProcessNormalization(sysDic, self.processes)

        # Write datacard
        checkMakeDir(output_dir)
        outCard = f"{output_dir}/datacard.txt"
        write_shape_datacard(outCard, template_path, self.channel, self.processes, sysDic, self.era)

        return outCard
