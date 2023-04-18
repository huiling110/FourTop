import os
import subprocess

import usefulFunc as uf

# from pathlib import Path


# import sys


#???make all job subscrison more modulized
def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v5updateHLTSF_v52noHLTButPreSelection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v5updateHLTSF_v52noHLTButPreSelection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baslineNoHLT_v54noHLTButPre/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3HLTBaseline_v54noHLTButPre/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v55ojectRemovalwithTight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v54noHLTButPreMetFixed/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v55ojectRemovalwithTightNoHLT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2baslineNoHLT_v56NoHLTButPre/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3HLTWeightUpdatedBugFixed_v56NoHLTButPre/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2baslineNoHLTBugFixed_v56NoHLTButPre/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v6baseline_v56NoHLTButPre/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v57ovelapWithTausF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v57ovelapWithTausF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2baslineNoHLT_v57ovelapWithTausF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baslineNoHLT_v57ovelapWithTausF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/'

    # version = 'v0FR_measureVR_1prong'
    # version = 'v0FR_measureVR_1prong_Add'
    # version = 'v0FR_measureVR_3prong'
    # version = 'v1FR_application'
   
    # version = 'v0_HLTSFMeasure'
    version = 'v1_btagRMeasure'

    # version = 'v7_btagCorrection'
    # version = 'v7_btagCorrectionWith1tau0L'
    # version = 'v8_noBtagCorrection'
    # version = 'v0_basicCorrection'
    # version = 'v0_triggerSFNewRange'
    # version = 'v1basicWeight'
    # version = 'v2HLTSFWeight'
    # version ='v3btagShapeWeight'
    # version = 'v6allCorrectionButBtag'
    # version = 'v7btagShapeRWeight'
    # version = 'v8btagRMeasureWith1tau0l'
    
    #
    # version = 'v0btagRCal'
    
    #1tau1l
    # version = 'v1pileupWeight'
    # version = 'v2HLTweight'
    
    
    justMC = False
    # justMC = True
    isTest = 0
    print( inputDir, ' ', version )





    Jobsubmitpath = os.path.dirname( os.path.abspath(__file__) ) +'/'
    print( Jobsubmitpath)
    subAllProcess = open( Jobsubmitpath+'subAllProcess.sh', 'w') 
    #important to add the full path so that it can be ran in any folder
    subAllProcess.write('#!/bin/bash\n')
    subAllProcess.write('cd '+ Jobsubmitpath +'\n')
    inputDirDic={}
    inputDirDic['mc'] = inputDir + 'mc/'
    if not justMC:
        inputDirDic['data'] = inputDir + 'data/'

    for i in inputDirDic.keys():
        makeJobsforDir( inputDirDic[i], version, isTest, subAllProcess, Jobsubmitpath )
    subAllProcess.close()

    uf.sumbitJobs(  Jobsubmitpath+'subAllProcess.sh')



def makeJobsforDir( inputDir, version, isTest, subAllProcess, Jobsubmitpath ):

    # jobDir = 'jobSH/'
    jobDir = Jobsubmitpath +'jobSH/'
    outputDir = inputDir + 'variableHists_' + version +'/'
    if not os.path.exists( jobDir ):
        os.mkdir( jobDir )
    if not os.path.exists( outputDir ): os.mkdir( outputDir)

    if not os.path.exists(outputDir +"/log/" ):
        os.mkdir( outputDir  +"/log/")
    for iFile in os.listdir( inputDir ):
        if '.root' in iFile:
            iProcess = iFile.split('.root')[0]
            print(iProcess)
            # iJobFile = jobDir + iProcess +'.sh' 
            iJobFile = jobDir + 'WH_'+iProcess +'.sh' 
            makeIjob( iJobFile, iProcess, isTest, inputDir, version, Jobsubmitpath )  

            logFile = outputDir +   "log/" + iProcess + ".log"
            errFile = outputDir +  "log/" + iProcess +".err"
            subAllProcess.write('hep_sub '+ iJobFile + ' -o ' + logFile + ' -e ' + errFile +'\n' )

    subprocess.run('chmod 777 ' + jobDir +'*sh',  shell=True)
    subprocess.run('chmod 777 ' + Jobsubmitpath+ 'subAllProcess.sh', shell=True)





def makeIjob( shFile, iProcess, isTest, inputDir, version, Jobsubmitpath ):
    subFile = open( shFile, "w" )
    subFile.write('#!/bin/bash\n')
    subFile.write('cd '+ Jobsubmitpath + '\n' )
    subFile.write( 'root -q -b \'run_writeHist.C( \"{}\", \"{}\", \"{}\", {} )\' '.format( inputDir, iProcess, version, isTest ) )
    print( 'done writing: ', shFile)


if __name__=='__main__':
    main()
