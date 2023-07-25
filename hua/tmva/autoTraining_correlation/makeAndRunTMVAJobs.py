#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : makeAndRunTMVAJobs.py
# Author            : Huiling Hua <huahl@ihep.ac.cn>
# Date              : 03.10.2021
# Last Modified Date: 03.10.2021
# Last Modified By  : Huiling Hua <huahl@ihep.ac.cn>

import os

import generateVariableList as GV
import usefulFunc as uf


def main():
    channel = '1tau1l'
    # channel = '1tau2l'
    # version = 0 # with b tag shape
    version = 1 #with b tag WP 
    # version = 3 # add bjetT variables
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v1fixedTauVariables_v40addTauJetEtau/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3extra1tau1lCut_v41addVertexSelection/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v3extra1tau1lCut_v41addVertexSelection/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v3extra1tau1lCut_v42fixedChargeType/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v6Cut1tau1lVariableFixed_v42fixedChargeType/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2018/v6Cut1tau1lVariableFixed_v42fixedChargeType/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v6Cut1tau1lVariableFixed_v42fixedChargeType/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v8Cut1tau1l_v42fixedChargeType/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v5extra1tau1lCut_v56NoHLTButPre/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v5extra1tau1lCut_v56preselection/'
    outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v7forBDT_v60fixeJetBtagBug/'
    # isApp = True
    isApp = False
    # appYear = '2018'
    # appYear = '2017'
    appYear = '2016'
    binNum = 30
    # binNum = 20
    # binNum = 15
    # binNum = 10
    # binNum = 40
    
    
    # appFolderName = 'AppResults'
    appFolderName = 'AppResults_'+appYear
    # appFolderName = 'AppResults_resubmit'
    # binNum = 11 #for App only
    # binNum = 40#for App only
    # binNum = 20#for App only

    
   
    era = uf.getEraFromDir(outputDir) 

    TMVACodeDir = os.path.dirname(os.path.abspath(__file__)) 
    TMVACodeDir = TMVACodeDir[:TMVACodeDir.rfind('/')]
    vListDir, outputDir = checkMakeDir( channel, outputDir, TMVACodeDir, version, isApp, binNum, appFolderName )
    subAll = makeJobScripts( vListDir, channel, outputDir, TMVACodeDir, isApp, binNum, appFolderName, era )
    
    #???add features of submitting jobs and reporting job status and check job results
    uf.sumbitJobs( subAll )






def makeJobScripts( vlistDir, channel, outputDir, TMVACodeDir, isApp, binNum, appFolderName,era ):
    jobDir = os.path.dirname(os.path.abspath(__file__)) 
    subAllscriptName = ''
    if isApp:
        jobDirSep =  jobDir +'/singleJobs' + '_App/'
        subAllscriptName = jobDir + 'subAlljobs_App.sh'
    else:
        jobDirSep = jobDir +'/singleJobs' + '_Train/'
        subAllscriptName = jobDir + '/subAlljobs_train.sh'
    subAllscript = open( subAllscriptName, 'wt')
    if not os.path.exists( jobDirSep ):
        os.mkdir( jobDirSep )
    
    for entry in os.listdir( vlistDir ):
        entryName = entry[:-4]
        print( entry)
        iJob = jobDirSep +  entryName + ".sh"
        makeSingleTMVAJob( vlistDir, entry, channel, iJob, TMVACodeDir, outputDir, isApp, binNum, appFolderName, era )

        logFile = outputDir +   "log/" + entryName + ".log"
        errFile = outputDir +  "log/" + entryName +".err"
        subAllscript.write( "hep_sub -mem 4000 "+  iJob  + " -o " + logFile + " -e " + errFile + '\n')
    os.popen('chmod 777 '+jobDirSep + "*sh")
    os.popen('chmod 777 ' + subAllscriptName )
    print( 'sub all jobs using: ', subAllscriptName)
    return subAllscriptName

    
def makeSingleTMVAJob( vlistDir, entry, channel, jobName, TMVACodeDir , outputDir, isApp, binNum, appFolderName , era):
    listCsv = vlistDir + entry
    output = open( jobName ,'wt')
    output.write( '#!/bin/bash' + '\n')
    output.write( '/bin/hostname' + '\n')
    output.write( 'cd '+ TMVACodeDir + '\n')
    if isApp:
        vlistName = entry[:-4]
        weightDir = outputDir[:outputDir.find( appFolderName )]
        
        weightDir = weightDir + 'dataset/'+ channel + vlistName + '_weight/'
        print( 'weightDir :', weightDir)
        output.write( 'root -b -l -q '  +'\'' + 'TMVAClassificationApplication_multipleSamples.C(' + '\"\",' + '\"'+outputDir+'\",' + '\"'+listCsv+'\"' +',\"' + weightDir+ "\","+ '\"'+ channel +'\"'  +',' +str(binNum) + ')' + '\''   )
    else:
        # output.write( 'root -b -l -q '  +'\'' + 'TMVAClassification_variableFileInput.C(' + '\"\",' + '\"'+outputDir+'\",' + '\"'+listCsv+'\"' +',' + "\""+ channel +"\""+ ', false,  false )' + '\''   )
        trainCommand = 'root -b -l -q '  +'\'' + 'TMVAClassification_variableFileInput.C(' + '\"\",' + '\"'+outputDir+'\",' + '\"'+listCsv+'\"' +',' + "\""+ channel +'\", '+ '\"'+era+'\"'+  ', false,  false )' + '\'' 

        output.write(trainCommand   )
    output.close()
    print('written ', jobName)

#  def checkJob():







def checkMakeDir( channelName, outputDir, TMVACodeDir, version, isApp, binNum , appFolderName ):
    uf.checkMakeDir( outputDir )
    outputDir = GV.makeBaseDir(channelName, version, outputDir )
    vListDir = outputDir + 'variableList/'
    if isApp:
        # outputDir = outputDir + 'AppResults_' + str(binNum) +'bins/'
        outputDir = outputDir + appFolderName + '_' + str(binNum) +'bins/'
        if not os.path.exists(outputDir ):
            os.mkdir( outputDir )
    print( 'outputDir: ', outputDir)
    if not os.path.exists(outputDir +"/log/" ):
        os.mkdir( outputDir  +"/log/")
    return vListDir, outputDir



if __name__ == '__main__':
    main()






