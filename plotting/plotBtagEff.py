import ROOT


def main():
    inputDirFile = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewMV_v59newOScode/mc/variableHists_v1_btagEffMeasure/ttbar_0l.root'
    
    eff_b_eta1 = getEffFromFile(inputDirFile,  ['b_jets_ptEta1_de', 'b_jets_ptEta1_nu'])
   
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