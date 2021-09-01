import os
import ROOT
import sys
#  import /workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/autoTraining_correlation/plotAUC
sys.path.insert(1, '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/autoTraining_correlation/')
import plotAUC

def main():
    resultDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/combine/1tau1l_v2/'
    variable_nums, mediumLimits = getMediumLimit( resultDir, False )
    variable_numsSig, mediumSigs = getMediumLimit( resultDir, True )

    outDir = resultDir + 'combineResults/'
    if not os.path.exists(outDir):
        os.mkdir( outDir )
    #  plotAUC.plot2D( variable_nums, mediumLimits, 'expectedLimit' , outDir)
    plotAUC.plot2D( variable_nums, mediumLimits, 'expectedLimit' , outDir)
    plotAUC.plot2D( variable_numsSig, mediumSigs, 'expectedSigs', outDir)

#  def getMediumSigs( resultDir )


def getMediumLimit( resultDir, isSig ):
    variable_nums = []
    mediumLimits = []
    for ifile in os.listdir( resultDir ):
        if (not isSig) and ifile.find( 'AsymptoticLimits')>0:
            print( 'ifile: ',ifile )
            variable_nums.append( getVarNum( ifile) )
            mediumLimits.append( getSingleLimit( resultDir + ifile , isSig) )
        if isSig and (ifile.find( 'Significance')>0):
            print( 'ifile: ',ifile )
            variable_nums.append( getVarNum( ifile) )
            mediumLimits.append( getSingleLimit( resultDir + ifile, isSig)  )

    return variable_nums, mediumLimits

def getSingleLimit( limitFile, isSig ):
    rootF = ROOT.TFile( limitFile )
    tree = rootF.Get( 'limit')
    #  limit = 0.0
    #  limitBranch = ROOT.TBranch(0)
    mediumLimit = 0.0
    i=0
    for event in tree:
        i=i+1
        print( event.limit )
        if isSig and i==1:
            mediumLimit = event.limit
        if (not isSig) and i==3 :
            mediumLimit = event.limit

    print( mediumLimit )
    return mediumLimit



def getVarNum( rootFile ):
    varNum = rootFile[ 26:rootFile.find('var')]
    varNum = int(varNum)
    print( varNum )
    return varNum










if __name__ == '__main__':
    main()
