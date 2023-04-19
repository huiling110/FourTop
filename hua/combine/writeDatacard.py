import os
import subprocess
import sys

import pandas as pd
import ROOT
import usefulFunc as uf
from ttttGlobleQuantity import samples, summedProcessList


def main():
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_v41addVertexSelection/mc/variableHists_v1HT30bins1tau0l/1tau0l_templatesForCombine/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4baseline_v42fixedChargeType/mc/variableHists_v0forVariables1tau0l/1tau0l_templatesForCombine/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baseline_v42fixedChargeType/mc/variableHists_v0forVariables1tau0l/1tau0l_templatesForCombine/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_v42fixedChargeType/mc/variableHists_v0forVariables1tau0l/1tau0l_templatesForCombine/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v6Cut1tau1lVariableFixed_v42fixedChargeType/1tau1l_v0/AppResults_2016_30bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v8Cut1tau1l_v42fixedChargeType/1tau1l_v0/AppResults_2017_15bins/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1cut1tau1l_v51TESNewLepFoLepForrObjectRemoval/mc/variableHists_v0_BDTWithSystematics/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1FR_application/'
    # variables = ['jets_HT', 'jets_bScore', 'jets_bScoreMultiply', 'jets_4largestBscoreSum', 'jets_4largestBscoreMulti', 'bjetsM_invariantMass'] #1tau0l  
    
    # regionList = []
    # variables = ['jets_bScore']

    regionList = ['1tau1lSR']
    variables = ['BDT']
    # ifSys = True 
    ifSys = False

    # channel = uf.getChannelFromDir (TMVAppDir)
    # print(channel)
    

    era = uf.getEraFromDir(inputDir)
    inputDirDic = uf.getInputDicNew( inputDir)
    # sumProcessPerVar = {}
    # sumProcessPerVarSys = {}
    # #sumProcessPerVarSys[var][region][sumedProcess][isysVariation] = hist
    # for ivar in variables:
    #     sumProcessPerVar[ivar], sumProcessPerVarSys[ivar] = uf.getSummedHists( inputDirDic, regionList, ivar, False, era, True )       
    # print( sumProcessPerVar )
    # print('\n')
    # print( sumProcessPerVarSys )
    # print('\n')
    # writeTemplatesForCombine(sumProcessPerVar, sumProcessPerVarSys, inputDirDic['mc'], regionList[0], '1tau1l') 

    templatesFile = inputDir+ '1tau0l_templatesForCombine/templates.root'
    # emptyList = checkEmptyProcess( templatesFile ) #after addSummedHists emptyList contains summeDhist
    # listForCombineSum = getNonEmptyList_new( emptyList,True, channel)
    processListForCombine = getProcessList(templatesFile, ifSys) 
    print('for combine: ', processListForCombine)
    
    # #remove WJets for no WJets entering training
    # listForCombineSum.remove('WJets')

    TMVAppDir = inputDir + '1tau0l_templatesForCombine/'
    channel = uf.getChannelFromDir (TMVAppDir)
    print(channel)
    # writeDatacards( TMVAppDir, listForCombineSum, True, 10, channel )
    # # writeDatacards( TMVAppDir, listForCombine, False, 10 )
    writeDatacards( TMVAppDir, processListForCombine, True, 10,  variables, 'SR'+channel )


def getProcessList( input, ifSys=False):
    list = []
    sysDic = {}
    file = ROOT.TFile.Open(input, 'READ')
    for key in file.GetListOfKeys():
        obj = key.ReadObj()
        ihist = obj.GetName()
        ipro = ihist.split('_')[0]
        if not ('_up' in ihist or '_down' in ihist):
            if ipro=='data': continue
            hist = file.Get(ihist)
            if hist.Integral()<=0:
                print(ipro, ' empty, not add to datacard\n')
                continue
            list.append(ipro)
        if '_up' in ihist:
            isys = 
            sysDic[ipro] = []
            susDic[ipro].append()
            
    list.pop(list.index('tttt')) 
    list.insert( 0, 'tttt')
    return list
            
         
def writeTemplatesForCombine(sumProcessPerVar,sumProcessPerVaySys, inputDir, region, channel='1tau0l') :
    outDir = inputDir + channel + '_templatesForCombine/'
    uf.checkMakeDir( outDir )
    outFile = ROOT.TFile( outDir+'templates.root', 'RECREATE')
    for ivar in sumProcessPerVar.keys():
        dataHist = ROOT.TH1D('data_obs_'+ivar, 'data_obs', sumProcessPerVar[ivar][region]['tttt'].GetNbinsX(), sumProcessPerVar[ivar][region]['tttt'].GetXaxis().GetXmin(), sumProcessPerVar[ivar][region]['tttt'].GetXaxis().GetXmax() )
        dataHist.Reset()
        dataHist.Sumw2()
        for ipro in sumProcessPerVar[ivar][region].keys():
            itempName = ipro + '_' + ivar 
            ihist = sumProcessPerVar[ivar][region][ipro].Clone(itempName)
            ihist.Write()
            if (not ipro=='tttt') and (not ipro=='qcd') and (not ipro=='qcd'):
                dataHist.Add(ihist)
                print('add data:', ihist)
                
                for isys in sumProcessPerVaySys[ivar][region][ipro].keys():
                    ihistSys = sumProcessPerVaySys[ivar][region][ipro][isys].Clone(itempName+'_'+isys)
                    ihistSys.Write()
        dataHist.Write()
    # outFile.ls()
    print('writen templates for combine here', outFile.GetName())
    outFile.Close()    
  
def getNonEmptyList_new( emptyList, isSum=True, channel='1tau1l'):
    listForCombine = []
    if isSum :
        listFrom = summedProcessList
    else:
        listFrom = samples
    for iPro in listFrom:
        if iPro == 'data' or 'jetHT' in iPro: continue
        # if 'WJets' in iPro: continue
        if iPro =='qcd': continue
        if iPro in emptyList: continue 
        listForCombine.append(iPro)
    if channel=='1tau0l':
        listForCombine.append('fakeTau')
    return listForCombine
  
  
def removeData( samples, isSumList = False):
    removedList = []
    for ipro in samples:
        if 'WJets' in ipro: continue
        if not isSumList:
            if (not 'jetHT' in ipro) :
                removedList.append( ipro)
        else:
            if not 'data' in ipro:
                removedList.append( ipro )
    return removedList
        
    





def ifInEmptyList( beginIndex, endIndex , emptyList, g_allProcesses):
    ifAllIn = False
    inNum = 0
    for i in range(beginIndex, endIndex+1):
    #    print( 'test: ', i)
       if g_allProcesses[i] in emptyList:
           inNum = inNum+1
    if inNum == endIndex-beginIndex+1:
        ifAllIn = True
    return ifAllIn
            
    



   
def addSummedHists( TMVAppDir ):
    '''
    add summed process hists, like ttbar_0l+ttbar_1l+ttbar_har=ttbar
    '''
    for ifile in os.listdir( TMVAppDir ):
        if '.root' in ifile:
            print( ifile )
            ifile = TMVAppDir + ifile
            command = 'root -q \'/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/autoTraining_correlation/sumBGsTogether_Nano.C( \"{}\")\''.format(ifile)
            print(command)
            process = subprocess.run( command, shell=True )
            output = process.stdout
            print( output )


def getStringWithSpaces( string, allSpaces ):
    if allSpaces< len(string):
        print( 'spaces not enough!')
        sys.exit()
    return string + (allSpaces-len(string))*' '

def writeSingleCard( rootFile, outCard, listForCombine, autoMCNum, channel, var, ifSys=False ):
    outCard = outCard.replace('Sum', 'Sum_'+var)
    card = open( outCard, 'wt' )
    card.write( 'imax *\n' )
    card.write( 'jmax *\n' )
    card.write( 'kmax *\n' )
    card.write( 80*'-' + '\n' )
    
    histName = ''
    if channel=='SR1tau1l':
        histName = 'PROCESS_BDT' 
    elif channel=='SR1tau0l':
        histName = 'PROCESS_' + var
    # card.write( 'shapes * *  ' + rootFile + '  $PROCESS_MVA_BDT\n'  )
    card.write( 'shapes * *  ' + rootFile + '  ${}\n'.format(histName)  )
    card.write( 'bin          {}\n'.format(channel))
    card.write( 'observation  -1\n')
    card.write( 80*'-' + '\n' )

    dicForProcessLines = {}
    for (i, ipro) in enumerate( listForCombine):
        dicForProcessLines[ipro] = [channel, i, -1]
    df = pd.DataFrame(dicForProcessLines)
    header = df.columns.tolist()
    new_row = pd.DataFrame([header], columns=df.columns)
    df = pd.concat([new_row, df], ignore_index=True)
    row1 = df.iloc[0].copy()
    row2 = df.iloc[1].copy()
    df.iloc[0] = row2
    df.iloc[1] = row1
    new_col = pd.Series(['bin', 'process', 'process', 'rate'])
    # insert the new column at the beginning of the dataframe
    df.insert(loc=0, column='first', value=new_col)
    # print(df)
    
    output_str = df.to_string(index=False, header=False, justify='right')
    card.write(output_str)
    card.write('\n')

    
          
    

    card.write( 80*'-' + '\n' )
    card.write( channel+ '   autoMCStats  ' + str(autoMCNum) +  '\n')

    card.close()
    print( 'datacard writen here: ', outCard)





def writeDatacards( TMVAppDir, listForCombine,  isSum, autoMCNum,  variables, channel='1tau1l' ):
    cardDir = TMVAppDir + 'datacard/'
    if not os.path.exists( cardDir ):
        os.mkdir( cardDir )
    if isSum:
        cardDir = cardDir + 'sumDC'
    else:
        cardDir = cardDir +'seperateDC'
    cardDir = cardDir + '_' + str( autoMCNum ) + '/'
    uf.checkMakeDir(cardDir)

    for entry in os.listdir( TMVAppDir ):
        if not '.root' in entry: continue
        irootFile = TMVAppDir+entry
        ioutCard = entry.split('.root')[0]
        if isSum:
            ioutCard = cardDir + ioutCard + '_Sum_datacard.txt'
        else:
            ioutCard = cardDir + ioutCard + '_datacard.txt'
        print( 'rootFile:', irootFile )
        print( 'datacard: ',ioutCard )
        # writeSingleCard( irootFile, ioutCard, listForCombine, autoMCNum , channel, 'jets_HT')
        for ivar in variables:
            writeSingleCard( irootFile, ioutCard, listForCombine, autoMCNum , channel, ivar)


# def checkEmptyProcess( fileDir, channel ):
def checkEmptyProcess( rootF ):
    # rootF = ""
    # if channel=='1tau1l':
    #     rootF = 'TMVApp_' + channel + '_10var_forCombine.root'
    # elif channel=='1tau0l':
    #     rootF = '1tau0ltemplates_forCombine.root'
    
    emptyProcesses = []
    iFile = ROOT.TFile( rootF)
    itnext = iFile.GetListOfKeys()
    for i in itnext:
        if ('QCD' in i) or ('SingleTop' in i) or ('VV' in i) or ('TT' in i): continue
        print( 'reading hist: ', i.GetName())
        iHistName = i.GetName()
        iProcessName = iHistName[:iHistName.find('MVA')-1]
        iHist = iFile.Get(iHistName)
        if iHist.Integral()<=0:
            emptyProcesses.append( iProcessName )
    emptyProcesses = list( dict.fromkeys(emptyProcesses) )
    print( 'emptyProcesses: ', emptyProcesses )
    return emptyProcesses




if __name__ == '__main__':
    main()
