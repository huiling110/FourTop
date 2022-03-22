#!/usr/bin/env python
# -*- coding: utf-8 -*-
# import pandas as pd
#？？？pandas not working in ihep
import os, sys
import csv


def main():
    # logDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v4_onlyMETandPreselectionNoHLT_FixedBugForData/'
    # logDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v5_preselectionHLTMet/mc/'
    # logDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/v6_noHLTSelection_addedMulitjetForSingleMu/mc/'
    logDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v0_testing/data/'

    allProcesses = os.listdir( logDir )

    iProcess = 0
    for i in allProcesses:
        iProcess=iProcess+1
        ilogDir = logDir + i +'/log/'
        jLog = 0
        for j in os.listdir( ilogDir ):
            jLog=jLog+1
            # print( iProcess )
            # print( jLog )
            # if jLog ==3  and iProcess==2:
            # print( iProcess )
            # print( jLog )
            # print( j )
            if '.err' in j:
                checkErrLog( ilogDir + j )


def checkErrLog( errLog ):
    with open( errLog ) as log:
        lines = log.readlines()
        findTerminate = False
        for iline in lines:
            # print( iline )
            if 'objectTSelectorForNanoAOD::Terminate' in iline:
                findTerminate = True
    if  not findTerminate:
        print( errLog , ': job not done' )

        #checking runRange
        loglog = errLog.replace( 'err', 'log' )
        with open( loglog ) as logfile:
            llines = logfile.readlines()
            for iline in llines:
                if 'runRange' in iline:
                    print( 'openning log file:', loglog )
                    print( iline )
                

if __name__ == "__main__":
    main()