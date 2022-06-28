import os,sys,math


from ROOT import *

from setTDRStyle import setTDRStyle

setTDRStyle()


histoGramPerSample = {
    'tttt':'tttt',
    'ttbar_0l':'tt',
    'ttbar_1l': 'tt',
    'ttbar_2l': 'tt',
    'qcd_50to100':'qcd',
    'qcd_100to200':'qcd',
    'qcd_200to300':'qcd',
    'qcd_300to500':'qcd',
    'qcd_500to700':'qcd',
    'qcd_700to1000':'qcd',
    'qcd_1000to1500':'qcd',
    'qcd_1500to2000':'qcd',
    'qcd_2000toInf':'qcd',
}

samples = [
    'tttt', 
    'ttbar_0l','ttbar_1l',
    'qcd_2000toInf'
]







def main():

    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baselineSelection_fromV15/variableHists/'
    variables = [ 'jets_HT', 'jets_number']

    nom, systs = extractHistograms( inputDir, variables )
    # a map to a map to a map



def extractHistograms( dir, variablesToCheck):
    nominalHists = {}
    systematicHists = {}

    myRegion = '1tau0lSR'

    for var in variablesToCheck:
        nominalHists[var] = {}
        systematicHists[var] = {}
    #nominalHists[varName][histoGramPerSample[sampleName]]

    for inFileName in os.listdir( dir ):
        sampleName = inFileName.split('_variableHist')[0]
        print('sampleName under dir: ', sampleName )

        if sampleName in samples:
            inFile = TFile( os.path.join(dir+inFileName), "READ" )
            for key in inFile.GetListOfKeys():
                print( 'key in iSample: ', key )
                if key.GetName()=='jetsNumber': continue
                #???need to tune this hist name 
                varName = key.GetName().split(sampleName)[1][1:]
                print('varName: ', varName )




    return (nominalHists,systematicHists)








if __name__ == "__main__":
    main()