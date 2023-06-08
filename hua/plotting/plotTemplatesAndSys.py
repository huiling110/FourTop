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
    for key in file.GetListOfKeys():
        hist = key.ReadObj()
        if not isinstance(hist, ROOT.TH1): continue
        # hist.Print()
        histName = hist.GetName()
        if 'tttt' in histName: continue
        if 'data' in histName: continue
        print(histName) 
        processName = histName[:histName.find('_')]
        print('processName: ', processName)
        sysName = getSysName(histName) 
        print('sysName: ', sysName)
        if not sysName in sysDic.keys():
            sysDic[sysName] = {}
        
        if 'SR' in histName:
            if not 'nominal' in sysDic[sysName].keys():
                sysDic[sysName]['nominal'] = hist.Clone()
                sysDic[sysName]['nominal'].SetName(processName)
            else:
                sysDic[sysName]['nominal'].Add(hist)
                sysDic[sysName]['nominal'].SetName(sysDic[sysName]['nominal'].GetName()+processName)
        # elif 'Up' in histName:
       
        print('\n') 
   
    inputDir = inputTemp[: inputTemp.rfind('/')+1] 
    outDir = inputDir+'templatesPlots/'
    uf.checkMakeDir(outDir)
    
    # plotSysVariaction(nominalHist, sysUp, sysDown, outDir, sysName, process)

def getSysName(histName):
    if 'SR' in histName:
        sys = ''
    if 'Up' in histName :
        sys = histName[histName.find('_'):histName.find('up')] 
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
    
  
    leggy = ROOT.TLegend(0.6,0.75,0.92,0.94)
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
            binUp.append((sysUp.GetBinContent(bin)-nomi)/nomi)
            # binDown.append((sysDown.GetBinContent(bin)-nomi)/nomi)
            binDown.append((nomi-sysDown.GetBinContent(bin))/nomi)
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
    print(y_err_down)
    
    graph = ROOT.TGraphAsymmErrors(num_bins, x_values, y_values, x_err_down, x_err_up, y_err_down, y_err_up)
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