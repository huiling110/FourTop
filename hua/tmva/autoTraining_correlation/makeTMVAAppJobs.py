
import sys
import os

import generateVariableList as GV

def makeTMVAAppJobs( channel, version, outputDir ):
    outputDir = GV.makeBaseDir(channel, outputDir, version )
    if not os.path.exists(outputDir +"/AppResults/" ):
        os.mkdir( outputDir  +"/AppResults/")







if __name__ == '__main__':
    #  channel = 1;#1 for 1tau1l
    #  channel = 2;#2 for 1tau2os
    channel =3 # 2tau1l
    #  channel = 4
    #  version = 1
    version = 2
    outputDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/'
    TMVACodeDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/'
