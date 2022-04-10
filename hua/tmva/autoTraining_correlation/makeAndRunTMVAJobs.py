#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : makeAndRunTMVAJobs.py
# Author            : Huiling Hua <huahl@ihep.ac.cn>
# Date              : 03.10.2021
# Last Modified Date: 03.10.2021
# Last Modified By  : Huiling Hua <huahl@ihep.ac.cn>

import sys
import os

import csv

import generateVariableList as GV


def main():
    channel = 1;#1 for 1tau1l
    #  channel = 2;#2 for 1tau2os
    #  channel =3 # 2tau1l
    # channel = 4
    # channel = 5
    #  version = 1
    version = 2
    outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/'
    TMVACodeDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop/hua/tmva/'
    # isApp = True
    isApp = False
    binNum = 11 #for App only
    channelName = GV.getNameForChannel( channel ) 

    vListDir, outputDir = checkMakeDir( channelName, outputDir, TMVACodeDir, version, isApp, binNum )
    makeJobScripts( vListDir, channel, outputDir, TMVACodeDir, isApp, binNum )
    
    #???add features of submitting jobs and reporting job status and check job results





def makeJobScripts( vlistDir, channel, outputDir, TMVACodeDir, isApp, binNum ):
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
    
    for entry in os.listdir( vlistDir ):
        entryName = entry[:-4]
        print( entry)
        #  iJob = 'JobScript/'+  entryName + ".sh"
        iJob = jobDir +  entryName + ".sh"
        makeSingleTMVAJob( vlistDir, entry, channel, iJob, TMVACodeDir, outputDir, isApp, binNum )

        logFile = outputDir +   "log/" + entryName + ".log"
        errFile = outputDir +  "log/" + entryName +".err"
        subAllscript.write( "hep_sub -mem 8000 "+  iJob  + " -o " + logFile + " -e " + errFile + '\n')
    os.popen('chmod 777 '+ TMVACodeDir + 'autoTraining_correlation/' + jobDir + "*sh")
    os.popen('chmod 777 ' + TMVACodeDir + 'autoTraining_correlation/'+ subAllscriptName )

    
def makeSingleTMVAJob( vlistDir, entry, channel, jobName, TMVACodeDir , outputDir, isApp, binNum ):
    listCsv = vlistDir + entry
    output = open( jobName ,'wt')
    output.write( '#!/bin/bash' + '\n')
    output.write( '/bin/hostname' + '\n')
    output.write( 'source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh' + '\n' )
    output.write( 'cd '+ TMVACodeDir + '\n')
    if isApp:
        #  weightDir = outputDir[:-11]
        vlistName = entry[:-4]
        weightDir = outputDir[:outputDir.find('AppResults')]
        # weightDir = weightDir + 'dataset/'+ GV.getNameForChannel( channel ) + '_' + vlistName + '_weight/'
        weightDir = weightDir + 'dataset/'+ GV.getNameForChannel( channel ) + vlistName + '_weight/'
        print( 'weightDir :', weightDir)
        # output.write( 'root -b -l -q '  +'\'' + 'TMVAClassificationApplication_multipleSamples.C(' + '\"\",' + '\"'+outputDir+'\",' + '\"'+listCsv+'\"' +',\"' + weightDir+ "\","+ str(channel) +',' +str(binNum) + ')' + '\''   )
        output.write( 'root -b -l -q '  +'\'' + 'TMVAClassificationApplication_multipleSamples.C(' + '\"\",' + '\"'+outputDir+'\",' + '\"'+listCsv+'\"' +',\"' + weightDir+ "\","+ '\"'+GV.getNameForChannel(channel)+'\"'  +',' +str(binNum) + ')' + '\''   )
    else:
        # output.write( 'root -b -l -q '  +'\'' + 'TMVAClassification_variableFileInput.C(' + '\"\",' + '\"'+outputDir+'\",' + '\"'+listCsv+'\"' +',' + str(channel) + ', false' ')' + '\''   )
        output.write( 'root -b -l -q '  +'\'' + 'TMVAClassification_variableFileInput.C(' + '\"\",' + '\"'+outputDir+'\",' + '\"'+listCsv+'\"' +',' + "\""+ GV.getNameForChannel(channel) +"\""+ ', false' ')' + '\''   )
    output.close()

#  def checkJob():







def checkMakeDir( channelName, outputDir, TMVACodeDir, version, isApp, binNum ):
    outputDir = GV.makeBaseDir(channelName, version, outputDir )
    vListDir = outputDir + 'variableList/'
    if isApp:
        #  outputDir = outputDir + 'AppResults/'
        outputDir = outputDir + 'AppResults_' + str(binNum) +'bins/'
        if not os.path.exists(outputDir ):
            os.mkdir( outputDir )
    print( 'outputDir: ', outputDir)
    if not os.path.exists(outputDir +"/log/" ):
        os.mkdir( outputDir  +"/log/")
    return vListDir, outputDir



if __name__ == '__main__':
    main()






