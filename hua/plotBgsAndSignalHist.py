import ROOT

import csv

regionsList = [  '1tau0lSR', '1tau0lCR', '1tau0lVR' ]
bgsAndSignalNameList = [ 'TTTT', 'TT', 'TTX', 'VV', 'SingleTop', 'QCD', 'allBg' ]
variable = 'jets_number'

baseDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016_preVFP/v0baselineSelection_fromV15/results/'
csvFile = open( baseDir+'1tau0lCR_EY.csv', 'w')
csvWriter = csv.writer( csvFile, delimiter=',')

csvField = regionsList.copy()
csvField.insert(0, 'process')
print(regionsList)
csvWriter.writerow( csvField )

inputFile = ROOT.TFile( baseDir+'DisForEY.root', 'READ')
inputFile.ls()
for iProcess in bgsAndSignalNameList:
    print( iProcess )
    iProcessEYList = []
    for iRegion in regionsList:
        iHistName = iRegion +'_'+ iProcess +'_'+variable
        # print(iHistName)
        iHist = inputFile.Get( iHistName )
        iHist.Print()
        iProcessEYList.append( iHist.Integral() )
    iProcessEYList.insert(0, iProcess)
    csvWriter.writerow( iProcessEYList  )



# csv_reader = csv.reader(csvFile, delimiter=',')
# for irow in csv_reader:
#     print(irow)
print(csvFile)
csvFile.close()