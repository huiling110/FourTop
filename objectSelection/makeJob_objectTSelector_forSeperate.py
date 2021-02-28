import sys
import os
import glob
import string
import subprocess

outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/v29_ptForAllLeptons_v2/"
#  outputDir = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/test_objectSelction/"
inputDir = "/publicfs/cms/data/TopQuark/FourTop_hua/v3/2016/"

Jobsubmitpath = "/publicfs/cms/user/huahuil/code/FourTopTau/CMSSW_10_2_20_UL/src/FourTop/objectSelection/"
rootplizer = "run_objectTSelector.C"
subAllFile = Jobsubmitpath+"/subAllProcess_seperate.sh"
if os.path.exists(subAllFile):
    os.popen('rm -fr '+subAllFile)
if not os.path.exists(Jobsubmitpath+"/Jobsubmit_seperate"):
    os.mkdir('Jobsubmit_seperate/')



sample = {
  #  "TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_correctnPartonsInBorn/Legacy16V2_TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8addGenWeight/210201_023641/0000/":"0",
  # {{{
##tt
    #  "TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/Legacy16V2_TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8addGenWeight/210201_024446/0000/":"1_0",
    #  "TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/Legacy16V2_TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8addGenWeight/210201_024239/0000/":"1_1",
    #  "TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/Legacy16V2_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8addGenWeight/210201_024040/0000/":"1_2",

    "ttZJets_13TeV_madgraphMLM-pythia8/Legacy16V2_ttZJets_13TeV_madgraphMLM-pythia8addGenWeight/210201_025644/0000":"3",
    "ttWJets_13TeV_madgraphMLM/Legacy16V2_ttWJets_13TeV_madgraphMLMaddGenWeight/210201_030246/0000/":"4",
    "ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8/Legacy16V2_ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8addGenWeight/210201_050201/0000/":"5",

    "WZ_TuneCUETP8M1_13TeV-pythia8/Legacy16V2_WZ_TuneCUETP8M1_13TeV-pythia8addGenWeight/210201_031735/0000/":"6",
    "WW_TuneCUETP8M1_13TeV-pythia8/Legacy16V2_WW_TuneCUETP8M1_13TeV-pythia8addGenWeight/210201_032142/0000/":"7",
    "ZZ_TuneCUETP8M1_13TeV-pythia8/Legacy16V2_ZZ_TuneCUETP8M1_13TeV-pythia8addGenWeight/210201_032809/0000/": "8",

    "WGGJets_TuneCUETP8M1_13TeV_madgraphMLM_pythia8/Legacy16V2_WGGJets_TuneCUETP8M1_13TeV_madgraphMLM_pythia8addGenWeight/210201_040503/0000/": "9",
    "ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8/Legacy16V2_ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8addGenWeight/210201_040904/0000/": "10",
    #  /publicfs/cms/data/TopQuark/FourTop_hua/v3/2016/
# }}}

}


def prepareCshJob(inputFile,shFile, singleFile):
    subFile  = file(shFile,"w")
    print >> subFile, "#!/bin/bash"
    print >> subFile, "/bin/hostname"
    #  print >> subFile, "gcc -v"
    #  print >> subFile, "pwd"
    print >> subFile, "cd "+Jobsubmitpath
    print >> subFile, "root -l -b -q "+"\'"+rootplizer+"(false,\""+inputFile+"\","+"\""+outputDir+"\"," + "\""+singleFile+ "\""   + ")"+ "\'"
    print shFile


subAllProcessName = file(subAllFile,"w")
print >> subAllProcessName, "#!/bin/bash"
print >> subAllProcessName, "cd "+Jobsubmitpath+"Jobsubmit_seperate"
for k in sample:
    print k
    #  print sample[k]
    sample_k = k
    #  sampleNumber = sample[k]
    sampleName = sample_k.split("/")[0]
    print sampleName
   
    if not os.path.exists(outputDir +sampleName):
        os.mkdir(outputDir + sampleName)
    if not os.path.exists(outputDir +sampleName +"/log/" ):
        os.mkdir( outputDir + sampleName +"/log/")

    oneProcess =  Jobsubmitpath + "/Jobsubmit_seperate/"+  sampleName + ".sh"
    if os.path.exists(Jobsubmitpath+"/Jobsubmit_seperate/"+sampleName+"/"):
       os.popen('rm -fr '+Jobsubmitpath+"/Jobsubmit_seperate/"+sampleName+"/")
    os.popen('mkdir -p '+Jobsubmitpath+"/Jobsubmit_seperate/"+sampleName+"/")
    if os.path.exists(oneProcess):
        os.popen('rm -fr '+ oneProcess)
    sub_oneProcess = file( oneProcess, "w")
    print >> sub_oneProcess , "cd "+Jobsubmitpath+"Jobsubmit_seperate/" + sampleName + "/"

    sampleDir = inputDir + sample_k
    for entry in os.listdir( sampleDir):
        if os.path.isfile(os.path.join(sampleDir, entry)):

            smallFile = entry.replace( ".root", "")
            smallFilejob = "Jobsubmit_seperate/" +sampleName + "/" + smallFile + ".sh"  
            prepareCshJob( sample_k, smallFilejob, entry)
            
            logFile = outputDir +  sampleName + "/log/" + smallFile + ".log"
            errFile = outputDir +  sampleName + "/log/" + smallFile + ".err"
            print >> sub_oneProcess, "hep_sub "+  smallFile + ".sh" + " -o " + logFile + " -e " + errFile

    #  print >> subAllProcessName, "cd " + sampleName
    print >> subAllProcessName, "sh  " + oneProcess
    os.popen('chmod 777 '+Jobsubmitpath+"/Jobsubmit_seperate/" + sampleName + "/*sh")
    os.popen('chmod 777 '+Jobsubmitpath+"/Jobsubmit_seperate/*sh")


os.popen('chmod 777 '+Jobsubmitpath+"/subAllProcess_seperate.sh")





