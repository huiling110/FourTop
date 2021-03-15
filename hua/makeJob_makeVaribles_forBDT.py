import sys
import os
import glob
import string
import subprocess
 #



#all the parameters you need to change is in this part , better not change the rest of the code.
#  isdata = True
isdata = False
inputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v32_addedalleventsTree/"
outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/forMVA/v1/"

Jobsubmitpath = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/"
rootplizer = "run_makeVaribles_forBDT.C"
subAllFile = Jobsubmitpath+"/subAllProcess.sh"
if os.path.exists(subAllFile):
    os.popen('rm -fr '+subAllFile)
if not os.path.exists(Jobsubmitpath+"/Jobsubmit_seperate"):
    os.mkdir('Jobsubmit_seperate/')

#better not change code after this line

def prepareCshJob(inputFile,shFile ):
    subFile  = file(shFile,"w")
    print >> subFile, "#!/bin/bash"
    print >> subFile, "/bin/hostname"
    #  print >> subFile, "gcc -v"
    #  print >> subFile, "pwd"
    print >> subFile, "cd "+Jobsubmitpath
    print >> subFile, "root -l -b -q "+"\'"+rootplizer+"(false,\""+inputFile+"\","+"\""+outputDir+ "\""  + ")"+ "\'"
    print shFile

subAllProcessName = file(subAllFile,"w")
print >> subAllProcessName, "#!/bin/bash"
#  print >> subAllProcessName, "cd "+Jobsubmitpath+"Jobsubmit_seperate"
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








#  subAllProcessName = file(subAllFile,"w")
#  print >> subAllProcessName, "#!/bin/bash"
#  print >> subAllProcessName, "cd "+Jobsubmitpath+"Jobsubmit_seperate"
#
#
#  for k in sample:
    #  print k
    #  sample_k = k
    #  sampleName = sample_k.split("/")[0]
    #  if  isdata:
        #  sampleName = sampleName + sample[k]
    #  print sampleName
#
    #  if not os.path.exists(outputDir +sampleName):
        #  os.mkdir(outputDir + sampleName)
    #  if not os.path.exists(outputDir +sampleName +"/log/" ):
        #  os.mkdir( outputDir + sampleName +"/log/")
#
    #  oneProcess =  Jobsubmitpath + "Jobsubmit_seperate/"+  sampleName + ".sh"
    #  if os.path.exists(Jobsubmitpath+"/Jobsubmit_seperate/"+sampleName+"/"):
       #  os.popen('rm -fr '+Jobsubmitpath+"/Jobsubmit_seperate/"+sampleName+"/")
    #  os.popen('mkdir -p '+Jobsubmitpath+"/Jobsubmit_seperate/"+sampleName+"/")
    #  if os.path.exists(oneProcess):
        #  os.popen('rm -fr '+ oneProcess)
    #  sub_oneProcess = file( oneProcess, "w")
    #  print >> sub_oneProcess , "cd "+Jobsubmitpath+"Jobsubmit_seperate/" + sampleName + "/"
#
    #  sampleDir = inputDir + sample_k
    #  for entry in os.listdir( sampleDir):
        #  if os.path.isfile(os.path.join(sampleDir, entry)):
#
            #  smallFile = entry.replace( ".root", "")
            #  smallFilejob = "Jobsubmit_seperate/" +sampleName + "/" + smallFile + ".sh"
            #  prepareCshJob( sample_k, smallFilejob, entry)
#
            #  logFile = outputDir +  sampleName + "/log/" + smallFile + ".log"
            #  errFile = outputDir +  sampleName + "/log/" + smallFile + ".err"
            #  print >> sub_oneProcess, "hep_sub "+  smallFile + ".sh" + " -o " + logFile + " -e " + errFile

    #  print >> subAllProcessName, "cd " + sampleName
    #  print >> subAllProcessName, "sh  " + oneProcess
    #  os.popen('chmod 777 '+Jobsubmitpath+"/Jobsubmit_seperate/" + sampleName + "/*sh")
    #  os.popen('chmod 777 '+Jobsubmitpath+"/Jobsubmit_seperate/*sh")
#  os.popen('chmod 777 '+Jobsubmitpath+"/subAllProcess_seperate.sh")





