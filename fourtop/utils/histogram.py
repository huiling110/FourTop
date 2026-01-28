"""
Histogram Operations
====================

ROOT histogram manipulation utilities.

Usage:
    from fourtop.utils.histogram import (
        getHistFromFile, handle_negative_bins, addBGHist
    )

    hists = getHistFromFile('file.root', ['hist1', 'hist2'])
    handle_negative_bins(hist)
"""

from typing import List, Dict, Tuple, Optional
import ROOT


def getHistFromFile(
    fileName: str,
    histNames: List[str],
    ifPrint: bool = False
) -> List[ROOT.TH1]:
    """
    Get histograms from a ROOT file.

    Args:
        fileName: Path to ROOT file
        histNames: List of histogram names to retrieve
        ifPrint: If True, print histogram info

    Returns:
        List of cloned histograms (detached from file)

    Raises:
        ValueError: If histogram not found
    """
    file = ROOT.TFile.Open(fileName)

    if not file or file.IsZombie():
        print(f"Error: Unable to open the file: {fileName}")
        return []

    histograms = []
    for name in histNames:
        histogram = file.Get(name)
        if not histogram:
            raise ValueError(
                f"Error: Unable to find histogram '{name}' in {fileName}"
            )
        if ifPrint:
            histogram.Print()
        # Clone and detach from file
        histogram1 = histogram.Clone()
        histogram1.SetDirectory(0)
        histograms.append(histogram1)

    file.Close()
    return histograms


def handle_negative_bins(hist: ROOT.TH1, warn: bool = True) -> None:
    """
    Set negative bin contents to zero.

    Args:
        hist: ROOT histogram (modified in place)
        warn: If True, print warning for each negative bin
    """
    for i in range(1, hist.GetNbinsX() + 1):
        if hist.GetBinContent(i) < 0:
            if warn:
                print(f"Warning: Negative bin content at bin {i}. Setting to zero.")
            hist.SetBinContent(i, 0)


def addBGHist(
    sumProcessIVar: Dict,
    region: str,
    includeQCD: bool = False
) -> ROOT.TH1:
    """
    Sum background histograms for a region.

    Args:
        sumProcessIVar: Dictionary of histograms [region][process]
        region: Region name
        includeQCD: If True, include QCD in sum

    Returns:
        Summed histogram
    """
    summedProcessList = list(sumProcessIVar[region].keys())
    sumHist = sumProcessIVar[region][summedProcessList[0]].Clone()
    sumHist.Reset()
    sumHist.Sumw2()
    sumHist.SetName(region)

    exclude_list = ['jetHT', 'singleMu', 'tttt', 'leptonSum']
    if not includeQCD:
        exclude_list.extend(['qcd'])
    else:
        exclude_list.extend(['fakeLepton'])

    for ipro in summedProcessList:
        if any(excl in ipro for excl in exclude_list):
            continue
        sumHist.Add(sumProcessIVar[region][ipro])

    return sumHist


def addDataHist(h1: ROOT.TH1, h2: ROOT.TH1) -> None:
    """
    Add two data histograms with proper error handling.

    Data histogram errors should be sqrt(N), not quadrature sum.
    Modifies h1 in place.

    Args:
        h1: First histogram (modified in place)
        h2: Second histogram

    Raises:
        ValueError: If histograms have different binning
    """
    if h1.GetNbinsX() != h2.GetNbinsX():
        raise ValueError("Histograms must have the same number of bins")

    for i in range(1, h1.GetNbinsX() + 1):
        bin_content = h1.GetBinContent(i) + h2.GetBinContent(i)
        bin_error = bin_content ** 0.5
        h1.SetBinContent(i, bin_content)
        h1.SetBinError(i, bin_error)


def getYmax(histograms: List[ROOT.TH1]) -> float:
    """
    Get maximum Y value across histograms.

    Args:
        histograms: List of histograms

    Returns:
        Maximum Y value
    """
    max_y = -1.0
    for hist in histograms:
        if hist:
            current_max_y = hist.GetMaximum()
            if current_max_y > max_y:
                max_y = current_max_y
    return max_y


def getSysList(rootFile: ROOT.TFile, variable: str) -> List[str]:
    """
    Get list of systematic variations from ROOT file.

    Args:
        rootFile: Open ROOT file
        variable: Variable name to look for

    Returns:
        List of systematic variation suffixes
    """
    histList = []
    sysList = []
    for key in rootFile.GetListOfKeys():
        obj = key.ReadObj()
        histName = obj.GetName()
        if isinstance(obj, ROOT.TH1):
            histList.append(histName)
            if '_up' in histName or '_down' in histName:
                iSys = histName[histName.find(variable) + len(variable) + 1:]
                sysList.append(iSys)
    return sysList


def getHistName(
    regionList: List[str],
    varList: List[str],
    isub: str
) -> List[str]:
    """
    Generate histogram names for subprocess.

    Args:
        regionList: List of region names
        varList: List of variable names
        isub: Subprocess name

    Returns:
        List of histogram names
    """
    histNames = []
    for iRe in regionList:
        for ivar in varList:
            iHist = f'{isub}_{iRe}_{ivar}'
            histNames.append(iHist)
    return histNames


def merge_dicts(dict1: dict, dict2: dict) -> dict:
    """
    Deep merge two dictionaries.

    Args:
        dict1: First dictionary
        dict2: Second dictionary

    Returns:
        Merged dictionary
    """
    merged_dict = {}
    for key in dict1.keys() | dict2.keys():
        if key in dict1 and key in dict2:
            if isinstance(dict1[key], dict) and isinstance(dict2[key], dict):
                merged_dict[key] = merge_dicts(dict1[key], dict2[key])
            else:
                merged_dict[key] = [dict1[key], dict2[key]]
        elif key in dict1:
            merged_dict[key] = dict1[key]
        else:
            merged_dict[key] = dict2[key]
    return merged_dict


def print_dict_structure(dictionary: dict, indent: int = 0) -> None:
    """
    Print nested dictionary structure.

    Args:
        dictionary: Dictionary to print
        indent: Current indentation level
    """
    for key, value in dictionary.items():
        print("\t" * indent + str(key))
        if isinstance(value, dict):
            print_dict_structure(value, indent + 1)


def getEff(h_de: ROOT.TH1, h_nu: ROOT.TH1) -> ROOT.TGraphAsymmErrors:
    """
    Calculate efficiency as TGraphAsymmErrors.

    Args:
        h_de: Denominator histogram
        h_nu: Numerator histogram

    Returns:
        Efficiency graph with Clopper-Pearson errors
    """
    eff = ROOT.TGraphAsymmErrors()
    eff.Divide(h_nu, h_de, "cp")  # Clopper-Pearson interval
    eff.SetTitle(h_de.GetTitle())
    eff.SetName(h_de.GetName())
    return eff


# =============================================================================
# Advanced Histogram Operations
# =============================================================================

def getHistFromFileDic(
    fileName: str,
    regionList: List[str],
    varList: List[str],
    subPro: str,
    sumProSys: Dict,
    era: str,
    sumPro: str = ''
) -> Tuple[Dict, Dict]:
    """
    Get histograms organized by variable/region/subprocess.

    Args:
        fileName: ROOT file path
        regionList: List of regions
        varList: List of variables
        subPro: Subprocess name
        sumProSys: Systematic dictionary per summed process
        era: Era string
        sumPro: Summed process name

    Returns:
        Tuple of (nominal histograms dict, systematic histograms dict)
    """
    file = ROOT.TFile.Open(fileName)
    if not file or file.IsZombie():
        print(f"Error: Unable to open file {fileName}")
        return {}, {}

    subProHist: Dict = {}
    subProHistSys: Dict = {}

    # Build list of all histogram names we need (for efficient batch reading)
    hist_names_needed = set()
    for ivar in varList:
        for ire in regionList:
            # Nominal histogram
            hist_names_needed.add(f'{subPro}_{ire}_{ivar}')
            # Systematic histograms
            if sumPro in sumProSys:
                for isys in sumProSys[sumPro]:
                    hist_names_needed.add(f'{subPro}_{ire}_{isys}Up_{ivar}')
                    hist_names_needed.add(f'{subPro}_{ire}_{isys}Down_{ivar}')

    # Read all histograms at once from the open file
    hist_cache: Dict[str, ROOT.TH1] = {}
    for name in hist_names_needed:
        hist = file.Get(name)
        if hist:
            cloned = hist.Clone()
            cloned.SetDirectory(0)
            hist_cache[name] = cloned

    # Organize into output dictionaries
    for ivar in varList:
        subProHist[ivar] = {}
        subProHistSys[ivar] = {}
        for ire in regionList:
            histName = f'{subPro}_{ire}_{ivar}'
            subProHist[ivar][ire] = {}
            if histName in hist_cache:
                subProHist[ivar][ire][subPro] = hist_cache[histName]
            else:
                print(f"Warning: Histogram {histName} not found in {fileName}")
                continue

            # Get systematic histograms from cache
            subProHistSys[ivar][ire] = {}
            sysDic: Dict[str, ROOT.TH1] = {}
            if sumPro in sumProSys:
                for isys in sumProSys[sumPro]:
                    isysUp = f'{subPro}_{ire}_{isys}Up_{ivar}'
                    isysDown = f'{subPro}_{ire}_{isys}Down_{ivar}'
                    if isysUp in hist_cache and isysDown in hist_cache:
                        sysDic[f'{isys}_up'] = hist_cache[isysUp]
                        sysDic[f'{isys}_down'] = hist_cache[isysDown]
            subProHistSys[ivar][ire][subPro] = sysDic

    file.Close()
    return subProHist, subProHistSys


def _getSysHistNames(
    sumProSys: Dict,
    subPro: str,
    region: str,
    var: str,
    era: str,
    fileName: str,
    sumPro: str = ''
) -> Dict[str, ROOT.TH1]:
    """
    Get systematic histograms for a subprocess.

    Args:
        sumProSys: Systematic dictionary
        subPro: Subprocess name
        region: Region name
        var: Variable name
        era: Era string
        fileName: ROOT file path
        sumPro: Summed process name

    Returns:
        Dictionary of systematic histograms
    """
    sysDic: Dict[str, ROOT.TH1] = {}
    if sumPro in sumProSys:
        for isys in sumProSys[sumPro]:
            isysUp = f'{subPro}_{region}_{isys}Up_{var}'
            isysDown = f'{subPro}_{region}_{isys}Down_{var}'
            try:
                hists = getHistFromFile(fileName, [isysUp, isysDown])
                sysDic[f'{isys}_up'] = hists[0]
                sysDic[f'{isys}_down'] = hists[1]
            except (ValueError, IndexError):
                pass  # Skip missing systematics
    return sysDic


def sumProDic(subProHists: Dict, sumProDicMapping: Dict) -> Dict:
    """
    Sum subprocess histograms into summed process histograms.

    Args:
        subProHists: Subprocess histogram dictionary [var][region][subPro]
        sumProDicMapping: Mapping from subprocess to summed process

    Returns:
        Summed process histogram dictionary [var][region][sumPro]
    """
    sumProHists: Dict = {}
    for ivar, reDic in subProHists.items():
        sumProHists[ivar] = {}
        for ire, subProDict in reDic.items():
            sumProHists[ivar][ire] = {}
            for isub, systs in subProDict.items():
                sumPro = sumProDicMapping.get(isub, isub)
                if isinstance(systs, dict):
                    if sumPro not in sumProHists[ivar][ire]:
                        sumProHists[ivar][ire][sumPro] = {}
                        for isys, hist in systs.items():
                            sumProHists[ivar][ire][sumPro][isys] = hist.Clone()
                            sumName = sumProHists[ivar][ire][sumPro][isys].GetName()
                            sumName = sumName.replace(isub, sumPro)
                            sumProHists[ivar][ire][sumPro][isys].SetName(sumName)
                    else:
                        for isys, hist in systs.items():
                            if isys in sumProHists[ivar][ire][sumPro]:
                                sumProHists[ivar][ire][sumPro][isys].Add(hist)
                else:
                    if sumPro not in sumProHists[ivar][ire]:
                        sumProHists[ivar][ire][sumPro] = systs.Clone()
                        sumHistName = sumProHists[ivar][ire][sumPro].GetName()
                        sumHistName = sumHistName.replace(isub, sumPro)
                        sumProHists[ivar][ire][sumPro].SetName(sumHistName)
                    else:
                        sumProHists[ivar][ire][sumPro].Add(systs)

    return sumProHists


# =============================================================================
# Full Histogram Aggregation
# =============================================================================

def _modifyDicForMCFTau(allDic: Dict[str, str], sumList: List[str]) -> None:
    """
    Modify process dictionary to split MC fake tau contributions.

    For MC fake tau studies, splits each subprocess into:
    - {subprocess}_NotMCFT: Non-fake tau contribution
    - {subprocess}_MCFT: MC fake tau contribution

    Args:
        allDic: Process dictionary (modified in place)
        sumList: List of summed processes to include
    """
    from fourtop.utils.process import isData

    updatedDic = {}
    for isub, sumPro in allDic.items():
        if isData(isub):
            continue
        if sumPro == 'fakeTau' or sumPro == 'fakeLepton':
            continue
        if sumPro == 'tttt':
            continue
        if sumPro not in sumList:
            continue
        # Update isub in allDic with postfix
        updatedDic[isub + '_NotMCFT'] = sumPro
        updatedDic[isub + '_MCFT'] = 'fakeTauMC'

    # Remove original keys and add updated ones
    for isub in updatedDic:
        original_key = isub[:-len('_MCFT')]
        if original_key in allDic:
            del allDic[original_key]

    allDic.update(updatedDic)
    print('proDic updated with MCFTau\n')


def getSumHist(
    inputDirDic: Dict[str, str],
    regionList: List[str],
    sumProList: List[str],
    sumProSys: Dict,
    varList: List[str],
    era: str = '2018',
    isRun3: bool = False,
    ifDebug: bool = False,
    ifMCFTau: bool = False,
    skip_subprocesses: Optional[List[str]] = None
) -> Tuple[Dict, Dict]:
    """
    Get summed process histograms from ROOT files.

    Aggregates histograms from individual subprocesses into summed process
    categories (e.g., ttbar_0l + ttbar_1l + ttbar_2l -> tt).

    Args:
        inputDirDic: Dict with 'mc' and 'data' input directories
        regionList: List of region names
        sumProList: List of summed process names to include
        sumProSys: Dict of systematics per summed process
        varList: List of variable names
        era: Era string (e.g., '2018')
        isRun3: If True, use Run3 sample definitions
        ifDebug: If True, print debug information
        ifMCFTau: If True, split MC fake tau contributions
        skip_subprocesses: List of subprocess names to skip

    Returns:
        Tuple of:
        - sumProHists[var][region][sumPro]: Nominal histograms
        - sumProHistSys[var][region][sumPro][sys]: Systematic histograms
    """
    from fourtop.utils.process import isData, checkIfOtherYear
    from fourtop.constants.samples import histoGramPerSample, ttX_newMap, Run3Samples

    print('start to get hists and add them from root files')

    # Get sample-to-process mapping
    allDic = histoGramPerSample.copy()
    if 'ttX' not in sumProList:
        allDic.update(ttX_newMap)
    if isRun3:
        allDic = Run3Samples.copy()
    if ifMCFTau:
        _modifyDicForMCFTau(allDic, sumProList)

    # Filter out skipped subprocesses
    if skip_subprocesses:
        for skip_sub in skip_subprocesses:
            if skip_sub in allDic:
                print(f'SKIPPING subprocess: {skip_sub} (negligible contribution)')
                del allDic[skip_sub]

    allSubPro = list(allDic.keys())
    toGetSubHist: Dict = {}
    toGetSubHistSys: Dict = {}

    for isub in allSubPro:
        is_data = isData(isub)
        if allDic[isub] not in sumProList:
            continue  # not getting
        if checkIfOtherYear(isub, era, is_data):
            continue
        if ifDebug:
            print('getting: ', isub)

        inputDir = inputDirDic['data'] if is_data else inputDirDic['mc']

        # Handle MCFT postfixes
        if isub.endswith('_MCFT'):
            iroot = isub.removesuffix('_MCFT')
        elif isub.endswith('_NotMCFT'):
            iroot = isub.removesuffix('_NotMCFT')
        else:
            iroot = isub
        rootFile = inputDir + iroot + '.root'

        print('opening file:', rootFile)
        isubProHist, isubProHistSys = getHistFromFileDic(
            rootFile, regionList, varList, isub, sumProSys, era, allDic[isub]
        )
        print_dict_structure(isubProHist)
        toGetSubHist = merge_dicts(toGetSubHist, isubProHist)
        toGetSubHistSys = merge_dicts(toGetSubHistSys, isubProHistSys)

    print_dict_structure(toGetSubHist)
    print('\n')

    sumProHists = sumProDic(toGetSubHist, allDic)
    sumProHistsSys = sumProDic(toGetSubHistSys, allDic)
    print_dict_structure(sumProHists)
    print_dict_structure(sumProHistsSys)

    return sumProHists, sumProHistsSys
