import subprocess

def query_das(dataset):
    # Use dasgoclient to query the dataset
    command = f"dasgoclient -query='file dataset={dataset}'"
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    stdout, stderr = process.communicate()
    
    # Check if the command was successful
    if process.returncode != 0:
        print(f"Error querying DAS: {stderr}")
        return []

    # Split the output into lines and return as a list
    file_list = stdout.strip().split('\n')
    return file_list

def main():
    # Specify the dataset you want to query
    dataset_dict = {
#2018 datasets
"2018": {
"ttbar_2l":"/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"ww":"/WW_TuneCP5_13TeV-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"wz":"/WZ_TuneCP5_13TeV-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"tttt":"/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"qcd_1000to1500":"/QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"qcd_100to200":"/QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"qcd_1500to2000":"/QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"qcd_2000toInf":"/QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"qcd_200to300":"/QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"qcd_500to700":"/QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"qcd_50to100":"/QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"qcd_700to1000":"/QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"qcd_300to500":"/QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"ttbar_0l":"/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"ttbar_1l":"/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"st_antitchan":"/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"st_tW_antitop":"/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"st_tW_top":"/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"st_tchan":"/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"st_tZq":"/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"ttW":"/ttWJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"ttZ":"/ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"ttG":"/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"ttWW":"/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"ttWZ":"/TTWZ_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"ttWH":"/TTWH_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"ttZZ":"/TTZZ_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"ttZH":"/TTZH_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"ttHH":"/TTHH_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"ggH_bb":"/GluGluHToBB_M-125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"ggH_gg":"/GluGluHToGG_M125_13TeV-sherpa/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"ggH_tautau":"/GluGluHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"ggH_WW_2l":"/GluGluHToWWTo2L2Nu_M-125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"ggH_ZZ_4l":"/GluGluHToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"ggH_ZZ_2l":"/GluGluHToZZTo2L2Q_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"vbfH_bb":"/VBFHToBB_M-125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"vbfH_tautau":"/VBFHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"vbfH_WW_2l":"/VBFHToWWTo2L2Nu_M-125_TuneCP5_13TeV-powheg-jhugen727-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"vH_nonbb":"/VHToNonbb_M125_TuneCP5_13TeV-amcatnloFXFX_madspin_pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"ttH_bb":"/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"ttH_nonbb":"/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
#"jetHT_2018a":"/JetHT/Run2018A-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD",
#"jetHT_2018b":"/JetHT/Run2018B-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"jetHT_2018c":"/JetHT/Run2018C-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2018a":"/SingleMuon/Run2018A-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD",
#"singleMu_2018b":"/SingleMuon/Run2018B-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD",
#"singleMu_2018c":"/SingleMuon/Run2018C-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD",
#"singleMu_2018d":"/SingleMuon/Run2018D-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
},
#2017 datasets
"2017":{
"dy":"/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"dy_ext":"/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9_ext1-v1/NANOAODSIM",
"ttbar_2l":"/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"ww":"/WW_TuneCP5_13TeV-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"wz":"/WZ_TuneCP5_13TeV-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"zz":"/ZZ_TuneCP5_13TeV-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"tttt":"/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"qcd_1000to1500":"/QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"qcd_100to200":"/QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"qcd_1500to2000":"/QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"qcd_200to300":"/QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"qcd_300to500":"/QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"qcd_500to700":"/QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"qcd_50to100":"/QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"qcd_700to1000":"/QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"ttbar_0l":"/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"ttbar_1l":"/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"st_antitchan":"/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"st_tchan":"/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"st_tW_antitop":"/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"st_tW_top":"/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"st_tZq":"/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"ttW":"/ttWJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"ttZ":"/ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"ttG":"/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"ttWW":"/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"ttWZ":"/TTWZ_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"ttWH":"/TTWH_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"ttZZ":"/TTZZ_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"ttZH":"/TTZH_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"ttHH":"/TTHH_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"ggH_gg":"/GluGluHToGG_M125_13TeV-sherpa/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"ggH_tautau":"/GluGluHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"ggH_WW_2l":"/GluGluHToWWTo2L2Nu_M-125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"ggH_ZZ_4l":"/GluGluHToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"ggH_ZZ_2l":"/GluGluHToZZTo2L2Nu_M125_TuneCP5_13TeV_powheg2_JHUGenV735_pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"vbfH_tautau":"/VBFHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"vbfH_WW_2l":"/VBFHToWWTo2L2Nu_M-125_TuneCP5_13TeV-powheg-jhugen727-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"vH_nonbb":"/VHToNonbb_M125_TuneCP5_13TeV-amcatnloFXFX_madspin_pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
"ttH_bb":"/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM",
"ttH_nonbb":"/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM",
#"jetHT_2017b":"/JetHT/Run2017B-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"jetHT_2017c":"/JetHT/Run2017C-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"jetHT_2017d":"/JetHT/Run2017D-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"jetHT_2017e":"/JetHT/Run2017E-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"jetHT_2017f":"/JetHT/Run2017F-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2017b":"/SingleMuon/Run2017B-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2017c":"/SingleMuon/Run2017C-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2017d":"/SingleMuon/Run2017D-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2017e":"/SingleMuon/Run2017E-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2017f":"/SingleMuon/Run2017F-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2017g":"/SingleMuon/Run2017G-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2017h":"/SingleMuon/Run2017H-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
},

#datasets 2016
"2016": {
"tttt":"/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"qcd_1500to2000":"/QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"qcd_2000toInf":"/QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"qcd_1000to1500":"/QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"qcd_100to200":"/QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"qcd_200to300":"/QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"qcd_300to500":"/QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"qcd_50to100":"/QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"qcd_500to700":"/QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"qcd_700to1000":"/QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"ttbar_2l":"/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"ttbar_0l":"/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"ttbar_1l":"/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"st_antitchan":"/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"st_tchan":"/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"st_tW_antitop":"/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"st_tW_top":"/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"st_tZq":"/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"ttG":"/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"ttWW":"/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"ttWZ":"/TTWZ_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"ttWH":"/TTWH_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"ttZZ":"/TTZZ_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"ttZH":"/TTZH_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"ttHH":"/TTHH_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"ggH_bb":"/GluGluHToBB_M-125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"ggH_gg":"/GluGluHToGG_M125_13TeV-sherpa/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"ggH_tautau":"/GluGluHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"ggH_WW_2l":"/GluGluHToWWTo2L2Nu_M-125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"ggH_ZZ_4l":"/GluGluHToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"vbfH_bb":"/VBFHToBB_M-125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"vbfH_tautau":"/VBFHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"vbfH_WW_2l":"/VBFHToWWTo2L2Nu_M-125_TuneCP5_13TeV-powheg-jhugen727-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"vH_nonbb":"/VHToNonbb_M125_TuneCP5_13TeV-amcatnloFXFX_madspin_pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM",
"ttH_bb":"/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"ttH_nonbb":"/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
#"jetHT_2016F":"/JetHT/Run2016F-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"jetHT_2016G":"/JetHT/Run2016G-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"jetHT_2016H":"/JetHT/Run2016H-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2016F":"/SingleMuon/Run2016F-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2016G":"/SingleMuon/Run2016G-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2016H":"/SingleMuon/Run2016H-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
"ww":"/WW_TuneCP5_13TeV-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"wz":"/WZ_TuneCP5_13TeV-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"zz":"/ZZ_TuneCP5_13TeV-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"dy":"/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16NanoAODv2-106X_mcRun2_asymptotic_v15-v1/NANOAODSIM",
#"doubleMu_2016f":"/DoubleMuon/Run2016F-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleMu_2016g":"/DoubleMuon/Run2016G-UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
#"doubleMu_2016h":"/DoubleMuon/Run2016H-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleEG_2016f":"/DoubleEG/Run2016F-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleEG_2016g":"/DoubleEG/Run2016G-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleEG_2016h":"/DoubleEG/Run2016H-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
"dy_fxfx":"/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"dy_fxfx_2j":"/DYJetsToLL_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM"
},

#datasets 2016APV
"2016APV": {
"ww":"/WW_TuneCP5_13TeV-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"wz":"/WZ_TuneCP5_13TeV-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"zz":"/ZZ_TuneCP5_13TeV-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"ttbar_2l":"/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v1/NANOAODSIM",
"dy":"/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
#"doubleMu_2016b_v1":"/DoubleMuon/Run2016B-ver1_HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleMu_2016b_v2":"/DoubleMuon/Run2016B-ver2_HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleMu_2016c":"/DoubleMuon/Run2016C-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleMu_2016d":"/DoubleMuon/Run2016D-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleMu_2016e":"/DoubleMuon/Run2016E-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleMu_2016f_hipm":"/DoubleMuon/Run2016F-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleEG_2016b_v1":"/DoubleEG/Run2016B-ver1_HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleEG_2016b_v2":"/DoubleEG/Run2016B-ver2_HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
#"doubleEG_2016c":"/DoubleEG/Run2016C-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleEG_2016d":"/DoubleEG/Run2016D-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleEG_2016e":"/DoubleEG/Run2016E-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"doubleEG_2016f_hipm":"/DoubleEG/Run2016F-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
"tttt":"/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2/NANOAODSIM",

"qcd_1000to1500":"/QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"qcd_100to200":"/QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"qcd_1500to2000":"/QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"qcd_2000toInf":"/QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"qcd_200to300":"/QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"qcd_500to700":"/QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"qcd_50to100":"/QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"qcd_700to1000":"/QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"ttbar_2l":"/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"ttbar_0l":"/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"ttbar_1l":"/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"st_antitchan":"/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"st_tchan":"/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"st_tW_antitop":"/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"st_tW_top":"/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"tZq_ll":"/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"ttW":"/ttWJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2/NANOAODSIM",
"ttZ":"/ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2/NANOAODSIM",
"ttG":"/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2/NANOAODSIM",
"TTWW":"/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"TTWZ":"/TTWZ_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"TTWH":"/TTWH_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2/NANOAODSIM",
"TTZZ":"/TTZZ_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"TTZH":"/TTZH_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2/NANOAODSIM",
"TTHH":"/TTHH_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2/NANOAODSIM",
"ggH_tautau":"/GluGluHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2/NANOAODSIM",
"ggH_WW_2l":"/GluGluHToWWTo2L2Nu_M-125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"vbfH_WW_2l":"/VBFHToWWTo2L2Nu_M-125_TuneCP5_13TeV-powheg-jhugen727-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"vH_nonbb":"/VHToNonbb_M125_TuneCP5_13TeV-amcatnloFXFX_madspin_pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v2/NANOAODSIM",
"ttH_bb":"/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"ttH_nonbb":"/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
#"jetHT_2016B_v1":"/JetHT/Run2016B-ver1_HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"jetHT_2016B_v2":"/JetHT/Run2016B-ver2_HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"jetHT_2016C":"/JetHT/Run2016C-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"jetHT_2016D":"/JetHT/Run2016D-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"jetHT_2016E":"/JetHT/Run2016E-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"jetHT_2016F_hipm":"/JetHT/Run2016F-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2016B_v1":"/SingleMuon/Run2016B-ver1_HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2016B_v2":"/SingleMuon/Run2016B-ver2_HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2016C":"/SingleMuon/Run2016C-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2016D":"/SingleMuon/Run2016D-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2016E":"/SingleMuon/Run2016E-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"singleMu_2016F_hipm":"/SingleMuon/Run2016F-HIPM_UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
"dy_fxfx":"/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"dy_fxfx_0j":"/DYJetsToLL_0J_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"dy_fxfx_1j":"/DYJetsToLL_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
"dy_fxfx_2j":"/DYJetsToLL_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11-v1/NANOAODSIM",
}
}

    #dcjdcsj = f"/VLferm_m{500+mass*50}GeV_{channel}_to_4b_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17-v2/NANOAODSIM"
    # Query DAS and get the list of files
    # file_list = query_das(dataset)
    # Print the list of files
    with open('tttt_Charis_2016APV.py', 'w') as f:
        f.write('''redirector = "root://cmsxrootd.fnal.gov/"''' + '\n')
        f.write('''filesetSignal = {''' + '\n')
        dataset_era = dataset_dict["2016APV"]
        for Process_name,dataset in dataset_era.items():
                print(dataset)
                file_list = query_das(dataset)
                f.write(f'''"{Process_name}" : [''' + '\n')
                for file in file_list[:-1]:
                    f.write(f'''redirector+"{file}",''' + '\n')
                f.write(f'''redirector+"{file_list[-1]}"''' + '\n')
                f.write("]," + '\n')
                print("DONE!!!")
        f.write("}" + '\n')
if __name__ == "__main__":
    main()
