import os
import sys
import subprocess

# inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baselineSelection_fromV15/'
inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v16_HLTselection/mc/'
# inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v16_HLTselection/data/'
# outputDir = inputDir + 'variableHists_v0basicWeight/
outputDir = inputDir + 'variableHists_v2noMCweighting/'




jobDir = 'jobSH/'
Jobsubmitpath = '/workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/src/FourTop/hua/writeVariableHist/' 
# outputDir = inputDir + 'variableHists/'

def main():

    if not os.path.exists( jobDir ):
        os.mkdir( jobDir )
    if not os.path.exists( outputDir ): os.mkdir( outputDir)

    subAllProcess = open( 'subAllProcess.sh', 'w')
    subAllProcess.write('#!/bin/bash\n')
    subAllProcess.write('cd '+ Jobsubmitpath +'\n')

    for iFile in os.listdir( inputDir ):
        if '.root' in iFile:
            iProcess = iFile.split('.root')[0]
            print(iProcess)
            iJobFile = jobDir + iProcess +'.sh' 
            makeIjob( iJobFile, iProcess )  

        if not os.path.exists(outputDir +"/log/" ):
            os.mkdir( outputDir  +"/log/")
        logFile = outputDir +   "log/" + iProcess + ".log"
        errFile = outputDir +  "log/" + iProcess +".err"
        subAllProcess.write('hep_sub '+ iJobFile + ' -o ' + logFile + ' -e ' + errFile +'\n' )

    subprocess.run('chmod 777 ' + Jobsubmitpath + jobDir +'*sh',  shell=True)
    subprocess.run('chmod 777 ' + Jobsubmitpath + 'subAllProcess.sh', shell=True)





def makeIjob( shFile, iProcess ):
    subFile = open( shFile, "w" )
    subFile.write('#!/bin/bash\n')
    subFile.write('cd '+ Jobsubmitpath + '\n' )
    subFile.write( 'root -q -b \'run_writeHist.C( \"{}\", \"{}\" )\' '.format( inputDir, iProcess ) )
    print( 'done writing: ', shFile)


if __name__=='__main__':
    main()