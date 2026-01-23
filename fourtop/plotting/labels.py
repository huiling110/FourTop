"""
Publication-quality label mappings for CMS plots.

This module provides standardized labels for physics processes,
regions, and other plot elements following paper conventions.

Usage:
    from fourtop.plotting.labels import PROCESS_LABELS_PAPER, REGION_LABELS, get_signal_label
"""

from typing import Dict, Optional

# =============================================================================
# Process Label Mappings
# =============================================================================

#: Publication-quality process labels (paper convention)
PROCESS_LABELS_PAPER: Dict[str, str] = {
    # Signal
    'tttt': 't#bar{t}t#bar{t}',

    # Main backgrounds
    'tt': 't#bar{t}',
    'ttX': 'ttX',  # Keep as-is per paper convention
    'ttZ': 't#bar{t}Z',
    'ttW': 't#bar{t}W',
    'ttH': 't#bar{t}H',
    'ttG': 't#bar{t}#gamma',
    'ttbb': 't#bar{t}b#bar{b}',

    # Fake backgrounds
    'fakeTau': 'fake #tau_{h}',  # Paper convention
    'fakeLepton': 'fake lepton',
    'fakeTauMC': 'fake #tau_{h} (MC)',

    # Other backgrounds
    'Minor': 'Other',
    'singleTop': 'Single t',
    'VV': 'Diboson',
    'VVV': 'Triboson',
    'WJets': 'W+jets',
    'DY': 'DY',
    'Higgs': 'Higgs',
    'XGamma': 'X#gamma',
    'qcd': 'QCD multijet',

    # VLL signals
    'VLLm600': 'VLL (600 GeV)',
    'VLLm700': 'VLL (700 GeV)',
    'VLLm800': 'VLL (800 GeV)',

    # Data
    'jetHT': 'Data',
    'leptonSum': 'Data',
}

#: Default process labels (internal names, for non-paper mode)
PROCESS_LABELS_DEFAULT: Dict[str, str] = {
    'tttt': 'tttt',
    'tt': 'tt',
    'ttX': 'ttX',
    'fakeTau': 'fakeTau',
    'fakeLepton': 'fakeLepton',
    'Minor': 'Minor',
    'singleTop': 'singleTop',
    'VV': 'VV',
    'jetHT': 'Data',
    'leptonSum': 'Data',
}


# =============================================================================
# Region Label Mappings
# =============================================================================

#: Region labels for plot annotations
REGION_LABELS: Dict[str, str] = {
    # Signal regions
    'SR1tau0l': 'SR 1#tau_{h}0#ell',
    'SR1tau1l': 'SR 1#tau_{h}1#ell',
    'SR1tau2l': 'SR 1#tau_{h}2#ell',
    '1tau0lSR': 'SR 1#tau_{h}0#ell',
    '1tau1lSR': 'SR 1#tau_{h}1#ell',
    '1tau2lSR': 'SR 1#tau_{h}2#ell',

    # Control regions
    'CR1tau0l': 'CR 1#tau_{h}0#ell',
    'CR1tau1l': 'CR 1#tau_{h}1#ell',
    'CR1tau2l': 'CR 1#tau_{h}2#ell',

    # Combined regions
    'SR1tau0l1l2l': 'SR Combined',
    'SR1tau1land2l': 'SR 1#tau_{h}1#ell+2#ell',
}


# =============================================================================
# Helper Functions
# =============================================================================

def get_process_label(process: str, paper_mode: bool = True) -> str:
    """
    Get display label for a physics process.

    Args:
        process: Internal process name (e.g., 'tttt', 'fakeTau')
        paper_mode: If True, use publication-quality labels

    Returns:
        Formatted label string (ROOT TLatex format)
    """
    if paper_mode:
        return PROCESS_LABELS_PAPER.get(process, process)
    else:
        return PROCESS_LABELS_DEFAULT.get(process, process)


def get_signal_label(
    process: str,
    scale: int = 1,
    yield_val: Optional[float] = None,
    paper_mode: bool = True
) -> str:
    """
    Get formatted signal label with optional scaling and yield.

    Args:
        process: Signal process name (e.g., 'tttt', 'VLLm700')
        scale: Scale factor applied to signal (e.g., 100)
        yield_val: Optional yield value to display
        paper_mode: If True, use publication-quality labels

    Returns:
        Formatted signal label (e.g., "t#bar{t}t#bar{t} #times 100 [4.4]")
    """
    label = get_process_label(process, paper_mode)

    if scale != 1:
        label = f"{label} #times {scale}"

    if yield_val is not None:
        label = f"{label} [{yield_val:.1f}]"

    return label


def get_region_label(region: str) -> str:
    """
    Get formatted region label for plot annotation.

    Args:
        region: Region code (e.g., 'SR1tau0l', '1tau1lSR')

    Returns:
        Formatted region label (e.g., "SR 1#tau_{h}0#ell")
    """
    return REGION_LABELS.get(region, region)


def get_fit_type_label(is_postfit: bool) -> str:
    """
    Get fit type label for plot annotation.

    Args:
        is_postfit: True for post-fit, False for pre-fit

    Returns:
        "Post-fit" or "Pre-fit"
    """
    return "Post-fit" if is_postfit else "Pre-fit"
