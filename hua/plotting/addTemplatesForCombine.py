import ROOT

import ttttGlobleQuantity as gq
import usefulFunc as uf

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1sysVariation1tau1l/'
    
    outDir = inputDir+'combine/'
    uf.checkMakeDir(outDir)
    templateFile = outDir + 'templatesForCombine1tau1l.root'
    outFile = ROOT.TFile(templateFile, 'RECREATE')
    
    allSubPro = list(gq.histoGramPerSampleR.keys())

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
            addHistToDic(iHist, summedHistDicAllSys[isysHist], isysHist, isub) 
      
       
        iroot.Close() 
        
        
    print(summedHistDicAllSys)
    
def addHistToDic(iHist, summedHistDic, isysHist, isub):
    iHist.Sumw2()
    iHist.SetDirectory(0)
    summedName = gq.histoGramPerSampleR[isub]    
    if not gq.histoGramPerSampleR[isub] in summedHistDic.keys():
        #create first summedHist
        summedHistDic[summedName] = iHist
        summedHistDic[summedName].SetName(summedName+'_'+isysHist)
    else:
        #add hist to summedHist
        summedHistDic[summedName].Add(iHist)
        
        
       
if __name__=='__main__':
    main() 
    