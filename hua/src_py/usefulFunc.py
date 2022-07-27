import os
import pandas as pd

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
