import os
import subprocess
import sys

import ROOT
from ttttGlobleQuantity import samples, summedProcessList

# sys.path.insert(1, '/workfs2/cms/huahuil/4topCode/CMSSW_12_2_4/src/FourTop/hua/tmva/autoTraining_correlation/')
# import generateVariableList as GV

# g_allProcesses = [
#     'tttt', #0
#     'ttbar_2l','ttbar_0l','ttbar_0l',#3
#     'ttG','ttZ', 'ttW','ttH_bb', 'ttH_bb', 'ttH_nonbb',#9
#     'wz','ww','zz',#12
#     'st_tZq', 'st_tW_antitop','st_tW_top',#15
#     'qcd_50to100','qcd_100to200','qcd_200to300','qcd_300to500','qcd_500to700','qcd_700to1000','qcd_1000to1500','qcd_1500to2000','qcd_2000toInf',#24
# ]
# g_allSumProcesses = [
#     'tttt', #0
#     'TT',
#     'TTX',
#     'VV',
#     'SingleTop',
#     'QCD',
# ]

def main():
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau1l_v4/AppResults_11bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau1l_v4/AppResults_30bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau1l_v4/AppResults_60bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau1l_v4/AppResults_90bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau2l_v1/AppResults_30bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/1tau2l_v2/AppResults_30bins/'
    TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/AppResults_30bins/'

    # channel = '2tau0l'
    channel = '1tau1l'
    # channel = '1tau2l'
    
    
    
    addSummedHists( TMVAppDir )

    # emptyList = checkEmptyProcess( TMVAppDir, channel ) #after addSummedHists emptyList contains summeDhist
    # listForCombineSum = getNonEmptyList_new( emptyList)
    # listForCombine = getNonEmptyList_new( emptyList, False)
    # print(listForCombineSum)

    # writeDatacards( TMVAppDir, listForCombineSum, True, 10 )
    # # writeDatacards( TMVAppDir, listForCombine, False, 10 )
  
def getNonEmptyList_new( emptyList, isSum=True):
    listForCombine = []
    if isSum :
        listFrom = summedProcessList
    else:
        listFrom = samples
    for iPro in listFrom:
        if iPro == 'data' or 'jetHT' in iPro: continue
        if 'WJets' in iPro: continue
        if iPro in emptyList: continue 
        listForCombine.append(iPro)
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
        
    

def getNonEmptyList( allList, emptyList ):
    nonEmptyList = []
    for en in allList:
        if not en in emptyList:
            nonEmptyList.append(en)
    return nonEmptyList

def checkEmptyProcessForSum( emptyList ):
    emptyListSum=[]
    if ifInEmptyList( 1,3, emptyList ):
        emptyListSum.apppend( 'TT')
    if ifInEmptyList( 4, 9, emptyList ):
        emptyListSum.append( 'TTX' )
    if ifInEmptyList( 10, 12, emptyList ):
        emptyListSum.append( 'VV' )
    if ifInEmptyList( 13, 15, emptyList ):
        emptyListSum.append( 'SingleTop' )
    if ifInEmptyList( 16, 24, emptyList ):
        emptyListSum.append( 'QCD')
    print( 'summedEmptyList: ', emptyListSum)
    return emptyListSum



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

def writeSingleCard( rootFile, outCard, listForCombine, autoMCNum ):
    card = open( outCard, 'wt' )
    card.write( 'imax *\n' )
    card.write( 'jmax *\n' )
    card.write( 'kmax *\n' )
    card.write( 80*'-' + '\n' )
    card.write( 'shapes * *  ' + rootFile + '  $PROCESS_MVA_BDT\n'  )
    card.write( 'bin          SR_1tau1l\n')
    card.write( 'observation  -1\n')
    card.write( 80*'-' + '\n' )

    processNum = len( listForCombine )
    card.write( getStringWithSpaces( 'bin', 10) + processNum*getStringWithSpaces('SR_1tau1l', 18) + '\n')
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

    card.write( 'SR_1tau1l   autoMCStats  ' + str(autoMCNum) +  '\n')

    card.close()
    print( 'datacard writen here: ', outCard)





def writeDatacards( TMVAppDir, listForCombine,  isSum, autoMCNum ):
    cardDir = TMVAppDir + 'datacard/'
    if not os.path.exists( cardDir ):
        os.mkdir( cardDir )
    if isSum:
        cardDir = cardDir + 'sumDC'
    else:
        cardDir = cardDir +'seperateDC'
    cardDir = cardDir + '_' + str( autoMCNum ) + '/'
    if not os.path.exists( cardDir ):
        os.mkdir( cardDir )

    for entry in os.listdir( TMVAppDir ):
        irootFile = TMVAppDir+entry
        ioutCard = entry[:-16]
        if isSum:
            ioutCard = cardDir + ioutCard + '_Sum_datacard.txt'
        else:
            ioutCard = cardDir + ioutCard + '_datacard.txt'
        print( 'rootFile:', irootFile )
        print( 'datacard: ',ioutCard )
        writeSingleCard( irootFile, ioutCard, listForCombine, autoMCNum )


def checkEmptyProcess( fileDir, channel ):
    rootF = ""
    rootF = 'TMVApp_' + channel + '_10var_forCombine.root'
    
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
