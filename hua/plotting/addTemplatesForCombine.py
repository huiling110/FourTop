
import ttttGlobleQuantity as gq

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1sysVariation1tau1l/'
    
    allSubPro = list(gq.histoGramPerSampleR.keys())
 
    for isub in allSubPro:
        if 'jetHT' in isub or 'singleMu' in isub: continue
        print(isub)
       
if __name__=='__main__':
    main() 
    