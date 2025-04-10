import ROOT
import usefulFunc as uf
import writeDatacard as wd
import pl as pl


def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV2/'
    channel = '1tau1l'
    variables = ['BDT']
    regionList = ['1tau1lSR', '1tau1lCR12']
    
    
    ifFakeTau = True
    ifMCFTau = True #!


    era = uf.getEraFromDir(inputDir)
    inputDirDic = uf.getInputDicNew( inputDir)

    sumProList = pl.getSumList(channel, ifFakeTau, False, ifMCFTau, True)    
    print('sumProList:', sumProList) 
    sumProSys = pl.getSysDicPL(True, channel, era, True)    
    
    
    sumProcessPerVar, sumProcessPerVarSys = uf.getSumHist(inputDirDic, regionList, sumProList, sumProSys, variables, era, False , False, ifMCFTau)#sumProcessPerVar[ivar][region][sumPro]
    
    #add fake data for SR
    for ivar in variables:
        for region in regionList:
            dataHist = None
            if 'SR' in region:
                for sumPro in sumProList:
                    if uf.isData(sumPro): continue
                    print('fake data: ', sumPro)
                    if dataHist == None:
                        dataHist = sumProcessPerVar[ivar][region][sumPro].Clone()  
                        dataHist.SetName(dataHist.GetName().replace(sumPro, 'data_obs'))
                    else:
                        dataHist.Add(sumProcessPerVar[ivar][region][sumPro])    # 
                sumProcessPerVar[ivar][region]['jetHT'] = dataHist
                print('fake data hist:', dataHist.GetName())
            dataName = sumProcessPerVar[ivar][region]['jetHT'].GetName().replace('jetHT', 'data_obs')
            sumProcessPerVar[ivar][region]['jetHT'].SetName(dataName)
          
             
            
                    
                    
                    
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
    
    
    
    
if __name__ == "__main__":
    main()
    
