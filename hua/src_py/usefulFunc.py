import os
import subprocess
import sys

import pandas as pd
import ROOT
# from ttttGlobleQuantity import (histoGramPerSample, lumiMap, summedProcessList,
                                # samplesCrossSection)
                                
import ttttGlobleQuantity as tg                                
import setTDRStyle as st


def checkMakeDir( folder ):
    if not os.path.exists( folder ):
        os.mkdir( folder )

def getGenSumDic( inputCsv, era ):
    df = pd.read_csv( inputCsv )
    # genSumDic = pd.Series( df['2016postVFP'].values, index=df['process'] ).to_dict()
    genSumDic = pd.Series( df[era].values, index=df['process'] ).to_dict()
    # print( genSumDic )
    return genSumDic

# def getProcessScale( processName, era ):
#     scale = lumiMap[era]*samplesCrossSection[processName]/getGenSumDic()

def sumbitJobs(  jobsh):
    print('staring to submit jobs')
    command = 'bash {}'.format(  jobsh )
    process = subprocess.run( command, shell=True ) 
    output = process.stdout
    print(output)

    print('jobs submitted')


def runCommand(command):
    print('runing command: ', command)
    # command = 'bash {}.'.format(command)
    process = subprocess.run( command, shell=True ) 
    output = process.stdout
    print(output)
    print('Done running command\n\n')

def getInputDic( inVersion, histVersion, era):
    '''
    for final hists folder structure
    '''
    inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/' + era +'/'
    inputDirDic = {
        'mc': inputDirBase + inVersion + '/mc/' + histVersion + '/',
        'data': inputDirBase + inVersion + '/data/' + histVersion + '/',
    }
    return inputDirDic

def getInputDicNew( inputDirMC ):
    inputDirmc = inputDirMC[:]
    inputDirData = inputDirMC.replace('mc', 'data')
    inputDirDic = {
        'mc': inputDirmc,
        'data': inputDirData,
    }
    return inputDirDic

def getEraFromDir(inputDir):
    era = ''
    if '2016' in inputDir:
        if '2016post' in inputDir or '2016_post' in inputDir:
            era = '2016postVFP'
        elif '2016pre' in inputDir or '2016_post' in inputDir:
            era = '2016preVFP'
        else:
            era = '2016'
    elif '2017' in inputDir:
        era = '2017'
    elif '2018' in inputDir:
        era = '2018'
    elif 'Run2' in inputDir:
        era = 'Run2'
    elif '2022' in inputDir:
        if '2022preEE' in inputDir:
            era = '2022preEE'
        elif '2022postEE' in inputDir:
            era = '2022postEE'
        else:
            era = '2022' 
    return era

def getChannelFromDir( dir ):
    cha = ''
    if '1tau1l' in dir:
        cha = '1tau1l'
    elif '1tau0l' in dir:
        cha = '1tau0l'
    return cha

def isRun3(inputDir):
    isRun3 = False
    if '2022' in inputDir:
        isRun3 = True
    return isRun3

def isRun3Era(era):
    isRun3 = False
    if '2022' in era:
        isRun3 = True
    return isRun3    
    

def getDirDic(inputMC):
    inputDirDic = {
        'mc': inputMC,
        'data': inputMC.replace('mc', 'data')
    }
    return inputDirDic

def getSysList(rootFile, variable):
    histList = []
    sysList = []
    for key in rootFile.GetListOfKeys():
        obj = key.ReadObj()
        histName = obj.GetName()
        if isinstance(obj, ROOT.TH1):
            histList.append(histName)
            if '_up' in histName or '_down' in histName:
                iSys = histName[histName.find(variable)+len(variable)+1:len(histName)]
                sysList.append(iSys)
    # print('all hists in file: ', histList)
    return sysList

def compare2List( list1, list2):
    print('comparing lists now: ')
    for (i, ie) in enumerate(list1):
        list1[i] = list1[i].split('.root')[0]
    diff1 = set(list1) -set(list2)
    diff2 = set(list2) - set(list1)
    print('!!!subprocess missing: ', diff2)
    print('\n')
    print('\n')
    
    

def getSummedHists( inputDir, regionsList, variable='jetsNumber_forYieldCount', ifScale=False, era = '2016postVFP' , ifGetSys=False, isRun3=False):
    if not isRun3:
        histoGramPerSample = tg.histoGramPerSample
    else:
        histoGramPerSample = tg.Run3Samples
    allSubProcess = histoGramPerSample.keys()
    sumProcessHistsDict = {}
    sumProcessHistsDictSys = {}
    mcFileList = os.listdir( inputDir['mc'] )
    dataFileList = os.listdir ( inputDir['data'] )
    #!!!need to be optimized for checking the hists
    compare2List(mcFileList+dataFileList, list(histoGramPerSample.keys()))
    
    for ifile in mcFileList+dataFileList:
        ifileName = ifile.split('.root')[0]
        if ('singleMu' in ifileName) or ('jetHT' in ifileName) or ('JetMet' in ifileName) or ('JetHT' in ifileName):
            isdata = True
        else:
            isdata = False
        if not ifileName in allSubProcess: continue
        iProScale = 1.0
        # if ifScale and (not 'jetHT' in ifileName):
        if ifScale and (not isdata):
            iProScale = getProcessScale( ifileName, era )
        print('ifileName: {}, scale: {}'.format( ifileName , iProScale) )
        if isdata:
            iRootFile = ROOT.TFile( inputDir['data']+ifile, 'READ' )
        else:
            iRootFile = ROOT.TFile( inputDir['mc']+ifile, 'READ' ) 
        print('openning file: ', iRootFile.GetName() )
        
        if ifGetSys: 
            sysList = getSysList(iRootFile, variable)  
            print('systematic in file: ', sysList)
        else:
            sysList=[]
        
        for iRegion in regionsList:
            # if 'SR' in iRegion and isdata: continue
            if (iRegion=='1tau1lSR' or iRegion=='1tau0lSR') and isdata: continue
            # if 'SR' in iRegion and isdata: continue
            if not isRun3:
                # iHistName = iRegion + '_' + ifileName + '_' + variable  #!!!old WH code
                iHistName = ifileName +'_' +iRegion+ '_' + variable
            else:
                iHistName = ifileName +'_' +iRegion+ '_' + variable#!!!new WH code
            
            if iRegion not in sumProcessHistsDict.keys(): 
                sumProcessHistsDict[iRegion]={}
                sumProcessHistsDictSys[iRegion]={}
            print('iHistName: ', iHistName )
            
            if histoGramPerSample[ifileName] not in sumProcessHistsDict[iRegion].keys():
                sumProcessHistsDictSys[iRegion][histoGramPerSample[ifileName]] = {}
                sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]] = iRootFile.Get( iHistName)
                sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].Sumw2()
                sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].SetDirectory(0)
                print('sumProcessHistDic[{}][{}] get hist: {}'.format( iRegion, histoGramPerSample[ifileName], iHistName ))
                if ifScale or not isdata: 
                    sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].Scale(iProScale)
                #get systematic hist
                if ifGetSys:
                    for isys in sysList:
                        sumProcessHistsDictSys[iRegion][histoGramPerSample[ifileName]][isys] = iRootFile.Get( iHistName+'_'+isys)
                        sumProcessHistsDictSys[iRegion][histoGramPerSample[ifileName]][isys].Sumw2()
                        sumProcessHistsDictSys[iRegion][histoGramPerSample[ifileName]][isys].SetDirectory(0)
            else:
                itemp = iRootFile.Get( iHistName)
                if ifScale or not isdata: 
                    itemp.Scale(iProScale)
                sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].Add( itemp)
                print('sumProcessHistDic[{}][{}] add hist: {}'.format( iRegion, histoGramPerSample[ifileName], iHistName ))
                if ifGetSys:
                    for isys in sysList:
                        sumProcessHistsDictSys[iRegion][histoGramPerSample[ifileName]][isys].Add( iRootFile.Get( iHistName+'_'+ isys))
                        
        iRootFile.Close()
        print( '\n')

    return sumProcessHistsDict, sumProcessHistsDictSys


def getProcessScale( processName, era ):
    # genWeight = uf.getGenSumDic( '../objectSelection/genWeightCSV/genSum_2016postVFP.csv' )[processName]
    genWeight = uf.getGenSumDic( '../objectSelection/genWeightCSV/genSum_'+era+'.csv', era )[processName]
    scale = lumiMap[era]*samplesCrossSection[processName]/genWeight
    print( processName, ': ', 'genWeight= ', genWeight, ' lumi=', lumiMap[era], ' cross=', samplesCrossSection[processName],  ' scale= ', scale)
    return scale


def addBGHist(sumProcessIVar,  region, includeQCD=False):
    summedProcessList = list(sumProcessIVar[region].keys())
    sumHist = sumProcessIVar[region][summedProcessList[0]].Clone()
    sumHist.Reset()
    sumHist.Sumw2()
    sumHist.SetName(region)
    for ipro in summedProcessList:
        if not includeQCD:
            # if ipro=='data' or ipro=='qcd' or ipro=='tttt': continue
            if ipro=='jetHT' or ipro=='singleMu' or ipro=='qcd' or ipro=='tttt': continue
        else:
            if ipro=='jetHT' or ipro=='singleMu' or ipro=='tttt': continue
        sumHist.Add( sumProcessIVar[region][ipro])
    return sumHist



def plotEfficiency(h_numeritor, h_dinominator, h_eff, plotName, era = '2016', ifFixMax=True, rightTitle='efficiency'):
    print('start to plot efficiency')
    mySty =  st.setMyStyle()
    mySty.cd()
    
    can = ROOT.TCanvas('efficiency', 'efficiency', 1000, 800)
    ROOT.gStyle.SetOptStat(ROOT.kFALSE)
    ROOT.gStyle.SetOptTitle(0)

    # h_dinominator.SetLineColor(ROOT.kOrange)
    h_dinominator.GetYaxis().SetRangeUser(h_numeritor.GetMinimum()*0.9, h_dinominator.GetMaximum()*1.5)
    h_dinominator.GetYaxis().SetTitle('Events')
    h_dinominator.GetYaxis().SetTitleSize(0.05)
    h_dinominator.GetYaxis().SetLabelSize(0.03)
    h_dinominator.GetYaxis().SetTitleOffset(1.1)
    h_dinominator.GetXaxis().SetTitle(h_dinominator.GetTitle())
    h_dinominator.GetXaxis().SetTitleSize(0.05)
    h_dinominator.SetLineWidth(3)
    h_dinominator.SetLineColorAlpha(ROOT.kOrange+1, 0.8)
    
    h_dinominator.Draw()
    h_numeritor.SetLineColorAlpha(ROOT.kGreen, 0.5)
    h_numeritor.SetLineWidth(3)
    # h_numeritor.SetLineStyle(8)
    h_numeritor.Draw('same')
    can.Update()

    h_efficiency = h_eff.Clone()
    if ifFixMax:
        rightmax = .35
        # rightmax = .2
    else:
        rightmax = 1.7*h_efficiency.GetMaximum()
    scale = ROOT.gPad.GetUymax()/rightmax
    h_efficiency.SetLineColor(ROOT.kRed)
    h_efficiency.SetLineWidth(4)
    # h_efficiency.SetMarkerStyle(3)
    h_efficiency.SetLineStyle(1)
    h_efficiency.Scale(scale) #!!!need to consider this scaling effect on uncertainty
    # h_efficiency.Scale(4000) #!!!need to consider this scaling effect on uncertainty
    h_efficiency.Draw("same")
    
    #print
    # for i in range(1,h_efficiency.GetNbinsX()+1):
    #     print( i, 'bin: ', h_dinominator.GetBinContent(), h_dinominator.GetBinError(), h_numeritor.GetBinContent(), h_numeritor.GetBinContent())
    
    axis = ROOT.TGaxis(ROOT.gPad.GetUxmax(),ROOT.gPad.GetUymin(), ROOT.gPad.GetUxmax(), ROOT.gPad.GetUymax(),0,rightmax,510,"+L")
    # axis.SetRangeUser(0, rightmax*1.4)
    axis.SetLineColor(ROOT.kRed)
    axis.SetLabelColor(ROOT.kRed)
    # axis.SetTitle('fake rate')
    # axis.SetTitle('efficiency')
    axis.SetTitle(rightTitle)
    axis.SetTitleSize(0.05)
    axis.SetTitleColor(ROOT.kRed)
    # axis.SetRangeUser(0, 0.4)
    axis.Draw()


    # legend = ROOT.TLegend(0.4,0.7,0.9,0.9)
    legend = ROOT.TLegend(0.35,0.68,0.9,0.9)
    legend.AddEntry(h_dinominator, "denominator: "+ h_dinominator.GetName())
    legend.AddEntry(h_numeritor, "numeritor: "+ h_numeritor.GetName())
    legend.AddEntry(h_efficiency, h_efficiency.GetName())
    legend.Draw()
    
    # addCMSTextToCan(can, 0.21, 0.33, 0.91, era)     

    can.SaveAs(plotName)


def getSameValues(diction, value):
    subList = []
    for ikey, ivalue in diction.items():
        if ivalue==value:
            subList.append(ikey)
    return subList
            
    
def getSumBG(inputDir, sumBG, regionList, ivar):
    if not sumBG in tg.histoGramPerSample: 
        print(sumBG, ' not exist!!!')
        sys.exit()
    subprocesses = getSameValues(tg.histoGramPerSample, sumBG)
    # for ifile in os.listdir(inputDir):
        
    
def plotEffTEff(h_numeritor, h_dinominator, plotName, era, ifFixMax=True, rightTitle='Efficiency'):
   #plot efficiency with TEfficiency   
    print('start to plot efficiency')
    mySty =  st.setMyStyle()
    mySty.cd()
    
    can = ROOT.TCanvas('efficiency', 'efficiency', 1000, 800)
    ROOT.gStyle.SetOptStat(ROOT.kFALSE)
    ROOT.gStyle.SetOptTitle(0)
    
    # leftmax  = h_dinominator.GetMaximum() *1.5 
    # scale = ROOT.gPad.GetUymax()/rightmax
    
    h_dinominator.GetYaxis().SetRangeUser(h_numeritor.GetMinimum()*0.9, h_dinominator.GetMaximum()*1.5)
    h_dinominator.GetYaxis().SetTitle('Events')
    h_dinominator.GetYaxis().SetTitleSize(0.05)
    h_dinominator.GetYaxis().SetLabelSize(0.03)
    h_dinominator.GetYaxis().SetTitleOffset(1.1)
    h_dinominator.GetXaxis().SetTitle(h_dinominator.GetTitle())
    h_dinominator.GetXaxis().SetTitleSize(0.05)
    h_dinominator.SetLineWidth(3)
    h_dinominator.SetLineColorAlpha(ROOT.kOrange+1, 0.8)
    
    h_dinominator.Draw()
    h_numeritor.SetLineColorAlpha(ROOT.kGreen, 0.5)
    h_numeritor.SetLineWidth(3)
    h_numeritor.Draw('same')
    can.Update()
    
    if ifFixMax:
        rightmax = 1.0
    else:
        rightmax = 1.7*h_efficiency.GetTotalHistogram().GetMaximum()
        
    h_efficiency =  ROOT.TEfficiency(h_numeritor, h_dinominator)
    h_efficiency.SetStatisticOption(ROOT.TEfficiency.kFCP) # Clopper-Pearson #!!!might not be working for weighted histograms, https://root-forum.cern.ch/t/tefficiency-with-weighted-events/18067
    scale = ROOT.gPad.GetUymax()/rightmax
    # h_efficiency.GetTotalHistogram().Scale(scale)
    # h_efficiency.GetTotalHistogram().Scale(5000)
    h_efficiency.Draw('same')

    
    
    axis = ROOT.TGaxis(ROOT.gPad.GetUxmax(),ROOT.gPad.GetUymin(), ROOT.gPad.GetUxmax(), ROOT.gPad.GetUymax(),0,rightmax,510,"+L")
    axis.SetLineColor(ROOT.kRed)
    axis.SetLabelColor(ROOT.kRed)
    axis.SetTitle(rightTitle)
    axis.SetTitleSize(0.05)
    axis.SetTitleColor(ROOT.kRed)
    axis.Draw()


    # legend = ROOT.TLegend(0.4,0.7,0.9,0.9)
    legend = ROOT.TLegend(0.35,0.68,0.9,0.9)
    legend.AddEntry(h_dinominator, "denominator: "+ h_dinominator.GetName())
    legend.AddEntry(h_numeritor, "numeritor: "+ h_numeritor.GetName())
    # legend.AddEntry(h_efficiency, h_efficiency.GetName())
    legend.Draw()
    
    can.SaveAs(plotName+'.png')
    can.SaveAs(plotName+'.pdf')
    print('done plot efficiency \n\n')
    
    
   