
import ROOT

def main():
    nanoFile = '/publicfs/cms/data/TopQuark/nanoAOD/2022/0182c6a5-2284-4d01-9af9-b31cf5d0cd07.root'
    nanoFileRun2 = '/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/ttbar_2l/outTree_0.root'
    
    rootF = ROOT.TFile(nanoFile, 'READ')
    tree = rootF.Get('Events')
    rootF2 = ROOT.TFile(nanoFileRun2, 'READ')
    tree2 = rootF2.Get('Events')
   
    get3Hist( tree, tree2)
    
    
def get3Hist( tree, tree2, tauID='VSjet'): 
    hist1 = getHist(tree, 'Tau_idDeepTau2017v2p1'+tauID, '2022')
    hist2 = getHist(tree2, 'Tau_idDeepTau2017v2p1'+tauID, '2017')
    hist3 = getHist(tree, 'Tau_idDeepTau2018v2p5'+tauID, '2022')
    hist1.Print()
    hist2.Print()
    
    drawHistoOverLay(hist1, hist2, hist3)
   
def getHist(tree, branchName, year): 
    tree.Draw(branchName)
    hist1 = ROOT.gPad.GetPrimitive('htemp').Clone()
    hist1.SetDirectory(0)
    hist1.SetName(year+': '+branchName)
    ROOT.gDirectory.Delete('htemp')
    return hist1
    
def drawHistoOverLay(hist1, hist2, hist3): 
    canvas = ROOT.TCanvas("canvas", "Tree Branch Canvas", 800, 600)
    
    hist1.Scale(1.0 / hist1.Integral()) 
    hist2.Scale(1.0 / hist2.Integral()) 
    hist3.Scale(1.0 / hist3.Integral()) 
    
    hist1.SetLineColor(ROOT.kRed)
    hist2.SetLineColor(ROOT.kBlue)
    hist3.SetLineColor(ROOT.kGreen)
    hist1.Draw()
    hist2.Draw('same')
    hist3.Draw('same')
   
    legend = ROOT.TLegend(0.5, 0.7, 0.9, 0.9)
    legend.AddEntry(hist1, hist1.GetName())
    legend.AddEntry(hist2, hist2.GetName())
    legend.AddEntry(hist3, hist3.GetName())
    legend.Draw('same')
    
    
    canvas.SaveAs('output/tauID.png') 
   
   
   
   
   
   
   
    
if __name__=='__main__':
    main()