import os
import subprocess

import usefulFunc as uf

T2DirPre = 'root://cceos.ihep.ac.cn:1094//eos/ihep//cms/store/user/hhua/'

def main():
    #set up voms first
    # T2Dir = '/cms/store/user/hhua/DYJetsToLL_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost/mc/TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost/mc/TTto4Q_TuneCP5_13p6TeV_powheg-pythia8/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost/mc/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost_2022PostEE/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost_2022PostEE_v2/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost_2022preEE_v3/mc/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost_data_v3/mc/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost_2022postEE_v3/mc/'
    # outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/TTto2L2Nu/'
    # outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/TTto4Q/'
    # outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/'
    T3Dir = '/publicfs/cms/data/TopQuark/nanoAOD/'
    
    # T2Dir = 'crabNanoPost_2022postEE_v3/'
    # T2Dir = 'crabNanoPost_2022preEE_v3/'
    # deleteT2Dir(T2Dir, False)

    T2Dir = 'crabNanoPost_run2_v3/'
    outDir = T3Dir + '/2017/BtagCSV/'
    uf.checkMakeDir(outDir)
    # copyT2ToT3(T2Dir, outDir, notFinishedList, True)
    copyT2ToT3(T2Dir, outDir, [], True)
    
   
    # mvDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022postEE_v3/data/'
    # T3Dir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022preEE_v3/data/'
    # mvDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022preEE_v3/data/'
    # sortT3Dir( T3Dir, mvDir, True)
    # sortT3Dir( T3Dir, mvDir, False)


def sortT3Dir( initDir, outDir, isData=False):
    for ipro in os.listdir(initDir):
        if 'crab_' not in ipro:
            continue
        print('iDir: ', ipro)
        iproName = getProName(ipro, isData)
        print('iProName: ', iproName)
        
        # fromDir = initDir+ipro +'/*/*/0000/*'
        # fromDir = initDir+ipro +'/*/0000/*' #!!!what if there is more folers than 0000/
        fromDir = initDir+ipro +'/*/*/*' #!!!what if there is more folers than 0000/
        toDir = outDir +iproName
        uf.checkMakeDir(toDir)
        mvCommand = 'mv {} {}'.format(fromDir, toDir)
        print('command: ', mvCommand)
        # sub = subprocess.run(mvCommand, shell=True)
        # print(sub.stdout)
        uf.runCommand(mvCommand)
        print('done mv ', ipro, ' \n')
       
def getProName(iDir, isData=False):
    iproName = iDir.split('crab_')[1]
    if not isData:
        name = iproName.split('_TuneCP')[0]
        postFix = iproName.split('_TuneCP')[1]
        postFix = postFix.split('pythia8')[1]
        name = name + postFix
    else: 
        name = iproName
    return name  
        
# def copyT2ToT3(T2Dir, T3Dir, copyList, ifDelete=False):
def copyT2ToT3(T2Dir, T3Dir, ignoreList, ifDelete=False):
    pros = getDirList(T2Dir)
    print('pros: ', pros)
    for ipro in pros:
        if ipro in ignoreList: continue
        print('copy ', ipro, '.......')
        # copyCommand = 'gfal-copy -r -t 99999 root://cceos.ihep.ac.cn:1094//eos/ihep/' + T2Dir + ipro + ' '+ T3Dir
        copyCommand = 'gfal-copy -r -t 99999 {}{}{} {}'.format(T2DirPre, T2Dir, ipro, T3Dir)
        uf.runCommand(copyCommand)
        print('copy done \n\n')
        if ifDelete:
            print('delete ', ipro, '.......')
            deleteCommand = 'gfal-rm -r root://cceos.ihep.ac.cn:1094//eos/ihep/' + T2Dir + ipro
            uf.runCommand(deleteCommand)
        else:
            print('skip ', ipro) 
        print('done ', ipro, ' \n\n')
     
    # command = 'xrdcp -r --parallel 4 root://cceos.ihep.ac.cn:1094//eos/ihep/' + T2Dir + ' '+ T3Dir #not working 
    # command = 'gfal-copy -r -t 99999 root://cceos.ihep.ac.cn:1094//eos/ihep/' + T2Dir + ' '+ T3Dir ###!!!gfal-copy too slow, need to think of other ways
    # uf.runCommand(command)
    # print('copy done \n\n')
    
# def deleteT2Dir(T2Dir, exceptDir, ifDryRun=True):
#     subDirs = getDirList(T2Dir)
#     print('subDirs: ', subDirs)
#     for iDir in subDirs:
#         if iDir in exceptDir:
#             print('skip ', iDir)
#             continue
#         else:
#             print('delete ', iDir)
#             # command = 'gfal-rm -r root://cceos.ihep.ac.cn:1094//eos/ihep/' + T2Dir +'mc/'+ iDir
#             command = 'gfal-rm -r {} {}'
#             uf.runCommand(command, ifDryRun)
def deleteT2Dir(T2Dir, ifDryRun=True):
    command = 'gfal-rm -r {}{}'.format(T2DirPre, T2Dir)
    uf.runCommand(command, ifDryRun)
    
def getDirList(T2Dir):
    command = 'gfal-ls {}{}'.format(T2DirPre, T2Dir)
    sub = subprocess.run(command, shell=True, stdout=subprocess.PIPE)
    subDirs = sub.stdout.decode('utf-8').split('\n')
    #delete empty string
    subDirs = [x for x in subDirs if x]
    return subDirs
    
    
   
if __name__=='__main__':
    main() 