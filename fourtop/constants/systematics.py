"""
Systematic Uncertainty Definitions
==================================

CMS Combine systematic definitions for the FourTop analysis.

This module centralizes the MCSys dictionary that was previously embedded
in writeDatacard.py. All systematic uncertainty configurations are defined here.

Format:
    'systematic_name': [is_correlated, process_type, channel_bits, is_process_correlated]

Where:
    - is_correlated (bool): If True, systematic is fully correlated across all eras
                           (no year suffix added). If False, era suffix is added.
    - process_type (int): Which process types this systematic applies to
        - 0 = MC (signal and backgrounds)
        - 1 = fakeTau (data-driven fake tau estimate)
        - 2 = fakeLepton (data-driven fake lepton estimate)
        - 3 = fakeTauMC (MC-based fake tau estimate)
    - channel_bits (int): Bitmask for channels where systematic applies
        - 0b100 = 1tau1l only
        - 0b010 = 1tau0l only
        - 0b001 = 1tau2l only
        - 0b111 = all channels
        - 0b110 = 1tau1l and 1tau0l
        - 0b101 = 1tau1l and 1tau2l
    - is_process_correlated (bool): If True, systematic is correlated between processes
                                    If False, treated as process-uncorrelated

Usage:
    from fourtop.constants.systematics import MCSYS, get_systematics_for_channel

    # Get all systematics for a channel
    sys_dict = get_systematics_for_channel('1tau0l', '2018')
"""

from typing import Dict, List, Set

# Channel bitmask definitions for readability
CHANNEL_1TAU1L = 0b100
CHANNEL_1TAU0L = 0b010
CHANNEL_1TAU2L = 0b001
CHANNEL_ALL = 0b111
CHANNEL_1TAU1L_1TAU0L = 0b110
CHANNEL_1TAU1L_1TAU2L = 0b101

# Process type definitions
PROCESS_MC = 0
PROCESS_FAKE_TAU = 1
PROCESS_FAKE_LEPTON = 2
PROCESS_FAKE_TAU_MC = 3

# =============================================================================
# Main Systematic Dictionary
# =============================================================================

MCSYS: Dict[str, List] = {
    # -------------------------------------------------------------------------
    # Pileup and Prefiring
    # -------------------------------------------------------------------------
    'CMS_pileup': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_l1_ecal_prefiring': [False, PROCESS_MC, CHANNEL_ALL, True],

    # -------------------------------------------------------------------------
    # Trigger Efficiency
    # -------------------------------------------------------------------------
    'CMS_TOP24017_eff_trigger_stats': [False, PROCESS_MC, CHANNEL_1TAU1L_1TAU0L, True],
    'CMS_TOP24017_ttttSS_eff_trigger': [False, PROCESS_MC, CHANNEL_1TAU2L, True],

    # -------------------------------------------------------------------------
    # Tau Fake Rates (DeepTau2017v2p1)
    # Updated 2025-11-27 to CMS naming convention
    # Fully correlated across all years
    # -------------------------------------------------------------------------
    'CMS_fake_t_DeepTau2017v2p1_VSmu': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_fake_t_DeepTau2017v2p1_VSe': [True, PROCESS_MC, CHANNEL_ALL, True],

    # -------------------------------------------------------------------------
    # Tau ID Efficiency (DeepTau2017v2p1)
    # Statistical uncertainties - era-dependent, per decay mode
    # -------------------------------------------------------------------------
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat1_DM0': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat1_DM1': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat1_DM10': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat1_DM11': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat2_DM0': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat2_DM1': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat2_DM10': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_stat2_DM11': [False, PROCESS_MC, CHANNEL_ALL, True],

    # Systematic uncertainties
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_syst_alleras': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_syst': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_syst_DM0': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_syst_DM1': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_syst_DM10': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_eff_t_DeepTau2017v2p1_VSjet_dm_syst_DM11': [False, PROCESS_MC, CHANNEL_ALL, True],

    # -------------------------------------------------------------------------
    # Lepton Efficiency (1tau1l, 1tau2l only)
    # -------------------------------------------------------------------------
    'CMS_TOP24017_ttttSS_eff_e_syst': [True, PROCESS_MC, CHANNEL_1TAU1L_1TAU2L, True],
    'CMS_TOP24017_ttttSS_eff_m_syst': [True, PROCESS_MC, CHANNEL_1TAU1L_1TAU2L, True],
    'CMS_TOP24017_ttttSS_eff_e_stat': [False, PROCESS_MC, CHANNEL_1TAU1L_1TAU2L, True],
    'CMS_TOP24017_ttttSS_eff_m_stat': [False, PROCESS_MC, CHANNEL_1TAU1L_1TAU2L, True],
    # Note: CMS_eff_e_reco_2016preVFP and CMS_eff_e_reco_2016postVFP should be correlated
    'CMS_eff_e_reco': [False, PROCESS_MC, CHANNEL_1TAU1L_1TAU2L, True],

    # -------------------------------------------------------------------------
    # B-tagging: Fixed WP (1tau1l, 1tau2l)
    # -------------------------------------------------------------------------
    'CMS_btag_fixedWP_comb_bc_correlated': [True, PROCESS_MC, CHANNEL_1TAU1L_1TAU2L, True],
    'CMS_btag_fixedWP_comb_bc_uncorrelated': [False, PROCESS_MC, CHANNEL_1TAU1L_1TAU2L, True],
    'CMS_btag_fixedWP_incl_light_correlated': [True, PROCESS_MC, CHANNEL_1TAU1L_1TAU2L, True],
    'CMS_btag_fixedWP_incl_light_uncorrelated': [False, PROCESS_MC, CHANNEL_1TAU1L_1TAU2L, True],

    # -------------------------------------------------------------------------
    # B-tagging: Full Shape (1tau0l only)
    # CMS naming convention with fullShape_ prefix
    # -------------------------------------------------------------------------
    'CMS_btag_fullShape_hf': [True, PROCESS_MC, CHANNEL_1TAU0L, True],
    'CMS_btag_fullShape_lf': [True, PROCESS_MC, CHANNEL_1TAU0L, True],
    'CMS_btag_fullShape_cferr1': [True, PROCESS_MC, CHANNEL_1TAU0L, True],
    'CMS_btag_fullShape_cferr2': [True, PROCESS_MC, CHANNEL_1TAU0L, True],
    'CMS_btag_fullShape_hfstats1': [False, PROCESS_MC, CHANNEL_1TAU0L, True],
    'CMS_btag_fullShape_hfstats2': [False, PROCESS_MC, CHANNEL_1TAU0L, True],
    'CMS_btag_fullShape_lfstats1': [False, PROCESS_MC, CHANNEL_1TAU0L, True],
    'CMS_btag_fullShape_lfstats2': [False, PROCESS_MC, CHANNEL_1TAU0L, True],

    # -------------------------------------------------------------------------
    # Fake Tau Data-Driven Estimate
    # -------------------------------------------------------------------------
    'CMS_fake_t': [False, PROCESS_FAKE_TAU, CHANNEL_ALL, True],

    # -------------------------------------------------------------------------
    # Fake Tau MC Estimate (1tau1l, 1tau2l only)
    # -------------------------------------------------------------------------
    'CMS_TOP24017_fake_t_MC': [True, PROCESS_FAKE_TAU_MC, CHANNEL_1TAU1L_1TAU2L, True],

    # -------------------------------------------------------------------------
    # PDF and QCD Scale
    # -------------------------------------------------------------------------
    'pdf_alphas': [True, PROCESS_MC, CHANNEL_ALL, True],
    'pdf_00': [True, PROCESS_MC, CHANNEL_ALL, True],  # PDF envelope
    'QCDscale_ren': [True, PROCESS_MC, CHANNEL_ALL, False],  # Process-uncorrelated
    'QCDscale_fac': [True, PROCESS_MC, CHANNEL_ALL, False],  # Process-uncorrelated
    'ps_isr': [True, PROCESS_MC, CHANNEL_ALL, False],  # Process-uncorrelated
    'ps_fsr': [True, PROCESS_MC, CHANNEL_ALL, True],

    # -------------------------------------------------------------------------
    # JES (Jet Energy Scale)
    # Based on: https://docs.google.com/spreadsheets/d/1JZfk78_9SD225bcUuTWVo4i02vwI5FfeVKH-dwzUdhM
    # -------------------------------------------------------------------------
    'CMS_scale_j_AbsoluteMPFBias': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_AbsoluteScale': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_AbsoluteStat': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_Fragmentation': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_PileUpDataMC': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_PileUpPtBB': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_PileUpPtEC1': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_PileUpPtEC2': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_PileUpPtHF': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_PileUpPtRef': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_RelativeFSR': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_RelativeJEREC1': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_RelativeJEREC2': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_RelativeJERHF': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_RelativePtBB': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_RelativePtEC1': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_RelativePtEC2': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_RelativePtHF': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_RelativeBal': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_RelativeSample': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_RelativeStatEC': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_RelativeStatFSR': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_RelativeStatHF': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_SinglePionECAL': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_SinglePionHCAL': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_TimePtEta': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_FlavorPureGluon': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_FlavorPureQuark': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_FlavorPureCharm': [True, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_j_FlavorPureBottom': [True, PROCESS_MC, CHANNEL_ALL, True],

    # -------------------------------------------------------------------------
    # JER (Jet Energy Resolution)
    # -------------------------------------------------------------------------
    'CMS_res_j': [False, PROCESS_MC, CHANNEL_ALL, True],

    # -------------------------------------------------------------------------
    # TES (Tau Energy Scale)
    # Updated naming: DeepTau2017v2p1 with genTau qualifier
    # Note: 2016preVFP/postVFP merged to 2016 via VFP era mapping
    # -------------------------------------------------------------------------
    'CMS_scale_t_DeepTau2017v2p1_DM0_genTau': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_t_DeepTau2017v2p1_DM1_genTau': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_t_DeepTau2017v2p1_DM10_genTau': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_t_DeepTau2017v2p1_DM11_genTau': [False, PROCESS_MC, CHANNEL_ALL, True],

    # -------------------------------------------------------------------------
    # MET and Electron Energy Scale
    # -------------------------------------------------------------------------
    'CMS_scale_met_unclustered_energy': [False, PROCESS_MC, CHANNEL_ALL, True],
    'CMS_scale_e': [False, PROCESS_MC, CHANNEL_1TAU1L_1TAU2L, True],
}


# =============================================================================
# Helper Functions
# =============================================================================

def get_channel_bit(channel: str) -> int:
    """
    Get the bitmask for a channel.

    Args:
        channel: Channel name ('1tau0l', '1tau1l', '1tau2l')

    Returns:
        Bitmask for the channel.
    """
    channel_map = {
        '1tau1l': CHANNEL_1TAU1L,
        '1tau0l': CHANNEL_1TAU0L,
        '1tau2l': CHANNEL_1TAU2L,
    }
    return channel_map.get(channel, 0)


def systematic_applies_to_channel(sys_name: str, channel: str) -> bool:
    """
    Check if a systematic applies to a given channel.

    Args:
        sys_name: Systematic name (key in MCSYS)
        channel: Channel name ('1tau0l', '1tau1l', '1tau2l')

    Returns:
        True if systematic applies to channel.
    """
    if sys_name not in MCSYS:
        return False
    channel_bits = MCSYS[sys_name][2]
    channel_bit = get_channel_bit(channel)
    return bool(channel_bits & channel_bit)


def get_systematics_for_channel(channel: str, process_type: int = None) -> Dict[str, List]:
    """
    Get all systematics applicable to a channel.

    Args:
        channel: Channel name ('1tau0l', '1tau1l', '1tau2l')
        process_type: Optional filter by process type (0=MC, 1=fakeTau, etc.)

    Returns:
        Dictionary of systematics that apply to the channel.
    """
    channel_bit = get_channel_bit(channel)
    result = {}

    for sys_name, sys_config in MCSYS.items():
        channel_bits = sys_config[2]
        if channel_bits & channel_bit:
            if process_type is None or sys_config[1] == process_type:
                result[sys_name] = sys_config

    return result


def get_correlated_systematics() -> Set[str]:
    """
    Get set of systematics that are fully correlated across eras.

    Returns:
        Set of systematic names that are era-correlated.
    """
    return {name for name, config in MCSYS.items() if config[0]}


def get_era_dependent_systematics() -> Set[str]:
    """
    Get set of systematics that are era-dependent (need year suffix).

    Returns:
        Set of systematic names that need era suffix.
    """
    return {name for name, config in MCSYS.items() if not config[0]}


def is_process_uncorrelated(sys_name: str) -> bool:
    """
    Check if a systematic is process-uncorrelated.

    Process-uncorrelated systematics get different nuisance parameters
    for different physics processes (e.g., QCDscale_ren for tttt vs ttbar).

    Args:
        sys_name: Systematic name

    Returns:
        True if systematic is process-uncorrelated.
    """
    if sys_name not in MCSYS:
        return False
    return not MCSYS[sys_name][3]
