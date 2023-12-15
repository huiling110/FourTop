import ROOT
import setTDRStyle as st
import usefulFunc as uf

#!!!functions here are more generic than that of plotForFR.py and plotHLTEfficiency.py, to be generized

def main():
    # inputDirFile = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewMV_v59newOScode/mc/variableHists_v2_btagEffBugFixed/ttbar_0l.root'
    # inputDirFile = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2btagShapeWeightCorrected_v60fixeJetBtagBug/mc/variableHists_v2_btagEffBugFixed/ttbar_0l.root'
    # inputDirFile = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3btagWPWeightGood_v60fixeJetBtagBug/mc/variableHists_v3btagEffNewRegion/ttbar_0l.root'
    # inputDirFile = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/ttbar_0l.root'
    # inputDirFile = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/ttbar_0l.root'
    # inputDirFile = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2eraBugFixed_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/ttbar_0l.root'
    inputDirFile = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v0btagEff/ttbar_0l.root'
    
    era = uf.getEraFromDir(inputDirFile)
    
    plotOverLayForBtagEff(inputDirFile, 'Eta1', era)
    plotOverLayForBtagEff(inputDirFile, 'Eta2', era)
    
    plotBEffFromFile(inputDirFile )
    plotBEffFromFile(inputDirFile, 'C' )
    plotBEffFromFile(inputDirFile, 'L' )
    

def plotBEffFromFile(inputDirFile, gen='B'):    
     
    hist2d_b = getEffFromFile(inputDirFile, ['jets_ptEta_gen'+gen, 'jets_ptEta_gen'+gen+'_nu'])
    inputDir = inputDirFile.rsplit('/',1)[0]
    plotDir = inputDir+'/results/'
    uf.checkMakeDir(plotDir)
    plotName = plotDir+'bEff_'+gen+'.png'
    plotName2 = plotDir+'bEff_'+gen+'_compareOneSelf.png'
    outName = plotDir + 'bEff_'+gen+ '.root'
    plot2D(hist2d_b, plotName, 'b tag efficiency', True, [0., 0.9])
    plot2D(hist2d_b, plotName2, 'b tag efficiency', True)
    saveHistToFile(hist2d_b, outName)
    
def saveHistToFile(hist, outFile):
    rootF = ROOT.TFile(outFile, 'RECREATE')
    hist.SetDirectory(rootF)
    rootF.Write()
    print('file saved here: ', rootF.GetName())
    rootF.Close()
    
def plot2D(hist2D, plotName, canTitle, ifPlotEven=False, yrange=[]):
    #!!!basically same as that of plotHLT but more generic
    print('start plot 2D plot')
    # mystyle = st.setMyStyle() 
    # mystyle.cd()
    can = ROOT.TCanvas('SF', 'SF', 1000, 800)
    ROOT.gStyle.SetOptStat(ROOT.kFALSE)
    ROOT.gStyle.SetPaintTextFormat(".2f")
    # ROOT.gStyle.SetOptTitle(1) #title of the histogram
    # ROOT.gStyle.SetTitleSize(0.07, "X")#???not working
    # ROOT.gStyle.SetTitleSize(0.07, "Y")
    ROOT.gStyle.SetLabelSize(0.05, "Y")
    ROOT.gStyle.SetLabelSize(0.05, "X")
    # levels = [i*1 for i in range(30, 39)]
    # print('colors: ', levels)
    # print(int(ROOT.kRed)) 
    # palette = array.array('i', levels)
    # ROOT.gStyle.SetPalette(57) #default
    # ROOT.gStyle.SetPalette(69)
    ROOT.gStyle.SetPalette(70)
   
    hist2DPlot = hist2D.Clone() 
    if ifPlotEven:
        xbin_edges = hist2DPlot.GetXaxis().GetXbins() 
        ybin_edges = hist2DPlot.GetYaxis().GetXbins() 
        for x in range(1, hist2DPlot.GetNbinsX()+1):
            hist2DPlot.GetXaxis().SetBinLabel(x, str(xbin_edges[x-1]) + '-'+ str(xbin_edges[x]) )
        for y in range(1, hist2DPlot.GetNbinsY()+1):
            hist2DPlot.GetYaxis().SetBinLabel(y, str(ybin_edges[y-1]) + '-'+ str(ybin_edges[y])  )
        hist2DPlot_even = ROOT.TH2D(hist2DPlot.GetName(), hist2DPlot.GetTitle(), len(xbin_edges)-1, 0, len(xbin_edges)-1, len(ybin_edges)-1, 0, len(ybin_edges)-1) 
        for x in range(1, hist2DPlot_even.GetNbinsX()+1):
            hist2DPlot_even.GetXaxis().SetBinLabel(x, hist2DPlot.GetXaxis().GetBinLabel(x)) 
            for y in range(1, hist2DPlot_even.GetNbinsY()+1):
                hist2DPlot_even.SetBinContent(x,y, hist2DPlot.GetBinContent(x,y))
                hist2DPlot_even.SetBinError(x,y, hist2DPlot.GetBinError(x,y))
                if x==1:
                    hist2DPlot_even.GetYaxis().SetBinLabel(y, hist2DPlot.GetYaxis().GetBinLabel(y)) 
        hist2DPlot_even.Print()
    
    if not ifPlotEven:
        histToDraw = hist2DPlot
    else:
        histToDraw = hist2DPlot_even
    
    # box_width = histToDraw.GetXaxis().GetBinWidth(1)
    # box_height = histToDraw.GetYaxis().GetBinWidth(1)
    # font_size = min(box_width, box_height) * 0.8
    # Increase the font size inside each box
    # histToDraw.GetZaxis().SetLabelSize(0.08)
    histToDraw.SetMarkerSize(2.5) #works! for seting the number inside the box

    histTitle = histToDraw.GetTitle() 
    xtitle = histToDraw.GetTitle().split(":")[0]
    ytitle = histToDraw.GetTitle().split(":")[1]
    histToDraw.GetXaxis().SetTitle(xtitle)
    histToDraw.GetYaxis().SetTitle(ytitle)
    histToDraw.GetYaxis().SetTitleSize(0.05)
    histToDraw.GetXaxis().SetTitleSize(0.05)
    histToDraw.GetXaxis().SetTitleOffset(1.0)
    histToDraw.GetXaxis().SetTickLength(0.02)
    # histToDraw.GetXaxis().SetLabelOffset(0.02)  # Offset of X-axis labels from the axis (in multiples of text size)
    # histToDraw.GetXaxis().SetLabelSize(0.03)    # S
    # histToDraw.LabelsOption("v")  #labels drawn vetically
    histToDraw.Draw("colzetext")
    histToDraw.SetTitle(canTitle)
    # histToDraw.SetContour(10)
    if len(yrange)>1:
        histToDraw.SetMinimum(yrange[0])
        histToDraw.SetMaximum(yrange[1])
        
    # ROOT.gPad.Update()
    # palette_axis = ROOT.TPaletteAxis(histToDraw.GetListOfFunctions().FindObject("palette"))
    # palette_axis.SetLabelSize(0.1) #this set the size in the left axis rather than the text 
    # palette_axis.SetTitleSize(0.1) #wrong too
    # hist
     
    can.SetLeftMargin(0.20)
    can.SetRightMargin(0.15)
    can.SetBottomMargin(0.20) 
    # can.SetTopMargin(0.2) 
    # can.SetTitle(canTitle)
    can.Draw("g")
    # can.SaveAs(plotName)
    can.SaveAs(plotName + '.png')
    can.SaveAs(plotName + '.pdf')
    hist2DPlot.SetTitle(histTitle)
    
   
def plotOverLayForBtagEff(inputDirFile, eta='Eta1',era='2017'):   
    
    eff_b_eta1 = getEffFromFile(inputDirFile,  ['b_jets_pt'+eta+'_de', 'b_jets_pt'+eta+'_nu'])
    eff_c_eta1 = getEffFromFile(inputDirFile,  ['c_jets_pt'+eta+'_de', 'c_jets_pt'+eta+'_nu'])
    eff_l_eta1 = getEffFromFile(inputDirFile,  ['l_jets_pt'+eta+'_de', 'l_jets_pt'+eta+'_nu'])
    histList = [eff_b_eta1, eff_c_eta1, eff_l_eta1]
    legendList = ['b', 'c', 'light']
    
    inputDir = inputDirFile.rsplit('/',1)[0]
    plotDir = inputDir+'/results/'
    uf.checkMakeDir(plotDir)
    plotName = plotDir+'/overlay_'+eta+'.png'
    plotOverlay(histList, legendList, era, 'B tag efficiency', plotName, [0., 1.2] )
   
#!!!new version in usefulFunc, keep this here just for now    
def plotOverlay(histList, legenList, era, yTitle, plotName, legendPos=[0.65, 0.8, 0.9,0.93], yRange=[]):
    print('start to plot overlay plot')
    mySty =  st.setMyStyle()
    mySty.cd()
    can = ROOT.TCanvas('overlay', 'overlay', 1000, 800)
    
    # legend = ROOT.TLegend(0.65, 0.8, 0.9, 0.93)  # Create a legend to label the histograms
    legend = ROOT.TLegend(legendPos[0], legendPos[1], legendPos[2], legendPos[3])  # Create a legend to label the histograms
    legend.SetBorderSize(0)
    legend.SetFillStyle(0) 
    legend.SetTextFont(42)
    
    yMax = getYmax(histList)
    #plot style
    LineColorDic={
        # 0: ROOT.TColor.GetColor("#fdae61"),
        0: ROOT.TColor.GetColor("#fd8d3c"),
        1: ROOT.TColor.GetColor("#f03b20"),
        2: ROOT.TColor.GetColor("#2ca25f"),
        #2ca25f green
        #d01c8b purple
        ##fdae61 fc9272" orange
    }
    

    for i, histogram in enumerate(histList):
        if i == 0:
            histogram.Draw()  # Draw the first histogram without any options
        else:
            histogram.Draw("same")  # Draw subsequent histograms with "same" option to overlay

        histogram.SetLineColor(LineColorDic[i])
        histogram.SetMarkerColor(LineColorDic[i])
        histogram.SetLineWidth(3)  # Set line width for each histogram
        histogram.SetMarkerSize(1.5)
        # histogram.SetMarkerStyle(45)
        histogram.SetMarkerStyle(64)
        histogram.GetXaxis().SetTitle(histogram.GetTitle())  # Set X-axis title (modify as needed)
        histogram.GetYaxis().SetTitle(yTitle)  # Set Y-axis title (modify as needed)
        histogram.GetXaxis().SetTitleSize(0.05)
        histogram.GetYaxis().SetTitleSize(0.06)
        if len(yRange)>1:
            histList[i].GetYaxis().SetRangeUser(yRange[0], yRange[1])
        else:
            histList[i].GetYaxis().SetRangeUser(0, yMax*1.3)

        legend.AddEntry(histogram, legenList[i], "lep")  # Add an entry to the legend
        legend.Draw() 
        
    # st.addCMSTextToCan(can, 0.22, 0.4, 0.9, 0.94, era, False)
    st.addCMSTextToCan(can, 0.225, 0.4, 0.9, 0.94, era)
        
    can.SaveAs(plotName)
    print('Done overlay plotting\n\n')
        

    
   
def getEffFromFile(inputDirFile, Histlist):   
    b_eta1List= getHistFromFile( inputDirFile, Histlist) 
    #    print(b_eta1List)
    eff_b_eta1 = getEff( b_eta1List[0], b_eta1List[1] )
    eff_b_eta1.Print() 
    return eff_b_eta1
 
 
def getEff(de, nu) :
    #!!! use maybe TEfficiency later to calculate efficiency
    de_d = de.Clone()
    nu_d = nu.Clone()
    de.Print()
    de_d.Sumw2()
    nu_d.Sumw2()
    eff = de_d.Clone()
    eff.Print()
    eff.Reset()
    eff.Print()
    eff.Divide(nu_d, de_d)
    eff.Print()
    return eff
    
     
  
 
# def getHistFromFile(file_name, histogram_name):
#     file = ROOT.TFile.Open(file_name)

#     if not file or file.IsZombie():
#         print("Error: Unable to open the file.")
#         return None
#     # Get the histogram from the file
#     histogram = file.Get(histogram_name)

#     if not histogram:
#         print("Error: Unable to find the histogram in the file.")
#         file.Close()
#         return None

#     histogram = histogram.Clone()
#     file.Close()

#     return histogram
#!!!put this in usefulFunc.py already    
def getHistFromFile(fileName, histNames):
    file = ROOT.TFile.Open(fileName)

    if not file or file.IsZombie():
        print("Error: Unable to open the file.")
        return []

    histograms = []
    # Loop through the list of histogram names
    for name in histNames:
        # Get the histogram from the file
        histogram = file.Get(name)
        histogram.Print()
        if not histogram:
            print("Error: Unable to find the histogram", name, "in the file.")
            continue
        # Clone the histogram to avoid potential issues when the file is closed
        histogram1 = histogram.Clone()
        # histogram1.Print()
        histogram1.SetDirectory(0)
        histograms.append(histogram1)
    # Close the file (optional, depending on your use case)
    file.Close()

    return histograms
     
    
  
   
   
   
if __name__=='__main__':
    main() 