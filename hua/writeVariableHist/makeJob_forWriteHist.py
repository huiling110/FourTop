import os
import sys
import subprocess

#???make all job subscrison more modulized


# inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v16_HLTselection/mc/'
# inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v16_HLTselection/data/'
# inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v17NoSelection/mc/'
# inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v17NoSelection/data/'
# inputDir = '/scratchfs/cms/huahuil/forMVA/2016postVFP/v4ClearedSomeMemoryUse_v17NoSelection/mc/'
# inputDir = '/scratchfs/cms/huahuil/forMVA/2016postVFP/v4ClearedSomeMemoryUse_v17NoSelection/data/'
# inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baseline_v18HLTSelection/mc/'

Jobsubmitpath = '/workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/src/FourTop/hua/writeVariableHist/' 
def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v18HLTSelection/'
    version = "v2SwitchedCRVR"
    justMC = False
    isTest = 0




    subAllProcess = open( 'subAllProcess.sh', 'w')
    subAllProcess.write('#!/bin/bash\n')
    subAllProcess.write('cd '+ Jobsubmitpath +'\n')
    inputDirDic={}
    inputDirDic['mc'] = inputDir + 'mc/'
    if not justMC:
        inputDirDic['data'] = inputDir + 'data/'

    for i in inputDirDic.keys():
        makeJobsforDir( inputDirDic[i], version, isTest, subAllProcess )




def makeJobsforDir( inputDir, version, isTest, subAllProcess ):

    jobDir = 'jobSH/'
    outputDir = inputDir + 'variableHists_' + version +'/'
    if not os.path.exists( jobDir ):
        os.mkdir( jobDir )
    if not os.path.exists( outputDir ): os.mkdir( outputDir)

    # subAllProcess = open( 'subAllProcess.sh', 'w')
    # subAllProcess.write('#!/bin/bash\n')
    # subAllProcess.write('cd '+ Jobsubmitpath +'\n')

    if not os.path.exists(outputDir +"/log/" ):
        os.mkdir( outputDir  +"/log/")
    for iFile in os.listdir( inputDir ):
        if '.root' in iFile:
            iProcess = iFile.split('.root')[0]
            print(iProcess)
            iJobFile = jobDir + iProcess +'.sh' 
            makeIjob( iJobFile, iProcess, isTest, inputDir, version )  

            logFile = outputDir +   "log/" + iProcess + ".log"
            errFile = outputDir +  "log/" + iProcess +".err"
            subAllProcess.write('hep_sub '+ iJobFile + ' -o ' + logFile + ' -e ' + errFile +'\n' )

    subprocess.run('chmod 777 ' + Jobsubmitpath + jobDir +'*sh',  shell=True)
    subprocess.run('chmod 777 ' + Jobsubmitpath + 'subAllProcess.sh', shell=True)





def makeIjob( shFile, iProcess, isTest, inputDir, version ):
    subFile = open( shFile, "w" )
    subFile.write('#!/bin/bash\n')
    subFile.write('cd '+ Jobsubmitpath + '\n' )
    subFile.write( 'root -q -b \'run_writeHist.C( \"{}\", \"{}\", \"{}\", {} )\' '.format( inputDir, iProcess, version, isTest ) )
    print( 'done writing: ', shFile)


if __name__=='__main__':
    main()