from array import array
import ROOT
import usefulFunc as uf

def main():
    inputTemp = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineAddMoreSys_v58addGenBranches/mc/variableHists_v41tau0lGenTauSys/combine/templatesForCombine1tau1l.root'
    
    file = ROOT.TFile(inputTemp, 'READ')
    
    # sysName = 'CMS_tttt_FR_shape_stats2017'
    # process = 'fakeTau'
    # nominalHist = file.Get(process+'_SR_jets_bScore') 
    # sysUp  = file.Get(process+ '_'+ sysName + 'Up_jets_bScore')
    # sysDown  = file.Get(process+ '_'+ sysName + 'Down_jets_bScore')
    
    sysDic = {} 
    SRDic = {}
    for key in file.GetListOfKeys():
        hist = key.ReadObj()
        if not isinstance(hist, ROOT.TH1): continue
        # hist.Print()
        histName = hist.GetName()
        if 'data' in histName: continue
        print(histName) 
        processName = histName[:histName.find('_')]
        if processName=='qcd' : continue
        if processName=='tttt' : continue
        if processName=='WJetsToLNu' : continue
        print('processName: ', processName)
        sysName = getSysName(histName) 
        print('sysName: ', sysName)
        if not sysName in sysDic.keys() and (len(sysName)>0):
            sysDic[sysName] = {}
        
        if 'SR' in histName:
            # addToSysDic(sysDic, 'SR', 'nominal', processName, hist)
            SRDic[processName] =  hist.Clone()
        elif 'Up' in histName:
            addToSysDic(sysDic, sysName, 'up', processName, hist)
        elif 'Down' in histName:
            addToSysDic(sysDic, sysName, 'dn', processName, hist)
        print('\n') 
    
    print(sysDic)
    addSRtoSysDic(sysDic, SRDic) 
    print(sysDic)
    
    inputDir = inputTemp[: inputTemp.rfind('/')+1] 
    outDir = inputDir+'templatesPlots/'
    uf.checkMakeDir(outDir)
    for isys in sysDic.keys():
        # if not isys=='CMS_btag_shape_cferr22017': continue
        plotSysVariaction(sysDic[isys]['nominal'], sysDic[isys]['up'], sysDic[isys]['dn'], outDir, isys, sysDic[isys]['up'].GetName() ) 
    
    
    
    

def    addSRtoSysDic(sysDic, SRDic) :
    for isys in sysDic.keys():
        # print(isys)
        name = sysDic[isys]['up'].GetName()
        # print(name)
        processList = name.split('+')
        # print(processList)
        for ipro in processList:
            if not 'nominal' in sysDic[isys].keys():
                sysDic[isys]['nominal'] = SRDic[ipro].Clone()
            else:
                sysDic[isys]['nominal'].Add(SRDic[ipro])
    
    
    
def addToSysDic(sysDic, sysName, sysVari, processName, hist):
    if not sysVari in sysDic[sysName].keys():
        sysDic[sysName][sysVari] = hist.Clone()
        sysDic[sysName][sysVari].SetName(processName)
    else:
        sysDic[sysName][sysVari].Add(hist)
        sysDic[sysName][sysVari].SetName(sysDic[sysName][sysVari].GetName()+'+'+processName)


def getSysName(histName):
    if 'SR' in histName:
        sys = ''
    if 'Up' in histName :
        sys = histName[histName.find('_')+1:histName.find('Up')] 
    if 'Down' in histName:
        sys = histName[histName.find('_')+1:histName.find('Down')] 
    return sys
    
def plotSysVariaction(nominalHist, sysUp, sysDown, outDir, sysName='FR', process='fakeTau'): 
    canvy = ROOT.TCanvas( 'canva', 'canva', 1000,800)
    myStyle = myPlotStyle()
    ROOT.gROOT.SetStyle("myStyle")
    
    pad1 = ROOT.TPad("pad1", "Upper Pad", 0, 0.5, 1, 1)
    pad1.Draw()
    pad2 = ROOT.TPad("pad2", "Lower Pad", 0, 0, 1, 0.5)
    pad2.Draw()
    
    nominalHist.SetLineColor(ROOT.kBlack)
    sysUp.SetLineColor(ROOT.kRed)
    sysDown.SetLineColor(ROOT.kBlue)
    nominalHist.GetXaxis().SetTitle(nominalHist.GetTitle())

    pad1.cd() 
    nominalHist.Draw('HIST')
    sysUp.Draw('HIST SAME')
    sysDown.Draw('HIST SAME')
    
    yMax = sysDown.GetMaximum()
    nominalHist.SetMaximum(yMax*1.3)
    
  
    leggy = ROOT.TLegend(0.6,0.75,0.92,0.99)
    leggy.AddEntry(nominalHist, 'nominal: '+ process)
    leggy.AddEntry(sysUp, 'up: '+sysName)
    leggy.AddEntry(sysDown, 'down: ' + sysName)
    leggy.Draw()
    
    pad2.cd()
    graph = getSysRatio(nominalHist, sysUp, sysDown)
    # Set the marker color and style
    # graph.SetMarkerStyle(20)
    graph.SetMinimum(-0.13)

    # Draw the histogram with variations
    graph.Draw()
    
    plotName =  outDir + sysName +'_sysVariation.png' 
    
    canvy.SaveAs( plotName)
    print('plot saved here: ', plotName )
  
   
def getSysRatio(nominalHist, sysUp, sysDown):
    bin_centers = []
    bin_values = []
    binUp = []
    binDown = []
    for bin in range(1, nominalHist.GetNbinsX() + 1): 
        bin_centers.append(nominalHist.GetBinCenter(bin))
        bin_values.append(0.0)
        nomi = nominalHist.GetBinContent(bin)
        if not nomi==0:
            binUp.append((abs(sysUp.GetBinContent(bin)-nomi)/nomi))
            binDown.append(abs((nomi-sysDown.GetBinContent(bin))/nomi))
        else:
            binUp.append(0)
            binDown.append(0)
  
    num_bins = len(bin_centers)
    x_values = array("d", bin_centers)
    y_values = array("d", bin_values)

# Create arrays to store the upper and lower errors
    x_err_up = array("d", [0] * num_bins)
    x_err_down = array("d", [0] * num_bins)
    y_err_up = array("d", binUp)
    y_err_down = array("d", binDown) 
    # print(y_err_down)
    
    graph = ROOT.TGraphAsymmErrors(num_bins, x_values, y_values, x_err_down, x_err_up, y_err_down, y_err_up)
    graph.GetXaxis().SetRangeUser(nominalHist.GetXaxis().GetXmin(), nominalHist.GetXaxis().GetXmax())
    return graph

        
    
    

    
   
def myPlotStyle():
    tdrStyle = ROOT.TStyle("myStyle","Style for P-TDR")

    tdrStyle.SetCanvasBorderMode(0)
    tdrStyle.SetCanvasColor(ROOT.kWhite)
    tdrStyle.SetCanvasDefH(600)
    tdrStyle.SetCanvasDefW(600)
    tdrStyle.SetCanvasDefX(0)
    tdrStyle.SetCanvasDefY(0)

    tdrStyle.SetPadBorderMode(0)
    tdrStyle.SetPadColor(ROOT.kWhite)

    tdrStyle.SetFrameBorderMode(0)
    tdrStyle.SetFrameBorderSize(1)
    tdrStyle.SetFrameFillColor(0)
    tdrStyle.SetFrameFillStyle(0)
    tdrStyle.SetFrameLineColor(1)
    tdrStyle.SetFrameLineStyle(1)
    tdrStyle.SetFrameLineWidth(1)

    tdrStyle.SetHistLineColor(ROOT.kBlack)
    tdrStyle.SetHistLineStyle(0)
    tdrStyle.SetHistLineWidth(2)

    tdrStyle.SetEndErrorSize(2)
    tdrStyle.SetErrorX(0.)
    
    tdrStyle.SetMarkerStyle(20)
    tdrStyle.SetMarkerSize(2)

    tdrStyle.SetOptFit(1)
    tdrStyle.SetFitFormat("5.4g")
    tdrStyle.SetFuncColor(2)
    tdrStyle.SetFuncStyle(1)
    tdrStyle.SetFuncWidth(1)

    tdrStyle.SetOptDate(0)

    tdrStyle.SetOptFile(0)
    tdrStyle.SetOptStat(0) 
    tdrStyle.SetStatColor(ROOT.kWhite)
    tdrStyle.SetStatFont(42)
    tdrStyle.SetStatFontSize(0.025)
    tdrStyle.SetStatTextColor(1)
    tdrStyle.SetStatFormat("6.4g")
    tdrStyle.SetStatBorderSize(1)
    tdrStyle.SetStatH(0.1)
    tdrStyle.SetStatW(0.15)

    tdrStyle.SetPadTopMargin(0.07)
    tdrStyle.SetPadBottomMargin(0.13)
    tdrStyle.SetPadLeftMargin(0.16)
    tdrStyle.SetPadRightMargin(0.03)

    tdrStyle.SetOptTitle(0)
    tdrStyle.SetTitleFont(42)
    tdrStyle.SetTitleColor(1)
    tdrStyle.SetTitleTextColor(1)
    tdrStyle.SetTitleFillColor(10)
    tdrStyle.SetTitleFontSize(0.05)

    # //Axis titles:
    tdrStyle.SetTitleColor(1,"XYZ")
    tdrStyle.SetTitleFont(42,"XYZ")
    tdrStyle.SetTitleSize(0.06,"XYZ")
    tdrStyle.SetTitleXOffset(0.9)
    tdrStyle.SetTitleYOffset(1.25)
    
    #  // For the axis labels:

    tdrStyle.SetLabelColor(1, "XYZ")
    tdrStyle.SetLabelFont(42,"XYZ")
    tdrStyle.SetLabelOffset(0.007, "XYZ")
    tdrStyle.SetLabelSize(0.05, "XYZ")

    tdrStyle.SetAxisColor(1, "XYZ")
    tdrStyle.SetStripDecimals(ROOT.kTRUE)
    tdrStyle.SetTickLength(0.03, "XYZ")
    tdrStyle.SetNdivisions(510, "XYZ")
    tdrStyle.SetPadTickX(1)  
    tdrStyle.SetPadTickY(1)


    tdrStyle.SetOptLogx(0)
    tdrStyle.SetOptLogy(0)
    tdrStyle.SetOptLogz(0)

    tdrStyle.SetPaperSize(20.,20.)
    
    return tdrStyle

if __name__=='__main__':
    main()