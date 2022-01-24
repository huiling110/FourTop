import sys
import os
import glob
import string
import subprocess
 #



#all the parameters you need to change is in this part , better not change the rest of the code.
#CHANGE HERE TO RUN ON DATA
#isdata = True
isdata = False
isHuiling = True
if isHuiling:
    outputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/2016PPV/"
    Jobsubmitpath = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/"
else:
    outputDir = "/publicfs/cms/user/fabioiemmi/tauOfTTTT_NanoAOD/"
    Jobsubmitpath = "/publicfs/cms/user/fabioiemmi/CMSSW_10_2_20_UL/src/FourTop/objectSelection/"
inputDir = '/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/'
allProcesses = os.listdir( inputDir )



rootplizer = "run_objectTSelector.C"
subAllFile = Jobsubmitpath+"subAllProcess_seperate.sh"
if os.path.exists(subAllFile):
    os.popen('rm -fr '+subAllFile)
if not os.path.exists(Jobsubmitpath+"Jobsubmit_seperate"):
    os.mkdir('Jobsubmit_seperate/')
if not os.path.exists( outputDir):
    os.mkdir(outputDir)

# sample = {
    #"QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Legacy16V2_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8addGenWeight/210201_055930/0000/": "17",
    #"QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Legacy16V2_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8addGenWeight/210201_055930/0000/": "18",
    #"QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Legacy16V2_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8addGenWeight/210201_060130/0000/": "19",:3

# }
#better not change code after this line













def prepareCshJob( inputDir,shFile, singleFile ):
    subFile = open( shFile, 'w')
    subFile.write( "#!/bin/bash\n" )
    subFile.write( "cd "+Jobsubmitpath + "\n")
    subFile.write( "root -l -b -q "+"\'"+rootplizer+"(false,\""+inputDir+"\","+"\""+outputDir+"\"," + "\""+singleFile+ "\""   + ")"+ "\'" + "\n" )
    subFile.close()
    print( 'done writing the iJob for kProcess: ', shFile )


# subAllProcessName = file(subAllFile,"w")
# print >> subAllProcessName, "#!/bin/bash"
# print >> subAllProcessName, "cd "+Jobsubmitpath+"Jobsubmit_seperate"
subAllProcessName = open( subAllFile, 'w')
subAllProcessName.write( "#!/bin/bash\n")
subAllProcessName.write( "cd "+Jobsubmitpath+"Jobsubmit_seperate\n" )

# for k in sample:
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
       os.popen('rm -fr '+Jobsubmitpath+"Jobsubmit_seperate/"+sampleName+"/")
    os.popen('mkdir -p '+Jobsubmitpath+"Jobsubmit_seperate/"+sampleName+"/")
    if os.path.exists(oneProcess):
        os.popen('rm -fr '+ oneProcess)
    sub_oneProcess = open ( oneProcess, 'w')
    sub_oneProcess.write( "cd "+Jobsubmitpath+"Jobsubmit_seperate/" + sampleName + "/" + "\n" + "\n")
    print( 'job sub script for kProcess is: ', oneProcess )

    sampleDir = inputDir + sample_k +'/'
    for entry in os.listdir( sampleDir):
        if os.path.isfile(os.path.join(sampleDir, entry)):

            smallFile = entry.replace( ".root", "")
            smallFilejob = "Jobsubmit_seperate/" +sampleName + "/" + smallFile + ".sh"  
            prepareCshJob( sampleDir, smallFilejob, entry)
            
            logFile = outputDir +  sampleName + "/log/" + smallFile + ".log"
            errFile = outputDir +  sampleName + "/log/" + smallFile + ".err"
            sub_oneProcess.write( "hep_sub "+  smallFile + ".sh" + " -o " + logFile + " -e " + errFile )

    subAllProcessName.write( "sh  " + oneProcess + "\n")
    os.popen('chmod 777 '+Jobsubmitpath+"Jobsubmit_seperate/" + sampleName + "/*sh")
    os.popen('chmod 777 '+Jobsubmitpath+"Jobsubmit_seperate/*sh")
    print( 'done with kProcess')
    print( '\n')


os.popen('chmod 777 '+Jobsubmitpath+"subAllProcess_seperate.sh")





