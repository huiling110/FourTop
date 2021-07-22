
import sys
import os

import csv

import generateVariableList as GV






def makeJobScripts( vlistDir, channel, outputDir, TMVACodeDir ):
    if not os.path.exists( 'JobScript/'):
        os.mkdir('JobScript/')
    
    subAllscript = open( 'subAlljobs.sh', 'wt')
    for entry in os.listdir( vlistDir ):
        entryName = entry[:-4]
        print( entry)
        iJob = 'JobScript/'+  entryName + ".sh"
        makeSingleTMVAJob( vlistDir+entry, channel, iJob, TMVACodeDir, outputDir )

        logFile = outputDir +   "log/" + entryName + ".log"
        errFile = outputDir +  "log/" + entryName +".err"
        #  print >> subAllscript, "hep_sub -mem 8000 "+  iJob  + " -o " + logFile + " -e " + errFile
        subAllscript.write( "hep_sub -mem 8000 "+  iJob  + " -o " + logFile + " -e " + errFile + '\n')
    os.popen('chmod 777 '+ TMVACodeDir + 'autoTraining_correlation' + "/JobScript/*sh")
    os.popen('chmod 777 ' + TMVACodeDir + 'autoTraining_correlation'+ '/subAlljobs.sh' )

    
def makeSingleTMVAJob( listCsv, channel, jobName, TMVACodeDir , outputDir):
    output = open( jobName ,'wt')
    output.write( '#!/bin/bash' + '\n')
    output.write( '/bin/hostname' + '\n')
    output.write( 'source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh' + '\n' )
    output.write( 'cd '+ TMVACodeDir + '\n')
    #  output.write( 'root -b -l -q '  +'\'' + 'TMVAClassification_variableFileInput.C(' + '\"\",' + '\"'+listCsv+'\"' +',' + str(channel) + ')' + '\''   )
    output.write( 'root -b -l -q '  +'\'' + 'TMVAClassification_variableFileInput.C(' + '\"\",' + '\"'+outputDir+'\",' + '\"'+listCsv+'\"' +',' + str(channel) + ')' + '\''   )
    output.close()

#  def checkJob():







def checkMakeDir( channel, outputDir, TMVACodeDir, version ):
    outputDir = GV.makeBaseDir(channel, outputDir, version )
    vListDir = outputDir + 'variableList/'
    print( 'outputDir: ', outputDir)
    if not os.path.exists(outputDir +"/log/" ):
        os.mkdir( outputDir  +"/log/")
    return vListDir, outputDir



if __name__ == '__main__':
    #  channel = 1;#1 for 1tau1l
    #  channel = 2;#2 for 1tau2os
    channel =3
    version = 1
    outputDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/'
    TMVACodeDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/'

    vListDir, outputDir = checkMakeDir( channel, outputDir, TMVACodeDir, version )
    makeJobScripts( vListDir, channel, outputDir, TMVACodeDir )






