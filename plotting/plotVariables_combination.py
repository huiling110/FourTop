import usefulFunc as uf
import ttttGlobleQuantity as gq                                
import plotVaribles as pl

def main():
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE2/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE2/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE2/'
    
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/'
    
    inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/'
    inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/'
    inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/'
    inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/'
    
    channel = '1tau1l'
    regionList = ['1tau1lCR1', '1tau1lCR2', '1tau1lSR']
    
    # channel = '1tau2l'
    # regionList = ['1tau2lSR', '1tau2lCR3'] 
    
    variables = ['BDT']
    
    sumPros = gq.proChannelDic[channel]
    # sumPros.append('jetHT')
    print(sumPros)
    
    sumProHists2018, sumProHistsSys2018 = getSumHistPerYear(inputDir2018, regionList, variables, sumPros)
    sumProHists2017, sumProHistsSys2017 = getSumHistPerYear(inputDir2017, regionList, variables, sumPros)
    sumProHists2016preVFP, sumProHistsSys2016preVFP = getSumHistPerYear(inputDir2016preVFP, regionList, variables, sumPros)
    sumProHists2016postVFP, sumProHistsSys2016postVFP = getSumHistPerYear(inputDir2016postVFP, regionList, variables, sumPros)
    
    
    combineHists = {}
    for ire in sumProHists2018['BDT'].keys():
        print(ire)
        combineHists[ire] = {}
        for isumPro in sumProHists2018['BDT'][ire].keys():
            # sumProHists2018['BDT'][ire][isumPro].Print()
            combineHists[ire][isumPro] = sumProHists2018['BDT'][ire][isumPro].Clone()
            if not uf.isData(isumPro):
                combineHists[ire][isumPro].Add(sumProHists2017['BDT'][ire][isumPro])
                combineHists[ire][isumPro].Add(sumProHists2016preVFP['BDT'][ire][isumPro])
                combineHists[ire][isumPro].Add(sumProHists2016postVFP['BDT'][ire][isumPro])
            else:
                combineHists[ire][isumPro]
                uf.addDataHist(combineHists[ire][isumPro], sumProHists2017['BDT'][ire][isumPro])
                uf.addDataHist(combineHists[ire][isumPro], sumProHists2016preVFP['BDT'][ire][isumPro])
                uf.addDataHist(combineHists[ire][isumPro], sumProHists2016postVFP['BDT'][ire][isumPro])
    
    plotDir = inputDir2018+'results/'
    uf.checkMakeDir(plotDir)
    # plotName = 'combination' 
    plotName = 'combination_fixedDataError' 
    for ire in combineHists.keys():
        pl.makeStackPlotNew(combineHists[ire], sumPros, 'BDT', ire, plotDir, False, plotName, 'Run2', True, 100, True, True, True, False ) 
    
def getSumHistPerYear(inputDir2018, regionList, variables, sumPros):
    era = uf.getEraFromDir(inputDir2018)
    print('era=', era)
    # isRun3 = uf.isRun3(inputDir2018)
    inputDirDic = uf.getInputDicNew( inputDir2018)
    uf.checkMakeDir( inputDirDic['mc']+'results/')
    sumProHists, sumProHistsSys = uf.getSumHist(inputDirDic, regionList, sumPros,{},  variables, era, False)
    return sumProHists, sumProHistsSys
    
    
    
if __name__ == '__main__':
    main()