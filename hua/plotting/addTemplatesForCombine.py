import ROOT

import ttttGlobleQuantity as gq
import usefulFunc as uf

channelDic = {
    '1tau0l': 'jets_bScore',
    '1tau1l': 'BDT',
}
def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1sysVariation1tau1l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1sysVariation1tau1l_30bins/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v1sysVariation1tau1l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v2traingWithBtag/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v3withBjetT/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v41tau0lGenTauSys/'
    channel = '1tau0l' # 1tau0l
    
    outDir = inputDir+'combine/'
    uf.checkMakeDir(outDir)
    templateFile = outDir + 'templatesForCombine1tau1l.root'
    outFile = ROOT.TFile(templateFile, 'RECREATE')
    
    # allSubPro = list(gq.histoGramPerSampleR.keys())
    allSubPro = list(gq.histoGramPerSample.keys())

    summedHistDicAllSys = {}
   
    ttttFile = ROOT.TFile(inputDir+'tttt.root', 'READ' )
    for key in ttttFile.GetListOfKeys():
        obj = key.ReadObj()
        # if isinstance(obj, ROOT.TH1):
        #     hist = obj.Clone()
        #     print("Found histogram:", hist.GetName())
        # print(obj.GetName())
        histName = obj.GetName()
        sysName = histName[histName.find('_')+1: ]
        print('sysName: ', sysName)
        if 'cutFlow' in sysName: continue
        summedHistDicAllSys[sysName] = {}
        obj.Delete()
    ttttFile.Close()
    print(summedHistDicAllSys)
    
    
    #loop through all subProcess
    # fakeDataHist = 
    for isub in allSubPro:
        if 'jetHT' in isub or 'singleMu' in isub: continue
        print(isub)
        ifile = inputDir + isub + '.root'
        iroot = ROOT.TFile(ifile, 'READ')
        if iroot.IsZombie():
            print('BAD!!!', ifile, 'not existing\n')
       
        for isysHist in summedHistDicAllSys.keys():
            print(isub+isysHist)
            # iHist = iroot.Get(isub+'_'+isysHist).Clone()
            iHist = iroot.Get(isub+'_'+isysHist).Clone()
            addHistToDic(iHist, summedHistDicAllSys[isysHist], isysHist, isub, outFile) 
       
        iroot.Close() 
    print(summedHistDicAllSys)
  
    # fakeData = addDataHist(summedHistDicAllSys['SR_BDT'], outFile)
    fakeData = addDataHist(summedHistDicAllSys['SR_' + channelDic[channel]], outFile, channel)
     
    outFile.Write()
    print('outFile here: ', outFile.GetName())
    outFile.Close()
    
    
def addDataHist(summedHistSR, outFile, channel):
    print('adding fake data hist from signal+bg MC')
    fakeData = summedHistSR[ list(summedHistSR.keys())[0]].Clone()
    fakeData.Reset()
    fakeData.SetDirectory(outFile)
    # fakeData.SetName('data_obs_SR_BDT')
    fakeData.SetName('data_obs_SR_'+channelDic[channel])
    for ipro in summedHistSR.keys():
        fakeData.Add(summedHistSR[ipro])
    return fakeData
        
         
    
    
def addHistToDic(iHist, summedHistDic, isysHist, isub, outFile):
    iHist.Sumw2()
    iHist.SetDirectory(outFile)
    summedName = gq.histoGramPerSample[isub]    
    if not gq.histoGramPerSample[isub] in summedHistDic.keys():
        #create first summedHist
        summedHistDic[summedName] = iHist
        summedHistDic[summedName].SetName(summedName+'_'+isysHist)
    else:
        #add hist to summedHist
        summedHistDic[summedName].Add(iHist)
        
        
       
if __name__=='__main__':
    main() 
    