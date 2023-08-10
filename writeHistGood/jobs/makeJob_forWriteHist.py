import os
import subprocess

import usefulFunc as uf


def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v57ovelapWithTausF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2baslineNoHLT_v57ovelapWithTausF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baslineNoHLT_v57ovelapWithTausF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baselineBtagRUpdated_v57ovelapWithTausF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4baselineBtagRUpdated_v57ovelapWithTausF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022/v0NewMV_v0Testing/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022/v0NewMV_v1newCrab/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewMV_v59newOScode/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightAdded_v59newOScode/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2btagShapeWeightCorrected_v60fixeJetBtagBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3btagWPWeightGood_v60fixeJetBtagBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v5newBtagEff_v60fixeJetBtagBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v6updatedBtagR_v60fixeJetBtagBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v8tau1elCut_v60fixeJetBtagBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2eraBugFixed_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3btagWeightGood_v61fixesLepRemovalBug/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/'

    # version = 'v0FR_measureVR_1prong'
    # version = 'v0FR_measureVR_3prong'
    # version = 'v1FR_application'
   
    # version = 'v0_HLTSFMeasure'
    # version = 'v1_btagRMeasure'
    # version = 'v1_btagEffMeasure'
    # version = 'v2_btagEffBugFixed'
    # version = 'v0_dataMCBeforeBtagWP'
    # version = 'v1_dataMCafterBtagWP'
    # version = 'v2AllButBtagWP'
    # version ='v3btagEffNewRegion'
    # version = 'v4newBtagEff'
    # version = 'v5OldBtagR'
    # version = 'v6forBtagRMeasure'
    # version = 'v7newBtagRApp'

    # version = 'v2_btagCorrection'
    # version = 'v3NoHLTBTagCorrection'
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
    # version = 'v0btagEff'
    # version = 'v1btagRCal'
    # version = 'v2btagWPCorrection'
    # version = 'v3basicWeight'
    
    
    #1tau1l
    # version = 'v1pileupWeight'
    # version = 'v2traingWithBtag'
    # version = 'v3withBjetT'
    # version = 'v0trainingWithBtagShape'
    version = 'v1traingWithBtagWP'
    channel = 0
    
    #
    # version = 'v41tau0lGenTauSys'
    # channel = 1 
    
    #run3
    # version = 'v0allRegions'
    # version = 'v1dataMC'
    
   
    justMC = False
    # justMC = True
    isTest = 0
    print( inputDir, ' ', version )





    Jobsubmitpath = os.path.dirname( os.path.abspath(__file__) ) +'/'
    print('JobsubmitPath: ' ,Jobsubmitpath)
    subAllProcess = open( Jobsubmitpath+'subAllProcess.sh', 'w') 
    #important to add the full path so that it can be ran in any folder
    subAllProcess.write('#!/bin/bash\n')
    # subAllProcess.write('cd '+ Jobsubmitpath +'\n')
    inputDirDic={}
    inputDirDic['mc'] = inputDir + 'mc/'
    if not justMC:
        inputDirDic['data'] = inputDir + 'data/'

    for i in inputDirDic.keys():
        # makeJobsforDir( inputDirDic[i], version, channel, isTest, subAllProcess, Jobsubmitpath )
        makeJobsforDir( inputDirDic[i], version,  isTest, subAllProcess, Jobsubmitpath, channel )
    subAllProcess.close()

    uf.sumbitJobs(  Jobsubmitpath+'subAllProcess.sh')



def makeJobsforDir( inputDir, version, isTest, subAllProcess, Jobsubmitpath , channel):
    jobDir = Jobsubmitpath +'jobSH/'
    outputDir = inputDir + 'variableHists_' + version +'/'
    logDir = outputDir+'log/'
    uf.checkMakeDir(jobDir)
    uf.checkMakeDir(outputDir)
    uf.checkMakeDir(logDir)
    
    exeDir = Jobsubmitpath.rsplit('/', 2)[0]+'/apps/'

    for iFile in os.listdir( inputDir ):
        if '.root' in iFile:
            iProcess = iFile.split('.root')[0]
            print(iProcess)
            iJobFile = jobDir + 'WH_'+iProcess +'.sh' 
            # run = './run_WH_forDataMC.out {} {} {} {}'.format(inputDir, iProcess, version, isTest)
            run = './run_treeAnalyzer.out {} {} {} {} {}'.format(inputDir, iProcess, version, channel, isTest)
            makeIjob( iJobFile,  Jobsubmitpath, run ,exeDir)  

            logFile = logDir + iProcess + ".log"
            errFile = logDir + iProcess +".err"
            subAllProcess.write('hep_sub '+ iJobFile + ' -o ' + logFile + ' -e ' + errFile +'\n' )

    subprocess.run('chmod 777 ' + jobDir +'*sh',  shell=True)
    subprocess.run('chmod 777 ' + Jobsubmitpath+ 'subAllProcess.sh', shell=True)





def makeIjob( shFile, Jobsubmitpath, run, exeDir ):
    subFile = open( shFile, "w" )
    subFile.write('#!/bin/bash\n')
    # subFile.write('cd '+ Jobsubmitpath + '\n' )
    subFile.write('cd '+ exeDir + '\n' )
    # run = './run_treeAnalyzer.out {} {} {} {} {}'.format(inputDir, iProcess, version, channel, isTest
    subFile.write(run) 
    print( 'done writing: ', shFile)


if __name__=='__main__':
    main()
