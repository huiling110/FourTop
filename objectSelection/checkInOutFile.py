

import os
import ROOT
import pandas as pd


from ttttGlobleQuantity import  histoGramPerSample, summedProcessList, samples, samplesCrossSection, lumiMap
import usefulFunc as uf

import sys
sys.path.insert(0,'/workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/src/FourTop/hua/')
from writeCSVforEY import getSummedHists, writeHistsToCSV



from makeJob_objectTSelectorForNanoAOD import inputBase, outputBase, eraDic, jobVersionName, era

def main():
    inOutListMC = [ inputBase + era +'/' + 'mc/', outputBase + eraDic[era] + '/' +jobVersionName  + 'mc/' ]
    inOutListData = [ inputBase + era +'/' + 'data/',outputBase + eraDic[era] + '/' +jobVersionName  + 'data/' ]
    iera = '2016postVFP'

    # checkInOutFileNumber( inOutListMC )
    # checkInOutFileNumber( inOutListData )
    
    # writeGenSumToCSV( inOutListMC[1] )

    # genSumDic = getGenSumDic( 'genWeightCSV/genSum_2016postVFP.csv' )
    # lumi = lumiMap[iera]
    # fileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/' + jobVersionName
    # uf.checkMakeDir( fileDir )
    # writeHistsOneFileOneProcess( inOutListMC[1], genSumDic, samplesCrossSection, lumi, fileDir+'mc/' )
    # writeHistsOneFileOneProcess( inOutListData[1], genSumDic, samplesCrossSection, lumi, fileDir+'data/', True )
    

    variableList = ['forEventCount']
    regionList = ['OBinitial', 'OBHLT']
    inputDir = {
        # 'mc': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/v22addedRunsTree/mc/',
        # 'data': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/v22addedRunsTree/data/',
        'mc': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/v24noJER/mc/',
        'data': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/v24noJER/data/',
    }
    # #sumProcessPerVar[var][region][sumedProcess] = hist
    sumProcessPerVar = {}
    for ivar in variableList:
        sumProcessPerVar[ivar] = getSummedHists( inputDir, regionList, ivar )
    print( sumProcessPerVar )
    # writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', 'cutFlow_objectSelection.csv')
    writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', 'cutFlowRawEntries_objectSelection.csv', True)


#copied to 
def getGenSumDic( inputCsv ):
    df = pd.read_csv( inputCsv )
    # genSumDic = df.to_dict()
    genSumDic = pd.Series( df['2016postVFP'].values, index=df['process'] ).to_dict()
    print( genSumDic )
    return genSumDic


# de/ calCutFlow( mcDir, dataDir ):

def writeHistsOneFileOneProcess( indir, genSumDic, samplesCrossSection, lumi, outDir, isData=False ):
    uf.checkMakeDir( outDir )
    for iPro in os.listdir( indir ):
        print( iPro )
        iRootFile = ROOT.TFile( outDir+iPro+'.root', "RECREATE")
        # iRootFile = ROOT.TFile( outDir+iPro+'_variableHists.root', "RECREATE")
        iHist = ROOT.TH1D( 'OBinitial_' + iPro + '_' + 'forEventCount', 'initial_' + iPro + '_' + 'onlygenWeight', 2, -1, 1 )
        iHistHLT = ROOT.TH1D( 'OBHLT_' + iPro + '_' + 'forEventCount', 'HLT_' + iPro + '_' + 'onlygenWeight', 2, -1, 1 )
        iHistPre = ROOT.TH1D( 'OBpreSelection_' + iPro + '_' + 'forEventCount', 'preSelection_' + iPro + '_' + 'onlygenWeight', 2, -1, 1 )
        iHist.SetDirectory(iRootFile)
        for ifile in os.listdir( indir+iPro ):
            if 'log' in ifile: continue
            # print( ifile )
            iRoot = ROOT.TFile( indir+iPro+ '/'+ ifile, 'READ' )
            ihist_initial = iRoot.Get( 'h_initial' )
            ihist_HLT = iRoot.Get( 'h_afterHLT' )
            ihist_pre = iRoot.Get( 'h_afterpreSelection')
            iHist.Add( ihist_initial )
            iHistHLT.Add( ihist_HLT )
            iHistPre.Add( ihist_pre)
            # iHist.SetDirectory(iRootFile)
            iRoot.Close()

        if isData: 
            iProScale = 1.0
        else: 
            iProScale = lumi*samplesCrossSection[iPro]/genSumDic[iPro]
        iHist.Scale( iProScale )
        iHistHLT.Scale( iProScale )
        iHistPre.Scale( iProScale )
        iHist.Print()

        iRootFile.Write()
        print( 'written: ', iRootFile.GetName() )
        iRootFile.Close()



def writeGenSumToCSV( outDir ):
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

    df = pd.DataFrame.from_dict( genWeightDic, orient='index' , columns=['2016postVFP'])
    df['process'] = df.index
    print( df )
    df.to_csv( 'genWeightCSV/' + 'genSum_2016postVFP.csv'  )




def checkInOutFileNumber( inOutList):
    for ipro in os.listdir( inOutList[0]) :
        if not ipro in samples: continue
        print( ipro )
        if not len( os.listdir(inOutList[1]+ipro)) - len( os.listdir(inOutList[1]+ipro)) == 1: 
            print( 'strange!!!!!!!!!!!!!!!!!!!!!! ', ipro, ' :', len( os.listdir(inOutList[0]+ipro)), " ", len( os.listdir(inOutList[1]+ipro) ) )








if __name__=='__main__':
    main()