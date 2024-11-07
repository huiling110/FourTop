import ROOT

def main():
#! tttt, VLL, ttX and ttbar samples have to be not filtered 
    inputDir = '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/'
    isample =  inputDir + 'tttt/'
    
    df = ROOT.RDataFrame('Events', isample+'*.root')
    print(isample) 
    genSum = df.Sum('genWeight').GetValue()   
    print('genSum = ', genSum) 

    df = df.Define('genWeight_PSWeightUp', 'genWeight*PSWeight[0]')
    df = df.Define('genWeight_PSWeightDown', 'genWeight*PSWeight[0]')
    genSum_PSWeightUp = df.Sum('genWeight_PSWeightUp').GetValue()
    genSum_PSWeightDown = df.Sum('genWeight_PSWeightDonw').GetValue()
    
    print('PSWeightUp_scale = ', genSum/genSum_PSWeightUp)
    print('PSWeightDown_scale = ', genSum/genSum_PSWeightDown)

if __name__=='__main__':
    main()
