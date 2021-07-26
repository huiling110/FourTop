
import sys
import os
import subprocess
import plotAUC

def main( ):
    TMVAFileDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v1/'
    #  TMVAFileDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau2os_v1/'
    #  TMVAFileDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v1/'
    #  TMVAFileDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau2l_v1/'
    print( 'TMVAFileDir: ', TMVAFileDir )


    variableNum_BDT, sig_BDT = [], []
    variableNum_BDTG, sig_BDTG = [], []


    for entry in os.listdir( TMVAFileDir ):
        #  print( entry )
        if os.path.isfile( TMVAFileDir+entry ):
            #  continue
            #  if entry.find( 'varibleList'):
            if  'varibleList' in entry:
                #  print( entry )
                #  command = 'root -q ../plotAll.C(' + '\"' + TMVAFileDir + entry + '\" )'
                command = 'root -l -b -q \'/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/plotAll.C(' + '\"' + TMVAFileDir + entry + '\" )\''
                print( command )
                process = subprocess.run( [command], 
                        shell=True,
                        capture_output=True,
                        text=True,
                         #  stdout=subprocess.PIPE,
                        bufsize=1,
                        universal_newlines=True
                        )
                # we’re invoking a shell at the start of the execution of our subprocess, and the command argument is interpreted directly by the shell
                #  output = process.stdout.strip()
                output = process.stdout
                print( output)
                #  for line in output:
                findNum = 1
                for line in output.split(os.linesep):
                    if 'BDT_sigMax' in line:
                        #  print( line )
                        #  print( repr(line))
                        line_Sig = line[13:]
                        BDTSig = float( line_Sig )
                        #  print( BDTSig )
                        sig_BDT.append( BDTSig )
                    if 'BDTG_sigMax' in line:
                        #  print( line )
                        line_Sig = line[13:]
                        BDTGSig = float( line_Sig )
                        sig_BDTG.append( BDTGSig )
                    if 'inputNum' in line and findNum%2==1:
                        findNum +=1
                        line = line[11:]
                        num = int(line)
                        variableNum_BDT.append( num )
                        variableNum_BDTG.append( num )
                    
                        

    print( len(sig_BDT), sig_BDT )
    print( len(sig_BDTG), sig_BDTG )

    #  print( len(variableNum_BDT),variableNum_BDT )

    #plot sig
    logDir = TMVAFileDir + 'log/'
    plotAUC.plotAUC(  variableNum_BDT, sig_BDT, logDir, True, True )
    plotAUC.plotAUC(  variableNum_BDTG, sig_BDTG, logDir, False, True )



if __name__ == '__main__':
    main()
