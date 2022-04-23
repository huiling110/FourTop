
import os
import subprocess

def main():
    inputTemplateFileFolder = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_80bins/'
    for ifile in os.listdir( inputTemplateFileFolder ):
        if '.root' in  ifile:
            command = 'root -q -b \'checkTemplatesForCombine.C( \"{}\", \"{}\" )\' '.format( inputTemplateFileFolder, ifile )
            print( command )
            process = subprocess.run( command, shell=True )
            output = process.stdout
            print( output )  
            print( '\n' )
            







if __name__ == '__main__':
    main()