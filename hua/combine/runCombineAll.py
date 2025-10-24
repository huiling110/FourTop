import os
import subprocess
import argparse


#!!!run this with python2 because the CMSSW supports only python2

def main():
    parser = argparse.ArgumentParser(description="Process some directories and options.")
    parser.add_argument('--cardDir', type=str, required=True, help='The card directory to use.')
    parser.add_argument('--ifBlind', type=bool, default=False, help='Flag indicating if analysis should be blinded.')

    args = parser.parse_args()

    cardDir = args.cardDir
    ifBlind = args.ifBlind
    


     
     
    # cardToWorkspaces( cardDir )
    
    # runCombineSig( cardDir, True, ifBlind )#!Step 3
    # runCombineSig( cardDir, False, ifBlind )
    # copyCombineResultsToDir( cardDir )

    # runImpact(cardDir )#!Step 1 of unblinding
    
    # runPostFitPlots(cardDir)#!Step 2 of unblinding
    
    # measureSignalStrength(cardDir)#!Step 3 of unblinding
    
    goodnessOfFit(cardDir)#!Step 1 of unblinding


def goodnessOfFit(cardDir):
    '''
        Perform goodness-of-fit test to assess the quality of the fit
        Reference: 
        https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/latest/part3/commonstatsmethods/?h=good#goodness-of-fit-tests
    '''
    datacardFile = cardDir + 'workspace/datacard.root'
    outFolder = cardDir + 'combineResults/'

    goodnessOfFitDir = outFolder + 'goodnessOfFit/'
    if not os.path.exists(goodnessOfFitDir):
        os.mkdir(goodnessOfFitDir)
    #cd goodnessOfFitDir
    os.chdir(goodnessOfFitDir) #!don't need to cd in run_runCombineAll.sh anymore

    # Run goodness-of-fit test on observed data
    gofObservedCommand = 'combine -M GoodnessOfFit {} --algo saturated -n .observed'.format(datacardFile)
    runCommand(gofObservedCommand)

    # Generate toys for expected distribution
    gofToysCommand = 'combine -M GoodnessOfFit {} --algo saturated -t 200'.format(datacardFile)
    runCommand(gofToysCommand)

    #plot GOF results 
    # plotGofCommand = 'plotGof.py higgsCombine.observed.GoodnessOfFit.mH120.root higgsCombine.toys.GoodnessOfFit.mH120.123456.root --statistic saturated --mass 120.0 -o gof_plot'.format(goodnessOfFitDir)
    plot1 = 'combineTool.py -M CollectGoodnessOfFit --input higgsCombine.observed.GoodnessOfFit.mH120.root higgsCombineTest.GoodnessOfFit.mH120.123456.root -o gof.json'#gets error running combineTool.py
    plotGofCommand = 'plotGof.py gof.json --statistic saturated --mass 120.0 -o gof_plot'
    runCommand(plot1)
    runCommand(plotGofCommand)

    print('Goodness-of-fit results here: ', goodnessOfFitDir)
    print('\n' + '='*60)
    print('Goodness-of-Fit Test Results:')
    print('='*60)


def measureSignalStrength(cardDir):
    '''
        Measure signal strength using MultiDimFit method
        Reference: https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/latest/part5/longexercise/#e-signal-strength-measurement-and-uncertainty-breakdown
    '''
    datacardFile = cardDir + 'workspace/datacard.root'
    outFolder = cardDir + 'combineResults/'

    signalStrengthDir = outFolder + 'signalStrength/'
    if not os.path.exists(signalStrengthDir):
        os.mkdir(signalStrengthDir)

    # Likelihood scan
    scanCommand = 'combine -M MultiDimFit {} --algo grid --points 100 --rMin 0 --rMax 10 --redefineSignalPOIs r -n .scan'.format(datacardFile)
    runCommand(scanCommand)

    # Fit with only statistical uncertainty (freeze all nuisance parameters)
    fitSnapCommand = f'combine -M MultiDimFit {datacardFile} -n .snapshot --rMin 0 --rMax 10 --saveWorkspace'
    runCommand(fitSnapCommand)
    freezeAllCommand = 'combine -M MultiDimFit higgsCombine.snapshot.MultiDimFit.mH120.root -n .freezeAll --rMin 0 --rMax 10 --algo grid --points 100 --freezeParameters allConstrainedNuisances --snapshotName MultiDimFit'
    runCommand(freezeAllCommand)
    # python plot1DScan.py higgsCombine.part3E.MultiDimFit.mH200.root --others 'higgsCombine.part3E.freezeAll.MultiDimFit.mH200.root:FreezeAll:2' -o freeze_second_attempt --breakdown Syst,Stat
    # fitStatCommand = 'combine -M MultiDimFit {} --algo singles --redefineSignalPOIs r --freezeParameters allConstrainedNuisances --rMin 0 --rMax 10 -n .stat'.format(datacardFile)
    # runCommand(fitStatCommand)
    # Plot likelihood scan (plot1DScan.py is in PATH after cmsenv)
    # Overlay stat-only scan to show total vs statistical uncertainty, systematic is derived
    plotScanCommand = "plot1DScan.py higgsCombine.scan.MultiDimFit.mH120.root --others 'higgsCombine.freezeAll.MultiDimFit.mH120.root:StatOnly:2' -o scan_plot --breakdown Syst,Stat"
    runCommand(plotScanCommand)

    # Move files - only move files that actually exist
    mv = 'mv higgsCombine*.root combine_logger.out {}'.format(signalStrengthDir)
    runCommand(mv)

    # Move plot files if they exist
    mvPlot = 'if ls scan_plot.* 1> /dev/null 2>&1; then mv scan_plot.* {}; fi'.format(signalStrengthDir)
    runCommand(mvPlot)

    # Report uncertainties
    print('Signal strength results here: ', signalStrengthDir)
    print('\n' + '='*60)
    print('Signal Strength and Uncertainty Breakdown:')
    print('='*60)

    # Extract values from ROOT files using combine's output format
    extractTotal = 'cd {} && combine -M MultiDimFit higgsCombineTest.MultiDimFit.mH120.root --algo singles --redefineSignalPOIs r --saveWorkspace 2>&1 | grep "r :"'.format(signalStrengthDir)
    extractStat = 'cd {} && combine -M MultiDimFit higgsCombine.stat.MultiDimFit.mH120.root --algo singles --redefineSignalPOIs r --saveWorkspace 2>&1 | grep "r :"'.format(signalStrengthDir)

    print('\nRunning uncertainty extraction...')
    runCommand(extractTotal)
    runCommand(extractStat)

    print('\nTo extract the values manually, run:')
    print('cd {} && combine -M MultiDimFit higgsCombineTest.MultiDimFit.mH120.root --algo singles --redefineSignalPOIs r --saveWorkspace 2>&1 | grep "r :"'.format(signalStrengthDir))
    print('cd {} && combine -M MultiDimFit higgsCombine.stat.MultiDimFit.mH120.root --algo singles --redefineSignalPOIs r --saveWorkspace 2>&1 | grep "r :"'.format(signalStrengthDir))
    print('\nSystematic uncertainty = sqrt(total_unc^2 - stat_unc^2)')
    print('='*60)


def runPostFitPlots(cardDir):
    '''Using CMSSW14_1_0_pre4 to run postfit plots'''
    for ifile in os.listdir(cardDir+'workspace/'):
        if ifile.find('root')>0:
            print('ifile: ', ifile)
            outFolder = cardDir + 'combineResults/'
            wf = cardDir + 'workspace/' + ifile
    
            postfitDir = outFolder+ 'postfitPlots/'
            if not os.path.exists(postfitDir):
                os.mkdir(postfitDir)
            fitCommand = 'combine -M FitDiagnostics {}  --rMin 0 --rMax 20 --saveShapes --saveWithUncertainties --cminDefaultMinimizerStrategy 0'.format(wf) #generate fitDiagnostics_postfit.root
            #[WARNING]: Unable to determine uncertainties on all fit parameters in b-only fit. The option --saveWithUncertainties will be ignored as it would lead to incorrect results --> This means the covariance matrix calculated in FitDiagnostics was not correct.
            # plotCommand = 'python diffNuisances.py fitDiagnostics_postfit.root --all --output-file {}/nuisancePostFit.txt '.format(postfitDir)
            # plotCommand2 = 'python plotNuisances.py -i {}/nuisancePostFit.txt -o {}/nuisancePostFit '.format(postfitDir, postfitDir)
            # mv = 'mv fitDiagnostics_postfit.root nuisancesPostFit.pdf combine_logger.out {}'.format(postfitDir)
            runCommand(fitCommand)
            # runCommand(plotCommand)
            # runCommand(plotCommand2)
            # runCommand(mv)
            # print('postfitPlots here: ', postfitDir+'nuisancePostFit.pdf')

    
    
def runImpact(cardDir, ifBlind=True):
    for ifile in os.listdir(cardDir+'workspace/'):
        if ifile.find('root')>0:
            print('ifile: ', ifile)
            outFolder = cardDir + 'combineResults/'
            wf = cardDir + 'workspace/' + ifile
    
            impacDir = outFolder+ 'impactResult/'
            if not os.path.exists(impacDir):
                os.mkdir(impacDir)
            step1 = 'combineTool.py -M Impacts -d {} -m 125 --doInitialFit --robustFit 1  '.format(wf)
            # step2 = 'combineTool.py -M Impacts -d {} -m 125 --robustFit 1 --doFits  '.format(wf) 
            step2 = 'combineTool.py -M Impacts -d {} -m 125 --robustFit 1 --doFits --parallel 8 --job-mode "interactive"'.format(wf) 
            step3 = 'combineTool.py -M Impacts -d {} -m 125 -robustFit 1 -o {}/impacts.json '.format(wf, impacDir)
            step4 = 'plotImpacts.py -i {}impacts.json -o impacts'.format(impacDir)
            mv = 'mv higgsCombine_paramFit*.root impacts.pdf combine_logger.out {}'.format(impacDir)
            runCommand(step1)
            runCommand(step2)
            runCommand(step3)
            runCommand(step4)
            runCommand(mv)
            print('impactPlot here: ', impacDir+'impacts.pdf')

def runCommand(com):
    print('run command: ', com)
    # Set environment to ignore user site-packages, use only CMSSW packages
    env = os.environ.copy()
    env['PYTHONNOUSERSITE'] = '1'
    process = subprocess.Popen( com, shell=True, env=env )
    out = process.communicate()
    print(out)
    print('\n')
    

def copyCombineResultsToDir( cardDir ):
    resultsDir = cardDir+ 'combineResults/'
    print( 'combineResultsDir', resultsDir )
    if not os.path.exists( resultsDir ):
        os.mkdir( resultsDir )
    # command = 'mv higgsCombineTMVApp*root {}'.format( resultsDir  )
    command = 'mv higgsCombine*root {}'.format( resultsDir  )
    process = subprocess.Popen( command, shell=True )
    out = process.communicate()


# def runCombineSig( cardDir, isLimit ):
def runCombineSig( cardDir, isLimit, ifBlind=True ):
    workspaceDir =  cardDir + 'workspace/'
    resultDir = workspaceDir+'results/'
    if not os.path.exists(resultDir):
        os.mkdir( resultDir )
    for ifile in os.listdir( workspaceDir ):
        if ifile.find( 'root')>0:
            iname = '_'+ ifile.split('.root')[0]
            irootF = workspaceDir + ifile
            print("iname: ", iname)
            if isLimit:
                if ifBlind:
                    significanceCommand = 'combine -M AsymptoticLimits {rootFile} --run blind --name {name}'.format( rootFile=irootF, name=iname )
                else:
                    significanceCommand = 'combine -M AsymptoticLimits {rootFile} --name {name}'.format( rootFile=irootF, name=iname ) 
            else:
                if ifBlind:
                    significanceCommand = 'combine -M Significance {rootFile} -t -1 --expectSignal=1 --name {name}'.format( rootFile=irootF, name=iname )
                else:
                    significanceCommand = 'combine -M Significance {rootFile} --name {name}'.format( rootFile=irootF, name=iname )
            print( significanceCommand )
            env = os.environ.copy()
            env['PYTHONNOUSERSITE'] = '1'
            irunSig = subprocess.Popen( [significanceCommand] ,
                    shell=True,
                    env=env
                    )
            irunSigOut = irunSig.communicate()[0]
            print( irunSigOut )


def cardToWorkspaces( cardDir):
    print('start to turn datacard into workspace.........................\n')
    for en in os.listdir( cardDir ):
        if not '.txt' in en: continue
        idatacard = en
        idatacard = cardDir +  idatacard
        if os.path.isfile( idatacard ):
            print( 'idatacard: ', idatacard )
            iworkspaceName = en[:]
            iworkspaceName = iworkspaceName.replace('.txt', '.root' )
            print('iworkspaceName; ', iworkspaceName )
            iworkspaceDir = cardDir + 'workspace/'
            if not os.path.exists(iworkspaceDir):
                os.mkdir( iworkspaceDir )
    #
            iworkspace = iworkspaceDir + iworkspaceName
            command = 'text2workspace.py {da} -o {work}'.format( da=idatacard, work=iworkspace )
            print( 'command: ', command )

            env = os.environ.copy()
            env['PYTHONNOUSERSITE'] = '1'
            iprocess = subprocess.Popen( [command], shell=True, env=env )
            output = iprocess.communicate()[0]
            # output = iprocess.communicate()
            print( output)
    print( 'workpace transformation done!...............................\n' )
    print('\n')
    print('\n')



if __name__ == '__main__':
    main()

    #!1tau1l
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/datacardSys_v6AllSysWithFR/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/datacardSys_v6AllSysWithFR/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/datacardSys_v6AllSysWithFR/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/datacardSys_v0basic/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/datacardSys_v6AllSysWithFR/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV2/combine/datacardSys_v0basic/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV2/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/combine/datacardSys_v3BasicAndJES/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/combine/datacardSys_v4BasicAndJESJER/'
# cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV15/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV16/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV16/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV16/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV16/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/datacardSys_v8JESFlavorSplit/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/datacardSys_v8JESFlavorSplit/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/datacardSys_v8JESFlavorSplit/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/datacardSys_v8Smoothed/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/datacardSys_v6smoothed/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys/'

    #!1tau0l
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v2JESadded/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v3JESadded/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v6AllSysV2/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v7OnlyTauFR/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV2/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV16/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV16/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV16/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV16/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/combine/datacardSys_v6AllSys/'
    
    
    #!1tau2l
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v5BasicTTXDeorrelated/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noFSRSingleTop/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v0/'#!Problem with r value not 1
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noMinor/'#!fixed by not adding Minor
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noMinor/'#!fixed by not adding Minor
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v0/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/combine/datacardSys_v6AllSysWithFR/' 
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV16/combine/datacardSys_v5BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV16/combine/datacardSys_v5BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV16/combine/datacardSys_v5BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV16/combine/datacardSys_v5BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys/'