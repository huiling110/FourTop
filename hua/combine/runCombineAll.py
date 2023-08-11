import os
import subprocess
import sys

import usefulFunc as uf

sys.path.insert(1, '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/autoTraining_correlation/')
# import plotCombineResults as plot

#  import ROOT
#!!!run this with python2 because the CMSSW supports only python2


def main():
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v1sysVariation1tau1l/combine/datacard/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v2traingWithBtag/combine/datacardNoSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v1sysVariation1tau1l/combine/datacardNoSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v3withBjetT/combine/datacardNoSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v41tau0lGenTauSys/combine/datacard/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v41tau0lGenTauSys/combine/datacardNoSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v41tau0lGenTauSys/combine/datacardAllButBtag/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v3withBjetT/combine/datacardSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v41tau0lGenTauSys/combine_test/datacardOnlyFR/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v41tau0lGenTauSys/combine_modifyFakeDataError/datacardOnlyFR/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v41tau0lGenTauSys/combine_modifyFakeDataError/datacardOnlyBtagCerr2/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v41tau0lGenTauSys/combine_modifyFakeDataError/datacardBtagCerr2AndFR/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v8tau1elCut_v60fixeJetBtagBug/mc/variableHists_v0trainingWithBtagShape/combine/datacardNoSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v8tau1elCut_v60fixeJetBtagBug/mc/variableHists_v1traingWithBtagWP/combine/datacardNoSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v8tau1elCut_v60fixeJetBtagBug/mc/variableHists_v0trainingWithBtagShape/combine/datacardSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v8tau1elCut_v60fixeJetBtagBug/mc/variableHists_v1traingWithBtagWP/combine/datacardSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3btagWeightGood_v61fixesLepRemovalBug/mc/variableHists_v1traingWithBtagWP/combine/datacardSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/mc/variableHists_v1traingWithBtagWP/combine/datacardSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1btagWPandRUpdated_v61fixesLepRemovalBug/mc/variableHists_v1traingWithBtagWP/combine/datacardSys/'
    cardDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/combine/combinationV6/Run2_1tau1l/'

    
    

    cardToWorkspaces( cardDir )
# # # # #
    runCombineSig( cardDir, True )
    runCombineSig( cardDir, False )
    copyCombineResultsToDir( cardDir )
    
    runImpact(cardDir+'workspace/datacard_1tau1lSys.root', cardDir+'combineResults/')
    # runImpact(cardDir+'workspace/datacard_1tau0lSys.root', cardDir+'combineResults/')

    # plot.main( cardDir+ 'combineResults/')
    
    
def runImpact(wf, outFolder):
    impacDir = outFolder+ 'impactResult/'
    uf.checkMakeDir(impacDir)
    # step1 = 'combineTool.py -M Impacts -d {} -m 125 --doInitialFit --robustFit 1  --rMin -10 --rMax 10'.format(wf)
    # step2 = 'combineTool.py -M Impacts -d {} -m 125 --robustFit 1 --doFits  --rMin -10 --rMax 10'.format(wf)
    # step3 = 'combineTool.py -M Impacts -d {} -m 125 -robustFit 1 -o {}/impacts.json --rMin -10 --rMax 10'.format(wf, impacDir)
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
    uf.checkMakeDir(resultDir)
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
