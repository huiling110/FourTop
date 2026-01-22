"""
Era Constants and Mappings
==========================

Consolidated era handling for Run 2 analysis. This module centralizes
all VFP era mapping logic that was previously duplicated across:
- workflow_utils.py
- writeDatacard.py
- addTemplateNew.py
- addJESTemplatesToHistFile.py
- pl.py

Usage:
    from fourtop.constants.era import ERAS, map_vfp_era, ERA_TO_UL

    # Map VFP era to 2016 for correlated systematics
    mapped_era = map_vfp_era('2016preVFP', correlate=True)  # Returns '2016'

    # Get UL path era
    ul_era = ERA_TO_UL['2018']  # Returns 'UL2018'
"""

from typing import Set, Dict, List

# =============================================================================
# Era Definitions
# =============================================================================

#: All Run 2 eras used in analysis
ERAS: List[str] = ['2018', '2017', '2016preVFP', '2016postVFP']

#: VFP (Very Forward Pixel) eras that need special handling for correlations
VFP_ERAS: Set[str] = {'2016preVFP', '2016postVFP'}

# =============================================================================
# Era Mappings
# =============================================================================

#: Map analysis era to UL (Ultra-Legacy) path convention for Stage 1 outputs
ERA_TO_UL: Dict[str, str] = {
    '2016postVFP': 'UL2016_postVFP',
    '2016preVFP': 'UL2016_preVFP',
    '2016': 'UL2016_postVFP',  # Default 2016 maps to postVFP
    '2016APV': 'UL2016_preVFP',  # APV is alias for preVFP
    '2017': 'UL2017',
    '2018': 'UL2018',
}

#: Map analysis era to NanoAOD input directory naming
ERA_TO_NANOAOD: Dict[str, str] = {
    '2016postVFP': '2016',
    '2016preVFP': '2016APV',
    '2016': '2016',
    '2016APV': '2016APV',
    '2017': '2017',
    '2018': '2018',
}

#: Map era to luminosity year for systematic naming (VFP merged to 2016)
ERA_TO_LUMI_YEAR: Dict[str, str] = {
    '2016preVFP': '2016',
    '2016postVFP': '2016',
    '2017': '2017',
    '2018': '2018',
}

# =============================================================================
# VFP Correlation Handling
# =============================================================================

#: Systematics that should be correlated across VFP eras (use '2016' suffix)
#: These systematics are measured for combined 2016 dataset
VFP_CORRELATED_SYSTEMATICS: List[str] = [
    'CMS_eff_e_reco',
    'CMS_scale_t_DeepTau2017v2p1_DM0_genTau',
    'CMS_scale_t_DeepTau2017v2p1_DM1_genTau',
    'CMS_scale_t_DeepTau2017v2p1_DM10_genTau',
    'CMS_scale_t_DeepTau2017v2p1_DM11_genTau',
    'CMS_l1_ecal_prefiring',
]


def map_vfp_era(era: str, correlate: bool = True) -> str:
    """
    Map VFP era to '2016' if correlation is desired.

    For certain systematics (TES, prefiring, electron reco), the 2016preVFP
    and 2016postVFP eras should be treated as correlated '2016' in datacards.

    Args:
        era: Era string (e.g., '2016preVFP', '2017', '2018')
        correlate: If True, map VFP eras to '2016'. If False, return unchanged.

    Returns:
        Mapped era string. VFP eras become '2016' when correlate=True.

    Example:
        >>> map_vfp_era('2016preVFP', correlate=True)
        '2016'
        >>> map_vfp_era('2016preVFP', correlate=False)
        '2016preVFP'
        >>> map_vfp_era('2018', correlate=True)
        '2018'
    """
    if correlate and era in VFP_ERAS:
        return '2016'
    return era


def is_vfp_era(era: str) -> bool:
    """
    Check if era is a VFP (2016preVFP or 2016postVFP) era.

    Args:
        era: Era string to check.

    Returns:
        True if era is VFP, False otherwise.
    """
    return era in VFP_ERAS


def get_ul_era(era: str) -> str:
    """
    Get UL (Ultra-Legacy) path convention for an era.

    Args:
        era: Analysis era string.

    Returns:
        UL era string for path construction.

    Raises:
        KeyError: If era is not recognized.
    """
    if era not in ERA_TO_UL:
        raise KeyError(f"Unknown era '{era}'. Valid eras: {list(ERA_TO_UL.keys())}")
    return ERA_TO_UL[era]


def get_nanoaod_era(era: str) -> str:
    """
    Get NanoAOD input directory era naming.

    Args:
        era: Analysis era string.

    Returns:
        NanoAOD directory era string.

    Raises:
        KeyError: If era is not recognized.
    """
    if era not in ERA_TO_NANOAOD:
        raise KeyError(f"Unknown era '{era}'. Valid eras: {list(ERA_TO_NANOAOD.keys())}")
    return ERA_TO_NANOAOD[era]


def get_lumi_year(era: str) -> str:
    """
    Get luminosity year for an era (VFP eras return '2016').

    Args:
        era: Analysis era string.

    Returns:
        Year string for luminosity/systematic naming.
    """
    return ERA_TO_LUMI_YEAR.get(era, era)
