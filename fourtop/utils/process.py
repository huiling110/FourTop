"""
Process Identification and Filtering
=====================================

Utilities for identifying and filtering physics processes.

Usage:
    from fourtop.utils.process import isData, isBG, getAllSubPro

    if isData('jetHT_2018a'):
        print('This is data')

    subprocesses = getAllSubPro('2018', ['tt', 'ttX'], isData=False)
"""

from typing import List, Dict, Set

from fourtop.constants.samples import (
    histoGramPerSample,
    ttX_newMap,
    Run3Samples,
    dataDict,
    proChannelDic,
    proChannelDic_forCombine,
)


def isData(subPro: str) -> bool:
    """
    Check if a subprocess is data.

    Args:
        subPro: Subprocess name

    Returns:
        True if subprocess is data
    """
    data_patterns = [
        'jetHT', 'singleMu', 'BTagCSV', 'doubleMu', 'MuonEG',
        'eGamma', 'singleE', 'leptonSum', 'doubleEG',
        'JetHT', 'Muon', 'JetMET'
    ]
    return any(pattern in subPro for pattern in data_patterns)


def isBG(sumPro: str, ifVLL: bool = False) -> int:
    """
    Determine process type.

    Args:
        sumPro: Summed process name
        ifVLL: If True, treat tttt as background (for VLL analysis)

    Returns:
        1 = signal, 2 = background, 3 = data
    """
    if 'jetHT' in sumPro or 'singleMu' in sumPro or 'leptonSum' in sumPro:
        return 3  # data
    elif 'tttt' in sumPro:
        return 1 if not ifVLL else 2  # signal or background
    elif 'VLL' in sumPro:
        return 1  # signal
    else:
        return 2  # background


def getAllSubPro(
    era: str,
    sumPro: List[str],
    isDataFlag: bool = True,
    ifttXDecorrelate: bool = False
) -> List[str]:
    """
    Get all subprocesses for a summed process list.

    Args:
        era: Era string (e.g., '2018')
        sumPro: List of summed process names
        isDataFlag: If True, filter data by era
        ifttXDecorrelate: If True, use ttX decorrelated mapping

    Returns:
        List of subprocess names
    """
    all_samples = histoGramPerSample.copy()
    if ifttXDecorrelate:
        all_samples.update(ttX_newMap)

    allSubs = []
    if isDataFlag:
        for isub, isum in all_samples.items():
            if isum not in sumPro:
                continue
            # Get the substring after first '_'
            parts = isub.split('_', 1)
            if len(parts) > 1:
                subEra = parts[1]
                if subEra in dataDict.get(era, []) and isum in sumPro:
                    allSubs.append(isub)
        return allSubs
    else:
        return [isub for isub, isum in all_samples.items() if isum in sumPro]


def getSubProDic(era: str, sumPro: List[str]) -> Dict[str, List[str]]:
    """
    Get subprocess dictionary grouped by summed process.

    Args:
        era: Era string
        sumPro: List of summed process names

    Returns:
        Dictionary mapping summed process to list of subprocesses
    """
    allSubs: Dict[str, List[str]] = {}
    for isub, isum in histoGramPerSample.items():
        if isum not in sumPro:
            continue
        is_data = isData(isub)
        if is_data:
            parts = isub.split('_', 1)
            if len(parts) > 1:
                subEra = parts[1]
                if subEra in dataDict.get(era, []):
                    if isum not in allSubs:
                        allSubs[isum] = []
                    allSubs[isum].append(isub)
        else:
            if isum not in allSubs:
                allSubs[isum] = []
            allSubs[isum].append(isub)
    return allSubs


def getSubProScale(subPro: str, era: str) -> float:
    """
    Calculate scale factor for a subprocess.

    Args:
        subPro: Subprocess name
        era: Era string

    Returns:
        Scale factor (lumi * cross / genSum)
    """
    from fourtop.constants.physics import lumiMap, crossSectionMap
    from fourtop.constants.samples import genSumDic

    lumi = lumiMap[era]
    cross = crossSectionMap[subPro]
    genSum = genSumDic[subPro]
    return lumi * cross / genSum


def checkIfOtherYear(isub: str, era: str, is_data: bool) -> bool:
    """
    Check if subprocess belongs to a different year than specified era.

    Args:
        isub: Subprocess name
        era: Era to check against
        is_data: Whether subprocess is data

    Returns:
        True if subprocess is from a different year
    """
    if not is_data:
        return False

    if 'leptonSum' in isub:
        return era not in isub
    else:
        era_list = dataDict.get(era, [])
        parts = isub.split('_')
        if len(parts) > 1:
            iera = '_'.join(parts[1:])
            return iera not in era_list
        return True


def checkIfInputDic(entry: str, is_run3: bool = False) -> bool:
    """
    Check if entry is in the sample dictionary.

    Args:
        entry: Sample name
        is_run3: If True, check Run3 samples

    Returns:
        True if entry is in dictionary
    """
    sample_dict = Run3Samples if is_run3 else histoGramPerSample
    return entry in sample_dict


def getSumList(channel: str, forCombine: bool = False) -> List[str]:
    """
    Get process list for a channel.

    Args:
        channel: Channel name ('1tau0l', '1tau1l', '1tau2l')
        forCombine: If True, return list with split ttX

    Returns:
        List of process names
    """
    proc_dict = proChannelDic_forCombine if forCombine else proChannelDic
    return proc_dict.get(channel, [])


def getSameValues(diction: dict, value) -> List[str]:
    """
    Get all keys in dictionary with the specified value.

    Args:
        diction: Dictionary to search
        value: Value to match

    Returns:
        List of keys with matching value
    """
    return [ikey for ikey, ivalue in diction.items() if ivalue == value]


# =============================================================================
# Era/Channel Detection
# =============================================================================

def getEraFromDir(inputDir: str) -> str:
    """
    Extract era from directory path.

    Args:
        inputDir: Directory path

    Returns:
        Era string (e.g., '2018', '2016preVFP')
    """
    if '2016' in inputDir:
        if '2016post' in inputDir or '2016_post' in inputDir:
            return '2016postVFP'
        elif '2016pre' in inputDir:
            return '2016preVFP'
        else:
            return '2016'
    elif '2017' in inputDir:
        return '2017'
    elif '2018' in inputDir:
        return '2018'
    elif 'Run2' in inputDir:
        return 'Run2'
    elif '2022' in inputDir:
        if '2022preEE' in inputDir:
            return '2022preEE'
        elif '2022postEE' in inputDir:
            return '2022postEE'
        else:
            return '2022'
    return ''


def getChannelFromDir(dir_path: str) -> str:
    """
    Extract channel from directory path.

    Args:
        dir_path: Directory path

    Returns:
        Channel string ('1tau0l', '1tau1l', '1tau2l', or '')
    """
    if '1tau1l' in dir_path:
        return '1tau1l'
    elif '1tau0l' in dir_path:
        return '1tau0l'
    elif '1tau2l' in dir_path:
        return '1tau2l'
    return ''


def isRun3(inputDir: str) -> bool:
    """
    Check if directory is for Run 3 data.

    Args:
        inputDir: Directory path

    Returns:
        True if Run 3
    """
    return '2022' in inputDir


def isRun3Era(era: str) -> bool:
    """
    Check if era is Run 3.

    Args:
        era: Era string

    Returns:
        True if Run 3 era
    """
    return '2022' in era
