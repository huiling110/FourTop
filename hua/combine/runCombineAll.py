import os
import sys
#  import ROOT

import subprocess

import plotCombineResults as plot

def main():

    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/2tau1l_HT/datacard/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/combination/'
    # cardDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop/hua/combine/combination/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_11bins/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_20bins/datacard/sumDC_10/'
    # cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_40bins/datacard/sumDC_10/'
    cardDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_80bins/datacard/sumDC_10/'

    cardToWorkspaces( cardDir )
#
    runCombineSig( cardDir, True )
    runCombineSig( cardDir, False )
#
    copyCombineResultsToDir( cardDir )

    plot.main( cardDir+ 'combineResults/')

def copyCombineResultsToDir( cardDir ):
    resultsDir = cardDir+ 'combineResults/'
    print( 'combineResultsDir', resultsDir )
    if not os.path.exists( resultsDir ):
        os.mkdir( resultsDir )
    command = 'mv higgsCombineTMVApp*root {}'.format( resultsDir  )
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

            #  iprocess = subprocess.run( [command],
                    #  shell=True,
                    #  )
            #  output = iprocess.stdout
            iprocess = subprocess.Popen( [command], shell=True )
            output = iprocess.communicate()[0]
            print( output)
    print( 'workpace transformation done!' )



if __name__ == '__main__':
    main()
