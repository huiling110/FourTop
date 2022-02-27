import sys
import os
import glob
import string
import subprocess
 #

eraDic = {
    '2016':'UL2016_postVFP',
    '2016APV': 'UL2016_preVFP',
    '2017': 'UL2017',
    '2018': 'UL2018'
}


codePath = "/workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop/objectSelection/"
rootplizer = "run_objectTSelectorForNanoAOD.C"
inputBase = '/publicfs/cms/data/TopQuark/nanoAOD/'
outputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/'
def main():
    # jobVersionName = 'v5_preselectionHLTMet'
    # jobVersionName = 'v6_noHLTSelection_addedMulitjetForSingleMu'
    # jobVersionName = 'v4_onlyMETandPreselectionNoHLT_FixedBugForData'
    jobVersionName ='v7_preselectionAddingTausL'
    onlyMC = True
    # onlyMC = False
    era = '2016'
    # era = '2016APV'
    eventSelection = '7'
   # 1 for MetFilters, 2 for HLTSelection, 4 for preSelection. so 7 if all selection; 0 if no selection 
    isHuiling = True
    dataList = [ 'jetHT', 'singleMu'] 



###########################################
#better not modify anything afer this
    inputDir = inputBase + era +'/'
    outputDir = outputBase + eraDic[era] + '/' +jobVersionName +'/' 
    checkMakeDir( outputDir) 
    inputDirMC = inputDir + 'mc/'
    makeJobsInDir( inputDirMC, outputDir , False, '', eventSelection, isHuiling )
    if not onlyMC:
        for idata in dataList:
            inputDirData = inputDir + 'data/'
            makeJobsInDir( inputDirData, outputDir, True, idata, eventSelection, isHuiling )

    jobsDir = codePath + 'jobs_seperata/'
    makeSubAllJobs( jobsDir )
    subprocess.run('chmod 777 '+codePath+"jobs_seperata/*sh", shell=True )






def makeSubAllJobs( jobsDir ):
    subAllFile = codePath+"subAllJobs.sh"
    if os.path.exists(subAllFile):
        subprocess.run('rm -fr '+subAllFile , shell=True)

    subAllProcessName = open( subAllFile, 'w')
    subAllProcessName.write( "#!/bin/bash\n")
    subAllProcessName.write( 'cd ' + jobsDir + '\n')
    for ijob in os.listdir( jobsDir ):
        if '.sh' in ijob:
            subAllProcessName.write( "sh  " + ijob + "\n")
    subAllProcessName.close()
    print( 'submitting all jobs using: ', subAllFile )
    subprocess.run( 'chmod 777 ' + subAllFile,  shell=True )








def checkMakeDir( folder ):
    if not os.path.exists( folder ):
        os.mkdir( folder )

def makeJobsInDir( inputDir, outputDir, isData, dataSet, eventSelection, isHuiling ):
    allProcesses = os.listdir( inputDir )
    if isData:
        outputDir = outputDir + 'data/'
    else:
        outputDir = outputDir + 'mc/'
    checkMakeDir( outputDir )

    jobScriptsFolder = codePath + 'jobs_seperata/'
    checkMakeDir( jobScriptsFolder )

    processNumber = 0
    for k in allProcesses:
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
        checkMakeDir( koutputDir )
        checkMakeDir( kOutDirLog )
        print( 'outputDir for kprocess: ', koutputDir )
        for entry in os.listdir( sampleDir):
            if os.path.isfile(os.path.join(sampleDir, entry)):
                smallFile = entry.replace( ".root", "")
                # smallFilejob = "jobs_seperate/" +sample_k + "/" + sample_k + '_' + smallFile + ".sh"  
                smallFilejob = jobScriptsFolder +sample_k + "/" + sample_k + '_' + smallFile + ".sh"  
                prepareCshJob( sampleDir, koutputDir, smallFilejob, entry, eventSelection, isHuiling )
                
                logFile = kOutDirLog + smallFile + ".log"
                errFile = kOutDirLog + smallFile + ".err"
                sub_oneProcess.write( "hep_sub "+ sample_k + '_' + smallFile + ".sh" + " -o " + logFile + " -e " + errFile + "\n")

        os.popen('chmod 777 '+ jobScriptsFolder + sample_k + "/*sh")
        sub_oneProcess.close()
        print( 'done with kProcess: ', k )
        print( '\n')




def prepareCshJob( inputDir, koutputDir, shFile, singleFile, eventSelection, isHuiling ):
    if isHuiling: 
        ishuiling = 'true'
    else:
        ishuiling = 'false'
    subFile = open( shFile, 'w')
    subFile.write( "#!/bin/bash\n" )
    subFile.write( "cd "+codePath + "\n")
    # subFile.write( "root -l -b -q "+"\'"+rootplizer+"(false,\""+inputDir+"\","+"\""+koutputDir+"\"," + "\""+singleFile+ "\""   + ")"+ "\'" + "\n" )
    subFile.write( "root -l -b -q "+"\'"+rootplizer+"(false,\""+inputDir+"\","+"\""+koutputDir+"\"," + "\""+singleFile+ "\"," +  "\""+eventSelection+"\","  +ishuiling   + ")"+ "\'" + "\n" )
    subFile.close()
    print( 'done writing the iJob for kProcess: ', shFile )



if __name__ == "__main__":
    main()





