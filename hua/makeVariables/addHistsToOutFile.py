
import os

from ttttGlobleQuantity import samples
import makeJob_makeVaribles_forBDT as mj



def main():

    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_postVFP/v18HLTSelection/mc/'
    # outDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/'

    inOutDirMap = mj.getInOutDic( mj.year, mj.inputBase, mj.outputBase, mj.inVersion, mj.outVersion, mj.justMC  )
    print( inOutDirMap )

    for ipro in os.listdir( inOutDirMap['2016postVFP']['mc'][0] ):
        if not ipro in samples: continue
        print( 'iProcess: ', ipro )
        for ifile in os.listdir(  inOutDirMap['2016postVFP']['mc'][0]+ipro ):
            if not '.root' in ifile: continue 
            print( ifile )



    # for isam in samples:



if __name__=='__main__':
    main()