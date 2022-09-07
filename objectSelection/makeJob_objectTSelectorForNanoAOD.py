import glob
import os
import string
import subprocess
import sys

import ttttGlobleQuantity as gq
import usefulFunc as uf

 #my own modules



eraDic = {
    '2016':'UL2016_postVFP',
    '2016APV': 'UL2016_preVFP',
    '2017': 'UL2017',
    '2018': 'UL2018'
}


codePath = "/workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/src/FourTop/objectSelection/"
rootplizer = "run_objectTSelectorForNanoAOD.C"
inputBase = '/publicfs/cms/data/TopQuark/nanoAOD/'
outputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/'
# jobVersionName = 'v20FixedSelectJetsBug/'
# jobVersionName = 'v21withGoodLumi/'
# jobVersionName = 'v22addedRunsTree/'
# jobVersionName = 'v23basicWeight/'
# jobVersionName = 'v24noJER/'
# jobVersionName = 'v25noJERNOTES/'
# jobVersionName = 'v26noJERNOTESwithSorting/'
# jobVersionName = 'v27noJERnoTESWithObjectRemoval/'
# jobVersionName = 'v28JERTESBack/'
jobVersionName = 'v29LorentzProblemSolvedNoJERnoTES/'
onlyMC = False
era = '2016'
# era = '2016APV'
# era = '2018'
def main():
    # onlyMC = True
    eventSelection = '3'
   # 1 for MetFilters, 2 for HLTSelection, 4 for preSelection. so 7 if all selection; 0 if no selection 
    isHuiling = True
    # dataList = [ 'jetHT', 'singleMu'] 
    dataList = [ 'jetHT'] 

    print( "era: ", era, "  eventSelection: ", eventSelection )



###########################################
#better not modify anything afer this
    inputDir = inputBase + era +'/'
    outputDir = outputBase + eraDic[era] + '/' +jobVersionName  
    uf.checkMakeDir( outputDir) 
    inputDirMC = inputDir + 'mc/'

    jobsDir = codePath + 'jobs_seperata/'
    if os.path.exists( jobsDir ):
        subprocess.run('rm -fr '+ jobsDir , shell=True)
    uf.checkMakeDir( jobsDir)

    makeJobsInDir( inputDirMC, outputDir , False, '', eventSelection, isHuiling )
    if not onlyMC:
        for idata in dataList:
            inputDirData = inputDir + 'data/'
            makeJobsInDir( inputDirData, outputDir, True, idata, eventSelection, isHuiling )

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









def makeJobsInDir( inputDir, outputDir, isData, dataSet, eventSelection, isHuiling ):
    allProcesses = os.listdir( inputDir )
    if isData:
        outputDir = outputDir + 'data/'
    else:
        outputDir = outputDir + 'mc/'
    uf.checkMakeDir( outputDir )

    jobScriptsFolder = codePath + 'jobs_seperata/'
    uf.checkMakeDir( jobScriptsFolder )

    for k in allProcesses:
        if not k in gq.samples:  continue
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





