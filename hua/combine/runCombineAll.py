import os
import subprocess
import sys


#!!!run this with python2 because the CMSSW supports only python2

def main():
    #1tau1l
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v2leptonsNameChange/mc/variableHists_v0NoSystematic/combine/datacardNoSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v2leptonsNameChange/mc/variableHists_v0NoSystematic/combine/datacardNoSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_V0Basictraining_bin3/combine/datacardMainSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v76For1tau2l/mc/variableHists_v0BDT1tau2l/combine/datacards_mainSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_newTriSFBinD_v75OverlapRemovalFTau/mc/variableHists_v0Basictraining1tau1l/combine/datacards_mainSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_newTriSFBinD_v75OverlapRemovalFTau/mc/variableHists_v0Basictraining1tau1l/combine/datacards_noSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE2/combine/datacard_noSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT1tau1l_binE2/combine/datacard_sys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v81addSysSum/mc/variableHists_v2BDT1tau1l_binE2/combine/datacard_sys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/combine/datacard_sys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v86HadroPreSelWithTTWTTZNLO/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v0/'

    #1tau0l
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baselineHardro_FRweightSys_v76WithVLLSample/mc/variableHists_v0BDT1tau0l_3bins/combine/datacard_noPdfAlphaS/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHardro_FRweightSys_v79HadroPresel/mc/variableHists_v0BDT1tau0l/combine/datacardSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardro_btagMTWeight_v76WithVLLAllMass/mc/variableHists_v0BDT1tau0lBinB/combine/datacardSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputsWith2018train/combine/datacardSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardroFRUpdated_v85HadroPreselTauOverlap0.5/mc/variableHists_v0BDT1tau0l/combine/datacardSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v86HadroPreSelWithTTWTTZNLO/mc/variableHists_v2BDT1tau0lBinC/combine/datacardSys_v0/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v86HadroPreSelWithTTWTTZNLO/mc/variableHists_v2BDT1tau0lBinC/combine/datacardSys_v1proNormAdd/'
    
    #!1tau2l
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/combine/datacard_sys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/combine/datacard_sys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/combine/datacard_sys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v87LepPreSel_GammaRemovalBugFixed/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v1proNormAdd/'
    cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v87addPdfPSWeightSum/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v1proNormAdd/'
    

    #combination
    # cardDir = 'combinationV6/run2_1tau0l/'
    # cardDir = 'combinationV6/run2_bothChannels/'
    # cardDir = 'combinationV6/combinationRun2andRun3/'
    # cardDir = 'combinationV8/1tau1lCom/'
    # cardDir = 'combinationV8/run2_1tau1lAnd1tau0l/'
    # cardDir = 'combinationV8/run2_1tau0l/'
    # cardDir = 'combinationV9/run2_1tau1l/'
    # cardDir = 'combinationV9/run2_1tau0l/'
    # cardDir = 'combinationV9/run2/'
    # cardDir = 'combinationV9/2022_1tau1l/'
    # cardDir = 'combinationV9/run2AndRun3/'
    # cardDir = 'combinationV10/run2_1tau2l/'
    # cardDir = 'combinationV10/run2_1tau1l/'
    # cardDir = 'combinationV10/run2_1tau0l/'
    # cardDir = 'combinationV10/run2_3channels/'

     
     
        
    cardToWorkspaces( cardDir )
    runCombineSig( cardDir, True )
    runCombineSig( cardDir, False )
    copyCombineResultsToDir( cardDir )

    runImpact(cardDir )
    # runImpact(cardDir+'workspace/datacard_1tau1lSys.root', cardDir+'combineResults/')
    # runImpact(cardDir+'workspace/datacard_comb_1tau1l.root', cardDir+'combineResults/')
    # runImpact(cardDir+'workspace/datacard_comb_1tau0l.root', cardDir+'combineResults/')
    # runImpact(cardDir+'workspace/datacard.root', cardDir+'combineResults/')
    # runImpact(cardDir+'workspace/datacard_1tau0lCom.root', cardDir+'combineResults/')

# def runImpact()
    
    
def runImpact(cardDir):
    for ifile in os.listdir(cardDir+'workspace/'):
        if ifile.find('root')>0:
            print('ifile: ', ifile)
            # runImpact(cardDir+'workspace/'+ifile, cardDir+'combineResults/') 
            outFolder = cardDir + 'combineResults/'
            wf = cardDir + 'workspace/' + ifile
    
            impacDir = outFolder+ 'impactResult/'
            if not os.path.exists(impacDir):
                os.mkdir(impacDir)
            step1 = 'combineTool.py -M Impacts -d {} -m 125 --doInitialFit --robustFit 1  '.format(wf)
            step2 = 'combineTool.py -M Impacts -d {} -m 125 --robustFit 1 --doFits  '.format(wf)
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
    process = subprocess.Popen( com, shell=True )
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


def runCombineSig( cardDir, isLimit ):
    workspaceDir =  cardDir + 'workspace/'
    resultDir = workspaceDir+'results/'
    # uf.checkMakeDir(resultDir)
    if not os.path.exists(resultDir):
        os.mkdir( resultDir )
    for ifile in os.listdir( workspaceDir ):
        if ifile.find( 'root')>0:
            iname = '_'+ ifile.split('.root')[0]
            irootF = workspaceDir + ifile
            print("iname: ", iname)
            if isLimit:
                significanceCommand = 'combine -M AsymptoticLimits {rootFile} --run blind --name {name}'.format( rootFile=irootF, name=iname )
                # significanceCommand = 'combine -M AsymptoticLimits {rootFile} --run blind --name {name} -S {outDir}'.format( rootFile=irootF, name=iname, outDir=resultDir )
            else:
                significanceCommand = 'combine -M Significance {rootFile} -t -1 --expectSignal=1 --name {name}'.format( rootFile=irootF, name=iname )
            print( significanceCommand )
            irunSig = subprocess.Popen( [significanceCommand] ,
                    shell=True
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

            iprocess = subprocess.Popen( [command], shell=True )
            output = iprocess.communicate()[0]
            # output = iprocess.communicate()
            print( output)
    print( 'workpace transformation done!...............................\n' )
    print('\n')
    print('\n')



if __name__ == '__main__':
    main()
