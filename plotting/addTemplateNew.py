import argparse
import ROOT
import usefulFunc as uf
import writeDatacard as wd
import pl as pl

# Import workflow utilities for config-based path building
try:
    from workflow_utils import (
        load_config, build_hist_path, get_channel, get_options
    )
    WORKFLOW_UTILS_AVAILABLE = True
except ImportError:
    WORKFLOW_UTILS_AVAILABLE = False


def main():
    parser = argparse.ArgumentParser(description='Create template ROOT files for CMS Combine')
    parser.add_argument('--quiet', '-q', action='store_true', help='Suppress verbose output')
    parser.add_argument('--config', '-c', type=str, required=True,
                        help='Path to YAML config file (required)')
    parser.add_argument('--era', '-e', type=str, required=True,
                        choices=['2018', '2017', '2016preVFP', '2016postVFP'],
                        help='Era to process (required)')
    args = parser.parse_args()

    # Validate workflow_utils is available
    if not WORKFLOW_UTILS_AVAILABLE:
        parser.error("workflow_utils not available. Install pyyaml: pip install pyyaml")

    # Import additional workflow utilities
    from workflow_utils import get_regions

    # Load config and build paths
    config = load_config(args.config)
    channel = get_channel(config)
    options = get_options(config)
    inputDir = build_hist_path(config, args.era)
    variables = ['BDT']
    regionList = get_regions(config)
    ifFakeTau = options.get('fake_tau', True)
    ifMCFTau = options.get('mc_fake_tau', False)
    ifBlind = options.get('blind', False)

    if not args.quiet:
        print(f"Using config: {args.config}")
        print(f"Era: {args.era}, Channel: {channel}")
        print(f"Regions: {regionList}")
        print(f"Input dir: {inputDir}")

    # Historical paths preserved in: config/historical_paths_backup.txt
    era = uf.getEraFromDir(inputDir)
    inputDirDic = uf.getInputDicNew( inputDir)
    is1tau2l = True if channel == '1tau2l' else False

    sumProList = pl.getSumList(channel, ifFakeTau, False, ifMCFTau, True)
    if not args.quiet:
        print('sumProList:', sumProList)
    sumProSys = pl.getSysDicPL(sumProList, True, channel, era, True)

    # WORKAROUND: For 2016preVFP/postVFP eras, we need to use the actual era suffix
    # to find histograms in ROOT files, even though getSysDicPL maps them to _2016
    # sumProSys is a dict of processes, each containing a LIST of systematic names
    # NOTE: As of v9BDT1tau0l_CMSNamingComplete (2025-11-28):
    #   - Tau TES: Mapped at C++ level (_2016 for both VFP eras)
    #   - Tau fakes: Fully correlated (no era suffix at all)
    #   - L1 prefiring: NOW ALSO mapped at C++ level (_2016 for both VFP eras)
    # Therefore: NO unmapping needed! All VFP correlation is handled in C++.
    if era in ["2016preVFP", "2016postVFP"]:
        if not args.quiet:
            print(f"DEBUG: VFP era detected ({era}), but NO unmapping needed - all handled at C++ level")
        systematics_to_unmap = [
            # 'CMS_scale_t_DeepTau2017v2p1_DM0_genTau',   # Mapped at C++ level - DON'T remap
            # 'CMS_scale_t_DeepTau2017v2p1_DM1_genTau',   # Mapped at C++ level - DON'T remap
            # 'CMS_scale_t_DeepTau2017v2p1_DM10_genTau',  # Mapped at C++ level - DON'T remap
            # 'CMS_scale_t_DeepTau2017v2p1_DM11_genTau',  # Mapped at C++ level - DON'T remap
            # 'CMS_fake_t_DeepTau2017v2p1_VSe',          # Fully correlated (no era suffix) - DON'T remap
            # 'CMS_fake_t_DeepTau2017v2p1_VSmu',         # Fully correlated (no era suffix) - DON'T remap
            # 'CMS_l1_ecal_prefiring'                    # NOW mapped at C++ level - DON'T remap
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
                        if not args.quiet:
                            print(f"DEBUG: Remapping {sys_with_2016} -> {sys_with_era} for process {process}")
                        new_sys_list.append(sys_with_era)
                        remapped = True
                        break
                if not remapped:
                    new_sys_list.append(sys_name)
            sumProSys[process] = new_sys_list

    
    sumProcessPerVar, sumProcessPerVarSys = uf.getSumHist(inputDirDic, regionList, sumProList, sumProSys, variables, era, False , False, ifMCFTau)#sumProcessPerVar[ivar][region][sumPro]
    
    
    addDataHist(variables, regionList, sumProList, sumProcessPerVar, is1tau2l, ifBlind, args.quiet) 
   
          
             
            
                    
                    
                    
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
                        # Note: Keep VFP-specific names in template files (_2016preVFP, _2016postVFP)
                        # VFP correlation mapping (_2016) is done in writeDatacard.py::getSysDic()

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
   
   
def addDataHist(variables, regionList, sumProList, sumProcessPerVar, is1tau2l, ifBlind=True, quiet=False):
    #add fake data for SR
    dataName = 'leptonSum' if is1tau2l else 'jetHT'
    for ivar in variables:
        for region in regionList:
            dataHist = None
            if 'SR' in region and ifBlind:
                for sumPro in sumProList:
                    if uf.isData(sumPro): continue
                    if not quiet:
                        print('fake data: ', sumPro)

                    hist = sumProcessPerVar[ivar][region][sumPro]
                    resetNegtiveBins(hist)

                    if dataHist == None:
                        dataHist = sumProcessPerVar[ivar][region][sumPro].Clone()
                        dataHist.SetName(dataHist.GetName().replace(sumPro, 'data_obs'))
                    else:
                        dataHist.Add(sumProcessPerVar[ivar][region][sumPro])    # some process has negative bins, set them to 0
                sumProcessPerVar[ivar][region][dataName] = dataHist
                if not quiet:
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
    
