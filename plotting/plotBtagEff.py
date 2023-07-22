import ROOT
import setTDRStyle as st
import usefulFunc as uf

def main():
    inputDirFile = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewMV_v59newOScode/mc/variableHists_v1_btagEffMeasure/ttbar_0l.root'
    
    era = uf.getEraFromDir(inputDirFile)
    plotOverLayForBtagEff(inputDirFile, 'Eta1', era)
   
def plotOverLayForBtagEff(inputDirFile, eta='Eta1',era='2017'):   
    
    eff_b_eta1 = getEffFromFile(inputDirFile,  ['b_jets_pt'+eta+'_de', 'b_jets_pt'+eta+'_nu'])
    eff_c_eta1 = getEffFromFile(inputDirFile,  ['c_jets_pt'+eta+'_de', 'c_jets_pt'+eta+'_nu'])
    eff_l_eta1 = getEffFromFile(inputDirFile,  ['l_jets_pt'+eta+'_de', 'l_jets_pt'+eta+'_nu'])
    histList = [eff_b_eta1, eff_c_eta1, eff_l_eta1]
    legendList = ['b', 'c', 'light']
    
    inputDir = inputDirFile.rsplit('/',1)[0]
    plotDir = inputDir+'/results/'
    plotName = plotDir+'/overlay_'+eta+'.png'
    plotOverlay(histList, legendList, era, 'B tag efficiency', plotName , [0, 0.2])
    
def plotOverlay(histList, legenList, era, yTitle, plotName, yRange=[0, 1] ):
    print('start to plot overlay plot')
    mySty =  st.setMyStyle()
    mySty.cd()
    can = ROOT.TCanvas('overlay', 'overlay', 1000, 800)
    
    legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)  # Create a legend to label the histograms

    # histList[0].Draw()
    
    # histList[1].Draw('same')
    for i, histogram in enumerate(histList):
        if i == 0:
            histogram.Draw()  # Draw the first histogram without any options
        else:
            histogram.Draw("same")  # Draw subsequent histograms with "same" option to overlay

        histogram.SetLineColor(i + 1)  # Set line color for each histogram
        histogram.SetLineWidth(2)  # Set line width for each histogram
        histogram.GetXaxis().SetTitle(histogram.GetTitle())  # Set X-axis title (modify as needed)
        histogram.GetYaxis().SetTitle(yTitle)  # Set Y-axis title (modify as needed)
        if len(yRange)>1:
            histList[i].GetYaxis().SetRangeUser(yRange[0], yRange[1])

        legend.AddEntry(histogram, legenList[i], "l")  # Add an entry to the legend
        legend.Draw() 
    
    
    can.SaveAs(plotName)
        
    

    
   
def getEffFromFile(inputDirFile, Histlist):   
    b_eta1List= getHistFromFile( inputDirFile, Histlist) 
    #    print(b_eta1List)
    eff_b_eta1 = getEff( b_eta1List[0], b_eta1List[1] )
    eff_b_eta1.Print() 
    return eff_b_eta1
 
 
def getEff(de, nu) :
    #!!! use maybe TEfficiency later to calculate efficiency
    de.Sumw2()
    nu.Sumw2()
    eff = de.Clone()
    eff.Reset()
    eff.Divide(nu, de)
    return eff
    
     
  
 
def getHistFromFile(file_name, histogram_name):
    file = ROOT.TFile.Open(file_name)

    if not file or file.IsZombie():
        print("Error: Unable to open the file.")
        return None
    # Get the histogram from the file
    histogram = file.Get(histogram_name)

    if not histogram:
        print("Error: Unable to find the histogram in the file.")
        file.Close()
        return None

    histogram = histogram.Clone()
    file.Close()

    return histogram
    
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