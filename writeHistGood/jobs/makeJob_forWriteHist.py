import os
import subprocess
import argparse
import sys

import usefulFunc as uf

# Add plotting directory to path for workflow_utils
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', 'plotting'))

try:
    from workflow_utils import load_config, build_stage2_path, get_channel, get_versions, get_workflow_state
    WORKFLOW_UTILS_AVAILABLE = True
except ImportError:
    WORKFLOW_UTILS_AVAILABLE = False

#!For jobs of energy scale variaion, make the outut version the same of the nominal one

def main(
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/', #!!V13
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly_TESdm11Down/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly_TESdm11Down/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/', #!v13
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinC_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinA_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinC_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_tauFMorph_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorph_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorphBugFix_v94HadroPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/',
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/', #!v14, and V16
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/', #TTBB test
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/', #TTBB test 2017
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/',#!!!v14
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/',#!!!v14
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/',#!!!v14
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/',#!!!v14
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/', #!moved v14 to v13 nominal
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/',#!!!v14
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/',#!!!v14
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/',#!!!v14
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/',#!!!v14
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/',#!!!v14
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/',#!!!v14
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/',#!!!v14
    
    # channel = '1tau1l',
    channel = '1tau0l',
    # channel = '1tau2l',
    # version = 'v0BDT1tau2l', 
    # version = 'v0BDT1tau1l',
    # version = 'v1BDT1tau1lTestLeading7',
    # version = 'v0BDT1tau1lFakeTau',
    # version = 'v0BDT1tau0l',
    # version = 'v0BDT1tau0lFakeTauPtMorphed',
    # version = 'v0BDT1tau0lFakeTau',
    # version = 'v0BDT1tau0lV2',
    # version = 'v0BDT1tau1lV16',
    # version = 'v0BDT1tau0lV16',
    # version = 'v0BDT1tau1lV17',
    # version = 'v8BDT1tau1lV_refactorAndBtagNameFix', 
    version = 'v8BDT1tau0l_refactorAndBtagNameFix', 
    # version = 'v0BDT1tau0lV17',
    # version = 'v0BDT1tau2lV16',
    # version = 'v0BDT1tau2lV17',
    # version = 'v5BDT1tau0l_tauFMorphFix',
    # version = 'v5BDT1tau2l_tauFMorphFix',
    # version = 'v0BDT1tau2lV17_fakeTauDataDriven',
    # version = 'v3BDT1tau2lV18_fakeTauDataDriven',
    # version = 'v4BDT1tau2lV18_fakeTauDataDriven',#correct event weight 
    # version = 'v3BDT1tau1lV18_fakeTauDataDriven',
    # version = 'v0DataMC_sys',
    # version = 'v0DataMC',
    # version = 'v1DataMC_noHLTSF',
    # version = 'v1dataMC_fakeTauMC',
    # version = 'v1dataMC_fakeTauDataDriven',
    # version = 'v0FRMeasure',
    # version = 'v2FRMeasureCheckMC',
    # version = 'v2FRMeasureCheckMC_v2',
    # version = 'v2FRMeasureCheckMCBin3',
    # exe = './apps/run_WH_forDataMC.out',
    exe = './apps/run_treeAnalyzer.out' ,
    ifSys = 1,
    justMC = False
):
    
    
       
    #b-tag measurement 
    # version = 'v1_btagRMeasure'
    # version = 'v0_btagEffMeasure'
    # version = 'v0_btagEffMeasureT'
    
    #HLT 
    # version = 'v0HLTMeasure'
  
   
    #dataMC
    # version = 'v0dataMC_allCorrection'
    # version = 'v1dataMC_allCorrectionNotFakeTau'
    # version = 'v0dataMC_allCorrectionFakeLepton'
    # version = 'v1dataMC_allbutHLT'
    # version = 'v1dataMC_allbutHLTFakeLepton'
    # version = 'v2dataMC_allbutHLT'
    # version = 'v0dataMC_genWeight'
    
        
   
    # justMC = True
    isTest = 0
    print( inputDir, ' ', version )


    inputDirDic={}
    inputDirDic['mc'] = inputDir + 'mc/'
    if not justMC:
        inputDirDic['data'] = inputDir + 'data/'
        
    Jobsubmitpath = inputDirDic['mc'] + 'variableHists_' + version + '/' 
    uf.checkMakeDir(Jobsubmitpath)
    print('JobsubmitPath: ' ,Jobsubmitpath)
    subAllProcess = open( Jobsubmitpath+'subAllProcess.sh', 'w') 
    #important to add the full path so that it can be ran in any folder
    subAllProcess.write('#!/bin/bash\n')

    for i in inputDirDic.keys():
        # makeJobsforDir( inputDirDic[i], version,  isTest, subAllProcess, Jobsubmitpath, channel , exe)
        makeJobsforDir( inputDirDic[i], version, ifSys, isTest, subAllProcess, Jobsubmitpath, channel , exe)
    subAllProcess.close()

    uf.sumbitJobs(  Jobsubmitpath+'subAllProcess.sh')



def makeJobsforDir( inputDir, version, ifSys, isTest, subAllProcess, Jobsubmitpath , channel, exe='./apps/run_WH_forDataMC.out'):
    jobDir = Jobsubmitpath +'jobSH/'
    uf.checkMakeDir(jobDir) 
    outputDir = inputDir + 'variableHists_' + version +'/'
    logDir = outputDir+'log/'
    uf.checkMakeDir(jobDir)
    uf.checkMakeDir(outputDir)
    uf.checkMakeDir(logDir)
    
    exeDir = (os.path.dirname( os.path.abspath(__file__) ) +'/').rsplit('/', 2)[0] + '/'
    

    for iFile in os.listdir( inputDir ):
        if '.root' in iFile:
            iProcess = iFile.split('.root')[0]
            print(iProcess)
            iJobFile = jobDir + 'WH_'+iProcess +'.sh' 
            # run = f"{exe} {inputDir} {iProcess} {channel} {version} {isTest}"
            run = f"{exe} {inputDir} {iProcess} {channel} {version} {ifSys} {isTest}"
            makeIjob( iJobFile,  Jobsubmitpath, run ,exeDir)  

            logFile = logDir + iProcess + ".log"
            errFile = logDir + iProcess +".err"
            # subAllProcess.write('hep_sub -os CentOS7 -mem 6000 '+ iJobFile + ' -o ' + logFile + ' -e ' + errFile +'\n' )
            # subAllProcess.write('hep_sub -os CentOS7  '+ iJobFile + ' -o ' + logFile + ' -e ' + errFile +'\n' )
            subAllProcess.write('hep_sub  '+ iJobFile + ' -o ' + logFile + ' -e ' + errFile +'\n' )


    subprocess.run('chmod 777 ' + jobDir +'*sh',  shell=True)
    subprocess.run('chmod 777 ' + Jobsubmitpath+ 'subAllProcess.sh', shell=True)





def makeIjob( shFile, Jobsubmitpath, run, exeDir ):
    subFile = open( shFile, "w" )
    subFile.write('#!/bin/bash\n')
    subFile.write('cd '+ exeDir + '\n' )
    subFile.write(run)
    print( 'done writing: ', shFile)


def create_parser():
    """Create argument parser for WH job submission."""
    parser = argparse.ArgumentParser(
        description='Submit writeHistGood (Stage 3) jobs to HTCondor',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog='''
Examples:
  # Using YAML config (recommended):
  python3 makeJob_forWriteHist.py --config ../../config/analysis_config_1tau0l_full.yaml --era 2017

  # Legacy mode (uses hardcoded paths in script):
  python3 makeJob_forWriteHist.py
        '''
    )
    parser.add_argument('--config', '-c', type=str,
                        help='Path to YAML config file')
    parser.add_argument('--era', '-e', type=str,
                        choices=['2018', '2017', '2016preVFP', '2016postVFP'],
                        help='Era to process')
    parser.add_argument('--sys', type=int, default=1,
                        help='Include systematics (0=no, 1=yes, default: 1)')
    parser.add_argument('--just-mc', action='store_true',
                        help='Only process MC (skip data)')
    parser.add_argument('--dry-run', action='store_true',
                        help='Show what would be done without submitting')
    return parser


if __name__=='__main__':
    parser = create_parser()
    args = parser.parse_args()

    # Deprecation warning
    print("=" * 70)
    print("DEPRECATION WARNING:")
    print("  makeJob_forWriteHist.py is deprecated.")
    print("  Please use: makeJob_WH.py --systematic nominal")
    print("  Example: python3 makeJob_WH.py --config CONFIG --era 2018 --systematic nominal")
    print("=" * 70)
    print()

    if args.config:
        # Config mode: use YAML config
        if not WORKFLOW_UTILS_AVAILABLE:
            parser.error("workflow_utils not available. Install pyyaml: pip install pyyaml")
        if not args.era:
            parser.error("--era is required when using --config")

        config = load_config(args.config)
        # build_stage2_path returns path with /mc/, but main() expects parent dir
        inputDir = build_stage2_path(config, args.era)
        # Remove trailing 'mc/' since main() adds it
        if inputDir.endswith('/mc/'):
            inputDir = inputDir[:-3]  # Remove 'mc/'
        elif inputDir.endswith('/mc'):
            inputDir = inputDir[:-2]  # Remove 'mc'
        channel = get_channel(config)
        versions = get_versions(config)
        version = versions['hist']

        print(f"=== Config mode ===")
        print(f"Config: {args.config}")
        print(f"Era: {args.era}")
        print(f"Channel: {channel}")
        print(f"Input dir: {inputDir}")
        print(f"Hist version: {version}")

        if args.dry_run:
            print("\n[DRY RUN] Would submit jobs with above settings")
        else:
            # Update workflow state before submission
            try:
                state = get_workflow_state(channel, args.config)
                state.update_stage('3', args.era, 'submitting', 'WH_nominal')
                state.log_execution('3', args.era, 'WH_nominal', 'submitting',
                                   config=args.config, version=version)
            except Exception as e:
                print(f"[WARNING] Could not update workflow state: {e}")

            main(
                inputDir=inputDir,
                channel=channel,
                version=version,
                ifSys=args.sys,
                justMC=args.just_mc
            )

            # Update workflow state after submission
            try:
                state = get_workflow_state(channel, args.config)
                state.update_stage('3', args.era, 'submitted', 'WH_nominal')
                state.log_execution('3', args.era, 'WH_nominal', 'submitted',
                                   config=args.config, version=version)
                print(f"\n[WorkflowState] Updated: Stage 3, {args.era}, submitted")
            except Exception as e:
                print(f"[WARNING] Could not update workflow state: {e}")
    else:
        # Legacy mode: use hardcoded paths in main()
        print("=== Legacy mode (using hardcoded paths) ===")
        main()
