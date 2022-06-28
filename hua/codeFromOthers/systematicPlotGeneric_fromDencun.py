from ROOT import *
from random import *

import sys,os,weightProcesses,math

from array import array

#A bunch of global variables that are used in the drawing

includeDataInStack = True

isEle = False

weights = weightProcesses.ReweightObject(False,isEle)

gROOT.SetBatch()

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

histoGramPerSample = {"tW_top":"tW","tW_antitop":"tW","sChan":"singleTop","tChan":"singleTop","zz":"VV","zPlusJetsLowMass":"zPlusJets","zPlusJetsHighMass":"zPlusJets","wz":"VV","ww":"VV","wPlusJets":"wPlusJets","ttbar":"ttbar","qcd700_1000":"qcd","qcd500_700":"qcd","qcd300_500":"qcd","qcd200_300":"qcd","qcd2000_inf":"qcd","qcd1500_2000":"qcd","qcd100_200":"qcd","qcd1000_1500":"qcd","wPlusJetsMCatNLO":"wPlusJets","tChan_top":"singleTop","tChan_antitop":"singleTop","ttbarBU":"ttbar","tW_top_nfh":"tW","tW_antitop_nfh":"tW","wPlusJetsMadgraph":"wPlusJets","wPlus0Jets":"wPlusJets","wPlus1Jets":"wPlusJets","wPlus2Jets":"wPlusJets"}

samples = ["tW_top_nfh","tW_antitop_nfh","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","ttbar","ttbarBU","wPlus0Jets","wPlus1Jets","wPlus2Jets"]

colourPerSample = {"tW_top":kGreen+2,"tW_antitop":kGreen+2,"tW_top_nfh":kGreen+2,"tW_antitop_nfh":kGreen+2,"tChan":kYellow,"zPlusJetsLowMass":kBlue,"zPlusJetsHighMass":kBlue,"wz":kPink,"ww":kPink,"zz":kPink,"wPlusJets":kTeal,"ttbar":kRed,"qcd700_1000":kGray,"qcd500_700":kGray,"qcd300_500":kGray,"qcd200_300":kGray,"qcd2000_inf":kGray,"qcd1500_2000":kGray,"qcd100_200":kGray,"qcd1000_1500":kGray,"sChan":kOrange,"VV":kPink,"qcd":kGray,"tW":kGreen+2,"zPlusJets":kBlue,"singleTop":kYellow}

legendOrder = ["tW","wPlusJets","ttbar","qcd","VV","zPlusJets","singleTop"]

def makeSystHist(nominalHist,upHist,downHist,canvasName,outDir):
#    canvasName = upHist.GetName().split("Up")[0]
    canvy = TCanvas(canvasName,canvasName,1000,800)
    canvy.cd()
    canvy.SetBottomMargin(0.3)
    nominalHist.SetLineColor(kBlack)
    histMax = 0.
    if upHist.GetMaximum() > histMax: histMax = upHist.GetMaximum() 
    if downHist.GetMaximum() > histMax: histMax = downHist.GetMaximum()
    nominalHist.SetMaximum(histMax*1.2)
    nominalHist.Draw("hist")
    upHist.SetLineColor(kRed)
    upHist.Draw("hist same")
    downHist.SetLineColor(kBlue)
    downHist.Draw("hist same")

    latex.SetTextSize(0.04)
    latex.SetTextFont(cmsTextFont)
    latex.DrawLatex(0.23, 0.95, cmsText )
    
    latex.SetTextFont(extraTextFont)
    latex.SetTextSize(0.04*0.76)
    latex.DrawLatex(0.35, 0.95 , extraText )
    
    latex2.DrawLatex(0.95, 0.95, canvasName);
    
    ratioCanvy = TPad("mva_ratio","mva_ratio",0.0,0.0,1.0,1.0)
    ratioCanvy.SetTopMargin(0.7)
    ratioCanvy.SetFillColor(0)
    ratioCanvy.SetFillStyle(0)
    ratioCanvy.SetGridy(1)
    ratioCanvy.Draw()
    ratioCanvy.cd(0)
    SetOwnership(ratioCanvy,False)
    

    
#    text2 = TLatex(0.45,0.98, "#mu channel " + canvasName)
#    text2.SetNDC()
#    text2.SetTextAlign(13)
#    text2.SetX(0.18)
#    text2.SetY(0.92)
#    text2.SetTextFont(42)
#    text2.SetTextSize(0.0610687)
#

    upHistRatio = upHist.Clone()
    upHistRatio.Divide(nominalHist)
    upHistRatio.SetMaximum(1.3)
    upHistRatio.SetMinimum(0.7)
    upHistRatio.Draw("hist same")
    downHistRatio = downHist.Clone()
    downHistRatio.Divide(nominalHist)
    downHistRatio.GetXaxis().SetTitle("BDT Discriminant")
    downHistRatio.Draw("hist same")

    canvy.SaveAs(outDir+canvasName+".png")

def getSystVariation(nominalHist,systHists,sampleName,region):
    
    systHistUp = nominalHist.Clone("up")
    systHistDown = nominalHist.Clone("down")
    systHistUp.Reset()
    systHistDown.Reset()
    
    for systHi in systHists.keys():
        print
        print systHi
        if "bTag" in systHi: continue
        syst = systHists[systHi].Clone()
        syst.Add(nominalHist,-1)
        syst.Divide(nominalHist)
        for i in range(1,syst.GetXaxis().GetNbins()+1):
            print "{0}: {1:.1f} ({2:.1f} - {3:.1f})".format(i, 100*syst.GetBinContent(i),systHists[systHi].GetBinContent(i),nominalHist.GetBinContent(i)),
            if "up" in syst.GetName():
                systHistUp.SetBinContent(i,systHistUp.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
            else:
                systHistDown.SetBinContent(i,systHistDown.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
    for i in range(1,systHistUp.GetXaxis().GetNbins()+1):
        systHistUp.SetBinContent(i,(math.sqrt(systHistUp.GetBinContent(i)))*nominalHist.GetBinContent(i))
        systHistDown.SetBinContent(i,(math.sqrt(systHistDown.GetBinContent(i)))*nominalHist.GetBinContent(i))

    return systHistUp,systHistDown

def getErrorPlot(totalMC,systUp,systDown,isRatio = False):
    x = array('d',[])
    y = array('d',[])
    exl = array('d',[])
    exh = array('d',[])
    eyl = array('d',[])
    eyh = array('d',[])
    xAxis = systUp.GetXaxis()
    for i in range(1,xAxis.GetNbins()+1):
        x.append(xAxis.GetBinCenter(i))
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
    print
    print x
    print y
    print exl
    print exh
    print eyl
    print eyh
    errors = TGraphAsymmErrors(xAxis.GetNbins(),x,y,exl,exh,eyl,eyh)
    return errors

def makeStackPlot(nominal,systHists,name,region,outDir,savePost = ""):
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
    dataHist = 0
    sumHist = nominal[nominal.keys()[0]].Clone()
    sumHist.Reset()
    systsUp = nominal[nominal.keys()[0]].Clone("systsUp")
    systsUp.Reset()
    systsDown = nominal[nominal.keys()[0]].Clone("systsDown")
    systsDown.Reset()
    for i in nominal.keys():
        if i == "data":
            dataHist = nominal["data"]
            dataHist.SetMarkerStyle(20)
            dataHist.SetMarkerSize(1.2)
            dataHist.SetMarkerColor(kBlack)
            continue
        scaleFactor = weights.getDatasetWeight(i,region)
        nominal[i].Scale(scaleFactor)
        if i in systHists.keys():
            for syst in systHists[i].keys():
                systHists[i][syst].Scale(scaleFactor)
        nominal[i].SetFillColor(colourPerSample[i])
        nominal[i].SetLineColor(kBlack)
        nominal[i].SetLineWidth(1)
        sumHist.Add(nominal[i])
        if i == "qcd": continue
        print i, " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
        tempUp,tempDown = getSystVariation(nominal[i],systHists[i],i,region)
        systsUp.Add(tempUp)
        systsDown.Add(tempDown)
#        stack.Add(nominal[i])
        #Do systematic estimation here when I get aorund to it)

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
    legendOrder.reverse()

    maxi = stack.GetMaximum()
    if dataHist.GetMaximum() > stack. GetMaximum(): maxi = dataHist.GetMaximum()
    stack.SetMaximum(maxi)
    stack.Draw("hist")

    if includeDataInStack: dataHist.Draw("e1x0 same")

    assymErrorPlot.Draw("e2 SAME")
#    assymErrorPlot.Draw("p")

    leggy.Draw()

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


    canvy.SaveAs(outDir+"/{2}{0}{1}.png".format(region,savePost,name))
    canvy.SaveAs(outDir+"/{2}{0}{1}.root".format(region,savePost,name))

    canvy.cd()

def extractHistograms(dir1,dir2,variablesToCheck):

    inDir = os.path.join(dir1,dir2)
    inFiles = [f for f in os.listdir(inDir)]
    
    nominalHists = {}
    systematicHists = {}

    for var in variablesToCheck:
        nominalHists[var] = {}
        systematicHists[var] = {}
    
    for inFileName in inFiles:
        inFile = TFile(os.path.join(inDir+inFileName),"READ")
        sampleName = inFileName.split("output_")[-1].split(".root")[0]
        print sampleName
        if sampleName in samples: # This checks that it is a MC sample
            if histoGramPerSample[sampleName] not in nominalHists[nominalHists.keys()[0]].keys():
                for var in nominalHists.keys():
                    systematicHists[var][histoGramPerSample[sampleName]] = {}
            for key in inFile.GetListOfKeys():
                varName = key.GetName().split(sampleName)[0][:-1]
                if not varName in variablesToCheck: continue
                if "{0}_{1}".format(varName,sampleName) == key.GetName():
                    if histoGramPerSample[sampleName] not in nominalHists[varName].keys():
                        nominalHists[varName][histoGramPerSample[sampleName]] = inFile.Get(key.GetName()).Clone()
                        nominalHists[varName][histoGramPerSample[sampleName]].SetDirectory(0)
                    else:
                        nominalHists[varName][histoGramPerSample[sampleName]].Add(inFile.Get(key.GetName()))
                else: #systematic uncertainties
                    if histoGramPerSample[sampleName] not in systematicHists[varName].keys(): systematicHists[varName][histoGramPerSample[sampleName]] = {}
                    systName = key.GetName().split("{0}_".format(sampleName))[-1]
                    if systName in systematicHists[varName][histoGramPerSample[sampleName]].keys():
    #                    print sampleName,varName,systName, systematicHists[varName][histoGramPerSample[sampleName]][systName]
                        systematicHists[varName][histoGramPerSample[sampleName]][systName].Add(inFile.Get(key.GetName()))
                    else:
                        systematicHists[varName][histoGramPerSample[sampleName]][systName] = inFile.Get(key.GetName()).Clone()
                        systematicHists[varName][histoGramPerSample[sampleName]][systName].SetDirectory(0)
            #Let's also grab the JER/S here
            for syst in ["JER","JES"]:
                systFileUp = TFile(os.path.join(dir1+syst+"Up"+dir2+inFileName),"READ")
                systFileDown = TFile(os.path.join(dir1+syst+"Down"+dir2+inFileName),"READ")
                for varName in variablesToCheck:
                    if not syst+"_up" in systematicHists[varName][histoGramPerSample[sampleName]].keys():
                        systematicHists[varName][histoGramPerSample[sampleName]][syst+"_up"] = systFileUp.Get("{0}_{1}".format(varName,sampleName)).Clone()
                        systematicHists[varName][histoGramPerSample[sampleName]][syst+"_up"].SetDirectory(0)
                        systematicHists[varName][histoGramPerSample[sampleName]][syst+"_down"] = systFileDown.Get("{0}_{1}".format(varName,sampleName)).Clone()
                        systematicHists[varName][histoGramPerSample[sampleName]][syst+"_down"].SetDirectory(0)
                    else:
                        systematicHists[varName][histoGramPerSample[sampleName]][syst+"_up"].Add(systFileUp.Get("{0}_{1}".format(varName,sampleName)).Clone())
                        systematicHists[varName][histoGramPerSample[sampleName]][syst+"_down"].Add(systFileDown.Get("{0}_{1}".format(varName,sampleName)).Clone())
                systFileUp.Close()
                systFileDown.Close()
        else: # Now do data stuff
            if "SingMu" not in inFileName: continue
            inFileQCD = TFile(os.path.join(dir1+"/QCD"+dir2+inFileName),"READ")
            for varName in variablesToCheck:
                if not "data" in nominalHists[varName].keys():
                    nominalHists[varName]["data"] = inFile.Get("{0}_{1}".format(varName,sampleName)).Clone()
                    nominalHists[varName]["data"].SetDirectory(0)
                    nominalHists[varName]["qcd"] = inFileQCD.Get("{0}_{1}".format(varName,sampleName)).Clone()
                    nominalHists[varName]["qcd"].SetDirectory(0)
                else:
                    nominalHists[varName]["data"].Add(inFile.Get("{0}_{1}".format(varName,sampleName)))
                    nominalHists[varName]["qcd"].Add(inFileQCD.Get("{0}_{1}".format(varName,sampleName)))
            inFileQCD.Close()
        inFile.Close()
        
    return (nominalHists,systematicHists)

if __name__ == "__main__":
    #Do something to get your nominal and systUp/Down plots here

    variables = ["mTW","met"]

    nom,systs = extractHistograms("bdtReading/2018-02-22/","3j1t/",variables)

    for variable in variables:        
        makeStackPlot(nom[variable],systs[variable],variable,"3j1t","plots/test/")

#    print nom
#    print systs

    sys.exit(0)

    nominalHist = TH1F("nominalHist","nominalHist",10,0,10)
    for i in range(100):
        nominalHist.Fill(randint(0,10))
    systUp = nominalHist.Clone("up")
    systDown = nominalHist.Clone("down")

    for i in range(1,11):
        systUp.SetBinContent(i,systUp.GetBinContent(i)+uniform(0,3))
        systUp.SetBinContent(i,systUp.GetBinContent(i)-uniform(0,3))

    #Whatever you want your canvas to be called
    name = "yourNameHere"
    #out directory
    outDir = "plots"
    #And now make the systematic comparison plot
    
    makeSystHist(nominalHist,systUp,systDown,name,outDir)
