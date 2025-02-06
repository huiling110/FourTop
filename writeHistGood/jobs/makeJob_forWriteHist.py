import os
import subprocess

import usefulFunc as uf
#!For jobs of energy scale variaion, make the outut version the same of the nominal one

def main(
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadroV2_v88PSWeightFixedHadroPre/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadroV2_v88PSWeightFixedHadroPre/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadroV2_v88PSWeightFixedHadroPre/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadroV2_v88PSWeightFixedHadroPre/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v90MuonESHadroPre/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v90MuonESHadroPre_JERUp/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre_JERDown/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre_METDown/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre_EleScaleDown/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre_TESdm11Down/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v91TESAddedHadroPre/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v91TESAddedHadroPre_EleScaleDown/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v91TESAddedHadroPre_METDown/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v91TESAddedHadroPre_JERDown/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v91TESAddedHadroPre_TESdm11Down/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v93HadroPreJetVetoPileupID/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v93HadroPreJetVetoPileupID/',
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly_JERDown/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly_EleScaleDown/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly_METDown/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly_TESdm11Down/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/',
    # channel = '1tau1l',
    # channel = '1tau0l',
    # channel = '1tau2l',
    # version = 'v0BDT1tau2l'
    # version = 'v0BDT1tau1l'
    # version = 'v0BDT1tau0l'
    #dataMC 
    version = 'v0DataMC_sys'
):
    
    exe = './apps/run_WH_forDataMC.out'
    # exe = './apps/run_treeAnalyzer.out' 
    
    #!fakerate
    # version = 'v0FRMeasure'
       
    #b-tag measurement 
    # version = 'v1_btagRMeasure'
    # version = 'v0_btagEffMeasure'
    # version = 'v0_btagEffMeasureT'
    
    #HLT 
    # version = 'v0HLTMeasure'
   
    #dataMC
    # version = 'v0dataMC_allCorrection'
    # version = 'v1dataMC_allCorrectionNotFakeTau'
    # version = 'v0dataMC_allCorrectionFakeLepton'
    # version = 'v1dataMC_allbutHLT'
    # version = 'v1dataMC_allbutHLTFakeLepton'
    # version = 'v2dataMC_allbutHLT'
    # version = 'v0dataMC_genWeight'
    
        
    #1tau1l
    # channel = '1tau1l'
    # version = 'v1BDT1tau1lEvenBin'
    
    #1tau0l systematic
    # channel = '1tau0l'
    # version = 'v0BDT1tau0l'
    # version = 'v1BDT1tau0lEvenBin'
    
    # channel = '1tau2l'
    # version = 'v0BDT1tau2l'
    # version = 'v0BDT1tau2l_newMCSample'
    # version = 'v1BDT1tau2lEvenBin'
   
    
   
    justMC = False
    # justMC = True
    isTest = 0
    print( inputDir, ' ', version )


    inputDirDic={}
    inputDirDic['mc'] = inputDir + 'mc/'
    if not justMC:
        inputDirDic['data'] = inputDir + 'data/'
        
    Jobsubmitpath = inputDirDic['mc'] + 'variableHists_' + version + '/' 
    uf.checkMakeDir(Jobsubmitpath)
    print('JobsubmitPath: ' ,Jobsubmitpath)
    subAllProcess = open( Jobsubmitpath+'subAllProcess.sh', 'w') 
    #important to add the full path so that it can be ran in any folder
    subAllProcess.write('#!/bin/bash\n')

    for i in inputDirDic.keys():
        makeJobsforDir( inputDirDic[i], version,  isTest, subAllProcess, Jobsubmitpath, channel , exe)
        # makeJobsforDir( inputDirDic[i], version,  isTest, subAllProcess, Jobsubmitpath, exe, channel )
    subAllProcess.close()

    uf.sumbitJobs(  Jobsubmitpath+'subAllProcess.sh')



def makeJobsforDir( inputDir, version, isTest, subAllProcess, Jobsubmitpath , channel, exe='./apps/run_WH_forDataMC.out'):
    jobDir = Jobsubmitpath +'jobSH/'
    uf.checkMakeDir(jobDir) 
    outputDir = inputDir + 'variableHists_' + version +'/'
    logDir = outputDir+'log/'
    uf.checkMakeDir(jobDir)
    uf.checkMakeDir(outputDir)
    uf.checkMakeDir(logDir)
    
    # exeDir = Jobsubmitpath.rsplit('/', 2)[0]+'/apps/'
    # exeDir = Jobsubmitpath.rsplit('/', 2)[0]+'/'
    exeDir = (os.path.dirname( os.path.abspath(__file__) ) +'/').rsplit('/', 2)[0] + '/'
    

    for iFile in os.listdir( inputDir ):
        if '.root' in iFile:
            iProcess = iFile.split('.root')[0]
            print(iProcess)
            iJobFile = jobDir + 'WH_'+iProcess +'.sh' 
            run = f"{exe} {inputDir} {iProcess} {channel} {version} {isTest}"
            makeIjob( iJobFile,  Jobsubmitpath, run ,exeDir)  

            logFile = logDir + iProcess + ".log"
            errFile = logDir + iProcess +".err"
            subAllProcess.write('hep_sub -os CentOS7 -mem 6000 '+ iJobFile + ' -o ' + logFile + ' -e ' + errFile +'\n' )


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
