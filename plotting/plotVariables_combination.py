import usefulFunc as uf
import ttttGlobleQuantity as gq                                
import plotVaribles as pl

def main():
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE2/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE2/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE2/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/'
    # channel = '1tau1l'
    # regionList = ['1tau1lCR12', '1tau1lSR']
   
   
    
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/'
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l_newMCSample/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l/'
    # channel = '1tau2l'
    # regionList = ['1tau2lSR', '1tau2lCR3'] 
    
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/'
    
    
    
    
    #1tau0l
    # inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputs/'
    # inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputsWith2018train/'
    # inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputsWith2018train/'
    # inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputsWith2018train/'
    inputDir2017 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/'
    inputDir2016postVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/' #!problem with fakeTau_MC 
    inputDir2016preVFP = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/'
    inputDir2018 = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/'
    channel = '1tau0l'
    regionList = ['1tau0lSR', '1tau0lCRMR', '1tau0lVR']
    
    
    
    
    
    variables = ['BDT']
    
    sumPros = gq.proChannelDic[channel]
    print(sumPros)
    
    sumProHists2018, sumProHistsSys2018 = getSumHistPerYear(inputDir2018, regionList, variables, sumPros, channel)
    sumProHists2017, sumProHistsSys2017 = getSumHistPerYear(inputDir2017, regionList, variables,  sumPros, channel)
    sumProHists2016preVFP, sumProHistsSys2016preVFP = getSumHistPerYear(inputDir2016preVFP, regionList, variables,  sumPros, channel)
    sumProHists2016postVFP, sumProHistsSys2016postVFP = getSumHistPerYear(inputDir2016postVFP, regionList, variables,  sumPros, channel)
    
    
    combineHists = {}
    combineHistSys = {}
    for ire in sumProHists2018['BDT'].keys():
        print(ire)
        combineHists[ire] = {}
        combineHistSys[ire] = {}
        for isumPro in sumProHists2018['BDT'][ire].keys():
            # sumProHists2018['BDT'][ire][isumPro].Print()
            combineHists[ire][isumPro] = sumProHists2018['BDT'][ire][isumPro].Clone()
            combineHistSys[ire][isumPro] = {}
            if not uf.isData(isumPro):
                combineHists[ire][isumPro].Add(sumProHists2017['BDT'][ire][isumPro])
                combineHists[ire][isumPro].Add(sumProHists2016preVFP['BDT'][ire][isumPro])
                combineHists[ire][isumPro].Add(sumProHists2016postVFP['BDT'][ire][isumPro])
                combineHistSys[ire][isumPro] = addSys(sumProHistsSys2018['BDT'][ire][isumPro], sumProHistsSys2017['BDT'][ire][isumPro], sumProHistsSys2016preVFP['BDT'][ire][isumPro], sumProHistsSys2016postVFP['BDT'][ire][isumPro])
            else:
                combineHists[ire][isumPro]
                uf.addDataHist(combineHists[ire][isumPro], sumProHists2017['BDT'][ire][isumPro])
                uf.addDataHist(combineHists[ire][isumPro], sumProHists2016preVFP['BDT'][ire][isumPro])
                uf.addDataHist(combineHists[ire][isumPro], sumProHists2016postVFP['BDT'][ire][isumPro])
    
    plotDir = inputDir2018+'results/'
    uf.checkMakeDir(plotDir)
    plotName = 'combination_withSys' 
    # plotName = 'combination_fixedDataError' 
    for ire in combineHists.keys():
        # pl.makeStackPlotNew(combineHists[ire], sumPros, 'BDT', ire, plotDir, False, plotName, 'Run2', True, 100, True, True, True, False ) 
        pl.makeStackPlotNew(combineHists[ire], sumPros, 'BDT', ire, plotDir, False, plotName, 'Run2', True, 100, True, True, True, False, combineHistSys[ire], True ) 
   
def addSys(sumProHistsSys2018, sumProHistsSys2017, sumProHistsSys2016preVFP, sumProHistsSys2016postVFP) :
    sumSys = {}
    for isys, ihist in sumProHistsSys2018.items():
        isys2017 = isys.replace('2018', '2017')
        isys2016preVFP = isys.replace('2018', '2016preVFP')
        isys2016postVFP = isys.replace('2018', '2016postVFP')
        sumSys[isys] = sumProHistsSys2018[isys].Clone()
        sumSys[isys].Add(sumProHistsSys2017[isys2017])
        sumSys[isys].Add(sumProHistsSys2016postVFP[isys2016postVFP])
        sumSys[isys].Add(sumProHistsSys2016preVFP[isys2016preVFP])
    return sumSys 
        
    
    
def getSumHistPerYear(inputDir2018, regionList, variables, sumPros, channel):
    era = uf.getEraFromDir(inputDir2018)
    print('era=', era)
    # isRun3 = uf.isRun3(inputDir2018)
    inputDirDic = uf.getInputDicNew( inputDir2018)
    uf.checkMakeDir( inputDirDic['mc']+'results/')
    
    sumProSys = pl.getSysDicPL(True, channel, era)    
    # sumProHists, sumProHistsSys = uf.getSumHist(inputDirDic, regionList, sumPros,{},  variables, era, False)
    sumProHists, sumProHistsSys = uf.getSumHist(inputDirDic, regionList, sumPros, sumProSys,  variables, era, False)
    return sumProHists, sumProHistsSys
    
    
    
if __name__ == '__main__':
    main()