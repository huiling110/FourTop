import os
import subprocess
import sys

sys.path.insert(1, '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/autoTraining_correlation/')
import plotCombineResults as plot

#  import ROOT
#!!!run this with python2 because the CMSSW supports only python2


def main():

    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau1l_v4/AppResults_30bins/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau1l_v4/AppResults_60bins/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau1l_v4/AppResults_90bins/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau2l_v1/AppResults_30bins/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau2l_v2/AppResults_30bins/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/2tau0l_HT/datacard/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau0l_HT/datacard_error_L/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/AppResults_30bins/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/AppResults_30bins/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v3extra1tau1lCut_v42fixedChargeType/1tau1l_v0/AppResults_30bins/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v6Cut1tau1lVariableFixed_v42fixedChargeType/1tau1l_v0/AppResults_30bins/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2018/v6Cut1tau1lVariableFixed_v42fixedChargeType/1tau1l_v0/AppResults_30bins/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1fixedTauVariables_v40addTauJetEtau/mc/variableHists_v4forFRAddHistTitle/1tau0l_templatesForCombine/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_v41addVertexSelection/mc/variableHists_v1HT30bins1tau0l/1tau0l_templatesForCombine/datacard/sumDC_10/'
    # cardDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/combine/combination/combination1/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_v41addVertexSelection/mc/combination/combination2/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4baseline_v42fixedChargeType/mc/variableHists_v0forVariables1tau0l/1tau0l_templatesForCombine/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_v42fixedChargeType/mc/variableHists_v0forVariables1tau0l/1tau0l_templatesForCombine/datacard/sumDC_10/'
    # cardDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/combine/combination/combinationRun2_1tau0l/'
    cardDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/combine/combination/comRun2_1tau1l/'
    

    cardToWorkspaces( cardDir )
#
    runCombineSig( cardDir, True )
    runCombineSig( cardDir, False )
# #
    copyCombineResultsToDir( cardDir )

    # plot.main( cardDir+ 'combineResults/')

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
    for ifile in os.listdir( workspaceDir ):
        if ifile.find( 'root')>0:
            iname = ifile[:-15]
            irootF = workspaceDir + ifile
            print("iname: ", iname)
            if isLimit:
                significanceCommand = 'combine -M AsymptoticLimits {rootFile} --run blind --name {name}'.format( rootFile=irootF, name=iname )
            else:
                significanceCommand = 'combine -M Significance {rootFile} -t -1 --expectSignal=1 --name {name}'.format( rootFile=irootF, name=iname )
            print( significanceCommand )
            irunSig = subprocess.Popen( [significanceCommand] ,
                    shell=True
                    )
            irunSigOut = irunSig.communicate()[0]
            print( irunSigOut )


def cardToWorkspaces( cardDir):
    for en in os.listdir( cardDir ):
        if not '.txt' in en: continue
        idatacard = en
            #  idatacard = 'TMVApp_1tau1l_11var_datacard.txt'
        idatacard = cardDir +  idatacard
        if os.path.isfile( idatacard ):
            print( 'idatacard: ', idatacard )
            iworkspaceName = en[:]
            iworkspaceName = iworkspaceName.replace('datacard.txt', 'workspace.root' )
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
    print( 'workpace transformation done!' )
    print('\n')
    print('\n')



if __name__ == '__main__':
    main()
