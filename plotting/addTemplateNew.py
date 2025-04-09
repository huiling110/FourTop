import ROOT
import usefulFunc as uf
import pl as pl


def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeT/'
    channel = '1tau1l'
    variables = ['BDT']
    regionList = ['1tau1lSR', '1tau1lCR12']
    
    
    ifFakeTau = True
    ifMCFTau = True #!


    era = uf.getEraFromDir(inputDir)
    inputDirDic = uf.getInputDicNew( inputDir)

    sumProList = pl.getSumList(channel, ifFakeTau, False, ifMCFTau)    
    
    sumProSys = pl.getSysDicPL(True, channel, era)    
    
    
    sumProcessPerVar, sumProcessPerVarSys = uf.getSumHist(inputDirDic, regionList, sumProList, sumProSys, variables, era, False , False, ifMCFTau)#sumProcessPerVar[ivar][region][sumPro]
    
    # 
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
                        hist.Write(hist.GetName())
    outFile.Write()
    outFile.Close()
    print('template file created:', templateFile)
    
    
    
    
if __name__ == "__main__":
    main()
    
