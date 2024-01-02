import os
import subprocess

import usefulFunc as uf


def main():
    #set up voms first
    # T2Dir = '/cms/store/user/hhua/DYJetsToLL_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost/mc/TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost/mc/TTto4Q_TuneCP5_13p6TeV_powheg-pythia8/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost/mc/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost_2022PostEE/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost_2022PostEE_v2/'
    T2Dir = '/cms/store/user/hhua/crabNanoPost_2022preEE_v3/'
    # outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/TTto2L2Nu/'
    # outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/TTto4Q/'
    outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/'
    
    # for ipro in os.listdir(T2Dir):
    #     print(ipro)
    #     iT2Dir = T2Dir + ipro + 'crab*/*/0000/'
    #     ioutDir = outDir + ipro.find('_')
        
    # outDir = outDir+ 'crabNanoPost_2022PostEE_v2/'
    outDir = outDir+ 'crabNanoPost_2022preEE_v3/'
    # copyT2ToT3(T2Dir, outDir)
    
    
    notFinishedList = [
        'QCD_PT-30to50_TuneCP5_13p6TeV_pythia8', 
        'QCD_PT-3200_TuneCP5_13p6TeV_pythia8',
        'QCD_PT-80to120_TuneCP5_13p6TeV_pythia8',
        'QCD_PT-800to1000_TuneCP5_13p6TeV_pythia8',
        'TTTT_TuneCP5_13p6TeV_amcatnlo-pythia8',
        'TTtoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8',
        'TTto4Q_TuneCP5_13p6TeV_powheg-pythia8',
        # 'crab_TTto4Q_TuneCP5_13p6TeV_powheg-pythia81',
    ]
    deleteT2Dir(T2Dir, notFinishedList)
    
   
    # T3Dir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022PostEE/data/JetMET/'
    # T3Dir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022PostEE/data/' #!!!need in previous nanoAOD tool step make data MC outDir consistent!
    # mvDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022PostEE/2022postEE/data/' 
    # mvDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022PostEE/2022postEE/mc/' 
    # sortT3Dir( T3Dir, mvDir)
    
def sortT3Dir( initDir, outDir):
    for ipro in os.listdir(initDir):
        print('iDir: ', ipro)
        # iproName = ipro.split('crab_')[1]
        iproName = ipro.split('_')[0]
        print('iProName: ', iproName)
        
        # fromDir = initDir+ipro +'/*/0000/*'
        fromDir = initDir+ipro +'/*/*/0000/*'
        toDir = outDir +iproName
        uf.checkMakeDir(toDir)
        mvCommand = 'mv {} {}'.format(fromDir, toDir)
        # mvCommand = 'mv -n {} {}'.format(fromDir, toDir) #not dry run!!!
        print('command: ', mvCommand)
        sub = subprocess.run(mvCommand, shell=True)
        print(sub.stdout)
        print('done mv ', ipro, ' \n')
        
        
def copyT2ToT3(T2Dir, T3Dir):
    # command = 'xrdcp -r --parallel 4 root://cceos.ihep.ac.cn:1094//eos/ihep/' + T2Dir + ' '+ T3Dir #not working 
    command = 'gfal-copy -r -t 99999 root://cceos.ihep.ac.cn:1094//eos/ihep/' + T2Dir + ' '+ T3Dir ###!!!gfal-copy too slow, need to think of other ways
    uf.runCommand(command)
    print('copy done \n\n')
    
def deleteT2Dir(T2Dir, exceptDir):
    subDirs = getDirList(T2Dir)
    print('subDirs: ', subDirs)
    
def getDirList(T2Dir):
    # command = 'xrdfs root://cceos.ihep.ac.cn:1094//eos/ihep/ ls ' + T2Dir
    command = 'gfal-ls root://cceos.ihep.ac.cn:1094//eos/ihep/' + T2Dir + 'mc/'
    sub = subprocess.run(command, shell=True, stdout=subprocess.PIPE)
    subDirs = sub.stdout.decode('utf-8').split('\n')
    #delete empty string
    subDirs = [x for x in subDirs if x]
    return subDirs
    
    
   
if __name__=='__main__':
    main() 