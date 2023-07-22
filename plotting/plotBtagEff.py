import ROOT
import setTDRStyle as st
import usefulFunc as uf

#!!!functions here are more generic than that of plotForFR.py and plotHLTEfficiency.py, to be generized

def main():
    inputDirFile = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewMV_v59newOScode/mc/variableHists_v1_btagEffMeasure/ttbar_0l.root'
    
    era = uf.getEraFromDir(inputDirFile)
    
    # plotOverLayForBtagEff(inputDirFile, 'Eta1', era)
    # plotOverLayForBtagEff(inputDirFile, 'Eta2', era)
    
    hist = getHistFromFile(inputDirFile, ['jets_ptEta_genB'])
    file = ROOT.TFile.Open(inputDirFile)
    # file.ls()
    # hist1 = ROOT.TH2D(file.Get('jets_ptEta_genB_nu'))
    # hist1.Print()
    # can = ROOT.TCanvas('SF', 'SF', 1000, 800)
    # hist1.Draw()
    # can.SaveAs('output/test.png')
     
    # hist2d_b = getEffFromFile(inputDirFile, ['jets_ptEta_genB', 'jets_ptEta_genB_nu'])
    # hist2d_b.Print()
    # inputDir = inputDirFile.rsplit('/',1)[0]
    # plotDir = inputDir+'/results/'
    # uf.checkMakeDir(plotDir)
    # plotName = plotDir+'/bEff_b.png'
    # plot2D(hist2d_b, plotName, 'b tag efficiency', True)
    
def plot2D(hist2D, plotName, canTitle, ifPlotEven=False):
    #!!!basically same as that of plotHLT but more generic
    print('start plot 2D plot')
    can = ROOT.TCanvas('SF', 'SF', 1000, 800)
    
    if ifPlotEven:
        xbin_edges = hist2D.GetXaxis().GetXbins() 
        ybin_edges = hist2D.GetYaxis().GetXbins() 
        for x in range(1, hist2D.GetNbinsX()+1):
            hist2D.GetXaxis().SetBinLabel(x, str(xbin_edges[x-1]) + '-'+ str(xbin_edges[x]) )
        for y in range(1, hist2D.GetNbinsY()+1):
            hist2D.GetYaxis().SetBinLabel(y, str(ybin_edges[y-1]) + '-'+ str(ybin_edges[y])  )
        hist2D_even = ROOT.TH2D(hist2D.GetName(), hist2D.GetTitle(), len(xbin_edges)-1, 0, len(xbin_edges)-1, len(ybin_edges)-1, 0, len(ybin_edges)-1) 
        for x in range(1, hist2D_even.GetNbinsX()+1):
            hist2D_even.GetXaxis().SetBinLabel(x, hist2D.GetXaxis().GetBinLabel(x)) 
            for y in range(1, hist2D_even.GetNbinsY()+1):
                hist2D_even.SetBinContent(x,y, hist2D.GetBinContent(x,y))
                hist2D_even.SetBinError(x,y, hist2D.GetBinError(x,y))
                if x==1:
                    hist2D_even.GetYaxis().SetBinLabel(y, hist2D.GetYaxis().GetBinLabel(y)) 
        hist2D_even.Print()
    
    if not ifPlotEven:
        histToDraw = hist2D
    else:
        histToDraw = hist2D_even
        
    histTitle = histToDraw.GetTitle() 
    xtitle = histToDraw.GetTitle().split(":")[0]
    ytitle = histToDraw.GetTitle().split(":")[1]
    histToDraw.GetXaxis().SetTitle(xtitle)
    histToDraw.GetYaxis().SetTitle(ytitle)
    histToDraw.GetYaxis().SetTitleSize(0.05)
    histToDraw.GetXaxis().SetTitleSize(0.05)
    histToDraw.GetXaxis().SetTitleOffset(1.0)
    histToDraw.GetXaxis().SetTickLength(0.02)
    # histToDraw.GetXaxis().SetLabelAngle(45)
    # histToDraw.GetXaxis().SetLabelSize(0.02)
    histToDraw.SetMinimum(0.65)
    histToDraw.SetMaximum(1.35)
    histToDraw.LabelsOption("v") 
    histToDraw.Draw("colzetext")
    histToDraw.SetTitle(canTitle)
    # histToDraw.SetContour(10)
     
    can.SetLeftMargin(0.20)
    can.SetRightMargin(0.15)
    can.SetBottomMargin(0.20) 
    # can.SetTopMargin(0.2) 
    # can.SetTitle(canTitle)
    can.Draw("g")
    can.SaveAs(plotName)
    hist2D.SetTitle(histTitle)
    
   
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
    plotOverlay(histList, legendList, era, 'B tag efficiency', plotName )
    
def plotOverlay(histList, legenList, era, yTitle, plotName, yRange=[]):
    print('start to plot overlay plot')
    mySty =  st.setMyStyle()
    mySty.cd()
    can = ROOT.TCanvas('overlay', 'overlay', 1000, 800)
    
    legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)  # Create a legend to label the histograms
    
    yMax = getYmax(histList)
    #plot style
    LineColorDic={
        0: ROOT.kOrange,
        1: ROOT.TColor.GetColor("#f03b20"),
        2: ROOT.TColor.GetColor("#fc9272"),
    }
    

    for i, histogram in enumerate(histList):
        if i == 0:
            histogram.Draw()  # Draw the first histogram without any options
        else:
            histogram.Draw("same")  # Draw subsequent histograms with "same" option to overlay

        histogram.SetLineColor(LineColorDic[i])
        histogram.SetMarkerColor(LineColorDic[i])
        histogram.SetLineWidth(2)  # Set line width for each histogram
        histogram.SetMarkerSize(4)
        histogram.GetXaxis().SetTitle(histogram.GetTitle())  # Set X-axis title (modify as needed)
        histogram.GetYaxis().SetTitle(yTitle)  # Set Y-axis title (modify as needed)
        if len(yRange)>1:
            histList[i].GetYaxis().SetRangeUser(yRange[0], yRange[1])
        else:
            histList[i].GetYaxis().SetRangeUser(0, yMax*1.3)

        legend.AddEntry(histogram, legenList[i], "l")  # Add an entry to the legend
        legend.Draw() 
        
    can.SaveAs(plotName)
    print('Done overlay plotting\n\n')
        
def getYmax(histograms):
    max_y = -1.0
    for hist in histograms:
        if hist:
            current_max_y = hist.GetMaximum()
            if current_max_y > max_y:
                max_y = current_max_y

    return max_y    

    
   
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