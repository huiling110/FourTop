import usefulFunc as uf
import ttttGlobleQuantity as gq
import writeDatacard as wd

#!copied from inputMAP_MV.H
JESVariationList = [
    "AbsoluteMPFBias_AK4PFchs",
    "AbsoluteScale_AK4PFchs",
    "AbsoluteStat_AK4PFchs",
    "FlavorQCD_AK4PFchs",
    "Fragmentation_AK4PFchs",
    "PileUpDataMC_AK4PFchs",
    "PileUpPtBB_AK4PFchs",
    "PileUpPtEC1_AK4PFchs",
    "PileUpPtEC2_AK4PFchs",
    "PileUpPtHF_AK4PFchs",
    "PileUpPtRef_AK4PFchs",
    "RelativeFSR_AK4PFchs",
    "RelativeJEREC1_AK4PFchs",
    "RelativeJEREC2_AK4PFchs",
    "RelativeJERHF_AK4PFchs",
    "RelativePtBB_AK4PFchs",
    "RelativePtEC1_AK4PFchs",
    "RelativePtEC2_AK4PFchs",
    "RelativePtHF_AK4PFchs",
    "RelativeBal_AK4PFchs",
    "RelativeSample_AK4PFchs",
    "RelativeStatEC_AK4PFchs",
    "RelativeStatFSR_AK4PFchs",
    "RelativeStatHF_AK4PFchs",
    "SinglePionECAL_AK4PFchs",
    "SinglePionHCAL_AK4PFchs",
    "TimePtEta_AK4PFchs",
]

#add JES variation templates to WH root files 
def main():
    nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/'    
       
    inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/'
    inVersion = 'v89HadroPre_JESPt22'#!!!for JES variation only
    outVersion = 'v0baselineHadro'
    channel = '1tau1l'
    
     
    era = uf.getEraFromDir(nominalDir)
    sumProcesses = gq.proChannelDic[channel]
    if 'jetHT' in sumProcesses:
        sumProcesses.remove('jetHT')
    if 'leptonSum' in sumProcesses:
        sumProcesses.remove('leptonSum')
    if 'fakeTau' in sumProcesses:
        sumProcesses.remove('fakeTau')
    if 'fakeLepton' in sumProcesses:
        sumProcesses.remove('fakeLepton')
        
    allSubProcesses = uf.getAllSubPro(era, sumProcesses, False) 
    print(allSubProcesses)
     
    JESListUp = {}# 'tttt' = [jestVariationHist]
    JESListDown = {}
    for isub in allSubProcesses:
        JESListUp[isub] = []
        JESListDown[isub] = []
    
     
    regionList = ['1tau1lSR', '1tau1lCR12']#
    # for i in range(0, 27):
    for i in range(0, 1):
        JESUpDir, JESDownDir = uf.getInputDirUpDown(inVersion, outVersion, i)
        JESUpDir = f'{JESUpDir}/mc/variableHists_v0BDT1tau1l/'
        JESDownDir = f'{JESDownDir}/mc/variableHists_v0BDT1tau1l/'
        print(JESUpDir, JESDownDir)  
        iJESVariation = JESVariationList[i]
        ifCorrelated = wd.MCSys[iJESVariation][0]
        if ifCorrelated:
            JESUpName =  f'{channel}SR_CMS_JES_{iJESVariation}Up'        
            JESDownName =  f'{channel}SR_CMS_JES_{iJESVariation}Down'        
        else:
            JESUpName =  f'{channel}SR_CMS_JES_{iJESVariation}_{era}Up'        
            JESDownName =  f'{channel}SR_CMS_JES_{iJESVariation}_{era}Down'        
        getJESHistForDir(JESUpDir, JESDownDir, JESListUp, JESListDown, JESUpName, JESDownName, regionList) 
          
def getJESHistForDir(JESUpDir, JESDownDir, JESListUP, JESListDown, JESUpName, JESDownName, regionList):
    for isub in JESListUP.keys():
        histList = [f'{isub}_{ire}_BDT' for ire in regionList]
        JESHistsNameUp = [f'{isub}_{ire}_{JESUpName}_BDT' for ire in regionList] 
        JESHistsNameDown = [f'{isub}_{ire}_{JESDownName}_BDT' for ire in regionList] 
        gotHistsUp = uf.getHistFromFile(f'{JESUpDir}{isub}.root', histList)   
        gotHistsDown = uf.getHistFromFile(f'{JESDownDir}{isub}.root', histList)   
        # for iHist in gotHists:
        for ire, iHist in enumerate(regionList):
            gotHistsUp[ire].SetName(JESHistsNameUp[ire])
            gotHistsDown[ire].SetName(JESHistsNameDown[ire])
            JESListUP[isub].append(gotHistsUp[ire])
            JESListDown[isub].append(gotHistsDown[ire])
        
    print(JESListUP) 
        
        
if __name__=='__main__':
    main()