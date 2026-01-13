import usefulFunc as uf
import ttttGlobleQuantity as gq
# import plotVaribles as pl
import pl as pl
import argparse
import yaml
import os

def get_input_dir_from_config(config, era):
    """Build input directory path from config for a given era."""
    base_path = config['paths']['output_base']
    stage1_version = config['versions']['stage1']
    hist_version = config['versions']['hist']

    return f"{base_path}/{era}/v1baselineHadro_{stage1_version}/mc/variableHists_{hist_version}/"

def main_with_config(config_path, channel):
    """Main function using config file."""
    with open(config_path, 'r') as f:
        config = yaml.safe_load(f)

    # Get input directories for all eras
    inputDir2018 = get_input_dir_from_config(config, '2018')
    inputDir2017 = get_input_dir_from_config(config, '2017')
    inputDir2016preVFP = get_input_dir_from_config(config, '2016preVFP')
    inputDir2016postVFP = get_input_dir_from_config(config, '2016postVFP')

    # Get options from config
    ifMCFTau = config.get('options', {}).get('mc_fake_tau', False)
    ifblinding = config.get('options', {}).get('blind', False)

    # Set region list based on channel
    if channel == '1tau1l':
        regionList = ['1tau1lSR', '1tau1lCR12']
    elif channel == '1tau0l':
        regionList = ['1tau0lSR', '1tau0lCRMR', '1tau0lVR']
    elif channel == '1tau2l':
        regionList = ['1tau2lSR', '1tau2lCR3']
    else:
        raise ValueError(f"Unknown channel: {channel}")

    print(f"Config: {config_path}")
    print(f"Channel: {channel}")
    print(f"Regions: {regionList}")
    print(f"Input dir (2018): {inputDir2018}")

    variables = ['BDT']
    sumPros = pl.getSumList(channel, True, False, ifMCFTau)
    print(f"Processes: {sumPros}")

    sumProHists2018, sumProHistsSys2018 = getSumHistPerYear(inputDir2018, regionList, variables, sumPros, channel, ifMCFTau)
    sumProHists2017, sumProHistsSys2017 = getSumHistPerYear(inputDir2017, regionList, variables, sumPros, channel, ifMCFTau)
    sumProHists2016preVFP, sumProHistsSys2016preVFP = getSumHistPerYear(inputDir2016preVFP, regionList, variables, sumPros, channel, ifMCFTau)
    sumProHists2016postVFP, sumProHistsSys2016postVFP = getSumHistPerYear(inputDir2016postVFP, regionList, variables, sumPros, channel, ifMCFTau)

    for iVar in variables:
        plotIVar(sumProHists2018, sumProHistsSys2018, sumProHists2017, sumProHistsSys2017, sumProHists2016preVFP, sumProHistsSys2016preVFP, sumProHists2016postVFP, sumProHistsSys2016postVFP, sumPros, inputDir2018, iVar, ifMCFTau, ifblinding)

def main():
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE2/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE2/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE2/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    # inputDir2018 = '/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_Varibles_1tau1l_VLLm600_5_FakeTau/'
    # inputDir2017 = '/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_Varibles_1tau1l_VLLm600_5_FakeTau/'
    # inputDir2016postVFP = '/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_Varibles_1tau1l_VLLm600_5_FakeTau/'
    # inputDir2016preVFP = '/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_Varibles_1tau1l_VLLm600_5_FakeTau/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/'
    # channel = '1tau1l'
    # regionList = ['1tau1lCR12', '1tau1lSR']
    # regionList = ['1tau1lCR12']
   
   
    
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l_newMCSample/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lNewCR/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lNewCR/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lNewCR/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lNewCR/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/combine/datacardSys_v4BasicAndJESJER/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/'
    # channel = '1tau2l'
    # regionList = ['1tau2lSR', '1tau2lCR3'] 
    
    
    
    
    
    #1tau0l
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputs/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputsWith2018train/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputsWith2018train/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputsWith2018train/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/' #!problem with fakeTau_MC 
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/'
    inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v5BDT1tau0l_tauFMorphFix/'
    inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v5BDT1tau0l_tauFMorphFix/'
    inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v5BDT1tau0l_tauFMorphFix/'
    inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v5BDT1tau0l_tauFMorphFix/'
    channel = '1tau0l'
    regionList = ['1tau0lSR', '1tau0lCRMR', '1tau0lVR']
    
    
    
    
    # ifMCFTau = True #!
    ifMCFTau = False #!
    ifblinding = False
    
    variables = ['BDT']
    sumPros = pl.getSumList(channel, True, False, ifMCFTau)
    print(sumPros)
    
    sumProHists2018, sumProHistsSys2018 = getSumHistPerYear(inputDir2018, regionList, variables, sumPros, channel, ifMCFTau)
    sumProHists2017, sumProHistsSys2017 = getSumHistPerYear(inputDir2017, regionList, variables,  sumPros, channel, ifMCFTau)
    sumProHists2016preVFP, sumProHistsSys2016preVFP = getSumHistPerYear(inputDir2016preVFP, regionList, variables,  sumPros, channel, ifMCFTau)
    sumProHists2016postVFP, sumProHistsSys2016postVFP = getSumHistPerYear(inputDir2016postVFP, regionList, variables,  sumPros, channel, ifMCFTau)

    for iVar in variables:
        plotIVar(sumProHists2018, sumProHistsSys2018, sumProHists2017, sumProHistsSys2017, sumProHists2016preVFP, sumProHistsSys2016preVFP, sumProHists2016postVFP, sumProHistsSys2016postVFP, sumPros, inputDir2018, iVar, ifMCFTau, ifblinding)    
    
def plotIVar(sumProHists2018, sumProHistsSys2018, sumProHists2017, sumProHistsSys2017, sumProHists2016preVFP, sumProHistsSys2016preVFP, sumProHists2016postVFP, sumProHistsSys2016postVFP, sumPros, inputDir2018, iVar, ifMCFTau=False, ifblinding=False):
    combineHists = {}
    combineHistSys = {}
    for ire in sumProHists2018[iVar].keys():
        print(ire)
        combineHists[ire] = {}
        combineHistSys[ire] = {}
        for isumPro in sumProHists2018[iVar][ire].keys():
            # sumProHists2018[iVar][ire][isumPro].Print()
            combineHists[ire][isumPro] = sumProHists2018[iVar][ire][isumPro].Clone()
            combineHistSys[ire][isumPro] = {}
            if not uf.isData(isumPro):
                combineHists[ire][isumPro].Add(sumProHists2017[iVar][ire][isumPro])
                combineHists[ire][isumPro].Add(sumProHists2016preVFP[iVar][ire][isumPro])
                combineHists[ire][isumPro].Add(sumProHists2016postVFP[iVar][ire][isumPro])
                combineHistSys[ire][isumPro] = addSys(sumProHistsSys2018[iVar][ire][isumPro], sumProHistsSys2017[iVar][ire][isumPro], sumProHistsSys2016preVFP[iVar][ire][isumPro], sumProHistsSys2016postVFP[iVar][ire][isumPro])
            else:
                # combineHists[ire][isumPro]
                # uf.addDataHist(combineHists[ire][isumPro], sumProHists2017[iVar][ire][isumPro])
                # uf.addDataHist(combineHists[ire][isumPro], sumProHists2016preVFP[iVar][ire][isumPro])
                # uf.addDataHist(combineHists[ire][isumPro], sumProHists2016postVFP[iVar][ire][isumPro])
                combineHists[ire][isumPro].Add(sumProHists2017[iVar][ire][isumPro])
                combineHists[ire][isumPro].Add(sumProHists2016preVFP[iVar][ire][isumPro])
                combineHists[ire][isumPro].Add(sumProHists2016postVFP[iVar][ire][isumPro])
    
    plotDir = inputDir2018+'results/'
    uf.checkMakeDir(plotDir)
    plotName = 'combination_withSys' if not ifMCFTau else 'combination_withSys_MCFTau'
    for ire in combineHists.keys():
        # pl.makeStackPlotNew(combineHists[ire], sumPros, iVar, ire, plotDir, False, plotName, 'Run2', True, 100, True, True, True, False, combineHistSys[ire], True ) 
        pl.makeStackPlotNew(combineHists[ire], sumPros, iVar, ire, plotDir, False, plotName, 'Run2', True, 100, True, True, True, False, combineHistSys[ire], True, ifblinding ) 
   
def addSys(sumProHistsSys2018, sumProHistsSys2017, sumProHistsSys2016preVFP, sumProHistsSys2016postVFP) :
    sumSys = {}
    for isys, ihist in sumProHistsSys2018.items():
        isys2017 = isys.replace('2018', '2017')
        isys2016preVFP = isys.replace('2018', '2016preVFP')
        isys2016postVFP = isys.replace('2018', '2016postVFP')
        # Systematics that use shared '2016' instead of '2016preVFP'/'2016postVFP'
        if 'CMS_eff_e_reco' in isys or 'CMS_scale_t_DeepTau' in isys:
            isys2016preVFP = isys2016preVFP.replace('2016preVFP', '2016')
            isys2016postVFP = isys2016postVFP.replace('2016postVFP', '2016')

        sumSys[isys] = sumProHistsSys2018[isys].Clone()
        sumSys[isys].Add(sumProHistsSys2017[isys2017])
        sumSys[isys].Add(sumProHistsSys2016postVFP[isys2016postVFP])
        sumSys[isys].Add(sumProHistsSys2016preVFP[isys2016preVFP])
    return sumSys 
        
    
    
def getSumHistPerYear(inputDir2018, regionList, variables, sumPros, channel, ifMCFTau = False):
    era = uf.getEraFromDir(inputDir2018)
    print('era=', era)
    # isRun3 = uf.isRun3(inputDir2018)
    inputDirDic = uf.getInputDicNew( inputDir2018)
    uf.checkMakeDir( inputDirDic['mc']+'results/')
    
    sumProSys = pl.getSysDicPL(sumPros, True, channel, era, True)
    # Skip subprocesses that were excluded from JES systematics (negligible contribution)
    skip_subs = gq.SKIP_SUBPROCESSES.get(channel, [])
    sumProHists, sumProHistsSys = uf.getSumHist(inputDirDic, regionList, sumPros, sumProSys,  variables, era, False, False, ifMCFTau, skip_subs)
    return sumProHists, sumProHistsSys
    
    
    
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Plot Run2 combination prefit plots')
    parser.add_argument('--config', type=str, help='Path to config YAML file')
    parser.add_argument('--channel', type=str, choices=['1tau1l', '1tau0l', '1tau2l'],
                        help='Analysis channel')
    args = parser.parse_args()

    if args.config and args.channel:
        main_with_config(args.config, args.channel)
    else:
        # Fall back to legacy hardcoded paths
        main()