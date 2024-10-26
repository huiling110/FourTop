import glob
import os
import ROOT
import pandas as pd
import usefulFunc as uf
import ttttGlobleQuantity as gq

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
    "ttww": 0.00698, 
   
    #VV cross section to be updated! 
    "WZTo3LNu": 4.9173,
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
    'ggH_WW_2l': 1.10,
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

genSumMap = {
    "2018": {
        "VLL_EE_M900": 28.573285710000004,
        "VLL_NN_M750": 18.732711000000002,
        "VLL_NN_M950": 4.80302336,
        "VLL_NN_M900": 6.61964497,
        "VLL_EN_M800": 102.43406055000003,
        "VLL_EE_M500": 591.1833100000001,
        "VLL_NN_M550": 91.49154300000001,
        "VLL_EE_M650": 166.88674399999996,
        "VLL_EN_M750": 145.86020320000003,
        "VLL_EN_M700": 209.162717,
        "VLL_NN_M600": 59.591204000000005,
        "VLL_NN_M850": 9.260824567,
        "VLL_NN_M500": 143.230307,
        "VLL_EN_M1000": 28.1200414,
        "VLL_EN_M850": 72.9743729,
        "VLL_EN_M600": 451.93825000000015,
        "VLL_EE_M950": 20.55407540000001,
        "VLL_EE_M800": 55.58882853,
        "VLL_NN_M800": 13.16760272,
        "VLL_EE_M750": 79.043692,
        "VLL_EN_M650": 305.767699,
        "VLL_EN_M500": 1063.7767100000003,
        "VLL_EN_M900": 53.19825936,
        "VLL_EE_M550": 378.49510999999995,
        "VLL_NN_M700": 27.080457,
        "VLL_EN_M550": 589.06433,
        "VLL_EE_M850": 39.047127379999985,
        "VLL_EN_M950": 38.63094899999999,
        "VLL_EE_M1000": 14.825747,
        "VLL_NN_M650": 40.048385,
        "VLL_EE_M600": 248.85666000000006,
        "VLL_EE_M700": 113.842985,
        "VLL_NN_M1000": 3.4763252000000002,
        "TTToSemiLeptonic": 1.35336e+12,  # only for BDT training in 1tau1l and 1tau2l
        "TTToHadronic": 7.16154e+11,
        "TTTo2L2Nu": 9.77873e+10,
        "TTTo2L2Nu12": 3676686735.3588,
        "TTTo2L2Nu20": 4686306971.145,
        "dy": 44304135.0,
        "qcd_200to300": 57336623.0,
        "TTTo2L2Nu19": 4316055324.3996,
        "ZJetsToNuNu_HT-2500ToInf": 350168.8629485784,
        "TTTo2L2Nu7": 5107198152.420001,
        "WJetsToLNu_HT-2500ToInf": 2097648.0,
        "TTToSemiLeptonic8": 58902792307.920006,
        "TTTo2L2Nu13": 4123992377.0602016,
        "TTZprime_M1750W20": 999000.0,
        "dy_fxfx_2j": 0.0,
        "dy_fxfx_0j": 0.0,
        "DYJetsToLL_M-4to50_HT-100to200": 6784415.669920306,
        "ZHToTauTau": 3757651.586189425,
        "zz": 3526000.0,
        "TTTo2L2Nu2": 10457566706.558405,
        "dy_fxfx": 1865334146117.397,
        "TTZprime_M1250W50": 1000000.0,
        "ZJetsToNuNu_HT-400To600": 9483323.05142726,
        "TTZprime_M1250W4": 1000000.0,
        "TTToSemiLeptonic0": 59525436999.57598,
        "ZJetsToNuNu_HT-1200To2500": 340171.00930426666,
        "st_tW_top": 258137398.5808001,
        "ttbar_2l": 10457566706.558403,  # a different, probably due to accuracy with float calculation
        "dy_100to200": 25271871.0,
        "ZGToLLG": 2945217421.2728004,
        "dy_400to600": 4615088.0,
        "TTZprime_M4000W20": 1000000.0,
        "WGToLNuG": 21973848102.29522,
        "TTZprime_M2000W50": 998000.0,
        "ggH_bb": 306093781.5276001,
        "ttG": 27849497.759999998,
        "vbfH_WW_2l": 36941581.16351999,
        "dy_600to800": 7035971.0,
        "TTZprime_M1250W20": 998000.0,
        "TTToSemiLeptonic20": 59994502183.19997,
        "DYJetsToLL_M-50": 1237360468.848,
        "TTZprime_M1500W10": 998000.0,
        "st_schan_had": 115657659.06405006,
        "WJetsToQQ_HT-600to800": 15246402.339965336,
        "TTToSemiLeptonic3": 58317663263.20004,
        "ZZZ": 3690.7843549760005,
        "DYJetsToLL_M-50_HT-600to800": 7035971.0,
        "st_tchan": 18955983507.894,
        "qcd_50to100": 38599389.0,
        "qcd_2000toInf": 5374711.0,
        "WJetsToLNu_HT-600To800": 7718765.0,
        "ggH_WW_2l": 136936228.18140003,
        "dy_70to100": 17004433.0,
        "ZJetsToQQ_HT-600to800": 14600689.076338131,
        "TTToHadronic6": 97194927854.9522,
        "TTToSemiLeptonic16": 59104136472.96404,
        "TTToHadronic3": 104910439190.40396,
        "ggH_ZZ_4l": 27138279.532200005,
        "TTZprime_M2000W10": 998000.0,
        "TTToSemiLeptonic18": 59998667622.47604,
        "TTTo2L2Nu11": 4323628205.963002,
        "TTZprime_M1500W50": 999000.0,
        "TTTW": 494000.0,
        "DYJetsToLL_M-4to50_HT-200to400": 1933953.2940268652,
        "TTTo2L2Nu6": 4435418494.282599,
        "TTZprime_M1000W50": 999000.0,
        "ttZH": 500000.0,
        "dy_2500toInf": 106267.0,
        "TTTo2L2Nu0": 4319091786.994,
        "TTTo2L2Nu15": 10797600355.304184,
        "DYJetsToLL_M-50_HT-1200to2500": 5966661.0,
        "TTZprime_M2500W10": 999000.0,
        "DYJetsToLL_M-50_HT-800to1200": 6554679.0,
        "TTToHadronic10": 43375307823.66003,
        "TTToHadronic5": 43787699958.8,
        "DYJetsToLL_M-50_HT-70to100": 17004433.0,
        "TTZprime_M2500W50": 1000000.0,
        "wz": 7940000.0,
        "dy_ext": 88819930.0,
        "WJetsToLNu": 1188874708.6423705,
        "ttbar_0l": 104910439190.40405,
        "qcd_700to1000": 48506751.0,
        "TTToHadronic11": 43849410601.71601,
        "WJetsToQQ_HT-400to600": 10046074.61723694,
        "WJetsToLNu_HT-70To100": 66220256.0,
        "st_tW_antitop": 251902163.21000004,
        "TTToHadronic2": 43328394801.03,
        "TTToSemiLeptonic13": 58518292489.722,
        "TTToSemiLeptonic1": 59977563613.13203,
        "WJetsToLNu_HT-1200To2500": 6481518.0,
        "DYJetsToLL_M-10to50": 94452816.0,
        "TTToSemiLeptonic21": 67828954921.01004,
        "TTToSemiLeptonic4": 59635849027.61204,
        "TTToSemiLeptonic7": 50874238399.147995,
        "DYJetsToLL_M-50_HT-2500toInf": 1978203.0,
        "TTZprime_M750W20": 1000000.0,
        "TTToSemiLeptonic12": 59586418661.66006,
        "TTToHadronic4": 49168689979.65599,
        "TTZprime_M3000W4": 1000000.0,
        "TTZprime_M1750W10": 999000.0,
        "tt": 3311826398.912999,
        "TTTo2L2Nu3": 4218732074.6372004,
        "TTToSemiLeptonic14": 59534257770.35002,
        "DYJetsToLL_M-4to50_HT-600toInf": 1964769.6021715738,
        "TTZprime_M750W50": 1000000.0,
        "ggH_ZZ_2l": 28813633.235200007,
        "TTToSemiLeptonic5": 59374335623.416016,
        "TTZprime_M2000W20": 1000000.0,
        "TTToHadronic14": 41845099323.056,
        "ggH_gg": 465089.7155499391,
        "TTZprime_M2500W4": 1000000.0,
        "TTZprime_M1750W50": 1000000.0,
        "TTZprime_M750W10": 1000000.0,
        "TTTo2L2Nu16": 4299241370.782402,
        "WWZ": 42310.517360879996,
        "TTToHadronic12": 43861623026.944016,
        "TTZprime_M1000W20": 996000.0,
        "TTZprime_M750W4": 1000000.0,
        "vbfH_bb": 29417189.70328001,
        "vbfH_tautau": 11530157.705640003,
        "TTZprime_M3000W10": 999000.0,
        "DYJetsToLL_M-50_HT-400to600": 8682257.0,
        "TTZprime_M1750W4": 999000.0,
        "WJetsToLNu_HT-100To200": 51408967.0,
        "ttWH": 497000.0,
        "qcd_500to700": 49184771.0,
        "TTZprime_M2500W20": 983000.0,
        "TTToSemiLeptonic19": 50794376435.20801,
        "TTTJ": 500000.0,
        "TTToSemiLeptonic15": 58140741853.34999,
        "TTToSemiLeptonic10": 91624122566.98811,
        "TTZprime_M2000W4": 1000000.0,
        "DYJetsToLL_M-50_HT-200to400": 18455718.0,
        "TTZprime_M4000W4": 1000000.0,
        "TTToHadronic7": 39928686942.576004,
        "TTTo2L2Nu4": 4221545062.6574025,
        "ttbar_1l": 143354137521.54016,
        "TTToHadronic0": 43357269007.32803,
        "TTToSemiLeptonic9": 58707486787.22403,
        "vH_nonbb": 7023767.516864,
        "TTZprime_M500W10": 1000000.0,
        "TTToSemiLeptonic2": 143354137521.54007,
        "ZH_HToBB_ZToLL": 176281.34766683044,
        "TTTo2L2Nu18": 4009940860.8139997,
        "TTZprime_M1000W4": 1000000.0,
        "ww": 15679122.7146132,
        "qcd_300to500": 61609663.0,
        "TTZprime_M500W4": 1000000.0,
        "TTTo2L2Nu10": 4114968337.0812016,
        "TTToHadronic9": 42938302139.52201,
        "TTZprime_M1500W4": 999000.0,
        "WJetsToLNu_HT-800To1200": 7306187.0,
        "TTTo2L2Nu1": 4324824484.1388,
        "ttH_nonbb": 9281203.666461302,
        "TTZprime_M1500W20": 979000.0,
        "ttH_bb": 9451717.2550458,
        "qcd_100to200": 84434559.0,
        "TTTo2L2Nu17": 4298318538.562201,
        "TTToSemiLeptonic6": 57138751583.45202,
        "TTZprime_M1250W10": 1000000.0,
        "TTZprime_M3000W20": 1000000.0,
        "ttW": 27686862.0,
        "WWW": 51638.257653960005,
        "DYJetsToLL_M-50_HT-100to200": 26202328.0,
        "TTZprime_M500W50": 1000000.0,
        "ZJetsToNuNu_HT-800To1200": 2055725.5230469361,
        "ZJetsToQQ_HT-800toInf": 10513086.250308977,
        "ttZZ": 498000.0,
        "TTZprime_M4000W10": 998000.0,
        "qcd_1500to2000": 10411831.0,
        "TGJets": 6935139.129627102,
        "dy_200to400": 18455718.0,
        "TTToHadronic8": 34734821996.607994,
        "WJetsToQQ_HT-800toInf": 14476833.800819013,
        "ttWZ": 498000.0,
        "ttZ": 32793815.0,
        "ttWW": 944000.0,
        "TTToSemiLeptonic11": 63363746785.32,
        "dy_fxfx_1j": 0.0,
        "ZJetsToQQ_HT-400to600": 16669536.822226059,
        "TTToHadronic1": 39388467256.86398,
        "TTTo2L2Nu8": 3979048160.395001,
        "ggH_tautau": 278393469.9064,
        "TTZprime_M4000W50": 1000000.0,
        "DYJetsToLL_M-4to50_HT-400to600": 2001264.5194430775,
        "TTZprime_M500W20": 1000000.0,
        "WJetsToLNu_HT-400To600": 7444030.0,
        "TTToSemiLeptonic17": 59040696427.85603,
        "WZZ": 17121.264030234,
        "TTTo2L2Nu5": 4213360833.440001,
        "dy_pu": 15296958.0,
        "tttt": 106024.995330672,
        "dy_40to70": 0.0,
        "st_schan_lep": 68767082.31869161,
        "TTToHadronic13": 43873260112.40801,
        "ttHH": 500000.0,
        "WJetsToLNu_HT-200To400": 58225632.0,
        "TTTo2L2Nu14": 3897563367.062399,
        "TTZprime_M1000W10": 1000000.0,
        "dy_1200to2500": 5831760.0,
        "st_tZq": 924058.9126336002,
        "st_antitchan": 6114949908.582959,
        "TTZprime_M3000W50": 999000.0,
        "dy_800to1200": 6090972.0,
        "ZJetsToNuNu_HT-600To800": 5726462.973848988,
        "qcd_1000to1500": 14394786.0,
        "TTTo2L2Nu9": 4291003926.409401,
        "WZTo3LNu": 83145979.098
    }
}


def main():
    # OSdir = '/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/UL2018/v84fakeLeptonUpdateV2/'
    OSdir = '/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/UL2018/v81addSysSum_1tau1l_full_TESTING/'
    # Example value for era
    era = "2018"

    subDic = {}
    swjd = [item for item in os.listdir(OSdir+'mc/') if "VLL" not in item or "M600" in item]
    for isub in swjd:
        print(isub)
        processName = isub  # Set processName to the current isub
        global_weight = calculate_global_weight(era, processName)  # Calculate global_weight for each isub
        isData = uf.isData(isub)
        preDir = 'data/' if isData else 'mc/'
        icutflow = getHistDir(OSdir + preDir + isub, 'OScutflow', global_weight)
        subDic[isub] = icutflow
    print(subDic)

    sumDic = sum_histograms(subDic)
    print(sumDic)

    #writeCSV(sumDic, OSdir)
    writeCSV(subDic, OSdir, 'cutflow_sub')

def calculate_global_weight(era, processName):
    # Replace these dictionary accesses with actual data retrieval
    lumi = lumiMap[era]
    cross_section = crossSectionMap[processName]
    gen_sum = genSumMap[era][processName]
    return lumi * cross_section / gen_sum

def writeCSV(sumDic, OSdir, name='cutflow', ifsub=False):
    df = histogram_to_dataframe(sumDic)
    outDir = OSdir + 'results/'
    uf.checkMakeDir(outDir)
    df.to_csv(outDir + name + '.csv', index=False)
    print(f"Cutflow CSV written to {outDir + name + '.csv'}")

def histogram_to_dataframe(hist_dict):
    dic = {}
    for subprocess, hist in hist_dict.items():
        print(subprocess, hist)
        icutflow = []
        for bin in range(1, hist.GetNbinsX() + 1):
            bin_content = hist.GetBinContent(bin)
            icutflow.append(f"{bin_content:.2f}")
            #icutflow.append(bin_content)
        dic[subprocess] = icutflow
    df = pd.DataFrame.from_dict(dic, orient='index', columns=['initial', 'METFilter', 'HLT', 'tauF>=1', 'jet>=6', 'bjet>1', 'HT>480&6thjet>38'])
    #df = pd.DataFrame.from_dict(dic, orient='index', columns=['initial', 'METFilter', 'HLT', 'tauF', 'jet', 'bjet', 'HT'])
    df.reset_index(inplace=True)
    df.rename(columns={'index': 'Process'}, inplace=True)

    print(df)
    return df

def sum_histograms(subprocess_hist_dict):
    summed_hist_dict = {}
    for subprocess, summed_process in gq.histoGramPerSample.items():
        if summed_process == "ttExtra":
            continue

        if "VLL" in summed_process and "VLLm600" not in summed_process:
            continue
        if subprocess not in subprocess_hist_dict:
            #print(f"Warning: Subprocess {subprocess} not found in histogram dictionary")
            continue

        hist = subprocess_hist_dict[subprocess]

        if summed_process not in summed_hist_dict:
            summed_hist_dict[summed_process] = hist.Clone(summed_process)
            summed_hist_dict[summed_process].SetDirectory(0)
        else:
            summed_hist_dict[summed_process].Add(hist)

    return summed_hist_dict

def getHistDir(directory, hist_name, global_weight):
    summed_hist = None
    root_files = glob.glob(os.path.join(directory, '*.root'))

    for file_path in root_files:
        root_file = ROOT.TFile.Open(file_path)
        if not root_file:
            print(f"Error: Could not open {file_path}")
            continue

        tree = root_file.Get("tree")
        if not tree:
            print(f"Error: Histogram {hist_name} not found in {file_path}")
            root_file.Close()
            continue

        hist = root_file.Get("OScutflow")
        
        hist.Scale(global_weight)

        if summed_hist is None:
            summed_hist = hist.Clone("summed_hist")
            summed_hist.SetDirectory(0)
        else:
            summed_hist.Add(hist)

        root_file.Close()

    return summed_hist

if __name__ == "__main__":
    main()
