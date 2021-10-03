import os
import sys
#  import ROOT

import subprocess

import plotCombineResults as plot

def main():

    #  cardDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v2/AppResults/datacard/'
    #  cardDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau1l_v1/AppResults/datacard/'
    #  cardDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau1l_v1/AppResults/datacard/sumDC/'
    #  cardDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau1l_v1/AppResults/datacard/seperateDC/'
    #  cardDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau2l_v1/AppResults/datacard/sumDC/'
    #  cardDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/2tauXl_v1/AppResults/datacard/sumDC/'
    cardDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau1l_v1/AppResults_11bins/datacard/sumDC/'
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
    command = 'mv higgsCombineTMVApp*root {}'.format( resultsDir )
    #  process = subprocess.run( command, shell=True )
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
