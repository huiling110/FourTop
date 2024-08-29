import usefulFunc as uf

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/variableHists_v1BDT1tau1l_evenBin/'
    
    
    era = uf.getEraFromDir(inputDir)
    print('era=', era)
    inputDirDic = uf.getInputDicNew( inputDir)
    uf.checkMakeDir( inputDirDic['mc']+'results/')
    sigHist, bgHist = getSigBgHist(inputDirDic,  era)

def getSigBgHist(inputDirDic,  era):
    sumProList = ['jetHT','tt', 'ttX', 'singleTop', 'WJets', 'tttt'] #1tau1l
    sumProcessPerVar, sumProcessPerVarSys = uf.getSumHist(inputDirDic, ['1tau1lSR'], sumProList, {}, ['BDT'], era, False )#sumProcessPerVar[ivar][region][sumPro]
    
    sigHist = sumProcessPerVar['BDT']['1tau1lSR']['tttt']
    bgHist = uf.addBGHist(sumProcessPerVar['BDT'], '1tau1lSR')
    sigHist.Print()
    bgHist.Print()
    
    return sigHist, bgHist

if __name__ == '__main__':
    main()