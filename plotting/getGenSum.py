import os
import re
import ROOT

import usefulFunc as uf

def getGenSumFromNano():
    # inputDir = '/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/'
    # inputDir = '/publicfs/cms/data/TopQuark/nanoAOD/2017/mc/'
    inputDir = '/publicfs/cms/data/TopQuark/nanoAOD/2016/mc/'
    # inputDir = '/publicfs/cms/data/TopQuark/nanoAOD/2016APV/mc/'
    
    # year = uf.getEraFromDir(inputDir)
    # year = '2016APV'
    # year = '2018'
    # year = '2017'
    year = '2016'
    
    # iinputDir = inputDir+'tttt/'
    dic = {}
    for ipro in os.listdir(inputDir):
        if not os.path.isdir(inputDir+ipro):
            continue
        # if not ipro == 'WZTo3LNu': continue 
        if 'TTZprime' in ipro: continue
        if 'XToYY' in ipro: continue
        print(ipro)
        iprocess, genSum = calculate_genSum(inputDir+ipro)
        dic[iprocess] = genSum
        
    # save dic into c++ map file
    outfile = f'../inputFiles/genSumMap{year}.h' 
    with open(outfile, 'w') as f:
        f.write('std::map<std::string, double> genSumMap = {\n')
        for key, value in dic.items():
            f.write(f'{{"{key}", {value}}},\n')
        f.write('};\n')
        print(f'{outfile} is saved')
    
def calculate_genSum(directory_path):
    # Initialize the total sum
    total_genSum = 0.0
    # Traverse the directory to find all ROOT files
    process = directory_path.split('/')[-1]
    for root, _, files in os.walk(directory_path):
        for file in files:
            if file.endswith('.root'):
                file_path = os.path.join(root, file)
                
                # Open the ROOT file
                root_file = ROOT.TFile.Open(file_path)
                if not root_file or root_file.IsZombie():
                    print(f"Error opening file: {file_path}")
                    continue
                
                # Extract the genSum (assuming it's stored in a TTree or a TH1)
                # Adjust the following lines based on how genSum is stored in your ROOT files
                # Example for TTree:
                tree = root_file.Get("Runs")  # Replace "tree_name" with your actual tree name
                if not tree:
                    print(f"Tree not found in file: {file_path}")
                    root_file.Close()
                    continue
                
                # Loop over the entries in the tree and sum the genSum
                for entry in tree:
                    total_genSum += entry.genEventSumw  # Replace "genSum" with the actual branch name
                
                # Close the ROOT file
                root_file.Close()
    print('process:', process, 'genSum: ', total_genSum)
    
    return process, total_genSum 

def extract_gen_weight_sum(directory):
    # Dictionary to store results
    gen_weight_sums = {}
    
    # Regex pattern to match the line and extract the number
    # pattern = re.compile(r'genWeightSumInitial: (\d+(\.\d+)?)')
    pattern = re.compile(r'genWeightSumInitial: (\d+(\.\d+)?([eE][+-]?\d+)?)')
    
    # Iterate through all files in the directory
    for filename in os.listdir(directory):
        # Check if the file is a .log file
        if filename.endswith(".log"):
            # Construct the full file path
            filepath = os.path.join(directory, filename)
            
            # Open and read the file
            with open(filepath, 'r') as file:
                for line in file:
                    # Search for the pattern in the current line
                    match = pattern.search(line)
                    if match:
                        # Extract the number from the matched pattern
                        number = float(match.group(1))
                        # Store the result in the dictionary
                        # gen_weight_sums[filename] = number
                        gen_weight_sums[os.path.splitext(filename)[0]] = number
                        break  # Assuming only one such line per file, exit the loop early
                        
    return gen_weight_sums

def getGenSumFromWH():
    # Specify the directory to search
    # directory = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_v0dataMC_allCorrection/log/"
    directory = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHardro_FRweightSys_v79HadroPresel/mc/variableHists_v1dataMC_allCorrectionFakeTau/log/'
    gen_weight_sums = extract_gen_weight_sum(directory)
    # print(gen_weight_sums)
    for filename, weight_sum in gen_weight_sums.items():
        print(f"'{filename}': {weight_sum}")


if __name__=='__main__':
    getGenSumFromNano()