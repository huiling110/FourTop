import os
import subprocess
import re
import glob

import ttttGlobleQuantity as gq
import usefulFunc as uf

corr_Uncer_JES_map = {
    "2016preVFP": [
        "Summer19UL16APV_V7_MC_AbsoluteMPFBias_AK4PFchs",
        "Summer19UL16APV_V7_MC_AbsoluteScale_AK4PFchs",
        "Summer19UL16APV_V7_MC_AbsoluteStat_AK4PFchs",
        "Summer19UL16APV_V7_MC_FlavorQCD_AK4PFchs",
        "Summer19UL16APV_V7_MC_Fragmentation_AK4PFchs",
        "Summer19UL16APV_V7_MC_PileUpDataMC_AK4PFchs",
        "Summer19UL16APV_V7_MC_PileUpPtBB_AK4PFchs",
        "Summer19UL16APV_V7_MC_PileUpPtEC1_AK4PFchs",
        "Summer19UL16APV_V7_MC_PileUpPtEC2_AK4PFchs",
        "Summer19UL16APV_V7_MC_PileUpPtHF_AK4PFchs",
        "Summer19UL16APV_V7_MC_PileUpPtRef_AK4PFchs",
        "Summer19UL16APV_V7_MC_RelativeFSR_AK4PFchs",
        "Summer19UL16APV_V7_MC_RelativeJEREC1_AK4PFchs",
        "Summer19UL16APV_V7_MC_RelativeJEREC2_AK4PFchs",
        "Summer19UL16APV_V7_MC_RelativeJERHF_AK4PFchs",
        "Summer19UL16APV_V7_MC_RelativePtBB_AK4PFchs",
        "Summer19UL16APV_V7_MC_RelativePtEC1_AK4PFchs",
        "Summer19UL16APV_V7_MC_RelativePtEC2_AK4PFchs",
        "Summer19UL16APV_V7_MC_RelativePtHF_AK4PFchs",
        "Summer19UL16APV_V7_MC_RelativeBal_AK4PFchs",
        "Summer19UL16APV_V7_MC_RelativeSample_AK4PFchs",
        "Summer19UL16APV_V7_MC_RelativeStatEC_AK4PFchs",
        "Summer19UL16APV_V7_MC_RelativeStatFSR_AK4PFchs",
        "Summer19UL16APV_V7_MC_RelativeStatHF_AK4PFchs",
        "Summer19UL16APV_V7_MC_SinglePionECAL_AK4PFchs",
        "Summer19UL16APV_V7_MC_SinglePionHCAL_AK4PFchs",
        "Summer19UL16APV_V7_MC_TimePtEta_AK4PFchs"
    ],
    "2016postVFP": [
        "Summer19UL16_V7_MC_AbsoluteMPFBias_AK4PFchs",
        "Summer19UL16_V7_MC_AbsoluteScale_AK4PFchs",
        "Summer19UL16_V7_MC_AbsoluteStat_AK4PFchs",
        "Summer19UL16_V7_MC_FlavorQCD_AK4PFchs",
        "Summer19UL16_V7_MC_Fragmentation_AK4PFchs",
        "Summer19UL16_V7_MC_PileUpDataMC_AK4PFchs",
        "Summer19UL16_V7_MC_PileUpPtBB_AK4PFchs",
        "Summer19UL16_V7_MC_PileUpPtEC1_AK4PFchs",
        "Summer19UL16_V7_MC_PileUpPtEC2_AK4PFchs",
        "Summer19UL16_V7_MC_PileUpPtHF_AK4PFchs",
        "Summer19UL16_V7_MC_PileUpPtRef_AK4PFchs",
        "Summer19UL16_V7_MC_RelativeFSR_AK4PFchs",
        "Summer19UL16_V7_MC_RelativeJEREC1_AK4PFchs",
        "Summer19UL16_V7_MC_RelativeJEREC2_AK4PFchs",
        "Summer19UL16_V7_MC_RelativeJERHF_AK4PFchs",
        "Summer19UL16_V7_MC_RelativePtBB_AK4PFchs",
        "Summer19UL16_V7_MC_RelativePtEC1_AK4PFchs",
        "Summer19UL16_V7_MC_RelativePtEC2_AK4PFchs",
        "Summer19UL16_V7_MC_RelativePtHF_AK4PFchs",
        "Summer19UL16_V7_MC_RelativeBal_AK4PFchs",
        "Summer19UL16_V7_MC_RelativeSample_AK4PFchs",
        "Summer19UL16_V7_MC_RelativeStatEC_AK4PFchs",
        "Summer19UL16_V7_MC_RelativeStatFSR_AK4PFchs",
        "Summer19UL16_V7_MC_RelativeStatHF_AK4PFchs",
        "Summer19UL16_V7_MC_SinglePionECAL_AK4PFchs",
        "Summer19UL16_V7_MC_SinglePionHCAL_AK4PFchs",
        "Summer19UL16_V7_MC_TimePtEta_AK4PFchs"
    ],
    "2017": [
        "Summer19UL17_V5_MC_AbsoluteMPFBias_AK4PFchs",
        "Summer19UL17_V5_MC_AbsoluteScale_AK4PFchs",
        "Summer19UL17_V5_MC_AbsoluteStat_AK4PFchs",
        "Summer19UL17_V5_MC_FlavorQCD_AK4PFchs",
        "Summer19UL17_V5_MC_Fragmentation_AK4PFchs",
        "Summer19UL17_V5_MC_PileUpDataMC_AK4PFchs",
        "Summer19UL17_V5_MC_PileUpPtBB_AK4PFchs",
        "Summer19UL17_V5_MC_PileUpPtEC1_AK4PFchs",
        "Summer19UL17_V5_MC_PileUpPtEC2_AK4PFchs",
        "Summer19UL17_V5_MC_PileUpPtHF_AK4PFchs",
        "Summer19UL17_V5_MC_PileUpPtRef_AK4PFchs",
        "Summer19UL17_V5_MC_RelativeFSR_AK4PFchs",
        "Summer19UL17_V5_MC_RelativeJEREC1_AK4PFchs",
        "Summer19UL17_V5_MC_RelativeJEREC2_AK4PFchs",
        "Summer19UL17_V5_MC_RelativeJERHF_AK4PFchs",
        "Summer19UL17_V5_MC_RelativePtBB_AK4PFchs",
        "Summer19UL17_V5_MC_RelativePtEC1_AK4PFchs",
        "Summer19UL17_V5_MC_RelativePtEC2_AK4PFchs",
        "Summer19UL17_V5_MC_RelativePtHF_AK4PFchs",
        "Summer19UL17_V5_MC_RelativeBal_AK4PFchs",
        "Summer19UL17_V5_MC_RelativeSample_AK4PFchs",
        "Summer19UL17_V5_MC_RelativeStatEC_AK4PFchs",
        "Summer19UL17_V5_MC_RelativeStatFSR_AK4PFchs",
        "Summer19UL17_V5_MC_RelativeStatHF_AK4PFchs",
        "Summer19UL17_V5_MC_SinglePionECAL_AK4PFchs",
        "Summer19UL17_V5_MC_SinglePionHCAL_AK4PFchs",
        "Summer19UL17_V5_MC_TimePtEta_AK4PFchs"
    ],
    "2018": [
        "Summer19UL18_V5_MC_AbsoluteMPFBias_AK4PFchs",
        "Summer19UL18_V5_MC_AbsoluteScale_AK4PFchs",
        "Summer19UL18_V5_MC_AbsoluteStat_AK4PFchs",
        "Summer19UL18_V5_MC_FlavorQCD_AK4PFchs",
        "Summer19UL18_V5_MC_Fragmentation_AK4PFchs",
        "Summer19UL18_V5_MC_PileUpDataMC_AK4PFchs",
        "Summer19UL18_V5_MC_PileUpPtBB_AK4PFchs",
        "Summer19UL18_V5_MC_PileUpPtEC1_AK4PFchs",
        "Summer19UL18_V5_MC_PileUpPtEC2_AK4PFchs",
        "Summer19UL18_V5_MC_PileUpPtHF_AK4PFchs",
        "Summer19UL18_V5_MC_PileUpPtRef_AK4PFchs",
        "Summer19UL18_V5_MC_RelativeFSR_AK4PFchs",
        "Summer19UL18_V5_MC_RelativeJEREC1_AK4PFchs",
        "Summer19UL18_V5_MC_RelativeJEREC2_AK4PFchs",
        "Summer19UL18_V5_MC_RelativeJERHF_AK4PFchs",
        "Summer19UL18_V5_MC_RelativePtBB_AK4PFchs",
        "Summer19UL18_V5_MC_RelativePtEC1_AK4PFchs",
        "Summer19UL18_V5_MC_RelativePtEC2_AK4PFchs",
        "Summer19UL18_V5_MC_RelativePtHF_AK4PFchs",
        "Summer19UL18_V5_MC_RelativeBal_AK4PFchs",
        "Summer19UL18_V5_MC_RelativeSample_AK4PFchs",
        "Summer19UL18_V5_MC_RelativeStatEC_AK4PFchs",
        "Summer19UL18_V5_MC_RelativeStatFSR_AK4PFchs",
        "Summer19UL18_V5_MC_RelativeStatHF_AK4PFchs",
        "Summer19UL18_V5_MC_SinglePionECAL_AK4PFchs",
        "Summer19UL18_V5_MC_SinglePionHCAL_AK4PFchs",
        "Summer19UL18_V5_MC_TimePtEta_AK4PFchs"
    ]
}
jes_up_down = ['normal', 'up', 'down']

codePath = os.path.dirname(os.path.abspath(__file__)) + '/'
# jobVersionName = 'v72PreSelWithTauF_METAdd'
# jobVersionName = 'v73NoHLTNoTauHT400/'
# jobVersionName = 'v73NoHLTTauFHT400/'
# jobVersionName = 'v74AddMETPhi/'
# jobVersionName = 'v75AddTauTTTT/'
# jobVersionName = 'v75AddTauTTTTNoHTCut/'
# jobVersionName = 'v75OverlapRemovalFTau/'
# jobVersionName = 'v76For1tau2l/'
# jobVersionName = 'v77ForHLT/'
# jobVersionName = 'v76WithVLLSample/'
# jobVersionName = 'v76WithVLLAllMass/'
# jobVersionName = 'v77forBtagMeasurement/'
# jobVersionName = 'v77HadroPresel/'
# jobVersionName = 'v78HadroPresel/'
# jobVersionName = 'v79HadroPresel/'
# jobVersionName = 'v79forHLT/'
# jobVersionName = 'v80addTauJetVar/'
# jobVersionName = 'v80addTTExtra/'
# jobVersionName = 'v80addTTExtra1/'
# jobVersionName = 'v81addSysSum/'
# jobVersionName = 'v81for1tau2l/'
# jobVersionName = 'v82for1tau2l/'
# jobVersionName = 'v83for1tau2lEleEtaCut/'
# jobVersionName = 'v84fakeLeptonUpdate/'
# jobVersionName = 'v84Pre1tau2lNoLepCut/'
# jobVersionName = 'v84Pre1tau2lLepF2/'
# jobVersionName = 'v84Pre1tau2lLepF2V2/'
# jobVersionName = 'v84HadroPresel/'
# jobVersionName = 'v85HadroPreselTauOverlap0.5/'
# jobVersionName = 'v86HadroPreSelWithGammaRemoval/'
#jobVersionName = 'v87addPdfPSWeightSum/'
g_era = "2018"
# jobVersionName = 'v86HadroPreSelWithTTWTTZNLO'
jobVersionName = 'v88HardroForJES'
JESSys = 2
JESSysType = 3 #None or in range 0-26 2
print('JESSys=', JESSys, ' JESSysType=', JESSysType)
if JESSysType is not None:
    jobVersionName = jobVersionName + '_' + corr_Uncer_JES_map[g_era][JESSysType] + '_' + jes_up_down[JESSys]+'/'
    #jobVersionNameDown = jobVersionName + '_' + corr_Uncer_JES_map[g_era][JESSysType] + '_' + jes_up_down[2]+'/'
else:
    jobVersionName = jobVersionName + '/'

def generateJob_eachJES():
    JESSys = 2
    for iJES in range(0, 27):    
        JESSysType = iJES #None or in range 0-26 2
        print('JESSys=', JESSys, ' JESSysType=', JESSysType)
        if JESSysType is not None:
            jobVersionName = jobVersionName + '_' + corr_Uncer_JES_map[g_era][JESSysType] + '_' + jes_up_down[1]+'/'
            jobVersionNameDown = jobVersionName + '_' + corr_Uncer_JES_map[g_era][JESSysType] + '_' + jes_up_down[2]+'/'
        else:
            jobVersionName = jobVersionName + '/'

#!same version numbers means no change in algrithm but only in selection
#!todo: submit jobs in bunches for faster job submission; http://afsapply.ihep.ac.cn/cchelp/zh/local-cluster/jobs/HTCondor/
def main():
    # era = '2016'
    # era = '2016APV'
    # era = '2017'
    era = '2018'
    # era = '2022_13p6/crabNanoPost_2022postEE_v3'
    # era = '2022_13p6/crabNanoPost_2022preEE_v3'
    # onlyMC = True
    # dataList = ['jetHT', 'BTagCSV']#!for 1tau1l and 1tau0l
    # dataList = ['singleMu'] #!for HLT
    # dataList = ['JetMET', 'JetHT']
    # dataList = [ 'Muon']
    # dataList = ['doubleMu', 'muonEG', 'eGamma', 'singleMu'] #!for 1tau2l  
    
    # sumProToSkip = ['jetHT', 'ttExtra'] #! and 1tau2l
    # sumProToSkip = ['jetHT', 'BTagCSV', 'qcd', 'ttExtra'] #1tau2l #! need ttExtra for BDT training
    # sumProToSkip = ['singleMu', 'singleE','doubleMu', 'muonEG', 'eGamma', 'doubleEG', 'ttExtra'] #1tau1l and 1tau0l , 
    sumProToSkip = ['singleMu', 'singleE','doubleMu', 'muonEG', 'eGamma', 'doubleEG', 'ttExtra', 'jetHT', 'BTagCSV', 'Minor', 'singleTop', 'WJets', 'DY', 'qcd' ] #1tau1l and 1tau0l , 




###########################################
#better not modify anything afer this
    inputDir, outputDir, eraOut = getInputOutDir(jobVersionName, era)
    if JESSysType is not None:
        jobsDir = codePath + 'jobs_eachYear'+ '_' + corr_Uncer_JES_map[g_era][JESSysType] + '_' + jes_up_down[JESSys] +'/'
    else:
        jobsDir = codePath + 'jobs_eachYear/'
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
    makeJobsInDir( inputDirMC, outputDir , jobScriptsFolder, False,   eraOut, isRun3,  sumProToSkip)
    # if not onlyMC:
        # for idata in dataList:
    inputDirData = inputDir + 'data/'
    makeJobsInDir( inputDirData, outputDir, jobScriptsFolder, True, eraOut , isRun3, sumProToSkip)

    makeSubAllJobs( jobsDir , eraOut)
    subprocess.run('chmod 777 '+jobScriptsFolder + "*sh", shell=True )


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
    # outputBase = '/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/'
    outputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/'
    inputDir = inputBase + era +'/'
    outputDir = outputBase + eraDic[era] + '/' +jobVersionName  
    uf.checkMakeDir( outputDir) 
    return inputDir, outputDir, eraDic[era]
    




def makeSubAllJobs( jobsDir , era):
    if JESSysType is not None:
        subAllFile = jobsDir+"subAllJobs"+era+ '_' + corr_Uncer_JES_map[g_era][JESSysType] + '_' + jes_up_down[JESSys] + ".sh"
    else:
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
    print( 'submitting all jobs using: ', subAllFile )
    subprocess.run( 'chmod 777 ' + subAllFile,  shell=True )
    subprocess.run( 'bash ' + subAllFile,  shell=True ) 









# def makeJobsInDir( inputDir, outputDir, jobScriptsFolder, isData, dataSet, era, isRun3, ifSkipTTExtra=True):
def makeJobsInDir( inputDir, outputDir, jobScriptsFolder, isData, era, isRun3,  sumProToSkip=[]):
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
                prepareCshJob( sampleDir, koutputDir, smallFilejob, entry)
                _idx_tmp += 1
                
                #logFile = kOutDirLog + smallFile + ".log"
                #errFile = kOutDirLog + smallFile + ".err"
                # sub_oneProcess.write( "hep_sub -os CentOS7 " + iSmallJobName + " -o " + logFile + " -e " + errFile + "\n")
        if len(sample_file_path)!=0:
            #smallFile_forSub = sample_file_name[0].replace( ".root", "")
            #smallFile_forSub = re.sub(r'_(\d+)$', r'''_"%{ProcId}"''', smallFile_forSub)
            iSmallJobName_forSub = 'OS_'+ era + sample_k + '_' + '''"%{ProcId}"''' + ".sh"
            logFile = kOutDirLog + '''_"%{ProcId}"''' + ".log"
            errFile = kOutDirLog + '''_"%{ProcId}"''' + ".err"
            sub_oneProcess.write( "hep_sub -os CentOS7 -mem 8000 " + iSmallJobName_forSub + " -o " + logFile + " -e " + errFile + f" -n {len(sample_file_path)}" + "\n")#!Memory comsuption is too high, need to be understood

        os.popen('chmod 777 '+ jobScriptsFolder + sample_k + "/*sh")
        sub_oneProcess.close()
        print( 'done with kProcess: ', k )
        print( '\n')




# def prepareCshJob( inputDir, koutputDir, shFile, singleFile, eventSelection):
def prepareCshJob( inputDir, koutputDir, shFile, singleFile):
    subFile = open( shFile, 'w')
    subFile.write( "#!/bin/bash\n" )
    appDir = codePath.rsplit('/', 2)[0]
    # subFile.write( "cd "+codePath + "\n")
    subFile.write( "cd "+appDir + "\n")
    if JESSysType is not None:
        subFile.write(f'./apps/run_objectSelection_{JESSysType}_{JESSys}.out ' + inputDir +' ' + singleFile +' '+ koutputDir  + ' 0' )
    else:
        subFile.write('./apps/run_objectSelection.out ' + inputDir +' ' + singleFile +' '+ koutputDir  + ' 0' )
    subFile.close()
    # print( 'done writing the iJob for kProcess: ', shFile )



if __name__ == "__main__":
    # generateJob_eachJES()
    main()




