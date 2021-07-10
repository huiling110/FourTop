
import sys
import os

import csv

def makeJobScripts( vlistDir, channel, outputDir, TMVACodeDir ):
    if not os.path.exists( 'JobScript/'):
        os.mkdir('JobScript/')
    
    subAllJobs = 'subAlljobs.sh'
    subAllscript = open( 'subAlljobs.sh', 'wt')
    for entry in os.listdir( vlistDir ):
        entry = entry[:-4]
        print( entry)
        iJob = 'JobScript/'+  entry + ".sh"
        makeSingleTMVAJob( vlistDir+entry, channel, iJob, TMVACodeDir )

        logFile = outputDir +   "log/" + entry + ".log"
        errFile = outputDir +  "log/" + entry +".err"
        print >> subAllscript, "hep_sub "+  iJob  + " -o " + logFile + " -e " + errFile

    
def makeSingleTMVAJob( listCsv, channel, jobName, TMVACodeDir ):
    output = open( jobName ,'wt')
    output.write( '#!/bin/bash' + '\n')
    output.write( '/bin/hostname' + '\n')
    output.write( 'cd '+ TMVACodeDir + '\n')
    output.write( 'root -b -l -q TMVAClassification_variableFileInput.C(' + '\"\",' + '\''+listCsv+'\'' +',' + str(channel) + ')'    )
    output.close()







def main():
    channel = 1;#1 for 1tau1l
    outputDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v1HT400Cut_v44_fixedSingJetHLTBugAndAddHLTcut/'
    TMVACodeDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/'
    if channel == 1:
        outputDir = outputDir + '1tau1l/'
    vListDir = outputDir + 'variableList/'
    print( 'outputDir: ', outputDir)
    if not os.path.exists( outputDir ):
        os.mkdir( outputDir )
    if not os.path.exists( vListDir):
        os.mkdir( vListDir )
    if not os.path.exists(outputDir +"/log/" ):
        os.mkdir( outputDir  +"/log/")

    makeJobScripts( vListDir, channel, outputDir, TMVACodeDir )







if __name__ == '__main__':
	main()
