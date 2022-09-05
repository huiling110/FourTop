

import os
import sys

import pandas as pd
import ROOT
import usefulFunc as uf
from ttttGlobleQuantity import (histoGramPerSample, lumiMap, samples,
                                samplesCrossSection, summedProcessList)

sys.path.insert(0,'/workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/src/FourTop/hua/')
from writeCSVforEY import getSummedHists, writeHistsToCSV

from makeJob_objectTSelectorForNanoAOD import (era, eraDic, inputBase,
                                               jobVersionName, outputBase)


def main():
    inOutListMC = [ inputBase + era +'/' + 'mc/', outputBase + eraDic[era] + '/' +jobVersionName  + 'mc/' ]
    inOutListData = [ inputBase + era +'/' + 'data/',outputBase + eraDic[era] + '/' +jobVersionName  + 'data/' ]
    # iera = '2016postVFP'
    iera = '2016preVFP'

    # checkInOutFileNumber( inOutListMC )
    # checkInOutFileNumber( inOutListData )
    
    # writeGenSumToCSV( inOutListMC[1] )
    # writeGenSumToCSV( inOutListMC[1] , iera)

    

    variableList = ['forEventCount']
    regionList = ['OBinitial', 'OBHLT']

    inputDir = {
        # 'mc': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/' +  jobVersionName+ '/mc/',
        # 'data': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/' + jobVersionName + '/data/',
        'mc': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/'+iera+'/objectSelectionResults/' +  jobVersionName+ '/mc/',
        'data': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/'+iera+'/objectSelectionResults/' + jobVersionName + '/data/',
    }
    # #sumProcessPerVar[var][region][sumedProcess] = hist
    sumProcessPerVar = {}
    for ivar in variableList:
        sumProcessPerVar[ivar] = getSummedHists( inputDir, regionList, ivar )
    print( sumProcessPerVar )
    writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', 'cutFlow_objectSelection.csv')
    writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', 'cutFlowRawEntries_objectSelection.csv', True)




# de/ calCutFlow( mcDir, dataDir ):

# def writGenSum_fromRunTree( outDir):
#     processList = []
#     genWeightDic = {}
#     for iPro in os.listdir( outDir ):
#         print( iPro) 
#         processList.append( iPro )
#         # runTree = ROOT.
#         for ifile in os.listdir( outDir+iPro ):
#             if 'log' in ifile: continue
#             # print( ifile )
#             iRoot = ROOT.TFile( outDir+iPro+ '/'+ ifile, 'READ' )
#             iRunTree = iRoot.Get( 'Runs' )
#             sumHist.Add( ihist_initial )
#             iRoot.Close()



def writeGenSumToCSV( outDir, era ):
    processList = []
    genWeightDic = {}
    for iPro in os.listdir( outDir ):
        print( iPro) 
        processList.append( iPro )
        sumHist = ROOT.TH1D( 'summedHist' , 'summedHist', 2, -1, 1 )
        for ifile in os.listdir( outDir+iPro ):
            if 'log' in ifile: continue
            # print( ifile )
            iRoot = ROOT.TFile( outDir+iPro+ '/'+ ifile, 'READ' )
            ihist_initial = iRoot.Get( 'h_initial' )
            # ihist_initial.Print()
            sumHist.Add( ihist_initial )
            iRoot.Close()
        genWeightDic[iPro] = sumHist.Integral()
        # sumHist.Print()
        del sumHist

    print( genWeightDic )

    # series = pd.Series( genWeightDic, name='2016postVFP')

    # df = pd.DataFrame.from_dict( genWeightDic, orient='index' , columns=['2016postVFP'])
    df = pd.DataFrame.from_dict( genWeightDic, orient='index' , columns=[era])
    df['process'] = df.index
    print( df )
    # df.to_csv( 'genWeightCSV/' + 'genSum_2016postVFP.csv'  )
    df.to_csv( 'genWeightCSV/genSum_' + era +'.csv' )




def checkInOutFileNumber( inOutList):
    for ipro in os.listdir( inOutList[0]) :
        if not ipro in samples: continue
        print( ipro )
        if not len( os.listdir(inOutList[1]+ipro)) - len( os.listdir(inOutList[1]+ipro)) == 1: 
            print( 'strange!!!!!!!!!!!!!!!!!!!!!! ', ipro, ' :', len( os.listdir(inOutList[0]+ipro)), " ", len( os.listdir(inOutList[1]+ipro) ) )








if __name__=='__main__':
    main()
