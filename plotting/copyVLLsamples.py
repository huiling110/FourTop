import subprocess 
import os
#!set up Voms credentials first 
#!also cmsenv, for the xroot dependance wrong


# redirector = ''
#from Charis: https://gitlab.cern.ch/ckoraka/vll-analysis/-/blob/master/samples/fileLists/Signal_2018.py?ref_type=heads
sampleDic = {
'VLL_EE_M600': '/store/user/ckoraka/VLferm_EWcouplings_4321_m600GeV_EE_to_4b/RunIISummer20UL18_NanoAODv9/230718_212705/0000/',
'VLL_EN_M600': '/store/user/ckoraka/VLferm_EWcouplings_4321_m600GeV_EN_to_4b/RunIISummer20UL18_NanoAODv9/230718_212731/0000/',
'VLL_NN_M600': '/store/user/ckoraka/VLferm_EWcouplings_4321_m600GeV_NN_to_4b/RunIISummer20UL18_NanoAODv9/230718_212756/0000/',
}

redirector = 'root://cmsxrootd.hep.wisc.edu//'
VLLfile = 'root://cmsxrootd.hep.wisc.edu///store/user/ckoraka/VLferm_EWcouplings_4321_m500GeV_EE_to_4b/RunIISummer20UL18_NanoAODv9/230718_212434/0000/NanoAODv9_10.root'

outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/VVL_600/' 

for isam, ifile in sampleDic.items():
    inputDir = redirector + ifile
    ioutDir = outDir + isam + '/'
    if not os.path.exists( ioutDir ):
        os.mkdir( ioutDir )
    command = 'xrdcp -r ' + inputDir + ' ' + ioutDir
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


