import os,sys,math


from ROOT import *

from setTDRStyle import setTDRStyle
from array import array

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

    "ttG":"ttX",
    "ttZ":"ttX",  
    "ttW":"ttX",
    "ttH_bb": "ttX", 
    "ttH_nonbb": "ttX", 
    "wz":"VV",
    "ww":"VV",
    "zz":"VV",
    "st_tZq":"singleTop",
    "st_tW_antitop":"singleTop",
    "st_tW_top":"singleTop",
}

colourPerSample = {
    'tttt':kPink-9,
    'tt': kRed-4,
    'qcd': kOrange,
    'ttX': kPink-4,
    'singleTop': kPink+5,
    'VV': kYellow,
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
    "ttG",
    "ttZ",  
    "ttW",
    "ttH_bb", 
    "ttH_nonbb", 
    "wz",
    "ww",
    "zz",
    "st_tZq",
    "st_tW_antitop",
    "st_tW_top",
]

legendOrder = ['tttt', 'tt', 'qcd', 'ttX', 'singleTop', 'VV']

includeDataInStack = False




def main():

    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baselineSelection_fromV15/variableHists/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v16_HLTselection/mc/variableHists/'
    variables = [ 'jets_HT', 'jets_number', 'jets_bScore', 'tausT_HT']
    # myRegion = '1tau0lSR'
    myRegion = '1tau0lCR'
    # myRegion = '1tau0lVR'


    nom, systs = extractHistograms( inputDir, variables, myRegion )
    #nom[var].key() is actually summed processes
    print('nom: ', nom)

    plotDir = inputDir+'results/'
    if not os.path.exists( plotDir ):
        os.mkdir( plotDir )
    for variable in variables:        
        makeStackPlot_mcOnly(nom[variable],systs[variable],variable,myRegion, plotDir, 'mcOnly' )


def extractHistograms( dir, variablesToCheck , myRegion):
    nominalHists = {}
    systematicHists = {}

    for var in variablesToCheck:
        nominalHists[var] = {}
        systematicHists[var] = {}
    #nominalHists[varName][histoGramPerSample[sampleName]]

    for inFileName in os.listdir( dir ):
        sampleName = inFileName.split('_variableHist')[0]
        # print('sampleName under dir: ', sampleName )

        if sampleName in samples:
            #???missing something here compared to Duncan's code

            inFile = TFile( os.path.join(dir+inFileName), "READ" )
            for key in inFile.GetListOfKeys():
                # print( 'key in iSample: ', key )
                if 'forYieldCount' in  key.GetName(): continue
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
                        # print('get hist: ', key.GetName() )
                    else: #add grouped mc bg together
                        nominalHists[varName][histoGramPerSample[sampleName]].Add(inFile.Get(key.GetName()))
                        # print('add hist: ', key.GetName() )
                else: #systematic uncertainties
                    if histoGramPerSample[sampleName] not in systematicHists[varName].keys(): systematicHists[varName][histoGramPerSample[sampleName]] = {}
                    systName = key.GetName().split("{0}_".format(sampleName))[-1]
                    #depends on how I name my syst histgram
                    if systName in systematicHists[varName][histoGramPerSample[sampleName]].keys():
    #                    print sampleName,varName,systName, systematicHists[varName][histoGramPerSample[sampleName]][systName]
                        systematicHists[varName][histoGramPerSample[sampleName]][systName].Add(inFile.Get(key.GetName()))
                    else:
                        systematicHists[varName][histoGramPerSample[sampleName]][systName] = inFile.Get(key.GetName()).Clone()
                        systematicHists[varName][histoGramPerSample[sampleName]][systName].SetDirectory(0)
            # for syst in ["JER","JES"]:
            #JER and JES in a different files, good idea!

        else: # Now do data stuff

            inFile.Close()

    return (nominalHists,systematicHists)


def makeStackPlot_mcOnly(nominal,systHists,name,region,outDir, plotNameEtra = ""):
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
        print('ikey: ', i)
        #missing
        nominal[i].SetFillColor(colourPerSample[i])
        nominal[i].SetLineColor(kBlack)
        nominal[i].SetLineWidth(1)
        nominal[i].GetXaxis().SetTitle(name)
        sumHist.Add(nominal[i])

    if "data" in nominal.keys():
        leggy.AddEntry(nominal['data'],"Data","p")
    for entry in legendOrder:
        if entry=='tttt': continue
        leggy.AddEntry(nominal[entry],entry,"f")
    # leggy.AddEntry(assymErrorPlot,"Systs","f")

    legendOrder.reverse()
    for entry in legendOrder:
        if entry=='tttt': continue
        stack.Add(nominal[entry])
        # print( 'ientry integral: ', nominal[entry].Integral() )
    legendOrder.reverse()


    maxi = stack.GetMaximum()
    # if dataHist.GetMaximum() > stack. GetMaximum(): maxi = dataHist.GetMaximum()
    stack.SetMaximum(maxi)
    # stack.GetXaxis().SetTitle(name)
    stack.Draw("hist")

    #scale tttt
    signal = nominal['tttt'].Clone()
    signal.Scale(1000)
    # signal.SetLineColor(kPink-9)
    signal.SetLineColor(kBlue)
    signal.SetLineStyle(kSolid)
    signal.SetLineWidth(4)
    signal.SetFillStyle(3335)
    signal.SetFillColor(kBlue)
    leggy.AddEntry( signal, 'tttt', 'l')
    # signal.GetXaxis().SetTitle(name)
    # signal.Print()
    signal.Draw("SAME HIST ")


    leggy.Draw()

    # canvy.SaveAs(outDir+"{2}{0}{1}.png".format(region,savePost,name))
    canvy.SaveAs( outDir+"{}_{}_{}.png".format(region,name, plotNameEtra) )

    canvy.cd()

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
    #the base hist for adding
    sumHist = nominal[keyList[0]].Clone()
    sumHist.Reset()
    systsUp = nominal[keyList[0]].Clone("systsUp")
    systsUp.Reset()
    systsDown = nominal[keyList[0]].Clone("systsDown")
    systsDown.Reset()

    for i in nominal.keys():
        print('ikey: ', i)
        if i == "data":
            dataHist = nominal["data"]
            dataHist.SetMarkerStyle(20)
            dataHist.SetMarkerSize(1.2)
            dataHist.SetMarkerColor(kBlack)
            continue
        nominal[i].SetFillColor(colourPerSample[i])
        nominal[i].SetLineColor(kBlack)
        nominal[i].SetLineWidth(1)
        nominal[i].GetXaxis().SetTitle(name)
        sumHist.Add(nominal[i]) #sumHist is bg+signal
        # if i == "qcd": continue #special treatment to data driven bg
        #???need systsUp and systsDown calculation

    assymErrorPlot = getErrorPlot(sumHist,systsUp,systsDown)

    assymErrorPlot.SetFillStyle(3013)
    assymErrorPlot.SetFillColor(14)



    if "data" in nominal.keys():
        leggy.AddEntry(nominal['data'],"Data","p")
    for entry in legendOrder:
        leggy.AddEntry(nominal[entry],entry,"f")
    leggy.AddEntry(assymErrorPlot,"Systs","f")

    legendOrder.reverse()
    for entry in legendOrder:
        stack.Add(nominal[entry])
        # print( 'ientry integral: ', nominal[entry].Integral() )
    legendOrder.reverse()


    maxi = stack.GetMaximum()
    if dataHist.GetMaximum() > stack. GetMaximum(): maxi = dataHist.GetMaximum()
    stack.SetMaximum(maxi)
    stack.Draw("hist")

    if includeDataInStack: dataHist.Draw("e1x0 same")

    assymErrorPlot.Draw("e2 SAME")

    if includeDataInStack:
        ratioCanvy = TPad("{0}_ratio".format(name),"{0}_ratio".format(name),0.0,0.0,1.0,1.0)
        ratioCanvy.SetTopMargin(0.7)
        ratioCanvy.SetFillColor(0)
        ratioCanvy.SetFillStyle(0)
        ratioCanvy.SetGridy(1)
        ratioCanvy.Draw()
        ratioCanvy.cd(0)
        SetOwnership(ratioCanvy,False)

        sumHistoData = dataHist.Clone(dataHist.GetName()+"_ratio")
        sumHistoData.Sumw2()
        sumHistoData.Divide(sumHist)

        sumHistoData.GetYaxis().SetTitle("Data/MC")
        sumHistoData.GetYaxis().SetTitleOffset(1.3)
        ratioCanvy.cd()
        SetOwnership(sumHistoData,False)
        sumHistoData.SetMinimum(0.8)
        sumHistoData.SetMaximum(1.2)
        sumHistoData.GetXaxis().SetTitleOffset(1.2)
        sumHistoData.GetXaxis().SetLabelSize(0.04)
        sumHistoData.GetYaxis().SetNdivisions(6)
        sumHistoData.GetYaxis().SetTitleSize(0.03)
        sumHistoData.Draw("E1X0")
        assymErrorPlotRatio = getErrorPlot(sumHist,systsUp,systsDown,True)

        assymErrorPlotRatio.SetFillStyle(3013)
        assymErrorPlotRatio.SetFillColor(14) 
        assymErrorPlotRatio.Draw("e2 same")
    leggy.Draw()

    canvy.SaveAs(outDir+"/{2}{0}{1}.png".format(region,savePost,name))
    # canvy.SaveAs(outDir+"/{2}{0}{1}.root".format(region,savePost,name))

    canvy.cd()


def getErrorPlot(totalMC,systUp,systDown,isRatio = False):
    # for the data/mc ratio
    x = array('d',[])
    y = array('d',[])
    exl = array('d',[])
    exh = array('d',[])
    eyl = array('d',[])
    eyh = array('d',[])
    xAxis = systUp.GetXaxis()
    for i in range(1,xAxis.GetNbins()+1):
        x.append(xAxis.GetBinCenter(i)) # x is the x value
        if not isRatio: y.append(totalMC.GetBinContent(i))
        else: y.append(1.)
        exl.append(xAxis.GetBinCenter(i) - xAxis.GetBinLowEdge(i))
        exh.append(xAxis.GetBinLowEdge(i)+xAxis.GetBinWidth(i)-xAxis.GetBinCenter(i))
        if not isRatio:
            eyl.append(systDown.GetBinContent(i))
            eyh.append(systUp.GetBinContent(i))
        else:
            eyl.append(systDown.GetBinContent(i)/totalMC.GetBinContent(i))
            eyh.append(systUp.GetBinContent(i)/totalMC.GetBinContent(i))
            #???can you simply divide error like this? i think it's wrong
    print(x)
    print(y)
    print(exl)
    print(exh)
    print(eyl)
    print(eyh)
    errors = TGraphAsymmErrors(xAxis.GetNbins(),x,y,exl,exh,eyl,eyh)
    return errors






if __name__ == "__main__":
    main()