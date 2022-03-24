
# import ROOT
import os
import subprocess

pre_dir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/v1_fromV8/'
post_dir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_postVFP/v1_fromV8/' 
merged_dir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1_fromV8/'


if not os.path.exists( merged_dir ):
    os.mkdir( merged_dir )




ifile = pre_dir  + 'tttt.root'
ifile_post = post_dir + 'tttt.root'
ifile_merged = merged_dir + 'tttt.root'

icommand = 'hadd {} {} {}'.format( ifile_merged, ifile, ifile_post )
print( icommand )
process = subprocess.run( icommand, shell=True )
output = process.stdout
print( output )


 





