import os
import subprocess

import ttttGlobleQuantity as gq
import usefulFunc as uf

eraDic = {
    '2016':'UL2016_postVFP',
    '2016APV': 'UL2016_preVFP',
    '2017': 'UL2017',
    '2018': 'UL2018'
}

codePath = os.path.dirname(os.path.abspath(__file__)) + '/'
#
inputBase = '/publicfs/cms/data/TopQuark/nanoAOD/'
outputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/'
# jobVersionName = 'v49FixedPileUpOnlyJER/'
# jobVersionName = 'v49FixedPileUpJERAndTES/'
# jobVersionName = 'v50switchRawPtJERNoTES/'
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
jobVersionName = 'v57ovelapWithTausF/'

onlyMC = False
# era = '2016'
era = '2016APV'
# era = '2017'
# era = '2018'
def main():
    # onlyMC = True
    # eventSelection = '7'
    eventSelection = '5'
    # eventSelection = '1'
   # 1 for MetFilters, 2 for HLTSelection, 4 for preSelection. so 7 if all selection; 0 if no selection 
    isHuiling = True
    dataList = [ 'jetHT', 'singleMu'] 
    # dataList = [ 'jetHT']
    # dataList = ['singleMu'] 

    print( "era: ", era, "  eventSelection: ", eventSelection )



###########################################
#better not modify anything afer this
    inputDir = inputBase + era +'/'
    outputDir = outputBase + eraDic[era] + '/' +jobVersionName  
    uf.checkMakeDir( outputDir) 
    inputDirMC = inputDir + 'mc/'

    # jobsDir = codePath + 'jobs_seperata/'
    jobsDir = codePath + 'jobs_eachYear/'
    uf.checkMakeDir(jobsDir)

    makeJobsInDir( inputDirMC, outputDir , False, '', eventSelection, isHuiling, era )
    if not onlyMC:
        for idata in dataList:
            inputDirData = inputDir + 'data/'
            makeJobsInDir( inputDirData, outputDir, True, idata, eventSelection, isHuiling, era )

    makeSubAllJobs( jobsDir )
    # subprocess.run('chmod 777 '+codePath+"jobs_seperata/*sh", shell=True )
    subprocess.run('chmod 777 '+ jobsDir+ era+ "/*sh", shell=True )






def makeSubAllJobs( jobsDir ):
    # subAllFile = codePath+"subAllJobs.sh"
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









def makeJobsInDir( inputDir, outputDir, isData, dataSet, eventSelection, isHuiling , era):
    allProcesses = os.listdir( inputDir )
    if isData:
        outputDir = outputDir + 'data/'
    else:
        outputDir = outputDir + 'mc/'
    uf.checkMakeDir( outputDir )

    # jobScriptsFolder = codePath + 'jobs_seperata/'
    jobScriptsFolder = codePath + 'jobs_eachYear/'
    uf.checkMakeDir( jobScriptsFolder )
    jobScriptsFolder = jobScriptsFolder+era+'/'
    # if os.path.exists( jobScriptsFolder ):
    #     subprocess.run('rm -fr '+ jobScriptsFolder , shell=True)
    uf.checkMakeDir(jobScriptsFolder)
    

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
                # smallFilejob = jobScriptsFolder +sample_k + "/" + sample_k + '_' + smallFile + ".sh"  
                iSmallJobName = 'OS_'+ era + sample_k + '_' + smallFile + ".sh"
                smallFilejob = jobScriptsFolder +sample_k + "/" + iSmallJobName   
                prepareCshJob( sampleDir, koutputDir, smallFilejob, entry, eventSelection, isHuiling )
                
                logFile = kOutDirLog + smallFile + ".log"
                errFile = kOutDirLog + smallFile + ".err"
                # sub_oneProcess.write( "hep_sub "+ sample_k + '_' + smallFile + ".sh" + " -o " + logFile + " -e " + errFile + "\n")
                sub_oneProcess.write( "hep_sub "+ iSmallJobName + " -o " + logFile + " -e " + errFile + "\n")

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
    # subFile.write
    # subFile.write( "root -l -b -q "+"\'"+rootplizer+"(false,\""+inputDir+"\","+"\""+koutputDir+"\"," + "\""+singleFile+ "\"," +  "\""+eventSelection+"\","  
    # +ishuiling   + ")"+ "\'" + "\n" )
    subFile.write('./run_objectTSelectorForNanoAOD.out ' + '0' +' '+ inputDir + ' ' + koutputDir + ' ' + singleFile + ' '  + eventSelection  )
    subFile.close()
    print( 'done writing the iJob for kProcess: ', shFile )



if __name__ == "__main__":
    main()





