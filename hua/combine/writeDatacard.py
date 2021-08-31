import os
import sys

g_allProcesses = [
    'TTTT', #0
    'TTTo2L2Nu', 'TTToHadronic', 'TTToSemiLeptonic', #3
    'TTGJets', 'ttZJets', 'ttWJets', 'ttH', #7
    'WZ', 'WW', 'ZZ', 'WGJets', 'ZGJetsToLLG', #12
    'WWW', 'WWZ', 'WWG', 'ZZZ', 'WZZ', 'WZG', 'WGG', 'ZGGJets',#20
    'WJetsToLNu', 'DYJetsToTauTau',#22
    'tZq_ll', 'tZq_nunu', 'ST_tW_antitop', 'ST_tW_top',#26
    'TGJets', 'THW', 'THQ', #29
    'QCD_HT200to300', 'QCD_HT300to500', 'QCD_HT500to700', 'QCD_HT700to1000', 'QCD_HT1000to1500', 'QCD_HT1500to2000', 'QCD_HT2000toInf'
]
 
def getStringWithSpaces( string, allSpaces ):
    if allSpaces< len(string):
        print( 'spaces not enough!')
        sys.exit()
    return string + (allSpaces-len(string))*' '

def writeSingleCard( rootFile, outCard ):
    card = open( outCard, 'wt' )
    card.write( 'imax *\n' )
    card.write( 'jmax *\n' )
    card.write( 'kmax *\n' )
    card.write( 80*'-' + '\n' )
    card.write( 'shapes * *  ' + rootFile + '  $PROCESS_MVA_BDT\n'  )
    card.write( 'bin          SR_1tau1l\n')
    card.write( 'observation  -1\n')
    card.write( 80*'-' + '\n' )

    processNum = len( g_allProcesses )
    card.write( getStringWithSpaces( 'bin', 10) + processNum*getStringWithSpaces('SR_1tau1l', 18) + '\n')
    card.write( getStringWithSpaces('process', 10) )
    for ip in g_allProcesses:
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

    card.write( 'SR_1tau1l   autoMCStats  0\n')

    card.close()





def writeDatacards( TMVAppDir ):
    cardDir = TMVAppDir + 'datacard/'
    if not os.path.exists( cardDir ):
        os.mkdir( cardDir )

    for entry in os.listdir( TMVAppDir ):
        irootFile = TMVAppDir+entry
        ioutCard = entry[:-16]
        ioutCard = cardDir + ioutCard + '_datacard.txt'
        print( 'rootFile:', irootFile )
        print( 'datacard: ',ioutCard )
        writeSingleCard( irootFile, ioutCard )






if __name__ == '__main__':
    TMVAppDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v2/AppResults/'

    writeDatacards( TMVAppDir )
