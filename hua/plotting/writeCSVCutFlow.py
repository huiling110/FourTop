import os
import ROOT

def main():
    osDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/ReReco2022PreEE/v1newCrab/'
   
   
    proHistDic = {}  
    getCutFlowForDir(osDir+'mc/', proHistDic)
    getCutFlowForDir(osDir+'data/', proHistDic)
    print(proHistDic)    
    
def getCutFlowForDir(indir, proHistDic):
    # mcDir = osDir+'mc/'
    for ipro in os.listdir(indir):
        print(ipro)
        iCutflowHist = getCutFlowHist(indir+ipro+'/')
        iCutflowHist.Print()
        proHistDic[ipro] = iCutflowHist
     
  
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
    
    