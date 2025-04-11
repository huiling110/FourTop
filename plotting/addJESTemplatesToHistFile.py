import ROOT
import usefulFunc as uf
import ttttGlobleQuantity as gq
import writeDatacard as wd

#add JES variation templates to WH root files 
#add JER variation templetas to WH root files
#add TES variation templates to WH root files
def main():
    #!1tau1l
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sys/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sys/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sys/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sys/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV2/'
    channel = '1tau1l'
    regionList = ['1tau1lSR', '1tau1lCR12']#
    variables = ['BDT']
    # variables = ['jets_num', 'jets_HT', 'jets_1pt', 'jets_6pt', 'jets_7pt', 'bjetsM_num', 'bjetsT_num', 'bjetsM_HT', 'tausT_1decayMode', 'tausT_1pt', 'tausT_1lepton1_charge', 'lepTopMVAT_1pt', 'lepTopMVAT_1eta']
    
    #1tau2l   
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/mc/variableHists_v0BDT1tau2l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'#!Replaced the old one with data-driven fake tau
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'#!Replaced the old one with data-driven fake tau
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'#!Replaced the old one with data-driven fake tau
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'#!Replaced the old one with data-driven fake tau
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lNewCR/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lNewCR/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lNewCR/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lNewCR/'
    # channel = '1tau2l'
    # variables = ['BDT']
    # regionList = ['1tau2lSR', '1tau2lCR3']
   
    #!1tau0l 
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/'    
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/'    
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/'    
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/'    
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sysV2/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sysV2/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sysV2/'
    # nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sysV2/'
    # variables = ['BDT']
    # variables = ['jets_num', 'jets_HT',  'jets_6pt', 'bjetsM_num','jets_bScore', 'tausF_1decayMode',  'tausF_1jetPt', 'tausF_1jetEta', 'tausF_1prongNum', 'tausF_num']#!fake rate validation
    # channel = '1tau0l'
    # regionList = ['1tau0lSR', '1tau0lCRMR', '1tau0lVR']
    
    
    ifMCFTau = True 
    
     
    era = uf.getEraFromDir(nominalDir)
    allSubProcesses = getMCSubPro(channel, era)
    
    
    
    # addJESToFile(allSubProcesses, channel, regionList, era, nominalDir, variables)#!make sure JES OS dir with _JESPt22 in the end
    # addJESToFile(allSubProcesses, channel, regionList, era, nominalDir, variables, '_MCFT')#!make sure JES OS dir with _JESPt22 in the end
    addJESToFile(allSubProcesses, channel, regionList, era, nominalDir, variables, '_NotMCFT')#!make sure JES OS dir with _JESPt22 in the end
    # addJERToFile(allSubProcesses, regionList, era, nominalDir, variables)
    
    # addMETToFile(allSubProcesses, regionList, era, nominalDir)
    # addEESToFile(allSubProcesses, regionList, era, nominalDir)
    # addTESToFile(allSubProcesses, regionList, era, nominalDir)
    
    
    
     
def addTESToFile(allSubProcesses, regionList, era, nominalDir):
    for i in (0, 1, 10, 11):
        # iTESUpDir = f'{TESbase}_TESdm{i}Up/mc/variableHists_v0BDT{channel}/'
        # iTESDownDir = f'{TESbase}_TESdm{i}Down/mc/variableHists_v0BDT{channel}/'
        iTESUpDir = nominalDir.replace('/mc/', f'_TESdm{i}Up/mc/')
        iTESDownDir = nominalDir.replace('/mc/', f'_TESdm{i}Down/mc/')
        # TESName = f'CMS_tau_TES_dm{i}' 
        TESName = f'CMS_scale_t_DM{i}'
        addUpDownToFile(allSubProcesses, regionList, era, nominalDir, iTESUpDir, iTESDownDir, TESName)
         
    
    
def addJERToFile(allSubProcesses, regionList, era, nominalDir, variables=['BDT']):
    JERUpDir = nominalDir.replace('/mc/', '_JERUp/mc/')
    JERDownDir = nominalDir.replace('/mc/', '_JERDown/mc/')
    # name = 'CMS_JER'
    name = 'CMS_res_j'
    for ivariable in variables:
        addUpDownToFile(allSubProcesses, regionList, era, nominalDir, JERUpDir, JERDownDir, name, ivariable)
    
def addMETToFile(allSubProcesses, regionList, era, nominalDir):
    METUpDir = nominalDir.replace('/mc/', '_METUp/mc/')
    METDownDir = nominalDir.replace('/mc/', '_METDown/mc/')
    # name = 'CMS_MET_unclusteredEnergy' 
    name = 'CMS_scale_met_unclustered_energy'
    addUpDownToFile(allSubProcesses, regionList, era, nominalDir, METUpDir, METDownDir, name)

def addEESToFile(allSubProcesses, regionList, era, nominalDir):
    EESUpDir = nominalDir.replace('/mc/', '_EleScaleUp/mc/')
    EESDownDir = nominalDir.replace('/mc/', '_EleScaleDown/mc/')
    # name = 'CMS_e_scale'
    name = 'CMS_scale_e'
    addUpDownToFile(allSubProcesses, regionList, era, nominalDir, EESUpDir, EESDownDir, name)
    
        
    
def addUpDownToFile(allSubProcesses, regionList, era, nominalDir, upDir, downDir, variationName, variable='BDT'):
    JERListUp = {}
    JERListDown = {}
    JERUpName = f'{variationName}_{era}Up'
    JERDownName = f'{variationName}_{era}Down'
    for isub in allSubProcesses:
        JERListUp[isub] = []
        JERListDown[isub] = []
        JERHistsNameUp = [f'{isub}_{ire}_{JERUpName}_{variable}' for ire in regionList] 
        JERHistsNameDown = [f'{isub}_{ire}_{JERDownName}_{variable}' for ire in regionList] 
        
        histList = [f'{isub}_{ire}_{variable}' for ire in regionList]
        histsUp = uf.getHistFromFile(f'{upDir}{isub}.root', histList) 
        histsDown = uf.getHistFromFile(f'{downDir}{isub}.root', histList)
        for ire, iHist in enumerate(regionList):
            histsUp[ire].SetName(JERHistsNameUp[ire])
            histsDown[ire].SetName(JERHistsNameDown[ire]) 
            JERListUp[isub].append(histsUp[ire])
            JERListDown[isub].append(histsDown[ire])
        
    for isub, histList in JERListUp.items():
        inominal = f'{nominalDir}{isub}.root'
        downHists = JERListDown[isub]
        histToAdd = histList + downHists
        add_histograms_to_rootfile(histToAdd, inominal) 


def getMCSubPro(channel, era):
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
    return allSubProcesses
    
        
# def addJESToFile(allSubProcesses, channel, regionList, era, nominalDir, variables=['BDT']):
def addJESToFile(allSubProcesses, channel, regionList, era, nominalDir, variables=['BDT'], proPostFix=''):
    Version = nominalDir.split('/')[-4]
    print(Version)
    inVersion = Version.split('_')[-1]+'_JESPt22'
    outVersion = Version.split('_')[0]
    print(inVersion, outVersion)
    
    
    inputDirBase = f'/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}/'
    nominalHistDir = nominalDir.split('mc/', 1)[1]
    
    
    JESListUp = {}# 'tttt' = [jestVariationHist]
    JESListDown = {}
    for isub in allSubProcesses:
        JESListUp[isub] = []
        JESListDown[isub] = []
     
    for i in gq.JESVariationList:
        JESUpDir = f'{inputDirBase}{outVersion}_JESup_{i}_{inVersion}'
        JESDownDir = f'{inputDirBase}{outVersion}_JESDown_{i}_{inVersion}'
        JESUpDir = f'{JESUpDir}/mc/{nominalHistDir}'
        JESDownDir = f'{JESDownDir}/mc/{nominalHistDir}'
        print(JESUpDir, JESDownDir)  
        iJESVariation = i.split('_')[0]
        ifCorrelated = wd.MCSys[f'CMS_scale_j_{iJESVariation}'][0]
        if ifCorrelated:
            JESUpName =  f'CMS_scale_j_{iJESVariation}Up'        
            JESDownName =  f'CMS_scale_j_{iJESVariation}Down'        
        else:
            JESUpName =  f'CMS_scale_j_{iJESVariation}_{era}Up'        
            JESDownName =  f'CMS_scale_j_{iJESVariation}_{era}Down'        
        for ivariable in variables:
            getJESHistForDir(JESUpDir, JESDownDir, JESListUp, JESListDown, JESUpName, JESDownName, regionList, ivariable, proPostFix) 
        
    for isub, histList in JESListUp.items():
        inominal = f'{nominalDir}{isub}.root'
        downHists = JESListDown[isub]
        histToAdd = histList + downHists
        add_histograms_to_rootfile(histToAdd, inominal) 
    
       
def add_histograms_to_rootfile(histograms, rootfile_path):
    """
    Add a list of histograms to an existing ROOT file.

    Parameters:
    histograms (list): A list of ROOT.TH1 objects to be added to the file.
    rootfile_path (str): The path to the existing ROOT file.
    """
    # Open the ROOT file in update mode
    rootfile = ROOT.TFile.Open(rootfile_path, "UPDATE")
    if not rootfile or rootfile.IsZombie():
        print(f"Error: Could not open file {rootfile_path}")
        return

    # Write each histogram to the ROOT file
    for histogram in histograms:
        if isinstance(histogram, ROOT.TH1):
            histogram.Write()  # Write the histogram to the file
        else:
            print(f"Warning: Object {histogram} is not a ROOT.TH1 histogram and will not be added.")

    # Close the ROOT file to ensure all changes are saved
    rootfile.Close()
    print(f"Histograms added to {rootfile_path}") 
        
          
# def getJESHistForDir(JESUpDir, JESDownDir, JESListUP, JESListDown, JESUpName, JESDownName, regionList, variable='BDT'):
def getJESHistForDir(JESUpDir, JESDownDir, JESListUP, JESListDown, JESUpName, JESDownName, regionList, variable='BDT', subPostfix=''):
    for isub in JESListUP.keys():
        isubHistName = isub + subPostfix
        # histList = [f'{isub}_{ire}_{variable}' for ire in regionList]
        # JESHistsNameUp = [f'{isub}_{ire}_{JESUpName}_{variable}' for ire in regionList] 
        # JESHistsNameDown = [f'{isub}_{ire}_{JESDownName}_{variable}' for ire in regionList] 
        histList = [f'{isubHistName}_{ire}_{variable}' for ire in regionList]
        JESHistsNameUp = [f'{isubHistName}_{ire}_{JESUpName}_{variable}' for ire in regionList]
        JESHistsNameDown = [f'{isubHistName}_{ire}_{JESDownName}_{variable}' for ire in regionList]
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