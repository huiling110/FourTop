import ROOT
import usefulFunc as uf

def main():
    input = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noCut_v52noHLTSelection/mc/variableHists_test/tttt.root' 
    region = 'noSelection'
    
    inputDir = input[ 0: input.rfind('/')+1 ]
    print(inputDir)
    outDir = inputDir + 'results/'
    uf.checkMakeDir(outDir)
    
    file = ROOT.TFile(input, 'READ') 
    
    for key in file.GetListOfKeys():
        # Get the histogram object
        hist = key.ReadObj()
        histName = hist.GetName()
        if not region in histName: continue
        print('histName: ', histName) 
        plotShape( hist, outDir  )
        
def plotShape( hist, outDir):
    # outFile = TFile
    canvas = ROOT.TCanvas("canvas", "My Canvas", 800, 600) 
   
    ROOT.gStyle.SetOptTitle(0)
    ROOT.gStyle.SetOptStat(ROOT.kFALSE)

    hist.GetXaxis().SetTitle(hist.GetTitle())
    hist.GetXaxis().SetTitleSize(0.05)
    hist.SetLineWidth(2)
    hist.Draw()
   
   
    outName = outDir+ hist.GetName()+'.png'
    canvas.SaveAs(outName)
    print('plot saved here: ', outName)
    
     
    
if __name__=='__main__':
    main()
    