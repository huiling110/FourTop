
import sys
import os
import subprocess


def main( ):
    #  TMVAFileDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v1/'
    TMVAFileDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau2os_v1/'
    print( 'TMVAFileDir: ', TMVAFileDir )

    for entry in os.listdir( TMVAFileDir ):
        #  print( entry )
        if os.path.isfile( TMVAFileDir+entry ):
            #  continue
            #  if entry.find( 'varibleList'):
            if  'varibleList' in entry:
                print( entry )
                #  command = 'root -q ../plotAll.C(' + '\"' + TMVAFileDir + entry + '\" )'
                command = 'root -l -b -q \'/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/plotAll.C(' + '\"' + TMVAFileDir + entry + '\" )\''
                print( command )
                process = subprocess.run( [command], 
                         #  stdout=subprocess.PIPE,
                         shell=True)
                         #  universal_newlines=True)



if __name__ == '__main__':
    main()
