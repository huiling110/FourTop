import os
import subprocess

import usefulFunc as uf


def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v8tau1elCut_v60fixeJetBtagBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2eraBugFixed_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3btagWeightGood_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1btagWPandRUpdated_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v0preSel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v0preSel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022/v0baseline_v0preSel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4forBDT1tau1lCut_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_addTauGenNum_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_addTauGenNum_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_addTauGenNum_v61fixesLepRemovalBug/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v62addTauJetVars/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v62addTauJetVars/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v62addTauJetVars/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSF_v64PreAndHLTSel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFBinA_v64PreAndHLTSel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFBinD_v64PreAndHLTSel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFBinE_v64PreAndHLTSel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT500BinE_v64PreAndHLTSel/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/' #final version
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v64noHLTSel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewHLTSFHT550BinF_v64PreAndHLTSel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_JERUp/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_JERDown/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_JESUp/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_JESDown/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_TESUp/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_TESDown/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64noHLTSel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64PreAndHLTSel/'

    #!fakerate
    # version = 'v0FR_measureVR_1prong'
    # version = 'v0FR_measureVR_3prong'
    # version = 'v1FR_application'
    # version = 'v1FR_application_correctWeight'
    # version = 'v1FR_application_bjets2_bShapeWeight'
    # version = 'v1FR_application_bjets3_bShapeWeight'
    # version = 'v1FR_application_correctWeight_bjets3'
    # version = 'v1FR_application_MCBtagShape'
    # version = 'v1FR_application_bjets3_bWPWeight'
    # version = 'v1FR_application_bjets2_bWPWeight'
    # version = 'v1FR_application_bjets2_bShapeWeight'
   
    # version = 'v0_HLTSFMeasure'
    # version = 'v0_HLTSFMeasure_6thJet45'
    # version = 'v0_HLTSFMeasure_6thJet40Mu35'
    # version = 'v0_HLTSFMeasure_6thJet40HT550'
    # version = 'v0_HLTSFMeasure_6thJet40HT600'
    # version = 'v0_HLTSFMeasure_6thJet45_binningA'
    # version = 'v0_HLTSFMeasure_6thJet45_binningB'
    # version = 'v0_HLTSFMeasure_6thJet40HT600BinA'
    # version = 'v0_HLTSFMeasure_6thJet40HT600BinB'
    # version = 'v0_HLTSFMeasure_6thJet40HT600BinC'
    # version = 'v0_HLTSFMeasure_6thJet40HT600BinD'
    # version = 'v0_HLTSFMeasure_6thJet40HT600BinE'
    # version = 'v0_HLTSFMeasure_6thJet40HT550BinE'
    # version = 'v0_HLTSFMeasure_6thJet40HT550BinF'
    
    
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
    # version = 'v0btagEff'
    # version = 'v1btagRCal'
    # version = 'v2btagWPCorrection'
    
    # version = 'v0dataMC_btagWPsf'
    # version = 'v0dataMC_jets6pt45'
    # version = 'v0dataMC_jets6pt40'
    # version = 'v0dataMC_jets6pt42'
    # version = 'v0dataMC_HT600'
    # version = 'v1dataMC_noHLTSF'
    # version = 'v2dataMC_HT600HLTSF'
    # version = 'v3dataMC_HT600HLTSFBinA'
    # version = 'v3dataMC_HT600HLTSFBinB'
    # version = 'v3dataMC_HT600HLTSFBinD'
    # version = 'v3dataMC_HT600HLTSFBinE'
    # version = 'v3dataMC_HT550HLTSFBinF'
    # channel = 0
    
        
    #1tau1l
    channel = '1tau1l'
    # version = 'v0BasicSystematic'
    version = 'v0BasicSystematic_20bins'
    # version = 'v1JERup'
    # version = 'v1JERdown'
    # version = 'v1JESDown'
    # version = 'v1TESDown'
    # version = 'v1JESDown'
    # version = 'v2traingWithBtag'
    # version = 'v3withBjetT'
    # version = 'v0trainingWithBtagShape' #for btagWP or shape
    # version = 'v1traingWithBtagWP' e
    # version = 'v4forBtagWPShape_WP'#for btagWP or shape
    # version = 'v5forBtagWPShape_shape'#for btagWP or shape
    
    #1tau0l systematic
    # channel = 1
    # version = 'v0systematic1tau0l_bScore' 
    # version = 'v0systematic1tau0lBjet3_bScore' 
    # version = 'v0systematic1tau0lBjet3_bHT' 
    # version = 'v0systematic1tau0lBjet3_bMass' 
    # version = 'v0systematic1tau0l_bMass' 
    
    #run3
    # version = 'v0allRegions'
    # version = 'v1dataMC'
    # version = 'v2SR1tau1l'
    
   
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
    subFile.write('cd '+ exeDir + '\n' )
    subFile.write(run) 
    print( 'done writing: ', shFile)


if __name__=='__main__':
    main()
