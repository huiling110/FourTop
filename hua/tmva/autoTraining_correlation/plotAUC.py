#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : plotAUC.py
# Author            : Huiling Hua <huahl@ihep.ac.cn>
# Date              : 03.10.2021
# Last Modified Date: 03.10.2021
# Last Modified By  : Huiling Hua <huahl@ihep.ac.cn>

import csv
import os

import numpy as np
import ROOT
import setTDRStyle


def getAUCfromLog( logDir, histo):
    for entry in os.listdir( logDir ):
        if '.err' in entry:
            continue # The continue statement is used to skip the rest of the code inside a loop for the current iteration only. 
        #  print( entry)
        vListNum = entry[:-4]
        vListNum = vListNum[12:]
        vListNum = int(vListNum)
        print( vListNum )

        AUC_BDT, AUC_BDTG = getROC( logDir+entry)
        print( AUC_BDT, AUC_BDTG)

        histo.SetBinContent( vListNum, AUC_BDT)


def getAUCToTGragh( logDir):
    era = '2016'
    #x, y = array( 'd' ), array( 'd' )
    x, y = [], []
    x_BDTG, y_BDTG= [], []

    n = 0
    for entry in os.listdir( logDir ):
        
        if '.err' in entry:
            continue # The continue statement is used to skip the rest of the code inside a loop for the current iteration only. 
        #  print( entry)
        vListNum = entry[:-4]
        vListNum = vListNum[12:]
        vListNum = int(vListNum)
        #  print( vListNum )

        AUC_BDT, AUC_BDTG = getROC( logDir+entry)
        #  print( AUC_BDT, AUC_BDTG)
        x.append( vListNum )
        y.append( AUC_BDT )
        x_BDTG.append( vListNum )
        y_BDTG.append( AUC_BDTG )
        #  print(' i %i %f %f ' % ( n,x[n],y[n]))

        n = n+1
    
    plotAUC( x, y , logDir , True, False, era )
    # plotAUC( x_BDTG, y_BDTG, logDir,False, False )


def plotAUC( x, y, logDir, isBDT, isSig, era='2016' ):
    x, y = np.array([x,y])
    # x = np.array([x])
    # y = np.array([y])
    flag = np.argsort(x)
    x, y = x[flag], y[flag]


    c1 = ROOT.TCanvas( 'c1', 'A Simple Graph Example', 200, 10, 700, 500 )
    c1.SetGrid()
 
    n = len( x )
    gr = ROOT.TGraph( n, x, y )
    gr.SetLineColor( ROOT.kOrange )
    gr.SetLineWidth( 2 )
    gr.SetMarkerColor( ROOT.kRed )
    gr.SetMarkerStyle( 21 )
    # if isBDT: 
    #     if isSig:
    #         gr.SetTitle( 'Maximum Significance vs No. of Variables (BDT)' )
    #     else:
    #         gr.SetTitle( 'AUC vs No. of Variables (BDT)' )
    # else:
    #     if isSig:
    #         gr.SetTitle( 'Maximum Significance vs No. of Variables (BDTG)' )
    #     else:
    #         gr.SetTitle( 'AUC vs No. of Variables (BDTG)' )
    gr.SetTitle("")
    
    gr.GetXaxis().SetTitle( 'number of variables' )
    if isSig:
        gr.GetYaxis().SetTitle( 'Significance' )
    else:
        gr.GetYaxis().SetTitle( 'AUC' )
    gr.Draw('APL')

    setTDRStyle.addCMSTextToCan(c1, 0.17, 0.27, 0.91, era)

    AUCDir = logDir[:-4]
    #  print( AUCDir )
    AUCDir = AUCDir + 'results/'
    if not os.path.exists( AUCDir ):
        os.mkdir( AUCDir )

    if isBDT:
        if isSig:
            c1.SaveAs( AUCDir+'maxSig_BDT.png' )
        else:
            c1.SaveAs( AUCDir+'AUC_BDT.png' )
    else:
        if isSig:
            c1.SaveAs( AUCDir+'maxSig_BDTG.png' )
        else:
            c1.SaveAs( AUCDir+'AUC_BDTG.png' )

    print( 'plot saved here:', AUCDir )
    #  return gr


def plot2D(x, y, name, outDir, era  ): 
    # x, y = np.array([x,y])
    # flag = np.argsort(x)
    # x, y = x[flag], y[flag]
    
    limit = np.array(y)
    # print(limit)
    varNum = np.array([[i] for i in x])
    # print(varNum)
    appenedArray = np.append(limit,  varNum, axis=1)
    # print(appenedArray)
    appenedArray =  appenedArray[appenedArray[:,3].argsort()]
    print(appenedArray)
    varNum_x = appenedArray[:,3]
    limit = appenedArray[:,1]
    limit_up = appenedArray[:,2]
    limit_down = appenedArray[:,0]
    exl = np.zeros((len(varNum)))
    exh = np.zeros((len(varNum)))
    # print(varNum_x)
    # print(limit)
    # print(type(varNum_x))
    varNum_x = np.array(varNum_x)#???
    limit = np.array(limit)
    limit_down = np.array(limit_down)
    limit_down = np.subtract(limit, limit_down)
    limit_up = np.array(limit_up)
    limit_up = np.subtract(limit_up, limit)
    # print(type(limit))
    # print(limit_up)

    c1 = ROOT.TCanvas( 'c1', 'A Simple Graph Example', 200, 10, 700, 500 )
    c1.SetGrid()
 
    n = len( x )
    # gr = ROOT.TGraph( n, x, y )
    gr = ROOT.TGraphAsymmErrors( n, varNum_x, limit, exl, exh, limit_down, limit_up )
    gr.SetLineColor( ROOT.kOrange)
    gr.SetLineWidth( 2 )
    gr.SetMarkerColor( ROOT.kRed )
    gr.SetMarkerStyle( 21 )


    gr.GetXaxis().SetTitle( 'numer of variables' )
    #  if name.find( 'Limit'):
    if 'Limit' in name:
        gr.GetYaxis().SetTitle( 'expected limit' )
        # gr.SetTitle( "Expected Limit Vs Number of Variables" )
    else:
        # gr.SetTitle( "Expected Significance Vs Number of Variables" )
        gr.GetYaxis().SetTitle( 'expected significance' )
    gr.SetTitle("")
        

    gr.Draw('APL')
    
    setTDRStyle.addCMSTextToCan(c1, 0.17, 0.27, 0.91, era)
    c1.SaveAs( outDir + name + '.png' )
    print( 'plot saved here:', outDir )




def getROC( logFile):
    print( 'reading ', logFile, '\n')
    #  with open( logFile , "rb") as csv_file:
    with open( logFile ) as csv_file:
        csv_reader = csv.reader( csv_file, delimiter=':')
        ROCline = 0
        line = 0
        AUC_BDT = 0.0
        AUC_BDTG = 0.0
        for irow in csv_reader: # is seems log can contain strange char
            #  print( irow)
            #  print( len(irow))
            line+=1
            if len(irow) > 3:
                if 'ROC-integ' in irow[3]:
                    #  print( irow)
                    ROCline = line
            if line == ROCline +1:
                #  print( line )
                #  print( irow)
                if len(irow)>2:
                    AUC_BDT = irow[2]
            if line == ROCline+ 2:
                if len(irow)>2:
                    AUC_BDTG = irow[2]
        csv_file.close()
    return float(AUC_BDT), float(AUC_BDTG)



if __name__ == '__main__':
    #  logDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v1HT400Cut_v44_fixedSingJetHLTBugAndAddHLTcut/1tau1l/log/'
    #  logDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau2os_v1/log/'
    #  logDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v1/log/'
    #  logDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v1/log/'
    #  logDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau2l_v1/log/'
    # logDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v2/log/'
    # logDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v1fixedTauVariables_v40addTauJetEtau/1tau1l_v1/log/'
    logDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/log/'
    getAUCToTGragh( logDir )



