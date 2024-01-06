import os
import subprocess

import ttttGlobleQuantity as gq
import usefulFunc as uf


codePath = os.path.dirname(os.path.abspath(__file__)) + '/'
#
# jobVersionName = 'v51TESNoJER/'
# jobVersionName = 'v51TESNewLepObjectRemovalCorrected/'
# jobVersionName = 'v52noHLTSelection/'
# jobVersionName = 'v52noHLTButPreSelection/'
# jobVersionName = 'v53HLTAndPre/'
# jobVersionName = 'v54noHLTButPre/'
# jobVersionName = 'v55HLTAndPre/'
# jobVersionName = 'v54noHLTButPreMetFixed/'
# jobVersionName = 'v55ojectRemovalwithTight/'
# jobVersionName = 'v55ojectRemovalwithTightNoHLT/'
# jobVersionName = 'v56addLepTopHLTSel/'
# jobVersionName = 'v56NoHLTButPre/'
# jobVersionName = 'v56preselection/'
# jobVersionName = 'v57ovelapWithTausF/'
# jobVersionName = 'v58addGenBranches/'
# jobVersionName = 'v59newOScode/'
# jobVersionName = 'v60fixeJetBtagBug/'
# jobVersionName = 'v61fixesLepRemovalBug/'
# jobVersionName = 'v62addTauJetVars/'
# jobVersionName = 'v63smallFixJER/'
# jobVersionName = 'v64noHLTSel/'
# jobVersionName = 'v64PreAndHLTSel/'
# jobVersionName = 'v64PreAndHLTSel_JERUp/'
# jobVersionName = 'v64PreAndHLTSel_JERDown/'
# jobVersionName = 'v64PreAndHLTSel_JESUp/'
# jobVersionName = 'v64PreAndHLTSel_JESDown/'
# jobVersionName = 'v64PreAndHLTSel_TESUp/'
# jobVersionName = 'v64PreAndHLTSel_TESDown/'
# jobVersionName = 'v65TheoryWeightAdded/'
# jobVersionName = 'v66TheoryWeightAdded/'
# jobVersionName = 'v0for2022NoHLT/'
jobVersionName = 'v0for2022baseline/'

#run3
# jobVersionName = 'v0Testing/'
# jobVersionName = 'v1newCrab/'
# jobVersionName = 'v0preSel/'



def main():
    # era = '2016'
    # era = '2016APV'
    # era = '2017'
    # era = '2018'
    # era = '13p6TeV/2022'
    # era = '2022_13p6/NanoPost'
    # era = '2022_13p6/crabNanoPost_2022PostEE/2022postEE'
    # era = '2022_13p6/NanoPost/2022preEE'
    era = '2022_13p6/crabNanoPost_2022postEE_v3'
    # onlyMC = True
    # dataList = ['jetHT']
    # dataList = [ 'jetHT', 'singleMu'] 
    # dataList = [ 'JetHT', 'JetMet'] # 2022
    # dataList = ['singleMu'] 
    # dataList = ['JetMET', 'Muon']
    dataList = ['JetMET']
    

    print( "era: ", era )



    onlyMC = False


###########################################
#better not modify anything afer this
    inputDir, outputDir, eraOut = getInputOutDir(jobVersionName, era)

    jobsDir = codePath + 'jobs_eachYear/'
    uf.checkMakeDir(jobsDir)


    inputDirMC = inputDir + 'mc/'
    makeJobsInDir( inputDirMC, outputDir , False, '',  eraOut )
    if not onlyMC:
        for idata in dataList:
            inputDirData = inputDir + 'data/'
            makeJobsInDir( inputDirData, outputDir, True, idata,  eraOut )

    makeSubAllJobs( jobsDir , eraOut)
    subprocess.run('chmod 777 '+ jobsDir+ eraOut+ "/*sh", shell=True )


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
    print( 'submitting all jobs using: ', subAllFile )
    subprocess.run( 'chmod 777 ' + subAllFile,  shell=True )









def makeJobsInDir( inputDir, outputDir, isData, dataSet, era):
    allProcesses = os.listdir( inputDir )
    if isData:
        outputDir = outputDir + 'data/'
    else:
        outputDir = outputDir + 'mc/'
    uf.checkMakeDir( outputDir )

    jobScriptsFolder = codePath + 'jobs_eachYear/'
    uf.checkMakeDir( jobScriptsFolder )
    jobScriptsFolder = jobScriptsFolder+era+'/'
    uf.checkMakeDir(jobScriptsFolder)

    for k in allProcesses:
        if not '2022' in era:
            if not k in gq.samples:  continue
        else:
            if not k in gq.Run3Samples.keys():  continue
            
        print(k)
        sample_k = k
        if  isData:
            if dataSet not in k:
                print( "omitting: ", k )
                continue
        print( 'kProcess: ', sample_k )

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
        for entry in os.listdir( sampleDir):
            if not '.root' in entry: continue
            if os.path.isfile(os.path.join(sampleDir, entry)):
                smallFile = entry.replace( ".root", "")
                iSmallJobName = 'OS_'+ era + sample_k + '_' + smallFile + ".sh"
                smallFilejob = jobScriptsFolder +sample_k + "/" + iSmallJobName   
                prepareCshJob( sampleDir, koutputDir, smallFilejob, entry)
                
                logFile = kOutDirLog + smallFile + ".log"
                errFile = kOutDirLog + smallFile + ".err"
                # sub_oneProcess.write( "hep_sub "+ '-m 6000 '+ iSmallJobName + " -o " + logFile + " -e " + errFile + "\n")
                sub_oneProcess.write( "hep_sub " + iSmallJobName + " -o " + logFile + " -e " + errFile + "\n")

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
    subFile.write('./apps/run_objectSelection.out ' + inputDir +' ' + singleFile +' '+ koutputDir  + ' 0' )
    subFile.close()
    print( 'done writing the iJob for kProcess: ', shFile )



if __name__ == "__main__":
    main()





