#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : plotVariablesAndSP.py
# Author            : Huiling Hua <huahl@ihep.ac.cn>
# Date              : 03.10.2021
# Last Modified Date: 03.10.2021
# Last Modified By  : Huiling Hua <huahl@ihep.ac.cn>

import os
import ROOT
import csv

import generateVariableList as gV


def main():
    #  TMVAlog = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau2os/1tau2os__variables.log'
    #  TMVAlog = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v1/1tau1l__variables.log'
    #  TMVAlog = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau2l_v1/1tau2l__variables.log'
    # TMVAlog = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v1/2tau2l__variables.log'
    TMVAlog = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v1_fromV8/1tau1l_variables.log'
    TMVAroot = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v1_fromV8/1tau1l_variables.root'
    SPDic = getInitListAndSP(TMVAlog )

    vListList = gV.generateListList( TMVAlog, TMVAroot )

    channel = 1;#1 for 1tau1l
    #  channel = 2#2 for 1tau2os
    # channel = 3 # 2tau1l
    #  channel = 4 #1tau2l
    version = 1
    outputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v1_fromV8/'
    outputDir = gV.makeBaseDir( channel, outputDir, version )

    plotListListSP( vListList, outputDir, SPDic , channel )

def plotListListSP( vListList, outputDir, SPDic,  channel ):
    for iList in vListList:
        #  if len(iList) == 50:
        plotListSP( iList, SPDic, channel, outputDir )

def plotListSP( ilist, SPDic , channel, outputDir ):

    c1 = ROOT.TCanvas( 'c1', 'c1', 330, 800 )

    pt = ROOT.TPaveText(.05,.99,.95,.05,);# the position relative to cavas, first is the left down point
    if channel == 1:
        t1 = pt.AddText( "1tau1l")
        t1.SetTextSize( 0.06)
    if channel == 2:
        t2 = pt.AddText( "1tau2os")
        t2.SetTextSize( 0.06)
    if channel == 3:
        t2 = pt.AddText( "2tau1l")
        t2.SetTextSize( 0.06)
    if channel == 4:
        t2 = pt.AddText( "1tau2l")
        t2.SetTextSize( 0.06)
    
    ivariable = 1
    for i in ilist:
        SP = str( SPDic[i])
        spaces = (34-len(SP)-len(i))*' '
        irow = str(ivariable) + ': '+ i + spaces + SP
        print( irow )
        t0 = pt.AddText( irow )
        t0.SetTextAlign(11)
        t0.SetTextSize( 0.05)
        ivariable= ivariable+1


    pt.Draw()
    if not os.path.exists( outputDir + 'results/' ):
        os.mkdir(  outputDir + 'results/')
    c1.SaveAs( outputDir + 'results/' + str( len(ilist) ) + 'SP.png')



def getInitListAndSP( TMVAlog ):
    #  initialVariableList = []
    SPDic = {}
    #  with open(TMVAlog) as csv_file, open("variableList.csv", "w+") as to_file2:
    with open(TMVAlog) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=':')
        linecount = 0
        SPline = 0
        variable1 = ''
    
        for irow in csv_reader: 
            #Each row returned by the reader is a list of String elements containing the data found by removing the delimiters.
            #get the SP part
            if len(irow)>0:
                if irow[0] == "IdTransformation         ":
                    #  print(irow[1])
                    SPline = linecount+2
            if (linecount == SPline and not(linecount == 0) ):
                #  print(irow)
                if len(irow)>3:
                    #  if not(irow[2] == ' -----------------------------------------------------') or not(irow[1]=='Factory                  '):
                    if irow[2] != ' -----------------------------------------------------' and irow[1]!='Factory                  ' and irow[2]!=' Variable                     ':
                        #  print(irow)
                        variable1 = irow[2].replace( " ", "")
                        SP = irow[3].replace( " ", "")
                        SP = float(SP)
                        print( "SP : ", SP )
                        #  print( 'variable1', variable1 )
                        #  initialVariableList.append(variable1)
                        SPDic[variable1] = SP

                if not irow[0] == 'Factory                  ':
                    SPline += 1
                    #  print(irow[2])
                    #  data.append(irow[2])
            linecount +=1
    print( SPDic )
    return SPDic




if __name__ == '__main__':
    main()
