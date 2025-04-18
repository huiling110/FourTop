import ROOT
import usefulFunc as uf
import writeDatacard as wd
import pl as pl


def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV2/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    channel = '1tau1l'
    variables = ['BDT']
    regionList = ['1tau1lSR', '1tau1lCR12']
    
    #1tau0l
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # channel = '1tau0l'
    # variables = ['BDT']
    # regionList = ['1tau0lSR', '1tau0lCRMR', '1tau0lVR']
    
    #1tau2l 
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # channel = '1tau2l'
    # variables = ['BDT']
    # regionList = ['1tau2lSR', '1tau2lCR3']
    
    
    ifFakeTau = True
    ifMCFTau = True #!
    # ifMCFTau = False #!


    era = uf.getEraFromDir(inputDir)
    inputDirDic = uf.getInputDicNew( inputDir)
    is1tau2l = True if channel == '1tau2l' else False

    sumProList = pl.getSumList(channel, ifFakeTau, False, ifMCFTau, True)    
    print('sumProList:', sumProList) 
    sumProSys = pl.getSysDicPL(sumProList, True, channel, era, True)    
    
    
    sumProcessPerVar, sumProcessPerVarSys = uf.getSumHist(inputDirDic, regionList, sumProList, sumProSys, variables, era, False , False, ifMCFTau)#sumProcessPerVar[ivar][region][sumPro]
    
    dataName = 'leptonSum' if is1tau2l else 'jetHT' 
    #add fake data for SR
    for ivar in variables:
        for region in regionList:
            dataHist = None
            if 'SR' in region:
                for sumPro in sumProList:
                    if uf.isData(sumPro): continue
                    print('fake data: ', sumPro)
                    
                    hist = sumProcessPerVar[ivar][region][sumPro]
                    resetNegtiveBins(hist)
                    
                    
                    if dataHist == None:
                        dataHist = sumProcessPerVar[ivar][region][sumPro].Clone()  
                        dataHist.SetName(dataHist.GetName().replace(sumPro, 'data_obs'))
                    else:
                        dataHist.Add(sumProcessPerVar[ivar][region][sumPro])    # some process has negative bins, set them to 0 
                sumProcessPerVar[ivar][region][dataName] = dataHist
                print('fake data hist:', dataHist.GetName())
            dataHistName = sumProcessPerVar[ivar][region][dataName].GetName().replace(dataName, 'data_obs')
            sumProcessPerVar[ivar][region][dataName].SetName(dataHistName)
          
             
            
                    
                    
                    
    outDir = inputDir+'combine/'
    uf.checkMakeDir(outDir)
    templateFile = outDir + 'templatesForCombine'+channel+'_new.root'
    outFile = ROOT.TFile(templateFile, 'RECREATE')
    
    #for all hists in sumProcessPerVar and sumProcessPerVarSys, save them to the outFile
    for ivar in variables:
        for region in regionList:
            for sumPro in sumProList:
                if sumPro in sumProcessPerVar[ivar][region]:
                    hist = sumProcessPerVar[ivar][region][sumPro]
                    hist.Write(hist.GetName())
                if sumPro in sumProcessPerVarSys[ivar][region]:
                    for sys in sumProcessPerVarSys[ivar][region][sumPro]:
                        hist = sumProcessPerVarSys[ivar][region][sumPro][sys]
                        #! rename process-uncorrelated sys for combine 
                        sysName = sys.replace('_up', '').replace('_down', '') 
                        sysName = sysName.replace('_2018', '').replace('_2017', '').replace('_2016preVFP', '').replace('_2016postVFP', '')
                        #sysName is sys remove '_up" or '_down'
                        if not wd.MCSys[sysName][3]: # process-uncorrelated sys 
                            sysNameNew = sysName + '_' + sumPro
                            hist.SetName(hist.GetName().replace(sysName, sysNameNew))
                            
                        hist.Write(hist.GetName())
    outFile.Write()
    outFile.Close()
    print('template file created:', templateFile)
    

def resetNegtiveBins(hist):
    for i in range(1, hist.GetNbinsX()+1):
        if hist.GetBinContent(i) < 0.:
            hist.SetBinContent(i, 0)
            hist.SetBinError(i, 0)
    return hist
    
    
if __name__ == "__main__":
    main()
    
