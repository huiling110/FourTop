import usefulFunc as uf

from plotForFakeRate import plotEfficiency 

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v2baslineNoHLT_v52noHLTButPreSelection/mc/variableHists_v0triggerEff/'
    variableList = ['jets_HT']
    regionList = ['baseline1Muon', 'baseline1MuonAndHLT', 'baseline', 'baselineAndHLT']
    
    inputDirDic = uf.getDirDic(inputDir)
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
    era = uf.getEraFromDir(inputDir)
     
    sumProcessPerVar = {}
    sumProcessPerVarSys = {} 
    for ivar in variableList:
        sumProcessPerVar[ivar], sumProcessPerVarSys[ivar]= uf.getSummedHists( inputDirDic, regionList, ivar )
    print( sumProcessPerVar )
    
    #MC truth efficiency
    # ptBins = np.array( [500., ] )
    # variableDic = {
    #     'jets_HT'
    # } 
    MCTrueth_de = uf.addBGHist(sumProcessPerVar['jets_HT'], 'jets_HT', 'baseline', includeQCD=True)
    MCTrueth_nu = uf.addBGHist(sumProcessPerVar['jets_HT'], 'jets_HT', 'baselineAndHLT', includeQCD=True)
    # MCTrueth_de.Print()
    # MCTrueth_nu.Print()
    eff_MCTrueth = MCTrueth_de.Clone()
    eff_MCTrueth.Reset()
    eff_MCTrueth.Divide(MCTrueth_nu, MCTrueth_de)
    eff_MCTrueth.SetName('eff_MCTrueth')
    eff_MCTrueth.SetTitle('efficiency')
    eff_MCTrueth.Print()
    plotName = plotDir + 'MCTruethEff.png'
    plotEfficiency(MCTrueth_nu, MCTrueth_de, eff_MCTrueth, plotName, '2016postVFP', False)
     
    
    
    #MC reference efficiency
    
    
    #overlay of MC truth efficiency, MC reference efficiency and data reference efficiency



    
if __name__=='__main__':
    main()