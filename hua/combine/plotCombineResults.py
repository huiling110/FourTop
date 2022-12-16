import os
import sys

import ROOT
import usefulFunc as uf

sys.path.insert(1, '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/autoTraining_correlation/')
import plotAUC


def main(
    # resultDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau1l_v1/AppResults/datacard/sumDC/combineResults/'
    # resultDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau1l_v1/AppResults_11bins/datacard/sumDC/combineResults/'
    # resultDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/AppResults_30bins/datacard/sumDC_10/combineResults/'
    resultDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/AppResults_30bins/datacard/sumDC_10/combineResults/'
        ):
    variable_nums, mediumLimits = getMediumLimit( resultDir, False )
    variable_numsSig, mediumSigs = getMediumLimit( resultDir, True )

    era = uf.getEraFromDir(resultDir)
    outDir = resultDir + 'combineResults/'
    uf.checkMakeDir(outDir)
    # plotAUC.plot2D( variable_nums, mediumLimits, 'expectedLimit_withError' , outDir, era)
    plotAUC.plot2D( variable_nums, mediumLimits, 'expectedLimit' , outDir, era)
    plotAUC.plot2D( variable_numsSig, mediumSigs, 'expectedSigs', outDir, era)



def getMediumLimit( resultDir, isSig ):
    variable_nums = []
    mediumLimits = []
    for ifile in os.listdir( resultDir ):
        if (not isSig) and ifile.find( 'AsymptoticLimits')>0:
            print( 'ifile: ', resultDir+ ifile )
            variable_nums.append( getVarNum( ifile) )
            mediumLimits.append( getSingleLimit( resultDir + ifile , isSig) )
        if isSig and (ifile.find( 'Significance')>0):
            print( 'ifile: ', resultDir + ifile )
            variable_nums.append( getVarNum( ifile) )
            mediumLimits.append( getSingleLimit( resultDir + ifile, isSig)  )

    return variable_nums, mediumLimits

def getSingleLimit( limitFile, isSig ):
    rootF = ROOT.TFile( limitFile )
    tree = rootF.Get( 'limit')
    #  limit = 0.0
    #  limitBranch = ROOT.TBranch(0)
    # mediumLimit = 0.0
    mediumLimit = [] # medium up , limit, down
    i=0
    for event in tree:
        i=i+1
        print( event.limit )
        if isSig and i==1:
            mediumLimit.append(event.limit)
        if (not isSig) and i==3 :
            # mediumLimit = event.limit
            mediumLimit.append(event.limit)
        if (not isSig) and i==2:
            mediumLimit.append(event.limit)
        if (not isSig) and i==4:
            mediumLimit.append(event.limit)

    print( mediumLimit )
    return mediumLimit



def getVarNum( rootFile ):
    varNum = rootFile[ 26:rootFile.find('var')]
    varNum = int(varNum)
    print( varNum )
    return varNum










if __name__ == '__main__':
    main()
