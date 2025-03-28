import os
import subprocess

import usefulFunc as uf
#!For jobs of energy scale variaion, make the outut version the same of the nominal one

def main(
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/', #!!V13
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly_TESdm11Down/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly_TESdm11Down/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinC_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinA_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinC_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_tauFMorph_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorph_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorphBugFix_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/',
    # channel = '1tau1l',
    channel = '1tau0l',
    # channel = '1tau2l',
    # version = 'v0BDT1tau2l', 
    # version = 'v0BDT1tau2lNewCR', 
    # version = 'v0BDT1tau2lFakeTau', #v0_v94 replace with new MV
    # version = 'v0BDT1tau1l',
    # version = 'v0BDT1tau1lFakeTau',
    # version = 'v0BDT1tau0l',
    # version = 'v0BDT1tau0lFakeTauPtMorphed',
    # version = 'v0BDT1tau0lFakeTau',
    # version = 'v0DataMC_sys',
    # version = 'v0DataMC',
    # version = 'v1DataMC_noHLTSF',
    # version = 'v1dataMC_fakeTauMC',
    # version = 'v1dataMC_fakeTauDataDriven',
    # version = 'v1dataMC_fakeTauDataDriven_fakeTauScaled',
    # version = 'v0FRMeasure',
    # version = 'v2FRMeasureCheckMC',
    version = 'v2FRMeasureCheckMC_v2',
    exe = './apps/run_WH_forDataMC.out',
    # exe = './apps/run_treeAnalyzer.out' ,
    justMC = False
):
    
    
       
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
            # subAllProcess.write('hep_sub -os CentOS7 -mem 6000 '+ iJobFile + ' -o ' + logFile + ' -e ' + errFile +'\n' )
            subAllProcess.write('hep_sub -os CentOS7  '+ iJobFile + ' -o ' + logFile + ' -e ' + errFile +'\n' )


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
