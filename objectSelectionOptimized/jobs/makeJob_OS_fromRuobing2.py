import os
import subprocess
import re
import glob

import ttttGlobleQuantity as gq
import usefulFunc as uf


codePath = os.path.dirname(os.path.abspath(__file__)) + '/'
# jobVersionName = 'v90MuonESHadroPre_JESPt22/'
# jobVersionName = 'v90MuonESHadroPre_JERUp/'
# jobVersionName = 'v90MuonESHadroPre_JERDown/'
# jobVersionName = 'v91TESAddedHadroPre/'
# jobVersionName = 'v91TESAddedHadroPre_TESdm11Down/'
# jobVersionName = 'v91TESAddedHadroPre_EleScaleUp/'
# jobVersionName = 'v91TESAddedHadroPre_EleScaleDown/'
# jobVersionName = 'v91TESAddedHadroPre_JESPt20/'
# jobVersionName = 'v91TESAddedHadroPre_METUp/'
# jobVersionName = 'v91TESAddedHadroPre_JERDown/'
# jobVersionName = 'v92HadroPre_NoJetVetoMap/'
# jobVersionName = 'v93HadroPreJetVetoPileupID/'
# jobVersionName = 'v93HadroPreJetVetoPileupID_JESPt22/'
# jobVersionName = 'v93HadroPreJetVetoPileupID_EleSca
# jobVersionName = 'v93HadroPreJetVetoPileupID_JERDown/'
# jobVersionName = 'v93HadroPreJetVetoPileupID_METDown/'
# jobVersionName = 'v93HadroPreJetVetoPileupID_TESdm0Up/'
# jobVersionName = 'v94HadroPreJetVetoHemOnly/'#3 years submitted
# jobVersionName = 'v94HadroPreJetVetoHemOnly_JESPt22/' # 2018, 2017
# jobVersionName = 'v94HadroPreJetVetoHemOnly_JERUp/'#2018
# jobVersionName = 'v94HadroPreJetVetoHemOnly_EleScaleDown/'#2018, 2017
# jobVersionName = 'v94HadroPreJetVetoHemOnly_METDown/' #2018
# jobVersionName = 'v94HadroPreJetVetoHemOnly_TESdm11Down/'


# jobVersionName = 'v91TESAddedLepPre/'
# jobVersionName = 'v91TESAddedLepPre_JETPt22/'
# jobVersionName = 'v91TESAddedLepPre_JERUp/'
# jobVersionName = 'v91TESAddedLepPre_METDown/'
# jobVersionName = 'v91TESAddedLepPre_TESdm11Down/'
# jobVersionName = 'v91TESAddedLepPre_EleScaleDown/'
# jobVersionName = 'v94LepPreJetVetoHemOnly_JESPt22/' #2018; 2017, 2016
# jobVersionName = 'v94LepPreJetVetoHemOnly_JERDown/'#2018
# jobVersionName = 'v94LepPreJetVetoHemOnly_METDown/' # 3 years submitted
# jobVersionName = 'v94LepPreJetVetoHemOnly_EleScaleDown/'
# jobVersionName = 'v94LepPreJetVetoHemOnly_TESdm0Up/' #dm0 3years down

#!Have to submit one version at one time. It seems job sricpts can not be overwriten
#!same version numbers means no change in algrithm but only in selection
isRuobing = False
#done by Ruobing: submit jobs in bunches for faster job submission; http://afsapply.ihep.ac.cn/cchelp/zh/local-cluster/jobs/HTCondor/
def main(
    # TES = 0 ,#!!!TES = 0, //no correction; 1: up; 2: down; 3: up, decayMode=0; 4: down, decayMode=0; 5: up, decayMode=1; 6: down, decayMode=1; 7: up, decayMode=10; 8: down, decayMode=10; 9: up, decayMode=11; 10: down, decayMode=11
    TES = 0,#!!!TES = 0, //no correction; 1: up; 2: down; 3: up, decayMode=0; 4: down, decayMode=0; 5: up, decayMode=1; 6: down, decayMode=1; 7: up, decayMode=10; 8: down, decayMode=10; 9: up, decayMode=11; 10: down, decayMode=11
    eleScale = 0, #!!! 0: nominal; 1: up; 2: down
    JESSys = 0 ,#!!! nominal: 0;
    JERSys = 0, #!!! 0: no correction; 1: up; 2: down
    METSys = 2, #!!! nominal: 0; 1: up; 2: down
    # if1tau2l = 0 #!!!True 
    if1tau2l = 1, #!!!True 
    era = '2016',
    # era = '2016APV',
    # era = '2017',
    # era = '2018',
    # jobVersionNamePre = 'v94LepPreJetVetoHemOnly'#3 years submitted
    jobVersionNamePre = 'v94LepPreJetVetoHemOnlyV2'#3 years submitted
    
):
    
    jobVersionName = getJobVersionName(jobVersionNamePre, TES, eleScale, JESSys, JERSys, METSys)
    
    ifSys = any(substring in jobVersionName for substring in ['Up', 'Down', 'JES'])
    print('ifSys=', ifSys)
    if if1tau2l:
        sumProToSkip = ['jetHT', 'BTagCSV', 'qcd', 'ttExtra'] #1tau2l #! need ttExtra for BDT training
        if ifSys:
            toadd = ['singleMu', 'singleE','doubleMu', 'muonEG', 'eGamma', 'doubleEG']
            sumProToSkip = sumProToSkip + toadd        
    else:
        sumProToSkip = ['singleMu', 'singleE','doubleMu', 'muonEG', 'eGamma', 'doubleEG', 'ttExtra', 'Minor'] #!1tau1l and 1tau0l , 
        if ifSys:
            toadd = ['jetHT', 'BTagCSV', 'qcd']
            sumProToSkip = sumProToSkip + toadd
    print('sumProToSkip=', sumProToSkip)




###########################################
#better not modify anything afer this
    inputDir, outputDir, eraOut = getInputOutDir(jobVersionName, era)

    # jobsDir = codePath + 'jobs_eachYear/'
    jobsDir = outputDir + 'jobs_eachYear/'
    uf.checkMakeDir(jobsDir)
    isRun3 = uf.isRun3(inputDir)
    print( "era: ", era, 'isRun3=', isRun3 )
    print('version: ', jobVersionName)
    
    
    jobScriptsFolder = jobsDir+eraOut+'/'
    if os.path.exists( jobScriptsFolder ):
        subprocess.run('rm -fr '+ jobScriptsFolder , shell=True)
        print('removing old job folder', jobScriptsFolder)
    uf.checkMakeDir(jobScriptsFolder)

    inputDirMC = inputDir + 'mc/'
    makeJobsInDir( inputDirMC, outputDir , jobScriptsFolder, False,   eraOut, isRun3,  sumProToSkip, TES, eleScale, JESSys, JERSys, METSys, if1tau2l)
    # if not onlyMC:
        # for idata in dataList:
    inputDirData = inputDir + 'data/'
    makeJobsInDir( inputDirData, outputDir, jobScriptsFolder, True, eraOut , isRun3, sumProToSkip, TES, eleScale, JESSys, JERSys, METSys, if1tau2l)

    makeSubAllJobs( jobsDir , eraOut)
    subprocess.run(f"nohup python3 /workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/objectSelectionOptimized/jobs/speedOS.py {jobScriptsFolder}/cluster_logs.csv > {jobScriptsFolder}output.log 2>&1 &", shell=True )

    print('done submitting jobs for: ', jobVersionName) 

# def getJobVersionName(jobVersionNamePre, TES, eleScale, JESSys, JERSys, METSys):
#     sysKey = {1: 'Up', 2: 'Down'}
#     if TES ==0 and eleScale==0 and JESSys==0 and JERSys==0 and METSys==0:
#         jobVersionName = f'{jobVersionNamePre}/'
#     elif eleScale==0 and JESSys==0 and JERSys==0 and METSys==0 and (not TES==0): 
# #!!!TES = 0, //no correction; 1: up; 2: down; 3: up, decayMode=0; 4: down, decayMode=0; 5: up, decayMode=1; 6: down, decayMode=1; 7: up, decayMode=10; 8: down, decayMode=10; 9: up, decayMode=11; 10: down, decayMode=11
#         TESkey = {1: 'Up', 2: 'Down', 3: 'dm0Up', 4: 'dm0Down', 5: 'dm1Up', 6: 'dm1Down', 7: 'dm10Up', 8: 'dm10Down', 9: 'dm11Up', 10: 'dm11Down'}
#         jobVersionName = f'{jobVersionNamePre}_TES{TESkey[TES]}/'
#     elif TES==0 and JESSys==0 and JERSys==0 and METSys==0 and (not eleScale==0):
#         jobVersionName = f'{jobVersionNamePre}_EleScale{sysKey[eleScale]}/'
#     elif TES==0 and eleScale==0 and JERSys==0 and METSys==0 and (not JESSys==0):
#         jobVersionName = f'{jobVersionNamePre}_JESPt22/'
#     elif TES==0 and eleScale==0 and JESSys==0 and (not JERSys==0):
#         jobVersionName = f'{jobVersionNamePre}_JER{sysKey[JERSys]}/'
#     else: #error
#         #assert error of input 
#         print('!!!error in input sys, please check')
    
#     print ('jobVersionName=', jobVersionName) 
#     return jobVersionName


def getJobVersionName(jobVersionNamePre, TES, eleScale, JESSys, JERSys, METSys):
    sysKey = {1: 'Up', 2: 'Down'}
    TESkey = {
        1: 'Up', 2: 'Down', 3: 'dm0Up', 4: 'dm0Down',
        5: 'dm1Up', 6: 'dm1Down', 7: 'dm10Up', 8: 'dm10Down',
        9: 'dm11Up', 10: 'dm11Down'
    }
    
    # Check for multiple non-zero systematics
    non_zero = [p for p in [TES, eleScale, JESSys, JERSys, METSys] if p != 0]
    if len(non_zero) > 1:
        raise ValueError("Only one systematic parameter can be non-zero")
    
    # Validate parameter ranges
    def validate_range(name, value, allowed):
        if value != 0 and value not in allowed:
            raise ValueError(f"{name}={value} is invalid")

    validate_range("TES", TES, TESkey.keys())
    for name, val in [('eleScale', eleScale), ('JESSys', JESSys),
                      ('JERSys', JERSys), ('METSys', METSys)]:
        validate_range(name, val, {0, 1, 2})
    
    # Handle nominal case
    if TES == 0 and eleScale == 0 and JESSys == 0 and JERSys == 0 and METSys == 0:
        jobVersionName = f'{jobVersionNamePre}/'
    
    # Handle TES systematic
    elif TES != 0:
        jobVersionName = f'{jobVersionNamePre}_TES{TESkey[TES]}/'
    
    # Handle Electron Scale
    elif eleScale != 0:
        jobVersionName = f'{jobVersionNamePre}_EleScale{sysKey[eleScale]}/'
    
    # Handle JES systematic
    elif JESSys != 0:
        jobVersionName = f'{jobVersionNamePre}_JESPt22/'
    
    # Handle JER systematic
    elif JERSys != 0:
        jobVersionName = f'{jobVersionNamePre}_JER{sysKey[JERSys]}/'
    
    # Handle MET systematic
    elif METSys != 0:
        jobVersionName = f'{jobVersionNamePre}_MET{sysKey[METSys]}/'
    
    else:
        raise ValueError("Unexpected parameter configuration")
    
    print('jobVersionName=', jobVersionName)
    return jobVersionName

def getInputOutDir( jobVersionName, era):
    eraDic = {
        '2016':'UL2016_postVFP',
        '2016APV': 'UL2016_preVFP',
        '2017': 'UL2017',
        '2018': 'UL2018',
        '13p6TeV/2022':'Prompt2022',
        '2022_13p6/NanoPost/2022preEE': 'ReReco2022PreEE',
        '2022_13p6/crabNanoPost_2022PostEE/2022postEE': 'Prompt2022postEE',
        '2022_13p6/crabNanoPost_2022postEE_v3': '2022postEE',
        '2022_13p6/crabNanoPost_2022preEE_v3': '2022preEE',
    }
    inputBase = '/publicfs/cms/data/TopQuark/nanoAOD/'
    outputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/'
    if isRuobing:
        outputBase = '/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/'
        
    inputDir = inputBase + era +'/'
    outputDir = outputBase + eraDic[era] + '/' +jobVersionName  
    uf.checkMakeDir( outputDir) 
    return inputDir, outputDir, eraDic[era]
    




def makeSubAllJobs( jobsDir , era):
    subAllFile = jobsDir+"subAllJobs"+era+ ".sh"
    if os.path.exists(subAllFile):
        subprocess.run('rm -fr '+subAllFile , shell=True)

    subAllProcessName = open( subAllFile, 'w')
    subAllProcessName.write( "#!/bin/bash\n")
    subAllProcessName.write( 'cd ' + jobsDir+era + '\n')
    for ijob in os.listdir( jobsDir+era ):
        if '.sh' in ijob:
            subAllProcessName.write( "sh  " + ijob + "\n")
    subAllProcessName.close()
    # print( 'submitting all jobs using: ', subAllFile )
    subprocess.run( 'chmod 777 ' + subAllFile,  shell=True )









# def makeJobsInDir( inputDir, outputDir, jobScriptsFolder, isData, era, isRun3,  sumProToSkip=[]):
def makeJobsInDir( inputDir, outputDir, jobScriptsFolder, isData, era, isRun3, sumProToSkip=[], TES=0, eleScale=0, JESSys=0, JERSys=0, METSys=0, if1tau2l=0):
    allProcesses = os.listdir( inputDir )
    if isData:
        outputDir = outputDir + 'data/'
    else:
        outputDir = outputDir + 'mc/'
    uf.checkMakeDir( outputDir )

    for k in allProcesses:
        print( 'kProcess: ', k )
        if not uf.checkIfInputDic(k, isRun3): continue
        print('input=', inputDir+k)
        
        print(k)
        sample_k = k
        # if  isData:
        #     if dataSet not in k:
        #         print( "omitting: ", k )
        #         continue
        # if ifSkipTTExtra and gq.histoGramPerSample.get(k)=='ttExtra': continue
        
        if gq.histoGramPerSample.get(k) in sumProToSkip:
            print(gq.histoGramPerSample.get(k), ' is in sumProToSkip, skipping')
            continue

        print( 'have made folder neccessary for out put directory' )

        oneProcess =  jobScriptsFolder +  sample_k + ".sh"
        kProcessDir = jobScriptsFolder + sample_k + '/'
        if os.path.exists( kProcessDir ):
            subprocess.run('rm -fr '+ kProcessDir , shell=True)
        subprocess.run('mkdir -p '+ kProcessDir, shell=True )
        if os.path.exists(oneProcess):
            subprocess.run('rm -fr '+ oneProcess,  shell=True )
        sub_oneProcess = open ( oneProcess, 'w')
        sub_oneProcess.write( "cd "+ jobScriptsFolder + sample_k + "/" + "\n" + "\n")
        print( 'job sub script for kProcess is: ', oneProcess )

        sampleDir = inputDir + sample_k +'/'
        koutputDir = outputDir + k + '/'
        kOutDirLog = koutputDir + 'log/'
        uf.checkMakeDir( koutputDir )
        uf.checkMakeDir( kOutDirLog )
        print( 'outputDir for kprocess: ', koutputDir )
        sample_file_path = glob.glob(os.path.join(sampleDir, "*.root"))
        sample_file_name = [os.path.basename(file) for file in sample_file_path]
        _idx_tmp = 0
        for entry in os.listdir( sampleDir):
            if not '.root' in entry: continue
            if os.path.isfile(os.path.join(sampleDir, entry)):
                smallFile = entry.replace( ".root", "")

                iSmallJobName = 'OS_'+ era + sample_k + '_' + f"{_idx_tmp}" + ".sh"
                smallFilejob = jobScriptsFolder +sample_k + "/" + iSmallJobName   
                prepareCshJob( sampleDir, koutputDir, smallFilejob, entry, TES, eleScale, JESSys, JERSys, METSys, if1tau2l)
                _idx_tmp += 1
                
        if len(sample_file_path)!=0:
            iSmallJobName_forSub = 'OS_'+ era + sample_k + '_' + '''"%{ProcId}"''' + ".sh"
            logFile = kOutDirLog + '''_"%{ProcId}"''' + ".log"
            errFile = kOutDirLog + '''_"%{ProcId}"''' + ".err"
            # sub_oneProcess.write( "hep_sub -os CentOS7 -mem 8000 " + iSmallJobName_forSub + " -o " + logFile + " -e " + errFile + f" -n {len(sample_file_path)}" + "\n")#!Memory comsuption is too high, need to be understood
            sub_oneProcess.write( "hep_sub -os CentOS7 " + iSmallJobName_forSub + " -o " + logFile + " -e " + errFile + f" -n {len(sample_file_path)}" + "\n")#!Memory comsuption is too high, need to be understood
            
            #!!!
            # submit_cmd = "hep_sub -os CentOS7 " + kProcessDir + iSmallJobName_forSub + " -o " + logFile + " -e " + errFile + f" -n {len(sample_file_path)}" + "\n"
            submit_cmd = "hep_sub " + kProcessDir + iSmallJobName_forSub + " -o " + logFile + " -e " + errFile + f" -n {len(sample_file_path)}" + "\n"
            result = subprocess.run(submit_cmd, shell=True, capture_output=True, text=True)
            cluster_id = None
            if result.returncode == 0:
                match = re.search(r'submitted to cluster (\d+)', result.stdout)
                if match:
                    cluster_id = match.group(1)
                    print(f"Submitted cluster: {cluster_id}")
                    
                    # 保存 clusterid 和日志路径到文件
                    with open(os.path.join(jobScriptsFolder, 'cluster_logs.csv'), 'a') as f:
                        f.write(f"{cluster_id},{kOutDirLog},{kProcessDir},0\n")
            else:
                print(f"提交失败: {result.stderr}")

        os.popen('chmod 777 '+ jobScriptsFolder + sample_k + "/*sh")
        sub_oneProcess.close()
        print( 'done with kProcess: ', k )
        print( '\n')
            
            
            





# def prepareCshJob( inputDir, koutputDir, shFile, singleFile):
def prepareCshJob( inputDir, koutputDir, shFile, singleFile, TES, eleScale, JESSys, JERSys, METSys, if1tau2l):
    subFile = open( shFile, 'w')
    subFile.write( "#!/bin/bash\n" )
    appDir = codePath.rsplit('/', 2)[0]
    # subFile.write( "cd "+codePath + "\n")
    subFile.write( "cd "+appDir + "\n")
    # command = f'./apps/run_objectSelection.out {inputDir} {singleFile} {koutputDir} {TES} {eleScale} {JESSys} {JERSys} {METSys} 0'
    command = f'./apps/run_objectSelection.out {inputDir} {singleFile} {koutputDir} {TES} {eleScale} {JESSys} {JERSys} {METSys} {if1tau2l} 0'
    subFile.write(command)
    subFile.close()
    # print( 'done writing the iJob for kProcess: ', shFile )



if __name__ == "__main__":
    main()





