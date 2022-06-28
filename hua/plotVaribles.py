
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


    variables = [ 'jets_HT', 'jets_number']

    # nom, systs = extractHistograms()



def extractHistograms( variablesToCheck):
    nominalHists = {}
    systematicHists = {}

    for var in variablesToCheck:
        nominalHists[var] = {}
        systematicHists[var] = {}
    #nominalHists[varName][histoGramPerSample[sampleName]]


    return (nominalHists,systematicHists)


if __name__ == "__main__":
    main()