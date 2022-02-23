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
def main():
    jobVersionName = 'v5_preselectionHLTMet'
    isHuiling = True
    dataList = [ 'jetHT', 'singleMu'] 




    inputBase = '/publicfs/cms/data/TopQuark/nanoAOD/'
    # inputDir = '/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/'
    inputSubDir = '2016/data/'
    inputDir = inputBase + inputSubDir

    era = inputSubDir[ 0:inputSubDir.find('/') ]
    print( era )
    
    outputSubDir = eraDic[era]
    outputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/'
    outputDir = outputBase + outputSubDir + jobVersionName

    isData = True
    isDataS = inputSubDir[ inputSubDir.find('/')+1:len(inputSubDir)-1]
    print( isDataS ) 
    if isDataS=='data':
        isData = True
    else:
        isData = False

    # if isHuiling:
    # else:

    
    if not isData:
        makeJobsInDir( inputDir, outputDir ,isData, '' )
    else:
        for idata in dataList:
            makeJobsInDir( inputDir, outputDir, isData, idata )










    # subAllFile = codePath+"subAllProcess_seperate.sh"
    # if os.path.exists(subAllFile):
    #     subprocess.run('rm -fr '+subAllFile , shell=True)
    # if not os.path.exists(codePath+"jobs_seperate"):
    #     os.mkdir('jobs_seperate/')
    # if not os.path.exists( outputDir):
    #     os.mkdir(outputDir)


    # subAllProcessName = open( subAllFile, 'w')
    # subAllProcessName.write( "#!/bin/bash\n")
    # subAllProcessName.write( "cd "+codePath+"jobs_seperate\n" )
    # subAllProcessName.write( "sh  " + oneProcess + "\n")
    # subAllProcessName.close()

    # subprocess.run('chmod 777 '+codePath+"jobs_seperate/*sh", shell=True )
    # subprocess.run( 'chmod 777 ' + subAllFile,  shell=True )






def checkMakeDir( folder ):
    if not os.path.exists( folder ):
        os.mkdir( folder )

def makeJobsInDir( inputDir, outputDir, isData, dataSet ):
    allProcesses = os.listdir( inputDir )
    if isData:
        outputDir = outputDir + 'mc/'
    else:
        outputDir = outputDir + 'data/'
    checkMakeDir( outputDir )

    jobScriptsFolder = codePath + 'jobs_seperata/'
    subprocess.run( 'rm -rf '+jobScriptsFolder, shell = True )
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
        # if os.path.exists(codePath+"jobs_seperate/"+sample_k+"/"):
        # subprocess.run('rm -fr '+codePath+"jobs_seperate/"+sample_k+"/", shell=True)
        subprocess.run('mkdir -p '+ jobScriptsFolder +sample_k+"/", shell=True )
        # if os.path.exists(oneProcess):
        #     subprocess.run('rm -fr '+ oneProcess,  shell=True )
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
                prepareCshJob( sampleDir, koutputDir, smallFilejob, entry)
                
                logFile = kOutDirLog + smallFile + ".log"
                errFile = kOutDirLog + smallFile + ".err"
                sub_oneProcess.write( "hep_sub "+ sample_k + '_' + smallFile + ".sh" + " -o " + logFile + " -e " + errFile + "\n")

        os.popen('chmod 777 '+ jobScriptsFolder + sample_k + "/*sh")
        sub_oneProcess.close()
        print( 'done with kProcess: ', k )
        print( '\n')




def prepareCshJob( inputDir, koutputDir, shFile, singleFile ):
    subFile = open( shFile, 'w')
    subFile.write( "#!/bin/bash\n" )
    subFile.write( "cd "+codePath + "\n")
	# subFile.write( "/bin/hostname\n" )
    subFile.write( "root -l -b -q "+"\'"+rootplizer+"(false,\""+inputDir+"\","+"\""+koutputDir+"\"," + "\""+singleFile+ "\""   + ")"+ "\'" + "\n" )
    subFile.close()
    print( 'done writing the iJob for kProcess: ', shFile )



if __name__ == "__main__":
    main()





