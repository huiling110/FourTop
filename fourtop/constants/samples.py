"""
Sample Definitions and Process Mappings
=======================================

Sample-to-process mappings for histogram aggregation and analysis.

Usage:
    from fourtop.constants.samples import (
        histoGramPerSample, proChannelDic, proChannelDic_forCombine
    )

    # Get aggregated process for a sample
    process = histoGramPerSample['ttbar_0l']  # 'tt'

    # Get process list for a channel
    processes = proChannelDic['1tau1l']  # ['fakeTau', 'tt', 'ttbb', ...]
"""

from typing import Dict, List

# =============================================================================
# Generator-Level Sum of Weights (for normalization validation)
# =============================================================================

#: Generator-level sum of weights per sample (from genWeights histogram)
genSumDic: Dict[str, float] = {
    'ttW': 27686900.0,
    'qcd_2000toInf': 5374710.0,
    'qcd_200to300': 57336600.0,
    'st_tW_top': 258137000.0,
    'WJetsToLNu_HT-200To400': 58225600.0,
    'WJetsToLNu_HT-400To600': 7444030.0,
    'WJetsToLNu_HT-1200To2500': 6481520.0,
    'qcd_1000to1500': 14394800.0,
    'WJetsToLNu_HT-2500ToInf': 2097650.0,
    'qcd_300to500': 61609700.0,
    'qcd_50to100': 38599400.0,
    'tttt': 106025.0,
    'qcd_1500to2000': 10411800.0,
    'ttbar_0l': 104910000000.0,
    'ttbar_2l': 10457600000.0,
    'ttH_nonbb': 9281200.0,
    'WJetsToLNu_HT-600To800': 7718760.0,
    'st_tW_antitop': 251902000.0,
    'st_tZq': 924059.0,
    'ttH_bb': 9451720.0,
    'ww': 15679100.0,
    'zz': 3526000.0,
    'ttG': 27849500.0,
    'qcd_700to1000': 48506800.0,
    'wz': 7940000.0,
    'qcd_500to700': 49184800.0,
    'ttbar_1l': 143354000000.0,
    'WJetsToLNu_HT-800To1200': 7306190.0,
    'ttZ': 32793800.0
}

# =============================================================================
# Process Categories
# =============================================================================

#: List of aggregated process names used in analysis
summedProcessList: List[str] = [
    'tttt', 'tt', 'qcd', 'ttX', 'VV', 'singleTop', 'WJets', 'jetHT', 'singleMu'
]

# =============================================================================
# Sample to Process Mapping
# =============================================================================

#: Maps individual MC samples to aggregated process categories
#: Used for histogram stacking and legend grouping
histoGramPerSample: Dict[str, str] = {
    # Signal
    'tttt': 'tttt',

    # ttbar (inclusive decay modes)
    'ttbar_0l': 'tt',
    'ttbar_1l': 'tt',
    'ttbar_2l': 'tt',

    # TTBB samples - separate process category
    'TTBB_4f_TTToHadronic': 'ttbb',
    'TTBB_4f_TTToSemiLeptonic': 'ttbb',
    'TTBB_4f_TTTo2L2Nu': 'ttbb',

    # QCD (Run 2)
    'qcd_50to100': 'qcd',
    'qcd_100to200': 'qcd',
    'qcd_200to300': 'qcd',
    'qcd_300to500': 'qcd',
    'qcd_500to700': 'qcd',
    'qcd_700to1000': 'qcd',
    'qcd_1000to1500': 'qcd',
    'qcd_1500to2000': 'qcd',
    'qcd_2000toInf': 'qcd',

    # ttX processes
    "TTZToLLNuNu": "ttX",
    "TTZToQQ": "ttX",
    "TTWJetsToQQ": "ttX",
    "TTWJetsToLNu": "ttX",
    "ttH_bb": "ttX",
    "ttH_nonbb": "ttX",

    # Minor backgrounds (VV, triboson, gamma, Higgs)
    "WZTo3LNu": "Minor",
    "zz": "Minor",
    'WWW': "Minor",
    'WWZ': 'Minor',
    'WZZ': 'Minor',
    'ZZZ': 'Minor',
    "ZGToLLG": "Minor",
    "ttG": "Minor",
    "ggH_bb": "Minor",
    "ggH_WW_2l": "Minor",
    "ggH_ZZ_2l": "Minor",
    "ggH_ZZ_4l": "Minor",
    "TTT": "Minor",
    "TTTW": "Minor",

    # Single top
    "st_tW_antitop": "singleTop",
    "st_tW_top": "singleTop",
    "st_schan_had": "singleTop",
    "st_schan_lep": "singleTop",
    "st_tchan": "singleTop",

    # W+jets
    "WJetsToLNu_HT-200To400": "WJets",
    "WJetsToLNu_HT-400To600": "WJets",
    "WJetsToLNu_HT-600To800": "WJets",
    "WJetsToLNu_HT-800To1200": "WJets",
    "WJetsToLNu_HT-1200To2500": "WJets",
    "WJetsToLNu_HT-2500ToInf": "WJets",

    # Drell-Yan
    "DYJetsToLL_M-10to50": "DY",
    "DYJetsToLL_M-50": "DY",

    # Fake backgrounds
    "fakeLepton": "fakeLepton",
    "fakeTau_data_ptMorphed": "fakeTau",
    "fakeTau_MC_ptMorphed": "fakeTau",

    # VLL signal (various masses)
    "VLL_EE_M500": "VLLm500",
    "VLL_EN_M500": "VLLm500",
    "VLL_NN_M500": "VLLm500",
    "VLL_EE_M550": "VLLm550",
    "VLL_EN_M550": "VLLm550",
    "VLL_NN_M550": "VLLm550",
    "VLL_EE_M600": "VLLm600",
    "VLL_EN_M600": "VLLm600",
    "VLL_NN_M600": "VLLm600",
    "VLL_EE_M650": "VLLm650",
    "VLL_EN_M650": "VLLm650",
    "VLL_NN_M650": "VLLm650",
    "VLL_EE_M700": "VLLm700",
    "VLL_EN_M700": "VLLm700",
    "VLL_NN_M700": "VLLm700",
    "VLL_EE_M750": "VLLm750",
    "VLL_EN_M750": "VLLm750",
    "VLL_NN_M750": "VLLm750",
    "VLL_EE_M800": "VLLm800",
    "VLL_EN_M800": "VLLm800",
    "VLL_NN_M800": "VLLm800",
    "VLL_EE_M850": "VLLm850",
    "VLL_EN_M850": "VLLm850",
    "VLL_NN_M850": "VLLm850",
    "VLL_EE_M900": "VLLm900",
    "VLL_EN_M900": "VLLm900",
    "VLL_NN_M900": "VLLm900",
    "VLL_EE_M950": "VLLm950",
    "VLL_EN_M950": "VLLm950",
    "VLL_NN_M950": "VLLm950",
    "VLL_EE_M1000": "VLLm1000",
    "VLL_EN_M1000": "VLLm1000",
    "VLL_NN_M1000": "VLLm1000",

    # Data - JetHT
    'jetHT_2016F': 'jetHT',
    'jetHT_2016G': 'jetHT',
    'jetHT_2016H': 'jetHT',
    'jetHT_2016B_v1_v2': 'jetHT',
    'jetHT_2016B_v2_v2': 'jetHT',
    'jetHT_2016C_v2': 'jetHT',
    'jetHT_2016D_v2': 'jetHT',
    'jetHT_2016E_v2': 'jetHT',
    'jetHT_2016F_hipm_v2': 'jetHT',
    'jetHT_2018a': 'jetHT',
    'jetHT_2018b': 'jetHT',
    'jetHT_2018c': 'jetHT',
    'jetHT_2018d': 'jetHT',
    'jetHT_2017b': 'jetHT',
    'jetHT_2017c': 'jetHT',
    'jetHT_2017d': 'jetHT',
    'jetHT_2017e': 'jetHT',
    'jetHT_2017f': 'jetHT',
    'BTagCSV_2017b': 'jetHT',
    'BTagCSV_2017c': 'jetHT',
    'BTagCSV_2017d': 'jetHT',
    'BTagCSV_2017e': 'jetHT',
    'BTagCSV_2017f': 'jetHT',

    # Data - SingleMu
    'singleMu_2016F': 'singleMu',
    'singleMu_2016G': 'singleMu',
    'singleMu_2016H': 'singleMu',
    'singleMu_2016B_v1_v2': 'singleMu',
    'singleMu_2016B_v2_v2': 'singleMu',
    'singleMu_2016C_v2': 'singleMu',
    'singleMu_2016D_v2': 'singleMu',
    'singleMu_2016E_v2': 'singleMu',
    'singleMu_2016F_hipm_v2': 'singleMu',
    'singleMu_2018a': 'singleMu',
    'singleMu_2018b': 'singleMu',
    'singleMu_2018c': 'singleMu',
    'singleMu_2018d': 'singleMu',
    'singleMu_2017b': 'singleMu',
    'singleMu_2017c': 'singleMu',
    'singleMu_2017d': 'singleMu',
    'singleMu_2017e': 'singleMu',
    'singleMu_2017f': 'singleMu',

    # Data - DoubleMu, MuonEG, eGamma (for 1tau2l)
    'doubleMu_2018a': 'doubleMu',
    'doubleMu_2018b': 'doubleMu',
    'doubleMu_2018c': 'doubleMu',
    'doubleMu_2018d': 'doubleMu',
    'MuonEG_2018a': 'muonEG',
    'MuonEG_2018b': 'muonEG',
    'MuonEG_2018c': 'muonEG',
    'MuonEG_2018d': 'muonEG',
    'eGamma_2018a': 'eGamma',
    'eGamma_2018b': 'eGamma',
    'eGamma_2018c': 'eGamma',
    'eGamma_2018d': 'eGamma',

    'doubleMu_2017b': 'doubleMu',
    'doubleMu_2017c': 'doubleMu',
    'doubleMu_2017d': 'doubleMu',
    'doubleMu_2017e': 'doubleMu',
    'doubleMu_2017f': 'doubleMu',
    'doubleEG_2017b': 'doubleEG',
    'doubleEG_2017c': 'doubleEG',
    'doubleEG_2017d': 'doubleEG',
    'doubleEG_2017e': 'doubleEG',
    'doubleEG_2017f': 'doubleEG',
    'MuonEG_2017b': 'muonEG',
    'MuonEG_2017c': 'muonEG',
    'MuonEG_2017d': 'muonEG',
    'MuonEG_2017e': 'muonEG',
    'MuonEG_2017f': 'muonEG',
    'singleE_2017b': 'singleE',
    'singleE_2017c': 'singleE',
    'singleE_2017d': 'singleE',
    'singleE_2017e': 'singleE',
    'singleE_2017f': 'singleE',

    'doubleMu_2016b_v1': 'doubleMu',
    'doubleMu_2016b_v2': 'doubleMu',
    'doubleMu_2016c': 'doubleMu',
    'doubleMu_2016d': 'doubleMu',
    'doubleMu_2016e': 'doubleMu',
    'doubleMu_2016f_hipm': 'doubleMu',
    'doubleMu_2016f': 'doubleMu',
    'doubleMu_2016g': 'doubleMu',
    'doubleMu_2016h': 'doubleMu',
    'doubleEG_2016b_v1': 'doubleEG',
    'doubleEG_2016b_v2': 'doubleEG',
    'doubleEG_2016c': 'doubleEG',
    'doubleEG_2016d': 'doubleEG',
    'doubleEG_2016e': 'doubleEG',
    'doubleEG_2016f_hipm': 'doubleEG',
    'doubleEG_2016f': 'doubleEG',
    'doubleEG_2016g': 'doubleEG',
    'doubleEG_2016h': 'doubleEG',
    'MuonEG_2016b_v2': 'muonEG',
    'MuonEG_2016b': 'muonEG',
    'MuonEG_2016c': 'muonEG',
    'MuonEG_2016d': 'muonEG',
    'MuonEG_2016e': 'muonEG',
    'MuonEG_2016f_hipm': 'muonEG',
    'MuonEG_2016f': 'muonEG',
    'MuonEG_2016g': 'muonEG',
    'MuonEG_2016h': 'muonEG',
    'singleE_2016B_v1': 'singleE',
    'singleE_2016B_v2': 'singleE',
    'singleE_2016C': 'singleE',
    'singleE_2016D': 'singleE',
    'singleE_2016E': 'singleE',
    'singleE_2016F_hipm': 'singleE',
    'singleE_2016F': 'singleE',
    'singleE_2016G': 'singleE',
    'singleE_2016H': 'singleE',

    # Combined lepton data (overlap removed for 1tau2l)
    'leptonSum_2018': 'leptonSum',
    'leptonSum_2017': 'leptonSum',
    'leptonSum_2016preVFP': 'leptonSum',
    'leptonSum_2016postVFP': 'leptonSum',

    # Extra tt samples for BDT training
    'TTTo2L2Nu0': 'ttExtra',
    'TTTo2L2Nu1': 'ttExtra',
    'TTTo2L2Nu2': 'ttExtra',
    'TTTo2L2Nu3': 'ttExtra',
    'TTTo2L2Nu4': 'ttExtra',
    'TTTo2L2Nu5': 'ttExtra',
    'TTTo2L2Nu6': 'ttExtra',
    'TTTo2L2Nu7': 'ttExtra',
    'TTTo2L2Nu8': 'ttExtra',
    'TTTo2L2Nu9': 'ttExtra',
    'TTTo2L2Nu10': 'ttExtra',
    'TTTo2L2Nu11': 'ttExtra',
    'TTTo2L2Nu12': 'ttExtra',
    'TTTo2L2Nu13': 'ttExtra',
    'TTTo2L2Nu14': 'ttExtra',
    'TTTo2L2Nu15': 'ttExtra',
    'TTTo2L2Nu16': 'ttExtra',
    'TTTo2L2Nu17': 'ttExtra',
    'TTTo2L2Nu18': 'ttExtra',
    'TTTo2L2Nu19': 'ttExtra',
    'TTTo2L2Nu20': 'ttExtra',
    'TTToHadronic0': 'ttExtra',
    'TTToHadronic1': 'ttExtra',
    'TTToHadronic2': 'ttExtra',
    'TTToHadronic3': 'ttExtra',
    'TTToHadronic4': 'ttExtra',
    'TTToHadronic5': 'ttExtra',
    'TTToHadronic6': 'ttExtra',
    'TTToHadronic7': 'ttExtra',
    'TTToHadronic8': 'ttExtra',
    'TTToHadronic9': 'ttExtra',
    'TTToHadronic10': 'ttExtra',
    'TTToHadronic11': 'ttExtra',
    'TTToHadronic12': 'ttExtra',
    'TTToHadronic13': 'ttExtra',
    'TTToHadronic14': 'ttExtra',
    'TTToSemiLeptonic0': 'ttExtra',
    'TTToSemiLeptonic1': 'ttExtra',
    'TTToSemiLeptonic2': 'ttExtra',
    'TTToSemiLeptonic3': 'ttExtra',
    'TTToSemiLeptonic4': 'ttExtra',
    'TTToSemiLeptonic5': 'ttExtra',
    'TTToSemiLeptonic6': 'ttExtra',
    'TTToSemiLeptonic7': 'ttExtra',
    'TTToSemiLeptonic8': 'ttExtra',
    'TTToSemiLeptonic9': 'ttExtra',
    'TTToSemiLeptonic10': 'ttExtra',
    'TTToSemiLeptonic11': 'ttExtra',
    'TTToSemiLeptonic12': 'ttExtra',
    'TTToSemiLeptonic13': 'ttExtra',
    'TTToSemiLeptonic14': 'ttExtra',
    'TTToSemiLeptonic15': 'ttExtra',
    'TTToSemiLeptonic16': 'ttExtra',
    'TTToSemiLeptonic17': 'ttExtra',
    'TTToSemiLeptonic18': 'ttExtra',
    'TTToSemiLeptonic19': 'ttExtra',
    'TTToSemiLeptonic20': 'ttExtra',
    'TTToSemiLeptonic21': 'ttExtra',
}

# =============================================================================
# ttX Subprocess Mapping
# =============================================================================

#: Maps ttX subprocesses to individual components (for detailed studies)
ttX_newMap: Dict[str, str] = {
    "TTZToLLNuNu": "ttZ",
    "TTZToQQ": "ttZ",
    "TTWJetsToQQ": "ttW",
    "TTWJetsToLNu": "ttW",
    "ttH_bb": "ttH",
    "ttH_nonbb": "ttH",
}

# =============================================================================
# Subprocess Lists per Summed Process
# =============================================================================

#: Maps aggregated process to list of contributing subprocesses
subSumProDic: Dict[str, List[str]] = {
    'tttt': ['tttt'],
    'tt': ['ttbar_0l', 'ttbar_1l', 'ttbar_2l'],
    'qcd': [
        'qcd_50to100', 'qcd_200to300', 'qcd_300to500', 'qcd_500to700',
        'qcd_700to1000', 'qcd_1000to1500', 'qcd_1500to2000', 'qcd_2000toInf'
    ],
    'ttX': ['ttG', 'ttZ', 'ttW', 'ttH_bb', 'ttH_nonbb'],
    'VV': ['wz', 'ww', 'zz'],
    'singleTop': ['st_tZq', 'st_tW_antitop', 'st_tW_top'],
    'WJets': [
        'WJetsToLNu_HT-200To400', 'WJetsToLNu_HT-400To600',
        'WJetsToLNu_HT-600To800', 'WJetsToLNu_HT-800To1200',
        'WJetsToLNu_HT-1200To2500', 'WJetsToLNu_HT-2500ToInf'
    ],
    'fakeTau': ['fakeTau_tauF', 'fakeTau_tauT', 'fakeTau_tauFGen', 'fakeTau_tauTGen'],
    'VLLm600': ['VLL_EE_M600', 'VLL_EN_M600', 'VLL_NN_M600'],
    'VLLm650': ['VLL_EE_M650', 'VLL_EN_M650', 'VLL_NN_M650'],
    'VLLm700': ['VLL_EE_M700', 'VLL_EN_M700', 'VLL_NN_M700'],
    'VLLm750': ['VLL_EE_M750', 'VLL_EN_M750', 'VLL_NN_M750'],
    # Data
    'jetHT': [
        'jetHT_2016F', 'jetHT_2016G', 'jetHT_2016H', 'jetHT_2016B_v1_v2',
        'jetHT_2016B_v2_v2', 'jetHT_2016C_v2', 'jetHT_2016D_v2', 'jetHT_2016E_v2',
        'jetHT_2016F_hipm_v2', 'jetHT_2018a', 'jetHT_2018b', 'jetHT_2018c',
        'jetHT_2018d', 'jetHT_2017b', 'jetHT_2017c', 'jetHT_2017d', 'jetHT_2017e',
        'jetHT_2017f', 'BTagCSV_2017b', 'BTagCSV_2017c', 'BTagCSV_2017d',
        'BTagCSV_2017e', 'BTagCSV_2017f'
    ],
    'singleMu': [
        'singleMu_2016F', 'singleMu_2016G', 'singleMu_2016H', 'singleMu_2016B_v1_v2',
        'singleMu_2016B_v2_v2', 'singleMu_2016C_v2', 'singleMu_2016D_v2',
        'singleMu_2016E_v2', 'singleMu_2016F_hipm_v2', 'singleMu_2018a',
        'singleMu_2018b', 'singleMu_2018c', 'singleMu_2018d', 'singleMu_2017b',
        'singleMu_2017c', 'singleMu_2017d', 'singleMu_2017e', 'singleMu_2017f'
    ],
    'doubleMu': ['doubleMu_2018a', 'doubleMu_2018b', 'doubleMu_2018c', 'doubleMu_2018d'],
    'muonEG': ['MuonEG_2018a', 'MuonEG_2018b', 'MuonEG_2018c', 'MuonEG_2018d'],
    'eGamma': ['eGamma_2018a', 'eGamma_2018b', 'eGamma_2018c', 'eGamma_2018d'],
}

# =============================================================================
# Run 3 Sample Mapping
# =============================================================================

#: Maps Run 3 sample names to process categories
Run3Samples: Dict[str, str] = {
    'TTTT': 'tttt',

    'TTto2L2Nu': 'tt',
    'TTto2L2Nu1': 'tt',
    'TTto4Q': 'tt',
    'TTto4Q1': 'tt',
    'TTtoLNu2Q': 'tt',
    'TTtoLNu2Q1': 'tt',

    'QCD_PT-50to80': 'qcd',
    'QCD_PT-80to120': 'qcd',
    'QCD_PT-120to170': 'qcd',
    'QCD_PT-170to300': 'qcd',
    'QCD_PT-300to470': 'qcd',
    'QCD_PT-470to600': 'qcd',
    'QCD_PT-600to800': 'qcd',
    'QCD_PT-800to1000': 'qcd',
    'QCD_PT-1000to1400': 'qcd',
    'QCD_PT-1400to1800': 'qcd',
    'QCD_PT-1800to2400': 'qcd',
    'QCD_PT-2400to3200': 'qcd',
    'QCD_PT-3200': 'qcd',

    'JetHT2022C': 'jetHT',
    'JetMET2022C': 'jetHT',
    'JetMET2022D': 'jetHT',
    'JetMET2022E': 'jetHT',
    'JetMET2022F': 'jetHT',
    'JetMET2022G': 'jetHT',

    'SingleMuon2022C': 'singleMu',
    'Muon2022C': 'singleMu',
    'Muon2022D': 'singleMu',
    'Muon2022E': 'singleMu',
    'Muon2022F': 'singleMu',
    'Muon2022G': 'singleMu',
}

# =============================================================================
# Data Era Mapping
# =============================================================================

#: Maps era to list of data run periods (for filtering data samples)
dataDict: Dict[str, List[str]] = {
    '2022preEE': ['2022C', '2022D'],
    '2022postEE': ['2022E', '2022F', '2022G'],
    '2016': ['2016B', '2016C', '2016D', '2016E', '2016F', '2016'],
    '2017': ['2017b', '2017c', '2017d', '2017e', '2017f', '2017'],
    '2018': ['2018a', '2018b', '2018c', '2018d', '2018'],
    '2016postVFP': ['2016F', '2016G', '2016H', '2016f', '2016g', '2016h', '2016postVFP'],
    '2016preVFP': [
        '2016B_v1_v2', '2016B_v2_v2', '2016C_v2', '2016D_v2', '2016E_v2',
        '2016F_hipm_v2', '2016b_v1', '2016b_v2', '2016b', '2016c', '2016d',
        '2016e', '2016f_hipm', '2016preVFP'
    ],
}

# =============================================================================
# Channel-Specific Process Lists
# =============================================================================

#: Process list per channel for validation plots and analysis
#: Order matters for stack plot legend (ttbb before tt for legend order: ttbb, tt, ttX)
proChannelDic: Dict[str, List[str]] = {
    '1tau1l': ['fakeTau', 'ttbb', 'tt', 'ttX', 'fakeLepton', 'tttt', 'jetHT'],
    '1tau0l': ['fakeTau', 'ttbb', 'tt', 'ttX', 'singleTop', 'WJets', 'tttt', 'jetHT'],
    '1tau2l': ['fakeTau', 'tt', 'ttX', 'fakeLepton', 'singleTop', 'Minor', 'tttt', 'leptonSum'],
}

#: Process list per channel for CMS Combine (ttX split into ttZ/ttW/ttH)
#: Order: ttbb before tt so that after grouping ttZ/ttW/ttH->ttX, legend shows ttbb, tt, ttX
proChannelDic_forCombine: Dict[str, List[str]] = {
    '1tau1l': ['fakeTau', 'ttbb', 'tt', 'ttZ', 'ttW', 'ttH', 'fakeLepton', 'tttt', 'jetHT'],
    '1tau2l': ['fakeTau', 'tt', 'ttZ', 'ttW', 'ttH', 'fakeLepton', 'Minor', 'tttt', 'leptonSum'],
    '1tau0l': ['fakeTau', 'ttbb', 'tt', 'ttZ', 'ttW', 'ttH', 'singleTop', 'WJets', 'tttt', 'jetHT'],
}


# =============================================================================
# Utility Functions
# =============================================================================

def get_process(sample: str) -> str:
    """
    Get aggregated process for a sample name.

    Args:
        sample: Sample name (e.g., 'ttbar_0l', 'TTBB_4f_TTToHadronic')

    Returns:
        Aggregated process name (e.g., 'tt', 'ttbb')

    Raises:
        KeyError: If sample not found in mapping.
    """
    if sample not in histoGramPerSample:
        raise KeyError(f"Unknown sample '{sample}'. Check histoGramPerSample.")
    return histoGramPerSample[sample]


def get_process_list(channel: str, for_combine: bool = False) -> List[str]:
    """
    Get process list for a channel.

    Args:
        channel: Channel name ('1tau0l', '1tau1l', '1tau2l')
        for_combine: If True, return list with split ttX (ttZ/ttW/ttH)

    Returns:
        List of process names.

    Raises:
        KeyError: If channel not found.
    """
    proc_dict = proChannelDic_forCombine if for_combine else proChannelDic
    if channel not in proc_dict:
        raise KeyError(f"Unknown channel '{channel}'. Valid: {list(proc_dict.keys())}")
    return proc_dict[channel]


def is_data_sample(sample: str) -> bool:
    """
    Check if a sample is a data sample.

    Args:
        sample: Sample name

    Returns:
        True if sample is data.
    """
    if sample not in histoGramPerSample:
        return False
    process = histoGramPerSample[sample]
    return process in ['jetHT', 'singleMu', 'doubleMu', 'muonEG', 'eGamma',
                       'doubleEG', 'singleE', 'leptonSum']


def is_mc_sample(sample: str) -> bool:
    """
    Check if a sample is a MC sample.

    Args:
        sample: Sample name

    Returns:
        True if sample is MC (not data).
    """
    return not is_data_sample(sample)
