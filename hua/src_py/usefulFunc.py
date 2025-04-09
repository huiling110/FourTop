import os
import subprocess
import pandas as pd
import ROOT
                                
import ttttGlobleQuantity as gq                                
import setTDRStyle as st

def getSubProScale(subPro, era):
    lumi = gq.lumiMap[era]
    cross = gq.crossSectionMap[subPro]
    genSum = gq.genSumDic[subPro]
    # print(subPro, ': ', 'genSum= ', genSum, ' lumi=', lumi, ' cross=', cross)
    return lumi*cross/genSum
    

def checkMakeDir( folder,ifDelete=False) :
    if not os.path.exists( folder ):
        os.mkdir( folder )
    else:
        if ifDelete:
            os.system('rm -rf '+folder + '/*')
            # os.mkdir( folder )

def getGenSumDic( inputCsv, era ):
    df = pd.read_csv( inputCsv )
    # genSumDic = pd.Series( df['2016postVFP'].values, index=df['process'] ).to_dict()
    genSumDic = pd.Series( df[era].values, index=df['process'] ).to_dict()
    # print( genSumDic )
    return genSumDic


def sumbitJobs(  jobsh):
    print('staring to submit jobs')
    command = 'bash {}'.format(  jobsh )
    process = subprocess.run( command, shell=True ) 
    output = process.stdout
    print(output)

    print('jobs submitted')


def runCommand(command, ifDryRun=False):
    print('runing command: ', command)
    if not ifDryRun:
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
    
    
def getProcessScale( processName, era ):
    # genWeight = uf.getGenSumDic( '../objectSelection/genWeightCSV/genSum_2016postVFP.csv' )[processName]
    genWeight = uf.getGenSumDic( '../objectSelection/genWeightCSV/genSum_'+era+'.csv', era )[processName]
    scale = lumiMap[era]*samplesCrossSection[processName]/genWeight
    print( processName, ': ', 'genWeight= ', genWeight, ' lumi=', lumiMap[era], ' cross=', samplesCrossSection[processName],  ' scale= ', scale)
    return scale



def getSameValues(diction, value):
    subList = []
    for ikey, ivalue in diction.items():
        if ivalue==value:
            subList.append(ikey)
    return subList
            
def getHistFromFile(fileName, histNames, ifPrint=False):
    file = ROOT.TFile.Open(fileName)

    if not file or file.IsZombie():
        print("Error: Unable to open the file.")
        return []

    histograms = []
    # Loop through the list of histogram names
    for name in histNames:
        # Get the histogram from the file
        histogram = file.Get(name)
        if not histogram:
            raise ValueError(f"Error: Unable to find the histogram '{name}' in the file.")
        if ifPrint:
            histogram.Print()
        # Clone the histogram to avoid potential issues when the file is closed
        histogram1 = histogram.Clone()
        # histogram1.Print()
        histogram1.SetDirectory(0)
        histograms.append(histogram1)
    # Close the file (optional, depending on your use case)
    file.Close()

    return histograms
    
# def getHistFromFileDic(fileName, regionList, varList, subPro, sumProSys, era):
def getHistFromFileDic(fileName, regionList, varList, subPro, sumProSys, era, sumPro=''):
    file = ROOT.TFile.Open(fileName)
    if not file or file.IsZombie():
        print("Error: Unable to open the file.")
        return []
    subProHist = {} 
    subProHistSys = {}
    # histNames =  getHistName(regionList, varList, subPro)
    for ivar in varList:
        subProHist[ivar] = {}
        subProHistSys[ivar] = {}
        for ire in regionList:
            histName = subPro + '_' + ire + '_' + ivar 
            subProHist[ivar][ire] = {}
            subProHist[ivar][ire][subPro] = {}
            subProHist[ivar][ire][subPro] = getHistFromFile(fileName, [histName])[0]
            subProHistSys[ivar][ire] = {}
            subProHistSys[ivar][ire][subPro] = {}
            # subProHistSys[ivar][ire][subPro] = getSysHistNames(sumProSys, subPro, ire, ivar, era, fileName)
            subProHistSys[ivar][ire][subPro] = getSysHistNames(sumProSys, subPro, ire, ivar, era, fileName, sumPro)
            
    return subProHist, subProHistSys
             
# def getSysHistNames(sumProSys, subPro, region, var, era, fileName):
def getSysHistNames(sumProSys, subPro, region, var, era, fileName, sumPro=''):
    # sysHistNames = []
    sysDic = {}
    # sumPro = gq.histoGramPerSample[subPro]
    if sumPro in sumProSys.keys():
        for isys in sumProSys[sumPro]:
            # isysUp = f"{subPro}_{region}_{isys}_{era}Up_{var}"
            # isysDown = f"{subPro}_{region}_{isys}_{era}Down_{var}"
            isysUp = f"{subPro}_{region}_{isys}Up_{var}"
            isysDown = f"{subPro}_{region}_{isys}Down_{var}"
            sysDic[isys+'_up'], sysDic[isys+'_down']= getHistFromFile(fileName, [isysUp, isysDown])
    return sysDic        
    
   
def getHistName(regionList, varList, isub):
    histNames = []
    for iRe in regionList:
        for ivar in varList:
            iHist = isub + '_' + iRe + '_' + ivar
            histNames.append(iHist)
    return histNames

def print_dict_structure(dictionary, indent=0):
    # print(name, )
    for key, value in dictionary.items():
        print("\t" * indent + str(key))
        if isinstance(value, dict):
            print_dict_structure(value, indent + 1)
    # print('\n')

def getSumHist(inputDirDic, regionList, sumProList, sumProSys,varList, era='2018', isRun3=False, ifDebug=False, ifMCFTau=False):
#!new and better
    #return sumProHists[var][region][sumPro]
    #return sumProHistSys[var][region][sumPro]['sys'] 
    #!ifMCFTau=True: 
    print('start to get hists and add them from root files')
    allDic = gq.histoGramPerSample.copy()
    if isRun3: 
        allDic = gq.Run3Samples
    if ifMCFTau:
        modifyDicForMCFTau(allDic, sumProList)    
    
    allSubPro = list(allDic.keys())
    print('allSubPro: ', allSubPro)
    toGetSubHist = {} 
    toGetSubHistSys = {}
    for isub in allSubPro:
        isdata = isData(isub)
        if not allDic[isub] in sumProList: continue # not getting
        if checkIfOtherYear(isub, era, isdata): continue
        if ifDebug:
            print('getting: ', isub)
        inputDir = inputDirDic['data'] if isdata else inputDirDic['mc']
        # if isdata:
        #     rootFile = inputDirDic['data'] + isub + '.root'
        # else:
        #     rootFile = inputDirDic['mc'] + isub +'.root'
        
        # rootFile = inputDir + isub + '.root' 
        # if ifMCFTau and 'MCFT' in isub:
           #remove '_MCFT' or '_NotMCFT' from isub without chaning the original isub
        if isub.endswith('_MCFT'):
            iroot = isub.removesuffix('_MCFT')
        elif isub.endswith('_NotMCFT'):
            iroot = isub.removesuffix('_NotMCFT')
        else:
            iroot = isub
        rootFile = inputDir + iroot + '.root'
        
        print('opening file:', rootFile)
        # isubToGet = isub if not ifMCFTau else isub+ '_MCFT'
        # isubProHist, isubProHistSys = getHistFromFileDic(rootFile, regionList, varList, isub, sumProSys, era) #isubProHist[var][region][subPro]
        isubProHist, isubProHistSys = getHistFromFileDic(rootFile, regionList, varList, isub, sumProSys, era, allDic[isub]) #isubProHist[var][region][subPro]
        print_dict_structure(isubProHist)
        toGetSubHist = merge_dicts(toGetSubHist, isubProHist)
        toGetSubHistSys = merge_dicts(toGetSubHistSys, isubProHistSys)
    print_dict_structure(toGetSubHist)
    print('\n')
    
    sumProHists =  sumProDic(toGetSubHist, allDic)
    sumProHistsSys = sumProDic(toGetSubHistSys, allDic)
    print_dict_structure(sumProHists)
    print_dict_structure(sumProHistsSys)
    return sumProHists, sumProHistsSys


def modifyDicForMCFTau(allDic, sumList):
    updatedDic = {}
    for isub, sumPro in allDic.items():
        if isData(isub): continue
        if sumPro=='fakeTau' or sumPro == 'fakeLepton': continue
        if sumPro == 'tttt': continue
        if not sumPro in sumList: continue
        #update isub in allDic with postfix ['_MCFT']
        updatedDic[isub + '_NotMCFT'] = sumPro
        updatedDic[isub + '_MCFT'] = 'fakeTauMC'
        
    for isub in updatedDic:
        original_key = isub[:-len('_MCFT')]
        if original_key in allDic:
            del allDic[original_key]

    
    print('proDic updated with MCFTau')
    print('allDic: ', allDic)
        
        

     
   
def checkIfOtherYear(isub, era, isData):
    if not isData:
        return False
    else:
        if 'leptonSum' in isub:
            return False if era in isub else True
        else:
            for isubEra in gq.dataDict[era]:
                parts = isub.split('_')
                iera = '_'.join(parts[1:])
                if iera == isubEra:
                    return False 
            return True
    
def sumProDic(subProHists, sumProDic):
    #subProDicSys[var][region][subPro]['sys']
    #: subProDic[var][region][subPro]
    sumProHists = {}
    for ivar, reDic in subProHists.items():
        sumProHists[ivar] = {}
        for ire, subProDic in reDic.items():
            sumProHists[ivar][ire] = {}
            #!careful here
            # for isub, hist in subProDic.items():
            # if isinstance(subProDic, dict):
            for isub, systs in subProDic.items():
                if isinstance(systs, dict):
                    if sumProDic[isub] not in sumProHists[ivar][ire].keys():
                        sumProHists[ivar][ire][sumProDic[isub]] = {}
                        for isys, hist in systs.items():
                            sumProHists[ivar][ire][sumProDic[isub]][isys] = hist.Clone()
                    else:
                        for isys, hist in systs.items():
                            sumProHists[ivar][ire][sumProDic[isub]][isys].Add(hist)
                else:
                    if sumProDic[isub] not in sumProHists[ivar][ire].keys():
                        sumProHists[ivar][ire][sumProDic[isub]] = systs.Clone()
                    else:
                        sumProHists[ivar][ire][sumProDic[isub]].Add(systs)
                            
    return sumProHists
                

def merge_dicts(dict1, dict2):
    #to stud
    merged_dict = {}
    for key in dict1.keys() | dict2.keys():
        if key in dict1 and key in dict2:
            if isinstance(dict1[key], dict) and isinstance(dict2[key], dict):
                merged_dict[key] = merge_dicts(dict1[key], dict2[key])
            else:
                merged_dict[key] = [dict1[key], dict2[key]]
        elif key in dict1:
            merged_dict[key] = dict1[key]
        else:
            merged_dict[key] = dict2[key]
    return merged_dict

def isData(subPro):
    isdata = False
    if ('jetHT' in subPro) or ('singleMu' in subPro) or ('BTagCSV' in subPro)  or ('singleMu' in subPro) or ('doubleMu' in subPro) or ('MuonEG' in subPro) or ('eGamma' in subPro) or ('singleE' in subPro) or ('leptonSum' in subPro) or ('doubleEG' in subPro):
        isdata = True
    if('JetHT' in subPro) or ('Muon' in subPro) or ('JetMET' in subPro):
        isdata = True
    return isdata

def getYmax(histograms):
    max_y = -1.0
    for hist in histograms:
        if hist:
            current_max_y = hist.GetMaximum()
            if current_max_y > max_y:
                max_y = current_max_y

    return max_y    

def drop_last_one(input_string):
    # Find the last occurrence of '1' in the string
    last_one_index = input_string.rfind('1')
    
    # Check if '1' was found in the string
    if last_one_index != -1:
        # If '1' was found, create a new string by removing the last occurrence of '1'
        new_string = input_string[:last_one_index] + input_string[last_one_index+1:]
        return new_string
    else:
        # If '1' was not found, return the original string
        return input_string
    
def remove_last_char_if_1(s):
    # Check if the last character of the string is '1'
    if s.endswith('1'):
        # Remove the last character
        return s[:-1]
    # Return the original string if the last character is not '1'
    return s
    
    
def checkIfInputDic(entry, isRun3):
    ifInDic = False
    # entryName = remove_last_char_if_1(entry)#! wrongly remove 2016B_v1
    entryName = entry
    # print('entryName=', entryName)
    if not isRun3:
        if  entryName in gq.histoGramPerSample.keys(): 
            ifInDic = True
    else:
        if  entryName in gq.Run3Samples.keys(): 
            ifInDic = True
    return ifInDic



def isBG(sumPro, ifVLL=False):
    #protype 1: signal; 2: background; 3: data
    proType = 0
    if 'jetHT' in sumPro or 'singleMu' in sumPro:
        proType = 3
    elif 'tttt' in sumPro:
        proType = 1 if not ifVLL else 2
    elif 'VLL' in sumPro:
        proType = 1
    else: 
        proType = 2
        
    return proType
        
        
def getAllSubPro(era, sumPro, isData=True, ifttXDecorrelate=False):
    all = gq.histoGramPerSample.copy()
    if ifttXDecorrelate:
        all.update(gq.ttX_newMap)
    allSubs = []
    if isData:
        for isub, isum in all.items():
            if not isum in sumPro: continue
           #get the substring after first '_'
            subEra = isub.split('_', 1)[1]
            if subEra in gq.dataDict[era] and isum in sumPro:
                allSubs.append(isub) 
        return allSubs
    else:
        return [ isub for isub, isum in all.items() if isum in sumPro]
   
def getSubProDic(era, sumPro) :
    all = gq.histoGramPerSample
    allSubs = {}
    for isub, isum in all.items():
        if not isum in sumPro: continue
        isdata = isData(isub)
        if isdata:
            subEra = isub.split('_', 1)[1]
            if subEra in gq.dataDict[era] :
                if isum not in allSubs.keys():
                    allSubs[isum] = []
                allSubs[isum].append(isub)
        else:
            if isum not in allSubs.keys():
                allSubs[isum] = []
            allSubs[isum].append(isub)
    return allSubs
  
############################################################################################################
#dictionary manipulation
 
    
    
############################################################################################################
#!functions to plot histograms
def plotOverlay(histList, legenList, era, yTitle, plotName, drawOp='', legendPos=[0.65, 0.8, 0.9,0.93], yRange=[]):
    print('start to plot overlay plot')
    mySty =  st.setMyStyle()
    mySty.cd()
    can = ROOT.TCanvas('overlay', 'overlay', 1000, 800)
    
    legend = st.getMyLegend(legendPos[0], legendPos[1], legendPos[2], legendPos[3])
    
    yMax = getYmax(histList)
    #plot style
    LineColorDic={
        0: [ROOT.TColor.GetColor("#f03b20"), 8], #rea
        1: [ROOT.TColor.GetColor("#fd8d3c"), 41], #orange
        # 2: [ROOT.TColor.GetColor("#2ca25f"), 101],
        2: [ROOT.TColor.GetColor("#2ca25f"), 1], #green
        #2ca25f green
        #d01c8b purple
        ##fdae61 fc9272" orange
    }

    for i, histogram in enumerate(histList):
        if i == 0:
            histogram.Draw(drawOp)  # Draw the first histogram without any options
        else:
            histogram.Draw('P same')  # Draw subsequent histograms with "same" option to overlay
        # if not 'singleMu' in histogram.GetName(): # keep data black
        #     histogram.SetLineColor(LineColorDic[i][0])
        #     histogram.SetMarkerColor(LineColorDic[i][0])
        # else:
        #     histogram.SetLineColor(ROOT.kBlack)
        #     histogram.SetMarkerColor(ROOT.kBlack)
        histogram.SetLineColor(LineColorDic[i][0])
        histogram.SetMarkerColor(LineColorDic[i][0])
            
        # histogram.SetLineWidth(4)  # Set line width for each histogram
        # histogram.SetMarkerSize(1.0)
        histogram.SetLineWidth(3)  # Set line width for each histogram
        histogram.SetMarkerSize(1.5)
        # histogram.SetMarkerStyle(45)
        histogram.SetMarkerStyle(LineColorDic[i][1])
        histogram.GetXaxis().SetTitle(histogram.GetTitle())  # Set X-axis title (modify as needed)
        histogram.GetYaxis().SetTitle(yTitle)  # Set Y-axis title (modify as needed)
        histogram.GetXaxis().SetTitleSize(0.05)
        histogram.GetYaxis().SetTitleSize(0.06)
        if len(yRange)>1:
            histList[i].GetYaxis().SetRangeUser(yRange[0], yRange[1])
        else:
            histList[i].GetYaxis().SetRangeUser(0, yMax*1.3)

        legend.AddEntry(histogram, legenList[i], "lep")  # Add an entry to the legend
        legend.Draw() 
        
    # st.addCMSTextToCan(can, 0.225, 0.4, 0.9, 0.94, era)
    st.addCMSTextToPad(can, era)
        
    can.SaveAs(plotName+'.png')
    can.SaveAs(plotName+'.pdf')
    print('Done overlay plotting\n\n')
    
    
def getEff(h_de, h_nu):    
    eff = ROOT.TGraphAsymmErrors()
    eff.Divide(h_nu, h_de, "cp") #cp : Clopper-Pearson interval; #https://root.cern.ch/doc/master/classTGraphAsymmErrors.html#ac9a2403d1297546c603f5cf1511a5ca5
    # eff.Draw("AP")
    eff.SetTitle(h_de.GetTitle())
    eff.SetName(h_de.GetName())
    return eff
   
def handle_negative_bins(hist):
    """Set negative bin contents to zero and log a warning."""
    for i in range(1, hist.GetNbinsX() + 1):  # Start from 1 to skip underflow bin
        if hist.GetBinContent(i) < 0:
            print(f"Warning: Negative bin content at bin {i}. Setting to zero.")
            hist.SetBinContent(i, 0)
   
    
def plotEffTEff(h_nu, h_de, plotName, era, legendName, yRange=[0, 1.2], rightTitle='Efficiency'):
    '''
    to do: add the plotting of denominator and numerator too
    '''
   #plot efficiency with TEfficiency, might not work with MC with event weights ;https://root-forum.cern.ch/t/tefficiency-with-weighted-events/18067
    print('start to plot efficiency')
    mySty =  st.setMyStyle()
    mySty.cd()
    
    can = ROOT.TCanvas('efficiency', 'efficiency', 1000, 800)
    ROOT.gStyle.SetOptStat(ROOT.kFALSE)
    ROOT.gStyle.SetOptTitle(0)
    
    handle_negative_bins(h_nu)
    handle_negative_bins(h_de)
    eff = ROOT.TGraphAsymmErrors()
    eff.Divide(h_nu, h_de, "cp") #cp : Clopper-Pearson interval; #https://root.cern.ch/doc/master/classTGraphAsymmErrors.html#ac9a2403d1297546c603f5cf1511a5ca5
    eff.Draw("AP")
    eff.SetTitle(h_de.GetTitle())
    eff.SetName(h_de.GetName())
    
    # eff.GetYaxis().SetRangeUser(0, 1.2)
    eff.GetYaxis().SetRangeUser(yRange[0], yRange[1])
    eff.GetYaxis().SetTitle(rightTitle)
    eff.GetXaxis().SetTitle(h_de.GetTitle())
    
    eff.SetMarkerSize(0.8)
    eff.SetMarkerColor(ROOT.kRed)
    eff.SetLineWidth(3)
    eff.SetLineColor(ROOT.kRed)
   
    # #draw the denominator and numerator hists 
    #  # Create a transparent pad for the second histogram
    # pad = ROOT.TPad("pad", "pad", 0, 0, 1, 1)
    # pad.SetFillStyle(4000)  # will be transparent
    # pad.SetFillColor(0)
    # pad.Draw()
    # pad.cd()

    # # Draw the second histogram using the right Y axis
    # h_de.SetLineColor(ROOT.kRed+1)
    # h_de.Draw("same")

    # # Create a new Y axis for the second histogram
    # # The range should be set according to h_de's scale
    # ymax = h_de.GetMaximum()
    # ymin = h_de.GetMinimum()
    # axis = ROOT.TGaxis(ROOT.gPad.GetUxmax(), ROOT.gPad.GetUymin(), ROOT.gPad.GetUxmax(), ROOT.gPad.GetUymax(),  ymin, ymax, 510, "+L")
    # axis.SetLineColor(h_de.GetLineColor())
    # axis.SetLabelColor(h_de.GetLineColor())
    # axis.SetTitle("Right Axis Title")
    # axis.Draw()
    # # Go back to the main pad and draw
    # can.cd()
    # can.Draw()
    # can.Update()

    legend = st.getMyLegend(0.6,0.25,0.9,0.4)
    legend.AddEntry(eff, 'tttt', 'lep')
    legend.SetTextSize(0.06)
    legend.Draw()
    
    st.addCMSTextToPad(can, era) 
    
    can.SaveAs(plotName+'.png')
    can.SaveAs(plotName+'.pdf')
    print('done plot efficiency \n\n')
    
    return eff
    
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
    

  
############################################################################################################
#!functions to manipulate histograms
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
            if ipro=='jetHT' or ipro=='singleMu' or ipro=='tttt' or ipro=='fakeLepton': continue
        sumHist.Add( sumProcessIVar[region][ipro])
    return sumHist

def addDataHist(h1, h2):
    #!The uncertainty of data hists should not be calculated with quadronic sum
    if h1.GetNbinsX() != h2.GetNbinsX():
        raise ValueError("Histograms must have the same number of bins")

    # Create a new histogram to store the result
    # h_result = h1.Clone("h_result")
    # h_result = h1.Clone()
    # Add bin contents without recalculating errors
    for i in range(1, h1.GetNbinsX() + 1):
        bin_content = h1.GetBinContent(i) + h2.GetBinContent(i)
        # bin_error = (h1.GetBinError(i)**2 + h2.GetBinError(i)**2)**0.5
        bin_error = (bin_content)**0.5
        # h_result.SetBinContent(i, bin_content)
        # h_result.SetBinError(i, bin_error)
        h1.SetBinContent(i, bin_content)
        h1.SetBinError(i, bin_error)

    # return h_result 
    
    
    
# def getInputDirUpDown(inVersion, outVersion, i, inputDirBase):
#     # inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/'
#     inputVersionUp = f'{inputDirBase}{outVersion}_JESup_{i}_{inVersion}/'
#     inputVersionDown = f'{inputDirBase}{outVersion}_JESDown_{i}_{inVersion}/'
#     return inputVersionUp, inputVersionDown