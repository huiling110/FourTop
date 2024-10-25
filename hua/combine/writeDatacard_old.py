import os
import subprocess
import sys

import ROOT
import usefulFunc as uf
from ttttGlobleQuantity import samples, summedProcessList

# variables = ['jets_HT', 'jets_bScore', 'jets_bScoreMultiply', 'jets_4largestBscoreSum', 'jets_4largestBscoreMulti', 'bjetsM_invariantMass'] #1tau0l  
# variables = ['jets_bScore']
variables = ['MVA_BDT']
def main():
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1fixedTauVariables_v40addTauJetEtau/mc/variableHists_v4forFRAddHistTitle/1tau0l_templatesForCombine/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v3extra1tau1lCut_v42fixedChargeType/1tau1l_v0/AppResults_30bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v6Cut1tau1lVariableFixed_v42fixedChargeType/1tau1l_v0/AppResults_30bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2018/v6Cut1tau1lVariableFixed_v42fixedChargeType/1tau1l_v0/AppResults_30bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_v41addVertexSelection/mc/variableHists_v1HT30bins1tau0l/1tau0l_templatesForCombine/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4baseline_v42fixedChargeType/mc/variableHists_v0forVariables1tau0l/1tau0l_templatesForCombine/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baseline_v42fixedChargeType/mc/variableHists_v0forVariables1tau0l/1tau0l_templatesForCombine/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_v42fixedChargeType/mc/variableHists_v0forVariables1tau0l/1tau0l_templatesForCombine/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v6Cut1tau1lVariableFixed_v42fixedChargeType/1tau1l_v0/AppResults_2016_30bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v8Cut1tau1l_v42fixedChargeType/1tau1l_v0/AppResults_2017_15bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/1tau1l_v0/AppResults_2017_20bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/1tau1l_v0/AppResults_2017_30bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/1tau1l_v0/AppResults_2017_15bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/1tau1l_v0/AppResults_2017_10bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/1tau1l_v0/AppResults_2017_40bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/1tau1l_v0/AppResults_2018_15bins/'
    TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/Run2/v1cut1tau1l_v51TESNewLepObjectRemovalCorrected/1tau1l_v0/AppResults_2016_15bins/'

    # ifMCUncert = False
    ifMCUncert = True

    channel = uf.getChannelFromDir (TMVAppDir)
    print(channel)
    
    
    
    addSummedHists( TMVAppDir )#todo adding histograms is dangerous!!!

    emptyList = checkEmptyProcess( TMVAppDir, channel ) #after addSummedHists emptyList contains summeDhist
    listForCombineSum = getNonEmptyList_new( emptyList,True, channel)
    # listForCombine = getNonEmptyList_new( emptyList, False)
    print('for combine: ', listForCombineSum)
    
    #remove WJets for no WJets entering training
    listForCombineSum.remove('WJets')

    writeDatacards( TMVAppDir, listForCombineSum, True, 10, channel, ifMCUncert )
    # writeDatacards( TMVAppDir, listForCombine, False, 10 )
 
         
  
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

def writeSingleCard( rootFile, outCard, listForCombine, autoMCNum, channel, var, ifMCUncert=True ):
    outCard = outCard.replace('Sum', 'Sum_'+var)
    card = open( outCard, 'wt' )
    card.write( 'imax *\n' )
    card.write( 'jmax *\n' )
    card.write( 'kmax *\n' )
    card.write( 80*'-' + '\n' )
    histName = ''
    if channel=='1tau1l':
        histName = 'PROCESS_MVA_BDT' 
    elif channel=='1tau0l':
        histName = 'PROCESS_' + var
    # card.write( 'shapes * *  ' + rootFile + '  $PROCESS_MVA_BDT\n'  )
    card.write( 'shapes * *  ' + rootFile + '  ${}\n'.format(histName)  )
    # card.write( 'bin          SR_1tau1l\n')
    card.write( 'bin          SR{}\n'.format(channel))
    card.write( 'observation  -1\n')
    card.write( 80*'-' + '\n' )

    processNum = len( listForCombine )
    # card.write( getStringWithSpaces( 'bin', 10) + processNum*getStringWithSpaces('SR_1tau1l', 18) + '\n')
    card.write( getStringWithSpaces( 'bin', 10) + processNum*getStringWithSpaces('SR'+channel, 18) + '\n')
    card.write( getStringWithSpaces('process', 10) )
    for ip in listForCombine:
        card.write( getStringWithSpaces(ip,18))
    card.write('\n')

    start = 0
    card.write( getStringWithSpaces('process', 10))
    while start<processNum:
        card.write( getStringWithSpaces( str(start),18)  )
        start = start+1
    card.write('\n')

    start = 0
    card.write( getStringWithSpaces('rate', 10) )
    while start<processNum:
        card.write( getStringWithSpaces('-1', 18) )
        start = start+1
    card.write('\n')
    card.write( 80*'-' + '\n' )

    if ifMCUncert:
        card.write( 'SR'+channel+ '   autoMCStats  ' + str(autoMCNum) +  '\n')

    card.close()
    print( 'datacard writen here: ', outCard)





def writeDatacards( TMVAppDir, listForCombine,  isSum, autoMCNum, channel='1tau1l' , ifMCUncert=True):
    cardDir = TMVAppDir + 'datacard/'
    if not os.path.exists( cardDir ):
        os.mkdir( cardDir )
    if isSum:
        cardDir = cardDir + 'sumDC'
    else:
        cardDir = cardDir +'seperateDC'
    if not ifMCUncert:
        cardDir = cardDir+'_noMCUncert'
    cardDir = cardDir + '_' + str( autoMCNum ) + '/'
    uf.checkMakeDir(cardDir)

    for entry in os.listdir( TMVAppDir ):
        if not '.root' in entry: continue
        irootFile = TMVAppDir+entry
        ioutCard = entry[:-16]
        if isSum:
            ioutCard = cardDir + ioutCard + '_Sum_datacard.txt'
        else:
            ioutCard = cardDir + ioutCard + '_datacard.txt'
        print( 'rootFile:', irootFile )
        print( 'datacard: ',ioutCard )
        # writeSingleCard( irootFile, ioutCard, listForCombine, autoMCNum , channel, 'jets_HT')
        for ivar in variables:
            writeSingleCard( irootFile, ioutCard, listForCombine, autoMCNum , channel, ivar, ifMCUncert)


def checkEmptyProcess( fileDir, channel ):
    rootF = ""
    if channel=='1tau1l':
        rootF = 'TMVApp_' + channel + '_10var_forCombine.root'
    elif channel=='1tau0l':
        rootF = '1tau0ltemplates_forCombine.root'
    
    emptyProcesses = []
    iFile = ROOT.TFile( fileDir+rootF)
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