#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : plotAllinDir.py
# Author            : Huiling Hua <huahl@ihep.ac.cn>
# Date              : 03.10.2021
# Last Modified Date: 03.10.2021
# Last Modified By  : Huiling Hua <huahl@ihep.ac.cn>

import os
import subprocess

import plotAUC
import usefulFunc as uf


def main( ):
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau1l_v1/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau1l_v3/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau1l_v4/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau2l_v1/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau2l_v2/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v3extra1tau1lCut_v42fixedChargeType/1tau1l_v0/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v6Cut1tau1lVariableFixed_v42fixedChargeType/1tau1l_v0/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2018/v6Cut1tau1lVariableFixed_v42fixedChargeType/1tau1l_v0/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v6Cut1tau1lVariableFixed_v42fixedChargeType/1tau1l_v0/'
    # TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v8Cut1tau1l_v42fixedChargeType/1tau1l_v0/'
    TMVAFileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/1tau1l_v0/'
    
    print( 'TMVAFileDir: ', TMVAFileDir )
    #  plotSigOnly = True
    plotSigOnly = False

    channel = uf.getChannelFromDir( TMVAFileDir)
    era = uf.getEraFromDir(TMVAFileDir) 
    print('channel: ', channel)
    fileForVaribles = channel + 'varibleList_40.root'
    plotInputVariables( TMVAFileDir , fileForVaribles )




    variableNum_BDT, sig_BDT =  plotAll( TMVAFileDir , plotSigOnly)
    print( len(sig_BDT), sig_BDT )

    # #plot sig
    logDir = TMVAFileDir + 'log/'
    # plotAUC.plotAUC(  variableNum_BDT, sig_BDT, logDir, True, True )
    # plotAUC.plotAUC(  variableNum_BDTG, sig_BDTG, logDir, False, True )
    # #plot AUC
    if not plotSigOnly:
        plotAUC.getAUCToTGragh( logDir, era )
        
def plotAll( TMVAFileDir, plotSigOnly ):
    print('starting to plotAll.C')
    if plotSigOnly:
        plotSigOnlyC = 'true'
    else:
        plotSigOnlyC = 'false'
    variableNum_BDT, sig_BDT = [], []
    for entry in os.listdir( TMVAFileDir ):
        #  print( entry )
        if os.path.isfile( TMVAFileDir+entry ):
            #  continue
            if  'varibleList' in entry:
                #  print( entry )
                command = 'root -l -b -q \'/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/plotAll.C(' + '\"' + TMVAFileDir + entry + '\", '  + plotSigOnlyC + ' )\''
                print( command )
                process = subprocess.run( [command], 
                        shell=True,
                        capture_output=True,
                        text=True,
                        universal_newlines=True
                        )
                output = process.stdout
                print( output)
                findNum = 1
                # for line in output:
                for line in output.split(os.linesep):
                    if 'BDT_sigMax' in line:
                        line_Sig = line[13:]
                        BDTSig = float( line_Sig )
                        sig_BDT.append( BDTSig )
                    # if 'BDTG_sigMax' in line:
                    #     #  print( line )
                    #     line_Sig = line[13:]
                    #     BDTGSig = float( line_Sig )
                    if 'inputNum' in line and findNum%2==1:
                        findNum +=1
                        line = line[11:]
                        num = int(line)
                        variableNum_BDT.append( num )
                        
    print('done plotAll.C')
    return variableNum_BDT, sig_BDT

    

def plotInputVariables( TMVAFileDir, fileForVariables ):
    print( 'start to plot input variable  distribution')
    outForVariables = TMVAFileDir + 'results/variableDistribution/'
    if not os.path.exists( outForVariables ):
        os.mkdir( outForVariables )
    codeDir = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/'
    command = 'root -q -b \'{}variables.C( \"{}\",  \"{}\", \"TMVA Input Variables\", kFALSE, kTRUE      )\'  '.format( codeDir, TMVAFileDir+fileForVariables, outForVariables ) 
    print( command )
    process = subprocess.run( command, shell=True)   
    print( process.stdout )
    print( 'done input variable distribution')
    print('\n')
    print('\n')
    
    


if __name__ == '__main__':
    main()
