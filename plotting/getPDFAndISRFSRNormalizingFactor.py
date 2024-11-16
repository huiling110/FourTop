import ROOT
import usefulFunc as uf

# 
ROOT.gInterpreter.Declare("""
    #include <vector>
    #include <cmath>  // Ensure sqrt is available
    double quadratic_sum(const ROOT::VecOps::RVec<float>& values) {
        double sum = 0.0;
        for (size_t i=0; i<101; i++){
            sum += (values.at(i)-1.)*(values.at(i)-1.);
        }
        return std::sqrt(sum); 
    }; 
""")

def main():
#! tttt, VLL, ttX and ttbar samples have to be not filtered 
    ROOT.ROOT.EnableImplicitMT()  # Enable multi-threading
    inputDir = '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/'
    isample =  inputDir + 'tttt/'
    era = '2018'
    
    
    
    sumProList = ['tttt', 'VLL', 'tt', 'ttX']
    allSubPros = uf.getSubProDic(era, sumProList)
    # print(allSubPros)
    allSubProList = [value for sublist in allSubPros.values() for value in sublist]
    print(allSubProList)
    
    proDic = {}
    for isub in allSubProList:
        if isub == 'tttt' or isub=='ttbar_0l': continue
        isProDic = getOneSampleScale(inputDir, isub, proDic)
    
    print(proDic)
    outFile = f'./pdfISRFSF_scale{era}.h'
    # outFile = f'./ISRFSF_scale{era}.h'
    writeToMap(outFile, proDic) 

def writeToMap(output_file, data):
    with open(output_file, 'w') as f:
        for key, values in data.items():
            # Format each key-value pair for C++ syntax
            f.write(f'    {{"{key}", {{')
            f.write(", ".join(map(str, values)))  # Add the list values
            f.write('}}')
            f.write(',\n')  # End each entry with a comma and newline
    
    # Close the map initialization
        f.write('};\n')

    print(f"C++ map data has been written to {output_file}")
  
   
def getOneSampleScale(inputDir, ipro, proDic):  
    isample = inputDir + ipro +'/'
    branches = ['genWeight', 'PSWeight', 'LHEPdfWeight']  
    df = ROOT.RDataFrame('Events', isample+'*.root', branches)
    print(isample) 
    genSum = df.Sum('genWeight').GetValue()   
    # print('genSum = ', genSum) 

    df = df.Define('genWeight_PSWeightUp', 'genWeight*PSWeight[0]')
    df = df.Define('genWeight_PSWeightDown', 'genWeight*PSWeight[3]')
    genSum_PSWeightUp = df.Sum('genWeight_PSWeightUp').GetValue()
    genSum_PSWeightDown = df.Sum('genWeight_PSWeightDown').GetValue()
    PSWeight_up_scale = genSum/genSum_PSWeightUp
    PSWeight_down_scale = genSum/genSum_PSWeightDown
    print('PSWeightUp_scale = ', PSWeight_up_scale)
    print('PSWeightDown_scale = ', PSWeight_down_scale)

    #can not run due to too much resources
    df = df.Define('LHEPdfWeight_up', '(1.+ quadratic_sum(LHEPdfWeight)) * genWeight') 
    df = df.Define('LHEPdfWeight_down', '(1.- quadratic_sum(LHEPdfWeight)) * genWeight') 
    pdfSum_up = df.Sum('LHEPdfWeight_up').GetValue()
    pdfSum_down = df.Sum('LHEPdfWeight_down').GetValue()
    pdfSum_up_SF = genSum/pdfSum_up
    pdfSum_down_SF = genSum/pdfSum_down
    print('pdfSum_up_SF=', pdfSum_up_SF)
    print('pdfSum_down_SF=', pdfSum_down_SF)
    
    proDic[ipro] = [PSWeight_up_scale, PSWeight_down_scale, pdfSum_up_SF, pdfSum_down_SF]
    # proDic[ipro] = [PSWeight_up_scale, PSWeight_down_scale]
    del df
    
    
    

if __name__=='__main__':
    main()
