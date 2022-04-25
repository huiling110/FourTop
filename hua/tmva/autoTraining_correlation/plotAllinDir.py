#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : plotAllinDir.py
# Author            : Huiling Hua <huahl@ihep.ac.cn>
# Date              : 03.10.2021
# Last Modified Date: 03.10.2021
# Last Modified By  : Huiling Hua <huahl@ihep.ac.cn>

import sys
import os
import subprocess
import plotAUC

def main( ):
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v1_fromV9/1tau1l_v1/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v2/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau2l_v1/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/2tau0l_v1/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3correctBjetsvariable_fromV9/1tau1l_v1/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3correctBjetsvariable_fromV9/1tau1l_v1/variableList_check/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3correctBjetsvariable_fromV9/1tau1l_v2/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau1l_v1/'
    TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau1l_v3/'
    
    print( 'TMVAFileDir: ', TMVAFileDir )
    #  plotSigOnly = True
    plotSigOnly = False

    channel = TMVAFileDir[-10:-4]
    print('channel: ', channel)
    # fileForVaribles = channel + 'varibleList_50.root'
    fileForVaribles = channel + 'varibleList_40.root'
    plotInputVariables( TMVAFileDir , fileForVaribles )

    if plotSigOnly:
        plotSigOnlyC = 'true'
    else:
        plotSigOnlyC = 'false'


    variableNum_BDT, sig_BDT = [], []
    variableNum_BDTG, sig_BDTG = [], []


    for entry in os.listdir( TMVAFileDir ):
        #  print( entry )
        if os.path.isfile( TMVAFileDir+entry ):
            #  continue
            if  'varibleList' in entry:
            # if  '.root' in entry:
                #  print( entry )
                # command = 'root -l -b -q \'/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/plotAll.C(' + '\"' + TMVAFileDir + entry + '\", '  + plotSigOnlyC + ' )\''
                command = 'root -l -b -q \'/workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop/hua/tmva/plotAll.C(' + '\"' + TMVAFileDir + entry + '\", '  + plotSigOnlyC + ' )\''
                print( command )
                process = subprocess.run( [command], 
                        shell=True,
                        capture_output=True,
                        text=True,
                         #  stdout=subprocess.PIPE,
                        # bufsize=1,
                        universal_newlines=True
                        )
                # we’re invoking a shell at the start of the execution of our subprocess, and the command argument is interpreted directly by the shell
                #  output = process.stdout.strip()
                output = process.stdout
                print( output)
                findNum = 1
                # for line in output:
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


    #plot sig
    logDir = TMVAFileDir + 'log/'
    plotAUC.plotAUC(  variableNum_BDT, sig_BDT, logDir, True, True )
    plotAUC.plotAUC(  variableNum_BDTG, sig_BDTG, logDir, False, True )

    #plot AUC
    if not plotSigOnly:
        plotAUC.getAUCToTGragh( logDir )
        
    

def plotInputVariables( TMVAFileDir, fileForVariables ):
    outForVariables = TMVAFileDir + 'results/variableDistribution/'
    if not os.path.exists( outForVariables ):
        os.mkdir( outForVariables )
    # command = 'root -q -b \'../variables.C( \"{}\",  \"{}\", \"TMVA Input Variables\", kFALSE, kTRUE      )\'  '.format( TMVAFileDir+fileForVariables, outForVariables ) 
    codeDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_6_27/src/FourTop/hua/tmva/'
    command = 'root -q -b \'{}variables.C( \"{}\",  \"{}\", \"TMVA Input Variables\", kFALSE, kTRUE      )\'  '.format( codeDir, TMVAFileDir+fileForVariables, outForVariables ) 
    print( command )
    process = subprocess.run( command, shell=True)   
    print( process.stdout )
    
    


if __name__ == '__main__':
    main()
