import ROOT
import usefulFunc as uf
import writeDatacard as wd
import pl as pl


def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV15/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV15/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV16/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV16/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV16/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV16/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v8BDT1tau1lV_refactorAndBtagNameFix/'
    # channel = '1tau1l'
    # variables = ['BDT']
    # regionList = ['1tau1lSR', '1tau1lCR12']
    
    #1tau0l
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV16/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV16/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV16/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV16/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV16/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v8BDT1tau0l_refactorAndBtagNameFix/' #!2025-11-24: Done
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v8BDT1tau0l_refactorAndBtagNameFix/' #!2025-11-24: Done
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v8BDT1tau0l_refactorAndBtagNameFix/' #!2025-11-24: Done
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v8BDT1tau0l_refactorAndBtagNameFix/' #!2025-11-24: Done
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v9BDT1tau0l_CMSNamingComplete/' #!2025-11-27: Done
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v9BDT1tau0l_CMSNamingComplete/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v9BDT1tau0l_CMSNamingComplete/' #!2025-11-27: Done
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v9BDT1tau0l_CMSNamingComplete/' #!2025-11-27: Done
    channel = '1tau0l'
    variables = ['BDT']
    regionList = ['1tau0lSR', '1tau0lCRMR', '1tau0lVR']
    
    #1tau2l 
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV16/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV16/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV16/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV16/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/'
    # channel = '1tau2l'
    # variables = ['BDT']
    # regionList = ['1tau2lSR', '1tau2lCR3']
    
    
    ifFakeTau = True
    # ifMCFTau = False if channel =='1tau0l' else True
    # ifMCFTau = True #!
    ifMCFTau = False #!
    ifBlind = False #!!!


    era = uf.getEraFromDir(inputDir)
    inputDirDic = uf.getInputDicNew( inputDir)
    is1tau2l = True if channel == '1tau2l' else False

    sumProList = pl.getSumList(channel, ifFakeTau, False, ifMCFTau, True)
    print('sumProList:', sumProList)
    sumProSys = pl.getSysDicPL(sumProList, True, channel, era, True)

    # WORKAROUND: For 2016preVFP/postVFP eras, we need to use the actual era suffix
    # to find histograms in ROOT files, even though getSysDicPL maps them to _2016
    # sumProSys is a dict of processes, each containing a LIST of systematic names
    # NOTE: Tau TES and tau fakes are already mapped at C++ level, so only remap L1 prefiring
    if era in ["2016preVFP", "2016postVFP"]:
        print(f"DEBUG: Unmapping VFP systematics for era {era}")
        systematics_to_unmap = [
            # 'CMS_scale_t_DeepTau2017v2p1_DM0_genTau',   # Already mapped at C++ level - DON'T remap
            # 'CMS_scale_t_DeepTau2017v2p1_DM1_genTau',   # Already mapped at C++ level - DON'T remap
            # 'CMS_scale_t_DeepTau2017v2p1_DM10_genTau',  # Already mapped at C++ level - DON'T remap
            # 'CMS_scale_t_DeepTau2017v2p1_DM11_genTau',  # Already mapped at C++ level - DON'T remap
            # 'CMS_fake_t_DeepTau2017v2p1_VSe',          # Fully correlated (no era suffix) - DON'T remap
            # 'CMS_fake_t_DeepTau2017v2p1_VSmu',         # Fully correlated (no era suffix) - DON'T remap
            'CMS_l1_ecal_prefiring'
        ]
        for process in sumProSys:
            if not isinstance(sumProSys[process], list):
                continue
            new_sys_list = []
            for sys_name in sumProSys[process]:
                # Check if this is one of the systematics we need to unmap
                remapped = False
                for sys_base in systematics_to_unmap:
                    sys_with_2016 = f'{sys_base}_2016'
                    sys_with_era = f'{sys_base}_{era}'
                    if sys_name == sys_with_2016:
                        print(f"DEBUG: Remapping {sys_with_2016} -> {sys_with_era} for process {process}")
                        new_sys_list.append(sys_with_era)
                        remapped = True
                        break
                if not remapped:
                    new_sys_list.append(sys_name)
            sumProSys[process] = new_sys_list

    
    sumProcessPerVar, sumProcessPerVarSys = uf.getSumHist(inputDirDic, regionList, sumProList, sumProSys, variables, era, False , False, ifMCFTau)#sumProcessPerVar[ivar][region][sumPro]
    
    
    addDataHist(variables, regionList, sumProList, sumProcessPerVar, is1tau2l, ifBlind) 
   
          
             
            
                    
                    
                    
    outDir = inputDir+'combine/'
    uf.checkMakeDir(outDir)
    name = 'templatesForCombine'+channel+'_new'
    if not ifMCFTau:
        name = name.replace('new', 'new_notMCFTau') 
    if not ifBlind:
        name = name + '_unblind'
    templateFile = outDir + name + '.root'
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

                        # Map 2016preVFP/postVFP → 2016 for specific systematics
                        # These systematics should be fully correlated across 2016 VFP eras
                        histName = hist.GetName()
                        systematics_to_merge = [
                            'CMS_scale_t_DeepTau2017v2p1_DM0_genTau',
                            'CMS_scale_t_DeepTau2017v2p1_DM1_genTau',
                            'CMS_scale_t_DeepTau2017v2p1_DM10_genTau',
                            'CMS_scale_t_DeepTau2017v2p1_DM11_genTau',
                            'CMS_fake_t_DeepTau2017v2p1_VSe',
                            'CMS_fake_t_DeepTau2017v2p1_VSmu',
                            'CMS_l1_ecal_prefiring'
                        ]
                        for sys_name in systematics_to_merge:
                            histName = histName.replace(f'{sys_name}_2016preVFP', f'{sys_name}_2016')
                            histName = histName.replace(f'{sys_name}_2016postVFP', f'{sys_name}_2016')
                        hist.SetName(histName)

                        #! rename process-uncorrelated sys for combine
                        sysName = sys.replace('_up', '').replace('_down', '')
                        sysName = sysName.replace('_2018', '').replace('_2017', '').replace('_2016preVFP', '').replace('_2016postVFP', '').replace('_2016', '') # remove era
                        #sysName is sys remove '_up" or '_down'
                        if not wd.MCSys[sysName][3]: # process-uncorrelated sys
                            sysNameNew = sysName + '_' + sumPro
                            hist.SetName(hist.GetName().replace(sysName, sysNameNew))

                        hist.Write(hist.GetName())
    outFile.Write()
    outFile.Close()
    print('template file created:', templateFile)
   
   
def addDataHist(variables, regionList, sumProList, sumProcessPerVar, is1tau2l, ifBlind=True): 
    #add fake data for SR
    dataName = 'leptonSum' if is1tau2l else 'jetHT' 
    for ivar in variables:
        for region in regionList:
            dataHist = None
            if 'SR' in region and ifBlind:
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

def resetNegtiveBins(hist):
    for i in range(1, hist.GetNbinsX()+1):
        if hist.GetBinContent(i) < 0.:
            hist.SetBinContent(i, 0)
            hist.SetBinError(i, 0)
    return hist
    
    
if __name__ == "__main__":
    main()
    
