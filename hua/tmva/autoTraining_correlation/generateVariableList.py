

import sys
import os
import subprocess
import ROOT
#  from ROOT import *
#  import array
#  import math

import csv
import plotVariablesAndSP


#  def main(  TMVAlog = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v1HT400Cut_v44_fixedSingJetHLTBugAndAddHLTcut/1tau1l_forvariables.log"):
#  def main(  TMVAlog = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau2os/1tau2os__variables.log"):
#  def main(  TMVAlog = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v1/1tau1l__variables.log"):
#  def main(  TMVAlog = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v1/2tau2l__variables.log"):
#  def main(  TMVAlog = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau2l_v1/1tau2l__variables.log"):
def main():
    #  TMVADir =  "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v1/"
    
    #the first line identifies each piece of datain other words, the name of a data column
    
    channel = 1;#1 for 1tau1l
    #  channel = 2;#2 for 1tau2os
    #  channel =3 # 2tau1l
    #  channel =4# 1tau2l
    version = 1
    #  version = 2 #corrected correlation removel
    #  outputBase = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/'
    outputBase = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/'

    channelName = getNameForChannelVersion( channel, version ) 
    vListDir, outputDir = checkAndMakeDir( channelName, outputBase )

    generateAllVariablesLog( outputDir, channelName, channel )#just to get the SP of all variables
    
    #  TMVAlog, TMVAroot = getTMVAlog( outputDir, channel )
    #  vListList = generateListList( TMVAlog, TMVAroot )
    #  writeListListToFile( vListList, vListDir)

    #plot variable list
    #  SPDic = plotVariablesAndSP.getInitListAndSP(TMVAlog )
    #  plotVariablesAndSP.plotListListSP( vListList, outputDir, SPDic , channel )

def generateAllVariablesLog( outputDir , channelName, channel ):
    tmvaTraining = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/TMVAClassification_variableFileInput.C'
    trainingCommand = 'root -b -q \'{}( \"\", \"{}\", \"\", {}, true )\''.format( tmvaTraining, outputDir, channel )
    print( 'training for all variables starts....................................... ' )
    print( 'command: ', trainingCommand )
    process = subprocess.run( 'root -b -q {}'.format(tmvaTraining), shell=True, capture_output=True, text=True )
    output = process.stdout.strip()
    print( output )

    with open( outputDir+'{}__variables.log'.format(channelName), 'w') as logFile:
        logFile.writelines( output )


def getTMVAlog( outputDir, channel):
    if channel == 1:
        TMVAlog = outputDir + '1tau1l__variables.log'
        TMVAroot = outputDir + '1tau1l__variables.root'
    if channel == 2:
        TMVAlog = outputDir + '1tau2os__variables.log'
        TMVAroot = outputDir + '1tau2os__variables.root'
    if channel == 3:
        TMVAlog = outputDir + '2tau1l__variables.log'
        TMVAroot = outputDir + '2tau1l__variables.root'
    if channel == 4:
        TMVAlog = outputDir + '1tau2l__variables.log'
        TMVAroot = outputDir + '1tau2l__variables.root'
    return TMVAlog, TMVAroot

def generateListList( TMVAlog, TMVAroot ):
    initialVariableList = getInitList( TMVAlog )

    removedPhiEtaList = removephieta( initialVariableList )

    #  print( 'initialVariableList: ', len(initialVariableList), initialVariableList)
    leading50List = leadingNList( removedPhiEtaList, 50 )
    #  print( '50 leadingList:\n', len(leading50List),  str(leading50List),'\n')
    removeBjetTL_list = removeBjetTL( leading50List )
    print( 'removeBjets list: ', len(removeBjetTL_list), removeBjetTL_list )
    print( '\n')

    vListList = createNextVariableList_correlation( removeBjetTL_list, TMVAroot  )

    vListList.append( leading50List )
    #  vListList.append( removeBjetTL_list )
    #  print( 'vListList: \n', len(vListList), vListList )

    return vListList

def removephieta( initialList ):
    #  print('initialList length: ', len(initialList) )
    removedList = []
    for ivariable in initialList:
        #  if ('phi' in ivariable) or ('eta' in ivariable):
        if not(ivariable.find( 'phi') != -1 or ivariable.find( 'eta')!=-1 ):
            #  print( ivariable)
            removedList.append( ivariable )
    print( 'list after remove phieta: ', len( removedList), removedList )
    return removedList

    return initialList

#  def checkAndMakeDir( channel, outputDir, version ):
def checkAndMakeDir( channelName, outputDir ):
    outputDir = makeBaseDir( channelName, outputDir )
    vListDir = outputDir + 'variableList/'
    print( 'outputDir: ', outputDir)
    if not os.path.exists( vListDir):
        os.mkdir( vListDir )
    return vListDir, outputDir

def makeBaseDir( channelName, outputDir ):
    if not os.path.exists( outputDir ):
        os.mkdir( outputDir )

    #  if channel == 1:
        #  outputDir = outputDir + '1tau1l_v' + str(version) +'/'
    #  if channel == 2:
        #  outputDir = outputDir + '1tau2os_v' + str(version) + '/'
    #  if channel ==3:
        #  outputDir = outputDir + '2tau1l_v' + str(version) + '/'
    #  if channel ==4:
        #  outputDir = outputDir + '1tau2l_v' + str(version) + '/'
    outputDir = outputDir + channelName + '/'

    if not os.path.exists( outputDir ):
        os.mkdir( outputDir )
    return outputDir

def getNameForChannelVersion( channel, version ):
    channelName = ''
    if channel == 1:
        channelName = '1tau1l_v' + str(version) 
    if channel == 2:
        channelName = '1tau2os_v' + str(version) 
    if channel == 3:
        channelName = '2tau1l_v' + str(version) 
    if channel == 4:
        channelName = '1tau2l_v' + str(version) 
    return channelName



def getInitList( TMVAlog ):
    initialVariableList = []
    with open(TMVAlog) as csv_file, open("variableList.csv", "w+") as to_file2:
        csv_reader = csv.reader(csv_file, delimiter=':')
        writer2 = csv.writer(to_file2, delimiter=":")
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
                        #  print( 'variable1', variable1 )
                        #  writer2.writerow([irow[2]])
                        #  initialVariableList.append(irow[2])
                        writer2.writerow( variable1)
                        initialVariableList.append(variable1)

                if not irow[0] == 'Factory                  ':
                    SPline += 1
                    #  print(irow[2])
                    #  data.append(irow[2])
            linecount +=1
    return initialVariableList



def writeListListToFile( listList, fileDir ):
    for iList in listList:
        writeListToFile( iList, fileDir )


def writeListToFile( iList, fileDir ):
    iFileName = fileDir + 'varibleList_'+str(len(iList)) + '.csv'
    print( 'writing file: ', iFileName )
    output = open(iFileName,'wt')
    for ele in iList:
        output.write(ele+'\n')
    output.close()



def leadingNList( variableList, N):
    #  return variableList[0:N-1]
    return variableList[0:N]
    



def removeBjetTL( variableList) :
    removedList = []
    for variable in variableList:
        #  print( 'variable in list: ', variable)
        if not(variable.find( 'bjetsL') != -1 or variable.find( 'bjetsT')!=-1 ):
        #  if not(variable.find( 'bjetsL') ):
            removedList.append( variable )
        #  else:
            #  print( variable )
        #  if variable.find('bjetsL') != -1:
            #  print( variable)
    return removedList



def createNextVariableList_correlation( vlist, TMVAroot):
    #only stores variable in vlist
    #  inputFile = ROOT.TFile("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v1HT400Cut_v44_fixedSingJetHLTBugAndAddHLTcut/1tau1l_forvariables_variables.root")
    inputFile = ROOT.TFile( TMVAroot )
    inputFile.Print()
    h2 = inputFile.Get("dataset/CorrelationMatrixS"); #TH2F
    #  h2.Print()

    #getting the correlaiton list out of root TH2F
    #  print( h2.GetXaxis().GetBinLabel(1))
    binNum = h2.GetNbinsX()
    print( 'variable number in TH2F: ', binNum)
    ibinX = 1
    #  ibinY = 1
    correlation_list = [] #list of sets
    while ibinX<binNum+1:
        #  print(ibinX)
        ibinY = 1
        while ibinY<ibinX:
            #  print(ibinY)
            xBinLabel = h2.GetXaxis().GetBinLabel(ibinX)
            yBinLabel = h2.GetYaxis().GetBinLabel(ibinY)
            if xBinLabel in vlist and yBinLabel in vlist:
                icorrelation = abs( h2.GetBinContent( ibinX, ibinY) )
                #  correlation_list.append( (xBinLabel, yBinLabel, icorrelation) )
                correlation_list.append( [xBinLabel, yBinLabel, icorrelation] )
            ibinY+=1
        ibinX+=1

    #  print( 'correlaition list: ', correlation_list)
    correlation_list.sort( key=takeThird, reverse = True )
    print('\n')
    print( 'list after sorting: ', correlation_list)
    print('\n')

    #for simplisity, not taking multiple same correlation into account for now
    tempList = vlist
    listLenth = len(vlist)
    variableListList = []
    for correlationPair in correlation_list:
        if len(tempList)==listLenth:
            #print( 'tempList: ', len(tempList), tempList)
            #  variableListList.append(tempList)
            variableListList.append(tempList[:])# The notation list[:] creates a copy of the list.
            listLenth = listLenth-1
        firstVariable = correlationPair[0]
        secondVariable = correlationPair[1]
        #  print( 'tempList: ', len(tempList), tempList)
        if firstVariable in tempList and secondVariable in tempList:
            #  print( firstVariable,' index = ', vlist.index( firstVariable), secondVariable,' index = ', vlist.index( secondVariable ))
            if vlist.index( firstVariable) > vlist.index( secondVariable ):
                tempList.remove( firstVariable)
                #  print( 'removed: ', secondVariable )
            else:
                tempList.remove( secondVariable)
                #  print( 'removed: ', firstVariable )
        #  elif :
    #  print( 'variableListList: ', len(variableListList), variableListList)
    #  print( 'variableListList: ', variableListList[0])
    return variableListList







def takeThird( elem ):
    return elem[2]








if __name__ == '__main__':
        main()
