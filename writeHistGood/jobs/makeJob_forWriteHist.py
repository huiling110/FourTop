import os
import subprocess

import usefulFunc as uf

def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v79HadroPresel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHardro_FRweightSys_v79HadroPresel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v79forHLT/'#!HLT
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v79forHLT/'#!HLT
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHardroHLTSF_v79HadroPresel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHardroHLTSF_v79HadroPresel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHardro_FRweightSys_v79HadroPresel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHardro_FRweightSys_v79HadroPresel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v80addTauJetVar/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v80addTauJetVar/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v80addTauJetVar/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v81addSysSum/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v82for1tau2l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baseline1tau2l_noTauCut_v82for1tau2l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baseline1tau2l_noLepCut_v83for1tau2lEleEtaCut/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v84fakeLeptonUpdate/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v2_v84fakeLeptonUpdateV2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2lNotLepCut_v84Pre1tau2lNoLepCut/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v84Pre1tau2lLepF2/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v84Pre1tau2lLepF2/'
    

    #!fakerate
    # version = 'v0FR_measure1prong'
    # version = 'v0FR_measure3prong'
    # version = 'v1FR_application'
       
    #b-tag measurement 
    # version = 'v1_btagRMeasure'
    # version = 'v0_btagEffMeasure'
    # version = 'v0_btagEffMeasureT'
    
    #HLT 
    # version = 'v0HLTMeasure'
    # version = 'v0HLTMeasureBinB'
   
    #dataMC
    # version = 'v0dataMC_allCorrection'
    # version = 'v1dataMC_allbutHLT'
    version = 'v1dataMC_allbutHLTFakeLepton'
    # version = 'v1dataMC_allbutHLTFakeLeptonNoLepCut'
    # version = 'v2dataMC_allbutHLT'
    # version = 'v0dataMC_genWeight'
    # version = 'v1dataMC_allCorrectionFakeTau'
    
        
    #1tau1l
    # channel = '1tau1l'
    # version = 'v0Basictraining1tau1l_VLL'
    # version = 'v0Basictraining1tau1l_VLLm800'
    # version = 'v0Basictraining1tau1l_VLLm700'
    # version = 'v0Basictraining1tau1l_VLLm700_DifBin2'
    # version = 'v0BDT1tau1l'
    # version = 'v0BDT1tau1l_binC'
    # version = 'v1BDT1tau1l_evenBin'
    # version = 'v2BDT1tau1l_binD'
    # version = 'v2BDT1tau1l_binE'
    # version = 'v2BDT1tau1l_binE2'
    # version = 'v0trainingWithBtagShape' #for btagWP or shape
    
    #1tau0l systematic
    # channel = '1tau0l'
    # version = 'v0BDT1tau0l'
    # version = 'v0BDT1tau0lBinB'
    # version = 'v1BDTtauFJetVar2017train'
    # version = 'v2BDT25inputs'
    # version = 'v2BDT25inputsWith2018train'
    
    channel = '1tau2l'
    # version = 'v0BDT1tau2l'
    # version = 'v1BDT1tau2lEvenBin'
    # version = 'v1BDT1tau2lBinA'
    # version = 'v1BDT1tau2lBinB'
    # version = 'v1BDT1tau2lBinA'
   
    # exe = './run_WH_forDataMC.out'
    # exe = './run_treeAnalyzer.out' 
    
   
    justMC = False
    # justMC = True
    isTest = 0
    print( inputDir, ' ', version )


    Jobsubmitpath = os.path.dirname( os.path.abspath(__file__) ) +'/'
    print('JobsubmitPath: ' ,Jobsubmitpath)
    subAllProcess = open( Jobsubmitpath+'subAllProcess.sh', 'w') 
    #important to add the full path so that it can be ran in any folder
    subAllProcess.write('#!/bin/bash\n')
    inputDirDic={}
    inputDirDic['mc'] = inputDir + 'mc/'
    if not justMC:
        inputDirDic['data'] = inputDir + 'data/'

    for i in inputDirDic.keys():
        makeJobsforDir( inputDirDic[i], version,  isTest, subAllProcess, Jobsubmitpath, channel )
        # makeJobsforDir( inputDirDic[i], version,  isTest, subAllProcess, Jobsubmitpath, exe, channel )
    subAllProcess.close()

    uf.sumbitJobs(  Jobsubmitpath+'subAllProcess.sh')



def makeJobsforDir( inputDir, version, isTest, subAllProcess, Jobsubmitpath , channel):
# def makeJobsforDir( inputDir, version, isTest, subAllProcess, Jobsubmitpath , exe='', channel= '1tau0l'):
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
            run = './run_WH_forDataMC.out {} {} {} {}'.format(inputDir, iProcess, version, isTest)
            # run = './run_treeAnalyzer.out {} {} {} {} {}'.format(inputDir, iProcess, version, channel, isTest)
            makeIjob( iJobFile,  Jobsubmitpath, run ,exeDir)  

            logFile = logDir + iProcess + ".log"
            errFile = logDir + iProcess +".err"
            # subAllProcess.write('hep_sub '+ iJobFile + ' -o ' + logFile + ' -e ' + errFile +'\n' )
            subAllProcess.write('hep_sub -os CentOS7 '+ iJobFile + ' -o ' + logFile + ' -e ' + errFile +'\n' )

    subprocess.run('chmod 777 ' + jobDir +'*sh',  shell=True)
    subprocess.run('chmod 777 ' + Jobsubmitpath+ 'subAllProcess.sh', shell=True)





def makeIjob( shFile, Jobsubmitpath, run, exeDir ):
    subFile = open( shFile, "w" )
    subFile.write('#!/bin/bash\n')
    subFile.write('cd '+ exeDir + '\n' )
    subFile.write(run) 
    print( 'done writing: ', shFile)


if __name__=='__main__':
    main()
