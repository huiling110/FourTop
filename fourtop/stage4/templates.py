"""
Template File Builder
=====================

Create template ROOT files for CMS Combine from histogram inputs.

Usage:
    from fourtop.stage4.templates import TemplateBuilder, addDataHist

    builder = TemplateBuilder(config, era)
    builder.build()
"""

from typing import Dict, List, Optional
import ROOT

from fourtop.constants.systematics import MCSYS
from fourtop.utils.process import isData


def resetNegativeBins(hist: ROOT.TH1) -> ROOT.TH1:
    """
    Set negative bin contents and errors to zero.

    Args:
        hist: ROOT histogram (modified in place)

    Returns:
        The modified histogram
    """
    for i in range(1, hist.GetNbinsX() + 1):
        if hist.GetBinContent(i) < 0.:
            hist.SetBinContent(i, 0)
            hist.SetBinError(i, 0)
    return hist


def addDataHist(
    variables: List[str],
    regionList: List[str],
    sumProList: List[str],
    sumProcessPerVar: Dict,
    is1tau2l: bool,
    ifBlind: bool = True,
    quiet: bool = False
) -> None:
    """
    Add data histogram (or fake data for blinded SR).

    For blinded signal regions, creates fake data from sum of MC backgrounds.

    Args:
        variables: List of variable names
        regionList: List of region names
        sumProList: List of process names
        sumProcessPerVar: Histogram dictionary [var][region][process]
        is1tau2l: If True, use leptonSum for data, else jetHT
        ifBlind: If True, blind SR regions with fake data
        quiet: If True, suppress print output
    """
    dataName = 'leptonSum' if is1tau2l else 'jetHT'

    for ivar in variables:
        for region in regionList:
            dataHist = None
            if 'SR' in region and ifBlind:
                # Create fake data from sum of MC
                for sumPro in sumProList:
                    if isData(sumPro):
                        continue
                    if not quiet:
                        print('fake data:', sumPro)

                    hist = sumProcessPerVar[ivar][region][sumPro]
                    resetNegativeBins(hist)

                    if dataHist is None:
                        dataHist = hist.Clone()
                        dataHist.SetName(dataHist.GetName().replace(sumPro, 'data_obs'))
                    else:
                        dataHist.Add(hist)

                sumProcessPerVar[ivar][region][dataName] = dataHist
                if not quiet:
                    print('fake data hist:', dataHist.GetName())

            # Rename data histogram to data_obs
            if dataName in sumProcessPerVar[ivar][region]:
                dataHistName = sumProcessPerVar[ivar][region][dataName].GetName()
                dataHistName = dataHistName.replace(dataName, 'data_obs')
                sumProcessPerVar[ivar][region][dataName].SetName(dataHistName)


def renameProcessUncorrelatedSys(
    hist: ROOT.TH1,
    sys_name: str,
    process: str
) -> None:
    """
    Rename histogram for process-uncorrelated systematics.

    Process-uncorrelated systematics need unique names per process in Combine.

    Args:
        hist: ROOT histogram (modified in place)
        sys_name: Systematic name with _up or _down suffix
        process: Process name to append
    """
    # Remove direction suffix
    sysName = sys_name.replace('_up', '').replace('_down', '')

    # Remove era suffix
    for era_suffix in ['_2018', '_2017', '_2016preVFP', '_2016postVFP', '_2016']:
        sysName = sysName.replace(era_suffix, '')

    # Check if process-uncorrelated
    if sysName in MCSYS and not MCSYS[sysName][3]:
        sysNameNew = sysName + '_' + process
        hist.SetName(hist.GetName().replace(sysName, sysNameNew))


def writeTemplateFile(
    outFile: ROOT.TFile,
    variables: List[str],
    regionList: List[str],
    sumProList: List[str],
    sumProcessPerVar: Dict,
    sumProcessPerVarSys: Dict,
    quiet: bool = False
) -> None:
    """
    Write histograms to template ROOT file.

    Args:
        outFile: Output ROOT file (must be open)
        variables: List of variable names
        regionList: List of region names
        sumProList: List of process names
        sumProcessPerVar: Nominal histogram dictionary
        sumProcessPerVarSys: Systematic histogram dictionary
        quiet: If True, suppress output
    """
    for ivar in variables:
        for region in regionList:
            for sumPro in sumProList:
                # Write nominal histogram
                if sumPro in sumProcessPerVar[ivar][region]:
                    hist = sumProcessPerVar[ivar][region][sumPro]
                    hist.Write(hist.GetName())

                # Write systematic histograms
                if sumPro in sumProcessPerVarSys[ivar][region]:
                    for sys_name in sumProcessPerVarSys[ivar][region][sumPro]:
                        hist = sumProcessPerVarSys[ivar][region][sumPro][sys_name]

                        # Rename process-uncorrelated systematics
                        renameProcessUncorrelatedSys(hist, sys_name, sumPro)

                        hist.Write(hist.GetName())


def buildTemplatePath(
    inputDir: str,
    channel: str,
    template_version: str,
    ifMCFTau: bool,
    ifBlind: bool
) -> str:
    """
    Build template file path.

    Args:
        inputDir: Input directory path
        channel: Channel name
        template_version: Version string for template file
        ifMCFTau: If True, using MC fake tau
        ifBlind: If True, blinded

    Returns:
        Full path to template file
    """
    name = f'templatesForCombine{channel}_{template_version}'
    if not ifMCFTau:
        name += '_notMCFTau'
    if not ifBlind:
        name += '_unblind'

    outDir = inputDir + 'combine/'
    return outDir + name + '.root'


class TemplateBuilder:
    """
    Builder class for CMS Combine template files.

    Handles loading histograms, applying systematic variations,
    and writing output template files.

    Usage:
        builder = TemplateBuilder(config, era)
        builder.build()
    """

    def __init__(self, config: dict, era: str, quiet: bool = False):
        """
        Initialize template builder.

        Args:
            config: Analysis configuration dictionary
            era: Era string (2018, 2017, etc.)
            quiet: If True, suppress output
        """
        self.config = config
        self.era = era
        self.quiet = quiet

        # Will be populated during build
        self.channel = None
        self.inputDir = None
        self.sumProList = None

    def build(self) -> str:
        """
        Build template file from configuration.

        Returns:
            Path to created template file
        """
        from fourtop.workflow import (
            load_config, build_hist_path, get_channel, get_options, get_regions
        )
        from fourtop.utils import checkMakeDir, getInputDicNew, getSumHist
        from fourtop.constants.jes import SKIP_SUBPROCESSES

        # Load configuration
        self.channel = get_channel(self.config)
        options = get_options(self.config)
        self.inputDir = build_hist_path(self.config, self.era)
        variables = ['BDT']
        regionList = get_regions(self.config)
        ifFakeTau = options.get('fake_tau', True)
        ifMCFTau = options.get('mc_fake_tau', False)
        ifBlind = options.get('blind', False)

        if not self.quiet:
            print(f"Era: {self.era}, Channel: {self.channel}")
            print(f"Input dir: {self.inputDir}")

        inputDirDic = getInputDicNew(self.inputDir)
        is1tau2l = self.channel == '1tau2l'

        # Get process list and systematics
        # (This would need pl.getSumList and pl.getSysDicPL to be refactored)
        # For now, this serves as documentation of the intended interface

        # Build and write template
        template_version = self.config.get('versions', {}).get('template_file', 'v3')
        templatePath = buildTemplatePath(
            self.inputDir, self.channel, template_version, ifMCFTau, ifBlind
        )

        return templatePath
