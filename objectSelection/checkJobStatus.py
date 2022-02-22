#!/usr/bin/env python
# -*- coding: utf-8 -*-
# import pandas as pd
#？？？pandas not working in ihep
import os, sys
import csv


def main():
    logDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v4_onlyMETandPreselectionNoHLT_FixedBugForData/'

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
                

if __name__ == "__main__":
    main()