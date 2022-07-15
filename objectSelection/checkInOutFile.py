

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

def writeGenSumToCSV( outDir ):
    genWeightDic = {}
    for iPro in os.listdir( outDir ):
        print( iPro) 
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
        sumHist.Print()
        del sumHist

    print( genWeightDic )

    pd.DataFrame([genWeightDic] )

    print( pd )



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