

import os
import ROOT

from ttttGlobleQuantity import samples


def main():
    nanoDir = '/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/'
    sumGenDic = getSumGenFromRun( nanoDir )
    print(sumGenDic)

def getSumGenFromRun( nanoDir ):
    sumGenDic = {}
    for ifile in os.listdir( nanoDir ):
        if ifile not in samples: continue
        print(ifile)
        iProcessSum = 0.0 #maybe need more precision here
        for ioutTree in os.listdir( nanoDir+ifile):
            if not '.root' in ioutTree: continue
            iRoot = ROOT.TFile( nanoDir+ifile+'/'+ioutTree, 'READ' )
            iRunTree = iRoot.Get('Runs')
            # isum = 0.0
            # iRunTree.SetBranchAddress( 'genEventSumw', isum)
            for ientry in (0, iRunTree.GetEntries()):
                iRunTree.GetEntry(ientry)
                iProcessSum+=iRunTree.genEventSumw
            iRoot.Close()
        # print( ifile, ': ', iProcessSum )
        sumGenDic[ifile]=iProcessSum

    return sumGenDic




if __name__=='__main__':
    main()
