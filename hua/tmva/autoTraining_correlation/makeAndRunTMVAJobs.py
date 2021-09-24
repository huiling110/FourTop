
import sys
import os

import csv

import generateVariableList as GV


def main():
    channel = 1;#1 for 1tau1l
    #  channel = 2;#2 for 1tau2os
    #  channel =3 # 2tau1l
    #  channel = 4
    #  version = 1
    version = 1
    outputDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/'
    TMVACodeDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/'
    isApp = True
    #  isApp = False
    channelName = GV.getNameForChannel( channel ) 

    vListDir, outputDir = checkMakeDir( channelName, outputDir, TMVACodeDir, version, isApp )
    makeJobScripts( vListDir, channel, outputDir, TMVACodeDir, isApp )





def makeJobScripts( vlistDir, channel, outputDir, TMVACodeDir, isApp ):
    jobDir = ''
    subAllscriptName = ''
    if isApp:
        jobDir = 'singleJobs' + '_App/'
        subAllscriptName = 'subAlljobs_App.sh'
    else:
        jobDir = 'singleJobs' + '_Train/'
        subAllscriptName = 'subAlljobs_train.sh'
    subAllscript = open( subAllscriptName, 'wt')
    if not os.path.exists( jobDir ):
        os.mkdir( jobDir )
    #  if not os.path.exists( 'JobScript/'):
        #  os.mkdir('JobScript/')
    
    #  subAllscript = open( 'subAlljobs.sh', 'wt')
    for entry in os.listdir( vlistDir ):
        entryName = entry[:-4]
        print( entry)
        #  iJob = 'JobScript/'+  entryName + ".sh"
        iJob = jobDir +  entryName + ".sh"
        makeSingleTMVAJob( vlistDir, entry, channel, iJob, TMVACodeDir, outputDir, isApp )

        logFile = outputDir +   "log/" + entryName + ".log"
        errFile = outputDir +  "log/" + entryName +".err"
        #  print >> subAllscript, "hep_sub -mem 8000 "+  iJob  + " -o " + logFile + " -e " + errFile
        subAllscript.write( "hep_sub -mem 8000 "+  iJob  + " -o " + logFile + " -e " + errFile + '\n')
    #  os.popen('chmod 777 '+ TMVACodeDir + 'autoTraining_correlation' + "/JobScript/*sh")
    #  os.popen('chmod 777 ' + TMVACodeDir + 'autoTraining_correlation'+ '/subAlljobs.sh' )
    os.popen('chmod 777 '+ TMVACodeDir + 'autoTraining_correlation/' + jobDir + "*sh")
    os.popen('chmod 777 ' + TMVACodeDir + 'autoTraining_correlation/'+ subAllscriptName )

    
def makeSingleTMVAJob( vlistDir, entry, channel, jobName, TMVACodeDir , outputDir, isApp ):
    listCsv = vlistDir + entry
    output = open( jobName ,'wt')
    output.write( '#!/bin/bash' + '\n')
    output.write( '/bin/hostname' + '\n')
    output.write( 'source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh' + '\n' )
    output.write( 'cd '+ TMVACodeDir + '\n')
    if isApp:
        weightDir = outputDir[:-11]
        vlistName = entry[:-4]
        weightDir = weightDir + 'dataset/'+ GV.getNameForChannel( channel ) + '_' + vlistName + '_weight/'
        print( 'weightDir :', weightDir)
        output.write( 'root -b -l -q '  +'\'' + 'TMVAClassificationApplication_multipleSamples.C(' + '\"\",' + '\"'+outputDir+'\",' + '\"'+listCsv+'\"' +',\"' + weightDir+ "\","+ str(channel) + ')' + '\''   )
    else:
        output.write( 'root -b -l -q '  +'\'' + 'TMVAClassification_variableFileInput.C(' + '\"\",' + '\"'+outputDir+'\",' + '\"'+listCsv+'\"' +',' + str(channel) + ', false' ')' + '\''   )
    output.close()

#  def checkJob():







def checkMakeDir( channelName, outputDir, TMVACodeDir, version, isApp ):
    outputDir = GV.makeBaseDir(channelName, version, outputDir )
    vListDir = outputDir + 'variableList/'
    if isApp:
        outputDir = outputDir + 'AppResults/'
        #  if not os.path.exists(outputDir +"AppResults/" ):
            #  os.mkdir( outputDir  +"AppResults/")
        if not os.path.exists(outputDir ):
            os.mkdir( outputDir )
    print( 'outputDir: ', outputDir)
    if not os.path.exists(outputDir +"/log/" ):
        os.mkdir( outputDir  +"/log/")
    return vListDir, outputDir



if __name__ == '__main__':
    main()






