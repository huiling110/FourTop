import sys
import os
import glob
import string
import subprocess
 #



#all the parameters you need to change is in this part , better not change the rest of the code.
#  isdata = True
isdata = False
# outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_postVFP/v2Add2Variables_fromV9/'
inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v9_allSelection/mc/"
# outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/v3correctBjetsvariable_fromV9/'
# inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v9_allSelection/mc/"
# outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_postVFP/v3correctBjetsvariable_fromV9/'
# outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_postVFP/v4modifiedMinDeltaR_fromV9/'
# outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/v4modifiedMinDeltaR_fromV9/'
outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/v5addWeight_fromV9/'


Jobsubmitpath = '/workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop/hua/makeVariables'
rootplizer = "run_makeVaribles_forBDT.C"
subAllFile = Jobsubmitpath+"/subAllProcess.sh"
if os.path.exists(subAllFile):
    os.popen('rm -fr '+subAllFile)
if not os.path.exists(Jobsubmitpath+"/Jobsubmit_seperate"):
    os.mkdir('Jobsubmit_seperate/')
if not os.path.exists( outputDir):
    os.mkdir( outputDir )

#better not change code after this line

def prepareCshJob(inputFile,shFile ):
    subFile  = file(shFile,"w")
    print >> subFile, "#!/bin/bash"
    print >> subFile, "/bin/hostname"
    #  print >> subFile, "gcc -v"
    #  print >> subFile, "pwd"
    print >> subFile, "cd "+Jobsubmitpath
    # print >> subFile, "root -l -b -q "+"\'"+rootplizer+"(false,\""+inputFile+"\","+"\""+outputDir+ "\""  + ")"+ "\'"
    print >> subFile, "root -l -b -q "+"\'"+rootplizer+"(false,\"" + inputDir+"\","     +"\""+inputFile+"\","+"\""+outputDir+ "\""  + ")"+ "\'"
    print shFile

subAllProcessName = file(subAllFile,"w")
print >> subAllProcessName, "#!/bin/bash"
print >> subAllProcessName, "cd "+Jobsubmitpath

for entry in os.listdir(inputDir ):
    #  if entry
    processJob = 'Jobsubmit_seperate/'+  entry + ".sh"
    prepareCshJob( entry, processJob )

    if not os.path.exists(outputDir +"/log/" ):
        os.mkdir( outputDir  +"/log/")
    logFile = outputDir +   "log/" + entry + ".log"
    errFile = outputDir +  "log/" + entry +".err"
    print >> subAllProcessName, "hep_sub "+  processJob  + " -o " + logFile + " -e " + errFile


os.popen('chmod 777 '+Jobsubmitpath+"/Jobsubmit_seperate/*sh")
os.popen('chmod 777 '+Jobsubmitpath+"/subAllProcess.sh")













