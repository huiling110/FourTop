import os

import ROOT
import usefulFunc as uf
from ttttGlobleQuantity import summedProcessList

import plotVaribles


def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/AppResults_30bins/'
    
    
   
    for ifile in os.listdir( inputDir ): 
        # inputFile = 'TMVApp_1tau1l_10var_forCombine.root'
        if not '.root' in ifile: continue
        plotOneFile(ifile, inputDir) 


def plotOneFile(inputFile, inputDir):
    era = uf.getEraFromDir(inputDir)
    histsInProcesses, dummySys = getHists(inputDir, inputFile)
    print(histsInProcesses)

    outDir = inputDir+'results/'
    uf.checkMakeDir( outDir )
    legendOrder = [ 'qcd', 'tt', 'ttX', 'singleTop', 'VV']
    plotName = inputFile.replace('.root', '')
    plotVaribles.makeStackPlot( histsInProcesses, dummySys, 'BDTScore', '1tau1l', outDir, legendOrder, False, plotName +'BDTTemplates', era, False, 100  )

    
def getHists(inputDir, inputFile):
    histsInProcesses = {}
    histSys = {}
    rootFile = ROOT.TFile( inputDir+inputFile, 'READ')
    for ipro in summedProcessList:
        ihistName = ipro+'_MVA_BDT'
        # print('trying to get hist: ', ihistName)
        if ( not rootFile.Get(ihistName) ):
            print( ipro, ' not in rootfile')
        else:
            ihist = rootFile.Get(ihistName)
            # ihist.Print()
            histsInProcesses[ipro] = ihist.Clone()
            histsInProcesses[ipro].Print()
            histsInProcesses[ipro].SetDirectory(0)#!!!very important to do this! if not, the hists will be destroyed after the rootfile closes
            # histSys[ipro]={}
    rootFile.Close()
    # print(histsInProcesses)
    return histsInProcesses, histSys
        
        
    



if __name__=='__main__':
    main()