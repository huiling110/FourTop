import os,sys,math


from ROOT import *

from setTDRStyle import setTDRStyle

setTDRStyle()
latex = TLatex()
latex.SetNDC()
latex.SetTextAlign(31)

cmsTextFont = 61
extraTextFont = 52

latex2 = TLatex();
latex2.SetNDC();
latex2.SetTextSize(0.04);
latex2.SetTextAlign(31);

cmsText = "CMS"
extraText = "Preliminary"


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

colourPerSample = {
    'tttt':kRed-2,
    'tt': kRed-4,
    'qcd': kOrange,
}

samples = [
    'tttt', 
    'ttbar_0l','ttbar_0l', 'ttbar_1l',
    'qcd_50to100',
    'qcd_100to200',
    'qcd_200to300',
    'qcd_300to500',
    'qcd_500to700',
    'qcd_700to1000',
    'qcd_1000to1500',
    'qcd_1500to2000',
    'qcd_2000toInf',
]

legendOrder = ['tttt', 'tt', 'qcd']

includeDataInStack = False




def main():

    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baselineSelection_fromV15/variableHists/'
    variables = [ 'jets_HT', 'jets_number']


    nom, systs = extractHistograms( inputDir, variables )
    #nom[var].key() is actually summed processes
    print('nom: ', nom)

    plotDir = inputDir+'results'
    if not os.path.exists( plotDir ):
        os.mkdir( plotDir )
    for variable in variables:        
        makeStackPlot(nom[variable],systs[variable],variable,"1tau0lSR", plotDir )


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
            #???missing something here compared to Duncan's code

            inFile = TFile( os.path.join(dir+inFileName), "READ" )
            for key in inFile.GetListOfKeys():
                print( 'key in iSample: ', key )
                if key.GetName()=='jetsNumber': continue
                #???need to tune this hist name 
                varName = key.GetName().split(sampleName)[1][1:]
                # print('varName: ', varName )

                if not myRegion in key.GetName(): continue
                if not varName in variablesToCheck: continue#only check 
                if not ('up' in key.GetName()) or ('down' in key.GetName()  ):
                    #for nominal hists
                    if histoGramPerSample[sampleName] not in nominalHists[varName].keys():
                        #nominalHist[varName].keys() is summed hists
                        nominalHists[varName][histoGramPerSample[sampleName]] = inFile.Get( key.GetName()).Clone()
                        nominalHists[varName][histoGramPerSample[sampleName]].SetDirectory(0)
                        print('get hist: ', key.GetName() )
                    else:
                        nominalHists[varName][histoGramPerSample[sampleName]].Add(inFile.Get(key.GetName()))
                        print('add hist: ', key.GetName() )
                # else: #systematic uncertainties
                #???


            inFile.Close()

    return (nominalHists,systematicHists)


def makeStackPlot(nominal,systHists,name,region,outDir,savePost = ""):
    #name is variable name
    stack = THStack("{1}_{0}".format(region,name),"{1}_{0}".format(region,name))
    canvy = TCanvas("{1}_{0}".format(region,name),"{1}_{0}".format(region,name),1000,800)
    leggy = TLegend(0.8,0.6,0.95,0.9)
    leggy.SetFillStyle(1001)
    leggy.SetBorderSize(1)
    leggy.SetFillColor(0)
    leggy.SetLineColor(0)
    leggy.SetShadowColor(0)
    leggy.SetFillColor(kWhite)

    canvy.cd()
    if includeDataInStack: canvy.SetBottomMargin(0.3)

    #???no dataHist
    # sumHist = nominal[nominal.keys()[0]].Clone()
    keyList = list(nominal.keys())
    sumHist = nominal[keyList[0]].Clone()
    sumHist.Reset()
    #???no systsUp systsDown

    for i in nominal.keys():
        #missing
        nominal[i].SetFillColor(colourPerSample[i])
        nominal[i].SetLineColor(kBlack)
        nominal[i].SetLineWidth(1)
        sumHist.Add(nominal[i])

    if "data" in nominal.keys():
        leggy.AddEntry(nominal['data'],"Data","p")
    for entry in legendOrder:
        leggy.AddEntry(nominal[entry],entry,"f")
    # leggy.AddEntry(assymErrorPlot,"Systs","f")

    legendOrder.reverse()
    for entry in legendOrder:
    # legendOrder = ["tW","wPlusJets","ttbar","qcd","VV","zPlusJets","singleTop"]
        stack.Add(nominal[entry])
        print( 'ientry integral: ', nominal[entry].Integral() )
    legendOrder.reverse()


    maxi = stack.GetMaximum()
    # if dataHist.GetMaximum() > stack. GetMaximum(): maxi = dataHist.GetMaximum()
    stack.SetMaximum(maxi)
    stack.Draw("hist")


    leggy.Draw()

    canvy.SaveAs(outDir+"/{2}{0}{1}.png".format(region,savePost,name))
    # canvy.SaveAs(outDir+"/{2}{0}{1}.root".format(region,savePost,name))

    canvy.cd()



if __name__ == "__main__":
    main()