import ROOT



def main():
#! tttt, VLL, ttX and ttbar samples have to be not filtered 
    inputDir = '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/'
    isample =  inputDir + 'tttt/'
    
    df = ROOT.RDataFrame('Events', isample+'*.root')
    print(isample) 
    genSum = df.Sum('genWeight').GetValue()   
    # print('genSum = ', genSum) 

    df = df.Define('genWeight_PSWeightUp', 'genWeight*PSWeight[0]')
    df = df.Define('genWeight_PSWeightDown', 'genWeight*PSWeight[3]')
    genSum_PSWeightUp = df.Sum('genWeight_PSWeightUp').GetValue()
    genSum_PSWeightDown = df.Sum('genWeight_PSWeightDown').GetValue()
    print('PSWeightUp_scale = ', genSum/genSum_PSWeightUp)
    print('PSWeightDown_scale = ', genSum/genSum_PSWeightDown)

    # 
    ROOT.gInterpreter.Declare("""
        #include <vector>
        #include <cmath>  // Ensure sqrt is available
        //double quadratic_sum(std::vector<float> values) {
        double quadratic_sum(const ROOT::VecOps::RVec<float>& values) {
            double sum = 0.0;
            for (size_t i=0; i<101; i++){
                sum += (values.at(i)-1.)*(values.at(i)-1.);
            }
            return std::sqrt(sum); 
        }; 
    """)
    # df = df.Define('LHEPdfWeight_up', '1.+quadratic_sum(LHEPdfWeight)') 
    df = df.Define('LHEPdfWeight_up', '(1.+ quadratic_sum(LHEPdfWeight)) * genWeight') 
    df = df.Define('LHEPdfWeight_down', '(1.- quadratic_sum(LHEPdfWeight)) * genWeight') 
    pdfSum_up = df.Sum('LHEPdfWeight_up').GetValue()
    pdfSum_down = df.Sum('LHEPdfWeight_down').GetValue()
    pdfSum_up_SF = genSum/pdfSum_up
    pdfSum_down_SF = genSum/pdfSum_down
    print('pdfSum_up_SF=', pdfSum_up_SF)
    print('pdfSum_down_SF=', pdfSum_down_SF)
    
    
    
    

if __name__=='__main__':
    main()
