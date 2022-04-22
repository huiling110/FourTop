import os
import sys
import subprocess
import ROOT
sys.path.insert(1, '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/autoTraining_correlation/')
import generateVariableList as GV

g_allProcesses = [
    'tttt', #0
    'ttbar_2l','ttbar_0l','ttbar_0l',#3
    'ttG','ttZ', 'ttW','ttH_bb', 'ttH_bb', 'ttH_nonbb',#9
    'wz','ww','zz',#12
    'st_tZq', 'st_tW_antitop','st_tW_top',#15
    'qcd_50to100','qcd_100to200','qcd_200to300','qcd_300to500','qcd_500to700','qcd_700to1000','qcd_1000to1500','qcd_1500to2000','qcd_2000toInf',#24
]
g_allSumProcesses = [
    'tttt', #0
    'TT',
    'TTX',
    'VV',
    'SingleTop',
    'QCD',
]

def main():
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v2/AppResults_11bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v2/AppResults_changeBDTrange_11bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau2l_v1/AppResults_11bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/2tau0l_v1/AppResults_11bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_11bins/'
    # TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_20bins/'
    TMVAppDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_40bins/'

    # channel = '2tau0l'
    channel = '1tau1l'
    addSummedHists( TMVAppDir )

    emptyList = checkEmptyProcess( TMVAppDir, channel ) #after addSummedHists emptyList contains summeDhist
    emptyListSum = checkEmptyProcessForSum( emptyList )
    listForCombine = getNonEmptyList( g_allProcesses, emptyList )
    listForCombineSum = getNonEmptyList( g_allSumProcesses, emptyListSum  )

    writeDatacards( TMVAppDir, listForCombineSum, True, 10 )

    writeDatacards( TMVAppDir, listForCombine, False, 10 )
  


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



def ifInEmptyList( beginIndex, endIndex , emptyList):
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
    for ifile in os.listdir( TMVAppDir ):
        if '.root' in ifile:
            print( ifile )
            ifile = TMVAppDir + ifile
            # command = 'root -q \'/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/autoTraining_correlation/sumBGsTogether.C( \"{}\")\''.format(ifile)
            command = 'root -q \'../tmva/autoTraining_correlation/sumBGsTogether_Nano.C( \"{}\")\''.format(ifile)
            print(command)
            # process = subprocess.run( command, shell=True, capture_output=True, text=True )
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

    # card.write( 'SR_1tau1l   autoMCStats  0\n')
    card.write( 'SR_1tau1l   autoMCStats  ' + str(autoMCNum) +  '\n')

    card.close()





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
    #  fileDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v2/AppResults/'
    rootF = ""
    # channelName = GV.getNameForChannel( channel )
    rootF = 'TMVApp_' + channel + '_10var_forCombine.root'
    
    emptyProcesses = []
    iFile = ROOT.TFile( fileDir+rootF)
    itnext = iFile.GetListOfKeys()
    for i in itnext:
        print(i.GetName())
        iHistName = i.GetName()
        iProcessName = iHistName[:iHistName.find('MVA')-1]
        # print( iProcessName )
        iHist = iFile.Get(iHistName)
        if iHist.Integral()<=0:
            emptyProcesses.append( iProcessName )
    emptyProcesses = list( dict.fromkeys(emptyProcesses) )
    print( 'emptyProcesses: ', emptyProcesses )
    return emptyProcesses




if __name__ == '__main__':
    main()
