
import os

from ttttGlobleQuantity import samples
import makeJob_makeVaribles_forBDT as mj

import ROOT


def main():

    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v18HLTSelection/mc/'
    # outDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/'

    inOutDirMap = mj.getInOutDic( mj.year, mj.inputBase, mj.outputBase, mj.inVersion, mj.outVersion, mj.justMC  )
    print( inOutDirMap )

    inputDir = inOutDirMap['2016postVFP']['mc'][0] 
    # for ifile in os.listdir( inOutDirMap['2016postVFP']['mc'][0]+'ttbar_0l' ):
    #     print(ifile)
    print( len(inOutDirMap['2016postVFP']['mc'][0]+'ttbar_0l') )
    print( len(inOutDirMap['2016postVFP']['mc'][1]+'ttbar_0l') )

    # for ipro in os.listdir( inputDir ):
    #     if not ipro in samples: continue
    #     print( 'iProcess: ', ipro )
    #     iproOutFile = ROOT.TFile( inOutDirMap['2016postVFP']['mc'][1] + ipro +'.root', 'UPDATE'  )
    #     isummedHist_initial = ROOT.TH1D()
    #     for ifile in os.listdir(  inputDir+ipro ):
    #         if not '.root' in ifile: continue 
    #         # print( ifile )
    #         iRoot = ROOT.TFile( inputDir+ipro +'/'+ifile, 'READ' )
    #         iiHist_initial = iRoot.Get( 'h_initial')
    #         isummedHist_initial.Add( iiHist_initial )
    #         iRoot.Close()
    #         iiHist_initial.Reset()

    #     isummedHist_initial.Print()
    #     isummedHist_initial.Write()
    #     isummedHist.Reset()
    #     iproOutFile.ls()



    # for isam in samples:



if __name__=='__main__':
    main()