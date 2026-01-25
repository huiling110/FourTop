import argparse
import ROOT

# Use fourtop package for centralized utilities
from fourtop.workflow import (
    load_config, build_hist_path, get_channel, get_options, get_regions
)
from fourtop.utils import checkMakeDir, getInputDicNew, getEraFromDir
from fourtop.utils.process import getSumListFull
from fourtop.utils.histogram import getSumHist
from fourtop.constants.jes import SKIP_SUBPROCESSES
from fourtop.constants.systematics import MCSYS
from fourtop.stage4.templates import addDataHist, resetNegativeBins
from fourtop.stage4.datacards import getProSysDicForPlotting


def main():
    parser = argparse.ArgumentParser(description='Create template ROOT files for CMS Combine')
    parser.add_argument('--quiet', '-q', action='store_true', help='Suppress verbose output')
    parser.add_argument('--config', '-c', type=str, required=True,
                        help='Path to YAML config file (required)')
    parser.add_argument('--era', '-e', type=str, required=True,
                        choices=['2018', '2017', '2016preVFP', '2016postVFP'],
                        help='Era to process (required)')
    parser.add_argument('--variables', '-v', type=str, default='BDT',
                        help='Comma-separated list of variables (default: BDT)')
    parser.add_argument('--input-dir', type=str, default=None,
                        help='Override input directory (default: use config)')
    parser.add_argument('--output-dir', type=str, default=None,
                        help='Override output directory (default: {input-dir}/combine/)')
    parser.add_argument('--mode', '-m', type=str, default='bdt',
                        choices=['bdt', 'variables'],
                        help='Mode: bdt (default, variableHists_*) or variables (inputVarHists_*)')
    args = parser.parse_args()

    # Load config and build paths
    config = load_config(args.config)
    channel = get_channel(config)
    options = get_options(config)
    inputDir = args.input_dir if args.input_dir else build_hist_path(config, args.era, mode=args.mode)
    variables = [v.strip() for v in args.variables.split(',')]
    regionList = get_regions(config)
    ifFakeTau = options.get('fake_tau', True)
    ifMCFTau = options.get('mc_fake_tau', False)
    ifBlind = options.get('blind', False)

    if not args.quiet:
        print(f"Using config: {args.config}")
        print(f"Era: {args.era}, Channel: {channel}, Mode: {args.mode}")
        print(f"Regions: {regionList}")
        print(f"Input dir: {inputDir}")

    # Historical paths preserved in: config/historical_paths_backup.txt
    era = getEraFromDir(inputDir)
    inputDirDic = getInputDicNew(inputDir)
    is1tau2l = True if channel == '1tau2l' else False

    sumProList = getSumListFull(channel, ifFakeTau, '', ifMCFTau, True)
    if not args.quiet:
        print('sumProList:', sumProList)
    sumProSys = getProSysDicForPlotting(sumProList, True, channel, era, True)

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


    # Get skip list for this channel (reduces systematic noise from negligible subprocesses)
    skip_subprocesses = SKIP_SUBPROCESSES.get(channel, [])
    if skip_subprocesses and not args.quiet:
        print(f"Will skip subprocesses: {skip_subprocesses}")

    sumProcessPerVar, sumProcessPerVarSys = getSumHist(inputDirDic, regionList, sumProList, sumProSys, variables, era, False , False, ifMCFTau, skip_subprocesses=skip_subprocesses)#sumProcessPerVar[ivar][region][sumPro]


    addDataHist(variables, regionList, sumProList, sumProcessPerVar, is1tau2l, ifBlind, args.quiet)

    outDir = args.output_dir if args.output_dir else inputDir+'combine/'
    if not outDir.endswith('/'):
        outDir += '/'
    checkMakeDir(outDir)
    # Get template version from config (default: v3)
    template_version = config.get('versions', {}).get('template_file', 'v3')

    # Create separate template file for each variable
    for ivar in variables:
        # Build template filename with variable suffix for non-BDT variables
        var_suffix = '' if ivar == 'BDT' else f'_{ivar}'
        name = f'templatesForCombine{channel}_{template_version}{var_suffix}'
        if not ifMCFTau:
            name += '_notMCFTau'
        if not ifBlind:
            name += '_unblind'
        templateFile = outDir + name + '.root'

        # Safety check: non-BDT variables must have suffix in path
        if ivar != 'BDT':
            assert f'_{ivar}' in templateFile, f"Safety check: non-BDT variable {ivar} must have suffix in path"

        outFile = ROOT.TFile(templateFile, 'RECREATE')

        # Write histograms for this variable
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
                        if sysName in MCSYS and not MCSYS[sysName][3]: # process-uncorrelated sys
                            sysNameNew = sysName + '_' + sumPro
                            hist.SetName(hist.GetName().replace(sysName, sysNameNew))

                        hist.Write(hist.GetName())
        outFile.Write()
        outFile.Close()
        print('template file created:', templateFile)


# Note: addDataHist and resetNegativeBins are now imported from fourtop.stage4.templates


if __name__ == "__main__":
    main()
    
