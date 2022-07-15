

import os
import ROOT
import pandas as pd


from ttttGlobleQuantity import  histoGramPerSample, summedProcessList, samples


from makeJob_objectTSelectorForNanoAOD import inputBase, outputBase, eraDic, jobVersionName, era

def main():
    inOutListMC = [ inputBase + era +'/' + 'mc/', outputBase + eraDic[era] + '/' +jobVersionName  + 'mc/' ]
    inOutListData = [ inputBase + era +'/' + 'data/',outputBase + eraDic[era] + '/' +jobVersionName  + 'data/' ]

    # checkInOutFileNumber( inOutListMC )
    # checkInOutFileNumber( inOutListData )
    
    writeGenSumToCSV( inOutListMC[1] )

    # genSumDic = getGenSumDic( 'genWeightCSV/genSum_2016postVFP.csv' )
    # writeHistsOneFileOneProcess( inOutListMC[1] )


    # calCutFlow()

def getGenSumDic( inputCsv ):
    df = pd.read_csv( inputCsv )
    genSumDic = df.to_dict()
    print( genSumDic )
    return genSumDic


# de/ calCutFlow( mcDir, dataDir ):

def writeHistsOneFileOneProcess( indir ):
    for iPro in os.listdir( indir ):
        print( iPro )
        iHist = ROOT.TH1D( 'initial_' + iPro + '_' + 'onlygenWeight' )
        for ifile in os.listdir( indir+iPro ):
            if 'log' in ifile: continue
            # print( ifile )
            iRoot = ROOT.TFile( indir+iPro+ '/'+ ifile, 'READ' )
            ihist_initial = iRoot.Get( 'h_initial' )
            iHist.Add( ihist_initial )
            iRoot.Close()
        iHist.Scale(  )



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





# iprocess = 'ttbar_0l/'

# print( os.listdir( inputDir ))

# print( len( os.listdir(inputDir+iprocess)))
# print( len( os.listdir(outputDir+iprocess)))



if __name__=='__main__':
    main()