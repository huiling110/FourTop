
# import ROOT
import os
import subprocess

# pre_dir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/v2Add2Variables_fromV9/'
# post_dir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_postVFP/v2Add2Variables_fromV9/' 
# merged_dir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2Add2Variables_fromV9/'
# pre_dir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/v3correctBjetsvariable_fromV9/'
# post_dir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_postVFP/v3correctBjetsvariable_fromV9/' 
# merged_dir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3correctBjetsvariable_fromV9/'
# pre_dir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/v4modifiedMinDeltaR_fromV9/'
# post_dir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_postVFP/v4modifiedMinDeltaR_fromV9/' 
# merged_dir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4modifiedMinDeltaR_fromV9/'
version = 'v0baseline_v16_HLTselection/'
ifJustMC = False

# pre_dir_base = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/'
# post_dir_base = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_postVFP/'
pre_dir_base = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/'
post_dir_base = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/'
merged_dir_base = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/'
pre_dir = pre_dir_base + version
post_dir = post_dir_base + version
merged_dir = merged_dir_base + version


if not os.path.exists( merged_dir ):
    os.mkdir( merged_dir )

preDirDict = {}
postDirDict = {}
mergedDirDict = {}
preDirDict['mc'] = pre_dir + 'mc/'
postDirDict['mc'] = post_dir + 'mc/'
mergedDirDict ['mc']= merged_dir + 'mc/'
if not ifJustMC:
    preDirDict['data'] = pre_dir + 'data/'
    postDirDict['data'] = post_dir + 'data/'
    mergedDirDict['data'] = merged_dir + 'data/'


for ikey in preDirDict.keys():
    print( ikey )
    if not os.path.exists( mergedDirDict[ikey] ):
        os.mkdir( mergedDirDict[ikey] )
    for i in os.listdir( preDirDict[ikey] ):

        if os.path.isdir( preDirDict[ikey] + i ):
            continue

        ifile = preDirDict[ikey]  + i
        ifile_post = postDirDict[ikey] + i 
        ifile_merged = mergedDirDict[ikey] + i

        icommand = 'hadd {} {} {}'.format( ifile_merged, ifile, ifile_post )
        print( icommand )
        process = subprocess.run( icommand, shell=True )
        output = process.stdout
        print( output )


 





