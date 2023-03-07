import ROOT


def main():
    input = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0noCut_v52noHLTSelection/mc/variableHists_test/tttt.root' 
    region = 'noSelection'
    
    
    
    file = ROOT.TFile(input, 'READ') 
    
    for key in file.GetListOfKeys():
        # Get the histogram object
        hist = key.ReadObj()
        histName = hist.GetName()
        print('histName: ', histName) 
     
    
if __name__=='__main__':
    main()
    