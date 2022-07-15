

import os
import ROOT
import pandas as pd


from ttttGlobleQuantity import  histoGramPerSample, summedProcessList, samples, samplesCrossSection
import usefulFunc as uf


from makeJob_objectTSelectorForNanoAOD import inputBase, outputBase, eraDic, jobVersionName, era

def main():
    inOutListMC = [ inputBase + era +'/' + 'mc/', outputBase + eraDic[era] + '/' +jobVersionName  + 'mc/' ]
    inOutListData = [ inputBase + era +'/' + 'data/',outputBase + eraDic[era] + '/' +jobVersionName  + 'data/' ]

    # checkInOutFileNumber( inOutListMC )
    # checkInOutFileNumber( inOutListData )
    
    # writeGenSumToCSV( inOutListMC[1] )

    genSumDic = getGenSumDic( 'genWeightCSV/genSum_2016postVFP.csv' )
    lumi = 16810
    fileDir = outputBase + eraDic[era] + '/' +jobVersionName+'results/'
    uf.checkMakeDir( fileDir )
    writeHistsOneFileOneProcess( inOutListMC[1], genSumDic, samplesCrossSection, lumi, fileDir+'mc/' )
    writeHistsOneFileOneProcess( inOutListData[1], genSumDic, samplesCrossSection, lumi, fileDir+'data/', True )
    


    # calCutFlow()

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
        # iRootFile = ROOT.TFile( outDir+iPro+'.root', "RECREATE")
        iRootFile = ROOT.TFile( outDir+iPro+'_variableHists.root', "RECREATE")
        iHist = ROOT.TH1D( 'initial_' + iPro + '_' + 'onlygenWeight', 'initial_' + iPro + '_' + 'onlygenWeight', 2, -1, 1 )
        iHistHLT = ROOT.TH1D( 'HLT_' + iPro + '_' + 'onlygenWeight', 'HLT_' + iPro + '_' + 'onlygenWeight', 2, -1, 1 )
        iHistPre = ROOT.TH1D( 'preSelection_' + iPro + '_' + 'onlygenWeight', 'preSelection_' + iPro + '_' + 'onlygenWeight', 2, -1, 1 )
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