import os
import ROOT

def main():
    osDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/ReReco2022PreEE/v1newCrab/'
    
    mcDir = osDir+'mc/'
    for ipro in os.listdir(osDir+'mc/'):
        print(ipro)
        iCutflowHist = getCutFlowHist(mcDir+ipro+'/')
        iCutflowHist.Print()
        
        
  
def getCutFlowHist(dir):
    print('getting cutflow hist for: ', dir)
    summedHist = ROOT.TH1D()
    count = 0
    for ifile in os.listdir(dir):
        if not '.root' in ifile: continue
        rootf = ROOT.TFile(dir+ifile, 'READ')
        iHist = rootf.Get('OScutflow')
        # iHist.Print()
        if count==0:
            summedHist = iHist.Clone()
            summedHist.SetDirectory(0)
        else:
            summedHist.Add(iHist)
        rootf.Close()
        count+=1
    return summedHist
       
   
if __name__=='__main__':
    main() 
    
    