
import os
import subprocess

def main():
    rootDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baselineSelection_fromV15/'

    histDir = rootDir + 'variableHists/'
    if not os.path.exists(histDir):
        os.mkdir( histDir )

    for ifile in os.listdir( rootDir ):
        if '.root' in ifile:
            iProcess = ifile[:-5]
            print(iProcess)
            command = 'root -q -b \'run_writeHist.C( \"{}\", \"{}\" )\' '.format( rootDir, iProcess )
            print( command )
            process = subprocess.run( command, shell=True )
            output = process.stdout
            print( output )
            print( '\n' )





if __name__ == '__main__':
    main()