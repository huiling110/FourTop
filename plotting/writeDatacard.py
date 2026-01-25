import os
import argparse
import ROOT

# Use fourtop package for centralized utilities
from fourtop.workflow import (
    load_config, build_template_path, get_channel, get_options
)
from fourtop.utils import checkMakeDir, getEraFromDir
from fourtop.utils.process import getSumListFull
from fourtop.constants.systematics import MCSYS
from fourtop.stage4.datacards import (
    getSysDic, addLumi, addProcessNormalization, remove0Process, write_shape_datacard
)

# Alias for backward compatibility (some external scripts may import MCSys from this file)
MCSys = MCSYS

# Default version for datacard output directory naming
outVersion = 'v6AllSys_unblind_CMSnaming'


def main():
    parser = argparse.ArgumentParser(description='Generate datacards for CMS Combine')
    parser.add_argument('--quiet', '-q', action='store_true', help='Suppress verbose output')
    parser.add_argument('--config', '-c', type=str, required=True,
                        help='Path to YAML config file (required)')
    parser.add_argument('--era', '-e', type=str, required=True,
                        choices=['2018', '2017', '2016preVFP', '2016postVFP'],
                        help='Era to process (required)')
    parser.add_argument('--smoothed', action='store_true', default=None,
                        help='Use smoothed templates (default: from config options.smoothing)')
    parser.add_argument('--no-smoothed', dest='smoothed', action='store_false',
                        help='Use unsmoothed templates')
    parser.add_argument('--template-version', type=str, default=None,
                        help='Template version suffix (e.g., "v3" for templatesForCombine1tau1l_v3_...)')
    parser.add_argument('--variable', type=str, default='BDT',
                        help='Variable for datacard (default: BDT)')
    args = parser.parse_args()

    # Load config and build paths
    config = load_config(args.config)
    channel = get_channel(config)
    options = get_options(config)

    # Get template version from CLI or config
    template_version = args.template_version or config.get('versions', {}).get('template_file', 'v3')
    variable = args.variable

    # Build suffix using template version
    # Add variable suffix for non-BDT variables
    var_suffix = '' if variable == 'BDT' else f'_{variable}'
    suffix = f"_{template_version}{var_suffix}"
    if not options.get('mc_fake_tau', False):
        suffix += '_notMCFTau'
    if not options.get('blind', True):
        suffix += '_unblind'

    # Safety check: non-BDT variables must have suffix in path
    if variable != 'BDT':
        assert f'_{variable}' in suffix, f"Safety check: non-BDT variable {variable} must have suffix"

    # Determine smoothed setting: command line overrides config
    # Default: 1tau0l/1tau1l use smoothed (smoothing: true), 1tau2l uses non-smoothed (smoothing: false)
    if args.smoothed is None:
        use_smoothed = options.get('smoothing', False)  # Default False, config should specify
    else:
        use_smoothed = args.smoothed

    # Build template path
    if use_smoothed:
        # For smoothed templates, use _smoothed_v2 suffix (smoothing script output)
        inputTemplate = build_template_path(config, args.era, channel, suffix, smoothed=False)
        inputTemplate = inputTemplate.replace('.root', '_smoothed_v2.root')
    else:
        inputTemplate = build_template_path(config, args.era, channel, suffix, smoothed=False)
    ifFTauMC = options.get('mc_fake_tau', False)
    datacard_version = config.get('versions', {}).get('datacard', outVersion)

    # Add variable suffix to datacard version for non-BDT variables
    if variable != 'BDT':
        datacard_version = f"{datacard_version}_{variable}"

    if not args.quiet:
        print(f"Using config: {args.config}")
        print(f"Era: {args.era}, Channel: {channel}")
        print(f"Template: {inputTemplate}")

    # Historical paths preserved in: config/historical_paths_backup.txt
    inputDir = os.path.dirname(inputTemplate)
    outDir = f"{inputDir}/datacardSys_{datacard_version}/"
    checkMakeDir(outDir)
    outCard = f"{outDir}datacard.txt"  # Use consistent name for combine workflow
    era = getEraFromDir(inputTemplate)

    processes = getSumListFull(channel, True, '', ifFTauMC, True)
    if channel == '1tau2l':
        processes.remove('leptonSum')
    else:
        processes.remove('jetHT')
    if not args.quiet:
        print(processes)

    remove0Process(processes, inputTemplate, channel, args.quiet, variable)

    era = getEraFromDir(inputTemplate)
    sysDic = getSysDic(processes, channel, era)
    if not args.quiet:
        print(sysDic, '\n')
        for i, iv in sysDic.items():
            print(i, iv)

    addLumi(sysDic, era, processes)
    addProcessNormalization(sysDic, processes)

    write_shape_datacard(outCard, inputTemplate, channel, processes, sysDic, era, variable)


if __name__ == '__main__':
    main()
