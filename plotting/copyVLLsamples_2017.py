import subprocess 
import os
#!set up Voms credentials first 
#!also cmsenv, for the xroot dependance wrong
import input.ttX_Charis_2016APV as VLL_Charis_2016APV
import input.ttX_Charis_2016post as VLL_Charis_2016post
import input.ttX_Charis_2017 as VLL_Charis_2017
import input.ttX_Charis_2018 as VLL_Charis_2018
import ROOT

#!xroot -r for copying directory too slow

Process_name = [
    "TTZToLLNuNu",
    "TTZToQQ",
    "TTWJetsToLNu",
    "TTWJetsToQQ"
]

def copyDir():
    redirector = 'root://cmsxrootd.hep.wisc.edu//'
    # redirector = ''
    #from Charis: https://gitlab.cern.ch/ckoraka/vll-analysis/-/blob/master/samples/fileLists/Signal_2018.py?ref_type=heads
    sampleDic = {
    # 'VLL_EE_M600': '/store/user/ckoraka/VLferm_EWcouplings_4321_m600GeV_EE_to_4b/RunIISummer20UL18_NanoAODv9/230718_212705/0000/',
    # 'VLL_EN_M600': '/store/user/ckoraka/VLferm_EWcouplings_4321_m600GeV_EN_to_4b/RunIISummer20UL18_NanoAODv9/230718_212731/0000/',
    # 'VLL_NN_M600': '/store/user/ckoraka/VLferm_EWcouplings_4321_m600GeV_NN_to_4b/RunIISummer20UL18_NanoAODv9/230718_212756/0000/',#done

    # 'VLL_EE_M650': '/store/user/ckoraka/VLferm_EWcouplings_4321_m650GeV_EE_to_4b/RunIISummer20UL18_NanoAODv9/230718_212823/0000/',
    # 'VLL_EN_M650': '/store/user/ckoraka/VLferm_EWcouplings_4321_m650GeV_EN_to_4b/RunIISummer20UL18_NanoAODv9/230718_212847/0000/',
    # 'VLL_NN_M650': '/store/user/ckoraka/VLferm_EWcouplings_4321_m650GeV_NN_to_4b/RunIISummer20UL18_NanoAODv9/230718_212915/0000/',#done

    'VLL_EE_M700': '/store/user/ckoraka/VLferm_EWcouplings_4321_m700GeV_EE_to_4b/RunIISummer20UL18_NanoAODv9/230718_212943/0000/',
    'VLL_EN_M700': '/store/user/ckoraka/VLferm_EWcouplings_4321_m700GeV_EN_to_4b/RunIISummer20UL18_NanoAODv9/230718_213011/0000/',
    'VLL_NN_M700': '/store/user/ckoraka/VLferm_EWcouplings_4321_m700GeV_NN_to_4b/RunIISummer20UL18_NanoAODv9/230718_213039/0000/',

    'VLL_EE_M750': '/store/user/ckoraka/VLferm_EWcouplings_4321_m750GeV_EE_to_4b/RunIISummer20UL18_NanoAODv9/230718_213110/0000/',
    'VLL_EN_M750': '/store/user/ckoraka/VLferm_EWcouplings_4321_m750GeV_EN_to_4b/RunIISummer20UL18_NanoAODv9/230718_213135/0000/',
    'VLL_NN_M750': '/store/user/ckoraka/VLferm_EWcouplings_4321_m750GeV_NN_to_4b/RunIISummer20UL18_NanoAODv9/230718_213202/0000/',

    # 'VLL_EE_M800': '/store/user/ckoraka/VLferm_EWcouplings_4321_m800GeV_EE_to_4b/RunIISummer20UL18_NanoAODv9/230718_213240/0000/',
    # 'VLL_EN_M800': '/store/user/ckoraka/VLferm_EWcouplings_4321_m800GeV_EN_to_4b/RunIISummer20UL18_NanoAODv9/230718_213240/0000/',
    # 'VLL_NN_M800': '/store/user/ckoraka/VLferm_EWcouplings_4321_m800GeV_NN_to_4b/RunIISummer20UL18_NanoAODv9/230718_213240/0000/',



    }

    # redirector = 'root://cmsxrootd-cms.infn.it//'
    VLLfile = 'root://cmsxrootd.hep.wisc.edu///store/user/ckoraka/VLferm_EWcouplings_4321_m500GeV_EE_to_4b/RunIISummer20UL18_NanoAODv9/230718_212434/0000/NanoAODv9_10.root'

    # outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/VVL_600/' 
    outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2016APV/mc/' 

    for isam, ifile in sampleDic.items():
        inputDir = redirector + ifile
        ioutDir = outDir + isam + '/'
        if not os.path.exists( ioutDir ):
            os.mkdir( ioutDir )
        # command = 'xrdcp -r ' + inputDir + ' ' + ioutDir
        command = 'xrdcp -r --parallel 5 ' + inputDir + ' ' + ioutDir
        # command = 'xrdcp -r --parallel 5 ' + inputDir + '*.root ' + ioutDir
        print(command)
        # process = subprocess.run([command], shell=True)
        # output =  process.stdout
        # print(output)
        
    # inputDir = redirector + sampleDic['VLL_EE_M600']
    # # command = 'xrdcp '+ VLLfile + ' ' + outDir #only works with CMSSW
    # command = 'xrdcp -r ' + inputDir + ' ' + outDir
    # print(command)
    # process = subprocess.run([command], shell=True)
    # output =  process.stdout
    # print(output)
    
def copySingleFile():
    for isam, ifile in VLL_Charis_2017.filesetSignal.items():
        print(isam)
        outName = isam
        # outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/VLL/' + outName + '/'
        outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/' + outName + '/'
        
        if not os.path.exists( outDir ):
            os.mkdir( outDir )
        print(outName)
        # if not outName == 'VLL_EE_M500': continue
        # if outName == 'VLL_EE_M500': continue
        if not Process_name[1] in outName: continue
        
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
        
        
        
        
        
def transform_string(input_str):
    # Split the string by underscores
    parts = input_str.split('_')
    # Extract the relevant parts
    prefix = parts[0] + '_' + parts[1]  # 'VLL_EE'
    mass_part = parts[2]  # 'M-500GeV'
        # Remove the hyphen and 'GeV'
    mass_value = mass_part.replace('-', '').replace('GeV', '')
    # Combine the parts
    # output_str = f"{prefix}_M{mass_value}"
    output_str = f"{prefix}_{mass_value}"
    return output_str
        
if __name__=='__main__':
    # copyDir()
    copySingleFile()


