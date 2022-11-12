import os
import subprocess

import pandas as pd

from ttttGlobleQuantity import lumiMap, samplesCrossSection


def checkMakeDir( folder ):
    if not os.path.exists( folder ):
        os.mkdir( folder )

def getGenSumDic( inputCsv, era ):
    df = pd.read_csv( inputCsv )
    # genSumDic = pd.Series( df['2016postVFP'].values, index=df['process'] ).to_dict()
    genSumDic = pd.Series( df[era].values, index=df['process'] ).to_dict()
    # print( genSumDic )
    return genSumDic

# def getProcessScale( processName, era ):
#     scale = lumiMap[era]*samplesCrossSection[processName]/getGenSumDic()

def sumbitJobs(  jobsh):
    print('staring to submit jobs')
    command = 'bash {}'.format(  jobsh )
    process = subprocess.run( command, shell=True ) 
    output = process.stdout
    print(output)

    print('jobs submitted')


def getInputDic( inVersion, histVersion, era):
    '''
    for final hists folder structure
    '''
    inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/' + era +'/'
    inputDirDic = {
        'mc': inputDirBase + inVersion + '/mc/' + histVersion + '/',
        'data': inputDirBase + inVersion + '/data/' + histVersion + '/',
    }
    return inputDirDic

def getEraFromDir(inputDir):
    era = ''
    if '2016' in inputDir:
        era = '2016'
    elif '2017' in inputDir:
        era = '2017'
    elif '2018' in inputDir:
        era = '2018'
    return era
