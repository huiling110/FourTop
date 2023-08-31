import ROOT
import math

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
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v41tau0lGenTauSys/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v8tau1elCut_v60fixeJetBtagBug/mc/variableHists_v0trainingWithBtagShape/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v8tau1elCut_v60fixeJetBtagBug/mc/variableHists_v1traingWithBtagWP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3btagWeightGood_v61fixesLepRemovalBug/mc/variableHists_v1traingWithBtagWP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/mc/variableHists_v1traingWithBtagWP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1btagWPandRUpdated_v61fixesLepRemovalBug/mc/variableHists_v1traingWithBtagWP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022/v0baseline_v0preSel/mc/variableHists_v2SR1tau1l/' #!copied tttt.root from 2018
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/mc/variableHists_v4forBtagWPShape_WP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/mc/variableHists_v5forBtagWPShape_shape/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4forBDT1tau1lCut_v61fixesLepRemovalBug/mc/variableHists_v4forBtagWPShape_WP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4forBDT1tau1lCut_v61fixesLepRemovalBug/mc/variableHists_v5forBtagWPShape_shape/'
    
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_addTauGenNum_v61fixesLepRemovalBug/mc/variableHists_v0systematic1tau0l/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_addTauGenNum_v61fixesLepRemovalBug/mc/variableHists_v0systematic1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_addTauGenNum_v61fixesLepRemovalBug/mc/variableHists_v0systematic1tau0l/'
    
    
    channel = '1tau0l' # 1tau0l
    # channel = '1tau1l' # 1tau0l
    
    isRun3 = uf.isRun3(inputDir)
    era = uf.getEraFromDir(inputDir)
    print('isRun3=', isRun3)
    
    
    outDir = inputDir+'combine/'
    uf.checkMakeDir(outDir)
    # templateFile = outDir + 'templatesForCombine1tau1l.root'
    templateFile = outDir + 'templatesForCombine'+channel+'.root'
    outFile = ROOT.TFile(templateFile, 'RECREATE')
   
    if not isRun3:
        allSubList = gq.histoGramPerSample.keys()
    else:
        allSubList = gq.Run3Samples.keys()
    
    allSubPro = list(allSubList)

    summedHistDicAllSys = {}
   
    ttttFile = ROOT.TFile(inputDir+'tttt.root', 'READ' )
    for key in ttttFile.GetListOfKeys():
        obj = key.ReadObj()
        histName = obj.GetName()
        sysName = histName[histName.find('_')+1: ]
        # if 'Up' in sysName or 'Down' in sysName: continue #!!!temporidaily shup down for 2022
        if 'cutFlow' in sysName: continue
        print('sysName: ', sysName)
        summedHistDicAllSys[sysName] = {}
        obj.Delete()
    ttttFile.Close()
    print(summedHistDicAllSys)
    
    
    #loop through all subProcess
    for isub in allSubPro:
        if 'jetHT' in isub or 'singleMu' in isub or 'JetMet' in isub: continue
        print(isub)
        ifile = inputDir + isub + '.root'
        iroot = ROOT.TFile(ifile, 'READ')
        if iroot.IsZombie():
            print('BAD!!!', ifile, 'not existing\n')
       
        for isysHist in summedHistDicAllSys.keys():
            print(isub+isysHist)
            iHist = iroot.Get(isub+'_'+isysHist).Clone()
            addHistToDic(iHist, summedHistDicAllSys[isysHist], isysHist, isub, outFile, isRun3) 
       
        iroot.Close() 
    print(summedHistDicAllSys)
 
    if channel=='1tau0l':
        addFakeTauSys(outFile, channel, summedHistDicAllSys, era)
        print(summedHistDicAllSys)
    
    fakeData = addDataHist(summedHistDicAllSys['SR_' + channelDic[channel]], outFile, channel)
    
     
    outFile.Write()
    print('outFile here: ', outFile.GetName())
    outFile.Close()
    
def addFakeTauSys(outFile, channel, summedHistDicAllSys, era='2018'):
    print('start to add fake tau and sys into outfile')
    
    #!!! the fakeTau needs to be updated, the previous one is using wrong btag 
    fakeTauDic = {
        '2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1FR_application/1tau0l_templatesForCombine/templates.root',
        '2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v57ovelapWithTausF/mc/variableHists_v1FR_application/1tau0l_templatesForCombine/templates.root',
        '2016': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1FR_application/1tau0l_templatesForCombine/templates.root',
    }
    # tempatesWithFT = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v57ovelapWithTausF/mc/variableHists_v1FR_application/1tau0l_templatesForCombine/templates.root'
    #/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1FR_application/1tau0l_templatesForCombine
    templatesWithFT = fakeTauDic[era]
    print('using fakeTau file: ', templatesWithFT)
    FTFile = ROOT.TFile(templatesWithFT, 'READ')
    fakeTau = FTFile.Get('fakeTau_jets_bScore')
    fakeTau_up = FTFile.Get('fakeTau_jets_bScore_FR_up')
    fakeTau_down = FTFile.Get('fakeTau_jets_bScore_FR_down')
    fakeTau_up.SetName('fakeTau_CMS_tttt_FR_shape_stats_'+era+'Up_' + channelDic[channel])
    fakeTau_down.SetName('fakeTau_CMS_tttt_FR_shape_stats_'+ era+'Down_'+channelDic[channel])
    fakeTau.SetName('fakeTau_SR_jets_bScore')
    fakeTau.SetDirectory(outFile)
    fakeTau_up.SetDirectory(outFile)
    fakeTau_down.SetDirectory(outFile)
    if channel=='1tau0l':
        summedHistDicAllSys['SR_' + channelDic[channel]] ['faketau']= fakeTau
    

    
def addDataHist(summedHistSR, outFile, channel):
    print('adding fake data hist from signal+bg MC......')
    fakeData = summedHistSR[ list(summedHistSR.keys())[0]].Clone()
    fakeData.Reset()
    fakeData.SetDirectory(outFile)
    fakeData.SetName('data_obs_SR_'+channelDic[channel])
    for ipro in summedHistSR.keys():
        if ipro=='qcd': continue
        print('add fakeData: ',ipro)
        fakeData.Add(summedHistSR[ipro])

    for bin in range(1, fakeData.GetNbinsX()+1):
        fakeData.SetBinError(bin, math.sqrt(bin))
        
    print('done adding fake data............\n')
    return fakeData
        
         
    
    
def addHistToDic(iHist, summedHistDic, isysHist, isub, outFile, isRun3=False):
    iHist.Sumw2()
    iHist.SetDirectory(outFile)
    if not isRun3:
        summedName = gq.histoGramPerSample[isub]    
    else:
       summedName = gq.Run3Samples[isub] 
    # if not gq.histoGramPerSample[isub] in summedHistDic.keys():
    if not summedName in summedHistDic.keys():
        #create first summedHist
        summedHistDic[summedName] = iHist
        summedHistDic[summedName].SetName(summedName+'_'+isysHist)
    else:
        #add hist to summedHist
        summedHistDic[summedName].Add(iHist)
        
        
       
if __name__=='__main__':
    main() 
    