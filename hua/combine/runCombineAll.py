import os
import subprocess
import sys


#!!!run this with python2 because the CMSSW supports only python2

def main():
    #!1tau1l
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4NoJESForTTX/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4NoJESForTTX/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v90MuonESHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v1proNormAdd/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v90MuonESHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v2OnlyJES/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v90MuonESHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v3BasicAndJES/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v90MuonESHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v91TESAddedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v5BasicAndTES/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v91TESAddedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6BasicAndTESJES/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v91TESAddedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v3BasicAndJES/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v91TESAddedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v93HadroPreJetVetoPileupID/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v3BasicAndJES/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/datacardSys_v6AllSysWithFR/'

    #!1tau0l
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v2JESadded/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v3JESadded/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v6AllSysV2/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v7OnlyTauFR/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/'
    
    #!1tau2l
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v3BasicAndJES/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v3BasicAndJESFixed/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v4BasicTheoreyDecorrelated/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v5BasicTTXDeorrelated/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noFSRSingleTop/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v4BasicAndJESJER/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v0/'#!Problem with r value not 1
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noMinor/'#!fixed by not adding Minor
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noMinor/'#!fixed by not adding Minor
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v0/'
    cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/combine/datacardSys_v6AllSysWithFR/' 

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
    # cardDir = 'combinationV11/run2_1tau1l/'
    # cardDir = 'combinationV11/run2_1tau0l/' # no JES
    # cardDir = 'combinationV11/run2_1tau2l/' # no JES
    # cardDir = 'combinationV11/run2_3years/' # no JES
    # cardDir = 'combinationV12/run2_1tau0l/'
    # cardDir = 'combinationV12/run2_1tau1l_v2/'
    # cardDir = 'combinationV13/run2_1tau1l/'
    # cardDir = 'combinationV13/run2_1tau0l/'
    # cardDir = 'combinationV13/run2_1tau2l_JESJER/'
    # cardDir = 'combinationV13/run2_1tau2l/'
    # cardDir = 'combinationV13/run2_3years/'

     
     
        
    cardToWorkspaces( cardDir )
    runCombineSig( cardDir, True )
    runCombineSig( cardDir, False )
    copyCombineResultsToDir( cardDir )

    runImpact(cardDir )

    
    
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
