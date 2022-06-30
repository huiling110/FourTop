import sys
import os
import glob
import string
import subprocess
 #


#???make the makeJobs code some functions and stuff to make it reusable

#???make this code to be able to submit 2016pre and post and data all at once

def main():


    #all the parameters you need to change is in this part , better not change the rest of the code.
    # inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v9_allSelection/mc/"
    # inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v12_addedMissingBranch/mc/"
    # inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v14_MetFilterHLTSelection/mc/"
    # inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v14_MetFilterHLTSelection/mc/"
    # inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v15_0selection/mc/"
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_postVFP/v4modifiedMinDeltaR_fromV9/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/v4modifiedMinDeltaR_fromV9/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/v6addWeightUpdown_fromV9/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/v0baselineSelection_fromV15/'
    # outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_postVFP/v0baselineSelection_fromV15/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v16_HLTselection/mc/'
    outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineSelection_fromV16/mc/'


    inVersion = 'v16_HLTselection'
    outVersion = 'v0baseline'
    justMC = False
    year = '2016'
    dataSet = 'jetHT'


    inputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/'
    outputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/'

    inputDirMap = {}
    #python dict
    if year=='2016':
        inputDirMap ['2016postVFP'] = {}
        inputDirMap ['2016preVFP'] = {}
        inputDirMap['2016preVFP']['mc']= inputBase + 'UL2016_preVFP/'+ inVersion + '/mc/'  
        inputDirMap['2016postVFP']['mc'] = inputBase + 'UL2016_postVFP/' + inVersion + '/mc/'
        if not justMC:
            inputDirMap['2016preVFP'] ['data']= inputBase + 'UL2016_preVFP/'+ inVersion + '/data/'  
            inputDirMap['2016postVFP']['data'] = inputBase + 'UL2016_postVFP/' + inVersion + '/data/'

    for iera in inputDirMap.keys():
        print(iera)



#     Jobsuvbmitpath = '/workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/src/FourTop/hua/makeVariables'
#     rootplizer = "run_makeVaribles_forBDT.C"
#     subAllFile = Jobsubmitpath+"/subAllProcess.sh"
#     if os.path.exists(subAllFile):
#         os.popen('rm -fr '+subAllFile)
#     if not os.path.exists(Jobsubmitpath+"/Jobsubmit_seperate"):
#         os.mkdir('Jobsubmit_seperate/')
#     if not os.path.exists( outputDir):
#         os.mkdir( outputDir )

#     #better not change code after this line
#     subAllProcessName = file(subAllFile,"w")
#     print >> subAllProcessName, "#!/bin/bash"
#     print >> subAllProcessName, "cd "+Jobsubmitpath

#     for entry in os.listdir(inputDir ):
#         #  if entry
#         processJob = 'Jobsubmit_seperate/'+  entry + ".sh"
#         prepareCshJob( entry, processJob )

#         if not os.path.exists(outputDir +"/log/" ):
#             os.mkdir( outputDir  +"/log/")
#         logFile = outputDir +   "log/" + entry + ".log"
#         errFile = outputDir +  "log/" + entry +".err"
#         print >> subAllProcessName, "hep_sub "+  processJob  + " -o " + logFile + " -e " + errFile


# os.popen('chmod 777 '+Jobsubmitpath+"/Jobsubmit_seperate/*sh")
# os.popen('chmod 777 '+Jobsubmitpath+"/subAllProcess.sh")



# def prepareCshJob(inputFile,shFile ):
#     subFile  = file(shFile,"w")
#     print >> subFile, "#!/bin/bash"
#     print >> subFile, "/bin/hostname"
#     print >> subFile, "cd "+Jobsubmitpath
#     print >> subFile, "root -l -b -q "+"\'"+rootplizer+"(false,\"" + inputDir+"\","     +"\""+inputFile+"\","+"\""+outputDir+ "\""  + ")"+ "\'"
#     print shFile



if __name__=="__main__":
    main() 










