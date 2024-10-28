import types

lumiMap = {
    "2016preVFP": 19500.,
    "2016postVFP": 16810.,
    "2016": 36310.,
    "2017": 41480.0,
    "2018": 59830.0,
    "Run2" : 137620.0,
    "2022": 37300,  
    "2022preEE": 7875,  
    "2022postEE": 26377,  
}

crossSectionMap = {
    "tttt": 0.01337,
    "ttbar_0l": 377.96,
    "ttbar_1l": 365.34,
    "ttbar_2l": 88.29,
    
    "ttG": 15.89, # 4.62,
    "ttZ": 0.783,
    "ttW": 0.611,
    "ttH_bb": 0.2897,
    "ttH_nonbb": 0.209,
    "ttWW": 0.00698, 
   
    #VV cross section to be updated! 
    "wz": 47.,#2.343, #47
    "ww": 118.,# 6.430, #118 
    "zz": 16.5,# 1.016, #16.5
    
    "WWW": 0.2086,
    "WWZ": 0.1651,
    "WZZ": 0.05565,
    "ZZZ": 0.01476,
    
    "st_tZq": 0.07358,
    "st_tW_antitop": 35.85,
    "st_tW_top": 35.85,
    
    #GX: ttGamma, ZGamma 
    'TGJets': 1.02,
    'ZGToLLG': 55.48,
    'WGToLNuG': 192 ,
   
    #H->ZZ, WW
    'ggH_bb': 28.3, # ! not exist in 2017
    'ggH_tautau': 3.05,
    'ggH_WW_2l': 1.10, #!'ggH_ww_2l', in 2016
    'ggH_ZZ_2l': 28.87,
    'ggH_ZZ_4l': 0.01212,
    'ggH_gg': 0.01,
    
    'vbfH_bb': 2.20,
    # 'vbfH_nonbb': ,
    'vbfH_tautau': 0.237,
    'vbfH_WW_2l': 0.0859,
    'VH_nonbb': 0.942, 
    
    "DYJetsToLL_M-10to50": 15810.0,
    "DYJetsToLL_M-50": 6077.22,
    
    "qcd_50to100": 2.466e+08,
    "qcd_100to200": 2.801e+07,
    "qcd_200to300": 1.721e+6,
    "qcd_300to500": 3.479e+05,
    "qcd_500to700": 3.206e+04,
    "qcd_700to1000": 6.827e+03,
    "qcd_1000to1500": 1.207e+03,
    "qcd_1500to2000": 1.20e+02,
    "qcd_2000toInf": 2.525e+01,
    "WJetsToLNu_HT-200To400": 532.4,
    "WJetsToLNu_HT-400To600": 61.6,
    "WJetsToLNu_HT-600To800": 12.4,
    "WJetsToLNu_HT-800To1200": 5.77,
    "WJetsToLNu_HT-1200To2500": 1.023,
    "WJetsToLNu_HT-2500ToInf": 0.0248,
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
    "TTto4Q": 419.69,
    "TTto2L2Nu": 98.09,
    "TTtoLNu2Q": 405.80,
    "TTTT": 0.0158,
   
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
    "VLL_NN_M1000": 2.909e-5 * 3.96 
    
    
}


genSumDic={
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

# summedProcessList = [ 'tttt', 'tt', 'qcd', 'ttX', 'VV', 'singleTop', 'WJets', 'data' ]
summedProcessList = [ 'tttt', 'tt', 'qcd', 'ttX', 'VV', 'singleTop', 'WJets', 'jetHT', 'singleMu' ]

histoGramPerSample = { 
    'tttt':'tttt',
    
    'ttbar_0l':'tt',
    'ttbar_1l': 'tt',
    'ttbar_2l': 'tt',
    
    'qcd_50to100':'qcd',
    # 'qcd_100to200':'qcd',//!!!to be updated
    'qcd_200to300':'qcd',
    'qcd_300to500':'qcd',
    'qcd_500to700':'qcd',
    'qcd_700to1000':'qcd',
    'qcd_1000to1500':'qcd',
    'qcd_1500to2000':'qcd',
    'qcd_2000toInf':'qcd',

    "ttG":"ttX",
    "ttZ":"ttX",  
    "ttW":"ttX",
    "ttH_bb": "ttX", 
    "ttH_nonbb": "ttX", 
    # "ttWW": "ttX", #!temprarily close
    
    # "wz":"Minor", #!should probably use wz instead of WZTo3LNu because the 2L part can also pass 1tau2l selection; but non of it passes selection
    "WZTo3LNu":"Minor", #!use this instead of wz
    "ww":"Minor",
    "zz":"Minor",
    'WWW': "Minor",
    'WWZ': 'Minor',
    'WZZ': 'Minor',
    'ZZZ': 'Minor',
    
    #!do we miss some single top samples : s-channel, t channel, tW channel
    "st_tZq":"singleTop",
    "st_tW_antitop":"singleTop",
    "st_tW_top":"singleTop",
    "st_schan_had": "singleTop",
    "st_schan_lep": "singleTop",
    "st_tchan": "singleTop",
    
    "TGJets": "Minor",#"XGamma", #!not exist in 2016preVFP
    "ZGToLLG": "Minor",#"XGamma",
    "WGToLNuG": "Minor",#"XGamma",
   
    
    # "ggH_bb": "Minor",#"Higgs",#!not excsi in 2017 nano files
    "ggH_tautau": "Minor",#"Higgs",
    # "ggH_WW_2l": "Minor",#"Higgs", #! ggH_ww_2l in 2016   
    # "ggH_ZZ_2l": "Minor",#"Higgs", #!ggH_zz_2l in 2016
    # "ggH_ZZ_4l": "Minor",#"Higgs", #!ggH_zz_4l in 2016
    # "ggH_gg": "Minor",#"Higgs", #!ggH_gg in 2016
    # "vbfH_bb": "Minor",#"Higgs", #!not exist in 2017
    # "vbfH_tautau": "Minor",#"Higgs", #! not exist in 2016preVFP
    # "vbfH_WW_2l": "Minor",#"Higgs", #!vbH_ww_2l in 2016
    # "VH_nonbb": "Minor",#"Higgs", #!not in MV
    
    "WJetsToLNu_HT-200To400": "WJets",
    "WJetsToLNu_HT-400To600": "WJets",
    "WJetsToLNu_HT-600To800": "WJets",
    "WJetsToLNu_HT-800To1200": "WJets",
    "WJetsToLNu_HT-1200To2500": "WJets",
    "WJetsToLNu_HT-2500ToInf": "WJets",
    
    "DYJetsToLL_M-10to50": "DY",
    "DYJetsToLL_M-50": "DY",
    
    "fakeLepton": "fakeLepton",
    
    # "fakeTau_tauF": "fakeTau",
    # "fakeTau_tauT": "fakeTau",
    # "fakeTau_tauFGen": "fakeTau",
    # "fakeTau_tauTGen": "fakeTau",
    "fakeTau_data": "fakeTau", #!update
    "fakeTau_MC": "fakeTau",
    
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
    

    #data
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
    
    #additonal python code to remove the overlap
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
    
    #overlap removed data for 1tau2l
    'leptonSum_2018': 'leptonSum',
    'leptonSum_2017': 'leptonSum',
    'leptonSum_2016preVFP': 'leptonSum',
    'leptonSum_2016postVFP': 'leptonSum',
    
    
    
    #extra tt samples for BDT training 
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

#! maybe it's better to keep it in this format?
subSumProDic ={
   'tttt': ['tttt'],
    'tt': ['ttbar_0l', 'ttbar_1l', 'ttbar_2l'],
    'qcd': ['qcd_50to100', 'qcd_200to300', 'qcd_300to500', 'qcd_500to700', 'qcd_700to1000', 'qcd_1000to1500', 'qcd_1500to2000', 'qcd_2000toInf'],
    'ttX': ['ttG', 'ttZ', 'ttW', 'ttH_bb', 'ttH_nonbb'],
    'VV': ['wz', 'ww', 'zz'],
    'singleTop': ['st_tZq', 'st_tW_antitop', 'st_tW_top'],
    'WJets': ['WJetsToLNu_HT-200To400', 'WJetsToLNu_HT-400To600', 'WJetsToLNu_HT-600To800', 'WJetsToLNu_HT-800To1200', 'WJetsToLNu_HT-1200To2500', 'WJetsToLNu_HT-2500ToInf'],
    'fakeTau': ['fakeTau_tauF', 'fakeTau_tauT', 'fakeTau_tauFGen', 'fakeTau_tauTGen'],
    'VLLm600': ['VLL_EE_M600', 'VLL_EN_M600', 'VLL_NN_M600'],
    'VLLm650': ['VLL_EE_M650', 'VLL_EN_M650', 'VLL_NN_M650'],
    'VLLm700': ['VLL_EE_M700', 'VLL_EN_M700', 'VLL_NN_M700'],
    'VLLm750': ['VLL_EE_M750', 'VLL_EN_M750', 'VLL_NN_M750'],
    #data
    'jetHT': ['jetHT_2016F', 'jetHT_2016G', 'jetHT_2016H', 'jetHT_2016B_v1_v2', 'jetHT_2016B_v2_v2', 'jetHT_2016C_v2', 'jetHT_2016D_v2', 'jetHT_2016E_v2', 'jetHT_2016F_hipm_v2', 'jetHT_2018a', 'jetHT_2018b', 'jetHT_2018c', 'jetHT_2018d', 'jetHT_2017b', 'jetHT_2017c', 'jetHT_2017d', 'jetHT_2017e', 'jetHT_2017f', 'BTagCSV_2017b', 'BTagCSV_2017c', 'BTagCSV_2017d', 'BTagCSV_2017e', 'BTagCSV_2017f'],
    'singleMu': ['singleMu_2016F', 'singleMu_2016G', 'singleMu_2016H', 'singleMu_2016B_v1_v2', 'singleMu_2016B_v2_v2', 'singleMu_2016C_v2', 'singleMu_2016D_v2', 'singleMu_2016E_v2', 'singleMu_2016F_hipm_v2', 'singleMu_2018a', 'singleMu_2018b', 'singleMu_2018c', 'singleMu_2018d', 'singleMu_2017b', 'singleMu_2017c', 'singleMu_2017d', 'singleMu_2017e', 'singleMu_2017f'], 
    'doubleMu': ['doubleMu_2018a', 'doubleMu_2018b', 'doubleMu_2018c', 'doubleMu_2018d'],
    'muonEG': ['MuonEG_2018a', 'MuonEG_2018b', 'MuonEG_2018c', 'MuonEG_2018d'],
    'eGamma': ['eGamma_2018a', 'eGamma_2018b', 'eGamma_2018c', 'eGamma_2018d'],
}




Run3Samples = {
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
    #2022postEE
    'JetMET2022E': 'jetHT',
    'JetMET2022F': 'jetHT',
    'JetMET2022G': 'jetHT',
    
    #Muon
    'SingleMuon2022C': 'singleMu',
    'Muon2022C': 'singleMu',
    'Muon2022D': 'singleMu',
    'Muon2022E': 'singleMu',
    'Muon2022F': 'singleMu',
    'Muon2022G': 'singleMu',
    
}

dataDict = {
    '2022preEE':['2022C', '2022D'],
    '2022postEE': ['2022E', '2022F', '2022G'],
    '2016': ['2016B', '2016C', '2016D', '2016E', '2016F'],
    '2017': ['2017b', '2017c', '2017d', '2017e', '2017f'],
    '2018': ['2018a', '2018b', '2018c', '2018d', '2018'], #add 2018 for leptonSum_2018
    '2016postVFP': ['2016F', '2016G', '2016H', '2016f', '2016g', '2016h'],
    '2016preVFP': ['2016B_v1_v2', '2016B_v2_v2',  '2016C_v2', '2016D_v2', '2016E_v2', '2016F_hipm_v2', '2016b_v1', '2016b_v2', '2016b','2016c', '2016d', '2016e', '2016f_hipm'],
}

proChannelDic = {
    # '1tau1l':  ['tt', 'ttX', 'singleTop', 'WJets', 'tttt', 'jetHT'], #! 1tau1l
    '1tau1l':  ['tt', 'ttX',  'fakeLepton', 'singleTop', 'WJets',   'tttt', 'jetHT'], #! 1tau1l, no Minor in any region in 1tau1l
    '1tau0l':  [ 'fakeTau', 'tt',  'ttX', 'singleTop', 'WJets', 'tttt', 'jetHT'], #!1tau0l
    '1tau2l':  ['tt', 'ttX', 'fakeLepton', 'singleTop',  'Minor',  'tttt', 'leptonSum'], 
    # '1tau2l':  ['tt', 'ttX',  'singleTop',  'Minor',  'tttt', 'leptonSum'], #!testing
}