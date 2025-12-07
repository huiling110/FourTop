import argparse
import os
import subprocess

import ttttGlobleQuantity as GQ
import usefulFunc as uf

# Optional YAML support
try:
    import yaml
    YAML_AVAILABLE = True
except ImportError:
    YAML_AVAILABLE = False


def load_config(config_path: str) -> dict:
    """Load configuration from YAML file."""
    if not YAML_AVAILABLE:
        raise ImportError("PyYAML not available. Install with: pip install pyyaml")

    with open(config_path, 'r') as f:
        config = yaml.safe_load(f)
    return config


#???make this job submisssion and checking and resubmit and addHist automatized
#todo add git co after job submission for version control

def main(
    year = '2016',
    # year = '2017',
    # year = '2018',
    # inVersion = 'v94HadroPreJetVetoHemOnly',
    # inVersion = 'v94HadroPreJetVetoHemOnly_JERDown', #2018, 2017
    # inVersion = 'v94HadroPreJetVetoHemOnly_EleScaleDown', #2018, 2017
    # inVersion = 'v94HadroPreJetVetoHemOnly_METUp', #2018,
    # inVersion = 'v94HadroPreJetVetoHemOnly_TESdm10Up', #2018
    # inVersion = 'v94LepPreJetVetoHemOnly',
    inVersion = 'v94LepPreJetVetoHemOnlyV2',
    # outVersion = 'v0baselineLep',
    # outVersion = 'v0baselineLep_tauF1',
    # outVersion = 'v0baselineLep_tauF1NewFRBinA',
    # outVersion = 'v0baselineLep_tauF1NewFRBinA_tauFMorph',
    # outVersion = 'v0baselineLep_newFRBinATauFMorphBugFix',
    # outVersion = 'v0baselineLep_newFRBinATauFMorphBugFix',
    # outVersion = 'v0baselineHadro',
    # outVersion = 'v0baselineHadro_newFRBinATauFMorphBugFix',
    # outVersion = 'v0baselineHadro_tauFMorphMass',
    outVersion = 'v1baselineHadroBtagWeightAdded', #!v13
    # if1tau2l = 0, # !!!0 false, 1 True
    if1tau2l = 1, #!!! 0 false, 1 True
    # if1tau2l = 0, # 0 false, 1 True
    # JESVariationType = 2, # 1up, 2 down
    JESVariationType = 0, # 1up, 2 down
    JESVariation = 0,
    config_path = None,
    year_from_cli = False,  # Flag to indicate CLI year should override YAML
):
    # Load from YAML config if provided
    if config_path is not None:
        print(f"Loading configuration from: {config_path}")
        config = load_config(config_path)

        # Get paths from config
        paths = config.get('paths', {})
        inVersion = paths.get('in_version', inVersion)
        outVersion = paths.get('out_version', outVersion)

        # Get eras from config - only if CLI year not explicitly set
        if not year_from_cli:
            eras = config.get('eras', [year])
            year = eras[0] if eras else year
        # else: keep year from CLI argument

        # Get stage2 specific config
        stage2 = config.get('stage2', {})
        if1tau2l = stage2.get('if1tau2l', if1tau2l)
        JESVariationType = stage2.get('JESVariationType', JESVariationType)
        JESVariation = stage2.get('JESVariation', JESVariation)

        print(f"  Year: {year}" + (" (from CLI)" if year_from_cli else " (from config)"))
        print(f"  Input version: {inVersion}")
        print(f"  Output version: {outVersion}")
        print(f"  if1tau2l: {if1tau2l}")

    isRun3 = uf.isRun3Era(year)
    justMC = False
    
    jobVersion = outVersion + '_' + inVersion 
    print('jobVersion:', outVersion + '_'+ inVersion) 
    inOutDirMap = getInOutDic( year, inVersion, outVersion, justMC )
    jobDir = os.path.dirname(os.path.abspath(__file__)) 
    jobDir = jobDir + '/'+jobVersion
    uf.checkMakeDir(jobDir)

    subAllName = year+'subAllofAll.sh'
    subAllofAllName = jobDir+ '/'+ subAllName
    subAllofAll = open( subAllofAllName, 'w')
    print('creating subAllofAll: ', subAllofAllName )
    subAllofAll.write( '#!/bin/bash\n')
    subAllofAll.write('cd '+jobDir + '\n')

    for iera in inOutDirMap.keys():
        # if iera=='2016preVFP' : continue
        # if iera=='2016postVFP' : continue#
        print('era: ', iera)
        
        for key in inOutDirMap[iera].keys():
            iDir = inOutDirMap[iera][key]
            print( 'inputOutDir: ', iDir )
            generateJobsForDir( iDir, iera+'_'+key,  jobDir , isRun3, if1tau2l, JESVariationType, JESVariation)
            subAllofAll.write('bash '+ iera+'_'+key + '_subAll.sh\n' )
    print( 'sub all jobs using: ' + jobDir +'/' + subAllName)
    subAllofAll.close()

    #change mod
    subprocess.run( 'chmod 777 '+ subAllofAllName, shell=True )
    
    uf.sumbitJobs(  subAllofAllName )




def getInOutDic( year, inVersion, outVersion, justMC ):
    inputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/'
    # outputBase = '/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/forMVA/'
    outputBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/'
    # outputBase = '/scratchfs/cms/huahuil/forMVA/'
    inputOutputDic={
        '2016postVFP': 'UL2016_postVFP',
        '2016preVFP': 'UL2016_preVFP',
        '2017': 'UL2017',
        '2018': 'UL2018',
        # '2022': 'Prompt2022',
        '2022': 'ReReco2022PreEE',
        '2022preEE': '2022preEE',
        '2022postEE': '2022postEE',
    }
    inOutDirMap = {}
#python dict
    if year=='2016':
        inOutDirMap ['2016postVFP'] = {}
        inOutDirMap ['2016preVFP'] = {}
        inOutDirMap['2016preVFP']['mc']= [ inputBase + 'UL2016_preVFP/'+ inVersion + '/mc/' , outputBase + '2016preVFP/'+ outVersion+'_'+inVersion + '/mc/' ]  
        inOutDirMap['2016postVFP']['mc'] = [ inputBase + 'UL2016_postVFP/' + inVersion + '/mc/', outputBase + '2016postVFP/'+ outVersion+'_'+inVersion + '/mc/']
        if not justMC:
            inOutDirMap['2016preVFP'] ['data']= [ inputBase + 'UL2016_preVFP/'+ inVersion + '/data/',   outputBase + '2016preVFP/'+ outVersion+'_'+inVersion + '/data/']
            inOutDirMap['2016postVFP']['data'] = [ inputBase + 'UL2016_postVFP/' + inVersion + '/data/', outputBase + '2016postVFP/'+ outVersion+'_'+inVersion + '/data/']
    else:
        inOutDirMap[year]={}
        inOutDirMap[year]['mc']= [ inputBase + inputOutputDic[year]+'/'+ inVersion + '/mc/' , outputBase +year+ '/'+ outVersion+'_'+inVersion + '/mc/' ]
        if not justMC:
            inOutDirMap[year]['data']= [ inputBase + inputOutputDic[year]+'/'+ inVersion + '/data/' , outputBase +year+ '/'+ outVersion+'_'+inVersion + '/data/' ]
            
    for iera in inOutDirMap.keys():
        uf.checkMakeDir(outputBase+iera+'/')
        uf.checkMakeDir(outputBase+iera+'/'+ outVersion+'_'+inVersion)
            
    return inOutDirMap

         



def generateJobsForDir( inOutList, dirKind, jobDir , isRun3=False, if1tau2l=False, JESVariationType=0, JESVariation=0):
    subDirName = jobDir+ '/'+ dirKind+'_subAll.sh'
    print('creating: ', subDirName )
    subDirJobs = open( subDirName, 'w' )
    subDirJobs.write( '#!/bin/bash\n' )
    subDirJobs.write( 'cd ' + jobDir +'\n')
    jobsDir =  jobDir + '/'+dirKind + '_jobs/'
     
    if os.path.exists( jobsDir ):
        subprocess.run('rm -fr '+ jobsDir , shell=True)
    uf.checkMakeDir(jobsDir)
    uf.checkMakeDir(inOutList[1])

    for entry in os.listdir(inOutList[0] ):
        print( 'loop over: ', entry )
        if not uf.checkIfInputDic(entry, isRun3): continue
        
        processJob = jobsDir + 'MV_' + dirKind +'_'+ entry + ".sh"
        iParametersList = [ inOutList[0], entry, inOutList[1], 0, if1tau2l, JESVariationType, JESVariation]
        writeIjob( iParametersList, processJob )

        uf.checkMakeDir(inOutList[1] +"log/")
        logFile = inOutList[1] +   "log/" + entry + ".log"
        errFile = inOutList[1] +  "log/" + entry +".err"
        # subDirJobs.write( 'hep_sub -os CentOS7 -mem 6000 '+ processJob  + " -o " + logFile + " -e " + errFile +'\n'   )
        subDirJobs.write( 'hep_sub '+ processJob  + " -o " + logFile + " -e " + errFile +'\n'   )
        # subDirJobs.write( 'hep_sub -os CentOS7 '+ processJob  + " -o " + logFile + " -e " + errFile +'\n'   )

    subprocess.run( 'chmod 777 '+jobsDir +'*.sh', shell = True )
    subprocess.run( 'chmod 777 ' + subDirName, shell = True)


            
    

def writeIjob( parameterList, processJob ):
    subFile  = open ( processJob ,"w")
    subFile.write( "#!/bin/bash\n")
    subFile.write("/bin/hostname\n")
    codeDir = os.path.dirname(os.path.abspath(__file__))
    codeDir = codeDir.rsplit('/',1)[0]
    projectRoot = codeDir.rsplit('/',1)[0]
    subFile.write("cd {}\n".format(projectRoot))
    # Source the environment for correctionlib and other dependencies
    subFile.write("source setEnv_newNew.sh\n")
    subFile.write("cd makeVariables_goodCode\n")
    command = f'./apps/run_makeVariables.out {parameterList[0]} {parameterList[1]} {parameterList[2]} {parameterList[3]} {parameterList[4]} {parameterList[5]} {parameterList[6]}'
    subFile.write(command )
    subFile.close()







def parse_args():
    """Parse command-line arguments."""
    parser = argparse.ArgumentParser(
        description='Submit Stage 2 (makeVariables) jobs for FourTop analysis'
    )
    parser.add_argument(
        '--config', '-c', type=str, default=None,
        help='Path to YAML config file (optional). If not provided, uses hardcoded defaults.'
    )
    parser.add_argument(
        '--year', '-y', type=str, default='2018',
        help='Year to process (default: 2018). Overridden by config if provided.'
    )
    parser.add_argument(
        '--inVersion', type=str, default=None,
        help='Input version (Stage 1 output). Overridden by config if provided.'
    )
    parser.add_argument(
        '--outVersion', type=str, default=None,
        help='Output version. Overridden by config if provided.'
    )
    parser.add_argument(
        '--if1tau2l', type=int, default=0,
        help='Channel flag: 0=1tau0l/1tau1l, 1=1tau2l (default: 0)'
    )
    return parser.parse_args()


if __name__=="__main__":
    args = parse_args()

    # Build kwargs for main()
    # Track if year was explicitly set via CLI (not default)
    import sys
    year_explicitly_set = '--year' in sys.argv or '-y' in sys.argv

    kwargs = {
        'year': args.year,
        'if1tau2l': args.if1tau2l,
        'config_path': args.config,
        'year_from_cli': year_explicitly_set,  # Pass flag to main
    }
    if args.inVersion:
        kwargs['inVersion'] = args.inVersion
    if args.outVersion:
        kwargs['outVersion'] = args.outVersion

    main(**kwargs)










