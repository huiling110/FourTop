"""
Physics Constants
=================

Luminosity and cross-section values for the FourTop analysis.

Usage:
    from fourtop.constants.physics import lumiMap, crossSectionMap

    lumi_2018 = lumiMap['2018']  # 59830.0 pb^-1
    xsec_tttt = crossSectionMap['tttt']  # 0.01337 pb
"""

from typing import Dict

# =============================================================================
# Integrated Luminosity (pb^-1)
# =============================================================================

#: Integrated luminosity per era (pb^-1)
lumiMap: Dict[str, float] = {
    "2016preVFP": 19500.,
    "2016postVFP": 16810.,
    "2016": 36310.,
    "2017": 41480.0,
    "2018": 59830.0,
    "Run2": 137620.0,
    "2022": 37300,
    "2022preEE": 7875,
    "2022postEE": 26377,
}

# =============================================================================
# Cross Sections (pb)
# =============================================================================

#: Cross-sections for all physics processes (pb)
crossSectionMap: Dict[str, float] = {
    # Signal
    "tttt": 0.01337,

    # ttbar (inclusive decay modes)
    "ttbar_0l": 377.96,
    "ttbar_1l": 365.34,
    "ttbar_2l": 88.29,

    # TTBB 4-flavor scheme cross-sections at 13 TeV
    # Scaled from ttH(H->bb) AN: 43.74 * (17.75/21.34) = 36.3 pb total
    "TTBB_4f_TTToHadronic": 16.52,      # 36.3 * 0.455 (hadronic BR)
    "TTBB_4f_TTToSemiLeptonic": 15.97,  # 36.3 * 0.440 (semileptonic BR)
    "TTBB_4f_TTTo2L2Nu": 3.85,          # 36.3 * 0.106 (dilepton BR)

    # ttX processes
    "ttG": 15.89,
    "ttZ": 0.783,
    "ttW": 0.611,
    "ttH_bb": 0.2897,
    "ttH_nonbb": 0.209,
    "ttWW": 0.00698,

    # Diboson
    "wz": 47.,
    "ww": 118.,
    "zz": 16.5,

    # Triboson
    "WWW": 0.2086,
    "WWZ": 0.1651,
    "WZZ": 0.05565,
    "ZZZ": 0.01476,

    # Single top
    "st_tZq": 0.07358,
    "st_tW_antitop": 35.85,
    "st_tW_top": 35.85,

    # Gamma + X
    'TGJets': 1.02,
    'ZGToLLG': 55.48,
    'WGToLNuG': 192,

    # Higgs (ggF)
    'ggH_bb': 28.3,
    'ggH_tautau': 3.05,
    'ggH_WW_2l': 1.10,
    'ggH_ZZ_2l': 28.87,
    'ggH_ZZ_4l': 0.01212,
    'ggH_gg': 0.01,

    # Higgs (VBF)
    'vbfH_bb': 2.20,
    'vbfH_tautau': 0.237,
    'vbfH_WW_2l': 0.0859,
    'VH_nonbb': 0.942,

    # Drell-Yan
    "DYJetsToLL_M-10to50": 15810.0,
    "DYJetsToLL_M-50": 6077.22,

    # QCD (Run 2 binning)
    "qcd_50to100": 2.466e+08,
    "qcd_100to200": 2.801e+07,
    "qcd_200to300": 1.721e+6,
    "qcd_300to500": 3.479e+05,
    "qcd_500to700": 3.206e+04,
    "qcd_700to1000": 6.827e+03,
    "qcd_1000to1500": 1.207e+03,
    "qcd_1500to2000": 1.20e+02,
    "qcd_2000toInf": 2.525e+01,

    # W+jets
    "WJetsToLNu_HT-200To400": 532.4,
    "WJetsToLNu_HT-400To600": 61.6,
    "WJetsToLNu_HT-600To800": 12.4,
    "WJetsToLNu_HT-800To1200": 5.77,
    "WJetsToLNu_HT-1200To2500": 1.023,
    "WJetsToLNu_HT-2500ToInf": 0.0248,

    # QCD (Run 3 binning)
    "QCD_PT-30to50": 112800000.0,
    "QCD_PT-50to80": 16660000.0,
    "QCD_PT-80to120": 2507000.0,
    "QCD_PT-120to170": 441100.0,
    "QCD_PT-170to300": 113400.0,
    "QCD_PT-300to470": 7589.0,
    "QCD_PT-470to600": 626.4,
    "QCD_PT-600to800": 178.6,
    "QCD_PT-800to1000": 30.57,
    "QCD_PT-1000to1400": 8.92,
    "QCD_PT-1400to1800": 0.8103,
    "QCD_PT-1800to2400": 0.1148,
    "QCD_PT-2400to3200": 0.007542,
    "QCD_PT-3200": 0.0002331,

    # ttbar (Run 3 naming)
    "TTto4Q": 419.69,
    "TTto2L2Nu": 98.09,
    "TTtoLNu2Q": 405.80,
    "TTTT": 0.0158,

    # VLL signal (various masses)
    "VLL_EE_M500": 0.004918,
    "VLL_EN_M500": 0.008811 * 1.98,
    "VLL_NN_M500": 0.001194 * 3.96,
    "VLL_EE_M550": 0.003158,
    "VLL_EN_M550": 0.005739 * 1.98,
    "VLL_NN_M550": 0.0007615 * 3.96,
    "VLL_EE_M600": 0.002079,
    "VLL_EN_M600": 0.003743 * 1.98,
    "VLL_NN_M600": 0.0004964 * 3.96,
    "VLL_EE_M650": 0.001397,
    "VLL_EN_M650": 0.002551 * 1.98,
    "VLL_NN_M650": 0.0003352 * 3.96,
    "VLL_EE_M700": 0.0009504,
    "VLL_EN_M700": 0.001747 * 1.98,
    "VLL_NN_M700": 0.0002255 * 3.96,
    "VLL_EE_M750": 0.0006623,
    "VLL_EN_M750": 0.001215 * 1.98,
    "VLL_NN_M750": 0.0001578 * 3.96,
    "VLL_EE_M800": 0.0004645,
    "VLL_EN_M800": 0.0008622 * 1.98,
    "VLL_NN_M800": 0.0001095 * 3.96,
    "VLL_EE_M850": 0.0003267,
    "VLL_EN_M850": 0.000606 * 1.98,
    "VLL_NN_M850": 7.764e-5 * 3.96,
    "VLL_EE_M900": 0.0002385,
    "VLL_EN_M900": 0.0004428 * 1.98,
    "VLL_NN_M900": 5.562e-5 * 3.96,
    "VLL_EE_M950": 0.0001715,
    "VLL_EN_M950": 0.0003206 * 1.98,
    "VLL_NN_M950": 4e-5 * 3.96,
    "VLL_EE_M1000": 0.0001241,
    "VLL_EN_M1000": 0.0002329 * 1.98,
    "VLL_NN_M1000": 2.909e-5 * 3.96,
}


def get_cross_section(process: str) -> float:
    """
    Get cross-section for a physics process.

    Args:
        process: Process name (e.g., 'tttt', 'ttbar_2l')

    Returns:
        Cross-section in pb.

    Raises:
        KeyError: If process not found.
    """
    if process not in crossSectionMap:
        raise KeyError(f"Unknown process '{process}'. Check crossSectionMap.")
    return crossSectionMap[process]


def get_luminosity(era: str) -> float:
    """
    Get integrated luminosity for an era.

    Args:
        era: Era string (e.g., '2018', '2017', 'Run2')

    Returns:
        Integrated luminosity in pb^-1.

    Raises:
        KeyError: If era not found.
    """
    if era not in lumiMap:
        raise KeyError(f"Unknown era '{era}'. Check lumiMap.")
    return lumiMap[era]
