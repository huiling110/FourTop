import os
import pandas as pd

import subprocess

from ttttGlobleQuantity import lumiMap, samplesCrossSection

def checkMakeDir( folder ):
    if not os.path.exists( folder ):
        os.mkdir( folder )

def getGenSumDic( inputCsv ):
    df = pd.read_csv( inputCsv )
    genSumDic = pd.Series( df['2016postVFP'].values, index=df['process'] ).to_dict()
    # print( genSumDic )
    return genSumDic

# def getProcessScale( processName, era ):
#     scale = lumiMap[era]*samplesCrossSection[processName]/getGenSumDic()

def sumbitJobs(jobsh):
    print('staring to submit jobs')
    command = 'bash {}'.format( jobsh )
    process = subprocess.run( command, shell=True ) 
    output = process.stdout
    print(output)

    print('jobs submitted')

