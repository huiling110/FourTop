"""
Systematic Consolidation
========================

Consolidate JES/JER/TES/MET/EES systematic variations into nominal histogram files.

Usage:
    from fourtop.stage4.systematics import (
        addJESToFile, addJERToFile, addTESToFile, addMETToFile, addEESToFile
    )

    addJESToFile(subprocesses, channel, regions, era, nominal_dir, variables)
"""

from typing import Dict, List, Optional
import ROOT

from fourtop.constants.jes import JESVariationList, SKIP_SUBPROCESSES
from fourtop.constants.samples import proChannelDic
from fourtop.constants.systematics import MCSYS
from fourtop.utils.histogram import getHistFromFile
from fourtop.utils.process import getAllSubPro


def getMCSubPro(channel: str, era: str, quiet: bool = False) -> List[str]:
    """
    Get list of MC subprocesses for a channel.

    Args:
        channel: Channel name (1tau0l, 1tau1l, 1tau2l)
        era: Era string
        quiet: If True, suppress output

    Returns:
        List of subprocess names
    """
    sumProcesses = proChannelDic[channel].copy()

    # Remove data and fake processes
    for proc in ['jetHT', 'leptonSum', 'fakeTau', 'fakeLepton']:
        if proc in sumProcesses:
            sumProcesses.remove(proc)

    allSubProcesses = getAllSubPro(era, sumProcesses, False)

    # Filter out subprocesses that should be skipped for this channel
    skip_list = SKIP_SUBPROCESSES.get(channel, [])
    if skip_list:
        allSubProcesses = [sp for sp in allSubProcesses if sp not in skip_list]
        if not quiet:
            print(f"Skipping subprocesses for {channel}: {skip_list}")

    if not quiet:
        print(allSubProcesses)
    return allSubProcesses


def add_histograms_to_rootfile(
    histograms: List[ROOT.TH1],
    rootfile_path: str,
    quiet: bool = False
) -> None:
    """
    Add a list of histograms to an existing ROOT file.

    Args:
        histograms: List of ROOT.TH1 objects to add
        rootfile_path: Path to the existing ROOT file
        quiet: If True, suppress output
    """
    rootfile = ROOT.TFile.Open(rootfile_path, "UPDATE")
    if not rootfile or rootfile.IsZombie():
        print(f"Error: Could not open file {rootfile_path}")
        return

    for histogram in histograms:
        if isinstance(histogram, ROOT.TH1):
            histogram.Write()
        else:
            print(f"Warning: Object {histogram} is not a ROOT.TH1 histogram")

    rootfile.Close()
    if not quiet:
        print(f"Histograms added to {rootfile_path}")


def addUpDownToFile(
    allSubProcesses: List[str],
    regionList: List[str],
    era: str,
    nominalDir: str,
    upDir: str,
    downDir: str,
    variationName: str,
    variable: str = 'BDT',
    postFix: str = '',
    quiet: bool = False
) -> None:
    """
    Add up/down systematic variations to nominal histogram files.

    Args:
        allSubProcesses: List of subprocess names
        regionList: List of region names
        era: Era string
        nominalDir: Path to nominal histogram directory
        upDir: Path to up variation histogram directory
        downDir: Path to down variation histogram directory
        variationName: Name of the systematic variation
        variable: Variable name (default: 'BDT')
        postFix: Postfix for histogram names (e.g., '_MCFT')
        quiet: If True, suppress output
    """
    UpList = {}
    DownList = {}
    UpName = f'{variationName}_{era}Up'
    DownName = f'{variationName}_{era}Down'

    for isub in allSubProcesses:
        UpList[isub] = []
        DownList[isub] = []
        HistsNameUp = [f'{isub}{postFix}_{ire}_{UpName}_{variable}' for ire in regionList]
        HistsNameDown = [f'{isub}{postFix}_{ire}_{DownName}_{variable}' for ire in regionList]

        histList = [f'{isub}{postFix}_{ire}_{variable}' for ire in regionList]
        histsUp = getHistFromFile(f'{upDir}{isub}.root', histList)
        histsDown = getHistFromFile(f'{downDir}{isub}.root', histList)

        for ire, iHist in enumerate(regionList):
            histsUp[ire].SetName(HistsNameUp[ire])
            histsDown[ire].SetName(HistsNameDown[ire])
            UpList[isub].append(histsUp[ire])
            DownList[isub].append(histsDown[ire])

    for isub, histList in UpList.items():
        inominal = f'{nominalDir}{isub}.root'
        downHists = DownList[isub]
        histToAdd = histList + downHists
        add_histograms_to_rootfile(histToAdd, inominal, quiet)


def addTESToFile(
    allSubProcesses: List[str],
    regionList: List[str],
    era: str,
    nominalDir: str,
    variables: List[str] = None,
    ifMCFTau: bool = False,
    quiet: bool = False
) -> None:
    """
    Add TES (Tau Energy Scale) variations to nominal histogram files.

    Args:
        allSubProcesses: List of subprocess names
        regionList: List of region names
        era: Era string
        nominalDir: Path to nominal histogram directory
        variables: List of variables (default: ['BDT'])
        ifMCFTau: If True, also process MCFT variants
        quiet: If True, suppress output
    """
    if variables is None:
        variables = ['BDT']

    # Map 2016 VFP eras to unified "2016" for tau TES correlation
    mapped_era = "2016" if era in ["2016preVFP", "2016postVFP"] else era

    for dm in (0, 1, 10, 11):
        iTESUpDir = nominalDir.replace('/mc/', f'_TESdm{dm}Up/mc/')
        iTESDownDir = nominalDir.replace('/mc/', f'_TESdm{dm}Down/mc/')
        TESName = f'CMS_scale_t_DeepTau2017v2p1_DM{dm}_genTau'

        for ivariable in variables:
            addUpDownToFile(allSubProcesses, regionList, mapped_era, nominalDir,
                            iTESUpDir, iTESDownDir, TESName, ivariable, quiet=quiet)
            if ifMCFTau:
                addUpDownToFile(allSubProcesses, regionList, mapped_era, nominalDir,
                                iTESUpDir, iTESDownDir, TESName, ivariable, '_MCFT', quiet)
                addUpDownToFile(allSubProcesses, regionList, mapped_era, nominalDir,
                                iTESUpDir, iTESDownDir, TESName, ivariable, '_NotMCFT', quiet)


def addJERToFile(
    allSubProcesses: List[str],
    regionList: List[str],
    era: str,
    nominalDir: str,
    variables: List[str] = None,
    ifMCFTau: bool = False,
    quiet: bool = False
) -> None:
    """
    Add JER (Jet Energy Resolution) variations to nominal histogram files.

    Args:
        allSubProcesses: List of subprocess names
        regionList: List of region names
        era: Era string
        nominalDir: Path to nominal histogram directory
        variables: List of variables (default: ['BDT'])
        ifMCFTau: If True, also process MCFT variants
        quiet: If True, suppress output
    """
    if variables is None:
        variables = ['BDT']

    JERUpDir = nominalDir.replace('/mc/', '_JERUp/mc/')
    JERDownDir = nominalDir.replace('/mc/', '_JERDown/mc/')
    name = 'CMS_res_j'

    for ivariable in variables:
        addUpDownToFile(allSubProcesses, regionList, era, nominalDir,
                        JERUpDir, JERDownDir, name, ivariable, quiet=quiet)
        if ifMCFTau:
            addUpDownToFile(allSubProcesses, regionList, era, nominalDir,
                            JERUpDir, JERDownDir, name, ivariable, '_MCFT', quiet)
            addUpDownToFile(allSubProcesses, regionList, era, nominalDir,
                            JERUpDir, JERDownDir, name, ivariable, '_NotMCFT', quiet)


def addMETToFile(
    allSubProcesses: List[str],
    regionList: List[str],
    era: str,
    nominalDir: str,
    variables: List[str] = None,
    ifMCFTau: bool = False,
    quiet: bool = False
) -> None:
    """
    Add MET (unclustered energy) variations to nominal histogram files.

    Args:
        allSubProcesses: List of subprocess names
        regionList: List of region names
        era: Era string
        nominalDir: Path to nominal histogram directory
        variables: List of variables (default: ['BDT'])
        ifMCFTau: If True, also process MCFT variants
        quiet: If True, suppress output
    """
    if variables is None:
        variables = ['BDT']

    METUpDir = nominalDir.replace('/mc/', '_METUp/mc/')
    METDownDir = nominalDir.replace('/mc/', '_METDown/mc/')
    name = 'CMS_scale_met_unclustered_energy'

    for ivariable in variables:
        addUpDownToFile(allSubProcesses, regionList, era, nominalDir,
                        METUpDir, METDownDir, name, ivariable, quiet=quiet)
        if ifMCFTau:
            addUpDownToFile(allSubProcesses, regionList, era, nominalDir,
                            METUpDir, METDownDir, name, ivariable, '_MCFT', quiet)
            addUpDownToFile(allSubProcesses, regionList, era, nominalDir,
                            METUpDir, METDownDir, name, ivariable, '_NotMCFT', quiet)


def addEESToFile(
    allSubProcesses: List[str],
    regionList: List[str],
    era: str,
    nominalDir: str,
    variables: List[str] = None,
    ifMCFTau: bool = False,
    quiet: bool = False
) -> None:
    """
    Add EES (Electron Energy Scale) variations to nominal histogram files.

    Args:
        allSubProcesses: List of subprocess names
        regionList: List of region names
        era: Era string
        nominalDir: Path to nominal histogram directory
        variables: List of variables (default: ['BDT'])
        ifMCFTau: If True, also process MCFT variants
        quiet: If True, suppress output
    """
    if variables is None:
        variables = ['BDT']

    EESUpDir = nominalDir.replace('/mc/', '_EleScaleUp/mc/')
    EESDownDir = nominalDir.replace('/mc/', '_EleScaleDown/mc/')
    name = 'CMS_scale_e'

    for ivariable in variables:
        addUpDownToFile(allSubProcesses, regionList, era, nominalDir,
                        EESUpDir, EESDownDir, name, ivariable, quiet=quiet)
        if ifMCFTau:
            addUpDownToFile(allSubProcesses, regionList, era, nominalDir,
                            EESUpDir, EESDownDir, name, ivariable, '_MCFT', quiet)
            addUpDownToFile(allSubProcesses, regionList, era, nominalDir,
                            EESUpDir, EESDownDir, name, ivariable, '_NotMCFT', quiet)


def getJESHistForDir(
    JESUpDir: str,
    JESDownDir: str,
    JESListUp: Dict,
    JESListDown: Dict,
    JESUpName: str,
    JESDownName: str,
    regionList: List[str],
    variable: str = 'BDT',
    subPostfix: str = '',
    quiet: bool = False
) -> None:
    """
    Get JES histograms from up/down directories and add to lists.

    Args:
        JESUpDir: Path to JES up variation directory
        JESDownDir: Path to JES down variation directory
        JESListUp: Dictionary to store up histograms (modified in place)
        JESListDown: Dictionary to store down histograms (modified in place)
        JESUpName: Name for up variation histograms
        JESDownName: Name for down variation histograms
        regionList: List of region names
        variable: Variable name
        subPostfix: Postfix for histogram names
        quiet: If True, suppress output
    """
    for isub in JESListUp.keys():
        isubHistName = isub + subPostfix
        histList = [f'{isubHistName}_{ire}_{variable}' for ire in regionList]
        JESHistsNameUp = [f'{isubHistName}_{ire}_{JESUpName}_{variable}' for ire in regionList]
        JESHistsNameDown = [f'{isubHistName}_{ire}_{JESDownName}_{variable}' for ire in regionList]

        gotHistsUp = getHistFromFile(f'{JESUpDir}{isub}.root', histList)
        gotHistsDown = getHistFromFile(f'{JESDownDir}{isub}.root', histList)

        for ire, iHist in enumerate(regionList):
            gotHistsUp[ire].SetName(JESHistsNameUp[ire])
            gotHistsDown[ire].SetName(JESHistsNameDown[ire])
            JESListUp[isub].append(gotHistsUp[ire])
            JESListDown[isub].append(gotHistsDown[ire])

    if not quiet:
        print(JESListUp)


def addJESToFile(
    allSubProcesses: List[str],
    channel: str,
    regionList: List[str],
    era: str,
    nominalDir: str,
    variables: List[str] = None,
    proPostFix: str = '',
    config: dict = None,
    build_hist_path_jes_func=None,
    quiet: bool = False
) -> None:
    """
    Add JES (Jet Energy Scale) variations to nominal histogram files.

    Args:
        allSubProcesses: List of subprocess names
        channel: Channel name
        regionList: List of region names
        era: Era string
        nominalDir: Path to nominal histogram directory
        variables: List of variables (default: ['BDT'])
        proPostFix: Postfix for process names
        config: Analysis configuration (for path building)
        build_hist_path_jes_func: Function to build JES paths (from workflow_utils)
        quiet: If True, suppress output
    """
    if variables is None:
        variables = ['BDT']

    JESListUp = {}
    JESListDown = {}
    for isub in allSubProcesses:
        JESListUp[isub] = []
        JESListDown[isub] = []

    for jes_source in JESVariationList:
        # Use workflow_utils for path building if config is available
        if config is not None and build_hist_path_jes_func is not None:
            JESUpDir = build_hist_path_jes_func(config, era, 'up', jes_source)
            JESDownDir = build_hist_path_jes_func(config, era, 'Down', jes_source)
        else:
            # Legacy path building (backward compatibility)
            Version = nominalDir.split('/')[-4]
            if not quiet:
                print(Version)
            inVersion = Version.split('_')[-1] + '_JESPt22'
            outVersion = Version.split('_')[0]
            if not quiet:
                print(inVersion, outVersion)
            inputDirBase = f'/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}/'
            nominalHistDir = nominalDir.split('mc/', 1)[1]
            JESUpDir = f'{inputDirBase}{outVersion}_JESup_{jes_source}_{inVersion}'
            JESDownDir = f'{inputDirBase}{outVersion}_JESDown_{jes_source}_{inVersion}'
            JESUpDir = f'{JESUpDir}/mc/{nominalHistDir}'
            JESDownDir = f'{JESDownDir}/mc/{nominalHistDir}'

        if not quiet:
            print(JESUpDir, JESDownDir)

        iJESVariation = jes_source.split('_')[0]
        ifCorrelated = MCSYS[f'CMS_scale_j_{iJESVariation}'][0]
        if ifCorrelated:
            JESUpName = f'CMS_scale_j_{iJESVariation}Up'
            JESDownName = f'CMS_scale_j_{iJESVariation}Down'
        else:
            JESUpName = f'CMS_scale_j_{iJESVariation}_{era}Up'
            JESDownName = f'CMS_scale_j_{iJESVariation}_{era}Down'

        for ivariable in variables:
            getJESHistForDir(JESUpDir, JESDownDir, JESListUp, JESListDown,
                            JESUpName, JESDownName, regionList, ivariable, proPostFix, quiet)

    for isub, histList in JESListUp.items():
        inominal = f'{nominalDir}{isub}.root'
        downHists = JESListDown[isub]
        histToAdd = histList + downHists
        add_histograms_to_rootfile(histToAdd, inominal, quiet)
