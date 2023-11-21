import ROOT
import math

import ttttGlobleQuantity as gq
import usefulFunc as uf

channelDic = {
    '1tau0l': 'jets_bScore',
    # '1tau0l': 'bjetsM_invariantMass',
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
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_addTauGenNum_v61fixesLepRemovalBug/mc/variableHists_v0systematic1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_addTauGenNum_v61fixesLepRemovalBug/mc/variableHists_v0systematic1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0BasicSystematic/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0systematic1tau0l_bScore/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0systematic1tau0lBjet3_bScore/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0systematic1tau0lBjet3_bHT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0systematic1tau0lBjet3_bMass/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0systematic1tau0l_bMass/'
    channel = '1tau0l' # 1tau0l
    # channel = '1tau1l' 
   
   
   
    
    isRun3 = uf.isRun3(inputDir)
    era = uf.getEraFromDir(inputDir)
    print('isRun3=', isRun3)
    
    
    outDir = inputDir+'combine/'
    uf.checkMakeDir(outDir)
    # templateFile = outDir + 'templatesForCombine'+channel+'.root'
    templateFile = outDir + 'templatesForCombine'+channel+'_test.root'
    outFile = ROOT.TFile(templateFile, 'RECREATE')
   
    if not isRun3:
        allSubList = gq.histoGramPerSample.keys()
    else:
        allSubList = gq.Run3Samples.keys()
    allSubPro = list(allSubList)

    summedHistDicAllSys = {}
    #summedHistDicAllSys[sys][sumPro]
    getSumSys(summedHistDicAllSys, inputDir) 
    
   
    getSysHist(summedHistDicAllSys, allSubPro, inputDir, outFile, isRun3)
 
    if channel=='1tau0l':
        addFakeTauSys(outFile, channel, summedHistDicAllSys, era)
        print(summedHistDicAllSys)
    
    fakeData = addDataHist(summedHistDicAllSys['SR_' + channelDic[channel]], outFile, channel)
    
    
    #only 1tau1l for now 
    jerDic = {
        '2018': ['/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_JERUp/mc/variableHists_v1JERup/', '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_JERDown/mc/variableHists_v1JERdown/', 'JER'],
    }
    # addJERSys(outFile, summedHistDicAllSys, allSubPro, jerDic, era, isRun3)
    jesDic = {
        '2018': ['/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_JESUp/mc/variableHists_v1JESUp/', '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_JESDown/mc/variableHists_v1JESDown/', 'JES'],
    }
    # addJERSys(outFile, summedHistDicAllSys, allSubPro, jesDic, era, isRun3)
    jesDic = {
        '2018': ['/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_TESUp/mc/variableHists_v1TESUp/', '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_TESDown/mc/variableHists_v1TESDown/', 'TES'],
    }
    # addJERSys(outFile, summedHistDicAllSys, allSubPro, jesDic, era, isRun3)
    
     
    outFile.Write()
    print('outFile here: ', outFile.GetName())
    outFile.Close()
  
def getSysHist(summedHistDicAllSys, allSubPro,inputDir, outFile, isRun3=False):
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
      
   
def getSumSys(summedHistDicAllSys, inputDir):
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

def addJERSys(outFile, summedHistDicAllSys, allSubPro, jerDic, era = '2018', isRun3=False):
    print('start to add sys hists') 
    # jerDic = {
    #     '2018': ['/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_JERUp/mc/variableHists_v1JERup/', '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v64PreAndHLTSel_JERDown/mc/variableHists_v1JERdown/'],
    # }
    templatesWithJER = jerDic[era]
    sysName = templatesWithJER[2]
    print('using ', sysName, ' template file: ', templatesWithJER[0], '\n', templatesWithJER[1])
    # summedHistDicAllSys['JER_up'] = {}
    # summedHistDicAllSys['JER_down'] = {}
    summedHistDicAllSys[ sysName+'_up'] = {}
    summedHistDicAllSys[ sysName+'_down'] = {}
    for isub in allSubPro:
        if 'jetHT' in isub or 'singleMu' in isub or 'JetMet' in isub: continue
        ifileUp = templatesWithJER[0] + isub + '.root'
        ifileDown = templatesWithJER[1] + isub + '.root'
        isubHistUp = uf.getHistFromFile(ifileUp, [isub +'_SR_BDT'])[0]
        isubHistDown = uf.getHistFromFile(ifileDown, [isub +'_SR_BDT'])[0]
        # addHistToDic(isubHistUp,summedHistDicAllSys['JER_up'], 'CMS_JER_'+era+'Up_BDT', isub, outFile, isRun3 )
        # addHistToDic(isubHistDown,summedHistDicAllSys['JER_down'], 'CMS_JER_'+era+'Down_BDT', isub, outFile, isRun3 )
        addHistToDic(isubHistUp,summedHistDicAllSys[sysName+'_up'], 'CMS_'+sysName+'_'+era+'Up_BDT', isub, outFile, isRun3 )
        addHistToDic(isubHistDown,summedHistDicAllSys[sysName+'_down'], 'CMS_'+sysName+'_'+era+'Down_BDT', isub, outFile, isRun3 )
    print(summedHistDicAllSys)
    print('done adding sys templates\n')

   
    
def addFakeTauSys(outFile, channel, summedHistDicAllSys, era='2018'):
    print('start to add fake tau and sys into outfile')
    
    #!!! the fakeTau needs to be updated, the previous one is using wrong btag 
    fakeTauDic = {
        # '2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1FR_application/1tau0l_templatesForCombine/templates.root',
        '2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v1FR_application_correctWeight/1tau0l_templatesForCombine/templates.root', #just different binning, bjets>=2
        # '2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v1FR_application_correctWeight_bjets3/1tau0l_templatesForCombine/templates.root', #just different binning
        '2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v57ovelapWithTausF/mc/variableHists_v1FR_application/1tau0l_templatesForCombine/templates.root',
        '2016': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1FR_application/1tau0l_templatesForCombine/templates.root',
    }
    # tempatesWithFT = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v57ovelapWithTausF/mc/variableHists_v1FR_application/1tau0l_templatesForCombine/templates.root'
    #/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1FR_application/1tau0l_templatesForCombine
    templatesWithFT = fakeTauDic[era]
    print('using fakeTau file: ', templatesWithFT)
    FTFile = ROOT.TFile(templatesWithFT, 'READ')
    variable = channelDic[channel]
    # fakeTau = FTFile.Get('fakeTau_jets_bScore')
    # fakeTau_up = FTFile.Get('fakeTau_jets_bScore_FR_up')
    # fakeTau_down = FTFile.Get('fakeTau_jets_bScore_FR_down')
    fakeTau = FTFile.Get('fakeTau_'+channelDic[channel])
    fakeTau_up = FTFile.Get('fakeTau_'+channelDic[channel]+'_FR_up')
    fakeTau_down = FTFile.Get('fakeTau_'+channelDic[channel]+'_FR_down')
    fakeTau_up.SetName('fakeTau_CMS_tttt_FR_shape_stats_'+era+'Up_' + channelDic[channel])
    fakeTau_down.SetName('fakeTau_CMS_tttt_FR_shape_stats_'+ era+'Down_'+channelDic[channel])
    fakeTau.SetName('fakeTau_SR_'+variable)
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
    