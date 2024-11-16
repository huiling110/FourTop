import subprocess 
import os
#!set up Voms credentials first 
#!also cmsenv, for the xroot dependance wrong
import ROOT
import argparse

#!xroot -r for copying directory too slow

Process_dict = {
#2018 datasets
"2018": {
"TTZToLLNuNu":"/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"TTZToQQ":"/TTZToQQ_TuneCP5_13TeV_amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v3/NANOAODSIM",
"TTWJetsToQQ":"/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"TTWJetsToLNu":"/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"WJetsToLNu_HT-200To400":"/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"WJetsToLNu_HT-400To600":"/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"WJetsToLNu_HT-600To800":"/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"WJetsToLNu_HT-800To1200":"/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"WJetsToLNu_HT-1200To2500":"/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"WJetsToLNu_HT-2500ToInf":"/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
"DYJetsToLL_M-10to50":"/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
"DYJetsToLL_M-50":"/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",



# "zz":"/ZZ_TuneCP5_13TeV-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "WWW":"/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",   #!!!need to be corrected in AN list
# "WWW_Extra1":"/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1_ext1-v2/NANOAODSIM",
# "WWZ":"/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",  #!!!need to be corrected in AN list
# "WWZ_Extra1":"/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1_ext1-v2/NANOAODSIM",
# "WZZ":"/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "WZZ_Extra1":"/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1_ext1-v2/NANOAODSIM",
# "ZZZ":"/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM", #!!!need to be corrected in AN list
# "ZZZ_Extra1":"/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1_ext1-v2/NANOAODSIM",
# "ZGToLLG":"/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM", #!!!need to be corrected in AN list
# "ggH_bb":"/GluGluHToBB_M-125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
# "ggH_WW_2l":"/GluGluHToWWTo2L2Nu_M-125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",
# "ggH_ZZ_2l":"/GluGluHToZZTo2L2Q_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "ggH_ZZ_4l":"/GluGluHToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "vbfH_WW_2l":"/VBFHToWWTo2L2Nu_M-125_TuneCP5_13TeV-powheg-jhugen727-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM",




},
#2017 datasets
"2017":{
},

#datasets 2016
"2016": {
},

#datasets 2016APV
"2016APV": {
}
}

parser = argparse.ArgumentParser()
parser.add_argument('--nameid', type=int, default=0, help='int min 0 max 40')
parser.add_argument('--out_path', type=str, default="/publicfs/cms/data/TopQuark/nanoAOD_new/", help='Output Path')
parser.add_argument('--year', type=str, default="2018", help='2016 2016APV 2017 2018')
args = parser.parse_args()

if args.year == "2018":
    import input.tttt_samples_new as tttt_Charis
if args.year == "2017":
    import input.tttt_Extra_Charis_2017 as tttt_Charis
if args.year == "2016":
    import input.tttt_Extra_Charis_2016 as tttt_Charis
if args.year == "2016APV":
    import input.tttt_Extra_Charis_2016APV as tttt_Charis

Process_name_list = list(Process_dict[args.year].keys())

def copySingleFile():
    for isam, ifile in tttt_Charis.filesetSignal.items():
        print(isam)
        outName = isam
        # outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/VLL/' + outName + '/'
        outDir = args.out_path + args.year + '/mc/' + outName + '/'
        
        if not os.path.exists( outDir ):
            os.mkdir( outDir )
        print(outName)
        if not outName in Process_name_list: continue          # download one file once, you can remove it
        
        for inano in ifile:
            # inputDir = redirector + inano
            command = 'xrdcp --verbose ' + inano + ' ' + outDir
            print(command)
            file_name = inano.split('/')[-1]
            print(outDir+file_name)
            if os.path.exists(outDir+file_name):
                root_file = ROOT.TFile.Open(outDir+file_name)
                if not root_file:
                    print(f'rm {outDir+file_name}')
                    subprocess.run([f'rm {outDir+file_name}'], shell=True)
                elif root_file.IsZombie():
                    print(f'rm {outDir+file_name}')
                    subprocess.run([f'rm {outDir+file_name}'], shell=True)
                else:
                    print(f"{file_name} exists!!!")
                    continue
            process = subprocess.run([command], shell=True)
            output =  process.stdout
            print(output)
        print('\n\n') 
        
        
        
if __name__=='__main__':
    copySingleFile()

