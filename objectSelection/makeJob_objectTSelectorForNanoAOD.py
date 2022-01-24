import sys
import os
import glob
import string
import subprocess
 #


def prepareCshJob( inputDir, koutputDir, shFile, singleFile ):
    subFile = open( shFile, 'w')
    subFile.write( "#!/bin/bash\n" )
    subFile.write( "cd "+Jobsubmitpath + "\n")
	# subFile.write( "/bin/hostname\n" )
    subFile.write( "root -l -b -q "+"\'"+rootplizer+"(false,\""+inputDir+"\","+"\""+koutputDir+"\"," + "\""+singleFile+ "\""   + ")"+ "\'" + "\n" )
    subFile.close()
    print( 'done writing the iJob for kProcess: ', shFile )

#all the parameters you need to change is in this part , better not change the rest of the code.
#CHANGE HERE TO RUN ON DATA
#isdata = True
isdata = False
isHuiling = True
if isHuiling:
    outputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/2016PPV/v0_testing/"
    Jobsubmitpath = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/"
else:
    outputDir = "/publicfs/cms/user/fabioiemmi/tauOfTTTT_NanoAOD/"
    Jobsubmitpath = "/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/objectSelection/"
inputDir = '/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/'
allProcesses = os.listdir( inputDir )



rootplizer = "run_objectTSelectorForNanoAOD.C"
subAllFile = Jobsubmitpath+"subAllProcess_seperate.sh"
if os.path.exists(subAllFile):
    subprocess.run('rm -fr '+subAllFile , shell=True)
if not os.path.exists(Jobsubmitpath+"Jobsubmit_seperate"):
    os.mkdir('Jobsubmit_seperate/')
if not os.path.exists( outputDir):
    os.mkdir(outputDir)


subAllProcessName = open( subAllFile, 'w')
subAllProcessName.write( "#!/bin/bash\n")
subAllProcessName.write( "cd "+Jobsubmitpath+"Jobsubmit_seperate\n" )

processNumber = 0
for k in allProcesses:
    print(k)
    sample_k = k
    sampleName = k
    if  isdata:
        sampleName = sampleName + sample[k]
    print( 'kProcess: ', sampleName )
   
    if not os.path.exists(outputDir +sampleName):
        os.mkdir(outputDir + sampleName)
    if not os.path.exists(outputDir +sampleName +"/log/" ):
        os.mkdir( outputDir + sampleName +"/log/")
    print( 'have made folder neccessary for out put directory' )

    oneProcess =  Jobsubmitpath + "Jobsubmit_seperate/"+  sampleName + ".sh"
    if os.path.exists(Jobsubmitpath+"Jobsubmit_seperate/"+sampleName+"/"):
       subprocess.run('rm -fr '+Jobsubmitpath+"Jobsubmit_seperate/"+sampleName+"/", shell=True)
    #    subprocess.run( ['rm ', '-fr', Jobsubmitpath +"Jobsubmit_seperate/"+ sampleName +"/"]   )
    subprocess.run('mkdir -p '+Jobsubmitpath+"Jobsubmit_seperate/"+sampleName+"/", shell=True )
    if os.path.exists(oneProcess):
        subprocess.run('rm -fr '+ oneProcess,  shell=True )
    sub_oneProcess = open ( oneProcess, 'w')
    sub_oneProcess.write( "cd "+Jobsubmitpath+"Jobsubmit_seperate/" + sampleName + "/" + "\n" + "\n")
    print( 'job sub script for kProcess is: ', oneProcess )

    sampleDir = inputDir + sample_k +'/'
    koutputDir = outputDir + k + '/'
    print( 'outputDir for kprocess: ', koutputDir )
    for entry in os.listdir( sampleDir):
        if os.path.isfile(os.path.join(sampleDir, entry)):

            smallFile = entry.replace( ".root", "")
            smallFilejob = "Jobsubmit_seperate/" +sampleName + "/" + smallFile + ".sh"  
            prepareCshJob( sampleDir, koutputDir, smallFilejob, entry)
            
            logFile = outputDir +  sampleName + "/log/" + smallFile + ".log"
            errFile = outputDir +  sampleName + "/log/" + smallFile + ".err"
            sub_oneProcess.write( "hep_sub "+  smallFile + ".sh" + " -o " + logFile + " -e " + errFile + "\n")

    subAllProcessName.write( "sh  " + oneProcess + "\n")
    os.popen('chmod 777 '+Jobsubmitpath+"Jobsubmit_seperate/" + sampleName + "/*sh")
    # os.popen('chmod 777 '+Jobsubmitpath+"Jobsubmit_seperate/*sh")
    sub_oneProcess.close()
    print( 'done with kProcess: ', k )
    print( '\n')

subAllProcessName.close()

subprocess.run('chmod 777 '+Jobsubmitpath+"Jobsubmit_seperate/*sh", shell=True )
subprocess.run( 'chmod 777 ' + subAllFile,  shell=True )





